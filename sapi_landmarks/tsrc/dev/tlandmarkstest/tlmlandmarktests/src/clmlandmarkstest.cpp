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
* Description:   ?Description
*
*/




// INCLUDE FILES
#include <Stiftestinterface.h>
#include "Clmlandmarkstest.h"
#include <epos_cposlandmarkdatabase.h> 


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CClmlandmarkstest::CClmlandmarkstest
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CClmlandmarkstest::CClmlandmarkstest( 
    CTestModuleIf& aTestModuleIf ):
        CScriptBase( aTestModuleIf )
    {
    }

// -----------------------------------------------------------------------------
// CClmlandmarkstest::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CClmlandmarkstest::ConstructL()
    {
    iLog = CStifLogger::NewL( KClmlandmarkstestLogPath, 
                          KClmlandmarkstestLogFile,
                          CStifLogger::ETxt,
                          CStifLogger::EFile,
                          EFalse );
		CleanupStack::PushL (iLog);

		iDatabaseManager = CPosLmDatabaseManager::NewL();
		CleanupStack::PushL(iDatabaseManager);
	
		iDefaultLmHandle	= CPosLandmarkDatabase::OpenL ();
		CleanupStack::PushL(iDefaultLmHandle);
		if ( iDefaultLmHandle->IsInitializingNeeded() ) 
			ExecuteAndDeleteLD(iDefaultLmHandle->InitializeL());
		
		CleanupStack::Pop (3,iLog);
    }

// -----------------------------------------------------------------------------
// CClmlandmarkstest::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CClmlandmarkstest* CClmlandmarkstest::NewL( 
    CTestModuleIf& aTestModuleIf )
    {
    CClmlandmarkstest* self = new (ELeave) CClmlandmarkstest( aTestModuleIf );

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();

    return self;

    }

// Destructor
CClmlandmarkstest::~CClmlandmarkstest()
    { 

    // Delete resources allocated from test methods
    Delete();

    // Delete logger
    delete iLog; 
   	delete iDatabaseManager;
		delete iDefaultLmHandle;

		ReleaseLandmarkResources ();
    }

// ========================== OTHER EXPORTED FUNCTIONS =========================

// -----------------------------------------------------------------------------
// LibEntryL is a polymorphic Dll entry point.
// Returns: CScriptBase: New CScriptBase derived object
// -----------------------------------------------------------------------------
//
EXPORT_C CScriptBase* LibEntryL( 
    CTestModuleIf& aTestModuleIf ) // Backpointer to STIF Test Framework
    {

    return ( CScriptBase* ) CClmlandmarkstest::NewL( aTestModuleIf );

    }

// -----------------------------------------------------------------------------
// E32Dll is a DLL entry point function.
// Returns: KErrNone
// -----------------------------------------------------------------------------
//
#ifndef EKA2 // Hide Dll entry point to EKA2
GLDEF_C TInt E32Dll(
    TDllReason /*aReason*/) // Reason code
    {
    return(KErrNone);

    }
#endif // EKA2

//  End of File
