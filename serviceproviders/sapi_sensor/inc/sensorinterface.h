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

#ifndef C_CSENSORINTERFACE_H
#define C_CSENSORINTERFACE_H

#include <liwvariant.h>
#include <utf.h>

// User Includes
#include "sensorservice.hrh"
#include "sensorinterface.hrh"
#include "serviceerrno.h"
// Forward Declarations
class CSensorService;
class CStoreAsyncInfo;

/**
 * CSensorInterface - Provides interface between the Liw FrameWork
 * and Service Provider.
 */
class CSensorInterface : public CBase, public MLiwInterface
{
//enumerations for parameter indices.
private:
    enum TParamIndex
    {
    EParamIndex0 = 0,
    EParamIndex1,
    EParamIndex2,
    EParamIndex3,
    EParamIndex4
    };
public:// Construction and destruction
    /**
     * Two-phased constructor.
     * @return CSensorInterface*
     */
    static CSensorInterface* NewL();
    /**
     * Destructor
     */
    virtual ~CSensorInterface();

public:// General Methods

    /**
     * Returns the Corresponding Sapi Error Code.
     * @param aError Descriptor specifying format of image
     * @return SapiErrors.
     */
     static SapiErrors GetSapiErrorCode( TInt aError );

private:
    /**
     * Default constructor.
     */
    CSensorInterface();
    /**
     * Symbian OS constructor.
     * @return void
     */
    void ConstructL();
    /**
    * Executes the Commands passed by the user this method is called by the ExecuteCmdL method.
    *
    * @param aCmdName the name of the service command which the consumer wants to invoke
    * @param aInParamList the input parameter list, can be empty list
    * @param [in,out] aOutParamList the output parameter list.Return Code is
    * passed through this list
    * @param aCmdOptions Options for the command, see TLiwServiceCmdOptions in LiwCommon.hrh.
    * @param aCallback callback to be registered by consumer application
    *
    *
    *
    * @see TLiwServiceCmdOptions
    * @see CLiwGenericParamList
    * @see MLiwNotifyCallback
    *
    */
    void ExecuteServiceCommandL( const TDesC8& aCmdName,
                                 const CLiwGenericParamList& aInParamList,
                                 CLiwGenericParamList& aOutParamList,
                                 TUint aCmdOptions = 0,
                                 MLiwNotifyCallback* aCallback = 0 );
    /**
    * Extract Channel Information from input map
    * @param aChannelInfo Refers to channel info where information about the channel
    * will be extracted to.
    * @param aChnlInfoMap refers to input map containing channel info
    */

    void GetChannelInfoL( TSensrvChannelInfo& aChannelInfo,
                          const CLiwMap* aChnlInfoMap );

    /**
    * Returns Channel Property string from input property ID 
    * @param aPropertyId Refers to channel property id enum
    * @return Property Id string
    */
    TPtrC PropertyStrL( TSensrvPropertyId aPropertyId );

    /**
    * Returns Channel Property ID from input property ID string
    * @param aPropertyIdStr Refers to channel property id string
    * @return TSensrvPropertyId
    */
    TSensrvPropertyId PropertyIdInfoL( const TDesC& aPropertyIdStr );

    /**
    * Appends list of found channels to the out put parameter List
    *
    * @param aChannelInfoList: The List of channels found
    * @param aList List which will be populated and appended to outputparamList
    *
    */
    void AppendChannelInfoL( const RSensrvChannelInfoList& aChannelInfoList,
                             CLiwDefaultList* aList );
    
    /**
    * Appends list of found channel property to the out put parameter List
    *
    * @param aPropertyList: The List of channel property
    * @param aMap Map which will be populated and appended to outputparamList
    * @param aPropertyId Property id to be searched for
    */
    void AppendPropertyToMapL( const RSensrvPropertyList& aPropertyList,
                               CLiwDefaultMap* aMap,
                               const TUint aPropertyId );
	/*
	 * Function for validation of type of Input Containers
	 */
	void CheckInputTypeL( const TLiwVariant* aSource, 
						  LIW::TVariantTypeId aExpectedtype,
						  const TDesC8* aErrorArgument );
		
	/*
	 * Function for validation of missing params in Input Containers
	 */
	void MissingValueL( const TDesC8* aErrorArgument );

public:
   /**
    * provides a concrete implementation for the supported service
    * command aCmdName.
    *
    * @param aCmdName the name of the service command which the consumer wants to invoke
    * @param aInParamList the input parameter list, can be empty list
    * @param [in,out] aOutParamList the output parameter list.Return Code is
    * passed through this list
    * @param aCmdOptions Options for the command, see TLiwServiceCmdOptions in LiwCommon.hrh.
    * @param aCallback callback to be registered by consumer application
    *
    *
    *
    * @see TLiwServiceCmdOptions
    * @see CLiwGenericParamList
    * @see MLiwNotifyCallback
    *
    */
    virtual void ExecuteCmdL( const TDesC8& aCmdName,
                              const CLiwGenericParamList& aInParamList,
                              CLiwGenericParamList& aOutParamList,
                              TUint aCmdOptions = 0,
                              MLiwNotifyCallback* aCallback = 0 );
   /**
    * provides a concrete implementation
    * for this method.Deletes the interface handle.
    * The consumer application should call this method if there
    * are no more service commands to be executed on the interface.
    *
   */
    virtual void Close();

private:
    
    /**
     * Sensor service implementation object.
     */
    CSensorService* iSensorService;
    
    /**
     * Store Information about async calls
     */
    RPointerArray<CStoreAsyncInfo> iAsyncInfo;
    
    /**
     * Holds the error string
     */
    HBufC16* iErrorString;

};

#endif // C_CSENSORINTERFACE_H
