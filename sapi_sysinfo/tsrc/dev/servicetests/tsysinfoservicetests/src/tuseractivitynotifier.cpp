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



#include "tsysinfoservicetests.h"
#include "sysinfoservice.h"
#include "tuseractivitynotifier.h"
#include "entitykeys.h"
#include "watchtimer.h"
#include <e32std.h>

using namespace SysInfo;

CTestUserActivity* CTestUserActivity::NewL(CStifLogger* aLog,TInt aTimeOut,Test_Type aType)
	{
	CTestUserActivity* self = new(ELeave) CTestUserActivity(aLog,aTimeOut,aType);
	self->ConstructL();
	return self;
	}

CTestUserActivity::~CTestUserActivity()
	{
	Cancel();
	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();
	
	delete	iTimer;
	delete iSysInfoService;
	delete iWaitSchedular;
	}

void CTestUserActivity::ConstructL()
	{
	iSysInfoService = CSysInfoService::NewL();
	iWaitSchedular  = new(ELeave) CActiveSchedulerWait();
	iTimer			= CWatchTimer::NewL(EPriorityNormal,this);
	CActiveScheduler::Add(this);
	}

CTestUserActivity::CTestUserActivity(CStifLogger* aLog,TInt aTimeOut,
									Test_Type aType) :
								CActive(EPriorityStandard),
								iLog(aLog),
								iInactivityTimeOut(aTimeOut),
								iTestType(aType)
	{
	}

void CTestUserActivity::DoCancel()
	{
	}

void CTestUserActivity::RunL()
	{
	TestFuncL();
	}

void CTestUserActivity::Start()
	{
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}

TInt CTestUserActivity::Result()
	{
	return iResult;
	}

void CTestUserActivity::TestFuncL()
	{
	const TInt OneSec(1000000);
	iTimer->After(OneSec*iInactivityTimeOut*30);
	CStatus* inactivitytime = CStatus::NewL(iInactivityTimeOut);
	CleanupStack::PushL(inactivitytime);
	iSysInfoService->GetNotificationL(KDisplay,KUserInactivity,1,this,inactivitytime);
	CleanupStack::PopAndDestroy(inactivitytime);
	}


void CTestUserActivity::HandleResponseL(const TDesC& aEntity,const TDesC& aKey,
	 					CSysData* aOutput, TInt32 aTransID, TSysRequest::TRequestType /*aType*/,TInt aError)
	{
	delete iTimer;
	iTimer = NULL;
	
	TInt status(0);
	
	if( !(aEntity.Compare(KDisplay) || aKey.Compare(KUserInactivity)) )
		{
		if(!aError)
			{
			if(!(aTransID == 1))
				{
				iLog->Log(_L("Incorrect TransactionID: %d"),aTransID);				
				iResult = FAIL;
				}

			iLog->Log(_L("UserActivity/Inactivity Notification.."));
			status = ((CStatus*)aOutput)->Status();
			if(status)
				iLog->Log(_L("User Inactivity Detected.."));
			else
				iLog->Log(_L("User Activity Detected.."));
			iResult |= PASS;		
			delete aOutput;
			}
		else
			{
			iLog->Log(_L("Error Set in callback.."));
			iResult |= FAIL;	
			}
		}

	if (ETESTACTIVITY == iTestType)
		{
		if(status)
			{
			iLog->Log(_L("Waiting for user activity"));
			return;
			}
		else
			{
			iLog->Log(_L("User Activity Detected.."));
			}
		iResult |= PASS;
		}
		
	iResult |= PASS;

	iWaitSchedular->AsyncStop();
	}

void CTestUserActivity::HandleTimeOut()
{
	iLog->Log(_L("TimeOut reached. Inactivity not detected.."));
	iSysInfoService->Cancel(1);
	iResult = FAIL;
	iWaitSchedular->AsyncStop();
}

