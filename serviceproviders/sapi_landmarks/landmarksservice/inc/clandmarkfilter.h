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


#ifndef __CLANDMARKFILTER_H__
#define __CLANDMARKFILTER_H__

// INCLUDES
#include <e32base.h>
#include <EPos_CPosLmCategoryManager.h>

//FORWARD DECLARARTION
class CPosLmSearchCriteria;
class TPosLmSortPref;

/**
 * CLandmarkFilter
 * This class acts as a filter for retrieving a set of landmarks or landmark categories
 * based on different criteria from a database.
 */
// CLASS DECLARATION
NONSHARABLE_CLASS(CLandmarkFilter) : public CBase
	{
public:
	/**
	 * TFilterItem
	 *  Specifies if the filter is for a landmark or a landmark category.
	 */
	enum TFilterItem
		{
		ECategory = 0 /**<Item is a landmark category.> */,
		ELandmark /**<Item is a landmark.> */
		};

public: // New methods

	/**
	 * NewL.
	 * Two-phased constructor.
	 * Create a CLandmarkFilter object.
	 * @param aItem Sets the filter for a landmark or category.
	 * @return A pointer to the created instance of CLandmarkFilter.
	 */
	IMPORT_C static CLandmarkFilter* NewL( TFilterItem aItem );

	/**
	 * NewL.
	 * Two-phased constructor.
	 * Create a CLandmarkFilter object.
	 * @param aItem Sets the filter for a landmark or category.
	 * @return a pointer to the created instance of CLandmarkFilter.
	 */
	IMPORT_C static CLandmarkFilter* NewLC( TFilterItem aItem );

	/**
	 * ~CLandmarkFilter
	 * Destructor.
	 */
	~CLandmarkFilter();

public: // function to set search criteria 

	/**
	 * SetCriteria.
	 * This function sets the criteria for search in the database.
	 * @param aCriteria The criteria on which the search should be made.
	 */
	IMPORT_C void SetCriteria ( CPosLmSearchCriteria* aCriteria );

	/**
	 * SetLmSortPref.
	 * This function sets the sorting preference of retrieved landmarks.
	 * @param aLmSortPref The sorting order of retrieved landmarks.
	 */
	inline void SetLmSortPref ( const TPosLmSortPref& aLmSortPref );

	/**
	 * SetCatSortPref.
	 * This function sets the sorting preference of retrieved categories.
	 * @param aCatSortPref The sorting order of retrieved categories.
	 */
	inline void SetCatSortPref (
			const CPosLmCategoryManager::TCategorySortPref& aCatSortPref );

	/**
	 * SetPreviousMatches.
	 * This function sets flag for searching through a previously retrieved searched list.
	 * @param aSearchOnlyPreviousMatches Flag to enable search on previous matches.
	 */
	inline void SetPreviousMatches ( const TBool& aSearchOnlyPreviousMatches );

	/**
	 * SetMaximumMatches.
	 * This function sets the maximum number of matches.
	 * @param aMaximumMatches The maximum matches to be returned.
	 */
	inline void SetMaximumMatches ( const TInt32& aMaximumMatches );

public: // function to get search criteria

	/**
	 * Criteria.
	 * This function returns the criteria for search in the database.
	 * @return The criteria on which the search should be made.
	 */
	inline CPosLmSearchCriteria& Criteria ();

	/**
	 * LmSortPref.
	 * This function returns the sorting order of retrieved landmarks.
	 * @return The sorting order of retrieved landmarks.
	 */
	inline TPosLmSortPref LmSortPref ();

	/**
	 * CatSortPref.
	 * This function returns the sorting order of retrieved categories.
	 * @return The sorting order of retrieved categories.
	 */
	inline CPosLmCategoryManager::TCategorySortPref CatSortPref ();

	/**
	 * PreviousMatches.
	 * This function returns the flag for search on previous matches.
	 * @return Flag for search on previous matches.
	 */
	inline TBool PreviousMatches ();

	/**
	 * MaximumMatches.
	 * This function returns the maximum matches set for the search.
	 * @return The maximum matches to be returned.
	 */
	inline TInt32 MaximumMatches ();

	/**
	 * IsLandmark.
	 * This function checks whether the filter is for a landmark or category.
	 * @return The flag for type of item to be searched.
	 */
	inline TBool IsLandmark ();

private: // Constructors

	/**
	 * ConstructL
	 * 2nd phase constructor.
	 * Perform the second phase construction of a
	 * CLandmarkFilter object.
	 * @param aItem Sets the filter for a landmark or category.
	 */
	void ConstructL ( TFilterItem aItem );

	/**
	 * CLandmarkFilter.
	 * C++ default constructor.
	 */
	CLandmarkFilter ();

private: // Data

	/**
	 * iCriteria
	 * The handle to the CPosLmSearchCriteria.
	 */
	CPosLmSearchCriteria* iCriteria;

	/**
	 * iLmSortPref
	 * The sort preferance for landmarks.
	 */
	TPosLmSortPref iLmSortPref;

	/**
	 * iCatSortPref
	 * The sort preferance for categories.
	 */
	CPosLmCategoryManager::TCategorySortPref iCatSortPref;

	/**
	 * iSearchOnlyPreviousMatches
	 * Flag to enable search on previous matches.
	 */
	TBool iSearchOnlyPreviousMatches;

	/**
	 * iMaximumMatches
	 * Maximum number of matches.
	 */
	TInt32 iMaximumMatches;

	/**
	 * iIsLandmark
	 * Flag to check if filter is for landmark search or category search.
	 */
	TFilterItem iIsLandmark;
	};

#include "clandmarkfilter.inl"

#endif // __CLANDMARKFILTER_H__

// End of File
