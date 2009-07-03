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
#include "tfilterdetails.h"
#include "tprovidercallback.h"
#include "serviceerrno.h"

#define Sync 0
#define ASync 1

void Ctprovidertest :: tgetlistgenericPosL(CFilterDetails *aDetails,TInt aParsedValue) 

{
   if(aParsedValue==Sync)
   {
    _LIT(KLog , "sync test case for getlist api") ;
  	 iLog->Log(KLog) ;
    tgetlistsyncgenericPosL(aDetails);
   }
   
   else
   {
    _LIT(KLog , "async test case for getlist api") ;
  	 iLog->Log(KLog) ;
    tgetlistasyncgenericPosL(aDetails);
   }
    
}

//-----------------------------------------------------------------------------
// Functionality test for getlist sync call
//-----------------------------------------------------------------------------

void Ctprovidertest :: tgetlistsyncgenericPosL(CFilterDetails *aDetails) 
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
  
  
 TBuf <10> EmptyDes ;
 
    if(aDetails->GetEventId() != EmptyDes)
    {
     EventFilter->InsertL(KLogId , TLiwVariant(aDetails->GetEventId()) );   
    }
   
  if(aDetails->GetEventType() > -1)
    {
    EventFilter->InsertL(KEventTypeKey , TLiwVariant(aDetails->GetEventType()) );
    }
 
  if(aDetails->GetContactType()!=0)
  	{
  	EventFilter->InsertL(KContactidKey , TLiwVariant(aDetails->GetContactType()) );
  	}
    
  if((long)aDetails->GetTimer() !=0 )
  	{
  	EventFilter->InsertL(KEndTimeKey , TLiwVariant((long)aDetails->GetTimer())) ;	
  	}
    
  if(aDetails->GetNumberType() != EmptyDes)
  	{
  	EventFilter->InsertL(KPhoneNumberKey , TLiwVariant(aDetails->GetNumberType())) ;
  	}
    
  if(aDetails->GetRemotePartyType() != EmptyDes)
  	{
  	EventFilter->InsertL(KRemotePartyKey , TLiwVariant(aDetails->GetRemotePartyType())) ;
  	}
    
  if(aDetails->GetDirectionType() >= 0 ) 
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
  
  
   if(aDetails->GetAllEvent() == 1)
 	 {
     EventFilter->InsertL(KAllEvents , TLiwVariant(aDetails->GetAllEvent())) ;
 	 }
  
	TBufC16<10> contentType(KContentType) ;

	//Insert the contenttype to inputlist
	inputlist->AppendL(TLiwGenericParam(KNullDesC8 , TLiwVariant(contentType))) ;

  
  inputlist->AppendL(TLiwGenericParam(KPosItem , TLiwVariant(EventFilter))) ;
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
  	   LogInterface->Close() ;
  	   delete ServiceHandler;
 
      
   	 a.ResetAndDestroy();
   	 a.Close();
  	 _LIT(KLog , "Functionality test of add call failed ") ;
  	 iLog->Log(KLog) ;
  	 User :: Leave(KErrArgument) ;
  	}
  	
  	
  
  pos = 0 ;
  
  const TLiwGenericParam *LogIterParam = outputlist->FindFirst(pos , KResponse)  ;
  
  
  
//  CLiwIterable *LogIter = (LogIterParam->Value()).AsIterable() ;
  
   //LogIter->Reset();

  //  TLiwVariant var ; 
 tlogresultsL(LogIterParam , EGetList) ;

	
 
   LogInterface->Close() ;
   delete  ServiceHandler ;
   a.ResetAndDestroy() ;
   a.Close() ;
 
  
}

 //-----------------------------------------------------------------------------
// Functionality test for getlist async call
//-----------------------------------------------------------------------------




void Ctprovidertest :: tgetlistasyncgenericPosL(CFilterDetails *aDetails) 
{
    
     
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
	

	// set the identity information
    TBufC8<20>CmdBufSet(KCmdGetList) ;
    
    outputlist->Reset() ;
  
    inputlist->Reset() ;
  
    CLiwDefaultMap *EventFilter = CLiwDefaultMap :: NewL() ;
    
    
    TBuf<6> EmptyDes ;
   if(aDetails->GetEventId() != EmptyDes)
   {
    EventFilter->InsertL(KLogId , TLiwVariant(aDetails->GetEventId()) );
   }
    
    if(aDetails->GetEventType() > -1)
    {
    EventFilter->InsertL(KEventTypeKey , TLiwVariant(aDetails->GetEventType()) );
    }
    
  if(aDetails->GetContactType() != 0)
  	{
  	EventFilter->InsertL(KContactidKey , TLiwVariant(aDetails->GetContactType()) );
  	}
    
  if((long)aDetails->GetTimer() != 0)
  	{
  	EventFilter->InsertL(KEndTimeKey , TLiwVariant((long)aDetails->GetTimer())) ;
  	}
    
  if(aDetails->GetNumberType() != EmptyDes)
  	{
  	EventFilter->InsertL(KPhoneNumberKey , TLiwVariant(aDetails->GetNumberType())) ;
  	}
    
  if(aDetails->GetRemotePartyType() != EmptyDes)
  	{
  	EventFilter->InsertL(KRemotePartyKey , TLiwVariant(aDetails->GetRemotePartyType())) ;
  	}
    
  if(aDetails->GetDirectionType()  >=  0)
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
  
  
   if(aDetails->GetAllEvent() == 1)
 	 {
     EventFilter->InsertL(KAllEvents , TLiwVariant(aDetails->GetAllEvent())) ;
 	 }
  

	TBufC16<10> contentType(KContentType) ;

	//Insert the contenttype to inputlist
	inputlist->AppendL(TLiwGenericParam(KNullDesC8 , TLiwVariant(contentType))) ;

  
    inputlist->AppendL(TLiwGenericParam(KPosItem , TLiwVariant(EventFilter))) ;
    EventFilter->DecRef() ;
  
  
    LogInterface->ExecuteCmdL(CmdBufSet , *inputlist , *outputlist ,KLiwOptASyncronous , &cb);
  
  
     
  
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
  
  if(retval != SErrNone  )
  	{
  	 _LIT(KLog , "Functionality test of add call failed ") ;
  	 iLog->Log(KLog) ;
  	 User :: Leave(KErrArgument) ;
  	 
  	}
  	
    cb.Start();
   
   if(cb.Status() != KErrNone) 
 	{
 	 _LIT(KLog , "Async status error ") ;
 	 iLog->Log(KLog) ;
 	 User :: Leave (cb.Status()) ;
 	}
  	
  
 /* pos = 0 ;
  
  const TLiwGenericParam *LogIterParam = outputlist->FindFirst(pos , KLogIter)  ;
  
  CLiwIterable *LogIter = (LogIterParam->Value()).AsIterable() ;
  
  TLiwVariant var ; 
  LogIter->NextL(var) ;*/
    LogInterface->Close() ;
   delete ServiceHandler;
    // delete crit;
   
   	 a.ResetAndDestroy();
   	 a.Close();
   
    
}