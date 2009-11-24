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
#include "tserviceregistrytest.h"
#include <SettingServerClient.h>


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CIServiceTestModule::CIServiceTestModule
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CIServiceTestModule::CIServiceTestModule( 
    CTestModuleIf& aTestModuleIf ):
        CScriptBase( aTestModuleIf )
    {
    }

    
// -----------------------------------------------------------------------------
// CIServiceTestModule::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CIServiceTestModule::RunMethodL(CStifItemParser& aItem) 
    {        
    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY("GetMetaDataListL", CIServiceTestModule::GetMetaDataListL),
        ENTRY("LoadProviderTest", CIServiceTestModule::LoadProviderTest),
        ENTRY("GetListTwice", CIServiceTestModule::GetListTwice),
        ENTRY("InvalidCommand", CIServiceTestModule::InvalidCommand),
        ENTRY("CancelInvalidTransID", CIServiceTestModule::CancelInvalidTransID),
        ENTRY("InvalidServiceValue", CIServiceTestModule::InvalidServiceValue),
        ENTRY("InvalidInterfaceValue", CIServiceTestModule::InvalidInterfaceValue),
        ENTRY("InvalidMinVerValue", CIServiceTestModule::InvalidMinVerValue),
        ENTRY("InvalidMaxVerValue", CIServiceTestModule::InvalidMaxVerValue),
        ENTRY("InvalidFilterValue", CIServiceTestModule::InvalidFilterValue),        
        };
    const TInt count = sizeof(KFunctions)/ 
                       sizeof(TStifFunctionInfo);
    return RunInternalL(KFunctions, count, aItem);
    }
// -----------------------------------------------------------------------------
// CIServiceTestModule::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CIServiceTestModule::ConstructL()
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
        logFileName.Format(KIServiceTestModuleLogFileWithTitle, &title);
        }
    else
        {
        logFileName.Copy(KIServiceTestModuleLogFile);
        }

    iLog = CStifLogger::NewL( KIServiceTestModuleLogPath, 
                              logFileName,
                              CStifLogger::ETxt,
                              CStifLogger::EFile,
                              EFalse );    
    SendTestClassVersion();
    
    LoadServiceRegistry();
    }

// -----------------------------------------------------------------------------
// CIServiceTestModule::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CIServiceTestModule* CIServiceTestModule::NewL( 
    CTestModuleIf& aTestModuleIf )
    {
    CIServiceTestModule* self = new (ELeave) CIServiceTestModule( aTestModuleIf );

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();

    return self;

    }

// Destructor
CIServiceTestModule::~CIServiceTestModule()
    { 
    // Delete logger
    delete iLog; 

    }


void CIServiceTestModule::LoadServiceRegistry()
    {
    TInt pos = 0;        
    
    iServiceHandler = CLiwServiceHandler::NewL();

    iInparams = &(iServiceHandler->InParamListL());
    iOutparams = &(iServiceHandler->OutParamListL());

    iCriteria = CLiwCriteriaItem::NewL( 1, _L8("IService"), _L8("Service.ServiceRegistry") );
    iCriteria->SetServiceClass(TUid::Uid( KLiwClassBase ));

    iCriteriaArray.AppendL( iCriteria );
    iServiceHandler->AttachL( iCriteriaArray );

    iServiceHandler->ExecuteServiceCmdL( *iCriteria, *iInparams, *iOutparams );

    iOutparams->FindFirst( pos, _L8("IService") );
    if(pos != KErrNotFound)
        {
        //LogMessage(_L8("Service Loaded\n"));
        iIface = ( *iOutparams )[pos].Value().AsInterface();
        }
    else
        {
        //LogMessage(_L8("Service Not found\n"));
        }
    if( iInparams )
       {
       iInparams->Reset();       
       }
    if( iOutparams )
       {
       iOutparams->Reset();
       }
    if( iCriteria )
       {
        delete iCriteria;
        iCriteria = NULL;
       }
    }
//-----------------------------------------------------------------------------
// CIServiceTestModule::SendTestClassVersion
// Method used to send version of test class
//-----------------------------------------------------------------------------
//
void CIServiceTestModule::SendTestClassVersion()
	{
	TVersion moduleVersion;
	moduleVersion.iMajor = TEST_CLASS_VERSION_MAJOR;
	moduleVersion.iMinor = TEST_CLASS_VERSION_MINOR;
	moduleVersion.iBuild = TEST_CLASS_VERSION_BUILD;
	
	TFileName moduleName;
	moduleName = _L("IServiceTestModule.dll");

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

    return ( CScriptBase* ) CIServiceTestModule::NewL( aTestModuleIf );

    }


//  End of File
