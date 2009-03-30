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

#include"tsysinfoprovidergeneraltests.h"
#include "sysinfointerface.h"
#include"entitykeys.h"
#include "sysinfoaiwparams.hrh"

using namespace LIW ;
using namespace SysInfo;
using namespace sysinfoaiwparams;	


class CTestAsync3 : public CActive ,public MLiwNotifyCallback
{
public:
	static CTestAsync3* NewL(CStifLogger* aLog);
	~CTestAsync3();
	void Start();
	TInt Result();

	TInt HandleNotifyL(TInt aCmdId,
			            TInt aEventId,
			            CLiwGenericParamList& aEventParamList,
			            const CLiwGenericParamList& aInParamList);
    
    IMPORT_C static TInt32 GetTransactionID();

private:
	void ConstructL();
	CTestAsync3(CStifLogger* aLog);
	
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
};

CTestAsync3* CTestAsync3::NewL(CStifLogger* aLog)
	{
	CTestAsync3* self = new(ELeave) CTestAsync3(aLog);
	self->ConstructL();
	return self;
	}

CTestAsync3::~CTestAsync3()
	{
	Cancel();
	
	interface->Close();
	
	delete iServiceHandler;
	
	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();
	
	if(iWaitSchedular)
		delete iWaitSchedular;
	}

void CTestAsync3::ConstructL()
	{
	CActiveScheduler::Add(this);
	iWaitSchedular = new(ELeave) CActiveSchedulerWait();
	}

CTestAsync3::CTestAsync3(CStifLogger* aLog) :
CActive(EPriorityStandard),iResult(-1),iLog(aLog)
	{
	}

void CTestAsync3::DoCancel()
	{
	
	//TRAPD(err1,iSysInfoService->GetInfoL(req1));
		
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

		keyname.Set(SysInfo::KConnectionStatus);
		key.SetNameAndValueL(KKey,keyname);

		inparam->AppendL(entity);

		inparam->AppendL(key);
		
		entity.Reset();
		entityname.Reset();
		key.Reset();
		keyname.Reset();
		
		iLog->Log(_L("Calling notification"));		
		
		//get  notification vibra Active
		TRAPD(err1,	interface->ExecuteCmdL(KGetNotification,*inparam,*outparam,KLiwOptASyncronous,this));
		iResult = err1;
			if(err1 == KErrNone)
				{
				;
	
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

TInt CTestAsync3::HandleNotifyL(TInt aCmdId,
		            TInt aEventId,
		            CLiwGenericParamList& aEventParamList,
		            const CLiwGenericParamList& aInParamList)
	{
	TInt pos = 0;
	aEventParamList.FindFirst( pos, KErrorCode );
	if(pos != KErrNotFound)
		{
		if( (aEventParamList)[pos].Value().AsTInt32() != KErrNone )
		iResult = (TInt)((aEventParamList)[pos].Value().AsTInt32());
		}
			
	pos = 0 ;
	const TLiwGenericParam* output2 = aEventParamList.FindFirst( pos,KReturnValue );
	
	if(output2)     
		{
		const CLiwMap* Map = output2->Value().AsMap(); 
		if ( Map )
			{

			TLiwVariant connstate;
			Map->FindL(sysinfoaiwparams::KConnectionStatus,connstate);
			TUint state = connstate.AsTUint();
			TBuf<50> buf;
			buf.AppendNum(state);
			iLog->Log(_L("ConnectionStatus: "));
			iLog->Log(buf);
			connstate.Reset();
			
			TLiwVariant iapidVar;
			Map->FindL(KIAPID,iapidVar);
			TInt32 iapid = iapidVar.AsTInt32();
			buf.Zero();
			buf.AppendNum(iapid);
			iLog->Log(_L("IAPID"));
			iLog->Log(buf);
			iapidVar.Reset();


			TLiwVariant bearerTypeVar;
			Map->FindL(KConnectionType,bearerTypeVar);
			TInt32 bearerType = bearerTypeVar.AsTInt32();
			buf.Zero();
			buf.AppendNum(bearerType);
			iLog->Log(_L("Bearer Type:"));
			iLog->Log(buf);
			bearerTypeVar.Reset();

			TLiwVariant iapNameVar;
			Map->FindL(KIAPName,iapNameVar);
			TPtrC iapName = iapNameVar.AsDes();
			buf.Zero();
			buf.Copy(iapName);
			iLog->Log(_L("IAP Name:"));
			iLog->Log(buf);
			iapNameVar.Reset();

			TLiwVariant netNameVar;
			Map->FindL(KNetworkName,netNameVar);
			TPtrC netName = netNameVar.AsDes();
			buf.Zero();
			buf.Copy(netName);
			iLog->Log(_L("network Name:"));
			iLog->Log(buf);
			netNameVar.Reset();

			TLiwVariant connNameVar;
			Map->FindL(KIAPConnectionName,connNameVar);
			TPtrC connName = connNameVar.AsDes();
			buf.Zero();
			buf.Copy(connName);
			iLog->Log(_L("Connection Name:"));
			iLog->Log(buf);
			connNameVar.Reset();
			}//map
		((CLiwMap*)Map)->DecRef();
		}//output
	aEventParamList.Reset();
	iWaitSchedular->AsyncStop();
	}


int ConnectionNotification(CStifLogger* aLog)
	{
	__UHEAP_MARK;

	CTestAsync3* test = CTestAsync3::NewL(aLog);
	
	test->Start();
	TInt retval =	test->Result();
	delete test;
	__UHEAP_MARKEND;

	return retval;
	}

