/*
* Copyright (c) 2006-2007 Nokia Corporation and/or its subsidiary(-ies).
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


#include "storeasyncinfo.h"


/*
-----------------------------------------------------------------------------
    CStoreAsyncInfo::CStoreAsyncInfo()
    Description    : Constructor
    Return values  : N/A
-----------------------------------------------------------------------------
*/
CStoreAsyncInfo :: CStoreAsyncInfo( TAsyncType atype,
                                    TInt32 aTransactionId,
                                    CSensorCallback* aCallback,
                                    TUint aChannelId )
                 :ichnlId( aChannelId ),
                  iTransactionId( aTransactionId ),
                  iAsyncType( atype ),
                  iCallback( aCallback )
    {
    }


/*
-----------------------------------------------------------------------------
    void CStoreAsyncInfo::ConstructL()
    Description         : Symbian 2nd phase constructor can leave.
    Return values       : N/A
-----------------------------------------------------------------------------
*/
void CStoreAsyncInfo :: ConstructL()
    {
    }
    
/*
-----------------------------------------------------------------------------
    CStoreAsyncInfo* CStoreAsyncInfo::NewL()
    Description                       : Two-phased constructor.
    Return values                     : CSensorInterface object pointer

-----------------------------------------------------------------------------
*/
CStoreAsyncInfo* CStoreAsyncInfo::NewL( TAsyncType aType,
                                        TInt32 aTransactionId,
                                        CSensorCallback* aCallback,
                                        TUint aChnlId )
    {
    CStoreAsyncInfo* self = new ( ELeave ) CStoreAsyncInfo( aType,
    														aTransactionId,
    														aCallback,
    														aChnlId );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }
    
/*
-----------------------------------------------------------------------------
    CStoreAsyncInfo::~CStoreAsyncInfo()
    Description     : Destructor, free allocated resources
    Return values   : N/A
-----------------------------------------------------------------------------
*/
CStoreAsyncInfo::~CStoreAsyncInfo()
    {
    }
    
