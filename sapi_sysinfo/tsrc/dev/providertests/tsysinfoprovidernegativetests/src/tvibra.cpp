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
#include"watchtimer.h"

#include "sysinfointerface.h"
#include"entitykeys.h"
#include "sysinfoaiwparams.hrh"
#include "serviceerrno.h"

using namespace LIW ;
using namespace SysInfo;
using namespace sysinfoaiwparams;	


class CTestAsync1 : public CActive ,public MLiwNotifyCallback, public MTimeOutCallBack
{
public:
	static CTestAsync1* NewL(CStifLogger* aLog);
	~CTestAsync1();
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
	CTestAsync1(CStifLogger* aLog);
	
	virtual void DoCancel();
	virtual void RunL();

	void TestFunc();
	
private:	
	CActiveSchedulerWait* 	iWaitSchedular;
	CLiwServiceHandler* iServiceHandler;
	MLiwInterface* interface ;
	TInt32 vibrastatus ;
	TInt 					iResult;
	CStifLogger*			iLog;
		CWatchTimer*			iTimer;

};

CTestAsync1* CTestAsync1::NewL(CStifLogger* aLog)
	{
	CTestAsync1* self = new(ELeave) CTestAsync1(aLog);
	self->ConstructL();
	return self;
	}

CTestAsync1::~CTestAsync1()
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

void CTestAsync1::ConstructL()
	{
	CActiveScheduler::Add(this);
	iWaitSchedular = new(ELeave) CActiveSchedulerWait();
	iTimer			= CWatchTimer::NewL(EPriorityNormal,this);
	}

CTestAsync1::CTestAsync1(CStifLogger* aLog) :
CActive(EPriorityStandard),iResult(-1),iLog(aLog)
	{
	}

void CTestAsync1::DoCancel()
	{
	
	}

void CTestAsync1::RunL()
	{
	TestFunc();
	}

void CTestAsync1::Start()
	{
	
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}

TInt CTestAsync1::Result()
	{
	return iResult;
	}

void CTestAsync1::TestFunc()
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
		
		entityname.Set(KGeneral);
		entity.SetNameAndValueL(KEntity,entityname);

		keyname.Set(KVibraActive);
		key.SetNameAndValueL(KKey,keyname);

		inparam->AppendL(entity);

		inparam->AppendL(key);
		
		entity.Reset();
		entityname.Reset();
		key.Reset();
		keyname.Reset();
		
		iLog->Log(_L("before getnotification vibra Active:"));

		//get  notification vibra Active
		TRAPD(err1,	interface->ExecuteCmdL(KGetNotification,*inparam,*outparam,NULL,this));
		iTimer->After(OneMinute);

		iResult = err1;
			if(err1 == KErrNone)
				{
				pos = 0 ;
				const TLiwGenericParam* output = outparam->FindFirst( pos,KErrorCode );
				iResult = output->Value().AsTInt32(); 
				if(iResult != SErrBadArgumentType)
					{
					iResult =  -1;	
					}
				else
				{
				iResult =  0;	
				CLiwGenericParamList* outparam1 = CLiwGenericParamList::NewL();
				inparam->Reset();
				
				entityname.Set(KGeneral);
				entity.SetNameAndValueL(KEntity,entityname);

				keyname.Set(KVibraActive);
				key.SetNameAndValueL(KKey,keyname);

				inparam->AppendL(entity);

				inparam->AppendL(key);
				
				entity.Reset();
				entityname.Reset();
				key.Reset();
				keyname.Reset();
				
				//get current display language
				TRAPD(err2,	interface->ExecuteCmdL(KGetInfo,*inparam,*outparam1,KLiwOptASyncronous,this));
				
				iResult = err2;
				if(err2 == KErrNone)
					{
					pos =0 ;
					const TLiwGenericParam* output1 = outparam1->FindFirst( pos,KErrorCode );
							iResult = output1->Value().AsTInt32(); 
							if(iResult != SErrServiceNotSupported)
								{
								iResult =  -1;	
								}
							else
							{
							iResult =  0;	
							pos = 0 ;
					const TLiwGenericParam* output1 = outparam1->FindFirst( pos,KReturnValue );
					if(output1)     
						{
						const CLiwMap* Map = output1->Value().AsMap(); 
						if ( Map )
							{
							TLiwVariant data;
							if(EFalse!=Map->FindL(KStatus,data))
								{
								vibrastatus=data.AsTInt32();
								}
							}//map
						}//output
					
					inparam->Reset();
					outparam1->Reset();
					outparam->Reset();
				
				entityname.Set(KGeneral);
				entity.SetNameAndValueL(KEntity,entityname);

				keyname.Set(KVibraActive);
				key.SetNameAndValueL(KKey,keyname);
				

				//sysdata as map
				CLiwDefaultMap* map = CLiwDefaultMap::NewL();
				CleanupStack::PushL(map);

			    TLiwVariant sysdata((TInt32)!vibrastatus);
			    map->InsertL(KStatus,sysdata); 
			    sysdata.Reset();	
		    

			    TLiwVariant sysparam(map);
				TLiwGenericParam element ;	
				element.SetNameAndValueL(KSysData,sysparam);
				
				
				inparam->AppendL(entity);
				inparam->AppendL(key);

				inparam->AppendL(element);
				element.Reset();
				sysparam.Reset();
				
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
				TRAPD(err3,	interface->ExecuteCmdL(KSetInfo,*inparam,*outparam1));
				
				inparam->Reset();
				outparam1->Reset();
							}
				}//err2
					}
			}//err1
	
		}//interface
	return ;
	}


TInt CTestAsync1::HandleNotifyL(TInt /*aCmdId*/,
		            TInt /*aEventId*/,
		            CLiwGenericParamList& aEventParamList,
		            const CLiwGenericParamList& /*aInParamList*/)
	{
	TInt pos = 0;
	aEventParamList.FindFirst( pos, KErrorCode );
	if(pos != KErrNotFound)
		{
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
				if(EFalse!=Map->FindL(KStatus,data))
					{
					TInt32 changedvibrastatus=data.AsTInt32();

					if(changedvibrastatus == (!vibrastatus))
						{
						iResult = KErrNone;
						}
					else
						{
						iResult =  KErrGeneral;
						}
					}	
				
				}//map
		}//output							
	iWaitSchedular->AsyncStop();
	return 0;
	}

void CTestAsync1::HandleTimeOut()
{
	iWaitSchedular->AsyncStop();
}	
int VibraNotification(CStifLogger* aLog)
	{
	__UHEAP_MARK;

	CTestAsync1* test = CTestAsync1::NewL(aLog);
	
	test->Start();
	TInt retval =	test->Result();
	delete test;
	return retval;
	__UHEAP_MARKEND;


	}

