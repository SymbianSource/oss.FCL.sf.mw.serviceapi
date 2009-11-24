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
#include <liwcommon.h>
#include <liwservicehandler.h>
 
#include "sensrprovidertest.h"






// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CSensrProviderTest::CSensrProviderTest
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CSensrProviderTest::CSensrProviderTest( 
    CTestModuleIf& aTestModuleIf ):
        CScriptBase( aTestModuleIf )
    {
    }

// -----------------------------------------------------------------------------
// CSensrProviderTest::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CSensrProviderTest::ConstructL()
    {
    iLog = CStifLogger::NewL( KTSensrProviderLogPath, 
                          KTSensrProviderLogFile,
                          CStifLogger::ETxt,
                          CStifLogger::ERDebug,
                          EFalse );
                          
		
    
    }

// -----------------------------------------------------------------------------
// CSensrProviderTest::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CSensrProviderTest* CSensrProviderTest::NewL( 
    CTestModuleIf& aTestModuleIf )
    {
    CSensrProviderTest* self = new (ELeave) CSensrProviderTest( aTestModuleIf );

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();

    return self;

    }

// Destructor
CSensrProviderTest::~CSensrProviderTest()
    {
    // Delete resources allocated from test methods
    Delete();

    // Delete logger
    delete iLog; 
	

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

    return ( CScriptBase* ) CSensrProviderTest::NewL( aTestModuleIf );

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
