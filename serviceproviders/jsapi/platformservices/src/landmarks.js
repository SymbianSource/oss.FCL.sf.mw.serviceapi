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

var __device_landmarks_service_entry = {
    "name": null,
    "version": null,
    "proto": __device_landmarks,
    "descriptor": __device_landmarks_descriptor,
    "providers": [{
        "descriptor": __sp_landmarks_descriptor,
        "instance": __sp_landmarks_instance
    }]
};

// Private location prototype: called from service factory
function __device_landmarks(provider){
    //Private properties
    this.provider = provider;
    //Read-only properties
    this.interfaceName = provider.descriptor.interfaceName;
    this.version = provider.descriptor.version;
    //Core methods
    this.startEditor = __device_landmarks_startEditor;
    //Extended methods
    this.getCategories = __device_landmarks_getCategories;
    this.getLandmarks = __device_landmarks_getLandmarks;
    this.addCategory = __device_landmarks_add_category;
    this.updateCategory = __device_landmarks_update_category;
    this.updateLandmark = __device_landmarks_update_landmark;
    this.addLandmark = __device_landmarks_add_landmark;
    this.deleteCategory = __device_landmarks_delete_category;
    this.deleteLandmark = __device_landmarks_delete_landmark;
    this.importLandmarks = __device_landmarks_import_landmarks;
    this.exportLandmarks = __device_landmarks_export_landmarks;
    this.organizeLandmarks = __device_landmarks_organize_landmarks;
    ;
    this.cancel = __device_landmarks_cancel;
}

function __device_landmarks_descriptor(provider){
    this.interfaceName = provider.interfaceName;
    this.version = provider.version;
}

function __device_landmarks_startEditor(callback, entry){
    this.provider.startEditor(callback, entry);
}

function __device_landmarks_getCategories(callback, name, errorcb){
    return this.provider.getCategories(callback, name, errorcb);
}


function __device_landmarks_getLandmarks(callback, match, errcb){
    return this.provider.getLandmarks(callback, match, errcb);
}

function __device_landmarks_add_category(callback, categoryItem, ErrorCallback){
    return this.provider.addCategory(callback, categoryItem, ErrorCallback);
}


function __device_landmarks_add_landmark(callback, landmarkItem, ErrorCallback){
    return this.provider.addLandmark(callback, landmarkItem, ErrorCallback);
}

function __device_landmarks_delete_category(callback, categoryId, ErrorCallback){
    return this.provider.deleteCategory(callback, categoryId, ErrorCallback);
}

function __device_landmarks_delete_landmark(callback, landmarkId, ErrorCallback){
    return this.provider.deleteLandmark(callback, landmarkId, ErrorCallback);
}

function __device_landmarks_update_landmark(callback, landmarkItem, ErrorCallback){
    return this.provider.updateLandmark(callback, landmarkItem, ErrorCallback);
}

function __device_landmarks_update_category(callback, categoryItem, ErrorCallback){
    return this.provider.updateCategory(callback, categoryItem, ErrorCallback);
}

function __device_landmarks_import_landmarks(callback, sourceFileUri, mimetype, ErrorCallback){
    return this.provider.importLandmarks(callback, sourceFileUri, mimetype, ErrorCallback);
}

function __device_landmarks_export_landmarks(callback, landmarkIdList, destFileUri, mimetype, ErrorCallback){
    return this.provider.exportLandmarks(callback, landmarkIdList, destFileUri, mimetype, ErrorCallback);
}

function __device_landmarks_organize_landmarks(callback, landmarkIdList, categoryId, associate, ErrorCallback){
    return this.provider.organizeLandmarks(callback, landmarkIdList, categoryId, associate, ErrorCallback);
}

function __device_landmarks_cancel(transactionId){
    return this.provider.cancel(transactionId);
}


//utillity function for converting error code from PS to CJSE codes
//this gets used in communicating errors via error callback
var err_missing_argument = 1003;
var err_bad_argument = 1002;
var err_ServiceNotSupported = 1004;
var err_InvalidService_Argument = 1000;
function convertFromPS2JS(PSCode){
    var JSCodeValue = new DeviceAPIError(0, "dummy");
    var JsErrCode;
    switch (PSCode) {
        case 1016:
            JsErrCode = JSCodeValue.TIMEOUT_ERR;
            break;
        case 1012:
            JsErrCode = JSCodeValue.DATA_NOT_FOUND_ERR;
            break;
        case 1010:
            JsErrCode = JSCodeValue.DATA_ALREADY_EXISTS_ERR;
            break;
        case 1009:
            JsErrCode = JSCodeValue.SERVICE_BUSY_ERR;
            break;
        case 1005:
            JsErrCode = JSCodeValue.SERVICE_IN_USE_ERR;
            break;
        default:
            JsErrCode = 1001;
    }
    return JsErrCode;
}

// S60 sp-based landmarks provider

function __sp_landmarks_descriptor(){
    //Read-only properties
    this.interfaceName = "landmarks";
    if (window.__Service_Interface_Ver) 
        this.version = __Service_Interface_Ver;
    else 
        this.version = 1.0;
    //Class-static properties 
}

function __sp_landmarks_instance(){
    //Descriptor
    this.descriptor = new __sp_landmarks_descriptor();
    //Core methods
    this.startEditor = __sp_landmarks_startEditor;
    //Extended methods
    this.getCategories = __sp_landmarks_category_getList;
    this.getCategoriesCb = __sp_landmarks_category_getList_cb;
    
    this.addCategory = __sp_landmarks_category_add;
    this.addCategoryCb = __sp_landmarks_category_add_cb;
    
    this.updateCategory = __sp_landmarks_category_update;
    this.updateCategoryCb = __sp_landmarks_category_update_cb;
    
    this.deleteCategory = __sp_landmarks_category_delete;
    this.deleteCategoryCb = __sp_landmarks_category_delete_cb;
    
    this.getLandmarks = __sp_landmarks_getList;
    this.getLandmarksCb = __sp_landmarks_getList_cb;
    
    this.addLandmark = __sp_landmarks_add;
    this.addLandmarkCb = __sp_landmarks_add_cb;
    
    this.updateLandmark = __sp_landmarks_update;
    this.updateLandmarkCb = __sp_landmarks_update_cb;
    
    this.deleteLandmark = __sp_landmarks_delete;
    this.deleteLandmarkCb = __sp_landmarks_delete_cb;
    
    this.importLandmarks = __sp_landmarks_import;
    this.importLandmarksCb = __sp_landmarks_import_cb;
    
    this.exportLandmarks = __sp_landmarks_export;
    this.exportLandmarksCb = __sp_landmarks_export_cb;
    
    this.organizeLandmarks = __sp_landmarks_organize;
    this.organizeLandmarksCb = __sp_landmarks_organize_cb;
    
    this.temporarySCb = null;
    this.temporaryECb = null;
    
    this.cancel = __sp_landmarks_cancel;
    //Private data 
    try {
        this.so = device.getServiceObject("Service.Landmarks", "IDataSource");
    } 
    catch (e) {
        __device_handle_exception(e, "Landmarks service not available");
    }
}

// TBD: We MUST get rid of this when underlying sp supports category names directly
// For one thing this is not localized!

var __SP_CATEGORY_MIN_LOCAL_ID = 16;

var __sp_category_list = [{
    id: 1,
    globalId: 3000,
    name: "Accommodation"
}, {
    id: 2,
    globalId: 6000,
    name: "Businesses"
}, {
    id: 3,
    globalId: 9000,
    name: "Telecommunications"
}, {
    id: 4,
    globalId: 12000,
    name: "Education"
}, {
    id: 5,
    globalId: 15000,
    name: "Entertainment"
}, {
    id: 6,
    globalId: 18000,
    name: "Food and drink"
}, {
    id: 7,
    globalId: 21000,
    name: "Geographical locations"
}, {
    id: 8,
    globalId: 24000,
    name: "Outdoor activities"
}, {
    id: 9,
    globalId: 27000,
    name: "People"
}, {
    id: 10,
    globalId: 30000,
    name: "Public services"
}, {
    id: 11,
    globalId: 33000,
    name: "Places of worship"
}, {
    id: 12,
    globalId: 36000,
    name: "Shopping"
}, {
    id: 13,
    globalId: 39000,
    name: "Sightseeing"
}, {
    id: 14,
    globalId: 42000,
    name: "Sports"
}, {
    id: 15,
    globalId: 45000,
    name: "Transport"
}];

/* ------ Wrap sp iterators ------- */

function __sp_landmarks_category_iterator(js_iterator){
    this.iter = js_iterator;
    this.next = __sp_landmarks_category_iterator_get_next;
    this.hasNext = __sp_landmarks_category_iterator_has_next;
    
    //indicate whether iterator has been populated atleast once
    this.hasElement = false;
    //refers to the current category item
    this.catItem = null;
    this.close = __sp_landmarks_category_close;
}

function __sp_landmarks_category_close(){
    this.iter.close();
}

function __sp_landmarks_category_iterator_has_next(){
    if (this.hasElement) {
        if (this.catItem !== null) {
            return true;
        }
        else {
            return false;
        }
        
    }
    else {
        this.catItem = this.iter.getNext();
        this.hasElement = true;
        if (typeof this.catItem == "undefined" || this.catItem == null) {
            this.catItem = null;
            return false;
        }
        else {
            return true;
        }
    }
}

function __sp_landmarks_category_iterator_get_next(){
    if (this.hasElement) {
        var tempitem = new Object();
        tempitem = this.catItem;
        //update
        this.catItem = this.iter.getNext();
        if (typeof(this.catItem) == "undefined") {
            this.catItem = null;
        }
        
        if(tempitem){
            return new __sp_device_category_obj(tempitem);
        }
        else {
            return null;
        }
    }
    else {
        this.catItem = this.iter.getNext();
        if (typeof this.catItem == "undefined" || this.catItem == null) {
            this.hasElement = true;
            this.catItem = null;
            return null;
        }
        else {
            this.hasElement = true;
            var tempObject = new Object();
            tempObject = this.lmItem;
            //update 
            
            this.catItem = this.iter.getNext();
            if (typeof(this.catItem) == "undefined") {
                this.catItem = null;
            }
            return new __sp_device_category_obj(tempObject);
        }
    }
}

//landmark iterator
function __sp_landmarks_iterator(js_iterator){
    this.iter = js_iterator;
    this.next = __sp_landmarks_iterator_get_next;
    this.hasNext = __sp_landmarks_iterator_has_next;
    
    //indicate whether iterator has been populated atleast once
    this.hasElement = false;
    //refers to the current landmark item
    this.lmItem = null;
    this.close = __sp_landmarks_landmarkitem_close;
}

function __sp_landmarks_landmarkitem_close(){
    this.iter.close();
}

// Parameter objects
//converts from LIW position to JS wrapper positionfield object
function __sp_device_landmark_location_obj(sp_location){
    this.longitude = (sp_location.Longitude == undefined) ? null : sp_location.Longitude;
    this.latitude = (sp_location.Latitude == undefined) ? null : sp_location.Latitude;
    if (sp_location.Altitude) 
        this.altitude = sp_location.Altitude;
    if (sp_location.HAccuracy) 
        this.hAccuracy = sp_location.HAccuracy;
    if (sp_location.VAccuracy) 
        this.vAccuracy = sp_location.VAccuracy;
}

//this is being used for converting position field in criteria for getLandmarks.
function __sp_landmark_position_obj(location){
    if ((location.longitude !== undefined) &&
    (location.longitude !== null) &&
    (location.longitude !== "")) {
        this.Longitude = location.longitude;
    }
    if ((location.latitude !== undefined) &&
    (location.latitude !== null) &&
    (location.latitude !== "")) {
        this.Latitude = location.latitude;
    }
    
    
}

//use this to convert from positon filed of landmarkitem to convert it to position field 
//in LIW of landmark item
function __sp_landmark_position_obj_fromJS_2LIW(location){
	var error = new DeviceAPIError(0, "dummy");
	if (typeof(location) != "object"){
		throw new DeviceAPIError(error.INVALID_ARG_ERR, 'position must be of type object');	
	}
	var loFound = false;
	var laFound = false;
	if ((location.longitude !== undefined)
	     && (location.longitude !== null)
		 && (location.longitude !== "")){
		this.Longitude = location.longitude;
		loFound = true;	 
	}
	if ((location.latitude !== undefined)
	     && (location.latitude !== null)
		 && (location.latitude !== "")){
		this.Latitude = location.latitude;
		laFound = true;	 
	}
    if (!(loFound && laFound)) {
		throw new DeviceAPIError(error.MISSING_ARG_ERR, 'missing position field');
	}
    if (location.altitude) 
        this.Altitude = location.altitude;
    if (location.hAccuracy) 
        this.HAccuracy = location.hAccuracy;
    if (location.vAccuracy) 
        this.VAccuracy = location.vAccuracy;
}

function __sp_landmark_bounded_area_obj(area){

    var error = new DeviceAPIError(0, "dummy");
    var c1Found = false;
    var c2Found = false;
    if ((area.coordinate1 !== undefined) &&
    (area.coordinate1 !== null) &&
    (area.coordinate1 !== "")) {
        if (typeof(area.coordinate1) != "object") {
            throw new DeviceAPIError(error.INVALID_ARG_ERR, 'coordinate1 must be an object');
        }
        else {
            var latFound = false;
            var longFound = false;
            if ((area.coordinate1.latitude !== undefined) &&
            (area.coordinate1.latitude !== null) &&
            (area.coordinate1.latitude !== "")) {
                this.NorthLatitude = area.coordinate1.latitude;
                latFound = true;
            }
            
            
            if ((area.coordinate1.longitude !== undefined) &&
            (area.coordinate1.longitude !== null) &&
            (area.coordinate1.longitude !== "")) {
                this.EastLongitude = area.coordinate1.longitude;
                longFound = true;
            }
            if (!(latFound && longFound)) {
                throw new DeviceAPIError(error.MISSING_ARG_ERR, 'missing position field');
            }
            c1Found = true;
            
        }
        
        
    }
    if ((area.coordinate2 !== undefined) &&
    (area.coordinate2 !== null) &&
    (area.coordinate2 !== "")) {
        if (typeof(area.coordinate2) != "object") {
            throw new DeviceAPIError(error.INVALID_ARG_ERR, 'coordinate2 must be an object');
        }
        else {
            var latFound = false;
            var longFound = false;
            if ((area.coordinate2.latitude !== undefined) &&
            (area.coordinate2.latitude !== null) &&
            (area.coordinate2.latitude !== "")) {
                this.SouthLatitude = area.coordinate2.latitude;
                latFound = true;
            }
            
            
            if ((area.coordinate2.longitude !== undefined) &&
            (area.coordinate2.longitude !== null) &&
            (area.coordinate2.longitude !== "")) {
                this.WestLongitude = area.coordinate2.longitude;
                longFound = true;
            }
            if (!(latFound && longFound)) {
                throw new DeviceAPIError(error.MISSING_ARG_ERR, 'missing position field');
            }
            c2Found = true;
            
        }
        
        
    }
    if (!(c1Found && c2Found)) {
        throw new DeviceAPIError(error.MISSING_ARG_ERR, 'missing position field');
    }
    
}


//converts from LIW address to JS wrapper AddressDetails

function __sp_device_landmark_address_obj(sp_address){
    if (sp_address.Street) 
        this.street = sp_address.Street;
    if (sp_address.City) 
        this.city = sp_address.City;
    if (sp_address.state) 
        this.state = sp_address.state;
    if (sp_address.AreaCode) 
        this.postalCode = sp_address.AreaCode;
    if (sp_address.Country) 
        this.country = sp_address.Country;
    if (sp_address.BuildingName) 
        this.building = sp_address.BuildingName;
    if (sp_address.Telephone) 
        this.phone = sp_address.Telephone;
}

// sp problem: no way to specify state/province?

function __sp_landmark_address_obj(address){
	var error = new DeviceAPIError(0, "dummy");
	if (typeof(address) != "object"){
		throw new DeviceAPIError(error.MISSING_ARG_ERR, 'address must be of type object');	
	}
	
    if (address.street !== undefined){
		if (address.street === null){
			this.Street = "";	
		}
		else {
			this.Street = address.street;	
		}
			
	} 
	if (address.city !== undefined){
		if (address.city === null){
			this.City = "";	
		}
		else {
			this.City = address.city;	
		}
			
	} 
	if (address.state !== undefined){
		if (address.state === null){
			this.state = "";	
		}
		else {
			this.state = address.state;	
		}
			
	} 
	if (address.postalCode !== undefined){
		if (address.postalCode === null){
			this.AreaCode = "";	
		}
		else {
			this.AreaCode = address.postalCode;	
		}
			
	} 
	if (address.country !== undefined){
		if (address.country === null){
			this.Country = "";	
		}
		else {
			this.Country = address.country;	
		}
			
	} 
	if (address.building !== undefined){
		if (address.building === null){
			this.BuildingName = "";	
		}
		else {
			this.BuildingName = address.building;	
		}
			
	} 
	if (address.phone !== undefined){
		if (address.phone === null){
			this.Telephone = "";	
		}
		else {
			this.Telephone = address.phone;	
		}
			
	} 
    
}

function __sp_add_category_ids_for_names(names){
    var errObj = new DeviceAPIError(0, "dummy");
    var retval = new Array();
    
    for (var i in names) {
        if ((names[i] !== undefined) &&
        (names[i] !== "") &&
        (names[i] !== null)) {
            if (typeof(names[i]) != "string") {
                throw new DeviceAPIError(errObj.INVALID_ARG_ERR, 'category should be of type string');
            }
            else {
                retval.push(names[i].toString());
            }
            
            
        }
        
    }
    return retval;
}

function __sp_get_category_ids_for_names(names){
    var errObj = new DeviceAPIError(0, "dummy");
    var retval = new Array();
    var isCatGlobal = 0;// to check if the category passed is a global category
    for (var i in names) {
        if (typeof(names[i]) != "string") {
            throw new DeviceAPIError(errObj.INVALID_ARG_ERR, 'category should be of type string');
        }
        for (var ii in __sp_category_list) {
            //__device_debug(names[i] + " ==? " + __sp_category_list[ii].name);
            
            if (__sp_category_list[ii].name.toLowerCase() == names[i].toLowerCase()) {
                retval.push(__sp_category_list[ii].id.toString());
                isCatGlobal = 1;
            }
        }
        if (isCatGlobal == 0) {
            return null;
        }
        isCatGlobal = 0;// set the flag to 0
    }
    return retval;
}

//converts from LIW to JS wrapper paramater
function __sp_device_landmark_obj(sp_landmark){
    this.landmarkId = sp_landmark.id;
    if (sp_landmark.LandmarkName) {
        this.name = sp_landmark.LandmarkName;
    }
    if (sp_landmark.LandmarkDesc) {
        this.description = sp_landmark.LandmarkDesc;
    }
    if (sp_landmark.CoverageRadius) {
        this.coverageRadius = sp_landmark.CoverageRadius;
    }
    if (sp_landmark.LandmarkPosition) {
        this.position = new __sp_device_landmark_location_obj(sp_landmark.LandmarkPosition);
    }
    if (sp_landmark.CategoryInfo) {
        this.categoryIds = sp_landmark.CategoryInfo;
    }
    
    if (sp_landmark.LandmarkFields) {
        this.address = new __sp_device_landmark_address_obj(sp_landmark.LandmarkFields);
    }
}

function __sp_landmarks_addLocality(add){
    var errLoc = new DeviceAPIError(0, "dummy");
    if (typeof(add) != "object") {
        throw new DeviceAPIError(errLoc.INVALID_ARG_ERR, 'address should be of type object');
    }
    if ((add.street !== undefined) &&
    (add.street !== null) &&
    (add.street !== "")) {
    
        this.Street = add.street;
        
    }
    if ((add.city !== undefined) &&
    (add.city !== null) &&
    (add.city !== "")) {
    
        this.City = add.city;
        
    }
    if ((add.state !== undefined) &&
    (add.state !== null) &&
    (add.state !== "")) {
    
        this.state = add.state;
        
    }
    if ((add.postalCode !== undefined) &&
    (add.postalCode !== null) &&
    (add.postalCode !== "")) {
    
        this.AreaCode = add.postalCode;
        
    }
    if ((add.country !== undefined) &&
    (add.country !== null) &&
    (add.country !== "")) {
    
        this.Country = add.country;
        
    }
    if ((add.building !== undefined) &&
    (add.building !== null) &&
    (add.building !== "")) {
    
        this.BuildingName = add.building;
        
    }
    if ((add.phone !== undefined) &&
    (add.phone !== null) &&
    (add.phone !== "")) {
    
        this.Telephone = add.phone;
        
    }
}

function __sp_landmarks_addPosition(pos){
    var errPos = new DeviceAPIError(0, "dummy");
    if (typeof(pos) != "object") {
        throw new DeviceAPIError(errPos.INVALID_ARG_ERR, 'position should be of type object');
    }
    
    if ((pos.longitude !== undefined) &&
    (pos.longitude !== null) &&
    (pos.longitude !== "")) {
    
        this.Longitude = pos.longitude;
        //alert("longitude found");
    
    }
    if ((pos.latitude !== undefined) &&
    (pos.latitude !== null) &&
    (pos.latitude !== "")) {
    
        this.Latitude = pos.latitude;
        //alert("latitude found");
    
    }
    if ((pos.altitude !== undefined) &&
    (pos.altitude !== null) &&
    (pos.altitude !== "")) {
    
        this.Altitude = pos.altitude;
        
    }
    if ((pos.hAccuracy !== undefined) &&
    (pos.hAccuracy !== null) &&
    (pos.hAccuracy !== "")) {
    
        this.HAccuracy = pos.hAccuracy;
        
    }
    if ((pos.vAccuracy !== undefined) &&
    (pos.vAccuracy !== null) &&
    (pos.vAccuracy !== "")) {
    
        this.VAccuracy = pos.vAccuracy;
        
    }
}

function __sp_landmarks_addLmObject(lm){
    var posSet = false;
    var errObj = new DeviceAPIError(0, "dummy");
    if ((lm.name !== undefined) &&
    (lm.name !== null) &&
    (lm.name !== "")) {
    
        this.LandmarkName = lm.name;
        
    }
    if ((lm.description !== undefined) &&
    (lm.description !== null) &&
    (lm.description !== "")) {
    
        this.LandmarkDesc = lm.description;
        
    }
    if ((lm.position !== undefined) &&
    (lm.position !== null) &&
    (lm.position !== "")) {
        //alert("adding position");
        this.LandmarkPosition = new __sp_landmarks_addPosition(lm.position);
        posSet = true;
        //alert("pos="+this.position); 
    
    }
    if ((lm.coverageRadius !== undefined) &&
    (lm.coverageRadius !== null) &&
    (lm.coverageRadius !== "")) {
    
        if (posSet) {
            this.CoverageRadius = lm.coverageRadius;
        }
        else {
            throw new DeviceAPIError(errObj.MISSING_ARG_ERR, 'missing position');
        }
        
        
    }
    
    if ((lm.categoryIds !== undefined) &&
    (lm.categoryIds !== null) &&
    (lm.categoryIds !== "")) {
        if (typeof(lm.categoryIds) != 'object') {
            throw new DeviceAPIError(errObj.INVALID_ARG_ERR, 'categoryids should be of type object');
        }
        
        this.CategoryInfo = __sp_add_category_ids_for_names(lm.categoryIds);
        if (!this.CategoryInfo) {
            throw new DeviceAPIError(errObj.MISSING_ARG_ERR, 'invalid category');
            
        }
        
    }
    if ((lm.address !== undefined) &&
    (lm.address !== null) &&
    (lm.address !== "")) {
    
        this.LandmarkFields = new __sp_landmarks_addLocality(lm.address);
        
    }
    //dummy object
    this.dummyField = "dummyfield";
    
}

//this converts from JS landmarkitem to LIW landmark item
//being used by updateLandmark API
function __sp_landmark_obj(landmark, str){
	var error = new DeviceAPIError(0, "dummy");
    if (landmark.name !== undefined){
		if (landmark.name === null){
			this.LandmarkName = "";	
		}
		else {
			this.LandmarkName = landmark.name;	
		}
		
	} 
        
    if ((landmark.landmarkId === undefined)
	     || (landmark.landmarkId === null)
		 || (landmark.landmarkId === "")) 
		 throw new DeviceAPIError(error.MISSING_ARG_ERR, 'for updating; id must be supplied');
	else 
        this.id = landmark.landmarkId;
    if (landmark.description !== undefined){
		if (landmark.description === null){
			this.LandmarkDesc = "";	
		}
		else {
			this.LandmarkDesc = landmark.description;	
		}
		
	} 
        
    if (landmark.position) 
        this.LandmarkPosition = new __sp_landmark_position_obj_fromJS_2LIW(landmark.position);
    if (landmark.coverageRadius) 
        this.CoverageRadius = landmark.coverageRadius;
    if (landmark.categories) {
        this.CategoryInfo = __sp_get_category_ids_for_names(landmark.categories);
        if (!this.CategoryInfo) {
            throw new DeviceError("Landmarks: " + str + "Category is invalid", err_bad_argument);
        }
    }
    if (landmark.address) 
        this.LandmarkFields = new __sp_landmark_address_obj(landmark.address);
    
	this.temp = "dummy";
}

function __sp_landmarks_iterator_has_next(){
    if (this.hasElement) {
        if (this.lmItem !== null) {
            return true;
        }
        else {
            return false;
        }
        
    }
    else {
        this.lmItem = this.iter.getNext();
        this.hasElement = true;
        if (typeof this.lmItem == "undefined") {
            this.lmItem = null;
            return false;
        }
        else {
            return true;
        }
    }
}

function __sp_landmarks_iterator_get_next(){
    if (this.hasElement) {
        var tempitem = new Object();
        tempitem = this.lmItem;
        //update
        this.lmItem = this.iter.getNext();
        if (typeof(this.lmItem) == "undefined") {
            this.lmItem = null;
        }
        if(tempitem){
            return new __sp_device_landmark_obj(tempitem);
        }
        else{
            return null;
        } 
    }
    else {
        this.lmItem = this.iter.getNext();
        if (typeof this.lmItem == "undefined" || this.lmItem == null) {
            this.hasElement = true;
            this.lmItem = null;
            return null;
            
        }
        else {
            this.hasElement = true;
            var tempObject = new Object();
            tempObject = this.lmItem;
            //update 
            
            this.lmItem = this.iter.getNext();
            if (typeof(this.lmItem) == "undefined" || this.lmItem == null) {
                this.lmItem = null;
            }
            return new __sp_device_landmark_obj(tempObject);
        }
    }
    
}

function __sp_category_obj(category){
    if (category.name) 
        this.CategoryName = category.name;
    if (category.categoryId) 
        this.id = category.categoryId;
}

function __sp_device_category_obj(sp_category){
    this.categoryId = sp_category.id;
    this.name = sp_category.CategoryName;
}

/* --------- Public methods ---------- */


var LANDMARKS_APP_ID = 0x101F85A2;

// Apps should take care that this is not reinvoked
// while the editor is already running. 

function __sp_landmarks_startEditor(__success_cb, landmark_item, _error_cb){
    // internal variable used in this library implementation
    // This will made local variable when seperate module js files gets integrated in this file.
    error = new DeviceAPIError(0, "dummy");
    if ((__success_cb === undefined) ||
    (__success_cb === null) ||
    (__success_cb === "")) 
        throw new DeviceAPIError(error.MISSING_ARG_ERR, 'StartEditor:Missing Success Callback');
    
    if ((typeof __success_cb) != "function") 
        throw new DeviceAPIError(error.INVALID_ARG_ERR, 'StartEditor:Success Callback must be of type function');
    
    if (landmark_item !== undefined) {
        if ((landmark_item !== null) &&
        (landmark_item !== "")) {
        
            throw new DeviceAPIError(error.NOT_SUPPORTED_ERR, 'startEditor:landmark item is not supported');
            
        }
    }
    
    if ((_error_cb !== undefined) &&
    (_error_cb !== null) &&
    (_error_cb !== "")) {
        if ((typeof _error_cb) != "function") 
            throw new DeviceAPIError(error.INVALID_ARG_ERR, 'StartEditor:error callback must be of type function');
    }
    
    var LANDMARKS_APP_ID = 0x101F85A2;
    
    
    var __s60_start_and_wait_cb;
    
    function __s60_on_app_exit(){
        window.xwidget.onshow = null;
        if (__s60_start_and_wait_cb) {
            __s60_start_and_wait_cb();
        }
    }
    
    var finished = function(arg1, arg2, arg3){
        __success_cb(arg1, arg2, arg3);
    };
    __s60_start_and_wait(LANDMARKS_APP_ID, '', finished);
    
}

//oriiginal signature category_cb, name

function __sp_landmarks_category_getList_cb(arg1, arg2, arg3){
    var CbObj;
    var category_cb;
    var ErrorCallback;
    if (this.temporarySCb) {
        category_cb = this.temporarySCb;
        ErrorCallback = this.temporaryECb;
        this.temporarySCb = null;
        this.temporaryECb = null;
    }
    else {
        CbObj = glob_obj.getFromArray(arg1);
        if (CbObj) {
            category_cb = CbObj.success_cb;
            ErrorCallback = CbObj.error_cb;
        }
        
        else {
            alert("Landmarks: __sp_landmarks_category_getList_cb: Callback not found ");
            return;
        }
    }
    
    
    var iter = null;
    //if there is an error invoke user supplied error callback
    if (arg3.ErrorCode || (arg2 == 4)) { //indicates an error
        var scbErrCode = convertFromPS2JS(arg3.ErrorCode);
        var erroObject = new DeviceAPIError(scbErrCode, arg3.ErrorMessage);
        if (ErrorCallback) {
            ErrorCallback(erroObject);
        }
    }
    else {
        if (arg3.ReturnValue) {
            iter = new __sp_landmarks_category_iterator(arg3.ReturnValue);
            category_cb(iter);
        }
    }
    glob_obj.removeFromArray(arg1);
}

function __sp_landmarks_category_getList(category_cb, name, ErrorCallback){
    try {
        //alert("calling getlist");
        var error = new DeviceAPIError(0, "dummy");
        //succes callback must be defined and should be of the type function
        if ((category_cb === undefined) ||
        (category_cb === "") ||
        (category_cb === null)) {
            throw new DeviceAPIError(error.MISSING_ARG_ERR, 'callback is missing');
        }
        if (typeof(category_cb) != "function") {
            throw new DeviceAPIError(error.INVALID_ARG_ERR, 'invalid callback argument');
        }
        //check if errorcallback has been supplied and valid
        var errcbFound = false;
        if ((ErrorCallback !== undefined) &&
        (ErrorCallback !== null) &&
        (ErrorCallback !== "")) {
            if (typeof(ErrorCallback) != "function") {
                throw new DeviceAPIError(error.INVALID_ARG_ERR, 'invalid error callback argument');
            }
            else {
                errcbFound = true;
            }
        }
        //to check from here
        var criteria = new Object();
        modifyObjectBaseProp(criteria);
        criteria.Type = "Category";
        //if name has been supplied it must be of type string
        if ((name !== undefined) &&
        (name !== null) &&
        (name !== "")) {
        
            if (typeof(name) != "string") {
                throw new DeviceAPIError(error.INVALID_ARG_ERR, 'name must be a string');
            }
            
        }
        
        if (name) {
            criteria.Filter = new Object();
            modifyObjectBaseProp(criteria.Filter);
            criteria.Filter.CategoryName = name;
            criteria.Filter.PreviousMatchesOnly = false;
        }
        
        this.temporarySCb = category_cb;
        this.temporaryECb = ErrorCallback;
        
        var rval = this.so.IDataSource.GetList(criteria, this.getCategoriesCb);
        
        if (rval.TransactionID) {
            glob_obj.addToGlobalArray(rval.TransactionID, category_cb, ErrorCallback);
        }
        
        if (rval.ErrorCode != 0) {
            switch (rval.ErrorCode) {
                case 1003:
                    throw new DeviceAPIError(error.MISSING_ARG_ERR, rval.ErrorMessage);
                    break;
                case 1002:
                    throw new DeviceAPIError(error.INVALID_ARG_ERR, rval.ErrorMessage);
                    break;
                case 1004:
                    throw new DeviceAPIError(error.NOT_SUPPORTED_ERR, rval.ErrorMessage);
                    break;
                case 1000:
                    throw new DeviceAPIError(error.INVALID_ARG_ERR, rval.ErrorMessage);
                    break;
                default:
                    throw new DeviceAPIError(-101, "unknown error message");
                    
            }
            
        }
        return rval.TransactionID;
        
        
    } 
    catch (e) {
        //alert("exception from here");
        throw e;
    }
}

function __sp_landmarks_category_add_cb(arg1, arg2, arg3){
    var CbObj;
    var callback;
    var ErrorCallback;
    if (this.temporarySCb) {
        category_cb = this.temporarySCb;
        ErrorCallback = this.temporaryECb;
        this.temporarySCb = null;
        this.temporaryECb = null;
    }
    else {
        CbObj = glob_obj.getFromArray(arg1);
        if (CbObj) {
            callback = CbObj.success_cb;
            ErrorCallback = CbObj.error_cb;
        }
        
        else {
            alert("Landmarks: __sp_landmarks_category_add_cb: Callback not found ");
            return;
        }
    }
    
    
    var id = null;
    //if there is an error invoke user supplied error callback
    if (arg2 == 4 || arg3.ErrorCode) { //indicates an error
        var scbErrCode = convertFromPS2JS(arg3.ErrorCode);
        var erroObject = new DeviceAPIError(scbErrCode, arg3.ErrorMessage);
        if (ErrorCallback) {
            ErrorCallback(erroObject);
        }
    }
    else {
        if (arg3.ReturnValue) {
            id = arg3.ReturnValue;
        }
        //in case of success invoke user supplied scb
        callback(id);
    }
    glob_obj.removeFromArray(arg1);
}

//original signature : __sp_landmarks_category_add(cat)
function __sp_landmarks_category_add(callback, categoryItem, ErrorCallback){
    try {
        var error = new DeviceAPIError(0, "dummy");
        var isErrCB = true;//indicates a valid errocalback has been supplied
        if (callback === undefined) {
            throw new DeviceAPIError(error.MISSING_ARG_ERR, 'AddSucessCallback is missing');
        }
        else {
            if (((callback === null) ||
            (callback === "")) &&
            (typeof(callback) != "number")) {
                throw new DeviceAPIError(error.MISSING_ARG_ERR, 'AddSucessCallback is missing');
            }
            else 
                if (typeof(callback) != 'function') {
                    throw new DeviceAPIError(error.INVALID_ARG_ERR, 'invalid AddSucessCallback argument');
                }
        }
        if (categoryItem === undefined || categoryItem === null) {
            throw new DeviceAPIError(error.MISSING_ARG_ERR, 'CategoryItem is missing');
        }
        else 
            if (typeof(categoryItem) !== "object") {
                throw new DeviceAPIError(error.INVALID_ARG_ERR, 'invalid CategoryItem argument');
            }
        
        if ((ErrorCallback != undefined)) {
            if ((!ErrorCallback) &&
            (typeof(ErrorCallback) != "number")) {
                isErrCB = false;
            }
            else 
                if ((typeof(ErrorCallback) != 'function')) {
                    throw new DeviceAPIError(error.INVALID_ARG_ERR, 'invalid ErrorCallback callback');
                }
            
        }
        else {
            isErrCB = false;
        }
        
        var criteria = new Object();
        modifyObjectBaseProp(criteria);
        criteria.Type = "Category";
        criteria.Data = new __sp_category_obj(categoryItem);
		
		this.temporarySCb = callback;
        this.temporaryECb = ErrorCallback;
		
        var rval = this.so.IDataSource.Add(criteria, this.addCategoryCb);
        
        if (rval.TransactionID) {
            glob_obj.addToGlobalArray(rval.TransactionID, callback, ErrorCallback);
        }
        if (rval.ErrorCode != 0) {
            switch (rval.ErrorCode) {
                case err_missing_argument:
                    throw new DeviceAPIError(error.MISSING_ARG_ERR, rval.ErrorMessage);
                    break;
                case err_bad_argument:
                    throw new DeviceAPIError(error.INVALID_ARG_ERR, rval.ErrorMessage);
                    break;
                case err_ServiceNotSupported:
                    throw new DeviceAPIError(error.NOT_SUPPORTED_ERR, rval.ErrorMessage);
                    break;
                case err_InvalidService_Argument:
                    throw new DeviceAPIError(error.INVALID_ARG_ERR, rval.ErrorMessage);
                    break;
                default:
                    throw new DeviceAPIError(-101, "unknown error message");
            }
        }
        return rval.TransactionID;
    } 
    catch (e) {
        throw e;
    }
}

function __sp_landmarks_add_cb(arg1, arg2, arg3){
    var id = null;
    var CbObj;
    var callback;
    var ErrorCallback;
	if (this.temporarySCb) {
        category_cb = this.temporarySCb;
        ErrorCallback = this.temporaryECb;
        this.temporarySCb = null;
        this.temporaryECb = null;
    }
    else {
        CbObj = glob_obj.getFromArray(arg1);
        if (CbObj) {
            callback = CbObj.success_cb;
            ErrorCallback = CbObj.error_cb;
        }
        
        else {
            alert("Landmarks: __sp_landmarks_add_cb: Callback not found ");
            return;
        }
    }
    
    //if there is an error invoke user supplied error callback
    if (arg2 == 4 || arg3.ErrorCode) { //indicates an error
        var scbErrCode = convertFromPS2JS(arg3.ErrorCode);
        var erroObject = new DeviceAPIError(scbErrCode, arg3.ErrorMessage);
        if (ErrorCallback) {
            ErrorCallback(erroObject);
        }
    }
    else {
        if (arg3.ReturnValue) {
            id = arg3.ReturnValue;
        }
        //in case of success invoke user supplied scb
        callback(id);
    }
    glob_obj.removeFromArray(arg1);
}

//original signature : __sp_landmarks_add(landmark)
function __sp_landmarks_add(callback, landmarkItem, ErrorCallback){
    try {
        var error = new DeviceAPIError(0, "dummy");
        var isErrCB = true;//indicates a valid errocalback has been supplied
        if (callback === undefined) {
            throw new DeviceAPIError(error.MISSING_ARG_ERR, 'AddSucessCallback is missing');
        }
        else {
            if (((callback === null) ||
            (callback === "")) &&
            (typeof(callback) != "number")) {
                throw new DeviceAPIError(error.MISSING_ARG_ERR, 'AddSucessCallback is missing');
            }
            else 
                if (typeof(callback) != 'function') {
                    throw new DeviceAPIError(error.INVALID_ARG_ERR, 'invalid AddSucessCallback argument');
                }
        }
        if ((landmarkItem === undefined) ||
        (landmarkItem === null) ||
        (landmarkItem === "")) {
            throw new DeviceAPIError(error.MISSING_ARG_ERR, 'LandmarkItem is missing');
        }
        else 
            if (typeof(landmarkItem) !== "object") {
                throw new DeviceAPIError(error.INVALID_ARG_ERR, 'invalid LandmarkItem argument');
            }
        
        if ((ErrorCallback != undefined)) {
            if ((!ErrorCallback) &&
            (typeof(ErrorCallback) != "number")) {
                isErrCB = false;
            }
            else 
                if ((typeof(ErrorCallback) != 'function')) {
                    throw new DeviceAPIError(error.INVALID_ARG_ERR, 'invalid ErrorCallback callback');
                }
            
        }
        else {
            isErrCB = false;
        }
        
        
        var str = "addLandmark: ";
        var criteria = new Object();
        modifyObjectBaseProp(criteria);
        criteria.Type = "Landmark";
        //criteria.Data = new __sp_landmark_obj(landmarkItem, str);
        criteria.Data = new __sp_landmarks_addLmObject(landmarkItem);
        //alert("calling PS add");
		this.temporarySCb = callback;
        this.temporaryECb = ErrorCallback;
        var rval = this.so.IDataSource.Add(criteria, this.addLandmarkCb);
        //alert("rval.tid="+rval.TransactionID);
        //alert("rval.error="+rval.ErrorCode);
        if (rval.TransactionID) {
            glob_obj.addToGlobalArray(rval.TransactionID, callback, ErrorCallback);
        }
        
        if (rval.ErrorCode != 0) {
            switch (rval.ErrorCode) {
                case err_missing_argument:
                    throw new DeviceAPIError(error.MISSING_ARG_ERR, rval.ErrorMessage);
                    break;
                case err_bad_argument:
                    throw new DeviceAPIError(error.INVALID_ARG_ERR, rval.ErrorMessage);
                    break;
                case err_ServiceNotSupported:
                    throw new DeviceAPIError(error.NOT_SUPPORTED_ERR, rval.ErrorMessage);
                    break;
                case err_InvalidService_Argument:
                    throw new DeviceAPIError(error.INVALID_ARG_ERR, rval.ErrorMessage);
                    break;
                default:
                    throw new DeviceAPIError(-101, "unknown error message");
            }
        }
        return rval.TransactionID;
    } 
    catch (e) {
        throw e;
    }
}

function __sp_landmarks_delete_cb(arg1, arg2, arg3){
    var callback;
    var ErrorCallback;
    var CbObj;
	if (this.temporarySCb) {
        category_cb = this.temporarySCb;
        ErrorCallback = this.temporaryECb;
        this.temporarySCb = null;
        this.temporaryECb = null;
    }
    else {
        CbObj = glob_obj.getFromArray(arg1);
        if (CbObj) {
            callback = CbObj.success_cb;
            ErrorCallback = CbObj.error_cb;
        }
        
        else {
            alert("Landmarks: __sp_landmarks_delete_cb: Callback not found ");
            return;
        }
    }
    
    //if there is an error invoke user supplied error callback
    if (arg2 == 4 || arg3.ErrorCode) { //indicates an error
        var scbErrCode = convertFromPS2JS(arg3.ErrorCode);
        var erroObject = new DeviceAPIError(scbErrCode, arg3.ErrorMessage);
        if (ErrorCallback) {
            ErrorCallback(erroObject);
        }
    }
    else {
        //in case of success invoke user supplied scb
        callback();
    }
    glob_obj.removeFromArray(arg1);
}

//original signature : __sp_landmarks_delete(id)
function __sp_landmarks_delete(callback, landmarkId, ErrorCallback){
    try {
        var error = new DeviceAPIError(0, "dummy");
        var isErrCB = true;//indicates a valid errocalback has been supplied
        if (callback === undefined) {
            throw new DeviceAPIError(error.MISSING_ARG_ERR, 'SucessCallback is missing');
        }
        else {
            if (((callback === null) ||
            (callback === "")) &&
            (typeof(callback) != "number")) {
                throw new DeviceAPIError(error.MISSING_ARG_ERR, 'SucessCallback is missing');
            }
            else 
                if (typeof(callback) != 'function') {
                    throw new DeviceAPIError(error.INVALID_ARG_ERR, 'invalid SucessCallback argument');
                }
        }
        if (landmarkId === undefined || landmarkId === null) {
            throw new DeviceAPIError(error.MISSING_ARG_ERR, 'landmarkId is missing');
        }
        else 
            if (typeof(landmarkId) !== "string") {
                throw new DeviceAPIError(error.INVALID_ARG_ERR, 'invalid landmarkId argument');
            }
        
        if ((ErrorCallback != undefined)) {
            if ((!ErrorCallback) &&
            (typeof(ErrorCallback) != "number")) {
                isErrCB = false;
            }
            else 
                if ((typeof(ErrorCallback) != 'function')) {
                    throw new DeviceAPIError(error.INVALID_ARG_ERR, 'invalid ErrorCallback callback');
                }
            
        }
        else {
            isErrCB = false;
        }
        
        
        var criteria = new Object();
        modifyObjectBaseProp(criteria);
        criteria.Type = "Landmark";
        criteria.Data = new Object();
        modifyObjectBaseProp(criteria.Data);
        criteria.Data.id = landmarkId;
		
		this.temporarySCb = callback;
        this.temporaryECb = ErrorCallback;
		
        var rval = this.so.IDataSource.Delete(criteria, this.deleteLandmarkCb);
        if (rval.TransactionID) {
            glob_obj.addToGlobalArray(rval.TransactionID, callback, ErrorCallback);
        }
        if (rval.ErrorCode != 0) {
            switch (rval.ErrorCode) {
                case err_missing_argument:
                    throw new DeviceAPIError(error.MISSING_ARG_ERR, rval.ErrorMessage);
                    break;
                case err_bad_argument:
                    throw new DeviceAPIError(error.INVALID_ARG_ERR, rval.ErrorMessage);
                    break;
                case err_ServiceNotSupported:
                    throw new DeviceAPIError(error.NOT_SUPPORTED_ERR, rval.ErrorMessage);
                    break;
                case err_InvalidService_Argument:
                    throw new DeviceAPIError(error.INVALID_ARG_ERR, rval.ErrorMessage);
                    break;
                default:
                    throw new DeviceAPIError(-101, "unknown error message");
            }
        }
        return rval.TransactionID;
    } 
    catch (e) {
        throw e;
    }
}

function __sp_landmarks_update_cb(arg1, arg2, arg3){

    var callback;
    var ErrorCallback;
    var CbObj;
		if (this.temporarySCb) {
        category_cb = this.temporarySCb;
        ErrorCallback = this.temporaryECb;
        this.temporarySCb = null;
        this.temporaryECb = null;
    }
    else {
        CbObj = glob_obj.getFromArray(arg1);
        if (CbObj) {
            callback = CbObj.success_cb;
            ErrorCallback = CbObj.error_cb;
        }
        
        else {
            alert("Landmarks: __sp_landmarks_update_cb: Callback not found ");
            return;
        }
    }
    
    //if there is an error invoke user supplied error callback
    if (arg2 == 4 || arg3.ErrorCode) { //indicates an error
        var scbErrCode = convertFromPS2JS(arg3.ErrorCode);
        var erroObject = new DeviceAPIError(scbErrCode, arg3.ErrorMessage);
        if (ErrorCallback) {
            ErrorCallback(erroObject);
        }
    }
    else {
        //in case of success invoke user supplied scb
        callback();
    }
    glob_obj.removeFromArray(arg1);
}

//original signature : __sp_landmarks_update(landmark)
function __sp_landmarks_update(callback, landmarkItem, ErrorCallback){
    try {
        var error = new DeviceAPIError(0, "dummy");
        var isErrCB = true;//indicates a valid errocalback has been supplied
        if (callback === undefined) {
            throw new DeviceAPIError(error.MISSING_ARG_ERR, 'SuccessCallback is missing');
        }
        else {
            if (((callback === null) ||
            (callback === "")) &&
            (typeof(callback) != "number")) {
                throw new DeviceAPIError(error.MISSING_ARG_ERR, 'SuccessCallback is missing');
            }
            else 
                if (typeof(callback) != 'function') {
                    throw new DeviceAPIError(error.INVALID_ARG_ERR, 'invalid SuccessCallback argument');
                }
        }
        if (landmarkItem === undefined || landmarkItem === null || landmarkItem === "") {
            throw new DeviceAPIError(error.MISSING_ARG_ERR, 'LandmarkItem is missing');
        }
        else 
            if (typeof(landmarkItem) !== "object") {
                throw new DeviceAPIError(error.INVALID_ARG_ERR, 'invalid LandmarkItem argument');
            }
        
        if ((ErrorCallback != undefined)) {
            if ((!ErrorCallback) &&
            (typeof(ErrorCallback) != "number")) {
                isErrCB = false;
            }
            else 
                if ((typeof(ErrorCallback) != 'function')) {
                    throw new DeviceAPIError(error.INVALID_ARG_ERR, 'invalid ErrorCallback callback');
                }
            
        }
        else {
            isErrCB = false;
        }
        
        
        var str = "updateLandmark: ";
        var criteria = new Object();
        modifyObjectBaseProp(criteria);
        criteria.Type = "Landmark";
        criteria.Data = new __sp_landmark_obj(landmarkItem, str);
		
		this.temporarySCb = callback;
        this.temporaryECb = ErrorCallback;
        var rval = this.so.IDataSource.Add(criteria, this.updateLandmarkCb);
        if (rval.TransactionID) {
            glob_obj.addToGlobalArray(rval.TransactionID, callback, ErrorCallback);
        }
        
        if (rval.ErrorCode != 0) {
            switch (rval.ErrorCode) {
                case err_missing_argument:
                    throw new DeviceAPIError(error.MISSING_ARG_ERR, rval.ErrorMessage);
                    break;
                case err_bad_argument:
                    throw new DeviceAPIError(error.INVALID_ARG_ERR, rval.ErrorMessage);
                    break;
                case err_ServiceNotSupported:
                    throw new DeviceAPIError(error.NOT_SUPPORTED_ERR, rval.ErrorMessage);
                    break;
                case err_InvalidService_Argument:
                    throw new DeviceAPIError(error.INVALID_ARG_ERR, rval.ErrorMessage);
                    break;
                default:
                    throw new DeviceAPIError(-101, "unknown error message");
            }
        }
        return rval.TransactionID;
    } 
    catch (e) {
        throw e;
    }
}

function __sp_landmarks_category_update_cb(arg1, arg2, arg3){
    var callback;
    var ErrorCallback;
    var CbObj;
	if (this.temporarySCb) {
        category_cb = this.temporarySCb;
        ErrorCallback = this.temporaryECb;
        this.temporarySCb = null;
        this.temporaryECb = null;
    }
    else {
        CbObj = glob_obj.getFromArray(arg1);
        if (CbObj) {
            callback = CbObj.success_cb;
            ErrorCallback = CbObj.error_cb;
        }
        
        else {
            alert("Landmarks: __sp_landmarks_category_update_cb: Callback not found ");
            return;
        }
    }
    
    //if there is an error invoke user supplied error callback
    if (arg2 == 4 || arg3.ErrorCode) { //indicates an error
        var scbErrCode = convertFromPS2JS(arg3.ErrorCode);
        var erroObject = new DeviceAPIError(scbErrCode, arg3.ErrorMessage);
        if (ErrorCallback) {
            ErrorCallback(erroObject);
        }
    }
    else {
        //in case of success invoke user supplied scb
        callback();
    }
    glob_obj.removeFromArray(arg1);
}

function __sp_landmarks_category_update(callback, categoryItem, ErrorCallback){
    try {
        var error = new DeviceAPIError(0, "dummy");
        var isErrCB = true;//indicates a valid errocalback has been supplied
        if (callback === undefined) {
            throw new DeviceAPIError(error.MISSING_ARG_ERR, 'SucessCallback is missing');
        }
        else {
            if (((callback === null) ||
            (callback === "")) &&
            (typeof(callback) != "number")) {
                throw new DeviceAPIError(error.MISSING_ARG_ERR, 'SucessCallback is missing');
            }
            else 
                if (typeof(callback) != 'function') {
                    throw new DeviceAPIError(error.INVALID_ARG_ERR, 'invalid SucessCallback argument');
                }
        }
        if (categoryItem === undefined || categoryItem === null || categoryItem === "") {
            throw new DeviceAPIError(error.MISSING_ARG_ERR, 'CategoryItem is missing');
        }
        else 
            if (typeof(categoryItem) !== "object") {
                throw new DeviceAPIError(error.INVALID_ARG_ERR, 'invalid CategoryItem argument');
            }
        if ((categoryItem.categoryId === undefined)
		     || (categoryItem.categoryId === null)
			 || (categoryItem.categoryId === "")){
			 throw new DeviceAPIError(error.MISSING_ARG_ERR, 'categoryId is missing');	
		}
		if (typeof (categoryItem.categoryId) != "string") {
			throw new DeviceAPIError(error.INVALID_ARG_ERR, 'category Id must be a string');
		}
        if ((ErrorCallback != undefined)) {
            if ((!ErrorCallback) &&
            (typeof(ErrorCallback) != "number")) {
                isErrCB = false;
            }
            else 
                if ((typeof(ErrorCallback) != 'function')) {
                    throw new DeviceAPIError(error.INVALID_ARG_ERR, 'invalid ErrorCallback callback');
                }
        }
        else {
            isErrCB = false;
        }
        
        
        var criteria = new Object();
        modifyObjectBaseProp(criteria);
        criteria.Type = "Category";
        criteria.Data = new __sp_category_obj(categoryItem);
		
		this.temporarySCb = callback;
        this.temporaryECb = ErrorCallback;
		
        var rval = this.so.IDataSource.Add(criteria, this.updateCategoryCb);
        
        if (rval.TransactionID) {
            glob_obj.addToGlobalArray(rval.TransactionID, callback, ErrorCallback);
        }
        
        if (rval.ErrorCode != 0) {
            switch (rval.ErrorCode) {
                case err_missing_argument:
                    throw new DeviceAPIError(error.MISSING_ARG_ERR, rval.ErrorMessage);
                    break;
                case err_bad_argument:
                    throw new DeviceAPIError(error.INVALID_ARG_ERR, rval.ErrorMessage);
                    break;
                case err_ServiceNotSupported:
                    throw new DeviceAPIError(error.NOT_SUPPORTED_ERR, rval.ErrorMessage);
                    break;
                case err_InvalidService_Argument:
                    throw new DeviceAPIError(error.INVALID_ARG_ERR, rval.ErrorMessage);
                    break;
                default:
                    throw new DeviceAPIError(-101, "unknown error message");
            }
        }
        return rval.TransactionID;
    } 
    catch (e) {
        throw e;
    }
}

function __sp_landmarks_category_delete_cb(arg1, arg2, arg3){
    var callback;
    var ErrorCallback;
    var CbObj;
    if (this.temporarySCb) {
        category_cb = this.temporarySCb;
        ErrorCallback = this.temporaryECb;
        this.temporarySCb = null;
        this.temporaryECb = null;
    }
    else {
        CbObj = glob_obj.getFromArray(arg1);
        if (CbObj) {
            callback = CbObj.success_cb;
            ErrorCallback = CbObj.error_cb;
        }
        
        else {
            alert("Landmarks: __sp_landmarks_category_delete_cb: Callback not found ");
            return;
        }
    }
    
    //if there is an error invoke user supplied error callback
    if (arg2 == 4 || arg3.ErrorCode) { //indicates an error
        var scbErrCode = convertFromPS2JS(arg3.ErrorCode);
        var erroObject = new DeviceAPIError(scbErrCode, arg3.ErrorMessage);
        if (ErrorCallback) {
            ErrorCallback(erroObject);
        }
    }
    else {
        //in case of success invoke user supplied scb
        callback();
    }
    glob_obj.removeFromArray(arg1);
}

function __sp_landmarks_category_delete(callback, categoryId, ErrorCallback){
    try {
        var error = new DeviceAPIError(0, "dummy");
        var isErrCB = true;//indicates a valid errocalback has been supplied
        if (callback === undefined) {
            throw new DeviceAPIError(error.MISSING_ARG_ERR, 'SucessCallback is missing');
        }
        else {
            if (((callback === null) ||
            (callback === "")) &&
            (typeof(callback) != "number")) {
                throw new DeviceAPIError(error.MISSING_ARG_ERR, 'SucessCallback is missing');
            }
            else 
                if (typeof(callback) != 'function') {
                    throw new DeviceAPIError(error.INVALID_ARG_ERR, 'invalid SucessCallback argument');
                }
        }
        if (categoryId === undefined || categoryId === null) {
            throw new DeviceAPIError(error.MISSING_ARG_ERR, 'categoryId is missing');
        }
        else 
            if (typeof(categoryId) !== "string") {
                throw new DeviceAPIError(error.INVALID_ARG_ERR, 'invalid categoryId argument');
            }
        
        if ((ErrorCallback != undefined)) {
            if ((!ErrorCallback) &&
            (typeof(ErrorCallback) != "number")) {
                isErrCB = false;
            }
            else 
                if ((typeof(ErrorCallback) != 'function')) {
                    throw new DeviceAPIError(error.INVALID_ARG_ERR, 'invalid ErrorCallback callback');
                }
            
        }
        else {
            isErrCB = false;
        }
        
        
        var criteria = new Object();
        modifyObjectBaseProp(criteria);
        criteria.Type = "Category";
        criteria.Data = new Object();
        modifyObjectBaseProp(criteria.Data);
        criteria.Data.id = categoryId;
		
		this.temporarySCb = callback;
        this.temporaryECb = ErrorCallback;
		
        var rval = this.so.IDataSource.Delete(criteria, this.deleteCategoryCb);
        if (rval.TransactionID) {
            glob_obj.addToGlobalArray(rval.TransactionID, callback, ErrorCallback);
        }
        
        if (rval.ErrorCode != 0) {
            switch (rval.ErrorCode) {
                case err_missing_argument:
                    throw new DeviceAPIError(error.MISSING_ARG_ERR, rval.ErrorMessage);
                    break;
                case err_bad_argument:
                    throw new DeviceAPIError(error.INVALID_ARG_ERR, rval.ErrorMessage);
                    break;
                case err_ServiceNotSupported:
                    throw new DeviceAPIError(error.NOT_SUPPORTED_ERR, rval.ErrorMessage);
                    break;
                case err_InvalidService_Argument:
                    throw new DeviceAPIError(error.INVALID_ARG_ERR, rval.ErrorMessage);
                    break;
                default:
                    throw new DeviceAPIError(-101, "unknown error message");
            }
        }
        return rval.TransactionID;
    } 
    catch (e) {
        throw e;
    }
}

function __sp_landmarks_getList_cb(arg1, arg2, arg3){
    var iter = null;
    var callback;
    var ErrorCallback;
    var CbObj;
    if (this.temporarySCb) {
        category_cb = this.temporarySCb;
        ErrorCallback = this.temporaryECb;
        this.temporarySCb = null;
        this.temporaryECb = null;
    }
    else {
        CbObj = glob_obj.getFromArray(arg1);
        if (CbObj) {
            callback = CbObj.success_cb;
            ErrorCallback = CbObj.error_cb;
        }
        
        else {
            alert("Landmarks: __sp_landmarks_getList_cb: Callback not found ");
            return;
        }
    }
    
    //if there is an error invoke user supplied error callback
    if (arg3.ErrorCode || (arg2 == 4)) { //indicates an error
        var scbErrCode = convertFromPS2JS(arg3.ErrorCode);
        var erroObject = new DeviceAPIError(scbErrCode, arg3.ErrorMessage);
        if (ErrorCallback) {
            ErrorCallback(erroObject);
        }
    }
    else {
        if (arg3.ReturnValue) {
            iter = new __sp_landmarks_iterator(arg3.ReturnValue);
        }
        //in case of success invoke user supplied scb
        callback(iter);
    }
    glob_obj.removeFromArray(arg1);
}

function __sp_landmarks_getList(callback, matchObject, ErrorCallback){
    try {
        var error = new DeviceAPIError(0, "dummy");
        //test variable
        var isErrCB = false;//indicates a valid errocalback has not been supplied
        var isNameSearch = false;
        var isDefaultvalue = false;
        
        if ((callback === undefined) ||
        (callback === null) ||
        (callback === "")) {
        
            throw new DeviceAPIError(error.MISSING_ARG_ERR, 'SucessCallback is missing');
        }
        if (typeof(callback) != 'function') {
            throw new DeviceAPIError(error.INVALID_ARG_ERR, 'invalid SucessCallback argument');
        }
        if ((ErrorCallback !== undefined) &&
        (ErrorCallback !== "") &&
        (ErrorCallback !== null)) {
        
            if ((typeof(ErrorCallback) != 'function')) {
                throw new DeviceAPIError(error.INVALID_ARG_ERR, 'invalid error callback');
            }
            else {
                isErrCB = true;
            }
            
        }
        var criteria = new Object();
        modifyObjectBaseProp(criteria);
        criteria.Type = "Landmark";
        criteria.Filter = new Object();
        if ((matchObject === undefined) ||
        (matchObject === null) ||
        (matchObject === "")) {
        
            criteria.Filter.dummy = "dummy";
        }
        else 
            if (typeof(matchObject) == "string") {
            
                criteria.Filter.LandmarkName = matchObject;
            }
            else 
                if (typeof(matchObject) != "object") {
                    throw new DeviceAPIError(error.INVALID_ARG_ERR, 'invalid match criteria');
                }
                else {
                    if ((matchObject.name !== undefined) &&
                    (matchObject.name !== null) &&
                    (matchObject.name !== "")) 
                        criteria.Filter.LandmarkName = matchObject.name;
                    if ((matchObject.description !== undefined) &&
                    (matchObject.description !== null) &&
                    (matchObject.description !== "")) 
                        criteria.Filter.LandmarkDesc = matchObject.description;
                    
                    if ((matchObject.categoryId !== undefined) &&
                    (matchObject.categoryId !== null) &&
                    (matchObject.categoryId !== "")) 
                        criteria.Filter.categoryId = matchObject.categoryId;
                    
                    if ((matchObject.position !== undefined) &&
                    (matchObject.position !== null) &&
                    (matchObject.position !== "")) {
                        if (typeof(matchObject.position) != "object") 
                            throw new DeviceAPIError(error.INVALID_ARG_ERR, 'position must be an object');
                        else {
                            criteria.Filter.LandmarkPosition = new __sp_landmark_position_obj(matchObject.position);
                        }
                    }
                    if ((matchObject.coverageRadiusUsed !== undefined) &&
                    (matchObject.coverageRadiusUsed !== null) &&
                    (matchObject.coverageRadiusUsed !== "")) {
                        if (typeof(matchObject.coverageRadiusUsed) != "number") 
                            throw new DeviceAPIError(error.INVALID_ARG_ERR, "coverageRadiusUsed should be number");
                        else 
                            criteria.Filter.CoverageRadiusOption = matchObject.coverageRadiusUsed;
                    }
                    
                    if ((matchObject.searchRadius !== undefined) &&
                    (matchObject.searchRadius !== null) &&
                    (matchObject.searchRadius !== "")) {
                        if (typeof(matchObject.searchRadius) != "number") 
                            throw new DeviceAPIError(error.INVALID_ARG_ERR, "searchRadius should be number");
                        else 
                            criteria.Filter.MaximumDistance = matchObject.searchRadius;
                        
                    }
                    
                    if ((matchObject.area !== undefined) &&
                    (matchObject.area !== null) &&
                    (matchObject.area !== "")) {
                        if (typeof(matchObject.area) != 'object') 
                            throw new DeviceAPIError(error.INVALID_ARG_ERR, 'area must be an object');
                        else {
                            criteria.Filter.BoundedArea = new __sp_landmark_bounded_area_obj(matchObject.area);
                        }
                    }
                }
        //alert("calling getlist");        
		
		this.temporarySCb = callback;
        this.temporaryECb = ErrorCallback;
		   
        var rval = this.so.IDataSource.GetList(criteria, this.getLandmarksCb);
        if (rval.TransactionID) {
            glob_obj.addToGlobalArray(rval.TransactionID, callback, ErrorCallback);
        }
        
        if (rval.ErrorCode != 0) {
            switch (rval.ErrorCode) {
                case 1003:
                    throw new DeviceAPIError(error.MISSING_ARG_ERR, rval.ErrorMessage);
                    break;
                case 1002:
                    throw new DeviceAPIError(error.INVALID_ARG_ERR, rval.ErrorMessage);
                    break;
                case 1004:
                    throw new DeviceAPIError(error.NOT_SUPPORTED_ERR, rval.ErrorMessage);
                    break;
                case 1000:
                    throw new DeviceAPIError(error.INVALID_ARG_ERR, rval.ErrorMessage);
                    break;
                default:
                    throw new DeviceAPIError(-101, "unknown error message");
                    
            }
            
        }
        return rval.TransactionID;
        
        
    } 
    catch (e) {
        //alert("exception from here");
        throw e;
    }
}

function __sp_landmarks_import_cb(arg1, arg2, arg3){
    //if there is an error invoke user supplied error callback
    var iter = null;
    var callback;
    var ErrorCallback;
    var CbObj;
    if (this.temporarySCb) {
        category_cb = this.temporarySCb;
        ErrorCallback = this.temporaryECb;
        this.temporarySCb = null;
        this.temporaryECb = null;
    }
    else {
        CbObj = glob_obj.getFromArray(arg1);
        if (CbObj) {
            callback = CbObj.success_cb;
            ErrorCallback = CbObj.error_cb;
        }
        
        else {
            alert("Landmarks: __sp_landmarks_import_cb: Callback not found ");
            return;
        }
    }
    
    //if there is an error invoke user supplied error callback
    if (arg2 == 4 || arg3.ErrorCode) { //indicates an error
        var scbErrCode = convertFromPS2JS(arg3.ErrorCode);
        var erroObject = new DeviceAPIError(scbErrCode, arg3.ErrorMessage);
        if (ErrorCallback) {
            ErrorCallback(erroObject);
        }
    }
    else {
        if (arg3.ReturnValue) {
            iter = new __sp_landmarks_iterator(arg3.ReturnValue);
        }
        
        //in case of success invoke user supplied scb
        callback(iter);
    }
    glob_obj.removeFromArray(arg1);
}

function __sp_landmarks_import(callback, sourceFileUri, mimetype, ErrorCallback){
    try {
        var error = new DeviceAPIError(0, "dummy");
        var isErrCB = true;//indicates a valid errocalback has been supplied
        if (callback === undefined) {
            throw new DeviceAPIError(error.MISSING_ARG_ERR, 'LandmarksItrCallback is missing');
        }
        else {
            if (((callback === null) ||
            (callback === "")) &&
            (typeof(callback) != "number")) {
                throw new DeviceAPIError(error.MISSING_ARG_ERR, 'LandmarksItrCallback is missing');
            }
            else 
                if (typeof(callback) != 'function') {
                    throw new DeviceAPIError(error.INVALID_ARG_ERR, 'invalid LandmarksItrCallback argument');
                }
        }
        
        if (sourceFileUri === undefined || sourceFileUri === null) {
            throw new DeviceAPIError(error.MISSING_ARG_ERR, 'sourceFileUri is missing');
        }
        else 
            if (typeof(sourceFileUri) !== "string") {
                throw new DeviceAPIError(error.INVALID_ARG_ERR, 'invalid sourceFileUri argument');
            }
        
        if (mimetype === undefined || mimetype === null) {
            throw new DeviceAPIError(error.MISSING_ARG_ERR, 'mimetype is missing');
        }
        else 
            if (typeof(mimetype) !== "string") {
                throw new DeviceAPIError(error.INVALID_ARG_ERR, 'invalid mimetype argument');
            }
        
        if ((ErrorCallback != undefined)) {
            if ((!ErrorCallback) &&
            (typeof(ErrorCallback) != "number")) {
                isErrCB = false;
            }
            else 
                if ((typeof(ErrorCallback) != 'function')) {
                    throw new DeviceAPIError(error.INVALID_ARG_ERR, 'invalid ErrorCallback callback');
                }
            
        }
        else {
            isErrCB = false;
        }
        
        
        
        var criteria = new Object();
        modifyObjectBaseProp(criteria);
        criteria.Type = "Landmark";
        criteria.Data = new Object();
        modifyObjectBaseProp(criteria.Data);
        //replace all '/' to '\' and remove file:// or file:///
        if (sourceFileUri.slice(0, 7) == "file://") {
            sourceFileUri = sourceFileUri.slice(7);
        }
        else 
            if (sourceFileUri.slice(0, 8) == "file:///") {
                sourceFileUri = sourceFileUri.slice(8);
            }
            else {
                throw new DeviceAPIError(error.INVALID_ARG_ERR, "sourceFileUri is not in URI format");
            }
        while (sourceFileUri.search("/") != -1) {
            sourceFileUri = sourceFileUri.replace("/", "\\");
        }
        criteria.Data.SourceFile = sourceFileUri;
        criteria.Data.MimeType = mimetype;
		
		this.temporarySCb = callback;
        this.temporaryECb = ErrorCallback;
		
        var rval = this.so.IDataSource.Import(criteria, this.importLandmarksCb);
        if (rval.TransactionID) {
            glob_obj.addToGlobalArray(rval.TransactionID, callback, ErrorCallback);
        }
        
        if (rval.ErrorCode != 0) {
            switch (rval.ErrorCode) {
                case err_missing_argument:
                    throw new DeviceAPIError(error.MISSING_ARG_ERR, rval.ErrorMessage);
                    break;
                case err_bad_argument:
                    throw new DeviceAPIError(error.INVALID_ARG_ERR, rval.ErrorMessage);
                    break;
                case err_ServiceNotSupported:
                    throw new DeviceAPIError(error.NOT_SUPPORTED_ERR, rval.ErrorMessage);
                    break;
                case err_InvalidService_Argument:
                    throw new DeviceAPIError(error.INVALID_ARG_ERR, rval.ErrorMessage);
                    break;
                default:
                    throw new DeviceAPIError(-101, "unknown error message");
            }
        }
        return rval.TransactionID;
    } 
    catch (e) {
        throw e;
    }
}

function __sp_landmarks_export_cb(arg1, arg2, arg3){
    var callback;
    var ErrorCallback;
    var CbObj;
    if (this.temporarySCb) {
        category_cb = this.temporarySCb;
        ErrorCallback = this.temporaryECb;
        this.temporarySCb = null;
        this.temporaryECb = null;
    }
    else {
        CbObj = glob_obj.getFromArray(arg1);
        if (CbObj) {
            callback = CbObj.success_cb;
            ErrorCallback = CbObj.error_cb;
        }
        
        else {
            alert("Landmarks: __sp_landmarks_export_cb: Callback not found ");
            return;
        }
    }
    
    //if there is an error invoke user supplied error callback
    //if there is an error invoke user supplied error callback
    if (arg2 == 4 || arg3.ErrorCode) { //indicates an error
        var scbErrCode = convertFromPS2JS(arg3.ErrorCode);
        var erroObject = new DeviceAPIError(scbErrCode, arg3.ErrorMessage);
        if (ErrorCallback) {
            ErrorCallback(erroObject);
        }
    }
    else {
        //in case of success invoke user supplied scb
        callback();
    }
    
    glob_obj.removeFromArray(arg1);
}

function __sp_landmarks_export(callback, landmarkIdList, destFileUri, mimetype, ErrorCallback){
    try {
        var error = new DeviceAPIError(0, "dummy");
        var isErrCB = true;//indicates a valid errocalback has been supplied
        if (callback === undefined) {
            throw new DeviceAPIError(error.MISSING_ARG_ERR, 'SuccessCallback is missing');
        }
        else {
            if (((callback === null) ||
            (callback === "")) &&
            (typeof(callback) != "number")) {
                throw new DeviceAPIError(error.MISSING_ARG_ERR, 'SuccessCallback is missing');
            }
            else 
                if (typeof(callback) != 'function') {
                    throw new DeviceAPIError(error.INVALID_ARG_ERR, 'invalid SuccessCallback argument');
                }
        }
        
        if (landmarkIdList === undefined || landmarkIdList === null) {
            throw new DeviceAPIError(error.MISSING_ARG_ERR, 'landmarkIdList is missing');
        }
        else 
            if (typeof(landmarkIdList) !== "object") {
                throw new DeviceAPIError(error.INVALID_ARG_ERR, 'invalid landmarkIdList argument');
            }
        
        if (destFileUri === undefined || destFileUri === null) {
            throw new DeviceAPIError(error.MISSING_ARG_ERR, 'destFileUri is missing');
        }
        else 
            if (typeof(destFileUri) !== "string") {
                throw new DeviceAPIError(error.INVALID_ARG_ERR, 'invalid destFileUri argument');
            }
        
        if (mimetype === undefined || mimetype === null) {
            throw new DeviceAPIError(error.MISSING_ARG_ERR, 'mimetype is missing');
        }
        else 
            if (typeof(mimetype) !== "string") {
                throw new DeviceAPIError(error.INVALID_ARG_ERR, 'invalid mimetype argument');
            }
        
        if ((ErrorCallback != undefined)) {
            if ((!ErrorCallback) &&
            (typeof(ErrorCallback) != "number")) {
                isErrCB = false;
            }
            else 
                if ((typeof(ErrorCallback) != 'function')) {
                    throw new DeviceAPIError(error.INVALID_ARG_ERR, 'invalid ErrorCallback callback');
                }
            
        }
        else {
            isErrCB = false;
        }
        
        
        var criteria = new Object();
        modifyObjectBaseProp(criteria);
        criteria.Type = "Landmark";
        criteria.Data = new Object();
        modifyObjectBaseProp(criteria.Data);
        //replace all '/' to '\' and remove file:// or file:///
        if (destFileUri.slice(0, 7) == "file://") {
            destFileUri = destFileUri.slice(7);
        }
        else 
            if (destFileUri.slice(0, 8) == "file:///") {
                destFileUri = destFileUri.slice(8);
            }
            else {
                throw new DeviceAPIError(error.INVALID_ARG_ERR, "destFileUri is not in URI format");
            }
        while (destFileUri.search("/") != -1) {
            destFileUri = destFileUri.replace("/", "\\");
        }
        criteria.Data.DestinationFile = destFileUri;
        criteria.Data.IdList = landmarkIdList;
        criteria.Data.MimeType = mimetype;
		
		this.temporarySCb = callback;
        this.temporaryECb = ErrorCallback;
		
        var rval = this.so.IDataSource.Export(criteria, this.exportLandmarksCb);
        if (rval.TransactionID) {
            glob_obj.addToGlobalArray(rval.TransactionID, callback, ErrorCallback);
        }
        if (rval.ErrorCode != 0) {
            switch (rval.ErrorCode) {
                case err_missing_argument:
                    throw new DeviceAPIError(error.MISSING_ARG_ERR, rval.ErrorMessage);
                    break;
                case err_bad_argument:
                    throw new DeviceAPIError(error.INVALID_ARG_ERR, rval.ErrorMessage);
                    break;
                case err_ServiceNotSupported:
                    throw new DeviceAPIError(error.NOT_SUPPORTED_ERR, rval.ErrorMessage);
                    break;
                case err_InvalidService_Argument:
                    throw new DeviceAPIError(error.INVALID_ARG_ERR, rval.ErrorMessage);
                    break;
                default:
                    throw new DeviceAPIError(-101, "unknown error message");
            }
        }
        return rval.TransactionID;
    } 
    catch (e) {
        throw e;
    }
}

function __sp_landmarks_organize_cb(arg1, arg2, arg3){
    var callback;
    var ErrorCallback;
	if (this.temporarySCb) {
        category_cb = this.temporarySCb;
        ErrorCallback = this.temporaryECb;
        this.temporarySCb = null;
        this.temporaryECb = null;
    }
    else {
        CbObj = glob_obj.getFromArray(arg1);
        if (CbObj) {
            callback = CbObj.success_cb;
            ErrorCallback = CbObj.error_cb;
        }
        
        else {
            alert("Landmarks: __sp_landmarks_organize_cb: Callback not found ");
            return;
        }
    }
    
    //if there is an error invoke user supplied error callback
    if (arg2 == 4 || arg3.ErrorCode) { //indicates an error
        var scbErrCode = convertFromPS2JS(arg3.ErrorCode);
        var erroObject = new DeviceAPIError(scbErrCode, arg3.ErrorMessage);
        if (ErrorCallback) {
            ErrorCallback(erroObject);
        }
    }
    else {
        //in case of success invoke user supplied scb
        callback();
    }
    glob_obj.removeFromArray(arg1);
}

function __sp_landmarks_organize(callback, landmarkIdList, categoryId, associate, ErrorCallback){
    try {
        var error = new DeviceAPIError(0, "dummy");
        var isErrCB = true;//indicates a valid errocalback has been supplied
        if (callback === undefined) {
            throw new DeviceAPIError(error.MISSING_ARG_ERR, 'SuccessCallback is missing');
        }
        else {
            if (((callback === null) ||
            (callback === "")) &&
            (typeof(callback) != "number")) {
                throw new DeviceAPIError(error.MISSING_ARG_ERR, 'SuccessCallback is missing');
            }
            else 
                if (typeof(callback) != 'function') {
                    throw new DeviceAPIError(error.INVALID_ARG_ERR, 'invalid SuccessCallback argument');
                }
        }
        
        if (landmarkIdList === undefined || landmarkIdList === null) {
            throw new DeviceAPIError(error.MISSING_ARG_ERR, 'landmarkIdList is missing');
        }
        else 
            if (typeof(landmarkIdList) !== "object") {
                throw new DeviceAPIError(error.INVALID_ARG_ERR, 'invalid LandmarkItem argument');
            }
        
        if (categoryId === undefined || categoryId === null) {
            throw new DeviceAPIError(error.MISSING_ARG_ERR, 'categoryId is missing');
        }
        else 
            if (typeof(categoryId) !== "string") {
                throw new DeviceAPIError(error.INVALID_ARG_ERR, 'invalid categoryId argument');
            }
        
        if (associate === undefined || associate === null) {
            associate = true;
        }
        else 
            if (typeof(associate) !== "boolean") {
                throw new DeviceAPIError(error.INVALID_ARG_ERR, 'invalid associate argument');
            }
        
        if ((ErrorCallback != undefined)) {
            if ((!ErrorCallback) &&
            (typeof(ErrorCallback) != "number")) {
                isErrCB = false;
            }
            else 
                if ((typeof(ErrorCallback) != 'function')) {
                    throw new DeviceAPIError(error.INVALID_ARG_ERR, 'invalid ErrorCallback callback');
                }
            
        }
        else {
            isErrCB = false;
        }
        
        
        
        var criteria = new Object();
        modifyObjectBaseProp(criteria);
        criteria.Type = "Landmark";
        criteria.Data = new Object();
        modifyObjectBaseProp(criteria.Data);
        criteria.Data.id = categoryId;
        criteria.Data.IdList = landmarkIdList;
        if (associate) 
            criteria.OperationType = "Associate";
        else 
            criteria.OperationType = "Disassociate";
		
		this.temporarySCb = callback;
        this.temporaryECb = ErrorCallback;
		
        var rval = this.so.IDataSource.Organise(criteria, this.organizeLandmarksCb);
        if (rval.TransactionID) {
            glob_obj.addToGlobalArray(rval.TransactionID, callback, ErrorCallback);
        }
        
        if (rval.ErrorCode != 0) {
            switch (rval.ErrorCode) {
                case err_missing_argument:
                    throw new DeviceAPIError(error.MISSING_ARG_ERR, rval.ErrorMessage);
                    break;
                case err_bad_argument:
                    throw new DeviceAPIError(error.INVALID_ARG_ERR, rval.ErrorMessage);
                    break;
                case err_ServiceNotSupported:
                    throw new DeviceAPIError(error.NOT_SUPPORTED_ERR, rval.ErrorMessage);
                    break;
                case err_InvalidService_Argument:
                    throw new DeviceAPIError(error.INVALID_ARG_ERR, rval.ErrorMessage);
                    break;
                default:
                    throw new DeviceAPIError(-101, "unknown error message");
            }
        }
        return rval.TransactionID;
    } 
    catch (e) {
        throw e;
    }
}

function __sp_landmarks_cancel(transactionId){
    try {
        var error = new DeviceAPIError(0, "dummy");
        if ((transactionId === undefined) ||
        (transactionId === null) ||
        (transactionId === "")) {
            throw new DeviceAPIError(error.MISSING_ARG_ERR, 'transactionId is missing');
        }
        
        if (typeof(transactionId) != "number") {
            throw new DeviceAPIError(error.INVALID_ARG_ERR, 'invalid transactionId argument');
        }
        if (transactionId < 0) {
            throw new DeviceAPIError(error.DATA_NOT_FOUND_ERR, 'non-existent transactionId');
        }
        
        var criteria = new Object();
        modifyObjectBaseProp(criteria);
        criteria.TransactionID = transactionId;
        var rval = this.so.IDataSource.Cancel(criteria);
        if (rval.ErrorCode != 0) {
            switch (rval.ErrorCode) {
                case err_missing_argument:
                    throw new DeviceAPIError(error.MISSING_ARG_ERR, rval.ErrorMessage);
                    break;
                case err_bad_argument:
                    throw new DeviceAPIError(error.INVALID_ARG_ERR, rval.ErrorMessage);
                    break;
                case err_ServiceNotSupported:
                    throw new DeviceAPIError(error.NOT_SUPPORTED_ERR, rval.ErrorMessage);
                    break;
                case err_InvalidService_Argument:
                    throw new DeviceAPIError(error.INVALID_ARG_ERR, rval.ErrorMessage);
                    break;
                default:
                    throw new DeviceAPIError(-101, "unknown error message");
            }
        }
    } 
    catch (e) {
        throw e;
    }
}
