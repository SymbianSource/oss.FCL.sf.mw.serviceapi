/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef ALARMSERVERTEST_H
#define ALARMSERVERTEST_H

#include "startconsolealarmserver.h"


#include <calalarm.h>
#include <caluser.h>

#include "calendarconstants.h"
#include "calendarheader.h"
#include "entryattributes.h"
#include "calendarservice.h"


TInt AddAppointment(CCalendarService* aService, const TDesC& name, TUIDSet*& uids)
	{
	CEntryAttributes* entryObj = CEntryAttributes::NewL( KEntryAppt );
	
	entryObj->SetDescriptionL(_L("SAPI weekly meeting"));
	entryObj->SetLocationL(_L("Hara"));
	entryObj->SetEntryStatusL(KStatusConfirmed);
	entryObj->SetMethodL(KMethodNone);
	entryObj->SetPriority(5);
    entryObj->SetSummaryL(_L("Happens from 9 to 9:30"));
    
	entryObj->SetStartTimeL( TTime(TDateTime(2007, EAugust, 8, 9, 0, 0, 0)) );
	
	entryObj->SetEndTimeL(TTime(TDateTime(2007, EAugust, 8, 9, 30, 0, 0)));
	
	TRAPD( errno, aService->AddL(name,entryObj,uids) );
	delete entryObj;
	return errno;
	}
/*
EAppt An appointment, which has a start time and end time. 
 
ETodo A to-do, which can have a start time and end time (the end time is the due date), or can be undated. 
 
EEvent An event, which has a start time and end time. 
 
EReminder A reminder, which has a start time only. 
 
EAnniv An anniversary, which has a start time and end time. 
*/
	



	
TInt AddToDo(CCalendarService* aService, const TDesC& name, TUIDSet*& uids)
	{
	CEntryAttributes* entryObj = CEntryAttributes::NewL( KEntryTodo );
	
	entryObj->SetDescriptionL(_L("New todo entry created"));
	entryObj->SetSummaryL(_L("TODO Entry"));
	TTime endTime(TDateTime(2007, EAugust, 21, 0, 0, 0, 0));
	entryObj->SetEndTimeL(endTime);
	entryObj->SetReplicationL(KReplOpen);
	entryObj->SetPriority(0);	
	
	TRAPD( errno, aService->AddL(name,entryObj,uids) );
	delete entryObj;
	return errno;
	}

TInt RemoveCalendarFile(CCalendarService* aService, const TDesC& name)	
	{
	TRAPD( err , aService->DeleteL( name ) );
	return err ;
	}	
	
TInt AddCalendarFile(CCalendarService* aService, const TDesC& name)	
	{
	TRAPD( err , aService->AddL( name ) );
	return err ;
	}		

TInt DeleteAllCalendarEntry(CCalendarService* aService, const TDesC& name)	
	{
	CCalendarFilter* filter = CCalendarFilter::NewL();
	filter->SetDeleteAll();
	TRAPD( err, aService->DeleteL( name, filter ) );
	delete filter;
	return err ;
	}
		
TInt AddAppointmentWithAttendees(CCalendarService* aService, const TDesC& name, TUIDSet*& uids)
	{
	CEntryAttributes* entryObj = CEntryAttributes::NewL( KEntryAppt );
	
	entryObj->SetDescriptionL(_L("SAPI weekly meeting"));
	entryObj->SetLocationL(_L("Hara"));
	entryObj->SetEntryStatusL(KStatusConfirmed);

	entryObj->SetMethodL(KMethodNone);
	CAttendeeInfo* organizer=CAttendeeInfo::NewL(_L("mcrasta@gmail.com"));
	organizer->SetCommonNameL(_L("SAPI"));
	entryObj->SetOrganizerDataL(organizer);
	delete organizer;
	
	entryObj->SetPhoneOwnerDataL(_L("h2s@gmail.com"));
	
	entryObj->SetPriority(5);
    entryObj->SetSummaryL(_L("Happens from 9 to 9:30"));
    
    TTime stTime(TDateTime(2007, EAugust, 8, 9, 0, 0, 0));
	entryObj->SetStartTimeL(stTime);
	
	TTime endTime(TDateTime(2007, EAugust, 8, 9, 30, 0, 0));
	entryObj->SetEndTimeL(endTime);
	
	CCalAlarm* alarm = CCalAlarm::NewL();
	TTime alarmTime(TDateTime(2007,EAugust, 8, 7, 30, 0, 0));
	//entryObj->SetAlarm(alarmTime);
	delete alarm;
    CAttendeeInfo* attendee = CAttendeeInfo::NewL(_L("h2s@gmail.com"));
	attendee->SetRoleL(KAttRoleReqParticipant);
	attendee->SetStatusL(KAttStatusTentative);
    attendee->SetRsvp(EFalse);
    
	/*attendee = CCalAttendee::NewL(_L(""));
	attendee->SetCommonNameL(_L("SAPI"));
	attendee->SetRoleL(CCalAttendee::EReqParticipant);
	attendee->SetStatusL(CCalAttendee::ETentative);
    attendee->SetResponseRequested(EFalse);
    
	attendees.Append(attendee);*/
	
	entryObj->AddAttendeeL(attendee);
	delete attendee;
		
	TRAPD( errno, aService->AddL(name,entryObj,uids) );
	
	delete entryObj;
	
	return errno;
	}
TInt AddAnny(CCalendarService* aService, const TDesC& name, TUIDSet*& uids)
	{

	CEntryAttributes* entryObj = CEntryAttributes::NewL( KEntryAnniv );

	TTime stTime(TDateTime(2007, EDecember, 30, 0, 0, 0, 0));
	entryObj->SetStartTimeL(stTime);
	entryObj->SetReplicationL(KReplPrivate);	

	TCalTime startTime;
	startTime.SetTimeLocalFloatingL( stTime );
	/*TCalRRule rrule(TCalRRule::EYearly);
	rrule.SetDtStart(startTime);
	rrule.SetInterval(1);

	TCalTime uTime;
	uTime.SetTimeLocalFloatingL(TCalTime::MaxTime());
	rrule.SetUntil(uTime);

	entryObj->SetRepeatRule(rrule);*/

	TRAPD( errno, aService->AddL(name,entryObj,uids) );

	delete entryObj;
	
	return errno;
	}
	
TInt AddEvent(CCalendarService* aService, const TDesC& name, TUIDSet*& uids)
	{
	CEntryAttributes* entryObj = CEntryAttributes::NewL( KEntryEvent );
	
	entryObj->SetDescriptionL(_L("New Event entry created"));
	entryObj->SetSummaryL(_L("Event Entry"));
	TTime stTime(TDateTime(2007, EJuly, 25, 0, 0, 0, 0));
	entryObj->SetStartTimeL(stTime);
	entryObj->SetReplicationL(KReplPrivate);
	
		
	TRAPD( errno, aService->AddL(name,entryObj,uids) );

	delete entryObj;
	
	return errno;
	}
	
TInt AddReminder(CCalendarService* aService, const TDesC& name, TUIDSet*& uids)
	{
	CEntryAttributes* entryObj = CEntryAttributes::NewL( KEntryReminder );
	
	entryObj->SetDescriptionL(_L("New Reminder entry created"));
	entryObj->SetSummaryL(_L("Reminder Entry"));
	TTime stTime(TDateTime(2007, EJuly, 22, 10, 30, 0, 0));
	entryObj->SetStartTimeL(stTime);
	entryObj->SetReplicationL(KReplOpen);
	
	TRAPD( errno, aService->AddL(name,entryObj,uids) );
	delete entryObj;
	
	return errno;
	}
	
TInt AddRepeatingAppointmentEntryL(CCalendarService* aService, const TDesC& name, TUIDSet*& uids)
	{
	
	CEntryAttributes* entryObj = CEntryAttributes::NewL( KEntryAppt );
	
    entryObj->SetDescriptionL(_L("SAPI weekly meeting"));
	entryObj->SetLocationL(_L("Hara"));
	entryObj->SetEntryStatusL(KStatusConfirmed);
	
	entryObj->SetMethodL(KMethodNone);
	CAttendeeInfo* organizer = CAttendeeInfo::NewL(_L("mcrasta@gmail.com"));
	organizer->SetCommonNameL(_L("SAPI"));
	entryObj->SetOrganizerDataL(organizer);
	delete organizer;
	
	entryObj->SetPhoneOwnerDataL(_L("h2s@gmail.com"));
	
	entryObj->SetPriority(5);
    entryObj->SetSummaryL(_L("Repeating entry"));
    
    TTime stTime(TDateTime(2007, ESeptember, 15, 9, 0, 0, 0));
	entryObj->SetStartTimeL(stTime);
	
	TTime endTime(TDateTime(2007, ESeptember, 15, 9, 30, 0, 0));
	entryObj->SetEndTimeL(endTime);
	
	CCalAlarm* alarm = CCalAlarm::NewL();
	TTime alarmTime(TDateTime(2007,ESeptember, 15, 7, 30, 0, 0));
	//entryObj->SetAlarm(alarmTime);
	delete alarm;
	
    CAttendeeInfo* attendee = CAttendeeInfo::NewL(_L("h2s@gmail.com"));
	attendee->SetRoleL(KAttRoleReqParticipant);
	attendee->SetStatusL(KAttStatusTentative);
    attendee->SetRsvp(EFalse);
    entryObj->AddAttendeeL(attendee);
    delete attendee;
	
	attendee = CAttendeeInfo::NewL(_L("mdcosta@gmail.com"));
	attendee->SetCommonNameL(_L("SAPI"));
	attendee->SetRoleL(KAttRoleReqParticipant);
	attendee->SetStatusL(KAttStatusTentative);
    attendee->SetRsvp(EFalse);
    entryObj->AddAttendeeL(attendee);
    delete attendee;
    
    CRepeatInfo* rrule = CRepeatInfo::NewL(TCalRRule::EDaily);
	//TCalRRule rrule(TCalRRule::EDaily);
	TCalTime startTime;
	startTime.SetTimeUtcL(stTime);
	rrule->SetStartTimeL(stTime);
	TCalTime uTime;
	uTime.SetTimeUtcL(TTime(TDateTime(2007, ESeptember, 29, 0, 0, 0, 0)));
	rrule->SetUntilTimeL(TTime(TDateTime(2007, ESeptember, 29, 0, 0, 0, 0)));
	rrule->SetWeekStart(EWednesday);
	entryObj->SetRepeatRule(rrule);	
	delete rrule;
	
	TTime exDate(TDateTime(2007, ESeptember, 20, 0, 0, 0, 0)); 
    TCalTime exTime;
    exTime.SetTimeUtcL(exDate);
    entryObj->AddExceptionDateL(exDate);
        
    TTime rDate(TDateTime(2007, EOctober, 0, 9, 0, 0, 0)); 
    TCalTime rTime;
    rTime.SetTimeUtcL(rDate);
    entryObj->AddRepeatDateL(rDate);
        
	TRAPD( errno, aService->AddL(name,entryObj,uids) );
	delete entryObj;
	return errno;

    }		
		


#endif	
