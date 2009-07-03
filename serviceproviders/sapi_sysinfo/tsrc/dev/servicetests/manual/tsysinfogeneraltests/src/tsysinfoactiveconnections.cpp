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
* Description:   tsysinfoactiveconnections
*
*/



#include "sysinfoservice.h"
#include"entitykeys.h"
#include"tsysinfogeneraltests.h"

using namespace SysInfo;


class CTestActiveConn : public CActive ,public ISystemObserver
{
public:
	static CTestActiveConn* NewL(CStifLogger* aLog);
	~CTestActiveConn();
	void Start();
	TInt Result();

	 void HandleResponseL(const TDesC& aEntity,const TDesC& aKey, 
									CSysData* aResponse, TInt32 aTransID, 
									TSysRequest::TRequestType aType,TInt aError=KErrNone);

private:
	void ConstructL();
	CTestActiveConn(CStifLogger* aLog);
	
	virtual void DoCancel();
	virtual void RunL();
	
	
	void TestFunc();

	
	
private:	
	CActiveSchedulerWait* 	iWaitSchedular;
	CSysInfoService*		iSysInfoService;
	TInt bluetoothstatus ;
	TInt 					iResult;
	CStifLogger*			iLog;
	
};

CTestActiveConn* CTestActiveConn::NewL(CStifLogger* aLog)
	{
	CTestActiveConn* self = new(ELeave) CTestActiveConn(aLog);
	self->ConstructL();
	return self;
	}

CTestActiveConn::~CTestActiveConn()
	{
	Cancel();
	
	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();
	
	if(iSysInfoService)
		delete iSysInfoService;
	
	if(iWaitSchedular)
		delete iWaitSchedular;
	}

void CTestActiveConn::ConstructL()
	{
	CActiveScheduler::Add(this);
	iSysInfoService = CSysInfoService::NewL();
	iWaitSchedular = new(ELeave) CActiveSchedulerWait();
	}

CTestActiveConn::CTestActiveConn(CStifLogger* aLog) :
CActive(EPriorityStandard),iResult(KErrNone),iLog(aLog)
	{
	}

void CTestActiveConn::DoCancel()
	{
	
		
	}

void CTestActiveConn::RunL()
	{
	TestFunc();
	}

void CTestActiveConn::Start()
	{
	
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}

TInt CTestActiveConn::Result()
	{
	return iResult;
	}

void CTestActiveConn::TestFunc()
	{
	TRAPD(err1,iSysInfoService->GetInfoL(KConnectivity,KActiveConnections,7766,this));
	iResult = err1;

	return ;
	}

void CTestActiveConn::HandleResponseL(const TDesC& aEntity,const TDesC& aKey, 
									CSysData* aResponse, TInt32 aTransID, 
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
	
int ActiveConnection(CStifLogger* aLog)
	{
	__UHEAP_MARK;
	CTestActiveConn* test = CTestActiveConn::NewL(aLog);
	
	test->Start();
	TInt retval =	test->Result();
	delete test;
	
	__UHEAP_MARKEND;
	return retval;
	}

