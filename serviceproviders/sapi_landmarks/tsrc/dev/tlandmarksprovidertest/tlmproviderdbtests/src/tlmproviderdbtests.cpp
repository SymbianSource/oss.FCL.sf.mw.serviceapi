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
#include <EPos_Landmarks.h>
#include <EPos_HPosLmDatabaseInfo.h> 
#include <EPos_CPosLmDatabaseManager.h> 
#include <liwcommon.h>
#include <liwservicehandler.h>
#include "tlmproviderdbtests.h"
#include "landmarkliwparams.hrh"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTLmDbTests::CTLmDbTests
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//

CTLmDbTests::CTLmDbTests( 
    CTestModuleIf& aTestModuleIf ):
        CScriptBase( aTestModuleIf )//,iObserver(NULL)
    {
    
    }

// -----------------------------------------------------------------------------
// CTLmDbTests::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CTLmDbTests::ConstructL()
    {
    iLog = CStifLogger::NewL( KTLocTestLogPath, 
                          KTLocTestLogFile,
                          CStifLogger::ETxt,
                          CStifLogger::EFile,
                          EFalse );
    CleanupStack::PushL (iLog);

	iLog->Log(_L("In CTLmDbTests::ConstructL"));
	iDatabaseManager = CPosLmDatabaseManager::NewL();
	

	
  	CleanupStack::Pop (iLog);
	iLog->Log(_L("End of CTLmDbTests::ConstructL"));
    }

// -----------------------------------------------------------------------------
// CTLmDbTests::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CTLmDbTests* CTLmDbTests::NewL( 
    CTestModuleIf& aTestModuleIf )
    {
    CTLmDbTests* self = new (ELeave) CTLmDbTests( aTestModuleIf );

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();

    return self;

    }

// Destructor
CTLmDbTests::~CTLmDbTests()
    { 
	iLog->Log( _L("In ~CTLmDbTests" ));
	delete iDatabaseManager;
	ReleaseLandmarkResources ();
	iLog->Log( _L("CTLmDbTests destructor:deleting iLog" ));
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

    return ( CScriptBase* ) CTLmDbTests::NewL( aTestModuleIf );

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
