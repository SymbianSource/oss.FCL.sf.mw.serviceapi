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
* Description:   Tests sysinfo battery information
*
*/




// INCLUDE FILES
#include <e32svr.h>
#include <StifParser.h>
#include <Stiftestinterface.h>
#include "tsysbattery.h"
#include "tsysbatterystrengthasync.h"
#include "tsysbatterynot.h"

using namespace SysInfo;

// EXTERNAL DATA STRUCTURES
//extern  ?external_data;

// EXTERNAL FUNCTION PROTOTYPES  
//extern ?external_function( ?arg_type,?arg_type );

// CONSTANTS
//const ?type ?constant_var = ?constant;

// MACROS
//#define ?macro ?macro_def

// LOCAL CONSTANTS AND MACROS
//const ?type ?constant_var = ?constant;
//#define ?macro_name ?macro_def

// MODULE DATA STRUCTURES
//enum ?declaration
//typedef ?declaration

// LOCAL FUNCTION PROTOTYPES
//?type ?function_name( ?arg_type, ?arg_type );

// FORWARD DECLARATIONS
//class ?FORWARD_CLASSNAME;

// ============================= LOCAL FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// ?function_name ?description.
// ?description
// Returns: ?value_1: ?description
//          ?value_n: ?description_line1
//                    ?description_line2
// -----------------------------------------------------------------------------
//
/*
?type ?function_name(
    ?arg_type arg,  // ?description
    ?arg_type arg)  // ?description
    {

    ?code  // ?comment

    // ?comment
    ?code
    }
*/

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctsysbattery::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void Ctsysbattery::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// Ctsysbattery::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt Ctsysbattery::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
       
		ENTRY( "WrongKey", Ctsysbattery::WrongKey ),
		ENTRY( "BatteryLevelAsync", Ctsysbattery::BatteryLevelAsync ),
		ENTRY( "BatteryNotWrongData", Ctsysbattery::BatteryNotWrongData ),
		ENTRY( "BatteryNotWrongKey", Ctsysbattery::BatteryNotWrongKey ),
       };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }


// -----------------------------------------------------------------------------
// Ctsysbattery::WrongKey
// Test for wrong key input values
// -----------------------------------------------------------------------------
//
TInt Ctsysbattery::WrongKey( CStifItemParser& /*aItem*/ )
    {

     __UHEAP_MARK;
    
    _LIT(KEntity,"Battery") ;
    _LIT(KKey,"StatusCharging") ;
    
    TInt returnCode = KErrNone ;
        
    CSysInfoService *CoreObj = CSysInfoService :: NewL() ;
    
    if( NULL == CoreObj)
	    {
	    iLog->Log(_L8("Failed.. @Core")) ;
	   	return KErrGeneral ;
	   	}

    CSysData *sysData ;
       
    TRAPD(leaveCode, CoreObj->GetInfoL(KEntity,KKey,sysData)) ;
    if(KErrNotFound == leaveCode)
    	{
    	iLog->Log(_L8("Passed..")) ;
    	}
	else
		{
		returnCode = KErrGeneral ;	
		iLog->Log(_L8("Failed..")) ;
		}    
    
    delete CoreObj ;

    __UHEAP_MARKEND ;
    return returnCode ;
    
    }
    
// -----------------------------------------------------------------------------
// Ctsysbattery::BatteryLevelAsync
// Tests Getinfo() for battery level information throws KErrNotSupported
// -----------------------------------------------------------------------------
//
TInt Ctsysbattery::BatteryLevelAsync( CStifItemParser& /*aItem*/ )
    {
   	TInt Err ;
    TInt returnCode = KErrNone ;   
	
	__UHEAP_MARK;

	CBatteryStrengthAsync* test = CBatteryStrengthAsync::NewL(iLog);
	test->Start();
	Err = test->Result();
	delete test;
    
    if( KErrNotFound == Err )
		returnCode = KErrNone ;
    else
    	returnCode = KErrGeneral ;
	
	
	__UHEAP_MARKEND ;
	return returnCode ;
    
    }


// -----------------------------------------------------------------------------
// Ctsysbattery::BatteryNotWrongData
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctsysbattery::BatteryNotWrongData( CStifItemParser& /*aItem*/ )
    {
   	TInt Err = KErrNone ;
   	TInt returnCode = KErrNone ;
	
	__UHEAP_MARK;

	CBatteryNot *test = CBatteryNot::NewL(iLog, 0);
	test->Start();
	Err = test->Result();
	delete test;
   
    if(KErrArgument != Err)
    returnCode = KErrGeneral ; 
   
	__UHEAP_MARKEND;
	return returnCode ;

    
    }
    

// -----------------------------------------------------------------------------
// Ctsysbattery::BatteryNotWrongKey
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctsysbattery::BatteryNotWrongKey( CStifItemParser& /*aItem*/ )
    {
   	TInt Err = KErrNone ;
   	TInt returnCode = KErrNone ;
	
	__UHEAP_MARK;

	CBatteryNot *test = CBatteryNot::NewL(iLog, 1);
	test->Start();
	Err = test->Result();
	delete test;
   
    if(KErrNotFound != Err)
    returnCode = KErrGeneral ; 
   
	__UHEAP_MARKEND;
	return returnCode ;

    
    }


// -----------------------------------------------------------------------------
// Ctsysbattery::?member_function
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
/*
TInt Ctsysbattery::?member_function(
   CItemParser& aItem )
   {

   ?code

   }
*/

// ========================== OTHER EXPORTED FUNCTIONS =========================
// None

//  End of File
