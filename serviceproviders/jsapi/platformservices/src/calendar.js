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

function __device_calendar_descriptor(provider){
	//alert(("provider");
  this.interfaceName = provider.interfaceName;
  //alert(("provider interfaceName" + this.interfaceName);
  this.version = provider.version;
  //alert(("provider version" + this.version);
}

function __device_calendar_startEditor(callback, entry, ErrorCallback){
  this.provider.startEditor(callback, entry, ErrorCallback);
}

function __device_calendar_getList(callback, match, ErrorCallback){
  //alert(("__device_calendar_getList(callback, match)");
  return this.provider.getList(callback, match, ErrorCallback);
  //alert(("return from device_calendar_getList");

}

function __device_calendar_add(entry){
  return this.provider.addEntry(entry);
}

function __device_calendar_update(entry){
  return this.provider.updateEntry(entry);
}

function __device_calendar_delete(data){
  this.provider.deleteEntry(data);
}

function __device_calendar_cancel(transactionId){
  this.provider.cancel(transactionId);
}

// Private location prototype: called from service factory
function __device_calendar(provider){
  //Private properties
  this.provider = provider;
  //Read-only properties
  this.interfaceName = provider.descriptor.interfaceName;
  this.version = provider.descriptor.version;
  //Core methods
  this.startEditor = __device_calendar_startEditor;
  //Extended methods
  this.getList = __device_calendar_getList;
  this.addEntry = __device_calendar_add;
  this.updateEntry = __device_calendar_update;
  this.deleteEntry = __device_calendar_delete;
  this.cancel = __device_calendar_cancel;
}

// calendar service interface

// Namepace: com.nokia.device.service
//alert(("before com.nokia.device.service");
var __device_calendar_service_entry = {"name": null,
					  "version": null,
					  "proto": __device_calendar,
					  "descriptor": __device_calendar_descriptor,
					  "providers": [{"descriptor": __sp_calendar_descriptor, "instance": __sp_calendar_instance}]
					 };
		   
var dataGetList = 0;
var isUpdate = 0;
// S60 sp-based calendar provider

function __sp_calendar_descriptor(){
  //Read-only properties
  this.interfaceName = "calendar";
  if(window.__Service_Interface_Ver)
	this.version =__Service_Interface_Ver;
  else
	this.version =1.0;
  //Class-static properties 
}

function __sp_calendar_entry_time(start, end, alarm){
   //////alert( start + " __sp_calendar_entry_time ");
  if (start) {
    //////alert("if start");
	//////alert(start +"start");
	var st = new Date(start);
  	this.begin = st;
//	////alert("begin" + typeof this.begin);
  }
  if (end) {
  //	////alert("in end");
  	var en = new Date(end);
	this.end = en;
  }
  if (alarm) {
    var al = new Date(alarm);
  	this.alarm = al;
  }
}

function __sp_calendar_isInputValid(match){
//	////alert("Inside input validation");
	
		if (match) {
			if (match.id) {
				if (typeof(match.id) != "string") {
					return false;
				}
			}
			if (match.type) {
				if ((typeof(match.type) != "string") || !__sp_calendar_entry_types.match(match.type)) {
					return false;
				}
			}
			if (match.text) {
				if (typeof(match.text) != "string") {
					return false;
				}
			}
			if (match.range) {
				if (typeof(match.range) != "object") {
					return false;
				}
				if (match.range.begin) {
					if (typeof(match.range.begin) != "object") {
						return false;
					}
				}
				if (match.range.end) {
					if (typeof(match.range.end) != "object") {
						return false;
					}
				}
			}
			
			/******************************************************
			 * addEntry/updateEntry input ,  id and type checked above
			 **********************************************************/
		
				if (match.summary) {
					
					if (typeof(match.summary) != "string") {
						return false;
					}
				}
				if (match.description) {
					if (typeof(match.description) != "string") {
						return false;
					}
				}
				if (match.status) {
					if (typeof(match.status) != "string") {
						return false;
					}
					
				}
				if (match.location) {
					if (typeof(match.location) != "string") {
						return false;
					}
				}
				if (match.priority) {
					if (typeof(match.priority) != "number") {
						return false;
					}
				}
				if (match.instanceStartTime) {
					if (typeof(match.instanceStartTime) != "object") {
						return false;
					}
				}
				if (match.exceptionDates) {
					if (typeof(match.exceptionDates) != "object") {
						return false;
					}
				}
				if (match.time) {
					if (typeof match.time != 'object') {
						return false;
					}
					if (match.time.begin) {
						if (typeof(match.time.begin) != "object") {
							return false;
						}
						
						/*if(match.time.begin == "Invalid Date" )
						{
							return false;
						}*/
						
						var validDate = new Date("January 1, 1970 00:01"); 
						if(match.time.begin < validDate)
						{
							return false;
						}
					
						
						try{
							(match.time.begin).getTime();
						}
						catch(e){
							return false;
						}
					}
					
					if (match.time.end) {
						if (typeof(match.time.end) != "object") {
							return false;
						}
						if(match.time.end == "Invalid Date")
						{
							return false;
						}
						try{
							(match.time.end).getTime();
						}
						catch(e){
							return false;
						}
					}
					if(match.time.begin && match.time.end)
					{
						if(match.time.begin > match.time.end)
						{
							return false;
						}
					}
					if (match.time.alarm) {
						
						if (typeof(match.time.alarm) != "object") {
							return false;
						}
						try{
							(match.time.alarm).getTime();
						}
						catch(e){
							return false;
						}
					}
					
				}
				/*if(match.time && match.repeatRule){
					if(match.time.end && match.repeatRule.untilDate){
						if((match.time.end > match.repeatRule.untilDate)){
							return false
						}
					}
				}*/
				if (match.repeatRule) {
					if (typeof match.repeatRule != 'object') {
						return false;
					}
					if (match.repeatRule.frequency) {
						if (typeof(match.repeatRule.frequency) != "string") {
							return false;
						}
					}
					if (match.repeatRule.startDate) {
						if (typeof(match.repeatRule.startDate) != "object") {
							return false;
						}
						if((match.repeatRule.startDate) == "Invalid Date")
						{
							return false;
						}
						try{
							(match.repeatRule.startDate).getTime();
						}
						catch(e){
							return false;
						}
					}
					if (match.repeatRule.untilDate) {
						if (typeof(match.repeatRule.untilDate) != "object") {
							return false;
						}
						if((match.repeatRule.untilDate) == "Invalid Date")
						{
							return false;
						}
						try{
							(match.repeatRule.untilDate).getTime();
						}
						catch(e){
							return false;
						}
					}
					if (match.repeatRule.startDate && match.repeatRule.untilDate)
					{
						if (match.repeatRule.startDate > match.repeatRule.untilDate)
						{
							return false;
						}
					}
					if (match.repeatRule.interval) {
						if (typeof(match.repeatRule.interval) != "number") {
							return false;
						}
					}
					if (match.repeatRule.month) {
						if (typeof(match.repeatRule.month) != "number") {
							return false;
						}
					}
					if (match.repeatRule.weekDays) {
						if (typeof(match.repeatRule.weekDays) != "object") {
							return false;
						}
					}
					if (match.repeatRule.daysOfMonth) {
						if (typeof(match.repeatRule.daysOfMonth) != "object") {
							return false;
						}
					}
					if (match.repeatRule.monthDates) {
						if (typeof(match.repeatRule.monthDates) != "object") {
							return false;
						}
					}
					
				}
			}
	//	////alert("returning true from input validation");
		return true;
}

function __sp_calendar_getList_repeatRule(sp_RepeatRule){
	var string;
 //     ////alert("getlist repeatrule************");
	switch(sp_RepeatRule.Type){
		case 1:
			string = "daily";
			this.frequency = string.toString();
			break;
		case 2:
			string = "weekly";
			this.frequency = string.toString();
			break;
		case 3:
			string = "monthly";
		//	////alert("monthly");
			this.frequency = string.toString();
			break;
		case 4:
			string = "yearly";
			this.frequency = string.toString();
			break;
		default:
			throw new DeviceException( this.error.INVALID_ARG_ERR, "Calendar: Repeat Rule Type is Invalid");
	}
	if (sp_RepeatRule.StartDate) {
		this.startDate = new Date(sp_RepeatRule.StartDate);
		//////alert("startdate");
	}
	if (sp_RepeatRule.UntilDate) {
		this.untilDate = new Date(sp_RepeatRule.UntilDate);
	}
	if (sp_RepeatRule.Interval) {
		this.interval = sp_RepeatRule.Interval;
	}
	if (sp_RepeatRule.DaysInWeek) {
		//	this.weekDays = sp_RepeatRule.DaysInWeek;
			this.weekDays = [];
			//repeatRule.weekDays;
			for(var a in sp_RepeatRule.DaysInWeek){
				if(sp_RepeatRule.DaysInWeek[a] == 6){
					sp_RepeatRule.DaysInWeek[a] = 0;
				}
				else{
					sp_RepeatRule.DaysInWeek[a]=sp_RepeatRule.DaysInWeek[a]+ 1;
				}
				this.weekDays.push(sp_RepeatRule.DaysInWeek[a]);
			}
	}
	
	if (sp_RepeatRule.Month) {
		this.month = sp_RepeatRule.Month;
	}
	if(sp_RepeatRule.DaysOfMonth){
		if(sp_RepeatRule.DaysOfMonth.Day){
			if(sp_RepeatRule.DaysOfMonth.Day == 6){
				sp_RepeatRule.DaysOfMonth.Day = 0;
			}
			else{
				sp_RepeatRule.DaysOfMonth.Day = sp_RepeatRule.DaysOfMonth.Day + 1;
			}
			this.daysOfMonth.day = sp_RepeatRule.DaysOfMonth.Day;
		}
		if(sp_RepeatRule.DaysOfMonth.WeekNum){
			this.daysOfMonth.weekInMonth = sp_RepeatRule.DaysOfMonth.WeekNum;
		}
	}
	
	if (sp_RepeatRule.MonthDays) {
		//	this.monthDates = sp_RepeatRule.MonthDays;
			this.monthDates = [];
			for( var i=0; i<sp_RepeatRule.MonthDays.length; i++){
				this.monthDates.push(sp_RepeatRule.MonthDays[i]-1);
			}
	}
}

function __sp_device_calendar_entry(sp_entry){ 
 // ////alert("sp_entry");
  if (sp_entry.id) {
  //	////alert("sp_entry id" + sp_entry.id);
	this.id = sp_entry.id;
	}
	if (sp_entry.Type ) {
	//	////alert("sp_entry.Type" + sp_entry.type);
  this.type = sp_entry.Type;
	}
  if (sp_entry.Summary) {
 // 	////alert("summary" + sp_entry.Summary);
  	this.summary = sp_entry.Summary;
  }
  if (sp_entry.Description) {
  	this.description = sp_entry.Description;
  }
  if (sp_entry.Location) {
  	this.location = sp_entry.Location;
  }
  if (sp_entry.InstanceStartTime) {
  	this.instanceStartTime = sp_entry.InstanceStartTime;
//	////alert("startTimeInstacce" + sp_entry.InstanceStartTime);
  }
//  ////alert("sp_entry.Priority" + sp_entry.Priority);
  if (sp_entry.Priority >= 0 || sp_entry.Priority<= 255) {
  	this.priority = sp_entry.Priority;
  }
  if (sp_entry.Status) {
  	this.status = sp_entry.Status;
  }
  if (sp_entry.Status == "TodoCompleted") {
  	this.status = "Completed";
  }
  else if(sp_entry.Status == "TodoNeedsAction"){
  	this.status = "NeedsAction";
  }
  
  
  if (sp_entry.ExDates) {
  	this.exceptionDates = sp_entry.ExDates;
  }
  if (sp_entry.RepeatRule) {
  	this.repeatRule = new __sp_calendar_getList_repeatRule(sp_entry.RepeatRule);
  }
 // ////alert("sp_entry.StartTime" + sp_entry.StartTime);
	if (dataGetList == 0) {
		this.time = new __sp_calendar_entry_time(sp_entry.InstanceStartTime, sp_entry.InstanceEndTime, sp_entry.AlarmTime);
	}
	else{
		this.time = new __sp_calendar_entry_time(sp_entry.StartTime, sp_entry.EndTime, sp_entry.AlarmTime);
	}

}


function __sp_daysOfMonth_build(daysOfMonth){
	if (daysOfMonth.day) {
		////alert(daysOfMonth.day);
		if(daysOfMonth.day == 0){
			daysOfMonth.day = 6;
		}
		else{
			////alert("in else");
			daysOfMonth.day = daysOfMonth.day-1;
		}
		////alert(daysOfMonth.day);
		this.Day = daysOfMonth.day;
			//alert("this.Day - "+ this.Day);
	}
	if (daysOfMonth.weekInMonth) {
		this.WeekNum = daysOfMonth.weekInMonth;
	//alert("this.WeekNum" + this.WeekNum);
	}
}


function __sp_calendar_addEntry_repeatRule(repeatRule,str){
	try{
			if (!(repeatRule.frequency)) {
				throw new DeviceException( this.error.MISSING_ARG_ERR, "Calendar: addEntry: frequency is missing");
			}
			else {
				var frequency = repeatRule.frequency;
					switch(frequency){
						case "daily":
								this.Type = 1;
								break;
						case "weekly":
								this.Type = 2;
							//	////alert("weekly" + this.Type );
								break;
						case "monthly":
								this.Type = 3;
							//	////alert("monthly" + this.Type );
								break;
						case "yearly":
								this.Type = 4;
								break;
					default:
						throw new DeviceException( this.error.INVALID_ARG_ERR, "Calendar: "+str+" Repeat Rule Type is Invalid");
					}
				if (repeatRule.startDate) {
					this.StartDate = repeatRule.startDate;
				//	////alert("this.StartDate123" +  this.StartDate);
				}
				if (repeatRule.untilDate) {
					this.UntilDate = repeatRule.untilDate;
				//	////alert("this.untilDate123" +  this.UntilDate);
				}
				if (repeatRule.interval) {
					this.Interval = repeatRule.interval;
				//	////alert("repeatRule.interval" + typeof repeatRule.interval);
				//	////alert("this.Interval" + typeof this.Interval);
					
				}
					
				if (repeatRule.weekDays){
						this.DaysInWeek = [];
						//repeatRule.weekDays;
						for(var a in repeatRule.weekDays){
							if(repeatRule.weekDays[a] == 0){
								repeatRule.weekDays[a] = 6;
							}
							else{
								repeatRule.weekDays[a]=repeatRule.weekDays[a]-1;
							}
							this.DaysInWeek.push(repeatRule.weekDays[a]);
						}
				//		////alert("this.DaysInWeek123" + typeof this.DaysInWeek);
				} 
			//	//alert(repeatRule.month);
				if (repeatRule.month) {
					this.Month = repeatRule.month;
					////alert("this.Month " + typeof this.Month +"  " + this.Month);
				}
		//	//alert("before MonthDays");
				if (repeatRule.monthDates) {
						this.MonthDays = [];
						//repeatRule.monthDates;
						for( var i=0; i<repeatRule.monthDates.length; i++){
							this.MonthDays.push(repeatRule.monthDates[i]-1);
						}
						////alert("repeatRule.monthDates" + repeatRule.monthDates + "this.MonthDays" + this.MonthDays);
				}
				
				if (repeatRule.daysOfMonth) {
					////alert("repeatRule.daysOfMonth = " + repeatRule.daysOfMonth[0].weekInMonth);
					this.DaysOfMonth = new Array();
					for (var a in repeatRule.daysOfMonth) {
						var dayofmnt = new __sp_daysOfMonth_build(repeatRule.daysOfMonth[a]);
						////alert(dayofmnt.Day);
						////alert(dayofmnt.WeekNum);
						(this.DaysOfMonth).push(dayofmnt);
					}
					
    			}
				
			}	
	}
	catch(e){
	////alert("exception");	
	 __device_handle_exception (e, "__sp_calendar_addEntry_repeatRule: " + e);	
	}
}

function __sp_calendar_entry(entry,str){
  // //alert("entry.type" + entry.type);
  try {
  	if (entry.type) {
		this.Type = entry.type;
	}

  	if (entry.id) {
		this.id = entry.id;
		if(isUpdate)
		{
			if (entry.time) {
				if (entry.time.begin) {
					this.StartTime = entry.time.begin;
				}
				if (entry.time.end) {
					this.EndTime = entry.time.end;
				}
			}
		}
	}
	
	if (entry.instanceStartTime) {
		this.InstanceStartTime = entry.instanceStartTime;
	}

  	if (entry.description ) {
		this.Description = entry.description;
	}
	else if(isUpdate && (entry.description == null)){
		this.Description = " ";
	}
	
  	if (entry.summary) {
		this.Summary = entry.summary;
	}
	else if(isUpdate && (entry.summary == null)){
		this.Summary = " ";
	}
	
  	if (entry.location) {
		this.Location = entry.location;
	}
	else if(isUpdate && (entry.location == null))
	{
		this.Location = " ";
	}
	
	if (entry.priority) {
		if ((entry.priority < 0) || (entry.priority > 255)) {
			throw new DeviceException( this.error.INVALID_ARG_ERR, "Calendar: "+str+" Priority is Invalid");
		}
		else {
			this.Priority = entry.priority;
		}
	}
	else if(isUpdate && (entry.priority == null))
	{
		this.Priority = 0;
	}
	
	if (entry.status) {
		this.Status = entry.status;
		if (entry.status == "NeedsAction" || entry.status == "Completed") {
			this.Status = "Todo"+entry.status;
		}
	}
	/*else if(isUpdate && (entry.status == null))
	{
		this.Status = "Tentative";
		//////alert("status****" + this.Status);
	}*/
	
	if (entry.exceptionDates) {
		this.ExDates = entry.exceptionDates;
	}
	if(entry.repeatRule){
			this.RepeatRule = new __sp_calendar_addEntry_repeatRule(entry.repeatRule,str);
			
		}
	
	if (entry.type != undefined && entry.type != null) {
		////alert("7857465988");
		if (typeof this.Type != "string") {
			//	////alert("Type is not a string");
			throw new DeviceException(this.error.INVALID_ARG_ERR, "Calendar: " + str + " Type is not a string");
		}
		switch (this.Type) {
			case "Meeting":
				if (entry.time) {
					if (entry.time.begin) {
						this.StartTime = entry.time.begin;
						////alert("this.StartTime" + this.StartTime);
					}
					if (entry.time.end) {
						this.EndTime = entry.time.end;
					}
				}
				break;
			case "Reminder":
			case "Anniversary":
				if (entry.time) {
					if (entry.time.begin) {
						this.StartTime = entry.time.begin;
					}
				}
				break;
			case "ToDo":
				if (entry.time) {
					if (entry.time.end) {
						this.EndTime = entry.time.end;
					}
				}
				break;
			case "DayEvent":
				if (entry.time) {
					if (entry.time.begin) {
						this.StartTime = entry.time.begin;
					}
				}
				break;
			default:
				throw new DeviceException(this.error.INVALID_ARG_ERR, "Calendar: " + str + " Type is Invalid");
		}
	}
	
	if (entry.time) {
		if (entry.time.alarm) {
			this.AlarmTime = entry.time.alarm;
		}
	}
	
	
 }
  catch (e) {
  		//alert("*****out");
    __device_handle_exception (e, "__sp_calendar_entry: " + e);

  } 
}

/* ------ Wrap sp iterator ------- */

function __sp_calendar_iterator_get_next(){
	//////alert("in get next");
  var sp_entry = this.iter.getNext();
 // ////alert("after calling sapi getlist");
 // ////alert("output of get next"+sp_entry.StartTime);
 // ////alert("type of output of get next"+typeof sp_entry);
  if(typeof sp_entry == "undefined"){
  //	////alert("return null");
    return null;
  }
  var calEntry = new __sp_device_calendar_entry(sp_entry);
  sp_entry.close();
  //////alert("return cal entry");
  return calEntry;
}

function __sp_calendar_iterator(js_iterator){
 // ////alert("in iter");	
  this.iter = js_iterator;
  this.next = __sp_calendar_iterator_get_next;
  this.close = function(){
		this.iter.close();
	};
}

/* --------- Public methods ---------- */
var /*const causes rhino to fail */ CALENDAR_APP_ID = 0x10005901;

// Apps should take care that this is not reinvoked
// while the editor is already running. 

function __sp_calendar_startEditor(editor_cb, entry, err_cb){
  try {
  	if (!editor_cb) {
  		//MissingArgument error "callback not passed";
		throw new DeviceException( this.error.MISSING_ARG_ERR, "Calendar: startEditor: callback is missing");
	   }
	else if (typeof editor_cb != "function") //here we check if the type of callback is function. This case is useful when arbitrary values are passed to callback
		{
		  //BadArgumentType error
		  throw new DeviceException( this.error.INVALID_ARG_ERR, "Calendar: startEditor: callback is invalid");
		}
	if(err_cb)
	{ 
		if(typeof err_cb != 'function')
		{
		   	throw new DeviceException( this.error.INVALID_ARG_ERR, "Calendar: startEditor: error callback is invalid");
		}
	}
	
	if(entry != null)
	{
		throw new DeviceException( this.error.NOT_SUPPORTED_ERR, "Calendar: startEditor: Entry should be null");
	}
	
	var finished = function(arg1, arg2, arg3){
	
	
	var iter = null;
	editor_cb(iter);
	if (arg2 != event_cancelled) {
		var iter = null;
		if (arg3.ReturnValue) {
			iter = new __sp_calendar_iterator(arg3.ReturnValue);
		}
		editor_cb(iter);
	}		
	
	if (arg3.ErrorCode != 0) {
		switch( arg3.ErrorCode )
			{
			 case this.error.MISSING_ARG_ERR :
			 case this.error.INVALID_ARG_ERR :
			 case this.error.NOT_SUPPORTED_ERR :
				if(arg3.ErrorMessage) 
					{
					var err_msg = splitErrorMessage(arg3.ErrorMessage); 	
					throw new DeviceException( MapErrorCode[arg3.ErrorCode], "Calendar: startEditor: "+err_msg);
					}
				else
					{
					throw new DeviceException( MapErrorCode[arg3.ErrorCode], "Calendar: startEditor: Operation Failed");	
					}
				break;

			default:
				err_cb(new DeviceException( MapErrorCode[arg3.ErrorCode], "Calendar: startEditor: Operation Failed"));
				 }
	   }
	
	};
	//For some reason, calendar is unable to parse command line
	__s60_start_and_wait(CALENDAR_APP_ID, '', finished);
	return 0;
	}
   catch (e) {
    __device_handle_exception (e, "__sp_calendar_startEditor: " + e);
  } 
}

var /*const causes rhino to fail */ __sp_calendar_entry_types = "MeetingReminderToDoAnniversaryDayEvent";

function __sp_calendar_getList_cb(arg1, arg2, arg3) {

	var CbObj;
	var calendar_cb;
	var err_cb;
	
	CbObj = glob_obj.getFromArray(arg1);
			
	 
	if (CbObj) {
		calendar_cb = CbObj.success_cb;
		err_cb = CbObj.error_cb;
	}
	 
	else{
		alert( "Calendar: __sp_calendar_getList_cb: Callback not found ");
		return;
	}
	
	
	//arg3.ErrorCode = DATA_OUT_OF_RANGE_ERR;
	//////alert("err"+arg3.ErrorCode);
	if(arg3.ErrorCode != 0)
	{
	//	////alert("before calling errcbk" + arg3.ErrorCode);
		err_cb(new DeviceException( arg3.ErrorCode, "Calendar: getList: Operation Failed"));
		return;
	}	
   //__device_debug("Calendar callback invoker");
   // arg1 --> transacation Id
   // arg2 --> Error code
   // iter --> return object as per the domain
   if (arg2 != event_cancelled) {
   	  
	   	var iter = null;
	   	if (arg3.ReturnValue) {
	   		iter = new __sp_calendar_iterator(arg3.ReturnValue);
			}
		   	calendar_cb(iter);
		}	
	glob_obj.removeFromArray(arg1);
    }

function __sp_calendar_getList(calendar_cb, match, err_cb){

//	////alert("in getlist");
	
    try {
  	if(match)
	{
  		if(typeof match != "object")
		{
			throw new DeviceException( this.error.INVALID_ARG_ERR, "Calendar: getList: match is invalid");
		}
		if (match.id) {
			dataGetList = 1;
			if (typeof match.id != "string") {
				throw new DeviceException(this.error.INVALID_ARG_ERR, "Calendar: getList: match is invalid");
			}
		}
		else
		{
			dataGetList = 0;
		}
	}
 	
  	if(!calendar_cb)
  	{
  		//MissingArgument error "callback not passed";
		throw new DeviceException( this.error.MISSING_ARG_ERR, "Calendar: getList: callback is missing");
  	}
  	else if(typeof calendar_cb != "function")	//here we check if the type of callback is function. This case is useful when arbitrary values are passed to callback
  	{
  		//BadArgumentType error
		throw new DeviceException( this.error.INVALID_ARG_ERR, "Calendar: getList: callback is invalid");
  	}
	if(err_cb)
	{ 
		//////alert("(inside)type of err_cb" + typeof err_cb);
		if(typeof err_cb != "function")
		{
	//		////alert("not func");
		   	throw new DeviceException( this.error.INVALID_ARG_ERR, "Calendar: getList: error callback is invalid");
		}
		if( err_cb == undefined || err_cb == null)
		{	
			//alert("333");
			throw new DeviceException( this.error.MISSING_ARG_ERR, "Calendar: getList: error callback is missing");
		}
	}
	

  

    // Note: sp bug requires filter values of some kind
    var filter = {}; 
	modifyObjectBaseProp(filter);
    filter.Type = "IncludeAll";
    if(match)
	{
	  if(match.id){
		filter.id = match.id;
      }
      if((match.type) && __sp_calendar_entry_types.match(match.type)){
		filter.Type = match.type;
      }
	  else if((match.type) && typeof match.type != "string")
	  {
	  	 throw new DeviceException(this.error.INVALID_ARG_ERR, "Calendar: getList: match is invalid");
	  }
      if(match.range){
		if(match.range.begin){
			if (typeof(match.range.begin) != "object") {
				throw new DeviceException(this.error.INVALID_ARG_ERR, "Calendar: getList: match is invalid");
			}
			else if((match.range.begin) == "Invalid Date"){
				throw new DeviceException(this.error.INVALID_ARG_ERR, "Calendar: getList: match is invalid");
			}
			else{
				filter.StartRange = match.range.begin;
			}
		}
        if(match.range.end){
			if (typeof(match.range.end) != "object") {
				throw new DeviceException(this.error.INVALID_ARG_ERR, "Calendar: getList: match is invalid");
			}
			else if((match.range.end) == "Invalid Date"){
				throw new DeviceException(this.error.INVALID_ARG_ERR, "Calendar: getList: match is invalid");
			}
			else{
				filter.EndRange = match.range.end;
			}
		}
		if((match.range.begin) && (match.range.end)){
			if((match.range.begin) > (match.range.end))
			{
				throw new DeviceException(this.error.INVALID_ARG_ERR, "Calendar: getList: match is invalid");
			}
		}
			
      }
      if(match.text){
	  	if (typeof(match.text) != "string") {
			throw new DeviceException(this.error.INVALID_ARG_ERR, "Calendar: getList: match is invalid");
		}
		else {
			filter.SearchText = match.text;
		}
      }
    }
//	////alert("filter.StartRange" + filter.StartRange);
//	////alert("filter.EndRange" + filter.EndRange);
    var criteria = {};
	modifyObjectBaseProp(criteria);
    criteria.Type = "CalendarEntry";
    criteria.Filter = filter;
	temp_scb = calendar_cb;
	temp_ecb = err_cb;
//	////alert("1111");
	var rval = this.so.IDataSource.GetList(criteria , this.getListCb );
	if(rval.TransactionID){
			glob_obj.addToGlobalArray(rval.TransactionID,calendar_cb,err_cb);
		}
//	////alert("2222*******");
	if (criteria) {
		delete criteria.Type;
		delete criteria.Filter;
	}
//	////alert("rval.ErrorCode getlist" + rval.ErrorCode);
    if(rval.ErrorCode != 0)
		{
			
		switch( rval.ErrorCode )
			{
			 case this.error.MISSING_ARG_ERR :
			 case this.error.INVALID_ARG_ERR :
			 case this.error.NOT_SUPPORTED_ERR :
			 	////alert("case NOT_SUPPORTED_ERR");
				if(rval.ErrorMessage) 
					{
					var err_msg = splitErrorMessage(rval.ErrorMessage); 
					//////alert("1111" + rval.ErrorMessage);	
					throw new DeviceException( MapErrorCode[rval.ErrorCode], "Calendar: getList: "+err_msg);
					
					}
				else
					{
					//////alert("2222" + rval.ErrorMessage);
					throw new DeviceException( MapErrorCode[rval.ErrorCode], "Calendar: getList: Operation Failed");	
					}
				break;

			default:
			//	////alert("Calendar: getList: Operation Failed");
				err_cb(new DeviceException( MapErrorCode[rval.ErrorCode], "Calendar: getList: Operation Failed"));
				 }
   		}
	 return rval.TransactionID;
  }
  catch (e) {
  	 //  ////alert("out");
    __device_handle_exception (e, "sp_calendar_getList: " + e);
  }  
//////alert("out getlist");
}

function __sp_calendar_add(entry){
	
	
	if(entry)
	{
		if(typeof entry != "object")
		{
			throw new DeviceException(this.error.INVALID_ARG_ERR, 'Calendar: addEntry: calendarEntry param is invalid');			
		}
	//	//alert("add entry1");
		if(entry.id)
		{
			entry.id = undefined;
		}
	//	//alert("add entry2");
		if(!entry.type || !entry.time)
		{
			throw new DeviceException(this.error.MISSING_ARG_ERR, "Calendar: addEntry: mandatory param missing");
		}
		else if(typeof entry.type != "string" || typeof entry.time != "object")
		{
			throw new DeviceException(this.error.INVALID_ARG_ERR, "Calendar: addEntry: mandatory param missing");
		}
	//	//alert("add entry3");
		if((entry.type != "ToDo") && !entry.time.begin )
		{
			throw new DeviceException(this.error.MISSING_ARG_ERR, "Calendar: addEntry: mandatory param StartTime missing");
		}
	//	//alert("add entry4");
		if(!entry.time.end && (entry.type == "ToDo"  || entry.type == "Meeting"))
		{
			throw new DeviceException(this.error.MISSING_ARG_ERR, "Calendar: addEntry: mandatory param EndTime missing");
		}
	//	//alert("add entry5");
		if(entry.time.end && entry.time.alarm)
		{
			if(entry.time.end < entry.time.alarm)
			{
				throw new DeviceException(this.error.NOT_SUPPORTED_ERR, "Calendar: addEntry: alarm time greater than end time:Not supported");
			}
		}
		
		if(entry.type == "ToDo"){
			if(entry.status == 0) {
				if (typeof(entry.status) != "string") {
					throw new DeviceException(this.error.INVALID_ARG_ERR, "Calendar: addEntry: mandatory param missing");
				}
			}
		}
		
	//	//alert("add entry7");
		if (entry.repeatRule) {
			if(typeof entry.repeatRule != 'object')
			{
				throw new DeviceException(this.error.INVALID_ARG_ERR, "Calendar: addEntry: repeatRule param type is invalid");
			}
			
			if (!entry.repeatRule.frequency || entry.repeatRule.frequency == null) 
			{
				throw new DeviceException(this.error.MISSING_ARG_ERR, "Calendar: addEntry: mandatory param Frequency missing");
			}
		}
	
		var isValid = __sp_calendar_isInputValid(entry);
	//	//alert(isValid);
	    	    
	    if (!isValid) {	
		//	////alert("returned false");    
	        throw new DeviceException(this.error.INVALID_ARG_ERR, "Calendar: addEntry: calendarEntry param is invalid");
	    }
	//	////alert("returned true");
	}
	else
	{
		throw new DeviceException(this.error.MISSING_ARG_ERR, "Calendar: addEntry: mandatory param missing");
	}
	
  try{
  	////alert("calendar_entry");
  	var str = "addEntry:";
    var criteria = {};
	modifyObjectBaseProp(criteria);
    criteria.Type = "CalendarEntry";
    criteria.Item = new __sp_calendar_entry(entry,str);
	
 //   //alert("before add");
	var result = this.so.IDataSource.Add(criteria);
	//alert("result" + result.ErrorCode);
	if (criteria) {
		delete criteria.Type;
		delete criteria.Item;
	}
	var err_msg = "Operation Failed";
	if(result.ErrorMessage)
	{
	err_msg = splitErrorMessage(result.ErrorMessage); 	
	}
//	//alert(result.ErrorCode);
    if (result.ErrorCode != 0) {
			//alert("throwdeviceexptn" +result.ErrorCode);
			throw new DeviceException( MapErrorCode[result.ErrorCode], "Calendar: addEntry: Operation Failed");	
			return;
		}
	else {
		var retVal = result.ReturnValue;
		return retVal;
	}
//	////alert("addEntry");
  }
  catch(e){
 // 	////alert("exception");
    __device_handle_exception (e, "__sp_calendar_add: " + e);
  }
}

function __sp_calendar_update(entry){
	isUpdate = 1;
	if(entry)
		{
			if(typeof entry != 'object')
			{				
				throw new DeviceException(this.error.INVALID_ARG_ERR, 'Calendar: updateEntry: calendarEntry param is invalid');			
			}
			if(!entry.id)
			{
				throw new DeviceException(this.error.MISSING_ARG_ERR, "Calendar: updateEntry: mandatory param - Id missing");
			}	
			if (entry.repeatRule) {
				
				if(typeof entry.repeatRule != 'object')
				{
					throw new DeviceException(this.error.INVALID_ARG_ERR, "Calendar: updateEntry: repeatRule param type is invalid");
				}
				if(/*entry.repeatRule.frequency && */(entry.repeatRule.frequency == null || entry.repeatRule.frequency == undefined))
				{
					////alert("am here in repeatrule");
					throw new DeviceException(this.error.INVALID_ARG_ERR, "Calendar: updateEntry: repeatRule param type is invalid");
				}
				if(entry.repeatRule.startDate && (entry.repeatRule.startDate == null || entry.repeatRule.startDate == undefined))
				{
					throw new DeviceException(this.error.INVALID_ARG_ERR, "Calendar: updateEntry: repeatRule param type is invalid");
				}
				if(entry.repeatRule.untilDate && (entry.repeatRule.untilDate == null || entry.repeatRule.untilDate == undefined))
				{
					throw new DeviceException(this.error.INVALID_ARG_ERR, "Calendar: updateEntry: repeatRule param type is invalid");
				}
			}
			if(entry.time)
			{
				if(entry.time.end && entry.time.alarm)
				{
					if(entry.time.alarm > entry.time.end)
					{
						throw new DeviceException(this.error.NOT_SUPPORTED_ERR, "Calendar: updateEntry: alarm time greater than end time is not supported");
					}
				}
			}
		    var isValid = __sp_calendar_isInputValid(entry);
		//    //alert("isValid" + isValid);		    
		    if (!isValid) {	    
		        throw new DeviceException(this.error.INVALID_ARG_ERR, "Calendar: updateEntry: calendarEntry param is invalid");
		    }
		}
		
		else
		{
			////alert("missing argument");
			throw new DeviceException(this.error.MISSING_ARG_ERR, "Calendar: updateEntry: mandatory param missing");
		}
  try{
  	//alert("update");
  	var str = "updateEntry:";
    var criteria = {};
	modifyObjectBaseProp(criteria);
    criteria.Type = "CalendarEntry";
    criteria.Item = new __sp_calendar_entry(entry,str);
	isUpdate = 0;
//	//alert("am here in update entry");
    var result = this.so.IDataSource.Add(criteria);
//	//alert("result.ErrorCode" + result.ErrorCode);
	if (criteria) {
		delete criteria.Type;
		delete criteria.Item;
	}
	var err_msg = "Operation Failed";
	if(result.ErrorMessage)
	{
	err_msg = splitErrorMessage(result.ErrorMessage); 	
	}
    if (result.ErrorCode != 0) {
			////alert("throwdeviceexptn" +result.ErrorCode);
			throw new DeviceException( MapErrorCode[result.ErrorCode], "Calendar: addEntry: Operation Failed");	
			return;
		}
	else {
		var retVal = result.ReturnValue;
		return retVal;
   		}
  }
  catch(e){
 // 	////alert("update exception" + e.message);
    __device_handle_exception (e, "__sp_calendar_add: " + e);
  }
}

function __sp_calendar_delete(data){

//	////alert("in delete");
  try{
  	if(data)
	{
		if(typeof data != "object")
		{
			throw new DeviceException( this.error.INVALID_ARG_ERR, "Calendar: deleteEntry: data is invalid");
		}
		if (!data.id) 
		{
			throw new DeviceException( this.error.MISSING_ARG_ERR, "Calendar: deleteEntry: id is missing");
		}
		var isValid = __sp_calendar_isInputValid(data);
	    
	    if (!isValid) {      
	        throw new DeviceException(this.error.INVALID_ARG_ERR, "Calendar: deleteEntry: delete data is invalid");
	    }
	}
	else
	{
		throw new DeviceException( this.error.MISSING_ARG_ERR, "Calendar: deleteEntry: data is missing");
	}
	
  	
	
    var criteria = {};
	modifyObjectBaseProp(criteria);
    criteria.Type = "CalendarEntry";
    criteria.Data = {};
	modifyObjectBaseProp(criteria.Data);
    criteria.Data.IdList = [];
	var list = [data.id];
	//list  = data.id;       //new Array(data.id);
	criteria.Data.IdList = list;
	if (data.range) {
		if (data.range.begin) {
		criteria.Data.StartRange = data.range.begin;
		}
		if (data.range.end) {
		criteria.Data.EndRange = data.range.end;
		}
	}	
   var rval = this.so.IDataSource.Delete(criteria);
 //  ////alert("rval.ErrorCode" + rval.ErrorCode);
   if (criteria) {
   	delete criteria.Type;
	delete criteria.Data.IdList;
	delete criteria.Data.StartRange;
	delete criteria.Data.EndRange;
   }
   if (list) {
   	delete list.id;
   }
   if(rval.ErrorCode != 0)
	{
		if(rval.ErrorMessage) 
			{
			var err_msg = splitErrorMessage(rval.ErrorMessage); 	
			throw new DeviceException( MapErrorCode[rval.ErrorCode], "Calendar: deleteEntry: "+err_msg);
			}
		else
			{
			throw new DeviceException( MapErrorCode[rval.ErrorCode], "Calendar: deleteEntry: Operation Failed");	
			}
   	}
  }
  catch(e){
 // 	////alert("exception");
    __device_handle_exception (e, "__sp_calendar_delete: " + e);
  }
}

function __sp_calendar_cancel(transactionId)
{
	try{
    if (!transactionId || transactionId == null || transactionId == undefined) {
		throw new DeviceException( this.error.MISSING_ARG_ERR, "Calendar: cancel: id is missing");//SErrMissingArgument = 1003  
	}
	if(transactionId)
	{
		if(typeof transactionId != "number" ){
			throw new DeviceException( this.error.INVALID_ARG_ERR, "Calendar: cancel: id is missing");//SErrMissingArgument = 1003  
		}
	}
    var criteria = {};
    modifyObjectBaseProp(criteria);
	criteria.TransactionID = transactionId;
    var result = this.so.IDataSource.Cancel(criteria);
	if(criteria){
		delete criteria.TransactionID;
	}
	//alert("result.ErrorCode" + result.ErrorCode);
   if(result.ErrorCode != 0)
		{
		if(result.ErrorMessage) 
			{
			var err_msg = splitErrorMessage(result.ErrorMessage); 	
			throw new DeviceException( MapErrorCode[result.ErrorCode], "Calendar: cancel: "+err_msg);
			}
		else
			{
			throw new DeviceException( MapErrorCode[result.ErrorCode], "Calendar: cancel: Operation Failed");	
			}
   		}
	}
	catch(e){
    __device_handle_exception (e, "__sp_calendar_cancel: " + e);		
	}
}

function __sp_calendar_instance(){
  //Descriptor
  this.descriptor = new __sp_calendar_descriptor();
  //Core methods
  //////alert("startEditor");
  this.startEditor = __sp_calendar_startEditor;
  //Extended methods
  this.getList = __sp_calendar_getList;
  this.getListCb = __sp_calendar_getList_cb;
    
  this.addEntry = __sp_calendar_add;
  this.updateEntry = __sp_calendar_update;
  this.deleteEntry = __sp_calendar_delete;
  this.cancel = __sp_calendar_cancel;
  this.error = new DeviceException(0, "Dummy");
  //Private data
  this.so = null;
  //Private methods
  try {
	this.so = device.getServiceObject("Service.Calendar", "IDataSource");
	//////alert(so);
    }
  catch (e){
    __device_handle_exception(e, "Calendar service not available");
  }
}