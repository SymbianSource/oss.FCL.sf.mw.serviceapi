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



#include "sysinfoservice.h"
#include"watchtimer.h"

#include"entitykeys.h"

using namespace SysInfo;

class CTestAsync3 : public CActive ,public ISystemObserver, public MTimeOutCallBack
{
public:
	static CTestAsync3* NewL();
	~CTestAsync3();
	void Start();
	TInt Result();

	 void HandleResponseL(const TDesC& aEntity,const TDesC& aKey, 
									CSysData* aResponse, TInt32 aTransID, 
									TSysRequest::TRequestType aType, TInt aError=KErrNone);
	 void HandleTimeOut	();

private:
	void ConstructL();
	CTestAsync3();
	
	virtual void DoCancel();
	virtual void RunL();
	
	
	void TestFunc();

	
	
private:	
	CActiveSchedulerWait* 	iWaitSchedular;
	CSysInfoService*		iSysInfoService;
	TInt 					oldInputLang ;
	TInt 					newInputLang;
	TInt 					iResult;
	CWatchTimer*			iTimer;
	
};

CTestAsync3* CTestAsync3::NewL()
	{
	CTestAsync3* self = new(ELeave) CTestAsync3();
	self->ConstructL();
	return self;
	}

CTestAsync3::~CTestAsync3()
	{
	Cancel();
	
	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();
	
	if(iSysInfoService)
		delete iSysInfoService;
	
	if(iWaitSchedular)
		delete iWaitSchedular;
	
	delete iTimer;

	}

void CTestAsync3::ConstructL()
	{
	CActiveScheduler::Add(this);
	iSysInfoService = CSysInfoService::NewL();
	iWaitSchedular = new(ELeave) CActiveSchedulerWait();
	iTimer			= CWatchTimer::NewL(EPriorityNormal,this);

	}

CTestAsync3::CTestAsync3() :
CActive(EPriorityStandard),iResult(KErrNone)
	{
	}

void CTestAsync3::DoCancel()
	{
	
		
	}

void CTestAsync3::RunL()
	{
	TestFunc();
	}

void CTestAsync3::Start()
	{
	
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}

TInt CTestAsync3::Result()
	{
	return iResult;
	}

void CTestAsync3::TestFunc()
	{

	CSysData* data1 = NULL;
	const TTimeIntervalMicroSeconds32 OneMinute(600000);

	TRAPD(err1,iSysInfoService->GetNotificationL(KGeneral,KInputLanguage,777,this));
	iTimer->After(OneMinute);

	if(err1 == KErrNone)
		{
		TRAPD(err1,iSysInfoService->GetInfoL(KGeneral,KSupportedLanguages,data1));
		iResult = err1;
		
		if(err1 == KErrNone)
			{
		
			CSysData* data2 = NULL;

			TRAPD(err2,iSysInfoService->GetInfoL(KGeneral,KInputLanguage,data2));
			oldInputLang = ((CStatus*)data2)->Status();

			for(TInt i=0;i< ((CLanguageList*)data1)->Count() ;i++)
				{
				((CLanguageList*)data1)->At(i,newInputLang);
				if(newInputLang != oldInputLang)
					{
						break;
					}
				}
			
			CStatus* data3 = CStatus::NewL(newInputLang);

			TRAPD(err3,iSysInfoService->SetInfoL(KGeneral,KInputLanguage,data3));
			
			delete data3;
			delete data2;
			}
		}
	delete data1;
	return ;

	}

void CTestAsync3::HandleResponseL(const TDesC& /*aEntity*/,const TDesC& /*aKey*/, 
									CSysData* aResponse, TInt32 /*aTransID*/, 
									TSysRequest::TRequestType /*aType*/,TInt aError)
	{
		if(aError == KErrNone) 
		{
		const CStatus* data1 = (CStatus*)aResponse;

		TInt	changedInputLang = ((CStatus*)data1)->Status();

		if(newInputLang == changedInputLang)
			{
			iResult = KErrNone;
			}
		else
			{
			iResult =  KErrGeneral;

			}
		delete aResponse;
		}
		
	iWaitSchedular->AsyncStop();
	}
	
void CTestAsync3::HandleTimeOut()
{
	iWaitSchedular->AsyncStop();
	iResult = -1;
}	



int InputLangNotification()
	{
	__UHEAP_MARK;

	CTestAsync3* test = CTestAsync3::NewL();
	
	test->Start();
	TInt retval =	test->Result();
//	test->Cancel();
	delete test;

	__UHEAP_MARKEND;

	return retval;
	}

