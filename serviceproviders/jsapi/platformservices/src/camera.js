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

function __device_camera_descriptor(provider){
  this.interfaceName = provider.interfaceName;
  this.version = provider.version;
}

//Why bother to define these methods? Because the camera
//object defines the contract for providers!

function __device_camera_startCamera(camera_cb, ErrorCallback){
  return this.provider.startCamera(camera_cb, ErrorCallback);
}

function __device_camera_stopViewfinder(){
  this.provider.stopViewfinder();
}

function __device_camera_takePicture(format){
  this.provider.takePicture(format);
}

// Private camera  prototype: called from service factory
function __device_camera(provider){
  //Private properties
  this.provider = provider;
  //Read-only properties
  this.interfaceName = provider.descriptor.interfaceName;
  this.version = provider.descriptor.version;
  this.supportedMediaTypes = provider.supportedMediaTypes;
  this.supportedSizes = provider.supportedSizes;
  //Core methods
  this.startCamera = __device_camera_startCamera;
  this.stopViewfinder = __device_camera_stopViewfinder;
  //Extended methods
  this.takePicture = __device_camera_takePicture;
}

// Camera service interface

var __device_camera_service_entry =  {"name": null, 
					 "version": null,
					 "proto": __device_camera,
					 "descriptor": __device_camera_descriptor,
					 "providers": [{"descriptor": __sp_camera_descriptor, "instance": __sp_camera_instance}]
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


// S60 sp-based camera provider

function __sp_camera_descriptor(){
  //__device_debug("sp_camera_descriptor");
  //Read-only properties
  this.interfaceName = "camera";
  if(window.__Service_Interface_Ver)
	this.version =__Service_Interface_Ver;
  else
	this.version =1.0;
  //Class-static properties 
}

// TBD make local to closure funcs
var __sp_camera_start_date;

var CAMERA_APP_ID = 0x101f857a;

//Apps should take care that this is not reinvoked
//while the viewfinder is running. 

function __sp_startCamera(camera_cb, err_cb){
	//If callback is null , then return missing argument error
	


    if (camera_cb == null) {
		throw new DeviceException(this.error.MISSING_ARG_ERR, "Camera:startCamera:callback is missing");
	}
	//If the callback is not a function, then return bad type error
	if(camera_cb == undefined)
	{
	throw new DeviceException(this.error.INVALID_ARG_ERR, "Camera:startCamera:callback is a non-function" );	
	}
	
	if (typeof(camera_cb) != "function") {
		throw new DeviceException(this.error.INVALID_ARG_ERR, "Camera:startCamera:callback is a non-function" );
	}
	
	if(err_cb)
	{ 

		if(typeof err_cb != 'function')
		{
			
		   	throw new DeviceException(this.error.INVALID_ARG_ERR, "Camera:startCamera:callback is invalid");
		}
		
	}
	
  var finished = function (){
    var invoker = function (arg1, arg2, arg3){    	
      //__device_debug("invoker with: " + camera_cb);
      var it = arg3.ReturnValue;
      //arg3.ReturnValue.close();
      var item;
      var items = [];      
      
	  if(arg3.ErrorCode != 0)
		{
			
			err_cb(new DeviceException(arg3.ErrorCode, "Camera:startCamera: Operation Failed"));
			
			return;
		}	
	
 	  
      if (( item = it.getNext()) != undefined){
          var d = new Date(Date.parse(item.FileDate));
          //__device_debug(item.FileName + " " + d );
          // Items returned in reverse date order, so stop iterating before
          // reaching initial date. (Should be able to do this more efficiently
          // with sp filter, but that doesn't seem to work right now.)
          if (d > __sp_camera_start_date) {
          	
              var itemMap = {};
	      	  modifyObjectBaseProp(itemMap);
              var pathname = item.FileNameAndPath.replace(/\\/g, "/");
              var fileScheme = "file:///";
              //Non-patched builds don't allow file scheme TBD: change this for patched builds              
              var fileUrl = "";
              fileUrl = fileUrl.concat(fileScheme,pathname);
              itemMap.uri = fileUrl;// url
              
              var formatMap = {};
	      	   // modifyObjectBaseProp(formatMap);
              //var stringTemp = "";
              //stringTemp = stringTemp.concat(item.XPixels,"X",item.YPixels);
              //formatMap.dimensions = stringTemp;
              
              formatMap.height = item.XPixels;
              formatMap.width = item.YPixels;
              
              formatMap.type = item.MimeType;
              
              itemMap.format = formatMap;//format 
                
              items.unshift(itemMap); 
			  if (formatMap) {
			  	//delete formatMap.dimensions;
				//delete formatMap.mtype;
			  }
		  }
      
	  }
      var dummyTransID = 0;
      var dummyStatusCode = 0;
	   
      camera_cb(items);
    };
	
    //When camera returns, get the image(s) created
    try {
      var mso = device.getServiceObject("Service.MediaManagement", "IDataSource");
    }
    catch(e) {
      __device_handle_exception (e, "media service not available : " + e);
    }
    
    var criteria = {};
	modifyObjectBaseProp(criteria);
    criteria.Type = 'FileInfo';
    criteria.Filter = {};
	modifyObjectBaseProp(criteria.Filter);
    criteria.Filter.FileType = 'Image';
    //criteria.Filter.Key = 'FileDate';
    //criteria.Filter.StartRange = null;
    //criteria.Filter.EndRange = null;
    criteria.Sort = {};
	modifyObjectBaseProp(criteria.Sort);
    criteria.Sort.Key = 'FileDate';
    criteria.Sort.Order = 'Descending';
    
    try {
      var rval = mso.IDataSource.GetList(criteria, invoker);
    }
    catch (error) {
      __device_handle_exception (error, "media service GetList failed: " + error);
    }
  };

  __sp_camera_start_date = new Date();
  __s60_start_and_wait(CAMERA_APP_ID, "", finished);
  var dummyTid = 0;
  return dummyTid;
}

function __sp_supportedSizes() {
    try {
        var SysInfo = device.getServiceObject('Service.SysInfo', 'ISysInfo');
    }
    catch(e) {
      __device_handle_exception (e, "SysInfo Service not available : " + e);
    }
    var sys_req = {};
    modifyObjectBaseProp(sys_req);
    sys_req.Entity = "Camera";
    sys_req.Key = "CameraProperties";
    //Get supported Sizes
    try {
        var rval = SysInfo.ISysInfo.GetInfo(sys_req);
		if (sys_req) {
			delete sys_req.Entity;
			delete sys_req.Key;
		}
    }
    catch (error) {
        __device_handle_exception (error, "Camera : Failed to fetch supported size Info: " + error);
    }
    var returnValue = rval.ReturnValue;
    var resolutionArray = [];
    var supportedResolutions = [];
    resolutionArray = returnValue.ResolutionList;
    for(var i=0;i<resolutionArray.length;i++) {
       var stringTemp ="";
       stringTemp = stringTemp.concat(resolutionArray[i].height,"X",resolutionArray[i].width);
       supportedResolutions.push(stringTemp);        
    }
    return supportedResolutions;
}

function __sp_supportedMediaTypes() {
    try {
        var SysInfo = device.getServiceObject('Service.SysInfo', 'ISysInfo');
    }
    catch(e) {
      __device_handle_exception (e, "SysInfo Service not available : " + e);
    }
    var sys_req = {};
    modifyObjectBaseProp(sys_req);
    sys_req.Entity = "Camera";
    sys_req.Key = "CameraProperties";
    //Get supported Media Types
    try {
        var rval = SysInfo.ISysInfo.GetInfo(sys_req);
		if (sys_req) {
			delete sys_req.Entity;
			delete sys_req.Key;
		}
    }
    catch (error) {
        __device_handle_exception (error, "Camera :Failed to fetch supported media type Info: " + error);
    }
    var returnValue = rval.ReturnValue;
    var supportedMimeTypes = [];
    supportedMimeTypes = returnValue.MimeTypeList;  
    return supportedMimeTypes;
}

function __sp_camera_instance(){
  //__device_debug("sp_camera_instance");
  //Descriptor
  this.descriptor = new __sp_camera_descriptor();
  //Read-only properties
  this.supportedMediaTypes =   __sp_supportedMediaTypes();
  this.supportedSizes =  __sp_supportedSizes();
  //Core methods
  this.startCamera = __sp_startCamera;
  this.stopViewfinder = __s60_api_not_supported;
  //Extended methods
  this.takePicture = __s60_api_not_supported;
  this.error = new DeviceException(0, "Dummy");
  //Private data
}
