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

#include "calendariterableimpl.h"
#include "calendarconstants.h"
#include "calendarinterface.h"

// ---------------------------------------------------------------------------
// Two-Phase constructor
// ---------------------------------------------------------------------------
//
CIterableCalendarList* CIterableCalendarList::NewL( CDesCArray* aList )
	{
	return new(ELeave) CIterableCalendarList( aList );
	}
	
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CIterableCalendarList::~CIterableCalendarList()
	{
	if( iList )
		{
		iList->Reset();
		delete iList;
		}
	
	}
	
// ---------------------------------------------------------------------------
// Reset the list
// ---------------------------------------------------------------------------
//
void CIterableCalendarList::Reset()
	{
	iIndex = 0;
	}

// ---------------------------------------------------------------------------
// Gets next element in list
// ---------------------------------------------------------------------------
//
TBool CIterableCalendarList::NextL(TLiwVariant& aNext)
	{
	TBool retValue = EFalse;
	if ( iList && iList->Count() > iIndex )
		{
		aNext.SetL( (*iList)[iIndex] );
		iIndex++;
		retValue = ETrue;
		}
	return retValue;
	}


// ---------------------------------------------------------------------------
// Constructor
// ---------------------------------------------------------------------------
//
CIterableCalendarList::CIterableCalendarList(CDesCArray* aList):
	iList( aList )
	{
	}


// ---------------------------------------------------------------------------
// Two-Phase constructor
// ---------------------------------------------------------------------------
//
CIterableCalEntryList* CIterableCalEntryList::NewL( CCalendarInterface& aInterface, 
													const TDesC& aCalendarName,
													const TBool aIsEntryList )
	{
	CIterableCalEntryList* self = new(ELeave) CIterableCalEntryList( aInterface, aIsEntryList );
	CleanupStack::PushL(  TCleanupItem(CCalendarInterface::CleanupIterableCalEntry, self ) );
	self->ConstructL(aCalendarName);
	CleanupStack::Pop();
	return self;
	}
	
// ---------------------------------------------------------------------------
// Two-Phase constructor
// ---------------------------------------------------------------------------
//
void CIterableCalEntryList::ConstructL( const TDesC& aCalendarName )
	{
	if( aCalendarName.Length() )
		iCalendarName = aCalendarName.AllocL();
	}
	
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CIterableCalEntryList::~CIterableCalEntryList()
	{
	if ( !iIsResourceFree )
		{
		iInterface.RemoveCalEntryListFromArray( this );
		iInstanceList.ResetAndDestroy();
		iEntryList.ResetAndDestroy();
		}
		
	delete iCalendarName;	
	}
	
// ---------------------------------------------------------------------------
// Constructor
// ---------------------------------------------------------------------------
//
CIterableCalEntryList::CIterableCalEntryList( CCalendarInterface& aInterface, 
												const TBool aIsEntryList ):
	iIsEntryList( aIsEntryList ),
	iInterface( aInterface )
	{
	}

// ---------------------------------------------------------------------------
// Reset the list
// ---------------------------------------------------------------------------
//
void CIterableCalEntryList::Reset()
	{
	iIndex = 0;
	}

// ---------------------------------------------------------------------------
// Gets next element in list
// ---------------------------------------------------------------------------
//
TBool CIterableCalEntryList::NextL(TLiwVariant& aNext)
	{
	TBool retValue = EFalse;
	
	TInt count = iIsEntryList? iEntryList.Count() : iInstanceList.Count();
	
	if ( count > iIndex )
		{
		// Create the Map for Instance/Entry and return it. Ownership is also passed to User.
		if( iIsEntryList )
			{
			CLiwCalEntryMap* entryMap = CLiwCalEntryMap::NewL( iEntryList[iIndex] );
			CleanupClosePushL( *entryMap );
			aNext.SetL( entryMap );
			CleanupStack::PopAndDestroy( entryMap );
			}
		else
			{
			CLiwCalEntryMap* instanceMap = CLiwCalEntryMap::NewL( iInstanceList[iIndex] );
			CleanupClosePushL( *instanceMap );
			aNext.SetL( instanceMap );
			CleanupStack::PopAndDestroy( instanceMap );
			}	
		iIndex++;
		retValue = ETrue;
		}
	return retValue;
	}

// ---------------------------------------------------------------------------
// Return reference of the collection Entries.
// ---------------------------------------------------------------------------
//
RPointerArray<CCalEntry>& CIterableCalEntryList::EntryArray()
	{
	return iEntryList;
	}

// ---------------------------------------------------------------------------
// Return reference of the collection Instances.
// ---------------------------------------------------------------------------
//
RPointerArray<CCalInstance>& CIterableCalEntryList::InstanceArray()
	{
	return iInstanceList;
	}

// ---------------------------------------------------------------------------
// Free the resources held by this Iterator
// ---------------------------------------------------------------------------
//
void CIterableCalEntryList::SetResourceFree()
	{
	iInstanceList.ResetAndDestroy();
	iEntryList.ResetAndDestroy();
	iIsResourceFree = ETrue;
	}

// ---------------------------------------------------------------------------
// Returns calendar name
// ---------------------------------------------------------------------------
//
TPtrC CIterableCalEntryList::CalendarName()
	{
	return iCalendarName ? TPtrC( *iCalendarName ) : TPtrC();
	}

		
// ---------------------------------------------------------------------------
// Two-Phase constructor
// ---------------------------------------------------------------------------
//
CLiwCalEntryMap* CLiwCalEntryMap::NewL( CCalEntry* aCalEntry )
    {
    CLiwGenericParamList* gl = CLiwGenericParamList::NewLC();
    CLiwCalEntryMap* tempMap = new (ELeave) CLiwCalEntryMap(gl, aCalEntry );
    CleanupStack::Pop(gl); 
    return tempMap;
    }

// ---------------------------------------------------------------------------
// Two-Phase constructor
// ---------------------------------------------------------------------------
//
CLiwCalEntryMap* CLiwCalEntryMap::NewL( CCalInstance* aCalInstance )
    {
    CLiwGenericParamList* gl = CLiwGenericParamList::NewLC();
    CLiwCalEntryMap* tempMap = new (ELeave) CLiwCalEntryMap(gl, aCalInstance );
    CleanupStack::Pop(gl); 
    return tempMap;
    }

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CLiwCalEntryMap::~CLiwCalEntryMap()
    {
    delete iMap;
    }

// ---------------------------------------------------------------------------
// Inserts a key-value pair element to the map collection. If key already existes,
// it is removed
// ---------------------------------------------------------------------------
//
void CLiwCalEntryMap::InsertL(const TDesC8& aKey, const TLiwVariant& aValue)
    {
    Remove(aKey);
    TLiwGenericParam mp;
    mp.SetNameAndValueL(aKey, aValue);
    iMap->AppendL(mp);
    mp.Reset();
    }

// ---------------------------------------------------------------------------
// Adds Meeting entry elements  to the Map is it doesnot exist already
// ---------------------------------------------------------------------------
//
void CLiwCalEntryMap::PopulateMeetingKeyL( CLiwCalEntryMap* aMap, const TDesC8& aKey )
	{
	// Instance Specific attributes
	if ( aKey.CompareF( KInstStartTime ) == 0 )
		{
		if ( !aMap->iIsEntry && aMap->iCalInstance )
			{
			aMap->InsertL( KInstStartTime, TLiwVariant( aMap->iCalInstance->StartTimeL().TimeUtcL() ));
			}
		}
		
	else if ( aKey.CompareF( KInstEndTime ) == 0 )	
		{
		if ( !aMap->iIsEntry && aMap->iCalInstance )
			{
			aMap->InsertL( KInstEndTime, TLiwVariant( aMap->iCalInstance->EndTimeL().TimeUtcL() ));
			}
		}
	else if(  aKey.CompareF( KSeqNum ) == 0 )	
		{
		aMap->InsertL( KSeqNum, TLiwVariant( TInt32( aMap->iCalEntry->SequenceNumberL() ) ));
		}
		
	else if(  aKey.CompareF( KLocation ) == 0 )	
		{
		aMap->InsertL( KLocation, TLiwVariant( aMap->iCalEntry->LocationL() ) );
		}
		
	else if(  aKey.CompareF( KRepeatDates ) == 0 )	
		{
		RArray<TCalTime> rdates;
		aMap->iCalEntry->GetRDatesL( rdates );
		if ( rdates.Count() > 0 )
			{
    		CLiwDefaultList* dateList = CCalendarInterface::GetDatesListL( rdates );
			aMap->InsertL( KRepeatDates, TLiwVariant( dateList ) );
			dateList->DecRef();
			}
		rdates.Reset();
		}
		
	else if(  aKey.CompareF( KExceptionDates ) == 0 )	
		{
		RArray<TCalTime> rdates;
		aMap->iCalEntry->GetExceptionDatesL( rdates );
		if ( rdates.Count() > 0 )
			{
    		CLiwDefaultList* dateList = CCalendarInterface::GetDatesListL( rdates );
			aMap->InsertL( KExceptionDates, TLiwVariant( dateList ) );
			dateList->DecRef();
			}
		rdates.Reset();
		}
		
 	else if(  aKey.CompareF( KMethod ) == 0 )	
		{
		aMap->InsertL( KMethod, TLiwVariant( CCalendarInterface::GetMethodL( aMap->iCalEntry->MethodL() ) ));
		}
		
 	else if(  aKey.CompareF( KPhoneOwner ) == 0 )	
		{
		CCalUser* phoneOwner = aMap->iCalEntry->PhoneOwnerL();
		if ( phoneOwner )
			{
			aMap->InsertL( KPhoneOwner, TLiwVariant( phoneOwner->Address() ) );
			}
		}
		
 	else if(  aKey.CompareF( KOrganizer ) == 0 )	
		{
		CCalUser* orgraniser = aMap->iCalEntry->OrganizerL();
		if ( orgraniser )
			{
    		CLiwDefaultMap* ownerMap = CCalendarInterface::GetCalUserL( orgraniser );
			aMap->InsertL( KOrganizer, TLiwVariant( ownerMap ) );
			ownerMap->DecRef(); 
			}
		}
		
 	else if(  aKey.CompareF( KAttendeeList ) == 0 )	
		{
		RPointerArray< CCalAttendee >& attendeeList = aMap->iCalEntry->AttendeesL();
		TInt count = attendeeList.Count();
		if ( count > 0 )
			{
	    	CLiwDefaultList* attendList = CLiwDefaultList::NewL();

	    	CleanupClosePushL( *attendList );
	    	
			for ( TInt index = 0; index < count; index++ )
				{
	    		CLiwDefaultMap* attendMap = CCalendarInterface::GetCalUserL( attendeeList[index], ETrue );
				attendList->AppendL( TLiwVariant ( attendMap ) );
				attendMap->DecRef(); 
				}
				
			aMap->InsertL( KAttendeeList, TLiwVariant( attendList ) );

	    	CleanupStack::PopAndDestroy( attendList );
			}
		}

 	else if(  aKey.CompareF( KRepeatRule ) == 0 )	
		{
		TCalRRule repeatRule;
		if ( aMap->iCalEntry->GetRRuleL( repeatRule ) )
			{
    		CLiwDefaultMap* rrMap = CCalendarInterface::GetRRMapL( repeatRule );
    		if ( rrMap )
    			{
				aMap->InsertL( KRepeatRule, TLiwVariant( rrMap ) );
				rrMap->DecRef(); 
    			}
			}
		}
		

	}
// ---------------------------------------------------------------------------
// Adds an element to the Map is it doesnot exist already
// ---------------------------------------------------------------------------
//
void CLiwCalEntryMap::PopulateKeyL( CLiwCalEntryMap* aMap, const TDesC8& aKey )
	{
	// Entry Specific attributes
	if ( aKey.CompareF( KId ) == 0 )
		{
		HBufC* globalUid = HBufC::NewL( aMap->iCalEntry->UidL().Length() + 1 );
		CleanupStack::PushL( globalUid );
		globalUid->Des().Copy( aMap->iCalEntry->UidL() );
		aMap->InsertL( KId, TLiwVariant( *globalUid ));
		CleanupStack::PopAndDestroy( globalUid );
		}
		
	else if ( aKey.CompareF( KLocalId ) == 0 )
		{
		TBuf<KMaxUidLength> localUid;
		localUid.Num(TInt64(aMap->iCalEntry->LocalUidL()));
		aMap->InsertL( KLocalId, TLiwVariant( localUid));
		}
		
	else if ( aKey.CompareF( KType ) == 0 )
		{
		aMap->InsertL( KType, TLiwVariant( CCalendarInterface::GetEntryTypeL( aMap->iCalEntry->EntryTypeL() )));
		}
		
	else if(  aKey.CompareF( KSummary ) == 0 )	
		{
		aMap->InsertL( KSummary, TLiwVariant( aMap->iCalEntry->SummaryL() ));
		}
		
	else if(  aKey.CompareF( KStartTime ) == 0 )	
		{
		if( aMap->iCalEntry->EntryTypeL() != CCalEntry::ETodo )
			{
			if ( !aMap->iIsEntry && aMap->iCalInstance && aMap->iCalEntry->EntryTypeL() == CCalEntry::EAnniv )
				{
				if ( aMap->iCalInstance->StartTimeL().TimeUtcL() != Time::NullTTime() )
					aMap->InsertL( KStartTime, TLiwVariant( aMap->iCalInstance->StartTimeL().TimeUtcL() ));
				}
			else 
				{
				if ( aMap->iCalEntry->StartTimeL().TimeUtcL() != Time::NullTTime() )
					aMap->InsertL( KStartTime, TLiwVariant( aMap->iCalEntry->StartTimeL().TimeUtcL() ));
				}
			}
		}
		
	else if(  aKey.CompareF( KEndTime ) == 0 )	
		{
		if ( ( aMap->iCalEntry->EntryTypeL() == CCalEntry::EAppt ) ||
				( aMap->iCalEntry->EntryTypeL() == CCalEntry::ETodo ) ||
				( aMap->iCalEntry->EntryTypeL() == CCalEntry::EEvent ) )
			{
			if ( aMap->iCalEntry->EndTimeL().TimeUtcL() != Time::NullTTime() )
				aMap->InsertL( KEndTime, TLiwVariant( aMap->iCalEntry->EndTimeL().TimeUtcL() ));
			}
		}
		
	else if(  aKey.CompareF( KReplication ) == 0 )	
		{
		aMap->InsertL( KReplication, TLiwVariant( CCalendarInterface::GetReplicationL( aMap->iCalEntry->ReplicationStatusL() ) ));
		}
		
	else if(  aKey.CompareF( KDescription ) == 0 )	
		{
		aMap->InsertL( KDescription, TLiwVariant( aMap->iCalEntry->DescriptionL() ));
		}
		
	else if(  aKey.CompareF( KPriority ) == 0 )	
		{
		aMap->InsertL( KPriority, TLiwVariant( TInt32( aMap->iCalEntry->PriorityL() ) ));
		}
		
	else if(  aKey.CompareF( KAlarmTime ) == 0 )	
		{
		CCalAlarm* alarm = aMap->iCalEntry->AlarmL();
		if ( alarm )
			{
			CleanupStack::PushL( alarm );
			
			TTimeIntervalMinutes offset = alarm->TimeOffset();
			TTime stTime;
			if ( aMap->iIsEntry )
				{
				stTime = aMap->iCalEntry->StartTimeL().TimeUtcL();
				}
			else
				{
				stTime = aMap->iCalInstance->StartTimeL().TimeUtcL();
				}
			
			stTime -= offset;
	
			aMap->InsertL( KAlarmTime, TLiwVariant( stTime ));

			CleanupStack::PopAndDestroy( alarm );
			}
		}
		
	else if(  aKey.CompareF( KStatus ) == 0 )	
		{
		if ( ( aMap->iCalEntry->EntryTypeL() == CCalEntry::EAppt ) ||
				( aMap->iCalEntry->EntryTypeL() == CCalEntry::ETodo ))
			{
			aMap->InsertL( KStatus, TLiwVariant( CCalendarInterface::GetStatusL( aMap->iCalEntry->StatusL() ) ) );
			}
		}
		
	if ( aMap->iCalEntry->EntryTypeL() == CCalEntry::EAppt )
		{
		PopulateMeetingKeyL( aMap, aKey);
		}
	}
	
// ---------------------------------------------------------------------------
// Finds a value stored in the map collection based on the key.
// ---------------------------------------------------------------------------
//
TBool CLiwCalEntryMap::FindL(const TDesC8& aKey, TLiwVariant& aValue) const
    {
    TInt pos = 0;
    const TLiwGenericParam* tempParam = iMap->FindFirst(pos, aKey);
    if ( tempParam )
        {
        aValue.SetL(tempParam->Value());
        return ETrue;
        }
    else
    	{
    	PopulateKeyL( (CLiwCalEntryMap*)this, aKey );
    	}
    	
	pos = 0;
	tempParam = iMap->FindFirst( pos, aKey );
	
	if ( tempParam )
		{
        aValue.SetL(tempParam->Value());
        return ETrue;
		}

    return EFalse;
    }

// ---------------------------------------------------------------------------
// Returns the number of key-value pair stored in the map collection.
// ---------------------------------------------------------------------------
//
TInt CLiwCalEntryMap::Count() const
    {
    return iMap->Count();
    }

// ---------------------------------------------------------------------------
// Returns the key stored at a specified index. 
// ---------------------------------------------------------------------------
//
TBool CLiwCalEntryMap::AtL(TInt aIndex, TDes8& aKey) const
    {
    if(0 <= aIndex && aIndex < iMap->Count())
        {
        aKey = ((*iMap)[aIndex]).Name();
        return ETrue;   
        }
    else
        {
        return EFalse;  
        }
    }

// ---------------------------------------------------------------------------
// Removes a key from the map collection.
// ---------------------------------------------------------------------------
//
void CLiwCalEntryMap::Remove(const TDesC8& aKey)
    {
    iMap->Remove( aKey );
    }

	
	
// ---------------------------------------------------------------------------
// Two-Phase constructor
// ---------------------------------------------------------------------------
//
CIterableUIDMapList* CIterableUIDMapList::NewL( CLiwDefaultList *aUIDMapList )
	{
	return new(ELeave) CIterableUIDMapList( aUIDMapList );
	}
	
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CIterableUIDMapList::~CIterableUIDMapList()
	{
	if( iUIDMapList )
		{
		iUIDMapList->DecRef(); 
		}
	}
	
// ---------------------------------------------------------------------------
// Reset the list
// ---------------------------------------------------------------------------
//
void CIterableUIDMapList::Reset()
	{
	iIndex = 0;
	}

// ---------------------------------------------------------------------------
// Gets next element in list
// ---------------------------------------------------------------------------
//
TBool CIterableUIDMapList::NextL(TLiwVariant& aNext)
	{
	TBool retValue = EFalse;
	if ( iUIDMapList && iUIDMapList->Count() > iIndex )
		{
		iUIDMapList->AtL( iIndex++, aNext); 
		retValue = ETrue;
		}
	return retValue;
	}


// ---------------------------------------------------------------------------
// Constructor
// ---------------------------------------------------------------------------
//
CIterableUIDMapList::CIterableUIDMapList( CLiwDefaultList *aUIDMapList ):
	 iUIDMapList( aUIDMapList ), iIndex( 0 )
	{
	}