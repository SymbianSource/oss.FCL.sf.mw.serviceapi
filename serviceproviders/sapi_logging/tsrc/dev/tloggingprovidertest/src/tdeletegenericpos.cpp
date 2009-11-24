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
#include <StifTestInterface.h>

#include <liwservicehandler.h>
#include <liwcommon.h>


#include "tconstants.h"
#include "tprovidertest.h"
#include "tprovidercallback.h"
#include "serviceerrno.h"

void Ctprovidertest :: tdeleteTestPosL(TInt aExpected)
{
  if(aExpected != KErrNone)
  	{
  	 _LIT(KLog , "Negative test case for delete api") ;
  	 iLog->Log(KLog) ;
  tdeleteNegativePosL();
  	  
  	}
  	
  else 
  	{
  	 _LIT(KLog , "Functional test for the delete api")  ;
  	 iLog->Log(KLog)  ;	
  	 tdeleteFunctionalPosL() ;
  	}  	
}


//----------------------------------------------------------------------
// internal utility function which tests the functionality of delete api
//
//----------------------------------------------------------------------

void Ctprovidertest :: tdeleteFunctionalPosL()
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

  
 TBufC<20> itemid= (outparm1->Value()).AsDes() ;
  
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

void Ctprovidertest :: tdeleteNegativePosL()
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
   
  //inputlist->AppendL(TLiwGenericParam(KData , TLiwVariant((TInt32)itemid))) ;
  
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
void Ctprovidertest :: tdeleteTestasyncPosL(TInt aExpected)
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


void Ctprovidertest :: tdeleteFunctionalAsyncPosL(void)
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
 
   
  inputlist->AppendL(TLiwGenericParam(KData , TLiwVariant(Idmap))) ;
  Idmap->DecRef();
  CmdBuf = KCmdDelete ;
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

//----------------------------------------------------------------------
// negative test case for delete async
//
//----------------------------------------------------------------------



void Ctprovidertest :: tdeleteNegativeasyncPosL(void)
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
	Idmap->DecRef();
	TBufC8<20>CmdBuf(KCmdDelete) ;
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