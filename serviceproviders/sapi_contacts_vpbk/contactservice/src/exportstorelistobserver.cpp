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
* Description:  Implementation of export observer for the Contacts Service API.
*
*/

 

#include "exportstorelistobserver.h"

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
// Static method to create an instance of the export store list observer.
// ---------------------------------------------------------------------------
//
CExportStoreListObserver* CExportStoreListObserver::NewL(CContactService* aContactService,RFs &aFs,const TFileName& aFileName, const TDesC8& aContactId,MContactCallback *aCallback, TInt aTransId)
    {
	CExportStoreListObserver* self = new( ELeave ) CExportStoreListObserver( );
    CleanupStack::PushL(self);
    self->ConstructL(aContactService,aFs,aFileName,aContactId,aCallback, aTransId );
	CleanupStack::Pop(self);
	return self;

    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
CExportStoreListObserver::~CExportStoreListObserver()
    {   
    iDest.Close(); 
    delete iLinkArray;
	if(iOp)
		{
		delete iOp;
		}
    if(iContactStore)
       {
       iContactStore->Close(*this); 
       }

    }

// ---------------------------------------------------------------------------
// Constructor
// ---------------------------------------------------------------------------
CExportStoreListObserver::CExportStoreListObserver()
    {   
        
    }

//----------------------------------------------------------------------------
// Symbian Second phase constructor
//----------------------------------------------------------------------------

void CExportStoreListObserver::ConstructL( CContactService* aContactService, RFs &aFs,const TFileName& aFileName,const TDesC8& aContactId,MContactCallback *aCallback, TInt aTransId) 
    {
    iFs=aFs;
    iFileName=aFileName;
    
    iLinkArray = (&(aContactService->GetContactManager()))->CreateLinksLC(aContactId);
	iContactLink = &(iLinkArray->At(0));
    
    iCallback=aCallback;
    iTransId = aTransId;
    iOp = NULL;
    CleanupStack::Pop(); //iLinkArray
    }
/*
-------------------------------------------------------------------------------------
CExportStoreListObserver::Cancel()
Description 		: Cancel implementation relevant to Export Observer
Return values		: KErrorNone on Success and KErrGeneral on Failure
-------------------------------------------------------------------------------------
*/

void CExportStoreListObserver::Cancel()
	{
	iCallback->HandleReturnValue(EOpCancel, KErrNone, iTransId);
	delete this;	
	}

// ---------------------------------------------------------------------------
// Method to set vcard engine.
// ---------------------------------------------------------------------------

void CExportStoreListObserver::SetEngine(CVPbkVCardEng* aEngine)
    {
    iEngine=aEngine;
    }

// ---------------------------------------------------------------------------
// Method to set the contact store.
// ---------------------------------------------------------------------------

void CExportStoreListObserver::SetContactStore(MVPbkContactStore* aContactStore)
    {
     iContactStore=aContactStore;
    }

//----------------------------------------------------------------------------
// Method to set the contact service
//----------------------------------------------------------------------------
void CExportStoreListObserver::SetContactService(CContactService* aContactService)
	{
	iContactService = aContactService;
	}

// ---------------------------------------------------------------------------
// Called when OpenL async call is successfull. 
// ---------------------------------------------------------------------------

void CExportStoreListObserver::StoreReady( MVPbkContactStore& /* aContactStore */)
    {
    TInt error;
    error = iDest.Create( iFs, iFileName, EFileWrite );
	if(error != KErrNone)
	    {
      	iContactService->RequestComplete(iTransId);
	 	iCallback->HandleReturnValue( EOpComplete, error, iTransId );
	 	delete this;
	    }
	else
	    {
    	TRAPD(err,iOp = iEngine->ExportVCardL( iDest, *iContactLink, *this ));
        if( err!=KErrNone )
            {
           	iContactService->RequestComplete(iTransId);
    		iCallback->HandleReturnValue(EOpComplete, err,iTransId);
    		delete this;
            }
	    }
    }

// ---------------------------------------------------------------------------
// Called when OpenL is failed.
// ---------------------------------------------------------------------------

void CExportStoreListObserver::StoreUnavailable(
        MVPbkContactStore& /*aContactStore*/,
        TInt aReason )    
    {
  	iContactService->RequestComplete(iTransId);
	iCallback->HandleReturnValue(EOpError, aReason, iTransId );
	delete this;
    }

// ---------------------------------------------------------------------------
// 
// ---------------------------------------------------------------------------

void CExportStoreListObserver::HandleStoreEventL(
        MVPbkContactStore& /*aContactStore*/,
        TVPbkContactStoreEvent /*aStoreEvent*/ )
    {
    // Indication not needed.
    }

void CExportStoreListObserver::OpenComplete()
    {
    // Indication not needed.
    }


// ---------------------------------------------------------------------------
// Delete the completed operation object and close the write stream.
// ---------------------------------------------------------------------------

void CExportStoreListObserver::VPbkSingleContactOperationComplete(
        MVPbkContactOperationBase& aOperation,
        MVPbkStoreContact* )
    {
	delete &aOperation;
	iOp = NULL;
	iContactService->RequestComplete(iTransId);
	iCallback->HandleReturnValue(EOpComplete, KErrNone,iTransId);
	delete this;
    }

// ---------------------------------------------------------------------------
// Delete the completed operation object and close the write stream.
// ---------------------------------------------------------------------------

void CExportStoreListObserver::VPbkSingleContactOperationFailed(
        MVPbkContactOperationBase& aOperation, TInt aError )
    {
	delete &aOperation;
	iOp = NULL;
	iContactService->RequestComplete(iTransId);	
	iCallback->HandleReturnValue( EOpError, aError, iTransId );
	delete this;
    }
