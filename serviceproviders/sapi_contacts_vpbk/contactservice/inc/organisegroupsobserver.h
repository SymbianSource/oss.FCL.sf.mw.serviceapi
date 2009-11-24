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
* Description:  Observer to add/delete contacts to/from a group in the contact store.
*
*/


#ifndef C_ORGANISEGROUPSOBSERVER_H
#define C_ORGANISEGROUPSOBSERVER_H


#include <s32file.h> // Used for RFileReadStream and RFileWriteStream
#include <MVPbkContactObserver.h>    //base class for vCardExEng
#include <MVPbkContactStoreObserver.h>    //base class for vCardExEng
#include <MVPbkSingleContactOperationObserver.h>
#include <CVPbkContactLinkArray.h>
#include "contactservice.h"

class CVPbkContactManager;
class MVPbkStoreContact;
class MVPbkContactLink;
class MVPbkContactLinkArray;
class MContactCallback;
class MVPbkContactGroup;
class CContactService;

class COrganiseGroupsObserver : public CBase,
						   		public MVPbkContactStoreObserver,
						   		public MVPbkSingleContactOperationObserver,
						   		public MCancelAsync
{
	public:
		/*
		 * Called for creating an instace of organise groups observer.
		 */
    	static COrganiseGroupsObserver* NewL(CContactService* aContactService,
											 const TDesC8& aGroupId, 
											 RPointerArray<TDesC8>& aContactIdArray,
											 TBool aAssociateFlag,
											 TInt aTransId,
											 MContactCallback* aCallback ,
											 MVPbkContactStore* aContactStore);
		/*
		 * Destructor.
		 */
    	~COrganiseGroupsObserver();
		/*
    	 * Implementation of Cancel of MCancelAsync
    	 */
		void Cancel();

	private:
		/*
		 * Constructor
		 */
	    COrganiseGroupsObserver(); 
	    /*
	     * Symbian second-phase constuctor
	     */
	    /* 
	   	 * Symbian second-phase construction
	   	 */
	    void ConstructL(CContactService* aContactService,
						const TDesC8& aGroupId , 
						RPointerArray<TDesC8>& aContactIdArray,
						TBool aAssociateFlag,
						TInt aTransId,
						MContactCallback* aCallback ,
			            MVPbkContactStore* aContactStore);

	private:
		/*
		 * Called for associating/disassociating a list of contacts to/from the group.
		 */
		void DoOrganiseGroupsL(MVPbkStoreContact* aContact);
		/*
		 * Called to get the pointer to the contact group.
		 */
		void DoGetGroupL();
		
		/*
		 * Convert the contact ids into link array format.
	 	 */
		void ConvertContactIdsToLinkArrayL( RPointerArray<TDesC8>& aContactIdArray );

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
                					   TVPbkContactStoreEvent aStoreEvent);
	
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
	    virtual void VPbkSingleContactOperationComplete(MVPbkContactOperationBase& aOperation,
                							            MVPbkStoreContact* aContact);
			/**
         * Called if the operation fails.
         *
         * @param aOperation    the failed operation.
         * @param aError        error code of the failure.
         */
        virtual void VPbkSingleContactOperationFailed(MVPbkContactOperationBase& aOperation, 
                							          TInt aError);
	
	
	private: //Data members
		
		/*
		 * Pointer to a contact manager.
		 */
		const CVPbkContactManager* iContactManager;		
		/*
		 * Pointer to a contact group id.
		 */
		HBufC8* iGroupId;
		/*
		 * Pointer to a contact id array.
		 */
		CVPbkContactLinkArray* iContactLinkArray;
		/*
		 * Flag to indicate associate or disassociate.
		 */
		TBool iAssociateFlag;
		/*
		 * Pointer to a callback.
		 */
		MContactCallback* iCallback;
			
		/*
	     * Transaction Id.
	     */
	    TInt iTransId;
	    
	    RPointerArray<MVPbkContactLinkArray> iLinkArrayToDelete;
	    
	    MVPbkContactLinkArray* iLinkArray;
	    
	    MVPbkContactStore* iContactStore;
	    
	    CContactService* iContactService;

        //OperationBase pointer to be used to cancel async request
        MVPbkContactOperationBase* iOp;
	    
};

#endif //C_ORGANISEGROUPSOBSERVER_H