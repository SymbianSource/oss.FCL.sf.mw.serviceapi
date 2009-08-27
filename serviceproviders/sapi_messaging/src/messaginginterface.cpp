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
#include <e32def.h>
#include <msvapi.h>
#include <msvids.h>

#include <cmsvattachment.h>

#include "messageheader.h"
#include "messagingservice.h"
#include "messaginginterface.h"
#include "serviceerrno.h"

using namespace LIW;

_LIT8(KErrorCode,		"ErrorCode");
_LIT8(KTransactionID,	"TransactionID");
_LIT8(KReturnValue,		"ReturnValue");
_LIT8(KContentType,		"Type");



// Messaging Command Names
_LIT8(KCmdSendMessage,		"Send");
_LIT8(KCmdGetHeaderList,	"GetList");
_LIT8(KCmdRegNotification,	"RegisterNotification");
_LIT8(KCmdCancelNotification,"CancelNotification");
_LIT8(KCmdDeleteMsg,		"Delete");
_LIT8(KCmdChangeStatus,		"ChangeStatus");
_LIT8(KCmdCancel,			"Cancel");

// Send Message Parameters
_LIT8(KMessageParam, 		"MessageParam");
_LIT8(KMtm, 				"MessageType");
_LIT8(KTemplateId,  		"TemplateId");
_LIT8(KSubject,  			"Subject");
_LIT8(KBodyText,  			"BodyText");
_LIT8(KLaunchEditor,		"LaunchEditor");
_LIT8(KRecipientTo,  		"To");
_LIT8(KRecipientToElement,  "To List Element");
_LIT8(KRecipientCc,  		"Cc");
_LIT8(KRecipientCcElement,  "Cc List Element");
_LIT8(KRecipientBcc,  		"Bcc");
_LIT8(KAttachmentName, 		"Attachment");
_LIT8(KRecipientBccElement, "Bcc List Element");
_LIT8(KAttachmentList, 		"AttachmentList");
_LIT8(KAttachmentListElement,"AttachmentList Element");
_LIT8(KAttachmentType,		"AttachmentType" );
_LIT8(KFileName, 			"FileName" );
_LIT8(KMimeType, 			"MimeType" );

_LIT(KAttachmentFile,		"File" );
_LIT(KAttachmentLinkedFile,	"LinkedFile" );

// Header List Input Parameters
_LIT8(KFilter,				"Filter" );
_LIT8(KSortOrder,			"SortOrder" );
_LIT8(KField,				"Key");
_LIT8(KOrder,				"Order");

_LIT(KSortByDate,			"Date" );
_LIT(KSortBySize,			"Size" );
_LIT(KSortBySender,			"Sender" );
_LIT(KSortBySubject,		"Subject" );
_LIT(KSortById,				"MessageId" );
_LIT(KSortAsc,				"Ascending" );
_LIT(KSortDec,				"Descending" );
 
_LIT8(KSenderList, 			"SenderList");
_LIT8(KMtmList,				"MessageTypeList" );

_LIT8(KSenderElement, 		"SenderList Number");
_LIT8(KMtmElement,			"MessageTypeList Element" );
_LIT8(KMessageId, 			"MessageId");
_LIT8(KStartDate,			"StartDate" );
_LIT8(KEndDate,				"EndDate" );

// Header List Output Parameters
_LIT8(KUnreadFlag, 			"Unread");
_LIT8(KAttachFlag, 			"Attachment");
_LIT8(KPriority, 			"Priority");
_LIT8(KTime, 				"Time");

 
// Message detail Output Parameters
_LIT8(KSender,  			"Sender");
_LIT8(KFileSize, 			"FileSize" );
_LIT8(KFileHandle, 			"FileHandle" );


// Change status parameters
_LIT8(KStatus,				"Status");
_LIT(KInbox,				"Inbox");
_LIT(KStatusFlagRead,		"Read");
_LIT(KStatusFlagUnread,		"Unread");
_LIT(KStatusFlagReplied,	"Replied");
_LIT(KStatusFlagForward,	"Forwarded");
_LIT(KStatusFlagDeleted,	"Deleted");

// New Message Notification Parameters
_LIT8(KNotificationType,	"Type");
_LIT(KNotificationNewMsg,	"NewMessage");

//ErrorMessages
_LIT8( KErrorMessage, "ErrorMessage"); 
const TInt KMaxMsgSize = 256;

_LIT(KDomainName,"Messaging");
_LIT(KErrorMsgSeparator,":");
_LIT( KIncorrectValue, " Value Incorrect" );
_LIT( KDateMismatch, " Start Date greater than EndDate in Filter" );
_LIT( KTypeInvalid, " Type Invalid" );
_LIT( KMissing, " Missing" );
_LIT( KErrMsgMissingLiwCancel, "Liw Cancel Options Not Set" );
_LIT( KInvalidCallbackSetup, "Insufficent argument for asynchronous request" );
_LIT( KInvalidCMD, "Command not supported");
_LIT( KAsyncNotSupported,"Asynchronous Operation not supported" );
_LIT( KSyncNotSupported,"Synchronous Operation not supported" );


void UpdateOutputAsHeaderL( CLiwGenericParamList* aOutParamList, TAny* aResult );

void UpdateOutputAsIdListL( CLiwGenericParamList* aOutParamList, 
										CMsvEntrySelection* aEntrySelection, 
										CMessagingService* aMsgService,
										CFilterParamInfo* aFilter );

void UpdateMessageDetailToMapL( CLiwMap* aResultMap, CMessageDetailInfo* aMessageDetail );


TBool GetLiwHeaderL( CMessageHeader* aHeader, 
										TLiwVariant& aElement, 
										CMessagingService* aMsgService = NULL, 
										TBool aCustomMap = EFalse );

TInt32 ErrCodeConversion(TInt code);

// ---------------------------------------------------------------------------
// Check the Type of Liw variant... whether they match or not....
// If they dont match leave 
// If source is of nullvariant type then leave only if aLeaveflag is set
// ---------------------------------------------------------------------------
//
TBool CMessagingInterface::CheckInputTypeL( const TLiwVariant* aSource, 
                                            TBool aLeaveFlag, 
                                            LIW::TVariantTypeId aExpectedtype, 
                                            const TDesC8& aCmdName, 
											const TDesC8& aParameter,
											const TDesC& aMessage )
	{
	if ( aSource->TypeId() == aExpectedtype )
	    {
	    return ETrue;
	    }
	
	else if ( ( aSource->TypeId() != LIW::EVariantTypeNull ) || aLeaveFlag )
		{
		AppendErrorMessageL( aCmdName, aParameter, aMessage, 0 );
		((TLiwVariant*)aSource)->Reset();
		User::Leave( KErrBadName );
		}	
			    
	return EFalse;
	}

// ---------------------------------------------------------------------------
// Append Error Message
// ---------------------------------------------------------------------------
//
void CMessagingInterface::AppendErrorMessageL( const TDesC8& aCmdName, 
											   const TDesC8& aParameter, 
											   const TDesC& aMessage,
											   TInt aNoneOrMissingOrIncorrect )
	{
	iErrorMessage = HBufC::NewL( KMaxMsgSize );
	TPtr tmpMsgPtr = iErrorMessage->Des();
	tmpMsgPtr.Copy(KDomainName);
	
	HBufC* temp = HBufC::New( KMaxMsgSize );

	if ( aCmdName.Length() )
		{
		tmpMsgPtr.Append( KErrorMsgSeparator );
		temp->Des().Copy( aCmdName ); 
		tmpMsgPtr.Append( temp->Des() );
		}

	tmpMsgPtr.Append(KErrorMsgSeparator);
	
	if ( aParameter.Length() )
		{
		temp->Des().Copy(aParameter); 
		tmpMsgPtr.Append(temp->Des());
		}
	
	if ( aMessage.Length() )
		{
		tmpMsgPtr.Append( aMessage );
		}
    
    delete temp;
    		
	switch( aNoneOrMissingOrIncorrect )
		{
		case 1:
		        User::Leave(SErrMissingArgument);
		case 2:
		        User::Leave(KErrArgument);
		default:		        
		        break;
		}	
	}

// ---------------------------------------------------------------------------------------
// Function called from sync APIs to check whether Async set up is done if yes then leaves
// ---------------------------------------------------------------------------------------
//
inline void CMessagingInterface::LeaveIfAsynchronousL( TUint aCmdOptions,
	 				          					MLiwNotifyCallback* aCallback,
					          				    const TDesC8& aCmdName, 
											    const TDesC& aMessage )
	{
	if( aCallback && ( KLiwOptASyncronous & aCmdOptions ) )
		{
		AppendErrorMessageL( aCmdName, KNullDesC8, aMessage, 2/*For KErrArgument*/ );
		}
	}
		
// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CMessagingInterface* CMessagingInterface::NewL()
	{
  	CMessagingInterface* self = new (ELeave) CMessagingInterface();
  	CleanupStack::PushL( self );
  	self->ConstructL();
  	CleanupStack::Pop( self );
	return self;
	}
// ---------------------------------------------------------------------------
// Destructor.
// ---------------------------------------------------------------------------
//	
CMessagingInterface::~CMessagingInterface()
	{
	delete iErrorMessage;
	delete iMsgService;
	}

// ---------------------------------------------------------------------------
// Closes the interface
// ---------------------------------------------------------------------------
//

void CMessagingInterface::Close()
	{
	delete this;
	}

// ---------------------------------------------------------------------------
// Constructor
// ---------------------------------------------------------------------------
//
CMessagingInterface::CMessagingInterface(): iErrorMessage(0)
	{
	}

// ---------------------------------------------------------------------------
// Symbian Constructor
// ---------------------------------------------------------------------------
//	
void CMessagingInterface::ConstructL()
	{
	iMsgService = CMessagingService::NewL();	
	}

// ---------------------------------------------------------------------------
//  Executes the SAPI as per params
// ---------------------------------------------------------------------------
//
void CMessagingInterface::ExecuteCmdL( const TDesC8& aCmdName,
					                       const CLiwGenericParamList& aInParamList,
					                       CLiwGenericParamList& aOutParamList,
					                       TUint aCmdOptions,
					                       MLiwNotifyCallback* aCallback )
	{
	TInt errcode = KErrNotSupported;
	TInt32 transactionId(-1);
	if( ( aCallback && !( KLiwOptASyncronous & aCmdOptions ) ) 
	 || ( !aCallback && ( KLiwOptASyncronous & aCmdOptions ) ) )
		{//if any one of them is set it is an error
		errcode = KErrArgument;		
		AppendErrorMessageL( aCmdName, KNullDesC8, KInvalidCallbackSetup, 0 );
		}
		
	if ( aCmdName.CompareF( KCmdGetHeaderList ) == 0 )
		{
		TRAP( errcode, GetHeaderListL( aInParamList, aOutParamList, aCmdOptions, aCallback ) );
		}
	else if ( aCmdName.CompareF( KCmdSendMessage ) == 0 )
		{
		TRAP( errcode, SendMessageL( aInParamList, aOutParamList, aCmdOptions, aCallback ) );
		}	
	else if ( aCmdName.CompareF( KCmdRegNotification ) == 0 )
		{
		TRAP( errcode, RequestNotificationL( aInParamList, aOutParamList, aCmdOptions, aCallback ) );
		}
	else if ( aCmdName.CompareF( KCmdCancelNotification ) == 0 )
		{
		TRAP( errcode, CancelNotificationL( aInParamList, aOutParamList, aCmdOptions, aCallback ) );
		}		
	else if ( aCmdName.CompareF( KCmdDeleteMsg ) == 0 )
		{
		TRAP( errcode, DeleteMessageL( aInParamList, aOutParamList, aCmdOptions, aCallback ) );
		}		
	else if ( aCmdName.CompareF( KCmdChangeStatus ) == 0 )
		{
		TRAP( errcode, ChangeStatusL( aInParamList, aOutParamList, aCmdOptions, aCallback ) );
		}		
	else if ( aCmdName.CompareF( KCmdCancel ) == 0 )
		{		
		TRAP( errcode, CancelAsyncL( aCmdName, aInParamList, aOutParamList, aCmdOptions) );
		}			
	else 
		{			
		AppendErrorMessageL( aCmdName, KNullDesC8, KInvalidCMD, 0 );		
		}
			
	aOutParamList.AppendL(TLiwGenericParam( KErrorCode, 
							  TLiwVariant(ErrCodeConversion(errcode))));
	if( errcode != KErrNone )
		{
		aOutParamList.Reset();
		aOutParamList.AppendL(TLiwGenericParam( KErrorCode, 
							  TLiwVariant(ErrCodeConversion(errcode))));		
		if ( iErrorMessage )
			{
			aOutParamList.AppendL(TLiwGenericParam( KErrorMessage, 
								  TLiwVariant(iErrorMessage->Des())));
			delete iErrorMessage;
			iErrorMessage = NULL;		
			}
		}		
	}

// ---------------------------------------------------------------------------
// Issues SendMessage request to MessagingService
// ---------------------------------------------------------------------------
//	
void CMessagingInterface::SendMessageL( const CLiwGenericParamList& aInParamList,
					                       CLiwGenericParamList& aOutParamList,
					                       TUint aCmdOptions,
					                       MLiwNotifyCallback* aCallback )
	{
	CSendMessageParams* sendParam = GetSendParametersL( aInParamList );

	CleanupStack::PushL(sendParam);

	CMsgCallbackBase* callback = NULL;

	if ( aCallback && ( KLiwOptASyncronous & aCmdOptions ))
		{
		callback = CMsgCallbackInt::NewL();
		CleanupStack::PushL( callback );
		callback->iPtrInParamList = &aInParamList;
		callback->iPtrNotifyCallback = aCallback;
		callback->iTransactionId = aCallback->GetTransactionID();

		aOutParamList.AppendL(TLiwGenericParam( KTransactionID, 
								TLiwVariant( callback->iTransactionId )));		
		}
	
	
	// callback ownership Passed to SendMessageL
	iMsgService->SendMessageL( sendParam, callback );
	
	if ( callback )
		CleanupStack::Pop( callback );
	
	CleanupStack::PopAndDestroy( sendParam );
	}
	
// ---------------------------------------------------------------------------
// Cancel an Asynch request
// ---------------------------------------------------------------------------
//
void CMessagingInterface::CancelAsyncL( const TDesC8& aCmdName,
										const CLiwGenericParamList& aInParamList,
				                       	CLiwGenericParamList& aOutParamList,
				                       	TUint aCmdOptions)
				                       
	{
	TInt errcode = KErrNotSupported;
	TInt32 transactionId(-1);

    if( KLiwOptCancel & aCmdOptions )
		{
		GetTransactionIdL( aInParamList, transactionId, KCmdCancel);
		errcode = iMsgService->Cancel( transactionId );				
		if ( errcode == KErrNotFound )
			{
			AppendErrorMessageL( aCmdName, KTransactionID, KIncorrectValue, 2 );
			}
		}
	else
		{				
		AppendErrorMessageL( aCmdName, KNullDesC8, KErrMsgMissingLiwCancel, 2 );
		}		
	}
	
// ---------------------------------------------------------------------------
// Issues GetList request to MessagingService
// ---------------------------------------------------------------------------
//	
void CMessagingInterface::GetHeaderListL( const CLiwGenericParamList& aInParamList,
					                       CLiwGenericParamList& aOutParamList,
					                       TUint aCmdOptions,
					                       MLiwNotifyCallback* aCallback )
	{
	
	
	const TLiwGenericParam* param = NULL;
	
	TBool indexBaseInp = EFalse;
	
	TInt pos = 0;
	
	TMsvId folderId = KMsvGlobalInBoxIndexEntryId;//default is inbox
	
	param = aInParamList.FindFirst( pos, KContentType );
	
	if( !param )
		{
		if( aInParamList.Count() ) //changed from 1 to non zero
			{
			param = &aInParamList[0];//changed from 1 to 0 
			if( param->Name().Compare( KNullDesC8 ) )
				{
				AppendErrorMessageL( KCmdGetHeaderList, KContentType, KMissing, 1 );	
				}
			indexBaseInp = ETrue; //Indexed based parsing not name value based	
			}
		}
	
	if ( param && CheckInputTypeL( &param->Value(), ETrue, LIW::EVariantTypeDesC, KCmdGetHeaderList, KContentType, KTypeInvalid ) )
		{ 
		TPtrC value = param->Value().AsDes();
		if ( value.CompareF( KInbox ) == 0 )
			{
			folderId = KMsvGlobalInBoxIndexEntryId;
			}
		else
			{
			AppendErrorMessageL( KCmdGetHeaderList, KContentType, KIncorrectValue, 2 );
			}
		}
	else
		{
		AppendErrorMessageL( KCmdGetHeaderList, KContentType, KMissing, 1 );
		}

	CFilterParamInfo* filterParam = GetFilterParametersL( aInParamList, indexBaseInp );

	CleanupStack::PushL( filterParam );
			
	CMsvEntrySelection* entrySelection = NULL;
	
	CMsgCallbackBase* callback = NULL;

	    if ( aCallback && ( KLiwOptASyncronous & aCmdOptions ))
	        {
	        callback = CMsgCallbackHeader::NewL(iMsgService);
	        CleanupStack::PushL( callback );
	        callback->iPtrInParamList = &aInParamList;
	        callback->iPtrNotifyCallback = aCallback;
	        callback->iTransactionId = aCallback->GetTransactionID();

	        aOutParamList.AppendL(TLiwGenericParam( KTransactionID, 
	                                TLiwVariant( callback->iTransactionId )));      
	        }
	
	iMsgService->GetIdListL( filterParam, 
									folderId, 
									callback/*Callback*/, 
									entrySelection );
	
	if ( callback )
	{
	CleanupStack::Pop( callback );
	CleanupStack::PopAndDestroy(filterParam);
	}
	if(!callback)
	CleanupStack::Pop( filterParam );
		
	// Successfull completion
	// filterParam and entrySelection ownership passed to called function
	if(!callback)
	UpdateOutputAsIdListL( &aOutParamList, entrySelection, iMsgService, filterParam );
	}

	

// ---------------------------------------------------------------------------
// Issues request for new message notifications to MessagingService
// ---------------------------------------------------------------------------
//	
void CMessagingInterface::RequestNotificationL( const CLiwGenericParamList& aInParamList,
					                       CLiwGenericParamList& aOutParamList,
					                       TUint aCmdOptions,
					                       MLiwNotifyCallback* aCallback )
	{
	if ( ! (aCallback && ( KLiwOptASyncronous & aCmdOptions ) ) ) 
		{
		AppendErrorMessageL( KCmdRegNotification, KNullDesC8, KSyncNotSupported, 2 );
		}
		
	TNotificationType notificationType;
	
	GetNotificationTypeL( aInParamList, notificationType, KCmdRegNotification );

	CMsgCallbackBase* callback = NULL;
	callback = CMsgCallbackHeader::NewL(iMsgService);
	callback->iPtrInParamList = &aInParamList;
	callback->iPtrNotifyCallback = aCallback;
	callback->iTransactionId = aCallback->GetTransactionID();
	TInt errcode = iMsgService->RequestNotification( notificationType, callback );
	
	if ( errcode != KErrNone )
		{
		delete callback;
		User::Leave( errcode );
		}
		
	aOutParamList.AppendL(TLiwGenericParam( KTransactionID, 
						TLiwVariant( callback->iTransactionId )));		
	}


// ---------------------------------------------------------------------------
// Issues request for new message notifications to MessagingService
// ---------------------------------------------------------------------------
//	
void CMessagingInterface::CancelNotificationL( const CLiwGenericParamList& aInParamList,
					                       CLiwGenericParamList& /*aOutParamList*/,
					                       TUint aCmdOptions,
					                       MLiwNotifyCallback* aCallback )
	{
	LeaveIfAsynchronousL( aCmdOptions, aCallback, KCmdCancelNotification, KAsyncNotSupported );
	
	TNotificationType notificationType;
	GetNotificationTypeL( aInParamList, notificationType, KCmdCancelNotification );
	User::LeaveIfError( iMsgService->CancelNotification( notificationType ));
	}
	
// ---------------------------------------------------------------------------
// Issues request for delete message to MessagingService
// ---------------------------------------------------------------------------
//	
void CMessagingInterface::DeleteMessageL( const CLiwGenericParamList& aInParamList,
					                       CLiwGenericParamList& /*aOutParamList*/,
					                       TUint aCmdOptions,
					                       MLiwNotifyCallback* aCallback )
	{
	LeaveIfAsynchronousL( aCmdOptions, aCallback, KCmdDeleteMsg, KAsyncNotSupported );
	
	TMsvId messageId;

	GetMessageIdL( aInParamList, messageId , KCmdDeleteMsg);
	
	if ( messageId > 0 )
		{
		iMsgService->DeleteMessageL( messageId );
		}
	else
		{	
		AppendErrorMessageL( KCmdDeleteMsg, KMessageId, KIncorrectValue, 2 );
		}
	}

// ---------------------------------------------------------------------------
// Issues request for changing status of a message to MessagingService
// ---------------------------------------------------------------------------
//	
void CMessagingInterface::ChangeStatusL( const CLiwGenericParamList& aInParamList,
					                       CLiwGenericParamList& /*aOutParamList*/,
					                       TUint aCmdOptions,
					                       MLiwNotifyCallback* aCallback )
	{
	LeaveIfAsynchronousL( aCmdOptions, aCallback, KCmdChangeStatus, KAsyncNotSupported );
	TMsvId messageId;
	TMessageStatusFlag statusFlag;
	TBool flagValue;
	
    GetMessageIdL( aInParamList, messageId, KCmdChangeStatus );
	GetStatusFlagAndValueL( aInParamList, statusFlag, flagValue, KCmdChangeStatus );
	
	if ( messageId > 0 )
		{
		iMsgService->ChangeStatusL( messageId, statusFlag, flagValue );
		}
	else
		{	
		AppendErrorMessageL( KCmdChangeStatus, KMessageId, KIncorrectValue, 2 );
		}
	}
	
// ---------------------------------------------------------------------------
// Gets the message id 
// ---------------------------------------------------------------------------
//	
void CMessagingInterface::GetMessageIdL( const CLiwGenericParamList& aInParamList, 
										TMsvId& aMessageId,
										const TDesC8& aCmdName  )
	{
	TInt pos = 0;
	const TLiwGenericParam* param = aInParamList.FindFirst( pos, KMessageId );

	if(!param && aInParamList.Count() )
		{
		param = &aInParamList[0];
		
		if( param->Name().Compare( KNullDesC8 ) )
			{
			AppendErrorMessageL( aCmdName, KMessageId, KMissing, 1 );
			}
		}
		
	
	if ( param && CheckInputTypeL( &param->Value(), ETrue, LIW::EVariantTypeTInt32, aCmdName, KMessageId, KTypeInvalid  ) )
		{
		aMessageId = param->Value().AsTInt32();
		return;
		}	
	AppendErrorMessageL( aCmdName, KMessageId, KMissing, 1 );
	}
	
// ---------------------------------------------------------------------------
// Gets the Transaction id 
// ---------------------------------------------------------------------------
//	
void CMessagingInterface::GetTransactionIdL( const CLiwGenericParamList& aInParamList, 
											TInt32& aTransactionId,
											const TDesC8& aCmdName  )
	{ 
	TInt pos = 0;
	    
	const TLiwGenericParam* param = aInParamList.FindFirst( pos, 
															KTransactionID );
	if(!param && aInParamList.Count() )
		{
		param = &aInParamList[0];
		
		if( param->Name().Compare( KNullDesC8 ) )
			{
			AppendErrorMessageL( aCmdName, KTransactionID, KMissing, 1 );
			}
		}		
	
	if ( param && CheckInputTypeL( &param->Value(), ETrue, LIW::EVariantTypeTInt32, aCmdName, KTransactionID, KTypeInvalid ) )
		{
		aTransactionId = param->Value().AsTInt32();
		if( aTransactionId < 0 )
			{ 
			AppendErrorMessageL( aCmdName, KTransactionID, KIncorrectValue, 2 );
			}			
		return;
		}	
	AppendErrorMessageL( aCmdName, KTransactionID, KMissing, 1 );
	}
	
// ---------------------------------------------------------------------------
// Gets the status flag and its value
// ---------------------------------------------------------------------------
//
void CMessagingInterface::GetStatusFlagAndValueL( const CLiwGenericParamList&  aInParamList, 
													TMessageStatusFlag& aStatusFlag, 
													TBool& aFlagValue,
													const TDesC8& aCmdName  )
	{
	TInt pos = 0;

	const TLiwGenericParam* paramMandatory = aInParamList.FindFirst( pos, KMessageId );

	const TLiwGenericParam* param = NULL;
	
	pos = 0;
	if ( paramMandatory )
		param = aInParamList.FindFirst( pos, KStatus );
	else if( aInParamList.Count() > 1 )
		param = &aInParamList[1];
	
	if ( param && CheckInputTypeL( &param->Value(), ETrue, LIW::EVariantTypeDesC, aCmdName, KStatus, KTypeInvalid ) )
		{
		TPtrC value = param->Value().AsDes();
		aFlagValue = ETrue;
		if ( value.CompareF( KStatusFlagRead ) == 0 )
			{
			aStatusFlag = EUnread;
			aFlagValue = EFalse;
			}
		else if ( value.CompareF( KStatusFlagUnread ) == 0 )
			{
			aStatusFlag = EUnread;
			}
		else if ( value.CompareF( KStatusFlagReplied ) == 0 )
			{
			aStatusFlag = EReplied;
			}
		else if ( value.CompareF( KStatusFlagForward ) == 0 )
			{
			aStatusFlag = EForward;
			}
		else if ( value.CompareF( KStatusFlagDeleted ) == 0 )
			{
			aStatusFlag = EDelete;
			}
		else
			{
			AppendErrorMessageL( aCmdName, KStatus, KIncorrectValue, 2 );
			}
		return;	
		}
	AppendErrorMessageL( aCmdName, KStatus, KMissing, 1 );
	}
	
// ---------------------------------------------------------------------------
// Gets the notification type
// ---------------------------------------------------------------------------
//
void CMessagingInterface::GetNotificationTypeL( const CLiwGenericParamList& aInParamList, 
													TNotificationType& aNotificationType,
													const TDesC8& aCmdName  )
	{
	TInt pos = 0;
	const TLiwGenericParam* param = aInParamList.FindFirst( pos, KNotificationType );
	
	if(!param && aInParamList.Count() )
		{
		param = &aInParamList[0];
		if( param->Name().Compare( KNullDesC8 ) )
			{
			AppendErrorMessageL( aCmdName, KNotificationType, KMissing, 1 );	
			}
		}
	
	if ( param && CheckInputTypeL( &param->Value(), ETrue, LIW::EVariantTypeDesC, aCmdName, KNotificationType, KTypeInvalid) )
		{
		TPtrC notifType = param->Value().AsDes();
		if( notifType.CompareF( KNotificationNewMsg ) == 0 )
			{
			aNotificationType = ENewMessage;
			}
		else
			{
			AppendErrorMessageL( aCmdName, KNotificationType, KIncorrectValue, 2 );
			}
		}
	else
		{	
		AppendErrorMessageL( aCmdName, KNotificationType, KMissing, 1 );
		}		
	}
	
// ---------------------------------------------------------------------------
// Gets the param list for sending message form the inputparam list
// ---------------------------------------------------------------------------
//
CSendMessageParams* CMessagingInterface::GetSendParametersL( 
												const CLiwGenericParamList& aInParamList )
	{
	TInputValidator validator;
	CSendMessageParams* sendParams = CSendMessageParams::NewL();
	CleanupStack::PushL(sendParams);
	
	TInt pos = 0;
	TBool indexBaseInp = ETrue;
	
	const TLiwGenericParam* inMessageType = aInParamList.FindFirst( pos, KMtm );
	if ( inMessageType ) 
		{
		indexBaseInp = EFalse;
		}
	else
		{
		if( aInParamList.Count() )
			{
			inMessageType = &aInParamList[0];
			if( inMessageType->Name().Compare( KNullDesC8 ) )
				{
				AppendErrorMessageL( KCmdSendMessage, KMtm, KMissing, 1 );
				}
			}
		else
			{	
			AppendErrorMessageL( KCmdSendMessage, KMtm, KMissing, 1 );
			}			
		}

	CheckInputTypeL( &inMessageType->Value(), ETrue, LIW::EVariantTypeDesC, KCmdSendMessage, KMtm, KTypeInvalid ); 
		
	TPtrC type = inMessageType->Value().AsDes();
	if( sendParams->SetMessageTypeL( type ) != KErrNone )
		{
		AppendErrorMessageL( KCmdSendMessage, KMtm, KIncorrectValue, 2 );
		}

	const TLiwGenericParam* inTmpParam = NULL;

	// Read Recipient "To"
	if ( indexBaseInp ) 
		{
		if ( aInParamList.Count() > 1 )
			inTmpParam = &aInParamList[1];
		}
	else
		{
		pos = 0;
		inTmpParam = aInParamList.FindFirst( pos, KRecipientTo );
		}
	
	if ( inTmpParam && CheckInputTypeL( &inTmpParam->Value(), ETrue, LIW::EVariantTypeDesC, KCmdSendMessage, KRecipientTo, KTypeInvalid ))
		{
		TPtrC recipient = inTmpParam->Value().AsDes();
		if( validator.CheckValidNumberWithPlus( recipient ) )
			{
			sendParams->AddRecipientL(recipient, EMsvRecipientTo);
			inTmpParam = NULL;
			}
		else
			{
			AppendErrorMessageL( KCmdSendMessage, KRecipientTo, KIncorrectValue, 2 );
			}	
		}
	else
		{	
		AppendErrorMessageL( KCmdSendMessage, KRecipientTo, KMissing, 1 );
		}

	// Read BodyText
	if ( indexBaseInp ) 
		{
		if ( aInParamList.Count() > 2 )
			inTmpParam = &aInParamList[2];
		}
	else
		{
		pos = 0;
		inTmpParam = aInParamList.FindFirst( pos, KBodyText );
		}
		
	//this is an optional parameter so check for not null constraint, ignore this in case of NULL
	if ( inTmpParam && CheckInputTypeL( &inTmpParam->Value(), EFalse, LIW::EVariantTypeDesC, KCmdSendMessage, KBodyText, KTypeInvalid ) )
		{
		TPtrC bodytext = inTmpParam->Value().AsDes();
		sendParams->SetBodyTextL( bodytext );
		inTmpParam = NULL;
		}

	// Read Subject
	if ( indexBaseInp ) 
		{
		if ( aInParamList.Count() > 3 )
			inTmpParam = &aInParamList[3];
		}
	else
		{
		pos = 0;
		inTmpParam = aInParamList.FindFirst( pos, KSubject );
		}
		
	//this is an optional parameter so check for not null constraint, ignore this in case of NULL
	if ( inTmpParam && CheckInputTypeL( &inTmpParam->Value(), EFalse, LIW::EVariantTypeDesC, KCmdSendMessage, KSubject, KTypeInvalid ) )
		{
		TPtrC subject = inTmpParam->Value().AsDes();
		sendParams->SetSubjectL( subject );
		inTmpParam = NULL;
		}
	
	// Read Attachment
	if ( indexBaseInp ) 
		{
		if ( aInParamList.Count() > 4 )
			inTmpParam = &aInParamList[4];
		}
	else
		{
		pos = 0;
		inTmpParam = aInParamList.FindFirst( pos, KAttachmentName );
		}
		
	//this is an optional parameter so check for not null constraint, ignore this in case of NULL
	if ( inTmpParam && CheckInputTypeL( &inTmpParam->Value(), EFalse, LIW::EVariantTypeDesC, KCmdSendMessage, KAttachmentName, KTypeInvalid ) )
		{
		TBuf<KMaxFileName> attachmentfile;
		TBuf8<KMaxFileName> mimeType;
		
		if( ! validator.CheckDesSize(inTmpParam->Value().AsDes()) )
			{
			AppendErrorMessageL( KCmdSendMessage, KAttachmentName, KIncorrectValue, 2 );
			}
		
		attachmentfile.Copy( inTmpParam->Value().AsDes() );
		inTmpParam = NULL;
		
		if(attachmentfile.Length())
			{
			// Read Attachment Mime type
			if ( indexBaseInp ) 
				{
				if ( aInParamList.Count() > 5 )
					inTmpParam = &aInParamList[5];
				}
			else
				{
				pos = 0;
				inTmpParam = aInParamList.FindFirst( pos, KMimeType );
				}
				
			//this is an optional parameter so check for not null constraint, ignore this in case of NULL
			if ( inTmpParam && CheckInputTypeL( &inTmpParam->Value(), EFalse, LIW::EVariantTypeDesC, KCmdSendMessage, KMimeType, KTypeInvalid ) )
				{
				if( ! validator.CheckDesSize( inTmpParam->Value().AsDes() ) )
					{
					AppendErrorMessageL( KCmdSendMessage, KMimeType, KIncorrectValue, 2 );
					}
				mimeType.Copy( inTmpParam->Value().AsDes() );
				}

			inTmpParam = NULL;
			
			CMsvAttachment* attachment = CMsvAttachment::NewL( CMsvAttachment::EMsvFile );
			
			CleanupStack::PushL(attachment);
			
			attachment->SetAttachmentNameL( attachmentfile );
			
			if ( mimeType.Length() )
				attachment->SetMimeTypeL( mimeType );
			
			sendParams->AddAttachmentL( attachment );
			
			CleanupStack::Pop(attachment);
			}
		}
	
	const TLiwGenericParam* inMessageParam = NULL;

	if ( indexBaseInp ) 
		{
		if ( aInParamList.Count() > 6 )
			inMessageParam = &aInParamList[6];
		}
	else
		{
		pos = 0;
		inMessageParam = aInParamList.FindFirst( pos, KMessageParam );
		}
	
	//this is an optional parameter so check for not null constraint, ignore this in case of NULL
	if ( inMessageParam && CheckInputTypeL( &inMessageParam->Value(), EFalse, LIW::EVariantTypeMap, KCmdSendMessage, KMessageParam, KTypeInvalid ) ) 
		{
		const CLiwMap* inMap = inMessageParam->Value().AsMap();
		
		if(inMap)
			{
			
			TLiwVariant inParam;
			CleanupStack::PushL( TCleanupItem( TLiwVariant::VariantCleanup , &inParam) );
			//this is an optional parameter so check for not null constraint, ignore this in case of NULL
			if ( inMap->FindL( KTemplateId, inParam ) && CheckInputTypeL( &inParam, EFalse, LIW::EVariantTypeTInt32, KCmdSendMessage, KTemplateId, KTypeInvalid ) ) 
				{
				sendParams->SetTemplateId( (TMsvId)(inParam.AsTInt32()) );				
				}
			
			//this is an optional parameter so check for not null constraint, ignore this in case of NULL
			if ( inMap->FindL( KLaunchEditor, inParam ) && CheckInputTypeL( &inParam, EFalse, LIW::EVariantTypeTBool, KCmdSendMessage, KLaunchEditor, KTypeInvalid ) ) 
				{
				sendParams->SetLaunchEditor( inParam.AsTBool() );
				}
			
			//this is an optional parameter so check for not null constraint, ignore this in case of NULL
			if ( inMap->FindL( KRecipientTo, inParam ) && CheckInputTypeL( &inParam, EFalse, LIW::EVariantTypeList, KCmdSendMessage, KRecipientTo, KTypeInvalid ) ) 
				{
				CLiwList* obj = (CLiwList*)(inParam.AsList());

				
				for ( int index = 0; index < obj->Count(); index++ )
					{
					TLiwVariant element;
					CleanupStack::PushL( TCleanupItem( TLiwVariant::VariantCleanup , &element) );
					obj->AtL(index, element);
					
					if( CheckInputTypeL( &element, EFalse, LIW::EVariantTypeDesC, KCmdSendMessage, KRecipientToElement, KTypeInvalid ) ) 
						{
						if( validator.CheckValidNumberWithPlus( element.AsDes() ) )
							{
							sendParams->AddRecipientL( element.AsDes(), EMsvRecipientTo);
							}
						else
							{
							AppendErrorMessageL( KCmdSendMessage, KRecipientToElement, KIncorrectValue, 2 );
							}
						}
					CleanupStack::PopAndDestroy( &element );
					//element.Reset();	
					}
				}

			//this is an optional parameter so check for not null constraint, ignore this in case of NULL
			if ( inMap->FindL( KRecipientCc, inParam ) && CheckInputTypeL( &inParam, EFalse, LIW::EVariantTypeList, KCmdSendMessage, KRecipientCc, KTypeInvalid ) ) 
				{
				CLiwList* obj = (CLiwList*)(inParam.AsList());
				

				for ( int index = 0; index < obj->Count(); index++ )
					{
					TLiwVariant element;
					CleanupStack::PushL( TCleanupItem( TLiwVariant::VariantCleanup , &element) );
					obj->AtL(index, element);
					
					if( CheckInputTypeL( &element, EFalse, LIW::EVariantTypeDesC, KCmdSendMessage, KRecipientCcElement, KTypeInvalid ) ) 
						{
						if( validator.CheckValidNumberWithPlus( element.AsDes() ) )
							{
							sendParams->AddRecipientL( element.AsDes(), EMsvRecipientTo);
							}
						else
							{
							AppendErrorMessageL( KCmdSendMessage, KRecipientCcElement, KIncorrectValue, 2 );
							}
						}
					CleanupStack::PopAndDestroy( &element );
					//element.Reset();	
					}
				}
			
			//this is an optional parameter so check for not null constraint, ignore this in case of NULL
			if ( inMap->FindL( KRecipientBcc, inParam ) && CheckInputTypeL( &inParam, EFalse, LIW::EVariantTypeList, KCmdSendMessage, KRecipientBcc, KTypeInvalid ) ) 
				{
				CLiwList* obj = (CLiwList*)(inParam.AsList());
				

				for ( int index = 0; index < obj->Count(); index++ )
					{
					TLiwVariant element;
					CleanupStack::PushL( TCleanupItem( TLiwVariant::VariantCleanup , &element) );
					obj->AtL(index, element);
					
					if( CheckInputTypeL( &element, EFalse, LIW::EVariantTypeDesC, KCmdSendMessage, KRecipientBccElement, KTypeInvalid ) ) 
						{
						if( validator.CheckValidNumberWithPlus( element.AsDes() ) )
							{
							sendParams->AddRecipientL( element.AsDes(), EMsvRecipientTo);
							}
						else
							{
							AppendErrorMessageL( KCmdSendMessage, KRecipientBccElement, KIncorrectValue, 2 );
							}				
						}
					CleanupStack::PopAndDestroy( &element );
					//element.Reset();	
					}
				}
			
			//this is an optional parameter so check for not null constraint, ignore this in case of NULL
			if ( inMap->FindL( KAttachmentList, inParam ) && CheckInputTypeL( &inParam, EFalse, LIW::EVariantTypeList, KCmdSendMessage, KAttachmentList, KTypeInvalid ) ) 
				{
				CLiwList* obj = (CLiwList*)(inParam.AsList());
				
				if( obj && ( obj->Count() > 0 ) )
					{
					for ( int index = 0; index < obj->Count(); index++ )
						{
						TLiwVariant list;
						CleanupStack::PushL( TCleanupItem( TLiwVariant::VariantCleanup , &list) );
						if( obj->AtL(index, list) && CheckInputTypeL( &list, EFalse, LIW::EVariantTypeMap, KCmdSendMessage, KAttachmentListElement, KTypeInvalid ) ) 
							{
							CLiwMap* map = (CLiwMap*)(list.AsMap());
							
							TLiwVariant element;
							CleanupStack::PushL( TCleanupItem( TLiwVariant::VariantCleanup , &element) );
							TBuf<KMaxFileName> fileName;
							if ( map->FindL(KFileName, element) && CheckInputTypeL( &element, EFalse, LIW::EVariantTypeDesC, KCmdSendMessage, KFileName, KTypeInvalid ) ) 
								{
								if( ! validator.CheckDesSize( element.AsDes() ) )
									{
									AppendErrorMessageL( KCmdSendMessage, KFileName, KIncorrectValue, 2 );
									}
								fileName.Copy( element.AsDes() ); 
								element.Reset();
								}

							CMsvAttachment::TMsvAttachmentType fltype = CMsvAttachment::EMsvFile;
							if ( map->FindL(KAttachmentType, element) && CheckInputTypeL( &element, EFalse, LIW::EVariantTypeDesC, KCmdSendMessage, KAttachmentType, KTypeInvalid ) ) 
								{
								TPtrC fileType = element.AsDes();
								if ( fileType.CompareF( KAttachmentLinkedFile ) == 0 )
									fltype = CMsvAttachment::EMsvLinkedFile;
								if ( fileType.CompareF( KAttachmentFile ) != 0 )
									User::Leave( ErrCodeConversion(KErrNotSupported));
								element.Reset();
								}
							
							TBuf8<KMaxFileName> mimeType;
							//this is an optional parameter so check for not null constraint, ignore this in case of NULL
							if ( map->FindL(KMimeType, element) && CheckInputTypeL( &element, EFalse, LIW::EVariantTypeDesC, KCmdSendMessage, KMimeType, KTypeInvalid ) ) 
								{
								if( ! validator.CheckDesSize( element.AsDes() ) )
									{
									AppendErrorMessageL( KCmdSendMessage, KMimeType, KIncorrectValue, 2 );
									}
								mimeType.Copy( element.AsDes() ); 
								}
							CleanupStack::PopAndDestroy( &element );
							//element.Reset();	
								
							CMsvAttachment* attachment = CMsvAttachment::NewL(fltype);
							CleanupStack::PushL(attachment);
							attachment->SetAttachmentNameL( fileName );
							if ( mimeType.Length() )
								attachment->SetMimeTypeL( mimeType );
							
							sendParams->AddAttachmentL( attachment );
							
							CleanupStack::Pop(attachment);
							}
						CleanupStack::PopAndDestroy( &list );
						//list.Reset();
						}
					}
				}
			CleanupStack::PopAndDestroy( &inParam );
			//inParam.Reset();
			}
			
		}
		
	CleanupStack::Pop( sendParams );
	return sendParams;
	}
		
// ---------------------------------------------------------------------------
// Gives the sort type
// ---------------------------------------------------------------------------
//	
TMsvSorting CMessagingInterface::SortType( const TDesC& aSortField, const TDesC& aSortOrder )
	{
	TMsvSorting retValue = EMsvSortByNone;//this indicates mismatch in either the sortfield or sortorder
	
	if ( aSortOrder.CompareF( KSortAsc)== 0 )
		{
		if ( aSortField.CompareF( KSortByDate ) == 0 )
			retValue = EMsvSortByDate;	
		else if ( aSortField.CompareF( KSortBySize ) == 0 )
			retValue = EMsvSortBySize;		
		else if ( aSortField.CompareF( KSortBySender ) == 0 )
			retValue = EMsvSortByDetails;		
		else if ( aSortField.CompareF( KSortBySubject ) == 0 )
			retValue = EMsvSortByDescription;		
		else if ( aSortField.CompareF( KSortById ) == 0 )
			retValue = EMsvSortById;
		}
	else if ( aSortOrder.CompareF( KSortDec) == 0 )
		{
		if ( aSortField.CompareF( KSortByDate ) == 0 )
			retValue = EMsvSortByDateReverse;	
		else if ( aSortField.CompareF( KSortBySize ) == 0 )
			retValue = EMsvSortBySizeReverse;	
		else if ( aSortField.CompareF( KSortBySender ) == 0 )
			retValue = EMsvSortByDetailsReverse;	
		else if ( aSortField.CompareF( KSortBySubject ) == 0 )
			retValue = EMsvSortByDescriptionReverse;		
		else if ( aSortField.CompareF( KSortById ) == 0 )
			retValue = EMsvSortByIdReverse;		
		}
	
	return retValue;		
	}
	
// ---------------------------------------------------------------------------
// Gets the filter parameters and sorting option from  the inputparam list
// ---------------------------------------------------------------------------
//	
CFilterParamInfo* CMessagingInterface::GetFilterParametersL( 
											const CLiwGenericParamList& aInParamList, TBool aIndexBaseInp )
	{
	TInputValidator validator;
	TInt pos = 0 ;
	CFilterParamInfo* filterparam = CFilterParamInfo::NewL();
	CleanupStack::PushL( filterparam );

	const TLiwGenericParam* filter = NULL;
	
	if ( aIndexBaseInp )
		{
		if ( aInParamList.Count() > 1 )
			filter = &aInParamList[1];
		}
	else
		{
		pos = 0 ;
		filter = aInParamList.FindFirst( pos, KFilter );
		}

	//this is an optional parameter so check for not null constraint, ignore this in case of NULL
	if ( filter && CheckInputTypeL( &filter->Value(), EFalse, LIW::EVariantTypeMap, KCmdGetHeaderList, KFilter, KTypeInvalid ) )
		{
		const CLiwMap* inputMap = filter->Value().AsMap(); 
		
		if ( inputMap )
			{			
			// FromArray
			TLiwVariant inParam;
			CleanupStack::PushL( TCleanupItem( TLiwVariant::VariantCleanup , &inParam) );
			//this is an optional parameter so check for not null constraint, ignore this in case of NULL
			if ( inputMap->FindL( KSenderList, inParam ) && CheckInputTypeL( &inParam, EFalse, LIW::EVariantTypeList, KCmdGetHeaderList, KSenderList, KTypeInvalid ) ) 
				{
				CLiwList* obj = (CLiwList*)( inParam.AsList() );
				for ( int index = 0; index < obj->Count(); index++ )
					{
					TLiwVariant element;
					CleanupStack::PushL( TCleanupItem( TLiwVariant::VariantCleanup , &element) );
					if( obj->AtL(index, element) && CheckInputTypeL( &element, EFalse, LIW::EVariantTypeDesC, KCmdGetHeaderList, KSenderElement, KTypeInvalid ) )
						{
						TPtrC fromaddr = element.AsDes();
						filterparam->AddFromL(fromaddr);
						
						//This check needs to be relaxed
						/*if( validator.CheckValidNumberWithPlus( fromaddr ) )
							{
                            filterparam->AddFromL(fromaddr);														
							}
						else
							{
							AppendErrorMessageL( KCmdGetHeaderList, KSenderElement, KIncorrectValue, 2 );
							}	*/
						}
					CleanupStack::PopAndDestroy( &element );	
					//element.Reset();
					}
				}

			//this is an optional parameter so check for not null constraint, ignore this in case of NULL
			// Mtmarray
			if ( inputMap->FindL( KMtmList, inParam ) && CheckInputTypeL( &inParam, EFalse, LIW::EVariantTypeList, KCmdGetHeaderList, KMtmList, KTypeInvalid ) )
				{
				CLiwList* obj = (CLiwList*)( inParam.AsList() );
				

				
				for ( int index = 0; index < obj->Count(); index++ )
					{
					TLiwVariant element;
					CleanupStack::PushL( TCleanupItem( TLiwVariant::VariantCleanup , &element) );
					if( obj->AtL(index, element) && CheckInputTypeL( &element, EFalse, LIW::EVariantTypeDesC, KCmdGetHeaderList, KMtmElement, KTypeInvalid ) )
						{
						TPtrC mtm = element.AsDes();
						if( filterparam->AddMtmL(mtm) != KErrNone )
							{
							AppendErrorMessageL( KCmdGetHeaderList, KMtmElement, KIncorrectValue, 2 );
							}
						}
					CleanupStack::PopAndDestroy( &element );		
					//element.Reset();
					}
				}
				
			//this is an optional parameter so check for not null constraint, ignore this in case of NULL
			// Subject					
			if ( inputMap->FindL( KSubject, inParam ) && CheckInputTypeL( &inParam, EFalse, LIW::EVariantTypeDesC, KCmdGetHeaderList, KSubject, KTypeInvalid ) ) 
				{
				TPtrC obj = inParam.AsDes();
				filterparam->SetSubjectL(obj);
				}
			
			//this is an optional parameter so check for not null constraint, ignore this in case of NULL	
		 	//MessageId
			if ( inputMap->FindL( KMessageId, inParam ) && CheckInputTypeL( &inParam, EFalse, LIW::EVariantTypeTInt32, KCmdGetHeaderList, KMessageId, KTypeInvalid ) ) 
			 	{
				TInt32 messageid = (TInt32)inParam.AsTInt32();
		
				filterparam->SetMessageIdFilter( messageid );
			 	}
		 	
		 	//this is an optional parameter so check for not null constraint, ignore this in case of NULL
		 	//StartDate 
		 	TTime startDate = Time::NullTTime();
			if ( inputMap->FindL( KStartDate, inParam ) && CheckInputTypeL( &inParam, EFalse, LIW::EVariantTypeTTime, KCmdGetHeaderList, KStartDate, KTypeInvalid ) )
			 	{			 	
				startDate = inParam.AsTTime();
	
				filterparam->SetStartDateFilter( startDate );	
				}
				
			//this is an optional parameter so check for not null constraint, ignore this in case of NULL	
		 	//EndDate 
		 	TTime endDate = Time::NullTTime();
			if ( inputMap->FindL( KEndDate, inParam ) && CheckInputTypeL( &inParam, EFalse, LIW::EVariantTypeTTime, KCmdGetHeaderList, KEndDate, KTypeInvalid ) )
			 	{
			 	endDate = inParam.AsTTime();
	
				filterparam->SetEndDate( endDate );
				}

			if( ( startDate != Time::NullTTime() && endDate != Time::NullTTime() ) && 
					startDate > endDate )
				{
				AppendErrorMessageL( KCmdGetHeaderList, KStartDate, KDateMismatch, 2 );
				}
				
			CleanupStack::PopAndDestroy( &inParam );
			//inParam.Reset();
			}

		}

	//SortType
	const TLiwGenericParam* sortOrder = NULL;
	if ( aIndexBaseInp )
		{
		 if( aInParamList.Count() > 2 )
			sortOrder = &aInParamList[2];
		}
	else
		{
		pos = 0 ;
		sortOrder = aInParamList.FindFirst( pos, KSortOrder );
		}

	//this is an optional parameter so check for not null constraint, ignore this in case of NULL
	if ( sortOrder && CheckInputTypeL( &sortOrder->Value(), EFalse, LIW::EVariantTypeMap, KCmdGetHeaderList, KSortOrder, KTypeInvalid ) )
		{
		const CLiwMap* sortMap = sortOrder->Value().AsMap(); 
		if ( sortMap )
			{
			TLiwVariant sortParam;
			
			//this is an optional parameter so check for not null constraint, ignore this in case of NULL	
			if ( sortMap->FindL( KField, sortParam ) && CheckInputTypeL( &sortParam, EFalse, LIW::EVariantTypeDesC, KCmdGetHeaderList, KField, KTypeInvalid ) )
				{
				HBufC* sordField = sortParam.AsDes().AllocL();
				CleanupStack::PushL( sordField );
				
				//this is an optional parameter so check for not null constraint, ignore this in case of NULL		
				if ( sortMap->FindL( KOrder, sortParam ) && CheckInputTypeL( &sortParam, EFalse, LIW::EVariantTypeDesC, KCmdGetHeaderList, KOrder, KTypeInvalid ) )
					{
					TPtrC sortOrder = sortParam.AsDes();
					TMsvSorting sortCriterion = SortType( *sordField, sortOrder );
					if( sortCriterion == EMsvSortByNone )
						{
						sortParam.Reset(); 
						AppendErrorMessageL( KCmdGetHeaderList, KSortOrder, KIncorrectValue, 2 );
						}
					else
						filterparam->SetSortType( sortCriterion );
					}
				
				CleanupStack::PopAndDestroy( sordField );	
				}
			sortParam.Reset();					
			}
		}


		
	CleanupStack::Pop( filterparam ); 
	return filterparam;
	}
	
// ---------------------------------------------------------------------------
// Two-phase Constructor
// ---------------------------------------------------------------------------
//
CMsgCallbackHeader* CMsgCallbackHeader::NewL(CMessagingService* aMsgService)
	{
	CMsgCallbackHeader* self = new (ELeave) CMsgCallbackHeader(aMsgService);
	
	return self;
	}

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//	
CMsgCallbackHeader::~CMsgCallbackHeader()
	{
	}
	
// ---------------------------------------------------------------------------
// Constructor
// ---------------------------------------------------------------------------
//		
CMsgCallbackHeader::CMsgCallbackHeader(CMessagingService* aMsgService):iMsg(aMsgService)
	{
    }
    
// ---------------------------------------------------------------------------
// Gives the result of asynchronous SAPI
// ---------------------------------------------------------------------------
//
void CMsgCallbackHeader::NotifyResultL( TInt aErrCode, TAny* aResult )
	{
	CLiwGenericParamList* outParams = CLiwGenericParamList::NewL();

	CleanupStack::PushL( outParams );

	outParams->AppendL(TLiwGenericParam(KErrorCode, 
							TLiwVariant(ErrCodeConversion(aErrCode))));		

	if ( aErrCode == KErrNone && aResult )
		{
		UpdateOutputAsHeaderL( outParams, aResult );
		}
	
	TInt event = KLiwEventInProgress;
	
	if ( aErrCode == KErrCancel )
		{
		event = KLiwEventCanceled;
		}
	else if ( aErrCode != KErrNone )
		{
		event = KLiwEventStopped;
		}
	
	((MLiwNotifyCallback*)iPtrNotifyCallback)->HandleNotifyL( iTransactionId, 
													event, 
													*(outParams), 
													*((CLiwGenericParamList*)iPtrInParamList) ); 

	CleanupStack::PopAndDestroy( outParams );
	}

// ---------------------------------------------------------------------------
// Gives the result of getlist asynchronous SAPI
// ---------------------------------------------------------------------------
//	
void CMsgCallbackHeader::HandleGetlistL( TInt aErrCode, CMsvEntrySelection* aEntrySelection, CFilterParamInfo* aFilter )
    {
    CLiwGenericParamList* outParams = CLiwGenericParamList::NewL();

    CleanupStack::PushL( outParams );

    outParams->AppendL(TLiwGenericParam(KErrorCode, 
                            TLiwVariant(ErrCodeConversion(aErrCode)))); 
    
    if ( aErrCode==KErrNone )
        {
        CIterableIdList* iter = CIterableIdList::NewL( aEntrySelection, iMsg, aFilter );
        
        CleanupStack::PushL( iter );
        
        TLiwVariant listVal;
        
        listVal.Set( iter );
        
        outParams->AppendL( TLiwGenericParam( KReturnValue/*KMessageList*/, listVal ));
        
        CleanupStack::Pop( iter );
        
        listVal.Reset();
        
        iter->DecRef();
        }
    
    TInt event = KLiwEventCompleted;
    
    if ( aErrCode == KErrCancel )
        {
        event = KLiwEventCanceled;
        }
    else if ( aErrCode != KErrNone )
        {
        event = KLiwEventStopped;
        }
    
    ((MLiwNotifyCallback*)iPtrNotifyCallback)->HandleNotifyL( iTransactionId, 
                                                    event, 
                                                    *(outParams), 
                                                    *((CLiwGenericParamList*)iPtrInParamList) ); 

    CleanupStack::PopAndDestroy( outParams );
    }

// ---------------------------------------------------------------------------
// Two-phase Constructor
// ---------------------------------------------------------------------------
//
CMsgCallbackBase* CMsgCallbackInt::NewL()
	{
	return new (ELeave)	CMsgCallbackInt;
	}
	
// ---------------------------------------------------------------------------
//  Constructor
// ---------------------------------------------------------------------------
//	
CMsgCallbackInt::CMsgCallbackInt()
	{
	}
	
// ---------------------------------------------------------------------------
// Gives the result of asynchronous SAPI
// ---------------------------------------------------------------------------
//
void CMsgCallbackInt::NotifyResultL( TInt aErrCode, TAny* /*aResult*/ )
	{
	CLiwGenericParamList* outParams = CLiwGenericParamList::NewL();

	CleanupStack::PushL( outParams );

	outParams->AppendL(TLiwGenericParam(KErrorCode, 
							TLiwVariant(ErrCodeConversion(aErrCode))));		

	TInt event = KLiwEventCompleted;
	if ( aErrCode == KErrCancel )
		{
		event = KLiwEventCanceled;
		}
	else if ( aErrCode != KErrNone )
		{
		event = KLiwEventStopped;
		}
	
	((MLiwNotifyCallback*)iPtrNotifyCallback)->HandleNotifyL( iTransactionId, 
												 event, 
												 *(outParams), 
												 *((CLiwGenericParamList*)iPtrInParamList) ); 
											 
	CleanupStack::PopAndDestroy( outParams );
	}

void CMsgCallbackInt::HandleGetlistL( TInt aErrCode, CMsvEntrySelection* aEntrySelection, CFilterParamInfo* aFilter )
    {
    //Dummy Function
    }

// ---------------------------------------------------------------------------
// Updates the output for message header
// ---------------------------------------------------------------------------
//
void UpdateOutputAsHeaderL( CLiwGenericParamList* aOutParamList, TAny* aResult )
	{
	CMessageHeader* header = (CMessageHeader*)aResult;
	TLiwVariant newElement;
	if( GetLiwHeaderL( header, newElement ) )
		{
		aOutParamList->AppendL( TLiwGenericParam( KReturnValue/*KMessage*/, newElement ));
		}
	newElement.Reset();
	}
	
// ---------------------------------------------------------------------------
// Gets the message header
// ---------------------------------------------------------------------------
//
TBool GetLiwHeaderL( CMessageHeader* aHeader, TLiwVariant& aElement, 
												CMessagingService* aMsgService, 
												TBool aCustomMap )
	{
	if(aHeader)
		{
		CLiwMap* map = NULL;
		if ( aCustomMap )
			map = CLiwMessagingMap::NewL( aMsgService );
		else
			map = CLiwDefaultMap::NewL();

		CleanupClosePushL( *map );//CleanupStack::PushL(map);

		map->InsertL( KUnreadFlag, 	TLiwVariant( aHeader->UnreadFlag() ) );
		map->InsertL( KAttachFlag, 	TLiwVariant( aHeader->AttachFlag() ) );
		map->InsertL( KPriority, 	TLiwVariant( aHeader->Priority() ) );
		map->InsertL( KMessageId, 	TLiwVariant( aHeader->MessageId() ) );
		map->InsertL( KTime, 		TLiwVariant( aHeader->Time() ) );
		map->InsertL( KSender, 		TLiwVariant( aHeader->From() ) );
		map->InsertL( KSubject, 	TLiwVariant( aHeader->Subject() ) );
		map->InsertL( KMtm, 		TLiwVariant( aHeader->Mtm() ) );
		
		aElement.SetL( map );

		CleanupStack::PopAndDestroy(map);
		
		//map->DecRef();

		return ETrue;
		}
	return EFalse;
	}

// ---------------------------------------------------------------------------
// Updates output param list with the headerlist.
// aFilter ownership is passed
// ---------------------------------------------------------------------------
//
void UpdateOutputAsIdListL( CLiwGenericParamList* aOutParamList, 
										CMsvEntrySelection* aEntrySelection, 
										CMessagingService* aMsgService,
										CFilterParamInfo* aFilter )
	{
	CIterableIdList* iter = CIterableIdList::NewL( aEntrySelection, aMsgService, aFilter );
	CleanupStack::PushL( iter );
	
	TLiwVariant listVal;
	listVal.Set( iter );
	
	aOutParamList->AppendL( TLiwGenericParam( KReturnValue/*KMessageList*/, listVal ));
	
	CleanupStack::Pop( iter );
	listVal.Reset();
	iter->DecRef();
	}
	
// ---------------------------------------------------------------------------
// Updates the message details to input map
// ---------------------------------------------------------------------------
//
void UpdateMessageDetailToMapL( CLiwMap* aResultMap, CMessageDetailInfo* aMessageDetail )
	{
	if ( aResultMap )
		{
		aResultMap->InsertL( KMessageId, TLiwVariant( aMessageDetail->MessageId() ) );

		aResultMap->InsertL( KBodyText, TLiwVariant( aMessageDetail->BodyText() ) );
			
		// Update recipient list
		if ( aMessageDetail->RecipientArray() )
			{
			CLiwDefaultList* bccList = CLiwDefaultList::NewL();
			CleanupClosePushL( *bccList ); //CleanupStack::PushL( bccList );
			CLiwDefaultList* ccList = CLiwDefaultList::NewL();
			CleanupClosePushL( *ccList ); //CleanupStack::PushL( ccList );
			CLiwDefaultList* toList = CLiwDefaultList::NewL();
			CleanupClosePushL( *toList ); //CleanupStack::PushL( toList );


			for( TInt index = 0 ; index < aMessageDetail->RecipientArray()->Count() ;index++ )
				{
				switch ( aMessageDetail->RecipientArray()->Type( index ) )	
					{
		           	case EMsvRecipientTo :
							toList->AppendL(TLiwVariant( (*(aMessageDetail->RecipientArray()))[index] ) );
		                    break;
					
					case EMsvRecipientCc :
							ccList->AppendL(TLiwVariant( (*(aMessageDetail->RecipientArray()))[index] ) );
		                    break;

					case EMsvRecipientBcc :
							bccList->AppendL(TLiwVariant( (*(aMessageDetail->RecipientArray()))[index] ) );
		                    break;

					default :
		           			User::Leave( ErrCodeConversion(KErrGeneral) );
							break ; 
					}
				}
			
			if ( toList->Count() > 0 )
				{
				aResultMap->InsertL( KRecipientTo, TLiwVariant(toList) );
				}
			CleanupStack::PopAndDestroy( toList );
			//toList->DecRef();

			if ( ccList->Count() > 0 )
				{
				aResultMap->InsertL( KRecipientCc, TLiwVariant(ccList) );
				}
			CleanupStack::PopAndDestroy( ccList );
			//ccList->DecRef();

			if ( bccList->Count() > 0 )
				{
				aResultMap->InsertL( KRecipientBcc, TLiwVariant(bccList) );
				}
			CleanupStack::PopAndDestroy( bccList );
			//bccList->DecRef();
			}

	 	// Update attachment list
	   if ( aMessageDetail->AttachmentInfoArray() ) 
		    {
			CLiwDefaultList* mapList = CLiwDefaultList::NewL();
			CleanupClosePushL( *mapList ); //CleanupStack::PushL( mapList );
		    
			for ( TInt index = 0 ; index < aMessageDetail->AttachmentInfoArray()->Count(); index++ )
				{
				CLiwDefaultMap* map = CLiwDefaultMap::NewL();

				CleanupClosePushL( *map ); //CleanupStack::PushL( map );

				CMessageAttachInfo* attachinfo = aMessageDetail->AttachmentInfoArray()->At( index );
			    
				map->InsertL(KFileName, TLiwVariant( attachinfo->Name() ) );
				
				map->InsertL(KFileSize, TLiwVariant( attachinfo->Size() ) );
				
				map->InsertL(KMimeType, TLiwVariant( attachinfo->MimeType() ) );
				
				RFile tmpFile = attachinfo->FileHandle();
				
				CMsgFileBuffer* fileObj = CMsgFileBuffer::NewL( tmpFile );

				CleanupStack::PushL( fileObj );

				map->InsertL(KFileHandle, TLiwVariant( fileObj ) );

				CleanupStack::Pop( fileObj );
				fileObj->DecRef();

				mapList->AppendL( TLiwVariant(map) );
				
				CleanupStack::PopAndDestroy(map);
				
				//map->DecRef();
				}
			
			if ( mapList->Count() > 0 )
				{
				aResultMap->InsertL( KAttachmentList, TLiwVariant(mapList) );
				}
			
			CleanupStack::PopAndDestroy( mapList );
			
			//mapList->DecRef();
		    }
		}
	}
	
// ---------------------------------------------------------------------------
// Two-Phase constructor
// ---------------------------------------------------------------------------
//
CIterableIdList* CIterableIdList::NewL( CMsvEntrySelection* aList, 
													CMessagingService* aMsgService, 
													CFilterParamInfo* aFilter )
	{
	return new(ELeave) CIterableIdList( aList, aMsgService, aFilter );
	}
	
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CIterableIdList::~CIterableIdList()
	{
	if( iList )
		{
		iList->Reset();
		delete iList;
		}
	
	delete iFilter;	
	}
	
// ---------------------------------------------------------------------------
// Reset the list
// ---------------------------------------------------------------------------
//
void CIterableIdList::Reset()
	{
	if( iList )
		{
		iIndex = 0; //iList->Reset();
		}
	}

// ---------------------------------------------------------------------------
// Gets next element in list
// ---------------------------------------------------------------------------
//
TBool CIterableIdList::NextL(TLiwVariant& aNext)
	{
	TBool retValue = EFalse;
	if ( iList && iList->Count() > iIndex )
		{
		CMessageHeader* header = NULL;
		
		TRAPD( err, iMsgService->GetNextHeaderL( iFilter, iList, iIndex, NULL, header ));// Check for trap
		
		if ( ( err  == KErrNone ) && header )
			{
			CleanupStack::PushL( header );
			
			// Get object of the custom map
			if ( GetLiwHeaderL( header, aNext, iMsgService, ETrue ) )
				{
				retValue = ETrue;
				}
			
			CleanupStack::PopAndDestroy( header );
			}
		else
			{
			User::LeaveIfError( ErrCodeConversion(err));
			}	
		}
	return retValue;
	}


// ---------------------------------------------------------------------------
// Constructor
// ---------------------------------------------------------------------------
//
CIterableIdList::CIterableIdList(CMsvEntrySelection* aList, 
											CMessagingService* aMsgService,
											CFilterParamInfo* aFilter ):
	iList( aList ),
	iMsgService( aMsgService ),
	iFilter( aFilter )
	{
	}


//////////////////////////////////////
//Messaging Custom map Implementation
//////////////////////////////////////
CLiwMessagingMap* CLiwMessagingMap::NewL( CMessagingService* aMsgService )
    {
    CLiwGenericParamList* gl = CLiwGenericParamList::NewLC();
    CLiwMessagingMap* tempMap = new (ELeave) CLiwMessagingMap(gl, aMsgService);
    CleanupStack::Pop(gl); 
    return tempMap;
    }

void CLiwMessagingMap::InsertL(const TDesC8& aKey, const TLiwVariant& aValue)
    {
    Remove(aKey);
    TLiwGenericParam mp;
    mp.SetNameAndValueL(aKey, aValue);
    iMap->AppendL(mp);
    mp.Reset();
    }

TBool CLiwMessagingMap::FindL(const TDesC8& aKey, TLiwVariant& aValue) const
    {
    TInt pos = 0;
    const TLiwGenericParam* tempParam = iMap->FindFirst(pos, aKey);
    if (tempParam)
        {
        aValue.SetL(tempParam->Value());
        return ETrue;
        }
    else
    	{
    	// add for bodytext/recipient cc bcc to/attachlist
    	if( aKey.CompareF( KBodyText ) == 0 || 
    		aKey.CompareF( KRecipientTo ) == 0 || 
    		aKey.CompareF( KRecipientCc ) == 0 ||
    		aKey.CompareF( KRecipientBcc ) == 0 ||
    		aKey.CompareF( KAttachmentList ) == 0 )
    		{
    		pos = 0;
		    const TLiwGenericParam* messageIdParam = iMap->FindFirst( pos, KMessageId );
		    if ( messageIdParam && iMsgService  )
		    	{
		    	TMsvId messageId = messageIdParam->Value().AsTInt32();
		    	CMessageDetailInfo* messageDetail = NULL;
				TRAPD( err, iMsgService->GetMessageDetailL( messageId, NULL, messageDetail ));
				
				if ( err == KErrNone && messageDetail )
					{
					CleanupStack::PushL( messageDetail );
					
					UpdateMessageDetailToMapL( (CLiwMap*)this, messageDetail );
					
					CleanupStack::PopAndDestroy( messageDetail );
					
					pos = 0;
				    const TLiwGenericParam* detailParam = iMap->FindFirst(pos, aKey);
				    if ( detailParam )
				        {
				        aValue.SetL( detailParam->Value() );
				        return ETrue;
				        }
					}
				else
					{
					User::LeaveIfError( ErrCodeConversion(err) );
					}	
		    	}
    		}
    	}
    return EFalse;
    }

TInt CLiwMessagingMap::Count() const
    {
    return iMap->Count();
    }

TBool CLiwMessagingMap::AtL(TInt aIndex, TDes8& aKey) const
    {
    if(0 <= aIndex && aIndex < iMap->Count())
        {
        aKey = ((*iMap)[aIndex]).Name();
        return ETrue;   
        }
    else
        {
        return EFalse;  
        }
    }

void CLiwMessagingMap::Remove(const TDesC8& aKey)
    {
    iMap->Remove( aKey );
    }

CLiwMessagingMap::~CLiwMessagingMap()
    {
    delete iMap;
    }


//////////////////////////////////////
//File Buffer Implementation
//////////////////////////////////////
CMsgFileBuffer* CMsgFileBuffer::NewL(RFile& aFile)
	{
	return new(ELeave) CMsgFileBuffer(aFile);
	}

CMsgFileBuffer::~CMsgFileBuffer()
	{
	Release();
	}
	
CMsgFileBuffer::CMsgFileBuffer( RFile& aFile ):
			iFile( aFile )
	{
	
	}

RFile& CMsgFileBuffer::AsFile()
	{
	return iFile;
	}
	
TUint8* CMsgFileBuffer::Buf() const
	{
	return NULL;
	}
	
TInt CMsgFileBuffer::Len()
	{
	TInt size = 0;
	
	TInt retValue = iFile.Size( size );
	
	if ( retValue == KErrNone )
		{
		return size;
		}
	else
		{
		return retValue;
		}
	}
	
TInt CMsgFileBuffer::Read( TUint8* aPtr,TInt aLength )
	{
	TPtr8 temp(aPtr, aLength);

	TInt errCode = iFile.Read( temp, aLength );
	
	return errCode;
	}
	
TInt CMsgFileBuffer::Write(const TUint8 /*aPtr*/, TInt /*aLength*/)
	{
	return KLiwBufferReadOnly;
	}
	
void CMsgFileBuffer::Release()
	{
	iFile.Close();
	}
	
TInt CMsgFileBuffer::TypeID()
	{
	return KLiwBufferFile;
	}
	
TBool CMsgFileBuffer::operator==(CLiwBuffer& /*aBuffer*/)
	{
	return EFalse;
	}

// ---------------------------------------------------------------------------
// ErrCode Conversion
// ---------------------------------------------------------------------------
//
TInt32 ErrCodeConversion(TInt code)
	{
	 TInt32 err;
	switch (code)
		{
			case KErrCancel:
			case KErrNone:
							err= SErrNone;
							break;

			case KErrNotFound:
							err= SErrNotFound;
							break;

			case KErrNoMemory:
							err = SErrNoMemory;
							break;

			case KErrInUse:
							err = SErrServiceInUse;
							break;

			case KErrNotSupported:
							err = SErrServiceNotSupported;
							break;

			case KErrBadName:
							err = SErrBadArgumentType;
							break;
							
			case KErrArgument: 
							err = SErrInvalidServiceArgument;
							break;

			case KErrAlreadyExists: 
							err = SErrEntryExists;
							break;

			case SErrMissingArgument:
							err = SErrMissingArgument;
							break;
							
			default 		:
							err = SErrGeneralError;
							break;
		}
	
	    return err;
		
	}

 
TInputValidator::TInputValidator()
	{
	
	}

 		
TBool TInputValidator::CheckValidFile( const TDesC &aFileName )
	{
	if( aFileName.Length() <= KMaxFileName )
		{
		RFs fileSession;
		if( fileSession.Connect() == KErrNone )
			{
			if( fileSession.IsValidName( aFileName ) )
				{
				RFile tmpfile;
				if( tmpfile.Open( fileSession, aFileName, EFileRead ) == KErrNone )
					{
					tmpfile.Close();
					return ETrue;
					}
				}
			fileSession.Close();
			return EFalse;
			}	
		}
	return EFalse;	
	}
	
TBool TInputValidator::CheckDesSize( const TDesC &aDes )
	{
	if( aDes.Length() <= KMaxFileName )
		{
		return ETrue;
		}
	return EFalse;	
	}
		
TBool TInputValidator::CheckValidDate( const TTime &aTime )
	{
	TTime null = Time::NullTTime();
	TTime low = Time::MinTTime();
	TTime high = Time::MaxTTime();
	if( aTime == null || aTime < low || aTime > high )
		{
		return EFalse;
		}
	return ETrue;	
	}
	
TBool TInputValidator::CheckValidNumber( const TDesC &aDes )
	{
	if( aDes.Length() )
		{
		TLex parser( aDes );
		TChar character;
		while( (character = parser.Get()) !=0 )
			{
			if( !character.IsDigit() )
				{
				return EFalse;
				}
			}
		return ETrue;	
		}
	return EFalse;	
	}
 		
TBool TInputValidator::CheckValidNumberWithPlus( const TDesC &aDes )
	{
	if( aDes.Length() )
		{
		TLex parser( aDes );
		TChar character;
		character = parser.Get();
		if( !(character == '+') && !character.IsDigit() )//check for the first character
			{
			return EFalse;
			}
		while( (character = parser.Get()) !=0 )
			{
			if( !character.IsDigit() )
				{
				return EFalse;
				}
			}
		return ETrue;	
		}
	return EFalse;
	}
