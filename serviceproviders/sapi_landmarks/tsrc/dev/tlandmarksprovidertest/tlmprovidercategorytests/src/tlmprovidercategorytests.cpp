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
#include "tlmprovidercategorytests.h"
#include "landmarkliwparams.hrh"

_LIT(KDefaultDatabase,"c:default.ldb");

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTLmCategoryTests::CTLmCategoryTests
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//

CTLmCategoryTests::CTLmCategoryTests( 
    CTestModuleIf& aTestModuleIf ):
        CScriptBase( aTestModuleIf )//,iObserver(NULL)
    {

    }

// -----------------------------------------------------------------------------
// CTLmCategoryTests::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CTLmCategoryTests::ConstructL()
    {
    iLog = CStifLogger::NewL( KTLocTestLogPath, 
                          KTLocTestLogFile,
                          CStifLogger::ETxt,
                          CStifLogger::EFile,
                          EFalse );
	iLog->Log( _L("CTLmCategoryTests::ConstructL" ));
	iDatabaseManager = CPosLmDatabaseManager::NewL();
 	DeleteAllLocalDatabasesL();  	

	HPosLmDatabaseInfo*	 dbInfo	=	HPosLmDatabaseInfo::NewLC(KDefaultDatabase);
	iDatabaseManager-> CreateDatabaseL(*dbInfo);
	CleanupStack::PopAndDestroy(dbInfo);

	iLog->Log( _L("End of CTLmCategoryTests::ConstructL" ));
    }

// -----------------------------------------------------------------------------
// CTLmCategoryTests::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CTLmCategoryTests* CTLmCategoryTests::NewL( 
    CTestModuleIf& aTestModuleIf )
    {
    CTLmCategoryTests* self = new (ELeave) CTLmCategoryTests( aTestModuleIf );

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();
    return self;
    }

// Destructor
CTLmCategoryTests::~CTLmCategoryTests()
    { 
	iLog->Log( _L("In ~CTLmCategoryTests" ));
	iLog->Log( _L("~CTLmCategoryTests:deleting databasemanager" ));
	delete iDatabaseManager;
	ReleaseLandmarkResources ();
	iLog->Log( _L("~CTLmCategoryTests:Closing iLog" ));
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

    return ( CScriptBase* ) CTLmCategoryTests::NewL( aTestModuleIf );

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
