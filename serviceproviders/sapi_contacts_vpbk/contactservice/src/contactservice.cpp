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
* Description:  Implementation of the Contacts Service APIs.
*
*/


//System includes

#include <CVPbkVCardEng.h>//for the vcard engin
#include <CVPbkContactManager.h>// for iContactManager
#include <MVPbkContactStore.h>// for iContactStore
#include <TVPbkContactStoreUriPtr.h>//used in SetupL
#include <MVPbkContactStoreList.h>//used in SetupL to get contact stores
#include <MVPbkStoreContactField.h>//used in AddFieldToContactL
#include <MVPbkStoreContact.h>// used in many function to get the store contact
#include <MVPbkContactFieldTextData.h>//for the field text data
#include <TVPbkFieldTypeMapping.h>//used in CreateFieldTypeL()
#include <MVPbkFieldType.h>//return type of CreateFieldTypeL()
#include <MVPbkContactOperationBase.h>//for observer
#include <MVPbkContactFieldDateTimeData.h>//Used in AddDateFieldToContactL
#include <MVPbkContactLink.h>//for param in ContactsSaved()
#include <CVPbkContactStoreUriArray.h>//used in SetupL
#include <MVPbkStoreContact.h>		// used in many function to get the store contact
#include <MVPbkContactGroup.h>
#include <badesca.h>
#include <MVPbkContactStoreProperties.h>
#include <TVPbkContactStoreUriPtr.h>
#include <MVPbkContactStore.h>

//User includes.
#include "getliststorelistobserver.h"
#include "addcontactobserver.h"
#include "deletecontactobserver.h"
#include "organisegroupsobserver.h"
#include "contactretrieveobserver.h"
#include "contactservice.h"

class CContactIter;

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Static NewL() method to create an instance of the contact service core class.
// ---------------------------------------------------------------------------

EXPORT_C
CContactService* CContactService::NewL()
    {
    CContactService* self = new( ELeave ) CContactService( );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }


// ---------------------------------------------------------------------------
//  Destructor for CContactService.
// ---------------------------------------------------------------------------

CContactService::~CContactService()
    {
	iFs.Close();
	delete iEngine;
	delete iContactManager;
	for(TInt i = 0; i < iAsyncObjArray.Count(); i++)
		{
		((iAsyncObjArray[i]).iAsyncObj)->Cancel();
		}
	iAsyncObjArray.Close();
    }

// ---------------------------------------------------------------------------
//  Constructor.
// ---------------------------------------------------------------------------

CContactService::CContactService()
                 :iErrKey(0)                
    {

    }


// ---------------------------------------------------------------------------
//  Symbian second-phase constructor
// ---------------------------------------------------------------------------

void CContactService::ConstructL()
    {
    User::LeaveIfError( iFs.Connect() );
    BaseSetupL(VPbkContactStoreUris::DefaultCntDbUri());
    }

//  METHODS
// ---------------------------------------------------------------------------
// Method to setup basic parameters...like creating contact manager instance,
// and initialising the contact store.
// ---------------------------------------------------------------------------

TInt CContactService::BaseSetupL(const TDesC& aStoreUri
                                /*MVPbkContactStoreListObserver* aStoreObserver*/)
    {
    //Create an instance of uriList and append all the list of URIs to the list.

    CVPbkContactStoreUriArray* uriList =
        CVPbkContactStoreUriArray::NewLC();
    uriList->AppendL(TVPbkContactStoreUriPtr(aStoreUri));

    //Instantiate contact manager with the
    //constucted uri list and file session.
    iContactManager = CVPbkContactManager::NewL(*uriList,
                                                &iFs);

    MVPbkContactStoreList& contactStores = iContactManager->ContactStoresL();

    iContactStore = contactStores.Find(aStoreUri);

    CleanupStack::PopAndDestroy(uriList);

    return KErrNone;
    }


//-----------------------------------------------------------------------------------
// Open the store specific to Vcard import and export operations.
//-----------------------------------------------------------------------------------

TInt CContactService::VcardStoreOpenL(const TDesC& aStoreUri,
                                      MContactStoreListObserver* aStoreObserver)
    {
	iContactManager->LoadContactStoreL(TVPbkContactStoreUriPtr(aStoreUri));

    if( !iEngine )
      iEngine = CVPbkVCardEng::NewL( *iContactManager );

     aStoreObserver->SetEngine( iEngine );

    // Open the store
    MVPbkContactStoreList& contactStores = iContactManager->ContactStoresL();

    iContactStore = contactStores.Find(aStoreUri);

    if(!iContactStore)
        {
	    iContactManager->LoadContactStoreL(TVPbkContactStoreUriPtr(aStoreUri));
	    contactStores = iContactManager->ContactStoresL();
	    iContactStore = contactStores.Find(aStoreUri);
        }
    if(iContactStore)
        {
        aStoreObserver->SetContactStore( iContactStore );
    	iContactStore->OpenL( *aStoreObserver );
    	return KErrNone;
        }
	return KErrGeneral;

    }


// ---------------------------------------------------------------------------
// Create data for the operation, prepare the write stream and
// call the vCardEngine to execute the operation. The results are reported
// through callback methods.
// ---------------------------------------------------------------------------
//
EXPORT_C
void CContactService::ExportVCardL(MContactCallback* aCallback,
                                   TInt aTransId,
                                   const TFileName& aFileName,
                                   const TDesC8& aContactId,
                                   const TDesC& aStoreUri)
    {
	//Check for the validity of the arguments.
	if( !aContactId.Compare(KNullDesC8) || NULL == aCallback)
    	{
    	User::Leave(KErrArgument);
    	}
    TInt returncode;
	CExportStoreListObserver* exportObserver =
	    CExportStoreListObserver::NewL(this,
	                                   iFs,
	                                   aFileName,
	                                   aContactId,
	                                   aCallback,
	                                   aTransId);

	CleanupStack::PushL(exportObserver);
	exportObserver->SetContactService(this);
    returncode=VcardStoreOpenL(aStoreUri,
                               exportObserver);
	if(returncode != KErrNone)
		{
    	User::Leave(returncode);
		}
	AddAsyncObjL(aTransId, exportObserver);

    CleanupStack::Pop(exportObserver);
    }


// ---------------------------------------------------------------------------
// Prepare the read stream and call the vCardEngine to execute the operation.
// The results are reported through callback methods.
// ---------------------------------------------------------------------------
//
EXPORT_C
void CContactService::
    ImportVCardToStoreL(MContactCallback* aCallback,
                        TInt aTransId,
                        const TFileName& aFileName,
                        const TDesC& aStoreUri)
    {
	//Check for the validity of the arguments.
	if(NULL == aCallback)
	    {
		User::Leave(KErrArgument);
	    }

    TInt returncode;
    CImportStoreListObserver* importObserver =
        CImportStoreListObserver::NewL(iFs,
                                       aFileName,
                                       aCallback,
                                       aTransId);

    CleanupStack::PushL(importObserver);
    importObserver->SetContactService(this);
    returncode=VcardStoreOpenL(aStoreUri,
                               importObserver);
	if(returncode != KErrNone)
		{
    	User::Leave(returncode);
		}
	AddAsyncObjL(aTransId, importObserver);

    CleanupStack::Pop(importObserver);

    }

// ---------------------------------------------------------------------------
// This method gets the list of contact stores from the contact manager, finds
// the specified database from the list and opens the same with the appropriate
// observer passed to it.
// If it does not found in the list of stores then loads the same and opens it
// asynchronously.
// ---------------------------------------------------------------------------

TInt CContactService::
GetContactStoreAndOpenL(const TDesC& aStoreUri,
						MVPbkContactStoreObserver* aStoreObserver)
    {
    MVPbkContactStoreList& contactStores = iContactManager->ContactStoresL();

    iContactStore = contactStores.Find(aStoreUri);

    if(!iContactStore)
        {
	    iContactManager->LoadContactStoreL(TVPbkContactStoreUriPtr(aStoreUri));
	    contactStores = iContactManager->ContactStoresL();
	    iContactStore = contactStores.Find(aStoreUri);
        }
    if(iContactStore)
        {
    	iContactStore->OpenL( *aStoreObserver );
    	return KErrNone;
        }
	return KErrGeneral;
    }

// ---------------------------------------------------------------------------
// Method which does the following...
// 1. Adding a new contact to the contact store.
// 2. Adding a new group to the contact store.
// 3. Edit an existing contact from the contact store.
// 4. Edit a group from the contact store.
// ---------------------------------------------------------------------------

EXPORT_C
void CContactService::AddL( MContactCallback* aCallback,
							TInt aTransId,
							CSingleContact* aStoreContact,
							const TDesC8& aGroupId,
							const TDesC& aGroupLabel,
							const TDesC& aStoreUri )
    {
	//Check for the validity of the arguments.
	//if no new contact, no reference to exiting contact,
	// no reference to existing grp,
    //no label to new grp then or no callback fn parameter then,
    // leave the fn with the error code KErrArgument.
	if((aStoreContact && aGroupLabel != KNullDesC) || NULL == aCallback )
	    {
		User::Leave(KErrArgument);
	    }

	TInt retVal;

	// Create an instance of addContactObserver
	CAddContactObserver* addContactObserver =
	    CAddContactObserver::NewL(this,
						    	  iContactStore,
								  aStoreContact,
								  aGroupId,
								  aGroupLabel,
								  aTransId,
								  aCallback);

	CleanupStack::PushL(addContactObserver);

	retVal = GetContactStoreAndOpenL(aStoreUri,
	                                 addContactObserver);
	if(retVal != KErrNone)
		{
    	User::Leave(retVal);
		}
	AddAsyncObjL(aTransId, addContactObserver);
	CleanupStack::Pop(addContactObserver);

}


// ---------------------------------------------------------------------------
// Method for deleting a contact or list of contacts from the contact store.
// ---------------------------------------------------------------------------

EXPORT_C
void CContactService::DeleteL( MContactCallback* aCallback,
  							   TInt aTransId,
  							   RPointerArray<TDesC8>& aContactIdArray,
							   const TDesC& aStoreUri )
    {
	//Check for the validity of the arguments.
	if( !aCallback || (aContactIdArray.Count()==0))
	    {
		User::Leave(KErrArgument);
	    }
	TInt retVal;

    //Intantiate delete contact observer for deleting contacts from the contact store.
	CDeleteContactObserver* deleteContactsObserver =
	    CDeleteContactObserver::NewL(this,
									 iContactStore,
									 aContactIdArray,
									 aTransId,
									 aCallback );

	CleanupStack::PushL(deleteContactsObserver);

	retVal = GetContactStoreAndOpenL(aStoreUri,
	                                 deleteContactsObserver);
	if(retVal != KErrNone)
		{
    	User::Leave(retVal);
		}
	AddAsyncObjL(aTransId, deleteContactsObserver);

	CleanupStack::Pop(deleteContactsObserver);

    }


// ---------------------------------------------------------------------------
// Method does the following...
// 1. Associates one or more contacts to the specified group.
// 2. Disassociates one or more contacts from specified group.
// ---------------------------------------------------------------------------

EXPORT_C
void CContactService::OrganiseGroupsL(MContactCallback* aCallback,
								      TInt aTransId,
   						 			  const TDesC8& aGroupId,
   								  	  RPointerArray<TDesC8>& aContactIdArray,
   								  	  TBool aAssociateFlag,
    								  const TDesC& aStoreUri)
    {
	//Check for the validity of the arguments.
	if(!aCallback)
	    {
		User::Leave(KErrArgument);
	    }


	TInt retVal;
    //Create an instance of organise groups observer.
	COrganiseGroupsObserver* organiseGroupsObserver =
	    COrganiseGroupsObserver::NewL(this,
									  aGroupId,
									  aContactIdArray,
									  aAssociateFlag,
									  aTransId,
									  aCallback,
									  iContactStore);

	CleanupStack::PushL(organiseGroupsObserver);

	retVal = GetContactStoreAndOpenL(aStoreUri,
	                                 organiseGroupsObserver);
	if(retVal != KErrNone)
		{
    	User::Leave(retVal);
		}
	AddAsyncObjL(aTransId, organiseGroupsObserver);

	CleanupStack::Pop(organiseGroupsObserver); //organiseGroupsObserver
    }

//---------------------------------------------------
//Based on the kind of request for GetListL fetches a list of either contacts, groups or databases.
//In case of fetching contacts/groups it calls GetContactStoreAndOpenL() for setting up the database before fetching.
//In case of fetching of list of databases it calls GetContactsDatabases()
//In both cases the result is to be iterable.
//It can also be used in retrieving a single contact, in which case iterator is initialized directly.
//---------------------------------------------------
EXPORT_C
void CContactService::GetListL( MContactCallback*  aCallback,
	    						TInt aTransId,
	    						Ttype type,
	    						const TDesC8& aContactId,
	    						const TDesC& aSearchVal,
	    						CSearchFields* aSearchFields,
	    						TOrder aSortOrder,
	    						const TDesC& aStoreUri, TCmdType val)
	{
		TInt retVal = KErrGeneral;
		CContactIter* iter;
		CGetListStoreListObserver* getListOpenObserver;
	    if(!(aCallback))
				{
				User::Leave(KErrArgument);
				}


	    switch(type)
	    	{
	    	case EContacts:
	    	case EGroups:
				if(&aContactId && aContactId.Compare(KNullDesC8))
    				{
					// Create Iterator
					iter = CContactIter::NewL();
					CleanupStack::PushL(iter);

    				//Extract the contactlink from the contactid

					MVPbkContactLinkArray* linkArray = iContactManager->CreateLinksLC(aContactId);
					//Open Store using GetContactStoreAndOpenL()
					//and Create instantiate storelist observer
					getListOpenObserver =
					CGetListStoreListObserver::NewL((linkArray->At(0).
					                                 ContactStore().
					                                 StoreProperties().
					                                 Uri().
					                                 UriDes()),
													 aContactId,
													 aSearchVal,
									        		 aSearchFields,
												 	 aSortOrder,
													 aCallback,
													 this,
													 iter,
													 type,
													 aTransId,
													 iContactStore,val) ;

			        CleanupStack::PushL(getListOpenObserver);

			        //Opens the database and goes to observer's StoreReady() function.
			        retVal = GetContactStoreAndOpenL( aStoreUri, getListOpenObserver );
					if(retVal != KErrNone)
						{
				    	User::Leave(retVal);
						}
					AddAsyncObjL(aTransId, getListOpenObserver);


					CleanupStack::Pop(getListOpenObserver);
					CleanupStack::PopAndDestroy();//CreateLinksLC()
    				CleanupStack::Pop(iter);
					break;

    				}

				// Create Iterator
				iter = CContactIter::NewL();
				CleanupStack::PushL(iter);


				//Open Store using GetContactStoreAndOpenL() and Create
				//instantiate storelist observer
				getListOpenObserver =
				CGetListStoreListObserver::NewL(aStoreUri,
												aContactId,
												aSearchVal,
								        		aSearchFields,
												aSortOrder,
												aCallback,
												this,
												iter,
												type,
												aTransId,
												iContactStore,val) ;
		        CleanupStack::PushL(getListOpenObserver);

		        //Opens the database and goes to observer's StoreReady() function.
		        retVal = GetContactStoreAndOpenL(aStoreUri,
		                                         getListOpenObserver);
				if(retVal != KErrNone)
					{
			    	User::Leave(retVal);
					}
				AddAsyncObjL(aTransId, getListOpenObserver);


		        CleanupStack::Pop(getListOpenObserver);
				CleanupStack::Pop(iter);
			    break;
	    	default:
		    	User::Leave(KErrArgument);
		   	}
	}

//---------------------------------------------------
//Gets the list of databases from the member varible iContactManager
//and reads the data and sets the iterator with the result.
//---------------------------------------------------
EXPORT_C void CContactService::GetListL( CContactIter& aIter )
	{
	HBufC* ptr = NULL;

	//Get the list of stores present
	 TInt count=(iContactManager->ContactStoresL()).Count();

	 RPointerArray<HBufC> array(count);
	 CleanupClosePushL(array);
	 for(int i=0; i<count; i++)
        {
        ptr =
        iContactManager->ContactStoresL().At(i).StoreProperties().Uri().UriDes().AllocL();
        CleanupStack::PushL(ptr);
        array.AppendL(ptr);
        CleanupStack::Pop(ptr);
        }
	 //Set the iterator to point to this array
	 aIter.SetDbNamePtr(array, count);
	 CleanupStack::Pop(&array);
	}


const MVPbkFieldTypeList& CContactService::GetFieldTypes()
    {
	return iContactManager->FieldTypes();
	}


CVPbkContactManager& CContactService::GetContactManager()
	{
	return *iContactManager;
	}


// ---------------------------------------------------------------------------
// Adds asynchronous request object
// ---------------------------------------------------------------------------
//
void CContactService::AddAsyncObjL(const TInt32 aTransactionId,
                                   MCancelAsync* aAsyncObj)
	{
	TAsyncRequestInfo asyncRequestInfo;
	asyncRequestInfo.iTransactionId = aTransactionId;
	asyncRequestInfo.iAsyncObj = aAsyncObj;
	iAsyncObjArray.AppendL( asyncRequestInfo );
	}

// ---------------------------------------------------------------------------
// Cancels asynchronous request
// ---------------------------------------------------------------------------
//
EXPORT_C TInt CContactService::Cancel( const TInt32 aTransactionId )
	{
	TInt pos = iAsyncObjArray.Count() - 1;
	TAsyncRequestInfo obj;
	TInt retVal = KErrNotFound;

	for ( ; pos >= 0; pos-- )
		{
		obj = iAsyncObjArray[pos];
		if( obj.iTransactionId == aTransactionId )
			{
			obj.iAsyncObj->Cancel();
			iAsyncObjArray.Remove(pos);
			iAsyncObjArray.Compress();
			retVal = KErrNone;
			}
		}
	return retVal;
	}
	
// ---------------------------------------------------------------------------
// Gets the unsupported field key ID
// ---------------------------------------------------------------------------
//
EXPORT_C TInt CContactService :: GetErrKey()
    {
    return iErrKey;    
    }
// ---------------------------------------------------------------------------
// Notifies Messaging service about the completeion of the request
// ---------------------------------------------------------------------------
//
void CContactService::RequestComplete( const TInt32 aTransactionId )
	{
	TInt pos = iAsyncObjArray.Count() - 1;
	TAsyncRequestInfo obj;
	for ( ; pos >= 0; pos-- )
		{
		obj = iAsyncObjArray[pos];
		if( obj.iTransactionId == aTransactionId )
			{
			iAsyncObjArray.Remove(pos);
			iAsyncObjArray.Compress();
			return;
			}
		}
	}


//end of file
