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
* Description:  Interface to messaging provider
*
*/


#include <e32base.h>
#include <msvstd.h>
#include <msvapi.h>
#include <msvids.h>
#include <senduiconsts.h>

#include "messageheader.h"
#include "messagingservice.h"
#include "messagenotify.h"
#include "sendmessage.h"
#include "accessfolder.h"
#include "messagedetail.h"
#include "changestatus.h"


#ifdef __WINSCW__ 
	#define KFolderId KMsvDraftEntryId;
#else
	#define KFolderId KMsvGlobalInBoxIndexEntryId;
#endif


// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
EXPORT_C CMessagingService* CMessagingService::NewL()
	{
	CMessagingService* self = new (ELeave) CMessagingService;
	CleanupStack::PushL( self );
	self->ConstructL();
	CleanupStack::Pop( self );
	return self;
	}
	
// ---------------------------------------------------------------------------
// Destructor.
// ---------------------------------------------------------------------------
//
CMessagingService::~CMessagingService()
	{
	DeleteAsyncObjects();//deletes all Asychronous objects
	iAsyncObjArray.Reset();
	delete iMsgServerSession;
	delete iSessionObserver;			
	}

// ---------------------------------------------------------------------------
// Constructor.
// ---------------------------------------------------------------------------
//
CMessagingService::CMessagingService()
	{
	}

// ---------------------------------------------------------------------------
// Constructor.
// ---------------------------------------------------------------------------
//
void CMessagingService::ConstructL()
	{
	iSessionObserver = CMessageObserver::NewL();
	
	iMsgServerSession = CMsvSession::OpenSyncL( *iSessionObserver );
	
	((CMessageObserver*)iSessionObserver)->SetSession( iMsgServerSession );
	}

// ---------------------------------------------------------------------------
// Sends Message 
// ---------------------------------------------------------------------------
//
EXPORT_C void CMessagingService::SendMessageL( CSendMessageParams* aMessageParam, 
												CMsgCallbackBase* aCallback )
	{
	CMessageDetailInfo* 	templateDetail = NULL;

	if ( aMessageParam->TemplateId() > 0 )
		{
		CMessageDetail* detailObj = NULL;
		
		CMsvEntry * messageEntry = iMsgServerSession->GetEntryL( aMessageParam->TemplateId() );
		
	    CleanupStack::PushL(messageEntry);
		
	    if ( aMessageParam->MessageType() == KSenduiMtmSmsUid && 
	            messageEntry->Entry().iMtm == KSenduiMtmMmsUid )
            {
            User::Leave( KErrNotSupported );
            }
				
	    CleanupStack::PopAndDestroy(messageEntry);
		
		detailObj = CMessageDetail::NewL( *iMsgServerSession );
		
		CleanupStack::PushL( detailObj );
		
		detailObj->GetMessageDetailL( aMessageParam->TemplateId(), templateDetail );
										
		CleanupStack::PopAndDestroy( detailObj );
		}
	else if ( aMessageParam->TemplateId() < 0 )
		{
		User::Leave( KErrNotSupported );
		}
			

	CSendMessage* sendMessageObj = CSendMessage::NewL( *iMsgServerSession );

	CleanupStack::PushL( sendMessageObj );
	
	// aCallback, templateDetail ownership passes to CSendMessage
	sendMessageObj->SetInputParamsL( aMessageParam, templateDetail, aCallback, this );

	if ( aCallback )
		{
		AddAsyncObjL( aCallback->iTransactionId, sendMessageObj );
		}

	sendMessageObj->SendMessageL();
		
	CleanupStack::Pop( sendMessageObj );

	if ( !aCallback )
		delete sendMessageObj;
	}

// ---------------------------------------------------------------------------
// Deletes Message 
// ---------------------------------------------------------------------------
//
EXPORT_C void CMessagingService::DeleteMessageL( const TMsvId aMessageId,
					                       			CMsgCallbackBase* /*aCallback*/ )
	{
	CMessageChangeStatus* obj = NULL;

	obj = CMessageChangeStatus::NewL( *iMsgServerSession );

	CleanupStack::PushL( obj );
	
	obj->DeleteMessageL( aMessageId );

	CleanupStack::PopAndDestroy( obj );
	}

// ---------------------------------------------------------------------------
// Chages status of message entry
// ---------------------------------------------------------------------------
//
EXPORT_C void CMessagingService::ChangeStatusL( const TMsvId aMessageId,
												const TMessageStatusFlag aStatusFlag,
												const TBool  aFlagValue,
					                			CMsgCallbackBase* /*aCallback*/ )
	{
	CMessageChangeStatus* obj = CMessageChangeStatus::NewL( *iMsgServerSession );

	CleanupStack::PushL( obj );
	
	obj->ChangeStatusL( aMessageId, aStatusFlag, aFlagValue );

	CleanupStack::PopAndDestroy( obj );
	}

// ---------------------------------------------------------------------------
// Gives notification for new messages
// ---------------------------------------------------------------------------
//
EXPORT_C TInt CMessagingService::RequestNotification( const TNotificationType /*aNotification*/,
														CMsgCallbackBase* aCallback )
	{
	// Only one object can get the new message notification
	if( ( (CMessageObserver*)iSessionObserver )->IsActive() )
		return KErrAlreadyExists;
	
	CMsgCallbackBase* oldCallback = iSessionObserver->SetCallback( aCallback );
	
	delete oldCallback;
	
	return KErrNone;	
	}

// ---------------------------------------------------------------------------
// Cancels notification
// ---------------------------------------------------------------------------
//
EXPORT_C TInt CMessagingService::CancelNotification( const TNotificationType /*aNotification*/, 
														CMsgCallbackBase* /*aCallback*/ )
	{
	CMsgCallbackBase* oldCallback = iSessionObserver->SetCallback( NULL );

	delete oldCallback;
	
	return KErrNone;	
	}

// ---------------------------------------------------------------------------
// Gives a sorted list of message Ids 
// ---------------------------------------------------------------------------
//
EXPORT_C void CMessagingService::GetIdListL( CFilterParamInfo* aFilterParams,
											TMsvId /*aFolderId*/,
									        CMsgCallbackBase* 	aCallback,
									        CMsvEntrySelection*& aEntrySelection )
	{
	// Hard coding for Inbox/Draft
	// Folder Id can be passed as input parameter, to support access any folder
	TMsvId 	folderId = KFolderId;
	
	CMessagingAccessFolder* obj = CMessagingAccessFolder::NewL( *iMsgServerSession );
	
	CleanupStack::PushL( obj );
	
	obj->SetInputParamsL(aCallback,this);
	
	if ( aCallback )
	{
	AddAsyncObjL( aCallback->iTransactionId,obj);
	}
	
	obj->GetIdListL( folderId, aFilterParams, aEntrySelection );
	
	CleanupStack::Pop( obj );
	
	if ( !aCallback )
	    delete obj;
	}

EXPORT_C void CMessagingService::GetNextHeaderL( CFilterParamInfo* aFilterParams,
													CMsvEntrySelection* aEntrySelection,
													TInt& aIndex, 
									        		CMsgCallbackBase* 	/*aCallback*/,
									        		CMessageHeader*& aHeader )
	{
	CMessagingAccessFolder* obj = CMessagingAccessFolder::NewL( *iMsgServerSession );
	
	CleanupStack::PushL( obj );
	
	obj->GetNextHeaderL( aFilterParams, aEntrySelection, aIndex, aHeader );
	
	CleanupStack::PopAndDestroy( obj );
	}

// ---------------------------------------------------------------------------
// Gives details of the message 
// ---------------------------------------------------------------------------
//
EXPORT_C void CMessagingService::GetMessageDetailL( const TMsvId aMessageId, 
													CMsgCallbackBase* /*aCallback*/, 
													CMessageDetailInfo*& aResult )
	{
	CMessageDetail* obj = CMessageDetail::NewL( *iMsgServerSession );
	
	CleanupStack::PushL( obj );
	
	obj->GetMessageDetailL( aMessageId, aResult );
									
	CleanupStack::PopAndDestroy( obj );
	}
	
// ---------------------------------------------------------------------------
// Adds asynchronous request object
// ---------------------------------------------------------------------------
//
void CMessagingService::AddAsyncObjL( const TInt32 aTransactionId, CActive* aAsyncObj )
	{
	TAsyncRequestInfo asyncRequestInfo;
	asyncRequestInfo.iTransactionId = aTransactionId;
	asyncRequestInfo.iAsyncObj = aAsyncObj;
	User::LeaveIfError( iAsyncObjArray.Append( asyncRequestInfo ) );
	}

// ---------------------------------------------------------------------------
// Deletes all the asynchronous request objects
// ---------------------------------------------------------------------------
//
void CMessagingService::DeleteAsyncObjects()
	{
	TInt pos = iAsyncObjArray.Count() - 1;
	TAsyncRequestInfo obj;
	for ( ; pos >= 0; pos-- )
		{
		obj = iAsyncObjArray[pos];
		(obj.iAsyncObj)->Cancel();
		delete obj.iAsyncObj;
		}
	}

	
// ---------------------------------------------------------------------------
// Cancels asynchronous request
// ---------------------------------------------------------------------------
//
EXPORT_C TInt CMessagingService::Cancel( const TInt32 aTransactionId )
	{
	TInt pos = iAsyncObjArray.Count() - 1;
	TAsyncRequestInfo obj;
	for ( ; pos >= 0; pos-- )
		{
		obj = iAsyncObjArray[pos];
		if( obj.iTransactionId == aTransactionId )
			{
			obj.iAsyncObj->Cancel();
			delete obj.iAsyncObj;
			return KErrNone;
			}
		}
	return KErrNotFound;
	}


// ---------------------------------------------------------------------------
// Notifies Messaging service about the completeion of the request
// ---------------------------------------------------------------------------
//
void CMessagingService::RequestComplete( const TInt32 aTransactionId )
	{
	TInt pos = iAsyncObjArray.Count() - 1;
	TAsyncRequestInfo obj;
	for ( ; pos >= 0; pos-- )
		{
		obj = iAsyncObjArray[pos];
		if( obj.iTransactionId == aTransactionId )
			{
			iAsyncObjArray.Remove(pos);
			iAsyncObjArray.Compress();
			return;
			}
		}
	}

