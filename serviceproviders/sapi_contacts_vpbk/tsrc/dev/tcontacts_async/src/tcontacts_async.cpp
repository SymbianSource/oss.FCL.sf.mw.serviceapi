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
#include <coemain.h>

#include <CVPbkContactStoreUriArray.h>
#include <CVPbkContactManager.h>
#include <MVPbkContactStoreList.h>
#include <MVPbkContactStore.h>
#include <TVPbkContactStoreUriPtr.h>
#include <CVPbkVCardEng.h>

#include "contactservice.h"
#include "tcontacts_async.h"

_LIT( KCntDbUri, "cntdb://c:contacts.cdb" );
// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CContactsUT::CContactsUT
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CContactsUT::CContactsUT( 
    CTestModuleIf& aTestModuleIf ):
        CScriptBase( aTestModuleIf ),
        iErr(KErrNone)        
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
    
    // Create an URI list
    CVPbkContactStoreUriArray* uriList = CVPbkContactStoreUriArray::NewLC();
    uriList->AppendL( TVPbkContactStoreUriPtr( KCntDbUri ) );
    
    User::LeaveIfError( iRfs.Connect() );
    //iRfs = CCoeEnv::Static()->FsSession();
    iContactManager = CVPbkContactManager::NewL( *uriList, &iRfs );

    // Clean up temporary variable
    CleanupStack::PopAndDestroy( uriList );

    // Get all contact store list
    iStores = &(iContactManager->ContactStoresL());
    //iStore = &( iStores->At( (iStores->Count())-1 ) );
    iStores->OpenAllL( *this );
    CActiveScheduler::Start();
    
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
    Delete();
    if( iContactManager )
    {
        TRAP_IGNORE( iContactManager->ContactStoresL().CloseAll( *this ) );
    }
   
    iRfs.Close();   
    iDestStream.Close();

    delete iVCardEngine;
    delete iContactManager; 
    delete iServiceHandle;
    // Delete logger
    delete iLog; 

    }

void CContactsUT::OpenComplete()
    {
    CActiveScheduler::Stop();
    //Empty
    }
    
void CContactsUT::StoreReady(MVPbkContactStore& aContactStore)
    {
    _LIT(KStoreReady,"Store Ready\n");
    iLog->Log(KStoreReady);
    iStore = &aContactStore;
    }
    
void CContactsUT::StoreUnavailable(MVPbkContactStore& /*aContactStore*/, 
                TInt aReason)
    {
    _LIT(KStoreUnavailable," Store is unavailable. Reason: ");
    TBuf<5> buf;
    buf.Num(aReason);
    iLog->Log(KStoreUnavailable);
    iLog->Log(buf);
    }

void CContactsUT::HandleStoreEventL(
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

    return ( CScriptBase* ) CContactsUT::NewL( aTestModuleIf );

    }


//  End of File
