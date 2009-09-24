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

#ifndef CALENDARGETLIST_H_
#define CALENDARGETLIST_H_


//System Includes
#include <e32base.h>


//Forward Declarations
class CCalSession;
class CCalEntryView;
class CCalendarSessionInfo;
class MCalCallbackBase;
class CCalendarFilter;
class CCalEntry;
class CCalInstance;

/**
 *  This class provides functionality for Calendar GetList
 *  provides four versions of GetList Functionality Sync and Async 
 *  @since S60_3_2_200726
 */
class CCalendarGetList : public CCalendarASyncRequest/*, public CActive*/
	{
	
    enum TGetListOption
        {
        EGetListAll = 0,
        EGetListGUid,
        EGetListLocalUid,
        EGetListTimeRange,
        };
	
	public: //*********************Public Members(Behaviours)******************************************/
	
		/**
		 * Static Method which either returns the Two Phase constructed Object or Leave 
		 *
		 * @param CCalendarSessionInfo  to set the iCalenderSessionInfo which is used to access various resources
		 *										like CCalSession, CCalEntryView etc
		 * @param aFormat used to set the iFormat it can be either ICAL or VCAL, two popular Calendar formats
		 *
		 * @param aInputBuffer contains the data to be GetListed to the specified calendar
		 * 
		 * @param CAsyncRequestObserver For ASyncronous usage of this Object this paramater is set / Default is NULL
		 *											Set in case of Asynchronous call only
		 * @param MCalCallbackBase      For Asyncronous usage of this Object this paramater is set
		 *				
		 * NOTE: Ownership of any of the parameters is not taken through this function call
		 * NOTE: Therefore the User of this function needs to take care of neccessary cleanup of passed parameters		
		 * @return CCalendarExport
		 */
		static CCalendarGetList* NewL ( CCalendarSessionInfo* aCalSessionInfo,  
                                        const TDesC8& aGuid, 
										CAsyncRequestObserver* aAsyncRequestObserver = NULL,
										MCalCallbackBase* aCallBack = NULL );

			static CCalendarGetList* NewL ( CCalendarSessionInfo* aCalSessionInfo,  
                                        const TCalLocalUid aLocalUid, 
										CAsyncRequestObserver* aAsyncRequestObserver = NULL,
										MCalCallbackBase* aCallBack = NULL );
		
		static CCalendarGetList* NewL ( CCalendarSessionInfo* aCalSessionInfo,  
                                        CCalendarFilter* aFilter, 
		                                CAsyncRequestObserver* aAsyncRequestObserver = NULL,
		                                MCalCallbackBase* aCallBack = NULL );								
		/**
		 * Destructor.
		 */
		~CCalendarGetList();

        /**
         * Inherited from MAsyncRequest class 
         */ 
        void CancelRequest();

        /**
           * Inherited from MAsyncRequest class.
        */
      //  TInt32 GetTransactionID();
		
		/**
     	  * Synchronous Version of GetList which takes InputBuffer set at the time of Construction of this object through NewL
     	  * and GetLists them to the Calender opened in CalSession of CalendarSessionInfoL object passed to this object
          * It sets the LUids and GUids in the aOutputLocalUidArray, this object is not the owner of aOutputLocalUidArray
          * @since S60_3_2_200726
          *
          * @param aOutputLocalUidArray 	Output which is the array of LocalUIDs after StoreL on the Calender file
          *
          * @return void
          */
		void GetListL(const TDesC8& aGuid, RPointerArray<CCalEntry>& aEntryList );
		
		void GetListL(const TCalLocalUid aLocalUid, RPointerArray<CCalEntry>& aEntryList );
		
		void GetListL( RPointerArray<CCalInstance>& aInstanceList );
	
		/**
     	  * ASynchronous Version of GetList which takes InputBuffer set at the time of Construction of this object through NewL
     	  *                     and GetLists to the Calender(outputis passed through callback)
          *
          * @since S60_3_2_200726
          *
          * @return void
          */
		void GetListL();
		
	private: //*********************Private Member(Behaviours)******************************************/
	
	   /** 
          * Constructor.
      	  * @param CCalendarSessionInfo  to set the iCalenderSessionInfo which is used to access various resources
		  *										like CCalSession, CCalEntryView etc
		  * @param CAsyncRequestObserver For Asyncronous usage of this Object this paramater is set / Default is NULL
		  * @param MCalCallbackBase      For Asyncronous usage of this Object this paramater is set
     	  */
	    CCalendarGetList( CCalendarSessionInfo* aCalSessionInfo,
						 CAsyncRequestObserver* aAsyncRequestObserver = NULL,
						 MCalCallbackBase* aCallBack = NULL );
		
		/** 
          * 2nd Phase of Two Phase Construction
 		  * @param aFormat used to set the iFormat it can be either ICAL or VCAL, two popular Calendar formats
		  *
		  * @param aInputBuffer contains the data to be GetListed to the specified calendar
		  * @return void
     	  */
		void ConstructL( const TDesC8& aGuid );
		void ConstructL( const TCalLocalUid aLocalUid );
		void ConstructL( CCalendarFilter* aFilter );
        /** 
          * Service Functions to Enable Proper Completion of Asynchronous Request called at the end of RUNL to send output
          * @param aReason  Give the reason it can be KErrNone or any error
          *
          * @return void
          */
        void NotifyRequestResult( TInt aReason );
        /**
          * Inherited from CActive class...Active Object for Aynchronous Support 
          */ 
        virtual void DoCancel();
       

        /** 
         * Initializes delete option based in input filter
        */
        void InitializeGetListOption();

        /**
        * Start Fetching Entries
        */
        void StartFetchingL();

        /**
        * Gets Entries based on GUid
        */
        void GetGUidL();
        /**
        * Gets Entries based on LocalUid
        */
        void GetLocalUidL();

        /**
        * Delete Instances based on Time Range
        */
        void GetTimeRangeL();

		/**
		 * Inherited from CActive class...Active Object for Aynchronous Support
		 */ 
		virtual void RunL();
		
		/** 
          * Service Functions to activate the Asynchronous Request by activating the Active Object using SetActive()
      	  * @param aReason  Give the reason it can be KErrNone or any error
		  *
		  * @return void
     	  */
		void ActivateRequest( TInt aReason );
				
	private: //*********************Private Member(Properties)******************************************/
			
		/**
          * This is the handle to CCalendarSessionInfo Service class which is used to access various resources
		  *										like CCalSession, CCalEntryView etc
		  * Pure USES A Relalationship...This class doesnot own this and So, it wont delete it
          */	
		CCalendarSessionInfo* iSessionInfo ; 
		
		/**
     	  * For Syncronous usage of this Object this paramater is set / Default is NULL
     	  * Own. This class is responsible for deleting it. HAS A Relationship
     	  */
		MCalCallbackBase* iCallBack;
		
		
		/**
     	  * For Syncronous usage of this Object this paramater is set / Default is NULL
     	  * Own. This class is responsible for deleting it. HAS A Relationship
     	  */
		
		CAsyncRequestObserver* iAsyncRequestObserver;

        /**
         * Filter Object
        */ 
        CCalendarFilter* iFilter;
        HBufC8* iGuid;
        TUint32 iLocalUid;
		
        TGetListOption iGetListOption;
	
        RPointerArray<CCalEntry> iEntryList;
        
        RPointerArray<CCalInstance> iInstanceList;
	};
	

#endif CALENDARGETLIST_H_
