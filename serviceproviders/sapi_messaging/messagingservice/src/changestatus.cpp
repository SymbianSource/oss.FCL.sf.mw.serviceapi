/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Implementaion of change status  Delete message
*
*/


#include <msvapi.h>
#include <miuthdr.h>

#include "messageheader.h"
#include "changestatus.h"

// ---------------------------------------------------------------------------
// two-phased constructor
// ---------------------------------------------------------------------------
CMessageChangeStatus* CMessageChangeStatus::NewL( CMsvSession& aSession )
	{
	CMessageChangeStatus* self=NewLC( aSession );
	CleanupStack::Pop( self );
	return self;
	}

// ---------------------------------------------------------------------------
// two-phased constructor
// ---------------------------------------------------------------------------
CMessageChangeStatus* CMessageChangeStatus::NewLC( CMsvSession& aSession )
	{
	CMessageChangeStatus* self=new(ELeave) CMessageChangeStatus( aSession );
	CleanupStack::PushL( self );
	return self;
  	}
  
// ---------------------------------------------------------------------------
// default constructor
// ---------------------------------------------------------------------------
CMessageChangeStatus::CMessageChangeStatus( CMsvSession& aSession ):
											iServerSession( aSession )
	{
	}
  
// ---------------------------------------------------------------------------
// destructor
// ---------------------------------------------------------------------------
CMessageChangeStatus::~CMessageChangeStatus()
	{
	delete iEntry;
	}
	
// ---------------------------------------------------------------------------
// CMessageChangeStatus::DeleteMessageL
// This function is used to delete a message 
// returns KErrNone after success
// ---------------------------------------------------------------------------
void CMessageChangeStatus::DeleteMessageL( const TMsvId& aMsgId )
	{
	iMessageId = aMsgId;

	InitializeL();
	DeleteMessageL();	
	}

// ---------------------------------------------------------------------------
// CMessageChangeStatus::ChangeStatus
// This function is used to change the message status based on the status falg passed
// returns KErrNone on success.
// ---------------------------------------------------------------------------
void CMessageChangeStatus::ChangeStatusL( const TMsvId& aMsgId, 
											const TMessageStatusFlag aStatusFlag, 
											const TBool aValue )
	{
	iMessageId= aMsgId;
	iStatusFlag = aStatusFlag;
	iFlagValue = aValue;

	InitializeL();
	ChangeStatusL();	
	}
	

// ---------------------------------------------------------------------------
// CMessageChangeStatus::InitializeL
// This function is used to get the various message entry to be chnaged/deleted 
// and an index pointing to that entry.
// ---------------------------------------------------------------------------
void CMessageChangeStatus::InitializeL()
	{
	if ( iEntry )
		{
		delete iEntry;
		iEntry = NULL;
		}
		
	iEntry = iServerSession.GetEntryL( iMessageId );
	iIndexEntry = iEntry->Entry();
	}
	
// ---------------------------------------------------------------------------
// CMessageChangeStatus::ChangeStatusL
// This function is used to change the message status based on the status flag passed
// returns KErrNone on success.
// ---------------------------------------------------------------------------
void CMessageChangeStatus::ChangeStatusL()
	{
	switch ( iStatusFlag )
		{
		case EUnread:
			{
			iIndexEntry.SetUnread( iFlagValue );
			iEntry->ChangeL( iIndexEntry );
			}
			break;
		
		default:
			User::Leave( KErrGeneral );
		}
	}
	
// ---------------------------------------------------------------------------
// CMessageChangeStatus::DeleteMessageL
// delete a message based on its message ID
// ---------------------------------------------------------------------------
void CMessageChangeStatus::DeleteMessageL()
	{
	TMsvId parentID = iIndexEntry.Parent();
	CMsvEntry* parentEntry = iServerSession.GetEntryL( parentID );
	CleanupStack::PushL( parentEntry );

	if ( iEntry )
		{
		delete iEntry;
		iEntry = NULL;
		}
	
	parentEntry->DeleteL( iMessageId );

	CleanupStack::PopAndDestroy( parentEntry );
	}

