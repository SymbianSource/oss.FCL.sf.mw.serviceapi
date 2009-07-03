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
#include<CMsvAttachment.h>

#ifdef MAIN
#define sendmessage_test7 main
#endif


class CTestAsync7: public CActive, public CMsgCallbackBase
{
public:
	static CTestAsync7* NewL();
	~CTestAsync7();
	void Start();
	TInt Result();
	
private:
	void ConstructL();
	CTestAsync7();
	
	virtual void DoCancel();
	virtual void RunL();
	
	
	void TestFunc();
	void NotifyResultL(TInt aErrCode, TAny* aResult);

	
	
private:	
	CActiveSchedulerWait* 	iWaitSchedular;
	CMessagingService*		iMessagingService;
	TInt 					iResult;	
};

CTestAsync7* CTestAsync7::NewL()
	{
	CTestAsync7* self = new(ELeave)CTestAsync7();
	self->ConstructL();
	return self;
	}

CTestAsync7::~CTestAsync7()
	{
	Cancel();
	
	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();
	
	if(iMessagingService)
		delete iMessagingService;
	
	if(iWaitSchedular)
		delete iWaitSchedular;
	}

void CTestAsync7::ConstructL()
	{
	CActiveScheduler::Add(this);
	iMessagingService = CMessagingService::NewL();
	iWaitSchedular = new(ELeave) CActiveSchedulerWait();
	}

CTestAsync7::CTestAsync7() :
CActive(EPriorityStandard)
	{
	}

void CTestAsync7::DoCancel()
	{
		
	}

void CTestAsync7::RunL()
	{
	TestFunc();
	}

void CTestAsync7::Start()
	{
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}

void CTestAsync7::NotifyResultL(TInt aErrCode, TAny* aResult)
	{
	//******************* set iResult ****************************
	iResult = aErrCode;
	//******************* set iResult ****************************
	
	iWaitSchedular->AsyncStop();
	}
TInt CTestAsync7::Result()
	{
	return iResult;
	}

void CTestAsync7::TestFunc()
	{
 
	CSendMessageParams* messageParam = CSendMessageParams::NewL();
	CleanupStack::PushL(messageParam);
	
	messageParam->AddRecipientL(_L("9008032761"));
	messageParam->SetMessageTypeL(_L("SMS"));
	messageParam->SetLaunchEditor();
	messageParam->SetBodyTextL(_L("Hi How are you!!! Its the first sms from imessaging"));
	
	TRAPD(errcode, iMessagingService->SendMessageL(messageParam, this));
	CleanupStack::PopAndDestroy(messageParam);

 	}


int sendmessage_test7(int, char**)
	{
	__UHEAP_MARK;
	CTestAsync7* test = CTestAsync7::NewL();
	test->Start();
	__UHEAP_MARKEND;

	return KErrNone;
	}


