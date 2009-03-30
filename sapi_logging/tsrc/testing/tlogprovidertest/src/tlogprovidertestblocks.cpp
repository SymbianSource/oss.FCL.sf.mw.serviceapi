/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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




// [INCLUDE FILES] - do not remove
#include <e32svr.h>
#include <StifParser.h>
#include <Stiftestinterface.h>
#include "tlogprovidertest.h"
#include "teventdetails.h"
#include "tfilterdetails.h"
#include "serviceerrno.h"
//#include <logwrap.hrh>
// EXTERNAL DATA STRUCTURES
//extern  ?external_data;



  




// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctlogprovidertest::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void Ctlogprovidertest::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// Ctlogprovidertest::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt Ctlogprovidertest::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "addL", Ctlogprovidertest::addL ),
        ENTRY( "add2L", Ctlogprovidertest::add2L ),
        ENTRY( "get1L", Ctlogprovidertest::get1L ),
        ENTRY( "get2L", Ctlogprovidertest::get2L ),
        ENTRY( "delete1L", Ctlogprovidertest::delete1L ),
         ENTRY( "delete2L", Ctlogprovidertest::delete2L ),
          ENTRY( "deleteneg1L", Ctlogprovidertest::deleteneg1L ),
           ENTRY( "cancel1L", Ctlogprovidertest::cancel1L ),
             ENTRY( "cancel2L", Ctlogprovidertest::cancel2L ),
        ENTRY( "sapierrorsL", Ctlogprovidertest::sapierrorsL ),
         ENTRY( "wronginterfaceL", Ctlogprovidertest::wronginterfaceL ),
          ENTRY( "loadtwiceL", Ctlogprovidertest::loadtwiceL ),
           ENTRY( "wrongcommandL", Ctlogprovidertest::wrongcommandL ),


        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// Ctlogprovidertest::ExampleL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctlogprovidertest::addL( CStifItemParser& aItem )
    {
    TInt ret = 0;
    
     __UHEAP_MARK ;
     
     CEventDetails *eventDetails = CEventDetails :: NewL() ;


       TInt ParsedValue ;
      
       TBufC<100> String; 
       TPtrC sptr;
       sptr.Set(String);
      // TInt ParsedValue1 ;
       
       //1 seteventype
       
      aItem.GetNextInt( ParsedValue);
 	eventDetails->SetEventType(ParsedValue) ;	
	


	//2 setduration
 
    aItem.GetNextInt(ParsedValue);
     eventDetails->SetDurationType(ParsedValue) ;
      
        //3 setcontact
       aItem.GetNextInt(ParsedValue);
       eventDetails->SetContactType(ParsedValue) ;
     
        
        //4 setlinktype
       aItem.GetNextInt(ParsedValue);
       eventDetails->SetLinkType(ParsedValue) ;
       
       //5 settimer
          aItem.GetNextInt(ParsedValue);
           
         TTime time(ParsedValue);
         eventDetails->SetTimer(time) ;
      
        
        
      //6 setsubject
        aItem.GetNextString(sptr);
        eventDetails->SetSubjectType(sptr) ;  
     
        //7 setnumbertype
      aItem.GetNextString(sptr);
       eventDetails->SetNumberType(sptr) ;  
       
        //8 setremoteparty
       aItem.GetNextString(sptr);
       eventDetails->SetRemotePartyType(sptr) ;  
     
        //9 setdirectiontype
         aItem.GetNextInt(ParsedValue);
        eventDetails->SetDirectionType(ParsedValue) ;    	
     
    	
        //10 setdescriptiontype
         aItem.GetNextString(sptr);
         eventDetails->SetDescriptionType(sptr) ;  
        
        //11 setstatustype
         aItem.GetNextInt(ParsedValue);
         eventDetails->SetStatusType(ParsedValue) ;  
        
         
        
     
      
        
      
      TRAPD(error , addtest1L(eventDetails)) ;
       delete eventDetails;
       
      
       

   __UHEAP_MARKEND;

    return KErrNone;

    }
    
    
    
    TInt Ctlogprovidertest::add2L( CStifItemParser& aItem )
    {
    
    __UHEAP_MARK;
    
    TInt ret = 0;
    

     
     CEventDetails *eventDetails = CEventDetails :: NewL() ;


       TInt ParsedValue ;
      
       TBufC<100> String; 
       TPtrC sptr;
       sptr.Set(String);
       TInt ParsedValue1 ;
       
       
       
      if(aItem.GetNextInt( ParsedValue) != KErrNone )
        {
      
          User :: Leave(KErrArgument) ;
        }
 


     
	if((ParsedValue >= KCallEvent ) && (ParsedValue <=KLogLbsAssistanceDataEvent))
		{
		eventDetails->SetEventType(ParsedValue) ;	
		}

	else 
		{
	 ;
 		}


        

     
       if(aItem.GetNextInt(ParsedValue) != KErrNone)
        {
          
         User :: Leave(KErrArgument)  ;
        }
     
       if(ParsedValue > 0 )
        {
         eventDetails->SetDurationType(ParsedValue) ;
        }
        
        
        if(aItem.GetNextInt(ParsedValue) != KErrNone)
        {
    
         User :: Leave(KErrArgument)  ;
        }
     
       if(ParsedValue > 0 )
        {
         eventDetails->SetContactType(ParsedValue) ;
        }
        
        
        
       if(aItem.GetNextInt(ParsedValue) != KErrNone)
        {
       
         User :: Leave(KErrArgument)  ;
        }
     
       if(ParsedValue > 0 )
        {
         eventDetails->SetLinkType(ParsedValue) ;
        }
        
        if(aItem.GetNextInt(ParsedValue) != KErrNone)
        {
      
         User :: Leave(KErrArgument)  ;
        }
     
       if(ParsedValue> 0 )
        {
        
         TTime time(ParsedValue);
         eventDetails->SetTimer(time) ;
        }
        
        _LIT(KNull,"NULL");
        
        if(aItem.GetNextString(sptr) !=KErrNone)
        {
       
          User :: Leave(KErrArgument) ;  
        }
        
        if((sptr.Compare(KNull)))
        {
          eventDetails->SetSubjectType(sptr) ;  
        }
        
        if(aItem.GetNextString(sptr) !=KErrNone)
        {
        
          User :: Leave(KErrArgument) ;  
        }
        
        if((sptr.Compare(KNull)))
        {
          eventDetails->SetNumberType(sptr) ;  
        }
        
        if(aItem.GetNextString(sptr) !=KErrNone)
        {
         
          User :: Leave(KErrArgument) ;  
        }
        
        if((sptr.Compare(KNull)))
        {
          eventDetails->SetRemotePartyType(sptr) ;  
        }
        
        if(aItem.GetNextInt(ParsedValue) != KErrNone)
        {
        
          User :: Leave(KErrArgument) ;  
        }
        
        if(ParsedValue >= 0)
    	{
		eventDetails->SetDirectionType(ParsedValue) ;    	
    	}
    	
        
        
        if(aItem.GetNextString(sptr) !=KErrNone)
        {
          
          
          User :: Leave(KErrArgument) ;  
        }
        
        if((sptr.Compare(KNull)))
        {
          eventDetails->SetDescriptionType(sptr) ;  
        }
        
        if(aItem.GetNextInt(ParsedValue) !=KErrNone)
        {
         
          User :: Leave(KErrArgument) ;  
        }
        
        if(ParsedValue >= 0)
        {
          eventDetails->SetStatusType(ParsedValue) ;  
        }
        
        
        
        if(aItem.GetNextInt(ParsedValue1) != KErrNone)
        {
       
         User :: Leave(KErrArgument)  ;
        }
        
        
        
        
        
        
        
     
     if(aItem.GetNextInt(ParsedValue) != KErrNone )
        {
        
         ret = KErrNone ;
        }
     else
        {
            ret = ParsedValue ;
        }
        
        
        
      
        
      
      TRAPD(error , addtest2L(eventDetails)) ;
       delete eventDetails;
       
      
       
  
    
  
   __UHEAP_MARKEND;
   

    return KErrNone;

    

 
   

  //  return ret;

    }
    
    
    
    
    
    
     TInt Ctlogprovidertest::get1L( CStifItemParser& aItem )
    {
     TInt ret = 0 ;
      
    
     
     __UHEAP_MARK ;
     
     CFilterDetails *filterDetails = CFilterDetails::NewL() ;
        
       TInt ParsedValue ;
      
       TBufC<100> String; 
       TPtrC sptr;
       sptr.Set(String);
       TInt ParsedValue1 ;
       
       
       _LIT(KNull,"NULL");
        
        
        if(aItem.GetNextString(sptr) !=KErrNone)
        {
          _LIT(KLog , "id not found") ;
	 	 iLog->Log(KLog) ;
          User :: Leave(KErrArgument) ;  
        }
        
        if((sptr.Compare(KNull)))
        {
          filterDetails->SetEventId(sptr) ;  
        }
       
       
       
       if(aItem.GetNextInt( ParsedValue) != KErrNone )
        {
        
          User :: Leave(KErrArgument) ;
        }
         
       
	if((ParsedValue >= KCallEvent ) && (ParsedValue <=KLogLbsAssistanceDataEvent))
		{
		filterDetails->SetEventType(ParsedValue) ;	
		}

	else 
		{
	 ;
 		}

        
       if(aItem.GetNextInt(ParsedValue) != KErrNone)
        {
       
         User :: Leave(KErrArgument)  ;
        }
     
       if(ParsedValue > 0 )
        {
         filterDetails->SetContactType(ParsedValue) ;
        }
        
        if(aItem.GetNextInt(ParsedValue) != KErrNone)
        {
         
         User :: Leave(KErrArgument)  ;
        }
     
       if(ParsedValue> 0 )
        {
        
         TTime time(ParsedValue);
         filterDetails->SetTimer(time) ;
        }
        
       
        
        
        if(aItem.GetNextString(sptr) !=KErrNone)
        {
         
          User :: Leave(KErrArgument) ;  
        }
        
        if((sptr.Compare(KNull)))
        {
          filterDetails->SetNumberType(sptr) ;  
        }
        
        if(aItem.GetNextString(sptr) !=KErrNone)
        {
         
          User :: Leave(KErrArgument) ;  
        }
        
        if((sptr.Compare(KNull)))
        {
          filterDetails->SetRemotePartyType(sptr) ;  
        }
        
        if(aItem.GetNextInt(ParsedValue) != KErrNone)
        {
       
          User :: Leave(KErrArgument) ;  
        }
        
        if(ParsedValue >= 0 )
        {
          filterDetails->SetDirectionType(ParsedValue) ;  
        }
        
        if(aItem.GetNextInt(ParsedValue) !=KErrNone)
        {
         
          User :: Leave(KErrArgument) ;  
        }
        
        if(ParsedValue >= 0 )
        {
          filterDetails->SetStatusType(ParsedValue) ;  
        }
        
    
        
        if(aItem.GetNextInt(ParsedValue) != KErrNone)
        {
 
         User :: Leave(KErrArgument)  ;
        }
        
   
     
       if(ParsedValue == 0 || ParsedValue < -1 )
        {
         ;
        }
        else
        {
          filterDetails->SetRecentList(ParsedValue) ;  
        }
            
        
        
         
      if(aItem.GetNextInt( ParsedValue) != KErrNone )
        {
        
          User :: Leave(KErrArgument) ;
        }
        
        
       if(ParsedValue == 0 )
        {
         filterDetails->SetAllEvent(FALSE) ;
        }
        else if(ParsedValue == 1)
        
        {
            filterDetails->SetAllEvent(TRUE); 
        }
         
        
         
       
       if(aItem.GetNextInt(ParsedValue1) != KErrNone)
        {
      
         User :: Leave(KErrArgument)  ;
        }
        
        
      if(aItem.GetNextInt(ParsedValue) != KErrNone )
        {
       
         ret = KErrNone ;
        }
     else
        {
            ret = ParsedValue ;
        }
        
       
       TRAPD(error , getlist1L(filterDetails)) ; 
       delete filterDetails;
       
       __UHEAP_MARKEND;
      
      if(error == ret)
        {
         return KErrNone; 
        }
      return error; 
       
    
}
      
        
 
 
 
  TInt Ctlogprovidertest::get2L( CStifItemParser& aItem )
    {
     TInt ret = 0 ;
      
  
     
     __UHEAP_MARK ;
     
     CFilterDetails *filterDetails = CFilterDetails::NewL() ;
        
       TInt ParsedValue ;
      
       TBufC<100> String; 
       TPtrC sptr;
       sptr.Set(String);
       TInt ParsedValue1 ;
       
       
      _LIT(KNull,"NULL");
        
       if(aItem.GetNextString(sptr) !=KErrNone)
        {
          _LIT(KLog , "id not found") ;
	 	 iLog->Log(KLog) ;
          User :: Leave(KErrArgument) ;  
        }
        
        if((sptr.Compare(KNull)))
        {
          filterDetails->SetEventId(sptr) ;  
       
        }
       
       
       if(aItem.GetNextInt( ParsedValue) != KErrNone )
        {
        
          User :: Leave(KErrArgument) ;
        }
         
         
           
	if((ParsedValue >= KCallEvent ) && (ParsedValue <=KLogLbsAssistanceDataEvent))
		{
		filterDetails->SetEventType(ParsedValue) ;	
		}

	else 
		{
	 ;
 		}

     
        
        
       if(aItem.GetNextInt(ParsedValue) != KErrNone)
        {
        _LIT(KLog , "contact id not found") ;
	 	 iLog->Log(KLog) ;
         User :: Leave(KErrArgument)  ;
        }
     
       if(ParsedValue > 0 )
        {
         filterDetails->SetContactType(ParsedValue) ;
        }
        
        if(aItem.GetNextInt(ParsedValue) != KErrNone)
        {
         
         User :: Leave(KErrArgument)  ;
        }
     
       if(ParsedValue> 0 )
        {
        
         TTime time(ParsedValue);
         filterDetails->SetTimer(time) ;
        }
        
       
        
        
        if(aItem.GetNextString(sptr) !=KErrNone)
        {
         
          User :: Leave(KErrArgument) ;  
        }
        
        if((sptr.Compare(KNull)))
        {
          filterDetails->SetNumberType(sptr) ;  
        }
        
        if(aItem.GetNextString(sptr) !=KErrNone)
        {
         
          User :: Leave(KErrArgument) ;  
        }
        
        if((sptr.Compare(KNull)))
        {
          filterDetails->SetRemotePartyType(sptr) ;  
        }
        
        if(aItem.GetNextInt(ParsedValue) != KErrNone)
        {
       
          User :: Leave(KErrArgument) ;  
        }
        
        if(ParsedValue >= 0 )
        {
          filterDetails->SetDirectionType(ParsedValue) ;  
        }
        
        if(aItem.GetNextInt(ParsedValue) !=KErrNone)
        {
         
          User :: Leave(KErrArgument) ;  
        }
        
        if(ParsedValue >= 0 )
        {
          filterDetails->SetStatusType(ParsedValue) ;  
        }
        
    
        
        if(aItem.GetNextInt(ParsedValue) != KErrNone)
        {
 
         User :: Leave(KErrArgument)  ;
        }
        
   
     
       if(ParsedValue == 0 || ParsedValue < -1 )
        {
         ;
        }
        else
        {
          filterDetails->SetRecentList(ParsedValue) ;  
        }
            
        
        
         
      if(aItem.GetNextInt( ParsedValue) != KErrNone )
        {
        
          User :: Leave(KErrArgument) ;
        }
        
        
       if(ParsedValue == 0 )
        {
         filterDetails->SetAllEvent(FALSE) ;
        }
        else if(ParsedValue == 1)
        
        {
            filterDetails->SetAllEvent(TRUE); 
        }
         
        
         
       
       if(aItem.GetNextInt(ParsedValue1) != KErrNone)
        {
      
         User :: Leave(KErrArgument)  ;
        }
        
        
      if(aItem.GetNextInt(ParsedValue) != KErrNone )
        {
       
         ret = KErrNone ;
        }
     else
        {
            ret = ParsedValue ;
        }
        
       
       TRAPD(error , getlist2L(filterDetails)) ; 
       delete filterDetails;
       
       __UHEAP_MARKEND;
      
      
      return ret; 
       
    
}



 TInt Ctlogprovidertest::delete1L( CStifItemParser& aItem )
    {
  
    TInt ret = 0;
    
     __UHEAP_MARK ;
     
     CEventDetails *eventDetails = CEventDetails :: NewL() ;


       TInt ParsedValue ;
      
       TBufC<100> String; 
       TPtrC sptr;
       sptr.Set(String);
     //  TInt ParsedValue1 ;
       
       //1 seteventype
       
      aItem.GetNextInt( ParsedValue);
 	eventDetails->SetEventType(ParsedValue) ;	
	


	//2 setduration
 
    aItem.GetNextInt(ParsedValue);
     eventDetails->SetDurationType(ParsedValue) ;
      
        //3 setcontact
       aItem.GetNextInt(ParsedValue);
       eventDetails->SetContactType(ParsedValue) ;
     
        
        //4 setlinktype
       aItem.GetNextInt(ParsedValue);
       eventDetails->SetLinkType(ParsedValue) ;
       
       //5 settimer
          aItem.GetNextInt(ParsedValue);
           
         TTime time(ParsedValue);
         eventDetails->SetTimer(time) ;
      
        
        
      //6 setsubject
        aItem.GetNextString(sptr);
        eventDetails->SetSubjectType(sptr) ;  
     
        //7 setnumbertype
      aItem.GetNextString(sptr);
       eventDetails->SetNumberType(sptr) ;  
       
        //8 setremoteparty
       aItem.GetNextString(sptr);
       eventDetails->SetRemotePartyType(sptr) ;  
     
        //9 setdirectiontype
         aItem.GetNextInt(ParsedValue);
        eventDetails->SetDirectionType(ParsedValue) ;    	
     
    	
        //10 setdescriptiontype
         aItem.GetNextString(sptr);
         eventDetails->SetDescriptionType(sptr) ;  
        
        //11 setstatustype
         aItem.GetNextInt(ParsedValue);
         eventDetails->SetStatusType(ParsedValue) ;  
        
          //12 
          aItem.GetNextInt(ParsedValue);
         
     
        if(ParsedValue == 0)
        {
        	
         
       
       TRAPD(error , deletetest1L(eventDetails)) ; 
        }
        else
        {
         TRAPD(error , deletetest1_0L(eventDetails)) ; 	
        }
       delete eventDetails;
       
       __UHEAP_MARKEND;
      
      
      return ret; 
       
    
}














 TInt Ctlogprovidertest::delete2L( CStifItemParser& aItem )
    {
  
    TInt ret = 0;
    
     __UHEAP_MARK ;
     
     CEventDetails *eventDetails = CEventDetails :: NewL() ;


       TInt ParsedValue ;
      
       TBufC<100> String; 
       TPtrC sptr;
       sptr.Set(String);
     //  TInt ParsedValue1 ;
       
       //1 seteventype
       
      aItem.GetNextInt( ParsedValue);
 	eventDetails->SetEventType(ParsedValue) ;	
	


	//2 setduration
 
    aItem.GetNextInt(ParsedValue);
     eventDetails->SetDurationType(ParsedValue) ;
      
        //3 setcontact
       aItem.GetNextInt(ParsedValue);
       eventDetails->SetContactType(ParsedValue) ;
     
        
        //4 setlinktype
       aItem.GetNextInt(ParsedValue);
       eventDetails->SetLinkType(ParsedValue) ;
       
       //5 settimer
          aItem.GetNextInt(ParsedValue);
           
         TTime time(ParsedValue);
         eventDetails->SetTimer(time) ;
      
        
        
      //6 setsubject
        aItem.GetNextString(sptr);
        eventDetails->SetSubjectType(sptr) ;  
     
        //7 setnumbertype
      aItem.GetNextString(sptr);
       eventDetails->SetNumberType(sptr) ;  
       
        //8 setremoteparty
       aItem.GetNextString(sptr);
       eventDetails->SetRemotePartyType(sptr) ;  
     
        //9 setdirectiontype
         aItem.GetNextInt(ParsedValue);
        eventDetails->SetDirectionType(ParsedValue) ;    	
     
    	
        //10 setdescriptiontype
         aItem.GetNextString(sptr);
         eventDetails->SetDescriptionType(sptr) ;  
        
        //11 setstatustype
         aItem.GetNextInt(ParsedValue);
         eventDetails->SetStatusType(ParsedValue) ;  
        
          
         
     
        
       
       TRAPD(error , deletetest2L(eventDetails)) ; 
       delete eventDetails;
       
       __UHEAP_MARKEND;
      
      
      return ret; 
       
    
}





TInt Ctlogprovidertest::deleteneg1L( CStifItemParser& aItem )
    {
    
    

 TInt ParsedValue ;
 
CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();
     // Input and output parameter list
    CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    
    CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());
    
    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KDsInterfaceName , KLoggingContents) ;
    
  
    
    crit->SetServiceClass(TUid::Uid(KLiwClassBase));
    
    RCriteriaArray a;
    
	
	a.AppendL(crit);

   
    
	
	ServiceHandler->AttachL(a) ;
	
	
	ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist);
	 
 	

	
    TInt pos = 0;
	
 
	const TLiwGenericParam *genericparm = outputlist->FindFirst(pos  , KDsInterfaceName);
	
	if(!genericparm)
	{

	 
	 User :: Leave(KErrArgument) ;
	}
	
   MLiwInterface* LogInterface = (genericparm->Value()).AsInterface();
    
    
   
    TBuf16 <10> Contents(KContentType) ;
     
 
  aItem.GetNextInt(ParsedValue);
 
 
  TInt itemid =  ParsedValue;
    
    //TInt itemid = 12;
 // TBuf<8> des;
  //des.Num(itemid);
    
     inputlist->Reset() ; outputlist->Reset() ;
  
   
   //Insert the contenttype to inputlist
   CLiwDefaultMap *Idmap = CLiwDefaultMap :: NewL() ;
   Idmap->InsertL(KLogId ,TLiwVariant(itemid)) ;
   
    TBufC16<10> contentType(KContentType) ;
   //Insert the contenttype to inputlist
   inputlist->AppendL(TLiwGenericParam(KContentTypeKey , TLiwVariant(contentType))) ;
 
   
 // inputlist->AppendL(TLiwGenericParam(KLogId , TLiwVariant((TInt32)itemid))) ;
    inputlist->AppendL(TLiwGenericParam(KData , TLiwVariant(Idmap))) ; 
    Idmap->DecRef();
 // CmdBuf = KCmdDelete ;
  
  TBufC8<20>CmdBuf(KCmdDelete) ;
  LogInterface->ExecuteCmdL(CmdBuf , *inputlist , *outputlist) ;
  
  pos = 0 ;
  const TLiwGenericParam *Errprm = outputlist->FindFirst(pos , KErrCode ) ;
  
  if(!Errprm)
  	{
   
  	 User :: Leave(KErrArgument) ;
  	}
  	
  TInt retval1  = Errprm->Value().AsTInt32() ;
  
  if(retval1 != SErrBadArgumentType )
  	{
   
  	 User :: Leave(KErrArgument) ;
  	}
    
    
    
   
      LogInterface->Close() ;
     delete ServiceHandler;
    // delete crit;
   
   	 a.ResetAndDestroy();
   	 a.Close();
    return SErrNone;
   
    }









TInt Ctlogprovidertest::cancel1L( CStifItemParser& aItem )
    {
    TInt ret = 0;
    
     __UHEAP_MARK ;
     
     CEventDetails *eventDetails = CEventDetails :: NewL() ;


       TInt ParsedValue ;
      
       TBufC<100> String; 
       TPtrC sptr;
       sptr.Set(String);
      // TInt ParsedValue1 ;
       
       //1 seteventype
       
      aItem.GetNextInt( ParsedValue);
 	eventDetails->SetEventType(ParsedValue) ;	
	


	//2 setduration
 
    aItem.GetNextInt(ParsedValue);
     eventDetails->SetDurationType(ParsedValue) ;
      
        //3 setcontact
       aItem.GetNextInt(ParsedValue);
       eventDetails->SetContactType(ParsedValue) ;
     
        
        //4 setlinktype
       aItem.GetNextInt(ParsedValue);
       eventDetails->SetLinkType(ParsedValue) ;
       
       //5 settimer
          aItem.GetNextInt(ParsedValue);
           
         TTime time(ParsedValue);
         eventDetails->SetTimer(time) ;
      
        
        
      //6 setsubject
        aItem.GetNextString(sptr);
        eventDetails->SetSubjectType(sptr) ;  
     
        //7 setnumbertype
      aItem.GetNextString(sptr);
       eventDetails->SetNumberType(sptr) ;  
       
        //8 setremoteparty
       aItem.GetNextString(sptr);
       eventDetails->SetRemotePartyType(sptr) ;  
     
        //9 setdirectiontype
         aItem.GetNextInt(ParsedValue);
        eventDetails->SetDirectionType(ParsedValue) ;    	
     
    	
        //10 setdescriptiontype
         aItem.GetNextString(sptr);
         eventDetails->SetDescriptionType(sptr) ;  
        
        //11 setstatustype
         aItem.GetNextInt(ParsedValue);
         eventDetails->SetStatusType(ParsedValue) ;  
        
         
        
     
      
        
      
      TRAPD(error , cancel1_0L(eventDetails)) ;
       delete eventDetails;
       
      
       

   __UHEAP_MARKEND;

    return KErrNone;

    }







TInt Ctlogprovidertest::cancel2L( CStifItemParser& aItem )
    {
    TInt ret = 0;
    
     __UHEAP_MARK ;
     
     CEventDetails *eventDetails = CEventDetails :: NewL() ;


       TInt ParsedValue ;
      
       TBufC<100> String; 
       TPtrC sptr;
       sptr.Set(String);
      // TInt ParsedValue1 ;
       
       //1 seteventype
       
      aItem.GetNextInt( ParsedValue);
 	eventDetails->SetEventType(ParsedValue) ;	
	


	//2 setduration
 
    aItem.GetNextInt(ParsedValue);
     eventDetails->SetDurationType(ParsedValue) ;
      
        //3 setcontact
       aItem.GetNextInt(ParsedValue);
       eventDetails->SetContactType(ParsedValue) ;
     
        
        //4 setlinktype
       aItem.GetNextInt(ParsedValue);
       eventDetails->SetLinkType(ParsedValue) ;
       
       //5 settimer
          aItem.GetNextInt(ParsedValue);
           
         TTime time(ParsedValue);
         eventDetails->SetTimer(time) ;
      
        
        
      //6 setsubject
        aItem.GetNextString(sptr);
        eventDetails->SetSubjectType(sptr) ;  
     
        //7 setnumbertype
      aItem.GetNextString(sptr);
       eventDetails->SetNumberType(sptr) ;  
       
        //8 setremoteparty
       aItem.GetNextString(sptr);
       eventDetails->SetRemotePartyType(sptr) ;  
     
        //9 setdirectiontype
         aItem.GetNextInt(ParsedValue);
        eventDetails->SetDirectionType(ParsedValue) ;    	
     
    	
        //10 setdescriptiontype
         aItem.GetNextString(sptr);
         eventDetails->SetDescriptionType(sptr) ;  
        
        //11 setstatustype
         aItem.GetNextInt(ParsedValue);
         eventDetails->SetStatusType(ParsedValue) ;  
        
         
        
     
      
        
      
      TRAPD(error , cancel1_1L(eventDetails)) ;
       delete eventDetails;
       
      
       __UHEAP_MARKEND;

   

    return KErrNone;

    }










 TInt Ctlogprovidertest::sapierrorsL( CStifItemParser& aItem )
 {
 
 TInt ret = 0;
 __UHEAP_MARK;
 
  ret = sapierrors();
 
 __UHEAP_MARKEND;
 	
 return ret;
 }
           
      
   
   
 TInt Ctlogprovidertest::wronginterfaceL( CStifItemParser& aItem )
 {
 
 
 //__UHEAP_MARK;
 TInt ret = 0;
    
     __UHEAP_MARK ;
     
     CEventDetails *eventDetails = CEventDetails :: NewL() ;


    
       
       //1 seteventype
       
     // aItem.GetNextInt( ParsedValue);
 	eventDetails->SetEventType(0) ;	
	


 
        
  TRAP(ret, wronginterface1(eventDetails));
 
 delete eventDetails;
 __UHEAP_MARKEND;
 if(ret == KErrArgument)	
 return KErrNone;
 }   
       
      
   
   
    TInt Ctlogprovidertest::loadtwiceL( CStifItemParser& aItem )
 {
 
 
 __UHEAP_MARK;
 TInt ret = 0;
    
   
     
     CEventDetails *eventDetails = CEventDetails :: NewL() ;


      
       
       //1 seteventype
       
     // aItem.GetNextInt( ParsedValue);
 	eventDetails->SetEventType(0) ;	
	


     TRAP(ret , loadtwice(eventDetails)) ;
        
 
 
 delete eventDetails;
 __UHEAP_MARKEND;
return ret;
 }     
  
 
 
     TInt Ctlogprovidertest::wrongcommandL( CStifItemParser& aItem )
 {
 
 
 __UHEAP_MARK;
 TInt ret = 0;
    
    // __UHEAP_MARK ;
     
     CEventDetails *eventDetails = CEventDetails :: NewL() ;


  
       
       //1 seteventype
       
     // aItem.GetNextInt( ParsedValue);
 	eventDetails->SetEventType(0) ;	
	


     TRAP(ret , wrongcommand(eventDetails)) ;
        
 
 
 delete eventDetails;
 __UHEAP_MARKEND;
return ret;
 }

