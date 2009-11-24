/*
* Copyright (c) 2006-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Header file for location SAPI core implementation.
*
*/

#ifndef C_LOGINTERFACE_H
#define C_LOGINTERFACE_H

#include <liwcommon.h>
#include "serviceerrno.h"

/**
* Forward Declarations
*/
class CLoggingService ;

/**
* error message
*/

const TInt KMaxMsgSize = 256;
const TInt KMaxKeySize = 128;                                                                                                                                                                                                                                                                                     
_LIT( KInvalid, "Invalid" );
_LIT( KMissing, " Missing" );
_LIT( KMsgErr, "Logging:");
_LIT( KColon, ":");
_LIT8( KErrorMessage, "ErrorMessage");
_LIT( KErrLogCmdName, "Invalid commandName" );	
_LIT( KErrMissingCallback, "Missing Callback" );	
_LIT(KInterfaceMissing,"Logging: Interface name missing");


/**
* Content Type
*/
_LIT(KContentType , "Log") ;

/**
* ContentType Key
*/
_LIT8(KContentTypeKey , "Type") ;
/**
* Error Indntifier in Output parameter list
*/
_LIT8(KErrorCode , "ErrorCode") ; 


/**
* Operations on the IDatasource(Logging) interface
*/
_LIT8(KCmdAdd , "Add") ;
_LIT8(KCmdDelete , "Delete") ; 
_LIT8(KCmdGetList ,"GetList") ;
_LIT8(KCmdRequestNotification ,"RequestNotification") ;
_LIT8(KCmdCancel ,"Cancel") ;


/**
* Transaction id, which will be part of outparamlist for asynchronous request
*/
_LIT8(KTransactionId, "TransactionID"); 

/**
* Event map that contains the details of the event to be logged 
*/
_LIT8(KEventDetails , "Item") ;

/**
* Filter for getlist operation
*/
_LIT8(KFilter , "Filter") ; 

/**
* DelayInterval
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
* Key for the flags fields
*/
_LIT8(KFlagsKey , "LogFlags") ;

/**
* EndTime Key, for getlist filter
*/
_LIT8(KEndTimeKey , "EndTime") ;

/**
* Error Code
*/
_LIT8(KErrCode , "ErrorCode") ;

/**
* Key for RecentList for Filter 
*/
_LIT8(KRecentListKey , "RecentList") ; 

/**
* Key for id
*/
_LIT8(KLogId , "id") ;

/**
* Key for Data Map
*/
_LIT8(KData , "Data") ;

/**
* output returnvalue key
*/
_LIT8(KResponse,"ReturnValue");


/**
* Forward declarations
*/
class MLiwInterface ;
class CLogIter ;

/**
* This class provides the Calendar SAPI interface to LIW Framework 
*/
class CLoggingInterface : public CBase, public MLiwInterface
    {
    public :

        /**
        *Enums for position pased parsing
        */
        enum 
        {
        EIndex0 = 0 ,
        EIndex1 ,
        EIndex2 ,
        EIndex3 ,

        /**
        * Event Types
        */
        EKLogCallEventType  = 0,
        EKLogDataEventType , 
        EKLogFaxEventType ,
        EKLogShortMessageEventType ,
        EKLogPacketDataEventType ,
        EKEventTypeNotPresent =-1,
        /**
        * RecentList types 
        */
        EKLogNullRecentList = -1 ,
        EKLogRecentIncomingCalls = 1,
        EKLogRecentOutgoingCalls , 
        EKLogRecentMissedCalls ,
        

        /**
        * Event Status 
        */

        EStatusPending    = 0 ,                     
        EStatusSent,                    
        EStatusFalied,                  
        EStatusNone ,                  
        EStatusDone ,                  
        EStatusNotSent,                  
        EStatusScheduled,                 
        EStatusNotPresent =-1,
        /**
        * Event Flags
        */
        EKLogEventContactSearched  = 0 ,
        EKLogEventRead ,
        EFlagNotPresent =-1,

        /**
        * Direction flags
        */
        EIncomingEvent  = 0,
        EOutgoingEvent ,
        EIncomingEventAlternateline,                       
        EOutgoingEventAlternateline,                       
        EFetchedEvent ,                         
        EMissedEvent ,                         
        EMissedEventAlternateline,                     
        EDirectionNotPresent = -1,
        };

    public:
    
        /**
        * NewL: Two phased construction
        */
        static CLoggingInterface* NewL();

        /**
        * NewLC: Creates an instance of CLoggingServiceClass
        * Two Phased constructor
        * returns newly allocated object.
        */
        static CLoggingInterface* NewLC() ;

        /**
        * Destructor.
        */
        virtual ~CLoggingInterface(); 

        /**
        * ExecuteCmdL parses the input parameters and then calls an appropriate method on iLoggingServic
        *
        * @param aCmdName the name of the service command which the consumer wants to invoke
        * @param aInParamList the input parameter list, can be empty list
        * @param [in,out] aOutParamList the output parameter list, can be empty lis. The
        * service provider can use the output parameter list to fill in necessary return values
        * @param aCmdOptions Options for the command, see TLiwServiceCmdOptions in LiwCommon.hrh.
        * @param aCallback callback to be registered by consumer application
        *               
        * @see TLiwServiceCmdOptions
        * @see CLiwGenericParamList
        * @see MLiwNotifyCallback
        */

        virtual void ExecuteCmdL( const TDesC8& aCmdName,
                                  const CLiwGenericParamList& aInParamList,
                                  CLiwGenericParamList& aOutParamList,
                                  TUint aCmdOptions = 0,
                                  MLiwNotifyCallback* aCallback = 0 );
                                  
                                  
        /**
        * ConvertToSapiError function
        */                          
        static TInt ConvertToSapiError( TInt aSymbianErrorCode );
                
        /**
        * Closes the interface 
        */
        virtual void Close();
        
    protected:

        /**
        * ConstructL(): Internal method to construct members
        */
        void ConstructL() ;

        /**
        * Default constructor
        */
        CLoggingInterface() ;

        /**
        * Internal CmdExecute function which parses  the input parameters
        * this function is called by ExecuteCmdL() function 
        *
        * @param aCmdName the name of the service command which the consumer wants to invoke
        * @param aInParamList the input parameter list, can be empty list
        * @param [in,out] aOutParamList the output parameter list, can be empty lis. The
        * service provider can use the output parameter list to fill in necessary return values
        * @param aCmdOptions Options for the command, see TLiwServiceCmdOptions in LiwCommon.hrh.
        * @param aCallback callback to be registered by consumer application
        * @see TLiwServiceCmdOptions
        * @see CLiwGenericParamList
        * @see MLiwNotifyCallback
        *
        */

        void CmdExecuteL( const TDesC8& aCmdName,
                          const CLiwGenericParamList& aInParamList ,
                          CLiwGenericParamList& aOutParamList,
                          TUint aCmdOptions,
                          MLiwNotifyCallback* aCallback );

        /**
        * Internal utility method, used for Add from the core class
        *
        * @param aParam, input paramater containg the eventdetails. 
        * @param aCallback, callback address for notification requests.
        * @param aTransId, transaction id.
        */

        TInt32 AddEventL( const TLiwGenericParam *eventdetails ,
                          TUint& aTansId ,
                          TUint aCmdOptions, 
                          MLiwNotifyCallback *aCallBack = NULL ) ; 
                    
        /**
        * Internal utility method, used to getlist from the core class
        *
        * @param aFilter, filter for getlist on core class
        * @param aIter, Valure result argument(TransactionId for async calls) 
        * @param aCallback, callback method for async events
        */

        CLogIter*  GetListL( const TLiwGenericParam  *aFilter  , 
                             TUint& aTransId,
                             TUint aCmdOptions,
                             MLiwNotifyCallback  *aCallBack = NULL) ; 
                      
        /**
        * Internal utility method, used for notification registration
        *
        * @param aParam, input paramater containg the delay details/
        * @param aCallback, callback address for notification requests.
        * @param aTransId, transaction id.
        */
        TInt RequestNotificationsL( const TLiwGenericParam *aParam ,
                                    MLiwNotifyCallback *aCallback ,
        		                    TUint& aTransId,
        		                    TUint aCmdOptions ) ;

        /**
        * Internal utility method, used for Delete from the core class
        *
        * @param aParam, input paramater containg the logid 
        * @param aCallback, callback address for notification requests.
        * @param aTransId, transaction id.
        */
        	
        TInt DeleteEventL( const TLiwGenericParam *aParam,
                           TUint& aTansId,
                           TUint aCmdOptions,
                           MLiwNotifyCallback *aCallBack = NULL );
         
        /**
        * IncorrectValueL function
        */
        void IncorrectValueL( const TDesC8* aErrorArgument );

        /**
        * MissingValueL function
        */ 
        void MissingValueL( const TDesC8* aErrorArgument );   
                
        /**
        * CheckInputTypeL function
        */ 
        void CheckInputTypeL( const TLiwVariant* aSource,
                              LIW::TVariantTypeId aExpectedtype,
                              const TDesC8* aErrorArgument );  
 							
    private:

        /**
        * Handle to core location class for performing location operations
        */

        CLoggingService *iLogService ;
        
        /**
        * ErrorString
        */

        HBufC16* iErrorString;

    };


#endif //C_LOGINTERFACE_H