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
#include "tcomplugin.h"
#include <CVPbkContactStoreUriArray.h>
#include <TVPbkContactStoreUriPtr.h>
#include <CVPbkContactManager.h>
#include <MVPbkContactStoreList.h>
#include <MVPbkContactStore.h>

_LIT( KCntDbUri, "cntdb://c:contacts.cdb" );
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


// -----------------------------------------------------------------------------
// CTestProvider::CTestProvider
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CTestProvider::CTestProvider( 
    CTestModuleIf& aTestModuleIf ):
        CScriptBase( aTestModuleIf )
    {
    
    
    }

// -----------------------------------------------------------------------------
// CTestProvider::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CTestProvider::ConstructL()
    {   

    iLog = CStifLogger::NewL( KContactsUTLogPath, 
                          KContactsUTLogFile,
                          CStifLogger::ETxt,
                          CStifLogger::EFile,
                          EFalse );

    // Create an URI list
    CVPbkContactStoreUriArray* uriList = CVPbkContactStoreUriArray::NewLC();
    uriList->AppendL( TVPbkContactStoreUriPtr( KCntDbUri ) );
    
    User::LeaveIfError( iFSession.Connect() );
    iContactManager = CVPbkContactManager::NewL( *uriList, &iFSession );

    // Clean up temporary variable
    CleanupStack::PopAndDestroy( uriList );

    // Get all contact store list
    iStores = &(iContactManager->ContactStoresL());
    iStores->OpenAllL( *this );
    CActiveScheduler::Start();      
    }

// -----------------------------------------------------------------------------
// CTestProvider::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CTestProvider* CTestProvider::NewL( 
    CTestModuleIf& aTestModuleIf )
    {
    CTestProvider* self = new (ELeave) CTestProvider( aTestModuleIf );

    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();

    return self;

    }

// Destructor
CTestProvider::~CTestProvider()
    { 

    // Delete resources allocated from test methods
    Delete();


    if( iContactManager )
    {
        TRAP_IGNORE( iContactManager->ContactStoresL().CloseAll( *this ) );
    }
   
    iFSession.Close();   
   
    delete iContactManager; 
    delete iLog; 

    }

void CTestProvider::OpenComplete()
    {
    CActiveScheduler::Stop();
    //Empty
    }
    
void CTestProvider::StoreReady(MVPbkContactStore& aContactStore)
    {
    _LIT(KStoreReady,"Store Ready\n");
    iLog->Log(KStoreReady);
    iStore = &aContactStore;
    }
    
void CTestProvider::StoreUnavailable(MVPbkContactStore& /*aContactStore*/, 
                TInt aReason)
    {
    _LIT(KStoreUnavailable," Store is unavailable. Reason: ");
    TBuf<5> buf;
    buf.Num(aReason);
    iLog->Log(KStoreUnavailable);
    iLog->Log(buf);
    }

void CTestProvider::HandleStoreEventL(
                MVPbkContactStore& /*aContactStore*/, 
                TVPbkContactStoreEvent aStoreEvent)
    {
    TBuf<50> buf;
    _LIT(KHandleStoreEventL,"Store Ready\n");
    iLog->Log(KHandleStoreEventL);
    _LIT(KEvent,"Event Occured:");
    _LIT(KNullEvent, "No Event\n");
    _LIT(KContactAdded, "Contact Added\n");
    _LIT(KContactDeleted, "Contact Deleted\n");
    _LIT(KContactChanged, "Contact Changed\n");
    _LIT(KGroupAdded, "Group Added\n");
    _LIT(KGroupDeleted, "Group Deleted\n");
    _LIT(KGroupChanged, "Group Changed\n");
    _LIT(KStoreBackupBeginning, "Store Backup Beginning\n");
    _LIT(KStoreBackupRestoreCompleted, "Store Backup Restore Completed\n");
    _LIT(KUnknownChanges, "Unknown Changes\n");
    
    switch(aStoreEvent.iEventType)
        {
        case TVPbkContactStoreEvent::ENullEvent :       buf.Append(KNullEvent);
                                                        break;
        case TVPbkContactStoreEvent::EContactAdded :    buf.Append(KContactAdded);
                                                        break;
        case TVPbkContactStoreEvent::EContactDeleted :  buf.Append(KContactDeleted);
                                                        break;
        case TVPbkContactStoreEvent::EContactChanged :  buf.Append(KContactChanged);
                                                        break;
        case TVPbkContactStoreEvent::EGroupAdded :      buf.Append(KGroupAdded);
                                                        break;
        case TVPbkContactStoreEvent::EGroupDeleted :    buf.Append(KGroupDeleted);
                                                        break;
        case TVPbkContactStoreEvent::EGroupChanged :    buf.Append(KGroupChanged);
                                                        break;
        case TVPbkContactStoreEvent::EStoreBackupBeginning :buf.Append(KStoreBackupBeginning);
                                                            break;
        case TVPbkContactStoreEvent::EStoreRestoreBeginning :buf.Append(KStoreBackupRestoreCompleted);
                                                            break;
        case TVPbkContactStoreEvent::EUnknownChanges :  buf.Append(KUnknownChanges);
                                                        break;
        }
        
    iLog->Log(KEvent);
    iLog->Log(buf);
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

    return ( CScriptBase* ) CTestProvider::NewL( aTestModuleIf );

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
