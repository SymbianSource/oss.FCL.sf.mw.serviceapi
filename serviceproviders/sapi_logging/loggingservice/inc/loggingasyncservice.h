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
* Description:  Includes logging asynchronous core class methods.
*
*/

#ifndef LOGGINGASYNCSERVICE_H
#define LOGGINGASYNCSERVICE_H

#include <e32base.h>
#include <logcli.h>
#include <logview.h>
#include <f32file.h>
#include <logwrap.h>

enum
    {
    EAddEvent ,
    EAddEventType,
    EDeleteEvent ,
    EReadEvents ,
    ESleep ,
    EGetRecent ,
    ENotification ,
    EGetEvent,
    EErrorEvent,
    };

/**
* Forward Declaration
*/

class MLoggingCallback ;
class CLogsEvent    ;
class CLogsFilter   ;
class CLogIter      ;

/**
* Core class which deals with all the async methods
*/

class CLogAsyncService : public CActive
    {
    public:

        /**
        * NewL: Two phased construction
        */

        IMPORT_C static CLogAsyncService*  NewL( MLoggingCallback* aCallback = NULL ) ;

        /**
        * NewLC: Creates an instance of CLogSyncServiceClass
        * Two Phased constructor
        * returns newly allocated object.
        */

        static CLogAsyncService*  NewLC( MLoggingCallback* aCallback ) ;

        /**
        * Async AddEvent function. adds an Event asynchronously
        * do event database
        * @param aEvent, details of the event to be added to the
        * event database
        */

        IMPORT_C void AddL( TUint aTransId ,CLogEvent* aEvent ) ;

       /**
        * Deletes a event from the event database
        * @param aLogId Event id of the event in the database
        * @param aFilter, search criteria for this event in event database
        */

        IMPORT_C void Delete( TUint aTransId , TLogId aLogId ) ;

        /**
        * Gets the Events list asynchronously
        * @param aFilter: Query Criteria
        * @param aCallback: callback address
        */

        IMPORT_C void GetListL( TUint aTransId , CLogFilter *aFilter ) ;

        /**
        * Read recent Events from the database
        *
        * @param Transaction id of the async event
        * @param RecentList
        * @param Filter for events to appear in the view.
        */

        TBool ReadRecentEventsL( TUint aTransId , 
                                 TLogRecentList aRecentList ,
                                 const CLogFilter *aFilter = NULL ) ;

        /**
        * Notify Update: Notifies the updates happening to
        * logdatabase.
        *
        * @param aDelay, minium duration for reciving the updates
        */

        IMPORT_C void NotifyUpdates( TUint aTransId ,TTimeIntervalMicroSeconds32 aDelay ) ;

        /**
        * Gets the details of the event, as specified by the input
        * paramater
        *
        * @param, Transactoin id of the  asynchronous event
        * @param, details of the event to be fetched from the database
        */

        IMPORT_C void GetEventL( TUint aTransId , CLogEvent* aEvent ) ;

        /**
        * SetInterval function
        */

        inline void SetInterval( TTimeIntervalMicroSeconds32 aInterval )
            {
            iInterval = aInterval ;
            }
        /**
        * Sets the boolean flag iFlagCancel
        */        
        inline void SetCancelFlag(TBool aValue) 
            {
            iFlagCancel = aValue;
            }
        
        /**
        * Default Desturctor
        */

        ~CLogAsyncService() ;


    protected :

        /**
        * Protected constructor
        */

        CLogAsyncService() ;

        /**
        * ConstructL Method to construct the class members
        */

        void ConstructL(MLoggingCallback* aCallback) ;

        /**
        * DoInitalise Method to intalise the class members
        */

        void DoInitialiseL() ;

        /**
        * From CActive
        */

        void DoCancel() ;

        /**
        * From CActive
        */

        void RunL() ;

        /**
        * RunCmL method
        */

        void RunCmdL() ;


    private :

        /**
        * Members of AsyncService Class
        */

        CLogClient*        iLogClient ;
        MLoggingCallback*  iCallback ;
        TUint               iTransId ;
        CLogsEvent         *iUpdatedEvent ;
        CLogIter*          iIter ;
        TInt               iTask ;
        RFs                iFs ;
        TTimeIntervalMicroSeconds32 iInterval ;
        CLogViewEvent* iLogViewEvent;
        CLogFilter* iFilter;
		TBool              iFlagCancel;

    };

/**
* Notify Callback class, used to get notifications for async events
*/

class MLoggingCallback
    {

    public :

        /**
        * HandleNotifyL , generic method to get updates on the async
        * methods
        * @param aTransId , Transaction id
        * @param aStatus
        * @param iter , Logging iterator
        */
        virtual void HandleNotifyL(TUint aTransid ,TUint aStatus , CLogIter *iter ) = 0 ;
		
        /**
        * HandleReqeustL , method to get output on notification
        * methods
        * @param aTransId , Transaction id
        * @param aStatus
        * @param aLogEvent , event containing the output
        */
        virtual void HandleReqeustL(TUint aTransid, TUint aStatus, CLogsEvent *aLogEvent) = 0;

        /**
        * CancelNotifyL , generic method to get updates on the async
        * methods
        *
        * @param aTransId , Transaction id
        * @param aFlag, Flag for notification to LiwBinding
        */

        virtual void CancelNotifyL(TUint aTransid ,TBool aFlag) = 0 ;

        /**
        * Default Desturctor
        */

        virtual ~MLoggingCallback()
        {
        ;
        }

    } ;

/**
 * Utility class for waiting for asychronous requests
*/
class CAsyncWaiter : public CActive
    {
public:
    /**
     * Two-phased constructor.
     * @param aPriority  set aPriority to  EPriorityStandard
     * @return CAsyncWaiter object
    */
    static CAsyncWaiter* NewL( TInt aPriority = EPriorityStandard );
    static CAsyncWaiter* NewLC( TInt aPriority = EPriorityStandard );
    /**
     * Destructor.
    */
    ~CAsyncWaiter();
    
    /**
     * Starts the active scheduler.
    */
    void StartAndWait();
    /**
     * Starts the active scheduler.
    */
    TInt Result() const;
    
private:
    
    /** 
     * Constructor.
     * @param aPriority 
    */
    CAsyncWaiter( TInt aPriority );
    
    /**
     * Inherited from CActive class 
    */
    void RunL();
    
    /**
     * Inherited from CActive class 
    */
    void DoCancel();
    
private:
    
    /**
     * wait scheduler
     */
    CActiveSchedulerWait iWait;
    
    /**
     * error
    */
    TInt iError;
    };

    



#endif