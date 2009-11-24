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

#include "tsysinfoprovidergeneraltests.h"
#include "sysinfointerface.h"
#include"entitykeys.h"
#include "sysinfoaiwparams.hrh"
#include"watchtimer.h"
#include "serviceerrno.h"

using namespace LIW ;
using namespace SysInfo;
using namespace sysinfoaiwparams;	


class CTestConnList : public CActive ,public MLiwNotifyCallback, public MTimeOutCallBack
{
public:
	static CTestConnList* NewL(CStifLogger* aLog);
	~CTestConnList();
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
	CTestConnList(CStifLogger* aLog);
	
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

CTestConnList* CTestConnList::NewL(CStifLogger* aLog)
	{
	CTestConnList* self = new(ELeave) CTestConnList(aLog);
	self->ConstructL();
	return self;
	}

CTestConnList::~CTestConnList()
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

void CTestConnList::ConstructL()
	{
	CActiveScheduler::Add(this);
	iWaitSchedular = new(ELeave) CActiveSchedulerWait();
	iTimer			= CWatchTimer::NewL(EPriorityNormal,this);
	}

CTestConnList::CTestConnList(CStifLogger* aLog) :
CActive(EPriorityStandard),iResult(-1),iLog(aLog)
	{
	}

void CTestConnList::DoCancel()
	{
	
	//TRAPD(err1,iSysInfoService->GetInfoL(req1));
		
	}

void CTestConnList::RunL()
	{
	TestFunc();
	}

void CTestConnList::Start()
	{
	
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}

TInt CTestConnList::Result()
	{
	return iResult;
	}

void CTestConnList::TestFunc()
	{
	const TTimeIntervalMicroSeconds32 OneMinute(60000000);
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
				if(iResult == SErrBadArgumentType)
					{
					iLog->Log(_L("after KCancel SErrBadArgumentType:"));
					iResult =  -1;	
					}
				else
					{
					iResult = 0;	
					}
				}//err1
		outparam->Reset();
		inparam->Reset();

		}//interface
	else
		{
		iLog->Log( _L("Interface not loaded..") );
		iResult = err;
		iWaitSchedular->AsyncStop();
		}
		
	return ;
	}

TInt CTestConnList::HandleNotifyL(TInt /*aCmdId*/,
		            TInt /*aEventId*/,
		            CLiwGenericParamList& aEventParamList,
		            const CLiwGenericParamList& /*aInParamList*/)
	{
    iLog->Log(_L("In HandleNotifyL"));
	TInt pos = 0;
	aEventParamList.FindFirst( pos, KErrorCode );
	if(pos != KErrNotFound)
		{
		if( (aEventParamList)[pos].Value().AsTInt32() != KErrNone )
			iResult = (TInt)((aEventParamList)[pos].Value().AsTInt32());
			TBuf<50> buf;
			buf.AppendNum(iResult);
			iLog->Log(_L("Error Code: "));
			iLog->Log(buf);
		}

	pos = 0 ;
	const TLiwGenericParam* output2 = aEventParamList.FindFirst( pos,KReturnValue );
	if(output2)     
		{
        iLog->Log(_L("KReturnValue Found"));
		const CLiwMap* Map = output2->Value().AsMap(); 
		if ( Map )
			{
			TLiwVariant data;
    		Map->FindL(KConnectionList,data);
			CLiwIterable* iterlist=data.AsIterable();

			if(iterlist)
				{
				TLiwVariant iterdata;int countlist = 0;
				while(iterlist->NextL(iterdata))
					{
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
					else
					    {
					    iLog->Log(_L("Iterator data is not a map"));
					    }
						
					countlist++;
					if(countlist < 2)	
                        iterlist->Reset();
					
					iterdata.Reset();
					}// while
				iterlist->DecRef();
				}//
			else
			    {
			    iLog->Log(_L("KConnectionList is not a Iterable object"));
			    }
			}//map
		else
		    {
		    iLog->Log(_L("Return value is not a map"));
		    }
		aEventParamList.Reset();
		}//output							
	iWaitSchedular->AsyncStop();
	return KErrNone;
	}
void CTestConnList::HandleTimeOut()
{
	iWaitSchedular->AsyncStop();
}	


int ConnList(CStifLogger* aLog)
	{
	__UHEAP_MARK;

	CTestConnList* test = CTestConnList::NewL(aLog);
	
	test->Start();
	TInt retval =	test->Result();
	delete test;
	__UHEAP_MARKEND;

	return retval;
	}

