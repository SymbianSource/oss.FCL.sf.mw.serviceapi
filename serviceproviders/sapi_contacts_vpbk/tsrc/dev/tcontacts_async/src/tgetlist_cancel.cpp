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

class CGetListTestAsync: public CActive, public MContactCallback
{
public:
	static CGetListTestAsync* NewL();
	~CGetListTestAsync();
	void Start();
	TInt Result();
	
private:
	void ConstructL();
	CGetListTestAsync();
	
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
	
};

CGetListTestAsync* CGetListTestAsync::NewL()
	{
	CGetListTestAsync* self = new(ELeave)CGetListTestAsync();
	self->ConstructL();
	return self;
	}

CGetListTestAsync::~CGetListTestAsync()
	{
	Cancel();
	
	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();
	
	if(iContactService)
		delete iContactService;
	
	if(iWaitSchedular)
		delete iWaitSchedular;
	}

void CGetListTestAsync::ConstructL()
	{
	CActiveScheduler::Add(this);
	iContactService = CContactService::NewL();
	iWaitSchedular = new(ELeave) CActiveSchedulerWait();
	}

CGetListTestAsync::CGetListTestAsync() :
CActive(EPriorityStandard)
	{
	}

void CGetListTestAsync::DoCancel()
	{
		
	}

void CGetListTestAsync::RunL()
	{
	TestFunc();
	}

void CGetListTestAsync::Start()
	{
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}


void CGetListTestAsync::HandleReturnId( const TInt& aError, HBufC8* acntId, TInt aTransId )
    {
    CActiveScheduler::Stop();
    }


void CGetListTestAsync::HandleReturnValue(TOperationEvent aEvent, const TInt& aError , TInt aTransId)
	{
	//******************* set iResult ****************************

	if(aEvent ==EOpCancel)
		iResult = KErrNone;
	else
		iResult = KErrGeneral;
		
	
	iWaitSchedular->AsyncStop();
	}
	
void CGetListTestAsync::HandleReturnIter( const TInt& aError, CContactIter* aIter, TInt aTransId )
	{
	// It should not be called
	iResult = KErrGeneral;
			
	}


void CGetListTestAsync::HandleReturnArray(const TInt& aError, RPointerArray<HBufC8>& aArray, TInt aTransId )
    {
    CActiveScheduler::Stop();
    }
TInt CGetListTestAsync::Result()
	{
	return iResult;
	}

void CGetListTestAsync::TestFunc()
	{
 
 
	TRAPD(err,iContactService->GetListL(this,0,EContacts,KNullDesC8,KNullDesC,NULL,EAsc ));

	TInt error = iContactService->Cancel(0);	
	
 	}


int getlist_cancel(int, char**)
	{
	__UHEAP_MARK;
	CGetListTestAsync* test = CGetListTestAsync::NewL();
	
	test->Start();
	
	TInt result = test->Result();
	
	delete test;
	__UHEAP_MARKEND;
	
	return  result;
	}






