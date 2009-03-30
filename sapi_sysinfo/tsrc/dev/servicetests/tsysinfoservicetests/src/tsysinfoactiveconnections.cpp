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
#include "tsysinfoservicetests.h"

#include"watchtimer.h"

using namespace SysInfo;


class CTestAsync2 : public CActive ,public ISystemObserver, public MTimeOutCallBack
{
public:
	static CTestAsync2* NewL(CStifLogger* aLog);
	~CTestAsync2();
	void Start();
	TInt Result();

	 void HandleResponseL(const TDesC& aEntity,const TDesC& aKey, 
									CSysData* aResponse, TInt32 aTransID, 
									TSysRequest::TRequestType aType,TInt aError=KErrNone);
	 void HandleTimeOut	();

private:
	void ConstructL();
	CTestAsync2(CStifLogger* aLog);
	
	virtual void DoCancel();
	virtual void RunL();
	
	
	void TestFunc();

	
	
private:	
	CActiveSchedulerWait* 	iWaitSchedular;
	CSysInfoService*		iSysInfoService;
	TInt bluetoothstatus ;
	TInt 					iResult;
	CStifLogger*			iLog;
	CWatchTimer*			iTimer;

	
};

CTestAsync2* CTestAsync2::NewL(CStifLogger* aLog)
	{
	CTestAsync2* self = new(ELeave) CTestAsync2(aLog);
	self->ConstructL();
	return self;
	}

CTestAsync2::~CTestAsync2()
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

void CTestAsync2::ConstructL()
	{
	CActiveScheduler::Add(this);
	iSysInfoService = CSysInfoService::NewL();
	iWaitSchedular = new(ELeave) CActiveSchedulerWait();
	iTimer			= CWatchTimer::NewL(EPriorityNormal,this);

	}

CTestAsync2::CTestAsync2(CStifLogger* aLog) :
CActive(EPriorityStandard),iResult(KErrNone),iLog(aLog)
	{
	}

void CTestAsync2::DoCancel()
	{
	
		
	}

void CTestAsync2::RunL()
	{
	TestFunc();
	}

void CTestAsync2::Start()
	{
	
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}

TInt CTestAsync2::Result()
	{
	return iResult;
	}

void CTestAsync2::TestFunc()
	{
	const TTimeIntervalMicroSeconds32 OneMinute(600000);

	TRAPD(err1,iSysInfoService->GetInfoL(KConnectivity,KActiveConnections,7766,this));
	iResult = err1;
	iTimer->After(OneMinute);

	return ;
	}

void CTestAsync2::HandleResponseL(const TDesC& /*aEntity*/,const TDesC& /*aKey*/, 
									CSysData* aResponse, TInt32 /*aTransID*/, 
									TSysRequest::TRequestType /*aType*/,TInt aError)
	{
		if(aError == KErrNone) 
			{
			const CConnectionInfo* conninfo = NULL;
			for(TInt i=0;i< ((CConnectionList*)aResponse)->Count() ;i++)
				{
				((CConnectionList*)aResponse)->At(i,conninfo);
				
			TUint	iapid = conninfo->IAPId();
			iLog->Log(_L("iapid:"));
 			TBuf8<50> buf;
			buf.AppendNum(iapid,EDecimal);
			iLog->Log(buf);


 			
			TInt	bearerType = conninfo->BearerType();
			iLog->Log(_L("bearerType:"));
 			buf.Zero();
			buf.AppendNum(bearerType);
			iLog->Log(buf);
 			
			TPtrC	iapName = conninfo->IAPName();
			iLog->Log(_L("iapName:"));
 			buf.Zero();
			buf.Copy(iapName);
 			iLog->Log(buf);

			TPtrC	netName = conninfo->NetworkName();
			iLog->Log(_L("network name:"));
 			buf.Zero();
			buf.Copy(netName);
			iLog->Log(buf);

 			
			TPtrC	connName = conninfo->ConnectionName();
			iLog->Log(_L("Connection name:"));
 			buf.Zero();
			buf.Copy(connName);
			iLog->Log(buf);
				
			}
			
			iResult = KErrNone;
	
	}
	delete aResponse;
	iWaitSchedular->AsyncStop();
	}

void CTestAsync2::HandleTimeOut()
{
	iWaitSchedular->AsyncStop();
}	
	
int ActiveConnection(CStifLogger* aLog)
	{
	__UHEAP_MARK;
	CTestAsync2* test = CTestAsync2::NewL(aLog);
	
	test->Start();
	TInt retval =	test->Result();
	delete test;
	
	__UHEAP_MARKEND;
	return retval;
	}

