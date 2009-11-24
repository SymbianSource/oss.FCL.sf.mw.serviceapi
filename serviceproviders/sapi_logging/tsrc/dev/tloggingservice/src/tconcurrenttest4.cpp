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
//Concurrenttest4, core class test for concurrent async calls
// RequestNotification and RequestNotification async test
//------------------------------------------------------------------

TInt concurrenttest4(void)
	{
	TInt ret ;
	TInt flag  ;

	CLoggingService *LogService = CLoggingService :: NewL() ;
	CLogsFilter  *filter = CLogsFilter :: NewL() ;
	MLogCallback MyCb ;
	CLogsEvent *event = CLogsEvent :: NewL() ;

	LogService->NotifyUpdatesL(2 ,900 , &MyCb) ;

	ret = LogService->NotifyUpdatesL(3 ,900 , &MyCb) ;



	if(ret == KErrServerBusy)
		{
		 flag = KErrNone ;
		}
	else
		{
		flag = ret ;
		}	


	delete filter ;
	delete event ;
	delete LogService ;

	return KErrNone ;

	 
	}
	