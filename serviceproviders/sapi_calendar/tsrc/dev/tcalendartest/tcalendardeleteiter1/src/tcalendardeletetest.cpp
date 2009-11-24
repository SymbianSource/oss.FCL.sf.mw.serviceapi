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

#include <StifTestInterface.h>

#include "tcalendardeletetest.h"

extern void StartAlarmServerL();



// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTSendMessageTest::CTSendMessageTest
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CTCalendarDeleteTest::CTCalendarDeleteTest( 
    CTestModuleIf& aTestModuleIf ):
        CScriptBase( aTestModuleIf )
    {
    
    }

// -----------------------------------------------------------------------------
// CTSendMessageTest::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CTCalendarDeleteTest::ConstructL()
    {
    TInt count;
    count = User::CountAllocCells();                     
	#if __WINS__
	    StartAlarmServerL();
	#endif    
    }

// -----------------------------------------------------------------------------
// CTSendMessageTest::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CTCalendarDeleteTest* CTCalendarDeleteTest::NewL( 
    CTestModuleIf& aTestModuleIf )
    {
    CTCalendarDeleteTest* self = new (ELeave) CTCalendarDeleteTest( aTestModuleIf );

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();

    return self;

    }

// Destructor
CTCalendarDeleteTest::~CTCalendarDeleteTest()
    { 
	#if __WINS__
//.	    StopAlarmServerL( iAlarmId );
	#endif    
	
    TInt count;
    count = User::CountAllocCells();                     
	
    // Delete resources allocated from test methods
    Delete();
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

    return ( CScriptBase* ) CTCalendarDeleteTest::NewL( aTestModuleIf );

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
