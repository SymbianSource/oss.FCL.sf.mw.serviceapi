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
* Description:  Implementation of import observer for Contacts Service API.
*
*/

 


#include "importstorelistobserver.h"

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



// ---------------------------------------------------------------------------
// Static method to create an instance of the import store list observer.
// ---------------------------------------------------------------------------

CImportStoreListObserver* CImportStoreListObserver::
    NewL(RFs &aFs,
         const TFileName& aFileName,
         MContactCallback *aCallback,
         TInt32 aTransId)
    {
    return new( ELeave ) CImportStoreListObserver(aFs,
                                                  aFileName,
                                                  aCallback,
                                                  aTransId);                                                  
    }


// ---------------------------------------------------------------------------
// Destructor 
// ---------------------------------------------------------------------------

CImportStoreListObserver::~CImportStoreListObserver()
    {
    iSource.Close();
    if(iOp)
    	{
    	delete iOp;
    	}
    if(iContactStore)
       {
       iContactStore->Close(*this); 
       }

    }
/*
-------------------------------------------------------------------------------------
CImportStoreListObserver::Cancel()
Description 		: Cancel implementation relevant to ImportObserver
Return values		: KErrorNone on Success and KErrGeneral on Failure
-------------------------------------------------------------------------------------
*/

void CImportStoreListObserver::Cancel()
	{
	iCallback->HandleReturnValue(EOpCancel, KErrNone, iTransId);
	delete this;	
	}

// ---------------------------------------------------------------------------
// Constructor
// ---------------------------------------------------------------------------

CImportStoreListObserver::
    CImportStoreListObserver(RFs &aFs,
                             const TFileName& aFileName,
                             MContactCallback *aCallback,
                             TInt32 aTransId)                                                    
    {
    iFs=aFs;    
    iFileName=aFileName;
    iCallback=aCallback;
    iTransId=aTransId;  
    iOp = NULL;
    }

// ---------------------------------------------------------------------------
// Method to set the vcard engine.
// ---------------------------------------------------------------------------

void CImportStoreListObserver::SetEngine(CVPbkVCardEng* aEngine)
    {
    iEngine=aEngine;
    }

// ---------------------------------------------------------------------------
// Method to set the contact store.
// ---------------------------------------------------------------------------

void CImportStoreListObserver::SetContactStore(MVPbkContactStore* aContactStore)
    {
    iContactStore = aContactStore;
    }

//----------------------------------------------------------------------------
// Method to set the contact service
//----------------------------------------------------------------------------
void CImportStoreListObserver::SetContactService(CContactService* aContactService)
	{
	iContactService = aContactService;
	}
// ---------------------------------------------------------------------------
// Called By MVPbkContactStoreListObserver indicate the
// the store is ready
// ---------------------------------------------------------------------------

void CImportStoreListObserver::StoreReady( MVPbkContactStore& aContactStore )
    {
    TInt error;
    error = iSource.Open( iFs, iFileName, EFileRead );
	if(error !=KErrNone )
    	{
      	iContactService->RequestComplete(iTransId);
		iCallback->HandleReturnValue(EOpComplete, error,iTransId);
		delete this;
    	}
    else
    {
    TRAPD(err,iOp = iEngine->ImportVCardL( aContactStore, iSource, *this ));
    if( err!=KErrNone )
        {
       	iContactService->RequestComplete(iTransId);
		iCallback->HandleReturnValue(EOpComplete, err,iTransId);
		delete this;
        }
    }
    }

// ---------------------------------------------------------------------------
//  Called when OpenL is failed
// ---------------------------------------------------------------------------

void CImportStoreListObserver::StoreUnavailable(
        MVPbkContactStore& aContactStore,
        TInt aReason )    
    {
	if(aReason == KErrNotFound)    
    	{
    	TRAPD(err,aContactStore.ReplaceL(*this));
    	if(err != KErrNone)
        	{
	       	iContactService->RequestComplete(iTransId);
        	iCallback->HandleReturnValue(EOpComplete, err,iTransId);
        	delete this;    
        	}
    	}
    else
        {
       	iContactService->RequestComplete(iTransId);
    	iCallback->HandleReturnValue(EOpError, aReason,iTransId);
    	delete this;
        }  
           
    }

void CImportStoreListObserver::HandleStoreEventL(
        MVPbkContactStore& /*aContactStore*/,
        TVPbkContactStoreEvent /*aStoreEvent*/ )
    {
    // Indication not needed.
    }

void CImportStoreListObserver::OpenComplete()
    {
    // Indication not needed.
    }


// ---------------------------------------------------------------------------
//  Called when field adding to the contact is successful.
// ---------------------------------------------------------------------------

void CImportStoreListObserver::FieldAddedToContact(
        MVPbkContactOperationBase& /*aOperation*/ )
    {
    // Indication not needed. Occurs when setting up the example data.
    }

// ---------------------------------------------------------------------------
// Called when field adding to the contact is failed.
// ---------------------------------------------------------------------------

void CImportStoreListObserver::FieldAddingFailed(
        MVPbkContactOperationBase& /*aOperation*/, TInt /*aError*/ )
    {
    // Indication not needed. Failures in adding example data fields can
    // be ignored.
    }

// ---------------------------------------------------------------------------
// Delete the completed operation object and close the read stream.
// ---------------------------------------------------------------------------

void CImportStoreListObserver::ContactsSaved( MVPbkContactOperationBase& aOp,
        										MVPbkContactLinkArray* aResults )
    {
    delete &aOp;
    iOp = NULL;
    iContactService->RequestComplete(iTransId);
    delete aResults;
    iCallback->HandleReturnValue(EOpComplete, KErrNone,iTransId);
    delete this;
    }


// ---------------------------------------------------------------------------
// Delete the completed operation object and close the read stream.
// ---------------------------------------------------------------------------

void CImportStoreListObserver::ContactsSavingFailed(
        MVPbkContactOperationBase& aOperation, TInt aError )
    {
    delete &aOperation;
    iOp = NULL;
    iContactService->RequestComplete(iTransId);
    iCallback->HandleReturnValue(EOpError, aError,iTransId);
    delete this;
    }
