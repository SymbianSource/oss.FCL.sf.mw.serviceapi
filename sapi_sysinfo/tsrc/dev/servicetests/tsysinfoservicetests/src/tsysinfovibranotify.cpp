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


class CTestAsync1 : public CActive ,public ISystemObserver
{
public:
	static CTestAsync1* NewL();
	~CTestAsync1();
	void Start();
	TInt Result();

	 void HandleResponseL(const TDesC& aEntity,const TDesC& aKey, 
									CSysData* aResponse, TInt32 aTransID, 
									TSysRequest::TRequestType aType, TInt aError=KErrNone);

private:
	void ConstructL();
	CTestAsync1();
	
	virtual void DoCancel();
	virtual void RunL();
	
	
	void TestFunc();

	
	
private:	
	CActiveSchedulerWait* 	iWaitSchedular;
	CSysInfoService*		iSysInfoService;
	TInt vibrastatus ;
	TInt 					iResult;	
};

CTestAsync1* CTestAsync1::NewL()
	{
	CTestAsync1* self = new(ELeave) CTestAsync1();
	self->ConstructL();
	return self;
	}

CTestAsync1::~CTestAsync1()
	{
	Cancel();
	
	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();
	
	if(iSysInfoService)
		delete iSysInfoService;
	
	if(iWaitSchedular)
		delete iWaitSchedular;
	}

void CTestAsync1::ConstructL()
	{
	CActiveScheduler::Add(this);
	iSysInfoService = CSysInfoService::NewL();
	iWaitSchedular = new(ELeave) CActiveSchedulerWait();
	}

CTestAsync1::CTestAsync1() :
CActive(EPriorityStandard),iResult(-1)
	{
	}

void CTestAsync1::DoCancel()
	{
	
	//TRAPD(err1,iSysInfoService->GetInfoL(req1));
		
	}

void CTestAsync1::RunL()
	{
	TestFunc();
	}

void CTestAsync1::Start()
	{
	
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}

TInt CTestAsync1::Result()
	{
	return iResult;
	}

void CTestAsync1::TestFunc()
	{
		
	TRAPD(err1,iSysInfoService->GetNotificationL(KGeneral,KVibraActive,999,this));
	iResult =err1; 

	if(err1 == KErrNone)
	{

	CSysData* data1 = NULL;
	
	TRAPD(err2,iSysInfoService->GetInfoL(KGeneral,KVibraActive,data1));
	iResult =err2; 
	
	vibrastatus = ((CStatus*)data1)->Status();
	
	CStatus* data2 = CStatus::NewL(!vibrastatus);

	TRAPD(err3,iSysInfoService->SetInfoL(KGeneral,KVibraActive,data2));
	iResult =err3; 

	delete data1;
	delete data2;
	}

	

	return ;
	}

void CTestAsync1::HandleResponseL(const TDesC& /*aEntity*/,const TDesC& /*aKey*/, 
									CSysData* aResponse, TInt32 /*aTransID*/, 
									TSysRequest::TRequestType /*aType*/,TInt aError)
	{
	if(aError == KErrNone) 
			{
		const CStatus* data1 = (CStatus*)aResponse;
		if((data1->Status() ) == (!vibrastatus) )
			{
				iResult = KErrNone;
			}
		else
			{
					iResult = -1;
			}
			}
			
	delete aResponse;
		
	iWaitSchedular->AsyncStop();
	}


int VibraNotification()
	{
	__UHEAP_MARK;

	CTestAsync1* test = CTestAsync1::NewL();
	
	test->Start();
	TInt retval =	test->Result();
	delete test;
	__UHEAP_MARKEND;

	return retval;
	}

