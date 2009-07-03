/*
* Copyright (c) 2006-2007 Nokia Corporation and/or its subsidiary(-ies).
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
#include "sendmessage.h"

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
// Csapi_sendmessage::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void Csapi_sendmessage::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// Csapi_sendmessage::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt Csapi_sendmessage::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
      
        ENTRY( "sendmessage_test1", Csapi_sendmessage::sendmessage_test1L ),
        ENTRY( "sendmessage_test2", Csapi_sendmessage::sendmessage_test2L ),
        ENTRY( "sendmessage_test3", Csapi_sendmessage::sendmessage_test3L ),
        ENTRY( "sendmessage_test4", Csapi_sendmessage::sendmessage_test4L ),
        ENTRY( "sendmessage_test5", Csapi_sendmessage::sendmessage_test5L ),
        ENTRY( "sendmessage_test6", Csapi_sendmessage::sendmessage_test6L ),
        ENTRY( "sendmessage_test7", Csapi_sendmessage::sendmessage_test7L ),
        ENTRY( "sendmessage_test8", Csapi_sendmessage::sendmessage_test8L ),
        ENTRY( "sendmessage_test9", Csapi_sendmessage::sendmessage_test9L ),
        ENTRY( "sendmessage_test10", Csapi_sendmessage::sendmessage_test10L ),

        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// Csapi_sendmessage::sendmessage1_testL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Csapi_sendmessage::sendmessage_test1L( CStifItemParser& /*aItem*/ )
    {
    return sendmessage_test1(0, NULL);
    }
// -----------------------------------------------------------------------------
// Csapi_sendmessage::sendmessage2_testL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Csapi_sendmessage::sendmessage_test2L( CStifItemParser& /*aItem*/ )
    {
    return sendmessage_test2(0, NULL);
    }
// -----------------------------------------------------------------------------
// Csapi_sendmessage::sendmessage3_testL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Csapi_sendmessage::sendmessage_test3L( CStifItemParser& /*aItem*/ )
    {
    return sendmessage_test3(0, NULL);
    }                               
// -----------------------------------------------------------------------------
// Csapi_sendmessage::sendmessage4_testL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Csapi_sendmessage::sendmessage_test4L( CStifItemParser& /*aItem*/ )
    {
    return sendmessage_test4(0, NULL);
    }    
// -----------------------------------------------------------------------------
// Csapi_sendmessage::sendmessage5_testL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Csapi_sendmessage::sendmessage_test5L( CStifItemParser& /*aItem*/ )
    {
    return sendmessage_test5(0, NULL);
    }    
// -----------------------------------------------------------------------------
// Csapi_sendmessage::sendmessage6_testL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Csapi_sendmessage::sendmessage_test6L( CStifItemParser& /*aItem*/ )
    {
    return sendmessage_test6(0, NULL);
    }    
// -----------------------------------------------------------------------------
// Csapi_sendmessage::sendmessage7_testL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Csapi_sendmessage::sendmessage_test7L( CStifItemParser& /*aItem*/ )
    {
    return sendmessage_test7(0, NULL);
    }    
// -----------------------------------------------------------------------------
// Csapi_sendmessage::sendmessage8_testL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Csapi_sendmessage::sendmessage_test8L( CStifItemParser& /*aItem*/ )
    {
    return sendmessage_test8(0, NULL);
    }    
// -----------------------------------------------------------------------------
// Csapi_sendmessage::sendmessage9_testL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Csapi_sendmessage::sendmessage_test9L( CStifItemParser& /*aItem*/ )
    {
    return sendmessage_test9(0, NULL);
    }    
// -----------------------------------------------------------------------------
// Csapi_sendmessage::sendmessage10_testL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Csapi_sendmessage::sendmessage_test10L( CStifItemParser& /*aItem*/ )
    {
    return sendmessage_test10(0, NULL);
    }    
// -----------------------------------------------------------------------------
// Csapi_sendmessage::?member_function
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
/*
TInt Csapi_sendmessage::?member_function(
   CItemParser& aItem )
   {

   ?code

   }
*/

// ========================== OTHER EXPORTED FUNCTIONS =========================
// None

//  End of File
