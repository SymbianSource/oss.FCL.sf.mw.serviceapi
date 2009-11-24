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
#include "tuseractivitynotifier.h"
#include "watchtimer.h"

#include "entitykeys.h"
#include "sysinfoaiwparams.hrh"

using namespace LIW ;
using namespace SysInfo;
using namespace sysinfoaiwparams;

CTestUserActivity* CTestUserActivity::NewL(CStifLogger* aLog,TInt aTimeOut,Test_Type aType)
	{
	CTestUserActivity* self = new(ELeave) CTestUserActivity(aLog,aTimeOut,aType);
	self->ConstructL();
	return self;
	}

CTestUserActivity::~CTestUserActivity()
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

void CTestUserActivity::ConstructL()
	{
	iWaitSchedular  = new(ELeave) CActiveSchedulerWait();
	iTimer			= CWatchTimer::NewL(EPriorityNormal,this);
	CreateInterfaceL();
	CActiveScheduler::Add(this);
	}

CTestUserActivity::CTestUserActivity(CStifLogger* aLog,TInt aTimeOut,
									Test_Type aType) :
								CActive(EPriorityStandard),
								iInactivityTimeOut(aTimeOut),
								iLog(aLog),
								iTestType(aType)
	{
	}

void CTestUserActivity::DoCancel()
	{
	}

void CTestUserActivity::RunL()
	{
	TestFuncL();
	}

void CTestUserActivity::Start()
	{
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}

TInt CTestUserActivity::Result()
	{
	return iResult;
	}

void CTestUserActivity::TestFuncL()
	{
	const TInt OneSec(1000000);
	iTimer->After(OneSec*iInactivityTimeOut*30);

//	REGISTER FOR NOTIFICATION.
//-------------------------------------------------------------------------
	{
	iLog->Log( _L("Issueing Notification request .."));
	TInt RetVal(PASS);
	TInt32 Err;
	
	iOutParamList->Reset();
	iInParamList->Reset();
	
	CLiwMap* inmap = CLiwDefaultMap::NewL();

	iInParamList->AppendL(TLiwGenericParam(KEntity,TLiwVariant(KDisplay)));
	iInParamList->AppendL(TLiwGenericParam(KKey,TLiwVariant(KUserInactivity)));

	inmap->InsertL(KStatus,TLiwVariant((TInt32)iInactivityTimeOut));
	iInParamList->AppendL(TLiwGenericParam(KSysData,TLiwVariant(inmap)));

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
	
	inmap->DecRef();
	}

	iOutParamList->Reset();
	iInParamList->Reset();

	}

TInt CTestUserActivity::HandleNotifyL( TInt aTransID, TInt aEventId,
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
		
		if( !(entity.Compare(KDisplay) || key.Compare(KUserInactivity)) )
			{
			if(!(aTransID == iTransID))
				{
				iLog->Log(_L("Incorrect TransactionID: %d"),aTransID);				
				iResult |= FAIL;
				}

			iLog->Log(_L("UserActivity/Inactivity Notification.."));
			if(status)
				iLog->Log(_L("User Inactivity Detected.."));
			else
				iLog->Log(_L("User Activity Detected.."));
			
			iResult |= PASS;		
			}

		ventity.Reset();
		vkey.Reset();
		
		if (ETESTACTIVITY == iTestType)
			{
			if(status)
				{
				iLog->Log(_L("Waiting for user activity"));
				return KErrNone;
				}
			else
				{
				iLog->Log(_L("User Activity Detected.."));
				}
			iResult |= PASS;
			}
		}
	}

	iResult |= PASS;
	iWaitSchedular->AsyncStop();
	return KErrNone;
	}

void CTestUserActivity::HandleTimeOut()
{
	iLog->Log(_L("TimeOut reached. Inactivity not detected.."));
/*	iSysInfoService->Cancel(1);
*/
	iResult = FAIL;
	iWaitSchedular->AsyncStop();
}

void CTestUserActivity::CreateInterfaceL() 
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

TInt CTestUserActivity::CheckErrorCode( const CLiwGenericParamList& aOutList, TInt32 &aError )
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
