/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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

#include <StifParser.h>
#include <Stiftestinterface.h>

#include <LiwServiceHandler.h>
#include <LiwCommon.h>


#include "tconstants.h"
#include "tprovidertest.h"
#include "tprovidercallback.h"
#include "serviceerrno.h"

void Ctprovidertest :: tdeleteTestL(TInt aExpected)
{
  if(aExpected != KErrNone)
  	{
  	 _LIT(KLog , "Negative test case for delete api") ;
  	 iLog->Log(KLog) ;
  tdeleteNegativeL();
  	  
  	}
  	
  else 
  	{
  	 _LIT(KLog , "Functional test for the delete api")  ;
  	 iLog->Log(KLog)  ;	
  	 tdeleteFunctionalL() ;
  	}  	
}


//----------------------------------------------------------------------
// internal utility function which tests the functionality of delete api
//
//----------------------------------------------------------------------

void Ctprovidertest :: tdeleteFunctionalL()
	{
	  
	_LIT(KOwnEventSubject, "RandomLogEvent");
	_LIT(KOwnEventRemoteParty, "OwnContact");

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
	 _LIT(KLog , "Logging interface not found") ;
	 iLog->Log(KLog) ;
	 
	 User :: Leave(KErrArgument) ;
	}
	
   MLiwInterface* LogInterface = (genericparm->Value()).AsInterface();
   
   //Add an event and then delete this added event ;
   
   CLiwDefaultMap *EventDetails = CLiwDefaultMap :: NewL() ;	
   
   EventDetails->InsertL(KEventTypeKey ,TLiwVariant((TInt32)KLogShortMessageEvent)) ;
   
   
   TBufC16<10> contentType(KContentType) ;
   
   //Insert the contenttype to inputlist
   inputlist->AppendL(TLiwGenericParam(KContentTypeKey , TLiwVariant(contentType))) ;
 
   
   inputlist->AppendL(TLiwGenericParam(KEventDetails , TLiwVariant(EventDetails))) ;
   
   EventDetails->DecRef();
   TBufC8<20>CmdBuf(KCmdAdd) ;
   
   LogInterface->ExecuteCmdL(CmdBuf , *inputlist , *outputlist) ;
   
   //Now get the id to deleted
   
   pos = 0 ;
   
   const TLiwGenericParam *outparm1 = outputlist->FindFirst(pos , KResponse) ; 
   
   if(!outparm1)
   	{
   	 _LIT8(KLog , "Log id of the delete item not found") ;
   	 iLog->Log(KLog) ;
   	 User :: Leave(KErrArgument) ;
   	}
  	
  //Now delete the added item
  
// TInt itemid = (outparm1->Value()).AsTInt32() ;

  TBufC<20> itemid = (outparm1->Value()).AsDes() ;
  
 /* if(itemid  < 0 )
   {
   _LIT(KLog , "Invalid item id ") ;
   iLog->Log(KLog) ;
   User :: Leave(KErrArgument) ;	
   }*/
   
  inputlist->Reset() ; outputlist->Reset() ;
  
   CLiwDefaultMap *Idmap = CLiwDefaultMap :: NewL() ;
   Idmap->InsertL(KLogId ,TLiwVariant(itemid)) ;
   
   //Insert the contenttype to inputlist
   inputlist->AppendL(TLiwGenericParam(KContentTypeKey , TLiwVariant(contentType))) ;
 
   
 // inputlist->AppendL(TLiwGenericParam(KLogId , TLiwVariant((TInt32)itemid))) ;
    inputlist->AppendL(TLiwGenericParam(KData , TLiwVariant(Idmap))) ; 
    Idmap->DecRef();
  CmdBuf = KCmdDelete ;
  LogInterface->ExecuteCmdL(CmdBuf , *inputlist , *outputlist) ;
  
  pos = 0 ;
  const TLiwGenericParam *Errprm = outputlist->FindFirst(pos , KErrCode ) ;
  
  if(!Errprm)
  	{
  	 _LIT(KLog , "Generic error param missing form the outputlist of delete" ) ;
  	 iLog->Log(KLog) ;
  	 User :: Leave(KErrArgument) ;
  	}
  	
  TInt retval  = Errprm->Value().AsTInt32() ;
  
  if(retval != SErrNone )
  	{
  	 _LIT(KLog , "Functionality test of delete call failed ") ;
  	 iLog->Log(KLog) ;
  	 User :: Leave(KErrArgument) ;
  	}
  	  LogInterface->Close() ;
  	 delete ServiceHandler;
 
      
   	 a.ResetAndDestroy();
   	 a.Close();
    
   
   
     
  }
  
  
  //----------------------------------------------------------------------
// Negative testcase for delete api
//
//----------------------------------------------------------------------

void Ctprovidertest :: tdeleteNegativeL()
	{
	

    CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();
     // Input and output parameter list
    CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    
    CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());
    
    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KDsInterfaceName , KLoggingContents) ;
    
    crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray a;
	
	a.AppendL(crit);
	
	ServiceHandler->AttachL(a) ;
	
	TBufC16<10> contentType(KContentType) ;
   
   //Insert the contenttype to inputlist
   inputlist->AppendL(TLiwGenericParam(KContentTypeKey , TLiwVariant(contentType))) ;
 
	
	ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist);
    
    TInt pos = 0;
	
 
	const TLiwGenericParam *genericparm = outputlist->FindFirst(pos  , KDsInterfaceName);
	
	if(!genericparm)
	{
	 _LIT(KLog , "Logging interface not found") ;
	 iLog->Log(KLog) ;
	 
	 User :: Leave(KErrArgument) ;
	}
	
   MLiwInterface* LogInterface = (genericparm->Value()).AsInterface();
   
   
  
  	
  
  
  TInt itemid = -1;
  TBuf<8> des;
  des.Num(itemid);
 
   
   inputlist->Reset() ;
   outputlist->Reset() ;
   
   CLiwDefaultMap *Idmap = CLiwDefaultMap :: NewL() ;
   Idmap->InsertL(KLogId ,TLiwVariant(des)) ;
   
  inputlist->AppendL(TLiwGenericParam(KData , TLiwVariant(Idmap))) ;
  Idmap->DecRef();
  TBufC8<20>CmdBuf(KCmdDelete) ;
  //CmdBuf = KCmdDelete ;
  LogInterface->ExecuteCmdL(CmdBuf , *inputlist , *outputlist) ;
  
  pos = 0 ;
  const TLiwGenericParam *Errprm = outputlist->FindFirst(pos , KErrCode ) ;
  
  if(!Errprm)
  	{
  	 _LIT(KLog , "Generic error param missing form the outputlist of delete" ) ;
  	 iLog->Log(KLog) ;
  	 User :: Leave(KErrArgument) ;
  	}
  	
  TInt retval  = Errprm->Value().AsTInt32() ;
  
  if(retval != SErrNone )
  	{
  	     LogInterface->Close() ;
  	   delete ServiceHandler;
 
      
   	 a.ResetAndDestroy();
   	 a.Close();
    
  
   
  	 _LIT(KLog , "Functionality test of delete call failed ") ;
  	 iLog->Log(KLog) ;
  	 User :: Leave(KErrArgument) ;
  	}
  	
	LogInterface->Close() ;
	delete ServiceHandler;
 
   
   	 a.ResetAndDestroy();
   	 a.Close();
    
   
  }


//-----------------------------------------------------------------------------
// Functionality test for delete async call
//-----------------------------------------------------------------------------
void Ctprovidertest :: tdeleteTestasyncL(TInt aExpected)
{
  if(aExpected != KErrNone)
  	{
  	 _LIT(KLog , "Negative test case for delete api") ;
  	 iLog->Log(KLog) ;
  	 tdeleteNegativeasyncL();
  	  
  	}
  	
  else 
  	{
  	 _LIT(KLog , "Functional test for the delete async api")  ;
  	 iLog->Log(KLog)  ;	
  	 tdeleteFunctionalAsyncL() ;
  	}  	
}

//----------------------------------------------------------------------
// positive test case for delete async
//
//----------------------------------------------------------------------


void Ctprovidertest :: tdeleteFunctionalAsyncL(void)
{
		
	NotifyCB Callback ;
		
	_LIT(KOwnEventSubject, "RandomLogEvent");
	_LIT(KOwnEventRemoteParty, "OwnContact");

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
	 _LIT(KLog , "Logging interface not found") ;
	 iLog->Log(KLog) ;
	 
	 User :: Leave(KErrArgument) ;
	}
	
   MLiwInterface* LogInterface = (genericparm->Value()).AsInterface();
   
   //Add an event and then delete this added event ;
   
   CLiwDefaultMap *EventDetails = CLiwDefaultMap :: NewL() ;	
   
   EventDetails->InsertL(KEventTypeKey ,TLiwVariant((TInt32)KLogShortMessageEvent)) ;
   
   
   /**
    * First append content type
    */
    
    TBufC16<10> contentType(KContentType) ;
   
   //Insert the contenttype to inputlist
   inputlist->AppendL(TLiwGenericParam(KContentTypeKey , TLiwVariant(contentType))) ;
 
   
   inputlist->AppendL(TLiwGenericParam(KEventDetails , TLiwVariant(EventDetails))) ;
   
   EventDetails->DecRef();
   TBufC8<20>CmdBuf(KCmdAdd) ;
   
   LogInterface->ExecuteCmdL(CmdBuf , *inputlist , *outputlist) ;
   
   //Now get the id to deleted
   
   pos = 0 ;
   
   const TLiwGenericParam *outparm1 = outputlist->FindFirst(pos , KResponse) ; 
   
   if(!outparm1)
   	{
   	 _LIT8(KLog , "Log id of the delete item not found") ;
   	 iLog->Log(KLog) ;
   	 User :: Leave(KErrArgument) ;
   	}
  	
  //Now delete the added item
  
  TBufC<20> itemid = (outparm1->Value()).AsDes();
// TInt itemid = (outparm1->Value()).AsTInt32() ;
  
  /*if(itemid  < 0 )
   {
   _LIT(KLog , "Invalid item id ") ;
   iLog->Log(KLog) ;
   User :: Leave(KErrArgument) ;	
   }*/
   
  inputlist->Reset() ; outputlist->Reset() ;
    CLiwDefaultMap *Idmap = CLiwDefaultMap :: NewL() ;
   Idmap->InsertL(KLogId ,TLiwVariant(itemid)) ;
  
   //Insert the contenttype to inputlist
   inputlist->AppendL(TLiwGenericParam(KContentTypeKey , TLiwVariant(contentType))) ;
 
   
  inputlist->AppendL(TLiwGenericParam(KData , TLiwVariant(Idmap))) ;
   Idmap->DecRef();
  CmdBuf = KCmdDelete ;
  LogInterface->ExecuteCmdL(CmdBuf , *inputlist , *outputlist ,KLiwOptASyncronous, &Callback) ;
  
  pos = 0 ;
  const TLiwGenericParam *Errprm = outputlist->FindFirst(pos , KErrCode ) ;
  
  if(!Errprm)
  	{
  	 _LIT(KLog , "Generic error param missing form the outputlist of delete" ) ;
  	 iLog->Log(KLog) ;
  	 User :: Leave(KErrArgument) ;
  	}
  	
  TInt retval  = Errprm->Value().AsTInt32() ;
  
  if(retval != SErrNone )
  	{
  	 _LIT(KLog , "Functionality test of delete call failed ") ;
  	 iLog->Log(KLog) ;
  	 User :: Leave(KErrArgument) ;
  	}
  	
 Callback.Start() ;
 
 if(Callback.Status() != KErrNone) 
 	{
 	 _LIT(KLog , "Async status error ") ;
 	 iLog->Log(KLog) ;
 	 User :: Leave (Callback.Status()) ;
 	}
 	LogInterface->Close() ;
    delete ServiceHandler;
 
   
   	 a.ResetAndDestroy();
   	 a.Close();
   
    
}

//----------------------------------------------------------------------
// negative test case for delete async
//
//----------------------------------------------------------------------



void Ctprovidertest :: tdeleteNegativeasyncL(void)
{
		
	NotifyCB Callback ;
		
	
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
	 _LIT(KLog , "Logging interface not found") ;
	 iLog->Log(KLog) ;
	 
	 User :: Leave(KErrArgument) ;
	}
	
   MLiwInterface* LogInterface = (genericparm->Value()).AsInterface();
   
   
  
  
 TInt itemid = -1;
  TBuf<8> des;
  des.Num(itemid);
  
  inputlist->Reset() ; 
  outputlist->Reset() ;
   
   CLiwDefaultMap *Idmap = CLiwDefaultMap :: NewL() ;
   Idmap->InsertL(KLogId ,TLiwVariant(des)) ;
   
	TBufC16<10> contentType(KContentType) ;

	//Insert the contenttype to inputlist
	inputlist->AppendL(TLiwGenericParam(KContentTypeKey , TLiwVariant(contentType))) ;

	inputlist->AppendL(TLiwGenericParam(KData , TLiwVariant(Idmap))) ;
	TBufC8<20>CmdBuf(KCmdDelete) ;
	Idmap->DecRef();
 //CmdBuf = KCmdDelete ;
  LogInterface->ExecuteCmdL(CmdBuf , *inputlist , *outputlist ,KLiwOptASyncronous , &Callback) ;
  
  pos = 0 ;
  const TLiwGenericParam *Errprm = outputlist->FindFirst(pos , KErrCode ) ;
  
  if(!Errprm)
  	{
  	 _LIT(KLog , "Generic error param missing form the outputlist of delete" ) ;
  	 iLog->Log(KLog) ;
  	 User :: Leave(KErrArgument) ;
  	}
  	
  TInt retval  = Errprm->Value().AsTInt32() ;
  
  if(retval != SErrNone )
  	{
  	 _LIT(KLog , "Functionality test of delete call failed ") ;
  	 iLog->Log(KLog) ;
  	 User :: Leave(KErrArgument) ;
  	}
  	
 Callback.Start() ;
 
 if(Callback.Status() != KErrNone) 
 	{
 	 _LIT(KLog , "Async status error ") ;
 	 iLog->Log(KLog) ;
 	 User :: Leave (Callback.Status()) ;
 	}
 	  LogInterface->Close() ;
     delete ServiceHandler;
 
   
   	 a.ResetAndDestroy();
   	 a.Close();
    
   
}

/**
 * Delete testcase for deleting all events
 */
 
 void Ctprovidertest :: tdeleteAllEventsL(TInt aSync)
	{
	if(aSync)
		{
		tdeleteAllEventsAsyncL() ;
		}
	else
		{
		tdeleteAllEventsSyncL() ;
		}	
	}
	

/**
 * Synchronously delete all events
 */
 
 void Ctprovidertest ::	tdeleteAllEventsSyncL()
 	{
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
		_LIT(KLog , "Logging interface not found") ;
		iLog->Log(KLog) ;

		User :: Leave(KErrArgument) ;
		}

	MLiwInterface* LogInterface = (genericparm->Value()).AsInterface();
	
	

	// set the identity information
    TBufC8<20>CmdBufSet(KCmdGetList) ;
    
    outputlist->Reset() ;
  
    inputlist->Reset() ;
  
    CLiwDefaultMap *EventFilter = CLiwDefaultMap :: NewL() ;
    
  //if(aDetails->GetEventId()!=0)  
   
  	EventFilter->InsertL(KAllEvents , TLiwVariant(TRUE)) ;
  
  
	TBufC16<10> contentType(KContentType) ;

	//Insert the contenttype to inputlist
	inputlist->AppendL(TLiwGenericParam(KContentTypeKey , TLiwVariant(contentType))) ;
	inputlist->AppendL(TLiwGenericParam(KFilter , TLiwVariant(EventFilter))) ;
    EventFilter->DecRef() ;
    
    LogInterface->ExecuteCmdL(CmdBufSet , *inputlist , *outputlist ); 
  
  
  
	/** 
	* Extract the error param, and check the status of the call
	*/
	TInt index = 0 ;

	const TLiwGenericParam *ErrCode  = outputlist->FindFirst(index , KErrCode) ;

	if(!ErrCode )
		{
		 _LIT(KLog , "Generic error param missing form the outputlist of add" ) ;
		 iLog->Log(KLog) ;
		 User :: Leave(KErrArgument) ;
		}

	TInt retval  = ErrCode->Value().AsTInt32() ;

	if(retval != SErrNone )
		{
		 _LIT(KLog , "Functionality test of add call failed ") ;
		 iLog->Log(KLog) ;
		 User :: Leave(KErrArgument) ;
		}



	pos = 0 ;

	const TLiwGenericParam *LogIterParam = outputlist->FindFirst(pos , KLogIter)  ;



	 CLiwIterable *LogIter = (LogIterParam->Value()).AsIterable() ;
	 
	 if(!LogIter)
	 	{
	 	 _LIT(KLog , "LogIterator not found \n") ;
	 	 iLog->Log(KLog) ;
	 	 User :: Leave (KErrGeneral) ;
	 	}
	 TLiwVariant   Events ;
	 TLiwVariant   EventDetails ;
	 
	 
	 
	 CmdBufSet = KCmdDelete ;
	 
	 while(LogIter->NextL(EventDetails))
	 	{
	 	 const CLiwMap *eventDetails = EventDetails.AsMap() ;
	 	 
	 	 if(eventDetails->FindL(KLogId , Events) == KErrNotFound)
	 	 	{
	 	 	 _LIT(KLog , "Item_id not found") ;
	 	 	 iLog->Log(KLog) ;
	 	 	 User :: Leave(KErrArgument) ;
	 	 	}
	 	 
	 	 
	 	 
	 	 TInt32 eventid =  Events.AsTInt32() ;
	 	 
	 	 inputlist->Reset() ;
	 	 
	 	 inputlist->AppendL(TLiwGenericParam(KContentTypeKey , TLiwVariant(KContentType))) ;
	 	 inputlist->AppendL(TLiwGenericParam(KLogId , TLiwVariant(eventid))) ;
	 	 
	 	 
	 	 LogInterface->ExecuteCmdL(CmdBufSet , *inputlist , *outputlist ) ;
	 	 
	 	 (const_cast<CLiwMap *>(eventDetails))->DecRef() ;
	 	}
	 	
	 	EventDetails.Reset() ;
	 	Events.Reset() ;
	 	
	CmdBufSet = KCmdGetList ;
	
	
	inputlist->Reset() ;
	inputlist->AppendL(TLiwGenericParam(KContentTypeKey , TLiwVariant(KContentType))) ;
	LogInterface->ExecuteCmdL(CmdBufSet , *inputlist , *outputlist ); 
	
	
	index = 0 ;
	ErrCode  = outputlist->FindFirst(index , KErrCode) ;
	
	if(!ErrCode )
		{
		 _LIT(KLog , "Generic error param missing form the outputlist of add" ) ;
		 iLog->Log(KLog) ;
		 User :: Leave(KErrArgument) ;
		}

    retval  = ErrCode->Value().AsTInt32() ;

	if(retval != SErrNone )
		{
		 _LIT(KLog , "Functionality test of add call failed ") ;
		 iLog->Log(KLog) ;
		 User :: Leave(KErrArgument) ;
		}

  
   LogIterParam = outputlist->FindFirst(pos , KLogIter)  ;	
   LogIter = (LogIterParam->Value()).AsIterable() ; 
   
   TInt totalCnt ;
  
  for( totalCnt = 0 ; LogIter->NextL(EventDetails) ;  ++totalCnt)
  	{
  	 const CLiwMap *eventDetails = EventDetails.AsMap() ;
	 	 
	 	 if(eventDetails->FindL(KLogId , Events) == KErrNotFound)
	 	 	{
	 	 	 _LIT(KLog , "Item_id not found") ;
	 	 	 iLog->Log(KLog) ;
	 	 	 User :: Leave(KErrArgument) ;
	 	 	}
	 	 
	 	 
	 	 
	 	 TInt32 eventid =  Events.AsTInt32() ;
	 	 
	 	 inputlist->Reset() ;
	 	 
	 	 inputlist->AppendL(TLiwGenericParam(KContentTypeKey , TLiwVariant(KContentType))) ;
	 	 inputlist->AppendL(TLiwGenericParam(KLogId , TLiwVariant(eventid))) ;
	 	 
	 	 LogInterface->ExecuteCmdL(CmdBufSet , *inputlist , *outputlist ) ;
	 	 
	 	 (const_cast<CLiwMap *>(eventDetails))->DecRef() ;
  	}
  	
	Events.Reset() ;
	EventDetails.Reset() ;
	LogInterface->Close() ;
	delete  ServiceHandler ;
	a.ResetAndDestroy() ;
	a.Close() ;
	
	if(totalCnt > 0)
		{
		 _LIT(KLog , "Total count is still greater than zero") ;
		 iLog->Log(KLog) ;
		 User :: Leave (KErrGeneral) ;
		}

 	}
	
/**
 * Synchronously delete all events
 */
 
 void Ctprovidertest ::	tdeleteAllEventsAsyncL(void)
 	{
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
		_LIT(KLog , "Logging interface not found") ;
		iLog->Log(KLog) ;

		User :: Leave(KErrArgument) ;
		}

	MLiwInterface* LogInterface = (genericparm->Value()).AsInterface();
	
	

	// set the identity information
    TBufC8<20>CmdBufSet(KCmdGetList) ;
    
    outputlist->Reset() ;
  
    inputlist->Reset() ;
  
    CLiwDefaultMap *EventFilter = CLiwDefaultMap :: NewL() ;
    
  //if(aDetails->GetEventId()!=0)  
   
  	EventFilter->InsertL(KAllEvents , TLiwVariant(TRUE)) ;
  
  
	TBufC16<10> contentType(KContentType) ;

	//Insert the contenttype to inputlist
	inputlist->AppendL(TLiwGenericParam(KContentTypeKey , TLiwVariant(contentType))) ;
	inputlist->AppendL(TLiwGenericParam(KFilter , TLiwVariant(EventFilter))) ;
    EventFilter->DecRef() ;
    
    LogInterface->ExecuteCmdL(CmdBufSet , *inputlist , *outputlist ); 
  
  
  
	/** 
	* Extract the error param, and check the status of the call
	*/
	TInt index = 0 ;

	const TLiwGenericParam *ErrCode  = outputlist->FindFirst(index , KErrCode) ;

	if(!ErrCode )
		{
		 _LIT(KLog , "Generic error param missing form the outputlist of add" ) ;
		 iLog->Log(KLog) ;
		 User :: Leave(KErrArgument) ;
		}

	TInt retval  = ErrCode->Value().AsTInt32() ;

	if(retval != SErrNone )
		{
		 _LIT(KLog , "Functionality test of add call failed ") ;
		 iLog->Log(KLog) ;
		 User :: Leave(KErrArgument) ;
		}



	pos = 0 ;

	const TLiwGenericParam *LogIterParam = outputlist->FindFirst(pos , KLogIter)  ;



	 CLiwIterable *LogIter = (LogIterParam->Value()).AsIterable() ;
	 TLiwVariant   Events ;
	 TLiwVariant   EventDetails ;
	 
	 
	 
	 CmdBufSet = KCmdDelete ;
	 NotifyCB Callback ;
	 
	 while(LogIter->NextL(EventDetails))
	 	{
	 	 const CLiwMap *eventDetails = EventDetails.AsMap() ;
	 	 
	 	 if(eventDetails->FindL(KLogId , Events) == KErrNotFound)
	 	 	{
	 	 	 _LIT(KLog , "Item_id not found") ;
	 	 	 iLog->Log(KLog) ;
	 	 	 User :: Leave(KErrArgument) ;
	 	 	}
	 	 
	 	 
	 	 
	 	 TUid eventid =  Events.AsTUid() ;
	 	 
	 	 inputlist->Reset() ;
	 	 
	 	 inputlist->AppendL(TLiwGenericParam(KContentTypeKey , TLiwVariant(KContentType))) ;
	 	 inputlist->AppendL(TLiwGenericParam(KLogId , TLiwVariant(eventid))) ;
	 	 
	 	 
	 	 
	 	 LogInterface->ExecuteCmdL(CmdBufSet , *inputlist , *outputlist , 0 , &Callback ) ;
	 	 Callback.Start() ;
	 	 
	 	 (const_cast<CLiwMap *>(eventDetails))->DecRef() ;
	 	 
	 	 if(Callback.Status() != KErrNone)
	 	 	{
	 	 	 _LIT(KLog , "Callback status not KErrNone") ;
	 	 	 iLog->Log(KLog) ;
	 	 	 User :: Leave(KErrArgument) ;
	 	 	}
	 	 
	 	}
	 	
   Events.Reset() ;
   EventDetails.Reset() ;
   
    LogIterParam = outputlist->FindFirst(pos , KLogIter)  ;	
   LogIter = (LogIterParam->Value()).AsIterable() ; 
   
   TInt totalCnt ;
  
  for( totalCnt = 0 ; LogIter->NextL(EventDetails) ;  ++totalCnt)
  	{
  	 const CLiwMap *eventDetails = EventDetails.AsMap() ;
	 	 
	 	 if(eventDetails->FindL(KLogId , Events) == KErrNotFound)
	 	 	{
	 	 	 _LIT(KLog , "Item_id not found") ;
	 	 	 iLog->Log(KLog) ;
	 	 	 User :: Leave(KErrArgument) ;
	 	 	}
	 	 
	 	 
	 	 
	 	 TInt32 eventid =  Events.AsTInt32() ;
	 	 
	 	 inputlist->Reset() ;
	 	 
	 	 inputlist->AppendL(TLiwGenericParam(KContentTypeKey , TLiwVariant(KContentType))) ;
	 	 inputlist->AppendL(TLiwGenericParam(KLogId , TLiwVariant(eventid))) ;
	 	 
	 	 LogInterface->ExecuteCmdL(CmdBufSet , *inputlist , *outputlist ) ;
	 	 
	 	 (const_cast<CLiwMap *>(eventDetails))->DecRef() ;
  	}
  	
	Events.Reset() ;
	EventDetails.Reset() ;
	LogInterface->Close() ;
	delete  ServiceHandler ;
	a.ResetAndDestroy() ;
	a.Close() ;
	
	if(totalCnt > 0)
		{
		 _LIT(KLog , "Total count is still greater than zero") ;
		 iLog->Log(KLog) ;
		 User :: Leave (KErrGeneral) ;
		}

  



	LogInterface->Close() ;
	delete  ServiceHandler ;
	a.ResetAndDestroy() ;
	a.Close() ;
  
 	}
	
