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
* Description:  
*
*/


#ifndef __ASYNCREQOBSERVER_H
#define __ASYNCREQOBSERVER_H


/**
 * Structure for storing transaction id and associated active object.
*/
struct TAsyncRequestInfo
	{

    /**
     * TransactionId
    */
	TInt32 iTransactionId;

    /**
     * Active object pointer
    */
	CCalendarASyncRequest* iAsyncObj;
	};	
	

/**
 *  Class used to get callback notification from async request module 
 *	about completion of request. 
*/
class CAsyncRequestObserver : public CBase
	{
	public:
	
		/**
		 * Two-Phase Constructor
		*/ 
		static CAsyncRequestObserver* NewL();
		
		/**
		 * Destructor
		*/ 
		~CAsyncRequestObserver();
		
		/**
		   * Notifies about the completeion of an async request
		   * @param aTransactionId TransactionId of Asynchronous request object
		   * @return void
	  	*/
		void RequestComplete( const TInt32 aTransactionId );

		/**
		 * Cancels asynchronous request
		 * @param aTransactionId     asynchronous transaction id
		 * @param aResult        error code
		*/ 				
		TInt Cancel( const TInt32 aTransectionID );
		
		/**
		 * Adds asynchronous request object
		 * @param aTransactionId Transcation Id os Async object
		 * @param aAsyncObj  Async object
		*/ 
		void AddAsyncObjL( const TInt32 aTransactionId, CCalendarASyncRequest* aAsyncObj );

	private:
	   /**
		 * Deletes all the Asynchronous request objects
		*/
		void DeleteAsyncObjects();

	
	private:

		/**
		 * Contains handles of all asynchronous requests
	  	*/ 
		RArray<TAsyncRequestInfo> iAsyncObjArray;
		
	};
	


#endif __ASYNCREQOBSERVER_H