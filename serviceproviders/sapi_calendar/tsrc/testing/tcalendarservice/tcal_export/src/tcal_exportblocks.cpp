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
#include "tcal_export.h"
#include "calendarheader.h"
#include "calendarservice.h"
#include "exportestcases.h"


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
// Ctcal_export::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void Ctcal_export::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// Ctcal_export::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt Ctcal_export::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "ExportCases", Ctcal_export::ExportCases ),
        ENTRY( "ExportGuid", Ctcal_export::ExportGuid ),
        ENTRY( "ExportGuidBufAsync", Ctcal_export::ExportGuidBufAsync ),
        ENTRY( "ExportGuidFileAsync", Ctcal_export::ExportGuidFileAsync),
        ENTRY( "ExportLuid", Ctcal_export::ExportLuid),
        ENTRY( "ExportLuidAsync", Ctcal_export::ExportLuidAsync),
        ENTRY( "ExportCaseAsync", Ctcal_export::ExportCaseAsync),
        ENTRY( "RemoveFile", Ctcal_export::RemoveFile ),
        //ADD NEW ENTRY HERE

        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// Function to remove a file
TInt Ctcal_export::RemoveFile( CStifItemParser& aItem )
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
// Ctcal_export::ExportCases
// Example test method function to test few cases with export - sync
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_export::ExportCases( CStifItemParser& aItem )
    {

   	__UHEAP_MARK;
	
	TInt result=KErrNone;
	
	CCalExpTestCases *calExpTest = CCalExpTestCases::NewL(result);
	
	CleanupStack::PushL(calExpTest);
	
	result = calExpTest->TestExportCasesL();
	
	CleanupStack::PopAndDestroy(calExpTest);
	
	__UHEAP_MARKEND;
	
	return result;
    }


// -----------------------------------------------------------------------------
// Ctcal_export::ExportGuid
// Example test method function to export Guid - sync
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_export::ExportGuid( CStifItemParser& aItem )
    {

   	__UHEAP_MARK;
	
	TInt result=KErrNone;
	
	CCalExpTestCases *calExpTest = CCalExpTestCases::NewL(result);
	
	CleanupStack::PushL(calExpTest);
	
	result = calExpTest->TestExportForGuidsL();
	
	CleanupStack::PopAndDestroy(calExpTest);
	
	__UHEAP_MARKEND;
	
	return result;
    }
    
    
// -----------------------------------------------------------------------------
// Ctcal_export::ExportGuidBufAsync
// Example test method function to export Guid - async using buf
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_export::ExportGuidBufAsync( CStifItemParser& aItem )
    {

   	__UHEAP_MARK;
	
	TInt result=KErrNone;
	
	CCalExpTestCases *calExpTest = CCalExpTestCases::NewL(result);
	
	CleanupStack::PushL(calExpTest);
	
	calExpTest->TestExportForGuidsBufAsyncL();
	
	CleanupStack::PopAndDestroy(calExpTest);
	
	__UHEAP_MARKEND;
	
	return result;
    }
    
 // -----------------------------------------------------------------------------
// Ctcal_export::ExportGuidFileAsync
// Example test method function to export Guid - async using file
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_export::ExportGuidFileAsync( CStifItemParser& aItem )
    {

   	__UHEAP_MARK;
	
	TInt result=KErrNone;
	
	CCalExpTestCases *calExpTest = CCalExpTestCases::NewL(result);
	
	CleanupStack::PushL(calExpTest);
	
	calExpTest->TestExportForGuidsFileAsyncL();
	
	CleanupStack::PopAndDestroy(calExpTest);
	
	__UHEAP_MARKEND;
	
	return result;
    }
    
    
 // -----------------------------------------------------------------------------
// Ctcal_export::ExportLuid
// Example test method function to export Luid for vcal - sync
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_export::ExportLuid( CStifItemParser& aItem )
    {

   	__UHEAP_MARK;
	
	TInt result=KErrNone;
	
	CCalExpTestCases *calExpTest = CCalExpTestCases::NewL(result);
	
	CleanupStack::PushL(calExpTest);
	
	result = calExpTest->TestExportForLuidsL();
	
	CleanupStack::PopAndDestroy(calExpTest);
	
	__UHEAP_MARKEND;
	
	return result;
    }
    
    
// -----------------------------------------------------------------------------
// Ctcal_export::ExportLuidAsync
// Example test method function to export Luid  for vcal- async using buf
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_export::ExportLuidAsync( CStifItemParser& aItem )
    {

   	__UHEAP_MARK;
	
	TInt result=KErrNone;
	
	CCalExpTestCases *calExpTest = CCalExpTestCases::NewL(result);
	
	CleanupStack::PushL(calExpTest);
	
	calExpTest->TestExportForLuidAsyncL();
	
	CleanupStack::PopAndDestroy(calExpTest);
	
	__UHEAP_MARKEND;
	
	return result;
    }
    
// -----------------------------------------------------------------------------
// Ctcal_export::ExportCaseAsync
// Example test method function to test case with export - async
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_export::ExportCaseAsync( CStifItemParser& aItem )
    {

   	__UHEAP_MARK;
	
	TInt result=KErrNone;
	
	CCalExpTestCases *calExpTest = CCalExpTestCases::NewL(result);
	
	CleanupStack::PushL(calExpTest);
	
	calExpTest->TestExportCaseAsyncL();
	
	CleanupStack::PopAndDestroy(calExpTest);
	
	__UHEAP_MARKEND;
	
	return result;
    }
    
// -----------------------------------------------------------------------------
// Ctcal_export::?member_function
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
/*
TInt Ctcal_export::?member_function(
   CItemParser& aItem )
   {

   ?code

   }
*/

// ========================== OTHER EXPORTED FUNCTIONS =========================
// None

//  End of File
