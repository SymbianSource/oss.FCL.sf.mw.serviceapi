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
* Description:  Implements logging SAPI logobserver class.
*
*/

#include <logwrap.h>
#include <logcli.h>
#include <logview.h>
#include <LOGCLIENTCHANGEOBSERVER.H>

#include "loggingsyncservice.h"
#include "logobserver.h"


/**
* Default Constructor
*/

CLogObserver  :: CLogObserver()
    {
    }
/**
* Two phase constructors
*/

CLogObserver* CLogObserver :: NewL()
    {
    CLogObserver* self = CLogObserver :: NewLC() ;
    CleanupStack::Pop(self) ;
    return self ;
    }

/**
* Two phased constructor implementation
*/

CLogObserver* CLogObserver :: NewLC()
    {
    CLogObserver* self = new(ELeave)CLogObserver() ;
    CleanupStack :: PushL(self) ;
    self->ConstructL() ;
    return self ;
    }


/**
* This function constructs the member elements of CLogObserver Class
*/

void CLogObserver :: ConstructL()
    {
    User :: LeaveIfError (iFs.Connect()) ;
    iLogClient = CLogClient :: NewL(iFs) ;
    }

/**
* Default Destructor
*/

CLogObserver :: ~CLogObserver()
    {
    delete iLogClient ;
    iFs.Close() ;
    }

/**
* setobserver function
*/
void CLogObserver :: SetObserverL(MLogClientChangeObserver* aObserver)
    {
    iLogClient->SetGlobalChangeObserverL(aObserver) ;
    }