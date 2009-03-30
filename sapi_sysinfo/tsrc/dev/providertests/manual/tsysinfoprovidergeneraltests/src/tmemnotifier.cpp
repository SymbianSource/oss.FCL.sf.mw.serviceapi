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


#include <e32std.h>
#include <LiwServiceHandler.h>

#include "tsysinfoprovidergeneraltests.h"
#include "tmemnotifier.h"
#include "entitykeys.h"
#include "watchtimer.h"

#include "entitykeys.h"
#include "sysinfoaiwparams.hrh"

using namespace LIW ;
using namespace SysInfo;
using namespace sysinfoaiwparams;


CTestMemNotification* CTestMemNotification::NewL(CStifLogger* aLog)
	{
	CTestMemNotification* self = new(ELeave) CTestMemNotification(aLog);
	self->ConstructL();
	return self;
	}

CTestMemNotification::~CTestMemNotification()
	{
	Cancel();
	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();
	
	delete	iTimer;
	iInParamList->Reset();
	iOutParamList->Reset();
	iInterface->Close();
	delete iServiceHandler;
	delete iWaitSchedular;
	}

void CTestMemNotification::ConstructL()
	{
	iWaitSchedular  = new(ELeave) CActiveSchedulerWait();
	iTimer			= CWatchTimer::NewL(EPriorityNormal,this);
	CreateInterfaceL();
	CActiveScheduler::Add(this);
	}

CTestMemNotification::CTestMemNotification(CStifLogger* aLog) :
				CActive(EPriorityStandard),iLog(aLog)
	{
	}

void CTestMemNotification::DoCancel()
	{
	//TRAPD(err1,iSysInfoService->GetInfoL(req1));
	}

void CTestMemNotification::RunL()
	{
	TestFuncL();
	}

void CTestMemNotification::Start()
	{
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}

TInt CTestMemNotification::Result()
	{
	return iResult;
	}

void CTestMemNotification::TestFuncL()
	{
	TInt RetVal(PASS);
	TInt32 Err;
	
	iInParamList->AppendL(TLiwGenericParam(KEntity,TLiwVariant(KMemory)));
	iInParamList->AppendL(TLiwGenericParam(KKey,TLiwVariant(KMemoryCard)));

	iInterface->ExecuteCmdL(KGetNotification,*iInParamList,*iOutParamList,KLiwOptASyncronous,this);
	RetVal |= CheckErrorCode(*iOutParamList,Err);
	if ( Err )
		{
		iLog->Log( _L("GetNotification retured error : %d"),Err );
		User::Leave(Err);
		} 
	
	TInt index=0;
	const TLiwGenericParam* ret_val = iOutParamList->FindFirst(index,KTransactionId);
	if(!ret_val)
		{
		iLog->Log( _L("Transaction ID not found"));
		User::Leave(FAIL);
		}
	else
		{
		iTransID = ret_val->Value().AsTInt32();
		iLog->Log( _L("Transaction ID: %d"),iTransID);
		}
	
	const TTimeIntervalMicroSeconds32 OneMinute(120000000);
	iTimer->After(OneMinute);
	
	return;
	}


TInt CTestMemNotification::HandleNotifyL( TInt aTransID, TInt aEventId,
            CLiwGenericParamList& aEventParamList,
            const CLiwGenericParamList& /*aInParamList*/)
	{
	aEventId=aEventId;
	delete iTimer;
	iTimer = NULL;
	{
	TInt index=0;
	TPtrC entity,key;
	TInt32 status;
	const TLiwGenericParam* ret_val = aEventParamList.FindFirst(index,KReturnValue);
	if(!ret_val)
		{
		iLog->Log( _L("Return value parameter not found"));
		User::Leave(FAIL);
		}
	else
		{
		const CLiwMap* outmap = ret_val->Value().AsMap();
		TLiwVariant ventity,vkey,vstatus;
		if( !outmap->FindL(KEntity,ventity) )
			{
			iLog->Log( _L("Entity parameter not found"));
			User::Leave(FAIL);
			}
		if( !outmap->FindL(KKey,vkey) )
			{
			iLog->Log( _L("Key parameter not found"));
			User::Leave(FAIL);
			}
		
		if( !outmap->FindL(KStatus,vstatus) )
			{
			iLog->Log( _L("Key parameter not found"));
			User::Leave(FAIL);
			}
		ventity.Get(entity);
		vkey.Get(key);
		status = vstatus.AsTInt32();

//		((CLiwMap)outmap)->DecRef();	
		
		if( !(entity.Compare(KMemory) || key.Compare(KMemoryCard)) )
			{
			if(!(aTransID == iTransID))
				{
				iLog->Log(_L("Incorrect TransactionID: %d"),aTransID);				
				iResult |= FAIL;
				}

			iLog->Log(_L("Memoty Card Notification Notification.."));
			if(status)
				iLog->Log(_L("Memory Card Inserted.."));
			else
				iLog->Log(_L("Memory Card Removed.."));
			
			iResult |= PASS;		
			}

		ventity.Reset();
		vkey.Reset();
		}
	}

	iResult |= PASS;
	iWaitSchedular->AsyncStop();
	return KErrNone;
	}

void CTestMemNotification::HandleTimeOut()
{
	iLog->Log(_L("TimeOut reached. Memorycard not inserted.."));
//	iSysInfoService->Cancel(1);
	iResult = FAIL;
	iWaitSchedular->AsyncStop();
}

void CTestMemNotification::CreateInterfaceL() 
	{
    iServiceHandler = CLiwServiceHandler::NewL();
    CleanupStack::PushL(iServiceHandler);

    iInParamList = &(iServiceHandler->InParamListL());
    iOutParamList = &(iServiceHandler->OutParamListL());
      
	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1,KIDataSource,KService);
	CleanupStack::PushL(crit);
	crit->SetServiceClass(TUid::Uid(KLiwClassBase));
	RCriteriaArray a;
	CleanupClosePushL(a);
	a.AppendL(crit);
	iServiceHandler->AttachL(a);
	iServiceHandler->ExecuteServiceCmdL(*crit,*iInParamList,*iOutParamList);
		
	TInt Index = 0;
	const TLiwGenericParam* param = iOutParamList->FindFirst(Index,KIDataSource);
	if(!param)
		{
		iLog->Log( _L("Interface Not found "));
		User::Leave(KErrGeneral);
		}
		
	iInterface = param->Value().AsInterface();
	CleanupStack::PopAndDestroy(&a);	
	CleanupStack::PopAndDestroy (crit);
	
  	CleanupStack::Pop (iServiceHandler); 
  	}	

TInt CTestMemNotification::CheckErrorCode( const CLiwGenericParamList& aOutList, TInt32 &aError )
	{
	TInt Index = 0;
	const TLiwGenericParam* errcode = aOutList.FindFirst(Index,KErrorCode);
	if ( KErrNotFound == Index )
		{
		iLog->Log( _L("ErrorCode not found in output ArgList") );
		return FAIL;
		}
	else
		errcode->Value().Get(aError);
	return PASS;
	}
//End of file.


