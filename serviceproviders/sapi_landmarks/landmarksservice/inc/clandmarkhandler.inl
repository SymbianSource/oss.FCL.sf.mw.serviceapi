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

// -----------------------------------------------------------------------------
// CLandmarkHandler::LandmarkDatabaseHandle()
// Returns the handle to CPosLandmarkDatabase instance.
// -----------------------------------------------------------------------------
//
inline CPosLandmarkDatabase* CLandmarkHandler::LandmarkDatabaseHandle( )
	{
	return iLandmarkDatabaseHandle;
	}

// -----------------------------------------------------------------------------
// CLandmarkHandler::CategoryManagerHandle()
// Returns the handle to CPosLmCategoryManager instance.
// -----------------------------------------------------------------------------
//
inline CPosLmCategoryManager* CLandmarkHandler::CategoryManagerHandle( )
	{
	return iLmCategoryManagerHandle;
	}

// -----------------------------------------------------------------------------
// CLandmarkHandler::LandmarkSearchHandle()
// Returns the handle to CPosLandmarkSearch instance.
// -----------------------------------------------------------------------------
//
inline CPosLandmarkSearch* CLandmarkHandler::LandmarkSearchHandle( )
	{
	return iLandmarkSearchHandle;
	}

// -----------------------------------------------------------------------------
// CLandmarkHandler::GetDatabaseUri( TPtrC& aDatabaseUri )
// Sets the URI of the landmark database.
// -----------------------------------------------------------------------------
//
inline void CLandmarkHandler::GetDatabaseUri( TPtrC& aDatabaseUri ) const
	{
	aDatabaseUri.Set (iDatabaseUri->Des ( ) );
	}
inline TInt CLandmarkHandler::DecRef() 
    {
    iRefCount--;
    return iRefCount;
    
    }

inline void CLandmarkHandler::IncRef() 
    {
    iRefCount++;
    }
