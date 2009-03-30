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
* Description:   Includes logging synchronous service methods.
*
*/



#ifndef LOGGINGDELIGATOR_H
#define LOGGINGDELIGATOR_H


/**
* Forward Declarations
*/
class CLogAsyncService  ;
class CLogSyncService   ;
class CLogsEvent        ;
class CLogsFilter       ;
class MLoggingCallback  ;
class CCallbackSlot ;
class CLogIter      ;

/**
* CLoggingService: Deligator class declariation, this is a wrapper class
* for all the functionalities offers by symbian logging service.
*/


class CLoggingService : public CBase
    {
    public :
        /**
        *  NewL: Two phased construction
        */

        IMPORT_C static CLoggingService* NewL() ;

        /**
        * NewLC: Creates an instance of CLogSyncServiceClass
        * Two Phased constructor
        * returns newly allocated object.
        */

        static CLoggingService* NewLC() ;

        /**
        * Default Destructor.
        */

        ~CLoggingService() ;

        /**
        * Adds an event to the event database synchronously
        * @parm Details of the event to be logged
        */

        IMPORT_C TLogId AddEventL( CLogsEvent *aSapiEvent ) ;

        
        /**
        * Async AddEvent function. adds an Event asynchronously
        * do event database
        * @param aEvent, details of the event to be added to the
        * event database
        */

        IMPORT_C TInt AddEventL( TUint aTransId ,
                                 CLogsEvent* aSapiEvent ,
                                 MLoggingCallback* aCallback ) ;
        /**
        * Deletes an event from the event database synchronously
        * @parm Details of the event to be logged
        * @param aFilter, search criteria for this event in event database
        */

        IMPORT_C TInt DeleteEventL( TLogId aLogId );

        /**
        * Deletes a event from the event database
        * @param aLogId Event id of the event in the database
        * @param aFilter, search criteria for this event in event database
        */

        IMPORT_C void DeleteEventL( TUint aTransId ,
                                    TLogId aLogId,
                                    MLoggingCallback* aCallback ) ;

        /**
        * Gets the list of items from the log database synchronously
        * @param aTransId: Transaction ID.
        * @param aCallBack: Notify callback object
        * @param aFilter : Query Criteria for log database
        */

        IMPORT_C CLogIter* GetListL( CLogsFilter* aFilter ) ;

        /**
        * Gets the list of items from the log database asynchronously
        * @param aTransId: Transaction ID.
        * @param aFilter : Query Criteria for log database
        */

        IMPORT_C TInt GetListL( TUint aTransId ,
                                CLogsFilter* aFilter ,
                                MLoggingCallback* aCallback ) ;

        /**
        * NotifyUpdatesL, overloaded function for Notifications
        *
        * aUid, Transation Id
        * @param aDelay, Minium delay for reciving the updates
        * @param aCallback callback address for notifications
        */

        IMPORT_C TInt NotifyUpdatesL( TUint aUid ,
                                      TTimeIntervalMicroSeconds32 aDelay ,
                                      MLoggingCallback *aCallback );

        /**
        * CancelServiceL, cancels the on going service
        * @param aTransid
        */

        IMPORT_C TInt CancelServiceL( TUint aTransid );


        protected :

        /**
        * ConstructL(): Internal method to construct members
        */

        void ConstructL() ;

        /**
        * Default constructor
        */

        CLoggingService() ;



    private :

        CLogSyncService *iLogService ;
        CLogsEvent*       iSapiEvent;
        RArray <CCallbackSlot *> iRegTable ;

    };

#endif
