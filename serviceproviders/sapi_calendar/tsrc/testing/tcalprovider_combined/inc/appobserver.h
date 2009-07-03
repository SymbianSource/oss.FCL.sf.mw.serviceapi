/*
* Copyright (c) 2007-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:   Operation Observer is for observing operation events of the appservice class.
*  							 Client application gets notified when asynchronous operations
*                are completed.
*
*/




#ifndef __APPOBSERVER_H
#define __APPOBSERVER_H

#include <e32def.h> 
#include "appmanagercommon.h"

// CLASS DECLARATION
/**
*  App Observer is for observing operation events of the appservice class.
*  Client application gets notified when asynchronous operations
*  are completed.
*
*
*  @since  Series60 v3.2
*/
class MAppObserver
    {

    public:

        /**
        * Abstract method to get AppServiceclass events. This method is
        * called when an event is received.
        * @since  Series60 v3.2
        * @param aReason indicates error code or sucess of asynch event
        * @return void
        */
        virtual void AppNotifyCallbackL( TInt32 aReason, TInt32 aTransactionID ,TAppOperationEvent& aOperationEvent ) = 0;

        /**
        * Destructor.
        */
        //virtual ~MAppObserver() {}


	};

#endif __APPOBSERVER_H