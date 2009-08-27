/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:   
*
*/

// [INCLUDE FILES] - do not remove
#include <e32svr.h>
#include <e32base.h>
#include <StifParser.h>
#include <Stiftestinterface.h>
#include <CMsvAttachment.h>
#include "get_message_async.h"
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

TInt iResult;
TInt iPosneg;

TInt Cget_message_async::messageid_func(CStifItemParser& aItem,TInt& id)
  {
     TInt err = aItem.GetNextInt(id);
     if(err)
     {
      ////iLog->Log(_L("Failed to Get message id"));
      return KErrGeneral;
     };
     return KErrNone;
  }   
     
TInt Cget_message_async::fromarray_func(CStifItemParser& aItem,TPtrC& fromarray)     
  {
     TInt err = aItem.GetNextString(fromarray);  
     if(err)
     {
      //iLog->Log(_L("Failed to Get from array"));
      return KErrGeneral;
     };
     return KErrNone;
  }   
  
TInt Cget_message_async::subject_func(CStifItemParser& aItem,TPtrC& subj)     
  {
     TInt err = aItem.GetNextString(subj);  
     if(err)
     {
      //iLog->Log(_L("Failed to Get subject"));
      return KErrGeneral;
     };
     return KErrNone;
  }   

TInt Cget_message_async::sort_func(CStifItemParser& aItem,TInt& sorttype)     
  {
     TInt err = aItem.GetNextInt(sorttype);  
     if(err)
     {
      //iLog->Log(_L("Failed to Get sort type"));
      return KErrGeneral;
     };
     return KErrNone;
  } 

TInt Cget_message_async::mtm_func(CStifItemParser& aItem,TPtrC& mtmtype)     
  {
     TInt err = aItem.GetNextString(mtmtype);  
     if(err)
     {
      //iLog->Log(_L("Failed to Get mtm type"));
      return KErrGeneral;
     };
     return KErrNone;
  } 
    
TInt Cget_message_async::flag_func(CStifItemParser& aItem,TInt& flag)     
  {
     TInt err = aItem.GetNextInt(flag);  
     if(err)
     {
      //iLog->Log(_L("Failed to Get date flag or err code"));
      return KErrGeneral;
     };
     return KErrNone;
  } 
  
TInt Cget_message_async::date_func(CStifItemParser& aItem,TInt& year,TInt& month,TInt& day,TInt& hour,TInt& min,TInt& sec,TInt& microsec)
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
  
 TInt Cget_message_async::getsub_func(CStifItemParser& aItem,TPtrC& sub)
  {
     TInt err = aItem.GetNextString(sub);
     if(err)
     {
      //iLog->Log(_L("Failed to Get message subject to verify"));
      return KErrGeneral;
     };
     return KErrNone;
  }
 
 TInt Cget_message_async::posneg_func(CStifItemParser& aItem,TInt& posneg)     
   {
      TInt err = aItem.GetNextInt(posneg);  
      if(err)
      {
       //iLog->Log(_L("Failed to Get date flag or err code"));
       return KErrGeneral;
      };
      return KErrNone;
   } 
 
 void CMsgCallbackHeader::NotifyResultL( TInt aErrCode, TAny* aResult )
     {
     
     }

 void CMsgCallbackHeader::HandleGetlistL( TInt aErrCode, CMsvEntrySelection* aEntrySelection, CFilterParamInfo* aFilter )
    {
    TInt err=aErrCode;
    Cheader_test* test2 = Cheader_test::NewL();
    CFilterParamInfo* f=aFilter;
    CMsvEntrySelection* e=aEntrySelection;
    TInt index=0;
    CMessageHeader* header = NULL;
    TInt checkposneg = test2->getposneg();
   iservice->GetNextHeaderL(f, e, index, NULL, header);
   if(!iPosneg)
     {
     if(header)
         iResult=KErrGeneral;
     else
         iResult=KErrNone;
     }
       
   else if(aErrCode==KErrNone)
       iResult=KErrNone;
   else
       iResult=KErrNone;
   delete header;
   delete test2;
    delete f;
    delete e;
        
         iWaitSchedular->AsyncStop();
    }

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
     


 void Cheader_test::set(CFilterParamInfo* pi)
     {
      v = pi;
     } 
 
 void Cheader_test::setposneg(TInt aFlag)
     {
     posnegflag = aFlag;
     }

 CFilterParamInfo* Cheader_test::get(void) 
     { 
      return v;
     } 
 
 TInt Cheader_test::getposneg(void) 
     {
     return posnegflag;
     }
 /*void Cheader_test::HandleGetlistL(TInt aErrCode, CMsvEntrySelection* aEntryselection,CFilterParamInfo* aFilterParams)
     { 
       
      iResult=KErrNone;
      iWaitSchedular->AsyncStop();
     }
 void Cheader_test::NotifyResultL(TInt aErrCode,TAny* aResult)
     {
     
     }*/
     
 int memorycleanflag = 0;     
       
 void Cheader_test::TestFunc()
     {

     CFilterParamInfo* arg = get();
     CMsvEntrySelection* en = NULL;
     
     TRAPD(err, iMessagingService->GetIdListL(arg ,0,iCallBack,en)); 
     
     if(err!=0)
      {
      memorycleanflag = 1;
       iResult = KErrNone;
       iWaitSchedular->AsyncStop();
      }      
     delete arg;
     }




// -----------------------------------------------------------------------------
// Cget_message_async::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void Cget_message_async::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// Cget_message_async::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt Cget_message_async::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "Example", Cget_message_async::ExampleL ),
        ENTRY( "test_1",Cget_message_async::Test1L)
        //ADD NEW ENTRY HERE
        // [test cases entries] - Do not remove

        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// Cget_message_async::ExampleL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Cget_message_async::ExampleL( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( Kget_message_async, "get_message_async" );
    _LIT( KExample, "In Example" );
    TestModuleIf().Printf( 0, Kget_message_async, KExample );
    // Print to log file
    iLog->Log( KExample );

    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, Kget_message_async, 
                                KParam, i, &string );
        i++;
        }

    return KErrNone;

    }

// -----------------------------------------------------------------------------
// Cget_message_async::?member_function
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//

TInt Cget_message_async::Test1L( CStifItemParser& aItem )
    {

   
    
    TInt id,sorttype,flag,year,month,day,hour,min,sec,microsec,posneg;
    TPtrC subj,mtmtype,fromarray;
    bool test = TRUE;
    __UHEAP_MARK;
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
        err1=posneg_func(aItem,posneg);
        if(err1)
         {
         return KErrGeneral;
         }
        iPosneg=posneg;
        Cheader_test* test1 = Cheader_test::NewL();
            
            test1->set(filter);
            test1->setposneg(posneg);
            test1->Start();
        delete test1;
        __UHEAP_MARKEND;
        return iResult;
           
    }
/*
TInt Cget_message_async::?member_function(
   CItemParser& aItem )
   {

   ?code

   }
*/

// ========================== OTHER EXPORTED FUNCTIONS =========================
// None

//  [End of File] - Do not remove
