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


#include <e32base.h>
#include <calsession.h>
#include <calinstance.h>
#include <calentryview.h>
#include <calinstanceview.h>
#include <caleninterimutils2.h>
#include <calrrule.h>
#include <calalarm.h>
#include <caluser.h>

#include "calendarheader.h"
#include "calendarconstants.h"
#include "asyncreqobserver.h"
#include "entryattributes.h"
#include "addentry.h"


void CleanupCCalEntryArray(TAny* aPointer);
void CleanupCCalInstanceArray(TAny* aPointer);


// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CCalendarAddEntry* CCalendarAddEntry::NewL( CCalendarSessionInfo* aSessionInfo, 
												CEntryAttributes* aCalendarData )
	{
	return new (ELeave) CCalendarAddEntry( aSessionInfo, aCalendarData );
	}

// ---------------------------------------------------------------------------
// Destructor.
// ---------------------------------------------------------------------------
//
CCalendarAddEntry::~CCalendarAddEntry()
	{
	}

// ---------------------------------------------------------------------------
// Constructor
// ---------------------------------------------------------------------------
//
CCalendarAddEntry::CCalendarAddEntry( CCalendarSessionInfo* aSessionInfo, 
												CEntryAttributes* aCalendarData ):
							iSessionInfo( aSessionInfo ),
							iCalendarEntry( aCalendarData )
	{
	}

// ---------------------------------------------------------------------------
// CAddEntry::AddL
// ---------------------------------------------------------------------------
//
void CCalendarAddEntry::AddL( TUIDSet*& aGuidAdded )
	{
	if ( iCalendarEntry->ModifiedAttributes() & CEntryAttributes::ELocalUid )
		UpdateEntryL( aGuidAdded );
	else
		AddNewEntryL( aGuidAdded );
	}

// ---------------------------------------------------------------------------
// CAddEntry::AddNewEntryL
// ---------------------------------------------------------------------------
//
void CCalendarAddEntry::AddNewEntryL( TUIDSet*& aGuidAdded )
	{
	if ( !( iCalendarEntry->ModifiedAttributes() & CEntryAttributes::EEntryType ))
		User::Leave( KErrArgument );
	
	CCalenInterimUtils2* interimUtils2 = CCalenInterimUtils2::NewL();

    CleanupStack::PushL( interimUtils2 );	           

	// Obtain a new global uid which is an ASCII string
	HBufC8* guid = interimUtils2->GlobalUidL();

	CleanupStack::PopAndDestroy( interimUtils2 );      

	CCalEntry* newEntry = CCalEntry::NewL( iCalendarEntry->EntryType(),
                 guid, iCalendarEntry->Method(), iCalendarEntry->SequenceNumber());

    CleanupStack::PushL( newEntry );             

	if( !( iCalendarEntry->ModifiedAttributes() & CEntryAttributes::EStartTime && 
	                 iCalendarEntry->ModifiedAttributes() & CEntryAttributes::EEndTime ) && 
	                 iCalendarEntry->EntryType() == CCalEntry::EAppt )
		{
		// For Appointment need to have both start and end time
		User::Leave( KErrArgument );	
		}
		
	else if ( ( iCalendarEntry->EntryType() == CCalEntry::EAnniv || 
	                 iCalendarEntry->EntryType() == CCalEntry::EReminder ) )
		{
		// For Reminder and Anniversary need to have start time
		// End time can be set to same as start time
		if ( !(iCalendarEntry->ModifiedAttributes() & CEntryAttributes::EStartTime) ) 
			{
			User::Leave( KErrArgument );	
			}
		else
			{
			iCalendarEntry->SetEndTimeL(iCalendarEntry->StartTime().TimeUtcL());	
			}	
		}
	
	else if ( iCalendarEntry->EntryType() == CCalEntry::EEvent )
		{
		// For Event need to have start time
		if ( !(iCalendarEntry->ModifiedAttributes() & CEntryAttributes::EStartTime) ) 
			{
			User::Leave( KErrArgument );	
			}
		else if( !(iCalendarEntry->ModifiedAttributes() & CEntryAttributes::EEndTime) )	
			{
			iCalendarEntry->SetEndTimeL(iCalendarEntry->StartTime().TimeUtcL());	
			}
		}
		
	// For Todo both endtime and starttime are optional
		
	UpdateEntryAttributesL( newEntry );

	//store the entry in the calendar file
	CCalenInterimUtils2::StoreL(*(iSessionInfo->EntryView()), *newEntry);
	
	aGuidAdded = new(ELeave) TUIDSet;
	CleanupStack::PushL( aGuidAdded );             
	aGuidAdded->iLocalUID = newEntry->LocalUidL();//local uid of the entry
	aGuidAdded->iGlobalUID = newEntry->UidL().AllocL();//global uid of the entry
	CleanupStack::Pop( aGuidAdded );             

	CleanupStack::PopAndDestroy( newEntry );      
	}


	

// ---------------------------------------------------------------------------
// CAddEntry::UpdateEntryL
// ---------------------------------------------------------------------------
//
void CCalendarAddEntry::UpdateEntryL( TUIDSet*& aGuidAdded )
	{
	aGuidAdded = new(ELeave) TUIDSet;

	CleanupStack::PushL( aGuidAdded );             
	
	// Instance Modification as the instance start time has been specified
	if( iCalendarEntry->ModifiedAttributes() & CEntryAttributes::EInsStartTime )
		{
		if( iCalendarEntry->ModifiedAttributes() & CEntryAttributes::ERepeatRule )
			User::Leave( KErrArgument );
		
		TCalTime instanceStTime = iCalendarEntry->InstanceStartTime();

		// Fetch instance having start time specified
		CCalInstance* instance = GetInstanceL( instanceStTime, iCalendarEntry->LocalUid() );
		
		if ( !instance )
			User::Leave( KErrArgument );
		
		CleanupStack::PushL( instance );
		
		TTime inStTime = instanceStTime.TimeLocalL();
		
		TCalTime instStTime;
		
		// if entry is of type appointment set instance start time tom fixed
		if( ( &instance->Entry() )->EntryTypeL() == CCalEntry::EAppt )
			instStTime.SetTimeLocalL( inStTime );
		// for other entry types set time mode to floating
		else
			instStTime.SetTimeLocalFloatingL( inStTime );
		
		CCalEntry* parent = &instance->Entry();
		
	    TCalTime recId = parent->RecurrenceIdL();	
	   
	    TBool newModEntry = ( recId.TimeLocalL() == Time::NullTTime() );

	    CCalEntry* modifyingEntry = NULL;
	    
		// If entry does not have a recurrence id, then it is the parent entry
		if ( newModEntry )
			{
			HBufC8* guid = parent->UidL().AllocL();
	    	
			//Create a modifying entry 
			modifyingEntry = CCalEntry::NewL( parent->EntryTypeL(), guid, 
														iCalendarEntry->Method(),
														iCalendarEntry->SequenceNumber(), 
														instStTime,
														CalCommon::EThisOnly);
		    CleanupStack::PushL( modifyingEntry );
			}
		else
			{
			modifyingEntry = parent;
			}
			        
		// Sets instance start and end time
		SetStartEndTimeL(modifyingEntry, instance->StartTimeL(), instance->EndTimeL() );	  
		       
		// Add new entry or update existing entry
		UpdateEntryAttributesL( modifyingEntry );
		
		// If new modifying is created then update blank fields from parent entry
		if ( newModEntry )
			CCalenInterimUtils2::PopulateChildFromParentL( *modifyingEntry, *parent );

		// Store entry in calendar file
		CCalenInterimUtils2::StoreL( *iSessionInfo->EntryView(), *modifyingEntry, ETrue );		

		// Populate local and global uid fields 
		aGuidAdded->iLocalUID = modifyingEntry->LocalUidL();
		aGuidAdded->iGlobalUID = modifyingEntry->UidL().AllocL();
		
		if ( newModEntry )
			CleanupStack::PopAndDestroy( modifyingEntry );
		
		CleanupStack::PopAndDestroy( instance );
		}
	// Entry Modification
	else
		{
		// Fetch entry to be modified
		CCalEntry* entry = iSessionInfo->EntryView()->FetchL( iCalendarEntry->LocalUid() );
		
		//Invalid LocalUID
		if( !entry )
			User::Leave( KErrArgument );
		
		CleanupStack::PushL( entry );
		
	    // Set entry's start and end time
		SetStartEndTimeL( entry, entry->StartTimeL(), entry->EndTimeL() );	  

	 	// Update only those attributes which have new values
	 	UpdateEntryAttributesL( entry );	

		// Store the updated entry in calendar file
		CCalenInterimUtils2::StoreL( *iSessionInfo->EntryView(), *entry, ETrue );		

		// Populate and return global and local uids
		aGuidAdded->iLocalUID = entry->LocalUidL();
		aGuidAdded->iGlobalUID = entry->UidL().AllocL();

		CleanupStack::PopAndDestroy( entry );
		}	
	
	CleanupStack::Pop( aGuidAdded );             
	}

// ---------------------------------------------------------------------------
// CAddEntry::UpdateEntryAttributesL
// Updates those attributes which have been set
// ---------------------------------------------------------------------------
//	
void CCalendarAddEntry::UpdateEntryAttributesL( CCalEntry* aEntry )
	{
    // Get the attributes which have been set by user
	TInt32 modifiedAttr = iCalendarEntry->ModifiedAttributes();

	if( modifiedAttr & CEntryAttributes::ESummary )
		{
		aEntry->SetSummaryL( iCalendarEntry->Summary() );//set entry summary field	 
		}
		
    if( modifiedAttr & CEntryAttributes::EDescription )
		{
		aEntry->SetDescriptionL( iCalendarEntry->Description() );//set entry description field	 	
		}
		
	if( modifiedAttr & CEntryAttributes::ELocation )
		{
		if ( aEntry->EntryTypeL() == CCalEntry::EAppt ) 
			{
			aEntry->SetLocationL( iCalendarEntry->Location() );	//set entry location field	 
			}
		else
			{
			User::Leave( KErrArgument );	
			}
		}
		
	if( modifiedAttr & CEntryAttributes::EReplication )
		{
		aEntry->SetReplicationStatusL( iCalendarEntry->ReplicationStatus() ); //set entry replication status	 	
		}
		
	if( modifiedAttr & CEntryAttributes::EPriority )
		{
		aEntry->SetPriorityL( iCalendarEntry->Priority() );	//set entry priority field	 
		}
		
	if( modifiedAttr & CEntryAttributes::EStatus )
		{
		if ( aEntry->EntryTypeL() == CCalEntry::EAppt || 
				 aEntry->EntryTypeL() == CCalEntry::ETodo )
			{
			aEntry->SetStatusL( iCalendarEntry->EntryStatus() );// set entry status field	
			}
		else
			{
			User::Leave( KErrArgument );	
			}
		}
	
	if( modifiedAttr & CEntryAttributes::EOrganizer )
		{
		if ( aEntry->EntryTypeL() == CCalEntry::EAppt ) 
			{
			CCalUser* caluser = CCalUser::NewL( iCalendarEntry->Organizer()->Address() );
			CleanupStack::PushL( caluser );
			caluser->SetCommonNameL( iCalendarEntry->Organizer()->CommonName() );
			CleanupStack::Pop( caluser );
			aEntry->SetOrganizerL( caluser ); // set organizer for appointment entry, entry takes ownership 	
			}
		else
			{
			User::Leave( KErrArgument );	
			}
		}
		
	if( modifiedAttr & CEntryAttributes::EAttendees )
		{
		if ( aEntry->EntryTypeL() == CCalEntry::EAppt )
			{
			RPointerArray<CCalAttendee>& attendeeList = iCalendarEntry->AttendeeList();
			
			for ( int i=0; i<attendeeList.Count(); i++ )
				{
				CCalAttendee* caluser = CCalAttendee::NewL( attendeeList[i]->Address() );
				CleanupStack::PushL( caluser );

				caluser->SetCommonNameL( attendeeList[i]->CommonName() );
				caluser->SetRoleL( attendeeList[i]->RoleL() );
				caluser->SetStatusL( attendeeList[i]->StatusL() );
				caluser->SetResponseRequested( attendeeList[i]->ResponseRequested() );
				
				CleanupStack::Pop( caluser );
				aEntry->AddAttendeeL(caluser);// add attendee to appointment entry, entry takes ownership
			    }	
			}
		else
			{
			User::Leave( KErrArgument );	
			}
			
		
		}
	
	if( modifiedAttr & CEntryAttributes::EPhoneOwner )
		{
		if ( aEntry->EntryTypeL() == CCalEntry::EAppt )
			{
			TBool ownerSet = EFalse;	
	        
	        RPointerArray<CCalAttendee>& attendeeList = aEntry->AttendeesL();

	        for ( int i=0;i<attendeeList.Count();i++ )
				{
				// phone owner must match one of the attendees
				if( iCalendarEntry->PhoneOwner().CompareF( attendeeList[i]->Address() ) == 0 )
					{
					aEntry->SetPhoneOwnerL( attendeeList[i] ); //add phone owner to appointment entry
					ownerSet = ETrue; //  entry takes ownership
					break;
					}
				}

            if( !ownerSet)
				{
				User::Leave( KErrArgument );
				}
			}
		else
			{
			User::Leave( KErrArgument );	
			}
		}

	if( modifiedAttr & CEntryAttributes::ESeqNum )
		{
		if ( aEntry->EntryTypeL() == CCalEntry::EAppt )
			{
			aEntry->SetSequenceNumberL( iCalendarEntry->SequenceNumber() );	 // set entry sequence number field
			}
		else
			{
			User::Leave( KErrArgument );	
			}
		}
		
	if( modifiedAttr & CEntryAttributes::EMethod )
		{
		if ( aEntry->EntryTypeL() == CCalEntry::EAppt )
			{
			aEntry->SetMethodL( iCalendarEntry->Method() );	 
			}
		else
			{
			User::Leave( KErrArgument );	
			}
		}
	
		
	if( modifiedAttr & CEntryAttributes::EStartTime ||  modifiedAttr & CEntryAttributes::EEndTime )
		{
		if( aEntry->EntryTypeL() == CCalEntry::EAppt || 
			 aEntry->EntryTypeL() == CCalEntry::EEvent )
			{
			// Meeting needs to be Fixed time
			if( iCalendarEntry->StartTime().TimeLocalL() <= iCalendarEntry->EndTime().TimeLocalL() )
				{
				aEntry->SetStartAndEndTimeL( iCalendarEntry->StartTime(), iCalendarEntry->EndTime() );	
				}
			else
				{
				User::Leave( KErrArgument );	
				}	
			}
		
		else 
			{
			// Except Meeting all need to be floating time
			TCalTime startTime = iCalendarEntry->StartTime();
			TCalTime endTime = iCalendarEntry->EndTime();

			if( startTime.TimeLocalL() != Time::NullTTime() && endTime.TimeLocalL() != Time::NullTTime() )
				{
				if ( startTime.TimeLocalL() > endTime.TimeLocalL() )
					{
					User::Leave( KErrArgument );	
					}	
				}

			startTime.SetTimeLocalFloatingL( startTime.TimeLocalL() );
			endTime.SetTimeLocalFloatingL( endTime.TimeLocalL() );
			
			aEntry->SetStartAndEndTimeL( startTime, endTime );	 	
			}
		}
		
	if(  modifiedAttr & CEntryAttributes::EAlarmTime )
		{
		TTime alarmTime = iCalendarEntry->AlarmTime();
    	TTimeIntervalMinutes minutes;
	    if ( alarmTime != Time::NullTTime() )
		    {
		    TDateTime alDtTime = alarmTime.DateTime();
		    alDtTime.SetSecond(0);
		    alDtTime.SetMicroSecond(0);
		    TTime alTime( alDtTime );

		    if ( aEntry->EntryTypeL() == CCalEntry::EAppt || aEntry->EntryTypeL() == CCalEntry::EReminder )
			    {
			    if( alarmTime > iCalendarEntry->StartTime().TimeUtcL() )
			    	User::Leave( KErrNotSupported );	
			    }
			    
			else if( aEntry->EntryTypeL() == CCalEntry::EAnniv || aEntry->EntryTypeL() == CCalEntry::EEvent)
				{
				TTime starttime = iCalendarEntry->StartTime().TimeUtcL();
				TDateTime startdttime = starttime.DateTime();
				startdttime.SetHour(0);
				startdttime.SetMinute(0);
				startdttime.SetSecond(0);
				startdttime.SetMicroSecond(0);
				TTime temp( startdttime );
				temp = temp + TTimeIntervalDays(1);
				if( alarmTime >= temp )
					User::Leave( KErrNotSupported );	
				}
		    
		    TDateTime stTime;
	    	stTime = aEntry->StartTimeL().TimeUtcL().DateTime();
		    alTime.MinutesFrom( stTime, minutes );// calculate the offset between alarm time and start time
		    CCalAlarm* alarm = CCalAlarm::NewL();
		    CleanupStack::PushL( alarm );
		    alarm->SetTimeOffset(-minutes.Int());
			aEntry->SetAlarmL(alarm); // set the alarm for the entry
		    CleanupStack::PopAndDestroy( alarm );
		    }	
		}
			
	TBool parentEntry = EFalse;
	
	if ( aEntry->RecurrenceIdL().TimeLocalL() == Time::NullTTime())
		{
		parentEntry = ETrue;
		}
		
	if( parentEntry )
		{
		if ( iCalendarEntry->RepeatRuleL().Type() != TCalRRule::EInvalid )// if repeat rule is valid
			{
			if ( aEntry->EntryTypeL() == CCalEntry::EAppt || aEntry->EntryTypeL() == CCalEntry::EAnniv)// set rp rule st time to entry st time and calc st day for weekly repeat from entry's st time
				{
				TCalTime sttime;
				if ( modifiedAttr & CEntryAttributes::ELocalUid )
					{
					CCalEntry* entry = iSessionInfo->EntryView()->FetchL( iCalendarEntry->LocalUid() );
					if ( entry )
						{
						CleanupStack::PushL( entry );
						sttime = entry->StartTimeL();
						CleanupStack::PopAndDestroy( entry );
						}
					else
						{
						User::Leave( KErrArgument );
						}
					}
				else
					{
					sttime = iCalendarEntry->StartTime();	
					}
				if ( iCalendarEntry->RepeatRuleL().DtStart().TimeLocalL() == Time::NullTTime() )
					{
					iCalendarEntry->RepeatRuleL().SetDtStart( sttime );	
					}
				if ( iCalendarEntry->RepeatRuleL().Type() == TCalRRule::EWeekly )
					{
					RArray<TDay> weekDays;
					iCalendarEntry->RepeatRuleL().GetByDayL( weekDays );
					if( weekDays.Count() == 0 )
						{
						weekDays.Reset();
						weekDays.Append( TDay( sttime.TimeLocalL().DayNoInWeek() ) );
						iCalendarEntry->RepeatRuleL().SetByDay( weekDays  );	
						}
					weekDays.Close();
					}
					
				else if ( iCalendarEntry->RepeatRuleL().Type() == TCalRRule::EMonthly )
					{
					RArray<TInt> monthDates;
					iCalendarEntry->RepeatRuleL().GetByMonthDayL( monthDates );
					RArray<TCalRRule::TDayOfMonth> monthDays;
					iCalendarEntry->RepeatRuleL().GetByDayL( monthDays );
					
					if( monthDates.Count() > 0 && monthDays.Count() > 0 )
						{
						User::Leave( KErrArgument );	
						}
					if( monthDates.Count() == 0 && monthDays.Count() == 0 )
						{
						monthDates.Reset();
						monthDates.Append( sttime.TimeLocalL().DayNoInMonth() );
						iCalendarEntry->RepeatRuleL().SetByMonthDay( monthDates  );	
						}
					monthDays.Close();
					monthDates.Close();
					}

				aEntry->SetRRuleL(iCalendarEntry->RepeatRuleL());    
				}
			else
				{
				User::Leave( KErrArgument );	
				}	
			}
		}

	if( ( modifiedAttr & CEntryAttributes::ERepeatDates ) && parentEntry ) // only parent entry can have repeat dates
		{
		if ( aEntry->EntryTypeL() == CCalEntry::EAppt )
			{
			aEntry->SetRDatesL( iCalendarEntry->RepeatDates() );
			}
		else
			{
			User::Leave( KErrArgument );	
			}	
		}	
		
	
		
	if( ( modifiedAttr & CEntryAttributes::EExDates ) && parentEntry )// only parent entry can have exception dates
		{
		if ( aEntry->EntryTypeL() == CCalEntry::EAppt )
			{
			aEntry->SetExceptionDatesL( iCalendarEntry->ExceptionDates() );	
			}
		else
			{
			User::Leave( KErrArgument );	
			}
		}
	}
	
// ---------------------------------------------------------------------------
// CCalendarAddEntry::GetInstanceL
// Retrieves the Instance for the given local Uid
// ---------------------------------------------------------------------------
//
CCalInstance* CCalendarAddEntry::GetInstanceL( const TCalTime& aInsStTime, 
													TCalLocalUid aLUid )
	{
	CCalInstance* instance = NULL;

	RPointerArray<CCalInstance> insArray( KArrayGran );

	CleanupStack::PushL( TCleanupItem(CleanupCCalInstanceArray, &insArray) );
	
	// Find instance having the instance start time specified
	iSessionInfo->InstanceView()->FindInstanceL(insArray, CalCommon::EIncludeAll, 
											CalCommon::TCalTimeRange(aInsStTime, aInsStTime));
	
	TInt count = insArray.Count();
	
	for( TInt index = 0 ; index < count; index++ )
		{
		if ( insArray[index]->Entry().LocalUidL() == aLUid )
			{
			instance = insArray[index];
			insArray[index] = NULL;	
			break;
			}
		}
	CleanupStack::PopAndDestroy( &insArray );	
	
	return instance;
	}

// ---------------------------------------------------------------------------
// CCalendarAddEntry::SetStartEndTimeL
// Set instance start and end time
// ---------------------------------------------------------------------------
//
void CCalendarAddEntry::SetStartEndTimeL( CCalEntry* aEntry, const TCalTime& aStTime, const TCalTime& aEndTime )
	{
    if( aEntry->EntryTypeL() == CCalEntry::EEvent || aEntry->EntryTypeL() == CCalEntry::EReminder ||
             aEntry->EntryTypeL() == CCalEntry::EAnniv )	
		{
	    //if start time is not specified for instance, it is taken from parent 
	    if ( iCalendarEntry->ModifiedAttributes() & CEntryAttributes::EStartTime ) 
			{
			iCalendarEntry->SetEndTimeL( iCalendarEntry->StartTime().TimeUtcL() );	
			} 
		else
			{
			iCalendarEntry->SetStartTimeL( aStTime.TimeUtcL() );
			iCalendarEntry->SetEndTimeL( aStTime.TimeUtcL() );
			}
		}
	    
	    	
    //if end time is not specified for instance, it is taken from parent    
    else if ( aEntry->EntryTypeL() == CCalEntry::ETodo )
	    {
	    if ( iCalendarEntry->ModifiedAttributes() & CEntryAttributes::EEndTime )
			{
			iCalendarEntry->SetStartTimeL( iCalendarEntry->EndTime().TimeUtcL() );	
			}
		else
			{
			iCalendarEntry->SetStartTimeL( aEndTime.TimeUtcL() );
			iCalendarEntry->SetEndTimeL( aEndTime.TimeUtcL() );
			}	
	    }
		
    // both start and end time need to be specified for instance whose  entry type is an appointment, else they are taken from parent	
    else if ( aEntry->EntryTypeL() == CCalEntry::EAppt )
	    {
	    if ( !( iCalendarEntry->ModifiedAttributes() & CEntryAttributes::EStartTime || 
             iCalendarEntry->ModifiedAttributes() & CEntryAttributes::EEndTime ) )
	    	{
	    	// No time set
		    iCalendarEntry->SetStartTimeL( aStTime.TimeUtcL() );
		    iCalendarEntry->SetEndTimeL( aEndTime.TimeUtcL() );	
	    	}
	    else if(!( iCalendarEntry->ModifiedAttributes() & CEntryAttributes::EStartTime ))
	    	{
	    	// Set End time
		    iCalendarEntry->SetStartTimeL( aStTime.TimeUtcL() );
	    	}
	    else if(!( iCalendarEntry->ModifiedAttributes() & CEntryAttributes::EEndTime ))
	    	{
	    	// Set Start time
		    iCalendarEntry->SetEndTimeL( aEndTime.TimeUtcL() );	
	    	}
		}
	}
