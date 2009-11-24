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
* Description:  ?Description
*
*/



// INCLUDE FILES
#include <StifTestInterface.h>
#include <liwcommon.h>
#include <liwservicehandler.h>
#include <EPos_Landmarks.h>
#include <EPos_HPosLmDatabaseInfo.h> 
#include <EPos_CPosLmDatabaseManager.h> 
#include "tlandmarkprovider.h"
#include "landmarkliwparams.hrh"

// EXTERNAL DATA STRUCTURES
//extern  ?external_data;

// EXTERNAL FUNCTION PROTOTYPES  
//extern ?external_function( ?arg_type,?arg_type );

// CONSTANTS

// MACROS
//#define ?macro ?macro_def

// LOCAL CONSTANTS AND MACROS
//const ?type ?constant_var = ?constant;
//#define ?macro_name ?macro_def

// MODULE DATA STRUCTURES
//enum ?declaration
//typedef ?declaration

// LOCAL FUNCTION PROTOTYPES
//?type ?function_name( ?arg_type, ?arg_type );

// FORWARD DECLARATIONS
//class ?FORWARD_CLASSNAME;

// ============================= LOCAL FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// ?function_name ?description.
// ?description
// Returns: ?value_1: ?description
//          ?value_n: ?description_line1
//                    ?description_line2
// -----------------------------------------------------------------------------
//
/*
?type ?function_name(
    ?arg_type arg,  // ?description
    ?arg_type arg)  // ?description
    {

    ?code  // ?comment

    // ?comment
    ?code
    }
*/

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTLandmarkProvider::CTLandmarkProvider
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CTLandmarkProvider::CTLandmarkProvider( 
    CTestModuleIf& aTestModuleIf ):
        CScriptBase( aTestModuleIf )
    {
    }

// -----------------------------------------------------------------------------
// CTLandmarkProvider::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CTLandmarkProvider::ConstructL()
    {
    iLog = CStifLogger::NewL( KTLandmarkProviderLogPath, 
                          KTLandmarkProviderLogFile,
                          CStifLogger::ETxt,
                          CStifLogger::EFile,
                          EFalse );
                          
	iDatabaseManager = CPosLmDatabaseManager::NewL();
	DeleteAllLocalDatabasesL();
	HPosLmDatabaseInfo* info = HPosLmDatabaseInfo::NewLC(KTestDbUri);
	iDatabaseManager->CreateDatabaseL (*info);
	CleanupStack::PopAndDestroy(info);
	info = HPosLmDatabaseInfo::NewLC(KTestDbUri1);
	iDatabaseManager->CreateDatabaseL (*info);
	CleanupStack::PopAndDestroy(info);
    }

// -----------------------------------------------------------------------------
// CTLandmarkProvider::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CTLandmarkProvider* CTLandmarkProvider::NewL( 
    CTestModuleIf& aTestModuleIf )
    {
    CTLandmarkProvider* self = new (ELeave) CTLandmarkProvider( aTestModuleIf );

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();

    return self;

    }

// Destructor
CTLandmarkProvider::~CTLandmarkProvider()
    {
    iLog->Log( _L(" deleting iDatabaseManager ...") ); 
	delete iDatabaseManager;
    delete iLog; 
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

    return ( CScriptBase* ) CTLandmarkProvider::NewL( aTestModuleIf );

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
