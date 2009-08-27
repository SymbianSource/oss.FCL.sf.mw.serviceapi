/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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




#ifndef TCOMPLUGIN_H
#define TCOMPLUGIN_H

//  INCLUDES
#include <StifLogger.h>
#include <TestScripterInternal.h>
#include <StifTestModule.h>

#include "serviceerrno.h"

#include <LiwCommon.h>
#include <LiwBufferExtension.h>
#include <LiwServiceHandler.h>
#include <MVPbkContactStoreListObserver.h>
#include <MVPbkContactObserver.h>
#include <MVPbkContactFindObserver.h>
#include <MVPbkSingleContactOperationObserver.h>
#include <MVPbkBatchOperationObserver.h>
#include <MVPbkStoreContact.h>




class CTestProvider;
class CVPbkContactManager;
class MVPbkContactStoreList;
class MVPbkStoreContact;
class MVPbkContactOperationBase;

class CVPbkContactLinkArray;
_LIT( KContactsUTLogPath, "\\logs\\testframework\\ContactsUT\\" ); 
// Log file
_LIT( KContactsUTLogFile, "ContactsUT.txt" ); 



/**
*  CTestProvider test class for STIF Test Framework TestScripter.
*  ?other_description_lines
*
*  @lib ?library
*  @since ?Series60_version
*/
NONSHARABLE_CLASS(CTestProvider) : public CScriptBase,public MLiwNotifyCallback,
                                 public MVPbkContactStoreListObserver,
                                 public MVPbkContactObserver,
                                 public MVPbkContactFindObserver,
                                 public MVPbkSingleContactOperationObserver,
                                 public MVPbkBatchOperationObserver

	
    {
  

  
    enum TTestCase
        { 
        
        EGetAllContacts = 0,
        EGetContactSearch,
        EGetGroup,
        EGetDatabase,
        EAddContact,
        EDeleteContact,
        EDeleteVerify,
        EAddGroup,
        EOrganizeAddcntid,
        EOrganizeAdd,
        EOrganizeDelete,
        EImportVcard,
        EExportVcard,
        EVerifyGroupAdd,
        EVerifyImport,
        EVerifyOrganizeDelete            
  
        };
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        */
        static CTestProvider* NewL( CTestModuleIf& aTestModuleIf );

        /**
        * Destructor.
        */
        virtual ~CTestProvider();

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
        void LoadService();

	public : // Fucntions for callbacks
	
	         /**
        * From CScriptBase Runs a script line.
        * @since ?Series60_version
        * @param aItem Script line containing method name and parameters
        * @return Symbian OS error code
        */
        virtual void HandleError( const TInt& aError,TInt aTransId );
        
        
        /*
         * Called when creating a new contact or retrieving a contact is successful
         */
        virtual void HandleRetrieveContact( MVPbkStoreContact* aStoreContact, TInt aTransId );
        
        //MVPbkContactStoreListObserver
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
        
        //MVPbkContactObserver
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
         
         //MVPbkContactFindObserver   
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
		
		
		//MVPbkSingleContactOperationObserver
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
         
         //MVPbkBatchOperationObserver       
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

    private: //Helper functions from VPbk
	    
	    void AddOneContactL(const TDesC& aName);
	    void AddOneGroupL(const TDesC& aName);
	    void DeleteAllContactsL();
	    void DeleteAllGroupsL();
		TInt GetListContactL();
	    TInt GetListGroupL();
	    
    private:
	    
		TInt HandleNotifyL(	TInt aCmdId,
            	            TInt aEventId,
            	            CLiwGenericParamList& aEventParamList,
            	            const CLiwGenericParamList& aInParamList );
 	    
	    
	    /**
        * C++ default constructor.
        */
        CTestProvider( CTestModuleIf& aTestModuleIf );
        

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
        /**
        * Example test method.
        * @since ?Series60_version
        * @param aItem Script line containing parameters.
        * @return Symbian OS error code.
        */
        
        
        virtual TInt GetContactALL(CStifItemParser &aItem );
        virtual TInt GetContactSearch(CStifItemParser &aItem );
        virtual TInt GetGroup(CStifItemParser& aItem) ;
        virtual TInt GetDatabase(CStifItemParser& aItem) ;
        virtual TInt AddContact(CStifItemParser& aItem) ;
        virtual TInt DeleteContact(CStifItemParser& aItem) ;
        virtual TInt AddGroup(CStifItemParser& aItem) ;
		virtual TInt OrganiseAdd(CStifItemParser& aItem) ;
		virtual TInt OrganiseDelete(CStifItemParser& aItem);
//		virtual TInt ModifyContact(CStifItemParser& aItem);
//		virtual TInt ModifyGroup(CStifItemParser& aItem);
		virtual TInt ExportVCard(CStifItemParser& /*aItem*/);
		virtual TInt ImportVCard(CStifItemParser& /*aItem*/);
		virtual TInt GetListNewFieldsTestSync(CStifItemParser& /*aItem*/) ;
		virtual TInt AddContactNewFieldsSynTest(CStifItemParser& /*aItem */);
		virtual TInt AddGroupSynTest(CStifItemParser& /*aItem */);
		//virtual TInt GetLocationUpdateOpts(CStifItemParser& /*aItem*/) ;
        //virtual TInt MoveCoordinates(CStifItemParser& /*aItem*/) ;
    public:     // Data
        // ?one_line_short_description_of_data
        //?data_declaration;

    protected:  // Data
        // ?one_line_short_description_of_data
        //?data_declaration;

    private:    // Data
        
        // ?one_line_short_description_of_data
        //?data_declaration;
        TInt CTestGetLocation() ;
        TInt AddOneContactNewFieldsL();

        // Reserved pointer for future extension
        //TAny* iReserved;

    public:     // Friend classes
        //?friend_class_declaration;
    protected:  // Friend classes
        //?friend_class_declaration;
    private:    // Friend classes
        //?friend_class_declaration;        
        
            CLiwServiceHandler* iServiceHandler;
            MLiwInterface* iIface;            
            CLiwCriteriaItem* iCriteria;
            RCriteriaArray iCriteriaArray;
            CLiwMap* iMap;
            CLiwGenericParamList* iInparams;
            CLiwGenericParamList* iOutparams;
            
            CLiwGenericParamList* inList;
            CLiwGenericParamList* outList;
            
            TInt iErr;
            TTestCase iCase;
          //  TInt iResult;
            TInt ires;
            TInt iIndex;
            RFs iFSession;
            RFile iFileHandle;
            TInt32 iTransid;
            TPtrC iCntID;                                   
            TPtrC iGrpID;
            RPointerArray<TDesC> iIdArrayList;  
            
            CVPbkContactManager* iContactManager;
	        MVPbkContactStoreList* iStores;
	        MVPbkContactStore* iStore;
	        MVPbkStoreContact* iStoreContact;
	        MVPbkContactGroup* iGroup;
	        MVPbkContactLinkArray* iFindResults;
	        MVPbkContactLink* iResult;
	        MVPbkContactOperationBase* iOp;
	        CVPbkContactLinkArray* iContactToDelete;
            HBufC8* iBuffer;
	        TInt iOperation;
                                 

    };
    
    


#endif      // TCOMPLUGIN_H

// End of File
