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




#include "snrdatacallback.h"
#include <sensrvchanneldatatypes.h>


// ---------------------------------------------------------------------------
// ?description_if_needed
// ---------------------------------------------------------------------------
//
void CSnrDataCallBack::ConstructL()
    {
    //do nothing
    }


// ---------------------------------------------------------------------------
// ?description_if_needed
// ---------------------------------------------------------------------------
//
CSnrDataCallBack* CSnrDataCallBack::NewL(CSensorService* aChannel,TUint32 aChannelId)
    {
    CSnrDataCallBack* self = new(ELeave) CSnrDataCallBack();
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
CSnrDataCallBack::~CSnrDataCallBack()
    {
    //do nothing
    
    }
CSnrDataCallBack::CSnrDataCallBack()
    {
    //do nothing
    
    }
void CSnrDataCallBack::DataReceived( CSensrvChannel& aChannel, 
                                   TInt /*aCount*/, 
                                   TInt /*aDataLost*/ )
	{
	 TSensrvChannelInfo info = aChannel.GetChannelInfo();
	 if( info.iChannelType == KSensrvChannelTypeIdAccelerometerXYZAxisData )
        {
        TSensrvAccelerometerAxisData accData;
        TPckg<TSensrvAccelerometerAxisData> accPackage( accData );
        aChannel.GetData( accPackage );
        
        callback_x =  accData.iAxisX;
        callback_y =  accData.iAxisY;
        callback_z =  accData.iAxisZ;
        }
        
     if( info.iChannelType == KSensrvChannelTypeIdAccelerometerWakeupData )
        {
        TSensrvTappingData accData;
        TPckg<TSensrvTappingData> accPackage( accData );
        aChannel.GetData( accPackage );
        
        callback_wake =  accData.iDirection;
        
        } 
        
     if( info.iChannelType == KSensrvChannelTypeIdAccelerometerDoubleTappingData )
        {
        TSensrvTappingData accData;
        TPckg<TSensrvTappingData> accPackage( accData );
        aChannel.GetData( accPackage );
        
        callback_dir =  accData.iDirection;
        
        } 
         
     if( info.iChannelType == KSensrvChannelTypeIdOrientationData )
        {
        TSensrvOrientationData accData;
        TPckg<TSensrvOrientationData> accPackage( accData );
        aChannel.GetData( accPackage );
        
        callback_or =  accData.iDeviceOrientation;
        
        }  
        
     if( info.iChannelType == KSensrvChannelTypeIdRotationData )
        {
        TSensrvRotationData accData;
        TPckg<TSensrvRotationData> accPackage( accData );
        aChannel.GetData( accPackage );
        
        callback_rx =  accData.iDeviceRotationAboutXAxis;
        callback_ry =  accData.iDeviceRotationAboutYAxis;
        callback_rz =  accData.iDeviceRotationAboutZAxis;
        
        }      
        
     CActiveScheduler *Current = CActiveScheduler :: Current() ;
     Current->Stop() ;		
	}
	
void CSnrDataCallBack::DataError( CSensrvChannel& /*aChannel*/, 
                                TSensrvErrorSeverity /*aError*/)
	{
	}

void CSnrDataCallBack::GetDataListenerInterfaceL( TUid /*aInterfaceUid*/, 
                                TAny*& aInterface )
    {
    aInterface = NULL; // Extension interfaces are not supported
    }





