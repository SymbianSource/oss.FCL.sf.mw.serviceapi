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
var __device_debug_on__=true;
var event_completed=2;
var event_cancelled=3;
var __Service_Interface_Ver=1;
var MapErrorCode={1016:100,1012:101,1010:102,1009:103,1005:104,1000:105,1011:106,1007:107,1003:1,1002:2,1004:3};
function __device_debug(_1){
};
function __device_handle_exception(e,_3){
__device_debug(_3);
throw (e);
};
function __device_typeof(_4){
if(_4==undefined){
return "undefined";
}
if(_4 instanceof Object){
if(_4 instanceof String){
return "String";
}else{
if(_4 instanceof Array){
return "Array";
}
}
}
if(typeof _4){
if(typeof _4=="object"){
if(typeof _4=="object"&&!_4){
return "null";
}
}else{
if(typeof _4=="string"){
return "string";
}
}
}
};
if((typeof nokia)=="undefined"){
nokia={};
nokia.device={};
}else{
if((typeof nokia.device)!="undefined"){
nokia.device={};
}else{
throw ("nokia.device already defined");
}
}
nokia.device={load:__device_service_load,listInterfaces:__device_service_interfaces,getSystemProperties:__device_getSystemProperties,getLibraryVersion:__device_getLibraryVersion,version:2};
function __device_getLibraryVersion(){
return 2;
};
function __device_getSystemProperties(){
return {uriPath:{max:255}};
};
var __device_services_inited=false;
var __device_services=[{"name":"device","version":2,"interfaces":[]}];
function __device_services_init(){
if(__device_services_inited){
return;
}
__device_services_inited=true;
try{
var _5=device.getServiceObject("Service.ServiceRegistry","IService");
var _6={ServiceName:"Service.Calendar",InterfaceName:"IDataSource"};
var _7=_5.IService.GetList(_6);
if(_7.ErrorCode==0){
var _8=_7.ReturnValue;
if(_8){
var _9=_8.getNext();
if(_9){
var _a=_9.VersionList;
var _b;
for(_b in _a){
if(_a[_b]>__Service_Interface_Ver){
__Service_Interface_Ver=_a[_b];
}
}
}
}
_8.close();
}
_5.close();
}
catch(e){
__Service_Interface_Ver=1;
}
try{
__device_services[0].interfaces.push(__device_geolocation_service_entry);
}
catch(e){
__device_debug("Missing library implementation: "+e);
}
try{
__device_services[0].interfaces.push(__device_camera_service_entry);
}
catch(e1){
__device_debug("Missing library implementation: "+e1);
}
try{
__device_services[0].interfaces.push(__device_media_service_entry);
}
catch(e2){
}
try{
__device_services[0].interfaces.push(__device_contacts_service_entry);
}
catch(e3){
}
try{
__device_services[0].interfaces.push(__device_messaging_service_entry);
}
catch(e4){
__device_debug("Missing library implementation: "+e4);
}
try{
__device_services[0].interfaces.push(__device_calendar_service_entry);
}
catch(e5){
__device_debug("Missing library implementation: "+e5);
}
try{
__device_services[0].interfaces.push(__device_landmarks_service_entry);
}
catch(e6){
__device_debug("Missing library implementation: "+e6);
}
try{
__device_services[0].interfaces.push(__device_commlog_service_entry);
}
catch(e7){
__device_debug("Missing library implementation: "+e7);
}
try{
__device_services[0].interfaces.push(__device_sysinfo_service_entry);
}
catch(e8){
__device_debug("Missing library implementation: "+e8);
}
try{
__device_services[0].interfaces.push(__device_sensors_service_entry);
}
catch(e9){
__device_debug("Missing library implementation: "+e9);
}
};
function __device_get_implementation(i){
return new i.proto(new (i.providers[0].instance));
};
function __device_get_descriptor(i){
return new i.descriptor(new (i.providers[0].descriptor));
};
function __device_get_interface(s,_f,_10){
var i=s.interfaces;
for(var d in i){
if(i[d].name==null){
__device_update_descriptor(i[d]);
}
if(i[d].name==undefined){
continue;
}
if(i[d].name==_f){
if(_10){
if(i[d].version>=_10){
return __device_get_implementation(i[d]);
}
}else{
return __device_get_implementation(i[d]);
}
}
}
return null;
};
function __device_service_load(_13,_14){
var _15=new DeviceException("dummy",0);
if(_13){
if(typeof _13!="string"){
throw new DeviceException(_15.INVALID_ARG_ERR,"nokia.device.load:Invalid type interfaceName");
}
}else{
throw new DeviceException(_15.MISSING_ARG_ERR,"nokia.device.load:interfaceName param expected");
}
if(_14){
if(typeof _14!="number"){
throw new DeviceException(_15.INVALID_ARG_ERR,"nokia.device.load:Invalid type version");
}
}
__device_services_init();
for(var s in __device_services){
var i=__device_get_interface(__device_services[s],_13,_14);
if(i!=null){
return i;
}
}
return null;
};
function __device_update_descriptor(i){
var d=__device_get_descriptor(i);
i.name=d.interfaceName;
i.version=d.version;
};
function __device_interface_list(s){
var _1b=new Array();
for(var i in s.interfaces){
if(s.interfaces[i].name==null){
__device_update_descriptor(s.interfaces[i]);
}
if(s.interfaces[i].name==undefined){
continue;
}
_1b[i]=new Object();
_1b[i].name=s.interfaces[i].name;
_1b[i].version=s.interfaces[i].version;
}
return _1b;
};
function __device_service_descriptor(s){
this.name=s.name;
this.version=s.version;
this.interfaces=__device_interface_list(s);
this.toString=__device_service_descriptor_to_string;
};
function __device_service_descriptor_to_string(){
var is="\nInterfaces(s): ";
for(i in this.interfaces){
is+="\n"+this.interfaces[i].name+" "+this.interfaces[0].version;
}
return ("Service: "+this.name+is);
};
function __device_service_interfaces(){
__device_services_init();
for(var s in __device_services){
var _20=__device_interface_list(__device_services[s]);
return new __FWIter(_20);
}
return null;
};
function __FWIter(arr){
this._arr=arr;
this._pos=0;
this._valid=true;
};
__FWIter.prototype.hasNext=function(){
return (this._valid&&this._pos<this._arr.length);
};
__FWIter.prototype.next=function(){
if(this._valid&&(this._pos<this._arr.length)){
return this._arr[this._pos++];
}else{
return null;
}
};
__FWIter.prototype.close=function(){
delete this._arr;
this._valid=false;
};
function modifyObjectBaseProp(obj){
for(pro in obj){
if(typeof obj[pro]=="function"){
obj[pro]=0;
}
}
};
var glob_obj=null;
var temp_scb=null;
var temp_ecb=null;
glob_obj=new Object();
glob_obj.glob_cb_arr=new Array();
glob_obj.addToGlobalArray=addToGlobalArray;
glob_obj.removeFromArray=removeFromArray;
glob_obj.getFromArray=getFromArray;
DeviceAPIError.prototype=new Error();
DeviceAPIError.prototype.constructor=DeviceAPIError;
function DeviceAPIError(_23,_24){
this.toString=concatenate;
this.code=_23;
this.name="DeviceError";
this.message=_24;
this.MISSING_ARG_ERR=1;
this.INVALID_ARG_ERR=2;
this.NOT_SUPPORTED_ERR=3;
this.TIMEOUT_ERR=100;
this.DATA_NOT_FOUND_ERR=101;
this.DATA_ALREADY_EXISTS_ERR=102;
this.SERVICE_BUSY_ERR=103;
this.SERVICE_IN_USE_ERR=104;
this.DATA_OUT_OF_RANGE_ERR=105;
this.NOT_ALLOWED_ERR=106;
this.SIZE_EXCEEDED_ERR=107;
this.INVALID_URI_ERR=108;
this.URI_NOT_FOUND_ERR=109;
this.URI_ALREADY_EXISTS_ERR=110;
this.NO_MEMORY_ERR=111;
};
DeviceException.prototype=new Error();
DeviceException.prototype.constructor=DeviceException;
function DeviceException(_25,_26){
this.toString=concatenate;
this.code=_25;
this.name="DeviceException";
this.message=_26;
this.MISSING_ARG_ERR=1;
this.INVALID_ARG_ERR=2;
this.NOT_SUPPORTED_ERR=3;
this.TIMEOUT_ERR=100;
this.DATA_NOT_FOUND_ERR=101;
this.DATA_ALREADY_EXISTS_ERR=102;
this.SERVICE_BUSY_ERR=103;
this.SERVICE_IN_USE_ERR=104;
this.DATA_OUT_OF_RANGE_ERR=105;
this.NOT_ALLOWED_ERR=106;
this.SIZE_EXCEEDED_ERR=107;
this.INVALID_URI_ERR=108;
this.URI_NOT_FOUND_ERR=109;
this.URI_ALREADY_EXISTS_ERR=110;
this.NO_MEMORY_ERR=111;
};
function concatenate(){
return (this.name+": errcode: "+this.code+"\nline: "+this.lineNumber+"\nfileName: "+this.fileName+"\nerrmsg: "+this.message);
};
function splitErrorMessage(_27){
if(_27.search(/:/)!=-1){
if((_27.split(":").length)==2){
return _27.split(":")[1];
}
if((_27.split(":").length)>2){
return _27.split(":")[2];
}
}
return _27;
};
var __s60_start_and_wait_cb;
function __s60_on_app_exit(){
widget.onshow=null;
if(__s60_start_and_wait_cb!==null){
__s60_start_and_wait_cb();
}
};
function __s60_on_app_start(){
widget.onhide=null;
widget.onshow=__s60_on_app_exit;
};
function __s60_start_and_wait(id,_29,_2a){
__s60_start_and_wait_cb=_2a;
widget.onhide=__s60_on_app_start;
widget.openApplication(id,_29);
};
function __s60_api_not_supported(){
throw (err_ServiceNotSupported);
};
function __s60_enumerate_object(_2b,_2c,_2d,_2e){
var key;
for(key in _2b){
var _30;
if(_2c){
_30=_2c+"."+key;
}else{
_30=key;
}
var _31=_2b[key];
if(typeof _31=="object"){
__s60_enumerate_object(_31,_30,_2d,_2e);
}else{
_2d(_30,_31,_2e);
}
}
};
function removeFromArray(_32){
for(i=0;i<(glob_obj.glob_cb_arr.length);i++){
if(glob_obj.glob_cb_arr[i].transactionId==_32){
glob_obj.glob_cb_arr.splice(i,1);
}
}
};
function addToGlobalArray(_33,sCb,_35){
var obj=new Object();
obj.success_cb=sCb;
obj.transactionId=_33;
obj.error_cb=_35;
glob_obj.glob_cb_arr.push(obj);
};
function getFromArray(tid){
var i;
for(i=0;i<(glob_obj.glob_cb_arr.length);i++){
if(glob_obj.glob_cb_arr[i].transactionId==tid){
return glob_obj.glob_cb_arr[i];
}
}
if(temp_scb){
var obj=new Object();
obj.success_cb=temp_scb;
obj.error_cb=temp_ecb;
temp_ecb=temp_scb=null;
return obj;
}
return null;
};
var __device_landmarks_service_entry={"name":null,"version":null,"proto":__device_landmarks,"descriptor":__device_landmarks_descriptor,"providers":[{"descriptor":__sp_landmarks_descriptor,"instance":__sp_landmarks_instance}]};
function __device_landmarks(_3a){
this.provider=_3a;
this.interfaceName=_3a.descriptor.interfaceName;
this.version=_3a.descriptor.version;
this.startEditor=__device_landmarks_startEditor;
this.getCategories=__device_landmarks_getCategories;
this.getLandmarks=__device_landmarks_getLandmarks;
this.addCategory=__device_landmarks_add_category;
this.updateCategory=__device_landmarks_update_category;
this.updateLandmark=__device_landmarks_update_landmark;
this.addLandmark=__device_landmarks_add_landmark;
this.deleteCategory=__device_landmarks_delete_category;
this.deleteLandmark=__device_landmarks_delete_landmark;
this.importLandmarks=__device_landmarks_import_landmarks;
this.exportLandmarks=__device_landmarks_export_landmarks;
this.organizeLandmarks=__device_landmarks_organize_landmarks;
this.cancel=__device_landmarks_cancel;
};
function __device_landmarks_descriptor(_3b){
this.interfaceName=_3b.interfaceName;
this.version=_3b.version;
};
function __device_landmarks_startEditor(_3c,_3d){
this.provider.startEditor(_3c,_3d);
};
function __device_landmarks_getCategories(_3e,_3f,_40){
return this.provider.getCategories(_3e,_3f,_40);
};
function __device_landmarks_getLandmarks(_41,_42,_43){
return this.provider.getLandmarks(_41,_42,_43);
};
function __device_landmarks_add_category(_44,_45,_46){
return this.provider.addCategory(_44,_45,_46);
};
function __device_landmarks_add_landmark(_47,_48,_49){
return this.provider.addLandmark(_47,_48,_49);
};
function __device_landmarks_delete_category(_4a,_4b,_4c){
return this.provider.deleteCategory(_4a,_4b,_4c);
};
function __device_landmarks_delete_landmark(_4d,_4e,_4f){
return this.provider.deleteLandmark(_4d,_4e,_4f);
};
function __device_landmarks_update_landmark(_50,_51,_52){
return this.provider.updateLandmark(_50,_51,_52);
};
function __device_landmarks_update_category(_53,_54,_55){
return this.provider.updateCategory(_53,_54,_55);
};
function __device_landmarks_import_landmarks(_56,_57,_58,_59){
return this.provider.importLandmarks(_56,_57,_58,_59);
};
function __device_landmarks_export_landmarks(_5a,_5b,_5c,_5d,_5e){
return this.provider.exportLandmarks(_5a,_5b,_5c,_5d,_5e);
};
function __device_landmarks_organize_landmarks(_5f,_60,_61,_62,_63){
return this.provider.organizeLandmarks(_5f,_60,_61,_62,_63);
};
function __device_landmarks_cancel(_64){
return this.provider.cancel(_64);
};
var err_missing_argument=1003;
var err_bad_argument=1002;
var err_ServiceNotSupported=1004;
var err_InvalidService_Argument=1000;
function convertFromPS2JS(_65){
var _66=new DeviceAPIError(0,"dummy");
var _67;
switch(_65){
case 1016:
_67=_66.TIMEOUT_ERR;
break;
case 1012:
_67=_66.DATA_NOT_FOUND_ERR;
break;
case 1010:
_67=_66.DATA_ALREADY_EXISTS_ERR;
break;
case 1009:
_67=_66.SERVICE_BUSY_ERR;
break;
case 1005:
_67=_66.SERVICE_IN_USE_ERR;
break;
default:
_67=1001;
}
return _67;
};
function __sp_landmarks_descriptor(){
this.interfaceName="landmarks";
if(window.__Service_Interface_Ver){
this.version=__Service_Interface_Ver;
}else{
this.version=1;
}
};
function __sp_landmarks_instance(){
this.descriptor=new __sp_landmarks_descriptor();
this.startEditor=__sp_landmarks_startEditor;
this.getCategories=__sp_landmarks_category_getList;
this.getCategoriesCb=__sp_landmarks_category_getList_cb;
this.addCategory=__sp_landmarks_category_add;
this.addCategoryCb=__sp_landmarks_category_add_cb;
this.updateCategory=__sp_landmarks_category_update;
this.updateCategoryCb=__sp_landmarks_category_update_cb;
this.deleteCategory=__sp_landmarks_category_delete;
this.deleteCategoryCb=__sp_landmarks_category_delete_cb;
this.getLandmarks=__sp_landmarks_getList;
this.getLandmarksCb=__sp_landmarks_getList_cb;
this.addLandmark=__sp_landmarks_add;
this.addLandmarkCb=__sp_landmarks_add_cb;
this.updateLandmark=__sp_landmarks_update;
this.updateLandmarkCb=__sp_landmarks_update_cb;
this.deleteLandmark=__sp_landmarks_delete;
this.deleteLandmarkCb=__sp_landmarks_delete_cb;
this.importLandmarks=__sp_landmarks_import;
this.importLandmarksCb=__sp_landmarks_import_cb;
this.exportLandmarks=__sp_landmarks_export;
this.exportLandmarksCb=__sp_landmarks_export_cb;
this.organizeLandmarks=__sp_landmarks_organize;
this.organizeLandmarksCb=__sp_landmarks_organize_cb;
this.temporarySCb=null;
this.temporaryECb=null;
this.cancel=__sp_landmarks_cancel;
try{
this.so=device.getServiceObject("Service.Landmarks","IDataSource");
}
catch(e){
__device_handle_exception(e,"Landmarks service not available");
}
};
var __SP_CATEGORY_MIN_LOCAL_ID=16;
var __sp_category_list=[{id:1,globalId:3000,name:"Accommodation"},{id:2,globalId:6000,name:"Businesses"},{id:3,globalId:9000,name:"Telecommunications"},{id:4,globalId:12000,name:"Education"},{id:5,globalId:15000,name:"Entertainment"},{id:6,globalId:18000,name:"Food and drink"},{id:7,globalId:21000,name:"Geographical locations"},{id:8,globalId:24000,name:"Outdoor activities"},{id:9,globalId:27000,name:"People"},{id:10,globalId:30000,name:"Public services"},{id:11,globalId:33000,name:"Places of worship"},{id:12,globalId:36000,name:"Shopping"},{id:13,globalId:39000,name:"Sightseeing"},{id:14,globalId:42000,name:"Sports"},{id:15,globalId:45000,name:"Transport"}];
function __sp_landmarks_category_iterator(_68){
this.iter=_68;
this.next=__sp_landmarks_category_iterator_get_next;
this.hasNext=__sp_landmarks_category_iterator_has_next;
this.hasElement=false;
this.catItem=null;
this.close=__sp_landmarks_category_close;
};
function __sp_landmarks_category_close(){
this.iter.close();
};
function __sp_landmarks_category_iterator_has_next(){
if(this.hasElement){
if(this.catItem!==null){
return true;
}else{
return false;
}
}else{
this.catItem=this.iter.getNext();
this.hasElement=true;
if(typeof this.catItem=="undefined"){
this.catItem=null;
return false;
}else{
return true;
}
}
};
function __sp_landmarks_category_iterator_get_next(){
if(this.hasElement){
var _69=new Object();
_69=this.catItem;
this.catItem=this.iter.getNext();
if(typeof (this.catItem)=="undefined"){
this.catItem=null;
}
return new __sp_device_category_obj(_69);
}else{
this.catItem=this.iter.getNext();
if(typeof this.catItem=="undefined"){
this.hasElement=true;
this.catItem=null;
return null;
}else{
this.hasElement=true;
var _6a=new Object();
_6a=this.lmItem;
this.catItem=this.iter.getNext();
if(typeof (this.catItem)=="undefined"){
this.catItem=null;
}
return new __sp_device_category_obj(_6a);
}
}
};
function __sp_landmarks_iterator(_6b){
this.iter=_6b;
this.next=__sp_landmarks_iterator_get_next;
this.hasNext=__sp_landmarks_iterator_has_next;
this.hasElement=false;
this.lmItem=null;
this.close=__sp_landmarks_landmarkitem_close;
};
function __sp_landmarks_landmarkitem_close(){
this.iter.close();
};
function __sp_device_landmark_location_obj(_6c){
this.longitude=(_6c.Longitude==undefined)?null:_6c.Longitude;
this.latitude=(_6c.Latitude==undefined)?null:_6c.Latitude;
if(_6c.Altitude){
this.altitude=_6c.Altitude;
}
if(_6c.HAccuracy){
this.hAccuracy=_6c.HAccuracy;
}
if(_6c.VAccuracy){
this.vAccuracy=_6c.VAccuracy;
}
};
function __sp_landmark_position_obj(_6d){
if((_6d.longitude!==undefined)&&(_6d.longitude!==null)&&(_6d.longitude!=="")){
this.Longitude=_6d.longitude;
}
if((_6d.latitude!==undefined)&&(_6d.latitude!==null)&&(_6d.latitude!=="")){
this.Latitude=_6d.latitude;
}
};
function __sp_landmark_position_obj_fromJS_2LIW(_6e){
var _6f=new DeviceAPIError(0,"dummy");
if(typeof (_6e)!="object"){
throw new DeviceAPIError(_6f.INVALID_ARG_ERR,"position must be of type object");
}
var _70=false;
var _71=false;
if((_6e.longitude!==undefined)&&(_6e.longitude!==null)&&(_6e.longitude!=="")){
this.Longitude=_6e.longitude;
_70=true;
}
if((_6e.latitude!==undefined)&&(_6e.latitude!==null)&&(_6e.latitude!=="")){
this.Latitude=_6e.latitude;
_71=true;
}
if(!(_70&&_71)){
throw new DeviceAPIError(_6f.MISSING_ARG_ERR,"missing position field");
}
if(_6e.altitude){
this.Altitude=_6e.altitude;
}
if(_6e.hAccuracy){
this.HAccuracy=_6e.hAccuracy;
}
if(_6e.vAccuracy){
this.VAccuracy=_6e.vAccuracy;
}
};
function __sp_landmark_bounded_area_obj(_72){
var _73=new DeviceAPIError(0,"dummy");
var _74=false;
var _75=false;
if((_72.coordinate1!==undefined)&&(_72.coordinate1!==null)&&(_72.coordinate1!=="")){
if(typeof (_72.coordinate1)!="object"){
throw new DeviceAPIError(_73.INVALID_ARG_ERR,"coordinate1 must be an object");
}else{
var _76=false;
var _77=false;
if((_72.coordinate1.latitude!==undefined)&&(_72.coordinate1.latitude!==null)&&(_72.coordinate1.latitude!=="")){
this.NorthLatitude=_72.coordinate1.latitude;
_76=true;
}
if((_72.coordinate1.longitude!==undefined)&&(_72.coordinate1.longitude!==null)&&(_72.coordinate1.longitude!=="")){
this.EastLongitude=_72.coordinate1.longitude;
_77=true;
}
if(!(_76&&_77)){
throw new DeviceAPIError(_73.MISSING_ARG_ERR,"missing position field");
}
_74=true;
}
}
if((_72.coordinate2!==undefined)&&(_72.coordinate2!==null)&&(_72.coordinate2!=="")){
if(typeof (_72.coordinate2)!="object"){
throw new DeviceAPIError(_73.INVALID_ARG_ERR,"coordinate2 must be an object");
}else{
var _76=false;
var _77=false;
if((_72.coordinate2.latitude!==undefined)&&(_72.coordinate2.latitude!==null)&&(_72.coordinate2.latitude!=="")){
this.SouthLatitude=_72.coordinate2.latitude;
_76=true;
}
if((_72.coordinate2.longitude!==undefined)&&(_72.coordinate2.longitude!==null)&&(_72.coordinate2.longitude!=="")){
this.WestLongitude=_72.coordinate2.longitude;
_77=true;
}
if(!(_76&&_77)){
throw new DeviceAPIError(_73.MISSING_ARG_ERR,"missing position field");
}
_75=true;
}
}
if(!(_74&&_75)){
throw new DeviceAPIError(_73.MISSING_ARG_ERR,"missing position field");
}
};
function __sp_device_landmark_address_obj(_78){
if(_78.Street){
this.street=_78.Street;
}
if(_78.City){
this.city=_78.City;
}
if(_78.state){
this.state=_78.state;
}
if(_78.AreaCode){
this.postalCode=_78.AreaCode;
}
if(_78.Country){
this.country=_78.Country;
}
if(_78.BuildingName){
this.building=_78.BuildingName;
}
if(_78.Telephone){
this.phone=_78.Telephone;
}
};
function __sp_landmark_address_obj(_79){
var _7a=new DeviceAPIError(0,"dummy");
if(typeof (_79)!="object"){
throw new DeviceAPIError(_7a.MISSING_ARG_ERR,"address must be of type object");
}
if(_79.street!==undefined){
if(_79.street===null){
this.Street="";
}else{
this.Street=_79.street;
}
}
if(_79.city!==undefined){
if(_79.city===null){
this.City="";
}else{
this.City=_79.city;
}
}
if(_79.state!==undefined){
if(_79.state===null){
this.state="";
}else{
this.state=_79.state;
}
}
if(_79.postalCode!==undefined){
if(_79.postalCode===null){
this.AreaCode="";
}else{
this.AreaCode=_79.postalCode;
}
}
if(_79.country!==undefined){
if(_79.country===null){
this.Country="";
}else{
this.Country=_79.country;
}
}
if(_79.building!==undefined){
if(_79.building===null){
this.BuildingName="";
}else{
this.BuildingName=_79.building;
}
}
if(_79.phone!==undefined){
if(_79.phone===null){
this.Telephone="";
}else{
this.Telephone=_79.phone;
}
}
};
function __sp_add_category_ids_for_names(_7b){
var _7c=new DeviceAPIError(0,"dummy");
var _7d=new Array();
for(var i in _7b){
if((_7b[i]!==undefined)&&(_7b[i]!=="")&&(_7b[i]!==null)){
if(typeof (_7b[i])!="string"){
throw new DeviceAPIError(_7c.INVALID_ARG_ERR,"category should be of type string");
}else{
_7d.push(_7b[i].toString());
}
}
}
return _7d;
};
function __sp_get_category_ids_for_names(_7f){
var _80=new DeviceAPIError(0,"dummy");
var _81=new Array();
var _82=0;
for(var i in _7f){
if(typeof (_7f[i])!="string"){
throw new DeviceAPIError(_80.INVALID_ARG_ERR,"category should be of type string");
}
for(var ii in __sp_category_list){
if(__sp_category_list[ii].name.toLowerCase()==_7f[i].toLowerCase()){
_81.push(__sp_category_list[ii].id.toString());
_82=1;
}
}
if(_82==0){
return null;
}
_82=0;
}
return _81;
};
function __sp_device_landmark_obj(_85){
this.landmarkId=_85.id;
if(_85.LandmarkName){
this.name=_85.LandmarkName;
}
if(_85.LandmarkDesc){
this.description=_85.LandmarkDesc;
}
if(_85.CoverageRadius){
this.coverageRadius=_85.CoverageRadius;
}
if(_85.LandmarkPosition){
this.position=new __sp_device_landmark_location_obj(_85.LandmarkPosition);
}
if(_85.CategoryInfo){
this.categoryIds=_85.CategoryInfo;
}
if(_85.LandmarkFields){
this.address=new __sp_device_landmark_address_obj(_85.LandmarkFields);
}
};
function __sp_landmarks_addLocality(add){
var _87=new DeviceAPIError(0,"dummy");
if(typeof (add)!="object"){
throw new DeviceAPIError(_87.INVALID_ARG_ERR,"address should be of type object");
}
if((add.street!==undefined)&&(add.street!==null)&&(add.street!=="")){
this.Street=add.street;
}
if((add.city!==undefined)&&(add.city!==null)&&(add.city!=="")){
this.City=add.city;
}
if((add.state!==undefined)&&(add.state!==null)&&(add.state!=="")){
this.state=add.state;
}
if((add.postalCode!==undefined)&&(add.postalCode!==null)&&(add.postalCode!=="")){
this.AreaCode=add.postalCode;
}
if((add.country!==undefined)&&(add.country!==null)&&(add.country!=="")){
this.Country=add.country;
}
if((add.building!==undefined)&&(add.building!==null)&&(add.building!=="")){
this.BuildingName=add.building;
}
if((add.phone!==undefined)&&(add.phone!==null)&&(add.phone!=="")){
this.Telephone=add.phone;
}
};
function __sp_landmarks_addPosition(pos){
var _89=new DeviceAPIError(0,"dummy");
if(typeof (pos)!="object"){
throw new DeviceAPIError(_89.INVALID_ARG_ERR,"position should be of type object");
}
if((pos.longitude!==undefined)&&(pos.longitude!==null)&&(pos.longitude!=="")){
this.Longitude=pos.longitude;
}
if((pos.latitude!==undefined)&&(pos.latitude!==null)&&(pos.latitude!=="")){
this.Latitude=pos.latitude;
}
if((pos.altitude!==undefined)&&(pos.altitude!==null)&&(pos.altitude!=="")){
this.Altitude=pos.altitude;
}
if((pos.hAccuracy!==undefined)&&(pos.hAccuracy!==null)&&(pos.hAccuracy!=="")){
this.HAccuracy=pos.hAccuracy;
}
if((pos.vAccuracy!==undefined)&&(pos.vAccuracy!==null)&&(pos.vAccuracy!=="")){
this.VAccuracy=pos.vAccuracy;
}
};
function __sp_landmarks_addLmObject(lm){
var _8b=false;
var _8c=new DeviceAPIError(0,"dummy");
if((lm.name!==undefined)&&(lm.name!==null)&&(lm.name!=="")){
this.LandmarkName=lm.name;
}
if((lm.description!==undefined)&&(lm.description!==null)&&(lm.description!=="")){
this.LandmarkDesc=lm.description;
}
if((lm.position!==undefined)&&(lm.position!==null)&&(lm.position!=="")){
this.LandmarkPosition=new __sp_landmarks_addPosition(lm.position);
_8b=true;
}
if((lm.coverageRadius!==undefined)&&(lm.coverageRadius!==null)&&(lm.coverageRadius!=="")){
if(_8b){
this.CoverageRadius=lm.coverageRadius;
}else{
throw new DeviceAPIError(_8c.MISSING_ARG_ERR,"missing position");
}
}
if((lm.categoryIds!==undefined)&&(lm.categoryIds!==null)&&(lm.categoryIds!=="")){
if(typeof (lm.categoryIds)!="object"){
throw new DeviceAPIError(_8c.INVALID_ARG_ERR,"categoryids should be of type object");
}
this.CategoryInfo=__sp_add_category_ids_for_names(lm.categoryIds);
if(!this.CategoryInfo){
throw new DeviceAPIError(_8c.MISSING_ARG_ERR,"invalid category");
}
}
if((lm.address!==undefined)&&(lm.address!==null)&&(lm.address!=="")){
this.LandmarkFields=new __sp_landmarks_addLocality(lm.address);
}
this.dummyField="dummyfield";
};
function __sp_landmark_obj(_8d,str){
var _8f=new DeviceAPIError(0,"dummy");
if(_8d.name!==undefined){
if(_8d.name===null){
this.LandmarkName="";
}else{
this.LandmarkName=_8d.name;
}
}
if((_8d.landmarkId===undefined)||(_8d.landmarkId===null)||(_8d.landmarkId==="")){
throw new DeviceAPIError(_8f.MISSING_ARG_ERR,"for updating; id must be supplied");
}else{
this.id=_8d.landmarkId;
}
if(_8d.description!==undefined){
if(_8d.description===null){
this.LandmarkDesc="";
}else{
this.LandmarkDesc=_8d.description;
}
}
if(_8d.position){
this.LandmarkPosition=new __sp_landmark_position_obj_fromJS_2LIW(_8d.position);
}
if(_8d.coverageRadius){
this.CoverageRadius=_8d.coverageRadius;
}
if(_8d.categories){
this.CategoryInfo=__sp_get_category_ids_for_names(_8d.categories);
if(!this.CategoryInfo){
throw new DeviceError("Landmarks: "+str+"Category is invalid",err_bad_argument);
}
}
if(_8d.address){
this.LandmarkFields=new __sp_landmark_address_obj(_8d.address);
}
this.temp="dummy";
};
function __sp_landmarks_iterator_has_next(){
if(this.hasElement){
if(this.lmItem!==null){
return true;
}else{
return false;
}
}else{
this.lmItem=this.iter.getNext();
this.hasElement=true;
if(typeof this.lmItem=="undefined"){
this.lmItem=null;
return false;
}else{
return true;
}
}
};
function __sp_landmarks_iterator_get_next(){
if(this.hasElement){
var _90=new Object();
_90=this.lmItem;
this.lmItem=this.iter.getNext();
if(typeof (this.lmItem)=="undefined"){
this.lmItem=null;
}
return new __sp_device_landmark_obj(_90);
}else{
this.lmItem=this.iter.getNext();
if(typeof this.lmItem=="undefined"){
this.hasElement=true;
this.lmItem=null;
return null;
}else{
this.hasElement=true;
var _91=new Object();
_91=this.lmItem;
this.lmItem=this.iter.getNext();
if(typeof (this.lmItem)=="undefined"){
this.lmItem=null;
}
return new __sp_device_landmark_obj(_91);
}
}
};
function __sp_category_obj(_92){
if(_92.name){
this.CategoryName=_92.name;
}
if(_92.categoryId){
this.id=_92.categoryId;
}
};
function __sp_device_category_obj(_93){
this.categoryId=_93.id;
this.name=_93.CategoryName;
};
var LANDMARKS_APP_ID=270501282;
function __sp_landmarks_startEditor(_94,_95,_96){
error=new DeviceAPIError(0,"dummy");
if((_94===undefined)||(_94===null)||(_94==="")){
throw new DeviceAPIError(error.MISSING_ARG_ERR,"StartEditor:Missing Success Callback");
}
if((typeof _94)!="function"){
throw new DeviceAPIError(error.INVALID_ARG_ERR,"StartEditor:Success Callback must be of type function");
}
if(_95!==undefined){
if((_95!==null)&&(_95!=="")){
throw new DeviceAPIError(error.NOT_SUPPORTED_ERR,"startEditor:landmark item is not supported");
}
}
if((_96!==undefined)&&(_96!==null)&&(_96!=="")){
if((typeof _96)!="function"){
throw new DeviceAPIError(error.INVALID_ARG_ERR,"StartEditor:error callback must be of type function");
}
}
var _97=270501282;
var _98;
function __s60_on_app_exit(){
window.xwidget.onshow=null;
if(_98){
_98();
}
};
var _99=function(_9a,_9b,_9c){
_94(_9a,_9b,_9c);
};
__s60_start_and_wait(_97,"",_99);
};
function __sp_landmarks_category_getList_cb(_9d,_9e,_9f){
var _a0;
var _a1;
var _a2;
if(this.temporarySCb){
_a1=this.temporarySCb;
_a2=this.temporaryECb;
this.temporarySCb=null;
this.temporaryECb=null;
}else{
_a0=glob_obj.getFromArray(_9d);
if(_a0){
_a1=_a0.success_cb;
_a2=_a0.error_cb;
}else{
alert("Landmarks: __sp_landmarks_category_getList_cb: Callback not found ");
return;
}
}
var _a3=null;
if(_9f.ErrorCode||(_9e==4)){
var _a4=convertFromPS2JS(_9f.ErrorCode);
var _a5=new DeviceAPIError(_a4,_9f.ErrorMessage);
if(_a2){
_a2(_a5);
}
}else{
if(_9f.ReturnValue){
_a3=new __sp_landmarks_category_iterator(_9f.ReturnValue);
_a1(_a3);
}
}
glob_obj.removeFromArray(_9d);
};
function __sp_landmarks_category_getList(_a6,_a7,_a8){
try{
var _a9=new DeviceAPIError(0,"dummy");
if((_a6===undefined)||(_a6==="")||(_a6===null)){
throw new DeviceAPIError(_a9.MISSING_ARG_ERR,"callback is missing");
}
if(typeof (_a6)!="function"){
throw new DeviceAPIError(_a9.INVALID_ARG_ERR,"invalid callback argument");
}
var _aa=false;
if((_a8!==undefined)&&(_a8!==null)&&(_a8!=="")){
if(typeof (_a8)!="function"){
throw new DeviceAPIError(_a9.INVALID_ARG_ERR,"invalid error callback argument");
}else{
_aa=true;
}
}
var _ab=new Object();
modifyObjectBaseProp(_ab);
_ab.Type="Category";
if((_a7!==undefined)&&(_a7!==null)&&(_a7!=="")){
if(typeof (_a7)!="string"){
throw new DeviceAPIError(_a9.INVALID_ARG_ERR,"name must be a string");
}
}
if(_a7){
_ab.Filter=new Object();
modifyObjectBaseProp(_ab.Filter);
_ab.Filter.CategoryName=_a7;
_ab.Filter.PreviousMatchesOnly=false;
}
this.temporarySCb=_a6;
this.temporaryECb=_a8;
var _ac=this.so.IDataSource.GetList(_ab,this.getCategoriesCb);
if(_ac.TransactionID){
glob_obj.addToGlobalArray(_ac.TransactionID,_a6,_a8);
}
if(_ac.ErrorCode!=0){
switch(_ac.ErrorCode){
case 1003:
throw new DeviceAPIError(_a9.MISSING_ARG_ERR,_ac.ErrorMessage);
break;
case 1002:
throw new DeviceAPIError(_a9.INVALID_ARG_ERR,_ac.ErrorMessage);
break;
case 1004:
throw new DeviceAPIError(_a9.NOT_SUPPORTED_ERR,_ac.ErrorMessage);
break;
case 1000:
throw new DeviceAPIError(_a9.INVALID_ARG_ERR,_ac.ErrorMessage);
break;
default:
throw new DeviceAPIError(-101,"unknown error message");
}
}
return _ac.TransactionID;
}
catch(e){
throw e;
}
};
function __sp_landmarks_category_add_cb(_ad,_ae,_af){
var _b0;
var _b1;
var _b2;
if(this.temporarySCb){
category_cb=this.temporarySCb;
_b2=this.temporaryECb;
this.temporarySCb=null;
this.temporaryECb=null;
}else{
_b0=glob_obj.getFromArray(_ad);
if(_b0){
_b1=_b0.success_cb;
_b2=_b0.error_cb;
}else{
alert("Landmarks: __sp_landmarks_category_add_cb: Callback not found ");
return;
}
}
var id=null;
if(_ae==4||_af.ErrorCode){
var _b4=convertFromPS2JS(_af.ErrorCode);
var _b5=new DeviceAPIError(_b4,_af.ErrorMessage);
if(_b2){
_b2(_b5);
}
}else{
if(_af.ReturnValue){
id=_af.ReturnValue;
}
_b1(id);
}
glob_obj.removeFromArray(_ad);
};
function __sp_landmarks_category_add(_b6,_b7,_b8){
try{
var _b9=new DeviceAPIError(0,"dummy");
var _ba=true;
if(_b6===undefined){
throw new DeviceAPIError(_b9.MISSING_ARG_ERR,"AddSucessCallback is missing");
}else{
if(((_b6===null)||(_b6===""))&&(typeof (_b6)!="number")){
throw new DeviceAPIError(_b9.MISSING_ARG_ERR,"AddSucessCallback is missing");
}else{
if(typeof (_b6)!="function"){
throw new DeviceAPIError(_b9.INVALID_ARG_ERR,"invalid AddSucessCallback argument");
}
}
}
if(_b7===undefined||_b7===null){
throw new DeviceAPIError(_b9.MISSING_ARG_ERR,"CategoryItem is missing");
}else{
if(typeof (_b7)!=="object"){
throw new DeviceAPIError(_b9.INVALID_ARG_ERR,"invalid CategoryItem argument");
}
}
if((_b8!=undefined)){
if((!_b8)&&(typeof (_b8)!="number")){
_ba=false;
}else{
if((typeof (_b8)!="function")){
throw new DeviceAPIError(_b9.INVALID_ARG_ERR,"invalid ErrorCallback callback");
}
}
}else{
_ba=false;
}
var _bb=new Object();
modifyObjectBaseProp(_bb);
_bb.Type="Category";
_bb.Data=new __sp_category_obj(_b7);
this.temporarySCb=_b6;
this.temporaryECb=_b8;
var _bc=this.so.IDataSource.Add(_bb,this.addCategoryCb);
if(_bc.TransactionID){
glob_obj.addToGlobalArray(_bc.TransactionID,_b6,_b8);
}
if(_bc.ErrorCode!=0){
switch(_bc.ErrorCode){
case err_missing_argument:
throw new DeviceAPIError(_b9.MISSING_ARG_ERR,_bc.ErrorMessage);
break;
case err_bad_argument:
throw new DeviceAPIError(_b9.INVALID_ARG_ERR,_bc.ErrorMessage);
break;
case err_ServiceNotSupported:
throw new DeviceAPIError(_b9.NOT_SUPPORTED_ERR,_bc.ErrorMessage);
break;
case err_InvalidService_Argument:
throw new DeviceAPIError(_b9.INVALID_ARG_ERR,_bc.ErrorMessage);
break;
default:
throw new DeviceAPIError(-101,"unknown error message");
}
}
return _bc.TransactionID;
}
catch(e){
throw e;
}
};
function __sp_landmarks_add_cb(_bd,_be,_bf){
var id=null;
var _c1;
var _c2;
var _c3;
if(this.temporarySCb){
category_cb=this.temporarySCb;
_c3=this.temporaryECb;
this.temporarySCb=null;
this.temporaryECb=null;
}else{
_c1=glob_obj.getFromArray(_bd);
if(_c1){
_c2=_c1.success_cb;
_c3=_c1.error_cb;
}else{
alert("Landmarks: __sp_landmarks_add_cb: Callback not found ");
return;
}
}
if(_be==4||_bf.ErrorCode){
var _c4=convertFromPS2JS(_bf.ErrorCode);
var _c5=new DeviceAPIError(_c4,_bf.ErrorMessage);
if(_c3){
_c3(_c5);
}
}else{
if(_bf.ReturnValue){
id=_bf.ReturnValue;
}
_c2(id);
}
glob_obj.removeFromArray(_bd);
};
function __sp_landmarks_add(_c6,_c7,_c8){
try{
var _c9=new DeviceAPIError(0,"dummy");
var _ca=true;
if(_c6===undefined){
throw new DeviceAPIError(_c9.MISSING_ARG_ERR,"AddSucessCallback is missing");
}else{
if(((_c6===null)||(_c6===""))&&(typeof (_c6)!="number")){
throw new DeviceAPIError(_c9.MISSING_ARG_ERR,"AddSucessCallback is missing");
}else{
if(typeof (_c6)!="function"){
throw new DeviceAPIError(_c9.INVALID_ARG_ERR,"invalid AddSucessCallback argument");
}
}
}
if((_c7===undefined)||(_c7===null)||(_c7==="")){
throw new DeviceAPIError(_c9.MISSING_ARG_ERR,"LandmarkItem is missing");
}else{
if(typeof (_c7)!=="object"){
throw new DeviceAPIError(_c9.INVALID_ARG_ERR,"invalid LandmarkItem argument");
}
}
if((_c8!=undefined)){
if((!_c8)&&(typeof (_c8)!="number")){
_ca=false;
}else{
if((typeof (_c8)!="function")){
throw new DeviceAPIError(_c9.INVALID_ARG_ERR,"invalid ErrorCallback callback");
}
}
}else{
_ca=false;
}
var str="addLandmark: ";
var _cc=new Object();
modifyObjectBaseProp(_cc);
_cc.Type="Landmark";
_cc.Data=new __sp_landmarks_addLmObject(_c7);
this.temporarySCb=_c6;
this.temporaryECb=_c8;
var _cd=this.so.IDataSource.Add(_cc,this.addLandmarkCb);
if(_cd.TransactionID){
glob_obj.addToGlobalArray(_cd.TransactionID,_c6,_c8);
}
if(_cd.ErrorCode!=0){
switch(_cd.ErrorCode){
case err_missing_argument:
throw new DeviceAPIError(_c9.MISSING_ARG_ERR,_cd.ErrorMessage);
break;
case err_bad_argument:
throw new DeviceAPIError(_c9.INVALID_ARG_ERR,_cd.ErrorMessage);
break;
case err_ServiceNotSupported:
throw new DeviceAPIError(_c9.NOT_SUPPORTED_ERR,_cd.ErrorMessage);
break;
case err_InvalidService_Argument:
throw new DeviceAPIError(_c9.INVALID_ARG_ERR,_cd.ErrorMessage);
break;
default:
throw new DeviceAPIError(-101,"unknown error message");
}
}
return _cd.TransactionID;
}
catch(e){
throw e;
}
};
function __sp_landmarks_delete_cb(_ce,_cf,_d0){
var _d1;
var _d2;
var _d3;
if(this.temporarySCb){
category_cb=this.temporarySCb;
_d2=this.temporaryECb;
this.temporarySCb=null;
this.temporaryECb=null;
}else{
_d3=glob_obj.getFromArray(_ce);
if(_d3){
_d1=_d3.success_cb;
_d2=_d3.error_cb;
}else{
alert("Landmarks: __sp_landmarks_delete_cb: Callback not found ");
return;
}
}
if(_cf==4||_d0.ErrorCode){
var _d4=convertFromPS2JS(_d0.ErrorCode);
var _d5=new DeviceAPIError(_d4,_d0.ErrorMessage);
if(_d2){
_d2(_d5);
}
}else{
_d1();
}
glob_obj.removeFromArray(_ce);
};
function __sp_landmarks_delete(_d6,_d7,_d8){
try{
var _d9=new DeviceAPIError(0,"dummy");
var _da=true;
if(_d6===undefined){
throw new DeviceAPIError(_d9.MISSING_ARG_ERR,"SucessCallback is missing");
}else{
if(((_d6===null)||(_d6===""))&&(typeof (_d6)!="number")){
throw new DeviceAPIError(_d9.MISSING_ARG_ERR,"SucessCallback is missing");
}else{
if(typeof (_d6)!="function"){
throw new DeviceAPIError(_d9.INVALID_ARG_ERR,"invalid SucessCallback argument");
}
}
}
if(_d7===undefined||_d7===null){
throw new DeviceAPIError(_d9.MISSING_ARG_ERR,"landmarkId is missing");
}else{
if(typeof (_d7)!=="string"){
throw new DeviceAPIError(_d9.INVALID_ARG_ERR,"invalid landmarkId argument");
}
}
if((_d8!=undefined)){
if((!_d8)&&(typeof (_d8)!="number")){
_da=false;
}else{
if((typeof (_d8)!="function")){
throw new DeviceAPIError(_d9.INVALID_ARG_ERR,"invalid ErrorCallback callback");
}
}
}else{
_da=false;
}
var _db=new Object();
modifyObjectBaseProp(_db);
_db.Type="Landmark";
_db.Data=new Object();
modifyObjectBaseProp(_db.Data);
_db.Data.id=_d7;
this.temporarySCb=_d6;
this.temporaryECb=_d8;
var _dc=this.so.IDataSource.Delete(_db,this.deleteLandmarkCb);
if(_dc.TransactionID){
glob_obj.addToGlobalArray(_dc.TransactionID,_d6,_d8);
}
if(_dc.ErrorCode!=0){
switch(_dc.ErrorCode){
case err_missing_argument:
throw new DeviceAPIError(_d9.MISSING_ARG_ERR,_dc.ErrorMessage);
break;
case err_bad_argument:
throw new DeviceAPIError(_d9.INVALID_ARG_ERR,_dc.ErrorMessage);
break;
case err_ServiceNotSupported:
throw new DeviceAPIError(_d9.NOT_SUPPORTED_ERR,_dc.ErrorMessage);
break;
case err_InvalidService_Argument:
throw new DeviceAPIError(_d9.INVALID_ARG_ERR,_dc.ErrorMessage);
break;
default:
throw new DeviceAPIError(-101,"unknown error message");
}
}
return _dc.TransactionID;
}
catch(e){
throw e;
}
};
function __sp_landmarks_update_cb(_dd,_de,_df){
var _e0;
var _e1;
var _e2;
if(this.temporarySCb){
category_cb=this.temporarySCb;
_e1=this.temporaryECb;
this.temporarySCb=null;
this.temporaryECb=null;
}else{
_e2=glob_obj.getFromArray(_dd);
if(_e2){
_e0=_e2.success_cb;
_e1=_e2.error_cb;
}else{
alert("Landmarks: __sp_landmarks_update_cb: Callback not found ");
return;
}
}
if(_de==4||_df.ErrorCode){
var _e3=convertFromPS2JS(_df.ErrorCode);
var _e4=new DeviceAPIError(_e3,_df.ErrorMessage);
if(_e1){
_e1(_e4);
}
}else{
_e0();
}
glob_obj.removeFromArray(_dd);
};
function __sp_landmarks_update(_e5,_e6,_e7){
try{
var _e8=new DeviceAPIError(0,"dummy");
var _e9=true;
if(_e5===undefined){
throw new DeviceAPIError(_e8.MISSING_ARG_ERR,"SuccessCallback is missing");
}else{
if(((_e5===null)||(_e5===""))&&(typeof (_e5)!="number")){
throw new DeviceAPIError(_e8.MISSING_ARG_ERR,"SuccessCallback is missing");
}else{
if(typeof (_e5)!="function"){
throw new DeviceAPIError(_e8.INVALID_ARG_ERR,"invalid SuccessCallback argument");
}
}
}
if(_e6===undefined||_e6===null||_e6===""){
throw new DeviceAPIError(_e8.MISSING_ARG_ERR,"LandmarkItem is missing");
}else{
if(typeof (_e6)!=="object"){
throw new DeviceAPIError(_e8.INVALID_ARG_ERR,"invalid LandmarkItem argument");
}
}
if((_e7!=undefined)){
if((!_e7)&&(typeof (_e7)!="number")){
_e9=false;
}else{
if((typeof (_e7)!="function")){
throw new DeviceAPIError(_e8.INVALID_ARG_ERR,"invalid ErrorCallback callback");
}
}
}else{
_e9=false;
}
var str="updateLandmark: ";
var _eb=new Object();
modifyObjectBaseProp(_eb);
_eb.Type="Landmark";
_eb.Data=new __sp_landmark_obj(_e6,str);
this.temporarySCb=_e5;
this.temporaryECb=_e7;
var _ec=this.so.IDataSource.Add(_eb,this.updateLandmarkCb);
if(_ec.TransactionID){
glob_obj.addToGlobalArray(_ec.TransactionID,_e5,_e7);
}
if(_ec.ErrorCode!=0){
switch(_ec.ErrorCode){
case err_missing_argument:
throw new DeviceAPIError(_e8.MISSING_ARG_ERR,_ec.ErrorMessage);
break;
case err_bad_argument:
throw new DeviceAPIError(_e8.INVALID_ARG_ERR,_ec.ErrorMessage);
break;
case err_ServiceNotSupported:
throw new DeviceAPIError(_e8.NOT_SUPPORTED_ERR,_ec.ErrorMessage);
break;
case err_InvalidService_Argument:
throw new DeviceAPIError(_e8.INVALID_ARG_ERR,_ec.ErrorMessage);
break;
default:
throw new DeviceAPIError(-101,"unknown error message");
}
}
return _ec.TransactionID;
}
catch(e){
throw e;
}
};
function __sp_landmarks_category_update_cb(_ed,_ee,_ef){
var _f0;
var _f1;
var _f2;
if(this.temporarySCb){
category_cb=this.temporarySCb;
_f1=this.temporaryECb;
this.temporarySCb=null;
this.temporaryECb=null;
}else{
_f2=glob_obj.getFromArray(_ed);
if(_f2){
_f0=_f2.success_cb;
_f1=_f2.error_cb;
}else{
alert("Landmarks: __sp_landmarks_category_update_cb: Callback not found ");
return;
}
}
if(_ee==4||_ef.ErrorCode){
var _f3=convertFromPS2JS(_ef.ErrorCode);
var _f4=new DeviceAPIError(_f3,_ef.ErrorMessage);
if(_f1){
_f1(_f4);
}
}else{
_f0();
}
glob_obj.removeFromArray(_ed);
};
function __sp_landmarks_category_update(_f5,_f6,_f7){
try{
var _f8=new DeviceAPIError(0,"dummy");
var _f9=true;
if(_f5===undefined){
throw new DeviceAPIError(_f8.MISSING_ARG_ERR,"SucessCallback is missing");
}else{
if(((_f5===null)||(_f5===""))&&(typeof (_f5)!="number")){
throw new DeviceAPIError(_f8.MISSING_ARG_ERR,"SucessCallback is missing");
}else{
if(typeof (_f5)!="function"){
throw new DeviceAPIError(_f8.INVALID_ARG_ERR,"invalid SucessCallback argument");
}
}
}
if(_f6===undefined||_f6===null||_f6===""){
throw new DeviceAPIError(_f8.MISSING_ARG_ERR,"CategoryItem is missing");
}else{
if(typeof (_f6)!=="object"){
throw new DeviceAPIError(_f8.INVALID_ARG_ERR,"invalid CategoryItem argument");
}
}
if((_f6.categoryId===undefined)||(_f6.categoryId===null)||(_f6.categoryId==="")){
throw new DeviceAPIError(_f8.MISSING_ARG_ERR,"categoryId is missing");
}
if(typeof (_f6.categoryId)!="string"){
throw new DeviceAPIError(_f8.INVALID_ARG_ERR,"category Id must be a string");
}
if((_f7!=undefined)){
if((!_f7)&&(typeof (_f7)!="number")){
_f9=false;
}else{
if((typeof (_f7)!="function")){
throw new DeviceAPIError(_f8.INVALID_ARG_ERR,"invalid ErrorCallback callback");
}
}
}else{
_f9=false;
}
var _fa=new Object();
modifyObjectBaseProp(_fa);
_fa.Type="Category";
_fa.Data=new __sp_category_obj(_f6);
this.temporarySCb=_f5;
this.temporaryECb=_f7;
var _fb=this.so.IDataSource.Add(_fa,this.updateCategoryCb);
if(_fb.TransactionID){
glob_obj.addToGlobalArray(_fb.TransactionID,_f5,_f7);
}
if(_fb.ErrorCode!=0){
switch(_fb.ErrorCode){
case err_missing_argument:
throw new DeviceAPIError(_f8.MISSING_ARG_ERR,_fb.ErrorMessage);
break;
case err_bad_argument:
throw new DeviceAPIError(_f8.INVALID_ARG_ERR,_fb.ErrorMessage);
break;
case err_ServiceNotSupported:
throw new DeviceAPIError(_f8.NOT_SUPPORTED_ERR,_fb.ErrorMessage);
break;
case err_InvalidService_Argument:
throw new DeviceAPIError(_f8.INVALID_ARG_ERR,_fb.ErrorMessage);
break;
default:
throw new DeviceAPIError(-101,"unknown error message");
}
}
return _fb.TransactionID;
}
catch(e){
throw e;
}
};
function __sp_landmarks_category_delete_cb(_fc,_fd,_fe){
var _ff;
var _100;
var _101;
if(this.temporarySCb){
category_cb=this.temporarySCb;
_100=this.temporaryECb;
this.temporarySCb=null;
this.temporaryECb=null;
}else{
_101=glob_obj.getFromArray(_fc);
if(_101){
_ff=_101.success_cb;
_100=_101.error_cb;
}else{
alert("Landmarks: __sp_landmarks_category_delete_cb: Callback not found ");
return;
}
}
if(_fd==4||_fe.ErrorCode){
var _102=convertFromPS2JS(_fe.ErrorCode);
var _103=new DeviceAPIError(_102,_fe.ErrorMessage);
if(_100){
_100(_103);
}
}else{
_ff();
}
glob_obj.removeFromArray(_fc);
};
function __sp_landmarks_category_delete(_104,_105,_106){
try{
var _107=new DeviceAPIError(0,"dummy");
var _108=true;
if(_104===undefined){
throw new DeviceAPIError(_107.MISSING_ARG_ERR,"SucessCallback is missing");
}else{
if(((_104===null)||(_104===""))&&(typeof (_104)!="number")){
throw new DeviceAPIError(_107.MISSING_ARG_ERR,"SucessCallback is missing");
}else{
if(typeof (_104)!="function"){
throw new DeviceAPIError(_107.INVALID_ARG_ERR,"invalid SucessCallback argument");
}
}
}
if(_105===undefined||_105===null){
throw new DeviceAPIError(_107.MISSING_ARG_ERR,"categoryId is missing");
}else{
if(typeof (_105)!=="string"){
throw new DeviceAPIError(_107.INVALID_ARG_ERR,"invalid categoryId argument");
}
}
if((_106!=undefined)){
if((!_106)&&(typeof (_106)!="number")){
_108=false;
}else{
if((typeof (_106)!="function")){
throw new DeviceAPIError(_107.INVALID_ARG_ERR,"invalid ErrorCallback callback");
}
}
}else{
_108=false;
}
var _109=new Object();
modifyObjectBaseProp(_109);
_109.Type="Category";
_109.Data=new Object();
modifyObjectBaseProp(_109.Data);
_109.Data.id=_105;
this.temporarySCb=_104;
this.temporaryECb=_106;
var rval=this.so.IDataSource.Delete(_109,this.deleteCategoryCb);
if(rval.TransactionID){
glob_obj.addToGlobalArray(rval.TransactionID,_104,_106);
}
if(rval.ErrorCode!=0){
switch(rval.ErrorCode){
case err_missing_argument:
throw new DeviceAPIError(_107.MISSING_ARG_ERR,rval.ErrorMessage);
break;
case err_bad_argument:
throw new DeviceAPIError(_107.INVALID_ARG_ERR,rval.ErrorMessage);
break;
case err_ServiceNotSupported:
throw new DeviceAPIError(_107.NOT_SUPPORTED_ERR,rval.ErrorMessage);
break;
case err_InvalidService_Argument:
throw new DeviceAPIError(_107.INVALID_ARG_ERR,rval.ErrorMessage);
break;
default:
throw new DeviceAPIError(-101,"unknown error message");
}
}
return rval.TransactionID;
}
catch(e){
throw e;
}
};
function __sp_landmarks_getList_cb(arg1,arg2,arg3){
var iter=null;
var _10f;
var _110;
var _111;
if(this.temporarySCb){
category_cb=this.temporarySCb;
_110=this.temporaryECb;
this.temporarySCb=null;
this.temporaryECb=null;
}else{
_111=glob_obj.getFromArray(arg1);
if(_111){
_10f=_111.success_cb;
_110=_111.error_cb;
}else{
alert("Landmarks: __sp_landmarks_getList_cb: Callback not found ");
return;
}
}
if(arg3.ErrorCode||(arg2==4)){
var _112=convertFromPS2JS(arg3.ErrorCode);
var _113=new DeviceAPIError(_112,arg3.ErrorMessage);
if(_110){
_110(_113);
}
}else{
if(arg3.ReturnValue){
iter=new __sp_landmarks_iterator(arg3.ReturnValue);
}
_10f(iter);
}
glob_obj.removeFromArray(arg1);
};
function __sp_landmarks_getList(_114,_115,_116){
try{
var _117=new DeviceAPIError(0,"dummy");
var _118=false;
var _119=false;
var _11a=false;
if((_114===undefined)||(_114===null)||(_114==="")){
throw new DeviceAPIError(_117.MISSING_ARG_ERR,"SucessCallback is missing");
}
if(typeof (_114)!="function"){
throw new DeviceAPIError(_117.INVALID_ARG_ERR,"invalid SucessCallback argument");
}
if((_116!==undefined)&&(_116!=="")&&(_116!==null)){
if((typeof (_116)!="function")){
throw new DeviceAPIError(_117.INVALID_ARG_ERR,"invalid error callback");
}else{
_118=true;
}
}
var _11b=new Object();
modifyObjectBaseProp(_11b);
_11b.Type="Landmark";
_11b.Filter=new Object();
if((_115===undefined)||(_115===null)||(_115==="")){
_11b.Filter.dummy="dummy";
}else{
if(typeof (_115)=="string"){
_11b.Filter.LandmarkName=_115;
}else{
if(typeof (_115)!="object"){
throw new DeviceAPIError(_117.INVALID_ARG_ERR,"invalid match criteria");
}else{
if((_115.name!==undefined)&&(_115.name!==null)&&(_115.name!=="")){
_11b.Filter.LandmarkName=_115.name;
}
if((_115.description!==undefined)&&(_115.description!==null)&&(_115.description!=="")){
_11b.Filter.LandmarkDesc=_115.description;
}
if((_115.categoryId!==undefined)&&(_115.categoryId!==null)&&(_115.categoryId!=="")){
_11b.Filter.categoryId=_115.categoryId;
}
if((_115.position!==undefined)&&(_115.position!==null)&&(_115.position!=="")){
if(typeof (_115.position)!="object"){
throw new DeviceAPIError(_117.INVALID_ARG_ERR,"position must be an object");
}else{
_11b.Filter.LandmarkPosition=new __sp_landmark_position_obj(_115.position);
}
}
if((_115.coverageRadiusUsed!==undefined)&&(_115.coverageRadiusUsed!==null)&&(_115.coverageRadiusUsed!=="")){
if(typeof (_115.coverageRadiusUsed)!="number"){
throw new DeviceAPIError(_117.INVALID_ARG_ERR,"coverageRadiusUsed should be number");
}else{
_11b.Filter.CoverageRadiusOption=_115.coverageRadiusUsed;
}
}
if((_115.searchRadius!==undefined)&&(_115.searchRadius!==null)&&(_115.searchRadius!=="")){
if(typeof (_115.searchRadius)!="number"){
throw new DeviceAPIError(_117.INVALID_ARG_ERR,"searchRadius should be number");
}else{
_11b.Filter.MaximumDistance=_115.searchRadius;
}
}
if((_115.area!==undefined)&&(_115.area!==null)&&(_115.area!=="")){
if(typeof (_115.area)!="object"){
throw new DeviceAPIError(_117.INVALID_ARG_ERR,"area must be an object");
}else{
_11b.Filter.BoundedArea=new __sp_landmark_bounded_area_obj(_115.area);
}
}
}
}
}
this.temporarySCb=_114;
this.temporaryECb=_116;
var rval=this.so.IDataSource.GetList(_11b,this.getLandmarksCb);
if(rval.TransactionID){
glob_obj.addToGlobalArray(rval.TransactionID,_114,_116);
}
if(rval.ErrorCode!=0){
switch(rval.ErrorCode){
case 1003:
throw new DeviceAPIError(_117.MISSING_ARG_ERR,rval.ErrorMessage);
break;
case 1002:
throw new DeviceAPIError(_117.INVALID_ARG_ERR,rval.ErrorMessage);
break;
case 1004:
throw new DeviceAPIError(_117.NOT_SUPPORTED_ERR,rval.ErrorMessage);
break;
case 1000:
throw new DeviceAPIError(_117.INVALID_ARG_ERR,rval.ErrorMessage);
break;
default:
throw new DeviceAPIError(-101,"unknown error message");
}
}
return rval.TransactionID;
}
catch(e){
throw e;
}
};
function __sp_landmarks_import_cb(arg1,arg2,arg3){
var iter=null;
var _121;
var _122;
var _123;
if(this.temporarySCb){
category_cb=this.temporarySCb;
_122=this.temporaryECb;
this.temporarySCb=null;
this.temporaryECb=null;
}else{
_123=glob_obj.getFromArray(arg1);
if(_123){
_121=_123.success_cb;
_122=_123.error_cb;
}else{
alert("Landmarks: __sp_landmarks_import_cb: Callback not found ");
return;
}
}
if(arg2==4||arg3.ErrorCode){
var _124=convertFromPS2JS(arg3.ErrorCode);
var _125=new DeviceAPIError(_124,arg3.ErrorMessage);
if(_122){
_122(_125);
}
}else{
if(arg3.ReturnValue){
iter=new __sp_landmarks_iterator(arg3.ReturnValue);
}
_121(iter);
}
glob_obj.removeFromArray(arg1);
};
function __sp_landmarks_import(_126,_127,_128,_129){
try{
var _12a=new DeviceAPIError(0,"dummy");
var _12b=true;
if(_126===undefined){
throw new DeviceAPIError(_12a.MISSING_ARG_ERR,"LandmarksItrCallback is missing");
}else{
if(((_126===null)||(_126===""))&&(typeof (_126)!="number")){
throw new DeviceAPIError(_12a.MISSING_ARG_ERR,"LandmarksItrCallback is missing");
}else{
if(typeof (_126)!="function"){
throw new DeviceAPIError(_12a.INVALID_ARG_ERR,"invalid LandmarksItrCallback argument");
}
}
}
if(_127===undefined||_127===null){
throw new DeviceAPIError(_12a.MISSING_ARG_ERR,"sourceFileUri is missing");
}else{
if(typeof (_127)!=="string"){
throw new DeviceAPIError(_12a.INVALID_ARG_ERR,"invalid sourceFileUri argument");
}
}
if(_128===undefined||_128===null){
throw new DeviceAPIError(_12a.MISSING_ARG_ERR,"mimetype is missing");
}else{
if(typeof (_128)!=="string"){
throw new DeviceAPIError(_12a.INVALID_ARG_ERR,"invalid mimetype argument");
}
}
if((_129!=undefined)){
if((!_129)&&(typeof (_129)!="number")){
_12b=false;
}else{
if((typeof (_129)!="function")){
throw new DeviceAPIError(_12a.INVALID_ARG_ERR,"invalid ErrorCallback callback");
}
}
}else{
_12b=false;
}
var _12c=new Object();
modifyObjectBaseProp(_12c);
_12c.Type="Landmark";
_12c.Data=new Object();
modifyObjectBaseProp(_12c.Data);
if(_127.slice(0,7)=="file://"){
_127=_127.slice(7);
}else{
if(_127.slice(0,8)=="file:///"){
_127=_127.slice(8);
}else{
throw new DeviceAPIError(_12a.INVALID_ARG_ERR,"sourceFileUri is not in URI format");
}
}
while(_127.search("/")!=-1){
_127=_127.replace("/","\\");
}
_12c.Data.SourceFile=_127;
_12c.Data.MimeType=_128;
this.temporarySCb=_126;
this.temporaryECb=_129;
var rval=this.so.IDataSource.Import(_12c,this.importLandmarksCb);
if(rval.TransactionID){
glob_obj.addToGlobalArray(rval.TransactionID,_126,_129);
}
if(rval.ErrorCode!=0){
switch(rval.ErrorCode){
case err_missing_argument:
throw new DeviceAPIError(_12a.MISSING_ARG_ERR,rval.ErrorMessage);
break;
case err_bad_argument:
throw new DeviceAPIError(_12a.INVALID_ARG_ERR,rval.ErrorMessage);
break;
case err_ServiceNotSupported:
throw new DeviceAPIError(_12a.NOT_SUPPORTED_ERR,rval.ErrorMessage);
break;
case err_InvalidService_Argument:
throw new DeviceAPIError(_12a.INVALID_ARG_ERR,rval.ErrorMessage);
break;
default:
throw new DeviceAPIError(-101,"unknown error message");
}
}
return rval.TransactionID;
}
catch(e){
throw e;
}
};
function __sp_landmarks_export_cb(arg1,arg2,arg3){
var _131;
var _132;
var _133;
if(this.temporarySCb){
category_cb=this.temporarySCb;
_132=this.temporaryECb;
this.temporarySCb=null;
this.temporaryECb=null;
}else{
_133=glob_obj.getFromArray(arg1);
if(_133){
_131=_133.success_cb;
_132=_133.error_cb;
}else{
alert("Landmarks: __sp_landmarks_export_cb: Callback not found ");
return;
}
}
if(arg2==4||arg3.ErrorCode){
var _134=convertFromPS2JS(arg3.ErrorCode);
var _135=new DeviceAPIError(_134,arg3.ErrorMessage);
if(_132){
_132(_135);
}
}else{
_131();
}
glob_obj.removeFromArray(arg1);
};
function __sp_landmarks_export(_136,_137,_138,_139,_13a){
try{
var _13b=new DeviceAPIError(0,"dummy");
var _13c=true;
if(_136===undefined){
throw new DeviceAPIError(_13b.MISSING_ARG_ERR,"SuccessCallback is missing");
}else{
if(((_136===null)||(_136===""))&&(typeof (_136)!="number")){
throw new DeviceAPIError(_13b.MISSING_ARG_ERR,"SuccessCallback is missing");
}else{
if(typeof (_136)!="function"){
throw new DeviceAPIError(_13b.INVALID_ARG_ERR,"invalid SuccessCallback argument");
}
}
}
if(_137===undefined||_137===null){
throw new DeviceAPIError(_13b.MISSING_ARG_ERR,"landmarkIdList is missing");
}else{
if(typeof (_137)!=="object"){
throw new DeviceAPIError(_13b.INVALID_ARG_ERR,"invalid landmarkIdList argument");
}
}
if(_138===undefined||_138===null){
throw new DeviceAPIError(_13b.MISSING_ARG_ERR,"destFileUri is missing");
}else{
if(typeof (_138)!=="string"){
throw new DeviceAPIError(_13b.INVALID_ARG_ERR,"invalid destFileUri argument");
}
}
if(_139===undefined||_139===null){
throw new DeviceAPIError(_13b.MISSING_ARG_ERR,"mimetype is missing");
}else{
if(typeof (_139)!=="string"){
throw new DeviceAPIError(_13b.INVALID_ARG_ERR,"invalid mimetype argument");
}
}
if((_13a!=undefined)){
if((!_13a)&&(typeof (_13a)!="number")){
_13c=false;
}else{
if((typeof (_13a)!="function")){
throw new DeviceAPIError(_13b.INVALID_ARG_ERR,"invalid ErrorCallback callback");
}
}
}else{
_13c=false;
}
var _13d=new Object();
modifyObjectBaseProp(_13d);
_13d.Type="Landmark";
_13d.Data=new Object();
modifyObjectBaseProp(_13d.Data);
if(_138.slice(0,7)=="file://"){
_138=_138.slice(7);
}else{
if(_138.slice(0,8)=="file:///"){
_138=_138.slice(8);
}else{
throw new DeviceAPIError(_13b.INVALID_ARG_ERR,"destFileUri is not in URI format");
}
}
while(_138.search("/")!=-1){
_138=_138.replace("/","\\");
}
_13d.Data.DestinationFile=_138;
_13d.Data.IdList=_137;
_13d.Data.MimeType=_139;
this.temporarySCb=_136;
this.temporaryECb=_13a;
var rval=this.so.IDataSource.Export(_13d,this.exportLandmarksCb);
if(rval.TransactionID){
glob_obj.addToGlobalArray(rval.TransactionID,_136,_13a);
}
if(rval.ErrorCode!=0){
switch(rval.ErrorCode){
case err_missing_argument:
throw new DeviceAPIError(_13b.MISSING_ARG_ERR,rval.ErrorMessage);
break;
case err_bad_argument:
throw new DeviceAPIError(_13b.INVALID_ARG_ERR,rval.ErrorMessage);
break;
case err_ServiceNotSupported:
throw new DeviceAPIError(_13b.NOT_SUPPORTED_ERR,rval.ErrorMessage);
break;
case err_InvalidService_Argument:
throw new DeviceAPIError(_13b.INVALID_ARG_ERR,rval.ErrorMessage);
break;
default:
throw new DeviceAPIError(-101,"unknown error message");
}
}
return rval.TransactionID;
}
catch(e){
throw e;
}
};
function __sp_landmarks_organize_cb(arg1,arg2,arg3){
var _142;
var _143;
if(this.temporarySCb){
category_cb=this.temporarySCb;
_143=this.temporaryECb;
this.temporarySCb=null;
this.temporaryECb=null;
}else{
CbObj=glob_obj.getFromArray(arg1);
if(CbObj){
_142=CbObj.success_cb;
_143=CbObj.error_cb;
}else{
alert("Landmarks: __sp_landmarks_organize_cb: Callback not found ");
return;
}
}
if(arg2==4||arg3.ErrorCode){
var _144=convertFromPS2JS(arg3.ErrorCode);
var _145=new DeviceAPIError(_144,arg3.ErrorMessage);
if(_143){
_143(_145);
}
}else{
_142();
}
glob_obj.removeFromArray(arg1);
};
function __sp_landmarks_organize(_146,_147,_148,_149,_14a){
try{
var _14b=new DeviceAPIError(0,"dummy");
var _14c=true;
if(_146===undefined){
throw new DeviceAPIError(_14b.MISSING_ARG_ERR,"SuccessCallback is missing");
}else{
if(((_146===null)||(_146===""))&&(typeof (_146)!="number")){
throw new DeviceAPIError(_14b.MISSING_ARG_ERR,"SuccessCallback is missing");
}else{
if(typeof (_146)!="function"){
throw new DeviceAPIError(_14b.INVALID_ARG_ERR,"invalid SuccessCallback argument");
}
}
}
if(_147===undefined||_147===null){
throw new DeviceAPIError(_14b.MISSING_ARG_ERR,"landmarkIdList is missing");
}else{
if(typeof (_147)!=="object"){
throw new DeviceAPIError(_14b.INVALID_ARG_ERR,"invalid LandmarkItem argument");
}
}
if(_148===undefined||_148===null){
throw new DeviceAPIError(_14b.MISSING_ARG_ERR,"categoryId is missing");
}else{
if(typeof (_148)!=="string"){
throw new DeviceAPIError(_14b.INVALID_ARG_ERR,"invalid categoryId argument");
}
}
if(_149===undefined||_149===null){
_149=true;
}else{
if(typeof (_149)!=="boolean"){
throw new DeviceAPIError(_14b.INVALID_ARG_ERR,"invalid associate argument");
}
}
if((_14a!=undefined)){
if((!_14a)&&(typeof (_14a)!="number")){
_14c=false;
}else{
if((typeof (_14a)!="function")){
throw new DeviceAPIError(_14b.INVALID_ARG_ERR,"invalid ErrorCallback callback");
}
}
}else{
_14c=false;
}
var _14d=new Object();
modifyObjectBaseProp(_14d);
_14d.Type="Landmark";
_14d.Data=new Object();
modifyObjectBaseProp(_14d.Data);
_14d.Data.id=_148;
_14d.Data.IdList=_147;
if(_149){
_14d.OperationType="Associate";
}else{
_14d.OperationType="Disassociate";
}
this.temporarySCb=_146;
this.temporaryECb=_14a;
var rval=this.so.IDataSource.Organise(_14d,this.organizeLandmarksCb);
if(rval.TransactionID){
glob_obj.addToGlobalArray(rval.TransactionID,_146,_14a);
}
if(rval.ErrorCode!=0){
switch(rval.ErrorCode){
case err_missing_argument:
throw new DeviceAPIError(_14b.MISSING_ARG_ERR,rval.ErrorMessage);
break;
case err_bad_argument:
throw new DeviceAPIError(_14b.INVALID_ARG_ERR,rval.ErrorMessage);
break;
case err_ServiceNotSupported:
throw new DeviceAPIError(_14b.NOT_SUPPORTED_ERR,rval.ErrorMessage);
break;
case err_InvalidService_Argument:
throw new DeviceAPIError(_14b.INVALID_ARG_ERR,rval.ErrorMessage);
break;
default:
throw new DeviceAPIError(-101,"unknown error message");
}
}
return rval.TransactionID;
}
catch(e){
throw e;
}
};
function __sp_landmarks_cancel(_14f){
try{
var _150=new DeviceAPIError(0,"dummy");
if((_14f===undefined)||(_14f===null)||(_14f==="")){
throw new DeviceAPIError(_150.MISSING_ARG_ERR,"transactionId is missing");
}
if(typeof (_14f)!="number"){
throw new DeviceAPIError(_150.INVALID_ARG_ERR,"invalid transactionId argument");
}
if(_14f<0){
throw new DeviceAPIError(_150.DATA_NOT_FOUND_ERR,"non-existent transactionId");
}
var _151=new Object();
modifyObjectBaseProp(_151);
_151.TransactionID=_14f;
var rval=this.so.IDataSource.Cancel(_151);
if(rval.ErrorCode!=0){
switch(rval.ErrorCode){
case err_missing_argument:
throw new DeviceAPIError(_150.MISSING_ARG_ERR,rval.ErrorMessage);
break;
case err_bad_argument:
throw new DeviceAPIError(_150.INVALID_ARG_ERR,rval.ErrorMessage);
break;
case err_ServiceNotSupported:
throw new DeviceAPIError(_150.NOT_SUPPORTED_ERR,rval.ErrorMessage);
break;
case err_InvalidService_Argument:
throw new DeviceAPIError(_150.INVALID_ARG_ERR,rval.ErrorMessage);
break;
default:
throw new DeviceAPIError(-101,"unknown error message");
}
}
}
catch(e){
throw e;
}
};
function __device_media_descriptor(_153){
this.interfaceName=_153.interfaceName;
this.version=_153.version;
};
function __device_media_getList(_154,_155,_156,_157){
return this.provider.getList(_154,_155,_156,_157);
};
function __device_media_getThumbnail(_158,_159,_15a){
return this.provider.getThumbnail(_158,_159,_15a);
};
function __device_media_addStreamUri(uri){
return this.provider.addStreamUri(uri);
};
function __device_media_deleteStreamUri(uri){
return this.provider.deleteStreamUri(uri);
};
function __device_media_cancel(_15d){
this.provider.cancel(_15d);
};
function __device_media_refreshMediaDb(uri){
this.provider.refreshMediaDb(uri);
};
function __device_media(_15f){
this.provider=_15f;
this.interfaceName=_15f.descriptor.interfaceName;
this.version=_15f.descriptor.version;
this.SORT_ASCENDING=0;
this.SORT_DESCENDING=1;
this.getList=__device_media_getList;
this.getThumbnail=__device_media_getThumbnail;
this.addStreamUri=__device_media_addStreamUri;
this.deleteStreamUri=__device_media_deleteStreamUri;
this.refreshMediaDb=__device_media_refreshMediaDb;
this.cancel=__device_media_cancel;
};
var __device_media_service_entry={"name":null,"version":null,"proto":__device_media,"descriptor":__device_media_descriptor,"providers":[{"descriptor":__sp_media_descriptor,"instance":__sp_media_instance}]};
function __device_media_descriptor(_160){
this.interfaceName=_160.interfaceName;
this.version=_160.version;
};
function __device_media_getList(_161,_162,_163,_164){
return this.provider.getList(_161,_162,_163,_164);
};
function __device_media_getThumbnail(_165,_166,_167){
return this.provider.getThumbnail(_165,_166,_167);
};
function __device_media_addStreamUri(uri){
return this.provider.addStreamUri(uri);
};
function __device_media_deleteStreamUri(uri){
return this.provider.deleteStreamUri(uri);
};
function __device_media_cancel(_16a){
this.provider.cancel(_16a);
};
function __device_media_refreshMediaDb(uri){
this.provider.refreshMediaDb(uri);
};
function __device_media(_16c){
this.provider=_16c;
this.interfaceName=_16c.descriptor.interfaceName;
this.version=_16c.descriptor.version;
this.SORT_ASCENDING=0;
this.SORT_DESCENDING=1;
this.getList=__device_media_getList;
this.getThumbnail=__device_media_getThumbnail;
this.addStreamUri=__device_media_addStreamUri;
this.deleteStreamUri=__device_media_deleteStreamUri;
this.refreshMediaDb=__device_media_refreshMediaDb;
this.cancel=__device_media_cancel;
};
var __device_media_service_entry={"name":null,"version":null,"proto":__device_media,"descriptor":__device_media_descriptor,"providers":[{"descriptor":__sp_media_descriptor,"instance":__sp_media_instance}]};
var FILESCHMLEN=7;
function __sp_media_descriptor(){
this.interfaceName="media";
if(window.__Service_Interface_Ver){
this.version=__Service_Interface_Ver;
}else{
this.version=1;
}
};
function __sp_device_media_item_build(_16d){
if(!_16d){
return null;
}
var _16e={};
modifyObjectBaseProp(_16e);
if(_16d.FileNameAndPath){
var _16f=_16d.FileNameAndPath.replace(/\\/g,"/");
var _170="file://";
_16e.uri=_170+_16f;
}
if(_16d.MediaType){
var _171=_16d.MediaType;
switch(_171){
case 1:
case 2:
_16e.type="audio";
break;
case 3:
_16e.type="image";
break;
case 4:
_16e.type="video";
break;
case 5:
_16e.type="stream";
break;
default:
break;
}
}
if(_16d.FileName){
if(_16d.MediaType==3){
_16e.title=_16d.FileName;
}
}
if(_16d.FileDate){
_16e.date=new Date(Date.parse(_16d.FileDate));
}
if(_16d.FileSize){
_16e.size=_16d.FileSize;
}
if(_16d.SongName){
_16e.title=_16d.SongName;
}
if(_16d.Artist){
_16e.artist=_16d.Artist;
}
if(_16d.Album){
_16e.album=_16d.Album;
}
if(_16d.Genre){
_16e.genre=_16d.Genre;
}
if(_16d.TrackNumber){
_16e.track=_16d.TrackNumber;
}
if(_16d.Composer){
_16e.composer=_16d.Composer;
}
return _16e;
};
function __sp_media_iterator_get_next(){
var item=this.iter.getNext();
if(typeof item=="undefined"){
return null;
}
var _173=__sp_device_media_item_build(item);
item.close();
return _173;
};
function __sp_media_iterator(_174){
this.iter=_174;
this.next=__sp_media_iterator_get_next;
this.close=function(){
this.iter.close();
};
};
function __sp_media_get_field_name(name,type){
this.error=new DeviceException(0,"Dummy");
if(typeof name!="string"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Media:getList:field is of invalid type");
}
switch(name.toLowerCase()){
case "title":
if(type=="Image"||type=="Video"){
return "FileName";
}else{
return "SongName";
}
case "artist":
return "Artist";
case "album":
return "Album";
case "genre":
return "Genre";
case "track":
return "TrackNumber";
case "composer":
return "Composer";
default:
return null;
}
};
function __sp_media_get_sortfield_name(name,type){
this.error=new DeviceException(0,"Dummy");
if(typeof name!="string"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Media:getList:sortBy is of invalid type");
}
var _179=name.toLowerCase();
if(_179=="date"){
return "FileDate";
}else{
return __sp_media_get_field_name(name,type);
}
};
function __sp_media_get_date_objct(date){
var _17b="";
_17b=date.getFullYear().toString();
if(date.getMonth()<10){
_17b=_17b+("0")+(date.getMonth().toString());
}else{
_17b=_17b+(date.getMonth().toString());
}
var day=date.getDate()-1;
if(day<10){
_17b=_17b+("0")+(day.toString());
}else{
_17b=_17b+(day.toString());
}
_17b=_17b+(":");
if(date.getHours()<10){
_17b=_17b+("0")+(date.getHours().toString());
}else{
_17b=_17b+(date.getHours().toString());
}
if(date.getMinutes()<10){
_17b=_17b+("0")+(date.getMinutes().toString());
}else{
_17b=_17b+(date.getMinutes().toString());
}
if(date.getSeconds()<10){
_17b=_17b+("0")+(date.getSeconds().toString());
}else{
_17b=_17b+(date.getSeconds().toString());
}
return _17b;
};
function __sp_media_getList_cb(arg1,arg2,arg3){
var _180;
var _181;
var _182;
_182=glob_obj.getFromArray(arg1);
if(_182){
_180=_182.success_cb;
_181=_182.error_cb;
}else{
alert("Media : __sp_media_getList_cb: Callback not found ");
return;
}
if(arg3.ErrorCode!=0&&arg3.ErrorCode!=1010){
_181(new DeviceException(arg3.ErrorCode,"Media: getList: Operation Failed"));
return;
}
if(arg2!=event_cancelled){
var iter=null;
if(arg3.ReturnValue){
iter=new __sp_media_iterator(arg3.ReturnValue);
}
_180(iter);
}
glob_obj.removeFromArray(arg1);
};
function __sp_media_getList(_184,_185,_186,_187){
if(!_184){
throw new DeviceException(this.error.MISSING_ARG_ERR,"Media:getList:Callback is missing");
}else{
if(typeof _184!="function"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Media:getList:Callback is of invalid type");
}
}
if(_187){
if(typeof _187!="function"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Media: getList: error callback is invalid");
}
}
if((typeof _185)!="object"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Invalid Argument:"+_185);
}
if(_185){
if(("sortBy" in _185)&&(_185.sortBy==undefined||_185.sortBy==null||_185.sortBy=="")){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Media: getList: sortby is invalid");
}
}
var _188={};
modifyObjectBaseProp(_188);
_188.Type="FileInfo";
_188.Filter={};
modifyObjectBaseProp(_188.Filter);
_188.Sort={};
modifyObjectBaseProp(_188.Sort);
if(_185){
if(_185.type){
if(typeof _185.type!="string"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Media:getList:type is of invalid type");
}
switch(_185.type.toLowerCase()){
case "audio":
_188.Filter.FileType="audio";
break;
case "image":
_188.Filter.FileType="Image";
break;
case "video":
_188.Filter.FileType="Video";
break;
case "stream":
_188.Filter.FileType="StreamingURL";
break;
default:
throw new DeviceException(this.error.INVALID_ARG_ERR,"Media:getList: type is invalid");
}
if(("field" in _185)&&(_185.field==undefined||_185.field==null)){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Media:getList:field is invalid");
}
if(_185.field!=null){
_188.Filter.Key=__sp_media_get_field_name(_185.field.name,_188.Filter.FileType);
if(_188.Filter.Key==null){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Media:getList:key is invalid");
}
if(_185.field.value){
_188.Filter.StartRange=_185.field.value;
if(_188.Filter.Key=="TrackNumber"){
_188.Filter.EndRange=_185.field.value;
}
}
}else{
if(_185.dateRange){
if(typeof _185.dateRange!="object"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Media:getList:dateRange is of invalid type");
}
_188.Filter.Key="FileDate";
if((typeof _185.dateRange.start!="undefined")&&(typeof _185.dateRange.end!="undefined")){
if((typeof _185.dateRange.start!="object")||(_185.dateRange.start=="")||(_185.dateRange.start==null)){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Media:getList:dateRange:start is of invalid type");
}else{
_188.Filter.StartRange=__sp_media_get_date_objct(_185.dateRange.start);
}
if((typeof _185.dateRange.end!="object")||(_185.dateRange.end=="")||(_185.dateRange.end==null)){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Media:getList:dateRange:end is of invalid type");
}else{
_188.Filter.EndRange=__sp_media_get_date_objct(_185.dateRange.end);
}
}else{
throw new DeviceException(this.error.INVALID_ARG_ERR,"Media:getList:start or end of dateRange is missing");
}
}else{
if(("dateRange" in _185)&&(_185.dateRange==0||_185.dateRange==null||_185.dateRange=="")){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Media:getList: dateRange is Invalid");
}
}
}
if(_185.sortBy){
_188.Sort.Key=__sp_media_get_sortfield_name(_185.sortBy,_188.Filter.FileType);
if(_188.Sort.Key==null){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Media:getList:sortBy is invalid");
}
}else{
_188.Sort.Key="FileDate";
}
if(_186){
if(_186==this.SORT_ASCENDING){
_188.Sort.Order="Ascending";
}else{
if(_186==this.SORT_DESCENDING){
_188.Sort.Order="Descending";
}else{
if((_186!=this.SORT_ASCENDING)||(_186!=this.SORT_DESCENDING)){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Media:getList:sortBy is invalid");
}
}
}
}else{
_188.Sort.Order="Ascending";
}
}else{
throw new DeviceException(this.error.MISSING_ARG_ERR,"Media:type is missing");
}
}else{
_188.Filter.FileType="all";
_188.Sort.Key="FileDate";
_188.Sort.Order="Ascending";
}
try{
temp_scb=_184;
temp_ecb=_187;
var rval=this.so.IDataSource.GetList(_188,this.getListMediaCb);
if(rval.TransactionID){
glob_obj.addToGlobalArray(rval.TransactionID,_184,_187);
}
if(_188.Sort){
delete _188.Sort;
}
if(_188.Filter.StartRange){
delete _188.Filter.StartRange;
}
if(_188.Filter.EndRange){
delete _188.Filter.EndRange;
}
if(_188.Filter){
delete _188.Filter;
}
if(rval.ErrorCode!=0){
switch(MapErrorCode[rval.ErrorCode]){
case this.error.MISSING_ARG_ERR:
case this.error.INVALID_ARG_ERR:
case this.error.NOT_SUPPORTED_ERR:
if(rval.ErrorMessage){
var _18a=splitErrorMessage(rval.ErrorMessage);
throw new DeviceException(MapErrorCode[rval.ErrorCode],"Media:getList:"+_18a);
}else{
throw new DeviceException(MapErrorCode[rval.ErrorCode],"Media:getList:Operation failed");
}
break;
default:
_187(new DeviceException(MapErrorCode[rval.ErrorCode],"Media: getList: Operation Failed"));
}
}
return rval.TransactionID;
}
catch(e){
__device_handle_exception(e,"__sp_media_getList: "+e);
}
};
function __sp_media_getThumbnail_cb(arg1,arg2,arg3){
var _18e;
var _18f;
var _190;
_190=glob_obj.getFromArray(arg1);
if(_190){
_18f=_190.success_cb;
_18e=_190.error_cb;
}else{
alert("Media : __sp_media_getThumbnail_cb: Callback not found ");
return;
}
if(arg3.ErrorCode!=0&&arg3.ErrorCode!=1010){
_18e(new DeviceException(arg3.ErrorCode,"Media: getThumbnail: Operation Failed"));
return;
}
if(arg2!=event_cancelled){
var _191=null;
if(arg3.ReturnValue){
_191=arg3.ReturnValue.replace(/\\/g,"/");
var _192="file://";
_191=_192+_191;
}
_18f(_191);
}
glob_obj.removeFromArray(arg1);
};
function __sp_media_getThumbnail(_193,_194,_195){
if(!_193){
throw new DeviceException(this.error.MISSING_ARG_ERR,"Media:getThumbnail:Callback is missing");
}else{
if(typeof _193!="function"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Media:getList:Callback is invalid");
}
}
if(_195){
var _196=_195;
if(typeof _195!="function"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Media: getThumbnail: error callback is invalid");
}
}
var _197={};
modifyObjectBaseProp(_197);
if(_194){
if(typeof _194!="object"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Media:getThumbnail:thumbnailInfo is of invalid type object");
}
if(_194.uri){
if(typeof _194.uri!="string"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Media:getThumbnail:uri is not of type string");
}
if(_194.uri.search("file://")==0){
url=_194.uri.slice(FILESCHMLEN);
_197.Url=url.replace(/\//g,"\\");
}else{
throw new DeviceException(this.error.INVALID_ARG_ERR,"Media:getThumbnail:uri is not in file protocol");
}
}else{
throw new DeviceException(this.error.MISSING_ARG_ERR,"Media:getThumbnail:uri is missing");
}
}else{
throw new DeviceException(this.error.MISSING_ARG_ERR,"Media:thumbnailInfo is missing");
}
if(_194.size==null||_194.size==""){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Media:getThumbnail:size is not of type Object");
}
if(_194.size){
if(typeof _194.size!="object"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Media:getThumbnail:size is not of type Object");
}
if((typeof _194.size.width=="undefined")&&(typeof _194.size.height=="undefined")){
throw new DeviceException(this.error.MISSING_ARG_ERR,"Media:thumbnailInfo should have atleast width or height");
}else{
var _198={};
modifyObjectBaseProp(_198);
if(typeof _194.size.width!="undefined"){
_198.width=_194.size.width;
}
if(typeof _194.size.height!="undefined"){
_198.height=_194.size.height;
}
_197.ThumbnailSize=_198;
delete _198;
}
}
try{
temp_scb=_193;
temp_ecb=_195;
var rval=this.so.IDataSource.GetThumbnail(_197,this.getThumbnailCb);
if(rval.TransactionID){
glob_obj.addToGlobalArray(rval.TransactionID,_193,_195);
}
delete _197;
if(rval.ErrorCode!=0){
switch(MapErrorCode[rval.ErrorCode]){
case this.error.MISSING_ARG_ERR:
_195(new DeviceException(this.error.MISSING_ARG_ERR,"Media: getThumbnail: Operation Failed"));
break;
case this.error.NOT_SUPPORTED_ERR:
_195(new DeviceException(MapErrorCode[rval.ErrorCode],"Media:getThumbnail:Operation failed"));
break;
case this.error.INVALID_ARG_ERR:
throw new DeviceException(MapErrorCode[rval.ErrorCode],"Media:getThumbnail:Operation failed");
break;
default:
if(_195){
_195(new DeviceException(MapErrorCode[rval.ErrorCode],"Media:getThumbnail:Operation failed"));
}else{
throw new DeviceException(MapErrorCode[rval.ErrorCode],"Media:getThumbnail:Operation failed");
}
}
}
return rval.TransactionID;
}
catch(e){
__device_handle_exception(e,"__sp_media_getThumbnail: "+e);
}
};
function __sp_media_addStreamUri(uri){
throw new DeviceException(MapErrorCode[rval.ErrorCode],"Media:addStreamUri:Not Supported");
};
function __sp_media_deleteStreamUri(uri){
throw new DeviceException(MapErrorCode[rval.ErrorCode],"Media:deleteStreamUri:Not Supported");
};
function __sp_media_refreshMediaDb(uri){
};
function __sp_media_cancel(_19d){
try{
var rval=this.so.IDataSource.Cancel(_19d);
if(rval.ErrorCode!=0){
switch(rval.ErrorCode){
case this.error.MISSING_ARG_ERR:
case this.error.INVALID_ARG_ERR:
case this.error.NOT_SUPPORTED_ERR:
if(rval.ErrorMessage){
var _19f=splitErrorMessage(rval.ErrorMessage);
throw new DeviceException(MapErrorCode[rval.ErrorCode],"Media:cancel:"+_19f);
}else{
throw new DeviceException(MapErrorCode[rval.ErrorCode],"Media:cancel:Operation failed");
}
break;
default:
throw new DeviceException(MapErrorCode[rval.ErrorCode],"Media:cancel:Operation failed");
}
}
}
catch(e){
__device_handle_exception(e,"__sp_media_refreshMediaDb: "+e);
}
};
function __sp_media_instance(){
this.descriptor=new __sp_media_descriptor();
this.SORT_ASCENDING=0;
this.SORT_DESCENDING=1;
this.getList=__sp_media_getList;
this.getListMediaCb=__sp_media_getList_cb;
this.getThumbnail=__sp_media_getThumbnail;
this.getThumbnailCb=__sp_media_getThumbnail_cb;
this.addStreamUri=__sp_media_addStreamUri;
this.deleteStreamUri=__sp_media_deleteStreamUri;
this.refreshMediaDb=__sp_media_refreshMediaDb;
this.cancel=__sp_media_cancel;
this.error=new DeviceException(0,"Dummy");
try{
this.so=device.getServiceObject("Service.MediaManagement","IDataSource");
}
catch(e){
this.so=null;
__device_handle_exception(e,"media service not available");
}
};
var __device_sensors_service_entry={"name":null,"version":null,"proto":__device_sensors,"descriptor":__device_sensors_descriptor,"providers":[{"descriptor":__sp_sensors_descriptor,"instance":__sp_sensors_instance}]};
function __device_sensors(_1a0){
this.provider=_1a0;
this.interfaceName=_1a0.descriptor.interfaceName;
this.version=_1a0.descriptor.version;
this.getChannels=__device_sensors_getChannels;
this.startChannel=__device_sensors_setNotifier;
this.stopChannel=__device_sensors_cancelNotifier;
this.getScaleFactor=__device_sensors_getScaleFactor;
};
function __device_sensors_descriptor(_1a1){
this.interfaceName=_1a1.interfaceName;
this.version=_1a1.version;
};
function __device_sensors_getChannels(){
return this.provider.getChannels();
};
function __device_sensors_setNotifier(_1a2,_1a3,_1a4){
return this.provider.startChannel(_1a2,_1a3,_1a4);
};
function __device_sensors_cancelNotifier(_1a5){
return this.provider.stopChannel(_1a5);
};
function __device_sensors_getScaleFactor(_1a6){
return this.provider.getScaleFactor(_1a6);
};
function __sp_sensors_descriptor(){
this.interfaceName="sensors";
if(window.__Service_Interface_Ver){
this.version=__Service_Interface_Ver;
}else{
this.version=1;
}
};
function __sp_sensors_instance(){
this.descriptor=new __sp_sensors_descriptor();
this.getChannels=__sp_sensors_getChannels;
this.startChannel=__sp_sensors_setNotifier;
this.stopChannel=__sp_sensors_cancelNotifier;
this.getScaleFactor=__sp_sensors_getScaleFactor;
try{
this.so=device.getServiceObject("Service.Sensor","ISensor");
}
catch(e){
this.so=null;
__device_handle_exception(e,"sensors service not available");
}
};
var __rotation_channel={ucb:null,tids:null};
var __XYZ_channel={ucb:null,tids:null};
var __orientation_channel={ucb:null,tids:null};
function __rotation_cb(arg1,arg2,arg3){
if(arg2!=event_cancelled){
var _1aa=null;
if(arg3.ReturnValue){
var time=arg3.ReturnValue.TimeStamp;
var xrot=arg3.ReturnValue.XRotation;
var yrot=arg3.ReturnValue.YRotation;
var zrot=arg3.ReturnValue.ZRotation;
arg3.ReturnValue.close();
_1aa={};
modifyObjectBaseProp(_1aa);
_1aa.timeStamp=time;
_1aa.rotationAboutXAxis=xrot;
_1aa.rotationAboutYAxis=yrot;
_1aa.rotationAboutZAxis=zrot;
}
__rotation_channel.ucb(_1aa);
}
};
function __XYZ_cb(arg1,arg2,arg3){
if(arg2!=event_cancelled){
var _1b2=null;
if(arg3.ReturnValue){
var time=arg3.ReturnValue.TimeStamp;
var _1b4=arg3.ReturnValue.XAxisData;
var _1b5=arg3.ReturnValue.YAxisData;
var _1b6=arg3.ReturnValue.ZAxisData;
arg3.ReturnValue.close();
_1b2={};
modifyObjectBaseProp(_1b2);
_1b2.timeStamp=time;
_1b2.axisX=_1b4;
_1b2.axisY=_1b5;
_1b2.axisZ=_1b6;
}
__XYZ_channel.ucb(_1b2);
}
};
function __orientation_cb(arg1,arg2,arg3){
if(arg2!=event_cancelled){
var _1ba=null;
if(arg3.ReturnValue){
var time=arg3.ReturnValue.TimeStamp;
var _1bc=arg3.ReturnValue.DeviceOrientation;
arg3.ReturnValue.close();
_1ba={};
modifyObjectBaseProp(_1ba);
_1ba.timeStamp=time;
_1ba.deviceOrientation=_1bc;
}
__orientation_channel.ucb(_1ba);
}
};
function __sp_sensors_getChannels(){
return ["Rotation","AccelerometerAxis","Orientation"];
};
function __sp_sensors_setNotifier(_1bd,_1be,_1bf){
var _1c0=new DeviceException(0,"dummy");
if(!_1bd){
throw new DeviceAPIError(_1c0.MISSING_ARG_ERR,"Callback is missing");
}
if((typeof _1bd)!="function"){
throw new DeviceAPIError(_1c0.INVALID_ARG_ERR,"Callback is of invalid type");
}
if(_1bf&&((typeof _1bf)!="function")){
throw new DeviceAPIError(_1c0.INVALID_ARG_ERR,"InValid error Callback");
}
if(!_1be){
throw new DeviceAPIError(_1c0.MISSING_ARG_ERR,"Channel is missing");
}
if((typeof _1be)!="string"){
throw new DeviceAPIError(_1c0.INVALID_ARG_ERR,"Channel is of invalid type");
}
var rval;
var cb;
var _1c3={};
modifyObjectBaseProp(_1c3);
switch(_1be){
case "Rotation":
_1c3.SearchCriterion="Rotation";
cb=__rotation_cb;
__rotation_channel.ucb=_1bd;
break;
case "AccelerometerAxis":
_1c3.SearchCriterion="AccelerometerAxis";
cb=__XYZ_cb;
__XYZ_channel.ucb=_1bd;
break;
case "Orientation":
_1c3.SearchCriterion="Orientation";
cb=__orientation_cb;
__orientation_channel.ucb=_1bd;
break;
default:
throw new DeviceAPIError(_1c0.NOT_SUPPORTED_ERR,"Unsupported input channel");
}
try{
rval=this.so.ISensor.FindSensorChannel(_1c3);
if(_1c3){
delete _1c3.SearchCriterion;
}
if(rval.ErrorCode!=0){
throw new DeviceAPIError(_1c0.NOT_SUPPORTED_ERR,"StartChannel:Operation Failed");
}
var cmap=[];
var _1c5=[];
var _1c6=rval["ReturnValue"];
var _1c7=_1c6.length;
cmap=_1c6[0];
var _1c8={};
modifyObjectBaseProp(_1c8);
_1c8.ListeningType="ChannelData";
_1c8.ChannelInfoMap=cmap;
var _1c9=this.so.ISensor.RegisterForNotification(_1c8,cb);
if(_1c8){
delete _1c8.ChannelInfoMap;
delete _1c8.ListeningType;
}
if(cmap){
delete cmap.index;
}
_1c5[0]=_1c9["TransactionID"];
if(_1c9.ErrorCode!=0){
if(_1c9.ErrorCode==1005){
_1bf(new DeviceAPIError(_1c0.SERVICE_IN_USE_ERR,"Not Allowed Operation"));
return;
}else{
throw new DeviceAPIError(_1c0.NOT_SUPPORTED_ERR,"StartChannel:Operation Failed");
}
}
}
catch(e2){
__device_handle_exception(e2,"__sp_sensors_setNotifier: RegisterForNotification: "+e2);
}
switch(_1be){
case "Rotation":
__rotation_channel.tid=_1c5;
break;
case "AccelerometerAxis":
__XYZ_channel.tid=_1c5;
break;
case "Orientation":
__orientation_channel.tid=_1c5;
break;
}
return _1c5;
};
function __sp_sensors_cancelNotifier(_1ca){
var _1cb=new DeviceException(0,"dummy");
if(!_1ca){
throw new DeviceAPIError(_1cb.MISSING_ARG_ERR,"Channel is missing");
}
if((typeof _1ca)!="string"){
throw new DeviceAPIError(_1cb.INVALID_ARG_ERR,"Channel is of invalid type");
}
var id;
switch(_1ca){
case "Rotation":
id=__rotation_channel.tid;
__rotation_channel.tid=null;
break;
case "AccelerometerAxis":
id=__XYZ_channel.tid;
__XYZ_channel.tid=null;
break;
case "Orientation":
id=__orientation_channel.tid;
__orientation_channel.tid=null;
break;
default:
throw new DeviceAPIError(_1cb.NOT_SUPPORTED_ERR,"Unsupported input channel");
}
if(!id){
throw new DeviceAPIError(_1cb.DATA_NOT_FOUND_ERR,"Stop Channel:Operation Failed");
}
var _1cd={};
modifyObjectBaseProp(_1cd);
for(var i in id){
_1cd.TransactionID=id[i];
try{
var _1cf=this.so.ISensor.Cancel(_1cd);
if(_1cd){
delete _1cd.TransactionID;
}
if(_1cf.ErrorCode!=0){
throw new DeviceAPIError(_1cb.DATA_NOT_FOUND_ERR,"Stop Channel:Operation Failed");
}
}
catch(e1){
__device_handle_exception(e1,"__sp_sensors_cancelNotifier: "+e1);
}
}
};
function __sp_sensors_getScaleFactor(_1d0){
var _1d1=new DeviceException(0,"dummy");
if(!_1d0){
throw new DeviceAPIError(_1d1.MISSING_ARG_ERR,"Channel is missing");
}
if((typeof _1d0)!="string"){
throw new DeviceAPIError(_1d1.INVALID_ARG_ERR,"Channel is of invalid type");
}
if(_1d0!="AccelerometerAxis"){
throw new DeviceAPIError(_1d1.NOT_SUPPORTED_ERR,"Unsupported input channel");
}
try{
var _1d2={};
_1d2.SearchCriterion="AccelerometerAxis";
var rval=this.so.ISensor.FindSensorChannel(_1d2);
if(_1d2){
delete _1d2.SearchCriterion;
}
if(rval.ErrorCode!=0){
throw new DeviceAPIError(_1d1.NOT_SUPPORTED_ERR,"getScaleFactor:Operation Failed");
}
var cmap=[];
var _1d5=rval["ReturnValue"];
cmap=_1d5[0];
var _1d6={};
modifyObjectBaseProp(_1d6);
_1d6.ListeningType="ChannelData";
_1d6.ChannelInfoMap=cmap;
var _1d7=this.so.ISensor.GetScaleFactor(_1d6);
if(_1d6){
delete _1d6.ChannelInfoMap;
delete _1d6.ListeningType;
}
if(cmap){
delete cmap.index;
}
if(_1d7.ErrorCode!=0){
throw new DeviceAPIError(_1d1.NOT_SUPPORTED_ERR,"getScaleFactor:Operation Failed");
}
}
catch(e1){
__device_handle_exception(e1,"__sp_sensors_getScaleFactor: "+e1);
}
return _1d7["ReturnValue"];
};
var __device_sysinfo_service_entry={"name":null,"version":null,"proto":__device_sysinfo,"descriptor":__device_sysinfo_descriptor,"providers":[{"descriptor":__sp_sysinfo_descriptor,"instance":__sp_sysinfo_instance}]};
function __device_sysinfo(_1d8){
this.provider=_1d8;
this.interfaceName=_1d8.descriptor.interfaceName;
this.version=_1d8.descriptor.version;
this.getChannelList=__device_channels_get;
this.getChannel=__device_sysinfo_get;
this.startChannel=__device_sysinfo_setNotifier;
this.stopChannel=__device_sysinfo_cancelNotifier;
this.cancel=__device_sysinfo_cancel;
};
function __device_sysinfo_descriptor(_1d9){
this.interfaceName=_1d9.interfaceName;
this.version=_1d9.version;
};
function __device_channels_get(){
return this.provider.getChannelList();
};
function __device_sysinfo_get(_1da,_1db,_1dc){
return this.provider.getChannel(_1da,_1db,_1dc);
};
function __device_sysinfo_setNotifier(_1dd,_1de,_1df,_1e0){
return this.provider.startChannel(_1dd,_1de,_1df,_1e0);
};
function __device_sysinfo_cancelNotifier(_1e1){
return this.provider.stopChannel(_1e1);
};
function __device_sysinfo_cancel(id){
return this.provider.cancel(id);
};
function __sp_sysinfo_descriptor(){
this.interfaceName="sysinfo";
if(window.__Service_Interface_Ver){
this.version=__Service_Interface_Ver;
}else{
this.version=1;
}
};
function __sp_sysinfo_instance(){
this.descriptor=new __sp_sysinfo_descriptor();
this.getChannelList=__sp_channel_descriptors_get;
this.getChannel=__sp_sysinfo_get;
this.getChannelCb=__sp_sysinfo_get_cb;
this.startChannel=__sp_sysinfo_setNotifier;
this.stopChannel=__sp_sysinfo_cancelNotifier;
this.cancel=__sp_sysinfo_cancel;
this.error=new DeviceException(0,"Dummy");
try{
this.so=device.getServiceObject("Service.SysInfo","ISysInfo");
}
catch(e){
this.so=null;
__device_handle_exception(e,"Sysinfo service not available");
}
};
function __sp_channel_descriptors_get(){
var _1e3=[{name:"Charging",data:[{name:"chargingStatus",range:"true or false",description:"Charging(true) ,Not charging(false)",}],style:["Sync","Oneshot","Notification"]},{name:"BluetoothOn",data:[{name:"btOn",range:"true or false",description:"BluetoothOn(true) ,BluetoothOff(false)",}],style:["Sync","Oneshot","Notification"]},{name:"PhoneLanguage",data:[{name:"phoneLanguage",range:"",description:"",}],style:["Sync","Oneshot"]},{name:"ProductType",data:[{name:"productType",range:"",description:"",}],style:["Sync","Oneshot"]},{name:"FirmwareVersion",data:[{name:"firmwareVersion",range:"",description:"",}],style:["Sync","Oneshot"]},{name:"BatteryLevel",data:[{name:"batteryLevel ",range:"0-100",description:"Percent battery charge"}],style:["Async","Oneshot","Notification"]},{name:"SignalStrength",data:[{name:"signalStrength",range:"0-100",description:"Signal Strength in Percentage"}],style:["Async","Oneshot","Notification"]},{name:"Network",data:[{name:"networkName ",description:"Network name"},{name:"networkStatus",range:"Available,Current,Forbidden",description:""},{name:"networkMode",range:"ModeGsm,ModeCdma,ModeWcdma",description:""},{name:"mobileCountryCode",range:"",description:""},{name:"mobileNetworkCode",range:"",description:""},{name:"locationStatus",range:"True, False",description:""},{name:"areaCode",range:"",description:""},{name:"cellID",range:"",description:""}],style:["Async","Oneshot","Notification"]},{name:"IMEI",data:[{name:"imei",range:"",description:""}],style:["Sync","Oneshot"]},{name:"OutOfMemory",data:[{name:"oomDrive",range:"",description:""}],style:["NA","NA","Notification"]},{name:"DeviceOrientation",data:[{name:"deviceOrientation",range:"Landscape,Portrait",description:""}],style:["Sync","Oneshot"]},{name:"RoamingFlag",data:[{name:"roamingFlag",range:"",description:""}],style:["Sync","Oneshot"]},{name:"DeviceInputMethod",data:[{name:"deviceInputMethod",range:"Touch,NonTouch,Hybrid",description:""}],style:["Sync","Oneshot"]},{name:"HomeNetwork",data:[{name:"networkName ",description:"Network name"},{name:"networkStatus",range:"Available,Current,Forbidden",description:""},{name:"networkMode",range:"ModeGsm,ModeCdma,ModeWcdma",description:""},{name:"mobileCountryCode",range:"",description:""},{name:"mobileNetworkCode",range:"",description:""},{name:"locationStatus",range:"True, False",description:""},{name:"areaCode",range:"",description:""},{name:"cellID",range:"",description:""}],style:["Async","Oneshot","Notification"]}];
return _1e3;
};
var max=110;
var min=40;
var diff=max-min;
function __sp_device_sysinfo_toDecibel(_1e4){
var _1e5=_1e4/100;
var _1e6=max-(_1e5*diff);
_1e6=Math.round(_1e6);
return _1e6;
};
function __sp_device_sysinfo_toPercentage(_1e7){
if(_1e7==0){
return _1e7;
}else{
var _1e8=max-_1e7;
var _1e9=_1e8/diff;
_1e9*=100;
_1e9=Math.round(_1e9);
return _1e9;
}
};
function __sp_device_sysinfo_toBool(_1ea){
if(_1ea==0){
return false;
}else{
return true;
}
};
function mappingVerification(_1eb){
if(_1eb==1016||_1eb==1012||_1eb==1010||_1eb==1009||_1eb==1005||_1eb==1000||_1eb==1011||_1eb==1007||_1eb==1003||_1eb==1002){
return true;
}else{
return false;
}
};
function __sp_device_sysinfo_extract(_1ec){
var _1ed=_1ec.Key;
var _1ee={};
modifyObjectBaseProp(_1ee);
try{
switch(_1ed){
case "ChargingStatus":
_1ee.chargingStatus=__sp_device_sysinfo_toBool(_1ec.Status);
break;
case "BatteryStrength":
_1ee.batteryLevel=_1ec.Status;
break;
case "SignalStrength":
_1ee.signalStrength=__sp_device_sysinfo_toPercentage(_1ec.Status);
break;
case "CurrentNetwork":
var _1ef;
var mode;
switch(_1ec.NetworkStatus){
case 0:
_1ef="Available";
break;
case 1:
_1ef="Current";
break;
case 2:
_1ef="Forbidden";
break;
default:
_1ef="Unknown";
break;
}
switch(_1ec.NetworkMode){
case 1:
mode="ModeGsm";
break;
case 3:
case 4:
mode="ModeCdma";
break;
case 5:
mode="ModeWcdma";
break;
default:
mode="Unknown";
break;
}
_1ee.networkName=_1ec.NetworkName;
_1ee.networkStatus=_1ef;
_1ee.networkMode=mode;
_1ee.mobileCountryCode=_1ec.CountryCode;
_1ee.mobileNetworkCode=_1ec.NetworkCode;
_1ee.locationStatus=_1ec.LocationStatus;
_1ee.areaCode=_1ec.AreaCode;
_1ee.cellID=_1ec.CellId;
break;
case "DisplayLanguage":
_1ee.phoneLanguage=_1ec.StringData;
break;
case "BlueTooth":
_1ee.btOn=__sp_device_sysinfo_toBool(_1ec.Status);
break;
case "ProductType":
_1ee.productType=_1ec.StringData;
break;
case "FirmwareVersion":
_1ee.firmwareVersion=_1ec.StringData;
break;
case "DeviceInputMethod":
_1ee.deviceInputMethod=_1ec.StringData;
break;
default:
_1ee=_1ec;
break;
}
return _1ee;
}
catch(e){
__device_handle_exception(e,"__sp_device_sysinfo_extract: "+e);
}
};
function __sp_sysinfo_get_cb(arg1,arg2,arg3){
var _1f4;
var _1f5;
var _1f6;
_1f6=glob_obj.getFromArray(arg1);
if(_1f6){
_1f4=_1f6.success_cb;
_1f5=_1f6.error_cb;
}else{
alert("Sysinfo: __sp_sysinfo_get_cb: Callback not found ");
return;
}
var op=null;
if(arg3.ErrorCode!=0){
var _1f8=splitErrorMessage(arg3.ErrorMessage);
_1f5(new DeviceException(MapErrorCode[arg3.ErrorCode],"SysInfo:getChannel: "+_1f8));
}else{
if(arg3.ReturnValue){
op=__sp_device_sysinfo_extract(arg3.ReturnValue);
arg3.ReturnValue.close();
_1f4(op);
}
}
glob_obj.removeFromArray(arg1);
};
function __sp_sysinfo_get(_1f9,_1fa,_1fb){
var so;
var rval;
var _1fe=false;
var _1ff="Status";
var _200;
var _201={};
modifyObjectBaseProp(_201);
try{
switch(_1f9){
case "Charging":
_201.Entity="Battery";
_201.Key="ChargingStatus";
break;
case "BatteryLevel":
_201.Entity="Battery";
_201.Key="BatteryStrength";
_1fe=true;
break;
case "SignalStrength":
_201.Entity="Network";
_201.Key="SignalStrength";
_1fe=true;
break;
case "Network":
_201.Entity="Network";
_201.Key="CurrentNetwork";
_1fe=true;
break;
case "PhoneLanguage":
_201.Entity="General";
_201.Key="DisplayLanguage";
break;
case "BluetoothOn":
_201.Entity="Connectivity";
_201.Key="BlueTooth";
break;
case "ProductType":
_201.Entity="Device";
_201.Key="ProductType";
break;
case "FirmwareVersion":
_201.Entity="Device";
_201.Key="FirmwareVersion";
break;
case "DeviceInputMethod":
_201.Entity="Device";
_201.Key="DeviceInputMethod";
break;
default:
if(_1f9==null){
throw new DeviceException(this.error.MISSING_ARG_ERR,"SysInfo:getChannel:channel is missing");
}else{
if(typeof _1f9!="string"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"SysInfo:getChannel:channel is of invalid type");
}else{
throw new DeviceException(this.error.INVALID_ARG_ERR,"SysInfo:getChannel:channel is invalid");
}
}
}
if(_1fe){
if(_1fa==null){
throw new DeviceException(this.error.MISSING_ARG_ERR,"SysInfo:getChannel:callback is missing");
}
if(typeof _1fa!="function"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"SysInfo:getChannel:callback is invalid");
}
if(_1fb){
if(typeof (_1fb)!="function"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"SysInfo:getChannel: ErrorCallback is invalid");
}
}
temp_scb=_1fa;
temp_ecb=_1fb;
rval=this.so.ISysInfo.GetInfo(_201,this.getChannelCb);
if(rval.TransactionID){
glob_obj.addToGlobalArray(rval.TransactionID,_1fa,_1fb);
}
if(rval.ErrorCode!=0){
var _202=mappingVerification(rval.ErrorCode);
if(_202){
switch(MapErrorCode[rval.ErrorCode]){
case this.error.MISSING_ARG_ERR:
case this.error.INVALID_ARG_ERR:
if(rval.ErrorMessage){
var _203=splitErrorMessage(rval.ErrorMessage);
throw new DeviceException(MapErrorCode[rval.ErrorCode],"SysInfo: getChannel: "+_203);
}else{
throw new DeviceException(MapErrorCode[rval.ErrorCode],"SysInfo:getChannel:Operation Failed");
}
break;
default:
_1fa(0);
}
}else{
_1fa(0);
}
}
return rval.TransactionID;
}else{
rval=this.so.ISysInfo.GetInfo(_201);
if(rval.ErrorCode!=0){
if(rval.ErrorMessage){
var _204=splitErrorMessage(rval.ErrorMessage);
throw new DeviceException(MapErrorCode[rval.ErrorCode],"SysInfo: getChannel: "+_204);
}else{
throw new DeviceException(MapErrorCode[rval.ErrorCode],"SysInfo:getChannel:Operation Failed");
}
}
_200=__sp_device_sysinfo_extract(rval.ReturnValue);
return _200;
}
delete _201;
}
catch(e){
__device_handle_exception(e,"__sp_sysinfo_get: getChannel: "+e);
}
};
var __cell_id_channel={scb:null,ecb:null,cancel_id:null};
function __cell_id_channel_cb(arg1,arg2,arg3){
var op=null;
if(arg3.ErrorCode){
__cell_id_channel.ecb(arg3.ErrorCode);
}else{
if(arg3.ReturnValue){
op=arg3.ReturnValue;
arg3.ReturnValue.close();
__cell_id_channel.scb(op);
}
}
};
var __charging_status_channel={scb:null,ecb:null,cancel_id:null};
function __charging_status_channel_cb(arg1,arg2,arg3){
var op=null;
if(arg3.ErrorCode){
__charging_status_channel.ecb(arg3.ErrorCode);
}else{
if(arg3.ReturnValue){
op=__sp_device_sysinfo_extract(arg3.ReturnValue);
arg3.ReturnValue.close();
__charging_status_channel.scb(op);
}
}
};
var __net_coverage_channel={scb:null,ecb:null,cancel_id:null};
function __net_coverage_channel_cb(arg1,arg2,arg3){
var op=null;
if(arg3.ErrorCode){
__net_coverage_channel.ecb(arg3.ErrorCode);
}else{
if(arg3.ReturnValue){
op=__sp_device_sysinfo_extract(arg3.ReturnValue);
arg3.ReturnValue.close();
__net_coverage_channel.scb(op);
}
}
};
var __battery_level_channel={scb:null,ecb:null,cancel_id:null};
function __battery_level_channel_cb(arg1,arg2,arg3){
var op=null;
if(arg3.ErrorCode){
__battery_level_channel.ecb(arg3.ErrorCode);
}else{
if(arg3.ReturnValue){
op=__sp_device_sysinfo_extract(arg3.ReturnValue);
arg3.ReturnValue.close();
__battery_level_channel.scb(op);
}
}
};
var __bluetooth_on_channel={scb:null,ecb:null,cancel_id:null};
function __bluetooth_on_channel_cb(arg1,arg2,arg3){
var op=null;
if(arg3.ErrorCode){
__bluetooth_on_channel.ecb(arg3.ErrorCode);
}else{
if(arg3.ReturnValue){
op=__sp_device_sysinfo_extract(arg3.ReturnValue);
arg3.ReturnValue.close();
__bluetooth_on_channel.scb(op);
}
}
};
var __signal_channel={scb:null,ecb:null,cancel_id:null};
function __signal_channel_cb(arg1,arg2,arg3){
var op=null;
if(arg3.ErrorCode){
__signal_channel.ecb(arg3.ErrorCode);
}else{
if(arg3.ReturnValue){
op=__sp_device_sysinfo_extract(arg3.ReturnValue);
arg3.ReturnValue.close();
__signal_channel.scb(op);
}
}
};
function __sp_sysinfo_setNotifier(_21d,_21e,_21f,_220){
var rval;
var _222=null;
var cb=null;
var _224={};
if(_21d==null){
throw new DeviceException(this.error.MISSING_ARG_ERR,"SysInfo:startChannel:callback is missing");
}
if(typeof _21d!="function"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"SysInfo:startChannel:callback is invalid");
}
modifyObjectBaseProp(_224);
try{
switch(_21e){
case "Charging":
_224.Entity="Battery";
_224.Key="ChargingStatus";
_222=__charging_status_channel;
cb=__charging_status_channel_cb;
break;
case "Network":
_224.Entity="Network";
_224.Key="CurrentNetwork";
_222=__net_coverage_channel;
cb=__net_coverage_channel_cb;
break;
case "BatteryLevel":
_224.Entity="Battery";
_224.Key="BatteryStrength";
_224.SystemData={};
modifyObjectBaseProp(_224.SystemData);
if(_21f==null){
_21f=50;
}
if(!(_21f>=0&&_21f<=100)){
throw new DeviceException(this.error.DATA_OUT_OF_RANGE_ERR,"SysInfo:startChannel:trigger is out of range");
}
if(typeof _21f!="number"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"SysInfo:startChannel:trigger is of  invalid type");
}
_224.SystemData.Status=_21f;
_222=__battery_level_channel;
cb=__battery_level_channel_cb;
break;
case "SignalStrength":
_224.Entity="Network";
_224.Key="SignalStrength";
_224.SystemData={};
modifyObjectBaseProp(_224.SystemData);
if(_21f!=null){
if(!(_21f>=0&&_21f<=100)){
throw new DeviceException(this.error.DATA_OUT_OF_RANGE_ERR,"SysInfo:startChannel:trigger is out of range");
}
if(typeof _21f!="number"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"SysInfo:startChannel:trigger is of invalid type");
}
_224.SystemData.Status=__sp_device_sysinfo_toDecibel(_21f);
}
_222=__signal_channel;
cb=__signal_channel_cb;
break;
case "BluetoothOn":
_224.Entity="Connectivity";
_224.Key="BlueTooth";
_222=__bluetooth_on_channel;
cb=__bluetooth_on_channel_cb;
break;
default:
var _225;
if(_21e==null){
throw new DeviceException(this.error.MISSING_ARG_ERR,"SysInfo:startChannel:channel is missing");
}else{
if(typeof _21e!="string"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"SysInfo:startChannel:channel is of invalid type");
}else{
throw new DeviceException(this.error.INVALID_ARG_ERR,"SysInfo:startChannel:channel is invalid");
}
}
if(_224.SystemData){
delete _224.SystemData;
}
}
_222.scb=_21d;
_222.ecb=_220;
if(_222.ecb){
if(typeof (_222.ecb)!="function"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"SysInfo:startChannel: ErrorCallback is invalid");
}
}
if(_222.cancel_id){
var _226={};
modifyObjectBaseProp(_226);
_226.TransactionID=_222.cancel_id;
this.so.ISysInfo.Cancel(_226);
_222.cancel_id=null;
delete _226;
}
temp_scb=_21d;
temp_ecb=_220;
rval=this.so.ISysInfo.GetNotification(_224,cb);
delete _224;
if(rval.ErrorCode!=0){
switch(MapErrorCode[rval.ErrorCode]){
case this.error.MISSING_ARG_ERR:
case this.error.INVALID_ARG_ERR:
if(rval.ErrorMessage){
var _227=splitErrorMessage(rval.ErrorMessage);
throw new DeviceException(MapErrorCode[rval.ErrorCode],"SysInfo: startChannel: "+_227);
}else{
throw new DeviceException(MapErrorCode[rval.ErrorCode],"SysInfo:startChannel:Operation Failed");
}
break;
default:
_21d(0);
}
}
_222.cancel_id=rval.TransactionID;
return _222.cancel_id;
}
catch(e){
__device_handle_exception(e,"__sp_sysinfo_startChannel: "+e);
}
};
function __sp_sysinfo_cancelNotifier(_228){
try{
switch(_228){
case "CellId":
channel=__cell_id_channel;
break;
case "Charging":
channel=__charging_status_channel;
break;
case "Network":
channel=__net_coverage_channel;
break;
case "BatteryLevel":
channel=__battery_level_channel;
break;
case "SignalStrength":
channel=__signal_channel;
break;
case "BluetoothOn":
channel=__bluetooth_on_channel;
break;
default:
var _229;
if(_228==null){
throw new DeviceException(this.error.MISSING_ARG_ERR,"SysInfo:stopChannel:channel is missing");
}else{
if(typeof _228!="string"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"SysInfo:stopChannel:channel is of invalid type");
}else{
throw new DeviceException(this.error.INVALID_ARG_ERR,"SysInfo:stopChannel:channel is invalid");
}
}
}
if(channel.cancel_id){
var _22a={};
modifyObjectBaseProp(_22a);
_22a.TransactionID=channel.cancel_id;
var _22b=this.so.ISysInfo.Cancel(_22a);
delete _22a;
if(_22b.ErrorCode!=0){
if(_22b.ErrorMessage){
var _22c=splitErrorMessage(_22b.ErrorMessage);
throw new DeviceException(MapErrorCode[_22b.ErrorCode],"SysInfo: stopChannel: "+_22c);
}else{
throw new DeviceException(MapErrorCode[_22b.ErrorCode],"SysInfo:stopChannel:Operation Failed");
}
}
channel.cancel_id=null;
}else{
throw new DeviceException(this.error.DATA_NOT_FOUND_ERR,"SysInfo:stopChannel:channel not started");
}
}
catch(e){
__device_handle_exception(e,"__sp_sysinfo_stopChannel: "+e);
}
};
function __sp_sysinfo_cancel(_22d){
try{
var _22e=0;
if(_22d==null){
throw new DeviceException(this.error.MISSING_ARG_ERR,"SysInfo:cancel:Id is missing");
}
if(typeof _22d!="number"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"SysInfo:cancel:Id is of invalid type");
}
if(_22d==__charging_status_channel.cancel_id||_22d==__net_coverage_channel.cancel_id||_22d==__battery_level_channel.cancel_id||_22d==__bluetooth_on_channel.cancel_id||_22d==__signal_channel.cancel_id){
_22e=1;
}
if(_22e!=1){
var _22f={TransactionID:_22d};
var _230=this.so.ISysInfo.Cancel(_22f);
if(_230.ErrorCode!=0){
if(_230.ErrorMessage){
var _231=splitErrorMessage(_230.ErrorMessage);
throw new DeviceException(this.error.INVALID_ARG_ERR,"SysInfo:cancel: "+_231);
}else{
throw new DeviceException(MapErrorCode[_230.ErrorCode],"SysInfo:cancel:Operation Failed");
}
}
}else{
_22e=0;
throw new DeviceException(this.error.NOT_ALLOWED_ERR,"SysInfo:cancel:Cannot Cancel a channel started using startChannel ");
}
}
catch(e){
__device_handle_exception(e,"__sp_sysinfo_cancel: "+e);
}
};
function __device_camera_descriptor(_232){
this.interfaceName=_232.interfaceName;
this.version=_232.version;
};
function __device_camera_startCamera(_233,_234){
return this.provider.startCamera(_233,_234);
};
function __device_camera_stopViewfinder(){
this.provider.stopViewfinder();
};
function __device_camera_takePicture(_235){
this.provider.takePicture(_235);
};
function __device_camera(_236){
this.provider=_236;
this.interfaceName=_236.descriptor.interfaceName;
this.version=_236.descriptor.version;
this.supportedMediaTypes=_236.supportedMediaTypes;
this.supportedSizes=_236.supportedSizes;
this.startCamera=__device_camera_startCamera;
this.stopViewfinder=__device_camera_stopViewfinder;
this.takePicture=__device_camera_takePicture;
};
var __device_camera_service_entry={"name":null,"version":null,"proto":__device_camera,"descriptor":__device_camera_descriptor,"providers":[{"descriptor":__sp_camera_descriptor,"instance":__sp_camera_instance}]};
function __sp_camera_descriptor(){
this.interfaceName="camera";
if(window.__Service_Interface_Ver){
this.version=__Service_Interface_Ver;
}else{
this.version=1;
}
};
var __sp_camera_start_date;
var CAMERA_APP_ID=270501242;
function __sp_startCamera(_237,_238){
if(_237==null){
throw new DeviceException(this.error.MISSING_ARG_ERR,"Camera:startCamera:callback is missing");
}
if(_237==undefined){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Camera:startCamera:callback is a non-function");
}
if(typeof (_237)!="function"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Camera:startCamera:callback is a non-function");
}
if(_238){
if(typeof _238!="function"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Camera:startCamera:callback is invalid");
}
}
var _239=function(){
var _23a=function(arg1,arg2,arg3){
var it=arg3.ReturnValue;
var item;
var _240=[];
if(arg3.ErrorCode!=0){
_238(new DeviceException(arg3.ErrorCode,"Camera:startCamera: Operation Failed"));
return;
}
if((item=it.getNext())!=undefined){
var d=new Date(Date.parse(item.FileDate));
if(d>__sp_camera_start_date){
var _242={};
modifyObjectBaseProp(_242);
var _243=item.FileNameAndPath.replace(/\\/g,"/");
var _244="file:///";
var _245="";
_245=_245.concat(_244,_243);
_242.uri=_245;
var _246={};
_246.height=item.XPixels;
_246.width=item.YPixels;
_246.type=item.MimeType;
_242.format=_246;
_240.unshift(_242);
if(_246){
}
}
}
var _247=0;
var _248=0;
_237(_240);
};
try{
var mso=device.getServiceObject("Service.MediaManagement","IDataSource");
}
catch(e){
__device_handle_exception(e,"media service not available : "+e);
}
var _24a={};
modifyObjectBaseProp(_24a);
_24a.Type="FileInfo";
_24a.Filter={};
modifyObjectBaseProp(_24a.Filter);
_24a.Filter.FileType="Image";
_24a.Sort={};
modifyObjectBaseProp(_24a.Sort);
_24a.Sort.Key="FileDate";
_24a.Sort.Order="Descending";
try{
var rval=mso.IDataSource.GetList(_24a,_23a);
}
catch(error){
__device_handle_exception(error,"media service GetList failed: "+error);
}
};
__sp_camera_start_date=new Date();
__s60_start_and_wait(CAMERA_APP_ID,"",_239);
var _24c=0;
return _24c;
};
function __sp_supportedSizes(){
try{
var _24d=device.getServiceObject("Service.SysInfo","ISysInfo");
}
catch(e){
__device_handle_exception(e,"SysInfo Service not available : "+e);
}
var _24e={};
modifyObjectBaseProp(_24e);
_24e.Entity="Camera";
_24e.Key="CameraProperties";
try{
var rval=_24d.ISysInfo.GetInfo(_24e);
if(_24e){
delete _24e.Entity;
delete _24e.Key;
}
}
catch(error){
__device_handle_exception(error,"Camera : Failed to fetch supported size Info: "+error);
}
var _250=rval.ReturnValue;
var _251=[];
var _252=[];
_251=_250.ResolutionList;
for(var i=0;i<_251.length;i++){
var _254="";
_254=_254.concat(_251[i].height,"X",_251[i].width);
_252.push(_254);
}
return _252;
};
function __sp_supportedMediaTypes(){
try{
var _255=device.getServiceObject("Service.SysInfo","ISysInfo");
}
catch(e){
__device_handle_exception(e,"SysInfo Service not available : "+e);
}
var _256={};
modifyObjectBaseProp(_256);
_256.Entity="Camera";
_256.Key="CameraProperties";
try{
var rval=_255.ISysInfo.GetInfo(_256);
if(_256){
delete _256.Entity;
delete _256.Key;
}
}
catch(error){
__device_handle_exception(error,"Camera :Failed to fetch supported media type Info: "+error);
}
var _258=rval.ReturnValue;
var _259=[];
_259=_258.MimeTypeList;
return _259;
};
function __sp_camera_instance(){
this.descriptor=new __sp_camera_descriptor();
this.supportedMediaTypes=__sp_supportedMediaTypes();
this.supportedSizes=__sp_supportedSizes();
this.startCamera=__sp_startCamera;
this.stopViewfinder=__s60_api_not_supported;
this.takePicture=__s60_api_not_supported;
this.error=new DeviceException(0,"Dummy");
};
var _infinity=Infinity;
function TransIdCbMap(){
this.TransactionID=null;
this.success_callback=null;
this.error_callback=null;
};
function __device_geolocation_descriptor(_25a){
this.interfaceName=_25a.interfaceName;
this.version=_25a.version;
};
function __device_geolocation_getCurrentPosition(_25b,_25c,_25d){
return this.provider.getLocation(_25b,_25c,_25d);
};
function __device_geolocation_watchPosition(_25e,_25f,_260){
return this.provider.traceLocation(_25e,_25f,_260);
};
function __device_geolocation_clearWatch(_261){
this.provider.clearTrace(_261);
};
function __device_geolocation(_262){
this.provider=_262;
this.interfaceName=_262.descriptor.interfaceName;
this.version=_262.descriptor.version;
this.getCurrentPosition=__device_geolocation_getCurrentPosition;
this.watchPosition=__device_geolocation_watchPosition;
this.clearWatch=__device_geolocation_clearWatch;
};
var __device_geolocation_service_entry={"name":null,"version":null,"proto":__device_geolocation,"descriptor":__device_geolocation_descriptor,"providers":[{"descriptor":__sp_location_descriptor,"instance":__sp_location_instance}]};
function Location_PositionError(){
this.UNKNOWN_ERROR=0;
this.PERMISSION_DENIED=1;
this.POSITION_UNAVAILABLE=2;
this.TIMEOUT=3;
this.code;
this.message;
};
function Location_Coordinates(){
this.latitude=null;
this.longitude=null;
this.altitude=null;
this.accuracy=null;
this.altitudeAccuracy=null;
this.heading=null;
this.speed=null;
};
function Location_Position(){
this.coords=null;
this.timestamp=null;
};
function Location_PositionOptions(){
this.enableHighAccuracy;
this.timeout;
this.maximumAge;
};
var __sp_location_trace_transactionId=-1;
function __sp_location_handle_error(_263,_264,_265){
if((_263!=undefined)&&(typeof _263=="function")&&(_263!=null)){
var _266=new Location_PositionError();
if((-21)==_264){
_266.code=_266.PERMISSION_DENIED;
_266.message="permission denied";
}else{
if((-33)==_264){
_266.code=_266.TIMEOUT;
_266.message="request timed out";
}else{
_266.code=_266.UNKNOWN_ERROR;
_266.message="UnKnown Error";
}
}
_263(_266);
}else{
var _266=new Location_PositionError();
_266.code=_266.UNKNOWN_ERROR;
_266.message="UnKnown Error";
throw _266;
}
};
function __sp_location_descriptor(){
this.interfaceName="geolocation";
if(window.__Service_Interface_Ver){
this.version=__Service_Interface_Ver;
}else{
this.version=1;
}
};
var obj;
function __sp_getLocation_cb(arg1,arg2,arg3){
var _26a;
_26a=glob_obj.getFromArray(arg1);
if(_26a){
success_cb1=_26a.success_cb;
error_cb=_26a.error_cb;
}else{
alert("Geolocation: __sp_getLocation_cb: Callback not found ");
return;
}
if(arg3.ErrorCode){
__sp_location_handle_error(error_cb,arg3.ErrorCode,arg3.ErrorMessage);
return;
}else{
var _26b=new Location_Coordinates();
_26b.longitude=(arg3.ReturnValue.Longitude==undefined)?null:arg3.ReturnValue.Longitude;
_26b.latitude=(arg3.ReturnValue.Latitude==undefined)?null:arg3.ReturnValue.Latitude;
_26b.altitude=(arg3.ReturnValue.Altitude==undefined)?null:arg3.ReturnValue.Altitude;
_26b.accuracy=(arg3.ReturnValue.HorizontalAccuracy==undefined)?null:arg3.ReturnValue.HorizontalAccuracy;
_26b.altitudeAccuracy=(arg3.ReturnValue.VerticalAccuracy==undefined)?null:arg3.ReturnValue.VerticalAccuracy;
_26b.heading=(arg3.ReturnValue.Heading==undefined)?null:arg3.ReturnValue.Heading;
_26b.speed=(arg3.ReturnValue.HorizontalSpeed==undefined)?null:arg3.ReturnValue.HorizontalSpeed;
var _26c=new Location_Position();
_26c.coords={};
modifyObjectBaseProp(_26c.coords);
_26c.coords=_26b;
_26c.timestamp=new Date();
success_cb1(_26c);
delete _26c.timestamp;
delete _26c;
delete _26b;
}
glob_obj.removeFromArray(arg1);
};
function __sp_getLocation(_26d,_26e,_26f){
if((_26d==undefined)||(_26d==null)||(typeof (_26d)!="function")){
var _270="Wrong callback type";
__sp_location_handle_error(_26e,0,_270);
}
if((_26e!=undefined)){
if((_26e!=null)&&(_26e!="")&&(typeof (_26e)!="function")){
var _271=new Location_PositionError();
_271.code=-1;
throw _271;
}
}
var _272;
var _273={};
modifyObjectBaseProp(_273);
_273.LocationInformationClass="GenericLocationInfo";
var _274={};
modifyObjectBaseProp(_274);
_274.UpdateInterval=0;
if(_26f!=undefined&&_26f!=null){
if((typeof (_26f)!="object")){
var _275="Wrong posOptions type";
__sp_location_handle_error(_26e,0,_275);
return;
}
}
if(_26f!=undefined){
if(_26f.maximumAge!=undefined){
if(_26f.maximumAge){
if((_26f.maximumAge==Infinity)){
if((_26f.enableHighAccuracy==undefined)||(typeof (_26f.enableHighAccuracy)=="boolean")){
var arg3=this.so.ILocation.GetLastPosition();
if(arg3.ErrorCode<0){
var _275="Invalid input type";
__sp_location_handle_error(_26e,0,_275);
return;
}
var _277=new Location_Coordinates();
_277.longitude=(arg3.ReturnValue.Longitude==undefined)?null:arg3.ReturnValue.Longitude;
_277.latitude=(arg3.ReturnValue.Latitude==undefined)?null:arg3.ReturnValue.Latitude;
_277.altitude=(arg3.ReturnValue.Altitude==undefined)?null:arg3.ReturnValue.Altitude;
_277.accuracy=(arg3.ReturnValue.HorizontalAccuracy==undefined)?null:arg3.ReturnValue.HorizontalAccuracy;
_277.altitudeAccuracy=(arg3.ReturnValue.VerticalAccuracy==undefined)?null:arg3.ReturnValue.VerticalAccuracy;
_277.heading=(arg3.ReturnValue.Heading==undefined)?null:arg3.ReturnValue.Heading;
_277.speed=(arg3.ReturnValue.HorizontalSpeed==undefined)?null:arg3.ReturnValue.HorizontalSpeed;
var _278=new Location_Position();
_278.coords={};
modifyObjectBaseProp(_278.coords);
_278.coords=_277;
_278.timestamp=new Date();
_26d(_278);
delete _278.timestamp;
delete _278;
delete _277;
return;
}
}
if(!(isNaN(parseInt(_26f.maximumAge)))){
if((_26f.maximumAge==0)){
var _275="Invalid input type";
__sp_location_handle_error(_26e,0,_275);
return;
}
_274.UpdateMaxAge=_26f.maximumAge;
}else{
var _275="Invalid input type";
__sp_location_handle_error(_26e,0,_275);
return;
}
}else{
if((_26f.maximumAge==null)||(_26f.maximumAge=="")){
}
}
}
if((_26f.enableHighAccuracy!==undefined)){
if(_26f.enableHighAccuracy==true){
_273.EnableHighAccuracy=_26f.enableHighAccuracy;
}else{
if(_26f.enableHighAccuracy==false){
_273.EnableHighAccuracy=_26f.enableHighAccuracy;
}else{
if((_26f.enableHighAccuracy==null)||(_26f.enableHighAccuracy=="")){
}else{
if((typeof (_26f.enableHighAccuracy)!="boolean")){
var _279="Wrong value for enableHighAccuracy param";
__sp_location_handle_error(_26e,0,_279);
return;
}
}
}
}
}
if(_26f.timeout!==undefined){
if((_26f.timeout!==null)||((_26f.timeout!==""))){
if((_26f.timeout==Infinity)){
var _275="Invalid input type";
__sp_location_handle_error(_26e,0,_275);
return;
}else{
if(!(isNaN(parseInt(_26f.timeout)))){
if((_26f.timeout<=2147483647)){
if((_26f.timeout==0)){
var _275="Invalid input type";
__sp_location_handle_error(_26e,0,_275);
return;
}
_274.UpdateTimeOut=_26f.timeout;
}else{
var _275="Invalid input type";
__sp_location_handle_error(_26e,0,_275);
return;
}
}
}
}else{
if((_26f.timeout===null)||((_26f.timeout===""))){
}else{
var _275="Invalid input type";
__sp_location_handle_error(_26e,0,_275);
return;
}
}
}
}
_274.PartialUpdates=false;
_273.Updateoptions=_274;
try{
temp_scb=_26d;
temp_ecb=_26e;
var rval=this.so.ILocation.GetLocation(_273,this.getLocationCb);
if(rval.TransactionID){
glob_obj.addToGlobalArray(rval.TransactionID,_26d,_26e);
}
delete _274;
delete _273;
if(rval.ErrorCode!=0){
__sp_location_handle_error(_26e,rval.ErrorCode,rval.ErrorMessage);
return;
}
}
catch(e){
__device_handle_exception(e,"__sp_getLocation: "+e);
}
};
var __sp_location_trace_ucb=null;
var __sp_location_fail_cb=null;
function __sp_traceLocation_cb(arg1,arg2,arg3){
var _27e;
_27e=glob_obj.getFromArray(arg1);
if(_27e){
success_cb=_27e.success_cb;
error_cb=_27e.error_cb;
}else{
alert("Geolocation: __sp_traceLocation_cb: Callback not found ");
return;
}
if(arg3.ErrorCode){
__sp_location_handle_error(error_cb,arg3.ErrorCode,arg3.ErrorMessage);
}else{
var _27f=new Location_Coordinates();
_27f.longitude=(arg3.ReturnValue.Longitude==undefined)?null:arg3.ReturnValue.Longitude;
_27f.latitude=(arg3.ReturnValue.Latitude==undefined)?null:arg3.ReturnValue.Latitude;
_27f.altitude=(arg3.ReturnValue.Altitude==undefined)?null:arg3.ReturnValue.Altitude;
_27f.accuracy=(arg3.ReturnValue.HorizontalAccuracy==undefined)?null:arg3.ReturnValue.HorizontalAccuracy;
_27f.altitudeAccuracy=(arg3.ReturnValue.VerticalAccuracy==undefined)?null:arg3.ReturnValue.VerticalAccuracy;
_27f.heading=(arg3.ReturnValue.Heading==undefined)?null:arg3.ReturnValue.Heading;
_27f.speed=(arg3.ReturnValue.HorizontalSpeed==undefined)?null:arg3.ReturnValue.HorizontalSpeed;
var _280=new Location_Position();
_280.coords={};
modifyObjectBaseProp(_280.coords);
_280.coords=_27f;
_280.timestamp=new Date();
success_cb(_280);
delete _280.timestamp;
delete _280;
delete _27f;
return;
}
glob_obj.removeFromArray(arg1);
};
function __sp_traceLocation(_281,_282,_283){
if((_281==undefined)||(_281==null)||(typeof (_281)!="function")){
var _284="Wrong callback type";
__sp_location_handle_error(_282,0,_284);
return;
}
if((typeof _281!="function")){
var _284="Wrong callback type";
__sp_location_handle_error(_282,0,_284);
return;
}
if((_282!=undefined)){
if((_282!=null)&&(_282!="")&&(typeof (_282)!="function")){
var _285=new Location_PositionError();
_285.code=-1;
throw _285;
}
}
var _286=this;
var _287={};
modifyObjectBaseProp(_287);
_287.UpdateInterval=0;
var _288={};
modifyObjectBaseProp(_288);
_288.LocationInformationClass="GenericLocationInfo";
if(_283!=undefined&&_283!=null){
if((typeof (_283)!="object")){
var _284="Wrong posOptions type";
__sp_location_handle_error(_282,0,_284);
return;
}
}
if(_283!=undefined){
if((_283.enableHighAccuracy!==undefined)){
if(_283.enableHighAccuracy==true){
_288.EnableHighAccuracy=_283.enableHighAccuracy;
}else{
if(_283.enableHighAccuracy==false){
_288.EnableHighAccuracy=_283.enableHighAccuracy;
}else{
if((_283.enableHighAccuracy==null)||(_283.enableHighAccuracy=="")){
}else{
if((typeof (_283.enableHighAccuracy)!="boolean")){
var _289="Wrong value for enableHighAccuracy param";
__sp_location_handle_error(_282,0,_289);
return;
}
}
}
}
}
if(_283.timeout!==undefined){
if((_283.timeout!==null)||((_283.timeout!==""))){
if((_283.timeout==Infinity)){
var _284="Invalid input type";
__sp_location_handle_error(_282,0,_284);
return;
}else{
if(!(isNaN(parseInt(_283.timeout)))){
if((_283.timeout==0)){
var _284="Invalid input type";
__sp_location_handle_error(_282,0,_284);
return;
}
_287.UpdateTimeOut=_283.timeout;
}
}
}else{
if((_283.timeout===null)||((_283.timeout===""))){
}else{
var _284="Invalid input type";
__sp_location_handle_error(_282,0,_284);
return;
}
}
}
if(typeof _283.maximumAge!="undefined"){
if(_283.maximumAge==_infinity){
_287.UpdateTimeOut=0;
_287.UpdateMaxAge=2147483647;
}else{
if(!(isNaN(parseInt(_283.maximumAge)))){
_287.UpdateMaxAge=_283.maximumAge;
}else{
if((_283.maximumAge===null)||((_283.maximumAge===""))){
}else{
var _284="Invalid input type";
__sp_location_handle_error(_282,0,_284);
return;
}
}
}
}
}
_287.PartialUpdates=false;
_288.Updateoptions=_287;
try{
temp_scb=_281;
temp_ecb=_282;
var rval=this.so.ILocation.Trace(_288,this.traceCb);
if(rval.TransactionID){
glob_obj.addToGlobalArray(rval.TransactionID,_281,_282);
}
delete _287;
delete _288;
if(rval.ErrorCode!=0){
__sp_location_handle_error(_282,rval.ErrorCode,rval.ErrorMessage);
return;
}
return rval.TransactionID;
}
catch(e){
__device_handle_exception(e,"__sp_traceLocation: "+e);
}
};
function __sp_clearTrace(_28b){
if(typeof _28b!="number"){
var _28c="Invalid input type";
__sp_location_handle_error(fail_cb,0,_28c);
}
var _28d={TransactionID:_28b};
try{
var _28e=this.so.ILocation.Cancel(_28d);
}
catch(e){
__device_handle_exception(e,"__sp_clearTrace: "+e);
}
};
function __sp_location_instance(){
this.descriptor=new __sp_location_descriptor();
this.getLocation=__sp_getLocation;
this.getLocationCb=__sp_getLocation_cb;
this.traceLocation=__sp_traceLocation;
this.traceCb=__sp_traceLocation_cb;
this.clearTrace=__sp_clearTrace;
try{
this.so=device.getServiceObject("Service.Location","ILocation");
}
catch(e){
this.so=null;
__device_handle_exception(e,"Location service not available");
}
};
function __device_commlog_descriptor(_28f){
this.interfaceName=_28f.interfaceName;
this.version=_28f.version;
};
function __device_commlog_getList(_290,_291,_292){
return this.provider.getList(_290,_291,_292);
};
function __device_commlog_setNotification(_293,_294){
return this.provider.setNotification(_293,_294);
};
function __device_commlog_cancelNotification(){
return this.provider.cancelNotification();
};
function __device_commlog_cancel(_295){
return this.provider.cancel(_295);
};
function __device_commlog_deleteLogEntry(_296){
return this.provider.deleteLogEntry(_296);
};
function __device_commlog(_297){
this.provider=_297;
this.interfaceName=_297.descriptor.interfaceName;
this.version=_297.descriptor.version;
this.getList=__device_commlog_getList;
this.setNotification=__device_commlog_setNotification;
this.cancelNotification=__device_commlog_cancelNotification;
this.cancel=__device_commlog_cancel;
this.deleteLogEntry=__device_commlog_deleteLogEntry;
};
var __device_commlog_service_entry={"name":null,"version":null,"proto":__device_commlog,"descriptor":__device_commlog_descriptor,"providers":[{"descriptor":__sp_commlog_descriptor,"instance":__sp_commlog_instance}]};
var invoker_notification;
function __sp_commlog_descriptor(){
this.interfaceName="commlog";
if(window.__Service_Interface_Ver){
this.version=__Service_Interface_Ver;
}else{
this.version=1;
}
};
var __sp_commlog_type_constants={"call":0,"sms":3};
var __sp_commlog_constants={"received":0,"missed":5,"outgoing":1};
var __sp_commlog_constants_output={"Received":0,"Missed":5,"Outgoing":1};
var __notifArr=new Array();
var __notifCount=0;
__Notification.prototype=new Object();
__Notification.prototype.constructor=__Notification;
function __Notification(_298,_299){
this.connectionId=_298;
this.callback=_299;
};
var __nofLogs;
function __get_const_string(def,val){
var i;
for(i in def){
if(def[i]==val){
return i;
}
}
return null;
};
function __get_const_val(def,str){
if(def[str]!=undefined){
return def[str];
}
return null;
};
function __device_commlog_item(_29f){
if(!_29f){
return null;
}
var evt={};
evt.type=__get_const_string(__sp_commlog_type_constants,_29f.EventType);
if(evt.type==null||evt.type==undefined){
return null;
}
evt.phoneNumber=_29f.PhoneNumber;
if(evt.phoneNumber==null||evt.phoneNumber==undefined||evt.phoneNumber.length==0){
evt.phoneNumber="private number";
}
evt.time=_29f.EventTime;
evt.flag=(_29f.Direction==undefined)?null:__get_const_string(__sp_commlog_constants_output,_29f.Direction);
evt.summary=_29f.Description;
evt.logId=Number(_29f.id);
evt.contactName=_29f.RemoteParty;
if(!evt.contactName){
evt.contactName=evt.phoneNumber;
}
return evt;
};
function __sp_commlog_iterator_get_next(){
if(typeof __nofLogs=="number"){
if(__nofLogs<=0){
return null;
}
__nofLogs=__nofLogs-1;
}
if((typeof this.buffer=="object")&&(this.buffer!=null)){
var b1=this.buffer;
this.buffer=null;
var _2a2=new __device_commlog_item(b1);
return _2a2;
}else{
var _2a3;
if(this.iter!=undefined&&this.iter!=null){
while(_2a3=this.iter.getNext()){
if(_2a3.EventType==0||_2a3.EventType==3){
break;
}
}
}
if(typeof _2a3=="undefined"){
return null;
}
var rval=new __device_commlog_item(_2a3);
_2a3.close();
return rval;
}
};
function __sp_commlog_iterator_has_next(){
if(__nofLogs<=0){
return false;
}
if(this.iter!=undefined&&this.iter!=null){
while(this.buffer=this.iter.getNext()){
if(this.buffer.EventType==0||this.buffer.EventType==3){
break;
}
}
}
if((typeof this.buffer=="object")&&(this.buffer!=null)){
return true;
}else{
return false;
}
};
function __sp_commlog_iterator_close(){
this.iter.close();
};
function __sp_commlog_iterator(_2a5){
this.iter=_2a5;
this.buffer=null;
this.next=__sp_commlog_iterator_get_next;
this.hasNext=__sp_commlog_iterator_has_next;
this.close=__sp_commlog_iterator_close;
this.nofLogs=__nofLogs;
};
function __sp_commlog_getList_cb(arg1,arg2,arg3){
var _2a9;
var _2aa;
var iter=null;
var _2ac=null;
var _2ad;
_2ad=glob_obj.getFromArray(arg1);
if(_2ad){
_2a9=_2ad.success_cb;
_2aa=_2ad.error_cb;
}else{
alert("Commlog: __sp_commlog_getList_cb : Callback not found ");
return;
}
if(arg3.ErrorCode!=0){
if(arg3.ErrorMessage){
_2ac=splitErrorMessage(arg3.ErrorMessage);
}else{
_2ac="operation failed";
}
if(_2aa){
setTimeout(function(){
_2aa(new DeviceException(MapErrorCode[arg3.ErrorCode],"Commlog: getList: "+_2ac));
},1000);
return;
}
}else{
if(arg3.ReturnValue){
iter=new __sp_commlog_iterator(arg3.ReturnValue);
}
}
if(arg2!=event_cancelled){
_2a9(iter);
}
glob_obj.removeFromArray(arg1);
};
function __sp_commlog_getList(_2ae,_2af,_2b0){
if(_2ae==null||_2ae==undefined){
throw new DeviceException(this.error.MISSING_ARG_ERR,"CommLog:getList:callback is Required");
}else{
if(typeof _2ae!="function"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"CommLog:getList:Invalid Callback");
}
}
if(_2b0){
if(typeof (_2b0)!="function"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"CommLog: getList: ErrorCallback is invalid");
}
}
if(_2af!=null&&_2af!=undefined){
if(typeof _2af!="object"||__device_typeof(_2af)=="Array"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"CommLog: getList: Match is not an object");
}
if(_2af.type!=null&&_2af.type!=undefined){
if(typeof _2af.type!="string"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"CommLog: getList: Type is not a string");
}
}
if(_2af.flag!=null&&_2af.flag!=undefined){
if(typeof _2af.flag!="string"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"CommLog: getList: Flag is not a string");
}
if(_2af.type){
if(_2af.type.toLowerCase()=="sms"&&_2af.flag.toLowerCase()=="missed"){
if(_2b0){
_2b0(new DeviceException(this.error.DATA_OUT_OF_RANGE_ERR,"commlogs: getList: Missed is not supported for sms"));
return;
}else{
throw new DeviceException(this.error.DATA_OUT_OF_RANGE_ERR,"commlogs: getList: Missed is not supported for sms");
}
}
}
}
if(_2af.nofLogs!=null&&_2af.nofLogs!=undefined){
if(typeof _2af.nofLogs!="number"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"CommLog: getList: nofLogs is invalid");
}
}
}
try{
var _2b1={};
modifyObjectBaseProp(_2b1);
_2b1.Type="Log";
_2b1.Filter={};
modifyObjectBaseProp(_2b1.Filter);
if(_2af){
if(_2af.type){
var _2b2;
_2b2=__get_const_val(__sp_commlog_type_constants,_2af.type.toLowerCase());
if(_2b2!=undefined){
_2b1.Filter.EventType=_2b2;
}else{
if(_2b0){
_2b0(new DeviceException(this.error.DATA_OUT_OF_RANGE_ERR,"CommLog: getList: Type is out of range"));
return;
}else{
throw new DeviceException(this.error.DATA_OUT_OF_RANGE_ERR,"CommLog: getList: Type is out of range");
}
}
}
if(_2af.nofLogs!=null&&_2af.nofLogs!=undefined){
if((_2af.nofLogs<0)||(_2af.nofLogs!=(_2af.nofLogs|0))){
if(_2b0){
_2b0(new DeviceException(this.error.DATA_OUT_OF_RANGE_ERR,"CommLog: getList: nofLogs is out of range"));
return;
}else{
throw new DeviceException(this.error.DATA_OUT_OF_RANGE_ERR,"CommLog: getList: nofLogs is out of range");
}
}
__nofLogs=_2af.nofLogs;
}
if(_2af.flag){
var _2b3;
_2b3=__get_const_val(__sp_commlog_constants,_2af.flag.toLowerCase());
if(_2b3!=undefined){
_2b1.Filter.Direction=_2b3;
}else{
if(_2b0){
_2b0(new DeviceException(this.error.DATA_OUT_OF_RANGE_ERR,"CommLog: getList: Flag is out of range"));
}else{
throw new DeviceException(this.error.DATA_OUT_OF_RANGE_ERR,"CommLog: getList: Flag is out of range");
}
}
}
if(_2af.phoneNumber!=null&&_2af.phoneNumber!=undefined){
if(_2af.phoneNumber!=""){
_2b1.Filter.PhoneNumber=_2af.phoneNumber;
}
}
if(_2af.contactName!=null&&_2af.contactName!=undefined){
if(_2af.contactName!=""){
_2b1.Filter.RemoteParty=_2af.contactName;
}
}
if(_2af.startTime!=null&&_2af.startTime!=undefined){
_2b1.Filter.StartTime=_2af.startTime;
}
if(_2af.endTime!=null&&_2af.endTime!=undefined){
_2b1.Filter.EndTime=_2af.endTime;
}
}
temp_scb=_2ae;
temp_ecb=_2b0;
var _2b4=this.so.IDataSource.GetList(_2b1,this.getListCb);
if(_2b4.TransactionID){
glob_obj.addToGlobalArray(_2b4.TransactionID,_2ae,_2b0);
}
if(_2b1.Filter){
delete _2b1.Filter.Direction;
delete _2b1.Filter.EventType;
delete _2b1.Filter.PhoneNumber;
}
if(_2b1){
delete _2b1.Filter;
delete _2b1.Type;
}
if(_2b4.ErrorCode!=0){
var _2b5="operation failed";
if(_2b4.ErrorMessage){
_2b5=splitErrorMessage(_2b4.ErrorMessage);
}
switch(MapErrorCode[_2b4.ErrorCode]){
case this.error.INVALID_ARG_ERR:
case this.error.MISSING_ARG_ERR:
case this.error.NOT_SUPPORTED_ERR:
throw new DeviceException(MapErrorCode[_2b4.ErrorCode],"CommLog:getList:"+_2b5);
break;
default:
if(_2b0){
_2b0(new DeviceException(MapErrorCode[_2b4.ErrorCode],"CommLog:getList:"+_2b5));
return;
}else{
throw new DeviceException(MapErrorCode[_2b4.ErrorCode],"CommLog:getList:"+_2b5);
}
}
}
return _2b4.TransactionID;
}
catch(e){
__device_handle_exception(e,"__sp_commlog_Input_validation: "+e);
}
};
function __sp_commlog_setNotification_cb(arg1,arg2,arg3){
var _2b9;
var _2ba;
var _2bb=null;
var _2bc;
_2bc=glob_obj.getFromArray(arg1);
if(_2bc){
_2b9=_2bc.success_cb;
_2ba=_2bc.error_cb;
}else{
alert("Commlog: __sp_commlog_setNotification_cb : Callback not found ");
return;
}
if(arg3.ErrorCode!=0){
if(arg3.ErrorMessage){
err_msg=splitErrorMessage(arg3.ErrorMessage);
}else{
err_msg="operation failed";
}
if(_2ba){
_2ba(new DeviceException(MapErrorCode[arg3.ErrorCode],"CommLog: getList: "+err_msg));
return;
}
}else{
if(arg3.ReturnValue){
_2bb=new __device_commlog_item(arg3.ReturnValue);
}
}
if(arg2!=event_cancelled){
for(i in __notifArr){
if(arg1==__notifArr[i].connectionId){
var _2bd=__notifArr[i];
break;
}
}
if(_2bd){
_2bd.callback(_2bb);
}
}
glob_obj.removeFromArray(arg1);
};
function __sp_commlog_setNotification(_2be,_2bf){
if(!_2be){
throw new DeviceException(this.error.MISSING_ARG_ERR,"CommLog:setNotification:callback is missing");
}
if(typeof _2be!="function"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"CommLog:setNotification:callback is invalid");
}
if(_2bf){
if(typeof (_2bf)!="function"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"CommLog: setNotification: ErrorCallback is invalid");
}
}
for(i in __notifArr){
var _2c0=__notifArr[i];
__notifArr.splice(i,1);
__notifCount=__notifArr.length;
this.so.IDataSource.Cancel({TransactionID:_2c0.connectionId});
break;
}
var _2c1={};
modifyObjectBaseProp(_2c1);
_2c1.Type="Log";
_2c1.Filter={DelayTime:0};
temp_scb=_2be;
temp_ecb=_2bf;
var _2c2=this.so.IDataSource.RequestNotification(_2c1,this.setNotificationCb);
if(_2c2.TransactionID){
glob_obj.addToGlobalArray(_2c2.TransactionID,_2be,_2bf);
}
__notifArr[__notifCount++]=new __Notification(_2c2.TransactionID,_2be);
if(_2c1){
delete _2c1.Type;
}
if(_2c2.ErrorCode!=0){
var _2c3="operation failed";
if(_2c2.ErrorMessage){
_2c3=splitErrorMessage(_2c2.ErrorMessage);
}
switch(MapErrorCode[_2c2.ErrorCode]){
case this.error.INVALID_ARG_ERR:
case this.error.MISSING_ARG_ERR:
case this.error.NOT_SUPPORTED_ERR:
throw new DeviceException(MapErrorCode[_2c2.ErrorCode],"CommLog:setNotification:"+_2c3);
break;
default:
if(_2bf){
setTimeout(function(){
_2bf(new DeviceException(MapErrorCode[_2c2.ErrorCode],"CommLog:setNotification:"+_2c3));
},1000);
}else{
throw new DeviceException(MapErrorCode[_2c2.ErrorCode],"CommLog:setNotification:"+_2c3);
}
}
}
};
function __sp_commlog_cancelNotification(){
for(i in __notifArr){
if(__notifArr[i].connectionId){
var _2c4=__notifArr[i];
__notifArr.splice(i,1);
__notifCount=__notifArr.length;
break;
}
}
if(_2c4){
var _2c5=this.so.IDataSource.Cancel({TransactionID:_2c4.connectionId});
if(_2c5.ErrorCode!=0){
var _2c6="operation failed";
if(_2c5.ErrorMessage){
_2c6=splitErrorMessage(_2c5.ErrorMessage);
}
}
}
};
function __sp_commlog_cancel(_2c7){
if(!_2c7){
throw new DeviceException(this.error.MISSING_ARG_ERR,"CommLog:cancel:transactionId is missing");
}
if(typeof _2c7!="number"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"CommLog:cancel:transactionId is invalid");
}
var _2c8=this.so.IDataSource.Cancel({TransactionID:_2c7});
if(_2c8.ErrorCode!=0){
var _2c9="operation failed";
if(_2c8.ErrorMessage){
_2c9=splitErrorMessage(_2c8.ErrorMessage);
}
throw new DeviceException(MapErrorCode[_2c8.ErrorCode],"CommLog:cancel:"+_2c9);
}
};
function __sp_commlog_deleteLogEntry(_2ca){
if(_2ca==null||_2ca==undefined){
throw new DeviceException(this.error.MISSING_ARG_ERR,"CommLog:deleteLogEntry:logId is missing");
}
if(typeof _2ca!="number"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"CommLog:deleteLogEntry:logId is invalid");
}
var _2cb={};
modifyObjectBaseProp(_2cb);
_2cb.Type="Log";
_2cb.Data={id:_2ca.toString()};
modifyObjectBaseProp(_2cb.Data);
var _2cc=this.so.IDataSource.Delete(_2cb);
if(_2cc.ErrorCode!=0){
var _2cd="operation failed";
if(_2cc.ErrorMessage){
_2cd=splitErrorMessage(_2cc.ErrorMessage);
}
throw new DeviceException(MapErrorCode[_2cc.ErrorCode],"CommLog:deleteLogEntry:"+_2cd);
}
};
function __sp_commlog_instance(){
this.descriptor=new __sp_commlog_descriptor();
this.getList=__sp_commlog_getList;
this.getListCb=__sp_commlog_getList_cb;
this.setNotification=__sp_commlog_setNotification;
this.setNotificationCb=__sp_commlog_setNotification_cb;
this.cancelNotification=__sp_commlog_cancelNotification;
this.cancel=__sp_commlog_cancel;
this.deleteLogEntry=__sp_commlog_deleteLogEntry;
this.error=new DeviceException(0,"Dummy");
try{
this.so=device.getServiceObject("Service.Logging","IDataSource");
}
catch(e){
this.so=null;
__device_handle_exception(e,"commlog service not available");
}
};
function __device_messaging_descriptor(_2ce){
this.interfaceName=_2ce.interfaceName;
this.version=_2ce.version;
};
function __device_messaging_startEditor(_2cf){
return this.provider.startEditor(_2cf);
};
function __device_messaging_getList(_2d0,_2d1,_2d2,_2d3,_2d4){
return this.provider.getList(_2d0,_2d1,_2d2,_2d3,_2d4);
};
function __device_messaging_send(_2d5,_2d6,id,_2d8){
return this.provider.send(_2d5,_2d6,id,_2d8);
};
function __device_messaging_setNotifier(_2d9,_2da){
return this.provider.setNotifier(_2d9,_2da);
};
function __device_messaging_cancelNotifier(){
return this.provider.cancelNotifier();
};
function __device_messaging_getMessage(id){
return this.provider.getMessage(id);
};
function __device_messaging_delete(id){
return this.provider.deleteMessage(id);
};
function __device_messaging_setStatus(id,_2de){
return this.provider.setStatus(id,_2de);
};
function __device_messaging_cancel(_2df){
return this.provider.cancel(_2df);
};
function __device_messaging(_2e0){
this.provider=_2e0;
this.interfaceName=_2e0.descriptor.interfaceName;
this.version=_2e0.descriptor.version;
this.SORT_ASCENDING=0;
this.SORT_DESCENDING=1;
this.SORT_BY_DATE=0;
this.SORT_BY_SENDER=1;
this.STATUS_READ=0;
this.STATUS_UNREAD=1;
this.startEditor=__device_messaging_startEditor;
this.getList=__device_messaging_getList;
this.send=__device_messaging_send;
this.setNotifier=__device_messaging_setNotifier;
this.cancelNotifier=__device_messaging_cancelNotifier;
this.getMessage=__device_messaging_getMessage;
this.deleteMessage=__device_messaging_delete;
this.setStatus=__device_messaging_setStatus;
this.cancel=__device_messaging_cancel;
};
var __device_messaging_service_entry={"name":null,"version":null,"proto":__device_messaging,"descriptor":__device_messaging_descriptor,"providers":[{"descriptor":__sp_messaging_descriptor,"instance":__sp_messaging_instance}]};
var FILE_SCHEME="file://";
function __sp_messaging_descriptor(){
this.interfaceName="messaging";
if(window.__Service_Interface_Ver){
this.version=__Service_Interface_Ver;
}else{
this.version=1;
}
};
function __sp_messaging_instance(){
this.descriptor=new __sp_messaging_descriptor();
this.startEditor=__sp_messaging_startEditor;
this.getList=__sp_messaging_getList;
this.getListcB=__sp_message_getListcB;
this.send=__sp_messaging_send;
this.sendcb=__sp_message_sendcb;
this.setNotifier=__sp_messaging_setNotifier;
this.setNotifierCb=__sp_messaging_setNotifier_cb;
this.cancelNotifier=__sp_messaging_cancelNotifier;
this.getMessage=__sp_messaging_getMessage;
this.deleteMessage=__sp_messaging_delete;
this.setStatus=__sp_messaging_setStatus;
this.cancel=__sp_messaging_cancel;
this.sendCommon=__sp_messaging_send_common;
this.SORT_ASCENDING=0;
this.SORT_DESCENDING=1;
this.SORT_BY_DATE=0;
this.SORT_BY_SENDER=1;
this.STATUS_READ=0;
this.STATUS_UNREAD=1;
this.error=new DeviceException(0,"Dummy");
try{
this.so=device.getServiceObject("Service.Messaging","IMessaging");
}
catch(e){
this.so=null;
__device_handle_exception(e,"Messaging service not available");
}
};
function __sp_attachment_build(_2e1){
if(!_2e1){
return null;
}
var _2e2={};
modifyObjectBaseProp(_2e2);
if(_2e1.uri){
if(typeof _2e1.uri!="string"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"uri is invalid");
}
if(_2e1.uri.slice(0,7)==FILE_SCHEME){
if(_2e1.uri.charAt(7)=="/"){
if(_2e1.uri.charAt(9)!=":"){
throw new DeviceException(this.error.URI_NOT_FOUND_ERR,"specified uri not found");
}
_2e2.FileName=_2e1.uri.slice(8).replace(/\057/g,"\\");
if(_2e2.FileName.length>256){
throw new DeviceException(this.error.DATA_OUT_OF_RANGE_ERR,"uri is out of range");
}
}else{
if(_2e1.uri.charAt(8)!=":"){
throw new DeviceException(this.error.URI_NOT_FOUND_ERR,"specified uri not found");
}
_2e2.FileName=_2e1.uri.slice(7).replace(/\057/g,"\\");
if(_2e2.FileName.length>256){
throw new DeviceException(this.error.DATA_OUT_OF_RANGE_ERR,"uri is out of range");
}
}
}else{
throw new DeviceException(this.error.INVALID_URI_ERR,"uri is invalid");
}
}
return _2e2;
};
function __sp_message_build(_2e3,id){
if(!_2e3){
return null;
}
var _2e5={};
modifyObjectBaseProp(_2e5);
var _2e6=0;
_2e5.MessageParam={};
modifyObjectBaseProp(_2e5.MessageParam);
_2e5.MessageParam.LaunchEditor=false;
_2e5.MessageType=(_2e3.type==undefined||_2e3.type==null)?"SMS":_2e3.type;
if(_2e3.to){
if(typeof (_2e3.to)=="string"){
_2e5.To=_2e3.to;
}else{
if(__device_typeof(_2e3.to)=="Array"&&_2e3.to.length>0){
if(_2e3.to[0]){
_2e5.To=_2e3.to[0];
}
if(_2e3.to.length>1){
if(_2e3.to.slice(1)){
_2e5.MessageParam.To=_2e3.to.slice(1);
}
}
}else{
_2e5.To=_2e3.to;
}
}
}
if(_2e3.cc){
_2e5.MessageParam.Cc=_2e3.cc;
}
if(id){
if((typeof (id)=="string")&&!(isNaN(id))){
id=Number(id);
}
_2e5.MessageParam.TemplateId=id;
}
if(_2e5.MessageType=="SMS"){
if(_2e3.body){
_2e5.BodyText=_2e3.body;
}
}
if(_2e5.MessageType=="MMS"){
if(_2e3.body){
_2e5.BodyText=_2e3.body;
}
if(_2e3.subject){
if(typeof _2e3.subject=="string"&&_2e3.subject.length>256){
throw new DeviceException(this.error.DATA_OUT_OF_RANGE_ERR,"subject length is greater than 256 characters");
}
_2e5.Subject=_2e3.subject;
}
if(_2e3.attachments){
_2e5.MessageParam.AttachmentList=[];
for(var a in _2e3.attachments){
if(typeof _2e3.attachments[a]=="object"&&__device_typeof(_2e3.attachments[a])!="Array"){
_2e5.MessageParam.AttachmentList.push(__sp_attachment_build(_2e3.attachments[a]));
_2e6=1;
}
}
if(_2e6==0){
throw new DeviceException(this.error.INVALID_ARG_ERR,"uri is invalid");
}
}
}
return _2e5;
};
function __sp_device_attachment_build(_2e8){
if(!_2e8){
return null;
}
var _2e9={};
_2e9.uri=FILE_SCHEME+_2e8.FileName;
return _2e9;
};
function __sp_device_message_build(_2ea){
if(!_2ea){
return null;
}
var _2eb={};
_2eb.body=null;
_2eb.subject=null;
_2eb.attachments=null;
_2eb.to=null;
_2eb.cc=null;
_2eb.type=_2ea.MessageType;
if(_2ea.BodyText){
_2eb.body=_2ea.BodyText;
}
if(_2ea.to){
_2eb.to=_2ea.To;
}
if(_2ea.Subject){
_2eb.subject=_2ea.Subject;
}
_2eb.attachment=false;
if(_2eb.type=="MMS"){
if(_2ea.Cc){
_2eb.cc=_2ea.Cc;
}
if(_2ea.AttachmentList){
_2eb.attachment=true;
_2eb.attachments=[];
for(var a in _2ea.AttachmentList){
if(_2ea.AttachmentList.hasOwnProperty("a")){
_2eb.attachments.push(__sp_device_attachment_build(_2ea.AttachmentList[a]));
}
}
}
}
return _2eb;
};
function __sp_device_message_info_build_notifier(_2ed){
if(!_2ed){
return null;
}
var _2ee={};
_2ee.message={};
_2ee.message.type=_2ed.MessageType;
_2ee.sender=_2ed.Sender;
_2ee.message.subject=_2ed.Subject;
_2ee.time=_2ed.Time;
_2ee.attachments=(_2ed.Attachments==undefined||_2ed.Attachments==null)?(!(_2ed.AttachmentList==undefined||_2ed.AttachmentList==null)):_2ed.Attachments;
_2ee.unread=_2ed.Unread;
_2ee.id=(_2ed.MessageId).toString();
return _2ee;
};
function __sp_device_message_info_build(_2ef){
if(!_2ef){
return null;
}
var _2f0={};
_2f0.message=__sp_device_message_build(_2ef);
_2f0.sender=_2ef.Sender;
_2f0.time=_2ef.Time;
_2f0.unread=_2ef.Unread;
_2f0.id=(_2ef.MessageId).toString();
return _2f0;
};
function __sp_message_iterator_get_next(){
var _2f1=this.iter.getNext();
if(typeof _2f1=="undefined"){
return null;
}
var _2f2=__sp_device_message_info_build(_2f1);
_2f1.close();
return _2f2;
};
function __sp_message_iterator(_2f3){
this.iter=_2f3;
this.next=__sp_message_iterator_get_next;
this.close=function(){
this.iter.close();
};
};
function __sp_message_getListcB(arg1,arg2,arg3){
var _2f7;
var _2f8;
var _2f9;
_2f9=glob_obj.getFromArray(arg1);
if(_2f9){
_2f7=_2f9.success_cb;
_2f8=_2f9.error_cb;
}else{
alert("Messaging: __sp_message_getListcB: Callback not found ");
return;
}
var iter=null;
if(arg3.ErrorCode!=0){
if(arg3.ErrorMessage){
err_msg=splitErrorMessage(arg3.ErrorMessage);
}else{
err_msg="Operation Failed";
}
if(_2f8){
_2f8(new DeviceException(MapErrorCode[arg3.ErrorCode],"Messaging: getList: "+err_msg));
return;
}
}else{
if(arg3.ReturnValue){
iter=new __sp_message_iterator(arg3.ReturnValue);
}
}
if(arg2!=event_cancelled){
_2f7(iter);
}
glob_obj.removeFromArray(arg1);
};
function __sp_messaging_getList(_2fb,_2fc,_2fd,_2fe,_2ff){
if(!_2fb){
throw new DeviceException(this.error.MISSING_ARG_ERR,"Messaging:getList:callback is missing");
}else{
if(typeof _2fb!="function"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Messaging:getList:callback is not a function");
}
}
if(_2fc!=null&&_2fc!=undefined&&typeof _2fc!="object"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Messaging:getList:match is invalid");
}
if(_2fd!=null&&_2fd!=undefined&&typeof _2fd!="number"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Messaging:getList:sortkey is invalid");
}
if(_2fe!=null&&_2fe!=undefined&&typeof _2fe!="number"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Messaging:getList:sortorder is invalid");
}
if(_2fd!=null&&_2fd!=undefined&&typeof _2fd=="number"){
if((_2fd!=0)&&(_2fd!=1)){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Messaging:getList:sortkey is invalid");
}
}
if(_2fe!=null&&_2fe!=undefined&&typeof _2fe=="number"){
if((_2fe!=0)&&(_2fe!=1)){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Messaging:getList:sortorder is invalid");
}
}
if(_2ff){
if(typeof (_2ff)!="function"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Messaging: startEditor: ErrorCallback is invalid");
}
}
var _300={};
modifyObjectBaseProp(_300);
_300.Type="Inbox";
_300.Filter={};
modifyObjectBaseProp(_300.Filter);
if(_2fc){
if(_2fc.type!=null&&_2fc.type!=undefined){
_300.Filter.MessageTypeList=_2fc.type;
}
if(_2fc.senders!=null&&_2fc.senders!=undefined){
_300.Filter.SenderList=_2fc.senders;
}
if(_2fc.subject!=null&&_2fc.subject!=undefined){
if(_2fc.subject.length>256){
if(_2ff){
_2ff(new DeviceException(this.error.DATA_OUT_OF_RANGE_ERR,"Messaging:getList:subject is out of range"));
return;
}else{
throw new DeviceException(this.error.DATA_OUT_OF_RANGE_ERR,"Messaging:getList:subject is out of range");
}
}else{
_300.Filter.Subject=_2fc.subject;
}
}
if(_2fc.start!=null&&_2fc.start!=undefined){
_300.Filter.StartDate=_2fc.start;
}
if(_2fc.end!=null&&_2fc.end!=undefined){
_300.Filter.EndDate=_2fc.end;
}
}
if(_2fd||_2fe){
_300.SortOrder={};
modifyObjectBaseProp(_300.SortOrder);
if(_2fd){
if((_2fd==this.SORT_BY_DATE)){
_300.SortOrder.Key="Date";
}else{
if((_2fd==this.SORT_BY_SENDER)){
_300.SortOrder.Key="Sender";
}
}
}else{
_300.SortOrder.Key="Date";
}
if(_2fe){
if((_2fe==this.SORT_ASCENDING)){
_300.SortOrder.Order="Ascending";
}else{
if((_2fe==this.SORT_DESCENDING)){
_300.SortOrder.Order="Descending";
}
}
}else{
_300.SortOrder.Order="Ascending";
}
}
try{
temp_scb=_2fb;
temp_ecb=_2ff;
var _301=this.so.IMessaging.GetList(_300,this.getListcB);
if(_301.TransactionID){
glob_obj.addToGlobalArray(_301.TransactionID,_2fb,_2ff);
}
if(_300){
delete _300.Filter;
delete _300.SortOrder;
delete _300.Type;
}
if(_301.ErrorCode!=0){
var _302="operation failed";
if(_301.ErrorMessage){
_302=splitErrorMessage(_301.ErrorMessage);
}
switch(MapErrorCode[_301.ErrorCode]){
case this.error.INVALID_ARG_ERR:
case this.error.MISSING_ARG_ERR:
case this.error.NOT_SUPPORTED_ERR:
throw new DeviceException(MapErrorCode[_301.ErrorCode],"Messaging:getList:"+_302);
break;
default:
if(_2ff){
setTimeout(function(){
_2ff(new DeviceException(MapErrorCode[_301.ErrorCode],"Messaging:getList:"+_302));
},500);
}else{
throw new DeviceException(MapErrorCode[_301.ErrorCode],"Messaging:getList:"+_302);
}
}
}
return _301.TransactionID;
}
catch(e){
__device_handle_exception(e,"__sp_messaging_getList: "+e);
}
};
function __sp_message_sendcb(arg1,arg2,arg3){
var _306;
var eCB;
var _308=glob_obj.getFromArray(arg1);
if(_308){
_306=_308.success_cb;
eCB=_308.error_cb;
}else{
alert("Messaging : __sp_message_sendcb : Callback not found");
return;
}
if(_306){
var _309="operation failed";
if(arg3.ErrorCode!=0){
if(arg3.ErrorMessage){
_309=splitErrorMessage(arg3.ErrorMessage);
}
if(eCB){
setTimeout(function(){
eCB(new DeviceException(MapErrorCode[arg3.ErrorCode],"Messaging: send: "+_309));
},500);
return;
}
}
if(arg2!=event_cancelled){
_306();
}
}
glob_obj.removeFromArray(arg1);
};
function __sp_messaging_send_common(_30a,_30b,_30c,id,eCB){
var _30f=__sp_message_build(_30a,id);
_30f.MessageParam.LaunchEditor=_30b;
var _310;
if(_30b==false){
temp_scb=_30c;
temp_ecb=eCB;
_310=this.so.IMessaging.Send(_30f,this.sendcb);
if(_310.TransactionID){
glob_obj.addToGlobalArray(_310.TransactionID,_30c,eCB);
}
if(_310.ErrorCode!=0){
var _311="operation failed";
if(_310.ErrorMessage){
_311=splitErrorMessage(_310.ErrorMessage);
}
switch(MapErrorCode[_310.ErrorCode]){
case this.error.INVALID_ARG_ERR:
case this.error.MISSING_ARG_ERR:
case this.error.NOT_SUPPORTED_ERR:
throw new DeviceException(MapErrorCode[_310.ErrorCode],_311);
break;
default:
if(eCB){
setTimeout(function(){
eCB(new DeviceException(MapErrorCode[_310.ErrorCode],_311));
},500);
return;
}else{
throw new DeviceException(MapErrorCode[_310.ErrorCode],_311);
}
}
}
var _312=_310.TransactionID;
return _312;
}else{
_310=this.so.IMessaging.Send(_30f);
if(_310.ErrorCode!=0){
if(_310.ErrorMessage){
var _313=splitErrorMessage(_310.ErrorMessage);
throw new DeviceException(MapErrorCode[_310.ErrorCode],"Messaging:startEditor"+_313);
}else{
throw new DeviceException(MapErrorCode[_310.ErrorCode],"Messaging:startEditor:operation failed");
}
}
}
if(_30f){
delete _30f.MessageParam;
}
};
function __sp_messaging_startEditor(_314){
if(!_314){
throw new DeviceException(this.error.MISSING_ARG_ERR,"Messaging:startEditor:message is missing");
}else{
if(typeof _314!="object"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Messaging:startEditor:message is invalid");
}
}
if((_314.subject)){
if((_314.subject).length>256){
throw new DeviceException(this.error.DATA_OUT_OF_RANGE_ERR,"Messaging:startEditor:subject is too lengthy");
}
}
if(_314.to==undefined||_314.to==null){
throw new DeviceException(this.error.MISSING_ARG_ERR,"Messaging:startEditor:to field is missing");
}
if(_314.attachments!=undefined&&_314.attachments!=null&&typeof _314.attachments!="object"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Messaging:startEditor:attachment is invalid");
}
if(_314){
if(_314.body){
if(typeof (_314.body)!="string"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Messaging:startEditor:body is invalid");
}
}
}
try{
this.sendCommon(_314,true,null);
}
catch(e){
var _315=null;
if(e.message){
_315=new DeviceException(e.code,"Messaging:startEditor:"+e.message);
}else{
_315=new DeviceException(e.code,"Messaging:startEditor:operation failed");
}
__device_handle_exception(_315,"__sp_messaging_startEditor: "+_315);
}
};
function __sp_messaging_send(_316,_317,id,_319){
if(!_317){
throw new DeviceException(this.error.MISSING_ARG_ERR,"Messaging:send:message is missing");
}else{
if(typeof _317!="object"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Messaging:send:message is invalid");
}
}
if(!_316){
throw new DeviceException(this.error.MISSING_ARG_ERR,"Messaging:send:callback is missing");
}else{
if(typeof _316!="function"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Messaging:send:callback is invalid");
}
}
if(_317.to==undefined||_317.to==null){
throw new DeviceException(this.error.MISSING_ARG_ERR,"Messaging:send:to field is missing");
}
if(_317.attachments!=undefined&&_317.attachments!=null&&typeof _317.attachments!="object"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Messaging:send:attachment is invalid");
}
if(!id){
id="";
}
if((typeof id)=="function"){
var _31a=id;
id="";
_319=_31a;
}
if((typeof _319)=="undefined"||_319==null){
_319=null;
}else{
if((typeof _319)!="function"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Messaging:send:errorCallback is not a function");
}
}
var _31b=function(arg1,arg2,arg3){
var _31f=_316;
var _320=_319;
var iter=null;
if(arg3.ErrorCode!=0){
var _322;
if(arg3.ErrorMessage){
_322=splitErrorMessage(arg3.ErrorMessage);
}else{
_322="Operation Failed";
}
_320(new DeviceException(MapErrorCode[arg3.ErrorCode],"Messaging:startEditor: "+_322));
return;
}else{
if(arg3.ReturnValue){
iter=new __sp_message_iterator(arg3.ReturnValue);
_31f(iter);
}
}
if(arg2!=event_cancelled){
_31f(iter);
}
};
try{
var _323=this.sendCommon(_317,false,_316,id,_319);
return _323;
}
catch(e){
var _324=null;
switch(e.code){
case this.error.INVALID_ARG_ERR:
case this.error.MISSING_ARG_ERR:
case this.error.NOT_SUPPORTED_ERR:
throw new DeviceException(e.code,"Messaging:send:"+e.message);
break;
default:
if(_319){
setTimeout(function(){
_319(new DeviceException(e.code,"Messaging:send:"+e.message));
},1000);
}else{
throw new DeviceException(e.code,"Messaging:send:"+e.message);
}
}
}
};
function __sp_messaging_setNotifier_cb(arg1,arg2,arg3){
var _328;
var _329;
var _32a=null;
var _32b=null;
var _32c;
_32c=glob_obj.getFromArray(arg1);
if(_32c){
_328=_32c.success_cb;
_329=_32c.error_cb;
}else{
alert("Messaging: __sp_messaging_setNotifier_cb : Callback not found ");
return;
}
if(arg3.ErrorCode!=0){
if(arg3.ErrorMessage){
_32b=splitErrorMessage(arg3.ErrorMessage);
}else{
_32b="operation failed";
}
if(_329){
_329(new DeviceException(MapErrorCode[arg3.ErrorCode],"Messaging:setNotifier: "+_32b));
return;
}
}else{
if(arg3.ReturnValue){
_32a=new __sp_device_message_info_build_notifier(arg3.ReturnValue);
arg3.ReturnValue.close();
}
}
if(arg2!=event_cancelled){
_328(_32a.id);
}
glob_obj.removeFromArray(arg1);
};
function __sp_messaging_setNotifier(_32d,_32e){
if(!_32d){
throw new DeviceException(this.error.MISSING_ARG_ERR,"Messaging:setNotifier:callback is missing");
}else{
if(typeof _32d!="function"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Messaging:setNotifier:callback is invalid");
}
}
if(_32e){
if(typeof (_32e)!="function"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Messaging:setNotifier: ErrorCallback is invalid");
}
}
var _32f={};
modifyObjectBaseProp(_32f);
_32f.Type="NewMessage";
try{
temp_scb=_32d;
temp_ecb=_32e;
var _330=this.so.IMessaging.RegisterNotification(_32f,this.setNotifierCb);
if(_330.TransactionID){
glob_obj.addToGlobalArray(_330.TransactionID,_32d,_32e);
}
if(_32f){
delete _32f.Type;
}
if(_330.ErrorCode!=0){
var _331="operation failed";
if(_330.ErrorMessage){
_331=splitErrorMessage(_330.ErrorMessage);
}
switch(MapErrorCode[_330.ErrorCode]){
case this.error.INVALID_ARG_ERR:
case this.error.MISSING_ARG_ERR:
case this.error.NOT_SUPPORTED_ERR:
throw new DeviceException(MapErrorCode[_330.ErrorCode],"Messaging:setNotifier:"+_331);
break;
default:
if(_32e){
setTimeout(function(){
_32e(new DeviceException(MapErrorCode[_330.ErrorCode],"Messaging:setNotifier:"+_331));
},1000);
}else{
throw new DeviceException(MapErrorCode[_330.ErrorCode],"Messaging:setNotifier:"+_331);
}
}
}
var _332=_330.TransactionID;
return _332;
}
catch(e){
__device_handle_exception(e,"__sp_messaging_setNotifier: "+e.toString());
}
};
function __sp_messaging_cancelNotifier(){
var _333={};
modifyObjectBaseProp(_333);
_333.Type="NewMessage";
try{
var _334=this.so.IMessaging.CancelNotification(_333);
if(_333){
delete _333.Type;
}
if(_334.ErrorCode!=0){
if(_334.ErrorMessage){
var _335=splitErrorMessage(_334.ErrorMessage);
throw new DeviceException(MapErrorCode[_334.ErrorCode],"Messaging:cancelNotifier"+_335);
}else{
throw new DeviceException(MapErrorCode[_334.ErrorCode],"Messaging:cancelNotifier:operation failed");
}
}
}
catch(e){
__device_handle_exception(e,"__sp_messaging_cancelNotifier: "+e);
}
};
function __sp_messaging_getMessage(id){
if(!id){
throw new DeviceException(this.error.MISSING_ARG_ERR,"Messaging:getMessage:id is missing");
}else{
if((typeof id)!="string"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Messaging:getMessage:MessageId should be a string");
}
}
if((typeof id=="string")&&!(isNaN(id))){
id=Number(id);
if(id==0){
throw new DeviceException(this.error.DATA_NOT_FOUND_ERR,"Messaging:getMessage:id not found");
}
if(id<0){
throw new DeviceException(this.error.DATA_OUT_OF_RANGE_ERR,"Messaging:getMessage:id is out of range");
}
}
var _337={};
modifyObjectBaseProp(_337);
_337.Type="Inbox";
_337.Filter={};
modifyObjectBaseProp(_337.Filter);
_337.Filter.MessageId=id;
try{
var _338=this.so.IMessaging.GetList(_337);
if(_337){
delete _337.Filter;
delete _337.Type;
}
if(_338.ErrorCode!=0){
if(_338.ErrorMessage){
var _339=splitErrorMessage(_338.ErrorMessage);
throw new DeviceException(MapErrorCode[_338.ErrorCode],"Messaging:getMessage"+_339);
}else{
throw new DeviceException(MapErrorCode[_338.ErrorCode],"Messaging:getMessage:operation failed");
}
}
if(_338.ReturnValue){
var iter=new __sp_message_iterator(_338.ReturnValue);
var _33b=iter.next();
if(_33b){
return _33b;
}else{
throw new DeviceException(this.error.DATA_NOT_FOUND_ERR,"Messaging:getMessage:id not found");
}
}
}
catch(e){
__device_handle_exception(e,"__sp_messaging_getMessage: "+e);
}
};
function __sp_messaging_delete(id){
a("messageId"+typeof id);
if(!id){
throw new DeviceException(this.error.MISSING_ARG_ERR,"Messaging:delete:id is missing");
}else{
if((typeof id)!="string"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Messaging:deleteMessage:MessageId should be a string");
}
}
if((typeof id=="string")&&!(isNaN(id))){
id=Number(id);
if(id==0){
throw new DeviceException(this.error.DATA_NOT_FOUND_ERR,"Messaging:delete:id not found");
}
if(id<0){
throw new DeviceException(this.error.DATA_OUT_OF_RANGE_ERR,"Messaging:delete:id is out of range");
}
}
var _33d={};
modifyObjectBaseProp(_33d);
_33d.MessageId=id;
try{
var _33e=this.so.IMessaging.Delete(_33d);
a("MapErrorCode[ result.ErrorCode ]"+MapErrorCode[_33e.ErrorCode]);
if(_33d){
delete _33d.MessageId;
}
if(_33e.ErrorCode!=0){
if(_33e.ErrorMessage){
var _33f=splitErrorMessage(_33e.ErrorMessage);
throw new DeviceException(MapErrorCode[_33e.ErrorCode],"Messaging:delete"+_33f);
}else{
throw new DeviceException(MapErrorCode[_33e.ErrorCode],"Messaging:delete:operation failed");
}
}
}
catch(e){
__device_handle_exception(e,"__sp_messaging_delete: "+e);
}
};
function __sp_messaging_setStatus(id,_341){
if(id==null||id==undefined||(id.length)<=0){
throw new DeviceException(this.error.MISSING_ARG_ERR,"Messaging:setStatus:id is missing");
}
if((typeof id)!="string"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Messaging:setStatus:id should be string");
}
if(_341==null||_341==undefined){
throw new DeviceException(this.error.MISSING_ARG_ERR,"Messaging:setStatus:status is missing");
}
if(typeof _341!="number"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Messaging:setStatus:status is invalid");
}
if(typeof _341=="number"&&_341!=0&&_341!=1){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Messaging:setStatus:status is invalid");
}
if((typeof id=="string")&&!(isNaN(id))){
id=Number(id);
if(id==0){
throw new DeviceException(this.error.DATA_NOT_FOUND_ERR,"Messaging:setStatus:id not found");
}
if(id<0){
throw new DeviceException(this.error.DATA_OUT_OF_RANGE_ERR,"Messaging:setStatus:id is out of range");
}
}
var _342={};
modifyObjectBaseProp(_342);
_342.MessageId=id;
if((_341==this.STATUS_UNREAD)){
_342.Status="Unread";
}else{
if((_341==this.STATUS_READ)){
a("in read");
_342.Status="Read";
}
}
try{
var _343=this.so.IMessaging.ChangeStatus(_342);
if(_342){
delete _342.MessageId;
delete _342.Status;
}
if(_343.ErrorCode!=0){
if(_343.ErrorMessage){
var _344=splitErrorMessage(_343.ErrorMessage);
throw new DeviceException(MapErrorCode[_343.ErrorCode],"Messaging:setStatus"+_344);
}else{
throw new DeviceException(MapErrorCode[_343.ErrorCode],"Messaging:setStatus:operation failed");
}
}
}
catch(e){
__device_handle_exception(e,"__sp_messaging_setStatus: "+e);
}
};
function __sp_messaging_cancel(_345){
if(_345==null||_345==undefined){
throw new DeviceException(this.error.MISSING_ARG_ERR,"Messaging:setStatus:id is missing");
}
if(typeof _345!="number"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Messaging:cancel:id is invalid");
}
var _346={};
modifyObjectBaseProp(_346);
_346.TransactionID=_345;
try{
var _347=this.so.IMessaging.Cancel(_346);
if(_346){
delete _346.TransactionID;
}
if(_347.ErrorCode!=0){
var err;
if(_347.ErrorCode==1000){
err=this.error.DATA_NOT_FOUND_ERR;
}else{
err=MapErrorCode[_347.ErrorCode];
}
if(_347.ErrorMessage){
var _349=splitErrorMessage(_347.ErrorMessage);
throw new DeviceException(err,"Messaging:cancel"+_349);
}else{
throw new DeviceException(err,"Messaging:cancel:operation failed");
}
}
}
catch(e){
__device_handle_exception(e,"__sp_messaging_setStatus: "+e);
}
};
function __device_calendar_descriptor(_34a){
this.interfaceName=_34a.interfaceName;
this.version=_34a.version;
};
function __device_calendar_startEditor(_34b,_34c,_34d){
this.provider.startEditor(_34b,_34c,_34d);
};
function __device_calendar_getList(_34e,_34f,_350){
return this.provider.getList(_34e,_34f,_350);
};
function __device_calendar_add(_351){
return this.provider.addEntry(_351);
};
function __device_calendar_update(_352){
return this.provider.updateEntry(_352);
};
function __device_calendar_delete(data){
this.provider.deleteEntry(data);
};
function __device_calendar_cancel(_354){
this.provider.cancel(_354);
};
function __device_calendar(_355){
this.provider=_355;
this.interfaceName=_355.descriptor.interfaceName;
this.version=_355.descriptor.version;
this.startEditor=__device_calendar_startEditor;
this.getList=__device_calendar_getList;
this.addEntry=__device_calendar_add;
this.updateEntry=__device_calendar_update;
this.deleteEntry=__device_calendar_delete;
this.cancel=__device_calendar_cancel;
};
var __device_calendar_service_entry={"name":null,"version":null,"proto":__device_calendar,"descriptor":__device_calendar_descriptor,"providers":[{"descriptor":__sp_calendar_descriptor,"instance":__sp_calendar_instance}]};
var dataGetList=0;
var isUpdate=0;
function __sp_calendar_descriptor(){
this.interfaceName="calendar";
if(window.__Service_Interface_Ver){
this.version=__Service_Interface_Ver;
}else{
this.version=1;
}
};
function __sp_calendar_entry_time(_356,end,_358){
if(_356){
var st=new Date(_356);
this.begin=st;
}
if(end){
var en=new Date(end);
this.end=en;
}
if(_358){
var al=new Date(_358);
this.alarm=al;
}
};
function __sp_calendar_isInputValid(_35c){
if(_35c){
if(_35c.id){
if(typeof (_35c.id)!="string"){
return false;
}
}
if(_35c.type){
if((typeof (_35c.type)!="string")||!__sp_calendar_entry_types.match(_35c.type)){
return false;
}
}
if(_35c.text){
if(typeof (_35c.text)!="string"){
return false;
}
}
if(_35c.range){
if(typeof (_35c.range)!="object"){
return false;
}
if(_35c.range.begin){
if(typeof (_35c.range.begin)!="object"){
return false;
}
}
if(_35c.range.end){
if(typeof (_35c.range.end)!="object"){
return false;
}
}
}
if(_35c.summary){
if(typeof (_35c.summary)!="string"){
return false;
}
}
if(_35c.description){
if(typeof (_35c.description)!="string"){
return false;
}
}
if(_35c.status){
if(typeof (_35c.status)!="string"){
return false;
}
}
if(_35c.location){
if(typeof (_35c.location)!="string"){
return false;
}
}
if(_35c.priority){
if(typeof (_35c.priority)!="number"){
return false;
}
}
if(_35c.instanceStartTime){
if(typeof (_35c.instanceStartTime)!="object"){
return false;
}
}
if(_35c.exceptionDates){
if(typeof (_35c.exceptionDates)!="object"){
return false;
}
}
if(_35c.time){
if(typeof _35c.time!="object"){
return false;
}
if(_35c.time.begin){
if(typeof (_35c.time.begin)!="object"){
return false;
}
if(_35c.time.begin=="Invalid Date"){
return false;
}
try{
(_35c.time.begin).getTime();
}
catch(e){
return false;
}
}
if(_35c.time.end){
if(typeof (_35c.time.end)!="object"){
return false;
}
if(_35c.time.end=="Invalid Date"){
return false;
}
try{
(_35c.time.end).getTime();
}
catch(e){
return false;
}
}
if(_35c.time.begin&&_35c.time.end){
if(_35c.time.begin>_35c.time.end){
return false;
}
}
if(_35c.time.alarm){
if(typeof (_35c.time.alarm)!="object"){
return false;
}
try{
(_35c.time.alarm).getTime();
}
catch(e){
return false;
}
}
}
if(_35c.repeatRule){
if(typeof _35c.repeatRule!="object"){
return false;
}
if(_35c.repeatRule.frequency){
if(typeof (_35c.repeatRule.frequency)!="string"){
return false;
}
}
if(_35c.repeatRule.startDate){
if(typeof (_35c.repeatRule.startDate)!="object"){
return false;
}
if((_35c.repeatRule.startDate)=="Invalid Date"){
return false;
}
try{
(_35c.repeatRule.startDate).getTime();
}
catch(e){
return false;
}
}
if(_35c.repeatRule.untilDate){
if(typeof (_35c.repeatRule.untilDate)!="object"){
return false;
}
if((_35c.repeatRule.untilDate)=="Invalid Date"){
return false;
}
try{
(_35c.repeatRule.untilDate).getTime();
}
catch(e){
return false;
}
}
if(_35c.repeatRule.startDate&&_35c.repeatRule.untilDate){
if(_35c.repeatRule.startDate>_35c.repeatRule.untilDate){
return false;
}
}
if(_35c.repeatRule.interval){
if(typeof (_35c.repeatRule.interval)!="number"){
return false;
}
}
if(_35c.repeatRule.month){
if(typeof (_35c.repeatRule.month)!="number"){
return false;
}
}
if(_35c.repeatRule.weekDays){
if(typeof (_35c.repeatRule.weekDays)!="object"){
return false;
}
}
if(_35c.repeatRule.daysOfMonth){
if(typeof (_35c.repeatRule.daysOfMonth)!="object"){
return false;
}
}
if(_35c.repeatRule.monthDates){
if(typeof (_35c.repeatRule.monthDates)!="object"){
return false;
}
}
}
}
return true;
};
function __sp_calendar_getList_repeatRule(_35d){
var _35e;
switch(_35d.Type){
case 1:
_35e="daily";
this.frequency=_35e.toString();
break;
case 2:
_35e="weekly";
this.frequency=_35e.toString();
break;
case 3:
_35e="monthly";
this.frequency=_35e.toString();
break;
case 4:
_35e="yearly";
this.frequency=_35e.toString();
break;
default:
throw new DeviceException(this.error.INVALID_ARG_ERR,"Calendar: Repeat Rule Type is Invalid");
}
if(_35d.StartDate){
this.startDate=new Date(_35d.StartDate);
}
if(_35d.UntilDate){
this.untilDate=new Date(_35d.UntilDate);
}
if(_35d.Interval){
this.interval=_35d.Interval;
}
if(_35d.DaysInWeek){
this.weekDays=[];
for(var a in _35d.DaysInWeek){
if(_35d.DaysInWeek[a]==6){
_35d.DaysInWeek[a]=0;
}else{
_35d.DaysInWeek[a]=_35d.DaysInWeek[a]+1;
}
this.weekDays.push(_35d.DaysInWeek[a]);
}
}
if(_35d.Month){
this.month=_35d.Month;
}
if(_35d.DaysOfMonth){
if(_35d.DaysOfMonth.Day){
if(_35d.DaysOfMonth.Day==6){
_35d.DaysOfMonth.Day=0;
}else{
_35d.DaysOfMonth.Day=_35d.DaysOfMonth.Day+1;
}
this.daysOfMonth.day=_35d.DaysOfMonth.Day;
}
if(_35d.DaysOfMonth.WeekNum){
this.daysOfMonth.weekInMonth=_35d.DaysOfMonth.WeekNum;
}
}
if(_35d.MonthDays){
this.monthDates=[];
for(var i=0;i<_35d.MonthDays.length;i++){
this.monthDates.push(_35d.MonthDays[i]-1);
}
}
};
function __sp_device_calendar_entry(_361){
if(_361.id){
this.id=_361.id;
}
if(_361.type){
this.type=_361.Type;
}
if(_361.Summary){
this.summary=_361.Summary;
}
if(_361.Description){
this.description=_361.Description;
}
if(_361.Location){
this.location=_361.Location;
}
if(_361.InstanceStartTime){
this.instanceStartTime=_361.InstanceStartTime;
}
if(_361.Priority>=0||_361.Priority<=255){
this.priority=_361.Priority;
}
if(_361.Status){
this.status=_361.Status;
}
if(_361.ExDates){
this.exceptionDates=_361.ExDates;
}
if(_361.RepeatRule){
this.repeatRule=new __sp_calendar_getList_repeatRule(_361.RepeatRule);
}
if(dataGetList==0){
this.time=new __sp_calendar_entry_time(_361.InstanceStartTime,_361.InstanceEndTime,_361.AlarmTime);
}else{
this.time=new __sp_calendar_entry_time(_361.StartTime,_361.EndTime,_361.AlarmTime);
}
};
function __sp_daysOfMonth_build(_362){
if(_362.day){
if(_362.day==0){
_362.day=6;
}else{
_362.day=_362.day-1;
}
this.Day=_362.day;
}
if(_362.weekInMonth){
this.WeekNum=_362.weekInMonth;
}
};
function __sp_calendar_addEntry_repeatRule(_363,str){
try{
if(!(_363.frequency)){
throw new DeviceException(this.error.MISSING_ARG_ERR,"Calendar: addEntry: frequency is missing");
}else{
var _365=_363.frequency;
switch(_365){
case "daily":
this.Type=1;
break;
case "weekly":
this.Type=2;
break;
case "monthly":
this.Type=3;
break;
case "yearly":
this.Type=4;
break;
default:
throw new DeviceException(this.error.INVALID_ARG_ERR,"Calendar: "+str+" Repeat Rule Type is Invalid");
}
if(_363.startDate){
this.StartDate=_363.startDate;
}
if(_363.untilDate){
this.UntilDate=_363.untilDate;
}
if(_363.interval){
this.Interval=_363.interval;
}
if(_363.weekDays){
this.DaysInWeek=[];
for(var a in _363.weekDays){
if(_363.weekDays[a]==0){
_363.weekDays[a]=6;
}else{
_363.weekDays[a]=_363.weekDays[a]-1;
}
this.DaysInWeek.push(_363.weekDays[a]);
}
}
if(_363.month){
this.Month=_363.month;
}
if(_363.monthDates){
this.MonthDays=[];
for(var i=0;i<_363.monthDates.length;i++){
this.MonthDays.push(_363.monthDates[i]-1);
}
}
if(_363.daysOfMonth){
this.DaysOfMonth=new Array();
for(var a in _363.daysOfMonth){
var _368=new __sp_daysOfMonth_build(_363.daysOfMonth[a]);
(this.DaysOfMonth).push(_368);
}
}
}
}
catch(e){
__device_handle_exception(e,"__sp_calendar_addEntry_repeatRule: "+e);
}
};
function __sp_calendar_entry(_369,str){
try{
if(_369.type){
this.Type=_369.type;
}
if(_369.id){
this.id=_369.id;
if(isUpdate){
if(_369.time){
if(_369.time.begin){
this.StartTime=_369.time.begin;
}
if(_369.time.end){
this.EndTime=_369.time.end;
}
}
}
}
if(_369.instanceStartTime){
this.InstanceStartTime=_369.instanceStartTime;
}
if(_369.description){
this.Description=_369.description;
}else{
if(isUpdate&&(_369.description==null)){
this.Description=" ";
}
}
if(_369.summary){
this.Summary=_369.summary;
}else{
if(isUpdate&&(_369.summary==null)){
this.Summary=" ";
}
}
if(_369.location){
this.Location=_369.location;
}else{
if(isUpdate&&(_369.location==null)){
this.Location=" ";
}
}
if(_369.priority){
if((_369.priority<0)||(_369.priority>255)){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Calendar: "+str+" Priority is Invalid");
}else{
this.Priority=_369.priority;
}
}else{
if(isUpdate&&(_369.priority==null)){
this.Priority=0;
}
}
if(_369.status){
if(this.Type=="ToDo"){
this.Status="Todo"+_369.status;
}else{
this.Status=_369.status;
}
}else{
if(isUpdate&&(_369.status==null)){
this.Status="Tentative";
}
}
if(_369.exceptionDates){
this.ExDates=_369.exceptionDates;
}
if(_369.repeatRule){
this.RepeatRule=new __sp_calendar_addEntry_repeatRule(_369.repeatRule,str);
}
if(_369.type!=undefined&&_369.type!=null){
if(typeof this.Type!="string"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Calendar: "+str+" Type is not a string");
}
switch(this.Type){
case "Meeting":
if(_369.time){
if(_369.time.begin){
this.StartTime=_369.time.begin;
}
if(_369.time.end){
this.EndTime=_369.time.end;
}
}
break;
case "Reminder":
case "Anniversary":
if(_369.time){
if(_369.time.begin){
this.StartTime=_369.time.begin;
}
}
break;
case "ToDo":
if(_369.time){
if(_369.time.end){
this.EndTime=_369.time.end;
}
}
break;
case "DayEvent":
if(_369.time){
if(_369.time.begin){
this.StartTime=_369.time.begin;
}
}
break;
default:
throw new DeviceException(this.error.INVALID_ARG_ERR,"Calendar: "+str+" Type is Invalid");
}
}
if(_369.time){
if(_369.time.alarm){
this.AlarmTime=_369.time.alarm;
}
}
}
catch(e){
__device_handle_exception(e,"__sp_calendar_entry: "+e);
}
};
function __sp_calendar_iterator_get_next(){
var _36b=this.iter.getNext();
if(typeof _36b=="undefined"){
return null;
}
var _36c=new __sp_device_calendar_entry(_36b);
_36b.close();
return _36c;
};
function __sp_calendar_iterator(_36d){
this.iter=_36d;
this.next=__sp_calendar_iterator_get_next;
this.close=function(){
this.iter.close();
};
};
var CALENDAR_APP_ID=268458241;
function __sp_calendar_startEditor(_36e,_36f,_370){
try{
if(!_36e){
throw new DeviceException(this.error.MISSING_ARG_ERR,"Calendar: startEditor: callback is missing");
}else{
if(typeof _36e!="function"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Calendar: startEditor: callback is invalid");
}
}
if(_370){
if(typeof _370!="function"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Calendar: startEditor: error callback is invalid");
}
}
if(_36f==null||_36f==undefined){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Calendar: startEditor: entry is invalid");
}
var _371=function(arg1,arg2,arg3){
var iter=null;
_36e(iter);
if(arg2!=event_cancelled){
var iter=null;
if(arg3.ReturnValue){
iter=new __sp_calendar_iterator(arg3.ReturnValue);
}
_36e(iter);
}
if(arg3.ErrorCode!=0){
switch(arg3.ErrorCode){
case this.error.MISSING_ARG_ERR:
case this.error.INVALID_ARG_ERR:
case this.error.NOT_SUPPORTED_ERR:
if(arg3.ErrorMessage){
var _376=splitErrorMessage(arg3.ErrorMessage);
throw new DeviceException(MapErrorCode[arg3.ErrorCode],"Calendar: startEditor: "+_376);
}else{
throw new DeviceException(MapErrorCode[arg3.ErrorCode],"Calendar: startEditor: Operation Failed");
}
break;
default:
_370(new DeviceException(MapErrorCode[arg3.ErrorCode],"Calendar: startEditor: Operation Failed"));
}
}
};
__s60_start_and_wait(CALENDAR_APP_ID,"",_371);
return 0;
}
catch(e){
__device_handle_exception(e,"__sp_calendar_startEditor: "+e);
}
};
var __sp_calendar_entry_types="MeetingReminderToDoAnniversaryDayEvent";
function __sp_calendar_getList_cb(arg1,arg2,arg3){
var _37a;
var _37b;
var _37c;
_37a=glob_obj.getFromArray(arg1);
if(_37a){
_37b=_37a.success_cb;
_37c=_37a.error_cb;
}else{
alert("Calendar: __sp_calendar_getList_cb: Callback not found ");
return;
}
if(arg3.ErrorCode!=0){
_37c(new DeviceException(arg3.ErrorCode,"Calendar: getList: Operation Failed"));
return;
}
if(arg2!=event_cancelled){
var iter=null;
if(arg3.ReturnValue){
iter=new __sp_calendar_iterator(arg3.ReturnValue);
}
_37b(iter);
}
glob_obj.removeFromArray(arg1);
};
function __sp_calendar_getList(_37e,_37f,_380){
try{
if(_37f){
if(typeof _37f!="object"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Calendar: getList: match is invalid");
}
if(_37f.id){
dataGetList=1;
if(typeof _37f.id!="string"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Calendar: getList: match is invalid");
}
}else{
dataGetList=0;
}
}
if(!_37e){
throw new DeviceException(this.error.MISSING_ARG_ERR,"Calendar: getList: callback is missing");
}else{
if(typeof _37e!="function"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Calendar: getList: callback is invalid");
}
}
if(_380){
if(typeof _380!="function"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Calendar: getList: error callback is invalid");
}
if(_380==undefined||_380==null){
throw new DeviceException(this.error.MISSING_ARG_ERR,"Calendar: getList: error callback is missing");
}
}
var _381={};
modifyObjectBaseProp(_381);
_381.Type="IncludeAll";
if(_37f){
if(_37f.id){
_381.id=_37f.id;
}
if((_37f.type)&&__sp_calendar_entry_types.match(_37f.type)){
_381.Type=_37f.type;
}else{
if((_37f.type)&&typeof _37f.type!="string"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Calendar: getList: match is invalid");
}
}
if(_37f.range){
if(_37f.range.begin){
if(typeof (_37f.range.begin)!="object"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Calendar: getList: match is invalid");
}else{
if((_37f.range.begin)=="Invalid Date"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Calendar: getList: match is invalid");
}else{
_381.StartRange=_37f.range.begin;
}
}
}
if(_37f.range.end){
if(typeof (_37f.range.end)!="object"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Calendar: getList: match is invalid");
}else{
if((_37f.range.end)=="Invalid Date"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Calendar: getList: match is invalid");
}else{
_381.EndRange=_37f.range.end;
}
}
}
if((_37f.range.begin)&&(_37f.range.end)){
if((_37f.range.begin)>(_37f.range.end)){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Calendar: getList: match is invalid");
}
}
}
if(_37f.text){
if(typeof (_37f.text)!="string"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Calendar: getList: match is invalid");
}else{
_381.SearchText=_37f.text;
}
}
}
var _382={};
modifyObjectBaseProp(_382);
_382.Type="CalendarEntry";
_382.Filter=_381;
temp_scb=_37e;
temp_ecb=_380;
var rval=this.so.IDataSource.GetList(_382,this.getListCb);
if(rval.TransactionID){
glob_obj.addToGlobalArray(rval.TransactionID,_37e,_380);
}
if(_382){
delete _382.Type;
delete _382.Filter;
}
if(rval.ErrorCode!=0){
switch(rval.ErrorCode){
case this.error.MISSING_ARG_ERR:
case this.error.INVALID_ARG_ERR:
case this.error.NOT_SUPPORTED_ERR:
if(rval.ErrorMessage){
var _384=splitErrorMessage(rval.ErrorMessage);
throw new DeviceException(MapErrorCode[rval.ErrorCode],"Calendar: getList: "+_384);
}else{
throw new DeviceException(MapErrorCode[rval.ErrorCode],"Calendar: getList: Operation Failed");
}
break;
default:
_380(new DeviceException(MapErrorCode[rval.ErrorCode],"Calendar: getList: Operation Failed"));
}
}
return rval.TransactionID;
}
catch(e){
__device_handle_exception(e,"sp_calendar_getList: "+e);
}
};
function __sp_calendar_add(_385){
if(_385){
if(typeof _385!="object"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Calendar: addEntry: calendarEntry param is invalid");
}
if(_385.id){
_385.id=undefined;
}
if(!_385.type||!_385.time){
throw new DeviceException(this.error.MISSING_ARG_ERR,"Calendar: addEntry: mandatory param missing");
}else{
if(typeof _385.type!="string"||typeof _385.time!="object"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Calendar: addEntry: mandatory param missing");
}
}
if((_385.type!="ToDo")&&!_385.time.begin){
throw new DeviceException(this.error.MISSING_ARG_ERR,"Calendar: addEntry: mandatory param StartTime missing");
}
if(!_385.time.end&&(_385.type=="ToDo"||_385.type=="Meeting")){
throw new DeviceException(this.error.MISSING_ARG_ERR,"Calendar: addEntry: mandatory param EndTime missing");
}
if(_385.time.end&&_385.time.alarm){
if(_385.time.end<_385.time.alarm){
throw new DeviceException(this.error.NOT_SUPPORTED_ERR,"Calendar: addEntry: alarm time greater than end time:Not supported");
}
}
if(_385.type=="ToDo"){
if(_385.status==0){
if(typeof (_385.status)!="string"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Calendar: addEntry: mandatory param missing");
}
}
}
if(_385.repeatRule){
if(typeof _385.repeatRule!="object"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Calendar: addEntry: repeatRule param type is invalid");
}
if(!_385.repeatRule.frequency||_385.repeatRule.frequency==null){
throw new DeviceException(this.error.MISSING_ARG_ERR,"Calendar: addEntry: mandatory param Frequency missing");
}
}
var _386=__sp_calendar_isInputValid(_385);
if(!_386){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Calendar: addEntry: calendarEntry param is invalid");
}
}else{
throw new DeviceException(this.error.MISSING_ARG_ERR,"Calendar: addEntry: mandatory param missing");
}
try{
var str="addEntry:";
var _388={};
modifyObjectBaseProp(_388);
_388.Type="CalendarEntry";
_388.Item=new __sp_calendar_entry(_385,str);
var _389=this.so.IDataSource.Add(_388);
if(_388){
delete _388.Type;
delete _388.Item;
}
var _38a="Operation Failed";
if(_389.ErrorMessage){
_38a=splitErrorMessage(_389.ErrorMessage);
}
if(_389.ErrorCode!=0){
throw new DeviceException(MapErrorCode[_389.ErrorCode],"Calendar: addEntry: Operation Failed");
return;
}else{
var _38b=_389.ReturnValue;
return _38b;
}
}
catch(e){
__device_handle_exception(e,"__sp_calendar_add: "+e);
}
};
function __sp_calendar_update(_38c){
isUpdate=1;
if(_38c){
if(typeof _38c!="object"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Calendar: updateEntry: calendarEntry param is invalid");
}
if(!_38c.id){
throw new DeviceException(this.error.MISSING_ARG_ERR,"Calendar: updateEntry: mandatory param - Id missing");
}
if(_38c.repeatRule){
if(typeof _38c.repeatRule!="object"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Calendar: updateEntry: repeatRule param type is invalid");
}
if((_38c.repeatRule.frequency==null||_38c.repeatRule.frequency==undefined)){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Calendar: updateEntry: repeatRule param type is invalid");
}
if(_38c.repeatRule.startDate&&(_38c.repeatRule.startDate==null||_38c.repeatRule.startDate==undefined)){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Calendar: updateEntry: repeatRule param type is invalid");
}
if(_38c.repeatRule.untilDate&&(_38c.repeatRule.untilDate==null||_38c.repeatRule.untilDate==undefined)){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Calendar: updateEntry: repeatRule param type is invalid");
}
}
if(_38c.time){
if(_38c.time.end&&_38c.time.alarm){
if(_38c.time.alarm>_38c.time.end){
throw new DeviceException(this.error.NOT_SUPPORTED_ERR,"Calendar: updateEntry: alarm time greater than end time is not supported");
}
}
}
var _38d=__sp_calendar_isInputValid(_38c);
if(!_38d){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Calendar: updateEntry: calendarEntry param is invalid");
}
}else{
throw new DeviceException(this.error.MISSING_ARG_ERR,"Calendar: updateEntry: mandatory param missing");
}
try{
var str="updateEntry:";
var _38f={};
modifyObjectBaseProp(_38f);
_38f.Type="CalendarEntry";
_38f.Item=new __sp_calendar_entry(_38c,str);
isUpdate=0;
var _390=this.so.IDataSource.Add(_38f);
if(_38f){
delete _38f.Type;
delete _38f.Item;
}
var _391="Operation Failed";
if(_390.ErrorMessage){
_391=splitErrorMessage(_390.ErrorMessage);
}
if(_390.ErrorCode!=0){
throw new DeviceException(MapErrorCode[_390.ErrorCode],"Calendar: addEntry: Operation Failed");
return;
}else{
var _392=_390.ReturnValue;
return _392;
}
}
catch(e){
__device_handle_exception(e,"__sp_calendar_add: "+e);
}
};
function __sp_calendar_delete(data){
try{
if(data){
if(typeof data!="object"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Calendar: deleteEntry: data is invalid");
}
if(!data.id){
throw new DeviceException(this.error.MISSING_ARG_ERR,"Calendar: deleteEntry: id is missing");
}
var _394=__sp_calendar_isInputValid(data);
if(!_394){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Calendar: deleteEntry: delete data is invalid");
}
}else{
throw new DeviceException(this.error.MISSING_ARG_ERR,"Calendar: deleteEntry: data is missing");
}
var _395={};
modifyObjectBaseProp(_395);
_395.Type="CalendarEntry";
_395.Data={};
modifyObjectBaseProp(_395.Data);
_395.Data.IdList=[];
var list=[data.id];
_395.Data.IdList=list;
if(data.range){
if(data.range.begin){
_395.Data.StartRange=data.range.begin;
}
if(data.range.end){
_395.Data.EndRange=data.range.end;
}
}
var rval=this.so.IDataSource.Delete(_395);
if(_395){
delete _395.Type;
delete _395.Data.IdList;
delete _395.Data.StartRange;
delete _395.Data.EndRange;
}
if(list){
delete list.id;
}
if(rval.ErrorCode!=0){
if(rval.ErrorMessage){
var _398=splitErrorMessage(rval.ErrorMessage);
throw new DeviceException(MapErrorCode[rval.ErrorCode],"Calendar: deleteEntry: "+_398);
}else{
throw new DeviceException(MapErrorCode[rval.ErrorCode],"Calendar: deleteEntry: Operation Failed");
}
}
}
catch(e){
__device_handle_exception(e,"__sp_calendar_delete: "+e);
}
};
function __sp_calendar_cancel(_399){
try{
if(!_399||_399==null||_399==undefined){
throw new DeviceException(this.error.MISSING_ARG_ERR,"Calendar: cancel: id is missing");
}
if(_399){
if(typeof _399!="number"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Calendar: cancel: id is missing");
}
}
var _39a={};
modifyObjectBaseProp(_39a);
_39a.TransactionID=_399;
var _39b=this.so.IDataSource.Cancel(_39a);
if(_39a){
delete _39a.TransactionID;
}
if(_39b.ErrorCode!=0){
if(_39b.ErrorMessage){
var _39c=splitErrorMessage(_39b.ErrorMessage);
throw new DeviceException(MapErrorCode[_39b.ErrorCode],"Calendar: cancel: "+_39c);
}else{
throw new DeviceException(MapErrorCode[_39b.ErrorCode],"Calendar: cancel: Operation Failed");
}
}
}
catch(e){
__device_handle_exception(e,"__sp_calendar_cancel: "+e);
}
};
function __sp_calendar_instance(){
this.descriptor=new __sp_calendar_descriptor();
this.startEditor=__sp_calendar_startEditor;
this.getList=__sp_calendar_getList;
this.getListCb=__sp_calendar_getList_cb;
this.addEntry=__sp_calendar_add;
this.updateEntry=__sp_calendar_update;
this.deleteEntry=__sp_calendar_delete;
this.cancel=__sp_calendar_cancel;
this.error=new DeviceException(0,"Dummy");
this.so=null;
try{
this.so=device.getServiceObject("Service.Calendar","IDataSource");
}
catch(e){
__device_handle_exception(e,"Calendar service not available");
}
};
function __device_contacts_descriptor(_39d){
this.interfaceName=_39d.interfaceName;
this.version=_39d.version;
};
function __device_contacts_startEditor(_39e,_39f,_3a0){
return this.provider.startEditor(_39e,_39f,_3a0);
};
function __device_contacts_getContacts(_3a1,_3a2,_3a3,_3a4){
return this.provider.getContacts(_3a1,_3a2,_3a3,_3a4);
};
function __device_contacts_add(_3a5){
return this.provider.addContact(_3a5);
};
function __device_contacts_update(_3a6){
this.provider.updateContact(_3a6);
};
function __device_contacts_delete(id){
this.provider.deleteContacts(id);
};
function __device_contacts_getContactInfo(id){
return this.provider.getContactInfo(id);
};
function __device_contacts_addGroup(_3a9){
return this.provider.addGroup(_3a9);
};
function __device_contacts_getGroups(_3aa,_3ab){
return this.provider.getGroups(_3aa,_3ab);
};
function __device_contacts_deleteGroups(id){
this.provider.deleteGroups(id);
};
function __device_contacts_addContactsToGroup(_3ad,id){
this.provider.addContactsToGroup(_3ad,id);
};
function __device_contacts_getContactIds(_3af,_3b0,_3b1,_3b2){
return this.provider.getContactIds(_3af,_3b0,_3b1,_3b2);
};
function __device_contacts_getGroupIds(_3b3,_3b4){
return this.provider.getGroupIds(_3b3,_3b4);
};
function __device_contacts_removeContactsFromGroup(_3b5,id){
this.provider.removeContactsFromGroup(_3b5,id);
};
function __device_contacts_cancel(_3b7){
this.provider.cancel(_3b7);
};
function __device_contacts_updateGroup(_3b8){
this.provider.updateGroup(_3b8);
};
function __device_contacts_getGroupInfo(_3b9){
return this.provider.getGroupInfo(_3b9);
};
function __device_contacts(_3ba){
this.provider=_3ba;
this.interfaceName=_3ba.descriptor.interfaceName;
this.version=_3ba.descriptor.version;
this.SORT_ASCENDING=0;
this.SORT_DESCENDING=1;
this.startEditor=__device_contacts_startEditor;
this.getContacts=__device_contacts_getContacts;
this.addContact=__device_contacts_add;
this.updateContact=__device_contacts_update;
this.deleteContacts=__device_contacts_delete;
this.getContactInfo=__device_contacts_getContactInfo;
this.addGroup=__device_contacts_addGroup;
this.getGroups=__device_contacts_getGroups;
this.deleteGroups=__device_contacts_deleteGroups;
this.addContactsToGroup=__device_contacts_addContactsToGroup;
this.getContactIds=__device_contacts_getContactIds;
this.getGroupIds=__device_contacts_getGroupIds;
this.removeContactsFromGroup=__device_contacts_removeContactsFromGroup;
this.cancel=__device_contacts_cancel;
this.updateGroup=__device_contacts_updateGroup;
this.getGroupInfo=__device_contacts_getGroupInfo;
};
var __device_contacts_service_entry={"name":null,"version":null,"proto":__device_contacts,"descriptor":__device_contacts_descriptor,"providers":[{"descriptor":__sp_contacts_descriptor,"instance":__sp_contacts_instance}]};
nokia.device.contacts.SORT_ASCENDING=0;
nokia.device.contacts.SORT_DESCENDING=1;
function __sp_contacts_descriptor(){
this.interfaceName="contacts";
if(window.__Service_Interface_Ver){
this.version=__Service_Interface_Ver;
}else{
this.version=1;
}
};
function __s60_enumerate_contact_object(_3bb,_3bc,func,_3be){
try{
var key;
for(key in _3bb){
var _3c0;
if(_3bc){
_3c0=_3bc+"."+key;
}else{
_3c0=key;
}
var _3c1=_3bb[key];
if(_3c1 instanceof Array){
func(_3c0,_3c1,_3be);
}else{
if(_3c1 instanceof Date){
func(_3c0,_3c1,_3be);
}else{
if(typeof _3c1=="object"){
__s60_enumerate_contact_object(_3c1,_3c0,func,_3be);
}else{
func(_3c0,_3c1,_3be);
}
}
}
}
}
catch(e){
throw e;
}
};
function __sp_contact_extract(name,_3c3,_3c4){
switch(name){
case "name.last":
_3c4.LastName={};
modifyObjectBaseProp(_3c4.LastName);
_3c4.LastName.Label="Last name";
_3c4.LastName.Value=_3c3;
break;
case "name.first":
_3c4.FirstName={};
modifyObjectBaseProp(_3c4.FirstName);
_3c4.FirstName.Label="First name";
_3c4.FirstName.Value=_3c3;
break;
case "name.middle":
_3c4.MiddleName={};
modifyObjectBaseProp(_3c4.MiddleName);
_3c4.MiddleName.Label="Middle name";
_3c4.MiddleName.Value=_3c3;
break;
case "name.prefix":
_3c4.Prefix={};
modifyObjectBaseProp(_3c4.Prefix);
_3c4.Prefix.Label="Prefix";
_3c4.Prefix.Value=_3c3;
break;
case "name.suffix":
_3c4.Suffix={};
modifyObjectBaseProp(_3c4.Suffix);
_3c4.Suffix.Label="Suffix";
_3c4.Suffix.Value=_3c3;
break;
case "tel.land":
_3c4.LandPhoneGen={};
modifyObjectBaseProp(_3c4.LandPhoneGen);
_3c4.LandPhoneGen.Label="Landline";
_3c4.LandPhoneGen.Value=_3c3;
break;
case "tel.mobile":
_3c4.MobilePhoneGen={};
modifyObjectBaseProp(_3c4.MobilePhoneGen);
_3c4.MobilePhoneGen.Label="Mobile";
_3c4.MobilePhoneGen.Value=_3c3;
break;
case "tel.video":
_3c4.VideoNumberGen={};
modifyObjectBaseProp(_3c4.VideoNumberGen);
_3c4.VideoNumberGen.Label="Video";
_3c4.VideoNumberGen.Value=_3c3;
break;
case "tel.fax":
_3c4.FaxNumberGen={};
modifyObjectBaseProp(_3c4.FaxNumberGen);
_3c4.FaxNumberGen.Label="Fax";
_3c4.FaxNumberGen.Value=_3c3;
break;
case "tel.voip":
_3c4.VOIPGen={};
modifyObjectBaseProp(_3c4.VOIPGen);
_3c4.VOIPGen.Label="Voip";
_3c4.VOIPGen.Value=_3c3;
break;
case "tel.home.land":
_3c4.LandPhoneHome={};
modifyObjectBaseProp(_3c4.LandPhoneHome);
_3c4.LandPhoneHome.Label="Home Landline";
_3c4.LandPhoneHome.Value=_3c3;
break;
case "tel.home.mobile":
_3c4.MobilePhoneHome={};
modifyObjectBaseProp(_3c4.MobilePhoneHome);
_3c4.MobilePhoneHome.Label="Home Mobile";
_3c4.MobilePhoneHome.Value=_3c3;
break;
case "tel.home.video":
_3c4.VideoNumberHome={};
modifyObjectBaseProp(_3c4.VideoNumberHome);
_3c4.VideoNumberHome.Label="Home Video";
_3c4.VideoNumberHome.Value=_3c3;
break;
case "tel.home.fax":
_3c4.FaxNumberHome={};
modifyObjectBaseProp(_3c4.FaxNumberHome);
_3c4.FaxNumberHome.Label="Home Fax";
_3c4.FaxNumberHome.Value=_3c3;
break;
case "tel.home.voip":
_3c4.VoipHome={};
modifyObjectBaseProp(_3c4.VoipHome);
_3c4.VoipHome.Label="Home Voip";
_3c4.VoipHome.Value=_3c3;
break;
case "tel.work.land":
_3c4.LandPhoneWork={};
modifyObjectBaseProp(_3c4.LandPhoneWork);
_3c4.LandPhoneWork.Label="Work Landline";
_3c4.LandPhoneWork.Value=_3c3;
break;
case "tel.work.mobile":
_3c4.MobilePhoneWork={};
modifyObjectBaseProp(_3c4.MobilePhoneWork);
_3c4.MobilePhoneWork.Label="Work Mobile";
_3c4.MobilePhoneWork.Value=_3c3;
break;
case "tel.work.video":
_3c4.VideoNumberWork={};
modifyObjectBaseProp(_3c4.VideoNumberWork);
_3c4.VideoNumberWork.Label="Work Video";
_3c4.VideoNumberWork.Value=_3c3;
break;
case "tel.work.fax":
_3c4.FaxNumberWork={};
modifyObjectBaseProp(_3c4.FaxNumberWork);
_3c4.FaxNumberWork.Label="Work Fax";
_3c4.FaxNumberWork.Value=_3c3;
break;
case "tel.work.voip":
_3c4.VoipWork={};
modifyObjectBaseProp(_3c4.VoipWork);
_3c4.VoipWork.Label="Work Voip";
_3c4.VoipWork.Value=_3c3;
break;
case "address.street":
_3c4.AddrStreetGen={};
modifyObjectBaseProp(_3c4.AddrStreetGen);
_3c4.AddrStreetGen.Label="Street Address";
_3c4.AddrStreetGen.Value=_3c3;
break;
case "address.local":
_3c4.AddrLocalGen={};
modifyObjectBaseProp(_3c4.AddrLocalGen);
_3c4.AddrLocalGen.Label="City";
_3c4.AddrLocalGen.Value=_3c3;
break;
case "address.region":
_3c4.AddrRegionGen={};
modifyObjectBaseProp(_3c4.AddrRegionGen);
_3c4.AddrRegionGen.Label="State/Province";
_3c4.AddrRegionGen.Value=_3c3;
break;
case "address.code":
_3c4.AddrPostCodeGen={};
modifyObjectBaseProp(_3c4.AddrPostCodeGen);
_3c4.AddrPostCodeGen.Label="Postal code";
_3c4.AddrPostCodeGen.Value=_3c3;
break;
case "address.country":
_3c4.AddrCountryGen={};
modifyObjectBaseProp(_3c4.AddrCountryGen);
_3c4.AddrCountryGen.Label="Country";
_3c4.AddrCountryGen.Value=_3c3;
break;
case "address.email":
_3c4.EmailGen={};
modifyObjectBaseProp(_3c4.EmailGen);
_3c4.EmailGen.Label="EMail";
_3c4.EmailGen.Value=_3c3;
break;
case "address.uri":
_3c4.URLGen={};
modifyObjectBaseProp(_3c4.URLGen);
_3c4.URLGen.Label="Website";
_3c4.URLGen.Value=_3c3;
break;
case "address.home.street":
_3c4.AddrStreetHome={};
modifyObjectBaseProp(_3c4.AddrStreetHome);
_3c4.AddrStreetHome.Label="Home Address";
_3c4.AddrStreetHome.Value=_3c3;
break;
case "address.home.local":
_3c4.AddrLocalHome={};
modifyObjectBaseProp(_3c4.AddrLocalHome);
_3c4.AddrLocalHome.Label="City";
_3c4.AddrLocalHome.Value=_3c3;
break;
case "address.home.region":
_3c4.AddrRegionHome={};
modifyObjectBaseProp(_3c4.AddrRegionHome);
_3c4.AddrRegionHome.Label="State/Province";
_3c4.AddrRegionHome.Value=_3c3;
break;
case "address.home.code":
_3c4.AddrPostCodeHome={};
modifyObjectBaseProp(_3c4.AddrPostCodeHome);
_3c4.AddrPostCodeHome.Label="Postal code";
_3c4.AddrPostCodeHome.Value=_3c3;
break;
case "address.home.country":
_3c4.AddrCountryHome={};
modifyObjectBaseProp(_3c4.AddrCountryHome);
_3c4.AddrCountryHome.Label="Country";
_3c4.AddrCountryHome.Value=_3c3;
break;
case "address.home.email":
_3c4.EmailHome={};
modifyObjectBaseProp(_3c4.EmailHome);
_3c4.EmailHome.Label="Home EMail";
_3c4.EmailHome.Value=_3c3;
break;
case "address.home.uri":
_3c4.URLHome={};
modifyObjectBaseProp(_3c4.URLHome);
_3c4.URLHome.Label="Home Website";
_3c4.URLHome.Value=_3c3;
break;
case "address.work.street":
_3c4.AddrStreetWork={};
modifyObjectBaseProp(_3c4.AddrStreetWork);
_3c4.AddrStreetWork.Label="Work Address";
_3c4.AddrStreetWork.Value=_3c3;
break;
case "address.work.local":
_3c4.AddrLocalWork={};
modifyObjectBaseProp(_3c4.AddrLocalWork);
_3c4.AddrLocalWork.Label="City";
_3c4.AddrLocalWork.Value=_3c3;
break;
case "address.work.region":
_3c4.AddrRegionWork={};
modifyObjectBaseProp(_3c4.AddrRegionWork);
_3c4.AddrRegionWork.Label="State/Province";
_3c4.AddrRegionWork.Value=_3c3;
break;
case "address.work.code":
_3c4.AddrPostCodeWork={};
modifyObjectBaseProp(_3c4.AddrPostCodeWork);
_3c4.AddrPostCodeWork.Label="Postal code";
_3c4.AddrPostCodeWork.Value=_3c3;
break;
case "address.work.country":
_3c4.AddrCountryWork={};
modifyObjectBaseProp(_3c4.AddrCountryWork);
_3c4.AddrCountryWork.Label="Country";
_3c4.AddrCountryWork.Value=_3c3;
break;
case "address.work.email":
_3c4.EmailWork={};
modifyObjectBaseProp(_3c4.EmailWork);
_3c4.EmailWork.Label="Work EMail";
_3c4.EmailWork.Value=_3c3;
break;
case "address.work.uri":
_3c4.URLWork={};
modifyObjectBaseProp(_3c4.URLWork);
_3c4.URLWork.Label="Work Website";
_3c4.URLWork.Value=_3c3;
break;
case "company.name":
_3c4.CompanyName={};
modifyObjectBaseProp(_3c4.CompanyName);
_3c4.CompanyName.Label="Company";
_3c4.CompanyName.Value=_3c3;
break;
case "company.title":
_3c4.JobTitle={};
modifyObjectBaseProp(_3c4.JobTitle);
_3c4.JobTitle.Label="Title";
_3c4.JobTitle.Value=_3c3;
break;
case "id":
_3c4.id=_3c3;
break;
case "notes":
_3c4.Note={};
modifyObjectBaseProp(_3c4.Note);
_3c4.Note.Label="Note";
_3c4.Note.Value=_3c3;
break;
case "anniversary":
_3c4.Anniversary={};
modifyObjectBaseProp(_3c4.Anniversary);
_3c4.Anniversary.Label="Anniversary";
_3c4.Anniversary.Value=_3c3;
break;
case "birthday":
_3c4.Date={};
modifyObjectBaseProp(_3c4.Date);
_3c4.Date.Label="BirthDay";
_3c4.Date.Value=_3c3;
break;
case "nickName":
_3c4.SecondName={};
modifyObjectBaseProp(_3c4.SecondName);
_3c4.SecondName.Label="NickName";
_3c4.SecondName.Value=_3c3;
break;
case "photo":
_3c4.CallerObjImg={};
modifyObjectBaseProp(_3c4.CallerObjImg);
_3c4.CallerObjImg.Label="CallerObjImg";
_3c4.CallerObjImg.Value=_3c3;
break;
case "xspid":
_3c4.IMPP={};
modifyObjectBaseProp(_3c4.IMPP);
_3c4.IMPP.Label="IMPP";
_3c4.IMPP.Value=_3c3;
break;
}
};
function __s60_enumerate_build_contact_object(_3c5,_3c6,func,_3c8){
var key;
for(key in _3c5){
var _3ca;
if(_3c6){
_3ca=_3c6+"."+key;
}else{
_3ca=key;
}
var _3cb=_3c5[key];
if(_3ca=="IMPP"){
func(_3ca,_3cb,_3c8);
}
if(typeof _3cb=="object"){
__s60_enumerate_build_contact_object(_3cb,_3ca,func,_3c8);
}else{
func(_3ca,_3cb,_3c8);
}
}
};
function __sp_device_contact_extract(name,_3cd,_3ce){
if(name=="id"){
_3ce.id=_3cd;
return;
}
if(!name.match(".Value")){
return;
}
try{
if(name.match("IMPP.Value.0")){
_3ce.xspid=[];
}
if(name.match("Name")){
if(name.match("CompanyName")){
if(!_3ce.company){
_3ce.company={};
}
}else{
if(!_3ce.name){
_3ce.name={};
}
}
}else{
if(name.match("Phone")||name.match("Number")||name.match("VOIP")||name.match("Voip")){
if(!_3ce.tel){
_3ce.tel={};
}
if(name.match("Home")){
if(!_3ce.tel.home){
_3ce.tel.home={};
}
}else{
if(name.match("Work")){
if(!_3ce.tel.work){
_3ce.tel.work={};
}
}
}
}else{
if(name.match("Addr")||name.match("Email")||name.match("URL")){
if(!_3ce.address){
_3ce.address={};
}
if(name.match("Home")){
if(!_3ce.address.home){
_3ce.address.home={};
}
}else{
if(name.match("Work")){
if(!_3ce.address.work){
_3ce.address.work={};
}
}
}
}else{
if(name.match("JobTitle")){
if(!_3ce.company){
_3ce.company={};
}
}
}
}
}
}
catch(e){
__device_handle_exception(e,"__sp_device_contact_extract: "+e);
}
if(name.match("IMPP.Value")){
var _3cf=name.split(".");
var _3d0=_3cf[2];
if(_3d0!=undefined){
_3ce.xspid[_3cf[2]]=_3cd;
return;
}
}
switch(name){
case "LastName.Value":
_3ce.name.last=_3cd;
break;
case "FirstName.Value":
_3ce.name.first=_3cd;
break;
case "MiddleName.Value":
_3ce.name.middle=_3cd;
break;
case "Prefix.Value":
_3ce.name.prefix=_3cd;
break;
case "Suffix.Value":
_3ce.name.suffix=_3cd;
break;
case "LandPhoneGen.Value":
_3ce.tel.land=_3cd;
break;
case "MobilePhoneGen.Value":
_3ce.tel.mobile=_3cd;
break;
case "VideoNumberGen.Value":
_3ce.tel.video=_3cd;
break;
case "FaxNumberGen.Value":
_3ce.tel.fax=_3cd;
break;
case "VOIPGen.Value":
_3ce.tel.voip=_3cd;
break;
case "LandPhoneHome.Value":
_3ce.tel.home.land=_3cd;
break;
case "MobilePhoneHome.Value":
_3ce.tel.home.mobile=_3cd;
break;
case "VideoNumberHome.Value":
_3ce.tel.home.video=_3cd;
break;
case "FaxNumberHome.Value":
_3ce.tel.home.fax=_3cd;
break;
case "VoipHome.Value":
_3ce.tel.home.voip=_3cd;
break;
case "LandPhoneWork.Value":
_3ce.tel.work.land=_3cd;
break;
case "MobilePhoneWork.Value":
_3ce.tel.work.mobile=_3cd;
break;
case "VideoNumberWork.Value":
_3ce.tel.work.video=_3cd;
break;
case "FaxNumberWork.Value":
_3ce.tel.work.fax=_3cd;
break;
case "VoipWork.Value":
_3ce.tel.work.voip=_3cd;
break;
case "AddrStreetGen.Value":
_3ce.address.street=_3cd;
break;
case "AddrLocalGen.Value":
_3ce.address.local=_3cd;
break;
case "AddrRegionGen.Value":
_3ce.address.region=_3cd;
break;
case "AddrPostCodeGen.Value":
_3ce.address.code=_3cd;
break;
case "AddrCountryGen.Value":
_3ce.address.country=_3cd;
break;
case "EmailGen.Value":
_3ce.address.email=_3cd;
break;
case "URLGen.Value":
_3ce.address.uri=_3cd;
break;
case "AddrStreetHome.Value":
_3ce.address.home.street=_3cd;
break;
case "AddrLocalHome.Value":
_3ce.address.home.local=_3cd;
break;
case "AddrRegionHome.Value":
_3ce.address.home.region=_3cd;
break;
case "AddrPostCodeHome.Value":
_3ce.address.home.code=_3cd;
break;
case "AddrCountryHome.Value":
_3ce.address.home.country=_3cd;
break;
case "EmailHome.Value":
_3ce.address.home.email=_3cd;
break;
case "URLHome.Value":
_3ce.address.home.uri=_3cd;
break;
case "AddrStreetWork.Value":
_3ce.address.work.street=_3cd;
break;
case "AddrLocalWork.Value":
_3ce.address.work.local=_3cd;
break;
case "AddrRegionWork.Value":
_3ce.address.work.region=_3cd;
break;
case "AddrPostCodeWork.Value":
_3ce.address.work.code=_3cd;
break;
case "AddrCountryWork.Value":
_3ce.address.work.country=_3cd;
break;
case "EmailWork.Value":
_3ce.address.work.email=_3cd;
break;
case "URLWork.Value":
_3ce.address.work.uri=_3cd;
break;
case "CompanyName.Value":
_3ce.company.name=_3cd;
break;
case "JobTitle.Value":
_3ce.company.title=_3cd;
break;
case "Note.Value":
_3ce.notes=_3cd;
break;
case "Anniversary.Value":
_3ce.anniversary=_3cd;
break;
case "Date.Value":
_3ce.birthday=_3cd;
break;
case "SecondName.Value":
_3ce.nickName=_3cd;
break;
case "CallerObjImg.Value":
_3ce.photo=_3cd;
break;
default:
}
};
function __sp_device_contact_build(_3d1,_3d2){
__s60_enumerate_build_contact_object(_3d1,null,__sp_device_contact_extract,_3d2);
};
function __sp_contact_iterator_get_next(){
var _3d3=this.iter.getNext();
if(typeof _3d3=="undefined"){
return null;
}
var rval={};
__sp_device_contact_build(_3d3,rval);
_3d3.close();
return rval;
};
function __sp_contact_iterator(_3d5){
this.iter=_3d5;
this.next=__sp_contact_iterator_get_next;
this.close=function(){
this.iter.close();
};
};
function __s60_enumerate_group_object(_3d6,func,_3d8){
var key;
for(key in _3d6){
var _3da=key;
var _3db=_3d6[key];
func(_3da,_3db,_3d8);
}
};
function __sp_device_groupinfo_extract(name,_3dd,_3de){
if(_3de.group==undefined){
_3de.group={};
}
if(name=="id"){
_3de.group.groupId=_3dd;
}else{
if(name=="GroupLabel"){
_3de.group.groupName=_3dd;
}else{
if(name=="Contents"){
_3de.contents=_3dd;
}
}
}
return;
};
function __sp_device_groupinfo_build(_3df,_3e0){
__s60_enumerate_group_object(_3df,__sp_device_groupinfo_extract,_3e0);
};
function __sp_device_group_extract(name,_3e2,_3e3){
if(name=="id"){
_3e3.groupId=_3e2;
return;
}
if(name=="GroupLabel"){
_3e3.groupName=_3e2;
return;
}
};
function __sp_device_group_build(_3e4,_3e5){
__s60_enumerate_object(_3e4,null,__sp_device_group_extract,_3e5);
};
function __sp_group_iterator_get_next(){
var _3e6=this.iter.getNext();
if(typeof _3e6=="undefined"){
return null;
}
var rval={};
__sp_device_group_build(_3e6,rval);
_3e6.close();
return rval;
};
function __sp_group_iterator(_3e8){
this.iter=_3e8;
this.next=__sp_group_iterator_get_next;
this.close=function(){
this.iter.close();
};
};
var CONTACTS_APP_ID=270486734;
function __sp_contacts_startEditor(_3e9,_3ea,_3eb){
if(!_3e9){
throw new DeviceException(this.error.MISSING_ARG_ERR,"Contacts: StartEditor:Missing Success Callback");
}
if((typeof _3e9)!="function"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Contacts: StartEditor:Invalid Success Callback");
}
if((_3ea)==null){
_3ea={};
}
if((typeof _3ea)=="undefined"){
_3ea={};
}
if((_3ea)==undefined){
_3ea={};
}
if((typeof _3ea)!="object"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Contacts: StartEditor:Invalid Contact Data");
}
if(_3eb){
if((typeof _3eb)!="function"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Contacts :StartEditor:Invalid Error Callback");
}
}
var _3ec=function(arg1,arg2,arg3){
var iter=null;
_3e9(iter);
};
__s60_start_and_wait(CONTACTS_APP_ID,"",_3ec);
return 0;
};
function __sp_contacts_getContacts_cb(arg1,arg2,arg3){
var iter=null;
var _3f5;
var _3f6;
var _3f7;
_3f7=glob_obj.getFromArray(arg1);
if(_3f7){
_3f5=_3f7.success_cb;
_3f6=_3f7.error_cb;
}else{
alert("Contacts: __sp_contacts_getContacts_cb : Callback not found ");
return;
}
if(arg3.ReturnValue){
iter=new __sp_contact_iterator(arg3.ReturnValue);
}else{
if(arg3.ErrorCode!=0){
var _3f8;
if(arg3.ErrorMessage){
_3f8=splitErrorMessage(arg3.ErrorMessage);
}else{
_3f8="Operation Failed";
}
_3f6(new DeviceException(MapErrorCode[arg3.ErrorCode],"Contacts: getContacts: "+_3f8));
return;
}
}
_3f5(iter);
glob_obj.removeFromArray(arg1);
};
function __sp_contacts_getContacts(_3f9,_3fa,_3fb,_3fc){
var _3fd={};
modifyObjectBaseProp(_3fd);
_3fd.Type="Contact";
if(_3fa){
_3fd.Filter={};
modifyObjectBaseProp(_3fd.Filter);
_3fd.Filter.SearchVal=_3fa;
}
if(_3fb!=null&&_3fb!=undefined){
_3fd.Sort={};
modifyObjectBaseProp(_3fd.Sort);
if(typeof _3fb=="number"){
if(_3fb==this.SORT_ASCENDING){
_3fd.Sort.Order="Ascending";
}else{
if(_3fb==this.SORT_DESCENDING){
_3fd.Sort.Order="Descending";
}else{
_3fc(new DeviceException(this.error.DATA_OUT_OF_RANGE_ERR,"Contacts: getContacts: invalid sortOrder input"));
return;
}
}
}else{
throw new DeviceException(this.error.INVALID_ARG_ERR,"Contacts: getContacts: invalid sortOrder input");
}
}
try{
if(!_3f9){
throw new DeviceException(this.error.MISSING_ARG_ERR,"Contacts: getContacts: callback is missing");
}else{
if(typeof _3f9!="function"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Contacts: getContacts: callback is invalid");
}
}
if(_3fc){
if(typeof (_3fc)!="function"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Contacts: getContacts: ErrorCallback is invalid");
}
}
temp_scb=_3f9;
temp_ecb=_3fc;
var rval=this.so.IDataSource.GetList(_3fd,this.getContactsCb);
if(rval.TransactionID){
glob_obj.addToGlobalArray(rval.TransactionID,_3f9,_3fc);
}
if(_3fd.Sort){
delete _3fd.Sort.Order;
}
if(_3fd.Filter){
delete _3fd.Filter.SearchVal;
}
if(_3fd){
delete _3fd.Type;
delete _3fd.Filter;
delete _3fd.Sort;
}
if(rval.ErrorCode!=0){
var _3ff=mappingVerification(rval.ErrorCode);
var _400=null;
if(rval.ErrorMessage){
_400=splitErrorMessage(rval.ErrorMessage);
}
if(_3ff){
switch(MapErrorCode[rval.ErrorCode]){
case this.error.MISSING_ARG_ERR:
case this.error.INVALID_ARG_ERR:
case this.error.NOT_SUPPORTED_ERR:
if(_400){
throw new DeviceException(MapErrorCode[rval.ErrorCode],"Contacts: getContacts: "+_400);
}else{
throw new DeviceException(MapErrorCode[rval.ErrorCode],"Contacts: getContacts:Operation Failed");
}
break;
default:
if(_3fc!=undefined){
if(_400){
_3fc(new DeviceException(MapErrorCode[rval.ErrorCode],"Contacts: getContacts: "+_400));
}else{
_3fc(new DeviceException(MapErrorCode[rval.ErrorCode],"Contacts: getContacts:Operation Failed "));
}
}else{
if(_400){
throw new DeviceException(MapErrorCode[rval.ErrorCode],"Contacts: getContacts: "+_400);
}else{
throw new DeviceException(MapErrorCode[rval.ErrorCode],"Contacts: getContacts:Operation Failed");
}
}
}
}else{
if(_3fc!=undefined){
if(_400){
_3fc(new DeviceException(rval.ErrorCode,"Contacts: getContacts: "+_400));
}else{
_3fc(new DeviceException(rval.ErrorCode,"getContacts:Operation Failed "));
}
}else{
if(_400){
throw new DeviceException(rval.ErrorCode,"Contacts: getContacts: "+_400);
}else{
throw new DeviceException(rval.ErrorCode,"Contacts: getContacts:Operation Failed");
}
}
}
}
return rval.TransactionID;
}
catch(e){
__device_handle_exception(e,"__sp_contacts_getContacts: "+e);
}
};
function __sp_contacts_add(_401){
if((_401)==null){
throw new DeviceException(this.error.MISSING_ARG_ERR,"addContact:Contact Data Needed");
}
if((typeof _401)=="undefined"){
throw new DeviceException(this.error.MISSING_ARG_ERR,"addContact:Contact Data Needed");
}
if((_401)==undefined){
throw new DeviceException(this.error.MISSING_ARG_ERR,"addContact:Contact Data Needed");
}
if((typeof _401)!="object"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"addContact:Invalid Contact Data");
}
var _402={};
modifyObjectBaseProp(_402);
__s60_enumerate_contact_object(_401,null,__sp_contact_extract,_402);
var _403={};
modifyObjectBaseProp(_403);
_403.Type="Contact";
_403.Data=_402;
try{
if(_402.id){
throw new DeviceException(this.error.NOT_SUPPORTED_ERR,"Contacts: addContact: Id Not Supported");
}
var _404=this.so.IDataSource.Add(_403);
if(_402){
delete _402.id;
}
if(_403){
delete _403.Type;
delete _403.Data;
}
var _405=_404["ReturnValue"];
if(_404.ErrorCode!=0){
var _406=mappingVerification(_404.ErrorCode);
if(_404.ErrorMessage){
var _407=splitErrorMessage(_404.ErrorMessage);
if(_406){
throw new DeviceException(MapErrorCode[_404.ErrorCode],"Contacts: addContact: "+_407);
}else{
throw new DeviceException(_404.ErrorCode,"Contacts: addContact: "+_407);
}
}else{
if(_406){
throw new DeviceException(MapErrorCode[_404.ErrorCode],"Contacts: addContact: Operation Failed");
}else{
throw new DeviceException(_404.ErrorCode,"Contacts: addContact: Operation Failed");
}
}
}
return _405;
}
catch(e){
__device_handle_exception(e,"__sp_contacts_addContact: "+e);
}
};
function __sp_contacts_update(_408){
try{
if(!(_408&&_408.id)){
throw new DeviceException(this.error.MISSING_ARG_ERR,"Contacts: updateContact: contact is missing");
}
var _409={};
modifyObjectBaseProp(_409);
__s60_enumerate_contact_object(_408,null,__sp_contact_extract,_409);
if(_409.id==undefined){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Contacts: updateContact: Invalid id type");
}
if(typeof _409.id!="string"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Contacts: updateContact: Invalid id type");
}
var _40a={};
modifyObjectBaseProp(_40a);
_40a.Type="Contact";
_40a.Data=_409;
var _40b=this.so.IDataSource.Add(_40a);
if(_409){
delete _409.id;
}
if(_40a){
delete _40a.Type;
delete _40a.Data;
}
if(_40b.ErrorCode!=0){
var _40c=mappingVerification(_40b.ErrorCode);
if(_40b.ErrorMessage){
var _40d=splitErrorMessage(_40b.ErrorMessage);
if(_40c){
throw new DeviceException(MapErrorCode[_40b.ErrorCode],"Contacts: updateContact: "+_40d);
}else{
throw new DeviceException(_40b.ErrorCode,"Contacts: updateContact: "+_40d);
}
}else{
if(_40c){
throw new DeviceException(MapErrorCode[_40b.ErrorCode],"Contacts: updateContact: Operation Failed");
}else{
throw new DeviceException(_40b.ErrorCode,"Contacts: updateContact: Operation Failed");
}
}
}
}
catch(e){
__device_handle_exception(e,"__sp_contacts_updateContact: "+e);
}
};
function __sp_contacts_delete(id){
__device_debug("sp_contacts_delete id: "+id);
var _40f={};
modifyObjectBaseProp(_40f);
if(id==undefined){
throw new DeviceException(this.error.MISSING_ARG_ERR,"Contacts: deleteContacts: idlist is missing");
}
if(typeof id=="object"){
_40f.IdList=id;
}else{
_40f.IdList=[];
_40f.IdList[0]=id;
}
var _410={};
modifyObjectBaseProp(_410);
_410.Type="Contact";
_410.Data=_40f;
try{
var _411=this.so.IDataSource.Delete(_410);
if(_40f){
delete _40f.IdList;
}
if(_410){
delete _410.Type;
delete _410.Data;
}
if(_411.ErrorCode!=0){
var _412=mappingVerification(_411.ErrorCode);
if(_411.ErrorMessage){
var _413=splitErrorMessage(_411.ErrorMessage);
if(_412){
throw new DeviceException(MapErrorCode[_411.ErrorCode],"Contacts: deleteContacts: "+_413);
}else{
throw new DeviceException(_411.ErrorCode,"Contacts: deleteContacts: "+_413);
}
}else{
if(_412){
throw new DeviceException(MapErrorCode[_411.ErrorCode],"Contacts: deleteContacts: Operation Failed");
}else{
throw new DeviceException(_411.ErrorCode,"Contacts: deleteContacts: Operation Failed");
}
}
}
}
catch(e){
__device_handle_exception(e,"__sp_contacts_deleteContacts: "+e);
}
};
function __sp_contacts_get(id){
var _415={};
modifyObjectBaseProp(_415);
_415.Type="Contact";
if(id==null){
throw new DeviceException(this.error.MISSING_ARG_ERR,"Contacts: getContactInfo: id should not be null");
}
if(typeof id!="string"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Contacts: getContactInfo: id should be string");
}
_415.Filter={};
modifyObjectBaseProp(_415.Filter);
_415.Filter.id=id;
try{
var rval=this.so.IDataSource.GetList(_415);
if(_415.Filter){
delete _415.Filter.id;
}
if(_415){
delete _415.Type;
delete _415.Filter;
}
if(rval){
if(rval.ErrorCode!=0){
var _417=mappingVerification(rval.ErrorCode);
if(rval.ErrorMessage){
var _418=splitErrorMessage(rval.ErrorMessage);
if(_417){
throw new DeviceException(MapErrorCode[rval.ErrorCode],"Contacts: getContactInfo: "+_418);
}else{
throw new DeviceException(rval.ErrorCode,"Contacts: getContactInfo: "+_418);
}
}else{
if(_417){
throw new DeviceException(MapErrorCode[rval.ErrorCode],"Contacts: getContactInfo: Operation Failed");
}else{
throw new DeviceException(rval.ErrorCode,"Contacts: getContactInfo: Operation Failed");
}
}
}
var _419={};
modifyObjectBaseProp(_419);
var _41a=rval.ReturnValue.getNext();
__sp_device_contact_build(_41a,_419);
return _419;
}
}
catch(e){
__device_handle_exception(e,"__sp_contacts_getContactInfo:"+e);
}
};
function __sp_contacts_addGroup(_41b){
var _41c={};
modifyObjectBaseProp(_41c);
_41c.GroupLabel=_41b;
if(typeof (_41c.GroupLabel)==null){
throw new DeviceException(this.error.MISSING_ARG_ERR,"Contacts: addGroups: callback is missing");
}
if((typeof _41c.GroupLabel)=="undefined"){
throw new DeviceException(this.error.MISSING_ARG_ERR,"addGroup:Group Data Needed");
}
if((_41c.GroupLabel)==undefined){
throw new DeviceException(this.error.MISSING_ARG_ERR,"addGroup:Group Data Needed");
}
var _41d={};
modifyObjectBaseProp(_41d);
_41d.Type="Group";
_41d.Data=_41c;
try{
var _41e=this.so.IDataSource.Add(_41d);
if(_41c){
delete _41c.GroupLabel;
}
if(_41d){
delete _41d.Type;
delete _41d.Data;
}
var _41f=_41e["ReturnValue"];
if(_41e.ErrorCode!=0){
var _420=mappingVerification(_41e.ErrorCode);
if(_41e.ErrorMessage){
var _421=splitErrorMessage(_41e.ErrorMessage);
if(_420){
throw new DeviceException(MapErrorCode[_41e.ErrorCode],"Contacts: addGroup: "+_421);
}else{
throw new DeviceException(_421,_41e.ErrorCode,"Contacts: addGroup: Operation Failed ");
}
}else{
if(_420){
throw new DeviceException(MapErrorCode[_41e.ErrorCode],"Contacts: addGroup: Operation Failed");
}else{
throw new DeviceException(_41e.ErrorCode,"Contacts: addGroup: Operation Failed");
}
}
}
return _41f;
}
catch(e){
__device_handle_exception(e,"__sp_contacts_addGroup: "+e);
}
};
function __sp_contacts_getGroups_cb(arg1,arg2,arg3){
var iter=null;
var _426;
var _427;
var _428;
_428=glob_obj.getFromArray(arg1);
if(_428){
_426=_428.success_cb;
_427=_428.error_cb;
}else{
return;
}
iter=arg3.ReturnValue;
if(arg3.ReturnValue){
iter=new __sp_group_iterator(arg3.ReturnValue);
}else{
if(arg3.ErrorCode!=0){
var _429;
if(arg3.ErrorMessage){
_429=splitErrorMessage(arg3.ErrorMessage);
}else{
_429="Operation Failed";
}
_427(new DeviceException(_429,MapErrorCode[arg3.ErrorCode],"Contacts: getGroups:"));
return;
}
}
_426(iter);
glob_obj.removeFromArray(arg1);
};
function __sp_contacts_getGroups(_42a,_42b){
var _42c={};
modifyObjectBaseProp(_42c);
_42c.Type="Group";
try{
if(!_42a){
throw new DeviceException(this.error.MISSING_ARG_ERR,"Contacts: getGroups: callback is missing");
}else{
if(typeof _42a!="function"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Contacts: getGroups: callback is invalid");
}
}
if(_42b){
if(typeof (_42b)!="function"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Contacts: getGroups: ErrorCallback is invalid");
}
}
temp_scb=_42a;
temp_ecb=_42b;
var rval=this.so.IDataSource.GetList(_42c,this.getGroupsCb);
if(rval.TransactionID){
glob_obj.addToGlobalArray(rval.TransactionID,_42a,_42b);
}
if(_42c){
delete _42c.Type;
}
if(rval.ErrorCode!=0){
var _42e=mappingVerification(rval.ErrorCode);
var _42f=null;
if(rval.ErrorMessage){
_42f=splitErrorMessage(rval.ErrorMessage);
}
if(_42e){
switch(MapErrorCode[rval.ErrorCode]){
case this.error.MISSING_ARG_ERR:
case this.error.INVALID_ARG_ERR:
case this.error.NOT_SUPPORTED_ERR:
if(_42f){
throw new DeviceException(MapErrorCode[rval.ErrorCode],"Contacts: getGroups: "+_42f);
}else{
throw new DeviceException(MapErrorCode[rval.ErrorCode],"Contacts: getGroups: Operation Failed");
}
break;
default:
if(_42b!=undefined){
if(_42f){
_42b(new DeviceException(MapErrorCode[rval.ErrorCode],"Contacts: getGroups: "+_42f));
}else{
_42b(new DeviceException(MapErrorCode[rval.ErrorCode],"Contacts:  getGroups: Operation Failed "));
}
}else{
if(_42f){
throw new DeviceException(MapErrorCode[rval.ErrorCode],"Contacts: getGroups: Operation Failed"+_42f);
}else{
throw new DeviceException(MapErrorCode[rval.ErrorCode],"Contacts: getGroups: Operation Failed");
}
}
}
}else{
if(_42b!=undefined){
if(_42f){
_42b(new DeviceException(rval.ErrorCode,"Contacts: getGroups: "+_42f));
}else{
_42b(new DeviceException(rval.ErrorCode,"Contacts: getGroups: Operation Failed"));
}
}else{
if(_42f){
throw new DeviceException(rval.ErrorCode,"Contacts: getGroups: Operation Failed"+_42f);
}else{
throw new DeviceException(rval.ErrorCode,"Contacts: getGroups: Operation Failed");
}
}
}
}
return rval.TransactionID;
}
catch(e){
__device_handle_exception(e,"__sp_contacts_getGroups: "+e);
}
};
function __sp_contacts_deleteGroups(id){
var _431={};
modifyObjectBaseProp(_431);
var _432=[];
if(typeof id=="object"){
var i=0;
for(var val in id){
_432[i]=id[val];
i++;
}
}else{
_432[0]=id;
}
_431.IdList=[];
_431.IdList=_432;
var _435={};
modifyObjectBaseProp(_435);
_435.Type="Group";
_435.Data=_431;
try{
var _436=this.so.IDataSource.Delete(_435);
if(_436.ErrorCode!=0){
var _437=mappingVerification(_436.ErrorCode);
if(_436.ErrorMessage){
var _438=splitErrorMessage(_436.ErrorMessage);
if(_437){
throw new DeviceException(MapErrorCode[_436.ErrorCode],"Contacts: deleteGroups: "+_438);
}else{
throw new DeviceException(_436.ErrorCode,"Contacts: deleteGroups: "+_438);
}
}else{
if(_437){
throw new DeviceException(MapErrorCode[_436.ErrorCode],"Contacts: deleteGroups: Operation Failed");
}else{
throw new DeviceException(_436.ErrorCode,"Contacts: deleteGroups: Operation Failed");
}
}
}
}
catch(e){
__device_handle_exception(e,"__sp_contacts_deleteGroups: "+e);
}
};
function __sp_contacts_addContactsToGroup(_439,id1){
try{
var _43b={};
modifyObjectBaseProp(_43b);
var _43c=false;
_43b.Type="Group";
var map={};
modifyObjectBaseProp(map);
var _43e=[];
if(typeof id1=="object"){
var i=0;
for(var val in id1){
_43e[i]=id1[val];
i++;
}
}else{
_43e[0]=id1;
}
map.IdList=_43e;
_43c=true;
delete _43e.index;
if(_439!=undefined){
map.id=_439;
_43c=true;
}
if(_43c){
_43b.Data=map;
}
_43b.OperationType="Associate";
var _441=this.so.IDataSource.Organise(_43b);
if(map){
delete map.id;
delete map.IdList;
}
if(_43b){
delete _43b.Data;
delete _43b.OperationType;
delete _43b.Type;
}
if(_441.ErrorCode!=0){
var _442=mappingVerification(_441.ErrorCode);
if(_441.ErrorMessage){
var _443=splitErrorMessage(_441.ErrorMessage);
if(_442){
throw new DeviceException(MapErrorCode[_441.ErrorCode],"Contacts: addContactsToGroup: "+_443);
}else{
throw new DeviceException(_441.ErrorCode,"Contacts: addContactsToGroup: "+_443);
}
}else{
if(_442){
throw new DeviceException(MapErrorCode[_441.ErrorCode],"Contacts: addContactsToGroup: Operation Failed");
}else{
throw new DeviceException(_441.ErrorCode,"Contacts: addContactsToGroup: Operation Failed");
}
}
}
}
catch(e){
__device_handle_exception(e,"__sp_contacts_addContactsToGroup: "+e);
}
};
function __sp_contacts_getContactIds_cb(arg1,arg2,arg3){
var item=null;
var _448=null;
var _449;
var _44a;
var _44b;
_44b=glob_obj.getFromArray(arg1);
if(_44b){
_449=_44b.success_cb;
_44a=_44b.error_cb;
}else{
alert("Contacts: __sp_contacts_getContactIds_cb : Callback not found ");
return;
}
var id=null;
if(arg3["ReturnValue"]!=undefined){
item=arg3["ReturnValue"];
id=item["IdList"];
_448=[];
_448=id;
delete _448.index;
}else{
if(arg3.ErrorCode!=0){
var _44d;
if(arg3.ErrorMessage){
_44d=splitErrorMessage(arg3.ErrorMessage);
}else{
_44d="Operation Failed";
}
_44a(new DeviceException(MapErrorCode[arg3.ErrorCode],"Contacts: getContactIds:"+_44d));
return;
}
}
_449(_448);
glob_obj.removeFromArray(arg1);
};
function __sp_contacts_getContactIds(_44e,_44f,_450,_451){
var _452={};
modifyObjectBaseProp(_452);
_452.Type="Contact";
if(_44f){
_452.Filter={};
modifyObjectBaseProp(_452.Filter);
_452.Filter.SearchVal=_44f;
}
if(_450!=null&&_450!=undefined){
_452.Sort={};
modifyObjectBaseProp(_452.Sort);
if(typeof _450=="number"){
if(_450==this.SORT_ASCENDING){
_452.Sort.Order="Ascending";
}else{
if(_450==this.SORT_DESCENDING){
_452.Sort.Order="Descending";
}else{
_451(new DeviceException(this.error.DATA_OUT_OF_RANGE_ERR,"Contacts: getContacts: invalid sortOrder input"));
return;
}
}
}else{
throw new DeviceException(this.error.INVALID_ARG_ERR,"Contacts: getContactIds: SortOrder is Invalid");
}
}
try{
if(!_44e){
throw new DeviceException(this.error.MISSING_ARG_ERR,"Contacts: getContactIds: callback is missing");
}else{
if(typeof _44e!="function"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Contacts: getContactIds: callback is invalid");
}
}
if(_451){
if(typeof (_451)!="function"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Contacts: getContactIds: ErrorCallback is invalid");
}
}
temp_scb=_44e;
temp_ecb=_451;
var rval=this.so.IDataSource.GetIds(_452,this.getContactIdsCb);
if(rval.TransactionID){
glob_obj.addToGlobalArray(rval.TransactionID,_44e,_451);
}
if(rval.ErrorCode!=0){
var _454=mappingVerification(rval.ErrorCode);
var _455=null;
if(rval.ErrorMessage){
var _455=splitErrorMessage(rval.ErrorMessage);
}
if(_454){
switch(MapErrorCode[rval.ErrorCode]){
case this.error.MISSING_ARG_ERR:
case this.error.INVALID_ARG_ERR:
case this.error.NOT_SUPPORTED_ERR:
if(_455){
throw new DeviceException(MapErrorCode[rval.ErrorCode],"Contacts: getContactIds: "+_455);
}else{
throw new DeviceException(MapErrorCode[rval.ErrorCode],"Contacts: getContactIds: Operation Failed");
}
break;
default:
if(_451!=undefined){
if(_455){
_451(new DeviceException(MapErrorCode[rval.ErrorCode],"Contacts: getContactIds: "+_455));
}else{
_451(new DeviceException(MapErrorCode[rval.ErrorCode],"Contacts: getContactIds: Operation Failed "));
}
}else{
if(_455){
throw new DeviceException(MapErrorCode[rval.ErrorCode],"Contacts: getContactIds:"+_455);
}else{
throw new DeviceException(MapErrorCode[rval.ErrorCode],"Contacts: getContactIds: Operation Failed");
}
}
}
}else{
if(_451!=undefined){
if(_455){
_451(new DeviceException(rval.ErrorCode,"Contacts: getContactIds: "+_455));
}else{
_451(new DeviceException(rval.ErrorCode,"Contacts: getContactIds: Operation Failed "));
}
}else{
if(_455){
throw new DeviceException(rval.ErrorCode,"Contacts: getContactIds:"+_455);
}else{
throw new DeviceException(rval.ErrorCode,"Contacts: getContactIds: Operation Failed");
}
}
}
}
return rval.TransactionID;
}
catch(e){
__device_handle_exception(e,"__sp_contacts_getContactIds: "+e);
}
};
function __sp_contacts_getGroupIds_cb(arg1,arg2,arg3){
var _459=null;
var item=null;
var _45b=[];
var _45c;
var _459;
var _45d;
_45d=glob_obj.getFromArray(arg1);
if(_45d){
_45c=_45d.success_cb;
_459=_45d.error_cb;
}else{
return;
}
if(arg3.ReturnValue){
item=arg3["ReturnValue"];
arg3.ReturnValue.close();
var id=item["IdList"];
_45b=id;
}else{
if(arg3.ErrorCode!=0){
var _45f;
if(rval.ErrorMessage){
_45f=splitErrorMessage(rval.ErrorMessage);
}else{
_45f="Operation Failed";
}
_459(new DeviceException(MapErrorCode[arg3.ErrorCode],"Contacts: getGroupIds:"+_45f));
return;
}
}
_45c(_45b);
delete _45b.index;
glob_obj.removeFromArray(arg1);
};
function __sp_contacts_getGroupIds(_460,_461){
var _462={};
modifyObjectBaseProp(_462);
_462.Type="Group";
try{
if(!_460){
throw new DeviceException(this.error.MISSING_ARG_ERR,"Contacts: getGroupIds: callback is missing");
}else{
if(typeof _460!="function"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Contacts: getGroupIds: callback is invalid");
}
}
if(_461){
if(typeof (_461)!="function"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Contacts: getGroupIds: ErrorCallback is invalid");
}
}
temp_scb=_460;
temp_ecb=_461;
var rval=this.so.IDataSource.GetIds(_462,this.getGroupIdsCb);
if(rval.TransactionID){
glob_obj.addToGlobalArray(rval.TransactionID,_460,_461);
}
if(_462){
delete _462.Type;
}
if(rval.ErrorCode!=0){
var _464=mappingVerification(rval.ErrorCode);
var _465=null;
if(rval.ErrorMessage){
var _465=splitErrorMessage(rval.ErrorMessage);
}
if(_464){
switch(rval.ErrorCode){
case this.error.MISSING_ARG_ERR:
case this.error.INVALID_ARG_ERR:
case this.error.NOT_SUPPORTED_ERR:
if(_465){
throw new DeviceException(MapErrorCode[rval.ErrorCode],"Contacts: getGroupIds: "+_465);
}else{
throw new DeviceException(MapErrorCode[rval.ErrorCode],"Contacts: getGroupIds: Operation Failed");
}
break;
default:
if(_461!=undefined){
if(_465){
_461(new DeviceException(MapErrorCode[rval.ErrorCode],"Contacts: getGroupIds: "+_465));
}else{
_461(new DeviceException(MapErrorCode[rval.ErrorCode],"Contacts: getGroupIds: Operation Failed"));
}
}else{
if(_465){
throw new DeviceException(MapErrorCode[rval.ErrorCode],"Contacts: Contacts: getGroupIds:"+_465);
}else{
throw new DeviceException(MapErrorCode[rval.ErrorCode],"Contacts: getGroupIds: Operation Failed");
}
}
}
}else{
if(_461!=undefined){
if(_465){
_461(new DeviceException(rval.ErrorCode,"Contacts: getGroupIds: "+_465));
}else{
_461(new DeviceException(rval.ErrorCode,"Contacts: getGroupIds: Operation Failed"));
}
}else{
if(_465){
throw new DeviceException(rval.ErrorCode,"Contacts: Contacts: getGroupIds:"+_465);
}else{
throw new DeviceException(rval.ErrorCode,"Contacts: getGroupIds: Operation Failed");
}
}
}
}
return rval.TransactionID;
}
catch(e){
__device_handle_exception(e,"__sp_contacts_getGroupIds: "+e);
}
};
function __sp_contacts_removeContactsFromGroup(_466,id){
try{
var _468={};
modifyObjectBaseProp(_468);
var _469=false;
_468.Type="Group";
var map={};
if(id!=undefined){
var _46b=[];
if(typeof id=="object"){
var i=0;
for(var val in id){
_46b[i]=id[val];
i++;
}
}else{
_46b[0]=id;
}
map.IdList=_46b;
_469=true;
}
if(_466!=undefined){
map.id=_466;
_469=true;
}
if(_469){
_468.Data=map;
}
_468.OperationType="Disassociate";
var _46e=this.so.IDataSource.Organise(_468);
if(map){
delete map.IdList;
}
if(_468){
delete _468.Data;
delete _468.OperationType;
delete _468.Type;
}
if(_46e.ErrorCode!=0){
var _46f=mappingVerification(_46e.ErrorCode);
if(_46e.ErrorMessage){
var _470=splitErrorMessage(_46e.ErrorMessage);
if(_46f){
throw new DeviceException(MapErrorCode[_46e.ErrorCode],"Contacts: removeContactsFromGroup: "+_470);
}else{
throw new DeviceException(_46e.ErrorCode,"Contacts: removeContactsFromGroup: "+_470);
}
}else{
if(_46f){
throw new DeviceException(MapErrorCode[_46e.ErrorCode],"Contacts: removeContactsFromGroup: Operation Failed");
}else{
throw new DeviceException(_46e.ErrorCode,"Contacts: removeContactsFromGroup: Operation Failed");
}
}
}
}
catch(e){
__device_handle_exception(e,"__sp_contacts_removeContactsFromGroup: "+e);
}
};
function __sp_contacts_cancel(_471){
try{
var _472={};
if((_471)==null){
throw new DeviceException(this.error.MISSING_ARG_ERR,"Contacts: cancel: transactionId is missing ");
}
if((_471)==undefined){
throw new DeviceException(this.error.MISSING_ARG_ERR,"Contacts: cancel:transactionId is undefined ");
}
if((typeof _471)=="undefined"){
throw new DeviceException(this.error.MISSING_ARG_ERR,"Contacts: cancel: transactionId is undefined ");
}
if(((typeof _471)!="number")||(_471<=0)){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Contacts: cancel: transactionId is Invalid");
}
modifyObjectBaseProp(_472);
_472.TransactionID=_471;
var _473=this.so.IDataSource.Cancel(_472);
if(_472){
delete _472.TransactionID;
}
var _474=_473["ErrorCode"];
if(_474!=0){
var _475=mappingVerification(_473.ErrorCode);
if(_473["ErrorMessage"]){
var _476=splitErrorMessage(_473.ErrorMessage);
if(_475){
throw new DeviceException(MapErrorCode[_474],"Contacts: cancel: "+_476);
}else{
throw new DeviceException(_474,"Contacts: cancel: "+_476);
}
}else{
if(_475){
throw new DeviceException(MapErrorCode[_474],"Contacts: cancel: Operation Failed");
}else{
throw new DeviceException(_474,"Contacts: cancel: Operation Failed");
}
}
}
}
catch(e){
__device_handle_exception(e,"__sp_contacts_cancel: "+e);
}
};
function __sp_contacts_updateGroup(_477){
if(!(_477)){
throw new DeviceException(this.error.MISSING_ARG_ERR,"Contacts: updateGroup:Group Data is missing");
}
if((typeof _477)!="object"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Contacts: updateGroup:Invalid Group Data");
}
if(!(_477&&_477.groupId)){
throw new DeviceException(this.error.MISSING_ARG_ERR,"Contacts: updateGroup: Group id is missing");
}
if(typeof _477.groupId!="string"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Contacts: updateGroup:Invalid Group id input");
}
try{
var _478={};
modifyObjectBaseProp(_478);
_478.Type="Group";
var _479={};
modifyObjectBaseProp(_479);
if(_477!=undefined){
if(_477.groupId!=undefined){
_479["id"]=_477.groupId;
}else{
throw new DeviceException(this.error.MISSING_ARG_ERR,"Contacts: updateGroup: Id input is mandatory");
}
if(_477.groupName!=undefined){
_479["GroupLabel"]=_477.groupName;
}
}
_478.Data=_479;
var _47a=this.so.IDataSource.Add(_478);
if(_479){
delete _479.prototype;
}
if(_478){
delete _478.Data;
delete _478.Type;
}
if(_47a.ErrorCode!=0){
var _47b=mappingVerification(_47a.ErrorCode);
if(_47a.ErrorMessage){
var _47c=splitErrorMessage(_47a.ErrorMessage);
if(_47b){
throw new DeviceException(MapErrorCode[_47a.ErrorCode],"Contacts: updateGroup: "+_47c);
}else{
throw new DeviceException(_47a.ErrorCode,"Contacts: updateGroup: "+_47c);
}
}else{
if(_47b){
throw new DeviceException(MapErrorCode[_47a.ErrorCode],"Contacts: updateGroup: Operation Failed");
}else{
throw new DeviceException(_47a.ErrorCode,"Contacts: updateGroup: Operation Failed");
}
}
}
}
catch(e){
__device_handle_exception(e,"__sp_contacts_updateGroup: "+e);
}
};
function __sp_contacts_getGroupInfo(_47d){
try{
var _47e={};
modifyObjectBaseProp(_47e);
_47e.Type="Group";
_47e.Filter={};
modifyObjectBaseProp(_47e.Filter);
if(_47d==undefined){
throw new DeviceException(this.error.MISSING_ARG_ERR,"Contacts: getGroupInfo: Id input is mandatory");
}
if((typeof _47d)!="string"){
throw new DeviceException(this.error.INVALID_ARG_ERR,"Contacts: getGroupInfo: Id input is mandatory");
}
_47e.Filter.id=_47d;
var rval=this.so.IDataSource.GetList(_47e);
if(_47e.Filter){
delete _47e.Filter.id;
}
if(_47e){
delete _47e.Filter;
delete _47e.Type;
}
if(rval){
if(rval.ErrorCode!=0){
var _480=mappingVerification(rval.ErrorCode);
if(rval.ErrorMessage){
var _481=splitErrorMessage(rval.ErrorMessage);
if(_480){
throw new DeviceException(MapErrorCode[rval.ErrorCode],"Contacts: getGroupInfo: "+_481);
}else{
throw new DeviceException(rval.ErrorCode,"Contacts: getGroupInfo: "+_481);
}
}else{
if(_480){
throw new DeviceException(MapErrorCode[rval.ErrorCode],"Contacts: getGroupInfo: Operation Failed");
}else{
throw new DeviceException(rval.ErrorCode,"Contacts: getGroupInfo: Operation Failed");
}
}
}else{
var _482={};
modifyObjectBaseProp(_482);
var _483=rval.ReturnValue.getNext();
__sp_device_groupinfo_build(_483,_482);
return _482;
}
}
}
catch(e){
__device_handle_exception(e,"__sp_contacts_getGroupInfo:"+e);
}
};
function mappingVerification(_484){
if(_484===1016||_484===1012||_484===1010||_484===1009||_484===1005||_484===1000||_484===1011||_484===1007||_484===1003||_484===1002){
return true;
}else{
return false;
}
};
function __sp_contacts_instance(){
this.SORT_ASCENDING=0;
this.SORT_DESCENDING=1;
this.descriptor=new __sp_contacts_descriptor();
this.startEditor=__sp_contacts_startEditor;
this.getContacts=__sp_contacts_getContacts;
this.getContactsCb=__sp_contacts_getContacts_cb;
this.addContact=__sp_contacts_add;
this.updateContact=__sp_contacts_update;
this.deleteContacts=__sp_contacts_delete;
this.getContactInfo=__sp_contacts_get;
this.addGroup=__sp_contacts_addGroup;
this.getGroups=__sp_contacts_getGroups;
this.getGroupsCb=__sp_contacts_getGroups_cb;
this.deleteGroups=__sp_contacts_deleteGroups;
this.addContactsToGroup=__sp_contacts_addContactsToGroup;
this.getContactIds=__sp_contacts_getContactIds;
this.getContactIdsCb=__sp_contacts_getContactIds_cb;
this.getGroupIds=__sp_contacts_getGroupIds;
this.getGroupIdsCb=__sp_contacts_getGroupIds_cb;
this.removeContactsFromGroup=__sp_contacts_removeContactsFromGroup;
this.cancel=__sp_contacts_cancel;
this.updateGroup=__sp_contacts_updateGroup;
this.getGroupInfo=__sp_contacts_getGroupInfo;
this.error=new DeviceException(0,"Dummy");
try{
this.so=device.getServiceObject("Service.Contact","IDataSource");
}
catch(e){
__device_handle_exception(e,"Contacts service not available "+e);
}
};

