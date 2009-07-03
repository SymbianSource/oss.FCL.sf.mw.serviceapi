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
#include <LiwServiceHandler.h>
#include <LiwCommon.h>

#include "tprovidertest.h"

#include "tprovidercallback.h"
#include "liwlogiter.h"
 _LIT8(KLogIter , "Iterator") ;



//-------------------------------------------------------------
// Generic call back function implementation, used by logging 
// component
//--------------------------------------------------------------

static TInt count = 0 ;

//--------------------------------------------------------------
// Default constructor
//--------------------------------------------------------------

NotifyCB :: NotifyCB()
	{
	 iScheduler = new CActiveSchedulerWait() ;
	 //iConsumer = aConsumer ;
	}

//----------------------------------------------------------------
// Default destructor
//----------------------------------------------------------------

NotifyCB :: ~NotifyCB()
	{
	delete iScheduler ;
	}
	
//-----------------------------------------------------------------
//Starts the async wait loop
//-----------------------------------------------------------------


void NotifyCB :: Start()
	{
	 iScheduler->Start() ;
	}
	
TInt NotifyCB :: HandleNotifyL(TInt aCmdId,TInt aEventId,
                     CLiwGenericParamList& aEventParamList,
                   const CLiwGenericParamList& aInParamList)
{
 	++count ;
    TInt pos=0;
 	const TLiwGenericParam *LogIterParam = aEventParamList.FindFirst(pos , KLogIter)  ;
 	
 	if(pos != KErrNotFound)
 	    {
        CLiwIterable *liwiter = (LogIterParam->Value()).AsIterable() ;
        liwiter->Reset() ;
   	    
 	    }
    
   // aEventParamList.Reset();
    //(const_cast<CLiwGenericParamList&>(aInParamList)).Reset() ;
    //delete &aEventParamList;
    //delete &aInParamList;
	if( count > 0 && (aEventId == KLiwEventCompleted || aEventId == KLiwEventError ))
		{
		 iScheduler->AsyncStop() ;
		}
		
   	if( aEventId == KLiwEventInProgress )
		{
		 iScheduler->AsyncStop() ;
		}		
	iRetVal = KErrNone ;
	


}