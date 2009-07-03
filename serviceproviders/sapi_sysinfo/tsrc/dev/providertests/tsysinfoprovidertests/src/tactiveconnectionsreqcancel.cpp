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

#include <Liwcommon.h>
#include<LiwServiceHandler.h>

#include"tsysinfoprovidertests.h"
#include "sysinfointerface.h"
#include"entitykeys.h"
#include "sysinfoaiwparams.hrh"
#include"watchtimer.h"

using namespace LIW ;
using namespace SysInfo;
using namespace sysinfoaiwparams;	

TInt CheckErrorCode( const CLiwGenericParamList& aOutList, TInt32 &aError );

class CTestActiveConnCancel : public CActive ,public MLiwNotifyCallback, public MTimeOutCallBack
{
public:
	static CTestActiveConnCancel* NewL(CStifLogger* aLog);
	~CTestActiveConnCancel();
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
	CTestActiveConnCancel(CStifLogger* aLog);
	
	virtual void DoCancel();
	virtual void RunL();
	
	void TestFunc();

private:	
	CActiveSchedulerWait* 	iWaitSchedular;
	CLiwServiceHandler* iServiceHandler;
	MLiwInterface* interface ;
	TInt32 btstatus ;
	TInt 					iResult;
	CStifLogger*			iLog;
	CWatchTimer*			iTimer;

};

CTestActiveConnCancel* CTestActiveConnCancel::NewL(CStifLogger* aLog)
	{
	CTestActiveConnCancel* self = new(ELeave) CTestActiveConnCancel(aLog);
	self->ConstructL();
	return self;
	}

CTestActiveConnCancel::~CTestActiveConnCancel()
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

void CTestActiveConnCancel::ConstructL()
	{
	CActiveScheduler::Add(this);
	iWaitSchedular = new(ELeave) CActiveSchedulerWait();
	iTimer			= CWatchTimer::NewL(EPriorityNormal,this);

	}

CTestActiveConnCancel::CTestActiveConnCancel(CStifLogger* aLog) :
CActive(EPriorityStandard),iResult(-1),iLog(aLog)
	{
	}

void CTestActiveConnCancel::DoCancel()
	{
	
	//TRAPD(err1,iSysInfoService->GetInfoL(req1));
		
	}

void CTestActiveConnCancel::RunL()
	{
	TestFunc();
	}

void CTestActiveConnCancel::Start()
	{
	
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}

TInt CTestActiveConnCancel::Result()
	{
	return iResult;
	}

void CTestActiveConnCancel::TestFunc()
	{
    iLog->Log(_L("In test func"));
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

		keyname.Set(KActiveConnections);
		key.SetNameAndValueL(KKey,keyname);

		inparam->AppendL(entity);

		inparam->AppendL(key);
		
		entity.Reset();
		entityname.Reset();
		key.Reset();
		keyname.Reset();
		
		iLog->Log(_L("Issueing Notification Request"));
		//get  notification vibra Active
		TRAPD(err1,	interface->ExecuteCmdL(KGetInfo,*inparam,*outparam,KLiwOptASyncronous,this));
		iResult = err1;
		
		TInt pos = 0;
		const TLiwGenericParam* output2 = outparam->FindFirst( pos,KTransactionId );
		TInt32 transactionid = output2->Value().AsTInt32(); 
		
		outparam->Reset();
		inparam->Reset();
		
		TLiwGenericParam transid;
		transid.SetNameAndValueL(KTransactionId,transactionid);
		inparam->AppendL(transid);
		transid.Reset();
        
        iLog->Log(_L("Issueing Cancel Request"));
		TRAPD(errcancel,interface->ExecuteCmdL(KCancel,*inparam,*outparam,KLiwOptCancel,this));
        TInt32 Err(KErrNone);
        err |= CheckErrorCode(*outparam,Err);
        if(Err)
            {
            iLog->Log(_L("Cancle Operation returned err: %d"),Err);
            }
		
		iTimer->After(OneMinute);
		
		outparam->Reset();
		inparam->Reset();

		}//interface
	else
		{
		iLog->Log( _L("API returned error") );
		iResult = err;
		iWaitSchedular->AsyncStop();
		}
		
	return ;
	}

TInt CTestActiveConnCancel::HandleNotifyL(TInt /*aCmdId*/,
		            TInt aEventId,
		            CLiwGenericParamList& /*aEventParamList*/,
		            const CLiwGenericParamList& /*aInParamList*/)
	{
	iLog->Log(_L("In Handle NotifyL"));	
	iLog->Log(_L("EventId: %d"),aEventId);	
	if(aEventId == KLiwEventCanceled)
		{
		iLog->Log(_L("EventId is KLiwEventCanceled"));	
		iResult =KErrNone;
		}
	else
		{
		iLog->Log(_L("Wrong eventID generated"));	
	    iResult =KErrGeneral;
		}
				
	iWaitSchedular->AsyncStop();
	return KErrNone;
	}


int ActiveConnectionReqCancel(CStifLogger* aLog)
	{
	__UHEAP_MARK;

	CTestActiveConnCancel* test = CTestActiveConnCancel::NewL(aLog);
	
	test->Start();
	TInt retval =	test->Result();
	delete test;
	__UHEAP_MARKEND;

	return retval;
	}
	
void CTestActiveConnCancel::HandleTimeOut()
{
	iLog->Log(_L("Timeout reached.."));
	iWaitSchedular->AsyncStop();
}	

TInt CheckErrorCode( const CLiwGenericParamList& aOutList, TInt32 &aError )
	{
	TInt Index = 0;
	const TLiwGenericParam* errcode = aOutList.FindFirst(Index,KErrorCode);
	if ( KErrNotFound == Index )
		{
		return FAIL;
		}
	else
		errcode->Value().Get(aError);
	return PASS;
	}
