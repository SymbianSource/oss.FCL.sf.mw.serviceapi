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
#include "tcurrentnetworkasync.h"

using namespace LIW ;
using namespace SysInfo;

CCurrentNetAsync* CCurrentNetAsync::NewL(CStifLogger* aLog)
	{
	CCurrentNetAsync* self = new(ELeave) CCurrentNetAsync(aLog);
	self->ConstructL();
	return self;
	}

CCurrentNetAsync::~CCurrentNetAsync()
	{
	Cancel();
	
	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();
	
	delete iSysInfoService;
	delete iWaitSchedular;
	delete iTimer;
	}

void CCurrentNetAsync::ConstructL()
	{
	iSysInfoService = CSysInfoService::NewL();
	iWaitSchedular  = new(ELeave) CActiveSchedulerWait();
	iTimer			= CWatchTimer::NewL(EPriorityNormal,this);
	CActiveScheduler::Add(this);
	}

CCurrentNetAsync::CCurrentNetAsync(CStifLogger* aLog)
							 :CActive(EPriorityStandard),
								iLog(aLog)
	{
	}

void CCurrentNetAsync::DoCancel()
	{
	}

void CCurrentNetAsync::RunL()
	{
	TestFuncL();
	}

void CCurrentNetAsync::Start()
	{
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}

TInt CCurrentNetAsync::Result()
	{
	return iResult;
	}

void CCurrentNetAsync::TestFuncL()
	{
	const TTimeIntervalMicroSeconds32 OneMinute(6000000000);
	iTransId = 5555;
	iSysInfoService->GetInfoL(KNetwork,KCurrentNetwork,iTransId,this);
	iTimer->After(OneMinute);
	}

void CCurrentNetAsync::HandleResponseL(const TDesC& aEntity,const TDesC& aKey,
	 					CSysData* aOutput, TInt32 aTransID, TInt aError)
	{
	aEntity;
	aKey;
	delete iTimer;
	iTimer = NULL;
	
	iLog->Log(_L("CurrentNetwork read..."));
	
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

void CCurrentNetAsync::HandleTimeOut()
{
	iLog->Log(_L("TimeOut reached..."));
	iSysInfoService->Cancel(1);
	iResult = FAIL;
	iWaitSchedular->AsyncStop();
}



