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
#include <StifParser.h>
#include <StifTestInterface.h>
#include <logcli.h>
#ifndef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <logwrap.h>
#else
#include <logwrap.h>
#include <logengevents.h>
#include <logwraplimits.h>
#include <logfilterandeventconstants.hrh>
#include <logengdurations.h>
#endif

#include "loggingasyncservice.h"
#include "loggingservice.h"
#include "loggingfilter.h"
#include "loggingsyncservice.h"
#include "loggingevent.h"

#include "tlogging.h"
#include "logiter.h"



// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctlogging::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void Ctlogging::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// Ctlogging::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt Ctlogging::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
       ENTRY( "GetListSimple", Ctlogging::GetListSimpleL ),
       ENTRY( "GetListAsync", Ctlogging::GetListAsyncL ),
       ENTRY("AddEventSync1", Ctlogging::AddEventSync1 ),
       ENTRY("AddEventSync2", Ctlogging::AddEventSync2 ),
       ENTRY("AddEventSync3", Ctlogging::AddEventSync3 ),
       ENTRY("AddEventSync4", Ctlogging::AddEventSync4 ),
       ENTRY("AddEventSync5", Ctlogging::AddEventSync5 ),
       ENTRY("AddEventAsync1", Ctlogging::AddEventAsync1 ),
       ENTRY("AddEventAsync2", Ctlogging::AddEventAsync2 ),
       ENTRY("AddEventAsync3", Ctlogging::AddEventAsync3 ),
       ENTRY("AddEventAsync4", Ctlogging::AddEventAsync4 ),
       ENTRY("AddEventAsync5", Ctlogging::AddEventAsync5 ),
       ENTRY("DeleteEventSync", Ctlogging::DeleteEventSync ),
       ENTRY("DeleteEventAsync", Ctlogging::DeleteEventAsync ),
       ENTRY( "ConcurrentTest1", Ctlogging::ConcurrentTestL1 ),
       ENTRY( "ConcurrentTest2", Ctlogging::ConcurrentTestL2 ),
       ENTRY( "ConcurrentTest3", Ctlogging::ConcurrentTestL3 ),
       ENTRY( "ConcurrentTest4", Ctlogging::ConcurrentTestL4 ),
       ENTRY( "ConcurrentTest5", Ctlogging::ConcurrentTestL5 ),
       ENTRY( "ConcurrentTest6", Ctlogging::ConcurrentTestL6 ),
       
       
       ENTRY( "GetRecentList1", Ctlogging::GetRecentListL1 ),
       ENTRY( "GetRecentList2", Ctlogging::GetRecentListL2 ),
       ENTRY( "GetRecentList3", Ctlogging::GetRecentListL3 ),
       
       ENTRY( "GetEvent1", Ctlogging::GetEventL1 ),
       ENTRY( "GetEvent2", Ctlogging::GetEventL2 ),
       ENTRY( "GetEvent3", Ctlogging::GetEventL3 ),
       
       

        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }


//--------------------------------------------------------------------------------
//Ctlogging::AddEventTest
// Test and simple add event
//--------------------------------------------------------------------------------

TInt Ctlogging :: AddEventSync1(CStifItemParser& aItem )   
	{
	
	_LIT(KOwnEventSubject, "RandomLogEvent");
    _LIT(KOwnEventRemoteParty, "OwnContact");

	_LIT(KTLocTest ,"AddEventSync1");
	iLog->Log(KTLocTest) ;
	
	
	__UHEAP_MARK ;
	
	  CLoggingService *LogService = CLoggingService :: NewL() ;
		
      CLogsEvent* event = CLogsEvent::NewL();

	// Sets the duration of the event in seconds.
	// Randomize something between 0-299 
	
	event->SetDuration(300);
	
	TBuf<KLogMaxDirectionLength> direction;
	
	// Direction of the event is randomized

	TInt dirID = R_LOG_DIR_IN;
	TUid eventTypeID = KLogCallEventTypeUid; 
	event->SetEventType(eventTypeID);
	event->SetSubject(KOwnEventSubject);
	event->SetDirection(R_LOG_DIR_IN) ;
	TTime time;			// creation time from the device clock
	time.HomeTime();
	event->SetTime(time); 
	
	TBuf<KLogMaxNumberLength> number; // Randomize number
	number.AppendNum(7000000);
	event->SetNumber(number);
	event->SetRemoteParty(KOwnEventRemoteParty);
	
    TInt ret=LogService->AddEventL(event) ;
    
    TInt count = 0 ;
	delete event ;
	delete LogService ;
	
	__UHEAP_MARKEND ;
	
	if(ret > 0)
	{
	  return KErrNone;  
	}
	 return ret ;
	}
	
	//--------------------------------------------------------------------------------
//Ctlogging::AddEventTest
// adding an empty event
//--------------------------------------------------------------------------------

	
	
	TInt Ctlogging :: AddEventSync2(CStifItemParser& aItem )   
	{
	
	_LIT(KOwnEventSubject, "RandomLogEvent");
    _LIT(KOwnEventRemoteParty, "OwnContact");

	_LIT(KTLocTest ,"AddEventSync2");
	iLog->Log(KTLocTest) ;
	
	
	__UHEAP_MARK ;
	
	  CLoggingService *LogService = CLoggingService :: NewL() ;
		
      CLogsEvent* event = CLogsEvent::NewL();

     TInt ret = LogService->AddEventL(event) ;
     TInt count = 0 ;
	 delete event ;
	 delete LogService ;
	__UHEAP_MARKEND ;
	
	 if(ret < 0)
	 {
	    return KErrNone ;
	 }
	 
	 return ret ;
	}
	
	//--------------------------------------------------------------------------------
//Ctlogging::AddEventTest
// adding an event with out direction
//--------------------------------------------------------------------------------
	
TInt Ctlogging :: AddEventSync3(CStifItemParser& aItem )   
	{
	
	_LIT(KOwnEventSubject, "RandomLogEvent");
    _LIT(KOwnEventRemoteParty, "OwnContact");

	_LIT(KTLocTest ,"AddEventSync3");
	iLog->Log(KTLocTest) ;
	
	
	__UHEAP_MARK ;
	
	  CLoggingService *LogService = CLoggingService :: NewL() ;
		
      CLogsEvent* event = CLogsEvent::NewL();

	// Sets the duration of the event in seconds.
	// Randomize something between 0-299 
	
	event->SetDuration(300);
	
	TUid eventTypeID = KLogCallEventTypeUid; 
	event->SetEventType(eventTypeID);
	event->SetSubject(KOwnEventSubject);
	TTime time;			// creation time from the device clock
	time.HomeTime();
	event->SetTime(time); 
	
	TBuf<KLogMaxNumberLength> number; // Randomize number
	number.AppendNum(7000000);
	event->SetNumber(number);
	event->SetRemoteParty(KOwnEventRemoteParty);
	
    TInt ret=LogService->AddEventL(event) ;
    TInt count = 0 ;
	delete event ;
	delete LogService ;
	
	__UHEAP_MARKEND ;
	
	 	if(ret > 0)
	{
	  return KErrNone;  
	}
	 return ret ;
	
	}	
	
	//--------------------------------------------------------------------------------
//Ctlogging::AddEventTest
// adding an event with out subject
//--------------------------------------------------------------------------------
		
TInt Ctlogging :: AddEventSync4(CStifItemParser& aItem )   
	{
	
    _LIT(KOwnEventRemoteParty, "OwnContact");

	_LIT(KTLocTest ,"AddEventSync4");
	iLog->Log(KTLocTest) ;
	
	
	__UHEAP_MARK ;
	
	  CLoggingService *LogService = CLoggingService :: NewL() ;
		
      CLogsEvent* event = CLogsEvent::NewL();

	// Sets the duration of the event in seconds.
	// Randomize something between 0-299 
	
	event->SetDuration(300);
	
	TBuf<KLogMaxDirectionLength> direction;
	
	// Direction of the event is randomized

	TInt dirID = R_LOG_DIR_IN;
	TUid eventTypeID = KLogCallEventTypeUid; 
	event->SetEventType(eventTypeID);
	TTime time;			// creation time from the device clock
	time.HomeTime();
	event->SetTime(time); 
	
	TBuf<KLogMaxNumberLength> number; // Randomize number
	number.AppendNum(7000000);
	event->SetNumber(number);
	event->SetRemoteParty(KOwnEventRemoteParty);
	
    TInt ret=LogService->AddEventL(event) ;
    TInt count = 0 ;
	delete event ;
	delete LogService ;
	__UHEAP_MARKEND ;
	
    	if(ret > 0)
	{
	  return KErrNone;  
	}
	 return ret ;
	}
	
	//--------------------------------------------------------------------------------
//Ctlogging::AddEventTest
// adding an event with out event type
//--------------------------------------------------------------------------------
			
	TInt Ctlogging :: AddEventSync5(CStifItemParser& aItem )   
	{
	
	_LIT(KOwnEventSubject, "RandomLogEvent");
    _LIT(KOwnEventRemoteParty, "OwnContact");

	_LIT(KTLocTest ,"AddEventSync5");
	iLog->Log(KTLocTest) ;
	
	
	__UHEAP_MARK ;
	
	  CLoggingService *LogService = CLoggingService :: NewL() ;
		
      CLogsEvent* event = CLogsEvent::NewL();

	// Sets the duration of the event in seconds.
	// Randomize something between 0-299 
	
	event->SetDuration(300);
	
	TBuf<KLogMaxDirectionLength> direction;
	
	// Direction of the event is randomized

	TInt dirID = R_LOG_DIR_IN;
	event->SetSubject(KOwnEventSubject);
	TTime time;			// creation time from the device clock
	time.HomeTime();
	event->SetTime(time); 
	
	TBuf<KLogMaxNumberLength> number; // Randomize number
	number.AppendNum(7000000);
	event->SetNumber(number);
	event->SetRemoteParty(KOwnEventRemoteParty);
	
    TInt ret=LogService->AddEventL(event) ;
    TInt count = 0 ;
	delete event ;
	delete LogService ;
	__UHEAP_MARKEND ;
	
	 	if(ret < 0)
	{
	  return KErrNone;  
	}
	 return ret ;
	}
	
//--------------------------------------------------------------------------------
//Ctlogging::AddEventTest
// async.. 
//--------------------------------------------------------------------------------
	
	
		
	
TInt Ctlogging :: AddEventAsync1(CStifItemParser& aItem)
    {
    _LIT(KLogTest , "AddEventAsync1") ;
    iLog->Log(KLogTest) ;

    __UHEAP_MARK ;
     TInt ret = AddEventasync1() ;
    __UHEAP_MARKEND ;
     return ret ; 
    }
    
    
   //--------------------------------------------------------------------------------
//Ctlogging::AddEventTest
// add an empty event
//--------------------------------------------------------------------------------
	
	
		
	
TInt Ctlogging :: AddEventAsync2(CStifItemParser& aItem)
    {
    _LIT(KLogTest , "AddEventAsync2") ;
    iLog->Log(KLogTest) ;

    __UHEAP_MARK ;
     TInt ret = AddEventasync2() ;
    __UHEAP_MARKEND ;
     return ret ; 
    }
    
    
    //--------------------------------------------------------------------------------
//Ctlogging::AddEventTest
// aad an event with out direction
//--------------------------------------------------------------------------------
	
	
		
	
TInt Ctlogging :: AddEventAsync3(CStifItemParser& aItem)
    {
    _LIT(KLogTest , "AddEventAsync3") ;
    iLog->Log(KLogTest) ;

    __UHEAP_MARK ;
     TInt ret = AddEventasync3() ;
    __UHEAP_MARKEND ;
     return ret ; 
    }
    
    //--------------------------------------------------------------------------------
//Ctlogging::AddEventTest
// add an event with out subject
//--------------------------------------------------------------------------------
	
	
		
	
TInt Ctlogging :: AddEventAsync4(CStifItemParser& aItem)
    {
    _LIT(KLogTest , "AddEventAsync4") ;
    iLog->Log(KLogTest) ;

    __UHEAP_MARK ;
     TInt ret = AddEventasync4() ;
    __UHEAP_MARKEND ;
     return ret ;
    }
    
    
    //--------------------------------------------------------------------------------
//Ctlogging::AddEventTest
// add an eventn with out event type
//--------------------------------------------------------------------------------
	
		
TInt Ctlogging :: AddEventAsync5(CStifItemParser& aItem)
    {
    _LIT(KLogTest , "AddEventAsync5") ;
    iLog->Log(KLogTest) ;

    __UHEAP_MARK ;
     TInt ret = AddEventasync5() ;
    __UHEAP_MARKEND ;
     return ret ; 
    }
//-----------------------------------------------------------------------------
// Simple GetListTest
//-----------------------------------------------------------------------------

TInt Ctlogging :: GetListSimpleL(CStifItemParser& aItem )  
	{
	 _LIT(KLogTest , "GetListSimple") ;
	 iLog->Log(KLogTest) ;
	 
	 __UHEAP_MARK ;
	 CLoggingService *LogService = CLoggingService :: NewL() ;
	 
	 CLogsFilter   *LogFilter = CLogsFilter :: NewL() ;
	 
	 
	 LogFilter->SetRequestType(EReadEvents) ;
	 
	 CLogIter *iter  = LogService->GetListL(LogFilter) ;
	 
	 TInt count = 0 ;
	 CLogsEvent *aEvent ;
	 
	 
	 while(aEvent = iter->NextL())
	 	{
	 	 delete aEvent ;
	 	}
	 
	 
	 delete iter ;
	 delete LogFilter ;
	 delete LogService ;	
	 __UHEAP_MARKEND ;
	 return KErrNone ;
	}
	
//-----------------------------------------------------------------
// GetListAsync Test
//----------------------------------------------------------------

TInt Ctlogging :: GetListAsyncL(CStifItemParser& aItem)
{
	_LIT(KLogTest , "GetListAsyncTest") ;
	iLog->Log(KLogTest) ;
	
	__UHEAP_MARK ;
	 TInt ret = getlistasyncL1() ;
	__UHEAP_MARKEND ;
	 return ret ; 
	 
	
}

TInt Ctlogging :: DeleteEventSync(CStifItemParser& aItem )   
	{
	

	_LIT(KTLocTest ,"DeleteEventSync");
	iLog->Log(KTLocTest) ;
	
	__UHEAP_MARK ;
	
	  TInt ret= DeleteEventsync();
	__UHEAP_MARKEND ;
	   return ret;	 
	}
	
	
TInt Ctlogging :: DeleteEventAsync(CStifItemParser& aItem )   
	{
	

	_LIT(KTLocTest ,"DeleteEventAsync");
	iLog->Log(KTLocTest) ;
	
	__UHEAP_MARK ;
	
	  TInt ret= DeleteEventasync();
	__UHEAP_MARKEND ;
	   return ret;
	}
//-------------------------------------------------------------------
//Concurrent Call test (Add and GetList)
//-------------------------------------------------------------------

TInt Ctlogging :: ConcurrentTestL1(CStifItemParser& aItem)
	{
	 __UHEAP_MARK ;
	  TInt ret = concurrenttest1() ;
	  __UHEAP_MARKEND ;
	  return ret ;
	  
	 
	}
	

//-------------------------------------------------------------------
//Concurrent Call test (GetList and requestNotification)
//-------------------------------------------------------------------

TInt Ctlogging :: ConcurrentTestL2(CStifItemParser& aItem)
	{
	 __UHEAP_MARK ;
	  TInt ret = concurrenttest2() ;
	  __UHEAP_MARKEND ;
	  return ret ;
	  
	 
	}	
	
//-------------------------------------------------------------------
//Concurrent Call test (GetList and requestNotification)
//-------------------------------------------------------------------

TInt Ctlogging :: ConcurrentTestL3(CStifItemParser& aItem)
	{
	 __UHEAP_MARK ;
	  TInt ret = concurrenttest3() ;
	  __UHEAP_MARKEND ;
	  return ret ;
	  
	 
	}	
		
//-------------------------------------------------------------------
//Concurrent Call test (GetList and getlist)
//-------------------------------------------------------------------

TInt Ctlogging :: ConcurrentTestL4(CStifItemParser& aItem)
	{
	 __UHEAP_MARK ;
	  TInt ret = concurrenttest4() ;
	  __UHEAP_MARKEND ;
	  return ret ;
	  
	 
	}
	
//-------------------------------------------------------------------
//Concurrent Call test (Add and Add)
//-------------------------------------------------------------------

TInt Ctlogging :: ConcurrentTestL5(CStifItemParser& aItem)
	{
	 __UHEAP_MARK ;
	  TInt ret = concurrenttest5() ;
	  __UHEAP_MARKEND ;
	  return ret ;
	  
	 
	}	
	
//-------------------------------------------------------------------
//Concurrent Call test (Delet and Delete)
//-------------------------------------------------------------------

TInt Ctlogging :: ConcurrentTestL6(CStifItemParser& aItem)
	{
	 __UHEAP_MARK ;
	  TInt ret = concurrenttest6() ;
	  __UHEAP_MARKEND ;
	  return ret ;
	  
	 
	}			
//-------------------------------------------------------------------
//GetRecentList Test synchronous
//-------------------------------------------------------------------

TInt Ctlogging :: GetRecentListL1(CStifItemParser& aItem)
	{
	 __UHEAP_MARK ;
	  TInt ret = getRecentList1() ;
	  __UHEAP_MARKEND ;
	  return ret ;
	  
	 
	}	
	

//-------------------------------------------------------------------
//GetList test asynchronous test
//-------------------------------------------------------------------

TInt Ctlogging :: GetRecentListL2(CStifItemParser& aItem)
	{
	 __UHEAP_MARK ;
	  TInt ret = getRecentList2() ;
	  __UHEAP_MARKEND ;
	  return ret ;
	  
	 
	}
	
//-------------------------------------------------------------------
//GetEvent2 , test for getevent based on event id 
// this is a synchronous call test
//-------------------------------------------------------------------

TInt Ctlogging :: GetEventL1(CStifItemParser& aItem)
	{
	 __UHEAP_MARK ;
	  TInt ret = getEvent1() ;
	  __UHEAP_MARKEND ;
	  return ret ;
	  
	 
	}	
	
//---------------------------------------------------------------------
// GetEvent2 , test for getevent based on event id 
// this is a asynchronous call test
//---------------------------------------------------------------------


TInt Ctlogging :: GetEventL2(CStifItemParser& aItem)
	{
	 __UHEAP_MARK ;
	  TInt ret = getEvent2() ;
	  __UHEAP_MARKEND ;
	  return ret ;
	  
	 
	}
	
//---------------------------------------------------------------------
// GetEvent3, test for getevent, with invalid event id 
// this is a asynchronous call test
//---------------------------------------------------------------------


TInt Ctlogging :: GetEventL3(CStifItemParser& aItem)
	{
	 __UHEAP_MARK ;
	  TInt ret = getEvent3() ;
	  __UHEAP_MARKEND ;
	  return ret ;
	  
	 
	}
	
//---------------------------------------------------------------------
// GetEvent4, test for getrecentevent, with an empty filter
//---------------------------------------------------------------------


TInt Ctlogging :: GetRecentListL3(CStifItemParser& aItem)
	{
	 __UHEAP_MARK ;
	  TInt ret = getRecentlist3() ;
	  __UHEAP_MARKEND ;
	  return ret ;
	  
	 
	}		
