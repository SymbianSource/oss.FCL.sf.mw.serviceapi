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
* Description:  
*
*/



#include "contactiter.h"
#include "contactretrieveobserver.h"
#include "contactservice.hrh"
#include "getliststorelistobserver.h"
#include <CVPbkContactStoreUriArray.h>
#include <CVPbkContactManager.h>
#include <mvpbkcontactstorelist.h>
#include <MVPbkContactOperationBase.h>
#include <TVPbkContactStoreUriPtr.h>
#include <MVPbkContactLink.h>
#include <mvpbkcontactstoreproperties.h>


//Initialize the class variable with the result of ReadContactL
void CContactIter::SetContactFetchResult(MVPbkStoreContact* aContact)
    {
	iContact = aContact;
    }		


/**
  * Set the class variables with the parameters sent from CContactViewObserver
  */	
TInt CContactIter::SetParams(MVPbkContactLinkArray * aContactLinkArray,
						 const TDesC& aStoreUri,
						 TOrder aSortOrder,
						 TInt aTransId,
						 Ttype aIndicator,
						 CContactService* aContactService)
    {
	TInt retVal = KErrNone;
	
	iContactLinkArray =aContactLinkArray;
	iCount = aContactLinkArray->Count();
	
	iStoreUri = &aStoreUri;
	iSortOrder = aSortOrder;
	iTransId = aTransId;
	iIndicator = aIndicator;
	iContactService = aContactService;
	TRAPD(error, SetupEnvironL());
	if(error != KErrNone)
		{
		retVal = error;
		}	
	return retVal;
    }


void CContactIter::SetupEnvironL()
    {
	if((iIndicator == EContacts) && (iContactLinkArray->Count() == 1))
	{
	iStoreUri = &(iContactLinkArray->At(0).ContactStore().StoreProperties().Uri().UriDes());
	}

	iSyncIter = CContactSyncIter::NewL();
	SetupDBL();
    }
/*
 * NextL Function gets the next contact/group in the linkarray.
 * Based on the Ascending/Desending order chosen the links are read in that order
 */
 
EXPORT_C void CContactIter::NextL(CSingleContact*& aSingleContact, HBufC8*& aContactID )
    {

	MVPbkContactLink* link = NULL;
	// Create the instance of CContactSyncIter class ,
	// which has methods for making the iterator synchronous
		
	if((iCount>=1) && (iCursor < (iCount-1)) && (iSortOrder == EAsc))
		{

		//Setup the Database before reading
		
     	CContactRetrieveObserver* newObserver = CContactRetrieveObserver::NewL(this);
		CleanupStack::PushL(newObserver);
		// Reads the Contact/Group info
		ReadContactL(((*iContactLinkArray)[++iCursor]), *newObserver);	

		//  for the request to be complete
		iSyncIter->Wait();

		link = const_cast<MVPbkContactLink*>(&((*iContactLinkArray)[iCursor]));
	
		//Set the output param
		aSingleContact = CSingleContact::NewL(iContact, iIndicator);

		//Intialiaze the ContactId info using PackLC() method
		aContactID = link->PackLC();
		aSingleContact->SetContactIdL(*aContactID);
		
		CleanupStack::Pop(aContactID);
		CleanupStack::Pop(newObserver);
		}
	else if(iSortOrder == EDesc) 
		{	   
		if(iCursor == -1)
			{
			iCursor = iCount;
			}
		if(iCursor != 0)
			{
			//Setup the Database before reading
			
			CContactRetrieveObserver* newObserver = CContactRetrieveObserver::NewL(this);
			CleanupStack::PushL(newObserver);

			// Reads the Contact/Group info
			ReadContactL(((*iContactLinkArray)[--iCursor]), *newObserver);	
			
			//  for the request to be complete
			iSyncIter->Wait();

			link = const_cast<MVPbkContactLink*>(&((*iContactLinkArray)[iCursor]));
			
			//Set the output param
			aSingleContact = CSingleContact::NewL(iContact, iIndicator);

			//Intialiaze the ContactId info using PackLC() method
			aContactID = link->PackLC();
			aSingleContact->SetContactIdL(*aContactID);
			
			CleanupStack::Pop(aContactID);
			CleanupStack::Pop(newObserver);
			}
		else
			{		
			aSingleContact = NULL;
			aContactID = KNullDesC8().Alloc();
			}
		}
	else
		{	
		aSingleContact = NULL;
		aContactID = KNullDesC8().Alloc();
		}
	
    }

//Method for reading the next Database name in the list of names
EXPORT_C void CContactIter::NextL(TPtrC& aDbs)
    {
	if(iDbArray.Count())
		{
		if((iCount>=1) && (iCursor < (iCount-1)))
			{
			aDbs.Set(*(iDbArray[++iCursor]));
			}
		else
			{
			aDbs.Set(KNullDesC);	
			}
		}
	else
		{
		aDbs.Set(KNullDesC);	
		}		
    }

//Initialises the cursor
EXPORT_C void CContactIter::Reset()
    {
	iCursor = -1;
    }

//Sets the array of databases and the number of them
void CContactIter::SetDbNamePtr(RPointerArray<HBufC>& aArray, TInt aCnt)
    {
	iIndicator = EDatabase;
	iDbArray= aArray;
	iCount = aCnt;
    }

//Sets up the database before any operation could be performed over it.
void CContactIter::SetupDBL()
{
    CVPbkContactStoreUriArray* uriList = CVPbkContactStoreUriArray::NewLC();
    uriList->AppendL( TVPbkContactStoreUriPtr( *iStoreUri ) );

    User::LeaveIfError( iFs.Connect() );

    iContactManager = CVPbkContactManager::NewL( *uriList ,&iFs );
    
    MVPbkContactStoreList& stores = iContactManager->ContactStoresL();
    
    iContactStore = &( stores.At( (stores.Count())-1 ) );
    
    TDesC16* aSearchVal = NULL;
    TDesC8* cntId = NULL;
    CContactIter* self = this;


	iGetListStoreListObserver = CGetListStoreListObserver::NewL(*iStoreUri,
																	*cntId,
																	*aSearchVal ,
													           		NULL, 
																	ENULL,
																	NULL,
																	iContactService,
																	self,
																	EOthers,
																	iTransId,
																	NULL,
																	EGetList) ;
    if(iContactStore)
    {
    	iContactStore->OpenL( *iGetListStoreListObserver  );    	
    }
    
    //Making opening Database Synchronous
	iSyncIter->Wait();
    
   CleanupStack::PopAndDestroy(uriList);

}


// Method that will go and fetch individual contacts
void CContactIter::ReadContactL( const MVPbkContactLink& aLink, CContactRetrieveObserver& aObserver )
    {
	MVPbkContactOperationBase* ret = iContactManager->RetrieveContactL(aLink,aObserver);
    }    


CContactIter::CContactIter()
    {
    iCursor = iCount = -1;
    iContactLinkArray=NULL;
    iContactManager = NULL; 	
    }	

EXPORT_C CContactIter* CContactIter::NewL()
    {
	return new (ELeave) CContactIter();
    }


CContactIter::~CContactIter()
    {
    if(iGetListStoreListObserver)
	    {
	    delete iGetListStoreListObserver;
	    }
    if(iContactLinkArray)
		{
		delete iContactLinkArray;	
		}
    iFs.Close();
    if(iContactManager)
	    {
	    delete iContactManager;   
	    iContactManager =NULL;	
	    }	
    if(iSyncIter)
    {
       	delete iSyncIter;
		iSyncIter = NULL;
    }
    iDbArray.ResetAndDestroy();
    }

