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
* Description:  CSysInfoService class
*
*/


#ifndef __CSYSINFOSERVICE_H__
#define __CSYSINFOSERVICE_H__

//  INCLUDES
#include "sysinfo.h"
#include "sysrequest.h"

// FORWORD CLASS DECLARATION
class CSysData;
class CDeviceInfo;

/**
*   @ref ISystemObserver
*   Client Observer interface to handle response from Asynchronous system requests.
*
*   @param aResponse
*/

class ISystemObserver
    {
    public:
    /**
    * HandleResponseL ()
    * Callback function to be implimented by client in order to handle asynchronous
    * response.
    * @param aEntity        Entity
    * 
    * @param aKey           Key
    *
    * @param aOutput        client owns output data.
    *
    * @param aTransID       TransactionID associated with request.
    *
    * @param aType          Asynchronous Response type.
    *
    * @param aError         If any error occured in process of generating response.
    *
    */		
    virtual void HandleResponseL(const TDesC& aEntity,const TDesC& aKey, 
                                CSysData* aOutput, TInt32 aTransID, 
                                TSysRequest::TRequestType aType,
                                TInt aError=KErrNone) = 0;
    };


/**
*   @ref CSysInfoService is used to read and modify and system information
*
*   @lib sysinfoservice
*   @since S60 3.2
*   @version $Revision: 1.0 $
*/

NONSHARABLE_CLASS(CSysInfoService) : public CBase
    {
    public:  // Constructors and destructor

    /**
    * NewL()
    * Two-phased constructor.
    * Create a CSysInfoService object.
    * @return A pointer to the created instance of CSysInfoService.
    */
    IMPORT_C static CSysInfoService* NewL();

    /**
    * Destructor.
    */
    ~CSysInfoService();

    private:

    /**
    * C++ default constructor.
    */
    CSysInfoService();

    public:	

    /**
    * GetInfoL ()
    * Retrieves specified SA value synchronously.
    * User will provide SA and any input by aRequest argument.
    *
    * @param aEntity    Entity of an system attribute.
    *
    * @param aKey       Key of an system attribute.
    *
    * @param aOutput    Retrived system attribute value.
    *
    * @param aInput     Optional input data.
    *
    * @error @p KErrArgument    if specified input SystemData is not associated with 
    *                           system attribute.
    * @error @p KErrNotFound
    *                       if specified system attribute not found.
    *                       if Specified SA doesn't support this kind of operation
    *                       i.e request type. 
    */

    IMPORT_C void GetInfoL( const TDesC& aEntity, const TDesC& aKey, 
                            CSysData*& aOutput, const CSysData* aInput=NULL );

    /**
    * GetInfoL ()
    * Retrieves specified SA value asynchronously.
    * User will provide SA and any input thru aRequest argument.
    *
    * @param aEntity        Entity of an system attribute.
    *
    * @param aKey           Key of an system attribute.
    *
    * @param aTransID       TransactionID for async operation.
    *
    * @param aCallback      Observer for handling async response.
    *
    * @param aInput         Optional input data.
    *
    * @error @p KErrArgument 	
    *                       if specified input SystemData is not associated with 
    *                       system attribute.
    * @error @p KErrNotFound
    *                   if specified system attribute not found.
    *                   if Specified SA doesn't support this kind of operation
    *                   i.e request type. 
    * @error @p KErrAlreadyExists	
    *                       if Transaction ID specified already exists.
    */

    IMPORT_C void GetInfoL( const TDesC& aEntity, const TDesC& aKey, 
                            TInt32 aTransID, ISystemObserver* aCallback, 
                            const CSysData* aInput=NULL );

    /**
    * GetNotificationL ()
    * Registers for notifications for a given SA.
    * User will provide SA and any input thru aRequest argument.
    *
    * @param aEntity        Entity of an system attribute.
    *
    * @param aKey           Key of an system attribute.
    *
    * @param aTransID       TransactionID for async operation.
    *
    * @param aCallback      Observer for handling async response.
    * 
    * @param aInput         Optional input data.
    *
    * @error @p KErrArgument 	
    *                       if specified input SystemData is not associated with 
    *                       system attribute.
    * @error @p KErrNotFound
    *                       if specified system attribute not found.
    *                       if Specified SA doesn't support this kind of operation
    *                       i.e request type. 
    * @error @p KErrAlreadyExists	
    *                       if Transaction ID specified already exists.
    */

    IMPORT_C void GetNotificationL( const TDesC& aEntity, const TDesC& aKey, 
                                TInt32 aTransID, ISystemObserver* aCallback, 
                                const CSysData* aInput=NULL  );
    /**
    * SetInfoL()
    * Modifies system attribute value.
    * This API can be used to change system attribute value 
    * synchronously/asynchronously, based on attribute specification.
    *
    * @param aEntity        Entity of an system attribute.
    *
    * @param aKey           Key of an system attribute.
    *
    * @param aInput         Input data.
    *
    * @error @p KErrArgument
    *                       if specified input SystemData is not associated with 
    *                       system attribute.
    * @error @p KErrNotFound
    *               if specified system attribute not found.
    *               if Specified SA doesn't support this kind of operation
    *               i.e request type. 
    * @error @p KErrAlreadyExists
    *               if Transaction ID specified already exists for async requests.
    */

    IMPORT_C void SetInfoL( const TDesC& aEntity, const TDesC& aKey, 
                                                const CSysData* aInput );

    /**
    * Cancel()
    * Cancels any outstanding requests and releases resources owned by them.
    *
    */

    IMPORT_C void Cancel(TInt32 aTransID);

    private:
    /*
    *   Modifies General Entity attribute value.
    */
    void SetGeneralInfoL(const TDesC& aKey, const CSysData* aInput);

    /*
    *	Modifies General Entity attribute value.
    */
    void SetDisplayInfoL(const TDesC& aKey, const CSysData* aInput);

    /*
    *	Modifies Connectivity Entity attribute value.
    */
    void SetConnectivityInfoL(const TDesC& aKey, const CSysData* aInput);

    /*
    *	Retrieves Network Entity attribute value.
    */
    void GetNetworkInfoL(TPtrC aKey,CSysData*& aSysData);

    /*
    *	Retrieves Battery Entity attribute value.
    */
    void GetBatteryInfoL(TPtrC aKey,CSysData*& aSysData);

    /*
    *	Retrieves General Entity attribute value.
    */
    void GetGeneralInfoL(TPtrC aKey,CSysData*& aSysData);

    /*
    *	Retrieves Display Entity attribute value.
    */
    void GetDisplayInfoL(TPtrC aKey,CSysData*& aSysData);

    /*
    *	Retrieves available/supported usb modes.
    */
    void GetAvailableUsbModesL(CSysData*& aSysData);

    /*
    *	Retrieves Connectivity Entity attribute value.
    */
    void GetConnectivittyInfoL(TPtrC aKey,CSysData*& aSysData);

    /*
    *	Retrieves Memory Entity attribute value.
    */
    void GetMemoryInfoL(const TDesC& aKey, const CSysData* aInput,
                                                CSysData*& aOutput);

    /*
    *	Retrieves Feature Entity attribute value.
    */
    void GetFeatureInfoL(TPtrC aKey,CSysData*& aSysData);
    /*
    *	Retrieves Device Entity attribute values.
    */
    void GetDeviceInfoL(TPtrC aKey,CSysData*& aSysData);

    private: //DATA

    /**
    * status member to identify feature manager initialization state.
    */       
    TBool           iFeatureManagerInitialized;

    /**
    * class to read static device properties.
    */       
    CDeviceInfo*    iDeviceInfo;
    };


#endif __CSYSINFOSERVICE_H__

