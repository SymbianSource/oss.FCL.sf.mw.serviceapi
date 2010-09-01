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

 
// STLport regression testsuite component.
// To compile as a separate example, please #define MAIN.

#include <e32base.h>
////#include <senduiconsts.h>
#include "messagingservice.h"
#include <badesca.h>

#include <f32file.h>
#include "messageheader.h"
#ifdef MAIN
#define ReqNotification main
#endif

/**
 * Callback class for asynchronous SAPI message header
*/	
class CMsgCallbackHeader : public CMsgCallbackBase
	{
	public:
		
		static CMsgCallbackHeader* NewL(CActiveSchedulerWait* aWaitSchedular, CMessagingService*s);
		
		virtual ~CMsgCallbackHeader(){}
		
		virtual void NotifyResultL(TInt aErrCode, TAny* aResult);
		
	private:
	
 		CMsgCallbackHeader(CActiveSchedulerWait* aWaitSchedular, CMessagingService*s):iWaitSchedular(aWaitSchedular), iservice(s){ }

		CActiveSchedulerWait* 	iWaitSchedular;
		CMessagingService* 	iservice;
	};

class CTestAsync : public CActive
{
public:
	static CTestAsync* NewL();
	~CTestAsync();
	void Start();
	TInt Result();
	void CancelNotification()
		{
		iMessagingService->CancelNotification(ENewMessage, NULL);
		iCallBack = NULL;
		}
	
private:
	void ConstructL();
	CTestAsync();
	
	virtual void DoCancel();
	virtual void RunL();
	
	
	void TestFunc();

	
	
private:	
	CActiveSchedulerWait* 	iWaitSchedular;
	CMessagingService*		iMessagingService;
	CMsgCallbackHeader*		iCallBack;
	TInt 					iResult;	
};

// ---------------------------------------------------------------------------
// Gives the result of asynchronous SAPI
// ---------------------------------------------------------------------------
//
void CMsgCallbackHeader::NotifyResultL( TInt aErrCode, TAny* aResult )
	{
	CMessageHeader* header = (CMessageHeader*)aResult;

	CFilterParamInfo* filterParams = CFilterParamInfo::NewL();

	filterParams->SetMessageIdFilter( header->MessageId() );
	
	CMsvEntrySelection* entrySelection = NULL;
	
	iservice->GetIdListL( filterParams, 0, NULL, entrySelection );
	
	if ( entrySelection && ( entrySelection->Count() > 0 ))
		{
		TInt result = KErrNone;
		}
		
	entrySelection->Reset();
	delete entrySelection;
	delete filterParams;
	
	iWaitSchedular->AsyncStop();
	
	
	}

CMsgCallbackHeader* CMsgCallbackHeader::NewL(CActiveSchedulerWait* aWaitSchedular, CMessagingService* s)
	{
	CMsgCallbackHeader* self = new (ELeave) CMsgCallbackHeader(aWaitSchedular, s);
	return self;
	}

CTestAsync* CTestAsync::NewL()
	{
	CTestAsync* self = new(ELeave) CTestAsync();
	self->ConstructL();
	return self;
	}

CTestAsync::~CTestAsync()
	{
	Cancel();
	
	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();
	
	if(iMessagingService)
		delete iMessagingService;
	
	if(iWaitSchedular)
		delete iWaitSchedular;
	}

void CTestAsync::ConstructL()
	{
	CActiveScheduler::Add(this);
	iMessagingService = CMessagingService::NewL();
	iWaitSchedular = new(ELeave) CActiveSchedulerWait();
	}

CTestAsync::CTestAsync() :
CActive(EPriorityStandard)
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
	iCallBack = CMsgCallbackHeader::NewL(iWaitSchedular, iMessagingService);
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
  	   
    TRAPD(err, iMessagingService->RequestNotification(ENewMessage, iCallBack));
 	}

int ReqNotification(int, char**)
	{
	__UHEAP_MARK;
	CTestAsync* test = CTestAsync::NewL();
	
	test->Start();
	
	test->CancelNotification();
	
	delete test;
	__UHEAP_MARKEND;
	return KErrNone;
	

  
//	return 0;
	}
