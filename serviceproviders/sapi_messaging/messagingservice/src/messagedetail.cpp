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
* Description:  Implementation of class CMessageDetail
*
*/



#include <e32base.h>
#include <badesca.h>
#include <msvapi.h>

#include <CMsvAttachment.h>
#include <MMsvAttachmentManager.h>
#include <txtrich.h>
#include <MsvUids.h>
#include <MTCLREG.H>
#include <smsclnt.h>
#include <smuthdr.h>
#include <senduiconsts.h>
#include <cmsvrecipientlist.h>
#include <mmsclient.h>

#include "messageheader.h"
#include "messagedetail.h"

// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CMessageDetail* CMessageDetail::NewL( CMsvSession& aServerSession )
	{
	CMessageDetail* self = new (ELeave) CMessageDetail( aServerSession );
	return self;
	}
	
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CMessageDetail::~CMessageDetail()
	{
	delete iMessageDetail;
	}
	
// ---------------------------------------------------------------------------
// Constructor.
// ---------------------------------------------------------------------------
//
CMessageDetail::CMessageDetail( CMsvSession& aServerSession ):
				iServerSession( aServerSession )
				
	{
	}
	
// ---------------------------------------------------------------------------
// Gets the message details  
// ---------------------------------------------------------------------------
//
void CMessageDetail::GetMessageDetailL( TMsvId aMessageId, 
										CMessageDetailInfo*& aMessageDetail )
	{
	iMessageId = aMessageId;

	ProcessRequestL(); // Client can get the results by calling the functions
	aMessageDetail = iMessageDetail;
	iMessageDetail = NULL; 		
	}
	
// ---------------------------------------------------------------------------
// Extracts the message body and attachment information, if any.
// ---------------------------------------------------------------------------
//
void CMessageDetail::ProcessRequestL()
	{
	CMsvEntry * messageEntry = iServerSession.GetEntryL( iMessageId );
	CleanupStack::PushL(messageEntry);
	
	if ( messageEntry->Entry().iMtm != KSenduiMtmSmsUid && 
		messageEntry->Entry().iMtm != KSenduiMtmMmsUid )
		{
		User::Leave( KErrNotSupported );
		}
		
	iMessageDetail = CMessageDetailInfo::NewL();
	iMessageDetail->SetMessageId( iMessageId );
	
	CMsvStore * messageStore = messageEntry->ReadStoreL();
	CleanupStack::PushL( messageStore );
	
	
    // Attachment ......
    MMsvAttachmentManager& attachMgr = messageStore->AttachmentManagerL();
    
    TInt count = attachMgr.AttachmentCount();
    
    for ( TInt i=0;i<count;i++)
	    {
	    CMsvAttachment * attachment = attachMgr.GetAttachmentInfoL( i );
		CleanupStack::PushL( attachment );

		CMessageAttachInfo* element = CMessageAttachInfo::NewL();
		CleanupStack::PushL( element );

		element->SetFileHandle( attachMgr.GetAttachmentFileL( i ) );
		element->SetNameL( attachment->AttachmentName() );
		element->SetSize( attachment->Size() );
		
		HBufC* tempMime = HBufC::NewLC( attachment->MimeType().Length() );
		tempMime->Des().Copy( attachment->MimeType() );
		element->SetMimeTypeL( *tempMime );
		CleanupStack::PopAndDestroy( tempMime );
		
	    iMessageDetail->AddAttachmentInfoL( element );
		CleanupStack::Pop( element );
		CleanupStack::PopAndDestroy( attachment );
	    }

	// Bodytext
	if ( messageStore->HasBodyTextL() )
		{
		// build a CRichText object to read in message body
		CParaFormatLayer* paraFormatLayer = CParaFormatLayer::NewL();
		CleanupStack::PushL( paraFormatLayer );
		CCharFormatLayer* charFormatLayer = CCharFormatLayer::NewL();
		CleanupStack::PushL( charFormatLayer );
		CRichText* richText = CRichText::NewL( paraFormatLayer, charFormatLayer );
		CleanupStack::PushL(richText);

		// Get the body text.
		messageStore->RestoreBodyTextL( *richText );
		const TInt length = richText->DocumentLength();
		iMessageDetail->SetBodyTextL( richText->Read( 0, length ) );

		CleanupStack::PopAndDestroy( 3, paraFormatLayer );
		}
		
	// Sender / Reciever info
	if ( messageEntry->Entry().iMtm == KSenduiMtmSmsUid )
		{
		GetSmsSenderRecipientL();
		}
	else if ( messageEntry->Entry().iMtm == KSenduiMtmMmsUid )
		{
		GetMmsSenderRecipientL();
		}
		
	CleanupStack::PopAndDestroy( 2, messageEntry );
	}

// ---------------------------------------------------------------------------
// Gets the Sender Recipient info for SMS
// ---------------------------------------------------------------------------
//
void CMessageDetail::GetSmsSenderRecipientL()
	{
	CClientMtmRegistry* clientMtmReg = NULL;
	clientMtmReg = CClientMtmRegistry::NewL( iServerSession );
	CleanupStack::PushL( clientMtmReg ); 

	CSmsClientMtm* smsMtm = NULL;
	smsMtm = static_cast<CSmsClientMtm*>( clientMtmReg->NewMtmL( KSenduiMtmSmsUid ) );
	CleanupStack::PushL( smsMtm );
 	smsMtm->SwitchCurrentEntryL( iMessageId );
 	smsMtm->LoadMessageL();
 	const CMsvRecipientList &recipientList = smsMtm->AddresseeList();

 	TInt count = recipientList.Count();
 	for ( int pos = 0; pos < count; pos++ )
	 	{
	 	iMessageDetail->AddRecipientL( recipientList[pos], recipientList.Type(pos) ); 
	 	}
	
	const CSmsHeader& smsHeader = smsMtm->SmsHeader();
	iMessageDetail->SetFromL( smsMtm->Entry().Entry().iDetails );

 	CleanupStack::PopAndDestroy( smsMtm );
	CleanupStack::PopAndDestroy( clientMtmReg );
	}

// ---------------------------------------------------------------------------
// Gets the Sender Recipient info for MMS
// ---------------------------------------------------------------------------
//
void CMessageDetail::GetMmsSenderRecipientL()
	{
	CClientMtmRegistry* clientMtmReg = NULL;
	clientMtmReg = CClientMtmRegistry::NewL( iServerSession );
	CleanupStack::PushL( clientMtmReg );

	CMmsClientMtm* mmsMtm = NULL;
	mmsMtm = static_cast<CMmsClientMtm*>( clientMtmReg->NewMtmL( KUidMsgTypeMultimedia ) );
	CleanupStack::PushL( mmsMtm );
 	mmsMtm->SwitchCurrentEntryL( iMessageId );
 	mmsMtm->LoadMessageL();
 	const CMsvRecipientList &recipientList = mmsMtm->AddresseeList();

  	TInt count = recipientList.Count();
	for ( int pos = 0; pos < count; pos++ )
	 	{
	 	iMessageDetail->AddRecipientL( recipientList[pos], recipientList.Type(pos) ); 
	 	}
	 	
 	iMessageDetail->SetFromL( mmsMtm->Sender() );
 	
 	CleanupStack::PopAndDestroy( mmsMtm );
	CleanupStack::PopAndDestroy( clientMtmReg );
	}
	
