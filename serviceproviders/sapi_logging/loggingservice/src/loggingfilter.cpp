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
* Description:  Implements sapifilter class.
*
*/


#ifdef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <logwraplimits.h>
#endif
#include <e32base.h>
#include <logcli.h>
#include "loggingfilter.h"
#include "loggingevent.h"

/**
* Default consturctor
*/

CLogsFilter :: CLogsFilter()
    {
    }

/**
* Default Desturctor
*/

CLogsFilter :: ~CLogsFilter()
    {
    delete  iLogFilter;
    delete iEvent ;
    delete iLogClient ;
    iFs.Close() ;
    }

/**
* Two phase constructors
*/
EXPORT_C CLogsFilter* CLogsFilter :: NewL()
    {
    CLogsFilter *self = CLogsFilter :: NewLC();
    CleanupStack :: Pop(self) ;
    return self ;
    }

/**
* Two Phase constructor
*/
CLogsFilter* CLogsFilter :: NewLC()
    {
    CLogsFilter *self = new((ELeave)) CLogsFilter() ;
    CleanupStack :: PushL(self);
    self->ConstructL() ;
    return self ;
    }

/**
* This function constructs the member elements of CLogSyncService Class
*/
void CLogsFilter :: ConstructL()
    {
    User::LeaveIfError(iFs.Connect());
    iLogClient = CLogClient::NewL(iFs);
    iLogFilter = CLogFilter :: NewL() ;
    iRecentList = 0;
    iTaskId = -1 ;
    iEvent = NULL ;
    }

/**
* SetEvent, Sets the event for the filer
*
* @param aEvent , event to be set
*/
EXPORT_C void CLogsFilter :: SetEventL( CLogsEvent *aEvent )
    {
    if( iEvent )
        {
        delete iEvent ;
        }
    iEvent = CLogsEvent :: NewL() ;
    iEvent->Copy(aEvent->getEvent()) ;
    }

/**
* Function to set the Direction for this filter
*
* @param aDirection direction id
*/
EXPORT_C void CLogsFilter :: SetDirection( TInt aDirection )
    {
    TBuf<KLogMaxDirectionLength> direction;
    iLogClient->GetString(direction, aDirection);
    iLogFilter->SetDirection(direction) ;
    }
/**
* Function to set the Status of the filter
*/
EXPORT_C void CLogsFilter :: SetStatus( TInt aStatus )
    {
    TBuf<KLogMaxDirectionLength> status ;
    iLogClient->GetString(status , aStatus) ;
    iLogFilter->SetStatus(status) ;
    }


