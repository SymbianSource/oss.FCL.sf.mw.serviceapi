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
* Description:   tsysinfosiglevelasync
*
*/



#include "tsysinfonetworktests.h"
#include "sysinfoservice.h"
#include "entitykeys.h"
#include "tsysinfosiglevelasync.h"

using namespace SysInfo;

CSigLevelAsync* CSigLevelAsync::NewL(CStifLogger* aLog)
	{
	CSigLevelAsync* self = new(ELeave) CSigLevelAsync(aLog);
	self->ConstructL();
	return self;
	}

CSigLevelAsync::~CSigLevelAsync()
	{
	Cancel();
	
	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();
	
	delete iSysInfoService;
	delete iWaitSchedular;
	delete iTimer;
	}

void CSigLevelAsync::ConstructL()
	{
	iSysInfoService = CSysInfoService::NewL();
	iWaitSchedular  = new(ELeave) CActiveSchedulerWait();
	iTimer			= CWatchTimer::NewL(EPriorityNormal,this);
	CActiveScheduler::Add(this);
	}

CSigLevelAsync::CSigLevelAsync(CStifLogger* aLog)
							 :CActive(EPriorityStandard),
								iLog(aLog)
	{
	}

void CSigLevelAsync::DoCancel()
	{
	}

void CSigLevelAsync::RunL()
	{
	TestFuncL();
	}

void CSigLevelAsync::Start()
	{
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}

TInt CSigLevelAsync::Result()
	{
	return iResult;
	}

void CSigLevelAsync::TestFuncL()
	{
	TInt64 x = 6000000000;
  const TTimeIntervalMicroSeconds32 OneMinute = TTimeIntervalMicroSeconds32(x);
	iTransId = 3333;
	TRAPD(err,iSysInfoService->GetInfoL(KNetwork,KSignalLevel,iTransId,this));
	iResult  = err;
	iTimer->After(OneMinute);
	}

void CSigLevelAsync::HandleResponseL(const TDesC& /*aEntity*/,const TDesC& /*aKey*/,
	 					CSysData* aOutput, TInt32 aTransID, TSysRequest::TRequestType /*aType*/,TInt aError)
	{
	iLog->Log(_L("Signal level read.."));
	
	if(!aError)
		{
		TInt32 tid = aTransID;
		TInt sigLevel = ((CStatus*)aOutput)->Status();
		
		if(tid ==iTransId)
			{
			iResult = PASS;
			iLog->Log(_L("sigLevel"));
			TBuf<50> buf;
			buf.AppendNum(sigLevel);
			iLog->Log(buf);
			}
		else
			{
			iResult = FAIL;
			iLog->Log(_L("Cell id err.."));
			}
		}
	else
		{
		iLog->Log(_L("ERROR SET"));
		iResult = FAIL;
		}
	delete aOutput;

	iWaitSchedular->AsyncStop();
	}

void CSigLevelAsync::HandleTimeOut()
{
	iLog->Log(_L("TimeOut reached..."));
	iSysInfoService->Cancel(1);
	iResult = FAIL;
	iWaitSchedular->AsyncStop();
}



