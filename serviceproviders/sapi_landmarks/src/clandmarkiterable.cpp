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
* Description:  CLandmarkIterable class implementation
*
*/


#include <e32math.h>
#include <epos_cposlandmark.h>
#include <epos_cposlandmarkdatabase.h>
#include <epos_cposlmitemiterator.h>
#include <lbsposition.h>
#include "clandmarkiterable.h"
#include "landmarkliwparams.hrh"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CLandmarkIterable::NewL( CPosLmItemIterator* aIterator,
//    TDesC& aDatabaseUri )
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CLandmarkIterable* CLandmarkIterable::NewL( CPosLmItemIterator* aIterator,
    const TDesC& aDatabaseUri )
    {
    CLandmarkIterable* self = new (ELeave) CLandmarkIterable(aIterator);
    CleanupStack::PushL(self);
    self->ConstructL(aDatabaseUri);
    CleanupStack::Pop(self);
    return self;
    }

// -----------------------------------------------------------------------------
// CLandmarkIterable::ConstructL( const TDesC & aDatabaseUri )
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CLandmarkIterable::ConstructL( const TDesC& aDatabaseUri )
    {
    iDatabase = CPosLandmarkDatabase::OpenL(aDatabaseUri);
    if ( iDatabase->IsInitializingNeeded() )
        {
        ExecuteAndDeleteLD(iDatabase->InitializeL());
        }
    }

// -----------------------------------------------------------------------------
// CLandmarkIterable::CLandmarkIterable( CPosLmItemIterator* aIterator )
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CLandmarkIterable::CLandmarkIterable( CPosLmItemIterator* aIterator )
                 : iIterator(aIterator)
    {
    }

// -----------------------------------------------------------------------------
// CLandmarkIterable::~CLandmarkIterable()
// Destructor.
// -----------------------------------------------------------------------------
//
 CLandmarkIterable::~CLandmarkIterable()
    {
    delete iIterator;
    delete iLandmark;
    delete iDatabase;
    delete iLandmarkId;
    iCategoryIds.ResetAndDestroy();
    iCategoryIds.Close();
    ReleaseLandmarkResources();
    }

// -----------------------------------------------------------------------------
// CLandmarkIterable::Reset()
// Resets the iterator. NextL has to be called to retrieve the first item.
// -----------------------------------------------------------------------------
//
void CLandmarkIterable::Reset()
    {
    iIterator->Reset();
    }

// -----------------------------------------------------------------------------
// CLandmarkIterable::NextL( TLiwVariant& aEntry )
// retrievs the next item in the list.
// -----------------------------------------------------------------------------
//
TBool CLandmarkIterable::NextL( TLiwVariant& aEntry )
    {
    if ( iLandmark )
        {
        delete iLandmark;
        iLandmark = NULL;
        delete iLandmarkId;
        iLandmarkId = NULL;
        iCategoryIds.ResetAndDestroy();
        }
        
    TPosLmItemId landmarkId = iIterator->NextL();
    if ( KPosLmNullItemId == landmarkId )
        {
        return EFalse;
        }
        
    TPtrC landmarkName;
    TLocality location;
    TReal32 coverageRadius;
    TPtrC iconFileName;
    TInt iconIndex;
    TInt iconMaskIndex;
    TPtrC description;
    TUint numberOfId;
    
    CLiwMap* landmarkMap = CLiwDefaultMap::NewL();
    CleanupClosePushL (*landmarkMap );
    RArray<TPosLmItemId> categoryIdArray;
    CleanupClosePushL(categoryIdArray);
    
    iLandmark = iDatabase->ReadLandmarkLC(landmarkId);
    CleanupStack::Pop(iLandmark);
    
    iLandmarkId = HBufC::NewL(KMaxIDStringLength);
    iLandmarkId->Des().Num(landmarkId,EDecimal);
    landmarkMap->InsertL(KId,TLiwVariant(iLandmarkId));

    if ( iLandmark->GetLandmarkName(landmarkName) == KErrNone )
        {
        landmarkMap->InsertL(KLandmarkName,TLiwVariant(landmarkName));
        }
        
    if ( iLandmark->GetPosition(location) == KErrNone )
        {
        CLiwMap* positionMap = CLiwDefaultMap::NewL();
        CleanupClosePushL (*positionMap );
        TRealX num = location.Latitude();
        if( !num.IsNaN() )
        {
        	positionMap->InsertL(KLatitude,TLiwVariant((TReal)num));
        }
        num = location.Longitude();
        if( !num.IsNaN() )
        {
        	positionMap->InsertL(KLongitude,TLiwVariant((TReal)num));
        }
        num = location.Altitude();
        if( !num.IsNaN() )
        {
        	positionMap->InsertL(KAltitude,TLiwVariant((TReal)num));
        }
        num = location.HorizontalAccuracy();
        if( !num.IsNaN() )
        {
        	positionMap->InsertL(KHAccuracy,TLiwVariant((TReal)num));
        }
        num = location.VerticalAccuracy();
        if( !num.IsNaN() )
        {
        	positionMap->InsertL(KVAccuracy,TLiwVariant((TReal)num));
        }

        landmarkMap->InsertL(KLandmarkPosition,TLiwVariant(positionMap));
        CleanupStack::PopAndDestroy (positionMap );
        }
        
    if ( iLandmark->GetCoverageRadius(coverageRadius) == KErrNone )
        {
        landmarkMap->InsertL(KCoverageRadius,TLiwVariant(coverageRadius));
        }
        
    iLandmark->GetCategoriesL(categoryIdArray);
    TInt catCount = categoryIdArray.Count();
    if ( catCount )
        {
        CLiwList* categoryList = CLiwDefaultList::NewL();
        CleanupClosePushL ( *categoryList );
        for ( TInt index = 0; index < catCount; ++index )
            {
            HBufC* catId = HBufC::NewLC(KMaxIDStringLength);
            iCategoryIds.AppendL(catId);
            CleanupStack::Pop(catId);
            catId->Des().Num(categoryIdArray[index],EDecimal);
            categoryList->AppendL(TLiwVariant(catId));
            }
        landmarkMap->InsertL(KCategoryInfo,TLiwVariant(categoryList));
        CleanupStack::PopAndDestroy (categoryList );
        }
        
    if ( iLandmark->GetIcon(iconFileName,iconIndex,iconMaskIndex) == KErrNone )
        {
        landmarkMap->InsertL(KIconFile,TLiwVariant(iconFileName));
        landmarkMap->InsertL(KIconIndex,TLiwVariant((TInt32)iconIndex));
        landmarkMap->InsertL(KIconMaskIndex,TLiwVariant((TInt32)iconMaskIndex));
        }
        
    if ( iLandmark->GetLandmarkDescription(description) == KErrNone )
        {
        landmarkMap->InsertL(KLandmarkDesc,TLiwVariant(description));
        }
        
    numberOfId = iLandmark->NumOfAvailablePositionFields();
    if ( numberOfId )
        {
        CLiwMap* fieldMap = CLiwDefaultMap::NewL();
        CleanupClosePushL (*fieldMap );
        TPositionFieldId fieldId = iLandmark->FirstPositionFieldId();
        TPtrC fieldValue;
        TLiwVariant variant;
        while( numberOfId-- )
            {
            iLandmark->GetPositionField(fieldId,fieldValue);
            variant.Set(fieldValue);
            if ( EPositionFieldCountry == fieldId)
                {
                fieldMap->InsertL(KLandmarkCountry,variant);
                }
            if ( EPositionFieldPostalCode == fieldId)
                {
                fieldMap->InsertL(KLandmarkAreaCode,variant);
                }
            if ( EPositionFieldCity == fieldId)
                {
                fieldMap->InsertL(KLandmarkCity,variant);
                }
            if ( EPositionFieldDistrict == fieldId)
                {
                fieldMap->InsertL(KLandmarkDistrict,variant);
                }
            if ( EPositionFieldBuildingName == fieldId)
                {
                fieldMap->InsertL(KLandmarkBuildingName,variant);
                }
            if ( EPositionFieldStreet == fieldId)
                {
                fieldMap->InsertL(KLandmarkStreet,variant);
                }
            if ( EPositionFieldBuildingTelephone == fieldId)
                {
                fieldMap->InsertL(KLandmarkTelephone,variant);
                }
            fieldId = iLandmark->NextPositionFieldId(fieldId);
            }
        landmarkMap->InsertL(KLandmarkFields,TLiwVariant(fieldMap));
        CleanupStack::PopAndDestroy (fieldMap );
        variant.Reset();
        }
     
    CleanupStack::PopAndDestroy(&categoryIdArray);
       
    aEntry.SetL(landmarkMap);
    CleanupStack::PopAndDestroy (landmarkMap );
    
    return ETrue;
    }

//end of file
