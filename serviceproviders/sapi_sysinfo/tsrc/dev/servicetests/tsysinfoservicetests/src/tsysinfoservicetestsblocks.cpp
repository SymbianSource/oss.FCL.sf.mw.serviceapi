/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:   ?Description
*
*/




// INCLUDE FILES
#include <e32svr.h>
#include <StifParser.h>
#include <Stiftestinterface.h>
#include <hal.h>
#include "tsysinfoservicetests.h"
#include "tbatterystrengthasyn.h"
#include "tuseractivitynotifier.h"
#include "Tautolocknotifier.h"

#include "sysinfoservice.h"
#include "entitykeys.h"
#include <COEMAIN.H> 

using namespace SysInfo;
_LIT(KROMInstallDir,"\\system\\install\\");
_LIT(KS60ProductIdFile,"Series60v*.sis");

	const TPtrC KFeature[] = 
	{
	KCamera.operator()(),
	KMemoryCard.operator()(),
	KFMRadio.operator()(),
	KQwerty.operator()(),
	KWLan.operator()(),
	KUsb.operator()(),
	KPen.operator()(),
	KLED.operator()(),
	KCoverUI.operator()(),
	KSideVolumeKeys.operator()(),
	KVibra.operator()(),
	};

const TInt KSize = sizeof(KFeature)/sizeof(TPtrC);

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctsysinfoservicetests::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void Ctsysinfoservicetests::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// Ctsysinfoservicetests::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt Ctsysinfoservicetests::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
//Features
        ENTRY( "Features",			Ctsysinfoservicetests::FeaturesL),
//Battery
        ENTRY( "BatteryLevelSync",			Ctsysinfoservicetests::BatteryLevelAutoL),
        ENTRY( "BatteryStrengthASync",		Ctsysinfoservicetests::BatteryStrengthAsyncL),
        ENTRY( "BatteryChargeSync",			Ctsysinfoservicetests::BatteryChargingAutoL),
//Device
        ENTRY( "FirmwareVersion",		Ctsysinfoservicetests::FirmwareVersionL),
		ENTRY( "PlatformVersion",    	Ctsysinfoservicetests::PlatformVersionL),
		ENTRY( "SymbianOSversion",  	Ctsysinfoservicetests::SymbianOSVersionL),
		ENTRY( "MachineID",  			Ctsysinfoservicetests::MachineIDL),
		ENTRY( "ProductType",  			Ctsysinfoservicetests::ProductTypeL),
		ENTRY( "Manufacturer", 			Ctsysinfoservicetests::ManufacturerL),
		ENTRY( "PhoneModel", 			Ctsysinfoservicetests::PhoneModelL),
		ENTRY( "IMEINumber", 			Ctsysinfoservicetests::IMEINumberL),		
//General
        ENTRY( "ConnectedAcc",    Ctsysinfoservicetests::ConnectedAcc),
        ENTRY( "SetDisplayLang",    Ctsysinfoservicetests::SetDisplayLang),
        ENTRY( "GetDisplayLang",    Ctsysinfoservicetests::GetDisplayLang),
        ENTRY( "SetInputLang",    Ctsysinfoservicetests::SetInputLang),
        ENTRY( "SupportedLang",    Ctsysinfoservicetests::SupportedLang),
	    ENTRY( "InputLang",    Ctsysinfoservicetests::InputLang),
        ENTRY( "PredText",    Ctsysinfoservicetests::PredText),
        ENTRY( "VibraStatus",    Ctsysinfoservicetests::VibraStatus),
        ENTRY( "AvailableUSBModes",    Ctsysinfoservicetests::AvailableUSBModes),
        ENTRY( "ActiveUSBModes",    Ctsysinfoservicetests::ActiveUSBModes),
        ENTRY( "NotificationCancelVibra",    Ctsysinfoservicetests::NotificationCancelVibra),
        ENTRY( "CameraData",    Ctsysinfoservicetests::CameraData),
        ENTRY( "CameraDataWrongEntity", Ctsysinfoservicetests::CameraDataNegativeEntity),
        ENTRY( "CameraDataWrongKey",   Ctsysinfoservicetests::CameraDataNegativeKey),
//Connectivity
  		ENTRY( "ConnBluetooth",    Ctsysinfoservicetests::ConnBluetooth),
        ENTRY( "IRStatus",    Ctsysinfoservicetests::IRStatus),
        ENTRY( "GetActiveConnections",    Ctsysinfoservicetests::GetActiveConnections),
        ENTRY( "GetWlanMacAddress",    Ctsysinfoservicetests::GetWlanMacAddress),
        ENTRY( "GetActiveConnectionsCancel",    Ctsysinfoservicetests::GetActiveConnectionsCancel),
//Display
        ENTRY( "GetSetBrightness",		Ctsysinfoservicetests::GetSetBrightnessL),
		ENTRY( "GetSetScreensaverTimeOut",	Ctsysinfoservicetests::GetSetScreensaverTimeOutL),
		ENTRY( "UserInactivityNotifier",  Ctsysinfoservicetests::UserInactivityNotifierL),
		ENTRY( "SetGetAutoLockTime",  		Ctsysinfoservicetests::SetGetAutoLockTimeL),
		ENTRY( "AutoLockNotifier",  	Ctsysinfoservicetests::AutoLockNotifierL),
		ENTRY( "DisplayResolution",  	Ctsysinfoservicetests::DisplayResolutionL),
		ENTRY( "DisplayOrientation",  Ctsysinfoservicetests::DisplayOrientationL),
		ENTRY( "GetSetLightTimeOut",	Ctsysinfoservicetests::GetSetLightTimeOutL),		
		ENTRY( "GetSetWallPaper",		Ctsysinfoservicetests::GetSetWallPaperL),
		ENTRY( "GetSetKeyGaurdTime",	Ctsysinfoservicetests::GetSetKeyGaurdL),
//Memory
        ENTRY( "GetListofDrives",		Ctsysinfoservicetests::GetListofDrivesL),
		ENTRY( "GetDriveInfo",    		Ctsysinfoservicetests::GetDriveInfoL),
        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

TInt  Ctsysinfoservicetests::FeaturesL(CStifItemParser& )
	{	
    _LIT( KExample, "TestFeaturesL" );
    iLog->Log( KExample );
	TInt Err(PASS);
	
#if (!(defined(__WINS__) || defined(__WINSCW__)))
	TInt MachineId;
	HAL::Get(HALData::EMachineUid, MachineId);
	iLog->Log(_L("Device MachineID: %x"),MachineId );
	switch(MachineId)
	{
		case 0x20001857:	//E70
						Err |= TestE70();
						break;
		case 0x20000606:	//N6290
						Err |= TestN6290();
						break;
		case 0x101fb3e8:	
						Err |= TestDevlon();
						break;
		default:
						iLog->Log(_L("Unknown Device "));
						TestDevlon();
						Err |= PASS;
						break;
	}
#endif
	return Err;
	}
		
TInt  Ctsysinfoservicetests::FirmwareVersionL(CStifItemParser& /*aItem*/)
	{	
    _LIT( KExample, "FirmwareVersionL" );
    iLog->Log( KExample );
	TInt Err(PASS);
	
	__UHEAP_MARK;
	CSysInfoService *obj = CSysInfoService::NewL();
	CleanupStack::PushL(obj);

	
	CSysData* output=NULL;
	
	TRAPD(err,obj->GetInfoL(KDevice,KFirmwareVersion,output));
	if (!err)
		{
		if(!output)
			{
			Err |= FAIL;
			iLog->Log( _L("Output data Set to NULL") );
			}
		else
			{
			CleanupStack::PushL(output);
			if( CSysData::EStringData != output->DataType() )
				{
				iLog->Log( _L("Invalid output data") );
				Err |= FAIL;
				}
			else
				{
				TPtrC firmwareversion;
				((CStringData*)output)->StringData(firmwareversion);
				iLog->Log( _L("Firmware Version: %s"), firmwareversion.Ptr());
				if(!(firmwareversion.Length() > 0))
					{
					iLog->Log( _L("Null string returned..") );
					Err |= FAIL;
					}
				}
			CleanupStack::PopAndDestroy(output);
			}
		}
	else
		{
		Err |= err;
		iLog->Log( _L("GetInfo API returned error") );
		}

	CleanupStack::PopAndDestroy(obj);
	
	__UHEAP_MARKEND;
	return Err;
	}
		
TInt  Ctsysinfoservicetests::SymbianOSVersionL(CStifItemParser& /*aItem*/)
	{	
    _LIT( KExample, "SymbianOSVersionL" );
    iLog->Log( KExample );
	TInt Err(PASS);
	_LIT(KSymbianOsVersion,"OSVersion");
	__UHEAP_MARK;
	CSysInfoService *obj = CSysInfoService::NewL();
	CleanupStack::PushL(obj);
	
	CSysData* output;
	
	TRAPD(err,obj->GetInfoL(KDevice,KSymbianOsVersion,output));
	if (err == KErrNotFound)
		{
		iLog->Log( _L("SymbianOsVersion not supported") );
		}
	else
		{
		Err |= FAIL;
		iLog->Log( _L("GetInfo API should return KErrNotFound") );
		}

	CleanupStack::PopAndDestroy(obj);
	
	__UHEAP_MARKEND;
	return Err;
	}

TInt  Ctsysinfoservicetests::PlatformVersionL(CStifItemParser& /*aItem*/)
	{	
    _LIT( KExample, "PlatformVersionL" );
    iLog->Log( KExample );
	TInt Err(PASS);
	
	__UHEAP_MARK;
	CSysInfoService *obj = CSysInfoService::NewL();
	CleanupStack::PushL(obj);

	CSysData* output;
	
	TRAPD(err,obj->GetInfoL(KDevice,KPlatformVersion,output));
	if (!err)
		{
		if(!output)
			{
			Err |= FAIL;
			iLog->Log( _L("Output data Set to NULL") );
			}
		else
			{
			CleanupStack::PushL(output);
			//Check data type
			if( CSysData::EVersion != output->DataType() )
				{
				iLog->Log( _L("Invalid output data") );
				Err |= FAIL;
				}
			else
				{
				TInt Major,Minor;
				Major = ((CVersion*)output)->MajorVersion();
				Minor = ((CVersion*)output)->MinorVersion();
				iLog->Log( _L("Platform version: Major: %d, Minor: %d"), Major,Minor);
				TInt ExpectedMajor,ExpectedMinor;
				GetPlatformVersion(ExpectedMajor,ExpectedMinor);
				if(!(ExpectedMajor == Major && ExpectedMinor == Minor))
					{
					iLog->Log( _L("incorrect major minor versions returned..") );
					Err |= FAIL;
					}
				}
			CleanupStack::PopAndDestroy(output);
			}
		}
	else
		{
		Err |= err;
		iLog->Log( _L("GetInfo API returned error") );
		}

	CleanupStack::PopAndDestroy(obj);
	
	__UHEAP_MARKEND;
	return Err;
	}

TInt  Ctsysinfoservicetests::ProductTypeL(CStifItemParser& /*aItem*/)
	{	
    _LIT( KExample, "ProductTypeL" );
    iLog->Log( KExample );
	TInt Err(PASS);
	
	__UHEAP_MARK;
	CSysInfoService *obj = CSysInfoService::NewL();
	CleanupStack::PushL(obj);

	CSysData* output;
	
	TRAPD(err,obj->GetInfoL(KDevice,KProductType,output));
	if (!err)
		{
		if(!output)
			{
			Err |= FAIL;
			iLog->Log( _L("Output data Set to NULL") );
			}
		else
			{
			CleanupStack::PushL(output);
			//Check data type
			if( CSysData::EStringData != output->DataType() )
				{
				iLog->Log( _L("Invalid output data") );
				Err |= FAIL;
				}
			else
				{
#if ( !((defined(__WINS__) || defined(__WINSCW__))) )
				TPtrC ProductType;
				((CStringData*)output)->StringData(ProductType);
				iLog->Log( _L("Product Type: %s"), ProductType.Ptr());
#endif
				}
				
			CleanupStack::PopAndDestroy(output);
			}
		}
	else
		{
		Err |= err;
		iLog->Log( _L("GetInfo API returned error") );
		}

	CleanupStack::PopAndDestroy(obj);
	
	__UHEAP_MARKEND;
	return Err;
	}	

TInt  Ctsysinfoservicetests::MachineIDL(CStifItemParser& /*aItem*/)
	{	
    _LIT( KExample, "MachineIDL" );
    iLog->Log( KExample );
	TInt Err(PASS);
	
	__UHEAP_MARK;
	CSysInfoService *obj = CSysInfoService::NewL();
	CleanupStack::PushL(obj);

	CSysData* output;
	
	TRAPD(err,obj->GetInfoL(KDevice,KMachineID,output));
	if (!err)
		{
		if(!output)
			{
			Err |= FAIL;
			iLog->Log( _L("Output data Set to NULL") );
			}
		else
			{
			CleanupStack::PushL(output);
			//Check data type
			if( CSysData::EStatus != output->DataType() )
				{
				iLog->Log( _L("Invalid output data") );
				Err |= FAIL;
				}
			else
				{
				TInt MachineID;
				MachineID = ((CStatus*)output)->Status();
				iLog->Log( _L("Machine ID: %x"), MachineID);
				TInt ExpectedMachineId;
				HAL::Get(HALData::EMachineUid, ExpectedMachineId);
				if(!(ExpectedMachineId == MachineID))
					{
					iLog->Log( _L("Incorrect Machine ID") );
					Err |= FAIL;					
					}
				}
			CleanupStack::PopAndDestroy(output);
			}
		}
	else
		{
		Err |= err;
		iLog->Log( _L("GetInfo API returned error") );
		}

	CleanupStack::PopAndDestroy(obj);
	
	__UHEAP_MARKEND;
	return Err;
	}	


TInt  Ctsysinfoservicetests::ManufacturerL(CStifItemParser& /*aItem*/)
	{	
    _LIT( KExample, "ManufacturerL" );
    iLog->Log( KExample );
	TInt Err(PASS);
	
	__UHEAP_MARK;
	CSysInfoService *obj = CSysInfoService::NewL();
	CleanupStack::PushL(obj);

	CSysData* output;
	
	TRAPD(err,obj->GetInfoL(KDevice,KManufacturer,output));
	if (!err)
		{
		if(!output)
			{
			Err |= FAIL;
			iLog->Log( _L("Output Data Set to NULL") );
			}
		else
			{
			CleanupStack::PushL(output);
			//Check data type
			if( CSysData::EStringData != output->DataType() )
				{
				iLog->Log( _L("Invalid output data") );
				Err |= FAIL;
				}
			else
				{
				TPtrC Manufacturer;
				((CStringData*)output)->StringData(Manufacturer);
				iLog->Log( _L("PhoneModel: %s"), Manufacturer.Ptr());
				TBuf<100> manufacturer(Manufacturer);
				manufacturer.UpperCase();
				if( manufacturer.Compare(_L("NOKIA")) )
					{
					iLog->Log( _L("Incorrect Manufacturer Name") );
					Err |= FAIL;
					}
				CleanupStack::PopAndDestroy(output);
				}
			}
		}
	else
		{
		Err |= err;
		iLog->Log( _L("GetInfo API returned error") );
		}

	CleanupStack::PopAndDestroy(obj);
	
	__UHEAP_MARKEND;
	return Err;
	}	

TInt  Ctsysinfoservicetests::PhoneModelL(CStifItemParser& /*aItem*/)
	{	
    _LIT( KExample, "PhoneModelL" );
    iLog->Log( KExample );
	TInt Err(PASS);
	
	__UHEAP_MARK;
	CSysInfoService *obj = CSysInfoService::NewL();
	CleanupStack::PushL(obj);

	CSysData* output;
	
	TRAPD(err,obj->GetInfoL(KDevice,KPhoneModel,output));
	if (!err)
		{
		if(!output)
			{
			Err |= FAIL;
			iLog->Log( _L("Output data Set to NULL") );
			}
		else
			{
			CleanupStack::PushL(output);
			//Check data type
			if( CSysData::EStringData != output->DataType() )
				{
				iLog->Log( _L("Invalid output data") );
				Err |= FAIL;
				}
			else
				{
				TPtrC PhoneModel;
				((CStringData*)output)->StringData(PhoneModel);
				
				iLog->Log( _L("PhoneModel: %s"), PhoneModel.Ptr());
				
				if(!(PhoneModel.Length() > 2))
					{
					iLog->Log( _L("Invalid PhoneModel") );
					Err |= FAIL;
					}
				}
			CleanupStack::PopAndDestroy(output);
			}
		}
	else
		{
		Err |= err;
		iLog->Log( _L("GetInfo API returned error") );
		}

	CleanupStack::PopAndDestroy(obj);
	
	__UHEAP_MARKEND;
	return Err;
	}
	
TInt  Ctsysinfoservicetests::IMEINumberL(CStifItemParser& /*aItem*/)
	{	
    _LIT( KExample, "IMEINumberL" );
    iLog->Log( KExample );
	TInt Err(PASS);
	
	__UHEAP_MARK;
	CSysInfoService *obj = CSysInfoService::NewL();
	CleanupStack::PushL(obj);

	CSysData* output;
	
	TRAPD(err,obj->GetInfoL(KDevice,KIMEI,output));
	if (!err)
		{
		if(!output)
			{
			Err |= FAIL;
			iLog->Log( _L("Output data Set to NULL") );
			}
		else
			{
			CleanupStack::PushL(output);
			//Check data type
			if( CSysData::EStringData != output->DataType() )
				{
				iLog->Log( _L("Invalid output data") );
				Err |= FAIL;
				}
			else
				{
				TPtrC IMEINumber;
				((CStringData*)output)->StringData(IMEINumber);
				iLog->Log( _L("IMEI: %s"), IMEINumber.Ptr());
				if(!(IMEINumber.Length() >= 15))
					{
					iLog->Log( _L("Invalid producttype") );
					Err |= FAIL;
					}
				}
			CleanupStack::PopAndDestroy(output);
			}
		}
	else
		{
		Err |= err;
		iLog->Log( _L("GetInfo API returned error") );
		}


	CleanupStack::PopAndDestroy(obj);
	
	__UHEAP_MARKEND;
	return Err;
	}	
TInt  Ctsysinfoservicetests::GetListofDrivesL(CStifItemParser& /*aItem*/)
	{	
    _LIT( KExample, "GetListofDrivesL" );
    iLog->Log( KExample );
	TInt Err(PASS);
	
	__UHEAP_MARK;
	CSysInfoService *obj = CSysInfoService::NewL();
	CleanupStack::PushL(obj);

	CSysData* output=NULL;
	TRAPD(err,obj->GetInfoL(KMemory,KListDrives,output));
	if (!err)
		{
		if(!output)
			{
			Err |= FAIL;
			iLog->Log( _L("Output data Set to NULL") );
			}
		else
			{
			CleanupStack::PushL(output);
			//On Emulator this must give C:2,D:3,Z:25
			if( CSysData::EDriveList != output->DataType() )
				{
				iLog->Log( _L("Invalid output data") );
				Err |= FAIL;
				}
			else
				{
				CDriveList* drivelist = (CDriveList*)output;
				TInt count = drivelist->Count();
				//atleast one drive.
				if(count<=0)
					{
					iLog->Log( _L("Atlease One drive must be present") );
					Err |= FAIL;
					}
				else
					{
					iLog->Log( _L("Available Drives: "));
					for(TInt i=0;i<count;i++)
						{
						TInt driveno = (*drivelist)[i];
						iLog->Log( _L("Drive (Number,Letter): (%d, %c)"),driveno,97+driveno );
						if( driveno < 0 )
							{
							iLog->Log( _L("Invalid drive number found") );
							Err |= FAIL;
							}
						}
					}
				CleanupStack::PopAndDestroy(output);
				}
			}
		}
	else
		{
		Err |= err;
		iLog->Log( _L("GetInfo API returned error") );
		}

	CleanupStack::PopAndDestroy(obj);
	
	__UHEAP_MARKEND;
	return Err;
	}
		
TInt  Ctsysinfoservicetests::GetDriveInfoL(CStifItemParser& /*aItem*/)
	{	
    _LIT( KExample, "GetDriveInfoL" );
    iLog->Log( KExample );
	TInt Err(PASS);
	
	__UHEAP_MARK;
	CSysInfoService *obj = CSysInfoService::NewL();
	CleanupStack::PushL(obj);

	CSysData* output=NULL;
	TRAPD(err,obj->GetInfoL(KMemory,KListDrives,output));
	if (!err)
		{
		if(!output)
			{
			Err |= FAIL;
			iLog->Log( _L("Output data Set to NULL") );
			}
		else
			{
			CleanupStack::PushL(output);
			//On Emulator this must give C:2,D:3,Z:25
			if( CSysData::EDriveList != output->DataType() )
				{
				iLog->Log( _L("Invalid output data") );
				Err |= FAIL;
				}
			else
				{
				CDriveList* drivelist = (CDriveList*)output;
				TInt count = drivelist->Count();
				//atleast one drive.
				if(count<=0)
					{
					iLog->Log( _L("Atleast One drive must be present") );
					Err |= FAIL;
					}
				else
					{
					for(TInt i=0;i<count;i++)
						{
						TInt driveno = (*drivelist)[i];
						CSysData* input1 = CDriveInfo::NewL(driveno);
						CleanupStack::PushL(input1);
						
						CSysData* output1;
						
						TRAPD(err,obj->GetInfoL(KMemory,KDriveInfo,output1,input1));
						CleanupStack::PopAndDestroy(input1);
						if(!err )
							{
							CleanupStack::PushL(output1);
							User::LeaveIfError(DriveInfoL(output1));
							CleanupStack::PopAndDestroy(output1);
							}
						else
							{
							if( err == KErrNotReady && driveno == 4)
								{
								iLog->Log( _L("Memory card not present"));
								continue;
								}
							iLog->Log( _L("Error retriving drive information of %d drive, err: %d"),driveno,err);
							Err |= FAIL;
							}						
						}//for
					}//count
				}//datatype
			CleanupStack::PopAndDestroy(output);
			}//output
		}//err
	else
		{
		Err |= err;
		iLog->Log( _L("GetInfo API returned error") );
		}
	
	iLog->Log( _L("Test Completed err: %d"),Err);
	CleanupStack::PopAndDestroy(obj);
	
	__UHEAP_MARKEND;
	return Err;
	}

TInt Ctsysinfoservicetests::DriveInfoL(CSysData* aOutput)
{
	TInt Err(PASS);
	CDriveInfo* driveinfo = (CDriveInfo*)aOutput;
	
	TInt drvno = driveinfo->DriveNumber();
	iLog->Log( _L("Drive (Number,Letter): (%d, %c)"),drvno,97+drvno );
	if( !(drvno >=0 && drvno <= EDriveZ ))
		{
		iLog->Log( _L("Incorrect drive number in output data") );
		Err |= FAIL;
		}
	
	iLog->Log( _L("-------------------------------") );
	TPtrC drvname;
	driveinfo->DriveName(drvname);
	iLog->Log( _L("Drive Name: %s"),drvname.Ptr() );

	iLog->Log( _L("Total Space: %ld"),driveinfo->TotalSpace() );
	if( driveinfo->TotalSpace() < 0)
		{
		iLog->Log( _L("Incorrect total space") );
		Err |= FAIL;
		}				

	iLog->Log( _L("Free Space:  %ld"),driveinfo->FreeSpace() );
	if( driveinfo->FreeSpace() < 0)
		{
		iLog->Log( _L("Incorrect free space") );
		Err |= FAIL;
		}	

	TInt CriticalLevel = driveinfo->CriticalSpace();
	iLog->Log( _L("Critical Space: %d"),CriticalLevel );
	if( CriticalLevel <= 0)
		{
		iLog->Log( _L("Incorrect Critical Sapce") );
		Err |= FAIL;
		}

	iLog->Log( _L("Media Type: %d"),driveinfo->MediaType() );
	if( !(driveinfo->MediaType() <= EMediaRotatingMedia) )
		{
		iLog->Log( _L("Incorrect media type") );
		Err |= FAIL;
		}
	
	iLog->Log( _L("-------------------------------") );
	return Err;
	}


TInt  Ctsysinfoservicetests::BatteryLevelAutoL(CStifItemParser& )
	{	
    _LIT( KExample, "BatteryLevelAutoL" );
    iLog->Log( KExample );
	TInt Err(PASS);

#if ( !(defined(__WINS__) || defined(__WINSCW__)) )	
	__UHEAP_MARK;
	CSysInfoService *obj = CSysInfoService::NewL();
	CleanupStack::PushL(obj);
	
	CSysData* output=NULL;
	
	_LIT(KBatteryLevel,"BatteryLevel");
		
	TRAPD(err,obj->GetInfoL(KBattery,KBatteryLevel,output));
	if ( err == KErrNotFound )
		{
		Err = PASS;
		iLog->Log( _L("Battery Level Not supported "));
		}
	else
		{
		Err |= FAIL;
		iLog->Log( _L("GetInfo API returned error: %d Expected Error: %d"), err,KErrNotFound);
		}
		
	CleanupStack::PopAndDestroy(obj);
	__UHEAP_MARKEND;

#endif 
	return Err;
	}

TInt  Ctsysinfoservicetests::BatteryChargingAutoL(CStifItemParser& )
	{	
    _LIT( KExample, "BatteryChargingAutoL" );
    iLog->Log( KExample );
	TInt Err(PASS);

#if ( !(defined(__WINS__) || defined(__WINSCW__)) )	
	__UHEAP_MARK;
	CSysInfoService *obj = CSysInfoService::NewL();
	CleanupStack::PushL(obj);
	
	CSysData* output=NULL;
	
	TRAPD(err,obj->GetInfoL(KBattery,KChargingStatus,output));
	if (!err)
		{
		if(!output)
			{
			Err |= FAIL;
			iLog->Log( _L("Output data Set to NULL") );
			}
		else
			{
			CleanupStack::PushL(output);
			//Check data type
			if( CSysData::EStatus != output->DataType() )
				{
				iLog->Log( _L("Invalid output data") );
				Err |= FAIL;
				}
			else
				{
				TInt BatteryCharg;
				BatteryCharg = ((CStatus*)output)->Status();
				
				iLog->Log(_L("Battery Charger State: %d"),BatteryCharg);
				
				if( !(BatteryCharg == 0 || BatteryCharg == 1) )
					{
					iLog->Log( _L("Invalid Battery Level : %d"),BatteryCharg);
					Err |= FAIL;
					}
				}
			CleanupStack::PopAndDestroy(output);
			}
		}
	else
		{
		Err |= err;
		iLog->Log( _L("GetInfo API returned error: %d"), err);
		}

	CleanupStack::PopAndDestroy(obj);
	__UHEAP_MARKEND;

#endif 
	return Err;
	}

TInt  Ctsysinfoservicetests::BatteryStrengthAsyncL(CStifItemParser&)
	{	
    _LIT( KExample, "BatteryStrengthAsyncL" );
    iLog->Log( KExample );
	TInt Err(PASS);
	
#if ( !(defined(__WINS__) || defined(__WINSCW__)) )
	__UHEAP_MARK;
	CBatteryStrengthAsync* test = CBatteryStrengthAsync::NewL(iLog);
	test->Start();
	Err = test->Result();
	delete test;

#endif
	__UHEAP_MARKEND;
	return Err;
	}

TInt  Ctsysinfoservicetests::GetSetBrightnessL(CStifItemParser& /*aItem*/)
	{	
    _LIT( KExample, "GetSetBrightnessL" );
    iLog->Log( KExample );
	TInt Err(PASS);
	
	__UHEAP_MARK;
	CSysInfoService *obj = CSysInfoService::NewL();
	CleanupStack::PushL(obj);

	CSysData* output=NULL;
	TRAPD(err,obj->GetInfoL(KDisplay,KBrightness,output));
	if (!err)
		{
		if(!output)
			{
			Err |= FAIL;
			iLog->Log( _L("Output data Set to NULL") );
			}
		else
			{
			CleanupStack::PushL(output);
			if( CSysData::EStatus != output->DataType() )
				{
				iLog->Log( _L("Invalid output data") );
				Err |= FAIL;
				}
			else
				{
				TInt OldBrightness;
				CStatus* brightness = (CStatus*)output;
				OldBrightness = brightness->Status();
				iLog->Log( _L("System Brigthness Value: %d"),OldBrightness );
				CleanupStack::PopAndDestroy(output);
#ifdef _SET_BRIGHTNESS_SUPPORTED_				
				CStatus* set_bright_val = CStatus::NewL(80);
				CleanupStack::PushL(set_bright_val);
				
				TRAPD(err,obj->SetInfoL(KDisplay,KBrightness,set_bright_val));
				if(!err)
					{
					iLog->Log( _L("Brigthness set to %d"),80 );
					}
				else
					{
					Err |= err;
					iLog->Log( _L("SetInfoL API returned error") );
					}
				
				CleanupStack::PopAndDestroy(set_bright_val);
				
				iLog->Log( _L("Getting Brightness Value after setting to 80") );

				CSysData* output1=NULL;
				TRAP(err,obj->GetInfoL(KDisplay,KBrightness,output1));
				if(!err)
					{
					if(!output1)
						{
						Err |= FAIL;
						iLog->Log( _L("Output data Set to NULL") );
						}
					else
						{
						CleanupStack::PushL(output1);
						TInt cur_brightness = ((CStatus*)output1)->Status();
						if (cur_brightness != 80)
							{
							Err |= FAIL;
							iLog->Log( _L("Brightness value not set to 80, read val:  %d"), cur_brightness);
							}
						else
							{
							iLog->Log( _L("Brightness value set to 80"));
							}
						CleanupStack::PopAndDestroy(output1);
						}
					}
				else
					{
					Err |= err;
					iLog->Log( _L("GetInfoL API returned error on secound attempt") );
					}
				
				iLog->Log( _L("Restoring Brightness Value to %d"), OldBrightness);	
				set_bright_val = CStatus::NewL(OldBrightness);
				CleanupStack::PushL(set_bright_val);
				
				TRAP(err,obj->SetInfoL(KDisplay,KBrightness,set_bright_val));
				if(!err)
					{
					iLog->Log( _L("Brigthness Value restored to %d"),OldBrightness );
					}
				else
					{
					Err |= err;
					iLog->Log( _L("SetInfoL API returned error") );
					}
				
				CleanupStack::PopAndDestroy(set_bright_val);
#endif
				}
			}
		}
	else
		{
		Err |= err;
		iLog->Log( _L("GetInfo API returned error") );
		}

	CleanupStack::PopAndDestroy(obj);
	
	__UHEAP_MARKEND;
	return Err;
	}
		
TInt  Ctsysinfoservicetests::GetSetScreensaverTimeOutL(CStifItemParser& /*aItem*/)
	{	
    _LIT( KExample, "GetSetScreensaverTimeOutL" );
    iLog->Log( KExample );
	TInt Err(PASS);
	
	__UHEAP_MARK;
	CSysInfoService *obj = CSysInfoService::NewL();
	CleanupStack::PushL(obj);

	CSysData* output=NULL;
	TRAPD(err,obj->GetInfoL(KDisplay,KScreenSaverTimeOut,output));
	if (!err)
		{
		if(!output)
			{
			Err |= FAIL;
			iLog->Log( _L("Output data Set to NULL") );
			}
		else
			{
			CleanupStack::PushL(output);
			if( CSysData::EStatus != output->DataType() )
				{
				iLog->Log( _L("Invalid output data") );
				Err |= FAIL;
				}
			else
				{
				TInt OldScrTimeOut;
				CStatus* ScrTimeOut = (CStatus*)output;
				OldScrTimeOut = ScrTimeOut->Status();
				
				iLog->Log( _L("System Screen Saver Timeout Value: %d"),OldScrTimeOut );
				CleanupStack::PopAndDestroy(output);
#ifdef _SET_SCREESAVER_SUPPORTED_				
				CStatus* set_scrtimeout_val = CStatus::NewL(30);
				CleanupStack::PushL(set_scrtimeout_val);
				
				TRAPD(err,obj->SetInfoL(KDisplay,KScreenSaverTimeOut,set_scrtimeout_val));
				if(!err)
					{
					iLog->Log( _L("Screen saver timeout set to %d"),30 );
					}
				else
					{
					Err |= err;
					iLog->Log( _L("SetInfoL API returned error") );
					}
				
				CleanupStack::PopAndDestroy(set_scrtimeout_val);
				
				iLog->Log( _L("Getting Screen saver timeout Value after setting to 30") );

				CSysData* output1=NULL;
				TRAP(err,obj->GetInfoL(KDisplay,KScreenSaverTimeOut,output1));
				if(!err)
					{
					if(!output1)
						{
						Err |= FAIL;
						iLog->Log( _L("Output data Set to NULL") );
						}
					else
						{
						CleanupStack::PushL(output1);
						TInt cur_scrtimeout = ((CStatus*)output1)->Status();
						if (cur_scrtimeout != 30)
							{
							Err |= FAIL;
							iLog->Log( _L("Screen saver timeout value not set to 30, read val:  %d"), cur_scrtimeout);
							}
						else
							{
							iLog->Log( _L("Brightness value set to 30"));
							}
						CleanupStack::PopAndDestroy(output1);
						}
					}
				else
					{
					Err |= err;
					iLog->Log( _L("GetInfoL API returned error on secound attempt") );
					}
				
				iLog->Log( _L("Restoring Screen saver timeout Value to %d"), OldScrTimeOut);	
				set_scrtimeout_val = CStatus::NewL(OldScrTimeOut);
				CleanupStack::PushL(set_scrtimeout_val);
				
				TRAP(err,obj->SetInfoL(KDisplay,KScreenSaverTimeOut,set_scrtimeout_val));
				if(!err)
					{
					iLog->Log( _L("Screen saver value restored to %d"),OldScrTimeOut );
					}
				else
					{
					Err |= err;
					iLog->Log( _L("SetInfoL API returned error") );
					}
				
				CleanupStack::PopAndDestroy(set_scrtimeout_val);
#endif
				}
			}
		}
	else
		{
		Err |= err;
		iLog->Log( _L("GetInfo API returned error") );
		}

	CleanupStack::PopAndDestroy(obj);
	
	__UHEAP_MARKEND;
	return Err;
	}

TInt  Ctsysinfoservicetests::UserInactivityNotifierL(CStifItemParser& )
	{	
    _LIT( KExample, "UserInactivityNotifierL" );
    iLog->Log( KExample );
	TInt Err(PASS);

	__UHEAP_MARK;

	CTestUserActivity* test = CTestUserActivity::NewL(iLog,1,CTestUserActivity::ETESTINACTIVITY);
	test->Start();
	Err = test->Result();
	delete test;
		
	__UHEAP_MARKEND;

	return Err;
	}	
	
TInt  Ctsysinfoservicetests::UserActivityNotifierL(CStifItemParser& )
	{	
    _LIT( KExample, "UserInactivityNotifierL" );
    iLog->Log( KExample );
	TInt Err(PASS);

	__UHEAP_MARK;

	CTestUserActivity* test = CTestUserActivity::NewL(iLog,1,CTestUserActivity::ETESTACTIVITY);
	test->Start();
	Err = test->Result();
	delete test;
		
	__UHEAP_MARKEND;

	return Err;
	}	

TInt  Ctsysinfoservicetests::SetGetAutoLockTimeL(CStifItemParser& )
	{	
    _LIT( KExample, "SetGetAutoLockTimeL" );
    iLog->Log( KExample );
	TInt Err(PASS);
	
	__UHEAP_MARK;
	CSysInfoService *obj = CSysInfoService::NewL();
	CleanupStack::PushL(obj);

	CSysData* output=NULL;
	TRAPD(err,obj->GetInfoL(KDisplay,KAutoLockTime,output));
	if (!err)
		{
		if(!output)
			{
			Err |= FAIL;
			iLog->Log( _L("Output data Set to NULL") );
			}
		else
			{
			CleanupStack::PushL(output);
			if( CSysData::EStatus != output->DataType() )
				{
				iLog->Log( _L("Invalid output data") );
				Err |= FAIL;
				}
			else
				{
				TInt OldAutolockTime;
				CStatus* AutoLockTimeOut = (CStatus*)output;
				OldAutolockTime = AutoLockTimeOut->Status();
				
				iLog->Log( _L("System Auto Lock Time Value: %d"),OldAutolockTime );
				CleanupStack::PopAndDestroy(output);
#ifdef _SET_SCREESAVER_SUPPORTED_				
				CStatus* set_autolocktime_val = CStatus::NewL(1);
				CleanupStack::PushL(set_autolocktime_val);
				
				TRAPD(err,obj->SetInfoL(KDisplay,KAutoLockTime,set_autolocktime_val));
				if(!err)
					{
					iLog->Log( _L("Auto Lock time set to %d"),1 );
					}
				else
					{
					Err |= err;
					iLog->Log( _L("SetInfoL API returned error") );
					}
				
				CleanupStack::PopAndDestroy(set_autolocktime_val);
				
				iLog->Log( _L("Getting Auto Lock time Value after setting to 1") );

				CSysData* output1=NULL;
				TRAP(err,obj->GetInfoL(KDisplay,KAutoLockTime,output1));
				if(!err)
					{
					if(!output1)
						{
						Err |= FAIL;
						iLog->Log( _L("Output1 data Set to NULL") );
						}
					else
						{
						CleanupStack::PushL(output1);
						TInt cur_autolocktime = ((CStatus*)output1)->Status();
						if (cur_autolocktime != 1)
							{
							Err |= FAIL;
							iLog->Log( _L("Auto lock time value not set to 1, read val:  %d"), cur_autolocktime);
							}
						else
							{
							iLog->Log( _L("Auto lock value set to %d"),cur_autolocktime);
							}
						CleanupStack::PopAndDestroy(output1);
						}
					}
				else
					{
					Err |= err;
					iLog->Log( _L("GetInfoL API returned error on secound attempt") );
					}
				
				iLog->Log( _L("Restoring Auto lock time Value to %d"), OldAutolockTime);	
				set_autolocktime_val = CStatus::NewL(OldAutolockTime);
				CleanupStack::PushL(set_autolocktime_val);
				
				TRAP(err,obj->SetInfoL(KDisplay,KAutoLockTime,set_autolocktime_val));
				if(!err)
					{
					iLog->Log( _L("Screen saver value restored to %d"),OldAutolockTime );
					}
				else
					{
					Err |= err;
					iLog->Log( _L("SetInfoL API returned error") );
					}
				
				CleanupStack::PopAndDestroy(set_autolocktime_val);
#endif
				}
			}
		}
	else
		{
		Err |= err;
		iLog->Log( _L("GetInfo API returned error") );
		}

	CleanupStack::PopAndDestroy(obj);
	
	__UHEAP_MARKEND;
	return Err;
	}	

TInt  Ctsysinfoservicetests::AutoLockNotifierL(CStifItemParser& )
	{	
    _LIT( KExample, "AutoLockNotifierL" );
    iLog->Log( KExample );
	TInt Err(PASS);
	
	__UHEAP_MARK;

	CAutoLockNotifier* test = CAutoLockNotifier::NewL(iLog,1);
	test->Start();
	Err = test->Result();
	delete test;
		
	__UHEAP_MARKEND;

	return Err;
	}	

TInt  Ctsysinfoservicetests::DisplayResolutionL(CStifItemParser& )
	{	
    _LIT( KExample, "DisplayResolutionL" );
    iLog->Log( KExample );
	TInt Err(PASS);

	__UHEAP_MARK;
	CSysInfoService *obj = CSysInfoService::NewL();
	CleanupStack::PushL(obj);

	CSysData* output=NULL;
	TRAPD(err,obj->GetInfoL(KDisplay,KDisplayResolution,output));	
	if (!err)
		{
		if(!output)
			{
			Err |= FAIL;
			iLog->Log( _L("Output data Set to NULL") );
			}
		else
			{
			CleanupStack::PushL(output);
			if( CSysData::EResolution != output->DataType() )
				{
				iLog->Log( _L("Invalid output data") );
				Err |= FAIL;
				}
			else
				{
				CResolution* resolution = (CResolution*)output;
				TInt xpix = resolution->XPixels();
				TInt ypix = resolution->YPixels();
				if( xpix <= 0 || ypix<= 0)
					{
					Err |= FAIL;
					iLog->Log( _L("Incorrect Display Resolution.. "));
					}

				iLog->Log( _L("XPixels: %d"), xpix);
				iLog->Log( _L("YPixels: %d"), ypix);
				}
			CleanupStack::PopAndDestroy(output);
			}
		}
	else
		{
		Err |= err;
		iLog->Log( _L("GetInfo API returned error") );
		}

	CleanupStack::PopAndDestroy(obj);
	
	__UHEAP_MARKEND;
	return Err;	
	}	
	
TInt  Ctsysinfoservicetests::DisplayOrientationL(CStifItemParser& )
	{	
    _LIT( KExample, "DisplayOrientationL" );
    iLog->Log( KExample );
	TInt Err(PASS);

	__UHEAP_MARK;
	CSysInfoService *obj = CSysInfoService::NewL();
	CleanupStack::PushL(obj);

	CSysData* output=NULL;
	TRAPD(err,obj->GetInfoL(KDisplay,KDisplayOrientation,output));	
	if (!err)
		{
		if(!output)
			{
			Err |= FAIL;
			iLog->Log( _L("Output data Set to NULL") );
			}
		else
			{
			CleanupStack::PushL(output);
			if( CSysData::EStatus != output->DataType() )
				{
				iLog->Log( _L("Invalid output data") );
				Err |= FAIL;
				}
			else
				{
				CStatus* orientation = (CStatus*)output;
				TInt orient = orientation->Status();
				iLog->Log( _L("Display Orientation: %d"), orient);
				}
			CleanupStack::PopAndDestroy(output);
			}
		}
	else
		{
		Err |= err;
		iLog->Log( _L("GetInfo API returned error") );
		}

	CleanupStack::PopAndDestroy(obj);
	
	__UHEAP_MARKEND;
	return Err;	
	}	
TInt  Ctsysinfoservicetests::GetSetLightTimeOutL(CStifItemParser& )
	{	
    _LIT( KExample, "GetSetLightTimeOutL" );
    iLog->Log( KExample );
	TInt Err(PASS);
	
	__UHEAP_MARK;
	CSysInfoService *obj = CSysInfoService::NewL();
	CleanupStack::PushL(obj);

	CSysData* output=NULL;
	TRAPD(err,obj->GetInfoL(KDisplay,KLightTimeOut,output));
	if (!err)
		{
		if(!output)
			{
			Err |= FAIL;
			iLog->Log( _L("Output data Set to NULL") );
			}
		else
			{
			CleanupStack::PushL(output);
			if( CSysData::EStatus != output->DataType() )
				{
				iLog->Log( _L("Invalid output data") );
				Err |= FAIL;
				}
			else
				{
				TInt OldLightTimeOut;
				CStatus* LightTimeOut = (CStatus*)output;
				OldLightTimeOut = LightTimeOut->Status();
				
				iLog->Log( _L("System Light TimeOu Value: %d"),OldLightTimeOut );
				CleanupStack::PopAndDestroy(output);
#ifdef _SET_LIGHTSTIMEOUT_SUPPORTED_				
				CStatus* set_lighttimeout_val = CStatus::NewL(5);
				CleanupStack::PushL(set_lighttimeout_val);
				
				TRAPD(err,obj->SetInfoL(KDisplay,KLightTimeOut,set_lighttimeout_val));
				if(!err)
					{
					iLog->Log( _L("Light timeout set to %d"),5 );
					}
				else
					{
					Err |= err;
					iLog->Log( _L("SetInfoL API returned error") );
					}
				
				CleanupStack::PopAndDestroy(set_lighttimeout_val);
				
				iLog->Log( _L("Getting Light TimeOut Value after setting to 5") );

				CSysData* output1=NULL;
				TRAP(err,obj->GetInfoL(KDisplay,KLightTimeOut,output1));
				if(!err)
					{
					if(!output1)
						{
						Err |= FAIL;
						iLog->Log( _L("Output1 data Set to NULL") );
						}
					else
						{
						CleanupStack::PushL(output1);
						TInt cur_lighttimeout = ((CStatus*)output1)->Status();
						if (cur_lighttimeout != 5)
							{
							Err |= FAIL;
							iLog->Log( _L("Light TimeOut value not set to 1, read val:  %d"), cur_lighttimeout);
							}
						else
							{
							iLog->Log( _L("Light TimeOut value set to %d"),cur_lighttimeout);
							}
						CleanupStack::PopAndDestroy(output1);
						}
					}
				else
					{
					Err |= err;
					iLog->Log( _L("GetInfoL API returned error on secound attempt") );
					}
				
				iLog->Log( _L("Restoring Light Timeout Value to %d"), OldLightTimeOut);	
				set_lighttimeout_val = CStatus::NewL(OldLightTimeOut);
				CleanupStack::PushL(set_lighttimeout_val);
				
				TRAP(err,obj->SetInfoL(KDisplay,KLightTimeOut,set_lighttimeout_val));
				if(!err)
					{
					iLog->Log( _L("Light TimeOut value restored to %d"),OldLightTimeOut );
					}
				else
					{
					Err |= err;
					iLog->Log( _L("SetInfoL API returned error") );
					}
				CleanupStack::PopAndDestroy(set_lighttimeout_val);
#endif
				}
			}
		}
	else
		{
		Err |= err;
		iLog->Log( _L("GetInfo API returned error") );
		}

	CleanupStack::PopAndDestroy(obj);
	
	__UHEAP_MARKEND;
	return Err;
	}	

TInt  Ctsysinfoservicetests::GetSetWallPaperL(CStifItemParser& )
	{	
    _LIT( KExample, "GetSetWallPaperL" );
    iLog->Log( KExample );
	TInt Err(PASS);
/*	
	__UHEAP_MARK;
	CSysInfoService *obj = CSysInfoService::NewL();
	CleanupStack::PushL(obj);

	CSysData* output=NULL;
	TRAPD(err,obj->GetInfoL(KDisplay,KWallpaper,output));
	if (!err)
		{
		if(!output)
			{
			Err |= FAIL;
			iLog->Log( _L("Output data Set to NULL") );
			}
		else
			{
			CleanupStack::PushL(output);
			if( CSysData::EStatus != output->DataType() )
				{
				iLog->Log( _L("Invalid output data") );
				Err |= FAIL;
				}
			else
				{
				TInt OldLightTimeOut;
				CStatus* LightTimeOut = (CStatus*)output;
				OldLightTimeOut = LightTimeOut->Status();
				
				iLog->Log( _L("System Light TimeOu Value: %d"),OldLightTimeOut );
				CleanupStack::PopAndDestroy(output);
				
				CStatus* set_lighttimeout_val = CStatus::NewL(5);
				CleanupStack::PushL(set_lighttimeout_val);
				
				TRAPD(err,obj->SetInfoL(KDisplay,KLightTimeOut,set_lighttimeout_val));
				if(!err)
					{
					iLog->Log( _L("Light timeout set to %d"),5 );
					}
				else
					{
					Err |= err;
					iLog->Log( _L("SetInfoL API returned error") );
					}
				
				CleanupStack::PopAndDestroy(set_lighttimeout_val);
				
				iLog->Log( _L("Getting Light TimeOut Value after setting to 5") );

				CSysData* output1=NULL;
				TRAP(err,obj->GetInfoL(KDisplay,KLightTimeOut,output1));
				if(!err)
					{
					if(!output1)
						{
						Err |= FAIL;
						iLog->Log( _L("Output1 data Set to NULL") );
						}
					else
						{
						CleanupStack::PushL(output1);
						TInt cur_lighttimeout = ((CStatus*)output1)->Status();
						if (cur_lighttimeout != 5)
							{
							Err |= FAIL;
							iLog->Log( _L("Light TimeOut value not set to 1, read val:  %d"), cur_lighttimeout);
							}
						else
							{
							iLog->Log( _L("Light TimeOut value set to %d"),cur_lighttimeout);
							}
						CleanupStack::PopAndDestroy(output1);
						}
					}
				else
					{
					Err |= err;
					iLog->Log( _L("GetInfoL API returned error on secound attempt") );
					}
				
				iLog->Log( _L("Restoring Light Timeout Value to %d"), OldLightTimeOut);	
				set_lighttimeout_val = CStatus::NewL(OldLightTimeOut);
				CleanupStack::PushL(set_lighttimeout_val);
				
				TRAP(err,obj->SetInfoL(KDisplay,KLightTimeOut,set_lighttimeout_val));
				if(!err)
					{
					iLog->Log( _L("Light TimeOut value restored to %d"),OldLightTimeOut );
					}
				else
					{
					Err |= err;
					iLog->Log( _L("SetInfoL API returned error") );
					}
				CleanupStack::PopAndDestroy(set_lighttimeout_val);
				}
			}
		}
	else
		{
		Err |= err;
		iLog->Log( _L("GetInfo API returned error") );
		}

	CleanupStack::PopAndDestroy(obj);
*/	
	__UHEAP_MARKEND;
	return Err;
	}
	
TInt  Ctsysinfoservicetests::GetSetKeyGaurdL(CStifItemParser& /*aItem*/)
	{	
    _LIT( KExample, "GetSetKeyGaurdL" );
    iLog->Log( KExample );
	TInt Err(PASS);
	
	__UHEAP_MARK;
	CSysInfoService *obj = CSysInfoService::NewL();
	CleanupStack::PushL(obj);

	CSysData* output=NULL;
	TRAPD(err,obj->GetInfoL(KDisplay,KKeyGaurdTime,output));
	if (!err)
		{
		if(!output)
			{
			Err |= FAIL;
			iLog->Log( _L("Output data Set to NULL") );
			}
		else
			{
			CleanupStack::PushL(output);
			if( CSysData::EStatus != output->DataType() )
				{
				iLog->Log( _L("Invalid output data") );
				Err |= FAIL;
				}
			else
				{
				TInt OldKeyGaurdTime;
				CStatus* keygaurdtime = (CStatus*)output;
				OldKeyGaurdTime = keygaurdtime->Status();
				iLog->Log( _L("System keygaurdtime Value: %d"),OldKeyGaurdTime );
				CleanupStack::PopAndDestroy(output);
#ifdef _SET_KEYGAURD_SUPPORTED_				
				CStatus* set_keygaurdtime_val = CStatus::NewL(5);
				CleanupStack::PushL(set_keygaurdtime_val);
				
				TRAPD(err,obj->SetInfoL(KDisplay,KKeyGaurdTime,set_keygaurdtime_val));
				if(!err)
					{
					iLog->Log( _L("KeyGaurd Time set to %d"),5 );
					}
				else
					{
					Err |= err;
					iLog->Log( _L("SetInfoL API returned error") );
					}
				
				CleanupStack::PopAndDestroy(set_keygaurdtime_val);
				
				iLog->Log( _L("Getting KeyGaurd Time Value after setting to 5") );

				CSysData* output1=NULL;
				TRAP(err,obj->GetInfoL(KDisplay,KKeyGaurdTime,output1));
				if(!err)
					{
					if(!output1)
						{
						Err |= FAIL;
						iLog->Log( _L("Output data Set to NULL") );
						}
					else
						{
						CleanupStack::PushL(output1);
						TInt cur_keygaurdval = ((CStatus*)output1)->Status();
						if (cur_keygaurdval != 5)
							{
							Err |= FAIL;
							iLog->Log( _L("KeyGaurd Time value not set to 5, read val:  %d"), cur_keygaurdval);
							}
						else
							{
							iLog->Log( _L("KeyGaurd Time value set to 5"));
							}
						CleanupStack::PopAndDestroy(output1);
						}
					}
				else
					{
					Err |= err;
					iLog->Log( _L("GetInfoL API returned error on secound attempt") );
					}
				
				iLog->Log( _L("Restoring KeyGaurd Time Value to %d"), OldKeyGaurdTime);	
				set_keygaurdtime_val = CStatus::NewL(OldKeyGaurdTime);
				CleanupStack::PushL(set_keygaurdtime_val);
				
				TRAP(err,obj->SetInfoL(KDisplay,KKeyGaurdTime,set_keygaurdtime_val));
				if(!err)
					{
					iLog->Log( _L("KeyGaurd Time Value restored to %d"),OldKeyGaurdTime );
					}
				else
					{
					Err |= err;
					iLog->Log( _L("SetInfoL API returned error") );
					}
				
				CleanupStack::PopAndDestroy(set_keygaurdtime_val);
#endif
				}
			}
		}
	else
		{
		Err |= err;
		iLog->Log( _L("GetInfo API returned error") );
		}

	CleanupStack::PopAndDestroy(obj);
	
	__UHEAP_MARKEND;
	return Err;
	}




//returns OS VERSION
void Ctsysinfoservicetests::GetOSVersion(TInt& aMajor,TInt& aMinor)
{
	TInt MachineId;
	HAL::Get(HALData::EMachineUid, MachineId);
		switch(MachineId) 	
		{
		case 		0x101F466A :
		case	    0x101F8C19 :
		case	 	0x101FB2B1 :
		case	   	0x10005E33 :
		case		0X101FA031 :
		case		0x101F9071 :
									aMajor = 6;
									aMinor = 1;
									break;
		case 		0x101F408B :
		case		0x101FB2AE :
		case		0x10200AC6 :
		case		0x101F6B26 :
									aMajor = 7;
									aMinor = 0;
									break;
		case 		0x10200F97 :
		case		0x101FB3DD :
		case		0x101FB3F4 :					
		case		0x101FB3F3 :
		case		0x101F3EE3 :
		case		0x101FBE09 :
		case		0x101F8ED1 :
		case		0x1020E048 :
		case		0x101FF525 :	//iversion =  7.0s;
									aMajor = 7;
									aMinor = 0;
									break;
	 						
		case 		0x101FBB55 : 
		case		0x10200f99 :
		case		0x10200F9C :
		case		0x10200F9B :
									//	iversion 8.0a;
									aMajor = 8;
									aMinor = 0;
									break;
		case 		0x10200F9A :
		case		0x10200F98 :
									//iversion 8.1a;
									aMajor = 8;
									aMinor = 1;
									break;
		case 		0x1020E285 :
		case		0x10274BFA :
		case		0x10274BF9 :
		case		0x200005F8 :
		case		0x20000602 :
		case		0x200005FF :
		case		0x200005FB :
		case		0x200005FE :
		case		0x20000601 :
		case		0x200005F9 :
		case		0x200005FC :
		case		0x200005FA :
		case		0x20000600 :
		case		0x20000605 :
		case		0x20002495 :
		case		0x20001856 :
		case		0x20001858 :
		case		0x20002D7F :
		case		0x20001859 :
		case		0x20000604 :
		case		0x20001857 :
									aMajor = 9;
									aMinor = 1;
									break;
		case	 	0x20002D7C :
		case		0x20002D7B :
		case		0x20002D7E :
		case		0x20000606 :
		case		0x2000060A :
		case		0x2000060B :
		case		0x20002496 :
									aMajor = 9;
									aMinor = 2;
									break;
		case		0x101fb3e8 :	
		case		0x2000da56 :	
									aMajor = 9;
									aMinor = 3;
									break;
	}
}

void Ctsysinfoservicetests::GetPlatformVersion(TInt& aMajor, TInt& aMinor)
{
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
			parser.Inc(9);
			
			// Get major version value
			err = parser.Val(aMajor);
			
			if( parser.Get() != '.' || err )
				{
				aMajor = 0;
				}
			else
				{
			 	// Get minor version value
				err = parser.Val(aMinor);
				if( err )
					{
					aMajor = 0;
					aMinor = 0;
					}
				}
			}
		// clean up result
		CleanupStack::PopAndDestroy(result);
		}
	// clean up file session fs.
	CleanupStack::PopAndDestroy(&fs);	
}

TInt  Ctsysinfoservicetests::TestE70()
	{	
    _LIT( KExample, "TestE70L" );
    iLog->Log( KExample );
	TInt Err(PASS);
	
	__UHEAP_MARK;
	CSysInfoService *obj = CSysInfoService::NewL();
	CleanupStack::PushL(obj);

	TInt ExpectedValue[KSize]=
		{
		ETrue, //KCamera
		ETrue, //KMemoryCard
		EFalse, //KFMRadio
		ETrue, //KQwerty
		ETrue, //KWLan
		ETrue, //KUsb
		EFalse, //KPen
		EFalse, //KLED
		EFalse, //KCoverUI
		EFalse, //KSideVolumeKeys
		ETrue, //KVibra
		};
	
	for(TInt i=0;i<KSize;i++)
		{
		CSysData* output=NULL;
		TRAPD(err,obj->GetInfoL(KFeatures,KFeature[i],output));
		if (!err)
			{
			if(!output)
				{
				Err |= FAIL;
				iLog->Log( _L("Output data Set to NULL feature: %s"),KFeature[i].Ptr() );
				}
			else
				{
				CleanupStack::PushL(output);
				if( CSysData::EStatus != output->DataType() )
					{
					iLog->Log( _L("Invalid output data: %s"), KFeature[i].Ptr());
					Err |= FAIL;
					}
				else
					{
					TInt IsSupported = ((CStatus*)output)->Status();
					
					if(IsSupported)
						{
						iLog->Log( _L("Feature %s: Supported"), KFeature[i].Ptr());
						}
					else
						{
						iLog->Log( _L("Feature %s: Not Supported"), KFeature[i].Ptr());
						}
					
					if(ExpectedValue[i] != IsSupported)
						{
						iLog->Log( _L("Incorrect Feature of the device configuration :%s"), KFeature[i].Ptr());
						Err |= FAIL;
						}
					}
				CleanupStack::PopAndDestroy(output);
				}
			}
		else
			{
			Err |= err;
			iLog->Log( _L("GetInfo API returned error") );
			}
		}
	CleanupStack::PopAndDestroy(obj);
	return Err;
	}

TInt  Ctsysinfoservicetests::TestDevlon()
	{	
    _LIT( KExample, "TestDevlon" );
    iLog->Log( KExample );
	TInt Err(PASS);
	
	__UHEAP_MARK;
	CSysInfoService *obj = CSysInfoService::NewL();
	CleanupStack::PushL(obj);

	TInt ExpectedValue[KSize]=
		{
		ETrue, //KCamera
		ETrue, //KMemoryCard
		ETrue, //KFMRadio
		EFalse, //KQwerty
		ETrue, //KWLan
		ETrue, //KUsb
		ETrue, //KPen
		EFalse, //KLED
		EFalse, //KCoverUI
		ETrue, //KSideVolumeKeys
		ETrue, //KVibra
		};
	
	for(TInt i=0;i<KSize;i++)
		{
		CSysData* output=NULL;
		TRAPD(err,obj->GetInfoL(KFeatures,KFeature[i],output));
		if (!err)
			{
			if(!output)
				{
				Err |= FAIL;
				iLog->Log( _L("Output data Set to NULL feature: %s"),KFeature[i].Ptr() );
				}
			else
				{
				CleanupStack::PushL(output);
				if( CSysData::EStatus != output->DataType() )
					{
					iLog->Log( _L("Invalid output data: %s"), KFeature[i].Ptr());
					Err |= FAIL;
					}
				else
					{
					TInt IsSupported = ((CStatus*)output)->Status();
					
					if(IsSupported)
						{
						iLog->Log( _L("Feature %s: Supported"), KFeature[i].Ptr());
						}
					else
						{
						iLog->Log( _L("Feature %s: Not Supported"), KFeature[i].Ptr());
						}
					
					if(ExpectedValue[i] != IsSupported)
						{
						iLog->Log( _L("Incorrect Feature of the device configuration :%s"), KFeature[i].Ptr());
						Err |= FAIL;
						}
					}
				CleanupStack::PopAndDestroy(output);
				}
			}
		else
			{
			Err |= err;
			iLog->Log( _L("GetInfo API returned error") );
			}
		}
	CleanupStack::PopAndDestroy(obj);
	return Err;
	}

TInt  Ctsysinfoservicetests::TestN6290()
	{	
    _LIT( KExample, "TestN6290" );
    iLog->Log( KExample );
	TInt Err(PASS);
	
	__UHEAP_MARK;
	CSysInfoService *obj = CSysInfoService::NewL();
	CleanupStack::PushL(obj);

	TInt ExpectedValue[KSize]=
		{
		ETrue, //KCamera
		ETrue, //KMemoryCard
		ETrue, //KFMRadio
		EFalse, //KQwerty
		EFalse, //KWLan
		ETrue, //KUsb
		EFalse, //KPen
		EFalse, //KLED
		EFalse, //KCoverUI	// but supported need to check.
		ETrue, //KSideVolumeKeys
		ETrue, //KVibra
		};
	
	for(TInt i=0;i<KSize;i++)
		{
		CSysData* output=NULL;
		TRAPD(err,obj->GetInfoL(KFeatures,KFeature[i],output));
		if (!err)
			{
			if(!output)
				{
				Err |= FAIL;
				iLog->Log( _L("Output data Set to NULL feature: %s"),KFeature[i].Ptr() );
				}
			else
				{
				CleanupStack::PushL(output);
				if( CSysData::EStatus != output->DataType() )
					{
					iLog->Log( _L("Invalid output data: %s"), KFeature[i].Ptr());
					Err |= FAIL;
					}
				else
					{
					TInt IsSupported = ((CStatus*)output)->Status();
					
					if(IsSupported)
						{
						iLog->Log( _L("Feature %s: Supported"), KFeature[i].Ptr());
						}
					else
						{
						iLog->Log( _L("Feature %s: Not Supported"), KFeature[i].Ptr());
						}
					
					if(ExpectedValue[i] != IsSupported)
						{
						iLog->Log( _L("Incorrect Feature of the device configuration :%s"), KFeature[i].Ptr());
						Err |= FAIL;
						}
					}
				CleanupStack::PopAndDestroy(output);
				}
			}
		else
			{
			Err |= err;
			iLog->Log( _L("GetInfo API returned error: %d"),err );
			}
		}
	CleanupStack::PopAndDestroy(obj);
	return Err;
	}


// -----------------------------------------------------------------------------
// Ctsysinfoservicetests::VibraStatus
// 
// -----------------------------------------------------------------------------
//		
TInt  Ctsysinfoservicetests::VibraStatus(CStifItemParser& /*aItem*/)
	{
	
	int ret=0;
    ret = VibraNotification();
    
    if(ret==0)
			return KErrNone;
		else	
			return KErrGeneral;
		}
// -----------------------------------------------------------------------------
// Ctsysinfoservicetests::PredText
// 
// -----------------------------------------------------------------------------
//
TInt  Ctsysinfoservicetests::PredText(CStifItemParser& /*aItem*/)
	{	int ret=0;
    ret = PredTextNotification();
    
    if(ret==0)
			return KErrNone;
		else	
			return KErrGeneral;
		}
				
// -----------------------------------------------------------------------------
// Ctsysinfoservicetests::InputLang
// 
// -----------------------------------------------------------------------------
//
TInt  Ctsysinfoservicetests::InputLang(CStifItemParser& /*aItem*/)
	{	int ret=0;
    ret = InputLangNotification();
    
    if(ret==0)
			return KErrNone;
		else	
			return KErrGeneral;
		}
				
// -----------------------------------------------------------------------------
// Ctsysinfoservicetests::GetDisplayLang
// 
// -----------------------------------------------------------------------------
//
TInt Ctsysinfoservicetests::GetDisplayLang(CStifItemParser& /*aItem*/)
    {
    CCoeEnv* coeSupported = NULL;
    coeSupported = CCoeEnv::Static();
    if (coeSupported)
        {
        TInt result = KErrNone;
        __UHEAP_MARK;

        _LIT(KExample, "GetDisplayLang:");
        iLog->Log(KExample);

        CSysInfoService* iSysInfoService = CSysInfoService::NewL();

        CleanupStack::PushL(iSysInfoService);

        CSysData* data2 = NULL;

        TRAPD(err, iSysInfoService->GetInfoL(KGeneral, KDisplayLanguage,
                data2));
        if (err != KErrNotFound)
            {
            iLog->Log(_L("Failed,Get Display language found ret err: %d"),
                    err);
            result = KErrGeneral;
            }
        else
            {
            result = KErrNone;
            iLog->Log(_L("Passed Get Display language not found") );
            }

        delete data2;

        CleanupStack::PopAndDestroy(1);
        __UHEAP_MARKEND;

        return result;

        }
    else
        {
        iLog->Log(_L("CCoeEnv not supported . Hence passing the test case") );
        return 0;
        }
    }

// -----------------------------------------------------------------------------
// Ctsysinfoservicetests::SetDisplayLang
// 
// -----------------------------------------------------------------------------
//	
TInt Ctsysinfoservicetests::SetDisplayLang(CStifItemParser& /*aItem*/)
    {
    TInt result = KErrNone;
    __UHEAP_MARK;
    CSysInfoService* iSysInfoService = CSysInfoService::NewL();
    CleanupStack::PushL(iSysInfoService);
    CStatus* data = CStatus::NewL(10);
    CleanupStack::PushL(data);
    TRAPD(err, iSysInfoService->SetInfoL(KGeneral, KDisplayLanguage, data));
    if (err != KErrNotFound)
        {
        iLog->Log(_L("Failed,Set Display language found ret err: %d"), err);
        result = KErrGeneral;
        }
    else
        {
        result = KErrNone;
        iLog->Log(_L("Passed Set Display language not found") );
        }
    CleanupStack::PopAndDestroy(data);

    CCoeEnv* coeSupported = NULL;
    coeSupported = CCoeEnv::Static();
    if (coeSupported)
        {
        CSysData *data1 = NULL;
        TRAPD(err1, iSysInfoService->GetInfoL(KGeneral, KDisplayLanguage,data1));
        if (err1 != KErrNotFound)
            {
            iLog->Log(_L("Failed,Set Display language found ret err: %d"),err);
            result = KErrGeneral;
            }
        else
            {
            result = KErrNone;
            iLog->Log(_L("Passed Set Display language not found") );
            }
        delete data1;
        }
    CleanupStack::PopAndDestroy(1);
    __UHEAP_MARKEND;
    return result;
    }
// -----------------------------------------------------------------------------
// Ctsysinfoservicetests::SetInputLang
// 
// -----------------------------------------------------------------------------
//	
TInt  Ctsysinfoservicetests::SetInputLang(CStifItemParser& /*aItem*/)
	{

	TInt result = KErrNone;
	TInt oldInputLang ,newInputLang;

	__UHEAP_MARK;

	CSysInfoService* iSysInfoService = CSysInfoService::NewL();

	CleanupStack::PushL(iSysInfoService);

	CSysData* data1 = NULL;

	TRAPD(err1,iSysInfoService->GetInfoL(KGeneral,KSupportedLanguages,data1));
	result = err1;
	
	if(err1 == KErrNone)
		{
	
		CSysData* data2 = NULL;

		TRAPD(err2,iSysInfoService->GetInfoL(KGeneral,KInputLanguage,data2));
		oldInputLang = ((CStatus*)data2)->Status();
		
		result = err2;
		if(err2 == KErrNone)
			{
		
			for(TInt i=0;i< ((CLanguageList*)data1)->Count() ;i++)
			{
			((CLanguageList*)data1)->At(i,newInputLang);
			if(newInputLang != oldInputLang)
				{
					break;
				}
			}
			
			CStatus* data3 = CStatus::NewL(newInputLang);

			TRAPD(err3,iSysInfoService->SetInfoL(KGeneral,KInputLanguage,data3));
			TInt	changedInputLang = ((CStatus*)data3)->Status();
			result = err3;
				if(err3 == KErrNone)
				{
				if(newInputLang == changedInputLang)
					{
					result = KErrNone;
					}
				else
					{
					result =  KErrGeneral;

					}
				delete data2;
				delete data3;

				}
			}
		}

	CleanupStack::PopAndDestroy(1);
	delete data1;

	__UHEAP_MARKEND;

	return result;
	
	
	
	}
// -----------------------------------------------------------------------------
// Ctsysinfoservicetests::SupportedLang
// 
// -----------------------------------------------------------------------------
//		
TInt  Ctsysinfoservicetests::SupportedLang(CStifItemParser& /*aItem*/)
	{

	TInt result = KErrNone;
	TInt newDisplayLang;

	__UHEAP_MARK;
	
	_LIT( KExample, "SupportedLang:" );
    iLog->Log( KExample );
    
			 
	CSysInfoService* iSysInfoService = CSysInfoService::NewL();

	CleanupStack::PushL(iSysInfoService);

	CSysData* data1 = NULL;

	TRAPD(err1,iSysInfoService->GetInfoL(KGeneral,KSupportedLanguages,data1));

	if(err1 == KErrNone)
		{
		TInt lang;
		for(TInt i=0;i< ((CLanguageList*)data1)->Count() ;i++)
			{
			((CLanguageList*)data1)->At(i,lang);
			TBuf8<50> buf;
			buf.AppendNum(newDisplayLang);
			iLog->Log(buf);
			}
		}
	else
    	{
    	iLog->Log(_L("Error GetInfo on supported languages: %d"),err1); 
    	}
	
	result = err1;
	CleanupStack::PopAndDestroy(1);
	delete data1;

	__UHEAP_MARKEND;
	
	return result;
	}
// -----------------------------------------------------------------------------
// Ctsysinfoservicetests::AvailableUSBModes
// 
// -----------------------------------------------------------------------------
//		

TInt  Ctsysinfoservicetests::AvailableUSBModes(CStifItemParser& /*aItem*/)
	{
	TInt result = KErrNone;
	TPtrC usbModes;

	#if (!(defined(__WINS__) || defined(__WINSCW__))) 

	__UHEAP_MARK;
	_LIT( KExample, "AvailableUSBModes:" );
    iLog->Log( KExample );
    
	CSysInfoService* iSysInfoService = CSysInfoService::NewL();

	CleanupStack::PushL(iSysInfoService);


	CSysData* data1 = NULL;

	TRAPD(err1,iSysInfoService->GetInfoL(KGeneral,KAvailableUSBModes,data1));

	if(err1 == KErrNone)
		{
			for(TInt i=0;i< ((CStringList*)data1)->Count() ;i++)
				{
				((CStringList*)data1)->At(i,usbModes);
				TBuf<50> buf;
				buf.Copy(usbModes);
				iLog->Log(buf);

				}
		}
	result = err1;
	CleanupStack::PopAndDestroy(1);
	delete data1;
	__UHEAP_MARKEND;
	
	#endif

	return result;
	}
	
// -----------------------------------------------------------------------------
// Ctsysinfoservicetests::ActiveUSBModes
// 
// -----------------------------------------------------------------------------
//	
TInt  Ctsysinfoservicetests::ActiveUSBModes(CStifItemParser& /*aItem*/)
	{
	TInt result = KErrNone;
	TPtrC activeUsbmode;

	#if (!(defined(__WINS__) || defined(__WINSCW__))) 
	__UHEAP_MARK;

	_LIT( KExample, "Active USB Modes:" );
    iLog->Log( KExample );
    
	 
	CSysInfoService* iSysInfoService = CSysInfoService::NewL();

	CleanupStack::PushL(iSysInfoService);

	CSysData* data1 = NULL;
	 
	TRAPD(err1,iSysInfoService->GetInfoL(KGeneral,KActiveUSBMode,data1));

	if(err1 == KErrNone)
		{
				((CStringData*)data1)->StringData(activeUsbmode);
				iLog->Log(_L("active usb mode..............."));
			 	TBuf<50> mode;
			 	mode.Copy(activeUsbmode);
			 	iLog->Log(mode);

			
		}
	CleanupStack::Pop(1);
	result = err1;
	delete data1;
	delete iSysInfoService;

	__UHEAP_MARKEND;
	
	#endif
	return result;
	}
	
	
// -----------------------------------------------------------------------------
// Ctsysinfoservicetests::ConnectedAcc
// 
// -----------------------------------------------------------------------------
//	
	
TInt  Ctsysinfoservicetests::ConnectedAcc(CStifItemParser& /*aItem*/)
	{
	TInt result = 0;
	TPtrC usbModes;
	// On Emulator this is not supported.				
	#if (! (defined(__WINS__) || defined(__WINSCW__)) )

	__UHEAP_MARK;

	_LIT( KExample, "Connected Accessories:" );
    iLog->Log( KExample );
    
	 
	CSysInfoService* iSysInfoService = CSysInfoService::NewL();

	CleanupStack::PushL(iSysInfoService);


	CSysData* data1 = NULL;
	
	const CAccessoryInfo* accInfo= NULL;

	TRAPD(err1,iSysInfoService->GetInfoL(KGeneral,KConnectedAccessories,data1));

	if(err1 == KErrNone)
		{
			for(TInt i=0;i< ((CAccList*)data1)->Count() ;i++)
				{
				((CAccList*)data1)->AtL(i,accInfo);
				TBuf8<50> acctype ;
				TBuf8<50> accConnState;
				acctype.AppendNum(	accInfo->AccessoryType() );
				accConnState.AppendNum(	accInfo->ConnectionState() );
			 	iLog->Log(_L("Accessory Type:"));
				iLog->Log(acctype);

 				iLog->Log(_L("Accessory Connection State:"));
				iLog->Log(accConnState);


				
				}
		}
	result = err1;
	CleanupStack::PopAndDestroy(1);
	delete data1;
	
	__UHEAP_MARKEND;
    #endif
	return result;
	}	
	
// -----------------------------------------------------------------------------
// Ctsysinfoservicetests::VibraNotificationCancel
// 
// -----------------------------------------------------------------------------
//		
TInt  Ctsysinfoservicetests::NotificationCancelVibra(CStifItemParser& /*aItem*/)
	{
	
	int ret=0;
    ret = VibraNotificationCancel();
    
    if(ret==0)
			return KErrNone;
		else	
			return KErrGeneral;
		}	

// -----------------------------------------------------------------------------
// Ctsysinfoservicetests::CameraData
// Positive Test for Core Class
// -----------------------------------------------------------------------------
//
TInt Ctsysinfoservicetests::CameraData(CStifItemParser& /*aItem*/)
   {
    TInt result = 0;
    _LIT( KExample, "CameraData" );
    iLog->Log( KExample );
	
	__UHEAP_MARK;

	CSysInfoService *obj = CSysInfoService::NewL();
	CleanupStack::PushL(obj);
	
	CSysData* output=NULL;
	TRAPD(err,obj->GetInfoL(KCameraInfo,KCameraProperties,output));
	result = err;
	if (result == KErrNone)
		{
		iLog->Log(_L("Got Expected error code %d "),result);
		if(!output)
			{
			iLog->Log( _L("Output data Set to NULL") );
			result = -1;
			}
		else
			{
			CleanupStack::PushL(output);
			iLog->Log( _L("Output data Obtained") );			
			if( CSysData::ECameraInfo != output->DataType() )
				{
				iLog->Log( _L("Invalid output data type") );
				result = -1;
				}
			else
				{
				iLog->Log( _L("Valid output data type - ECameraInfo") );
				const CCameraInfo* camInfoTest = ((CCameraInfo*) output);	
				TInt count = camInfoTest->ResolutionList()->Count();

			    iLog->Log( _L("Count is - %d"),count );
                for(TInt i=0; i<count; i++)
                    {
                    TInt val = 0;
                    TPtrC string;
                    camInfoTest->ResolutionList()->At(i,0,val);
                    iLog->Log( _L("Width %d is - %d"),i+1,val );
                    camInfoTest->ResolutionList()->At(i,1,val);
                    iLog->Log( _L("Height %d is - %d"),i+1,val );
                    camInfoTest->MimeTypesList()->At(i,string);
                    iLog->Log( _L("MimeType %d is %s"),i+1,string.Ptr());
                    }  
                iLog->Log(_L("Test Completed"));
                iLog->Log( _L("PASS"));  
				}//datatype	- ECameraInfo	
			CleanupStack::PopAndDestroy(output);
			}//output		
		}//err
	else
		{
		iLog->Log( _L("GetInfo API for Camera returned error %d"),result );
        iLog->Log(_L("Test Completed"));
        iLog->Log( _L("FAIL"));   
		}	
	
	CleanupStack::PopAndDestroy(obj);
	__UHEAP_MARKEND;
	return result;    
    }	

// -----------------------------------------------------------------------------
// Ctsysinfoservicetests::CameraDataNegativeEntity
// negative test case for core class - Wrong Entity
// -----------------------------------------------------------------------------
//
TInt Ctsysinfoservicetests::CameraDataNegativeEntity(CStifItemParser& /*aItem*/)
   {
    TInt result;
    TInt expectedError = KErrNotFound;
    _LIT( KExample, "CameraDataNegativeEntity" );
    iLog->Log( KExample );
    
    _LIT( KCameraEntity, "CameraEntity" );
    __UHEAP_MARK;

    CSysInfoService *obj = CSysInfoService::NewL();
    CleanupStack::PushL(obj);
    
    CSysData* output=NULL; 
    TRAPD(err,obj->GetInfoL(KCameraEntity,KCameraProperties,output));
    result = err;
    if (result == expectedError)
        {
        iLog->Log(_L("Got Expected error code %d "),result);
        result = KErrNone;
        iLog->Log(_L("Test Completed"));
        iLog->Log( _L("PASS"));   
        }//err
    else
        {
        iLog->Log( _L("GetInfo API for Camera returned unexpected error") );
        iLog->Log(_L("Test Completed"));
        iLog->Log( _L("FAIL"));  
        }    
    
    CleanupStack::PopAndDestroy(obj);
    __UHEAP_MARKEND;
    return result;    
    }   

// -----------------------------------------------------------------------------
// Ctsysinfoservicetests::CameraDataNegativeKey
// negative test case for core class - Wrong Key
// -----------------------------------------------------------------------------
//
TInt Ctsysinfoservicetests::CameraDataNegativeKey(CStifItemParser& /*aItem*/)
   {
    TInt result;
    TInt expectedError = KErrNotFound;
    _LIT( KExample, "CameraDataNegativeKey" );
    iLog->Log( KExample );
    
    _LIT( KCameraKey, "CameraKey" );
    __UHEAP_MARK;

    CSysInfoService *obj = CSysInfoService::NewL();
    CleanupStack::PushL(obj);
    
    CSysData* output=NULL;
    TRAPD(err,obj->GetInfoL(KCameraInfo,KCameraKey,output));
    result = err;
    if (result == expectedError)
        {
        iLog->Log(_L("Got Expected error code %d "),result);
        result = KErrNone;
        iLog->Log(_L("Test Completed"));
        iLog->Log( _L("PASS"));  
        }//err
    else
        {
        iLog->Log( _L("GetInfo API for Camera returned unexpected error") );
        iLog->Log(_L("Test Completed"));
        iLog->Log( _L("FAIL"));   
        }    
    
    CleanupStack::PopAndDestroy(obj);
    __UHEAP_MARKEND;
    return result;    
    }  

		
TInt  Ctsysinfoservicetests::ConnBluetooth(CStifItemParser& /*aItem*/)
	{	int ret=0;
    ret = ReqNotification(0, NULL);
    
    if(ret==0)
			return KErrNone;
		else	
			return KErrGeneral;
		}
		
TInt  Ctsysinfoservicetests::IRStatus(CStifItemParser& /*aItem*/)
	{	int ret=0;
    ret = IRNotification(0, NULL);
    
    if(ret==0)
			return KErrNone;
		else	
			return KErrGeneral;
		}

TInt  Ctsysinfoservicetests::GetActiveConnections(CStifItemParser& /*aItem*/)
	{
	_LIT( KExample, "GetActiveConnections" );
    iLog->Log( KExample );
    
	int ret=0;
    ret = ActiveConnection(iLog);
    
    if(ret==0)
			return KErrNone;
		else	
			return KErrGeneral;
		}
				

TInt  Ctsysinfoservicetests::GetWlanMacAddress(CStifItemParser& /*aItem*/)
	{
	int ret=0;

	#if (!(defined(__WINS__) || defined(__WINSCW__))) 
	TInt Err(PASS);

	_LIT( KExample, "GetWlanMacAddress" );
    iLog->Log( KExample );
    TPtrC wlanAddress;
    
	CSysInfoService* iSysInfoService = CSysInfoService::NewL();

	CleanupStack::PushL(iSysInfoService);
	CSysData* data2 = NULL;

	TRAPD(err1,iSysInfoService->GetInfoL(KFeatures,KWLan,data2));
	if (!err1)
			{
			if(!data2)
				{
				Err |= FAIL;
				iLog->Log( _L("Output data Set to NULL feature: %s"),KWLan );
				}
			else
				{
				CleanupStack::PushL(data2);
				if( CSysData::EStatus != data2->DataType() )
					{
					iLog->Log( _L("Invalid output data: %s"), KWLan);
					Err |= FAIL;
					}
				else
					{
					TInt IsSupported = ((CStatus*)data2)->Status();
					
					if(IsSupported)
						{
						CSysData* data1 = NULL;

						TRAPD(err1,iSysInfoService->GetInfoL(KConnectivity,KWLanMacAddress,data1));
						ret = err1;	
						if(err1 == KErrNone)
							{
							((CStringData*)data1)->StringData(wlanAddress);

							iLog->Log(_L("WlanMacAddress:"));
							TBuf8<50> buf;
							buf.Copy(wlanAddress);
							iLog->Log(buf);

							}
						else
							{
							iLog->Log(_L("Error reading: %d"),err1);
							}
						delete data1;
						}
					}
				CleanupStack::Pop(1);
				}
			}
	delete data2;
	CleanupStack::PopAndDestroy(1);

	#endif
	return ret;

	}


TInt  Ctsysinfoservicetests::GetActiveConnectionsCancel(CStifItemParser& /*aItem*/)
	{
	
	_LIT( KExample, "ConnNotification" );
    iLog->Log( KExample );
    
    int ret=0;
    ret = GetActiveConnReqCancel();
    
    if(ret==0)
			return KErrNone;
		else	
			return KErrGeneral;
		}
						

	
