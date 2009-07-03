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
* Description:   tsysinfoaccessorystatus
*
*/


#include "tsysmanualtest.h"
#include "sysinfoservice.h"
#include "tasyncaccandvibra.h"
#include "watchtimer.h"
#include "entitykeys.h"

using namespace SysInfo;


CTestAccAndVibraNot* CTestAccAndVibraNot::NewL(CStifLogger* aLog)
	{
	CTestAccAndVibraNot* self = new(ELeave) CTestAccAndVibraNot(aLog);
	self->ConstructL();
	return self;
	}

CTestAccAndVibraNot::~CTestAccAndVibraNot()
	{
	Cancel();
	
	if(iWaitScheduler->IsStarted())
		iWaitScheduler->AsyncStop();
	
	if(iSysInfoService)
		delete iSysInfoService;
	
	if(iWaitScheduler)
		delete iWaitScheduler;
	}

void CTestAccAndVibraNot::ConstructL()
	{
	CActiveScheduler::Add(this);
	iSysInfoService = CSysInfoService::NewL();
	iWaitScheduler = new(ELeave) CActiveSchedulerWait();
	}

CTestAccAndVibraNot::CTestAccAndVibraNot(CStifLogger* aLog) :
CActive(EPriorityStandard),iResult(-1),iLog(aLog),iCount(0)
	{
	}

void CTestAccAndVibraNot::DoCancel()
	{

	}

void CTestAccAndVibraNot::RunL()
	{
	TestFunc();
	}

void CTestAccAndVibraNot::Start()
	{
	
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitScheduler->Start();	
	}

TInt CTestAccAndVibraNot::Result()
	{
	return iResult;
	}

void CTestAccAndVibraNot::TestSetup(TInt aVibraStatus)
	{
	CStatus *vibStatus = CStatus::NewL(aVibraStatus) ;
	iSysInfoService->SetInfoL(KGeneral,KVibraActive,vibStatus) ;
    delete vibStatus ;
	}

void CTestAccAndVibraNot::TestFunc()
	{
    TestSetup(0) ;	
	TRAPD(err1,iSysInfoService->GetNotificationL(KGeneral,KAccessoryStatus,1000,this));
	TRAPD(err2,iSysInfoService->GetNotificationL(KGeneral,KVibraActive,1001,this));
	
	if((KErrNone == err1) && (KErrNone == err2))
		{
		TestSetup(1) ;	
       	}
	else
		{
		iWaitScheduler->AsyncStop();
		TestSetup(0) ;
		}
	return ;
	}

void CTestAccAndVibraNot::HandleResponseL(const TDesC& /*aEntity*/,const TDesC& /*aKey*/, 
									CSysData* aResponse, TInt32 aTransID,
									 TSysRequest::TRequestType /*aType*/, TInt aError)
	{

	if(aError == KErrNone) 
		{
		if(aTransID == 1000)
			{
			const CAccessoryInfo* accInfo= (CAccessoryInfo*)aResponse;
				
			TBuf<50> acctype ;
			TBuf<50> accConnState;
			acctype.AppendNum(	accInfo->AccessoryType() );
			accConnState.AppendNum(	accInfo->ConnectionState() );
			iLog->Log(_L("Accessory Type:"));
			iLog->Log(acctype);

			iLog->Log(_L("Accessory Connection State:"));
			iLog->Log(accConnState);
			 		
			iResult = KErrNone;
			}
		
		else if(aTransID == 1001)
			{
			TInt expVibStatus = 1 ;
			
			const CStatus* data = (CStatus*)aResponse ;
			TInt vibStatus = data->Status() ;
			
			if(vibStatus == expVibStatus)
				{
				iResult = KErrNone ;
				}
			iLog->Log(_L8("PredicitiveText status : %d"),vibStatus) ;
			
			}
		iCount++ ;
		delete aResponse ;
		}

	if(iCount == 2)
		{
		iWaitScheduler->AsyncStop();
		TestSetup(0) ;	
		}
	
	}


TInt TestAccAndVibraNot(CStifLogger* aLog)
	{

	__UHEAP_MARK ;
	
	CTestAccAndVibraNot* test = CTestAccAndVibraNot::NewL(aLog);
	aLog->Log(_L8("Accessory and Vibration Status Notifications")) ;
	test->Start();
	TInt retval = test->Result();
	delete test;
	
	__UHEAP_MARKEND ;
	return retval;
	}

