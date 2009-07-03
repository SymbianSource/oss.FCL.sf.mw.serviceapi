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
* Description:  CSysInfoInterface class
*
*/


#ifndef __SYSINFOINTERFACE_H__
#define __SYSINFOINTERFACE_H__

const TInt  KMaxErrMsg = 1024;

//INCLUDES
#include <e32def.h>
#include <e32base.h>
#include <liwvariant.h>

#include "sysinfoservice.h"
//FORWARD DECLARATION
class CSysInfoObserver;
class CSysInfoCallbackMap;
/**
* CSysInfoInterface
* This class inherits from MAiwInterface and implements the
* ExecuteCmdL( const TDesC8& aCmdName,
*              const CLiwGenericParamList& aInParamList,
*              CLiwGenericParamList& aOutParamList, TUint aCmdOptions = 0,
*              MLiwNotifyCallback* aCallback = 0) and
* Close() functions. The member functions of this class parses the input parameters,
* constructs proper structures and calls the corresponding service class functions
* based on the input arguments.
*/
// CLASS DECLARATION
NONSHARABLE_CLASS(CSysInfoInterface): public CBase, public MLiwInterface
    {
        enum TIndex
        {
        EIndex0 = 0,        
        EIndex1,
        EIndex2,
        EIndex3
        };	

    public://New Methods

    /**
    * NewL.
    * Two-phased constructor.
    * Create a CSysInfoInterface object.
    * @return A pointer to the created instance of CSysInfoInterface.
    */
    static CSysInfoInterface* NewL();

    public: // from MAiwInterface

    /**
    * The consumer application should call this method to execute a service
    * command directly on the interface. The service provider should
    * provide a concrete implementation for the supported service
    * command aCmdName. The consumer application should fill in the necessary
    * parameters in \em aInParamList.
    */
    void ExecuteCmdL( const TDesC8& aCmdName,
                        const CLiwGenericParamList& aInParamList,
                        CLiwGenericParamList& aOutParamList, 
                        TUint aCmdOptions = 0,
                        MLiwNotifyCallback* aCallback = 0);

    /**
    * The service provider should provide a concrete implementation
    * for this method. The internal state of the service provider
    * implemeting \c MAiwInterface can be reset within this method.
    * The consumer application should call this method if there
    * are no more service commands to be executed on the interface.
    */
    void Close();

    /**
    * Callback
    * This function returns the callback for the corresponding asynchronous 
    * request whose transaction id is passed.
    *
    * @param aTransactionId Transaction id of asynchronous request whose 
    *                       callback is required.
    * @return The callback of the asynchronous request.
    */
    MLiwNotifyCallback* GetCallback( TInt32 aTransactionId );

    /**
    * Callback
    * This function returns the callback for the corresponding asynchronous request whose
    * transaction id is passed and removes the callback entry.
    *
    * @param aTransactionId Transaction id of asynchronous request 
    *                       whose callback is required.
    * @return The callback of the asynchronous request.
    */
    MLiwNotifyCallback* GetCallbackAndRemove( TInt32 aTransactionId );

    /**
    * SapiError
    * This function maps sapi error.
    *
    * @param aSymbianErr symbian error code.
    *
    */       
    TInt SapiError( TInt aSymbianErr );

    /**
    * ConvertSysData2AiwParamL
    * This function converts system data aInSysData to aOutMapParam
    * 
    * @param aInSysData the input parameter sysdata.
    * @param [out] aOutMapParam aiw map representation of sysdata.
    *
    *
    * @see CLiwMap
    * @see CSysData
    *
    */     		
    static void ConvertSysData2AiwParamL(const CSysData* aInSysData,
                                            CLiwMap*& aOutMapParam);

    private:

    /**
    * ConstructL
    * 2nd phase constructor.
    * Perform the second phase construction of CSysInfoInterface object.
    */
    void ConstructL();

    /**
    * C++ default constructor.
    * By default Symbian OS constructor is private.
    */
    CSysInfoInterface();

    /**
    * ~CSysInfoInterface
    * Destructor.
    */
    ~CSysInfoInterface();

    private:// delegator functions

    /**
    * SwitchCmdL
    * This function delegates the control to other functions based on the command.
    *
    * @param aCmdName the name of the service command which the consumer wants to invoke.
    * @param aInParamList the input parameter list.
    * @param [in,out] aOutParamList the output parameter list, can be empty list or may contain the errors.
    * @param aCmdOptions Options for the command, see TAiwServiceCmdOptions in liwcommon.hrh.
    * @param aCallback callback to be registered by consumer application
    *
    *
    *
    * @see TAiwServiceCmdOptions
    * @see CLiwGenericParamList
    * @see MLiwNotifyCallback
    *
    */
    void SwitchCmdL( const TDesC8& aCmdName,
                    const CLiwGenericParamList& aInParamList,
                    CLiwGenericParamList& aOutParamList, 
                    TUint aCmdOptions,
                    MLiwNotifyCallback* aCallback );

    private:
    /**
    * SetInfoL
    * This function modifies a specified system attribute value by calling core class
    * function SetInfoL.
    *
    * @param aInParamList the input parameter list.
    *
    * @see CLiwGenericParamList
    *
    */
    void SetInfoL(const CLiwGenericParamList& aInParamList);

    /**
    * GetInfoL
    * This function reads a specified system attribute by calling GetInfoL core class.
    * funtion.
    * 
    * @param aInParamList the input parameter list.
    * @param [in,out] aOutParamList the output parameter list, is an empty list.
    * @param aCmdOptions Options for the command, see TAiwServiceCmdOptions in liwcommon.hrh.
    * @param aCallback callback to be registered by consumer application
    *
    *
    *
    * @see TAiwServiceCmdOptions
    * @see CLiwGenericParamList
    * @see MLiwNotifyCallback
    *
    */     
    void GetInfoL( const CLiwGenericParamList& aInParamList,
                    CLiwGenericParamList& aOutParamList, 
                    TUint aCmdOptions,
                    MLiwNotifyCallback* aCallback );

    /**
    * GetNotificationL
    * This function registers a callback for notification on specified system attribute by.
    * calling core class function GetNotificationL.
    * 
    * @param aInParamList the input parameter list.
    * @param [in,out] aOutParamList the output parameter list, is an empty list.
    * @param aCmdOptions Options for the command, see TAiwServiceCmdOptions in liwcommon.hrh.
    * @param aCallback callback to be registered by consumer application
    *
    *
    *
    * @see TAiwServiceCmdOptions
    * @see CLiwGenericParamList
    * @see MLiwNotifyCallback
    *
    */     
    void GetNotificationL( const CLiwGenericParamList& aInParamList,
                            CLiwGenericParamList& aOutParamList, 
                            TUint aCmdOptions,
                            MLiwNotifyCallback* aCallback );

    /**
    * ReadInputParamsL
    * This function reads input parameters specified in aInParamList.
    * 
    * @param aInParamList the input parameter list.
    * @param [out] aEntity input param entity.
    * @param [out] aKey input param key.
    * @param [out] aInputData optional data specified.
    *
    *
    * @see CLiwGenericParamList
    * @see CSysData
    *
    */     
    void ReadInputParamsL(const CLiwGenericParamList& aInParamList,
                            TPtrC& aEntity, TPtrC& aKey,
                            CSysData*& aInputData);

    /**
    * Convert2SysDataL
    * This function converts system data specified in aInputParam
    * to aSysData.
    * 
    * @param aInputParam the input parameter.
    * @param [out] aSysData input param sysdata.
    *
    *
    * @see TLiwGenericParam
    * @see CSysData
    *
    */     
    void Convert2SysDataL(const TLiwGenericParam& aInputParam,
                                            CSysData*& aSysData);

    /**
    * Cancel
    * This function cancels a previously requested aynchronous request
    * based on transaction id.
    *
    * @param aInParamList the input parameter list.
    * @param [in,out] aOutParamList the output parameter list, is an empty list.
    * @param aCmdOptions Options for the command, see TAiwServiceCmdOptions in liwcommon.hrh.
    * @param aCallback callback to be registered by consumer application
    *
    *
    *
    * @see TAiwServiceCmdOptions
    * @see CLiwGenericParamList
    * @see MLiwNotifyCallback
    *
    */
    void CancelL( const CLiwGenericParamList& aInParamList,
                    CLiwGenericParamList& aOutParamList, 
                    TUint aCmdOptions,
                    MLiwNotifyCallback* aCallback );

    private:// Data

    /**
    * iService
    * The handle to the CSysInfoService object.
    */
    CSysInfoService* iService;
    /**
    * iObserver
    * ISystemObserver instance.
    */
    CSysInfoObserver* iObserver;

    /**
    * iCallbackMap
    * Array of CSysInfoCallbackMap objects.
    */
    RPointerArray<CSysInfoCallbackMap> iCallbackMap;

    /**
    * Error Message buffer.
    */
    TBuf<KMaxErrMsg>  iErrBuf;
    };

#endif // __SYSINFOINTERFACE_H__