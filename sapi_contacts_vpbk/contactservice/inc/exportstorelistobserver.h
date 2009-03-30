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
* Description:  Observer for exporting a contact from the contact store.
*
*/


#ifndef C_EXPORTSTORELISTOBSERVER_H
#define C_EXPORTSTORELISTOBSERVER_H


#include <s32file.h> // Used for RFileWriteStream 
#include <mvpbkcontactstoreListobserver.h>    //base class for vCardEng
#include <mvpbkcontactobserver.h>    //base class for vCardEng
#include <mvpbksinglecontactoperationObserver.h> //base class for vCardEng
#include <CVPbkVCardEng.h>
#include <MVPbkContactStore.h>
#include "contactcallback.h"
#include "storelistobserver.h"
#include "contactservice.h"
#include "cancelasyncrquest.h"

class CVPbkVCardEng;
class CVPbkContactManager;
class MVPbkStoreContact;
class MVPbkFieldType;
class MVPbkContactLink;
class CContactCopyObserver;
class CContactService;

class CExportStoreListObserver;
class CExportStoreListObserver: public CBase,
								public MContactStoreListObserver,
								public MVPbkSingleContactOperationObserver,
								public MCancelAsync
{   
public:
	/*
	 * called for creating an instace of delete contact observer
	 */
    static CExportStoreListObserver* NewL(CContactService* aContactService,
    									  RFs &aFs,
    									  const TFileName& aFileName,
    									  const TDesC8& aContactId,
    									  MContactCallback *aCallback, 
    									  TInt aTransId );
	
	/*
	 * Destructor
	 */
    ~CExportStoreListObserver();
   	/* 
   	 * sets vcard engine
   	 */
     void SetEngine(CVPbkVCardEng* aEngine);
    /*
     * sets contact store
     */
     void SetContactStore(MVPbkContactStore* aContactStore);

    /*
     * sets contact service
     */
     void SetContactService(CContactService* aContactService);

	/*
	 * Implementation of Cancel of MCancelAsync
	 */
	 void Cancel();

private: // from MVPbkContactStoreListObserver

    /**
     * An indication that the contact store is ready.
     *
     * @param aContactStore A reference to the store sending the indication.
     * @return None.
     */
    void StoreReady( MVPbkContactStore& aContactStore );

    /**
     * An indication that the contact store is not ready.
     *
     * @param aContactStore A reference to the store sending the indication.
     * @param aReason An error code defining the reason for unavailability.
     * @return None.
     */
    void StoreUnavailable( MVPbkContactStore& aContactStore,
        TInt aReason );

    /**
     * An indication for a contact store event.
     *
     * @param aContactStore A reference to the store sending the indication.
     * @param aStoreEvent The contact store event.
     * @return None.
     */
    void HandleStoreEventL( MVPbkContactStore& aContactStore,
        TVPbkContactStoreEvent aStoreEvent );

    /**
     * An indication that the contact store is openned successfully.
     *
     * @return None.
     */
    void OpenComplete();

private: // from MVPbkSingleContactOperationObserver

    /**
     * An indication that a contact operation has been completed.
     *
     * @param aOperation A reference to the operation instance.
     * @param aContact A pointer to the contact object used in the operation.
     * @return None.
     */
    void VPbkSingleContactOperationComplete(
        MVPbkContactOperationBase& aOperation,
        MVPbkStoreContact* aContact );

    /**
     * An indication that a contact operation has failed.
     *
     * @param aOperation A reference to the operation instance.
     * @param aError The error code for the operation.
     * @return None.
     */
    void VPbkSingleContactOperationFailed(
        MVPbkContactOperationBase& aOperation, TInt aError );    
    
private:
	/*
	 * Constructor
	 */
    CExportStoreListObserver();
    
    /*
     * Symbian second-phase constructor
     */
    void ConstructL(CContactService* aContactService,
					RFs &aFs,
					const TFileName& aFileName,
					const TDesC8& aContactId,
					MContactCallback *aCallback,
					TInt aTransId);
    
 private: // Data members
    /**
     * A pointer to the Virtual Phonebook Engine instance.
     * Own.
     */
     CVPbkVCardEng* iEngine;
	/*
	 * File session.
	 */     
     RFs iFs;
    /*
     * File name
     */
     TFileName iFileName;
    /*
     * Pointer to a callback instance.
     */
     MContactCallback* iCallback;
    /*
     * Pointer to contact link instance.
     */ 
     const MVPbkContactLink* iContactLink;
    /*
     * Pointer to contact store instance.
     */ 
     MVPbkContactStore* iContactStore;
    /*
     * Transaction Id.
     */
     TInt32 iTransId;
    /*
     * File write stream instance.
     */ 
     RFileWriteStream iDest;
     
     MVPbkContactLinkArray* iLinkArray;
     
     CContactService* iContactService;
    /*
     * Handle for underlying Export call
     */
     MVPbkContactOperationBase* iOp;     
};

#endif //// C_EXPORTSTORELISTOBSERVER_H