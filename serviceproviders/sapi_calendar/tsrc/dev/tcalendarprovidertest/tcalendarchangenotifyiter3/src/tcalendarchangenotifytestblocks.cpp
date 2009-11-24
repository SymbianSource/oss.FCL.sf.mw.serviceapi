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
#include <StifTestInterface.h>

#include <badesca.h>
#include<liwservicehandler.h>
#include<liwcommon.h>    


#include "tcalendarchangenotifytest.h"

#include "startconsolealarmserver.h"

TInt doImportTestDirect(TInt x);
void* doImportTestCBindingAsync1( void* /*x*/);
TInt doImportTestCBinding();

_LIT(KCalNameImportTestDirect, "ImportTothisatProvider");

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTChangeStatusTest::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTCalendarChangeNotifyTest::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CTChangeStatusTest::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTCalendarChangeNotifyTest::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        //TRY( "SendMessage",    CTDeleteMessageTest::SendMessage ),
        
        ENTRY( "NotifyAdd",       		CTCalendarChangeNotifyTest::NotifyAdd),
        ENTRY( "NotifyAddPosBased",     CTCalendarChangeNotifyTest::NotifyAddPosBased),
        ENTRY( "NotifyDelete",    		CTCalendarChangeNotifyTest::NotifyDelete),
        ENTRY( "NotifyDeletePosBased",  CTCalendarChangeNotifyTest::NotifyDeletePosBased),
        ENTRY( "NotifyUpdate",    		CTCalendarChangeNotifyTest::NotifyUpdate),
        ENTRY( "NotifyUpdatePosBased",  CTCalendarChangeNotifyTest::NotifyUpdatePosBased),
        ENTRY( "NotifyAddLocalUid", 	CTCalendarChangeNotifyTest::NotifyAddLocalUid),
        ENTRY( "NotifyDeleteLocalUid", 	CTCalendarChangeNotifyTest::NotifyDeleteLocalUid),
        ENTRY( "NotifyUpdateLocalUid",	CTCalendarChangeNotifyTest::NotifyUpdateLocalUid),
        ENTRY( "TestCancelPosBased",	CTCalendarChangeNotifyTest::TestCancelPosBased),
        ENTRY( "TestCancelInvalid",		CTCalendarChangeNotifyTest::TestCancelInvalid),
        ENTRY( "TestCancelMultiple",	CTCalendarChangeNotifyTest::TestCancelMultiple),
        ENTRY( "TestAsyncWithNoCancel",	CTCalendarChangeNotifyTest::TestAsyncWithNoCancel),
        };

    


    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

TInt ReqNotification( TInt aChangeType, TBool aLocalUid, TBool aPosBased = EFalse );
TInt ReqNotificationCancel( TInt aChangeType, TBool aLocalUid, TBool aPosBased = EFalse, TBool aInvalidId = EFalse, TBool aMultiCancel = EFalse);
TInt ReqNotificationWithoutWaitSch( TInt aChangeType, TBool aLocalUid, TBool aPosBased  );

   
TInt  CTCalendarChangeNotifyTest::NotifyAdd(CStifItemParser& /*aItem*/)
	{
	TInt result = KErrNone;
	__UHEAP_MARK;

	result = ReqNotification(1, EFalse);

	__UHEAP_MARKEND;
	return result;

    }

    
TInt  CTCalendarChangeNotifyTest::NotifyAddPosBased(CStifItemParser& /*aItem*/)
	{
	TInt result = KErrNone;
	__UHEAP_MARK;

	result = ReqNotification(1, EFalse, ETrue );

	__UHEAP_MARKEND;
	return result;

    }


TInt  CTCalendarChangeNotifyTest::NotifyDelete(CStifItemParser& /*aItem*/)
	{
	TInt result = KErrNone;
	__UHEAP_MARK;

	result = ReqNotification(2, EFalse);

	__UHEAP_MARKEND;
	return result;
    }

TInt  CTCalendarChangeNotifyTest::NotifyDeletePosBased(CStifItemParser& /*aItem*/)
	{
	TInt result = KErrNone;
	__UHEAP_MARK;

	result = ReqNotification(2, EFalse, ETrue);

	__UHEAP_MARKEND;
	return result;
    }

TInt  CTCalendarChangeNotifyTest::NotifyUpdate(CStifItemParser& /*aItem*/)
	{
	TInt result = KErrNone;
	__UHEAP_MARK;

	result = ReqNotification(3, EFalse);

	__UHEAP_MARKEND;
	return result;
    }

TInt  CTCalendarChangeNotifyTest::NotifyUpdatePosBased(CStifItemParser& /*aItem*/)
	{
	TInt result = KErrNone;
	__UHEAP_MARK;

	result = ReqNotification(3, EFalse, ETrue);

	__UHEAP_MARKEND;
	return result;
    }

TInt  CTCalendarChangeNotifyTest::NotifyAddLocalUid(CStifItemParser& /*aItem*/)
	{
	TInt result = KErrNone;
	__UHEAP_MARK;

	result = ReqNotification(1, ETrue);

	__UHEAP_MARKEND;
	return result;

    }

TInt  CTCalendarChangeNotifyTest::NotifyDeleteLocalUid(CStifItemParser& /*aItem*/)
	{
	TInt result = KErrNone;
	__UHEAP_MARK;

	result = ReqNotification(2, ETrue);

	__UHEAP_MARKEND;
	return result;
    }

TInt  CTCalendarChangeNotifyTest::NotifyUpdateLocalUid(CStifItemParser& /*aItem*/)
	{
	TInt result = KErrNone;
	__UHEAP_MARK;

	result = ReqNotification(3, ETrue);

	__UHEAP_MARKEND;
	return result;
    }
    
TInt  CTCalendarChangeNotifyTest::TestCancelPosBased(CStifItemParser& /*aItem*/)
	{
	TInt result = KErrNone;
	__UHEAP_MARK;

	result = ReqNotificationCancel(3, ETrue, ETrue);

	__UHEAP_MARKEND;
	return result;
    }

TInt  CTCalendarChangeNotifyTest::TestCancelInvalid(CStifItemParser& /*aItem*/)
	{
	TInt result = KErrNone;
	__UHEAP_MARK;

	result = ReqNotificationCancel( 3, ETrue, EFalse, ETrue );

	__UHEAP_MARKEND;
	return result;
    }
    
TInt  CTCalendarChangeNotifyTest::TestCancelMultiple(CStifItemParser& /*aItem*/)
	{
	TInt result = KErrNone;
	__UHEAP_MARK;

	result = ReqNotificationCancel(3, ETrue, EFalse, EFalse, ETrue );

	__UHEAP_MARKEND;
	return result;
    }

TInt  CTCalendarChangeNotifyTest::TestAsyncWithNoCancel(CStifItemParser& /*aItem*/)
	{
	TInt result = KErrNone;
	__UHEAP_MARK;

	result = ReqNotificationWithoutWaitSch(3, ETrue, EFalse );

	__UHEAP_MARKEND;
	return result;
    }

