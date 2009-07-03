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
* Description:  Support for header information retrieval 
*
*/


#ifndef __CALENDARHEADER_H
#define __CALENDARHEADER_H

#include <e32base.h>
#include <badesca.h>
#include <calcommon.h>

class CCalSession;
class CCalEntryView;
class CCalInstanceView;
class CCalenInterimUtils2;
class CCalEntry;
class CCalInstance;

/**
 * struct to Output Details of the Imported Entries Both LocalUid and Global UID
*/
struct TUIDSet 
	{
	
	TCalLocalUid iLocalUID;
	HBufC8*  iGlobalUID;
	
	TUIDSet():iGlobalUID(NULL){}
	
	~TUIDSet()
		{
		delete iGlobalUID;
		}
	};

/**
 * Contains information about session for a calendar
*/
class CCalendarASyncRequest : public CActive
	{
	protected: 
		CCalendarASyncRequest():CActive( EPriorityStandard )
			{
			}
			
	public:	
		virtual TBool IsInProgress() 
			{
			return EFalse;
			}
	};

/**
 * Contains information about session for a calendar
*/
class CCalendarSessionInfo : public CBase
	{
	public: 

		/**
		 * Two Phase Constructor
		*/ 
		static CCalendarSessionInfo* NewL( const TDesC& aCalendar );

		/**
		 * Destructor
		*/ 
		~CCalendarSessionInfo();
		
		/**
		 * Returns the calendar Name
		 * @return Calendar Name to which this object is associated
		*/ 
		TPtrC Calendar();

		/**
		 * Returns the calendar session
		 * @return Calendar session
		*/ 
		CCalSession* Session();

		/**
		 * Returns the calendar entry view
		 * @return Calendar entry view
		*/ 
		CCalEntryView* EntryView();

		/**
		 * Returns the calendar instance view
		 * @return Calendar instance view
		*/ 
		CCalInstanceView* InstanceView();
		
	private:
	
		/**
		 * Constructor
		*/ 
		CCalendarSessionInfo();
		
		/**
		 * Two Phase Constructor
		 * @param aCalendar Calendar name
		 * @return void
		*/ 
		void ConstructL( const TDesC& aCalendar );
		
		
	private:

		/**
		 * Calendar Name
	  	*/ 
		HBufC* 				iCalName;

		/**
		 * Calendar Session
	  	*/ 
		CCalSession*		iCalSession;

		/**
		 * Calendar Entry View
	  	*/ 
		CCalEntryView*		iCalEntView;

		/**
		 * Calendar Instance View
	  	*/ 
		CCalInstanceView*	iCalInstView;
		
	};
	
/**
 * Calendar Filer options
*/
enum TCalendarFilerFlags
	{
	EFilterGUid		= 0x1,
	EFilterLUid		= 0x2,
	EFilterText 	= 0x4,
	EFilterType		= 0x8,
	EFilterStTime 	= 0x10,
	EFilterEndTime 	= 0x20,
	EFlagDeleteAll 	= 0x40,
	EFlagUnDateToDo	= 0x80,
	};	
	
/**
 * Contains Filter information for an operation(GetList/Delete/ChangeNotification)
*/
class CCalendarFilter : public CBase
	{
	public:

		/**
		 * Two Phase Constructor
		*/ 
		IMPORT_C static CCalendarFilter* NewL();

		/**
		 * Destructor
		*/ 
		~CCalendarFilter();

		/**
		 * Sets Start time for time range 
		 * @param aStartTime Start Time
		 * @return void
		*/ 
		IMPORT_C void SetStartTimeL( const TTime& aStartTime );

		/**
		 * Sets End time for time range 
		 * @param aEndTime Start Time
		 * @return void
		*/ 
		IMPORT_C void SetEndTimeL( const TTime& aStartTime );

		/**
		 * Sets Filter type
		 * @param aFilterType filter type
		 * @return void
		*/ 
		IMPORT_C void SetFilterTypeL( const TDesC& aFilterType );

		/**
		 * Sets Filter text
		 * @param aTextToSearch Filter text
		 * @return void
		*/ 
		IMPORT_C void SetFilterTextL( const TDesC& aTextToSearch );

		/**
		 * Adds Global Uid to filter criteria
		 * @param aGuid Global Uid
		 * @return void
		*/ 
		IMPORT_C void AddGuidL( const TDesC8& aGuid );

		/**
		 * Adds Local Uid to filter criteria
		 * @param aLocalUid Local Uid
		 * @return void
		*/ 
		IMPORT_C void AddLocalUid( const TCalLocalUid aLocalUid );

		/**
		 * Sets Delete all flag. Valid for Remove operations only.
		 * @param aDeleteAll Delete All flag
		 * @return void
		*/ 
		IMPORT_C void SetDeleteAll( TBool aDeleteAll = ETrue );

		/**
		 * Sets IncludeUnDateToDo to filter.Valid for Change Notification cmd only.
		 * @param aInclude 
		 * @return void
		*/ 
		IMPORT_C void SetIncludeUnDateToDo( TBool aInclude = ETrue );
		
		/**
		 * Returns time range 
		 * @return CalCommon::TCalTimeRange 
		*/ 
		IMPORT_C CalCommon::TCalTimeRange TimeRange() const;
		
		/**
		 * Returns Entry type filter
		 * @return TUint 
		*/ 
		IMPORT_C TUint FilterType() const;

		/**
		 * Returns filter text
		 * @return TPtrC 
		*/ 
		IMPORT_C TPtrC FilterText() const;

		/**
		 * Returns Global UID list
		 * @return CDesC8Array* 
		*/ 
		IMPORT_C const CDesC8Array* GuidList() const;

		/**
		 * Returns Local Uid List
		 * @return RArray<TCalLocalUid>
		*/ 
		IMPORT_C const RArray<TCalLocalUid>& LocalUidList() const;

		/**
		 * Returns Filter options selected
		 * @return TInt32
		*/ 
		IMPORT_C TInt32 Filter() const;
		
	
        /** 
        * Assignment operator. 
        * @param aFilterParamInfo Item to assign.
        * @return The source object.
        */
		CCalendarFilter& operator=(const CCalendarFilter& aFilterParamInfo);
		
	private:
	
		/**
		 * Constructor
		*/ 
		CCalendarFilter();
		
		/**
		 * Constructor
		*/ 
		void ConstructL();

	private:
	
		/**
		 * Global Uid List
		*/ 
		CDesC8Array* iGuidList;

		/**
		 * Local Uid List
		*/ 
		RArray<TCalLocalUid> iLocalUidList;		
	
		/**
		 * Start time
		*/ 
		TCalTime 	iStartTimeRange;

		/**
		 * End time
		*/ 
		TCalTime 	iEndTimeRange;

		/**
		 * Filter Type
		*/ 
		TUint 		iFilterType;

		/**
		 * Filter text
		*/ 
		HBufC*		iTextToSearch;
		
		/**
		 * Filter options selected
		*/ 
		TInt32		iFilterFlags;
	};

/**
 * Callback base class
*/
class MCalCallbackBase 
	{
	public:

	/**
	   * Gives the result
	   * @param aErrCode Error code
	   * @param aResult Result 
	   * @return void
  	*/
		virtual void NotifyResultL(TInt aErrCode, TAny* aResult) = 0;
		
	/**
	  * Input param 
  	*/		
		const TAny* iPtrInParamList; 

	/**
	  * Callback 
  	*/		
		TAny* iPtrNotifyCallback; 
		
	/**
	  * Transaction Id
  	*/		
		TInt32 iTransactionId;
	};
	
	

/**
 * Contains Input Params information for Export
*/
class CCalendarExportParams : public CBase
	{
	
	public:
	
		/**
		 * Calendar Export Parameter options
		*/
		enum TCalendarExportParams
			{
			EParamsGUid				= 0x1,
			EParamsLUid				= 0x2,
			EParamsFileName		 	= 0x4,
			};
			

		/**
		 * Two Phase Constructor
		*/ 
		IMPORT_C static CCalendarExportParams* NewL();

		/**
		 * Destructor
		*/ 
		~CCalendarExportParams();

		/**
		 * Adds Global Uid to Params
		 * @param aGuid Global Uid
		 * @return void
		*/ 
		IMPORT_C void AddGuidL( const TDesC8& aGuid );

		/**
		 * Adds Global Uid to Params
		 * @param CDesC8Array*
		 * @return void
		*/ 
		IMPORT_C void AddGuidL( const CDesC8Array* aInputGUIDArray );
		
		/**
		 * Adds Local Uid to Params
		 * @param aLocalUid Local Uid
		 * @return void
		*/ 
		IMPORT_C void AddLocalUid( const TCalLocalUid aLocalUid );

		/**
		 * Adds Local Uid to Params
		 * @param RArray<TCalLocalUid>&
		 * @return void
		*/ 
		IMPORT_C void AddLocalUid( const RArray<TCalLocalUid>& aInputLocalUIDArray );
		
		/**
		 * Adds Local Uid to Params
		 * @param aLocalUid Local Uid
		 * @return void
		*/ 
		IMPORT_C void SetExportFileNameL( const TDesC& aExportFileName );
		
		/**
		 * Returns Global UID Array
		 * @return CDesC8Array* 
		*/ 
		IMPORT_C const CDesC8Array* GuidArray() const;

		/**
		 * Returns Local Uid Array
		 * @return RArray<TCalLocalUid>
		*/ 
		IMPORT_C const RArray<TCalLocalUid>& LocalUidArray() const;

		/**
		 * Returns implementor of MCalCallbackBase Mixin Class(Interface)
		 * @return MCalCallbackBase*
		*/ 
		IMPORT_C TPtrC ExportFileName();
		
		/**
		 * Returns Params options selected
		 * @return TInt32
		*/ 
		IMPORT_C TInt32 Params() const;
		
		/**
		 * Returns CCalendarExportParams object which is the exact copy of this object
		 * @return CCalendarExportParams*
		*/ 
		IMPORT_C CCalendarExportParams* CloneL();
		
	private:
	
		/**
		 * Constructor
		*/ 
		CCalendarExportParams();
		
	private:
	
		/**
		 * Global Uid Array
		*/ 
		CDesC8Array* iInputGUIDArray;

		/**
		 * Local Uid Array
		*/ 
		RArray<TCalLocalUid> iInputLocalUIDArray;		
	
		/**
		 * Start time
		*/ 
		HBufC* 		iFileName;

		/**
		 * Params options selected
		*/ 
		TInt32		iParamsFlags;

	};

#endif __CALENDARHEADER_H