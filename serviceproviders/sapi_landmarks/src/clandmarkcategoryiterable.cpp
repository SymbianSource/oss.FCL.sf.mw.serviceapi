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
* Description:  CLandmarkCategoryIterable class implementation
*
*/


#include <epos_cposlandmarkcategory.h>
#include <epos_cposlandmarkdatabase.h>
#include <epos_cposlmcategorymanager.h>
#include <epos_cposlmitemiterator.h>
#include "clandmarkcategoryiterable.h"
#include "landmarkliwparams.hrh"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CLandmarkCategoryIterable::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CLandmarkCategoryIterable* CLandmarkCategoryIterable::NewL( CPosLmItemIterator* aIterator,
     const TDesC& aDatabaseUri )
    {
    CLandmarkCategoryIterable* self = new (ELeave) CLandmarkCategoryIterable(aIterator);
    CleanupStack::PushL(self);
    self->ConstructL(aDatabaseUri);
    CleanupStack::Pop(self);
    return self;
    }

// -----------------------------------------------------------------------------
// CLandmarkCategoryIterable::ConstructL( const TDesC & aDatabaseUri )
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CLandmarkCategoryIterable::ConstructL( const TDesC& aDatabaseUri )
    {
    iDatabase = CPosLandmarkDatabase::OpenL(aDatabaseUri);
    if ( iDatabase->IsInitializingNeeded() )
        {
        ExecuteAndDeleteLD(iDatabase->InitializeL());
        }
    iCategoryManager = CPosLmCategoryManager::NewL(*iDatabase);
    }

// CLandmarkCategoryIterable::CLandmarkCategoryIterable( CPosLmItemIterator* aIterator )
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CLandmarkCategoryIterable::CLandmarkCategoryIterable( CPosLmItemIterator* aIterator )
                         : iIterator(aIterator)
    {
    }

// -----------------------------------------------------------------------------
// CLandmarkCategoryIterable::~CLandmarkCategoryIterable()
// Destructor.
// -----------------------------------------------------------------------------
//
CLandmarkCategoryIterable::~CLandmarkCategoryIterable()
    {
    delete iIterator;
    delete iLandmarkCategory;
    delete iCategoryManager;
    delete iDatabase;
    delete iCategoryId;
    delete iGlobalCategoryId;
    ReleaseLandmarkResources();
    }

// -----------------------------------------------------------------------------
// CLandmarkCategoryIterable::Reset()
// Resets the iterator. NextL has to be called to retrieve the first item.
// -----------------------------------------------------------------------------
//
void CLandmarkCategoryIterable::Reset()
    {
    iIterator->Reset();
    }

// -----------------------------------------------------------------------------
// CLandmarkCategoryIterable::NextL( TLiwVariant& aEntry )
// retrievs the next item in the list.
// -----------------------------------------------------------------------------
//
TBool CLandmarkCategoryIterable::NextL( TLiwVariant& aEntry )
    {
    if ( iLandmarkCategory )
        {
        delete iLandmarkCategory;
        iLandmarkCategory = NULL;
        delete iCategoryId;
        iCategoryId = NULL;
        delete iGlobalCategoryId;
        iGlobalCategoryId = NULL;
        }
    TPosLmItemId categoryId = iIterator->NextL();
    if ( KPosLmNullItemId == categoryId )
        {
        return EFalse;
        }
    TPtrC categoryName;
    TPtrC iconFileName;
    TInt iconIndex;
    TInt iconMaskIndex;
    CLiwMap* categoryMap = CLiwDefaultMap::NewL();
    CleanupClosePushL(*categoryMap);
    iLandmarkCategory = iCategoryManager->ReadCategoryLC(categoryId);
    CleanupStack::Pop(iLandmarkCategory);
    
    iCategoryId = HBufC::NewL(KMaxIDStringLength);
    iCategoryId->Des().Num(categoryId,EDecimal);
    categoryMap->InsertL(KId,TLiwVariant(iCategoryId));
    
    if ( iLandmarkCategory->GetCategoryName(categoryName) == KErrNone )
        {
        categoryMap->InsertL(KCategoryName,TLiwVariant(categoryName));
        }
    TPosLmGlobalCategory globalCategory = iLandmarkCategory->GlobalCategory();
    if ( KPosLmNullGlobalCategory != globalCategory )
        {
        iGlobalCategoryId = HBufC::NewL(KMaxIDStringLength);
        iGlobalCategoryId->Des().Num(globalCategory,EDecimal);
        categoryMap->InsertL(KGlobalCategory,TLiwVariant(iGlobalCategoryId));
        }
    if ( iLandmarkCategory->GetIcon(iconFileName,iconIndex,iconMaskIndex) == KErrNone )
        {
        categoryMap->InsertL(KIconFile,TLiwVariant(iconFileName));
        categoryMap->InsertL(KIconIndex,TLiwVariant((TInt32)iconIndex));
        categoryMap->InsertL(KIconMaskIndex,TLiwVariant((TInt32)iconMaskIndex));
        }
    aEntry.SetL(categoryMap);
    CleanupStack::PopAndDestroy(categoryMap);
    return ETrue;
    }

//end of file
