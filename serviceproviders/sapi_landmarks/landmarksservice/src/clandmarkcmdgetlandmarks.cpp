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
* Description:  CLandmarkCmdGetLandmarks class implementation.
 *
*/


#include <EPos_CPosLmOperation.h>
#include <EPos_CPosLandmarkSearch.h>
#include "clandmarkcmdgetlandmarks.h"
#include "mlandmarkobserver.h"
#include "clandmarkmanagehandlers.h"
#include "clandmarkfilter.h"
#include "clandmarkmanageobjects.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CLandmarkCmdGetLandmarks::NewL( MLandmarkObserver* aObserver, CLandmarkManageObjects* aManageObjects )
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CLandmarkCmdGetLandmarks* CLandmarkCmdGetLandmarks::NewL(
		MLandmarkObserver* aObserver, CLandmarkManageObjects* aManageObjects )
	{
	CLandmarkCmdGetLandmarks* self = CLandmarkCmdGetLandmarks::NewLC (
			aObserver, aManageObjects );
	CleanupStack::Pop ( self );
	return self;
	}

// -----------------------------------------------------------------------------
// CLandmarkCmdGetLandmarks::NewLC( MLandmarkObserver* aObserver, CLandmarkManageObjects* aManageObjects )
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CLandmarkCmdGetLandmarks* CLandmarkCmdGetLandmarks::NewLC(
		MLandmarkObserver* aObserver, CLandmarkManageObjects* aManageObjects )
	{
	CLandmarkCmdGetLandmarks* self = new (ELeave) CLandmarkCmdGetLandmarks(aObserver,aManageObjects);
	CleanupStack::PushL ( self );
	return self;
	}

// -----------------------------------------------------------------------------
// CLandmarkCmdGetLandmarks::CLandmarkCmdGetLandmarks( MLandmarkObserver* aObserver, CLandmarkManageObjects* aManageObjects )
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CLandmarkCmdGetLandmarks::CLandmarkCmdGetLandmarks(
		MLandmarkObserver* aObserver, CLandmarkManageObjects* aManageObjects )
	{
	iObserver = aObserver;
	iManageObjects = aManageObjects;
	CActiveScheduler::Add ( this );
	}

// -----------------------------------------------------------------------------
// CLandmarkCmdGetLandmarks::~CLandmarkCmdGetLandmarks()
// Destructor.
// -----------------------------------------------------------------------------
//
CLandmarkCmdGetLandmarks::~CLandmarkCmdGetLandmarks( )
	{
	Cancel ( );
	delete iSearchOperation;
	}

// -----------------------------------------------------------------------------
// CLandmarkCmdGetLandmarks::StartL( CLandmarkHandler* aHandle, TInt32 aTransactionId, CLandmarkFilter* aFilter )
// Start asynchronous operation.
// -----------------------------------------------------------------------------
//
void CLandmarkCmdGetLandmarks::StartL( CLandmarkHandler* aHandle,
		TInt32 aTransactionId, CLandmarkFilter& aFilter )
	{
	iHandle = aHandle;
	iTransactionId = aTransactionId;
	CPosLandmarkSearch* search = iHandle->LandmarkSearchHandle ( );
	search->SetMaxNumOfMatches (aFilter.MaximumMatches ( ) );
	iSearchOperation = search->StartLandmarkSearchL (aFilter.Criteria ( ),
			aFilter.LmSortPref ( ), aFilter.PreviousMatches ( ) );
	NextStep ( );
	}

// -----------------------------------------------------------------------------
// CLandmarkCmdGetLandmarks::NextStep()
// Execute the next step.
// -----------------------------------------------------------------------------
//
void CLandmarkCmdGetLandmarks::NextStep( )
	{
	iSearchOperation->NextStep (iStatus, iProgress );
	SetActive ( );
	}

// -----------------------------------------------------------------------------
// CLandmarkCmdGetLandmarks::RunL()
// Notify Observer on completion of the asynchronous call.
// -----------------------------------------------------------------------------
//
void CLandmarkCmdGetLandmarks::RunL( )
	{
	if ( iStatus == KPosLmOperationNotComplete )
		{
		NextStep ( );
		}
	else
		{
		User::LeaveIfError (iStatus.Int ( ) );
		CPosLmItemIterator* iterator=  NULL;
		CPosLandmarkDatabase* db = iHandle->LandmarkDatabaseHandle ( );
		TPtrC dbUri;
		iHandle->GetDatabaseUri (dbUri );
		CPosLandmarkSearch* search = iHandle->LandmarkSearchHandle ( );
		iterator = search->MatchIteratorL ( );
		CleanupStack::PushL (iterator );
		TRAP_IGNORE(iObserver->HandleLandmarkItemsL(iterator,iTransactionId,KErrNone,dbUri));
		CleanupStack::Pop (iterator );
		//set active garbage collector
		if ( !iManageObjects->IsActive() )
			{
			iManageObjects->Start ( );
			}
		}
	}

// -----------------------------------------------------------------------------
// CLandmarkCmdGetLandmarks::DoCancel()
// Cancel asynchronous call.
// -----------------------------------------------------------------------------
//
void CLandmarkCmdGetLandmarks::DoCancel( )
	{
	if ( iSearchOperation )
		{
		delete iSearchOperation;
		iSearchOperation = NULL;
		}
	}

// -----------------------------------------------------------------------------
// CLandmarkCmdGetLandmarks::RunError( TInt aError )
// This functions handles a leave occurring in the request completion event handler.
// -----------------------------------------------------------------------------
//
TInt CLandmarkCmdGetLandmarks::RunError( TInt aError )
	{
	TRAP_IGNORE(iObserver->HandleLandmarkItemsL(NULL,iTransactionId,aError,KNullDesC));
	if ( !iManageObjects->IsActive() )
		{
		iManageObjects->Start ( );
		}
	return KErrNone;
	}
//End of file
