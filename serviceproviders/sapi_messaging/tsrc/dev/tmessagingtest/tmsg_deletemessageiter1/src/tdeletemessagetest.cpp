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
//#include <SAPI_TEST\testprg.h>
//#include <sendmessage.h>
//#include<messagenotify.h>
#include "tdeletemessagetest.h"
//#include <SAPI_TEST\testprg.h>



// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTDeleteMessageTest::CTDeleteMessageTest
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CTDeleteMessageTest::CTDeleteMessageTest( 
    CTestModuleIf& aTestModuleIf ):
        CScriptBase( aTestModuleIf )
    {
    
    }

// -----------------------------------------------------------------------------
// CTDeleteMessageTest::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CTDeleteMessageTest::ConstructL()
    {
    //iLog = CStifLogger::NewL( KTMsgTestLogPath, 
      //                    KTMsgTestLogFile,
        //                  CStifLogger::ETxt,
          //                CStifLogger::EFile,
            //              EFalse );
    
                         

    }

// -----------------------------------------------------------------------------
// CTDeleteMessageTest::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CTDeleteMessageTest* CTDeleteMessageTest::NewL( 
    CTestModuleIf& aTestModuleIf )
    {
    CTDeleteMessageTest* self = new (ELeave) CTDeleteMessageTest( aTestModuleIf );

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();

    return self;

    }

// Destructor
CTDeleteMessageTest::~CTDeleteMessageTest()
    { 

    // Delete resources allocated from test methods
    Delete();

    // Delete logger
    //delete iLog; 
    ;

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

    return ( CScriptBase* ) CTDeleteMessageTest::NewL( aTestModuleIf );

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
