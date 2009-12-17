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


#ifndef TCONSTANTS_H
#define TCONSTANTS_H 
/**
 * InterfaceName ILogging
 * Contenttypes Service.Logging
 */
 
_LIT8(KDsInterfaceName , "IDataSource") ;
_LIT8(KLoggingContents , "Service.Logging") ;


/**
 * Error Indntifier in Output parameter list
 */
 _LIT8(KErrorCode , "ErrorCode") ; 
   _LIT8(KResponse,"ReturnValue");

/**
 * Content type
 */
 
 _LIT16(KContentType , "Log") ;
 
/**
 * Content Type Key
 */
 _LIT8(KContentTypeKey , "Type") ; 
/**
 * Operations on the IDatasource(Logging) interface
 */
 _LIT8(KCmdAdd , "Add") ;
_LIT8(KCmdDelete , "Delete") ; 
 _LIT8(KCmdGetList ,"GetList") ;
_LIT8(KCmdRequestNotification ,"RequestNotification") ;
 _LIT8(KCmdCancel ,"Cancel") ;
 /**
  * Position Item
  */
  _LIT8(KPosItem , "PosItem") ;
 
 
/**
 * Transaction id, which will be part of outparamlist for asynchronous request
 */
_LIT8(KTransactionId, "TransactionID"); 

/**
 * Event map that contains the details of the event to be logged 
 */
 
/**
 * Filter for getlist operation
 */
 _LIT8(KFilter , "Filter") ; 
 _LIT8(KEventDetails , "Item") ;
  _LIT8(KData , "Data") ;
 
 /**
  * DelayInterval....
  */
  _LIT8(KDelayTime , "DelayTime") ;
 
 /**
  * Key for identifying the type of the event in event map
  */
_LIT8(KEventTypeKey , "EventType") ;

 /**
  * Key for identifying the remote party in event map
  */
_LIT8(KRemotePartyKey , "RemoteParty") ;

 /**
  * Key for identifying the direction in event map
  */
_LIT8(KDirectionKey , "Direction") ;

 /**
  * Key for identifying the time in event map
  */
_LIT8(KEventTimeKey , "EventTime") ;

 /**
  * Key for identifying the duration in event map
  */
_LIT8(KEventDurationKey , "EventDuration") ;

 /**
  * Key for identifying the deliverystatus in event map
  */
_LIT8(KDeliveryStatusKey , "DeliveryStatus") ;

 /**
  * Key for identifying the subject in event map
  */
_LIT8(KSubjectKey , "Subject") ;


 /**
  * Key for identifying the phonenumber in event map
  */
_LIT8(KPhoneNumberKey , "PhoneNumber") ;


 /**
  * Key for identifying the contactid in event map
  */
_LIT8(KContactidKey , "Contactid") ;



 /**
  * Key for identifying the description in event map
  */
_LIT8(KDescriptionKey , "Description") ;



 /**
  * Key for identifying the eventdata in event map
  */
_LIT8(KEventDataKey , "EventData") ;



 /**
  * Key for identifying the link in event map
  */
_LIT8(KLinkKey , "Link") ;

/**
 * EndTime Key, for getlist filter
 */
 _LIT8(KEndTimeKey , "EndTime") ;
 
 
 
/**
* Key for the flags fields
*/
_LIT8(KFlagsKey , "LogFlags") ;

/**
* Liwiterator key in outparamlist
*/
_LIT8(KLogIter , "Iterator") ;

/**
* Error Code
*/
_LIT8(KErrCode , "ErrorCode") ;

/**
* Keys for the filter input paramater for getlist api
*/
_LIT8(KAllEvents , "All") ;

 /**
  * Key for RecentList for Filter 
  */
  _LIT8(KRecentListKey , "RecentList") ; 
  
  _LIT8(KLogId , "id") ;
  

  
 
 enum RequestType
    {
        EAddEvent ,
        EGetList ,
    }; 
  
 enum EeventType
    {
        KCallEvent ,
        KLogDataEvent,
        KLogFaxEvent,
        KLogShortMessageEvent,
        KLogMailEvent,
        KLogTaskSchedulerEvent,
        KLogPacketDataEvent,
        KLogLbsSelfLocateEvent,
        KLogLbsExternalLocateEvent,
        KLogLbsTransmitLocationEvent,
        KLogLbsNetworkLocateEvent,
        KLogLbsAssistanceDataEvent,
      
     }; 
       
const TInt KLogMaxRemotePartyLength = 64;
const TInt KLogMaxDirectionLength = 64;
const TInt KLogMaxStatusLength = 64;
const TInt KLogMaxSubjectLength = 64;
const TInt KLogMaxDescriptionLength = 64;
const TInt KLogMaxSharedStringLength = 64;
const TInt KLogMaxNumberLength = 100;

#endif 
 
     