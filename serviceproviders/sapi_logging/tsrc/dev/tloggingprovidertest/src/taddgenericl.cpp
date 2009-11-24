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

#define Sync 0
#define ASync 1

_LIT(KNull,"NULL");

void Ctprovidertest :: taddgenericL(CEventDetails *aDetails,TInt aParsedValue) 

{
   if(aParsedValue==Sync)
   {
    _LIT(KLog , "sync test case for add api") ;
  	 iLog->Log(KLog) ;
    taddsyncgenericL(aDetails);
   }
   
   else
   {
    _LIT(KLog , "async test case for add api") ;
  	 iLog->Log(KLog) ;
    taddasyncgenericL(aDetails);
   }
    
}

//-----------------------------------------------------------------------------
// Functionality test for add sync call
//-----------------------------------------------------------------------------

//const TBuf<KLogMaxSubjectLength> NullBuf ;


void Ctprovidertest :: taddsyncgenericL(CEventDetails *aDetails) 
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
    
    
   //First set the identity information
  TBufC8<20>CmdBufSet(KCmdAdd) ;
  
  outputlist->Reset() ;
  
  inputlist->Reset() ;
  
  CLiwDefaultMap *EventDetails = CLiwDefaultMap :: NewL() ;
  
  
  
  EventDetails->InsertL(KEventTypeKey , TLiwVariant(aDetails->GetEventType()) );
  
  
 if(aDetails->GetDurationType()!=0)
 	{
 	EventDetails->InsertL(KEventDurationKey ,TLiwVariant(aDetails->GetDurationType()) );
 	}
    
 if(aDetails->GetContactType() !=0 )
 	{
 	EventDetails->InsertL(KContactidKey , TLiwVariant(aDetails->GetContactType()) );
 	}
    
 if(aDetails->GetLinkType()!=0)
 	{
 	EventDetails->InsertL(KLinkKey , TLiwVariant(aDetails->GetLinkType()) );
 	}
    
 if(aDetails->GetTimer() !=0 )
 	{
 	EventDetails->InsertL(KEventTimeKey , TLiwVariant(aDetails->GetTimer())) ;
 	}
    
   
  TBuf<10> EmptyDes ;
   
   
   //if(ptr.Compare(KNull) )
   if(aDetails->GetSubjectType() != EmptyDes)
   	{
   	 EventDetails->InsertL(KSubjectKey , TLiwVariant(aDetails->GetSubjectType())) ;
   	}
    
   
   
 //if(aDetails->GetSubjectType().Compare(_LIT(NULL)) ) 
    
 if(aDetails->GetNumberType()!= EmptyDes)
 	{
 	EventDetails->InsertL(KPhoneNumberKey , TLiwVariant(aDetails->GetNumberType())) ;
 	}
    
 if(aDetails->GetRemotePartyType() != EmptyDes)
 	{
 	EventDetails->InsertL(KRemotePartyKey , TLiwVariant(aDetails->GetRemotePartyType())) ;
 	}
    
 if(aDetails->GetDirectionType() >= 0)
	 {
 	EventDetails->InsertL(KDirectionKey , TLiwVariant(aDetails->GetDirectionType())) ;
 	}
    
 if(aDetails->GetDescriptionType() != EmptyDes)
 	{
 	EventDetails->InsertL(KDescriptionKey , TLiwVariant(aDetails->GetDescriptionType())) ;
 	}
    
 if(aDetails->GetStatusType() >= 0 )
 	{
 	EventDetails->InsertL(KDeliveryStatusKey , TLiwVariant(aDetails->GetStatusType())) ;
 	}
 _LIT8(KData,"1234");   
 if(aDetails->GetDataType() != EmptyDes)
 	{
 	EventDetails->InsertL(KEventDataKey , TLiwVariant(KData)) ;
 	}    

  TBuf16 <10> Contents(KContentType) ;
  
  inputlist->AppendL(TLiwGenericParam(KContentTypeKey , TLiwVariant(Contents))) ;
  
  inputlist->AppendL(TLiwGenericParam(KEventDetails , TLiwVariant(EventDetails))) ;
  EventDetails->DecRef();
    
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
  	
  	    LogInterface->Close() ;
  	   delete ServiceHandler;
  	   a.ResetAndDestroy();
   	   a.Close();
    
      
    
  	 _LIT(KLog , "Functionality test of add call failed ") ;
  	 iLog->Log(KLog) ;
  	 User :: Leave(KErrArgument) ;
  	}
   
 /* if((ErrCode->Value().AsTInt32()) != KErrNone )
    {
    User :: Leave(ErrCode->Value().AsTInt32()) ;
    } */
  
  
  /** Log the event details to a file
   */
   
  index = 0 ;
  const TLiwGenericParam *genparm = outputlist->FindFirst(index , KResponse) ;
  
  if(!genparm)
    {
     _LIT8(KLog , "Log id of the added item not found") ;
   	 iLog->Log(KLog) ;
   	 User :: Leave(KErrArgument) ;
    }
   
   tlogresultsL(genparm , EAddEvent) ;
   
      LogInterface->Close() ;
     delete ServiceHandler;
    // delete crit;
   
   	 a.ResetAndDestroy();
   	 a.Close();
    
   
    

      
 }
 
 //-----------------------------------------------------------------------------
// Functionality test for add async call
//-----------------------------------------------------------------------------




void Ctprovidertest :: taddasyncgenericL(CEventDetails *aDetails) 
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
  TBufC8<20>CmdBufSet(KCmdAdd) ;
  
  outputlist->Reset() ;
  
  inputlist->Reset() ;
  
  CLiwDefaultMap *EventDetails = CLiwDefaultMap :: NewL() ;
  
  EventDetails->InsertL(KEventTypeKey , TLiwVariant(aDetails->GetEventType()) );
  
 if(aDetails->GetDurationType()!=0)
 	{	
 	EventDetails->InsertL(KEventDurationKey ,TLiwVariant(aDetails->GetDurationType()) );
 	}
    
 if(aDetails->GetContactType()!=0)
 	{
 	EventDetails->InsertL(KContactidKey , TLiwVariant(aDetails->GetContactType()) );
 	}
    
 if(aDetails->GetLinkType()!=0)
 	{
 	EventDetails->InsertL(KLinkKey , TLiwVariant(aDetails->GetLinkType()) );
 	}
    
 if(aDetails->GetTimer()!=0)
 	{
 	EventDetails->InsertL(KEventTimeKey , TLiwVariant(aDetails->GetTimer())) ;
 	}
    
 if(aDetails->GetSubjectType() != EmptyDes)
 	{
 	EventDetails->InsertL(KSubjectKey , TLiwVariant(aDetails->GetSubjectType())) ;
 	}
    
 if(aDetails->GetNumberType()!= EmptyDes)
 	{
 	EventDetails->InsertL(KPhoneNumberKey , TLiwVariant(aDetails->GetNumberType())) ;
 	}
    
 if(aDetails->GetRemotePartyType() != EmptyDes)
 	{
 	EventDetails->InsertL(KRemotePartyKey , TLiwVariant(aDetails->GetRemotePartyType())) ;
 	}
    
 if(aDetails->GetDirectionType() >= 0 )
 	{
 	EventDetails->InsertL(KDirectionKey , TLiwVariant(aDetails->GetDirectionType())) ;
 	}
    
 if(aDetails->GetDescriptionType() !=  EmptyDes)
 	{
 	EventDetails->InsertL(KDescriptionKey , TLiwVariant(aDetails->GetDescriptionType())) ;
 	}
    
 if(aDetails->GetStatusType()  >= 0)
 	{
 	EventDetails->InsertL(KDeliveryStatusKey , TLiwVariant(aDetails->GetStatusType())) ;
 	}
    
_LIT8(KData,"1234");   
 if(aDetails->GetDataType() != EmptyDes)
 	{
 	EventDetails->InsertL(KEventDataKey , TLiwVariant(KData)) ;
 	}    
  
//EventDetails->InsertL(KEventDataKey , TLiwVariant(true)) ;
  TBufC16<10> contentType(KContentType) ;
 // contentType.SetLengthL(3) ;
   
   //Insert the contenttype to inputlist
   inputlist->AppendL(TLiwGenericParam(KContentTypeKey , TLiwVariant(contentType))) ;
 
  
  inputlist->AppendL(TLiwGenericParam(KEventDetails , TLiwVariant(EventDetails))) ;
  EventDetails->DecRef();
 
  
    
  LogInterface->ExecuteCmdL(CmdBufSet , *inputlist , *outputlist ,KLiwOptASyncronous, &cb);

    
    
    
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
  	  LogInterface->Close() ;
  	   delete ServiceHandler;
  	   a.ResetAndDestroy();
   	   a.Close();
    
  	  
     _LIT(KLog , "Functionality test of delete call failed ") ;
  	 iLog->Log(KLog) ;
  	 User :: Leave(KErrArgument) ;
  	}
  	
  	
   

   
 /* if((ErrCode->Value().AsTInt32()) != KErrNone )
    {
    User :: Leave(ErrCode->Value().AsTInt32()) ;
    } */
  
  
 
    cb.Start();
   
   if(cb.Status() != KErrNone) 
 	{
 	 _LIT(KLog , "Async status error ") ;
 	 iLog->Log(KLog) ;
 	 User :: Leave (cb.Status()) ;
 	}
  
   
    // delete crit;
      LogInterface->Close() ;
    delete ServiceHandler;
      
   	 a.ResetAndDestroy();
   	 a.Close();
    
  
    
    
    
      
}


