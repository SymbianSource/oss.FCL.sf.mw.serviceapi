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
* Description:   This class is a interface for the observer of
*                CMgService class
*
*/



#ifndef __MGOPERATIONOBSERVER_H
#define __MGOPERATIONOBSERVER_H
#include "mgservice.hrh"

class MCLFItemListModel;

// CLASS DECLARATION
/**
*  Operation Observer is for observing operation events of the mgservice class.
*  Client application gets notified when asynchronous operations
*  are completed.
*
*  
*  @since  Series60 v3.2
*/
class MMgOperationObserver
    {

    public:

        /**
        * Abstract method to get CMgService class events. This method is
        * called when an event is received.
        * @since  Series60 v3.2
        * @param aListModel ClF iterator contains the required result
        * @param aOperationEvent specifies the asynchronous event
        * @param aError System wide error code if the operation did not
        *        succeed.
        * @return void
        */
        virtual void MgNotifyL(TUint  aTransactionID, 
                               MCLFItemListModel*  aListModel,
        					   TMgOperationEvent& aOperationEvent,
                               const TInt& aError ) = 0;
        /**
        * Destructor.
        */
        virtual ~MMgOperationObserver() {}

	};

#endif __MGOPERATIONOBSERVER_H