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


#include <e32std.h>
#include <apgcli.h>

#include "asynchrequestmanager.h"
#include "mgclfoperationobserver.h"

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
	
	    obj.iAsyncObj->CancelL();
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
			obj.iAsyncObj->CancelL();
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
// CAsynchRequestManager ::AddObserverL
// AddObserever
// -----------------------------------------------------------------------------
void CAsynchRequestManager ::AddObserverL(CClfOperationObserver* aServiceObserver, TUint aTransactionID)

	{
    // Add the given observer in array and return the laucher observer
    // strutcure for binding the transaction ID and callback object

    TAsyncRequestInfo asyncRequestInfo;
	asyncRequestInfo.iTransactionId = aTransactionID;

	//observer for observering underlying classes
	asyncRequestInfo.iAsyncObj = aServiceObserver;

	User::LeaveIfError( iAsyncObjArray.Append( asyncRequestInfo ) );

   	}






