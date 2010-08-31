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
* Description:   tsysinfolacnotify
*
*/



#include "tsysinfonetworktests.h"
#include "sysinfoservice.h"
#include "entitykeys.h"
#include "tsysinfolacnotify.h"

using namespace SysInfo;

CLacNotify* CLacNotify::NewL(CStifLogger* aLog)
	{
	CLacNotify* self = new(ELeave) CLacNotify(aLog);
	self->ConstructL();
	return self;
	}

CLacNotify::~CLacNotify()
	{
	Cancel();
	
	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();
	
	delete iSysInfoService;
	delete iWaitSchedular;
	delete iTimer;
	}

void CLacNotify::ConstructL()
	{
	iSysInfoService = CSysInfoService::NewL();
	iWaitSchedular  = new(ELeave) CActiveSchedulerWait();
	iTimer			= CWatchTimer::NewL(EPriorityNormal,this);
	CActiveScheduler::Add(this);
	}

CLacNotify::CLacNotify(CStifLogger* aLog)
							 :CActive(EPriorityStandard),
								iLog(aLog)
	{
	}

void CLacNotify::DoCancel()
	{
	}

void CLacNotify::RunL()
	{
	TestFuncL();
	}

void CLacNotify::Start()
	{
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}

TInt CLacNotify::Result()
	{
	return iResult;
	}

void CLacNotify::TestFuncL()
	{
	const TTimeIntervalMicroSeconds32 OneMinute(6000000000);
	iTransId = 8888;
	TRAPD(err,iSysInfoService->GetNotificationL(KNetwork,KLocationArea,iTransId,this));
	iResult  = err;
	iTimer->After(OneMinute);
	}

void CLacNotify::HandleResponseL(const TDesC& /*aEntity*/,const TDesC& /*aKey*/,
	 					CSysData* aOutput, TInt32 aTransID, TSysRequest::TRequestType /*aType*/,TInt aError)
	{
	
	iLog->Log(_L("Location area Code read.."));
	
	if(!aError)
		{
		TInt32 tid = aTransID;
		TInt cellId = ((CStatus*)aOutput)->Status();
		
		if(tid ==iTransId)
			{
			iResult = PASS;
			iLog->Log(_L("LAC"));
			TBuf<50> buf;
			buf.AppendNum(cellId);
			iLog->Log(buf);
			}
		else
			{
			iResult = FAIL;
			iLog->Log(_L("LAC err.."));
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

void CLacNotify::HandleTimeOut()
{
	iLog->Log(_L("TimeOut reached..."));
	iSysInfoService->Cancel(1);
	iResult = FAIL;
	iWaitSchedular->AsyncStop();
}



