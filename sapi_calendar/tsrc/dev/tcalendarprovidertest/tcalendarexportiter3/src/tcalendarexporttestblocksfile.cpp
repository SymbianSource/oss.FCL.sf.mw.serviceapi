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
#include <unistd.h>

#include <badesca.h>

#include<LiwServiceHandler.h>


#include "cliwbinding.h"

#include "tcalendarexporttest.h"

#include "calendarheader.h"

void StartAlarmServerL();
TInt RemoveCalendarFile(void* aInterfaceptr, const wchar_t* aCalname)	;
TInt AddCalendarFile(void* aInterfaceptr, const wchar_t* aCalname)	;
TInt DeleteAllCalendarEntry(void* aInterfaceptr, const wchar_t* aCalname)	;
TInt AddEvent(void* aInterfaceptr, const wchar_t* aCalname, TUIDSet*& uids);
TInt AddAppointmentWithDailyRepeat(void* aInterfaceptr, const wchar_t* aCalname, TUIDSet*& uids);
TInt AddTodoEntry(void* aInterfaceptr, const wchar_t* aCalname, TUIDSet*& uids);
TInt AddDayEvent(void* aInterfaceptr, const wchar_t* aCalname, TUIDSet*& uids);
TInt AddAnniversary(void* aInterfaceptr, const wchar_t* aCalname, TUIDSet*& uids);
TInt AddReminder(void* aInterfaceptr, const wchar_t* aCalname, TUIDSet*& uids);
TInt AddAppointmentWithoutRepeat(void* aInterfaceptr, const wchar_t* aCalname, TUIDSet*& uids);

sem_t exportall_async_semFile = NULL;
sem_t exportforguids_async_semFile = NULL;
sem_t exportforluids_async_semFile = NULL;

void* doExportAllTestCBindingAsyncFile( void* /*x*/);
TInt doExportAllTestCBindingFile();

void* doExportForGuidsTestCBindingAsyncFile( void* /*x*/);
TInt doExportForGuidsTestCBindingFile();

void* doExportForLuidsTestCBindingAsyncFile( void* /*x*/);
TInt doExportForLuidsTestCBindingFile();


// -----------------------------------------------------------------------------
// CTCalendarExportTest::Export
// Test Method to test the Export(Synchronous)
// Functionality of CalenderService
// -----------------------------------------------------------------------------
//
TInt  CTCalendarExportTest::ExportAllFile(CStifItemParser& /*aItem*/)
	{
	
	
	TInt result=KErrNone;
	
	result = doExportAllTestCBindingFile();
	
	if( result == KErrNone )
		{
		__UHEAP_MARK;	
		
	//	result = doExportTestDirect( 0 );// 0 for sync
			
		__UHEAP_MARKEND;
		}
	return result;
    }


// -----------------------------------------------------------------------------
// CTCalendarExportTest::ExportAsync
// Test Method to test the ExportAsync(ASynchronous)
// Functionality of CalenderService
// -----------------------------------------------------------------------------
//
TInt  CTCalendarExportTest::ExportAllAsyncFile(CStifItemParser& /*aItem*/)
	{	
	pthread_t tid;
	
	if(sem_init(&exportall_async_semFile,0,0)<0)
	{
		iLog->Log(_L("Export async sem_init failed"));
		return ;
	}
	
	int ret = pthread_create(&tid, NULL, doExportAllTestCBindingAsyncFile ,NULL);

    if(ret )
	{
		printf("ERROR; return code from pthread_create() is %d\n", ret);
    	exit(-1);
	}
	
	pthread_join(tid, NULL);
	return 0;
    }


// -----------------------------------------------------------------------------
// CTCalendarExportTest::Export
// Test Method to test the Export(Synchronous)
// Functionality of CalenderService
// -----------------------------------------------------------------------------
//
TInt  CTCalendarExportTest::ExportForGuidsFile(CStifItemParser& /*aItem*/)
	{
	
	
	TInt result=KErrNone;
	
	result = doExportForGuidsTestCBindingFile();
	
	if( result == KErrNone )
		{
		__UHEAP_MARK;	
		
	//	result = doExportTestDirect( 0 );// 0 for sync
			
		__UHEAP_MARKEND;
		}
	return result;
    }


// -----------------------------------------------------------------------------
// CTCalendarExportTest::ExportAsync
// Test Method to test the ExportAsync(ASynchronous)
// Functionality of CalenderService
// -----------------------------------------------------------------------------
//
TInt  CTCalendarExportTest::ExportForGuidsAsyncFile(CStifItemParser& /*aItem*/)
	{	
	pthread_t tid;
	
	if(sem_init(&exportforguids_async_semFile,0,0)<0)
	{
		iLog->Log(_L("Export async sem_init failed"));
		return ;
	}
	
	int ret = pthread_create(&tid, NULL, doExportForGuidsTestCBindingAsyncFile ,NULL);

    if(ret )
	{
		printf("ERROR; return code from pthread_create() is %d\n", ret);
    	exit(-1);
	}
	
	pthread_join(tid, NULL);
	return 0;
    }
    
// -----------------------------------------------------------------------------
// CTCalendarExportTest::Export
// Test Method to test the Export(Synchronous)
// Functionality of CalenderService
// -----------------------------------------------------------------------------
//
TInt  CTCalendarExportTest::ExportForLuidsFile(CStifItemParser& /*aItem*/)
	{
	
	
	TInt result=KErrNone;
	
	result = doExportForLuidsTestCBindingFile();
	
	if( result == KErrNone )
		{
		__UHEAP_MARK;	
		
	//	result = doExportTestDirect( 0 );// 0 for sync
			
		__UHEAP_MARKEND;
		}
	return result;
    }


// -----------------------------------------------------------------------------
// CTCalendarExportTest::ExportAsync
// Test Method to test the ExportAsync(ASynchronous)
// Functionality of CalenderService
// -----------------------------------------------------------------------------
//
TInt  CTCalendarExportTest::ExportForLuidsAsyncFile(CStifItemParser& /*aItem*/)
	{	
	pthread_t tid;
	
	if(sem_init(&exportforluids_async_semFile,0,0)<0)
	{
		iLog->Log(_L("Export async sem_init failed"));
		return ;
	}
	
	int ret = pthread_create(&tid, NULL, doExportForLuidsTestCBindingAsyncFile ,NULL);

    if(ret )
	{
		printf("ERROR; return code from pthread_create() is %d\n", ret);
    	exit(-1);
	}
	
	pthread_join(tid, NULL);
	return 0;
    }
    
// -----------------------------------------------------------------------------
// CTCalendarExportTest::ICALExport
// Test Method to test the ICALExport(Synchronous)
// Functionality of CalenderService
// -----------------------------------------------------------------------------
//
TInt  CTCalendarExportTest::ICALExportFile(CStifItemParser& /*aItem*/)
	{
	__UHEAP_MARK;
	
	TInt result=KErrNone;
	

	__UHEAP_MARKEND;
	
	return result;
    }


// -----------------------------------------------------------------------------
// CTCalendarExportTest::ICALExportAsync
// Test Method to test the ICALExportAsync(ASynchronous)
// Functionality of CalenderService
// -----------------------------------------------------------------------------
//
TInt  CTCalendarExportTest::ICALExportAsyncFile(CStifItemParser& /*aItem*/)
	{
	__UHEAP_MARK;
	
	TInt result=KErrNone;

			
	__UHEAP_MARKEND;
	
	return result;
    }






static const wchar_t *KCALEXPORTSYNCNAME1  = L"exportallsynctestcal1";
static const wchar_t *KCALEXPORTSYNCNAME2  = L"exportallsynctestcal2";


TInt doExportAllTestCBindingFile() //cbinding stuff
	{
	void *interface_pointer = NULL;	
	
	GValue outparam;
	
	GValue inparam;
		
	TInt error = KErrNone;

	const char *service_name   = "Service.Calendar";
	
	const char *interface_name = "IDataSource";

	const char *calendarName   = "C:Calendar";
	
	const char *format		   = "VCal";
	
	const char *returnkey = "ReturnValue";
	
	TInt num = User::CountAllocCells();
	
	cbindingattach();
	
	
	num = User::CountAllocCells();
	
	TRAP( error, interface_pointer = loadservice( service_name, interface_name, G_TYPE_INVALID ) );
	
	RemoveCalendarFile( interface_pointer, KCALEXPORTSYNCNAME1 );	
	RemoveCalendarFile( interface_pointer, KCALEXPORTSYNCNAME2 );
	
	AddCalendarFile( interface_pointer, KCALEXPORTSYNCNAME1 );
	AddCalendarFile( interface_pointer, KCALEXPORTSYNCNAME2 );
	
	num = User::CountAllocCells();

    num = User::CountAllocCells();
    
    TUIDSet *uids = NULL;
    
    TInt err;
    
    err = AddAppointmentWithoutRepeat( interface_pointer , KCALEXPORTSYNCNAME1 , uids);
    if( uids )
    	{
    	delete uids;
    	uids = NULL;
    	}
    err = AddReminder( interface_pointer , KCALEXPORTSYNCNAME1 , uids);
    if( uids )
    	{
    	delete uids;
    	uids = NULL;
    	}
    /*err = AddAnniversary( interface_pointer , KCALEXPORTSYNCNAME1 , uids);
    if( uids )
    	{
    	delete uids;
    	uids = NULL;
    	}*/
    err = AddDayEvent( interface_pointer , KCALEXPORTSYNCNAME1 , uids);
    if( uids )
    	{
    	delete uids;
    	uids = NULL;
    	}
    err = AddTodoEntry( interface_pointer , KCALEXPORTSYNCNAME1 , uids);
    if( uids )
    	{
    	delete uids;
    	uids = NULL;
    	}
    err = AddAppointmentWithDailyRepeat( interface_pointer , KCALEXPORTSYNCNAME1 , uids);    
	if( uids )
    	{
    	delete uids;
    	uids = NULL;
    	}
    	
    map_construct( &inparam , G_BINDING_DERIVED_TYPE_UNICODE , "CalendarName", KCALEXPORTSYNCNAME1 , 
		                      G_BINDING_DERIVED_TYPE_UNICODE,  "Format"      , L"VCal"       , 
		                      G_BINDING_DERIVED_TYPE_UNICODE,  "FileName"      , L"c:\\exportfile.txt"       , 
		                      G_TYPE_INVALID );
	
	num = User::CountAllocCells();
	          
    TRAP( err , requestservice( interface_pointer, "Export" , 
	                             G_BINDING_DERIVED_TYPE_UNICODE, "Type" , L"CalendarEntry",
	                             G_BINDING_DERIVED_TYPE_MAP    , "Data"      , inparam , 
	                             G_TYPE_INVALID ,
	                             &outparam     , NULL ,0 , &error));

	num = User::CountAllocCells();
	
	GValue result, returntypemap, tempresult;
	
	GType type;
	
	gchar key[32];
	
	if( err == KErrNone )
			{		
			TInt x = 0;
			
			TInt rescnt = getoutputcount(outparam);
			
			
			//now Export this stuff to some calendar and get the guids.......
			
			num = User::CountAllocCells();
	
			map_delete(inparam);

			resetoutput(outparam);
		
			num = User::CountAllocCells();
			
			map_construct( &inparam , G_BINDING_DERIVED_TYPE_UNICODE , "CalendarName", KCALEXPORTSYNCNAME2 , 
									  G_BINDING_DERIVED_TYPE_UNICODE,  "FileName"      , L"c:\\exportfile.txt" ,
		                              G_BINDING_DERIVED_TYPE_UNICODE,  "Format"      , L"VCal"       , 
		                              G_TYPE_INVALID );
		                              
    		TRAP( err , requestservice( interface_pointer, "Import" , 
	                             G_BINDING_DERIVED_TYPE_UNICODE, "Type" , L"CalendarEntry",
	                             G_BINDING_DERIVED_TYPE_MAP    , "Data"      , inparam , 
	                             G_TYPE_INVALID ,
	                             &outparam     , NULL ,0 , &error));
	                            

			num = User::CountAllocCells();
			
			rescnt = getoutputcount(outparam);
			
			type = getoutputatindex( outparam, &result, 0);

			GValue resnext, value;
			
			rescnt=0;
			
			unsigned int localuid;
			
			while( iterator_next(result, &resnext) == KErrNone )
				{
				++rescnt;
				
				err = map_findvaluewithkey ( resnext , "LocalUid" ,&value);
				
				//getresult(value, G_TYPE_UINT, &localuid);
				}
			
			
			if( rescnt == 5 )//because 6 entries are added earlier
				error = KErrNone;
			else
			    error = KErrGeneral;				
			}

	map_delete(inparam);
	
	num = User::CountAllocCells();

	resetoutput(outparam);

	num = User::CountAllocCells();

	
	RemoveCalendarFile( interface_pointer, KCALEXPORTSYNCNAME1 );
	
	RemoveCalendarFile( interface_pointer, KCALEXPORTSYNCNAME2 );
	
	closeinterface( interface_pointer );
	
	num = User::CountAllocCells();
	
    unloadservice( service_name , interface_name );
    
    num = User::CountAllocCells();

    cbindingdetach();
    
    num = User::CountAllocCells();    	
    	
	if( error != 0 )
		{
		 User::Leave(error);
		}
	
	return error;	
	}



//async export all
	
int ExportAllasyncHandlerFile(GValue* value)
{
    GValue UIDMap;
    gint error = -1;
    gint mCount = 0;
    gint cErr = 0;
    
    pthread_t tid1 = pthread_self();
	
	stopscheduler(tid1);
	
	
	sem_post(&exportall_async_semFile);
	
    return KErrNone;	
}



//for asyn
static const wchar_t *KCALEXPORTASYNCNAME1  = L"exportallasynctestcal1";
static const wchar_t *KCALEXPORTASYNCNAME2  = L"exportallasynctestcal2";



void* doExportAllTestCBindingAsyncFile( void* /*x*/) //cbinding stuff
	{
	void *interface_pointer = NULL;	
	
	GValue outparam, tempparam;
	
	GValue inparam;
		
	TInt error = KErrNone;

	const char *service_name   = "Service.Calendar";
	
	const char *interface_name = "IDataSource";

	const char *calendarName   = "C:Calendar";
	
	const char *format		   = "VCal";
	
	const char *returnkey = "ReturnValue";
	
	TInt num = User::CountAllocCells();
	
	cbindingattach();
	
		

	pthread_t tid =pthread_self();//for async
	
	createnewscheduler(tid);//for async
	
	num = User::CountAllocCells();
	

	TRAP( error, interface_pointer = loadservice( service_name, interface_name, G_TYPE_INVALID ) );
	
	RemoveCalendarFile( interface_pointer, KCALEXPORTASYNCNAME1 );
	
	RemoveCalendarFile( interface_pointer, KCALEXPORTASYNCNAME2 );
	
	AddCalendarFile( interface_pointer, KCALEXPORTASYNCNAME1 );

	AddCalendarFile( interface_pointer, KCALEXPORTASYNCNAME2 );
	
	num = User::CountAllocCells();
    
    TUIDSet *uids = NULL;
    
    TInt err;
    
    err = AddAppointmentWithoutRepeat( interface_pointer , KCALEXPORTASYNCNAME1 , uids);
    if( uids )
    	{
    	delete uids;
    	uids = NULL;
    	}
    err = AddReminder( interface_pointer , KCALEXPORTASYNCNAME1 , uids);
    if( uids )
    	{
    	delete uids;
    	uids = NULL;
    	}
    /*err = AddAnniversary( interface_pointer , KCALEXPORTASYNCNAME1 , uids);
    if( uids )
    	{
    	delete uids;
    	uids = NULL;
    	}*/
    err = AddDayEvent( interface_pointer , KCALEXPORTASYNCNAME1 , uids);
    if( uids )
    	{
    	delete uids;
    	uids = NULL;
    	}
    err = AddTodoEntry( interface_pointer , KCALEXPORTASYNCNAME1 , uids);
    if( uids )
    	{
    	delete uids;
    	uids = NULL;
    	}
    err = AddAppointmentWithDailyRepeat( interface_pointer , KCALEXPORTASYNCNAME1 , uids);    
	if( uids )
    	{
    	delete uids;
    	uids = NULL;
    	}
    	
    map_construct( &inparam , G_BINDING_DERIVED_TYPE_UNICODE , "CalendarName", KCALEXPORTASYNCNAME1 , 
		                      G_BINDING_DERIVED_TYPE_UNICODE,  "Format"      , L"VCal"       , 
		                      G_BINDING_DERIVED_TYPE_UNICODE,  "FileName"      , L"c:\\ExportAllAsync.txt"       , 
		                      G_TYPE_INVALID );
	
	num = User::CountAllocCells();
	     
	//making an asynchronous call to export all          
    TRAP( err , requestservice( interface_pointer, "Export" , 
	                             G_BINDING_DERIVED_TYPE_UNICODE, "Type" , L"CalendarEntry",
	                             G_BINDING_DERIVED_TYPE_MAP    , "Data"      , inparam , 
	                             G_TYPE_INVALID ,
	                             &tempparam     , ExportAllasyncHandlerFile ,0 , &error));

	startscheduler(tid);
			
	num = User::CountAllocCells();
	
	if(sem_wait(&exportall_async_semFile))
		{
		return (void *)	-1;
		}

	
	GValue result, returntypemap, tempresult;
	
	GType type;
	
	gchar key[32];
	
	
	
	if( err == KErrNone )
			{		
		
			//now Export the export all buffer to a calendar this stuff to some calendar and get the guids.......
			
			num = User::CountAllocCells();
	
			map_delete(inparam);


			num = User::CountAllocCells();
			
			map_construct( &inparam , G_BINDING_DERIVED_TYPE_UNICODE , "CalendarName", KCALEXPORTASYNCNAME2 , 
									  G_BINDING_DERIVED_TYPE_UNICODE,  "FileName"      , L"c:\\ExportAllAsync.txt",
		                              G_BINDING_DERIVED_TYPE_UNICODE,  "Format"      , L"VCal"       , 
		                              G_TYPE_INVALID );
	                
    		TRAP( err , requestservice( interface_pointer, "Import" , 
	                             G_BINDING_DERIVED_TYPE_UNICODE, "Type" , L"CalendarEntry",
	                             G_BINDING_DERIVED_TYPE_MAP    , "Data"      , inparam , 
	                             G_TYPE_INVALID ,
	                             &outparam              , NULL ,0 , &error));
	        		
			num = User::CountAllocCells();
			
			int rescnt = getoutputcount(outparam);
			
			type = getoutputatindex( outparam, &result, 0);

			GValue resnext, value;
			
			rescnt=0;
			
			unsigned int localuid;
			
			while( iterator_next(result, &resnext) == KErrNone )
				{
				++rescnt;
				
				err = map_findvaluewithkey ( resnext , "LocalUid" ,&value);
				
				//getresult(value, G_TYPE_UINT, &localuid);
				}
			
			
			if( rescnt == 5 )//because 6 entries are added earlier
				error = KErrNone;
			else
			    error = KErrGeneral;			                   
			}
	
	map_delete(inparam);
	
	num = User::CountAllocCells();
	
	resetoutput(outparam);
			
	RemoveCalendarFile( interface_pointer, KCALEXPORTASYNCNAME1 );
	
	RemoveCalendarFile( interface_pointer, KCALEXPORTASYNCNAME2 );
	
	closeinterface( interface_pointer );
	
	num = User::CountAllocCells();
	
    unloadservice( service_name , interface_name );
    
    num = User::CountAllocCells();

    cbindingdetach();
    
    num = User::CountAllocCells();    	
    	
	if( error != 0 )
		{
		 User::Leave(error);
		}		
	}	



static const wchar_t *KCALEXPORTFORGUIDSSYNCNAME1  = L"exportforguidssynctestcal1";
static const wchar_t *KCALEXPORTFORGUIDSSYNCNAME2  = L"exportforguidssynctestcal2";
	
TInt doExportForGuidsTestCBindingFile()
	{
	void *interface_pointer = NULL;	
	
	GValue outparam;
	
	GValue inparam, guidlist;
		
	TInt error = KErrNone;

	const char *service_name   = "Service.Calendar";
	
	const char *interface_name = "IDataSource";

	const char *calendarName   = "C:Calendar";
	
	const char *format		   = "VCal";
	
	const char *returnkey = "ReturnValue";
	
	TInt num = User::CountAllocCells();
	
	cbindingattach();
	
	
	num = User::CountAllocCells();
	
	TRAP( error, interface_pointer = loadservice( service_name, interface_name, G_TYPE_INVALID ) );
	
	RemoveCalendarFile( interface_pointer, KCALEXPORTFORGUIDSSYNCNAME1 );	
	RemoveCalendarFile( interface_pointer, KCALEXPORTFORGUIDSSYNCNAME2 );
	
	AddCalendarFile( interface_pointer, KCALEXPORTFORGUIDSSYNCNAME1 );
	AddCalendarFile( interface_pointer, KCALEXPORTFORGUIDSSYNCNAME2 );
	
	num = User::CountAllocCells();

    num = User::CountAllocCells();
    
    TUIDSet *uids = NULL;
    
    TInt err, x;
    
    wchar_t tempp[6][40];
    
    err = AddAppointmentWithoutRepeat( interface_pointer , KCALEXPORTFORGUIDSSYNCNAME1 , uids);
    if( uids )
    	{
    	TBuf<100> tmpuid;
    	tmpuid.Copy(uids->iGlobalUID->Des());
    	wcsncpy(tempp[0], (wchar_t *)tmpuid.Ptr(), tmpuid.Length());
 
    	x = uids->iGlobalUID->Des().Length();
    	tempp[0][x]='\0';
    		
    	delete uids;
    	uids = NULL;
    	}
    err = AddReminder( interface_pointer , KCALEXPORTFORGUIDSSYNCNAME1 , uids);
    if( uids )
    	{
    
    	TBuf<100> tmpuid;
    	tmpuid.Copy(uids->iGlobalUID->Des());
    	wcsncpy(tempp[1], (wchar_t *)tmpuid.Ptr(), tmpuid.Length());
    	x = uids->iGlobalUID->Des().Length();
    	tempp[1][x]='\0';
    	delete uids;
    	uids = NULL;
    	}
    err = AddDayEvent( interface_pointer , KCALEXPORTFORGUIDSSYNCNAME1 , uids);
    if( uids )
    	{
        
    	TBuf<100> tmpuid;
    	tmpuid.Copy(uids->iGlobalUID->Des());
    	wcsncpy(tempp[2], (wchar_t *)tmpuid.Ptr(), tmpuid.Length());

    	x = uids->iGlobalUID->Des().Length();
    	tempp[2][x]='\0';	
    	delete uids;
    	uids = NULL;
    	}
    err = AddTodoEntry( interface_pointer , KCALEXPORTFORGUIDSSYNCNAME1 , uids);
    if( uids )
    	{
    
    	TBuf<100> tmpuid;
    	tmpuid.Copy(uids->iGlobalUID->Des());
    	wcsncpy(tempp[3], (wchar_t *)tmpuid.Ptr(), tmpuid.Length());
    	x = uids->iGlobalUID->Des().Length();
    	tempp[3][x]='\0';
    	delete uids;
    	uids = NULL;
    	}
    err = AddAppointmentWithDailyRepeat( interface_pointer , KCALEXPORTFORGUIDSSYNCNAME1 , uids);    
	if( uids )
    	{
    
    	TBuf<100> tmpuid;
    	tmpuid.Copy(uids->iGlobalUID->Des());
    	wcsncpy(tempp[4], (wchar_t *)tmpuid.Ptr(), tmpuid.Length());
    	x = uids->iGlobalUID->Des().Length();
    	tempp[4][x]='\0';
    	delete uids;
    	uids = NULL;
    	}
    /*err = AddAnniversary( interface_pointer , KCALEXPORTFORGUIDSSYNCNAME1 , uids);
    if( uids )
    	{
    
    	TBuf<100> tmpuid;
    	tmpuid.Copy(uids->iGlobalUID->Des());
    	wcscpy(tempp[2], (wchar_t *)tmpuid.Ptr() )
    	x = uids->iGlobalUID->Des().Length();
    	tempp[2][x]='\0';
    	delete uids;
    	uids = NULL;
    	}*/
  	
  	list_construct(&guidlist, G_BINDING_DERIVED_TYPE_UNICODE , tempp[0]
  							, G_BINDING_DERIVED_TYPE_UNICODE , tempp[1]
  							, G_BINDING_DERIVED_TYPE_UNICODE , tempp[2]
  							, G_BINDING_DERIVED_TYPE_UNICODE , tempp[3]
  							, G_BINDING_DERIVED_TYPE_UNICODE , tempp[4]
  						//	, G_BINDING_DERIVED_TYPE_UNICODE , tempp[5]							  							  							  							
  							, G_TYPE_INVALID  );
  							
    map_construct( &inparam , G_BINDING_DERIVED_TYPE_UNICODE , "CalendarName", KCALEXPORTFORGUIDSSYNCNAME1 , 
		                      G_BINDING_DERIVED_TYPE_UNICODE,  "Format"      , L"VCal"       ,
		                      G_BINDING_DERIVED_TYPE_UNICODE,  "FileName"      , L"c:\\exportguid.txt"       ,
		                      G_BINDING_DERIVED_TYPE_LIST   , "GlobalUidList", guidlist, 
		                      G_TYPE_INVALID );

	num = User::CountAllocCells();
	          
    TRAP( err , requestservice( interface_pointer, "Export" , 
	                             G_BINDING_DERIVED_TYPE_UNICODE, "Type"  , L"CalendarEntry",
	                             G_BINDING_DERIVED_TYPE_MAP    , "Data"       , inparam ,	                    
	                             G_TYPE_INVALID ,
	                             &outparam     , NULL ,0 , &error));

	num = User::CountAllocCells();
	
	GValue result, returntypemap, tempresult;
	
	GType type;
	
	gchar key[32];
	
	if( err == KErrNone )
			{		
			TInt x = 0;
			
			map_delete(inparam);

			resetoutput(outparam);
		
			num = User::CountAllocCells();
			
			map_construct( &inparam , G_BINDING_DERIVED_TYPE_UNICODE , "CalendarName", KCALEXPORTFORGUIDSSYNCNAME2 , 
		                              G_BINDING_DERIVED_TYPE_UNICODE,  "FileName"      , L"c:\\exportguid.txt"       , 
		                              G_BINDING_DERIVED_TYPE_UNICODE,  "Format"      , L"VCal"       , 
		                              G_TYPE_INVALID );
		                              
    		TRAP( err , requestservice( interface_pointer, "Import" , 
	                             G_BINDING_DERIVED_TYPE_UNICODE, "Type" , L"CalendarEntry",
	                             G_BINDING_DERIVED_TYPE_MAP    , "Data"      , inparam , 
	                             G_TYPE_INVALID ,
	                             &outparam     , NULL ,0 , &error));
	                            

			num = User::CountAllocCells();
			
			int rescnt = getoutputcount(outparam);
			
			type = getoutputatindex( outparam, &result, 0);

			GValue resnext, value;
			
			rescnt=0;
			
			unsigned int localuid;
			
			while( iterator_next(result, &resnext) == KErrNone )
				{
				++rescnt;
				
				err = map_findvaluewithkey ( resnext , "LocalUid" ,&value);
				
				//getresult(value, G_TYPE_UINT, &localuid);
				}
			
			
			if( rescnt == 5 )//because 6 entries are added earlier
				error = KErrNone;
			else
			    error = KErrGeneral;				
			}

	map_delete(inparam);
	
	list_delete(guidlist);
	
	num = User::CountAllocCells();

	resetoutput(outparam);

	num = User::CountAllocCells();
	
	RemoveCalendarFile( interface_pointer, KCALEXPORTFORGUIDSSYNCNAME1 );
	
	RemoveCalendarFile( interface_pointer, KCALEXPORTFORGUIDSSYNCNAME2 );
	
	closeinterface( interface_pointer );
	
	num = User::CountAllocCells();
	
    unloadservice( service_name , interface_name );
    
    num = User::CountAllocCells();

    cbindingdetach();
    
    num = User::CountAllocCells();    	
    	
	if( error != 0 )
		{
		 User::Leave(error);
		}
	
	return error;	
	}
	



//async export for guids
	
int ExportForGuidsasyncHandlerFile(GValue* value)
{
    GValue UIDMap;
    gint error = -1;
    gint mCount = 0;
    gint cErr = 0;
    
    pthread_t tid1 = pthread_self();
	
	stopscheduler(tid1);
	
	
	sem_post(&exportforguids_async_semFile);
	
    return KErrNone;	
}
	
//for asyn
static const wchar_t *KCALEXPORTFORGUIDSASYNCNAME1  = L"exportforguidsasynctestcal1";
static const wchar_t *KCALEXPORTFORGUIDSASYNCNAME2  = L"exportforguidsasynctestcal2";
	
void* doExportForGuidsTestCBindingAsyncFile( void* /*x*/)
	{
	void *interface_pointer = NULL;	
	
	GValue outparam, tempparam;
	
	GValue inparam, guidlist;
		
	TInt error = KErrNone;

	const char *service_name   = "Service.Calendar";
	
	const char *interface_name = "IDataSource";

	const char *calendarName   = "C:Calendar";
	
	const char *format		   = "VCal";
	
	const char *returnkey = "ReturnValue";
	
	TInt num = User::CountAllocCells();
	
	cbindingattach();
	
		

	pthread_t tid =pthread_self();//for async
	
	createnewscheduler(tid);//for async
	
	num = User::CountAllocCells();
	

	TRAP( error, interface_pointer = loadservice( service_name, interface_name, G_TYPE_INVALID ) );
	
	RemoveCalendarFile( interface_pointer, KCALEXPORTFORGUIDSASYNCNAME1 );
	
	RemoveCalendarFile( interface_pointer, KCALEXPORTFORGUIDSASYNCNAME2 );
	
	AddCalendarFile( interface_pointer, KCALEXPORTFORGUIDSASYNCNAME1 );

	AddCalendarFile( interface_pointer, KCALEXPORTFORGUIDSASYNCNAME2 );
	
	num = User::CountAllocCells();
    
    TUIDSet *uids = NULL;
    
    TInt err, x;
    
    wchar_t tempp[6][30];
    
    err = AddAppointmentWithoutRepeat( interface_pointer , KCALEXPORTFORGUIDSASYNCNAME1 , uids);
    if( uids )
    	{
    	TBuf<100> tmpuid;
    	tmpuid.Copy(uids->iGlobalUID->Des());
    	wcsncpy(tempp[0], (wchar_t *)tmpuid.Ptr(), tmpuid.Length());
    	x = uids->iGlobalUID->Des().Length();
    	tempp[0][x]='\0';
    		
    	delete uids;
    	uids = NULL;
    	}
    err = AddReminder( interface_pointer , KCALEXPORTFORGUIDSASYNCNAME1 , uids);
    if( uids )
    	{
 
    	TBuf<100> tmpuid;
    	tmpuid.Copy(uids->iGlobalUID->Des());
    	wcsncpy(tempp[1], (wchar_t *)tmpuid.Ptr(), tmpuid.Length());
    	x = uids->iGlobalUID->Des().Length();
    	tempp[1][x]='\0';
    	delete uids;
    	uids = NULL;
    	}
    err = AddDayEvent( interface_pointer , KCALEXPORTFORGUIDSASYNCNAME1 , uids);
    if( uids )
    	{
       
    	TBuf<100> tmpuid;
    	tmpuid.Copy(uids->iGlobalUID->Des());
    	wcsncpy(tempp[2], (wchar_t *)tmpuid.Ptr(), tmpuid.Length());
    	x = uids->iGlobalUID->Des().Length();
    	tempp[2][x]='\0';	
    	delete uids;
    	uids = NULL;
    	}
    err = AddTodoEntry( interface_pointer , KCALEXPORTFORGUIDSASYNCNAME1 , uids);
    if( uids )
    	{
    	
    	TBuf<100> tmpuid;
    	tmpuid.Copy(uids->iGlobalUID->Des());
    	wcsncpy(tempp[3], (wchar_t *)tmpuid.Ptr(), tmpuid.Length());
    	x = uids->iGlobalUID->Des().Length();
    	tempp[3][x]='\0';
    	delete uids;
    	uids = NULL;
    	}
    err = AddAppointmentWithDailyRepeat( interface_pointer , KCALEXPORTFORGUIDSASYNCNAME1 , uids);    
	if( uids )
    	{
    	
    	TBuf<100> tmpuid;
    	tmpuid.Copy(uids->iGlobalUID->Des());
    	wcsncpy(tempp[4], (wchar_t *)tmpuid.Ptr(), tmpuid.Length());
    	x = uids->iGlobalUID->Des().Length();
    	tempp[4][x]='\0';
    	delete uids;
    	uids = NULL;
    	}
     /*err = AddAnniversary( interface_pointer , KCALEXPORTFORGUIDSASYNCNAME1 , uids);
    if( uids )
    	{
    
    	TBuf<100> tmpuid;
    	tmpuid.Copy(uids->iGlobalUID->Des());
    	wcscpy(tempp[2], (wchar_t *)tmpuid.Ptr() )
    	x = uids->iGlobalUID->Des().Length();
    	tempp[2][x]='\0';
    	delete uids;
    	uids = NULL;
    	}*/
 	
  	list_construct(&guidlist, G_BINDING_DERIVED_TYPE_UNICODE , tempp[0]
  							, G_BINDING_DERIVED_TYPE_UNICODE , tempp[1]
  							, G_BINDING_DERIVED_TYPE_UNICODE , tempp[2]
  							, G_BINDING_DERIVED_TYPE_UNICODE , tempp[3]
  							, G_BINDING_DERIVED_TYPE_UNICODE , tempp[4]
  							//, G_BINDING_DERIVED_TYPE_UNICODE , tempp[5]							  							  							  							
  							, G_TYPE_INVALID  );	
  							
    map_construct( &inparam , G_BINDING_DERIVED_TYPE_UNICODE , "CalendarName", KCALEXPORTFORGUIDSASYNCNAME1 , 
		                      G_BINDING_DERIVED_TYPE_UNICODE,  "Format"      , L"VCal"       ,
		                      G_BINDING_DERIVED_TYPE_UNICODE,  "FileName"      , L"c:\\exportguidasync.txt"       ,
		                      G_BINDING_DERIVED_TYPE_LIST   , "GlobalUidList", guidlist, 
		                      G_TYPE_INVALID );
	
	num = User::CountAllocCells();
	     
	//making an asynchronous call to export all          
    TRAP( err , requestservice( interface_pointer, "Export" , 
	                             G_BINDING_DERIVED_TYPE_UNICODE, "Type" , L"CalendarEntry",
	                             G_BINDING_DERIVED_TYPE_MAP    , "Data"      , inparam , 
	                             G_TYPE_INVALID ,
	                             &tempparam     , ExportForGuidsasyncHandlerFile ,0 , &error));

	startscheduler(tid);
			
	num = User::CountAllocCells();
	
	if(sem_wait(&exportforguids_async_semFile))
		{
		return (void *)	-1;
		}

	
	GValue result, returntypemap, tempresult;
	
	GType type;
	
	gchar key[32];
	
	
	
	if( err == KErrNone )
			{		
		
			//now Export the export all buffer to a calendar this stuff to some calendar and get the guids.......
			
			num = User::CountAllocCells();
	
			map_delete(inparam);


			num = User::CountAllocCells();
			
			map_construct( &inparam , G_BINDING_DERIVED_TYPE_UNICODE , "CalendarName", KCALEXPORTFORGUIDSASYNCNAME2 , 
									  G_BINDING_DERIVED_TYPE_UNICODE,	"FileName"      , L"c:\\exportguidasync.txt",
		                              G_BINDING_DERIVED_TYPE_UNICODE,  "Format"      , L"VCal"       , 
		                              G_TYPE_INVALID );
	                
    		TRAP( err , requestservice( interface_pointer, "Import" , 
	                             G_BINDING_DERIVED_TYPE_UNICODE, "Type" , L"CalendarEntry",
	                             G_BINDING_DERIVED_TYPE_MAP    , "Data"      , inparam , 
	                             G_TYPE_INVALID ,
	                             &outparam              , NULL ,0 , &error));
	        		
			num = User::CountAllocCells();
			
			int rescnt = getoutputcount(outparam);
			
			type = getoutputatindex( outparam, &result, 0);

			GValue resnext, value;
			
			rescnt=0;
			
			unsigned int localuid;
			
			while( iterator_next(result, &resnext) == KErrNone )
				{
				++rescnt;
				
				err = map_findvaluewithkey ( resnext , "LocalUid" ,&value);
				
				//getresult(value, G_TYPE_UINT, &localuid);
				}
			
			
			if( rescnt == 5 )//because 6 entries are added earlier
				error = KErrNone;
			else
			    error = KErrGeneral;			                   
			}
	
	
	
	list_delete(guidlist);
		
	map_delete(inparam);
	
	num = User::CountAllocCells();

	
	resetoutput(outparam);
			
	RemoveCalendarFile( interface_pointer, KCALEXPORTFORGUIDSASYNCNAME1 );
	
	RemoveCalendarFile( interface_pointer, KCALEXPORTFORGUIDSASYNCNAME2 );
	
	closeinterface( interface_pointer );
	
	num = User::CountAllocCells();
	
    unloadservice( service_name , interface_name );
    
    num = User::CountAllocCells();

    cbindingdetach();
    
    num = User::CountAllocCells();    	
    	
	if( error != 0 )
		{
		 User::Leave(error);
		}		
	}




static const wchar_t *KCALEXPORTFORLUIDSSYNCNAME1  = L"exportforluidssynctestcal1";
static const wchar_t *KCALEXPORTFORLUIDSSYNCNAME2  = L"exportforluidssynctestcal2";
	
TInt doExportForLuidsTestCBindingFile()
	{
	void *interface_pointer = NULL;	
	
	GValue outparam;
	
	GValue inparam, guidlist;
		
	TInt error = KErrNone;

	const char *service_name   = "Service.Calendar";
	
	const char *interface_name = "IDataSource";

	const char *calendarName   = "C:Calendar";
	
	const char *format		   = "VCal";
	
	const char *returnkey = "ReturnValue";
	
	TInt num = User::CountAllocCells();
	
	cbindingattach();
	
	
	num = User::CountAllocCells();
	
	TRAP( error, interface_pointer = loadservice( service_name, interface_name, G_TYPE_INVALID ) );
	
	RemoveCalendarFile( interface_pointer, KCALEXPORTFORLUIDSSYNCNAME1 );	
	RemoveCalendarFile( interface_pointer, KCALEXPORTFORLUIDSSYNCNAME2 );
	
	AddCalendarFile( interface_pointer, KCALEXPORTFORLUIDSSYNCNAME1 );
	AddCalendarFile( interface_pointer, KCALEXPORTFORLUIDSSYNCNAME2 );
	
	num = User::CountAllocCells();

    num = User::CountAllocCells();
    
    TUIDSet *uids = NULL;
    
    TInt err, x;
    
    wchar_t tempp[6][40];
    
    err = AddAppointmentWithoutRepeat( interface_pointer , KCALEXPORTFORLUIDSSYNCNAME1 , uids);
    if( uids )
    	{
    	TBuf<100> tmpuid;
    	tmpuid.Num(uids->iLocalUID);
    	wcsncpy(tempp[0], (wchar_t *)tmpuid.Ptr(), tmpuid.Length());
    	x = tmpuid.Length();
    	tempp[0][x]='\0';	
    	delete uids;
    	uids = NULL;
    	}
    err = AddReminder( interface_pointer , KCALEXPORTFORLUIDSSYNCNAME1 , uids);
    if( uids )
    	{
    	TBuf<100> tmpuid;
    	tmpuid.Num(uids->iLocalUID);
     	wcsncpy(tempp[1], (wchar_t *)tmpuid.Ptr(), tmpuid.Length());
    	x = tmpuid.Length();
    	tempp[1][x]='\0';	
    	delete uids;
    	uids = NULL;
    	}
    err = AddDayEvent( interface_pointer , KCALEXPORTFORLUIDSSYNCNAME1 , uids);
    if( uids )
    	{
    	TBuf<100> tmpuid;
    	tmpuid.Num(uids->iLocalUID);
    	wcsncpy(tempp[2], (wchar_t *)tmpuid.Ptr(), tmpuid.Length());
    	x = tmpuid.Length();
    	tempp[2][x]='\0';	
    	delete uids;
    	uids = NULL;
    	}
    err = AddTodoEntry( interface_pointer , KCALEXPORTFORLUIDSSYNCNAME1 , uids);
    if( uids )
    	{
    	TBuf<100> tmpuid;
    	tmpuid.Num(uids->iLocalUID);
    	wcsncpy(tempp[3], (wchar_t *)tmpuid.Ptr(), tmpuid.Length());
    	x = tmpuid.Length();
    	tempp[3][x]='\0';	
    	delete uids;
    	uids = NULL;
    	}
    err = AddAppointmentWithDailyRepeat( interface_pointer , KCALEXPORTFORLUIDSSYNCNAME1 , uids);    
	if( uids )
    	{
    	TBuf<100> tmpuid;
    	tmpuid.Num(uids->iLocalUID);
    	wcsncpy(tempp[4], (wchar_t *)tmpuid.Ptr(), tmpuid.Length());
    	x = tmpuid.Length();
    	tempp[4][x]='\0';	
    	delete uids;
    	uids = NULL;
    	}
    /*err = AddAnniversary( interface_pointer , KCALEXPORTFORLUIDSSYNCNAME1 , uids);
    if( uids )
    	{
    	tempp[5] = uids->iLocalUID;
    	
    	delete uids;
    	uids = NULL;
    	}*/
  	
  	list_construct(&guidlist, G_BINDING_DERIVED_TYPE_UNICODE , tempp[0]
  							, G_BINDING_DERIVED_TYPE_UNICODE , tempp[1]
  							, G_BINDING_DERIVED_TYPE_UNICODE , tempp[2]
  							, G_BINDING_DERIVED_TYPE_UNICODE , tempp[3]
  							, G_BINDING_DERIVED_TYPE_UNICODE , tempp[4]
  							//, G_BINDING_DERIVED_TYPE_UNICODE , tempp[5]							  							  							  							
  							, G_TYPE_INVALID  );
  							
  	map_construct( &inparam , G_BINDING_DERIVED_TYPE_UNICODE , "CalendarName", KCALEXPORTFORLUIDSSYNCNAME1 , 
		                      G_BINDING_DERIVED_TYPE_UNICODE,  "Format"      , L"VCal"       , 
		                      G_BINDING_DERIVED_TYPE_UNICODE,  "FileName"      , L"c:\\exportluid.txt"       , 
		                      G_BINDING_DERIVED_TYPE_LIST   ,  "LocalUidList", guidlist,
		                      G_TYPE_INVALID );
	
	num = User::CountAllocCells();
	          
    TRAP( err , requestservice( interface_pointer, "Export" , 
	                             G_BINDING_DERIVED_TYPE_UNICODE, "Type"  , L"CalendarEntry",
	                             G_BINDING_DERIVED_TYPE_MAP    , "Data"       , inparam ,	                    
	                             G_TYPE_INVALID ,
	                             &outparam     , NULL ,0 , &error));

	num = User::CountAllocCells();
	
	GValue result, returntypemap, tempresult;
	
	GType type;
	
	gchar key[32];
	
	if( err == KErrNone )
			{		
			TInt x = 0;
			
	
			map_delete(inparam);

			resetoutput(outparam);
		
			num = User::CountAllocCells();
			
			map_construct( &inparam , G_BINDING_DERIVED_TYPE_UNICODE , "CalendarName", KCALEXPORTFORLUIDSSYNCNAME2 , 
		                              G_BINDING_DERIVED_TYPE_UNICODE,  "FileName"      , L"c:\\exportluid.txt"       , 
		                              G_BINDING_DERIVED_TYPE_UNICODE,  "Format"      , L"VCal"       , 
		                              G_TYPE_INVALID );
		                              
    		TRAP( err , requestservice( interface_pointer, "Import" , 
	                             G_BINDING_DERIVED_TYPE_UNICODE, "Type" , L"CalendarEntry",
	                             G_BINDING_DERIVED_TYPE_MAP    , "Data"      , inparam , 
	                             G_TYPE_INVALID ,
	                             &outparam     , NULL ,0 , &error));
	                            

			num = User::CountAllocCells();
			
			int rescnt = getoutputcount(outparam);
			
			type = getoutputatindex( outparam, &result, 0);

			GValue resnext, value;
			
			rescnt=0;
			
			unsigned int localuid;
			
			while( iterator_next(result, &resnext) == KErrNone )
				{
				++rescnt;
				
				err = map_findvaluewithkey ( resnext , "LocalUid" ,&value);
				
				//getresult(value, G_TYPE_UINT, &localuid);
				}
			
			
			if( rescnt == 5 )//because 6 entries are added earlier
				error = KErrNone;
			else
			    error = KErrGeneral;				
			}

	map_delete(inparam);
	
	list_delete(guidlist);
	
	num = User::CountAllocCells();

	resetoutput(outparam);

	num = User::CountAllocCells();
	
	RemoveCalendarFile( interface_pointer, KCALEXPORTFORLUIDSSYNCNAME1 );
	
	RemoveCalendarFile( interface_pointer, KCALEXPORTFORLUIDSSYNCNAME2 );
	
	closeinterface( interface_pointer );
	
	num = User::CountAllocCells();
	
    unloadservice( service_name , interface_name );
    
    num = User::CountAllocCells();

    cbindingdetach();
    
    num = User::CountAllocCells();    	
    	
	if( error != 0 )
		{
		 User::Leave(error);
		}
	
	return error;	
	return KErrNone;
	}



//async export for luids
	
int ExportForLuidsasyncHandlerFile(GValue* value)
{
    GValue UIDMap;
    gint error = -1;
    gint mCount = 0;
    gint cErr = 0;
    
    pthread_t tid1 = pthread_self();
	
	stopscheduler(tid1);
	
	resetoutput(*value);
	
	sem_post(&exportforluids_async_semFile);
	
    return KErrNone;	
}

//for asyn
static const wchar_t *KCALEXPORTFORLUIDSASYNCNAME1  = L"exportforluidsasynctestcal1";
static const wchar_t *KCALEXPORTFORLUIDSASYNCNAME2  = L"exportforluidsasynctestcal2";

void* doExportForLuidsTestCBindingAsyncFile( void* /*x*/)
	{
	void *interface_pointer = NULL;	
	
	GValue outparam, tempparam;
	
	GValue inparam, guidlist;
		
	TInt error = KErrNone;

	const char *service_name   = "Service.Calendar";
	
	const char *interface_name = "IDataSource";

	const char *calendarName   = "C:Calendar";
	
	const char *format		   = "VCal";
	
	const char *returnkey = "ReturnValue";
	
	TInt num = User::CountAllocCells();
	
	cbindingattach();
	
		

	pthread_t tid =pthread_self();//for async
	
	createnewscheduler(tid);//for async
	
	num = User::CountAllocCells();
	

	TRAP( error, interface_pointer = loadservice( service_name, interface_name, G_TYPE_INVALID ) );
	
	RemoveCalendarFile( interface_pointer, KCALEXPORTFORLUIDSASYNCNAME1 );
	
	RemoveCalendarFile( interface_pointer, KCALEXPORTFORLUIDSASYNCNAME2 );
	
	AddCalendarFile( interface_pointer, KCALEXPORTFORLUIDSASYNCNAME1 );

	AddCalendarFile( interface_pointer, KCALEXPORTFORLUIDSASYNCNAME2 );
	
	num = User::CountAllocCells();
    
    TUIDSet *uids = NULL;
    
    TInt err, x;
    
    wchar_t tempp[6][10];
    
    err = AddAppointmentWithoutRepeat( interface_pointer , KCALEXPORTFORLUIDSASYNCNAME1 , uids);
    if( uids )
    	{
    	TBuf<100> tmpuid;
    	tmpuid.Num(uids->iLocalUID);
    	wcsncpy(tempp[0], (wchar_t *)tmpuid.Ptr(), tmpuid.Length());
    	x = tmpuid.Length();
    	tempp[0][x]='\0';	
    	delete uids;
    	uids = NULL;
    	}
    err = AddReminder( interface_pointer , KCALEXPORTFORLUIDSASYNCNAME1 , uids);
    if( uids )
    	{
    	TBuf<100> tmpuid;
    	tmpuid.Num(uids->iLocalUID);
    	wcsncpy(tempp[1], (wchar_t *)tmpuid.Ptr(), tmpuid.Length());
    	x = tmpuid.Length();
    	tempp[1][x]='\0';	
    	delete uids;
    	uids = NULL;
    	}
    err = AddDayEvent( interface_pointer , KCALEXPORTFORLUIDSASYNCNAME1 , uids);
    if( uids )
    	{
    	TBuf<100> tmpuid;
    	tmpuid.Num(uids->iLocalUID);
    	wcsncpy(tempp[2], (wchar_t *)tmpuid.Ptr(), tmpuid.Length());
    	x = tmpuid.Length();
    	tempp[2][x]='\0';	
    	delete uids;
    	uids = NULL;
    	}
    err = AddTodoEntry( interface_pointer , KCALEXPORTFORLUIDSASYNCNAME1 , uids);
    if( uids )
    	{
    	TBuf<100> tmpuid;
    	tmpuid.Num(uids->iLocalUID);
    	wcsncpy(tempp[3], (wchar_t *)tmpuid.Ptr(), tmpuid.Length());
    	x = tmpuid.Length();
    	tempp[3][x]='\0';	
    	delete uids;
    	uids = NULL;
    	}
    err = AddAppointmentWithDailyRepeat( interface_pointer , KCALEXPORTFORLUIDSASYNCNAME1 , uids);    
	if( uids )
    	{
    	TBuf<100> tmpuid;
    	tmpuid.Num(uids->iLocalUID);
    	wcsncpy(tempp[4], (wchar_t *)tmpuid.Ptr(), tmpuid.Length());
    	x = tmpuid.Length();
    	tempp[4][x]='\0';	
    	delete uids;
    	uids = NULL;
    	}
     /*err = AddAnniversary( interface_pointer , KCALEXPORTFORLUIDSASYNCNAME1 , uids);
    if( uids )
    	{
    	tempp[2] = uids->iLocalUID;
    	delete uids;
    	uids = NULL;
    	}*/
 	
    list_construct(&guidlist, G_BINDING_DERIVED_TYPE_UNICODE , tempp[0]
  							, G_BINDING_DERIVED_TYPE_UNICODE , tempp[1]
  							, G_BINDING_DERIVED_TYPE_UNICODE , tempp[2]
  							, G_BINDING_DERIVED_TYPE_UNICODE , tempp[3]
  							, G_BINDING_DERIVED_TYPE_UNICODE , tempp[4]
  						//	, G_BINDING_DERIVED_TYPE_UNICODE , tempp[5]							  							  							  							
  							, G_TYPE_INVALID  );	
  							
    map_construct( &inparam , G_BINDING_DERIVED_TYPE_UNICODE , "CalendarName", KCALEXPORTFORLUIDSASYNCNAME1 , 
		                      G_BINDING_DERIVED_TYPE_UNICODE,  "Format"      , L"VCal"       ,
		                      G_BINDING_DERIVED_TYPE_UNICODE,  "FileName"      , L"c:\\exportluidasync.txt"       ,
		                      G_BINDING_DERIVED_TYPE_LIST   , "LocalUidList", guidlist, 
		                      G_TYPE_INVALID );
	
	num = User::CountAllocCells();
	     
	//making an asynchronous call to export all          
    TRAP( err , requestservice( interface_pointer, "Export" , 
	                             G_BINDING_DERIVED_TYPE_UNICODE, "Type" , L"CalendarEntry",
	                             G_BINDING_DERIVED_TYPE_MAP    , "Data"      , inparam , 
	                             G_TYPE_INVALID ,
	                             &tempparam     , ExportForLuidsasyncHandlerFile ,0 , &error));

	startscheduler(tid);
			
	num = User::CountAllocCells();
	
	if(sem_wait(&exportforluids_async_semFile))
		{
		return (void *)	-1;
		}

	
	GValue result, returntypemap, tempresult;
	
	GType type;
	
	gchar key[32];
	
	
	
	if( err == KErrNone )
			{		
		
			//now Export the export all buffer to a calendar this stuff to some calendar and get the guids.......
			
			num = User::CountAllocCells();
	
			map_delete(inparam);


			num = User::CountAllocCells();
			
			map_construct( &inparam , G_BINDING_DERIVED_TYPE_UNICODE , "CalendarName", KCALEXPORTFORLUIDSASYNCNAME2 , 
				                      G_BINDING_DERIVED_TYPE_UNICODE,  "FileName"      , L"c:\\exportluidasync.txt"       ,
		                              G_BINDING_DERIVED_TYPE_UNICODE,  "Format"      , L"VCal"       , 
		                              G_TYPE_INVALID );
	                
    		TRAP( err , requestservice( interface_pointer, "Import" , 
	                             G_BINDING_DERIVED_TYPE_UNICODE, "Type" , L"CalendarEntry",
	                             G_BINDING_DERIVED_TYPE_MAP    , "Data"      , inparam , 
	                             G_TYPE_INVALID ,
	                             &outparam              , NULL ,0 , &error));
	        		
			num = User::CountAllocCells();
			
			int rescnt = getoutputcount(outparam);
			
			type = getoutputatindex( outparam, &result, 0);

			GValue resnext, value;
			
			rescnt=0;
			
			unsigned int localuid;
			
			while( iterator_next(result, &resnext) == KErrNone )
				{
				++rescnt;
				
				err = map_findvaluewithkey ( resnext , "LocalUid" ,&value);
				
				//getresult(value, G_TYPE_UINT, &localuid);
				}
			
			
			if( rescnt == 5 )//because 6 entries are added earlier
				error = KErrNone;
			else
			    error = KErrGeneral;			                   
			}
	
	
	
	list_delete(guidlist);
		
	map_delete(inparam);
	
	num = User::CountAllocCells();

	
	resetoutput(outparam);
			
	RemoveCalendarFile( interface_pointer, KCALEXPORTFORLUIDSASYNCNAME1 );
	
	RemoveCalendarFile( interface_pointer, KCALEXPORTFORLUIDSASYNCNAME2 );
	
	closeinterface( interface_pointer );
	
	num = User::CountAllocCells();
	
    unloadservice( service_name , interface_name );
    
    num = User::CountAllocCells();

    cbindingdetach();
    
    num = User::CountAllocCells();    	
    	
	if( error != 0 )
		{
		 User::Leave(error);
		}		
	}

	