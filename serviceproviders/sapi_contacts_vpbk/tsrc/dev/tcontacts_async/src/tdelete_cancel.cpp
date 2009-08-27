/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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

 

#include<e32base.h>

#include "contactservice.h"
#include "contactcallback.h"
#include "tcontacts_async.h"
#include "contactiter.h" // Iterator 

#ifdef MAIN
#define getlist_cancel main
#endif

class CDeleteTestAsync: public CActive, public MContactCallback
{
public:
	static CDeleteTestAsync* NewL();
	~CDeleteTestAsync();
	void Start();
	TInt Result();
	
private:
	void ConstructL();
	CDeleteTestAsync();
	
	virtual void DoCancel();
	virtual void RunL();
	
	
	void TestFunc();
	
	void HandleReturnValue(TOperationEvent aEvent, const TInt& aError , TInt aTransId);
	
	void HandleReturnIter( const TInt& aError, CContactIter* aIter, TInt aTransId );
	void HandleReturnId( const TInt& aError, HBufC8* acntId, TInt aTransId );
	void HandleReturnArray(const TInt& aError, RPointerArray<HBufC8>& aArray, TInt aTransId );
	
private:	
	CActiveSchedulerWait* 	iWaitSchedular;
	CContactService*		iContactService;
	TInt 					iResult;	
	HBufC8* 				iBuffer;
	
};

CDeleteTestAsync* CDeleteTestAsync::NewL()
	{
	CDeleteTestAsync* self = new(ELeave)CDeleteTestAsync();
	self->ConstructL();
	return self;
	}

CDeleteTestAsync::~CDeleteTestAsync()
	{
	Cancel();
	
	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();
	
	if(iContactService)
		delete iContactService;
	
	if(iWaitSchedular)
		delete iWaitSchedular;
	}

void CDeleteTestAsync::ConstructL()
	{
	CActiveScheduler::Add(this);
	iContactService = CContactService::NewL();
	iWaitSchedular = new(ELeave) CActiveSchedulerWait();
	}

CDeleteTestAsync::CDeleteTestAsync() :
CActive(EPriorityStandard)
	{
	}

void CDeleteTestAsync::DoCancel()
	{
		
	}

void CDeleteTestAsync::RunL()
	{
	TestFunc();
	}

void CDeleteTestAsync::Start()
	{
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}

void CDeleteTestAsync::HandleReturnValue(TOperationEvent aEvent, const TInt& aError , TInt aTransId)
	{
	//******************* set iResult ****************************
	
	if(aEvent ==EOpCancel)
		iResult = KErrNone;
	else
		iResult = KErrGeneral;
		
	
	iWaitSchedular->AsyncStop();
	}
	
void CDeleteTestAsync::HandleReturnIter( const TInt& aError, CContactIter* aIter, TInt aTransId )
	{
	// It should not be called
	//iWaitSchedular->AsyncStop();

	iResult = KErrGeneral;

    CSingleContact* singleContact = NULL;  
    HBufC8* buf = NULL;
    TInt count = 0; 
    aIter->NextL(singleContact,buf);
    iBuffer = buf;
    
    __UHEAP_MARK;
    RPointerArray<TDesC8> idArray;
    CleanupClosePushL(idArray);
    HBufC8* contactId = iBuffer->AllocLC();
    idArray.AppendL(contactId);  
    
    iContactService->DeleteL(this,0,idArray);
   	TInt error = iContactService->Cancel(0);	

    CleanupStack::PopAndDestroy();
    CleanupStack::PopAndDestroy(&idArray);//singleContactField	
      
  	__UHEAP_MARK;
    delete buf;
    delete singleContact;
    delete aIter;
	}
void CDeleteTestAsync::HandleReturnArray(const TInt& aError, RPointerArray<HBufC8>& aArray, TInt aTransId )
    {
    CActiveScheduler::Stop();
    }

void CDeleteTestAsync::HandleReturnId( const TInt& aError, HBufC8* acntId, TInt aTransId )
    {
    CActiveScheduler::Stop();
    }
	
TInt CDeleteTestAsync::Result()
	{
	return iResult;
	}

void CDeleteTestAsync::TestFunc()
	{
 	TInt32 transId = 1003;
	
	TRAPD(err,iContactService->GetListL(this,transId,EContacts,KNullDesC8,KNullDesC,NULL,EAsc ));
 	}


int delete_cancel(int, char**)
	{
	__UHEAP_MARK;
	CDeleteTestAsync* test = CDeleteTestAsync::NewL();
	
	test->Start();
	
	TInt result = test->Result();
	
	delete test;
	__UHEAP_MARKEND;
	
	return  result;
	}






