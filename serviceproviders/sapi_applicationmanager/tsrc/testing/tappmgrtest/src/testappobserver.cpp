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
* Description:  This Class is observer for the Launching Application
*
*/


#include <e32const.h>
#include "testappobserver.h"


// -----------------------------------------------------------------------------
// CAppObserver::NewL
// Returns the instance of CLauncherObserver.
// -----------------------------------------------------------------------------
CAppObserver* CAppObserver::NewL(CActiveSchedulerWait * aWait)
	{
	CAppObserver* self = new( ELeave ) CAppObserver(aWait);
	return self;
	}

// ---------------------------------------------------------------------------
// call back
// ---------------------------------------------------------------------------
//
void CAppObserver::AppNotifyCallbackL( TInt32 aReason, TInt32 aTransactionID ,TAppOperationEvent& aOperationEvent )

	{
		iReason = aReason;
		
		if( KErrCancel != aReason )
			iWait->AsyncStop();
	}




// ---------------------------------------------------------------------------
// consturctor
// ---------------------------------------------------------------------------
//
CAppObserver::CAppObserver(CActiveSchedulerWait * aWait )
	{
	 iWait = aWait;
	 iReason = 10 ; //Reason of failure can be either 0 or some negative valuw which incater 
	 //error but it cant be greater than 0 
	}