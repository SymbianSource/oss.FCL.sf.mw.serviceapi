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

#include <MVPbkContactOperationBase.h>
#include "contactservice.h"
#include "contactiter.h"
#include "contactretrieveobserver.h"
#include "contactcallback.h"
//-------------------------------------------
// NewL() Method
//-------------------------------------------
CContactRetrieveObserver* CContactRetrieveObserver::NewL(CContactIter* aIter, MContactCallback* aCallback, CContactService* aContactService, enum Ttype aType, TInt aTransId, CActiveSchedulerWait* aSchedulerWait)
{
    CContactRetrieveObserver* self = new( ELeave ) CContactRetrieveObserver( );
    CleanupStack::PushL( self );
    self->ConstructL(aIter, aCallback, aContactService, aType, aTransId, aSchedulerWait);    
    CleanupStack::Pop( self );
    return self;
	
}

//-------------------------------------------
// ConstructL() Method
//-------------------------------------------
void CContactRetrieveObserver::ConstructL(CContactIter* aIter, MContactCallback* aCallback, CContactService* aContactService, enum Ttype aType, TInt aTransId, CActiveSchedulerWait* aSchedulerWait)
{
	iIter = aIter;
	iCallback = aCallback;
	iContactService = aContactService;
	iType = aType;
	iTransId = aTransId;
	iSchedulerWait = aSchedulerWait;
}

//--------------------------------------------------------------------------------------
// Retrival of the contact was successful
// Results are set in the iterator and RequestComplete is notified. 
//--------------------------------------------------------------------------------------
void CContactRetrieveObserver::VPbkSingleContactOperationComplete(
                MVPbkContactOperationBase& aOperation,
                MVPbkStoreContact* aContact )
{
	delete &aOperation;
	if(iCallback)
		{
		if(iContactService)
			{
			iContactService->RequestComplete(iTransId);	
			}
			
		iSchedulerWait->AsyncStop();
		
		if(((aContact->Group()) && (iType == EGroups)) || (!(aContact->Group()) && (iType == EContacts)))
			{ 
			//Indicate operation complete 
			iCallback->HandleReturnIter(KErrNone, iIter, iTransId);
			}
		else
			{
			iCallback->HandleReturnValue(EOpComplete, KErrArgument, iTransId);
			delete iIter;
			}
		}
	else if(!iCallback)
		{
		//Set the iterator with the result
		iIter->SetContactFetchResult(aContact);
		
		//Set ActiveObject status to RequestComplete
		TRequestStatus* status = &(iIter->iSyncIter->iStatus);
		User::RequestComplete(status, KErrNone);
		}
	delete this;
}

//-------------------------------------------
// In case the retrival was unsuccessful
//-------------------------------------------
void CContactRetrieveObserver::VPbkSingleContactOperationFailed(
                MVPbkContactOperationBase& aOperation, 
                TInt aError)
{
	delete &aOperation;
	if(!iCallback)
		{
		//Set the iterator with the result
		iIter->SetContactFetchResult(NULL);
		
		//Set ActiveObject status to RequestComplete
		TRequestStatus* status = &(iIter->iSyncIter->iStatus);
		User::RequestComplete(status, KErrNone);
		}
	else
		{
		if(iContactService)
			{
			iContactService->RequestComplete(iTransId);	
			}
		iSchedulerWait->AsyncStop();		
		//Indicate operation failure
		iCallback->HandleReturnValue(EOpError, aError, iTransId);	
		delete iIter;
		iIter = NULL;
		}
	delete this;
}


/*
-------------------------------------------------------------------------------------
CContactViewObserver::Cancel()
Description 		: Cancel implementation relevant to ViewObserver
Return values		: KErrorNone on Success and KErrGeneral on Failure
-------------------------------------------------------------------------------------
*/

void CContactRetrieveObserver::Cancel()
	{
	iCallback->HandleReturnValue(EOpCancel, KErrNone, iTransId);
	delete this;	
	}
	
