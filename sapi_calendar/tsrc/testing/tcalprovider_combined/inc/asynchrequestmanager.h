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
* Description:   This Class provides the core functionality for handling mulitiple asynch request
*		     SAPI
*
*/




#ifndef __ASYNCHREQUESTMANAGER_H
#define __ASYNCHREQUESTMANAGER_H

#include "appmanagercommon.h"

class CLauncherObserver;
class MAppObserver;


/**
* This Class provides the core functionality of
* Application Manager SAPI
*
* @since  Series60 v3.2
*/
class CAsynchRequestManager : public CBase
    {

    public:

    	/**
        * Returns the instance of CAsynchRequestManager.
        * @since  Series60 v3.2
        * @param  void
        * @return CAsynchRequestManager* return the instance of CAsynchRequestManager class
        */
        IMPORT_C static CAsynchRequestManager* NewL();

        /**
    	* Destructor.
    	*/
        virtual ~CAsynchRequestManager();

     

        /**
        * Cancel the pending asynchronous request
        * @since  Series60 v3.2
        * @param  aTransactionID  Unique number to identify the request
        * @return TInt System wide error code
        */
        IMPORT_C TInt Cancel( TInt32 aTransactionID );



        /**
        * This function delete the callback object from the array
        * corresponding to the given transaction id
        * @since  Series60 v3.2
        * @param  aTransactionID  Unique number to identify the callback
        * @return void
        */
        void RequestComplete( TInt32 aTransactionID );




       /**
        * This function add the callback object for support multiple cancle operation
        * @param  MAppObserver observer interface pointer provided by user for informing event.
        * @return The observer for actually observing the underlying class events
        * @since  Series60 v3.2
        */
        CLauncherObserver* AddObsereverLC( MAppObserver* aObserver, TInt32& aTransactionID );

   	
    private:
       
        /**
		* Contains handles of all asynchronous requests
	  	*/
		RArray<TAsyncRequestInfo> iAsyncObjArray;


      };

#endif __ASYNCHREQUESTMANAGER_H