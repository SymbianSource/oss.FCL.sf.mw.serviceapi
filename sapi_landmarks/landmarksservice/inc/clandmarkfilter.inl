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
* Description:  CLandmarkFilter class
 *
*/


// -----------------------------------------------------------------------------
// CLandmarkFilter::SetLmSortPref ( const TPosLmSortPref& aLmSortPref )
// Sets the sorting order for landmarks.
// -----------------------------------------------------------------------------
//
inline void CLandmarkFilter::SetLmSortPref( const TPosLmSortPref& aLmSortPref )
	{
	iLmSortPref = aLmSortPref;
	}

// -----------------------------------------------------------------------------
// CLandmarkFilter::SetCatSortPref ( const CPosLmCategoryManager::TCategorySortPref&  aCatSortPref )
// Sets the sorting order for categories.
// -----------------------------------------------------------------------------
//
inline void CLandmarkFilter::SetCatSortPref(
		const CPosLmCategoryManager::TCategorySortPref& aCatSortPref )
	{
	iCatSortPref = aCatSortPref;
	}

// -----------------------------------------------------------------------------
// CLandmarkFilter::SetPreviousMatches ( const TBool& aSearchOnlyPreviousMatches )
// Sets the flag for searching on a previously searched list.
// -----------------------------------------------------------------------------
//
inline void CLandmarkFilter::SetPreviousMatches(
		const TBool& aSearchOnlyPreviousMatches )
	{
	iSearchOnlyPreviousMatches = aSearchOnlyPreviousMatches;
	}

// -----------------------------------------------------------------------------
// CLandmarkFilter::SetMaximumMatches ( const TInt32& aMaximumMatches )
// Sets the maximum matches to be retrieved.
// -----------------------------------------------------------------------------
//
inline void CLandmarkFilter::SetMaximumMatches( const TInt32& aMaximumMatches )
	{
	iMaximumMatches = aMaximumMatches;
	}

// -----------------------------------------------------------------------------
// CLandmarkFilter::Criteria ()
// Returns the criteria on which search should be made.
// -----------------------------------------------------------------------------
//
inline CPosLmSearchCriteria& CLandmarkFilter::Criteria( )
	{
	return *iCriteria;
	}

// -----------------------------------------------------------------------------
// CLandmarkFilter::LmSortPref ()
// Returns the sorting order for landmarks.
// -----------------------------------------------------------------------------
//
inline TPosLmSortPref CLandmarkFilter::LmSortPref( )
	{
	return iLmSortPref;
	}

// -----------------------------------------------------------------------------
// CLandmarkFilter::CatSortPref ()
// Returns the sorting order for categories.
// -----------------------------------------------------------------------------
//
inline CPosLmCategoryManager::TCategorySortPref CLandmarkFilter::CatSortPref( )
	{
	return iCatSortPref;
	}

// -----------------------------------------------------------------------------
// CLandmarkFilter::PreviousMatches ()
// Returns the flag for searching on a previously searched list.
// -----------------------------------------------------------------------------
//
inline TBool CLandmarkFilter::PreviousMatches( )
	{
	return iSearchOnlyPreviousMatches;
	}

// -----------------------------------------------------------------------------
// CLandmarkFilter::MaximumMatches ()
// Sets the maximum matches to be retrieved.
// -----------------------------------------------------------------------------
//
inline TInt32 CLandmarkFilter::MaximumMatches( )
	{
	return iMaximumMatches;
	}

// -----------------------------------------------------------------------------
// CLandmarkFilter::IsLandmark ()
// Returns the flag if search is on landmark or category.
// -----------------------------------------------------------------------------
//
inline TBool CLandmarkFilter::IsLandmark( )
	{
	return iIsLandmark;
	}
