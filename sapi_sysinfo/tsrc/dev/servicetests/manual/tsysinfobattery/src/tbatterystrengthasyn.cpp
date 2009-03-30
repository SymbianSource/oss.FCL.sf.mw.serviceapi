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



#include "TSysBattery.h"
#include "sysinfoservice.h"
#include "entitykeys.h"
#include "tbatterystrengthasyn.h"

using namespace SysInfo;

CBatteryStrengthAsync* CBatteryStrengthAsync::NewL(CStifLogger* aLog)
	{
	CBatteryStrengthAsync* self = new(ELeave) CBatteryStrengthAsync(aLog);
	self->ConstructL();
	return self;
	}

CBatteryStrengthAsync::~CBatteryStrengthAsync()
	{
	Cancel();
	
	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();
	
	delete iSysInfoService;
	delete iWaitSchedular;
	delete iTimer;
	}

void CBatteryStrengthAsync::ConstructL()
	{
	iSysInfoService = CSysInfoService::NewL();
	iWaitSchedular  = new(ELeave) CActiveSchedulerWait();
	iTimer			= CWatchTimer::NewL(EPriorityNormal,this);
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
	TestFuncL();
	}

void CBatteryStrengthAsync::Start()
	{
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}

TInt CBatteryStrengthAsync::Result()
	{
	return iResult;
	}

void CBatteryStrengthAsync::TestFuncL()
	{
	const TTimeIntervalMicroSeconds32 OneMinute(60000000);
	iSysInfoService->GetInfoL(KBattery,KBatteryStrength,1,this);
	iTimer->After(OneMinute);
	}

void CBatteryStrengthAsync::HandleResponseL(const TDesC& aEntity,const TDesC& aKey,
	 					CSysData* aOutput, TInt32 aTransID, TSysRequest::TRequestType /*aType*/,TInt aError)
	{
	delete iTimer;
	iTimer = NULL;
	
	iLog->Log(_L("Entity: %s, Key: %s "),aEntity.Ptr(),aKey.Ptr());
	
	if(aEntity.Compare(KBattery) || aKey.Compare(KBatteryStrength))
		iLog->Log(_L("Incorrect Entity,Key.."));
	
	iLog->Log(_L("Battery Strength read.."));
	
	if(!aError)
		{
		TInt32 tid = aTransID;
		if(tid != 1)
			{
			iResult = FAIL;
			iLog->Log(_L("Incorrect TID Retured.. %d"),tid);
			}
		
		TInt BatteryStrength = ((CStatus*)aOutput)->Status();
		
		iLog->Log(_L("Battery Strength: %d "),BatteryStrength);
		
		if( BatteryStrength > 0	&& BatteryStrength <= 100 )
			{
			iResult = PASS;
			iLog->Log(_L("Battery strength is with in expected range"));
			}
		else
			{
			iResult = FAIL;
			iLog->Log(_L("Battery strength is out of range"));
			}
		delete aOutput;
		}
	else
		{
		iLog->Log(_L("ERROR SET"));
		iResult = FAIL;
		}
	iWaitSchedular->AsyncStop();
	}

void CBatteryStrengthAsync::HandleTimeOut()
{
	iLog->Log(_L("CBatteryStrengthAsync TimeOut reached..."));
	iSysInfoService->Cancel(1);
	iResult = FAIL;
	iWaitSchedular->AsyncStop();
}
