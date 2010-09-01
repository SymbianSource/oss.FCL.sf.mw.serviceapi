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

#include <liwservicehandler.h>
#include <liwcommon.h>
#include <logcli.h>
#include <logwrap.h>
#include "tlogprovidertest.h"
#include "serviceerrno.h"
#include "tcallback.h"
#include "teventdetails.h"
#include "tconstants.h"

_LIT8(KIMDataSource,		"IMessaging");
  _LIT8(KService, 		"Service.Messaging");
  
  TInt wronginterface1(CEventDetails *aDetails)
{


	CLiwServiceHandler* ServiceHandler = CLiwServiceHandler::NewL();
     // Input and output parameter list
    CLiwGenericParamList* inputlist = &(ServiceHandler->InParamListL());
    
    CLiwGenericParamList* outputlist = &(ServiceHandler->OutParamListL());
    
    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIMDataSource , KService) ;
    
    crit->SetServiceClass(TUid::Uid(KLiwClassBase));
    
    RCriteriaArray a;
    
	
	a.AppendL(crit);
 	
	ServiceHandler->AttachL(a) ;
	
	
	TRAPD(err,ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist));
	 
 	

	
    TInt pos = 0;
	
 
	const TLiwGenericParam *genericparm = outputlist->FindFirst(pos  , KIMDataSource);
	
	if(!genericparm)
	{
	  outputlist->Reset() ;
  
  inputlist->Reset() ;
	 a.Close();
	 delete crit;
delete ServiceHandler;
	 
	 User :: Leave(KErrArgument) ;
	}
	
   MLiwInterface* LogInterface = (genericparm->Value()).AsInterface();
    
    
  TBufC8<20>CmdBufSet(KCmdAdd) ;
  
  outputlist->Reset() ;
  
  inputlist->Reset() ;
  
  CLiwDefaultMap *EventDetails = CLiwDefaultMap :: NewL() ;
  
  
  
  EventDetails->InsertL(KEventTypeKey , TLiwVariant(aDetails->GetEventType()) );
  
  
  
  

  TBuf16 <10> Contents(KContentType) ;
  
  inputlist->AppendL(TLiwGenericParam(KContentTypeKey , TLiwVariant(Contents))) ;
  
  inputlist->AppendL(TLiwGenericParam(KEventDetails , TLiwVariant(EventDetails))) ;
  
  EventDetails->DecRef();
    
  LogInterface->ExecuteCmdL(CmdBufSet , *inputlist , *outputlist ); 
 
  
  
  
   TInt index = 0 ;
   
   const TLiwGenericParam *ErrCode  = outputlist->FindFirst(index , KErrCode) ;
   
   if(!ErrCode )
    {
    
  	 User :: Leave(KErrArgument) ;
    }
    
    TInt retval  = ErrCode->Value().AsTInt32() ;
  
  if(retval != SErrNone )
  	{
  	
  	    LogInterface->Close() ;
  	   delete ServiceHandler;
  	   a.ResetAndDestroy();
   	   a.Close();
    
      
    
  	 User :: Leave(KErrArgument) ;
  	}
   
 
  
   
  index = 0 ;
  const TLiwGenericParam *genparm = outputlist->FindFirst(index , KResponse) ;
  
  if(!genparm)
    {
      LogInterface->Close() ;
     delete ServiceHandler;
    // delete crit;
   
   	 a.ResetAndDestroy();
   	 a.Close();
   
   
   return KErrArgument;
   	 //User :: Leave(KErrArgument) ;
    }
    
    
     
    
    
   
      LogInterface->Close() ;
     delete ServiceHandler;
    // delete crit;
   
   	 a.ResetAndDestroy();
   	 a.Close();
   
   return 0;   
    }






 TInt loadtwice(CEventDetails *aDetails)
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
	 ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist);
 	

	
    TInt pos = 0;
	
 
	const TLiwGenericParam *genericparm = outputlist->FindFirst(pos  , KDsInterfaceName);
	
	if(!genericparm)
	{

	 
	 User :: Leave(KErrArgument) ;
	}
	
   MLiwInterface* LogInterface = (genericparm->Value()).AsInterface();
    
    
  TBufC8<20>CmdBufSet(KCmdAdd) ;
  
  outputlist->Reset() ;
  
  inputlist->Reset() ;
  
  CLiwDefaultMap *EventDetails = CLiwDefaultMap :: NewL() ;
  
  
  
  EventDetails->InsertL(KEventTypeKey , TLiwVariant(aDetails->GetEventType()) );
  
  
  
  

  TBuf16 <10> Contents(KContentType) ;
  
  inputlist->AppendL(TLiwGenericParam(KContentTypeKey , TLiwVariant(Contents))) ;
  
  inputlist->AppendL(TLiwGenericParam(KEventDetails , TLiwVariant(EventDetails))) ;
  
  EventDetails->DecRef();
    
  LogInterface->ExecuteCmdL(CmdBufSet , *inputlist , *outputlist ); 
 
  
  
  
   TInt index = 0 ;
   
   const TLiwGenericParam *ErrCode  = outputlist->FindFirst(index , KErrCode) ;
   
   if(!ErrCode )
    {
    
  	 User :: Leave(KErrArgument) ;
    }
    
    TInt retval  = ErrCode->Value().AsTInt32() ;
  
  if(retval != SErrNone )
  	{
  	
  	    LogInterface->Close() ;
  	   delete ServiceHandler;
  	   a.ResetAndDestroy();
   	   a.Close();
    
      
    
  	 User :: Leave(KErrArgument) ;
  	}
   
 
  
   
  index = 0 ;
  const TLiwGenericParam *genparm = outputlist->FindFirst(index , KResponse) ;
  
  if(!genparm)
    {
      LogInterface->Close() ;
     delete ServiceHandler;
    // delete crit;
   
   	 a.ResetAndDestroy();
   	 a.Close();
   
   
   return KErrArgument;
   	 //User :: Leave(KErrArgument) ;
    }
    
    
     
    
    
   
      LogInterface->Close() ;
     delete ServiceHandler;
    // delete crit;
   
   	 a.ResetAndDestroy();
   	 a.Close();
   
      return 0;   
    }





 TInt wrongcommand(CEventDetails *aDetails)
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
	// ServiceHandler->ExecuteServiceCmdL(*crit, *inputlist, *outputlist);
 	

	
    TInt pos = 0;
	
 
	const TLiwGenericParam *genericparm = outputlist->FindFirst(pos  , KDsInterfaceName);
	
	if(!genericparm)
	{

	 
	 User :: Leave(KErrArgument) ;
	}
	
   MLiwInterface* LogInterface = (genericparm->Value()).AsInterface();
    
    
  TBufC8<20>CmdBufSet(Kother) ;
  
  outputlist->Reset() ;
  
  inputlist->Reset() ;
  
  CLiwDefaultMap *EventDetails = CLiwDefaultMap :: NewL() ;
  
  
  
  EventDetails->InsertL(KEventTypeKey , TLiwVariant(aDetails->GetEventType()) );
  
  
  
  

  TBuf16 <10> Contents(KContentType) ;
  
  //inputlist->AppendL(TLiwGenericParam(KContentTypeKey , TLiwVariant(Contents))) ;
  
  inputlist->AppendL(TLiwGenericParam(KEventDetails , TLiwVariant(EventDetails))) ;
  
  EventDetails->DecRef();
    
  LogInterface->ExecuteCmdL(CmdBufSet , *inputlist , *outputlist ); 
 
  
  
  
   TInt index = 0 ;
   
   const TLiwGenericParam *ErrCode  = outputlist->FindFirst(index , KErrCode) ;
   
   if(!ErrCode )
    {
    
  	 User :: Leave(KErrArgument) ;
    }
    
    TInt retval  = ErrCode->Value().AsTInt32() ;
  
  if(retval != SErrServiceNotSupported )
  	{
  	
    
  	 User :: Leave(KErrArgument) ;
  	}
   
 
  
    
     
    
    
   
      LogInterface->Close() ;
     delete ServiceHandler;
    // delete crit;
   
   	 a.ResetAndDestroy();
   	 a.Close();
   
   return 0;   
    }






