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


var __device_debug_on__ = true;

var event_completed = 2;
var event_cancelled = 3;

var __Service_Interface_Ver=1.0;


var MapErrorCode = {1016:100,1012:101,1010:102,1009:103,1005:104,1000:105,1011:106,1007:107,1003:1,1002:2, 1004:3};

function __device_debug(text){
  //if(__device_debug_on__) alert(text);
}

function __device_handle_exception(e, text){
	__device_debug(text);
	throw(e);
}

function __device_typeof(value)
{
	// First check to see if the value is undefined.
	if (value == undefined) {
        return "undefined";
    }
	// Check for objects created with the "new" keyword.
	if (value instanceof Object) {
		// Check whether it's a string object.
		if (value instanceof String) {
			return "String";
		}
		// Check whether it's an array object/array literal.
		else 
			if (value instanceof Array) {
				return "Array";
			}
	}
	// dealing with a literal.
		if (typeof value) {
			if (typeof value == "object") {
				if (typeof value == "object" && !value) {
					return "null";
				}
			}
           // if not null check for other types
			
				// Check if it's a string literal.
			else if (typeof value == "string") {
					return "string";
				}
		}	 
}

if ((typeof nokia) == 'undefined') {
	nokia = {};
	nokia.device = {};
}
else {
    if ((typeof nokia.device) != 'undefined') {
		nokia.device = {};
    }
	else{
		throw ("nokia.device already defined");
	} 
}

nokia.device = {
    load: __device_service_load,
    listInterfaces: __device_service_interfaces,
	getSystemProperties: __device_getSystemProperties,
	getLibraryVersion: __device_getLibraryVersion,
    version: 2.0
};

function __device_getLibraryVersion(){
	return 2.0;
}

function __device_getSystemProperties(){
	return {
		uriPath:{
			// maximum limitation is 255 charectors
			max:255
		}
	};
}
// Configure the services offered.

var __device_services_inited = false;

var __device_services = [

  // For now, the only service is the base "device"" service
  {
    "name":"device",
    "version": 2.0, 
    "interfaces": []
  }
];

// Initialize the configured services.

function __device_services_init(){
  if(__device_services_inited){
    return;
  }
  __device_services_inited = true;
  
  try {
  	var so_SrvReg = device.getServiceObject("Service.ServiceRegistry", "IService");
	var filter = {ServiceName:"Service.Calendar", InterfaceName:"IDataSource"};  
	
	var returnVal = so_SrvReg.IService.GetList(filter);
		if (returnVal.ErrorCode == 0)	{
			var intf_iterator = returnVal.ReturnValue;
			if(intf_iterator)	{
				var intf = intf_iterator.getNext();
				if(intf){
					var versionList = intf.VersionList;
					var index;
					for(index in versionList){
						if(versionList[index] > __Service_Interface_Ver){						
							__Service_Interface_Ver = versionList[index];
						}
					}
				}
			}
			intf_iterator.close();
		}
	so_SrvReg.close();
  }catch(e){
  	// service registry not available default version to 1.0
//	alert('in catch'+e);
	__Service_Interface_Ver = 1.0;
  }
	
 

  // Get the service-specific service entries. Note that these
  // need to be individually wrapped by try/catch blocks so that the
  // interpreter gracefully handles missing services. 

  try {
    __device_services[0].interfaces.push(__device_geolocation_service_entry);
  }catch (e){
    __device_debug("Missing library implementation: " + e);
  }
  try {
    __device_services[0].interfaces.push(__device_camera_service_entry);
  }catch (e1){
    __device_debug("Missing library implementation: " + e1);
  }
  try {
    __device_services[0].interfaces.push(__device_media_service_entry);
  }catch (e2){
//    __device_debug("Missing library implementation: " + e2);
  }
  try {
    __device_services[0].interfaces.push(__device_contacts_service_entry);
  }catch (e3){
//    __device_debug("Missing library implementation: " + e3);
  }
 try {
    __device_services[0].interfaces.push(__device_messaging_service_entry);
  }catch (e4){
      __device_debug("Missing library implementation: " + e4);
  }
  try {
    __device_services[0].interfaces.push(__device_calendar_service_entry);
  }catch (e5){
      __device_debug("Missing library implementation: " + e5);
  }
  try {
    __device_services[0].interfaces.push(__device_landmarks_service_entry);
  }catch (e6){
      __device_debug("Missing library implementation: " + e6);
  }
  try {
    __device_services[0].interfaces.push(__device_commlog_service_entry);
  }catch (e7){
      __device_debug("Missing library implementation: " + e7);
  }
  try {
    __device_services[0].interfaces.push(__device_sysinfo_service_entry);
  }catch (e8){
      __device_debug("Missing library implementation: " + e8);
  }
  try {
    __device_services[0].interfaces.push(__device_sensors_service_entry);
  }catch (e9){
      __device_debug("Missing library implementation: " + e9);
  }

}

function __device_get_implementation(i){
  //__device_debug("get_implementation: " + i);
  return  new i.proto(new(i.providers[0].instance));
}

function __device_get_descriptor(i){
  //__device_debug("get_descriptor: " + i);
  return new i.descriptor(new(i.providers[0].descriptor));
}

function __device_get_interface(s, interfaceName, version){

    // Find first match of name and version
    var i = s.interfaces;
	for (var d in i){
		if(i[d].name == null){
		  __device_update_descriptor(i[d]);
		}
		
		if(i[d].name == undefined){
		  continue;
		}
		
		if (i[d].name == interfaceName){
		// Match version if specified
			if (version) {
				if (i[d].version >= version) {
					return __device_get_implementation(i[d]);
				}
			}else{
				return __device_get_implementation(i[d]);
			}
	    }
	}
	return null;
}

// Implemention of the load method

function __device_service_load(interfaceName, version){
    var error = new DeviceException('dummy',0);
	if(interfaceName){
        if(typeof interfaceName != 'string'){
            throw new DeviceException(error.INVALID_ARG_ERR, 'nokia.device.load:Invalid type interfaceName');
        }
    }else{
        throw new DeviceException(error.MISSING_ARG_ERR, 'nokia.device.load:interfaceName param expected');
    }
    if(version){
        if(typeof version != 'number'){
            throw new DeviceException(error.INVALID_ARG_ERR, 'nokia.device.load:Invalid type version');
        }
    }

    __device_services_init();
  
	for(var s in __device_services){
	  //__device_debug("service_load: " + s + ":" +  __device_services[s].name + ": " + interfaceName);
	  var i = __device_get_interface(__device_services[s], interfaceName, version);
	  if (i != null){
	    return i;
	  }
	}
    return null;
}

// Lazily fill in the descriptor table

function __device_update_descriptor(i){
  var d = __device_get_descriptor(i);
  i.name = d.interfaceName;
  i.version = d.version;  
}
// Get an array of interface descriptors for a service

function __device_interface_list(s){
  var retval = new Array();
  for(var i in s.interfaces){
    if(s.interfaces[i].name == null){
      __device_update_descriptor(s.interfaces[i]);
    }
    if(s.interfaces[i].name == undefined){
      continue;
    }
    retval[i] = new Object();
    retval[i].name = s.interfaces[i].name;
    retval[i].version = s.interfaces[i].version;
  }  
  return retval;
}

// Get a service description

function __device_service_descriptor(s){
  this.name = s.name;
  this.version = s.version;
  this.interfaces = __device_interface_list(s);
  this.toString = __device_service_descriptor_to_string;
}

function __device_service_descriptor_to_string(){
  var is = "\nInterfaces(s): ";

  for (i in this.interfaces){
    is += "\n" + this.interfaces[i].name + " " + this.interfaces[0].version;
  }
  return ("Service: " + this.name + is);
}

// Implement the listInterfaces method
    
function __device_service_interfaces(){
  __device_services_init();

  for (var s in __device_services){
      var intfs = __device_interface_list(__device_services[s]);
	  // create interator
	  return new __FWIter(intfs);
  }
  return null;
}


function __FWIter(arr)
{
    this._arr = arr;
	this._pos = 0;
	this._valid = true;
}

__FWIter.prototype.hasNext = function() {
    return (this._valid && this._pos < this._arr.length);
}

__FWIter.prototype.next = function() {
    if(this._valid && (this._pos < this._arr.length)){
		return this._arr[this._pos++];
	}
	else{
		return null;
	}
}

__FWIter.prototype.close = function(){
    delete this._arr;
	this._valid = false;
}

function modifyObjectBaseProp(obj){
  for (pro in obj) {
    if(typeof obj[pro] == "function" )
      obj[pro] = 0;
    }
}

//TBD: Get rid of this global, use closures instead
//Functions for  Handling Async API's use this variable
var glob_obj = null;
var temp_scb = null;
var temp_ecb = null;
 
glob_obj = new Object();

glob_obj.glob_cb_arr = new Array();
glob_obj.addToGlobalArray = addToGlobalArray;
glob_obj.removeFromArray = removeFromArray;
glob_obj.getFromArray = getFromArray;
     
DeviceAPIError.prototype = new Error(); //inheritance occurs here
DeviceAPIError.prototype.constructor = DeviceAPIError; //If this not present then, it uses default constructor of Error

//constructor for DeviceAPIError.
function DeviceAPIError(code,message) 
{
	this.toString = concatenate;
	this.code = code;
	this.name = "DeviceError";//we can even overwrite default name "Error"
	this.message=message; 
	
        this.MISSING_ARG_ERR            = 1;
        this.INVALID_ARG_ERR            = 2;
        this.NOT_SUPPORTED_ERR          = 3;
        this.TIMEOUT_ERR                = 100;
        this.DATA_NOT_FOUND_ERR         = 101;
        this.DATA_ALREADY_EXISTS_ERR    = 102;
        this.SERVICE_BUSY_ERR           = 103;
        this.SERVICE_IN_USE_ERR         = 104;
        this.DATA_OUT_OF_RANGE_ERR      = 105;
        this.NOT_ALLOWED_ERR            = 106;
        this.SIZE_EXCEEDED_ERR          = 107;
        this.INVALID_URI_ERR            = 108;
        this.URI_NOT_FOUND_ERR          = 109;
        this.URI_ALREADY_EXISTS_ERR     = 110;
        this.NO_MEMORY_ERR              = 111;  
}

DeviceException.prototype = new Error(); //inheritance occurs here
DeviceException.prototype.constructor = DeviceException; //If this not present then, it uses default constructor of Error

//constructor for DeviceException.
function DeviceException(code,message) 
{
    this.toString = concatenate;
    this.code = code;
    this.name = "DeviceException";//we can even overwrite default name "Error"
    this.message=message; 
    
        this.MISSING_ARG_ERR            = 1;
        this.INVALID_ARG_ERR            = 2;
        this.NOT_SUPPORTED_ERR          = 3;
        this.TIMEOUT_ERR                = 100;
        this.DATA_NOT_FOUND_ERR         = 101;
        this.DATA_ALREADY_EXISTS_ERR    = 102;
        this.SERVICE_BUSY_ERR           = 103;
        this.SERVICE_IN_USE_ERR         = 104;
        this.DATA_OUT_OF_RANGE_ERR      = 105;
        this.NOT_ALLOWED_ERR            = 106;
        this.SIZE_EXCEEDED_ERR          = 107;
        this.INVALID_URI_ERR            = 108;
        this.URI_NOT_FOUND_ERR          = 109;
        this.URI_ALREADY_EXISTS_ERR     = 110;
        this.NO_MEMORY_ERR              = 111;  
}


function concatenate()
{
    return (this.name+': errcode: '+this.code+'\nline: '+this.lineNumber+'\nfileName: '+this.fileName+'\nerrmsg: '+this.message);
}

function splitErrorMessage(errmessage)
{
	if(errmessage.search(/:/)!=-1)
	{
		if((errmessage.split(":").length)==2)
		{
			return errmessage.split(":")[1];
		}
		if((errmessage.split(":").length)>2)
		{
			return errmessage.split(":")[2];
		}
	}
	return errmessage;
}


var __s60_start_and_wait_cb;

function __s60_on_app_exit(){
  widget.onshow = null;
  if(__s60_start_and_wait_cb !== null){
    __s60_start_and_wait_cb();
  }
}

function __s60_on_app_start(){
  widget.onhide = null;
  widget.onshow = __s60_on_app_exit;
}

// This function cannot actually force JS to wait,
// but it does supply a callback the apps can use
// to continue processing on return from the app.
// Apps should take care not to reinvoke this and
// should be careful about any other processing
// that might happen while the app is running.

function __s60_start_and_wait(id, args, app_exit_cb){
  __s60_start_and_wait_cb = app_exit_cb;
  widget.onhide = __s60_on_app_start;
  widget.openApplication(id, args);
}

function __s60_api_not_supported(){
  throw(err_ServiceNotSupported);
}

function __s60_enumerate_object(object, namespace, func, param){
   var key;
   for (key in object) {
   		var propname;
   		if (namespace) {
   			propname = namespace + "." + key;
   		}
   		else {
   			propname = key;
   		}
   		var value = object[key];
   		if (typeof value == "object") {
   			__s60_enumerate_object(value, propname, func, param);
   		}
   		else {
   			func(propname, value, param);
   		}
   }
}


/*
 * Handling Async calls
 */
function removeFromArray(transId){
    for (i = 0; i < (glob_obj.glob_cb_arr.length); i++) {
        if (glob_obj.glob_cb_arr[i].transactionId == transId) {
            glob_obj.glob_cb_arr.splice(i, 1);
        }
    }
}

function addToGlobalArray(transId, sCb, errCb){

    var obj = new Object();
    
    obj.success_cb = sCb;
    obj.transactionId = transId;
    obj.error_cb = errCb;
    
    glob_obj.glob_cb_arr.push(obj);
    
}

function getFromArray(tid){
    var i;
    
    for (i = 0; i < (glob_obj.glob_cb_arr.length); i++) {
        if (glob_obj.glob_cb_arr[i].transactionId == tid) {
            return glob_obj.glob_cb_arr[i];
        }
    }
	
	if(temp_scb)
	{
		var obj = new Object();
    
	    obj.success_cb = temp_scb;
	    obj.error_cb = temp_ecb;
		
		temp_ecb = temp_scb = null;
		return obj;		
	}
    return null;
}
