/*
* Copyright (c) 2005-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  CLandmarkCmdGetLandmarks class
 *
*/
#include <EPos_CPosLmOperation.h>
#include <EPos_CPosLandmarkSearch.h>
#include <EPos_CPosLandmarkDatabase.h>
#include <EPos_CPosLandmarkEncoder.h>
#include <EPos_CPosLandmarkParser.h>
#include <f32file.h>
#include "clandmarkoperation.h"
#include "mlandmarkobserver.h"
#include "clandmarkmanagehandlers.h"
#include "clandmarkmanageobjects.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CLandmarkOperation::NewL( MLandmarkObserver* aObserver, CLandmarkManageObjects* aManageObjects )
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CLandmarkOperation* CLandmarkOperation::NewL(
		MLandmarkObserver* aObserver, CLandmarkManageObjects* aManageObjects)
	{
	CLandmarkOperation* self =
			CLandmarkOperation::NewLC(aObserver, aManageObjects);
	CleanupStack::Pop(self);
	return self;
	}

// -----------------------------------------------------------------------------
// CLandmarkOperation::NewLC( MLandmarkObserver* aObserver, CLandmarkManageObjects* aManageObjects )
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CLandmarkOperation* CLandmarkOperation::NewLC(
		MLandmarkObserver* aObserver, CLandmarkManageObjects* aManageObjects)
	{
	CLandmarkOperation* self =
			new (ELeave) CLandmarkOperation(aObserver,
					aManageObjects);
	CleanupStack::PushL(self);
	return self;
	}

// -----------------------------------------------------------------------------
// CLandmarkOperation::CLandmarkOperation( MLandmarkObserver* aObserver, CLandmarkManageObjects* aManageObjects )
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CLandmarkOperation::CLandmarkOperation(
		MLandmarkObserver* aObserver, CLandmarkManageObjects* aManageObjects) :
	CActive(EPriorityNormal), iObserver(aObserver), iManageObjects(
			aManageObjects)
	{
	CActiveScheduler::Add(this);
	}

// -----------------------------------------------------------------------------
// CLandmarkOperation::~CLandmarkOperation()
// Destructor.
// -----------------------------------------------------------------------------
//
CLandmarkOperation::~CLandmarkOperation()
	{
	Cancel();
	delete iOperation;
	delete iExportBuffer;
	delete iEncoder;
	delete iParser;
	delete iDestinationFile;
	}

// -----------------------------------------------------------------------------
// CLandmarkOperation::StartL( CLandmarkHandler* aHandle, TInt32 aTransactionId, CLandmarkFilter* aFilter )
// Start asynchronous operation.
// -----------------------------------------------------------------------------
//
void CLandmarkOperation::LinkL(TInt32 aTransactionId,
		TPosLmItemId aCategoryId, RArray<TPosLmItemId>& aLandmarkIdArray,
		CPosLmCategoryManager* aCategoryManager)
	{
	iOperationType = EOrganise;
	iTransactionId = aTransactionId;
	iOperation = aCategoryManager->AddCategoryToLandmarksL(aCategoryId,
			aLandmarkIdArray);
	NextStep();
	}

void CLandmarkOperation::UnLinkL(TInt32 aTransactionId,
		TPosLmItemId aCategoryId, RArray<TPosLmItemId>& aLandmarkIdArray,
		CPosLmCategoryManager* aCategoryManager)
	{
	iOperationType = EOrganise;
	iTransactionId = aTransactionId;
	iOperation = aCategoryManager->RemoveCategoryFromLandmarksL(
			aCategoryId, aLandmarkIdArray);
	NextStep();
	}

void CLandmarkOperation::ImportL(TInt32 aTransactionId, CLandmarkHandler* aHandle, 
			CPosLandmarkParser& aLandmarkParser)
	{
	iHandle = aHandle;
	iOperationType = EImport;
	iTransactionId = aTransactionId;
	iParser = &aLandmarkParser;
	CPosLandmarkDatabase* db = iHandle->LandmarkDatabaseHandle();
	iOperation = db->ImportLandmarksL(aLandmarkParser,
			CPosLandmarkDatabase::EDefaultOptions);
	NextStep();
	}

void CLandmarkOperation::ExportL(TInt32 aTransactionId, CPosLandmarkDatabase* aDatabase, 
			CPosLandmarkEncoder& aLandmarkEncoder,
			const RArray<TPosLmItemId>& aLandmarkIdArray,
			const TDesC& aDestinationFile)
	{
	iOperationType = EExport;
	iTransactionId = aTransactionId;
	iEncoder = &aLandmarkEncoder;
	iDestinationFile= aDestinationFile.AllocL();
	iExportBuffer = iEncoder->SetUseOutputBufferL();
	iOperation = aDatabase->ExportLandmarksL(aLandmarkEncoder,aLandmarkIdArray,
			CPosLandmarkDatabase::EIncludeCategories);
	NextStep();
	}

// -----------------------------------------------------------------------------
// CLandmarkOperation::NextStep()
// Execute the next step.
// -----------------------------------------------------------------------------
//
void CLandmarkOperation::NextStep()
	{
	iOperation->NextStep(iStatus, iProgress);
	SetActive();
	}

// -----------------------------------------------------------------------------
// CLandmarkOperation::RunL()
// Notify Observer on completion of the asynchronous call.
// -----------------------------------------------------------------------------
//
void CLandmarkOperation::RunL()
	{
	if (iStatus == KPosLmOperationNotComplete)
		{
		NextStep();
		}
	else
		{
		if( iOperationType == EImport)
			{
			CPosLmItemIterator* iterator=  NULL;
			CPosLandmarkDatabase* db = iHandle->LandmarkDatabaseHandle ( );
			iterator = db->ImportedLandmarksIteratorL(iOperation);
			CleanupStack::PushL (iterator );
			TRAP_IGNORE(iObserver->HandleLandmarkItemsL(iterator,iTransactionId,KErrNone,iHandle));
			CleanupStack::Pop (iterator );
			}
		else if( iOperationType == EExport)
			{
			ExecuteAndDeleteLD (iEncoder->FinalizeEncodingL ( ) );
			//Write to file			
			RFs fs;
			User::LeaveIfError(fs.Connect());
			CleanupClosePushL(fs);
			RFile file;
			CleanupClosePushL(file);
			User::LeaveIfError(file.Create(fs, *iDestinationFile, 
					EFileShareExclusive | EFileStreamText | EFileWrite));
			TInt size = iExportBuffer->Size();
			for( TInt i = 0; i < size; ++i )
				{
				file.Write(i,iExportBuffer->Ptr(i));
				}
			CleanupStack::PopAndDestroy(&file);
			CleanupStack::PopAndDestroy(&fs);
			TRAP_IGNORE(iObserver->HandleItemsL(iTransactionId,iStatus.Int ( )));
			}
		else
			{
			TRAP_IGNORE(iObserver->HandleItemsL(iTransactionId,iStatus.Int ( )));
			}
		//set active garbage collector
		if (!iManageObjects->IsActive())
			{
			iManageObjects->Start();
			}
		}
	}

// -----------------------------------------------------------------------------
// CLandmarkOperation::DoCancel()
// Cancel asynchronous call.
// -----------------------------------------------------------------------------
//
void CLandmarkOperation::DoCancel()
	{
	if (iOperation)
		{
		delete iOperation;
		iOperation = NULL;
		}
	}

TInt CLandmarkOperation::RunError( TInt aError )
	{
	if( iOperationType == EImport)
		{
		TRAP_IGNORE(iObserver->HandleLandmarkItemsL(NULL,iTransactionId,aError,NULL));
		}
	else
		{
		TRAP_IGNORE(iObserver->HandleItemsL(iTransactionId,aError));
		}
	if ( !iManageObjects->IsActive() )
		{
		iManageObjects->Start ( );
		}
	return KErrNone;
	}
//end of file


