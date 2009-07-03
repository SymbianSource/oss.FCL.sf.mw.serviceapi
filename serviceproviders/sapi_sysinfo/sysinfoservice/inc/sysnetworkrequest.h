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
* Description:  describes system information notifiers.
*
*/


#ifndef __SYSNETWORKREQUEST_H__
#define __SYSNETWORKREQUEST_H__

//INCLUDES
#include "activerequests.h"

// FORWORD CLASS DECLARATION
class RTelServer;
class RMobilePhone;


/**
*  @ref CNetwork active object class to handle asynchronous network
*   information requests.
*
*  @lib   sysinfoservice.lib
*  @since 3.2
*/
NONSHARABLE_CLASS(CNetwork): public CActiveRequest
    {
    public:
    // Enumeration of supported network request types.
    typedef enum { 
        ESignalStrength,
        EHomeNetworkInfo, 
        ECurrentNetworkInfo,
        ELocationAreaCode,
        ECellId,
        EBatteryStrength 
        }TNetInfoType;

    public:	// Constructors and destructor
    /**
    * Two-phased constructor.
    *
    * @return A new instance of this class.
    */    
    static CNetwork* NewL( const TSysRequest& aRequest,TInt aNetworkInfoType );
    /**
    * Destructor.
    */
    ~CNetwork();

    private:
    /**
    * C++ default constructor.
    */
    CNetwork( TSysRequest::TRequestType aReqType, TInt32 aTransID,
                    TInt aNetworkInfoType, ISystemObserver* aObsrver);

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL( const TSysRequest& aRequest );

    public:	
    /**
    * Issues network request.
    */
    TInt Request();

    protected: // from CActive
    
    void RunL();

    void DoCancel();

    private:	// DATA
    //	Local copy of Entity.
    HBufC* 	        iEntity;

    //	Local copy of Key.
    HBufC* 	        iKey;

    // Session to the telephony server @ref RTelServer.
    RTelServer      iTelServer;

    //RMobilePhone handle.	
    RMobilePhone    iMobilePhone;

    //Network Request type.
    TNetInfoType    iNetworkInfoType;

    //Signal strength.
    TInt32          iSignalStrength;

    //Signal strength/Battery Threshold.
    TInt            iThreshold;

    //Network Information.
    RMobilePhone::TMobilePhoneNetworkInfoV1 iNetworkInfo;

    //packaged Network Information.
    RMobilePhone::TMobilePhoneNetworkInfoV1Pckg iNetworkInfoBuf;

    //mobile phone location area Information.
    RMobilePhone::TMobilePhoneLocationAreaV1    iArea;

    //LAC
    TUint           iLocationAreaCodeOld;

    //Cell ID
    TUint           iCellIdOld;

    //Battery Information.
    RMobilePhone::TMobilePhoneBatteryInfoV1     iBatteryInfo;

    //signal strength in scale of 0-7.
    TInt8           iBar;

    //Flag for Threshold.
    TBool           iIsThresholdSet;
    };


// CLASS DECLARATION
#endif __SYSNETWORKREQUEST_H__