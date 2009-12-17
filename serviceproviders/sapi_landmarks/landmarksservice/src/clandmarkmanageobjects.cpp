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
* Description:  CLandmarkManageObjects class implementation.
 *
*/


#include "clandmarkmanageobjects.h"
#include "clandmarkcmdbase.h"
#include "clandmarkdummyao.h"
#include "clandmarkoperation.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CLandmarkManageObjects::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CLandmarkManageObjects* CLandmarkManageObjects::NewL( )
	{
	CLandmarkManageObjects* self = new (ELeave) CLandmarkManageObjects();
	return self;
	}

// -----------------------------------------------------------------------------
// CLandmarkManageObjects::CLandmarkManageObjects()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CLandmarkManageObjects::CLandmarkManageObjects( ) :
	CActive(EPriorityNormal)
	{
	CActiveScheduler::Add (this );
	}

// -----------------------------------------------------------------------------
// CLandmarkManageObjects::~CLandmarkManageObjects()
// Destructor.
// -----------------------------------------------------------------------------
//
CLandmarkManageObjects::~CLandmarkManageObjects( )
	{
	Cancel ( );
	iObjects.ResetAndDestroy ( );
	iObjects.Close();
	iDummyObjects.ResetAndDestroy();
	iDummyObjects.Close();
	iOrgObjects.ResetAndDestroy();
	iOrgObjects.Close();
	}

// -----------------------------------------------------------------------------
// CLandmarkManageObjects::Start()
// Start asynchronous operation.
// -----------------------------------------------------------------------------
//
void CLandmarkManageObjects::Start( )
	{
	SetActive ( );
	TRequestStatus* status = &iStatus;
	User::RequestComplete (status, KErrNone );
	}

// -----------------------------------------------------------------------------
// CLandmarkManageObjects::AppendL( CLandmarkCmdBase* aObject )
// Execute the next step.
// -----------------------------------------------------------------------------
//
void CLandmarkManageObjects::AppendL( CLandmarkCmdBase* aObject )
	{
	iObjects.AppendL (aObject );
	}

void CLandmarkManageObjects::AppendL(CLandmarkDummyAO* aObject)
	{
	iDummyObjects.AppendL(aObject);
	}

void CLandmarkManageObjects::AppendL(CLandmarkOperation* aObject)
	{
	iOrgObjects.AppendL(aObject);
	}
// -----------------------------------------------------------------------------
// CLandmarkManageObjects::CancelObject()
// Execute the next step.
// -----------------------------------------------------------------------------
//
void CLandmarkManageObjects::CancelObject( TInt32 aTransactionId )
	{
	TBool isDone = EFalse;
	TInt count = iObjects.Count();
	for (TInt i = 0; i < count; ++i)
		{
		if ( iObjects[i]->TransactionId ( )== aTransactionId )
			{
			iObjects[i]->Cancel();
			isDone = ETrue;
			break;
			}
		}
	if( !isDone )
		{
		count = iOrgObjects.Count();
		for (TInt i = 0; i < count; ++i)
			{
			if (iOrgObjects[i]->TransactionId() == aTransactionId)
				{
				iOrgObjects[i]->Cancel();
				break;
				}
			}
		}
	}
// -----------------------------------------------------------------------------
// CLandmarkManageObjects::RunL()
// Notify Observer on completion of the asynchronous call.
// -----------------------------------------------------------------------------
//
void CLandmarkManageObjects::RunL( )
	{
	TInt count = iObjects.Count ( );
	for (TInt i = 0; i< count; ++i )
		{
		if ( !iObjects[i]->IsActive() )
			{
			delete iObjects[i];
			//Removes a node from the RPointerArray.
			iObjects.Remove (i );
			//Decrement node count.
			--count;
			//Decrement index count since the present node
			//has been deleted.
			--i;
			}
		}
	count = iDummyObjects.Count();
	for (TInt i = 0; i < count; ++i)
		{
		if (!iDummyObjects[i]->IsActive())
			{
			delete iDummyObjects[i];
			//Removes a node from the RPointerArray.
			iDummyObjects.Remove(i);
			//Decrement node count.
			--count;
			//Decrement index count since the present node
			//has been deleted.
			--i;
			}
		}
	count = iOrgObjects.Count();
	for (TInt i = 0; i < count; ++i)
		{
		if (!iOrgObjects[i]->IsActive())
			{
			delete iOrgObjects[i];
			//Removes a node from the RPointerArray.
			iOrgObjects.Remove(i);
			//Decrement node count.
			--count;
			//Decrement index count since the present node
			//has been deleted.
			--i;
			}
		}
	}

// -----------------------------------------------------------------------------
// CLandmarkManageObjects::DoCancel()
// Cancel asynchronous call.
// -----------------------------------------------------------------------------
//
void CLandmarkManageObjects::DoCancel( )
	{
	}
//end of file
