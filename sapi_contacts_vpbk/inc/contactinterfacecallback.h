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
* Description:  Implements the contact callback interface.
*
*/

#ifndef C_CCONTACTINTERFACECALLBACK_H
#define C_CCOTNACTINTERFACECALLBACK_H

// System includes
#include <e32base.h>

// User Includes
#include "contactcallback.h"
#include "contactinterface.hrh"
#include "contactiterator.h"

// Forward declarations
class MLiwNotifyCallback;
class CLiwGenericParamList;

/**
 * CContactInterfaceCallback - Implements the contact callback interface.
 * Passes the frames and notifies the the events
 * through callback.
 */
class CContactInterfaceCallback : public CBase, public MContactCallback
    {
    public:
        /**
         * Two-phased constructor.
         * @return CContactInterfaceCallback*
         */
        static CContactInterfaceCallback* NewL();

		/**
         * Two-phased constructor.
         * @return CContactInterfaceCallback*
         */
        static CContactInterfaceCallback* NewL(CSingleContact* aContact);
        
        /**
         * Destructor
         */
        virtual ~CContactInterfaceCallback();

    private:
        /**
         * Default constructor.
         */
        CContactInterfaceCallback();

    public:
        /**
         * Method  to set the parameters for the callback.
         * @param aCallback the callback to be called
         * @param aTransId the transaction Id
         * @param aInParamList to send back to LIW.
         * @return void
         */
        void SetParams( MLiwNotifyCallback* aCallback,
                        const TInt aTransId,
                        const CLiwGenericParamList* aInParamList );


        /**
         * Called when the any async operation returns with error or success
         * @return void
         */
        virtual void HandleReturnValue(TOperationEvent aEventId, const TInt& aError, TInt aTransId );

        /**
         * Called when the GetList returns the an iterator (which iterates over the output)
         * @return void
         */		
		virtual void HandleReturnIter(const TInt& aError,CContactIter* aIter, TInt aTransId );
        

    private:
        //Pointer to the MLiwNotifyCallback callback passed by consumer.
        MLiwNotifyCallback* iCallback;

        //Trasaction ID.
        TInt iTransactionId;

        //Referance to top the Input Parameter list passed by consumer.
        const CLiwGenericParamList* iInParamList;

        //Event Generic Parameter List
        CLiwGenericParamList* iEventParamList;
        
        //pointer to the single contact object needed for cleanup
        CSingleContact* iContact;        
    };

#endif // C_CCOTNACTINTERFACECALLBACK_H
