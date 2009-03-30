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
* Description:  ?Description
*
*/



// INCLUDE FILES
#include <e32svr.h>
#include <StifParser.h>
#include <Stiftestinterface.h>
#include <LiwServiceHandler.h>
#include <Liwbufferextension.h>
#include "appmanagertest.h"
#include <appmanagerservice.h>
#include <appmanagercommon.h>
#include <f32file.h>
#include <e32des16.h>
#include <e32base.h>


#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <unistd.h>
#include <cliwbinding.h>


const TInt KDocMaxDigitsInHexString = 8; // 32 bits.

static const wchar_t *DOCUMENTNAME  = L"C:\\data\\Hello.txt";
static const wchar_t *MIMETYPE      = L"audio/mpeg";


#include "testappobserver.h"

_LIT8(KContent,"Type");
_LIT8(KDocumentPath,"DocumentPath");
_LIT8(KMimeType,"MimeType");
_LIT8(KMode,"Mode");
_LIT8(KPostion,"Position");
_LIT8(KHandle,"Handle");
_LIT8(KDocument,"Document");
_LIT(KNull,"NULL");

_LIT8(KService, "Service.AppManager");
_LIT8(KIAppManager,"IAppManager");
_LIT8(KTransactionID,"TransactionID");
_LIT8(KCmdLine,"CmdLine");

_LIT8(KApplicationID,"ApplicationID");
_LIT8(KDocumentName,"DocumentName");

//Supported Operation
_LIT8(KGetList,  "GetList");
_LIT8(KLaunchApp,"LaunchApp");
_LIT8(KLaunchDoc,"LaunchDoc");

_LIT8(KResponse,"ReturnValue");
_LIT8(KErrorCode,"ErrorCode");
_LIT8(KOptions,"Options");

// Filter Map
_LIT8(KFilter,"Filter");


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
void CAppManagerTest::Delete()
    {

    }

// -----------------------------------------------------------------------------
// Csapi_getheader:RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CAppManagerTest::RunMethodL(
    CStifItemParser& aItem )
    {

    static TStifFunctionInfo const KFunctions[] =
        {
         ENTRY( "getlisttest", CAppManagerTest::getlisttestL ),
        };

    const TInt count = sizeof( KFunctions ) /
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CAppManagerTest:getlistapplication1_testL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CAppManagerTest::getlisttestL( CStifItemParser& aItem  )
    {

    __UHEAP_MARK;
 	TPtrC16 content;
 	TPtrC16 docname;
 	TPtrC16 mimetype16;
 	TInt expected;
 	TInt noOfmaps;
 	TPtrC16 filename;
 	TInt result =KErrNone ;// KErrGeneral; // 0 means pass and -1 means Fail

 	aItem.GetNextString(content);
 	aItem.GetNextString(docname);
 	aItem.GetNextString(mimetype16);
 	aItem.GetNextInt(expected);
 	aItem.GetNextString(filename);
 	aItem.GetNextInt(noOfmaps);

    iLog->Log(_L("read varibale "));

/*--------------------------------------C Runtime Code ----------------------------------------*/

    	
	const char *service_name   = "Service.AppManager";
	const char *interface_name = "IAppManager";
  	void *interface_handle = NULL;	
   	//cbindingattach(); // Attach to binding
	
	// Load Serive and interface handle
    interface_handle = loadservice( service_name, interface_name ); // Got interface
	
	if( interface_handle )
	    {
	     // Got Interface
	     GValue outparam;
	    
	     const char *operation1 = "GetList";	
	     TInt error = KErrNone;
	     
	     GValue result,result3;

         //	GValue map1 ;
	     int rescnt;	
	     GType type;
	     GValue resmap;
	     GValue filterMap;
	     GValue foundvalue;
	     TInt cErr;
	     char keyfound[20];
	     
	
	
	    // Filter Map Creation 
	    if(( docname.CompareF(_L("NULL")) != 0  ) && (mimetype16.CompareF(_L("NULL")) != 0) )
	        {
	        map_construct( &filterMap , G_BINDING_DERIVED_TYPE_UNICODE , "DocumentName", DOCUMENTNAME , 
	                       G_BINDING_DERIVED_TYPE_UNICODE,  "MimeType" , MIMETYPE, 
			               G_TYPE_INVALID );	

	        }
	    
	 
	     else if(docname.CompareF(_L("NULL")) != 0 )
		    {
		    map_construct( &filterMap , G_BINDING_DERIVED_TYPE_UNICODE , "DocumentName", DOCUMENTNAME , 
	                       G_TYPE_INVALID );	

	 	    }


	     else if (mimetype16.CompareF(_L("NULL")) != 0)
		    {
		    map_construct( &filterMap ,G_BINDING_DERIVED_TYPE_UNICODE,  "MimeType"      , MIMETYPE       , 
			               G_TYPE_INVALID );	

		    }
	    
	
	    
	     if(( docname.CompareF(_L("NULL")) != 0  ) || (mimetype16.CompareF(_L("NULL")) != 0) )
	        {
	
             // Request Service	with Filter 		                      
	         requestservice(interface_handle, operation1, 
	         G_BINDING_DERIVED_TYPE_UNICODE, "Type",L"Application", 
			 G_BINDING_DERIVED_TYPE_MAP, "Filter",filterMap,
			 G_TYPE_INVALID,
			 &outparam, NULL, 0, &error);
	        }
	     else
	        {
	         // Request Service	without  Filter 		                      
	         requestservice(interface_handle, operation1, 
	         G_BINDING_DERIVED_TYPE_UNICODE  , "ContentType",L"Application", 
			 G_TYPE_INVALID,
			 &outparam, NULL, 0, &error);
	        }
      
			                      
         //result = error ;

         rescnt = getoutputcount(outparam);			   
         wchar_t buffer[5012];
	     type = getoutputatindex(outparam, &result, 0);
	
         if( KErrNone == error )
	        {	
	
	        while( iterator_next ( result, &resmap ) == 0 )
		        {

		        FILE *fp;
    	        fp = fopen("C:\\data\\AppManager\\Result1iter3.txt","w");

		        TInt mCount = map_count(resmap);
	    
	            for(TInt index = 0 ; index < mCount ; index++ )
		            {
		            map_findkeyatindex(resmap, index , keyfound);	 	
		            map_findvaluewithkey(resmap , keyfound, &foundvalue);
		            getresult( foundvalue, G_BINDING_DERIVED_TYPE_UNICODE, &buffer );
		            fprintf(fp,"%s   =  ",keyfound);
		            fprintf(fp,"%ls",buffer);
		            fprintf(fp,"\n");
		            }

		        map_delete(resmap);	
		        fclose(fp);			
		        }
	        }

        map_delete(filterMap);
	    resetoutput(outparam);

    	closeinterface( interface_handle ); // Closing interface
	
	    unloadservice( service_name , interface_name ); // Unload service

	    cbindingdetach(); // Dettach from binding    
	    }
	else
	    {
	    // Interface missing
	    iLog->Log(_L("Didn't get interface"));
	    cbindingdetach(); // Dettach from binding
  	    return KErrGeneral;
	    }
        
        
   
  /*-------------------------------------------------------------------------------------------*/


   	__UHEAP_MARKEND;
	return result;


    }


//Helper Function

TInt CAppManagerTest::ConvertHexStringToInt32(const TDesC& aHexString,TInt32& aInt32 )
    {
    aInt32 = 0;

    TInt pos = aHexString.LocateF( 'x' );
    if ( pos == KErrNotFound )
        {
        pos = 0;
        }
    else
        {
        pos++;
        }

    if( ( aHexString.Length() - pos ) > KDocMaxDigitsInHexString )
        {
        return KErrArgument; // Error: value too big.
        }
    TPtrC aHexStringPtr( aHexString.Mid( pos ) );

    TInt64 value64;
    if ( TLex( aHexStringPtr ).Val( value64, EHex ) != KErrNone )
        {
        return KErrArgument; // Error: conversion failed.
        }
    aInt32 = value64;

    return KErrNone;
    }

// ========================== OTHER EXPORTED FUNCTIONS =========================
// None

//  End of File
