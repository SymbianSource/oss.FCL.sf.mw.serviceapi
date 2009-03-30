/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  
*
*/

#include <e32svr.h>
#include "tloggingservicetest.h"
#include <logcli.h>
#include <logwrap.h>

#include "loggingasyncservice.h"
#include "loggingsyncservice.h"
#include "loggingfilter.h"
#include "loggingservice.h"
#include "loggingevent.h"
#include "tlogcallback.h"

#include "logobserver.h"

 
#include "logiter.h"



//-------------------------------------------------------------
// Generic call back function implementation, used by logging 
// component
//--------------------------------------------------------------

static TInt count = 0 ;

//--------------------------------------------------------------
// Default constructor
//--------------------------------------------------------------

MLogCallback :: MLogCallback()
	{
	 iScheduler = new CActiveSchedulerWait() ;
	 
	}

//----------------------------------------------------------------
// Default destructor
//----------------------------------------------------------------

MLogCallback :: ~MLogCallback()
	{
 	delete iScheduler ;
	}
	
//-----------------------------------------------------------------
//Starts the async wait loop
//-----------------------------------------------------------------


void MLogCallback :: Start()
	{
	 iScheduler->Start() ;
	}
	
void MLogCallback :: HandleNotifyL(TUint aTransid ,TUint aStatus , CLogIter *iter )
{
 	++count ;
 	 
    
    delete iter ;
	if(count > 0)
		{
		 iScheduler->AsyncStop() ;
		}
	
	
}
 


void MLogCallback :: CancelNotifyL( TUint aTransid ) 
{
 	
	
}







 //addevents1()
 
  
 TInt  addeventas1(void )
    {
    CLogObserver *iLogObserver ;//= CLogObserver::NewLC();
	CLoggingService *iLoggingService = CLoggingService::NewL();
    CLogsEvent  *iLogsEvent = CLogsEvent::NewL();
     
          
    
     TUint iTransid = 1;
     MLogCallback icallback;
     //-ve testing 
     
      
     TUid tuid  = KLogCallEventTypeUid;
    
   
    iLogsEvent->SetDuration(300);
    iLogsEvent->SetEventType(tuid);
    	iLogsEvent->SetDirection(R_LOG_DIR_IN);
    
    
   TRAPD(ret1, iLoggingService->AddEventL(iTransid,iLogsEvent,&icallback));
    icallback.Start();
    
    
     delete iLogsEvent;
     delete iLoggingService;
       
    	if(ret1 ==0)
        
     return KErrNone;
    return KErrGeneral;

    }
    
    
    
     //addevents1()
 
  
 TInt  addeventas2(void )
    {
    
	CLoggingService *iLoggingService = CLoggingService::NewL();
    CLogsEvent  *iLogsEvent = CLogsEvent::NewL();
    MLogCallback icallback;
     
     TUint iTransid = 1;
     TUid tuid  = KLogCallEventTypeUid;
     
       
    iLogsEvent->SetDuration(300);
    iLogsEvent->SetEventType(tuid);
     	iLogsEvent->SetDirection(R_LOG_DIR_IN);
     
   	TRAPD(error,iLoggingService->AddEventL(iTransid,iLogsEvent,&icallback));
      
      
      iLoggingService->NotifyUpdatesL(iTransid,100,&icallback);
       
     delete iLogsEvent;
     delete iLoggingService;
               
      if(error==0)
 
    return KErrNone;
    return KErrGeneral;

    }
    
    
    
    
    TInt isbusy(void)
    {
    
    TInt ret ;
	 TInt flag  ;
	 
	 
	 CLoggingService *LogService = CLoggingService :: NewL() ;
	 CLogsFilter  *filter = CLogsFilter :: NewL() ;
	 MLogCallback MyCb ;
	 CLogsEvent *event = CLogsEvent :: NewL() ;
	 filter->SetRequestType(EReadEvents) ;
	 LogService->GetListL(1 , filter , &MyCb) ;
	 
	  ret = LogService->GetListL(2, filter , &MyCb) ;
    
    
    //	if(LogService->IsBusy())
    delete filter ;
	 delete event ;
	 delete LogService ;
	 return 0;
    
    }
     
    
    
    
     