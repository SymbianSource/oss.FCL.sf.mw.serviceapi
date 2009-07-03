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
* Description:   tsysinfoconnectionnotify
*
*/



#include "sysinfoservice.h"

#include"entitykeys.h"
#include"tsysinfogeneraltests.h"

using namespace SysInfo;

class CTestConnNotify : public CActive ,public ISystemObserver
{
public:
	static CTestConnNotify* NewL(CStifLogger* aLog);
	~CTestConnNotify();
	void Start();
	TInt Result();

	 void HandleResponseL(const TDesC& aEntity,const TDesC& aKey, 
									CSysData* aResponse, TInt32 aTransID, 
									TSysRequest::TRequestType aType, TInt aError=KErrNone);

private:
	void ConstructL();
	CTestConnNotify(CStifLogger* aLog);
	
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

CTestConnNotify* CTestConnNotify::NewL(CStifLogger* aLog)
	{
	CTestConnNotify* self = new(ELeave) CTestConnNotify(aLog);
	self->ConstructL();
	return self;
	}

CTestConnNotify::~CTestConnNotify()
	{
	Cancel();
	
	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();
	
	if(iSysInfoService)
		delete iSysInfoService;
	
	if(iWaitSchedular)
		delete iWaitSchedular;
	}

void CTestConnNotify::ConstructL()
	{
	CActiveScheduler::Add(this);
	iSysInfoService = CSysInfoService::NewL();
	iWaitSchedular = new(ELeave) CActiveSchedulerWait();
	}

CTestConnNotify::CTestConnNotify(CStifLogger* aLog) :
CActive(EPriorityStandard),iResult(KErrNone),iLog(aLog)
	{
	}

void CTestConnNotify::DoCancel()
	{
	
	//TRAPD(err1,iSysInfoService->GetInfoL(req1));
		
	}

void CTestConnNotify::RunL()
	{
	TestFunc();
	}

void CTestConnNotify::Start()
	{
	
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}

TInt CTestConnNotify::Result()
	{
	return iResult;
	}

void CTestConnNotify::TestFunc()
	{
	TRAPD(err1,iSysInfoService->GetNotificationL(KConnectivity,KConnectionStatus,6655,this));
	iResult = err1;
	
	return ;
	}

void CTestConnNotify::HandleResponseL(const TDesC& aEntity,const TDesC& aKey, 
									CSysData* aResponse, TInt32 aTransID, 
									TSysRequest::TRequestType /*aType*/,TInt aError)
	{
	
		if(aError == KErrNone) 
			{
			const CConnectionInfo* conninfo = (CConnectionInfo*)aResponse;
		
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
				
			iResult = aError;
			}
	
	iResult = aError;
	delete aResponse;

	iWaitSchedular->AsyncStop();
	}


int ConnectionNotification(CStifLogger* aLog)
	{
	__UHEAP_MARK;
	CTestConnNotify* test = CTestConnNotify::NewL(aLog);
	
	test->Start();
	TInt retval =	test->Result();
	//test->Cancel();
	delete test;
	
	__UHEAP_MARKEND;
	return retval;
	}

