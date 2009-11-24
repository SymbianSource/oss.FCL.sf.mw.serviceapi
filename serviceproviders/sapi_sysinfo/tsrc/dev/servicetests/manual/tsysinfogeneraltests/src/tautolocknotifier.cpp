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
#include "tautolocknotifier.h"
#include "entitykeys.h"
#include "watchtimer.h"
#include <e32std.h>

using namespace SysInfo;

CAutoLockNotifier* CAutoLockNotifier::NewL(CStifLogger* aLog,TInt aDrvNo)
	{
	CAutoLockNotifier* self = new(ELeave) CAutoLockNotifier(aLog,aDrvNo);
	self->ConstructL();
	return self;
	}

CAutoLockNotifier::~CAutoLockNotifier()
	{
	Cancel();
	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();
	
	delete iTimer;
	delete iSysInfoService;
	delete iWaitSchedular;
	}

void CAutoLockNotifier::ConstructL()
	{
	iSysInfoService = CSysInfoService::NewL();
	iWaitSchedular  = new(ELeave) CActiveSchedulerWait();
	iTimer			= CWatchTimer::NewL(EPriorityNormal,this);
	CActiveScheduler::Add(this);
	}

CAutoLockNotifier::CAutoLockNotifier(CStifLogger* aLog,TInt aAutoLockTime) :
				CActive(EPriorityStandard),iLog(aLog),iAutoLockTime(aAutoLockTime)
	{
	}

void CAutoLockNotifier::DoCancel()
	{
	//TRAPD(err1,iSysInfoService->GetInfoL(req1));
	}

void CAutoLockNotifier::RunL()
	{
	TestFuncL();
	}

void CAutoLockNotifier::Start()
	{
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}

TInt CAutoLockNotifier::Result()
	{
	return iResult;
	}

void CAutoLockNotifier::TestFuncL()
	{
	CSysData* input = CStatus::NewL(iAutoLockTime);
	CleanupStack::PushL(input);
	TRAPD(err,iSysInfoService->SetInfoL(KDisplay,KAutoLockTime,input));
	CleanupStack::PopAndDestroy(input);
	if (err)
		{
		iLog->Log( _L("Error setting auto lock time: %d"),err );
		}
	
	iLog->Log( _L("Auto Lock Time Set to %d Mins"),iAutoLockTime );
	iSysInfoService->GetNotificationL(KDisplay,KAutoLockStatus,1,this);
	
	const TInt OneMin(60000000);
	iTimer->After(OneMin*iAutoLockTime*2);
	return ;
	}

void CAutoLockNotifier::HandleResponseL(const TDesC& aEntity,const TDesC& aKey,
	 					CSysData* aOutput, TInt32 aTransID, TSysRequest::TRequestType /*aType*/,TInt aError)
	{
	delete iTimer;
	iTimer = NULL;
	if( !(aEntity.Compare(KDisplay) || aKey.Compare(KAutoLockStatus)) )
		{
		if(!aError)
			{
			if(!(aTransID == 1))
				{
				iLog->Log(_L("Incorrect TransactionID: %d"),aTransID);				
				iResult = FAIL;
				}

			TInt AutoLockStatus = ((CStatus*)aOutput)->Status();
			
			if(AutoLockStatus)
				iLog->Log(_L("Auto Lock Enabled"));
			else
				iLog->Log(_L("Auto Lock Disabled"));
			
			delete aOutput;
			iResult = PASS;
			}
		else
			{
			iLog->Log(_L("Error Set in Response Error: %d "),aError);
			iResult = FAIL;
			}
			
		}
//reset autolock time to 0	
	CSysData* input = CStatus::NewL(0);
	CleanupStack::PushL(input);
	TRAPD(err,iSysInfoService->SetInfoL(KDisplay,KAutoLockTime,input));
	CleanupStack::PopAndDestroy(input);
	if (err)
		{
		iLog->Log( _L("Error setting auto lock time: %d"),err );
		}
		
	iWaitSchedular->AsyncStop();

	}

void CAutoLockNotifier::HandleTimeOut()
{
	iLog->Log(_L("TimeOut reached. Auto Lock Not Enabled.."));
	iSysInfoService->Cancel(1);
	iResult = FAIL;
//reset autolock time to 0	
	CSysData* input = CStatus::NewL(0);
	CleanupStack::PushL(input);
	TRAPD(err,iSysInfoService->SetInfoL(KDisplay,KAutoLockTime,input));
	CleanupStack::PopAndDestroy(input);
	if (err)
		{
		iLog->Log( _L("Error setting auto lock time: %d"),err );
		}
	iWaitSchedular->AsyncStop();
}

