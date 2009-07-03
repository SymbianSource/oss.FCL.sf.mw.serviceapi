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

#include <epos_cposlandmarkparser.h> 
#include <epos_cposlandmarkencoder.h> 
#include <lbsposition.h> 
#include <EPos_CPosLmTextCriteria.h>
#include <epos_cposlandmarkdatabase.h>
#include <epos_cposlmitemiterator.h> 
#include "clandmarkfilter.h"
#include "landmarkservice.h"
#include "CLandmarkAsyncTests.h"

_LIT(KLmName1, "lm1");
_LIT(KLmName2, "lm2");
_LIT(KLmName3, "lm3");
_LIT(KLmName4, "landmark1");
_LIT(KLmName5, "landmark2");
_LIT(KLmName6, "landmark3");

_LIT(KLmSearchString, "lm*");

// -----------------------------------------------------------------------------
// CLandmarkAsyncTests::NewL
// object creation
// -----------------------------------------------------------------------------
//	
CLandmarkAsyncTests* CLandmarkAsyncTests::NewL(CLandmarkAsyncTests::TESTID aTestID)
	{
	CLandmarkAsyncTests* self = new(ELeave)CLandmarkAsyncTests(aTestID);
	self->ConstructL();
	return self;
	}
// -----------------------------------------------------------------------------
// CLandmarkAsyncTests::CLandmarkAsyncTests
// constructor
// -----------------------------------------------------------------------------
//	
CLandmarkAsyncTests::CLandmarkAsyncTests(TESTID aTestID):
CActive(EPriorityStandard),iTestID(aTestID)
	{
	}
// -----------------------------------------------------------------------------
// CLandmarkAsyncTests::~CLandmarkAsyncTests
// destructor
// -----------------------------------------------------------------------------
//	
CLandmarkAsyncTests::~CLandmarkAsyncTests()
	{
	Cancel();
	
	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();
	
	delete iService;
	delete iDefaultLmHandle;
	if(iWaitSchedular)
		delete iWaitSchedular;
	}
// -----------------------------------------------------------------------------
// CLandmarkAsyncTests::ConstructL
// two phase constructor
// -----------------------------------------------------------------------------
//	
void CLandmarkAsyncTests::ConstructL()
	{
	CActiveScheduler::Add(this);

	iDefaultLmHandle	= CPosLandmarkDatabase::OpenL ();
	CleanupStack::PushL(iDefaultLmHandle);
	if (iDefaultLmHandle->IsInitializingNeeded()) 
		ExecuteAndDeleteLD(iDefaultLmHandle->InitializeL());
	
	iService = CLandmarkService::NewL();
    iService->RegisterObserver(this);
    
    CleanupStack::Pop(iDefaultLmHandle);	
	
	iWaitSchedular = new(ELeave) CActiveSchedulerWait();
	}
// -----------------------------------------------------------------------------
// CLandmarkAsyncTests::StartL
// Starts the execution of the ASync test
// -----------------------------------------------------------------------------
//
void CLandmarkAsyncTests::StartL()
	{
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}	
// -----------------------------------------------------------------------------
// CLandmarkAsyncTests::Result
// returns the result of the test
// -----------------------------------------------------------------------------
//
TInt CLandmarkAsyncTests::Result()
	{
	return iResult;
	}

// -----------------------------------------------------------------------------
// CLandmarkAsyncTests::HandleLandmarkItemsL
// MLmObserver observer callback method for async getlist of landmark request.
// -----------------------------------------------------------------------------
//
void CLandmarkAsyncTests::HandleLandmarkItemsL( CPosLmItemIterator* aIterator,
												TInt32 /*aTransactionId*/, 
												TInt aError, const TDesC& /*aDatabaseUri*/)
{
	TPosLmItemId lmID;
	TInt count = 0;
	
	iResult = 0;
	switch ( iTestID )
	{
	case ETEST1:
		while ((lmID = aIterator->NextL()) != KPosLmNullItemId)
	    {
		    CPosLandmark* lm = iDefaultLmHandle->ReadLandmarkLC(lmID);
			TPtrC lmname;
			if ( !lm->GetLandmarkName(lmname) )
			{
				if ( lmname.Compare(KLmName1) || lmname.Compare(KLmName2) || lmname.Compare(KLmName3) )
					count++;
			}
			else
			{
				break;
			}
			
		    CleanupStack::PopAndDestroy(lm);
	    }
	    if ( count != 3 )
	    {
	    	iResult = 1;
	    }
	    break;
	case ETEST2:
		while ((lmID = aIterator->NextL()) != KPosLmNullItemId)
	    {
		    CPosLandmark* lm = iDefaultLmHandle->ReadLandmarkLC(lmID);
			TPtrC lmname;
			if ( !lm->GetLandmarkName(lmname) )
			{
				if ( !lmname.Compare(KLmName1) || !lmname.Compare(KLmName2) || !lmname.Compare(KLmName3) )
					count++;
				if ( !lmname.Compare(KLmName4) || !lmname.Compare(KLmName5) || !lmname.Compare(KLmName6))
					count++;
			}
			else
			{
				break;
			}
			
		    CleanupStack::PopAndDestroy(lm);
	    }
	    if ( count != 6 )
	    {
	    	iResult = 1;
	    }
	    break;
	}
    iResult |= ( !(KErrNone == aError) );

	delete aIterator;
	iWaitSchedular->AsyncStop();
}

// -----------------------------------------------------------------------------
// CLandmarkAsyncTests::HandleCategoryItemsL
// MLmObserver observer callback method for async getlist of categories request.
// -----------------------------------------------------------------------------
//
void CLandmarkAsyncTests::HandleCategoryItemsL( CPosLmItemIterator* /*aIterator*/,
												TInt32 /*aTransactionId*/, 
												TInt /*aError*/, const TDesC& /*aDatabaseUri*/)
{
}
// -----------------------------------------------------------------------------
// CLandmarkAsyncTests::RunL
// Executes specified test 
// -----------------------------------------------------------------------------
//
void CLandmarkAsyncTests::RunL()
{
	switch(iTestID)
	{
		case ETEST1:
			AsyncTestFunc1L();
			break;
		case ETEST2:
			AsyncTestFunc2L();
			break;
	}
}
// -----------------------------------------------------------------------------
// CLandmarkAsyncTests::DoCancel
// Cancels ongoing Async operationby this active object
// -----------------------------------------------------------------------------
//
void CLandmarkAsyncTests::DoCancel()
{

}
// -----------------------------------------------------------------------------
// CLandmarkAsyncTests::AsyncTestFunc1L
// 
// -----------------------------------------------------------------------------
//
void CLandmarkAsyncTests::AsyncTestFunc1L()
{
	   TInt err = 0;
	   TPosLmSortPref SortPref(CPosLandmark::ELandmarkName,TPosLmSortPref:: EAscending);
	   
		CreateLandmarksL ();
	   
		CLandmarkFilter* filter = CLandmarkFilter::NewLC(CLandmarkFilter::ELandmark);
	    
	    CPosLmTextCriteria* crit = CPosLmTextCriteria::NewLC();

		crit->SetTextL(KLmSearchString);
		crit->SetAttributesToSearch  ( CPosLandmark::ELandmarkName );
		
		filter->SetCriteria(crit);
		filter->SetLmSortPref(SortPref);
//		filter->SetIsLandmark(ETrue);
	   
     TInt32 tranId = 0;
	   TRAP (err,iService->GetListL (tranId,*filter));
		CleanupStack::Pop(crit);
	   CleanupStack::PopAndDestroy(filter);
}	
// -----------------------------------------------------------------------------
// CLandmarkAsyncTests::AsyncTestFunc2L
// 
// -----------------------------------------------------------------------------
//
void CLandmarkAsyncTests::AsyncTestFunc2L()
{
	   TInt err = 0;
	   TPosLmSortPref SortPref(CPosLandmark::ELandmarkName,TPosLmSortPref:: EAscending);
	   
		CreateLandmarksL ();
	   
		CLandmarkFilter* filter = CLandmarkFilter::NewLC(CLandmarkFilter::ELandmark);
	    
//		filter->SetCriteria(NULL);
		filter->SetLmSortPref(SortPref);
	   
     TInt32 tranId = 0;
	   TRAP (err,iService->GetListL (tranId,*filter));

	   CleanupStack::PopAndDestroy(1,filter);
}
// -----------------------------------------------------------------------------
// CLandmarkAsyncTests::CreateLandmarksL
// pre condition
// -----------------------------------------------------------------------------
//
void CLandmarkAsyncTests::CreateLandmarksL()
{
	   TLocality pos;
   	   pos.SetCoordinate(45.1122,34.0099);
   	   
	   CPosLandmark* lm = CPosLandmark::NewLC ();
	   lm->SetLandmarkNameL (KLmName1);
	   lm->SetLandmarkDescriptionL (KLmName1);
	   lm->SetPositionL(pos);
       iDefaultLmHandle->AddLandmarkL (*lm);

	   lm->SetLandmarkNameL (KLmName2);
	   lm->SetLandmarkDescriptionL (KLmName2);
	   lm->SetPositionL(pos);
	   iDefaultLmHandle->AddLandmarkL (*lm);

	   lm->SetLandmarkNameL (KLmName3);
	   lm->SetLandmarkDescriptionL (KLmName3);
	   lm->SetPositionL(pos);
	   iDefaultLmHandle->AddLandmarkL (*lm);

	   lm->SetLandmarkNameL (KLmName4);
	   lm->SetLandmarkDescriptionL (KLmName4);
	   lm->SetPositionL(pos);
	   iDefaultLmHandle->AddLandmarkL (*lm);	
	   
	   lm->SetLandmarkNameL (KLmName5);
	   lm->SetLandmarkDescriptionL (KLmName5);
	   lm->SetPositionL(pos);
	   iDefaultLmHandle->AddLandmarkL (*lm);	   

	   lm->SetLandmarkNameL (KLmName6);
	   lm->SetLandmarkDescriptionL (KLmName6);
	   lm->SetPositionL(pos);
	   iDefaultLmHandle->AddLandmarkL (*lm);

		CleanupStack::PopAndDestroy(lm);	
}
