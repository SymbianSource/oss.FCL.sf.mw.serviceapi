/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
#include <Stiftestinterface.h>
#include "tcal_changenotify.h"
#include "calendarheader.h"
#include "calendarservice.h"
#include "entryattributes.h"
#include "teststartconsolealarmserver.h"
#include <calchangecallback.h>

_LIT(KTestCal1File         ,"c:testcal1");
_LIT(KTestCal2File         ,"c:testcal2");
_LIT(KCalName         ,"c:Calendar");

class CChangeNotifyTest : public CActive, public MCalCallbackBase 
	{
	
			enum TTestCaseType
				{
				KNotifyAdd =0,
				KNotifyDelete,
				KNotifyUpdate,
				};
	public:
		static CChangeNotifyTest* NewL(TInt& aResult);

		~CChangeNotifyTest();

		void NotifyResultL(TInt aErrCode, TAny* aResult);
			
		void Start(TInt aChange);
		
		void CancelNotification();
	
	private:
		CChangeNotifyTest(TInt& aResult);

		void ConstructL();

		void RunL();

		void DoCancel();
		
		void DoChangesAdd();
		void DoChangesDelete();
		void DoChangesUpdate();
		void DoAddDelete();
		
	
	private:
		CActiveSchedulerWait* iWaitscheduler;

		CCalendarService* iService;
		
		TInt iChange;
		
		TInt& iResult;
	
		TUIDSet* iUidSet;
	};

CChangeNotifyTest* CChangeNotifyTest::NewL(TInt& aResult)
	{
	CChangeNotifyTest* self = new(ELeave) CChangeNotifyTest(aResult);
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
	
	RemoveCalendarFile(iService, KTestCal1File);
	delete iService;
	
	delete iUidSet;
	}

void CChangeNotifyTest::NotifyResultL(TInt aErrCode, TAny* aResult)
	{
	
	
		RArray<TCalChangeEntry>& outputChangeSet = *((RArray<TCalChangeEntry>*)aResult);
	
	TInt value = iChange;
	
	
	
	if(aErrCode != KErrCancel)
	{
		iResult = aErrCode;
		TInt count = outputChangeSet.Count();
		TInt type = outputChangeSet[0].iChangeType;
		switch(iChange)
		{
			case 1 :
				 if(outputChangeSet[0].iChangeType != MCalChangeCallBack2::EChangeAdd)
					iResult = KErrGeneral;
				 break;
				
			case 2 : 
				if(outputChangeSet[0].iChangeType != MCalChangeCallBack2::EChangeDelete)
					iResult = KErrGeneral;
				 break;
				 
			case 3: 
				if(outputChangeSet[0].iChangeType != MCalChangeCallBack2::EChangeModify)
					iResult = KErrGeneral;
				 break;
			case 4 :
				if(outputChangeSet[0].iChangeType != 1)
					iResult = KErrGeneral;
					break;
		
		}
	}
	
	
	
	if(iWaitscheduler->IsStarted())
		iWaitscheduler->AsyncStop();
	
	}
	
void CChangeNotifyTest::Start(TInt aChange)
	{
	iChange = aChange;
	AddCalendarFile(iService, KTestCal1File);
	CCalendarFilter* filter = CCalendarFilter::NewL();
	
	if( aChange == 2 || aChange == 3 || aChange ==4) //in case of change notify or delete notify add an default entry 
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

CChangeNotifyTest::CChangeNotifyTest(TInt& aResult):
	CActive(EPriorityStandard),iUidSet(NULL), iResult(aResult)
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
		if(iChange ==4)
			DoAddDelete();
	
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
	
void CChangeNotifyTest::DoAddDelete()
{
	TUIDSet* uids = NULL;
	TUIDSet* tempLUid = NULL;
	AddAppointment(iService, KTestCal1File, uids);
	delete uids;
	CCalendarFilter* filter = CCalendarFilter::NewL();
	filter->AddGuidL( iUidSet->iGlobalUID->Des() );
	iService->DeleteL( KTestCal1File , filter );
	uids = NULL;
	delete filter;
	
	
}


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctcal_changenotify::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void Ctcal_changenotify::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// Ctcal_changenotify::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt Ctcal_changenotify::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "GetAddNotification", Ctcal_changenotify::GetAddNotification ),
        ENTRY( "GetDeleteNotification", Ctcal_changenotify::GetDeleteNotification ),
        ENTRY( "GetUpdateNotification", Ctcal_changenotify::GetUpdateNotification ),
        ENTRY( "GetAddDeleteNotification", Ctcal_changenotify::GetAddDeleteNotification ),
        
        //ADD NEW ENTRY HERE

        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// Ctcal_changenotify::GetAddNotification
// Example test method function to check notification for add.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_changenotify::GetAddNotification( CStifItemParser& aItem )
    {

    TInt result = KErrNone;
	__UHEAP_MARK;
	TInt cells = User::CountAllocCells();
	CChangeNotifyTest* test = CChangeNotifyTest::NewL(result);
	cells = User::CountAllocCells();
	test->Start(1);
	test->CancelNotification();
	cells = User::CountAllocCells();
	delete test;
	cells = User::CountAllocCells();
	__UHEAP_MARKEND;
	return result;

    }
    
  // -----------------------------------------------------------------------------
// Ctcal_changenotify::GetDeleteNotification
// Example test method function to check notification for update.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_changenotify::GetDeleteNotification( CStifItemParser& aItem )
    {

    TInt result = KErrNone;
	__UHEAP_MARK;
	TInt cells = User::CountAllocCells();
	CChangeNotifyTest* test = CChangeNotifyTest::NewL(result);
	cells = User::CountAllocCells();
	test->Start(2);
	test->CancelNotification();
	cells = User::CountAllocCells();
	delete test;
	cells = User::CountAllocCells();
	__UHEAP_MARKEND;
	return result;

    }
    
    
 // -----------------------------------------------------------------------------
// Ctcal_changenotify::GetUpdateNotification
// Example test method function to check notification for delete.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_changenotify::GetUpdateNotification( CStifItemParser& aItem )
    {

    TInt result = KErrNone;
	__UHEAP_MARK;
	TInt cells = User::CountAllocCells();
	CChangeNotifyTest* test = CChangeNotifyTest::NewL(result);
	cells = User::CountAllocCells();
	test->Start(3);
	test->CancelNotification();
	cells = User::CountAllocCells();
	delete test;
	cells = User::CountAllocCells();
	__UHEAP_MARKEND;
	return result;

    }
    
  // -----------------------------------------------------------------------------
// Ctcal_changenotify::GetAddDeleteNotification
// Example test method function to check notification for add+delete.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_changenotify::GetAddDeleteNotification( CStifItemParser& aItem )
    {

    TInt result = KErrNone;
	__UHEAP_MARK;
	TInt cells = User::CountAllocCells();
	CChangeNotifyTest* test = CChangeNotifyTest::NewL(result);
	cells = User::CountAllocCells();
	test->Start(4);
	test->CancelNotification();
	cells = User::CountAllocCells();
	delete test;
	cells = User::CountAllocCells();
	__UHEAP_MARKEND;
	return result;

    }


// -----------------------------------------------------------------------------
// Ctcal_changenotify::?member_function
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
/*
TInt Ctcal_changenotify::?member_function(
   CItemParser& aItem )
   {

   ?code

   }
*/

// ========================== OTHER EXPORTED FUNCTIONS =========================
// None

//  End of File
