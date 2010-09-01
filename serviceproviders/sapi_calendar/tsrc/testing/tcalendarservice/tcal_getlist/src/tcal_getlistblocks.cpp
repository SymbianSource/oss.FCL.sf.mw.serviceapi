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
#include <e32std.h>
#include <f32file.h> //for RFile and Rfs
#include <StifParser.h>
#include <StifTestInterface.h>
#include "tcal_getlist.h"
#include "calendarheader.h"
#include "calendarservice.h"
#include <calentry.h>//for CCalEntry
#include <calinstanceview.h>//for CCalInstance
#include <calcommon.h>//for Filter Type Enum Constants
#include <calinstance.h>
#include "teststartconsolealarmserver.h"

#include "calgetlisttestcases.h"

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
TInt AddRepeatingAptEntryL(CCalendarService* aService, const TDesC& name, TUIDSet*& uids);

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


struct TUIDSetTest 
	{
	
	TCalLocalUid iLocalUID;
	HBufC8*  iGlobalUID;
	
	TUIDSetTest():iGlobalUID(NULL){}
	
	~TUIDSetTest()
		{
		delete iGlobalUID;
		iGlobalUID = NULL;
		}
	};
// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctcal_getlist::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void Ctcal_getlist::Delete() 
    {

    }


// -----------------------------------------------------------------------------
// Ctcal_getlist::printUid
// Log the GUID of calendar entry passed. 
// Called from other member functions. 
// -----------------------------------------------------------------------------
//
void Ctcal_getlist::printUid(const TDesC8& aGuid)
{
	TInt err_alloc = KErrNone;
}


// -----------------------------------------------------------------------------
// Ctcal_getlist::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt Ctcal_getlist::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "EmptyGetList"   , Ctcal_getlist::EmptyGetList ),
		ENTRY( "AddGetList"   , Ctcal_getlist::AddGetList ),
		ENTRY( "DeleteDefaultCalendar"   , Ctcal_getlist::DeleteDefaultCalendar ),
		ENTRY( "GetDefaultCalendar"   , Ctcal_getlist::GetDefaultCalendar ),
		ENTRY( "DefaultArgTest"   , Ctcal_getlist::DefaultArgTest ),
		ENTRY( "InvalidArgTest"   , Ctcal_getlist::InvalidArgTest ),
		ENTRY( "GetCalByGUid"   , Ctcal_getlist::GetCalByGUid ),
		ENTRY( "GetUpdatedEntByGuid"   , Ctcal_getlist::GetUpdatedEntByGuid ),
		ENTRY( "GetUpdatedEntByLuid"   , Ctcal_getlist::GetUpdatedEntByLuid ),
		ENTRY( "GetCalByLuid"   , Ctcal_getlist::GetCalByLuid ),
		ENTRY( "GetCalEntBySearchFilter"   , Ctcal_getlist::GetCalEntBySearchFilter ),
		ENTRY( "GetCalEntByTimeFilter"   , Ctcal_getlist::GetCalEntByTimeFilter ),
		ENTRY( "GetCalEntByTypeFilter"   , Ctcal_getlist::GetCalEntByTypeFilter ),

		ENTRY( "GetListTimeRangeFilterAsync",       Ctcal_getlist::GetListTimeRangeFilterAsync ),
        ENTRY( "GetListGuidFilterAsync",       Ctcal_getlist::GetListGuidFilterAsync ),
        ENTRY( "GetListLuidFilterAsync",       Ctcal_getlist::GetListLuidFilterAsync ),
        ENTRY( "GetListTextFilterAsync",       Ctcal_getlist::GetListTextFilterAsync ),
        ENTRY( "GetListTypeFilterAsync",       Ctcal_getlist::GetListTypeFilterAsync ),
        ENTRY( "GetListInvalidGuidFilterAsync",       Ctcal_getlist::GetListInvalidGuidFilterAsync ),
        ENTRY( "GetListInvalidLuidFilterAsync",       Ctcal_getlist::GetListInvalidLuidFilterAsync ),

        //ADD NEW ENTRY HERE

        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }


// -----------------------------------------------------------------------------
// Ctcal_getlist::EmptyGetList
// To test GetList API on calendar files when there are no calendar files. Should return default calendar
// (other items were commented in a header).
// -----------------------------------------------------------------------------

//
TInt Ctcal_getlist::EmptyGetList( CStifItemParser& /*aItem*/ )
    { 

	 TInt result = KErrNone;
	 __UHEAP_MARK;
	 
    // Print to UI
    _LIT( KTestCal                ,"C:Calendar");
    _LIT( KExample, "In Example" );

	
	CDesCArray *allCalendarNames = NULL;
	
	TInt Noofitems;
	

//	TInt Noofitems = allCalendarNames->Count();
	
	 CCalendarService* service = NULL;
	 
	 TRAPD(err_one,service = CCalendarService::NewL());
	 
	TInt flag=0;		
	
	if(service && err_one == KErrNone)
		{
			TRAPD( err , service->GetListL( allCalendarNames, EFalse ) );
			if( err == KErrNone )
			{
				if( allCalendarNames )
				{
					Noofitems = allCalendarNames->Count();		
					
				/*	iLog->Log(_L("element"));
				 	iLog->Log("%s",element.Ptr());
					TBuf<20> buf ;
					buf.Copy(element) ;
					iLog->Log(buf) ;*/
					for(TInt i=0;i<Noofitems;i++)
					{
						TPtrC16 element = allCalendarNames->MdcaPoint(i);
						if(element.Compare(KTestCal) == 0)
						{
							allCalendarNames->Reset();
							flag=1;
							break;
						}
					}		
											
				}
				else
					result = KErrGeneral;
			}
			else
				result=err;
		}

	if(!result && !flag)
		result = KErrGeneral;
	
	delete allCalendarNames;
	delete service; 

	__UHEAP_MARKEND;
    return result;

    }
    
// -----------------------------------------------------------------------------
// Ctcal_getlist::AddGetList
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------

//
TInt Ctcal_getlist::AddGetList( CStifItemParser& /*aItem*/ )
    {

	 TInt result = KErrNone;
	 __UHEAP_MARK;
	 
    // Print to UI
    _LIT( Ktcal_getlist, "tcal_getlist" );
    _LIT( KExample, "In Example" );
    _LIT( KTestCalFile                ,"C:Calendar");
    _LIT(KTestCal1File                ,"C:getlistcal1");
	_LIT(KTestCal2File                ,"C:getlistcal2"); 
	
	TInt count=0;
	TInt cal1_flag = 0, cal2_flag =0, cal_flag =0;
          
    CDesCArray* allCalendarNames = NULL;

//	CDesCArray* allCalendarNames;
	
	 CCalendarService* service = NULL;
	 
	 TRAPD(err_one,service = CCalendarService::NewL());
	 
	if(service && err_one == KErrNone)
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
						for(TInt i=0;i<allCalendarNames->Count();i++)
						{
							if(allCalendarNames->MdcaPoint(i).Compare(KTestCal1File) == 0)
							{
								cal1_flag=1;
							}
							else if(allCalendarNames->MdcaPoint(i).Compare(KTestCal2File) == 0)
							{
								cal2_flag=1;
						
							}
							else if(allCalendarNames->MdcaPoint(i).Compare(KTestCalFile) == 0)
							{
								cal_flag=1;
						
							}
						}						
						
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

	if(!result && (!cal_flag || !cal1_flag || !cal2_flag))
		result = KErrGeneral;
	
	RemoveCalendarFile( service, KTestCal1File );
	RemoveCalendarFile( service, KTestCal2File );
	
	delete allCalendarNames;
	delete service;

	__UHEAP_MARKEND;
    return result;

    }


// -----------------------------------------------------------------------------
// Ctcal_getlist::DeleteDefaultCalendar
// Attempt to delete default calendar. Deletion of default calendar not supported
// (other items were commented in a header).
// -----------------------------------------------------------------------------

//
TInt Ctcal_getlist::DeleteDefaultCalendar( CStifItemParser& /*aItem*/ )
    { 

	 TInt result = KErrGeneral;
	 __UHEAP_MARK;
	 
    // Print to UI
    _LIT( KTestCalFile                ,"C:Calendar");
    
	
	
	
//	TInt Noofitems;
	

	 CCalendarService* service = NULL;
	 
	 TRAPD(err_one,service = CCalendarService::NewL());
	
	if(err_one == KErrNone && service)
		{
		//	TRAPD(err_delete,RemoveCalendarFile( service, KTestCalFile ));
			TInt err_delete = RemoveCalendarFile( service, KTestCalFile );
			if(err_delete == KErrNotSupported)
			{
				result = KErrNone;
			}
			
				
		}

	delete service; 
	__UHEAP_MARKEND;
    return result;

    }

// -----------------------------------------------------------------------------
// Ctcal_getlist::GetDefaultCalendar
// Attempt to retrieve default calendar in the presence of other calendar files
// (other items were commented in a header).
// -----------------------------------------------------------------------------

//
TInt Ctcal_getlist::GetDefaultCalendar( CStifItemParser& /*aItem*/ )
    { 

		TInt result = KErrNone;
    _LIT( Ktcal_getlist, "tcal_getlist" );
    _LIT( KExample, "In Example" );
    _LIT(KTestCal1File                ,"C:getlistcal1");
	_LIT(KTestCal2File                ,"C:getlistcal2"); 
	
	
          
    CDesCArray* allCalendarNames = NULL;

//	CDesCArray* allCalendarNames;
	
	 CCalendarService* service = NULL;
	 
	TRAPD(err_one,service = CCalendarService::NewL());
	 
	RemoveCalendarFile( service, KTestCal1File );
	RemoveCalendarFile( service, KTestCal2File );
	TInt count = 0;
	
	TRAPD( err_getlist , service->GetListL( allCalendarNames, EFalse ) );
	
	if(!err_getlist)
	{
		count = allCalendarNames->Count() ;
		allCalendarNames->Reset();
	}
	else
		result = KErrGeneral;
	
	if(!result && service && !err_one)
		{
		TInt calAdderr = AddCalendarFile(service, KTestCal1File);
		if( calAdderr == KErrNone || calAdderr == KErrAlreadyExists )	
			{
			calAdderr = AddCalendarFile(service, KTestCal2File);
			if( calAdderr == KErrNone || calAdderr == KErrAlreadyExists )	
				{
				TRAPD( err , service->GetListL( allCalendarNames, ETrue ) );
				
		
				if( err == KErrNone )
					{
					if( allCalendarNames )
						{
						TInt pos1, pos2;
					//	if( allCalendarNames->Count() < 2 || allCalendarNames->Find(KTestCal1File, pos1) != 0 || allCalendarNames->Find(KTestCal2File, pos2) != 0 )
						if(allCalendarNames->Count() != 1)
							result = KErrGeneral;
						else
							allCalendarNames->Reset();
						
						service->GetListL( allCalendarNames, EFalse );
						if(!result && allCalendarNames->Count() != count+2)
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
	if(!result)
	{
		service->GetListL( allCalendarNames, EFalse );
		if(allCalendarNames->Count() != count)
			result = KErrGeneral;
	}
	
	
	allCalendarNames->Reset();
	
	delete allCalendarNames;
	delete service;


	__UHEAP_MARKEND;
    return result;
	

    }
    
    
// -----------------------------------------------------------------------------
// Ctcal_getlist::DefaultArgTest
// Attempt to test GetList for default argument 
// (other items were commented in a header).
// -----------------------------------------------------------------------------

//
TInt Ctcal_getlist::DefaultArgTest( CStifItemParser& /*aItem*/ )
    { 

	 TInt result = KErrNone;
	 TInt flag=0;
	 __UHEAP_MARK;
	 
    // Print to UI
    _LIT( KTestCalFile                ,"C:Calendar");
    _LIT(KTestCal1File                ,"C:getlistcal1"); 
    
	
	CDesCArray *allCalendarNames = NULL;
	
 	 CCalendarService* service = NULL;
	 
	 TRAPD(err_one,service = CCalendarService::NewL());
	
	if(err_one == KErrNone && service)
	{
			//Checking for default argument value of EFalse
			TRAPD( err , service->GetListL( allCalendarNames) );
			if(err == KErrNone && allCalendarNames)
			{
				TInt count = allCalendarNames->Count();
				for(TInt i=0;i<count;i++)
				{
					if(allCalendarNames->MdcaPoint(i).Compare(KTestCalFile) == 0)
					{
						flag=1;
						break;
					}
				}			
			}
			else
				result = err;	
	}
	else
		result = err_one;
	
		
	if(!result && !flag)
		result = KErrGeneral;
	
	if(allCalendarNames)
		allCalendarNames->Reset();
	
	
	delete allCalendarNames;
	delete service; 


	__UHEAP_MARKEND;
    return result;

    }

// -----------------------------------------------------------------------------
// Ctcal_getlist::InvalidArgTest
// Attempt to test GetList for invalid argument
// (other items were commented in a header).
// -----------------------------------------------------------------------------

//
TInt Ctcal_getlist::InvalidArgTest( CStifItemParser& /*aItem*/ )
    { 
	__UHEAP_MARK;
	 TInt result = KErrNone;
	 TInt result_one = KErrNone;
	 TInt result_two = KErrNone;
	 TInt result_three = KErrNone;
	 TInt result_four = KErrNone;
	 TInt count;
	 TBuf<40> buf;
	 TCalLocalUid luid;
	 
	 
    // Print to UI
    _LIT( KTestCalFile                ,"C:Calendar");
    _LIT(KTestCal1File                ,"C:getlistcal1");
    _LIT(KTestCal2File                ,"C:getlistcal2");
    _LIT(KInvalidFile                ,"F:check");
    
    
	RPointerArray<TUIDSet> arruids;
	RPointerArray<CCalEntry> entryArray(1);
	TUIDSet* uids = NULL;
		
	CCalendarService* service = NULL;
	TRAPD(err_one,service = CCalendarService::NewL());	 
	RemoveCalendarFile( service, KTestCal1File );
	
	 
	 if(err_one == KErrNone && service)
	 {
	 	TInt calAdderr = AddCalendarFile(service, KTestCal1File);
		if( calAdderr == KErrNone || calAdderr == KErrAlreadyExists )	
		{
			result_one = KErrNone;			
		}
		else
			result = calAdderr;
	 } 
	

	if(AddAppointmentWithAttendees(service, KTestCal1File, uids) == KErrNone && uids)
		{
			arruids.Append(uids);
			buf.Copy(*(uids->iGlobalUID));
	//		iLog->Log(buf);
	//		uids = NULL;
		}

	TCalLocalUid uid_entry = uids->iLocalUID;	
	
	if ( arruids.Count() > 0 )
		{    
	     
	    TRAPD( err_two, service->GetListL( KTestCal1File, NULL, entryArray ));
	    if ( err_two == KErrNone )
	    	{ 
	    		if(entryArray.Count())
	    		{
	    			result_two = KErrGeneral;
	    			entryArray.ResetAndDestroy();
	    		}
	    	}
	    else
	    	result_two = err_two;
	    
	    
	    
	   TRAPD( err_three, service->GetListL( KTestCal1File, 12340e11, entryArray ));
	   
	    if ( err_three == KErrNone )
	    	{ 
	    		if(entryArray.Count())
	    		{
	    			result_two = KErrGeneral;
	    			entryArray.ResetAndDestroy();
	    		}
	    	}
	    else
	    	result_two = err_three;
	    
	    
	    TRAPD( err_four, service->GetListL( KTestCal1File, 2000000, entryArray ));
	    if ( err_four == KErrNone )
	    	{ 
	    		if(entryArray.Count())
	    		{
	    			result_two = KErrGeneral;
	    			entryArray.ResetAndDestroy();
	    		}
	    	}
	    else
	    	result_two = err_four;
	    
	    
	    
	    TRAPD( err_five, service->GetListL( KTestCal1File, 123e-12, entryArray ));
	    if ( err_five == KErrNone )
	    	{ 
	    		if(entryArray.Count())
	    		{
	    			result_two = KErrGeneral;
	    			entryArray.ResetAndDestroy();
	    		}
	    	}
	    else
	    	result_two = err_five;
	    
	    
	    TRAPD( err_six, service->GetListL( KTestCal1File, 45.33343434343493823423948238432423423, entryArray ));
	    if ( err_six == KErrNone )
	    	{ 
				if(entryArray.Count())
	    		{
	    			result_two = KErrGeneral;
	    			entryArray.ResetAndDestroy();
	    		}
	    	}
	    else
	    	result_two = err_six;       
	    
	    
	    TRAPD( err_nine, service->GetListL( KTestCalFile, NULL, entryArray ));
	    if ( err_nine == KErrNone )
	    	{ 
	    		if(entryArray.Count())
	    		{
	    			result_two = KErrGeneral;
	    			entryArray.ResetAndDestroy();
	    		}
	    	}
	    else
	    	result_two = err_nine;
	            
	    
	    TRAPD( err_eleven, service->GetListL( KTestCal1File, arruids[0]->iLocalUID, entryArray ));
	    if ( err_eleven == KErrNone )
	    	{ 
	    		service->GetListL( KTestCal1File, arruids[0]->iLocalUID, entryArray );
	    		count = entryArray.Count();
	    	if( !( entryArray.Count() == 2 && entryArray[0]->LocalUidL() == arruids[0]->iLocalUID && entryArray[1]->LocalUidL() == arruids[0]->iLocalUID))
	    		{
	    		result_three = KErrGeneral;
	    	
	    		}
	    		if(count > 0)
	    		{
	    			buf.Copy(entryArray[0]->UidL());
	    			luid = entryArray[0]->LocalUidL();   
	    			entryArray.ResetAndDestroy(); 
	    			count = 0; 			
	    		}
	    	}
	    else
	    	result_three = err_eleven;
	    
	    
	    TRAPD( err_twelve, service->GetListL( KTestCal1File, arruids[0]->iLocalUID, entryArray ));
	    if ( err_twelve == KErrNone )
	    	{ 
	    		entryArray.ResetAndDestroy();
	    		service->GetListL( KTestCal1File, arruids[0]->iLocalUID, entryArray );
	    		count = entryArray.Count();
	    	if( !( entryArray.Count() == 1 && entryArray[0]->LocalUidL() == arruids[0]->iLocalUID ))
	    		{
	    		result_four = KErrGeneral;
	    	
	    		}
	    		if(count > 0)
	    		{
	    			buf.Copy(entryArray[0]->UidL());
	    			luid = entryArray[0]->LocalUidL();  
	    			entryArray.ResetAndDestroy();  
	    			count = 0;  			
	    		}
	    	}
	    else
	    	result_four = err_twelve;
	    
		}
	    
	entryArray.ResetAndDestroy();
	arruids.ResetAndDestroy();    
	RemoveCalendarFile( service, KTestCal1File );
	    
	delete service; 	
	
	uids = NULL;
	
	__UHEAP_MARKEND;
	 if(result == KErrNone && result_one == KErrNone && result_two == KErrNone && result_three == KErrNone && result_four == KErrNone)
    return KErrNone;
    
    else
    return KErrGeneral;


    }



// -----------------------------------------------------------------------------
// Ctcal_getlist::GetCalByGUid
// Get calendar entries based on GUID
// (other items were commented in a header).
// -----------------------------------------------------------------------------

TInt Ctcal_getlist::GetCalByGUid( CStifItemParser& /*aItem*/ )
	{
	TInt result = KErrNone;
	__UHEAP_MARK;
//	__UHEAP_MARK;
	
	_LIT(KTestCal1File                ,"C:getlistcal1");
	_LIT( KTestCalFile                ,"C:Calendar");
	_LIT(KTestCal2File                ,"ALH3434MDFLMEF046");

	HBufC8* guid = NULL;
	TBuf<40> buf;
	
//	const TDesC8& test_guid = *guid;

	
	
	CCalendarService* service = CCalendarService::NewL();
	
	RemoveCalendarFile( service, KTestCal1File );
	AddCalendarFile( service, KTestCal1File );

	RPointerArray<TUIDSet> arruids;
	
	TUIDSet* uids = NULL;
	
	if(AddRepeatingAppointmentEntryL(service, KTestCal1File, uids) == KErrNone && uids)
		{
		arruids.Append(uids);
		buf.Copy(*(uids->iGlobalUID));
		}


	
	if(AddToDo( service, KTestCal1File, uids ) == KErrNone && uids)
	{
		arruids.Append(uids);
		buf.Copy(*(uids->iGlobalUID));
	//	iLog->Log(buf);
	}
	
	if(AddAnny( service, KTestCal1File, uids ) == KErrNone && uids)
	{
		arruids.Append(uids);
		buf.Copy(*(uids->iGlobalUID));
	//	iLog->Log(buf);
	}
	
	if(AddReminder( service, KTestCal1File, uids ) == KErrNone && uids)
	{
		arruids.Append(uids);
		//iLog->Log(*(uids->iGlobalUID)) ;
		buf.Copy(*(uids->iGlobalUID));
	//	iLog->Log(buf);
	}

	if(AddEvent(service, KTestCal1File, uids) == KErrNone && uids)
		{
		arruids.Append(uids);
		buf.Copy(*(uids->iGlobalUID));
		//iLog->Log(buf);
	//	uids = NULL;
		}
	
	TInt entry_count = arruids.Count();
	//printUid(*(arruids[0]->iGlobalUID));
	

	
	
	if ( arruids.Count() > 0 )
		{
		
	    RPointerArray<CCalEntry> entryArray(1);
	     
	    TRAPD( err_one, service->GetListL( KTestCal1File, *(arruids[0]->iGlobalUID), entryArray ));
	    if ( err_one == KErrNone )
	    	{ 
	    		TInt count = entryArray.Count();
	    	if( !( entryArray.Count() == 1 && entryArray[0]->UidL().CompareF(*(arruids[0]->iGlobalUID)) == 0 ))
	    		{
	    		result = KErrGeneral;
	    	
	    		}
	    	}
	    else
	    	result = err_one;	
	    
	//    entryArray.ResetAndDestroy();
	    
	    if(result == KErrNone)
	    {
	    	TRAPD( err_two, service->GetListL( KTestCal1File, *(arruids[1]->iGlobalUID), entryArray ));
	    	if(err_two == KErrNone)
	    	{
	    		TInt count = entryArray.Count();
	    		buf.Copy(entryArray[0]->UidL());
	    	//	iLog->Log(buf);
	    		if( !( entryArray.Count() == 2 && entryArray[1]->UidL().CompareF(*(arruids[1]->iGlobalUID)) == 0))
	    		{
	    		result = KErrGeneral;
	    		}
	    	}
	    	else
	    		result = err_two;
	    	
	    }
	    
	    if(result == KErrNone)
	    {
	    	TRAPD( err_three, service->GetListL( KTestCal1File, *(arruids[2]->iGlobalUID), entryArray ));
	    	if(err_three == KErrNone)
	    	{
	    		TInt count = entryArray.Count();
	    		buf.Copy(entryArray[0]->UidL());
	    	//	iLog->Log(buf);
	    		if( !( entryArray.Count() == 3 && entryArray[2]->UidL().CompareF(*(arruids[2]->iGlobalUID)) == 0))
	    		{
	    		result = KErrGeneral;
	    		}
	    	}
	    	else
	    		result = err_three;
	    	
	    }
	    
	    if(result == KErrNone)
	    {
	    	TRAPD( err_four, service->GetListL( KTestCal1File, *(arruids[3]->iGlobalUID), entryArray ));
	    	if(err_four == KErrNone)
	    	{
	    		TInt count = entryArray.Count();
	    		buf.Copy(entryArray[0]->UidL());
	    	//	iLog->Log(buf);
	    		if( !( entryArray.Count() == 4 && entryArray[3]->UidL().CompareF(*(arruids[3]->iGlobalUID)) == 0))
	    		{
	    		result = KErrGeneral;
	    		}
	    	}
	    	else
	    		result = err_four;
	    	
	    }
	    
	    if(result == KErrNone)
	    {
	    	TRAPD( err_five, service->GetListL( KTestCal1File, *(arruids[4]->iGlobalUID), entryArray ));
	    	if(err_five == KErrNone)
	    	{
	    		TInt count = entryArray.Count();
	    		buf.Copy(entryArray[0]->UidL());
	    	//	iLog->Log(buf);
	    		if( !( entryArray.Count() == 5 && entryArray[4]->UidL().CompareF(*(arruids[4]->iGlobalUID)) == 0))
	    		{
	    		result = KErrGeneral;
	    		}
	    	}
	    	else
	    		result = err_five;
	    	
	    }
	  //  delete uids;
	//	uids = NULL;
		
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
    
 // -----------------------------------------------------------------------------
// Ctcal_getlist::GetUpdatedEntByGuid
// GetList by Guid for updated calendar entry. 
// (other items were commented in a header).
// -----------------------------------------------------------------------------

//
TInt Ctcal_getlist::GetUpdatedEntByGuid( CStifItemParser& /*aItem*/ )
    { 

TInt result = KErrNone;
__UHEAP_MARK;
	
_LIT(KTestCal1File                ,"C:getlistcal1");
	
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
		
		TCalLocalUid old_luid = arruids[0]->iLocalUID;

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
				utTime.SetTimeUtcL(TTime(TDateTime(2007, EDecember, 18, 9, 0, 0, 0)));
	    //		if( !( rRule.Type() == TCalRRule::EMonthly && rRule.Until().TimeLocalL() == utTime.TimeLocalL() ))
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
	        
	     if(result == KErrNone)
	     {
	     	service->GetListL( KTestCal1File,*(arruids[0]->iGlobalUID),entryArray);
	     	TInt count = entryArray.Count();
	     	if(count != 2 || entryArray[0]->UidL().CompareF(*(arruids[0]->iGlobalUID)) != 0 || entryArray[1]->UidL().CompareF(*(arruids[0]->iGlobalUID)))
	     		result =KErrGeneral;
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
// Ctcal_getlist::GetUpdatedEntByLuid
// GetList by Luid for updated calendar entry. 
// (other items were commented in a header).
// -----------------------------------------------------------------------------

//
TInt Ctcal_getlist::GetUpdatedEntByLuid( CStifItemParser& /*aItem*/ )
    { 

	TInt result = KErrNone;
	__UHEAP_MARK;
	_LIT(KTestCal1File                ,"C:getlistcal1");
	TBuf<40> buf;
	
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
		
		TCalLocalUid old_luid = arruids[0]->iLocalUID; 	
			    		
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
		    		else
		    		{
		    			service->GetListL( KTestCal1File,old_luid,entryArray);
		    			buf.Copy(entryArray[0]->UidL());
	    				//iLog->Log(buf);
	    				buf.Copy(entryArray[1]->UidL());
	    				//iLog->Log(buf);
		    			if(entryArray[0]->LocalUidL() == entryArray[1]->LocalUidL() || entryArray[0]->UidL().CompareF(entryArray[1]->UidL()) != 0)
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


// -----------------------------------------------------------------------------
// Ctcal_getlist::GetCalByLuid
// fetch cal entry by Luid
// (other items were commented in a header).
// -----------------------------------------------------------------------------

//
TInt Ctcal_getlist::GetCalByLuid( CStifItemParser& /*aItem*/ )
    { 

	 TInt result = KErrNone;
	__UHEAP_MARK;

	_LIT(KTestCal1File                ,"C:getlistcal1");
	_LIT( KTestCalFile                ,"C:Calendar");
	_LIT(KTestCal2File                ,"ALH3434MDFLMEF046");

	TBuf<40> buf;
	

	CCalendarService* service = CCalendarService::NewL();
	
	RemoveCalendarFile( service, KTestCal1File );
	AddCalendarFile( service, KTestCal1File );

	RPointerArray<TUIDSet> arruids;
	TUIDSet* uids = NULL;
	

	if(AddRepeatingAppointmentEntryL(service, KTestCal1File, uids) == KErrNone && uids)
		{
			arruids.Append(uids);
			//iLog->Log(*(uids->iGlobalUID)) ;
			buf.Copy(*(uids->iGlobalUID));
	//		iLog->Log(buf);
	//		uids = NULL;
		}


	
	if(AddToDo( service, KTestCal1File, uids ) == KErrNone && uids)
	{
		arruids.Append(uids);
		//iLog->Log(*(uids->iGlobalUID)) ;
		buf.Copy(*(uids->iGlobalUID));
	//	iLog->Log(buf);
	}
	
	if(AddAnny( service, KTestCal1File, uids ) == KErrNone && uids)
	{
		arruids.Append(uids);
	//	iLog->Log(*(uids->iGlobalUID)) ;
		buf.Copy(*(uids->iGlobalUID));
	//	iLog->Log(buf);
	}
	
	if(AddReminder( service, KTestCal1File, uids ) == KErrNone && uids)
	{
		arruids.Append(uids);
	//	iLog->Log(*(uids->iGlobalUID)) ;
		buf.Copy(*(uids->iGlobalUID));
	//	iLog->Log(buf);
	}

	if(AddEvent(service, KTestCal1File, uids) == KErrNone && uids)
		{
		arruids.Append(uids);
		buf.Copy(*(uids->iGlobalUID));
	//	iLog->Log(buf);
	//	uids = NULL;
		}
	
	TInt entry_count = arruids.Count();
		
	if ( arruids.Count() > 0 )
		{
		
	    RPointerArray<CCalEntry> entryArray(1);
	     
	    TRAPD( err_one, service->GetListL( KTestCal1File, arruids[0]->iLocalUID, entryArray ));
	    if ( err_one == KErrNone )
	    	{ 
	    		TInt count = entryArray.Count();
	    	if( !( entryArray.Count() == 1 && entryArray[0]->LocalUidL() == arruids[0]->iLocalUID))
	    		{
	    		result = KErrGeneral;
	    	
	    		}
	    	}
	    else
	    	result = err_one;	
	    
    
	    if(result == KErrNone)
	    {
	    	TRAPD( err_two, service->GetListL( KTestCal1File, arruids[1]->iLocalUID, entryArray ));
	    	if(err_two == KErrNone)
	    	{
	    		TInt count = entryArray.Count();
	    		buf.Copy(entryArray[0]->UidL());
	    	//	iLog->Log(buf);
	    		if( !( entryArray.Count() == 2 && entryArray[1]->LocalUidL() == arruids[1]->iLocalUID))
	    		{
	    		result = KErrGeneral;
	    		}
	    	}
	    	else
	    		result = err_two;
	    	
	    }
	    
	    if(result == KErrNone)
	    {
	    	TRAPD( err_three, service->GetListL( KTestCal1File, arruids[2]->iLocalUID, entryArray ));
	    	if(err_three == KErrNone)
	    	{
	    		TInt count = entryArray.Count();
	    		buf.Copy(entryArray[0]->UidL());
	    	//	iLog->Log(buf);
	    		if( !( entryArray.Count() == 3 && entryArray[2]->LocalUidL() == arruids[2]->iLocalUID))
	    		{
	    		result = KErrGeneral;
	    		}
	    	}
	    	else
	    		result = err_three;
	    	
	    }
	    
	    if(result == KErrNone)
	    {
	    	TRAPD( err_four, service->GetListL( KTestCal1File, arruids[3]->iLocalUID, entryArray ));
	    	if(err_four == KErrNone)
	    	{
	    		TInt count = entryArray.Count();
	    		buf.Copy(entryArray[0]->UidL());
	    	//	iLog->Log(buf);
	    		if( !( entryArray.Count() == 4 && entryArray[3]->LocalUidL() == arruids[3]->iLocalUID))
	    		{
	    		result = KErrGeneral;
	    		}
	    	}
	    	else
	    		result = err_four;
	    	
	    }
	    
	    if(result == KErrNone)
	    {
	    	TRAPD( err_five, service->GetListL( KTestCal1File, arruids[4]->iLocalUID, entryArray ));
	    	if(err_five == KErrNone)
	    	{
	    		TInt count = entryArray.Count();
	    		buf.Copy(entryArray[0]->UidL());
	    	//	iLog->Log(buf);
	    		if( !( entryArray.Count() == 5 && entryArray[4]->LocalUidL() == arruids[4]->iLocalUID))
	    		{
	    		result = KErrGeneral;
	    		}
	    	}
	    	else
	    		result = err_five;
	    	
	    }
	    
	    entryArray.ResetAndDestroy();
	    arruids.ResetAndDestroy();
		}
	else
		result = KErrGeneral;	

	RemoveCalendarFile( service, KTestCal1File );
	
	delete service;
	uids = NULL;
	__UHEAP_MARKEND;
	return result;
    }

// -----------------------------------------------------------------------------
// Ctcal_getlist::GetCalEntBySearchFilter
// GetList by text filter on summary field. 
// (other items were commented in a header).
// -----------------------------------------------------------------------------

//
TInt Ctcal_getlist::GetCalEntBySearchFilter( CStifItemParser& /*aItem*/ )
    { 

	TInt result = KErrNone;
	
	TInt count;
	TInt val;
	TBuf<40> buf;
	
	_LIT(KTestCal1File                ,"C:getlistcal1");
	_LIT(KSearchTexttest                 ,"HAPPENs from 9 TO");
	_LIT(KLongTexttest                 ,"dsfnsdflksdn 9234i2- as;mmsal; sdklasdasjdhaskl sadasldjasldjasd lasdklasjdlkasjdklsjad  kasjdkasjdlkasjdlkdjakl -3232m asdjasl;dkas;ldka;slkd;askd ;lsakd hawdhwqduahsizudh");
	_LIT(KCalTexttest                 ,"C:xyndsks:dkl");
	_LIT(KNewTexttest                 ,"SUMMARY");
	_LIT(KRepeatingEnttexttest                 ,"REPEATING");
	 RPointerArray<CCalInstance> instanceArray;
	
	CCalendarService* service = CCalendarService::NewL();
	
	RemoveCalendarFile( service, KTestCal1File );
	AddCalendarFile( service, KTestCal1File );


	CEntryAttributes* entryObj = CEntryAttributes::NewL(KEntryAppt);
	
	entryObj->SetDescriptionL(_L("SAPI weekly meeting"));
	entryObj->SetLocationL(_L("Hara"));
	entryObj->SetEntryStatusL(KStatusConfirmed);
	entryObj->SetMethodL(KMethodNone);
	entryObj->SetPriority(5);
    entryObj->SetSummaryL(_L("Meeting happens from 9 to 9:30"));
    
    TCalTime stTime;
	stTime.SetTimeUtcL(TTime(TDateTime(2007, EAugust, 8, 9, 0, 0, 0)));
	entryObj->SetStartTimeL(TTime(TDateTime(2007, EAugust, 8, 9, 0, 0, 0)));
	
	TCalTime endTime;
	endTime.SetTimeUtcL(TTime(TDateTime(2007, EAugust, 8, 9, 30, 0, 0)));
	entryObj->SetEndTimeL(TTime(TDateTime(2007, EAugust, 8, 9, 30, 0, 0)));
	
	TUIDSet* uids = NULL;
	service->AddL(KTestCal1File,entryObj,uids);
	
	
	RPointerArray<TUIDSet> arruids(5);

	
	arruids.Append(uids);
	TCalLocalUid luid = arruids[0]->iLocalUID;
	buf.Copy(*(arruids[0]->iGlobalUID));
	//iLog->Log(buf);
	
	TCalLocalUid luid_entry;
	
	
	uids = NULL;
	
	
	if(AddAppointmentWithAttendees(service, KTestCal1File, uids) == KErrNone && uids)
		{
			arruids.Append(uids);
		}
		
		buf.Copy(*(arruids[1]->iGlobalUID));
	    //iLog->Log(buf);
	    TCalLocalUid new_luid = uids->iLocalUID;
	    
	    

	if ( arruids.Count() > 0 )
		{
	   

		CCalendarFilter *filter = CCalendarFilter::NewL();
		
		filter->SetFilterTextL( KSearchTexttest );
	     
	    TRAPD( err, service->GetListL( KTestCal1File, filter, instanceArray ));

	    if ( err == KErrNone )
	    	{ 
	    		count = instanceArray.Count() ;
	    	if( !( instanceArray.Count() == 2 && instanceArray[0]->Entry().UidL().CompareF(*(arruids[1]->iGlobalUID)) == 0 && instanceArray[1]->Entry().UidL().CompareF(*(arruids[0]->iGlobalUID)) == 0))
	    		{
	    		result = KErrGeneral;
	    		}
	    		if(count > 0)
	    		{
	    			for(TInt index=0;index<count;index++)
	    			{
	    				luid_entry = instanceArray[index]->Entry().LocalUidL();
	    				buf.Copy(instanceArray[index]->Entry().UidL());
	    				//iLog->Log(buf);
	    			
	    				buf.Copy(instanceArray[index]->Entry().SummaryL());
	    				//iLog->Log(buf);
	    			
	    			}
	    			
	    			count = 0;
	    			instanceArray.ResetAndDestroy();
	    		}
	    		
	    	}
	    else
	    	result = err;
	    
	    
	    if(AddRepeatingAppointmentEntryL(service, KTestCal1File, uids) == KErrNone && uids)
		{
			arruids.Append(uids);
			buf.Copy(*(uids->iGlobalUID));
	   		 //iLog->Log(buf);
	   		 new_luid = uids->iLocalUID;
		
		}
		
				
		
		filter->SetFilterTextL( KRepeatingEnttexttest );
	    TRAPD( err_one, service->GetListL( KTestCal1File, filter, instanceArray ));
	    if(err_one == KErrNone)
	    {
	    	count = instanceArray.Count() ;
	    	if(count > 0)
	    	{
	    		for(TInt index=0;index<count;index++)
	    		{
	    			luid_entry = instanceArray[index]->Entry().LocalUidL();
	    			buf.Copy(instanceArray[index]->Entry().UidL());
	    			//iLog->Log(buf);
	    			
	    			buf.Copy(instanceArray[index]->Entry().SummaryL());
	    			//iLog->Log(buf);
	    			
	    			TTime stTime = instanceArray[index]->Entry().StartTimeL().TimeLocalL();
	    			TTime endTime = instanceArray[index]->Entry().EndTimeL().TimeLocalL();
	    			
    			
	    		}
	    		count = 0;
	    	}
	    }
	    else if(result == KErrNone)
	    	result = err_one;
	    
	    	    
	    filter->SetFilterTextL( KLongTexttest );
	    TRAPD( err_two, service->GetListL( KTestCal1File, filter, instanceArray ));
	    if(err_two != KErrArgument)
	       	result = KErrGeneral;
	    
	    
	    
	    
	    filter->SetFilterTextL( KCalTexttest );
	    TRAPD( err_three, service->GetListL( KTestCal1File, filter, instanceArray ));
	    if(err_three == KErrNone)
	    {
	    	count = instanceArray.Count() ;
	    	if(count > 0)
	    	{
	    		val = instanceArray[0]->Entry().UidL().CompareF(*(arruids[0]->iGlobalUID));
	    		count = 0;
	    		instanceArray.ResetAndDestroy();
	    	}
	    }
	    else if(result == KErrNone)
	    	result = err_three;
	    
	    
	    CEntryAttributes* new_entryObj = CEntryAttributes::NewL();
	    new_entryObj->SetSummaryL(_L("New summary text"));
	    new_entryObj->SetLocalUid( luid );
	    TRAPD(err_add,service->AddL(KTestCal1File,new_entryObj,uids));
	    delete new_entryObj;
	    arruids.Append(uids);
	    
	    filter->SetFilterTextL( KNewTexttest );
	    TRAPD( err_four, service->GetListL( KTestCal1File, filter, instanceArray ));
	    if(err_four == KErrNone)
	    {
	    	count = instanceArray.Count() ;
	    	if( !( instanceArray.Count() == 1 && instanceArray[0]->Entry().UidL().CompareF(*(arruids[3]->iGlobalUID)) == 0 ))
	    	{
	    		result = KErrGeneral;
	    	}
	    	count = 0;
	    }
	    else if(result == KErrNone)
	    	result = err_four;
	    
	       
	    
	    
	    delete filter;
	    instanceArray.ResetAndDestroy();
	    arruids.ResetAndDestroy();
		}
	else
		result = KErrGeneral;	
	
	
	RemoveCalendarFile( service, KTestCal1File );

	delete service;
	delete entryObj;

	
	return result;
    }


// -----------------------------------------------------------------------------
// Ctcal_getlist::GetCalEntByTimeFilter
// GetList by time range 
// (other items were commented in a header).
// -----------------------------------------------------------------------------

//
TInt Ctcal_getlist::GetCalEntByTimeFilter( CStifItemParser& /*aItem*/ )
    { 

	TInt result = KErrNone;
	TInt count;
	_LIT(KTestCal1File                ,"C:getlistcal1");
	_LIT(KInvalidCalFile                ,"C:xynsdsdk");
	__UHEAP_MARK;
	
	
	TBuf<40> buf;

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
	stTime.SetTimeUtcL(TTime(TDateTime(2007, EAugust, 8, 9, 0, 0, 0)));
	entryObj->SetStartTimeL(TTime(TDateTime(2007, EAugust, 8, 9, 0, 0, 0)));
	
	TCalTime endTime;
	endTime.SetTimeUtcL(TTime(TDateTime(2007, EAugust, 8, 9, 30, 0, 0)));
	entryObj->SetEndTimeL(TTime(TDateTime(2007, EAugust, 8, 9, 30, 0, 0)));
	
    CRepeatInfo* rrule = CRepeatInfo::NewL(TCalRRule::EWeekly);
	rrule->SetStartTimeL(TTime(TDateTime(2007, EAugust, 8, 9, 0, 0, 0)));
    
    RArray<TDay> dayArray;
    dayArray.Append( stTime.TimeUtcL().DayNoInWeek() );
    rrule->SetDaysInWeek( dayArray );
    rrule->SetCount( 1 );

    entryObj->SetRepeatRule( rrule );
    dayArray.Reset();
    delete rrule;
	
	TUIDSet* uids = NULL;
	service->AddL(KTestCal1File,entryObj,uids);
	buf.Copy(*(uids->iGlobalUID));
	//iLog->Log(buf);

	RPointerArray<TUIDSet> arruids(5);
	CCalendarFilter *filter = CCalendarFilter::NewL();
	RPointerArray<CCalInstance> instanceArray;
	RPointerArray<CCalEntry> entryArray(1);
	
	arruids.Append(uids);
	
	if(AddRepeatingAptEntryL(service, KTestCal1File, uids) == KErrNone && uids)
		{
			arruids.Append(uids);
			buf.Copy(*(uids->iGlobalUID));
	   		 //iLog->Log(buf);
	   			
		} 
		
	

	if ( arruids.Count() > 0 )
		{
	    

		
		
	    filter->SetStartTimeL(TTime(TDateTime(2007, EAugust, 8, 9, 0, 0, 0)));
		filter->SetEndTimeL(TTime(TDateTime(2008, EAugust, 8, 9, 0, 0, 0)));
	     
	    TRAPD( err, service->GetListL( KTestCal1File, filter, instanceArray ));

	    if ( err == KErrNone )
	    	{ 
	    		count = instanceArray.Count();
	    		for(TInt i=0;i<count;i++)
	    		{
	    			buf.Copy(instanceArray[i]->Entry().UidL());
	    			//iLog->Log(_L("Global Uid of Instance"));
	   			 	//iLog->Log(buf);
	   			 
	   			 	buf.Copy(instanceArray[i]->Entry().DescriptionL());
	   			 	//iLog->Log(_L("Summary of the instance"));
	   			 	//iLog->Log(buf); 
	   			 	
	   			 	TInt day_no = instanceArray[i]->Time().TimeLocalL().DateTime().Day();
	   			 				 	
	    		}
	   		
	    	if( !( instanceArray.Count() == 16 && instanceArray[0]->Entry().UidL().CompareF(*(arruids[0]->iGlobalUID)) == 0 && instanceArray[1]->Entry().UidL().CompareF(*(arruids[1]->iGlobalUID)) == 0))
	    		{
	    		result = KErrGeneral;
	    		}
	    		
	    	}
	    else
	    	result = err;	
	    
	    instanceArray.ResetAndDestroy();
	    count = 0;
	    
	   // delete uids;
	    //uids = NULL;
	    
	    
	    filter->SetStartTimeL(TTime(TDateTime(2008, EAugust, 8, 9, 0, 0, 0)));
		filter->SetEndTimeL(TTime(TDateTime(2009, EAugust, 8, 9, 0, 0, 0)));
	    
	    TRAPD( err_one, service->GetListL( KTestCal1File, filter, instanceArray ));

	    if ( err_one == KErrNone )
	    	{ 
	    		count = instanceArray.Count();
	    		if(count != 0)
	    			result = KErrGeneral;
	    	}
	    	
	    else if (result == KErrNone)
	    	result = err_one;
	    
	    
	    instanceArray.ResetAndDestroy();
	    count = 0;
	    
	    //same day    
	    filter->SetStartTimeL(TTime(TDateTime(2007, EAugust, 8, 9, 0, 0, 0)));
		filter->SetEndTimeL(TTime(TDateTime(2007, EAugust, 8, 10, 0, 0, 0)));
	    
	    TRAPD( err_two, service->GetListL( KTestCal1File, filter, instanceArray ));

	    if ( err_two == KErrNone )
	    	{ 
	    		count = instanceArray.Count();
	    		if(count != 1)
	    			result = KErrGeneral;
	    	}
	    	
	    else if (result == KErrNone)
	    	result = err_two;
	    
	    
	    instanceArray.ResetAndDestroy();
	    count = 0;
	    
	    	    
	    filter->SetStartTimeL(TTime(TDateTime(2007, ESeptember, 14, 9, 0, 0, 0)));
		filter->SetEndTimeL(TTime(TDateTime(2007, ESeptember, 29, 8, 0, 0, 0)));
	    
	    TRAPD( err_three, service->GetListL( KTestCal1File, filter, instanceArray ));

	    if ( err_three == KErrNone )
	    	{ 
	    		count = instanceArray.Count();
	    		if(count != 13)
	    			result = KErrGeneral;
	    	}
	    	
	    else if (result == KErrNone)
	    	result = err_three;
	    
	    instanceArray.ResetAndDestroy();
	    count = 0;
	    
	    
	    // pass null object as filter
	   	    
	    TRAPD( err_four, service->GetListL( KTestCal1File, NULL, instanceArray ));

	    if ( err_four == KErrNone && result == KErrNone)
	    	{ 
	    		result = KErrGeneral;
	    	}
	    	
	        
	    
	    
		
		//invalid calendar file
		
		TRAPD( err_five, service->GetListL( KInvalidCalFile, filter, instanceArray ));

	    if ( err_five == KErrNone && result == KErrNone)
	    	{ 
	    		result = KErrGeneral;
	    	}
	    
	   	    
	    }
		else
			result = KErrGeneral; 
	
	delete filter;
	instanceArray.ResetAndDestroy();
	arruids.ResetAndDestroy();
	    

	RemoveCalendarFile( service, KTestCal1File );
	delete entryObj;
	delete service;
	__UHEAP_MARKEND;
	return result;
    }
    
    
    // -----------------------------------------------------------------------------
// Ctcal_getlist::GetCalEntByTypeFilter
// GetList by type of entry 
// (other items were commented in a header).
// -----------------------------------------------------------------------------

//
TInt Ctcal_getlist::GetCalEntByTypeFilter( CStifItemParser& /*aItem*/ )
    { 

	TInt result = KErrNone;
	__UHEAP_MARK;
	
	_LIT(KTestCal1File                ,"C:getlistcal1");
	_LIT(KInvalidCalFile                ,"C:xynsdsdk");
	_LIT(KInvalidText, 			"Invalid");
	
	TInt count;
	TBuf<40> buf;
	
	
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
	
	if(AddRepeatingAptEntryL(service, KTestCal1File, uids) == KErrNone && uids)
		{
		arruids.Append(uids);
		uids = NULL;
		}
		
//	delete uids;
//	uids = NULL;		
	

	if ( arruids.Count() > 0 )
		{
	    RPointerArray<CCalInstance> instanceArray;

		CCalendarFilter *filter = CCalendarFilter::NewL();
		
		filter->SetFilterTypeL( KEntryAppt );
		
	     
	    TRAPD( err, service->GetListL( KTestCal1File, filter, instanceArray ));

	    if ( err == KErrNone )
	    	{ 
	    		count = instanceArray.Count();
	    		
	    	if( instanceArray.Count() > 0 && count == 16 )
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
	    
	    TRAPD(err_setfilter,filter->SetFilterTypeL(KInvalidText));
	    
	   if ( err_setfilter == KErrNone && result == KErrNone )
	    	  	result = KErrGeneral; 
	    
	    
	    count =0;
	    instanceArray.ResetAndDestroy();
	    
	    filter->SetFilterTypeL( KEntryReminder );
	    
	    TRAPD( err_two, service->GetListL( KTestCal1File, filter, instanceArray ));

	    if ( err_two == KErrNone )
	    	{ 
	    		count = instanceArray.Count();
	    		if(count != 0)
	    			result = KErrGeneral;
	    		
	       	}
	    else if(result == KErrNone)
	    	result = err_two;
	    
	    
	    if(AddEvent(service, KTestCal1File, uids) == KErrNone && uids)
		{
		arruids.Append(uids);
		uids = NULL;
		}
		
		
	    filter->SetFilterTypeL(KIncludeAll);
	    
	    TRAPD( err_three, service->GetListL( KTestCal1File, filter, instanceArray ));

	    if ( err_three == KErrNone )
	    	{ 
	    		count = instanceArray.Count();
	    		if(count != 17)
	    			result = KErrGeneral;
	    		
	       	}
	    else if(result == KErrNone)
	    	result = err_three;
	    
	    
	    	    
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

TInt Ctcal_getlist::GetListTimeRangeFilterAsync(CStifItemParser& /*aItem*/ )
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

TInt Ctcal_getlist::GetListGuidFilterAsync(CStifItemParser& /*aItem*/ )
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
TInt Ctcal_getlist::GetListLuidFilterAsync(CStifItemParser& /*aItem*/ )
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
TInt Ctcal_getlist::GetListTextFilterAsync(CStifItemParser& /*aItem*/ )
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
TInt Ctcal_getlist::GetListTypeFilterAsync(CStifItemParser& /*aItem*/ )
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
TInt Ctcal_getlist::GetListInvalidGuidFilterAsync(CStifItemParser& /*aItem*/ )
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
TInt Ctcal_getlist::GetListInvalidLuidFilterAsync(CStifItemParser& /*aItem*/ )
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
   
// Helper function

TInt AddRepeatingAptEntryL(CCalendarService* aService, const TDesC& name, TUIDSet*& uids)
	{
	
	CEntryAttributes* entryObj = CEntryAttributes::NewL( KEntryAppt );
	
    entryObj->SetDescriptionL(_L("SAPI weekly meeting"));
	entryObj->SetLocationL(_L("Hara"));
	entryObj->SetEntryStatusL(KStatusConfirmed);
	
	entryObj->SetMethodL(KMethodNone);
	CAttendeeInfo* organizer = CAttendeeInfo::NewL(_L("mcrasta@gmail.com"));
	organizer->SetCommonNameL(_L("SAPI"));
	entryObj->SetOrganizerDataL(organizer);
	delete organizer;
	
	entryObj->SetPhoneOwnerDataL(_L("h2s@gmail.com"));
	
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
	
    CAttendeeInfo* attendee = CAttendeeInfo::NewL(_L("h2s@gmail.com"));
	attendee->SetRoleL(KAttRoleReqParticipant);
	attendee->SetStatusL(KAttStatusTentative);
    attendee->SetRsvp(EFalse);
    entryObj->AddAttendeeL(attendee);
    delete attendee;
	
	attendee = CAttendeeInfo::NewL(_L("mdcosta@gmail.com"));
	attendee->SetCommonNameL(_L("SAPI"));
	attendee->SetRoleL(KAttRoleReqParticipant);
	attendee->SetStatusL(KAttStatusTentative);
    attendee->SetRsvp(EFalse);
    entryObj->AddAttendeeL(attendee);
    delete attendee;
    
    CRepeatInfo* rrule = CRepeatInfo::NewL(TCalRRule::EDaily);
	//TCalRRule rrule(TCalRRule::EDaily);
	TCalTime startTime;
	startTime.SetTimeUtcL(stTime);
	rrule->SetStartTimeL(stTime);
	TCalTime uTime;
	uTime.SetTimeUtcL(TTime(TDateTime(2007, ESeptember, 29, 0, 0, 0, 0)));
	rrule->SetUntilTimeL(TTime(TDateTime(2007, ESeptember, 29, 9, 0, 0, 0)));
	rrule->SetWeekStart(EWednesday);
	entryObj->SetRepeatRule(rrule);	
	delete rrule;
	
	TTime exDate(TDateTime(2007, ESeptember, 20, 0, 0, 0, 0)); 
    TCalTime exTime;
    exTime.SetTimeUtcL(exDate);
    entryObj->AddExceptionDateL(exDate);
        
    TTime rDate(TDateTime(2007, EOctober, 0, 9, 0, 0, 0)); 
    TCalTime rTime;
    rTime.SetTimeUtcL(rDate);
    entryObj->AddRepeatDateL(rDate);
        
	TRAPD( errno, aService->AddL(name,entryObj,uids) );
	delete entryObj;
	return errno;

    }		    
    
    
// -----------------------------------------------------------------------------
// Ctcal_getlist::?member_function
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
/*
TInt Ctcal_getlist::?member_function(
   CItemParser& aItem )
   {

   ?code

   }
*/

// ========================== OTHER EXPORTED FUNCTIONS =========================
// None

//  End of File
