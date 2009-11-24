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
* Description:  Callback class declaration for sensor service API
*
*/


#ifndef CSENSORCALLBACK_H
#define CSENSORCALLBACK_H


#include <liwserviceifbase.h>
#include <liwcommon.h>
#include <sensrvtypes.h>
#include <sensrvdatalistener.h>
#include <sensrvchannelinfo.h>
#include "sensorinterface.hrh"
#include "sensorinterface.h"

/**
 *  This class implements sensor  callback.
 *  An object of this class gets instantiated by sensor
 *  interface class when a request for getting sensor data
 *  arrives from consumer.
 *  @since S60 v5.0
 */

class CSensorCallback : public CBase,
                        public MSensrvDataListener
    {
    public:

         static CSensorCallback*  NewL( MLiwNotifyCallback* aCallBack,
                                        TInt32 aTransactionid );
         virtual ~CSensorCallback();

         /**
         * Indicates data is available in the receiving buffer. A client can read the
         * data through ReadData()-function in a related channel object. Data is valid until
         * the data received notification will occurs again.
         *
         * @since S60 5.0
         * @param[in] aChannel Reference to the related channel object
         * @param[in] aCount Data object count in receiving buffer.
         * @param[in] aDataLost Data object lost count.
         */
         void DataReceived( CSensrvChannel& aChannel,
                            TInt aCount,
                            TInt aDataLost );

         /**
         * Data listening failed.
         * If error was fatal, channel has also been closed and sensor server session terminated.
         * If error was minor, some data has potentially been lost.
         *
         * @param[in] aChannel Reference to the related channel object
         * @param[in] aError Error code.
         * @since S60 5.0
         */
         void DataError( CSensrvChannel& aChannel,
                         TSensrvErrorSeverity aError);

         /**
         * Send Received sensor data back to the consumer
         * @param[in] aChannel Reference to the related channel object
         * @since S60 5.0
         */
         void DataNotificationL( CSensrvChannel& aChannel );

		 
		/** 
        * Returns a pointer to a specified interface - to allow future extension
        * of this class without breaking binary compatibility
        *
        * @since S60 5.0
        * @param aInterfaceUid Identifier of the interface to be retrieved
        * @param aInterface A reference to a pointer that retrieves the specified interface.
        */
        void GetDataListenerInterfaceL( TUid aInterfaceUid, 
                                        TAny*& aInterface );

    private:
         void ConstructL();
         CSensorCallback( MLiwNotifyCallback* aCallBack,
                          TInt32 aTransactionid );
    private:
         
         MLiwNotifyCallback* iCallBack;
         TInt32 iTransactionId;

    };




#endif // CSENSORCALLBACK_H
