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
#include "tchargernoti.h"

using namespace SysInfo;

CChargerNoti* CChargerNoti::NewL(CStifLogger* aLog)
	{
	CChargerNoti* self = new(ELeave) CChargerNoti(aLog);
	self->ConstructL();
	return self;
	}

CChargerNoti::~CChargerNoti()
	{
	Cancel();
	
	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();
	
	delete iSysInfoService;
	delete iWaitSchedular;
	delete iTimer;
	}

void CChargerNoti::ConstructL()
	{
	iSysInfoService = CSysInfoService::NewL();
	iWaitSchedular  = new(ELeave) CActiveSchedulerWait();
	iTimer			= CWatchTimer::NewL(EPriorityNormal,this);
	CActiveScheduler::Add(this);
	}

CChargerNoti::CChargerNoti(CStifLogger* aLog)
							 :CActive(EPriorityStandard),
								iLog(aLog)
	{
	}

void CChargerNoti::DoCancel()
	{
	}

void CChargerNoti::RunL()
	{
	TestFuncL();
	}

void CChargerNoti::Start()
	{
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}

TInt CChargerNoti::Result()
	{
	return iResult;
	}

void CChargerNoti::TestFuncL()
	{
	const TTimeIntervalMicroSeconds32 OneMinute(60000000);
	iSysInfoService->GetNotificationL(KBattery,KChargingStatus,1,this);
	iTimer->After(OneMinute);
	}

void CChargerNoti::HandleResponseL(const TDesC& aEntity,const TDesC& aKey,
	 					CSysData* aOutput, TInt32 aTransID, TSysRequest::TRequestType /*aType*/,TInt aError)
	{
	delete iTimer;
	iTimer = NULL;

	iLog->Log(_L("Entity: %s, Key: %s "),aEntity.Ptr(),aKey.Ptr());
	
	if(aEntity.Compare(KBattery) || aKey.Compare(KChargingStatus))
		iLog->Log(_L("Incorrect Entity,Key.."));

	iLog->Log(_L("Charger Status changed.."));
	
	if(!aError)
		{
		TInt32 tid = aTransID;
		if(tid != 1)
			{
			iResult = FAIL;
			iLog->Log(_L("Incorrect TID Retured.. %d"),tid);
			}
		TInt IsChargerConnected = ((CStatus*)aOutput)->Status();
		
		if(IsChargerConnected)
			iLog->Log(_L("Charger Connected.."));
		else
			iLog->Log(_L("Charger DisConnected.."));
		
		if( IsChargerConnected >= 2 )
			{
			iResult = FAIL;
			iLog->Log(_L("Charger State is out of range"));
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

void CChargerNoti::HandleTimeOut()
{
	iLog->Log(_L("CCharger Notification TimeOut reached..."));
	iSysInfoService->Cancel(1);
	iResult = FAIL;
	iWaitSchedular->AsyncStop();
}

