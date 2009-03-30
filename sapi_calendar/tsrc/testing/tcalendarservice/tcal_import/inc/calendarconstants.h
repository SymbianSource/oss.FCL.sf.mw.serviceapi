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
* Description:   Constants definitions used across calendar SAPI
*
*/



#ifndef _CALENDARCONSTANTS_H_
#define _CALENDARCONSTANTS_H_

const TInt KArrayGran 		= 4;
const TInt KArrayZeroIndex 	= 0;
const TInt KMaxUidLength 	= 100;
const TInt KMaxErrorMessageLength = 100;
const TInt KMaxFileNameLength = 239;

const TInt KRRTypeDaily 	= 1;
const TInt KRRTypeWeekly 	= 2;
const TInt KRRTypeMonthly 	= 3;
const TInt KRRTypeYearly 	= 4;

const TUint KUidSeparator 	= ':';

// Constants for Error Message
_LIT(KErrorMsgSeparator, 	" : ");
_LIT(KDomainName, 			"Calendar");
_LIT(KCmdInvalid, 			"Command Not Supported");
_LIT(KCmdFailed, 			"Error executing Command");
_LIT(KMissing,				" is missing");
_LIT(KInvalid,				" is invalid");
_LIT(KAsyncNotSupported,	"Async not supported");
_LIT(KInvalidAsyncParam,	"Invalid async parameters");
_LIT(KInvalidCancelParam,	"Cancel bit not set in aCmdOptions");
_LIT8(KRepeatWeekNum,		"RepeatRule:DaysOfMonth:WeekNunber");
_LIT(KServiceInUse,	    "Operation in progress, cannot be cancelled");


// Constants specifing the format of the calender
_LIT8(KCalFmtVCal,			"VCal");
_LIT8(KCalFmtICal,			"ICal");

_LIT8(KErrorCode,			"ErrorCode");
_LIT8(KErrorMessage,		"ErrorMessage");
_LIT8(KReturnValue,			"ReturnValue");
_LIT8(KTransactionID,		"TransactionID");


// Calendar Entry Replication Status
_LIT(KReplOpen, 			"Open");
_LIT(KReplPrivate, 			"Private");
_LIT(KReplRest, 			"Restricted");

// Calendar Entry Status
_LIT(KStatusTentative, 		"Tentative");
_LIT(KStatusConfirmed, 		"Confirmed");
_LIT(KStatusCancelled, 		"Cancelled");
_LIT(KStatusTodoNeedsAction,"TodoNeedsAction");
_LIT(KStatusTodoCompleted, 	"TodoCompleted");
_LIT(KStatusTodoInProcess, 	"TodoInProcess");
_LIT(KNullStatus, 			"NullStatus");

// Calendar Entry Methods
_LIT(KMethodNone, 			"None");
_LIT(KMethodPublish, 		"Publish");
_LIT(KMethodRequest, 		"Request");
_LIT(KMethodReply, 			"Reply");
_LIT(KMethodAdd, 			"Add");
_LIT(KMethodCancel, 		"Cancel");
_LIT(KMethodRefresh, 		"Refresh");
_LIT(KMethodCounter, 		"Counter");
_LIT(KMethodDecCounter, 	"DeclineCounter");

// Calendar Entry types
_LIT(KEntryAppt, 			"Meeting");
_LIT(KEntryTodo, 			"ToDo");
_LIT(KEntryEvent, 			"DayEvent");
_LIT(KEntryReminder, 		"Reminder");
_LIT(KEntryAnniv, 			"Anniversary");
_LIT(KIncludeAll, 			"IncludeAll");

// Calendar Command Names
_LIT8(KCmdAdd,				"Add");
_LIT8(KCmdDelete,			"Delete");
_LIT8(KCmdGetList,			"GetList");
_LIT8(KCmdImport,			"Import");
_LIT8(KCmdExport,			"Export");
_LIT8(KCmdReqNot,			"RequestNotification");
_LIT8(KCmdCancel,			"Cancel");

// GetList Parameters
_LIT8(KFilter, 				"Filter");
_LIT8(KDefault, 			"DefaultCalendar");
_LIT8(KId, 			        "id");
_LIT8(KLocalId, 			"LocalId");
_LIT8(KStartRange, 			"StartRange");
_LIT8(KEndRange, 			"EndRange");
_LIT8(KSearchText, 			"SearchText");
_LIT8(KEntryType, 			"Type");

// Delete parameters
_LIT8(KCalendarList, 		"CalendarList");
_LIT8(KIdList, 		        "IdList");
_LIT8(KLocalIdList, 		"LocalIdList");
_LIT8(KDeleteAll, 			"DeleteAll");
_LIT8(KData, 				"Data");


// Request notification parameters
_LIT8(KIncludeUndatedTodos, "IncludeUndatedTodos");
_LIT8(KChangeType, 			"ChangeType");

// Change type attributes
_LIT(KChangeAdd, 		  	"Add");
_LIT(KChangeDelete, 		"Delete");
_LIT(KChangeModify, 		"Modify");
_LIT(KChangeUndefined, 		"Unknown");


// Content type attributes
_LIT(KContentCalendar, 		"Calendar");
_LIT(KContentCalendarEntry, "CalendarEntry");

// Calendar Entry Attributes
_LIT8(KContentType, 		"Type");
_LIT8(KItem,  		      	"Item");
_LIT8(KCalendar,  		    "Calendar");
_LIT8(KCalendarName,        "CalendarName");
_LIT8(KCalendarEntry,       "CalendarEntry");
_LIT8(KType,                "Type");
_LIT8(KSummary,             "Summary");
_LIT8(KDescription,         "Description");
_LIT8(KLocation,            "Location");
_LIT8(KReplication,         "Replication");
_LIT8(KEntryStatus,         "Status");
_LIT8(KMethod,              "Method");
_LIT8(KSeqNum,              "SeqNum");
_LIT8(KPriority,            "Priority");
_LIT8(KStartTime,           "StartTime");
_LIT8(KEndTime,             "EndTime");
_LIT8(KAlarmTime,           "AlarmTime");
_LIT8(KPhoneOwner,          "PhoneOwner");
_LIT8(KOrganizer,           "Organizer");
_LIT8(KAttendeeList,        "Attendees");
_LIT8(KCommonName,          "CommonName");
_LIT8(KAddress,             "Address");
_LIT8(KRole,                "Role");
_LIT8(KStatus,              "Status");
_LIT8(KRsvp,                "Rsvp");
_LIT8(KRepeatDates,         "RepeatDates");
_LIT8(KExceptionDates,      "ExDates");
_LIT8(KRepeatRule,          "RepeatRule");
_LIT8(KRepeatType,          "Type");
_LIT8(KRStartDate,          "StartDate");
_LIT8(KUntilDate,           "UntilDate");
_LIT8(KInterval,            "Interval");
_LIT8(KDaysInWeek,          "DaysInWeek");
_LIT8(KMonthDays,           "MonthDays");
_LIT8(KDaysOfMonth,         "DaysOfMonth");
_LIT8(KMonth,               "Month");
_LIT8(KDay,           		"Day");
_LIT8(KWeekNum,             "WeekNum");

// Calendar Instance Attributes
_LIT8(KInstStartTime,       "InstanceStartTime");
_LIT8(KInstEndTime,         "InstanceEndTime");

// Import / Export params
_LIT8(KCalendarFormat,      "Format");
_LIT8(KFormatICal,          "ICal");
_LIT8(KFormatVCal,          "VCal");
_LIT8(KInputBuffer,         "Buffer");
_LIT8(KImExFileName,        "FileName");
_LIT8(KCalendarGuidList,    "IdList");
_LIT8(KCalendarLuidList,    "LocalIdList");


// Calendar User Status
_LIT(KAttStatusNeedsAction,     "NeedsAction");
_LIT(KAttStatusAccepted, 		"Accepted");
_LIT(KAttStatusTentative, 		"Tentative");
_LIT(KAttStatusConfirmed, 		"Confirmed");
_LIT(KAttStatusDeclined, 	    "Declined");
_LIT(KAttStatusCompleted, 		"Completed");
_LIT(KAttStatusDelegated, 		"Delegated");
_LIT(KAttStatusInProcess, 	    "InProcess");

// Calendar User Role
_LIT(KAttRoleReqParticipant,    "Required");
_LIT(KAttRoleOptParticipant, 	"Optional");
_LIT(KAttRoleNonParticipant,	"NonParticipant");
_LIT(KAttRoleChair     , 		"Chair");


// Calendar Entry Repeat Types
_LIT(KDailyRepeat,              "Daily");
_LIT(KWeeklyRepeat,             "Weekly");
_LIT(KMonthlyRepeat,            "Monthly");
_LIT(KYearlyRepeat,             "Yearly");

#endif _CALENDARCONSTANTS_H_