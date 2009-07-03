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


#include <msvids.h>

#include "messageheader.h"
#include "messagenotify.h"

#ifdef __WINS__
const TMsvId KObservedFolderId = KMsvDraftEntryId;
#else
const TMsvId KObservedFolderId =  KMsvGlobalInBoxIndexEntryId;
#endif


// ---------------------------------------------------------------------------
// two-phased constructor
// ---------------------------------------------------------------------------
CMessageObserver* CMessageObserver::NewL( CMsvSession* aSession, 
											CMsgCallbackBase* aNotifyCallback )
	{
	return new(ELeave) CMessageObserver( aSession, aNotifyCallback );
	}
	
// ---------------------------------------------------------------------------
// destructor
// ---------------------------------------------------------------------------
CMessageObserver::~CMessageObserver()
	{
	delete iNotifyCallback;
	}

// ---------------------------------------------------------------------------
// default constructor
// ---------------------------------------------------------------------------
CMessageObserver::CMessageObserver( CMsvSession* aSession, 
									CMsgCallbackBase* aNotifyCallback ) :
					iServerSession( aSession ),
					iNotifyCallback( aNotifyCallback ),
					iNewMessageId( -1 )
	{
		
	}


// ---------------------------------------------------------------------------
// CMessageObserver::HandleSessionEventL
// Indicates the event of arrival of new message.
// ---------------------------------------------------------------------------
void CMessageObserver::HandleSessionEventL( TMsvSessionEvent aEvent, 
											TAny* aArg1, 
											TAny* aArg2, 
											TAny* /*aArg3*/ )
	{
		//if there is a callback request registered
		if ( iNotifyCallback )
			{
			switch ( aEvent )
				{
				// if there is a new entry created	
				case EMsvEntriesCreated:
					{
					//aArg2 specifies the parent ID of the entry
					// entry is created in observed folder
					if ( aArg2 && *(static_cast<TMsvId*> (aArg2)) == KObservedFolderId )
						{
						CMsvEntrySelection* entries = static_cast<CMsvEntrySelection*>( aArg1 );
						//one or more new entries created
						if ( entries->Count() > 0 )
							{
							// get the message ID of the first entry 
							iNewMessageId = entries->At(0);
							}
						}
					}
					break; 
				
				// one or more index entries are changed
				case EMsvEntriesChanged:
					{
					//change in index entry in the observed folder
					if ( aArg2 && *(static_cast<TMsvId*>(aArg2)) == KObservedFolderId )
						{
						CMsvEntrySelection* entries = static_cast<CMsvEntrySelection*>( aArg1 );
						if( entries->Count() > 0 && iNewMessageId == entries->At(0) )
							{
							CMessageHeader* newEntryHeader;
							// set the message header fields
							newEntryHeader = MessageHeaderL( iNewMessageId );
							if( newEntryHeader )
								{
								CleanupStack::PushL( newEntryHeader );
								//notify new header entry created
								iNotifyCallback->NotifyResultL( KErrNone, (TAny*)newEntryHeader );
								CleanupStack::PopAndDestroy(newEntryHeader);
								iNewMessageId = -1;
								}
							}
						}
					}
					break;
				
				default: break;
			}
		}
	}
	
// ---------------------------------------------------------------------------
// CMessageObserver::SetSession
// sets the iServersession member variable with a message server session
// ---------------------------------------------------------------------------
void CMessageObserver::SetSession( CMsvSession* aSession )
	{ 
	iServerSession = aSession; 
	}
		
// ---------------------------------------------------------------------------
// CMessageObserver::SetCallbackL
// registers a new callback request
// returns the old callback request
// ---------------------------------------------------------------------------
CMsgCallbackBase* CMessageObserver::SetCallback( CMsgCallbackBase* aCallback ) 
	{ 
	CMsgCallbackBase* oldCallback = iNotifyCallback;
	// get the new callback request
	iNotifyCallback = aCallback; 
	return oldCallback;
	}
	
// ---------------------------------------------------------------------------
// Checks if Notification is activated
// return True if notification request is active.
// ---------------------------------------------------------------------------
TBool CMessageObserver::IsActive()
	{
	if ( iNotifyCallback )
		return ETrue;
	
	return EFalse;
	}


// ---------------------------------------------------------------------------
// CMessageObserver::GetMessageHeaderL
// sets the header fields of a message
// returns an header object.
// ---------------------------------------------------------------------------
CMessageHeader* CMessageObserver::MessageHeaderL( TMsvId aMessageId )
	{
	TMsvEntry newEntry;
	TMsvId serviceId;

	//gets index of the specified message ID
	if( iServerSession->GetEntry( aMessageId, serviceId, newEntry ) == KErrNone )
		{
		CMessageHeader* newEntryHeader = CMessageHeader::NewL();
		CleanupStack::PushL( newEntryHeader );
		
		newEntryHeader->SetMtmId( newEntry.iMtm );
		newEntryHeader->SetTime( newEntry.iDate );
		newEntryHeader->SetMessageId( aMessageId );
		newEntryHeader->SetFromL( newEntry.iDetails );
		newEntryHeader->SetSubjectL( newEntry.iDescription );
		newEntryHeader->SetAttachFlag( newEntry.Attachment() );
		newEntryHeader->SetPriorityFlag( newEntry.Priority() );
		newEntryHeader->SetUnreadFlag( newEntry.Unread() );

		CleanupStack::Pop(newEntryHeader); 

		return newEntryHeader;
		}
	
	return NULL;
	}
