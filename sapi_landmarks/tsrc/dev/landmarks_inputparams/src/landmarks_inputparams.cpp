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
#include <Stiftestinterface.h>
#include "landmarks_inputparams.h"
#include <SettingServerClient.h>
#include <LiwServicehandler.h>

using namespace LIW;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Clandmarks_inputparams::Clandmarks_inputparams
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
Clandmarks_inputparams::Clandmarks_inputparams( 
    CTestModuleIf& aTestModuleIf ):
        CScriptBase( aTestModuleIf )
    {
    }

// -----------------------------------------------------------------------------
// Clandmarks_inputparams::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void Clandmarks_inputparams::ConstructL()
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
        logFileName.Format(Klandmarks_inputparamsLogFileWithTitle, &title);
        }
    else
        {
        logFileName.Copy(Klandmarks_inputparamsLogFile);
        }

    iLog = CStifLogger::NewL( Klandmarks_inputparamsLogPath, 
                          logFileName,
                          CStifLogger::ETxt,
                          CStifLogger::EFile,
                          EFalse );
    
    SendTestClassVersion();
    
    }

// -----------------------------------------------------------------------------
// Clandmarks_inputparams::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
Clandmarks_inputparams* Clandmarks_inputparams::NewL( 
    CTestModuleIf& aTestModuleIf )
    {
    Clandmarks_inputparams* self = new (ELeave) Clandmarks_inputparams( aTestModuleIf );

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();

    return self;

    }

// Destructor
Clandmarks_inputparams::~Clandmarks_inputparams()
    { 

    // Delete logger
    delete iLog; 

    }

//-----------------------------------------------------------------------------
// Clandmarks_inputparams::SendTestClassVersion
// Method used to send version of test class
//-----------------------------------------------------------------------------
//
void Clandmarks_inputparams::SendTestClassVersion()
	{
	TVersion moduleVersion;
	moduleVersion.iMajor = TEST_CLASS_VERSION_MAJOR;
	moduleVersion.iMinor = TEST_CLASS_VERSION_MINOR;
	moduleVersion.iBuild = TEST_CLASS_VERSION_BUILD;
	
	TFileName moduleName;
	moduleName = _L("landmarks_inputparams.dll");

	TestModuleIf().SendTestModuleVersion(moduleVersion, moduleName);
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

    return ( CScriptBase* ) Clandmarks_inputparams::NewL( aTestModuleIf );

    }


//  End of File
