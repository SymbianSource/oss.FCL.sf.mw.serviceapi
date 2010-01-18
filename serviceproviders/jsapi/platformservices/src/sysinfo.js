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


// sysinfo service interface
var __device_sysinfo_service_entry = {"name": null, 
				      "version": null,
				      "proto": __device_sysinfo,
				      "descriptor": __device_sysinfo_descriptor,
				      "providers": [{"descriptor": __sp_sysinfo_descriptor, "instance": __sp_sysinfo_instance}]
				     };
	

// Private location prototype: called from service factory
function __device_sysinfo(provider){
	//alert("in provider");
  //Private properties
  this.provider = provider;
  //Read-only properties
  this.interfaceName = provider.descriptor.interfaceName;
  this.version = provider.descriptor.version;  
  //Extended methods
  this.getChannelList = __device_channels_get;
  this.getChannel = __device_sysinfo_get;
  this.startChannel = __device_sysinfo_setNotifier;
  this.stopChannel = __device_sysinfo_cancelNotifier;

  this.cancel = __device_sysinfo_cancel;
}

function __device_sysinfo_descriptor(provider){
  this.interfaceName = provider.interfaceName;
  this.version = provider.version;
}
function __device_channels_get(){
   return this.provider.getChannelList();   
}

function __device_sysinfo_get(channel, sysinfo_cb, ErrorCallback){
  return this.provider.getChannel(channel, sysinfo_cb, ErrorCallback);
}

function __device_sysinfo_setNotifier( sysinfo_cb,channel, trigger, ErrorCallback){
  return this.provider.startChannel(sysinfo_cb,channel,trigger, ErrorCallback);
}

function __device_sysinfo_cancelNotifier(channel){
  return this.provider.stopChannel(channel);
}

function __device_sysinfo_cancel(id) {
    return this.provider.cancel(id);    
}
	   




// S60 sp-based sysinfo provider
/*
var DATA_NOT_FOUND_ERR = 101;
var DATA_OUT_OF_RANGE_ERR = 105;
var NOT_ALLOWED_ERR = 106;
//var error = new DeviceAPIError();
var error = new DeviceException();
*/
function __sp_sysinfo_descriptor(){
    //Read-only properties
    this.interfaceName = "sysinfo";
  if(window.__Service_Interface_Ver)
	this.version =__Service_Interface_Ver;
  else
	this.version =1.0;
    //Class-static properties 
}

function __sp_sysinfo_instance(){//alert("in instance");
    //Descriptor
    this.descriptor = new __sp_sysinfo_descriptor();
    //Extended methods
    this.getChannelList = __sp_channel_descriptors_get;
    this.getChannel = __sp_sysinfo_get;
	this.getChannelCb = __sp_sysinfo_get_cb;
	
    this.startChannel = __sp_sysinfo_setNotifier;
    this.stopChannel = __sp_sysinfo_cancelNotifier;
    this.cancel = __sp_sysinfo_cancel;
    this.error = new DeviceException(0, "Dummy");
    try {
        //__device_debug("Trying sysinfo service");
        this.so = device.getServiceObject('Service.SysInfo', 'ISysInfo');
		//alert( this.so);
        //__device_debug("Got sysinfo service object: ");    
    } 
    catch (e) {
        this.so = null;
		//alert( this.so);
        __device_handle_exception(e, "Sysinfo service not available");
    }
}
// Data format is 
// {
//    Entity: Network, Device, Features, Battery
//    Key:  SignalStrength, RegistrationStatus, CurrentNetwork, CellID | IMEI|| ChargingStatus, BatteryStrength
//    [SystemData]: params
// }

function __sp_channel_descriptors_get(){
	
	var __sp_channel_descriptors = [{
		name: 'Charging',
		data: [{
			name: 'chargingStatus',
			range: 'true or false',
			description: 'Charging(true) ,Not charging(false)',
		}],
		style: ["Sync", "Oneshot", "Notification"]
	}, {
		name: 'BluetoothOn',
		data: [{
			name: 'btOn',
			range: 'true or false',
			description: 'BluetoothOn(true) ,BluetoothOff(false)',
		}],
		style: ["Sync", "Oneshot", "Notification"]
	}, {
		name: 'PhoneLanguage',
		data: [{
			name: 'phoneLanguage',
			range: "",
			description: "",
		}],
		style: ["Sync", "Oneshot"]
	}, {
		name: 'ProductType',
		data: [{
			name: 'productType',
			range: "",
			description: "",
		}],
		style: ["Sync", "Oneshot"]
	}, {
		name: 'FirmwareVersion',
		data: [{
			name: 'firmwareVersion',
			range: "",
			description: "",
		}],
		style: ["Sync", "Oneshot"]
	}, {
		name: 'BatteryLevel',
		data: [{
			name: "batteryLevel ",
			range: '0-100',
			description: 'Percent battery charge'
		}],
		style: ["Async", "Oneshot", "Notification"]
	}, {
		name: 'SignalStrength',
		data: [{
			name: "signalStrength",
			range: '0-100',
			description: 'Signal Strength in Percentage'
		}],
		style: ["Async", "Oneshot", "Notification"]
	}, {
		name: 'Network',
		data: [{
			name: "networkName ",
			description: "Network name"
		}, {
			name: "networkStatus",
			range: "Available,Current,Forbidden",
			description: ""
		}, {
			name: "networkMode",
			range: "ModeGsm,ModeCdma,ModeWcdma",
			description: ""
		}, {
			name: "mobileCountryCode",
			range: "",
			description: ""
		}, {
			name: "mobileNetworkCode",
			range: "",
			description: ""
		}, {
			name: "locationStatus",
			range: "True, False",
			description: ""
		}, {
			name: "areaCode",
			range: "",
			description: ""
		}, {
			name: "cellID",
			range: "",
			description: ""
		}],
		style: ["Async", "Oneshot", "Notification"]
	} , {
		name: 'IMEI',
		data: [{
			name: "imei",
			range: "",
			description: ""
		}],
		style: ["Sync", "Oneshot"]
	} , {
		name: 'OutOfMemory',
		data: [{
			name: "oomDrive",
			range: "",
			description: ""
		}],
		style: ["NA", "NA", "Notification"]
	}, {
		name: 'DeviceOrientation',
		data: [{
			name: "deviceOrientation",
			range: "Landscape,Portrait",
			description: ""
		}],
		style: ["Sync", "Oneshot"]
	}, {
		name: 'RoamingFlag',
		data: [{
			name: "roamingFlag",
			range: "",
			description: ""
		}],
		style: ["Sync", "Oneshot"]
	}, {
		name: 'DeviceInputMethod',
		data: [{
			name: "deviceInputMethod",
			range: "Touch,NonTouch,Hybrid",
			description: ""
		}],
		style: ["Sync", "Oneshot"]
	}, {
		name: 'HomeNetwork',
		data: [{
			name: "networkName ",
			description: "Network name"
		}, {
			name: "networkStatus",
			range: "Available,Current,Forbidden",
			description: ""
		}, {
			name: "networkMode",
			range: "ModeGsm,ModeCdma,ModeWcdma",
			description: ""
		}, {
			name: "mobileCountryCode",
			range: "",
			description: ""
		}, {
			name: "mobileNetworkCode",
			range: "",
			description: ""
		}, {
			name: "locationStatus",
			range: "True, False",
			description: ""
		}, {
			name: "areaCode",
			range: "",
			description: ""
		}, {
			name: "cellID",
			range: "",
			description: ""
		}],
		style: ["Async", "Oneshot", "Notification"]
	}];
	return __sp_channel_descriptors;
}

var max = 110;
var min = 40;
var diff = max-min;
function __sp_device_sysinfo_toDecibel(trigger) {
    var percentage = trigger/100;
    var decibel = max - (percentage * diff);
	decibel = Math.round(decibel);
    return decibel;
}

function __sp_device_sysinfo_toPercentage(signalStatus) {
   if(signalStatus == 0){
		return signalStatus;
		}
    else{
		 var numerator = max - signalStatus;
	    var percentage = numerator/diff;
	    percentage *= 100;
	    percentage = Math.round(percentage);
	    return percentage;  
    }             
}

function __sp_device_sysinfo_toBool(chargeStatus) {
	if(chargeStatus == 0){
		return false;
		}
    else{
		return true;
		}
}

function mappingVerification(errorCode) {
	if(errorCode == 1016 || errorCode == 1012 || errorCode == 1010 || errorCode == 1009 || errorCode == 1005 || errorCode == 1000 || errorCode == 1011 || errorCode == 1007 || errorCode  == 1003 || errorCode == 1002){
		return true;
		}
	else{
		return false;		
		}
}

function __sp_device_sysinfo_extract(sysinfo){

    var channel = sysinfo.Key;
	//alert("inside extract , channel  "+channel);
    var dataMap = {};
    modifyObjectBaseProp(dataMap);
    try {
        switch (channel) { 
            case "ChargingStatus": 
                dataMap.chargingStatus = __sp_device_sysinfo_toBool(sysinfo.Status);
                break; 
                
            case "BatteryStrength":
                dataMap.batteryLevel = sysinfo.Status;
				//alert(dataMap.batteryLevel);
                break; 
                
            case "SignalStrength":
                dataMap.signalStrength = __sp_device_sysinfo_toPercentage(sysinfo.Status);
                break;
                
            case "CurrentNetwork":
				var status;
				var  mode;
				switch(sysinfo.NetworkStatus)
				{
					case 0:
						status = "Available";
						break;
					case 1:
						status = "Current";
						break;
					case 2:
						status = "Forbidden";
						break;
					default:
						status = "Unknown";
						break;									
				}
				
				switch(sysinfo.NetworkMode) {
					case 1:
						mode = "ModeGsm";
						break;
					case 3:
					case 4:
						mode = "ModeCdma";
						break;
					case 5:
						mode = "ModeWcdma";
						break;
					default:
						mode = "Unknown";
						break;
				}
                dataMap.networkName = sysinfo.NetworkName;
                dataMap.networkStatus = status;
                dataMap.networkMode = mode;
                dataMap.mobileCountryCode = sysinfo.CountryCode;
                dataMap.mobileNetworkCode = sysinfo.NetworkCode;
                dataMap.locationStatus = sysinfo.LocationStatus;
                dataMap.areaCode = sysinfo.AreaCode;
                dataMap.cellID = sysinfo.CellId;
                break;
                
            case "DisplayLanguage" :
                dataMap.phoneLanguage = sysinfo.StringData;
                break;
                
            case "BlueTooth" :
                dataMap.btOn = __sp_device_sysinfo_toBool(sysinfo.Status);
                break;
                
            case "ProductType":
                dataMap.productType = sysinfo.StringData;
                break;
                
            case "FirmwareVersion" :
                dataMap.firmwareVersion = sysinfo.StringData;
                break;
            
			case "DeviceInputMethod" :
                dataMap.deviceInputMethod = sysinfo.StringData;
                break;			
			    
            default :
                dataMap = sysinfo;
                break;
        }
        return dataMap;
    } 
    
    catch (e) {
        __device_handle_exception(e, "__sp_device_sysinfo_extract: " + e);
    }   
}

function __sp_sysinfo_get_cb(arg1, arg2, arg3){//alert("in callback of wrapper");
		var success_cb ;
		var error_cb ;
	 	var CbObj;
	    
	    
	    CbObj = glob_obj.getFromArray(arg1);
	    
	    
	    
	    if (CbObj) {
	        success_cb = CbObj.success_cb;
	        error_cb = CbObj.error_cb;
	    }
	    
	    else {
	        alert("Sysinfo: __sp_sysinfo_get_cb: Callback not found ");
			return;
	    }
	    		
        var op = null;        
		if(arg3.ErrorCode != 0){
				var err_msg = splitErrorMessage(arg3.ErrorMessage); 	
				error_cb(new DeviceException(MapErrorCode[arg3.ErrorCode], "SysInfo:getChannel: "+err_msg ));
			}
		else if (arg3.ReturnValue) {
		    //alert("returnvalue is"+arg3.ReturnValue);
            op = __sp_device_sysinfo_extract(arg3.ReturnValue);
			arg3.ReturnValue.close();
			success_cb(op);
        }
		glob_obj.removeFromArray(arg1);	
    }
	
function __sp_sysinfo_get(channel, sysinfo_success_cb, ErrorCallback){
    var so;
    var rval;
    
    
	//---------------Function not in use-------------------
    /*var cell_id_invoker = function(arg1, arg2, arg3){
        var op = null;
        if (arg3.ReturnValue) {
            op = arg3.ReturnValue;
			arg3.ReturnValue.close();
        }
        sysinfo_success_cb(arg1, arg3.ErrorCode, op);
        so.ISysInfo.Cancel(arg1);
    };*/
	//-----------------------------------------------------------
    var async = false;
    var rdata = "Status";
	var rvalSync;
    var sys_req = {};
	modifyObjectBaseProp(sys_req);
    try {
        switch (channel) {
            case "Charging":
                sys_req.Entity = "Battery";
                sys_req.Key = "ChargingStatus";
                break;
            case "BatteryLevel":
                sys_req.Entity = "Battery";
                sys_req.Key = "BatteryStrength";
                async = true;
                break;
            case "SignalStrength":
                sys_req.Entity = "Network";
                sys_req.Key = "SignalStrength";
                async = true;
                break;
            case "Network":
                sys_req.Entity = "Network";
                sys_req.Key = "CurrentNetwork";
                async = true;
                break;
		    case "PhoneLanguage": 
                sys_req.Entity = "General";
                sys_req.Key = "DisplayLanguage";
                break;
            case "BluetoothOn":
                sys_req.Entity = "Connectivity";
                sys_req.Key = "BlueTooth";
                break;
            case "ProductType":
                sys_req.Entity = "Device";
                sys_req.Key = "ProductType";
                break; 
            case "FirmwareVersion":
                sys_req.Entity = "Device";
                sys_req.Key = "FirmwareVersion";
                break; 
				
			case "DeviceInputMethod":
				sys_req.Entity = "Device";
                sys_req.Key = "DeviceInputMethod";			
			     break;	                               
            default:
                if (channel == null) {
					throw new DeviceException(this.error.MISSING_ARG_ERR, "SysInfo:getChannel:channel is missing" );
                }
                else {
                    if (typeof channel != "string"){ 
                        throw new DeviceException(this.error.INVALID_ARG_ERR, "SysInfo:getChannel:channel is of invalid type");
						}
                    else {
						throw new DeviceException(this.error.INVALID_ARG_ERR, "SysInfo:getChannel:channel is invalid");
						}
                }
        }
        
        if (async) {
            if (sysinfo_success_cb == null) {
                throw new DeviceException( this.error.MISSING_ARG_ERR, "SysInfo:getChannel:callback is missing");
				}
            if (typeof sysinfo_success_cb != "function"){ 
                 throw new DeviceException(this.error.INVALID_ARG_ERR, "SysInfo:getChannel:callback is invalid" );            
				 }
			if(ErrorCallback){
				if(typeof(ErrorCallback) != 'function'){
				throw new DeviceException(this.error.INVALID_ARG_ERR, "SysInfo:getChannel: ErrorCallback is invalid" );
				}
			}
			temp_scb = sysinfo_success_cb;
			temp_ecb = ErrorCallback;
            rval = this.so.ISysInfo.GetInfo(sys_req, this.getChannelCb);
			if (rval.TransactionID) {
            	glob_obj.addToGlobalArray(rval.TransactionID, sysinfo_success_cb, ErrorCallback);
        	}
            if (rval.ErrorCode != 0) {     
						var doMap = mappingVerification(rval.ErrorCode);
						if(doMap) {
							switch(MapErrorCode[rval.ErrorCode])
							{						
								case this.error.MISSING_ARG_ERR :
								case this.error.INVALID_ARG_ERR :							
								if(rval.ErrorMessage)  {
									var err_msg = splitErrorMessage(rval.ErrorMessage); 
									throw new DeviceException(MapErrorCode[rval.ErrorCode], "SysInfo: getChannel: "+err_msg );
								}
								else {
									throw new DeviceException(MapErrorCode[rval.ErrorCode], "SysInfo:getChannel:Operation Failed" );	
								}
								break;
	       						default:
									sysinfo_success_cb(0) ;
	    					}
						}
						else {
							sysinfo_success_cb(0) ;
						}
			}
						
            return rval.TransactionID;
        }
        else {   
            rval = this.so.ISysInfo.GetInfo(sys_req);
            if (rval.ErrorCode != 0) {
                if(rval.ErrorMessage) {
					var err_msg1 = splitErrorMessage(rval.ErrorMessage); 
					throw new DeviceException(MapErrorCode[rval.ErrorCode], "SysInfo: getChannel: "+err_msg1 );
				}
				else {
					throw new DeviceException(MapErrorCode[rval.ErrorCode], "SysInfo:getChannel:Operation Failed" );	
				}
            }
            rvalSync = __sp_device_sysinfo_extract(rval.ReturnValue);
            return rvalSync;
        }
		delete sys_req;
    } 
    catch (e) {
        __device_handle_exception(e, "__sp_sysinfo_get: getChannel: " + e);
    }
}

// channels
var __cell_id_channel = {
    scb: null,
	ecb: null,
    cancel_id: null
};

function __cell_id_channel_cb(arg1, arg2, arg3){
    var op = null;
	if(arg3.ErrorCode){
		__cell_id_channel.ecb(arg3.ErrorCode);
	}
    else if (arg3.ReturnValue) {
       op = arg3.ReturnValue;
	   arg3.ReturnValue.close();
	    __cell_id_channel.scb(op);    
    }
}

var __charging_status_channel = {
    scb: null,
	ecb: null,
    cancel_id: null    
};
function __charging_status_channel_cb(arg1, arg2, arg3){
    var op = null;
	if(arg3.ErrorCode){
		__charging_status_channel.ecb(arg3.ErrorCode);
	}
    else if (arg3.ReturnValue) {
        op = __sp_device_sysinfo_extract(arg3.ReturnValue);
		arg3.ReturnValue.close();
    __charging_status_channel.scb(op);
    }
}


var __net_coverage_channel = {
    scb: null,
	ecb: null,
    cancel_id: null    
};
function __net_coverage_channel_cb(arg1, arg2, arg3){
    var op = null;
	if(arg3.ErrorCode){
		__net_coverage_channel.ecb(arg3.ErrorCode);
	}
    else if (arg3.ReturnValue) {
        op = __sp_device_sysinfo_extract(arg3.ReturnValue);
		arg3.ReturnValue.close();
	    __net_coverage_channel.scb(op);
    }
}

var __battery_level_channel = {
    scb: null,
	ecb: null,
    cancel_id: null    
};
function __battery_level_channel_cb(arg1, arg2, arg3){
    var op = null;
	if(arg3.ErrorCode){
		__battery_level_channel.ecb(arg3.ErrorCode);
	}
	else if (arg3.ReturnValue) {
        op = __sp_device_sysinfo_extract(arg3.ReturnValue);
		arg3.ReturnValue.close();
	    __battery_level_channel.scb(op);
    }
}

var __bluetooth_on_channel = {
    scb: null,
	ecb: null,
    cancel_id: null    
};
function __bluetooth_on_channel_cb(arg1, arg2, arg3){
    var op = null;
	if(arg3.ErrorCode){
		__bluetooth_on_channel.ecb(arg3.ErrorCode);
	}
	else if (arg3.ReturnValue) {
        op = __sp_device_sysinfo_extract(arg3.ReturnValue);
		arg3.ReturnValue.close();
    __bluetooth_on_channel.scb(op);
    }
}


var __signal_channel = {
    scb: null,
	ecb: null,
    cancel_id: null    
};


function __signal_channel_cb(arg1, arg2, arg3){

    var op = null;
	if(arg3.ErrorCode){
		__signal_channel.ecb(arg3.ErrorCode);
	}
	else if (arg3.ReturnValue) {
        op = __sp_device_sysinfo_extract(arg3.ReturnValue);
		arg3.ReturnValue.close();
	    __signal_channel.scb(op);
    }
}


function __sp_sysinfo_setNotifier(sysinfo_success_cb, channel_name, trigger, ErrorCallback){
    var rval;
    var channel = null;
    var cb = null;
    var sys_req = {};
	
	
	 if (sysinfo_success_cb == null) {
            throw new DeviceException(this.error.MISSING_ARG_ERR, "SysInfo:startChannel:callback is missing" );
        }
        if (typeof sysinfo_success_cb != "function") {
            throw new DeviceException(this.error.INVALID_ARG_ERR, "SysInfo:startChannel:callback is invalid" );
        }
		
	
	modifyObjectBaseProp(sys_req);
    try {
        switch (channel_name) {
            case "Charging":
                sys_req.Entity = "Battery";
                sys_req.Key = "ChargingStatus";
                channel = __charging_status_channel;
                cb = __charging_status_channel_cb;
                break;            
            case "Network":
                sys_req.Entity = "Network";
                sys_req.Key = "CurrentNetwork";
                channel = __net_coverage_channel;
                cb = __net_coverage_channel_cb;
                break;
            case "BatteryLevel":
                sys_req.Entity = "Battery";
                sys_req.Key = "BatteryStrength";
                sys_req.SystemData = {};
				modifyObjectBaseProp(sys_req.SystemData);
                if (trigger == null) {
                    trigger = 50;
                }
                if(!(trigger>=0 && trigger<=100)){
				    throw new DeviceException(this.error.DATA_OUT_OF_RANGE_ERR, "SysInfo:startChannel:trigger is out of range" );
					}
				if(typeof trigger != "number"){
					throw new DeviceException(this.error.INVALID_ARG_ERR, "SysInfo:startChannel:trigger is of  invalid type" );
					}
                sys_req.SystemData.Status = trigger;
                channel = __battery_level_channel;
                cb = __battery_level_channel_cb;
                break;
            case "SignalStrength":
                sys_req.Entity = "Network";
                sys_req.Key = "SignalStrength";
                sys_req.SystemData = {};
				modifyObjectBaseProp(sys_req.SystemData);
                if (trigger != null) {
				     if(!(trigger>=0 && trigger<=100)){
						throw new DeviceException(this.error.DATA_OUT_OF_RANGE_ERR, "SysInfo:startChannel:trigger is out of range" );
						}
					if(typeof trigger != "number"){
						throw new DeviceException(this.error.INVALID_ARG_ERR, "SysInfo:startChannel:trigger is of invalid type" );
						}
                sys_req.SystemData.Status = __sp_device_sysinfo_toDecibel(trigger);						                 
                }
                channel = __signal_channel;
                cb = __signal_channel_cb;
                break;                
             case "BluetoothOn":
                sys_req.Entity = "Connectivity";
                sys_req.Key = "BlueTooth";
                channel = __bluetooth_on_channel;
                cb = __bluetooth_on_channel_cb;
                break;
            default:
                var error;
                if (channel_name == null) {
				    throw new DeviceException(this.error.MISSING_ARG_ERR, "SysInfo:startChannel:channel is missing" );
                }
                else {
                    if (typeof channel_name != "string"){ 
						throw new DeviceException(this.error.INVALID_ARG_ERR, "SysInfo:startChannel:channel is of invalid type" );
						}
                    else {
                        throw new DeviceException(this.error.INVALID_ARG_ERR, "SysInfo:startChannel:channel is invalid" );
						}
                }
				if(sys_req.SystemData){
					delete sys_req.SystemData;
					}
        }
        
        channel.scb = sysinfo_success_cb;		
       
		channel.ecb = ErrorCallback;
		
		if(channel.ecb){
				if(typeof(channel.ecb) != 'function'){
				throw new DeviceException(this.error.INVALID_ARG_ERR, "SysInfo:startChannel: ErrorCallback is invalid" );
				}
			}
        if (channel.cancel_id) {
            var cancelParams = {};
			modifyObjectBaseProp(cancelParams);
            cancelParams.TransactionID = channel.cancel_id;
            this.so.ISysInfo.Cancel(cancelParams);            
            channel.cancel_id = null;   
			delete cancelParams;         
        }
        temp_scb = sysinfo_success_cb;
		temp_ecb = ErrorCallback;
        rval = this.so.ISysInfo.GetNotification(sys_req, cb);
		
		delete sys_req;
        if (rval.ErrorCode != 0) {
            switch(MapErrorCode[rval.ErrorCode])
			{						
				case this.error.MISSING_ARG_ERR :
				case this.error.INVALID_ARG_ERR :		
				if(rval.ErrorMessage)  {
					var err_msg = splitErrorMessage(rval.ErrorMessage); 
					throw new DeviceException(MapErrorCode[rval.ErrorCode], "SysInfo: startChannel: "+err_msg );
				}
				else {
					throw new DeviceException(MapErrorCode[rval.ErrorCode], "SysInfo:startChannel:Operation Failed" );	
				}
				break;
				default:
					sysinfo_success_cb(0) ;
			}
        }
        channel.cancel_id = rval.TransactionID;        
        return channel.cancel_id;
    } 
    
    catch (e) {
        __device_handle_exception(e, "__sp_sysinfo_startChannel: " + e);
    }
}

function __sp_sysinfo_cancelNotifier(channel_name){
    try {
        switch (channel_name) {            
            case "CellId":
                channel = __cell_id_channel;
                break;
            case "Charging":
                channel = __charging_status_channel;
                break;                
            case "Network":
                channel = __net_coverage_channel;
                break;
            case "BatteryLevel":
                channel = __battery_level_channel;
                break;
            case "SignalStrength":
                channel = __signal_channel;
                break;
            case "BluetoothOn":
                channel = __bluetooth_on_channel;
                break;
            default:
                var error;
                if (channel_name == null) {
                     throw new DeviceException(this.error.MISSING_ARG_ERR, "SysInfo:stopChannel:channel is missing" );
                }
                else {
                    if (typeof channel_name != "string") {
						 throw new DeviceException(this.error.INVALID_ARG_ERR, "SysInfo:stopChannel:channel is of invalid type"  );
						 }
                    else{
						throw new DeviceException(this.error.INVALID_ARG_ERR, "SysInfo:stopChannel:channel is invalid" );
						}
                }
        }
        if (channel.cancel_id) {
            var cancelParams = {};
			modifyObjectBaseProp(cancelParams);
            cancelParams.TransactionID = channel.cancel_id;
            var retval = this.so.ISysInfo.Cancel(cancelParams);   
			delete cancelParams;   
            if(retval.ErrorCode != 0) {
					if(retval.ErrorMessage)  {
						var err_msg = splitErrorMessage(retval.ErrorMessage); 
						throw new DeviceException(MapErrorCode[retval.ErrorCode], "SysInfo: stopChannel: "+err_msg );
					}
					else {
						throw new DeviceException(MapErrorCode[retval.ErrorCode], "SysInfo:stopChannel:Operation Failed" );	
					}
					}	           
            channel.cancel_id = null;          
        }
        else {
			throw new DeviceException(this.error.DATA_NOT_FOUND_ERR, "SysInfo:stopChannel:channel not started" );
        }
    } 
    catch (e) {
        __device_handle_exception(e, "__sp_sysinfo_stopChannel: " + e);
    }
}

function __sp_sysinfo_cancel(cancel_Id) {
    try {        
        var cancelFlag = 0;
        
        if(cancel_Id == null) {
            throw new DeviceException(this.error.MISSING_ARG_ERR, "SysInfo:cancel:Id is missing" );
        }
        
        if(typeof cancel_Id != "number") {
            throw new DeviceException(this.error.INVALID_ARG_ERR, "SysInfo:cancel:Id is of invalid type" );
        }

        if (cancel_Id == __charging_status_channel.cancel_id || cancel_Id == __net_coverage_channel.cancel_id || cancel_Id == __battery_level_channel.cancel_id || cancel_Id == __bluetooth_on_channel.cancel_id || cancel_Id == __signal_channel.cancel_id){
            cancelFlag = 1;
			}
        
        if (cancelFlag != 1) {          
                var cancelParam = {
                    TransactionID: cancel_Id
                };
                var retval = this.so.ISysInfo.Cancel(cancelParam);
                if (retval.ErrorCode != 0) {
                    if (retval.ErrorMessage) {
                        var err_msg = splitErrorMessage(retval.ErrorMessage);//alert("err_msg_my"+err_msg);
                        throw new DeviceException( this.error.INVALID_ARG_ERR, "SysInfo:cancel: " + err_msg);
                    }
                    else {
                        throw new DeviceException(MapErrorCode[retval.ErrorCode],"SysInfo:cancel:Operation Failed" );
                    }
                }
        }
        
        else {
            cancelFlag = 0;
			throw new DeviceException(this.error.NOT_ALLOWED_ERR,"SysInfo:cancel:Cannot Cancel a channel started using startChannel ");          
        }
    }
    catch (e) {
        __device_handle_exception(e, "__sp_sysinfo_cancel: " + e);
    }  
}
