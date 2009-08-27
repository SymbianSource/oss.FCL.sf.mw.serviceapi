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
* Description:  Core class for the contact service APIs.
*
*/


#ifndef C_CONTACTSERVICE_H
#define C_CONTACTSERVICE_H

//System includes
#include <s32file.h> // Used for RFileReadStream and RFileWriteStream
#include <mvpbkcontactstoreListobserver.h>    //base class for vCardEng
#include <mvpbkcontactobserver.h>    //base class for vCardEng
#include <mvpbksinglecontactoperationObserver.h>//base class
#include <mvpbkcontactcopyobserver.h>    //base class for vCardEng
#include <CVPbkFieldTypeRefsList.h>		//Used to specify search fields
#include <CVPbkContactLinkArray.h>
#include <vpbkcontactstoreuris.h>

//User Includes
#include "contactcallback.h"
#include "contactservice.hrh"
#include "contactiter.h"
#include "storelistobserver.h"
#include "exportstorelistobserver.h"
#include "importstorelistobserver.h"
#include "searchfields.h"
#include "singlecontact.h"
#include "fieldkeys.hrh"

class CVPbkVCardEng;
class CVPbkContactManager;
class MVPbkStoreContact;
class MVPbkFieldType;
class MVPbkContactLink;
class CContactCopyObserver;
class CSingleContactOperationObserver;
class CImportStoreListObserver;
class CExportStoreListObserver;
class CContactViewObserver;
class CGetListStoreListObserver;
class CContactIter;
class CContactRetrieveObserver;
class CSearchFields;
class CSingleContact;
class MCancelAsync;
class MLocalCallback;


/**
 * Structure for storing transaction id and associated active object.
*/
struct TAsyncRequestInfo
	{

    /**
     * TransactionId
    */
	TInt32 iTransactionId;

    /**
     * Active object pointer
    */
	MCancelAsync* iAsyncObj;
	};	

class CContactService: public CBase
{

public:

    IMPORT_C static CContactService* NewL();
    ~CContactService();
    /**
     * Export a predefined vCard from the contact database into a file.
     *
     * @return Integer indicating requestion submission.
     */
    IMPORT_C void ExportVCardL(MContactCallback* aCallback,
                               TInt aTransId, 
                               const TFileName& aFileName, 
                               const TDesC8& aContactId,
                               const TDesC& aStoreUri=VPbkContactStoreUris::DefaultCntDbUri());

    /**
     * Import a vCard from a predefined file into the contact database.
     *
     * @return Integer indicating requestion submission.
     */
    IMPORT_C void ImportVCardToStoreL(MContactCallback* aCallback,
                                      TInt aTransId, 
                                      const TFileName& aFilename, 
                                      const TDesC& aStoreUri=VPbkContactStoreUris::DefaultCntDbUri());
    
    /**
     * Get the list of entries in the database satisfying the criteria in the SearchVal
     *
     * @return Integer indicating requestion submission.
     */
    IMPORT_C void GetListL(MContactCallback*  aCallback, 
    					   TInt aTransId,
    					   Ttype type,
    					   const TDesC8& aContactId = KNullDesC8,  							
 						   const TDesC& aSearchVal = KNullDesC,
    					   CSearchFields* aSearchFields = NULL,
    					   TOrder aSortOrder = EAsc,
    					   const TDesC& aStoreUri = VPbkContactStoreUris::DefaultCntDbUri(),
    					   TCmdType val = EGetList);
    
    /*
	Get the list of databases currently open
	*/
	IMPORT_C void GetListL(CContactIter& aIter);
    
   /*
    * Called for 1) Adding a new contact/group to the contacts database.
    *            2) Editing a contact/group from the contacts database.
    * @return Integer indicating requestion submission.
    */    
    IMPORT_C void AddL(  MContactCallback* aCallback,
    						 TInt aTransId,
    						 CSingleContact* aContact,
   							 const TDesC8& aGroupId = KNullDesC8,
   							 const TDesC& aGroupLabel = KNullDesC,
   							 const TDesC& aStoreUri = VPbkContactStoreUris::DefaultCntDbUri()); 
   /*
    * Called for deleting a contact/group from the contacts database.
    *
    * @return Integer indicating requestion submission.
    */							 								
    IMPORT_C void DeleteL( MContactCallback* aCallback,
   						   TInt aTransId,
   						   RPointerArray<TDesC8>& aContactIdArray,
   						   const TDesC& aStoreUri = VPbkContactStoreUris::DefaultCntDbUri() );
   						  
   
   /*
    * Called for Associating/Disassociating contacts to/from the group.
    *
    * @return Integer indicating requestion submission.
    */
    IMPORT_C void OrganiseGroupsL(MContactCallback* aCallback,
    								TInt aTransId,
    								const TDesC8& aGroupId,
   								  	RPointerArray<TDesC8>& aContactIdArray,
   								  	TBool aAssociateFlag,
   								    const TDesC& aStoreUri = VPbkContactStoreUris::DefaultCntDbUri() ); 
   								    
   								    
   								    
   	/**
     * Synchronous implementation of Export api.
     *Export a predefined vCard from the contact database into a file.
     *
     * @return Integer indicating requestion submission.
     */							    
    IMPORT_C void ExportVCardL(const TFileName& aFileName,
                               const TDesC8& aContactId,
                               const TDesC& aStoreUri=VPbkContactStoreUris::
                               DefaultCntDbUri() );

    /**
     * Synchronous implementation of Import api.
     * Import a vCard from a predefined file into the contact database.
     *
     * @return Integer indicating requestion submission.
     */
    IMPORT_C void ImportVCardToStoreL(const TFileName& aFilename,
                                      const TDesC& aStoreUri = VPbkContactStoreUris::
                                      DefaultCntDbUri() );

    /**
     * Synchronous implementation of GetList api.
     * Get the list of entries in the database satisfying the criteria in the SearchVal
     *
     * @return Integer indicating requestion submission.
     */
    IMPORT_C CContactIter* GetListL(Ttype type,
                                    const TDesC8& aContactId = KNullDesC8,                                   
                                    const TDesC& aSearchVal=KNullDesC,
                                    CSearchFields* aSearchFields=NULL,
                                    TOrder aSortOrder=EAsc,
                                    const TDesC& aStoreUri=VPbkContactStoreUris::DefaultCntDbUri(),
                                    TCmdType val=EGetList);
    
    /**
     * Synchronous implementation of GetIds api.
     * Get the list of ids of contacts/groups in the database satisfying the criteria in the SearchVal
     *
     * @return Integer indicating requestion submission.
     */
    IMPORT_C
    RPointerArray<HBufC8>& GetIdsL(Ttype atype,                                       
                                            const TDesC& aSearchVal=KNullDesC,
                                            CSearchFields* aSearchFields=NULL,
                                            TOrder aSortOrder = EAsc,
                                            const TDesC& aStoreUri=VPbkContactStoreUris::DefaultCntDbUri(),
                                            TCmdType aval=EGetIds);

	/**
	 * Synchronous implementation of AddL api.
     * Called for 1) Adding a new contact/group to the contacts database.
     *            2) Editing a contact/group from the contacts database.
     * @return Integer indicating requestion submission.
     */
     IMPORT_C HBufC8* AddL(CSingleContact* aContact,
						const TDesC8& aGroupId = KNullDesC8,
						const TDesC& aGroupLabel = KNullDesC,
						const TDesC& aStoreUri = VPbkContactStoreUris::
						DefaultCntDbUri());

    /**
     * Synchronous implementation of DeleteL api.
     * Called for deleting a contact/group from the contacts database.
     *
     * @return Integer indicating requestion submission.
     */
    IMPORT_C void DeleteL(RPointerArray<TDesC8>& aContactIdArray,
       					  const TDesC& aStoreUri = VPbkContactStoreUris::
       					  DefaultCntDbUri() );


    /**
     * Synchronous implementation of OrganiseGroupsL api.
     * Called for Associating/Disassociating contacts to/from the group.
     *
     * @return Integer indicating requestion submission.
     */
    IMPORT_C void OrganiseGroupsL(const TDesC8& aGroupId,
   								  RPointerArray<TDesC8>& aContactIdArray,
   								  TBool aAssociateFlag,
   								  const TDesC& aStoreUri = VPbkContactStoreUris::
   								  DefaultCntDbUri() );
	/**
	 * Cancels asynchronous request
	 * @param aTransactionId     asynchronous transaction id
	 * @param aResult        error code
	 */ 			
	IMPORT_C TInt Cancel( const TInt32 aTransactionId );
   /**
	 * Gets the field key id which is not supported on the current data base
	 * It is only used for sync api's
	 * @return field key ID
	 */
	IMPORT_C TInt GetErrKey();

public :
   const MVPbkFieldTypeList& GetFieldTypes();

   void AddAsyncObjL( const TInt32 aTransactionId, MCancelAsync* aAsyncObj );

   void RequestComplete( const TInt32 aTransactionId );

	/*
	 * Called interanally to get the pointer to ContactManager instance.
	 */
	CVPbkContactManager& GetContactManager();
   
private:

    /*
     * Constructor.
     */
    CContactService();
    /*
     * Symbian Second-phase constructor.
     */
    void ConstructL();
    
    /**
     * Called for setting up the initial parameters for contacts.
     *
     * @return Integer.
     */
    TInt BaseSetupL(const TDesC& aStoreUri);

    TInt VcardStoreOpenL(const TDesC& aStoreUri,
                         MContactStoreListObserver* aStoreObserver);
	 /*
	  * Called for getting a contact store from the contact manager and
	  * opening the database
	  */
    TInt GetContactStoreAndOpenL(const TDesC& aDbUri, 
   								 MVPbkContactStoreObserver* aStoreObserver);
	
private: // Data

    

    /**
     * A pointer to the Virtual Phonebook Engine instance.
     * Own.
     */
    CVPbkVCardEng* iEngine;

    /**
     * A pointer to the Virtual Phonebook Contact Manager instance.
     * Own.
     */
    CVPbkContactManager* iContactManager;

    /**
     * A pointer to a contact store.
     * Not own.
     */
    MVPbkContactStore* iContactStore;
    
   	/*
   	 * Pointer to store contact.
   	 */
   	MVPbkStoreContact* iStoreContact;

    /**
     * A reference to a File Server session.
     */
    RFs iFs;    
    
    TInt iErrKey;		
	/**
	 * Contains handles of all asynchronous requests
	 */ 
	RArray<TAsyncRequestInfo> iAsyncObjArray;

 };
 
 
#endif //// C_CONTACTSERVICE_H
