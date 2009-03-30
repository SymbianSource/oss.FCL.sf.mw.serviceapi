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
#define sendmessage_test9 main
#endif

class CTestAsync9: public CActive, public CMsgCallbackBase
{
public:
	static CTestAsync9* NewL();
	~CTestAsync9();
	void Start();
	TInt Result();
	
private:
	void ConstructL();
	CTestAsync9();
	
	virtual void DoCancel();
	virtual void RunL();
	
	
	void TestFunc();
	void NotifyResultL(TInt aErrCode, TAny* aResult);

	
	
private:	
	CActiveSchedulerWait* 	iWaitSchedular;
	CMessagingService*		iMessagingService;
	TInt 					iResult;	
};

CTestAsync9* CTestAsync9::NewL()
	{
	CTestAsync9* self = new(ELeave)CTestAsync9();
	self->ConstructL();
	return self;
	}

CTestAsync9::~CTestAsync9()
	{
	Cancel();
	
	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();
	
	if(iMessagingService)
		delete iMessagingService;
	
	if(iWaitSchedular)
		delete iWaitSchedular;
	}

void CTestAsync9::ConstructL()
	{
	CActiveScheduler::Add(this);
	iMessagingService = CMessagingService::NewL();
	iWaitSchedular = new(ELeave) CActiveSchedulerWait();
	}

CTestAsync9::CTestAsync9() :
CActive(EPriorityStandard)
	{
	}

void CTestAsync9::DoCancel()
	{
		
	}

void CTestAsync9::RunL()
	{
	TestFunc();
	}

void CTestAsync9::Start()
	{
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}

void CTestAsync9::NotifyResultL(TInt aErrCode, TAny* aResult)
	{
	//******************* set iResult ****************************
	iResult = aErrCode;
	//******************* set iResult ****************************
	
	iWaitSchedular->AsyncStop();
	}
TInt CTestAsync9::Result()
	{
	return iResult;
	}

void CTestAsync9::TestFunc()
	{
 
	CSendMessageParams* messageParam = CSendMessageParams::NewL();
	CleanupStack::PushL(messageParam);	
	messageParam->AddRecipientL(_L("9008032761"));
	messageParam->SetMessageTypeL(_L("MMS"));
	messageParam->SetBodyTextL(_L("Hi How are you!!! Its the first mms from imessaging"));
	messageParam->SetSubjectL(_L("MMS"));
	
	CMsvAttachment* element = CMsvAttachment::NewL(CMsvAttachment::EMsvFile);
	element->SetMimeTypeL(_L8("image/jpeg"));
	element->SetAttachmentNameL(_L("c:\\data\\images\\test1.jpg"));
	messageParam->AddAttachmentL(element);

	element = CMsvAttachment::NewL(CMsvAttachment::EMsvFile);
	element->SetMimeTypeL(_L8("image/jpeg"));
	element->SetAttachmentNameL(_L("c:\\data\\images\\test2.jpg"));
	messageParam->AddAttachmentL(element);


	TRAPD(errcode, iMessagingService->SendMessageL(messageParam, this));
	
	CleanupStack::PopAndDestroy(messageParam);	

 	}


int sendmessage_test9(int, char**)
	{
	__UHEAP_MARK;
	CTestAsync9* test = CTestAsync9::NewL();
	test->Start();
	__UHEAP_MARKEND;;

	return 0;
	}






