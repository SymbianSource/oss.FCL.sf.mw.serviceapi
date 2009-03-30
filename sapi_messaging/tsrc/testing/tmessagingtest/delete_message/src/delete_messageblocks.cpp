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
#include "delete_message.h"
//#include <senduiconsts.h>
#include <CMsvAttachment.h>
#include "messagingservice.h"
#include "messageheader.h"

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
// Cdelete_message::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void Cdelete_message::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// Cdelete_message::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt Cdelete_message::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "test_1", Cdelete_message::Test1L ),

        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// Cdelete_message::ExampleL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//

TInt Cdelete_message::messageid_func(CStifItemParser& aItem,TInt& id)
  {
     TInt err = aItem.GetNextInt(id);
     if(err)
     {
      //iLog->Log(_L("Failed to Get message id"));
      return KErrGeneral;
     };
     return KErrNone;
  }  

TInt Cdelete_message::flag_func(CStifItemParser& aItem,TInt& flag)     
  {
     TInt err = aItem.GetNextInt(flag);  
     if(err)
     {
      //iLog->Log(_L("Failed to Get err code"));
      return KErrGeneral;
     };
     return KErrNone;
  } 


TInt Cdelete_message::Test1L( CStifItemParser& aItem )
    {

     __UHEAP_MARK;
     
     TInt id,flag;
     TMsvId iD;
     
     CMessagingService* service = (CMessagingService*)CMessagingService::NewL();
     CleanupStack::PushL(service);

     TInt err1 = messageid_func(aItem,id);  // get message id from cfg
     if(err1)
	  {
	   return KErrGeneral;
	  }	
     
     if(id == 1)
     {
      	 CMessagingService* mservice = (CMessagingService*)CMessagingService::NewL(); 	
	 	 CleanupStack::PushL(mservice);
	 	 CFilterParamInfo* mfilter = CFilterParamInfo::NewL();
	 	 CMsvEntrySelection* marray = NULL ;
	     TRAPD(err,mservice->GetIdListL(mfilter,0,NULL ,marray));
	     TInt index = 0;
	     CMessageHeader* headerarr = NULL;
	     mservice->GetNextHeaderL(mfilter, marray, index, NULL, headerarr);  
		 TMsvId message_id;
		 headerarr->GetMessageId(message_id);
		 iD = message_id;
	     delete headerarr; 
	     delete marray;
	     delete mfilter;                    
	     CleanupStack::PopAndDestroy(mservice);    
     }
     else
     {
      iD = id;                                // message id specified
     }
      
     TRAPD(err,service->DeleteMessageL(iD,NULL));          
     
     
     if(err == 0)
     {     

      CFilterParamInfo*  filter = CFilterParamInfo::NewL();
      filter->SetMessageIdFilter(iD);	
     
	  CMsvEntrySelection* array = NULL ;	      
	  TRAPD(error,service->GetIdListL(filter,0,NULL ,array));
	      
	  TInt index = 0;
	  CMessageHeader* headers = NULL;
	  service->GetNextHeaderL(filter, array, index, NULL, headers);
      
      delete array;
      delete filter;
      CleanupStack::PopAndDestroy(service);
      
      if(headers == NULL)
       {
        __UHEAP_MARKEND;
        return KErrNone;      
       }
      else
       {
         __UHEAP_MARKEND;
         return KErrGeneral; 
       } 
     }  
     else
     {
        err1 = flag_func(aItem,flag);       // get err code from cfg
        if(err1)
	    {
	     return KErrGeneral;
	    }   
       
       CleanupStack::PopAndDestroy(service);	   
       if(err == flag)
       {
         __UHEAP_MARKEND;
         return KErrNone;
       }  
       else
       {
         __UHEAP_MARKEND;
         return KErrGeneral; 
       }  
     }   
       
  }

// -----------------------------------------------------------------------------
// Cdelete_message::?member_function
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
/*
TInt Cdelete_message::?member_function(
   CItemParser& aItem )
   {

   ?code

   }
*/

// ========================== OTHER EXPORTED FUNCTIONS =========================
// None

//  End of File
