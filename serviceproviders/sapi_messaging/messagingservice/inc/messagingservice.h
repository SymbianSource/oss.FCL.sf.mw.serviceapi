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


#ifndef __MESSAGINGSERVICE_H
#define __MESSAGINGSERVICE_H

#include "messageheader.h"

class CMessageObserver;


/**
 * Messaging Service class 
*/
class CMessagingService : public CBase, public MAsyncRequestObserver
	{
	public:

		/**
		 * Two Phase Constructor
		*/ 
		IMPORT_C static CMessagingService* NewL();

		/**
		 * Destructor
		*/ 
		virtual ~CMessagingService();

	private:

		/**
		 * Constructor
		*/ 
		CMessagingService();

		/**
		 * Constructor
		*/ 
		void ConstructL();
		
		/**
		 * Adds asynchronous request object
		 * @param aTransactionId Transcation Id os Async object
		 * @param aAsyncObj  Async object
		*/ 
		void AddAsyncObjL( const TInt32 aTransactionId, CActive* aAsyncObj );

		/**
		 * Deletes all the Asynchronous request objects
		*/
		void DeleteAsyncObjects();
		
	public:

		/**
		 * Sends Message
		 * @param aMessageParam Structure containing details about the message
		 *         							which is being send
		 * @param aCallback     CallBack object for asynchronous operation
		*/ 
		IMPORT_C void SendMessageL( CSendMessageParams* aMessageParam, 
											CMsgCallbackBase* aCallback = NULL );

		/**
		 * Deletes Message
		 * @param aMessageId  Message Id of message which is to be deleted
		 * @param aCallback   CallBack object for asynchronous operation
		*/ 
		IMPORT_C void DeleteMessageL( const TMsvId aMessageId,
											CMsgCallbackBase* aCallback = NULL );

		/**
		 * Changes Status
		 * @param aMessageId  Message Id of message which is to be deleted
		 * @param aStatusFlag Status flag
		 * @param aFlagValue  Flag value
		 * @param aCallback   CallBack object for asynchronous operation
		*/ 
		IMPORT_C void ChangeStatusL( const TMsvId aMessageId,
											const TMessageStatusFlag aStatusFlag,
											const TBool  aFlagValue,
											CMsgCallbackBase* aCallback = NULL );

		/**
		 * Gives notification 
		 * @param aNotification  Notification type
		 * @param aCallback   CallBack object for asynchronous operation
		*/ 		
		IMPORT_C TInt RequestNotification( const TNotificationType aNotification, 
											CMsgCallbackBase* aCallback );

		/**
		 * Cancels notification 
		 * @param aNotification  Notification type
		 * @param aCallback      CallBack object for asynchronous operation
		*/ 				
		IMPORT_C TInt CancelNotification( const TNotificationType aNotification, 
											CMsgCallbackBase* aCallback = NULL );

		
		/**
		 * Gives list of message ids
		 * @param aFilterParams  Filter parameters
		 * @param aFolderId  	 Folder to be used (Inbox/outbox/send/...)
		 * @param aCallback      CallBack object for asynchronous operation
		 * @param aEntrySelection   output pararmeter for the result id array
		*/ 				
		IMPORT_C void GetIdListL( CFilterParamInfo* aFilterParams,
											TMsvId aFolderId,
									        CMsgCallbackBase* 	/*aCallback*/,
									        CMsvEntrySelection*& aEntrySelection );
											        
		/**
		 * Gives next header based on inputs 
		 * @param aFilterParams  Filter parameters
		 * @param aEntrySelection array of message ids on which filteration to be done
		 * @param aIndex      starting position on aEntrySelection to be start search
		 * @param aCallback   CallBack object for asynchronous operation
		 * @param aHeader   output pararmeter for the result header
		*/ 				
		IMPORT_C void GetNextHeaderL( CFilterParamInfo* aFilterParams,
											CMsvEntrySelection* aEntrySelection,
											TInt& aIndex, 
							        		CMsgCallbackBase* 	/*aCallback*/,
							        		CMessageHeader*& aHeader );
		/**
		 * Gives message details 
		 * @param aMessageId     Message id 
		 * @param aCallback      CallBack object for asynchronous operation
		 * @param aResult        Output parameter containing requested message details
		*/ 				
		IMPORT_C void GetMessageDetailL( const TMsvId aMessageId, 
											CMsgCallbackBase* aCallback, 
											CMessageDetailInfo*& aResult );

		/**
		 * Cancels asynchronous request
		 * @param aTransactionId     asynchronous transaction id
		 * @param aResult        error code
		*/ 				
		IMPORT_C TInt Cancel( const TInt32 aTransactionId );


	//MAsyncRequestObserver	drived
	public:

		/**
		   * Notifies Messaging service about the completeion of the request
		   * @param aTransactionId TransactionId of Asynchronous request object
		   * @return void
	  	*/
		void RequestComplete( const TInt32 aTransactionId );

	private:
		
		/**
		 * Represents a channel of communication between a client thread 
		 * and the Message Server thread.
	  	*/ 
		CMsvSession* iMsgServerSession;
		
		/**
		 * Provides the interface for notification of events from a Message Server session.
	  	*/ 
		CMessageObserver* iSessionObserver;
		
		/**
		 * Contains handles of all asynchronous requests
	  	*/ 
		RArray<TAsyncRequestInfo> iAsyncObjArray;
	};


#endif __MESSAGINGSERVICE_H