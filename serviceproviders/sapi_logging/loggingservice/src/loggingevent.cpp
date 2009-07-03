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
* Description:  Implements sapievent class.
*
*/


#include <e32base.h>
#include <logwrap.h>
#include <logcli.h>

#include "loggingevent.h"

/**
* Default Constructor Method
*/

CLogsEvent :: CLogsEvent()
    {
    }

/**
* Default Destructor
*/

CLogsEvent :: ~CLogsEvent()
    {
    delete iLogEvent;
    delete iLogClient ;
    iFs.Close() ;
    }

/**
*Two phased constructor implementation
*/

EXPORT_C CLogsEvent* CLogsEvent :: NewL()
    {
    CLogsEvent* self = CLogsEvent::NewLC();
    CleanupStack::Pop(self);
    return self;
    }

/**
* Two phased constructor implementation
*/

CLogsEvent* CLogsEvent :: NewLC()
    {
    CLogsEvent* self = new (ELeave) CLogsEvent();
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

/**
* This function constructs the member elements of CLogsEvent Class
*/
void CLogsEvent :: ConstructL()
    {
    User::LeaveIfError(iFs.Connect());
    iLogClient = CLogClient::NewL(iFs);
    iLogEvent = CLogEvent::NewL();
    }

/**
* This function sets the direction of the event
*/
EXPORT_C  void CLogsEvent ::  SetDirection(TInt aDirection)
    {
    TBuf<KLogMaxDirectionLength> direction;
    iLogClient->GetString(direction, aDirection);
    iLogEvent->SetDirection(direction) ;
    }


/**
* This function sets the status of the event
*
* @param aStatus , status of the event(pending, delivered etc.,)
*/
EXPORT_C void CLogsEvent :: SetStatus(TInt aStatus)
    {
    TBuf<KLogMaxDirectionLength> status ;
    iLogClient->GetString(status , aStatus) ;
    iLogEvent->SetStatus(status) ;
    }




