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
#include "searchfields.h"

#ifdef MAIN
#define getlist_cancel main
#endif

class CGetListTestSrhAsync: public CActive, public MContactCallback
{
public:
	static CGetListTestSrhAsync* NewL();
	~CGetListTestSrhAsync();
	void Start();
	TInt Result();
	
private:
	void ConstructL();
	CGetListTestSrhAsync();
	
	virtual void DoCancel();
	virtual void RunL();
	
	
	void TestFunc();
	
	void HandleReturnValue(TOperationEvent aEvent, const TInt& aError , TInt aTransId);
	
	void HandleReturnIter( const TInt& aError, CContactIter* aIter, TInt aTransId );
	
	
private:	
	CActiveSchedulerWait* 	iWaitSchedular;
	CContactService*		iContactService;
	TInt 					iResult;	
	
};

CGetListTestSrhAsync* CGetListTestSrhAsync::NewL()
	{
	CGetListTestSrhAsync* self = new(ELeave)CGetListTestSrhAsync();
	self->ConstructL();
	return self;
	}

CGetListTestSrhAsync::~CGetListTestSrhAsync()
	{
	Cancel();
	
	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();
	
	if(iContactService)
		delete iContactService;
	
	if(iWaitSchedular)
		delete iWaitSchedular;
	}

void CGetListTestSrhAsync::ConstructL()
	{
	CActiveScheduler::Add(this);
	iContactService = CContactService::NewL();
	iWaitSchedular = new(ELeave) CActiveSchedulerWait();
	}

CGetListTestSrhAsync::CGetListTestSrhAsync() :
CActive(EPriorityStandard)
	{
	}

void CGetListTestSrhAsync::DoCancel()
	{
		
	}

void CGetListTestSrhAsync::RunL()
	{
	TestFunc();
	}

void CGetListTestSrhAsync::Start()
	{
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}

void CGetListTestSrhAsync::HandleReturnValue(TOperationEvent aEvent, const TInt& aError , TInt aTransId)
	{
	//******************* set iResult ****************************
    _LIT(KName,"Jack"); 
	if(EOpCancel ==aEvent)
		{
		iResult = KErrNone;
		return;
		}
		
	else
		iResult = KErrGeneral;
		

	TRAPD(err,iContactService->GetListL(this,0,EContacts,KNullDesC8,KName,NULL,EAsc ));

	TInt error = iContactService->Cancel(0);	
	iWaitSchedular->AsyncStop();
	
	}
	
void CGetListTestSrhAsync::HandleReturnIter( const TInt& aError, CContactIter* aIter, TInt aTransId )
	{
	// It should not be called
	iResult = KErrGeneral;
			
	}

	
TInt CGetListTestSrhAsync::Result()
	{
	return iResult;
	}

void CGetListTestSrhAsync::TestFunc()
	{
	iWaitSchedular->AsyncStop();
    _LIT8(KFirstName,"FirstName");
    _LIT(KName,"Jack"); 
    _LIT8(KNumber,"MobilePhoneHome");
    _LIT(KPhone,"0909977");

	TInt32 transId = 1003;
	
    CSingleContact* singleContact = CSingleContact::NewL();
    CleanupStack::PushL(singleContact);
    
    CSingleContactField* nameContactField = CSingleContactField::NewL();
    CleanupStack::PushL(nameContactField);
    
    CSingleContactField* phoneContactField = CSingleContactField::NewL();
    CleanupStack::PushL(phoneContactField);
    
    nameContactField->SetFieldParamsL(KFirstName,KNullDesC,KName);
    singleContact->AddFieldToContactL(nameContactField);
    
    phoneContactField->SetFieldParamsL(KNumber,KNullDesC,KPhone);
    singleContact->AddFieldToContactL(phoneContactField);
    
    iContactService->AddL(this,transId,singleContact,KNullDesC8,KNullDesC);
	iWaitSchedular->Start();

 
    CleanupStack::Pop(phoneContactField);//singleContactField	
    CleanupStack::Pop(nameContactField);//singleContactField	
    CleanupStack::PopAndDestroy(singleContact);//singleContact

 	}


int getlistsrh_cancel(int, char**)
	{
	__UHEAP_MARK;
	CGetListTestSrhAsync* test = CGetListTestSrhAsync::NewL();
	
	test->Start();
	
	TInt result = test->Result();
	
	delete test;
	__UHEAP_MARKEND;
	
	return  result;
	}






