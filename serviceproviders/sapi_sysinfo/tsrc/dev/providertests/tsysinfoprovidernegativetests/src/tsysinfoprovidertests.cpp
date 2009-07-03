/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
#include "tsysinfoprovidertests.h"


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctsysinfoprovidertests::Ctsysinfoprovidertests
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
Ctsysinfoprovidertests::Ctsysinfoprovidertests( 
    CTestModuleIf& aTestModuleIf ):
        CScriptBase( aTestModuleIf ),iInterface(NULL),iServiceHandler(NULL)
    {
    }

// -----------------------------------------------------------------------------
// Ctsysinfoprovidertests::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void Ctsysinfoprovidertests::ConstructL()
    {
    iLog = CStifLogger::NewL( KtsysinfoprovidertestsLogPath, 
                          KtsysinfoprovidertestsLogFile,
                          CStifLogger::ETxt,
                          CStifLogger::EFile,
                          EFalse );
    }

// -----------------------------------------------------------------------------
// Ctsysinfoprovidertests::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
Ctsysinfoprovidertests* Ctsysinfoprovidertests::NewL( 
    CTestModuleIf& aTestModuleIf )
    {
    Ctsysinfoprovidertests* self = new (ELeave) Ctsysinfoprovidertests( aTestModuleIf );

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();

    return self;

    }

// Destructor
Ctsysinfoprovidertests::~Ctsysinfoprovidertests()
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

    return ( CScriptBase* ) Ctsysinfoprovidertests::NewL( aTestModuleIf );

    }


//  End of File
