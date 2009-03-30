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



#include "tsysinfogeneraltests.h"
#include "sysinfoservice.h"
#include "tmemnotifier.h"
#include "entitykeys.h"
#include "watchtimer.h"
#include <e32std.h>


//const TTimeIntervalMicroSeconds32 OneMinute(6000000);

using namespace SysInfo;

CTestMemNotification* CTestMemNotification::NewL(CStifLogger* aLog)
	{
	CTestMemNotification* self = new(ELeave) CTestMemNotification(aLog);
	self->ConstructL();
	return self;
	}

CTestMemNotification::~CTestMemNotification()
	{
	Cancel();
	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();
	
	delete	iTimer;
	delete iSysInfoService;
	delete iWaitSchedular;
	}

void CTestMemNotification::ConstructL()
	{
	iSysInfoService = CSysInfoService::NewL();
	iWaitSchedular  = new(ELeave) CActiveSchedulerWait();
	iTimer			= CWatchTimer::NewL(EPriorityNormal,this);
	CActiveScheduler::Add(this);
	}

CTestMemNotification::CTestMemNotification(CStifLogger* aLog) :
				CActive(EPriorityStandard),iLog(aLog)
	{
	}

void CTestMemNotification::DoCancel()
	{
	//TRAPD(err1,iSysInfoService->GetInfoL(req1));
	}

void CTestMemNotification::RunL()
	{
	TestFuncL();
	}

void CTestMemNotification::Start()
	{
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}

TInt CTestMemNotification::Result()
	{
	return iResult;
	}

void CTestMemNotification::TestFuncL()
	{
	const TTimeIntervalMicroSeconds32 OneMinute(60000000);
	iTimer->After(OneMinute);
	iSysInfoService->GetNotificationL(KMemory,KMemoryCard,1,this);
	return ;
	}

void CTestMemNotification::HandleResponseL(const TDesC& aEntity,const TDesC& aKey,
	 					CSysData* aOutput, TInt32 aTransID, TSysRequest::TRequestType aType, TInt aError)
	{
	delete iTimer;
	iTimer = NULL;

	if( !(aEntity.Compare(KMemory) || aKey.Compare(KMemoryCard)) )
		{
		if(!aError)
			{
			if(!(aTransID == 1))
				{
				iLog->Log(_L("Incorrect TransactionID: %d"),aTransID);				
				iResult = FAIL;
				}

			iLog->Log(_L("Memorycard Notification.."));
			TInt status = ((CStatus*)aOutput)->Status();
			if(status)
				iLog->Log(_L("Memorycard Inserted.."));
			else
				iLog->Log(_L("Memorycard Removed.."));
			iResult |= PASS;		
			delete aOutput;
			}
		else
			{
			iLog->Log(_L("Error Set in callback.."));
			iResult |= FAIL;	
			}
		}

	iWaitSchedular->AsyncStop();
	}

void CTestMemNotification::HandleTimeOut()
{
	iLog->Log(_L("TimeOut reached. Memorycard not inserted.."));
	iSysInfoService->Cancel(1);
	iResult = FAIL;
	iWaitSchedular->AsyncStop();
}

