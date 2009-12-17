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
* Description:  CLandmarkManageHandlers class
 *
*/


#ifndef __CLANDMARKMANAGEHANDLERS_H__
#define __CLANDMARKMANAGEHANDLERS_H__

// INCLUDES
#include <e32base.h>
#include <e32cmn.h>

//FORWARD DECLARARTION
class CPosLandmarkDatabase;
class CPosLmCategoryManager;
class CPosLandmarkSearch;
class CLandmarkHandler;

/**
 * CLandmarkManageHandlers
 * This class maintains a list of handles to different databases.
 */
// CLASS DECLARATION
NONSHARABLE_CLASS(CLandmarkManageHandlers): public CBase
	{
public: // New methods

	/**
	 * NewL.
	 * Two-phased constructor.
	 * Create a CPosLmManageHandle object.	
	 * @return A pointer to the newly created instance of CLandmarkManageHandlers.	
	 */
	static CLandmarkManageHandlers* NewL();

	/**
	 * ~CPosLmManageHandle
	 * Destructor.
	 */
	~CLandmarkManageHandlers();

public: // Functions to create, return and destroy handle

	/**
	 * CreateHandlerL
	 * This creates and returns CLandmarkHandler instance.
	 * @param aDatabaseUri The URI of the database to be opened.
	 * @return A pointer to the newly created instance of CLandmarkHandler.
	 */
	CLandmarkHandler* CreateHandlerL( const TDesC& aDatabaseUri );

	/**
	 * GetHandlerL
	 * This returns CLandmarkHandler instance.
	 * @param aDatabaseUri The URI of the database to be opened.
	 * @return A pointer to an existing instance of CLandmarkHandler.
	 */
	CLandmarkHandler* GetHandlerL( const TDesC& aDatabaseUri );

	/**
	 * CloseHandler
	 * This destroys CLandmarkHandler instance.
	 * @param aHandler The CLandmarkHandler instance to be destroyed.
	 */
	void CloseHandler( CLandmarkHandler* aHandler );

	/**
	 * SetDefaultHandler
	 * This changes the default handle managed by this class.
	 * @param aHandler The CLandmarkHandler instance to be set as default.
	 */
	void SetDefaultHandler( CLandmarkHandler* aHandler );

private: // Constructors

	/**
	 * CLandmarkManageHandlers.
	 * C++ default constructor.
	 */
	CLandmarkManageHandlers();

private: // Data members

	/**
	 * iHandlers
	 * Array of CLandmarkHandler instances to all open databases.
	 */
	RPointerArray <CLandmarkHandler> iHandlers;

	/**
	 * iDefaultHandler
	 * CLandmarkHandler instance to the default database.
	 */
	CLandmarkHandler* iDefaultHandler;
	};

/**
 * CLandmarkHandler
 * This class maintains a handle to an open database as well as the CPosLmCategoryManager
 * handle and CPosLandmarkSearch handle associated with the CPosLandmarkDatabase
 * database.
 */
// CLASS DECLARATION
NONSHARABLE_CLASS(CLandmarkHandler): public CBase
	{
public: // New methods

	/**
	 * CreateL.
	 * Two-phased constructor.
	 * Create a CLandmarkHandler object.
	 * @param aDatabaseUri The URI of the database to be opened.
	 * @return A pointer to the created instance of CLandmarkHandler.
	 */
	static CLandmarkHandler* CreateL( const TDesC& aDatabaseUri );

	
	TInt DecRef();
	
	void IncRef();
	
	/**
	 * ~CLandmarkHandler
	 * Destructor.
	 */
	~CLandmarkHandler();

public: // Functions to retrieve data members

	/**
	 * LandmarkDatabaseHandle.
	 * @return The handle to CPosLandmarkDatabase instance.
	 */
	inline CPosLandmarkDatabase* LandmarkDatabaseHandle ();

	/**
	 * CategoryManagerHandle.
	 * @return The handle to CPosLmCategoryManager instance.
	 */
	inline CPosLmCategoryManager* CategoryManagerHandle ();

	/**
	 * LandmarkSearchHandle.
	 * @return The handle to CPosLandmarkSearch instance.
	 */
	inline CPosLandmarkSearch* LandmarkSearchHandle ();

	/**
	 * GetDatabaseUri.
	 * @param aDatabaseUri The URI of the open CPosLandmarkDatabase.
	 */
	inline void GetDatabaseUri( TPtrC& aDatabaseUri ) const;

	/**
	 * InitL.
	 * This initializes the CPosLandmarkDatabase if required.
	 */
	void InitL();

private: // Constructors

	/**
	 * ConstructL
	 * 2nd phase constructor.
	 * Perform the second phase construction of a
	 * CLandmarkHandler object.
	 * @param aDatabaseUri The URI of the CPosLandmarkDatabase to be opened.
	 */
	void ConstructL(const TDesC& aDatabaseUri);

	/**
	 * CLandmarkHandler.
	 * C++ default constructor.
	 */
	CLandmarkHandler();

private: // Data members

	/**
	 * iDatabaseUri
	 * The URI of the open CPosLandmarkDatabase.
	 */
	HBufC* iDatabaseUri;

	/**
	 * iLandmarkDatabaseHandle
	 * The handle to the open CPosLandmarkDatabase.
	 */
	CPosLandmarkDatabase* iLandmarkDatabaseHandle;

	/**
	 * iLmCategoryManagerHandle
	 * The handle to the CPosLmCategoryManager of the database.
	 */
	CPosLmCategoryManager* iLmCategoryManagerHandle;

	/**
	 * iLandmarkSearchHandle
	 * The handle to the CPosLandmarkSearch of the database.
	 */
	CPosLandmarkSearch* iLandmarkSearchHandle;
	TInt iRefCount;
	};

#include "clandmarkhandler.inl"

#endif // __CLANDMARKMANAGEHANDLERS_H__

// End of File
