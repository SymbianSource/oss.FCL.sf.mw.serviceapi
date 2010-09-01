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

//#include "teventdetails.h"
#include "tconstants.h"
#include "tfilterdetails.h"
//#include <liwlogiter.h>


 

_LIT8(KEventIdKey , "EventId");

  
 



//sms macros

  
  
  TInt getlist1L(CFilterDetails *aDetails)
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
	
	


    TBufC8<20>CmdBufSet(KCmdGetList) ;
    
    outputlist->Reset() ;
  
    inputlist->Reset() ;
  
    CLiwDefaultMap *EventFilter = CLiwDefaultMap :: NewL() ;
    
    EventFilter->InsertL(KEventIdKey , TLiwVariant(aDetails->GetEventId()) );
 
    EventFilter->InsertL(KEventTypeKey , TLiwVariant(aDetails->GetEventType()) );
  
  if(aDetails->GetContactType()!=0)
  	{
  	EventFilter->InsertL(KContactidKey , TLiwVariant(aDetails->GetContactType()) );
  	}
  
       
  if((long)aDetails->GetTimer()!=0)
  	{
  	EventFilter->InsertL(KEndTimeKey , TLiwVariant((long)aDetails->GetTimer())) ;
  	}
    
    TBuf<6> EmptyDes ;
    
  if(aDetails->GetNumberType() != EmptyDes)
  	{
  	EventFilter->InsertL(KPhoneNumberKey , TLiwVariant(aDetails->GetNumberType())) ;
  	}
    
  if(aDetails->GetRemotePartyType() != EmptyDes)
  	{
  	EventFilter->InsertL(KRemotePartyKey , TLiwVariant(aDetails->GetRemotePartyType())) ;
  	}
    
    
  if(aDetails->GetDirectionType() >= 0)
  	{
  	EventFilter->InsertL(KDirectionKey , TLiwVariant(aDetails->GetDirectionType())) ;
  	}
    
  if(aDetails->GetStatusType() >= 0)
  	{
  	EventFilter->InsertL(KDeliveryStatusKey , TLiwVariant(aDetails->GetStatusType())) ;
  	}
    
  if(aDetails->GetRecentList() != 0)
  	{  
    EventFilter->InsertL(KRecentListKey , TLiwVariant(aDetails->GetRecentList())) ;
  	}
 if(aDetails->GetAllEvent()!=0)
 {
  EventFilter->InsertL(KAllEvents , TLiwVariant(aDetails->GetAllEvent())) ;
 }
  
  
	TBufC<10> contentType(KContentType) ;

 	inputlist->AppendL(TLiwGenericParam(KContentTypeKey , TLiwVariant(contentType))) ;

  
  inputlist->AppendL(TLiwGenericParam(KFilter , TLiwVariant(EventFilter))) ;
  EventFilter->DecRef() ;
  
   
   
  /* TInt Index = 0 ;
     const TLiwGenericParam *contentType1 = inputlist->FindFirst(Index , KContentTypeKey) ;
     
     if(Index == KErrNotFound)
     	{
     	
     	   //contentType1  = inputlist->Value().AsTInt32() ;
     //	 contentType1 = &(inputlist[0]) ;
     	 
     	}
     
     TPtrC content = (contentType1->Value()).AsDes() ;
     	 
     	 if(content.CompareF(KContentType))
     	 	{
     	 	 User :: Leave(KErrArgument) ;
     	 	}	
      	*/
  
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
   
  	 User :: Leave(KErrArgument) ;
  	}
  	
  	
  
  pos = 0 ;
  
  const TLiwGenericParam *LogIterParam = outputlist->FindFirst(pos , KResponse)  ;
  
  
 
 CLiwIterable *LogIter = (LogIterParam->Value()).AsIterable() ;
 
	 if(!LogIter)
	 	{
	  
	 	 User :: Leave (KErrGeneral) ;
	 	}
	 	
//TLiwVariant   Events ;
//TLiwVariant   EventDetails ;
	 
//	 CLiwLogIter  *x  = NULL; 
	 
	// x->CountL();

//	 CountL();
	
	
 
	 
	// TRAPD(ret,LogIter->NextL(EventDetails));
	 
	 /*while(LogIter->NextL(EventDetails))
	 {
	 	 const CLiwMap *eventDetails = EventDetails.AsMap() ;
  	 
	 	 if(eventDetails->FindL(KLogId , Events) == KErrNotFound)
	 	 	{
	 	  
	 	 	 User :: Leave(KErrArgument) ;
	 	 	}
	 	 
	 	 
	 	 
	 	 TInt32 eventid =  Events.AsTInt32() ;
	 	 
	 	 inputlist->Reset() ;
	 	 
	 	 inputlist->AppendL(TLiwGenericParam(KContentTypeKey , TLiwVariant(KContentType))) ;
	 	 inputlist->AppendL(TLiwGenericParam(KLogId , TLiwVariant(eventid))) ;
	 	 
	 	 
	 	 LogInterface->ExecuteCmdL(CmdBufSet , *inputlist , *outputlist ) ;
	 	 
	 	 (const_cast<CLiwMap *>(eventDetails))->DecRef() ;
	 	 delete eventDetails;
	 	}*/
	 

   
  inputlist->Reset() ; outputlist->Reset() ;
  
   
   //Insert the contenttype to inputlist
  // inputlist->AppendL(TLiwGenericParam(KContentTypeKey , TLiwVariant(contentType))) ;
 
   
  //inputlist->AppendL(TLiwGenericParam(KLogId , TLiwVariant((TInt32)item))) ;
  
 // CmdBuf = KCmdDelete ;
  
 // LogInterface->ExecuteCmdL(_L8("Delete") , *inputlist , *outputlist) ;
  
	 
	 	 
	 	 
	 // TInt itemid = (outparm1->Value()).AsTInt32() ;
	 
	 
	 
//	LogIter->Reset();
	 
//	 delete eventDetails;
 
// delete LogIter;
 //delete eventDetails;
 
 
   LogInterface->Close() ;
   delete  ServiceHandler ;
   a.ResetAndDestroy() ;
   a.Close() ;
 
   return 0;  
}


















  TInt getlist2L(CFilterDetails *aDetails)
{
   tcallback icallback;
  
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
	
	


    TBufC8<20>CmdBufSet(KCmdGetList) ;
    
    outputlist->Reset() ;
  
    inputlist->Reset() ;
  
    CLiwDefaultMap *EventFilter = CLiwDefaultMap :: NewL() ;
    
    EventFilter->InsertL(KEventIdKey , TLiwVariant(aDetails->GetEventId()) );
 
    EventFilter->InsertL(KEventTypeKey , TLiwVariant(aDetails->GetEventType()) );
  
  if(aDetails->GetContactType()!=0)
  	{
  	EventFilter->InsertL(KContactidKey , TLiwVariant(aDetails->GetContactType()) );
  	}
  
       
  if((long)aDetails->GetTimer()!=0)
  	{
  	EventFilter->InsertL(KEndTimeKey , TLiwVariant((long)aDetails->GetTimer())) ;
  	}
    
    TBuf<6> EmptyDes ;
    
  if(aDetails->GetNumberType() != EmptyDes)
  	{
  	EventFilter->InsertL(KPhoneNumberKey , TLiwVariant(aDetails->GetNumberType())) ;
  	}
    
  if(aDetails->GetRemotePartyType() != EmptyDes)
  	{
  	EventFilter->InsertL(KRemotePartyKey , TLiwVariant(aDetails->GetRemotePartyType())) ;
  	}
    
    
  if(aDetails->GetDirectionType() >= 0)
  	{
  	EventFilter->InsertL(KDirectionKey , TLiwVariant(aDetails->GetDirectionType())) ;
  	}
    
  if(aDetails->GetStatusType() >= 0)
  	{
  	EventFilter->InsertL(KDeliveryStatusKey , TLiwVariant(aDetails->GetStatusType())) ;
  	}
    
  if(aDetails->GetRecentList() != 0)
  	{   
    EventFilter->InsertL(KRecentListKey , TLiwVariant(aDetails->GetRecentList())) ;
  	}
 // EventFilter->InsertL(KRecentListKey , TLiwVariant(aDetails->GetAllEvent())) ;
  
  
	TBufC<10> contentType(KContentType) ;

 	inputlist->AppendL(TLiwGenericParam(KContentTypeKey , TLiwVariant(contentType))) ;

  
  inputlist->AppendL(TLiwGenericParam(KFilter , TLiwVariant(EventFilter))) ;
  EventFilter->DecRef() ;
  
   
   
  /* TInt Index = 0 ;
     const TLiwGenericParam *contentType1 = inputlist->FindFirst(Index , KContentTypeKey) ;
     
     if(Index == KErrNotFound)
     	{
     	
     	   //contentType1  = inputlist->Value().AsTInt32() ;
     //	 contentType1 = &(inputlist[0]) ;
     	 
     	}
     
     TPtrC content = (contentType1->Value()).AsDes() ;
     	 
     	 if(content.CompareF(KContentType))
     	 	{
     	 	 User :: Leave(KErrArgument) ;
     	 	}	
      	*/
  
  LogInterface->ExecuteCmdL(CmdBufSet , *inputlist , *outputlist,KLiwOptASyncronous,&icallback ); 
  
  
  
  
   TInt index = 0 ;
   
   const TLiwGenericParam *ErrCode  = outputlist->FindFirst(index , KErrCode) ;
   
   if(!ErrCode )
    {
    
  	 User :: Leave(KErrArgument) ;
    }
    
    TInt retval  = ErrCode->Value().AsTInt32() ;
  
  if(retval != SErrNone )
  	{
   
  	 User :: Leave(KErrArgument) ;
  	}
  	
  icallback.Start();	
  
 /* pos = 0 ;
  
  const TLiwGenericParam *LogIterParam = outputlist->FindFirst(pos , KLogIter)  ;
  
  
 
 CLiwIterable *LogIter = (LogIterParam->Value()).AsIterable() ;
 

TLiwVariant   Events ;
TLiwVariant   EventDetails ;
	 
//	 CLiwLogIter  *x  = NULL; 
	 
	// x->CountL();

//	 CountL();
	// CmdBufSet = KCmdDelete ;
	 
	 while(LogIter->NextL(EventDetails))
	 {
	 	 const CLiwMap *eventDetails = EventDetails.AsMap() ;
	 	 
	 	 if(eventDetails->FindL(KLogId , Events) == KErrNotFound)
	 	 	{
	 	 	 
	 	 	 User :: Leave(KErrArgument) ;
	 	 	}
	 	 	
	 	 
	 	 /*	 if(eventDetails->FindL(KContactidKey , Events) == KErrNotFound)
	 	 	{
	 	 	 
	 	 	 User :: Leave(KErrArgument) ;
	 	 	}
	 
	 delete eventDetails;	 
	
	
	 }
	 
	 TInt32 item = Events.AsTInt32();
	 	 
	 	 
	 	 
	 
	 
	 
	 
	LogIter->Reset();*/
	 
//	 delete eventDetails;
 
// delete LogIter;
 //delete eventDetails;
 
 
   LogInterface->Close() ;
   delete  ServiceHandler ;
   a.ResetAndDestroy() ;
   a.Close() ;
 
   return 0;  
}








 





 

 





 