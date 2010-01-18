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

var _infinity = 1.7976931348623157E+10308;
/*function PositionError()
{
	this.UNKNOWN_ERROR = 0;
	this.PERMISSION_DENIED = 1;
	this.POSITION_UNAVAILABLE = 2;
	this.TIMEOUT = 3;
	this.code ;
	this.message ;
}
function Coordinates()
{
	this.latitude = null;
	this.longitude = null;
	this.altitude = null;
	this.accuracy = null;
	this.altitudeAccuracy = null;
	this.heading = null;
	this.speed = null;
}
function Position()
{
	this.coords = null;
	this.timestamp = null;
}
function PositionOptions()
{
	this.enableHighAccuracy = null;
	this.timeout = null;
	this.maximumAge = null;
}*/

function TransIdCbMap()
{
	this.TransactionID = null;
	this.success_callback = null;
	this.error_callback = null;
}

function __device_geolocation_descriptor(provider)
{
	this.interfaceName = provider.interfaceName;
	this.version = provider.version;
}

function __device_geolocation_getCurrentPosition(success_cb,fail_cb,posOptions)
{
  
	return this.provider.getLocation(success_cb,fail_cb,posOptions);
}


function __device_geolocation_watchPosition(success_cb,fail_cb,posOpts)
{
	return this.provider.traceLocation(success_cb,fail_cb,posOpts);
}

function __device_geolocation_clearWatch(watchId)
{
	this.provider.clearTrace(watchId);
}

// Private location prototype: called from service factory
function __device_geolocation(provider)
{
	//Private properties
	this.provider = provider;
	//Read-only properties
	this.interfaceName = provider.descriptor.interfaceName;
	this.version = provider.descriptor.version;
	//one shot retrival of the current position of the device
	this.getCurrentPosition = __device_geolocation_getCurrentPosition;
	
	//Register to get contineous update of device location change
	this.watchPosition = __device_geolocation_watchPosition;
	
	//Clear previously invoke watchPosition Request
	this.clearWatch = __device_geolocation_clearWatch;
}

// geolocation service interface

// Namepace: com.nokia.device.service

var __device_geolocation_service_entry = {"name": null, 
					     "version": null,
					     "proto": __device_geolocation,
					     "descriptor": __device_geolocation_descriptor,
					     "providers": [{"descriptor": __sp_location_descriptor, "instance": __sp_location_instance}]
					    };






/*
Copyright � 2009 Nokia. All rights reserved.
Code licensed under the BSD License:
Software License Agreement (BSD License) Copyright � 2009 Nokia.
All rights reserved.
Redistribution and use of this software in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 
Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution. 
Neither the name of Nokia Corporation. nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission of Nokia Corporation. 
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

version: 1.0
*/


// S60 sp-based location provider
 function Location_PositionError()
	{
		this.UNKNOWN_ERROR = 0;
		this.PERMISSION_DENIED = 1;
		this.POSITION_UNAVAILABLE = 2;
		this.TIMEOUT = 3;
		this.code ;
		this.message ;
	}
	function Location_Coordinates()
	{
		this.latitude = null;
		this.longitude = null;
		this.altitude = null;
		this.accuracy = null;
		this.altitudeAccuracy = null;
		this.heading = null;
		this.speed = null;
	}
	function Location_Position()
	{
		this.coords = null;
		this.timestamp = null;
	}
	function Location_PositionOptions()
	{
		this.enableHighAccuracy ;
		this.timeout;
		this.maximumAge;
	}





var __sp_location_trace_transactionId = -1;

function __sp_location_handle_error(errorCallback,errorCode,errorMessage)
	{ 
		if( (errorCallback != undefined) && (typeof errorCallback == 'function') && (errorCallback != null) )
		{
			//create a new position error object
			var posError = new Location_PositionError(); 
			if( (-21) == errorCode )
			{
				posError.code = posError.PERMISSION_DENIED;
				posError.message = "permission denied";
				
			}
			else if( (-33) == errorCode )
			{
	
				posError.code = posError.TIMEOUT;
				posError.message = "request timed out";
	
				
			}
			else 
			{
				posError.code = posError.UNKNOWN_ERROR;
				posError.message = "UnKnown Error";
				
			}
			
			//Invoke user supplied error callback
			errorCallback( posError );
			
		} else {
			var posError = new Location_PositionError();
			posError.code = posError.UNKNOWN_ERROR;
			posError.message = "UnKnown Error";
			throw posError;
		}
		
		
		
	}

function __sp_location_descriptor()
{
	//Read-only properties
	this.interfaceName = "geolocation";
  if(window.__Service_Interface_Ver)
	this.version =__Service_Interface_Ver;
  else
	this.version =1.0;
	//Class-static properties 
}


var obj;

function __sp_getLocation_cb(arg1, arg2, arg3)
	{ 
	var CbObj;
    
    
    CbObj = glob_obj.getFromArray(arg1);
    
    
    
    if (CbObj) {
        success_cb1 = CbObj.success_cb;
        error_cb = CbObj.error_cb;
    }
    
    else {
        alert("Geolocation: __sp_getLocation_cb: Callback not found ");
		return;
    }
    
	
		if( arg3.ErrorCode )
		{
			//process error condition
				////alert("arg3.ErrorCode");
				__sp_location_handle_error(error_cb,arg3.ErrorCode,arg3.ErrorMessage);
				return;			
		}
		//there is no error so invoke consumer supplied success callback
		else
		{    
			 var _pos_coord = new Location_Coordinates();
			_pos_coord.longitude = (arg3.ReturnValue.Longitude == undefined)?null:arg3.ReturnValue.Longitude;
			_pos_coord.latitude = (arg3.ReturnValue.Latitude == undefined)?null:arg3.ReturnValue.Latitude;
			_pos_coord.altitude = (arg3.ReturnValue.Altitude == undefined)?null:arg3.ReturnValue.Altitude;
			_pos_coord.accuracy = (arg3.ReturnValue.HorizontalAccuracy == undefined)?null:arg3.ReturnValue.HorizontalAccuracy;			
			_pos_coord.altitudeAccuracy = (arg3.ReturnValue.VerticalAccuracy == undefined)?null:arg3.ReturnValue.VerticalAccuracy;
			_pos_coord.heading = (arg3.ReturnValue.Heading == undefined)?null:arg3.ReturnValue.Heading;
			_pos_coord.speed = (arg3.ReturnValue.HorizontalSpeed == undefined)?null:arg3.ReturnValue.HorizontalSpeed;
			
			//Position Object
			var _pos_data = new Location_Position();

			_pos_data.coords = {};
			modifyObjectBaseProp(_pos_data.coords);
			_pos_data.coords =_pos_coord;
			_pos_data.timestamp = new Date();
			
			//Invoke consumer callback			
			success_cb1( _pos_data );			
			delete _pos_data.timestamp;
			delete _pos_data;
			delete _pos_coord;	
		}
		 glob_obj.removeFromArray(arg1);	
	}
	
//Gets the current location 
function __sp_getLocation(success_cb,fail_cb,posOptions)
{    
     
	
		
	 if((success_cb == undefined) || (success_cb == null) || (typeof(success_cb) != "function"))
			{
				var errorFormat = "Wrong callback type";
		       __sp_location_handle_error(fail_cb,0,errorFormat);
				
			}	
	
	
	if ((fail_cb != undefined)) {
				if ((fail_cb != null)
				    &&(fail_cb != "")
					&& (typeof(fail_cb) != "function")) {						
						var errorObject = new Location_PositionError();
						errorObject.code = -1;
						throw errorObject;	
				}
			}


	var returnValue;
	//Input object to be passed to Location provider
	var criteria = {};
	modifyObjectBaseProp(criteria);
	criteria.LocationInformationClass = "GenericLocationInfo";
	
	var updateoptions = {};
	modifyObjectBaseProp(updateoptions);
	updateoptions.UpdateInterval = 0;
	
	if (posOptions != undefined && posOptions != null) {
		if ((typeof(posOptions) != "object")) {
			////alert("!= object");
			var errorMessage = "Wrong posOptions type";
			__sp_location_handle_error(fail_cb, 0, errorMessage);
			return;
		}
	}		
			
	if( posOptions != undefined )
	{
	
		if (posOptions.maximumAge != undefined ) {
		
			if (posOptions.maximumAge) {
				//If the param is specified and it is a number
				if ((posOptions.maximumAge == Infinity)) {////alert("infinty");
					if ((posOptions.enableHighAccuracy == undefined) ||
					(typeof(posOptions.enableHighAccuracy) == "boolean")) {															
						var arg3 = this.so.ILocation.GetLastPosition();
						if (arg3.ErrorCode < 0) { 						
							var errorMessage = "Invalid input type";
							__sp_location_handle_error(fail_cb, 0, errorMessage);
							return;
							
						}
						
						var _pos_coord = new Location_Coordinates();
						_pos_coord.longitude = (arg3.ReturnValue.Longitude == undefined) ? null : arg3.ReturnValue.Longitude;
						_pos_coord.latitude = (arg3.ReturnValue.Latitude == undefined) ? null : arg3.ReturnValue.Latitude;
						_pos_coord.altitude = (arg3.ReturnValue.Altitude == undefined) ? null : arg3.ReturnValue.Altitude;
						_pos_coord.accuracy = (arg3.ReturnValue.HorizontalAccuracy == undefined) ? null : arg3.ReturnValue.HorizontalAccuracy;
						_pos_coord.altitudeAccuracy = (arg3.ReturnValue.VerticalAccuracy == undefined) ? null : arg3.ReturnValue.VerticalAccuracy;
						_pos_coord.heading = (arg3.ReturnValue.Heading == undefined) ? null : arg3.ReturnValue.Heading;
						_pos_coord.speed = (arg3.ReturnValue.HorizontalSpeed == undefined) ? null : arg3.ReturnValue.HorizontalSpeed;
						
						//Position Object
						var _pos_data = new Location_Position();
						_pos_data.coords = {};
						modifyObjectBaseProp(_pos_data.coords);
						_pos_data.coords = _pos_coord;
						_pos_data.timestamp = new Date();
						
						//Invoke consumer callback
						
						success_cb(_pos_data);
						delete _pos_data.timestamp;
						delete _pos_data;
						delete _pos_coord;
						return;
						
					}
					
				
				}
			
			if (!(isNaN(parseInt(posOptions.maximumAge)))) {
					
					if ((posOptions.maximumAge == 0)) {
						
						var errorMessage = "Invalid input type";
						__sp_location_handle_error(fail_cb, 0, errorMessage);
						return;
					}
					
					    //alert("number");
						updateoptions.UpdateMaxAge = posOptions.maximumAge ;
						//alert("updateoptions.UpdateMaxAget"+ updateoptions.UpdateMaxAge);
					
				}
				else {
					//alert("!number");
					var errorMessage = "Invalid input type";
					__sp_location_handle_error(fail_cb, 0, errorMessage);
					return;
				}
				
			}
			
			else if ((posOptions.maximumAge == null) || (posOptions.maximumAge == "")) { ////alert("null");
					}
			
		}
		
		//check if timeout is supplied.
		if((posOptions.enableHighAccuracy !== undefined ))
		{  
			
			if(posOptions.enableHighAccuracy == true) {////alert("1");
					criteria.EnableHighAccuracy = posOptions.enableHighAccuracy;
				}				
			else if(posOptions.enableHighAccuracy == false) {	////alert("2e");					
						criteria.EnableHighAccuracy = posOptions.enableHighAccuracy;
					}				
			else if ((posOptions.enableHighAccuracy == null) || (posOptions.enableHighAccuracy == "")) {
							}
			else{ ////alert("acc = else");
				if ((typeof(posOptions.enableHighAccuracy) != "boolean")) {
					var errorFormat1 = "Wrong value for enableHighAccuracy param";
					__sp_location_handle_error(fail_cb, 0, errorFormat1);
				
					return;
				}
				
			}
			
		}
		
			
		if (posOptions.timeout !== undefined) {
			if ((posOptions.timeout !== null) || ((posOptions.timeout !== ""))) {
				//alert("12");
				if ((posOptions.timeout == Infinity)) {
					//alert("12345");
					//alert("infinty condition");
					var errorMessage = "Invalid input type";
					__sp_location_handle_error(fail_cb, 0, errorMessage);
					return;
				}
				
				else 
					if (!(isNaN(parseInt(posOptions.timeout)))) {
						//alert("timeout = 0")
						if ((posOptions.timeout <= 2147483647)) {
						
						if ((posOptions.timeout == 0)) {
							//alert("inside if int");
							var errorMessage = "Invalid input type";
							__sp_location_handle_error(fail_cb, 0, errorMessage);
							return;
						}
						//alert("true condition");
						updateoptions.UpdateTimeOut = posOptions.timeout;
						
					}
					else{
						var errorMessage = "Invalid input type";
				       __sp_location_handle_error(fail_cb, 0, errorMessage);
				       return;
					}
			}
		}
		else if ((posOptions.timeout === null) || ((posOptions.timeout === ""))) {
				//alert("true condition");
			
			}
			else {
				//alert("!number");
				var errorMessage = "Invalid input type";
				__sp_location_handle_error(fail_cb, 0, errorMessage);
				return;
			}		
		}   
		     
	}

	// Setting PartialUpdates to false ensures that user gets at least 
	// BasicLocationInformation (Longitude, Latitude, and Altitude.)
	updateoptions.PartialUpdates = false;
		
	criteria.Updateoptions = updateoptions;
	
	try 
	{     
		temp_scb = success_cb;
		temp_ecb = fail_cb;
		var rval = this.so.ILocation.GetLocation(criteria, this.getLocationCb);   
		if (rval.TransactionID) {
            glob_obj.addToGlobalArray(rval.TransactionID, success_cb, fail_cb);
        }
		
		delete updateoptions;
		delete criteria; 
		
		if(rval.ErrorCode != 0)
			{   		
			//process error condition
	
			__sp_location_handle_error(fail_cb,rval.ErrorCode,rval.ErrorMessage);
			
			//__sp_location_handle_error(__fail_cb,-1);
			return;
			}

	}
	
	catch (e) 
	{
		__device_handle_exception (e, "__sp_getLocation: " + e);
	}
}



var __sp_location_trace_ucb = null;
var __sp_location_fail_cb  = null;

function __sp_traceLocation_cb(arg1, arg2, arg3){
	
		 var CbObj;
    
    
	    CbObj = glob_obj.getFromArray(arg1);
	    
	    
	    
	    if (CbObj) {
	        success_cb = CbObj.success_cb;
	        error_cb = CbObj.error_cb;
	    }
	    
	    else {
	        alert("Geolocation: __sp_traceLocation_cb: Callback not found ");
			return;
	    }
    
		
			
		if( arg3.ErrorCode )
		{	
			//process error condition			
			__sp_location_handle_error(error_cb,
									   arg3.ErrorCode,
									   arg3.ErrorMessage);
				
		}
		
		else//there is no error so invoke consumer supplied success callback
		{   
			
			 var _pos_coord = new Location_Coordinates();
			_pos_coord.longitude = (arg3.ReturnValue.Longitude == undefined)?null:arg3.ReturnValue.Longitude;
			_pos_coord.latitude = (arg3.ReturnValue.Latitude == undefined)?null:arg3.ReturnValue.Latitude;
			_pos_coord.altitude = (arg3.ReturnValue.Altitude == undefined)?null:arg3.ReturnValue.Altitude;
			_pos_coord.accuracy = (arg3.ReturnValue.HorizontalAccuracy == undefined)?null:arg3.ReturnValue.HorizontalAccuracy;		
			_pos_coord.altitudeAccuracy = (arg3.ReturnValue.VerticalAccuracy == undefined)?null:arg3.ReturnValue.VerticalAccuracy;
			_pos_coord.heading = (arg3.ReturnValue.Heading == undefined)?null:arg3.ReturnValue.Heading;
			_pos_coord.speed = (arg3.ReturnValue.HorizontalSpeed == undefined)?null:arg3.ReturnValue.HorizontalSpeed;
			
			//Position Object
			var _pos_data = new Location_Position();
			_pos_data.coords = {};
			modifyObjectBaseProp(_pos_data.coords);
			_pos_data.coords =_pos_coord;
			_pos_data.timestamp = new Date();
			
			
			//Invoke consumer callback
			
			success_cb( _pos_data );
			delete _pos_data.timestamp;
			delete _pos_data;
			delete _pos_coord;
			return;
		}
	 glob_obj.removeFromArray(arg1);	
	}

//Funtion to obtain periodic updates
function __sp_traceLocation(trace_cb, fail_cb,posOptions)
{

	
	if((trace_cb == undefined) || (trace_cb == null) || (typeof(trace_cb) != "function"))
			{
				var errorMessage = "Wrong callback type";
				__sp_location_handle_error(fail_cb,0,errorMessage);
				return;				
			}
	
	
	if((typeof trace_cb != 'function' ))
	{////alert("not fun");
		var errorMessage = "Wrong callback type";
		__sp_location_handle_error(fail_cb,0,errorMessage);
		return;
	}
	
	if ((fail_cb != undefined)) {////alert("!= fail_cb");
				if ((fail_cb != null)
				    &&(fail_cb != "")
					&& (typeof(fail_cb) != "function")) {
						//////alert("fail_cb fail");
					var errorObject = new Location_PositionError();
					errorObject.code = -1;
					throw errorObject;	
				}
			}
   
   
	   
	var thisobj = this;
	
	
	
	var updateoptions = {};
	modifyObjectBaseProp(updateoptions);
	updateoptions.UpdateInterval = 0;
	var criteria = {};
	modifyObjectBaseProp(criteria);
	criteria.LocationInformationClass = "GenericLocationInfo";	
	
	if (posOptions != undefined && posOptions != null) {
		if ((typeof(posOptions) != "object")) {
			////alert("!= object");
			var errorMessage = "Wrong posOptions type";
			__sp_location_handle_error(fail_cb, 0, errorMessage);
			return;
		}
	}		

	if (posOptions != undefined) {
	
	
		if ((posOptions.enableHighAccuracy !== undefined)) {
		
			if (posOptions.enableHighAccuracy == true) {////alert("1");
				criteria.EnableHighAccuracy = posOptions.enableHighAccuracy;
			}
			else 
				if (posOptions.enableHighAccuracy == false) { ////alert("2e");					
					criteria.EnableHighAccuracy = posOptions.enableHighAccuracy;
				}
				else 
					if ((posOptions.enableHighAccuracy == null) || (posOptions.enableHighAccuracy == "")) {
					}
					
					else { 
						if ((typeof(posOptions.enableHighAccuracy) != "boolean")) {
							var errorFormat = "Wrong value for enableHighAccuracy param";
							__sp_location_handle_error(fail_cb, 0, errorFormat);
							return;
						}
						
					}
			
		}	

	
	if (posOptions.timeout !== undefined) {
			if ((posOptions.timeout !== null)  || ((posOptions.timeout !== ""))) {
					//alert("12");
				if ((posOptions.timeout == Infinity)) {
					//alert("12345");
					//alert("infinty condition");
					var errorMessage = "Invalid input type";
					__sp_location_handle_error(fail_cb, 0, errorMessage);
					return;
				}
				
				else if (!(isNaN(parseInt(posOptions.timeout)))) {//alert("timeout = 0")
					
					if ((posOptions.timeout == 0) ) {
						//alert("inside if int");
						var errorMessage = "Invalid input type";
						__sp_location_handle_error(fail_cb, 0, errorMessage);
						return;
					}
						//alert("true condition");
						updateoptions.UpdateTimeOut = posOptions.timeout ;
					
				}	
			}	
				
		else if ((posOptions.timeout === null) ||((posOptions.timeout === ""))) {
					//alert("true condition");
					//	updateoptions.UpdateTimeOut = posOptions.timeout * 1000;
				}
				else {
					//alert("!number");
					var errorMessage = "Invalid input type";
					__sp_location_handle_error(fail_cb, 0, errorMessage);
					return;
				}	
				
					
		}
		//check that update interval if specified is an integer.
	 
		if( typeof posOptions.maximumAge != 'undefined')
		{
			
						
			if(posOptions.maximumAge == _infinity)
				{
					updateoptions.UpdateTimeOut = 0;
					updateoptions.UpdateMaxAge = 2147483647; //2^31 - 1

				}
			
			//If the param is specified and it is a number 
			else if(!(isNaN(parseInt(posOptions.maximumAge))))
			{
		  		updateoptions.UpdateMaxAge = posOptions.maximumAge ;
			}
				
			else if ((posOptions.maximumAge === null) || ((posOptions.maximumAge === ""))) {
				//alert("true condition");
			//	updateoptions.UpdateTimeOut = posOptions.timeout * 1000;
				}
			else {
				//alert("!number");
				var errorMessage = "Invalid input type";
				__sp_location_handle_error(fail_cb, 0, errorMessage);
				return;
			}		
				
		}
		
	}

	// Setting PartialUpdates to false ensures that user gets at least 
	// BasicLocationInformation (Longitude, Latitude, and Altitude.)	
	updateoptions.PartialUpdates = false;
	
	criteria.Updateoptions = updateoptions;
	
	try 
	{
		temp_scb = trace_cb;
		temp_ecb = fail_cb;
		var rval = this.so.ILocation.Trace(criteria,this.traceCb);
		if (rval.TransactionID) {
            glob_obj.addToGlobalArray(rval.TransactionID, trace_cb, fail_cb);
        }
		delete updateoptions;
		delete criteria;
		if(rval.ErrorCode != 0)
			{
				//process error condition
				__sp_location_handle_error(fail_cb,rval.ErrorCode,rval.ErrorMessage);				
				return;
			}
		
		return rval.TransactionID;
	}

	catch (e) 
	{
		__device_handle_exception (e, "__sp_traceLocation: " + e);  
	}
}

//clears any outstanding Trace requests
function __sp_clearTrace(watchId)
{ 

		if(typeof watchId != 'number')	
		{
			        var errorMessage = "Invalid input type";
				   __sp_location_handle_error(fail_cb,0,errorMessage);		
		}
		 
		var locationParams = {            
            TransactionID : watchId
        };
		
		try 
		{
			
			var result = this.so.ILocation.Cancel(locationParams);
			
		//Just ignore the error
			
		}
		catch (e) 
		{
			__device_handle_exception (e, "__sp_clearTrace: " + e );
		
		}
		 

}


function __sp_location_instance()
{
	
	//Descriptor
	this.descriptor = new __sp_location_descriptor();
	//Core methods
	this.getLocation = __sp_getLocation;
	this.getLocationCb = __sp_getLocation_cb;
	//Extended methods
	this.traceLocation = __sp_traceLocation;
	this.traceCb = __sp_traceLocation_cb;
	this.clearTrace = __sp_clearTrace;
	
	//Private data

	try
	{
	
		this.so = device.getServiceObject("Service.Location", "ILocation");
	
	}
	catch (e)
	{
		this.so = null;
		__device_handle_exception (e, "Location service not available");
	}
}
