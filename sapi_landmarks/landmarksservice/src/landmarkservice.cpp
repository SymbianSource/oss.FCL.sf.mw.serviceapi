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
* Description:  CLandmarkService class implementation
 *
*/


#include <epos_hposlmdatabaseinfo.h>
#include <epos_cposlmdatabasemanager.h>
#include <epos_cposlandmarkparser.h>
#include <epos_cposlandmarkencoder.h>
#include <epos_cposlmitemiterator.h>
#include <epos_cposlandmarkdatabase.h>
#include <epos_cposlandmarksearch.h>
#include <epos_cposlmcategorymanager.h>
#include "landmarkservice.h"
#include "clandmarkcmdgetcategories.h"
#include "clandmarkcmdgetlandmarks.h"
#include "clandmarkmanagehandlers.h"
#include "clandmarkfilter.h"
#include "clandmarkmanageobjects.h"
#include "mlandmarkobserver.h"

//CONSTANTS
_LIT(KProtocolSeparator, "://");
_LIT(KLocalProtocol, "file");

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CLandmarkService::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
EXPORT_C CLandmarkService* CLandmarkService::NewL()
	{
	CLandmarkService* self = CLandmarkService::NewLC();
	CleanupStack::Pop( self );
	return self;
	}

// -----------------------------------------------------------------------------
// CLandmarkService::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
EXPORT_C CLandmarkService* CLandmarkService::NewLC()
	{
	CLandmarkService* self = new (ELeave) CLandmarkService();
	CleanupStack::PushL( self );
	self->ConstructL();
	return self;
	}

// -----------------------------------------------------------------------------
// CLandmarkService::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CLandmarkService::ConstructL( )
	{
#ifdef _DEBUG
	User::LeaveIfError (iLog.Connect ( ) );
	iLog.CreateLog (_L("landmarks"),_L("log.txt"),EFileLoggingModeOverwrite );
	iLog.Write (_L("CLandmarkService::ConstructL()") );
#endif

	iDatabaseManager = CPosLmDatabaseManager::NewL ( );
	iManageHandler = CLandmarkManageHandlers::NewL ( );
	SetActiveL(KNullDesC);
	}

// -----------------------------------------------------------------------------
// CLandmarkService::CLandmarkService()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CLandmarkService::CLandmarkService( )
	{
	}

// -----------------------------------------------------------------------------
// CLandmarkService::~CLandmarkService()
// Destructor.
// -----------------------------------------------------------------------------
//
CLandmarkService::~CLandmarkService( )
	{
#ifdef _DEBUG
	iLog.Write (_L("CLandmarkService::~CLandmarkService()") );
	iLog.CloseLog ( );
	iLog.Close ( );
#endif

	delete iManageObjects;
	delete iDatabaseManager;
	delete iManageHandler;
	ReleaseLandmarkResources ( );
	}

// -----------------------------------------------------------------------------
// CLandmarkService::ImportL( CPosLmItemIterator*&  aIterator,
//    CPosLandmarkParser& aLandmarkParser, TDesC& aDatabaseUri ) const
// Imports landmarks parsed from the input file to the given database.
// -----------------------------------------------------------------------------
//
EXPORT_C void CLandmarkService::ImportL( CPosLmItemIterator*& aIterator,
		CPosLandmarkParser& aLandmarkParser, const TDesC& aDatabaseUri )
	{
#ifdef _DEBUG
	iLog.Write(_L("CLandmarkService::ImportL"));
#endif

	CLandmarkHandler* handler = iManageHandler->GetHandlerL(aDatabaseUri);
	if ( !handler )
		{
		handler = iManageHandler->CreateHandlerL(aDatabaseUri);
		}
	CPosLandmarkDatabase* db = handler->LandmarkDatabaseHandle();
	CPosLmOperation* op = db->ImportLandmarksL(aLandmarkParser,
			CPosLandmarkDatabase::EDefaultOptions);
	CleanupStack::PushL(op);
	op->ExecuteL();
	aIterator = db->ImportedLandmarksIteratorL(op);
	CleanupStack::PopAndDestroy(op);

#ifdef _DEBUG
	iLog.Write(_L("CLandmarkService::ImportL:Exit"));
#endif    
	}

// -----------------------------------------------------------------------------
// CLandmarkService::ExportL( CPosLandmarkEncoder* aLandmarkEncoder,
//  const RArray<TPosLmItemId>& aLandmarkIdArray, const TDesC& aDatabaseUri )
// Exports a list of landmarks from database to a file.
// -----------------------------------------------------------------------------
//
EXPORT_C void CLandmarkService::ExportL( CPosLandmarkEncoder& aLandmarkEncoder,
		const RArray<TPosLmItemId>& aLandmarkIdArray, const TDesC& aDatabaseUri ) const
	{
	CLandmarkHandler* handler = iManageHandler->GetHandlerL(aDatabaseUri);
	if (!handler)
		{
		handler = iManageHandler->CreateHandlerL(aDatabaseUri);
		}
	CPosLandmarkDatabase* db = handler->LandmarkDatabaseHandle();
	ExecuteAndDeleteLD(db->ExportLandmarksL(aLandmarkEncoder,aLandmarkIdArray,
					CPosLandmarkDatabase::EIncludeCategories));
	}

// -----------------------------------------------------------------------------
// CLandmarkService::GetListL(  CPosLmItemIterator*&  aIterator,
//    const CLandmarkFilter* aFilter, const  TDesC&  aDatabaseUri ) const
// Get a list of Landmarks/Categories from  Database synchronously based on filter.
// -----------------------------------------------------------------------------
//
EXPORT_C void CLandmarkService::GetListL( CPosLmItemIterator*& aIterator,
		CLandmarkFilter& aFilter, const TDesC& aDatabaseUri ) const
	{
	CLandmarkHandler* handler = iManageHandler->GetHandlerL(aDatabaseUri);
	if ( !handler )
		{
		handler = iManageHandler->CreateHandlerL(aDatabaseUri);
		}
	CPosLandmarkSearch* search = handler->LandmarkSearchHandle();
	search->SetMaxNumOfMatches(aFilter.MaximumMatches());
	if ( aFilter.IsLandmark() )
		{
		ExecuteAndDeleteLD(search->StartLandmarkSearchL(aFilter.Criteria(),
						aFilter.LmSortPref(),aFilter.PreviousMatches()));
		}
	else
		{
		ExecuteAndDeleteLD(search->StartCategorySearchL(aFilter.Criteria(),
						aFilter.CatSortPref(),aFilter.PreviousMatches()));
		}
	aIterator = search->MatchIteratorL();
	}

// -----------------------------------------------------------------------------
// CLandmarkService::GetListL( CDesCArray*& aDatabaseList,
//    const TDesC& aProtocol ) const
// Get a list of Landmark databases.
// -----------------------------------------------------------------------------
//
EXPORT_C void CLandmarkService::GetListL (CDesCArray*& aDatabaseList,
		const TDesC& aProtocol) const
	{
	if ( aProtocol != KNullDesC )
		{
		aDatabaseList = iDatabaseManager->ListDatabasesLC(aProtocol);
		}
	else
		{
		aDatabaseList = iDatabaseManager->ListDatabasesLC();
		}
	CleanupStack::Pop(aDatabaseList);
	}

// -----------------------------------------------------------------------------
// CLandmarkService::GetListL( TInt32 aTransactionId,
//    CLandmarkFilter* aFilter,const TDesC & aDatabaseUri )
// Get a list of Landmarks/catgeories from  Database asynchronously based on filter.
// -----------------------------------------------------------------------------
//
EXPORT_C void CLandmarkService::GetListL( TInt32 aTransactionId,
		CLandmarkFilter& aFilter, const TDesC& aDatabaseUri )
	{
#ifdef _DEBUG
	iLog.Write(_L("CLandmarkService::GetListL: Landmark: Async"));
#endif

	CLandmarkHandler* handler = iManageHandler->GetHandlerL(aDatabaseUri);
	if ( !handler )
		{
		handler = iManageHandler->CreateHandlerL(aDatabaseUri);
		}

	//Leave if observer has not been set for the async call.
	if ( !iObserver )
		{
		User::Leave(KErrGeneral);
		}

	if ( !iManageObjects )
		{
		iManageObjects = CLandmarkManageObjects::NewL();
		}

	if ( aFilter.IsLandmark() )
		{
		CLandmarkCmdBase* getLm = CLandmarkCmdGetLandmarks::NewLC(iObserver,
				iManageObjects);
		getLm->StartL(handler,aTransactionId,aFilter);
		iManageObjects->AppendL(getLm);
		CleanupStack::Pop(getLm);
#ifdef _DEBUG
		iLog.Write(_L("CLandmarkService::GetListL: Landmark: Async: Exit"));
#endif
		}
	else
		{
		CLandmarkCmdBase* getCat = CLandmarkCmdGetCategories::NewLC(iObserver,
				iManageObjects);
		getCat->StartL(handler,aTransactionId,aFilter);
		iManageObjects->AppendL(getCat);
		CleanupStack::Pop(getCat);
#ifdef _DEBUG
		iLog.Write(_L("CLandmarkService::GetListL: Category: Async: Exit"));
#endif
		}
	}

// -----------------------------------------------------------------------------
// CLandmarkService::AddItemL( CPosLandmark& aLandmark,const TDesC& aDatabaseUri)
// Adds a landmark to the given database.
// -----------------------------------------------------------------------------
//
EXPORT_C TPosLmItemId CLandmarkService::AddItemL( CPosLandmark& aLandmark,
		const TDesC& aDatabaseUri )
	{
#ifdef _DEBUG
	iLog.Write(_L("CLandmarkService::AddItemL: Landmark"));
#endif

	CLandmarkHandler* handler = iManageHandler->GetHandlerL(aDatabaseUri);
	if ( !handler )
		{
		handler = iManageHandler->CreateHandlerL(aDatabaseUri);
		}
	CPosLandmarkDatabase* db = handler->LandmarkDatabaseHandle();
	
#ifdef _DEBUG
	iLog.Write(_L("CLandmarkService::AddItemL: Landmark:Exit"));
#endif
	
	return db->AddLandmarkL(aLandmark);
	}

// -----------------------------------------------------------------------------
// CLandmarkService::AddItemL( CPosLandmarkCategory& aCategory,const TDesC& aDatabaseUri )
// Adds a landmark category to the given database.
// -----------------------------------------------------------------------------
//
EXPORT_C TPosLmItemId CLandmarkService::AddItemL( CPosLandmarkCategory& aCategory,
		const TDesC& aDatabaseUri )
	{
#ifdef _DEBUG
	iLog.Write(_L("CLandmarkService::AddItemL: Category"));
#endif

	CLandmarkHandler* handler = iManageHandler->GetHandlerL(aDatabaseUri);
	if ( !handler )
		{
		handler = iManageHandler->CreateHandlerL(aDatabaseUri);
		}
	CPosLmCategoryManager* cat = handler->CategoryManagerHandle();
	
#ifdef _DEBUG
	iLog.Write(_L("CLandmarkService::AddItemL: Category: Exit"));
#endif 
	
	return cat->AddCategoryL(aCategory);
	}
// -----------------------------------------------------------------------------
// CLandmarkService::AddItemL( CPosLandmarkCategory& aCategory,const TDesC& aDatabaseUri )
// Adds a landmark category to the given database.
// -----------------------------------------------------------------------------
//
EXPORT_C void CLandmarkService::AddItemL( const TDesC& aDatabaseUri )
	{
#ifdef _DEBUG
	iLog.Write(_L("CLandmarkService::AddItemL: Database"));
#endif

	HPosLmDatabaseInfo* dbInfo = HPosLmDatabaseInfo::NewLC(aDatabaseUri);
	if ( ELocalDatabase == GetDbTypeFromUri ( aDatabaseUri ) )
		{
		iDatabaseManager->CreateDatabaseL(*dbInfo);
		}
	else
		{
		iDatabaseManager->RegisterDatabaseL(*dbInfo);
		}
	CleanupStack::PopAndDestroy(dbInfo);

#ifdef _DEBUG
	iLog.Write(_L("CLandmarkService::AddItemL: Database: Exit"));
#endif    
	}

// -----------------------------------------------------------------------------
// CLandmarkService::UpdateItemL( const CPosLandmark& aLandmark,
//    const TDesC& aDatabaseUri )
// Updates a landmark in the given database.
// -----------------------------------------------------------------------------
//
EXPORT_C void CLandmarkService::UpdateItemL( const CPosLandmark& aLandmark,
		const TDesC& aDatabaseUri )
	{
#ifdef _DEBUG
	iLog.Write(_L("CLandmarkService::UpdateItemL: Landmark"));
#endif

	CLandmarkHandler* handler = iManageHandler->GetHandlerL(aDatabaseUri);
	if ( !handler )
		{
		handler = iManageHandler->CreateHandlerL(aDatabaseUri);
		}
	CPosLandmarkDatabase* db = handler->LandmarkDatabaseHandle();
	db->UpdateLandmarkL(aLandmark);

#ifdef _DEBUG
	iLog.Write(_L("CLandmarkService::UpdateItemL: Landmark:Exit"));
#endif    
	}

// -----------------------------------------------------------------------------
// CLandmarkService::UpdateItemL( const CPosLandmarkCategory& aCategory,
//    const TDesC& aDatabaseUri )
// Updates a landmark Category in the given database.
// -----------------------------------------------------------------------------
//
EXPORT_C void CLandmarkService::UpdateItemL( const CPosLandmarkCategory& aCategory,
		const TDesC& aDatabaseUri )
	{
#ifdef _DEBUG
	iLog.Write(_L("CLandmarkService::UpdateItemL: Category"));
#endif

	CLandmarkHandler* handler = iManageHandler->GetHandlerL(aDatabaseUri);
	if ( !handler )
		{
		handler = iManageHandler->CreateHandlerL(aDatabaseUri);
		}
	CPosLmCategoryManager* cat = handler->CategoryManagerHandle();
	cat->UpdateCategoryL(aCategory);

#ifdef _DEBUG
	iLog.Write(_L("CLandmarkService::UpdateItemL: Category; Exit"));
#endif    
	}

// -----------------------------------------------------------------------------
// CLandmarkService::UpdateItemL( TPosLmDatabaseSettings aSettings, const TDesC& aDatabaseUri )
// Updates the database information in the given database.
// -----------------------------------------------------------------------------
//
EXPORT_C void CLandmarkService::UpdateItemL( TPosLmDatabaseSettings aSettings,
		const TDesC& aDatabaseUri )
	{
#ifdef _DEBUG
	iLog.Write(_L("CLandmarkService::UpdateItemL: Database"));
#endif

	//while modifying database settings drive letter in database uri 
	//should always be specified in uppercase.
	HBufC* dburi = aDatabaseUri.AllocLC();
	//set modifiable pointer.
	TPtr modifyuri = dburi->Des();

	TInt offset = aDatabaseUri.Find(KProtocolSeparator);
	if(offset>=0)
		{
		//get drive letter
		TChar drive = modifyuri[offset+KProtocolSeparator.iTypeLength];
		//make drive uppercase.
		drive.UpperCase();
		modifyuri[offset+KProtocolSeparator.iTypeLength] = drive;
		}
	else
		{
		//get drive letter at index-0
		TChar drive = modifyuri[0];
		//make drive uppercase.
		drive.UpperCase();
		modifyuri[0] = drive;
		}

	iDatabaseManager->ModifyDatabaseSettingsL(*dburi,aSettings);
	CleanupStack::PopAndDestroy(dburi);
#ifdef _DEBUG
	iLog.Write(_L("CLandmarkService::UpdateItemL: Database: Exit"));
#endif    
	}

// -----------------------------------------------------------------------------
// CLandmarkService::LandmarkLC( const TPosLmItemId& aLandmarkId,
//    const TDesC& aDatabaseUri  )
// Retrieves a landmark from the database.
// -----------------------------------------------------------------------------
//
EXPORT_C CPosLandmark* CLandmarkService::LandmarkLC( const TPosLmItemId& aLandmarkId,
		const TDesC& aDatabaseUri ) const
	{
	CPosLandmark* landmark = NULL;
	CleanupStack::PushL(landmark);
	CLandmarkHandler* handler = iManageHandler->GetHandlerL(aDatabaseUri);
	if ( !handler )
		{
		handler = iManageHandler->CreateHandlerL(aDatabaseUri);
		}
	CPosLandmarkDatabase* db = handler->LandmarkDatabaseHandle();
	CPosLmItemIterator* iterator = db->LandmarkIteratorL();
	CleanupStack::PushL(iterator);
	TPosLmItemId lmId;
	while ( (lmId = iterator->NextL()) != KPosLmNullItemId )
		{
		if ( aLandmarkId == lmId )
			{
			CleanupStack::PopAndDestroy(iterator);
			CleanupStack::Pop(landmark);
			return db->ReadLandmarkLC(lmId);
			}
		}
	CleanupStack::PopAndDestroy(iterator);
	return landmark;
	}

// -----------------------------------------------------------------------------
// CLandmarkService::CategoryLC( const TPosLmItemId& aCategoryId,
//    const TDesC& aDatabaseUri  )
// Retrieves a category from the database.
// -----------------------------------------------------------------------------
//
EXPORT_C CPosLandmarkCategory* CLandmarkService::CategoryLC(
		const TPosLmItemId& aCategoryId, const TDesC& aDatabaseUri ) const
	{
	CPosLandmarkCategory* category = NULL;
	CleanupStack::PushL(category);
	CLandmarkHandler* handler = iManageHandler->GetHandlerL(aDatabaseUri);
	if ( !handler )
		{
		handler = iManageHandler->CreateHandlerL(aDatabaseUri);
		}
	CPosLmCategoryManager* cat = handler->CategoryManagerHandle();
	CPosLmItemIterator* iterator = cat->CategoryIteratorL();
	CleanupStack::PushL(iterator);
	TPosLmItemId catId;
	while ( (catId = iterator->NextL()) != KPosLmNullItemId )
		{
		if ( aCategoryId == catId )
			{
			CleanupStack::PopAndDestroy(iterator);
			CleanupStack::Pop(category);
			return cat->ReadCategoryLC(catId);
			}
		}
	CleanupStack::PopAndDestroy(iterator);
	return category;
	}

// -----------------------------------------------------------------------------
// CLandmarkService::RemoveItemL( TPosLmItemId aItemId,
//    TBool aItemIsLandmark, const TDesC& aDatabaseUri )
// Removes a landmark/ landmark category from the given database
// -----------------------------------------------------------------------------
//
EXPORT_C void CLandmarkService::RemoveItemL( TPosLmItemId aItemId,
		TPosItem aItemIsLandmark, const TDesC& aDatabaseUri )
	{
#ifdef _DEBUG
	iLog.Write(_L("CLandmarkService::RemoveItemL"));
#endif

	CLandmarkHandler* handler = iManageHandler->GetHandlerL(aDatabaseUri);
	if ( !handler )
		{
		handler = iManageHandler->CreateHandlerL(aDatabaseUri);
		}
	if ( aItemIsLandmark )
		{
		CPosLandmarkDatabase* db = handler->LandmarkDatabaseHandle();
		db->RemoveLandmarkL(aItemId);
		}
	else
		{
		CPosLmCategoryManager* cat = handler->CategoryManagerHandle();
		ExecuteAndDeleteLD(cat->RemoveCategoryL(aItemId));
		}

#ifdef _DEBUG
	iLog.Write(_L("CLandmarkService::RemoveItemL:exit"));
#endif    
	}

// -----------------------------------------------------------------------------
// CLandmarkService::RemoveItemL( const TDesC& aDatabaseUri )
// Removes the given database.
// -----------------------------------------------------------------------------
//
EXPORT_C void CLandmarkService::RemoveItemL( const TDesC& aDatabaseUri )
	{
#ifdef _DEBUG
	iLog.Write(_L("CLandmarkService::RemoveItemL: Database"));
#endif

	if ( ELocalDatabase == GetDbTypeFromUri (aDatabaseUri) )
		{
		// will leave with KErrInUse if it is in use.
		iDatabaseManager->DeleteDatabaseL(aDatabaseUri);
		}
	else
		{
		// this is for remote databases and it will remove this
		// database from being listed.
		iDatabaseManager->UnregisterDatabaseL(aDatabaseUri);
		}

#ifdef _DEBUG
	iLog.Write(_L("CLandmarkService::RemoveItemL: Database: Exit"));
#endif    
	}

// -----------------------------------------------------------------------------
// CLandmarkService::SetActiveL( const TDesC& aDatabaseUri )
// sets the given database as default.
// -----------------------------------------------------------------------------
//
EXPORT_C void CLandmarkService::SetActiveL( const TDesC& aDatabaseUri )
	{
#ifdef _DEBUG
	iLog.Write(_L("CLandmarkService::SetActiveL: Database"));
#endif

	CLandmarkHandler* handler = iManageHandler->GetHandlerL(aDatabaseUri);
	if ( !handler )
		{
		handler = iManageHandler->CreateHandlerL(aDatabaseUri);
		}
	iManageHandler->SetDefaultHandler(handler);

#ifdef _DEBUG
	iLog.Write(_L("CLandmarkService::SetActiveL: Database: Exit"));
#endif    
	}

// -----------------------------------------------------------------------------
// CLandmarkService::LinkCategoryToLandmarksL( TPosLmItemId aCategoryId,
//    RArray< TPosLmItemId >& aLandmarkIdArray, const TDesC& aDatabaseUri )
// associates a category to a set of landmarks.
// -----------------------------------------------------------------------------
//
EXPORT_C void CLandmarkService::LinkCategoryToLandmarksL ( TPosLmItemId aCategoryId,
		RArray<TPosLmItemId>& aLandmarkIdArray, const TDesC& aDatabaseUri )
	{
#ifdef _DEBUG
	iLog.Write(_L("CLandmarkService::LinkCategoryToLandmarksL"));
#endif

	CLandmarkHandler* handler = iManageHandler->GetHandlerL(aDatabaseUri);
	if ( !handler )
		{
		handler = iManageHandler->CreateHandlerL(aDatabaseUri);
		}
	CPosLmCategoryManager* cat = handler->CategoryManagerHandle();
	ExecuteAndDeleteLD(cat->AddCategoryToLandmarksL(aCategoryId,aLandmarkIdArray));

#ifdef _DEBUG
	iLog.Write(_L("CLandmarkService::LinkCategoryToLandmarksL: Exit"));
#endif    
	}

// -----------------------------------------------------------------------------
// CLandmarkService::UnlinkCategoryToLandmarksL( TPosLmItemId aCategoryId,
//    RArray< TPosLmItemId >& aLandmarkIdArray, const TDesC& aDatabaseUri )
// associates a category to a set of landmarks.
// -----------------------------------------------------------------------------
//
EXPORT_C void CLandmarkService::UnlinkCategoryToLandmarksL (
		TPosLmItemId aCategoryId, RArray<TPosLmItemId>& aLandmarkIdArray,
		const TDesC& aDatabaseUri )
	{
#ifdef _DEBUG
	iLog.Write(_L("CLandmarkService::UnlinkCategoryToLandmarksL"));
#endif

	CLandmarkHandler* handler = iManageHandler->GetHandlerL(aDatabaseUri);
	if ( !handler )
		{
		handler = iManageHandler->CreateHandlerL(aDatabaseUri);
		}
	CPosLmCategoryManager* cat = handler->CategoryManagerHandle();
	ExecuteAndDeleteLD(cat->RemoveCategoryFromLandmarksL(aCategoryId,aLandmarkIdArray));

#ifdef _DEBUG
	iLog.Write(_L("CLandmarkService::UnlinkCategoryToLandmarksL: Exit"));
#endif    
	}

// -----------------------------------------------------------------------------
// CLandmarkService::RegisterObserver( MLandmarkObserver* aObserver )
// Register an observer for aynsc method.
// -----------------------------------------------------------------------------
//
EXPORT_C void CLandmarkService::RegisterObserver( MLandmarkObserver* aObserver )
	{
	if ( iObserver )
		{
		delete iObserver;
		iObserver = NULL;
		}
	iObserver = aObserver;
	}

// -----------------------------------------------------------------------------
// CLandmarkService::Cancel( TInt32 aTransactionId )
// Cancel an ongoing async request.
// -----------------------------------------------------------------------------
//
EXPORT_C void CLandmarkService::Cancel( TInt32 aTransactionId ) const
	{
	if ( iManageObjects )
		{
		iManageObjects->CancelObject(aTransactionId);
		}
	}

// -----------------------------------------------------------------------------
// CLandmarkService::GetDefaultDbUri( TPtrC& aDefaultDbUri ) const
// Gets the deafult Database URI.
// -----------------------------------------------------------------------------
//
EXPORT_C void CLandmarkService::GetDefaultDbUriL( TPtrC& aDefaultDbUri ) const
	{
	CLandmarkHandler* handler = iManageHandler->GetHandlerL(KNullDesC);
	if ( handler )
		{
		handler->GetDatabaseUri(aDefaultDbUri);
		}
	}
// -----------------------------------------------------------------------------
// CLandmarkService::GetDbTypeFromUri( const TDesC& aDbUri )
// returns type of database.
// -----------------------------------------------------------------------------
//
CLandmarkService::TDatabaseType CLandmarkService::GetDbTypeFromUri(
		const TDesC& aDbUri ) const
	{
	CLandmarkService::TDatabaseType type = ERemoteDatabase;
	TInt offset = aDbUri.Find (KProtocolSeparator );
	if ( KErrNotFound == offset )
		{
		type = ELocalDatabase;
		}
	else
		{
		const TPtrC DbProtocol = aDbUri.Left (offset );
		if ( DbProtocol == KLocalProtocol )
			{
			type = ELocalDatabase;
			}
		}
	return type;
	}

// End of File
