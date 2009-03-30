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

#include "teststartconsolealarmserver3.h"
#include<LiwServiceHandler.h>

#include <f32file.h>
#include "cliwbinding.h"

#include "tcalendarimporttest.h"

sem_t import_async_sem = NULL;

TInt doImportTestDirect(TInt x);
void* doImportTestCBindingAsync( void* /*x*/);
TInt doImportTestCBinding();

_LIT(KCalNameImportTestDirect, "ImportTothisatProvider");

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTChangeStatusTest::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTCalendarImportTest::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CTChangeStatusTest::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTCalendarImportTest::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        //TRY( "SendMessage",    CTDeleteMessageTest::SendMessage ),
        
        ENTRY( "ImportProviderIter3",    	 CTCalendarImportTest::Import ),
		ENTRY( "ImportAsyncProviderIter3",    CTCalendarImportTest::ImportAsync ),
		ENTRY( "ICALImportProviderIter3",     CTCalendarImportTest::ICALImport ),
		ENTRY( "ICALImportAsyncProviderIter3",CTCalendarImportTest::ICALImportAsync ),
        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

   
#include<LiwCommon.h>    
/**
 * Callback class for asynchronous SAPI Calendar Import
*/	
class CCalCallback1 : public MLiwNotifyCallback
	{
	public:
		
		static CCalCallback1* NewL(TInt aCount, MLiwInterface* aInterface);
		
		virtual ~CCalCallback1(){}
		
		TInt HandleNotifyL(TInt aCmdId,
	            TInt aEventId,
	            CLiwGenericParamList& aEventParamList,
	            const CLiwGenericParamList& aInParamList);
		
	private:
	
 		CCalCallback1(TInt aCount, MLiwInterface* aInterface);

		TInt iCount;
		
		MLiwInterface* 			iInterface ;	
	};

	
// -----------------------------------------------------------------------------
// CTCalendarImportTest::Import
// Test Method to test the Import(Synchronous)
// Functionality of CalenderService
// -----------------------------------------------------------------------------
//
TInt  CTCalendarImportTest::Import(CStifItemParser& /*aItem*/)
	{
	
	
	TInt result=KErrNone;
	
	result = doImportTestCBinding();
	
	if( result == KErrNone )
		{
		__UHEAP_MARK;	
		
	//	result = doImportTestDirect( 0 );// 0 for sync
			
		__UHEAP_MARKEND;
		}
	return result;
    }




_LIT( KImportLogFileName, "c:\\importasynclogfile.txt");
			    
_LIT8(KImportMainFunction,    "  \nIn Main test function call at Begining Step 1\r\n         ");
_LIT8(KImportMainFunctionEnd, "  \nIn Main test function call at end Step 1z\r\n         ");
	    		
   		
void WriteLog( const TDesC8& aData)
	{
	/*RFs fs;
	    		
	RFile file;  
	
	User::LeaveIfError(fs.Connect());			    
	
	CleanupClosePushL(fs);
			    
	TInt err= file.Open(fs, KImportLogFileName, EFileWrite ); 
			    
	CleanupClosePushL(file);
	
	TInt x=0;
	
	file.Seek(ESeekEnd, x);
	
	file.Write( aData );
	
	CleanupStack::PopAndDestroy( 2 );*/
	}
// -----------------------------------------------------------------------------
// CTCalendarImportTest::ImportAsync
// Test Method to test the ImportAsync(ASynchronous)
// Functionality of CalenderService
// -----------------------------------------------------------------------------
//
TInt  CTCalendarImportTest::ImportAsync(CStifItemParser& /*aItem*/)
	{	
	
	
	
	iLog->Log( KImportMainFunction.operator()() );
	
	pthread_t tid;
	
	if(sem_init(&import_async_sem,0,0)<0)
	{
		iLog->Log(_L("Import async sem_init failed"));
		return ;
	}
	
	int ret = pthread_create(&tid, NULL, doImportTestCBindingAsync ,this);

    if(ret )
	{
		printf("ERROR; return code from pthread_create() is %d\r\n", ret);
    	exit(-1);
	}
	
	pthread_join(tid, NULL);
	
	iLog->Log( KImportMainFunctionEnd.operator()() );
	
	return 0;
    }

// -----------------------------------------------------------------------------
// CTCalendarImportTest::ICALImport
// Test Method to test the ICALImport(Synchronous)
// Functionality of CalenderService
// -----------------------------------------------------------------------------
//
TInt  CTCalendarImportTest::ICALImport(CStifItemParser& /*aItem*/)
	{
	__UHEAP_MARK;
	
	TInt result=KErrNone;
	

	__UHEAP_MARKEND;
	
	return result;
    }


// -----------------------------------------------------------------------------
// CTCalendarImportTest::ICALImportAsync
// Test Method to test the ICALImportAsync(ASynchronous)
// Functionality of CalenderService
// -----------------------------------------------------------------------------
//
TInt  CTCalendarImportTest::ICALImportAsync(CStifItemParser& /*aItem*/)
	{
	__UHEAP_MARK;
	
	TInt result=KErrNone;

			
	__UHEAP_MARKEND;
	
	return result;
    }
/*
static const char *service_name  = "Service.Calendar";
static const char *interface_name = "IDataSource";
static const wchar_t *KTestCal1File = L"C:getlistcal1";
static const wchar_t *KTestCal2File = L"C:getlistcal2";
*/

static const wchar_t *KCALIMPORTSYNCNAME1  = L"importsynctestcal1";
static const wchar_t *KCALIMPORTSYNCNAME2  = L"importsynctestcal2";


TInt doImportTestCBinding() //cbinding stuff
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
	
	RemoveCalendarFile( interface_pointer, KCALIMPORTSYNCNAME1 );
	
	RemoveCalendarFile( interface_pointer, KCALIMPORTSYNCNAME2 );
	
	AddCalendarFile( interface_pointer, KCALIMPORTSYNCNAME1 );
	AddCalendarFile( interface_pointer, KCALIMPORTSYNCNAME2 );
	
	num = User::CountAllocCells();

    num = User::CountAllocCells();
    
    TUIDSet *uids = NULL;
    
    TInt err;
    
    err = AddAppointmentWithoutRepeat( interface_pointer , KCALIMPORTSYNCNAME1 , uids);
    if( uids )
    	{
    	delete uids;
    	uids = NULL;
    	}
    err = AddReminder( interface_pointer , KCALIMPORTSYNCNAME1 , uids);
    if( uids )
    	{
    	delete uids;
    	uids = NULL;
    	}
    /*err = AddAnniversary( interface_pointer , KCALIMPORTSYNCNAME1 , uids);
    if( uids )
    	{
    	delete uids;
    	uids = NULL;
    	}*/
    err = AddDayEvent( interface_pointer , KCALIMPORTSYNCNAME1 , uids);
    if( uids )
    	{
    	delete uids;
    	uids = NULL;
    	}
    err = AddTodoEntry( interface_pointer , KCALIMPORTSYNCNAME1 , uids);
    if( uids )
    	{
    	delete uids;
    	uids = NULL;
    	}
    err = AddAppointmentWithDailyRepeat( interface_pointer , KCALIMPORTSYNCNAME1 , uids);    
	if( uids )
    	{
    	delete uids;
    	uids = NULL;
    	}
    	
    map_construct( &inparam , G_BINDING_DERIVED_TYPE_UNICODE , "CalendarName", KCALIMPORTSYNCNAME1 , 
		                      G_BINDING_DERIVED_TYPE_UNICODE,  "Format"      , L"VCal"       , 
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
	
	gchar buffer[5012];
	
	if( err == KErrNone )
			{		
			TInt x = 0;
			
			TInt rescnt = getoutputcount(outparam);
			
			type = getoutputatindex( outparam, &result, 0);
			
			rescnt = getresult( result, G_TYPE_STRING , &buffer );
			
			
			//now import this stuff to some calendar and get the guids.......
			
			num = User::CountAllocCells();
	
			map_delete(inparam);

			resetoutput(outparam);
		
			num = User::CountAllocCells();
			
			map_construct( &inparam , G_BINDING_DERIVED_TYPE_UNICODE , "CalendarName", KCALIMPORTSYNCNAME2 , 
									  G_TYPE_STRING,				   "Buffer"      , buffer		 ,
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
				
				getresult(value, G_TYPE_UINT, &localuid);
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

	
	RemoveCalendarFile( interface_pointer, KCALIMPORTSYNCNAME1 );
	
	RemoveCalendarFile( interface_pointer, KCALIMPORTSYNCNAME2 );
	
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
	
_LIT8(KImportAsyncHandler,       "  \nInside Import Async Handler function at BEGINING Step 3a\r\n         ");

_LIT8(KImportAsyncHandlerEnd,    "  \nInside Import Async Handler function at END Step 3c\r\n         ");

_LIT8(KImportAsyncHandlerMiddle, "  \nInside Import Async Handler function at MIDDLE Step 3a\r\n         ");

int CTCalendarImportTest::importasyncHandler(GValue* value)
{
iLog->Log( KImportAsyncHandler.operator()() );
	
    GValue UIDMap;
    gint error = -1;
    gint mCount = 0;
    gint cErr = 0;
    
    pthread_t tid1 = pthread_self();
	stopscheduler(tid1);
	
	int rescnt = getoutputcount(*value);
	
	GValue resnext, tvalue, result;		
	
	GType type = getoutputatindex( *value, &result, 0);
			
	rescnt=0;
	
iLog->Log( KImportAsyncHandlerMiddle.operator()() );
			
	unsigned int localuid;
			
	while( iterator_next(result, &resnext) == KErrNone )
		{
		++rescnt;
				
		error = map_findvaluewithkey ( resnext , "LocalUid" ,&tvalue);
				
		getresult(tvalue, G_TYPE_UINT, &localuid);
		}
	
			
	if( rescnt == 5 )//because 6 entries are added earlier
		error = KErrNone;
	else
		error = KErrNone;
	
	resetoutput(*value);
	
	sem_post(&import_async_sem);
	
iLog->Log( KImportAsyncHandlerEnd.operator()() );
	
    return error;	
}

//for async

_LIT8(KImportAsyncFunctionBEG,                  "  \nInside doImportTestCBindingAsync function at BEGINING Step 2a\r\n         ");	 
_LIT8(KImportAsyncFunctionAfterCBindingAttach,  "  \nStep 2b After CBindingAttach\r\n         ");
_LIT8(KImportAsyncFunctionAfterCreateSched,     "  \nStep 2c After Create Scheduler\r\n         ");
_LIT8(KImportAsyncFunctionAfterLoad,            "  \nStep 2d After Load Service\r\n         ");	
_LIT8(KImportAsyncFunctionAfterCalAdd,          "  \nStep 2e After Adding the Calendars\r\n         ");
_LIT8(KImportAsyncFunctionAfterEntriesAddition, "  \nStep 2f After Addition of Entries\r\n         ");
_LIT8(KImportAsyncFunctionAfterSyncExport,      "  \nStep 2g After Synchronous Export\r\n         ");	
_LIT8(KImportAsyncFunctionAfterGetResult,       "  \nStep 2h After Get Result of Export\r\n         ");		             
_LIT8(KImportAsyncFunctionAfterAsyncCall,       "  \nStep 2i After Async Import Call\r\n         ");
_LIT8(KImportAsyncFunctionAfterSemWait,         "  \nStep 2j After Sem Wait\r\n         ");	
_LIT8(KImportAsyncFunctionAfterRemoveCals,      "  \nStep 2k After Remove Calendar\r\n         ");
_LIT8(KImportAsyncFunctionAfterUnLoad,          "  \nStep 2l After Unload Service\r\n         ");
_LIT8(KImportAsyncFunctionEnd,                  "  \nStep 2z At End\r\n         "); 
	    		
static const wchar_t *KCALIMPORTASYNCNAME1  = L"importasynctestcal1";
static const wchar_t *KCALIMPORTASYNCNAME2  = L"importasynctestcal2";


void* CTCalendarImportTest::TMPdoImportTestCBindingAsync() //cbinding stuff
	{
iLog->Log( KImportAsyncFunctionBEG.operator()() );
	
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
	

iLog->Log( KImportAsyncFunctionAfterCBindingAttach.operator()() );	


	pthread_t tid =pthread_self();//for async
	
	createnewscheduler(tid);//for async
	
	num = User::CountAllocCells();
	

iLog->Log( KImportAsyncFunctionAfterCreateSched.operator()() );

	
	TRAP( error, interface_pointer = loadservice( service_name, interface_name, G_TYPE_INVALID ) );
	
	
iLog->Log( KImportAsyncFunctionAfterLoad.operator()() );
	
	
	RemoveCalendarFile( interface_pointer, KCALIMPORTASYNCNAME1 );
	
	RemoveCalendarFile( interface_pointer, KCALIMPORTASYNCNAME2 );
	
	AddCalendarFile( interface_pointer, KCALIMPORTASYNCNAME1 );

	AddCalendarFile( interface_pointer, KCALIMPORTASYNCNAME2 );
	

iLog->Log( KImportAsyncFunctionAfterCalAdd.operator()() );


	num = User::CountAllocCells();
    
    TUIDSet *uids = NULL;
    
    TInt err;
    
    err = AddAppointmentWithoutRepeat( interface_pointer , KCALIMPORTASYNCNAME1 , uids);
    if( uids )
    	{
    	delete uids;
    	uids = NULL;
    	}
    err = AddReminder( interface_pointer , KCALIMPORTASYNCNAME1 , uids);
    if( uids )
    	{
    	delete uids;
    	uids = NULL;
    	}
    /*err = AddAnniversary( interface_pointer , KCALIMPORTASYNCNAME1 , uids);
    if( uids )
    	{
    	delete uids;
    	uids = NULL;
    	}*/
    err = AddDayEvent( interface_pointer , KCALIMPORTASYNCNAME1 , uids);
    if( uids )
    	{
    	delete uids;
    	uids = NULL;
    	}
    err = AddTodoEntry( interface_pointer , KCALIMPORTASYNCNAME1 , uids);
    if( uids )
    	{
    	delete uids;
    	uids = NULL;
    	}
    err = AddAppointmentWithDailyRepeat( interface_pointer , KCALIMPORTASYNCNAME1 , uids);    
	if( uids )
    	{
    	delete uids;
    	uids = NULL;
    	}
 
 iLog->Log( KImportAsyncFunctionAfterEntriesAddition.operator()() );
 
    	
    map_construct( &inparam , G_BINDING_DERIVED_TYPE_UNICODE , "CalendarName", KCALIMPORTASYNCNAME1 , 
		                      G_BINDING_DERIVED_TYPE_UNICODE,  "Format"      , L"VCal"       , 
		                      G_TYPE_INVALID );
	
	num = User::CountAllocCells();
	          
    TRAP( err , requestservice( interface_pointer, "Export" , 
	                             G_BINDING_DERIVED_TYPE_UNICODE, "Type" , L"CalendarEntry",
	                             G_BINDING_DERIVED_TYPE_MAP    , "Data"      , inparam , 
	                             G_TYPE_INVALID ,
	                             &outparam     , NULL ,0 , &error));

	num = User::CountAllocCells();


iLog->Log( KImportAsyncFunctionAfterSyncExport.operator()() );

	
	GValue result, returntypemap, tempresult;
	
	GType type;
	
	gchar key[32];
	
	gchar buffer[5012];
	
	if( err == KErrNone )
			{		
			TInt x = 0;
			
			TInt rescnt = getoutputcount(outparam);
			
			type = getoutputatindex( outparam, &result, 0);
			
			rescnt = getresult( result, G_TYPE_STRING , &buffer );
			
			
		
iLog->Log( KImportAsyncFunctionAfterGetResult.operator()() );
			
			
			//now import this stuff to some calendar and get the guids.......
			
			num = User::CountAllocCells();
	
			map_delete(inparam);

			resetoutput(outparam);

			num = User::CountAllocCells();
			
			map_construct( &inparam , G_BINDING_DERIVED_TYPE_UNICODE , "CalendarName", KCALIMPORTASYNCNAME2 , 
									  G_TYPE_STRING,				   "Buffer"      , buffer		 ,
		                              G_BINDING_DERIVED_TYPE_UNICODE,  "Format"      , L"VCal"       , 
		                              G_TYPE_INVALID );
	                
    		TRAP( err , requestservice( interface_pointer, "Import" , 
	                             G_BINDING_DERIVED_TYPE_UNICODE, "Type" , L"CalendarEntry",
	                             G_BINDING_DERIVED_TYPE_MAP    , "Data"      , inparam , 
	                             G_TYPE_INVALID ,
	                             &outparam              , importasyncHandler ,0 , &error));
	             

iLog->Log( KImportAsyncFunctionAfterAsyncCall.operator()() );	 

                           
			startscheduler(tid);
			
			num = User::CountAllocCells();
			
			if(sem_wait(&import_async_sem))
				{
				return (void *)	-1;
				}
			}
	
	
iLog->Log( KImportAsyncFunctionAfterSemWait.operator()() );


	map_delete(inparam);
	
	num = User::CountAllocCells();
	
	RemoveCalendarFile( interface_pointer, KCALIMPORTASYNCNAME1 );
	
	RemoveCalendarFile( interface_pointer, KCALIMPORTASYNCNAME2 );
	
	closeinterface( interface_pointer );
	
	num = User::CountAllocCells();
	

iLog->Log( KImportAsyncFunctionAfterRemoveCals.operator()() );


    unloadservice( service_name , interface_name );
    
    num = User::CountAllocCells();


iLog->Log( KImportAsyncFunctionAfterUnLoad.operator()() );


    cbindingdetach();
    
    num = User::CountAllocCells();    	
    
  
 iLog->Log( KImportAsyncFunctionEnd.operator()() );
 	
	if( error != 0 )
		{
		 User::Leave(error);
		}	
	}

void* CTCalendarImportTest::doImportTestCBindingAsync( void* x) //cbinding stuff
	{
	CTCalendarImportTest* temp = (CTCalendarImportTest*)x;
	return temp->TMPdoImportTestCBindingAsync();
/*	
iLog->Log( KImportAsyncFunctionBEG.operator()() );
	
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
	

iLog->Log( KImportAsyncFunctionAfterCBindingAttach.operator()() );	


	pthread_t tid =pthread_self();//for async
	
	createnewscheduler(tid);//for async
	
	num = User::CountAllocCells();
	

iLog->Log( KImportAsyncFunctionAfterCreateSched.operator()() );

	
	TRAP( error, interface_pointer = loadservice( service_name, interface_name, G_TYPE_INVALID ) );
	
	
iLog->Log( KImportAsyncFunctionAfterLoad.operator()() );
	
	
	RemoveCalendarFile( interface_pointer, KCALIMPORTASYNCNAME1 );
	
	RemoveCalendarFile( interface_pointer, KCALIMPORTASYNCNAME2 );
	
	AddCalendarFile( interface_pointer, KCALIMPORTASYNCNAME1 );

	AddCalendarFile( interface_pointer, KCALIMPORTASYNCNAME2 );
	

iLog->Log( KImportAsyncFunctionAfterCalAdd.operator()() );


	num = User::CountAllocCells();
    
    TUIDSet *uids = NULL;
    
    TInt err;
    
    err = AddAppointmentWithoutRepeat( interface_pointer , KCALIMPORTASYNCNAME1 , uids);
    if( uids )
    	{
    	delete uids;
    	uids = NULL;
    	}
    err = AddReminder( interface_pointer , KCALIMPORTASYNCNAME1 , uids);
    if( uids )
    	{
    	delete uids;
    	uids = NULL;
    	}
    err = AddDayEvent( interface_pointer , KCALIMPORTASYNCNAME1 , uids);
    if( uids )
    	{
    	delete uids;
    	uids = NULL;
    	}
    err = AddTodoEntry( interface_pointer , KCALIMPORTASYNCNAME1 , uids);
    if( uids )
    	{
    	delete uids;
    	uids = NULL;
    	}
    err = AddAppointmentWithDailyRepeat( interface_pointer , KCALIMPORTASYNCNAME1 , uids);    
	if( uids )
    	{
    	delete uids;
    	uids = NULL;
    	}
 
 iLog->Log( KImportAsyncFunctionAfterEntriesAddition.operator()() );
 
    	
    map_construct( &inparam , G_BINDING_DERIVED_TYPE_UNICODE , "CalendarName", KCALIMPORTASYNCNAME1 , 
		                      G_BINDING_DERIVED_TYPE_UNICODE,  "Format"      , L"VCal"       , 
		                      G_TYPE_INVALID );
	
	num = User::CountAllocCells();
	          
    TRAP( err , requestservice( interface_pointer, "Export" , 
	                             G_BINDING_DERIVED_TYPE_UNICODE, "Type" , L"CalendarEntry",
	                             G_BINDING_DERIVED_TYPE_MAP    , "Data"      , inparam , 
	                             G_TYPE_INVALID ,
	                             &outparam     , NULL ,0 , &error));

	num = User::CountAllocCells();


iLog->Log( KImportAsyncFunctionAfterSyncExport.operator()() );

	
	GValue result, returntypemap, tempresult;
	
	GType type;
	
	gchar key[32];
	
	gchar buffer[5012];
	
	if( err == KErrNone )
			{		
			TInt x = 0;
			
			TInt rescnt = getoutputcount(outparam);
			
			type = getoutputatindex( outparam, &result, 0);
			
			rescnt = getresult( result, G_TYPE_STRING , &buffer );
			
			
		
iLog->Log( KImportAsyncFunctionAfterGetResult.operator()() );
			
			
			//now import this stuff to some calendar and get the guids.......
			
			num = User::CountAllocCells();
	
			map_delete(inparam);

			resetoutput(outparam);

			num = User::CountAllocCells();
			
			map_construct( &inparam , G_BINDING_DERIVED_TYPE_UNICODE , "CalendarName", KCALIMPORTASYNCNAME2 , 
									  G_TYPE_STRING,				   "Buffer"      , buffer		 ,
		                              G_BINDING_DERIVED_TYPE_UNICODE,  "Format"      , L"VCal"       , 
		                              G_TYPE_INVALID );
	                
    		TRAP( err , requestservice( interface_pointer, "Import" , 
	                             G_BINDING_DERIVED_TYPE_UNICODE, "Type" , L"CalendarEntry",
	                             G_BINDING_DERIVED_TYPE_MAP    , "Data"      , inparam , 
	                             G_TYPE_INVALID ,
	                             &outparam              , importasyncHandler ,0 , &error));
	             

iLog->Log( KImportAsyncFunctionAfterAsyncCall.operator()() );	 

                           
			startscheduler(tid);
			
			num = User::CountAllocCells();
			
			if(sem_wait(&import_async_sem))
				{
				return (void *)	-1;
				}
			}
	
	
iLog->Log( KImportAsyncFunctionAfterSemWait.operator()() );


	map_delete(inparam);
	
	num = User::CountAllocCells();
	
	RemoveCalendarFile( interface_pointer, KCALIMPORTASYNCNAME1 );
	
	RemoveCalendarFile( interface_pointer, KCALIMPORTASYNCNAME2 );
	
	closeinterface( interface_pointer );
	
	num = User::CountAllocCells();
	

iLog->Log( KImportAsyncFunctionAfterRemoveCals.operator()() );


    unloadservice( service_name , interface_name );
    
    num = User::CountAllocCells();


iLog->Log( KImportAsyncFunctionAfterUnLoad.operator()() );


    cbindingdetach();
    
    num = User::CountAllocCells();    	
    
  
 iLog->Log( KImportAsyncFunctionEnd.operator()() );
 	
	if( error != 0 )
		{
		 User::Leave(error);
		}	*/
	}	
	
_LIT8(KService, "Service.Calendar");

_LIT8(KIDataSource,"IDataSource");

_LIT (KCalendarFile,"C:Calendar");

_LIT (KFormat,"VCal");
	
TInt doImportTestDirect(TInt x)
	{
	CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    
    CLiwGenericParamList* inParamList = &(iServiceHandler->InParamListL());
    
    CLiwGenericParamList* outParamList = &(iServiceHandler->OutParamListL());
    
    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource , KService );
    
    crit->SetServiceClass( TUid::Uid( KLiwClassBase ) );
    
    RCriteriaArray a;
    
    a.AppendL(crit);    
    
    iServiceHandler->AttachL(a);
    
	iServiceHandler->ExecuteServiceCmdL(*crit, *inParamList, *outParamList); 
	
	delete crit;
	
	crit = NULL;
	
	a.Reset();
	
	TInt pos = 0;
	
    MLiwInterface* interface = NULL;
    
    outParamList->FindFirst(pos, KIDataSource );
    
    if(pos != KErrNotFound)
        {
        interface = (*outParamList)[pos].Value().AsInterface();	
        }

	outParamList->Reset();


	//adding the calendar to the system
	TLiwGenericParam addelement0, addelement1;
    
    TLiwVariant addCalName1( KCalNameImportTestDirect );
    
    TLiwVariant addContentType(_L("Calendar"));
    
    CLiwDefaultMap* addmap = CLiwDefaultMap::NewL();
    
    addelement0.SetNameAndValueL(_L8("Type") , addContentType );
    
    inParamList->AppendL(addelement0);
    
    addmap->InsertL(_L8("CalendarName"), addCalName1  );
	
	TLiwVariant filterparam0( addmap );
	
	addelement1.SetNameAndValueL(_L8("Item"),filterparam0);
	
	inParamList->AppendL(addelement1);
	
	TInt err = 0;

	TRAP(err,interface->ExecuteCmdL( _L8("Add") ,*inParamList ,*outParamList));
	
	filterparam0.Reset();
	
	addelement0.Reset();
	
	addelement1.Reset();
	
	addCalName1.Reset();
	
	addContentType.Reset();
	
	addmap->DecRef();
	
	inParamList->Reset();//setting the input and output to use it further
	
	outParamList->Reset();
	
	
	//exporting the entries to the buffer from the default calendar
   	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
   	
	CleanupStack::PushL(map);

	TLiwVariant calName( KCalendarFile ), format( KFormat );

	map->InsertL(_L8("CalendarName"), calName );
	
	map->InsertL(_L8("Format"), format);

	calName.Reset();
	
	format.Reset();
	
	
    TLiwVariant contentparam ( _L("CalendarEntry") );
    
    TLiwGenericParam element0;
    
    element0.SetNameAndValueL(_L8("Type") , contentparam );
    
    inParamList->AppendL(element0);
	
	element0.Reset();
	
	contentparam.Reset();
	
	TLiwVariant filterparam(map);
    
	TLiwGenericParam element ;	
	
	element.SetNameAndValueL(_L8("Data"),filterparam);	
	
	inParamList->AppendL(element);
	
	element.Reset();
	
	filterparam.Reset();
	
    map->DecRef();

    CleanupStack::Pop(map);

	TRAP(err,interface->ExecuteCmdL( _L8("Export") ,*inParamList ,*outParamList));

    pos = 0 ;
    
    const TLiwGenericParam* output = outParamList->FindFirst( pos,_L8("ReturnValue")); 
	 
	if(output) //got the exported entries in this buffer so import them to the calendar KCalNameImportTestDirect    
		{
		TLiwVariant returnExportedBuffer;
		 
	    HBufC8 *inputBuffer = HBufC8::NewL( output->Value().AsData().Length() );
	    
	    (inputBuffer->Des()).Copy( output->Value().AsData() );
	    
		TPtrC8 temp( output->Value().AsData() );
		
		inParamList->Reset();//setting the input and output to use it further
	
		outParamList->Reset();
				 
	    returnExportedBuffer.Set( inputBuffer->Des() );
	    
	    
	    TLiwVariant importcontentparam( _L("CalendarEntry") );
	    
	    TLiwGenericParam importelement0;
	    
	    importelement0.SetNameAndValueL(_L8("Type") , importcontentparam );
	    
	    inParamList->AppendL(importelement0); 

		
		CLiwDefaultMap* importmap = CLiwDefaultMap::NewL();

		TLiwVariant importcalName( KCalendarFile ), importformat( KFormat );

		importmap->InsertL(_L8("CalendarName"), importcalName );
		
		importmap->InsertL(_L8("Buffer"), returnExportedBuffer );
		
		importmap->InsertL(_L8("Format"), importformat);
		
		TLiwGenericParam importelement1;
		
		TLiwVariant importfilter( importmap );
		
		importelement1.SetNameAndValueL(_L8("Data"), importfilter );
		
		inParamList->AppendL(importelement1); 
		
		TInt count = 6;
		
		if( x != 0 )
			{
			CCalCallback1 *lCallBack = CCalCallback1::NewL( count, interface );
			
			TRAP(err,interface->ExecuteCmdL( _L8("Import") ,*inParamList ,*outParamList, KLiwOptASyncronous, lCallBack));
			
			CActiveScheduler::Start();//to wait till the async call is done
			}
		else	
			TRAP(err,interface->ExecuteCmdL( _L8("Import") ,*inParamList ,*outParamList));
		
		
		const TLiwGenericParam* uidoutput = outParamList->FindFirst( pos,_L8("ReturnValue")); 
		
		TInt uidcount = 6;
		
		if( uidoutput )
			{
			CLiwIterable *citr = uidoutput->Value().AsIterable();
			
			//uidcount = citr->Size();
			
			if( uidcount == 0)
				err = KErrGeneral;
			}
		else
			err = KErrGeneral;
		
		delete inputBuffer;
		
		importfilter.Reset();
		
		importelement1.Reset();
		
		importcalName.Reset();
		
		importformat.Reset();
		
		importmap->DecRef();
		
		importcontentparam.Reset();
		
		importelement0.Reset();
		
		returnExportedBuffer.Reset();
		}
	else
		err = KErrGeneral;	
	
    TInt index=0;

	interface->Close();
	
	iServiceHandler->Reset();
	
	delete iServiceHandler;

	return err;
	}
	
	
CCalCallback1* CCalCallback1::NewL(TInt aCount, MLiwInterface* aInterface)
	{
	return new (ELeave) CCalCallback1(aCount, aInterface);
	}

CCalCallback1::CCalCallback1(TInt aCount, MLiwInterface* aInterface): iInterface(aInterface),iCount(aCount)
	{
	
	}
TInt CCalCallback1::HandleNotifyL(TInt aCmdId,
									        TInt aEventId,
									        CLiwGenericParamList& aEventParamList,
									        const CLiwGenericParamList& aInParamList)
	{
/*	TInt pos = 0;
	TInt result = KErrNone;
    const TLiwGenericParam* output = aEventParamList.FindFirst( pos,KMessage);
	
	const CLiwMap* header = output->Value().AsMap();
	TInt32 newmessageid = -1;
    if ( header )
    	{
    	TLiwVariant mesageid;
    	if( header->FindL(KMessageId, mesageid))
    		{
    		newmessageid  = mesageid.AsTInt32();
    		}
    	mesageid.Reset();	
    	}
  
 	if ( newmessageid ) 
 		{
 		
	    CLiwGenericParamList* inParamList = CLiwGenericParamList::NewL();
	    CLiwGenericParamList* outParamList = CLiwGenericParamList::NewL();
 		
	   	CLiwDefaultMap* filtermap = CLiwDefaultMap::NewL();
		CleanupStack::PushL(filtermap);

	    TLiwVariant filterid( newmessageid );
	    filtermap->InsertL(KMessageId, filterid); // Mtmtype is added
	    filterid.Reset();	
    

	    TLiwVariant filterparam(filtermap);
		TLiwGenericParam element ;	
		element.SetNameAndValueL(_L8("Filter"),filterparam);
		filterparam.Reset();
		
		inParamList->AppendL(element);
		element.Reset();
		
	    filtermap->DecRef();
	    CleanupStack::Pop(filtermap);
	    

		TInt err = 0;
		TRAP(err,iInterface->ExecuteCmdL( _L8("GetList") ,*inParamList ,*outParamList));
	    
	    pos = 0 ;
	    
	    const TLiwGenericParam* finaloutput = outParamList->FindFirst( pos,_L8("MessageList"));
	
		if ( finaloutput )     
			{
			CLiwIterable* iterlist = finaloutput->Value().AsIterable();

	      	if(iterlist)
	      		{
			    TLiwVariant data;

	      		if ( iterlist->NextL(data) )
	      			result = KErrNone;	
	      		
	      		data.Reset();  

	      		}
			}
			
		inParamList->Reset();
		outParamList->Reset();
		
		delete inParamList;
		delete outParamList;
		
		}

	if ( iWaitSchedular && iWaitSchedular->IsStarted())
		{
		iWaitSchedular->AsyncStop();
		}*/
	}
	
	
	