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
#include "loggingcallbackslot.h"
#include "loggingasyncservice.h"

/**
* Default Destructor
*/

CCallbackSlot :: ~CCallbackSlot()
    {
    if(iActive->IsAdded())
        {
        iActive->Deque() ;
        }
    delete iActive ;
    }

/**
*Two phased constructor implementation
*/
EXPORT_C CCallbackSlot* CCallbackSlot :: NewL()
    {
    CCallbackSlot* self = CCallbackSlot::NewLC();
    CleanupStack::Pop(self);
    return self;
    }

/**
* Two phased constructor implementation
*/
CCallbackSlot* CCallbackSlot :: NewLC()
    {
    CCallbackSlot* self = new (ELeave) CCallbackSlot();
    CleanupStack::PushL(self);
    return self;
    }
