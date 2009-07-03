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
* Description:   ?Description
*
*/



// INCLUDE FILES
#include <e32svr.h>
#include <StifParser.h>
#include <Stiftestinterface.h>
#include <f32file.h>
#include <hal.h>

#include "TSysBattery.h"
#include "sysinfoservice.h"
#include "entitykeys.h"
#include "TBatteryStrengthAsyn.h"
#include "TBatLvlNoti.h"
#include "TChargerNoti.h"
#include "tbatstrnoti.h"

using namespace SysInfo;

// -----------------------------------------------------------------------------
// CTSysBattery::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTSysBattery::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CTSysBattery::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTSysBattery::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "BatteryNotChargingSync-M", CTSysBattery::BatteryNotChargingL),
        ENTRY( "BatteryChargingSync-M",	CTSysBattery::BatteryChargingL),
        ENTRY( "BatteryLevelSync-M",	CTSysBattery::BatteryLevelL),
        ENTRY( "BatteryLvlNoti-M",CTSysBattery::BatteryLvlNotiL),
        ENTRY( "ChargeStateNoti-M",CTSysBattery::ChargeStateNotiL),
        ENTRY( "BatteryStrengthNoti-M",CTSysBattery::BatteryStrengthNotiL),
        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );
    }

TInt  CTSysBattery::BatteryChargingL(CStifItemParser& )
	{	
    _LIT( KExample, "BatteryChargingL" );
    iLog->Log( KExample );
	TInt Err(PASS);
	
#if ( !(defined(__WINS__) || defined(__WINSCW__)) )
	__UHEAP_MARK;
	CSysInfoService *obj = CSysInfoService::NewL();
	CleanupStack::PushL(obj);

	CSysData* output=NULL;
	
	TRAPD(err,obj->GetInfoL(KBattery,KBatteryStrength,output));
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
				TInt ChargerState;
				ChargerState = ((CStatus*)output)->Status();
				if( ECharging != ChargerState )
					{
					iLog->Log( _L("Incorrect charging state returned.. %d"),ChargerState );
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

TInt  CTSysBattery::BatteryNotChargingL(CStifItemParser& )
	{	
    _LIT( KExample, "BatteryNotChargingL" );
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
				TInt ChargerState;
				ChargerState = ((CStatus*)output)->Status();
				if( ENotCharging != ChargerState )
					{
					iLog->Log( _L("Incorrect charging state returned.. %d"),ChargerState );
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

TInt  CTSysBattery::BatteryLevelL(CStifItemParser& /*aItem*/)
	{	
    _LIT( KExample, "BatteryLevelL" );
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

TInt  CTSysBattery::BatteryLvlNotiL(CStifItemParser&)
	{	
    _LIT( KExample, "BatteryLvlNotiL" );
    iLog->Log( KExample );
	TInt Err(PASS);

#if ( !(defined(__WINS__) || defined(__WINSCW__)) )	
	__UHEAP_MARK;

	CSysInfoService *obj = CSysInfoService::NewL();
	CleanupStack::PushL(obj);
	
	_LIT(KBatteryLevel,"BatteryLevel");
			
	TRAPD(err,obj->GetNotificationL(KBattery,KBatteryLevel,1,this));
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


void CTSysBattery::HandleResponseL(const TDesC& /*aEntity*/,const TDesC& /*aKey*/,
	 					CSysData* /*aOutput*/, TInt32 /*aTransID*/, TSysRequest::TRequestType /*aType*/,TInt /*aError*/)
	{

	}
TInt  CTSysBattery::ChargeStateNotiL(CStifItemParser&)
	{	
    _LIT( KExample, "ChargeStateNotiL" );
    iLog->Log( KExample );
	TInt Err(PASS);

#if ( !(defined(__WINS__) || defined(__WINSCW__)) )	
	__UHEAP_MARK;
	
	CChargerNoti* test = CChargerNoti::NewL(iLog);
	test->Start();
	Err = test->Result();
	delete test;
		
	__UHEAP_MARKEND;
#endif
	return Err;
	}

TInt  CTSysBattery::BatteryStrengthNotiL(CStifItemParser&)
	{	
    _LIT( KExample, "BatteryStrengthNotiL" );
    iLog->Log( KExample );
	TInt Err(PASS);
#if ( !(defined(__WINS__) || defined(__WINSCW__)) )	
	__UHEAP_MARK;
	
	CBatStrengthNoti* test = CBatStrengthNoti::NewL(iLog);
	test->Start();
	Err = test->Result();
	delete test;
#endif		
	__UHEAP_MARKEND;
	return Err;
	}
