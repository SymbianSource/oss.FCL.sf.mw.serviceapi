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



#include "TSysNetwork.h"
#include "sysinfoservice.h"
#include "entitykeys.h"
#include "tcellidasync.h"

using namespace LIW ;
using namespace SysInfo;

CCellidAsync* CCellidAsync::NewL(CStifLogger* aLog)
	{
	CCellidAsync* self = new(ELeave) CCellidAsync(aLog);
	self->ConstructL();
	return self;
	}

CCellidAsync::~CCellidAsync()
	{
	Cancel();
	
	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();
	
	delete iSysInfoService;
	delete iWaitSchedular;
	delete iTimer;
	}

void CCellidAsync::ConstructL()
	{
	iSysInfoService = CSysInfoService::NewL();
	iWaitSchedular  = new(ELeave) CActiveSchedulerWait();
	iTimer			= CWatchTimer::NewL(EPriorityNormal,this);
	CActiveScheduler::Add(this);
	}

CCellidAsync::CCellidAsync(CStifLogger* aLog)
							 :CActive(EPriorityStandard),
								iLog(aLog)
	{
	}

void CCellidAsync::DoCancel()
	{
	}

void CCellidAsync::RunL()
	{
	TestFuncL();
	}

void CCellidAsync::Start()
	{
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}

TInt CCellidAsync::Result()
	{
	return iResult;
	}

void CCellidAsync::TestFuncL()
	{
	const TTimeIntervalMicroSeconds32 OneMinute(6000000000);
	iTransId = 333;
	iSysInfoService->GetInfoL(KNetwork,KCellID,iTransId,this);
	iTimer->After(OneMinute);
	}

void CCellidAsync::HandleResponseL(const TDesC& aEntity,const TDesC& aKey,
	 					CSysData* aOutput, TInt32 aTransID, TInt aError)
	{
	aEntity;
	aKey;
	delete iTimer;
	iTimer = NULL;
	
	iLog->Log(_L("Cell id read.."));
	
	if(!aError)
		{
		TInt32 tid = aTransID;
		TInt cellId = ((CStatus*)aOutput)->Status();
		
		if(tid ==iTransId)
			{
			iResult = PASS;
			iLog->Log(_L("Cell id"));
			TBuf<50> buf;
			buf.AppendNum(cellId);
			iLog->Log(buf);
			}
		else
			{
			iResult = FAIL;
			iLog->Log(_L("Cell id err.."));
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

void CCellidAsync::HandleTimeOut()
{
	iLog->Log(_L("TimeOut reached..."));
	iSysInfoService->Cancel(1);
	iResult = FAIL;
	iWaitSchedular->AsyncStop();
}



