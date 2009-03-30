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


#ifndef __ADDENTRY_H
#define __ADDENTRY_H

class CEntryAttributes;

/**
 * This class provides functions to add a new calendar entry or modify
 * an existing calendar entry.
 */
class CCalendarAddEntry : public CBase
	{

	public:
	    /**
	     * Two-phased constructor.
	     * @param aSessionInfo Object of CCalendarSessionInfo class which
	     *        contains information for a calendar session.
	     * @param aCalendarData Attributes of the entry
	     * @return CAddEntry object
	    */
		static CCalendarAddEntry* NewL( CCalendarSessionInfo* aSessionInfo, 
											CEntryAttributes* aCalendarData ) ;

	    /** 
	     * Destructor.
	     * @param 
	     * @return 
	    */
		~CCalendarAddEntry();
		
	    /** 
	     * Adds/Updates entry in a specific calendar file
	     * @param aGuidAdded A structure containing the Global Uid and
	     *        LocalUid of the entry that was successfully added/updated.
	    */
		void AddL( TUIDSet*& aGuidAdded );

  
	private:

	    /** 
	     * Constructor.
	     * @param aSessionInfo Object of CCalendarSessionInfo class which
	     *        contains information for a calendar session.
	    */
		CCalendarAddEntry( CCalendarSessionInfo* aSessionInfo, 
											CEntryAttributes* aCalendarData  );
	
	    /** 
	     * Adds entry in a specific calendar file
	     * @param aGuidAdded A structure containing the Global Uid and
	     *        LocalUid of the entry that was successfully added.
	    */
	    void AddNewEntryL( TUIDSet*& aGuidAdded );
	    
	    /** 
	     * Updates entry in a specific calendar file
	     * @param aGuidAdded A structure containing the Global Uid and
	     *        LocalUid of the entry that was successfully updated.
	    */
	    void UpdateEntryL( TUIDSet*& aGuidAdded );
	    
        /**
		 * Updates an existing calendar entry without adding a new entry to the calendar store
		 * @param aCalendarData A structure containing entry attributes to be modified
	     * @param aEntry The calendar entry to be modified
		*/ 
		void UpdateEntryAttributesL( CCalEntry* aEntry );
        
        /**
		 * Retrieves the instance for the given local uid
		 * @param aInsStTime Instance start time
		 * @param aLUid Local Uid
	     * @return CCalInstance* 
		*/ 
		CCalInstance* GetInstanceL( const TCalTime& aInsStTime, TCalLocalUid aLUid );
        
		void SetStartEndTimeL( CCalEntry* aEntry, const TCalTime& aStTime, const TCalTime& aEndTime );

	private:

		/**
		 * CCalendarSessionInfo object containing session information
		*/ 
	 	CCalendarSessionInfo* iSessionInfo;
	 	
	 	CEntryAttributes* iCalendarEntry;
	};


#endif __ADDENTRY_H