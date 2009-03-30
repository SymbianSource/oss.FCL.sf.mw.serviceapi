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
*  V	ersion     : %version: 3 % << Don't touch! Updated by Synergy at check-out.
*
*/




#include "sensrdatacallback.h"
#include <sensrvchannel.h>
#include <sensrvchanneldatatypes.h>

#include "sensrservicetest.h"


// ---------------------------------------------------------------------------
// ?description_if_needed
// ---------------------------------------------------------------------------
//
void CSensrDataCallBack::ConstructL()
    {
    //do nothing
    }


// ---------------------------------------------------------------------------
// ?description_if_needed
// ---------------------------------------------------------------------------
//
CSensrDataCallBack* CSensrDataCallBack::NewL(CSensorService* aChannel,TUint32 aChannelId)
    {
    CSensrDataCallBack* self = new(ELeave) CSensrDataCallBack();
    CleanupStack::PushL(self);
    
    self->ConstructL();
    self->iChannel = aChannel;
    self->iChannelId = aChannelId;
    CleanupStack::Pop(self);
    return self;
    
    }





// ---------------------------------------------------------------------------
// ?description_if_needed
// ---------------------------------------------------------------------------
//
CSensrDataCallBack::~CSensrDataCallBack()
    {
    //do nothing
    
    }
CSensrDataCallBack::CSensrDataCallBack()
    {
    //do nothing
    
    }
    
void CSensrDataCallBack::DataReceived( CSensrvChannel& aChannel, 
                                   TInt /*aCount*/, 
                                   TInt /*aDataLost*/)
	{

	TSensrvChannelInfo info = aChannel.GetChannelInfo();
	if( info.iChannelType == EFindAccelerometerXYZAxisData )
		{
		TSensrvAccelerometerAxisData accData;
		TPckg<TSensrvAccelerometerAxisData> accPackage( accData );
		aChannel.GetData( accPackage );
		}
	else if( info.iChannelType == EFindAccelerometerDoubleTappingData )
		{
		TSensrvTappingData accData;
		TPckg<TSensrvTappingData> accPackage( accData );
		aChannel.GetData( accPackage );

		}
	else if( info.iChannelType == EFindOrientationData )
		{
		TSensrvOrientationData accData;
     	TPckg<TSensrvOrientationData> accPackage( accData );
     	aChannel.GetData( accPackage );
		}
	else if( info.iChannelType == EFindRotationData )
		{
		TSensrvRotationData accData;
     	TPckg<TSensrvRotationData> accPackage( accData );
     	aChannel.GetData( accPackage );
     
		}

  	iChannel->StopNotificationL(EStopData,info.iChannelId);
  	CActiveScheduler *sched = CActiveScheduler :: Current() ;
  	sched->Stop() ;

	}
	
void CSensrDataCallBack::DataError( CSensrvChannel& /*aChannel*/, 
                                TSensrvErrorSeverity /*aError*/)
	{
	}

void CSensrDataCallBack::GetDataListenerInterfaceL( TUid /*aInterfaceUid*/, 
                                TAny*& aInterface )
    {
    aInterface = NULL; // Extension interfaces are not supported
    }



