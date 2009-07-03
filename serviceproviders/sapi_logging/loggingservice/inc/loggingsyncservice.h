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
*   %created_by:    shreedha %
*   %date_created:  Tue Feb 10 11:34:01 2009 %
*
*/
/**********************************************************************
*
*   Header %name:   loggingsyncservice.h %
*   Instance:       bh1sapi_1
*   Description:
*   %created_by:    shreedha %
*   %date_created:  Tue Feb 10 11:34:01 2009 %
*
**********************************************************************/
#ifndef LOGGINGSERVICE_H
#define LOGGINGSERVICE_H

#include <logwrap.h>
#include <logcli.h>


/**
* Forward declaration
*/
class CLogViewEvent  ;
class CLogIter       ;

/**
* CLogSyncService: Deligator class declariation, this is a wrapper class
* for all the functionalities offers by symbian logging service.
*
* This Class deligates the responsibilities to coreimp class for async
* service
*/

class CLogSyncService: public CActive
    {

    public :

        /**
        * NewL: Two phased construction
        */

        IMPORT_C static CLogSyncService *NewL() ;

        /**
        * NewLC: Creates an instance of CLogSyncServiceClass
        * Two Phased constructor
        * returns newly allocated object.
        */

        static CLogSyncService* NewLC() ;

        /**
        * Add(): Adds a new event to event database.Synchronous
        * returns unique id of the event added in event database.
        */

        IMPORT_C TLogId AddL( CLogEvent *aEvent );

        /**
        * Deletes a event from the event database
        * @param aLogId Event id of the event in the database
        */

        IMPORT_C TInt   Delete( TLogId aId ) ;

        /**
        * GetList(): Gets the events as specified by filter
        *
        * @param aFilter, view filter
        */

        IMPORT_C CLogIter*   GetListL( CLogFilter *aFilter ) ;

        /**
        * Returns the current event in the view
        */

        inline const CLogEvent& Event()
            {
            return iLogViewEvents->Event() ;
            }

        /**
        * ReadRecentEvents, reads recentEvents from the list
        *
        * @param aRecentList, recentlist to be viewed
        * @param aFilter, filter for events to appear in view
        */

        CLogIter* ReadRecentEventsL( TLogRecentList  aRecentList ,
                                    CLogFilter *aFilter = NULL ) ;

        /**
        * Gets the details of the event as specified by the
        * input paramater
        *
        * @param aEvent, details of the event to be fetched
        */

        CLogIter* GetEventL( CLogEvent *aEvent ) ;


        /**
        * Default Destructor
        */

        ~CLogSyncService() ;


    protected :

        /**
        * ConstructL(): Internal method to construct members
        */

        void ConstructL() ;

        /**
        * Default constructor
        */

        CLogSyncService() ;


        /**
        * DoInitialiseL(): Internal method to initialise members
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

    private:

        /**
        * Log Engine Handle
        */
        CActiveSchedulerWait* iWaitScheduler;
        CLogClient*   iLogClient ;
        CLogViewEvent* iLogViewEvents ;
        CLogViewRecent* iLogViewRecent ;
        RFs iFs ;
        TInt iTaskId ;


};

#endif
