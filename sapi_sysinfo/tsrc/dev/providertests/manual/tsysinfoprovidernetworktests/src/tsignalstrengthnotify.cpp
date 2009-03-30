/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:   ?Description
*
*/



#include <Liwcommon.h>
#include<LiwServiceHandler.h>

#include"tsysinfoprovidernetworktests.h"
#include "sysinfointerface.h"
#include "sysinfoaiwparams.hrh"
#include "tsingnalstrengthnotify.h"
#include"entitykeys.h"

using namespace LIW ;
using namespace SysInfo;

using namespace sysinfoaiwparams;	



CSignalStrNotify* CSignalStrNotify::NewL(CStifLogger* aLog,TInt Strength)
	{
	CSignalStrNotify* self = new(ELeave) CSignalStrNotify(aLog,Strength);
	self->ConstructL();
	return self;
	}

CSignalStrNotify::~CSignalStrNotify()
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

void CSignalStrNotify::ConstructL()
	{
	CActiveScheduler::Add(this);
	iTimer			= CWatchTimer::NewL(EPriorityNormal,this);

	iWaitSchedular = new(ELeave) CActiveSchedulerWait();
	}

CSignalStrNotify::CSignalStrNotify(CStifLogger* aLog,TInt aStrength) :
CActive(EPriorityStandard),iResult(-1),iLog(aLog),iSignalStrength(aStrength)
	{
	}

void CSignalStrNotify::DoCancel()
	{
	
	//TRAPD(err1,iSysInfoService->GetInfoL(req1));
		
	}

void CSignalStrNotify::RunL()
	{
	TestFuncL();
	}

void CSignalStrNotify::Start()
	{
	
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}

TInt CSignalStrNotify::Result()
	{
	return iResult;
	}

void CSignalStrNotify::TestFuncL()
	{
	const TTimeIntervalMicroSeconds32 OneMinute(6000000000);
	TInt result =KErrNone;	

    TInt32 oldDisplayLang = 0 ,newDisplayLang = 0;
	
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
		
		entityname.Set(KNetwork);
		entity.SetNameAndValueL(KEntity,entityname);

		keyname.Set(KSignalStrength);
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
				iResult = err1;
				}//err1
	
		}//interface
	else
		{
		iLog->Log( _L("API returned error") );
		iResult = err;
		iWaitSchedular->AsyncStop();
		}
		
	iTimer->After(OneMinute);

	return ;
	}

TInt CSignalStrNotify::HandleNotifyL(TInt aCmdId,
		            TInt aEventId,
		            CLiwGenericParamList& aEventParamList,
		            const CLiwGenericParamList& aInParamList)
	{

	TInt pos = 0 ,err =0;
	aEventParamList.FindFirst( pos, KErrorCode );
	if(pos != KErrNotFound)
		{
		if( (aEventParamList)[pos].Value().AsTInt32() != KErrNone )
		err = (TInt)((aEventParamList)[pos].Value().AsTInt32());
		}

    pos = 0 ;
	const TLiwGenericParam* output2 = aEventParamList.FindFirst( pos,KReturnValue );
	if(output2)     
		{
		const CLiwMap* Map = output2->Value().AsMap(); 
		if ( Map )
			{

			TLiwVariant regTypeVar;
			Map->FindL(KStatus,regTypeVar);
			TInt regType = regTypeVar.AsTInt32();
			regTypeVar.Reset();

			TBuf<50> buf;
			buf.AppendNum(regType);
			iLog->Log(buf);

			}//map
	
		}//output							
	else
		{
		
		iLog->Log( _L("Output data Set to NULL") );
		}
		

	iWaitSchedular->AsyncStop();
	}


void CSignalStrNotify::HandleTimeOut()
{/*
	iLog->Log(_L("TimeOut reached..."));
	interface->Close();
	iResult = FAIL;
	iWaitSchedular->AsyncStop();
	*/
}
