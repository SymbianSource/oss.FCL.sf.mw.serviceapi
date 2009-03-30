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
* Description:  This Class provides the core functionality to Application Manager
*				 SAPI
*
*/



#include <e32std.h>
#include <apgcli.h>

#include "asynchrequestmanager.h"
#include "launcherobserver.h"
#include "appobserver.h"



// -----------------------------------------------------------------------------
// CCAsynchRequestManager ::NewLC
// Returns the instance of CCAsynchRequestManager  class.
// -----------------------------------------------------------------------------
CAsynchRequestManager * CAsynchRequestManager ::NewL()
	{
	CAsynchRequestManager * self = new ( ELeave )CAsynchRequestManager ();
	return self;
	}


// -----------------------------------------------------------------------------
// CCAsynchRequestManager ::~CCAsynchRequestManager
// Destructor
// -----------------------------------------------------------------------------

CAsynchRequestManager ::~CAsynchRequestManager ()
	{

	//Cancel All pending request

	TInt pos = iAsyncObjArray.Count() - 1;
	TAsyncRequestInfo obj;
	for ( ; pos >= 0; pos-- )
		{
		obj = iAsyncObjArray[pos];
		//No need to inform for this cancel
		//obj.iAsyncObj->SetAppObserver( NULL );
	    obj.iAsyncObj->Cancel();
	    delete obj.iAsyncObj;
		}
    iAsyncObjArray.Close();

    }



// -----------------------------------------------------------------------------
// CCAsynchRequestManager ::Cancel
// Cancel the pending asynchronous request
// -----------------------------------------------------------------------------
TInt CAsynchRequestManager ::Cancel( TInt32 aTransactionID )
	{

    TInt pos = iAsyncObjArray.Count() - 1;
	TAsyncRequestInfo obj;
	for ( ; pos >= 0; pos-- )
		{
		obj = iAsyncObjArray[pos];
		if( obj.iTransactionId == aTransactionID )
			{
			obj.iAsyncObj->Cancel();
			delete obj.iAsyncObj;
	    	return KErrNone;
			}
		}
	return KErrNotFound;

	}


// -----------------------------------------------------------------------------
// CCAsynchRequestManager ::RequestComplete
// This is called by the observer when asynch request complete
// -----------------------------------------------------------------------------
void CAsynchRequestManager ::RequestComplete( TInt32 aTransactionID )

	{
    TInt pos = iAsyncObjArray.Count()-1;
	TAsyncRequestInfo obj;
	for ( ; pos >= 0; pos-- )
		{
		obj = iAsyncObjArray[pos];
		if( obj.iTransactionId == aTransactionID )
			{
			iAsyncObjArray.Remove(pos);
			iAsyncObjArray.Compress();
			return;
			}
		}
	}

// -----------------------------------------------------------------------------
// CCAsynchRequestManager ::AddObserever
// AddObserever
// -----------------------------------------------------------------------------
CLauncherObserver* CAsynchRequestManager ::AddObsereverLC( MAppObserver* aObserver, TInt32& aTransactionID, TThreadId& aThreadId )

	{
    // Add the given observer in array and return the laucher observer
    // strutcure for binding the transaction ID and callback object

    TAsyncRequestInfo asyncRequestInfo;
	asyncRequestInfo.iTransactionId = aTransactionID;

	//observer for observering underlying classes
	CLauncherObserver* observer = CLauncherObserver::NewL( aObserver,aTransactionID, this);
	CleanupStack::PushL( observer );

	observer->ActivateRequestL( aThreadId );
	asyncRequestInfo.iAsyncObj = observer;

	User::LeaveIfError( iAsyncObjArray.Append( asyncRequestInfo ) );

    return observer;
	}






