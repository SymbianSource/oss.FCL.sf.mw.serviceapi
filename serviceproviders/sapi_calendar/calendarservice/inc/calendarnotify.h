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


#ifndef __CALENDARNOTIFY_H
#define __CALENDARNOTIFY_H

class MCalCallbackBase;
class CAsyncRequestObserver;

/**
 *This class implements CalendarNotify SAPI core logic.It includes  
 * methods for notification of changes in calendar.
 * 
 */
class CCalendarObserver : public CCalendarASyncRequest, /*public CActive, */public MCalChangeCallBack2
	{
	public:
	
		/**
		 * Two-phased constructor.
		 * @param CCalendarSessionInfo* a calendar session information.
		 * @param aFilter* Filter object. 
		 * @param aAsyncRequestObserver Asynchronous request observer
	     * @param aNotifyCallback Callback Object for Change notification. 
		*/
		static CCalendarObserver* NewL( CCalendarSessionInfo* aSessionInfo, 
											CCalendarFilter* aFilter, 
											CAsyncRequestObserver* aAsyncRequestObserver,
											MCalCallbackBase* aNotifyCallback );
		
		/**
		* Start the notification process
		*/
		void StartChangeNotificationL();
		
		/**
	     * Destructor.
    	*/
		virtual ~CCalendarObserver();

		/**
		 * Inherited from MCalChangeCallBack2 class 
		*/ 
		virtual void CalChangeNotification(RArray< TCalChangeEntry > &aChangeItems);		
	
		virtual TBool IsInProgress();
	
	private:

		/** 
	     * Default  constructor.
	     * @param aSessionInfo  It is an object of CCalSession Class which
	     *        represents a channel of communication between a client thread  
	     *        and the calendar Server thread .
	     * @param aNotifyCallback It is a callback notification
	    */
		CCalendarObserver( CCalendarSessionInfo* aSessionInfo, 
									CAsyncRequestObserver* aAsyncRequestObserver, 
									MCalCallbackBase* aNotifyCallback );

		void ConstructL( CCalendarFilter* aFilter );
		
		/**
		 * Inherited from CActive class 
		*/ 
    	virtual void DoCancel();

		/**
		 * Inherited from CActive class 
		*/ 
        virtual void RunL();

		/**
		 * Activates the request and call SetActive() function
		*/ 
		void ActivateRequest(TInt aReason);

		/**
		 * Gives the result for notification request.
		*/ 
		void NotifyRequestResult(TInt aReason);
	
	private:

		/**
		 * Calendar server session
		*/ 
		CCalendarSessionInfo* iSessionInfo;

		/**
		 * Calendar server session for notifications
		*/ 
		CCalSession* 			iSession;

		/**
		 * Callback Object
		*/ 
		MCalCallbackBase* iNotifyCallback;

		/**
		 * Filter Object
		*/ 
		CCalendarFilter* iFilter;

		/**
		 * Asynchronous request observer, Used to get infromed of completion or request
		*/ 
		CAsyncRequestObserver* 	iAsyncRequestObserver;
		
		TBool			iIsInProgress;

	};



#endif __CALENDARNOTIFY_H