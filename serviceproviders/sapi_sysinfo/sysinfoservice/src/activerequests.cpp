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


#include <centralrepository.h>
#include <btserversdkcrkeys.h>
#include <settingsinternalcrkeys.h>
#include <hwrmvibrasdkcrkeys.h>
#include <hwrmlightdomaincrkeys.h>
#include <AknFepInternalCRKeys.h>
#include <sysutildomaincrkeys.h>

#include <UikonInternalPSKeys.h>
#include <NetworkHandlingDomainPSKeys.h>
#include <hwrmdomainpskeys.h>
#include <hwrmpowerstatesdkpskeys.h>
#include <ir_sock.h>

#include "activerequests.h"
#include "sysinfoservice.h"
#include "entitykeys.h"
#include "sysinfoutils.h"

using namespace SysInfo;
_LIT(KDriveSeperator,":\\");
const TInt KMaxDriveLength = 5;

// --------------------------------------------------------------------
// CCenrepNotifier::CCenrepNotifier()
// C++ default constructor.
// --------------------------------------------------------------------
//
CCenrepNotifier::CCenrepNotifier(TSysRequest::TRequestType aReqType,
                                TInt32 aTransID, TCommand aCommand,
                                ISystemObserver* aObsrver)
                                :CActiveRequest(aReqType,aTransID,aObsrver),	
                                iCommand(aCommand)
    {
    }

// --------------------------------------------------------------------
// CCenrepNotifier::~CCenrepNotifier()
// Destructor.
// --------------------------------------------------------------------
//
CCenrepNotifier::~CCenrepNotifier()
    {
    Cancel();
    delete iCenrep;
    delete iEntity;
    delete iKey;
    }

// --------------------------------------------------------------------
// CCenrepNotifier::NewL()
// Two-phased constructor, returns instance of this class.
// --------------------------------------------------------------------
//
CCenrepNotifier* CCenrepNotifier::NewL(const TSysRequest& aRequest, 
                                                    TCommand aCommand)
    {
    CCenrepNotifier* self;
    self = new (ELeave) CCenrepNotifier(aRequest.RequestType(),
                                        aRequest.TransactionID(),
                                        aCommand,aRequest.Observer());

    CleanupStack::PushL(self);
    self->ConstructL(aRequest);
    CleanupStack::Pop(self);
    return self;
    }

// --------------------------------------------------------------------
// CCenrepNotifier::ConstructL()
// 2nd Phase constructor to allocate required resources for this obj.
// --------------------------------------------------------------------
//
void CCenrepNotifier::ConstructL(const TSysRequest& aRequest)
    {
    //supportes only notifications.
    if(TSysRequest::ENotification != RequestType())
        User::Leave(KErrNotSupported);

    // Identify repository uid and key.
    switch (iCommand)
        {
        case EPridictiveText:
            iRepositoryUid = KCRUidAknFep;
            iRepositoryKey = KAknFepPredTxtFlag;
            break;

        case EInputLanguage:
            iRepositoryUid = KCRUidAknFep;
            iRepositoryKey = KAknFepInputTxtLang;
            break;

        case EBlueTooth:
            iRepositoryUid = KCRUidBluetoothPowerState;
            iRepositoryKey = KBTPowerState;
            break;

        case EVibra:
            iRepositoryUid = KCRUidVibraCtrl;
            iRepositoryKey = KVibraCtrlProfileVibraEnabled;
            break;
    
        case EKeyLock:
            iRepositoryUid = KCRUidSecuritySettings;
            iRepositoryKey = KSettingsAutolockStatus;
            break;

        default: 
            User::Leave(KErrNotFound);
        }

    // create repository instance.
    iCenrep = CRepository::NewL(iRepositoryUid);	
    // Make local copy of SA.
    iEntity = aRequest.Entity().AllocL();
    iKey	= aRequest.Key().AllocL();
    }

// --------------------------------------------------------------------
// CCenrepNotifier::Request()
// Issues notification request.
// --------------------------------------------------------------------
//
TInt CCenrepNotifier::Request ()
    {
    if( !IsActive() )
        {
        iCenrep->NotifyRequest(iRepositoryKey, iStatus);
        SetActive ();
        }
    return KErrNone;
    }

// --------------------------------------------------------------------
// CCenrepNotifier::RunL()
// Gets called in event of request completion or error situation.
// --------------------------------------------------------------------
//
void CCenrepNotifier::RunL()
    {
    TInt Error(iStatus.Int());

    if (KErrNone <= Error)
        {
        // Re-Issue request
        Request ();
        Error = iCenrep->Get(iRepositoryKey,iValue);
        //Create CSysData
        CStatus* Status = CStatus::NewL(iValue);
        // Calling Observer response method.
        TRAP_IGNORE(SystemObserver()->HandleResponseL(*iEntity, *iKey, Status,
                                            TransactionID(),RequestType(),Error));
        }
    else
        {
        TRAP_IGNORE(SystemObserver()->HandleResponseL(*iEntity, *iKey, NULL,
                TransactionID(),RequestType(),Error));

        ActiveStore::RemoveRequest(TransactionID());
        }
    }

// --------------------------------------------------------------------
// CCenrepNotifier::DoCancel()
// Cancel ongoing request.
// --------------------------------------------------------------------
//
void CCenrepNotifier::DoCancel()
    {
    iCenrep->NotifyCancel(iRepositoryKey);
    }

// --------------------------------------------------------------------
// CPubSubNotifier::CPubSubNotifier()
// C++ default constructor.
// --------------------------------------------------------------------
//
CPubSubNotifier::CPubSubNotifier(TSysRequest::TRequestType aReqType, 
                                TInt32 aTransID, TCommand aCommand,
                                ISystemObserver* aObsrver)
                                :CActiveRequest(aReqType,aTransID,aObsrver),	
                                iValue(EUnknown), iCommand(aCommand)
    {
    }

// --------------------------------------------------------------------
// CPubSubNotifier::~CPubSubNotifier()
// Destructor.
// --------------------------------------------------------------------
//
CPubSubNotifier::~CPubSubNotifier()
    {
    Cancel();
    iProperty.Close();
    delete iEntity;
    delete iKey;
    }

// --------------------------------------------------------------------
// CPubSubNotifier::NewL()
// Two-phased constructor, returns instance of this class.
// --------------------------------------------------------------------
//
CPubSubNotifier* CPubSubNotifier::NewL(const TSysRequest& aRequest, 
                                                    TCommand aCommand)
    {
    CPubSubNotifier* self;
    self = new (ELeave) CPubSubNotifier( aRequest.RequestType(),
                                        aRequest.TransactionID(),
                                        aCommand,aRequest.Observer() );

    CleanupStack::PushL(self);
    self->ConstructL (aRequest);
    CleanupStack::Pop(self);
    return self;
    }

// --------------------------------------------------------------------
// CPubSubNotifier::ConstructL()
// 2nd Phase constructor to allocate required resources for this obj.
// --------------------------------------------------------------------
//
void CPubSubNotifier::ConstructL (const TSysRequest& aRequest)
    {
    //supportes only notifications.
    if(TSysRequest::ENotification != RequestType())
        User::Leave(KErrNotSupported);

    // Identify publish subscribe category uid and key based on command.
    switch (iCommand)
        {
        case ERegistrationStatus:
            iPropertyUid = KPSUidNetworkInfo;
            iPropertyKey = KNWRegistrationStatus;
            break;

        case ENetworkMode:
            iPropertyUid = KPSUidNetworkInfo;
            iPropertyKey = KNWTelephonyNetworkMode;
            break;

        case EChargingStatus:
            iPropertyUid = KPSUidHWRMPowerState;
            iPropertyKey = KHWRMChargingStatus;
            break;

        case EFlipStatus:
            iPropertyUid = KPSUidHWRM;
            iPropertyKey = KHWRMFlipStatus;
            break;

        case EGripStatus:
            iPropertyUid = KPSUidHWRM;
            iPropertyKey = KHWRMGripStatus;
            break;

        case EInfraRed:
            iPropertyUid = KIrdaPropertyCategory;
            iPropertyKey = KIrdaStatus;
            break;

        case EMemoryCard:
            iPropertyUid = KPSUidUikon;
            iPropertyKey = KUikMMCInserted;
            break;

        default:
            User::Leave(KErrNotFound);
        }

    User::LeaveIfError (iProperty.Attach(iPropertyUid,iPropertyKey));
    // Make local copy of SA.
    iEntity = aRequest.Entity().AllocL();
    iKey	= aRequest.Key().AllocL();
    }

// --------------------------------------------------------------------
// CPubSubNotifier::Request()
// Issues notification request.
// --------------------------------------------------------------------
//
TInt CPubSubNotifier::Request()
    {
    if( !IsActive() )
        {
        iProperty.Subscribe(iStatus);
        SetActive ();
        }
    return KErrNone;
    }

// --------------------------------------------------------------------
// CPubSubNotifier::RunL()
// Gets called in event of request completion or error situation.
// --------------------------------------------------------------------
//
void CPubSubNotifier::RunL()
    {
    //get error.
    TInt Error(iStatus.Int());
    TInt value = 0;	

    if (KErrNone <= Error)
    {
    // Re-Issue request
    Request();
    // read value.
    iProperty.Get(value);
    switch (iCommand)
        {
        case EChargingStatus:
            // ChargeStatus need to be mapped to one these states Charging,
            // NotCharging and Unknown
            if ( EChargingStatusCharging == value || 
                    EChargingStatusAlmostComplete == value ||
                    EChargingStatusChargingContinued == value )
                value = ECharging;
            
            else if( EChargingStatusNotConnected == value || 
                        EChargingStatusNotCharging == value || 
                        EChargingStatusChargingComplete == value)
                value = ENotCharging;
            
            else
                value = EUnknown;
            break;

        case EInfraRed:
            // IRStatus need to be mapped to one these states 
            // ON, OFF, UNKNOWN.
            if ( TIrdaStatusCodes::EIrLoaded == value || 
                    TIrdaStatusCodes::EIrDiscoveredPeer == value ||
                    TIrdaStatusCodes::EIrBlocked == value || 
                    TIrdaStatusCodes::EIrLostPeer == value || 
                    TIrdaStatusCodes::EIrDisconnected == value )
                value = EOn;
            else if( TIrdaStatusCodes::EIrUnloaded == value )
                value = EOff;
            else
                value = EUnknown;
            break;

        case EFlipStatus:
        case EGripStatus:
            if (value == EPSHWRMFlipOpen)
                value = EOpen;
            else if (value == EPSHWRMFlipClosed)
                value = EClosed;
            else
                value = EUnknown;
            break;
        
        case ERegistrationStatus:
        case ENetworkMode :	
        case EMemoryCard:
            break;
        
        default:
            Error= KErrGeneral;
        }
    
    if((value != iValue))
        {
        iValue = value;
        //Create output CSysData
        CStatus* Status = CStatus::NewL(iValue);
        //Calling Observer Handle.
        TRAP_IGNORE(SystemObserver()->HandleResponseL(*iEntity, *iKey, Status,
                                        TransactionID(),RequestType(),Error));
        }    
    }
    else
    {
    TRAP_IGNORE(SystemObserver()->HandleResponseL(*iEntity, *iKey, NULL,
            TransactionID(),RequestType(),Error));

    ActiveStore::RemoveRequest(TransactionID());
    }

    }

// --------------------------------------------------------------------
// CPubSubNotifier::DoCancel()
// Cancel ongoing request.
// --------------------------------------------------------------------
//
void CPubSubNotifier::DoCancel()
    {
    iProperty.Cancel();
    }

// --------------------------------------------------------------------
// CCriticalMemNotifier::CCriticalMemNotifier()
// C++ default constructor.
// --------------------------------------------------------------------
//
CCriticalMemNotifier::CCriticalMemNotifier(TSysRequest::TRequestType aReqType, 
                                TInt32 aTransID,ISystemObserver* aObsrver)
                                :CActiveRequest(aReqType,aTransID,aObsrver)
    {
    }

// --------------------------------------------------------------------
// CCriticalMemNotifier::~CCriticalMemNotifier()
// Destructor.
// --------------------------------------------------------------------
//
CCriticalMemNotifier::~CCriticalMemNotifier()
    {
    Cancel();
    iFs.Close();
    }

// --------------------------------------------------------------------
// CCriticalMemNotifier::NewL()
// Two-phased constructor, returns instance of this class.
// --------------------------------------------------------------------
//
CCriticalMemNotifier* CCriticalMemNotifier::NewL(const TSysRequest& aRequest)
    {
    CCriticalMemNotifier* self;
    self = new (ELeave) CCriticalMemNotifier(aRequest.RequestType(),
                        aRequest.TransactionID(),aRequest.Observer());

    CleanupStack::PushL(self);
    self->ConstructL (aRequest);
    CleanupStack::Pop(self);

    return self;
    }

// --------------------------------------------------------------------
// CCriticalMemNotifier::ConstructL()
// 2nd Phase constructor to allocate required resources for this obj.
// --------------------------------------------------------------------
//
void CCriticalMemNotifier::ConstructL(const TSysRequest& aRequest)
    {
    //supportes only notifications.
    if(TSysRequest::ENotification != RequestType())
        User::Leave(KErrNotSupported);

    CDriveInfo* DrvInfo=NULL;
    //Input validation.
    if( aRequest.SystemData() && 
            CSysData::EDriveInfo == aRequest.SystemData()->DataType() )
        DrvInfo = (CDriveInfo*)aRequest.SystemData();
    else
        User::Leave(KErrArgument);

    iDrvNumber = DrvInfo->DriveNumber();
    iCriticalFreeMemory = DrvInfo->CriticalSpace();

    CleanupClosePushL(iFs);
    User::LeaveIfError(iFs.Connect());

    // If Critical Memory not specified assume system defaults.
    if( -1 == iCriticalFreeMemory )
        {
        TVolumeInfo VolumeInfo;
        User::LeaveIfError(iFs.Volume(VolumeInfo,iDrvNumber));
        if(EMediaRam == VolumeInfo.iDrive.iType)
            RepositoryUtil::GetRepositoryKeyL(KCRUidDiskLevel,
                                KRamDiskCriticalLevel, iCriticalFreeMemory);
        else
            RepositoryUtil::GetRepositoryKeyL(KCRUidDiskLevel,
                                KDiskCriticalThreshold, iCriticalFreeMemory);
        }
    CleanupStack::Pop(&iFs);
    }

// --------------------------------------------------------------------
// CCriticalMemNotifier::Request()
// Issues notification request.
// --------------------------------------------------------------------
//
TInt CCriticalMemNotifier::Request ()
    {
    if( !IsActive() )
        {
        iFs.NotifyDiskSpace(iCriticalFreeMemory,iDrvNumber,iStatus);
        SetActive();
        }
    return KErrNone;
    }

// --------------------------------------------------------------------
// CCriticalMemNotifier::RunL()
// Gets called in event of request completion or error situation.
// --------------------------------------------------------------------
//
void CCriticalMemNotifier::RunL()
    {
    TInt error(iStatus.Int());

    if(KErrNone <= error)
        {
        //Re-Issue request.
        Request();
    
        //Specify the Drive number in output CSysData.
        TBuf<KMaxDriveLength> drv;
        drv.FillZ();
        drv.Append('A'+iDrvNumber);
        drv.Append(KDriveSeperator);
        CStringData* drive = CStringData::NewL(drv);
    
        TVolumeInfo VolumeInfo;
        iFs.Volume(VolumeInfo,iDrvNumber);
    
        //Call Observer handle.
        if(VolumeInfo.iFree <= iCriticalFreeMemory)
        	TRAP_IGNORE(SystemObserver()->HandleResponseL(KMemory, KCriticalMemory,
                                        drive,TransactionID(),RequestType(),error));
        }
    else
        {
        TRAP_IGNORE(SystemObserver()->HandleResponseL(KMemory, KCriticalMemory,
                                    NULL,TransactionID(),RequestType(),error));
        ActiveStore::RemoveRequest(TransactionID());
        }

    }

// --------------------------------------------------------------------
// CPubSubNotifier::DoCancel()
// Cancel ongoing request.
// --------------------------------------------------------------------
//
void CCriticalMemNotifier::DoCancel()
    {
    iFs.NotifyDiskSpaceCancel(iStatus);
    }

// End of file
