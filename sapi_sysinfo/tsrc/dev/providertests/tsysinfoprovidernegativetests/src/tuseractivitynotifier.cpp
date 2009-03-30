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
#include "serviceerrno.h"
#include"watchtimer.h"

using namespace LIW ;
using namespace SysInfo;
using namespace sysinfoaiwparams;	


class CUserInactivity : public CActive ,public MLiwNotifyCallback, public MTimeOutCallBack
{
public:
	static CUserInactivity* NewL(CStifLogger* aLog);
	~CUserInactivity();
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
	CUserInactivity(CStifLogger* aLog);
	
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

CUserInactivity* CUserInactivity::NewL(CStifLogger* aLog)
	{
	CUserInactivity* self = new(ELeave) CUserInactivity(aLog);
	self->ConstructL();
	return self;
	}

CUserInactivity::~CUserInactivity()
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

void CUserInactivity::ConstructL()
	{
	CActiveScheduler::Add(this);
	iWaitSchedular = new(ELeave) CActiveSchedulerWait();
	iTimer			= CWatchTimer::NewL(EPriorityNormal,this);
	}

CUserInactivity::CUserInactivity(CStifLogger* aLog) :
CActive(EPriorityStandard),iResult(-1),iLog(aLog)
	{
	}

void CUserInactivity::DoCancel()
	{
	
	//TRAPD(err1,iSysInfoService->GetInfoL(req1));
		
	}

void CUserInactivity::RunL()
	{
	TestFunc();
	}

void CUserInactivity::Start()
	{
	
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}

TInt CUserInactivity::Result()
	{
	return iResult;
	}

void CUserInactivity::TestFunc()
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
		
		entityname.Set(KDisplay);
		entity.SetNameAndValueL(KEntity,entityname);

		keyname.Set(KUserInactivity);
		key.SetNameAndValueL(KKey,keyname);

	    //sysdata as map
		CLiwDefaultMap* map = CLiwDefaultMap::NewL();
		CleanupStack::PushL(map);

	    TLiwVariant sysdata((TInt32)-5);
	    map->InsertL(KStatus,sysdata); 
	    sysdata.Reset();	

	    TLiwVariant sysparam(map);
		TLiwGenericParam element ;	
		element.SetNameAndValueL(KSysData,sysparam);
		sysparam.Reset();

		inparam->AppendL(entity);

		inparam->AppendL(key);
		inparam->AppendL(element);
		
		element.Reset();

		map->DecRef();
		CleanupStack::Pop(map);
			
		entity.Reset();
		entityname.Reset();
		key.Reset();
		keyname.Reset();
		sysdata.Reset();
		
		//get  notification vibra Active
		TRAPD(err1,	interface->ExecuteCmdL(KGetNotification,*inparam,*outparam,KLiwOptASyncronous,this));
		iTimer->After(OneMinute);
	
		iResult = err1;
			if(err1 == KErrNone)
				{
				pos = 0 ;
				outparam->FindFirst( pos, KErrorCode );
				if(pos != KErrNotFound)
					{
					iResult = (TInt)((*outparam)[pos].Value().AsTInt32());
					}
				if(iResult != SErrNone)
					{
					iLog->Log(_L("after KGetNotification Error: %d"),iResult);
					iResult =  0;	
					iWaitSchedular->AsyncStop();
					}
				else
					{
					iLog->Log(_L("after KGetNotification :"));
					iResult =  -1;	
					}
				}//err1
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

TInt CUserInactivity::HandleNotifyL(TInt /*aCmdId*/,
		            TInt aEventId,
		            CLiwGenericParamList& aEventParamList,
		            const CLiwGenericParamList& /*aInParamList*/)
	{
	iLog->Log(_L("In HandleNotifyL Event ID: %d"),aEventId);
	if(aEventId == KLiwEventCanceled)
		{
		iLog->Log(_L("EventID: KLiwEventCanceled"));
		iResult =KErrNone;
		}
	else
		{
	    iResult =-1;
		}
				
	iWaitSchedular->AsyncStop();
	return KErrNone;
	}
	
void CUserInactivity::HandleTimeOut()
{
	iLog->Log(_L("In HandleTimeOut"));
	iWaitSchedular->AsyncStop();
}	


int UserInactivity(CStifLogger* aLog)
	{
	__UHEAP_MARK;

	CUserInactivity* test = CUserInactivity::NewL(aLog);
	
	test->Start();
	TInt retval =	test->Result();
	delete test;
	__UHEAP_MARKEND;

	return retval;
	}

