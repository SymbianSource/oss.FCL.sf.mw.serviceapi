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
#include <StifTestInterface.h>
#include "async_send_message.h"
//#include <senduiconsts.h>
#include <cmsvattachment.h>
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
// Casync_send_message::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void Casync_send_message::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// Casync_send_message::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt Casync_send_message::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "test_1", Casync_send_message::Test1L ),

        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// Casync_send_message::ExampleL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//

TInt iResult;

TInt Casync_send_message::fromarray_func(CStifItemParser& aItem,TPtrC& fromarray)     
  {
     TInt err = aItem.GetNextString(fromarray);  
     if(err)
     {
      //iLog->Log(_L("Failed to Get from array"));
      return KErrGeneral;
     };
     return KErrNone;
  }   


TInt Casync_send_message::messtype_func(CStifItemParser& aItem,TPtrC& messtype)     
  {
     TInt err = aItem.GetNextString(messtype);  
     if(err)
     {
      //iLog->Log(_L("Failed to Get message type"));
      return KErrGeneral;
     };
     return KErrNone;
  }   

TInt Casync_send_message::subject_func(CStifItemParser& aItem,TPtrC& subj)     
  {
     TInt err = aItem.GetNextString(subj);  
     if(err)
     {
      //iLog->Log(_L("Failed to Get subject"));
      return KErrGeneral;
     };
     return KErrNone;
  }   
 

TInt Casync_send_message::attach_func(CStifItemParser& aItem,TPtrC& attachm)     
  {
     TInt err = aItem.GetNextString(attachm);  
     if(err)
     {
      //iLog->Log(_L("Failed to Get attachments path"));
      return KErrGeneral;
     };
     return KErrNone;
  }
  
TInt Casync_send_message::attachtype_func(CStifItemParser& aItem,TPtrC& attachfiletype)     
  {
     TInt err = aItem.GetNextString(attachfiletype);  
     if(err)
     {
      //iLog->Log(_L("Failed to Get attachments type"));
      return KErrGeneral;
     };
     return KErrNone;
  }     
     

TInt Casync_send_message::template_func(CStifItemParser& aItem,TInt& templateid)     
  {
     TInt err = aItem.GetNextInt(templateid);  
     if(err)
     {
      //iLog->Log(_L("Failed to Get template id"));
      return KErrGeneral;
     };
     return KErrNone;
  } 
  

TInt Casync_send_message::editor_func(CStifItemParser& aItem,TInt& editorl)     
  {
     TInt err = aItem.GetNextInt(editorl);  
     if(err)
     {
      //iLog->Log(_L("Failed to Get launch flag for editor"));
      return KErrGeneral;
     };
     return KErrNone;
  }  
TInt Casync_send_message::messageid_func(CStifItemParser& aItem,TInt& id)
  {
     TInt err = aItem.GetNextInt(id);
     if(err)
     {
      //iLog->Log(_L("Failed to Get message id"));
      return KErrGeneral;
     };
     return KErrNone;
  }   

TInt Casync_send_message::body_func(CStifItemParser& aItem,TPtrC& body)     
    {
     TInt err = aItem.GetNextString(body);  
     if(err)
      {
      //iLog->Log(_L("Failed to Get subject"));
      return KErrGeneral;
      };
     return KErrNone;
    }   

TInt Casync_send_message::sender_func(CStifItemParser& aItem,TPtrC& sender)     
    {
     TInt err = aItem.GetNextString(sender);  
     if(err)
      {
      //iLog->Log(_L("Failed to Get sender"));
      return KErrGeneral;
      };
     return KErrNone;
    }  
    
TInt Casync_send_message::rec_func(CStifItemParser& aItem,TPtrC& recarray)     
    {
     TInt err = aItem.GetNextString(recarray);  
     if(err)
      {
      //iLog->Log(_L("Failed to Get recarray"));
      return KErrGeneral;
      };
     return KErrNone;
    }      

TInt Casync_send_message::flag_func(CStifItemParser& aItem,TInt& flag)     
  {
     TInt err = aItem.GetNextInt(flag);  
     if(err)
     {
      //iLog->Log(_L("Failed to Get flag id"));
      return KErrGeneral;
     };
     return KErrNone;
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
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}
	


void Cheader_test::set(CSendMessageParams* pi)
    {
     v = pi;
    } 

CSendMessageParams* Cheader_test::get(void) 
    { 
     return v;
    }  

void Cheader_test::NotifyResultL(TInt aErrCode, TAny* aResult)
	{ 
      
	if(aErrCode == KErrNone)
	   {
			
			if(exflag == 1)
           {
            User::Leave(-9);
           } 
			
/*		#if defined(__WINSCW__) || defined(__WINS__)	
		  
		  TBool test = TRUE;
		  CMessagingService* service = (CMessagingService*)CMessagingService::NewL();
			  
		  CFilterParamInfo*  filter = CFilterParamInfo::NewL();
      
	      TMsvSorting sort = EMsvSortByDateReverse;
	      filter->SetSortType(sort);           //  sort by date reverse      
	      
	      CMsvEntrySelection* array = NULL ;

	      TRAPD(err,service->GetIdListL(filter,0,NULL ,array));  
	      
	      TInt index = 0;
      
			CMessageHeader* headers = NULL;
			service->GetNextHeaderL(filter, array, index, NULL, headers);
			_LIT(Kblanksms,"\x2029");
			_LIT(Kblankmms,"");
			
			if(headers)
			{

			     TPtrC subject = headers->Subject();
			     TPtrC from = headers->From();

				 TPtrC sub,fr;	

			     if( ((subject == Kblanksms)||(subject == Kblankmms)||(subject.FindF(b)!= KErrNotFound)) && (r[0] == from))     // compare message subject
				 {
				  test = TRUE;
				 } 
				 else
				 {
				  test = FALSE;  		  
				 }
				 delete headers;
			}
	        else
	        {
	         test = FALSE;
	        }*/

		
/*			for(TInt i=0;i<attcnt;i++)
		      {
		       CMessageAttachInfo* obj = detail->iAttachEntries->At(i);
		       obj->iFile.Close();
		      } */

	/*		delete array;
			delete filter;
			delete service;
			
			if(test == TRUE)
	           iResult = KErrNone;
	      	else
	           iResult = KErrGeneral; 
	           
	     #else*/
	     
           iResult =  KErrNone;         
           
//         #endif   
	    }      
	    else
	    {   
           if(aErrCode == -9)
           {
            iResult = KErrNone;
            User::Leave(-9);
           }  
	       if(aErrCode == pick2)
	         iResult = KErrNone;
	       else
	         iResult = KErrGeneral; 
            
        }

	 iWaitSchedular->AsyncStop();
	}
	
int memorycleanflag = 0;     
      
void Cheader_test::TestFunc()
	{

    CSendMessageParams* arg = get();
    
    TRAPD(err, iMessagingService->SendMessageL(arg ,this)); 
    
    if(err!=0)
     {
     memorycleanflag = 1;
      iResult = KErrNone;
      iWaitSchedular->AsyncStop();
     }      
    
 	if(canflag == 1)
 	{
 	 TInt c1 = iMessagingService->Cancel(1);
 	 iMessagingService->Cancel(0);
 	}
 	
 	}




TInt Casync_send_message::Test1L( CStifItemParser& aItem )
    {

	
	TPtrC fromarray,messtype,subj,attachfiletype,attachm,body,sender,recarray;
    TInt templateid,editorl,flag,flag1,flag2,count1=0;
    
    
    CSendMessageParams*  send = CSendMessageParams::NewL();
    
   
    TInt err1 = fromarray_func(aItem,fromarray); 
    if(err1)
	{
	 return KErrGeneral;
	}    
	
	_LIT(Knull,"NULL");
	if(fromarray.CompareF(Knull))
	{	    	     	 
	 _LIT(Kfin,"AddrEnd");
	 while(fromarray != Kfin)
	 {	   
	   count1++;
	   send->AddRecipientL(fromarray,EMsvRecipientTo);    // recipient array
	   err1 = fromarray_func(aItem,fromarray); 
	   if(err1)
		{
		 return KErrGeneral;
		}   	  	   
	 }  
    }    
    else 
    {
//     send.iRecipientArray = NULL;
    }
     
     
    
    err1 = messtype_func(aItem,messtype); 
    if(err1)
	{
	 return KErrGeneral;
	}    
	   
	if(messtype.CompareF(Knull))
    {   
	 send->SetMessageTypeL(messtype);                      // type of message
	}
	else
	{
//	 send->SetMessageTypeL = NULL;
	}	
    
    
    
    err1 = subject_func(aItem,subj); 
    if(err1)
	{
	 return KErrGeneral;
	}
	
	if(subj.CompareF(Knull))
	{
     send->SetSubjectL(subj);                               // subject
    }
    else
    {
//    send->SetSubjectL = NULL; 
    }
    
    
    
    err1 = body_func(aItem,body); 
    if(err1)
	{
	 return KErrGeneral;
	}

	if(body.CompareF(Knull))
	{ 
     send->SetBodyTextL(body);                              // body of message
    } 
    else
    {
//     send->SetBodyTextL = NULL;
    }
    
    
    
    err1 = flag_func(aItem,flag); 
    if(err1)
	 {
	  return KErrGeneral;
	 } 
	TInt att_cnt = flag;    
	if(flag!=0)                                             // any attachments
	 {	
       
       for(int i=0;i<flag;i++)
         {
	       err1 = attach_func(aItem,attachm); 
	       if(err1)
		   {
		   return KErrGeneral;
		   }
	       err1 = attachtype_func(aItem,attachfiletype); 
	       if(err1)
		   {
		   return KErrGeneral;
		   } 
          _LIT(Kbl,"NULL");
          CMsvAttachment::TMsvAttachmentType attachtype = CMsvAttachment::EMsvFile; 
          CMsvAttachment* element = CMsvAttachment::NewL(attachtype);
		  if(attachm != Kbl)
          {
		  element->SetAttachmentNameL(attachm);                        // attachment path
		  } 
		  if(attachfiletype != Kbl)
	      {
		  TBuf8<30> mimetype ;
	      mimetype.Copy(attachfiletype);
	      element->SetMimeTypeL(mimetype);                             // attachment mime type
	      } 
	      send->AddAttachmentL(element);
	     }
             
     }
    else
     {
//       send->AddAttachmentL = NULL;
     }  
     
     
     
    err1 = template_func(aItem,templateid); 
    if(err1)
	{
	 return KErrGeneral;
	}
    
    if(templateid == 1)
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
     send->SetTemplateId(message_id); 
     delete headerarr; 
     delete marray;
     delete mfilter;           
     CleanupStack::PopAndDestroy(mservice);   
    }
    else if(templateid == 2)
    {
     CMessagingService* mservice = (CMessagingService*)CMessagingService::NewL(); 	
 	 CleanupStack::PushL(mservice);
 	 CFilterParamInfo* mfilter = CFilterParamInfo::NewL();
 	 CMsvEntrySelection* marray = NULL ;
     TRAPD(err,mservice->GetIdListL(mfilter,0,NULL ,marray));
     TInt index = 0;
     _LIT(Kwron,"wr");
     for(;;)
     {
      CMessageHeader* headerarr = NULL;
      mservice->GetNextHeaderL(mfilter, marray, index, NULL, headerarr);  
	  if(headerarr)
	  {
	   TPtrC subn = headerarr->Subject();
	   TMsvId message_id;
	   headerarr->GetMessageId(message_id);
	   if((subn.FindF(Kwron))!=KErrNotFound)
	   {
        send->SetTemplateId(message_id); 
       }
       delete headerarr;
      }
      else
       break; 
     }       
     delete marray;
     delete mfilter;           
     CleanupStack::PopAndDestroy(mservice);   
    }
    else if(templateid == 3)
    {
     CMessagingService* mservice = (CMessagingService*)CMessagingService::NewL(); 	
 	 CleanupStack::PushL(mservice);
 	 CFilterParamInfo* mfilter = CFilterParamInfo::NewL();
 	 CMsvEntrySelection* marray = NULL ;
     TRAPD(err,mservice->GetIdListL(mfilter,0,NULL ,marray));
     TInt index = 0;
     for(;;)
     {
      CMessageHeader* headerarr = NULL;
      mservice->GetNextHeaderL(mfilter, marray, index, NULL, headerarr);  
	  _LIT(Kwron1,"nok");
	  _LIT(Kwron2,"hi");
	  TBool flg;
	  if(headerarr)
	  {
	   TPtrC subn = headerarr->Subject();
	   headerarr->GetAttachFlag(flg);
	   TMsvId message_id;
	   headerarr->GetMessageId(message_id);
	   if(((subn.FindF(Kwron1))==KErrNotFound)&&((subn.FindF(Kwron2))==KErrNotFound)&&(flg!=0))
	   {
        send->SetTemplateId(message_id); 
       }
       delete headerarr;
      }
      else
       break; 
     }       
     delete marray;
     delete mfilter;           
     CleanupStack::PopAndDestroy(mservice);   
    }
    else
    { 
     send->SetTemplateId(templateid);       // template id
    }

    
    err1 = editor_func(aItem,editorl); 
    if(err1)
	{
	 return KErrGeneral;
	}    
    send->SetLaunchEditor(editorl);        					   // launch editor or not  
           
   	
   	
   	Cheader_test* test = Cheader_test::NewL();
	
	test->set(send);
	test->attcnt = att_cnt;

	err1 = flag_func(aItem,flag1);            				   // +ve or -ve test case
    if(err1)
	 {
	  return KErrGeneral;
	 }   

    if(flag1 == 0)                    
    { 
      err1 = body_func(aItem,body);          				// get bodytxt from cfg
      if(err1)
	  {
	   return KErrGeneral;
	  }
      test->b.Set(body);
      
      for(int i=0;i<count1;i++)
      {
       err1 = rec_func(aItem,recarray);        				// get recarray from cfg
       if(err1)
	   {
	    return KErrGeneral;
	   }
       test->r[i].Set(recarray);
      }
      

    } 
    else
    {
      err1 = flag_func(aItem,flag2);          				 // get err code from cfg
        if(err1)
	    {
	     return KErrGeneral;
	    }   	
      if(flag2 == -3)
      {
       test->canflag = 1;
      }
      if(flag2 == -9)
      {
       test->exflag = 1;
      }
      test->pick2 = flag2;
    }        
	
 	
	test->Start();

    
    
    if( ( (templateid!=0) && (templateid!=1)&& (templateid!=3)&& (templateid!=2) ) || (memorycleanflag !=0) ) 
    {
     delete test;
    }
    TInt ret = iResult;
    return ret;


    

    }

// -----------------------------------------------------------------------------
// Casync_send_message::?member_function
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
/*
TInt Casync_send_message::?member_function(
   CItemParser& aItem )
   {

   ?code

   }
*/

// ========================== OTHER EXPORTED FUNCTIONS =========================
// None

//  End of File
