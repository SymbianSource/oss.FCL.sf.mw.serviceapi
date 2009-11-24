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
#include <e32std.h>
#include <StifParser.h>
#include <StifTestInterface.h>
#include <logcli.h>
#include <logwrap.h>

#include "loggingasyncservice.h"
#include "loggingservice.h"
#include "loggingfilter.h"

#include "tlogging.h"
#include "tlogcallback.h"
#include "loggingevent.h"


//------------------------------------------------------------------
//getRecentList , synchronous test
//------------------------------------------------------------------

TInt getRecentList2(void)
	{
	 CLoggingService *LogService = CLoggingService :: NewL() ;
	 CLogsFilter *filter = CLogsFilter :: NewL() ;
	 CLogsEvent* event = CLogsEvent::NewL();
	 MLogCallback MyCb ;
	 
	 TBuf<KLogMaxDirectionLength> direction;
	
	// Direction of the event is randomized

	TInt dirID = R_LOG_DIR_IN;
	TUid eventTypeID = KLogCallEventTypeUid; 
	event->SetEventType(eventTypeID);
    event->SetDirection(R_LOG_DIR_IN) ;
	TTime time;			// creation time from the device clock
	time.HomeTime();
	event->SetTime(time); 
	
	TBuf<KLogMaxNumberLength> number; // Randomize number
	number.AppendNum(7000000);
	event->SetNumber(number);

	
    TInt ret=LogService->AddEventL(event) ;
	 
	
	  filter->SetRecentList(KLogNullRecentList) ;
	  
	  filter->SetRequestType(EGetRecent) ;
	 
	  LogService->GetListL(1, filter , &MyCb) ;
	 
      MyCb.Start() ;
      	
	 delete event ;
	 delete filter ;
	 delete LogService ;
	 	
	 return KErrNone ; 	
	}
	