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


#include <caliterator.h>
#include <calentryview.h>
#include <calinstanceview.h>
#include <calinstance.h>

#include "calendarheader.h"
#include "calendarconstants.h"
#include "asyncreqobserver.h"
#include "calendardeleteentry.h"

void CleanupCCalEntryArray(TAny* aPointer)
	{
	RPointerArray<CCalEntry>* calEntryArray = static_cast<RPointerArray<CCalEntry>*>(aPointer); 
	if ( calEntryArray )
		{
		calEntryArray->ResetAndDestroy();
		}
	}

void CleanupCCalInstanceArray(TAny* aPointer)
	{
	RPointerArray<CCalInstance>* calInstanceArray = static_cast<RPointerArray<CCalInstance>*>(aPointer); 
	if ( calInstanceArray )
		{
		calInstanceArray->ResetAndDestroy();
		}
	}

// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CCalendarDeleteEntry* CCalendarDeleteEntry::NewL( CCalendarSessionInfo* aSessionInfo, 
													CCalendarFilter* aFilter,
													CAsyncRequestObserver* aAsyncRequestObserver,
													MCalCallbackBase* aNotifyCallback )
	{
	CCalendarDeleteEntry* self = new (ELeave) CCalendarDeleteEntry( aSessionInfo, aAsyncRequestObserver, aNotifyCallback );
	CleanupStack::PushL( self );
	// Construct filter object which determines the type of delete 
	self->ConstructL( aFilter );
	CleanupStack::Pop( self );
	return self;
	}

// ---------------------------------------------------------------------------
// Destructor.
// ---------------------------------------------------------------------------
//
CCalendarDeleteEntry::~CCalendarDeleteEntry()
	{
	Cancel();
	
	delete iFilter;
	}

// ---------------------------------------------------------------------------
// Constructor.
// ---------------------------------------------------------------------------
//
CCalendarDeleteEntry::CCalendarDeleteEntry( CCalendarSessionInfo* aSessionInfo, 
												CAsyncRequestObserver* aAsyncRequestObserver,
												MCalCallbackBase* aNotifyCallback  ):
					//CActive( EPriorityStandard ),
					iSessionInfo( aSessionInfo ),
					iNotifyCallback ( aNotifyCallback ),
					iAsyncRequestObserver( aAsyncRequestObserver )
	{
	}

// ---------------------------------------------------------------------------
// ConstructL
// ---------------------------------------------------------------------------
//
void CCalendarDeleteEntry::ConstructL( CCalendarFilter* aFilter )
	{
	iFilter = CCalendarFilter::NewL();
	*iFilter = *aFilter;
	}
	
// ---------------------------------------------------------------------------
// Delete Request
// ---------------------------------------------------------------------------
//
void CCalendarDeleteEntry::DeleteL()
	{
	if ( iNotifyCallback ) // making call as asynchronous
		{
		if( !iAsyncRequestObserver )
			User::Leave( KErrArgument );
		
		CActiveScheduler::Add( this );
		ActivateRequest( KErrNone );
		}
	else				// making call as synchronous
		{ 
		// Sets the parameters for the delete operation
		InitializeDeleteOptionL();
		// Performs the actual delete depending on the parameters set
		StartDeleteL();
		}
	}

// ---------------------------------------------------------------------------
// Inherited from CActive class 
// ---------------------------------------------------------------------------
//
void CCalendarDeleteEntry::DoCancel()
	{
	NotifyRequestResult( KErrCancel );
	}

// ---------------------------------------------------------------------------
// Inherited from CActive class 
// ---------------------------------------------------------------------------
//
void CCalendarDeleteEntry::RunL()
	{
	TInt err = iStatus.Int();
	if ( err == KErrNone )
		{
		// Sets the parameters for the delete operation
		InitializeDeleteOptionL();
        // Performs the actual delete depending on the parameters set
		TRAP(err, StartDeleteL());
		}

	NotifyRequestResult( err );		
	}

// ---------------------------------------------------------------------------
// Delete All entries from the calendar
// ---------------------------------------------------------------------------
//
void CCalendarDeleteEntry::DeleteAllL()
	{
	// Create an instance of CCalIter to iterate through all calendar entries
	CCalIter* calIter = CCalIter::NewL(*(iSessionInfo->Session()));
	
	CleanupStack::PushL( calIter );
	
	CDesC8Array* array = new(ELeave) CDesC8ArraySeg( KArrayGran ); 

	CleanupStack::PushL( array );
	
	TPtrC8 firstUid( calIter->FirstL() );
	
	while ( firstUid != KNullDesC8 )
		{
		array->AppendL( firstUid );
		firstUid.Set( calIter->NextL() );
		}
    // Delete all calendar entries using entry view object
	iSessionInfo->EntryView()->DeleteL( *array );
	
	array->Reset();
	
	CleanupStack::PopAndDestroy(2, calIter);
	}

// ---------------------------------------------------------------------------
// Delete Instances based on Time Range
// ---------------------------------------------------------------------------
//
void CCalendarDeleteEntry::DeleteTimeRangeL()
	{
	RPointerArray<CCalInstance> array;

	CleanupStack::PushL( TCleanupItem(CleanupCCalInstanceArray, &array) );
	
	CalCommon::TCalTimeRange range =  iFilter->TimeRange();

	if( range.EndTime().TimeLocalL() != Time::NullTTime() && 
		range.StartTime().TimeLocalL() != Time::NullTTime() )
		{
		if( range.EndTime().TimeLocalL() < range.StartTime().TimeLocalL() )
			User::Leave( KErrArgument );
		}
	
	
	// Find all instances in specfied time range using instance view object
	iSessionInfo->InstanceView()->FindInstanceL( array, iFilter->FilterType(), 
														iFilter->TimeRange() );
	
	TInt count = array.Count();
	
	if ( count > 0 )
		{
		for ( TInt index = 0; index < count; index++ )
			{
			// Delete instances one by one using instance view object
			iSessionInfo->InstanceView()->DeleteL( array[index], CalCommon::EThisOnly );
			array[index] = NULL;
			}
		}
		
	CleanupStack::PopAndDestroy( &array );	
	}

// ---------------------------------------------------------------------------
// Delete Entries based in GlobalUid/LocalUid
// ---------------------------------------------------------------------------
//
void CCalendarDeleteEntry::DeleteUidL( TBool aLocalUid )
	{
	if ( aLocalUid )
		{
		TInt num;
		// Delete all entries with local uids as specified
		iSessionInfo->EntryView()->DeleteL( iFilter->LocalUidList(), num );
		}
	else
		{
		TInt count = iFilter->GuidList()->Count();
		for(TInt index = 0; index < count; index++)
			{
			RPointerArray<CCalEntry> calEntryArray;
			iSessionInfo->EntryView()->FetchL( iFilter->GuidList()->MdcaPoint(index), calEntryArray );
			if ( calEntryArray.Count() )
				{
	            CleanupStack::PushL( TCleanupItem(CleanupCCalEntryArray, &calEntryArray) );
				iSessionInfo->EntryView()->DeleteL( *calEntryArray[0] );
				CleanupStack::Pop( &calEntryArray );
				}
			
			calEntryArray.ResetAndDestroy();	
			// Delete all entries with global uids as specified
			//iSessionInfo->EntryView()->DeleteL( *iFilter->GuidList() );
			}
		// Delete all entries with global uids as specified
		//iSessionInfo->EntryView()->DeleteL( *iFilter->GuidList() );
		}	
	}

// ---------------------------------------------------------------------------
// Delete Instances based on Time Range and Global Uid
// ---------------------------------------------------------------------------
//
void CCalendarDeleteEntry::DeleteTimeRangeWithGlobalUidL()
	{
	RPointerArray<CCalInstance> array;
	
	CleanupStack::PushL( TCleanupItem(CleanupCCalInstanceArray, &array) );
	
	CalCommon::TCalTimeRange range =  iFilter->TimeRange();

	if( range.EndTime().TimeLocalL() != Time::NullTTime() && 
		range.StartTime().TimeLocalL() != Time::NullTTime() )
		{
		if( range.EndTime().TimeLocalL() < range.StartTime().TimeLocalL() )
			User::Leave( KErrArgument );
		}

	// Find all instances matching filter criteria
	iSessionInfo->InstanceView()->FindInstanceL( array, iFilter->FilterType(), iFilter->TimeRange() );
	
	for ( TInt index = 0; index < array.Count(); index++ )
		{
		TInt pos = 0;
		if( iFilter->GuidList()->Find( array[index]->Entry().UidL(), pos ) == 0 )
			{
			// Delete only those instances matching specified set of global uids
			iSessionInfo->InstanceView()->DeleteL( array[index], CalCommon::EThisOnly );
			array[index] = NULL;
			}
		}
	
	CleanupStack::PopAndDestroy( &array );	
	}

// ---------------------------------------------------------------------------
// Delete Instances based on Time Range and Local Uid
// ---------------------------------------------------------------------------
//
void CCalendarDeleteEntry::DeleteTimeRangeWithLocalUidL()
	{
	RPointerArray<CCalInstance> array;
	
	CleanupStack::PushL( TCleanupItem(CleanupCCalInstanceArray, &array) );
	
	const RArray<TCalLocalUid> &calLocalUidArray = iFilter->LocalUidList();
	
	CalCommon::TCalTimeRange range =  iFilter->TimeRange();

	if( range.EndTime().TimeLocalL() != Time::NullTTime() && 
		range.StartTime().TimeLocalL() != Time::NullTTime() )
		{
		if( range.EndTime().TimeLocalL() < range.StartTime().TimeLocalL() )
			User::Leave( KErrArgument );
		}

    // Find all instances matching filter criteria
	iSessionInfo->InstanceView()->FindInstanceL( array, iFilter->FilterType(), iFilter->TimeRange() );
	
	TInt count = array.Count();
	
	if ( count > 0 )
		{
		for ( TInt index = 0; index < count; index++ )
			{
			if( calLocalUidArray.Find( array[index]->Entry().LocalUidL() ) != KErrNotFound )
				{
				//// Delete only those instances matching specified set of local uids
				iSessionInfo->InstanceView()->DeleteL( array[index], CalCommon::EThisOnly );
				array[index] = NULL;
				}
			}
		}
		
	CleanupStack::PopAndDestroy( &array );
	}
	
// ---------------------------------------------------------------------------
// Call the appropriate delete based in delete option
// ---------------------------------------------------------------------------
//
void CCalendarDeleteEntry::StartDeleteL()
	{
	switch ( iDeleteOption )
		{
		case EDeleteAll:// delete all entries
			DeleteAllL();
			break;

		case EDeleteGUid: // delete on guid - entries
			DeleteUidL( EFalse );
			break;
			
		case EDeleteLUid: // delete on luid - etries
			DeleteUidL( ETrue );
			break;
			
		case EDeleteTimeRange: // delete on time range - instances
			DeleteTimeRangeL();
			break;
			
		case EDeleteTmRngGUid: // delete on time range with global uid - instances
			DeleteTimeRangeWithGlobalUidL();
			break;
			
		case EDeleteTmRngLUid: // delete on time range with local uid - instances
			DeleteTimeRangeWithLocalUidL();
			break;
		
		default:
			break;
		}
	}

// ---------------------------------------------------------------------------
// Initialises delete option
// ---------------------------------------------------------------------------
//
void CCalendarDeleteEntry::InitializeDeleteOptionL()
	{
	//Delete all entries from calendar
	if ( iFilter->Filter() == EFlagDeleteAll )
		{
		iDeleteOption = EDeleteAll;
		}
	
	//Filter having only GUids
	else if ( iFilter->Filter() == EFilterGUid )
		{
		iDeleteOption = EDeleteGUid;
		}
		

	//Filter having only LocalUids
	else if ( iFilter->Filter() == EFilterLUid )
		{
		iDeleteOption = EDeleteLUid;
		}
	
	
	//Filter having time range only (No GUid/LocalUid)
	else if ( !( iFilter->Filter() & EFilterGUid ) &&
				!( iFilter->Filter() & EFilterLUid ) )
		{
		if ( ( iFilter->Filter() & EFilterStTime ) || ( iFilter->Filter() & EFilterEndTime ) )
			iDeleteOption = EDeleteTimeRange;
		else
			iDeleteOption = EDeleteAll;
		}

	//Filter having time range and GUid
	else if ( ( iFilter->Filter() & EFilterGUid ) && 
				( ( iFilter->Filter() & EFilterStTime ) || ( iFilter->Filter() & EFilterEndTime ) ) )// bound time only
		{
		iDeleteOption = EDeleteTmRngGUid;
		}

	//Filter having time range and LocalUid
	else if ( ( iFilter->Filter() & EFilterLUid ) && 
				( ( iFilter->Filter() & EFilterStTime ) || ( iFilter->Filter() & EFilterEndTime ) ) )
		{
		iDeleteOption = EDeleteTmRngLUid;
		}
	else
		{
		User::Leave( KErrArgument );
		}
	}


// ---------------------------------------------------------------------------
// Activates the asynchronous request
// ---------------------------------------------------------------------------
//
void CCalendarDeleteEntry::ActivateRequest( TInt aReason )
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
void CCalendarDeleteEntry::NotifyRequestResult( TInt aReason )
	{
	if ( iNotifyCallback )
		{
		iAsyncRequestObserver->RequestComplete( iNotifyCallback->iTransactionId );
		TRAPD( err, iNotifyCallback->NotifyResultL( aReason, NULL ));
		}
	
	// caller will delete the object in case of cancel
	if ( aReason != KErrCancel )
		delete this;
	}

