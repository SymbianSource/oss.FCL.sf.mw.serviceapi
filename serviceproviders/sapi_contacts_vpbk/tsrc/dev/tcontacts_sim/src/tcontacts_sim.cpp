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
#include <StifTestInterface.h>



#include "tcontactssim.h"


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CContactsUT::CContactsUT
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CContactsUT::CContactsUT(CTestModuleIf& aTestModuleIf ):
        CScriptBase( aTestModuleIf )
        {
	    }

// -----------------------------------------------------------------------------
// CContactsUT::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CContactsUT::ConstructL()
    {
    iLog = CStifLogger::NewL( KContactsUTLogPath, 
                          KContactsUTLogFile,
                          CStifLogger::ETxt,
                          CStifLogger::EFile,
                          EFalse );
    
  
    }

// -----------------------------------------------------------------------------
// CContactsUT::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CContactsUT* CContactsUT::NewL( 
    CTestModuleIf& aTestModuleIf )
    {
    CContactsUT* self = new (ELeave) CContactsUT( aTestModuleIf );

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();

    return self;

    }

// Destructor
CContactsUT::~CContactsUT()
    { 

    // Delete resources allocated from test methods
  delete iLog ;

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

    return ( CScriptBase* ) CContactsUT::NewL( aTestModuleIf );

    }


//  End of File
