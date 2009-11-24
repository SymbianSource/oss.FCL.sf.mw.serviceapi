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
* Description:   ?Description
*
*/




// INCLUDE FILES
#include <e32svr.h>
#include <StifParser.h>
#include <StifTestInterface.h>
#include "tcal_import.h"
#include "calendarheader.h"
#include "calendarservice.h"
#include "importestcases.h"


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
// Ctcal_import::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void Ctcal_import::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// Ctcal_import::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt Ctcal_import::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "ImportByGuid", Ctcal_import::ImportByGuid ),
        ENTRY( "ImportUsingGUidAsync", Ctcal_import::ImportUsingGUidAsync),
        ENTRY( "ImportByLuid", Ctcal_import::ImportByLuid),
        ENTRY( "ImportUsingLUidAsync", Ctcal_import::ImportUsingLUidAsync),
        ENTRY( "ImportCases_one", Ctcal_import::ImportCases_one),
        ENTRY( "ImportCases_two", Ctcal_import::ImportCases_two),
        ENTRY( "ImportFromFile", Ctcal_import::ImportFromFile),
        ENTRY( "ImportUsingFileAsync", Ctcal_import::ImportUsingFileAsync),
        ENTRY( "ImportCases_three", Ctcal_import::ImportCases_three),
        ENTRY( "ImportMultipleEntry", Ctcal_import::ImportMultipleEntry),
        ENTRY( "ImportMultipleEntryAsync", Ctcal_import::ImportMultipleEntryAsync),
        ENTRY( "ImportCaseAsync", Ctcal_import::ImportCaseAsync),
        ENTRY( "RemoveFile", Ctcal_import::RemoveFile ),
        //ADD NEW ENTRY HERE

        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// Function to remove a file
TInt Ctcal_import::RemoveFile( CStifItemParser& aItem )
    {
		TPtrC16 file;
    	aItem.GetNextString(file);
  		RFile LogResult;
    	RFs LogResultSession;
    	User::LeaveIfError(LogResultSession.Connect());
    	if(LogResult.Open(LogResultSession ,file , EFileWrite | EFileShareAny )  != KErrNotFound)
        {
        	LogResult.Close();

			LogResultSession.Delete(file);
		
        	LogResultSession.Close();
        }
    
    	LogResult.Close();
    	LogResultSession.Close();
		return KErrNone;
    
    }
    
    
// -----------------------------------------------------------------------------
// Ctcal_import::ImportByGuid
// Example test method function to import entries based on Guid.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_import::ImportByGuid( CStifItemParser& /*aItem*/ )
    {

    __UHEAP_MARK;
	
	TInt result=KErrNone;
	
	CCalImpTestCases *calImpTest = CCalImpTestCases::NewL(result);

	result = calImpTest->TestImportGuidL();

	delete calImpTest;
	
	__UHEAP_MARKEND;
	
	return result;

    }
    
 // -----------------------------------------------------------------------------
// Ctcal_import::ImportUsingGUidAsync
// Example test method function to import entries based on Guid - Async.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_import::ImportUsingGUidAsync( CStifItemParser& /*aItem*/ )
    {

    TInt result=KErrNone;
	
	CCalImpTestCases *calImpTest = CCalImpTestCases::NewL(result);

	calImpTest->TestImportUsingGuidAsyncL();

	delete calImpTest;
	
	return result;

    }
    
// -----------------------------------------------------------------------------
// Ctcal_import::ImportByLuid
// Example test method function to import entries based on Luid.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_import::ImportByLuid( CStifItemParser& /*aItem*/ )
    {

    __UHEAP_MARK;
	
	TInt result=KErrNone;
	
	CCalImpTestCases *calImpTest = CCalImpTestCases::NewL(result);

	result = calImpTest->TestImportLuidL();

	delete calImpTest;
	
	__UHEAP_MARKEND;
	
	return result;

    }
    
 // -----------------------------------------------------------------------------
// Ctcal_import::ImportUsingLUidAsync
// Example test method function to import entries based on Luid - Async.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_import::ImportUsingLUidAsync( CStifItemParser& /*aItem*/ )
    {

    TInt result=KErrNone;
	
	CCalImpTestCases *calImpTest = CCalImpTestCases::NewL(result);

	calImpTest->TestImportUsingLuidAsyncL();

	delete calImpTest;
	
	return result;

    }
    
 // -----------------------------------------------------------------------------
// Ctcal_import::ImportCases_one
// Example test method function to test few cases with Import.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_import::ImportCases_one( CStifItemParser& /*aItem*/ )
    {

    __UHEAP_MARK;
	
	TInt result=KErrNone;
	
	CCalImpTestCases *calImpTest = CCalImpTestCases::NewL(result);

	result = calImpTest->TestImportCases1();

	delete calImpTest;
	
	__UHEAP_MARKEND;
	
	return result;

    }
    
 // -----------------------------------------------------------------------------
// Ctcal_import::ImportCases_two
// Example test method function to test few cases with Import.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_import::ImportCases_two( CStifItemParser& /*aItem*/ )
    {

    __UHEAP_MARK;
	
	TInt result=KErrNone;
	
	CCalImpTestCases *calImpTest = CCalImpTestCases::NewL(result);

	result = calImpTest->TestImportCases2();

	delete calImpTest;
	
	__UHEAP_MARKEND;
	
	return result;

    }
    
// -----------------------------------------------------------------------------
// Ctcal_import::ImportFromFile
// Example test method function to import from file.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_import::ImportFromFile( CStifItemParser& /*aItem*/ )
    {

    __UHEAP_MARK;
	
	TInt result=KErrNone;
	
	CCalImpTestCases *calImpTest = CCalImpTestCases::NewL(result);

	result = calImpTest->TestImportFromFileL();

	delete calImpTest;
	
	__UHEAP_MARKEND;
	
	return result;

    }
    
 // -----------------------------------------------------------------------------
// Ctcal_import::ImportUsingFileAsync
// Example test method function to import from file - async
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_import::ImportUsingFileAsync( CStifItemParser& /*aItem*/ )
    {

    
	TInt result=KErrNone;
	
	CCalImpTestCases *calImpTest = CCalImpTestCases::NewL(result);

	calImpTest->TestImportUsingFileAsyncL();

	delete calImpTest;
	
	return result;

    }
 
 // -----------------------------------------------------------------------------
// Ctcal_import::ImportCases_three
// Example test method function to test few cases with Import.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_import::ImportCases_three( CStifItemParser& /*aItem*/ )
    {

    __UHEAP_MARK;
	
	TInt result=KErrNone;
	
	CCalImpTestCases *calImpTest = CCalImpTestCases::NewL(result);

	result = calImpTest->TestImportCases3();

	delete calImpTest;
	
	__UHEAP_MARKEND;
	
	return result;

    }  
    
 // -----------------------------------------------------------------------------
// Ctcal_import::ImportMultipleEntry
// Example test method function to import entries from multiple files.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_import::ImportMultipleEntry( CStifItemParser& /*aItem*/ )
    {

    __UHEAP_MARK;
	
	TInt result=KErrNone;
	
	CCalImpTestCases *calImpTest = CCalImpTestCases::NewL(result);

	result = calImpTest->TestImportMultipleEntry();

	delete calImpTest;
	
	__UHEAP_MARKEND;
	
	return result;

    }  
    
  // -----------------------------------------------------------------------------
// Ctcal_import::ImportMultipleEntryAsync
// Example test method function to import entries from multiple files - Async.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_import::ImportMultipleEntryAsync( CStifItemParser& /*aItem*/ )
    {

   	
	TInt result=KErrNone;
	
	CCalImpTestCases *calImpTest = CCalImpTestCases::NewL(result);

	calImpTest->TestImportMultipleEntryAsyncL();

	delete calImpTest;
	
	return result;

    }  
    
 // -----------------------------------------------------------------------------
// Ctcal_import::ImportCaseAsync
// Example test method function to test import case - Async.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_import::ImportCaseAsync( CStifItemParser& /*aItem*/ )
    {

    
	TInt result=KErrNone;
	
	CCalImpTestCases *calImpTest = CCalImpTestCases::NewL(result);

	calImpTest->TestImportCaseAsyncL();

	delete calImpTest;
	
	return result;

    }  
    
    
// -----------------------------------------------------------------------------
// Ctcal_import::?member_function
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
/*
TInt Ctcal_import::?member_function(
   CItemParser& aItem )
   {

   ?code

   }
*/

// ========================== OTHER EXPORTED FUNCTIONS =========================
// None

//  End of File
