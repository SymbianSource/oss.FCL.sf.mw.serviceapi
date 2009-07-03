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
#include <btengsettings.h>

using namespace SysInfo;


class CTestAsync : public CActive ,public ISystemObserver
{
public:
	static CTestAsync* NewL();
	~CTestAsync();
	void Start();
	TInt Result();

 void HandleResponseL(const TDesC& aEntity,const TDesC& aKey, 
									CSysData* aResponse, TInt32 aTransID, 
									TSysRequest::TRequestType aType, TInt aError=KErrNone);

private:
	void ConstructL();
	CTestAsync();
	
	virtual void DoCancel();
	virtual void RunL();
	
	
	void TestFunc();

	
	
private:	
	CActiveSchedulerWait* 	iWaitSchedular;
	CSysInfoService*		iSysInfoService;
	TInt bluetoothstatus ;
	TInt 					iResult;	
};



CTestAsync* CTestAsync::NewL()
	{
	CTestAsync* self = new(ELeave) CTestAsync();
	self->ConstructL();
	return self;
	}

CTestAsync::~CTestAsync()
	{
	Cancel();
	
	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();
	
	if(iSysInfoService)
		delete iSysInfoService;
	
	if(iWaitSchedular)
		delete iWaitSchedular;
	}

void CTestAsync::ConstructL()
	{
	CActiveScheduler::Add(this);
	iSysInfoService = CSysInfoService::NewL();
	iWaitSchedular = new(ELeave) CActiveSchedulerWait();
	}

CTestAsync::CTestAsync() :
CActive(EPriorityStandard),iResult(KErrNone)
	{
	}

void CTestAsync::DoCancel()
	{
	}

void CTestAsync::RunL()
	{
	TestFunc();
	}

void CTestAsync::Start()
	{
	
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}

TInt CTestAsync::Result()
	{
	return iResult;
	}

void CTestAsync::TestFunc()
	{

// On Emulator this is not supported.				
#if (! (defined(__WINS__) || defined(__WINSCW__)) )
	TRAPD(err1,iSysInfoService->GetNotificationL(KConnectivity,KBlueTooth,9988,this));
	iResult =err1; 
	if(err1 == KErrNone)
		{
		CSysData* data1 = NULL;
		
		TRAPD(err2,iSysInfoService->GetInfoL(KConnectivity,KBlueTooth,data1));
		iResult =err2; 
		if(err2 == KErrNone)
			{
			bluetoothstatus = ((CStatus*)data1)->Status();

			CBTEngSettings* BtSettings = CBTEngSettings::NewLC();
	        TInt err3(KErrNone);
			if( bluetoothstatus == EOn)
			    err3 = BtSettings->SetPowerState( EBTPowerOff );
	        else if(bluetoothstatus == EOff)
	            err3 = BtSettings->SetPowerState( EBTPowerOn );
	        else
	            err3 = KErrArgument;
	        CleanupStack::PopAndDestroy(BtSettings);

			if(err3)
				{
				iResult = err3;
				iWaitSchedular->AsyncStop();
				}
			}
		delete  data1;
		}
#else
	iResult = 0;
	iWaitSchedular->AsyncStop();
#endif
	
	return ;
	}

void CTestAsync::HandleResponseL(const TDesC& /*aEntity*/,const TDesC& /*aKey*/, 
									CSysData* aResponse, TInt32 /*aTransID*/, 
									TSysRequest::TRequestType /*aType*/,TInt /*aError*/)
	{
	const CStatus* data1 = (CStatus*)aResponse;
	if((data1->Status() ) == (!bluetoothstatus) )
		{
			iResult = KErrNone;
		}
	else
		{
			iResult = -1;
		}

    CBTEngSettings* BtSettings = CBTEngSettings::NewLC();
    TInt err3(KErrNone);
    if( bluetoothstatus == EOn)
        err3 = BtSettings->SetPowerState( EBTPowerOff );
    else if(bluetoothstatus == EOff)
        err3 = BtSettings->SetPowerState( EBTPowerOn );
    else
        err3 = KErrArgument;
    CleanupStack::PopAndDestroy(BtSettings);	
	
    delete aResponse;
    data1 = NULL;
    iWaitSchedular->AsyncStop();	
	}


int ReqNotification(int, char**)
	{
	__UHEAP_MARK;
	CTestAsync* test = CTestAsync::NewL();
	
	test->Start();
	TInt retval =	test->Result();

	delete test;

	__UHEAP_MARKEND;

	return retval;
	}
