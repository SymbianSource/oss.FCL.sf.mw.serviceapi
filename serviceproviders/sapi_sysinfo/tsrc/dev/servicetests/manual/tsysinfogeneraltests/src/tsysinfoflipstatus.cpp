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
* Description:   tsysinfoflipstatus
*
*/



#include "sysinfoservice.h"
#include"entitykeys.h"

using namespace SysInfo;
class CTestAsync5 : public CActive ,public ISystemObserver
{
public:
	static CTestAsync5* NewL();
	~CTestAsync5();
	void Start();
	TInt Result();

	 void HandleResponseL(const TDesC& aEntity,const TDesC& aKey, 
									CSysData* aResponse, TInt32 aTransID, 
									TSysRequest::TRequestType aType, TInt aError=KErrNone);

private:
	void ConstructL();
	CTestAsync5();
	
	virtual void DoCancel();
	virtual void RunL();
	
	
	void TestFunc();

	
	
private:	
	CActiveSchedulerWait* 	iWaitSchedular;
	CSysInfoService*		iSysInfoService;
	TInt flipstatus ;
	TInt 					iResult;	
};

CTestAsync5* CTestAsync5::NewL()
	{
	CTestAsync5* self = new(ELeave) CTestAsync5();
	self->ConstructL();
	return self;
	}

CTestAsync5::~CTestAsync5()
	{
	Cancel();
	
	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();
	
	if(iSysInfoService)
		delete iSysInfoService;
	
	if(iWaitSchedular)
		delete iWaitSchedular;
	}

void CTestAsync5::ConstructL()
	{
	CActiveScheduler::Add(this);
	iSysInfoService = CSysInfoService::NewL();
	iWaitSchedular = new(ELeave) CActiveSchedulerWait();
	}

CTestAsync5::CTestAsync5() :
CActive(EPriorityStandard),iResult(-1)
	{
	}

void CTestAsync5::DoCancel()
	{
	
		
	}

void CTestAsync5::RunL()
	{
	TestFunc();
	}

void CTestAsync5::Start()
	{
	
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}

TInt CTestAsync5::Result()
	{
	return iResult;
	}

void CTestAsync5::TestFunc()
	{

	CStatus* data = CStatus::NewL(flipstatus);
	
	TRAPD(err1,iSysInfoService->GetNotificationL(KGeneral,KFlipStatus,555,this));
	iResult = err1;	

	if(err1 == KErrNone)
	{
	
	CSysData* data1 = NULL;
	
	TRAPD(err2,iSysInfoService->GetInfoL(KGeneral,KFlipStatus,data1));
   iResult = err2;
   if(err2 != KErrNone)
      return;
		
	flipstatus = ((CStatus*)data1)->Status();
	
	CStatus* data2 = CStatus::NewL(!flipstatus);

	TRAPD(err3,iSysInfoService->SetInfoL(KGeneral,KFlipStatus,data2));
	iResult = err3;
	if( err3 != KErrNone )
      return;
	delete data1;
	delete data2;

	}
	
	
	return ;
	}

void CTestAsync5::HandleResponseL(const TDesC& /*aEntity*/,const TDesC& /*aKey*/, 
									CSysData* aResponse, TInt32 /*aTransID*/, 
									TSysRequest::TRequestType /*aType*/,TInt aError)
	{
		if(aError == KErrNone) 
			{
			const CStatus* data1 = (CStatus*)aResponse;
			
			if((data1->Status() ) == (!flipstatus) )
				{
				iResult = KErrNone;
				delete aResponse;

				}
			else
				{
				iResult = -1;
				}
			}
		
iWaitSchedular->AsyncStop();
	}


int FlipNotification()
	{
	__UHEAP_MARK;

	CTestAsync5* test = CTestAsync5::NewL();
	
	test->Start();
	TInt retval =	test->Result();
//	test->Cancel();
	delete test;
	__UHEAP_MARKEND;

	return retval;
	}

