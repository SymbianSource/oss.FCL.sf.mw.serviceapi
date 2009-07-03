/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Implementation of the contactsynccallback class.
*
*/


//system include
#include <e32base.h>

//user include
#include "contactsynccallback.h"
#include "singlecontact.h"
/*
-----------------------------------------------------------------------------
    contactsynccallback::contactsynccallback()
    Description          : Default Constructor
    Return values        : N/A
-----------------------------------------------------------------------------
*/
CContactSyncCallback :: CContactSyncCallback():
                            iIter(NULL),
                            iError(KErrNone),
                            iWaitScheduler(NULL),
                            iErrKey(0)
                     {
                     }

/*
-----------------------------------------------------------------------------
    contactsynccallback::~contactsynccallback()
    Description          : Destructor
    Return values        : N/A
-----------------------------------------------------------------------------
*/
CContactSyncCallback :: ~CContactSyncCallback()
     {
     iIter=NULL;
     }

/*
-----------------------------------------------------------------------------
    contactsynccallback :: GetIter()
    Description          : Getter method to get a pointer to the iterator does a shallow copy.
    Return values        : pointer to class CContactIter
-----------------------------------------------------------------------------
*/

 CContactIter* CContactSyncCallback :: GetIter()
     {
     return iIter;
     }

/*
-----------------------------------------------------------------------------
    contactsynccallback :: GetErrorCode()
    Description          : Getter method to get error code.
    Return values        : Integer error code.
-----------------------------------------------------------------------------
*/
 TInt CContactSyncCallback :: GetErrorCode()
     {
     return iError;
     }
/*
-----------------------------------------------------------------------------
    contactsynccallback :: SetWaitScheduler()
    Description          : setter method for the wait shceduler shallow copy owned by core class.
    Return values        : Integer error code.
-----------------------------------------------------------------------------
*/
 void CContactSyncCallback::SetWaitScheduler(CActiveSchedulerWait *aWaitScheduler)
     {
     iWaitScheduler = aWaitScheduler;
     }
/*
-----------------------------------------------------------------------------
    contactsynccallback :: HandleReturnValue( TOperationEvent aEvent, const TInt& aError, TInt aTransId )
    Description          : virtual method which is called by the core class if there is any event
                         : in the asynchronous call.
    Return values        : N/A
-----------------------------------------------------------------------------
*/
 void CContactSyncCallback :: HandleReturnValue(TOperationEvent aEvent, 
                                                const TInt& aError, 
                                                TInt /*aTransId*/ )
    {
    if(aEvent == EInvalidKey)
        {
        iError = KErrNotSupported;
        //TPtrC8 ptr = CSearchFields :: GetFieldKeyFromId(aError);         
        iErrKey = aError;   
        }
    else
        {
        iError = aError;    
        }    
    //can be CActiveScheduler::Stop(); or to be replaced by wait scheduler.     
    iWaitScheduler->AsyncStop();
    }


/*
-----------------------------------------------------------------------------
    contactsynccallback :: HandleReturnIter( TOperationEvent aEvent, const TInt& aError, CContactIter* aIter, TInt aTransId )
    Description          : virtual method which is called by the core class if
                         : any asynchronous call completes successfully
    Return values        : N/A
-----------------------------------------------------------------------------
*/

 void CContactSyncCallback :: HandleReturnIter( const TInt& /*aError*/, CContactIter* aIter, TInt /*aTransId*/ )
     {         
     iIter = aIter;     
     //can be CActiveScheduler::Stop(); or to be replaced by wait scheduler.    
     iWaitScheduler->AsyncStop();
     }
