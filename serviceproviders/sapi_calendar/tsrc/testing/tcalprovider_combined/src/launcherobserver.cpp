/*
* Copyright (c) 2007-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:   This Class is observer for the Launching Application
*
*/


#include "launcherobserver.h"
#include "asynchrequestmanager.h"
#include "appobserver.h"
#include "appmanagercommon.h"


// -----------------------------------------------------------------------------
// launcherObserver::NewL
// Returns the instance of CLauncherObserver.
// -----------------------------------------------------------------------------
CLauncherObserver* CLauncherObserver::NewL(  MAppObserver* aObserver ,TInt32& aTransactionID, CAsynchRequestManager* aAsynchRequestManager )
	{
	CLauncherObserver* self = new ( ELeave )CLauncherObserver( aObserver ,aTransactionID, aAsynchRequestManager );
	return self;
	}

// ---------------------------------------------------------------------------
// Destructor.
// ---------------------------------------------------------------------------
//
CLauncherObserver::~CLauncherObserver()
	{

    iAppThread.Close();
	}

// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CLauncherObserver::CLauncherObserver(MAppObserver* aObserver ,TInt32& aTransactionID, CAsynchRequestManager* aAsynchRequestManager ):
                   CActive( EPriorityStandard ),
                   iAppObserver ( aObserver ),
                   iTransactionID( aTransactionID ),
                   iAsynchRequestManager ( aAsynchRequestManager )
 	
	{
	CActiveScheduler::Add( this );
	}

	


// ---------------------------------------------------------------------------
// Activates the asynchronous request
// ---------------------------------------------------------------------------
//
void CLauncherObserver::ActivateRequestL( TThreadId& aThreadId  )
	{
	
	User::LeaveIfError( iAppThread.Open( aThreadId ) );
	iStatus = KRequestPending;
	SetActive();
	iAppThread.Logon( iStatus );
	}

// ---------------------------------------------------------------------------
// sets the observer pointer 
// ---------------------------------------------------------------------------
//
void CLauncherObserver::SetAppObserver ( MAppObserver* aAppObserver )
	{
	
	iAppObserver = aAppObserver;
	}

// ---------------------------------------------------------------------------
// Notifies callback the result for asynchronous request.
// ---------------------------------------------------------------------------
//
void CLauncherObserver::NotifyRequestResultL( TInt aReason , TAppOperationEvent& aOperationEvent )
	{
     //Inform core class for completing the reuqest 
     iAsynchRequestManager->RequestComplete( iTransactionID );
     
     if( iAppObserver )
        {
        iAppObserver->AppNotifyCallbackL( aReason , iTransactionID , aOperationEvent  );
        }

     if( aOperationEvent != EAppCancel ) // If this is called because of cancel then skip the deletion
     delete this;    

	}
// ---------------------------------------------------------------------------
// Inherited from CActive class 
// ---------------------------------------------------------------------------
//
void CLauncherObserver::DoCancel()
	{
	iAppThread.LogonCancel( iStatus );
	TAppOperationEvent appEvent = EAppCancel;
	TRAP_IGNORE( NotifyRequestResultL( KErrCancel , appEvent ) );
	}

// ---------------------------------------------------------------------------
// Inherited from CActive class 
// ---------------------------------------------------------------------------
//
void CLauncherObserver::RunL()
	{
	TAppOperationEvent appEvent = EAppComplete;
	NotifyRequestResultL( iStatus.Int(), appEvent );
	}

