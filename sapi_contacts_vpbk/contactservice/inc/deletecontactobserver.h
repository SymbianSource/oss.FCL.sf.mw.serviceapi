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
* Description:  Observer to Delete contacts from the contact store
*
*/


#ifndef C_DELETECONTACTOBSERVER_H
#define C_DELETECONTACTOBSERVER_H

#include <s32file.h> // Used for RFileReadStream and RFileWriteStream

#include <mvpbkcontactobserver.h>    //base class for vCardExEng
#include <mvpbkbatchoperationobserver.h>
#include <mvpbkcontactstoreobserver.h>
#include <cvpbkcontactlinkarray.h>

#include "contactservice.h"
#include "cancelasyncrquest.h"

class CVPbkContactManager;
class MVPbkStoreContact;
class MVPbkContactLink;
class MContactCallback;
class MVPbkContactLinkArray;
class MCancelAsync;


class CDeleteContactObserver : public CBase,
						   	   public MVPbkBatchOperationObserver,
						   	   public MVPbkContactStoreObserver,
						   	   public MCancelAsync
	{
	public:
		/*
		 * called for creating an instace of delete contact observer
		 */
    	static CDeleteContactObserver* NewL(CContactService* aContactService,
											MVPbkContactStore* aContactStore, 
											RPointerArray<TDesC8>& aContactIdArray,
											TInt aTransId,
											MContactCallback* aCallback);
		/*
		 * Destructor
		 */ 
    	~CDeleteContactObserver();
    	/*
    	 * Implementation of Cancel of MCancelAsync
    	 */
		void Cancel();

	private:
		/*
		 * Constructor
		 */
	    CDeleteContactObserver();
	   	/* 
	   	 * Symbian second-phase construction
	   	 */
	    void ConstructL(CContactService* aContactService, 
				  		MVPbkContactStore* aContactStore, 
				  		RPointerArray<TDesC8>& aContactIdArray,
				  		TInt aTransId,
				  		MContactCallback* aCallback);

	    /*
	     * Called for deleting contacts from the contacts database.
	     */
	    void DoDeleteL();
	    
	    /*
		 * Convert the contact ids into link array format.
		 */
	    void ConvertContactIdsToLinkArrayL( RPointerArray<TDesC8>& aContactIdArray );

	private: //MVPbkBatchOperationObserver
		/**
         * Called when one step of the operation is complete.
         * @param aOperation Operation whose step has completed.
         * @param aStepSize Size of the performed step
         */
        void StepComplete( MVPbkContactOperationBase& aOperation,
      			          			TInt aStepSize );
				
		/**
         * Called when one step of the operation fails.
         * @param aOperation Operation whose step has completed.
         * @param aStepSize Size of the performed step
         * @param aError Error that occured.
         * @return ETrue if the batch operation should continue, 
         *               EFalse otherwise.
         */
        TBool StepFailed( MVPbkContactOperationBase& aOperation,
            		    		  TInt aStepSize, TInt aError );

		/**
         * Called when operation is completed.
         *
         * @param aOperation    the completed operation.
         */
        void OperationComplete( MVPbkContactOperationBase& aOperation );
	
	        
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
     	 virtual void HandleStoreEventL(MVPbkContactStore& aContactStore, 
     								    TVPbkContactStoreEvent aStoreEvent );
	
	private:  //Data members
		/*
		 * Pointer to a contact service
		 */
		CContactService* iContactService;
		/*
		 * Pointer to a contact store
		 */
		MVPbkContactStore* iContactStore;
		/*
		 * Pointer to a contact link array.
		 */
		CVPbkContactLinkArray* iContactLinkArray;
		/*
		 * Pointer to a callback.
		 */
		MContactCallback* iCallback;
		
		/*
	     * Transaction Id.
	     */
	    TInt iTransId;
	    
	    RPointerArray<MVPbkContactLinkArray> iLinkArrayToDelete;
	    
	   /*
        * OperationBase pointer to be used to cancel async request
	    */
	    MVPbkContactOperationBase* iOp;
		
	};

#endif //C_DELETECONTACTOBSERVER_H