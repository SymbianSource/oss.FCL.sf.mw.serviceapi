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



 
#include "logiter.h"


 
	_LIT(KOwnEventSubject, "RandomLogiLogsEvent");
    _LIT(KOwnEventRemoteParty, "OwnContact");


 //getlist1()
 
  
 TInt  getlist1(void )
    {
    
		CLoggingService *iLoggingService = CLoggingService :: NewL() ;
	   MLogCallback icallback ;
	   
	   CLogsFilter *iLogsFilter = CLogsFilter :: NewL() ;
	   
 
	   
	  iLogsFilter->SetRequestType(EReadEvents) ;
	   
	  iLoggingService->GetListL(1 , iLogsFilter , &icallback) ;
	   
	   icallback.Start() ; 
	 
	    delete iLogsFilter ;
	    delete iLoggingService ;
  	 return KErrNone;
     }
    
    
    
     //getlist2()
 
  
 TInt  getlist2(void )
    {
    
		CLoggingService *iLoggingService = CLoggingService :: NewL() ;
	  	 MLogCallback icallback ;
	   
	   	CLogsFilter *iLogsFilter = CLogsFilter :: NewL() ;
	       CLogsEvent* iLogsEvent = CLogsEvent::NewL();

	   
	 		 iLogsFilter->SetRequestType(EReadEvents) ;
	 		  //iLoggingService->SetFilterL(iLogsFilter);

TUid tuid = KLogCallEventTypeUid; 
	iLogsEvent->SetEventType(tuid);

//	TLogId id= iLoggingService->AddEventL(iLogsEvent) ;

 //	iLogsEvent->SetId(id) ;
	
//	CLogsFilter *filter = CLogsFilter :: NewL() ;
	
//	filter->SetRequestType(EGetEvent)  ;
	iLogsFilter->SetEventL(iLogsEvent) ;
	  // CLogIter *iter;
	   
 	 		 iLoggingService->GetListL(1 ,iLogsFilter , &icallback) ;
	   
 	 		 	 		
	   		icallback.Start() ; 
	   		//iter->DoCancel();
	 //delete iter;
	   delete iLogsEvent;
	    delete iLogsFilter ;
	    delete iLoggingService ;
  	 return KErrNone;
     }
    
    
   
       
 
	
	
	

        //getlist3()
 
  
 TInt  getlist4(void )
    {
    
	CLoggingService *iLoggingService = CLoggingService :: NewL() ;
	
	TUint  iTransid = 0;
//	iLoggingService->CancelServiceL(iTransid);
    delete iLoggingService;
    return KErrNone;
    
    
    }
	   
	
		
	
	
	
	 TInt  getevent1(void )
    {	
    
	
	CLoggingService *iLoggingService = CLoggingService :: NewL() ;
 
	CLogsEvent* iLogsEvent = CLogsEvent::NewL();
//CLogSyncService *iLoggingsyncservice = CLogSyncService::NewL();
  
	iLogsEvent->SetDuration(301);

	TBuf<KLogMaxDirectionLength> direction;

 
 
	TUid eventTypeID = KLogCallEventTypeUid; 
	iLogsEvent->SetEventType(eventTypeID);
	iLogsEvent->SetSubject(KOwnEventSubject);
	TTime time;			// creation time from the device clock
	time.HomeTime();
	iLogsEvent->SetTime(time); 

	TBuf<KLogMaxNumberLength> number; // Randomize number
	number.AppendNum(7000008);
	iLogsEvent->SetNumber(number);
	iLogsEvent->SetRemoteParty(KOwnEventRemoteParty);

	TLogId id= iLoggingService->AddEventL(iLogsEvent) ;

 	iLogsEvent->SetId(id) ;
	
	CLogsFilter *filter = CLogsFilter :: NewL() ;
	
	filter->SetRequestType(EGetEvent)  ;
	filter->SetEventL(iLogsEvent) ;
	
	
	CLogIter *iter;// = CLogIter::NewL();
	iter = iLoggingService->GetListL(filter) ;
	CLogsEvent *iterevents ;
	
	while (iterevents = iter->NextL())
		{
		iLoggingService->DeleteEventL(iterevents->Id()) ;
		    delete iterevents ;
		}
	
	iter->DoCancel();
 	delete iter ;

    delete filter ; 
	delete iLogsEvent ;
	delete iLoggingService ;
	return KErrNone ;
	}
	
	
	
	
	
	
	
	
	
	 //getlist1()
 
  
 TInt  getevent2(void )
    {
    
		CLoggingService *iLoggingService = CLoggingService :: NewL() ;
	   MLogCallback icallback ;
	   
	   CLogsFilter *iLogsFilter = CLogsFilter :: NewL() ;
	   	CLogsEvent* iLogsEvent = CLogsEvent::NewL();

  	 TUid eventTypeID = KLogCallEventTypeUid; 
	iLogsEvent->SetEventType(eventTypeID);
	   iLogsEvent->SetStatus(R_LOG_DEL_NONE);
	  iLogsFilter->SetRequestType(EGetEvent) ;
 	   	   iLogsFilter->SetStatus(R_LOG_DEL_NONE);

 	   	TLogId id= iLoggingService->AddEventL(iLogsEvent) ;

 	iLogsEvent->SetId(id) ;
 	   iLogsFilter->SetEventL(iLogsEvent) ;
	   //if(iLogsEvent)
	  iLoggingService->GetListL(1 , iLogsFilter , &icallback) ;
	   
	   icallback.Start() ; 
	 
		delete iLogsEvent;
	    delete iLogsFilter ;
	    delete iLoggingService ;
  	 return KErrNone;
     }
 
 
 TInt  getevent3(void )
	    {	
	    
		
		CLoggingService *iLoggingService = CLoggingService :: NewL() ;
	 
		CLogsEvent* iLogsEvent = CLogsEvent::NewL();
	//CLogSyncService *iLoggingsyncservice = CLogSyncService::NewL();
	  
		iLogsEvent->SetDuration(301);

		TBuf<KLogMaxDirectionLength> direction;

	 
	 
		TUid eventTypeID = KLogCallEventTypeUid; 
		iLogsEvent->SetEventType(eventTypeID);
		iLogsEvent->SetSubject(KOwnEventSubject);
		TTime time;			// creation time from the device clock
		time.HomeTime();
		iLogsEvent->SetTime(time); 

		TBuf<KLogMaxNumberLength> number; // Randomize number
		number.AppendNum(7000008);
		iLogsEvent->SetNumber(number);
		iLogsEvent->SetRemoteParty(KOwnEventRemoteParty);

		TLogId id= iLoggingService->AddEventL(iLogsEvent) ;

	 	iLogsEvent->SetId(id) ;
		
		CLogsFilter *filter = CLogsFilter :: NewL() ;
		
		filter->SetRequestType(EReadEvents)  ;
		filter->SetEventL(iLogsEvent) ;
		
		
		CLogIter *iter;// = CLogIter::NewL();
		iter = iLoggingService->GetListL(filter) ;
		//CLogsEvent *iterevents ;
		
	//	while (iterevents = iter->NextL())
		//	{
			//iLoggingService->DeleteEventL(iterevents->Id()) ;
			   // delete iterevents ;
			//}
		
		//iter->DoCancel();
	 	delete iter ;

	    delete filter ; 
		delete iLogsEvent ;
		delete iLoggingService ;
		return KErrNone ;
		}
		
		
 

 TInt  getevent4(void )
	    {	
	    
		
		CLoggingService *iLoggingService = CLoggingService :: NewL() ;
	 
		CLogsEvent* iLogsEvent = CLogsEvent::NewL();
	//CLogSyncService *iLoggingsyncservice = CLogSyncService::NewL();
	  
		iLogsEvent->SetDuration(301);

		TBuf<KLogMaxDirectionLength> direction;

	 
	 
		TUid eventTypeID = KLogCallEventTypeUid; 
		iLogsEvent->SetEventType(eventTypeID);
		iLogsEvent->SetSubject(KOwnEventSubject);
		TTime time;			// creation time from the device clock
		time.HomeTime();
		iLogsEvent->SetTime(time); 

		TBuf<KLogMaxNumberLength> number; // Randomize number
		number.AppendNum(7000008);
		iLogsEvent->SetNumber(number);
		iLogsEvent->SetRemoteParty(KOwnEventRemoteParty);

		TLogId id= iLoggingService->AddEventL(iLogsEvent) ;

	 	iLogsEvent->SetId(id) ;
		
		CLogsFilter *filter = CLogsFilter :: NewL() ;
		
		filter->SetRequestType(EGetRecent)  ;
		filter->SetRecentList(KLogNullRecentList) ;
		filter->SetEventL(iLogsEvent) ;
		
		
		CLogIter *iter;// = CLogIter::NewL();
		iter = iLoggingService->GetListL(filter) ;
		CLogsEvent *iterevents = CLogsEvent::NewL() ;
		
		//while (iterevents = iter->NextL())
			//{
			//iLoggingService->DeleteEventL(iterevents->Id()) ;
			    delete iterevents ;
			//}
		
		iter->DoCancel();
	 	delete iter ;

	    delete filter ; 
		delete iLogsEvent ;
		delete iLoggingService ;
		return KErrNone ;
		}
		
		
     
      
	
	
     
 TInt  getevent5(void )
	    {	
	    
		
		CLoggingService *iLoggingService = CLoggingService :: NewL() ;
	 
		CLogsEvent* iLogsEvent = CLogsEvent::NewL();
	//CLogSyncService *iLoggingsyncservice = CLogSyncService::NewL();
	  
		iLogsEvent->SetDuration(301);

		TBuf<KLogMaxDirectionLength> direction;

	 
	 
		TUid eventTypeID = KLogCallEventTypeUid; 
		iLogsEvent->SetEventType(eventTypeID);
		iLogsEvent->SetSubject(KOwnEventSubject);
		TTime time;			// creation time from the device clock
		time.HomeTime();
		iLogsEvent->SetTime(time); 

		TBuf<KLogMaxNumberLength> number; // Randomize number
		number.AppendNum(7000008);
		iLogsEvent->SetNumber(number);
		iLogsEvent->SetRemoteParty(KOwnEventRemoteParty);

		TLogId id= iLoggingService->AddEventL(iLogsEvent) ;

	 	iLogsEvent->SetId(id) ;
		
		CLogsFilter *filter = CLogsFilter :: NewL() ;
		
		filter->SetRequestType(ENotification)  ;
		filter->SetEventL(iLogsEvent) ;
		
		
		//CLogIter *iter;// = CLogIter::NewL();
		//iter = iLoggingService->GetListL(filter) ;
		TRAPD(iter,iLoggingService->GetListL(filter));			
		
		//iter->DoCancel();
	 	//delete iter ;

	    delete filter ; 
		delete iLogsEvent ;
		delete iLoggingService ;
		if(iter == -6)
		return KErrNone ;
		return iter;
		}
		
     