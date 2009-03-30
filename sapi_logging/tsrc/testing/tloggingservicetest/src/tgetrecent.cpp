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

  
     
      TInt  getrecent1(void )
    {
    
     
	
	 CLoggingService *iLoggingService = CLoggingService :: NewL() ;
	 CLogsFilter *iLogsFilter = CLogsFilter :: NewL() ;
	   
	
	 MLogCallback iCallback ;
	 iLogsFilter->SetDirection(R_LOG_DIR_IN);
     iLogsFilter->SetRequestType(EGetRecent) ;
     iLogsFilter->SetRecentList(KLogNullRecentList) ;
	 
	 TBool ret = iLoggingService->GetListL(2,  iLogsFilter , &iCallback) ;
	 
	
	 
	 if(ret != KErrNone)
	 	{
	 	delete iLoggingService ;
	 	delete iLogsFilter ;
	 	return ret ;
	 	}
	 
	 
	 iCallback.Start() ;	
	 delete iLogsFilter ;
	 delete iLoggingService ;
	 
	 	
	 return ret ; 
 
	 
	 
	  
	}
	
	
	
	
	 TInt  getrecent2(void )
	{
	
     
     CLoggingService *iLoggingService = CLoggingService :: NewL() ;
	   MLogCallback icallback ;
	       CLogsEvent  *iLogsEvent = CLogsEvent::NewL();

	   CLogsFilter *iLogsFilter = CLogsFilter :: NewL() ;
	 const TUid KLogtestEventTypeUid = {0x1000550C};
  
   iLogsEvent->SetDuration(300);
    TUid tuid  = KLogtestEventTypeUid;
 
 iLoggingService->AddEventL(iLogsEvent);
	   
	  iLogsFilter->SetRequestType(EGetRecent) ;
	   iLogsFilter->SetRecentList(KLogNullRecentList) ;
	   
	  TBool ret = iLoggingService->GetListL(1 , iLogsFilter , &icallback) ;
	  // TInt count = 0;
	   icallback.Start() ; 
	 
	    delete iLogsEvent;
	    delete iLogsFilter ;
	    delete iLoggingService ;
  	 return KErrNone;
  	 
  	 
  	 
	}
     