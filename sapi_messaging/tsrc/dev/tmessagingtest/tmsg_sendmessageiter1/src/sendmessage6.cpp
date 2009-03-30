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

 
// STLport regression testsuite component.
// To compile as a separate example, please #define MAIN.

#include<e32base.h>

#include "messagingservice.h"
#include "sendmessage.h"


#ifdef MAIN
#define sendmessage_test6 main
#endif

class CTestAsync6: public CActive, public CMsgCallbackBase
{
public:
	static CTestAsync6* NewL();
	~CTestAsync6();
	void Start();
	TInt Result();
	
private:
	void ConstructL();
	CTestAsync6();
	
	virtual void DoCancel();
	virtual void RunL();
	
	
	void TestFunc();
	void NotifyResultL(TInt aErrCode, TAny* aResult);

	
	
private:	
	CActiveSchedulerWait* 	iWaitSchedular;
	CMessagingService*		iMessagingService;
	TInt 					iResult;	
};

CTestAsync6* CTestAsync6::NewL()
	{
	CTestAsync6* self = new(ELeave)CTestAsync6();
	self->ConstructL();
	return self;
	}

CTestAsync6::~CTestAsync6()
	{
	Cancel();
	
	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();
	
	if(iMessagingService)
		delete iMessagingService;
	
	if(iWaitSchedular)
		delete iWaitSchedular;
	}

void CTestAsync6::ConstructL()
	{
	CActiveScheduler::Add(this);
	iMessagingService = CMessagingService::NewL();
	iWaitSchedular = new(ELeave) CActiveSchedulerWait();
	}

CTestAsync6::CTestAsync6() :
CActive(EPriorityStandard)
	{
	}

void CTestAsync6::DoCancel()
	{
		
	}

void CTestAsync6::RunL()
	{
	TestFunc();
	}

void CTestAsync6::Start()
	{
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}

void CTestAsync6::NotifyResultL(TInt aErrCode, TAny* aResult)
	{
	//******************* set iResult ****************************
	iResult = aErrCode;
	//******************* set iResult ****************************
	
	iWaitSchedular->AsyncStop();
	}
TInt CTestAsync6::Result()
	{
	return iResult;
	}

void CTestAsync6::TestFunc()
	{
 
	CSendMessageParams* messageParam = CSendMessageParams::NewL();
	CleanupStack::PushL(messageParam);
	
	messageParam->AddRecipientL(_L("9008032761"));
	messageParam->SetMessageTypeL(_L("SMS"));
	messageParam->SetBodyTextL(_L("Hi How are you!!! Its the first Sms from imessaging"));
	
	TRAPD (errcode, iMessagingService->SendMessageL(messageParam, this));
	iMessagingService->Cancel(0);
	CleanupStack::PopAndDestroy(messageParam);

 	}


int sendmessage_test6(int, char**)
	{
	__UHEAP_MARK;
	
	CTestAsync6* test = CTestAsync6::NewL();
	test->Start();

	__UHEAP_MARKEND;
	return KErrNone;
	}
