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
//getRecentList , test with empty filter
//------------------------------------------------------------------

TInt getRecentList4(void)
	{
	 CLoggingService *LogService = CLoggingService :: NewL() ;
	 CLogsFilter *filter = CLogsFilter :: NewL() ;
	 MLogCallback MyCb ;
	
	 //TBool ret = LogService->ReadRecentEventsL(2, &MyCb , KLogNullRecentList , filter) ;
	 
	
	 TInt ret = 0 ;
	 if(ret != KErrNone)
	 	{
	 	delete LogService ;
	 	delete filter ;
	 	return ret ;
	 	}
	 
	 MyCb.Start() ;	
	 	
	 return ret ; 	
	}
	