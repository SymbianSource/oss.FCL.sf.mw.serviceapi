/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:   ?Description
*
*/




#include "sysinfoservice.h"
#include"entitykeys.h"

using namespace SysInfo;
class CTestAsync4 : public CActive ,public ISystemObserver
{
public:
	static CTestAsync4* NewL();
	~CTestAsync4();
	void Start();
	TInt Result();

	 void HandleResponseL(const TDesC& aEntity,const TDesC& aKey, 
									CSysData* aResponse, TInt32 aTransID, 
									TSysRequest::TRequestType aType,TInt aError=KErrNone);

private:
	void ConstructL();
	CTestAsync4();
	
	virtual void DoCancel();
	virtual void RunL();
	
	
	void TestFunc();

	
	
private:	
	CActiveSchedulerWait* 	iWaitSchedular;
	CSysInfoService*		iSysInfoService;
	TInt predtextstatus ;
	TInt 					iResult;	
};

CTestAsync4* CTestAsync4::NewL()
	{
	CTestAsync4* self = new(ELeave) CTestAsync4();
	self->ConstructL();
	return self;
	}

CTestAsync4::~CTestAsync4()
	{
	Cancel();
	
	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();
	
	if(iSysInfoService)
		delete iSysInfoService;
	
	if(iWaitSchedular)
		delete iWaitSchedular;
	}

void CTestAsync4::ConstructL()
	{
	CActiveScheduler::Add(this);
	iSysInfoService = CSysInfoService::NewL();
	iWaitSchedular = new(ELeave) CActiveSchedulerWait();
	}

CTestAsync4::CTestAsync4() :
CActive(EPriorityStandard),iResult(KErrNone)
	{
	}

void CTestAsync4::DoCancel()
	{
	
		
	}

void CTestAsync4::RunL()
	{
	TestFunc();
	}

void CTestAsync4::Start()
	{
	
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}

TInt CTestAsync4::Result()
	{
	return iResult;
	}

void CTestAsync4::TestFunc()
	{

	TRAPD(err1,iSysInfoService->GetNotificationL(KGeneral,KPridictiveText,666,this));
	iResult = err1;
	
	if(err1 == KErrNone)
	{
	CSysData* data1 = NULL;
	
	
	TRAPD(err2,iSysInfoService->GetInfoL(KGeneral,KPridictiveText,data1));
	iResult =err2; 
	
	predtextstatus = ((CStatus*)data1)->Status();
	
	CStatus* data2 = CStatus::NewL(!predtextstatus);

	TRAPD(err3,iSysInfoService->SetInfoL(KGeneral,KPridictiveText,data2));
	iResult =err3; 
	
	delete data1;
	delete data2;
	}
	
	
	return ;
	}

void CTestAsync4::HandleResponseL(const TDesC& aEntity,const TDesC& aKey, 
									CSysData* aResponse, TInt32 /*aTransID*/, 
									TSysRequest::TRequestType /*aType*/,TInt aError)
	{
	
		if(aError == KErrNone) 
			{
			if(aEntity.Compare(KGeneral) || aKey.Compare(KPridictiveText))
				{
				iResult = -1;
				}
		
			const CStatus* data1 = (CStatus*)aResponse;
		
			if((data1->Status() ) == (!predtextstatus) )
				{
				iResult = KErrNone;
				delete aResponse;

				}
			else
				{
				iResult = -1;
				}
			}
		
iWaitSchedular->AsyncStop();
	}


int PredTextNotification()
	{
	__UHEAP_MARK;

	CTestAsync4* test = CTestAsync4::NewL();
	
	test->Start();
	TInt retval =	test->Result();
//	test->Cancel();
	delete test;
	
	__UHEAP_MARKEND;
	
	return retval;
	}
