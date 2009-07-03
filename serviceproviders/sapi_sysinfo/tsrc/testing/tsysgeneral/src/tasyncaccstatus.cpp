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


#include "tsysgeneral.h"
#include "sysinfoservice.h"
#include "tasyncaccstatus.h"
#include "entitykeys.h"
#include "watchtimer.h"
#include <e32std.h>

using namespace SysInfo;

CAsyncStatus* CAsyncStatus::NewL(CStifLogger* aLog)
	{
	CAsyncStatus* self = new(ELeave) CAsyncStatus(aLog);
	self->ConstructL();
	return self;
	}

CAsyncStatus::~CAsyncStatus()
	{
	Cancel();
	if(iWaitScheduler->IsStarted())
		iWaitScheduler->AsyncStop();
	
	delete	iTimer;
	delete iSysInfoService;
	delete iWaitScheduler;
	}

void CAsyncStatus::ConstructL()
	{
	iSysInfoService = CSysInfoService::NewL();
	iWaitScheduler  = new(ELeave) CActiveSchedulerWait();
	iTimer			= CWatchTimer::NewL(EPriorityNormal,this);
	CActiveScheduler::Add(this);
	}

CAsyncStatus::CAsyncStatus(CStifLogger* aLog) :
				CActive(EPriorityStandard),iLog(aLog)
	{
	}

void CAsyncStatus::DoCancel()
	{
	//TRAPD(err1,iSysInfoService->GetInfoL(req1));
	}

void CAsyncStatus::RunL()
	{
	TestFuncL();
	}

void CAsyncStatus::Start()
	{
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitScheduler->Start();	
	}

TInt CAsyncStatus::Result()
	{
	return iResult;
	}

void CAsyncStatus::TestFuncL()
	{
	
	TInt retValue = KErrNone ;
	CSysData* input = CDriveInfo::NewL(retValue);
	TRAPD(err,iSysInfoService->GetInfoL(KGeneral,KAccessoryStatus,1,this,input));
	
	if (KErrNotSupported == err)
		{
		TRAP(err,iSysInfoService->GetInfoL(KGeneral,KInputLanguage,1,this,input));
		
		if(KErrNotSupported == err)
			{
			TRAP(err,iSysInfoService->GetInfoL(KGeneral,KFlipStatus,1,this,input));
			if(KErrNotSupported != err)
				{
				retValue = KErrGeneral ;	
				}
			}
		else
			{
			retValue = KErrGeneral ;
			}
		
		}
	else
		{
		retValue = KErrGeneral ;
		}
	iResult = retValue ;
	delete input ;
	iWaitScheduler->AsyncStop();
	}

void CAsyncStatus::HandleResponseL(const TDesC& /*aEntity*/,const TDesC& /*aKey*/,
	 					CSysData* /*aOutput*/, TInt32 /*aTransID*/,TSysRequest::TRequestType /*aType*/, TInt /*aError*/)
	{

	}

void CAsyncStatus::HandleTimeOut()
{
}

TInt TestAsyncStatus(CStifLogger* aLog )
{

	CAsyncStatus* test = CAsyncStatus::NewL(aLog);
	
	test->Start();
	TInt retval = test->Result();
	delete test;

	return retval;
}