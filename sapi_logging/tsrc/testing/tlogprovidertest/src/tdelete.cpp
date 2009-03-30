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

#include <LiwServiceHandler.h>
#include <LiwCommon.h>
#include <logcli.h>
#include <logwrap.h>
#include "tlogprovidertest.h"
#include "serviceerrno.h"
#include "tcallback.h"

 #include "tconstants.h"
#include "tfilterdetails.h"
 #include"teventdetails.h"
 
 
 
 _LIT8(KEventIdKey , "EventId");
 
 TInt deletetest1L(CEventDetails *aDetails)
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

	 
	 User :: Leave(KErrArgument) ;
	}
	
   MLiwInterface* LogInterface = (genericparm->Value()).AsInterface();
    
    
  TBufC8<20>CmdBufSet(KCmdAdd) ;
  
  outputlist->Reset() ;
  
  inputlist->Reset() ;
  
  CLiwDefaultMap *EventDetails = CLiwDefaultMap :: NewL() ;
  
  
  
  EventDetails->InsertL(KEventTypeKey , TLiwVariant(aDetails->GetEventType()) );
  
  
 if(((unsigned int)aDetails->GetDurationType()!=0))
 	{
 	EventDetails->InsertL(KEventDurationKey ,TLiwVariant((unsigned int)aDetails->GetDurationType()) );
 	}
    
 if(aDetails->GetContactType() !=0 )
 	{
 	EventDetails->InsertL(KContactidKey , TLiwVariant(aDetails->GetContactType()) );
 	}
    
 if((unsigned int)aDetails->GetLinkType()!=0)
 	{
 	EventDetails->InsertL(KLinkKey , TLiwVariant((unsigned int)aDetails->GetLinkType()) );
 	}
    
 if(aDetails->GetTimer() !=0 )
 	{
 	EventDetails->InsertL(KEventTimeKey , TLiwVariant(aDetails->GetTimer())) ;
 	}
    
   
  TBuf<10> EmptyDes ;
   
   
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
    
 if(aDetails->GetDescriptionType() != EmptyDes)
 	{
 	EventDetails->InsertL(KDescriptionKey , TLiwVariant(aDetails->GetDescriptionType())) ;
 	}
    
 if(aDetails->GetStatusType() >= 0  )
 	{
 	EventDetails->InsertL(KDeliveryStatusKey , TLiwVariant(aDetails->GetStatusType())) ;
 	}
    
  

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
   
   	 User :: Leave(KErrArgument) ;
    }
    
    
     
   TBufC<20> itemid = (genparm->Value()).AsDes() ;
    
    
    
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
  
  if(retval1 != SErrNone )
  	{
   
  	 User :: Leave(KErrArgument) ;
  	}
    
   
  

  
  
   
      LogInterface->Close() ;
     delete ServiceHandler;
    // delete crit;
   
   	 a.ResetAndDestroy();
   	 a.Close();
    
   
    } 
   
    

      
 

TInt deletetest1_0L(CEventDetails *aDetails)
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

	 
	 User :: Leave(KErrArgument) ;
	}
	
   MLiwInterface* LogInterface = (genericparm->Value()).AsInterface();
    
    
  TBufC8<20>CmdBufSet(KCmdAdd) ;
  
  outputlist->Reset() ;
  
  inputlist->Reset() ;
  
  CLiwDefaultMap *EventDetails = CLiwDefaultMap :: NewL() ;
  
  
  
  EventDetails->InsertL(KEventTypeKey , TLiwVariant(aDetails->GetEventType()) );
  
  
 if(((unsigned int)aDetails->GetDurationType()!=0))
 	{
 	EventDetails->InsertL(KEventDurationKey ,TLiwVariant((unsigned int)aDetails->GetDurationType()) );
 	}
    
 if(aDetails->GetContactType() !=0 )
 	{
 	EventDetails->InsertL(KContactidKey , TLiwVariant(aDetails->GetContactType()) );
 	}
    
 if((unsigned int)aDetails->GetLinkType()!=0)
 	{
 	EventDetails->InsertL(KLinkKey , TLiwVariant((unsigned int)aDetails->GetLinkType()) );
 	}
    
 if(aDetails->GetTimer() !=0 )
 	{
 	EventDetails->InsertL(KEventTimeKey , TLiwVariant(aDetails->GetTimer())) ;
 	}
    
   
  TBuf<10> EmptyDes ;
   
   
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
    
 if(aDetails->GetDescriptionType() != EmptyDes)
 	{
 	EventDetails->InsertL(KDescriptionKey , TLiwVariant(aDetails->GetDescriptionType())) ;
 	}
    
 if(aDetails->GetStatusType() >= 0  )
 	{
 	EventDetails->InsertL(KDeliveryStatusKey , TLiwVariant(aDetails->GetStatusType())) ;
 	}
    
  

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
   
   	 User :: Leave(KErrArgument) ;
    }
    
    
     
   TBufC<20> itemid = (genparm->Value()).AsDes() ;
    
    
    
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
  
  if(retval1 != SErrNone )
  	{
   
  	 User :: Leave(KErrArgument) ;
  	}
    
   
  
   
  
  //deleting twice
  
    LogInterface->ExecuteCmdL(CmdBuf , *inputlist , *outputlist) ;
  
  pos = 0 ;
  const TLiwGenericParam *Errprm1 = outputlist->FindFirst(pos , KErrCode ) ;
  
  if(!Errprm1)
  	{
   
  	 User :: Leave(KErrArgument) ;
  	}
  	
  TInt retval2  = Errprm1->Value().AsTInt32() ;
  
  if(retval2 != SErrNotFound )
  	{
   
  	 User :: Leave(KErrArgument) ;
  	}
  
  
  
  
  
  
  
   
      LogInterface->Close() ;
     delete ServiceHandler;
    // delete crit;
   
   	 a.ResetAndDestroy();
   	 a.Close();
    
   
    } 
   
    



TInt deletetest2L(CEventDetails *aDetails)
{
tcallback iCallback;

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
    
    
  TBufC8<20>CmdBufSet(KCmdAdd) ;
  
  outputlist->Reset() ;
  
  inputlist->Reset() ;
  
  CLiwDefaultMap *EventDetails = CLiwDefaultMap :: NewL() ;
  
  
  
  EventDetails->InsertL(KEventTypeKey , TLiwVariant(aDetails->GetEventType()) );
  
  
 if(((unsigned int)aDetails->GetDurationType()!=0))
 	{
 	EventDetails->InsertL(KEventDurationKey ,TLiwVariant((unsigned int)aDetails->GetDurationType()) );
 	}
    
 if(aDetails->GetContactType() !=0 )
 	{
 	EventDetails->InsertL(KContactidKey , TLiwVariant(aDetails->GetContactType()) );
 	}
    
 if((unsigned int)aDetails->GetLinkType()!=0)
 	{
 	EventDetails->InsertL(KLinkKey , TLiwVariant((unsigned int)aDetails->GetLinkType()) );
 	}
    
 if(aDetails->GetTimer() !=0 )
 	{
 	EventDetails->InsertL(KEventTimeKey , TLiwVariant(aDetails->GetTimer())) ;
 	}
    
   
  TBuf<10> EmptyDes ;
   
   
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
    
 if(aDetails->GetDescriptionType() != EmptyDes)
 	{
 	EventDetails->InsertL(KDescriptionKey , TLiwVariant(aDetails->GetDescriptionType())) ;
 	}
    
 if(aDetails->GetStatusType() >= 0  )
 	{
 	EventDetails->InsertL(KDeliveryStatusKey , TLiwVariant(aDetails->GetStatusType())) ;
 	}
    
  

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
   
   	 User :: Leave(KErrArgument) ;
    }
    
    
     
   TBufC<20> itemid = (genparm->Value()).AsDes() ;
    
    
    
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
 LogInterface->ExecuteCmdL(CmdBuf , *inputlist , *outputlist ,KLiwOptASyncronous, &iCallback) ;
  
  pos = 0 ;
  const TLiwGenericParam *Errprm = outputlist->FindFirst(pos , KErrCode ) ;
  
  if(!Errprm)
  	{
   
  	 User :: Leave(KErrArgument) ;
  	}
  	
  TInt retval1  = Errprm->Value().AsTInt32() ;
  
  if(retval1 != SErrNone )
  	{
   
  	 User :: Leave(KErrArgument) ;
  	}
    
   
   iCallback.Start() ;
   
      LogInterface->Close() ;
     delete ServiceHandler;
    // delete crit;
   
   	 a.ResetAndDestroy();
   	 a.Close();
    
   
    } 
   
    

      
 





















