/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
#include "tcal_add.h"
#include "calendarheader.h"
#include "calendarservice.h"
#include <calentry.h>//for CCalEntry
#include <calinstanceview.h>//for CCalInstance
#include <calcommon.h>//for Filter Type Enum Constants
#include <calinstance.h>
#include "teststartconsolealarmserver.h"


// EXTERNAL DATA STRUCTURES
//extern  ?external_data;

// EXTERNAL FUNCTION PROTOTYPES  
//extern ?external_function( ?arg_type,?arg_type );

// CONSTANTS
//const ?type ?constant_var = ?constant;

// MACROS
//#define ?macro ?macro_def

// LOCAL CONSTANTS AND MACROS
//const ?type ?constant_var = ?constant;
//#define ?macro_name ?macro_def

// MODULE DATA STRUCTURES
//enum ?declaration
//typedef ?declaration

// LOCAL FUNCTION PROTOTYPES
//?type ?function_name( ?arg_type, ?arg_type );

// FORWARD DECLARATIONS
//class ?FORWARD_CLASSNAME;

// ============================= LOCAL FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// ?function_name ?description.
// ?description
// Returns: ?value_1: ?description
//          ?value_n: ?description_line1
//                    ?description_line2
// -----------------------------------------------------------------------------
//
/*
?type ?function_name(
    ?arg_type arg,  // ?description
    ?arg_type arg)  // ?description
    {

    ?code  // ?comment

    // ?comment
    ?code
    }
*/

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctcal_add::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void Ctcal_add::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// Ctcal_add::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt Ctcal_add::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "AddCalendar", Ctcal_add::AddCalendar ),
        ENTRY( "AddMeetingEntry", Ctcal_add::AddMeetingEntry ),
        ENTRY( "AddRepeatingEntry", Ctcal_add::AddRepeatingEntry ),
        ENTRY( "AddMonthlyRepeatingEntry", Ctcal_add::AddMonthlyRepeatingEntry ),
        ENTRY( "AddAptWithAttendee", Ctcal_add::AddAptWithAttendee ),
        //ADD NEW ENTRY HERE

        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }


_LIT(KTestCal1File                ,"C:getlistcal1");
_LIT(KTestCal2File                ,"C:getlistcal2"); 
_LIT(KTestCalFile                ,"C:Calendar"); 
	
// -----------------------------------------------------------------------------
// Ctcal_add::AddCalendar
// Add calendar file
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_add::AddCalendar( CStifItemParser& /*aItem*/ )
    {
    	TInt result = KErrNone;
    	__UHEAP_MARK;
    	_LIT(KTestCalTestFile                ,"X:001");
    	_LIT(KTestCalTest1File                ,"X:001");
    	TInt count =0;
    	
    	  	
    	CCalendarService* service = CCalendarService::NewL();
    	
      
    	TInt err = AddCalendarFile( service, KTestCal1File );
    	
    	if(err != KErrNone)
    		result = err;   	
    	
    	   	
    	TInt err_one = AddCalendarFile( service, KTestCal1File );
    	
    	if(err_one != KErrAlreadyExists && result == KErrNone)
    		result = err_one;
       	
			
		TInt err_three = AddCalendarFile( service, KTestCalTestFile );
		
		if(err_three != KErrNotReady && result == KErrNone)
			result = KErrGeneral;
		
		TInt err_four = AddCalendarFile( service, KTestCalTest1File );
		
		if(err_four != KErrNotReady && result == KErrNone)
			result = KErrGeneral;
		
		TInt err_five = AddCalendarFile( service, KNullDesC);
		
		if(err_five != KErrAlreadyExists && result == KErrNone)
			result = KErrGeneral;
		
		TInt err_six = AddCalendarFile( service, KTestCalFile);
		
		if(err_six != KErrAlreadyExists && result == KErrNone)
			result = KErrGeneral;			
    	
		RemoveCalendarFile( service, KTestCal1File );   
	 	delete service;
    	__UHEAP_MARKEND;
    	return result;
    	

    }
    
    // -----------------------------------------------------------------------------
// Ctcal_add::AddMeetingEntry
// Add a new meeting entry
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_add::AddMeetingEntry( CStifItemParser& /*aItem*/ )
    {
    	TInt result = KErrNone;
    	__UHEAP_MARK;
    	_LIT(KTestMethod, 			"XYZ123");	
    	
    	CCalendarService* service = CCalendarService::NewL();
    	
    	RemoveCalendarFile( service, KTestCal1File );
    	TInt err = AddCalendarFile( service, KTestCal1File );
    	
    	if(err != KErrNone)
    		result = err;
    	
    	RPointerArray<TUIDSet> arruids;
	
	TUIDSet* uids = NULL;

	CEntryAttributes* entryObj = CEntryAttributes::NewL( KEntryAppt );
	
	TRAPD(err_one,entryObj->SetDescriptionL(_L("SAPI weekly meeting sdsdnsbdsdsb sdkjsjk sjkdbks bsdb8808s sdnskjdbsjkdnsjkdjk nnjksndsjn kjsnd jns")));
	if(err_one != KErrNone)
		entryObj->SetDescriptionL(_L("SAPI weekly meeting"));
	
	
	TRAPD(err_two,entryObj->SetLocationL(_L("fsdfsjdnf jnnjns jknsdkjn jkndsjfnsd9030934 ndfns nlsdnf ldnflksn lksdnflkns dlfn lksdfnsdnfl kndflkn")));
	if(err_two != KErrNone)
		entryObj->SetLocationL(_L("Hara"));
	
	
	TRAPD(err_entrystatus,entryObj->SetEntryStatusL(KNullDesC));
	if(err_entrystatus != KErrNone)
		entryObj->SetEntryStatusL(KStatusConfirmed);

	TRAPD(err_three,entryObj->SetMethodL(KTestMethod));
	if(err_three != KErrNone)
		entryObj->SetMethodL(KMethodNone); 
	
	TRAPD(err_four,entryObj->SetPriority(55555e12));
	if(err_four != KErrNone)
		entryObj->SetPriority(5);
	
	
    TRAPD(err_five,entryObj->SetSummaryL(_L("Happens from 9 to 9:30 sdfndfjs n89834 dsfksdfjsdfjdsjflsdjflsdj ljdf")));
    if(err_five != KErrNone)
    	entryObj->SetSummaryL(_L("Happens from 9 to 9:30"));
    
    TTime stTime(TDateTime(2007, EAugust, 8, 9, 0, 0, 0));
	entryObj->SetStartTimeL(stTime);
	
	TTime endTime(TDateTime(2007, EAugust, 8, 9, 30, 0, 0));
	entryObj->SetEndTimeL(endTime);
	
	CCalAlarm* alarm = CCalAlarm::NewL();
	TTime alarmTime(TDateTime(2007,EAugust, 7, 23, 30, 0, 0));
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
    	TInt count = entryArray.Count();
    	if( entryArray.Count() == 1 )
    		{
    		if( !( entryArray[0]->StartTimeL().TimeUtcL() == stTime  && entryArray[0]->DescriptionL().CompareF(_L("SAPI weekly meeting sdsdnsbdsdsb sdkjsjk sjkdbks bsdb8808s sdnskjdbsjkdnsjkdjk nnjksndsjn kjsnd jns")) == 0
    		                                                           && entryArray[0]->LocationL().CompareF(_L("fsdfsjdnf jnnjns jknsdkjn jkndsjfnsd9030934 ndfns nlsdnf ldnflksn lksdnflkns dlfn lksdfnsdnfl kndflkn")) == 0  ) )
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
//	delete entryObj;
//	delete uids;
	__UHEAP_MARKEND;
	return result;
    	   	
        	

    }
    
    
// -----------------------------------------------------------------------------
// Ctcal_add::AddRepeatingEntry
// Add a new daily repeating meeting entry
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_add::AddRepeatingEntry( CStifItemParser& /*aItem*/ )
    {
    	TInt result = KErrNone;
    	__UHEAP_MARK;
    	RPointerArray<TUIDSet> arruids;
    	TInt err_six;
		TUIDSet* uids = NULL;
    	
    CCalendarService* service = CCalendarService::NewL();
    	
    RemoveCalendarFile( service, KTestCal1File );
    AddCalendarFile( service, KTestCal1File );
    CEntryAttributes* entryObj = CEntryAttributes::NewL( KEntryAppt );
	
    TRAPD(err_desc,entryObj->SetDescriptionL(KNullDesC));
    if(err_desc != KErrNone)
    	entryObj->SetDescriptionL(_L("SAPI weekly meeting"));
    	
	TRAPD(err_loc,entryObj->SetLocationL(KNullDesC));
	if(err_loc != KErrNone)
		entryObj->SetLocationL(_L("Hara"));
	
	
	TRAPD(err_one,entryObj->SetEntryStatusL(KStatusTodoNeedsAction));
	if(err_one != KErrNone)
		entryObj->SetEntryStatusL(KStatusCancelled);
	
	entryObj->SetMethodL(KMethodNone);
			
	TRAPD(err_two,entryObj->SetPriority(-5.2));
	if(err_two != KErrNone)
		entryObj->SetPriority(1);
	
    entryObj->SetSummaryL(_L("Repeating entry"));
    
    TTime stTime(TDateTime(2007, EJune, 15, 9, 0, 0, 0));
	entryObj->SetStartTimeL(stTime);
	
	TTime endTime(TDateTime(2007, EJune, 15, 9, 30, 0, 0));
	entryObj->SetEndTimeL(endTime);
	
	CRepeatInfo* rrule = CRepeatInfo::NewL(2);
	    
    rrule->SetStartTimeL(stTime);
	TTime uTime(TDateTime(2007, EJuly, 29, 0, 0, 0, 0));
	rrule->SetUntilTimeL(uTime);
	
	RArray<TDay> days;
	days.Append(EWednesday);
	days.Append(EFriday);
	TRAPD(err_rrule,rrule->SetDaysInWeek(days));
	if(err_rrule != KErrNone)
		rrule->SetDaysInWeek(days);
	
	days.Close();
	
	TRAPD(err_three,entryObj->SetRepeatRule(NULL));
	if(err_three != KErrNone)
			result = KErrGeneral;
	
	
	entryObj->SetRepeatRule(rrule);
	
	
	TRAPD(err_five,service->AddL(KTestCal1File,entryObj,uids));
	if(err_five == KErrNotSupported)
	{
		entryObj->SetEntryStatusL(KStatusCancelled);
		TRAP(err_six,service->AddL(KTestCal1File,entryObj,uids));
	}
	
	
	//TRAPD(err_add,service->AddL(KTestCal1File,entryObj,uids));	

		
    if ( err_six == KErrNone && uids )
	{
		arruids.Append(uids);
		RPointerArray<CCalEntry> entryArray;
    	service->GetListL( KTestCal1File, arruids[0]->iLocalUID , entryArray );
    	TInt count = entryArray.Count();
    	if( entryArray.Count() == 1 )
    		{
    			TCalRRule rRule;
    			entryArray[0]->GetRRuleL( rRule );
    			TCalTime utTime;
				utTime.SetTimeLocalL(TTime(TDateTime(2007, EJuly, 26, 9, 0, 0, 0)));
			
				TInt val = entryArray[0]->DescriptionL().CompareF(KNullDesC);
		//		if( entryArray[0]->DescriptionL().CompareF(KNullDesC) != 0 || rRule.Type() != TCalRRule::EWeekly || rRule.Until().TimeLocalL() != utTime.TimeLocalL() )
				if( entryArray[0]->DescriptionL().CompareF(KNullDesC) != 0 || rRule.Type() != TCalRRule::EWeekly  )
	    		   		result = KErrGeneral;	
	    		
	    	}
	    
        else
	        {
	        result = KErrGeneral;		
	        }
	        count = 0;
		entryArray.ResetAndDestroy();
	    
	 }
	 else
			result = KErrGeneral;	

	RemoveCalendarFile( service, KTestCal1File );
	arruids.ResetAndDestroy();
	if(uids)
//		delete uids;
	delete entryObj;
	delete rrule;
	delete service;
	__UHEAP_MARKEND;
	return result;
	
    }


// -----------------------------------------------------------------------------
// Ctcal_add::AddMonthlyRepeatingEntry
// Add a new monthly repeating meeting entry
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_add::AddMonthlyRepeatingEntry( CStifItemParser& /*aItem*/ )
    {
    		TInt result = KErrNone;
   __UHEAP_MARK;
	
	CCalendarService* service = CCalendarService::NewL();

	RemoveCalendarFile( service, KTestCal1File );
	AddCalendarFile( service, KTestCal1File );

	RPointerArray<TUIDSet> arruids(5);
	
	TUIDSet* uids = NULL;

	CEntryAttributes* entryObj = CEntryAttributes::NewL( KEntryAppt );
	
    entryObj->SetDescriptionL(_L("SAPI weekly meeting"));
	entryObj->SetLocationL(_L("Safed"));
	entryObj->SetEntryStatusL(KStatusConfirmed	);
	
	entryObj->SetMethodL(KMethodNone);
		
	entryObj->SetPriority(15);
    entryObj->SetSummaryL(_L(" Monthly Rep entry"));
    
    TTime stTime(TDateTime(2007, EJuly, 15, 9, 0, 0, 0));
	entryObj->SetStartTimeL(stTime);
	
	TTime endTime(TDateTime(2007, EJuly, 15, 9, 30, 0, 0));
	entryObj->SetEndTimeL(endTime);
	
	CCalAlarm* alarm = CCalAlarm::NewL();
	TTime alarmTime(TDateTime(2007,ESeptember, 15, 7, 30, 0, 0));
	//entryObj->SetAlarm(alarmTime);
	delete alarm;
	
	CRepeatInfo* rrule = CRepeatInfo::NewL(3);    
   	rrule->SetStartTimeL(stTime);
	TTime uTime(TDateTime(2008, ESeptember, 29, 0, 0, 0, 0));
	rrule->SetUntilTimeL(uTime);
	TCalRRule::TDayOfMonth day1(EMonday,1);
	TCalRRule::TDayOfMonth day2(EThursday,4);
	TCalRRule::TDayOfMonth day3(EFriday,5);
	RArray<TCalRRule::TDayOfMonth> monthDays;
	monthDays.Append(day1);
	monthDays.Append(day2);
	monthDays.Append(day3);
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
    		if( !( entryArray[0]->DescriptionL().CompareF(_L("SAPI weekly meeting")) == 0
    		                            &&rRule.Type() == TCalRRule::EMonthly ) )
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


// -----------------------------------------------------------------------------
// Ctcal_add::AddAptWithAttendee
// Add a new meeting entry
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_add::AddAptWithAttendee( CStifItemParser& /*aItem*/ )
    {
    	TInt result = KErrNone;
		
	__UHEAP_MARK;
	
	CCalendarService* service = CCalendarService::NewL();

	RemoveCalendarFile( service, KTestCal1File );
	AddCalendarFile( service, KTestCal1File );

	RPointerArray<TUIDSet> arruids(5);
	
	TUIDSet* uids = NULL;

	CEntryAttributes* entryObj = CEntryAttributes::NewL( KEntryAppt );
	
	entryObj->SetDescriptionL(_L("SAPI weekly meeting"));
	entryObj->SetLocationL(_L("Safed"));
	entryObj->SetEntryStatusL(KStatusConfirmed);

	entryObj->SetMethodL(KMethodNone);
	
	CAttendeeInfo* organizer = CAttendeeInfo::NewL(_L("roshan@gmail.com"));
	CleanupStack::PushL(organizer);
	organizer->SetCommonNameL(_L("Service"));
	entryObj->SetOrganizerDataL(organizer);
	CleanupStack::PopAndDestroy(organizer);
	
	entryObj->SetPhoneOwnerDataL(_L("roshan@gmail.com"));
	
	entryObj->SetPriority(5);
    entryObj->SetSummaryL(_L("Happens from 9 to 9:30"));
    
    TTime stTime(TDateTime(2007, EAugust, 8, 9, 0, 0, 0));
	entryObj->SetStartTimeL(stTime);
	
	TTime endTime(TDateTime(2007, EAugust, 8, 9, 30, 0, 0));
	entryObj->SetEndTimeL(endTime);
	
	
    CAttendeeInfo* attendee = CAttendeeInfo::NewL(_L("roshan@gmail.com"));
    CleanupStack::PushL(attendee);
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
    		TInt count = attendeeList.Count();
    		
    		if( count != 1 )
	    		result = KErrGeneral;	
	    	else
	    	{
	    		if(attendeeList[0]->RoleL() != 0 || attendeeList[0]->StatusL() != 2)	
					result = KErrGeneral;
		
					if(attendeeList[0]->Address().CompareF(_L("roshan@gmail.com")) != 0)
					result = KErrGeneral;
	    	}
	    }
	    
        else
	    {
	       result = KErrGeneral;		
	    }
		entryArray.ResetAndDestroy();
	    
	    }
		else
			result = KErrGeneral;	
		
	arruids.ResetAndDestroy();
	delete entryObj;

	RemoveCalendarFile( service, KTestCal1File );
	
	delete service;
	
	__UHEAP_MARKEND;

	return result;
	
    }

// -----------------------------------------------------------------------------
// Ctcal_add::?member_function
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
/*
TInt Ctcal_add::?member_function(
   CItemParser& aItem )
   {

   ?code

   }
*/

// ========================== OTHER EXPORTED FUNCTIONS =========================
// None

//  End of File
