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


#ifndef __CALENDARENTRY_H
#define __CALENDARENTRY_H

#include <calentry.h>
#include <calrrule.h>

class CCalUser;

class CAttendeeInfo : public CBase
	{
	public:
	
		/**
	     * Two-phased constructor.
	     * @param aAddress The address of the attendee
	     * @return An instance of CAttendeeInfo
	    */
		IMPORT_C static CAttendeeInfo* NewL( const TDesC& aAddress );
		
		/** 
	     * Destructor.
	    */
		~CAttendeeInfo();
		
		/**
		 * Sets the iCalender-defined common name of the user
		 * @param aName It is the common name of the user
		*/ 
		IMPORT_C void SetCommonNameL( const TDesC& aName );

		/**
		 * Set the role of this attendee
		 * @param aRole The role
		*/ 
		IMPORT_C void SetRoleL( const TDesC& aRole );
		
		/**
		 * Set the status of this attendee
		 * @param aStatus The status
		*/ 
		IMPORT_C void SetStatusL( const TDesC& aStatus );
		
		/**
		 * Sets whether or not a response was requested for this attendee
		 * @param aResponse ETrue if a response was requested, EFalse if not
		*/ 
		IMPORT_C void SetRsvp( const TBool aResponse );
		
		/**
		 * Gets the address of the attendee.
		 * @return The address of the attendee.
		*/ 
		IMPORT_C TPtrC Address();
		
		/**
		 * Gets the iCalender-defined common name of the user.
		 * @return The common name of the user.
		*/ 
		IMPORT_C TPtrC CommonName();
		
		/**
		 * Get the role of this attendee
		 * @return The role
		*/ 
		IMPORT_C TPtrC Role();

		/**
		 * Get the status of this attendee
		 * @return The status
		*/ 
		IMPORT_C TPtrC Status();
		
		/**
		 * Gets whether or not a response was requested for this attendee. 
		 * @return ETrue if a response was requested, EFalse if not. 
		*/ 
		IMPORT_C TBool ResponseRequested();
		
        
	private:
	 
	    /**
		 * Constructor
		*/ 
		CAttendeeInfo();
		
		/**
		 * Constructor
		*/ 
		void ConstructL( const TDesC& aAddress );
		
	private:
	

		/**
		 * Repeat type: can be daily, weekly, monthly or yearly
	  	*/ 
		HBufC* iAddress;
		
		/**
		 * Repeat type: can be daily, weekly, monthly or yearly
	  	*/ 
		HBufC* iRole;
		
		/**
		 * Until time of the repeat rule
	  	*/ 
		HBufC* iStatus;
		
		/**
		 * Start time of the repeat rule
	  	*/ 
		HBufC* iCommonName;
		
		/**
		 * Interval for the repeat rule
	  	*/ 
		TBool iResponse;
		
		
	
	};
	
class CRepeatInfo : public CBase
	{
	
	public:
		/**
	     * Two-phased constructor.
	     * @param 
	     * @return An instance of CRepeatInfo
	    */
		IMPORT_C static CRepeatInfo* NewL( const TInt aType );
		
		/** 
	     * Destructor.
	    */
		~CRepeatInfo();

		/**
		 * Sets the until time for the repeat rule
		 * @param aUntilTime It is the time until which we want this rule to
		 *				 repeat
		*/ 
		IMPORT_C void SetUntilTimeL( const TTime& aUntilTime );

		/**
		 * Sets the number of instances for the repeat rule
		 * @param aCount It is the number of instances we want this rule to
		 *				 repeat
		*/ 
		IMPORT_C void SetCount( const TUint aCount );

		/**
		 * Sets the start time for the repeat rule
		 * @param aStartTime It is the start time for the repeat rule
		*/ 
		IMPORT_C void SetStartTimeL( const TTime& aStartTime );
		
		/**
		 * Sets the interval for the repeat rule
		 * @param aInterval It is the interval between two successive repeats
		*/ 
		IMPORT_C void SetInterval( const TInt aInterval );
		
		/**
		 * Sets all week days on which this rule is repeated, applicable only
		 *				 for weekly repeat rule
		 * @param aDay It specifies the day of the week on which this rule
		 *               repeats. 
		*/ 
		IMPORT_C void SetDaysInWeek( const RArray<TDay>& aDays );
		
		/**
		 * Sets all dates of the month on which this rule is repeated, applicable 
		 *				 only for monthly repeat rule
		 * @param aDay It specifies the day of the month on which this rule
		 *               repeats. 
		*/ 
		IMPORT_C void SetMonthDates( const RArray<TInt>& aMonthDates );
		
		/**
		 * Sets all days of the month on which this rule is repeated, applicable 
		 *				 only for monthly and yearly repeat rule
		 * @param aDay It specifies the day of the week on which this rule
		 *               repeats. 
		 * @param  aWeekNum  The week number in the month i.e.1, 2, 3, 4 for the 1st, 
		 				 2nd, 3rd and 4th week of the month, or -1 for the last week 
		 				 of the month.
		*/ 
		IMPORT_C void SetMonthDays( const RArray<TCalRRule::TDayOfMonth>& aDays );

		/**
		 * Sets the month of the year for this repeat rule
		 * @param aMonthNum It is the month number in which we want the rule to repeat
		*/ 
		IMPORT_C void SetMonth( const TInt aMonthNum );
		
	
       	/**
		 * Sets the first day of the week for this repeat rule.
		 * @param aDay The weekday to be the first
		*/ 
		IMPORT_C void SetWeekStart( const TInt aDay );
	
		/**
		 * Gets the month of the year for this repeat rule
		 * @return The month of the yearly repeat
		*/ 
		IMPORT_C TMonth Month();
		
		/**
		 * Gets all weekdays on which this rule is repeated
		 * @return Array containing all weekdays that are to be set
		*/ 
		IMPORT_C RArray< TDay >& DaysInWeek();

		/**
		 * Gets all days in the month on which this rule is repeated
		 * @return Array containing all days in the month that are to be set
		*/ 
		IMPORT_C RArray< TCalRRule::TDayOfMonth >& DaysInMonth();
		
		/**
		 * Gets all dates in the month on which this rule is repeated
		 * @return Array containing all dates in the month that are to be set
		*/ 
		IMPORT_C RArray< TInt >& DatesInMonth();
		
		/**
		 * Gets the repeat interval.
		 * @return The repeat interval
		*/ 
		IMPORT_C TInt Interval();
		
		/**
		 * Gets the repeat interval.
		 * @return The end date, as a TCalTime so it may be accessed in utc or system local time
		*/ 
	    IMPORT_C TCalTime& UntilDate();
	    
	    /**
		 * Gets the repeat definition's type.
		 * @return The repeat definition's type
		*/ 
		IMPORT_C TCalRRule::TType Type();
		
		/**
		 * Gets the first day of the week for this repeat rule.
		 * @return The first day of the week for this repeat rule.
		*/ 
		IMPORT_C TDay WeekStart();
		
		/**
		 * Gets the repeat rule
		 * @return The repeat rule.
		*/ 
	    IMPORT_C TCalRRule& GetRepeatRule();
	private:
	 
	    /**
		 * Constructor
		*/ 
		CRepeatInfo();
		
		/**
		 * Constructor
		*/ 
		void ConstructL( const TInt aType );	
	private:
	
		
		/**
		 * Repeat type: can be daily, weekly, monthly or yearly
	  	*/ 
		TCalRRule::TType iType;
		
		/**
		 * Until time of the repeat rule
	  	*/ 
		TCalTime iUntilTime;
		
		/**
		 * Start time of the repeat rule
	  	*/ 
		TCalTime iStartTime;
		
		/**
		 * Interval for the repeat rule
	  	*/ 
		TInt iInterval;
		
		/**
		 * Month for the yearly repeat rule
	  	*/ 
		TMonth iMonth;
		
		/**
		 * Array of month days for the monthly/yearly repeat rule
	  	*/ 
		RArray<TCalRRule::TDayOfMonth> iMonthDays;
		
		/**
		 * Array of month dates for the monthly repeat rule
	  	*/ 
		RArray<TInt> iMonthDates;
		
		/**
		 * Array of weekdays for the weekly repeat rule
	  	*/ 
		RArray<TDay> iWeekDays;
		
		TDay iWkSt;
		
		TCalRRule iRule;
		
	};

/**
 * This class provides function to set and get various attributes
 * associated with a calendar entry.
 */	
class CEntryAttributes : public CBase
	{
	public:
	
	/**
	 * TModifiedParameters enum for indicating which entry fields have new values
	 * for modification
	*/
	enum TModifiedParameters
		{
		ESummary		=0x00001,
		ESeqNum			=0x00002,
		EStartTime		=0x00004,
		EEndTime		=0x00008,
		EReplication	=0x00010,
		EDescription	=0x00020,
		EPriority		=0x00040,
		EMethod			=0x00080,
		EAlarmTime		=0x00100,
		ELocation		=0x00200,
		EStatus			=0x00400,
		ERepeatRule		=0x00800,
		EExDates		=0x01000,
		ERepeatDates	=0x02000,
		EPhoneOwner		=0x04000,
		EOrganizer		=0x08000,
		EAttendees		=0x10000,
		ELocalUid		=0x20000,
		EEntryType		=0x40000,
		EInsStartTime	=0x80000,
		};
				
	public:
		
		/**
	     * Two-phased constructor.
	     * @param aType It is the type of calendar entry and can be an appointment,
	     *              to-do item, reminder, event or anniversary  
	     * @return An instance of CEntryAttributes
	    */
		IMPORT_C static CEntryAttributes* NewL( const TDesC& aType );
		
		/**
	     * Two-phased constructor.
	     * @return An instance of CEntryAttributes
	    */
		IMPORT_C static CEntryAttributes* CEntryAttributes::NewL();
		/** 
	     * Destructor.
	    */
		~CEntryAttributes();
		
		/**
		 * Sets the start time for the calendar entry
		 * @param aStartTime It is the start time that we want to set to the 
		 *               calendar entry. 
		 * @return void
		*/ 
		IMPORT_C void SetTypeL( const TDesC& aType );
		
		/**
		 * Sets the start time for the calendar entry
		 * @param aStartTime It is the start time that we want to set to the 
		 *               calendar entry. 
		 * @return void
		*/ 
		IMPORT_C void SetStartTimeL( const TTime& aStartTime );
		
		/**
		 * Sets the end time for the calendar entry
		 * @param aEndTime It is the start time that we want to set to the 
		 *               calendar entry.  
		 * @return void
		*/ 
		IMPORT_C void SetEndTimeL( const TTime& aEndTime );
		
		/**
		 * Sets the instance start time for the calendar entry, valid for "Update"
		 * opration
		 * @param aEndTime It is the start time that we want to set to the 
		 *               calendar entry.  
		 * @return void
		*/ 
		IMPORT_C void SetInstanceStartTimeL( const TTime& aStartTime );

		/**
		 * Sets the sequence number for the calendar entry
		 * @param aSeqNum It is the sequence number that we want to set to the 
		 *               calendar entry.  
		 * @return void
		*/ 
		IMPORT_C void SetSequenceNumber( const TInt aSeqNum );
		
		/**
		 * Sets the status of the calendar entry
		 * @param aStatus It specifies the current status of the calendar entry.
		 * @return void
		*/ 
		IMPORT_C void SetEntryStatusL( const TDesC& aStatus );
		
		/**
		 * Sets the phone owner for a calendar entry 
		 * @param aCommonName It is the common name of the calendar user
		 * @param aEmailAddress It is the email address of the calendar user
		 * @return void
		*/ 
		IMPORT_C void SetPhoneOwnerDataL( const TDesC& aPhoneOwner ); 
		/**
		
		 * Sets the organizer of a calendar entry of type appointment
		 * @param aCommonName It is the common name of the group to which
		 *                  this user belongs.
		 * @param aEmailAddress It is the email address of the meeting organizer
		 * @return void
		*/ 
		IMPORT_C void SetOrganizerDataL( CAttendeeInfo* aPhoneOwner );
		
		/**
		 * Adds the attendees of a calendar entry of type appointment
		 * @param aAttendee attendee for the appointment. Ownership is transfered
		 * @return void
		*/ 
		IMPORT_C void AddAttendeeL( CAttendeeInfo* aAttendee );
		
		/**
		 * Adds the out-of-sequence dates on which this entry occurs.
		 * @param aRepeatDate date that we want to add to the original schedule. 
		 * @return void
		*/ 
		IMPORT_C void AddRepeatDateL( const TTime& aRepeatDate );
		
		/**
		 * Adds the date that is to be exceptioned in the original schedule.
		 * @param aExDate It is the date that we want to remove 
		 *                  from the original schedule. 
		 * @return void
		*/ 
		IMPORT_C void AddExceptionDateL( const TTime& aExDate );
		
		/**
		 * Sets the summary for the calendar entry.
		 * @param aSummary It is the summary that we want to set for the
		 *					calendar entry.
		 * @return void
		*/ 
		IMPORT_C void SetSummaryL( const TDesC& aSummary );
		
		/**
		 * Sets the description for the calendar entry.
		 * @param aDescription It is the description that we want to set for the
		 *					calendar entry.
		 * @return void
		*/ 
		IMPORT_C void SetDescriptionL( const TDesC& aDescription );
		
		/**
		 * Sets the location for the calendar entry.
		 * @param aLocation It is the location that we want to set for the
		 *					meeting entry.
		 * @return void
		*/ 
		IMPORT_C void SetLocationL( const TDesC& aLocation );
		
		/**
		 * Sets the method for the calendar entry.
		 * @param aMethod It is the method that we want to set for the
		 *					meeting entry.
		 * @return void
		*/ 
		IMPORT_C void SetMethodL( const TDesC& aMethod );
		
		/**
		 * Sets the replication for the calendar entry.
		 * @param aLocation It is the location that we want to set for the
		 *					meeting entry.
		 * @return void
		*/ 
		IMPORT_C void SetReplicationL( const TDesC& aRepStatus );
		
		/**
		 * Sets the priority for the calendar entry.
		 * @param aLocation It is the location that we want to set for the
		 *					meeting entry.
		 * @return Error code
		*/ 
		IMPORT_C int SetPriority(const TInt aPriority );
		
		/**
		 * Sets the alarm for the calendar entry.
		 * @param aAlarmTime It is the time that we want to set for the
		 *					entry alarm.
		 * @return void
		*/ 
		IMPORT_C void SetAlarm( const TTime& aAlarmTime);
		
		/**
		 * Sets the local uid for the calendar entry.
		 * @param aLocation It is the location that we want to set for the
		 *					meeting entry.
		 * @return void
		*/ 
		IMPORT_C void SetLocalUid( const TCalLocalUid aLUid);

		/**
		 * Gets the start time for the calendar entry.
		 * @param aLocation It is the location that we want to set for the
		 *					meeting entry.
		 * @return void
		*/ 
		
	    
		IMPORT_C TCalTime& StartTime();
       
        /**
		 * Sets the entry's repeat rule
		 * @param aRptInfo It is the repeat rule information for this entry
		*/ 	
		IMPORT_C  void SetRepeatRule( CRepeatInfo* aRptInfo);
		
		/**
		 * Gets the end time for the calendar entry.
		 * @return The end time for the calendar entry.
		*/ 
		IMPORT_C TCalTime& EndTime();
		
		/**
		 * Gets the instance start time.
		 * @return void The instance start time.
		*/ 
		IMPORT_C TCalTime& InstanceStartTime();
		
		/**
		 * Gets the entry type for the calendar entry.
		 * @return void The entry type for the calendar entry.
		*/ 
	    IMPORT_C CCalEntry::TType EntryType();
	    
	    /**
		 * Gets the sequence number for the calendar entry.
		 * @return void The sequence number for the calendar entry.
		*/ 
		IMPORT_C TInt SequenceNumber();
		
		/**
		 * Gets the entry status for the calendar entry.
		 * @return void The entry status for the calendar entry.
		*/ 
		IMPORT_C CCalEntry::TStatus EntryStatus();
		
		/**
		 * Gets the alarm time for the calendar entry.
		 * @return void The alarm time for the calendar entry.
		*/ 
		IMPORT_C TTime AlarmTime();
		
		/**
		 * Gets the phone owner for the calendar entry.
		 * @return void The phone owner for the calendar entry.
		*/ 
		IMPORT_C TPtrC PhoneOwner();
		
		/**
		 * Gets the method for the calendar entry.
		 * @return void The method for the calendar entry
		*/ 
		IMPORT_C CCalEntry::TMethod Method();
		
		/**
		 * Gets the organizer for the calendar entry.
		 * @return void The organizer for the calendar entry.
		*/ 
		IMPORT_C CCalUser* Organizer();
		
		/**
		 * Gets the list of attendees for the calendar entry.
		 * @return RPointerArray<CCalAttendee>&
		*/ 
		IMPORT_C RPointerArray<CCalAttendee>& AttendeeList();
		
		/**
		 * Gets the list of repeat dates for the calendar entry.
		 * @return void
		*/ 
		IMPORT_C RArray<TCalTime>& RepeatDates();
		
		/**
		 * Gets the exception dates for the calendar entry.
		 * @return void
		*/ 
		IMPORT_C RArray<TCalTime>& ExceptionDates();
		
		/**
		 * Gets the summary for the calendar entry.
		 * @return void
		*/ 
		IMPORT_C TPtrC Summary();
		
		/**
		 * Gets the description for the calendar entry.
		 * @return void
		*/ 
		IMPORT_C TPtrC Description();
		
		/**
		 * Gets the location for the calendar entry.
		 * @return void
		*/ 
		IMPORT_C TPtrC Location();
		
		/**
		 * Gets the priority for the calendar entry.
		 * @return void
		*/ 
		IMPORT_C TInt Priority();
		
		/**
		 * Gets the replication status for the calendar entry.
		 * @return void
		*/ 
		IMPORT_C CCalEntry::TReplicationStatus ReplicationStatus();
		
		/**
		 * Gets the repeat rule for the calendar entry.
		 * @return void
		*/ 
		IMPORT_C TCalRRule& RepeatRuleL();
		
		/**
		 * Gets the local uid for the calendar entry.
		 * @return void
		*/ 
		IMPORT_C TCalLocalUid LocalUid();
		
		/**
		 * Gets the attributes that have changed for the calendar entry.
    	 * @return A 32-bit integer indicating which attributes have been modified.
		*/ 
		IMPORT_C TInt32 ModifiedAttributes();
	
	private:
	 
	    /**
		 * Constructor
		*/ 
		CEntryAttributes();
		
		/**
		 * Constructor
		*/ 
		void ConstructL( const TDesC& aType );		
	private:
	
		
		/**
		 * Entry type: can be an appointment, to-do item, reminder, event or anniversary
	  	*/ 
		CCalEntry::TType iType;
		
		/**
		 * Start time of the entry
	  	*/ 
		TCalTime iStartTime;
		
		/**
		 * End time of the entry
	  	*/ 
		TCalTime iEndTime;

        /**
		 * Start time of the instance to be modified
	  	*/ 
		TCalTime iInstanceStartTime;

		/**
		 * Sequence number for the entry
	  	*/ 
		TInt iSequenceNum;
		
		/**
		 * Summary for the entry
	  	*/ 
		HBufC* iSummary;
		
		/**
		 * Description for the entry
	  	*/ 
		HBufC* iDescription;
		
		/**
		 * Location for entry of appointment type
	  	*/ 
		HBufC* iLocation;
		
		/**
		 * Alarm time for the entry
	  	*/ 
		TTime iAlarmTime;
		
		/**
		 * Status of the entry: valid for entries of "appointment" and "todo" type
	  	*/ 
		CCalEntry::TStatus iEntryStatus;
		
		/**
		 * Entry's method property for group scheduling
	  	*/ 
		CCalEntry::TMethod iMethod;
		
		/**
		 * Replication status of the entry
	  	*/ 
		CCalEntry::TReplicationStatus iRepStatus;
		
		/**
		 * Phone owner data for the entry: applicable only for entries of "appointment" type
	  	*/ 
		HBufC* iPhoneOwner;
		
		/**
		 * Organizer of an appointment entry
	  	*/ 
		CCalUser* iOrganizer;
		
		/**
		 * An array of out-of-sequence dates on which this entry repeats
	  	*/ 
		RArray<TCalTime> iRepeatDates;
		
		/**
		 * An array of exception dates i.e occurrences in the original schedule that 
		 * have been removed and may be replaced with a different occurrence
	  	*/ 
		RArray<TCalTime> iExDates;
		
		/**
		 * Array of attendees of an appointment entry
	  	*/ 	
		RPointerArray<CCalAttendee> iAttendees;
		
		/**
		 * The entry's repeat definition: valid for repeating entries of "appointment" type
	  	*/ 
		TCalRRule iRepeatRule;
		
		/**
		 * Priority of the entry
	  	*/ 
		TInt iPriority;
		
		/**
		 * Local Uid of an entry which can uniquely identify entries having the same Global Uid
	  	*/ 
		TCalLocalUid iLocal;
		
		/**
		 * Indicates which entries have new values for the update operation
	  	*/ 
		TInt32 iSetAttributes;
	};
	
#endif __CALENDARENTRY_H