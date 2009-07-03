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
* Description:  Implements logging SAPI logiter class.
*
*/

#include <e32base.h>
#include <e32def.h>
#include <logwrap.h>
#include <logcli.h>

#include "loggingevent.h"
#include "logiter.h"
#include "loggingasyncservice.h"


/**
* Two phase constructors
*
* @param aClient,  CLogClient handle for log database
* @param aRecent , CLogViewRecent handle
* @param aViewEvents ,CLogViewEvents handle
*/
EXPORT_C CLogIter* CLogIter :: NewL()
    {
    CLogIter *self = CLogIter :: NewLC() ;
    CleanupStack :: Pop(self);
    return self ;
    }

CLogIter* CLogIter ::  NewLC()
    {
    CLogIter *self = new(ELeave) CLogIter() ;
    CleanupStack :: PushL(self);
    self->ConstructL() ;
    return self ;
    }

/**
* ConstructL Method to construct the internal members of
* CLogIter class
*/
void CLogIter :: ConstructL()
    {
    User :: LeaveIfError(iFs.Connect()) ;
    CActiveScheduler :: Add(this) ;
    iScheduler = new CActiveSchedulerWait();
    }

/**
* Default Constructor
* This object holds the ownership of its members and
*
*/
CLogIter :: CLogIter() : CActive(EPriorityStandard) ,  iLogViewEvents(NULL) , iLogViewRecent(NULL) ,
                         iTaskId(-1), iCount(0)
    {
     ;
    }

/**
* Default Destructor
*/
CLogIter :: ~CLogIter()
    {
    if(this->IsAdded())
        {
        Deque() ;
        }
    
    delete iLogViewEvents ;
    delete iLogViewRecent ;
    delete iLogClient ;
    delete iEvent ;
    delete iScheduler;
    iFs.Close() ;
    
    }

/**
* Do Cancel Method, From CActive
*/
void CLogIter :: DoCancel()
    {
    switch(iTaskId)
        {
        case EReadEvents :
            {
            iLogViewEvents->Cancel() ;
            break ;
            }
        
        case EGetRecent :
            {
            iLogViewRecent->Cancel() ;
            break ;
            }
        
        case EGetEvent :
            {
            break ;
            }
        
        default :
            {
            break ;
            }
        }
    }
/**
* RunL Method to handle async events
* Read , ReadRecent and Get an event
*/
void CLogIter :: RunL()
    {
    iScheduler->AsyncStop();
    }

/**
* NextL method to iterate on the getlist result
*/

EXPORT_C CLogsEvent* CLogIter :: NextL()
    {
    CLogsEvent* currEvent = NULL  ;
    switch(iTaskId)
        {
        case EReadEvents :
            {
            if(!iCount)
                {
                iCount = iLogViewEvents->CountL() ;
                }
            if(iOps++ >= iCount)
                {
                return currEvent ;
                }
            currEvent =  CLogsEvent :: NewL() ;
            currEvent->SetEvent(iLogViewEvents->Event()) ;
            
            if((iLogViewEvents->NextL(iStatus)))
                {
                SetActive() ;
                iScheduler->Start() ;
                }
            break ;
            }
        
        case EGetRecent :
            {
            if(!iCount)
                {
                iCount = iLogViewRecent->CountL() ;
                }
            
            if(iOps++ >=  iCount)
                {
                return currEvent ;
                }
            
            currEvent =  CLogsEvent :: NewL() ;
            currEvent->SetEvent(iLogViewRecent->Event()) ;
            
            if(iLogViewRecent->NextL(iStatus) )
                {
                SetActive() ;
                iScheduler->Start() ;
                }
            break ;
            }
        
        case EGetEvent :
            {
            if ( iEvent && !iOps )
                 {
                 ++iOps;
                 currEvent = iEvent;
                 iEvent = NULL;
                 }
            
            break ;
            }
        
        default :
            {
            break ;
            }
        
        }
    return currEvent ;
    }
    
    
/**
* Reset 
*/    
    
EXPORT_C void CLogIter :: Reset() 
	{
	iOps = 0 ;	
	}
    
/**
* Function to set the event
*
* @param aEvent , event to be set
*/


EXPORT_C void CLogIter :: SetEventL(CLogsEvent* aEvent)
    {
    if( iEvent )
        {
        delete iEvent ;
        }
    
    iEvent = CLogsEvent :: NewL() ;
    iEvent->Copy(aEvent->getEvent()) ;
    }



/**
* Sets the LogClient Handle
*
* @param aLogClient, Handle to
* the logclient
*/
void CLogIter :: SetLogClient(CLogClient *aLogClient)
    {
    iLogClient = aLogClient ;
    }


/**
* SetLogViewEvents, sets the handle to view the events
*
* @param CLogViewEvent , handle to view the events
*/

void CLogIter :: SetLogViewEvents(CLogViewEvent *aViewEvents)
    {
    iLogViewEvents = aViewEvents ;
    }

/**
* SetLogViewRecent, sets the handle to the recent view
*
* @param aRecentView, recent view handle
*/

void CLogIter :: SetLogRecentView(CLogViewRecent *aViewRecent)
    {
    iLogViewRecent = aViewRecent ;
    }



