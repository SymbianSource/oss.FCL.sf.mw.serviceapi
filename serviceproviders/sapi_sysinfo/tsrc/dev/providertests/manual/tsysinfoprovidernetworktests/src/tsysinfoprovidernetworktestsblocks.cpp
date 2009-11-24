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
* Description:   tsysinfoprovidernetworktestsblocks
*
*/




// INCLUDE FILES
#include <e32svr.h>
#include <StifParser.h>
#include <StifTestInterface.h>
#include <f32file.h>
#include <liwcommon.h>
#include<liwservicehandler.h>
#include "../../../inc/serviceerrno.h"

#include "tsysinfoprovidernetworktests.h"
#include "tsignalstrengthasyn.h"
#include "thomenetworkasync.h"
#include "tcurrentnetworknotify.h"
#include "tsingnalstrengthnotify.h"
#include "sysinfoaiwparams.hrh"
#include"entitykeys.h"

using namespace LIW ;
using namespace SysInfo;

using namespace sysinfoaiwparams;	


// -----------------------------------------------------------------------------
// CTSysInfoProviderNetworkTests::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTSysInfoProviderNetworkTests::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CTSysInfoProviderNetworkTests::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTSysInfoProviderNetworkTests::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
       
       	ENTRY( "SignalStrengthAsyc-M", 	CTSysInfoProviderNetworkTests::SignalStrengthAsyncL),
		ENTRY( "SignalStrengthNoti-M", 	CTSysInfoProviderNetworkTests::SignalStrengthNotiL),
		ENTRY( "RegisteredOnHomeNw-M",	CTSysInfoProviderNetworkTests::RegisteredOnHomeNwL),
        ENTRY( "NetworkModeGSM-M",   	CTSysInfoProviderNetworkTests::GetNwModeGSML),
		ENTRY( "HomeNetworkAsyc-M", 	CTSysInfoProviderNetworkTests::HomeNwAsyncL),
		ENTRY( "CurrentNwNoti-M", 		CTSysInfoProviderNetworkTests::CurrentNwNotiL),
        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );
    }

TInt  CTSysInfoProviderNetworkTests::RegisteredOnHomeNwL(CStifItemParser& /*aItem*/)
	{
	
	TInt Err(PASS);
	_LIT( KExample, "RegisteredOnHomeNwL:" );
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
		
		entityname.Set(KNetwork);
		entity.SetNameAndValueL(KEntity,entityname);

		keyname.Set(KRegistrationStatus);
		key.SetNameAndValueL(KKey,keyname);

		inparam->AppendL(entity);

		inparam->AppendL(key);
		
		entity.Reset();
		entityname.Reset();
		key.Reset();
		keyname.Reset();

		TRAP(err,	interface->ExecuteCmdL(KGetInfo,*inparam,*outparam));
		
		
		pos = 0 ;
	    
	     outparam->FindFirst( pos,KErrorCode );
		if(pos != KErrNotFound)
			{
			if( (*outparam)[pos].Value().AsTInt32() != KErrNone )
				err = (TInt)((*outparam)[pos].Value().AsTInt32());
			}
			
		if(err == SErrNone)
			{
    		pos = 0 ;
    		const TLiwGenericParam* output = outparam->FindFirst( pos,KReturnValue );

			if(output)     
				{
				const CLiwMap* Map = output->Value().AsMap(); 
				if ( Map )
					{

					TLiwVariant regTypeVar;
					Map->FindL(KStatus,regTypeVar);
					TInt regType = regTypeVar.AsTInt32();
					regTypeVar.Reset();

					TBuf<50> buf;
					buf.AppendNum(regType);
					iLog->Log(buf);

					if( REGISTEREDONHOMENW != regType )
						{
						Err |= FAIL;
						iLog->Log( _L("Incorrect NW regitration status") );
						}

					}
				
				}//output
			else
				{
				Err |= err;
				iLog->Log( _L("Output data Set to NULL") );
				}
			}//err
		else
			{
			Err |= err;
			iLog->Log( _L("API returned error") );
			}
	    
		}//interface

	inparam->Reset();
	outparam->Reset();
	
	interface->Close();
	
	CleanupStack::PopAndDestroy( iServiceHandler );
	__UHEAP_MARKEND;
	
	return Err;
	}
	


TInt  CTSysInfoProviderNetworkTests::GetNwModeGSML(CStifItemParser& /*aItem*/)
	{	
    	
	TInt Err(PASS);
	_LIT( KExample, "GetNwModeGSML:" );
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
		
		entityname.Set(KNetwork);
		entity.SetNameAndValueL(KEntity,entityname);

		keyname.Set(SysInfo::KNetworkMode);
		key.SetNameAndValueL(KKey,keyname);

		inparam->AppendL(entity);

		inparam->AppendL(key);
		
		entity.Reset();
		entityname.Reset();
		key.Reset();
		keyname.Reset();

		TRAP(err,	interface->ExecuteCmdL(KGetInfo,*inparam,*outparam));
		
		
		pos = 0 ;
	    
	     outparam->FindFirst( pos,KErrorCode );
		if(pos != KErrNotFound)
			{
			if( (*outparam)[pos].Value().AsTInt32() != KErrNone )
				err = (TInt)((*outparam)[pos].Value().AsTInt32());
			}
			
		if(err == SErrNone)
			{
    		pos = 0 ;
    		const TLiwGenericParam* output = outparam->FindFirst( pos,KReturnValue );

			if(output)     
				{
				const CLiwMap* Map = output->Value().AsMap(); 
				if ( Map )
					{
						if ( Map )
							{
							TLiwVariant netModeVar;
							Map->FindL(KStatus,netModeVar);
					    	TInt netMode = netModeVar.AsTInt32();
							netModeVar.Reset();
							
							TBuf<50> buf;
			 				buf.AppendNum(netMode);
			 				iLog->Log(buf);
			 				
							if( GSM != netMode )
								{
								Err |= FAIL;
								iLog->Log( _L("Incorrect NW regitration status") );
								}
						
							}
			      		
			
						}
				
				}//output
			else
				{
				Err |= err;
				iLog->Log( _L("Output data Set to NULL") );
				}
			}//err
		else
			{
			Err |= err;
			iLog->Log( _L("API returned error") );
			}
	    
		}//interface

	inparam->Reset();
	outparam->Reset();
	
	interface->Close();
	
	CleanupStack::PopAndDestroy( iServiceHandler );
	__UHEAP_MARKEND;

	return Err;
	
	
	}

			
TInt  CTSysInfoProviderNetworkTests::SignalStrengthAsyncL(CStifItemParser& aItem)
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


TInt  CTSysInfoProviderNetworkTests::SignalStrengthNotiL(CStifItemParser& aItem)
	{	
    _LIT( KExample, "SignalStrengthNotiL" );
    iLog->Log( KExample );
	TInt Err(PASS);
	// On Emulator this is not supported.				
	#if (! (defined(__WINS__) || defined(__WINSCW__)) )

	__UHEAP_MARK;
	
	TInt InputStrength;
	aItem.GetNextInt(InputStrength);

	CSignalStrNotify* test = CSignalStrNotify::NewL(iLog,InputStrength);
	test->Start();
	Err = test->Result();
	delete test;
		
	__UHEAP_MARKEND;
	#endif
	return Err;
	}
	



TInt  CTSysInfoProviderNetworkTests::HomeNwAsyncL(CStifItemParser& aItem)
	{
    _LIT( KExample, "HomeNwAsyncL" );
    iLog->Log( KExample );
	TInt Err(PASS);
	
	__UHEAP_MARK;
	
	CHomeNetAsync* test = CHomeNetAsync::NewL(iLog);
	test->Start();
	Err = test->Result();
	delete test;
		
	__UHEAP_MARKEND;
	return Err;
	}
	

TInt  CTSysInfoProviderNetworkTests::CurrentNwNotiL(CStifItemParser& aItem)
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
	
