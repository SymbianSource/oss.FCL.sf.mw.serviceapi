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
#include "tlacnotify.h"

using namespace LIW ;
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
	iSysInfoService->GetNotificationL(KNetwork,KLocationArea,iTransId,this);
	iTimer->After(OneMinute);
	}

void CLacNotify::HandleResponseL(const TDesC& aEntity,const TDesC& aKey,
	 					CSysData* aOutput, TInt32 aTransID, TInt aError)
	{
	aEntity;
	aKey;
	delete iTimer;
	iTimer = NULL;
	
	iLog->Log(_L("Location area code read..."));
	
	if(!aError)
		{
		if(aTransID ==iTransId )
		{
		TInt32 tid = aTransID;
		CNetworkInfo* networkInfo= ((CNetworkInfo*)aOutput);
		
		
		TPtrC 	networkName = networkInfo->NetworkName();
		iLog->Log(_L("Network name..."));
		iLog->Log(networkName);


		TInt	networkMode =networkInfo->NetworkMode();
		iLog->Log(_L("Network mode..."));
		TBuf<50> buf;
		buf.AppendNum(networkMode);
		iLog->Log(buf);
		
		TInt	networkStatus = networkInfo->NetworkStatus();
		iLog->Log(_L("Network Status..."));
		buf.Zero();
		buf.AppendNum(networkStatus);
		iLog->Log(buf);
		
		TPtrC 	countryCode = networkInfo->CountryCode();
		iLog->Log(_L("Country Code..."));
		buf.Zero();
		buf.Copy(countryCode);
		iLog->Log(buf);
		
		TPtrC	networkCode = networkInfo->NetworkCode();
		iLog->Log(_L("Network Code..."));
		buf.Zero();
		buf.Copy(networkCode);
		iLog->Log(buf);
		
		TUint	locationAreaCode =networkInfo->LocationAreaCode();
		iLog->Log(_L("Location Area Code..."));
		buf.Zero();
		buf.AppendNum(locationAreaCode);
		iLog->Log(buf);
		
		TUint	cellId = networkInfo->CellId();
		iLog->Log(_L("CellId..."));
		buf.Zero();
		buf.AppendNum(cellId);
		iLog->Log(buf);
		
		TBool	validLocationAreaCode = networkInfo->ValidLocationAreaCode();
		iLog->Log(_L("ValidLocationAreaCode..."));
		buf.Zero();
		buf.AppendNum(validLocationAreaCode);
		iLog->Log(buf);
		
		
		iResult = PASS;
		}
		

		else
		{
		iResult = PASS;

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



