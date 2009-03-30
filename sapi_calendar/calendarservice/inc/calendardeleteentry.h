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


#ifndef __CALENDARDELETEENTRY_H
#define __CALENDARDELETEENTRY_H

class CAsyncRequestObserver;


/**
 * This class provides functionality for deleting calendar entries.
*/
class CCalendarDeleteEntry : public CCalendarASyncRequest/*, public CActive*/
	{

	/**
	 * TDeleteOption enum represents the delete options.
	*/
	enum TDeleteOption
		{
		EDeleteAll = 0,
		EDeleteGUid,
		EDeleteLUid,
		EDeleteTimeRange,
		EDeleteTmRngGUid,
		EDeleteTmRngLUid
		};
		
	public:
	
		/**
		* Two-phased constructor.
		* @param CCalendarSessionInfo* a calendar session information.
		* @param aFilter* Filter object. Function takes the ownership.
		* @param MCalCallbackBase* 
		*/
		static CCalendarDeleteEntry* NewL( CCalendarSessionInfo* aSessionInfo, 
											CCalendarFilter* aFilter, 
											CAsyncRequestObserver* aAsyncRequestObserver = NULL,
											MCalCallbackBase* aNotifyCallback = NULL );
		
	    /**
	    * Destructor.
	    */
		virtual ~CCalendarDeleteEntry();

		/**
		* Delete Entries
		*/
		void DeleteL();
		
	private:

		/** 
	     * Default  constructor.
	     * @param aSessionInfo  It is an object of CCalSession Class which
	     *        represents a channel of communication between a client thread  
	     *        and the calendar Server thread .
	     * @param aNotifyCallback It is a callback notification
	    */
		CCalendarDeleteEntry( CCalendarSessionInfo* aSessionInfo, 
										CAsyncRequestObserver* aAsyncRequestObserver = NULL, 
										MCalCallbackBase* aNotifyCallback = NULL );

		void ConstructL( CCalendarFilter* aFilter );
		/** 
	     * Initializes delete option based in input filter
	    */
		void InitializeDeleteOptionL();

		/**
		* Start Deleting Entries
		*/
		void StartDeleteL();

		/**
		* Delete All Entries with in calendar
		*/
		void DeleteAllL();

		/**
		* Delete Entries based in GlobalUid/LocalUid
	     * @param aLocalUid Deletion will Local Uid based if this is true.
		*/
		void DeleteUidL( TBool aLocalUid );

		/**
		* Delete Instances based on Time Range
		*/
		void DeleteTimeRangeL();

		/**
		* Delete Instances based on Time Range and Global Uid
		*/
		void DeleteTimeRangeWithGlobalUidL();

		/**
		* Delete Instances based on Time Range and Local Uid
		*/
		void DeleteTimeRangeWithLocalUidL();

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
		 * Not own.
		*/ 
		CCalendarSessionInfo* iSessionInfo;

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

		/**
		 * Delete option selected, derived from Filter
		*/ 
		TDeleteOption iDeleteOption;
	};




#endif __CALENDARDELETEENTRY_H