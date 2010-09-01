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


// sensors service interface

var __device_sensors_service_entry = {"name": null, 
				      "version": null,
				      "proto": __device_sensors,
				      "descriptor": __device_sensors_descriptor,
				      "providers": [{"descriptor": __sp_sensors_descriptor, "instance": __sp_sensors_instance}]
				     };
		   

// Private location prototype: called from service factory
function __device_sensors(provider){
  //Private properties
  this.provider = provider;
  //Read-only properties
  this.interfaceName = provider.descriptor.interfaceName;
  this.version = provider.descriptor.version;  
  //Extended methods
  this.getChannels = __device_sensors_getChannels;
  this.startChannel = __device_sensors_setNotifier;
  this.stopChannel = __device_sensors_cancelNotifier;
  this.getScaleFactor = __device_sensors_getScaleFactor;
}

function __device_sensors_descriptor(provider){
  this.interfaceName = provider.interfaceName;
  this.version = provider.version;
}

function __device_sensors_getChannels(){
  return this.provider.getChannels();
}

function __device_sensors_setNotifier(sensors_cb, channel,__fail_cb){
  return this.provider.startChannel(sensors_cb, channel,__fail_cb);
}

function __device_sensors_cancelNotifier(channel){
  return this.provider.stopChannel(channel);
}

function __device_sensors_getScaleFactor(channel){
  return this.provider.getScaleFactor(channel);
}



// S60 sp-based sensors provider
function __sp_sensors_descriptor(){
  //Read-only properties
  this.interfaceName = "sensors";
  if(window.__Service_Interface_Ver)
	this.version =__Service_Interface_Ver;
  else
	this.version =1.0;
  //Class-static properties 
}

function __sp_sensors_instance(){
  //Descriptor
  this.descriptor = new __sp_sensors_descriptor();
  //Extended methods
  this.getChannels = __sp_sensors_getChannels;
  this.startChannel =  __sp_sensors_setNotifier;
  this.stopChannel =  __sp_sensors_cancelNotifier;
  this.getScaleFactor = __sp_sensors_getScaleFactor;
  //Public properties
  
  try {
    //__device_debug("Trying sensors service");
    this.so = device.getServiceObject('Service.Sensor', 'ISensor');
    //__device_debug("Got sensors service object: ");    
  }
  catch (e){
    this.so = null;
    __device_handle_exception (e, "sensors service not available");
  }
}

var __rotation_channel = {
  ucb: null,
  tids: null
};


var __XYZ_channel = {
  ucb: null,
  tids: null
};

var __orientation_channel = {
  ucb: null,
  tids: null
};

function __rotation_cb(arg1, arg2, arg3){
    if(arg2 != event_cancelled)
        {
        var output = null ;    
        if (arg3.ReturnValue)
            {
            var time = arg3.ReturnValue.TimeStamp;
            var xrot = arg3.ReturnValue.XRotation;
            var yrot = arg3.ReturnValue.YRotation;
            var zrot = arg3.ReturnValue.ZRotation;
			      arg3.ReturnValue.close();
            output = {};
	          modifyObjectBaseProp(output); 
            output.timeStamp = time;
            output.rotationAboutXAxis = xrot;
            output.rotationAboutYAxis = yrot;
            output.rotationAboutZAxis = zrot;
            }
         __rotation_channel.ucb(output);
        }
		
}

function __XYZ_cb(arg1, arg2, arg3){
    if(arg2 != event_cancelled)
        {
        var output = null ;    
        if (arg3.ReturnValue)
            {
            var time = arg3.ReturnValue.TimeStamp;
            var xaxis = arg3.ReturnValue.XAxisData;
            var yaxis = arg3.ReturnValue.YAxisData;
            var zaxis = arg3.ReturnValue.ZAxisData;
			      arg3.ReturnValue.close();
            output = {}; 
	          modifyObjectBaseProp(output);
            output.timeStamp = time;
            output.axisX = xaxis;
            output.axisY = yaxis;
            output.axisZ = zaxis;
            }    
        __XYZ_channel.ucb(output);
        }
		
}

function __orientation_cb(arg1, arg2, arg3){
    if(arg2 != event_cancelled)
        {
        var output = null ;    
        if (arg3.ReturnValue)
            {
            var time = arg3.ReturnValue.TimeStamp;
            var orientation = arg3.ReturnValue.DeviceOrientation;
			arg3.ReturnValue.close();
            output = {}; 
	    modifyObjectBaseProp(output);
            output.timeStamp = time;
            output.deviceOrientation = orientation;
            }        
        __orientation_channel.ucb(output);
        }
		
}


// For now this is statically configured though this could be dynamically populated by the sensors sp




function __sp_sensors_getChannels(){
  return ["Rotation", "AccelerometerAxis", "Orientation"];
}

function __sp_sensors_setNotifier(__succes_cb, __channel,__fail_cb){ 
	    
    	var error = new DeviceException(0, 'dummy');
	    if (!__succes_cb) {//alert("!__succes_cb");
			throw new DeviceAPIError(error.MISSING_ARG_ERR, "Callback is missing");
		}		
		if ((typeof __succes_cb) != "function") {
			throw new DeviceAPIError(error.INVALID_ARG_ERR, "Callback is of invalid type");
		}	
		if (__fail_cb && ((typeof __fail_cb) != "function")) {
			throw new DeviceAPIError(error.INVALID_ARG_ERR, "InValid error Callback");
		} 
		if (!__channel) {
			throw new DeviceAPIError(error.MISSING_ARG_ERR, "Channel is missing");
		}			
		if ((typeof __channel) != "string") {
			
			throw new DeviceAPIError(error.INVALID_ARG_ERR, "Channel is of invalid type");
		}
		
		
	  var rval;
	  var cb;
	  var channelInfo = {};
	  modifyObjectBaseProp(channelInfo);
   switch(__channel){
   	  
	  case "Rotation":
		channelInfo.SearchCriterion = "Rotation";
		cb = __rotation_cb;
		__rotation_channel.ucb = __succes_cb;
		break;
	  case "AccelerometerAxis":
	  //alert("case AccelerometerAxis");
	  channelInfo.SearchCriterion = "AccelerometerAxis";
		cb = __XYZ_cb;
		__XYZ_channel.ucb = __succes_cb;
	 break;
	  case "Orientation":
		channelInfo.SearchCriterion = "Orientation";
		cb = __orientation_cb;
		__orientation_channel.ucb = __succes_cb;
		break;
	  default:
	    //alert("default");
	    throw  new DeviceAPIError(error.NOT_SUPPORTED_ERR, "Unsupported input channel");	
	 }
  
  try{
  	rval = this.so.ISensor.FindSensorChannel(channelInfo);
		if (channelInfo) {
		delete channelInfo.SearchCriterion;
		}
    if(rval.ErrorCode != 0)
      {
      throw  new DeviceAPIError(error.NOT_SUPPORTED_ERR, "StartChannel:Operation Failed");
      }

  var cmap = [];
  var transactionid = [];
  var returnvalue = rval["ReturnValue"];
  var count = returnvalue.length;
  cmap = returnvalue[0];
  var sensorParams = {};
	modifyObjectBaseProp(sensorParams);
	sensorParams.ListeningType = "ChannelData";
	sensorParams.ChannelInfoMap = cmap;
	var result = this.so.ISensor.RegisterForNotification(sensorParams, cb);
	  if(sensorParams){
	  	delete sensorParams.ChannelInfoMap;
		  delete sensorParams.ListeningType;
	  }
	  if(cmap){
	  	delete cmap.index;
	  }
    transactionid[0] = result["TransactionID"];
    if(result.ErrorCode != 0)
        {
        //throw result.ErrorCode;
		
						 if( result.ErrorCode == 1005)
						 {
						 __fail_cb(new DeviceAPIError(error.SERVICE_IN_USE_ERR,"Not Allowed Operation"));
						 return;	 
						 }
						 else
						 	{
						 	throw  new DeviceAPIError(error.NOT_SUPPORTED_ERR, "StartChannel:Operation Failed");	
						 	}
				 }
        		 
			
    }catch(e2){
      __device_handle_exception (e2, "__sp_sensors_setNotifier: RegisterForNotification: " + e2);
        }
  
  
  switch(__channel){
  case "Rotation":
    __rotation_channel.tid = transactionid;
    break;
  case "AccelerometerAxis":
  __XYZ_channel.tid = transactionid;
    break;
  case "Orientation":
    __orientation_channel.tid = transactionid;
    break;
  }
  return transactionid;
 }

function __sp_sensors_cancelNotifier(__channel){
 
    var error1 = new DeviceException(0, 'dummy');
	  if(!__channel)
			    throw  new DeviceAPIError(error1.MISSING_ARG_ERR, "Channel is missing");
							
			if((typeof __channel) != "string")
					throw  new DeviceAPIError(error1.INVALID_ARG_ERR, "Channel is of invalid type");
  
	  var id ;  
	  
	  switch (__channel)
	  {
		case "Rotation":
		  id = __rotation_channel.tid;
		  __rotation_channel.tid = null;
		  break;
		case "AccelerometerAxis":
		id = __XYZ_channel.tid;
		__XYZ_channel.tid = null;
		  break;
		case "Orientation":
		  id = __orientation_channel.tid;
		  __orientation_channel.tid = null;
		  break;
		default:
		  throw  new DeviceAPIError(error1.NOT_SUPPORTED_ERR, "Unsupported input channel");	
		}     
	
	 if(!id)
	 {
	 throw  new DeviceAPIError(error1.DATA_NOT_FOUND_ERR, "Stop Channel:Operation Failed");		
	 }
	 
	var cancelParams = {};
  modifyObjectBaseProp(cancelParams);
  for (var i in id) {
  		  cancelParams.TransactionID = id[i];
				try {
					var result = this.so.ISensor.Cancel(cancelParams);
					if (cancelParams) {
						delete cancelParams.TransactionID;
					}
					if (result.ErrorCode != 0) {
						throw  new DeviceAPIError(error1.DATA_NOT_FOUND_ERR, "Stop Channel:Operation Failed");
						}
				} 
				catch (e1) {
					__device_handle_exception(e1, "__sp_sensors_cancelNotifier: " + e1);
				}
		}
}

function __sp_sensors_getScaleFactor(__channel){
	var error2 = new DeviceException(0, 'dummy');
	if(!__channel)
		    throw  new DeviceAPIError(error2.MISSING_ARG_ERR, "Channel is missing");
						
		if((typeof __channel) != "string")
				throw  new DeviceAPIError(error2.INVALID_ARG_ERR, "Channel is of invalid type");
				
	if(__channel != "AccelerometerAxis")
		    throw  new DeviceAPIError(error2.NOT_SUPPORTED_ERR, "Unsupported input channel");
		    
 try{    
	  var channelInfo = {};	    
	  channelInfo.SearchCriterion = "AccelerometerAxis";
	  var rval = this.so.ISensor.FindSensorChannel(channelInfo);
		if (channelInfo) {
		delete channelInfo.SearchCriterion;
		}
    if(rval.ErrorCode != 0)
      {
      throw  new DeviceAPIError(error2.NOT_SUPPORTED_ERR, "getScaleFactor:Operation Failed");
      }
    var cmap = [];    		
		var returnvalue = rval["ReturnValue"];
    cmap = returnvalue[0];
    var sensorParams = {};
	  modifyObjectBaseProp(sensorParams);
	  sensorParams.ListeningType = "ChannelData";
	  sensorParams.ChannelInfoMap = cmap;
	  var result = this.so.ISensor.GetScaleFactor(sensorParams);
	  if(sensorParams){
	  	delete sensorParams.ChannelInfoMap;
		  delete sensorParams.ListeningType;
	  }
	  if(cmap){
	  	delete cmap.index;
	  }
	  if(result.ErrorCode != 0)
        {
        throw  new DeviceAPIError(error2.NOT_SUPPORTED_ERR, "getScaleFactor:Operation Failed");	
        }
   }
   
   catch (e1) {
					__device_handle_exception(e1, "__sp_sensors_getScaleFactor: " + e1);
				}
		 return result["ReturnValue"];  
				
}