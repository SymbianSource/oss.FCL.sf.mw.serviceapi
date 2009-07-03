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




// INCLUDE FILES
#include <e32svr.h>
#include <StifParser.h>
#include <Stiftestinterface.h>
#include "tprovidertest.h"
#include "teventdetails.h"
#include "tfilterdetails.h"



// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctprovidertest::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void Ctprovidertest::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// Ctprovidertest::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt Ctprovidertest::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "Example", Ctprovidertest::ExampleL ),
        ENTRY( "AddTest1", Ctprovidertest :: AddTest1L ),
        ENTRY( "AddTest2", Ctprovidertest :: AddTest2L ),
        ENTRY( "AddGeneric", Ctprovidertest :: AddGenericL ),
        ENTRY( "DeleteTest" , Ctprovidertest :: DeletetestL),
        ENTRY( "GetListGeneric",Ctprovidertest :: GetListGenericL ),
        ENTRY("AddGenericPos" , Ctprovidertest :: AddGenericPosL),
        ENTRY("DeleteTestPos" , Ctprovidertest :: DeleteGenericPosL),
        ENTRY( "GetListGenericPos",Ctprovidertest :: GetListGenericPosL ),

        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// Ctprovidertest::ExampleL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctprovidertest::ExampleL( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( Ktprovidertest, "tprovidertest" );
    _LIT( KExample, "In Example" );
    TestModuleIf().Printf( 0, Ktprovidertest, KExample );
    // Print to log file
    iLog->Log( KExample );

    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, Ktprovidertest, 
                                KParam, i, &string );
        i++;
        }

    return KErrNone;

    }


// -----------------------------------------------------------------------------
// Ctprovidertest::ExampleL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctprovidertest::AddTest1L( CStifItemParser& /*aItem*/ )
    {
    
      
     _LIT(KTProvidertest , "tprovidertest") ;
     iLog->Log(KTProvidertest) ;
     
     __UHEAP_MARK ;
     
     TRAPD(error , taddtest1L() ) ;
     
    __UHEAP_MARKEND ;
    return KErrNone;

    }
    
TInt Ctprovidertest::AddTest2L( CStifItemParser& /*aItem*/ )
    {
    
      
     _LIT(KTProvidertest , "tprovidertest") ;
     iLog->Log(KTProvidertest) ;
     
     __UHEAP_MARK ;
     
     TRAPD(error , taddtest2L() ) ;
     
    __UHEAP_MARKEND ;
    return KErrNone;

    }    
    
    
 // -----------------------------------------------------------------------------
// Ctprovidertest::AddGenericL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctprovidertest::AddGenericL( CStifItemParser& aItem )
    {
    
     TInt ret = 0 ;
      
     _LIT(KTProvidertest , "tprovidertest") ;
     iLog->Log(KTProvidertest) ;
     
     __UHEAP_MARK ;
     
     CEventDetails *eventDetails = CEventDetails :: NewL() ;


       TInt ParsedValue ;
      
       TBufC<100> String; 
       TPtrC sptr;
       sptr.Set(String);
       TInt ParsedValue1 ;
       
       
       
      if(aItem.GetNextInt( ParsedValue) != KErrNone )
        {
          _LIT(KLog , "Eventid  not found") ;
	 	  iLog->Log(KLog) ;
          User :: Leave(KErrArgument) ;
        }
 


     
	if((ParsedValue >= KCallEvent ) && (ParsedValue <=KLogLbsAssistanceDataEvent))
		{
		eventDetails->SetEventType(ParsedValue) ;	
		}

	else 
		{
		_LIT(KLog , "Wrong input EventID") ;
		iLog->Log(KLog) ;
	//	User :: Leave(KErrGeneral) ;	
		}


        

     
       if(aItem.GetNextInt(ParsedValue) != KErrNone)
        {
         _LIT(KLog , "duration not found") ;
	 	 iLog->Log(KLog) ;
         User :: Leave(KErrArgument)  ;
        }
     
       if(ParsedValue > 0 )
        {
         eventDetails->SetDurationType(ParsedValue) ;
        }
        
        
        if(aItem.GetNextInt(ParsedValue) != KErrNone)
        {
        _LIT(KLog , "contact id not found") ;
	 	 iLog->Log(KLog) ;
         User :: Leave(KErrArgument)  ;
        }
     
       if(ParsedValue > 0 )
        {
         eventDetails->SetContactType(ParsedValue) ;
        }
        
        
        
       if(aItem.GetNextInt(ParsedValue) != KErrNone)
        {
         _LIT(KLog , "link value not found") ;
	 	 iLog->Log(KLog) ;
         User :: Leave(KErrArgument)  ;
        }
     
       if(ParsedValue > 0 )
        {
         eventDetails->SetLinkType(ParsedValue) ;
        }
        
        if(aItem.GetNextInt(ParsedValue) != KErrNone)
        {
         _LIT(KLog , "time value not found") ;
	 	 iLog->Log(KLog) ;
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
          _LIT(KLog , "subject not found") ;
	 	 iLog->Log(KLog) ;
          User :: Leave(KErrArgument) ;  
        }
        
        if((sptr.Compare(KNull)))
        {
          eventDetails->SetSubjectType(sptr) ;  
        }
        
        if(aItem.GetNextString(sptr) !=KErrNone)
        {
          _LIT(KLog , "phone number not found") ;
	 	 iLog->Log(KLog) ;
          User :: Leave(KErrArgument) ;  
        }
        
        if((sptr.Compare(KNull)))
        {
          eventDetails->SetNumberType(sptr) ;  
        }
        
        if(aItem.GetNextString(sptr) !=KErrNone)
        {
          _LIT(KLog , "remote party number not found") ;
	 	 iLog->Log(KLog) ;
          User :: Leave(KErrArgument) ;  
        }
        
        if((sptr.Compare(KNull)))
        {
          eventDetails->SetRemotePartyType(sptr) ;  
        }
        
        if(aItem.GetNextInt(ParsedValue) != KErrNone)
        {
          _LIT(KLog , "direction not found") ;
	 	  iLog->Log(KLog) ;
          User :: Leave(KErrArgument) ;  
        }
        
        if(ParsedValue >= 0)
    	{
		eventDetails->SetDirectionType(ParsedValue) ;    	
    	}
    	
        
        
        if(aItem.GetNextString(sptr) !=KErrNone)
        {
          _LIT(KLog , "description not found") ;
	 	 iLog->Log(KLog) ;
          
          User :: Leave(KErrArgument) ;  
        }
        
        if((sptr.Compare(KNull)))
        {
          eventDetails->SetDescriptionType(sptr) ;  
        }
        
        if(aItem.GetNextInt(ParsedValue) !=KErrNone)
        {
          _LIT(KLog , "status value not found") ;
	 	  iLog->Log(KLog) ;
          User :: Leave(KErrArgument) ;  
        }
        
        if(ParsedValue >= 0)
        {
          eventDetails->SetStatusType(ParsedValue) ;  
        }
        
        
        
        if(aItem.GetNextInt(ParsedValue1) != KErrNone)
        {
         _LIT(KLog , "Sync/Async version  not found") ;
	 	  iLog->Log(KLog) ;
         User :: Leave(KErrArgument)  ;
        }
        
        
       if(aItem.GetNextString(sptr) !=KErrNone)
        {
          _LIT(KLog , "data not found") ;
	 	 iLog->Log(KLog) ;
          
          User :: Leave(KErrArgument) ;  
        }
        if((sptr.Compare(KNull)))
        {
          eventDetails->SetDataType(sptr) ;  
        }  
          
        
        
        
        
     
     if(aItem.GetNextInt(ParsedValue) != KErrNone )
        {
         _LIT(KLog , "Expected value not found") ;
	 	  iLog->Log(KLog) ;
         ret = KErrNone ;
        }
     else
        {
            ret = ParsedValue ;
        }
        
        
        
      
        
      
      TRAPD(error , taddgenericL(eventDetails,ParsedValue1)) ;
       delete eventDetails;
       
      
       
     __UHEAP_MARKEND;
      
      if(error == ret)
          {
         return KErrNone; 
          }
      return error ;

    }   
//-------------------------------------------------------------------------
// Ctprovidertest :: Deletetest
// Tests the delete use case ofthe provider
//-------------------------------------------------------------------------    
    
TInt Ctprovidertest::DeletetestL( CStifItemParser& aItem )   
	{
	 TInt parseval =  0 ;
	 TInt async = 0 ;
	 TInt allEvents = 0 ;
	 
__UHEAP_MARK ;	 

	 if(aItem.GetNextInt(async) != KErrNone)
	 	{	
	 	 _LIT(KLog , "Sync/Async version  not found") ;
	 	 iLog->Log(KLog) ;
	 	 User :: Leave(KErrNotFound) ;
	 	}
	 	
	TInt ret = 0 ;
	
	if(aItem.GetNextInt(allEvents ))
		{
		 _LIT8(KLog , "All events field not found") ;
		 iLog->Log(KLog) ;
		}
	 //Get the expected return value
	 
	 if(aItem.GetNextInt(parseval) != KErrNone)
	 	{
	 	 _LIT(KLog , "Expected output not found") ;
	 	 iLog->Log(KLog) ;
	 	 User :: Leave(KErrNotFound)  ;
	 	}
	 	
	TInt retval = 0 ;	 	
	
	if(allEvents)
		{
		_LIT(KLog , "Delete all events called \n") ;
		iLog->Log(KLog) ;
		TRAPD(err , tdeleteAllEventsL(async)) ;
		
		if(err != parseval)
			{
			 _LIT(KLog , "Expected and the return values doesn't match") ;
			 iLog->Log(KLog) ;
			}
		}
	 	
	 if(async)
	 	{
	 	 _LIT(KLog , "Functionality test of delete async api") ;
	 	 iLog->Log(KLog) ;
	 	 
	    TRAPD(aerr , tdeleteTestasyncL(parseval)) ;
	    
	    if(aerr != parseval)
	    	{
	    	 _LIT(KLog , "Expected and the return value dont match") ;
	    	 iLog->Log(KLog) ;
	    	 retval = KErrArgument ; 
	    	}
	    else 
	    	{
	    	 retval = KErrNone ;	
	    	}	
	    	
	 	}
	 else 
	 {
		TRAPD(error , tdeleteTestL(parseval))  ; 	
		
		if(error != parseval)
			{
			 _LIT(KLog , "Expected and the return value dont match") ;
			 iLog->Log(KLog) ;
			 retval = KErrArgument ;
			}
		else
			{
				retval = KErrNone ;
			}	
	 }
	
	
__UHEAP_MARKEND	;
  
 
    return KErrNone ;	 	
	}
	
 // -----------------------------------------------------------------------------
// Ctprovidertest::GetListGenericL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctprovidertest::GetListGenericL( CStifItemParser& aItem )

{
     TInt ret = 0 ;
      
     _LIT(KTProvidertest , "tprovidertest") ;
     iLog->Log(KTProvidertest) ;
     
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
       
       
      /* if(aItem.GetNextInt(ParsedValue) != KErrNone)
        {
        _LIT(KLog , "Event id not found") ;
	 	 iLog->Log(KLog) ;
         User :: Leave(KErrArgument)  ;
        }
     
       if(ParsedValue > 0 )
        {
         filterDetails->SetEventId(ParsedValue) ;
        }*/
       
       
       
       if(aItem.GetNextInt( ParsedValue) != KErrNone )
        {
          _LIT(KLog , "Eventtype  not found") ;
	 	 iLog->Log(KLog) ;
          User :: Leave(KErrArgument) ;
        }
         
     if((ParsedValue >= KCallEvent ) && (ParsedValue <=KLogLbsAssistanceDataEvent))
		{
		filterDetails->SetEventType(ParsedValue) ;	
		}
       /* switch(ParsedValue)
        {
        
        
        case  KCallEvent :
             {
             filterDetails->SetEventType(KLogCallEventType) ;
             break ;
                
             }
                 
        case  KLogDataEvent :
             
                
              filterDetails->SetEventType(KLogDataEventType) ;
              break;
             
                 
        case  KLogFaxEvent :
              filterDetails->SetEventType(KLogFaxEventType) ;
                 break ;
                 
        case  KLogShortMessageEvent :
              filterDetails->SetEventType(KLogShortMessageEventType) ;
                 break ;
                 
        case  KLogMailEvent :
              filterDetails->SetEventType(KLogMailEventType) ;
                 break ;
                 
        case  KLogTaskSchedulerEvent :
              filterDetails->SetEventType(KLogTaskSchedulerEventType) ;
                 break ;
                 
        case  KLogPacketDataEvent :
              filterDetails->SetEventType(KLogPacketDataEventType) ;
                 break ;
                 
        case  KLogLbsSelfLocateEvent :
              filterDetails->SetEventType(KLogLbsSelfLocateEventType) ;
                 break ;
                 
        case  KLogLbsExternalLocateEvent :
              filterDetails->SetEventType(KLogLbsExternalLocateEventType) ;
                 break ;
                 
        case  KLogLbsTransmitLocationEvent :
              filterDetails->SetEventType(KLogLbsTransmitLocationEventType) ;
                 break ;
                 
        case  KLogLbsNetworkLocateEvent :
              filterDetails->SetEventType(KLogLbsNetworkLocateEventType) ;
                 break ;
                 
        case  KLogLbsAssistanceDataEvent :
              filterDetails->SetEventType(KLogLbsAssistanceDataEventType) ;
                 break ; 
                 
            default:
            
            break;
                                                                       
        }
        */
        
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
         _LIT(KLog , "time value not found") ;
	 	 iLog->Log(KLog) ;
         User :: Leave(KErrArgument)  ;
        }
     
       if(ParsedValue> 0 )
        {
        
         TTime time(ParsedValue);
         filterDetails->SetTimer(time) ;
        }
        
       // _LIT(KNull,"NULL");
        
        
        if(aItem.GetNextString(sptr) !=KErrNone)
        {
          _LIT(KLog , "phone number not found") ;
	 	 iLog->Log(KLog) ;
          User :: Leave(KErrArgument) ;  
        }
        
        if((sptr.Compare(KNull)))
        {
          filterDetails->SetNumberType(sptr) ;  
        }
        
        if(aItem.GetNextString(sptr) !=KErrNone)
        {
          _LIT(KLog , "remote party number not found") ;
	 	 iLog->Log(KLog) ;
          User :: Leave(KErrArgument) ;  
        }
        
        if((sptr.Compare(KNull)))
        {
          filterDetails->SetRemotePartyType(sptr) ;  
        }
        
        if(aItem.GetNextInt(ParsedValue) != KErrNone)
        {
          _LIT(KLog , "direction not found") ;
	 	  iLog->Log(KLog) ;
          User :: Leave(KErrArgument) ;  
        }
        
        if(ParsedValue >= 0 )
        {
          filterDetails->SetDirectionType(ParsedValue) ;  
        }
        
        if(aItem.GetNextInt(ParsedValue) !=KErrNone)
        {
          _LIT(KLog , "status value not found") ;
	 	  iLog->Log(KLog) ;
          User :: Leave(KErrArgument) ;  
        }
        
        if(ParsedValue >= 0 )
        {
          filterDetails->SetStatusType(ParsedValue) ;  
        }
        
    
        
        if(aItem.GetNextInt(ParsedValue) != KErrNone)
        {
        _LIT(KLog , "Recent list not found") ;
	 	 iLog->Log(KLog) ;
         User :: Leave(KErrArgument)  ;
        }
        
       /* switch(ParsedValue)
            {
            case -1 :
                filterDetails->SetRecentList(KLogNullRecentList) ;
                break;
            case 1 :
                filterDetails->SetRecentList(KLogRecentIncomingCalls);
                break;
            case 2 :
                filterDetails->SetRecentList(KLogRecentOutgoingCalls);
                break;
            case 3 :
                filterDetails->SetRecentList(KLogRecentMissedCalls);
                break;
            default :
                break;
            }*/
     
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
          _LIT(KLog , "all events  not found") ;
	 	 iLog->Log(KLog) ;
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
         _LIT(KLog , "Sync/Async version  not found") ;
	 	  iLog->Log(KLog) ;
         User :: Leave(KErrArgument)  ;
        }
        
        
      if(aItem.GetNextInt(ParsedValue) != KErrNone )
        {
         _LIT(KLog , "Expected value not found") ;
	 	  iLog->Log(KLog) ;
         ret = KErrNone ;
        }
     else
        {
            ret = ParsedValue ;
        }
        
       
       TRAPD(error , tgetlistgenericL(filterDetails,ParsedValue1)) ; 
       delete filterDetails;
       
       __UHEAP_MARKEND;
      
      if(error == ret)
        {
         return KErrNone; 
        }
      return error; 
       
    
}

//=======================================================================================================
// Position based parsing testcases 
//=======================================================================================================


// Ctprovidertest::AddGenericL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctprovidertest::AddGenericPosL( CStifItemParser& aItem )
    {
    
     TInt ret = 0 ;
      
     _LIT(KTProvidertest , "tprovidertest") ;
     iLog->Log(KTProvidertest) ;
     
     __UHEAP_MARK ;
     
     CEventDetails *eventDetails = CEventDetails :: NewL() ;


       TInt ParsedValue ;
      
       TBufC<100> String; 
       TPtrC sptr;
       sptr.Set(String);
       TInt ParsedValue1 ;
       
       
       
      if(aItem.GetNextInt( ParsedValue) != KErrNone )
        {
          _LIT(KLog , "Eventid  not found") ;
	 	 iLog->Log(KLog) ;
          User :: Leave(KErrArgument) ;
        }
        
        if((ParsedValue >= KCallEvent ) && (ParsedValue <=KLogLbsAssistanceDataEvent))
	        {
	        eventDetails->SetEventType(ParsedValue) ;	
	        }
	        
        else 
	    	{
	    	 _LIT(KLog , "Wrong input EventID") ;
	    	 iLog->Log(KLog) ;
	    	// User :: Leave(KErrGeneral) ;	
	    	}
	 
      
        

     
       if(aItem.GetNextInt(ParsedValue) != KErrNone)
        {
         _LIT(KLog , "duration not found") ;
	 	 iLog->Log(KLog) ;
         User :: Leave(KErrArgument)  ;
        }
     
       if(ParsedValue > 0 )
        {
         eventDetails->SetDurationType(ParsedValue) ;
        }
        
        
        if(aItem.GetNextInt(ParsedValue) != KErrNone)
        {
        _LIT(KLog , "contact id not found") ;
	 	 iLog->Log(KLog) ;
         User :: Leave(KErrArgument)  ;
        }
     
       if(ParsedValue > 0 )
        {
         eventDetails->SetContactType(ParsedValue) ;
        }
        
        
        
       if(aItem.GetNextInt(ParsedValue) != KErrNone)
        {
         _LIT(KLog , "link value not found") ;
	 	 iLog->Log(KLog) ;
         User :: Leave(KErrArgument)  ;
        }
     
       if(ParsedValue > 0 )
        {
         eventDetails->SetLinkType(ParsedValue) ;
        }
        
        if(aItem.GetNextInt(ParsedValue) != KErrNone)
        {
         _LIT(KLog , "time value not found") ;
	 	 iLog->Log(KLog) ;
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
          _LIT(KLog , "subject not found") ;
	 	 iLog->Log(KLog) ;
          User :: Leave(KErrArgument) ;  
        }
        
        if((sptr.Compare(KNull)))
        {
          eventDetails->SetSubjectType(sptr) ;  
        }
        
        if(aItem.GetNextString(sptr) !=KErrNone)
        {
          _LIT(KLog , "phone number not found") ;
	 	 iLog->Log(KLog) ;
          User :: Leave(KErrArgument) ;  
        }
        
        if((sptr.Compare(KNull)))
        {
          eventDetails->SetNumberType(sptr) ;  
        }
        
        if(aItem.GetNextString(sptr) !=KErrNone)
        {
          _LIT(KLog , "remote party number not found") ;
	 	 iLog->Log(KLog) ;
          User :: Leave(KErrArgument) ;  
        }
        
        if((sptr.Compare(KNull)))
        {
          eventDetails->SetRemotePartyType(sptr) ;  
        }
        
        if(aItem.GetNextInt(ParsedValue) !=KErrNone)
        {
          _LIT(KLog , "direction not found") ;
	 	  iLog->Log(KLog) ;
          User :: Leave(KErrArgument) ;  
        }
        
        if(ParsedValue >= 0)
        {
          eventDetails->SetDirectionType(ParsedValue) ;  
        }
        
        if(aItem.GetNextString(sptr) !=KErrNone)
        {
          _LIT(KLog , "description not found") ;
	 	 iLog->Log(KLog) ;
          
          User :: Leave(KErrArgument) ;  
        }
        
        if((sptr.Compare(KNull)))
        {
          eventDetails->SetDescriptionType(sptr) ;  
        }
        
        if(aItem.GetNextInt(ParsedValue) != KErrNone)
        {
          _LIT(KLog , "status value not found") ;
	 	  iLog->Log(KLog) ;
          User :: Leave(KErrArgument) ;  
        }
        
        if(ParsedValue >= 0)
        {
          eventDetails->SetStatusType(ParsedValue) ;  
        }
        
        
        
        if(aItem.GetNextInt(ParsedValue1) != KErrNone)
        {
         _LIT(KLog , "Sync/Async version  not found") ;
	 	  iLog->Log(KLog) ;
         User :: Leave(KErrArgument)  ;
        }
        
        
        
        
        
        
        
     
     if(aItem.GetNextInt(ParsedValue) != KErrNone )
        {
         _LIT(KLog , "Expected value not found") ;
	 	  iLog->Log(KLog) ;
         ret = KErrNone ;
        }
     else
        {
            ret = ParsedValue ;
        }
        
        
        
      
        
      
      TRAPD(error , taddgenericPosL(eventDetails,ParsedValue1)) ;
       delete eventDetails;
       
      
       
     __UHEAP_MARKEND;
      
      if(error == ret)
          {
         return KErrNone; 
          }
      return error ;

    } 
	
	
//-------------------------------------------------------------------------
// Ctprovidertest :: Deletetest Position Based
// Tests the delete use case ofthe provider
//-------------------------------------------------------------------------    
    
TInt Ctprovidertest::DeleteGenericPosL( CStifItemParser& aItem )   
	{
	 TInt parseval =  0 ;
	 TInt async = 0 ;
	 
__UHEAP_MARK ;	 

	 if(aItem.GetNextInt(async) != KErrNone)
	 	{	
	 	 _LIT(KLog , "Sync/Async version  not found") ;
	 	 iLog->Log(KLog) ;
	 	 User :: Leave(KErrNotFound) ;
	 	}
	TInt ret = 0 ;
	
	 //Get the expected return value
	 
	 if(aItem.GetNextInt(parseval) != KErrNone)
	 	{
	 	 _LIT(KLog , "Expected output not found") ;
	 	 iLog->Log(KLog) ;
	 	 User :: Leave(KErrNotFound)  ;
	 	}
	 	
TInt retval = 0 ;	 	
	 	
	 if(async)
	 	{
	 	 _LIT(KLog , "Functionality test of delete async api") ;
	 	 iLog->Log(KLog) ;
	 	 
	    TRAPD(aerr , tdeleteTestasyncL(parseval)) ;
	    
	    if(aerr != parseval)
	    	{
	    	 _LIT(KLog , "Expected and the return value dont match") ;
	    	 iLog->Log(KLog) ;
	    	 retval = KErrArgument ; 
	    	}
	    else 
	    	{
	    	 retval = KErrNone ;	
	    	}	
	    	
	 	}
	 else 
	 {
		TRAPD(error , tdeleteTestPosL(parseval))  ; 	
		
		if(error != parseval)
			{
			 _LIT(KLog , "Expected and the return value dont match") ;
			 iLog->Log(KLog) ;
			 retval = KErrArgument ;
			}
		else
			{
				retval = KErrNone ;
			}	
	 }
	
	
__UHEAP_MARKEND	;
  
 
    return KErrNone ;	 	
	}

 // -----------------------------------------------------------------------------
// Ctprovidertest::GetListGenericL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctprovidertest::GetListGenericPosL( CStifItemParser& aItem )

{
     TInt ret = 0 ;
      
     _LIT(KTProvidertest , "tprovidertest") ;
     iLog->Log(KTProvidertest) ;
     
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
       
       
       /*if(aItem.GetNextInt(ParsedValue) != KErrNone)
        {
        _LIT(KLog , "Event id not found") ;
	 	 iLog->Log(KLog) ;
         User :: Leave(KErrArgument)  ;
        }
     
       if(ParsedValue > 0 )
        {
         filterDetails->SetEventId(ParsedValue) ;
        }*/
       
       
       
       if(aItem.GetNextInt( ParsedValue) != KErrNone )
        {
          _LIT(KLog , "Eventtype  not found") ;
	 	 iLog->Log(KLog) ;
          User :: Leave(KErrArgument) ;
        }
         
     if((ParsedValue >= KCallEvent ) && (ParsedValue <=KLogLbsAssistanceDataEvent))
	        {
	        filterDetails->SetEventType(ParsedValue) ;	
	        }
	        
        else 
	    	{
	    	 _LIT(KLog , "Wrong input EventID") ;
	    	 iLog->Log(KLog) ;
	    	// User :: Leave(KErrGeneral) ;	
	    	}
      /*  switch(ParsedValue)
        {
        
        
        case  KCallEvent :
             {
             filterDetails->SetEventType(KLogCallEventType) ;
             break ;
                
             }
                 
        case  KLogDataEvent :
             
                
              filterDetails->SetEventType(KLogDataEventType) ;
              break;
             
                 
        case  KLogFaxEvent :
              filterDetails->SetEventType(KLogFaxEventType) ;
                 break ;
                 
        case  KLogShortMessageEvent :
              filterDetails->SetEventType(KLogShortMessageEventType) ;
                 break ;
                 
        case  KLogMailEvent :
              filterDetails->SetEventType(KLogMailEventType) ;
                 break ;
                 
        case  KLogTaskSchedulerEvent :
              filterDetails->SetEventType(KLogTaskSchedulerEventType) ;
                 break ;
                 
        case  KLogPacketDataEvent :
              filterDetails->SetEventType(KLogPacketDataEventType) ;
                 break ;
                 
        case  KLogLbsSelfLocateEvent :
              filterDetails->SetEventType(KLogLbsSelfLocateEventType) ;
                 break ;
                 
        case  KLogLbsExternalLocateEvent :
              filterDetails->SetEventType(KLogLbsExternalLocateEventType) ;
                 break ;
                 
        case  KLogLbsTransmitLocationEvent :
              filterDetails->SetEventType(KLogLbsTransmitLocationEventType) ;
                 break ;
                 
        case  KLogLbsNetworkLocateEvent :
              filterDetails->SetEventType(KLogLbsNetworkLocateEventType) ;
                 break ;
                 
        case  KLogLbsAssistanceDataEvent :
              filterDetails->SetEventType(KLogLbsAssistanceDataEventType) ;
                 break ; 
                 
            default:
            
            break;
                                                                       
        }*/
        
        
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
         _LIT(KLog , "time value not found") ;
	 	 iLog->Log(KLog) ;
         User :: Leave(KErrArgument)  ;
        }
     
       if(ParsedValue> 0 )
        {
        
         TTime time(ParsedValue);
         filterDetails->SetTimer(time) ;
        }
        
       
        
        
        if(aItem.GetNextString(sptr) !=KErrNone)
        {
          _LIT(KLog , "phone number not found") ;
	 	 iLog->Log(KLog) ;
          User :: Leave(KErrArgument) ;  
        }
        
        if((sptr.Compare(KNull)))
        {
          filterDetails->SetNumberType(sptr) ;  
        }
        
        if(aItem.GetNextString(sptr) !=KErrNone)
        {
          _LIT(KLog , "remote party number not found") ;
	 	 iLog->Log(KLog) ;
          User :: Leave(KErrArgument) ;  
        }
        
        if((sptr.Compare(KNull)))
        {
          filterDetails->SetRemotePartyType(sptr) ;  
        }
        
        if(aItem.GetNextInt(ParsedValue) != KErrNone)
        {
          _LIT(KLog , "direction not found") ;
	 	  iLog->Log(KLog) ;
          User :: Leave(KErrArgument) ;  
        }
        
        if( ParsedValue >= 0 )
        {
          filterDetails->SetDirectionType(ParsedValue) ;  
        }
        
        if(aItem.GetNextInt(ParsedValue) !=KErrNone)
        {
          _LIT(KLog , "status value not found") ;
	 	  iLog->Log(KLog) ;
          User :: Leave(KErrArgument) ;  
        }
        
        if(ParsedValue >= 0)
        {
          filterDetails->SetStatusType(ParsedValue) ;  
        }
        
       /* if(aItem.GetNextInt( ParsedValue) != KErrNone )
        {
          _LIT(KLog , "recentlist  not found") ;
	 	 iLog->Log(KLog) ;
          User :: Leave(KErrArgument) ;
        }
        
        
       if(ParsedValue == 0 )
        {
         filterDetails->SetRecentList(FALSE) ;
        }
        else if(ParsedValue == 1)
        
        {
            filterDetails->SetRecentList(TRUE); 
        }*/
        
        if(aItem.GetNextInt(ParsedValue) != KErrNone)
        {
        _LIT(KLog , "Recent list not found") ;
	 	 iLog->Log(KLog) ;
         User :: Leave(KErrArgument)  ;
        }
        
       /* switch(ParsedValue)
            {
            case -1 :
                filterDetails->SetRecentList(KLogNullRecentList) ;
                break;
            case 1 :
                filterDetails->SetRecentList(KLogRecentIncomingCalls);
                break;
            case 2 :
                filterDetails->SetRecentList(KLogRecentOutgoingCalls);
                break;
            case 3 :
                filterDetails->SetRecentList(KLogRecentMissedCalls);
                break;
            default :
                break;
            }*/
     
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
          _LIT(KLog , "all events  not found") ;
	 	 iLog->Log(KLog) ;
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
         _LIT(KLog , "Sync/Async version  not found") ;
	 	  iLog->Log(KLog) ;
         User :: Leave(KErrArgument)  ;
        }
        
      
        
      if(aItem.GetNextInt(ParsedValue) != KErrNone )
        {
         _LIT(KLog , "Expected value not found") ;
	 	  iLog->Log(KLog) ;
         ret = KErrNone ;
        }
     else
        {
            ret = ParsedValue ;
        }
        
       
       TRAPD(error , tgetlistgenericPosL(filterDetails,ParsedValue1)) ; 
       delete filterDetails;
       
       __UHEAP_MARKEND;
      
      if(error == ret)
        {
         return KErrNone; 
        }
      return error; 
       
    
}
	
		
// -----------------------------------------------------------------------------
// Ctprovidertest::?member_function
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
/*
TInt Ctprovidertest::?member_function(
   CItemParser& aItem )
   {

   ?code

   }
*/

// ========================== OTHER EXPORTED FUNCTIONS =========================
// None

//  End of File
