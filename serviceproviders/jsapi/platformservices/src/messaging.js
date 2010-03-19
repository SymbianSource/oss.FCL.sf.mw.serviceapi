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



function __device_messaging_descriptor(provider){
    this.interfaceName = provider.interfaceName;
    this.version = provider.version;
}



function __device_messaging_startEditor(message){

    return this.provider.startEditor(message);
}

function __device_messaging_getList(callback, match, sortkey, sortorder, ErrorCallback){
    return this.provider.getList(callback, match, sortkey, sortorder, ErrorCallback);
}

function __device_messaging_send(callback, message, id, ErrorCallback){
    return this.provider.send(callback, message, id, ErrorCallback);
}


function __device_messaging_setNotifier(callback, ErrorCallback){
    return this.provider.setNotifier(callback, ErrorCallback );
}

function __device_messaging_cancelNotifier(){
    return this.provider.cancelNotifier();
}

function __device_messaging_getMessage(id){
    return this.provider.getMessage(id);
}

function __device_messaging_delete(id){
    return this.provider.deleteMessage(id);
}

function __device_messaging_setStatus(id, status){
    return this.provider.setStatus(id, status);
}
function __device_messaging_cancel(transactionId){

    return this.provider.cancel(transactionId);
}

function __device_messaging(provider){
    //Private properties
    this.provider = provider;
    //Read-only properties
    this.interfaceName = provider.descriptor.interfaceName;
    this.version = provider.descriptor.version;
	//constants
	this.SORT_ASCENDING = 0;
    this.SORT_DESCENDING = 1;
    this.SORT_BY_DATE = 0;
    this.SORT_BY_SENDER = 1;
	this.STATUS_READ = 0;
	this.STATUS_UNREAD = 1;

    //Core methods
    this.startEditor = __device_messaging_startEditor;
    //Extended methods
    this.getList = __device_messaging_getList;
    this.send = __device_messaging_send;
    this.setNotifier = __device_messaging_setNotifier;
    this.cancelNotifier = __device_messaging_cancelNotifier;
    this.getMessage = __device_messaging_getMessage;
    this.deleteMessage = __device_messaging_delete;
    this.setStatus = __device_messaging_setStatus;
	this.cancel = __device_messaging_cancel;
}

// Namepace: com.nokia.device.service


var __device_messaging_service_entry = {
    "name": null,
    "version": null,
    "proto": __device_messaging,
    "descriptor": __device_messaging_descriptor,
    "providers": [{
        "descriptor": __sp_messaging_descriptor,
        "instance": __sp_messaging_instance
    }]
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
// S60 sp-based messaging provider
var FILE_SCHEME = 'file://';
//Constant values as per the CJSE Spec
//var INVALID_URI_ERR = 108;

/*
 * Global object for Async utility functions:
 * 1)addToGlobalArray
 * 2)getFromArray
 * 3)removeFromArray
 */

//var error = new DeviceError(0, 'dummy');
/*
 if(undefined == com.nokia.device.messaging)
 {
 com.nokia.device.messaging={};
 }
 nokia.device.messaging.SORT_ASCENDING = 0;
 nokia.device.messaging.SORT_DESCENDING = 1;
 nokia.device.messaging.SORT_BY_DATE = 0;
 nokia.device.messaging.SORT_BY_SENDER = 1;
 nokia.device.messaging.STATUS_READ = 0;
 nokia.device.messaging.STATUS_UNREAD = 1;*/
function __sp_messaging_descriptor(){
    //Read-only properties
    this.interfaceName = "messaging";
    if (window.__Service_Interface_Ver) 
        this.version = __Service_Interface_Ver;
    else 
        this.version = 1.0;
    //Class-static properties 
}

function __sp_messaging_instance(){

    
    //Descriptor
    this.descriptor = new __sp_messaging_descriptor();
    //Core methods
    this.startEditor = __sp_messaging_startEditor;
    //Extended methods
    this.getList = __sp_messaging_getList;
    this.getListcB = __sp_message_getListcB;
    
    this.send = __sp_messaging_send;
    this.sendcb = __sp_message_sendcb;
    
    this.setNotifier = __sp_messaging_setNotifier;
	this.setNotifierCb = __sp_messaging_setNotifier_cb;
	
    this.cancelNotifier = __sp_messaging_cancelNotifier;
    this.getMessage = __sp_messaging_getMessage;
    this.deleteMessage = __sp_messaging_delete;
    this.setStatus = __sp_messaging_setStatus;
    this.cancel = __sp_messaging_cancel;
    // Private data
    this.sendCommon = __sp_messaging_send_common;
    //Constant values as per the CJSE Spec
    this.SORT_ASCENDING = 0;
    this.SORT_DESCENDING = 1;
    this.SORT_BY_DATE = 0;
    this.SORT_BY_SENDER = 1;
    this.STATUS_READ = 0;
    this.STATUS_UNREAD = 1;
    this.error = new DeviceException(0, "Dummy");
    
    try {
        //__device_debug("Trying messaging service");
        this.so = device.getServiceObject("Service.Messaging", "IMessaging");
        //__device_debug("Got messaging service object");    
    } 
    catch (e) {
        this.so = null;
        __device_handle_exception(e, "Messaging service not available");
    }
}



function __sp_attachment_build(attachment){
    if (!attachment) {
        return null;
    }
    var sp_attachment = {};
    modifyObjectBaseProp(sp_attachment);
    if (attachment.uri) {
        if (typeof attachment.uri != "string") {
            throw new DeviceException(this.error.INVALID_ARG_ERR, "uri is invalid");
        }
        //device1.0: added this statement.. with out this the script will crib..also checking for proper URI
        if (attachment.uri.slice(0, 7) == FILE_SCHEME) {
            if (attachment.uri.charAt(7) == "/") {
                if (attachment.uri.charAt(9) != ":") {
                    throw new DeviceException(this.error.URI_NOT_FOUND_ERR, "specified uri not found");
                }
                sp_attachment.FileName = attachment.uri.slice(8).replace(/\057/g, "\\");
                if (sp_attachment.FileName.length > 256) {
                    throw new DeviceException(this.error.DATA_OUT_OF_RANGE_ERR, "uri is out of range");//map the errorcode to data_out_of_range
                }
            }
            
            else {
                if (attachment.uri.charAt(8) != ":") {
                    throw new DeviceException(this.error.URI_NOT_FOUND_ERR, "specified uri not found");
                }
                sp_attachment.FileName = attachment.uri.slice(7).replace(/\057/g, "\\");
                if (sp_attachment.FileName.length > 256) {
                    throw new DeviceException(this.error.DATA_OUT_OF_RANGE_ERR, "uri is out of range");//map the errorcode to data_out_of_range
                }
            }
        }
        else {
            throw new DeviceException(this.error.INVALID_URI_ERR, "uri is invalid")
        }
        
    }
    //alert("attachment" + sp_attachment.FileName);
    return sp_attachment;
}

function __sp_message_build(message, id){
    //a(id)
    //__device_debug("sp_message_build");
    if (!message) {
        return null;
    }
    var sp_message = {};
    modifyObjectBaseProp(sp_message);
    var attachFlag = 0;
    sp_message.MessageParam = {};
    modifyObjectBaseProp(sp_message.MessageParam);
    sp_message.MessageParam.LaunchEditor = false; //Defaults to no editor
    sp_message.MessageType = (message.type == undefined || message.type == null) ? "SMS" : message.type;
    //alert(message.to[0]+" "+message.type)
    if (message.to) {
        if (typeof(message.to) == "string") {
            sp_message.To = message.to;
        }
        else 
            if (__device_typeof(message.to) == "Array" && message.to.length > 0) {
                if (message.to[0]) {
                    sp_message.To = message.to[0];
                }
                
                
                if (message.to.length > 1) {
                    if (message.to.slice(1)) {
                        sp_message.MessageParam.To = message.to.slice(1);
                        
                    }
                }
            }
            else {
                sp_message.To = message.to;
            }
    }
    
    if (message.cc) {
        sp_message.MessageParam.Cc = message.cc;
    }
    
    if (id) {
        if ((typeof(id) == "string") && !(isNaN(id))) {
            id = Number(id);
        }
        sp_message.MessageParam.TemplateId = id;
    }
    if (sp_message.MessageType == "SMS") {
        if (message.body) {
            sp_message.BodyText = message.body;
        }
    }
    
    if (sp_message.MessageType == "MMS") {
        if (message.body) {
            //device1.0: Added body to MMS as it is a valid input to MMS type of message also
            sp_message.BodyText = message.body;
        }
        if (message.subject) {
            if (typeof message.subject == "string" && message.subject.length > 256) {
                throw new DeviceException(this.error.DATA_OUT_OF_RANGE_ERR, "subject length is greater than 256 characters");
            }
            sp_message.Subject = message.subject;
        }
        if (message.attachments) {
            sp_message.MessageParam.AttachmentList = [];
            for (var a in message.attachments) {
                //if (message.attachments.hasOwnProperty('a')) {
                if (typeof message.attachments[a] == "object" && __device_typeof(message.attachments[a]) != "Array") {
                    sp_message.MessageParam.AttachmentList.push(__sp_attachment_build(message.attachments[a]));
                    attachFlag = 1;
                }
                
                
                
                //}
            }
            if (attachFlag == 0) {
                throw new DeviceException(this.error.INVALID_ARG_ERR, "uri is invalid");
            }
        }
    }
    //   //alert("returning message____");
    return sp_message;
}

function __sp_device_attachment_build(sp_attachment){
    if (!sp_attachment) {
        return null;
    }
    var attachment = {};
    attachment.uri = FILE_SCHEME + sp_attachment.FileName;
    return attachment;
}

function __sp_device_message_build(sp_message){
    if (!sp_message) {
        return null;
    }
    //	//alert("am in message build");
    var message = {};
    message.body = null;
    message.subject = null;
    message.attachments = null;
    message.to = null;
    message.cc = null;
    
    message.type = sp_message.MessageType;
    if (sp_message.BodyText) {
        message.body = sp_message.BodyText;
    }
    if (sp_message.to) {
        message.to = sp_message.To;
        
    }
    if (sp_message.Subject) //device1.0: moved to here from MMS,for sms also subject is valid it will return the first 64 characters of the body as subject
    {
        message.subject = sp_message.Subject;
    }
    message.attachment = false;
    
    
    if (message.type == "MMS") {
        if (sp_message.Cc) {
            message.cc = sp_message.Cc;
        }
        if (sp_message.AttachmentList) {
            message.attachment = true;
            message.attachments = [];
            for (var a in sp_message.AttachmentList) {
                if (sp_message.AttachmentList.hasOwnProperty('a')) {
                    message.attachments.push(__sp_device_attachment_build(sp_message.AttachmentList[a]));
                }
            }
        }
    }
    //	//alert("returning message");
    return message;
}

function __sp_device_message_info_build_notifier(sp_message){
    if (!sp_message) {
        return null;
    }
    var message_info = {};
    message_info.message = {};
    message_info.message.type = sp_message.MessageType;
    message_info.sender = sp_message.Sender;
    message_info.message.subject = sp_message.Subject;
    message_info.time = sp_message.Time;
    message_info.attachments = (sp_message.Attachments == undefined || sp_message.Attachments == null) ? (!(sp_message.AttachmentList == undefined || sp_message.AttachmentList == null)) : sp_message.Attachments;
    message_info.unread = sp_message.Unread; //TBD: check existence
    message_info.id = (sp_message.MessageId).toString(); // TBD: check name of sp field
    return message_info;
}


function __sp_device_message_info_build(sp_message){
    //__device_debug("sp_device_message_info_build");
    if (!sp_message) {
        return null;
    }
    //	//alert("*******");
    var message_info = {};
    message_info.message = __sp_device_message_build(sp_message);
    message_info.sender = sp_message.Sender;
    message_info.time = sp_message.Time;
    message_info.unread = sp_message.Unread; //TBD: check existence
    message_info.id = (sp_message.MessageId).toString(); // TBD: check name of sp field
    return message_info;
}

// ------ Wrap sp iterator ------- 



function __sp_message_iterator_get_next(){
    //__device_debug("sp_message_iterator_get_next");
    //	//alert("in get_next");
    var sp_message = this.iter.getNext();
    if (typeof sp_message == "undefined") {
        //	//alert("returning null");
        return null;
    }
    //	//alert("iterator");
    var message = __sp_device_message_info_build(sp_message);
    sp_message.close();
    return message;
}

function __sp_message_iterator(js_iterator){
    this.iter = js_iterator;
    this.next = __sp_message_iterator_get_next;
    this.close = function(){
        this.iter.close();
    }
    
}


function __sp_message_getListcB(arg1, arg2, arg3){

    var success_cb;
    var error_cb;
    var CbObj;
    
    
    CbObj = glob_obj.getFromArray(arg1);
    
    
    
    if (CbObj) {
        success_cb = CbObj.success_cb;
        error_cb = CbObj.error_cb;
    }
    
    else {
        alert("Messaging: __sp_message_getListcB: Callback not found ");
		return;
    }
    
    
    var iter = null;
    
    if (arg3.ErrorCode != 0) {
        //alert('error '+error_cb);
        if (arg3.ErrorMessage) {
            err_msg = splitErrorMessage(arg3.ErrorMessage);
        }
        else {
            err_msg = "Operation Failed";
        }
        
        if (error_cb) {
            error_cb(new DeviceException(MapErrorCode[arg3.ErrorCode], "Messaging: getList: " + err_msg));
            return;
        }
    }
    else 
        if (arg3.ReturnValue) {
        
            iter = new __sp_message_iterator(arg3.ReturnValue);
        }

    if (arg2 != event_cancelled) // 3 signifies eventcancelled //device1.0: currently this check is not required here but might be in future if sp provides Async getlist
    {
        success_cb(iter);//device1.0: arg1 is the errorcode, arg2 is the transactionId and iter is the return value
    }
    glob_obj.removeFromArray(arg1);
}

function __sp_messaging_getList(msg_cb, match, sortkey, sortorder, ErrorCallback){

    //alert("in getlist");
    
    if (!msg_cb) {
        throw new DeviceException(this.error.MISSING_ARG_ERR, "Messaging:getList:callback is missing");
    }
    else 
        if (typeof msg_cb != "function") {
            throw new DeviceException(this.error.INVALID_ARG_ERR, "Messaging:getList:callback is not a function"); //BadArgumentType error
        }
    if (match != null && match != undefined && typeof match != "object") {
        //	a("match not object")
        throw new DeviceException(this.error.INVALID_ARG_ERR, "Messaging:getList:match is invalid"); //BadArgumentType error
    }
    
    if (sortkey != null && sortkey != undefined && typeof sortkey != "number") {
        throw new DeviceException(this.error.INVALID_ARG_ERR, "Messaging:getList:sortkey is invalid"); //BadArgumentType error
    }
    
    if (sortorder != null && sortorder != undefined && typeof sortorder != "number") {
        throw new DeviceException(this.error.INVALID_ARG_ERR, "Messaging:getList:sortorder is invalid"); //BadArgumentType error
    }
    
    if (sortkey != null && sortkey != undefined && typeof sortkey == "number") {
        if ((sortkey != 0) && (sortkey != 1)) 
            throw new DeviceException(this.error.INVALID_ARG_ERR, "Messaging:getList:sortkey is invalid"); //BadArgumentType error
    }
    
    if (sortorder != null && sortorder != undefined && typeof sortorder == "number") {
        //	a(sortorder+" "+typeof sortorder)
        if ((sortorder != 0) && (sortorder != 1)) 
            throw new DeviceException(this.error.INVALID_ARG_ERR, "Messaging:getList:sortorder is invalid"); //BadArgumentType error
    }
    
    if (ErrorCallback) {
        if (typeof(ErrorCallback) != 'function') {
            throw new DeviceException(this.error.INVALID_ARG_ERR, "Messaging: startEditor: ErrorCallback is invalid");
        }
    }
    
    
    var criteria = {};
    modifyObjectBaseProp(criteria);
    criteria.Type = "Inbox";
    criteria.Filter = {};
    modifyObjectBaseProp(criteria.Filter);
    
    
    if (match) {
        //	a("in match");
        if (match.type != null && match.type != undefined) {
            //	a("match.type" + match.type);
            criteria.Filter.MessageTypeList = match.type;
        }
        if (match.senders != null && match.senders != undefined) {
            criteria.Filter.SenderList = match.senders;
        }
        if (match.subject != null && match.subject != undefined) {
            if (match.subject.length > 256) {
                if (ErrorCallback) {
                    ErrorCallback(new DeviceException(this.error.DATA_OUT_OF_RANGE_ERR, "Messaging:getList:subject is out of range"));
                    return;
                }
                else {
                    throw new DeviceException(this.error.DATA_OUT_OF_RANGE_ERR, "Messaging:getList:subject is out of range");
                }
            }
            else {
                criteria.Filter.Subject = match.subject;
            }
        }
        if (match.start != null && match.start != undefined) {
            criteria.Filter.StartDate = match.start;
        }
        if (match.end != null && match.end != undefined) {
            criteria.Filter.EndDate = match.end;
        }
    }
    
    if (sortkey || sortorder) {
        //	a("in sortkey");
        criteria.SortOrder = {};
        modifyObjectBaseProp(criteria.SortOrder);
        if (sortkey) {
            if ((sortkey == this.SORT_BY_DATE)) {
                criteria.SortOrder.Key = "Date";
            }
            else 
                if ((sortkey == this.SORT_BY_SENDER)) {
                    criteria.SortOrder.Key = "Sender";
                }
        }
        else {
            criteria.SortOrder.Key = "Date";
        }
        if (sortorder) {
        
            if ((sortorder == this.SORT_ASCENDING)) {
                criteria.SortOrder.Order = "Ascending";
            }
            else 
                if ((sortorder == this.SORT_DESCENDING)) {
                    criteria.SortOrder.Order = "Descending";
                }
        }
        else {
            criteria.SortOrder.Order = "Ascending";
        }
    }
    
    try {
        //__device_debug("Getting message list");
	    temp_scb = msg_cb;
		temp_ecb = ErrorCallback;
        var result = this.so.IMessaging.GetList(criteria, this.getListcB);
        if (result.TransactionID) {
            glob_obj.addToGlobalArray(result.TransactionID, msg_cb, ErrorCallback);
        }
        
        if (criteria) {
            delete criteria.Filter;
            delete criteria.SortOrder;
            delete criteria.Type;
        }
        if (result.ErrorCode != 0)//device1.0:Modified to throw exceptions
        {
        
            var err_msg = "operation failed";
            if (result.ErrorMessage) {
                err_msg = splitErrorMessage(result.ErrorMessage);
            }
            switch (MapErrorCode[result.ErrorCode]) {
                case this.error.INVALID_ARG_ERR:
                case this.error.MISSING_ARG_ERR:
                case this.error.NOT_SUPPORTED_ERR:
                    throw new DeviceException(MapErrorCode[result.ErrorCode], "Messaging:getList:" + err_msg);
                    break;
                    
                default:
                    if (ErrorCallback) {
                        setTimeout(function(){
                            ErrorCallback(new DeviceException(MapErrorCode[result.ErrorCode], "Messaging:getList:" + err_msg));
                        }, 500);
                    }
                    else {
                        throw new DeviceException(MapErrorCode[result.ErrorCode], "Messaging:getList:" + err_msg);
                    }
                    
            }
        }
        
        return result.TransactionID;
    } 
    catch (e) {
        __device_handle_exception(e, '__sp_messaging_getList: ' + e);
    }
}

function __sp_message_sendcb(arg1, arg2, arg3){
	var send_cb;
	var eCB;
    var CbObj = glob_obj.getFromArray(arg1);
    
    if (CbObj) {
        send_cb = CbObj.success_cb;
        eCB = CbObj.error_cb;
    }
    
	else
	{
		alert('Messaging : __sp_message_sendcb : Callback not found');
		return;
	}
    if (send_cb) {
        var err_msg = "operation failed";

        if (arg3.ErrorCode != 0) {
        
            if (arg3.ErrorMessage) {
                err_msg = splitErrorMessage(arg3.ErrorMessage);
            }
            if (eCB) {
                //alert("am in ecb");
                setTimeout(function(){
                    eCB(new DeviceException(MapErrorCode[arg3.ErrorCode], "Messaging: send: " + err_msg));
                }, 500);
                return;
            }
        }
        if (arg2 != event_cancelled) // 3 signifies eventcancelled 
        {
            send_cb();//device1.0: arg1 is the transaction id, arg3 is the return value which holds the errorcode
        }
    }
    glob_obj.removeFromArray(arg1);
}

function __sp_messaging_send_common(message, editor, send_cb, id, eCB){

    //__device_debug("sp_messaging_send_common");
    var criteria = __sp_message_build(message, id);
    criteria.MessageParam.LaunchEditor = editor;
    
    var result;
    //	//alert("before editor");
    if (editor == false) //device1.0:making it async only in case of send api, as it doesnot invoke editor, returning the output accordingly
    {
    	temp_scb = send_cb;
		temp_ecb = eCB;
        result = this.so.IMessaging.Send(criteria, this.sendcb);
        if (result.TransactionID) {
            glob_obj.addToGlobalArray(result.TransactionID, send_cb, eCB);
        }
        
        //alert("ErrorCode" + (result.ErrorCode));
        if (result.ErrorCode != 0)//device1.0:Modified to throw exceptions
        {
            var err_msg = "operation failed";
            if (result.ErrorMessage) {
                err_msg = splitErrorMessage(result.ErrorMessage);
            }
            //alert("before switch");
            switch (MapErrorCode[result.ErrorCode]) {
                case this.error.INVALID_ARG_ERR:
                case this.error.MISSING_ARG_ERR:
                case this.error.NOT_SUPPORTED_ERR:
                    //alert("INVALID");
                    throw new DeviceException(MapErrorCode[result.ErrorCode], err_msg);
                    break;
                    
                default:
                    //   a("in default");
                    if (eCB) {
                        //		a("calling eCB");
                        setTimeout(function(){
                            eCB(new DeviceException(MapErrorCode[result.ErrorCode], err_msg));
                        }, 500);
                        //	a("after eCB" + result.TransactionID);
                        return;
                    }
                    else {
                        //				a("else");
                        throw new DeviceException(MapErrorCode[result.ErrorCode], err_msg);
                    }
                    
            }
        }
        
        var transactionID = result.TransactionID;
        //		a("transactionID" + transactionID);
        return transactionID;
    }
    else {
        //		a("am coming here");
        result = this.so.IMessaging.Send(criteria);
        //		a("result.ErrorCode" + result.ErrorCode);
        if (result.ErrorCode != 0)//device1.0:Modified to throw exceptions
        {
            if (result.ErrorMessage) {
                var err_msg1 = splitErrorMessage(result.ErrorMessage);
                throw new DeviceException(MapErrorCode[result.ErrorCode], "Messaging:startEditor" + err_msg1);
            }
            else {
                throw new DeviceException(MapErrorCode[result.ErrorCode], "Messaging:startEditor:operation failed");
            }
        }
    }
    if (criteria) {
        delete criteria.MessageParam;
    }
    
}


function __sp_messaging_startEditor(message){
    //a("starteditor");
    if (!message) {
        //	a("starteditor1");
        throw new DeviceException(this.error.MISSING_ARG_ERR, "Messaging:startEditor:message is missing");//SErrMissingArgument = 1003      
    }
    else 
        if (typeof message != "object") {
            //	a("starteditor2");
            throw new DeviceException(this.error.INVALID_ARG_ERR, "Messaging:startEditor:message is invalid"); //BadArgumentType error
        }
    //__device_debug("sp_messaging_startEditor");
    if ((message.subject)) {
        if ((message.subject).length > 256) {
            //	a("starteditor3");
            throw new DeviceException(this.error.DATA_OUT_OF_RANGE_ERR, "Messaging:startEditor:subject is too lengthy");//SErrMissingArgument = 1003
        }
    }
    
    if (message.attachments != undefined && message.attachments != null && typeof message.attachments != "object") {
        //		a("INVALID_ARG_ERR");
        throw new DeviceException(this.error.INVALID_ARG_ERR, "Messaging:startEditor:attachment is invalid");//SErrMissingArgument = 1003
    }
    if (message) {
        if (message.body) {
            if (typeof(message.body) != "string") {
                throw new DeviceException(this.error.INVALID_ARG_ERR, "Messaging:startEditor:body is invalid");
            }
        }
    }
    try {
        //	a("before sendcommon");
        this.sendCommon(message, true, null);
    } 
    catch (e) {
        //	a("starteditor catch");
        var error = null;
        if (e.message) {
        
            error = new DeviceException(e.code, "Messaging:startEditor:" + e.message);
        }
        else {
            error = new DeviceException(e.code, "Messaging:startEditor:operation failed");
        }
        __device_handle_exception(error, '__sp_messaging_startEditor: ' + error);
    }
}

function __sp_messaging_send(msg_cb, message, id, ErrorCallback){

    //	a("send!!!!!!!" + ErrorCallback);
    if (!message) {
        throw new DeviceException(this.error.MISSING_ARG_ERR, "Messaging:send:message is missing");//SErrMissingArgument = 1003      
    }
    else 
        if (typeof message != "object") {
            throw new DeviceException(this.error.INVALID_ARG_ERR, "Messaging:send:message is invalid"); //BadArgumentType error
        }
    if (!msg_cb) {
        throw new DeviceException(this.error.MISSING_ARG_ERR, "Messaging:send:callback is missing");//SErrMissingArgument = 1003  
    }
    else 
        if (typeof msg_cb != "function") {
            throw new DeviceException(this.error.INVALID_ARG_ERR, "Messaging:send:callback is invalid"); //BadArgumentType error
        }
    
    
    if (message.to == undefined || message.to == null) {
        throw new DeviceException(this.error.MISSING_ARG_ERR, "Messaging:send:to field is missing");//SErrMissingArgument = 1003
    }
    
    
    if (message.attachments != undefined && message.attachments != null && typeof message.attachments != "object") {
        throw new DeviceException(this.error.INVALID_ARG_ERR, "Messaging:send:attachment is invalid");//SErrMissingArgument = 1003
    }
    
    if (!id) {
        id = "";
    }
    /*  if (id) {
     if (((typeof id) != "function") && ((typeof id) != "string") && ((typeof id) != "number")) {
     throw new DeviceException(INVALID_ARG_ERR, 'Messaging:send:id is not a string');
     }*/
    if ((typeof id) == "function") {
        var errorCbk = id;
        id = "";
        ErrorCallback = errorCbk;
    }
    
    if ((typeof ErrorCallback) == "undefined" || ErrorCallback == null) {
        ErrorCallback = null;
    }
    else 
        if ((typeof ErrorCallback) != "function") {
            throw new DeviceException(this.error.INVALID_ARG_ERR, 'Messaging:send:errorCallback is not a function');
        }
    
    var invoker = function(arg1, arg2, arg3){
        var success_cb = msg_cb;
        var error_cb = ErrorCallback;
        var iter = null;
        if (arg3.ErrorCode != 0) {
            var err_msg;
            if (arg3.ErrorMessage) 
                err_msg = splitErrorMessage(arg3.ErrorMessage);
            else 
                err_msg = "Operation Failed";
            
            error_cb(new DeviceException(MapErrorCode[arg3.ErrorCode], "Messaging:startEditor: " + err_msg));
            return;
        }
        else 
            if (arg3.ReturnValue) {
                iter = new __sp_message_iterator(arg3.ReturnValue);
                success_cb(iter);
            }
        if (arg2 != event_cancelled) // 3 signifies eventcancelled //device1.0: currently this check is not required here but might be in future if sp provides Async getlist
        {
            success_cb(iter);//device1.0: arg1 is the errorcode, arg2 is the transactionId and iter is the return value
        }
    };
    
    try {
        //	//alert("before sendCommon");
        //	a("ErrorCallback" + ErrorCallback);
        var transactionID = this.sendCommon(message, false, msg_cb, id, ErrorCallback);
        //	a("transactionID" + transactionID);
        return transactionID;
    } 
    catch (e) {
        //a("e.message" + e.message);
        var error = null;
        switch (e.code) {
            case this.error.INVALID_ARG_ERR:
            case this.error.MISSING_ARG_ERR:
            case this.error.NOT_SUPPORTED_ERR:
                throw new DeviceException(e.code, "Messaging:send:" + e.message);
                break;
                
            default:
                if (ErrorCallback) {
                    setTimeout(function(){
                        ErrorCallback(new DeviceException(e.code, "Messaging:send:" + e.message));
                    }, 1000);
                }
                else {
                    throw new DeviceException(e.code, "Messaging:send:" + e.message);
                }
                
        }
    }
}

function __sp_messaging_setNotifier_cb(arg1, arg2, arg3){
    var success_cb;
    var error_cb;
    var msginfo = null;
    var err_msg = null;
    
    var CbObj;
    
    
    CbObj = glob_obj.getFromArray(arg1);
    
    
    if (CbObj) {
        success_cb = CbObj.success_cb;
        error_cb = CbObj.error_cb;
    }
    
    else {
        alert("Messaging: __sp_messaging_setNotifier_cb : Callback not found ");
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
            error_cb(new DeviceException(MapErrorCode[arg3.ErrorCode], "Messaging:setNotifier: " + err_msg));
            return;
        }
    }
    else 
        if (arg3.ReturnValue) {
            msginfo = new __sp_device_message_info_build_notifier(arg3.ReturnValue);//LAT BUG
            arg3.ReturnValue.close();
        }
    if (arg2 != event_cancelled) // 3 signifies eventcancelled
    {
        success_cb(msginfo.id);//msginfo.id)//device1.0: returning the errorcode,
    }
    glob_obj.removeFromArray(arg1);
}

function __sp_messaging_setNotifier(msg_cb, ErrorCallback){

    if (!msg_cb) {
        throw new DeviceException(this.error.MISSING_ARG_ERR, "Messaging:setNotifier:callback is missing");//SErrMissingArgument = 1003  
    }
    else 
        if (typeof msg_cb != "function") {
            throw new DeviceException(this.error.INVALID_ARG_ERR, "Messaging:setNotifier:callback is invalid"); //BadArgumentType error
        }
    
    
    
    if (ErrorCallback) {
        if (typeof(ErrorCallback) != 'function') {
            throw new DeviceException(this.error.INVALID_ARG_ERR, "Messaging:setNotifier: ErrorCallback is invalid");
        }
    }
    
    
    
    
    var criteria = {};
    modifyObjectBaseProp(criteria);
    criteria.Type = 'NewMessage';
    
    try {
		temp_scb = msg_cb;
		temp_ecb = ErrorCallback;
        var result = this.so.IMessaging.RegisterNotification(criteria, this.setNotifierCb);
        
        if (result.TransactionID) {
            glob_obj.addToGlobalArray(result.TransactionID, msg_cb, ErrorCallback);
        }
        
        if (criteria) {
            delete criteria.Type;
        }
        if (result.ErrorCode != 0)//device1.0:Modified to throw exceptions
        {
        
            var err_msg = "operation failed";
            if (result.ErrorMessage) {
                err_msg = splitErrorMessage(result.ErrorMessage);
            }
            switch (MapErrorCode[result.ErrorCode]) {
                case this.error.INVALID_ARG_ERR:
                case this.error.MISSING_ARG_ERR:
                case this.error.NOT_SUPPORTED_ERR:
                    throw new DeviceException(MapErrorCode[result.ErrorCode], "Messaging:setNotifier:" + err_msg);
                    break;
                    
                default:
                    if (ErrorCallback) {
                        setTimeout(function(){
                            ErrorCallback(new DeviceException(MapErrorCode[result.ErrorCode], "Messaging:setNotifier:" + err_msg));
                        }, 1000);
                    }
                    else {
                        throw new DeviceException(MapErrorCode[result.ErrorCode], "Messaging:setNotifier:" + err_msg);
                    }
                    
            }
        }
        var transactionID = result.TransactionID;
        return transactionID;
    } 
    catch (e) {
        __device_handle_exception(e, '__sp_messaging_setNotifier: ' + e.toString());
    }
}

function __sp_messaging_cancelNotifier(){
    var criteria = {};
    modifyObjectBaseProp(criteria);
    criteria.Type = "NewMessage";
    
    try {
        var result = this.so.IMessaging.CancelNotification(criteria);
        if (criteria) {
            delete criteria.Type;
        }
        //alert("result.ErrorCode" + result.ErrorCode);
        if (result.ErrorCode != 0)//device1.0:Modified to throw exceptions
        {
            if (result.ErrorMessage) {
                var err_msg = splitErrorMessage(result.ErrorMessage);
                throw new DeviceException(MapErrorCode[result.ErrorCode], "Messaging:cancelNotifier" + err_msg);
            }
            else {
                throw new DeviceException(MapErrorCode[result.ErrorCode], "Messaging:cancelNotifier:operation failed");
            }
        }
    } 
    catch (e) {
        __device_handle_exception(e, '__sp_messaging_cancelNotifier: ' + e);
    }
}

function __sp_messaging_getMessage(id){

    if (!id) {
        throw new DeviceException(this.error.MISSING_ARG_ERR, "Messaging:getMessage:id is missing");//SErrMissingArgument = 1003  
    }
    else 
        if ((typeof id) != "string") 
            throw new DeviceException(this.error.INVALID_ARG_ERR, "Messaging:getMessage:MessageId should be a string");
    if ((typeof id == "string") && !(isNaN(id))) {
        id = Number(id);
        if (id == 0) {
            throw new DeviceException(this.error.DATA_NOT_FOUND_ERR, "Messaging:getMessage:id not found");
        }
        if (id < 0) {
            throw new DeviceException(this.error.DATA_OUT_OF_RANGE_ERR, "Messaging:getMessage:id is out of range");
        }
    }
    
    var criteria = {};
    modifyObjectBaseProp(criteria);
    criteria.Type = "Inbox";
    criteria.Filter = {};
    modifyObjectBaseProp(criteria.Filter);
    criteria.Filter.MessageId = id;
    
    try {
        var result = this.so.IMessaging.GetList(criteria);
        
        if (criteria) {
            delete criteria.Filter;
            delete criteria.Type;
        }
        //	a("result.ErrorCode" + result.ErrorCode);
        if (result.ErrorCode != 0)//device1.0:Modified to throw exceptions
        {
            //		a("result.ErrorCode" + result.ErrorCode);
            if (result.ErrorMessage) {
                //			a("result.ErrorMessage");
                var err_msg = splitErrorMessage(result.ErrorMessage);
                throw new DeviceException(MapErrorCode[result.ErrorCode], "Messaging:getMessage" + err_msg);
            }
            else {
                throw new DeviceException(MapErrorCode[result.ErrorCode], "Messaging:getMessage:operation failed");
            }
        }
        if (result.ReturnValue) {
            //		a("result.ReturnValue" + result.ReturnValue);
            var iter = new __sp_message_iterator(result.ReturnValue);//LAT BUG
            var result1 = iter.next();
            if (result1) {
                //		a("result1");
                return result1;
            }
            else {
                //		a("DATA_NOT_FOUND_ERR");
                throw new DeviceException(this.error.DATA_NOT_FOUND_ERR, "Messaging:getMessage:id not found");//sapi doesnot return errorcode for non-existent id
            }
            
        }
    } 
    catch (e) {
        __device_handle_exception(e, '__sp_messaging_getMessage: ' + e);
    }
}

function __sp_messaging_delete(id){
    a("messageId" + typeof id);
    if (!id) {
        throw new DeviceException(this.error.MISSING_ARG_ERR, "Messaging:delete:id is missing");//SErrMissingArgument = 1003  
    }
    else 
        if ((typeof id) != "string") 
            throw new DeviceException(this.error.INVALID_ARG_ERR, "Messaging:deleteMessage:MessageId should be a string");
    
    if ((typeof id == "string") && !(isNaN(id))) {
        id = Number(id);
        if (id == 0) {
            throw new DeviceException(this.error.DATA_NOT_FOUND_ERR, "Messaging:delete:id not found");
        }
        if (id < 0) {
            throw new DeviceException(this.error.DATA_OUT_OF_RANGE_ERR, "Messaging:delete:id is out of range");
        }
    }
    
    var criteria = {};
    modifyObjectBaseProp(criteria);
    criteria.MessageId = id;
    
    try {
        //		a("criteria.MessageId" + criteria.MessageId);
        var result = this.so.IMessaging.Delete(criteria);
        a("MapErrorCode[ result.ErrorCode ]" + MapErrorCode[result.ErrorCode]);
        if (criteria) {
            delete criteria.MessageId;
        }
        //		a("result.ErrorCode" + result.ErrorCode);
        if (result.ErrorCode != 0)//device1.0:Modified to throw exceptions
        {
            if (result.ErrorMessage) {
                //				a("result.ErrorMessage");
                var err_msg = splitErrorMessage(result.ErrorMessage);
                throw new DeviceException(MapErrorCode[result.ErrorCode], "Messaging:delete" + err_msg);
            }
            else {
                throw new DeviceException(MapErrorCode[result.ErrorCode], "Messaging:delete:operation failed");
            }
        }
    } 
    catch (e) {
        __device_handle_exception(e, '__sp_messaging_delete: ' + e);
    }
}

function __sp_messaging_setStatus(id, status){

    if (id == null || id == undefined || (id.length) <= 0) {
        throw new DeviceException(this.error.MISSING_ARG_ERR, "Messaging:setStatus:id is missing");//SErrMissingArgument = 1003  
    }
    //a("id.length" + id.length);
    if ((typeof id) != "string") {
        throw new DeviceException(this.error.INVALID_ARG_ERR, "Messaging:setStatus:id should be string");//SErrMissingArgument = 1003  
    }
    
    if (status == null || status == undefined) {
        throw new DeviceException(this.error.MISSING_ARG_ERR, "Messaging:setStatus:status is missing");//SErrMissingArgument = 1003 
    }
    
    if (typeof status != "number") {
        throw new DeviceException(this.error.INVALID_ARG_ERR, "Messaging:setStatus:status is invalid"); //BadArgumentType error
    }
    
    if (typeof status == "number" && status != 0 && status != 1) {
        throw new DeviceException(this.error.INVALID_ARG_ERR, "Messaging:setStatus:status is invalid"); //BadArgumentType error
    }
    
    if ((typeof id == "string") && !(isNaN(id))) {
        id = Number(id);
        if (id == 0) {
            throw new DeviceException(this.error.DATA_NOT_FOUND_ERR, "Messaging:setStatus:id not found");
        }
        if (id < 0) {
            throw new DeviceException(this.error.DATA_OUT_OF_RANGE_ERR, "Messaging:setStatus:id is out of range");
        }
    }
    
    var criteria = {};
    modifyObjectBaseProp(criteria);
    criteria.MessageId = id;
    if ((status == this.STATUS_UNREAD)) {
        criteria.Status = "Unread";
    }
    else 
        if ((status == this.STATUS_READ)) {
            a("in read")
            criteria.Status = "Read";
        }
    try {
        var result = this.so.IMessaging.ChangeStatus(criteria);
        if (criteria) {
            delete criteria.MessageId;
            delete criteria.Status;
        }
        //		a("result.ErrorCode" + result.ErrorCode);
        if (result.ErrorCode != 0)//device1.0:Modified to throw exceptions
        {
            //a("error code is non-zero")
            if (result.ErrorMessage) {
                var err_msg = splitErrorMessage(result.ErrorMessage);
                throw new DeviceException(MapErrorCode[result.ErrorCode], "Messaging:setStatus" + err_msg);
            }
            else {
                throw new DeviceException(MapErrorCode[result.ErrorCode], "Messaging:setStatus:operation failed");
            }
        }
    } 
    catch (e) {
        __device_handle_exception(e, '__sp_messaging_setStatus: ' + e);
    }
}

function __sp_messaging_cancel(transactionId){

    if (transactionId == null || transactionId == undefined) {
        throw new DeviceException(this.error.MISSING_ARG_ERR, "Messaging:setStatus:id is missing");//SErrMissingArgument = 1003  
    }
    
    if (typeof transactionId != "number") {
        throw new DeviceException(this.error.INVALID_ARG_ERR, "Messaging:cancel:id is invalid");//SErrMissingArgument = 1003  
    }
    var criteria = {};
    modifyObjectBaseProp(criteria);
    criteria.TransactionID = transactionId;
    //   a("in cancel");
    try {
        var result = this.so.IMessaging.Cancel(criteria);
        if (criteria) {
            delete criteria.TransactionID;
        }
        //alert("result.ErrorCode" + result.ErrorCode);
        if (result.ErrorCode != 0)//device1.0:Modified to throw exceptions
        {
            var err;
            if (result.ErrorCode == 1000) {
                err = this.error.DATA_NOT_FOUND_ERR;
            }
            else {
                err = MapErrorCode[result.ErrorCode];
            }
            if (result.ErrorMessage) {
                var err_msg = splitErrorMessage(result.ErrorMessage);
                throw new DeviceException(err, "Messaging:cancel" + err_msg);
            }
            else {
                throw new DeviceException(err, "Messaging:cancel:operation failed");
            }
        }
    } 
    catch (e) {
        __device_handle_exception(e, '__sp_messaging_setStatus: ' + e);
    }
}
