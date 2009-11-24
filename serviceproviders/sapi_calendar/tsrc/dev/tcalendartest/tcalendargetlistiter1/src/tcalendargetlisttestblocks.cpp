/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:   ?Description
*
*/




// INCLUDE FILES
#include <e32svr.h>
#include <e32std.h>
#include <f32file.h> //for RFile and Rfs
#include <StifParser.h>
//#include <SAPI_TEST\testprg.h>
#include <StifTestInterface.h>
#include "calendarheader.h"
#include "calendarservice.h"
#include <calentry.h>//for CCalEntry
#include <calinstanceview.h>//for CCalInstance
#include <calcommon.h>//for Filter Type Enum Constants
#include <calinstance.h>

#include "tcalendargetlisttest.h"
#include "teststartconsolealarmserver.h"
#include "calgetlisttestcases.h"


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTChangeStatusTest::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTCalendarGetListTest::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CTChangeStatusTest::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTCalendarGetListTest::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        //TRY( "SendMessage",    CTDeleteMessageTest::SendMessage ),
        
        ENTRY( "GetListCalendar",    	CTCalendarGetListTest::GetListCalendar ),
        ENTRY( "GetDefaultCalendar",    CTCalendarGetListTest::GetDefaultCalendar ),
        ENTRY( "GetListGUidFilter",    	CTCalendarGetListTest::GetListGUidFilter ),
        ENTRY( "GetListLocalUidFilter", CTCalendarGetListTest::GetListLocalUidFilter ),
        ENTRY( "GetListTimeRangeFilter",CTCalendarGetListTest::GetListTimeRangeFilter ),
        ENTRY( "GetListTextFilter",    	CTCalendarGetListTest::GetListTextFilter ),
        ENTRY( "GetListTypeFilter",    	CTCalendarGetListTest::GetListTypeFilter ),
		ENTRY( "GetListInvalidCalName", CTCalendarGetListTest::GetListInvalidCalName ),
		ENTRY( "GetListInvalidGUID"   , CTCalendarGetListTest::GetListInvalidGUID ),
		ENTRY( "GetListInvalidLUID"   , CTCalendarGetListTest::GetListInvalidLUID ),
		
		ENTRY( "GetListTimeRangeFilterAsync",       CTCalendarGetListTest::GetListTimeRangeFilterAsync ),
		ENTRY( "GetListGuidFilterAsync",       CTCalendarGetListTest::GetListGuidFilterAsync ),
		ENTRY( "GetListLuidFilterAsync",       CTCalendarGetListTest::GetListLuidFilterAsync ),
		ENTRY( "GetListTextFilterAsync",       CTCalendarGetListTest::GetListTextFilterAsync ),
		ENTRY( "GetListTypeFilterAsync",       CTCalendarGetListTest::GetListTypeFilterAsync ),
        ENTRY( "GetListInvalidGuidFilterAsync",       CTCalendarGetListTest::GetListInvalidGuidFilterAsync ),
	    ENTRY( "GetListInvalidLuidFilterAsync",       CTCalendarGetListTest::GetListInvalidLuidFilterAsync ),

        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }


_LIT(KSearchTexttest                 ,"Meeting");

_LIT(KDefaultCalendar                ,"C:Calendar");
_LIT(KTestCal1File                ,"C:getlistcal1");
_LIT(KTestCal2File                ,"C:getlistcal2");

//	
//Whats done here? 
//	Get all the Calendars in the system using GetList of CCalendarService and output that to GetListallCalendars.txt
//
TInt CTCalendarGetListTest::GetListCalendar(CStifItemParser& /*aItem*/ )
	{
	TInt result = KErrNone;

	__UHEAP_MARK;
	
	CDesCArray* allCalendarNames = NULL;
	
	CCalendarService* service = CCalendarService::NewL();
	
	if(service)
		{
		TInt calAdderr = AddCalendarFile(service, KTestCal1File);
		if( calAdderr == KErrNone || calAdderr == KErrAlreadyExists )	
			{
			calAdderr = AddCalendarFile(service, KTestCal2File);
			if( calAdderr == KErrNone || calAdderr == KErrAlreadyExists )	
				{
				TRAPD( err , service->GetListL( allCalendarNames, EFalse ) );

				if( err == KErrNone )
					{
					if( allCalendarNames )
						{
						TInt pos1, pos2;
						if( allCalendarNames->Count() < 2 || allCalendarNames->Find(KTestCal1File, pos1) != 0 ||
																allCalendarNames->Find(KTestCal2File, pos2) != 0 )
							result = KErrGeneral;
						
						allCalendarNames->Reset();
						}
					else
						result = KErrGeneral;
							
					}
				else
					{
					if( allCalendarNames )
						allCalendarNames->Reset();
					result = err;
					
					}	
				}
			}
		else
			result = calAdderr;
		}

	RemoveCalendarFile( service, KTestCal1File );
	RemoveCalendarFile( service, KTestCal2File );
	
	delete allCalendarNames;
	delete service;
	
	__UHEAP_MARKEND;
	return result;

    }

//	
//Whats done here? 
//	Get the default system Calendar using GetList of CCalendarService and output that to GetListdefaultCalendar.txt
//    
TInt CTCalendarGetListTest::GetDefaultCalendar(CStifItemParser& /*aItem*/ )
	{
	TInt result = KErrNone;

	__UHEAP_MARK;
	
	CDesCArray* allCalendarNames = NULL;
	
	CCalendarService* service = CCalendarService::NewL();
	
	CleanupStack::PushL( service );
	
	TRAPD( err , service->GetListL(  allCalendarNames, ETrue ) );
	
	result = err;
	
	if( err == KErrNone )
		{
		if( allCalendarNames )
			{
			if( allCalendarNames->Count() != 1 )
				result = KErrGeneral;
			
			allCalendarNames->Reset();
			}
		else
			result = KErrGeneral;
				
		}
	else
		{
		if( allCalendarNames )
			allCalendarNames->Reset();
		result = err;
		
		}	
	    
	delete allCalendarNames;
	
	CleanupStack::PopAndDestroy( service );

	__UHEAP_MARKEND;
	
	return result;
    }
 
 

//	
//Whats done here? 
//	Get the GUIDS from Default Calendar using GetList of CCalendarService and then get the CCalEntries for corresponding 
//	GUIDS using GetList of CCalendarService and dump the GUIDS , LUIDS into a files 
//    
TInt CTCalendarGetListTest::GetListGUidFilter(CStifItemParser& /*aItem*/ )
	{
	TInt result = KErrNone;
	
	__UHEAP_MARK;
	
	CCalendarService* service = CCalendarService::NewL();
	
	RemoveCalendarFile( service, KTestCal1File );
	AddCalendarFile( service, KTestCal1File );

	RPointerArray<TUIDSet> arruids(5);
	
	TUIDSet* uids = NULL;
	
	if(AddAppointment(service, KTestCal1File, uids) == KErrNone && uids)
		{
		arruids.Append(uids);
		uids = NULL;
		}

	if(AddEvent(service, KTestCal1File, uids) == KErrNone && uids)
		{
		arruids.Append(uids);
		uids = NULL;
		}
	
	if ( arruids.Count() > 0 )
		{
	    RPointerArray<CCalEntry> entryArray;
	     
	    TRAPD( err, service->GetListL( KTestCal1File, *(arruids[0]->iGlobalUID), entryArray ));
	    if ( err == KErrNone )
	    	{ 
	    	if( !( entryArray.Count() == 1 && entryArray[0]->UidL().CompareF(*(arruids[0]->iGlobalUID)) == 0 ))
	    		{
	    		result = KErrGeneral;
	    		}
	    	}
	    else
	    	result = err;	
	    
	    entryArray.ResetAndDestroy();
	    arruids.ResetAndDestroy();
		}
	else
		result = KErrGeneral;	

	RemoveCalendarFile( service, KTestCal1File );
	
	delete service;

	__UHEAP_MARKEND;

	return result;
    }
 

//	
//Whats done here? 
//  Get the LUIDS from Default Calendar using GetList of CCalendarService and then get the CCalEntries for corresponding 
//	LUIDS using GetList of CCalendarService and dump the GUIDS , LUIDS into a files 
//     
TInt CTCalendarGetListTest::GetListLocalUidFilter(CStifItemParser& /*aItem*/ )
	{
	TInt result = KErrNone;
	
	__UHEAP_MARK;
	
	CCalendarService* service = CCalendarService::NewL();
	
	RemoveCalendarFile( service, KTestCal1File );
	AddCalendarFile( service, KTestCal1File );

	RPointerArray<TUIDSet> arruids(5);
	
	TUIDSet* uids = NULL;
	
	if(AddAppointment(service, KTestCal1File, uids) == KErrNone && uids)
		{
		arruids.Append(uids);
		uids = NULL;
		}

	if(AddEvent(service, KTestCal1File, uids) == KErrNone && uids)
		{
		arruids.Append(uids);
		uids = NULL;
		}
	
	if ( arruids.Count() > 0 )
		{
	    RPointerArray<CCalEntry> entryArray;
	     
	    TRAPD( err, service->GetListL( KTestCal1File, arruids[0]->iLocalUID , entryArray ));
	    if ( err == KErrNone )
	    	{ 
	    	if( !( entryArray.Count() == 1 && entryArray[0]->LocalUidL() == arruids[0]->iLocalUID ))
	    		{
	    		result = KErrGeneral;
	    		}
	    	}
	    else
	    	result = err;	
	    
	    entryArray.ResetAndDestroy();
	    arruids.ResetAndDestroy();
		}
	else
		result = KErrGeneral;	

	RemoveCalendarFile( service, KTestCal1File );
	
	delete service;

	__UHEAP_MARKEND;

	return result;
    }
    
    

//	
//Whats done here? 
//	Get the default system Calendar using GetList of CCalendarService and output that to GetListdefaultCalendar.txt
//    
TInt CTCalendarGetListTest::GetListTimeRangeFilter(CStifItemParser& /*aItem*/ )
	{
	TInt result = KErrNone;
	
	__UHEAP_MARK;
	
	CCalendarService* service = CCalendarService::NewL();
	
	RemoveCalendarFile( service, KTestCal1File );
	AddCalendarFile( service, KTestCal1File );


	CEntryAttributes* entryObj = CEntryAttributes::NewL(KEntryAppt);
	
	entryObj->SetDescriptionL(_L("SAPI weekly meeting"));
	entryObj->SetLocationL(_L("Hara"));
	entryObj->SetEntryStatusL(KStatusConfirmed);
	entryObj->SetMethodL(KMethodNone);
	entryObj->SetPriority(5);
    entryObj->SetSummaryL(_L("Meeting Happens from 9 to 9:30"));
    
    TCalTime stTime;
	stTime.SetTimeLocalL(TTime(TDateTime(2007, EAugust, 8, 9, 0, 0, 0)));
	entryObj->SetStartTimeL(TTime(TDateTime(2007, EAugust, 8, 9, 0, 0, 0)));
	
	TCalTime endTime;
	endTime.SetTimeLocalL(TTime(TDateTime(2007, EAugust, 8, 9, 30, 0, 0)));
	entryObj->SetEndTimeL(TTime(TDateTime(2007, EAugust, 8, 9, 30, 0, 0)));
	
    CRepeatInfo* rrule = CRepeatInfo::NewL(TCalRRule::EWeekly);
	rrule->SetStartTimeL(TTime(TDateTime(2007, EAugust, 8, 9, 0, 0, 0)));
    
    RArray<TDay> dayArray;
    dayArray.Append( stTime.TimeLocalL().DayNoInWeek() );
    rrule->SetDaysInWeek( dayArray );
    rrule->SetCount( 10 );

    entryObj->SetRepeatRule( rrule );
    dayArray.Reset();
    delete rrule;
	
	TUIDSet* uids = NULL;
	service->AddL(KTestCal1File,entryObj,uids);

	RPointerArray<TUIDSet> arruids(5);
	
	arruids.Append(uids);

	if ( arruids.Count() > 0 )
		{
	    RPointerArray<CCalInstance> instanceArray;

		CCalendarFilter *filter = CCalendarFilter::NewL();
		
		filter->SetStartTimeL(TTime(TDateTime(2007, EAugust, 8, 9, 0, 0, 0)));
		filter->SetEndTimeL(TTime(TDateTime(2008, EAugust, 8, 9, 0, 0, 0)));
	     
	    TRAPD( err, service->GetListL( KTestCal1File, filter, instanceArray ));

	    if ( err == KErrNone )
	    	{ 
	    	if( !( instanceArray.Count() == 10 && instanceArray[0]->Entry().UidL().CompareF(*(arruids[0]->iGlobalUID)) == 0 ))
	    		{
	    		result = KErrGeneral;
	    		}
	    	}
	    else
	    	result = err;	
	    
	    delete filter;
	    instanceArray.ResetAndDestroy();
	    arruids.ResetAndDestroy();
		}
	else
		result = KErrGeneral;	

	RemoveCalendarFile( service, KTestCal1File );
	delete entryObj;
	delete service;

	__UHEAP_MARKEND;

	return result;
	}

  
//	
//Whats done here? 
//	Get the default system Calendar using GetList of CCalendarService and output that to GetListdefaultCalendar.txt
//       
TInt CTCalendarGetListTest::GetListTextFilter(CStifItemParser& /*aItem*/ )
	{
	TInt result = KErrNone;
	
	__UHEAP_MARK;
	
	CCalendarService* service = CCalendarService::NewL();
	
	RemoveCalendarFile( service, KTestCal1File );
	AddCalendarFile( service, KTestCal1File );


	CEntryAttributes* entryObj = CEntryAttributes::NewL(KEntryAppt);
	
	entryObj->SetDescriptionL(_L("SAPI weekly meeting"));
	entryObj->SetLocationL(_L("Hara"));
	entryObj->SetEntryStatusL(KStatusConfirmed);
	entryObj->SetMethodL(KMethodNone);
	entryObj->SetPriority(5);
    entryObj->SetSummaryL(_L("Meeting Happens from 9 to 9:30"));
    
    TCalTime stTime;
	stTime.SetTimeLocalL(TTime(TDateTime(2007, EAugust, 8, 9, 0, 0, 0)));
	entryObj->SetStartTimeL(TTime(TDateTime(2007, EAugust, 8, 9, 0, 0, 0)));
	
	TCalTime endTime;
	endTime.SetTimeLocalL(TTime(TDateTime(2007, EAugust, 8, 9, 30, 0, 0)));
	entryObj->SetEndTimeL(TTime(TDateTime(2007, EAugust, 8, 9, 30, 0, 0)));
	
	TUIDSet* uids = NULL;
	service->AddL(KTestCal1File,entryObj,uids);

	RPointerArray<TUIDSet> arruids(5);
	
	arruids.Append(uids);

	if ( arruids.Count() > 0 )
		{
	    RPointerArray<CCalInstance> instanceArray;

		CCalendarFilter *filter = CCalendarFilter::NewL();
		
		filter->SetFilterTextL( KSearchTexttest );
	     
	    TRAPD( err, service->GetListL( KTestCal1File, filter, instanceArray ));

	    if ( err == KErrNone )
	    	{ 
	    	if( !( instanceArray.Count() == 1 && instanceArray[0]->Entry().UidL().CompareF(*(arruids[0]->iGlobalUID)) == 0 ))
	    		{
	    		result = KErrGeneral;
	    		}
	    	}
	    else
	    	result = err;
	    
	    delete filter;
	    instanceArray.ResetAndDestroy();
	    arruids.ResetAndDestroy();
		}
	else
		result = KErrGeneral;	

	RemoveCalendarFile( service, KTestCal1File );
	
	delete service;
	delete entryObj;

	__UHEAP_MARKEND;

	return result;
    }
    

//	
//Whats done here? 
//	Get the default system Calendar using GetList of CCalendarService and output that to GetListdefaultCalendar.txt
//           
TInt CTCalendarGetListTest::GetListTypeFilter(CStifItemParser& /*aItem*/ )
	{
	TInt result = KErrNone;
	
	__UHEAP_MARK;
	
	CCalendarService* service = CCalendarService::NewL();
	
	RemoveCalendarFile( service, KTestCal1File );
	AddCalendarFile( service, KTestCal1File );

	RPointerArray<TUIDSet> arruids(5);
	
	TUIDSet* uids = NULL;
	
	if(AddAppointment(service, KTestCal1File, uids) == KErrNone && uids)
		{
		arruids.Append(uids);
		uids = NULL;
		}

	if ( arruids.Count() > 0 )
		{
	    RPointerArray<CCalInstance> instanceArray;

		CCalendarFilter *filter = CCalendarFilter::NewL();
		
		filter->SetFilterTypeL( KEntryAppt );
	     
	    TRAPD( err, service->GetListL( KTestCal1File, filter, instanceArray ));

	    if ( err == KErrNone )
	    	{ 
	    	if( instanceArray.Count() > 0 )
	    		{
	    		for(TInt index = 0; index < instanceArray.Count(); index++ )
	    			{
	    			if( instanceArray[index]->Entry().EntryTypeL() != CCalEntry::EAppt )
	    				{
	    				result = KErrGeneral;
	    				break;
	    				}
	    			}
	    		}
	    	else
	    		result = KErrGeneral;	
	    	}
	    else
	    	result = err;	
	    
   	    delete filter;
	    instanceArray.ResetAndDestroy();
	    arruids.ResetAndDestroy();
		}
	else
		result = KErrGeneral;	

	RemoveCalendarFile( service, KTestCal1File );
	
	delete service;

	__UHEAP_MARKEND;

	return result;
	}
	
	
//	
//Whats done here? 
//	Get the default system Calendar using GetList of CCalendarService and output that to GetListdefaultCalendar.txt
//       
TInt CTCalendarGetListTest::GetListInvalidCalName(CStifItemParser& /*aItem*/ )
	{
	TInt result = KErrNone;
	
	__UHEAP_MARK;

	CCalendarService *service = CCalendarService::NewL();
	
	RemoveCalendarFile( service, KTestCal1File );
	
	RPointerArray<CCalEntry> entryArray;
	
	TRAPD( err , service->GetListL( KTestCal1File, _L8("xyz"), entryArray ) );
	
	if(err != KErrNotFound)
		result = KErrGeneral;
	
	entryArray.ResetAndDestroy();
	
	delete service;
	
	__UHEAP_MARKEND;

	return result;
	}


//	
//Whats done here? 
//	Get the default system Calendar using GetList of CCalendarService and output that to GetListdefaultCalendar.txt
//       
TInt CTCalendarGetListTest::GetListInvalidGUID(CStifItemParser& /*aItem*/ )
	{
	TInt result = KErrNone;
	
	__UHEAP_MARK;

	CCalendarService *service = CCalendarService::NewL();
	
	AddCalendarFile( service, KTestCal1File );
	
	TUIDSet* uids = NULL;
	
	AddToDo( service, KTestCal1File, uids );
	
	delete uids;
	
	RPointerArray<CCalEntry> entryArray;
	
	TRAPD( err , service->GetListL( KTestCal1File, _L8("xyz"), entryArray ) );
	
	if(entryArray.Count() > 0)
		result = KErrGeneral;
	
	entryArray.ResetAndDestroy();
	
	RemoveCalendarFile( service, KTestCal1File );
	
	delete service;
	
	__UHEAP_MARKEND;

	return result;
	}	
	

//	
//Whats done here? 
//	Get the default system Calendar using GetList of CCalendarService and output that to GetListdefaultCalendar.txt
//       
TInt CTCalendarGetListTest::GetListInvalidLUID(CStifItemParser& /*aItem*/ )
	{
	TInt result = KErrNone;
	
	__UHEAP_MARK;

	CCalendarService *service = CCalendarService::NewL();
	
	AddCalendarFile( service, KTestCal1File );
	
	TUIDSet* uids = NULL;
	
	AddToDo( service, KTestCal1File, uids );
	
	delete uids;
	
	RPointerArray<CCalEntry> entryArray;
	
	TRAPD( err , service->GetListL( KTestCal1File, 0, entryArray ) );
	
	if(entryArray.Count() > 0)
		result = KErrGeneral;
	
	entryArray.ResetAndDestroy();
	
	RemoveCalendarFile( service, KTestCal1File );
	
	delete service;
	
	__UHEAP_MARKEND;

	return result;
	}		
	
	
/* Different Filter Types
EIncludeAppts Include timed appointments. 
 
EIncludeReminder Include appointments which only have a start time. 
 
EIncludeEvents Include all-day events. 
 
EIncludeAnnivs Include anniversaries. 
 
EIncludeCompletedTodos Include completed todos. 
 
EIncludeIncompletedTodos Include incompleted todos. 
 
EIncludeAlarmedOnly Remove non-alarmed entries. This flag cannot be used by itself. 
 
EIncludeRptsNextInstanceOnly Include next only instance of a repeat entry. 
 
EIncludeAll Include all entries (appointments, day events, anniversaries and todos).
*/
    
//  
//Whats done here? 
//  Get the default system Calendar using GetList of CCalendarService and output that to GetListdefaultCalendar.txt
//    
TInt CTCalendarGetListTest::GetListTimeRangeFilterAsync(CStifItemParser& /*aItem*/ )
    {
    TInt result = KErrNone;
   __UHEAP_MARK;
    
    CCalGetlistTestCases *calGetlistTest =  CCalGetlistTestCases::NewL(result);

    CleanupStack::PushL( calGetlistTest );

    calGetlistTest->TestGetlistTmRgFilterAsyncL();

    CleanupStack::PopAndDestroy( calGetlistTest );
    
    __UHEAP_MARKEND;
    return result;

    } 

TInt CTCalendarGetListTest::GetListGuidFilterAsync(CStifItemParser& /*aItem*/ )
    {
    TInt result = KErrNone;
   __UHEAP_MARK;
    
    CCalGetlistTestCases *calGetlistTest =  CCalGetlistTestCases::NewL(result);

   CleanupStack::PushL( calGetlistTest );

    calGetlistTest->TestGetlistGuidFilterAsyncL();

    CleanupStack::PopAndDestroy( calGetlistTest );
  //  delete calGetlistTest;
    
    __UHEAP_MARKEND;
    return result;

    } 
TInt CTCalendarGetListTest::GetListLuidFilterAsync(CStifItemParser& /*aItem*/ )
    {
    TInt result = KErrNone;
   __UHEAP_MARK;
    
    CCalGetlistTestCases *calGetlistTest =  CCalGetlistTestCases::NewL(result);

    CleanupStack::PushL( calGetlistTest );

    calGetlistTest->TestGetlistLuidFilterAsyncL();

    CleanupStack::PopAndDestroy( calGetlistTest );
    
    __UHEAP_MARKEND;
    return result;

    } 
TInt CTCalendarGetListTest::GetListTextFilterAsync(CStifItemParser& /*aItem*/ )
    {
    TInt result = KErrNone;
   __UHEAP_MARK;
    
    CCalGetlistTestCases *calGetlistTest =  CCalGetlistTestCases::NewL(result);

    CleanupStack::PushL( calGetlistTest );

    calGetlistTest->TestGetlistTextFilterAsyncL();

    CleanupStack::PopAndDestroy( calGetlistTest );
    
    __UHEAP_MARKEND;
    return result;

    } 
TInt CTCalendarGetListTest::GetListTypeFilterAsync(CStifItemParser& /*aItem*/ )
    {
    TInt result = KErrNone;
   __UHEAP_MARK;
    
    CCalGetlistTestCases *calGetlistTest =  CCalGetlistTestCases::NewL(result);

    CleanupStack::PushL( calGetlistTest );

    calGetlistTest->TestGetlistTypeFilterAsyncL();

    CleanupStack::PopAndDestroy( calGetlistTest );
    
    __UHEAP_MARKEND;
    return result;

    } 
TInt CTCalendarGetListTest::GetListInvalidGuidFilterAsync(CStifItemParser& /*aItem*/ )
    {
    TInt result = KErrNone;
   __UHEAP_MARK;
    
    CCalGetlistTestCases *calGetlistTest =  CCalGetlistTestCases::NewL(result);

    CleanupStack::PushL( calGetlistTest );

    calGetlistTest->TestGetlistInvalidGuidFilterAsyncL();

    CleanupStack::PopAndDestroy( calGetlistTest );
    
    __UHEAP_MARKEND;
    return result;

    } 
TInt CTCalendarGetListTest::GetListInvalidLuidFilterAsync(CStifItemParser& /*aItem*/ )
    {
    TInt result = KErrNone;
   __UHEAP_MARK;
    
    CCalGetlistTestCases *calGetlistTest =  CCalGetlistTestCases::NewL(result);

    CleanupStack::PushL( calGetlistTest );

    calGetlistTest->TestGetlistInvalidLuidFilterAsyncL();

    CleanupStack::PopAndDestroy( calGetlistTest );
    
    __UHEAP_MARKEND;
    return result;

    } 
