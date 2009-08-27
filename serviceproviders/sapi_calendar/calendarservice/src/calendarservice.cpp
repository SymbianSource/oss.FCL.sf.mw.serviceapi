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
* Description:  Interface to Calender service
*
*/


#include <e32base.h>
#include <calsession.h>
#include <calinstance.h>
#include <calentryview.h>
#include <calinstanceview.h>
#include <calrrule.h>
#include <badesca.h>

#include "calendarheader.h"
#include "calendarconstants.h"
#include "entryattributes.h"
#include "calendarservice.h"
#include "Calendarnotify.h"
#include "calendardeleteentry.h"
#include "calendarimport.h"
#include "calendarexport.h"
#include "addentry.h"
#include "asyncreqobserver.h"
#include "calendargetlist.h"

// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CAsyncRequestObserver* CAsyncRequestObserver::NewL()
	{
	return new(ELeave) CAsyncRequestObserver;
	}
	
// ---------------------------------------------------------------------------
// Destructor.
// ---------------------------------------------------------------------------
//
CAsyncRequestObserver::~CAsyncRequestObserver()
	{
	DeleteAsyncObjects();//deletes all Asychronous objects
	iAsyncObjArray.Reset();
	}
		
// ---------------------------------------------------------------------------
// Notifies about the completeion of an async request.
// ---------------------------------------------------------------------------
//
void CAsyncRequestObserver::RequestComplete( const TInt32 aTransactionId )
	{
	TInt pos = iAsyncObjArray.Count() - 1;
	TAsyncRequestInfo obj;
	for ( ; pos >= 0; pos-- )
		{
		obj = iAsyncObjArray[pos];
		// Remove object with transaction id aTransactionId from async object array
		if( obj.iTransactionId == aTransactionId )
			{
			iAsyncObjArray.Remove(pos);
			iAsyncObjArray.Compress();
			return;
			}
		}
	}

// ---------------------------------------------------------------------------
// Deletes all the asynchronous request objects
// ---------------------------------------------------------------------------
//
void CAsyncRequestObserver::DeleteAsyncObjects()
	{
	TInt pos = iAsyncObjArray.Count() - 1;
	TAsyncRequestInfo obj;
	for ( ; pos >= 0; pos-- )
		{
		obj = iAsyncObjArray[pos];
		obj.iAsyncObj->Cancel();
		delete obj.iAsyncObj;
		}
	}



// ---------------------------------------------------------------------------
// Cancels asynchronous request
// ---------------------------------------------------------------------------
//
EXPORT_C TInt CAsyncRequestObserver::Cancel( const TInt32 aTransactionId )
	{
	TInt pos = iAsyncObjArray.Count() - 1;
	TAsyncRequestInfo obj;
	for ( ; pos >= 0; pos-- )
		{
		obj = iAsyncObjArray[pos];
		// Cancel and remove object with transaction id aTransactionId from async object array
		if( obj.iTransactionId == aTransactionId )
			{
			if(obj.iAsyncObj->IsInProgress())
				return KErrInUse;
			
			obj.iAsyncObj->Cancel();
			delete obj.iAsyncObj;
			return KErrNone;
			}
		}
		
	return KErrNotFound;
	}

// ---------------------------------------------------------------------------
// Adds asynchronous request object
// ---------------------------------------------------------------------------
//
void CAsyncRequestObserver::AddAsyncObjL( const TInt32 aTransactionId, CCalendarASyncRequest* aAsyncObj )
	{
	// Add async object to array to keep track of async requests
	TAsyncRequestInfo asyncRequestInfo;
	asyncRequestInfo.iTransactionId = aTransactionId;
	asyncRequestInfo.iAsyncObj = aAsyncObj;
	User::LeaveIfError( iAsyncObjArray.Append( asyncRequestInfo ) );
	}

// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
EXPORT_C CCalendarService* CCalendarService::NewL()
	{
	CCalendarService* self = new (ELeave) CCalendarService;
	CleanupStack::PushL( self );
	self->ConstructL();
	CleanupStack::Pop( self );
	return self;
	}
	
// ---------------------------------------------------------------------------
// Destructor.
// ---------------------------------------------------------------------------
//
CCalendarService::~CCalendarService()
	{
	delete iAsyncReqObserver;
	iArraySessionInfo.ResetAndDestroy();
	}

// ---------------------------------------------------------------------------
// Constructor.
// ---------------------------------------------------------------------------
//
CCalendarService::CCalendarService()
	{
	}

// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
void CCalendarService::ConstructL()
	{
	//Create default calendar session
	CalendarSessionInfoL( KNullDesC );
	iAsyncReqObserver = CAsyncRequestObserver::NewL();
	}

// ---------------------------------------------------------------------------
// Returns list of available calendars in device.
// Default calendar will be returned in case aDefault is true.
// ---------------------------------------------------------------------------
//
EXPORT_C void CCalendarService::GetListL(  CDesCArray*&  aCalendarList, const TBool aDefault )
	{
	if ( aDefault )
		{
		aCalendarList = new(ELeave) CDesCArraySeg( KArrayGran );
		// Append default calendar to calendar list if aDefault ==  ETrue
		CleanupStack::PushL( aCalendarList );
		aCalendarList->AppendL( iArraySessionInfo[KArrayZeroIndex]->Calendar() );
		CleanupStack::Pop( aCalendarList );
		}
	else
		{
		// Append all available to calendar list
		aCalendarList = iArraySessionInfo[KArrayZeroIndex]->Session()->ListCalFilesL();
		}
	}

// ---------------------------------------------------------------------------
// Returns list of calendar entries from given calendar with the given Global UID.
// ---------------------------------------------------------------------------
//
EXPORT_C void CCalendarService::GetListL( const TDesC& aCalendarName, const TDesC8& aGuid, RPointerArray<CCalEntry>& aEntryList)
	{
	CCalendarSessionInfo* sessionInfo = CalendarSessionInfoL( aCalendarName );
	
	// Get list of calendar entries using CCalEntryView 
	CCalendarGetList* getlistObj = CCalendarGetList::NewL( sessionInfo, aGuid );
    
    CleanupStack::PushL( getlistObj );
    
    getlistObj->GetListL( aGuid, aEntryList );
    
    CleanupStack::PopAndDestroy( getlistObj );
	}

// ---------------------------------------------------------------------------
// Returns list of calendar entries from given calendar with the given Local UID.
// ---------------------------------------------------------------------------
//
EXPORT_C void CCalendarService::GetListL( const TDesC& aCalendarName, const TCalLocalUid aLocalUid, RPointerArray<CCalEntry>& aEntryList)
	{
	CCalendarSessionInfo* sessionInfo = CalendarSessionInfoL( aCalendarName );

	CCalendarGetList* getlistObj = CCalendarGetList::NewL( sessionInfo, aLocalUid );
    
    CleanupStack::PushL( getlistObj );
    
    getlistObj->GetListL( aLocalUid, aEntryList );
    
    CleanupStack::PopAndDestroy( getlistObj );

	}

// ---------------------------------------------------------------------------
// Returns list of calendar instances from given calendar based on input filter.
// ---------------------------------------------------------------------------
//
EXPORT_C void CCalendarService::GetListL( const TDesC& aCalendarName, CCalendarFilter* aFilter, 
											RPointerArray<CCalInstance>& aInstanceList )
	{
	if ( !aFilter )
		User::Leave( KErrArgument );
	
	CCalendarSessionInfo* sessionInfo = CalendarSessionInfoL( aCalendarName );
	
	CCalendarGetList* getlistObj = CCalendarGetList::NewL( sessionInfo, aFilter );
    
    CleanupStack::PushL( getlistObj );
    
    getlistObj->GetListL( aInstanceList );
    
    CleanupStack::PopAndDestroy( getlistObj );
    
	}

// ---------------------------------------------------------------------------
// Returns list of calendar instances from given calendar based on input filter and callback.
// ---------------------------------------------------------------------------
//
EXPORT_C void CCalendarService::GetListL( const TDesC& aCalendarName, CCalendarFilter* aFilter, 
                                                  MCalCallbackBase*      aCallBack )
    {
    if ( !aFilter )
        User::Leave( KErrArgument );
    
    CCalendarSessionInfo* sessionInfo = CalendarSessionInfoL( aCalendarName );

    //Instantiate the getlist CoreClass Object
    CCalendarGetList* getlistObj = CCalendarGetList::NewL( sessionInfo, aFilter, iAsyncReqObserver, aCallBack );
    
    //Push the GetlistObject onto the cleanup stack as the getlist function can Leave
    CleanupStack::PushL( getlistObj );
    
    getlistObj->GetListL();
    
    AddAsyncObjL( aCallBack->iTransactionId, getlistObj );
    
    CleanupStack::Pop( getlistObj );

    }
// ---------------------------------------------------------------------------
// Returns list of calendar entries from given calendar with the given Global UID.
// ---------------------------------------------------------------------------
//
EXPORT_C void CCalendarService::GetListL( const TDesC& aCalendarName, const TDesC8& aGuid, MCalCallbackBase*      aCallBack)
    {
    CCalendarSessionInfo* sessionInfo = CalendarSessionInfoL( aCalendarName );

    CCalendarGetList* getlistObj = CCalendarGetList::NewL( sessionInfo, aGuid, iAsyncReqObserver, aCallBack );
    
    CleanupStack::PushL( getlistObj );
    
    getlistObj->GetListL();
    
    AddAsyncObjL( aCallBack->iTransactionId, getlistObj );
    
    CleanupStack::Pop( getlistObj );

    }
// ---------------------------------------------------------------------------
// Returns list of calendar entries from given calendar with the given Local UID.
// ---------------------------------------------------------------------------
//
EXPORT_C void CCalendarService::GetListL( const TDesC& aCalendarName, const TCalLocalUid aLocalUid, MCalCallbackBase*      aCallBack)
    {
    CCalendarSessionInfo* sessionInfo = CalendarSessionInfoL( aCalendarName );

    CCalendarGetList* getlistObj = CCalendarGetList::NewL( sessionInfo, aLocalUid, iAsyncReqObserver, aCallBack );
    
    CleanupStack::PushL( getlistObj );
    
    getlistObj->GetListL();
    
    AddAsyncObjL( aCallBack->iTransactionId, getlistObj );
    
    CleanupStack::Pop( getlistObj );

    }
// ---------------------------------------------------------------------------
// Adds new calendar 
// ---------------------------------------------------------------------------
//
EXPORT_C void CCalendarService::AddL( const TDesC& aCalendarName )
	{
	//Create a new calendar file using the existing session object
	iArraySessionInfo[KArrayZeroIndex]->Session()->CreateCalFileL( aCalendarName );
	}

// ---------------------------------------------------------------------------
// Add
// ---------------------------------------------------------------------------
//
EXPORT_C void CCalendarService::AddL( const TDesC& aCalendarName, 
                        				CEntryAttributes* aCalendarData, TUIDSet*& aUidAdded ) 
	{
	if ( !aCalendarData )
		User::Leave( KErrArgument );
	
	CCalendarSessionInfo* sessionInfo = CalendarSessionInfoL( aCalendarName );
	CCalendarAddEntry* obj = CCalendarAddEntry::NewL( sessionInfo, aCalendarData );
	CleanupStack::PushL( obj );
	obj->AddL( aUidAdded );
	CleanupStack::PopAndDestroy( obj );
	}

// ---------------------------------------------------------------------------
// Remove calendar from the device. Deletion of defaut calendar is not supported
// ---------------------------------------------------------------------------
//
EXPORT_C void CCalendarService::DeleteL( const TDesC& aCalendarName )
	{
	if ( aCalendarName.CompareF(iArraySessionInfo[KArrayZeroIndex]->Calendar()) != 0 )
		{
		RemoveSessionInfo( aCalendarName );
		iArraySessionInfo[KArrayZeroIndex]->Session()->DeleteCalFileL( aCalendarName );
		}
	else
		{
		User::Leave( KErrNotSupported );
		}
	}

// ---------------------------------------------------------------------------
// Remove entries from the given calendar based on input filter
// ---------------------------------------------------------------------------
//
EXPORT_C void CCalendarService::DeleteL( const TDesC& aCalendarName, CCalendarFilter* aFilter, MCalCallbackBase* aCallBack )
	{
	if ( !aFilter )
		User::Leave( KErrArgument );
	
	CCalendarSessionInfo* sessionInfo = CalendarSessionInfoL( aCalendarName );

	//Instantiate the Delete Class Object
	CCalendarDeleteEntry* obj = CCalendarDeleteEntry::NewL( sessionInfo, aFilter, iAsyncReqObserver, aCallBack);

	CleanupStack::PushL( obj );
	
	// Call the appropriate version of delete depending on input
	obj->DeleteL();
	
	if ( aCallBack )
		{
		AddAsyncObjL(aCallBack->iTransactionId, obj );
		CleanupStack::Pop( obj );
		}
	else
		CleanupStack::PopAndDestroy( obj );
	}

// ---------------------------------------------------------------------------
// ImportL: This is the Synchronous version of Import which imports all the 
//         entries in the format specified from the Calendar
// ---------------------------------------------------------------------------
//
EXPORT_C void CCalendarService::ImportL( const TDesC& aCalendarName, 
										 const TDesC8& aFormat, 
										 const TDesC8& aInputBuffer, 
										 RPointerArray<TUIDSet>& aUIDSet )
	{
	//Step 1: get the session
	CCalendarSessionInfo* sessionInfo = CalendarSessionInfoL( aCalendarName );
	
	//Step 2: Instantiate the Import CoreClass Object
	CCalendarImport* importObj = CCalendarImport::NewL( sessionInfo, aFormat, aInputBuffer );
	
	//Step 3: Push the ImportObject onto the cleanup stack as the Import function can Leave
	CleanupStack::PushL( importObj );
	
	//Step 4: Call the Import along side the handle to the Output i.e.., aUIDSet
	importObj->ImportL( aUIDSet );
	
	//Step 5: Destroy the Object as the processing is done
	CleanupStack::PopAndDestroy( importObj );
	}

// ---------------------------------------------------------------------------
// ImportL: This is the Synchronous version of Import which imports all the 
//         entries in the format specified from the Calendar
// ---------------------------------------------------------------------------
//
EXPORT_C void CCalendarService::ImportL( const TDesC& aCalendarName, 
										 const TDesC8& aFormat, 
										 const TDesC& aImportFile, 
										 RPointerArray<TUIDSet>& aUIDSet )
	{
	//Step 1: get the session
	CCalendarSessionInfo* sessionInfo = CalendarSessionInfoL( aCalendarName );
	
	//Step 2: Instantiate the Import CoreClass Object
	CCalendarImport* importObj = CCalendarImport::NewL( sessionInfo, aFormat, aImportFile );
	
	//Step 3: Push the ImportObject onto the cleanup stack as the Import function can Leave
	CleanupStack::PushL( importObj );
	
	//Step 4: Call the Import along side the handle to the Output i.e.., aUIDSet
	importObj->ImportL( aUIDSet );
	
	//Step 5: Destroy the Object as the processing is done
	CleanupStack::PopAndDestroy( importObj );
	}

// -----------------------------------------------------------------------------
// ImportAsyncL: This is the Asynchronous version of Import which imports all the 
//         		 entries in the format specified to the Calendar
// ------------------------------------------------------------------------------
//		
EXPORT_C void CCalendarService::ImportL( const TDesC&           aCalendarName, 
									     const TDesC8&          aFormat, 
										 const TDesC8&          aInputBuffer, 
										 MCalCallbackBase*      aCallBack )
	{
	//get the session
	CCalendarSessionInfo* sessionInfo = CalendarSessionInfoL( aCalendarName );
	
	//Instantiate the Import CoreClass Object
	CCalendarImport* importObj = CCalendarImport::NewL( sessionInfo, aFormat, aInputBuffer, iAsyncReqObserver, aCallBack );
	
	//Push the ImportObject onto the cleanup stack as the Import function can Leave
	CleanupStack::PushL( importObj );
	
	importObj->ImportL();
	
	AddAsyncObjL( aCallBack->iTransactionId, importObj );
	
	CleanupStack::Pop( importObj );
	}
	
// -----------------------------------------------------------------------------
// ImportAsyncL: This is the Asynchronous version of Import which imports all the 
//         		 entries in the format specified to the Calendar
// ------------------------------------------------------------------------------
//		
EXPORT_C void CCalendarService::ImportL( const TDesC&           aCalendarName, 
									     const TDesC8&          aFormat, 
										 const TDesC&           aImportFile, 
										 MCalCallbackBase*      aCallBack )
	{
	//get the session
	CCalendarSessionInfo* sessionInfo = CalendarSessionInfoL( aCalendarName );
	
	//Instantiate the Import CoreClass Object
	CCalendarImport* importObj = CCalendarImport::NewL( sessionInfo, aFormat, aImportFile, iAsyncReqObserver, aCallBack );
	
	//Push the ImportObject onto the cleanup stack as the Import function can Leave
	CleanupStack::PushL( importObj );
	
	importObj->ImportL();
	
	AddAsyncObjL( aCallBack->iTransactionId, importObj );
	
	CleanupStack::Pop( importObj );
	}
	
	
	
// ---------------------------------------------------------------------------
// ExportL: This is the Synchronous Version which exports all the entries of 
//			Calendar in the Specified format
// ---------------------------------------------------------------------------
//
EXPORT_C void CCalendarService::ExportL( const TDesC&           aCalendarName, 
										 const TDesC8&          aFormat,
										 CCalendarExportParams* aParams,  
										 HBufC8*&               aOutputBuffer )
	{
	if( !aParams )
		User::Leave( KErrArgument );
	
	CCalendarSessionInfo* sessionInfo = CalendarSessionInfoL( aCalendarName );
	
	CCalendarExport* exportObj = CCalendarExport::NewL( sessionInfo, aFormat, aParams );

	CleanupStack::PushL( exportObj );
	
	exportObj->ExportL( aOutputBuffer );
	
	CleanupStack::PopAndDestroy( exportObj );	
	}


// ---------------------------------------------------------------------------
// ExportAsyncL: This is the Asynchronous Version which exports all the entries of 
//				 Calendar in the Specified format
// ---------------------------------------------------------------------------
//
EXPORT_C void CCalendarService::ExportL( const TDesC&           aCalendarName, 
									     const TDesC8&          aFormat, 
										 CCalendarExportParams* aParams, 
										 MCalCallbackBase*      aCallBack )
	{
	if( !aParams )
		User::Leave( KErrArgument );
	
	CCalendarSessionInfo* sessionInfo = CalendarSessionInfoL( aCalendarName );
	
	CCalendarExport* exportObj = CCalendarExport::NewL( sessionInfo, aFormat, aParams, iAsyncReqObserver, aCallBack );

	CleanupStack::PushL( exportObj );
	
	exportObj->ExportL();
	
	AddAsyncObjL(aCallBack->iTransactionId, exportObj );
	
	CleanupStack::Pop( exportObj );	
	}
	
// ---------------------------------------------------------------------------
// Start Notification for changes in given calendar
// ---------------------------------------------------------------------------
//
EXPORT_C void CCalendarService::StartChangeNotifyL( const TDesC& aCalendarName, CCalendarFilter* aFilter, MCalCallbackBase* aCallBack )
	{
	if( !aCallBack || !aFilter )
		User::Leave( KErrArgument );
	
	CCalendarSessionInfo* sessionInfo = CalendarSessionInfoL( aCalendarName );

	CCalendarObserver* obj = CCalendarObserver::NewL( sessionInfo, aFilter, iAsyncReqObserver, aCallBack );

	CleanupStack::PushL( obj );
	
	// notify in case of add/delete/update operation performed on calendar entries
	obj->StartChangeNotificationL();
	
	AddAsyncObjL(aCallBack->iTransactionId, obj );

	CleanupStack::Pop( obj );

	}

// ---------------------------------------------------------------------------
// Adds asynchronous request object
// ---------------------------------------------------------------------------
//
void CCalendarService::AddAsyncObjL( const TInt32 aTransactionId, CCalendarASyncRequest* aAsyncObj )
	{
	iAsyncReqObserver->AddAsyncObjL( aTransactionId, aAsyncObj );
	}

// ---------------------------------------------------------------------------
// Cancels asynchronous request
// ---------------------------------------------------------------------------
//
EXPORT_C TInt CCalendarService::Cancel( const TInt32 aTransactionId )
	{
	return iAsyncReqObserver->Cancel( aTransactionId );
	}

// ---------------------------------------------------------------------------
// Returns Calendar session information for given calendar
// ---------------------------------------------------------------------------
//
CCalendarSessionInfo* CCalendarService::CalendarSessionInfoL( const TDesC& aCalendar )
	{
	// Return default session object if aCalendar is KNullDesC
	if ( ( iArraySessionInfo.Count() > 0 ) && ( aCalendar.Length() == 0 ) )
		return iArraySessionInfo[KArrayZeroIndex];
	
	TInt count = iArraySessionInfo.Count();
	for( TInt index = 0; index < count; index++ )
		{
		// Return session information of object corresponding to aCalendar
		if ( aCalendar.CompareF(iArraySessionInfo[index]->Calendar() ) == 0 )
			return iArraySessionInfo[index];
		}
	// If session object is not found, create new session object
	// and append to session info array	
	CCalendarSessionInfo* sessionInfo = CCalendarSessionInfo::NewL( aCalendar );
	CleanupStack::PushL( sessionInfo );
	iArraySessionInfo.AppendL( sessionInfo );
	CleanupStack::Pop( sessionInfo );
	return sessionInfo;
	}

// ---------------------------------------------------------------------------
// Closes Calendar session for given calendar
// ---------------------------------------------------------------------------
//
void CCalendarService::RemoveSessionInfo( const TDesC& aCalendar )
	{
	TInt count = iArraySessionInfo.Count();
	for( TInt index = 1; index < count; index++ )
		{
		if( aCalendar.CompareF(iArraySessionInfo[index]->Calendar()) == 0 )
			{
			// Remove session information for aCalendar and close session
			CCalendarSessionInfo* sessionInfo = iArraySessionInfo[index];
			iArraySessionInfo.Remove( index );
			iArraySessionInfo.Compress();
			delete sessionInfo;
			break;
			}
		}
	}
