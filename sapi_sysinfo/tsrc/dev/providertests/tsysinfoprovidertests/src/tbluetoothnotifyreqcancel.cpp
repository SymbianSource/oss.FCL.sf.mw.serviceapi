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
#include <btengsettings.h>

#include "sysinfointerface.h"
#include"entitykeys.h"
#include "sysinfoaiwparams.hrh"
#include"watchtimer.h"

using namespace LIW ;
using namespace SysInfo;
using namespace sysinfoaiwparams;	


class CTestBTCancel : public CActive ,public MLiwNotifyCallback, public MTimeOutCallBack
{
public:
	static CTestBTCancel* NewL();
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

	CTestBTCancel();
	
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
	
};

CTestBTCancel* CTestBTCancel::NewL()
	{
	CTestBTCancel* self = new(ELeave) CTestBTCancel();
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

CTestBTCancel::CTestBTCancel() :
CActive(EPriorityStandard),iResult(-1)
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

	const TTimeIntervalMicroSeconds32 OneMinute(6000);

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
		
		//get  notification vibra Active
		TRAPD(err1,	interface->ExecuteCmdL(KGetNotification,*inparam,*outparam,KLiwOptASyncronous,this));
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

		TRAPD(errcancel,interface->ExecuteCmdL(KCancel,*inparam,*outparam,NULL,this));
		outparam->Reset();
		inparam->Reset();
		

		iTimer->After(OneMinute);

			if(err1 == KErrNone)
				{
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
				
				//get current display language
				TRAPD(err2,	interface->ExecuteCmdL(KGetInfo,*inparam,*outparam));
				
				iResult = err2;
				if(err2 == KErrNone)
					{
					pos = 0 ;
					const TLiwGenericParam* output1 = outparam->FindFirst( pos,KReturnValue );
					if(output1)     
						{
						const CLiwMap* Map = output1->Value().AsMap(); 
						if ( Map )
							{
							TLiwVariant data;
							if(EFalse!=Map->FindL(KStatus,data))
								{
								btstatus=data.AsTInt32();
								}
							}//map
						}//output
					
					inparam->Reset();
					outparam->Reset();

				CBTEngSettings* BtSettings = CBTEngSettings::NewLC();
	            if( btstatus == EOn)
	                BtSettings->SetPowerState( EBTPowerOff );
	            else if(btstatus == EOff)
	                BtSettings->SetPowerState( EBTPowerOn );
	            CleanupStack::PopAndDestroy(BtSettings);					
#ifdef _SET_BLUETOOTH_SUPPORTED_
					
				entityname.Set(KConnectivity);
				entity.SetNameAndValueL(KEntity,entityname);

				keyname.Set(KBlueTooth);
				key.SetNameAndValueL(KKey,keyname);

				//sysdata as map
				CLiwDefaultMap* map = CLiwDefaultMap::NewL();
				CleanupStack::PushL(map);

			    TLiwVariant sysdata((TInt32)!btstatus);
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
				inparam->AppendL(entity);
				inparam->AppendL(key);

				entity.Reset();
				entityname.Reset();
				key.Reset();
				keyname.Reset();
				sysdata.Reset();
				
				//set new display language
				TRAPD(err3,	interface->ExecuteCmdL(KSetInfo,*inparam,*outparam));
#endif				
				}//err2
	
			}//err1
	
		}//interface
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


int BTAsyncReqCancel()
	{
	__UHEAP_MARK;

	CTestBTCancel* test = CTestBTCancel::NewL();
	
	test->Start();
	TInt retval =	test->Result();
	delete test;
	__UHEAP_MARKEND;

	return retval;
	}

void CTestBTCancel::HandleTimeOut()
{
	iWaitSchedular->AsyncStop();
}	
