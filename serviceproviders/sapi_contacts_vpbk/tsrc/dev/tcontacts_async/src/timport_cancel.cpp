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

class CImportTestAsync: public CActive, public MContactCallback
{
public:
	static CImportTestAsync* NewL();
	~CImportTestAsync();
	void Start();
	TInt Result();
	
private:
	void ConstructL();
	CImportTestAsync();
	
	virtual void DoCancel();
	virtual void RunL();
	
	
	void TestFunc();
	
	void HandleReturnValue(TOperationEvent aEvent, const TInt& aError , TInt aTransId);
	
	void HandleReturnIter(const TInt& aError, CContactIter* aIter, TInt aTransId );
	
	
private:	
	CActiveSchedulerWait* 	iWaitSchedular;
	CContactService*		iContactService;
	TInt 					iResult;	
};

CImportTestAsync* CImportTestAsync::NewL()
	{
	CImportTestAsync* self = new(ELeave)CImportTestAsync();
	self->ConstructL();
	return self;
	}

CImportTestAsync::~CImportTestAsync()
	{
	Cancel();
	
	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();
	
	if(iContactService)
		delete iContactService;
	
	if(iWaitSchedular)
		delete iWaitSchedular;
	}

void CImportTestAsync::ConstructL()
	{
	CActiveScheduler::Add(this);
	iContactService = CContactService::NewL();
	iWaitSchedular = new(ELeave) CActiveSchedulerWait();
	}

CImportTestAsync::CImportTestAsync() :
CActive(EPriorityStandard)
	{
	}

void CImportTestAsync::DoCancel()
	{
		
	}

void CImportTestAsync::RunL()
	{
	TestFunc();
	}

void CImportTestAsync::Start()
	{
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}

void CImportTestAsync::HandleReturnValue(TOperationEvent aEvent, const TInt& aError , TInt aTransId)
	{
	//******************* set iResult ****************************
	
	if(aEvent ==EOpCancel)
		iResult = KErrNone;
	else
		iResult = KErrGeneral;
		
	
	iWaitSchedular->AsyncStop();
	}
	
void CImportTestAsync::HandleReturnIter( const TInt& aError, CContactIter* aIter, TInt aTransId )
	{
	// It should not be called
	iResult = KErrGeneral;
			
	}

	
TInt CImportTestAsync::Result()
	{
	return iResult;
	}

void CImportTestAsync::TestFunc()
	{
 

	TInt32 transId = 1003;
	
    _LIT(KFileName,"c:\\vcardim.vcf");
    //using sapi
    TFileName file(KFileName);
    
    iContactService->ImportVCardToStoreL(this,transId,file);

	TInt error = iContactService->Cancel(transId);	
 	}


int import_cancel(int, char**)
	{
	__UHEAP_MARK;
	CImportTestAsync* test = CImportTestAsync::NewL();
	
	test->Start();
	
	TInt result = test->Result();
	
	delete test;
	__UHEAP_MARKEND;
	
	return  result;
	}






