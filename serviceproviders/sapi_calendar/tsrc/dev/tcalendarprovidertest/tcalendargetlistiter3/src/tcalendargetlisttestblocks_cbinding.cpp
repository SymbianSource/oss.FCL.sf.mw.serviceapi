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
//#include <SAPI_TEST\testprg.h>
#include <Stiftestinterface.h>

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include <BADESCA.H>

#include "cliwbinding.h"

#include "tcalendargetlisttest.h"

#include "teststartconsoleAlarmServer3.h"

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
        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

	
	
_LIT(KSearchTexttest                 ,"Meeting");

_LIT(KDefaultCalendar                ,"C:Calendar");

static const char *service_name  = "Service.Calendar";
static const char *interface_name = "IDataSource";
static const wchar_t *KTestCal1File = L"C:getlistcal1";
static const wchar_t *KTestCal2File = L"C:getlistcal2";


//	
//Whats done here? 
//	Get all the Calendars in the system using GetList of CCalendarService and output that to GetListallCalendars.txt
//
TInt CTCalendarGetListTest::GetListCalendar(CStifItemParser& /*aItem*/ )
	{
	gchar key[32];
	GValue outparam;
	int num = 0;
	
	void *interface_pointer = NULL;	

	TInt error = KErrNone;

	cbindingattach();
	
	num = User::CountAllocCells();
	
	TRAP( error, interface_pointer = loadservice( service_name, interface_name, G_TYPE_INVALID ) );
	
	if ( error == KErrNone && interface_pointer )
		{
		error = AddCalendarFile( interface_pointer, KTestCal1File);
		
		if ( error == KErrNone || error == KErrAlreadyExists )
			{
			error = AddCalendarFile( interface_pointer, KTestCal2File);
			if ( error == KErrNone || error == KErrAlreadyExists )
				{
			    TRAP( error, requestservice( interface_pointer, "GetList" , 
				                             G_BINDING_DERIVED_TYPE_UNICODE, "Type" , L"Calendar",
				                             G_TYPE_INVALID ,
				                             &outparam, NULL ,0 , &error));
				if ( error == KErrNone )
					{
					TInt rescnt = getoutputcount(outparam);
					if(rescnt)
						{
						GValue calList;
						GValue value;
						int count = 0;
						int err = 0;
						GType type = getoutputatindex(outparam, &calList, 0);
						err = iterator_next(calList, &value);
						while ( err == KErrNone )
							{
							wchar_t  desc[30];
							getresult(value, G_BINDING_DERIVED_TYPE_UNICODE, desc);
							count++;
							err = iterator_next(calList, &value);
							}
							
						if(count < 2)
							error = KErrGeneral;
						}
					}
				resetoutput(outparam);	
				}
			
			}
		}
		
	RemoveCalendarFile( interface_pointer, KTestCal1File);
	RemoveCalendarFile( interface_pointer, KTestCal2File);

	closeinterface( interface_pointer );
	
    unloadservice( service_name , interface_name );
    
	num = User::CountAllocCells();

    cbindingdetach();
    
    return error;

    }

TInt CTCalendarGetListTest::GetDefaultCalendar(CStifItemParser& /*aItem*/ )
	{
	gchar key[32];
	GValue outparam;
	int num = 0;
	
	void *interface_pointer = NULL;	

	TInt error = KErrNone;

	cbindingattach();
	
	num = User::CountAllocCells();
	
	TRAP( error, interface_pointer = loadservice( service_name, interface_name, G_TYPE_INVALID ) );
	
	if ( error == KErrNone && interface_pointer )
		{
		error = AddCalendarFile( interface_pointer, KTestCal1File);
		
		if ( error == KErrNone || error == KErrAlreadyExists )
			{
			error = AddCalendarFile( interface_pointer, KTestCal2File);
			if ( error == KErrNone || error == KErrAlreadyExists )
				{
				GValue map;
			    map_construct( &map , G_TYPE_BOOLEAN, "DefaultCalendar" , 1, 
			                              G_TYPE_INVALID );
			    TRAP( error, requestservice( interface_pointer, "GetList" , 
				                             G_BINDING_DERIVED_TYPE_UNICODE, "Type" , L"Calendar",
	                             			 G_BINDING_DERIVED_TYPE_MAP    , "Filter"      , map, 
				                             G_TYPE_INVALID ,
				                             &outparam, NULL ,0 , &error));
				
				map_delete(map);
				
				if ( error == KErrNone )
					{
					TInt rescnt = getoutputcount(outparam);
					if(rescnt)
						{
						GValue calList;
						GValue value;
						int count = 0;
						int err = 0;
						GType type = getoutputatindex(outparam, &calList, 0);
						err = iterator_next(calList, &value);
						while ( err == KErrNone )
							{
							wchar_t  desc[30];
							getresult(value, G_BINDING_DERIVED_TYPE_UNICODE, desc);
							count++;
							err = iterator_next(calList, &value);
							}
							
						if(count < 1)
							error = KErrGeneral;
						}
					}
				resetoutput(outparam);	
				}
			
			}
		}
		
	RemoveCalendarFile( interface_pointer, KTestCal1File);
	RemoveCalendarFile( interface_pointer, KTestCal2File);

	closeinterface( interface_pointer );
	
    unloadservice( service_name , interface_name );
    
	num = User::CountAllocCells();

    cbindingdetach();
    
    return error;
    }
 
 
TInt CTCalendarGetListTest::GetListGUidFilter(CStifItemParser& /*aItem*/ )
	{
	TInt result = KErrNone;
	
	gchar key[32];
	GValue outparam;
	int num = 0;
	
	void *interface_pointer = NULL;	

	TInt error = KErrNone;

	cbindingattach();
	
	num = User::CountAllocCells();
	
	TRAP( error, interface_pointer = loadservice( service_name, interface_name, G_TYPE_INVALID ) );
	
	if ( error == KErrNone && interface_pointer )
		{
		RemoveCalendarFile( interface_pointer, KTestCal1File);

		error = AddCalendarFile( interface_pointer, KTestCal1File);
		
		if ( error == KErrNone || error == KErrAlreadyExists )
			{
			RPointerArray<TUIDSet> arruids(5);
			
			TUIDSet* uids = NULL;
			
			if(AddAppointmentWithoutRepeat(interface_pointer, KTestCal1File, uids) == KErrNone && uids)
				{
				arruids.Append(uids);
				uids = NULL;
				}

			if(AddEvent(interface_pointer, KTestCal1File, uids) == KErrNone && uids)
				{
				arruids.Append(uids);
				uids = NULL;
				}

			if ( arruids.Count() > 0 )
				{
			    GValue getlistparam;
			    
			    char* guidFlter = (char*)(arruids[0]->iGlobalUID->Des().PtrZ());
			     
		        map_construct( &getlistparam, G_BINDING_DERIVED_TYPE_UNICODE , "CalendarName", KTestCal1File, 
                              G_TYPE_STRING, "GlobalUid" , guidFlter,
                              G_TYPE_INVALID );
		
			    TRAPD( err , requestservice( interface_pointer, "GetList" , 
				                             G_BINDING_DERIVED_TYPE_UNICODE, "Type" , L"CalendarEntry",
				                             G_BINDING_DERIVED_TYPE_MAP    , "Filter"      , getlistparam, 
				                             G_TYPE_INVALID ,
				                             &outparam, NULL ,0 , &error));
				map_delete( getlistparam );

				if ( error == KErrNone )
					{
					TInt rescnt = getoutputcount(outparam);
					if(rescnt)
						{
						GValue calList;
						GValue entrymap;
						GValue value;
						const char* key1 = "LocalUid";
						const char* key2 = "GlobalUid";
						int count = 0;
						int err = 0;
						GType type = getoutputatindex(outparam, &calList, 0);
						err = iterator_next(calList, &entrymap);
						while ( err == KErrNone )
							{
							error = map_findvaluewithkey (entrymap,key2,&value);
							if(error == KErrNone)
								{
								char resultguid[60];
								getresult(value, G_TYPE_STRING, resultguid);
								}
								
							error = map_findvaluewithkey (entrymap,key1,&value);
							if(error == KErrNone)
								{
								unsigned int  resultluid;
								getresult(value, G_TYPE_UINT, &resultluid);
								}
							//Sunil Compare the Guid here
							
							
							count++;
							err = iterator_next(calList, &entrymap);
							}
							
						if(count != 1)
							error = KErrGeneral;
						}
			    	}
			    else
			    	error = err;	
			    
			    resetoutput(outparam);
			    arruids.ResetAndDestroy();
				}
			else
				error = KErrGeneral;	
			
			}
		}
		
	RemoveCalendarFile( interface_pointer, KTestCal1File);

	closeinterface( interface_pointer );
	
    unloadservice( service_name , interface_name );
    
    cbindingdetach();
    
    return error;
    }
 

TInt CTCalendarGetListTest::GetListLocalUidFilter(CStifItemParser& /*aItem*/ )
	{
	TInt result = KErrNone;
	
	gchar key[32];
	GValue outparam;
	int num = 0;
	
	void *interface_pointer = NULL;	

	TInt error = KErrNone;

	cbindingattach();
	
	num = User::CountAllocCells();
	
	TRAP( error, interface_pointer = loadservice( service_name, interface_name, G_TYPE_INVALID ) );
	
	if ( error == KErrNone && interface_pointer )
		{
		RemoveCalendarFile( interface_pointer, KTestCal1File);

		error = AddCalendarFile( interface_pointer, KTestCal1File);
		
		if ( error == KErrNone || error == KErrAlreadyExists )
			{
			RPointerArray<TUIDSet> arruids(5);
			
			TUIDSet* uids = NULL;
			
			if(AddAppointmentWithoutRepeat(interface_pointer, KTestCal1File, uids) == KErrNone && uids)
				{
				arruids.Append(uids);
				uids = NULL;
				}

			if(AddEvent(interface_pointer, KTestCal1File, uids) == KErrNone && uids)
				{
				arruids.Append(uids);
				uids = NULL;
				}

			if ( arruids.Count() > 0 )
				{
			    GValue getlistparam;
			    
			    unsigned int luidFlter = arruids[0]->iLocalUID;
			     
		        map_construct( &getlistparam, G_BINDING_DERIVED_TYPE_UNICODE , "CalendarName", KTestCal1File, 
                              G_TYPE_UINT, "LocalUid" , luidFlter,
                              G_TYPE_INVALID );
		
			    TRAPD( err , requestservice( interface_pointer, "GetList" , 
				                             G_BINDING_DERIVED_TYPE_UNICODE, "Type" , L"CalendarEntry",
				                             G_BINDING_DERIVED_TYPE_MAP    , "Filter"      , getlistparam, 
				                             G_TYPE_INVALID ,
				                             &outparam, NULL ,0 , &error));
				map_delete( getlistparam );

				if ( error == KErrNone )
					{
					TInt rescnt = getoutputcount(outparam);
					if(rescnt)
						{
						GValue calList;
						GValue entrymap;
						GValue value;
						const char* key1 = "LocalUid";
						const char* key2 = "GlobalUid";
						int count = 0;
						int err = 0;
						GType type = getoutputatindex(outparam, &calList, 0);
						err = iterator_next(calList, &entrymap);
						while ( err == KErrNone )
							{
							error = map_findvaluewithkey (entrymap,key2,&value);
							if(error == KErrNone)
								{
								char resultguid[60];
								getresult(value, G_TYPE_STRING, resultguid);
								}
								
							error = map_findvaluewithkey (entrymap,key1,&value);
							if(error == KErrNone)
								{
								unsigned int  resultluid;
								getresult(value, G_TYPE_UINT, &resultluid);
								}
							//Sunil Compare the Luid here
							
							
							count++;
							err = iterator_next(calList, &entrymap);
							}
							
						if(count != 1)
							error = KErrGeneral;
						}
			    	}
			    else
			    	error = err;	
			    
			    resetoutput(outparam);
			    arruids.ResetAndDestroy();
				}
			else
				error = KErrGeneral;	
			
			}
		}
		
	RemoveCalendarFile( interface_pointer, KTestCal1File);

	closeinterface( interface_pointer );
	
    unloadservice( service_name , interface_name );
    
    cbindingdetach();
    
    return error;
	
    }
    
TInt AddAppointmentLocal(void* aInterfaceptr, const wchar_t* aCalname, TUIDSet*& uids)
	{
	
	GValue outparam, inparam, repeatMap, result, res, value, getlistparam;
	
	GType type;	
		
	TInt error = KErrNone;

	int seqnum,rtype, rescnt;
		
	int cerr = 0;
	
	gint mCount = 0;
	gchar key[32];
	wchar_t  desc[20];
	wchar_t  desc1[20] = L"Meeting";
	
    TInt num = User::CountAllocCells();
    seqnum = 1;
    rtype = 1;//daily
    int ret;
    map_construct( &repeatMap , G_TYPE_INT, "Type" , rtype , 
                              G_BINDING_DERIVED_TYPE_DATE , "StartDate" , L"20070903:093000" ,
                              G_BINDING_DERIVED_TYPE_DATE , "UntilDate" , L"20070907:103000" ,
                              G_TYPE_INVALID );
    
    map_construct( &inparam , G_BINDING_DERIVED_TYPE_UNICODE , "CalendarName", aCalname , 
                              G_BINDING_DERIVED_TYPE_UNICODE , "Type", L"Meeting" ,
                              G_TYPE_INT, "SeqNum" , seqnum,
                              G_BINDING_DERIVED_TYPE_DATE , "StartTime" , L"20070903:093000" ,
                              G_BINDING_DERIVED_TYPE_DATE , "EndTime" , L"20070903:103000" ,
                              G_BINDING_DERIVED_TYPE_UNICODE , "Replication", L"Open" ,
                              G_BINDING_DERIVED_TYPE_UNICODE , "Description", L"Meeting" ,
                              G_BINDING_DERIVED_TYPE_UNICODE , "Summary", L"Meeting happen at 9.30" ,
                              G_BINDING_DERIVED_TYPE_UNICODE , "Location", L"Hara" ,
                              G_BINDING_DERIVED_TYPE_UNICODE , "Status", L"Confirmed" ,
                              G_BINDING_DERIVED_TYPE_UNICODE , "Method", L"None" ,
                              G_BINDING_DERIVED_TYPE_MAP, "RepeatRule" , repeatMap ,
                              G_TYPE_INVALID );
		                      
         
    TRAPD( err , requestservice( aInterfaceptr, "Add" , 
	                             G_BINDING_DERIVED_TYPE_UNICODE, "Type" , L"CalendarEntry",
	                             G_BINDING_DERIVED_TYPE_MAP    , "Item"      , inparam , 
	                             G_TYPE_INVALID ,
	                             &outparam     , NULL ,0 , &error));

	if ( err == KErrNone )
		{
		TInt x = 0;
		unsigned int luid;
		char guid[100]; 
		TInt rescnt = getoutputcount(outparam);
		const char * localuid = "LocalUid";
		const char * globaluid = "GlobalUid";
		
		GType type = getoutputatindex(outparam, &result, 0);
		
	    map_findvaluewithkey(result, localuid, &value );
        getresult(value,G_TYPE_UINT,&luid);

	    map_findvaluewithkey(result, globaluid, &value );
        getresult(value,G_TYPE_STRING,&guid);
        
        TPtrC8 temp((const unsigned char *)guid);
        uids = new TUIDSet;
        uids->iLocalUID = luid;
        uids->iGlobalUID = temp.AllocL();
		}
			 
	map_delete(repeatMap);
	
	map_delete(inparam);
	
	resetoutput(outparam);
	
	return err;	
    }

    

//	
//Whats done here? 
//	Get the default system Calendar using GetList of CCalendarService and output that to GetListdefaultCalendar.txt
//    
TInt CTCalendarGetListTest::GetListTimeRangeFilter(CStifItemParser& /*aItem*/ )
	{
	gchar key[32];
	GValue outparam;
	int num = 0;
	
	void *interface_pointer = NULL;	

	TInt error = KErrNone;

	cbindingattach();
	
	num = User::CountAllocCells();
	
	TRAP( error, interface_pointer = loadservice( service_name, interface_name, G_TYPE_INVALID ) );
	
	if ( error == KErrNone && interface_pointer )
		{
		RemoveCalendarFile( interface_pointer, KTestCal1File);

		error = AddCalendarFile( interface_pointer, KTestCal1File);
		
		if ( error == KErrNone || error == KErrAlreadyExists )
			{
			RPointerArray<TUIDSet> arruids(5);
			
			TUIDSet* uids = NULL;
			
			if(AddAppointmentLocal(interface_pointer, KTestCal1File, uids) == KErrNone && uids)
				{
				arruids.Append(uids);
				uids = NULL;
				}

			if ( arruids.Count() > 0 )
				{
			    GValue getlistparam;
			    
			    const wchar_t* text = L"Meeting";
			     
		        map_construct( &getlistparam, G_BINDING_DERIVED_TYPE_UNICODE , "CalendarName", KTestCal1File, 
                              G_BINDING_DERIVED_TYPE_DATE , "StartRange" , L"20070903:093000" ,
                              G_BINDING_DERIVED_TYPE_DATE , "EndRange" , L"20070907:103000" ,
                              G_TYPE_INVALID );
		
			    TRAPD( err , requestservice( interface_pointer, "GetList" , 
				                             G_BINDING_DERIVED_TYPE_UNICODE, "Type" , L"CalendarEntry",
				                             G_BINDING_DERIVED_TYPE_MAP    , "Filter"      , getlistparam, 
				                             G_TYPE_INVALID ,
				                             &outparam, NULL ,0 , &error));
				map_delete( getlistparam );

				if ( error == KErrNone )
					{
					TInt rescnt = getoutputcount(outparam);
					if(rescnt)
						{
						GValue calList;
						GValue entrymap;
						GValue value;
						const char* key1 = "Summary";
						int count = 0;
						int err = 0;
						GType type = getoutputatindex(outparam, &calList, 0);
						err = iterator_next(calList, &entrymap);
						while ( err == KErrNone )
							{
							error = map_findvaluewithkey (entrymap,key1,&value);
							if(error == KErrNone)
								{
								wchar_t resulttype[256];
								getresult(value, G_BINDING_DERIVED_TYPE_UNICODE, resulttype);
								//Sunil Compare the text here
								}
							
							count++;
							err = iterator_next(calList, &entrymap);
							}
							
						if ( count != 5 )
							error = KErrGeneral;
						}
			    	}
			    
			    resetoutput(outparam);
			    arruids.ResetAndDestroy();
				}
			else
				error = KErrGeneral;	
			
			}
		}
		
	RemoveCalendarFile( interface_pointer, KTestCal1File);

	closeinterface( interface_pointer );
	
    unloadservice( service_name , interface_name );
    
    cbindingdetach();
    
    return error;
	
	}

  
//	
//Whats done here? 
//	Get the default system Calendar using GetList of CCalendarService and output that to GetListdefaultCalendar.txt
//       
TInt CTCalendarGetListTest::GetListTextFilter(CStifItemParser& /*aItem*/ )
	{
	gchar key[32];
	GValue outparam;
	int num = 0;
	
	void *interface_pointer = NULL;	

	TInt error = KErrNone;

	cbindingattach();
	
	num = User::CountAllocCells();
	
	TRAP( error, interface_pointer = loadservice( service_name, interface_name, G_TYPE_INVALID ) );
	
	if ( error == KErrNone && interface_pointer )
		{
		RemoveCalendarFile( interface_pointer, KTestCal1File);

		error = AddCalendarFile( interface_pointer, KTestCal1File);
		
		if ( error == KErrNone || error == KErrAlreadyExists )
			{
			RPointerArray<TUIDSet> arruids(5);
			
			TUIDSet* uids = NULL;
			
			if(AddAppointmentLocal(interface_pointer, KTestCal1File, uids) == KErrNone && uids)
				{
				arruids.Append(uids);
				uids = NULL;
				}

			if ( arruids.Count() > 0 )
				{
			    GValue getlistparam;
			    
			    const wchar_t* text = L"Meeting";
			     
		        map_construct( &getlistparam, G_BINDING_DERIVED_TYPE_UNICODE , "CalendarName", KTestCal1File, 
                              G_BINDING_DERIVED_TYPE_UNICODE, "SearchText" , text,
                              G_TYPE_INVALID );
		
			    TRAPD( err , requestservice( interface_pointer, "GetList" , 
				                             G_BINDING_DERIVED_TYPE_UNICODE, "Type" , L"CalendarEntry",
				                             G_BINDING_DERIVED_TYPE_MAP    , "Filter"      , getlistparam, 
				                             G_TYPE_INVALID ,
				                             &outparam, NULL ,0 , &error));
				map_delete( getlistparam );

				if ( error == KErrNone )
					{
					TInt rescnt = getoutputcount(outparam);
					if(rescnt)
						{
						GValue calList;
						GValue entrymap;
						GValue value;
						const char* key1 = "Summary";
						int count = 0;
						int err = 0;
						GType type = getoutputatindex(outparam, &calList, 0);
						err = iterator_next(calList, &entrymap);
						while ( err == KErrNone )
							{
							error = map_findvaluewithkey (entrymap,key1,&value);
							if(error == KErrNone)
								{
								wchar_t resulttype[256];
								getresult(value, G_BINDING_DERIVED_TYPE_UNICODE, resulttype);
								//Sunil Compare the text here
								count++;
								}
							
							
							err = iterator_next(calList, &entrymap);
							}
							
						if ( count != 5 )
							error = KErrGeneral;
						}
			    	}
			    else
			    	error = err;	
			    
			    resetoutput(outparam);
			    arruids.ResetAndDestroy();
				}
			else
				error = KErrGeneral;	
			
			}
		}
		
	RemoveCalendarFile( interface_pointer, KTestCal1File);

	closeinterface( interface_pointer );
	
    unloadservice( service_name , interface_name );
    
    cbindingdetach();
    
    return error;
	
    }
    

//	
//Whats done here? 
//	Get the default system Calendar using GetList of CCalendarService and output that to GetListdefaultCalendar.txt
//           
TInt CTCalendarGetListTest::GetListTypeFilter(CStifItemParser& /*aItem*/ )
	{
	TInt result = KErrNone;
	
	gchar key[32];
	GValue outparam;
	int num = 0;
	
	void *interface_pointer = NULL;	

	TInt error = KErrNone;

	cbindingattach();
	
	num = User::CountAllocCells();
	
	TRAP( error, interface_pointer = loadservice( service_name, interface_name, G_TYPE_INVALID ) );
	
	if ( error == KErrNone && interface_pointer )
		{
		RemoveCalendarFile( interface_pointer, KTestCal1File);

		error = AddCalendarFile( interface_pointer, KTestCal1File);
		
		if ( error == KErrNone || error == KErrAlreadyExists )
			{
			RPointerArray<TUIDSet> arruids(5);
			
			TUIDSet* uids = NULL;
			
			if(AddAppointmentWithoutRepeat(interface_pointer, KTestCal1File, uids) == KErrNone && uids)
				{
				arruids.Append(uids);
				uids = NULL;
				}

			if(AddEvent(interface_pointer, KTestCal1File, uids) == KErrNone && uids)
				{
				arruids.Append(uids);
				uids = NULL;
				}

			if ( arruids.Count() > 0 )
				{
			    GValue getlistparam;
			    
			    const wchar_t* entrytype = L"Meeting";
			     
		        map_construct( &getlistparam, G_BINDING_DERIVED_TYPE_UNICODE , "CalendarName", KTestCal1File, 
                              G_BINDING_DERIVED_TYPE_UNICODE, "Type" , entrytype,
                              G_TYPE_INVALID );
		
			    TRAPD( err , requestservice( interface_pointer, "GetList" , 
				                             G_BINDING_DERIVED_TYPE_UNICODE, "Type" , L"CalendarEntry",
				                             G_BINDING_DERIVED_TYPE_MAP    , "Filter"      , getlistparam, 
				                             G_TYPE_INVALID ,
				                             &outparam, NULL ,0 , &error));
				map_delete( getlistparam );

				if ( error == KErrNone )
					{
					TInt rescnt = getoutputcount(outparam);
					if(rescnt)
						{
						GValue calList;
						GValue entrymap;
						GValue value;
						const char* key1 = "Type";
						int count = 0;
						int err = 0;
						GType type = getoutputatindex(outparam, &calList, 0);
						err = iterator_next(calList, &entrymap);
						while ( err == KErrNone )
							{
							error = map_findvaluewithkey (entrymap,key1,&value);
							if(error == KErrNone)
								{
								wchar_t resulttype[40];
								getresult(value, G_BINDING_DERIVED_TYPE_UNICODE, resulttype);
								//Sunil Compare the type here
								count++;
								}
							
							
							err = iterator_next(calList, &entrymap);
							}
							
						if(count != 1)
							error = KErrGeneral;
						}
			    	}
			    else
			    	error = err;	
			    
			    resetoutput(outparam);
			    arruids.ResetAndDestroy();
				}
			else
				error = KErrGeneral;	
			
			}
		}
		
	RemoveCalendarFile( interface_pointer, KTestCal1File);

	closeinterface( interface_pointer );
	
    unloadservice( service_name , interface_name );
    
    cbindingdetach();
    
    return error;
	}
	
	
//	
//Whats done here? 
//	Get the default system Calendar using GetList of CCalendarService and output that to GetListdefaultCalendar.txt
//       
TInt CTCalendarGetListTest::GetListInvalidCalName(CStifItemParser& /*aItem*/ )
	{
	gchar key[32];
	GValue outparam;
	int num = 0;
	
	void *interface_pointer = NULL;	

	TInt error = KErrNone;

	cbindingattach();
	
	num = User::CountAllocCells();
	
	TRAP( error, interface_pointer = loadservice( service_name, interface_name, G_TYPE_INVALID ) );
	
	if ( error == KErrNone && interface_pointer )
		{
	    GValue getlistparam;
			    
		RemoveCalendarFile( interface_pointer, KTestCal1File);

        map_construct( &getlistparam, G_BINDING_DERIVED_TYPE_UNICODE , "CalendarName", KTestCal1File, 
                      G_TYPE_INVALID );

	    TRAPD( err , requestservice( interface_pointer, "GetList" , 
		                             G_BINDING_DERIVED_TYPE_UNICODE, "Type" , L"CalendarEntry",
		                             G_BINDING_DERIVED_TYPE_MAP    , "Filter"      , getlistparam, 
		                             G_TYPE_INVALID ,
		                             &outparam, NULL ,0 , &error));
		map_delete( getlistparam );

		if ( error == 1012 )// Sapi error code ErrNotFound
			{
			error = KErrNone;	
	    	}
	    
	    resetoutput(outparam);
		}
		
	RemoveCalendarFile( interface_pointer, KTestCal1File);

	closeinterface( interface_pointer );
	
    unloadservice( service_name , interface_name );
    
    cbindingdetach();
    
    return error;
	}


//	
//Whats done here? 
//	Get the default system Calendar using GetList of CCalendarService and output that to GetListdefaultCalendar.txt
//       
TInt CTCalendarGetListTest::GetListInvalidGUID(CStifItemParser& /*aItem*/ )
	{
	TInt result = KErrNone;
	
	gchar key[32];
	GValue outparam;
	int num = 0;
	
	void *interface_pointer = NULL;	

	TInt error = KErrNone;

	cbindingattach();
	
	num = User::CountAllocCells();
	
	TRAP( error, interface_pointer = loadservice( service_name, interface_name, G_TYPE_INVALID ) );
	
	if ( error == KErrNone && interface_pointer )
		{
		RemoveCalendarFile( interface_pointer, KTestCal1File);

		error = AddCalendarFile( interface_pointer, KTestCal1File);
		
		if ( error == KErrNone || error == KErrAlreadyExists )
			{
			RPointerArray<TUIDSet> arruids(5);
			
			TUIDSet* uids = NULL;
			
			if(AddAppointmentWithoutRepeat(interface_pointer, KTestCal1File, uids) == KErrNone && uids)
				{
				arruids.Append(uids);
				uids = NULL;
				}

			if(AddEvent(interface_pointer, KTestCal1File, uids) == KErrNone && uids)
				{
				arruids.Append(uids);
				uids = NULL;
				}

			if ( arruids.Count() > 0 )
				{
			    GValue getlistparam;
			    
			    const char* guidFlter = "abc";
			     
		        map_construct( &getlistparam, G_BINDING_DERIVED_TYPE_UNICODE , "CalendarName", KTestCal1File, 
                              G_TYPE_STRING, "GlobalUid" , guidFlter,
                              G_TYPE_INVALID );
		
			    TRAPD( err , requestservice( interface_pointer, "GetList" , 
				                             G_BINDING_DERIVED_TYPE_UNICODE, "Type" , L"CalendarEntry",
				                             G_BINDING_DERIVED_TYPE_MAP    , "Filter"      , getlistparam, 
				                             G_TYPE_INVALID ,
				                             &outparam, NULL ,0 , &error));
				map_delete( getlistparam );

				if ( error == KErrNone )
					{
					TInt rescnt = getoutputcount(outparam);
					if(rescnt != 0)
						{
						GValue calList;
						GValue entrymap;
						int count = 0;
						int err = 0;
						GType type = getoutputatindex(outparam, &calList, 0);
						err = iterator_next(calList, &entrymap);
						while ( err == KErrNone )
							{
							count++;
							err = iterator_next(calList, &entrymap);
							}
							
						if(count != 0)
							error = KErrGeneral;
						}
			    	}
			    
			    resetoutput(outparam);
			    arruids.ResetAndDestroy();
				}
			else
				error = KErrGeneral;	
			
			}
		}
		
	RemoveCalendarFile( interface_pointer, KTestCal1File);

	closeinterface( interface_pointer );
	
    unloadservice( service_name , interface_name );
    
    cbindingdetach();
    
    return error;
	
	}	
	

//	
//Whats done here? 
//	Get the default system Calendar using GetList of CCalendarService and output that to GetListdefaultCalendar.txt
//       
TInt CTCalendarGetListTest::GetListInvalidLUID(CStifItemParser& /*aItem*/ )
	{
	TInt result = KErrNone;
	
	gchar key[32];
	GValue outparam;
	int num = 0;
	
	void *interface_pointer = NULL;	

	TInt error = KErrNone;

	cbindingattach();
	
	num = User::CountAllocCells();
	
	TRAP( error, interface_pointer = loadservice( service_name, interface_name, G_TYPE_INVALID ) );
	
	if ( error == KErrNone && interface_pointer )
		{
		RemoveCalendarFile( interface_pointer, KTestCal1File);

		error = AddCalendarFile( interface_pointer, KTestCal1File);
		
		if ( error == KErrNone || error == KErrAlreadyExists )
			{
			RPointerArray<TUIDSet> arruids(5);
			
			TUIDSet* uids = NULL;
			
			if(AddAppointmentWithoutRepeat(interface_pointer, KTestCal1File, uids) == KErrNone && uids)
				{
				arruids.Append(uids);
				uids = NULL;
				}

			if(AddEvent(interface_pointer, KTestCal1File, uids) == KErrNone && uids)
				{
				arruids.Append(uids);
				uids = NULL;
				}

			if ( arruids.Count() > 0 )
				{
			    GValue getlistparam;
			    
			    unsigned int luidFlter = 0;
			     
		        map_construct( &getlistparam, G_BINDING_DERIVED_TYPE_UNICODE , "CalendarName", KTestCal1File, 
                              G_TYPE_UINT, "LocalUid" , luidFlter,
                              G_TYPE_INVALID );
		
			    TRAPD( err , requestservice( interface_pointer, "GetList" , 
				                             G_BINDING_DERIVED_TYPE_UNICODE, "Type" , L"CalendarEntry",
				                             G_BINDING_DERIVED_TYPE_MAP    , "Filter"      , getlistparam, 
				                             G_TYPE_INVALID ,
				                             &outparam, NULL ,0 , &error));
				map_delete( getlistparam );

				if ( error == KErrNone )
					{
					TInt rescnt = getoutputcount(outparam);
					if(rescnt)
						{
						GValue calList;
						GValue entrymap;
						GValue value;
						int count = 0;
						int err = 0;
						GType type = getoutputatindex(outparam, &calList, 0);
						err = iterator_next(calList, &entrymap);
						while ( err == KErrNone )
							{
							count++;
							err = iterator_next(calList, &entrymap);
							}
							
						if(count != 0)
							error = KErrGeneral;
						}
			    	}
			    
			    resetoutput(outparam);
			    arruids.ResetAndDestroy();
				}
			else
				error = KErrGeneral;	
			
			}
		}
		
	RemoveCalendarFile( interface_pointer, KTestCal1File);

	closeinterface( interface_pointer );
	
    unloadservice( service_name , interface_name );
    
    cbindingdetach();
    
    return error;
	}		
