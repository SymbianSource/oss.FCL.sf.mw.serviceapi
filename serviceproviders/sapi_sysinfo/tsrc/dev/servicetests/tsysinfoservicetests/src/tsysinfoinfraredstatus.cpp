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



#include "sysinfoservice.h"
#include"entitykeys.h"

#include <ir_sock.h>
#include <e32property.h>

using namespace SysInfo;

class CInfraredTestAsync : public CActive ,public ISystemObserver
{
public:
	static CInfraredTestAsync* NewL();
	~CInfraredTestAsync();
	void Start();
	TInt Result();

	 void HandleResponseL(const TDesC& aEntity,const TDesC& aKey, 
									CSysData* aResponse, TInt32 aTransID, 
									TSysRequest::TRequestType aType, TInt aError=KErrNone);

private:
	void ConstructL();
	CInfraredTestAsync();
	
	virtual void DoCancel();
	virtual void RunL();
	
	
	void TestFunc();

	
	
private:	
	CActiveSchedulerWait* 	iWaitSchedular;
	CSysInfoService*		iSysInfoService;
	TInt infraredStatus ;
	TInt 					iResult;	
};

CInfraredTestAsync* CInfraredTestAsync::NewL()
	{
	CInfraredTestAsync* self = new(ELeave) CInfraredTestAsync();
	self->ConstructL();
	return self;
	}

CInfraredTestAsync::~CInfraredTestAsync()
	{
	Cancel();
	
	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();
	
	if(iSysInfoService)
		delete iSysInfoService;
	
	if(iWaitSchedular)
		delete iWaitSchedular;
	}

void CInfraredTestAsync::ConstructL()
	{
	CActiveScheduler::Add(this);
	iSysInfoService = CSysInfoService::NewL();
	iWaitSchedular = new(ELeave) CActiveSchedulerWait();
	}

CInfraredTestAsync::CInfraredTestAsync() :
CActive(EPriorityStandard),iResult(KErrNone)
	{
	}

void CInfraredTestAsync::DoCancel()
	{

		
	}

void CInfraredTestAsync::RunL()
	{
	TestFunc();
	}

void CInfraredTestAsync::Start()
	{
	
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}

TInt CInfraredTestAsync::Result()
	{
	return iResult;
	}

void CInfraredTestAsync::TestFunc()
	{

	TRAPD(err1,iSysInfoService->GetNotificationL(KConnectivity,KInfraRed,8877,this));
	iResult = err1;
	
	if(err1 == KErrNone)
	{
	CSysData* data1 = NULL;
	
	TRAPD(err2,iSysInfoService->GetInfoL(KConnectivity,KInfraRed,data1));
	iResult =err2;
	TInt newIRstatus;
	if(err2 == KErrNone)
		{
		infraredStatus = ((CStatus*)data1)->Status();
		CStatus* data2 = NULL;
		
		if(infraredStatus == EUnknown || infraredStatus ==EOff )
			{
			infraredStatus = EOff;
			newIRstatus = EOn;
			data2 = CStatus::NewL(newIRstatus);
			}
		else
			{
			newIRstatus = EOff;
			data2 = CStatus::NewL(newIRstatus);
			}
//		TRAPD(err3,iSysInfoService->SetInfoL(KConnectivity,KInfraRed,data2));
		 TInt err3(KErrNone);
        if(newIRstatus == EOn)
            err3= RProperty::Set(KIrdaPropertyCategory,
                                KIrdaStatus,TIrdaStatusCodes::EIrLoaded);
        else if(newIRstatus == EOff)
            err3 = RProperty::Set(KIrdaPropertyCategory,
                                KIrdaStatus,TIrdaStatusCodes::EIrUnloaded);
        else
            err3 = KErrArgument;		
		
		iResult =err3; 

		delete  data2;
		}
	delete  data1;

	}
	return ;
	}

void CInfraredTestAsync::HandleResponseL(const TDesC& /*aEntity*/,const TDesC& /*aKey*/, 
									CSysData* aResponse, TInt32 /*aTransID*/, 
									TSysRequest::TRequestType /*aType*/,TInt aError)
	{
		if(aError == KErrNone) 
			{
			const CStatus* data1 = (CStatus*)aResponse;
			TInt newIRstatus;
			if((data1->Status() ) == (!infraredStatus) )
				{
				iResult = KErrNone;
				
				if((data1->Status()) == EOn)
					{
					newIRstatus = EOff;
					}
				else
					{
					newIRstatus = EOn;
					}
					
//					TRAPD(err3,iSysInfoService->SetInfoL(KConnectivity,KInfraRed,data2));
		        TInt err3(KErrNone);
				if(newIRstatus == EOn)
		            err3= RProperty::Set(KIrdaPropertyCategory,
		                                KIrdaStatus,TIrdaStatusCodes::EIrLoaded);
		        else if(newIRstatus == EOff)
		            err3 = RProperty::Set(KIrdaPropertyCategory,
		                                KIrdaStatus,TIrdaStatusCodes::EIrUnloaded);
		        else
		            err3 = KErrArgument;
		        iResult = err3;
				}
			else
				{
				iResult = -1;
				}
		delete aResponse;
		data1 = NULL;
			}
	iWaitSchedular->AsyncStop();
	}


int IRNotification(int, char**)
	{
	__UHEAP_MARK;
	CInfraredTestAsync* test = CInfraredTestAsync::NewL();
	
	test->Start();
	TInt retval =	test->Result();
	delete test;
	
	__UHEAP_MARKEND;
	return retval;
	}

