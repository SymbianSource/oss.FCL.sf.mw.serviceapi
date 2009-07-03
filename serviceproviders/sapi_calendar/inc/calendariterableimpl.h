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


#ifndef __CALENDARITERABLEIMPL_H
#define __CALENDARITERABLEIMPL_H

#include <LiwCommon.h>
#include <LiwServiceIfBase.h>
#include <LiwBufferExtension.h>

#include <calentry.h>
#include <calinstance.h>
#include "calendarinterface.h"

/**
* Implemenation of abstract interface to iterate over the collection of Calendars.
*
* @see CLiwIterable
*
*/
class CIterableCalendarList : public CLiwIterable	
	{
	public:
	  	/**
	     * Two-phase Constructor
	     * @param aList list to be iterated 
	     * @return new CIterableCalList object
	    */	
		static CIterableCalendarList* NewL( CDesCArray* aList );

		/**
		* Resets the iterator. 
		*
	     * @return void
		*/
		void Reset();

		/**
		* Iterates over the collection entries to fetch the next data element.
		*
		* @param aValue contains the next data element
		*
		* @return false if there are no more data elements to be fetched;
		* true otherwise
		* 
		*/
		TBool NextL(TLiwVariant& aValue);
		
	    /**
	    * Destructor.
	    */
		~CIterableCalendarList();

	private:
	
	    /**
	    * Constructor
	     * @param aList list to be iterated 
	     * @return void
	    */
		CIterableCalendarList( CDesCArray* aList );


	private:
	
	  	/**
	     * CDesCArray  class pointer
	    */		
		CDesCArray* 	iList;

	  	/**
	     * Index on list
	    */		
		TInt					iIndex;	
	};

/**
* Implemenation of abstract interface to iterate over the collection of Calendar Entries.
*
* @see CLiwIterable
*
*/
class CIterableCalEntryList : public CLiwIterable	
	{
	public:
	  	/**
	     * Two-phase Constructor
	     * @param aInterface Calendar Interface reference
	     * @param aCalendarName Calendar Name
	     * @param aIsEntryList Flag for checking validity of EntryList
	     * @return new CIterableCalList object
	    */	
		static CIterableCalEntryList* NewL( CCalendarInterface& aInterface, 
												const TDesC& aCalendarName, 
												const TBool aIsEntryList );

		/**
		* Resets the iterator. 
		*
		*/
		void Reset();

		/**
		* Iterates over the collection entries to fetch the next data element.
		*
		* @param aEntry contains the next data element and its corresponding data type
		*
		* @return false if there are no more data elements to be fetched;
		* true otherwise
		* 
		*/
		TBool NextL(TLiwVariant& aEntry);
		
		/**
		* Return reference of the collection entries.
		*
		* @return Return reference of the collection entries
		* 
		*/
		RPointerArray<CCalEntry>& EntryArray();

		/**
		* Return reference of the collection instances.
		*
		* @return Return reference of the collection instances.
		* 
		*/
		RPointerArray<CCalInstance>& InstanceArray();
		
		/**
		* Return reference of the collection instances.
		*
		* @return Return reference of the collection instances.
		* 
		*/
		void SetResourceFree();
		
		/**
		* Return CalendarName.
		*
		* @return Return CalendarName.
		* 
		*/
		TPtrC CalendarName();
		
	    /**
	    * Destructor.
	    */
		~CIterableCalEntryList();

	private:

	    /**
	    * Constructor
	    * @param aInterface Calendar interface reference
	    * @param aList list to be iterated 
	    * @return void
	    */
		CIterableCalEntryList( CCalendarInterface& 	aInterface, const TBool aIsEntryList );

	  	/**
	     * Two-phase Constructor
	     * @param aCalendarName CalendarName to which this resource belongs
	     * @return void
	    */	
		void ConstructL( const TDesC& aCalendarName );
		
	private:
	
	  	/**
	     * Calendar Entry List
	    */		
		RPointerArray<CCalEntry> iEntryList;

	  	/**
	     * Calendar Instances List
	    */		
		RPointerArray<CCalInstance> iInstanceList;

	  	/**
	     * Index on list
	    */		
		TInt					iIndex;	

	  	/**
	     * Flag to check the validity of iEntryList;
	     * Only one of the iEntryList/iInstanceList can be valid
	    */		
		TBool					iIsEntryList;	
		
	  	/**
	     * Flag to check the validity of iEntryList/iInstanceList;
	    */		
		TBool					iIsResourceFree;	

	  	/**
	     * Calendar Interface reference
	    */		
		CCalendarInterface& 	iInterface;
		
	  	/**
	     * Calendar Name
	    */		
		HBufC* 					iCalendarName;
		
	};

/**
* An associative array or dictionary class. The collection
* key entries are of type string (Descriptor type) and their  
* associated values can be an variant type.
* 
*  \c CLiwDefaultMap provides default map implementation to
   *  <ul>
   *     <li>insert a key-value pair</li>
   *     <li>find a stored value based on a key</li>
   *     <li>get a key based on an index</li>
   *     <li>remove a key-value pair based on a key</li>
   *		 <li>get the total number of stored key-value pairs</li>
   *   </ul>
* 
*
* @lib ServiceHandler.lib
* @since S60 5.0
*
* @see CLiwContainer
* @see TLiwVariant
* @see CLiwMap
*
*/
class CLiwCalEntryMap : public CLiwMap
{
 public:
  
  /*
   * Creates an instance of CLiwCalEntryMap
   *
   * @param aEntry Calendar Entry
   *
   * @return an instance of CLiwCalEntryMap
   */
   static CLiwCalEntryMap* NewL( CCalEntry* aEntry );
  
  /*
   * Creates an instance of CLiwCalEntryMap
   *
   * @param aEntry Calendar Entry Instance
   *
   * @return an instance of CLiwCalEntryMap
   */
   static CLiwCalEntryMap* NewL( CCalInstance* aEntry );
  
  /**
    * Inserts a key-value pair element to the map collection. If
    * the specified key already exists, it will be removed from
    * the collection and the new key-value pair will be added to the
    * map.
    *  
    * @param aKey the key to be stored
    * @param aValue the value associated with the key to be stored
   	*
   	* @return void
    */
  	void InsertL(const TDesC8& aKey, const TLiwVariant& aValue);
  
  /**
    * Finds a value stored in the map collection based on the key.
    *  
    * @param aKey the key to be searched
    * @param aFndValue the value associated with the found key
    *
    * @return false if there is no key stored; true otherwise
   */
  	TBool FindL(const TDesC8& aKey, TLiwVariant& aValue) const;
  
  /**
    * Returns the number of key-value pair stored in the map collection.
    *  
    * @return the number of key-value pair stored in the map collection
   */
  	TInt Count() const;
  
  /**
    * Returns the key stored at a specified index. 
    *  
    * @param aIndex the index of the key to be found
    * @param aFndKey the key found at the passed index
    *
    * @return true if a key-value entry is found at the passed index;
    * false otherwise
   */
  	TBool AtL(TInt aIndex, TDes8& aFndKey) const;
  
  /**
    * Removes a key from the map collection.
    *  
    * @param aKey the key to be removed from the map
   */
  	void Remove(const TDesC8& aKey);
  
  
  
 private:
 
 	/*
 	 * Constructor
 	 */
	CLiwCalEntryMap( CLiwGenericParamList* aMap, CCalEntry* aEntry ) 
	: iMap(aMap), iCalEntry(aEntry), iIsEntry(ETrue)
	 {}
  
 	/*
 	 * Constructor
 	 */
	CLiwCalEntryMap( CLiwGenericParamList* aMap, CCalInstance* aInstance ) 
	: iMap(aMap), iCalInstance(aInstance), iIsEntry(EFalse)
	 { iCalEntry = &aInstance->Entry(); }
  
	/**
	* Adds the element to the Map is it doesnot exist already
	*  
	* @param aMap The map to be used for searching
	*
	* @param aKey The key to be searched
	*
	* @return void
	*/
	static void PopulateKeyL( CLiwCalEntryMap* aMap,  const TDesC8& aKey );
  
	/**
	* Adds the Meeting entry element to the Map is it doesnot exist already
	*  
	* @param aMap The map to be used for searching
	*
	* @param aKey The key to be searched
	*
	* @return void
	*/
	static void PopulateMeetingKeyL( CLiwCalEntryMap* aMap,  const TDesC8& aKey );
  

	/*
	* Destructor
	*/
	virtual ~CLiwCalEntryMap();
  
	/*
	* the underlying generic parameter list
	*/
	CLiwGenericParamList* iMap;
  
  	/**
     * CCalEntry class pointer
    */		
	CCalEntry* 			iCalEntry;
		
  	/**
     * CCalInstance class pointer
    */		
	CCalInstance* 		iCalInstance;
	
  	/**
     * Flag to check for the validity of iCalEntry
    */		
	TBool				iIsEntry;
};


/**
* Implemenation of abstract interface to iterate over the collection of UIDSets
*
* @see CLiwIterable
*
*/
class CIterableUIDMapList : public CLiwIterable	
	{
	public:
	  	/**
	     * Two-phase Constructor
	     * @param aList list to be iterated 
	     * @return new CIterableUIDMapList object
	    */	
		static CIterableUIDMapList* NewL( CLiwDefaultList *aUIDMapList );

		/**
		* Resets the iterator. 
		*
		*/
		void Reset();

		/**
		* Iterates over the collection entries to fetch the next data element.
		*
		* @param aEntry contains the next data element and its corresponding data type
		*
		* @return false if there are no more data elements to be fetched;
		* true otherwise
		* 
		*/
		TBool NextL(TLiwVariant&);
		
	    /**
	    * Destructor.
	    */
		~CIterableUIDMapList();

	private:
	
	    /**
	    * Constructor
	     * @param aList list to be iterated 
	     * @return void
	    */
		CIterableUIDMapList( CLiwDefaultList *aUIDMapList );


	private:
	
	  	/**
	     * CLiwDefaultList  class pointer
	    */		
		CLiwDefaultList *iUIDMapList;

	  	/**
	     * Index on list
	    */		
		TInt					iIndex;	
	};
	
#endif __CALENDARITERABLEIMPL_H
