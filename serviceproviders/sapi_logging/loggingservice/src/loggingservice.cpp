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


#include <e32def.h>
#include <logwrap.h>
#include <logcli.h>

#include "logiter.h"
#include "loggingservice.h"
#include "loggingasyncservice.h"
#include "loggingsyncservice.h"
#include "loggingevent.h"
#include  "loggingfilter.h"
#include  "loggingcallbackslot.h"

/**
* Default Constructor Method
*/

CLoggingService :: CLoggingService()
    {
    }

/**
* Default Destructor
*/
CLoggingService :: ~CLoggingService()
    {
    /**
     * Iterate through the registration table and
     * cancel and delete any outstanding async request
     */
    for(TInt iter = 0 ; iter < iRegTable.Count() ; ++iter)
        {
        iRegTable[iter]->GetActiveObj()->SetCancelFlag(EFalse);
        delete iRegTable[iter] ;
        }
    delete iLogService;
    delete iSapiEvent;
    iRegTable.Close() ;
    }

/**
*Two phased constructor implementation
*/
EXPORT_C CLoggingService* CLoggingService :: NewL()
    {
    CLoggingService* self = CLoggingService::NewLC();
    CleanupStack::Pop(self);
    return self;
    }

/**
* Two phased constructor implementation
*/
CLoggingService* CLoggingService :: NewLC()
    {
    CLoggingService* self = new (ELeave) CLoggingService();
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

/**
* This function constructs the member elements of CLogsEvent Class
*/
void CLoggingService:: ConstructL()
    {
    iSapiEvent = CLogsEvent :: NewL();
    iLogService = CLogSyncService :: NewL();
    }

/**
* Adds an event to the event database synchronously
* @parm Details of the event to be logged
*/
EXPORT_C TLogId CLoggingService :: AddEventL( CLogsEvent* aSapiEvent )
    {
    //Check The registration Table, and make sure that no async
    // Request is pending
    return iLogService->AddL(aSapiEvent->getEvent());
    }

/**
* Async AddEvent function. adds an Event asynchronously
* do event database
* @param aEvent, details of the event to be added to the
* event database
*/
EXPORT_C TInt CLoggingService :: AddEventL( TUint aTransId ,
                                            CLogsEvent* aSapiEvent ,
                                            MLoggingCallback* aCallback )
    {
    CLogAsyncService *LogAsyncService = CLogAsyncService :: NewL(aCallback) ;
    LogAsyncService->AddL( aTransId ,aSapiEvent->getEvent());
    CCallbackSlot *LogSlot = CCallbackSlot :: NewL() ;
    LogSlot->SetUid(aTransId) ;
    LogSlot->SetActiveObj(LogAsyncService) ;
    iRegTable.Append(LogSlot) ;
    return KErrNone ;
    }

/**
* Deletes an event from the event database synchronously
* @parm Details of the event to be logged
* @param aFilter, search criteria for this event in event database
*/

EXPORT_C TInt CLoggingService :: DeleteEventL( TLogId aLogId )
    {
    return iLogService->Delete(aLogId);
    }

/**
* Deletes a event from the event database
* @param aLogId Event id of the event in the database
* @param aFilter, search criteria for this event in event database
*/
EXPORT_C void CLoggingService :: DeleteEventL( TUint aTransId ,
                                               TLogId aLogId,
                                               MLoggingCallback* aCallback )

    {
    CLogAsyncService  *LogAsyncService =  CLogAsyncService :: NewL(aCallback) ;
    LogAsyncService->Delete(aTransId ,aLogId);
    CCallbackSlot *slot = CCallbackSlot :: NewL() ;
    slot->SetUid(aTransId) ;
    slot->SetActiveObj(LogAsyncService) ;
    iRegTable.Append(slot) ;
    }

/**
* Gets the event list from events from the log database synchronously
*
* @param aLogId Event id of the event in the database
* @param aFilter, search criteria for this event in event database
*
* Returns the iterator
*/
EXPORT_C CLogIter* CLoggingService :: GetListL( CLogsFilter* aFilter )
    {
    CLogIter* iter=NULL  ;
    switch(aFilter->GetRequestType())
        {
        case EReadEvents :
            {
            iter = iLogService->GetListL(aFilter->getFilter()) ;
            break ;
            }
    
        case EGetEvent :
            {
            CLogsEvent *event = aFilter->GetEvent() ;
            iter = iLogService->GetEventL(event->getEvent()) ;
    
            if(iter )
                {
                iter->SetEventL(event) ;
                }
    
            break ;
            }
    
        case EGetRecent :
            {
            iter = iLogService->ReadRecentEventsL( aFilter->GetRecentList(), aFilter->getFilter() ) ;
            break ;
            }
    
        default :
            {
            User :: Leave(KErrArgument) ;
            }
        }
    return iter ;
    }

/**
* Gets the event list from events from the log database asynchronously
*
* @param aTransId, transactionid of the async event
* @param aFilter, search criteria for this event in event database
* @param aCallback, call back address
*/
EXPORT_C TInt CLoggingService :: GetListL( TUint aTransId , 
                                           CLogsFilter* aFilter ,
                                           MLoggingCallback* aCallback )
    {
    CLogAsyncService* LogAsyncService = CLogAsyncService :: NewL(aCallback) ;
    /**
     * Parse the request type and  issue the request to loggingservice
     * class accordingly
     */
    switch(aFilter->GetRequestType())
        {
        case EReadEvents :
            {
            LogAsyncService->GetListL(aTransId , aFilter->getFilter()) ;
            break ;
            }
    
        case EGetEvent :
            {
            CLogsEvent *event = aFilter->GetEvent() ;
            LogAsyncService->GetEventL(aTransId , event->getEvent()) ;
            break ;
            }
    
        case EGetRecent :
            {
            LogAsyncService->ReadRecentEventsL(aTransId , aFilter->GetRecentList(), aFilter->getFilter()) ;
            break ;
            }
    
        default :
            {
            User :: Leave(KErrArgument) ;
            }
        }
    CCallbackSlot *slot = CCallbackSlot :: NewL() ;
    slot->SetActiveObj(LogAsyncService) ;
    slot->SetUid(aTransId) ;
    iRegTable.Append(slot);
    return KErrNone ;
    }


/**
* Notifies the updates happening to the log database
*
* @param aDelay, notification interval.
*/

EXPORT_C TInt CLoggingService :: NotifyUpdatesL( TUint aUid ,
                                                 TTimeIntervalMicroSeconds32 aDelay ,
                                                 MLoggingCallback *aCallback )
    {
    CLogAsyncService *AsyncService = CLogAsyncService :: NewL(aCallback);
    AsyncService->SetInterval(aDelay) ;
    AsyncService->NotifyUpdates(aUid ,aDelay) ;
    CCallbackSlot *slot = CCallbackSlot :: NewL() ;
    slot->SetActiveObj(AsyncService) ;
    slot->SetUid(aUid) ;
    iRegTable.AppendL(slot) ;
    return KErrNone ;
    }

/**
* CancelServiceL, cancels the on going service
* @param aTransid
*/
EXPORT_C TInt CLoggingService :: CancelServiceL( TUint aTransid )
    {
    for(TInt iterator = 0 ; iterator < iRegTable.Count() ; ++iterator)
        {
        if((iRegTable[iterator]->getUid()) == aTransid)
            {
           (iRegTable[iterator])->GetActiveObj()->Cancel() ;
            delete iRegTable[iterator];
            iRegTable[iterator]=NULL;
            iRegTable.Remove( iterator );
            iRegTable.Compress();
            return KErrNone ;
            }
        }
    
    return KErrNotFound ;
    }


