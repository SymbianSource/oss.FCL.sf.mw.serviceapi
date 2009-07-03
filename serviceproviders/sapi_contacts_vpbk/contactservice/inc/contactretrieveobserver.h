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
#ifndef C_CONTACTRETRIEVEOBSERVER_H
#define C_CONTACTRETRIEVEOBSERVER_H

#include <MVPbkSingleContactOperationObserver.h>

class MContactCallback;
class CContactIter;

/*
 * This class contains methods to handle contact retrival events.
 */
class CContactRetrieveObserver:public CBase,
							   public MVPbkSingleContactOperationObserver,
							   public MCancelAsync
							   
{
public:
		static CContactRetrieveObserver* NewL(CContactIter* aIter,
		                                      MContactCallback* aCallback = NULL, 
							                  CContactService* aContactService = NULL,
							                  enum Ttype aType = EOthers, 
		                                      TInt aTransId = 0, 
		                                      CActiveSchedulerWait* aSchedulerWait = NULL);
    	/*
    	 * Method that handles contact_retrieval_completion It notifies the caller with the result 
    	 * and sets the iterator with the results
    	 */
        void VPbkSingleContactOperationComplete(MVPbkContactOperationBase& aOperation,
                                                MVPbkStoreContact* aContact );
        /*
    	 * Method that handles contact_retrieval_failure. It notifies the caller with the error
    	 */                
        void VPbkSingleContactOperationFailed(MVPbkContactOperationBase& aOperation, 
                                              TInt aError );
    	/*
    	 * Implementation of Cancel of MCancelAsync
    	 */
		void Cancel();                                              
private:
		void ConstructL(CContactIter* aIter, 
		                MContactCallback* aCallback = NULL, 
		                CContactService* aContactService = NULL,
		                enum Ttype aType = EOthers,
		                TInt aTransId = 0, 
		                CActiveSchedulerWait* aSchedulerWait = NULL);
		
		//Callback function
		MContactCallback *iCallback;
		
		// Pointer to iterator
		CContactIter* iIter;
		
		//Type of Call, Sync or Async
		TInt iTransId;
			
		//For Stopping async calls
		CActiveSchedulerWait* iSchedulerWait;		
		
		//Pointer to contact service
		CContactService* iContactService;
		
		//Type of the item being retrieved
		Ttype iType;
		
};

#endif //C_CONTACTRETRIEVEOBSERVER_H