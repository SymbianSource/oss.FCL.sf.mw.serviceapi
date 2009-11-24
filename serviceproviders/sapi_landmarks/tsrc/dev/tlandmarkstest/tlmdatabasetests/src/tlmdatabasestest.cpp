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
#include <StifTestInterface.h>
#include "tlmdatabasestest.h"


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTLmDbTest::CTLmDbTest
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CTLmDbTest::CTLmDbTest( 
    CTestModuleIf& aTestModuleIf ):
        CScriptBase( aTestModuleIf )
    {
    
    }

// -----------------------------------------------------------------------------
// CTLmDbTest::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CTLmDbTest::ConstructL()
    {
    iLog = CStifLogger::NewL( KTLocTestLogPath, 
                          KTLocTestLogFile,
                          CStifLogger::ETxt,
                          CStifLogger::EFile,
                          EFalse );
 
    CleanupStack::PushL (iLog);

	iDatabaseManager = CPosLmDatabaseManager::NewL();

	CleanupStack::Pop (iLog);

    }

// -----------------------------------------------------------------------------
// CTLmDbTest::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CTLmDbTest* CTLmDbTest::NewL( 
    CTestModuleIf& aTestModuleIf )
    {
    CTLmDbTest* self = new (ELeave) CTLmDbTest( aTestModuleIf );

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();

    return self;

    }

// Destructor
CTLmDbTest::~CTLmDbTest()
    { 

    // Delete logger
    delete iLog;
	
	delete iDatabaseManager;
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

    return ( CScriptBase* ) CTLmDbTest::NewL( aTestModuleIf );

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
