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

#include "tlogging.h"
#include "tlogcallback.h"
#include "loggingevent.h"

//------------------------------------------------------------
// Get an event details on the eventid
//-------------------------------------------------------------

TInt getEvent2(void) 
{
	_LIT(KOwnEventSubject, "RandomLogEvent");
	_LIT(KOwnEventRemoteParty, "OwnContact");
	CLoggingService *LogService = CLoggingService :: NewL() ;
	CLogsFilter *filter = CLogsFilter :: NewL() ;


    filter->SetRequestType(EGetEvent) ;
    
	CLogsEvent* event = CLogsEvent::NewL();

	// Sets the duration of the event in seconds.
	// Randomize something between 0-299 

	event->SetDuration(301);

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
	number.AppendNum(7000008);
	event->SetNumber(number);
	event->SetRemoteParty(KOwnEventRemoteParty);
	TLogId id= LogService->AddEventL(event) ;

	CLogsEvent *updatedEvent   = CLogsEvent :: NewL() ;
	updatedEvent->SetId(id) ;
	
	filter->SetEventL(updatedEvent) ;
	 
	MLogCallback Mycb ;
	TInt ret = LogService->GetListL(1 ,filter , &Mycb) ;
	Mycb.Start() ;

    delete filter ;
    delete updatedEvent ;
	delete event ;
	delete LogService ;
	return ret ;
}
