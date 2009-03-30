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
#include "register_message.h"
//#include <senduiconsts.h>
#include <CMsvAttachment.h>
#include "messagingservice.h"
#include "messageheader.h"
#include "async.h"

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
// Cregister_message::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void Cregister_message::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// Cregister_message::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt Cregister_message::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "test_1", Cregister_message::Test1L ),

        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// Cregister_message::ExampleL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//

TInt iResult;

CMsgCallbackHeader* CMsgCallbackHeader::NewL(CActiveSchedulerWait* aWaitSchedular, CMessagingService* s)
	{
	CMsgCallbackHeader* self = new (ELeave) CMsgCallbackHeader(aWaitSchedular, s);
	return self;
	}

Cheader_test* Cheader_test::NewL()
	{
	Cheader_test* self = new(ELeave)Cheader_test();
	self->ConstructL();
	return self;
	}


Cheader_test::~Cheader_test()
	{
	Cancel();
	
	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();
	
	if(iMessagingService)
		delete iMessagingService;
	
	if(iWaitSchedular)
		delete iWaitSchedular;
	}


void Cheader_test::ConstructL()
	{
	CActiveScheduler::Add(this);
	iMessagingService = CMessagingService::NewL();
	iWaitSchedular = new(ELeave) CActiveSchedulerWait();
	}


Cheader_test::Cheader_test() :
CActive(EPriorityStandard)
	{
	}


void Cheader_test::DoCancel()
	{
		
	}


void Cheader_test::RunL()
	{
	TestFunc();
	}


void Cheader_test::Start()
	{
	iCallBack = CMsgCallbackHeader::NewL(iWaitSchedular, iMessagingService); 	
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}
	

void CMsgCallbackHeader::NotifyResultL(TInt aErrCode, TAny* aResult)
	{
    
	  if(aErrCode == KErrNone)
		{				
			CMessageHeader* headerArr = NULL;
			headerArr = (CMessageHeader*)aResult;
			headerArr->GetMessageId(messageid);
			
			CMessagingService* service = (CMessagingService*)CMessagingService::NewL();			
			CFilterParamInfo*  filter = CFilterParamInfo::NewL();
			filter->SetMessageIdFilter(messageid);
//		    TMsvSorting sort = EMsvSortByDateReverse;
//		    filter->SetSortType(sort); 

			User::After(1000000);
		
			CMsvEntrySelection* array = NULL ;
      		TRAPD(errc,service->GetIdListL(filter ,0 ,NULL ,array)); 
      		
      		
      	    TInt index = 0;
			CMessageHeader* headers = NULL;
			
			service->GetNextHeaderL(filter, array, index, NULL, headers);
			
			if(headers == NULL)
			  iResult = KErrGeneral;
			else
			{  				
		     TMsvId message_id;
			 headers->GetMessageId(message_id);
			 delete headers;
			 delete array;
			 delete filter;
			 delete service;
			
			 if(messageid == message_id)
	           iResult = KErrNone;
	      	 else
	           iResult = KErrGeneral; 
	        }   
	    }      
	    else
	    {    
	       if(aErrCode)
	         iResult = KErrNone;
	       else
	         iResult = KErrGeneral;          
        }
	 iWaitSchedular->AsyncStop();
	
	}
	
     
      
void Cheader_test::TestFunc()
	{
    
    TRAPD(err, iMessagingService->RequestNotification(ENewMessage ,iCallBack)); 
    
 	}



TInt Cregister_message::Test1L( CStifItemParser& aItem )
    {
 
    
            Cheader_test* test = Cheader_test::NewL();

	        test->Start();    

            test->CancelNotification();
            delete test;

            TInt ret = iResult;
            return ret;


    }

// -----------------------------------------------------------------------------
// Cregister_message::?member_function
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
/*
TInt Cregister_message::?member_function(
   CItemParser& aItem )
   {

   ?code

   }
*/

// ========================== OTHER EXPORTED FUNCTIONS =========================
// None

//  End of File
