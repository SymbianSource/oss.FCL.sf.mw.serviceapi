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
* Description:   Tests sysinfo connectivity information
*
*/




// INCLUDE FILES
#include <Stiftestinterface.h>
#include "tsysconnectivity.h"

// EXTERNAL DATA STRUCTURES
//extern  ?external_data;

// EXTERNAL FUNCTION PROTOTYPES  
//extern ?external_function( ?arg_type,?arg_type );

// CONSTANTS
//const ?type ?constant_var = ?constant;

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
// Ctsysconnectivity::Ctsysconnectivity
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
Ctsysconnectivity::Ctsysconnectivity( 
    CTestModuleIf& aTestModuleIf ):
        CScriptBase( aTestModuleIf )
    {
    }

// -----------------------------------------------------------------------------
// Ctsysconnectivity::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void Ctsysconnectivity::ConstructL()
    {
    iLog = CStifLogger::NewL( KtsysconnectivityLogPath, 
                          KtsysconnectivityLogFile,
                          CStifLogger::ETxt,
                          CStifLogger::EFile,
                          EFalse );

	if (!iFeatureManagerInitialized)
		{
		FeatureManager::InitializeLibL();
		iFeatureManagerInitialized = ETrue;
		}

    }

// -----------------------------------------------------------------------------
// Ctsysconnectivity::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
Ctsysconnectivity* Ctsysconnectivity::NewL( 
    CTestModuleIf& aTestModuleIf )
    {
    Ctsysconnectivity* self = new (ELeave) Ctsysconnectivity( aTestModuleIf );

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();

    return self;

    }

// Destructor
Ctsysconnectivity::~Ctsysconnectivity()
    { 

    // Delete resources allocated from test methods
    Delete();
	if(iFeatureManagerInitialized)
		FeatureManager::UnInitializeLib();
	
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

    return ( CScriptBase* ) Ctsysconnectivity::NewL( aTestModuleIf );

    }


//  End of File
