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
#include <liwservicehandler.h>
#include <liwcommon.h>

#include "tlogprovidertest.h"

#include "tcallback.h"
#include "liwlogiter.h"
#include"tconstants.h"
// _LIT8(KLogIter , "Iterator") ;



//-------------------------------------------------------------
// Generic call back function implementation, used by logging 
// component
//--------------------------------------------------------------

static TInt count = 0 ;

//--------------------------------------------------------------
// Default constructor
//--------------------------------------------------------------

tcallback :: tcallback()
	{
	 iScheduler = new CActiveSchedulerWait() ;
	}

//----------------------------------------------------------------
// Default destructor
//----------------------------------------------------------------

tcallback :: ~tcallback()
	{
	delete iScheduler ;
	}
	
//-----------------------------------------------------------------
//Starts the async wait loop
//-----------------------------------------------------------------


void tcallback :: Start()
	{
	 iScheduler->Start() ;
	}
	
TInt tcallback :: HandleNotifyL(TInt aCmdId,TInt aEventId,
                     CLiwGenericParamList& aEventParamList,
                   const CLiwGenericParamList& aInParamList)
{
 	++count ;
    TInt pos=0;
 	const TLiwGenericParam *LogIterParam = aInParamList.FindFirst(pos , KLogIter)  ;
 	
 	if(pos != KErrNotFound)
 	    {
        CLiwIterable *liwiter = (LogIterParam->Value()).AsIterable() ;
        liwiter->Reset() ;
   	    
 	    }
    
    aEventParamList.Reset();
    //aInParamList.Reset();
    /*(const_cast<CLiwGenericParamList&>(aInParamList)).Reset() ;
    delete &aEventParamList;
    delete &aInParamList;*/
	if(count > 0)
		{
		if(iScheduler->IsStarted())
		 iScheduler->AsyncStop() ;
		}
	iRetVal = KErrNone ;
	
   return 0;

}