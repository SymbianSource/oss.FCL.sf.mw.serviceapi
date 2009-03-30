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
* Description:  Store list observer implementation for getlist service api.
*
*/


#include "contactservice.h"
#include <CVPbkContactManager.h>
#include <MVPbkContactStore.h>
#include <barsread.h>//resource reader
#include "contactiter.h"
#include <MVPbkContactViewBase.h>
#include <MVPbkContactViewFiltering.h>
#include <cvpbkcontactviewdefinition.h>
#include <MVPbkContactLink.h>
#include <mvpbkcontactstoreproperties.h>
#include <MVPbkContactOperationBase.h>
#include "contactviewobserver.h"
#include "getliststorelistobserver.h"
#include "contactiter.h"


/*
-------------------------------------------------------------------------------------
CGetListStoreListObserver::Cancel()
Description 		: Cancel implementation relevant to GetListObserver
Return values		: KErrorNone on Success and KErrGeneral on Failure
-------------------------------------------------------------------------------------
*/

void CGetListStoreListObserver::Cancel()
	{
	if(iIter)
		{
		delete iIter;
		iIter = NULL;
		}
	if(iRetOp)
		{
		delete iRetOp;	
		iRetOp = NULL;
		}
	iCallback->HandleReturnValue(EOpCancel, KErrNone, iTransId);
	delete this;	
	}

// ---------------------------------------------------------------------------
// Called By MVPbkContactStoreListObserver indicate the
// the store is ready
// ---------------------------------------------------------------------------
//
void CGetListStoreListObserver::StoreReady( MVPbkContactStore& aContactStore )
{
	iContactStore = &aContactStore;
	TRAPD(error,CreateAndFilterViewL(*iContactStore));
	
	if(error !=KErrNone)
		{
		iContactService->RequestComplete(iTransId);	
		iCallback->HandleReturnValue(EOpComplete, error, iTransId);	
		}
	iContactService->RequestComplete(iTransId);
	if(iType != EOthers)
		delete this;     
}


//----------------------------------------------------------------------------
// First creates the default view of the database, then creates a filtered view for it.
// The fields to be searched in are made a part of the default view.
// And the string to be searched for is used for filtering the view to obtain the results.
// Sorting is taken into consideration for contacts alone.
//----------------------------------------------------------------------------
void CGetListStoreListObserver::CreateAndFilterViewL( MVPbkContactStore& aContactStore)
    {
    
    CVPbkContactManager* contactManager =&(iContactService->GetContactManager());
        
    if(iContactId && iContactId->Compare(KNullDesC8))
    	{
	    CActiveSchedulerWait* schedulerWait = new (ELeave) CActiveSchedulerWait;
	    CleanupStack::PushL(schedulerWait);

		//Extract the contactlink from the contactid
		MVPbkContactLinkArray* linkArray = (contactManager)->CreateLinksLC(*iContactId);
	

		//Set the params for iterator
		iIter->SetParams(linkArray, iUri, EAsc, iTransId, iType, iContactService);

		CContactRetrieveObserver* retrieveObserver = CContactRetrieveObserver::NewL(iIter, 
				    		                               iCallback, 
				    		                               iContactService,
				    		                               iType,
				    		                               iTransId, 
				    		                               schedulerWait);
		
		CleanupStack::PushL(retrieveObserver);
		//Retrieve contact
		iRetOp = (contactManager)->RetrieveContactL((*linkArray)[0],*retrieveObserver );
		iContactService->AddAsyncObjL(iTransId, retrieveObserver);

		CleanupStack::Pop(retrieveObserver);

	    schedulerWait->Start();
		
		iRetOp = NULL;
		CleanupStack::Pop();	
	   	CleanupStack::PopAndDestroy(schedulerWait);
	    }
    else if(iType == EContacts)
        {
   		if(!iSearchFields)
			{
			iFieldsList = CVPbkFieldTypeRefsList::NewL();
			iFieldsList->AppendL(*(contactManager)->FieldTypes().Find(R_VPBK_FIELD_TYPE_LASTNAME));	
			iFieldsList->AppendL(*(contactManager)->FieldTypes().Find(R_VPBK_FIELD_TYPE_FIRSTNAME));	
			}

        CVPbkContactViewDefinition* viewdef = 
        CVPbkContactViewDefinition::NewL();
        CleanupStack::PushL(viewdef);
        
        //Set the Uri on which the view is to be built
        viewdef->SetUriL(iUri);

        CActiveSchedulerWait* schedulerWait = 
        new (ELeave) CActiveSchedulerWait;
        
        CleanupStack::PushL(schedulerWait);
        

        CContactViewObserver* defaultView = 
        CContactViewObserver::NewL(iCallback,
							       EContactDefaultView, 
			 					   iIter,
			 					   iContactService,
			 					   iUri,
			 					   iSortOrder,
			 					   iTransId, 
			 					   schedulerWait);
        CleanupStack::PushL(defaultView);
        if(iSearchVal->Length() <= 0)
    	    {
    	    defaultView->ReturnDefaultView();	
    	    }
    	MVPbkContactViewBase* contactView = NULL;
    	    
    	if(iFieldsList)
        	{
        	//Create the default view for the database
            contactView = 
            contactManager->CreateContactViewLC(*defaultView,
                                                 *viewdef, 
                                                 *iFieldsList);    
        	}
    	else
        	{
        	CVPbkFieldTypeRefsList* fieldList = iSearchFields->GetFieldListL();
        	//Create the default view for the database
        	if(fieldList)
            	{
            	contactView = 
                contactManager->CreateContactViewLC(*defaultView,
                                                     *viewdef, 
                                                     *fieldList);     
            	}
            else
                {
                User::Leave(KErrArgument);    
                }	
              
        	}
		iContactService->AddAsyncObjL(iTransId, defaultView);
		
		schedulerWait->Start();

	if(iSearchVal->Length() > 0) //Filter the view only if searchVal is given
		{
	    // Initialise the Search Strings
	    CDesCArrayFlat* findStrings;
	    findStrings = new(ELeave)CDesCArrayFlat( 10 );
	    CleanupStack::PushL(findStrings); 

	    findStrings->AppendL(*iSearchVal);
	    
	    //Create filtered view of the database
	    CContactViewObserver* filteredView = 
	    CContactViewObserver::NewL(iCallback,
	    						   EContactFilteredView, 
	    						   iIter,
	    						   iContactService,
								   iUri,
								   iSortOrder,
			 					   iTransId, 
			 					   schedulerWait); 
           	    											 					    	    
	    CleanupStack::PushL(filteredView);
	    //Filtering the view to find the iFindStrings
	    MVPbkContactViewBase* findView = 
	    contactView->ViewFiltering()->CreateFilteredViewLC(*filteredView,
	                                                       *findStrings, 
	                                                       NULL);   
		iContactService->AddAsyncObjL(iTransId, filteredView);
	    schedulerWait->Start();
	    CleanupStack::PopAndDestroy();
	   	CleanupStack::PopAndDestroy(filteredView);
	   	CleanupStack::PopAndDestroy(findStrings);
		} 
		CleanupStack::PopAndDestroy();	   	
	   	CleanupStack::PopAndDestroy(defaultView);
	   	CleanupStack::PopAndDestroy(schedulerWait);
	   	CleanupStack::PopAndDestroy(viewdef);
    	 }
    else if(iType == EGroups)
    	{
    	//Get the linkarray of the groups in the database
    	MVPbkContactLinkArray* array = aContactStore.ContactGroupsLC();        	
    	if(array->Count())
        	{
        	//Set the iterator with the result
        	iIter->SetParams(array, iUri, EAsc, iTransId, EGroups, iContactService);
       		
			iContactService->RequestComplete(iTransId);	
       		//Notify the user
       		iCallback->HandleReturnIter(KErrNone, iIter, iTransId);
        	}
    	else
    		{
			iContactService->RequestComplete(iTransId);	
    		//Notify the user
    		iCallback->HandleReturnValue(EOpComplete, KErrNotFound, iTransId);	
    		}    	
    	CleanupStack::Pop();
    	}
    else if(iType == EOthers)
    	{
    	TRequestStatus* status = &(iIter->iSyncIter->iStatus);
    	User::RequestComplete(status, KErrNone);
    	}
    }


// ---------------------------------------------------------------------------
// For a possibility that store might be unavailable.
// Appropriate error code is returned
// ---------------------------------------------------------------------------
void CGetListStoreListObserver::StoreUnavailable(
        MVPbkContactStore& aContactStore,
        TInt aReason )    
	{
    if(iType == EOthers)
    	{
		TRequestStatus* status = &(iIter->iSyncIter->iStatus);
		User::RequestComplete(status, KErrNone);
    	}
	else
		{
		iContactService->RequestComplete(iTransId);	
		//Notify User
		iCallback->HandleReturnValue(EOpError, aReason, iTransId);
		}
    aContactStore.Close(*this);
    delete iIter;
    iIter = NULL;
	delete this;     
	}

// ---------------------------------------------------------------------------
// NewL() method
// ---------------------------------------------------------------------------

CGetListStoreListObserver* CGetListStoreListObserver::
NewL(const TDesC& aUri,
     const TDesC8& aContactId, 
     const TDesC& aSearchVal, 
     CSearchFields* aSearchFields,
     TOrder aSortOrder,
     MContactCallback *aCallback,
      CContactService *aContactService,
     CContactIter* aIter, 
     enum Ttype aType, TInt aTransId,
     MVPbkContactStore* aContactStore)
     
    {
    CGetListStoreListObserver* self = 
    new( ELeave ) CGetListStoreListObserver(aUri,
                                            aContactId, 
                                            aSearchVal, 
                                            aSearchFields, 
                                            aSortOrder,
                                            aCallback,
                                            aContactService,
                                            aIter,
                                            aType, 
                                            aTransId,
                                            aContactStore);    
    self->ConstructL(aContactId, aSearchVal);									 
    return self;
    }


void CGetListStoreListObserver::ConstructL( const TDesC8& aContactId, 
                                            const TDesC& aSearchVal )
    {
    if(&aContactId)
	    {
	    iContactId = HBufC8 :: NewL(aContactId.Length());
	    *iContactId = aContactId;	
	    }
    if(&aSearchVal)
	    {
	    iSearchVal = HBufC :: NewL(aSearchVal.Length());
	    *iSearchVal = aSearchVal;    	
	    }
    }
	
CGetListStoreListObserver::
CGetListStoreListObserver(const TDesC& aUri,const TDesC8& /*aContactId*/,
                          const TDesC& /*aSearchVal*/, 
                          CSearchFields* aSearchFields,
						  TOrder aSortOrder,
						  MContactCallback *aCallback,
						   CContactService *aContactService,
						  CContactIter* aIter, 
						  enum Ttype aType, TInt aTransId,
						  MVPbkContactStore* aContactStore)
    {
	iUri = aUri;			
    iSearchFields = aSearchFields;
    iSortOrder = aSortOrder;
    iCallback=aCallback;
    iContactService = aContactService;
	iIter = aIter;	
	iType = aType;	
	iTransId = aTransId;
	iFieldsList = NULL;
	iRetOp = NULL;
	iContactStore = aContactStore;
    }


CGetListStoreListObserver::~CGetListStoreListObserver()
	{
	if(iSearchFields)
		{
		delete iSearchFields;
		iSearchFields =NULL;	
		}
	delete iFieldsList;	
	delete iContactId;
	delete iSearchVal;	
    if(iContactStore)
       {
       iContactStore->Close(*this); 
       iContactStore = NULL;
       }
	}


void CGetListStoreListObserver::HandleStoreEventL(
        MVPbkContactStore& /*aContactStore*/,
        TVPbkContactStoreEvent /*aStoreEvent*/ )
	{
	}

void CGetListStoreListObserver::OpenComplete()
	{
	}
