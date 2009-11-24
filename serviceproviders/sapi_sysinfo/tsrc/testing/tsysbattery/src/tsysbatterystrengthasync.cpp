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



#include "tsysbattery.h"
#include "sysinfoservice.h"
#include "entitykeys.h"
#include "tsysbatterystrengthasync.h"

using namespace SysInfo;
_LIT(KBatteryLevel,"BatteryLevel");

CBatteryStrengthAsync* CBatteryStrengthAsync::NewL(CStifLogger* aLog)
	{
	CBatteryStrengthAsync* self = new(ELeave) CBatteryStrengthAsync(aLog);
	self->ConstructL();
	return self;
	}

CBatteryStrengthAsync::~CBatteryStrengthAsync()
	{
	Cancel();
	
	if(iWaitScheduler->IsStarted())
		iWaitScheduler->AsyncStop();
	
	delete iSysInfoService;
	delete iWaitScheduler;
//	delete iTimer;
	}

void CBatteryStrengthAsync::ConstructL()
	{
	iSysInfoService = CSysInfoService::NewL();
	iWaitScheduler  = new(ELeave) CActiveSchedulerWait();
//	iTimer			= CWatchTimer::NewL(EPriorityNormal,this);
	CActiveScheduler::Add(this);
	}

CBatteryStrengthAsync::CBatteryStrengthAsync(CStifLogger* aLog)
							 :CActive(EPriorityStandard),
								iLog(aLog)
	{
	}

void CBatteryStrengthAsync::DoCancel()
	{
	}

void CBatteryStrengthAsync::RunL()
	{
	TRAP(iResult,TestFuncL());
	iWaitScheduler->AsyncStop();
	}

void CBatteryStrengthAsync::Start()
	{
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitScheduler->Start();	
	}

TInt CBatteryStrengthAsync::Result()
	{
	return iResult;
	}

void CBatteryStrengthAsync::TestFuncL()
	{
//	const TTimeIntervalMicroSeconds32 OneMinute(60000000);
	iSysInfoService->GetInfoL(KBattery,KBatteryLevel,1,this);
//	iTimer->After(OneMinute);
	}

void CBatteryStrengthAsync::HandleResponseL(const TDesC& /*aEntity*/,const TDesC& /*aKey*/,
	 					CSysData* /*aOutput*/, TInt32 /*aTransID*/,TSysRequest::TRequestType /*aType*/, TInt /*aError*/)
	{

	}

