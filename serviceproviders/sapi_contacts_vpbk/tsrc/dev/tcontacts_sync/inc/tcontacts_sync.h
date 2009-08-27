/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:   ?Description
*
*/




#ifndef CONTACTSUT_H
#define CONTACTSUT_H

//  INCLUDES
#include <StifLogger.h>
#include <TestScripterInternal.h>
#include <StifTestModule.h>
#include <f32file.h>

#include <MVPbkContactStoreListObserver.h>
#include <MVPbkContactObserver.h>
#include <MVPbkContactFindObserver.h>
#include <MVPbkSingleContactOperationObserver.h>
#include <MVPbkBatchOperationObserver.h>
#include <S32MEM.H>
#include <S32FILE.H>

#include "contactcallback.h"

// Logging path
_LIT( KContactsUTLogPath, "\\logs\\testframework\\ContactsUT\\" ); 
// Log file
_LIT( KContactsUTLogFile, "ContactsUT.txt" ); 

// CONSTANTS



// FORWARD DECLARATIONS
class CContactsUT;
class CVPbkContactManager;
class MVPbkContactStoreList;
class MVPbkStoreContact;
class MVPbkContactOperationBase;
class CVPbkContactLinkArray;
class CVPbkVCardEng;
class CContactService;
class CSingleContact;
// CLASS DECLARATION

/**
*  CContactsUT test class for STIF Test Framework TestScripter.
*  ?other_description_lines
*
*  @lib ?library
*  @since ?Series60_version
*/
NONSHARABLE_CLASS(CContactsUT) : public CScriptBase, 
                                 public MContactCallback, 
                                 public MVPbkContactStoreListObserver,
                                 public MVPbkContactObserver,
                                 public MVPbkContactFindObserver,
                                 public MVPbkSingleContactOperationObserver,
                                 public MVPbkBatchOperationObserver
                                 
    {
    public:
        enum TOperation
            {
            ENone,
            EContact,
            EGroup,
            EVCard,
            EVCardEx,
            EGetContact,
            EGetGroup,
            EGetDatabase,
            EGetContactDelete
            };
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        */
        static CContactsUT* NewL( CTestModuleIf& aTestModuleIf );

        /**
        * Destructor.
        */
        virtual ~CContactsUT();

    public: // New functions

        /**
        * ?member_description.
        * @since ?Series60_version
        * @param ?arg1 ?description
        * @return ?description
        */
        //?type ?member_function( ?type ?arg1 );

    public: // Functions from base classes

        /**
        * From CScriptBase Runs a script line.
        * @since ?Series60_version
        * @param aItem Script line containing method name and parameters
        * @return Symbian OS error code
        */
        virtual TInt RunMethodL( CStifItemParser& aItem );
         
        /**
        * From CScriptBase Runs a script line.
        * @since ?Series60_version
        * @param aItem Script line containing method name and parameters
        * @return Symbian OS error code
        */
        virtual void HandleReturnValue( TOperationEvent aEvent, const TInt& aError, TInt aTransId );
        
        /*
         *Called after GetList async call is complete
         */
        virtual void HandleReturnIter( const TInt& aError, CContactIter* aIter, TInt aTransId );
        
        virtual void HandleReturnId( const TInt& aError, HBufC8* acntId, TInt aTransId );
        
        virtual void HandleReturnArray(const TInt& aError, RPointerArray<HBufC8>& aArray, TInt aTransId );
        
        /*
         * Called when creating a new contact or retrieving a contact is successful
         */
        virtual void HandleRetrieveContact( MVPbkStoreContact* aStoreContact, TInt aTransId );
        
        /**
         * Called when the opening process is complete. 
         *
         * Before this all stores have sent StoreReady or StoreUnavailable 
         * event. The client can not trust that all stores are available
         * for use when this is called.
         */
        virtual void OpenComplete();
        
        /**
         * Called when a contact store is ready to use.
         *
         * @param aContactStore The store that is ready.
         */
        virtual void StoreReady(MVPbkContactStore& aContactStore);

        /**
         * Called when a contact store becomes unavailable.
         *
         * Client may inspect the reason of the unavailability and decide
         * whether or not it will keep the store opened (ie. listen to 
         * the store events).
         *
         * @param aContactStore The store that became unavailable.
         * @param aReason The reason why the store is unavailable.
         *                This is one of the system wide error codes.
         */
        virtual void StoreUnavailable(MVPbkContactStore& aContactStore, 
                TInt aReason);

        /**
         * Called when changes occur in the contact store.
         *
         * @see TVPbkContactStoreEvent
         * @param aContactStore A store whose event it is.
         * @param aStoreEvent The event that has occurred.
         */
        virtual void HandleStoreEventL(
                MVPbkContactStore& aContactStore, 
                TVPbkContactStoreEvent aStoreEvent);
        
        /**
         * Called when a contact operation has succesfully completed.
         *
         * NOTE: If you use Cleanupstack for MVPbkStoreContact use 
         * MVPbkStoreContact::PushL or CleanupDeletePushL from e32base.h.
         * (Do Not Use CleanupStack::PushL(TAny*) because then the virtual 
         * destructor of the M-class won't be called when the object 
         * is deleted).
         *
         * @param aResult   The result of the operation. The client takes
         *                  the ownership of the iStoreContact immediately
         *                  if set in aResult.
         */
        virtual void ContactOperationCompleted(TContactOpResult aResult);

        /**
         * Called when a contact operation has failed.
         *
         * @param aOpCode           The operation that failed.
         * @param aErrorCode        System error code of the failure.
         *							KErrAccessDenied when EContactCommit 
         *							means that contact hasn't been locked.
         * @param aErrorNotified    ETrue if the implementation has already
         *                          notified user about the error, 
         *                          EFalse otherwise.
         */
        virtual void ContactOperationFailed
            (TContactOp aOpCode, TInt aErrorCode, TBool aErrorNotified);
            
        /**
         * Called when find is complete. Caller takes ownership of the results
         * In case of an error during find, the aResults may contain only 
         * partial results of the find
         *
         * @param aResults Array of contact links that matched the find
         *                 Callee must take ownership of this object in
         *                 the start of the function, ie. in case the 
         *                 function leaves the results must be destroyed. 
         *                 The find operation can be destroyed at the end 
         *                  of this callback.
         */
        virtual void FindCompleteL( MVPbkContactLinkArray* aResults );

        /**
         * Called in case the find fails for some reason. The find operation
         * can be destroyed at the end of this callback.
         * 
         * @param aError One of the system wide error codes.
         *        KErrNotReady if store is not ready (not open or unavailable)
         */
        virtual void FindFailed( TInt aError );

        /**
         * Called when the operation is completed.
         *
         * A client has the operation as a member and it can delete the operation
         * instance in this function call. If the implementation of the store
         * calls the function from the operation instance it must not handle
         * any member data after calling it.
         *
         * @param aOperation The completed operation.
         * @param aContact The contact returned by the operation.
         *                 A client must take the ownership immediately.
         *
         *                  NOTE:
         *                  If you use CleanupStack for MVPbkStoreContact
         *                  Use MVPbkStoreContact::PushL or
         *                  CleanupDeletePushL from e32base.h.
         *                  (Do Not Use CleanupStack::PushL(TAny*) because
         *                  then the virtual destructor of the M-class
         *                  won't be called when the object is deleted).
         */
        virtual void VPbkSingleContactOperationComplete(
                MVPbkContactOperationBase& aOperation,
                MVPbkStoreContact* aContact );

        /**
         * Called if the operation fails.
         *
         * A client has the operation as a member and it can delete the operation
         * instance in this function call. If the implementation of the store
         * calls the function from the operation instance it must not handle
         * any member data after calling it.
         *
         * @param aOperation The failed operation.
         * @param aError An error code of the failure.
         */
        virtual void VPbkSingleContactOperationFailed(
                MVPbkContactOperationBase& aOperation, 
                TInt aError );
                
        /**
         * Called when one step of the operation is completed.
         *
         * @param aOperation Operation whose step has completed
         * @param aStepSize Size of the performed step
         */
        virtual void StepComplete( 
                MVPbkContactOperationBase& aOperation,
                TInt aStepSize );

        /**
         * Called when one step of the operation fails.
         *
         * @param aOperation Operation whose step has failed
         * @param aStepSize Size of the performed step
         * @param aError Error that occured
         * @return ETrue if the batch operation should continue, 
         *               EFalse otherwise
         *         NOTE! If returning ETrue the operation can NOT be deleted.
         *               Operation should be deleted in OperationCompleted() 
         *               function.
         *               If returning EFalse the operation can be deleted
         *               safely.
         */
        virtual TBool StepFailed(
                MVPbkContactOperationBase& aOperation,
                TInt aStepSize, TInt aError );

        /**
         * Called when operation is completed.
         * This is called when all steps are executed. If EFalse is returned
         * in StepFailed() call this function is NOT called.
         *
         * @param aOperation    the completed operation
         */
        virtual void OperationComplete( 
                MVPbkContactOperationBase& aOperation );
        
        
    protected:  // New functions

        /**
        * ?member_description.
        * @since ?Series60_version
        * @param ?arg1 ?description
        * @return ?description
        */
        //?type ?member_function( ?type ?arg1 );

    protected:  // Functions from base classes

        /**
        * From ?base_class ?member_description
        */
        //?type ?member_function();

    private:

        /**
        * C++ default constructor.
        */
        CContactsUT( CTestModuleIf& aTestModuleIf );

        /**
        * By default Symbian 2nd phase constructor is private.
        */
        void ConstructL();

        // Prohibit copy constructor if not deriving from CBase.
        // ?classname( const ?classname& );
        // Prohibit assigment operator if not deriving from CBase.
        // ?classname& operator=( const ?classname& );

        /**
        * Frees all resources allocated from test methods.
        * @since ?Series60_version
        */
        void Delete();

        /**
        * Test methods are listed below. 
        */
        void DeleteAllL();
        void AddOneContactL(TDesC& aName);
        void CheckContactsL(TInt& aCount,RPointerArray<TDesC8>& aIdArray);


        /**
        * Example test method.
        * @since ?Series60_version
        * @param aItem Script line containing parameters.
        * @return Symbian OS error code.
        */       
        //ADD NEW METHOD DEC HERE
        virtual TInt AddContactSAPIL( CStifItemParser& aItem );
        virtual TInt DeleteContactSAPIL( CStifItemParser& aItem );
        virtual TInt ModifyContactSAPIL( CStifItemParser& aItem );
        virtual TInt ImportContactSAPIL( CStifItemParser& aItem );
        virtual TInt ExportContactSAPIL( CStifItemParser& aItem );
        
        virtual TInt GetListDeleteContactL( CStifItemParser& aItem );
        virtual TInt AddContactGetListL( CStifItemParser& aItem );
       	virtual TInt GetGroupsL( CStifItemParser& aItem );        
		virtual TInt GetContactsL( CStifItemParser& aItem );        
		virtual TInt GetDatabaseL( CStifItemParser& aItem );        		
		virtual TInt AddL( CStifItemParser& aItem );
		virtual TInt AddGroupL( CStifItemParser& aItem );
		virtual TInt DeleteContactL( CStifItemParser& aItem );
		virtual TInt DeleteGroupL( CStifItemParser& aItem );
		virtual TInt ModifyL( CStifItemParser& aItem );
        virtual TInt ModifyGroupL( CStifItemParser& aItem );
        virtual TInt OrganiseAddL( CStifItemParser& aItem );
        virtual TInt OrganiseDeleteL( CStifItemParser& aItem );
        virtual TInt ImportL( CStifItemParser& aItem );
        virtual TInt ExportL( CStifItemParser& aItem );
                       
    private:    // Data
        TInt iErr;   
        CVPbkContactManager* iContactManager;
        RFs iRfs;
        MVPbkContactStoreList* iStores;
        MVPbkContactStore* iStore;
        MVPbkStoreContact* iStoreContact;
        MVPbkContactGroup* iGroup;
        MVPbkContactLinkArray* iFindResults;
        MVPbkContactLink* iResult;
        MVPbkContactOperationBase* iOp;
        CVPbkContactLinkArray* iContactToDelete;
        CVPbkVCardEng* iVCardEngine;
        RDesWriteStream iDestStream;
        RFileReadStream iSource;
        HBufC8* iBuffer;
        TInt iOperation;
        CContactService* iServiceHandle;
        CSingleContact* iSingleContact;       

    };

#endif      // CONTACTSUT_H

// End of File
