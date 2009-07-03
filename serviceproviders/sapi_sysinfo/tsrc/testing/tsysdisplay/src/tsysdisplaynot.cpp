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
* Description:   Tests battery notifications
*
*/



#include "tsysdisplay.h"
#include "sysinfoservice.h"
#include "entitykeys.h"
#include "tsysdisplaynot.h"

using namespace SysInfo;

CDisplayNot* CDisplayNot::NewL(CStifLogger* aLog, TInt aCmdId)
	{
	CDisplayNot* self = new(ELeave) CDisplayNot(aLog,aCmdId );
	self->ConstructL();
	return self;
	}

CDisplayNot::~CDisplayNot()
	{
	Cancel();
	
	if(iWaitScheduler->IsStarted())
		iWaitScheduler->AsyncStop();
	
	delete iSysInfoService;
	delete iWaitScheduler;
	
	}

void CDisplayNot::ConstructL()
	{
	iSysInfoService = CSysInfoService::NewL();
	iWaitScheduler  = new(ELeave) CActiveSchedulerWait();
	CActiveScheduler::Add(this);
	}

CDisplayNot::CDisplayNot(CStifLogger* aLog, TInt aCmdId)
							 :CActive(EPriorityStandard),
							 iCmdId(aCmdId),	iLog(aLog)
	{
	}

void CDisplayNot::DoCancel()
	{
	}

void CDisplayNot::RunL()
	{
	if(iCmdId == EUnsupported)
		{
		TRAP(iResult,TestFuncL());	
		}
	
	else if(iCmdId == EWrongInputData)
		{
		TRAP(iResult,TestFunc1L());
		}
		
	else if(iCmdId == EWrongKey)
		{
		TRAP(iResult,TestFunc2L());
		}
	iWaitScheduler->AsyncStop();
	}

void CDisplayNot::Start()
	{
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitScheduler->Start();	
	}

TInt CDisplayNot::Result()
	{
	return iResult ;
	}

void CDisplayNot::TestFuncL()
	{
	_LIT(KSample,"Simple") ;
	CStringData* inputData = CStringData::NewL(KSample) ; 
	CleanupStack::PushL(inputData);
	iSysInfoService->GetInfoL(KDisplay,KUserInactivity,1,this,inputData);
	CleanupStack::PopAndDestroy() ;
	}

void CDisplayNot::TestFunc1L()
	{
	_LIT(KSample,"Simple") ;
	CStringData* inputData = CStringData::NewL(KSample) ; 
	CleanupStack::PushL(inputData);
	iSysInfoService->GetNotificationL(KDisplay,KUserInactivity,1,this,inputData);
	CleanupStack::PopAndDestroy() ;
	}



void CDisplayNot::TestFunc2L()
	{
	_LIT(KSample,"Simple") ;
	CStringData* inputData = CStringData::NewL(KSample) ; 
	CleanupStack::PushL(inputData);
	iSysInfoService->GetNotificationL(KDisplay,KSample,1,this,inputData);
	CleanupStack::PopAndDestroy() ;
	}
	
void CDisplayNot::HandleResponseL(const TDesC& /*aEntity*/,const TDesC& /*aKey*/,
	 					CSysData* aOutput, TInt32 /*aTransID*/,TSysRequest::TRequestType /*aType*/, TInt /*aError*/)
	{
	
	delete aOutput ;
	
	}

