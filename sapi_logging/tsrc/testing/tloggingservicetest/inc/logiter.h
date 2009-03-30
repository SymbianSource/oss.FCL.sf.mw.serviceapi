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
* Description:   Includes core class log iterator method.
*
*/


#ifndef _LOGITER_H
#define _LOGITER_H

/**
* Forward declarations
*/

class CBase ;
class CActive ;
class CLogClient ;
class CLogViewEvent ;
class CLogViewRecent ;
class RFs ;
class CLogsEvent ;

/**
* Logiterator class, used by the core class for getlist api.
*/

class CLogIter : public CActive
    {
    public :

        /**
        * Two phase constructors
        *
        * @param aClient,  CLogClient handle for log database
        * @param aRecent , CLogViewRecent handle
        * @param aViewEvents ,CLogViewEvents handle
        */
        IMPORT_C static  CLogIter*  NewL() ;

        static CLogIter* NewLC() ;

        /**
        * NextL() method, used to iterate through getlis result
        */

        IMPORT_C CLogsEvent* NextL() ;
        
        /**
        * Reset.
        */
        
        IMPORT_C void Reset() ;

        /**
        * SetRecentView, function to set handle to recent view
        *
        * @param aRecentView, recentview handle
        */

        inline void SetRecentView(CLogViewRecent* aRecent)
            {
            iLogViewRecent = aRecent ;
            }

        /**
        * SetEvent , holds the updated event for Getevent and
        * Add Event
        *
        * @param aEvent, Updated event to be stored
        */

        IMPORT_C void  SetEventL(CLogsEvent* aEvent) ;


        /**
        * Event, gets the current event and handles the owner ship
        */

        inline CLogsEvent* Event()
            {
            /*CSapiEvent *temp = iEvent ;
            iEvent = NULL ;*/
            return iEvent;
            }

        /**
        * GetRfs, gets the handle to the file server
        * subsession
        */

        inline RFs& GetRFs(void)
            {
            return iFs ;
            }

        /**
        * SetLogClient , sets the handle to  logview client
        */
        void SetLogClient(CLogClient *aClient) ;

        /**
        * SetLogViewEvents, sets the handle to view the events
        *
        * @param CLogViewEvent , handle to view the events
        */

        void SetLogViewEvents(CLogViewEvent *aEvent) ;

        /**
        * SetLogViewRecent, sets the handle to the recent view
        *
        * @param aRecentView, recent view handle
        */
        void SetLogRecentView(CLogViewRecent *aRecent) ;

        /**
        * Set the task associated with this iterator
        *
        * @param aTaskId, task ID (GetEvents, ReadRecent , etc.,)
        */
        inline void SetTaskId(TUint aTaskId)
            {
            iTaskId = aTaskId ;
            }

        /**
        * CountL function
        */

        inline TInt CountL()
            {
            return iCount;
            }

        /**
        * Default destructor
        */
        ~CLogIter() ;

        /**
        * From CActive
        */
        void RunL() ;

        /**
        * From CActive
        */

        void DoCancel() ;

    protected :

        
        /**
        * Default constructor
        */

        CLogIter()   ;

        /**
        *ConstructL() , to construct the member funtions
        */

        void ConstructL() ;

    private :

        /**
        * Private member variables
        */
        CActiveSchedulerWait* iScheduler;
        CLogViewEvent*  iLogViewEvents ;
        CLogViewRecent* iLogViewRecent ;
        CLogClient*     iLogClient ;
        CLogsEvent* iEvent ;
        RFs  iFs ;
        TInt iTaskId ;
        TInt iCount ;
        TInt iOps ;

};

#endif