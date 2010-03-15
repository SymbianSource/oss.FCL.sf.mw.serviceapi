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

function __device_media_descriptor(provider){
  this.interfaceName = provider.interfaceName;
  this.version = provider.version;
}

function __device_media_getList(media_cb, match,order, media_errcbk){
//  return this.provider.getList(match,order, media_cb);
   return this.provider.getList(media_cb, match,order, media_errcbk);
}
function __device_media_getThumbnail(media_cb, match, media_errcbk){


   return this.provider.getThumbnail(media_cb, match, media_errcbk);
}

function __device_media_addStreamUri(uri){

   return this.provider.addStreamUri(uri);
}

function __device_media_deleteStreamUri(uri){

   return this.provider.deleteStreamUri(uri);
}

function __device_media_cancel(transactionId)
{

 this.provider.cancel(transactionId);
}

function __device_media_refreshMediaDb(uri)
{

 this.provider.refreshMediaDb(uri); 
}

// Private location prototype: called from service factory
function __device_media(provider){
  //Private properties
  this.provider = provider;
  //Read-only properties
  this.interfaceName = provider.descriptor.interfaceName;
  this.version = provider.descriptor.version;
  //constants
  this.SORT_ASCENDING = 0;
  this.SORT_DESCENDING = 1;
    
  //Extended methods
  this.getList = __device_media_getList;

  this.getThumbnail = __device_media_getThumbnail;


  this.addStreamUri = __device_media_addStreamUri;

  this.deleteStreamUri = __device_media_deleteStreamUri;
  
  this.refreshMediaDb = __device_media_refreshMediaDb;
  
  this.cancel = __device_media_cancel;


}

// media service interface

var __device_media_service_entry = {"name": null, 
				      "version": null,
				      "proto": __device_media,
				      "descriptor": __device_media_descriptor,
				      "providers": [{"descriptor": __sp_media_descriptor, "instance": __sp_media_instance}]
				     };
		   

function __device_media_descriptor(provider){
  this.interfaceName = provider.interfaceName;
  this.version = provider.version;
}

function __device_media_getList(media_cb, match,order, media_errcbk){
//  return this.provider.getList(match,order, media_cb);
   return this.provider.getList(media_cb, match,order, media_errcbk);
}
function __device_media_getThumbnail(media_cb, match, media_errcbk){


   return this.provider.getThumbnail(media_cb, match, media_errcbk);
}

function __device_media_addStreamUri(uri){

   return this.provider.addStreamUri(uri);
}

function __device_media_deleteStreamUri(uri){

   return this.provider.deleteStreamUri(uri);
}

function __device_media_cancel(transactionId)
{

 this.provider.cancel(transactionId);
}

function __device_media_refreshMediaDb(uri)
{

 this.provider.refreshMediaDb(uri); 
}

// Private location prototype: called from service factory
function __device_media(provider){
  //Private properties
  this.provider = provider;
  //Read-only properties
  this.interfaceName = provider.descriptor.interfaceName;
  this.version = provider.descriptor.version;
  //constants
  this.SORT_ASCENDING = 0;
  this.SORT_DESCENDING = 1;
    
  //Extended methods
  this.getList = __device_media_getList;

  this.getThumbnail = __device_media_getThumbnail;


  this.addStreamUri = __device_media_addStreamUri;

  this.deleteStreamUri = __device_media_deleteStreamUri;
  
  this.refreshMediaDb = __device_media_refreshMediaDb;
  
  this.cancel = __device_media_cancel;


}

// media service interface

var __device_media_service_entry = {"name": null, 
				      "version": null,
				      "proto": __device_media,
				      "descriptor": __device_media_descriptor,
				      "providers": [{"descriptor": __sp_media_descriptor, "instance": __sp_media_instance}]
				     };
		   


// S60 sp-based media provider
var FILESCHMLEN = 7;

//var MISSING_ARG_ERR = 1003;
//var error = DeviceException();

/*
if(undefined==com.nokia.device.media){
com.nokia.device.media={};
}

com.nokia.device.media.SORT_ASCENDING  = 0;
com.nokia.device.media.SORT_DESCENDING  = 1;
*/
function __sp_media_descriptor(){
  //Read-only properties
  this.interfaceName = "media";
  if(window.__Service_Interface_Ver)
	this.version =__Service_Interface_Ver;
  else
	this.version =1.0;
  //Class-static properties 
}

function __sp_device_media_item_build(sp_item){
    if (!sp_item) {
		return null;
	}
    var media_item = {};
	modifyObjectBaseProp(media_item);
    if (sp_item.FileNameAndPath) {
        var pathname = sp_item.FileNameAndPath.replace(/\\/g, "/");
        var fileScheme = "file://";
        media_item.uri = fileScheme + pathname; 
    }
    if(sp_item.MediaType){
		var mediaType = sp_item.MediaType;
		switch( mediaType ){
			case 1:
			case 2:	 media_item.type	= "audio";
					break;
			case 3: media_item.type	= "image";
					break;
			case 4: media_item.type	= "video";
					break;
			case 5: media_item.type	= "stream";
			        break;
			default:break;
		}
	}
if(sp_item.FileName){
		if(sp_item.MediaType == 3)
		{
		media_item.title = 	sp_item.FileName;
		}
	}
    if (sp_item.FileDate) {
		media_item.date = new Date(Date.parse(sp_item.FileDate));
	}
    if (sp_item.FileSize) {
		media_item.size = sp_item.FileSize;
	}
    if (sp_item.SongName) {
		media_item.title = sp_item.SongName;
	}
    if (sp_item.Artist) {
		media_item.artist = sp_item.Artist;
	}
    if (sp_item.Album) {
		media_item.album = sp_item.Album;
	}
    if (sp_item.Genre) {
		media_item.genre = sp_item.Genre;
	}
    if (sp_item.TrackNumber) {
		media_item.track = sp_item.TrackNumber;
	}
    if (sp_item.Composer) {
		media_item.composer = sp_item.Composer;
	}
    return media_item;
}

// ------ Wrap sp iterator ------- 

function __sp_media_iterator_get_next(){
  //__device_debug("sp_media_iterator_get_next");
  //alert("Before iterator_get_next");
  var item = this.iter.getNext();
  //alert("After iterator_get_next");
  if(typeof item == "undefined"){
    return null;
  }
  var mediaitem =  __sp_device_media_item_build(item);
  item.close();
  return mediaitem;
}

function __sp_media_iterator(js_iterator){
  this.iter = js_iterator;
  this.next = __sp_media_iterator_get_next;
  this.close = function(){
        this.iter.close();
    };
}

function __sp_media_get_field_name(name, type){
	 this.error = new DeviceException(0, "Dummy");
	//alert("__sp_media_get_field_name");
	  if(typeof name != "string"){
	    throw new DeviceException(this.error.INVALID_ARG_ERR ,"Media:getList:field is of invalid type");
	  }
     switch(name.toLowerCase()){
        case "title":
			if (type == "Image" || type == "Video") {
				//alert("__sp_media_get_field_name video r image");
				return "FileName";
			}
			else {
				//alert("__sp_media_get_field_name in else part");
				return "SongName";
			}
        case "artist":
			//alert(" In artist");
            return "Artist";
        case "album":
		//alert(" In album");
            return "Album";
        case "genre":
			//alert(" In genere");
            return "Genre";
        case "track":
		//alert(" In track");
            return "TrackNumber";
        case "composer":
            return "Composer";
        default:				
		    return null;
     }
}
function __sp_media_get_sortfield_name(name, type){
	 this.error = new DeviceException(0, "Dummy");
	//alert("neme = "+name);
	//alert("In get sort field"+typeof name);
	  if(typeof name != "string"){
	    throw new DeviceException(this.error.INVALID_ARG_ERR, "Media:getList:sortBy is of invalid type");
	  }
	  var sortfield = name.toLowerCase();
	  if( sortfield == "date"){
	  	return "FileDate";
	  }
	  else{
	  	return __sp_media_get_field_name(name, type);
	  }
}


// Converting date object to string
function __sp_media_get_date_objct(date)
{
	//alert("In method __sp_media_get_date_objct");
	var dateString = "";
	// adding year to dateString
	dateString = date.getFullYear().toString();

	// adding month to dateString
	if(date.getMonth() <10)
		{
		dateString = dateString + ("0")+(date.getMonth().toString());
		}
	else
		{
		dateString = dateString + (date.getMonth().toString());
		}

	// adding day to dateString
	var day = date.getDate() -1;
	if(day<10)
		{
		dateString = dateString + ("0")+(day.toString());
		}
	else
		{
		dateString = dateString + (day.toString());	
		}
		
		// Adding : to dateString
		dateString = dateString + (":");
	
	// Adding hours to dateString
	if(date.getHours()<10)		
		{
		dateString = dateString + ("0")+(date.getHours().toString());	
		}
	else
		{
		dateString = dateString + (date.getHours().toString());		
		}
		
	// Adding minutes to dateString
	if(date.getMinutes()<10)		
		{
		dateString = dateString + ("0")+(date.getMinutes().toString());	
		}
	else
		{
		dateString = dateString + (date.getMinutes().toString());		
		}

	// Adding seconds to dateString
	if(date.getSeconds()<10)		
		{
		dateString = dateString + ("0")+(date.getSeconds().toString());	
		}
	else
		{
		dateString = dateString + (date.getSeconds().toString());		
		}
	return dateString;
}

function __sp_media_getList_cb(arg1, arg2, arg3) {
	//alert("__sp_media_getList_cb" + arg1);
	var media_cb;
	var media_errcbk;
	 var CbObj;
    
    //alert("1111111111");
    CbObj = glob_obj.getFromArray(arg1);
	// alert("222222222222");
    
    if (CbObj) {
		 //alert("33333333333");
        media_cb = CbObj.success_cb;
		// alert("4444444444444444");
        media_errcbk = CbObj.error_cb;
		// alert("5555555555555555");
    }
    
    else {
		//alert("6666666666666666");
        alert("Media : __sp_media_getList_cb: Callback not found ");
		return;
    }
    
		if(arg3.ErrorCode != 0 && arg3.ErrorCode != 1010)
		{
			//alert("77777777777777");
			media_errcbk(new DeviceException( arg3.ErrorCode,"Media: getList: Operation Failed"));
			return;
		}
		if (arg2 != event_cancelled) {
			//alert("888888888");
			var iter = null;
			if (arg3.ReturnValue) {
				//alert("11");
				iter = new __sp_media_iterator(arg3.ReturnValue);
				//alert("12");
			}
			//alert( " before sucess call back");
			media_cb(iter); // Need to make change later on as case of eventid
			//alert( " After sucess call back");
		}
		
		glob_obj.removeFromArray(arg1);
  }

function __sp_media_getList(media_cb, match, order, media_errcbk){	
	//alert("In __sp_media_getList wraper ");
	if (!media_cb) {		
		throw new DeviceException(this.error.MISSING_ARG_ERR,"Media:getList:Callback is missing");
	}
	else 
		if (typeof media_cb != "function") //here we check if the type of callback is function. This case is useful when arbitrary values are passed to callback
		{			
			throw new DeviceException(this.error.INVALID_ARG_ERR,"Media:getList:Callback is of invalid type");
		}
	if(media_errcbk)
	{ 		
		if(typeof media_errcbk != 'function')
		{			
		   	throw new DeviceException(this.error.INVALID_ARG_ERR, "Media: getList: error callback is invalid");
		}
	}
	
	 if((typeof match) != 'object'){
  			//alert(" match is not object");
  	      	throw  new DeviceException(this.error.INVALID_ARG_ERR, "Invalid Argument:" +match);	
			}
	
		//alert(" In my match");
		if (match) {
			if (('sortBy' in match) && (match.sortBy == undefined || match.sortBy == null || match.sortBy == "")) {
				//alert(" In condition" + this.error.INVALID_ARG_ERR);
				throw new DeviceException(this.error.INVALID_ARG_ERR, "Media: getList: sortby is invalid");
				
			}
		}
	//alert(" After match");

  var criteria = {};  
  modifyObjectBaseProp(criteria);  
  criteria.Type = 'FileInfo';  
  criteria.Filter = {};
  modifyObjectBaseProp(criteria.Filter);
  criteria.Sort = {};
  modifyObjectBaseProp(criteria.Sort);
  if (match) {  	
  	  if(match.type){	  	
	  	  if(typeof match.type != "string"){		  	
		  throw new DeviceException(this.error.INVALID_ARG_ERR,"Media:getList:type is of invalid type");
		  }
	      switch (match.type.toLowerCase()) {
	          case "audio":
//	              criteria.Filter.FileType = "Music";
 	              criteria.Filter.FileType = "audio";
	              break;
	          case "image":
	              criteria.Filter.FileType = "Image";
	              break;
	          case "video":
			  		//alert(" In Video");
	              criteria.Filter.FileType = "Video";
	              break;
	          case "stream":
	              criteria.Filter.FileType = "StreamingURL";
	              break;
			  default:			 
			  	  throw new DeviceException(this.error.INVALID_ARG_ERR,"Media:getList: type is invalid");
	      }
		  
		  if( ('field' in match) && ( match.field == undefined || match.field == null) )
        		   throw new DeviceException(this.error.INVALID_ARG_ERR, "Media:getList:field is invalid");
				   
				   
	      if (match.field != null) {
	          criteria.Filter.Key = __sp_media_get_field_name(match.field.name,criteria.Filter.FileType);
			  if( criteria.Filter.Key == null ){			  
			  throw new DeviceException(this.error.INVALID_ARG_ERR, "Media:getList:key is invalid");	
			  }
	          if(match.field.value){
			  criteria.Filter.StartRange = match.field.value;
			  if(criteria.Filter.Key == "TrackNumber"){
			  criteria.Filter.EndRange = match.field.value;  
			  }
	          //Note: date matches not supported currently		  	
			  }			  
	      }
		  else{ // When match is not defined then we will look for daterange
		  	if(match.dateRange)
			{				
				if(typeof match.dateRange != "object")
					{						
					throw new DeviceException(this.error.INVALID_ARG_ERR, "Media:getList:dateRange is of invalid type");		
					}
				//alert("got daterange");
				criteria.Filter.Key = "FileDate";
				if((typeof match.dateRange.start != "undefined") && (typeof match.dateRange.end != "undefined"))
				{
						//alert(" In range");
				if((typeof match.dateRange.start != 'object') || ( match.dateRange.start == "") ||(match.dateRange.start == null)){
				throw new DeviceException(this.error.INVALID_ARG_ERR, "Media:getList:dateRange:start is of invalid type");		
				}
				else{
				criteria.Filter.StartRange = __sp_media_get_date_objct(match.dateRange.start);	
				}	
					
				if((typeof match.dateRange.end != 'object') || ( match.dateRange.end == "")||(match.dateRange.end == null)){
					//alert(" end is empty");
				throw new DeviceException(this.error.INVALID_ARG_ERR, "Media:getList:dateRange:end is of invalid type");		
				}
				else{
					//alert(" ")
				criteria.Filter.EndRange   = __sp_media_get_date_objct(match.dateRange.end);	
				}	
				
				}
				else{					 
					throw new DeviceException(this.error.INVALID_ARG_ERR, "Media:getList:start or end of dateRange is missing"); //  frm missing to invalid for test case 60 & 65
				}
			}		
				 else if( ('dateRange' in match) &&(match.dateRange == 0 || match.dateRange == null || match.dateRange == "")){
					//alert(" In else match.dateRange = "+typeof(match.dateRange));
					throw new DeviceException(this.error.INVALID_ARG_ERR, "Media:getList: dateRange is Invalid");
				}	
		  }
	      if (match.sortBy) {
	          criteria.Sort.Key = __sp_media_get_sortfield_name(match.sortBy, criteria.Filter.FileType);
			  if( criteria.Sort.Key == null ){
			  throw new DeviceException(this.error.INVALID_ARG_ERR, "Media:getList:sortBy is invalid");	
			  }
	      } 
		  else {
		  criteria.Sort.Key = "FileDate";
		  }
		  // Adding sort order
		  if(order)
		  {  	
				
				if (order == this.SORT_ASCENDING) {
								//alert(" Ascending ");
								criteria.Sort.Order = "Ascending";
							}
							// else if(order == com.nokia.device.SORT_DESCENDING || order == com.nokia.device.media.SORT_DESCENDING)
				else if (order == this.SORT_DESCENDING) {
									criteria.Sort.Order = "Descending";
								}				
								
				else if((order != this.SORT_ASCENDING) || (order != this.SORT_DESCENDING)) {
								throw new DeviceException(this.error.INVALID_ARG_ERR, "Media:getList:sortBy is invalid");
			}
		  }
		  else
		  {
		  criteria.Sort.Order = "Ascending"; 		
		  }
	      //criteria.Sort.Order = "Descending"; 
		  //Note: sort order has been removed because of ambiguous behavior: if FileDate
		  // is specified then sapi sorts in ascending order by default, if FileDate is not specified,
		  // sorting is performed on FileDate in descending order. 	  	
	  }
	  else{
	  			//alert( " In match.type missing");
	  	throw new DeviceException(this.error.MISSING_ARG_ERR, "Media:type is missing");
	  }	
  }
  else {
      // Must supply something to sp, so default to music .... Need to change to all
//      criteria.Filter.FileType = "Music"; // here need to make all
        criteria.Filter.FileType = "all"; 
        criteria.Sort.Key = "FileDate";
	  //	  criteria.Sort.Order = "Descending";
	  criteria.Sort.Order = "Ascending"; // By default it should be ascending
  }
  
  try {    
    //__device_debug("Getting media list");
	//alert(" before calling sapi");
	temp_scb = media_cb;
	temp_ecb = media_errcbk;
    var rval = this.so.IDataSource.GetList(criteria, this.getListMediaCb);
	//alert(" errorcode = "+rval.ErrorCode);
	//alert(" errorcode = "+rval.TransactionID);
	if (rval.TransactionID) {
		//alert(" In if of TransactionID");
        glob_obj.addToGlobalArray(rval.TransactionID, media_cb, media_errcbk);
    }
	//alert("rval.errorcode = "+rval.ErrorCode);
	if(criteria.Sort)
	{
	delete criteria.Sort;	
	}	
	if(criteria.Filter.StartRange)
	{
	delete 	criteria.Filter.StartRange;
	}

	if(criteria.Filter.EndRange)
	{
	delete 	criteria.Filter.EndRange;
	}

	if(criteria.Filter)
	{
	delete 	criteria.Filter;
	}

    if(rval.ErrorCode != 0){
    	  switch(MapErrorCode[rval.ErrorCode]){
				case this.error.MISSING_ARG_ERR :
				case this.error.INVALID_ARG_ERR :
				case this.error.NOT_SUPPORTED_ERR :
        		//case err_missing_argument :
        		//case err_bad_argument :
						//case err_InvalidService_Argument :
						//case err_ServiceNotSupported :
							
						if(rval.ErrorMessage){ 
            			var err_msg = splitErrorMessage(rval.ErrorMessage); 	
			            throw new DeviceException(MapErrorCode[rval.ErrorCode],"Media:getList:"+err_msg);						    
						}
						else{
						throw new DeviceException(MapErrorCode[rval.ErrorCode], "Media:getList:Operation failed");	
						}
						break;
						default:						
						//media_cb(iter) ;
						//err_cb(new DeviceException(MapErrorCode[rval.ErrorCode], "Media: getList: Operation Failed"));
						media_errcbk(new DeviceException(MapErrorCode[rval.ErrorCode], "Media: getList: Operation Failed"));
    	  }
    }
  return rval.TransactionID;
  }
  catch (e) {
    __device_handle_exception(e, '__sp_media_getList: '+e);
  }  
}

function __sp_media_getThumbnail_cb(arg1, arg2, arg3) {
	var thumbnail_errcbk;
	var thumbnail_cb;
	 var CbObj;
    
    
    CbObj = glob_obj.getFromArray(arg1);
    
    if (CbObj) {
        thumbnail_cb = CbObj.success_cb;
        thumbnail_errcbk = CbObj.error_cb;
    }
    
    else {
        alert("Media : __sp_media_getThumbnail_cb: Callback not found ");
		return;
    }
    
	if(arg3.ErrorCode != 0 && arg3.ErrorCode != 1010)
	{
		
		thumbnail_errcbk(new DeviceException(arg3.ErrorCode, "Media: getThumbnail: Operation Failed"));
		return;
	}
	if (arg2 != event_cancelled) {
		var thumbUrl = null;
		if (arg3.ReturnValue) {
			thumbUrl = arg3.ReturnValue.replace(/\\/g, "/");
			var fileScheme = "file://";
			thumbUrl = fileScheme + thumbUrl;
		}
		thumbnail_cb(thumbUrl);
	} 
	glob_obj.removeFromArray(arg1);
	}
	
// Code for getthumbnail
function __sp_media_getThumbnail(thumbnail_cb,thumbnailInfo, thumbnail_errcbk)
{
	//alert("In __sp_media_getThumbnail");
	// Checking validation for callback method
	if(!thumbnail_cb)
  	{
  		throw new DeviceException(this.error.MISSING_ARG_ERR, "Media:getThumbnail:Callback is missing");
  	}
  	else if(typeof thumbnail_cb != "function")	//here we check if the type of callback is function. This case is useful when arbitrary values are passed to callback
  	{
  		throw new DeviceException(this.error.INVALID_ARG_ERR, "Media:getList:Callback is invalid");
  	}
	if(thumbnail_errcbk)
	{ 
		var err_cb = thumbnail_errcbk;
		//alert(" In thumbnail_errcbk");
		if(typeof thumbnail_errcbk != 'function')
		{
			//alert(" thumbnail_errcbk != function");
		   	throw new DeviceException(this.error.INVALID_ARG_ERR, "Media: getThumbnail: error callback is invalid");
			//err_cb(new DeviceException(INVALID_ARG_ERR, "Media: getThumbnail: error callback is invalid"));
		}
	}


	// Creating url and thumbnail
	var inputParam = {};
	modifyObjectBaseProp(inputParam);
	if (thumbnailInfo) {
		if(typeof thumbnailInfo != "object" ){			
			throw new DeviceException(this.error.INVALID_ARG_ERR, "Media:getThumbnail:thumbnailInfo is of invalid type object");
			}
		if (thumbnailInfo.uri) {			
			if (typeof thumbnailInfo.uri != "string") {				
				throw new DeviceException(this.error.INVALID_ARG_ERR, "Media:getThumbnail:uri is not of type string");
				
				}
			if (thumbnailInfo.uri.search("file://") == 0) {				
				url = thumbnailInfo.uri.slice(FILESCHMLEN);
				inputParam.Url = url.replace(/\//g, "\\");
			}
			else {				
				throw new DeviceException(this.error.INVALID_ARG_ERR, "Media:getThumbnail:uri is not in file protocol");
			}
		}
		else {			
			throw new DeviceException(this.error.MISSING_ARG_ERR, "Media:getThumbnail:uri is missing");
		}
	}
	else{		
		throw new DeviceException(this.error.MISSING_ARG_ERR, "Media:thumbnailInfo is missing");
		}	
	//for thumbanilsize

	if ( thumbnailInfo.size == null ||  thumbnailInfo.size == "" ){
		//alert(" size is null");
		throw new DeviceException(this.error.INVALID_ARG_ERR, "Media:getThumbnail:size is not of type Object");
	}
	if (thumbnailInfo.size) {
	
		// chekcing if sise is object or not
		//alert(" In thumbnail size");
		if(typeof thumbnailInfo.size != "object" ){
				throw new DeviceException(this.error.INVALID_ARG_ERR, "Media:getThumbnail:size is not of type Object");
		}
		if((typeof thumbnailInfo.size.width == "undefined") && ( typeof thumbnailInfo.size.height == "undefined"))
			{
			throw new DeviceException(this.error.MISSING_ARG_ERR, "Media:thumbnailInfo should have atleast width or height");	
			}
		else{
			var thumbnailsize = {};
			modifyObjectBaseProp(thumbnailsize);
			if (typeof thumbnailInfo.size.width != "undefined") // Need to put check on this
				{
				thumbnailsize.width = thumbnailInfo.size.width;
				}
			if (typeof thumbnailInfo.size.height != "undefined") 
				{
				thumbnailsize.height = thumbnailInfo.size.height;
				}
			inputParam.ThumbnailSize = thumbnailsize;
			delete thumbnailsize;
			}
	
		}

  try {    
   	temp_scb = thumbnail_cb;
	temp_ecb = thumbnail_errcbk;
    var rval = this.so.IDataSource.GetThumbnail(inputParam, this.getThumbnailCb);
	//alert(" errorcode = "+rval.ErrorCode);
	if (rval.TransactionID) {
        glob_obj.addToGlobalArray(rval.TransactionID, thumbnail_cb, thumbnail_errcbk);
    }
	delete inputParam;

    if(rval.ErrorCode != 0){
		//alert(" In if loop = "+ MapErrorCode[rval.ErrorCode]);
		//alert(" In not supported= "+ this.error.NOT_SUPPORTED_ERR);
		//alert(" in if of rval.errorcode" +MapErrorCode[rval.ErrorCode]);	
		//alert(" MISSING_ARG_ERR = " +MapErrorCode[1003]);	
		//var errmsg = null;
		//errmsg = splitErrorMessage(rval.ErrorMessage); 		
    	  switch(MapErrorCode[rval.ErrorCode]){		  	        				
        				case this.error.MISSING_ARG_ERR :
						{
							//alert(" in switch MISSING_ARG_ERR");
							thumbnail_errcbk(new DeviceException(this.error.MISSING_ARG_ERR, "Media: getThumbnail: Operation Failed"));
						}
						break;	
						case this.error.NOT_SUPPORTED_ERR :	{
							//alert(" In not supported");
							thumbnail_errcbk( new DeviceException(MapErrorCode[rval.ErrorCode], "Media:getThumbnail:Operation failed"));
						}						
						break;				
						case this.error.INVALID_ARG_ERR :												
						throw new DeviceException(MapErrorCode[rval.ErrorCode], "Media:getThumbnail:Operation failed");							
						break;
						default:	
							//throw new DeviceException(MapErrorCode[rval.ErrorCode], "Media:getThumbnail:Operation failed");					
							//thumbnail_errcbk
							if (thumbnail_errcbk) {
							
								thumbnail_errcbk(new DeviceException(MapErrorCode[rval.ErrorCode], "Media:getThumbnail:Operation failed"));
							}
							
							else {
							
								throw new DeviceException(MapErrorCode[rval.ErrorCode], "Media:getThumbnail:Operation failed");
							}
							
						
    	  }		  	
    }	
  return rval.TransactionID;
  }
  catch (e) {		
  		//alert(" In exception");
    __device_handle_exception(e, '__sp_media_getThumbnail: '+e);
  }  		
	
}

function __sp_media_addStreamUri(uri)
	{
	throw new DeviceException(MapErrorCode[rval.ErrorCode],"Media:addStreamUri:Not Supported");	
	}
function __sp_media_deleteStreamUri(uri)
	{
	throw new DeviceException(MapErrorCode[rval.ErrorCode], "Media:deleteStreamUri:Not Supported");	
	}

function 	__sp_media_refreshMediaDb(uri)
{

}

function __sp_media_cancel(transactionId)
{
	try{
		var rval = this.so.IDataSource.Cancel(transactionId);
	
	    if(rval.ErrorCode != 0){
    	  switch(rval.ErrorCode){
        				//case err_missing_argument :
        				//case err_bad_argument :
						//case err_InvalidService_Argument :
						//case err_ServiceNotSupported :
							case this.error.MISSING_ARG_ERR :
							case this.error.INVALID_ARG_ERR :							
							case this.error.NOT_SUPPORTED_ERR :
						if(rval.ErrorMessage){ 
            			var err_msg = splitErrorMessage(rval.ErrorMessage); 	
			            throw new DeviceException(MapErrorCode[rval.ErrorCode],"Media:cancel:"+err_msg);						    
						}
						else{
						throw new DeviceException(MapErrorCode[rval.ErrorCode], "Media:cancel:Operation failed");	
						}
						break;
						default:
						throw new DeviceException(MapErrorCode[rval.ErrorCode], "Media:cancel:Operation failed");
    	  }
    	}

	}
	catch(e){
	   __device_handle_exception(e, '__sp_media_refreshMediaDb: '+e);
	}
}

function __sp_media_instance(){
  
  //Descriptor
  this.descriptor = new __sp_media_descriptor();
  //Extended methods
  this.SORT_ASCENDING = 0;
  this.SORT_DESCENDING = 1;
  this.getList = __sp_media_getList;
  this.getListMediaCb = __sp_media_getList_cb;
  //Method for gethumbnail

  this.getThumbnail = __sp_media_getThumbnail;
  this.getThumbnailCb = __sp_media_getThumbnail_cb;
	// Method for addStreamuri
  this.addStreamUri = __sp_media_addStreamUri;
  
  //Method for deleteStreamUri
  this.deleteStreamUri = __sp_media_deleteStreamUri;
  
  //Method for refreshMediaDb
  this.refreshMediaDb = __sp_media_refreshMediaDb;
  
  //Method for cancel
  this.cancel = __sp_media_cancel;
  //Private data
  this.error = new DeviceException(0, "Dummy");
  try {
    //__device_debug("Trying media service");
      this.so = device.getServiceObject("Service.MediaManagement", "IDataSource");
    //__device_debug("Got media service object");    
  }
  catch (e){
    this.so = null;
    __device_handle_exception(e, "media service not available");
  }
}