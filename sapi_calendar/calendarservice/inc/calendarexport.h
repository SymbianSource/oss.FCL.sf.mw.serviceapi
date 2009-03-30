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
* Description:  Interface to Exporting the contents of a Calender
*
*/



#ifndef CALENDAREXPORTEXPORT_H_
#define CALENDAREXPORTEXPORT_H_

//System Includes
#include <e32base.h>


//Forward Declarations
class CCalSession;
class CCalEntryView;
class CCalenExporter;
class CCalendarSessionInfo;
class MCalCallbackBase;

class CAsyncRequestObserver;
class CCalendarExportParams;

/**
 *  This class provides functionality for Calendar Export
 *  provides Six versions of Export Functionality Sync and Async (3 versions for each)
 *  @since S60_3_2_200726
 */
class CCalendarExport : public CCalendarASyncRequest/*, public CActive*/
	{

	public: //*********************Public Members(Behaviours)******************************************/
	
		/**
		 * Static Method which either returns the Two Phase constructed Object or Leave 
		 *
		 * @param CCalendarSessionInfo  to set the iCalenderSessionInfo which is used to access various resources
		 *										like CCalSession, CCalEntryView etc
		 * @param aFormat used to set the iFormat it can be either ICAL or VCAL, two popular Calendar formats
		 * 
		 * @param MAsyncRequestObserver For ASyncronous usage of this Object this paramater is set / Default is NULL
		 *											Set in case of Asynchronous call only
		 * @param MCalCallbackBase      For Asyncronous usage of this Object this paramater is set
		 *				
		 * @return CCalendarExport
		 */
		static CCalendarExport* NewL ( CCalendarSessionInfo* aCalSessionInfo, 
											const TDesC8& aFormat, 
											CCalendarExportParams* aParams,
											CAsyncRequestObserver* aAsyncRequestObserver = NULL,
											MCalCallbackBase* aCallBack = NULL );

		/**
		 * Destructor.
		 */
		~CCalendarExport();
		
		/**
     	  * Synchronous Version of Export which decides the flow basing on the inputs set at the time of Construction 
		  *					    of this object through NewL and generates corresponding entries in an Ouput Buffer
          * @since S60_3_2_200726
          * @param aOutputBuffer    This Buffer contains the Output (Exported from the calender)
          *
          * @return void
          */
		void ExportL( HBufC8*& aOutputBuffer );

		/**
     	  * ASynchronous Version of Export Exports entries basing on the input set at the time of construction of this object througn NewL
     	  *				all the entries of the Calender(outputis passed through callback)
     	  *	
     	  * @since S60_3_2_200726
     	  *
          * @return void
          */
		void ExportL();
		

	private: //*********************Private Member(Behaviours)******************************************/
	
	    /** 
          * Constructor.
      	  * @param CCalendarSessionInfo  to set the iCalenderSessionInfo which is used to access various resources
		  *										like CCalSession, CCalEntryView etc
		  * @param CAsyncRequestObserver For ASyncronous usage of this Object this paramater is set / Default is NULL
		  *											Set in case of Asynchronous call only
		  * @param MCalCallbackBase      For Asyncronous usage of this Object this paramater is set
     	  */
		CCalendarExport( CCalendarSessionInfo* aCalSessionInfo, CAsyncRequestObserver* aAsyncRequestObserver = NULL, 
																MCalCallbackBase* aCallBack = NULL );
		
		/** 
          * 2nd Phase of Two Phase Construction
          *
     	  * @param aFormat used to set the iFormat it can be either ICAL or VCAL, two popular Calendar formats  
		  *												a local copy is made	
		  * NOTE: Ownership of any of the parameters is not taken through this function call
		  * @return void				
     	  */
		void ConstructL( const TDesC8& aFormat, CCalendarExportParams* aParams );
		
		/**
     	  * Internal Function ExportToBuffer which is called to actually export the data to Buffer
          *
          * @since S60_3_2_200726
          * @param aCalEntryArray 	Calender Entries of the Items to be exported to the Output Buffer
          *
          * @param aOutputBuffer 	This Buffer contains the Output (Exported from the calender)
          *
          * @return void
          */
		void ExportToBufferL( const RPointerArray<CCalEntry>& aCalEntryArray, HBufC8*& aOutputBuffer );
		
		/**
     	  * Internal Function For fetching all CCalEntries of the Calender and call ExportToBuffer
          * (this is called in case of both Synchronous(EXPORTL where no Local or Global UIDs are specified)and from RUNL of Asynchronous)
          * @since S60_3_2_200726
          *
          * @param aOutputBuffer 	This Buffer contains the Output (Exported from the calender)
          *
          * @return void
          */
		void GetCalEntriesAndExportL(HBufC8*& aOutputBuffer);
		
		/**
     	  * Internal Function For Conversion of LocalUIDS to CCalEntry and call ExportToBuffer
          * (this is called in case of Asynchronous from RUNL)
          * @since S60_3_2_200726
          *
          * @param aOutputBuffer 	This Buffer contains the Output (Exported from the calender)
          *
          * @return void
          */
		void ConvertLUIDAndExportL(HBufC8*& aOutputBuffer);
		
		/**
     	  * Internal Function For Conversion of GlobalUIDS to CCalEntry and call ExportToBuffer
          * (this is called in case of Asynchronous from RUNL)
          * @since S60_3_2_200726
          *
          * @param aOutputBuffer 	This Buffer contains the Output (Exported from the calender)
          *
          * @return void
          */
		void ConvertGUIDAndExportL(HBufC8*& aOutputBuffer);
		
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
     	  * Handle to the Library Class Object which provies the Conversion functionality i.e.., export
     	  * Own. This class is responsible for deleting it. HAS A Relationship
     	  */
		CCalenExporter *iCalenExporter; 
	
		/**
     	  * Handle to the Library Class Object which provies the Conversion functionality i.e.., export
     	  * Own. This class is responsible for deleting it. HAS A Relationship
     	  */
		HBufC8* iFormat;
	
		/**
     	  * Handle to the input params. This class takes the responsibility for deleting it. HAS A Relationship
     	  */
		CCalendarExportParams* iParams;

		/**
     	  * Output Buffer used only in case of Asynchronous calls
     	  * Own. This class takes the responsibility for deleting it. HAS A Relationship
     	  */	
		HBufC8* iOutputBuffer;
		
	};
	

#endif CALENDAREXPORTEXPORT_H_