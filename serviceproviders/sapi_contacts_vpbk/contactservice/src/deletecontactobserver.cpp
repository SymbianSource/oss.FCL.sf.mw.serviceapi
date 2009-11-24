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
* Description:  Implementation of the delete contact observer functionality.
*
*/


//User Includes
#include "deletecontactobserver.h"
#include "contactcallback.h"

//System Includes
#include <CVPbkContactManager.h>// for iContactManager
#include <MVPbkContactStore.h>// for iContactStore
#include <MVPbkStoreContact.h>// used in many function to get the store contact
#include <MVPbkContactOperationBase.h>//for observer
#include <MVPbkContactLink.h>//for param in ContactsSaved()
#include <MVPbkContactStoreProperties.h>//for getting store uri in StoreReady()

//-------------------------------------------------------------------------------------
// Static method to create instance of delete contact observer.
//-------------------------------------------------------------------------------------

CDeleteContactObserver* CDeleteContactObserver::NewL( CContactService* aContactService,
											 		  MVPbkContactStore* aContactStore, 
											 		  RPointerArray<TDesC8>& aContactIdArray,
											 		  TInt aTransId,
											 		  MContactCallback* aCallback )
{
     
    CDeleteContactObserver* self = new( ELeave ) CDeleteContactObserver( );
    CleanupStack::PushL(self);
    self->ConstructL(aContactService, aContactStore, 
    				 aContactIdArray, aTransId, aCallback );
	CleanupStack::Pop(self);
	return self;
}


//Constructor

CDeleteContactObserver::CDeleteContactObserver()
{
	
}

//second-phase constructor
void CDeleteContactObserver::ConstructL( CContactService* aContactService,
										  		MVPbkContactStore* aContactStore, 
										  		RPointerArray<TDesC8>& aContactIdArray,
										  		TInt aTransId,
										  		MContactCallback* aCallback )
{
	iContactService= aContactService;
	iContactStore = aContactStore;
	iTransId = aTransId;
	iCallback = aCallback;
	
	iContactLinkArray = CVPbkContactLinkArray::NewL();

	ConvertContactIdsToLinkArrayL( aContactIdArray );
	iOp = NULL;
	
}



//Destructor.

CDeleteContactObserver::~CDeleteContactObserver()
{
    TInt count = iLinkArrayToDelete.Count();
    if( count )
        {
        for(TInt index = 0; index < count; index++)
            {
            delete iLinkArrayToDelete[index];
            }
        }
    iLinkArrayToDelete.Reset();
    if(iContactLinkArray)
        {
        iContactLinkArray->Reset();
        delete iContactLinkArray;
        iContactLinkArray = NULL;    
        }        
    if( iContactStore )
        {
        iContactStore->Close(*this);
        }
    if(iOp)
    	{
    	delete iOp;
    	}
}

/*
-------------------------------------------------------------------------------------
CDeleteContactObserver::Cancel()
Description 		: Cancel implementation relevant to DeleteObserver
Return values		: KErrorNone on Success and KErrGeneral on Failure
-------------------------------------------------------------------------------------
*/

void CDeleteContactObserver::Cancel()
	{
	iCallback->HandleReturnValue(EOpCancel, KErrNone, iTransId);
	delete this;	
	}
	
//Get MVPbkContactLinkArray from the dynamic array, which is having contact ids.

void CDeleteContactObserver::ConvertContactIdsToLinkArrayL( RPointerArray<TDesC8>& aContactIdArray )
{

	TInt contactIdCount = aContactIdArray.Count();
	if((contactIdCount) && !(*aContactIdArray[0]).Compare(KNullDesC8))
		{
			User::Leave(KErrArgument);
		}
	
	for(TInt index = 0; index < contactIdCount; index++)
	{
		//get the id from the contact id array
		TPtrC8 contactId = *aContactIdArray[index]; 
		
		//construct link using contact mngr's CreateLinksLC
		MVPbkContactLinkArray* tmpLinkArray = (&(iContactService->GetContactManager()))->CreateLinksLC(contactId);
		
		iLinkArrayToDelete.AppendL(tmpLinkArray);

		iContactLinkArray->AppendL(const_cast<MVPbkContactLink*> (&(tmpLinkArray->At(0))) );		
		
		CleanupStack::Pop(); //tmpLinkArray
	}
	
}



//Deletes the list of contacts from the contact store.
void CDeleteContactObserver::DoDeleteL()
    {
    CVPbkContactManager* contactManager = &(iContactService->GetContactManager());
	MVPbkContactOperationBase* iOp = contactManager ->DeleteContactsL( *iContactLinkArray, *this );
    }


void CDeleteContactObserver::StepComplete( MVPbkContactOperationBase& /*aOperation*/,
                							TInt /*aStepSize*/ )
    {
    	//Ignore this...as it enters OperationComplete once it is done
    }

//deletion failed
TBool CDeleteContactObserver::StepFailed( MVPbkContactOperationBase& aOperation,
                		  				  TInt /*aStepSize*/ , TInt aError )
    {
	delete &aOperation;
	//&aOperation = NULL;
	iContactService->RequestComplete(iTransId);
	iCallback->HandleReturnValue(EOpError, aError, iTransId);
	
	delete this;
	
	return EFalse;
    }

 //successfully deleted.
void CDeleteContactObserver::OperationComplete( MVPbkContactOperationBase& aOperation )
    {
	delete &aOperation;
	//&aOperation = NULL;
	iContactService->RequestComplete(iTransId);
	iCallback->HandleReturnValue(EOpComplete, KErrNone, iTransId);
	delete this;
    }
	
    
//Enters this method when OpenL() is successfull.
void CDeleteContactObserver::StoreReady( MVPbkContactStore& aContactStore )
    {
	iContactStore = &aContactStore;

	if(!iContactLinkArray)
	    {
		iContactService->RequestComplete(iTransId);
		iCallback->HandleReturnValue(EOpComplete, KErrNotFound, iTransId );
		delete this;
	    }

	TRAPD(error, DoDeleteL());
	
	if(error != KErrNone)
	    {
		iContactService->RequestComplete(iTransId);
		iCallback->HandleReturnValue(EOpComplete, error, iTransId);
		delete this;
	    }
	
    }

//Store open failed
void CDeleteContactObserver::StoreUnavailable( MVPbkContactStore& /*aContactStore*/, TInt aReason )
    {
  	iContactService->RequestComplete(iTransId);
	iCallback->HandleReturnValue(EOpError, aReason, iTransId);
	delete this;
    }

void CDeleteContactObserver::HandleStoreEventL( MVPbkContactStore& /*aContactStore*/, TVPbkContactStoreEvent /*aStoreEvent*/ )
    {
    	//do nothing here     	
    }

