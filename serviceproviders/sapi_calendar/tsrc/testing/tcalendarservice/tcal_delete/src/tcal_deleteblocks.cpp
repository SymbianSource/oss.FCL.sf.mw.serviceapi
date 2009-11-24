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
#include "tcal_delete.h"
#include "cal_delete.h"
#include "calendarservice.h"


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
// Ctcal_delete::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void Ctcal_delete::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// Ctcal_delete::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt Ctcal_delete::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "DeleteCalEntryByGid", Ctcal_delete::DeleteCalEntryByGid ),
        ENTRY( "DeleteUsingGUidAsync", Ctcal_delete::DeleteUsingGUidAsync ),
        ENTRY( "DeleteCalEntryByLuid", Ctcal_delete::DeleteCalEntryByLuid ),
        ENTRY( "DeleteUsingLUidAsync", Ctcal_delete::DeleteUsingLUidAsync ),
        ENTRY( "DeleteCalEntryByTmRg", Ctcal_delete::DeleteCalEntryByTmRg ),
        ENTRY( "DeleteUsingTmRgAsync", Ctcal_delete::DeleteUsingTmRgAsync ),
        ENTRY( "DeleteCalEntryByGidLuidTm", Ctcal_delete::DeleteCalEntryByGidLuidTm ),
        ENTRY( "DeleteUsingGUidLuidTmAsync", Ctcal_delete::DeleteUsingGUidLuidTmAsync ),
        ENTRY( "DeleteCalEntryByInvalidGuidLuid", Ctcal_delete::DeleteCalEntryByInvalidGuidLuid ),
        ENTRY( "DeleteUsingInvalidGUidAsync", Ctcal_delete::DeleteUsingInvalidGUidAsync ),
        ENTRY( "DeleteUsingInvalidLUidAsync", Ctcal_delete::DeleteUsingInvalidLUidAsync ),
        ENTRY( "DeleteCalEntryByDefaultCal", Ctcal_delete::DeleteCalEntryByDefaultCal ),
        
        
        //ADD NEW ENTRY HERE

        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

_LIT(KTestCal1File                ,"C:calfile1");
_LIT(KTestCal2File                ,"C:calfile2");
_LIT(KTestRep                ,"invalid");

// -----------------------------------------------------------------------------
// Ctcal_delete::DeleteCalEntryByGid
// Method to delete calendar entry by Guid- Sync.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_delete::DeleteCalEntryByGid( CStifItemParser& /*aItem*/ )
    {
	
	TInt result = KErrNone;
	__UHEAP_MARK;
	CCalDelTestCases *calDelTest =  CCalDelTestCases::NewL(result);

	CleanupStack::PushL( calDelTest );

	result = calDelTest->TestDeleteUsingGUidL();	

	CleanupStack::PopAndDestroy( calDelTest );
	__UHEAP_MARKEND;
	return result;

    }

 //-----------------------------------------------------------------------------
// Ctcal_delete::DeleteUsingGUidAsync
// Method to delete calendar entry by Guid- ASync.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_delete::DeleteUsingGUidAsync(CStifItemParser & /*aItem*/ )
	{
	TInt result = KErrNone;
	__UHEAP_MARK;
	//removeCalendarFileL();
	
	CCalDelTestCases *calDelTest =  CCalDelTestCases::NewL(result);

	CleanupStack::PushL( calDelTest );

	calDelTest->TestDeleteUsingGUidAsyncL();	

	CleanupStack::PopAndDestroy( calDelTest );
	
//	removeCalendarFileL();
	__UHEAP_MARKEND;
	return result;
    }
    
// -----------------------------------------------------------------------------
// Ctcal_delete::DeleteCalEntryByLuid
// Method to delete calendar entry by Luid- Sync.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_delete::DeleteCalEntryByLuid( CStifItemParser& /*aItem*/ )
    {
	
	TInt result = KErrNone;
	__UHEAP_MARK;
	CCalDelTestCases *calDelTest =  CCalDelTestCases::NewL(result);

	CleanupStack::PushL( calDelTest );

	result = calDelTest->TestDeleteUsingLocalUidL();	

	CleanupStack::PopAndDestroy( calDelTest );
	__UHEAP_MARKEND;
	return result;

    }
    
//-----------------------------------------------------------------------------
// Ctcal_delete::DeleteUsingLUidAsync
// Method to delete calendar entry by Guid- ASync.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_delete::DeleteUsingLUidAsync(CStifItemParser & /*aItem*/ )
	{
	TInt result = KErrNone;
	__UHEAP_MARK;
	//removeCalendarFileL();
	
	CCalDelTestCases *calDelTest =  CCalDelTestCases::NewL(result);

	CleanupStack::PushL( calDelTest );

	calDelTest->TestDeleteUsingLocalUidAsyncL();	

	CleanupStack::PopAndDestroy( calDelTest );
	
//	removeCalendarFileL();
//	delete calDelTest;
	
	__UHEAP_MARKEND;
	return result;
    }
    
// -----------------------------------------------------------------------------
// Ctcal_delete::DeleteCalEntryByTmRg
// Method to delete calendar entry by Time range- Sync.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_delete::DeleteCalEntryByTmRg( CStifItemParser& /*aItem*/ )
    {
	
	TInt result = KErrNone;
	__UHEAP_MARK;
	CCalDelTestCases *calDelTest =  CCalDelTestCases::NewL(result);

	CleanupStack::PushL( calDelTest );

	result = calDelTest->TestDeleteTmRgL();	

	CleanupStack::PopAndDestroy( calDelTest );

//	delete calDelTest;
	
	__UHEAP_MARKEND;
	return result;

    }

 //-----------------------------------------------------------------------------
// Ctcal_delete::DeleteUsingTmRgAsync
// Method to delete calendar entry by Time range- AsSync.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_delete::DeleteUsingTmRgAsync(CStifItemParser & /*aItem*/ )
	{
	TInt result = KErrNone;
	__UHEAP_MARK;
	//removeCalendarFileL();
	
	CCalDelTestCases *calDelTest =  CCalDelTestCases::NewL(result);

	CleanupStack::PushL( calDelTest );

	calDelTest->TestDeleteTmRgAsyncL();	

	CleanupStack::PopAndDestroy( calDelTest );
	
//	removeCalendarFileL();
//	delete calDelTest;
	
	__UHEAP_MARKEND;
	return result;
    }
    
// -----------------------------------------------------------------------------
// Ctcal_delete::DeleteCalEntryByGidLuidTm
// Method to delete calendar entry by Guid+Luid+Tm- Sync.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_delete::DeleteCalEntryByGidLuidTm( CStifItemParser& /*aItem*/ )
    {
	
	TInt result = KErrNone;
	__UHEAP_MARK;
	CCalDelTestCases *calDelTest =  CCalDelTestCases::NewL(result);

	CleanupStack::PushL( calDelTest );

	result = calDelTest->TestDeleteGuidTmRgLocalUidL();	

	CleanupStack::PopAndDestroy( calDelTest );
//	delete calDelTest;
	
	__UHEAP_MARKEND;
	return result;

    }

 //-----------------------------------------------------------------------------
// Ctcal_delete::DeleteUsingGUidLuidTmAsync
// Method to delete calendar entry by Guid+Luid+Tm- ASync.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_delete::DeleteUsingGUidLuidTmAsync(CStifItemParser & /*aItem*/ )
	{
	TInt result = KErrNone;
	__UHEAP_MARK;
	//removeCalendarFileL();
	
	CCalDelTestCases *calDelTest =  CCalDelTestCases::NewL(result);

	CleanupStack::PushL( calDelTest );

	calDelTest->TestDeleteGuidTmRgLocalUidAsyncL();	

	CleanupStack::PopAndDestroy( calDelTest );
	
//	removeCalendarFileL();
//	delete calDelTest;
	
	
	__UHEAP_MARKEND;
	return result;    
	}
	
	
// -----------------------------------------------------------------------------
// Ctcal_delete::DeleteCalEntryByInvalidGuidLuid
// Method to delete calendar entry by Invalid guid+Luid- Sync.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_delete::DeleteCalEntryByInvalidGuidLuid( CStifItemParser& /*aItem*/ )
    {
	
	TInt result = KErrNone;
	__UHEAP_MARK;
	CCalDelTestCases *calDelTest =  CCalDelTestCases::NewL(result);

//	CleanupStack::PushL( calDelTest );

	result = calDelTest->TestDeleteInvalidGUidLuidL();	

//	CleanupStack::PopAndDestroy( calDelTest );

	delete calDelTest;
	
	__UHEAP_MARKEND;
	return result;

    }

 //-----------------------------------------------------------------------------
// Ctcal_delete::DeleteUsingInvalidGUidAsync
// Method to delete calendar entry by invalid Guid- ASync.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_delete::DeleteUsingInvalidGUidAsync(CStifItemParser & /*aItem*/ )
	{
	TInt result = KErrNone;
	__UHEAP_MARK;
	//removeCalendarFileL();
	
	CCalDelTestCases *calDelTest =  CCalDelTestCases::NewL(result);

//	CleanupStack::PushL( calDelTest );

	calDelTest->TestDeleteInvalidGUidAsyncL();	
	
	if(result == -1)
		result = KErrNone;	

//	CleanupStack::PopAndDestroy( calDelTest );
	
//	removeCalendarFileL();

	delete calDelTest;
	__UHEAP_MARKEND;
	return result;
    }
  
 //-----------------------------------------------------------------------------
// Ctcal_delete::DeleteUsingInvalidLUidAsync
// Method to delete calendar entry by invalid Guid- ASync.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_delete::DeleteUsingInvalidLUidAsync(CStifItemParser & /*aItem*/ )
	{
	TInt result = KErrNone;
	__UHEAP_MARK;
	//removeCalendarFileL();
	
	CCalDelTestCases *calDelTest =  CCalDelTestCases::NewL(result);

//	CleanupStack::PushL( calDelTest );

	calDelTest->TestDeleteInvalidLUidAsyncL();	
	
	//CleanupStack::PopAndDestroy( calDelTest );
	
//	removeCalendarFileL();

	delete calDelTest;
	
	__UHEAP_MARKEND;
	return result;
    } 
 // -----------------------------------------------------------------------------
// Ctcal_delete::DeleteCalEntryByDefaultCal
// Method to delete calendar entry in default calendar- Sync.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_delete::DeleteCalEntryByDefaultCal( CStifItemParser& /*aItem*/ )
    {
	
	TInt result = KErrNone;
	__UHEAP_MARK;
	CCalDelTestCases *calDelTest =  CCalDelTestCases::NewL(result);

	CleanupStack::PushL( calDelTest );

	result = calDelTest->TestDeleteByDefCalL();	

	CleanupStack::PopAndDestroy( calDelTest );
	__UHEAP_MARKEND;
	return result;

    }

     
      
    
// -----------------------------------------------------------------------------
// Ctcal_delete::?member_function
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
/*
TInt Ctcal_delete::?member_function(
   CItemParser& aItem )
   {

   ?code

   }
*/

// ========================== OTHER EXPORTED FUNCTIONS =========================
// None

//  End of File
