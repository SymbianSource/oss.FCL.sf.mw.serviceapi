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




#ifndef CSENSRDATACALLBACK_H
#define CSENSRDATACALLBACK_H

#include "sensrservicetest.h"

class CSensrDataCallBack : public CBase,
						   public MSensrvDataListener
	{
	public:
		 static CSensrDataCallBack* NewL(CSensorService* aChannel,TUint32 aChannelId);

		 virtual ~CSensrDataCallBack();

     void DataReceived( CSensrvChannel& aChannel, 
                                   TInt aCount, 
                                   TInt aDataLost);

    void DataError( CSensrvChannel& aChannel, 
                                TSensrvErrorSeverity aError);
	
    void GetDataListenerInterfaceL( TUid aInterfaceUid, 
                                    TAny*& aInterface );

	
	private:
		void ConstructL();
		CSensrDataCallBack();
	private://data
		CSensorService* iChannel;
		TUint32 iChannelId;
		
		
	};
#endif //CSENSRDATACALLBACK_H






