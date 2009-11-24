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
* Description:  Observer for importing a contact into the contacts database.
*
*/


#ifndef C_IMPORTSTORELISTOBSERVER_H
#define C_IMPORTSTORELISTOBSERVER_H

#include <s32file.h> // Used for RFileReadStream 
#include <MVPbkContactStoreListObserver.h>    //base class for vCardEng
#include <MVPbkContactObserver.h>    //base class for vCardEng
#include <MVPbkContactCopyObserver.h>    //base class for vCardEng
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
class CContactService;

class CImportStoreListObserver;
class CImportStoreListObserver: public CBase,
								public MContactStoreListObserver,
								public MVPbkContactCopyObserver,
	           		   			public MCancelAsync
{
public:
	/**
     * Called for creating an instance of import store list observer.
     */
    static CImportStoreListObserver* NewL(RFs &aFs,
                                          const TFileName& aFileName,
                                          MContactCallback *aCallback,
                                          TInt32 aTransId);
    /*
     * Destructor
     */
    ~CImportStoreListObserver();
	/*
	 * Methods to set vcard engine and contact store.
	 */
     void SetEngine(CVPbkVCardEng* aEngine);
     void SetContactStore(MVPbkContactStore* aContactStore);
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
     * An indication that the contact store is opened successfully.
     *
     * @return None.
     */
    void OpenComplete();
    
private: // from MVPbkContactCopyObserver

    /**
     * An indication that a field has been added into a contact.
     *
     * @param aOperation A reference to the operation instance.
     * @return None.
     */
    void FieldAddedToContact( MVPbkContactOperationBase& aOperation );

    /**
     * An indication that a contact operation has failed.
     *
     * @param aOperation A reference to the operation instance.
     * @param aError The error code for the operation.
     * @return None.
     */
    void FieldAddingFailed( MVPbkContactOperationBase& aOperation,
    TInt aError );

    /**
     * An indication that contacts have been saved into a store.
     *
     * @param aOperation A reference to the operation instance.
     * @param aResults An array of contact links pointing to the store.
     * @return None.
     */
    void ContactsSaved( MVPbkContactOperationBase& aOperation,
        MVPbkContactLinkArray* aResults );

    /**
     * An indication that contact saving has failed.
     *
     * @param aOperation A reference to the operation instance.
     * @param aError The error code for the operation.
     * @return None.
     */
    void ContactsSavingFailed( MVPbkContactOperationBase& aOperation,
        TInt aError );
	
private:
	/*
	 * Constructor.
	 */
    CImportStoreListObserver(RFs &aFs,
                             const TFileName& aFileName,
                             MContactCallback *aCallback,
                             TInt32 aTransId);
    
 private: // Data members
   	/*
     * A pointer to the Virtual Phonebook Engine instance.
     * Not Own.
     */
    CVPbkVCardEng* iEngine;
    /*
     * file session
     */
    RFs iFs;
    /**
     * A read stream for reading from file.
     */
    RFileReadStream iSource;
    /*
     * A pointer to contact store.
     */
    MVPbkContactStore* iContactStore;
    /*
     * File name
     */
    TFileName iFileName;
    /*
     * A pointer to callback instance.
     */
    MContactCallback *iCallback;
    /*
     * Transaction Id.
     */
    TInt32 iTransId;
    /*
     * ContactService Instance
     */
     CContactService* iContactService;
    /*
     * Handle for underlying Import call
     */
     MVPbkContactOperationBase* iOp;
};



#endif //// C_IMPORTSTORELISTOBSERVER_H