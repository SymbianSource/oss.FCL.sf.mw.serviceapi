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
* Description:   tsysinfoaccessorystatus
*
*/



#include "sysinfoservice.h"
#include "tsysinfogeneraltests.h"


#include"entitykeys.h"
using namespace SysInfo;

class CTestAsync2 : public CActive ,public ISystemObserver
{
public:
	static CTestAsync2* NewL(CStifLogger* aLog);
	
	~CTestAsync2();
	
	void Start();
	
	TInt Result();

    void HandleResponseL(const TDesC& aEntity,const TDesC& aKey, 
									CSysData* aResponse, TInt32 aTransID, 
									TSysRequest::TRequestType aType,TInt aError=KErrNone);

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
	}

void CTestAsync2::ConstructL()
	{
	CActiveScheduler::Add(this);
	iSysInfoService = CSysInfoService::NewL();
	iWaitSchedular = new(ELeave) CActiveSchedulerWait();
	}

CTestAsync2::CTestAsync2(CStifLogger* aLog) :
CActive(EPriorityStandard),iResult(-1),iLog(aLog)
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

	TRAPD(err1,iSysInfoService->GetNotificationL(KGeneral,KAccessoryStatus,888,this));
	
	if(err1 != KErrNone)
		{
			iWaitSchedular->AsyncStop();
		}
	
	return ;
	}

void CTestAsync2::HandleResponseL(const TDesC& /*aEntity*/,const TDesC& /*aKey*/, 
									CSysData* aResponse, TInt32 /*aTransID*/, 
									TSysRequest::TRequestType /*aType*/,TInt aError)
	{

		if(aError == KErrNone) 
			{
			const CAccessoryInfo* accInfo= (CAccessoryInfo*)aResponse;
				
				TBuf<50> acctype ;
				TBuf<50> accConnState;
				acctype.AppendNum(	accInfo->AccessoryType() );
				accConnState.AppendNum(	accInfo->ConnectionState() );
 				iLog->Log(_L("Accessory Type:"));
				iLog->Log(acctype);

 				iLog->Log(_L("Accessory Connection State:"));
				iLog->Log(accConnState);

			 		
			iResult = KErrNone;
			delete aResponse;

			}

	iWaitSchedular->AsyncStop();
	
	}


int AccStatusNotification(CStifLogger* aLog)
	{
	__UHEAP_MARK;

	CTestAsync2* test = CTestAsync2::NewL(aLog);
	
	test->Start();
	TInt retval =	test->Result();
//	test->Cancel();
	delete test;
	__UHEAP_MARKEND;

	return retval;
	}

