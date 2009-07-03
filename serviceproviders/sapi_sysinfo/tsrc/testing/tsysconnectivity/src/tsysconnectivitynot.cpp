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



#include "tsysconnectivity.h"
#include "entitykeys.h"
#include "tsysconnectivitynot.h"

using namespace SysInfo;

CConnectivityNot* CConnectivityNot::NewL(CStifLogger* aLog, TInt aCmdId)
	{
	CConnectivityNot* self = new(ELeave) CConnectivityNot(aLog,aCmdId );
	self->ConstructL();
	return self;
	}

CConnectivityNot::~CConnectivityNot()
	{
	Cancel();
	
	if(iWaitScheduler->IsStarted())
		iWaitScheduler->AsyncStop();
	
	delete iSysInfoService;
	delete iWaitScheduler;
	
	}

void CConnectivityNot::ConstructL()
	{
	iSysInfoService = CSysInfoService::NewL();
	iWaitScheduler  = new(ELeave) CActiveSchedulerWait();
	CActiveScheduler::Add(this);
	}

CConnectivityNot::CConnectivityNot(CStifLogger* aLog, TInt aCmdId)
							 :CActive(EPriorityStandard),
								 iCmdId(aCmdId),iLog(aLog)
	{
	}

void CConnectivityNot::DoCancel()
	{
	}

void CConnectivityNot::RunL()
	{
	if(iCmdId == EWrongKey)
		{
		TRAP(iResult,TestFuncL());	
		}
	iWaitScheduler->AsyncStop();
	}

void CConnectivityNot::Start()
	{
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitScheduler->Start();	
	}

TInt CConnectivityNot::Result()
	{
	return iResult ;
	}

void CConnectivityNot::TestFuncL()
	{
	iSysInfoService->GetNotificationL(KConnectivity,KUserInactivity,1,this);
	}


	
void CConnectivityNot::HandleResponseL(const TDesC& /*aEntity*/,const TDesC& /*aKey*/,
	 					CSysData* aOutput, TInt32 /*aTransID*/, TSysRequest::TRequestType /*aType*/,TInt /*aError*/)
	{
	
	delete aOutput ;
	
	}

