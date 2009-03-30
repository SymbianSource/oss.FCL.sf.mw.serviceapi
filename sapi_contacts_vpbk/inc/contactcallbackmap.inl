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
* Description:  Map of callback and transaction id.
*
*/


inline CContactCallbackMap::CContactCallbackMap( TInt32 aTransactionId, MLiwNotifyCallback* aCallback )
 									 : iTransactionId(aTransactionId), iCallback(aCallback)
    {    
    }

inline void CContactCallbackMap::Set( TInt32 aTransactionId, MLiwNotifyCallback* aCallback )
    {
    iTransactionId = aTransactionId;
    iCallback = aCallback;
    }
    
inline TBool CContactCallbackMap::Get( TInt32 aTransactionId, MLiwNotifyCallback*& aCallback ) const
    {
    if ( iTransactionId == aTransactionId )
    		{
    		aCallback = iCallback;
    		return ETrue;
    		}
    return EFalse;
    }

// End of file
