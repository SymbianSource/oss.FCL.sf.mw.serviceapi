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
#include <msvids.h> 
#include <msvapi.h> 
#include "messageheader.h"
#include "messagingservice.h"
////#include <senduiconsts.h>
#include "tdeletemessagetest.h"




// -----------------------------------------------------------------------------
// CTDeleteMessageTest::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTDeleteMessageTest::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CTDeleteMessageTest::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTDeleteMessageTest::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        //TRY( "SendMessage",    CTDeleteMessageTest::SendMessage ),
        
        ENTRY( "DeleteMessageSms",    CTDeleteMessageTest::DeleteMessageSms),
        ENTRY( "DeleteMessageMms",    CTDeleteMessageTest::DeleteMessageMms),
        ENTRY( "DeleteMessageInvalid",    CTDeleteMessageTest::DeleteMessageInvalid),

        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }




     
TInt  CTDeleteMessageTest::DeleteMessageSms(CStifItemParser& /*aItem*/)
	{
	__UHEAP_MARK;
	
	TInt result = KErrNone;
	
	CMessagingService* test = (CMessagingService* ) CMessagingService::NewL() ; 
	
	CleanupStack::PushL(test);	

	CFilterParamInfo* filterParams = CFilterParamInfo::NewL();

	filterParams->AddMtmL(_L("SMS"));
	
	CMsvEntrySelection* entrySelection = NULL;
	
	test->GetIdListL( filterParams, 0, NULL, entrySelection );
	
	if ( entrySelection && ( entrySelection->Count() > 0 ))
		{
		TMsvId messageid;

		CMessageHeader* header = NULL;
		
		TInt index = 0;
		test->GetNextHeaderL( filterParams, entrySelection, index, NULL, header );
		if ( header )
			{
			header->GetMessageId( messageid );
			delete header;
			header = NULL;
			
			test->DeleteMessageL( messageid, NULL );
			
			TRAPD( err, test->DeleteMessageL( messageid, NULL ));
			
			if ( err == KErrNone )
				result = KErrGeneral;
			}
		}
		
	entrySelection->Reset();
	delete entrySelection;
	delete filterParams;

	CleanupStack::PopAndDestroy(test);	

	__UHEAP_MARKEND;
	
	return result;
	}



TInt  CTDeleteMessageTest::DeleteMessageMms(CStifItemParser& /*aItem*/)
	{
	__UHEAP_MARK;
	
	TInt result = KErrNone;
	
	CMessagingService* test = (CMessagingService* ) CMessagingService::NewL() ; 
	
	CleanupStack::PushL(test);	

	CFilterParamInfo* filterParams = CFilterParamInfo::NewL();

	filterParams->AddMtmL(_L("MMS"));
	
	CMsvEntrySelection* entrySelection = NULL;
	
	test->GetIdListL( filterParams, 0, NULL, entrySelection );
	
	if ( entrySelection && ( entrySelection->Count() > 0 ))
		{
		TMsvId messageid;

		CMessageHeader* header = NULL;
		
		TInt index = 0;
		test->GetNextHeaderL( filterParams, entrySelection, index, NULL, header );
		if ( header )
			{
			header->GetMessageId( messageid );
			delete header;
			header = NULL;
			
			test->DeleteMessageL( messageid, NULL );
			
			TRAPD( err, test->DeleteMessageL( messageid, NULL ));
			
			if ( err == KErrNone )
				result = KErrGeneral;
	
			}
		}
		
	entrySelection->Reset();
	delete entrySelection;
	delete filterParams;

	CleanupStack::PopAndDestroy(test);	

	__UHEAP_MARKEND;
	
	return result;
	}


TInt  CTDeleteMessageTest::DeleteMessageInvalid(CStifItemParser& /*aItem*/)
	{

	__UHEAP_MARK;

	CMessagingService* test = (CMessagingService* ) CMessagingService::NewL() ; 
	CleanupStack::PushL(test);	


	TRAPD(err, test->DeleteMessageL(-1,NULL));


	CleanupStack::PopAndDestroy(1) ;

	__UHEAP_MARKEND;
	
	if(err != KErrNone)
	{	
		return KErrNone;
	}
	else
	{
		return err;
	}
}

