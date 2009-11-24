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
* Description:  Observer to Add a contact to the contact store
*
*/


#ifndef C_ADDCONTACTOBSERVER_H
#define C_ADDCONTACTOBSERVER_H


#include <s32file.h> 
#include <MVPbkContactStoreObserver.h>    
#include <MVPbkContactObserver.h>    
#include <MVPbkSingleContactOperationObserver.h>
#include <MVPbkStoreContact.h>

#include "singlecontact.h"
#include "cancelasyncrquest.h"

class CVPbkContactManager;
class MVPbkStoreContact;
class MVPbkContactLink;
class MContactCallback;
class MCancelAsync;


class CAddContactObserver : public CBase,
   							public MVPbkContactStoreObserver,
   							public MVPbkSingleContactOperationObserver,
           		   			public MVPbkContactObserver,
           		   			public MCancelAsync
{
	public:
			/*
			* called for creating an instace of add contact observer
			*/
    	static CAddContactObserver* NewL(CContactService* aContactService,
										 MVPbkContactStore* aContactStore, 
										 CSingleContact* aStoreContact,
										 const TDesC8& aGroupId,
										 const TDesC& aGroupLabel,
										 TInt aTransId,
										 MContactCallback* aCallback);
			/*
			* Destructor
			*/
    	~CAddContactObserver();
    	
    	/*
    	 * Implementation of Cancel of MCancelAsync
    	 */
		void Cancel();
	private:
 	   /*
		* Constructor		*/
	    CAddContactObserver(CContactService* aContactService,
	    					MVPbkContactStore* aContactStore, 
	    					CSingleContact* aStoreContact,	    				
	    					TInt aTransId,
	    					MContactCallback* aCallback);
	    
	   /*
		* Symbian second-phase construction
		*/
		void ConstructL(const TDesC8& aGroupId,
    				    const TDesC& aGroupLabel);
	   
	    /*
	    * Called for adding a contact into the contacts database.
	    */
	    void DoAddL();
	    
	    /*
	    * Called for committing a contact into the contacts database.
	    */
	    TInt DoCommitL(TContactOpResult aResult);
	    
	    void DoEditContactOrGroupL(MVPbkStoreContact* aContact);

	private: // from MVPbkContactObserver

	    /**
	     * An indication that a contact operation has been completed.
	     *
	     * @param aResult The result of the operation.
	     * @return None.
	     */
	    void ContactOperationCompleted( TContactOpResult aResult );

	    /**
	     * An indication that a contact operation has failed.
	     *
	     * @param aOpCode The operation identifier.
	     * @param aErrorCode The error code.
	     * @param aErrorNotified A flag indicating whether the user has been 
	     *                       notified about the error.
	     * @return None.
	     */
	    void ContactOperationFailed( TContactOp aOpCode, TInt aErrorCode,
	        TBool aErrorNotified );
	        
	        
	private: //MVPbkContactStoreObserver
		/**
         * Called when a contact store is ready to use.
         */
         void StoreReady( MVPbkContactStore& aContactStore );

        /**
         * Called when a contact store becomes unavailable.
         * Client may inspect the reason of the unavailability and decide whether or not
         * it will keep the store opened (ie. listen to the store events).
         * @param aContactStore The store that became unavailable.
         * @param aReason The reason why the store is unavailable.
         *                This is one of the system wide error codes.
         */
         void StoreUnavailable( MVPbkContactStore& aContactStore, TInt aReason );

        /**
         * Called when changes occur in the contact store.
         * @see TVPbkContactStoreEvent
         * @param aContactStore The store the event occurred in.
         * @param aStoreEvent   Event that has occured.
         */
        virtual void HandleStoreEventL( MVPbkContactStore& aContactStore, 
                						TVPbkContactStoreEvent aStoreEvent );
	
	private: // from MVPbkSingleContactOperationObserver
	    /**
         * Called when operation is completed.
         *
         * @param aOperation the completed operation.
         * @param aContact  the contact returned by the operation.
         *                  Client must take the ownership immediately.
         *
         *                  !!! NOTICE !!!
         *                  If you use Cleanupstack for MVPbkStoreContact
         *                  Use MVPbkStoreContact::PushL or
         *                  CleanupDeletePushL from e32base.h.
         *                  (Do Not Use CleanupStack::PushL(TAny*) because
         *                  then the virtual destructor of the M-class
         *                  won't be called when the object is deleted).
         */	    
	    virtual void VPbkSingleContactOperationComplete(
                							MVPbkContactOperationBase& aOperation,
                							MVPbkStoreContact* aContact);
			/**
         * Called if the operation fails.
         *
         * @param aOperation    the failed operation.
         * @param aError        error code of the failure.
         */
        virtual void VPbkSingleContactOperationFailed(
                							MVPbkContactOperationBase& aOperation, 
                							TInt aError);
                							
	private:
	
	void CreateAndAddFieldToContactL();
	
	public:
		/*
		* Pointer to a contact manager
		*/
		CContactService* iContactService;		
		/*
		* Pointer to a contact store
		*/
		MVPbkContactStore* iContactStore;
		/*
		* Pointer to a store contact
		*/
		CSingleContact* iStoreContact;
		/*
		* Pointer to a callback
		*/
		MContactCallback* iCallback;
		/*
		* Pointer to group id.
		*/
		HBufC8* iGroupId;
		/*
		* Pointer to group label
		*/
		HBufC* iGroupLabel;
		/*
		* Flag to indicate whether contact is locked or not
		*/
		TBool iLockFlag;
		
		/*
	     * Transaction Id.
	     */
        TInt iTransId;
        
        TInt iErrorID;
        //TPtrC iErrKey;
        
        MVPbkStoreContact* iContact;
        MVPbkContactGroup* iGroup;

        
        //OperationBase pointer to be used to cancel async request
        MVPbkContactOperationBase* iOp;
};

#endif //C_ADDCONTACTOBSERVER_H