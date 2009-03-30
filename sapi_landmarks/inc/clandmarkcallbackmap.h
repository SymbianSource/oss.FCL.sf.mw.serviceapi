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


#ifndef __CLANDMARKCALLBACKMAP_H__
#define __CLANDMARKCALLBACKMAP_H__

//INCLUDES
#include <e32base.h>

//FORWARD DECLARATION
class MLiwNotifyCallback;

/**
* CLandmarkCallbackMap
* This class keeps a map of the transaction id allocated to an asynchronous request with the callback
* of the request.
*/

// CLASS DECLARATION
NONSHARABLE_CLASS(CLandmarkCallbackMap): public CBase
    {
    public:// Constructors

        /**
        * CLandmarkCallbackMap
        * Constructor.
        *
        * @param aTransactionId The transaction id alloted to asynchronous request.
        * @param aCallback The callback associated with the asynchronous request.
        */
        inline CLandmarkCallbackMap( TInt32 aTransactionId, MLiwNotifyCallback* aCallback );
        
        /**
        * ~CLandmarkCallbackMap
        * Destructor.
        */
        inline ~CLandmarkCallbackMap() {}

    public:

        /**
        * Set
        * Sets the transaction id and callback.
        *
        * @param aTransactionId The transaction id alloted to asynchronous request.
        * @param aCallback The callback associated with the asynchronous request.
        */
        inline void Set( TInt32 aTransactionId, MLiwNotifyCallback* aCallback );

        /**
        * Get
        * Gets the transaction id and callback.
        *
        * @param aTransactionId The transaction id alloted to asynchronous request.
        * @param aCallback The reference to the callback associated with the asynchronous request.
        * @return True if aCallback is set else False.
        */
        inline TBool Get( TInt32 aTransactionId, MLiwNotifyCallback*& aCallback ) const;


    private:// Data

        /**
        * iTransactionId
        * The transaction id of the async call.
        */
        TInt32 iTransactionId;

        /**
        * iCallback
        * The handle to MLiwNotifyCallback.
        */
        MLiwNotifyCallback* iCallback;

    };

#include "clandmarkcallbackmap.inl"

#endif // __CLANDMARKCALLBACKMAP_H__
