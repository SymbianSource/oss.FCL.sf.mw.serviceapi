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
* Description:   tsysinfocellidasync
*
*/



#include "tsysinfonetworktests.h"
#include "sysinfoservice.h"
#include "entitykeys.h"
#include "tsysinfocellidasync.h"

using namespace SysInfo;

CCellidAsync* CCellidAsync::NewL(CStifLogger* aLog)
	{
	CCellidAsync* self = new(ELeave) CCellidAsync(aLog);
	self->ConstructL();
	return self;
	}

CCellidAsync::~CCellidAsync()
	{
	Cancel();
	
	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();
	
	delete iSysInfoService;
	delete iWaitSchedular;
	delete iTimer;
	}

void CCellidAsync::ConstructL()
	{
	iSysInfoService = CSysInfoService::NewL();
	iWaitSchedular  = new(ELeave) CActiveSchedulerWait();
	iTimer			= CWatchTimer::NewL(EPriorityNormal,this);
	CActiveScheduler::Add(this);
	}

CCellidAsync::CCellidAsync(CStifLogger* aLog)
							 :CActive(EPriorityStandard),
								iLog(aLog)
	{
	}

void CCellidAsync::DoCancel()
	{
	}

void CCellidAsync::RunL()
	{
	TestFuncL();
	}

void CCellidAsync::Start()
	{
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}

TInt CCellidAsync::Result()
	{
	return iResult;
	}

void CCellidAsync::TestFuncL()
	{
	TInt64 x = 6000000000;
  const TTimeIntervalMicroSeconds32 OneMinute = TTimeIntervalMicroSeconds32(x);
	iTransId = 333;
	TRAPD(err ,iSysInfoService->GetInfoL(KNetwork,KCellID,iTransId,this));
	iResult  = err;
	iTimer->After(OneMinute);

		if(iResult == KErrNotFound)
			{
			iLog->Log(_L("KErrNotFound:"));
			iResult =  0;
			iWaitSchedular->AsyncStop();
			}
		else
			{
			iResult =  -1;	
			}
			

	}

void CCellidAsync::HandleResponseL(const TDesC& /*aEntity*/,const TDesC& /*aKey*/,
	 					CSysData* aOutput, TInt32 aTransID, TSysRequest::TRequestType /*aType*/,TInt aError)
	{
	iResult =KErrGeneral;

	iWaitSchedular->AsyncStop();
	}

void CCellidAsync::HandleTimeOut()
{
	iLog->Log(_L("TimeOut reached..."));
	iSysInfoService->Cancel(1);
	iResult = FAIL;
	iWaitSchedular->AsyncStop();
}



