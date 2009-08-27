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

#include <calentry.h>
#include <calrrule.h>
#include <caluser.h>

#include "entryattributes.h"
#include "calendarconstants.h"

// ---------------------------------------------------------------------------
// CAttendeeInfo::NewL
// ---------------------------------------------------------------------------
//
EXPORT_C CAttendeeInfo* CAttendeeInfo::NewL( const TDesC& aAddress )
	{
	CAttendeeInfo* self = new (ELeave) CAttendeeInfo;
	CleanupStack::PushL( self );
	self->ConstructL( aAddress );
	CleanupStack::Pop( self );
	return self;
	}

// ---------------------------------------------------------------------------
// Constructor
// ---------------------------------------------------------------------------
//
CAttendeeInfo::CAttendeeInfo()
	{
	iResponse = EFalse;
	}	

// ---------------------------------------------------------------------------
// 2nd-phased constructor of two phase construction
// ---------------------------------------------------------------------------
//
void CAttendeeInfo::ConstructL( const TDesC& aAddress )
	{
	if( aAddress.Length() )
		{
		iAddress = aAddress.AllocL();
		}
	else
		User::Leave(KErrArgument);
	}

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//	
CAttendeeInfo::~CAttendeeInfo()
	{
	delete iAddress;
	delete iCommonName;
	delete iRole;
	delete iStatus;
	}	

// ---------------------------------------------------------------------------
// CAttendeeInfo::SetCommonNameL
// ---------------------------------------------------------------------------
//
EXPORT_C void CAttendeeInfo::SetCommonNameL( const TDesC& aName )
	{
	if( aName.Length() )
		{
		iCommonName = aName.AllocL();
		}
	}

// ---------------------------------------------------------------------------
// CAttendeeInfo::SetRoleL
// ---------------------------------------------------------------------------
//
EXPORT_C void CAttendeeInfo::SetRoleL( const TDesC& aRole )
	{
	if( aRole.Length() )
		{
		iRole = aRole.AllocL();
		}
	}

// ---------------------------------------------------------------------------
// CAttendeeInfo::SetStatusL
// ---------------------------------------------------------------------------
//
EXPORT_C void CAttendeeInfo::SetStatusL( const TDesC& aStatus )
	{
	if( aStatus.Length() )
		{
		iStatus = aStatus.AllocL();
		}
	}

// ---------------------------------------------------------------------------
// CAttendeeInfo::SetRsvp
// ---------------------------------------------------------------------------
//
EXPORT_C void CAttendeeInfo::SetRsvp( const TBool aResponse )
	{
	iResponse = aResponse;	
	}
	
// ---------------------------------------------------------------------------
// CAttendeeInfo::Address
// ---------------------------------------------------------------------------
//
EXPORT_C TPtrC CAttendeeInfo::Address()
	{
	return iAddress ? TPtrC( *iAddress ) : TPtrC();		
	}

// ---------------------------------------------------------------------------
// CAttendeeInfo::CommonName
// ---------------------------------------------------------------------------
//
EXPORT_C TPtrC CAttendeeInfo::CommonName()
	{
	return iCommonName ? TPtrC( *iCommonName ) : TPtrC();		
	}

// ---------------------------------------------------------------------------
// CAttendeeInfo::Role
// ---------------------------------------------------------------------------
//
EXPORT_C TPtrC CAttendeeInfo::Role()
	{
	return iRole ? TPtrC( *iRole ) : TPtrC();		
	}


// ---------------------------------------------------------------------------
// CAttendeeInfo::Statuse
// ---------------------------------------------------------------------------
//
EXPORT_C TPtrC CAttendeeInfo::Status()
	{
	return iStatus ? TPtrC( *iStatus ) : TPtrC();
	}

// ---------------------------------------------------------------------------
// CAttendeeInfo::ResponseRequested
// ---------------------------------------------------------------------------
//
EXPORT_C TBool CAttendeeInfo::ResponseRequested()
	{
	return iResponse;	
	}

// ---------------------------------------------------------------------------
// CRepeatInfo::NewL
// ---------------------------------------------------------------------------
//
EXPORT_C CRepeatInfo* CRepeatInfo::NewL( const TInt aType )
	{
	CRepeatInfo* self = new (ELeave) CRepeatInfo;
	CleanupStack::PushL( self );
	self->ConstructL( aType );
	CleanupStack::Pop( self );
	return self;
	}

// ---------------------------------------------------------------------------
// Constructor
// ---------------------------------------------------------------------------
//
CRepeatInfo::CRepeatInfo()
	{
	iInterval = 1;
	iType = TCalRRule::EInvalid;
	}	

// ---------------------------------------------------------------------------
// 2nd-phased constructor of two phase construction
// ---------------------------------------------------------------------------
//
void CRepeatInfo::ConstructL( const TInt aType )
	{
	if ( aType == KRRTypeDaily )
		iType = TCalRRule::EDaily;
	
	else if ( aType == KRRTypeWeekly )
		iType = TCalRRule::EWeekly;
	
	else if ( aType == KRRTypeMonthly )
		iType = TCalRRule::EMonthly;
	
	else if ( aType == KRRTypeYearly )
		iType = TCalRRule::EYearly;
	
	else
		User::Leave(KErrArgument);	
	
	iRule.SetType( iType );
	}
	
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CRepeatInfo::~CRepeatInfo()
	{
	iMonthDays.Close();
	iMonthDates.Close();
	iWeekDays.Close();
	}
	
// ---------------------------------------------------------------------------
// CRepeatInfo::SetCount
// ---------------------------------------------------------------------------
//
EXPORT_C void CRepeatInfo::SetCount( const TUint aCount )
	{
	iRule.SetCount( aCount );
	}

// ---------------------------------------------------------------------------
// CRepeatInfo::SetUntilTimeL
// ---------------------------------------------------------------------------
//
EXPORT_C void CRepeatInfo::SetUntilTimeL( const TTime& aUntilTime )
	{
	if( aUntilTime < TCalTime::MinTime() || aUntilTime > TCalTime::MaxTime() )
		User::Leave( KErrArgument );

	iUntilTime.SetTimeUtcL( aUntilTime );	
	iRule.SetUntil( iUntilTime );
	}

// ---------------------------------------------------------------------------
// CRepeatInfo::SetStartTimeL
// ---------------------------------------------------------------------------
//
EXPORT_C void CRepeatInfo::SetStartTimeL( const TTime& aStartTime )
	{
	if( aStartTime < TCalTime::MinTime() || aStartTime > TCalTime::MaxTime() )
		User::Leave( KErrArgument );

	iStartTime.SetTimeUtcL( aStartTime );	
	iRule.SetDtStart( iStartTime );
	}

// ---------------------------------------------------------------------------
// CRepeatInfo::SetInterval
// ---------------------------------------------------------------------------
//		
EXPORT_C void CRepeatInfo::SetInterval( const TInt aInterval )
	{
	iInterval = aInterval;	
	iRule.SetInterval( iInterval );
	}

// ---------------------------------------------------------------------------
// CRepeatInfo::SetDaysInWeek
// ---------------------------------------------------------------------------
//
EXPORT_C void CRepeatInfo::SetDaysInWeek( const RArray<TDay>& aDays )
	{
	if( iType == TCalRRule::EWeekly )
		{
		for( int i=0 ; i<aDays.Count() ; i++)
			iWeekDays.Append( aDays[i] );
		iRule.SetByDay( iWeekDays );
		}
	}
	
// ---------------------------------------------------------------------------
// CRepeatInfo::SetMonthDates
// ---------------------------------------------------------------------------
//
EXPORT_C void CRepeatInfo::SetMonthDates( const RArray<TInt>& aMonthDates  )
	{
	if( iType == TCalRRule::EMonthly )
		{
		// sets the month dates for the monthly repeat
		for( int i=0 ; i<aMonthDates.Count() ; i++)
			iMonthDates.Append( aMonthDates[i] );
		iRule.SetByMonthDay( iMonthDates );
		}
		
	}
	
// ---------------------------------------------------------------------------
// CRepeatInfo::SetMonthDays
// ---------------------------------------------------------------------------
//
EXPORT_C void CRepeatInfo::SetMonthDays( const RArray<TCalRRule::TDayOfMonth>& aDays )
	{
	if( iType == TCalRRule::EMonthly || iType == TCalRRule::EYearly )
		{
		TInt count = aDays.Count();
		// sets the days of the month for monthly and yearly repeats
		for( TInt i=0 ; i < count ; i++)
			{
			iMonthDays.Append( aDays[i] );
			}
		iRule.SetByDay( iMonthDays );	
		}
		
	}
	
// ---------------------------------------------------------------------------
// CRepeatInfo::SetMonth
// ---------------------------------------------------------------------------
//
EXPORT_C void CRepeatInfo::SetMonth( const TInt aMonth)
	{
	// sets the month for a yearly repeat
	if( iType == TCalRRule::EYearly )
		{
		iMonth = TMonth( aMonth );
    		RArray<TMonth> monthList;
		monthList.Append( iMonth );
		iRule.SetByMonth( monthList );
		}	
    	}
	
// ---------------------------------------------------------------------------
// CRepeatInfo::SetWeekStart
// ---------------------------------------------------------------------------
//
EXPORT_C void CRepeatInfo::SetWeekStart( const TInt aDay )
	{
	iWkSt = TDay( aDay );
	iRule.SetWkSt( iWkSt );	
	}

// ---------------------------------------------------------------------------
// CRepeatInfo::WeekStart
// ---------------------------------------------------------------------------
//
EXPORT_C TDay CRepeatInfo::WeekStart()
	{
	return iWkSt;
	}

// ---------------------------------------------------------------------------
// CRepeatInfo::Month
// ---------------------------------------------------------------------------
//	
EXPORT_C TMonth CRepeatInfo::Month()
	{
	return iMonth;	
	}

// ---------------------------------------------------------------------------
// CRepeatInfo::DaysInWeek
// ---------------------------------------------------------------------------
//	
EXPORT_C RArray<TDay>& CRepeatInfo::DaysInWeek()
	{
	return iWeekDays;	
	}
	
// ---------------------------------------------------------------------------
// CRepeatInfo::DaysInMonth
// ---------------------------------------------------------------------------
//
EXPORT_C RArray<TCalRRule::TDayOfMonth>& CRepeatInfo::DaysInMonth()
	{
	return iMonthDays;	
	}
	
// ---------------------------------------------------------------------------
// CRepeatInfo::DatesInMonth
// ---------------------------------------------------------------------------
//
EXPORT_C RArray<TInt>& CRepeatInfo::DatesInMonth()
	{
	return iMonthDates;	
	}
	
// ---------------------------------------------------------------------------
// CRepeatInfo::Interval
// ---------------------------------------------------------------------------
//
EXPORT_C TInt CRepeatInfo::Interval()
	{
	return iInterval;	
	}
	
// ---------------------------------------------------------------------------
// CRepeatInfo::UntilDate
// ---------------------------------------------------------------------------
//
EXPORT_C TCalTime& CRepeatInfo::UntilDate()
	{
	return iUntilTime;	
	}
	
// ---------------------------------------------------------------------------
// CRepeatInfo::Type
// ---------------------------------------------------------------------------
//
EXPORT_C TCalRRule::TType CRepeatInfo::Type()
	{
	return iType;	
	}

// ---------------------------------------------------------------------------
// CRepeatInfo::GetRepeatRule
// ---------------------------------------------------------------------------
//
EXPORT_C TCalRRule& CRepeatInfo::GetRepeatRule()	
	{
	return iRule;	
	}

// ---------------------------------------------------------------------------
// CEntryAttributes::NewL
// ---------------------------------------------------------------------------
//	
EXPORT_C CEntryAttributes* CEntryAttributes::NewL( const TDesC& aType )
	{
	CEntryAttributes* self = new (ELeave) CEntryAttributes;
	CleanupStack::PushL( self );
	self->ConstructL( aType );
	CleanupStack::Pop( self );
	return self;
	}
	
// ---------------------------------------------------------------------------
// CEntryAttributes::NewL
// ---------------------------------------------------------------------------
//	
EXPORT_C CEntryAttributes* CEntryAttributes::NewL()
	{
	return new (ELeave) CEntryAttributes;
	}

// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//	
CEntryAttributes::~CEntryAttributes()
	{
	delete iSummary;
	delete iDescription;
	delete iLocation;
	delete iPhoneOwner;
    delete iOrganizer;
    delete iUid;
    iRepeatDates.Close();
	iExDates.Close();

	iAttendees.ResetAndDestroy();
	}

// ---------------------------------------------------------------------------
// CEntryAttributes::ConstructL
// ---------------------------------------------------------------------------
//
void CEntryAttributes::ConstructL( const TDesC& aType )
	{
	SetTypeL( aType );
	iStartTime.SetTimeUtcL( Time::NullTTime() );
	iEndTime.SetTimeUtcL( Time::NullTTime() );
	}

// ---------------------------------------------------------------------------
// CEntryAttributes::SetTypeL
// ---------------------------------------------------------------------------
//
EXPORT_C void CEntryAttributes::SetTypeL( const TDesC& aType )
	{
	if ( aType.CompareF(KEntryAppt) == 0 )
		iType = CCalEntry::EAppt; // apointment entry
	
	else if ( aType.CompareF(KEntryTodo) == 0 )
		iType = CCalEntry::ETodo; // todo entry
	
	else if ( aType.CompareF(KEntryEvent) == 0 )
		iType = CCalEntry::EEvent; // event entry
	
	else if ( aType.CompareF(KEntryReminder) == 0 )
		iType = CCalEntry::EReminder; // reminder entry
	
	else if ( aType.CompareF(KEntryAnniv) == 0 )
		iType = CCalEntry::EAnniv; // anniversary entry
	
	else
		User::Leave(KErrArgument);
	
	iSetAttributes |= EEntryType;
	}
		

// ---------------------------------------------------------------------------
// CEntryAttributes::SetStartTimeL
// ---------------------------------------------------------------------------
//	
EXPORT_C void CEntryAttributes::SetStartTimeL( const TTime& aStartTime )
	{
	if ( aStartTime != Time::NullTTime())
		{
		if( aStartTime < TCalTime::MinTime() || aStartTime > TCalTime::MaxTime() )
			User::Leave( KErrArgument );
		
		iSetAttributes |= EStartTime;
		iStartTime.SetTimeUtcL( aStartTime );
		}
	}

// ---------------------------------------------------------------------------
// CEntryAttributes::SetEndTimeL
// ---------------------------------------------------------------------------
//	
EXPORT_C void CEntryAttributes::SetEndTimeL( const TTime& aEndTime )
	{
	if ( aEndTime != Time::NullTTime() )
		{
		if( aEndTime < TCalTime::MinTime() || aEndTime > TCalTime::MaxTime() )
			User::Leave( KErrArgument );
		
		iEndTime.SetTimeUtcL( aEndTime );
		iSetAttributes |= EEndTime;
		}
	}

// ---------------------------------------------------------------------------
// CEntryAttributes::SetInstanceStartTimeL
// ---------------------------------------------------------------------------
//
EXPORT_C void CEntryAttributes::SetInstanceStartTimeL( const TTime& aInsTime )
	{
	if ( aInsTime != Time::NullTTime() )
		{
		if( aInsTime < TCalTime::MinTime() || aInsTime > TCalTime::MaxTime() )
			User::Leave( KErrArgument );

		iInstanceStartTime.SetTimeUtcL( aInsTime );
		iSetAttributes |= EInsStartTime;
		
		}
	}

// ---------------------------------------------------------------------------
// CEntryAttributes::SetAlarm
// ---------------------------------------------------------------------------
//
EXPORT_C void CEntryAttributes::SetAlarm( const TTime& aAlarmTime)
	{
	if( aAlarmTime < TCalTime::MinTime() || aAlarmTime > TCalTime::MaxTime() )
		User::Leave( KErrArgument );

	iAlarmTime = aAlarmTime;
	iSetAttributes |= EAlarmTime;
	}

// ---------------------------------------------------------------------------
// CEntryAttributes::SetSequenceNumber
// ---------------------------------------------------------------------------
//
EXPORT_C void CEntryAttributes::SetSequenceNumber( TInt aSeqNum )
	{
	iSequenceNum = aSeqNum;
	iSetAttributes |= ESeqNum;
	}

// ---------------------------------------------------------------------------
// CEntryAttributes::SetEntryStatusL
// ---------------------------------------------------------------------------
//	
EXPORT_C void CEntryAttributes::SetEntryStatusL( const TDesC& aStatus )
	{
	if ( aStatus.CompareF(KNullStatus) == 0 )
		iEntryStatus = CCalEntry::ENullStatus; // null status
	
	else if ( aStatus.CompareF(KStatusTentative) == 0 )
		iEntryStatus = CCalEntry::ETentative; // status is tentative
	
	else if ( aStatus.CompareF(KStatusConfirmed) == 0 )
		iEntryStatus = CCalEntry::EConfirmed; // status is confirmed
	
	else if ( aStatus.CompareF(KStatusCancelled) == 0 )
		iEntryStatus = CCalEntry::ECancelled; // status is cancelled
	
	else if ( aStatus.CompareF(KStatusTodoNeedsAction) == 0 )
		iEntryStatus = CCalEntry::ETodoNeedsAction; //status of todo is needs action
	
	else if ( aStatus.CompareF(KStatusTodoCompleted) == 0 )
		iEntryStatus = CCalEntry::ETodoCompleted;//status of todo is completed
	
	else if ( aStatus.CompareF(KStatusTodoInProcess) == 0 )
		iEntryStatus = CCalEntry::ETodoInProcess; // status of todo is in process
	
	else
		User::Leave(KErrArgument);
	
	iSetAttributes |= EStatus;
	}

// ---------------------------------------------------------------------------
// CEntryAttributes::SetPhoneOwnerDataL
// ---------------------------------------------------------------------------
//	
EXPORT_C void CEntryAttributes::SetPhoneOwnerDataL( const TDesC& aPhoneOwner )
	{
    if( aPhoneOwner.Length() ) 
	    {
	    iPhoneOwner = aPhoneOwner.AllocL();
    	iSetAttributes |= EPhoneOwner;	
	    }
	}

// ---------------------------------------------------------------------------
// CEntryAttributes::SetOrganizerDataL
// ---------------------------------------------------------------------------
//	
EXPORT_C void CEntryAttributes::SetOrganizerDataL( CAttendeeInfo* aOrganizer )
	{
	if( aOrganizer ) 
	    {
	    iOrganizer = CCalUser::NewL( aOrganizer->Address() );

		if( aOrganizer->CommonName().Length() )
			iOrganizer->SetCommonNameL( aOrganizer->CommonName() ); 
		
    	iSetAttributes |= EOrganizer;
        }
	}
	
// ---------------------------------------------------------------------------
// CEntryAttributes::AddAttendeeL
// ---------------------------------------------------------------------------
//	
EXPORT_C void CEntryAttributes::AddAttendeeL( CAttendeeInfo* aAttendee )
	{
	if( aAttendee )	
		{
		CCalAttendee* attendee = CCalAttendee::NewL( aAttendee->Address() );
		if( aAttendee->CommonName().Length() )
			attendee->SetCommonNameL( aAttendee->CommonName() );
		TPtrC role = aAttendee->Role();
		if( role.Length() )
			{
			CCalAttendee::TCalRole attRole = CCalAttendee::EReqParticipant;
			
			if ( role.CompareF(KAttRoleReqParticipant) == 0 )
				attRole = CCalAttendee::EReqParticipant; // required participant
			
			else if ( role.CompareF(KAttRoleOptParticipant) == 0 )
				attRole = CCalAttendee::EOptParticipant; // optional participant
			
			else if ( role.CompareF(KAttRoleNonParticipant) == 0 )
				attRole = CCalAttendee::ENonParticipant; // non - participant
			
			else if ( role.CompareF(KAttRoleChair) == 0 )
				attRole = CCalAttendee::EChair; // chair
			
			else 
				User::Leave(KErrArgument);
		    
			attendee->SetRoleL( attRole );
			}
			
		TPtrC status = aAttendee->Status();
		if( status.Length() )
			{
			CCalAttendee::TCalStatus attStatus = CCalAttendee::ENeedsAction;
			
			if ( status.CompareF(KAttStatusTentative) == 0 )
				attStatus = CCalAttendee::ETentative; // attendee's status is tentative
			
			else if ( status.CompareF(KAttStatusConfirmed) == 0 )
				attStatus = CCalAttendee::EConfirmed; // attendee has confirmed participation
			
			else if ( status.CompareF(KAttStatusAccepted) == 0 )
				attStatus = CCalAttendee::EAccepted; // attendee has accepted
			
			else if ( status.CompareF(KAttStatusNeedsAction) == 0 )
				attStatus = CCalAttendee::ENeedsAction; // status needs action
			
			else if ( status.CompareF(KAttStatusDeclined) == 0 )
				attStatus = CCalAttendee::EDeclined;// attendee has declined
			
			else if ( status.CompareF(KAttStatusInProcess) == 0 )
				attStatus = CCalAttendee::EInProcess;// status in process
			
			else if ( status.CompareF(KAttStatusCompleted) == 0 )
				attStatus = CCalAttendee::ECompleted; // status is completed
			
			else if ( status.CompareF(KAttStatusDelegated) == 0 )
				attStatus = CCalAttendee::EDelegated;// attendee has delegated request
			
			else
				User::Leave(KErrArgument);
			
			attendee->SetStatusL( attStatus );
			}
		attendee->SetResponseRequested( aAttendee->ResponseRequested() );	
		iAttendees.AppendL( attendee );
		iSetAttributes |= EAttendees;
		}
	}

// ---------------------------------------------------------------------------
// CEntryAttributes::AddRepeatDateL
// ---------------------------------------------------------------------------
//	
EXPORT_C void CEntryAttributes::AddRepeatDateL( const TTime& aRepeatDate )
	{
	if ( aRepeatDate != Time::NullTTime())
		{
		TCalTime caltime;
		caltime.SetTimeUtcL( aRepeatDate );
		iRepeatDates.Append( caltime );
		iSetAttributes |= ERepeatDates;
		}
    }

// ---------------------------------------------------------------------------
// CEntryAttributes::AddExceptionDateL
// ---------------------------------------------------------------------------
//		
EXPORT_C void CEntryAttributes::AddExceptionDateL( const TTime& aExDate )
	{
	if ( aExDate != Time::NullTTime())
		{
		TCalTime caltime;
		caltime.SetTimeUtcL( aExDate );
		iExDates.Append( caltime );
		iSetAttributes |= EExDates;
		}
	}

// ---------------------------------------------------------------------------
// CEntryAttributes::SetReplicationL
// ---------------------------------------------------------------------------
//	
EXPORT_C void CEntryAttributes::SetReplicationL( const TDesC& aRepStatus )
	{
	if ( aRepStatus.CompareF( KReplOpen ) == 0 )
		iRepStatus = CCalEntry::EOpen; // open
	else if ( aRepStatus.CompareF( KReplPrivate ) == 0 )
		iRepStatus = CCalEntry::EPrivate; //private
	else if ( aRepStatus.CompareF( KReplRest ) == 0 )
		iRepStatus = CCalEntry::ERestricted;//restricted
	else
		User::Leave(KErrArgument);
	
	iSetAttributes |= EReplication;	
	}    
				
// ---------------------------------------------------------------------------
// CEntryAttributes::SetSummaryL
// ---------------------------------------------------------------------------
//
EXPORT_C void CEntryAttributes::SetSummaryL( const TDesC& aSummary )
	{
	if( aSummary.Length() )
		{
		iSummary = aSummary.AllocL();
		iSetAttributes |= ESummary;
		}
	}

// ---------------------------------------------------------------------------
// CEntryAttributes::SetDescriptionL
// ---------------------------------------------------------------------------
//	
EXPORT_C void CEntryAttributes::SetDescriptionL( const TDesC& aDescription )
	{
	if( aDescription.Length() )
		{
		iDescription = aDescription.AllocL();
		iSetAttributes |= EDescription;
		}
	}
	
// ---------------------------------------------------------------------------
// CEntryAttributes::SetLocationL
// ---------------------------------------------------------------------------
//
EXPORT_C void CEntryAttributes::SetLocationL( const TDesC& aLocation )
	{
	if( aLocation.Length() )
		{
		iLocation = aLocation.AllocL();
		iSetAttributes |= ELocation;
		}
	}

// ---------------------------------------------------------------------------
// CEntryAttributes::SetMethodL
// ---------------------------------------------------------------------------
//	
EXPORT_C void CEntryAttributes::SetMethodL( const TDesC& aMethod )
	{
	//Sets the entry's method property for group scheduling
	if ( aMethod.CompareF(KMethodNone) == 0 )
		iMethod = CCalEntry::EMethodNone; 
	
	else if ( aMethod.CompareF(KMethodPublish) == 0 )
		iMethod = CCalEntry::EMethodPublish;
	
	else if ( aMethod.CompareF(KMethodRequest) == 0 )
		iMethod = CCalEntry::EMethodRequest;
	
	else if ( aMethod.CompareF(KMethodReply) == 0 )
		iMethod = CCalEntry::EMethodReply;
	
	else if ( aMethod.CompareF(KMethodAdd) == 0 )
		iMethod = CCalEntry::EMethodAdd;
	
	else if ( aMethod.CompareF(KMethodCancel) == 0 )
		iMethod = CCalEntry::EMethodCancel;
	
	else if ( aMethod.CompareF(KMethodRefresh) == 0 )
		iMethod = CCalEntry::EMethodRefresh;
	
	else if ( aMethod.CompareF(KMethodCounter) == 0 )
		iMethod = CCalEntry::EMethodCounter;
	
	else if ( aMethod.CompareF(KMethodDecCounter) == 0 )
		iMethod = CCalEntry::EMethodDeclineCounter;
	
	else
		User::Leave(KErrArgument);
	
	iSetAttributes |= EMethod;
	}

// ---------------------------------------------------------------------------
// CEntryAttributes::SetPriority
// ---------------------------------------------------------------------------
//	
EXPORT_C int CEntryAttributes::SetPriority( TInt aPriority )
	{
	if( aPriority < 0 || aPriority > 255 )
		return KErrArgument;	
	iPriority = aPriority;	
	iSetAttributes |= EPriority;
	return KErrNone;
	}
	
// ---------------------------------------------------------------------------
// CEntryAttributes::SetLocalUid
// ---------------------------------------------------------------------------
//	
EXPORT_C void CEntryAttributes::SetLocalUid( const TCalLocalUid aLUid)
	{
	iLocal = aLUid;	
	iSetAttributes |= ELocalUid;
	}
// ---------------------------------------------------------------------------
// CEntryAttributes::SetUid
// ---------------------------------------------------------------------------
//  
EXPORT_C void CEntryAttributes::SetUidL( const TDesC8& aUid )
    {
    if( aUid.Length() )
        {
        iUid = aUid.AllocL();
        iSetAttributes |= EGlobalUid;
        }
    }
// ---------------------------------------------------------------------------
// CEntryAttributes::SetRepeatRule
// ---------------------------------------------------------------------------
//		
EXPORT_C void CEntryAttributes::SetRepeatRule( CRepeatInfo* aRptInfo)
	{
	if ( aRptInfo )
		iRepeatRule = aRptInfo->GetRepeatRule();
	}

// ---------------------------------------------------------------------------
// CEntryAttributes::StartTime
// ---------------------------------------------------------------------------
//		
EXPORT_C TCalTime& CEntryAttributes::StartTime()
	{
	return iStartTime;	
	}

// ---------------------------------------------------------------------------
// CEntryAttributes::EndTime
// ---------------------------------------------------------------------------
//		
EXPORT_C TCalTime& CEntryAttributes::EndTime()
	{
	return iEndTime;	
	}

// ---------------------------------------------------------------------------
// CEntryAttributes::InstanceStartTime
// ---------------------------------------------------------------------------
//	
EXPORT_C TCalTime& CEntryAttributes::InstanceStartTime()
	{
	return iInstanceStartTime;
	}

// ---------------------------------------------------------------------------
// CEntryAttributes::ReplicationStatus
// ---------------------------------------------------------------------------
//		
EXPORT_C CCalEntry::TReplicationStatus CEntryAttributes::ReplicationStatus()
	{
	return iRepStatus;	
	}

// ---------------------------------------------------------------------------
// CEntryAttributes::Summary
// ---------------------------------------------------------------------------
//				
EXPORT_C TPtrC CEntryAttributes::Summary()
	{
	return iSummary ? TPtrC( *iSummary ) : TPtrC();
	}

// ---------------------------------------------------------------------------
// CEntryAttributes::Description
// ---------------------------------------------------------------------------
//		
EXPORT_C TPtrC CEntryAttributes::Description()
	{
	return iDescription ? TPtrC( *iDescription ) : TPtrC();
	}

// ---------------------------------------------------------------------------
// CEntryAttributes::Location
// ---------------------------------------------------------------------------
//	
EXPORT_C TPtrC CEntryAttributes::Location()
	{
	return iLocation ? TPtrC( *iLocation ) : TPtrC();
	}
	
// ---------------------------------------------------------------------------
// CEntryAttributes::EntryType
// ---------------------------------------------------------------------------
//
EXPORT_C CCalEntry::TType CEntryAttributes::EntryType()
	{
	return iType;
	}

// ---------------------------------------------------------------------------
// CEntryAttributes::SequenceNumber
// ---------------------------------------------------------------------------
//
EXPORT_C TInt CEntryAttributes::SequenceNumber()
	{
	return iSequenceNum;
	}

// ---------------------------------------------------------------------------
// CEntryAttributes::AlarmTime
// ---------------------------------------------------------------------------
//	
EXPORT_C TTime CEntryAttributes::AlarmTime()
	{
	return iAlarmTime;
	}

// ---------------------------------------------------------------------------
// CEntryAttributes::EntryStatus
// ---------------------------------------------------------------------------
//
EXPORT_C CCalEntry::TStatus CEntryAttributes::EntryStatus()
	{
	return iEntryStatus;
	}		

// ---------------------------------------------------------------------------
// CEntryAttributes::PhoneOwner
// ---------------------------------------------------------------------------
//	
EXPORT_C TPtrC CEntryAttributes::PhoneOwner()
	{
	return iPhoneOwner ? *iPhoneOwner : TPtrC();
	}

// ---------------------------------------------------------------------------
// CEntryAttributes::Organizer
// ---------------------------------------------------------------------------
//	
EXPORT_C CCalUser* CEntryAttributes::Organizer()
	{
	return iOrganizer;
	}

// ---------------------------------------------------------------------------
// CEntryAttributes::AttendeeList
// ---------------------------------------------------------------------------
//
EXPORT_C RPointerArray<CCalAttendee>& CEntryAttributes::AttendeeList()
	{
	return iAttendees;
	}

// ---------------------------------------------------------------------------
// CEntryAttributes::RepeatDates
// ---------------------------------------------------------------------------
//	
EXPORT_C RArray<TCalTime>& CEntryAttributes::RepeatDates()
	{
	return iRepeatDates;
	}

// ---------------------------------------------------------------------------
// CEntryAttributes::ExceptionDates
// ---------------------------------------------------------------------------
//	
EXPORT_C RArray<TCalTime>& CEntryAttributes::ExceptionDates()
	{
	return iExDates;	
	}

// ---------------------------------------------------------------------------
// CEntryAttributes::RepeatRuleL
// ---------------------------------------------------------------------------
//	
EXPORT_C TCalRRule& CEntryAttributes::RepeatRuleL()
	{
	if ( iType == CCalEntry::EAnniv )
	// explicitly set repeat rule for anniversary type entries
		{
		TTime stTime = iStartTime.TimeLocalL();
		TTime zero(TInt64(0));
        stTime = zero + stTime.DaysFrom(zero);
        iStartTime.SetTimeLocalFloatingL( stTime );
        TCalRRule rrule( TCalRRule::EYearly );
        rrule.SetDtStart( iStartTime );
        rrule.SetInterval( 1 ); // once a year
		iRepeatRule = rrule	;
		}
	return iRepeatRule;	
	}

// ---------------------------------------------------------------------------
// CEntryAttributes::Method
// ---------------------------------------------------------------------------
//	
EXPORT_C CCalEntry::TMethod CEntryAttributes::Method()
	{
	return iMethod;	
	}

// ---------------------------------------------------------------------------
// CEntryAttributes::Priority
// ---------------------------------------------------------------------------
//	
EXPORT_C TInt CEntryAttributes::Priority()
	{
	return iPriority;	
	}

// ---------------------------------------------------------------------------
// CEntryAttributes::LocalUid
// ---------------------------------------------------------------------------
//	
EXPORT_C TCalLocalUid CEntryAttributes::LocalUid()
	{
	return iLocal;	
	}
// ---------------------------------------------------------------------------
// CEntryAttributes::GlobalUid
// ---------------------------------------------------------------------------
//  
EXPORT_C TPtrC8 CEntryAttributes::GlobalUid()
    {
    return iUid ? TPtrC8( *iUid ) : TPtrC8();
    }

// ---------------------------------------------------------------------------
// CEntryAttributes::ModifiedAttributes
// ---------------------------------------------------------------------------
//	
EXPORT_C TInt32 CEntryAttributes::ModifiedAttributes()
	{ 
	return iSetAttributes;
	}

// ---------------------------------------------------------------------------
// Constructor
// ---------------------------------------------------------------------------
//	
CEntryAttributes::CEntryAttributes()
	{
	iMethod = CCalEntry::EMethodNone;
	iSequenceNum = 0;
	iRepStatus = CCalEntry::EOpen;
	iPriority = 0;
	iPhoneOwner = NULL;
	iOrganizer = NULL;
	iLocation = NULL;
	iAlarmTime = NULL;
	iEntryStatus = CCalEntry::ENullStatus;
	}
	
