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



#include <calchangecallback.h>
#include <calsession.h>


#include "Calendarheader.h"
#include "Calendarnotify.h"
#include "asyncreqobserver.h"


// ---------------------------------------------------------------------------
// two-phased constructor
// ---------------------------------------------------------------------------
CCalendarObserver* CCalendarObserver::NewL( CCalendarSessionInfo* aSessionInfo,
												CCalendarFilter* aFilter,
												CAsyncRequestObserver* aAsyncRequestObserver,
												MCalCallbackBase* aNotifyCallback )
	{
	CCalendarObserver* self = new(ELeave) CCalendarObserver( aSessionInfo, aAsyncRequestObserver, aNotifyCallback );
	CleanupStack::PushL( self );
	self->ConstructL( aFilter );
	CleanupStack::Pop( self );
	return self;
	}
	
// ---------------------------------------------------------------------------
// destructor
// ---------------------------------------------------------------------------
CCalendarObserver::~CCalendarObserver()
	{
	delete iFilter;
	
	if ( iSession )
		{
		iSession->StopChangeNotification();
		delete iSession;
		}
	}

// ---------------------------------------------------------------------------
// default constructor
// ---------------------------------------------------------------------------
CCalendarObserver::CCalendarObserver( CCalendarSessionInfo* aSessionInfo, 
										CAsyncRequestObserver* aAsyncRequestObserver,
										MCalCallbackBase* aNotifyCallback ) :
//						CActive( EPriorityStandard ),
						iSessionInfo( aSessionInfo ),
						iNotifyCallback( aNotifyCallback ),
						iAsyncRequestObserver( aAsyncRequestObserver ),
						iIsInProgress(EFalse)
	{
	CActiveScheduler::Add( this ); 
	}

// ---------------------------------------------------------------------------
// second phase constructor
// ---------------------------------------------------------------------------
void CCalendarObserver::ConstructL( CCalendarFilter* aFilter )
	{
	iFilter = CCalendarFilter::NewL();
	*iFilter = *aFilter;
	}

// ---------------------------------------------------------------------------
// Initiates the Notification process
// ---------------------------------------------------------------------------
void CCalendarObserver::StartChangeNotificationL()
	{
	iSession = CCalSession::NewL();
	iSession->OpenL( iSessionInfo->Calendar() );

	TBool includeUndateToDo = ( iFilter->Filter() & EFlagUnDateToDo );

	CalCommon::TCalTimeRange range =  iFilter->TimeRange();

	if( range.EndTime().TimeLocalL() != Time::NullTTime() && 
		range.StartTime().TimeLocalL() != Time::NullTTime() )
		{
		if( range.EndTime().TimeLocalL() < range.StartTime().TimeLocalL() )
			User::Leave( KErrArgument );
		}

	// Create notification filter object specifying that notification for all entry types is required
	CCalChangeNotificationFilter* filter = CCalChangeNotificationFilter::NewL( MCalChangeCallBack2::EChangeEntryAll, 
													includeUndateToDo, 
													iFilter->TimeRange() );
	iSession->StartChangeNotification( *this, *filter );
	delete filter;
	ActivateRequest( KErrNone );
	}


// ---------------------------------------------------------------------------
// MCalChangeCallBack2::CalChangeNotification
// Indicates the event of arrival of change in calendar.
// ---------------------------------------------------------------------------
void CCalendarObserver::CalChangeNotification(RArray< TCalChangeEntry > &aChangeItems)
	{
	iIsInProgress = ETrue;
	if ( iFilter->Filter() & EFilterLUid )
		{
		RArray< TCalChangeEntry > filteredItems;
		TInt count = aChangeItems.Count();
		TInt uidCount = iFilter->LocalUidList().Count();
			
		for ( TInt index = 0; index < count; index++ )
			{
			for ( TInt i = 0; i < uidCount; i++ )
				{
				// Filter only those entries having local uids specified
				if ( aChangeItems[index].iEntryId ==  iFilter->LocalUidList()[i] )
					{
					filteredItems.Append( aChangeItems[index] );
					break;
					}
				}
			}
		// Notify the user of the changed entries
		TRAPD(err, iNotifyCallback->NotifyResultL( KErrNone, (TAny*)(&filteredItems) ));
		filteredItems.Reset();
		}
	else
		{
		TRAPD(err, iNotifyCallback->NotifyResultL( KErrNone, (TAny*)(&aChangeItems) ));
		}
	iIsInProgress = EFalse;	
	}		
	
// ---------------------------------------------------------------------------
// Inherited from CActive class 
// ---------------------------------------------------------------------------
//
void CCalendarObserver::DoCancel()
	{
	TRequestStatus* temp = &iStatus;
	User::RequestComplete( temp, KErrCancel );
	// Stop the notificaton operation
	iSession->StopChangeNotification();
	iAsyncRequestObserver->RequestComplete( iNotifyCallback->iTransactionId );
	TRAPD( err, iNotifyCallback->NotifyResultL( KErrCancel, NULL ));
	}

// ---------------------------------------------------------------------------
// Inherited from CActive class 
// ---------------------------------------------------------------------------
//
void CCalendarObserver::RunL()
	{

	}
	
// ---------------------------------------------------------------------------
// Activates the asynchronous request
// ---------------------------------------------------------------------------
//
void CCalendarObserver::ActivateRequest( TInt /*aReason*/ )
	{
	iStatus = KRequestPending;
	SetActive();
	}

TBool CCalendarObserver::IsInProgress()
	{
	return iIsInProgress;
	}
