/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  callback class implemented for synchronous api's.
*
*/


#ifndef C_CONTACTSYNCCALLBACK_H
#define C_CONTACTSYNCCALLBACK_H

#include <e32std.h>
#include "contactcallback.h"
/**
 *class CContactSyncCallback
 *class to implement the callback class which is needed in cases of synchronous implementation of the api's.
 */
 
class CContactSyncCallback: public CBase ,public MContactCallback
    {
     public:
         /**
          *Default constructor.
          */
         CContactSyncCallback();
          /**
           *Destructor.
           */
         ~CContactSyncCallback();
         /**
          *Getter method to get a pointer to the iterator does a shallow copy.
          *@return value CContactIter*, an iterator class pointer.
          */
         CContactIter* GetIter();
         /**
          *Getter method to get error code.
          *@return value TInt, integer error code KErrNone if no error
          *occured else can be any system wide error code.
          */
         TInt GetErrorCode();
         /**
          *setter method for the wait shceduler shallow copy owned by core class.
          *@return void.
          */
         void SetWaitScheduler(CActiveSchedulerWait *aWaitScheduler);         
         
         /**
          *virtual method inherited from the MContactCallback interface class
          *called by the core class if any event occurs in the asynchronous call.
          *@param aError error code.
          *@param aTransId trasaction Id of the asychronous call.
          *@return void.
          */
         virtual void HandleReturnValue(TOperationEvent aEvent, const TInt& aError, TInt aTransId );
         /**
          *virtual method inherited from the MContactCallback interface class
          *called by the core class if any  asynchronous call completes successfully .
          *@param aError error code.
          *@param aIter pointer to the CContactIter class.
          *@param aTransId trasaction Id of the asychronous call.
          *@return void.
          */
         virtual void HandleReturnIter( const TInt& aError, CContactIter* aIter, TInt aTransId );
     private:
        //Pointer to the CContactIter class.
        CContactIter* iIter;
        //Integer error code.
        TInt iError;
        //Scheduler pointer owned by core class used by this class
        CActiveSchedulerWait *iWaitScheduler;
    public:
        TInt iErrKey;    
    };

#endif    //C_CONTACTSYNCCALLBACK_H