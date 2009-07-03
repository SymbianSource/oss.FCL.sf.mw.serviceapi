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
#include "getheader.h"

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
// Csapi_getheader::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void Csapi_getheader::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// Csapi_getheader::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt Csapi_getheader::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
      
       ENTRY( "getheader_test1", Csapi_getheader::getheader_test1L ),
       ENTRY( "getheader_test2", Csapi_getheader::getheader_test2L ),
       ENTRY( "getheader_test3", Csapi_getheader::getheader_test3L ),
       ENTRY( "getheader_test4", Csapi_getheader::getheader_test4L ),
       ENTRY( "getheader_test5", Csapi_getheader::getheader_test5L ),
       ENTRY( "getheader_test6", Csapi_getheader::getheader_test6L ),
       ENTRY( "getheader_test7", Csapi_getheader::getheader_test7L ),

        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// Csapi_getheader::getheader1_testL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Csapi_getheader::getheader_test1L( CStifItemParser& /*aItem*/ )
    {
 		int ret=0;
    ret = getheader_test1(0, NULL);
    
    if(ret==0)
			return KErrNone;
		else	
			return KErrGeneral;

    }
// -----------------------------------------------------------------------------
// Csapi_getheader::getheader2_testL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Csapi_getheader::getheader_test2L( CStifItemParser& /*aItem*/ )
  {
 		int ret=0;
    ret = getheader_test2(0, NULL);
    
    if(ret==0)
			return KErrNone;
		else	
			return KErrGeneral;

    }
// -----------------------------------------------------------------------------
// Csapi_getheader::getheader3_testL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Csapi_getheader::getheader_test3L( CStifItemParser& /*aItem*/ )
  {
 		int ret=0;
    ret = getheader_test3(0, NULL);
    
    if(ret==0)
			return KErrNone;
		else	
			return KErrGeneral;

    }
 // -----------------------------------------------------------------------------
// Csapi_getheader::getheader4_testL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Csapi_getheader::getheader_test4L( CStifItemParser& /*aItem*/ )
  {
 		int ret=0;
    ret = getheader_test4(0, NULL);
    
    if(ret==0)
			return KErrNone;
		else	
			return KErrGeneral;

    }   
 // -----------------------------------------------------------------------------
// Csapi_getheader::getheader4_testL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Csapi_getheader::getheader_test5L( CStifItemParser& /*aItem*/ )
  {
 		int ret=0;
    ret = getheader_test5(0, NULL);
    
    if(ret==0)
			return KErrNone;
		else	
			return KErrGeneral;

    }   
     // -----------------------------------------------------------------------------
// Csapi_getheader::getheader4_testL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Csapi_getheader::getheader_test6L( CStifItemParser& /*aItem*/ )
  {
 		int ret=0;
    ret = getheader_test6(0, NULL);
    
    if(ret==0)
			return KErrNone;
		else	
			return KErrGeneral;

    }  
     // -----------------------------------------------------------------------------
// Csapi_getheader::getheader4_testL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Csapi_getheader::getheader_test7L( CStifItemParser& /*aItem*/ )
  {
 		int ret=0;
    ret = getheader_test7(0, NULL);
    
    if(ret==0)
			return KErrNone;
		else	
			return KErrGeneral;

    }        
// -----------------------------------------------------------------------------
// Csapi_getheader::?member_function
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
/*
TInt Csapi_getheader::?member_function(
   CItemParser& aItem )
   {

   ?code

   }
*/

// ========================== OTHER EXPORTED FUNCTIONS =========================
// None

//  End of File
