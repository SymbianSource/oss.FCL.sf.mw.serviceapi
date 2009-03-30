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
* Description:   tsysinfosigstrengthasyn
*
*/



#include "tsysinfonetworktests.h"
#include "sysinfoservice.h"
#include "entitykeys.h"
#include "tsysinfosigstrengthnotify.h"

using namespace SysInfo;

CSignalStrNotify* CSignalStrNotify::NewL(CStifLogger* aLog,TInt aStrength)
	{
	CSignalStrNotify* self = new(ELeave) CSignalStrNotify(aLog,aStrength);
	self->ConstructL();
	return self;
	}

CSignalStrNotify::~CSignalStrNotify()
	{
	Cancel();
	
	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();
	
	delete iSysInfoService;
	delete iWaitSchedular;
	delete iTimer;
	}

void CSignalStrNotify::ConstructL()
	{
	iSysInfoService = CSysInfoService::NewL();
	iWaitSchedular  = new(ELeave) CActiveSchedulerWait();
	iTimer			= CWatchTimer::NewL(EPriorityNormal,this);
	CActiveScheduler::Add(this);
	}

CSignalStrNotify::CSignalStrNotify(CStifLogger* aLog,TInt aStrength)
							 :CActive(EPriorityStandard),
								iLog(aLog),iSignalStrength(aStrength)
	{
	}

void CSignalStrNotify::DoCancel()
	{
	}

void CSignalStrNotify::RunL()
	{
	TestFuncL();
	}

void CSignalStrNotify::Start()
	{
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}

TInt CSignalStrNotify::Result()
	{
	return iResult;
	}

void CSignalStrNotify::TestFuncL()
	{
	const TTimeIntervalMicroSeconds32 OneMinute(6000000000);
	TRAPD(err,iSysInfoService->GetNotificationL(KNetwork,KSignalStrength,2222,this));
	iResult  = err;

	iTimer->After(OneMinute);
	}

void CSignalStrNotify::HandleResponseL(const TDesC& /*aEntity*/,const TDesC& /*aKey*/,
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

void CSignalStrNotify::HandleTimeOut()
{
	iLog->Log(_L("TimeOut reached..."));
	iSysInfoService->Cancel(1);
	iResult = FAIL;
	iWaitSchedular->AsyncStop();
}