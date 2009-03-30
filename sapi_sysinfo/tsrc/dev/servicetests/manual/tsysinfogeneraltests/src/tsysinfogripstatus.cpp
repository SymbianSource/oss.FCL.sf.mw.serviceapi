/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:   tsysinfogripstatus
*
*/



#include "sysinfoservice.h"
#include"entitykeys.h"
#include<e32err.h>

using namespace SysInfo;
class CTestAsync6 : public CActive ,public ISystemObserver
{
public:
	static CTestAsync6* NewL();
	~CTestAsync6();
	void Start();
	TInt Result();

	 void HandleResponseL(const TDesC& aEntity,const TDesC& aKey, 
									CSysData* aResponse, TInt32 aTransID, 
									TSysRequest::TRequestType aType,TInt aError=KErrNone);

private:
	void ConstructL();
	CTestAsync6();
	
	virtual void DoCancel();
	virtual void RunL();
	
	
	void TestFunc();

	
	
private:	
	CActiveSchedulerWait* 	iWaitSchedular;
	CSysInfoService*		iSysInfoService;
	TInt gripstatus ;
	TInt 					iResult;	
};

CTestAsync6* CTestAsync6::NewL()
	{
	CTestAsync6* self = new(ELeave) CTestAsync6();
	self->ConstructL();
	return self;
	}

CTestAsync6::~CTestAsync6()
	{
	Cancel();
	
	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();
	
	if(iSysInfoService)
		delete iSysInfoService;
	
	if(iWaitSchedular)
		delete iWaitSchedular;
	}

void CTestAsync6::ConstructL()
	{
	CActiveScheduler::Add(this);
	iSysInfoService = CSysInfoService::NewL();
	iWaitSchedular = new(ELeave) CActiveSchedulerWait();
	}

CTestAsync6::CTestAsync6() :
CActive(EPriorityStandard),iResult(-1)
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

TInt CTestAsync6::Result()
	{
	return iResult;
	}

void CTestAsync6::TestFunc()
	{
		
	CStatus* data = CStatus::NewL(gripstatus);
	
	TRAPD(err1,iSysInfoService->GetNotificationL(KGeneral,KGripStatus,444,this));
	iResult = err1;	
	
	if(err1 == KErrNone)
	{
	
	CSysData* data1 = NULL;
	
	TRAPD(err2,iSysInfoService->GetInfoL(KGeneral,KGripStatus,data1));
		
	gripstatus = ((CStatus*)data1)->Status();
	
	CStatus* data2 = CStatus::NewL(!gripstatus);

	TRAPD(err3,iSysInfoService->SetInfoL(KGeneral,KGripStatus,data2));
	delete data1;
	delete data2;

	}
	
	
	return ;
	}

void CTestAsync6::HandleResponseL(const TDesC& /*aEntity*/,const TDesC& /*aKey*/, 
									CSysData* aResponse, TInt32 /*aTransID*/, 
									TSysRequest::TRequestType /*aType*/,TInt aError)
	{

		if(aError == KErrNone) 
			{
			const CStatus* data1 = (CStatus*)aResponse;
			TInt statusval = data1->Status() ;
		
			if(statusval == 1)
				{
				gripstatus -=1;
				}
			else
				{
				gripstatus +=1;
				}
				
			if(statusval == (gripstatus) )
				{
				iResult = KErrNone;
				}
			else
				{
				iResult = -1;
				}
			delete aResponse;

			}
	iWaitSchedular->AsyncStop();
	}


int GripNotification()
	{
	__UHEAP_MARK;
	
	CTestAsync6* test = CTestAsync6::NewL();
	
	test->Start();
	TInt retval =	test->Result();
//	test->Cancel();
	delete test;
	__UHEAP_MARKEND;

	return retval;
	}

