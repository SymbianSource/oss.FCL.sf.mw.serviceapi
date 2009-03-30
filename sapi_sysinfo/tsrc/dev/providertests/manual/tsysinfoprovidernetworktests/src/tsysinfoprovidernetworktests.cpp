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
* Description:   tsysinfoprovidernetworktests
*
*/




// INCLUDE FILES
#include <Stiftestinterface.h>
#include "tsysinfoprovidernetworktests.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTSysInfoProviderNetworkTests::CTSysInfoProviderNetworkTests
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CTSysInfoProviderNetworkTests::CTSysInfoProviderNetworkTests( 
    CTestModuleIf& aTestModuleIf ):
        CScriptBase( aTestModuleIf )
    {
    
    }

// -----------------------------------------------------------------------------
// CTSysInfoProviderNetworkTests::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CTSysInfoProviderNetworkTests::ConstructL()
    {
    iLog = CStifLogger::NewL( KTSysNetworkLogPath, 
                          KTSysNetworkLogFile,
                          CStifLogger::ETxt,
                          CStifLogger::EFile,
                          EFalse );
    }

// -----------------------------------------------------------------------------
// CTSysInfoProviderNetworkTests::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CTSysInfoProviderNetworkTests* CTSysInfoProviderNetworkTests::NewL( 
    CTestModuleIf& aTestModuleIf )
    {
    CTSysInfoProviderNetworkTests* self = new (ELeave) CTSysInfoProviderNetworkTests( aTestModuleIf );

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();

    return self;

    }

// Destructor
CTSysInfoProviderNetworkTests::~CTSysInfoProviderNetworkTests()
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

    return ( CScriptBase* ) CTSysInfoProviderNetworkTests::NewL( aTestModuleIf );

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
