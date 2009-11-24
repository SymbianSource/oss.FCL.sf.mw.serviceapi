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
* Description:  CLandmarkFilter class implementation.
 *
*/


#include <EPos_CPosLandmarkSearch.h>
#include <EPos_CPosLmCatNameCriteria.h>
#include <EPos_CPosLmTextCriteria.h>
#include <EPos_CPosLandmark.h>
#include "clandmarkfilter.h"

_LIT(KGetAll,"*");
// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CLandmarkFilter::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
EXPORT_C CLandmarkFilter* CLandmarkFilter::NewL( TFilterItem aItem )
	{
	CLandmarkFilter* self = CLandmarkFilter::NewLC(aItem);
	CleanupStack::Pop( self );
	return self;
	}

// -----------------------------------------------------------------------------
// CLandmarkFilter::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
EXPORT_C CLandmarkFilter* CLandmarkFilter::NewLC( TFilterItem aItem )
	{
	CLandmarkFilter* self = new (ELeave) CLandmarkFilter();
	CleanupStack::PushL( self );
	self->ConstructL(aItem);
	return self;
	}

// -----------------------------------------------------------------------------
// CLandmarkFilter::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CLandmarkFilter::ConstructL( TFilterItem aItem )
	{
	iIsLandmark = aItem;
	CPosLmCatNameCriteria* catCriteria = NULL;
	CPosLmTextCriteria* lmCriteria = NULL;
	switch ( iIsLandmark )
		{
		case ECategory:
			catCriteria = CPosLmCatNameCriteria::NewLC ( );
			catCriteria->SetSearchPatternL (KGetAll );
			SetCriteria (catCriteria );
			CleanupStack::Pop (catCriteria );
			break;
		case ELandmark:
			lmCriteria = CPosLmTextCriteria::NewLC ( );
			lmCriteria->SetTextL (KGetAll );
			lmCriteria->SetAttributesToSearch (CPosLandmark::ELandmarkName );
			SetCriteria (lmCriteria );
			CleanupStack::Pop (lmCriteria );
			break;
		default:
			break;
		}
	}
// -----------------------------------------------------------------------------
// CLandmarkFilter::CLandmarkFilter()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CLandmarkFilter::CLandmarkFilter( ) :
	iLmSortPref(CPosLandmark::ELandmarkName),
			iCatSortPref(CPosLmCategoryManager::ECategorySortOrderNone),
			iSearchOnlyPreviousMatches(EFalse),
			iMaximumMatches(KPosLmMaxNumOfMatchesUnlimited)

	{
	}

// -----------------------------------------------------------------------------
// CLandmarkFilter::~CLandmarkFilter()
// Destructor.
// -----------------------------------------------------------------------------
//
CLandmarkFilter::~CLandmarkFilter( )
	{
	delete iCriteria;
	}

// -----------------------------------------------------------------------------
// CLandmarkFilter::SetCriteria ( CPosLmSearchCriteria* aCriteria )
// Sets the criteria on which search should be made.
// -----------------------------------------------------------------------------
//
EXPORT_C void CLandmarkFilter::SetCriteria ( CPosLmSearchCriteria* aCriteria )
	{
	if( iCriteria )
		{
		delete iCriteria;
		iCriteria = NULL;
		}
	iCriteria = aCriteria;
	}
//end of file
