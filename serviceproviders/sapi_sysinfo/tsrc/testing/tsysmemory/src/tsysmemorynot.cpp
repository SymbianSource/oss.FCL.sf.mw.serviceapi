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
* Description:   Tests memory notifications
*
*/



#include "tsysmemory.h"
#include "sysinfoservice.h"
#include "entitykeys.h"
#include "tsysmemorynot.h"

using namespace SysInfo;

CMemNot* CMemNot::NewL(CStifLogger* aLog, TInt aCmdId)
	{
	CMemNot* self = new(ELeave) CMemNot(aLog,aCmdId );
	self->ConstructL();
	return self;
	}

CMemNot::~CMemNot()
	{
	Cancel();
	
	if(iWaitScheduler->IsStarted())
		iWaitScheduler->AsyncStop();
	
	delete iSysInfoService;
	delete iWaitScheduler;
	delete iTimer;
	}

void CMemNot::ConstructL()
	{
	iSysInfoService = CSysInfoService::NewL();
	iWaitScheduler  = new(ELeave) CActiveSchedulerWait();
	iTimer			= CWatchTimer::NewL(EPriorityNormal,this);
	CActiveScheduler::Add(this);
	}

CMemNot::CMemNot(CStifLogger* aLog, TInt aCmdId)
							 :CActive(EPriorityStandard),
								iLog(aLog), iCmdId(aCmdId)
	{
	}

void CMemNot::DoCancel()
	{
	}

void CMemNot::RunL()
	{
	if(iCmdId == EUnsupported)
		{
		TRAP(iResult,TestFuncL());	
		}
	
	else if(iCmdId == EWrongKey)
		{
		TRAP(iResult,TestFunc1L());
		}
	iWaitScheduler->AsyncStop();
	}

void CMemNot::Start()
	{
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitScheduler->Start();	
	}

TInt CMemNot::Result()
	{
	return iResult ;
	}

void CMemNot::TestFuncL()
	{
	_LIT(KSample,"Simple") ;
	CStringData* inputData = CStringData::NewL(KSample) ; 
	CleanupStack::PushL(inputData);
	iSysInfoService->GetInfoL(KMemory,KCriticalMemory,1,this,inputData);
	CleanupStack::PopAndDestroy() ;
	}

void CMemNot::TestFunc1L()
	{
	_LIT(KSample,"Simple") ;
	CStringData* inputData = CStringData::NewL(KSample) ; 
	CleanupStack::PushL(inputData);
	iSysInfoService->GetNotificationL(KMemory,KSample,1,this,inputData);
	CleanupStack::PopAndDestroy() ;
	}
	
void CMemNot::HandleResponseL(const TDesC& /*aEntity*/,const TDesC& /*aKey*/,
	 					CSysData* aOutput, TInt32 /*aTransID*/, TSysRequest::TRequestType /*aType*/, TInt /*aError*/)
	{
	
	delete aOutput ;
	
	}

void CMemNot::HandleTimeOut()
{
	
}
