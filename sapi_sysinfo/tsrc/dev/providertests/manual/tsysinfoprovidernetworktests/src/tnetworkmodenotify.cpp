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



#include "TSysNetwork.h"
#include "sysinfoservice.h"
#include "entitykeys.h"
#include "tnetworkmodenotify.h"

using namespace LIW ;
using namespace SysInfo;

CNetModeNotify* CNetModeNotify::NewL(CStifLogger* aLog)
	{
	CNetModeNotify* self = new(ELeave) CNetModeNotify(aLog);
	self->ConstructL();
	return self;
	}

CNetModeNotify::~CNetModeNotify()
	{
	Cancel();
	
	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();
	
	delete iSysInfoService;
	delete iWaitSchedular;
	delete iTimer;
	}

void CNetModeNotify::ConstructL()
	{
	iSysInfoService = CSysInfoService::NewL();
	iWaitSchedular  = new(ELeave) CActiveSchedulerWait();
	iTimer			= CWatchTimer::NewL(EPriorityNormal,this);
	CActiveScheduler::Add(this);
	}

CNetModeNotify::CNetModeNotify(CStifLogger* aLog)
							 :CActive(EPriorityStandard),
								iLog(aLog)
	{
	}

void CNetModeNotify::DoCancel()
	{
	}

void CNetModeNotify::RunL()
	{
	TestFuncL();
	}

void CNetModeNotify::Start()
	{
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}

TInt CNetModeNotify::Result()
	{
	return iResult;
	}

void CNetModeNotify::TestFuncL()
	{
	const TTimeIntervalMicroSeconds32 OneMinute(6000000000);
	iSysInfoService->GetNotificationL(KNetwork,KNetworkMode,111,this);
	iTimer->After(OneMinute);
	}

void CNetModeNotify::HandleResponseL(const TDesC& aEntity,const TDesC& aKey,
	 					CSysData* aOutput, TInt32 aTransID, TInt aError)
	{
	aEntity;
	aKey;
	delete iTimer;
	iTimer = NULL;
	
	iLog->Log(_L("Network mode read..."));
	
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

void CNetModeNotify::HandleTimeOut()
{
	iLog->Log(_L("TimeOut reached..."));
	iSysInfoService->Cancel(1);
	iResult = FAIL;
	iWaitSchedular->AsyncStop();
}



