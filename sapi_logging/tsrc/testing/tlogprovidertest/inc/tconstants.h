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
 // Filter fields
#define ELogFirstFilterField 0x1
#define ELogContactField 0x1
#define ELogDirectionField 0x2
#define ELogDurationTypeField 0x4
#define ELogEventTypeField 0x8
#define ELogNumberField 0x10
#define ELogRemotePartyField 0x20
#define ELogStatusField 0x40
#define ELogStartTimeField 0x80
#define ELogEndTimeField 0x100
#define ELogFlagsField 0x200
#define ELogSubjectField 0x400
#define ELogLinkField 0x800
#define ELogDataField 0x1000
#define ELogLastFilterField 0x200
 
_LIT8(KDsInterfaceName , "IDataSource") ;
_LIT8(KLoggingContents , "Service.Logging") ;


/**
 * Error Indntifier in Output parameter list
 */
 _LIT8(KErrorCode , "ErrorCode") ; 
 

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
 _LIT8(KCmdRequestNotification ,"NotifyUpdates") ;
 _LIT8(KCmdCancel ,"Cancel") ;
  _LIT8(Kother ,"other") ;
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

_LIT8(KData, "Data");

 /**
  * Key for identifying the description in event map
  */
_LIT8(KDescriptionKey , "Description") ;

 _LIT8(KResponse,"ReturnValue");

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
       
   /*
const TUid  KLogCallEventType =  { 0x1000550D} ;   
 

const TUid KLogDataEventType ={0x10005566};
const TUid KLogFaxEventType ={0x10005567};
const TUid KLogShortMessageEventType ={0x10005568};
const TUid KLogMailEventType ={0x10005569};
const TUid KLogTaskSchedulerEventType = {0x1000585E};
const TUid KLogPacketDataEventType ={ 0x10008F8E};
const TUid KLogLbsSelfLocateEventType ={0x102822B2};
const TUid KLogLbsExternalLocateEventType ={0x102822B3};
const TUid KLogLbsTransmitLocationEventType= {0x102822B4};
const TUid KLogLbsNetworkLocateEventType ={0x102822B5};
const TUid KLogLbsAssistanceDataEventType ={0x102822B6};

 
*/






#endif 
 
     