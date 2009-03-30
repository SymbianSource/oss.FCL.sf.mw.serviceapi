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
* Description:  Contaions implementaion for sensor callback class
*
*/

#include "sensorcallback.h"
#include "sensorservice.hrh"



/*
-----------------------------------------------------------------------------
    CSensorCallback* CSensorCallback::NewL()
    Description     : Two-phased constructor.
    Return values   : CSensorCallback object pointer

-----------------------------------------------------------------------------
*/
CSensorCallback* CSensorCallback::NewL( MLiwNotifyCallback* aCallBack,
                                        TInt32 aTransactionid)

    {
    CSensorCallback* self = new ( ELeave ) CSensorCallback( aCallBack,
                                                            aTransactionid );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;

    }

/*
-----------------------------------------------------------------------------
    void CSensorCallback::DataNotificationL()
    Description    : Called by sensor framework when sensor
                     channel data is received to send received
                     data to the client
    Return values  : N/A

-----------------------------------------------------------------------------
*/
void CSensorCallback::DataNotificationL( CSensrvChannel& aChannel )
    {
    
    //Array for orientation data
    const TPtrC gOrientationArr[] = 
	{
	KUndefined(),
	KDisplayUp(),
	KDisplayDown(),
	KDisplayLeftUp(),
	KDisplayRightUp(),
	KDisplayUpwards(),
	KDisplayDownwards()
	};
	
	//Conversion from Localtime returned by Sensor FW to UTC time
    TTime utcNow;
    utcNow.UniversalTime();
    TTime localNow;
    localNow.HomeTime();
    // convert UTC time to local time
    TTimeIntervalMicroSeconds diff = localNow.MicroSecondsFrom( utcNow );
	
    CleanupStack :: PushL( this );
    CLiwGenericParamList* outParamList = CLiwGenericParamList :: NewL();
    CleanupStack :: PushL( outParamList );
    CLiwGenericParamList* inputParamList = CLiwGenericParamList :: NewL();
    CleanupStack :: PushL( inputParamList );
    TSensrvChannelInfo info = aChannel.GetChannelInfo();

    TLiwGenericParam errorparam(KErrorCode , TLiwVariant(( TInt32 )KErrNone)) ;
    outParamList->AppendL(errorparam);
    
    CLiwDefaultMap* chnlDataMap = CLiwDefaultMap::NewL() ;
    CleanupStack::PushL( chnlDataMap );

    switch( info.iChannelType )
        {
            case EFindAccelerometerXYZAxisData:
                {
                TSensrvAccelerometerAxisData accData;
                TPckg<TSensrvAccelerometerAxisData> accPackage( accData );
                aChannel.GetData( accPackage );

                chnlDataMap->InsertL( KDataType ,
                                      TLiwVariant( KAcclmtrAxisData ) );
                chnlDataMap->InsertL( KTimeStamp ,
                                      TLiwVariant((TTime)( accData.iTimeStamp  - diff ) ) );
                chnlDataMap->InsertL( KXAxisData ,
                                      TLiwVariant((TInt32)( accData.iAxisX ) ) );
                chnlDataMap->InsertL( KYAxisData ,
                                      TLiwVariant((TInt32)( accData.iAxisY ) ) );
                chnlDataMap->InsertL( KZAxisData ,
                                      TLiwVariant((TInt32)( accData.iAxisZ ) ) );
                
                break;
                }
            case EFindAccelerometerDoubleTappingData:
                {
                TSensrvTappingData accData;
                TPckg<TSensrvTappingData> accPackage( accData );
                aChannel.GetData( accPackage );

                chnlDataMap->InsertL( KDataType ,
                                      TLiwVariant( KAcclmtrDoubleTappingData ) );
                chnlDataMap->InsertL( KTimeStamp ,
                                      TLiwVariant((TTime)( accData.iTimeStamp - diff ) ) );
                chnlDataMap->InsertL( KDirection ,
                                      TLiwVariant( (TInt32)(accData.iDirection) ) );

                break;
                }

            case EFindOrientationData:
                {
                TSensrvOrientationData accData;
                TPckg<TSensrvOrientationData> accPackage( accData );
                aChannel.GetData( accPackage );

                chnlDataMap->InsertL( KDataType ,
                                     TLiwVariant( KOrientationData ) );
                chnlDataMap->InsertL( KTimeStamp ,
                                      TLiwVariant((TTime)( accData.iTimeStamp - diff ) ) );

                TInt orientation = accData.iDeviceOrientation;
                chnlDataMap->InsertL( KDeviceOrientation,
                					  TLiwVariant( gOrientationArr[orientation] ) );
                break;
                }

            case EFindRotationData:
                {
                TSensrvRotationData accData;
                TPckg<TSensrvRotationData> accPackage( accData );
                aChannel.GetData( accPackage );

                chnlDataMap->InsertL( KDataType , TLiwVariant( KRotationData ) );
                chnlDataMap->InsertL( KTimeStamp ,
                                      TLiwVariant( (TTime) ( accData.iTimeStamp - diff ) ) );
                chnlDataMap->InsertL ( KAbtXAxis ,
                                       TLiwVariant((TInt32)( accData.iDeviceRotationAboutXAxis ) ) );
                chnlDataMap->InsertL( KAbtYAxis ,
                                      TLiwVariant((TInt32)( accData.iDeviceRotationAboutYAxis ) ) );
                chnlDataMap->InsertL( KAbtZAxis ,
                                      TLiwVariant((TInt32)( accData.iDeviceRotationAboutZAxis ) ) );


                break;
                }

        }
        
        TLiwGenericParam outParm( KReturnValue , TLiwVariant( chnlDataMap ) ) ;

        outParamList->AppendL( outParm ) ;
        CleanupStack::Pop( chnlDataMap );
        chnlDataMap->DecRef();
        
        //Notify user with the data received from a particular sensor channel
        iCallBack->HandleNotifyL( iTransactionId , KLiwEventInProgress , *outParamList , *inputParamList ) ;

        CleanupStack::PopAndDestroy( inputParamList );
        CleanupStack::PopAndDestroy( outParamList );
		CleanupStack::Pop( this );
    }


/*
-----------------------------------------------------------------------------
    void CSensorCallback::DataReceived()
    Description     : Called by sensor framework when sensor
                      channel data is received
    Return values   : N/A

-----------------------------------------------------------------------------
*/
void CSensorCallback::DataReceived( CSensrvChannel& aChannel,
                                    TInt /*aCount*/,
                                    TInt /*aDataLost*/ )

    {
    TInt err = 0;
    TRAP( err , DataNotificationL( aChannel ) );
    }

/*
-----------------------------------------------------------------------------
    void CSensorCallback::DataError()
    Description    : Called by sensor framework when an
                     error occurs
    Return values  : N/A

-----------------------------------------------------------------------------
*/
void CSensorCallback::DataError( CSensrvChannel& /*aChannel*/,
                                 TSensrvErrorSeverity /*aError*/ )
    {
    }


/*
-----------------------------------------------------------------------------
    void CSensorCallback::GetDataListenerInterfaceL()
    Description    : Returns a pointer to a specified interface - to allow 
                     future extension of this class without breaking binary 
                     compatibility
    Return values  : N/A

-----------------------------------------------------------------------------
*/        
void CSensorCallback::GetDataListenerInterfaceL( TUid /*aInterfaceUid*/, 
                                TAny*& aInterface )
    {
    aInterface = NULL; // Extension interfaces are not supported
    }


/*
-----------------------------------------------------------------------------
    CSensorCallback::CSensorCallback()
    Description    : Constructor
    Return values  : N/A
-----------------------------------------------------------------------------
*/
CSensorCallback::CSensorCallback( MLiwNotifyCallback* aCallBack,
                                  TInt32 aTransactionid )
                                 :iCallBack( aCallBack ),
                                  iTransactionId( aTransactionid )
    {
    }

/*
-----------------------------------------------------------------------------
    void CSensorCallback::ConstructL()
    Description         : Symbian 2nd phase constructor can leave.
    Return values       : N/A
-----------------------------------------------------------------------------
*/
void CSensorCallback::ConstructL()
    {
    }

/*
-----------------------------------------------------------------------------
    CSensorCallback::~CSensorCallback()
    Description     : Destructor, free allocated resources
    Return values   : N/A
-----------------------------------------------------------------------------
*/
CSensorCallback::~CSensorCallback()
    {
    }

 
