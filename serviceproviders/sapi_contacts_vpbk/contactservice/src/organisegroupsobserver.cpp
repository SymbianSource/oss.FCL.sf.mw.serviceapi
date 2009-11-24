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
* Description:  Implementation of the organise groups observer functionality.
*
*/


//User includes
#include "organisegroupsobserver.h"
#include "contactcallback.h"

//System include
#include <CVPbkContactManager.h>// for iContactManager
#include <MVPbkContactStore.h>// for iContactStore
#include <MVPbkStoreContact.h>// used in many function to get the store contact
#include <MVPbkContactOperationBase.h>//for observer
#include <MVPbkContactLink.h>//for param in ContactsSaved()
#include <MVPbkContactGroup.h>
#include <CVPbkContactLinkArray.h>


//-------------------------------------------------------------------------------------
// Static method to create instance of organise groups observer.
//-------------------------------------------------------------------------------------

COrganiseGroupsObserver* COrganiseGroupsObserver::NewL(  CContactService* aContactService,
														  const TDesC8& aGroupId, 
												 		  RPointerArray<TDesC8>& aContactIdArray,
												 		  TBool aAssociateFlag,
												 		  TInt aTransId,
												 		  MContactCallback* aCallback,
												 		  MVPbkContactStore* aContactStore ) 
    {
    
    COrganiseGroupsObserver* self = new( ELeave ) COrganiseGroupsObserver( );
    CleanupStack::PushL(self);
    self->ConstructL(aContactService, aGroupId, 
    				 aContactIdArray, aAssociateFlag, aTransId, aCallback, aContactStore );
	CleanupStack::Pop(self);
	return self;

    }

//Constructor.
COrganiseGroupsObserver::COrganiseGroupsObserver()
    {
    }

//second-phase constructor
void COrganiseGroupsObserver::ConstructL( CContactService* aContactService,
	    						const TDesC8& aGroupId , 
	    						RPointerArray<TDesC8>& aContactIdArray,
	    						TBool aAssociateFlag,
	    						TInt aTransId,
	    						MContactCallback* aCallback,
				                MVPbkContactStore* aContactStore )
    {
	iContactService = aContactService;
	iGroupId = HBufC8 :: NewL(aGroupId.Length());
	*iGroupId = aGroupId;
	iAssociateFlag = aAssociateFlag;
	iTransId = aTransId;
	iCallback = aCallback;
    iContactStore = aContactStore;
	iContactLinkArray = CVPbkContactLinkArray::NewL();
    iContactManager = &(iContactService->GetContactManager());
	ConvertContactIdsToLinkArrayL( aContactIdArray );
	iOp =NULL;
    }

/*
-------------------------------------------------------------------------------------
COrganiseGroupsObserver::Cancel()
Description 		: Cancel implementation relevant to OrganiseObserver
Return values		: KErrorNone on Success and KErrGeneral on Failure
-------------------------------------------------------------------------------------
*/

void COrganiseGroupsObserver::Cancel()
	{
	iCallback->HandleReturnValue(EOpCancel, KErrNone, iTransId);
	delete this;	
	}
    
//Get MVPbkContactLinkArray from the dynamic array, which is having contact ids.

void COrganiseGroupsObserver::ConvertContactIdsToLinkArrayL( RPointerArray<TDesC8>& aContactIdArray )
    {
	TInt contactIdCount = aContactIdArray.Count();		

	for(TInt index = 0; index < contactIdCount; index++)
	    {
		//get the id from the contact id array
		TPtrC8 contactId = *aContactIdArray[index]; 
		
		//construct link using contact mngr's CreateLinksLC
		MVPbkContactLinkArray* tmpLinkArray = iContactManager->CreateLinksLC(contactId);
		
		iLinkArrayToDelete.AppendL(tmpLinkArray);

		iContactLinkArray->AppendL(const_cast<MVPbkContactLink*> (&(tmpLinkArray->At(0))) );		
		
		CleanupStack::Pop(); //tmpLinkArray
	    }
	
    }



//Destructor.
COrganiseGroupsObserver::~COrganiseGroupsObserver()
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
    delete iLinkArray;
    if(iOp)
    	{
    	delete iOp;
    	}
    if(iContactStore)
    	{
    	iContactStore->Close(*this);    	
    	}
    delete iGroupId;        
    }

//DoGetGroupL : gets the group from the contact manager.
void COrganiseGroupsObserver::DoGetGroupL()
    {
	iLinkArray = iContactManager->CreateLinksLC( *iGroupId );

	iOp = iContactManager->RetrieveContactL( iLinkArray->At(0), *this );
	
	CleanupStack::Pop();
    }
	    
//Enteres when OpenL() is successfull
void COrganiseGroupsObserver::StoreReady( MVPbkContactStore& /*aContactStore*/ )
    {
	TRAPD(error,DoGetGroupL());

	if(error != KErrNone)
	    {
      	iContactService->RequestComplete(iTransId);
		iCallback->HandleReturnValue(EOpComplete, error, iTransId);
		delete this;
	    }
    }

//Eneters when OpenL() fails.
void COrganiseGroupsObserver::StoreUnavailable( MVPbkContactStore& /*aContactStore*/, TInt aReason )
    {
  	iContactService->RequestComplete(iTransId);
	iCallback->HandleReturnValue(EOpError, aReason, iTransId);
	
	delete this;
    }

void COrganiseGroupsObserver::HandleStoreEventL( MVPbkContactStore& /*aContactStore*/, TVPbkContactStoreEvent /*aStoreEvent*/ )
    {
    	//do nothing here     	
    }


//Associtates/Disassociates list of contacts to/from the group.
void COrganiseGroupsObserver::DoOrganiseGroupsL(MVPbkStoreContact* aContact)
    {
	MVPbkContactGroup* groupPtr = aContact->Group();
	if( !groupPtr )
	{
		User::Leave(KErrNotFound);
	}	
	
	TInt linkCount = iContactLinkArray->Count();
	if(iAssociateFlag)
	{
		for(TInt index = 0; index < linkCount; index++)
		{
			groupPtr->AddContactL(iContactLinkArray->At(index));
		}
	}
	else
	{
		for(TInt index = 0; index < linkCount; index++)
		{
			groupPtr->RemoveContactL(iContactLinkArray->At(index));
		}
	}
    delete groupPtr;
    }

//Single contact operation observer methods
void COrganiseGroupsObserver::VPbkSingleContactOperationComplete( MVPbkContactOperationBase& aOperation,
                						 MVPbkStoreContact* aContact)
    {
	delete &aOperation;
	iOp = NULL;
	iContactService->RequestComplete(iTransId);

	TRAPD(error, DoOrganiseGroupsL(aContact));
		
	iCallback->HandleReturnValue(EOpComplete, error, iTransId);
	
	delete this;
    }


void COrganiseGroupsObserver::VPbkSingleContactOperationFailed( MVPbkContactOperationBase& aOperation, 
                					   TInt aError)
    {	
	delete &aOperation;
	iOp = NULL;
	iContactService->RequestComplete(iTransId);
	
	iCallback->HandleReturnValue(EOpError, aError, iTransId);	
	delete this;
    }

