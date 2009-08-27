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

class CAddTestAsync: public CActive, public MContactCallback
{
public:
	static CAddTestAsync* NewL();
	~CAddTestAsync();
	void Start();
	TInt Result();
	
private:
	void ConstructL();
	CAddTestAsync();
	
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

CAddTestAsync* CAddTestAsync::NewL()
	{
	CAddTestAsync* self = new(ELeave)CAddTestAsync();
	self->ConstructL();
	return self;
	}

CAddTestAsync::~CAddTestAsync()
	{
	Cancel();
	
	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();
	
	if(iContactService)
		delete iContactService;
	
	if(iWaitSchedular)
		delete iWaitSchedular;
	}

void CAddTestAsync::ConstructL()
	{
	CActiveScheduler::Add(this);
	iContactService = CContactService::NewL();
	iWaitSchedular = new(ELeave) CActiveSchedulerWait();
	}

CAddTestAsync::CAddTestAsync() :
CActive(EPriorityStandard)
	{
	}

void CAddTestAsync::DoCancel()
	{
		
	}

void CAddTestAsync::RunL()
	{
	TestFunc();
	}

void CAddTestAsync::Start()
	{
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}
void CAddTestAsync::HandleReturnId( const TInt& aError, HBufC8* acntId, TInt aTransId )
    {
    CActiveScheduler::Stop();
    }
void CAddTestAsync::HandleReturnValue(TOperationEvent aEvent, const TInt& aError , TInt aTransId)
	{
	//******************* set iResult ****************************
	
	if(aEvent ==EOpCancel)
		iResult = KErrNone;
	else
		iResult = KErrGeneral;
		
	
	iWaitSchedular->AsyncStop();
	}
	
void CAddTestAsync::HandleReturnIter( const TInt& aError, CContactIter* aIter, TInt aTransId )
	{
	// It should not be called
	iResult = KErrGeneral;
			
	}


void CAddTestAsync::HandleReturnArray(const TInt& aError, RPointerArray<HBufC8>& aArray, TInt aTransId )
    {
    CActiveScheduler::Stop();
    }
TInt CAddTestAsync::Result()
	{
	return iResult;
	}

void CAddTestAsync::TestFunc()
	{
 	
 	TInt transId = 666;
    /**Add contact using SAPI Core class*/
    
    _LIT8(KFirstName,"FirstName");
    _LIT(KName,"Suzanne"); 
    _LIT8(KNumber,"MobilePhoneHome");
    _LIT(KPhone,"88888888");
    
   // __UHEAP_MARK;
    //instantiate service class 

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
	
	TInt error = iContactService->Cancel(transId);	    
 
    CleanupStack::Pop(phoneContactField);//singleContactField	
    CleanupStack::Pop(nameContactField);//singleContactField	
    CleanupStack::PopAndDestroy(singleContact);//singleContact
  //  __UHEAP_MARKEND; 
    /**end */

 	}


int add_cancel(int, char**)
	{
	__UHEAP_MARK;
	CAddTestAsync* test = CAddTestAsync::NewL();
	
	test->Start();
	
	TInt result = test->Result();
	
	delete test;
	__UHEAP_MARKEND;
	
	return  result;
	}






