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

#include "tcalendardeletetest.h"

#include "caldeltestcases.h"

#include "calendarservice.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTChangeStatusTest::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTCalendarDeleteTest::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CTChangeStatusTest::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTCalendarDeleteTest::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        //TRY( "SendMessage",    CTDeleteMessageTest::SendMessage ),
        
        ENTRY( "DeleteCalendar",    	CTCalendarDeleteTest::DeleteCalendar),
        ENTRY( "DeleteDefaultCalendar", CTCalendarDeleteTest::DeleteDefaultCalendar),
        ENTRY( "DeleteAllEntries",    	CTCalendarDeleteTest::DeleteAllEntries),
        ENTRY( "DeleteUsingGUid",    	CTCalendarDeleteTest::DeleteUsingGUid),
        ENTRY( "DeleteUsingLocalUid",   CTCalendarDeleteTest::DeleteUsingLocalUid),
        ENTRY( "DeleteTmRgLocalUid",    CTCalendarDeleteTest::DeleteTmRgLocalUid),
        ENTRY( "DeleteTmRgGUid",    	CTCalendarDeleteTest::DeleteTmRgGUid),
        ENTRY( "DeleteTmRg",    		CTCalendarDeleteTest::DeleteTmRg),
        
        ENTRY( "DeleteAllEntriesAsync",    	CTCalendarDeleteTest::DeleteAllEntriesAsync),
        ENTRY( "DeleteUsingGUidAsync",    	CTCalendarDeleteTest::DeleteUsingGUidAsync),
        ENTRY( "DeleteUsingLocalUidAsync",  CTCalendarDeleteTest::DeleteUsingLocalUidAsync),
        ENTRY( "DeleteTmRgLocalUidAsync",   CTCalendarDeleteTest::DeleteTmRgLocalUidAsync),
        ENTRY( "DeleteTmRgGUidAsync",    	CTCalendarDeleteTest::DeleteTmRgGUidAsync),
        ENTRY( "DeleteTmRgAsync",    		CTCalendarDeleteTest::DeleteTmRgAsync),
        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }
    

TInt CTCalendarDeleteTest::DeleteCalendar(CStifItemParser & /*aItem*/ )
	{
	TInt result = KErrNone;
	__UHEAP_MARK;
	CCalDelTestCases *calDelTest =  CCalDelTestCases::NewL(result);

	CleanupStack::PushL( calDelTest );

	calDelTest->TestDeleteCalendarL();	

	CleanupStack::PopAndDestroy( calDelTest );
	__UHEAP_MARKEND;
	return result;
    }

TInt CTCalendarDeleteTest::DeleteDefaultCalendar(CStifItemParser & /*aItem*/ )
	{
	TInt result = KErrNone;
	__UHEAP_MARK;
	CCalDelTestCases *calDelTest =  CCalDelTestCases::NewL(result);

	CleanupStack::PushL( calDelTest );

	calDelTest->TestDeleteDefaultCalendarL();	

	CleanupStack::PopAndDestroy( calDelTest );
	__UHEAP_MARKEND;
	return result;
    }

_LIT(KDelTestCalName             ,"c:deletethiscalender");
	
void removeCalendarFileL()	
	{
	CCalendarService *service = CCalendarService::NewL();

	CleanupStack::PushL( service );
	
	TRAPD( err , service->DeleteL( KDelTestCalName.operator()() ) );
	
	CleanupStack::PopAndDestroy( service );
	}
	
TInt CTCalendarDeleteTest::DeleteAllEntries(CStifItemParser & /*aItem*/ )
	{
	TInt result = KErrNone;
	__UHEAP_MARK;
	removeCalendarFileL();
	
	CCalDelTestCases *calDelTest =  CCalDelTestCases::NewL(result);

	CleanupStack::PushL( calDelTest );

	calDelTest->TestDeleteAllEntriesL();	

	CleanupStack::PopAndDestroy( calDelTest );
	
	removeCalendarFileL();
	__UHEAP_MARKEND;
	return result;
    }

TInt CTCalendarDeleteTest::DeleteUsingGUid(CStifItemParser & /*aItem*/ )
	{
	TInt result = KErrNone;
	__UHEAP_MARK;
	removeCalendarFileL();
	
	CCalDelTestCases *calDelTest =  CCalDelTestCases::NewL(result);

	CleanupStack::PushL( calDelTest );

	calDelTest->TestDeleteUsingGUidL();	

	CleanupStack::PopAndDestroy( calDelTest );
	
	removeCalendarFileL();
	__UHEAP_MARKEND;
	return result;
    }


TInt CTCalendarDeleteTest::DeleteUsingLocalUid(CStifItemParser & /*aItem*/ )
	{
	TInt result = KErrNone;
	__UHEAP_MARK;
	removeCalendarFileL();
	
	CCalDelTestCases *calDelTest =  CCalDelTestCases::NewL(result);

	CleanupStack::PushL( calDelTest );

	calDelTest->TestDeleteUsingLocalUidL();	

	CleanupStack::PopAndDestroy( calDelTest );
	
	removeCalendarFileL();
	__UHEAP_MARKEND;
	return result;
    }


TInt CTCalendarDeleteTest::DeleteTmRgLocalUid(CStifItemParser & /*aItem*/ )
	{
	TInt result = KErrNone;
	__UHEAP_MARK;
	removeCalendarFileL();
	
	CCalDelTestCases *calDelTest =  CCalDelTestCases::NewL(result);

	CleanupStack::PushL( calDelTest );

	calDelTest->TestDeleteTmRgLocalUidL();	

	CleanupStack::PopAndDestroy( calDelTest );
	
	removeCalendarFileL();
	__UHEAP_MARKEND;
	return result;
    }


TInt CTCalendarDeleteTest::DeleteTmRgGUid(CStifItemParser & /*aItem*/ )
	{
	TInt result = KErrNone;
	__UHEAP_MARK;
	removeCalendarFileL();
	
	CCalDelTestCases *calDelTest =  CCalDelTestCases::NewL(result);

	CleanupStack::PushL( calDelTest );

	calDelTest->TestDeleteTmRgGUidL();	

	CleanupStack::PopAndDestroy( calDelTest );
	
	removeCalendarFileL();
	__UHEAP_MARKEND;
	return result;
    }


TInt CTCalendarDeleteTest::DeleteTmRg(CStifItemParser & /*aItem*/ )
	{
	TInt result = KErrNone;
	__UHEAP_MARK;
	removeCalendarFileL();
	
	CCalDelTestCases *calDelTest =  CCalDelTestCases::NewL(result);

	CleanupStack::PushL( calDelTest );

	calDelTest->TestDeleteTmRgL();

	CleanupStack::PopAndDestroy( calDelTest );
	
	removeCalendarFileL();
	__UHEAP_MARKEND;
	return result;
    }
    
 //Async things starts here **************************************************
    
TInt CTCalendarDeleteTest::DeleteAllEntriesAsync(CStifItemParser & /*aItem*/ )
	{
	TInt result = KErrNone;
	__UHEAP_MARK;
	removeCalendarFileL();
	
	CCalDelTestCases *calDelTest =  CCalDelTestCases::NewL(result);

	CleanupStack::PushL( calDelTest );

	calDelTest->TestDeleteAllEntriesAsyncL();	

	CleanupStack::PopAndDestroy( calDelTest );

	removeCalendarFileL();
	__UHEAP_MARKEND;
	return result;
    }

TInt CTCalendarDeleteTest::DeleteUsingGUidAsync(CStifItemParser & /*aItem*/ )
	{
	TInt result = KErrNone;
	__UHEAP_MARK;
	removeCalendarFileL();
	
	CCalDelTestCases *calDelTest =  CCalDelTestCases::NewL(result);

	CleanupStack::PushL( calDelTest );

	calDelTest->TestDeleteUsingGUidAsyncL();	

	CleanupStack::PopAndDestroy( calDelTest );
	
	removeCalendarFileL();
	__UHEAP_MARKEND;
	return result;
    }


TInt CTCalendarDeleteTest::DeleteUsingLocalUidAsync(CStifItemParser & /*aItem*/ )
	{
	TInt result = KErrNone;
	__UHEAP_MARK;
	removeCalendarFileL();
	
	CCalDelTestCases *calDelTest =  CCalDelTestCases::NewL(result);

	CleanupStack::PushL( calDelTest );

	calDelTest->TestDeleteUsingLocalUidAsyncL();	

	CleanupStack::PopAndDestroy( calDelTest );
	
	removeCalendarFileL();
	__UHEAP_MARKEND;
	return result;
    }


TInt CTCalendarDeleteTest::DeleteTmRgLocalUidAsync(CStifItemParser & /*aItem*/ )
	{
	TInt result = KErrNone;
	__UHEAP_MARK;
	removeCalendarFileL();
	
	CCalDelTestCases *calDelTest =  CCalDelTestCases::NewL(result);

	CleanupStack::PushL( calDelTest );

	calDelTest->TestDeleteTmRgLocalUidAsyncL();	

	CleanupStack::PopAndDestroy( calDelTest );
	
	removeCalendarFileL();
	__UHEAP_MARKEND;
	return result;
    }


TInt CTCalendarDeleteTest::DeleteTmRgGUidAsync(CStifItemParser & /*aItem*/ )
	{
	TInt result = KErrNone;
	__UHEAP_MARK;
	removeCalendarFileL();
	
	CCalDelTestCases *calDelTest =  CCalDelTestCases::NewL(result);

	CleanupStack::PushL( calDelTest );

	calDelTest->TestDeleteTmRgGUidAsyncL();	

	CleanupStack::PopAndDestroy( calDelTest );
	
	removeCalendarFileL();
	__UHEAP_MARKEND;
	return result;
    }


TInt CTCalendarDeleteTest::DeleteTmRgAsync(CStifItemParser & /*aItem*/ )
	{
	TInt result = KErrNone;
	__UHEAP_MARK;
	removeCalendarFileL();
	
	CCalDelTestCases *calDelTest =  CCalDelTestCases::NewL(result);

	CleanupStack::PushL( calDelTest );

	calDelTest->TestDeleteTmRgAsyncL();

	CleanupStack::PopAndDestroy( calDelTest );
	
	removeCalendarFileL();
	__UHEAP_MARKEND;
	return result;
    }    
