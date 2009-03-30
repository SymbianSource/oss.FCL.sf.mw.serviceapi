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
//Concurrenttest1, core class for concurrent async calls
// GetList and GetList async test
//------------------------------------------------------------------

TInt concurrenttest3(void)
	{
	 TInt ret ;
	 TInt flag  ;
	 
	 
	 CLoggingService *LogService = CLoggingService :: NewL() ;
	 CLogsFilter  *filter = CLogsFilter :: NewL() ;
	 MLogCallback MyCb ;
	 //CLogsEvent *event = CLogsEvent :: NewL() ;
	 CLogsFilter  *filter1 = CLogsFilter :: NewL() ;
	 
	  filter->SetRequestType(EReadEvents) ;
	 
	  LogService->GetListL(1 , filter , &MyCb) ;
	  
	  filter1->SetRequestType(EReadEvents) ;
	  
	  ret = LogService->GetListL(2, filter , &MyCb) ;
	 
	 
	 if(ret == KErrServerBusy)
	 	{
	 	 flag = KErrNone ;
	 	}
	 else
	 	{
	 		flag = ret ;
	 	}	
	 
	 
	 delete filter ;
	 delete filter1 ;
	 delete LogService ;
	 return flag ;
	
	 
	 
	}
	