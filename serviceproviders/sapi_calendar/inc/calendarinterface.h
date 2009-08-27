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
* Description:  Defination of class CCalendarInterface
*
*/


#ifndef __CALENDARINTERFACE_H
#define __CALENDARINTERFACE_H

#include <LiwCommon.h>
#include <LiwServiceIfBase.h>
#include <LiwBufferExtension.h>

#include <calrrule.h>
#include <calalarm.h>
#include <caluser.h>
#include <calentry.h>
#include <calchangecallback.h>

#include "calendarheader.h"
#include "calendarconstants.h"

class CCalendarService;
class CIterableCalEntryList;
class CEntryAttributes;
class TUIDSet;

/**
 * This class provides the Calendar SAPI interface to LIW Framework 
*/
class CCalendarInterface : public CBase, public MLiwInterface
	{
		
	public:

	    /**
	     * Two-phased constructor.
	     * @return CCalendarInterface* 
	    */
		static CCalendarInterface* NewL();

	    /**
	    * Destructor.
	    */
		virtual ~CCalendarInterface();

	private:

		/**
	     * Constructor
	    */
		CCalendarInterface();

		/**
	     * Symbian Constructor
	    */
		void ConstructL();

	// MLiwInterface member functions
	public:

		/**
	     * Executes the SAPI as per params
	     * @param aCmdName Command name defining which operation is to be performed
	     * @param aInParamList  Input param list
	     * @param aOutParamList Output list
	     * @param aCmdOptions Command option
	     * @param aCallback Callback object pointer
	    */
		virtual void ExecuteCmdL( const TDesC8& aCmdName,
		                       const CLiwGenericParamList& aInParamList,
		                       CLiwGenericParamList& aOutParamList,
		                       TUint aCmdOptions = 0,
		                       MLiwNotifyCallback* aCallback = 0 );
		
		/**
	     * Closes the interface 
	    */
		virtual void Close();
		
	/**
     * Static Functions
	 * 
	 * Same functionality required outside the CCalendarInterface class in case of async
	 * operation. Those set of functions can be given as static.
    */
	public:
 
		/**
	     * Converts symbian errcode to equivalent SAPI error code
	     * @param aErrorCode Symbian error code
		 *
	     * @return mapped SAPI error code
	    */
 		static TInt32 ErrCodeConversion(TInt aErrorCode);

		/**
	     * Set Import output to output parameter
	     * @param aOutputUIDSet Import output
	     * @param aOutParamList Output parammeter
		 *
	     * @return void
	    */
		static void SetImportOutputL( RPointerArray<TUIDSet>& aOutputUIDSet, 
												CLiwGenericParamList& aOutParamList );

        /**
         * Set Getlist output to output parameter
         * @param aOutputCalEntry getlist output
         * @param aOutParamList Output parammeter
         *
         * @return void
        */
        void SetCalEntryOutputL( RPointerArray<CCalEntry>& aOutputCalEntry, 
                                                CLiwGenericParamList& aOutParamList, 
                                                const TDesC& aCalendarName );
        /**
         * Set Getlist output to output parameter
         * @param aOutputCalEntry getlist output
         * @param aOutParamList Output parammeter
         *
         * @return void
        */
        void SetCalInstanceOutputL( RPointerArray<CCalInstance>& aOutputCalEntry, 
                                                CLiwGenericParamList& aOutParamList, 
                                                const TDesC& aCalendarName );
        
		
		/**
	     * Set Change Notification output to output parameter
	     * @param aOutputChangeSet Notifications list
	     * @param aOutParamList Output parammeter
		 *
	     * @return void
	    */
		static void SetNotifyOutputL( RArray<TCalChangeEntry>& aOutputChangeSet,  
												CLiwGenericParamList& aOutParamList );
		
		/**
	     * Set GlobalUid/LocalUid to the LiwVariant
	     * @param aReturnValue Variant to be set
	     * @param aUIDSet GlobalUid/LocalUid
		 *
	     * @return void
	    */
		static void GetTLiwVariantForUIDSetL( TLiwVariant& aReturnValue, TUIDSet* aUIDSet );

		/**
	     * Set Change type to the LiwVariant
	     * @param aValue Variant to be set
	     * @param aChangeEntry Change Type
		 *
	     * @return void
	    */
		static void GetTLiwVariantForCalChangeEntryL( TLiwVariant& aValue, 
												TCalChangeEntry& aChangeEntry );

		/**
	     * Cleanup function for an CIterableCalEntryList
	     * @param aIterEntryList CIterableCalEntryList pointer
		 *
	     * @return void
	    */
		static void CleanupIterableCalEntry(void* aIterEntryList);

		/**
	     * Returns Day of Month of repeat rule as LiwVariant Map. Caller takes the ownership of map
	     * @param aDayOfMonth Day of Month
		 *
	     * @return CLiwDefaultMap* LiwMap object
	    */
		static CLiwDefaultMap* GetDayOfMonthL( const TCalRRule::TDayOfMonth&  aDayOfMonth );

		/**
	     * Returns CalUser as LiwVariant Map. Caller takes the ownership of map
	     * @param aCalUser Day of Month
	     * @param aAttendee True if User is an attendee
		 *
	     * @return CLiwDefaultMap* LiwMap object
	    */
		static CLiwDefaultMap* GetCalUserL( CCalUser* aCalUser, TBool aAttendee = EFalse );

		/**
	     * Returns array of CalTime as LiwVariant List. Caller takes the ownership of list
	     * @param aDates Array of CalTime 
		 *
	     * @return CLiwDefaultList* LiwList object
	    */
		static CLiwDefaultList* GetDatesListL( RArray<TCalTime>& aDates ) ;

		/**
	     * Returns RepeatRule as LiwVariant Map. Caller takes the ownership of map
	     * @param aRepeatRule Repeat Rule
		 *
	     * @return CLiwDefaultMap* LiwMap object
	    */
		static CLiwDefaultMap* GetRRMapL( const TCalRRule& aRepeatRule );

		/**
	     * Returns string literal for the given Entry Type
	     * @param aType Entry Type
		 *
	     * @return TPtrC Entry Type string
	    */
		static TPtrC GetEntryTypeL( const CCalEntry::TType aType );

		/**
	     * Returns string literal for the given Entry Replication status
	     * @param aReplicationStatus Replication status
		 *
	     * @return TPtrC Replication status string
	    */
		static TPtrC GetReplicationL( const CCalEntry::TReplicationStatus aReplicationStatus );

		/**
	     * Returns string literal for Change Types
	     * @param aChangeType Change Type
		 *
	     * @return TPtrC Change Type
	    */
		static TPtrC GetChangeType( const MCalChangeCallBack2::TChangeType aChangeType );

		/**
	     * Returns string literal for Entry Status
	     * @param aStatus Entry Status
		 *
	     * @return TPtrC Entry Status
	    */
		static TPtrC GetStatusL( const CCalEntry::TStatus aStatus );

		/**
	     * Returns string literal for Attendee Status
	     * @param aStatus Attendee Status
		 *
	     * @return TPtrC Attendee Status
	    */
		static TPtrC GetAttendeeStatusL( const CCalAttendee::TCalStatus aStatus );

		/**
	     * Get string literal for Attendee Role
	     * @param aRole Attendee Role
		 *
	     * @return TPtrC Attendee Role
	    */
		static TPtrC GetAttendeeRoleL( const CCalAttendee::TCalRole aRole );

		/**
	     * Return string literal for Entry Method
	     * @param aMethod Entry Method
		 *
	     * @return TPtrC Entry Method
	    */
		static TPtrC GetMethodL( const CCalEntry::TMethod aMethod );

		/**
	     * Removes the reference of CIterableCalEntryList from the table maintained 
	     * by interface
	     * @param aCalEntryList Element that need to be removed from the table
		 *
	     * @return void
	    */
		void RemoveCalEntryListFromArray( CIterableCalEntryList* aCalEntryList );


	private:
	
		/**
	     * Issues Add Calendar request to Calendar Service
	     * @param aInParamList Input param list
	     * @param aOutParamList Output param list
	     * @param aPosBased ETrue for position pased parameters
		 *
	     * @return void
	    */
		void AddCalendarL(const CLiwGenericParamList& aInParamList, 
												CLiwGenericParamList& aOutParamList, 
												const TBool aPosBased );
		
		/**
	     * Issues Add Calendar Entry request to Calendar Service
	     * @param aInParamList Input param list
	     * @param aOutParamList Output param list
	     * @param aPosBased ETrue for position pased parameters
		 *
	     * @return void
	    */
		void AddCalendarEntryL(const CLiwGenericParamList& aInParamList, 
												CLiwGenericParamList& aOutParamList, 
												const TBool aPosBased );

		/**
	     * Issues Delete Calendar request to Calendar Service
	     * @param aInParamList Input param list
	     * @param aOutParamList Output param list
	     * @param aPosBased ETrue for position pased parameters
		 *
	     * @return void
	    */
		void DeleteCalendarL( const CLiwGenericParamList& aInParamList, TBool aPosBased);
		
		/**
	     * Issues Delete Calendar Entry request to Calendar Service
	     * @param aInParamList Input param list
	     * @param aOutParamList Output param list
	     * @param aCmdOptions Command option
	     * @param aCallback Callback object pointer
	     * @param aPosBased ETrue for position pased parameters
	     * @param aTransactionId Output param for async request to store transaction id
		 *
	     * @return void
	    */
		void DeleteCalendarEntryL(const CLiwGenericParamList& aInParamList, 
												CLiwGenericParamList& aOutParamList,
												TUint aCmdOptions,
				                       			MLiwNotifyCallback* aCallback ,
												const TBool aPosBased,
												TInt32& aTransactionId  );

		/**
	     * Issues GetList Calendar request to Calendar Service
	     * @param aInParamList Input param list
	     * @param aOutParamList Output param list
	     * @param aPosBased ETrue for position pased parameters
		 *
	     * @return void
	    */
		void GetListCalendarL(const CLiwGenericParamList& aInParamList, 
												CLiwGenericParamList& aOutParamList, 
												const TBool aPosBased );
		
		/**
	     * Issues GetList Calendar Entry request to Calendar Service
	     * @param aInParamList Input param list
	     * @param aOutParamList Output param list
	     * @param aPosBased ETrue for position pased parameters
		 *
	     * @return void
	    */
		void GetListCalendarEntryL(const CLiwGenericParamList& aInParamList, 
												CLiwGenericParamList& aOutParamList,
												TUint aCmdOptions,
												MLiwNotifyCallback* aCallback ,
												const TBool aPosBased,
												TInt32& aTransactionId  );
												
		/**
	     * Issues Import Calendar Entry request to Calendar Service
	     * @param aInParamList Input param list
	     * @param aOutParamList Output param list
	     * @param aCmdOptions Command option
	     * @param aCallback Callback object pointer
	     * @param aPosBased ETrue for position pased parameters
	     * @param aTransactionId Output param for async request to store transaction id
		 *
	     * @return void
	    */
		void ImportCalendarEntryL(const CLiwGenericParamList& aInParamList, 
												CLiwGenericParamList& aOutParamList,
												TUint aCmdOptions,
				                       			MLiwNotifyCallback* aCallback ,
												const TBool aPosBased,
												TInt32& aTransactionId  );

		/**
	     * Issues Export Calendar Entry request to Calendar Service
	     * @param aInParamList Input param list
	     * @param aOutParamList Output param list
	     * @param aCmdOptions Command option
	     * @param aCallback Callback object pointer
	     * @param aPosBased ETrue for position pased parameters
	     * @param aTransactionId Output param for async request to store transaction id
		 *
	     * @return void
	    */
		void ExportCalendarEntryL(const CLiwGenericParamList& aInParamList, 
												CLiwGenericParamList& aOutParamList,
												TUint aCmdOptions,
				                       			MLiwNotifyCallback* aCallback ,
												const TBool aPosBased,
												TInt32& aTransactionId  );
													
		/**
	     * Issues Change Notification request to Calendar Service
	     * @param aInParamList Input param list
	     * @param aCallback Callback object pointer
	     * @param aPosBased ETrue for position pased parameters
	     * @param aTransactionId Output param for async request to store transaction id
		 *
	     * @return void
	    */
		void RequestNotificationL( const CLiwGenericParamList& aInParamList, 
				                       			MLiwNotifyCallback* aCallback,
												const TBool aPosBased,
												TInt32& aTransactionId );



		/**
	     * Extracts LocalUid as TCalLocalUid from input Uid String
	     * @param aLocalUid Input string
	     * @param aOutLocalUid output param for LocalUid
		 *
	     * @return void
	    */
		void GetLocalUid( const TDesC& aLocalUid, TCalLocalUid& aOutLocalUid );
		
		/**
	     * Extracts GlobalUid as 8-bit string from input Uid String
	     * @param aGlobalUid Input string
	     * @param aOutGlobalUid output param for GlobalUid
		 *
	     * @return void
	    */
		void GetGlobalUid( const TDesC& aGlobalUid, TPtr8 aOutGlobalUid );

		/**
	     * Extracts ContentType from the input param list
	     * @param aInParamList Input param list
	     * @param aPosBased ETrue for position pased parameters
		 *
	     * @return ContentType string
	    */
		TPtrC GetContentType(const CLiwGenericParamList& aInParamList, 
												TBool& aPosBased );
		
		/**
	     * Extracts TransactionId from the input param list
	     * @param aInParamList Input param list
	     * @param aTransactionId output param fromtransactiod id
		 *
	     * @return void
	    */
		void GetTransactionIdL( const CLiwGenericParamList& aInParamList, 
												TInt32& aTransactionId );

		/**
	     * Extracts CalendarName from the input param list
	     * @param aInParamList Input param list
	     * @param aCmdName Command Name
	     * @param aField ParameterName to read
	     * @param aPosBased ETrue for position pased parameters
	     * @param aCalendarName Output param for Calendar Name
		 *
	     * @return void
	    */
	    void GetCalendarNameL( const CLiwGenericParamList& aInParamList,
	    										const TDesC8& aCmdName,  
	    										const TDesC8& aField, 
	    										TBool aPosBased, 
	    										HBufC*& aCalendarName );

		/**
	     * Extracts Descriptor Field from Map in input param list
	     * @param aInParamList Input param list
	     * @param aCmdName Command Name
	     * @param aMapName Map name in input param list
	     * @param aFieldName Filed name to read from map
	     * @param aPosBased ETrue for position pased parameters
	     * @param aOutputField Output param for Field value
		 *
	     * @return void
	    */
		void CCalendarInterface::GetDesCFieldFromMapL( const CLiwGenericParamList& aInParamList, 
														const TDesC8& aCmdName, 
														const TDesC8& aMapName, 
														const TDesC8& aFieldName, 
														TBool aPosBased, 
														HBufC*& aOutputField );

		/**
	     * Extracts 8-bit Descriptor Field from Map in input param list
	     * @param aInParamList Input param list
	     * @param aCmdName Command Name
	     * @param aMapName Map name in input param list
	     * @param aFieldName Filed name to read from map
	     * @param aPosBased ETrue for position pased parameters
	     * @param aOutputField Output param for Field value
		 *
	     * @return void
	    */
		void CCalendarInterface::GetDesC8FieldFromMapL( const CLiwGenericParamList& aInParamList, 
														const TDesC8& aCmdName, 
														const TDesC8& aMapName, 
														const TDesC8& aFieldName, 
														TBool aPosBased, 
														HBufC8*& aOutputField );

		/**
	     * Extracts Entry attributes for Add/Update request
	     * @param aInParamList Input param list
	     * @param aCalendarName CalendarName
	     * @param aPosBased ETrue for position pased parameters
		 *
	     * @return CEntryAttributes* EntryAttributes object
	    */
		CEntryAttributes* GetAddParametersL( const CLiwGenericParamList& aInParamList, 
												const TDesC& aCalendarName,
												TBool aPosBased);
		
		/**
	     * Extracts Filter for Delete request
	     * @param aInParamList Input param list
	     * @param aFilter Output param for Filter
	     * @param aPosBased ETrue for position pased parameters
		 *
	     * @return void
	    */
		void GetDeleteEntryFilterL(const CLiwGenericParamList& aInParamList, 
												CCalendarFilter& aFilter, 
												const TBool aPosBased );

		/**
	     * Extracts Inputs for Import request
	     * @param aInParamList Input param list
	     * @param aPosBased ETrue for position pased parameters
	     * @param aInputBuffer Output param for Buffer from which entries to be imported
	     * @param aImportFile Output param for File from which entries to be imported
	     * @param aCalendarFormat Output param for Calendar Format to be used (ICal/VCal)
	     * @param aCalendarName Output param for Calendar Name
		 *
	     * @return void
	    */
		void GetImportInputL( const CLiwGenericParamList& aInParamList,
												TBool    aPosBased, 
												HBufC8*& aInputBuffer, 
												TDes&   aImportFile,
												TDes8&  aCalendarFormat, 
												TDes&   aCalendarName );

		/**
	     * Extracts Inputs for Export request
	     * @param aInParamList Input param list
	     * @param aPosBased ETrue for position pased parameters
	     * @param aCalExportParams Output param for Export parameters
		 *
	     * @return void
	    */
		void GetExportInputL( const CLiwGenericParamList& aInParamList, 
												TBool                  aPosBased, 
												CCalendarExportParams& aCalExportParams);							  
	
		/**
	     * Extracts Inputs for Change Notification request
	     * @param aInParamList Input param list
	     * @param aFileter Output param for Change Notification filter
	     * @param aPosBased ETrue for position pased parameters
		 *
	     * @return void
	    */
		void GetNotificationFilterL( const CLiwGenericParamList& aInParamList, 
												CCalendarFilter& aFilter, 
												const TBool aPosBased );
												
		/**
	     * Appends error message
	     * @param aCmdName Command Name
	     * @param aParameter Parameter Name
	     * @param aMessage Error message
		 *
	     * @return void
	    */
		void AppendErrorMessageL( const TDesC8& aCmdName, 
												const TDesC8& aParameter, 
												const TDesC& aMessage );
												
		/**
	     * Checks for the valid data type of Parameter.
	     * @param aParam Input parameter
	     * @param aExpectedtype Expected type for input parameter
	     * @param aCmdName Command Name
	     * @param aParameter Parameter Name
	     * @param aErrorMessage Error message in case of type mismatch
		 *
	     * @return void
	    */
		void ValidateParamTypeL( TLiwVariant& aParam, 
												LIW::TVariantTypeId aExpectedtype, 
												const TDesC8& aCmdName, 
												const TDesC8& aParameter,
												const TDesC& aMessage );

		/**
	     * Returns entry type for given LocalUid.
	     * @param aCalendarName CalendarName
	     * @param aLocalUid LocalUid
		 *
	     * @return Entry type
	    */
		TInt GetEntryType( const TDesC& aCalendarName, TCalLocalUid aLocalUid );
        /**
         * Returns entry type for given LocalUid.
         * @param aCalendarName CalendarName
         * @param aLocalUid LocalUid
         *
         * @return Entry type
        */
        TInt GetEntryType( const TDesC& aCalendarName, const TDesC8& aGuid );
		
		
		/**
	     * Check if given calendar is in use.
	     * @param aCalendarName CalendarName
		 *
	     * @return True if given calendar is in use
	    */
		TBool CCalendarInterface::CheckCalendarInUse( const TDesC& aCalendarName );
		
	private:

	  	/**
	     * CCalendarService class pointer
	     * @internal
	    */		
		CCalendarService* iCalService;

	  	/**
	     * Error Message object
	     * @internal
	    */		
		HBufC* iErrorMessage;

	  	/**
	     * Array containing the list of CalEntryList.
	     * @internal
	    */		
		RPointerArray<CIterableCalEntryList> iArrayCalEntryList;

	};


#endif __CALENDARINTERFACE_H