/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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
//#include <SAPI_TEST\testprg.h>
#include <Stiftestinterface.h>

#include "tcalendarexporttest.h"

#include "calexptestcases.h"

#include "calendarservice.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTChangeStatusTest::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTCalendarExportTest::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CTChangeStatusTest::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTCalendarExportTest::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        //TRY( "SendMessage",    CTDeleteMessageTest::SendMessage ),
        
        ENTRY( "ExportAll",    CTCalendarExportTest::ExportAll ),
        ENTRY( "ExportForGUIDs", CTCalendarExportTest::ExportForGUIDs ),
        ENTRY( "ExportForLUIDs", CTCalendarExportTest::ExportForLUIDs ),
		
		ENTRY( "ExportAllAsync",    CTCalendarExportTest::ExportAllAsync ),
        ENTRY( "ExportForGUIDsAsync", CTCalendarExportTest::ExportForGUIDsAsync ),
        ENTRY( "ExportForLUIDsAsync", CTCalendarExportTest::ExportForLUIDsAsync ),
        
        ENTRY( "ICALExportAll",    CTCalendarExportTest::ICALExportAll ),
        ENTRY( "ICALExportForGUIDs", CTCalendarExportTest::ICALExportForGUIDs ),
        ENTRY( "ICALExportForLUIDs", CTCalendarExportTest::ICALExportForLUIDs ),
		
		ENTRY( "ICALExportAllAsync",    CTCalendarExportTest::ICALExportAllAsync ),
        ENTRY( "ICALExportForGUIDsAsync", CTCalendarExportTest::ICALExportForGUIDsAsync ),
        ENTRY( "ICALExportForLUIDsAsync", CTCalendarExportTest::ICALExportForLUIDsAsync ),
        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }
    
extern void StartAlarmServerL();
// -----------------------------------------------------------------------------
// CTCalendarExportTest::ExportAll
// Test Method to test the ExportAll(Synchronous) 
// Functionality of CalenderService
// -----------------------------------------------------------------------------
//
TInt  CTCalendarExportTest::ExportAll(CStifItemParser& /*aItem*/)
	{
	__UHEAP_MARK;

	TInt result=KErrNone;
	
	CCalExpTestCases *calExpTest = CCalExpTestCases::NewL(result);
	
	result = calExpTest->TestExportAllL();
	
	delete calExpTest;
	
	__UHEAP_MARKEND;
	
	return result;
    }



// -----------------------------------------------------------------------------
// CTCalendarExportTest::ExportForGUIDs
// Test Method to test the ExportExportForGUIDs(Synchronous) 
// Functionality of CalenderService
// -----------------------------------------------------------------------------
//
TInt  CTCalendarExportTest::ExportForGUIDs(CStifItemParser& /*aItem*/)
	{
	__UHEAP_MARK;
	
	TInt result=KErrNone;
	
	CCalExpTestCases *calExpTest = CCalExpTestCases::NewL(result);
	
	result = calExpTest->TestExportForGuidsL();
	
	delete calExpTest;
	
	__UHEAP_MARKEND;
	
	return result;
    }

    

// -----------------------------------------------------------------------------
// CTCalendarExportTest::ExportForLUIDs
// Test Method to test the ExportForLUIDs(Synchronous) 
// Functionality of CalenderService
// -----------------------------------------------------------------------------
//    
TInt  CTCalendarExportTest::ExportForLUIDs(CStifItemParser& /*aItem*/)
	{
	__UHEAP_MARK;
	

	TInt result=KErrNone;
	
	CCalExpTestCases *calExpTest = CCalExpTestCases::NewL(result);
	
	result = calExpTest->TestExportForLuidsL();
	
	delete calExpTest;
	
	__UHEAP_MARKEND;
	
	return result;
    }
    


// -----------------------------------------------------------------------------
// CTCalendarExportTest::ExportAllAsync
// Test Method to test the ExportAllAsync(Synchronous) 
// Functionality of CalenderService
// -----------------------------------------------------------------------------
//
TInt  CTCalendarExportTest::ExportAllAsync(CStifItemParser& /*aItem*/)
	{
	__UHEAP_MARK;
	

	TInt result = KErrNone;
	
	CCalExpTestCases *calExpTest = CCalExpTestCases::NewL(result);
	
	//CleanupStack::PushL(calExpTest);
	
	calExpTest->TestExportAllAsyncL();
	
	delete calExpTest;
	
	__UHEAP_MARKEND;
	
	return result;
    }

// -----------------------------------------------------------------------------
// CTCalendarExportTest::ExportForGUIDsAsync
// Test Method to test the ExportForGUIDsAsync(ASynchronous) 
// Functionality of CalenderService
// -----------------------------------------------------------------------------
//
TInt  CTCalendarExportTest::ExportForGUIDsAsync(CStifItemParser& /*aItem*/)
	{
	__UHEAP_MARK;
	

	TInt result=KErrNone;
	
	CCalExpTestCases *calExpTest = CCalExpTestCases::NewL(result);
	
	calExpTest->TestExportForGuidsAsyncL();

	delete calExpTest;
	
	__UHEAP_MARKEND;
	
	return result;
    }


// -----------------------------------------------------------------------------
// CTCalendarExportTest::ExportForLUIDsAsync
// Test Method to test the ExportForLUIDsAsync(ASynchronous) 
// Functionality of CalenderService
// -----------------------------------------------------------------------------
//
TInt  CTCalendarExportTest::ExportForLUIDsAsync(CStifItemParser& /*aItem*/)
	{
	__UHEAP_MARK;
	

	TInt result=KErrNone;
	
	CCalExpTestCases *calExpTest = CCalExpTestCases::NewL(result);

	calExpTest->TestExportForLuidsAsyncL();

	delete calExpTest;
	
	__UHEAP_MARKEND;
	
	return result;
    }
 
 
    
 //ICALICALICALICALICALICALICALICALICALICALICALICALICALICAL
 
// -----------------------------------------------------------------------------
// CTCalendarExportTest::ExportAll
// Test Method to test the ExportAll(Synchronous) 
// Functionality of CalenderService
// -----------------------------------------------------------------------------
//
TInt  CTCalendarExportTest::ICALExportAll(CStifItemParser& /*aItem*/)
	{
	__UHEAP_MARK;

	TInt result=KErrNone;
	
	CCalExpTestCases *calExpTest = CCalExpTestCases::NewL(result, 2);
	
	//CleanupStack::PushL( calExpTest );
	
	result = calExpTest->TestExportAllL();
	
	//CleanupStack::PopAndDestroy(calExpTest);
	
	delete calExpTest;
	
	__UHEAP_MARKEND;
	
	return result;
    }



// -----------------------------------------------------------------------------
// CTCalendarExportTest::ExportForGUIDs
// Test Method to test the ExportExportForGUIDs(Synchronous) 
// Functionality of CalenderService
// -----------------------------------------------------------------------------
//
TInt  CTCalendarExportTest::ICALExportForGUIDs(CStifItemParser& /*aItem*/)
	{
	__UHEAP_MARK;
	
	TInt result=KErrNone;
	
	CCalExpTestCases *calExpTest = CCalExpTestCases::NewL(result, 2);
	
	//CleanupStack::PushL(calExpTest);
	
	result = calExpTest->TestExportForGuidsL();
	
	//CleanupStack::PopAndDestroy(calExpTest);
	
	delete calExpTest;
	
	__UHEAP_MARKEND;
	
	return result;
    }

    

// -----------------------------------------------------------------------------
// CTCalendarExportTest::ExportForLUIDs
// Test Method to test the ExportForLUIDs(Synchronous) 
// Functionality of CalenderService
// -----------------------------------------------------------------------------
//    
TInt  CTCalendarExportTest::ICALExportForLUIDs(CStifItemParser& /*aItem*/)
	{
	__UHEAP_MARK;
	

	TInt result=KErrNone;
	
	CCalExpTestCases *calExpTest = CCalExpTestCases::NewL(result, 2);
	
	//CleanupStack::PushL(calExpTest);
	
	result = calExpTest->TestExportForLuidsL();
	
	//CleanupStack::PopAndDestroy(calExpTest);
	
	delete calExpTest;
	
	__UHEAP_MARKEND;
	
	return result;
    }
    


// -----------------------------------------------------------------------------
// CTCalendarExportTest::ExportAllAsync
// Test Method to test the ExportAllAsync(Synchronous) 
// Functionality of CalenderService
// -----------------------------------------------------------------------------
//
TInt  CTCalendarExportTest::ICALExportAllAsync(CStifItemParser& /*aItem*/)
	{
	__UHEAP_MARK;
	

	TInt result=KErrNone;
	
	CCalExpTestCases *calExpTest = CCalExpTestCases::NewL(result, 2);
	
	//CleanupStack::PushL(calExpTest);
	
	TRAPD(err, calExpTest->TestExportAllAsyncL());
	
	//CleanupStack::PopAndDestroy(calExpTest);
		
	delete calExpTest;
	
	
	__UHEAP_MARKEND;
	
	return result;
    }

// -----------------------------------------------------------------------------
// CTCalendarExportTest::ExportForGUIDsAsync
// Test Method to test the ExportForGUIDsAsync(ASynchronous) 
// Functionality of CalenderService
// -----------------------------------------------------------------------------
//
TInt  CTCalendarExportTest::ICALExportForGUIDsAsync(CStifItemParser& /*aItem*/)
	{
	__UHEAP_MARK;
	

	TInt result=KErrNone;
	
	CCalExpTestCases *calExpTest = CCalExpTestCases::NewL(result, 2);
	
	CleanupStack::PushL(calExpTest);
	
	calExpTest->TestExportForGuidsAsyncL();
	
	CleanupStack::PopAndDestroy(calExpTest);
	
	__UHEAP_MARKEND;
	
	return result;
    }


// -----------------------------------------------------------------------------
// CTCalendarExportTest::ExportForLUIDsAsync
// Test Method to test the ExportForLUIDsAsync(ASynchronous) 
// Functionality of CalenderService
// -----------------------------------------------------------------------------
//
TInt  CTCalendarExportTest::ICALExportForLUIDsAsync(CStifItemParser& /*aItem*/)
	{
	__UHEAP_MARK;
	

	TInt result=KErrNone;
	
	CCalExpTestCases *calExpTest = CCalExpTestCases::NewL(result, 2);
	
	CleanupStack::PushL(calExpTest);
	
	calExpTest->TestExportForLuidsAsyncL();
	
	CleanupStack::PopAndDestroy(calExpTest);
	
	__UHEAP_MARKEND;
	
	return result;
    }
        
