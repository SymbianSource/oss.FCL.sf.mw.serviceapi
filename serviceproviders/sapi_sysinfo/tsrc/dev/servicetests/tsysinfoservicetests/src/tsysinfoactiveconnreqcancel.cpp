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


class CTestActiveConnReqCancel : public CActive ,public ISystemObserver, public MTimeOutCallBack
	{
	public:
		static CTestActiveConnReqCancel* NewL();
		~CTestActiveConnReqCancel();
		void Start();
		TInt Result();

		 void HandleResponseL(const TDesC& aEntity,const TDesC& aKey, 
										CSysData* aResponse, TInt32 aTransID, 
										TSysRequest::TRequestType aType, TInt aError=KErrNone);
		 void HandleTimeOut	();

	private:
		void ConstructL();
		CTestActiveConnReqCancel();
		
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

CTestActiveConnReqCancel* CTestActiveConnReqCancel::NewL()
	{
	CTestActiveConnReqCancel* self = new(ELeave) CTestActiveConnReqCancel();
	self->ConstructL();
	return self;
	}

CTestActiveConnReqCancel::~CTestActiveConnReqCancel()
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

void CTestActiveConnReqCancel::ConstructL()
	{
	CActiveScheduler::Add(this);
	iSysInfoService = CSysInfoService::NewL();
	iWaitSchedular = new(ELeave) CActiveSchedulerWait();
	iTimer			= CWatchTimer::NewL(EPriorityNormal,this);

	}

CTestActiveConnReqCancel::CTestActiveConnReqCancel() :
CActive(EPriorityStandard),iResult(KErrNone)
	{
	}

void CTestActiveConnReqCancel::DoCancel()
	{
	
	//TRAPD(err1,iSysInfoService->GetInfoL(req1));
		
	}

void CTestActiveConnReqCancel::RunL()
	{
	TestFunc();
	}

void CTestActiveConnReqCancel::Start()
	{
	
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();
	}

TInt CTestActiveConnReqCancel::Result()
	{
	return iResult;
	}

void CTestActiveConnReqCancel::TestFunc()
	{
	
	TInt32 transid = 5544;
	
	const TTimeIntervalMicroSeconds32 OneMinute(600000);

	TRAPD(err1,iSysInfoService->GetInfoL(KConnectivity,KActiveConnections,transid,this));
	iResult = err1;
	
	iSysInfoService->Cancel(transid);
	
	iTimer->After(OneMinute);

	}

void CTestActiveConnReqCancel::HandleResponseL(const TDesC& /*aEntity*/,const TDesC& /*aKey*/, 
									CSysData* aResponse, TInt32 /*aTransID*/, 
									TSysRequest::TRequestType /*aType*/,TInt /*aError*/)
	{
	iResult =KErrGeneral;
			
	delete aResponse;
		
	iWaitSchedular->AsyncStop();
	}


int GetActiveConnReqCancel()
	{
	__UHEAP_MARK;

	CTestActiveConnReqCancel* test = CTestActiveConnReqCancel::NewL();
	
	test->Start();
	TInt retval =	test->Result();
	delete test;
	__UHEAP_MARKEND;

	return retval;
	}
	
void CTestActiveConnReqCancel::HandleTimeOut()
{
	iWaitSchedular->AsyncStop();
}	

