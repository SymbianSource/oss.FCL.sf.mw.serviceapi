/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of the License "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.eclipse.org/legal/epl-v10.html".
*
* Initial Contributors:
* Nokia Corporation - initial contribution.
*
* Contributors:
*
* Description:  
*
*/


#include <e32base.h>
#include <senduiconsts.h>
#include <mmsconst.h>
#include <CMsvAttachment.h>

#include <APGCLI.H>

#include "messageheader.h"
#include "sendmessage.h"

_LIT(KBodyTextFilePath,"C:\\");
// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CSendMessage* CSendMessage::NewL( CMsvSession& aServerSession )
	{
	CSendMessage* self = new (ELeave) CSendMessage( aServerSession );
	return self;
	}

// ---------------------------------------------------------------------------
// Destructor.
// ---------------------------------------------------------------------------
//
CSendMessage::~CSendMessage()
	{
	if ( IsActive() )
		{
		iCallNotifyForCancelFlag = EFalse;
		Cancel();
		}
	
	iMessage.Close();
	iSendAs.Close();
	
	delete iMessageParam;
	delete iNotifyCallback;
	delete iTemplateDetail;
	}

// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CSendMessage::CSendMessage( CMsvSession& aServerSession ):
				CActive( EPriorityStandard ),
				iServerSession( aServerSession ),
				iCallNotifyForCancelFlag(ETrue),
				iBodyTextFileFlag(EFalse)
	{
	}

// ---------------------------------------------------------------------------
// Sets message input parameters 
// aMessageParam/aTemplateDetail/aNotifyCallback ownership is passed to this
// ---------------------------------------------------------------------------
//
void CSendMessage::SetInputParamsL( CSendMessageParams* aMessageParam,
									CMessageDetailInfo* aTemplateDetail,
									CMsgCallbackBase* aNotifyCallback,
									MAsyncRequestObserver* aAsyncRequestObserver )
	{
	iMessageParam = CSendMessageParams::NewL();
	*iMessageParam = *aMessageParam;
	iNotifyCallback = aNotifyCallback;
	iTemplateDetail = aTemplateDetail;
	iAsyncRequestObserver = aAsyncRequestObserver;
	}

// ---------------------------------------------------------------------------
// Sends the message
// ---------------------------------------------------------------------------
//
void CSendMessage::SendMessageL()
	{
	if ( iNotifyCallback ) // making call as asynchronous
		{
		CActiveScheduler::Add( this );
		iMessageState = EInitialize;
		ActivateRequest( KErrNone );
		}
	else				// making call as synchronous
		{
		InitializeL();
		ValidateL();
		SendL();
		}
	}
	
// ---------------------------------------------------------------------------
// Inherited from CActive class 
// ---------------------------------------------------------------------------
//
void CSendMessage::DoCancel()
	{
	NotifyRequestResult( KErrCancel );
	}

// ---------------------------------------------------------------------------
// Inherited from CActive class 
// ---------------------------------------------------------------------------
//
void CSendMessage::RunL()
	{
	TInt err = iStatus.Int();
	if ( err == KErrNone )
		{
		switch ( iMessageState )
			{
			case EInitialize: 
				{
				TRAP( err, InitializeL() );
				iMessageState = EValidate;
				ActivateRequest( err );
				}
				break;	

			case EValidate: 
				{
				TRAP( err, ValidateL() );
				iMessageState = ESend;
				ActivateRequest( err );
				}
				break;	

			case ESend: 
				{
				TRAP( err, SendL() );
				iMessageState = EComplete;
				ActivateRequest( err );
				}
				break;

			case EComplete: 
				{
				NotifyRequestResult( err );
				}
				break;
					
			default:
				NotifyRequestResult( KErrGeneral );	
				break;	
			}
		}
	else
		{
		NotifyRequestResult( err );		
		}
	}

// ---------------------------------------------------------------------------
// Initialises RSendAs Server object and RSendAsMessage Object
// ---------------------------------------------------------------------------
//
void CSendMessage::InitializeL()
	{
	TInt err;
	
	err = iSendAs.Connect();

	if ( err == KErrNone )
		{
		iMessage.CreateL( iSendAs, iMessageParam->MessageType() );
		}
	else
		{
		User::Leave(err);	
		}
	
	if ( iTemplateDetail )
		{
		if ( iTemplateDetail->BodyText().Length() )
			{
			iMessageParam->AppendBodyTextL( iTemplateDetail->BodyText() );
			}
		
		const CArrayPtr<CMessageAttachInfo>* attacharray = iTemplateDetail->AttachmentInfoArray();
		
		if ( attacharray )
			{
			for ( TInt pos = 0; pos < attacharray->Count(); pos++ )
				{
				CMessageAttachInfo* element = (*attacharray)[pos];
				
				TBuf8<KMaxFileName> tmpMime;
				tmpMime.Copy( element->MimeType() );
				
				TRequestStatus stat;
				RFile fileHandle = element->FileHandle();
				iMessage.AddAttachment( fileHandle, tmpMime, stat );
				User::WaitForRequest( stat );

				}
			}
			
		delete iTemplateDetail;
		iTemplateDetail = NULL;
		}
	}

// ---------------------------------------------------------------------------
// Sets Subject, Recipient, BodyText, Attachments to RSendAsMessage object
// ---------------------------------------------------------------------------
//
void CSendMessage::ValidateL()
	{
	AddSubjectL();
	AddRecipientL();
	AddBodyTextL();
	AddAttachmentL();
	}

// ---------------------------------------------------------------------------
// Internal function 
// ---------------------------------------------------------------------------
//
void CSendMessage::SendL()
	{
	if( iMessageParam->LaunchEditor() )
		{
		iMessage.LaunchEditorAndCloseL();
		}
	else
		{
		iMessage.SendMessageAndCloseL();	
		}
	if( iBodyTextFileFlag )	//If the bodytext attach file is created for mms, delete it
		{
		RFs rFs;
    	if( rFs.Connect() == KErrNone )
    		{
    		rFs.Delete( iBodyTextFileName ); //if found delete it b4 creating it
   			rFs.Close();	
    		}
		}	
	}

// ---------------------------------------------------------------------------
// Activates the asynchronous request
// ---------------------------------------------------------------------------
//
void CSendMessage::ActivateRequest( TInt aReason )
	{
	iStatus = KRequestPending;
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete( temp, aReason );
	}

// ---------------------------------------------------------------------------
// Notifies callback the result for asynchronous request.
// ---------------------------------------------------------------------------
//
void CSendMessage::NotifyRequestResult( TInt aReason )
	{
	if ( iNotifyCallback )
		{
		iAsyncRequestObserver->RequestComplete( iNotifyCallback->iTransactionId );
		
		if( iCallNotifyForCancelFlag )
			{
			TRAPD( err, iNotifyCallback->NotifyResultL( aReason, NULL ));	
			}
		}
	// caller will delete the object in case of cancel
	if ( aReason != KErrCancel )
		delete this;
	}

// ---------------------------------------------------------------------------
// Sets the subject for message
// ---------------------------------------------------------------------------
//
void CSendMessage::AddSubjectL()
	{
	TPtrC subject( iMessageParam->Subject());
	if ( subject.Length() )
		iMessage.SetSubjectL( iMessageParam->Subject() );
	}

// ---------------------------------------------------------------------------
// Sets the recipient address.
// ---------------------------------------------------------------------------
//
void CSendMessage::AddRecipientL()
	{
	const CRecipientList* recipientArray = iMessageParam->RecipientArray();
	if ( recipientArray )
		{
		TInt count = recipientArray->Count();
		for( TInt pos = 0; pos < count; pos++ )
			{
			iMessage.AddRecipientL( (*recipientArray)[pos], 
				RSendAsMessage::TSendAsRecipientType( recipientArray->Type(pos) ) );
			}
		}
	else if ( !iMessageParam->LaunchEditor() )
		{
		User::Leave( KErrArgument );
		}
	}


// ---------------------------------------------------------------------------
// Sets body text to message.
// ---------------------------------------------------------------------------
//
void CSendMessage::AddBodyTextL()
	{
	TPtrC filePath( KBodyTextFilePath );
	
	TPtrC bodyText = iMessageParam->BodyText();
	
	if ( bodyText.Length() )
		{
		if ( iMessageParam->MessageType() == KSenduiMtmMmsUid )
			{
    		RFs rFs;
			RFile tmpfile;
    		User::LeaveIfError( rFs.Connect() );
   			
    		tmpfile.Temp(rFs, filePath, iBodyTextFileName, EFileShareExclusive|EFileWrite);
			
			iBodyTextFileFlag = ETrue;
			
			HBufC8* buffer=HBufC8::NewL( bodyText.Length() );
			CleanupStack::PushL( buffer );
			buffer->Des().Copy( bodyText );
			tmpfile.Write( *buffer ); 
			tmpfile.Flush();
			tmpfile.Close();			
			rFs.Close();
			CleanupStack::PopAndDestroy( buffer );
			
			TRequestStatus stat;
			iMessage.AddAttachment( iBodyTextFileName, KMmsTextPlain, stat );
			User::WaitForRequest( stat );
			}
		else
			{
			iMessage.SetBodyTextL( bodyText );	
			}
		}
	}

// ---------------------------------------------------------------------------
// Adds attachments to message
// ---------------------------------------------------------------------------
//
void CSendMessage::AddAttachmentL()
	{
	const CArrayPtr<CMsvAttachment>* attachmentArray = iMessageParam->AttachmentArray();
	if ( attachmentArray && attachmentArray->Count() > 0 )
		{
		TRequestStatus attachstatus;
		TInt error = KErrNone;
		TInt count;
		RApaLsSession rapaSesion;
		RFs rFs;
		RFile tmpfile;
		
		User::LeaveIfError( rapaSesion.Connect() );
		
		CleanupClosePushL( rapaSesion );
		
		User::LeaveIfError( rFs.Connect() );
		
		CleanupClosePushL( rFs );
		
		for ( count = 0; count < attachmentArray->Count(); count++ )
			{
			attachstatus = KRequestPending;	
			
			error = tmpfile.Open(rFs, ((*attachmentArray)[count])->AttachmentName(), EFileRead);
			
			if( error == KErrNone )
				{
				TBuf8<256> tmpbuf;
				
				tmpfile.Read(tmpbuf, 255 );
				
				tmpfile.Close();
				
				TDataRecognitionResult aDataType;
				
				error = rapaSesion.RecognizeData(((*attachmentArray)[count])->AttachmentName(), tmpbuf, aDataType);
				
				if( error == KErrNone )
					{
					TBuf8< KMaxDataTypeLength > tmp;
					tmp.Copy( aDataType.iDataType.Des() );
					
					iMessage.AddAttachment( ((*attachmentArray)[count])->AttachmentName(),
												tmp,
												attachstatus );																										
					}
				else
					{					
					if ( ((*attachmentArray)[count])->MimeType().Length() )
						{
						iMessage.AddAttachment( ((*attachmentArray)[count])->AttachmentName(),
												((*attachmentArray)[count])->MimeType(),
												attachstatus );
						}
					else
						{
						iMessage.AddAttachment( ((*attachmentArray)[count])->AttachmentName(), 
												attachstatus );
						}
					}	
				
				User::WaitForRequest( attachstatus );
				
				User::LeaveIfError( attachstatus.Int() );	
				}
			else
				{
				User::Leave( error );				
				}	
			}
		CleanupStack::PopAndDestroy( &rFs );	
		CleanupStack::PopAndDestroy( &rapaSesion );
		}
	}

	
