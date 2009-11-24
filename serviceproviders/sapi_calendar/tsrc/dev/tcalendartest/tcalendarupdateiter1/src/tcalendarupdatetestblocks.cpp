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
#include <StifTestInterface.h>

#include "calendarheader.h"
#include "calendarservice.h"
#include "entryattributes.h"
#include <caluser.h>
#include <calalarm.h>

#include "tcalendarupdatetest.h"
#include "teststartconsolealarmserver.h"
//#include "calendarconstants.h"
// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTChangeStatusTest::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTCalendarUpdateTest::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CTChangeStatusTest::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTCalendarUpdateTest::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
                
        ENTRY( "UpdateAppointmentEntry",    	CTCalendarUpdateTest::UpdateAppointmentEntryL),
        ENTRY( "UpdateTodoEntry",       CTCalendarUpdateTest::UpdateTodoEntryL),
        ENTRY( "UpdateAnniversary",       CTCalendarUpdateTest::UpdateAnniversaryL),
        ENTRY( "UpdateDayEvent",       CTCalendarUpdateTest::UpdateDayEventL),
        ENTRY( "UpdateReminder",       CTCalendarUpdateTest::UpdateReminderL),
        ENTRY( "UpdateAppointmentEntryWithNewTime",       CTCalendarUpdateTest::UpdateAppointmentEntryWithNewTimeL),
        ENTRY( "UpdateAppointmentEntryWithNewAttendees",       CTCalendarUpdateTest::UpdateAppointmentEntryWithNewAttendeesL),
        ENTRY( "UpdateAppointmentEntryWithNewRepeat",    	CTCalendarUpdateTest::UpdateAppointmentEntryWithNewRepeatL),
        //ENTRY( "UpdateAppointmentEntryWithNewTimeAndAttendees",       CTCalendarUpdateTest::UpdateAppointmentEntryWithNewTimeAndAttendeesL),
        
        ENTRY( "UpdateAppointmentEntryWithGlobalId",        CTCalendarUpdateTest::UpdateAppointmentEntryWithGlobalIdL),
        ENTRY( "UpdateTodoEntryWithGlobalId",       CTCalendarUpdateTest::UpdateTodoEntryWithGlobalIdL),
        ENTRY( "UpdateAnniversaryWithGlobalId",       CTCalendarUpdateTest::UpdateAnniversaryWithGlobalIdL),
        ENTRY( "UpdateDayEventWithGlobalId",       CTCalendarUpdateTest::UpdateDayEventWithGlobalIdL),
        ENTRY( "UpdateReminderWithGlobalId",       CTCalendarUpdateTest::UpdateReminderWithGlobalIdL),
        ENTRY( "UpdateAppointmentEntryWithNewTimeAndGlobalId",       CTCalendarUpdateTest::UpdateAppointmentEntryWithNewTimeAndGlobalIdL),
        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

/*
1. Change location, attendees, phone owner
2. Change start time of meeting - have to update alarm accordingly
3. Create a repeating entry
4. Create a repeating modifying entry
5. Modify the entire repeat sequence
6. Change alarm for parent and child
7. Set repeat and exeption dates
*/
_LIT(KTestCal1File                ,"C:updatecalfile1");
_LIT(KTestCal2File                ,"C:updatecalfile2");
_LIT(KString1                ,"New reminder");


TInt CTCalendarUpdateTest::UpdateAppointmentEntryL(CStifItemParser &aItem )
	{
	
    
    TInt result = KErrNone;
	
	__UHEAP_MARK;
	
	CCalendarService* service = CCalendarService::NewL();
	
	RemoveCalendarFile( service, KTestCal1File );
	AddCalendarFile( service, KTestCal1File );

	RPointerArray<TUIDSet> arruids(5);
	
	TUIDSet* uids = NULL;
	
	if(AddAppointmentWithAttendees(service, KTestCal1File, uids) == KErrNone && uids)
		{
		arruids.Append(uids);
		uids = NULL;
		}

	if ( arruids.Count() > 0 )
		{
	    RPointerArray<CCalEntry> entryArray;
	    
	    CEntryAttributes* entryObj = CEntryAttributes::NewL();
	    	    
	    TTime stTime(TDateTime(2007, EAugust, 8, 11, 0, 0, 0));
		entryObj->SetStartTimeL(stTime);
		
		TTime endTime(TDateTime(2007, EAugust, 8, 12, 0, 0, 0));
		entryObj->SetEndTimeL(endTime);
	    
	    
		CCalAlarm* alarm = CCalAlarm::NewL();
		TTime alarmTime(TDateTime(2007,EAugust, 8, 10, 30, 0, 0));
		entryObj->SetAlarm(alarmTime);
		delete alarm;
		
		service->GetListL( KTestCal1File, arruids[0]->iLocalUID , entryArray );

		if( entryArray.Count() == 1 )
			{
			entryObj->SetLocalUid( arruids[0]->iLocalUID );
			}
			
		TUIDSet* newuids = NULL;	
		entryArray.ResetAndDestroy();	
	    TRAPD( err, service->AddL(KTestCal1File,entryObj,newuids) );
	    delete newuids;
	    if ( err == KErrNone )
	    	{ 
	    	service->GetListL( KTestCal1File, arruids[0]->iLocalUID , entryArray );
	    	if( entryArray.Count() == 1 )
	    		{
	    		CCalAlarm* entryalarm = entryArray[0]->AlarmL();
	    		if( !(entryArray[0]->StartTimeL().TimeUtcL() == stTime && 
	    		    entryArray[0]->EndTimeL().TimeUtcL() == endTime &&
	    		    entryalarm->TimeOffset() == TTimeIntervalMinutes(30) ))
		    		{
		    		result = KErrGeneral;
		    		delete entryalarm;	
		    		}
		    	else
		    		delete entryalarm;
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
	
TInt CTCalendarUpdateTest::UpdateTodoEntryL(CStifItemParser &aItem )
	{
	
	TInt result = KErrNone;
	
	__UHEAP_MARK;
	
	CCalendarService* service = CCalendarService::NewL();
	
	RemoveCalendarFile( service, KTestCal1File );
	AddCalendarFile( service, KTestCal1File );

	RPointerArray<TUIDSet> arruids(5);
	
	TUIDSet* uids = NULL;
	
	if(AddToDo(service, KTestCal1File, uids) == KErrNone && uids)
		{
		arruids.Append(uids);
		uids = NULL;
		}

	if ( arruids.Count() > 0 )
		{
	    RPointerArray<CCalEntry> entryArray;
	    
	    CEntryAttributes* entryObj = CEntryAttributes::NewL();
	    
		TTime endTime(TDateTime(2007, EAugust, 22, 0, 0, 0, 0));
		entryObj->SetEndTimeL(endTime);	    
	    		
		service->GetListL( KTestCal1File, arruids[0]->iLocalUID , entryArray );

		if( entryArray.Count() == 1 )
			{
			entryObj->SetLocalUid( arruids[0]->iLocalUID );
			}
			
		TCalLocalUid modifiedEntryId;	
		TUIDSet* entryUids = NULL;	
	    TRAPD( err, service->AddL(KTestCal1File,entryObj,entryUids) );
	    delete entryUids;
	    entryArray.ResetAndDestroy();
	    if ( err == KErrNone )
	    	{ 
	    	service->GetListL( KTestCal1File, arruids[0]->iLocalUID , entryArray );
	    	if( entryArray.Count() == 1 )
	    		{
	    		if( !(entryArray[0]->EndTimeL().TimeUtcL() == endTime ))
		    		{
		    		result = KErrGeneral;	
		    		}
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

TInt CTCalendarUpdateTest::UpdateAnniversaryL(CStifItemParser &aItem )//try
	{
	
	TInt result = KErrNone;
	
	__UHEAP_MARK;
	
	CCalendarService* service = CCalendarService::NewL();

	RemoveCalendarFile( service, KTestCal1File );
	AddCalendarFile( service, KTestCal1File );

	RPointerArray<TUIDSet> arruids(5);
	
	TUIDSet* uids = NULL;
	
	if(AddAnny(service, KTestCal1File, uids) == KErrNone && uids)
		{
		arruids.Append(uids);
		uids = NULL;
		}

	if ( arruids.Count() > 0 )
		{
	    RPointerArray<CCalEntry> entryArray;
	    
	    CEntryAttributes* entryObj = CEntryAttributes::NewL();
	    TCalTime stTime;
		stTime.SetTimeLocalFloatingL(TTime(TDateTime(2007, EDecember, 28, 0, 0, 0, 0)));
		TTime startTime(TDateTime(2007, EDecember, 28, 0, 0, 0, 0));
		entryObj->SetStartTimeL(startTime);	
		
		/*TCalRRule rrule(TCalRRule::EYearly);
		rrule.SetDtStart(stTime);
		rrule.SetInterval(1);
		
		TCalTime uTime;
		uTime.SetTimeLocalFloatingL(TCalTime::MaxTime());
		rrule.SetUntil(uTime);
		
		entryObj->SetRepeatRule(rrule); */   
		    		
		service->GetListL( KTestCal1File, arruids[0]->iLocalUID , entryArray );

		if( entryArray.Count() == 1 )
			{
			entryObj->SetLocalUid( arruids[0]->iLocalUID );
			}
			
		TUIDSet* uids = NULL;
		entryArray.ResetAndDestroy();		
	    TRAPD( err, service->AddL(KTestCal1File,entryObj,uids) );
	    delete uids;
	    if ( err == KErrNone )
	    	{ 
	    	service->GetListL( KTestCal1File, arruids[0]->iLocalUID , entryArray );
	    	if( entryArray.Count() == 1 )
	    		{
		    	TCalRRule rRule;
	    		entryArray[0]->GetRRuleL( rRule );
	    		TCalTime utTime;
				utTime.SetTimeLocalFloatingL(TTime(TDateTime(2100, EDecember, 28, 0, 0, 0, 0)));
	    		if( !( entryArray[0]->StartTimeL().TimeLocalL() == stTime.TimeLocalL() ) && rRule.Until().TimeLocalL() == utTime.TimeLocalL())
		    		{
		    		result = KErrGeneral;	
		    		}
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

TInt CTCalendarUpdateTest::UpdateDayEventL(CStifItemParser &aItem )//try
	{
	TInt result = KErrNone;
	
	__UHEAP_MARK;
	
	CCalendarService* service = CCalendarService::NewL();
	
	RemoveCalendarFile( service, KTestCal1File );
	AddCalendarFile( service, KTestCal1File );

	RPointerArray<TUIDSet> arruids(5);
	
	TUIDSet* uids = NULL;
	
	if(AddEvent(service, KTestCal1File, uids) == KErrNone && uids)
		{
		arruids.Append(uids);
		uids = NULL;
		}

	if ( arruids.Count() > 0 )
		{
	    RPointerArray<CCalEntry> entryArray;
	    
	    CEntryAttributes* entryObj = CEntryAttributes::NewL();
	    	    
	    entryObj->SetDescriptionL(_L("Day event modified"));
	    entryObj->SetPriority(2);	
		service->GetListL( KTestCal1File, arruids[0]->iLocalUID , entryArray );

		if( entryArray.Count() == 1 )
			{
			entryObj->SetLocalUid( arruids[0]->iLocalUID );
			}
			
		TUIDSet* uids = NULL;		
	    TRAPD( err, service->AddL(KTestCal1File,entryObj,uids) );
	    delete uids;
	    entryArray.ResetAndDestroy();
	    if ( err == KErrNone )
	    	{ 
	    	service->GetListL( KTestCal1File, arruids[0]->iLocalUID , entryArray );
	    	if( entryArray.Count() == 1 )
	    		{
	    		if( !( entryArray[0]->DescriptionL().CompareF(_L("Day event modified")) == 0 && entryArray[0]->PriorityL() == 2 ) )
		    		{
		    		result = KErrGeneral;	
		    		}
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
	
TInt CTCalendarUpdateTest::UpdateReminderL(CStifItemParser &aItem )
	{
	TInt result = KErrNone;
	
	__UHEAP_MARK;
	
	CCalendarService* service = CCalendarService::NewL();
	
	RemoveCalendarFile( service, KTestCal1File );
	AddCalendarFile( service, KTestCal1File );

	RPointerArray<TUIDSet> arruids(5);
	
	TUIDSet* uids = NULL;
	
	if(AddReminder(service, KTestCal1File, uids) == KErrNone && uids)
		{
		arruids.Append(uids);
		uids = NULL;
		}

	if ( arruids.Count() > 0 )
		{
	    RPointerArray<CCalEntry> entryArray;
	    
	    CEntryAttributes* entryObj = CEntryAttributes::NewL();
	    entryObj->SetSummaryL(KString1);	    
	    TTime stTime(TDateTime(2007, EJuly, 23, 11, 30, 0, 0));
		entryObj->SetStartTimeL(stTime);
					
		service->GetListL( KTestCal1File, arruids[0]->iLocalUID , entryArray );

		if( entryArray.Count() == 1 )
			{
			entryObj->SetLocalUid( arruids[0]->iLocalUID );
			}
			
		TUIDSet* uids = NULL;		
	    TRAPD( err, service->AddL(KTestCal1File,entryObj,uids) );
	    delete uids;
	    entryArray.ResetAndDestroy();
	    if ( err == KErrNone )
	    	{ 
	    	service->GetListL( KTestCal1File, arruids[0]->iLocalUID , entryArray );
	    	if( entryArray.Count() == 1 )
	    		{
	    		if( !( entryArray[0]->SummaryL().CompareF( KString1 ) == 0 && entryArray[0]->StartTimeL().TimeUtcL() == stTime))
		    		{
		    		result = KErrGeneral;	
		    		}
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



TInt CTCalendarUpdateTest::UpdateAppointmentEntryWithNewTimeL(CStifItemParser &aItem )
	{
	TInt result = KErrNone;
	
	__UHEAP_MARK;
	
	CCalendarService* service = CCalendarService::NewL();
	
	RemoveCalendarFile( service, KTestCal1File );
	AddCalendarFile( service, KTestCal1File );

	RPointerArray<TUIDSet> arruids(5);
	
	TUIDSet* uids = NULL;
	
	if(AddRepeatingAppointmentEntryL(service, KTestCal1File, uids) == KErrNone && uids)
		{
		arruids.Append(uids);
		uids = NULL;
		}

	if ( arruids.Count() > 0 )
		{
	    RPointerArray<CCalEntry> entryArray;
	    
	    CEntryAttributes* entryObj = CEntryAttributes::NewL();
	    
	    
	    TTime stTime(TDateTime(2007, ESeptember, 17, 9, 0, 0, 0));
		entryObj->SetInstanceStartTimeL(stTime);
		TTime startTime(TDateTime(2007, ESeptember, 17, 14, 0, 0, 0));
		entryObj->SetStartTimeL(startTime);
		TTime endTime(TDateTime(2007, ESeptember, 17, 17, 30, 0, 0));
		entryObj->SetEndTimeL(endTime);		
			    		
		service->GetListL( KTestCal1File, arruids[0]->iLocalUID , entryArray );

		if( entryArray.Count() == 1 )
			{
			entryObj->SetLocalUid( arruids[0]->iLocalUID );
			}
			
		TUIDSet* uids = NULL;
		TCalLocalUid modifiedEntryId;		
	    TRAPD( err, service->AddL(KTestCal1File,entryObj,uids) );
	    modifiedEntryId = uids->iLocalUID;
	    delete uids;
	    entryArray.ResetAndDestroy();
	    if ( err == KErrNone )
	    	{ 
	    	service->GetListL( KTestCal1File, modifiedEntryId , entryArray );
	    	if( entryArray.Count() == 1 )
	    		{
	    		if( !( entryArray[0]->StartTimeL().TimeUtcL() == startTime && 
	    		    entryArray[0]->EndTimeL().TimeUtcL() == endTime ))
	    		    {
		    		result = KErrGeneral;	
		    		}
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


TInt CTCalendarUpdateTest::UpdateAppointmentEntryWithNewAttendeesL(CStifItemParser &aItem )
	{
	TInt result = KErrNone;
	
	__UHEAP_MARK;
	
	CCalendarService* service = CCalendarService::NewL();
	
	RemoveCalendarFile( service, KTestCal1File );
	AddCalendarFile( service, KTestCal1File );

	RPointerArray<TUIDSet> arruids(5);
	
	TUIDSet* uids = NULL;
	
	if(AddRepeatingAppointmentEntryL(service, KTestCal1File, uids) == KErrNone && uids)
		{
		arruids.Append(uids);
		uids = NULL;
		}

	if ( arruids.Count() > 0 )
		{
	    RPointerArray<CCalEntry> entryArray;
	    
	    CEntryAttributes* entryObj = CEntryAttributes::NewL();
	    
	    TTime stTime(TDateTime(2007, ESeptember, 17, 9, 0, 0, 0));
		entryObj->SetInstanceStartTimeL(stTime);
		TTime startTime(TDateTime(2007, ESeptember, 17, 14, 0, 0, 0));
		entryObj->SetStartTimeL(startTime);
		TTime endTime(TDateTime(2007, ESeptember, 17, 17, 30, 0, 0));
		entryObj->SetEndTimeL(endTime);	 
	    
		CAttendeeInfo* attendee = CAttendeeInfo::NewL(_L("carendar@yahoo.com"));
	    CleanupStack::PushL(attendee);
		attendee->SetRoleL(KAttRoleReqParticipant);
		attendee->SetStatusL(KAttStatusTentative);
	    attendee->SetRsvp(EFalse);
	    
		entryObj->AddAttendeeL(attendee);
		CleanupStack::PopAndDestroy(attendee);
		
		attendee = CAttendeeInfo::NewL(_L("bettinapinto@gmail.com"));
		CleanupStack::PushL(attendee);
		attendee->SetCommonNameL(_L("SAPI"));
		attendee->SetRoleL(KAttRoleReqParticipant);
		attendee->SetStatusL(KAttStatusTentative);
	    attendee->SetRsvp(EFalse);
	    
		entryObj->AddAttendeeL(attendee);
		CleanupStack::PopAndDestroy(attendee);
	    
		service->GetListL( KTestCal1File, arruids[0]->iLocalUID , entryArray );

		if( entryArray.Count() == 1 )
			{
			entryObj->SetLocalUid( arruids[0]->iLocalUID );
			}
			
		TUIDSet* uids = NULL;
		TCalLocalUid modifiedEntryId;		
	    TRAPD( err, service->AddL(KTestCal1File,entryObj,uids) );
	    modifiedEntryId = uids->iLocalUID;
	    delete uids;
	    entryArray.ResetAndDestroy();
	    if ( err == KErrNone )
	    	{ 
	    	service->GetListL( KTestCal1File, modifiedEntryId , entryArray );
	    	if( entryArray.Count() == 1 )
	    		{
	    		RPointerArray<CCalAttendee> attendeeList;
	    		attendeeList = entryArray[0]->AttendeesL(); 
	    		if( attendeeList.Count() != 2 )
	    		    {
		    		result = KErrGeneral;	
		    		}
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
	//update entry's location, repeat rule check local uid returned

TInt CTCalendarUpdateTest::UpdateAppointmentEntryWithNewRepeatL(CStifItemParser &aItem )
	{
	TInt result = KErrNone;
	
	__UHEAP_MARK;
	
	CCalendarService* service = CCalendarService::NewL();
	
	RemoveCalendarFile( service, KTestCal1File );
	AddCalendarFile( service, KTestCal1File );

	RPointerArray<TUIDSet> arruids(5);
	
	TUIDSet* uids = NULL;
	
	if(AddRepeatingAppointmentEntryL(service, KTestCal1File, uids) == KErrNone && uids)
		{
		arruids.Append(uids);
		uids = NULL;
		}

	if ( arruids.Count() > 0 )
		{
	    RPointerArray<CCalEntry> entryArray;
	    
	    CEntryAttributes* entryObj = CEntryAttributes::NewL();
	    
		entryObj->SetDescriptionL(_L("Updated SAPI weekly meeting"));
	    
	    TTime stTime(TDateTime(2007, ESeptember, 15, 9, 0, 0, 0));
			
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

		service->GetListL( KTestCal1File, arruids[0]->iLocalUID , entryArray );

		if( entryArray.Count() == 1 )
			{
			entryObj->SetLocalUid( arruids[0]->iLocalUID );
			}
		entryArray.ResetAndDestroy();
		TUIDSet* uids = NULL;
		TCalLocalUid modifiedEntryId;		
	    TRAPD( err, service->AddL(KTestCal1File,entryObj,uids) );
	    modifiedEntryId = uids->iLocalUID;
	    delete uids;
	    
	    if ( err == KErrNone )
	    	{ 
	    	service->GetListL( KTestCal1File, modifiedEntryId , entryArray );
	    	if( entryArray.Count() == 1 )
	    		{
	    		TCalRRule rRule;
	    		entryArray[0]->GetRRuleL( rRule );
	    		TCalTime utTime;
				utTime.SetTimeLocalL(TTime(TDateTime(2007, EDecember, 18, 9, 0, 0, 0)));
	    		if( !( rRule.Type() == TCalRRule::EMonthly ))
		    		{
		    		result = KErrGeneral;	
		    		}
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

TInt CTCalendarUpdateTest::UpdateAppointmentEntryWithGlobalIdL(CStifItemParser &aItem )
    {
    
    
    TInt result = KErrNone;
    
    __UHEAP_MARK;
    
    CCalendarService* service = CCalendarService::NewL();
    
    RemoveCalendarFile( service, KTestCal1File );
    AddCalendarFile( service, KTestCal1File );

    RPointerArray<TUIDSet> arruids(5);
    
    TUIDSet* uids = NULL;
    
    if(AddAppointmentWithAttendees(service, KTestCal1File, uids) == KErrNone && uids)
        {
        arruids.Append(uids);
        uids = NULL;
        }

    if ( arruids.Count() > 0 )
        {
        RPointerArray<CCalEntry> entryArray;
        
        CEntryAttributes* entryObj = CEntryAttributes::NewL();
                
        TTime stTime(TDateTime(2007, EAugust, 8, 11, 0, 0, 0));
        entryObj->SetStartTimeL(stTime);
        
        TTime endTime(TDateTime(2007, EAugust, 8, 12, 0, 0, 0));
        entryObj->SetEndTimeL(endTime);
        
        
        CCalAlarm* alarm = CCalAlarm::NewL();
        TTime alarmTime(TDateTime(2007,EAugust, 8, 10, 30, 0, 0));
        entryObj->SetAlarm(alarmTime);
        delete alarm;
        
        service->GetListL( KTestCal1File, *(arruids[0]->iGlobalUID) , entryArray );

        if( entryArray.Count() == 1 )
            {
            entryObj->SetUidL( *(arruids[0]->iGlobalUID) );
            }
            
        TUIDSet* newuids = NULL;    
        entryArray.ResetAndDestroy();   
        TRAPD( err, service->AddL(KTestCal1File,entryObj,newuids) );
        delete newuids;
        if ( err == KErrNone )
            { 
            service->GetListL( KTestCal1File, *(arruids[0]->iGlobalUID) , entryArray );
            if( entryArray.Count() == 1 )
                {
                CCalAlarm* entryalarm = entryArray[0]->AlarmL();
                if( !(entryArray[0]->StartTimeL().TimeUtcL() == stTime && 
                    entryArray[0]->EndTimeL().TimeUtcL() == endTime &&
                    entryalarm->TimeOffset() == TTimeIntervalMinutes(30) ))
                    {
                    result = KErrGeneral;
                    delete entryalarm;  
                    }
                else
                    delete entryalarm;
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
    
TInt CTCalendarUpdateTest::UpdateTodoEntryWithGlobalIdL(CStifItemParser &aItem )
    {
    
    TInt result = KErrNone;
    
    __UHEAP_MARK;
    
    CCalendarService* service = CCalendarService::NewL();
    
    RemoveCalendarFile( service, KTestCal1File );
    AddCalendarFile( service, KTestCal1File );

    RPointerArray<TUIDSet> arruids(5);
    
    TUIDSet* uids = NULL;
    
    if(AddToDo(service, KTestCal1File, uids) == KErrNone && uids)
        {
        arruids.Append(uids);
        uids = NULL;
        }

    if ( arruids.Count() > 0 )
        {
        RPointerArray<CCalEntry> entryArray;
        
        CEntryAttributes* entryObj = CEntryAttributes::NewL();
        
        TTime endTime(TDateTime(2007, EAugust, 22, 0, 0, 0, 0));
        entryObj->SetEndTimeL(endTime);     
                
        service->GetListL( KTestCal1File, *(arruids[0]->iGlobalUID) , entryArray );

        if( entryArray.Count() == 1 )
            {
            entryObj->SetUidL( *(arruids[0]->iGlobalUID) );
            }
            
        TCalLocalUid modifiedEntryId;   
        TUIDSet* entryUids = NULL;  
        TRAPD( err, service->AddL(KTestCal1File,entryObj,entryUids) );
        delete entryUids;
        entryArray.ResetAndDestroy();
        if ( err == KErrNone )
            { 
            service->GetListL( KTestCal1File, *(arruids[0]->iGlobalUID) , entryArray );
            if( entryArray.Count() == 1 )
                {
                if( !(entryArray[0]->EndTimeL().TimeUtcL() == endTime ))
                    {
                    result = KErrGeneral;   
                    }
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

TInt CTCalendarUpdateTest::UpdateAnniversaryWithGlobalIdL(CStifItemParser &aItem )//try
    {
    
    TInt result = KErrNone;
    
    __UHEAP_MARK;
    
    CCalendarService* service = CCalendarService::NewL();

    RemoveCalendarFile( service, KTestCal1File );
    AddCalendarFile( service, KTestCal1File );

    RPointerArray<TUIDSet> arruids(5);
    
    TUIDSet* uids = NULL;
    
    if(AddAnny(service, KTestCal1File, uids) == KErrNone && uids)
        {
        arruids.Append(uids);
        uids = NULL;
        }

    if ( arruids.Count() > 0 )
        {
        RPointerArray<CCalEntry> entryArray;
        
        CEntryAttributes* entryObj = CEntryAttributes::NewL();
        TCalTime stTime;
        stTime.SetTimeLocalFloatingL(TTime(TDateTime(2007, EDecember, 28, 0, 0, 0, 0)));
        TTime startTime(TDateTime(2007, EDecember, 28, 0, 0, 0, 0));
        entryObj->SetStartTimeL(startTime); 
        
        /*TCalRRule rrule(TCalRRule::EYearly);
        rrule.SetDtStart(stTime);
        rrule.SetInterval(1);
        
        TCalTime uTime;
        uTime.SetTimeLocalFloatingL(TCalTime::MaxTime());
        rrule.SetUntil(uTime);
        
        entryObj->SetRepeatRule(rrule); */   
                    
        service->GetListL( KTestCal1File, *(arruids[0]->iGlobalUID) , entryArray );

        if( entryArray.Count() == 1 )
            {
            entryObj->SetUidL( *(arruids[0]->iGlobalUID) );
            }
            
        TUIDSet* uids = NULL;
        entryArray.ResetAndDestroy();       
        TRAPD( err, service->AddL(KTestCal1File,entryObj,uids) );
        delete uids;
        if ( err == KErrNone )
            { 
            service->GetListL( KTestCal1File, *(arruids[0]->iGlobalUID) , entryArray );
            if( entryArray.Count() == 1 )
                {
                TCalRRule rRule;
                entryArray[0]->GetRRuleL( rRule );
                TCalTime utTime;
                utTime.SetTimeLocalFloatingL(TTime(TDateTime(2100, EDecember, 28, 0, 0, 0, 0)));
                if( !( entryArray[0]->StartTimeL().TimeLocalL() == stTime.TimeLocalL() ) && rRule.Until().TimeLocalL() == utTime.TimeLocalL())
                    {
                    result = KErrGeneral;   
                    }
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

TInt CTCalendarUpdateTest::UpdateDayEventWithGlobalIdL(CStifItemParser &aItem )//try
    {
    TInt result = KErrNone;
    
    __UHEAP_MARK;
    
    CCalendarService* service = CCalendarService::NewL();
    
    RemoveCalendarFile( service, KTestCal1File );
    AddCalendarFile( service, KTestCal1File );

    RPointerArray<TUIDSet> arruids(5);
    
    TUIDSet* uids = NULL;
    
    if(AddEvent(service, KTestCal1File, uids) == KErrNone && uids)
        {
        arruids.Append(uids);
        uids = NULL;
        }

    if ( arruids.Count() > 0 )
        {
        RPointerArray<CCalEntry> entryArray;
        
        CEntryAttributes* entryObj = CEntryAttributes::NewL();
                
        entryObj->SetDescriptionL(_L("Day event modified"));
        entryObj->SetPriority(2);   
        service->GetListL( KTestCal1File, *(arruids[0]->iGlobalUID) , entryArray );

        if( entryArray.Count() == 1 )
            {
            entryObj->SetUidL( *(arruids[0]->iGlobalUID) );
            }
            
        TUIDSet* uids = NULL;       
        TRAPD( err, service->AddL(KTestCal1File,entryObj,uids) );
        delete uids;
        entryArray.ResetAndDestroy();
        if ( err == KErrNone )
            { 
            service->GetListL( KTestCal1File, *(arruids[0]->iGlobalUID) , entryArray );
            if( entryArray.Count() == 1 )
                {
                if( !( entryArray[0]->DescriptionL().CompareF(_L("Day event modified")) == 0 && entryArray[0]->PriorityL() == 2 ) )
                    {
                    result = KErrGeneral;   
                    }
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
    
TInt CTCalendarUpdateTest::UpdateReminderWithGlobalIdL(CStifItemParser &aItem )
    {
    TInt result = KErrNone;
    
    __UHEAP_MARK;
    
    CCalendarService* service = CCalendarService::NewL();
    
    RemoveCalendarFile( service, KTestCal1File );
    AddCalendarFile( service, KTestCal1File );

    RPointerArray<TUIDSet> arruids(5);
    
    TUIDSet* uids = NULL;
    
    if(AddReminder(service, KTestCal1File, uids) == KErrNone && uids)
        {
        arruids.Append(uids);
        uids = NULL;
        }

    if ( arruids.Count() > 0 )
        {
        RPointerArray<CCalEntry> entryArray;
        
        CEntryAttributes* entryObj = CEntryAttributes::NewL();
        entryObj->SetSummaryL(KString1);        
        TTime stTime(TDateTime(2007, EJuly, 23, 11, 30, 0, 0));
        entryObj->SetStartTimeL(stTime);
                    
        service->GetListL( KTestCal1File, *(arruids[0]->iGlobalUID) , entryArray );

        if( entryArray.Count() == 1 )
            {
            entryObj->SetUidL( *(arruids[0]->iGlobalUID) );
            }
            
        TUIDSet* uids = NULL;       
        TRAPD( err, service->AddL(KTestCal1File,entryObj,uids) );
        delete uids;
        entryArray.ResetAndDestroy();
        if ( err == KErrNone )
            { 
            service->GetListL( KTestCal1File, *(arruids[0]->iGlobalUID) , entryArray );
            if( entryArray.Count() == 1 )
                {
                if( !( entryArray[0]->SummaryL().CompareF( KString1 ) == 0 && entryArray[0]->StartTimeL().TimeUtcL() == stTime))
                    {
                    result = KErrGeneral;   
                    }
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
TInt CTCalendarUpdateTest::UpdateAppointmentEntryWithNewTimeAndGlobalIdL(CStifItemParser &aItem )
    {
    TInt result = KErrNone;
    
    __UHEAP_MARK;
    
    CCalendarService* service = CCalendarService::NewL();
    
    RemoveCalendarFile( service, KTestCal1File );
    AddCalendarFile( service, KTestCal1File );

    RPointerArray<TUIDSet> arruids(5);
    
    TUIDSet* uids = NULL;
    
    if(AddRepeatingAppointmentEntryL(service, KTestCal1File, uids) == KErrNone && uids)
        {
        arruids.Append(uids);
        uids = NULL;
        }

    if ( arruids.Count() > 0 )
        {
        RPointerArray<CCalEntry> entryArray;
        
        CEntryAttributes* entryObj = CEntryAttributes::NewL();
        
        
        TTime stTime(TDateTime(2007, ESeptember, 17, 9, 0, 0, 0));
        entryObj->SetInstanceStartTimeL(stTime);
        TTime startTime(TDateTime(2007, ESeptember, 17, 14, 0, 0, 0));
        entryObj->SetStartTimeL(startTime);
        TTime endTime(TDateTime(2007, ESeptember, 17, 17, 30, 0, 0));
        entryObj->SetEndTimeL(endTime);     
                        
        service->GetListL( KTestCal1File, *(arruids[0]->iGlobalUID) , entryArray );

        if( entryArray.Count() == 1 )
            {
            entryObj->SetUidL( *(arruids[0]->iGlobalUID) );
            }
            
        TUIDSet* uids = NULL;
        TCalLocalUid modifiedEntryId;       
        TRAPD( err, service->AddL(KTestCal1File,entryObj,uids) );
        //modifiedEntryId = uids->iLocalUID;
     //   modifiedEntryId = uids->iGlobalUID;
        delete uids;
        entryArray.ResetAndDestroy();
        if ( err == KErrNone )
            { 
            service->GetListL( KTestCal1File, *(arruids[0]->iGlobalUID) , entryArray );
            if( entryArray.Count() == 1 )
                {
                if( !( entryArray[0]->StartTimeL().TimeUtcL() == startTime && 
                    entryArray[0]->EndTimeL().TimeUtcL() == endTime ))
                    {
                    result = KErrGeneral;   
                    }
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



#if 0

TInt CTCalendarUpdateTest::UpdateAppointmentEntryWithNewTimeAndAttendeesL(CStifItemParser &aItem )
	{
	
	TInt result = KErrNone;
	
	__UHEAP_MARK;
	
	CCalendarService* service = CCalendarService::NewL();
	
	RemoveCalendarFile( service, KTestCal1File );
	AddCalendarFile( service, KTestCal1File );

	RPointerArray<TUIDSet> arruids(5);
	
	TUIDSet* uids = NULL;
	
	if(AddAppointmentWithAttendees(service, KTestCal1File, uids) == KErrNone && uids)
		{
		arruids.Append(uids);
		uids = NULL;
		}

	if ( arruids.Count() > 0 )
		{
	    RPointerArray<CCalEntry> entryArray;
	    
	    CEntryAttributes* entryObj = CEntryAttributes::NewL();
	    
	    TTime stTime(TDateTime(2007, ESeptember, 17, 8, 0, 0, 0));
		entryObj->SetInstanceStartTime(stTime);
		TTime startTime(TDateTime(2007, ESeptember, 17, 14, 0, 0, 0));
		entryObj->SetStartTime(startTime);
		TTime endTime(TDateTime(2007, ESeptember, 17, 17, 30, 0, 0));
		entryObj->SetEndTime(endTime);
		
	    CCalAttendee* attendee = CCalAttendee::NewL(_L("carencar@yahoo.com"));
		attendee->SetRoleL(CCalAttendee::EReqParticipant);
		attendee->SetStatusL(CCalAttendee::ETentative);
	    attendee->SetResponseRequested(EFalse);
	    
		entryObj->AddAttendeeL(attendee);
				
		CCalUser* organizer = CCalUser::NewL(_L("mcrasta@gmail.com"));
		organizer->SetCommonNameL(_L("SAPI"));
		entryObj->SetOrganizerDataL(organizer);
	
    	entryObj->SetPhoneOwnerDataL(_L("carencar@yahoo.com"));	    
	    		
		service->GetListL( KTestCal1File, arruids[0]->iLocalUID , entryArray );

		if( entryArray.Count() == 1 )
			{
			entryObj->SetLocalUid( arruids[0]->iLocalUID );
			}
			
		TUIDSet* uids = NULL;
		entryArray.ResetAndDestroy();	
	    TRAPD( err, service->UpdateL(KTestCal1File,entryObj,uids) );
	    TCalLocalUid modifiedEntryId = uids->iLocalUID;
	    delete uids;
	    
	    if ( err == KErrNone )
	    	{ 
	    	service->GetListL( KTestCal1File, modifiedEntryId , entryArray );
	    	if( entryArray.Count() == 1 )
	    		{
	    		if( !( entryArray[0]->StartTimeL().TimeUtcL() == stTime && 
	    		    entryArray[0]->EndTimeL().TimeUtcL() == endTime &&
	    		    entryArray[0]->PhoneOwnerL()->Address().CompareF()) == 0 &&
	    		    entryArray[0]->PhoneOwnerL()->Address().CompareF(_L("mcrasta@gmail.com")) == 0))
		    		{
		    		result = KErrGeneral;	
		    	TDateTime tdStTime = entryArray[0]->StartTimeL().TimeLocalL().DateTime();
				TInt yr = tdStTime.Year();
				TMonth mon = tdStTime.Month() ;
				TInt day = tdStTime.Day() ;
				TInt hr = tdStTime.Hour() ;
				TInt min = tdStTime.Minute() ;
				
				TDateTime tdStTime1 = stTime.TimeLocalL().DateTime();
				TInt yr1 = tdStTime1.Year();
				TMonth mon1 = tdStTime1.Month() ;
				TInt day1 = tdStTime1.Day() ;
				TInt hr1 = tdStTime1.Hour() ;
				TInt min1 = tdStTime1.Minute() ;	
		    	//	}
	    		}
	    	}
        else
	        {
	        result = KErrGeneral;		
	        }
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
    #endif