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
#include "tcalendarimporttest.h"
#include "calendarheader.h"
#include "calendarservice.h"
#include "calimptestcases.h"


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTChangeStatusTest::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTCalendarImportTest::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CTChangeStatusTest::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTCalendarImportTest::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        //TRY( "SendMessage",    CTDeleteMessageTest::SendMessage ),
        
        ENTRY( "Import",    	 CTCalendarImportTest::Import ),
		ENTRY( "ImportAsync",    CTCalendarImportTest::ImportAsync ),
		ENTRY( "ICALImport",     CTCalendarImportTest::ICALImport ),
		ENTRY( "ICALImportAsync",CTCalendarImportTest::ICALImportAsync ),
        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }


	
// -----------------------------------------------------------------------------
// CTCalendarImportTest::Import
// Test Method to test the Import(Synchronous)
// Functionality of CalenderService
// -----------------------------------------------------------------------------
//
TInt  CTCalendarImportTest::Import(CStifItemParser& /*aItem*/)
	{
	__UHEAP_MARK;
	
	TInt result=KErrNone;
	
	CCalImpTestCases *calImpTest = CCalImpTestCases::NewL(result);

	calImpTest->TestImportL();

	delete calImpTest;
	
	__UHEAP_MARKEND;
	
	return result;
    }


// -----------------------------------------------------------------------------
// CTCalendarImportTest::ImportAsync
// Test Method to test the ImportAsync(ASynchronous)
// Functionality of CalenderService
// -----------------------------------------------------------------------------
//
TInt  CTCalendarImportTest::ImportAsync(CStifItemParser& /*aItem*/)
	{
	__UHEAP_MARK;
	
	TInt result=KErrNone;
	
	CCalImpTestCases *calImpTest = CCalImpTestCases::NewL(result);

	calImpTest->TestImportAsyncL();
	
	delete calImpTest;
	
	__UHEAP_MARKEND;
	
	return result;
    }

// -----------------------------------------------------------------------------
// CTCalendarImportTest::ICALImport
// Test Method to test the ICALImport(Synchronous)
// Functionality of CalenderService
// -----------------------------------------------------------------------------
//
TInt  CTCalendarImportTest::ICALImport(CStifItemParser& /*aItem*/)
	{
	__UHEAP_MARK;
	
	TInt result=KErrNone;
	
	CCalImpTestCases *calImpTest = CCalImpTestCases::NewL(result,2);
	
	calImpTest->TestImportL();

	delete calImpTest;
	
	__UHEAP_MARKEND;
	
	return result;
    }


// -----------------------------------------------------------------------------
// CTCalendarImportTest::ICALImportAsync
// Test Method to test the ICALImportAsync(ASynchronous)
// Functionality of CalenderService
// -----------------------------------------------------------------------------
//
TInt  CTCalendarImportTest::ICALImportAsync(CStifItemParser& /*aItem*/)
	{
	__UHEAP_MARK;
	
	TInt result=KErrNone;
	
	CCalImpTestCases *calImpTest = CCalImpTestCases::NewL(result,2);
	
	CleanupStack::PushL(calImpTest);
	
	calImpTest->TestImportAsyncL();
	
	CleanupStack::PopAndDestroy(calImpTest);
			
	__UHEAP_MARKEND;
	
	return result;
    }


