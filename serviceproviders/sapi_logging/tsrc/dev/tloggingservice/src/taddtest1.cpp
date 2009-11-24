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
#include "loggingevent.h"

#include "tlogging.h"
#include "tlogcallback.h"


_LIT(KOwnEventSubject, "RandomLogEvent");
_LIT(KOwnEventRemoteParty, "OwnContact");

TInt AddEventasync2(void)
	{
	   CLoggingService *LogService = CLoggingService :: NewL() ;
	   CLogsEvent* event = CLogsEvent::NewL();
	   MLogCallback MyCb ;
	
      LogService->AddEventL(1 , event , &MyCb) ;
	   
	  MyCb.Start() ;
	  delete event ;
	  delete LogService ;
	  
	 
	  
	  return KErrNone ;
	}

