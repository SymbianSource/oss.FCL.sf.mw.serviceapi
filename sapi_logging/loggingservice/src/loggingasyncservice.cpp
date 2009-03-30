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
* Description:  Implements logging SAPI async class.
*
*/


#include "loggingasyncservice.h"
#include "loggingevent.h"
#include "loggingfilter.h"
#include "logiter.h"

/**
* Default Constructor Method
*/
CLogAsyncService :: CLogAsyncService(): CActive(EPriorityStandard)
    {
    iTransId=0;
    }

/**
* Default Destructor
*/
CLogAsyncService :: ~CLogAsyncService()
    {
    Cancel();
    delete iLogClient ;
    iFs.Close() ;
    }

/**
* NewL() Constructs the ClogAsync object
*/
EXPORT_C CLogAsyncService* CLogAsyncService :: NewL( MLoggingCallback* aCallback )
    {
    CLogAsyncService* self = CLogAsyncService::NewLC( aCallback );
    CleanupStack :: Pop( self ) ;
    return self;
    }

/**
* NewLC Two phase constructor implementation
*/
CLogAsyncService* CLogAsyncService :: NewLC( MLoggingCallback* aCallback )
    {
    CLogAsyncService* self = new((ELeave)) CLogAsyncService() ;
    CleanupStack :: PushL(self) ;
    self->ConstructL(aCallback) ;
    return self ;
    }

/**
* ConstructL, Constructs Members of AsyncService Class
*/
void CLogAsyncService :: ConstructL( MLoggingCallback* aCallback )
    {
    User::LeaveIfError(iFs.Connect());
    iLogClient = CLogClient::NewL(iFs);
    iCallback = aCallback;
    iIter = NULL ;
    iTask = ESleep;
    DoInitialiseL() ;
    }

/**
* DoInitalise, Initalises the Members of AsyncService Class
*/
void CLogAsyncService :: DoInitialiseL()
    {
    CActiveScheduler :: Add(this) ;
    }

/**
* RunL Method .
*/
void CLogAsyncService :: RunL()
    {
    TRAP_IGNORE(RunCmdL());
    }

/**
* RunCmdL Method implementation, revices Notifications of completed
* Async services: Add , Delete and GetEvent requests
*/
void CLogAsyncService :: RunCmdL()
    {
    switch( iTask )
         {
         case EAddEvent:
            {
            CLogIter *iter = CLogIter :: NewL() ;
            iter->SetEventL(iUpdatedEvent) ;
            delete iUpdatedEvent ;
            iUpdatedEvent =  NULL ;
            iCallback->HandleNotifyL(iTransId ,iStatus.Int() , iter ) ;
            iter = NULL;
            iTask = ESleep;
            this->Deque();
            break;
            }
    
         case EDeleteEvent:
            {
            iCallback->HandleNotifyL( iTransId, iStatus.Int(), NULL ) ;
            iTask = ESleep;
            this->Deque();
            break;
            }
    
         case EReadEvents :
            {
            iIter->SetTaskId(EReadEvents) ;
            iCallback->HandleNotifyL( iTransId, KErrNone, iIter  ) ;
            iIter = NULL ;
            iTask = ESleep;
            break;
            }
    
        case EGetRecent:
            {
            iIter->SetTaskId(EGetRecent) ;
            iCallback->HandleNotifyL( iTransId ,KErrNone, iIter ) ;
            iIter = NULL ;
            iTask = ESleep;
            break;
            }
    
        case EGetEvent :
            {
            iIter->SetEventL( iUpdatedEvent ) ;
            iIter->SetTaskId( EGetEvent ) ;
            delete iUpdatedEvent ;
            iUpdatedEvent = NULL ;
            
            if( iStatus.Int() != KErrNone )
                {
                delete iIter;
                iIter = NULL ;
                }
                
            iCallback->HandleNotifyL(iTransId , KErrNone, iIter) ;
            iIter = NULL ;
            iTask = ESleep;
            break ;
            }
        case ENotification:
            {
            NotifyUpdates( iTransId, iInterval );
            iCallback->HandleNotifyL( iTransId, KErrNone , NULL ) ;
            break;
            }
        
        case EErrorEvent:
            {
            delete iIter;
            iIter = NULL ;
            iCallback->HandleNotifyL( iTransId ,KErrNone, iIter ) ;
            iTask = ESleep;
            break;    
            }
            
        case ESleep:
        default:
            {
            break ;
            }
    
         }
    }

/**
* Do Cancel Method for cancelling the outstanding async requests
*/
void CLogAsyncService :: DoCancel()
    {
    switch(iTask)
        {
        case EAddEvent:
            {
            iLogClient->Cancel();
            break;
            }
    
        case EDeleteEvent:
            {
            iLogClient->Cancel();
            break;
            }
        case EGetRecent:
        case EGetEvent:
        case EErrorEvent: 
        case EReadEvents :
            {
            delete iIter  ;
            break;
            }
        case ENotification:
            {
             iLogClient->NotifyChangeCancel() ;
             break ;
            }
        case ESleep:    
        default:
            {
            break;
            }
        }
    
    iCallback->CancelNotifyL( iTransId );
    
    if(iUpdatedEvent)
        {
         delete iUpdatedEvent ;
         iUpdatedEvent = NULL ;
        }
    
    }

/**
* AddEvent, adds an event to event database asynchronously
* @param aEvent, details of the event to be added to database
*/
EXPORT_C void CLogAsyncService :: AddL( TUint aTransId ,CLogEvent* aEvent )

    {
    if(!iUpdatedEvent)
        {
        iUpdatedEvent = CLogsEvent :: NewL()  ;
        }
    iUpdatedEvent->Copy(aEvent);
    iLogClient->AddEvent(*(iUpdatedEvent->getEvent()) , iStatus);
    iTransId = aTransId ;
    SetActive() ;
    iTask = EAddEvent;
    }

/**
* Deletes a event from the event database
* @param aLogId Event id of the event in the database
* @param aFilter, search criteria for this event in event database
*/
void CLogAsyncService :: Delete( TUint aTransId , TLogId aLogId )
    {
    iLogClient->DeleteEvent(aLogId , iStatus) ;
    iTransId = aTransId ;
    SetActive() ;
    iTask = EDeleteEvent;
    }

/**
* Gets eventList asynchronously
* @param aFilter: Event filter for querying the event database
* @param aCallback: callback address
*/
void CLogAsyncService :: GetListL( TUint aTransId ,CLogFilter *aFilter  )
    {
    if(!iIter)
        {
        iIter = CLogIter :: NewL() ;
        }
    
    CLogClient *cli = CLogClient :: NewL(iIter->GetRFs()) ;
    CLogViewEvent *events = CLogViewEvent :: NewL(*cli) ;
    
    iIter->SetLogViewEvents( events ) ;
    iIter->SetLogClient( cli ) ;
    
    if( events->SetFilterL( *aFilter, iStatus ) )
        {
        iTask = EReadEvents ;
        iTransId = aTransId ;
        SetActive() ;    
        }
    else //case where the setFilter fails but for the uniformity of the 
         //behaviour of this API for all the inputs.. we are artificially 
         //simulalting asyc behaviour to report the error to the user
         //as the other internal apis used in this command gives the error
         //in the callback i.e.., asycn error only
        {
        iIter->SetTaskId( EReadEvents ) ;
        iTask = EErrorEvent;
        iTransId = aTransId ;
        iStatus = KRequestPending;
    	SetActive();
    	TRequestStatus* temp = &iStatus;
        User::RequestComplete( temp, KErrNone );    
        }
    }
/**
* Reads recent events from the database aysnchronously
*
* @param Transaction id of the async event
* @param RecentList
* @param Filter for events to appear in the view.
*/
TBool CLogAsyncService :: ReadRecentEventsL( TUint aTransId , 
                                             TLogRecentList aList ,
                                             const CLogFilter *aFilter )
    {
    if(!iIter)
        {
        iIter = CLogIter :: NewL() ;
        }
    CLogClient *cli = CLogClient :: NewL(iIter->GetRFs()) ;
    CLogViewRecent *LogViewRecent = CLogViewRecent :: NewL(*cli) ;
    iIter->SetLogRecentView( LogViewRecent ) ;
    iIter->SetLogClient( cli ) ;
    
    if(LogViewRecent->SetRecentListL(aList, *aFilter, iStatus))
        {
        // set this active object active to get the events
        // from the main event database, see RunL()
        iTransId = aTransId ;
        iTask = EGetRecent;
        SetActive();
        }
    else
        {
        iIter->SetTaskId(EGetEvent) ;
        iTask = EErrorEvent;
        iTransId = aTransId ;
        iStatus = KRequestPending;
    	SetActive();
    	TRequestStatus* temp = &iStatus;
        User::RequestComplete( temp, KErrNone );    
        }    
    return ETrue ;
        
    }

/**
* Notifies the updates happening to the log database
*/
void CLogAsyncService :: NotifyUpdates( TUint aTransId ,TTimeIntervalMicroSeconds32 aDelay )
    {
    iLogClient->NotifyChange( aDelay , iStatus ) ;
    iTask = ENotification ;
    iTransId = aTransId ;
    SetActive() ;
    }

/**
* Gets the details of the event as specified by the input
* paramater asynchronously
*
* @param, Transaction id of this event
* @param , Details of the event to be fetched from the database
*/
void CLogAsyncService :: GetEventL( TUint aTransId, CLogEvent* aEvent )
    {
    if( !iUpdatedEvent )
        {
        iUpdatedEvent = CLogsEvent :: NewL() ;
        }
    
    iUpdatedEvent->SetEvent(*aEvent) ;
    iLogClient->GetEvent(*(iUpdatedEvent->getEvent()) , iStatus) ;
    
    if( !iIter )
         {
         iIter = CLogIter :: NewL() ;
         }
    iTransId = aTransId ;
    iTask = EGetEvent ;
    SetActive()  ;
    }


