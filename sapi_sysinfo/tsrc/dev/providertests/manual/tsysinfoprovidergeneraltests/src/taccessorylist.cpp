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

#include "tsysinfoprovidergeneraltests.h"
#include "sysinfointerface.h"
#include"entitykeys.h"
#include "sysinfoaiwparams.hrh"
#include "serviceerrno.h"
#include"watchtimer.h"

using namespace LIW ;
using namespace SysInfo;
using namespace sysinfoaiwparams;	


class CTestAccIter : public CActive ,public MLiwNotifyCallback, public MTimeOutCallBack
{
public:
	static CTestAccIter* NewL(CStifLogger* aLog);
	~CTestAccIter();
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
	CTestAccIter(CStifLogger* aLog);
	
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

CTestAccIter* CTestAccIter::NewL(CStifLogger* aLog)
	{
	CTestAccIter* self = new(ELeave) CTestAccIter(aLog);
	self->ConstructL();
	return self;
	}

CTestAccIter::~CTestAccIter()
	{
	Cancel();
	
	if(interface)
	interface->Close();
	
	delete iServiceHandler;
	
	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();
	
	if(iWaitSchedular)
		delete iWaitSchedular;
	delete iTimer;
	}

void CTestAccIter::ConstructL()
	{
	CActiveScheduler::Add(this);
	iWaitSchedular = new(ELeave) CActiveSchedulerWait();
	iTimer			= CWatchTimer::NewL(EPriorityNormal,this);
	}

CTestAccIter::CTestAccIter(CStifLogger* aLog) :
CActive(EPriorityStandard),iResult(-1),iLog(aLog)
	{
	}

void CTestAccIter::DoCancel()
	{
	
	//TRAPD(err1,iSysInfoService->GetInfoL(req1));
		
	}

void CTestAccIter::RunL()
	{
	TestFunc();
	}

void CTestAccIter::Start()
	{
	
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}

TInt CTestAccIter::Result()
	{
	return iResult;
	}

void CTestAccIter::TestFunc()
	{
	// On Emulator this is not supported.				
	#if (! (defined(__WINS__) || defined(__WINSCW__)) )

    iLog->Log(_L("Test Function:"));

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

    iLog->Log(_L("Interface loaded successfully"));

	outparam->Reset();
	inparam->Reset();
	
	if(interface)
		{
		TLiwGenericParam entity;
		TLiwVariant  entityname;
		TLiwGenericParam key;
		TLiwVariant  keyname;
		
		entityname.Set(KGeneral);
		entity.SetNameAndValueL(KEntity,entityname);

		keyname.Set(KConnectedAccessories);
		key.SetNameAndValueL(KKey,keyname);

		inparam->AppendL(entity);

		inparam->AppendL(key);
		
		entity.Reset();
		entityname.Reset();
		key.Reset();
		keyname.Reset();
		iLog->Log( _L("Calling getinfo for accessory list") );
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
					if(iResult != KErrNone)
					    {
					    iLog->Log(_L("Error Code: %d"),iResult);
					    iResult = err;
		                iWaitSchedular->AsyncStop();
					    }
					}
				else
				    {
				    iLog->Log(_L("Error Code not found"));
				    }
				iLog->Log(_L("Error Code: %d"),iResult);
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
		
	#else
		iResult = 0;
		iWaitSchedular->AsyncStop();

	#endif
		return ;
	}

TInt CTestAccIter::HandleNotifyL(TInt /*aCmdId*/,
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
						iLog->Log(_L("err"));
						iLog->Log(buf);

		}

	pos = 0 ;
	const TLiwGenericParam* output2 = aEventParamList.FindFirst( pos,KReturnValue );
	if(output2)     
		{
		iLog->Log(_L("inside output2:"));

		const CLiwMap* Map = output2->Value().AsMap(); 
		if ( Map )
			{
			iLog->Log(_L("inside Map:"));
			TLiwVariant data;

			Map->FindL(KConnectionList,data);
			CLiwIterable* iterlist=data.AsIterable();

			if(iterlist)
				{
		        iLog->Log(_L("inside iterlist:"));
				TLiwVariant iterdata;int countlist = 0;
				while(iterlist->NextL(iterdata))
					{
		            iLog->Log(_L("inside iterlist->NextL:"));
					const CLiwMap* Map = iterdata.AsMap(); 
					if ( Map )
						{
		                iLog->Log(_L("inside Map2:"));
						TLiwVariant accessoryTypeVar;
						Map->FindL(KAccessoryType,accessoryTypeVar);
						TInt accessoryType = accessoryTypeVar.AsTInt32();
						TBuf<50> buf;
						buf.AppendNum(accessoryType);
						iLog->Log(_L("accessoryType"));
						iLog->Log(buf);
						accessoryTypeVar.Reset();


						TLiwVariant AccessoryStateVar;
						Map->FindL(KAccessoryState,AccessoryStateVar);
						TInt32 AccessoryState = AccessoryStateVar.AsTInt32();
						buf.Zero();
						buf.AppendNum(AccessoryState);
						iLog->Log(_L("AccessoryState:"));
						iLog->Log(buf);
						AccessoryStateVar.Reset();

						}
						
					countlist++;
					if(countlist < 2)	
					 iterlist->Reset();
					
					iterdata.Reset();
					}
				}
					iterlist->DecRef();
			}//map
			aEventParamList.Reset();
		}//output							
	iWaitSchedular->AsyncStop();
	return KErrNone;
	}

void CTestAccIter::HandleTimeOut()
{
    iLog->Log( _L("Timeout reached..") );
	iWaitSchedular->AsyncStop();
}	


int AccIter(CStifLogger* aLog)
	{
	__UHEAP_MARK;

	CTestAccIter* test = CTestAccIter::NewL(aLog);
	
	test->Start();
	TInt retval =	test->Result();
	delete test;
	__UHEAP_MARKEND;

	return retval;
	}

