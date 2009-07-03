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


#ifndef __DEVICEINFO_H__
#define __DEVICEINFO_H__
//INCLUDES
#include <sysutil.h>

// CONSTANT DECLARATIONS
const TInt KProductTypeTextLength =  64;

// FORWARD DECLARATIONS
/**
*  @ref CDeviceInfo class used to read static system properties.
*
*  @lib sysinfoservice.lib
*  @since S60 3.2
*/
NONSHARABLE_CLASS(CDeviceInfo):public CBase
    {
    public:	// Constructors and destructor
        /**
        * Two-phased constructor.
        *
        * @return A new instance of this class.
        */    
        static CDeviceInfo* NewL();
        
        /**
        * Destructor.
        */
        ~CDeviceInfo();

    private:
        /**
        * C++ default constructor.
        */
        CDeviceInfo();

        /**
        * By default Symbian 2nd phase constructor is private.
        */
        void ConstructL();

    private:	
        /**
        *   This function reads device information initializes member varialbes.
        */
        void GetDeviceInfoL();
        /**
        *   This function does lexical processing on Firmware version to read
        *   product type.
        */
        void ProcessProductTypeL();
        
    public:	
        /**
        *   @return Firmware version.
        */
        TPtrC FirmwareVersion() const;
        /**
        *   @return Manufacturer name.
        */
        TPtrC Manufaturer() const;
        /**
        *   @return Phone model name.
        */
        TPtrC Model() const;
        /**
        *   @return Serial number of phone.
        */
        TPtrC IMEI() const;
        /**
        *   @return product type.
        */
        TPtrC ProductType() const;
        /**
        *   @return Unique Machine ID.
        */
        TInt MachineId() const;
        /**
        *   On return   @p aMajor contains major platform version number.
        *               @p aMinor contains minor platform version number.
        */
        void GetPlatformVersion(TInt& aMajor,TInt& aMinor);
        /**
        *   On return   @p aMajor contains major Symbian OS version number.
        *               @p aMinor contains minor Symbian OS version number.
        */
        void GetOSVersion(TInt& aMajor,TInt& aMinor);

    private:	// DATA
 
        //Platform version.
        TInt        iPlatformMajorVersion;
        TInt        iPlatformMinorVersion;

        //OS version
        TInt        iOSMajorVersion;
        TInt        iOSMinorVersion;

        //Firmware version.
        TBuf<KSysUtilVersionTextLength> iFirmwareVersion;

        //Serial number, Model and Manufacturer.
        RMobilePhone::TMobilePhoneIdentityV1    iPhoneIdentity;
    		
        //Product Type.
        HBufC*	    iProductType;
        //Unique Machine ID.
        TInt        iMachineId;
    };

#endif __DEVICE_INFO_H__