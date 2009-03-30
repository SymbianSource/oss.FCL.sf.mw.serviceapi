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

#include "tsysinfoprovidertests.h"
#include "Tautolocknotifier.h"
#include "watchtimer.h"
#include "entitykeys.h"
#include "sysinfoaiwparams.hrh"

using namespace LIW ;
using namespace SysInfo;
using namespace sysinfoaiwparams;

CAutoLockNotifier* CAutoLockNotifier::NewL(CStifLogger* aLog,TInt aDrvNo)
	{
	CAutoLockNotifier* self = new(ELeave) CAutoLockNotifier(aLog,aDrvNo);
	self->ConstructL();
	return self;
	}

CAutoLockNotifier::~CAutoLockNotifier()
	{
	Cancel();
	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();
	
	delete iTimer;

	iInParamList->Reset();
	iOutParamList->Reset();
	iInterface->Close();
	delete iServiceHandler;

	delete iWaitSchedular;
	}

void CAutoLockNotifier::ConstructL()
	{
	iWaitSchedular  = new(ELeave) CActiveSchedulerWait();
	iTimer			= CWatchTimer::NewL(EPriorityNormal,this);
	CreateInterfaceL();
	CActiveScheduler::Add(this);
	}

CAutoLockNotifier::CAutoLockNotifier(CStifLogger* aLog,TInt aAutoLockTime) :
				CActive(EPriorityStandard),
				iAutoLockTime(aAutoLockTime),
				iRestoreAutoLockTime(15),
				iLog(aLog)
	{
	}

void CAutoLockNotifier::DoCancel()
	{
	//TRAPD(err1,iSysInfoService->GetInfoL(req1));
	}

void CAutoLockNotifier::RunL()
	{
	TestFuncL();
	}

void CAutoLockNotifier::Start()
	{
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}

TInt CAutoLockNotifier::Result()
	{
	return iResult;
	}

void CAutoLockNotifier::TestFuncL()
	{
	TInt RetVal(PASS);
	TInt32 Err;

//	Get autolocktime val
//-------------------------------------------------------------------------
	{
	iLog->Log( _L("Reading initial autolocktime value .."));

	iOutParamList->Reset();
	iInParamList->Reset();

	iInParamList->AppendL(TLiwGenericParam(KEntity,TLiwVariant(KDisplay)));
	iInParamList->AppendL(TLiwGenericParam(KKey,TLiwVariant(KAutoLockTime)));

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
		TLiwVariant autolocktime;
		if( outmap->FindL(KStatus,autolocktime) )
			iRestoreAutoLockTime = autolocktime.AsTInt32();
		((CLiwMap*)outmap)->DecRef();
		}
	iLog->Log( _L("Inital autolocktime to be restored to: %d"),iRestoreAutoLockTime);
	}


//	SET AUTOLOCK TIME.
//-------------------------------------------------------------------------
	{
	CLiwMap* inmap = CLiwDefaultMap::NewL();
	iLog->Log( _L("Seting Autolock time .."));
	
	iOutParamList->Reset();
	iInParamList->Reset();
	
	iInParamList->AppendL(TLiwGenericParam(KEntity,TLiwVariant(KDisplay)));
	iInParamList->AppendL(TLiwGenericParam(KKey,TLiwVariant(KAutoLockTime)));

	inmap->InsertL(KStatus,TLiwVariant((TInt32)iAutoLockTime));
	iInParamList->AppendL(TLiwGenericParam(KSysData,TLiwVariant(inmap)));

	iInterface->ExecuteCmdL(KSetInfo,*iInParamList,*iOutParamList);	
	inmap->Remove(KStatus);	
	RetVal |= CheckErrorCode(*iOutParamList,Err);
	if ( Err )
		{
		iLog->Log( _L("SetInfo retured error : %d"),Err );
		User::Leave(Err);
		} 
	inmap->DecRef();
	}

//	REGISTER FOR NOTIFICATION.
//-------------------------------------------------------------------------
	{
	iLog->Log( _L("Issueing Notification request .."));
	TInt RetVal(PASS);
	TInt32 Err;
	
	iOutParamList->Reset();
	iInParamList->Reset();
	
	iInParamList->AppendL(TLiwGenericParam(KEntity,TLiwVariant(KDisplay)));
	iInParamList->AppendL(TLiwGenericParam(KKey,TLiwVariant(KAutoLockStatus)));

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
		iLog->Log( _L("TRANSACTION ID : %d"),iTransID );
		}
	
	}

	iOutParamList->Reset();
	iInParamList->Reset();

	const TInt OneMin(60000000);
	iTimer->After(OneMin*iAutoLockTime*2);

	}

TInt CAutoLockNotifier::HandleNotifyL( TInt aTransID, TInt aEventId,
            CLiwGenericParamList& aEventParamList,
            const CLiwGenericParamList& )
	{
	aEventId=aEventId;
	delete iTimer;
	iTimer = NULL;

//	RESTORE AUTOLOCK TIME.
//-------------------------------------------------------------------------
	{
	TInt RetVal(PASS);
	TInt32 Err(PASS);
	
	CLiwMap* inmap = CLiwDefaultMap::NewL();
	iLog->Log( _L("Restoring Autolock time to %d"),iRestoreAutoLockTime);
	
	iOutParamList->Reset();
	iInParamList->Reset();
	
	iInParamList->AppendL(TLiwGenericParam(KEntity,TLiwVariant(KDisplay)));
	iInParamList->AppendL(TLiwGenericParam(KKey,TLiwVariant(KAutoLockTime)));

	inmap->InsertL(KStatus,TLiwVariant((TInt32)iRestoreAutoLockTime));
	iInParamList->AppendL(TLiwGenericParam(KSysData,TLiwVariant(inmap)));

	iInterface->ExecuteCmdL(KSetInfo,*iInParamList,*iOutParamList);	
	inmap->Remove(KStatus);	
	RetVal |= CheckErrorCode(*iOutParamList,Err);
	if ( Err )
		{
		iLog->Log( _L("SetInfo retured error : %d"),Err );
		User::Leave(Err);
		} 
	inmap->DecRef();
	}

//	CHECK AUTOLOCK NOTIFICATION.
//-------------------------------------------------------------------------
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
			iLog->Log( _L("Status parameter not found"));
			User::Leave(FAIL);
			}
		ventity.Get(entity);
		vkey.Get(key);
		status = vstatus.AsTInt32();

//		((CLiwMap)outmap)->DecRef();	
		
		if( !(entity.Compare(KDisplay) || key.Compare(KAutoLockStatus)) )
			{
			if(!(aTransID == iTransID))
				{
				iLog->Log(_L("Incorrect TransactionID: %d"),aTransID);				
				iResult |= FAIL;
				}

			iLog->Log(_L("Autolock Notification.."));
			if(status)
				iLog->Log(_L("AutoLock ENABLED"));
			else
				iLog->Log(_L("AutoLock DISABLED"));
			
			iResult |= PASS;		
			}

		ventity.Reset();
		vkey.Reset();
		}
	}

	iWaitSchedular->AsyncStop();
	return KErrNone;
	}

void CAutoLockNotifier::HandleTimeOut()
{
	iLog->Log(_L("TimeOut reached. Auto Lock Not Enabled.."));
//	iSysInfoService->Cancel(1);
//	RESTORE AUTOLOCK TIME.
//-------------------------------------------------------------------------
	{
	TInt RetVal(PASS);
	TInt32 Err(PASS);
	
	CLiwMap* inmap = CLiwDefaultMap::NewL();
	iLog->Log( _L("Restoring Autolock time to %d"),iRestoreAutoLockTime);
	
	iOutParamList->Reset();
	iInParamList->Reset();
	
	iInParamList->AppendL(TLiwGenericParam(KEntity,TLiwVariant(KDisplay)));
	iInParamList->AppendL(TLiwGenericParam(KKey,TLiwVariant(KAutoLockTime)));

	inmap->InsertL(KStatus,TLiwVariant((TInt32)iRestoreAutoLockTime));
	iInParamList->AppendL(TLiwGenericParam(KSysData,TLiwVariant(inmap)));

	iInterface->ExecuteCmdL(KSetInfo,*iInParamList,*iOutParamList);	
	inmap->Remove(KStatus);	
	RetVal |= CheckErrorCode(*iOutParamList,Err);
	if ( Err )
		{
		iLog->Log( _L("SetInfo retured error : %d"),Err );
		User::Leave(Err);
		} 
	inmap->DecRef();
	}

	iResult = FAIL;
	iWaitSchedular->AsyncStop();
}

void CAutoLockNotifier::CreateInterfaceL() 
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

TInt CAutoLockNotifier::CheckErrorCode( const CLiwGenericParamList& aOutList, TInt32 &aError )
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

