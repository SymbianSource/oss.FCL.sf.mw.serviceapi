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
* Description:  This  class stores information about async calls
*
*/


#ifndef CSTOREASYNCINFO_H
#define CSTOREASYNCINFO_H

#include <e32base.h>
#include "sensorcallback.h"

//forward declaration
class CSensorCallback;
/**
 * This class stores information about async requests that are being served
 * currently and also provides method to fectch those information
 */

 //Enums for Async Request Type
enum TAsyncType
    {
    EData,
    EInvalid
    };

class CStoreAsyncInfo : public CBase
    {
    public:
        /**
         * Symbian Two Phase construction
         * @Param aType : Type of async request
         * @Param aTransactionId: TransactionId
         * @Param aChannelId : ChannelId
         * Returns Pointer to a newly Created object of this class
         */
        static CStoreAsyncInfo* NewL( TAsyncType atype,
                                      TInt32 aTransactionId,
                                      CSensorCallback* aCallback,
                                      TUint aChannelId = 0 );
        /**
         * Destructor
         */
        virtual ~CStoreAsyncInfo();
        

    private:
        /**
         * Default constructor.
         */
        CStoreAsyncInfo( TAsyncType atype,
                         TInt32 aTransactionId,
                         CSensorCallback* aCallback,
                         TUint aChannelId = 0 );
        /**
         * Symbian OS constructor.
         * @return void
         */
        void ConstructL();
    public:

        /**
         * Channel id
         */
         TUint ichnlId;

        /**
         * Transaction id
         */
         TInt32 iTransactionId;

        /**
         * Async type
         */
         TAsyncType iAsyncType;

        /**
         * Ptr to callback
         */
         CSensorCallback* iCallback;
    };

#endif // CSTOREASYNCINFO_H
