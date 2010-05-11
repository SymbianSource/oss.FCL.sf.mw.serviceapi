/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  
*
*/

#include <liwcommon.h>
#include<liwservicehandler.h>

#include "sysinfointerface.h"
#include"entitykeys.h"
#include "sysinfoaiwparams.hrh"
#include"watchtimer.h"
#include "serviceerrno.h"
#include"tsysinfoprovidertests.h"

using namespace LIW ;
using namespace SysInfo;
using namespace sysinfoaiwparams;	


class CTestBTCancel : public CActive ,public MLiwNotifyCallback, public MTimeOutCallBack
{
public:
	static CTestBTCancel* NewL(CStifLogger* aLog);
	~CTestBTCancel();
	void Start();
	TInt Result();

	TInt HandleNotifyL(TInt aCmdId,
			            TInt aEventId,
			            CLiwGenericParamList& aEventParamList,
			            const CLiwGenericParamList& aInParamList);
    IMPORT_C static TInt32 GetTransactionID();
    
    void HandleTimeOut	();
    	
private:
	void ConstructL();

	CTestBTCancel(CStifLogger* aLog);
	
	virtual void DoCancel();
	
	virtual void RunL();
	
	void TestFunc();
	
private:	
	CActiveSchedulerWait* 	iWaitSchedular;
	CLiwServiceHandler* iServiceHandler;
	MLiwInterface* interface ;
	TInt32 btstatus ;
	TInt 					iResult;
	CWatchTimer*			iTimer;
	CStifLogger*			iLog;
	
};

CTestBTCancel* CTestBTCancel::NewL(CStifLogger* aLog)
	{
	CTestBTCancel* self = new(ELeave) CTestBTCancel(aLog);
	self->ConstructL();
	return self;
	}

CTestBTCancel::~CTestBTCancel()
	{
	Cancel();
	
	interface->Close();
	
	delete iServiceHandler;
	
	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();
	
	if(iWaitSchedular)
		delete iWaitSchedular;
	
	delete iTimer;

	}

void CTestBTCancel::ConstructL()
	{
	CActiveScheduler::Add(this);
	iWaitSchedular = new(ELeave) CActiveSchedulerWait();
	iTimer			= CWatchTimer::NewL(EPriorityNormal,this);

	}

CTestBTCancel::CTestBTCancel(CStifLogger* aLog) :
CActive(EPriorityStandard),iResult(-1),iLog(aLog)
	{
	}

void CTestBTCancel::DoCancel()
	{
	
	//TRAPD(err1,iSysInfoService->GetInfoL(req1));
		
	}

void CTestBTCancel::RunL()
	{
	TestFunc();
	}

void CTestBTCancel::Start()
	{
	
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}

TInt CTestBTCancel::Result()
	{
	return iResult;
	}

void CTestBTCancel::TestFunc()
	{

	const TTimeIntervalMicroSeconds32 OneMinute(60000);

	iServiceHandler = CLiwServiceHandler::NewL();
	CLiwGenericParamList* inparam = &(iServiceHandler->InParamListL());
	CLiwGenericParamList* outparam = &(iServiceHandler->OutParamListL());

	TInt 	err = KErrNone; 
	
	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);
	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray a;
	a.AppendL(crit);    

	iServiceHandler->AttachL(a);

	iServiceHandler->ExecuteServiceCmdL(*crit, *inparam, *outparam); 

	delete crit;
	a.Reset();
	
	TInt pos = 0;

	outparam->FindFirst( pos, KIDataSource );
	if(pos != KErrNotFound)
		{
		//getting the interface handle
		interface = (*outparam)[pos].Value().AsInterface();	
		}

	outparam->Reset();
	inparam->Reset();
	
	if(interface)
		{
		TLiwGenericParam entity;
		TLiwVariant  entityname;
		TLiwGenericParam key;
		TLiwVariant  keyname;
		
		entityname.Set(KConnectivity);
		entity.SetNameAndValueL(KEntity,entityname);

		keyname.Set(KBlueTooth);
		key.SetNameAndValueL(KKey,keyname);

		inparam->AppendL(entity);

		inparam->AppendL(key);
		
		entity.Reset();
		entityname.Reset();
		key.Reset();
		keyname.Reset();
		iLog->Log(_L("before getnotification vibra Active:"));

		//get  notification vibra Active
		TRAPD(err1,	interface->ExecuteCmdL(KGetNotification,*inparam,*outparam,KLiwOptASyncronous,this));
		iResult = err1;
		iLog->Log(_L("after getnotification vibra Active:"));
		TInt pos = 0;
		TInt transactionid = 0;
		const TLiwGenericParam* output2 = outparam->FindFirst( pos,KTransactionId );
		iLog->Log(_L("after FindFirst vibra Active:"));

		if(pos > 0)
			transactionid = output2->Value().AsTInt32(); 
		else;
		
		outparam->Reset();
		inparam->Reset();
		
		iLog->Log(_L("before SetNameAndValueL vibra Active:"));

		TLiwGenericParam transid;
		transid.SetNameAndValueL(KTransactionId,transactionid);
		inparam->AppendL(transid);
		
		transid.Reset();
		iLog->Log(_L("before KCancel vibra Active:"));

		TRAPD(errcancel,interface->ExecuteCmdL(KCancel,*inparam,*outparam,NULL,this));

		iTimer->After(OneMinute);

			if(errcancel == KErrNone)
				{
				pos = 0 ;
				outparam->FindFirst( pos, KErrorCode );
				if(pos != KErrNotFound)
					{
					iResult = (TInt)((*outparam)[pos].Value().AsTInt32());
					}
				if(iResult == SErrBadArgumentType)
					{
					iLog->Log(_L("after KCancel SErrBadArgumentType:"));
					iResult =  0;	
					}
				else
					{
					iResult =  -1;	
					}
				}//err1
		outparam->Reset();
		inparam->Reset();
		
		}
	else
		{
		iResult = err;
		iWaitSchedular->AsyncStop();
		}
		
	return ;
	}

TInt CTestBTCancel::HandleNotifyL(TInt /*aCmdId*/,
		            TInt aEventId,
		            CLiwGenericParamList& /*aEventParamList*/,
		            const CLiwGenericParamList& /*aInParamList*/)
	{
	if(aEventId == KLiwEventCanceled)
		{
		iResult =KErrNone;
		}
	else
		{
		iResult =KErrGeneral;
		}
				
	iWaitSchedular->AsyncStop();
	return KErrNone;
	}


int BTAsyncReqCancel(CStifLogger* aLog)
	{
//	__UHEAP_MARK;

	CTestBTCancel* test = CTestBTCancel::NewL(aLog);
	
	test->Start();
	TInt retval =	test->Result();
	aLog->Log(_L("after  test->Result:"));

	delete test;
//	__UHEAP_MARKEND;

	return retval;
	}

void CTestBTCancel::HandleTimeOut()
{
	iWaitSchedular->AsyncStop();
}	
