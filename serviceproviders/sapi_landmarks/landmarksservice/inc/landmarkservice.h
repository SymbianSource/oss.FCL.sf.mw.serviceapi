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
* Description:  CLandmarkService class
 *
*/


#ifndef __CLANDMARKSERVICE_H__
#define __CLANDMARKSERVICE_H__

#ifdef _DEBUG
#include <flogger.h>
#endif

// INCLUDES
#include <e32base.h>
#include <e32cmn.h>
#include <badesca.h>

//FORWARD DECLARARTIONS
class CLandmarkManageHandlers;
class MLandmarkObserver;
class CLandmarkFilter;
class CPosLandmarkParser;
class CPosLandmarkEncoder;
class CPosLmItemIterator;
class CPosLmDatabaseManager;
class CPosLandmark;
class CPosLandmarkCategory;
class TPosLmDatabaseSettings;
class CLandmarkManageObjects;

/**
 * CLandmarkService
 * This class has the core implementation. The member functions of this class
 * call the native landmarks api's to perform the necessary operations. This class 
 * also owns the garbage collector which takes care of active objects associated 
 * with async requests. It also owns the CLandmarkManageHandlers object that manages
 * the handles to open databases. The interface class calls the appropriate member
 * functions of this class to perform the required operation.
 */
// CLASS DECLARATION
NONSHARABLE_CLASS(CLandmarkService): public CBase
	{
public:
	/**
	 * TPosItem
	 * Specifies whether the id passed is a landmark id or a category id.
	 */
	enum TPosItem
		{
		ECategory = 0 /**<
		 Item is a landmark category id. */,
		ELandmark /**<
		 Item is a landmark id. */,
		};
	/**
	 * TDatabaseType
	 *  Specifies whether the database is local or remote.
	 */
	enum TDatabaseType
		{
		ELocalDatabase = 0 /**<
		 database is a local. */,
		ERemoteDatabase /**<
		 database is remote.  */,
		};

public: // New methods

	/**
	 * NewL.
	 * Two-phased constructor.
	 * Create a CLandmarkService object.
	 * @return A pointer to the created instance of CLandmarkService.
	 */
	IMPORT_C static CLandmarkService* NewL();

	/**
	 * NewLC.
	 * Two-phased constructor.
	 * Create a CLandmarkService object.
	 * @return A pointer to the created instance of CLandmarkService.
	 */
	IMPORT_C static CLandmarkService* NewLC();

	/**
	 * ~CLandmarkService
	 * Destructor.
	 */
	~CLandmarkService();

public: // Functions to retrieve data members

	/**
	 * ImportL.
	 * Imports landmarks to the requested database.
	 * @param aIterator A pointer reference to the list of imported landmarks. User
	 * owns the iterator.
	 * @param aLandmarkParser The instance of CPosLandmarkParser that 
	 * will parse the input landmark file.
	 * @param aDatabaseUri The URI of the database to which the parsed landmarks 
	 * will be imported.
	 */
	IMPORT_C void ImportL( CPosLmItemIterator*& aIterator,
			CPosLandmarkParser& aLandmarkParser,
			const TDesC& aDatabaseUri = KNullDesC );

	/**
	 * ExportL.
	 * Export a set of landmarks from the requested database to a file.
	 * @param aLandmarkEncoder A pointer to a landmark encoder object.
	 * @param aLandmarkIdArray The array of landmark ids which should be exported.
	 * @param aDatabaseUri The URI of the database from which the landmarks will 
	 * be exported.
	 */
	IMPORT_C void ExportL( CPosLandmarkEncoder& aLandmarkEncoder,
			const RArray<TPosLmItemId>& aLandmarkIdArray,
			const TDesC& aDatabaseUri = KNullDesC ) const;

	/**
	 * GetListL.
	 * Gets a list of landmarks/landmark categories from the requested database synchronously.
	 * @param aIterator A pointer reference to the list of retrieved landmarks/landmark 
	 * categories. User owns the iterator.
	 * @param aFilter The filter to be used for searching landmarks/landmark categories
	 * in database.
	 * @param aDatabaseUri The URI of the database from which landmarks/lanmdark categories 
	 * should be fetched.
	 */
	IMPORT_C void GetListL ( CPosLmItemIterator*& aIterator,
			CLandmarkFilter& aFilter, const TDesC& aDatabaseUri = KNullDesC ) const;

	/**
	 * GetListL.
	 * Gets a list of landmark databases.
	 * @param aDatabaseList A pointer reference to the list of retrieved databases. 
	 * User owns allocated list.
	 * @param aProtocol Protocol which matches that of the databases to be retrieved.
	 */
	IMPORT_C void GetListL( CDesCArray*& aDatabaseList,
			const TDesC& aProtocol = KNullDesC ) const;

	/**
	 * GetListL.
	 * Gets a list of landmarks/landmark categories from the requested database asynchronously.
	 * @param aTransactionId The transaction id assigned to this asynchronous request.
	 * @param aFilter The filter to be used for searching landmarks/landmark categories 
	 * in database.
	 * @param aDatabaseUri The URI of the database from which landmarks/lanmdark categories 
	 * should be fetched.
	 */
	IMPORT_C void GetListL( TInt32 aTransactionId,
			CLandmarkFilter& aFilter, const TDesC& aDatabaseUri = KNullDesC );

	/**
	 * AddItemL.
	 * Adds a new Landmark to the given database.
	 * @param aLandmark CPosLandmark instance to be added to database.
	 * @param aDatabaseUri The URI of the database to which the CPosLandmark
	 * instance should be added.
	 */
	IMPORT_C TPosLmItemId AddItemL( CPosLandmark& aLandmark,
			const TDesC& aDatabaseUri = KNullDesC );

	/**
	 * AddItemL.
	 * Adds a new Landmark category to the given database.
	 * @param aCategory CPosLandmarkCategory instance to be added to database.
	 * @param aDatabaseUri The URI of the database to which CPosLandmarkCategory
	 * instance should be added.
	 */
	IMPORT_C TPosLmItemId AddItemL( CPosLandmarkCategory& aCategory,
			const TDesC& aDatabaseUri = KNullDesC );

	/**
	 * AddItemL.
	 * Adds a new database to terminal.
	 * @param aDatabaseUri The URI of the database to be added to terminal.
	 */
	IMPORT_C void AddItemL( const TDesC& aDatabaseUri );

	/**
	 * UpdateItemL.
	 * Updates an existing Landmark in the given database.
	 * @param aLandmark CPosLandmark instance to be updated in database.
	 * @param aDatabaseUri The URI of the database in which CPosLandmark 
	 * instance should be updated.
	 */
	IMPORT_C void UpdateItemL( const CPosLandmark& aLandmark,
			const TDesC& aDatabaseUri = KNullDesC );

	/**
	 * UpdateItemL.
	 * Updates an existing Landmark category in the given database.
	 * @param aCategory CPosLandmarkCategory instance to be updated in database.
	 * @param aDatabaseUri The URI of the database to which CPosLandmarkCategory 
	 * instance should be updated.
	 */
	IMPORT_C void UpdateItemL( const CPosLandmarkCategory& aCategory,
			const TDesC& aDatabaseUri = KNullDesC );

	/**
	 * UpdateItemL.
	 * Updates existing Database Information.
	 * @param aSettings TPosLmDatabaseSettings information to be updated.
	 * @param aDatabaseUri The URI of the database to be updated.
	 */
	IMPORT_C void UpdateItemL( TPosLmDatabaseSettings aSettings,
			const TDesC& aDatabaseUri = KNullDesC );

	/**
	 * LandmarkLC.
	 * Retrieves a Landmark from the database.
	 * @param aLandmarkId Id of the landmark to be retrieved.
	 * @param aDatabaseUri The URI of the database from which the CPosLandmark
	 * instance should be retrieved.
	 * @return A pointer to CPosLandmark instance.
	 */
	IMPORT_C CPosLandmark* LandmarkLC( const TPosLmItemId& aLandmarkId,
			const TDesC& aDatabaseUri = KNullDesC ) const;

	/**
	 * CategoryLC.
	 * Retrieves a Landmark category from the database.
	 * @param aCategoryId Id of the landmark category to be retrieved.
	 * @param aDatabaseUri The URI of the database from which the CPosLandmarkCategory
	 * instance should be retrieved.
	 * @return A pointer to CPosLandmarkCategory instance.
	 */
	IMPORT_C CPosLandmarkCategory* CategoryLC( const TPosLmItemId& aCategoryId,
			const TDesC& aDatabaseUri = KNullDesC ) const;

	/**
	 * RemoveItemL.
	 * Removes a Landmark/Landmark category from given database.
	 * @param aItemId The id of the Landmark/Landmark category to be removed.
	 * @param aItemIsLandmark Whether id passed is a landmark id or a category id.
	 * @param aDatabaseUri The URI of the database from which the 
	 * Landmark/Landmark category is to be removed.
	 */
	IMPORT_C void RemoveItemL( TPosLmItemId aItemId, TPosItem aItemIsLandmark,
			const TDesC& aDatabaseUri = KNullDesC );

	/**
	 * RemoveItemL.
	 * Removes the given database.
	 * @param aDatabaseUri The URI of the database to be removed from terminal.
	 */
	IMPORT_C void RemoveItemL( const TDesC& aDatabaseUri );

	/**
	 * SetActiveL.
	 * Sets specified database as an active database.
	 * @param aDatabaseUri The URI of the database to be set as an active database.
	 */
	IMPORT_C void SetActiveL( const TDesC& aDatabaseUri );

	/**
	 * LinkCategoryToLandmarksL.
	 * Associates a category with a set of landmarks.
	 * @param aCategoryId The id of category.
	 * @param aLandmarkIdArray The array of landmark ids to which the 
	 * category is to be associated.
	 * @param aDatabaseUri The URI of the database in which the landmarks and category exist.
	 */
	IMPORT_C void LinkCategoryToLandmarksL( TPosLmItemId aCategoryId,
			RArray< TPosLmItemId >& aLandmarkIdArray,
			const TDesC& aDatabaseUri = KNullDesC );

	/**
	 * UnlinkCategoryToLandmarksL.
	 * Dissociates a category with a set of landmarks.
	 * @param aCategoryId The id of category.
	 * @param aLandmarkIdArray The array of landmark ids to which the 
	 * category is to be dissociated.
	 * @param aDatabaseUri The URI of the database in which the landmarks and category exist.
	 */
	IMPORT_C void UnlinkCategoryToLandmarksL( TPosLmItemId aCategoryId,
			RArray< TPosLmItemId >& aLandmarkIdArray,
			const TDesC& aDatabaseUri = KNullDesC );

	/**
	 * RegisterObserver.
	 * Registers an observer for Asynchronous call backs.
	 * @param aObserver A pointer to a concrete MLandmarkObserver instance.
	 */
	IMPORT_C void RegisterObserver( MLandmarkObserver* aObserver );

	/**
	 * Cancel.
	 * Cancels an ongoing asynchronous request.
	 * @param aTransactionId The transaction id of the asynchronous request.
	 */
	IMPORT_C void Cancel( TInt32 aTransactionId ) const;

	/**
	 * GetDefaultDbUri.
	 * Gets the URI of the default database.
	 * @param aDefaultDbUri A reference to the URI of the default database.				
	 */
	IMPORT_C void GetDefaultDbUriL( TPtrC& aDefaultDbUri ) const;

private:// helper functions

	/**
	 * GetDbTypeFromUri.
	 * Gets the type of database.
	 * @param aDatabaseUri The URI of the database whose information is queried.
	 * @return Error.
	 */
	TDatabaseType GetDbTypeFromUri ( const TDesC& aDbUri ) const;

private: // Constructors

	/**
	 * ConstructL
	 * 2nd phase constructor.
	 * Perform the second phase construction of a
	 * CLandmarkService object.
	 */
	void ConstructL();

	/**
	 * CLandmarkService.
	 * C++ default constructor.
	 */
	CLandmarkService();

private: // Data members

	/**
	 * iManageHandler
	 * CPosLmManageHandler instance.
	 */
	CLandmarkManageHandlers* iManageHandler;

	/**
	 * iDatabaseManager
	 * CPosLmDatabaseManager instance.
	 */
	CPosLmDatabaseManager* iDatabaseManager;

	/**
	 * iObserver
	 * MLandmarkObserver instance.
	 */
	MLandmarkObserver* iObserver;

	/**
	 * iManageObjects
	 * CLandmarkManageObjects instance.
	 */
	CLandmarkManageObjects* iManageObjects;

#ifdef _DEBUG
	RFileLogger iLog;
#endif		
	};

#endif // __CLANDMARKSERVICE_H__

// End of File

