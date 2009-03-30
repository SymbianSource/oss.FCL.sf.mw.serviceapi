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
#include "tbatlvlnoti.h"

using namespace SysInfo;

CBatLvlNoti* CBatLvlNoti::NewL(CStifLogger* aLog)
	{
	CBatLvlNoti* self = new(ELeave) CBatLvlNoti(aLog);
	self->ConstructL();
	return self;
	}

CBatLvlNoti::~CBatLvlNoti()
	{
	Cancel();
	
	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();
	
	delete iSysInfoService;
	delete iWaitSchedular;
	delete iTimer;
	}

void CBatLvlNoti::ConstructL()
	{
	iSysInfoService = CSysInfoService::NewL();
	iWaitSchedular  = new(ELeave) CActiveSchedulerWait();
	iTimer			= CWatchTimer::NewL(EPriorityNormal,this);
	CActiveScheduler::Add(this);
	}

CBatLvlNoti::CBatLvlNoti(CStifLogger* aLog)
							 :CActive(EPriorityStandard),
								iLog(aLog)
	{
	}

void CBatLvlNoti::DoCancel()
	{
	}

void CBatLvlNoti::RunL()
	{
	TestFuncL();
	}

void CBatLvlNoti::Start()
	{
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}

TInt CBatLvlNoti::Result()
	{
	return iResult;
	}

void CBatLvlNoti::TestFuncL()
	{
	const TTimeIntervalMicroSeconds32 OneMinute(60000000);
	iSysInfoService->GetNotificationL(KBattery,KBatteryLevel,1,this);
	iTimer->After(OneMinute);
	}

void CBatLvlNoti::HandleResponseL(const TDesC& aEntity,const TDesC& aKey,
	 					CSysData* aOutput, TInt32 aTransID, TSysRequest::TRequestType /*aType*/,TInt aError)
	{
	delete iTimer;
	iTimer = NULL;
	
	iLog->Log(_L("Entity: %s, Key: %s "),aEntity.Ptr(),aKey.Ptr());
	
	if(aEntity.Compare(KBattery) || aKey.Compare(KChargingStatus))
		iLog->Log(_L("Incorrect Entity,Key.."));

	iLog->Log(_L("Battery Level changed.."));
	
	if(!aError)
		{
		TInt32 tid = aTransID;
		if(tid != 1)
			{
			iResult = FAIL;
			iLog->Log(_L("Incorrect TID Retured.. %d"),tid);
			}
			
		TInt BatLvl = ((CStatus*)aOutput)->Status();
		
		iLog->Log(_L("Battery Level: %d "),BatLvl);
		
		if( BatLvl >= 0	&& BatLvl <= 7 )
			{
			iResult = PASS;
			iLog->Log(_L("Battery level is with in expected range"));
			}
		else
			{
			iResult = FAIL;
			iLog->Log(_L("Battery level is out of range"));
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

void CBatLvlNoti::HandleTimeOut()
{
	iLog->Log(_L("CBatLvlNoti TimeOut reached..."));
	iSysInfoService->Cancel(1);
	iResult = FAIL;
	iWaitSchedular->AsyncStop();
}
