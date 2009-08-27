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
#include <f32file.h>
#include <hal.h>
#include <liwcommon.h>
#include <LiwServiceHandler.h>
#include <COEMAIN.H> 

#include "tsysinfoprovidertests.h"
#include "entitykeys.h"
#include "sysinfoaiwparams.hrh"
#include "tuseractivitynotifier.h"
#include "tautolocknotifier.h"
#include "serviceerrno.h"

using namespace LIW ;
using namespace SysInfo;
using namespace sysinfoaiwparams;

_LIT(KROMInstallDir,"\\system\\install\\");
_LIT(KS60ProductIdFile,"Series60v*.sis");

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctsysinfoprovidertests::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void Ctsysinfoprovidertests::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// Ctsysinfoprovidertests::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt Ctsysinfoprovidertests::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
      	ENTRY( "FirmwareVersion",		Ctsysinfoprovidertests::FirmwareVersionL),
		ENTRY( "PlatformVersion",    	Ctsysinfoprovidertests::PlatformVersionL),
//		ENTRY( "SymbianOSversion",  	Ctsysinfoprovidertests::SymbianOSVersionL),
		ENTRY( "MachineID",  			Ctsysinfoprovidertests::MachineIDL),
		ENTRY( "ProductType",  			Ctsysinfoprovidertests::ProductTypeL),
		ENTRY( "Manufacturer", 			Ctsysinfoprovidertests::ManufacturerL),
		ENTRY( "PhoneModel", 			Ctsysinfoprovidertests::PhoneModelL),
		ENTRY( "IMEINumber", 			Ctsysinfoprovidertests::IMEINumberL),

        ENTRY( "GetSetBrightness",		Ctsysinfoprovidertests::GetSetBrightnessL),
		ENTRY( "GetSetScreensaverTimeOut",	Ctsysinfoprovidertests::GetSetScreensaverTimeOutL),
		ENTRY( "UserInactivityNotifier",  Ctsysinfoprovidertests::UserInactivityNotifierL),
		ENTRY( "SetGetAutoLockTime",  		Ctsysinfoprovidertests::SetGetAutoLockTimeL),
		ENTRY( "AutoLockNotifier",  	Ctsysinfoprovidertests::AutoLockNotifierL),
		ENTRY( "DisplayResolution",  	Ctsysinfoprovidertests::DisplayResolutionL),
		ENTRY( "GetSetLightTimeOut",	Ctsysinfoprovidertests::GetSetLightTimeOutL),		
		ENTRY( "GetSetWallPaper",		Ctsysinfoprovidertests::GetSetWallPaperL),		
		ENTRY( "GetSetKeyGaurdTime",	Ctsysinfoprovidertests::GetSetKeyGaurdL),	
		ENTRY( "DisplayOrientation",	Ctsysinfoprovidertests::DisplayOrientationL),

        ENTRY( "GetListofDrives",		Ctsysinfoprovidertests::GetListofDrivesL),
		ENTRY( "GetDriveInfo",    		Ctsysinfoprovidertests::GetDriveInfoL),
		ENTRY( "GetDriveInfoNegTest",    		Ctsysinfoprovidertests::GetDriveInfoNegTestL),
		
		ENTRY( "VibraStatus",    Ctsysinfoprovidertests::VibraStatus),
        ENTRY( "SetDisplayLang",    Ctsysinfoprovidertests::SetDisplayLang),
        ENTRY( "SetInputLang",    Ctsysinfoprovidertests::SetInputLang),

        ENTRY( "SupportedLang",    Ctsysinfoprovidertests::SupportedLang),
        ENTRY( "AvailableUSBModes",    Ctsysinfoprovidertests::AvailableUSBModes),
        
        ENTRY( "ConnBluetooth",    Ctsysinfoprovidertests::ConnBluetooth),
        ENTRY( "GetActiveConnections",    Ctsysinfoprovidertests::GetActiveConnections),
        ENTRY( "BTAsyncRequestCancel",    Ctsysinfoprovidertests::BTAsyncRequestCancel),
        ENTRY( "GetActiveConnectionsReqCancel",    Ctsysinfoprovidertests::GetActiveConnectionsReqCancel),
        ENTRY("GetCameraInfo",  Ctsysinfoprovidertests::GetCameraInfoTest), // During CJSE 2.0


        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

TInt  Ctsysinfoprovidertests::GetListofDrivesL(CStifItemParser& /*aItem*/)
	{	
    _LIT( KExample, "GetListofDrivesL" );
    iLog->Log( KExample );
	TInt RetVal(PASS);
	TInt32 Err;
		
	__UHEAP_MARK;		

	CLiwServiceHandler* ServiceHandler;
	CLiwGenericParamList* InParamList,*OutParamList;
	MLiwInterface* Interface;
	
	CreateInterfaceL(ServiceHandler,Interface);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*Interface);

    InParamList = &(ServiceHandler->InParamListL());
    OutParamList = &(ServiceHandler->OutParamListL());

	InParamList->Reset();
	OutParamList->Reset();

//	Get List of drives
//-------------------------------------------------------------------------
	InParamList->AppendL(TLiwGenericParam(KEntity,TLiwVariant(KMemory)));
	InParamList->AppendL(TLiwGenericParam(KKey,TLiwVariant(KListDrives)));

	Interface->ExecuteCmdL(KGetInfo,*InParamList,*OutParamList);

	RetVal |= CheckErrorCode(*OutParamList,Err);
	if ( Err )
		{
		iLog->Log( _L("GetInfo retured error : %d"),Err );
		User::Leave(Err);
		} 
	
	TInt index=0;
	const TLiwGenericParam* ret_val = OutParamList->FindFirst(index,KReturnValue);
	if(!ret_val)
		{
		iLog->Log( _L("Return value parameter not found"));
		User::Leave(FAIL);
		}
	else
		{
		const CLiwMap* outmap = ret_val->Value().AsMap();
		const CLiwList* drvlist;
		TLiwVariant variant_drvlist;
		
		if( outmap->FindL(KDriveList,variant_drvlist) )
			drvlist = variant_drvlist.AsList();
		
		TInt count = drvlist->Count();
		
		if(count<=0)
			{
			iLog->Log( _L("Drives not found") );
			Err |= FAIL;
			}
		iLog->Log( _L("---------------------------------------------"));
		for(TInt i(0); i<count; i++)
			{
			TLiwVariant drive;
			drvlist->AtL(i,drive);
			TPtrC drivepath;
			drive.Get(drivepath);
			
			iLog->Log( _L("Drive number: %s"),drivepath.Ptr());
			drive.Reset();
			}
		iLog->Log( _L("---------------------------------------------"));
		((CLiwList*)drvlist)->DecRef();
		((CLiwMap*)outmap)->DecRef();
		}

//-------------------------------------------------------------------------		
	
	InParamList->Reset();
	OutParamList->Reset();	
		
	CleanupStack::PopAndDestroy(2,ServiceHandler);
	
	__UHEAP_MARKEND;

	return RetVal;
	}

TInt  Ctsysinfoprovidertests::GetDriveInfoL(CStifItemParser& /*aItem*/)
	{	
    _LIT( KExample, "GetDriveInfoL" );
    iLog->Log( KExample );
	TInt RetVal(PASS);
	TInt32 Err;
	
	__UHEAP_MARK;

	CLiwServiceHandler* ServiceHandler;
	CLiwGenericParamList* InParamList,*OutParamList;
	MLiwInterface* Interface;
	
	CreateInterfaceL(ServiceHandler,Interface);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*Interface);

    InParamList = &(ServiceHandler->InParamListL());
    OutParamList = &(ServiceHandler->OutParamListL());

	InParamList->Reset();
	OutParamList->Reset();

	CLiwMap* inputmap = CLiwDefaultMap::NewL();


//	Get List of drives
//-------------------------------------------------------------------------
	InParamList->AppendL(TLiwGenericParam(KEntity,TLiwVariant(KMemory)));
	InParamList->AppendL(TLiwGenericParam(KKey,TLiwVariant(KListDrives)));

	Interface->ExecuteCmdL(KGetInfo,*InParamList,*OutParamList);

	RetVal |= CheckErrorCode(*OutParamList,Err);
	if ( Err )
		{
		iLog->Log( _L("GetInfo retured error : %d"),Err );
		User::Leave(Err);
		} 
	
	TInt index=0;
	const TLiwGenericParam* ret_val = OutParamList->FindFirst(index,KReturnValue);
	if(!ret_val)
		{
		iLog->Log( _L("Return value parameter not found"));
		User::Leave(FAIL);
		}
	else
		{
		const CLiwMap* outmap = ret_val->Value().AsMap();
		const CLiwList* drvlist;
		TLiwVariant variant_drvlist;
		
		if( outmap->FindL(KDriveList,variant_drvlist) )
			drvlist = variant_drvlist.AsList();
		
		TInt count = drvlist->Count();
		
		if(count<=0)
			{
			iLog->Log( _L("Drives not found") );
			Err |= FAIL;
			}

		for(TInt i(0); i<count; i++)
			{
			TLiwVariant drive;
			drvlist->AtL(i,drive);
			TPtrC driveno;
			drive.Get(driveno);

			inputmap->Remove(KDriveNo);
			InParamList->Reset();
			OutParamList->Reset();			

			//	Get DriveInfo
			//-------------------------------------------------------------------------
				inputmap->InsertL(KDriveNo,driveno);

				InParamList->AppendL(TLiwGenericParam(KEntity,TLiwVariant(KMemory)));
				InParamList->AppendL(TLiwGenericParam(KKey,TLiwVariant(KDriveInfo)));
				InParamList->AppendL(TLiwGenericParam(KSysData,TLiwVariant(inputmap)));

				Interface->ExecuteCmdL(KGetInfo,*InParamList,*OutParamList);

				RetVal |= CheckErrorCode(*OutParamList,Err);
				if ( Err )
					{
					if( Err == SErrServiceNotReady && !driveno.CompareF(_L("E:\\")))
						{
						iLog->Log( _L("Memory card not present : %d"),Err );
						Err = 0;
						continue;
						}
					iLog->Log( _L("GetInfo retured error : %d"),Err );
					User::Leave(Err);
					} 
				
				TInt index=0;
				const TLiwGenericParam* ret_val = OutParamList->FindFirst(index,KReturnValue);
				if(!ret_val)
					{
					iLog->Log( _L("Return value parameter not found"));
					User::Leave(FAIL);
					}
				else
					{
					const CLiwMap* outmap = ret_val->Value().AsMap();
					iLog->Log( _L("-------------------------------") );	
					iLog->Log( _L("Drive : %s"), driveno.Ptr());
					TRAPD(error,ProcessDriveInfoL(outmap));
					iLog->Log( _L("-------------------------------") );	
					Err |= error;
					((CLiwMap*)outmap)->DecRef();
					}
			drive.Reset();
			//-------------------------------------------------------------------------
			}

		((CLiwList*)drvlist)->DecRef();
		((CLiwMap*)outmap)->DecRef();
		}

	inputmap->DecRef();

	InParamList->Reset();
	OutParamList->Reset();	
	iLog->Log( _L("Test completed Err: %d"),Err );	
	CleanupStack::PopAndDestroy(2,ServiceHandler);
	
	__UHEAP_MARKEND;
	return Err;
	}

TInt  Ctsysinfoprovidertests::GetDriveInfoNegTestL(CStifItemParser& /*aItem*/)
	{	
    _LIT( KExample, "GetDriveInfoL" );
    iLog->Log( KExample );
	TInt RetVal(PASS);
	TInt32 Err;
	
	__UHEAP_MARK;

	CLiwServiceHandler* ServiceHandler;
	CLiwGenericParamList* InParamList,*OutParamList;
	MLiwInterface* Interface;
	
	CreateInterfaceL(ServiceHandler,Interface);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*Interface);

    InParamList = &(ServiceHandler->InParamListL());
    OutParamList = &(ServiceHandler->OutParamListL());

	InParamList->Reset();
	OutParamList->Reset();

	CLiwMap* inputmap = CLiwDefaultMap::NewL();
	_LIT(KInvalidDrive1,"!:\\");
	_LIT(KInvalidDrive2,"C\\");
	_LIT(KInvalidDrive3,"SFAC:\\");

	inputmap->InsertL(KDriveNo,KInvalidDrive1());

//	Get DriveInfo
//-------------------------------------------------------------------------
	InParamList->AppendL(TLiwGenericParam(KEntity,TLiwVariant(KMemory)));
	InParamList->AppendL(TLiwGenericParam(KKey,TLiwVariant(KListDrives)));
	InParamList->AppendL(TLiwGenericParam(KSysData,TLiwVariant(inputmap)));

	Interface->ExecuteCmdL(KGetInfo,*InParamList,*OutParamList);

	RetVal |= CheckErrorCode(*OutParamList,Err);
	if ( Err != SErrBadArgumentType)
		{
		iLog->Log( _L("GetInfo on drive : %s retured error : %d expected error: %d"),KInvalidDrive1().Ptr(),Err,SErrBadArgumentType );
		User::Leave(Err);
		}
	Err = PASS;

	inputmap->Remove(KDriveNo);
	inputmap->InsertL(KDriveNo,KInvalidDrive2());
	InParamList->AppendL(TLiwGenericParam(KSysData,TLiwVariant(inputmap)));

	Interface->ExecuteCmdL(KGetInfo,*InParamList,*OutParamList);

	RetVal |= CheckErrorCode(*OutParamList,Err);
	if ( Err != SErrBadArgumentType)
		{
		iLog->Log( _L("GetInfo on drive : %s retured error : %d expected error: %d"),KInvalidDrive2().Ptr(),Err,SErrBadArgumentType );
		User::Leave(Err);
		}
	Err = PASS;

	inputmap->Remove(KDriveNo);
	InParamList->AppendL(TLiwGenericParam(KSysData,TLiwVariant(inputmap)));

	Interface->ExecuteCmdL(KGetInfo,*InParamList,*OutParamList);

	RetVal |= CheckErrorCode(*OutParamList,Err);
	if ( Err != SErrBadArgumentType)
		{
		iLog->Log( _L("GetInfo on drive : %s retured error : %d expected error: %d"),KInvalidDrive3().Ptr(),Err,SErrBadArgumentType );
		User::Leave(Err);
		}
	Err = PASS;

	inputmap->Remove(KDriveNo);
	inputmap->InsertL(KDriveNo,KInvalidDrive3());
	InParamList->AppendL(TLiwGenericParam(KSysData,TLiwVariant(inputmap)));

	Interface->ExecuteCmdL(KGetInfo,*InParamList,*OutParamList);

	RetVal |= CheckErrorCode(*OutParamList,Err);
	if ( Err != SErrBadArgumentType)
		{
		iLog->Log( _L("GetInfo on drive : %s retured error : %d expected error: %d"),KInvalidDrive1().Ptr(),Err,SErrBadArgumentType );
		User::Leave(Err);
		}
	Err = PASS;

	inputmap->DecRef();
	
	InParamList->Reset();
	OutParamList->Reset();	
	iLog->Log( _L("Test completed Err: %d"),Err );
	CleanupStack::PopAndDestroy(2,ServiceHandler);
	
	__UHEAP_MARKEND;
	return Err;
	}


TInt  Ctsysinfoprovidertests::FirmwareVersionL(CStifItemParser& /*aItem*/)
	{	
    _LIT( KExample, "FirmwareVersionL" );
    iLog->Log( KExample );
	TInt RetVal(PASS);
	TInt32 Err;
		
	__UHEAP_MARK;		

	CLiwServiceHandler* ServiceHandler;
	CLiwGenericParamList* InParamList,*OutParamList;
	MLiwInterface* Interface;
	
	CreateInterfaceL(ServiceHandler,Interface);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*Interface);

    InParamList = &(ServiceHandler->InParamListL());
    OutParamList = &(ServiceHandler->OutParamListL());

	InParamList->Reset();
	OutParamList->Reset();
	
	InParamList->AppendL(TLiwGenericParam(KEntity,TLiwVariant(KDevice)));
	InParamList->AppendL(TLiwGenericParam(KKey,TLiwVariant(KFirmwareVersion)));

	Interface->ExecuteCmdL(KGetInfo,*InParamList,*OutParamList);

	RetVal |= CheckErrorCode(*OutParamList,Err);
	if ( Err )
		{
		iLog->Log( _L("GetInfo retured error : %d"),Err );
		RetVal |= FAIL;
		} 
	
	TInt index=0;
	const TLiwGenericParam* ret_val = OutParamList->FindFirst(index,KReturnValue);
	if(!ret_val)
		{
		iLog->Log( _L("Return value parameter not found"));
		RetVal |= FAIL;
		}
	else
		{
		const CLiwMap* outmap = ret_val->Value().AsMap();
		TLiwVariant firmwareversion;
		outmap->FindL(KStringData,firmwareversion);
		TPtrC version(firmwareversion.AsDes());
		iLog->Log( _L("firmware version: %s"),version.Ptr());
		firmwareversion.Reset();
		((CLiwMap*)outmap)->DecRef();
		}
	
	InParamList->Reset();
	OutParamList->Reset();	
		
	CleanupStack::PopAndDestroy(2,ServiceHandler);
	
	__UHEAP_MARKEND;

	return RetVal;
	}
/*
TInt  Ctsysinfoprovidertests::SymbianOSVersionL(CStifItemParser& aItem)
	{	
    _LIT( KExample, "SymbianOSVersionL" );
    iLog->Log( KExample );
	TInt RetVal(PASS);
	TInt32 Err;
	
	__UHEAP_MARK;

	CLiwServiceHandler* ServiceHandler;
	CLiwGenericParamList* InParamList,*OutParamList;
	MLiwInterface* Interface;
	
	CreateInterfaceL(ServiceHandler,Interface);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*Interface);

    InParamList = &(ServiceHandler->InParamListL());
    OutParamList = &(ServiceHandler->OutParamListL());

	InParamList->Reset();
	OutParamList->Reset();
	
	InParamList->AppendL(TLiwGenericParam(KEntity,TLiwVariant(KDevice)));
	InParamList->AppendL(TLiwGenericParam(KKey,TLiwVariant(KSymbianOsVersion)));

	Interface->ExecuteCmdL(KGetInfo,*InParamList,*OutParamList);

	RetVal |= CheckErrorCode(*OutParamList,Err);
	if ( Err )
		{
		iLog->Log( _L("GetInfo retured error : %d"),Err );
		RetVal |= FAIL;
		} 
	
	TInt index=0;
	const TLiwGenericParam* ret_val = OutParamList->FindFirst(index,KReturnValue);
	if(!ret_val)
		{
		iLog->Log( _L("Return value parameter not found"));
		RetVal |= FAIL;
		}
	else
		{
		const CLiwMap* outmap = ret_val->Value().AsMap();
		TLiwVariant majorver;
		TLiwVariant minorver;
		if( !outmap->FindL(KMajorVersion,majorver) )
			{
			iLog->Log( _L("Major Version not found"));
			RetVal |= FAIL;
			}
		
		if( !outmap->FindL(KMinorVersion,minorver) )
			{
			iLog->Log( _L("Minor Version not found"));
			RetVal |= FAIL;
			}

		if( (majorver.AsDes().Length()<=0) || (minorver.AsDes().Length()<=0) )
			{
			iLog->Log( _L("Emulator returned invalid major minor versions..") );
			Err |= FAIL;
			}

		iLog->Log( _L("OS version: "));
		iLog->Log( _L("Major version: %s"),majorver.AsDes().Ptr());
		iLog->Log( _L("Minor version: %s"),minorver.AsDes().Ptr());
		majorver.Reset();
		minorver.Reset();
		((CLiwMap*)outmap)->DecRef();
		}
	
	InParamList->Reset();
	OutParamList->Reset();	
		
	CleanupStack::PopAndDestroy(2,ServiceHandler);
	
	__UHEAP_MARKEND;
	return Err;
	}
*/
TInt  Ctsysinfoprovidertests::PlatformVersionL(CStifItemParser& /*aItem*/)
	{	
    _LIT( KExample, "PlatformVersionL" );
    iLog->Log( KExample );
	TInt RetVal(PASS);
	TInt32 Err;
	
	__UHEAP_MARK;

	CLiwServiceHandler* ServiceHandler;
	CLiwGenericParamList* InParamList,*OutParamList;
	MLiwInterface* Interface;
	
	CreateInterfaceL(ServiceHandler,Interface);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*Interface);

    InParamList = &(ServiceHandler->InParamListL());
    OutParamList = &(ServiceHandler->OutParamListL());

	InParamList->Reset();
	OutParamList->Reset();
	
	InParamList->AppendL(TLiwGenericParam(KEntity,TLiwVariant(KDevice)));
	InParamList->AppendL(TLiwGenericParam(KKey,TLiwVariant(KPlatformVersion)));

	Interface->ExecuteCmdL(KGetInfo,*InParamList,*OutParamList);

	RetVal |= CheckErrorCode(*OutParamList,Err);
	if ( Err )
		{
		iLog->Log( _L("GetInfo retured error : %d"),Err );
		RetVal |= FAIL;
		} 
	
	TInt index=0;
	const TLiwGenericParam* ret_val = OutParamList->FindFirst(index,KReturnValue);
	if(!ret_val)
		{
		iLog->Log( _L("Return value parameter not found"));
		RetVal |= FAIL;
		}
	else
		{
		const CLiwMap* outmap = ret_val->Value().AsMap();
		TLiwVariant majorver;
		TLiwVariant minorver;
		if( !outmap->FindL(KMajorVersion,majorver) )
			{
			iLog->Log( _L("Major Version not found"));
			RetVal |= FAIL;
			}
		
		if( !outmap->FindL(KMinorVersion,minorver) )
			{
			iLog->Log( _L("Minor Version not found"));
			RetVal |= FAIL;
			}

		if( (majorver.AsDes().Length()<=0) || (minorver.AsDes().Length()<=0) )
			{
			iLog->Log( _L("Emulator returned invalid major minor versions..") );
			Err |= FAIL;
			}

		iLog->Log( _L("Platform version: "));
		iLog->Log( _L("Major version: %s"),majorver.AsDes().Ptr());
		iLog->Log( _L("Minor version: %s"),minorver.AsDes().Ptr());
		majorver.Reset();
		minorver.Reset();
		((CLiwMap*)outmap)->DecRef();
		}
	
	InParamList->Reset();
	OutParamList->Reset();	
		
	CleanupStack::PopAndDestroy(2,ServiceHandler);
	
	__UHEAP_MARKEND;
	return Err;
	}

TInt  Ctsysinfoprovidertests::ProductTypeL(CStifItemParser& /*aItem*/)
	{	
    _LIT( KExample, "ProductTypeL" );
    iLog->Log( KExample );
	TInt RetVal(PASS);
	TInt32 Err;
	
	__UHEAP_MARK;

	CLiwServiceHandler* ServiceHandler;
	CLiwGenericParamList* InParamList,*OutParamList;
	MLiwInterface* Interface;
	
	CreateInterfaceL(ServiceHandler,Interface);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*Interface);

    InParamList = &(ServiceHandler->InParamListL());
    OutParamList = &(ServiceHandler->OutParamListL());

	InParamList->Reset();
	OutParamList->Reset();
	
	InParamList->AppendL(TLiwGenericParam(KEntity,TLiwVariant(KDevice)));
	InParamList->AppendL(TLiwGenericParam(KKey,TLiwVariant(KProductType)));

	Interface->ExecuteCmdL(KGetInfo,*InParamList,*OutParamList);

	RetVal |= CheckErrorCode(*OutParamList,Err);
	if ( Err )
		{
		iLog->Log( _L("GetInfo retured error : %d"),Err );
		RetVal |= FAIL;
		} 
	
	TInt index=0;
	const TLiwGenericParam* ret_val = OutParamList->FindFirst(index,KReturnValue);
	if(!ret_val)
		{
		iLog->Log( _L("Return value parameter not found"));
		RetVal |= FAIL;
		}
	else
		{
		const CLiwMap* outmap = ret_val->Value().AsMap();
		TLiwVariant producttype;
		if( !outmap->FindL(KStringData,producttype) )
			{
			iLog->Log( _L("Product Type not found"));
			RetVal |= FAIL;
			}
		
#if ( !((defined(__WINS__) || defined(__WINSCW__))) )
			iLog->Log( _L("Product Type : %s"),producttype.AsDes().Ptr());

			if(!(producttype.AsDes().Length() > 2))
				{
				iLog->Log( _L("Invalid producttype") );
				Err |= FAIL;					
				}
#endif
		iLog->Log( _L("Product Type: %s"),producttype.AsDes().Ptr());
		
		producttype.Reset();
		((CLiwMap*)outmap)->DecRef();
		}
	
	InParamList->Reset();
	OutParamList->Reset();	
		
	CleanupStack::PopAndDestroy(2,ServiceHandler);
	
	__UHEAP_MARKEND;
	return Err;
	}	

TInt  Ctsysinfoprovidertests::MachineIDL(CStifItemParser& /*aItem*/)
	{	
    _LIT( KExample, "MachineIDL" );
    iLog->Log( KExample );
	TInt RetVal(PASS);
	TInt32 Err;
	
	__UHEAP_MARK;

	CLiwServiceHandler* ServiceHandler;
	CLiwGenericParamList* InParamList,*OutParamList;
	MLiwInterface* Interface;
	
	CreateInterfaceL(ServiceHandler,Interface);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*Interface);

    InParamList = &(ServiceHandler->InParamListL());
    OutParamList = &(ServiceHandler->OutParamListL());

	InParamList->Reset();
	OutParamList->Reset();
	
	InParamList->AppendL(TLiwGenericParam(KEntity,TLiwVariant(KDevice)));
	InParamList->AppendL(TLiwGenericParam(KKey,TLiwVariant(KMachineID)));

	Interface->ExecuteCmdL(KGetInfo,*InParamList,*OutParamList);

	RetVal |= CheckErrorCode(*OutParamList,Err);
	if ( Err )
		{
		iLog->Log( _L("GetInfo retured error : %d"),Err );
		RetVal |= FAIL;
		} 
	
	TInt index=0;
	const TLiwGenericParam* ret_val = OutParamList->FindFirst(index,KReturnValue);
	if(!ret_val)
		{
		iLog->Log( _L("Return value parameter not found"));
		RetVal |= FAIL;
		}
	else
		{
		const CLiwMap* outmap = ret_val->Value().AsMap();
		TLiwVariant machineid;
		if( !outmap->FindL(KStatus,machineid) )
			{
			iLog->Log( _L("Machine ID not found"));
			RetVal |= FAIL;
			}

		iLog->Log( _L("Machine ID : %x"),machineid.AsTInt32());

		TInt ExpectedMachineId;
		HAL::Get(HALData::EMachineUid, ExpectedMachineId);
		if(!(ExpectedMachineId == machineid.AsTInt32()))
			{
			iLog->Log( _L("Incorrect Machine ID") );
			Err |= FAIL;					
			}
		((CLiwMap*)outmap)->DecRef();
		}
	
	InParamList->Reset();
	OutParamList->Reset();	
		
	CleanupStack::PopAndDestroy(2,ServiceHandler);
	
	__UHEAP_MARKEND;
	return Err;
	}	


TInt  Ctsysinfoprovidertests::ManufacturerL(CStifItemParser& /*aItem*/)
	{	
    _LIT( KExample, "ManufacturerL" );
    iLog->Log( KExample );
	TInt RetVal(PASS);
	TInt32 Err;
	
	__UHEAP_MARK;

	CLiwServiceHandler* ServiceHandler;
	CLiwGenericParamList* InParamList,*OutParamList;
	MLiwInterface* Interface;
	
	CreateInterfaceL(ServiceHandler,Interface);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*Interface);

    InParamList = &(ServiceHandler->InParamListL());
    OutParamList = &(ServiceHandler->OutParamListL());

	InParamList->Reset();
	OutParamList->Reset();
	
	InParamList->AppendL(TLiwGenericParam(KEntity,TLiwVariant(KDevice)));
	InParamList->AppendL(TLiwGenericParam(KKey,TLiwVariant(KManufacturer)));

	Interface->ExecuteCmdL(KGetInfo,*InParamList,*OutParamList);

	RetVal |= CheckErrorCode(*OutParamList,Err);
	if ( Err )
		{
		iLog->Log( _L("GetInfo retured error : %d"),Err );
		RetVal |= FAIL;
		} 
	
	TInt index=0;
	const TLiwGenericParam* ret_val = OutParamList->FindFirst(index,KReturnValue);
	if(!ret_val)
		{
		iLog->Log( _L("Return value parameter not found"));
		RetVal |= FAIL;
		}
	else
		{
		const CLiwMap* outmap = ret_val->Value().AsMap();
		TLiwVariant manufacturer;
		if( !outmap->FindL(KStringData,manufacturer) )
			{
			iLog->Log( _L("Manufacturer not found"));
			RetVal |= FAIL;
			}

		iLog->Log( _L("Manufacturer : %s"),manufacturer.AsDes().Ptr());
		TBuf<50> manufc;
		manufc.Copy(manufacturer.AsDes());
		manufc.UpperCase();
		if((manufc.Compare(_L("NOKIA"))))
			{
			iLog->Log( _L("Incorrect Manufacturer") );
			Err |= FAIL;					
			}
		((CLiwMap*)outmap)->DecRef();
		manufacturer.Reset();
		}
	
	InParamList->Reset();
	OutParamList->Reset();	
		
	CleanupStack::PopAndDestroy(2,ServiceHandler);
	
	__UHEAP_MARKEND;
	return Err;
	}	

TInt  Ctsysinfoprovidertests::PhoneModelL(CStifItemParser& /*aItem*/)
	{	
    _LIT( KExample, "PhoneModelL" );
    iLog->Log( KExample );
	TInt RetVal(PASS);
	TInt32 Err;
	
	__UHEAP_MARK;

	CLiwServiceHandler* ServiceHandler;
	CLiwGenericParamList* InParamList,*OutParamList;
	MLiwInterface* Interface;
	
	CreateInterfaceL(ServiceHandler,Interface);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*Interface);

    InParamList = &(ServiceHandler->InParamListL());
    OutParamList = &(ServiceHandler->OutParamListL());

	InParamList->Reset();
	OutParamList->Reset();
	
	InParamList->AppendL(TLiwGenericParam(KEntity,TLiwVariant(KDevice)));
	InParamList->AppendL(TLiwGenericParam(KKey,TLiwVariant(KPhoneModel)));

	Interface->ExecuteCmdL(KGetInfo,*InParamList,*OutParamList);

	RetVal |= CheckErrorCode(*OutParamList,Err);
	if ( Err )
		{
		iLog->Log( _L("GetInfo retured error : %d"),Err );
		RetVal |= FAIL;
		} 
	
	TInt index=0;
	const TLiwGenericParam* ret_val = OutParamList->FindFirst(index,KReturnValue);
	if(!ret_val)
		{
		iLog->Log( _L("Return value parameter not found"));
		RetVal |= FAIL;
		}
	else
		{
		const CLiwMap* outmap = ret_val->Value().AsMap();
		TLiwVariant phonemodel;
		if( !outmap->FindL(KStringData,phonemodel) )
			{
			iLog->Log( _L("Phone Model not found"));
			RetVal |= FAIL;
			}

		iLog->Log( _L("Phone Model : %s"),phonemodel.AsDes().Ptr());

		if(!(phonemodel.AsDes().Length() >2))
			{
			iLog->Log( _L("Incorrect Phone Model") );
			Err |= FAIL;					
			}
		((CLiwMap*)outmap)->DecRef();
		phonemodel.Reset();
		}
	
	InParamList->Reset();
	OutParamList->Reset();	
		
	CleanupStack::PopAndDestroy(2,ServiceHandler);
	
	__UHEAP_MARKEND;
	return Err;
	}
	
TInt  Ctsysinfoprovidertests::IMEINumberL(CStifItemParser& /*aItem*/)
	{	
    _LIT( KExample, "IMEINumberL" );
    iLog->Log( KExample );
	TInt RetVal(PASS);
	TInt32 Err;
	
	__UHEAP_MARK;

	CLiwServiceHandler* ServiceHandler;
	CLiwGenericParamList* InParamList,*OutParamList;
	MLiwInterface* Interface;
	
	CreateInterfaceL(ServiceHandler,Interface);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*Interface);

    InParamList = &(ServiceHandler->InParamListL());
    OutParamList = &(ServiceHandler->OutParamListL());

	InParamList->Reset();
	OutParamList->Reset();
	
	InParamList->AppendL(TLiwGenericParam(KEntity,TLiwVariant(KDevice)));
	InParamList->AppendL(TLiwGenericParam(KKey,TLiwVariant(KIMEI)));

	Interface->ExecuteCmdL(KGetInfo,*InParamList,*OutParamList);

	RetVal |= CheckErrorCode(*OutParamList,Err);
	if ( Err )
		{
		iLog->Log( _L("GetInfo retured error : %d"),Err );
		RetVal |= FAIL;
		} 
	
	TInt index=0;
	const TLiwGenericParam* ret_val = OutParamList->FindFirst(index,KReturnValue);
	if(!ret_val)
		{
		iLog->Log( _L("Return value parameter not found"));
		RetVal |= FAIL;
		}
	else
		{
		const CLiwMap* outmap = ret_val->Value().AsMap();
		TLiwVariant imei;
		if( !outmap->FindL(KStringData,imei) )
			{
			iLog->Log( _L("IMEI NUMBER not found"));
			RetVal |= FAIL;
			}

		iLog->Log( _L("IMEI NUMBER : %s"),imei.AsDes().Ptr());

		if(!(imei.AsDes().Length() >= 15))
			{
			iLog->Log( _L("Incorrect imei number") );
			Err |= FAIL;					
			}
		((CLiwMap*)outmap)->DecRef();
		imei.Reset();
		}
	
	InParamList->Reset();
	OutParamList->Reset();	
		
	CleanupStack::PopAndDestroy(2,ServiceHandler);
	
	__UHEAP_MARKEND;
	return Err;
	}	
	
TInt  Ctsysinfoprovidertests::GetSetBrightnessL(CStifItemParser& /*aItem*/)
	{	
    _LIT( KExample, "GetSetBrightnessL" );
    iLog->Log( KExample );
	TInt RetVal(PASS);
	TInt32 Err;
	
	TInt32 brightness_restore (50);
	TInt32 brightness_newval = 30;
	
	__UHEAP_MARK;
	
	CLiwServiceHandler* ServiceHandler;
	CLiwGenericParamList* InParamList,*OutParamList;
	MLiwInterface* Interface;
	
	CreateInterfaceL(ServiceHandler,Interface);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*Interface);

    InParamList = &(ServiceHandler->InParamListL());
    OutParamList = &(ServiceHandler->OutParamListL());

	InParamList->Reset();
	OutParamList->Reset();
	
	CLiwMap* inmap = CLiwDefaultMap::NewL();
	
//	Get brightness val
//-------------------------------------------------------------------------
	{
	iLog->Log( _L("Reading initial Brightness value .."));
	InParamList->AppendL(TLiwGenericParam(KEntity,TLiwVariant(KDisplay)));
	InParamList->AppendL(TLiwGenericParam(KKey,TLiwVariant(KBrightness)));

	Interface->ExecuteCmdL(KGetInfo,*InParamList,*OutParamList);	
	
	RetVal |= CheckErrorCode(*OutParamList,Err);
	if ( Err )
		{
		iLog->Log( _L("GetInfo retured error : %d"),Err );
		User::Leave(Err);
		} 
	
	TInt index=0;
	const TLiwGenericParam* ret_val = OutParamList->FindFirst(index,KReturnValue);
	if(!ret_val)
		{
		iLog->Log( _L("Return value parameter not found"));
		User::Leave(FAIL);
		}
	else
		{
		const CLiwMap* outmap = ret_val->Value().AsMap();
		TLiwVariant brightness;
		if( outmap->FindL(KStatus,brightness) )
			brightness_restore = brightness.AsTInt32();
		((CLiwMap*)outmap)->DecRef();
		}
	iLog->Log( _L("Inital Brightness to be restored to: %d"),brightness_restore);
	}
#ifdef _SET_BRIGHTNESS_SUPPORTED_
//	Set brightness val
//-------------------------------------------------------------------------
	{
	iLog->Log( _L("Modifying Brightness value .."));

	OutParamList->Reset();

	inmap->InsertL(KStatus,TLiwVariant(brightness_newval));
	InParamList->AppendL(TLiwGenericParam(KSysData,TLiwVariant(inmap)));

	Interface->ExecuteCmdL(KSetInfo,*InParamList,*OutParamList);	
	inmap->Remove(KStatus);
			
	RetVal |= CheckErrorCode(*OutParamList,Err);
	if ( Err )
		{
		iLog->Log( _L("GetInfo retured error : %d"),Err );
		User::Leave(Err);
		} 
	
	TInt index=0;
	const TLiwGenericParam* ret_val = OutParamList->FindFirst(index,KReturnValue);
	if(ret_val)
		{
		iLog->Log( _L("Unexpected Return value from SetInfo api"));
		User::Leave(FAIL);
		}
		iLog->Log( _L("Brightness value Modified to: %d "),brightness_newval);
	}

//	Get brightness val to verify its set properly
//-------------------------------------------------------------------------
	{
	iLog->Log( _L("Verifying Brightness value .."));

	InParamList->Reset();
	OutParamList->Reset();
	InParamList->AppendL(TLiwGenericParam(KEntity,TLiwVariant(KDisplay)));
	InParamList->AppendL(TLiwGenericParam(KKey,TLiwVariant(KBrightness)));

	Interface->ExecuteCmdL(KGetInfo,*InParamList,*OutParamList);	
	
	RetVal |= CheckErrorCode(*OutParamList,Err);
	if ( Err )
		{
		iLog->Log( _L("GetInfo retured error : %d"),Err );
		User::Leave(Err);
		} 
	
	TInt index=0;
	const TLiwGenericParam* ret_val = OutParamList->FindFirst(index,KReturnValue);
	if(!ret_val)
		{
		iLog->Log( _L("Return value parameter not found"));
		User::Leave(FAIL);
		}
	else
		{
		const CLiwMap* outmap = ret_val->Value().AsMap();
		TLiwVariant brightness;
		TInt32 brightnes_read(0);
		if( outmap->FindL(KStatus,brightness) )
			brightnes_read = brightness.AsTInt32();
		
		if(brightnes_read != brightness_newval)
			{
			iLog->Log( _L("Brightness havn't been set properly"));
			RetVal |= FAIL;
			}			
		iLog->Log( _L("Brightness value read : %d"),brightnes_read);
		((CLiwMap*)outmap)->DecRef();
		}
	}
	
	iLog->Log( _L("Restoring Brightness value.."));

//	Restore brightness val.
//-------------------------------------------------------------------------	
	{
	OutParamList->Reset();
	inmap->InsertL(KStatus,TLiwVariant(brightness_restore));
	InParamList->AppendL(TLiwGenericParam(KSysData,TLiwVariant(inmap)));

	Interface->ExecuteCmdL(KSetInfo,*InParamList,*OutParamList);	

	RetVal |= CheckErrorCode(*OutParamList,Err);
	if ( Err )
		{
		iLog->Log( _L("GetInfo retured error : %d"),Err );
		User::Leave(Err);
		} 
	
	TInt index=0;
	const TLiwGenericParam* ret_val = OutParamList->FindFirst(index,KReturnValue);
	if(ret_val)
		{
		iLog->Log( _L("Unexpected Return value from SetInfo api"));
		User::Leave(FAIL);
		}
	}
	
	iLog->Log( _L("Brightness value restored to : %d"),brightness_restore);
#endif
	InParamList->Reset();
	OutParamList->Reset();
	inmap->DecRef();
	
	CleanupStack::PopAndDestroy(2,ServiceHandler);
	
	__UHEAP_MARKEND;
	return Err;
	}
		
TInt  Ctsysinfoprovidertests::GetSetScreensaverTimeOutL(CStifItemParser& /*aItem*/)
	{	
    _LIT( KExample, "GetSetScreensaverTimeOutL" );
    iLog->Log( KExample );
	TInt RetVal(PASS);
	TInt32 Err;
	
	TInt32 ScreensaverTimeOut_restore (15);
	TInt32 ScreensaverTimeOut_newval = 30;
	
	__UHEAP_MARK;
	
	CLiwServiceHandler* ServiceHandler;
	CLiwGenericParamList* InParamList,*OutParamList;
	MLiwInterface* Interface;
	
	CreateInterfaceL(ServiceHandler,Interface);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*Interface);

    InParamList = &(ServiceHandler->InParamListL());
    OutParamList = &(ServiceHandler->OutParamListL());

	InParamList->Reset();
	OutParamList->Reset();
	
	CLiwMap* inmap = CLiwDefaultMap::NewL();
	
//	Get brightness val
//-------------------------------------------------------------------------
	{
	iLog->Log( _L("Reading initial ScreensaverTimeOut value .."));
	InParamList->AppendL(TLiwGenericParam(KEntity,TLiwVariant(KDisplay)));
	InParamList->AppendL(TLiwGenericParam(KKey,TLiwVariant(KScreenSaverTimeOut)));

	Interface->ExecuteCmdL(KGetInfo,*InParamList,*OutParamList);	
	
	RetVal |= CheckErrorCode(*OutParamList,Err);
	if ( Err )
		{
		iLog->Log( _L("GetInfo retured error : %d"),Err );
		User::Leave(Err);
		} 
	
	TInt index=0;
	const TLiwGenericParam* ret_val = OutParamList->FindFirst(index,KReturnValue);
	if(!ret_val)
		{
		iLog->Log( _L("Return value parameter not found"));
		User::Leave(FAIL);
		}
	else
		{
		const CLiwMap* outmap = ret_val->Value().AsMap();
		TLiwVariant ScreensaverTimeOut;
		if( outmap->FindL(KStatus,ScreensaverTimeOut) )
			ScreensaverTimeOut_restore = ScreensaverTimeOut.AsTInt32();
		((CLiwMap*)outmap)->DecRef();
		}
	iLog->Log( _L("Inital ScreensaverTimeOut to be restored to: %d"),ScreensaverTimeOut_restore);
	}
#ifdef _SET_SCRTIMEOUT_SUPPORTED_
//	Set ScreensaverTimeOut val
//-------------------------------------------------------------------------
	{
	iLog->Log( _L("Modifying ScreensaverTimeOut value .."));

	OutParamList->Reset();

	inmap->InsertL(KStatus,TLiwVariant(ScreensaverTimeOut_newval));
	InParamList->AppendL(TLiwGenericParam(KSysData,TLiwVariant(inmap)));

	Interface->ExecuteCmdL(KSetInfo,*InParamList,*OutParamList);	
	inmap->Remove(KStatus);
			
	RetVal |= CheckErrorCode(*OutParamList,Err);
	if ( Err )
		{
		iLog->Log( _L("GetInfo retured error : %d"),Err );
		User::Leave(Err);
		} 
	
	TInt index=0;
	const TLiwGenericParam* ret_val = OutParamList->FindFirst(index,KReturnValue);
	if(ret_val)
		{
		iLog->Log( _L("Unexpected Return value from SetInfo api"));
		User::Leave(FAIL);
		}
		iLog->Log( _L("ScreensaverTimeOut value Modified to: %d "),ScreensaverTimeOut_newval);
	}

//	Get ScreensaverTimeOut val to verify its set properly
//-------------------------------------------------------------------------
	{
	iLog->Log( _L("Verifying ScreensaverTimeOut value .."));

	InParamList->Reset();
	OutParamList->Reset();
	InParamList->AppendL(TLiwGenericParam(KEntity,TLiwVariant(KDisplay)));
	InParamList->AppendL(TLiwGenericParam(KKey,TLiwVariant(KScreenSaverTimeOut)));

	Interface->ExecuteCmdL(KGetInfo,*InParamList,*OutParamList);	
	
	RetVal |= CheckErrorCode(*OutParamList,Err);
	if ( Err )
		{
		iLog->Log( _L("GetInfo retured error : %d"),Err );
		User::Leave(Err);
		} 
	
	TInt index=0;
	const TLiwGenericParam* ret_val = OutParamList->FindFirst(index,KReturnValue);
	if(!ret_val)
		{
		iLog->Log( _L("Return value parameter not found"));
		User::Leave(FAIL);
		}
	else
		{
		const CLiwMap* outmap = ret_val->Value().AsMap();
		TLiwVariant ScreensaverTimeOut;
		TInt32 brightnes_read(0);
		if( outmap->FindL(KStatus,ScreensaverTimeOut) )
			brightnes_read = ScreensaverTimeOut.AsTInt32();
		
		if(brightnes_read != ScreensaverTimeOut_newval)
			{
			iLog->Log( _L("ScreensaverTimeOut havn't been set properly"));
			RetVal |= FAIL;
			}			
		iLog->Log( _L("ScreensaverTimeOut value read : %d"),brightnes_read);
		((CLiwMap*)outmap)->DecRef();
		}
	}
	
	iLog->Log( _L("Restoring ScreensaverTimeOut value.."));

//	Restore ScreensaverTimeOut val.
//-------------------------------------------------------------------------	
	{
	OutParamList->Reset();
	inmap->InsertL(KStatus,TLiwVariant(ScreensaverTimeOut_restore));
	InParamList->AppendL(TLiwGenericParam(KSysData,TLiwVariant(inmap)));

	Interface->ExecuteCmdL(KSetInfo,*InParamList,*OutParamList);	

	RetVal |= CheckErrorCode(*OutParamList,Err);
	if ( Err )
		{
		iLog->Log( _L("GetInfo retured error : %d"),Err );
		User::Leave(Err);
		} 
	
	TInt index=0;
	const TLiwGenericParam* ret_val = OutParamList->FindFirst(index,KReturnValue);
	if(ret_val)
		{
		iLog->Log( _L("Unexpected Return value from SetInfo api"));
		User::Leave(FAIL);
		}
	}
	
	iLog->Log( _L("ScreensaverTimeOut value restored to : %d"),ScreensaverTimeOut_restore);
#endif
	InParamList->Reset();
	OutParamList->Reset();
	inmap->DecRef();
	
	CleanupStack::PopAndDestroy(2,ServiceHandler);
	
	__UHEAP_MARKEND;
	return Err;
	}

TInt  Ctsysinfoprovidertests::UserInactivityNotifierL(CStifItemParser& )
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

TInt  Ctsysinfoprovidertests::SetGetAutoLockTimeL(CStifItemParser& )
	{	
    _LIT( KExample, "SetGetAutoLockTimeL" );
    iLog->Log( KExample );
	TInt RetVal(PASS);
	TInt32 Err;
	
	TInt32 autolocktime_restore (15);
	TInt32 autolocktime_newval = 30;
	
	__UHEAP_MARK;
	
	CLiwServiceHandler* ServiceHandler;
	CLiwGenericParamList* InParamList,*OutParamList;
	MLiwInterface* Interface;
	
	CreateInterfaceL(ServiceHandler,Interface);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*Interface);

    InParamList = &(ServiceHandler->InParamListL());
    OutParamList = &(ServiceHandler->OutParamListL());

	InParamList->Reset();
	OutParamList->Reset();
	
	CLiwMap* inmap = CLiwDefaultMap::NewL();
	
//	Get autolocktime val
//-------------------------------------------------------------------------
	{
	iLog->Log( _L("Reading initial autolocktime value .."));
	InParamList->AppendL(TLiwGenericParam(KEntity,TLiwVariant(KDisplay)));
	InParamList->AppendL(TLiwGenericParam(KKey,TLiwVariant(KAutoLockTime)));

	Interface->ExecuteCmdL(KGetInfo,*InParamList,*OutParamList);	
	
	RetVal |= CheckErrorCode(*OutParamList,Err);
	if ( Err )
		{
		iLog->Log( _L("GetInfo retured error : %d"),Err );
		User::Leave(Err);
		} 
	
	TInt index=0;
	const TLiwGenericParam* ret_val = OutParamList->FindFirst(index,KReturnValue);
	if(!ret_val)
		{
		iLog->Log( _L("Return value parameter not found"));
		User::Leave(FAIL);
		}
	else
		{
		const CLiwMap* outmap = ret_val->Value().AsMap();
		TLiwVariant autolocktime;
		if( outmap->FindL(KStatus,autolocktime) )
			autolocktime_restore = autolocktime.AsTInt32();
		((CLiwMap*)outmap)->DecRef();
		}
	iLog->Log( _L("Inital autolocktime to be restored to: %d"),autolocktime_restore);
	}
#ifdef _SET_AUTOLOCKTIME_SUPPORTED_
//	Set autolocktime val
//-------------------------------------------------------------------------
	{
	iLog->Log( _L("Modifying autolocktime value .."));

	OutParamList->Reset();

	inmap->InsertL(KStatus,TLiwVariant(autolocktime_newval));
	InParamList->AppendL(TLiwGenericParam(KSysData,TLiwVariant(inmap)));

	Interface->ExecuteCmdL(KSetInfo,*InParamList,*OutParamList);	
	inmap->Remove(KStatus);
			
	RetVal |= CheckErrorCode(*OutParamList,Err);
	if ( Err )
		{
		iLog->Log( _L("GetInfo retured error : %d"),Err );
		User::Leave(Err);
		} 
	
	TInt index=0;
	const TLiwGenericParam* ret_val = OutParamList->FindFirst(index,KReturnValue);
	if(ret_val)
		{
		iLog->Log( _L("Unexpected Return value from SetInfo api"));
		User::Leave(FAIL);
		}
		iLog->Log( _L("autolocktime value Modified to: %d "),autolocktime_newval);
	}

//	Get autolocktime val to verify its set properly
//-------------------------------------------------------------------------
	{
	iLog->Log( _L("Verifying autolocktime value .."));

	InParamList->Reset();
	OutParamList->Reset();
	InParamList->AppendL(TLiwGenericParam(KEntity,TLiwVariant(KDisplay)));
	InParamList->AppendL(TLiwGenericParam(KKey,TLiwVariant(KAutoLockTime)));

	Interface->ExecuteCmdL(KGetInfo,*InParamList,*OutParamList);	
	
	RetVal |= CheckErrorCode(*OutParamList,Err);
	if ( Err )
		{
		iLog->Log( _L("GetInfo retured error : %d"),Err );
		User::Leave(Err);
		} 
	
	TInt index=0;
	const TLiwGenericParam* ret_val = OutParamList->FindFirst(index,KReturnValue);
	if(!ret_val)
		{
		iLog->Log( _L("Return value parameter not found"));
		User::Leave(FAIL);
		}
	else
		{
		const CLiwMap* outmap = ret_val->Value().AsMap();
		TLiwVariant autolocktime;
		TInt32 brightnes_read(0);
		if( outmap->FindL(KStatus,autolocktime) )
			brightnes_read = autolocktime.AsTInt32();
		
		if(brightnes_read != autolocktime_newval)
			{
			iLog->Log( _L("autolocktime havn't been set properly"));
			RetVal |= FAIL;
			}			
		iLog->Log( _L("autolocktime value read : %d"),brightnes_read);
		((CLiwMap*)outmap)->DecRef();
		}
	}
	
	iLog->Log( _L("Restoring autolocktime value.."));

//	Restore autolocktime val.
//-------------------------------------------------------------------------	
	{
	OutParamList->Reset();
	inmap->InsertL(KStatus,TLiwVariant(autolocktime_restore));
	InParamList->AppendL(TLiwGenericParam(KSysData,TLiwVariant(inmap)));

	Interface->ExecuteCmdL(KSetInfo,*InParamList,*OutParamList);	

	RetVal |= CheckErrorCode(*OutParamList,Err);
	if ( Err )
		{
		iLog->Log( _L("GetInfo retured error : %d"),Err );
		User::Leave(Err);
		} 
	
	TInt index=0;
	const TLiwGenericParam* ret_val = OutParamList->FindFirst(index,KReturnValue);
	if(ret_val)
		{
		iLog->Log( _L("Unexpected Return value from SetInfo api"));
		User::Leave(FAIL);
		}
	}
	
	iLog->Log( _L("autolocktime value restored to : %d"),autolocktime_restore);
#endif 
	
	InParamList->Reset();
	OutParamList->Reset();
	inmap->DecRef();
	
	CleanupStack::PopAndDestroy(2,ServiceHandler);
	
	__UHEAP_MARKEND;
	return Err;
	}	

TInt  Ctsysinfoprovidertests::AutoLockNotifierL(CStifItemParser& )
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

TInt  Ctsysinfoprovidertests::DisplayResolutionL(CStifItemParser& )
	{	
    _LIT( KExample, "DisplayResolutionL" );
    iLog->Log( KExample );
	TInt RetVal(PASS);
	TInt32 Err;

	__UHEAP_MARK;
	
	CLiwServiceHandler* ServiceHandler;
	CLiwGenericParamList* InParamList,*OutParamList;
	MLiwInterface* Interface;
	
	CreateInterfaceL(ServiceHandler,Interface);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*Interface);

    InParamList = &(ServiceHandler->InParamListL());
    OutParamList = &(ServiceHandler->OutParamListL());

	InParamList->Reset();
	OutParamList->Reset();

//	Get Display Resolution
//-------------------------------------------------------------------------
	{
	iLog->Log( _L("Reading Display Resolution.."));

	InParamList->Reset();
	OutParamList->Reset();
	InParamList->AppendL(TLiwGenericParam(KEntity,TLiwVariant(KDisplay)));
	InParamList->AppendL(TLiwGenericParam(KKey,TLiwVariant(KDisplayResolution)));

	Interface->ExecuteCmdL(KGetInfo,*InParamList,*OutParamList);	
	
	RetVal |= CheckErrorCode(*OutParamList,Err);
	if ( Err )
		{
		iLog->Log( _L("GetInfo retured error : %d"),Err );
		User::Leave(Err);
		} 
	
	TInt index=0;
	const TLiwGenericParam* ret_val = OutParamList->FindFirst(index,KReturnValue);
	if(!ret_val)
		{
		iLog->Log( _L("Return value parameter not found"));
		User::Leave(FAIL);
		}
	else
		{
		const CLiwMap* outmap = ret_val->Value().AsMap();
		TLiwVariant v_xpixels,v_ypixels;
		TInt32 xpixels(0),ypixels(0);
		if( outmap->FindL(KXPixels,v_xpixels) )
			xpixels = v_xpixels.AsTInt32();
		else
			{
			iLog->Log( _L("x-pixels not found"));
			RetVal |= FAIL;			
			}
		
		if( outmap->FindL(KYPixels,v_ypixels) )
			ypixels = v_ypixels.AsTInt32();
		else
			{
			iLog->Log( _L("y-pixels not found"));
			RetVal |= FAIL;			
			}
				
		iLog->Log( _L("xpixels: %d, ypixels: %d"),xpixels,ypixels);
		((CLiwMap*)outmap)->DecRef();
		}
	}
	
	
	CleanupStack::PopAndDestroy(2,ServiceHandler);
	__UHEAP_MARK;

	return Err;	
	}	

TInt  Ctsysinfoprovidertests::DisplayOrientationL(CStifItemParser& )
	{	
    _LIT( KExample, "DisplayOrientationL" );
    iLog->Log( KExample );
	TInt RetVal(PASS);
	TInt32 Err;

	__UHEAP_MARK;
	
	CLiwServiceHandler* ServiceHandler;
	CLiwGenericParamList* InParamList,*OutParamList;
	MLiwInterface* Interface;
	
	CreateInterfaceL(ServiceHandler,Interface);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*Interface);

    InParamList = &(ServiceHandler->InParamListL());
    OutParamList = &(ServiceHandler->OutParamListL());

	InParamList->Reset();
	OutParamList->Reset();

//	Get Display Orientation
//-------------------------------------------------------------------------
	{
	iLog->Log( _L("Reading Display Orientation.."));

	InParamList->Reset();
	OutParamList->Reset();
	InParamList->AppendL(TLiwGenericParam(KEntity,TLiwVariant(KDisplay)));
	InParamList->AppendL(TLiwGenericParam(KKey,TLiwVariant(KDisplayOrientation)));

	Interface->ExecuteCmdL(KGetInfo,*InParamList,*OutParamList);	
	
	RetVal |= CheckErrorCode(*OutParamList,Err);
	if ( Err )
		{
		iLog->Log( _L("GetInfo retured error : %d"),Err );
		User::Leave(Err);
		} 
	
	TInt index=0;
	const TLiwGenericParam* ret_val = OutParamList->FindFirst(index,KReturnValue);
	if(!ret_val)
		{
		iLog->Log( _L("Return value parameter not found"));
		User::Leave(FAIL);
		}
	else
		{
		const CLiwMap* outmap = ret_val->Value().AsMap();
		TLiwVariant v_orientation;
		TInt32 orientation(0);
		if( outmap->FindL(KStatus,v_orientation) )
			orientation = v_orientation.AsTInt32();
		else
			{
			iLog->Log( _L("orientation not found"));
			RetVal |= FAIL;			
			}
		
		iLog->Log( _L("orientation: %d"),orientation);
		((CLiwMap*)outmap)->DecRef();
		}
	}
	
	CleanupStack::PopAndDestroy(2,ServiceHandler);
	__UHEAP_MARK;

	return Err;	
	}	

TInt  Ctsysinfoprovidertests::GetSetLightTimeOutL(CStifItemParser& )
	{	
    _LIT( KExample, "GetSetLightTimeOutL" );
    iLog->Log( KExample );
	TInt RetVal(PASS);
	TInt32 Err;
	
	TInt32 lighttimeout_restore (15);
	TInt32 lighttimeout_newval = 30;
	
	__UHEAP_MARK;
	
	CLiwServiceHandler* ServiceHandler;
	CLiwGenericParamList* InParamList,*OutParamList;
	MLiwInterface* Interface;
	
	CreateInterfaceL(ServiceHandler,Interface);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*Interface);

    InParamList = &(ServiceHandler->InParamListL());
    OutParamList = &(ServiceHandler->OutParamListL());

	InParamList->Reset();
	OutParamList->Reset();
	
	CLiwMap* inmap = CLiwDefaultMap::NewL();
	
//	Get lighttimeout val
//-------------------------------------------------------------------------
	{
	iLog->Log( _L("Reading initial lighttimeout value .."));
	InParamList->AppendL(TLiwGenericParam(KEntity,TLiwVariant(KDisplay)));
	InParamList->AppendL(TLiwGenericParam(KKey,TLiwVariant(KLightTimeOut)));

	Interface->ExecuteCmdL(KGetInfo,*InParamList,*OutParamList);	
	
	RetVal |= CheckErrorCode(*OutParamList,Err);
	if ( Err )
		{
		iLog->Log( _L("GetInfo retured error : %d"),Err );
		User::Leave(Err);
		} 
	
	TInt index=0;
	const TLiwGenericParam* ret_val = OutParamList->FindFirst(index,KReturnValue);
	if(!ret_val)
		{
		iLog->Log( _L("Return value parameter not found"));
		User::Leave(FAIL);
		}
	else
		{
		const CLiwMap* outmap = ret_val->Value().AsMap();
		TLiwVariant lighttimeout;
		if( outmap->FindL(KStatus,lighttimeout) )
			lighttimeout_restore = lighttimeout.AsTInt32();
		((CLiwMap*)outmap)->DecRef();
		}
	iLog->Log( _L("Inital lighttimeout to be restored to: %d"),lighttimeout_restore);
	}
#ifdef _SET_LIGHTSTIMEOUT_SUPPORTED_
//	Set lighttimeout val
//-------------------------------------------------------------------------
	{
	iLog->Log( _L("Modifying lighttimeout value .."));

	OutParamList->Reset();

	inmap->InsertL(KStatus,TLiwVariant(lighttimeout_newval));
	InParamList->AppendL(TLiwGenericParam(KSysData,TLiwVariant(inmap)));

	Interface->ExecuteCmdL(KSetInfo,*InParamList,*OutParamList);	
	inmap->Remove(KStatus);
			
	RetVal |= CheckErrorCode(*OutParamList,Err);
	if ( Err )
		{
		iLog->Log( _L("GetInfo retured error : %d"),Err );
		User::Leave(Err);
		} 
	
	TInt index=0;
	const TLiwGenericParam* ret_val = OutParamList->FindFirst(index,KReturnValue);
	if(ret_val)
		{
		iLog->Log( _L("Unexpected Return value from SetInfo api"));
		User::Leave(FAIL);
		}
		iLog->Log( _L("lighttimeout value Modified to: %d "),lighttimeout_newval);
	}

//	Get lighttimeout val to verify its set properly
//-------------------------------------------------------------------------
	{
	iLog->Log( _L("Verifying lighttimeout value .."));

	InParamList->Reset();
	OutParamList->Reset();
	InParamList->AppendL(TLiwGenericParam(KEntity,TLiwVariant(KDisplay)));
	InParamList->AppendL(TLiwGenericParam(KKey,TLiwVariant(KLightTimeOut)));

	Interface->ExecuteCmdL(KGetInfo,*InParamList,*OutParamList);	
	
	RetVal |= CheckErrorCode(*OutParamList,Err);
	if ( Err )
		{
		iLog->Log( _L("GetInfo retured error : %d"),Err );
		User::Leave(Err);
		} 
	
	TInt index=0;
	const TLiwGenericParam* ret_val = OutParamList->FindFirst(index,KReturnValue);
	if(!ret_val)
		{
		iLog->Log( _L("Return value parameter not found"));
		User::Leave(FAIL);
		}
	else
		{
		const CLiwMap* outmap = ret_val->Value().AsMap();
		TLiwVariant lighttimeout;
		TInt32 brightnes_read(0);
		if( outmap->FindL(KStatus,lighttimeout) )
			brightnes_read = lighttimeout.AsTInt32();
		
		if(brightnes_read != lighttimeout_newval)
			{
			iLog->Log( _L("lighttimeout havn't been set properly"));
			RetVal |= FAIL;
			}			
		iLog->Log( _L("lighttimeout value read : %d"),brightnes_read);
		((CLiwMap*)outmap)->DecRef();
		}
	}
	
	iLog->Log( _L("Restoring lighttimeout value.."));

//	Restore lighttimeout val.
//-------------------------------------------------------------------------	
	{
	OutParamList->Reset();
	inmap->InsertL(KStatus,TLiwVariant(lighttimeout_restore));
	InParamList->AppendL(TLiwGenericParam(KSysData,TLiwVariant(inmap)));

	Interface->ExecuteCmdL(KSetInfo,*InParamList,*OutParamList);	

	RetVal |= CheckErrorCode(*OutParamList,Err);
	if ( Err )
		{
		iLog->Log( _L("GetInfo retured error : %d"),Err );
		User::Leave(Err);
		} 
	
	TInt index=0;
	const TLiwGenericParam* ret_val = OutParamList->FindFirst(index,KReturnValue);
	if(ret_val)
		{
		iLog->Log( _L("Unexpected Return value from SetInfo api"));
		User::Leave(FAIL);
		}
	}
	
	iLog->Log( _L("lighttimeout value restored to : %d"),lighttimeout_restore);
#endif
	InParamList->Reset();
	OutParamList->Reset();
	inmap->DecRef();
	
	CleanupStack::PopAndDestroy(2,ServiceHandler);
	
	__UHEAP_MARKEND;
	return Err;
	}	

TInt  Ctsysinfoprovidertests::GetSetWallPaperL(CStifItemParser& )
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
	
	__UHEAP_MARKEND;
*/
	return Err;
	}

TInt  Ctsysinfoprovidertests::GetSetKeyGaurdL(CStifItemParser& )
	{	
    _LIT( KExample, "GetSetKeyGaurdL" );
    iLog->Log( KExample );
	TInt RetVal(PASS);
	TInt32 Err;
	
	TInt32 keygaurdtime_restore (15);
	TInt32 keygaurdtime_newval = 30;
	
	__UHEAP_MARK;
	
	CLiwServiceHandler* ServiceHandler;
	CLiwGenericParamList* InParamList,*OutParamList;
	MLiwInterface* Interface;
	
	CreateInterfaceL(ServiceHandler,Interface);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*Interface);

    InParamList = &(ServiceHandler->InParamListL());
    OutParamList = &(ServiceHandler->OutParamListL());

	InParamList->Reset();
	OutParamList->Reset();
	
	CLiwMap* inmap = CLiwDefaultMap::NewL();
	
//	Get keygaurdtime val
//-------------------------------------------------------------------------
	{
	iLog->Log( _L("Reading initial keygaurdtime value .."));
	InParamList->AppendL(TLiwGenericParam(KEntity,TLiwVariant(KDisplay)));
	InParamList->AppendL(TLiwGenericParam(KKey,TLiwVariant(KKeyGaurdTime)));

	Interface->ExecuteCmdL(KGetInfo,*InParamList,*OutParamList);	
	
	RetVal |= CheckErrorCode(*OutParamList,Err);
	if ( Err )
		{
		iLog->Log( _L("GetInfo retured error : %d"),Err );
		User::Leave(Err);
		} 
	
	TInt index=0;
	const TLiwGenericParam* ret_val = OutParamList->FindFirst(index,KReturnValue);
	if(!ret_val)
		{
		iLog->Log( _L("Return value parameter not found"));
		User::Leave(FAIL);
		}
	else
		{
		const CLiwMap* outmap = ret_val->Value().AsMap();
		TLiwVariant keygaurdtime;
		if( outmap->FindL(KStatus,keygaurdtime) )
			keygaurdtime_restore = keygaurdtime.AsTInt32();
		((CLiwMap*)outmap)->DecRef();
		}
	iLog->Log( _L("Inital keygaurdtime to be restored to: %d"),keygaurdtime_restore);
	}
#ifdef _SET_KEYGAURDTIME_SUPPORTED_
//	Set keygaurdtime val
//-------------------------------------------------------------------------
	{
	iLog->Log( _L("Modifying keygaurdtime value .."));

	OutParamList->Reset();

	inmap->InsertL(KStatus,TLiwVariant(keygaurdtime_newval));
	InParamList->AppendL(TLiwGenericParam(KSysData,TLiwVariant(inmap)));

	Interface->ExecuteCmdL(KSetInfo,*InParamList,*OutParamList);	
	inmap->Remove(KStatus);
			
	RetVal |= CheckErrorCode(*OutParamList,Err);
	if ( Err )
		{
		iLog->Log( _L("GetInfo retured error : %d"),Err );
		User::Leave(Err);
		} 
	
	TInt index=0;
	const TLiwGenericParam* ret_val = OutParamList->FindFirst(index,KReturnValue);
	if(ret_val)
		{
		iLog->Log( _L("Unexpected Return value from SetInfo api"));
		User::Leave(FAIL);
		}
		iLog->Log( _L("keygaurdtime value Modified to: %d "),keygaurdtime_newval);
	}

//	Get keygaurdtime val to verify its set properly
//-------------------------------------------------------------------------
	{
	iLog->Log( _L("Verifying keygaurdtime value .."));

	InParamList->Reset();
	OutParamList->Reset();
	InParamList->AppendL(TLiwGenericParam(KEntity,TLiwVariant(KDisplay)));
	InParamList->AppendL(TLiwGenericParam(KKey,TLiwVariant(KKeyGaurdTime)));

	Interface->ExecuteCmdL(KGetInfo,*InParamList,*OutParamList);	
	
	RetVal |= CheckErrorCode(*OutParamList,Err);
	if ( Err )
		{
		iLog->Log( _L("GetInfo retured error : %d"),Err );
		User::Leave(Err);
		} 
	
	TInt index=0;
	const TLiwGenericParam* ret_val = OutParamList->FindFirst(index,KReturnValue);
	if(!ret_val)
		{
		iLog->Log( _L("Return value parameter not found"));
		User::Leave(FAIL);
		}
	else
		{
		const CLiwMap* outmap = ret_val->Value().AsMap();
		TLiwVariant keygaurdtime;
		TInt32 brightnes_read(0);
		if( outmap->FindL(KStatus,keygaurdtime) )
			brightnes_read = keygaurdtime.AsTInt32();
		
		if(brightnes_read != keygaurdtime_newval)
			{
			iLog->Log( _L("keygaurdtime havn't been set properly"));
			RetVal |= FAIL;
			}			
		iLog->Log( _L("keygaurdtime value read : %d"),brightnes_read);
		((CLiwMap*)outmap)->DecRef();
		}
	}
	
	iLog->Log( _L("Restoring keygaurdtime value.."));

//	Restore keygaurdtime val.
//-------------------------------------------------------------------------	
	{
	OutParamList->Reset();
	inmap->InsertL(KStatus,TLiwVariant(keygaurdtime_restore));
	InParamList->AppendL(TLiwGenericParam(KSysData,TLiwVariant(inmap)));

	Interface->ExecuteCmdL(KSetInfo,*InParamList,*OutParamList);	

	RetVal |= CheckErrorCode(*OutParamList,Err);
	if ( Err )
		{
		iLog->Log( _L("GetInfo retured error : %d"),Err );
		User::Leave(Err);
		} 
	
	TInt index=0;
	const TLiwGenericParam* ret_val = OutParamList->FindFirst(index,KReturnValue);
	if(ret_val)
		{
		iLog->Log( _L("Unexpected Return value from SetInfo api"));
		User::Leave(FAIL);
		}
	}
	
	iLog->Log( _L("keygaurdtime value restored to : %d"),keygaurdtime_restore);
#endif
	InParamList->Reset();
	OutParamList->Reset();
	inmap->DecRef();
	
	CleanupStack::PopAndDestroy(2,ServiceHandler);
	
	__UHEAP_MARKEND;
	return Err;
	
	}
	
	
//returns OS VERSION
void Ctsysinfoprovidertests::GetOSVersion(TInt& aMajor,TInt& aMinor)
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
									aMajor = 9;
									aMinor = 3;
									break;
	}
}

void Ctsysinfoprovidertests::GetPlatformVersion(TInt& aMajor, TInt& aMinor)
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

void Ctsysinfoprovidertests::ProcessDriveInfoL(const CLiwMap* aDriveInfo)
	{
	TInt Err(PASS);

	TLiwVariant info;
	if (aDriveInfo->FindL(KDriveName,info))
		{
		iLog->Log( _L("Drive Name: %s"),info.AsDes().Ptr() );
		}
	
	info.Reset();
	
	if( aDriveInfo->FindL(KTotalSpace,info) )
		{
		iLog->Log( _L("Total Space: %s"),info.AsDes().Ptr());
		TLex totalspace(info.AsDes());

		TInt64 totalspaceval;
		if ( KErrNone != totalspace.Val(totalspaceval) )
			{
			iLog->Log( _L("Invalid total space string") );
			}
		else
			{
			if(totalspaceval < 0)
				{
				iLog->Log( _L("Incorrect total space") );
				Err |= FAIL;
				}				
			}
		}
	else
		{
		iLog->Log(_L("Total Space Not found in output map"));
		Err |= FAIL;
		}
	
	info.Reset();

	if (aDriveInfo->FindL(KFreeSpace,info))
		{
		iLog->Log( _L("Free Space: %s"),info.AsDes().Ptr());
		TLex freespace(info.AsDes());

		TInt64 freespaceval;
		if ( KErrNone != freespace.Val(freespaceval) )
			{
			iLog->Log( _L("Invalid free space string") );
			}
		else
			{
			if(freespaceval < 0)
				{
				iLog->Log( _L("Incorrect free space") );
				Err |= FAIL;
				}
			}
		}
	else
		{
		iLog->Log(_L("Free Space Not found in output map"));
		Err |= FAIL;
		}
	
	info.Reset();			
	
	if (aDriveInfo->FindL(KCriticalSpace,info))
		{
		TInt CriticalLevel = info.AsTInt32();
		iLog->Log( _L("Critical Space: %d"),CriticalLevel );
		if( CriticalLevel <= 0)
			{
			iLog->Log( _L("Incorrect Critical Sapce") );
			Err |= FAIL;
			}
		}
	else
		{
		iLog->Log(_L("Critical Space Not found in output map"));
		Err |= FAIL;
		}

	if(aDriveInfo->FindL(KMediaType,info))
		{
		TInt mediatype = info.AsTInt32();
		switch(mediatype)
			{
			case EMediaNotPresent:
								iLog->Log( _L("Media Type: MediaNotPresent") );
								break;
			case EMediaUnknown:
								iLog->Log( _L("Media Type: MediaUnknown") );
								break;

			case EMediaFloppy:
								iLog->Log( _L("Media Type: MediaFloppy") );
								break;

			case EMediaHardDisk:
								iLog->Log( _L("Media Type: MediaHardDisk") );
								break;
			case EMediaCdRom:
								iLog->Log( _L("Media Type: MediaCdRom") );
								break;
			case EMediaRam:
								iLog->Log( _L("Media Type: MediaRam") );
								break;
			case EMediaFlash:
								iLog->Log( _L("Media Type: MediaFlash") );
								break;
			case EMediaRom:
								iLog->Log( _L("Media Type: MediaRom") );
								break;
			case EMediaRemote:
								iLog->Log( _L("Media Type: MediaRemote") );
								break;
			case EMediaNANDFlash:
								iLog->Log( _L("Media Type: MediaNANDFlash") );
								break;
			case EMediaRotatingMedia:
								iLog->Log( _L("Media Type: MediaRotatingMedia") );
								break;
			default:
								iLog->Log( _L("Media Type: UNKOWNN") );
								Err |= FAIL;
			}
		}
	else
		{
		iLog->Log(_L("Media Type Not found in output map"));
		Err |= FAIL;
		}
	
	if(aDriveInfo->FindL(KBatteryState,info))
		{
		TInt battstate = info.AsTInt32();
		
		switch(battstate)
			{
			case EBatNotSupported:
							iLog->Log( _L("Battey State: BatNotSupported") );
							break;
			case EBatGood:
							iLog->Log( _L("Battey State: BatGood") );
							break;
			case EBatLow:
							iLog->Log( _L("Battey State: BatLow") );
							break;
			default:
							iLog->Log( _L("Battey State: UNKOWNN") );
							Err |= FAIL;
			}	
		}
	else
		{
		iLog->Log(_L("Battery State Not found in output map"));
		Err |= FAIL;
		}

	if(KErrNone != Err)
		User::Leave(Err);
	}

TInt Ctsysinfoprovidertests::CheckErrorCode( const CLiwGenericParamList& aOutList, TInt32 &aError )
	{
	TInt Index = 0;
	const TLiwGenericParam* errcode = aOutList.FindFirst(Index,KErrorCode);
	if ( KErrNotFound == Index )
		{
		iLog->Log( _L("ErrorCode not found in output ArgList") );
		return FAIL;
		}
	else
		errcode->Value().Get(aError);
	return PASS;
	}
	
void Ctsysinfoprovidertests::CreateInterfaceL(CLiwServiceHandler*& aHandler,
								MLiwInterface*& aInterface) 
	{
    iLog->Log( _L("In CreateInterfaceL") );	
	CLiwGenericParamList* InParamList,*OutParamList;

    TRAPD(Err,aHandler = CLiwServiceHandler::NewL());
	if(Err)
		{
		iLog->Log( _L("CLiwServiceHandler Created %d"),Err );
		User::Leave(Err);
		}
    		
    CleanupStack::PushL(aHandler);
 
    InParamList = &(aHandler->InParamListL());
    OutParamList = &(aHandler->OutParamListL());

	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1,KIDataSource,KService);
	CleanupStack::PushL(crit);
	crit->SetServiceClass(TUid::Uid(KLiwClassBase));
	RCriteriaArray a;
	CleanupClosePushL(a);
	a.AppendL(crit);

	aHandler->AttachL(a);

	aHandler->ExecuteServiceCmdL(*crit,*InParamList,*OutParamList);
		
	TInt Index = 0;
	const TLiwGenericParam* param = OutParamList->FindFirst(Index,KIDataSource);
	if(!param)
		{
		iLog->Log( _L("Interface Not found "));
		User::Leave(KErrGeneral);
		}
		
	aInterface = param->Value().AsInterface();
	CleanupStack::PopAndDestroy(&a);	
	CleanupStack::PopAndDestroy (crit);
	
  	CleanupStack::Pop (aHandler); 
 	iLog->Log( _L("End of CreateInterfaceL") );
  	}
  	
  // -----------------------------------------------------------------------------
// Ctsysinfoprovidertests::VibraStatus
// 
// -----------------------------------------------------------------------------
//		
TInt  Ctsysinfoprovidertests::VibraStatus(CStifItemParser& /*aItem*/)
	{
	int ret=0;
    ret = VibraNotification(0, NULL);
    
    if(ret==0)
			return KErrNone;
		else	
			return KErrGeneral;
	}


// -----------------------------------------------------------------------------
// Ctsysinfoprovidertests::SetDisplayLang
// 
// -----------------------------------------------------------------------------
//	
TInt Ctsysinfoprovidertests::SetDisplayLang(CStifItemParser& /*aItem*/)
    {
    CCoeEnv* coeSupported = NULL;
    coeSupported = CCoeEnv::Static();
    if (coeSupported)
        {
        TInt result =KErrNone;

        _LIT(KExample, "SupportedLang:");
        iLog->Log(KExample);

        TInt32 oldDisplayLang = 0, newDisplayLang = 0, changedDisplayLang = 0;

        __UHEAP_MARK;

        CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
        CleanupStack::PushL(iServiceHandler);
        CLiwGenericParamList* inparam = &(iServiceHandler->InParamListL());
        CLiwGenericParamList* outparam = &(iServiceHandler->OutParamListL());

        TInt err = KErrNone;

        CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,
                KService);
        crit->SetServiceClass(TUid::Uid(KLiwClassBase));

        RCriteriaArray a;
        a.AppendL(crit);

        iServiceHandler->AttachL(a);

        iServiceHandler->ExecuteServiceCmdL(*crit, *inparam, *outparam);

        delete crit;
        a.Reset();

        TInt pos = 0;
        MLiwInterface* interface = NULL;
        outparam->FindFirst(pos, KIDataSource);
        if (pos != KErrNotFound)
            {
            //getting the interface handle
            interface = (*outparam)[pos].Value().AsInterface();
            }

        outparam->Reset();
        inparam->Reset();

        if (interface)
            {
            TLiwGenericParam entity;
            TLiwVariant entityname;
            TLiwGenericParam key;
            TLiwVariant keyname;

            entityname.Set(KGeneral);
            entity.SetNameAndValueL(KEntity, entityname);

            keyname.Set(KDisplayLanguage);
            key.SetNameAndValueL(KKey, keyname);

            inparam->AppendL(entity);

            inparam->AppendL(key);

            entity.Reset();
            entityname.Reset();
            key.Reset();
            keyname.Reset();
            TInt32 err(KErrNone);

            //get current display language
            interface->ExecuteCmdL(KGetInfo, *inparam, *outparam);

            result |= CheckErrorCode(*outparam, err);
            iLog->Log(_L("GetInfo retured error : %d"), err);

            if (err != SErrNotFound)
                {
                iLog->Log(_L("Failed,Get Display language found ret err: %d"),err);
                result = KErrGeneral;
                }
            else
                {
                result = KErrNone;
                iLog->Log(_L("Passed Get Display language not found") );
                }

            outparam->Reset();
            CLiwDefaultMap* sysdatamap = CLiwDefaultMap::NewL();
            CleanupClosePushL(*sysdatamap);
            sysdatamap->InsertL(KStatus, (TInt32)10);
            inparam->AppendL(TLiwGenericParam(KSysData,
                    TLiwVariant(sysdatamap)));
            CleanupStack::PopAndDestroy(sysdatamap);

            interface->ExecuteCmdL(KSetInfo, *inparam, *outparam);

            result |= CheckErrorCode(*outparam, err);
            iLog->Log(_L("GetInfo retured error : %d"), err);

            if (err != SErrNotFound)
                {
                iLog->Log(_L("Failed, Set Display language found ret err: %d"),
                        err);
                result = KErrGeneral;
                }
            else
                {
                result = KErrNone;
                iLog->Log(_L("Passed, Set Display language not found") );
                }
            }

        inparam->Reset();
        outparam->Reset();

        interface->Close();

        CleanupStack::PopAndDestroy(iServiceHandler);

        return result;
        __UHEAP_MARKEND;
        }
    else
        {
        iLog->Log(_L("CCoeEnv not supported . Hence passing the test case") );
        return 0;
        }

    }
	
	
// -----------------------------------------------------------------------------
// Ctsysinfoprovidertests::SetInputLang
// 
// -----------------------------------------------------------------------------
//	
TInt  Ctsysinfoprovidertests::SetInputLang(CStifItemParser& /*aItem*/)
	{
	TInt result =KErrNone;	

	_LIT( KExample, "SupportedLang:" );
    iLog->Log( KExample );
    
    TInt32 oldInputLang = 0 ,newInputLang = 0,changedInputLang =0;
	
	 __UHEAP_MARK;

	CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
	CleanupStack::PushL(iServiceHandler);
	CLiwGenericParamList* inparam = &(iServiceHandler->InParamListL());
	CLiwGenericParamList* outparam = &(iServiceHandler->OutParamListL());

	TInt 	err = KErrNone; 
	
	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);
	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray a;
	a.AppendL(crit);    

	iServiceHandler->AttachL(a);

	iServiceHandler->ExecuteServiceCmdL(*crit, *inparam, *outparam); 

	delete crit;
	a.Reset();
	
	TInt pos = 0;
	MLiwInterface* interface = NULL;
	outparam->FindFirst( pos, KIDataSource );
	if(pos != KErrNotFound)
		{
		//get interface handle
		interface = (*outparam)[pos].Value().AsInterface();	
		}

	outparam->Reset();
	inparam->Reset();
	
	if(interface)
		{
		TLiwGenericParam entity;
		TLiwVariant  entityname;
		TLiwGenericParam key;
		TLiwVariant  keyname;
		
		entityname.Set(KGeneral);
		entity.SetNameAndValueL(KEntity,entityname);

		keyname.Set(KSupportedLanguages);
		key.SetNameAndValueL(KKey,keyname);

		//append entity and key as input parameters
		inparam->AppendL(entity);

		inparam->AppendL(key);
		
		entity.Reset();
		entityname.Reset();
		key.Reset();
		keyname.Reset();
		
		//get supported language list
		TRAPD(err1,	interface->ExecuteCmdL(KGetInfo,*inparam,*outparam));
		result = err1;
			if(err1 == KErrNone)
				{
				CLiwGenericParamList* outparam1 = CLiwGenericParamList::NewL();
				inparam->Reset();
				
				entityname.Set(KGeneral);
				entity.SetNameAndValueL(KEntity,entityname);

				keyname.Set(KInputLanguage);
				key.SetNameAndValueL(KKey,keyname);

				inparam->AppendL(entity);

				inparam->AppendL(key);
				
				entity.Reset();
				entityname.Reset();
				key.Reset();
				keyname.Reset();
				
				//get current input language
				TRAPD(err2,	interface->ExecuteCmdL(KGetInfo,*inparam,*outparam1));
				
				result = err2;
				if(err2 == KErrNone)
					{
					pos = 0 ;
					const TLiwGenericParam* output1 = outparam1->FindFirst( pos,KReturnValue );
					if(output1)     
						{
						const CLiwMap* Map = output1->Value().AsMap(); 
						if ( Map )
							{
							TLiwVariant data;
							if(EFalse!=Map->FindL(KStatus,data))
								{
								oldInputLang=data.AsTInt32();

								iLog->Log(_L("Oldinputlang"));	
								TBuf<50> buf;
								buf.AppendNum(oldInputLang);
								iLog->Log(buf);	
								}
							}//map
						}//output
					
					inparam->Reset();
					outparam1->Reset();
					
					//get new input lang from supported lang list
					pos = 0 ;
	    			const TLiwGenericParam* output = outparam->FindFirst( pos,KReturnValue );
					if(output)     
						{
						const CLiwMap* Map = output->Value().AsMap(); 
						if ( Map )
							{
							TLiwVariant data;

							if(EFalse!=Map->FindL(KLanguageList,data))
								{
								const CLiwList* langList=data.AsList();
								
								TInt32 testacctype= 0,testaccstatus= 0;
					      		if(langList)
									{
									for(TInt i=0; i != langList->Count(); ++i)
										{
										TLiwVariant langVariant;
										langList->AtL(i,langVariant);
										newInputLang = langVariant.AsTInt32();
										
										if(newInputLang != oldInputLang)
											{
												break;
											}

										}
									}			
								}
						
							data.Reset(); 
							}//map
						}//output
						
				outparam->Reset();
				
				entityname.Set(KGeneral);
				entity.SetNameAndValueL(KEntity,entityname);

				keyname.Set(KInputLanguage);
				key.SetNameAndValueL(KKey,keyname);
				
			
				//sysdata as map
				CLiwDefaultMap* map = CLiwDefaultMap::NewL();
				CleanupStack::PushL(map);

			    TLiwVariant sysdata(newInputLang);
			    map->InsertL(KStatus,sysdata); 
			    sysdata.Reset();	
		    

			    TLiwVariant sysparam(map);
				TLiwGenericParam element ;	
				element.SetNameAndValueL(KSysData,sysparam);
				sysparam.Reset();
				
				inparam->AppendL(entity);
				inparam->AppendL(key);

				inparam->AppendL(element);
				element.Reset();
				
			    map->DecRef();
			    CleanupStack::Pop(map);
				inparam->AppendL(entity);
				inparam->AppendL(key);

				entity.Reset();
				entityname.Reset();
				key.Reset();
				keyname.Reset();
				sysdata.Reset();
				
				//set new input language
				TRAPD(err3,	interface->ExecuteCmdL(KSetInfo,*inparam,*outparam1));
				inparam->Reset();
				outparam1->Reset();
				
				result = err3;
				if(err3 == KErrNone)
					{
					CLiwGenericParamList* outparam1 = CLiwGenericParamList::NewL();
					inparam->Reset();

					entityname.Set(KGeneral);
					entity.SetNameAndValueL(KEntity,entityname);

					keyname.Set(KInputLanguage);
					key.SetNameAndValueL(KKey,keyname);

					inparam->AppendL(entity);

					inparam->AppendL(key);

					entity.Reset();
					entityname.Reset();
					key.Reset();
					keyname.Reset();

					//get changed input language
					TRAPD(err4,	interface->ExecuteCmdL(KGetInfo,*inparam,*outparam1));

					result = err4;
					if(err4 == KErrNone)
					{
					pos = 0 ;
					const TLiwGenericParam* output1 = outparam1->FindFirst( pos,KReturnValue );
					if(output1)     
						{
						const CLiwMap* Map = output1->Value().AsMap(); 
						if ( Map )
							{
							TLiwVariant data;
							if(EFalse!=Map->FindL(KStatus,data))
								{
								changedInputLang=data.AsTInt32();

								iLog->Log(_L("changedInputLang"));	
								TBuf<50> buf;
								buf.AppendNum(changedInputLang);
								iLog->Log(buf);	
								}
							}//map
						}//output

					inparam->Reset();
					outparam1->Reset();

					if(newInputLang == changedInputLang)
						{
						result = KErrNone;
						}
					else
						{
						result =  KErrGeneral;
						}
					}//err4
					inparam->Reset();
					outparam1->Reset();
					}//err3
				}//err2
	
			}//err1
	
		}//interface
		
		if(newInputLang == changedInputLang)
			{
			result = KErrNone;
			}
		else
			{
			result =  KErrGeneral;
			}

	interface->Close();
	
	CleanupStack::PopAndDestroy( iServiceHandler );
	
	return result;	
	
	__UHEAP_MARKEND;


	}
// -----------------------------------------------------------------------------
// Ctsysinfoprovidertests::SupportedLang
// 
// -----------------------------------------------------------------------------
//		
TInt  Ctsysinfoprovidertests::SupportedLang(CStifItemParser& /*aItem*/)
	{

	_LIT( KExample, "SupportedLang:" );
    iLog->Log( KExample );
    
	__UHEAP_MARK;

	CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
	CleanupStack::PushL(iServiceHandler);
	CLiwGenericParamList* inparam = &(iServiceHandler->InParamListL());
	CLiwGenericParamList* outparam = &(iServiceHandler->OutParamListL());

	TInt 	result = KErrNone; 
	
	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);
	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray a;
	a.AppendL(crit);    

	iServiceHandler->AttachL(a);

	iServiceHandler->ExecuteServiceCmdL(*crit, *inparam, *outparam); 

	delete crit;
	a.Reset();
	
	TInt pos = 0;
	MLiwInterface* interface = NULL;
	outparam->FindFirst( pos, KIDataSource );
	if(pos != KErrNotFound)
		{
		interface = (*outparam)[pos].Value().AsInterface();	
		}

	outparam->Reset();
	inparam->Reset();
	
	if(interface)
		{
		TLiwGenericParam entity;
		TLiwVariant  entityname;
		TLiwGenericParam key;
		TLiwVariant  keyname;
		
		entityname.Set(KGeneral);
		entity.SetNameAndValueL(KEntity,entityname);

		keyname.Set(KSupportedLanguages);
		key.SetNameAndValueL(KKey,keyname);

		inparam->AppendL(entity);

		inparam->AppendL(key);
		
		entity.Reset();
		entityname.Reset();
		key.Reset();
		keyname.Reset();
		
		//get supported languages list
		TRAPD(err,interface->ExecuteCmdL(KGetInfo,*inparam,*outparam));
		result = err;
		
		if(err == KErrNone)
			{
			pos = 0 ;
		    
		    const TLiwGenericParam* output = outparam->FindFirst( pos,KReturnValue );
		
				
			if(output)     
				{
				const CLiwMap* Map = output->Value().AsMap(); 
				if ( Map )
					{
					TLiwVariant data;

					if(EFalse!=Map->FindL(KLanguageList,data))
						{
						const CLiwList* langList=data.AsList();
						
						TInt32 testacctype= 0,testaccstatus= 0;
			      		if(langList)
							{
							for(TInt i=0; i != langList->Count(); ++i)
								{
								TLiwVariant langVariant;
								langList->AtL(i,langVariant);
								TInt32 langValue = langVariant.AsTInt32();
								
								TBuf<50> buf;
								buf.AppendNum(langValue);
								iLog->Log(buf);

								}
							}			
						}
				
					data.Reset(); 
					}
				}
		
			}
		}
	inparam->Reset();
	outparam->Reset();
	
	interface->Close();
	
	CleanupStack::PopAndDestroy( iServiceHandler );
	
	__UHEAP_MARKEND;

	return result;
	}
// -----------------------------------------------------------------------------
// Ctsysinfoprovidertests::AvailableUSBModes
// 
// -----------------------------------------------------------------------------
//		

TInt  Ctsysinfoprovidertests::AvailableUSBModes(CStifItemParser& /*aItem*/)
	{
	
	_LIT( KExample, "AvailableUSBModes:" );
    iLog->Log( KExample );
    
    	__UHEAP_MARK;

	CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
	CleanupStack::PushL(iServiceHandler);
	CLiwGenericParamList* inparam = &(iServiceHandler->InParamListL());
	CLiwGenericParamList* outparam = &(iServiceHandler->OutParamListL());

	TInt 	err = KErrNone; 
	
	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);
	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray a;
	a.AppendL(crit);    

	iServiceHandler->AttachL(a);

	iServiceHandler->ExecuteServiceCmdL(*crit, *inparam, *outparam); 

	delete crit;
	a.Reset();
	
	TInt pos = 0;
	MLiwInterface* interface = NULL;
	outparam->FindFirst( pos, KIDataSource );
	if(pos != KErrNotFound)
		{
		interface = (*outparam)[pos].Value().AsInterface();	
		}

	outparam->Reset();
	inparam->Reset();
	
	if(interface)
		{
		TLiwGenericParam entity;
		TLiwVariant  entityname;
		TLiwGenericParam key;
		TLiwVariant  keyname;
		
		entityname.Set(KGeneral);
		entity.SetNameAndValueL(KEntity,entityname);

		keyname.Set(KAvailableUSBModes);
		key.SetNameAndValueL(KKey,keyname);

		inparam->AppendL(entity);

		inparam->AppendL(key);
		
		entity.Reset();
		entityname.Reset();
		key.Reset();
		keyname.Reset();
		
		//get available usb modes
		TRAP(err,	interface->ExecuteCmdL(KGetInfo,*inparam,*outparam));
		
		pos = 0 ;
	    
	    const TLiwGenericParam* output = outparam->FindFirst( pos,KReturnValue );
	
			
		if(output)     
			{
			const CLiwMap* Map = output->Value().AsMap(); 
			if ( Map )
				{
				TLiwVariant data;

				if(EFalse!=Map->FindL(KStringList,data))
					{
					const CLiwList* usbList=data.AsList();

					TInt32 usbMode= 0;
					if(usbList)
						{
						for(TInt i=0; i != usbList->Count(); ++i)
							{
							TLiwVariant usbModeVariant;
							usbList->AtL(i,usbModeVariant);
							usbMode = usbModeVariant.AsTInt32();

							TBuf<50> buf;
							buf.AppendNum(usbMode);
							iLog->Log(buf);
							usbModeVariant.Reset();
							}
						}			
					}

				data.Reset(); 
				}
			}
		}
	
	inparam->Reset();
	outparam->Reset();
	
	interface->Close();
	
	CleanupStack::PopAndDestroy( iServiceHandler );
	
	__UHEAP_MARKEND;

	return err;
	}
	
TInt  Ctsysinfoprovidertests::ConnBluetooth(CStifItemParser& /*aItem*/)
	{	int ret=0;
    ret = ReqNotification();
    
    if(ret==0)
			return KErrNone;
		else	
			return KErrGeneral;
		}
		


TInt  Ctsysinfoprovidertests::GetActiveConnections(CStifItemParser& /*aItem*/)
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


TInt  Ctsysinfoprovidertests::BTAsyncRequestCancel(CStifItemParser& /*aItem*/)
	{	int ret=0;
    ret = BTAsyncReqCancel();
    
    if(ret==0)
			return KErrNone;
		else	
			return KErrGeneral;
		}
		


TInt  Ctsysinfoprovidertests::GetActiveConnectionsReqCancel(CStifItemParser& /*aItem*/)
	{
	_LIT( KExample, "GetActiveConnections" );
    iLog->Log( KExample );
    
	int ret=0;
    ret = ActiveConnectionReqCancel(iLog);
    
    if(ret==0)
			return KErrNone;
		else	
			return KErrGeneral;
		}

// -----------------------------------------------------------------------------
// Ctsysinfoprovidertests::GetCameraInfoTest
// Positive Test
// -----------------------------------------------------------------------------
//
TInt Ctsysinfoprovidertests::GetCameraInfoTest(CStifItemParser& aItem)
    {
    TInt retcode;
    iLog->Log(_L("GetCameraInfoTest - Positive Test") );

    __UHEAP_MARK;
    TInt error = KErrNone;
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    CleanupStack::PushL(iServiceHandler);
    CLiwGenericParamList* inparam = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outparam = &(iServiceHandler->OutParamListL());

    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource, KService);
    crit->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a;
    a.AppendL(crit);
    iServiceHandler->AttachL(a);
    iServiceHandler->ExecuteServiceCmdL(*crit, *inparam, *outparam);
    delete crit;
    a.Reset();

    TInt pos = 0;
    MLiwInterface* interface = NULL;
    outparam->FindFirst(pos, KIDataSource);
    if (pos != KErrNotFound)
        {
        interface = (*outparam)[pos].Value().AsInterface();
        }
    outparam->Reset();
    inparam->Reset();

    if (interface)
        {
        TLiwGenericParam entity;
        TLiwVariant entityValue;
        TLiwGenericParam key;
        TLiwVariant keyValue;
        TPtrC16 Entity(KNullDesC);
        TPtrC16 Key(KNullDesC);
        TInt expectedError = 0;

        aItem.GetNextString(Entity);
        aItem.GetNextString(Key);
        aItem.GetNextInt(expectedError);

        entityValue.Set(Entity);
        entity.SetNameAndValueL(KEntity, entityValue);
        keyValue.Set(Key);
        key.SetNameAndValueL(KKey, keyValue);

        inparam->AppendL(entity);
        inparam->AppendL(key);

        entity.Reset();
        entityValue.Reset();
        key.Reset();
        keyValue.Reset();

        //Get Image Data
        TRAP(error, interface->ExecuteCmdL(KGetInfo, *inparam, *outparam));

        pos = 0;
        const TLiwGenericParam* errorCode = outparam->FindFirst(pos,
                KErrorCode);
        if (errorCode)
            {
            retcode = errorCode->Value().AsTInt32();
            if (retcode == expectedError)
                {
                iLog->Log(_L("Got expected error code %d"), retcode);
                pos = 0;
                const TLiwGenericParam* output = outparam->FindFirst(pos,
                        KReturnValue);
                if (output)
                    {
                    const CLiwMap* Map = output->Value().AsMap();
                    if (Map)
                        {
                        TLiwVariant data1;
                        TLiwVariant data2;
                        if (EFalse != Map->FindL(KCamResList, data1))
                            {
                            const CLiwList* resolutionList = data1.AsList();
                            TInt width;
                            TInt height;
                            if (resolutionList)
                                {
                                TInt count = resolutionList->Count();
                                for (TInt i=0; i < count; i++)
                                    {
                                    TLiwVariant resolutionData;
                                    resolutionList->AtL(i, resolutionData);
                                    const CLiwMap* resolutionDataMap = resolutionData.AsMap();
                                    TLiwVariant xPix;
                                    resolutionDataMap->FindL(KXPixels, xPix);
                                    width = xPix.AsTInt32();
                                    xPix.Reset();
                                    iLog->Log(_L("Supported XPixel %d is - %d "),i, width);

                                    TLiwVariant yPix;
                                    resolutionDataMap->FindL(KYPixels, yPix);
                                    height = yPix.AsTInt32();
                                    yPix.Reset();
                                    iLog->Log(_L("Supported YPixel %d is - %d "),i, height);

                                    resolutionData.Reset();
                                    }//for
                                } //resolutionList                            
                            }//FindL
                        if (EFalse != Map->FindL(KCamMimeTypesList, data2))
                            {
                            const CLiwList* mimeList = data2.AsList();
                            if (mimeList)
                                {
                                for (TInt i=0; i != mimeList->Count(); i++)
                                    {
                                    TLiwVariant mimeData;
                                    TPtrC16 mimeType;
                                    mimeList->AtL(i, mimeData);
                                    mimeType.Set(mimeData.AsDes());

                                    iLog->Log(_L("Mimetype %d is - %s"), i,mimeType.Ptr());
                                    mimeData.Reset();
                                    }//for
                                } //mimeList
                            }//FindL
                        data1.Reset();
                        data2.Reset();
                        }//Map                    
                    }//output 
                retcode = KErrNone;
                iLog->Log(_L("Test Completed"));
                iLog->Log(_L("PASS"));
                }//retcode == expected error
            else
                {
                iLog->Log(_L("Error Code Returned = %d"), retcode);
                iLog->Log(_L("Error Code Expected = %d"), expectedError);
                iLog->Log(_L("Test Completed"));
                iLog->Log(_L("FAIL"));
                }
            }//errorCode
        }//interface    
    inparam->Reset();
    outparam->Reset();
    interface->Close();
    CleanupStack::PopAndDestroy(iServiceHandler);
    __UHEAP_MARKEND;
    iLog->Log(_L("END"));
    return retcode;
    }

//  End of File
