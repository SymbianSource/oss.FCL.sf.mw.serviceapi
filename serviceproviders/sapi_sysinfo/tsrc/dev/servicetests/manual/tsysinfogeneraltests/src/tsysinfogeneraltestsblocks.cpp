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
* Description:   tsysinfogeneraltestsblocks
*
*/




// INCLUDE FILES
#include <e32svr.h>
#include <StifParser.h>
#include <StifTestInterface.h>
#include<f32file.h>

#include "tsysinfogeneraltests.h"
#include "tuseractivitynotifier.h"
#include "tcriticalmemnoti.h"
#include "tmemnotifier.h"
#include"tautolocknotifier.h"
#include "sysinfoservice.h"
#include"entitykeys.h"

using namespace SysInfo;
// -----------------------------------------------------------------------------
// CTSysInfoGeneralTests::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTSysInfoGeneralTests::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CTSysInfoGeneralTests::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTSysInfoGeneralTests::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "ConnectedAcc",    CTSysInfoGeneralTests::ConnectedAcc),
        ENTRY( "AccStatus",    CTSysInfoGeneralTests::AccStatus),
        ENTRY( "FlipStatus",    CTSysInfoGeneralTests::FlipStatus),
        ENTRY( "GripStatus",    CTSysInfoGeneralTests::GripStatus),
        ENTRY( "ActiveUSBModes",    CTSysInfoGeneralTests::ActiveUSBModes),
        
        ENTRY( "GetActiveConnections",    CTSysInfoGeneralTests::GetActiveConnections),
        ENTRY( "ConnNotification",    CTSysInfoGeneralTests::ConnNotification),

//MEMORY
		ENTRY( "MemoryCardNotifier-M",  CTSysInfoGeneralTests::MemoryCardNotifierL),
		ENTRY( "CriticalMemOnDriveC-M",  CTSysInfoGeneralTests::CriticalMemOnDriveCL),        
		ENTRY( "CriticalMemOnDriveD-M",  CTSysInfoGeneralTests::CriticalMemOnDriveDL),
		ENTRY( "CriticalMemOnDriveE-M",  CTSysInfoGeneralTests::CriticalMemOnDriveEL),
//DISPLAY		
		ENTRY( "UserActivityNotifier-M",  CTSysInfoGeneralTests::UserActivityNotifierL), 
		ENTRY( "AutoLockNotifier",  	CTSysInfoGeneralTests::AutoLockNotifierL),
        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }




// -----------------------------------------------------------------------------
// CTSysInfoGeneralTests::AccStatus
// 
// -----------------------------------------------------------------------------
//		

TInt  CTSysInfoGeneralTests::AccStatus(CStifItemParser& /*aItem*/)
	{
	_LIT( KExample, "AccStatus" );
    iLog->Log( KExample );
    
	int ret=0;
	// On Emulator this is not supported.				
	#if (! (defined(__WINS__) || defined(__WINSCW__)) )

    ret = AccStatusNotification(iLog);
    
    #endif
    if(ret==0)
		return KErrNone;
	else	
		return KErrGeneral;
	}

// -----------------------------------------------------------------------------
// CTSysInfoGeneralTests::FlipStatus
// 
// -----------------------------------------------------------------------------
//		
TInt  CTSysInfoGeneralTests::FlipStatus(CStifItemParser& /*aItem*/)
	{	int ret=0;
	// On Emulator this is not supported.				
	#if (! (defined(__WINS__) || defined(__WINSCW__)) )

    ret = FlipNotification();
    #endif
    
    if(ret==0)
		return KErrNone;
	else	
		return KErrGeneral;
	}

// -----------------------------------------------------------------------------
// CTSysInfoGeneralTests::GripStatus
// 
// -----------------------------------------------------------------------------
//		
TInt  CTSysInfoGeneralTests::GripStatus(CStifItemParser& /*aItem*/)
	{	int ret=0;
	// On Emulator this is not supported.				
	#if (! (defined(__WINS__) || defined(__WINSCW__)) )

    ret = GripNotification();
    #endif
    
    if(ret==0)
		return KErrNone;
	else	
		return KErrGeneral;
	}

// -----------------------------------------------------------------------------
// CTSysInfoGeneralTests::ActiveUSBModes
// 
// -----------------------------------------------------------------------------
//	
TInt  CTSysInfoGeneralTests::ActiveUSBModes(CStifItemParser& /*aItem*/)
	{
	TInt result = KErrNone;
	TPtrC activeUsbmode;
	
	// On Emulator this is not supported.				
	#if (! (defined(__WINS__) || defined(__WINSCW__)) )


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
// CTSysInfoGeneralTests::AutoLockNotifierL
// 
// -----------------------------------------------------------------------------
//	
TInt  CTSysInfoGeneralTests::AutoLockNotifierL(CStifItemParser& )
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
// -----------------------------------------------------------------------------
// CTSysInfoGeneralTests::ConnectedAcc
// 
// -----------------------------------------------------------------------------
//	
	
TInt  CTSysInfoGeneralTests::ConnectedAcc(CStifItemParser& /*aItem*/)
	{
	TInt result = KErrNone;
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
// CTSysInfoGeneralTests::GetActiveConnections
// 
// -----------------------------------------------------------------------------
//	
TInt  CTSysInfoGeneralTests::GetActiveConnections(CStifItemParser& /*aItem*/)
	{
	_LIT( KExample, "GetActiveConnections" );
    iLog->Log( KExample );
    
	int ret=0;

	// On Emulator this is not supported.				
	#if (! (defined(__WINS__) || defined(__WINSCW__)) )

    ret = ActiveConnection(iLog);
   	#endif
 
    if(ret==0)
			return KErrNone;
		else	
			return KErrGeneral;
		}

	
// -----------------------------------------------------------------------------
// CTSysInfoGeneralTests::ConnNotification
// 
// -----------------------------------------------------------------------------
//

TInt  CTSysInfoGeneralTests::ConnNotification(CStifItemParser& /*aItem*/)
	{
	
	_LIT( KExample, "ConnNotification" );
    iLog->Log( KExample );
    
    int ret=0;
	// On Emulator this is not supported.				
	#if (! (defined(__WINS__) || defined(__WINSCW__)) )

    ret = ConnectionNotification(iLog);
   	#endif
   	
    if(ret==0)
			return KErrNone;
		else	
			return KErrGeneral;
		}
				
TInt  CTSysInfoGeneralTests::MemoryCardNotifierL(CStifItemParser& /*aItem*/)
	{	
    _LIT( KExample, "MemoryCardNotifierL" );
    iLog->Log( KExample );
	TInt Err(PASS);
#if ( !(defined(__WINS__) || defined(__WINSCW__)) )	
	TestModuleIf().Printf( 1, _L("Waiting"), _L("Waiting") );	
	__UHEAP_MARK;

	CTestMemNotification* test = CTestMemNotification::NewL(iLog);
	test->Start();
	Err = test->Result();
	delete test;
		
	__UHEAP_MARKEND;
#endif
	return Err;
	}	
	
TInt  CTSysInfoGeneralTests::CriticalMemOnDriveCL(CStifItemParser& /*aItem*/)
	{	
    _LIT( KExample, "CriticalMemOnDriveCL" );
    iLog->Log( KExample );
	TInt Err(PASS);
	
#if ( !(defined(__WINS__) || defined(__WINSCW__)) )	
	__UHEAP_MARK;

	CTCriticalMemNotification* test = CTCriticalMemNotification::NewL(iLog,EDriveC);
	test->Start();
	Err = test->Result();
	delete test;
		
	__UHEAP_MARKEND;
#endif

	return Err;
	}	

TInt  CTSysInfoGeneralTests::CriticalMemOnDriveDL(CStifItemParser& /*aItem*/)
	{	
    _LIT( KExample, "CriticalMemOnDriveDL" );
    iLog->Log( KExample );
	TInt Err(PASS);
#if ( !(defined(__WINS__) || defined(__WINSCW__)) )	
	__UHEAP_MARK;

	CTCriticalMemNotification* test = CTCriticalMemNotification::NewL(iLog,EDriveD);
	test->Start();
	Err = test->Result();
	delete test;
		
	__UHEAP_MARKEND;
#endif
	return Err;
	}	

TInt  CTSysInfoGeneralTests::CriticalMemOnDriveEL(CStifItemParser& /*aItem*/)
	{	
    _LIT( KExample, "CriticalMemOnDriveDL" );
    iLog->Log( KExample );
	TInt Err(PASS);
#if ( !(defined(__WINS__) || defined(__WINSCW__)) )	
	__UHEAP_MARK;

	CTCriticalMemNotification* test = CTCriticalMemNotification::NewL(iLog,EDriveE);
	test->Start();
	Err = test->Result();
	delete test;
		
	__UHEAP_MARKEND;
#endif
	return Err;
	}	

TInt  CTSysInfoGeneralTests::UserActivityNotifierL(CStifItemParser& )
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
	
