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

using namespace LIW ;
using namespace SysInfo;
using namespace sysinfoaiwparams;	


class CTestAsync2 : public CActive ,public MLiwNotifyCallback
{
public:
	static CTestAsync2* NewL(CStifLogger* aLog);
	~CTestAsync2();
	void Start();
	TInt Result();

	TInt HandleNotifyL(TInt aCmdId,
			            TInt aEventId,
			            CLiwGenericParamList& aEventParamList,
			            const CLiwGenericParamList& aInParamList);
    
    IMPORT_C static TInt32 GetTransactionID();
    
private:
	void ConstructL();
	CTestAsync2(CStifLogger* aLog);
	
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

CTestAsync2* CTestAsync2::NewL(CStifLogger* aLog)
	{
	CTestAsync2* self = new(ELeave) CTestAsync2(aLog);
	self->ConstructL();
	return self;
	}

CTestAsync2::~CTestAsync2()
	{
	Cancel();
	
	interface->Close();
	
	delete iServiceHandler;
	
	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();
	
	if(iWaitSchedular)
		delete iWaitSchedular;
	}

void CTestAsync2::ConstructL()
	{
	CActiveScheduler::Add(this);
	iWaitSchedular = new(ELeave) CActiveSchedulerWait();
	}

CTestAsync2::CTestAsync2(CStifLogger* aLog) :
CActive(EPriorityStandard),iResult(-1),iLog(aLog)
	{
	}

void CTestAsync2::DoCancel()
	{
	
	//TRAPD(err1,iSysInfoService->GetInfoL(req1));
		
	}

void CTestAsync2::RunL()
	{
	TestFunc();
	}

void CTestAsync2::Start()
	{
	
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}

TInt CTestAsync2::Result()
	{
	return iResult;
	}

void CTestAsync2::TestFunc()
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

		keyname.Set(KActiveConnections);
		key.SetNameAndValueL(KKey,keyname);

		inparam->AppendL(entity);

		inparam->AppendL(key);
		
		entity.Reset();
		entityname.Reset();
		key.Reset();
		keyname.Reset();
		
		//get  notification vibra Active
		TRAPD(err1,	interface->ExecuteCmdL(KGetInfo,*inparam,*outparam,KLiwOptASyncronous,this));
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

TInt CTestAsync2::HandleNotifyL(TInt /*aCmdId*/,
		            TInt /*aEventId*/,
		            CLiwGenericParamList& aEventParamList,
		            const CLiwGenericParamList& /*aInParamList*/)
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

			TLiwVariant data;

			Map->FindL(KConnectionList,data);
			CLiwIterable* iterlist=data.AsIterable();
			if(iterlist)
				{
				TLiwVariant iterdata;
				if(iterlist->NextL(iterdata))
					{
					iterlist->DecRef()	;
					const CLiwMap* Map = iterdata.AsMap(); 
					if ( Map )
						{
						TLiwVariant iapidVar;
						Map->FindL(KIAPID,iapidVar);
						TInt32 iapid = iapidVar.AsTInt32();
						TBuf<50> buf;
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
						}
					}
				iterdata.Reset();
				}
			iterlist->DecRef()	;
			}//map
		aEventParamList.Reset()	;
		}//output							
	iWaitSchedular->AsyncStop();
	return KErrNone;
	}


int ActiveConnection(CStifLogger* aLog)
	{
	__UHEAP_MARK;

	CTestAsync2* test = CTestAsync2::NewL(aLog);
	
	test->Start();
	TInt retval =	test->Result();
	delete test;
	__UHEAP_MARKEND;

	return retval;
	}

