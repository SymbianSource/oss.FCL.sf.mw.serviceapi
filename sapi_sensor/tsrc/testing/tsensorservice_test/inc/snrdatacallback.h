/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:   ?Description
*
*/




#ifndef CSNRDATACALLBACK_H
#define CSNRDATACALLBACK_H

#include <e32property.h>
#include <StifLogger.h>
#include <TestScripterInternal.h>
#include <StifTestModule.h>
#include <sensrvtypes.h>
#include <sensrvdatalistener.h>
#include <sensrvchannelinfo.h>
#include <sensrvchanneldatatypes.h>
#include "sensorservice.h"

class CSnrDataCallBack : public CBase,
						   public MSensrvDataListener
				
						  
	{
	public:
		 static CSnrDataCallBack*  NewL(CSensorService* aChannel,TUint32 aChannelId);
		 virtual ~CSnrDataCallBack();
	
	//Classes derrived from MSensrvDataListener
	
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
                                   TInt aDataLost);

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
                                

        void GetDataListenerInterfaceL( TUid aInterfaceUid, 
                                        TAny*& aInterface );

        
        TInt callback_x ,callback_y ,callback_z;  
        TInt callback_rx ,callback_ry ,callback_rz;  
        TUint callback_wake;
        TUint callback_dir;
        TInt  callback_or;                 
	
	private:
		void ConstructL();
		CSnrDataCallBack();
	private://data
		CSensorService* iChannel;
		TUint32 iChannelId;
		
		
	};
#endif //CSENSRDATACALLBACK_H






