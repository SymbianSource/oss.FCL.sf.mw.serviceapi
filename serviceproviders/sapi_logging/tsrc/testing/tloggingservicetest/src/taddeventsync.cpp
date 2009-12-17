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
#include "loggingsyncservice.h"
#include "loggingfilter.h"
#include "loggingservice.h"
#include "loggingevent.h"
#include "tlogcallback.h"
 

 
#include "logiter.h"

 




 //addevents1()
 
  
 TInt  addevents1(void )
    {
    
	 CLoggingService *iLoggingService = CLoggingService::NewL();
     CLogsEvent  *iLogsEvent = CLogsEvent::NewL();
     MLogCallback icallback;
        
    
    TInt error1 = iLoggingService->AddEventL(iLogsEvent);
    iLogsEvent->SetDuration(300);
    TRAPD(ret2, iLoggingService->AddEventL(iLogsEvent));
    TUid tuid  = KLogCallEventTypeUid;
    iLogsEvent->SetEventType(tuid);
    TInt error2= iLoggingService->AddEventL(iLogsEvent);
    iLogsEvent->SetSubject(_L("Testing"));
    TRAPD(ret4, iLoggingService->AddEventL(iLogsEvent));
    TTime itime;
    itime.HomeTime();
    iLogsEvent->SetTime(itime);
    TRAPD(ret5, iLoggingService->AddEventL(iLogsEvent));
     
    TBuf<KLogMaxNumberLength> number; // Randomize number
	number.AppendNum(9886665142);
	iLogsEvent->SetNumber(number);
	iLogsEvent->SetDirection(R_LOG_DIR_IN);
	iLogsEvent->SetRemoteParty(_L("contact"));
	
	TRAPD(ret6, iLoggingService->AddEventL(iLogsEvent));
    
   	
   	
   //	TRAPD(ret7, iLoggingService->AddEventL(iLogsEvent));
   	
    TInt iint = 0;
   	
   	
    //TLogId ret8= iLoggingService->AddEventL(iLogsEvent);
   // iLoggingService->DeleteEventL(1 , ret8 ,&icallback);
   // icallback.Start() ;
    
    CLogsEvent *DeletedEvent = CLogsEvent :: NewL() ;
   // DeletedEvent->SetId(ret8) ;

     delete iLogsEvent;
     delete iLoggingService;
     delete DeletedEvent;   	
       	
   		if(error1<0)
   		if(error2>0)
       	if(ret2==0)
       	if(ret4==0)
      	if(ret5==0)
      	if(ret6==0)
	//	if(ret7==0)
	//	if(ret8>0)
       

    return KErrNone;
    return KErrGeneral;
    
    }
    
   






 //addevents2()
 
  
 TInt  addevents2(void )
    {
    
	CLoggingService *iLoggingService = CLoggingService::NewL();
    CLogsEvent  *iLogsEvent = CLogsEvent::NewL();
     MLogCallback icallback;
const TUid KLogtestEventTypeUid = {0x1000550C};
   
    iLogsEvent->SetDuration(300);
    TUid tuid  = KLogtestEventTypeUid;
    // iLogsEvent->SetEventType(tuid);
    iLogsEvent->SetSubject(_L("Testing"));
    TTime itime;
    itime.HomeTime();
    iLogsEvent->SetTime(itime);
    
    TBuf<KLogMaxNumberLength> number; // Randomize number
	number.AppendNum(919886665142);
	iLogsEvent->SetNumber(number);
	     
   	iLogsEvent->SetRemoteParty(_L("contact"));
   	iLogsEvent->SetDirection(1);
   
    TInt error2= iLoggingService->AddEventL(iLogsEvent);

//	TUid tuid1 = -1;
 	
 //	 TInt error3 = iLoggingService->AddEventL(iLogsEvent,tuid1);
	
		delete iLoggingService;
		delete iLogsEvent;
       
   		if(error2<0)
    

    return KErrNone;
    return KErrGeneral;
    
    }
    
    
    
    
    
     
    
    
    
     
