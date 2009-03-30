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
#include <StifParser.h>
#include <Stiftestinterface.h>

#include "calendarheader.h"
#include "calendarservice.h"
#include "entryattributes.h"
#include <caluser.h>
#include <calalarm.h>
#include <calrrule.h>
#include "calendarconstants.h"
#include "tcalendaraddtest.h"
#include "teststartconsolealarmserver.h"
_LIT(KTestCal1File                ,"C:updatecalfile1");
_LIT(KTestCal2File                ,"C:updatecalfile2");
_LIT(KString1                ,"New reminder");

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTChangeStatusTest::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTCalendarAddTest::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CTChangeStatusTest::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTCalendarAddTest::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
                
        ENTRY( "AddAppointmentEntry",    	CTCalendarAddTest::AddAppointmentEntryL),
        ENTRY( "AddTodoEntry",       CTCalendarAddTest::AddTodoEntryL),
        ENTRY( "AddAnniversary",       CTCalendarAddTest::AddAnniversaryL),
        ENTRY( "AddDayEvent",       CTCalendarAddTest::AddDayEventL),
        ENTRY( "AddReminder",       CTCalendarAddTest::AddReminderL),
        ENTRY( "AddDailyAppointmentEntry",    	CTCalendarAddTest::AddDailyAppointmentEntryL),
        ENTRY( "AddWeeklyAppointmentEntry",    	CTCalendarAddTest::AddWeeklyAppointmentEntryL),
        ENTRY( "AddMonthlyAppointmentEntry",    	CTCalendarAddTest::AddMonthlyAppointmentEntryL),
        //ENTRY( "AddYearlyAppointmentEntry",    	CTCalendarAddTest::AddYearlyAppointmentEntryL),
        ENTRY( "AddAppointmentEntryWithAttendees",    	CTCalendarAddTest::AddAppointmentEntryWithAttendeesL),
        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }
/*
1. Add entries of all types
2. Add repeating appt
3. Add repeating appt with exception date and repeat date

*/

	
TInt CTCalendarAddTest::AddDailyAppointmentEntryL(CStifItemParser &aItem )
		{
    /*__UHEAP_MARK;
	
	CEntryAttributes* entryObj = CEntryAttributes::NewL( KEntryAppt );
	
    entryObj->SetDescriptionL(_L("SAPI weekly meeting"));
	entryObj->SetLocationL(_L("Hara"));
	entryObj->SetEntryStatusL(KStatusConfirmed	);
	
	entryObj->SetMethodL(KMethodNone);
	//CleanupStack::PopAndDestroy(organizer);
	//CCalUser* owner = CCalUser::NewL(_L(""));
		
	entryObj->SetPriority(5);
    entryObj->SetSummaryL(_L("Repeating entry"));
    
    TTime stTime(TDateTime(2007, ESeptember, 15, 9, 0, 0, 0));
	entryObj->SetStartTimeL(stTime);
	
	TTime endTime(TDateTime(2007, ESeptember, 15, 9, 30, 0, 0));
	entryObj->SetEndTimeL(endTime);
	
	CCalAlarm* alarm = CCalAlarm::NewL();
	TTime alarmTime(TDateTime(2007,ESeptember, 15, 7, 30, 0, 0));
	//entryObj->SetAlarm(alarmTime);
	delete alarm;
	
    TCalRRule rrule(TCalRRule::EMonthly);
	rrule.SetDtStart(stTime);
	TCalTime uTime;
	uTime.SetTimeLocalL(TTime(TDateTime(2007, EDecember, 30, 0, 0, 0, 0)));
	rrule.SetUntil(uTime);
	
	TCalRRule::TDayOfMonth day1(EMonday,1);
	TCalRRule::TDayOfMonth day2(EWednesday,3);
	
	
	
	RArray<TCalRRule::TDayOfMonth> monthDays;
	monthDays.Append(day1);
	monthDays.Append(day2);
	rrule.SetByDay(monthDays);
	
	entryObj->SetRepeatRule(rrule);
	monthDays.Close();
	
	CRepeatInfo* rrule = CRepeatInfo::NewL(1);    
    rrule->SetStartTimeL(stTime);
	TTime uTime(TDateTime(2007, ESeptember, 29, 0, 0, 0, 0));
	rrule->SetUntilTimeL(uTime);
	rrule->SetWeekStart(2);
	entryObj->SetRepeatRule(rrule);
	delete rrule;	
	
	TTime exDate(TDateTime(2007, ESeptember, 20, 0, 0, 0, 0)); 
    entryObj->AddExceptionDateL(exDate);
        
    TTime rDate(TDateTime(2007, EOctober, 0, 9, 0, 0, 0)); 
    entryObj->AddRepeatDateL(exDate);
        
	
	CCalendarService* service;
	TRAPD( err, service = CCalendarService::NewL() );
	
	TUIDSet* uids = NULL;
		
	TRAPD( errno, service->AddL(KNullDesC,entryObj,uids) );
	
    delete uids;
    delete entryObj;    
    delete service;
	__UHEAP_MARKEND;
	return errno;*/
	
	
	__UHEAP_MARK;
	
	CCalendarService* service = CCalendarService::NewL();


	
	CEntryAttributes* entryObj = CEntryAttributes::NewL( KEntryAppt );
	
    entryObj->SetDescriptionL(_L("SAPI weekly meeting"));
	entryObj->SetLocationL(_L("Hara"));
	entryObj->SetEntryStatusL(KStatusConfirmed	);
	
	entryObj->SetMethodL(KMethodNone);
	//CleanupStack::PopAndDestroy(organizer);
	//CCalUser* owner = CCalUser::NewL(_L(""));
		
	entryObj->SetPriority(5);
    entryObj->SetSummaryL(_L("Repeating entry"));
    
    TTime stTime(TDateTime(2007, EJune, 15, 9, 0, 0, 0));
	entryObj->SetStartTimeL(stTime);
	
	TTime endTime(TDateTime(2007, EJune, 15, 9, 30, 0, 0));
	entryObj->SetEndTimeL(endTime);
	
	CCalAlarm* alarm = CCalAlarm::NewL();
	TTime alarmTime(TDateTime(2007,EJune, 15, 7, 30, 0, 0));
	//entryObj->SetAlarm(alarmTime);
	delete alarm;
	
	/*CRepeatInfo* rrule = CRepeatInfo::NewL(2);    
    rrule->SetStartTimeL(stTime);
	TTime uTime(TDateTime(2007, EJuly, 29, 0, 0, 0, 0));*/
	
	CRepeatInfo* rrule = CRepeatInfo::NewL(1);    
    rrule->SetStartTimeL(stTime);
	TTime uTime(TDateTime(2007, EJune, 29, 0, 0, 0, 0));
	
	rrule->SetUntilTimeL(uTime);
	RArray<TDay> days;
	days.Append(ESaturday);
	//days.Append(EFriday);
	rrule->SetDaysInWeek(days);
	days.Close();
	
	entryObj->SetRepeatRule(rrule);	
	delete rrule;
	
	TUIDSet* uids = NULL;
		
	TRAPD( errno, service->AddL(KNullDesC,entryObj,uids) );
	
    delete uids;
    delete entryObj;       
    delete service;
	__UHEAP_MARKEND;
	return errno;
	

    }

TInt CTCalendarAddTest::AddWeeklyAppointmentEntryL(CStifItemParser &aItem )
	{
	/*__UHEAP_MARK;
	
	CEntryAttributes* entryObj = CEntryAttributes::NewL( KEntryAppt );
	
    entryObj->SetDescriptionL(_L("SAPI weekly meeting"));
	entryObj->SetLocationL(_L("Hara"));
	entryObj->SetEntryStatusL(KStatusConfirmed	);
	
	entryObj->SetMethodL(KMethodNone);
	//CleanupStack::PopAndDestroy(organizer);
	//CCalUser* owner = CCalUser::NewL(_L(""));
		
	entryObj->SetPriority(5);
    entryObj->SetSummaryL(_L("Repeating entry"));
    
    TTime stTime(TDateTime(2007, EJune, 15, 9, 0, 0, 0));
	entryObj->SetStartTimeL(stTime);
	
	TTime endTime(TDateTime(2007, EJune, 15, 9, 30, 0, 0));
	entryObj->SetEndTimeL(endTime);
	
	CCalAlarm* alarm = CCalAlarm::NewL();
	TTime alarmTime(TDateTime(2007,EJune, 15, 7, 30, 0, 0));
	//entryObj->SetAlarm(alarmTime);
	delete alarm;
	
	CRepeatInfo* rrule = CRepeatInfo::NewL(2);    
    rrule->SetStartTimeL(stTime);
	TTime uTime(TDateTime(2007, EJuly, 29, 0, 0, 0, 0));
	rrule->SetUntilTimeL(uTime);
	RArray<TDay> days;
	days.Append(EWednesday);
	days.Append(EFriday);
	rrule->SetDaysInWeek(days);
	days.Close();
	
	entryObj->SetRepeatRule(rrule);	
	delete rrule;
	
	CCalendarService* service;
	TRAPD( err, service = CCalendarService::NewL() );
	
	TUIDSet* uids = NULL;
		
	TRAPD( errno, service->AddL(KNullDesC,entryObj,uids) );
	
    delete uids;
    delete entryObj;       
    delete service;
	__UHEAP_MARKEND;
	return errno;*/
	
	TInt result = KErrNone;
	
	__UHEAP_MARK;
	
	CCalendarService* service = CCalendarService::NewL();

	RemoveCalendarFile( service, KTestCal1File );
	AddCalendarFile( service, KTestCal1File );

	RPointerArray<TUIDSet> arruids(5);
	
	TUIDSet* uids = NULL;

	CEntryAttributes* entryObj = CEntryAttributes::NewL( KEntryAppt );
	
    entryObj->SetDescriptionL(_L("SAPI weekly meeting"));
	entryObj->SetLocationL(_L("Hara"));
	entryObj->SetEntryStatusL(KStatusConfirmed	);
	
	entryObj->SetMethodL(KMethodNone);
	//CleanupStack::PopAndDestroy(organizer);
	//CCalUser* owner = CCalUser::NewL(_L(""));
		
	entryObj->SetPriority(5);
    entryObj->SetSummaryL(_L("Repeating entry"));
    
    TTime stTime(TDateTime(2007, EJune, 15, 9, 0, 0, 0));
	entryObj->SetStartTimeL(stTime);
	
	TTime endTime(TDateTime(2007, EJune, 15, 9, 30, 0, 0));
	entryObj->SetEndTimeL(endTime);
	
	CCalAlarm* alarm = CCalAlarm::NewL();
	TTime alarmTime(TDateTime(2007,EJune, 15, 7, 30, 0, 0));
	//entryObj->SetAlarm(alarmTime);
	delete alarm;
	
	CRepeatInfo* rrule = CRepeatInfo::NewL(2);    
    rrule->SetStartTimeL(stTime);
	TTime uTime(TDateTime(2007, EJuly, 29, 0, 0, 0, 0));
	rrule->SetUntilTimeL(uTime);
	RArray<TDay> days;
	days.Append(EWednesday);
	days.Append(EFriday);
	rrule->SetDaysInWeek(days);
	days.Close();
	
	entryObj->SetRepeatRule(rrule);	
	delete rrule;
	
	TRAPD( errno, service->AddL(KTestCal1File,entryObj,uids) );	

	if(errno == KErrNone && uids)
		{
		arruids.Append(uids);
		uids = NULL;
		}

	if ( arruids.Count() > 0 )
		{
		RPointerArray<CCalEntry> entryArray;
    	service->GetListL( KTestCal1File, arruids[0]->iLocalUID , entryArray );
    	if( entryArray.Count() == 1 )
    		{
    		TCalRRule rRule;
    		entryArray[0]->GetRRuleL( rRule );
    		TCalTime utTime;
			utTime.SetTimeUtcL(TTime(TDateTime(2007, EJuly, 26, 9, 0, 0, 0)));

    		if( !( entryArray[0]->DescriptionL().CompareF(_L("SAPI weekly meeting")) == 0
    		                            &&rRule.Type() == TCalRRule::EWeekly ) )
	    		{
	    		result = KErrGeneral;	
	    		}
	    	}
	    
        else
	        {
	        result = KErrGeneral;		
	        }
		entryArray.ResetAndDestroy();
	    arruids.ResetAndDestroy();
	    delete entryObj;
	    }
		else
			result = KErrGeneral;	

	RemoveCalendarFile( service, KTestCal1File );
	
	delete service;
	
	__UHEAP_MARKEND;

	return result;


    }    
TInt CTCalendarAddTest::AddMonthlyAppointmentEntryL(CStifItemParser &aItem )
	{
	/*__UHEAP_MARK;
	
	CEntryAttributes* entryObj = CEntryAttributes::NewL( KEntryAppt );
	
    entryObj->SetDescriptionL(_L("SAPI weekly meeting"));
	entryObj->SetLocationL(_L("Hara"));
	entryObj->SetEntryStatusL(KStatusConfirmed	);
	
	entryObj->SetMethodL(KMethodNone);
		
	entryObj->SetPriority(5);
    entryObj->SetSummaryL(_L("Repeating entry"));
    
    TTime stTime(TDateTime(2007, ESeptember, 15, 9, 0, 0, 0));
	entryObj->SetStartTimeL(stTime);
	
	TTime endTime(TDateTime(2007, ESeptember, 15, 9, 30, 0, 0));
	entryObj->SetEndTimeL(endTime);
	
	CCalAlarm* alarm = CCalAlarm::NewL();
	TTime alarmTime(TDateTime(2007,ESeptember, 15, 7, 30, 0, 0));
	//entryObj->SetAlarm(alarmTime);
	delete alarm;
	
	CRepeatInfo* rrule = CRepeatInfo::NewL(3);    
    rrule->SetStartTimeL(stTime);
	TTime uTime(TDateTime(2007, EDecember, 30, 0, 0, 0, 0));
	rrule->SetUntilTimeL(uTime);
	TCalRRule::TDayOfMonth day1(EMonday,1);
	TCalRRule::TDayOfMonth day2(EWednesday,3);
	RArray<TCalRRule::TDayOfMonth> monthDays;
	monthDays.Append(day1);
	monthDays.Append(day2);
	rrule->SetMonthDays(monthDays);
	monthDays.Close();
	
	entryObj->SetRepeatRule(rrule);	
	delete rrule;
	
	CCalendarService* service;
	TRAPD( err, service = CCalendarService::NewL() );
	
	TUIDSet* uids = NULL;
		
	TRAPD( errno, service->AddL(KNullDesC,entryObj,uids) );
	
    delete uids;
    delete entryObj;       
    delete service;
	__UHEAP_MARKEND;
	return errno;*/
	TInt result = KErrNone;
	
	__UHEAP_MARK;
	
	CCalendarService* service = CCalendarService::NewL();

	RemoveCalendarFile( service, KTestCal1File );
	AddCalendarFile( service, KTestCal1File );

	RPointerArray<TUIDSet> arruids(5);
	
	TUIDSet* uids = NULL;

	CEntryAttributes* entryObj = CEntryAttributes::NewL( KEntryAppt );
	
    entryObj->SetDescriptionL(_L("SAPI weekly meeting"));
	entryObj->SetLocationL(_L("Hara"));
	entryObj->SetEntryStatusL(KStatusConfirmed	);
	
	entryObj->SetMethodL(KMethodNone);
		
	entryObj->SetPriority(5);
    entryObj->SetSummaryL(_L("Repeating entry"));
    
    TTime stTime(TDateTime(2007, ESeptember, 15, 9, 0, 0, 0));
	entryObj->SetStartTimeL(stTime);
	
	TTime endTime(TDateTime(2007, ESeptember, 15, 9, 30, 0, 0));
	entryObj->SetEndTimeL(endTime);
	
	CCalAlarm* alarm = CCalAlarm::NewL();
	TTime alarmTime(TDateTime(2007,ESeptember, 15, 7, 30, 0, 0));
	//entryObj->SetAlarm(alarmTime);
	delete alarm;
	
	CRepeatInfo* rrule = CRepeatInfo::NewL(3);    
    rrule->SetStartTimeL(stTime);
	TTime uTime(TDateTime(2007, EDecember, 30, 0, 0, 0, 0));
	rrule->SetUntilTimeL(uTime);
	TCalRRule::TDayOfMonth day1(EMonday,1);
	TCalRRule::TDayOfMonth day2(EWednesday,3);
	RArray<TCalRRule::TDayOfMonth> monthDays;
	monthDays.Append(day1);
	monthDays.Append(day2);
	rrule->SetMonthDays(monthDays);
	monthDays.Close();
	
	entryObj->SetRepeatRule(rrule);	
	delete rrule;
	
	TRAPD( errno, service->AddL(KTestCal1File,entryObj,uids) );	

	if(errno == KErrNone && uids)
		{
		arruids.Append(uids);
		uids = NULL;
		}

	if ( arruids.Count() > 0 )
		{
		RPointerArray<CCalEntry> entryArray;
    	service->GetListL( KTestCal1File, arruids[0]->iLocalUID , entryArray );
    	if( entryArray.Count() == 1 )
    		{
    		TCalRRule rRule;
    		entryArray[0]->GetRRuleL( rRule );
    		TCalTime utTime;
			utTime.SetTimeUtcL(TTime(TDateTime(2007, EDecember, 18, 9, 0, 0, 0)));

    		if( !( entryArray[0]->DescriptionL().CompareF(_L("SAPI weekly meeting")) == 0
    		                            &&rRule.Type() == TCalRRule::EMonthly  ) )
	    		{
	    		result = KErrGeneral;	
	    		}
	    	}
	    
        else
	        {
	        result = KErrGeneral;		
	        }
		entryArray.ResetAndDestroy();
	    arruids.ResetAndDestroy();
	    delete entryObj;
	    }
		else
			result = KErrGeneral;	

	RemoveCalendarFile( service, KTestCal1File );
	
	delete service;
	
	__UHEAP_MARKEND;

	return result;


    }

TInt CTCalendarAddTest::AddTodoEntryL(CStifItemParser &aItem )
	{
	/*__UHEAP_MARK;
	CEntryAttributes* entryObj = CEntryAttributes::NewL( KEntryTodo );
	
	entryObj->SetDescriptionL(_L("New todo entry created"));
	entryObj->SetSummaryL(_L("TODO Entry"));
	
	TTime endTime(TDateTime(2007, EAugust, 21, 0, 0, 0, 0));
	entryObj->SetEndTimeL(endTime);
	entryObj->SetReplicationL(KReplOpen);
	entryObj->SetPriority(0);	
	
	TBuf<15> defaultfile(_L("C:Calendar"));
	TPtrC ptr(defaultfile);
	
	CCalendarService* service;
	TRAPD( err, service = CCalendarService::NewL() );
	
	TUIDSet* uids = NULL;
		
	TRAPD( errno, service->AddL(ptr,entryObj,uids) );
	
    delete uids;
    delete entryObj;       
    delete service;
	__UHEAP_MARKEND;
	return errno;*/
	
	TInt result = KErrNone;
	
	__UHEAP_MARK;
	
	CCalendarService* service = CCalendarService::NewL();

	RemoveCalendarFile( service, KTestCal1File );
	AddCalendarFile( service, KTestCal1File );

	RPointerArray<TUIDSet> arruids(5);
	
	TUIDSet* uids = NULL;

	CEntryAttributes* entryObj = CEntryAttributes::NewL( KEntryTodo );
	
	entryObj->SetDescriptionL(_L("New todo entry created"));
	entryObj->SetSummaryL(_L("TODO Entry"));
	
	TTime endTime(TDateTime(2007, EAugust, 21, 0, 0, 0, 0));
	entryObj->SetEndTimeL(endTime);
	entryObj->SetReplicationL(KReplOpen);
	entryObj->SetPriority(0);	
	entryObj->SetReplicationL(KReplPrivate);
	
	TRAPD( errno, service->AddL(KTestCal1File,entryObj,uids) );	

	if(errno == KErrNone && uids)
		{
		arruids.Append(uids);
		uids = NULL;
		}

	if ( arruids.Count() > 0 )
		{
		RPointerArray<CCalEntry> entryArray;
    	service->GetListL( KTestCal1File, arruids[0]->iLocalUID , entryArray );
    	if( entryArray.Count() == 1 )
    		{
    		if( !( entryArray[0]->EndTimeL().TimeUtcL() == endTime  && entryArray[0]->DescriptionL().CompareF(_L("New todo entry created")) == 0
    		                                                           && entryArray[0]->SummaryL().CompareF(_L("TODO Entry")) == 0  ) )
	    		{
	    		result = KErrGeneral;	
	    		}
	    	}
	    
        else
	        {
	        result = KErrGeneral;		
	        }
		entryArray.ResetAndDestroy();
	    arruids.ResetAndDestroy();
	    delete entryObj;
	    }
		else
			result = KErrGeneral;	

	RemoveCalendarFile( service, KTestCal1File );
	
	delete service;
	
	__UHEAP_MARKEND;

	return result;

	
	}

TInt CTCalendarAddTest::AddAppointmentEntryL(CStifItemParser &aItem )
	{
	/*__UHEAP_MARK;
	
	CEntryAttributes* entryObj = CEntryAttributes::NewL( KEntryAppt );
	
	entryObj->SetDescriptionL(_L("SAPI weekly meeting"));
	entryObj->SetLocationL(_L("Hara"));
	entryObj->SetEntryStatusL(KStatusConfirmed);

	entryObj->SetMethodL(KMethodNone);
	
	entryObj->SetPriority(5);
    entryObj->SetSummaryL(_L("Happens from 9 to 9:30"));
    
    TTime stTime(TDateTime(2007, EAugust, 8, 9, 0, 0, 0));
	entryObj->SetStartTimeL(stTime);
	
	TTime endTime(TDateTime(2007, EAugust, 8, 9, 30, 0, 0));
	entryObj->SetEndTimeL(endTime);
	
	CCalAlarm* alarm = CCalAlarm::NewL();
	TTime alarmTime(TDateTime(2007,EAugust, 8, 7, 30, 0, 0));
	//entryObj->SetAlarm(alarmTime);
	delete alarm;
	
	TBuf<15> defaultfile(_L("C:Calendar"));
	TPtrC ptr(defaultfile);
	
	CCalendarService* service;
	TRAPD( err, service = CCalendarService::NewL() );
	
	TUIDSet* uids = NULL;
		
	TRAPD( errno, service->AddL(ptr,entryObj,uids) );
	
	delete uids;
    delete entryObj;       
    delete service;
	__UHEAP_MARKEND;
	return errno;*/
    TInt result = KErrNone;
	
	__UHEAP_MARK;
	
	CCalendarService* service = CCalendarService::NewL();

	RemoveCalendarFile( service, KTestCal1File );
	AddCalendarFile( service, KTestCal1File );

	RPointerArray<TUIDSet> arruids(5);
	
	TUIDSet* uids = NULL;

	CEntryAttributes* entryObj = CEntryAttributes::NewL( KEntryAppt );
	
	entryObj->SetDescriptionL(_L("SAPI weekly meeting"));
	entryObj->SetLocationL(_L("Hara"));
	entryObj->SetEntryStatusL(KStatusConfirmed);

	entryObj->SetMethodL(KMethodNone);
	
	entryObj->SetPriority(5);
    entryObj->SetSummaryL(_L("Happens from 9 to 9:30"));
    
    TTime stTime(TDateTime(2007, EAugust, 8, 9, 0, 0, 0));
	entryObj->SetStartTimeL(stTime);
	
	TTime endTime(TDateTime(2007, EAugust, 8, 9, 30, 0, 0));
	entryObj->SetEndTimeL(endTime);
	
	CCalAlarm* alarm = CCalAlarm::NewL();
	TTime alarmTime(TDateTime(2007,EAugust, 8, 7, 30, 0, 0));
	//entryObj->SetAlarm(alarmTime);
	delete alarm;
	
	TRAPD( errno, service->AddL(KTestCal1File,entryObj,uids) );	

	if(errno == KErrNone && uids)
		{
		arruids.Append(uids);
		uids = NULL;
		}

	if ( arruids.Count() > 0 )
		{
		RPointerArray<CCalEntry> entryArray;
    	service->GetListL( KTestCal1File, arruids[0]->iLocalUID , entryArray );
    	if( entryArray.Count() == 1 )
    		{
    		if( !( entryArray[0]->StartTimeL().TimeUtcL() == stTime  && entryArray[0]->DescriptionL().CompareF(_L("SAPI weekly meeting")) == 0
    		                                                           && entryArray[0]->LocationL().CompareF(_L("Hara")) == 0  ) )
	    		{
	    		result = KErrGeneral;	
	    		}
	    	}
	    
        else
	        {
	        result = KErrGeneral;		
	        }
		entryArray.ResetAndDestroy();
	    arruids.ResetAndDestroy();
	    delete entryObj;
	    }
		else
			result = KErrGeneral;	

	RemoveCalendarFile( service, KTestCal1File );
	
	delete service;
	
	__UHEAP_MARKEND;

	return result;


    }
    
TInt CTCalendarAddTest::AddAppointmentEntryWithAttendeesL(CStifItemParser &aItem )
	{
	/*__UHEAP_MARK;
	
	CEntryAttributes* entryObj = CEntryAttributes::NewL( KEntryAppt );
	
	entryObj->SetDescriptionL(_L("SAPI weekly meeting"));
	entryObj->SetLocationL(_L("Hara"));
	entryObj->SetEntryStatusL(KStatusConfirmed);

	entryObj->SetMethodL(KMethodNone);
	
	CAttendeeInfo* organizer = CAttendeeInfo::NewL(_L(""));
	CleanupStack::PushL(organizer);
	organizer->SetCommonNameL(_L("SAPI"));
	entryObj->SetOrganizerDataL(organizer);
	CleanupStack::PopAndDestroy(organizer);
	
	entryObj->SetPhoneOwnerDataL(_L(""));
	
	entryObj->SetPriority(5);
    entryObj->SetSummaryL(_L("Happens from 9 to 9:30"));
    
    TTime stTime(TDateTime(2007, EAugust, 8, 9, 0, 0, 0));
	entryObj->SetStartTimeL(stTime);
	
	TTime endTime(TDateTime(2007, EAugust, 8, 9, 30, 0, 0));
	entryObj->SetEndTimeL(endTime);
	
	CCalAlarm* alarm = CCalAlarm::NewL();
	TTime alarmTime(TDateTime(2007,EAugust, 8, 7, 30, 0, 0));
	//entryObj->SetAlarm(alarmTime);
	delete alarm;
	
    CAttendeeInfo* attendee = CAttendeeInfo::NewL(_L(""));
    CleanupStack::PushL(attendee);
	attendee->SetRoleL(KAttRoleReqParticipant);
	attendee->SetStatusL(KAttStatusTentative);
    attendee->SetRsvp(EFalse);
    
	entryObj->AddAttendeeL(attendee);
	CleanupStack::PopAndDestroy(attendee);
	
	attendee = CAttendeeInfo::NewL(_L(""));
	CleanupStack::PushL(attendee);
	attendee->SetCommonNameL(_L("SAPI"));
	attendee->SetRoleL(KAttRoleReqParticipant);
	attendee->SetStatusL(KAttStatusTentative);
    attendee->SetRsvp(EFalse);
    
	entryObj->AddAttendeeL(attendee);
	CleanupStack::PopAndDestroy(attendee);
	
  	TBuf<15> defaultfile(_L("C:Calendar"));
	TPtrC ptr(defaultfile);
	
	CCalendarService* service;
	TRAPD( err, service = CCalendarService::NewL() );
	
	TUIDSet* uids = NULL;
		
	TRAPD( errno, service->AddL(ptr,entryObj,uids) );
	
	delete uids;
    delete entryObj;       
    delete service;
	__UHEAP_MARKEND;
	return errno;*/
    TInt result = KErrNone;
	
	__UHEAP_MARK;
	
	CCalendarService* service = CCalendarService::NewL();

	RemoveCalendarFile( service, KTestCal1File );
	AddCalendarFile( service, KTestCal1File );

	RPointerArray<TUIDSet> arruids(5);
	
	TUIDSet* uids = NULL;

	CEntryAttributes* entryObj = CEntryAttributes::NewL( KEntryAppt );
	
	entryObj->SetDescriptionL(_L("SAPI weekly meeting"));
	entryObj->SetLocationL(_L("Hara"));
	entryObj->SetEntryStatusL(KStatusConfirmed);

	entryObj->SetMethodL(KMethodNone);
	
	CAttendeeInfo* organizer = CAttendeeInfo::NewL(_L("mcrasta@gmail.com"));
	CleanupStack::PushL(organizer);
	organizer->SetCommonNameL(_L("SAPI"));
	entryObj->SetOrganizerDataL(organizer);
	CleanupStack::PopAndDestroy(organizer);
	
	entryObj->SetPhoneOwnerDataL(_L("h2s@gmail.com"));
	
	entryObj->SetPriority(5);
    entryObj->SetSummaryL(_L("Happens from 9 to 9:30"));
    
    TTime stTime(TDateTime(2007, EAugust, 8, 9, 0, 0, 0));
	entryObj->SetStartTimeL(stTime);
	
	TTime endTime(TDateTime(2007, EAugust, 8, 9, 30, 0, 0));
	entryObj->SetEndTimeL(endTime);
	
	CCalAlarm* alarm = CCalAlarm::NewL();
	TTime alarmTime(TDateTime(2007,EAugust, 8, 7, 30, 0, 0));
	//entryObj->SetAlarm(alarmTime);
	delete alarm;
	
    CAttendeeInfo* attendee = CAttendeeInfo::NewL(_L("h2s@gmail.com"));
    CleanupStack::PushL(attendee);
	attendee->SetRoleL(KAttRoleReqParticipant);
	attendee->SetStatusL(KAttStatusTentative);
    attendee->SetRsvp(EFalse);
    
	entryObj->AddAttendeeL(attendee);
	CleanupStack::PopAndDestroy(attendee);
	
	attendee = CAttendeeInfo::NewL(_L("mdcosta@gmail.com"));
	CleanupStack::PushL(attendee);
	attendee->SetCommonNameL(_L("SAPI"));
	attendee->SetRoleL(KAttRoleReqParticipant);
	attendee->SetStatusL(KAttStatusTentative);
    attendee->SetRsvp(EFalse);
    
	entryObj->AddAttendeeL(attendee);
	CleanupStack::PopAndDestroy(attendee);
	
	TRAPD( errno, service->AddL(KTestCal1File,entryObj,uids) );	

	if(errno == KErrNone && uids)
		{
		arruids.Append(uids);
		uids = NULL;
		}

	if ( arruids.Count() > 0 )
		{
		RPointerArray<CCalEntry> entryArray;
    	service->GetListL( KTestCal1File, arruids[0]->iLocalUID , entryArray );
    	if( entryArray.Count() == 1 )
    		{
    		RPointerArray<CCalAttendee> attendeeList;
    		attendeeList = entryArray[0]->AttendeesL(); 
    		
    		if( !( entryArray[0]->StartTimeL().TimeUtcL() == stTime  && entryArray[0]->DescriptionL().CompareF(_L("SAPI weekly meeting")) == 0
    		                                                           &&  attendeeList.Count() == 2 ) )
	    		{
	    		result = KErrGeneral;	
	    		}
	    	}
	    
        else
	        {
	        result = KErrGeneral;		
	        }
		entryArray.ResetAndDestroy();
	    arruids.ResetAndDestroy();
	    delete entryObj;
	    }
		else
			result = KErrGeneral;	

	RemoveCalendarFile( service, KTestCal1File );
	
	delete service;
	
	__UHEAP_MARKEND;

	return result;
	

    }
    
TInt CTCalendarAddTest::AddAnniversaryL(CStifItemParser &aItem )
	{
	/*__UHEAP_MARK;
	
	CEntryAttributes* entryObj = CEntryAttributes::NewL( KEntryAnniv );
	
	entryObj->SetDescriptionL(_L("New Anniversary entry created"));
	entryObj->SetSummaryL(_L("Anniv Entry"));
	
	TTime stTime(TDateTime(2007, EDecember, 30, 0, 0, 0, 0));
	entryObj->SetStartTimeL(stTime);
	
	entryObj->SetReplicationL(KReplPrivate);	
	
	TCalRRule rrule(TCalRRule::EYearly);
	TCalTime startTime;
	startTime.SetTimeLocalFloatingL( stTime );
	rrule.SetDtStart(startTime);
	//rrule.SetInterval(1);
	
	TCalTime uTime;
	uTime.SetTimeLocalFloatingL(TCalTime::MaxTime());
	rrule.SetUntil(uTime);
	entryObj->SetRepeatRule(rrule);
	
	TBuf<15> defaultfile(_L("C:Calendar"));
	TPtrC ptr(defaultfile);
	
	CCalendarService* service;
	TRAPD( err, service = CCalendarService::NewL() );
	
	TUIDSet* uids = NULL;
		
	TRAPD( errno, service->AddL(ptr,entryObj,uids) );
	
    delete uids;
    delete entryObj;   
          
    delete service;
	__UHEAP_MARKEND;
	return errno;*/
	
    TInt result = KErrNone;
	
	__UHEAP_MARK;
	
	CCalendarService* service = CCalendarService::NewL();

	RemoveCalendarFile( service, KTestCal1File );
	AddCalendarFile( service, KTestCal1File );

	RPointerArray<TUIDSet> arruids(5);
	
	TUIDSet* uids = NULL;

	CEntryAttributes* entryObj = CEntryAttributes::NewL( KEntryAnniv );
	
	entryObj->SetDescriptionL(_L("New Anniversary entry created"));
	entryObj->SetSummaryL(_L("Anniv Entry"));
	
	TTime stTime(TDateTime(2007, EDecember, 27, 0, 0, 0, 0));
	entryObj->SetStartTimeL(stTime);
	
	entryObj->SetReplicationL(KReplPrivate);
	
	TRAPD( errno, service->AddL(KTestCal1File,entryObj,uids) );	

	if(errno == KErrNone && uids)
		{
		arruids.Append(uids);
		uids = NULL;
		}

	if ( arruids.Count() > 0 )
		{
		RPointerArray<CCalEntry> entryArray;
    	service->GetListL( KTestCal1File, arruids[0]->iLocalUID , entryArray );
    	if( entryArray.Count() == 1 )
    		{
    		TDateTime tm = entryArray[0]->StartTimeL().TimeLocalL().DateTime();
    		TDateTime tm1 = stTime.DateTime();
    		if( !( entryArray[0]->StartTimeL().TimeUtcL() == stTime  && entryArray[0]->DescriptionL().CompareF(_L("New Anniversary entry created")) == 0
    		                                                           && entryArray[0]->SummaryL().CompareF(_L("Anniv Entry")) == 0  ) )
	    		{
	    		result = KErrGeneral;	
	    		}
	    	}
	    
        else
	        {
	        result = KErrGeneral;		
	        }
		entryArray.ResetAndDestroy();
	    arruids.ResetAndDestroy();
	    delete entryObj;
	    }
		else
			result = KErrGeneral;	

	RemoveCalendarFile( service, KTestCal1File );
	
	delete service;
	
	__UHEAP_MARKEND;

	return result;
		
	}
TInt CTCalendarAddTest::AddDayEventL(CStifItemParser &aItem )
	{
	/*__UHEAP_MARK;
	CEntryAttributes* entryObj = CEntryAttributes::NewL( KEntryEvent );
	
	entryObj->SetDescriptionL(_L("New Event entry created"));
	entryObj->SetSummaryL(_L("Event Entry"));
	
	TTime stTime(TDateTime(2007, EJuly, 25, 0, 0, 0, 0));
	entryObj->SetStartTimeL(stTime);
	entryObj->SetReplicationL(KReplPrivate);
	
	TBuf<15> defaultfile(_L("C:Calendar"));
	TPtrC ptr(defaultfile);
	
	CCalendarService* service;
	TRAPD( err, service = CCalendarService::NewL() );
	
	TUIDSet* uids = NULL;
		
	TRAPD( errno, service->AddL(ptr,entryObj,uids) );
	
    delete uids;
    delete entryObj;      
    delete service;
	__UHEAP_MARKEND;
	return errno;*/
	
	TInt result = KErrNone;
	
	__UHEAP_MARK;
	
	CCalendarService* service = CCalendarService::NewL();

	RemoveCalendarFile( service, KTestCal1File );
	AddCalendarFile( service, KTestCal1File );

	RPointerArray<TUIDSet> arruids(5);
	
	TUIDSet* uids = NULL;

	CEntryAttributes* entryObj = CEntryAttributes::NewL( KEntryEvent );
	
	entryObj->SetDescriptionL(_L("New Event entry created"));
	entryObj->SetSummaryL(_L("Event Entry"));
	
	TTime stTime(TDateTime(2007, EJuly, 25, 0, 0, 0, 0));
	entryObj->SetStartTimeL(stTime);
	entryObj->SetReplicationL(KReplPrivate);
	
	TRAPD( errno, service->AddL(KTestCal1File,entryObj,uids) );	

	if(errno == KErrNone && uids)
		{
		arruids.Append(uids);
		uids = NULL;
		}

	if ( arruids.Count() > 0 )
		{
		RPointerArray<CCalEntry> entryArray;
    	service->GetListL( KTestCal1File, arruids[0]->iLocalUID , entryArray );
    	if( entryArray.Count() == 1 )
    		{
    		if( !( entryArray[0]->StartTimeL().TimeUtcL() == stTime  && entryArray[0]->DescriptionL().CompareF(_L("New Event entry created")) == 0
    		                                                           && entryArray[0]->SummaryL().CompareF(_L("Event Entry")) == 0  ) )
	    		{
	    		result = KErrGeneral;	
	    		}
	    	}
	    
        else
	        {
	        result = KErrGeneral;		
	        }
		entryArray.ResetAndDestroy();
	    arruids.ResetAndDestroy();
	    delete entryObj;
	    }
		else
			result = KErrGeneral;	

	RemoveCalendarFile( service, KTestCal1File );
	
	delete service;
	
	__UHEAP_MARKEND;

	return result;

	}
	
TInt CTCalendarAddTest::AddReminderL(CStifItemParser &aItem )
	{
	/*__UHEAP_MARK;
	CEntryAttributes* entryObj = CEntryAttributes::NewL( KEntryReminder );
	
	entryObj->SetDescriptionL(_L("New Reminder entry created"));
	entryObj->SetSummaryL(_L("Reminder Entry"));

    TTime stTime(TDateTime(2007, EJuly, 22, 10, 30, 0, 0));
	entryObj->SetStartTimeL(stTime);
	entryObj->SetReplicationL(KReplOpen);
	
	TBuf<15> defaultfile(_L("C:Calendar"));
	TPtrC ptr(defaultfile);
	
	CCalendarService* service;
	TRAPD( err, service = CCalendarService::NewL() );
	
	TUIDSet* uids = NULL;
		
	TRAPD( errno, service->AddL(ptr,entryObj,uids) );
	
    delete uids;
    delete entryObj;   
    delete service;
	__UHEAP_MARKEND;
	return errno;*/
	TInt result = KErrNone;
	
	__UHEAP_MARK;
	
	CCalendarService* service = CCalendarService::NewL();

	RemoveCalendarFile( service, KTestCal1File );
	AddCalendarFile( service, KTestCal1File );

	RPointerArray<TUIDSet> arruids(5);
	
	TUIDSet* uids = NULL;

	CEntryAttributes* entryObj = CEntryAttributes::NewL( KEntryReminder );
	
	entryObj->SetDescriptionL(_L("New Reminder entry created"));
	entryObj->SetSummaryL(_L("Reminder Entry"));

    TTime stTime(TDateTime(2007, EJuly, 22, 10, 30, 0, 0));
	entryObj->SetStartTimeL(stTime);
	entryObj->SetReplicationL(KReplOpen);
	
	TRAPD( errno, service->AddL(KTestCal1File,entryObj,uids) );	

	if(errno == KErrNone && uids)
		{
		arruids.Append(uids);
		uids = NULL;
		}

	if ( arruids.Count() > 0 )
		{
		CCalEntry::TReplicationStatus rep = CCalEntry::EOpen;
		RPointerArray<CCalEntry> entryArray;
    	service->GetListL( KTestCal1File, arruids[0]->iLocalUID , entryArray );
    	if( entryArray.Count() == 1 )
    		{
    		if( !( entryArray[0]->StartTimeL().TimeUtcL() == stTime  && entryArray[0]->DescriptionL().CompareF(_L("New Reminder entry created")) == 0
    		                                                           && entryArray[0]->SummaryL().CompareF(_L("Reminder Entry")) == 0
    		                                                           && entryArray[0]->ReplicationStatusL() == rep  ) )
	    		{
	    		result = KErrGeneral;	
	    		}
	    	}
	    
        else
	        {
	        result = KErrGeneral;		
	        }
		entryArray.ResetAndDestroy();
	    arruids.ResetAndDestroy();
	    delete entryObj;
	    }
		else
			result = KErrGeneral;	

	RemoveCalendarFile( service, KTestCal1File );
	
	delete service;
	
	__UHEAP_MARKEND;

	return result;

	}