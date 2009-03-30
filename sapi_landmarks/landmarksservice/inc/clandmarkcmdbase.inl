/*
* Copyright (c) 2005-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  CLandmarkCmdBase class
 *
*/

// -----------------------------------------------------------------------------
// CLandmarkCmdBase::CLandmarkCmdBase()
// Returns the handle to CLandmarkCmdBase instance.
// -----------------------------------------------------------------------------
//
inline CLandmarkCmdBase::CLandmarkCmdBase( ) :
	CActive(EPriorityNormal)
	{
	}

// -----------------------------------------------------------------------------
// CLandmarkCmdBase::TransactionId()
// Returns the async transaction id.
// -----------------------------------------------------------------------------
//
inline TInt32 CLandmarkCmdBase::TransactionId( )
	{
	return iTransactionId;
	}
