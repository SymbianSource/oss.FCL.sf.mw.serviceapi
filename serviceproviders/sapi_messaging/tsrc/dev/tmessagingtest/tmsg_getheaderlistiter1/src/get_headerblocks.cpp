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
#include <StifTestInterface.h>
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
// Csapi_getheader:Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void Csapi_getheader::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// Csapi_getheader:RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt Csapi_getheader::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
         ENTRY( "getheader_test1", Csapi_getheader::getheader_test1L ),
         ENTRY( "getheader_test2", Csapi_getheader::getheader_test2L ),
         ENTRY( "getheader_test3", Csapi_getheader::getheader_test3L ),
         ENTRY( "getheadermms_test1", Csapi_getheader::getheadermms_test1L ),
         ENTRY( "getheadermms_test2", Csapi_getheader::getheadermms_test2L ),
         ENTRY( "getheadersmsasync_test4", Csapi_getheader::getheadersmsasync_test4L ),
         ENTRY( "getheadermmsasync_test3", Csapi_getheader::getheadermmsasync_test3L )
        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// Csapi_getheader:getheader1_testL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Csapi_getheader::getheader_test1L( CStifItemParser&  )
    {
 		int ret=0;
    ret = getheader_test1(0, NULL);
    
    if(ret==0)
			return KErrNone;
		else	
			return KErrGeneral;

    }
// -----------------------------------------------------------------------------
// Csapi_getheader:getheader2_testL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//

TInt Csapi_getheader::getheader_test2L( CStifItemParser&  )
    {
 		int ret=0;
    ret = getheader_test2(0, NULL);
    
    if(ret==0)
			return KErrNone;
		else	
			return KErrGeneral;

    }
// -----------------------------------------------------------------------------
// Csapi_getheader:getheader3_testL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//

TInt Csapi_getheader::getheader_test3L( CStifItemParser&  )
    {
 		int ret=0;
    ret = getheader_test3(0, NULL);
    
    if(ret==0)
			return KErrNone;
		else	
			return KErrGeneral;

    }    
// -----------------------------------------------------------------------------
// Csapi_getheader:getheadermms_test1L
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Csapi_getheader::getheadermms_test1L( CStifItemParser&  )
    {
 		int ret=0;
    ret = getheadermms_test1(0, NULL);
    
    if(ret==0)
			return KErrNone;
		else	
			return KErrGeneral;

    }    
// -----------------------------------------------------------------------------
// Csapi_getheader:getheadermms_test2L
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Csapi_getheader::getheadermms_test2L( CStifItemParser&  )
    {
 		int ret=0;
    ret = getheadermms_test2(0, NULL);
    
    if(ret==0)
			return KErrNone;
		else	
			return KErrGeneral;

    }  
// -----------------------------------------------------------------------------
// Csapi_getheader:getheadersmsasync_test4L
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Csapi_getheader::getheadersmsasync_test4L( CStifItemParser&  )
    {
        int ret=0;
    ret = getheadersmsasync_test4(0, NULL);
    
    if(ret==0)
            return KErrNone;
        else    
            return KErrGeneral;

    }
// -----------------------------------------------------------------------------
// Csapi_getheader:getheadermmsasync_test3L
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Csapi_getheader::getheadermmsasync_test3L( CStifItemParser&  )
    {
        int ret=0;
    ret = getheadermmsasync_test3(0, NULL);
    
    if(ret==0)
            return KErrNone;
        else    
            return KErrGeneral;

    }


/*  
// -----------------------------------------------------------------------------
// Csapi_getheader:getheader6_testL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Csapi_getheader::getheader_test6L( CStifItemParser&  )
    {
 		int ret=0;
    ret = getheader_test6(0, NULL);
    
    if(ret==0)
			return KErrNone;
		else	
			return KErrGeneral;

    }    
// -----------------------------------------------------------------------------
// Csapi_getheader:getheader7_testL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Csapi_getheader::getheader_test7L( CStifItemParser&  )
    {
 		int ret=0;
    ret = getheader_test7(0, NULL);
    
    if(ret==0)
			return KErrNone;
		else	
			return KErrGeneral;

    }    
// -----------------------------------------------------------------------------
// Csapi_getheader:getheader8_testL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Csapi_getheader::getheader_test8L( CStifItemParser&  )
    {
 		int ret=0;
    ret = getheader_test8(0, NULL);
    
    if(ret==0)
			return KErrNone;
		else	
			return KErrGeneral;

    }    
// -----------------------------------------------------------------------------
// Csapi_getheader:getheader9_testL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Csapi_getheader::getheader_test9L( CStifItemParser&  )
    {
 		int ret=0;
    ret = getheader_test9(0, NULL);
    
    if(ret==0)
			return KErrNone;
		else	
			return KErrGeneral;

    }    
// -----------------------------------------------------------------------------
// Csapi_getheader:getheader10_testL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Csapi_getheader::getheader_test10L( CStifItemParser&  )
    {
 		int ret=0;
    ret = getheader_test10(0, NULL);
    
    if(ret==0)
			return KErrNone;
		else	
			return KErrGeneral;

    }    
// -----------------------------------------------------------------------------
// Csapi_getheader:getheader11_testL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Csapi_getheader::getheader_test11L( CStifItemParser&  )
    {
 		int ret=0;
    ret = getheader_test11(0, NULL);
    
    if(ret==0)
			return KErrNone;
		else	
			return KErrGeneral;

    }    
// -----------------------------------------------------------------------------
// Csapi_getheader:getheader12_testL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Csapi_getheader::getheader_test12L( CStifItemParser&  )
    {
 		int ret=0;
    ret = getheader_test12(0, NULL);
    
    if(ret==0)
			return KErrNone;
		else	
			return KErrGeneral;

    }                                        
// -----------------------------------------------------------------------------
// Csapi_getheader:getheader13_testL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Csapi_getheader::getheader_test13L( CStifItemParser&  )
    {
 		int ret=0;
    ret = getheader_test13(0, NULL);
    
    if(ret==0)
			return KErrNone;
		else	
			return KErrGeneral;

    }                                        
// -----------------------------------------------------------------------------
// Csapi_getheader:getheader14_testL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Csapi_getheader::getheader_test14L( CStifItemParser&  )
    {
 		int ret=0;
    ret = getheader_test14(0, NULL);
    
    if(ret==0)
			return KErrNone;
		else	
			return KErrGeneral;

    }                                        
// -----------------------------------------------------------------------------
// Csapi_getheader:getheader15_testL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Csapi_getheader::getheader_test15L( CStifItemParser&  )
    {
 		int ret=0;
    ret = getheader_test15(0, NULL);
    
    if(ret==0)
			return KErrNone;
		else	
			return KErrGeneral;

    }                                        
// -----------------------------------------------------------------------------
// Csapi_getheader:getheader16_testL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Csapi_getheader::getheader_test16L( CStifItemParser&  )
    {
 		int ret=0;
    ret = getheader_test16(0, NULL);
    
    if(ret==0)
			return KErrNone;
		else	
			return KErrGeneral;

    }                                        
// -----------------------------------------------------------------------------
// Csapi_getheader:getheader17_testL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Csapi_getheader::getheader_test17L( CStifItemParser&  )
    {
 		int ret=0;
    ret = getheader_test17(0, NULL);
    
    if(ret==0)
			return KErrNone;
		else	
			return KErrGeneral;

    }                                        
// -----------------------------------------------------------------------------
// Csapi_getheader:getheader18_testL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Csapi_getheader::getheader_test18L( CStifItemParser&  )
    {
 		int ret=0;
    ret = getheader_test18(0, NULL);
    
    if(ret==0)
			return KErrNone;
		else	
			return KErrGeneral;

    }                                        
// -----------------------------------------------------------------------------
// Csapi_getheader:getheader19_testL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Csapi_getheader::getheader_test19L( CStifItemParser&  )
    {
 		int ret=0;
    ret = getheader_test19(0, NULL);
    
    if(ret==0)
			return KErrNone;
		else	
			return KErrGeneral;

    }    */                                    
   
// -----------------------------------------------------------------------------
// Csapi_getheader:?member_function
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
/*
TInt Csapi_getheader:?member_function(
   CItemParser& aItem )
   {

   ?code

   }
*/

// ========================== OTHER EXPORTED FUNCTIONS =========================
// None

//  End of File
