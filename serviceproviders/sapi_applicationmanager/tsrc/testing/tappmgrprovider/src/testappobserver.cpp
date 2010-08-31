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
* Description:  This Class is observer for the Launching Application
*
*/


#include <e32const.h>
#include "testappobserver.h"
_LIT8(KResponse,"ReturnValue");
_LIT8(KErrorCode,"ErrorCode");

// -----------------------------------------------------------------------------
// CAppObserver::NewL
// Returns the instance of CLauncherObserver.
// -----------------------------------------------------------------------------
CAppObserver* CAppObserver::NewL(CActiveSchedulerWait * aWait)
	{
	CAppObserver* self = new( ELeave ) CAppObserver(aWait);
	return self;
	}


// ---------------------------------------------------------------------------
// call back
// ---------------------------------------------------------------------------
//
TInt CAppObserver :: HandleNotifyL( TInt /*aCmdId*/, TInt aEventId, CLiwGenericParamList& aEventParamList,const CLiwGenericParamList& /*aInParamList*/)

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
        
        
        
        pos = 0;
        p = aEventParamList.FindFirst(pos, KResponse ); // Finding Error Code
        
        if( p )
            {
            iReason = p->Value().AsTInt32();
            }
       		  iWait->AsyncStop();
        }
    
     
  
    }




// ---------------------------------------------------------------------------
// consturctor
// ---------------------------------------------------------------------------
//
CAppObserver::CAppObserver(CActiveSchedulerWait * aWait )
	{
	 iWait = aWait;
	 iReason = 10 ; //Reason of failure can be either 0 or some negative valuw which incater 
	 //error but it cant be greater than 0 
	}