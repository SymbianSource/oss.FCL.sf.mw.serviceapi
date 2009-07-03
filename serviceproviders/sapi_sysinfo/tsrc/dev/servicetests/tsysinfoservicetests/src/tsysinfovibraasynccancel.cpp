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
#include"watchtimer.h"

using namespace SysInfo;


class CTestVibraNotificationCancel : public CActive ,public ISystemObserver, public MTimeOutCallBack
	{
	public:
		static CTestVibraNotificationCancel* NewL();
		~CTestVibraNotificationCancel();
		void Start();
		TInt Result();

		 void HandleResponseL(const TDesC& aEntity,const TDesC& aKey, 
										CSysData* aResponse, TInt32 aTransID, 
										TSysRequest::TRequestType aType,TInt aError=KErrNone);
		 void HandleTimeOut	();

	private:
		void ConstructL();
		CTestVibraNotificationCancel();
		
		virtual void DoCancel();
		virtual void RunL();
		
		
		void TestFunc();

	
		
	private:	
		CActiveSchedulerWait* 	iWaitSchedular;
		CSysInfoService*		iSysInfoService;
		TInt 					vibrastatus ;
		TInt 					iResult;
		CWatchTimer*			iTimer;
	
	};

CTestVibraNotificationCancel* CTestVibraNotificationCancel::NewL()
	{
	CTestVibraNotificationCancel* self = new(ELeave) CTestVibraNotificationCancel();
	self->ConstructL();
	return self;
	}

CTestVibraNotificationCancel::~CTestVibraNotificationCancel()
	{
	Cancel();
	
	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();
	
	if(iSysInfoService)
		delete iSysInfoService;
	
	if(iWaitSchedular)
		delete iWaitSchedular;
	
	delete iTimer;

	}

void CTestVibraNotificationCancel::ConstructL()
	{
	CActiveScheduler::Add(this);
	iSysInfoService = CSysInfoService::NewL();
	iWaitSchedular = new(ELeave) CActiveSchedulerWait();
	iTimer			= CWatchTimer::NewL(EPriorityNormal,this);

	}

CTestVibraNotificationCancel::CTestVibraNotificationCancel() :
CActive(EPriorityStandard),iResult(-1)
	{
	}

void CTestVibraNotificationCancel::DoCancel()
	{
	
	//TRAPD(err1,iSysInfoService->GetInfoL(req1));
		
	}

void CTestVibraNotificationCancel::RunL()
	{
	TestFunc();
	}

void CTestVibraNotificationCancel::Start()
	{
	
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();
	}

TInt CTestVibraNotificationCancel::Result()
	{
	return iResult;
	}

void CTestVibraNotificationCancel::TestFunc()
	{
	
	TInt32 transid = 333;

	const TTimeIntervalMicroSeconds32 OneMinute(600000);

	TRAPD(err1,iSysInfoService->GetNotificationL(KGeneral,KVibraActive,transid,this));
	
	iTimer->After(OneMinute);

	iResult = err1;

	if(err1 == KErrNone)
		{
		iSysInfoService->Cancel(transid);
		
		CSysData* data1 = NULL;
		
		TRAPD(err2,iSysInfoService->GetInfoL(KGeneral,KVibraActive,data1));
		
		iResult = err2;
		
		if(err2 == KErrNone)
		{
		vibrastatus = ((CStatus*)data1)->Status();
		
		CStatus* data2 = CStatus::NewL(!vibrastatus);

		TRAPD(err3,iSysInfoService->SetInfoL(KGeneral,KVibraActive,data2));
		iResult = err3;
		
		delete data2;

		}
		
		delete data1;
		}

	return ;
	}

void CTestVibraNotificationCancel::HandleResponseL(const TDesC& /*aEntity*/,const TDesC& /*aKey*/, 
									CSysData* aResponse, TInt32 /*aTransID*/, 
									TSysRequest::TRequestType /*aType*/,TInt /*aError*/)
	{
	iResult = -1;
			
	delete aResponse;
		
	iWaitSchedular->AsyncStop();
	}


int VibraNotificationCancel()
	{
	__UHEAP_MARK;

	CTestVibraNotificationCancel* test = CTestVibraNotificationCancel::NewL();
	
	test->Start();
	TInt retval =	test->Result();
	delete test;
	__UHEAP_MARKEND;

	return retval;
	}
	
void CTestVibraNotificationCancel::HandleTimeOut()
{
	iWaitSchedular->AsyncStop();
}	

