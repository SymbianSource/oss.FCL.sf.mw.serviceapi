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
* Description:   Tests battery notifications
*
*/



#include "TSysBattery.h"
#include "sysinfoservice.h"
#include "entitykeys.h"
#include "tsysbatterynot.h"

using namespace SysInfo;

CBatteryNot* CBatteryNot::NewL(CStifLogger* aLog, TInt aCmdId)
	{
	CBatteryNot* self = new(ELeave) CBatteryNot(aLog,aCmdId );
	self->ConstructL();
	return self;
	}

CBatteryNot::~CBatteryNot()
	{
	Cancel();
	
	if(iWaitScheduler->IsStarted())
		iWaitScheduler->AsyncStop();
	
	delete iSysInfoService;
	delete iWaitScheduler;
	delete iTimer;
	}

void CBatteryNot::ConstructL()
	{
	iSysInfoService = CSysInfoService::NewL();
	iWaitScheduler  = new(ELeave) CActiveSchedulerWait();
	iTimer			= CWatchTimer::NewL(EPriorityNormal,this);
	CActiveScheduler::Add(this);
	}

CBatteryNot::CBatteryNot(CStifLogger* aLog, TInt aCmdId)
							 :CActive(EPriorityStandard),
								iLog(aLog), iCmdId(aCmdId)
	{
	}

void CBatteryNot::DoCancel()
	{
	}

void CBatteryNot::RunL()
	{
	if(iCmdId == EWrongData)
		{
		TRAP(iResult,TestFuncL());	
		}
	
	else if(iCmdId == EWrongKey)
		{
		TRAP(iResult,TestFunc1L());
		}
	iWaitScheduler->AsyncStop();
	}

void CBatteryNot::Start()
	{
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitScheduler->Start();	
	}

TInt CBatteryNot::Result()
	{
	return iResult ;
	}

void CBatteryNot::TestFuncL()
	{
	_LIT(KSample,"Simple") ;
//	const TTimeIntervalMicroSeconds32 threeMin(180000000);
	CStringData* inputData = CStringData::NewL(KSample) ; 
	CleanupStack::PushL(inputData);
	iSysInfoService->GetNotificationL(KBattery,KBatteryStrength,1,this,inputData);
//	iTimer->After(threeMin);
//	delete inputData ;
	CleanupStack::PopAndDestroy() ;
	}

void CBatteryNot::TestFunc1L()
	{
	_LIT(KSample,"Simple") ;
	CStringData* inputData = CStringData::NewL(KSample) ; 
	CleanupStack::PushL(inputData);
	iSysInfoService->GetNotificationL(KBattery,KSample,1,this,inputData);
	CleanupStack::PopAndDestroy() ;
	}
	
void CBatteryNot::HandleResponseL(const TDesC& /*aEntity*/,const TDesC& /*aKey*/,
	 					CSysData* aOutput, TInt32 /*aTransID*/,TSysRequest::TRequestType /*aType*/, TInt /*aError*/)
	{
	
	delete aOutput ;
	
	}

void CBatteryNot::HandleTimeOut()
{
	
}
