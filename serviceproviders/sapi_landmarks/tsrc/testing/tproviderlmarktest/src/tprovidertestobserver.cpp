/*
* Copyright (c) 2007-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:   This Class is observer for the Launching Application
*
*/



#include <e32const.h>
#include "tprovidertestobserver.h"
_LIT8(KResponse,"ReturnValue");
#include <e32svr.h>
#include <f32file.h>
#include <e32std.h>
#include <liwgenericparam.h>
#include <liwservicehandler.h>
#include <liwvariant.h>
#include <lbsposition.h> 
#include "landmarkliwparams.hrh"
#include "serviceerrno.h"

// -----------------------------------------------------------------------------
// CProviderObserver::NewL
// Returns the instance of CLauncherObserver.
// -----------------------------------------------------------------------------
CProviderObserver* CProviderObserver::NewL()
	{
	CProviderObserver* self = new( ELeave ) CProviderObserver();
	return self;
	}


// ---------------------------------------------------------------------------
// call back
// ---------------------------------------------------------------------------
//
TInt CProviderObserver :: HandleNotifyL( TInt /*aCmdId*/, TInt aEventId, CLiwGenericParamList& aEventParamList,const CLiwGenericParamList& /*aInParamList*/)

    {
    
    iCancel = EFalse;
    if ( aEventId == KLiwEventCanceled  )
        {
            iCancel = ETrue;
            
        }
    
    if ( aEventId == KLiwEventCompleted )   
        {
        const TLiwGenericParam* p= NULL;
        TInt pos = 0;
            
        p = aEventParamList.FindFirst(pos, KErrorCode ); // Finding Error Code
        
        if(p)
            {
            iErrorReturn = p->Value().AsTInt32();
            }
        else
            {
            iErrorReturn = KErrGeneral; 
            }
  
        }
      
      if(iWait)
         iWait->AsyncStop();
    }




// ---------------------------------------------------------------------------
// consturctor
// ---------------------------------------------------------------------------
//
CProviderObserver::CProviderObserver( )
	{
	iWait= NULL;
	}
// ---------------------------------------------------------------------------
// consturctor
// ---------------------------------------------------------------------------
//
void CProviderObserver::SetWait(CActiveSchedulerWait *aWait )
	{
	iWait = aWait;
	}