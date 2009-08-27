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


#include <CVPbkContactLinkArray.h>
#include <MVPbkContactViewBase.h>

#include "contactiter.h"
#include "contactviewobserver.h"
#include <MVPbkContactLink.h>


//---------------------------------------------------------------------------
// Method that gets the links from the view and passes the link array to the 
// iterator.
//---------------------------------------------------------------------------
void CContactViewObserver::SetupContactLinkArrayL(MVPbkContactViewBase& aView )
{
	if((iFlag == EContactFilteredView) || ((iFlag == EContactDefaultView) && (iDefaultView)))
		{
        TInt viewCount = aView.ContactCountL();
        

        if(viewCount)
            {
            CVPbkContactLinkArray* linkArray = CVPbkContactLinkArray::NewL();
                                CleanupStack::PushL(linkArray);
            RPointerArray<HBufC8> idArray(viewCount);
            if(iVal == EGetList)
             {
             MVPbkContactLink* link = NULL;
            for(TInt i=0; i < viewCount; i++)
                 {
                     
                     link = aView.CreateLinkLC(i);
                     linkArray->AppendL(link);
                     CleanupStack::Pop();
                 }
             }
             else
                 {
				 if(iSortOrder == EDesc)
				 {
                 for(TInt i=(viewCount-1); i >= 0; i--)
                  {
                     MVPbkContactLink* link = NULL;
                     link = aView.CreateLinkLC(i);
                     idArray.AppendL( link->PackLC());
                     CleanupStack::Pop();   //PackLC puts every element into cleanup stack
                     //CleanupStack::PopAndDestroy();
                  }
				  }
				  else 
				  {
					for(TInt j=0; j < viewCount; j++)
                  {
                     MVPbkContactLink* link = NULL;
                     link = aView.CreateLinkLC(j);
                     idArray.AppendL( link->PackLC());
                     CleanupStack::Pop();   //PackLC puts every element into cleanup stack
                     //CleanupStack::PopAndDestroy();
                  }
				  }
                 }
                 
                 
                 
            if(iVal == EGetList)
            {
                //Set the params for iterator
                iIter->SetParams(linkArray, *iStoreUri, iSortOrder, iTransId, EContacts, iContactService);
                //Notify the user                
                iCallback->HandleReturnIter(KErrNone, iIter, iTransId);
              //  CleanupStack::Pop(viewCount);   //All Contacts are put in clean up stack. Pop em
                CleanupStack::Pop(linkArray);
                
            }
            else
            {
           //iContactService->RequestComplete(iTransId);
           //Notify the user
           //iCallback->HandleReturnIter(KErrNone, iIter, iTransId);
      
             iCallback->HandleReturnArray(KErrNone, idArray, iTransId);
             CleanupStack::PopAndDestroy(viewCount);
             CleanupStack::PopAndDestroy(linkArray);
             //idArray.Reset();
             delete iIter;
            }
             
                
            }
		else
			{
			//Notify User
			iCallback->HandleReturnValue(EOpComplete, KErrNotFound, iTransId);	
            delete iIter;
			iIter = NULL;
			}
               
		}
}


//---------------------------------------------------------------------------
// This method is called by the ContactViewObserver when the view is ready
//---------------------------------------------------------------------------
void CContactViewObserver::ContactViewReady(MVPbkContactViewBase& aView )
{
	iSchedulerWait->AsyncStop();
	iContactService->RequestComplete(iTransId);		
	
	TRAPD(error,SetupContactLinkArrayL(aView));
	if(error !=KErrNone)
		{
		//Notify User
		iCallback->HandleReturnValue(EOpComplete, error, iTransId);	
		delete iIter;
		iIter = NULL;
		}
}


//---------------------------------------------------------------------------
// NewL()
//---------------------------------------------------------------------------

CContactViewObserver* CContactViewObserver::NewL( MContactCallback* aCallback, enum TViewFlag aFlag, CContactIter* iIter, CContactService* aContactService,const TDesC& aStoreUri, TOrder aSortOrder, TInt aTransId, CActiveSchedulerWait* aSchedulerWait, TCmdType val)
{
    CContactViewObserver* self = new( ELeave ) CContactViewObserver( aStoreUri, aFlag, iIter,aContactService, aCallback, aSortOrder, aTransId, aSchedulerWait, val);
    return self;
}


//---------------------------------------------------------------------------
// ConstructL()
//---------------------------------------------------------------------------
    

CContactViewObserver::CContactViewObserver(const TDesC& aStoreUri, enum TViewFlag aFlag, CContactIter* aIter, CContactService* aContactService, MContactCallback* aCallback, TOrder aSortOrder, TInt aTransId, CActiveSchedulerWait* aSchedulerWait, TCmdType val )
:	iStoreUri (&aStoreUri),
	iFlag (aFlag),
	iIter (aIter),
	iCallback (aCallback),
	iSortOrder (aSortOrder),
	iTransId (aTransId),
	iDefaultView (EFalse),
	iSchedulerWait(aSchedulerWait),
	iContactService(aContactService),
	iVal(val)
{
}

/*
-------------------------------------------------------------------------------------
CContactViewObserver::Cancel()
Description 		: Cancel implementation relevant to ViewObserver
Return values		: KErrorNone on Success and KErrGeneral on Failure
-------------------------------------------------------------------------------------
*/

void CContactViewObserver::Cancel()
	{
	iCallback->HandleReturnValue(EOpCancel, KErrNone, iTransId);
	iView->RemoveObserver(*this);
	delete this;
	}
	
void CContactViewObserver::ReturnDefaultView()
	{
	iDefaultView = ETrue;
	}

void CContactViewObserver::ContactAddedToView( MVPbkContactViewBase& /*aView*/, TInt /*aIndex*/, const MVPbkContactLink& /*aContactLink */)
	{
	}
void CContactViewObserver::ContactRemovedFromView( MVPbkContactViewBase& /*aView*/, TInt /*aIndex*/, const MVPbkContactLink& /*aContactLink */)
	{
	}

void CContactViewObserver::ContactViewUnavailable(MVPbkContactViewBase& /*aView*/ )
	{
	iSchedulerWait->AsyncStop();
	iContactService->RequestComplete(iTransId);	
	//Notify User
	iCallback->HandleReturnValue(EOpError, KErrAbort, iTransId);
	delete iIter;
	iIter = NULL;
	}


void CContactViewObserver::ContactViewError( MVPbkContactViewBase& /*aView*/, TInt aError, TBool /*aErrorNotified*/ )
	{
	iSchedulerWait->AsyncStop();
	iContactService->RequestComplete(iTransId);	
	//Notify User
	iCallback->HandleReturnValue(EOpError, aError, iTransId);
	delete iIter;
	iIter = NULL;
	}
