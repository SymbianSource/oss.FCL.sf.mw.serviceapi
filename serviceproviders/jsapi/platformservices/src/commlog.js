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

function __device_commlog_descriptor(provider){
  this.interfaceName = provider.interfaceName;
  this.version = provider.version;
}

function __device_commlog_getList(commlog_cb, match, ErrorCallback){
  return this.provider.getList(commlog_cb, match, ErrorCallback);
}

function __device_commlog_setNotification(commlog_cb, ErrorCallback){
  return this.provider.setNotification(commlog_cb, ErrorCallback);
}

function __device_commlog_cancelNotification( ){
  return this.provider.cancelNotification( );
}

function __device_commlog_cancel( transactionId ){
  return this.provider.cancel( transactionId );
}

function __device_commlog_deleteLogEntry( logId ){
  return this.provider.deleteLogEntry( logId );
}

// Private location prototype: called from service factory
function __device_commlog(provider){
	//alert("in providere")
  //Private properties
  this.provider = provider;
  //Read-only properties
  this.interfaceName = provider.descriptor.interfaceName;
  this.version = provider.descriptor.version;  
  //Extended methods
  this.getList = __device_commlog_getList;
  this.setNotification = __device_commlog_setNotification;
  this.cancelNotification = __device_commlog_cancelNotification;
  this.cancel = __device_commlog_cancel;
  this.deleteLogEntry = __device_commlog_deleteLogEntry;
}

// commlog service interface

var __device_commlog_service_entry = {"name": null, 
				      "version": null,
				      "proto": __device_commlog,
				      "descriptor": __device_commlog_descriptor,
				      "providers": [{"descriptor": __sp_commlog_descriptor, "instance": __sp_commlog_instance}]
				     };
		



/*
 Copyright © 2009 Nokia. All rights reserved.
 Code licensed under the BSD License:
 Software License Agreement (BSD License) Copyright © 2009 Nokia.
 All rights reserved.
 Redistribution and use of this software in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 Neither the name of Nokia Corporation. nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission of Nokia Corporation.
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 version: 1.0
 */
var invoker_notification;
//var error = new DeviceException(0, 'dummy');
// S60 sp-based commlog provider



function __sp_commlog_descriptor(){
    //Read-only properties
    this.interfaceName = "commlog";
    if (window.__Service_Interface_Ver) 
        this.version = __Service_Interface_Ver;
    else 
        this.version = 1.0;
    //Class-static properties 
}

var __sp_commlog_type_constants = {
    "call": 0,
    "sms": 3
};

var __sp_commlog_constants = {
    "received": 0, // Incoming received
    "missed": 5, // Incoming missed
    "outgoing": 1
};

var __sp_commlog_constants_output = {
    "Received": 0, // Incoming received
    "Missed": 5, // Incoming missed
    "Outgoing": 1
};

/*
 * Array holding Connection objects for setNotification
 */
var __notifArr = new Array();

/*
 * Counter to hold number of setNotification calls
 */
var __notifCount = 0;

/*
 * Object to hold connectionId and callback for setNotification
 */
__Notification.prototype = new Object();
__Notification.prototype.constructor = __Notification;

/*
 * Constructor for Notification
 */
function __Notification(transactionId, callback){
    this.connectionId = transactionId;
    this.callback = callback;
    
}


var __nofLogs;

function __get_const_string(def, val){
    var i;
    for (i in def) {
        if (def[i] == val) {
            return i;
        }
    }
    return null;
}


function __get_const_val(def, str){//alert(def+"  "+str);
    if (def[str] != undefined) {
        return def[str];
    }
    return null; //TBD: trow an exception on bad input
}





// All of the event fields should normally be filled in, so don't make the returned event sparse

function __device_commlog_item(sp_commlog){
    if (!sp_commlog) {
        return null;
    }
    var evt = {};
    evt.type = __get_const_string(__sp_commlog_type_constants, sp_commlog.EventType);
    if (evt.type == null || evt.type == undefined) 
        return null;
    evt.phoneNumber = sp_commlog.PhoneNumber;
    if (evt.phoneNumber == null || evt.phoneNumber == undefined || evt.phoneNumber.length == 0) 
        evt.phoneNumber = "private number";
    evt.time = sp_commlog.EventTime;
    evt.flag = (sp_commlog.Direction == undefined) ? null : __get_const_string(__sp_commlog_constants_output, sp_commlog.Direction);
    evt.summary = sp_commlog.Description;
    evt.logId = Number(sp_commlog.id);
    evt.contactName = sp_commlog.RemoteParty;
    if (!evt.contactName) 
        evt.contactName = evt.phoneNumber;
    return evt;
}

/* ------ Wrap sp iterator ------- */
function __sp_commlog_iterator_get_next(){
    //__device_debug("sp_commlog_iterator_get_next");
    //alert(__nofLogs);
    if (typeof __nofLogs == "number") {
        if (__nofLogs <= 0) {
            return null;
        }
        __nofLogs = __nofLogs - 1;
    }
    
    
    if ((typeof this.buffer == "object") && (this.buffer != null)) {
        var b1 = this.buffer;
        this.buffer = null;
        var rval1 = new __device_commlog_item(b1);
        return rval1;
    }
    else {
        var sp_commlog;
        if (this.iter != undefined && this.iter != null) {
            while (sp_commlog = this.iter.getNext()) {
                if (sp_commlog.EventType == 0 || sp_commlog.EventType == 3) 
                    break;
            }
        }
        
        if (typeof sp_commlog == "undefined") {
            return null;
        }
        var rval = new __device_commlog_item(sp_commlog);
        sp_commlog.close();
        return rval;
    }
    
    
    // return sp_commlog;
}

function __sp_commlog_iterator_has_next(){
    if (__nofLogs <= 0) 
        return false;
    
    if (this.iter != undefined && this.iter != null) {
        while (this.buffer = this.iter.getNext()) {
            if (this.buffer.EventType == 0 || this.buffer.EventType == 3) 
                break;
        }
        
    }
    
    
    if ((typeof this.buffer == "object") && (this.buffer != null)) {
        return true;
    }
    else {
        return false;
    }
}

function __sp_commlog_iterator_close(){

    this.iter.close();
    
    
}

function __sp_commlog_iterator(js_iterator){
    this.iter = js_iterator;
    this.buffer = null;
    this.next = __sp_commlog_iterator_get_next;
    this.hasNext = __sp_commlog_iterator_has_next;
    this.close = __sp_commlog_iterator_close;
    this.nofLogs = __nofLogs;
    
}

function __sp_commlog_getList_cb(arg1, arg2, arg3){
    var success_cb;
    var error_cb;
    var iter = null;
    var err_msg = null;
    
    var CbObj;
    
    
    CbObj = glob_obj.getFromArray(arg1);
    
    if (CbObj) {
        success_cb = CbObj.success_cb;
        error_cb = CbObj.error_cb;
    }
    
    else {
        alert("Commlog: __sp_commlog_getList_cb : Callback not found ");
		return;
    }
    
    
    if (arg3.ErrorCode != 0) {
    
        if (arg3.ErrorMessage) {
            err_msg = splitErrorMessage(arg3.ErrorMessage);
        }
        else {
            err_msg = "operation failed";
        }
        
        if (error_cb) {
            setTimeout(function(){
                error_cb(new DeviceException(MapErrorCode[arg3.ErrorCode], "Commlog: getList: " + err_msg));
            }, 1000);
            return;
        }
    }
    else 
        if (arg3.ReturnValue) {
            iter = new __sp_commlog_iterator(arg3.ReturnValue);
        }
    
    if (arg2 != event_cancelled) // 3 signifies eventcancelled 
    {
        success_cb(iter);
    }
    glob_obj.removeFromArray(arg1);
}

function __sp_commlog_getList(commlog_success_cb, match, ErrorCallback){
    //alert("in getlist");
    
    if (commlog_success_cb == null || commlog_success_cb == undefined) {
        throw new DeviceException(this.error.MISSING_ARG_ERR, "CommLog:getList:callback is Required");
    }
    
    else 
        if (typeof commlog_success_cb != "function") { //here we check if the type of callback is function. This case is useful when arbitrary values are passed to callback
            throw new DeviceException(this.error.INVALID_ARG_ERR, "CommLog:getList:Invalid Callback");
        }
    if (ErrorCallback) {
        if (typeof(ErrorCallback) != 'function') {
            throw new DeviceException(this.error.INVALID_ARG_ERR, "CommLog: getList: ErrorCallback is invalid");
        }
    }
    
    if (match != null && match != undefined) {
        if (typeof match != "object" || __device_typeof(match) == "Array") {
            throw new DeviceException(this.error.INVALID_ARG_ERR, "CommLog: getList: Match is not an object");
        }
        
        if (match.type != null && match.type != undefined) {
            if (typeof match.type != "string") {
                throw new DeviceException(this.error.INVALID_ARG_ERR, "CommLog: getList: Type is not a string");
            }
        }
        
        if (match.flag != null && match.flag != undefined) {
            if (typeof match.flag != "string") {
                throw new DeviceException(this.error.INVALID_ARG_ERR, "CommLog: getList: Flag is not a string");
            }
            
            if (match.type) {
                if (match.type.toLowerCase() == "sms" && match.flag.toLowerCase() == "missed") {
                    if (ErrorCallback) {
						//alert("1111");
						ErrorCallback(new DeviceException(this.error.DATA_OUT_OF_RANGE_ERR, "commlogs: getList: Missed is not supported for sms"));
                        //setTimeout(function(){ErrorCallback(new DeviceException(this.error.DATA_OUT_OF_RANGE_ERR, "commlogs: getList: Missed is not supported for sms"));  }, 1000);
                        return;
                    }
                    else {
                        throw new DeviceException(this.error.DATA_OUT_OF_RANGE_ERR, "commlogs: getList: Missed is not supported for sms");
                        
                    }
                }
            }
        }
        
        if (match.nofLogs != null && match.nofLogs != undefined) {
            if (typeof match.nofLogs != "number") {
                throw new DeviceException(this.error.INVALID_ARG_ERR, "CommLog: getList: nofLogs is invalid");
            }
        }
    }
    //alert("after input validation");
    try {
        var criteria = {};
        modifyObjectBaseProp(criteria);
        criteria.Type = 'Log';
        criteria.Filter = {};
        modifyObjectBaseProp(criteria.Filter);
        
        if (match) {
            //alert(match.type.toLowerCase());
            if (match.type) { //Check it type is populated   	    
                var typevalue;
                typevalue = __get_const_val(__sp_commlog_type_constants, match.type.toLowerCase());
                //alert(typevalue);
                if (typevalue != undefined) {
                    criteria.Filter.EventType = typevalue;
                }
                else {
                    if (ErrorCallback) {
						//alert("22222222222" +this.error.DATA_OUT_OF_RANGE_ERR);
						ErrorCallback(new DeviceException(this.error.DATA_OUT_OF_RANGE_ERR, "CommLog: getList: Type is out of range"));
                        //setTimeout(function(){   ErrorCallback(new DeviceException(this.error.DATA_OUT_OF_RANGE_ERR, "CommLog: getList: Type is out of range")); }, 1000);
                        return;
                    }
                    else {
                        throw new DeviceException(this.error.DATA_OUT_OF_RANGE_ERR, "CommLog: getList: Type is out of range");
                    }
                }
            }
            
            if (match.nofLogs != null && match.nofLogs != undefined) {
                if ((match.nofLogs < 0) || (match.nofLogs != (match.nofLogs | 0))) {
                    if (ErrorCallback) {
						//alert("33333333333");
						ErrorCallback(new DeviceException(this.error.DATA_OUT_OF_RANGE_ERR, "CommLog: getList: nofLogs is out of range"));
                       // setTimeout(function(){ ErrorCallback(new DeviceException(this.error.DATA_OUT_OF_RANGE_ERR, "CommLog: getList: nofLogs is out of range"));                      }, 1000);
                        return;
                    }
                    else {
                        throw new DeviceException(this.error.DATA_OUT_OF_RANGE_ERR, "CommLog: getList: nofLogs is out of range");
                    }
                }
                __nofLogs = match.nofLogs;
            }
            if (match.flag) { //Check if flag is populated
                var directionvalue;
                directionvalue = __get_const_val(__sp_commlog_constants, match.flag.toLowerCase());
                
                if (directionvalue != undefined) {
                    criteria.Filter.Direction = directionvalue;
                }
                else {
                    if (ErrorCallback) {
                        /*setTimeout(function(){
							//alert("444444444444");
                            ErrorCallback(new DeviceException(this.error.DATA_OUT_OF_RANGE_ERR, "CommLog: getList: Flag is out of range"));
                        }, 1000);*/
						ErrorCallback(new DeviceException(this.error.DATA_OUT_OF_RANGE_ERR, "CommLog: getList: Flag is out of range"));
                    }
                    else {
                        throw new DeviceException(this.error.DATA_OUT_OF_RANGE_ERR, "CommLog: getList: Flag is out of range");
                    }
                }
            }
            
            if (match.phoneNumber != null && match.phoneNumber != undefined) {
                if (match.phoneNumber != "") //Check if phone is populated
                    criteria.Filter.PhoneNumber = match.phoneNumber;
            }
            
            if (match.contactName != null && match.contactName != undefined) {
                if (match.contactName != "") 
                    criteria.Filter.RemoteParty = match.contactName;
            }
            
            if (match.startTime != null && match.startTime != undefined) {
                criteria.Filter.StartTime = match.startTime;
            }
            
            if (match.endTime != null && match.endTime != undefined) {
                criteria.Filter.EndTime = match.endTime;
            }
        }
        
        
        temp_scb = commlog_success_cb;
		temp_ecb = ErrorCallback;
        var result = this.so.IDataSource.GetList(criteria, this.getListCb);
        
        if (result.TransactionID) {
            glob_obj.addToGlobalArray(result.TransactionID, commlog_success_cb, ErrorCallback);
        }
        
        if (criteria.Filter) {
            delete criteria.Filter.Direction;
            delete criteria.Filter.EventType;
            delete criteria.Filter.PhoneNumber;
        }
        if (criteria) {
            delete criteria.Filter;
            delete criteria.Type;
        }
        
        if (result.ErrorCode != 0) {
            var err_msg = "operation failed";
            if (result.ErrorMessage) {
                err_msg = splitErrorMessage(result.ErrorMessage);
            }
            switch (MapErrorCode[result.ErrorCode]) {
                case this.error.INVALID_ARG_ERR:
                case this.error.MISSING_ARG_ERR:
                case this.error.NOT_SUPPORTED_ERR:
                    throw new DeviceException(MapErrorCode[result.ErrorCode], "CommLog:getList:" + err_msg);
                    break;
                    
                default:
                    if (ErrorCallback) {
                    
                        ErrorCallback(new DeviceException(MapErrorCode[result.ErrorCode], "CommLog:getList:" + err_msg));
                        
                        return;
                    }
                    else {
                        throw new DeviceException(MapErrorCode[result.ErrorCode], "CommLog:getList:" + err_msg);
                    }
                    
            }
        }
        //	//alert(result.TransactionID);
        return result.TransactionID;
    } 
    catch (e) {
        __device_handle_exception(e, "__sp_commlog_Input_validation: " + e);
    }
    
    
}

function __sp_commlog_setNotification_cb(arg1, arg2, arg3){
    var success_cb;
    var error_cb;
    var result = null;
    //alert("arg3.ReturnValue  is "+arg3.ReturnValue+"  "+arg3.ErrorCode);
    var CbObj;
    
    
    CbObj = glob_obj.getFromArray(arg1);
    
    if (CbObj) {
        success_cb = CbObj.success_cb;
        error_cb = CbObj.error_cb;
    }
    
    else {
        alert("Commlog: __sp_commlog_setNotification_cb : Callback not found ");
		return;
    }
    
    if (arg3.ErrorCode != 0) {
        if (arg3.ErrorMessage) {
            err_msg = splitErrorMessage(arg3.ErrorMessage);
        }
        else {
            err_msg = "operation failed";
        }
        
        if (error_cb) {
            error_cb(new DeviceException(MapErrorCode[arg3.ErrorCode], "CommLog: getList: " + err_msg));
            return;
        }
    }
    else 
        if (arg3.ReturnValue) {//alert("in return value");
            result = new __device_commlog_item(arg3.ReturnValue);
        }
    
    if (arg2 != event_cancelled) // 3 signifies eventcancelled 
    {//alert("in not event cancelled"+"  "+arg1 +"  "+ __notifArr[0].connectionId);
        for (i in __notifArr) {
            if (arg1 == __notifArr[i].connectionId) {
                var found = __notifArr[i];
                break;
            }
        }
        //alert(found);
        if (found) 
            found.callback(result);
    }
	glob_obj.removeFromArray(arg1);
}

//TBD: implement these?

function __sp_commlog_setNotification(successCallback, ErrorCallback){

    if (!successCallback) {
        throw new DeviceException(this.error.MISSING_ARG_ERR, "CommLog:setNotification:callback is missing");
    }
    
    if (typeof successCallback != "function") {
        throw new DeviceException(this.error.INVALID_ARG_ERR, "CommLog:setNotification:callback is invalid");
    }
    
    if (ErrorCallback) {
        if (typeof(ErrorCallback) != 'function') {
            throw new DeviceException(this.error.INVALID_ARG_ERR, "CommLog: setNotification: ErrorCallback is invalid");
        }
    }
    
    
    
    for (i in __notifArr) {
        var spliced = __notifArr[i];
        __notifArr.splice(i, 1);
        __notifCount = __notifArr.length;
        
        this.so.IDataSource.Cancel({
            TransactionID: spliced.connectionId
        });
        break;
    }
    
    
    
    var criteria = {};
    modifyObjectBaseProp(criteria);
    criteria.Type = "Log";
    criteria.Filter = {
        DelayTime: 0
    };
    
    temp_scb = successCallback;
	temp_ecb = ErrorCallback;
    var result = this.so.IDataSource.RequestNotification(criteria, this.setNotificationCb);
    if (result.TransactionID) {
        glob_obj.addToGlobalArray(result.TransactionID, successCallback, ErrorCallback);
    }
    //alert("after call");
    __notifArr[__notifCount++] = new __Notification(result.TransactionID, successCallback);
    //alert("after count");
    if (criteria) {
        delete criteria.Type;
    }
    
    if (result.ErrorCode != 0) {
        var err_msg = "operation failed";
        if (result.ErrorMessage) {
            err_msg = splitErrorMessage(result.ErrorMessage);
        }
        //alert(MapErrorCode[ result.ErrorCode ] );
        switch (MapErrorCode[result.ErrorCode]) {
            case this.error.INVALID_ARG_ERR:
            case this.error.MISSING_ARG_ERR:
            case this.error.NOT_SUPPORTED_ERR:
                throw new DeviceException(MapErrorCode[result.ErrorCode], "CommLog:setNotification:" + err_msg);
                break;
                
            default:
                if (ErrorCallback) {
                    setTimeout(function(){
                        ErrorCallback(new DeviceException(MapErrorCode[result.ErrorCode], "CommLog:setNotification:" + err_msg));
                    }, 1000);
                }
                else {
                    throw new DeviceException(MapErrorCode[result.ErrorCode], "CommLog:setNotification:" + err_msg);
                }
                
        }
    }
}

function __sp_commlog_cancelNotification(){
    //alert("in cancel notification");
    
    for (i in __notifArr) {//alert("in array");
        if (__notifArr[i].connectionId) {
            var spliced = __notifArr[i];
            __notifArr.splice(i, 1);
            __notifCount = __notifArr.length;
            break;
        }
    }
    if (spliced) {
        var result = this.so.IDataSource.Cancel({
            TransactionID: spliced.connectionId
        });
        
        if (result.ErrorCode != 0) {
            var err_msg = "operation failed";
            if (result.ErrorMessage) {
                err_msg = splitErrorMessage(result.ErrorMessage);
            }
            
            //throw new DeviceException (MapErrorCode[ result.ErrorCode ],"CommLog:cancelNotification:" + err_msg );
        }
    }
}

function __sp_commlog_cancel(transactionId){//alert("in cancel");
    if (!transactionId) {
        throw new DeviceException(this.error.MISSING_ARG_ERR, "CommLog:cancel:transactionId is missing");
    }
    
    if (typeof transactionId != "number") {
        throw new DeviceException(this.error.INVALID_ARG_ERR, "CommLog:cancel:transactionId is invalid");
    }
    
    var result = this.so.IDataSource.Cancel({
        TransactionID: transactionId
    });
    
    if (result.ErrorCode != 0) {
        var err_msg = "operation failed";
        if (result.ErrorMessage) {
            err_msg = splitErrorMessage(result.ErrorMessage);
        }
        
        throw new DeviceException(MapErrorCode[result.ErrorCode], "CommLog:cancel:" + err_msg);
    }
}

function __sp_commlog_deleteLogEntry(logId){

    if (logId == null || logId == undefined) {
        throw new DeviceException(this.error.MISSING_ARG_ERR, "CommLog:deleteLogEntry:logId is missing");
    }
    
    if (typeof logId != "number") {
        throw new DeviceException(this.error.INVALID_ARG_ERR, "CommLog:deleteLogEntry:logId is invalid");
    }
    
    var criteria = {};
    modifyObjectBaseProp(criteria);
    criteria.Type = 'Log';
    criteria.Data = {
        id: logId.toString()
    };
    modifyObjectBaseProp(criteria.Data);
    
    var result = this.so.IDataSource.Delete(criteria);
    
    if (result.ErrorCode != 0) {
        var err_msg = "operation failed";
        if (result.ErrorMessage) {
            err_msg = splitErrorMessage(result.ErrorMessage);
        }
        
        throw new DeviceException(MapErrorCode[result.ErrorCode], "CommLog:deleteLogEntry:" + err_msg);
    }
}


function __sp_commlog_instance(){
    //alert("in instance");
    
    //Descriptor
    this.descriptor = new __sp_commlog_descriptor();
    
    //Extended methods
    this.getList = __sp_commlog_getList;
    this.getListCb = __sp_commlog_getList_cb;
    
    this.setNotification = __sp_commlog_setNotification;
	this.setNotificationCb = __sp_commlog_setNotification_cb;
    
    this.cancelNotification = __sp_commlog_cancelNotification;
    
    this.cancel = __sp_commlog_cancel;
    
    this.deleteLogEntry = __sp_commlog_deleteLogEntry;
    this.error = new DeviceException(0, "Dummy");
    //Private data
    
    try {
        //__device_debug("Trying commlog service");
        
        this.so = device.getServiceObject('Service.Logging', 'IDataSource');
        //__device_debug("Got commlog service object: ");    
    } 
    catch (e) {
        this.so = null;
        __device_handle_exception(e, "commlog service not available");
    }
}
