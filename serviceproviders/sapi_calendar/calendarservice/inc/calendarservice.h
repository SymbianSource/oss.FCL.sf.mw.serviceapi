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


#ifndef __CALENDARSERVICE_H
#define __CALENDARSERVICE_H

class CAsyncRequestObserver;
class CEntryAttributes;
class CCalendarSessionInfo;

/**
 * Calendar Service class. Perfoms various operations on calendar / calendar entries.
*/
class CCalendarService : public CBase
	{
	public:

		/**
		 * Two Phase Constructor
		*/ 
		IMPORT_C static CCalendarService* NewL();

		/**
		 * Destructor
		*/ 
		virtual ~CCalendarService();

	private:

		/**
		 * Constructor
		*/ 
		CCalendarService();

		/**
		 * Constructor
		*/ 
		void ConstructL();
		
		/**
		 * Adds asynchronous request object
		 * @param aTransactionId Transcation Id os Async object
		 * @param aAsyncObj  Async object
		*/ 
		void AddAsyncObjL( const TInt32 aTransactionId, CCalendarASyncRequest* aAsyncObj );

		/**
		 * Returns session info for the given calendar
		 * @param aCalendar Calendar Name
		 * @return CCalendarSessionInfo* Session info object
		*/ 
		CCalendarSessionInfo* CalendarSessionInfoL( const TDesC& aCalendar );

		/**
		 * Removes Session info object
		 * @param aCalendar Calendar session to be removed
		 * @return void
		*/ 
		void RemoveSessionInfo( const TDesC& aCalendar );
		
	public:

		/**
		 * Returns list of available calendars in device.
		 * @param aDefault Flag for getting default calendar only
		 * @param aCalendarList Calendar List
		*/ 
		IMPORT_C void GetListL( CDesCArray*&  aCalendarList, const TBool aDefault = EFalse );

		/**
		 * Returns list of calendar entries from given calendar with the given Global UID.
		 * @param aCalendarName Calendar Name
		 * @param aGuid Global UID
		 * @param aEntryList output param gives Calendar Entry List
		*/ 
		IMPORT_C void GetListL( const TDesC& aCalendarName, const TDesC8& aGuid, RPointerArray<CCalEntry>& aEntryList);

		/**
		 * Returns list of calendar entries from given calendar with the given Local UID.
		 * @param aCalendarName Calendar Name
		 * @param aLocalUid Local UID
		 * @param aEntryList output param gives Calendar Entry List
		*/ 
		IMPORT_C void GetListL( const TDesC& aCalendarName, const TCalLocalUid aLocalUid, RPointerArray<CCalEntry>& aEntryList);

		/**
		 * Returns list of calendar instance from given calendar with the given Filter.
		 * @param aCalendarName Calendar Name
		 * @param aFilter Filter, Ownership is passed
		 * @param aInstanceList output param gives Calendar Instance List
		*/ 
		IMPORT_C void GetListL( const TDesC& aCalendarName, CCalendarFilter* aFilter, RPointerArray<CCalInstance>& aEntryList);

		/**
		 * Add new calendar in device.
		 * @param aCalendarName Calendar Name
		*/ 
		IMPORT_C void AddL( const TDesC& aCalendarName );

		/**
		 * Add new entry to given calendar.
		 * @param aCalendarName Calendar Name
		 * @param aCalendarData Entry data, Ownership is passed
		 * @param aUidAdded Uid for newly added entry
		*/ 
		IMPORT_C void AddL( const TDesC& aCalendarName, CEntryAttributes* aCalendarData, TUIDSet*& aUidAdded );

		/**
		 * Remove calendar from the device. Deletion of defaut calendar is not supported
		 * @param aCalendarName Calendar Name
		*/ 
		IMPORT_C void DeleteL( const TDesC& aCalendarName );

		/**
		 * Remove entries from the given calendar based on input filter
		 * @param aCalendarName Calendar Name
		 * @param aFilter Filter, Ownership is passed
		 * @param aCallback CallBack for asynchronous requests, Ownership is passed
		*/ 
		IMPORT_C void DeleteL(  const TDesC& aCalendarName, CCalendarFilter* aFilter, MCalCallbackBase* aCallback = NULL );


        /**
		 * ASynchronous Version of Import: Imports the contents specified in the InputBuffer complaining to aFormat to aCalendarName
		 * @param aCalendarName Calendar Name
		 * @param aFormat used to set the iFormat it can be either ICAL or VCAL, two popular Calendar formats
		 * @param aInputBuffer contains the data to be imported to the specified calendar
		 * @param aCallBack   For ASyncronous usage of this Object this paramater is mandatory to be set
		 *
		 * @return void
		 */
		IMPORT_C void ImportL( const TDesC& aCalendarName, const TDesC8& aFormat, const TDesC8& aInputBuffer, MCalCallbackBase* aCallBack );

        /**
		 * ASynchronous Version of Import: Imports the contents specified in the InputBuffer complaining to aFormat to aCalendarName
		 * @param aCalendarName Calendar Name
		 * @param aFormat used to set the iFormat it can be either ICAL or VCAL, two popular Calendar formats
		 * @param aImportFile File from where entries needs to be imported
		 * @param aCallBack   For ASyncronous usage of this Object this paramater is mandatory to be set
		 *
		 * @return void
		 */
		IMPORT_C void ImportL( const TDesC& aCalendarName, const TDesC8& aFormat, const TDesC& aImportFile, MCalCallbackBase* aCallBack );

		/**
		 * Synchronous Version of Import: Imports the contents specified in the InputBuffer complaining to aFormat to aCalendarName
		 * @param aCalendarName Calendar Name
		 * @param aFormat used to set the iFormat it can be either ICAL or VCAL, two popular Calendar formats
		 * @param aInputBuffer contains the data to be imported to the specified calendar
		 * @param aCUIDSet contains the GUids and LUids of the imported entries from inputbuffer
		 *				
		 * @return void
		 */
		IMPORT_C void ImportL( const TDesC& aCalendarName, const TDesC8& aFormat, const TDesC8& aInputBuffer, RPointerArray<TUIDSet>& aUIDSet );	
			
		/**
		 * Synchronous Version of Import: Imports the contents specified in the InputBuffer complaining to aFormat to aCalendarName
		 * @param aCalendarName Calendar Name
		 * @param aFormat used to set the iFormat it can be either ICAL or VCAL, two popular Calendar formats
		 * @param aImportFile File from where entries needs to be imported
		 * @param aCUIDSet contains the GUids and LUids of the imported entries from inputbuffer
		 *				
		 * @return void
		 */
		IMPORT_C void ImportL( const TDesC& aCalendarName, const TDesC8& aFormat, const TDesC& aImportFile, RPointerArray<TUIDSet>& aUIDSet );	

		/**
     	 * Synchronous Version of Export which Exports the data from aCalendarName in aFormat to aOutputBuffer 
		 * @param aCalendarName Calendar Name
		 * @param aFormat used to set the iFormat it can be either ICAL or VCAL, two popular Calendar formats
		 * @param aParams used to specify the GUIDS or LUIDS in it or nulll signify all entries to be exported
		 * @param aOutputBuffer    This Buffer contains the Output (Exported from the calender)				
		 *
		 * @return void
		 */
		IMPORT_C void ExportL( const TDesC& aCalendarName, const TDesC8& aFormat, CCalendarExportParams* aParams, HBufC8*& aOutputBuffer );
		
		/**
     	 * ASynchronous Version of Export which Exports the data from aCalendarName in aFormat to HBufC8*(which is sent througn callback mehcnism) 
		 * @param aCalendarName Calendar Name
		 * @param aFormat used to set the iFormat it can be either ICAL or VCAL, two popular Calendar formats
		 * @param aParams used to specify the GUIDS or LUIDS in it or nulll signify all entries to be exported
		 * @param aCallBack   For ASyncronous usage of this Object this paramater is mandatory to be set				
		 *
		 * @return void
		 */
		IMPORT_C void ExportL( const TDesC& aCalendarName, const TDesC8& aFormat, CCalendarExportParams* aParams, MCalCallbackBase* aCallBack );

		/**
		 * Start Notification for changes in given calendar
		 * @param aCalendarName Calendar Name
		 * @param aFilter Filter, Ownership is passed
		 * @param aCallback CallBack for asynchronous requests, Ownership is passed
		*/ 
		IMPORT_C void StartChangeNotifyL( const TDesC& aCalendarName, CCalendarFilter* aFilter, MCalCallbackBase* aCallback );

		/**
		 * Cancels asynchronous request
		 * @param aTransactionId     asynchronous transaction id
		 * @param aResult        error code
		*/ 				
		IMPORT_C TInt Cancel( TInt32 aTransectionID );


	private:
		
		/**
		 * Represents a channel of communication between a client thread 
		 * and the Calendar Server thread.
	  	*/ 
		RPointerArray< CCalendarSessionInfo > iArraySessionInfo;
		
		/**
		 * Asynchronous request observer
	  	*/ 
		CAsyncRequestObserver* 		iAsyncReqObserver;
	};


#endif __CALENDARSERVICE_H