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



#include <liwcommon.h>
#include<liwservicehandler.h>

#include"tsysinfoprovidernetworktests.h"
#include "sysinfointerface.h"
#include "sysinfoaiwparams.hrh"
#include "tcurrentnetworknotify.h"
#include"entitykeys.h"

using namespace LIW ;
using namespace SysInfo;

using namespace sysinfoaiwparams;	


CCurrentNetNotify* CCurrentNetNotify::NewL(CStifLogger* aLog)
	{
	CCurrentNetNotify* self = new(ELeave) CCurrentNetNotify(aLog);
	self->ConstructL();
	return self;
	}

CCurrentNetNotify::~CCurrentNetNotify()
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

void CCurrentNetNotify::ConstructL()
	{
	CActiveScheduler::Add(this);
	iTimer			= CWatchTimer::NewL(EPriorityNormal,this);

	iWaitSchedular = new(ELeave) CActiveSchedulerWait();
	}

CCurrentNetNotify::CCurrentNetNotify(CStifLogger* aLog) :
CActive(EPriorityStandard),iResult(-1),iLog(aLog)
	{
	}

void CCurrentNetNotify::DoCancel()
	{
	
	//TRAPD(err1,iSysInfoService->GetInfoL(req1));
		
	}

void CCurrentNetNotify::RunL()
	{
	TestFuncL();
	}

void CCurrentNetNotify::Start()
	{
	
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}

TInt CCurrentNetNotify::Result()
	{
	return iResult;
	}

void CCurrentNetNotify::TestFuncL()
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

		keyname.Set(KCurrentNetwork);
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

TInt CCurrentNetNotify::HandleNotifyL(TInt aCmdId,
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

			TLiwVariant networkNameVar;
			Map->FindL(KNetworkName,networkNameVar);
			TPtrC networkName = networkNameVar.AsDes();
			TBuf<50> buf;
			buf.Copy(networkName);
			iLog->Log(buf);
			networkNameVar.Reset();

			TLiwVariant networkStatusVar;
			Map->FindL(KNetworkStatus,networkStatusVar);
			TInt networkStatus = networkStatusVar.AsTInt32();
			buf.Zero();
			buf.AppendNum(networkStatus);
			iLog->Log(buf);
			networkStatusVar.Reset();

			TLiwVariant networkModeVar;
			Map->FindL(sysinfoaiwparams::KNetworkMode,networkModeVar);
			TInt networkMode = networkModeVar.AsTInt32();
			buf.Zero();
			buf.AppendNum(networkMode);
			iLog->Log(buf);
			networkModeVar.Reset();

			TLiwVariant countryCodeVar;
			Map->FindL(KCountryCode,countryCodeVar);
			TPtrC countryCode = countryCodeVar.AsDes();
			buf.Zero();
			buf.Copy(countryCode);
			iLog->Log(buf);
			countryCodeVar.Reset();

			TLiwVariant networkCodeVar;
			Map->FindL(KNetworkCode,networkCodeVar);
			TPtrC networkCode = networkCodeVar.AsDes();
			buf.Zero();
			buf.Copy(networkCode);
			iLog->Log(buf);
			networkCodeVar.Reset();

			TLiwVariant locationStatusVar;
			Map->FindL(KLocationStatus,locationStatusVar);
			TBool locationStatus = locationStatusVar.AsTBool();
			buf.Zero();
			buf.AppendNum(locationStatus);
			iLog->Log(buf);
			locationStatusVar.Reset();

			TLiwVariant locationAreaCodeVar;
			Map->FindL(KAreaCode,locationAreaCodeVar);
			TUint locationAreaCode = locationAreaCodeVar.AsTUint();
			buf.Zero();
			buf.AppendNum(locationAreaCode);
			iLog->Log(buf);
			locationAreaCodeVar.Reset();

			
			TLiwVariant cellIdVar;
			Map->FindL(KCellId,cellIdVar);
			TUint cellId = cellIdVar.AsTUint();
			buf.Zero();
			buf.AppendNum(cellId);
			iLog->Log(buf);
			cellIdVar.Reset();


			}//map
	
		}//output							
	else
		{
		
		iLog->Log( _L("Output data Set to NULL") );
		}
		

	iWaitSchedular->AsyncStop();
	}


void CCurrentNetNotify::HandleTimeOut()
{/*
	iLog->Log(_L("TimeOut reached..."));
	interface->Close();
	iResult = FAIL;
	iWaitSchedular->AsyncStop();
	*/
}
