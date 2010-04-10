/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  ?Description
*
*/


#ifndef __ASYNCHREQUESTMANAGER_H
#define __ASYNCHREQUESTMANAGER_H

class CClfOperationObserver;

/**
 * Structure for storing transaction id and associated active object.
*/
class TAsyncRequestInfo
	{
	
	
	 public:
        /**
        * Constructor
        * @since  Series60 v3.2
        * @param void
        * @return void
        */
        TAsyncRequestInfo():iTransactionId( 0 ),
        		            iAsyncObj( NULL )
        {

    	}

    /**
     * TransactionId
    */
        TUint iTransactionId;

// Instance of observer
	CClfOperationObserver* iAsyncObj;
	};	
	



/**
* This Class provides the core functionality of
* MediaManagement SAPI
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
        * @param  aServiceObserver observer interface pointer provided by user for informing event.
        * @return The observer for actually observing the underlying class events
        * @since  Series60 v3.2
        */
        void AddObserverL( CClfOperationObserver* aServiceObserver, TUint aTransactionID );

   	
    private:
       
        /**
		* Contains handles of all asynchronous requests
	  	*/
		RArray<TAsyncRequestInfo> iAsyncObjArray;


      };

#endif // __ASYNCHREQUESTMANAGER_H
