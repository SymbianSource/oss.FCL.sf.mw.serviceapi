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
* Description:  Provides interface between the Liw FrameWork and Service Provider.
*
*/

//system include
#include <LiwVariant.h>
#include <LiwGenericParam.h>
#include <LiwCommon.h>
#include <sensrvchannelinfo.h>
#include <sensrvtypes.h>

// User Includes
#include "sensorservice.h"
#include "sensorinterface.h"
#include "sensorservice.hrh"
#include "sensorcallback.h"
#include "storeasyncinfo.h"

inline void CSensorInterface::CheckInputTypeL
                            ( const TLiwVariant* aSource,
							  LIW::TVariantTypeId aExpectedtype,
							  const TDesC8* aErrorArgument )
	{
	if( aSource->TypeId() != aExpectedtype )
		{
		iErrorString = HBufC::NewL(KMaxMsgSize);
        TPtr ptr(iErrorString->Des());
        TBuf<KMaxKeySize> buf;
        buf.Copy( *aErrorArgument );
        ptr.Append(buf);
        ptr.Append( KTypeErr.operator()());
		ptr.Append( KInvalid.operator()());
		User::Leave( KErrArgument );
		}
	}
	
inline void CSensorInterface::MissingValueL( const TDesC8* aErrorArgument )
	{
	iErrorString = HBufC::NewL(KMaxMsgSize);
    TPtr ptr(iErrorString->Des());
    TBuf<KMaxKeySize> buf;
    buf.Copy( *aErrorArgument );
    ptr.Append(buf);
    ptr.Append( KMissing.operator()());
    User::Leave( SErrMissingArgument );
	}	


/*
-----------------------------------------------------------------------------
    CSensorInterface::CSensorInterface()
    Description    : Constructor
    Return values  : N/A
-----------------------------------------------------------------------------
*/
CSensorInterface::CSensorInterface()
                : iSensorService( NULL )
    {
    }

/*
-----------------------------------------------------------------------------
    void CSensorInterface::ConstructL()
    Description         : Symbian 2nd phase constructor can leave.
    Return values       : N/A
-----------------------------------------------------------------------------
*/
void CSensorInterface::ConstructL()
    {
    iSensorService = CSensorService::NewL();
    }


/*
-----------------------------------------------------------------------------
    CSensorInterface::ExecuteServiceCommandL()
    Description     : This is called by the consumer with command to execute.
    Return values   : N/A
-----------------------------------------------------------------------------
*/
void CSensorInterface::ExecuteServiceCommandL
                     ( const TDesC8& aCmdName,
                       const CLiwGenericParamList& aInParamList,
                       CLiwGenericParamList& aOutParamList,
                       TUint aCmdOptions,
                       MLiwNotifyCallback* aCallback )
    {
    
    aOutParamList.Reset();
    
    TInt position = 0;
    TInt32 transId = 0;

    // Start of FindSensorChannel
    if ( (aCmdName.CompareF( KCmdFindChannel ) == 0)  )
        {
        if( aCallback )
            {
            iErrorString = KErrSensorInvalidReq.operator()().Alloc();
            User::Leave( SErrInvalidServiceArgument );
            }
        
        TPtrC searchString;
        const TLiwGenericParam* findString = NULL;
        findString = aInParamList.FindFirst( position, KSearchCriterion );

        if ( !findString )
            {
            //Position based parsing
            if( aInParamList.Count() != 0 )
	    		{
				findString =  &aInParamList[EParamIndex0];
				}
            else
               {
               iErrorString = KErrFindSensorChannelMissingSearchCrit.operator()().Alloc();
               User::Leave( SErrMissingArgument );
               }
            }

        TInt searchCriterion = 0;

		CheckInputTypeL( &findString->Value(),
	       				 LIW::EVariantTypeDesC,
	       				 KErrFindSensorChannelBadSrchType.operator&() );

        // Retrieve channel search condition specified in input parameter list
        findString->Value().Get( searchString );

        if ( searchString == KAll )
            searchCriterion = EFindAll;
        else if ( searchString == KAcclmtrAxis )
            searchCriterion = EFindAccelerometerXYZAxisData;
        else if ( searchString == KAcclmtrDoubleTapping )
            searchCriterion = EFindAccelerometerDoubleTappingData;
        else if ( searchString == KOrientation )
            searchCriterion = EFindOrientationData;
        else if ( searchString == KRotation )	
            searchCriterion = EFindRotationData;
        else
        	{
        	iErrorString = KErrFindSensorChannelInvalidSrch.operator()().Alloc();
        	User::Leave( SErrInvalidServiceArgument );
        	}

        // channelInfoList will be populated by core class API
        RSensrvChannelInfoList channelInfoList;
        CleanupClosePushL( channelInfoList );

        iSensorService->FindSensorChannelsL( searchCriterion ,
                                             channelInfoList );

        // Create list instance
        CLiwDefaultList* chnlList = CLiwDefaultList::NewL();
        CleanupStack::PushL( chnlList );
        // Obtain channel info list
        
   	    AppendChannelInfoL( channelInfoList ,chnlList );

        // Appending result to the output parameter list
        aOutParamList.AppendL( TLiwGenericParam( KReturnValue,
                               TLiwVariant( chnlList ) ) );

        CleanupStack::Pop( chnlList );
        CleanupStack::PopAndDestroy( &channelInfoList );
        chnlList->DecRef();

        }//end of FindSensorChannel
        //Start of RegisterForNotification
    else if ( ( aCmdName.CompareF( KCmdRegisterForNotification ) == 0 ) )
        {
        
        if(	( aCallback  && ( KLiwOptASyncronous & aCmdOptions ) ) )
        	{
        	
        	transId = aCallback->GetTransactionID();
        	
	        TPtrC listeningStrPtr;
	        const TLiwGenericParam* listeningString = NULL;
	        const TLiwGenericParam* chnlInfoParam = NULL;
	        CStoreAsyncInfo* info = NULL;
   	        TSensrvChannelInfo channelInfo;

	        if( aInParamList.Count() < 2 )
		    	{
		    	iErrorString = KErrRegNotEnoughParams.operator()().Alloc();
		        User::Leave( SErrMissingArgument );
		        }
	        
	        position = 0;
	        listeningString = aInParamList.FindFirst( position, KListeningType );
	        position = 0;
	        chnlInfoParam = aInParamList.FindFirst( position, KChnlInfoMap );
	        if( !listeningString )
	            {
		        //position based parsing
		        listeningString =  &aInParamList[EParamIndex0];
		        if ( ( !listeningString ) )
		        	{
		           	iErrorString = KErrRegNotifyMissingListening.operator()().Alloc();
		           	User::Leave( SErrMissingArgument );
		           	}

		        chnlInfoParam = &aInParamList[EParamIndex1];
		        if ( ( !chnlInfoParam ) )
		        	{
		            iErrorString = KErrMissingChnlMap.operator()().Alloc();
		            User::Leave( SErrMissingArgument );
		            }
		        }

            CheckInputTypeL( &listeningString->Value(),
	            			 LIW::EVariantTypeDesC,
	            			 KErrRegNotifyInvalidListeningType.operator&() );

            CheckInputTypeL( &chnlInfoParam->Value(),
            				 LIW::EVariantTypeMap,
            				 KChnlInfoMap.operator&() );

	        // Retrieve Listening Type
	        listeningString->Value().Get( listeningStrPtr );
			
	        //Leave if there is no listening type or is invalid
	        if( listeningStrPtr != KChnlData )
	            {
	            iErrorString = KErrRegNotifyInvalidListening.operator()().Alloc();
	            User::Leave( SErrInvalidServiceArgument );
	            }
	            				 
            const CLiwMap* chnlInfoMap = ( chnlInfoParam->Value() ).AsMap();
            //Retrieve channel information from input List
            GetChannelInfoL( channelInfo ,chnlInfoMap );

	        //Create CallBack
	        CSensorCallback* callBack = CSensorCallback::NewL( aCallback,
	                                                           transId );
	        CleanupStack::PushL( callBack );
	        TAsyncType asyncType(EInvalid);
	        TInt notificationErr(0);
	        //Data notification
	        if ( listeningStrPtr == KChnlData )
	            {
	            TRAP( notificationErr, iSensorService->GetDataNotificationL
				                     ( channelInfo,
				                       callBack ) );
				
				if( notificationErr != KErrNone )
					{
		            iErrorString = KErrInvalidNotif.operator()().Alloc();
		            User::Leave( KErrInUse );
					}
					
	            asyncType = EData;
	            }
	        else
	            {
	            iErrorString = KErrRegNotifyInvalidListening.operator()().Alloc();
	            User::Leave( SErrInvalidServiceArgument );
	            }

	        // Store information about this async call
	        info = CStoreAsyncInfo::NewL( asyncType,
	                                      transId,
	                                      callBack,
	                                      channelInfo.iChannelId );
	        iAsyncInfo.Append( info );

	        //Appending trans id to the output parameter list
	        aOutParamList.AppendL( TLiwGenericParam( KTransactionId ,
	                               TLiwVariant ( ( TInt32 )transId ) ) );

	        CleanupStack::Pop( callBack );

        	}
        else
        	{
        	iErrorString = KErrRegNotifyAsyncbit.operator()().Alloc();
        	User::Leave( SErrMissingArgument );
        	}

        }//End of RegisterForNotification
    // Start of StopNotification
    else if ( ( aCmdName.CompareF( KStopNotification ) == 0 ) )
        {
        
        if( aCallback )
            {
            iErrorString = KErrSensorInvalidReq.operator()().Alloc();
            User::Leave( SErrInvalidServiceArgument );
            }
        
        if( ! ( KLiwOptCancel & aCmdOptions) )
        	{
        	iErrorString = KErrStopNotifCancelBit.operator()().Alloc();
        	User::Leave( SErrMissingArgument );
        	}
        
        TInt32 transId = 0;
        const TLiwGenericParam* transIdParam = NULL;
        TAsyncType asyncType;
        TUint chnlId = 0;
        TInt asyncCount = 0;
        CStoreAsyncInfo* info = NULL;
        TInt i = 0;
        TBool transFound = FALSE;

        position = 0;
        transIdParam = aInParamList.FindFirst( position , KTransactionId );
        position = 0;

        if ( !transIdParam )
            {
            if( aInParamList.Count() != 0 )
            	{
            	transIdParam = &aInParamList[EParamIndex0];	
            	}
            else
            	{
                iErrorString = KErrStopNotifMissingTransId.operator()().Alloc();
                User::Leave( SErrMissingArgument );
            	}
            }

		CheckInputTypeL( &transIdParam->Value(),
	       				 LIW::EVariantTypeTInt32,
	       				 KTransactionId.operator&() );
		
        // Obtain transaction id from input list
        transIdParam->Value().Get( transId );
        
        // Get count of async calls
        asyncCount = iAsyncInfo.Count();
        
        // Search within the async call list for the transaction ID
        for( i = 0; i < asyncCount; i++ )
            {
            info = iAsyncInfo[i];
            if( transId == ( info->iTransactionId ) )
                {
                // Transaction id is found
                transFound = TRUE;
                break;
                }
            }
        // If found then cancel the request for notification on service class
        if( transFound )
            {
            asyncType = info->iAsyncType;
            chnlId = info->ichnlId;

            switch( asyncType )
                {
                case EData:  // To stop data notification
                    iSensorService->StopNotificationL( EStopData,chnlId );
                    break;
                }

            //Remove this from the store of async functions
            iAsyncInfo.Remove( i );
            delete info->iCallback;
            delete info;
            info = NULL;
            }
        else
            {
            // Incorrect transaction id
            iErrorString = KErrStopNotifInvalidTransId.operator()().Alloc();
            User::Leave( SErrInvalidServiceArgument );
            }

        }//End of command StopNotification
     // Start of GetChannelProperty
     else if ( ( aCmdName.CompareF( KCmdGetChnlProperty ) == 0 ) )
        {
        
        if( aCallback )
            {
            iErrorString = KErrSensorInvalidReq.operator()().Alloc();
            User::Leave( SErrInvalidServiceArgument );
            }
        
        const TLiwGenericParam* channelParam = NULL;
        const TLiwGenericParam* propertyIdParam= NULL;
		//Retreive property id for filling output map
        TSensrvPropertyId propertyId = 0;
        TPtrC propertyIdStr;
		
		if( aInParamList.Count() < 2)
        	{
            iErrorString = KErrRegNotEnoughParams.operator()().Alloc();
    	    User::Leave( SErrMissingArgument );
        	}

        channelParam = aInParamList.FindFirst( position, KChnlInfoMap );
        position = 0;
        propertyIdParam = aInParamList.FindFirst( position, KPropId );

        if ( !channelParam )
            {
            channelParam =  &aInParamList[EParamIndex0];
            if ( !channelParam )
               	{
               	iErrorString = KErrMissingChnlMap.operator()().Alloc();
               	User::Leave( SErrMissingArgument );
               	}
            propertyIdParam = &aInParamList[EParamIndex1];
            if ( !propertyIdParam )
	            {
	            iErrorString = KErrMissingPropId.operator()().Alloc();
    	        User::Leave( SErrMissingArgument );
	            }
            }
				
        // Obtain channel info from input map
        CheckInputTypeL( &channelParam->Value(),
           				 LIW::EVariantTypeMap,
           				 KChnlInfoMap.operator&() );

        CheckInputTypeL( &propertyIdParam->Value(),
           				 LIW::EVariantTypeDesC,
           				 KPropId.operator&() );

        TSensrvChannelInfo channelInfo;
        const CLiwMap* chnlInfoMap = ( channelParam->Value() ).AsMap();
        //Retreive Channel Info
        GetChannelInfoL( channelInfo , chnlInfoMap );

        propertyIdParam->Value().Get( propertyIdStr );
        propertyId = PropertyIdInfoL( propertyIdStr );

        // Obtain property list from service class
        RSensrvPropertyList propertyList;
        CleanupClosePushL( propertyList );
        TRAPD( getPropErr, iSensorService->GetChannelPropertyL
                                         ( channelInfo,
                                           propertyList ) );
		
		if( getPropErr != KErrNone )
			{
			CleanupStack::PopAndDestroy( &propertyList );
            iErrorString = KErrInvalidChnlMap.operator()().Alloc();
            User::Leave(KErrArgument);
			}

        // Create output map
        CLiwDefaultMap* outMap = CLiwDefaultMap::NewL();
        CleanupStack::PushL( outMap );

        // Append property from list to output map
        TRAPD( findPropErr ,AppendPropertyToMapL( propertyList,
                                                  outMap,
                                                  propertyId ) );
		
		if( findPropErr != KErrNone )
			{
            iErrorString = KErrPropNotSupported.operator()().Alloc();
			CleanupStack::Pop( outMap );
            CleanupStack::PopAndDestroy( &propertyList );
            outMap->DecRef();
            User::Leave(KErrNotFound);
			}

        //Appending result to the output parameter list
        aOutParamList.AppendL( TLiwGenericParam( KReturnValue ,
                                                 TLiwVariant( outMap ) ) );

        CleanupStack::Pop( outMap );
        CleanupStack::PopAndDestroy( &propertyList );
        outMap->DecRef();

        }//end of GetChannelProperty
     else
      	{
       	iErrorString = KErrSensorInvalidCmd.operator()().Alloc();
        User::Leave( KErrNotSupported );
        }
    }

/*
-----------------------------------------------------------------------------
    CSensorInterface* CSensorInterface::NewL()
    Description                       : Two-phased constructor.
    Return values                     : CSensorInterface object pointer

-----------------------------------------------------------------------------
*/
CSensorInterface* CSensorInterface::NewL()
    {
    CSensorInterface* self = new ( ELeave ) CSensorInterface();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }
/*
-----------------------------------------------------------------------------
    CSensorInterface::~CSensorInterface()
    Description     : Destructor, free allocated resources
    Return values   : N/A
-----------------------------------------------------------------------------
*/
CSensorInterface::~CSensorInterface()
    {
    
    TInt count = iAsyncInfo.Count();
    CStoreAsyncInfo* info = NULL;
    
    TAsyncType asyncType = EInvalid;
    TInt stopErr;
    TUint chnlId = 0;
    
    //Cleanup async info store
    for( TInt i = 0; i< count; i++)
        {
        info = iAsyncInfo[i];
        if( info )
        	{
	        asyncType = info->iAsyncType;
	        chnlId = info->ichnlId;
        	}

        switch( asyncType )
			{
			case EData:  // To stop data notification
				{
				if( iSensorService )
					{
	            	TRAP( stopErr,
    	        		  iSensorService->StopNotificationL( EStopData,
    	        		  									 chnlId ) );
					}
                break;
				}
            }
        
        if( info->iCallback )
        	{
			delete info->iCallback;
			info->iCallback = NULL;        	
        	}

        
        if( info )
        	{
        	delete info;
        	info = NULL;
        	}
        }
    
    iAsyncInfo.Reset();

    if( iSensorService )
    	delete iSensorService;
    
    if( iErrorString )
    	delete iErrorString;

    }

/*
-----------------------------------------------------------------------------
    CSensorInterface::GetSapiErrorCode()
    Description     : Returns the Sapi Error Code.
    Return values   : SapiErrors
-----------------------------------------------------------------------------
*/
SapiErrors CSensorInterface:: GetSapiErrorCode( TInt aError )
    {
    SapiErrors sapiErr = SErrNone;
    switch ( aError )
        {
		case KErrArgument: 
			{
			sapiErr = SErrBadArgumentType;
			break;
			}
		case KErrNotSupported:
			{
			sapiErr = SErrServiceNotSupported;
			break;
			} 
		case KErrNone:
			{
			sapiErr= SErrNone;
			break; 
			} 
		case KErrNotFound:
			{
			sapiErr= SErrNotFound;
			break; 
			}
		case SErrMissingArgument:
			{
			sapiErr = SErrMissingArgument;
			break; 
			}
        case SErrInvalidServiceArgument:
			{
			sapiErr = SErrInvalidServiceArgument;
			break; 
			}
		case KErrInUse:
            {
            sapiErr = SErrServiceInUse;
            break;
        	}
        }
        return sapiErr;
    }

/*
-----------------------------------------------------------------------------
    CSensorInterface::ExecuteCmdL()
    Description     : This is called by the consumer with command to execute.
    Return values   : N/A
-----------------------------------------------------------------------------
*/
void CSensorInterface::ExecuteCmdL( const TDesC8& aCmdName,
                                    const CLiwGenericParamList& aInParamList,
                                    CLiwGenericParamList& aOutParamList,
                                    TUint aCmdOptions,
                                    MLiwNotifyCallback* aCallback )
    {
    TRAPD( err, ExecuteServiceCommandL( aCmdName,
                                        aInParamList,
                                        aOutParamList,
                                        aCmdOptions,
                                        aCallback ) );
    if( err != KErrNone )
        {
        	
		if( iErrorString )
			{
			TBuf<KErrMessageLen> errorMessage;	
			errorMessage.Append( KMsgErr.operator()() );
			TBuf<KCmdLen> commandName;	
			commandName.Copy( aCmdName );	
			errorMessage.Append( commandName );	
			errorMessage.Append( KColon.operator()());
			errorMessage.Append( iErrorString->Des() );

			aOutParamList.AppendL(TLiwGenericParam( KErrorMessage, 
			 					  TLiwVariant( errorMessage )));
			}
        }
    
	TInt32 returnCode = CSensorInterface::GetSapiErrorCode( err );
	aOutParamList.AppendL( TLiwGenericParam( KErrorCode,
                           TLiwVariant( ( TInt32 ) returnCode ) ) );
        
    }

/*
-----------------------------------------------------------------------------
    CSensorInterface::Close()
    Description     : This is called by the consumer to delete the handle.
    Return values   : N/A
-----------------------------------------------------------------------------
*/
void CSensorInterface::Close()
    {
    delete this;
    }

/*
-----------------------------------------------------------------------------
    CSensorInterface::AppendChannelInfoL()
    Description     : Internal function used to append result of found sensor
                     channel to the outputlist
    Return values   : N/A
-----------------------------------------------------------------------------
*/
void CSensorInterface::AppendChannelInfoL
                     ( const RSensrvChannelInfoList& aChannelInfoList,
                       CLiwDefaultList* aList)
    {
    // Obtain channel count
    TInt channelCount = aChannelInfoList.Count();

    for(TInt i = 0; i < channelCount; i++)
        {
        
        TInt32 chnlType = (TInt32)aChannelInfoList[i].iChannelType;
        
        switch(chnlType)
        	{
        	case EFindAccelerometerXYZAxisData:
        	case EFindAccelerometerDoubleTappingData:
        	case EFindOrientationData:
        	case EFindRotationData:
        		{
        		// Map to be appended to the list
		        CLiwDefaultMap* chnlMap = CLiwDefaultMap::NewL() ;
		        CleanupStack::PushL( chnlMap );

		        //Retreive channel information
		        TInt32 chnlId = (TInt32)aChannelInfoList[i].iChannelId;
		        TInt32 contextType = aChannelInfoList[i].iContextType;
		        TInt32 quantity = aChannelInfoList[i].iQuantity;
		        TBuf8<KSensrvLocationLength> location( aChannelInfoList[i].iLocation );
		        TBuf8<KSensrvVendorIdLength> vendorId( aChannelInfoList[i].iVendorId );
		        TInt32 dataItemSize = aChannelInfoList[i].iDataItemSize;
		        TInt32 chnlDataTypeId = (TInt32)aChannelInfoList[i].iChannelDataTypeId;

				_LIT( KDummyLoc, "Unknown" );
				TBufC<KSensrvLocationLength> dummyLoc( KDummyLoc );
				TPtr location16 = dummyLoc.Des();
				CnvUtfConverter::ConvertToUnicodeFromUtf8( location16, location );

				_LIT( KDummyVen, "Unknown" );
				TBufC<KSensrvVendorIdLength> dummyVen( KDummyVen );
				TPtr vendor16 = dummyVen.Des();
				CnvUtfConverter::ConvertToUnicodeFromUtf8( vendor16, vendorId );

		        // Insert channel info to the map
		        chnlMap->InsertL( KChnlId ,TLiwVariant( (TInt32)chnlId ) );
		        chnlMap->InsertL( KContextType ,TLiwVariant( (TInt32)contextType ) );
		        chnlMap->InsertL( KQuantity ,TLiwVariant( (TInt32)quantity ) );
		        chnlMap->InsertL( KChannelType ,TLiwVariant( (TInt32)chnlType ) );
		        chnlMap->InsertL( KLocation , TLiwVariant( location16 ) );
		        chnlMap->InsertL( KVendorId , TLiwVariant( vendor16 ) );
		        chnlMap->InsertL( KDataItemSize ,TLiwVariant( (TInt32)dataItemSize ) );
		        chnlMap->InsertL( KChnlDataTypeId ,TLiwVariant( (TInt32)chnlDataTypeId ) );

		        //Append it to the list
		        aList->AppendL( TLiwVariant( chnlMap ) );
		        CleanupStack::Pop( chnlMap );

		        //done with the map
		        chnlMap->DecRef();
		        break;
        		}
			default:
				break;
        	
        	}
        }
    }

/*
-----------------------------------------------------------------------------
    CSensorInterface::AppendPropertyToMapL()
    Description     : Internal function used to append result of get property 
                      to the output map
    Return values   : N/A
-----------------------------------------------------------------------------
*/
void CSensorInterface::AppendPropertyToMapL
   ( const RSensrvPropertyList& aPropertyList,
     CLiwDefaultMap* aMap,
     const TUint aPropertyId)
    {
    // Obtain property count
    TInt propCount = aPropertyList.Count();

    // If no properties listed then leave with error - Not found
    if( propCount == 0 )
        {
        User::Leave( KErrNotFound );
        }
    
    TInt i = 0; // Loop variable
    TSensrvProperty tempProperty; // Property for copy from property list
    TSensrvProperty tempProperty1;// Property for obtaining value in array

    TBool found = FALSE;

    TInt propType = 0;
    TInt intVal;
    TReal rValue;
    TBuf8<KBufSize> bufValue;
    TInt32 itemIndex;
	
    // Search within property list and fill output map
    for ( i = 0; i < propCount; i++ )
        {
        tempProperty = aPropertyList[i];
		
        if( aPropertyId == ( tempProperty.GetPropertyId() ) )
            {
            // Property has been found
            found = TRUE;
            TPtrC propertyStr = PropertyStrL( aPropertyId );
            aMap->InsertL( KPropId ,TLiwVariant( propertyStr ) );

            // Obtain item index,property type and read only
            itemIndex = tempProperty.PropertyItemIndex();
            propType = tempProperty.PropertyType();

            // Insert item index,property type and read only into output map
            aMap->InsertL( KPropertyDataType ,TLiwVariant( (TInt32) ( propType - 1 ) ) );
            aMap->InsertL( KItemIndex ,TLiwVariant( (TInt32) itemIndex ) );
            aMap->InsertL( KReadOnly ,TLiwVariant(1) );
            
            // For single property,just fill the actual values
            if( ESensrvSingleProperty == ( tempProperty.GetArrayIndex() ) )
                {
                
                // Obtain values for integer property
                if( propType == ESensrvIntProperty )
                    {
                    tempProperty.GetValue( intVal );
                    aMap->InsertL( KPropertyValue ,TLiwVariant( (TInt32) intVal ) );
                    }
                // Obtain values for real property
                else if( propType == ESensrvRealProperty )
                    {
                    tempProperty.GetValue( rValue );
                    aMap->InsertL( KPropertyValue ,TLiwVariant( rValue ) );
                    }
                // Obtain values for string property
                else if( propType == ESensrvBufferProperty )
                    {
                    tempProperty.GetValue( bufValue );
                    _LIT( KDummyDesc, "Unknown" );
					TBufC<KSensrvLocationLength> dummyDesc( KDummyDesc );
					TPtr description16 = dummyDesc.Des();
					CnvUtfConverter::ConvertToUnicodeFromUtf8( description16, bufValue );

                    aMap->InsertL( KPropertyValue ,TLiwVariant( description16 ) );
                    }
                break;
                }
            // If array property then get values from the actual listed props
            else if( ESensrvArrayPropertyInfo == ( tempProperty.GetArrayIndex() ) )
                {
                // For integer property
                if( propType == ESensrvIntProperty )
                    {
                    TInt indexVal;
                    tempProperty.GetValue( indexVal );
                    tempProperty1 = aPropertyList[ i + indexVal ];
                    tempProperty1.GetValue( intVal );
                    aMap->InsertL( KPropertyValue ,TLiwVariant( (TInt32) intVal ) );
                    }
                // For real property
                else if( propType == ESensrvRealProperty )
                    {
                    TReal indexVal;
                    tempProperty.GetValue( indexVal );
                    tempProperty1 = aPropertyList[ i + indexVal ];
                    tempProperty1.GetValue( rValue );
                    aMap->InsertL( KPropertyValue ,TLiwVariant( rValue ) );
                    }
                break;
                }

            }
        else
            continue;
        }
    
    // If property not found then leave with error - not found
    if( found == FALSE )
    	{
    	User::Leave( KErrNotFound );
    	}
        
    }


/*
-----------------------------------------------------------------------------
    CSensorInterface::GetChannelInfoL()
    Description     : Internal function used to extract channel info from the
                    : Input
    Return values   : N/A
-----------------------------------------------------------------------------
*/
void CSensorInterface::GetChannelInfoL( TSensrvChannelInfo& aChannelInfo,
                                        const CLiwMap* aChnlInfoMap )
    {
    TLiwVariant infoVariant;
    
    if( aChnlInfoMap->FindL( KChnlId , infoVariant ) ) 
    	{
		CheckInputTypeL( &infoVariant,
						 LIW::EVariantTypeTInt32,
						 KChnlId.operator&() );
						 
    	aChannelInfo.iChannelId = infoVariant.AsTInt32();	
    	}
	else
		{
		infoVariant.Reset();
		MissingValueL( KChnlId.operator&() );
		}
		
    if( aChnlInfoMap->FindL( KContextType , infoVariant ) )
    	{
		CheckInputTypeL( &infoVariant,
 					     LIW::EVariantTypeTInt32,
						 KContextType.operator&() );

    	aChannelInfo.iContextType = infoVariant.AsTInt32();	
    	}
    else
    	{
    	infoVariant.Reset();
    	MissingValueL( KContextType.operator&() );
    	}

    if( aChnlInfoMap->FindL( KQuantity , infoVariant ) )
    	{
		CheckInputTypeL( &infoVariant,
 					     LIW::EVariantTypeTInt32,
						 KQuantity.operator&() );

    	aChannelInfo.iQuantity = infoVariant.AsTInt32();	
    	}
    else
    	{
    	infoVariant.Reset();
    	MissingValueL( KQuantity.operator&() );
    	}

    if( aChnlInfoMap->FindL( KChannelType , infoVariant ) )
    	{
		CheckInputTypeL( &infoVariant,
						 LIW::EVariantTypeTInt32,
						 KChannelType.operator&() );

    	aChannelInfo.iChannelType = infoVariant.AsTInt32();	
    	}
    else
    	{
    	infoVariant.Reset();
    	MissingValueL( KChannelType.operator&() );
    	}

    if( aChnlInfoMap->FindL( KLocation , infoVariant ) )
    	{
		CheckInputTypeL( &infoVariant,
 					     LIW::EVariantTypeDesC,
						 KLocation.operator&() );
		
		TPtrC location16 = infoVariant.AsDes();
   		TBuf8<KSensrvLocationLength> location8;
   		CnvUtfConverter::ConvertFromUnicodeToUtf8( location8, location16 );
		
    	aChannelInfo.iLocation = location8;	
    	}
    else
    	{
    	infoVariant.Reset();
    	MissingValueL( KLocation.operator&() );
    	}

    if( aChnlInfoMap->FindL( KVendorId , infoVariant ) )
    	{
		CheckInputTypeL( &infoVariant,
 					     LIW::EVariantTypeDesC,
						 KVendorId.operator&() );

		TPtrC vendorId16 = infoVariant.AsDes();
   		TBuf8<KSensrvVendorIdLength> vendorId8;
   		CnvUtfConverter::ConvertFromUnicodeToUtf8( vendorId8, vendorId16 );

    	aChannelInfo.iVendorId = vendorId8;
    	}
    else
    	{
    	infoVariant.Reset();
    	MissingValueL( KVendorId.operator&() );
    	}

    if( aChnlInfoMap->FindL( KDataItemSize , infoVariant ) )
    	{
		CheckInputTypeL( &infoVariant,
 					     LIW::EVariantTypeTInt32,
						 KDataItemSize.operator&() );

    	aChannelInfo.iDataItemSize = infoVariant.AsTInt32();	
    	}
    else
    	{
    	infoVariant.Reset();
    	MissingValueL( KDataItemSize.operator&() );
    	}

    if( aChnlInfoMap->FindL( KChnlDataTypeId , infoVariant ) )
    	{
		CheckInputTypeL( &infoVariant,
						 LIW::EVariantTypeTInt32,
						 KChnlDataTypeId.operator&() );
    	
    	aChannelInfo.iChannelDataTypeId = infoVariant.AsTInt32();	
    	}
    else
    	{
    	infoVariant.Reset();
    	MissingValueL( KChnlDataTypeId.operator&() );
    	}
	infoVariant.Reset();
    }

/*
-----------------------------------------------------------------------------
    CSensorInterface::PropertyStr()
    Description     : Internal function used to extract property string from
                    : the input property id
    Return values   : N/A
-----------------------------------------------------------------------------
*/
TPtrC CSensorInterface::PropertyStrL( TSensrvPropertyId aPropertyId )
	{
	
	TPtrC ptr;
	
	switch( aPropertyId )
		{
		case KSensrvPropIdDataRate:
			 ptr.Set( KDataRate );
			 break;

		case KSensrvPropIdAvailability:
			 ptr.Set( KAvailability );
			 break;

		case KSensrvPropIdMeasureRange:
			 ptr.Set( KMeasureRange );
			 break;
	 
		case KSensrvPropIdChannelDataFormat:
			 ptr.Set( KChannelDataFormat );
			 break;

		case KSensrvPropIdChannelAccuracy:
			 ptr.Set( KChannelAccuracy );
			 break;

		case KSensrvPropIdChannelScale:
			 ptr.Set( KChannelScale );
			 break;

		case KSensrvPropIdScaledRange:
			 ptr.Set( KScaledRange );
			 break;

		case KSensrvPropIdChannelUnit:
			 ptr.Set( KChannelUnit );
			 break;

		case KSensrvSensorModel:
			 ptr.Set( KSensorModel );
			 break;

		case KSensrvSensorConnectionType:
			 ptr.Set( KConnectionType );
			 break;

		case KSensrvSensorDescription:
			 ptr.Set( KSensorDescription );
			 break;

		default:
            User::Leave( KErrNotSupported );
		}
	return ptr;
	}

/*
-----------------------------------------------------------------------------
    CSensorInterface::PropertyIdInfoL()
    Description     : Internal function used to extract property id info from
                    : the Input
    Return values   : N/A
-----------------------------------------------------------------------------
*/
TSensrvPropertyId CSensorInterface::PropertyIdInfoL( const TDesC& aPropertyIdStr )
    {
    TSensrvPropertyId propId = 0;

        if( aPropertyIdStr == KDataRate )
            propId = KSensrvPropIdDataRate;
        else if( aPropertyIdStr == KAvailability )
            propId = KSensrvPropIdAvailability;
        else if( aPropertyIdStr == KMeasureRange )
            propId = KSensrvPropIdMeasureRange;
        else if( aPropertyIdStr == KChannelDataFormat )
            propId = KSensrvPropIdChannelDataFormat;
        else if( aPropertyIdStr == KChannelAccuracy )
            propId = KSensrvPropIdChannelAccuracy;
        else if( aPropertyIdStr == KChannelScale )
            propId = KSensrvPropIdChannelScale;
        else if( aPropertyIdStr == KScaledRange )
            propId = KSensrvPropIdScaledRange;
        else if( aPropertyIdStr == KChannelUnit )
            propId = KSensrvPropIdChannelUnit;
        else if( aPropertyIdStr == KSensorModel )
            propId = KSensrvSensorModel;
        else if( aPropertyIdStr == KConnectionType )
            propId = KSensrvSensorConnectionType;
        else if( aPropertyIdStr == KSensorDescription )
            propId = KSensrvSensorDescription;
        else
        	{
        	iErrorString = KErrPropInvalidPropId.operator()().Alloc();
        	User::Leave( SErrInvalidServiceArgument );
        	}
    return propId;
    }
