/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  class implementation
*
*/

#include <hal.h>
#include <SysUtil.h>

#include "sysinfoservice.h"
#include "SysInfoUtils.h"
#include "entitykeys.h"
#include "deviceinfo.h"

_LIT(KROMInstallDir,"\\system\\install\\");
_LIT(KS60ProductIdFile,"Series60v*.sis");
_LIT(KProductIdentifier,"RM");
_LIT(KProductUnknown,"Unknown");

const TInt KPositionNine = 9;

// --------------------------------------------------------------------
// CDeviceInfo::CDeviceInfo()
// C++ default constructor.
// --------------------------------------------------------------------
//
CDeviceInfo::CDeviceInfo():
            iPlatformMajorVersion(0),
            iPlatformMinorVersion(0),
            iOSMajorVersion(0),
            iOSMinorVersion(0)
    {
    }

// --------------------------------------------------------------------
// CDeviceInfo::~CDeviceInfo()
// Destructor.
// --------------------------------------------------------------------
//
CDeviceInfo::~CDeviceInfo()
    {
    delete iProductType;
    }
	
// --------------------------------------------------------------------
// CDeviceInfo::NewL()
// Two-phased constructor, returns instance of this class.
// --------------------------------------------------------------------
//
CDeviceInfo* CDeviceInfo::NewL()
    {
    CDeviceInfo* self;
    self = new (ELeave) CDeviceInfo();

    CleanupStack::PushL(self);
    self->ConstructL ();
    CleanupStack::Pop(self);

    return self;
    }
	
// --------------------------------------------------------------------
// CDeviceInfo::NewL()
// 2nd Phase constructor to allocate required resources for this obj.
// --------------------------------------------------------------------
//
void CDeviceInfo::ConstructL ()
    {
    GetDeviceInfoL();
    }

// --------------------------------------------------------------------
// CDeviceInfo::GetDeviceInfoL()
// This function reads device information initializes member varialbes.
// --------------------------------------------------------------------
//
void CDeviceInfo::GetDeviceInfoL()
    {
    //get firmware version			
    User::LeaveIfError(SysUtil::GetSWVersion(iFirmwareVersion));

    //get platform version			
    RFs fs;
    CDir* result;

    CleanupClosePushL(fs);
    User::LeaveIfError(fs.Connect());

    TFindFile ff(fs);
    TInt err(KErrNone);
    err = ff.FindWildByDir(KS60ProductIdFile,KROMInstallDir,result);
    if(!err)
        {
        CleanupStack::PushL(result);
        User::LeaveIfError(result->Sort(ESortByName|EDescending));

        if(result->Count() >= 0)
            {
            TPtrC filename = (*result)[0].iName;
            TLex parser((filename));
            parser.Inc(KPositionNine);

            // Get major version value
            err = parser.Val(iPlatformMajorVersion);

            if( parser.Get() != '.' || err )
                {
                iPlatformMajorVersion = 0;
                }
            else
                {
                // Get minor version value
                err = parser.Val(iPlatformMinorVersion);
                if( err )
                    {
                    iPlatformMajorVersion = 0;
                    iPlatformMinorVersion = 0;
                    }
                }
            }
        // clean up result
        CleanupStack::PopAndDestroy(result);
        }
    // clean up file session fs.
    CleanupStack::PopAndDestroy(&fs);	
    	
    //get machine id and symbian OS version			
    HAL::Get(HALData::EMachineUid, iMachineId);

    //get product type
    ProcessProductTypeL();

    // Session to the telephony server.
    RTelServer telserver;
    //RMobilePhone handle.	
    RMobilePhone 	mobilephone;

    CleanupClosePushL(telserver);
    CleanupClosePushL(mobilephone);

    User::LeaveIfError(RPhoneInstance::Connect( telserver,mobilephone ));

    //get phone manufacturer,model,IMEI		
    TRequestStatus Status = KRequestPending;
    mobilephone.GetPhoneId(Status,iPhoneIdentity);
    User::WaitForRequest(Status);

    //Close Phone handle.
    CleanupStack::PopAndDestroy(2,&telserver);
    }

// --------------------------------------------------------------------
// CDeviceInfo::ProcessProductType()
// This function does lexical processing on Firmware version to read
// product type.
// --------------------------------------------------------------------
//
void CDeviceInfo::ProcessProductTypeL()
    {
    TBuf<KSysUtilVersionTextLength> versionString(KNullDesC);
    TPtrC ProductType(KNullDesC);
    const TChar KNewLine('\n');

    versionString.Copy(iFirmwareVersion);

    TInt offset = versionString.FindF(KProductIdentifier);
    if( KErrNotFound != offset)
        {
        TPtr productinfo = versionString.MidTPtr(offset);
        //search new line charecter.
        offset = productinfo.LocateF(KNewLine);
        if( KErrNotFound != offset )
            {
            ProductType.Set(productinfo.Left(offset));
            }
        }

    iProductType = ProductType.AllocL();	
    }

// --------------------------------------------------------------------
// CDeviceInfo::ProductType()
// returns product type.
// --------------------------------------------------------------------
//
TPtrC CDeviceInfo::ProductType() const
    {
    if( iProductType->Des() == KNullDesC )
        return TPtrC(KProductUnknown);
    else
        return TPtrC(*iProductType);
    }

// --------------------------------------------------------------------
// CDeviceInfo::FirmwareVersion()
// returns firmware version.
// --------------------------------------------------------------------
//
TPtrC CDeviceInfo::FirmwareVersion() const
    {
    return TPtrC(iFirmwareVersion);
    }

// --------------------------------------------------------------------
// CDeviceInfo::Manufaturer()
// returns Manufacture name.
// --------------------------------------------------------------------
//
TPtrC CDeviceInfo::Manufaturer() const
{
	return TPtrC(iPhoneIdentity.iManufacturer);
}

// --------------------------------------------------------------------
// CDeviceInfo::Model()
// returns Phone Model.
// --------------------------------------------------------------------
//
TPtrC CDeviceInfo::Model() const
    {
    return TPtrC(iPhoneIdentity.iModel);
    }

// --------------------------------------------------------------------
// CDeviceInfo::IMEI()
// returns Serial number.
// --------------------------------------------------------------------
//
TPtrC CDeviceInfo::IMEI() const
    {
    return TPtrC(iPhoneIdentity.iSerialNumber);
    }

// --------------------------------------------------------------------
// CDeviceInfo::MachineId()
// returns Machine ID.
// --------------------------------------------------------------------
//
TInt CDeviceInfo::MachineId() const
    {
    return iMachineId;
    }

// --------------------------------------------------------------------
// CDeviceInfo::GetPlatformVersion()
// returns PLATFORM VERSION NUMBER.
// --------------------------------------------------------------------
//
void CDeviceInfo::GetPlatformVersion(TInt& aMajor,TInt& aMinor)
    {
    aMajor = iPlatformMajorVersion;
    aMinor = iPlatformMinorVersion;
    }

// --------------------------------------------------------------------
// CDeviceInfo::GetOSVersion()
// returns OS VERSION NUMBER.
// --------------------------------------------------------------------
//
void CDeviceInfo::GetOSVersion(TInt& aMajor,TInt& aMinor)
    {
    aMajor = iOSMajorVersion;
    aMinor = iOSMinorVersion;
    }

//End of file.
