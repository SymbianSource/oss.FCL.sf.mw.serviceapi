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
* Description:  ?Description
*
*/



// INCLUDE FILES
#include <StifTestInterface.h>
#include "tmediaprovidertesting.h"
#include <SettingServerClient.h>




// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctmediaprovidertesting::Ctmediaprovidertesting
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
Ctmediaprovidertesting::Ctmediaprovidertesting( 
    CTestModuleIf& aTestModuleIf ):
        CScriptBase(aTestModuleIf),
        iExpErrorCode(-1),
        iResult(-2),
        iInList(NULL),
        iOutList(NULL),
        iServicehandler(NULL),
        iIface(NULL),
        iFiletype(EOtherFile),
        iNumberApiCall(0)
        {
        }

// -----------------------------------------------------------------------------
// Ctmediaprovidertesting::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void Ctmediaprovidertesting::ConstructL()
    {
    //Read logger settings to check whether test case name is to be
    //appended to log file name.
    RSettingServer settingServer;
    TInt ret = settingServer.Connect();
    if(ret != KErrNone)
        {
        User::Leave(ret);
        }
    // Struct to StifLogger settigs.
    TLoggerSettings loggerSettings; 
    // Parse StifLogger defaults from STIF initialization file.
    ret = settingServer.GetLoggerSettings(loggerSettings);
    if(ret != KErrNone)
        {
        User::Leave(ret);
        } 
    // Close Setting server session
    settingServer.Close();

    TFileName logFileName;
    
    if(loggerSettings.iAddTestCaseTitle)
        {
        TName title;
        TestModuleIf().GetTestCaseTitleL(title);
        logFileName.Format(KtmediaprovidertestingLogFileWithTitle, &title);
        }
    else
        {
        logFileName.Copy(KtmediaprovidertestingLogFile);
        }

    iLog = CStifLogger::NewL( KtmediaprovidertestingLogPath, 
                              logFileName,
                              CStifLogger::ETxt,
                              CStifLogger::EFile,
                              EFalse );
    
    SendTestClassVersion();
    }

// -----------------------------------------------------------------------------
// Ctmediaprovidertesting::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
Ctmediaprovidertesting* Ctmediaprovidertesting::NewL( 
    CTestModuleIf& aTestModuleIf )
    {
    Ctmediaprovidertesting* self = new (ELeave) Ctmediaprovidertesting( aTestModuleIf );

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();

    return self;

    }

// Destructor
Ctmediaprovidertesting::~Ctmediaprovidertesting()
    { 

    // Delete resources allocated from test methods
    Delete();
    // Delete logger
    delete iLog; 

    }

//-----------------------------------------------------------------------------
// Ctmediaprovidertesting::SendTestClassVersion
// Method used to send version of test class
//-----------------------------------------------------------------------------
//
void Ctmediaprovidertesting::SendTestClassVersion()
	{
	TVersion moduleVersion;
	moduleVersion.iMajor = TEST_CLASS_VERSION_MAJOR;
	moduleVersion.iMinor = TEST_CLASS_VERSION_MINOR;
	moduleVersion.iBuild = TEST_CLASS_VERSION_BUILD;
	
	TFileName moduleName;
	moduleName = _L("tmediaprovidertesting.dll");

	TBool newVersionOfMethod = ETrue;
	TestModuleIf().SendTestModuleVersion(moduleVersion, moduleName, newVersionOfMethod);
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
    return ( CScriptBase* ) Ctmediaprovidertesting::NewL( aTestModuleIf );
    }


//  End of File
