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
#include <liwservicehandler.h>

#include "tsysinfoprovidergeneraltests.h"
#include "tcriticalmemnoti.h"
#include "watchtimer.h"

#include "entitykeys.h"
#include "sysinfoaiwparams.hrh"

using namespace LIW ;
using namespace SysInfo;
using namespace sysinfoaiwparams;

_LIT(KDriveSeperator,":\\");
const TInt KMaxDriveLength = 5;

CTCriticalMemNotification* CTCriticalMemNotification::NewL(CStifLogger* aLog,TInt aDrvNo)
	{
	CTCriticalMemNotification* self = new(ELeave) CTCriticalMemNotification(aLog,aDrvNo);
	self->ConstructL();
	return self;
	}

CTCriticalMemNotification::~CTCriticalMemNotification()
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

void CTCriticalMemNotification::ConstructL()
	{
	iWaitSchedular  = new(ELeave) CActiveSchedulerWait();
	iTimer			= CWatchTimer::NewL(EPriorityNormal,this);
	CreateInterfaceL();
	CActiveScheduler::Add(this);
	}

CTCriticalMemNotification::CTCriticalMemNotification(CStifLogger* aLog,TInt aDrvNo) :
				CActive(EPriorityStandard),iLog(aLog),iDrvNo(aDrvNo)
	{
	}

void CTCriticalMemNotification::DoCancel()
	{
	//TRAPD(err1,iSysInfoService->GetInfoL(req1));
	}

void CTCriticalMemNotification::RunL()
	{
	TestFuncL();
	}

void CTCriticalMemNotification::Start()
	{
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}

TInt CTCriticalMemNotification::Result()
	{
	return iResult;
	}

void CTCriticalMemNotification::TestFuncL()
	{
	TInt criticalspace(0);
	TInt32 Err(PASS);
	TInt RetVal(PASS);

//---------------------------------------------------------------------------
	{
	CLiwMap* inputmap = CLiwDefaultMap::NewL();

	TBuf<KMaxDriveLength> drive;
	drive.FillZ();
	drive.Append('A'+iDrvNo);
	drive.Append(KDriveSeperator);

	inputmap->InsertL(KDriveNo,TLiwVariant(drive));

	iInParamList->AppendL(TLiwGenericParam(KEntity,TLiwVariant(KMemory)));
	iInParamList->AppendL(TLiwGenericParam(KKey,TLiwVariant(KDriveInfo)));
	iInParamList->AppendL(TLiwGenericParam(KSysData,TLiwVariant(inputmap)));

	iInterface->ExecuteCmdL(KGetInfo,*iInParamList,*iOutParamList);

	RetVal |= CheckErrorCode(*iOutParamList,Err);
	if ( Err )
		{
		iLog->Log( _L("GetInfo retured error : %d"),Err );
		User::Leave(Err);
		} 
	
	TInt index=0;
	const TLiwGenericParam* ret_val = iOutParamList->FindFirst(index,KReturnValue);
	if(!ret_val)
		{
		iLog->Log( _L("Return value parameter not found"));
		User::Leave(FAIL);
		}
	else
		{
		const CLiwMap* outmap = ret_val->Value().AsMap();
		TLiwVariant info;
		if (outmap->FindL(KFreeSpace,info))
			{
			TLex freespace(info.AsDes());
			TInt64 freespaceval;
			if ( KErrNone != freespace.Val(freespaceval) )
				{
				iLog->Log( _L("Invalid free space string") );
				User::Leave(FAIL);
				}
			iLog->Log( _L("Free Space: %s"),info.AsDes().Ptr() );
			criticalspace = freespaceval/2;
			}
		info.Reset();
		((CLiwMap*)outmap)->DecRef();
		}
	inputmap->DecRef();
	}
	iInParamList->Reset();
	iOutParamList->Reset();

//---------------------------------------------------------------------------
	{
	CLiwMap* inputmap = CLiwDefaultMap::NewL();
	inputmap->InsertL(KCriticalSpace,TLiwVariant((TInt32)criticalspace));

	TBuf<KMaxDriveLength> drive;
	drive.FillZ();
	drive.Append('A'+iDrvNo);
	drive.Append(KDriveSeperator);

	inputmap->InsertL(KDriveNo,TLiwVariant(drive));
	
	iInParamList->AppendL(TLiwGenericParam(KEntity,TLiwVariant(KMemory)));
	iInParamList->AppendL(TLiwGenericParam(KKey,TLiwVariant(KCriticalMemory)));
	iInParamList->AppendL(TLiwGenericParam(KSysData,TLiwVariant(inputmap)));
	iLog->Log( _L("Critical Free Space Set to: %d"),criticalspace );

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
	inputmap->DecRef();
	}
	iInParamList->Reset();
	iOutParamList->Reset();	
	
	const TTimeIntervalMicroSeconds32 OneMinute(120000000);
	iTimer->After(OneMinute);

	return ;
	}

TInt CTCriticalMemNotification::HandleNotifyL( TInt aTransID, TInt aEventId,
            CLiwGenericParamList& aEventParamList,
            const CLiwGenericParamList& /*aInParamList*/)
	{
	aEventId=aEventId;
	delete iTimer;
	iTimer = NULL;
	{
	TInt index=0;
	TPtrC entity,key;
	TPtrC drive;
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
		
		if( !outmap->FindL(KStringData,vstatus) )
			{
			iLog->Log( _L("Drive not found"));
			User::Leave(FAIL);
			}
		ventity.Get(entity);
		vkey.Get(key);

		if ( !vstatus.Get(drive) )
			{
			iLog->Log( _L("Drive not found"));
			User::Leave(FAIL);
			}

		if( !(entity.Compare(KMemory) || key.Compare(KCriticalMemory)) )
			{
			if(!(aTransID == iTransID))
				{
				iLog->Log(_L("Incorrect TransactionID: %d"),aTransID);				
				iResult |= FAIL;
				}

			iLog->Log(_L("CRITICAL MEMORY Notification.."));
			iLog->Log(_L("LOW MEMORY DETECTED ON DRIVE %s"),drive.Ptr());
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

void CTCriticalMemNotification::HandleTimeOut()
{
	iLog->Log(_L("TimeOut reached. LOW MEMORY Notification not detected.."));
//	iSysInfoService->Cancel(1);
	iResult = FAIL;
	iWaitSchedular->AsyncStop();
}

void CTCriticalMemNotification::CreateInterfaceL() 
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

TInt CTCriticalMemNotification::CheckErrorCode( const CLiwGenericParamList& aOutList, TInt32 &aError )
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

