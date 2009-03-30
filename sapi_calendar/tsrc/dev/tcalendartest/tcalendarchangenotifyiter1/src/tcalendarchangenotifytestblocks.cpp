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




// INCLUDE FILES
#include <e32svr.h>
#include <StifParser.h>
//#include <SAPI_TEST\testprg.h>
#include <Stiftestinterface.h>
#include "calendarheader.h"
#include "calendarservice.h"
#include "entryattributes.h"

#include "teststartconsolealarmserver.h"
#include "tcalendarchangenotifytest.h"


_LIT(KTestCal1File                ,"C:getlistcal1");
_LIT(KTestCal2File                ,"C:getlistcal2");




class CChangeNotifyTest : public CActive, public MCalCallbackBase 
	{
	public:
		static CChangeNotifyTest* NewL();

		~CChangeNotifyTest();

		void NotifyResultL(TInt aErrCode, TAny* aResult);
			
		void Start(TInt aChange);
		
		void CancelNotification();
	
	private:
		CChangeNotifyTest();

		void ConstructL();

		void RunL();

		void DoCancel();
		
		void DoChangesAdd();
		void DoChangesDelete();
		void DoChangesUpdate();
	
	private:
		CActiveSchedulerWait* iWaitscheduler;

		CCalendarService* iService;
		
		TInt iChange;
	
		TUIDSet* iUidSet;
	};

CChangeNotifyTest* CChangeNotifyTest::NewL()
	{
	CChangeNotifyTest* self = new(ELeave) CChangeNotifyTest;
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;	
	}

CChangeNotifyTest::~CChangeNotifyTest()
	{
	Cancel();
	
	if(iWaitscheduler->IsStarted())
		iWaitscheduler->AsyncStop();
	
	delete iWaitscheduler;
	
	delete iService;
	
	delete iUidSet;
	}

void CChangeNotifyTest::NotifyResultL(TInt aErrCode, TAny* aResult)
	{
	if(iWaitscheduler->IsStarted())
		iWaitscheduler->AsyncStop();
	}
	
void CChangeNotifyTest::Start(TInt aChange)
	{
	iChange = aChange;
	AddCalendarFile(iService, KTestCal1File);
	CCalendarFilter* filter = CCalendarFilter::NewL();
	
	if( aChange == 2 || aChange == 3 ) //in case of change notify or delete notify add an default entry 
		{							   //and then do deletion/Change	
		AddAppointment(iService, KTestCal1File, iUidSet);
		filter->AddLocalUid(345);
		filter->AddLocalUid(346);
		filter->AddLocalUid( iUidSet->iLocalUID );
		}
	
	
	iService->StartChangeNotifyL( KTestCal1File, filter, this );
	
	delete filter;
	
	SetActive();
	
	TRequestStatus* temp = &iStatus;
	
	User::RequestComplete( temp, KErrNone );
	
	iWaitscheduler->Start();
	
	RemoveCalendarFile(iService, KTestCal1File);
	}

void CChangeNotifyTest::CancelNotification()
	{
	iService->Cancel(0);
	}

CChangeNotifyTest::CChangeNotifyTest():
	CActive(EPriorityStandard),iUidSet(NULL)
	{
	iTransactionId = 0;
	CActiveScheduler::Add(this);
	}

void CChangeNotifyTest::ConstructL()
	{
	iService = CCalendarService::NewL();
	iWaitscheduler = new(ELeave) CActiveSchedulerWait;
	}

void CChangeNotifyTest::RunL()
	{
	TInt err = iStatus.Int();
	
	if(err == KErrNone)
		{
		if(iChange == 1)
			DoChangesAdd();
		if(iChange == 2)
			DoChangesDelete();
		if(iChange == 3)
			DoChangesUpdate();
		}
	else
		{
		
		}	
	}

void CChangeNotifyTest::DoCancel()
	{
	
	}

void CChangeNotifyTest::DoChangesAdd()
	{
	TUIDSet* uids = NULL;
	
	AddAppointment(iService, KTestCal1File, uids);
	
	delete uids;
	}

void CChangeNotifyTest::DoChangesDelete()
	{
	CCalendarFilter* filter = CCalendarFilter::NewL();
	
	filter->AddGuidL( iUidSet->iGlobalUID->Des() );
	
	iService->DeleteL( KTestCal1File , filter );
	
	delete filter;
	}

void CChangeNotifyTest::DoChangesUpdate()
	{
	CEntryAttributes* entry = CEntryAttributes::NewL();
	
	TUIDSet* tempLUid = NULL;
	
	entry->SetLocalUid( iUidSet->iLocalUID );
	
	entry->SetLocationL(_L("Newyorkkkkk"));
	
	iService->AddL( KTestCal1File , entry , tempLUid );
	
	delete tempLUid;
	
	delete entry;
	
	}

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTCalendarChangeNotifyTest::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTCalendarChangeNotifyTest::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CTCalendarChangeNotifyTest::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTCalendarChangeNotifyTest::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        //TRY( "SendMessage",    CTDeleteMessageTest::SendMessage ),
        
        ENTRY( "NotifyAdd",       CTCalendarChangeNotifyTest::NotifyAdd),
        ENTRY( "NotifyDelete",    CTCalendarChangeNotifyTest::NotifyDelete),
        ENTRY( "NotifyUpdate",    CTCalendarChangeNotifyTest::NotifyUpdate),

        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }


TInt  CTCalendarChangeNotifyTest::NotifyAdd(CStifItemParser& /*aItem*/)
	{
	TInt result = KErrNone;
	__UHEAP_MARK;
	TInt cells = User::CountAllocCells();
	CChangeNotifyTest* test = CChangeNotifyTest::NewL();
	cells = User::CountAllocCells();
	test->Start(1);
	test->CancelNotification();
	cells = User::CountAllocCells();
	delete test;
	cells = User::CountAllocCells();
	__UHEAP_MARKEND;
	return result;

    }

TInt  CTCalendarChangeNotifyTest::NotifyDelete(CStifItemParser& /*aItem*/)
	{
	TInt result = KErrNone;
	__UHEAP_MARK;
	TInt cells = User::CountAllocCells();
	CChangeNotifyTest* test = CChangeNotifyTest::NewL();
	cells = User::CountAllocCells();
	test->Start(2);
	test->CancelNotification();
	cells = User::CountAllocCells();
	delete test;
	cells = User::CountAllocCells();
	__UHEAP_MARKEND;
	return result;

    }

TInt  CTCalendarChangeNotifyTest::NotifyUpdate(CStifItemParser& /*aItem*/)
	{
	TInt result = KErrNone;
	__UHEAP_MARK;
	TInt cells = User::CountAllocCells();
	CChangeNotifyTest* test = CChangeNotifyTest::NewL();
	cells = User::CountAllocCells();
	test->Start(3);
	test->CancelNotification();
	cells = User::CountAllocCells();
	delete test;
	cells = User::CountAllocCells();
	__UHEAP_MARKEND;
	return result;

    }


