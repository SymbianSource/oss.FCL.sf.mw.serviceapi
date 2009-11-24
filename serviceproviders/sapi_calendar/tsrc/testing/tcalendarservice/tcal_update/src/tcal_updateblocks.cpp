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
#include "tcal_update.h"
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
// Ctcal_update::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void Ctcal_update::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// Ctcal_update::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt Ctcal_update::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "UpdateToDo", Ctcal_update::UpdateToDo ),
        ENTRY( "UpdateAnny", Ctcal_update::UpdateAnny ),
        ENTRY( "UpdateRepeatingEntry", Ctcal_update::UpdateRepeatingEntry ),
        ENTRY( "UpdateApt", Ctcal_update::UpdateApt ),
        ENTRY( "UpdateAptWithAttendees", Ctcal_update::UpdateAptWithAttendees ),
        ENTRY( "UpdateRepeatDate", Ctcal_update::UpdateRepeatDate ),
        ENTRY( "UpdateInstance", Ctcal_update::UpdateInstance ),
 
        ENTRY( "UpdateToDoWithGlobalId", Ctcal_update::UpdateToDoWithGlobalId ),
        ENTRY( "UpdateInstanceWithGlobalId", Ctcal_update::UpdateInstanceWithGlobalId ),

        //ADD NEW ENTRY HERE

        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }
    
_LIT(KTestCalTestFile                ,"C:calfiledfjsdjf sdfs0923984938409 sfhsdfjhsdfhsdfsdfhsdfh 093u4093402934  sjdlasjdlasjdl jsaldkjas ldjaslkdjlasdjlaskdjlas jdla jdlasjdlasjdlasjddlkasdj1");
_LIT(KTestCal1File                ,"C:calfile1");
_LIT(KTestCal2File                ,"C:calfile2");
_LIT(KTestRep                ,"invalid");


// -----------------------------------------------------------------------------
// Ctcal_update::UpdateToDo
// Menthod to update the  ToDO entry.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_update::UpdateToDo( CStifItemParser& /*aItem*/ )
    {

    TInt result = KErrNone;
	
	
	CCalendarService* service = CCalendarService::NewL();
	
	RemoveCalendarFile( service, KTestCal1File );
//	TRAPD(err_add,AddCalendarFile( service, KTestCalTestFile ));
	AddCalendarFile( service, KTestCal1File);
	

	RPointerArray<TUIDSet> arruids(5);
	
	TUIDSet* uids = NULL;
	
	TInt err_addtodo;
	
//	TInt test_addtodo = AddToDo(service, KTestCalTestFile, uids);
	
//	if(test_addtodo != KErrNone)
		 err_addtodo = AddToDo(service, KTestCal1File, uids);
	
	if(err_addtodo == KErrNone && uids)
		{
		arruids.Append(uids);
		uids = NULL;
		}

		delete uids;
	if ( arruids.Count() > 0 )
		{
	    RPointerArray<CCalEntry> entryArray;
	    
	    CEntryAttributes* entryObj = CEntryAttributes::NewL();
	    
	    
	    entryObj->SetEntryStatusL(KStatusTodoCompleted); 
		
		
		
		
		TRAPD(err_rep,entryObj->SetReplicationL(KTestRep));
		if(err_rep != KErrNone)
			entryObj->SetReplicationL(KReplPrivate);
		
	
	    		
		service->GetListL( KTestCal1File, arruids[0]->iLocalUID , entryArray );

		if( entryArray.Count() == 1 )
			{
			entryObj->SetLocalUid( arruids[0]->iLocalUID );
			
			}
			
		TCalLocalUid modifiedEntryId;	
		TUIDSet* entryUids = NULL;	
	    TRAPD( err, service->AddL(KTestCal1File,entryObj,entryUids) );
	    TInt err_new;
	    TInt err_add;
	    	    	    
	    delete entryUids;
	    entryArray.ResetAndDestroy();
	    if ( err == KErrNone )
	    	{ 
	    	service->GetListL( KTestCal1File, arruids[0]->iLocalUID , entryArray );
	    	if( entryArray.Count() == 1 )
	    		{
	    		if( !(entryArray[0]->ReplicationStatusL() == CCalEntry::EPrivate && entryArray[0]->StatusL() == CCalEntry::ETodoCompleted))
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
    
	return result;
	

    }
    
 // -----------------------------------------------------------------------------
// Ctcal_update::UpdateAnny
// Menthod to update the  Anniversary entry.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_update::UpdateAnny( CStifItemParser& /*aItem*/ )
    {

    TInt result = KErrNone;
	TUIDSet* uids = NULL;
	
	CCalendarService* service = CCalendarService::NewL();
	
	RemoveCalendarFile( service, KTestCal1File );
	AddCalendarFile( service, KTestCal1File);
	
	CEntryAttributes* entryObj = CEntryAttributes::NewL( KEntryTodo );
	
	entryObj->SetDescriptionL(_L("New todo entry created"));
	entryObj->SetSummaryL(_L("TODO Entry"));
	TTime endTime(TDateTime(2007, EAugust, 21, 0, 0, 0, 0));
	entryObj->SetEndTimeL(endTime);
	entryObj->SetReplicationL(KReplOpen);
	entryObj->SetPriority(0);	
	
	TRAPD( errno, service->AddL(KTestCal1File,entryObj,uids) );
	delete entryObj;
	
	
	RPointerArray<TUIDSet> arruids(5);
	
	uids = NULL;
	
	TInt err_anny = AddAnny(service, KTestCal1File, uids);
	
	if(err_anny == KErrNone && uids)
		{
		arruids.Append(uids);
		uids = NULL;
		}

		delete uids;
	if ( arruids.Count() > 0 )
		{
	    RPointerArray<CCalEntry> entryArray;
	    
	    CEntryAttributes* entryObj = CEntryAttributes::NewL();
	    
	    entryObj->SetReplicationL(KReplPrivate);
		
		    		
		service->GetListL( KTestCal1File, arruids[0]->iLocalUID , entryArray );

		if( entryArray.Count() == 1 )
			{
			entryObj->SetLocalUid( 100);
			
			}
			
		TCalLocalUid modifiedEntryId;	
		TUIDSet* entryUids = NULL;	
	    TRAPD( err, service->AddL(KTestCal1File,entryObj,entryUids) );
	    TInt err_new;
	    
	    if(err != KErrNone)
	    {
	    	entryObj->SetLocalUid(arruids[0]->iLocalUID);
	    	entryObj->SetDescriptionL(_L("Anny event modified"));
	    	entryObj->SetPriority(2);
	    	TRAP(err_new,service->AddL(KTestCal1File,entryObj,entryUids));
	    }
	   
	    entryArray.ResetAndDestroy();
	    if ( err_new == KErrNone )
	    	{ 
	    	service->GetListL( KTestCal1File, arruids[0]->iLocalUID , entryArray );
	    	if( entryArray.Count() == 1 )
	    		{
	    		if( !(entryArray[0]->DescriptionL().CompareF(_L("Anny event modified")) == 0 && entryArray[0]->PriorityL() == 2))
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
	    delete entryUids;
	    
	    }
		else
			result = KErrGeneral;	

	RemoveCalendarFile( service, KTestCal1File );
	
	delete service;
	
    
	return result;
	

    }

// -----------------------------------------------------------------------------
// Ctcal_update::UpdateRepeatingEntry
// Menthod to update the  repeating apt entry.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_update::UpdateRepeatingEntry( CStifItemParser& /*aItem*/ )
    {

    TInt result = KErrNone;
	TUIDSet* uids = NULL;
	
	CCalendarService* service = CCalendarService::NewL();
	
	RemoveCalendarFile( service, KTestCal1File );
	AddCalendarFile( service, KTestCal1File);
	
	RPointerArray<TUIDSet> arruids(5);
	
	uids = NULL;
	
	TInt err_apt = AddRepeatingAppointmentEntryL(service, KTestCal1File, uids);
	
	if(err_apt == KErrNone && uids)
		{
		arruids.Append(uids);
		uids = NULL;
		}
		
	AddReminder(service, KTestCal1File, uids);

		delete uids;
		
		
	if ( arruids.Count() > 0 )
		{
	    CEntryAttributes* entryObj = CEntryAttributes::NewL();
	    
	    RPointerArray<CCalEntry> entryArray;
	    
	    TTime stTime(TDateTime(2009, ENovember, 0, 9, 0, 0, 0));
		TRAPD(err_instance,entryObj->SetInstanceStartTimeL(stTime));
		TTime new_stTime(TDateTime(2007, ESeptember, 28, 9, 0, 0, 0));
		//	entryObj->SetInstanceStartTimeL(new_stTime);
			
		
		TTime startTime(TDateTime(2007, ESeptember, 17, 14, 0, 0, 0));
		entryObj->SetStartTimeL(startTime);
		TTime endTime(TDateTime(2007, ESeptember, 17, 17, 30, 0, 0));
		entryObj->SetEndTimeL(endTime);		
			    		
		TTime instancetwo_stTime(TDateTime(2007, ESeptember, 21, 9, 0, 0, 0));

		
		service->GetListL( KTestCal1File, arruids[0]->iLocalUID , entryArray );

		if( entryArray.Count() == 1 )
			{
			entryObj->SetLocalUid( arruids[0]->iLocalUID );
			}
			
		TUIDSet* uids = NULL;
		TInt err_new;
		TCalLocalUid modifiedEntryId;		
	    TRAPD( err, service->AddL(KTestCal1File,entryObj,uids) );
	    if(err != KErrNone)
	    {
	    	entryObj->SetInstanceStartTimeL(new_stTime);
	    	TRAP( err_new, service->AddL(KTestCal1File,entryObj,uids) );
	    }
	    modifiedEntryId = uids->iLocalUID;
	    uids = NULL;
	    
	    entryArray.ResetAndDestroy();
	    if ( err_new == KErrNone )
	    	{ 
	    	service->GetListL( KTestCal1File, modifiedEntryId , entryArray );
	    	TInt count = entryArray.Count();
	    	if( entryArray.Count() == 1 )
	    		{
	    		if( !( entryArray[0]->StartTimeL().TimeUtcL() == startTime && 
	    		    entryArray[0]->EndTimeL().TimeUtcL() == endTime ))
	    		      		result = KErrGeneral;	
		    		
		    	}
	    		
	    	}
        else
	        {
	        result = KErrGeneral;		
	        }
	//	entryArray.ResetAndDestroy();
		entryObj->SetInstanceStartTimeL(instancetwo_stTime);   
		
		entryObj->SetStartTimeL(startTime);
		entryObj->SetEndTimeL(endTime);	
		
		TRAPD(err_add,service->AddL(KTestCal1File,entryObj,uids));
		
		TCalLocalUid new_luid = uids->iLocalUID;
		
		service->GetListL( KTestCal1File, new_luid , entryArray );
		
		if( entryArray.Count() == 2 )
	    	{
	    		if( !( entryArray[1]->StartTimeL().TimeUtcL() == startTime && 
	    		    entryArray[1]->EndTimeL().TimeUtcL() == endTime && new_luid != modifiedEntryId && entryArray[0]->UidL().CompareF(entryArray[1]->UidL()) == 0))
	    		 	    		result = KErrGeneral;	
		    		    	
	    		
	    	}
	    else if (result == KErrNone)
	    	result = KErrGeneral;
		
		entryArray.ResetAndDestroy();
	    arruids.ResetAndDestroy();
	    delete entryObj;
	     delete uids;
	    }
		else
			result = KErrGeneral;	

	RemoveCalendarFile( service, KTestCal1File );
	
	delete service;
	
	return result;

    }


// -----------------------------------------------------------------------------
// Ctcal_update::UpdateApt
// Menthod to update the  repeating apt entry.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_update::UpdateApt( CStifItemParser& /*aItem*/ )
    {

    TInt result = KErrNone;
	TUIDSet* uids = NULL;
	TBuf<40> buf ;
	
	
	CCalendarService* service = CCalendarService::NewL();
	
	RemoveCalendarFile( service, KTestCal1File );
	AddCalendarFile( service, KTestCal1File);
	
	RPointerArray<TUIDSet> arruids(5);
	
	uids = NULL;
	
	TInt err_apt = AddAppointmentWithAttendees(service, KTestCal1File, uids);
	
	if(err_apt == KErrNone && uids)
		{
		arruids.Append(uids);
		uids = NULL;
		}
	
	
	AddReminder(service, KTestCal1File, uids);
	
	
	arruids.Append(uids);
	
	uids = NULL;
			
		
	if ( arruids.Count() > 0 )
		{
	    CEntryAttributes* entryObj = CEntryAttributes::NewL();
	    
	    RPointerArray<CCalEntry> entryArray;
	    
	    CAttendeeInfo* organizer=CAttendeeInfo::NewL(_L("hello@gmail.com"));
		entryObj->SetOrganizerDataL(organizer);
		delete organizer;
	
		entryObj->SetPhoneOwnerDataL(_L("roshan@gmail.com"));
	
		entryObj->SetPriority(5);

		CAttendeeInfo* attendee = CAttendeeInfo::NewL(_L("roshan_shah@gmail.com"));
		attendee->SetRoleL(KAttRoleChair);
		attendee->SetStatusL(KAttStatusInProcess);
    	attendee->SetRsvp(ETrue);
    	
    	TRAPD(err_attendee,entryObj->AddAttendeeL(attendee));
    
		delete attendee;
    
		service->GetListL( KTestCal1File, arruids[0]->iLocalUID , entryArray );

		if( entryArray.Count() == 1 )
			{
			entryObj->SetLocalUid( arruids[0]->iLocalUID );
			}
			
		TCalLocalUid old_luid = arruids[0]->iLocalUID;
		TUIDSet* uids = NULL;
		TInt err_new;
		TCalLocalUid modifiedEntryId;		
	    TRAPD( err, service->AddL(KTestCal1File,entryObj,uids) );
	    if(err != KErrNone)
	    {
	    	entryObj->SetPhoneOwnerDataL(_L("roshan_shah@gmail.com"));
	    	TRAP( err_new, service->AddL(KTestCal1File,entryObj,uids) );
	    		
	    }
	    
	    modifiedEntryId = arruids[0]->iLocalUID;
	    TCalLocalUid new_luid = uids->iLocalUID;
	    
	    entryArray.ResetAndDestroy();
	    if ( err_new == KErrNone )
	    	{ 
	    	service->GetListL( KTestCal1File, modifiedEntryId , entryArray );
	    	TInt count = entryArray.Count();
	     
	    	if( entryArray.Count() == 1 )
	    		{
	    			RPointerArray<CCalAttendee> attendeeList;
	    			attendeeList = entryArray[0]->AttendeesL();
	    			TInt count = attendeeList.Count();
	    			if(attendeeList.Count() != 2 )
	    			{
	    				for(TInt index=0;index<count;index++)
	    				{
	    						buf.Copy(attendeeList[index]->Address()) ;
								iLog->Log(buf) ;
								
	    				}
	    				result = KErrGeneral;
	    			}
	    		      			
		    		
		    	}
	    		
	    	}
        else
	        {
	        result = KErrGeneral;		
	        }
	
		entryObj->SetLocalUid( arruids[1]->iLocalUID );
		TRAPD(err_luid,service->AddL(KTestCal1File,entryObj,uids) );
		
		if(err_luid != KErrArgument && result == KErrNone)
			result = KErrGeneral;
		
		entryArray.ResetAndDestroy();
	  //  arruids.ResetAndDestroy();
	    delete entryObj;
	     
	    }
		else
			result = KErrGeneral;	
	arruids.ResetAndDestroy();
	RemoveCalendarFile( service, KTestCal1File );
	
	delete service;
	
	return result;

    }


// -----------------------------------------------------------------------------
// Ctcal_update::UpdateAptWithAttendees
// Menthod to update the attendees for repeating/non repeating entry
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_update::UpdateAptWithAttendees( CStifItemParser& /*aItem*/ )
    {

   TInt result = KErrNone;
   TInt count;
	
	
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
		TCalLocalUid old_luid = arruids[0]->iLocalUID;		
	    TRAPD( err, service->AddL(KTestCal1File,entryObj,uids) );
	    modifiedEntryId = uids->iLocalUID;
	    delete uids;
	    entryArray.ResetAndDestroy();
	    if ( err == KErrNone && modifiedEntryId == old_luid )
	    	{ 
	    	service->GetListL( KTestCal1File, modifiedEntryId , entryArray );
	       	if( entryArray.Count() == 1 )
	    		{
	    		RPointerArray<CCalAttendee> attendeeList;
	    		attendeeList = entryArray[0]->AttendeesL(); 
	    		count = attendeeList.Count();
	    		if( attendeeList.Count() != 4 )
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
	
	
	return result;

    }


// -----------------------------------------------------------------------------
// Ctcal_update::UpdateRepeatDate
// Menthod to add more repeating dates to existing apt entry
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_update::UpdateRepeatDate( CStifItemParser& /*aItem*/ )
    {

   TInt result = KErrNone;
   TInt count;
	
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
	    
	    RPointerArray<CCalInstance> instanceArray;

		CCalendarFilter *filter = CCalendarFilter::NewL();
		
		filter->SetFilterTypeL( KEntryAppt );
		
		service->GetListL( KTestCal1File, filter , instanceArray );
	    	count = instanceArray.Count();
	    
	    
	    TTime rDate(TDateTime(2007, EOctober, 5, 9, 0, 0, 0)); 
   		TCalTime rTime;
    	rTime.SetTimeUtcL(rDate);
   		entryObj->AddRepeatDateL(rDate);
   		
   		 		
   		TTime rDate1(TDateTime(2007, EOctober, 20, 9, 0, 0, 0)); 
   	//	TCalTime rTime;
   		rTime.SetTimeUtcL(rDate1);
   		entryObj->AddRepeatDateL(rDate1);
   		
   		TTime rDate2(TDateTime(2007, ESeptember, 21, 9, 0, 0, 0)); 
   	//	TCalTime rTime;
   		rTime.SetTimeUtcL(rDate2);
   		entryObj->AddRepeatDateL(rDate2); 
   		
   	    
		service->GetListL( KTestCal1File, arruids[0]->iLocalUID , entryArray );

		if( entryArray.Count() == 1 )
			{
			entryObj->SetLocalUid( arruids[0]->iLocalUID );
			}
			
		TUIDSet* uids = NULL;
		TCalLocalUid modifiedEntryId;
		TCalLocalUid old_luid = arruids[0]->iLocalUID;		
	    TRAPD( err, service->AddL(KTestCal1File,entryObj,uids) );
	    modifiedEntryId = uids->iLocalUID;
	    delete uids;
	    
	    entryArray.ResetAndDestroy();
	    instanceArray.ResetAndDestroy();
	    count = 0;
	    
	    if ( err == KErrNone)
	    	{ 
	    	service->GetListL( KTestCal1File, filter , instanceArray );
	    	count = instanceArray.Count();
	    	if(count != 16)
	    		result = KErrGeneral;
	    		       			
	    	}
        
        delete filter;
		entryArray.ResetAndDestroy();
		instanceArray.ResetAndDestroy();
	    arruids.ResetAndDestroy();
	    delete entryObj;
	    }
		else
			result = KErrGeneral;	
		
	delete uids;
	
	uids = NULL;

	delete service;
	
	__UHEAP_MARKEND;
	
	return result;

    }


// -----------------------------------------------------------------------------
// Ctcal_update::UpdateInstance
// Menthod to add more repeating dates to existing apt entry
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_update::UpdateInstance( CStifItemParser& /*aItem*/ )
    {

   TInt result = KErrNone;
	
	__UHEAP_MARK;
	
	CCalendarService* service = CCalendarService::NewL();
	
	RemoveCalendarFile( service, KTestCal1File );
	AddCalendarFile( service, KTestCal1File );

	RPointerArray<TUIDSet> arruids(5);
	
	RPointerArray<CCalInstance> calInstanceArray;
	
	CCalendarFilter *getListfilter2 = CCalendarFilter::NewL();
	
	getListfilter2->SetFilterTypeL( KIncludeAll );
	
	TUIDSet* uids = NULL;
	
	if(AddRepeatingAppointmentEntryL(service, KTestCal1File, uids) == KErrNone && uids)
		{
		arruids.Append(uids);
		uids = NULL;
		}
		
	if(AddEvent(service, KTestCal1File, uids) == KErrNone && uids)
		{
		arruids.Append(uids);
		uids = NULL;
		}
		
	service->GetListL( KTestCal1File, getListfilter2 , calInstanceArray );
	
	TInt count = calInstanceArray.Count();
	
	calInstanceArray.ResetAndDestroy();
	

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
	    	   	
		    	getListfilter2->SetFilterTypeL( KIncludeAll );
		    
		    	service->GetListL( KTestCal1File, getListfilter2 , calInstanceArray );
	
			    TInt new_count = calInstanceArray.Count();
			    if(new_count != count)
			    {
			    	
			    	result = KErrGeneral;
			    }
				 calInstanceArray.ResetAndDestroy();
	    		delete getListfilter2;
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
// Ctcal_update::?member_function
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
/*
TInt Ctcal_update::?member_function(
   CItemParser& aItem )
   {

   ?code

   }
*/

// ========================== OTHER EXPORTED FUNCTIONS =========================
// None

//  End of File
TInt Ctcal_update::UpdateToDoWithGlobalId( CStifItemParser& /*aItem*/ )
    {

    TInt result = KErrNone;
    
    
    CCalendarService* service = CCalendarService::NewL();
    
    RemoveCalendarFile( service, KTestCal1File );
//  TRAPD(err_add,AddCalendarFile( service, KTestCalTestFile ));
    AddCalendarFile( service, KTestCal1File);
    

    RPointerArray<TUIDSet> arruids(5);
    
    TUIDSet* uids = NULL;
    
    TInt err_addtodo;
    
//  TInt test_addtodo = AddToDo(service, KTestCalTestFile, uids);
    
//  if(test_addtodo != KErrNone)
         err_addtodo = AddToDo(service, KTestCal1File, uids);
    
    if(err_addtodo == KErrNone && uids)
        {
        arruids.Append(uids);
        uids = NULL;
        }

        delete uids;
    if ( arruids.Count() > 0 )
        {
        RPointerArray<CCalEntry> entryArray;
        
        CEntryAttributes* entryObj = CEntryAttributes::NewL();
        
        
        entryObj->SetEntryStatusL(KStatusTodoCompleted); 
        
        
        
        
        TRAPD(err_rep,entryObj->SetReplicationL(KTestRep));
        if(err_rep != KErrNone)
            entryObj->SetReplicationL(KReplPrivate);
        
    
                
        service->GetListL( KTestCal1File, *(arruids[0]->iGlobalUID) , entryArray );

        if( entryArray.Count() == 1 )
            {
            entryObj->SetUidL( *(arruids[0]->iGlobalUID) );
            
            }
            
        TCalLocalUid modifiedEntryId;   
        TUIDSet* entryUids = NULL;  
        TRAPD( err, service->AddL(KTestCal1File,entryObj,entryUids) );
        TInt err_new;
        TInt err_add;
                        
        delete entryUids;
        entryArray.ResetAndDestroy();
        if ( err == KErrNone )
            { 
            service->GetListL( KTestCal1File, *(arruids[0]->iGlobalUID) , entryArray );
            if( entryArray.Count() == 1 )
                {
                if( !(entryArray[0]->ReplicationStatusL() == CCalEntry::EPrivate && entryArray[0]->StatusL() == CCalEntry::ETodoCompleted))
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
    
    return result;
    

    }
    
TInt Ctcal_update::UpdateInstanceWithGlobalId( CStifItemParser& /*aItem*/ )
    {

   TInt result = KErrNone;
    
    __UHEAP_MARK;
    
    CCalendarService* service = CCalendarService::NewL();
    
    RemoveCalendarFile( service, KTestCal1File );
    AddCalendarFile( service, KTestCal1File );

    RPointerArray<TUIDSet> arruids(5);
    
    RPointerArray<CCalInstance> calInstanceArray;
    
    CCalendarFilter *getListfilter2 = CCalendarFilter::NewL();
    
    getListfilter2->SetFilterTypeL( KIncludeAll );
    
    TUIDSet* uids = NULL;
    
    if(AddRepeatingAppointmentEntryL(service, KTestCal1File, uids) == KErrNone && uids)
        {
        arruids.Append(uids);
        uids = NULL;
        }
        
    if(AddEvent(service, KTestCal1File, uids) == KErrNone && uids)
        {
        arruids.Append(uids);
        uids = NULL;
        }
        
    service->GetListL( KTestCal1File, getListfilter2 , calInstanceArray );
    
    TInt count = calInstanceArray.Count();
    
    calInstanceArray.ResetAndDestroy();
    

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
        
        service->GetListL( KTestCal1File, *(arruids[0]->iGlobalUID) , entryArray );

        if( entryArray.Count() == 1 )
            {
            entryObj->SetUidL( *(arruids[0]->iGlobalUID) );
            }
            
        TUIDSet* uids = NULL;
       // TCalLocalUid modifiedEntryId;       
        TRAPD( err, service->AddL(KTestCal1File,entryObj,uids) );
        //modifiedEntryId = uids->iLocalUID;
        delete uids;
        entryArray.ResetAndDestroy();
        if ( err == KErrNone )
            { 
                
                getListfilter2->SetFilterTypeL( KIncludeAll );
            
                service->GetListL( KTestCal1File, getListfilter2 , calInstanceArray );
    
                TInt new_count = calInstanceArray.Count();
                if(new_count != count)
                {
                    
                    result = KErrGeneral;
                }
                 calInstanceArray.ResetAndDestroy();
                delete getListfilter2;
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
