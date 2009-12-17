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
* Description:  CLandmarkManageHandlers class implementation
 *
*/


#include <EPos_CPosLandmarkDatabase.h>
#include <EPos_CPosLmCategoryManager.h>
#include <EPos_CPosLandmarkSearch.h>
#include <EPos_TPosLmDatabaseSettings.h>
#include "clandmarkmanagehandlers.h"

//class CLandmarkManageHandlers
// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CLandmarkManageHandlers::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CLandmarkManageHandlers* CLandmarkManageHandlers::NewL( )
	{
	CLandmarkManageHandlers* self = new (ELeave) CLandmarkManageHandlers();
	return self;
	}

// -----------------------------------------------------------------------------
// CLandmarkManageHandlers::CLandmarkManageHandlers()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CLandmarkManageHandlers::CLandmarkManageHandlers( )
	{
	}

// -----------------------------------------------------------------------------
// CLandmarkManageHandlers::~CLandmarkManageHandlers()
// Destructor.
// -----------------------------------------------------------------------------
//
CLandmarkManageHandlers::~CLandmarkManageHandlers( )
	{
    TInt count = iHandlers.Count();
    for (TInt i = 0; i < count; i++)
        {
        if (!iHandlers[i]->DecRef())
            {
            delete iHandlers[i];
            }
        }
	iHandlers.Close();
	}

// -----------------------------------------------------------------------------
// CLandmarkManageHandlers::CloseHandler( CLandmarkHandler* aHandler )
// Closes the passed CLandmarkHandler handle and removes it from the array.
// -----------------------------------------------------------------------------
//
void CLandmarkManageHandlers::CloseHandler( CLandmarkHandler* aHandler )
	{
	TInt index = iHandlers.Find (aHandler );
	if ( index != KErrNotFound )
		{
        if (!iHandlers[index]->DecRef())
            {
            delete iHandlers[index];
            }
		iHandlers[index] = NULL;
		iHandlers.Remove (index );
		}
	}
// -----------------------------------------------------------------------------
// CLandmarkManageHandlers::CreateHandlerL(TDesC & aDatabaseUri)
// Creates and Returns the handle of CLandmarkHandler instance.
// -----------------------------------------------------------------------------
//
CLandmarkHandler* CLandmarkManageHandlers::CreateHandlerL(
		const TDesC& aDatabaseUri )
	{
	//create a database handle and append to the array.
	CLandmarkHandler* handler = CLandmarkHandler::CreateL (aDatabaseUri );
	CleanupStack::PushL (handler );
	iHandlers.AppendL (handler );
	CleanupStack::Pop (handler );
	//if there is no default handler then set default as device default
	if( !iDefaultHandler && aDatabaseUri == KNullDesC )
		{
		iDefaultHandler = handler;
		}
	return handler;
	}

// -----------------------------------------------------------------------------
// CLandmarkManageHandlers::GetHandlerL(TDesC & aDatabaseUri)
// Returns the handle of CLandmarkHandler instance.
// -----------------------------------------------------------------------------
//
CLandmarkHandler* CLandmarkManageHandlers::GetHandlerL(const TDesC& aDatabaseUri )
	{
	_LIT(KDriveSeparatorSymbol, ":");
	_LIT(KDefaultDriveLocal, "c");
	_LIT(KProtocolSeparatorLocal, "://");
	_LIT(KLocalProtocolString, "file");

	CLandmarkHandler* handler=  NULL;
	//if aDatabaseUri is KNullDesC then return the default handler
	if ( aDatabaseUri == KNullDesC )
		{
		if ( iDefaultHandler )
			{
			iDefaultHandler->InitL ( );
			}
		handler = iDefaultHandler;
		}
	//else compare the passed URI with the stored handle's URI
	else
		{
		//Simple parsing. Have to implement better parsing
		TBuf<KPosLmDatabaseName> dbName;
		TInt offset = aDatabaseUri.Find (KProtocolSeparatorLocal );
		if ( KErrNotFound == offset )
			{
			dbName.Copy (KLocalProtocolString );
			dbName.Append (KProtocolSeparatorLocal );
			}
		if ( aDatabaseUri.Find (KDriveSeparatorSymbol )<= offset )
			{
			dbName.Append (KDefaultDriveLocal );
			dbName.Append (KDriveSeparatorSymbol );
			}
		//Check for Length < KPosLmDatabaseName
		if ( (aDatabaseUri.Length() + dbName.Length()) > KPosLmDatabaseName )
			{
			User::Leave ( KErrBadName );
			}
		//create the complete db uri
		dbName.Append (aDatabaseUri );
		//normalize to lower
		dbName.LowerCase ( );
		TInt count = iHandlers.Count ( );
		TPtrC dbUri;
		while ( count )
			{
			//Retrieve the handles from end
			handler = iHandlers[--count];
			handler->GetDatabaseUri (dbUri );
			if ( dbUri == dbName )
				{
				handler->InitL ( );
				break;
				}
			//if no handle found then NULL
			handler = NULL;
			}
		}
	return handler;
	}

// -----------------------------------------------------------------------------
// CLandmarkManageHandlers::SetDefaultHandler(CLandmarkHandler* aHandler)
// Sets the default handler.
// -----------------------------------------------------------------------------
//
void CLandmarkManageHandlers::SetDefaultHandler( CLandmarkHandler* aHandler )
	{
	iDefaultHandler = aHandler;
	}

//Class CLandmarkHandler
// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CLandmarkHandler::CreateL( TDesC & aDatabaseUri )
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CLandmarkHandler* CLandmarkHandler::CreateL( const TDesC& aDatabaseUri )
	{
	CLandmarkHandler* self = new (ELeave) CLandmarkHandler();
	CleanupStack::PushL ( self );
	self->ConstructL (aDatabaseUri );
	CleanupStack::Pop ( self );
	return self;
	}

// -----------------------------------------------------------------------------
// CLandmarkHandler::ConstructL( TDesC & aDatabaseUri )
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CLandmarkHandler::ConstructL( const TDesC& aDatabaseUri )
	{
	//Open default database or the database requested depending on paramater aDatabaseUri
	if ( aDatabaseUri != KNullDesC )
		{
		iLandmarkDatabaseHandle = CPosLandmarkDatabase::OpenL (aDatabaseUri );
		}
	else
		{
		iLandmarkDatabaseHandle = CPosLandmarkDatabase::OpenL ( );
		}
	iDatabaseUri = iLandmarkDatabaseHandle->DatabaseUriLC ( );
	CleanupStack::Pop (iDatabaseUri );
	//Normalize to lower
	iDatabaseUri->Des().LowerCase ( );
	//initialize the database for further opertaions on the database.
	ExecuteAndDeleteLD (iLandmarkDatabaseHandle->InitializeL ( ) );
	//Create other handles with respect to the open database
	iLmCategoryManagerHandle = CPosLmCategoryManager::NewL (*iLandmarkDatabaseHandle );
	iLandmarkSearchHandle = CPosLandmarkSearch::NewL (*iLandmarkDatabaseHandle );
    IncRef();
	}

// -----------------------------------------------------------------------------
// CLandmarkHandler::CLandmarkHandler()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CLandmarkHandler::CLandmarkHandler( )
	{
	}

// -----------------------------------------------------------------------------
// CLandmarkHandler::~CLandmarkHandler()
// Destructor.
// -----------------------------------------------------------------------------
//
CLandmarkHandler::~CLandmarkHandler( )
	{
	delete iLandmarkSearchHandle;
	delete iLmCategoryManagerHandle;
	delete iLandmarkDatabaseHandle;
	delete iDatabaseUri;
	}

// -----------------------------------------------------------------------------
// CLandmarkHandler::InitL()
// Initialize the databse if required.
// -----------------------------------------------------------------------------
//
void CLandmarkHandler::InitL( )
	{
	if (iLandmarkDatabaseHandle->IsInitializingNeeded ( ) )
		{
		//Initialize the database for further opertaions on the database.
		ExecuteAndDeleteLD (iLandmarkDatabaseHandle->InitializeL ( ) );
		}
	}

// End of File
