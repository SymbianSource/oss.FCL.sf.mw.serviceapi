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


#ifndef __ENTITYKEYS_H__
#define __ENTITYKEYS_H__

namespace SysInfo
{
_LIT(KNetwork,	"Network");
_LIT(KBattery,	"Battery");
_LIT(KGeneral,	"General");
_LIT(KConnectivity,"Connectivity");
_LIT(KFeatures,	"Features");
_LIT(KDisplay,	"Display");
_LIT(KMemory,	"Memory");
_LIT(KDevice,	"Device");
_LIT(KCameraInfo,   "Camera");


_LIT(KSignalStrength,	"SignalStrength");
_LIT(KRegistrationStatus,"RegistrationStatus");
_LIT(KNetworkMode,		"NetworkMode");
_LIT(KHomeNetwork,		"HomeNetwork");
_LIT(KCurrentNetwork,	"CurrentNetwork");
_LIT(KLocationArea,		"LocationArea");
_LIT(KCellID,			"CellID");

_LIT(KChargingStatus,	"ChargingStatus");
_LIT(KBatteryStrength,	"BatteryStrength");

_LIT(KAccessoryStatus,		"AccessoryStatus");
_LIT(KConnectedAccessories,	"ConnectedAccessories");
_LIT(KInputLanguage,		"InputLanguage");
_LIT(KDisplayLanguage,      "DisplayLanguage");
_LIT(KSupportedLanguages,	"SupportedLanguages");
_LIT(KPridictiveText,		"PredictiveText");
_LIT(KVibraActive,			"VibraActive");
_LIT(KAvailableUSBModes,	"AvailableUSBModes");
_LIT(KActiveUSBMode,		"ActiveUSBMode");
_LIT(KFlipStatus,			"FlipStatus");
_LIT(KGripStatus,			"GripStatus");
_LIT(KNumberOfSoftKeys,		"NumberOfSoftKeys");


_LIT(KBlueTooth,		"BlueTooth");
_LIT(KInfraRed,			"InfraRed");
_LIT(KActiveConnections,"ActiveConnections");
_LIT(KConnectionStatus,	"ConnectionStatus");
_LIT(KWLanMacAddress,	"WLanMacAddress");
_LIT(KWirelessConnSupport, "WirelessConnSupport");

_LIT(KCamera,			"Camera");
_LIT(KMemoryCard,		"MemoryCard");
_LIT(KFMRadio,			"FMRadio");
_LIT(KQwerty,			"Qwerty");
_LIT(KWLan,				"WLan");
_LIT(KUsb,				"Usb");
_LIT(KPen,				"Pen");
_LIT(KLED,				"LED");
_LIT(KCoverUI,			"CoverUI");
_LIT(KSideVolumeKeys,	"SideVolumeKeys");
_LIT(KVibra,			"Vibra");
_LIT(KVideoDecoder,     "VideoDecoder");

_LIT(KBT, "Bluetooth");
_LIT(KIrda, "Irda");
_LIT(KWlan, "Wlan");
_LIT(KGsm, "Gsm");
_LIT(KWcdma, "Wcdma");
_LIT(KCdma, "Cdma");

_LIT(KBrightness,		"Brightness");
_LIT(KPowerSaverTimeOut,"PowerSaverTimeOut");
_LIT(KScreenSaverTimeOut,"ScreenSaverTimeOut");
_LIT(KUserInactivity,	"UserInactivity");
_LIT(KAutoLockTime,		"AutoLockTime");
_LIT(KAutoLockStatus,	"AutoLockStatus");
_LIT(KKeyGaurdTime,		"KeyGuardTime");
_LIT(KWallpaper,		"Wallpaper");
_LIT(KLightTimeOut,		"LightTimeOut");
_LIT(KDisplayResolution,"DisplayResolution");
_LIT(KDisplayOrientation,"DisplayOrientation");

_LIT(KListDrives,		"ListDrives");
_LIT(KDriveInfo,		"DriveInfo");
_LIT(KCriticalMemory,	"CriticalMemory");

_LIT(KFirmwareVersion,	"FirmwareVersion");
_LIT(KPlatformVersion,	"PlatformVersion");
_LIT(KSymbianOsVersion,	"OsVersion");
_LIT(KProductType,		"ProductType");
_LIT(KManufacturer,		"Manufacturer");
_LIT(KMachineID,		"MachineID");
_LIT(KPhoneModel,		"PhoneModel");
_LIT(KIMEI,				"IMEI");

_LIT(KCameraProperties,       "CameraProperties");

enum TStatus
	{
	EUnknown = -1,
	ENotCharging=0,
	ECharging=1,
	EOff=0,
	EOn=1, 
	EDisabled=0,
	EEnabled=1, 
	ENotLocked=0,
	ELocked=1,
	EClosed=0,
	EOpen=1,
	ERemoved=0,
	EInserted=1,
	ENormal=0,
	ERotated90,
	ERotated180,
	ERotated270
	};
	
}

#endif __ENTITYKEYS_H__
