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
#include <e32base.h>
#include <e32svr.h>
#include <StifParser.h>
#include <Stiftestinterface.h>
//#include <senduiconsts.h>
#include <CMsvAttachment.h>
#include "messagingservice.h"
#include "messageheader.h"
#include "get_header_message.h"

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
// Cget_header_message::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void Cget_header_message::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// Cget_header_message::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt Cget_header_message::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "test_1", Cget_header_message::Test1L ),

        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// Cget_header_message::ExampleL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Cget_header_message::messageid_func(CStifItemParser& aItem,TInt& id)
  {
     TInt err = aItem.GetNextInt(id);
     if(err)
     {
      ////iLog->Log(_L("Failed to Get message id"));
      return KErrGeneral;
     };
     return KErrNone;
  }   
     
TInt Cget_header_message::fromarray_func(CStifItemParser& aItem,TPtrC& fromarray)     
  {
     TInt err = aItem.GetNextString(fromarray);  
     if(err)
     {
      //iLog->Log(_L("Failed to Get from array"));
      return KErrGeneral;
     };
     return KErrNone;
  }   
  
TInt Cget_header_message::subject_func(CStifItemParser& aItem,TPtrC& subj)     
  {
     TInt err = aItem.GetNextString(subj);  
     if(err)
     {
      //iLog->Log(_L("Failed to Get subject"));
      return KErrGeneral;
     };
     return KErrNone;
  }   

TInt Cget_header_message::sort_func(CStifItemParser& aItem,TInt& sorttype)     
  {
     TInt err = aItem.GetNextInt(sorttype);  
     if(err)
     {
      //iLog->Log(_L("Failed to Get sort type"));
      return KErrGeneral;
     };
     return KErrNone;
  } 

TInt Cget_header_message::mtm_func(CStifItemParser& aItem,TPtrC& mtmtype)     
  {
     TInt err = aItem.GetNextString(mtmtype);  
     if(err)
     {
      //iLog->Log(_L("Failed to Get mtm type"));
      return KErrGeneral;
     };
     return KErrNone;
  } 
    
TInt Cget_header_message::flag_func(CStifItemParser& aItem,TInt& flag)     
  {
     TInt err = aItem.GetNextInt(flag);  
     if(err)
     {
      //iLog->Log(_L("Failed to Get date flag or err code"));
      return KErrGeneral;
     };
     return KErrNone;
  } 
  
TInt Cget_header_message::date_func(CStifItemParser& aItem,TInt& year,TInt& month,TInt& day,TInt& hour,TInt& min,TInt& sec,TInt& microsec)
  {
    
    TInt err = aItem.GetNextInt(year);
     if(err)
     {
      //iLog->Log(_L("Failed to Get year"));
      return KErrGeneral;
     };
    
    err = aItem.GetNextInt(month);
    if(err)
     {
      //iLog->Log(_L("Failed to Get month"));
      return KErrGeneral;
     };
  
    err = aItem.GetNextInt(day);
    if(err)
     {
      //iLog->Log(_L("Failed to Get day")); 
      return KErrGeneral;
     };

    err = aItem.GetNextInt(hour);
    if(err)
     {
      //iLog->Log(_L("Failed to Get hour")); 
      return KErrGeneral;
     };
    
    err = aItem.GetNextInt(min);
    if(err)
     {
      //iLog->Log(_L("Failed to Get min")); 
      return KErrGeneral;
     };
    
    err = aItem.GetNextInt(sec);
    if(err)
     {
      //iLog->Log(_L("Failed to Get sec")); 
      return KErrGeneral;
     };
     
    err = aItem.GetNextInt(microsec);
    if(err)
     {
      //iLog->Log(_L("Failed to Get microsec")); 
      return KErrGeneral;
     };
   return KErrNone;
  } 
  
 TInt Cget_header_message::getsub_func(CStifItemParser& aItem,TPtrC& sub)
  {
     TInt err = aItem.GetNextString(sub);
     if(err)
     {
      //iLog->Log(_L("Failed to Get message subject to verify"));
      return KErrGeneral;
     };
     return KErrNone;
  }    



TInt Cget_header_message::Test1L( CStifItemParser& aItem )
  {
  
    __UHEAP_MARK;
    
    TInt id,sorttype,flag,year,month,day,hour,min,sec,microsec;
    TPtrC subj,mtmtype,fromarray;
    bool test = TRUE;
    
    CMessagingService* service = (CMessagingService*)CMessagingService::NewL(); 	
 	CleanupStack::PushL(service);
 	
 	CFilterParamInfo* filter = CFilterParamInfo::NewL();

 	        
    TInt err1 = messageid_func(aItem,id); 
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
     filter->SetMessageIdFilter(message_id);
     delete headerarr; 
     marray->Reset();
     delete marray;
     delete mfilter;           
     CleanupStack::PopAndDestroy(mservice);                  
    }
    else if(id == 0)
    {
     filter->SetMessageIdFilter(NULL);              
    } 
    else
    {
     TMsvId iD = id;
     filter->SetMessageIdFilter(iD);                  // message id filter 
    }
       
        
    err1 = fromarray_func(aItem,fromarray); 
    if(err1)
	{
	 return KErrGeneral;
	}
	
	_LIT(Knull,"NULL");
	if(fromarray.CompareF(Knull))
	{    
     _LIT(Kaddr,"AddrEnd");
	 while(fromarray != Kaddr)
	   {	   
        filter->AddFromL(fromarray);                  // from address filter 
	    err1 = fromarray_func(aItem,fromarray); 
	    if(err1)
		 {
		  return KErrGeneral;
		 }   	  	   
	   }    	 
  	} 
    else
    {
//     filter->AddFromL(NULL);
    }
    
    
    
        
    err1 = subject_func(aItem,subj); 
    if(err1)
	{
	 return KErrGeneral;
	}
	if(subj.CompareF(Knull))
	{
     filter->SetSubjectL(subj);                      // subject filter
    } 
    else
    {
//    filter->SetSubjectL(NULL); 
    }
    
    
        
    err1 = sort_func(aItem,sorttype); 
    if(err1)
	{
	 return KErrGeneral;
	}
    
    TMsvSorting sort= (TMsvSorting)sorttype ;  
    filter->SetSortType(sort) ;                     // sort filter
    
    
    
        
    err1 = mtm_func(aItem,mtmtype); 
    if(err1)
	{
	 return KErrGeneral;
	}
	
	if(mtmtype.CompareF(Knull))
	{        
      _LIT(Kmt,"MtmEnd");
	  while(mtmtype != Kmt)
	   {	   
        if( filter->AddMtmL(mtmtype) == KErrNone ) //code changed by Venkat
	        {
	        err1 = mtm_func(aItem,mtmtype); 
		    if(err1)
				{				
				return KErrGeneral;
				}	
	        }// message type filter 
	    else   
		    {
		    delete filter;
		    CleanupStack::PopAndDestroy( service );
		    return KErrNone;
		    }        
       } 
    }  
    else
    {
//      filter.iMtmArray(NULL);     
    }  
    
    
    
    
    err1 = flag_func(aItem,flag);                   // start date as a filter(1) or not(0)
    if(err1)
	 {
	  return KErrGeneral;
	 }  
	   
	if(flag)                  
    {    
      err1 = date_func(aItem,year,month,day,hour,min,sec,microsec);
      if(err1)
	  {
	   return KErrGeneral;
      }
      TDateTime start(year,(TMonth)month,day,hour,min,sec,microsec);
      TTime startdate(start);
      filter->SetStartDateFilter(startdate);        // start date filter  
    }
    else
    {
//      filter->SetStartDateFilter(NULL) ;
    }
    
    
    
    
    err1 = flag_func(aItem,flag);                  // end date as a filter(1) or not(0) 
    if(err1)
	 {
	  return KErrGeneral;
	 }  
	   
	if(flag)                  
    {    
      err1 = date_func(aItem,year,month,day,hour,min,sec,microsec);
	  if(err1)
	  {
	   return KErrGeneral;
      }
	
      TDateTime end(year,(TMonth)month,day,hour,min,sec,microsec);
      TTime enddate(end) ;     
      filter->SetEndDate(enddate) ;                // end date filter
    }
    else
    {
//      filter->SetEndDate(NULL) ;
    }  
       
       
        
    CMsvEntrySelection* array = NULL ;

    TRAPD(err,service->GetIdListL(filter,0,NULL ,array));  
    
  
  	
    if(err == 0)                           
    {
     
	     TInt index = 0; 
	     for(;;)
		 {
			CMessageHeader* headers = NULL;
			service->GetNextHeaderL(filter, array, index, NULL, headers);
			if(headers)
				{
//			     if((header->Mtm().FindF(_L("SMS")) != KErrNotFound) && (header->From().FindF(_L("9008032761")) != KErrNotFound))	

			     TPtrC subject = headers->Subject();
			     
			     TBool attflag;
			     headers->GetAttachFlag(attflag);
			     TMsvPriority prior;
			     headers->GetPriorityFlag(prior);
			     TUid u_id;
			     headers->GetMtmId(u_id);
			     TTime time;
			     headers->GetTime(time);
			     
			     //headers->SetPriorityFlag(TMsvPriority(0));
			     //headers->SetPriorityFlag(TMsvPriority(2));
			     //headers->SetPriorityFlag(TMsvPriority(6));

			     TMsvId id_l = headers->MessageId();
			     TBool fl_l = headers->AttachFlag();
			     TBool fg_l = headers->UnreadFlag();
			     TPtrC pr_l = headers->Priority();
			     TTime ti_l = headers->Time();
			     TPtrC mt_l = headers->Mtm();
			     TPtrC fr_l = headers->From();				
				 TPtrC sub;
				 _LIT(Kblank,"\x2029");
				 TInt err2 = getsub_func(aItem,sub);         // get subject from cfg	
		    	 if(err2)
				 {
			      delete headers;
			      delete array;
			      delete filter;
			      CleanupStack::PopAndDestroy(service);
				  return KErrGeneral;
				 }
				
				 if((subject.FindF(sub)!= KErrNotFound) || (subject == Kblank) || (attflag!=0) )     // compare message subject
					  {
					   test = TRUE;
					  } 
				 	 else
					  {
					  delete headers;
					  headers = NULL;
					   test = FALSE;  		  
					   break;
					  }
				 delete headers;
				}
			else 
			    break;	
			
		 }

	      delete array;
	      delete filter;

	      CleanupStack::PopAndDestroy(service);
	      
	      if(test == TRUE)                             // all ids verified
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
       err1 = flag_func(aItem,flag);              // get err code from cfg
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
// Cget_header_message::?member_function
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
/*
TInt Cget_header_message::?member_function(
   CItemParser& aItem )
   {

   ?code

   }
*/

// ========================== OTHER EXPORTED FUNCTIONS =========================
// None

//  End of File
