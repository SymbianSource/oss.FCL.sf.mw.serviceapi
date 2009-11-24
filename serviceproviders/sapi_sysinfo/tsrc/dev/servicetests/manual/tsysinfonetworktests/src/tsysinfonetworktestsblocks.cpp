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
* Description:   tsysinfonetworktests
*
*/




// INCLUDE FILES
#include <e32svr.h>
#include <StifParser.h>
#include <StifTestInterface.h>
#include <f32file.h>

#include "tsysinfonetworktests.h"
#include "sysinfoservice.h"
#include "entitykeys.h"
#include "tsysinfosigstrengthasyn.h"
#include "tsysinfonetworkmodenotify.h"
#include "tsysinforegstatusnotify.h"
#include "tsysinfohomenetworkasync.h"
#include "tsysinfohomenetworknotify.h"
#include "tsysinfocurrentnetworkasync.h"
#include "tsysinfocurrentnetworknotify.h"
#include "tsysinfocellidnotify.h"
#include "tsysinfocellidasync.h"
#include "tsysinfolacasync.h"
#include "tsysinfolacnotify.h"
#include "tsysinfosiglevelasync.h"
#include "tsysinfosiglevelnotify.h"
#include "tsysinfosigstrengthnotify.h"


using namespace SysInfo;

// -----------------------------------------------------------------------------
// CTSysInfoNetworkTests::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTSysInfoNetworkTests::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CTSysInfoNetworkTests::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTSysInfoNetworkTests::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
       
       	ENTRY( "SignalStrengthAsyc-M", 	CTSysInfoNetworkTests::SignalStrengthAsyncL),
		ENTRY( "SignalStrengthNoti-M", 	CTSysInfoNetworkTests::SignalStrengthNotiL),
        ENTRY( "SignalLevelAsyc-M", 	CTSysInfoNetworkTests::SignalLevelAsyncL),
		ENTRY( "SignalLevelNoti-M", 	CTSysInfoNetworkTests::SignalLevelNotiL),        
		ENTRY( "RegisteredOnHomeNw-M",	CTSysInfoNetworkTests::RegisteredOnHomeNwL),
        ENTRY( "RegStatusNoService-M",	CTSysInfoNetworkTests::RegStatusNoServiceL),
	    ENTRY( "RegStatusNotify-M",	CTSysInfoNetworkTests::RegStatusNotifyL),
        ENTRY( "NetworkModeGSM-M",   	CTSysInfoNetworkTests::GetNwModeGSML),
        ENTRY( "NetworkModeNotify-M",   	CTSysInfoNetworkTests::NetworkModeNotifyL),
		ENTRY( "HomeNetworkAsyc-M", 	CTSysInfoNetworkTests::HomeNwAsyncL),
		ENTRY( "HomeNetworkNotify-M", 	CTSysInfoNetworkTests::HomeNetworkNotifyL),
		ENTRY( "CurrentNwAsync-M", 		CTSysInfoNetworkTests::CurrentNwAsyncL),        
		ENTRY( "CurrentNwNoti-M", 		CTSysInfoNetworkTests::CurrentNwNotiL),
		ENTRY( "LACAsync-M", 			CTSysInfoNetworkTests::LACAsyncL),        
		ENTRY( "LACNoti-M", 			CTSysInfoNetworkTests::LACNotiL),     
		ENTRY( "CellIdNotify-M", 			CTSysInfoNetworkTests::CellIdNotifyL),     
		ENTRY( "CellIdAsync-M", 			CTSysInfoNetworkTests::CellIdAsyncL),     
        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );
    }

TInt  CTSysInfoNetworkTests::RegisteredOnHomeNwL(CStifItemParser& /*aItem*/)
	{	
    _LIT( KExample, "RegisteredOnHomeNwL" );
    iLog->Log( KExample );
	TInt Err(PASS);
	
	__UHEAP_MARK;
	CSysInfoService *obj = CSysInfoService::NewL();
	CleanupStack::PushL(obj);

	CSysData* output ;
	
	TRAPD(err,obj->GetInfoL(KNetwork,KRegistrationStatus,output));
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
				TInt Registration = ((CStatus*)output)->Status();
				
			    if( REGISTEREDONHOMENW != Registration )
					{
					Err |= FAIL;
					iLog->Log( _L("Incorrect NW regitration status") );
					}
					
		TInt networkMode= ((CStatus*)output)->Status();
		
		TBuf<20> buf;
		buf.AppendNum(networkMode);
		iLog->Log(buf);

		Err = PASS;
		
		
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
	
TInt  CTSysInfoNetworkTests::RegStatusNoServiceL(CStifItemParser& /*aItem*/)
	{	
    _LIT( KExample, "RegStatusNoServiceL" );
    iLog->Log( KExample );
	TInt Err(PASS);
	
	__UHEAP_MARK;
	CSysInfoService *obj = CSysInfoService::NewL();
	CleanupStack::PushL(obj);

	CSysData* output;
	
	TRAPD(err,obj->GetInfoL(KNetwork,KRegistrationStatus,output));
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
				TInt Registration = ((CStatus*)output)->Status();
				
				if( NOSERVICE != Registration )
					{
					Err |= FAIL;
					iLog->Log( _L("Incorrect NW regitration status") );
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

TInt  CTSysInfoNetworkTests::GetNwModeGSML(CStifItemParser& /*aItem*/)
	{	
    _LIT( KExample, "GetNwModeGSML" );
    iLog->Log( KExample );
	TInt Err(PASS);
	
	__UHEAP_MARK;
	CSysInfoService *obj = CSysInfoService::NewL();
	CleanupStack::PushL(obj);

	CSysData* output;
	
	TRAPD(err,obj->GetInfoL(KNetwork,KNetworkMode,output));
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
				TInt NwMode = ((CStatus*)output)->Status();
				
				if( ENWNetworkModeGsm != NwMode )
					{
					Err |= FAIL;
					iLog->Log( _L("Incorrect NW Mode") );
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

			
TInt  CTSysInfoNetworkTests::SignalStrengthAsyncL(CStifItemParser& aItem)
	{	
    _LIT( KExample, "SignalStrengthAsyncL" );
    iLog->Log( KExample );
	TInt Err(PASS);
	
	__UHEAP_MARK;
	
	TInt InputStrength;
	aItem.GetNextInt(InputStrength);

	CSignalStrAsync* test = CSignalStrAsync::NewL(iLog,InputStrength);
	test->Start();
	Err = test->Result();
	delete test;
		
	__UHEAP_MARKEND;
	return Err;
	}


TInt  CTSysInfoNetworkTests::SignalStrengthNotiL(CStifItemParser& aItem)
	{	
    _LIT( KExample, "SignalStrengthNotiL" );
    iLog->Log( KExample );
	TInt Err(PASS);
	
	__UHEAP_MARK;
	
	TInt InputStrength;
	aItem.GetNextInt(InputStrength);

	CSignalStrNotify* test = CSignalStrNotify::NewL(iLog,InputStrength);
	test->Start();
	Err = test->Result();
	delete test;
		
	__UHEAP_MARKEND;
	return Err;
	}
	
TInt  CTSysInfoNetworkTests::SignalLevelAsyncL(CStifItemParser& /*aItem*/)
	{	
    _LIT( KExample, "SignalStrengthAsyncL" );
    iLog->Log( KExample );
	TInt Err(PASS);
	
	__UHEAP_MARK;
	
	CSysInfoService *obj = CSysInfoService::NewL();
	CleanupStack::PushL(obj);
	
	CSysData* output=NULL;
	
	_LIT(KSignalLevel,"SignalLevel");
		
	TRAPD(err,obj->GetInfoL(KNetwork,KSignalLevel,1,this));
	if ( err == KErrNotFound )
		{
		Err = PASS;
		iLog->Log( _L("Signal Level Not Found "));
		}
	else
		{
		Err |= FAIL;
		iLog->Log( _L("GetInfo API returned error: %d Expected Error: %d"), err,KErrNotFound);
		}
	CleanupStack::PopAndDestroy(obj);
	__UHEAP_MARKEND;
	return Err;
	}

void CTSysInfoNetworkTests::HandleResponseL(const TDesC& /*aEntity*/,const TDesC& /*aKey*/,
	 					CSysData* /*aOutput*/, TInt32 /*aTransID*/, TSysRequest::TRequestType /*aType*/,TInt /*aError*/)
	{

	}
	
TInt  CTSysInfoNetworkTests::SignalLevelNotiL(CStifItemParser& /*aItem*/)
	{	
    _LIT( KExample, "SignalLevelNotiL" );
    iLog->Log( KExample );
	TInt Err(PASS);
	
	__UHEAP_MARK;
	
	
	CSysInfoService *obj = CSysInfoService::NewL();
	CleanupStack::PushL(obj);
	
	CSysData* output=NULL;
	
	_LIT(KSignalLevel,"SignalLevel");
		
	TRAPD(err,obj->GetNotificationL(KNetwork,KSignalLevel,1,this));
	if ( err == KErrNotFound )
		{
		Err = PASS;
		iLog->Log( _L("Signal Level Not supported "));
		}
	else
		{
		Err |= FAIL;
		iLog->Log( _L("GetInfo API returned error: %d Expected Error: %d"), err,KErrNotFound);
		}

	CleanupStack::PopAndDestroy(obj);	
	__UHEAP_MARKEND;
	return Err;
	}
	
	
				
TInt  CTSysInfoNetworkTests::NetworkModeNotifyL(CStifItemParser& /*aItem*/)
	{
	
    _LIT( KExample, "NetworkModeNotifyL" );
    iLog->Log( KExample );
	TInt Err(PASS);
	
	__UHEAP_MARK;
	
	CNetModeNotify* test = CNetModeNotify::NewL(iLog);
	test->Start();
	Err = test->Result();
	delete test;
		
	__UHEAP_MARKEND;
	return Err;
	}


TInt  CTSysInfoNetworkTests::RegStatusNotifyL(CStifItemParser& /*aItem*/)
	{
	
    _LIT( KExample, "RegStatusNotifyL" );
    iLog->Log( KExample );
	TInt Err(PASS);
	
	__UHEAP_MARK;
	
	CRegStatusNotify* test = CRegStatusNotify::NewL(iLog);
	test->Start();
	Err = test->Result();
	delete test;
		
	__UHEAP_MARKEND;
	return Err;
	}


TInt  CTSysInfoNetworkTests::HomeNwAsyncL(CStifItemParser& /*aItem*/)
	{
	
    _LIT( KExample, "HomeNwAsyncL" );
    iLog->Log( KExample );
	TInt Err(PASS);
	
	__UHEAP_MARK;
	
	CHomeNwAsync* test = CHomeNwAsync::NewL(iLog);
	test->Start();
	Err = test->Result();
	if(Err == KErrNotFound)
	    {
	    iLog->Log( _L("HomeNetwork Not Found" ));
	    Err = KErrNone;
	    }
	else
	    {
	    iLog->Log( _L("Incorrect error returned" ));
	    Err = KErrGeneral;
	    }
	delete test;
		
	__UHEAP_MARKEND;
	return Err;
	}
	
TInt  CTSysInfoNetworkTests::HomeNetworkNotifyL(CStifItemParser& /*aItem*/)
	{
	
    _LIT( KExample, "HomeNetworkNotifyL" );
    iLog->Log( KExample );
	TInt Err(PASS);
	
	__UHEAP_MARK;
	
	CHomeNetworkNotify* test = CHomeNetworkNotify::NewL(iLog);
	test->Start();
	Err = test->Result();
	delete test;
		
	__UHEAP_MARKEND;
	return Err;
	}
	
TInt  CTSysInfoNetworkTests::CurrentNwAsyncL(CStifItemParser& /*aItem*/)
	{
	
    _LIT( KExample, "CurrentNwAsyncL" );
    iLog->Log( KExample );
	TInt Err(PASS);
	
	__UHEAP_MARK;
	
	CCurrentNetAsync* test = CCurrentNetAsync::NewL(iLog);
	test->Start();
	Err = test->Result();
	delete test;
		
	__UHEAP_MARKEND;
	return Err;
	}
	
TInt  CTSysInfoNetworkTests::CurrentNwNotiL(CStifItemParser& /*aItem*/)
	{
	
    _LIT( KExample, "CurrentNwNotiL" );
    iLog->Log( KExample );
	TInt Err(PASS);
	
	__UHEAP_MARK;
	
	CCurrentNetNotify* test = CCurrentNetNotify::NewL(iLog);
	test->Start();
	Err = test->Result();
	delete test;
		
	__UHEAP_MARKEND;
	return Err;
	}
	
	
		
TInt  CTSysInfoNetworkTests::LACAsyncL(CStifItemParser& /*aItem*/)
	{
	
    _LIT( KExample, "LACAsyncL" );
    iLog->Log( KExample );
	TInt Err(PASS);
	
	__UHEAP_MARK;
	
	CLacAsync* test = CLacAsync::NewL(iLog);
	test->Start();
	Err = test->Result();
	delete test;
		
	__UHEAP_MARKEND;
	return Err;
	}
	
TInt  CTSysInfoNetworkTests::LACNotiL(CStifItemParser& /*aItem*/)
	{
	
    _LIT( KExample, "LACNotiL" );
    iLog->Log( KExample );
	TInt Err(PASS);
	
	__UHEAP_MARK;
	
	CLacNotify* test = CLacNotify::NewL(iLog);
	test->Start();
	Err = test->Result();
	delete test;
		
	__UHEAP_MARKEND;
	return Err;
	}
	
TInt  CTSysInfoNetworkTests::CellIdNotifyL(CStifItemParser& /*aItem*/)
	{
	
    _LIT( KExample, "CellIdNotifyL" );
    iLog->Log( KExample );
	TInt Err(PASS);
	
	__UHEAP_MARK;
	
	CCellidNotify* test = CCellidNotify::NewL(iLog);
	test->Start();
	Err = test->Result();
	delete test;
		
	__UHEAP_MARKEND;
	return Err;
	}
	
TInt  CTSysInfoNetworkTests::CellIdAsyncL(CStifItemParser& /*aItem*/)
	{
	
    _LIT( KExample, "CellIdAsyncL" );
    iLog->Log( KExample );
	TInt Err(PASS);
	
	__UHEAP_MARK;
	

	CCellidAsync* test = CCellidAsync::NewL(iLog);
	test->Start();
	Err = test->Result();
	delete test;
		
	__UHEAP_MARKEND;
	return Err;
	}