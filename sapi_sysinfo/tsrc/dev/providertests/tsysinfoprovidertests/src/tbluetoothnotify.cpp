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
#include <LiwServiceHandler.h>
#include <btengsettings.h>

#include "sysinfointerface.h"
#include "entitykeys.h"
#include "sysinfoaiwparams.hrh"
#include "serviceerrno.h"

using namespace LIW ;
using namespace SysInfo;
using namespace sysinfoaiwparams;	


class CTestAsync : public CActive ,public MLiwNotifyCallback
{
public:
	static CTestAsync* NewL();
	~CTestAsync();
	void Start();
	TInt Result();

	TInt HandleNotifyL(TInt aCmdId,
			            TInt aEventId,
			            CLiwGenericParamList& aEventParamList,
			            const CLiwGenericParamList& aInParamList);
    
    IMPORT_C static TInt32 GetTransactionID();

private:
	void ConstructL();
	CTestAsync();
	
	virtual void DoCancel();
	virtual void RunL();
	
	void TestFunc();

private:	
	CActiveSchedulerWait* 	iWaitSchedular;
	CLiwServiceHandler* iServiceHandler;
	MLiwInterface* interface ;
	TInt32 btstatus ;
	TInt 					iResult;	
};

CTestAsync* CTestAsync::NewL()
	{
	CTestAsync* self = new(ELeave) CTestAsync();
	self->ConstructL();
	return self;
	}

CTestAsync::~CTestAsync()
	{
	Cancel();
	if(interface)
	interface->Close();
	
	delete iServiceHandler;
	
	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();
	
	if(iWaitSchedular)
		delete iWaitSchedular;
	}

void CTestAsync::ConstructL()
	{
	CActiveScheduler::Add(this);
	iWaitSchedular = new(ELeave) CActiveSchedulerWait();
	}

CTestAsync::CTestAsync() :
CActive(EPriorityStandard),iResult(-1)
	{
	}

void CTestAsync::DoCancel()
	{
	
	}

void CTestAsync::RunL()
	{
	TestFunc();
	}

void CTestAsync::Start()
	{
	
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}

TInt CTestAsync::Result()
	{
	return iResult;
	}

void CTestAsync::TestFunc()
	{
// On Emulator this is not supported.				
#if (! (defined(__WINS__) || defined(__WINSCW__)) )

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
		_LIT(Kconnectivity,"connectivity");
	
		entityname.Set(Kconnectivity);
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
		
		inparam->Reset();
		outparam->Reset();

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
			
			interface->ExecuteCmdL(KSetInfo,*inparam,*outparam);
			{
				pos = 0;
				const TLiwGenericParam* output1 = outparam->FindFirst( pos,KErrorCode );
				TInt32 err3;
				if(output1)
					err3 = output1->Value().AsTInt32();
				else
					User::Leave(KErrGeneral);
				if(err3)
					{
					inparam->Reset();
					outparam->Reset();
					iResult = err3;
					iWaitSchedular->AsyncStop();
					}
			}
			inparam->Reset();
			outparam->Reset();
#endif _SET_BLUETOOTH_SUPPORTED_
			}//err2
		}//err1
		}//interface
	else
		{
		iResult = err;
		iWaitSchedular->AsyncStop();
		}
#else
		iResult = 0;
		iWaitSchedular->AsyncStop();

#endif
	return ;
	}

TInt CTestAsync::HandleNotifyL(TInt /*aCmdId*/,
		            TInt /*aEventId*/,
		            CLiwGenericParamList& aEventParamList,
		            const CLiwGenericParamList& /*aInParamList*/)
	{
		TInt pos = 0 ;
		const TLiwGenericParam* output2 = aEventParamList.FindFirst( pos,KReturnValue );
		
		if(output2)     
			{
			const CLiwMap* Map = output2->Value().AsMap(); 
			if ( Map )
				{
				TLiwVariant err;
				Map->FindL(KStatus,err);
				TInt32 error =err.AsTInt32();
				err.Reset()	;

				if(error == KErrNone)
					{
					TLiwVariant data;
					if(EFalse!=Map->FindL(KStatus,data))
						{
						TInt32 changedBTstatus=data.AsTInt32();

						if(changedBTstatus != (btstatus))
							{
							iResult = KErrNone;
				            CBTEngSettings* BtSettings = CBTEngSettings::NewLC();
				            TInt err3(KErrNone);
				            if( btstatus == EOn)
				                BtSettings->SetPowerState( EBTPowerOn );
				            else if(btstatus == EOff)
				                BtSettings->SetPowerState( EBTPowerOff );

				            CleanupStack::PopAndDestroy(BtSettings);							
							}
						else
							{
							iResult =  KErrGeneral;
							}
						}
					data.Reset();	
					}
				}//map
			}//output
	iWaitSchedular->AsyncStop();
	return KErrNone;
	}


int ReqNotification()
	{
	__UHEAP_MARK;

	CTestAsync* test = CTestAsync::NewL();
	
	test->Start();
	TInt retval =	test->Result();
	delete test;
	__UHEAP_MARKEND;

	return retval;
	}

