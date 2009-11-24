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
#include "teventdetails.h"
#include "tprovidercallback.h"
#include "serviceerrno.h"




void Ctprovidertest ::  taddtest1L(void)
{
    TBuf<6> EmptyDes ;
    NotifyCB cb ;
   
 
   
    
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
   
     
	
  
    
 //First set the identity information
  TBufC8<20>CmdBufSet(KCmdRequestNotification) ;
  
  outputlist->Reset() ;
  
  inputlist->Reset() ;
  
  CLiwDefaultMap *EventDetails = CLiwDefaultMap :: NewL() ;
  
  
  EventDetails->InsertL(KDelayTime , TLiwVariant(TInt32(300000)) );
  TBufC16<10> contentType(KContentType) ;
 
   
   //Insert the contenttype to inputlist
   inputlist->AppendL(TLiwGenericParam(KNullDesC8 , TLiwVariant(contentType))) ;
 
  
  inputlist->AppendL(TLiwGenericParam(KFilter , TLiwVariant(EventDetails))) ;
  EventDetails->DecRef();
 
  
    
  LogInterface->ExecuteCmdL(CmdBufSet , *inputlist , *outputlist ,KLiwOptASyncronous, &cb);

  TInt index1 = 0 ;
   const TLiwGenericParam *transid = outputlist->FindFirst(index1 , KTransactionId) ;
  
  if(!transid)
    {
   
   	 User :: Leave(KErrArgument) ;
    }
  TInt32 transid1 = (transid->Value()).AsTInt32() ;   
    
  inputlist->Reset() ; outputlist->Reset() ;
  TBufC8<20>CmdBuf1(KCmdCancel) ;  
  inputlist->AppendL(TLiwGenericParam(KNullDesC8 , TLiwVariant((TInt32)transid1))) ; 
  
  
  LogInterface->ExecuteCmdL(CmdBuf1 , *inputlist , *outputlist ,KLiwOptCancel ); 
 
   
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


void Ctprovidertest ::  taddtest2L(void)
{
    TBuf<6> EmptyDes ;
    NotifyCB cb ;
   
 
   
    
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
   
     
	
  
    
 //First set the identity information
  TBufC8<20>CmdBufSet(KCmdRequestNotification) ;
  
  outputlist->Reset() ;
  
  inputlist->Reset() ;
  
  CLiwDefaultMap *EventDetails = CLiwDefaultMap :: NewL() ;
  
  
  EventDetails->InsertL(KDelayTime , TLiwVariant(TInt32(300000)) );
  TBufC16<10> contentType(KContentType) ;
 
   
   //Insert the contenttype to inputlist
   inputlist->AppendL(TLiwGenericParam(KNullDesC8 , TLiwVariant(contentType))) ;
 
  
  inputlist->AppendL(TLiwGenericParam(KFilter , TLiwVariant(EventDetails))) ;
  EventDetails->DecRef();
 
  
    
  LogInterface->ExecuteCmdL(CmdBufSet , *inputlist , *outputlist ,KLiwOptASyncronous, &cb);

  TInt index1 = 0 ;
   const TLiwGenericParam *transid = outputlist->FindFirst(index1 , KTransactionId) ;
  
  if(!transid)
    {
   
   	 User :: Leave(KErrArgument) ;
    }
  TInt32 transid1 = (transid->Value()).AsTInt32() ; 
  
  inputlist->Reset() ; outputlist->Reset() ;

    CLiwDefaultMap *add = CLiwDefaultMap :: NewL() ;
   add->InsertL(KEventTypeKey ,TLiwVariant((TInt32)0)) ;
  
   //Insert the contenttype to inputlist
   inputlist->AppendL(TLiwGenericParam(KContentTypeKey , TLiwVariant(contentType))) ;
 
   
  inputlist->AppendL(TLiwGenericParam(KEventDetails , TLiwVariant(add))) ;
   add->DecRef();
  CmdBufSet = KCmdAdd ;
  LogInterface->ExecuteCmdL(CmdBufSet , *inputlist , *outputlist ); 
  
  cb.Start();
    
    
  inputlist->Reset() ; outputlist->Reset() ;
  TBufC8<20>CmdBuf1(KCmdCancel) ;  
  inputlist->AppendL(TLiwGenericParam(KNullDesC8 , TLiwVariant((TInt32)transid1))) ; 
  
  
  LogInterface->ExecuteCmdL(CmdBuf1 , *inputlist , *outputlist ,KLiwOptCancel ); 
 
   
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

