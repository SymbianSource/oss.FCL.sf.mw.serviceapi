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
#include <e32std.h>
#include "tprovidertest.h"
#include "tconstants.h"




/**
 * Internal utility function for logging the results
 */


void Ctprovidertest ::  taddresultsL(const TLiwGenericParam *aGenericParam )
    {
    
      _LIT(KLogMsg , "Logging the add results ") ;
      iLog->Log(KLogMsg) ;
      
      TBuf<20> LogId = aGenericParam->Value().AsDes() ;
      //char Buff[10] ;
      
   //   sprintf(Buff , "%d" ,  (int)LogId) ;
   
      TBuf8<30> bufid;
      bufid.Append(LogId);
       
      
  //   TBuf8<20> buf((TUint8*) Buff) ;
     
     iLog->Log(bufid) ;
       
    }
    
    
/**
 * Internal utility function for logging the results
 */


void Ctprovidertest ::  tlogGetListL(const TLiwGenericParam *aGenericParam )
    {
    
      _LIT(KLogMsg , "Logging the GetList results ") ;
      iLog->Log(KLogMsg) ;
      
      
      CLiwIterable *LogIter = (aGenericParam->Value()).AsIterable() ;
      TLiwVariant mapvar ;
      
      TLiwVariant eventVars ;
     // LogIter->NextL(mapvar);
          
      //TInt K =0;
      
      LogIter->Reset();
      
      while(LogIter->NextL(mapvar))
        {
               _LIT(KLogMsg , "Logging the EventType results ") ;
           iLog->Log(KLogMsg) ;  
          const CLiwMap *eventDetails = mapvar.AsMap() ;
         
            if(eventDetails->FindL(KEventTypeKey , eventVars)) 
            {
              TInt32 eventtype =  eventVars.AsTInt32() ;
             // TInt32 val = eventtype.iUid ;
              
              //char Buff[20] ;
              
               TBuf8<256> buf;
              buf.Num(eventtype);
              
              
             // sprintf(Buff , "Event id %d" , (int)val) ;
              //TBuf8<20> buf((TUint8 *) Buff) ;
              iLog->Log(buf) ;
              eventVars.Reset();
              
            }
           if(eventDetails->FindL(KRemotePartyKey , eventVars)) 
            {
              TBufC<256> remoteparty=(eventVars.AsDes()) ;
              //remoteparty.Copy (eventVars.AsDes()) ;
              TBuf8<256> buf;
              buf.Copy(remoteparty);
               
             
              iLog->Log(buf) ;
              eventVars.Reset();
              
            }
            
            if(eventDetails->FindL(KEventDurationKey , eventVars)) 
            {
              _LIT(KLogMsg , "Logging the duration results ") ;
                iLog->Log(KLogMsg) ;
              TInt32 duration =  eventVars.AsTInt32() ;
             // char Buff[20] ;
              TBuf8<256> buf;
              buf.Num(duration);
             // sprintf(Buff , "duration %u" ,duration ) ;
              //TBuf8<20> buf((TUint8 *) Buff) ;
              iLog->Log(buf) ;
              eventVars.Reset();
              
            }
            
           /* if(eventDetails->FindL(KEventTimeKey , eventVars)) 
            {
              
              char Buff[20] ;
              TTime t1=eventVars.AsTTime();
              TBuf16<10> time;
              t1.FormatL(time,_L("%*C6"));
              sprintf(Buff , "Event id %s" , time) ;
              TBuf8<20> buf((TUint8 *) Buff) ;
              iLog->Log(buf) ;
              
              
            }
            
            if(eventDetails->FindL(KDeliveryStatusKey , eventVars)) 
            {
              TBufC<20> status(eventVars.AsDes()) ;
              
              char Buff[20] ;
              
              
              sprintf(Buff , "status %d" , status) ;
              TBuf8<20> buf((TUint8 *) Buff) ;
              iLog->Log(buf) ;
              
              
            }*/
            
            if(eventDetails->FindL(KSubjectKey , eventVars)) 
            {
              _LIT(KLogMsg , "Logging the subject results ") ;
               iLog->Log(KLogMsg) ;
              TBufC<256> subject=(eventVars.AsDes()) ;
              TBuf8<256> buf;
              buf.Copy(subject);
              
              iLog->Log(buf) ;
              eventVars.Reset();
              
            }
            
            if(eventDetails->FindL(KPhoneNumberKey , eventVars)) 
            {
              TBufC<256> number=(eventVars.AsDes()) ;
                             
              
              //sprintf(Buff , "number %d" ,number) ;
              TBuf8<256> buf;
              buf.Copy(number);
              iLog->Log(buf) ;
              eventVars.Reset();
              
            }
            
            if(eventDetails->FindL(KContactidKey , eventVars)) 
            {
              _LIT(KLogMsg , "Logging the contact results ") ;
                iLog->Log(KLogMsg) ;
              TInt32 contactid =  eventVars.AsTInt32() ;
              
              //char Buff[20] ;
              TBuf8<256> buf;
              buf.Num(contactid);
              
              
             // sprintf(Buff , "contact id %d" , contactid) ;
              //TBuf8<20> buf((TUint8 *) Buff) ;
              iLog->Log(buf) ;
              eventVars.Reset();
              
            }
            
            if(eventDetails->FindL(KDescriptionKey , eventVars)) 
            {
              TBufC<256> description=(eventVars.AsDes()) ;
              
                           
             
              TBuf8<256> buf ;
              buf.Copy(description);
              iLog->Log(buf) ;
              eventVars.Reset();
              
            }
            
            if(eventDetails->FindL(KLinkKey , eventVars)) 
            {
              TInt32 link =  eventVars.AsTInt32() ;
              
              //char Buff[20] ;
              
               TBuf8<256> buf;
               buf.Num(link);
              
              
             // sprintf(Buff , "link %u" ,link) ;
              //TBuf8<20> buf((TUint8 *) Buff) ;
              iLog->Log(buf) ;
              eventVars.Reset();
              
            }
            if(eventDetails->FindL(KDirectionKey , eventVars)) 
            {
              TInt32 direction =  eventVars.AsTInt32() ;
              
              //char Buff[20] ;
              
               TBuf8<256> buf;
               buf.Num(direction);
               
              
             // sprintf(Buff , "link %u" ,link) ;
              //TBuf8<20> buf((TUint8 *) Buff) ;
              iLog->Log(buf) ;
              eventVars.Reset();
              
            } 
            if(eventDetails->FindL(KDeliveryStatusKey , eventVars)) 
            {
              TInt32 status =  eventVars.AsTInt32() ;
              
              //char Buff[20] ;
              
               TBuf8<256> buf;
               buf.Num(status);
               
              
             // sprintf(Buff , "link %u" ,link) ;
              //TBuf8<20> buf((TUint8 *) Buff) ;
              iLog->Log(buf) ;
              eventVars.Reset();
              
            } 
            if(eventDetails->FindL(KLogId , eventVars)) 
            {
             // TInt32 id =  eventVars.AsTInt32() ;
               TBuf<20> id =  eventVars.AsDes() ;
              //char Buff[20] ;
              
               TBuf8<256> buf;
               buf.Append(id);
              
              
             // sprintf(Buff , "link %u" ,link) ;
              //TBuf8<20> buf((TUint8 *) Buff) ;
              iLog->Log(buf) ;
              eventVars.Reset();
              
            } 
            
            if(eventDetails->FindL(KEventDataKey , eventVars)) 
            {
              TBufC8<256> data=(eventVars.AsData()) ;
              
              TBuf8<256> buf ;
              buf.Copy(data);
              iLog->Log(buf) ;
              eventVars.Reset();
              
            }
            
            (const_cast<CLiwMap *>(eventDetails))->DecRef() ;
            
        mapvar.Reset(); 
        } 
       
        
       
        
       // eventVars.Reset();
       // mapvar.Reset();
       // LogIter->Reset();
        //LogIter->DecRef();
       
    }
     



/**
 * Internal utility function for logging the results
 */


void Ctprovidertest ::  tlogresultsL(const TLiwGenericParam *aGenericParam , TInt aRequestType)
    {
    
      switch (aRequestType)
        {
         case  EAddEvent :
            {
              taddresultsL(aGenericParam) ;  
            }
            break ;  
         
          case  EGetList :
            {
              tlogGetListL(aGenericParam) ;
            }
             break ; 
        }
       
    }
    