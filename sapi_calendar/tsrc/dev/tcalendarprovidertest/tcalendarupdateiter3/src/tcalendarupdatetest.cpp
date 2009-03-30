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
//#include <msvstd.h>
//#include <msvapi.h>
//#include <msvids.h>

#include <Stiftestinterface.h>

#include "tcalendarupdatetest.h"
#include "teststartconsolealarmserver2.h"

void StartAlarmServerL();
/*#if __WINS__
const TUid KServerUid2={0x1000008D};
const TUid KServerUid3={0x101F502A};
_LIT(KConsoleAlarmAlertServerImg,"ConsoleAlarmAlertServer");	
void StartAlarmServerL()
	{
	// Have to start the alarm alert server otherwise the alarm
	// server cannot start.
	const TUidType serverUid(KNullUid,KServerUid2,KServerUid3);
	TBuf<256> cmdline;
	for (TInt i = 0 ; i < 100 ; i++)
		{
        cmdline.Append('a');
		}

	RProcess server;
	TInt ret = 0;
	ret = server.Create(KConsoleAlarmAlertServerImg,cmdline,serverUid);
	TRequestStatus stat;
	server.Rendezvous(stat);
	if (stat!=KRequestPending)
		{
		server.Kill(0);		// abort startup
		}
	else
		{
		server.Resume();	// logon OK - start the server
		}
	}
#endif */   
//#include <SAPI_TEST\testprg.h>



// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTCalendarUpdateTest::CTCalendarUpdateTest
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CTCalendarUpdateTest::CTCalendarUpdateTest( 
    CTestModuleIf& aTestModuleIf ):
        CScriptBase( aTestModuleIf )
    {
    
    }

// -----------------------------------------------------------------------------
// CTCalendarUpdateTest::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CTCalendarUpdateTest::ConstructL()
    {
    }

// -----------------------------------------------------------------------------
// CTCalendarUpdateTest::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CTCalendarUpdateTest* CTCalendarUpdateTest::NewL( 
    CTestModuleIf& aTestModuleIf )
    {
#if __WINS__
    StartAlarmServerL();
#endif    
    CTCalendarUpdateTest* self = new (ELeave) CTCalendarUpdateTest( aTestModuleIf );

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();

    return self;

    }

// Destructor
CTCalendarUpdateTest::~CTCalendarUpdateTest()
    { 

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

    return ( CScriptBase* ) CTCalendarUpdateTest::NewL( aTestModuleIf );

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
