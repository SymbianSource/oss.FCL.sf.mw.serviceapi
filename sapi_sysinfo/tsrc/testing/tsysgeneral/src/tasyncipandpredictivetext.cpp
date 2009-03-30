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
* Description:   Tests input and predeictive text status
*
*/


#include "tsysgeneral.h"
#include "sysinfoservice.h"
#include "sysrequest.h"
#include "tasyncipandpredictivetext.h"
#include "watchtimer.h"
#include "entitykeys.h"

using namespace SysInfo;


CTestIpAndPredTextNot* CTestIpAndPredTextNot::NewL(CStifLogger* aLog)
	{
	CTestIpAndPredTextNot* self = new(ELeave) CTestIpAndPredTextNot(aLog);
	self->ConstructL();
	return self;
	}

CTestIpAndPredTextNot::~CTestIpAndPredTextNot()
	{
	Cancel();
	
	if(iWaitScheduler->IsStarted())
		iWaitScheduler->AsyncStop();
	
	if(iSysInfoService)
		delete iSysInfoService;
	
	if(iWaitScheduler)
		delete iWaitScheduler;
	}

void CTestIpAndPredTextNot::ConstructL()
	{
	CActiveScheduler::Add(this);
	iSysInfoService = CSysInfoService::NewL();
	iWaitScheduler = new(ELeave) CActiveSchedulerWait();
	}

CTestIpAndPredTextNot::CTestIpAndPredTextNot(CStifLogger* aLog) :
CActive(EPriorityStandard),iResult(-1),iLog(aLog),iCount(0)
	{
	}

void CTestIpAndPredTextNot::DoCancel()
	{

	}

void CTestIpAndPredTextNot::RunL()
	{
	TestFunc();
	}

void CTestIpAndPredTextNot::Start()
	{
	
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitScheduler->Start();	
	}

TInt CTestIpAndPredTextNot::Result()
	{
	return iResult;
	}

void CTestIpAndPredTextNot::TestSetup(TInt /*aLangIndex*/, TInt aPredTextStatus)
	{
	CStatus *predData = CStatus::NewL(aPredTextStatus) ;
    iSysInfoService->SetInfoL(KGeneral,KPridictiveText,predData) ;
    delete predData ;
	}

void CTestIpAndPredTextNot::TestFunc()
	{
    TestSetup(0,0) ;	
	TRAPD(err2,iSysInfoService->GetNotificationL(KGeneral,KPridictiveText,1001,this));
	
	if(KErrNone == err2)
		{
		TestSetup(58,1) ;	
       	}
	else
		{
		iWaitScheduler->AsyncStop();
		TestSetup(0,0) ;
		}
	return ;
	}

void CTestIpAndPredTextNot::HandleResponseL(const TDesC& /*aEntity*/,const TDesC& /*aKey*/, 
									CSysData* aResponse, TInt32 aTransID, 
									TSysRequest::TRequestType aType,
									TInt aError)
	{

	if(aError == KErrNone) 
		{
		if(aTransID == 1000 && aType == 2)
			{
			TInt expIpLanguage = 58 ;
			
			const CStatus* data = (CStatus*)aResponse ;
			TInt IpLang = data->Status() ;
			
			if(IpLang == expIpLanguage)
				{
				iResult = KErrNone ;
				}
			iLog->Log(_L8("IpLanguage : %d"),IpLang) ;
			}
		else if(aTransID == 1001 && aType == 2)
			{
			TInt expPredTextStatus = 1 ;
			
			const CStatus* data = (CStatus*)aResponse ;
			TInt predTextStatus = data->Status() ;
			
			if(predTextStatus == expPredTextStatus)
				{
				iResult = KErrNone ;
				}
			iLog->Log(_L8("PredicitiveText statys : %d"),predTextStatus) ;
			
			}
		iCount++ ;
		delete aResponse ;
		}

	if(iCount == 1)
		{
		iWaitScheduler->AsyncStop();
		TestSetup(0,0) ;	
		}
	
	}


int TestIpAndPredTextNot(CStifLogger* aLog)
	{

	__UHEAP_MARK ;
	
	CTestIpAndPredTextNot* test = CTestIpAndPredTextNot::NewL(aLog);
	aLog->Log(_L8("InputLang and PredText Notification Test")) ;
	test->Start();
	TInt retval = test->Result();
	delete test;
	
	__UHEAP_MARKEND ;
	return retval;
	}

