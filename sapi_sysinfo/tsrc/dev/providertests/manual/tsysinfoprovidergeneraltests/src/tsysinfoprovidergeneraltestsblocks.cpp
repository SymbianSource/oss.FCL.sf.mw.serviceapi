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
* Description:   tsysinfoprovidergeneraltestsblocks
*
*/




// INCLUDE FILES
#include <e32svr.h>
#include <StifParser.h>
#include <Stiftestinterface.h>
#include<f32file.h>
#include <Liwcommon.h>
#include<LiwServiceHandler.h>

#include "tsysinfoprovidergeneraltests.h"
#include "tuseractivitynotifier.h"
#include "Tmemnotifier.h"
#include "Tcriticalmemnoti.h"
#include "sysinfoservice.h"
#include "sysinfointerface.h"
#include"entitykeys.h"
#include "sysinfoaiwparams.hrh"

using namespace LIW ;
using namespace SysInfo;
using namespace sysinfoaiwparams;	

// -----------------------------------------------------------------------------
// CTSysInfoProviderGeneralTests::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTSysInfoProviderGeneralTests::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CTSysInfoProviderGeneralTests::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTSysInfoProviderGeneralTests::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "ConnectedAcc",    CTSysInfoProviderGeneralTests::ConnectedAcc),
        ENTRY( "ConnNotification",    CTSysInfoProviderGeneralTests::ConnNotification),
      	ENTRY( "AccessoryList",    CTSysInfoProviderGeneralTests::AccessoryList),

// connectivity
        ENTRY( "ConnectionList",    CTSysInfoProviderGeneralTests::ConnectionList),

		ENTRY( "MemoryCardNotifier-M",  CTSysInfoProviderGeneralTests::MemoryCardNotifierL),
		ENTRY( "CriticalMemOnDriveC-M",	CTSysInfoProviderGeneralTests::CriticalMemOnDriveCL),
		ENTRY( "CriticalMemOnDriveD-M",	CTSysInfoProviderGeneralTests::CriticalMemOnDriveDL),
		ENTRY( "CriticalMemOnDriveE-M",	CTSysInfoProviderGeneralTests::CriticalMemOnDriveEL),

		ENTRY( "UserActivityNotifier-M",  CTSysInfoProviderGeneralTests::UserActivityNotifierL),
		ENTRY( "UserInactivityNotifier",  CTSysInfoProviderGeneralTests::UserInactivityNotifierL)
        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }



	
// -----------------------------------------------------------------------------
// CTSysInfoProviderGeneralTests::ConnectedAcc
// 
// -----------------------------------------------------------------------------
//	
	
TInt  CTSysInfoProviderGeneralTests::ConnectedAcc(CStifItemParser& /*aItem*/)
	{

	_LIT( KExample, "ConnectedAcc:" );
    iLog->Log( KExample );
    	TInt 	err = KErrNone; 

	// On Emulator this is not supported.				
	#if (! (defined(__WINS__) || defined(__WINSCW__)) )

	__UHEAP_MARK;

	CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
	CleanupStack::PushL(iServiceHandler);
	
	CLiwGenericParamList* inparam = &(iServiceHandler->InParamListL());
	CLiwGenericParamList* outparam = &(iServiceHandler->OutParamListL());

	
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
		iLog->Log( _L("Interface loaded successfully") );
		TLiwGenericParam entity;
		TLiwVariant  entityname;
		TLiwGenericParam key;
		TLiwVariant  keyname;
		
		entityname.Set(KGeneral);
		entity.SetNameAndValueL(KEntity,entityname);

		keyname.Set(KConnectedAccessories);
		key.SetNameAndValueL(KKey,keyname);

		inparam->AppendL(entity);

		inparam->AppendL(key);
		
		entity.Reset();
		entityname.Reset();
		key.Reset();
		keyname.Reset();
        
        iLog->Log( _L("Calling Getinfo") );
		TRAP(err,	interface->ExecuteCmdL(KGetInfo,*inparam,*outparam));
		
		pos = 0 ;
	    const TLiwGenericParam* output = outparam->FindFirst( pos,KErrorCode );
		if(pos != KErrNotFound)
		{
			err = (TInt)((*outparam)[pos].Value().AsTInt32());
		}

		if(err >= KErrNone)
			{
			pos = 0 ;
		    
		    const TLiwGenericParam* output = outparam->FindFirst( pos,KReturnValue );
		
				
			if(output)     
				{
				iLog->Log( _L("KReturnValue found") );
				const CLiwMap* Map = output->Value().AsMap(); 
				if ( Map )
					{
					TLiwVariant data;
					Map->FindL(KAccessoryList,data);
					CLiwIterable* iterlist=data.AsIterable();
					
					TInt32 testacctype= 0,testaccstatus= 0;
		      		if(iterlist)
			      		{
			      		TLiwVariant iterdata;
			      		TInt count=0;
			      		while(iterlist->NextL(iterdata))
			      			{
							count++;
							const CLiwMap* Map = iterdata.AsMap(); 
							if ( Map )
								{
								TLiwVariant acctype;
								if (Map->FindL(KAccessoryType,acctype))
    								{
    						    	testacctype = acctype.AsTInt32();
    								TBuf<50> buf=_L("Accessory Type: ");
    				 				buf.AppendNum(testacctype);
    				 				iLog->Log(buf);
    								acctype.Reset();
    								}
    							else
    							    {
    							    iLog->Log( _L("KAccessoryType not found") );
    							    }

								
								TLiwVariant accstatus;
								if(Map->FindL(KAccessoryState,accstatus))
    								{
    								TBuf<50> buf=_L("Accessory Status: ");
    				 				TInt32 testaccstatus = accstatus.AsTInt32();
    								buf.AppendNum(testaccstatus);
    				 				iLog->Log(buf);
    								}
    							else
    							    {
    							    iLog->Log( _L("KAccessoryStatus not found") );
    							    }    								
								}
			      			}
			      		iLog->Log( _L("Connected accessory count: %d"), count);
			      		iterdata.Reset();	
						}
					data.Reset();
					}//map
				}
			}//err
		}//interface
	else
	    {
	    iLog->Log( _L("Interface load failed") );
	    }
	
	inparam->Reset();
	outparam->Reset();
		
	interface->Close();
	
	CleanupStack::PopAndDestroy( iServiceHandler );

	__UHEAP_MARKEND;
	#endif
	return err;

	
	}	
	
// -----------------------------------------------------------------------------
// CTSysInfoProviderGeneralTests::ConnNotification
// 
// -----------------------------------------------------------------------------
//		
TInt  CTSysInfoProviderGeneralTests::ConnNotification(CStifItemParser& /*aItem*/)
	{
	
	_LIT( KExample, "ConnNotification" );
    iLog->Log( KExample );
    
    int ret=0;
	// On Emulator this is not supported.				
//	#if (! (defined(__WINS__) || defined(__WINSCW__)) )

    ret = ConnectionNotification(iLog);
//    #endif
    
    if(ret==0)
			return KErrNone;
		else	
			return KErrGeneral;
	}

TInt  CTSysInfoProviderGeneralTests::MemoryCardNotifierL(CStifItemParser& /*aItem*/)
	{	
    _LIT( KExample, "MemoryCardNotifierL" );
    iLog->Log( KExample );
	TInt RetVal(PASS);
	TInt32 Err(PASS);
#if ( !(defined(__WINS__) || defined(__WINSCW__)) )	
	__UHEAP_MARK;

	CTestMemNotification* test = CTestMemNotification::NewL(iLog);
	test->Start();
	Err |= test->Result();
	delete test;

	__UHEAP_MARKEND;
#endif
	return Err;
	}

TInt  CTSysInfoProviderGeneralTests::CriticalMemOnDriveCL(CStifItemParser& /*aItem*/)
	{	
    _LIT( KExample, "CriticalMemOnDriveCL" );
    iLog->Log( KExample );
	TInt RetVal(PASS);
#if ( !(defined(__WINS__) || defined(__WINSCW__)) )	
	__UHEAP_MARK;

	CTCriticalMemNotification* test = CTCriticalMemNotification::NewL(iLog,EDriveC);
	test->Start();
	RetVal = test->Result();
	delete test;
	
	
	__UHEAP_MARKEND;
#endif
	return RetVal;
	}	

TInt  CTSysInfoProviderGeneralTests::CriticalMemOnDriveDL(CStifItemParser& /*aItem*/)
	{	
    _LIT( KExample, "CriticalMemOnDriveDL" );
    iLog->Log( KExample );
	TInt RetVal(PASS);
#if ( !(defined(__WINS__) || defined(__WINSCW__)) )	
	__UHEAP_MARK;

	CTCriticalMemNotification* test = CTCriticalMemNotification::NewL(iLog,EDriveD);
	test->Start();
	RetVal = test->Result();
	delete test;
	
	__UHEAP_MARKEND;
#endif
	return RetVal;
	}	


TInt  CTSysInfoProviderGeneralTests::CriticalMemOnDriveEL(CStifItemParser& /*aItem*/)
	{	
    _LIT( KExample, "CriticalMemOnDriveEL" );
    iLog->Log( KExample );
	TInt RetVal(PASS);
#if ( !(defined(__WINS__) || defined(__WINSCW__)) )	
	__UHEAP_MARK;

	CTCriticalMemNotification* test = CTCriticalMemNotification::NewL(iLog,EDriveE);
	test->Start();
	RetVal = test->Result();
	delete test;
	
	__UHEAP_MARKEND;
#endif
	return RetVal;
	}	

TInt  CTSysInfoProviderGeneralTests::UserActivityNotifierL(CStifItemParser& )
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

TInt  CTSysInfoProviderGeneralTests::UserInactivityNotifierL(CStifItemParser& )
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
	
// -----------------------------------------------------------------------------
// Ctsysinfoprovidertests::ConnectionList
// checking for the iterator behaviour
//
// -----------------------------------------------------------------------------
//		
TInt  CTSysInfoProviderGeneralTests::ConnectionList(CStifItemParser& /*aItem*/)
	{
	int ret=0;
	// On Emulator this is not supported.				
//	#if (! (defined(__WINS__) || defined(__WINSCW__)) )

    ret = ConnList(iLog);
//    #endif
    
    if(ret==0)
			return KErrNone;
		else	
			return KErrGeneral;
	}

// -----------------------------------------------------------------------------
// Ctsysinfoprovidertests::ConnectionList
// checking for the iterator behaviour
//
// -----------------------------------------------------------------------------
//		
TInt  CTSysInfoProviderGeneralTests::AccessoryList(CStifItemParser& /*aItem*/)
	{
	int ret=0;
	// On Emulator this is not supported.				
	#if (! (defined(__WINS__) || defined(__WINSCW__)) )

    ret = AccIter(iLog);
    #endif
    
    if(ret==0)
			return KErrNone;
		else	
			return KErrGeneral;
	}

	
//End of file
				
	