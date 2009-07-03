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
* Description:  CLandmarkCmdGetCategories class implementation.
 *
*/


#include <epos_cposlmoperation.h>
#include <epos_cposlandmarksearch.h>
#include "clandmarkcmdgetcategories.h"
#include "mlandmarkobserver.h"
#include "clandmarkmanagehandlers.h"
#include "clandmarkfilter.h"
#include "clandmarkmanageobjects.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CLandmarkCmdGetCategories::NewL( MLandmarkObserver* aObserver, CLandmarkManageObjects* aManageObjects )
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CLandmarkCmdGetCategories* CLandmarkCmdGetCategories::NewL(
		MLandmarkObserver* aObserver, CLandmarkManageObjects* aManageObjects )
	{
	CLandmarkCmdGetCategories* self = CLandmarkCmdGetCategories::NewLC (
			aObserver, aManageObjects );
	CleanupStack::Pop ( self );
	return self;
	}

// -----------------------------------------------------------------------------
// CLandmarkCmdGetCategories::NewLC( MLandmarkObserver* aObserver, CLandmarkManageObjects* aManageObjects )
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CLandmarkCmdGetCategories* CLandmarkCmdGetCategories::NewLC(
		MLandmarkObserver* aObserver, CLandmarkManageObjects* aManageObjects )
	{
	CLandmarkCmdGetCategories* self = new (ELeave) CLandmarkCmdGetCategories(aObserver,aManageObjects);
	CleanupStack::PushL ( self );
	return self;
	}

// -----------------------------------------------------------------------------
// CLandmarkCmdGetCategories::CLandmarkCmdGetCategories( MLandmarkObserver* aObserver, CLandmarkManageObjects* aManageObjects )
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CLandmarkCmdGetCategories::CLandmarkCmdGetCategories(
		MLandmarkObserver* aObserver, CLandmarkManageObjects* aManageObjects )
	{
	iObserver = aObserver;
	iManageObjects = aManageObjects;
	CActiveScheduler::Add ( this );
	}

// -----------------------------------------------------------------------------
// CLandmarkCmdGetCategories::~CLandmarkCmdGetCategories()
// Destructor.
// -----------------------------------------------------------------------------
//
CLandmarkCmdGetCategories::~CLandmarkCmdGetCategories( )
	{
	Cancel ( );
	delete iSearchOperation;
	}

// -----------------------------------------------------------------------------
// CLandmarkCmdGetCategories::StartL( CLandmarkHandler* aHandle, TInt32 aTransactionId, CLandmarkFilter* aFilter )
// Start asynchronous operation.
// -----------------------------------------------------------------------------
//
void CLandmarkCmdGetCategories::StartL( CLandmarkHandler* aHandle,
		TInt32 aTransactionId, CLandmarkFilter& aFilter )
	{
	iHandle = aHandle;
	iTransactionId = aTransactionId;
	CPosLandmarkSearch* search = iHandle->LandmarkSearchHandle ( );
	search->SetMaxNumOfMatches (aFilter.MaximumMatches ( ) );
	iSearchOperation = search->StartCategorySearchL (aFilter.Criteria ( ),
			aFilter.CatSortPref ( ), aFilter.PreviousMatches ( ) );
	NextStep ( );
	}

// -----------------------------------------------------------------------------
// CLandmarkCmdGetCategories::NextStep()
// Execute the next step.
// -----------------------------------------------------------------------------
//
void CLandmarkCmdGetCategories::NextStep( )
	{
	iSearchOperation->NextStep (iStatus, iProgress );
	SetActive ( );
	}

// -----------------------------------------------------------------------------
// CLandmarkCmdGetCategories::RunL()
// Notify Observer on completion of the asynchronous call.
// -----------------------------------------------------------------------------
//
void CLandmarkCmdGetCategories::RunL( )
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
		TRAP_IGNORE(iObserver->HandleCategoryItemsL(iterator,iTransactionId,KErrNone,dbUri));
		CleanupStack::Pop (iterator );
		//set active garbage collector
		if ( !iManageObjects->IsActive() )
			{
			iManageObjects->Start ( );
			}
		}
	}

// -----------------------------------------------------------------------------
// CLandmarkCmdGetCategories::DoCancel()
// Cancel asynchronous call.
// -----------------------------------------------------------------------------
//
void CLandmarkCmdGetCategories::DoCancel( )
	{
	if ( iSearchOperation )
		{
		delete iSearchOperation;
		iSearchOperation = NULL;
		}
	}

// -----------------------------------------------------------------------------
// CLandmarkCmdGetCategories::RunError( TInt aError )
// This functions handles a leave occurring in the request completion event handler.
// -----------------------------------------------------------------------------
//
TInt CLandmarkCmdGetCategories::RunError( TInt aError )
	{
	TRAP_IGNORE(iObserver->HandleCategoryItemsL(NULL,iTransactionId,aError,KNullDesC));
	if ( !iManageObjects->IsActive() )
		{
		iManageObjects->Start ( );
		}
	return KErrNone;
	}
//end of file
