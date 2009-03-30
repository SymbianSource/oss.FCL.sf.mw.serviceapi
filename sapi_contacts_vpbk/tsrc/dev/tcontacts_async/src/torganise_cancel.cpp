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
#include "contactservice.hrh"
#include "contactcallback.h"
#include "tcontacts_async.h"
#include "contactiter.h" // Iterator 

#ifdef MAIN
#define getlist_cancel main
#endif

class CTestAsync: public CActive, public MContactCallback
{
public:
	static CTestAsync* NewL();
	~CTestAsync();
	void Start();
	TInt Result();
	
private:
	void ConstructL();
	CTestAsync();
	
	virtual void DoCancel();
	virtual void RunL();
	
	
	void TestFunc();
	
	void HandleReturnValue(TOperationEvent aEvent, const TInt& aError , TInt aTransId);
	
	void HandleReturnIter( const TInt& aError, CContactIter* aIter, TInt aTransId );
	
	
private:	
	CActiveSchedulerWait* 	iWaitSchedular;
	CContactService*		iContactService;
	TInt 					iResult;	
	enum Ttype					iOpType;
	HBufC8*					iGroupBuffer;
	
};

CTestAsync* CTestAsync::NewL()
	{
	CTestAsync* self = new(ELeave)CTestAsync();
	self->ConstructL();
	return self;
	}

CTestAsync::~CTestAsync()
	{
	Cancel();
	
	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();
	
	if(iContactService)
		delete iContactService;
	
	if(iWaitSchedular)
		delete iWaitSchedular;
	
	delete iGroupBuffer;
	}

void CTestAsync::ConstructL()
	{
	CActiveScheduler::Add(this);
	iContactService = CContactService::NewL();
	iWaitSchedular = new(ELeave) CActiveSchedulerWait();
	}

CTestAsync::CTestAsync() :
CActive(EPriorityStandard)
	{
	}

void CTestAsync::DoCancel()
	{
		
	}

void CTestAsync::RunL()
	{
	TestFunc();
	}

void CTestAsync::Start()
	{
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}

void CTestAsync::HandleReturnValue(TOperationEvent aEvent, const TInt& aError , TInt aTransId)
	{
	//******************* set iResult ****************************
	
	if(aEvent ==EOpCancel)		
		iResult = KErrNone;	
	else
		iResult = KErrGeneral;
		
	
	iWaitSchedular->AsyncStop();
	}
	
void CTestAsync::HandleReturnIter( const TInt& aError, CContactIter* aIter, TInt aTransId )
	{

	// It should not be called
	iResult = KErrGeneral;
	if(iOpType == EGroups)
		{
		iWaitSchedular->AsyncStop();

	    CSingleContact* singleContact = NULL;  
	    HBufC8* buf = NULL;

	    aIter->NextL(singleContact,buf);

	    iGroupBuffer = buf->AllocLC();

		iOpType = EContacts;
	    iContactService->GetListL(this,1,EContacts);
		iWaitSchedular->Start();
		CleanupStack::Pop();
	    delete buf;
	    delete singleContact;
		
	    delete aIter;			

		}
	else if(iOpType == EContacts)
		{
		
	    CSingleContact* singleContact = NULL;  
	    HBufC8* buf = NULL;

	    aIter->NextL(singleContact,buf);
				
	    RPointerArray<TDesC8> idArray;
	    CleanupClosePushL(idArray);

	    HBufC8* contactId = buf->AllocLC();
	    idArray.AppendL(contactId);  
	    
	    iContactService->OrganiseGroupsL(this,0,*iGroupBuffer,idArray,EFalse);
		TInt error = iContactService->Cancel(0);	

	    CleanupStack::PopAndDestroy();
    	CleanupStack::PopAndDestroy(&idArray);//singleContactField	


	    delete buf;
	    delete singleContact;
	    
	    delete aIter;			
		
		}
	}

	
TInt CTestAsync::Result()
	{
	return iResult;
	}

void CTestAsync::TestFunc()
	{	
	iOpType = EGroups;
	TRAPD(err,iContactService->GetListL(this,3,EGroups));
 	}


int organise_cancel(int, char**)
	{
	__UHEAP_MARK;
	CTestAsync* test = CTestAsync::NewL();
	
	test->Start();
	
	TInt result = test->Result();
	
	delete test;
	__UHEAP_MARKEND;
	
	return  result;
	}






