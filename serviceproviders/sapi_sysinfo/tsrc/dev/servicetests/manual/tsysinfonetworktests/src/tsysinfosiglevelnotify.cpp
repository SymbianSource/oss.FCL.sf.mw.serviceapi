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
* Description:   tsysinfosiglevelnotify
*
*/



#include "tsysinfonetworktests.h"
#include "sysinfoservice.h"
#include "entitykeys.h"
#include "tsysinfosiglevelnotify.h"

using namespace SysInfo;

CSigLevelNotify* CSigLevelNotify::NewL(CStifLogger* aLog)
	{
	CSigLevelNotify* self = new(ELeave) CSigLevelNotify(aLog);
	self->ConstructL();
	return self;
	}

CSigLevelNotify::~CSigLevelNotify()
	{
	Cancel();
	
	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();
	
	delete iSysInfoService;
	delete iWaitSchedular;
	delete iTimer;
	}

void CSigLevelNotify::ConstructL()
	{
	iSysInfoService = CSysInfoService::NewL();
	iWaitSchedular  = new(ELeave) CActiveSchedulerWait();
	iTimer			= CWatchTimer::NewL(EPriorityNormal,this);
	CActiveScheduler::Add(this);
	}

CSigLevelNotify::CSigLevelNotify(CStifLogger* aLog)
							 :CActive(EPriorityStandard),
								iLog(aLog)
	{
	}

void CSigLevelNotify::DoCancel()
	{
	}

void CSigLevelNotify::RunL()
	{
	TestFuncL();
	}

void CSigLevelNotify::Start()
	{
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}

TInt CSigLevelNotify::Result()
	{
	return iResult;
	}

void CSigLevelNotify::TestFuncL()
	{
	TInt64 x = 6000000000;
  const TTimeIntervalMicroSeconds32 OneMinute = TTimeIntervalMicroSeconds32(x);
	iTransId = 4444;
	TRAPD(err,iSysInfoService->GetNotificationL(KNetwork,KSignalLevel,iTransId,this));
	iResult  = err;
	iTimer->After(OneMinute);
	}

void CSigLevelNotify::HandleResponseL(const TDesC& /*aEntity*/,const TDesC& /*aKey*/,
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

void CSigLevelNotify::HandleTimeOut()
{
	iLog->Log(_L("TimeOut reached..."));
	iSysInfoService->Cancel(1);
	iResult = FAIL;
	iWaitSchedular->AsyncStop();
}



