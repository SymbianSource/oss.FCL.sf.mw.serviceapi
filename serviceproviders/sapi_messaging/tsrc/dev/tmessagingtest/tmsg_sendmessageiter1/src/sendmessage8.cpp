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
#include<cmsvattachment.h>

#ifdef MAIN
#define sendmessage_test8 main
#endif

class CTestAsync8: public CActive, public CMsgCallbackBase
{
public:
	static CTestAsync8* NewL();
	~CTestAsync8();
	void Start();
	TInt Result();
	
private:
	void ConstructL();
	CTestAsync8();
	
	virtual void DoCancel();
	virtual void RunL();
	
	
	void TestFunc();
	void NotifyResultL(TInt aErrCode, TAny* aResult);

	
	
private:	
	CActiveSchedulerWait* 	iWaitSchedular;
	CMessagingService*		iMessagingService;
	TInt 					iResult;	
};

CTestAsync8* CTestAsync8::NewL()
	{
	CTestAsync8* self = new(ELeave)CTestAsync8();
	self->ConstructL();
	return self;
	}

CTestAsync8::~CTestAsync8()
	{
	Cancel();
	
	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();
	
	if(iMessagingService)
		delete iMessagingService;
	
	if(iWaitSchedular)
		delete iWaitSchedular;
	}

void CTestAsync8::ConstructL()
	{
	CActiveScheduler::Add(this);
	iMessagingService = CMessagingService::NewL();
	iWaitSchedular = new(ELeave) CActiveSchedulerWait();
	}

CTestAsync8::CTestAsync8() :
CActive(EPriorityStandard)
	{
	}

void CTestAsync8::DoCancel()
	{
		
	}

void CTestAsync8::RunL()
	{
	TestFunc();
	}

void CTestAsync8::Start()
	{
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}

void CTestAsync8::NotifyResultL(TInt aErrCode, TAny* aResult)
	{
	//******************* set iResult ****************************
	iResult = aErrCode;
	//******************* set iResult ****************************
	
	iWaitSchedular->AsyncStop();
	}
TInt CTestAsync8::Result()
	{
	return iResult;
	}

void CTestAsync8::TestFunc()
	{
 
	CSendMessageParams* messageParam = CSendMessageParams::NewL();
	CleanupStack::PushL(messageParam);	
	messageParam->AddRecipientL(_L("9008032761"));
	messageParam->SetMessageTypeL(_L("MMS"));
	messageParam->SetBodyTextL(_L("Hi How are you!!! Its the first mms from imessaging"));
	messageParam->SetSubjectL(_L("MMS"));
	
	TRAPD(errcode, iMessagingService->SendMessageL(messageParam, this));

	CleanupStack::PopAndDestroy(messageParam);	

 	}


int sendmessage_test8(int, char**)
	{
	__UHEAP_MARK;
	CTestAsync8* test = CTestAsync8::NewL();
	test->Start();
	__UHEAP_MARKEND;

	return KErrNone;
	}



