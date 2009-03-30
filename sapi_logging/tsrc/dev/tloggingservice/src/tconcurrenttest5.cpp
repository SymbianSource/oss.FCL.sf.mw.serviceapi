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
#include <Stiftestinterface.h>
#include <logcli.h>
#include <logwrap.h>

#include "loggingasyncservice.h"
#include "loggingservice.h"
#include "loggingfilter.h"

#include "tlogging.h"
#include "tlogcallback.h"
#include "loggingevent.h"


//------------------------------------------------------------------
//Concurrenttest5, core class test for concurrent async calls
// AddEvent and AddEvent async test
//------------------------------------------------------------------

TInt concurrenttest5(void)
	{
//	TInt ret ;
//	TInt flag  ;
	
	_LIT(KOwnEventSubject, "RandomLogEvent");
	_LIT(KOwnEventRemoteParty, "OwnContact");
	
	
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
	TTime time;			// creation time from the device clock
	time.HomeTime();
	event->SetTime(time); 
	
	TBuf<KLogMaxNumberLength> number; // Randomize number
	number.AppendNum(7000000);
	event->SetNumber(number);
	event->SetRemoteParty(KOwnEventRemoteParty);
	MLogCallback Mycb ;
	TLogId ret = LogService->AddEventL(1 , event , &Mycb) ;
	
	delete event ;
	delete LogService;
    return KErrNone ;

	 
	}
	