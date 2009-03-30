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
#include "loggingevent.h"
#include "logiter.h"
#include "tlogging.h"
#include "tlogcallback.h"



//-------------------------------------------------------------
// Generic call back function implementation, used by logging 
// component
//--------------------------------------------------------------

static TInt count = 0 ;

//--------------------------------------------------------------
// Default constructor
//--------------------------------------------------------------

MLogCallback :: MLogCallback()
	{
	 iScheduler = new CActiveSchedulerWait() ;
	 
	}

//----------------------------------------------------------------
// Default destructor
//----------------------------------------------------------------

MLogCallback :: ~MLogCallback()
	{
	delete iScheduler ;
	}
	
//-----------------------------------------------------------------
//Starts the async wait loop
//-----------------------------------------------------------------


void MLogCallback :: Start()
	{
	 iScheduler->Start() ;
	}
	
void MLogCallback :: HandleNotifyL(TUint aTransid ,TUint aStatus , CLogIter *iter )
{
 	++count ;
    
    delete iter ;
	if(count > 0)
		{
		 iScheduler->AsyncStop() ;
		}
	
	
}

void MLogCallback :: CancelNotifyL( TUint aTransid ) 
{
 	
	
}

