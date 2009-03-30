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
#include "Tcriticalmemnoti.h"
#include "entitykeys.h"
#include "watchtimer.h"
#include <e32std.h>

using namespace SysInfo;

CTCriticalMemNotification* CTCriticalMemNotification::NewL(CStifLogger* aLog,TInt aDrvNo)
	{
	CTCriticalMemNotification* self = new(ELeave) CTCriticalMemNotification(aLog,aDrvNo);
	self->ConstructL();
	return self;
	}

CTCriticalMemNotification::~CTCriticalMemNotification()
	{
	Cancel();
	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();
	
	delete	iTimer;
	delete iSysInfoService;
	delete iWaitSchedular;
	}

void CTCriticalMemNotification::ConstructL()
	{
	iSysInfoService = CSysInfoService::NewL();
	iWaitSchedular  = new(ELeave) CActiveSchedulerWait();
	iTimer			= CWatchTimer::NewL(EPriorityNormal,this);
	CActiveScheduler::Add(this);
	}

CTCriticalMemNotification::CTCriticalMemNotification(CStifLogger* aLog,TInt aDrvNo) :
				CActive(EPriorityStandard),iLog(aLog),iDrvNo(aDrvNo)
	{
	}

void CTCriticalMemNotification::DoCancel()
	{
	//TRAPD(err1,iSysInfoService->GetInfoL(req1));
	}

void CTCriticalMemNotification::RunL()
	{
	TestFuncL();
	}

void CTCriticalMemNotification::Start()
	{
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}

TInt CTCriticalMemNotification::Result()
	{
	return iResult;
	}

void CTCriticalMemNotification::TestFuncL()
	{
	TInt FreeSpace(0);
	TInt Err(PASS);
	CSysData* input = CDriveInfo::NewL(iDrvNo);
	CleanupStack::PushL(input);
	CSysData* output;
	TRAPD(err,iSysInfoService->GetInfoL(KMemory,KDriveInfo,output,input));
	CleanupStack::PopAndDestroy(input);
	if (!err)
		{
		if(!output)
			{
			Err |= FAIL;
			iLog->Log( _L("Output data Set to NULL") );
			}
		else
			{
			CleanupStack::PushL(output);
			//Check data type
			if( CSysData::EDriveInfo != output->DataType() )
				{
				iLog->Log( _L("Invalid output data") );
				Err |= FAIL;
				}
			else
				{
				CDriveInfo* driveinfo = (CDriveInfo*)output;
				iLog->Log( _L("Drive Number: %d"),driveinfo->DriveNumber() );
				FreeSpace = driveinfo->FreeSpace();
				iLog->Log( _L("Drive Free Space: %d"),FreeSpace );
				}
			CleanupStack::PopAndDestroy(output);
			}
	
		}
	
	User::LeaveIfError(Err);
	
	iLog->Log( _L("Critical Free Space Set to: %d"),FreeSpace/2 );
	input = CDriveInfo::NewL(iDrvNo,FreeSpace/2);
	CleanupStack::PushL(input);
	iSysInfoService->GetNotificationL(KMemory,KCriticalMemory,1,this,input);
	CleanupStack::PopAndDestroy(input);
	
	const TTimeIntervalMicroSeconds32 OneMinute(600000000);
	iTimer->After(OneMinute);
	return ;
	}

void CTCriticalMemNotification::HandleResponseL(const TDesC& aEntity,const TDesC& aKey,
	 					CSysData* aOutput, TInt32 aTransID,TSysRequest::TRequestType /*aType*/, TInt aError)
	{
	delete iTimer;
	iTimer = NULL;
	if( !(aEntity.Compare(KMemory) || aKey.Compare(KCriticalMemory)) )
		{
		if(!aError)
			{
			if(!(aTransID == 1))
				{
				iLog->Log(_L("Incorrect TransactionID: %d"),aTransID);				
				iResult = FAIL;
				}

			TPtrC Drv;
			((CStringData*)aOutput)->StringData(Drv);
			iLog->Log(_L("Critical Memory Notification on DriveNo: %s"),Drv.Ptr());
			delete aOutput;
			iResult = PASS;
			}
		else
			{
			iLog->Log(_L("Error Set in Response Error: %d "),aError);
			iResult = FAIL;
			}
			
		}
	iWaitSchedular->AsyncStop();
	}

void CTCriticalMemNotification::HandleTimeOut()
{
	iLog->Log(_L("TimeOut reached. Memorycard not inserted.."));
	iSysInfoService->Cancel(1);
	iResult = FAIL;
	iWaitSchedular->AsyncStop();
}

