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
#include "tbatstrnoti.h"

using namespace SysInfo;

CBatStrengthNoti* CBatStrengthNoti::NewL(CStifLogger* aLog)
	{
	CBatStrengthNoti* self = new(ELeave) CBatStrengthNoti(aLog);
	self->ConstructL();
	return self;
	}

CBatStrengthNoti::~CBatStrengthNoti()
	{
	Cancel();
	
	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();
	
	delete iSysInfoService;
	delete iWaitSchedular;
	delete iTimer;
	}

void CBatStrengthNoti::ConstructL()
	{
	iSysInfoService = CSysInfoService::NewL();
	iWaitSchedular  = new(ELeave) CActiveSchedulerWait();
	iTimer			= CWatchTimer::NewL(EPriorityNormal,this);
	CActiveScheduler::Add(this);
	}

CBatStrengthNoti::CBatStrengthNoti(CStifLogger* aLog)
							 :CActive(EPriorityStandard),
								iLog(aLog)
	{
	}

void CBatStrengthNoti::DoCancel()
	{
	}

void CBatStrengthNoti::RunL()
	{
	TestFuncL();
	}

void CBatStrengthNoti::Start()
	{
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}

TInt CBatStrengthNoti::Result()
	{
	return iResult;
	}

void CBatStrengthNoti::TestFuncL()
	{
	const TTimeIntervalMicroSeconds32 OneMinute(60000000);
	iSysInfoService->GetNotificationL(KBattery,KBatteryStrength,1,this);
	iTimer->After(OneMinute);
	}

void CBatStrengthNoti::HandleResponseL(const TDesC& aEntity,const TDesC& aKey,
	 					CSysData* aOutput, TInt32 aTransID, TSysRequest::TRequestType /*aType*/,TInt aError)
	{
	delete iTimer;
	iTimer = NULL;

	iLog->Log(_L("Entity: %s, Key: %s "),aEntity.Ptr(),aKey.Ptr());
	
	if(aEntity.Compare(KBattery) || aKey.Compare(KBatteryStrength))
		iLog->Log(_L("Incorrect Entity,Key.."));

	iLog->Log(_L("Battery Strength changed.."));
	
	if(!aError)
		{
		TInt32 tid = aTransID;
		if(tid != 1)
			{
			iResult = FAIL;
			iLog->Log(_L("Incorrect TID Retured.. %d"),tid);
			}
			
		TInt BatteryStrength = ((CStatus*)aOutput)->Status();
		
		iLog->Log(_L("Battery Strength: %d"),BatteryStrength);
		
		if( !(BatteryStrength > 0 && BatteryStrength <= 100) )
			{
			iResult = FAIL;
			iLog->Log(_L("Battery Strength is out of range"));
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

void CBatStrengthNoti::HandleTimeOut()
	{
	iLog->Log(_L("CBatStrengthNoti Notification TimeOut reached..."));
	iSysInfoService->Cancel(1);
	iResult = FAIL;
	iWaitSchedular->AsyncStop();
	}

