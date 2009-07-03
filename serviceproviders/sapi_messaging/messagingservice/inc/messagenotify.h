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


#ifndef __MESSAGENOTIFY_H
#define __MESSAGENOTIFY_H

class CMsgCallbackBase;
class CMessageHeader;

#include <msvapi.h>

/**
 *This class implements MessageNotify SAPI core logic.It includes  
 * methods for notification of new messages.
 * 
 */
class CMessageObserver : public CBase, public MMsvSessionObserver
	{
	public:
	
		/**
		* Two-phased constructor.
		* @param CMsvSession* a message server session.
		* @param CMsgCallbackBase* 
		*/
		static CMessageObserver* NewL( CMsvSession* aSession = NULL, 
										CMsgCallbackBase* aNotifyCallback = NULL );
		
		/**
	     * Destructor.
    	*/
		virtual ~CMessageObserver();

		/**
		 * Inherited from MMsvSessionObserver class 
		*/ 
		virtual void HandleSessionEventL( TMsvSessionEvent aEvent, 
											TAny* aArg1, 
											TAny* aArg2, 
											TAny* aArg3 );		
	
		/**
		 * Sets the message server session
		 * @param aSession It is a message server session.
		*/ 
		void SetSession( CMsvSession* aSession );

		/**
		 * Sets the callback object
		 * @param aCallback It is callback object to be registered
		 * @return Old callback object
		*/ 
		CMsgCallbackBase* SetCallback( CMsgCallbackBase* aCallback );
		
		/**
		 * Checks if Notification is activated
		 * 
		 * @return True if notification request is active.
		*/ 
		TBool IsActive();

	private:

		/** 
	     * Default  constructor.
	     * @param aSession  It is an object of CMsvSession Class which
	     *        represents a channel of communication between a client thread  
	     *        and the Message Server thread .
	     * @param aNotifyCallback It is a callback notification
	    */
		CMessageObserver( CMsvSession* aSession, CMsgCallbackBase* aNotifyCallback );

		/**
		 * Sets the message header fields
		 * @param aMessageId It is the ID of  message whose header fields are to be set
		*/ 
		CMessageHeader* MessageHeaderL( TMsvId aMessageId );
		
	private:

		/**
		 * Message server session
		 * Not own.
		*/ 
		CMsvSession* iServerSession;

		/**
		 * Callback Object
		 * Not own.
		*/ 
		CMsgCallbackBase* iNotifyCallback;

		/**
		 * Message ID
		*/
		TMsvId iNewMessageId;
	};



#endif __MESSAGENOTIFY_H