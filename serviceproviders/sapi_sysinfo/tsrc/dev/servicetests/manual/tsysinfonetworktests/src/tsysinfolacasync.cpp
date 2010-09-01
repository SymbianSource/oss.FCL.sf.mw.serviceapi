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
* Description:   tsysinfolacasync
*
*/



#include "tsysinfonetworktests.h"
#include "sysinfoservice.h"
#include "entitykeys.h"
#include "tsysinfolacasync.h"

using namespace SysInfo;

CLacAsync* CLacAsync::NewL(CStifLogger* aLog)
	{
	CLacAsync* self = new(ELeave) CLacAsync(aLog);
	self->ConstructL();
	return self;
	}

CLacAsync::~CLacAsync()
	{
	Cancel();
	
	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();
	
	delete iSysInfoService;
	delete iWaitSchedular;
	delete iTimer;
	}

void CLacAsync::ConstructL()
	{
	iSysInfoService = CSysInfoService::NewL();
	iWaitSchedular  = new(ELeave) CActiveSchedulerWait();
	iTimer			= CWatchTimer::NewL(EPriorityNormal,this);
	CActiveScheduler::Add(this);
	}

CLacAsync::CLacAsync(CStifLogger* aLog)
							 :CActive(EPriorityStandard),
								iLog(aLog)
	{
	}

void CLacAsync::DoCancel()
	{
	}

void CLacAsync::RunL()
	{
	TestFuncL();
	}

void CLacAsync::Start()
	{
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}

TInt CLacAsync::Result()
	{
	return iResult;
	}

void CLacAsync::TestFuncL()
	{
	TInt64 x = 6000000000;
  const TTimeIntervalMicroSeconds32 OneMinute = TTimeIntervalMicroSeconds32(x);
	iTransId = 7777;
	TRAPD(err,iSysInfoService->GetInfoL(KNetwork,KLocationArea,iTransId,this));
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

void CLacAsync::HandleResponseL(const TDesC& /*aEntity*/,const TDesC& /*aKey*/,
	 					CSysData* aOutput, TInt32 aTransID, TSysRequest::TRequestType /*aType*/,TInt aError)
	{
	iResult =KErrGeneral;

	iWaitSchedular->AsyncStop();
	}

void CLacAsync::HandleTimeOut()
{
	iLog->Log(_L("TimeOut reached..."));
	iSysInfoService->Cancel(1);
	iResult = FAIL;
	iWaitSchedular->AsyncStop();
}



