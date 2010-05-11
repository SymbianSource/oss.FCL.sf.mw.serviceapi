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
* Description:   tsysinforegstatusnotify
*
*/



#include "tsysinfonetworktests.h"
#include "sysinfoservice.h"
#include "entitykeys.h"
#include "tsysinforegstatusnotify.h"

using namespace SysInfo;

CRegStatusNotify* CRegStatusNotify::NewL(CStifLogger* aLog)
	{
	CRegStatusNotify* self = new(ELeave) CRegStatusNotify(aLog);
	self->ConstructL();
	return self;
	}

CRegStatusNotify::~CRegStatusNotify()
	{
	Cancel();
	
	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();
	
	delete iSysInfoService;
	delete iWaitSchedular;
	delete iTimer;
	}

void CRegStatusNotify::ConstructL()
	{
	iSysInfoService = CSysInfoService::NewL();
	iWaitSchedular  = new(ELeave) CActiveSchedulerWait();
	iTimer			= CWatchTimer::NewL(EPriorityNormal,this);
	CActiveScheduler::Add(this);
	}

CRegStatusNotify::CRegStatusNotify(CStifLogger* aLog)
							 :CActive(EPriorityStandard),
								iLog(aLog)
	{
	}

void CRegStatusNotify::DoCancel()
	{
	}

void CRegStatusNotify::RunL()
	{
	TestFuncL();
	}

void CRegStatusNotify::Start()
	{
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}

TInt CRegStatusNotify::Result()
	{
	return iResult;
	}

void CRegStatusNotify::TestFuncL()
	{
	TInt64 x = 6000000000;
  const TTimeIntervalMicroSeconds32 OneMinute = TTimeIntervalMicroSeconds32(x);
	TRAPD(err ,iSysInfoService->GetNotificationL(KNetwork,KRegistrationStatus,9999,this));
	iResult = err ;
	iTimer->After(OneMinute);
	}

void CRegStatusNotify::HandleResponseL(const TDesC& /*aEntity*/,const TDesC& /*aKey*/,
	 					CSysData* aOutput, TInt32 aTransID, TSysRequest::TRequestType /*aType*/,TInt aError)
	{

	iLog->Log(_L("RegStatusNotify..."));
	
	if(!aError)
		{
		TInt32 tid = aTransID;
		TInt networkMode= ((CStatus*)aOutput)->Status();
		
		TBuf<20> buf;
		buf.AppendNum(networkMode);
		iLog->Log(buf);

		iResult = PASS;
		
		}
	else
		{
		iLog->Log(_L("ERROR SET"));
		iResult = FAIL;
		}
	delete aOutput;
	iWaitSchedular->AsyncStop();
	}

void CRegStatusNotify::HandleTimeOut()
{
	iLog->Log(_L("TimeOut reached..."));
	iSysInfoService->Cancel(9999);
	iResult = FAIL;
	iWaitSchedular->AsyncStop();
}



