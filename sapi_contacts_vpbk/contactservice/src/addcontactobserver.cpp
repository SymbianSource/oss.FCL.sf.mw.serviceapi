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
* Description:  Implementation of the add contact observer functionality.
*
*/


//User include
#include "addcontactobserver.h"
#include "contactcallback.h"

//System include 
#include "contactservice.h"// for iContactService
#include <mvpbkcontactstore.h>// for iContactStore
#include <mvpbkstorecontact.h>// used in many function to get the store contact
#include <mvpbkcontactoperationbase.h>//for observer
#include <mvpbkcontactlink.h>//for param in ContactsSaved()
#include <MVPbkContactGroup.h>
#include <MVPbkContactFieldTextData.h>
#include <MVPbkContactFieldData.h>
#include <MVPbkContactFieldBinaryData.h>
#include <MVPbkContactFieldDateTimeData.h>

/*
-------------------------------------------------------------------------------------
CAddContactObserver::NewL( CContactService* aContactService,
											 	MVPbkContactStore* aContactStore, 
											 	CSingleContact* aStoreContact,
											 	const TDesC8& aGroupId,
											 	const TDesC& aGroupLabel,
											 	TInt aTransId,
											 	MContactCallback* aCallback)
Description        : Static method to create instance of add contact observer.
Return values      : CAddContactObserver*
-------------------------------------------------------------------------------------
*/
CAddContactObserver* CAddContactObserver::NewL(CContactService* aContactService,
											   MVPbkContactStore* aContactStore, 
											   CSingleContact* aStoreContact,
											   const TDesC8& aGroupId,
											   const TDesC& aGroupLabel,
											   TInt aTransId,
											   MContactCallback* aCallback)
    {
     
    CAddContactObserver* self =  new( ELeave )
                                 CAddContactObserver(aContactService, 
        										     aContactStore, 
        										     aStoreContact,        										     
        										     aTransId,
        										     aCallback);
        										             										     
        										     
    CleanupStack::PushL(self);            										     
    self->ConstructL(aGroupId,aGroupLabel);    										   
    CleanupStack::Pop(self);										   
    return self;
    }

/*
-------------------------------------------------------------------------------------
CAddContactObserver::CAddContactObserver(CVPbkContactManager* aContactManager, 
									    MVPbkContactStore* aContactStore, 
									    CSingleContact* aStoreContact,										 
									    TInt aTransId,
									    MContactCallback* aCallback)
Description        : This is the default constructor
Return values      : N/A										    
-------------------------------------------------------------------------------------
*/

CAddContactObserver::CAddContactObserver( CContactService* aContactService,
										  MVPbkContactStore* aContactStore, 
										  CSingleContact* aStoreContact,										 
										  TInt aTransId,
										  MContactCallback* aCallback )
    {
    iContactService = aContactService;
    iContactStore = aContactStore;
    iStoreContact = aStoreContact;    
    iGroupId = NULL;    
    iGroupLabel = NULL;    
    iTransId = aTransId;
    iCallback = aCallback;
    iLockFlag = EFalse;
    iContact = NULL;
    iGroup = NULL;
    iOp = NULL;
    iErrorID = 0;    
    }

void CAddContactObserver::ConstructL(const TDesC8& aGroupId,
    							     const TDesC& aGroupLabel)
    {
    iGroupId = HBufC8 :: NewL(aGroupId.Length());
    *iGroupId = aGroupId;
    
    iGroupLabel = HBufC :: NewL(aGroupLabel.Length());
    *iGroupLabel = aGroupLabel;    
    }
    						
    							
/*
-------------------------------------------------------------------------------------
CAddContactObserver::~CAddContactObserver()
Description        : Destructor
Return values      : N/A										    
-------------------------------------------------------------------------------------
*/

CAddContactObserver::~CAddContactObserver()
    {
    delete iGroupId;
    delete iGroupLabel;
    delete iContact;
  	delete iGroup;
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
CAddContactObserver::Cancel()
Description 		: Cancel implementation relevant to AddObserver
Return values		: KErrorNone on Success and KErrGeneral on Failure
-------------------------------------------------------------------------------------
*/

void CAddContactObserver::Cancel()
	{
	iCallback->HandleReturnValue(EOpCancel, KErrNone, iTransId);
	delete this;	
	}
	
/*
-------------------------------------------------------------------------------------
CAddContactObserver::CreateAndAddFieldToContactL()
Description        : This method creates the contact field and adds to the data base.
Return values      : N/A										    
-------------------------------------------------------------------------------------
*/
void CAddContactObserver::CreateAndAddFieldToContactL()
    {
    TPtrC8 fieldKey(KNullDesC8);
    TPtrC  label(KNullDesC); 
    TPtrC  value(KNullDesC);    
    iErrorID = 0;
    
    TInt fieldCount = iStoreContact->FieldCount();
	const CVPbkContactManager* contactManager = &(iContactService->GetContactManager());
    for(TInt index = 0; index < fieldCount; index++)
    {
    CSingleContactField* field = iStoreContact->FieldAt(index);

    field->GetFieldDataL(fieldKey, label, value);
    TInt fieldTypeResId = CSearchFields::GetIdFromFieldKey(fieldKey);
    iErrorID =  fieldTypeResId;        
    MVPbkStoreContactField* cntField = 
    			iContact->CreateFieldLC( * contactManager->FieldTypes().Find( fieldTypeResId ) );
    			
    iErrorID = 0;
            
    TVPbkFieldStorageType storageType = cntField->FieldData().DataType();

    if( EVPbkFieldStorageTypeBinary == storageType )
    	{        
        //(MVPbkContactFieldBinaryData::Cast(cntField->FieldData())).SetBinaryDataL( value8bit );
    	}
    else if( EVPbkFieldStorageTypeDateTime == storageType )
    	{
    	TTime timeVal = field->GetDateTime();
    	(MVPbkContactFieldDateTimeData::Cast(cntField->FieldData())).SetDateTime( timeVal );
    	}
    else
    	{
    	(MVPbkContactFieldTextData::Cast(cntField->FieldData())).SetTextL( value );
    	}

	TRAP_IGNORE(cntField->SetFieldLabelL(label));

    iContact->AddFieldL(cntField);

    CleanupStack::Pop(); //cntField
    }
    }


/*
-------------------------------------------------------------------------------------
CAddContactObserver::DoAddL()
Description        : Called for 1) Adding a new contact/group to the contacts database.
                                2) Editing a contact/group from the contacts database.
Return values      : N/A                               
-------------------------------------------------------------------------------------
*/
void CAddContactObserver::DoAddL()
    {
    //if iStoreContact is non-null pointer then it is a new contact or existing contact.
    if( iStoreContact )
        {
        //get contact id from the contact.
    	TPtrC8 cntId = iStoreContact->GetContactId();
    	//If cntId is null then it is new contact, get the fields from the CSingleContact
    	//create new contact, add the fields to it and commit the contact.
    	if( cntId == KNullDesC8 )
            {
            iContact = iContactStore->CreateNewContactLC();
            CleanupStack::Pop(); //contact

            CreateAndAddFieldToContactL();

            iContact->CommitL(*this);

            }
    	else //Edit contact : retrieve contact and update the fields and commit.
        	{
        	const CVPbkContactManager* contactManager = &(iContactService->GetContactManager());
    		MVPbkContactLinkArray* linkArray = contactManager->CreateLinksLC(cntId);
    		const MVPbkContactLink* link = &(linkArray->At(0));
    		CleanupStack::Pop(); //linkArray
    		MVPbkContactOperationBase* iOp =contactManager->RetrieveContactL(*link, *this);
        	}
    }
    //group id is not null and grp label is not null then exiting grp, 
    //retrieve the grp,and edit the label.
    else if( *iGroupId != KNullDesC8 && *iGroupLabel != KNullDesC )
        {
        const CVPbkContactManager* contactManager = &(iContactService->GetContactManager());
    	MVPbkContactLinkArray* linkArray = contactManager->CreateLinksLC(*iGroupId);
    	const MVPbkContactLink* link = &(linkArray->At(0));
    	CleanupStack::Pop(); //linkArray
    	contactManager->RetrieveContactL(*link, *this);
        }
    //if grp id is null and grp label is non-null then, create new grp and set the label.
    else if( *iGroupId == KNullDesC8 && *iGroupLabel != KNullDesC )
        {
    	iGroup = iContactStore->CreateNewContactGroupLC();
    	iGroup->SetGroupLabelL(*iGroupLabel);
    	iGroup->CommitL( *this );
    	CleanupStack::Pop(); //group
        }
    }

/*
-------------------------------------------------------------------------------------
CAddContactObserver::DoCommitL()
Description        : Commit contact to the contacts database.
Return values      : TInt                               
-------------------------------------------------------------------------------------
*/
TInt CAddContactObserver::DoCommitL( TContactOpResult aResult )
    {
    TInt retVal = KErrGeneral;
	
	//if lockflag is true, opcode is EContactLock, group id is not null 
	//and grp label is not null then exiting grp, get ptr to grp from 
	//contact and edit the label and commit the same.
	if( iLockFlag && 
		aResult.iOpCode == EContactLock && 
		((*iGroupId != KNullDesC8) && (*iGroupLabel != KNullDesC)) )
    	{
		(iContact->Group())->SetGroupLabelL(*iGroupLabel);
	    (iContact->Group())->CommitL(*this);
		//set lock flag to false, as it is done.
		iLockFlag = EFalse;
		//set return value to ErrNone...completed successfully.
	    retVal = KErrNone;
    	}	
	//lock is success, so update the fields in the contact and commit.
	else if( iLockFlag && aResult.iOpCode == EContactLock )
	    {	
		//remove all the fields from the original contact.
		iContact->RemoveAllFields();
		
		//add new fields to the contact;
		CreateAndAddFieldToContactL( );
		
		//added all the fields...commit the contact.
		iContact->CommitL( *this );
		//set lock flag to false, as it is done.
		iLockFlag = EFalse;
		//set return value to ErrNone...completed successfully.
		retVal = KErrNone;
	    }
	else if( aResult.iOpCode == EContactCommit )
	    {
		retVal = KErrNone; 
    	}
	
	return retVal;
    }
    
/*
-------------------------------------------------------------------------------------
void CAddContactObserver::DoEditContactOrGroupL(MVPbkStoreContact* aContact)
Description        : This method is used to edit the group,it locks 
                     the contact to be edited and performs the edit operation.
Return values      : N/A                                
-------------------------------------------------------------------------------------
*/
void CAddContactObserver::DoEditContactOrGroupL(MVPbkStoreContact* aContact)
    {
	//Edit contact : lock the contact for edit operation.
	iLockFlag = ETrue;
	aContact->LockL(*this);
	if(!iContact )
		{
		iContact = aContact;    
		}
    }


/*
-------------------------------------------------------------------------------------
CAddContactObserver::ContactOperationCompleted( TContactOpResult aResult )
Description        : Virtual Phonebook Observer method called back once 
                     the contact operation is completed successfully.
Return values      : N/A                                
-------------------------------------------------------------------------------------
*/
void CAddContactObserver::ContactOperationCompleted( TContactOpResult aResult )
    {
	//if lock operation is successfull then it enters here...
	//call DoCommitL(), to commit the contact into the contact store.
	TRAPD(error, error = DoCommitL(aResult));

	//notify the user with the status of the operation.
	if((aResult.iOpCode != EContactLock) || (error != KErrNone))
	    {
    	iContactService->RequestComplete(iTransId);
		iCallback->HandleReturnValue(EOpComplete, error, iTransId);
		delete this;
    	}
    }

/*
-------------------------------------------------------------------------------------
CAddContactObserver::ContactOperationFailed(TContactOp aOpCode, 
                                            TInt aErrorCode, 
                                            TBool aErrorNotified)
Description        : Virtual Phonebook Observer method called back if 
                     the contact operation is Failed.
Return values      : N/A                               
-------------------------------------------------------------------------------------
*/
void CAddContactObserver::ContactOperationFailed(TContactOp /*aOpCode*/, 
                                                 TInt aErrorCode, 
                                                 TBool /*aErrorNotified*/)
    {
	//operation failed....handle the error
	iContactService->RequestComplete(iTransId);
	iCallback->HandleReturnValue(EOpError, aErrorCode, iTransId);
	delete this;
    }

/*
-------------------------------------------------------------------------------------
CAddContactObserver::ContactOperationFailed(TContactOp aOpCode, 
                                            TInt aErrorCode, 
                                            TBool aErrorNotified)
Description        : Virtual Phonebook Observer method called back when OpenL(),
                     the database open operation is successfull.
Return values      : N/A                                
-------------------------------------------------------------------------------------
*/	    
void CAddContactObserver::StoreReady(MVPbkContactStore& aContactStore)
    {
	iContactStore = &aContactStore;
	
	TRAPD(error, DoAddL());
    	
    if( error !=  KErrNone )
        {        
       	iContactService->RequestComplete(iTransId);
       	if(error == KErrNotSupported && iErrorID != 0)
            {                        
            iCallback->HandleReturnValue(EInvalidKey, iErrorID, iTransId);    
            }            
        else
            {
            iCallback->HandleReturnValue(EOpComplete, error, iTransId);    
            }    
        
        delete this;
        }

    }

/*
-------------------------------------------------------------------------------------
CAddContactObserver::StoreUnavailable(MVPbkContactStore& aContactStore,
                                           TInt aReason)
Description        : Virtual Phonebook Observer method called back when OpenL(),
                     the database open operation is failed due to unavailable store.
Return values      : N/A                                
-------------------------------------------------------------------------------------
*/	 
void CAddContactObserver::StoreUnavailable(MVPbkContactStore& /*aContactStore*/,
                                           TInt aReason)
    {
	//store open failed.....handle the error
	iContactService->RequestComplete(iTransId);
	iCallback->HandleReturnValue(EOpError, aReason, iTransId);
	
	delete this;
    }
    
/*
-------------------------------------------------------------------------------------
CAddContactObserver::HandleStoreEventL(MVPbkContactStore& aContactStore, 
                                       TVPbkContactStoreEvent aStoreEvent)
Description        : Virtual Phonebook Observer method Not used here.                     
Return values      : N/A                                
-------------------------------------------------------------------------------------
*/	 
void CAddContactObserver::HandleStoreEventL(MVPbkContactStore& /*aContactStore*/, 
                                            TVPbkContactStoreEvent /*aStoreEvent*/)
    {
    	//do nothing here     	
    }

/*
-------------------------------------------------------------------------------------
CAddContactObserver::VPbkSingleContactOperationComplete
                        (MVPbkContactOperationBase& aOperation,
                		 MVPbkStoreContact* aContact)
Description        : Virtual Phonebook Observer method called back when
                     Single Contact Operation completes successfully..
Return values      : N/A                                
-------------------------------------------------------------------------------------
*/

void CAddContactObserver::VPbkSingleContactOperationComplete
                          (MVPbkContactOperationBase& aOperation,
                		  MVPbkStoreContact* aContact)
                        
    {
	delete &aOperation;
	TRAPD(error, DoEditContactOrGroupL(aContact));
	if(KErrNone != error)
	    {
    	iContactService->RequestComplete(iTransId);
		iCallback->HandleReturnValue(EOpComplete, error, iTransId);
		delete this;
	    }
    }

/*
-------------------------------------------------------------------------------------
CAddContactObserver::VPbkSingleContactOperationFailed
                          (MVPbkContactOperationBase& aOperation, 
        				   TInt aError)
Description        : Virtual Phonebook Observer method called back when
                     Single Contact Operation fails.
Return values      : N/A                                
-------------------------------------------------------------------------------------
*/
void CAddContactObserver::VPbkSingleContactOperationFailed
                          (MVPbkContactOperationBase& aOperation, 
        				   TInt aError)
    {
	delete &aOperation;
	iContactService->RequestComplete(iTransId);
	iCallback->HandleReturnValue(EOpError, aError, iTransId);
	
	delete this;
    }
