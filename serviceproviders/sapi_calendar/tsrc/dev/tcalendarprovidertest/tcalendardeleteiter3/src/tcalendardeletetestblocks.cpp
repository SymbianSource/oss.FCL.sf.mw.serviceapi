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
#include <Stiftestinterface.h>
#include <msvids.h> 
//#include <SendUiConsts.h>
#include <LiwCommon.h>
//#include <calendarinterface.h>

#include "delete.h"

#include "tcalendardeletetest.h"

#include "teststartconsolealarmserver2.h"

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
// CTLocTest::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTCalendarDeleteTest::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CTLocTest::RunMethodL
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
        //TRY( "SendMessage",    CTCalendarDeleteTest::SendMessage ),
        
        ENTRY( "DeleteAll",    CTCalendarDeleteTest::DeleteAll),
        ENTRY( "DeleteOnLuids",    CTCalendarDeleteTest::DeleteOnLuids),
        ENTRY( "DeleteOnGuids",    CTCalendarDeleteTest::DeleteOnGuids),
        ENTRY( "DeleteTimeRange",    CTCalendarDeleteTest::DeleteTimeRange),
        ENTRY( "DeleteTimeRangeBefore",    CTCalendarDeleteTest::DeleteTimeRangeBefore),
        ENTRY( "DeleteTimeRangeAfter",    CTCalendarDeleteTest::DeleteTimeRangeAfter),
        ENTRY( "DeleteWrongCalendar",    CTCalendarDeleteTest::DeleteWrongCalendar),
        ENTRY( "DeleteDefaultCalendar",    CTCalendarDeleteTest::DeleteDefaultCalendar),
        ENTRY( "DeleteOnLuidsWithTimeRange",    CTCalendarDeleteTest::DeleteOnLuidsWithTimeRange),
        ENTRY( "DeleteOnGuidsWithTimeRange",    CTCalendarDeleteTest::DeleteOnGuidsWithTimeRange),
        ENTRY( "DeleteTimeRangeSync",    CTCalendarDeleteTest::DeleteTimeRangeSync),
        ENTRY( "DeleteTimeRangeBeforeSync",    CTCalendarDeleteTest::DeleteTimeRangeBeforeSync),
        ENTRY( "DeleteTimeRangeAfterSync",    CTCalendarDeleteTest::DeleteTimeRangeAfterSync),
        ENTRY( "DeleteOnLuidsSync",    CTCalendarDeleteTest::DeleteOnLuidsSync),
        ENTRY( "DeleteOnLuidsWithTimeRangeSync",    CTCalendarDeleteTest::DeleteOnLuidsWithTimeRangeSync),
        ENTRY( "DeleteOnLuidsSync",    CTCalendarDeleteTest::DeleteOnLuidsSync),
        ENTRY( "DeleteOnLuidsWithTimeRangeSync",    CTCalendarDeleteTest::DeleteOnLuidsWithTimeRangeSync),
        ENTRY( "DeleteOnGuidsSync",    CTCalendarDeleteTest::DeleteOnGuidsSync),
        ENTRY( "DeleteOnGuidsWithTimeRangeSync",    CTCalendarDeleteTest::DeleteOnGuidsWithTimeRangeSync),

        };
	    const TInt count = sizeof( KFunctions ) / 
	                        sizeof( TStifFunctionInfo );

	    return RunInternalL( KFunctions, count, aItem );

    }
TInt  CTCalendarDeleteTest::DeleteAll(CStifItemParser& /*aItem*/)
	{
	int ret=0;
    int flag = 4;
    TBool async = ETrue;
    ret = DeleteAllAsync(flag, async);
    if(ret==0)
			return KErrNone;
	else	
			return KErrGeneral;
	}
	
TInt  CTCalendarDeleteTest::DeleteOnLuids(CStifItemParser& /*aItem*/)
	{
	int ret=0;
	int flag = 0;
    TBool async = ETrue;
    ret = DeleteLuidAsync(flag,async);
    if(ret==0)
			return KErrNone;
	else	
			return KErrGeneral;
	}

TInt  CTCalendarDeleteTest::DeleteOnLuidsSync(CStifItemParser& /*aItem*/)
	{
	int ret=0;
	int flag = 0;
    TBool async = EFalse;
    ret = DeleteLuidAsync(flag,async);
    if(ret==0)
			return KErrNone;
	else	
			return KErrGeneral;
	}
	
TInt  CTCalendarDeleteTest::DeleteOnLuidsWithTimeRange(CStifItemParser& /*aItem*/)
	{
	int ret=0;
	int flag = 1;
    TBool async = ETrue;
    ret = DeleteLuidAsync(flag,async);
    if(ret==0)
			return KErrNone;
	else	
			return KErrGeneral;
	}

TInt  CTCalendarDeleteTest::DeleteOnLuidsWithTimeRangeSync(CStifItemParser& /*aItem*/)
	{
	int ret=0;
	int flag = 1;
    TBool async = EFalse;
    ret = DeleteLuidAsync(flag,async);
    if(ret==0)
			return KErrNone;
	else	
			return KErrGeneral;
	}
	
TInt  CTCalendarDeleteTest::DeleteOnGuids(CStifItemParser& /*aItem*/)
	{
	int ret=0;
	int flag = 0;
    TBool async = ETrue;
    ret = DeleteGuidAsync(flag, async);
    if(ret==0)
			return KErrNone;
	else	
			return KErrGeneral;
	}
	
TInt  CTCalendarDeleteTest::DeleteOnGuidsSync(CStifItemParser& /*aItem*/)
	{
	int ret=0;
	int flag = 0;
    TBool async = EFalse;
    ret = DeleteGuidAsync(flag,async);
    if(ret==0)
			return KErrNone;
	else	
			return KErrGeneral;
	}


TInt  CTCalendarDeleteTest::DeleteOnGuidsWithTimeRange(CStifItemParser& /*aItem*/)
	{
	int ret=0;
	int flag = 1;
    TBool async = ETrue;
    ret = DeleteGuidAsync(flag,async);
    if(ret==0)
			return KErrNone;
	else	
			return KErrGeneral;
	}

TInt  CTCalendarDeleteTest::DeleteOnGuidsWithTimeRangeSync(CStifItemParser& /*aItem*/)
	{
	int ret=0;
	int flag = 1;
    TBool async = EFalse;
    ret = DeleteGuidAsync(flag,async);
    if(ret==0)
			return KErrNone;
	else	
			return KErrGeneral;
	}
		
TInt  CTCalendarDeleteTest::DeleteTimeRange(CStifItemParser& /*aItem*/)
	{
	int ret=0;
    //ret = DeleteAllSync();
    //ret = DeleteLuidAsync();
    int flag = 1;
    TBool async = ETrue;
    ret = DeleteAllAsync(flag, async);
    if(ret==0)
			return KErrNone;
	else	
			return KErrGeneral;
	}
	
TInt  CTCalendarDeleteTest::DeleteTimeRangeSync(CStifItemParser& /*aItem*/)
	{
	int ret=0;
    //ret = DeleteAllSync();
    //ret = DeleteLuidAsync();
    int flag = 1;
    TBool async = EFalse;
    ret = DeleteAllAsync(flag, async);
    if(ret==0)
			return KErrNone;
	else	
			return KErrGeneral;
	}
	
TInt  CTCalendarDeleteTest::DeleteTimeRangeBefore(CStifItemParser& /*aItem*/)
	{
	int ret=0;
    //ret = DeleteAllSync();
    //ret = DeleteLuidAsync();
    int flag = 2;
    TBool async = ETrue;
    ret = DeleteAllAsync(flag, async);
    if(ret==0)
			return KErrNone;
	else	
			return KErrGeneral;
	}

TInt  CTCalendarDeleteTest::DeleteTimeRangeBeforeSync(CStifItemParser& /*aItem*/)
	{
	int ret=0;
    //ret = DeleteAllSync();
    //ret = DeleteLuidAsync();
    int flag = 2;
    TBool async = EFalse;
    ret = DeleteAllAsync(flag, async);
    if(ret==0)
			return KErrNone;
	else	
			return KErrGeneral;
	}
	
TInt  CTCalendarDeleteTest::DeleteTimeRangeAfter(CStifItemParser& /*aItem*/)
	{
	int ret=0;
    //ret = DeleteAllSync();
    //ret = DeleteLuidAsync();
    int flag = 3;
    TBool async = ETrue;
    ret = DeleteAllAsync(flag, async);
    if(ret==0)
			return KErrNone;
	else	
			return KErrGeneral;
	}
	
TInt  CTCalendarDeleteTest::DeleteTimeRangeAfterSync(CStifItemParser& /*aItem*/)
	{
	int ret=0;
    //ret = DeleteAllSync();
    //ret = DeleteLuidAsync();
    int flag = 3;
    TBool async = EFalse;
    ret = DeleteAllAsync(flag, async);
    if(ret==0)
			return KErrNone;
	else	
			return KErrGeneral;
	}
		
TInt  CTCalendarDeleteTest::DeleteWrongCalendar(CStifItemParser& /*aItem*/)
	{
	int ret=0;
    //ret = DeleteAllSync();
    //ret = DeleteLuidAsync();
    ret = DeleteWrongSync();
    if(ret==0)
			return KErrGeneral;
	else	
			return KErrNone;
	}
	
TInt  CTCalendarDeleteTest::DeleteDefaultCalendar(CStifItemParser& /*aItem*/)
	{
	int ret=0;
    //ret = DeleteAllSync();
    //ret = DeleteLuidAsync();
    ret = DeleteDefaultSync();
    if(ret==0)
			return KErrGeneral;
	else	
			return KErrNone;
	}
	
