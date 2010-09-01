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
* Description:   tsigstrengthasyn
*
*/



#include "tsysinfonetworktests.h"
#include "sysinfoservice.h"
#include "entitykeys.h"
#include "tsysinfosigstrengthasyn.h"

using namespace SysInfo;

CSignalStrAsync* CSignalStrAsync::NewL(CStifLogger* aLog,TInt aStrength)
	{
	CSignalStrAsync* self = new(ELeave) CSignalStrAsync(aLog,aStrength);
	self->ConstructL();
	return self;
	}

CSignalStrAsync::~CSignalStrAsync()
	{
	Cancel();
	
	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();
	
	delete iSysInfoService;
	delete iWaitSchedular;
	delete iTimer;
	}

void CSignalStrAsync::ConstructL()
	{
	iSysInfoService = CSysInfoService::NewL();
	iWaitSchedular  = new(ELeave) CActiveSchedulerWait();
	iTimer			= CWatchTimer::NewL(EPriorityNormal,this);
	CActiveScheduler::Add(this);
	}

CSignalStrAsync::CSignalStrAsync(CStifLogger* aLog,TInt aStrength)
							 :CActive(EPriorityStandard),
								iLog(aLog),iSignalStrength(aStrength)
	{
	}

void CSignalStrAsync::DoCancel()
	{
	}

void CSignalStrAsync::RunL()
	{
	TestFuncL();
	}

void CSignalStrAsync::Start()
	{
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}

TInt CSignalStrAsync::Result()
	{
	return iResult;
	}

void CSignalStrAsync::TestFuncL()
	{
	TInt64 x = 6000000000;
  const TTimeIntervalMicroSeconds32 OneMinute = TTimeIntervalMicroSeconds32(x);
	TRAPD(err,iSysInfoService->GetInfoL(KNetwork,KSignalStrength,1111,this));
	iResult  = err;
	iTimer->After(OneMinute);
	}

void CSignalStrAsync::HandleResponseL(const TDesC& /*aEntity*/,const TDesC& /*aKey*/,
	 					CSysData* aOutput, TInt32 aTransID, TSysRequest::TRequestType /*aType*/,TInt aError)
	{

	iLog->Log(_L("Signal Strength read.."));
	
	if(!aError)
		{
		TInt32 tid = aTransID;
		TInt SignalStrength = ((CStatus*)aOutput)->Status();
		
			{
			iResult = PASS;
			iLog->Log(_L("Signal strength is with in specified range"));
			
			TInt32 tid = aTransID;
			TInt cellId = ((CStatus*)aOutput)->Status();
			
			TBuf<50> buf;
			buf.AppendNum(cellId);
			iLog->Log(buf);
		
			}

		}
	else
		{
		iLog->Log(_L("ERROR SET"));
		iResult = FAIL;
		}
		delete aOutput;
	iWaitSchedular->AsyncStop();
	}

void CSignalStrAsync::HandleTimeOut()
{
	iLog->Log(_L("TimeOut reached..."));
	iSysInfoService->Cancel(1);
	iResult = FAIL;
	iWaitSchedular->AsyncStop();
}