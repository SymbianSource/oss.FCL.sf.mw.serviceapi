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

//------------------------------------------------------------
// Get an event details on the eventid
//-------------------------------------------------------------

TInt getEvent3(void) 
{
	_LIT(KOwnEventSubject, "RandomLogEvent");
	_LIT(KOwnEventRemoteParty, "OwnContact");
	CLoggingService *LogService = CLoggingService :: NewL() ;
	CLogsFilter *filter = CLogsFilter :: NewL() ;
    filter->SetRequestType(EGetEvent) ;
    CLogsEvent *updatedEvent   = CLogsEvent :: NewL() ;
	updatedEvent->SetId(785) ;
	 filter->SetEventL(updatedEvent) ;
 	MLogCallback Mycb ;
   
	TInt ret = LogService->GetListL(1 , filter , &Mycb) ;
	Mycb.Start() ;
    
    if(ret == KErrArgument)
    	{
    	ret = KErrNone ;
    	}


	delete updatedEvent ;
	delete LogService ;
	delete filter;
	return ret ;
}
