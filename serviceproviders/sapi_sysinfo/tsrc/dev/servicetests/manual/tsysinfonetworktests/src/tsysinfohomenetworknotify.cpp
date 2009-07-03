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
* Description:   tsysinfohomenetworknotify
*
*/



#include "tsysinfonetworktests.h"
#include "sysinfoservice.h"
#include "entitykeys.h"
#include "tsysinfohomenetworknotify.h"

using namespace SysInfo;

CHomeNetworkNotify* CHomeNetworkNotify::NewL(CStifLogger* aLog)
	{
	CHomeNetworkNotify* self = new(ELeave) CHomeNetworkNotify(aLog);
	self->ConstructL();
	return self;
	}

CHomeNetworkNotify::~CHomeNetworkNotify()
	{
	Cancel();
	
	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();
	
	delete iSysInfoService;
	delete iWaitSchedular;
	delete iTimer;
	}

void CHomeNetworkNotify::ConstructL()
	{
	iSysInfoService = CSysInfoService::NewL();
	iWaitSchedular  = new(ELeave) CActiveSchedulerWait();
	iTimer			= CWatchTimer::NewL(EPriorityNormal,this);
	CActiveScheduler::Add(this);
	}

CHomeNetworkNotify::CHomeNetworkNotify(CStifLogger* aLog)
							 :CActive(EPriorityStandard),
								iLog(aLog)
	{
	}

void CHomeNetworkNotify::DoCancel()
	{
	}

void CHomeNetworkNotify::RunL()
	{
	TestFuncL();
	}

void CHomeNetworkNotify::Start()
	{
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}

TInt CHomeNetworkNotify::Result()
	{
	return iResult;
	}

void CHomeNetworkNotify::TestFuncL()
	{
	const TTimeIntervalMicroSeconds32 OneMinute(6000000000);
	iTransId = 222;
	TRAPD(err,iSysInfoService->GetNotificationL(KNetwork,KCurrentNetwork,iTransId,this));
	iResult  = err;
	iTimer->After(OneMinute);
	
	if(iResult == KErrNotFound)
		{
		iLog->Log(_L(" KErrNotFound: "));
		iResult =  0;
		iWaitSchedular->AsyncStop();
		}
	else
		{
		iResult =  -1;	
		}
		
	}

void CHomeNetworkNotify::HandleResponseL(const TDesC& /*aEntity*/,const TDesC& /*aKey*/,
	 					CSysData* aOutput, TInt32 aTransID, TSysRequest::TRequestType /*aType*/,TInt aError)
	{
	iResult =KErrGeneral;

	iWaitSchedular->AsyncStop();
	}

void CHomeNetworkNotify::HandleTimeOut()
{
	iLog->Log(_L("TimeOut reached..."));
	iSysInfoService->Cancel(1);
	iResult = FAIL;
	iWaitSchedular->AsyncStop();
}



