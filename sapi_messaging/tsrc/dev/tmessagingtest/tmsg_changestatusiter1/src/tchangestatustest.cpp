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
#include <e32base.h>
#include <msvstd.h>
#include <msvapi.h>
#include <msvids.h>

#include <Stiftestinterface.h>
//#include <SAPI_TEST\testprg.h>
#include "messageheader.h"
#include "messagingservice.h"

#include "tchangestatustest.h"
//#include <SAPI_TEST\testprg.h>



// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTSendMessageTest::CTSendMessageTest
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CTChangeStatusTest::CTChangeStatusTest( 
    CTestModuleIf& aTestModuleIf ):
        CScriptBase( aTestModuleIf )
    {
    
    }

// -----------------------------------------------------------------------------
// CTSendMessageTest::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CTChangeStatusTest::ConstructL()
    {
    //iLog = CStifLogger::NewL( KTMsgTestLogPath, 
      //                    KTMsgTestLogFile,
        //                  CStifLogger::ETxt,
          //                CStifLogger::EFile,
            //              EFalse );
    
                         

    }

// -----------------------------------------------------------------------------
// CTSendMessageTest::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CTChangeStatusTest* CTChangeStatusTest::NewL( 
    CTestModuleIf& aTestModuleIf )
    {
    CTChangeStatusTest* self = new (ELeave) CTChangeStatusTest( aTestModuleIf );

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();

    return self;

    }

// Destructor
CTChangeStatusTest::~CTChangeStatusTest()
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

    return ( CScriptBase* ) CTChangeStatusTest::NewL( aTestModuleIf );

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
