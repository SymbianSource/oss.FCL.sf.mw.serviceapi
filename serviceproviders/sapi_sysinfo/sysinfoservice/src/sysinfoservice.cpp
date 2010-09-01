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
* Description:  CSysInfoService class implementation
*
*/


#include <w32std.h>
#include <hal.h>
#include <featmgr.h>
#include <bldvariant.hrh>
#include <PtiEngine.h>
#include <driveinfo.h>


#include <centralrepository.h>
#include <hwrmvibrasdkcrkeys.h>
#include <settingsinternalcrkeys.h>
#include <hwrmlightdomaincrkeys.h>
#include <AknFepInternalCRKeys.h>
#include <ir_sock.h>
#include <btserversdkcrkeys.h>
#include <sysutildomaincrkeys.h>

#include <e32property.h>
#include <hwrmdomainpskeys.h>
#include <NetworkHandlingDomainPSKeys.h>
#include <hwrmpowerstatesdkpskeys.h>
#include <wlaninternalpskeys.h>
#include <UikonInternalPSKeys.h>
#include <btengsettings.h>

#include <usbman.h>
#include <AknsWallpaperUtils.h>
#include <AknUtils.h>

#include "sysinfoservice.h"
#include "sysinfo.h"
#include "sysinfoutils.h"
#include "entitykeys.h"
#include "activerequests.h"
#include "deviceinfo.h"
#include "sysrange.h"

#include <string.h>

using namespace SysInfo;

// CONSTANT DECLARATIONS
const TInt KGranularity(2);
const TInt KPhoneWlanMacAddressLength = 50;
const TChar KPhoneWlanSeparator (':');
const TUint KPrimaryCameraDisplayID = 2;
_LIT(KWLanMACDataFormat, "%02x");
const TInt KPhoneLanguageLength = 20;
const TInt KMimeTypeLength = 20;

// --------------------------------------------------------------------
// CSysInfoService::CSysInfoService()
// C++ default constructor.
// --------------------------------------------------------------------
//
EXPORT_C CSysInfoService::CSysInfoService():iFeatureManagerInitialized(EFalse)
    {
    }

// --------------------------------------------------------------------
// CSysInfoService::~CSysInfoService()
// Destructor.
// --------------------------------------------------------------------
//
CSysInfoService::~CSysInfoService()
    {
    //If initialized uninitialize.
    if(iFeatureManagerInitialized)
        FeatureManager::UnInitializeLib();

    delete iDeviceInfo;

    // Cancel any ongoing asynchronous requests and 
    // Deallocate resources.
    ActiveStore::ReleaseResources();
    }

// --------------------------------------------------------------------
// CSysInfoService::NewL()
// Two-phased constructor.
// --------------------------------------------------------------------
//
EXPORT_C CSysInfoService* CSysInfoService::NewL ()
    {
    CSysInfoService* self = new (ELeave) CSysInfoService();
    return self;
    }

// --------------------------------------------------------------------
// CSysInfoService::SetInfoL()
// Modifies the system attribute value specified in aRequest.
// --------------------------------------------------------------------
//
EXPORT_C void CSysInfoService::SetInfoL( const TDesC& aEntity, 
                            const TDesC& aKey, const CSysData* aInput )
    {
    if(!aInput)
        User::Leave(KErrArgument);

    if( !aEntity.CompareF(KGeneral) )
        SetGeneralInfoL(aKey,aInput);
    else if( !aEntity.CompareF(KDisplay) )
        SetDisplayInfoL(aKey,aInput);
// Bluetooth and IR which require WriteDeviceData are not usergratable permissions, 
// hence this funtionality is not exposed currently.    
#ifdef _REQUIRE_WRITEDEVICEDATA_
    else if( !aEntity.CompareF(KConnectivity) )
      SetConnectivityInfoL(aKey,aInput);
#endif
    else
        User::Leave(KErrNotFound);
    }

// --------------------------------------------------------------------
// CSysInfoService::Cancel()
// Cancels any outstanding requests and releases resources owned by them.
// --------------------------------------------------------------------
//
EXPORT_C void CSysInfoService::Cancel(TInt32 aTransID)
    {
    ActiveStore::RemoveRequest(aTransID);
    }

// --------------------------------------------------------------------
// CSysInfoService::SetConnectivityInfoL()
// Modifies the Connectivity Entity key values.
// --------------------------------------------------------------------
//
void CSysInfoService::SetConnectivityInfoL(const TDesC& aKey, 
                                            const CSysData* aInput)
    {
    //In Connectivity bluetooth, Infrared takes input argument of type EStatus.
    if( CSysData::EStatus != aInput->DataType() )
        User::Leave(KErrArgument);

    TInt inputStatus = ((CStatus*)aInput)->Status();

    if( !aKey.CompareF(KBlueTooth) )
        {
        CBTEngSettings* BtSettings = CBTEngSettings::NewLC();
        if( inputStatus == EOn)
            User::LeaveIfError(BtSettings->SetPowerState( EBTPowerOn ));
        else if(inputStatus == EOff)
            User::LeaveIfError(BtSettings->SetPowerState( EBTPowerOff ));
        else
            User::Leave(KErrArgument);
        CleanupStack::PopAndDestroy(BtSettings);
        }

    else if( !aKey.CompareF(KInfraRed) )
        {
        if(inputStatus == EOn)
            User::LeaveIfError(RProperty::Set(KIrdaPropertyCategory,
                                KIrdaStatus,TIrdaStatusCodes::EIrLoaded));
        else if(inputStatus == EOff)
            User::LeaveIfError(RProperty::Set(KIrdaPropertyCategory,
                                KIrdaStatus,TIrdaStatusCodes::EIrUnloaded));
        else
            User::Leave(KErrArgument);
        }
    else
        User::Leave(KErrNotFound);
    }

// --------------------------------------------------------------------
// CSysInfoService::SetGeneralInfoL()
// Modifies the General Entity key values.
// --------------------------------------------------------------------
//
void CSysInfoService::SetGeneralInfoL(const TDesC& aKey, const CSysData* aInput)
    {
    // for all General Entity keys input must be of type EStatus.
    if( aInput->DataType() != CSysData::EStatus )
        User::Leave(KErrArgument);

    TInt inStatus = ((CStatus*)aInput)->Status();

    if( !aKey.CompareF(KInputLanguage) )
        {
        CPtiEngine* PtiEngine;
        PtiEngine = CPtiEngine::NewL();
        CleanupStack::PushL(PtiEngine);
        User::LeaveIfError(PtiEngine->ActivateLanguageL(inStatus));
        CleanupStack::PopAndDestroy(PtiEngine);
        RepositoryUtil::SetRepositoryKeyL(KCRUidAknFep,
                                        KAknFepInputTxtLang,inStatus);
        }
    else if( !aKey.CompareF(KPridictiveText) )
        {
        if( EEnabled == inStatus || EDisabled == inStatus )
            RepositoryUtil::SetRepositoryKeyL(KCRUidAknFep,
                                            KAknFepPredTxtFlag,inStatus);
        else
            User::Leave(KErrArgument);
        }
    else if( !aKey.CompareF(KVibraActive) )
        {
        if( EEnabled == inStatus || EDisabled == inStatus )
            RepositoryUtil::SetRepositoryKeyL(KCRUidVibraCtrl,
                                    KVibraCtrlProfileVibraEnabled,inStatus);
        else
            User::Leave(KErrArgument);
        }
    else
        User::Leave(KErrNotFound);
    }

// --------------------------------------------------------------------
// CSysInfoService::SetDisplayInfoL()
// Modifies the Display Entity key values.
// --------------------------------------------------------------------
//
void CSysInfoService::SetDisplayInfoL(const TDesC& aKey, const CSysData* aInput)
    {
    // Input validation.
    // For wallpaper input type must be EStingData and 
    // for others keys input type must be EStatus.
    if( !aKey.CompareF(KWallpaper) )
        {
        if(aInput->DataType() != CSysData::EStringData)
            User::Leave(KErrArgument);
        }
    else if( aInput->DataType() != CSysData::EStatus )
        User::Leave(KErrArgument);

    TInt 	inputStatus = 0;
    TPtrC 	inputString;
    //Read Input data into InputStatus, InputString.
    if( !aKey.CompareF(KWallpaper) )
        {
        ((CStringData*)aInput)->StringData(inputString);
        }
    else
        {
        inputStatus = ((CStatus*)aInput)->Status();
        inputStatus = inputStatus;
        }

    //go thru Display entity keys.
    // Display Entity keys requiring WriteDeviceData are commented currently as these are not
    // usergrantable permissions.
#ifdef _REQUIRE_WRITEDEVICEDATA_
    if( !aKey.CompareF(KBrightness) )
        {
        if ( KBrightnessMax < inputStatus || KBrightnessMin > inputStatus )
            User::Leave(KErrArgument);

        RepositoryUtil::SetRepositoryKeyL(KCRUidLightSettings,
                                            KLightIntensity,inputStatus);
        }
    else if( !aKey.CompareF(KScreenSaverTimeOut) )
        {
        if ( KScreenSaverTimeoutMax < inputStatus || 
                KScreenSaverTimeoutMin > inputStatus )
            User::Leave(KErrArgument);

        RepositoryUtil::SetRepositoryKeyL(KCRUidPersonalizationSettings,
                                    KSettingsScreenSaverPeriod,inputStatus);
        }
    else if( !aKey.CompareF(KAutoLockTime) )
        {
        if ( KAutoLockTimeoutMax < inputStatus || 
                KAutoLockTimeoutMin > inputStatus )
            User::Leave(KErrArgument);

        RepositoryUtil::SetRepositoryKeyL(KCRUidSecuritySettings,
                                    KSettingsAutoLockTime,inputStatus);
        }
    else if( !aKey.CompareF(KKeyGaurdTime) )
        {
        if ( KKeyGaurdTimeoutMax < inputStatus || 
                KKeyGaurdTimeoutMin > inputStatus )
            User::Leave(KErrArgument);

        RepositoryUtil::SetRepositoryKeyL(KCRUidSecuritySettings,
                                    KSettingsAutomaticKeyguardTime,inputStatus);
        }
    else if( !aKey.CompareF(KLightTimeOut) )
        {
        if ( KLightTimeoutMax < inputStatus || 
                    KLightTimeoutMin > inputStatus )
            User::Leave(KErrArgument);

        RepositoryUtil::SetRepositoryKeyL(KCRUidLightSettings,
                                    KDisplayLightsTimeout,inputStatus);
        }
#endif
    if( !aKey.CompareF(KWallpaper) )
        {
        User::LeaveIfError(
                AknsWallpaperUtils::SetIdleWallpaper(inputString,NULL,0));
        }
    else
        User::Leave(KErrNotFound);
    }

// --------------------------------------------------------------------
// CSysInfoService::GetInfoL() SYNC
// Retrives the specified attribute value.
// aOutput contains attribute value.
// --------------------------------------------------------------------
//
EXPORT_C void CSysInfoService::GetInfoL( const TDesC& aEntity, const TDesC& aKey, 
                                    CSysData*& aOutput,const CSysData* aInput )
    {
    // retrieve data based Entity
    if( !aEntity.CompareF(KNetwork) )
        GetNetworkInfoL(aKey,aOutput);

    else if( !aEntity.CompareF(KBattery) )
        GetBatteryInfoL(aKey,aOutput);

    else if( !aEntity.CompareF(KConnectivity) )
        GetConnectivittyInfoL(aKey,aOutput);

    else if( !aEntity.CompareF(KDisplay) )
        GetDisplayInfoL(aKey,aOutput);

    else if( !aEntity.CompareF(KGeneral) )
        GetGeneralInfoL(aKey,aOutput);

    else if( !aEntity.CompareF(KMemory) )
        GetMemoryInfoL(aKey,aInput,aOutput);

    else if( !aEntity.CompareF(KDevice) )
        GetDeviceInfoL(aKey,aOutput);

    else if( !aEntity.CompareF(KFeatures) )
        GetFeatureInfoL(aKey,aOutput);
    
    else if ( !aEntity.CompareF( KCameraInfo ) )
        GetCameraDataL( aKey,aOutput );

    else
        User::Leave(KErrNotFound);
    }

// --------------------------------------------------------------------
// CSysInfoService::GetInfoL() ASYNC
// Creates an appropriate active object to serve the purpose of the 
// specified system attribute. Adds created active object to 
// Active Store.
// --------------------------------------------------------------------
//
EXPORT_C void CSysInfoService::GetInfoL( const TDesC& aEntity, const TDesC& aKey, 
                                    TInt32 aTransID, ISystemObserver* aCallback, 
                                    const CSysData* aInput )
    {
    if(!aCallback)
        User::Leave(KErrGeneral);

    TSysRequest systemRequest(aEntity,aKey,aInput,aTransID,aCallback,
                                            TSysRequest::EASyncONESHOT);

    CActiveRequest* activeRequestObj;
    CActiveRequest::CreateActiveRequestL(systemRequest,activeRequestObj);

    //place handle on cleanupstack.
    CleanupStack::PushL(activeRequestObj);
    //Add request handle to active store.
    ActiveStore::AddRequestL(activeRequestObj);
    CleanupStack::Pop(activeRequestObj);
    //Issue request.
    TInt err = activeRequestObj->Request();

    if( KErrNone != err)
        {
        ActiveStore::RemoveRequest(aTransID);
        User::Leave(err);
        }
    }

// --------------------------------------------------------------------
// CSysInfoService::GetNotificationL() ASYNC
// Creates an appropriate active object to serve the purpose of the 
// specified system attribute. Adds created active object to 
// Active Store.
// --------------------------------------------------------------------
//
EXPORT_C void CSysInfoService::GetNotificationL( const TDesC& aEntity, 
                                    const TDesC& aKey, TInt32 aTransID, 
                                    ISystemObserver* aCallback, 
                                    const CSysData* aInput )
    {
    if(!aCallback)
        User::Leave(KErrGeneral);

    TSysRequest systemRequest(aEntity,aKey,aInput,aTransID,aCallback,
                                        TSysRequest::ENotification);

    CActiveRequest* activeRequestObj;
    CActiveRequest::CreateActiveRequestL(systemRequest,activeRequestObj);

    //place handle on cleanupstack.
    CleanupStack::PushL(activeRequestObj);

    //Add request handle to active store.
    ActiveStore::AddRequestL(activeRequestObj);

    //Issue request.
    TInt err = activeRequestObj->Request();

    if( KErrNone != err)
        {
        //remove request handle on cleanup stack.
        CleanupStack::Pop(activeRequestObj);
        ActiveStore::RemoveRequest(aTransID);
        User::Leave(err);
        }

    //remove request handle on cleanup stack.
    CleanupStack::Pop(activeRequestObj);
    }

// --------------------------------------------------------------------
// CSysInfoService::GetNetworkInfoL()
// Retrives network related synchronous keys information.
// returns CSysData.
// --------------------------------------------------------------------
//
void CSysInfoService::GetNetworkInfoL(TPtrC aKey,CSysData*& aSysData)
    {
    TInt status = 0;
    if ( !aKey.CompareF(KRegistrationStatus) )
        {
        User::LeaveIfError(RProperty::Get(KPSUidNetworkInfo,
                                    KNWRegistrationStatus,status));
        }
    else if( !aKey.CompareF(SysInfo::KNetworkMode) )
        {
        User::LeaveIfError(RProperty::Get(KPSUidNetworkInfo,
                                    KNWTelephonyNetworkMode,status));
        }
    else
        {
        User::Leave(KErrNotFound);
        }
    aSysData = CStatus::NewL((status-1));
    }

// --------------------------------------------------------------------
// CSysInfoService::GetBatteryInfoL()
// Retrives battery related synchronous keys information.
// On return aSysData consists of key value.
// --------------------------------------------------------------------
//
void CSysInfoService::GetBatteryInfoL(TPtrC aKey,CSysData*& aSysData)
    {
    TInt status = 0;
    if( !aKey.CompareF(KChargingStatus) )
        {
        TInt chargeStatus = 0;
        User::LeaveIfError(RProperty::Get(KPSUidHWRMPowerState,
                                    KHWRMChargingStatus,chargeStatus));
        // ChargeStatus is manupulated to give only these states Charging,
        // NotCharging and Unknown
        if ( EChargingStatusCharging == chargeStatus || 
                EChargingStatusAlmostComplete == chargeStatus || 
                EChargingStatusChargingContinued == chargeStatus )
            status = ECharging;
        else if( EChargingStatusNotConnected == chargeStatus || 
                    EChargingStatusNotCharging == chargeStatus ||
                    EChargingStatusChargingComplete == chargeStatus )
            status = ENotCharging;
        else
            status = EUnknown;
        }
    else
        User::Leave(KErrNotFound);
    aSysData = CStatus::NewL(status);	
    }
// --------------------------------------------------------------------
// CSysInfoService::GetMemoryInfoL()
// Retrives memory related synchronous keys information.
// On return aSysData consists of SA value.
// --------------------------------------------------------------------
//
void CSysInfoService::GetMemoryInfoL(const TDesC& aKey, const CSysData* aInput,
										CSysData*& aOutput)
    {
    RFs Fs;
    CleanupClosePushL(Fs);
    User::LeaveIfError(Fs.Connect());

    if ( !aKey.CompareF(KListDrives) )
        {
        TDriveList drives;
        User::LeaveIfError(Fs.DriveList(drives));
        aOutput = CDriveList::NewL(drives);
        }
    else if( !aKey.CompareF(KDriveInfo) )
        {
        CDriveInfo* inputDrvInfo=NULL;
        if( aInput && CSysData::EDriveInfo == aInput->DataType())
            inputDrvInfo = (CDriveInfo*) aInput;
        else
            User::Leave(KErrArgument);

        TInt drvNumber = inputDrvInfo->DriveNumber();
        if ( !Fs.IsValidDrive(drvNumber) )
            User::Leave(KErrNotFound);

        TVolumeInfo volumeInfo;
        User::LeaveIfError(Fs.Volume(volumeInfo,drvNumber));
        aOutput = CDriveInfo::NewL(drvNumber,volumeInfo);
        }
    else if( !aKey.CompareF(KMemoryCard) )
        {
        TInt memoryCardState (-1);
        TInt defaultMemoryCard( 0 );
        User::LeaveIfError( DriveInfo::GetDefaultDrive( DriveInfo::EDefaultRemovableMassStorage, defaultMemoryCard ) );
        TUint driveStatus( 0 );
        User::LeaveIfError( DriveInfo::GetDriveStatus( Fs, defaultMemoryCard, driveStatus ) );
        if( driveStatus & DriveInfo::EDrivePresent )
            memoryCardState = ETrue;
        else
            memoryCardState = EFalse;        
        aOutput = CStatus::NewL(memoryCardState);

        }
    else
        User::Leave(KErrNotFound);
 
    CleanupStack::PopAndDestroy(&Fs);
    }

// --------------------------------------------------------------------
// CSysInfoService::GetFeatureInfoL()
// Retrives feature related synchronous keys information.
// On return aSysData consists of key value.
// --------------------------------------------------------------------
//
void CSysInfoService::GetFeatureInfoL(TPtrC aKey,CSysData*& aSysData)
    {
    TInt featureID(0);

    // Get the Feature ID to query feature manager.
    if( !aKey.CompareF(KBlueTooth) )
        featureID = KFeatureIdBt;
    else if( !aKey.CompareF(KInfraRed) )
        featureID = KFeatureIdIrda;
    else if( !aKey.CompareF(KCamera) )
        featureID = KFeatureIdCamera;
    else if( !aKey.CompareF(KMemoryCard) )
        featureID = KFeatureIdMmc;
    else if( !aKey.CompareF(KFMRadio) )
        featureID = KFeatureIdFmRadio;
    else if( !aKey.CompareF(KQwerty) )
        featureID = KFeatureIdQwertyInput;
    else if( !aKey.CompareF(KWLan) )
        featureID = KFeatureIdProtocolWlan;
    else if( !aKey.CompareF(KUsb) )
        featureID = KFeatureIdUsb;
    else if( !aKey.CompareF(KPen) )
        featureID = KFeatureIdPenSupport;
    else if( !aKey.CompareF(KLED) )
        featureID = KFeatureIdPenSupport;
    else if( !aKey.CompareF(KCoverUI) )
        featureID = KFeatureIdCoverDisplay;
    else if( !aKey.CompareF(KSideVolumeKeys) )
        featureID = KFeatureIdSideVolumeKeys;
    else if( !aKey.CompareF(KVibra) )
        featureID = KFeatureIdVibra;
    else if( !aKey.CompareF(KVideoDecoder) )
        {
        MMMFDevVideoPlayObserverImpl obsImpl;
        RArray<TUid> aDecoders;
        CMMFDevVideoPlay *videoPlay=CMMFDevVideoPlay::NewL(obsImpl);
        //place object on cleanupstack.
        CleanupStack::PushL(videoPlay);
        
        videoPlay->GetDecoderListL(aDecoders);
        CVideoDecDataList *decDataList=CVideoDecDataList::NewL();
        for(int i=0;i<aDecoders.Count();i++)
            {
            CVideoDecoderInfo *decoderInfo=videoPlay->VideoDecoderInfoLC(aDecoders[i]);
            CVideoDecDataList::CVideoDecData *data=new CVideoDecDataList::CVideoDecData(decoderInfo->Manufacturer(),decoderInfo->Identifier(),decoderInfo->MaxBitrate(),decoderInfo->Accelerated(),decoderInfo->Version().Name());
            decDataList->AppendL(data);
            CleanupStack::PopAndDestroy(decoderInfo);
            }
        
        aSysData = decDataList;
        CleanupStack::PopAndDestroy(videoPlay);
        return;     
        }
    else
        User::Leave(KErrNotFound);

    //Initialize feature manager if not.
    if (!iFeatureManagerInitialized)
        {
        FeatureManager::InitializeLibL();
        iFeatureManagerInitialized = ETrue;
        }

    TBool isSupported = ETrue;
    // LED feature is read using HAL others feature manager.
    if( !aKey.CompareF(KLED) )
        {
        TInt NumLEDs(0);
        TInt Err = HAL::Get(HALData::ELEDs,NumLEDs);
        if( KErrNone == Err )
            isSupported = ETrue;
        else if( KErrNotSupported == Err )
            isSupported = EFalse;
        else
            User::Leave(Err);
        }
    else
        {
        isSupported = FeatureManager::FeatureSupported(featureID);
        }

    aSysData = CStatus::NewL(isSupported);
    }

// --------------------------------------------------------------------
// CSysInfoService::GetConnectivityInfoL()
// Retrives Connectivity related synchronous keys information.
// On return aSysData consists of key value.
// --------------------------------------------------------------------
//
void CSysInfoService::GetConnectivittyInfoL(TPtrC aKey,CSysData*& aSysData)
    {
    if ( !aKey.CompareF(KBlueTooth) )
        {
        TInt bTPower = 0;
        RepositoryUtil::GetRepositoryKeyL(KCRUidBluetoothPowerState,
                                                KBTPowerState,bTPower);
        aSysData = CStatus::NewL(bTPower);
        }
    else if( !aKey.CompareF(KInfraRed) )
        {
        TInt IRStatus(0);
        TInt status(0);
        User::LeaveIfError(RProperty::Get(KIrdaPropertyCategory,
                                                KIrdaStatus,IRStatus));

        // Map all possible Infra red status values to ON, OFF and UnKnown states.
        if ( TIrdaStatusCodes::EIrLoaded == IRStatus || 
                TIrdaStatusCodes::EIrDiscoveredPeer == IRStatus ||
                TIrdaStatusCodes::EIrBlocked == IRStatus || 
                TIrdaStatusCodes::EIrLostPeer == IRStatus || 
                TIrdaStatusCodes::EIrDisconnected == IRStatus )
            status = EOn;
        else if( TIrdaStatusCodes::EIrUnloaded == IRStatus )
            status = EOff;
        else
            status = EUnknown;

        aSysData = CStatus::NewL(status);
        }
    else if( !aKey.CompareF(KWLanMacAddress) )
        {
        //result format 00:18:0f:1e:96:a2.
        TBuf8<KPSWlanMacAddressLength> DesC8AddrText;
        TBuf<KPhoneWlanMacAddressLength> FormatedMacAddress;

        User::LeaveIfError(RProperty::Get(KPSUidWlan,
                                        KPSWlanMacAddress,DesC8AddrText));
        for ( TInt i=0; i < KPSWlanMacAddressLength; i++ )
            {
            // Set separator
            if( i > 0 )
                FormatedMacAddress.Append(KPhoneWlanSeparator);
            
            // Set data
            TBuf<10> FormatText;
            FormatText.Format(KWLanMACDataFormat,DesC8AddrText[i]);
            FormatedMacAddress.Append(FormatText);
            }  
        aSysData = CStringData::NewL(FormatedMacAddress);
        }
    else if( !aKey.CompareF(KWirelessConnSupport) )
        {
        CDesCArray*     connTypesDesArray;
        connTypesDesArray = new (ELeave) CDesCArrayFlat(4);
        CleanupStack::PushL(connTypesDesArray);

         //Initialize the feature manager if not already done.
         if (!iFeatureManagerInitialized)
         {
             FeatureManager::InitializeLibL();
             iFeatureManagerInitialized = ETrue;
         }
         
         if(FeatureManager::FeatureSupported(KFeatureIdBt))
             {
             connTypesDesArray->AppendL(KBT);
             }
         if(FeatureManager::FeatureSupported(KFeatureIdIrda))
             {
             connTypesDesArray->AppendL(KIrda);
             }
         if(FeatureManager::FeatureSupported(KFeatureIdProtocolWlan))
             {
             connTypesDesArray->AppendL(KWlan);
             }
         if(FeatureManager::FeatureSupported(KFeatureIdProtocolGsm))
             {
             connTypesDesArray->AppendL(KGsm);
             }
         if(FeatureManager::FeatureSupported(KFeatureIdProtocolWcdma))
             {
             connTypesDesArray->AppendL(KWcdma);
             }
         if(FeatureManager::FeatureSupported(KFeatureIdProtocolCdma))
             {
             connTypesDesArray->AppendL(KCdma);
             }

        //connTypesDesArray ownership passed to CStringList.
        aSysData = CStringList::NewL(connTypesDesArray);
        CleanupStack::Pop(connTypesDesArray);         
        }
    else
        User::Leave(KErrNotFound);
    }

// --------------------------------------------------------------------
// CSysInfoService::GetGeneralInfoL()
// Retrives General Entity related synchronous keys information.
// On return aSysData consists of key value.
// --------------------------------------------------------------------
//
void CSysInfoService::GetGeneralInfoL(TPtrC aKey,CSysData*& aSysData)
    {
    if( !aKey.CompareF(KConnectedAccessories) )
        {
        aSysData = CAccList::NewL();
        }
    else if( !aKey.CompareF(KInputLanguage) )
        {
        TInt inputLang = 0;
        RepositoryUtil::GetRepositoryKeyL(KCRUidAknFep,
                                        KAknFepInputTxtLang,inputLang);
        aSysData = CStatus::NewL(inputLang);
        }    
    else if ( !aKey.CompareF( KDisplayLanguage ) )
        {
        HBufC* phoneLang = NULL;
        TBuf<KPhoneLanguageLength> language;
        TRAP_IGNORE(phoneLang = AknLangUtils::DisplayLanguageTagL());           
        language.Copy( phoneLang->Des() );
        delete phoneLang;
        aSysData = CStringData::NewL( language );
        }
    else if( !aKey.CompareF(KSupportedLanguages) )
        {
        aSysData = CLanguageList::NewL();
        }
    else if( !aKey.CompareF(KPridictiveText) )
        {
        TInt pridictiveText =0;
        RepositoryUtil::GetRepositoryKeyL(KCRUidAknFep,
                                        KAknFepPredTxtFlag,pridictiveText);
        aSysData = CStatus::NewL(pridictiveText);
        }
    else if( !aKey.CompareF(KVibraActive) )
        {
        TInt vibraState =0;
        RepositoryUtil::GetRepositoryKeyL(KCRUidVibraCtrl,
                                KVibraCtrlProfileVibraEnabled,vibraState);
        aSysData = CStatus::NewL(vibraState);
        }
    else if( !aKey.CompareF(KFlipStatus) )
        {
        TInt flipState = 0;
        User::LeaveIfError(RProperty::Get(KPSUidHWRM,
                                            KHWRMFlipStatus,flipState));
        if (flipState == EPSHWRMFlipOpen)
            flipState = EOpen;
        else if (flipState == EPSHWRMFlipClosed)
            flipState = EClosed;
        else
            flipState = EUnknown;

        aSysData = CStatus::NewL(flipState);
        }	
    else if( !aKey.CompareF(KGripStatus) )
        {
        TInt gripState = 0;
        User::LeaveIfError(RProperty::Get(KPSUidHWRM,
                                            KHWRMGripStatus,gripState));
        if (gripState == EPSHWRMGripOpen)
            gripState = EOpen;
        else if (gripState == EPSHWRMGripClosed)
            gripState = EClosed;
        else
            gripState = EUnknown;
        
        aSysData = CStatus::NewL(gripState);
        }
    else if( !aKey.CompareF(KAvailableUSBModes) )
        {
        GetAvailableUsbModesL(aSysData);
        }
    else if( !aKey.CompareF(KActiveUSBMode) )
        {
        RUsb usbsessn;

        CleanupClosePushL(usbsessn);
        User::LeaveIfError(usbsessn.Connect());
        TInt activePersonality = 0;
        User::LeaveIfError(usbsessn.GetCurrentPersonalityId(activePersonality));
        HBufC* activeUsbMode = NULL;
        User::LeaveIfError(usbsessn.GetDescription(activePersonality,activeUsbMode));
        aSysData = CStringData::NewL(*activeUsbMode);
        CleanupStack::PopAndDestroy(&usbsessn);
        }
    else
        User::Leave(KErrNotFound);
    }

// --------------------------------------------------------------------
// CSysInfoService::GetDisplayInfoL()
// Retrives Display Entity related synchronous keys information.
// On return aSysData consists of key value.
// --------------------------------------------------------------------
//
void CSysInfoService::GetDisplayInfoL(TPtrC aKey,CSysData*& aSysData)
    {
    if( !aKey.CompareF(KBrightness) )
        {
        TInt brightness = 0;
        RepositoryUtil::GetRepositoryKeyL(KCRUidLightSettings,
                                            KLightIntensity,brightness);
        
        aSysData = CStatus::NewL(brightness);
        }
    else if( !aKey.CompareF(KKeyGaurdTime) )
        {
        TInt keygaurdtime = 0;
        RepositoryUtil::GetRepositoryKeyL(KCRUidSecuritySettings,
                                KSettingsAutomaticKeyguardTime,keygaurdtime);
        
        aSysData = CStatus::NewL(keygaurdtime);
        }
    else if( !aKey.CompareF(KScreenSaverTimeOut) )
        {
        TInt screenSaverTimeOut = 0;
        RepositoryUtil::GetRepositoryKeyL(KCRUidPersonalizationSettings,
                                KSettingsScreenSaverPeriod,screenSaverTimeOut);
        
        aSysData = CStatus::NewL(screenSaverTimeOut);
        }	
    else if( !aKey.CompareF(KAutoLockTime) )
        {
        TInt autoLockTime = 0;
        RepositoryUtil::GetRepositoryKeyL(KCRUidSecuritySettings,
                                KSettingsAutoLockTime,autoLockTime);
        
        aSysData = CStatus::NewL(autoLockTime);
        }	
    else if( !aKey.CompareF(KAutoLockStatus) )
        {
        TInt keyLockState = 0;
        RepositoryUtil::GetRepositoryKeyL(KCRUidSecuritySettings,
                                KSettingsAutolockStatus,keyLockState);
        
        aSysData = CStatus::NewL(keyLockState);
        }	
    else if( !aKey.CompareF(KWallpaper) )
        {
        User::Leave(KErrNotSupported);
        }
    else if( !aKey.CompareF(KLightTimeOut) )
        {
        TInt lightTimeOut = 0;
        RepositoryUtil::GetRepositoryKeyL(KCRUidLightSettings,
                                KDisplayLightsTimeout,lightTimeOut);
        
        aSysData = CStatus::NewL(lightTimeOut);
        }
    else if( !aKey.CompareF(KDisplayResolution) )
        {
        TInt xPixels(0);
        TInt yPixels(0);
        User::LeaveIfError(HAL::Get(HALData::EDisplayXPixels,xPixels));
        User::LeaveIfError(HAL::Get(HALData::EDisplayYPixels,yPixels));
        aSysData = CResolution::NewL(xPixels,yPixels);
        }		
    else if( !aKey.CompareF(KDisplayOrientation) )
        {
        RWsSession session;
        CleanupClosePushL(session);
        User::LeaveIfError(session.Connect());
        CWsScreenDevice *Device = new (ELeave) CWsScreenDevice(session);
        CleanupStack::PushL(Device);
        Device->Construct();
        TPixelsTwipsAndRotation twipsRotation;
        Device->GetDefaultScreenSizeAndRotation(twipsRotation);
        aSysData = CStatus::NewL(twipsRotation.iRotation);
        CleanupStack::PopAndDestroy(2,&session);
        }
    else
        User::Leave(KErrNotFound);
    }

// --------------------------------------------------------------------
// CSysInfoService::GetDeviceInfoL()
// Retrives Device Entity related synchronous keys information.
// On return aSysData consists of key value.
// --------------------------------------------------------------------
//
void CSysInfoService::GetDeviceInfoL(TPtrC aKey,CSysData*& aSysData)
    {
    //if iDeviceInfo not instantiated before. Instantiate now.
    if( !iDeviceInfo )
        iDeviceInfo = CDeviceInfo::NewL();

    // read the requested key value.
    if ( !aKey.CompareF(KFirmwareVersion) )
        aSysData = CStringData::NewL(iDeviceInfo->FirmwareVersion());

    else if( !aKey.CompareF(KProductType) )
        aSysData = CStringData::NewL(iDeviceInfo->ProductType());

    else if( !aKey.CompareF(KManufacturer) )
        aSysData = CStringData::NewL(iDeviceInfo->Manufaturer());

    else if( !aKey.CompareF(KPhoneModel) )
        aSysData = CStringData::NewL(iDeviceInfo->Model());

    else if( !aKey.CompareF(KIMEI) )
        aSysData = CStringData::NewL(iDeviceInfo->IMEI());

    else if( !aKey.CompareF(KMachineID) )
        aSysData = CStatus::NewL(iDeviceInfo->MachineId());

    else if( !aKey.CompareF(KPlatformVersion) )
        {
        TInt majorVer(0);
        TInt minorVer(0);
        iDeviceInfo->GetPlatformVersion(majorVer,minorVer);
        aSysData = CVersion::NewL(majorVer,minorVer);
        }
    else
        User::Leave(KErrNotFound);
    }

// --------------------------------------------------------------------
// CSysInfoService::GetAvailableUsbModesL()
// Retrives available USB modes.
// returns CSysData.
// --------------------------------------------------------------------
//
void CSysInfoService::GetAvailableUsbModesL(CSysData*& aSysData)
    {
    RUsb usbsessn;
    CleanupClosePushL(usbsessn);
    User::LeaveIfError(usbsessn.Connect());

    RArray<TInt> usbModes;
    CleanupClosePushL(usbModes);

    User::LeaveIfError(usbsessn.GetPersonalityIds(usbModes));

    CDesCArray*		usbModesDesArray;
    usbModesDesArray = new (ELeave) CDesCArrayFlat(KGranularity);
    CleanupStack::PushL(usbModesDesArray);

    HBufC* modeName = NULL;
    TInt Count = usbModes.Count();
    for (TInt i=0; i<Count; i++)
        {
        usbsessn.GetDescription(usbModes[i],modeName);
        //Creates own copy of the text.
        usbModesDesArray->AppendL(*modeName);
        // free allocated memory by GetDescription.
        delete modeName;
        }

    //UsbModesDesArray ownership passed to CStringList.
    aSysData = CStringList::NewL(usbModesDesArray);
    CleanupStack::Pop(usbModesDesArray);
    CleanupStack::PopAndDestroy(2,&usbsessn);
    }

// --------------------------------------------------------------------
// CSysInfoService::GetACameraDataL()
// Returns the readonly properties of camera - Media Types and Sizes Supported.
// returns CSysData.
// --------------------------------------------------------------------
//
void CSysInfoService::GetCameraDataL( TPtrC aKey, CSysData*& aSysData )
    {
    if ( !aKey.CompareF( KCameraProperties ) )
        {
        CImagingConfigManager* cfgMgr = CImagingConfigManager::NewL();
        CleanupStack::PushL( cfgMgr );
        TImageQualitySet set;
        RPointerArray<CResolution> camResArr( KGranularity );
        CDesCArray* mimeArray= NULL;
        mimeArray = new (ELeave) CDesCArrayFlat( KGranularity );
        CleanupStack::PushL( mimeArray );

        CCameraResolutionList* resList= NULL;
        CStringList* mimeList= NULL;

        TInt totalLevels = cfgMgr->NumberOfImageQualityLevels();
        CArrayFixFlat<TUint>* levels = new (ELeave) CArrayFixFlat<TUint>( totalLevels );
        CleanupStack::PushL( levels );

        cfgMgr->GetImageQualityLevelsL( *levels, KPrimaryCameraDisplayID );
        TInt numLevels(levels->Count() );
        for ( int i=0; i<numLevels; i++ )
            {
            cfgMgr->GetImageQualitySet( set, levels->At(i), KPrimaryCameraDisplayID );
            if ( set.iCamcorderVisible > 0 )
                {
                CResolution* camRes = CResolution::NewL( set.iImageWidth, set.iImageHeight );
                CleanupStack::PushL( camRes );
                camResArr.AppendL( camRes );
                CleanupStack::Pop( camRes );

                TText8* mimeType = set.iImageFileMimeType;
                TInt length = strlen( (const char *)mimeType );
                TPtrC8 mimeTypePtr( mimeType, length );
                TBuf8<KMimeTypeLength> mimeTypeBuf = mimeTypePtr;
                TBuf16<KMimeTypeLength> imageMimeType;
                imageMimeType.Copy( mimeTypeBuf );
                mimeArray->AppendL( imageMimeType );
                }
            }
        resList = CCameraResolutionList::NewL( camResArr ); //Ownership of camResArr is transferred to CCameraResolutionList
        mimeList = CStringList::NewL( mimeArray ); //Ownership of mimeArray is transferred to CStringList
        CleanupStack::PopAndDestroy( levels );
        CleanupStack::Pop( mimeArray );
        CleanupStack::PopAndDestroy( cfgMgr );
        camResArr.Reset();
        aSysData = CCameraInfo::NewL( resList, mimeList ); //Ownership of resList and mimeList is transferred to CCameraInfo
        }
    else
        User::Leave( KErrNotFound );
    }

// End of file.
