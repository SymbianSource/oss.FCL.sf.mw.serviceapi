/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Implements logging SAPI deligator class.
*
*/



#include <logwrap.h>
#include <logcli.h>
#include <logview.h>

#include "loggingasyncservice.h"
#include "loggingsyncservice.h"
#include "loggingevent.h"
#include "logiter.h"

/**
* Default Constructor Method
*/

CLogSyncService :: CLogSyncService(): CActive(EPriorityStandard)
    {
    }


/**
* Default Destructor
*/
CLogSyncService :: ~CLogSyncService()
    {
    if(this->IsAdded())
        {
        this->Deque() ;
        }
    delete iLogViewEvents ;
    delete iLogViewRecent ;
    delete iLogClient ;
    delete iWaitScheduler;
    iFs.Close() ;
    }

/**
* Two phased constructor implementation
*/
EXPORT_C CLogSyncService* CLogSyncService :: NewL()
    {
    CLogSyncService* self = CLogSyncService::NewLC();
    CleanupStack::Pop(self);
    return self;
    }

/**
* Two phased constructor implementation
*/

CLogSyncService* CLogSyncService :: NewLC()
    {
    CLogSyncService* self = new (ELeave) CLogSyncService();
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

/**
* This function constructs the member elements of CLogSyncService Class
*/

void CLogSyncService :: ConstructL()
    {
    User::LeaveIfError(iFs.Connect());
    iLogClient = CLogClient::NewL(iFs);
    iLogViewEvents = CLogViewEvent :: NewL(*iLogClient) ;
    iLogViewRecent = CLogViewRecent :: NewL(*iLogClient) ;
    iTaskId  = -1 ;
    iWaitScheduler = new CActiveSchedulerWait();
    DoInitialiseL() ;
    }

/**
* DoInitialise Method, initalises the  members of the class,
* and puts the object in ActiveScheduler List
*/

void CLogSyncService :: DoInitialiseL()
    {
    if(!(this->IsAdded()))
        {
        CActiveScheduler :: Add (this) ;
        }
    }

/**
* RunL method implementation
*/
void CLogSyncService :: RunL()
    {
    iWaitScheduler->AsyncStop();
    }

/**
* DoCancel Implementation
*/
void CLogSyncService :: DoCancel()
    {
     ;
    }

/**
* Reads recent events from the event database
*
* @param aRecentList, recent event list
* @param aFilter, filter for events to appear in the view
* returns the ownership handle to Recentevents in the iter
*/
CLogIter* CLogSyncService :: ReadRecentEventsL( TLogRecentList aRecentList ,
                                                CLogFilter *aFilter )
    {
    CLogIter *iter = CLogIter :: NewL() ;
    CLogClient *logcli = CLogClient :: NewL(iter->GetRFs()) ;
    CLogViewRecent *LogViewRecent  = CLogViewRecent :: NewL(*logcli) ;
    
    iter->SetLogClient(logcli) ;
    iter->SetLogRecentView(LogViewRecent) ;
    iter->SetTaskId(EGetRecent) ;
    
    if (LogViewRecent->SetRecentListL(aRecentList, *aFilter, iStatus) )
        {
        // set this active object active to get the events
        // from the main event database, see RunL()
        SetActive();
        iWaitScheduler->Start() ;
        
        //Wrap the LogViewRecent in iter and return the ownership to
        // the consumer
        iter->SetRecentView(LogViewRecent) ;
        }
    else
        {
        delete iter ;
        iter = NULL ;
        }
    return iter ;
        
    }
    
    
/**
* Adds a new event to the event database
* @param aEvent: Details of the event to be added to the event database
*/
EXPORT_C TLogId  CLogSyncService :: AddL( CLogEvent* aEvent )
    {
    iLogClient->AddEvent( *aEvent , iStatus ) ;
    SetActive() ;
    iWaitScheduler->Start() ;
    
    if( iStatus.Int() != KRequestPending )
        {
        return aEvent->Id() ;
        }
    return iStatus.Int() ;
    }


/**
* Deletes a event from the event database
* @param aLogId Event id of the event in the database
*/
EXPORT_C TInt CLogSyncService :: Delete( TLogId aLogId )
    {
    if( aLogId > 0 )
        {
        iLogClient->DeleteEvent(aLogId , iStatus) ;
        }
    else
        {
        return KErrNotFound;
        }
    
    SetActive() ;
    iWaitScheduler->Start();
    return iStatus.Int() ;
    }

/**
* GetList(): Gets the events as specified by filter
*
* @param aFilter, view filter
* Returns the ownership of the iterator for the getlist
* result containing the handle to LogviewEvents.
*/
EXPORT_C CLogIter* CLogSyncService ::  GetListL( CLogFilter *aFilter )
    {
    
    CLogIter *iter = CLogIter :: NewL() ;
    CLogClient *cli = CLogClient :: NewL(iter->GetRFs()) ;
    CLogViewEvent* LogviewEvents =  CLogViewEvent :: NewL(*cli) ;
    
    iter->SetLogClient(cli) ;
    iter->SetLogViewEvents(LogviewEvents) ;
    //LogviewEvents->SetFilterL(*aFilter , iStatus) ;
    iter->SetTaskId(EReadEvents) ;
    
    if(LogviewEvents->SetFilterL(*aFilter , iStatus))
        {
        SetActive() ;
        iWaitScheduler->Start();
        iter->SetLogViewEvents(LogviewEvents);
        return iter ;
        }
    else
        {
        delete iter;
        return NULL;
        }
    }

/**
* Gets the details of the event as specified by the
* input paramater
*
* @param aEvent, details of the event to be fetched
* returns the owner ship of the iter to the consumer
*/
CLogIter* CLogSyncService :: GetEventL( CLogEvent *aEvent )
    {
    CLogIter *iter = CLogIter :: NewL() ;
    
    iter->SetTaskId(EGetEvent) ;
    CLogClient *cli = CLogClient :: NewL(iter->GetRFs()) ;
    iter->SetLogClient(cli) ;
    cli->GetEvent(*aEvent , iStatus) ;
    SetActive() ;
    iWaitScheduler->Start();
    
    if(iStatus.Int() != KErrNone)
        {
        delete iter ;
        return NULL ;
        }
    return  iter ;
    }



