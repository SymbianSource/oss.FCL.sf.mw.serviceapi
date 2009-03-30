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

#include "sysinfointerface.h"
#include"entitykeys.h"
#include "sysinfoaiwparams.hrh"

using namespace LIW ;
using namespace SysInfo;
using namespace sysinfoaiwparams;	


class CTestAsync1 : public CActive ,public MLiwNotifyCallback
{
public:
	static CTestAsync1* NewL();
	~CTestAsync1();
	void Start();
	TInt Result();

	TInt HandleNotifyL(TInt aCmdId,
			            TInt aEventId,
			            CLiwGenericParamList& aEventParamList,
			            const CLiwGenericParamList& aInParamList);
  
   	IMPORT_C static TInt32 GetTransactionID();
   	
private:
	void ConstructL();
	CTestAsync1();
	
	virtual void DoCancel();
	virtual void RunL();

	void TestFunc();
	
private:	
	CActiveSchedulerWait* 	iWaitSchedular;
	CLiwServiceHandler* iServiceHandler;
	MLiwInterface* interface ;
	TInt32 vibrastatus ;
	TInt 					iResult;	
};

CTestAsync1* CTestAsync1::NewL()
	{
	CTestAsync1* self = new(ELeave) CTestAsync1();
	self->ConstructL();
	return self;
	}

CTestAsync1::~CTestAsync1()
	{
	Cancel();
	Cancel();
	
	interface->Close();
	
	delete iServiceHandler;
	
	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();
	
	if(iWaitSchedular)
		delete iWaitSchedular;
	}

void CTestAsync1::ConstructL()
	{
	CActiveScheduler::Add(this);
	iWaitSchedular = new(ELeave) CActiveSchedulerWait();
	}

CTestAsync1::CTestAsync1() :
CActive(EPriorityStandard),iResult(-1)
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
		
		//get  notification vibra Active
		TRAPD(err1,	interface->ExecuteCmdL(KGetNotification,*inparam,*outparam,KLiwOptASyncronous,this));
		iResult = err1;
			if(err1 == KErrNone)
				{
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
				TRAPD(err2,	interface->ExecuteCmdL(KGetInfo,*inparam,*outparam1));
				
				iResult = err2;
				if(err2 == KErrNone)
					{
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
				}//err2
	
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


int VibraNotification(int, char**)
	{
	__UHEAP_MARK;

	CTestAsync1* test = CTestAsync1::NewL();
	
	test->Start();
	TInt retval =	test->Result();
	delete test;
	return retval;
	__UHEAP_MARKEND;


	}

