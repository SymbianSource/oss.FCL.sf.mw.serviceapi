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
* Description:  Interface to Importing the contents to a Calender
*
*/


#ifndef CALENDARIMPORTEXPORT_H_
#define CALENDARIMPORTEXPORT_H_


//System Includes
#include <e32base.h>


//Forward Declarations
class CCalSession;
class CCalEntryView;
class CCalenImporter;
class CCalendarSessionInfo;
class MCalCallbackBase;

/**
 *  This class provides functionality for Calendar Import
 *  provides four versions of Import Functionality Sync and Async 
 *  @since S60_3_2_200726
 */
class CCalendarImport : public CCalendarASyncRequest/*, public CActive*/
	{
	
	
	public: //*********************Public Members(Behaviours)******************************************/
	
		/**
		 * Static Method which either returns the Two Phase constructed Object or Leave 
		 *
		 * @param CCalendarSessionInfo  to set the iCalenderSessionInfo which is used to access various resources
		 *										like CCalSession, CCalEntryView etc
		 * @param aFormat used to set the iFormat it can be either ICAL or VCAL, two popular Calendar formats
		 *
		 * @param aInputBuffer contains the data to be imported to the specified calendar
		 * 
		 * @param CAsyncRequestObserver For ASyncronous usage of this Object this paramater is set / Default is NULL
		 *											Set in case of Asynchronous call only
		 * @param MCalCallbackBase      For Asyncronous usage of this Object this paramater is set
		 *				
		 * NOTE: Ownership of any of the parameters is not taken through this function call
		 * NOTE: Therefore the User of this function needs to take care of neccessary cleanup of passed parameters		
		 * @return CCalendarExport
		 */
		static CCalendarImport* NewL ( CCalendarSessionInfo* aCalSessionInfo,  
										const TDesC8& aFormat, 
										const TDesC8& aInputBuffer, 
										CAsyncRequestObserver* aAsyncRequestObserver = NULL,
										MCalCallbackBase* aCallBack = NULL );

		static CCalendarImport* NewL ( CCalendarSessionInfo* aCalSessionInfo,  
										const TDesC8& aFormat, 
										const TDesC& aImportFile, 
										CAsyncRequestObserver* aAsyncRequestObserver = NULL,
										MCalCallbackBase* aCallBack = NULL );
										
		/**
		 * Destructor.
		 */
		~CCalendarImport();
		
		/**
     	  * Synchronous Version of Import which takes InputBuffer set at the time of Construction of this object through NewL
     	  * and Imports them to the Calender opened in CalSession of CalendarSessionInfoL object passed to this object
          * It sets the LUids and GUids in the aOutputLocalUidArray, this object is not the owner of aOutputLocalUidArray
          * @since S60_3_2_200726
          *
          * @param aOutputLocalUidArray 	Output which is the array of LocalUIDs after StoreL on the Calender file
          *
          * @return void
          */
		void ImportL( RPointerArray<TUIDSet>& aOutputLocalUidArray );
	
		/**
     	  * ASynchronous Version of Import which takes InputBuffer set at the time of Construction of this object through NewL
     	  *                     and Imports to the Calender(outputis passed through callback)
          *
          * @since S60_3_2_200726
          *
          * @return void
          */
		void ImportL();
		
	private: //*********************Private Member(Behaviours)******************************************/
	
	   /** 
          * Constructor.
      	  * @param CCalendarSessionInfo  to set the iCalenderSessionInfo which is used to access various resources
		  *										like CCalSession, CCalEntryView etc
		  * @param CAsyncRequestObserver For Asyncronous usage of this Object this paramater is set / Default is NULL
		  * @param MCalCallbackBase      For Asyncronous usage of this Object this paramater is set
     	  */
		CCalendarImport( CCalendarSessionInfo* aCalSessionInfo,
						 CAsyncRequestObserver* aAsyncRequestObserver = NULL,
						 MCalCallbackBase* aCallBack = NULL );
		
		/** 
          * 2nd Phase of Two Phase Construction
 		  * @param aFormat used to set the iFormat it can be either ICAL or VCAL, two popular Calendar formats
		  *
		  * @param aInputBuffer contains the data to be imported to the specified calendar
		  * @return void
     	  */
		void ConstructL( const TDesC8& aFormat, const TDesC8& aInputBuffer );
		void ConstructL( const TDesC8& aFormat, const TDesC& aImportFile );

		/**
		 * Inherited from CActive class...Active Object for Aynchronous Support 
		 */ 
		virtual void DoCancel();

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
				
		/** 
          * Service Functions to Enable Proper Completion of Asynchronous Request called at the end of RUNL to send output
      	  * @param aReason  Give the reason it can be KErrNone or any error
		  *
		  * @return void
     	  */
		void NotifyRequestResult( TInt aReason );
		
		void ImportFromStreamL(RReadStream& aStream,  RPointerArray<TUIDSet>& aOutputUIDArray );

		

	private: //*********************Private Member(Properties)******************************************/
			
		/**
          * This is the handle to CCalendarSessionInfo Service class which is used to access various resources
		  *										like CCalSession, CCalEntryView etc
		  * Pure USES A Relalationship...This class doesnot own this and So, it wont delete it
          */	
		CCalendarSessionInfo* iCalSessionInfo; 
		
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
     	  * Handle to the Library Class Object which provies the Conversion functionality i.e.., Import
     	  * Own. This class is responsible for deleting it. HAS A Relationship
     	  */
		CCalenImporter *iCalenImporter; 
		
		/**
     	  * Handle to the Library Class Object which provies the Conversion functionality i.e.., export
     	  * Own. This class is responsible for deleting it. HAS A Relationship
     	  */
		HBufC8* iFormat;
	
	
		/**
     	  * InputBuffer used in case of Asynchronous calls
     	  * Own. This class takes the responsibility for deleting it. HAS A Relationship
     	  */
		HBufC8* iInputBuffer;

		HBufC* iImportFile;
	
		/**
     	  * Output Local(TUint) and Global UID(TDesC8) array used in case of Asynchronous calls
     	  * Own. This class takes the responsibility for deleting it. HAS A Relationship
     	  */
		RPointerArray<TUIDSet> iOutputUIDArray;
	};
	

#endif CALENDARIMPORTEXPORT_H_