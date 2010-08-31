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
* Description:   tsysinfohomenetworkasync
*
*/



#include "tsysinfonetworktests.h"
#include "sysinfoservice.h"
#include "entitykeys.h"
#include "tsysinfohomenetworkasync.h"

using namespace SysInfo;

CHomeNwAsync* CHomeNwAsync::NewL(CStifLogger* aLog)
	{
	CHomeNwAsync* self = new(ELeave) CHomeNwAsync(aLog);
	self->ConstructL();
	return self;
	}

CHomeNwAsync::~CHomeNwAsync()
	{
	Cancel();
	
	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();
	
	delete iSysInfoService;
	delete iWaitSchedular;
	delete iTimer;
	}

void CHomeNwAsync::ConstructL()
	{
	iSysInfoService = CSysInfoService::NewL();
	iWaitSchedular  = new(ELeave) CActiveSchedulerWait();
	iTimer			= CWatchTimer::NewL(EPriorityNormal,this);
	CActiveScheduler::Add(this);
	}

CHomeNwAsync::CHomeNwAsync(CStifLogger* aLog)
							 :CActive(EPriorityStandard),
								iLog(aLog)
	{
	}

void CHomeNwAsync::DoCancel()
	{
	}

void CHomeNwAsync::RunL()
	{
	TestFuncL();
	}

void CHomeNwAsync::Start()
	{
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}

TInt CHomeNwAsync::Result()
	{
	return iResult;
	}

void CHomeNwAsync::TestFuncL()
	{
	const TTimeIntervalMicroSeconds32 OneMinute(6000000000);
	iTransId = 1;
	TRAPD(err,iSysInfoService->GetInfoL(KNetwork,KHomeNetwork,iTransId,this));
	iResult  = err;
	if(err)
	    iWaitSchedular->AsyncStop();
	iTimer->After(OneMinute);
	}

void CHomeNwAsync::HandleResponseL(const TDesC& /*aEntity*/,const TDesC& /*aKey*/,
	 					CSysData* aOutput, TInt32 aTransID, TSysRequest::TRequestType /*aType*/,TInt aError)
	{
	iLog->Log(_L("HomeNetwork read..."));
	
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

void CHomeNwAsync::HandleTimeOut()
{
	iLog->Log(_L("TimeOut reached..."));
	iSysInfoService->Cancel(1);
	iResult = FAIL;
	iWaitSchedular->AsyncStop();
}



