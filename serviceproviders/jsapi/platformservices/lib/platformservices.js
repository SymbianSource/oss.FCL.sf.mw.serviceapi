/*
* Copyright (c) 2005 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  This is a top level bld file to generate all sapi libraries.
*
*/

function __device_calendar_descriptor(_1){
this.interfaceName=_1.interfaceName;
this.version=_1.version;
};
function __device_calendar_startEditor(_2,_3,_4){
this.provider.startEditor(_2,_3,_4);
};
function __device_calendar_getList(_5,_6,_7){
return this.provider.getList(_5,_6,_7);
};
function __device_calendar_add(_8){
return this.provider.addEntry(_8);
};
function __device_calendar_update(_9){
return this.provider.updateEntry(_9);
};
function __device_calendar_delete(_a){
this.provider.deleteEntry(_a);
};
function __device_calendar_cancel(_b){
this.provider.cancel(_b);
};
function __device_calendar(_c){
this.provider=_c;
this.interfaceName=_c.descriptor.interfaceName;
this.version=_c.descriptor.version;
this.startEditor=__device_calendar_startEditor;
this.getList=__device_calendar_getList;
this.addEntry=__device_calendar_add;
this.updateEntry=__device_calendar_update;
this.deleteEntry=__device_calendar_delete;
this.cancel=__device_calendar_cancel;
};
var __device_calendar_service_entry={"name":null,"version":null,"proto":__device_calendar,"descriptor":__device_calendar_descriptor,"providers":[{"descriptor":__sp_calendar_descriptor,"instance":__sp_calendar_instance}]};
function __device_camera_descriptor(_d){
this.interfaceName=_d.interfaceName;
this.version=_d.version;
};
function __device_camera_startCamera(_e,_f){
return this.provider.startCamera(_e,_f);
};
function __device_camera_stopViewfinder(){
this.provider.stopViewfinder();
};
function __device_camera_takePicture(_10){
this.provider.takePicture(_10);
};
function __device_camera(_11){
this.provider=_11;
this.interfaceName=_11.descriptor.interfaceName;
this.version=_11.descriptor.version;
this.supportedMediaTypes=_11.supportedMediaTypes;
this.supportedSizes=_11.supportedSizes;
this.startCamera=__device_camera_startCamera;
this.stopViewfinder=__device_camera_stopViewfinder;
this.takePicture=__device_camera_takePicture;
};
var __device_camera_service_entry={"name":null,"version":null,"proto":__device_camera,"descriptor":__device_camera_descriptor,"providers":[{"descriptor":__sp_camera_descriptor,"instance":__sp_camera_instance}]};
function __device_commlog_descriptor(_12){
this.interfaceName=_12.interfaceName;
this.version=_12.version;
};
function __device_commlog_getList(_13,_14,_15){
return this.provider.getList(_13,_14,_15);
};
function __device_commlog_setNotification(_16,_17){
return this.provider.setNotification(_16,_17);
};
function __device_commlog_cancelNotification(){
return this.provider.cancelNotification();
};
function __device_commlog_cancel(_18){
return this.provider.cancel(_18);
};
function __device_commlog_deleteLogEntry(_19){
return this.provider.deleteLogEntry(_19);
};
function __device_commlog(_1a){
this.provider=_1a;
this.interfaceName=_1a.descriptor.interfaceName;
this.version=_1a.descriptor.version;
this.getList=__device_commlog_getList;
this.setNotification=__device_commlog_setNotification;
this.cancelNotification=__device_commlog_cancelNotification;
this.cancel=__device_commlog_cancel;
this.deleteLogEntry=__device_commlog_deleteLogEntry;
};
var __device_commlog_service_entry={"name":null,"version":null,"proto":__device_commlog,"descriptor":__device_commlog_descriptor,"providers":[{"descriptor":__sp_commlog_descriptor,"instance":__sp_commlog_instance}]};
function __device_contacts_descriptor(_1b){
this.interfaceName=_1b.interfaceName;
this.version=_1b.version;
};
function __device_contacts_startEditor(_1c,_1d,_1e){
return this.provider.startEditor(_1c,_1d,_1e);
};
function __device_contacts_getContacts(_1f,_20,_21,_22){
return this.provider.getContacts(_1f,_20,_21,_22);
};
function __device_contacts_add(_23){
return this.provider.addContact(_23);
};
function __device_contacts_update(_24){
this.provider.updateContact(_24);
};
function __device_contacts_delete(id){
this.provider.deleteContacts(id);
};
function __device_contacts_getContactInfo(id){
return this.provider.getContactInfo(id);
};
function __device_contacts_addGroup(_27){
return this.provider.addGroup(_27);
};
function __device_contacts_getGroups(_28,_29){
return this.provider.getGroups(_28,_29);
};
function __device_contacts_deleteGroups(id){
this.provider.deleteGroups(id);
};
function __device_contacts_addContactsToGroup(_2b,id){
this.provider.addContactsToGroup(_2b,id);
};
function __device_contacts_getContactIds(_2d,_2e,_2f,_30){
return this.provider.getContactIds(_2d,_2e,_2f,_30);
};
function __device_contacts_getGroupIds(_31,_32){
return this.provider.getGroupIds(_31,_32);
};
function __device_contacts_removeContactsFromGroup(_33,id){
this.provider.removeContactsFromGroup(_33,id);
};
function __device_contacts_cancel(_35){
this.provider.cancel(_35);
};
function __device_contacts_updateGroup(_36){
this.provider.updateGroup(_36);
};
function __device_contacts_getGroupInfo(_37){
return this.provider.getGroupInfo(_37);
};
function __device_contacts(_38){
this.provider=_38;
this.interfaceName=_38.descriptor.interfaceName;
this.version=_38.descriptor.version;
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
var __device_debug_on__=true;
var MISSING_ARG_ERR=1;
var INVALID_ARG_ERR=2;
var NOT_SUPPORTED_ERR=3;
var event_completed=2;
var event_cancelled=3;
var __Service_Interface_Ver=1;
var MapErrorCode={1016:100,1012:101,1010:102,1009:103,1005:104,1000:105,1011:106,1007:107,1003:1,1002:2};
function __device_debug(_39){
};
function __device_handle_exception(e,_3b){
__device_debug(_3b);
throw (e);
};
function __device_typeof(_3c){
if(_3c==undefined){
return "undefined";
}
if(_3c instanceof Object){
if(_3c instanceof String){
return "String";
}else{
if(_3c instanceof Array){
return "Array";
}
}
}
if(typeof _3c){
if(typeof _3c=="object"){
if(typeof _3c=="object"&&!_3c){
return "null";
}
}else{
if(typeof _3c=="string"){
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
var _3d=device.getServiceObject("Service.ServiceRegistry","IService");
var _3e={ServiceName:"Service.Calendar",InterfaceName:"IDataSource"};
var _3f=_3d.IService.GetList(_3e);
if(_3f.ErrorCode==0){
var _40=_3f.ReturnValue;
if(_40){
var _41=_40.getNext();
if(_41){
var _42=_41.VersionList;
var _43;
for(_43 in _42){
if(_42[_43]>__Service_Interface_Ver){
__Service_Interface_Ver=_42[_43];
}
}
}
}
_40.close();
}
_3d.close();
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
function __device_get_interface(s,_47,_48){
var i=s.interfaces;
for(var d in i){
if(i[d].name==null){
__device_update_descriptor(i[d]);
}
if(i[d].name==undefined){
continue;
}
if(i[d].name==_47){
if(_48){
if(i[d].version>=_48){
return __device_get_implementation(i[d]);
}
}else{
return __device_get_implementation(i[d]);
}
}
}
return null;
};
function __device_service_load(_4b,_4c){
var _4d=new DeviceException("dummy",0);
if(_4b){
if(typeof _4b!="string"){
throw new DeviceException(_4d.INVALID_ARG_ERR,"nokia.device.load:Invalid type interfaceName");
}
}else{
throw new DeviceException(_4d.MISSING_ARG_ERR,"nokia.device.load:interfaceName param expected");
}
if(_4c){
if(typeof _4c!="number"){
throw new DeviceException(_4d.INVALID_ARG_ERR,"nokia.device.load:Invalid type version");
}
}
__device_services_init();
for(var s in __device_services){
var i=__device_get_interface(__device_services[s],_4b,_4c);
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
var _53=new Array();
for(var i in s.interfaces){
if(s.interfaces[i].name==null){
__device_update_descriptor(s.interfaces[i]);
}
if(s.interfaces[i].name==undefined){
continue;
}
_53[i]=new Object();
_53[i].name=s.interfaces[i].name;
_53[i].version=s.interfaces[i].version;
}
return _53;
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
var _58=__device_interface_list(__device_services[s]);
return new __FWIter(_58);
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
var _infinity=Infinity;
function PositionError(){
this.UNKNOWN_ERROR=0;
this.PERMISSION_DENIED=1;
this.POSITION_UNAVAILABLE=2;
this.TIMEOUT=3;
this.code;
this.message;
};
function Coordinates(){
this.latitude=null;
this.longitude=null;
this.altitude=null;
this.accuracy=null;
this.altitudeAccuracy=null;
this.heading=null;
this.speed=null;
};
function Position(){
this.coords=null;
this.timestamp=null;
};
function PositionOptions(){
this.enableHighAccuracy=null;
this.timeout=null;
this.maximumAge=null;
};
function TransIdCbMap(){
this.TransactionID=null;
this.success_callback=null;
this.error_callback=null;
};
function __device_geolocation_descriptor(_5b){
this.interfaceName=_5b.interfaceName;
this.version=_5b.version;
};
function __device_geolocation_getCurrentPosition(_5c,_5d,_5e){
return this.provider.getLocation(_5c,_5d,_5e);
};
function __device_geolocation_watchPosition(_5f,_60,_61){
return this.provider.traceLocation(_5f,_60,_61);
};
function __device_geolocation_clearWatch(_62){
this.provider.clearTrace(_62);
};
function __device_geolocation(_63){
this.provider=_63;
this.interfaceName=_63.descriptor.interfaceName;
this.version=_63.descriptor.version;
this.getCurrentPosition=__device_geolocation_getCurrentPosition;
this.watchPosition=__device_geolocation_watchPosition;
this.clearWatch=__device_geolocation_clearWatch;
};
var __device_geolocation_service_entry={"name":null,"version":null,"proto":__device_geolocation,"descriptor":__device_geolocation_descriptor,"providers":[{"descriptor":__sp_location_descriptor,"instance":__sp_location_instance}]};
function __device_media_descriptor(_64){
this.interfaceName=_64.interfaceName;
this.version=_64.version;
};
function __device_media_getList(_65,_66,_67){
return this.provider.getList(_65,_66,_67);
};
function __device_media_getThumbnail(_68,_69,_6a){
return this.provider.getThumbnail(_68,_69,_6a);
};
function __device_media_addStreamUri(uri){
return this.provider.addStreamUri(uri);
};
function __device_media_deleteStreamUri(uri){
return this.provider.deleteStreamUri(uri);
};
function __device_media_cancel(_6d){
this.provider.cancel(_6d);
};
function __device_media_refreshMediaDb(uri){
this.provider.refreshMediaDb(uri);
};
function __device_media(_6f){
this.provider=_6f;
this.interfaceName=_6f.descriptor.interfaceName;
this.version=_6f.descriptor.version;
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
function __device_messaging_descriptor(_70){
this.interfaceName=_70.interfaceName;
this.version=_70.version;
};
function __device_messaging_startEditor(_71){
return this.provider.startEditor(_71);
};
function __device_messaging_getList(_72,_73,_74,_75,_76){
return this.provider.getList(_72,_73,_74,_75,_76);
};
function __device_messaging_send(_77,_78,id,_7a){
return this.provider.send(_77,_78,id,_7a);
};
function __device_messaging_setNotifier(_7b,_7c){
return this.provider.setNotifier(_7b,_7c);
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
function __device_messaging_setStatus(id,_80){
return this.provider.setStatus(id,_80);
};
function __device_messaging_cancel(_81){
return this.provider.cancel(_81);
};
function __device_messaging(_82){
this.provider=_82;
this.interfaceName=_82.descriptor.interfaceName;
this.version=_82.descriptor.version;
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
var __device_sensors_service_entry={"name":null,"version":null,"proto":__device_sensors,"descriptor":__device_sensors_descriptor,"providers":[{"descriptor":__sp_sensors_descriptor,"instance":__sp_sensors_instance}]};
function __device_sensors(_83){
this.provider=_83;
this.interfaceName=_83.descriptor.interfaceName;
this.version=_83.descriptor.version;
this.getChannels=__device_sensors_getChannels;
this.startChannel=__device_sensors_setNotifier;
this.stopChannel=__device_sensors_cancelNotifier;
this.getScaleFactor=__device_sensors_getScaleFactor;
};
function __device_sensors_descriptor(_84){
this.interfaceName=_84.interfaceName;
this.version=_84.version;
};
function __device_sensors_getChannels(){
return this.provider.getChannels();
};
function __device_sensors_setNotifier(_85,_86,_87){
return this.provider.startChannel(_85,_86,_87);
};
function __device_sensors_cancelNotifier(_88){
return this.provider.stopChannel(_88);
};
function __device_sensors_getScaleFactor(_89){
return this.provider.getScaleFactor(_89);
};
var __device_sysinfo_service_entry={"name":null,"version":null,"proto":__device_sysinfo,"descriptor":__device_sysinfo_descriptor,"providers":[{"descriptor":__sp_sysinfo_descriptor,"instance":__sp_sysinfo_instance}]};
function __device_sysinfo(_8a){
this.provider=_8a;
this.interfaceName=_8a.descriptor.interfaceName;
this.version=_8a.descriptor.version;
this.getChannelList=__device_channels_get;
this.getChannel=__device_sysinfo_get;
this.startChannel=__device_sysinfo_setNotifier;
this.stopChannel=__device_sysinfo_cancelNotifier;
this.cancel=__device_sysinfo_cancel;
};
function __device_sysinfo_descriptor(_8b){
this.interfaceName=_8b.interfaceName;
this.version=_8b.version;
};
function __device_channels_get(){
return this.provider.getChannelList();
};
function __device_sysinfo_get(_8c,_8d,_8e){
return this.provider.getChannel(_8c,_8d,_8e);
};
function __device_sysinfo_setNotifier(_8f,_90,_91,_92){
return this.provider.startChannel(_8f,_90,_91,_92);
};
function __device_sysinfo_cancelNotifier(_93){
return this.provider.stopChannel(_93);
};
function __device_sysinfo_cancel(id){
return this.provider.cancel(id);
};
var __device_landmarks_service_entry={"name":null,"version":null,"proto":__device_landmarks,"descriptor":__device_landmarks_descriptor,"providers":[{"descriptor":__sp_landmarks_descriptor,"instance":__sp_landmarks_instance}]};
function __device_landmarks(_95){
this.provider=_95;
this.interfaceName=_95.descriptor.interfaceName;
this.version=_95.descriptor.version;
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
function __device_landmarks_descriptor(_96){
this.interfaceName=_96.interfaceName;
this.version=_96.version;
};
function __device_landmarks_startEditor(_97,_98){
this.provider.startEditor(_97,_98);
};
function __device_landmarks_getCategories(_99,_9a,_9b){
return this.provider.getCategories(_99,_9a,_9b);
};
function __device_landmarks_getLandmarks(_9c,_9d,_9e){
return this.provider.getLandmarks(_9c,_9d,_9e);
};
function __device_landmarks_add_category(_9f,_a0,_a1){
return this.provider.addCategory(_9f,_a0,_a1);
};
function __device_landmarks_add_landmark(_a2,_a3,_a4){
return this.provider.addLandmark(_a2,_a3,_a4);
};
function __device_landmarks_delete_category(_a5,_a6,_a7){
return this.provider.deleteCategory(_a5,_a6,_a7);
};
function __device_landmarks_delete_landmark(_a8,_a9,_aa){
return this.provider.deleteLandmark(_a8,_a9,_aa);
};
function __device_landmarks_update_landmark(_ab,_ac,_ad){
return this.provider.updateLandmark(_ab,_ac,_ad);
};
function __device_landmarks_update_category(_ae,_af,_b0){
return this.provider.updateCategory(_ae,_af,_b0);
};
function __device_landmarks_import_landmarks(_b1,_b2,_b3,_b4){
return this.provider.importLandmarks(_b1,_b2,_b3,_b4);
};
function __device_landmarks_export_landmarks(_b5,_b6,_b7,_b8,_b9){
return this.provider.exportLandmarks(_b5,_b6,_b7,_b8,_b9);
};
function __device_landmarks_organize_landmarks(_ba,_bb,_bc,_bd,_be){
return this.provider.organizeLandmarks(_ba,_bb,_bc,_bd,_be);
};
function __device_landmarks_cancel(_bf){
return this.provider.cancel(_bf);
};
DeviceAPIError.prototype=new Error();
DeviceAPIError.prototype.constructor=DeviceAPIError;
function DeviceAPIError(_c0,_c1){
this.toString=concatenate;
this.code=_c0;
this.name="DeviceError";
this.message=_c1;
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
function DeviceException(_c2,_c3){
this.toString=concatenate;
this.code=_c2;
this.name="DeviceException";
this.message=_c3;
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
function splitErrorMessage(_c4){
if(_c4.search(/:/)!=-1){
if((_c4.split(":").length)==2){
return _c4.split(":")[1];
}
if((_c4.split(":").length)>2){
return _c4.split(":")[2];
}
}
return _c4;
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
function __s60_start_and_wait(id,_c6,_c7){
__s60_start_and_wait_cb=_c7;
widget.onhide=__s60_on_app_start;
widget.openApplication(id,_c6);
};
function __s60_api_not_supported(){
throw (err_ServiceNotSupported);
};
function __s60_enumerate_object(_c8,_c9,_ca,_cb){
var key;
for(key in _c8){
var _cd;
if(_c9){
_cd=_c9+"."+key;
}else{
_cd=key;
}
var _ce=_c8[key];
if(typeof _ce=="object"){
__s60_enumerate_object(_ce,_cd,_ca,_cb);
}else{
_ca(_cd,_ce,_cb);
}
}
};
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
function __sp_calendar_entry_time(_cf,end,_d1){
if(_cf){
var st=new Date(_cf);
this.begin=st;
}
if(end){
var en=new Date(end);
this.end=en;
}
if(_d1){
var al=new Date(_d1);
this.alarm=al;
}
};
function __sp_calendar_isInputValid(_d5){
if(_d5){
if(_d5.id){
if(typeof (_d5.id)!="string"){
return false;
}
}
if(_d5.type){
if((typeof (_d5.type)!="string")||!__sp_calendar_entry_types.match(_d5.type)){
return false;
}
}
if(_d5.text){
if(typeof (_d5.text)!="string"){
return false;
}
}
if(_d5.range){
if(typeof (_d5.range)!="object"){
return false;
}
if(_d5.range.begin){
if(typeof (_d5.range.begin)!="object"){
return false;
}
}
if(_d5.range.end){
if(typeof (_d5.range.end)!="object"){
return false;
}
}
}
if(_d5.summary){
if(typeof (_d5.summary)!="string"){
return false;
}
}
if(_d5.description){
if(typeof (_d5.description)!="string"){
return false;
}
}
if(_d5.status){
if(typeof (_d5.status)!="string"){
return false;
}
}
if(_d5.location){
if(typeof (_d5.location)!="string"){
return false;
}
}
if(_d5.priority){
if(typeof (_d5.priority)!="number"){
return false;
}
}
if(_d5.instanceStartTime){
if(typeof (_d5.instanceStartTime)!="object"){
return false;
}
}
if(_d5.exceptionDates){
if(typeof (_d5.exceptionDates)!="object"){
return false;
}
}
if(_d5.time){
if(typeof _d5.time!="object"){
return false;
}
if(_d5.time.begin){
if(typeof (_d5.time.begin)!="object"){
return false;
}
if(_d5.time.begin=="Invalid Date"){
return false;
}
try{
(_d5.time.begin).getTime();
}
catch(e){
return false;
}
}
if(_d5.time.end){
if(typeof (_d5.time.end)!="object"){
return false;
}
if(_d5.time.end=="Invalid Date"){
return false;
}
try{
(_d5.time.end).getTime();
}
catch(e){
return false;
}
}
if(_d5.time.begin&&_d5.time.end){
if(_d5.time.begin>_d5.time.end){
return false;
}
}
if(_d5.time.alarm){
if(typeof (_d5.time.alarm)!="object"){
return false;
}
try{
(_d5.time.alarm).getTime();
}
catch(e){
return false;
}
}
}
if(_d5.repeatRule){
if(typeof _d5.repeatRule!="object"){
return false;
}
if(_d5.repeatRule.frequency){
if(typeof (_d5.repeatRule.frequency)!="string"){
return false;
}
}
if(_d5.repeatRule.startDate){
if(typeof (_d5.repeatRule.startDate)!="object"){
return false;
}
if((_d5.repeatRule.startDate)=="Invalid Date"){
return false;
}
try{
(_d5.repeatRule.startDate).getTime();
}
catch(e){
return false;
}
}
if(_d5.repeatRule.untilDate){
if(typeof (_d5.repeatRule.untilDate)!="object"){
return false;
}
if((_d5.repeatRule.untilDate)=="Invalid Date"){
return false;
}
try{
(_d5.repeatRule.untilDate).getTime();
}
catch(e){
return false;
}
}
if(_d5.repeatRule.startDate&&_d5.repeatRule.untilDate){
if(_d5.repeatRule.startDate>_d5.repeatRule.untilDate){
return false;
}
}
if(_d5.repeatRule.interval){
if(typeof (_d5.repeatRule.interval)!="number"){
return false;
}
}
if(_d5.repeatRule.month){
if(typeof (_d5.repeatRule.month)!="number"){
return false;
}
}
if(_d5.repeatRule.weekDays){
if(typeof (_d5.repeatRule.weekDays)!="object"){
return false;
}
}
if(_d5.repeatRule.daysOfMonth){
if(typeof (_d5.repeatRule.daysOfMonth)!="object"){
return false;
}
}
if(_d5.repeatRule.monthDates){
if(typeof (_d5.repeatRule.monthDates)!="object"){
return false;
}
}
}
}
return true;
};
function __sp_calendar_getList_repeatRule(_d6){
var _d7;
switch(_d6.Type){
case 1:
_d7="daily";
this.frequency=_d7.toString();
break;
case 2:
_d7="weekly";
this.frequency=_d7.toString();
break;
case 3:
_d7="monthly";
this.frequency=_d7.toString();
break;
case 4:
_d7="yearly";
this.frequency=_d7.toString();
break;
default:
throw new DeviceException(err_bad_argument,"Calendar: Repeat Rule Type is Invalid");
}
if(_d6.StartDate){
this.startDate=new Date(_d6.StartDate);
}
if(_d6.UntilDate){
this.untilDate=new Date(_d6.UntilDate);
}
if(_d6.Interval){
this.interval=_d6.Interval;
}
if(_d6.DaysInWeek){
this.weekDays=[];
for(var a in _d6.DaysInWeek){
if(_d6.DaysInWeek[a]==6){
_d6.DaysInWeek[a]=0;
}else{
_d6.DaysInWeek[a]=_d6.DaysInWeek[a]+1;
}
this.weekDays.push(_d6.DaysInWeek[a]);
}
}
if(_d6.Month){
this.month=_d6.Month;
}
if(_d6.DaysOfMonth){
if(_d6.DaysOfMonth.Day){
if(_d6.DaysOfMonth.Day==6){
_d6.DaysOfMonth.Day=0;
}else{
_d6.DaysOfMonth.Day=_d6.DaysOfMonth.Day+1;
}
this.daysOfMonth.day=_d6.DaysOfMonth.Day;
}
if(_d6.DaysOfMonth.WeekNum){
this.daysOfMonth.weekInMonth=_d6.DaysOfMonth.WeekNum;
}
}
if(_d6.MonthDays){
this.monthDates=[];
for(var i=0;i<_d6.MonthDays.length;i++){
this.monthDates.push(_d6.MonthDays[i]-1);
}
}
};
function __sp_device_calendar_entry(_da){
if(_da.id){
this.id=_da.id;
}
if(_da.type){
this.type=_da.Type;
}
if(_da.Summary){
this.summary=_da.Summary;
}
if(_da.Description){
this.description=_da.Description;
}
if(_da.Location){
this.location=_da.Location;
}
if(_da.InstanceStartTime){
this.instanceStartTime=_da.InstanceStartTime;
}
if(_da.Priority>=0||_da.Priority<=255){
this.priority=_da.Priority;
}
if(_da.Status){
this.status=_da.Status;
}
if(_da.ExDates){
this.exceptionDates=_da.ExDates;
}
if(_da.RepeatRule){
this.repeatRule=new __sp_calendar_getList_repeatRule(_da.RepeatRule);
}
if(dataGetList==0){
this.time=new __sp_calendar_entry_time(_da.InstanceStartTime,_da.InstanceEndTime,_da.AlarmTime);
}else{
this.time=new __sp_calendar_entry_time(_da.StartTime,_da.EndTime,_da.AlarmTime);
}
};
function __sp_daysOfMonth_build(_db){
if(_db.day){
if(_db.day==0){
_db.day=6;
}else{
_db.day=_db.day-1;
}
this.Day=_db.day;
}
if(_db.weekInMonth){
this.WeekNum=_db.weekInMonth;
}
};
function __sp_calendar_addEntry_repeatRule(_dc,str){
try{
if(!(_dc.frequency)){
throw new DeviceException(MISSING_ARG_ERR,"Calendar: addEntry: frequency is missing");
}else{
var _de=_dc.frequency;
switch(_de){
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
throw new DeviceException(err_bad_argument,"Calendar: "+str+" Repeat Rule Type is Invalid");
}
if(_dc.startDate){
this.StartDate=_dc.startDate;
}
if(_dc.untilDate){
this.UntilDate=_dc.untilDate;
}
if(_dc.interval){
this.Interval=_dc.interval;
}
if(_dc.weekDays){
this.DaysInWeek=[];
for(var a in _dc.weekDays){
if(_dc.weekDays[a]==0){
_dc.weekDays[a]=6;
}else{
_dc.weekDays[a]=_dc.weekDays[a]-1;
}
this.DaysInWeek.push(_dc.weekDays[a]);
}
}
if(_dc.month){
this.Month=_dc.month;
}
if(_dc.monthDates){
this.MonthDays=[];
for(var i=0;i<_dc.monthDates.length;i++){
this.MonthDays.push(_dc.monthDates[i]-1);
}
}
if(_dc.daysOfMonth){
this.DaysOfMonth=new Array();
for(var a in _dc.daysOfMonth){
var _e1=new __sp_daysOfMonth_build(_dc.daysOfMonth[a]);
(this.DaysOfMonth).push(_e1);
}
}
}
}
catch(e){
__device_handle_exception(e,"__sp_calendar_addEntry_repeatRule: "+e);
}
};
function __sp_calendar_entry(_e2,str){
try{
if(_e2.type){
this.Type=_e2.type;
}
if(_e2.id){
this.id=_e2.id;
if(isUpdate){
if(_e2.time){
if(_e2.time.begin){
this.StartTime=_e2.time.begin;
}
if(_e2.time.end){
this.EndTime=_e2.time.end;
}
}
}
}
if(_e2.instanceStartTime){
this.InstanceStartTime=_e2.instanceStartTime;
}
if(_e2.description){
this.Description=_e2.description;
}else{
if(isUpdate&&(_e2.description==null)){
this.Description=" ";
}
}
if(_e2.summary){
this.Summary=_e2.summary;
}else{
if(isUpdate&&(_e2.summary==null)){
this.Summary=" ";
}
}
if(_e2.location){
this.Location=_e2.location;
}else{
if(isUpdate&&(_e2.location==null)){
this.Location=" ";
}
}
if(_e2.priority){
if((_e2.priority<0)||(_e2.priority>255)){
throw new DeviceException(INVALID_ARG_ERR,"Calendar: "+str+" Priority is Invalid");
}else{
this.Priority=_e2.priority;
}
}else{
if(isUpdate&&(_e2.priority==null)){
this.Priority=0;
}
}
if(_e2.status){
if(this.Type=="ToDo"){
this.Status="Todo"+_e2.status;
}else{
this.Status=_e2.status;
}
}else{
if(isUpdate&&(_e2.status==null)){
this.Status="Tentative";
}
}
if(_e2.exceptionDates){
this.ExDates=_e2.exceptionDates;
}
if(_e2.repeatRule){
this.RepeatRule=new __sp_calendar_addEntry_repeatRule(_e2.repeatRule,str);
}
if(_e2.type!=undefined&&_e2.type!=null){
if(typeof this.Type!="string"){
throw new DeviceException(INVALID_ARG_ERR,"Calendar: "+str+" Type is not a string");
}
switch(this.Type){
case "Meeting":
if(_e2.time){
if(_e2.time.begin){
this.StartTime=_e2.time.begin;
}
if(_e2.time.end){
this.EndTime=_e2.time.end;
}
}
break;
case "Reminder":
case "Anniversary":
if(_e2.time){
if(_e2.time.begin){
this.StartTime=_e2.time.begin;
}
}
break;
case "ToDo":
if(_e2.time){
if(_e2.time.end){
this.EndTime=_e2.time.end;
}
}
break;
case "DayEvent":
if(_e2.time){
if(_e2.time.begin){
this.StartTime=_e2.time.begin;
}
}
break;
default:
throw new DeviceException(INVALID_ARG_ERR,"Calendar: "+str+" Type is Invalid");
}
}
if(_e2.time){
if(_e2.time.alarm){
this.AlarmTime=_e2.time.alarm;
}
}
}
catch(e){
__device_handle_exception(e,"__sp_calendar_entry: "+e);
}
};
function __sp_calendar_iterator_get_next(){
var _e4=this.iter.getNext();
if(typeof _e4=="undefined"){
return null;
}
var _e5=new __sp_device_calendar_entry(_e4);
_e4.close();
return _e5;
};
function __sp_calendar_iterator(_e6){
this.iter=_e6;
this.next=__sp_calendar_iterator_get_next;
};
var CALENDAR_APP_ID=268458241;
function __sp_calendar_startEditor(_e7,_e8,_e9){
try{
if(!_e7){
throw new DeviceException(MISSING_ARG_ERR,"Calendar: startEditor: callback is missing");
}else{
if(typeof _e7!="function"){
throw new DeviceException(INVALID_ARG_ERR,"Calendar: startEditor: callback is invalid");
}
}
if(_e9){
if(typeof _e9!="function"){
throw new DeviceException(INVALID_ARG_ERR,"Calendar: startEditor: error callback is invalid");
}
}
if(_e8==null||_e8==undefined){
throw new DeviceException(INVALID_ARG_ERR,"Calendar: startEditor: entry is invalid");
}
var _ea=function(_eb,_ec,_ed){
var _ee=null;
_e7(_ee);
if(_ec!=event_cancelled){
var _ee=null;
if(_ed.ReturnValue){
_ee=new __sp_calendar_iterator(_ed.ReturnValue);
}
_e7(_ee);
}
if(_ed.ErrorCode!=0){
switch(_ed.ErrorCode){
case MISSING_ARG_ERR:
case INVALID_ARG_ERR:
case NOT_SUPPORTED_ERR:
if(_ed.ErrorMessage){
var _ef=splitErrorMessage(_ed.ErrorMessage);
throw new DeviceException(MapErrorCode[_ed.ErrorCode],"Calendar: startEditor: "+_ef);
}else{
throw new DeviceException(MapErrorCode[_ed.ErrorCode],"Calendar: startEditor: Operation Failed");
}
break;
default:
_e9(new DeviceException(MapErrorCode[_ed.ErrorCode],"Calendar: startEditor: Operation Failed"));
}
}
};
__s60_start_and_wait(CALENDAR_APP_ID,"",_ea);
return 0;
}
catch(e){
__device_handle_exception(e,"__sp_calendar_startEditor: "+e);
}
};
var __sp_calendar_entry_types="MeetingReminderToDoAnniversaryDayEvent";
function __sp_calendar_getList(_f0,_f1,_f2){
try{
if(_f1){
if(typeof _f1!="object"){
throw new DeviceException(INVALID_ARG_ERR,"Calendar: getList: match is invalid");
}
if(_f1.id){
dataGetList=1;
if(typeof _f1.id!="string"){
throw new DeviceException(INVALID_ARG_ERR,"Calendar: getList: match is invalid");
}
}else{
dataGetList=0;
}
}
if(!_f0){
throw new DeviceException(MISSING_ARG_ERR,"Calendar: getList: callback is missing");
}else{
if(typeof _f0!="function"){
throw new DeviceException(INVALID_ARG_ERR,"Calendar: getList: callback is invalid");
}
}
if(_f2){
if(typeof _f2!="function"){
throw new DeviceException(INVALID_ARG_ERR,"Calendar: getList: error callback is invalid");
}
if(_f2==undefined||_f2==null){
throw new DeviceException(MISSING_ARG_ERR,"Calendar: getList: error callback is missing");
}
}
var _f3=function(_f4,_f5,_f6){
if(_f6.ErrorCode!=0){
_f2(new DeviceException(_f6.ErrorCode,"Calendar: getList: Operation Failed"));
return;
}
if(_f5!=event_cancelled){
var _f7=null;
if(_f6.ReturnValue){
_f7=new __sp_calendar_iterator(_f6.ReturnValue);
}
_f0(_f7);
}
};
var _f8={};
modifyObjectBaseProp(_f8);
_f8.Type="IncludeAll";
if(_f1){
if(_f1.id){
_f8.id=_f1.id;
}
if((_f1.type)&&__sp_calendar_entry_types.match(_f1.type)){
_f8.Type=_f1.type;
}else{
if((_f1.type)&&typeof _f1.type!="string"){
throw new DeviceException(INVALID_ARG_ERR,"Calendar: getList: match is invalid");
}
}
if(_f1.range){
if(_f1.range.begin){
if(typeof (_f1.range.begin)!="object"){
throw new DeviceException(INVALID_ARG_ERR,"Calendar: getList: match is invalid");
}else{
if((_f1.range.begin)=="Invalid Date"){
throw new DeviceException(INVALID_ARG_ERR,"Calendar: getList: match is invalid");
}else{
_f8.StartRange=_f1.range.begin;
}
}
}
if(_f1.range.end){
if(typeof (_f1.range.end)!="object"){
throw new DeviceException(INVALID_ARG_ERR,"Calendar: getList: match is invalid");
}else{
if((_f1.range.end)=="Invalid Date"){
throw new DeviceException(INVALID_ARG_ERR,"Calendar: getList: match is invalid");
}else{
_f8.EndRange=_f1.range.end;
}
}
}
if((_f1.range.begin)&&(_f1.range.end)){
if((_f1.range.begin)>(_f1.range.end)){
throw new DeviceException(INVALID_ARG_ERR,"Calendar: getList: match is invalid");
}
}
}
if(_f1.text){
if(typeof (_f1.text)!="string"){
throw new DeviceException(INVALID_ARG_ERR,"Calendar: getList: match is invalid");
}else{
_f8.SearchText=_f1.text;
}
}
}
var _f9={};
modifyObjectBaseProp(_f9);
_f9.Type="CalendarEntry";
_f9.Filter=_f8;
var _fa=this.so.IDataSource.GetList(_f9,_f3);
if(_f9){
delete _f9.Type;
delete _f9.Filter;
}
if(_fa.ErrorCode!=0){
switch(_fa.ErrorCode){
case MISSING_ARG_ERR:
case INVALID_ARG_ERR:
case NOT_SUPPORTED_ERR:
if(_fa.ErrorMessage){
var _fb=splitErrorMessage(_fa.ErrorMessage);
throw new DeviceException(MapErrorCode[_fa.ErrorCode],"Calendar: getList: "+_fb);
}else{
throw new DeviceException(MapErrorCode[_fa.ErrorCode],"Calendar: getList: Operation Failed");
}
break;
default:
_f2(new DeviceException(MapErrorCode[_fa.ErrorCode],"Calendar: getList: Operation Failed"));
}
}
return _fa.TransactionID;
}
catch(e){
__device_handle_exception(e,"sp_calendar_getList: "+e);
}
};
function __sp_calendar_add(_fc){
if(_fc){
if(typeof _fc!="object"){
throw new DeviceException(INVALID_ARG_ERR,"Calendar: addEntry: calendarEntry param is invalid");
}
if(_fc.id){
_fc.id=undefined;
}
if(!_fc.type||!_fc.time){
throw new DeviceException(MISSING_ARG_ERR,"Calendar: addEntry: mandatory param missing");
}else{
if(typeof _fc.type!="string"||typeof _fc.time!="object"){
throw new DeviceException(INVALID_ARG_ERR,"Calendar: addEntry: mandatory param missing");
}
}
if((_fc.type!="ToDo")&&!_fc.time.begin){
throw new DeviceException(MISSING_ARG_ERR,"Calendar: addEntry: mandatory param StartTime missing");
}
if(!_fc.time.end&&(_fc.type=="ToDo"||_fc.type=="Meeting")){
throw new DeviceException(MISSING_ARG_ERR,"Calendar: addEntry: mandatory param EndTime missing");
}
if(_fc.time.end&&_fc.time.alarm){
if(_fc.time.end<_fc.time.alarm){
throw new DeviceException(NOT_SUPPORTED_ERR,"Calendar: addEntry: alarm time greater than end time:Not supported");
}
}
if(_fc.type=="ToDo"){
if(_fc.status==0){
if(typeof (_fc.status)!="string"){
throw new DeviceException(INVALID_ARG_ERR,"Calendar: addEntry: mandatory param missing");
}
}
}
if(_fc.repeatRule){
if(typeof _fc.repeatRule!="object"){
throw new DeviceException(INVALID_ARG_ERR,"Calendar: addEntry: repeatRule param type is invalid");
}
if(!_fc.repeatRule.frequency||_fc.repeatRule.frequency==null){
throw new DeviceException(MISSING_ARG_ERR,"Calendar: addEntry: mandatory param Frequency missing");
}
}
var _fd=__sp_calendar_isInputValid(_fc);
if(!_fd){
throw new DeviceException(INVALID_ARG_ERR,"Calendar: addEntry: calendarEntry param is invalid");
}
}else{
throw new DeviceException(MISSING_ARG_ERR,"Calendar: addEntry: mandatory param missing");
}
try{
var str="addEntry:";
var _ff={};
modifyObjectBaseProp(_ff);
_ff.Type="CalendarEntry";
_ff.Item=new __sp_calendar_entry(_fc,str);
var _100=this.so.IDataSource.Add(_ff);
if(_ff){
delete _ff.Type;
delete _ff.Item;
}
var _101="Operation Failed";
if(_100.ErrorMessage){
_101=splitErrorMessage(_100.ErrorMessage);
}
if(_100.ErrorCode!=0){
throw new DeviceException(MapErrorCode[_100.ErrorCode],"Calendar: addEntry: Operation Failed");
return;
}else{
var _102=_100.ReturnValue;
return _102;
}
}
catch(e){
__device_handle_exception(e,"__sp_calendar_add: "+e);
}
};
function __sp_calendar_update(_103){
isUpdate=1;
if(_103){
if(typeof _103!="object"){
throw new DeviceException(INVALID_ARG_ERR,"Calendar: updateEntry: calendarEntry param is invalid");
}
if(!_103.id){
throw new DeviceException(MISSING_ARG_ERR,"Calendar: updateEntry: mandatory param - Id missing");
}
if(_103.repeatRule){
if(typeof _103.repeatRule!="object"){
throw new DeviceException(INVALID_ARG_ERR,"Calendar: updateEntry: repeatRule param type is invalid");
}
if((_103.repeatRule.frequency==null||_103.repeatRule.frequency==undefined)){
throw new DeviceException(INVALID_ARG_ERR,"Calendar: updateEntry: repeatRule param type is invalid");
}
if(_103.repeatRule.startDate&&(_103.repeatRule.startDate==null||_103.repeatRule.startDate==undefined)){
throw new DeviceException(INVALID_ARG_ERR,"Calendar: updateEntry: repeatRule param type is invalid");
}
if(_103.repeatRule.untilDate&&(_103.repeatRule.untilDate==null||_103.repeatRule.untilDate==undefined)){
throw new DeviceException(INVALID_ARG_ERR,"Calendar: updateEntry: repeatRule param type is invalid");
}
}
if(_103.time){
if(_103.time.end&&_103.time.alarm){
if(_103.time.alarm>_103.time.end){
throw new DeviceException(NOT_SUPPORTED_ERR,"Calendar: updateEntry: alarm time greater than end time is not supported");
}
}
}
var _104=__sp_calendar_isInputValid(_103);
if(!_104){
throw new DeviceException(INVALID_ARG_ERR,"Calendar: updateEntry: calendarEntry param is invalid");
}
}else{
throw new DeviceException(MISSING_ARG_ERR,"Calendar: updateEntry: mandatory param missing");
}
try{
var str="updateEntry:";
var _106={};
modifyObjectBaseProp(_106);
_106.Type="CalendarEntry";
_106.Item=new __sp_calendar_entry(_103,str);
isUpdate=0;
var _107=this.so.IDataSource.Add(_106);
if(_106){
delete _106.Type;
delete _106.Item;
}
var _108="Operation Failed";
if(_107.ErrorMessage){
_108=splitErrorMessage(_107.ErrorMessage);
}
if(_107.ErrorCode!=0){
throw new DeviceException(MapErrorCode[_107.ErrorCode],"Calendar: addEntry: Operation Failed");
return;
}else{
var _109=_107.ReturnValue;
return _109;
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
throw new DeviceException(INVALID_ARG_ERR,"Calendar: deleteEntry: data is invalid");
}
if(!data.id){
throw new DeviceException(MISSING_ARG_ERR,"Calendar: deleteEntry: id is missing");
}
var _10b=__sp_calendar_isInputValid(data);
if(!_10b){
throw new DeviceException(INVALID_ARG_ERR,"Calendar: deleteEntry: delete data is invalid");
}
}else{
throw new DeviceException(MISSING_ARG_ERR,"Calendar: deleteEntry: data is missing");
}
var _10c={};
modifyObjectBaseProp(_10c);
_10c.Type="CalendarEntry";
_10c.Data={};
modifyObjectBaseProp(_10c.Data);
_10c.Data.IdList=[];
var list=[data.id];
_10c.Data.IdList=list;
if(data.range){
if(data.range.begin){
_10c.Data.StartRange=data.range.begin;
}
if(data.range.end){
_10c.Data.EndRange=data.range.end;
}
}
var rval=this.so.IDataSource.Delete(_10c);
if(_10c){
delete _10c.Type;
delete _10c.Data.IdList;
delete _10c.Data.StartRange;
delete _10c.Data.EndRange;
}
if(list){
delete list.id;
}
if(rval.ErrorCode!=0){
if(rval.ErrorMessage){
var _10f=splitErrorMessage(rval.ErrorMessage);
throw new DeviceException(MapErrorCode[rval.ErrorCode],"Calendar: deleteEntry: "+_10f);
}else{
throw new DeviceException(MapErrorCode[rval.ErrorCode],"Calendar: deleteEntry: Operation Failed");
}
}
}
catch(e){
__device_handle_exception(e,"__sp_calendar_delete: "+e);
}
};
function __sp_calendar_cancel(_110){
try{
if(!_110||_110==null||_110==undefined){
throw new DeviceException(MISSING_ARG_ERR,"Calendar: cancel: id is missing");
}
if(_110){
if(typeof _110!="number"){
throw new DeviceException(INVALID_ARG_ERR,"Calendar: cancel: id is missing");
}
}
var _111={};
modifyObjectBaseProp(_111);
_111.TransactionID=_110;
var _112=this.so.IDataSource.Cancel(_111);
if(_111){
delete _111.TransactionID;
}
if(_112.ErrorCode!=0){
if(_112.ErrorMessage){
var _113=splitErrorMessage(_112.ErrorMessage);
throw new DeviceException(MapErrorCode[_112.ErrorCode],"Calendar: cancel: "+_113);
}else{
throw new DeviceException(MapErrorCode[_112.ErrorCode],"Calendar: cancel: Operation Failed");
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
this.addEntry=__sp_calendar_add;
this.updateEntry=__sp_calendar_update;
this.deleteEntry=__sp_calendar_delete;
this.cancel=__sp_calendar_cancel;
this.so=null;
try{
this.so=device.getServiceObject("Service.Calendar","IDataSource");
}
catch(e){
__device_handle_exception(e,"Calendar service not available");
}
};
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
function __sp_startCamera(_114,_115){
if(_114==null){
throw new DeviceException(MISSING_ARG_ERR,"Camera:startCamera:callback is missing");
}
if(_114==undefined){
throw new DeviceException(INVALID_ARG_ERR,"Camera:startCamera:callback is a non-function");
}
if(typeof (_114)!="function"){
throw new DeviceException(INVALID_ARG_ERR,"Camera:startCamera:callback is a non-function");
}
if(_115){
if(typeof _115!="function"){
throw new DeviceException(INVALID_ARG_ERR,"Camera:startCamera:callback is invalid");
}
}
var _116=function(){
var _117=function(arg1,arg2,arg3){
var it=arg3.ReturnValue;
var item;
var _11d=[];
if(arg3.ErrorCode!=0){
_115(new DeviceException(arg3.ErrorCode,"Camera:startCamera: Operation Failed"));
return;
}
if((item=it.getNext())!=undefined){
var d=new Date(Date.parse(item.FileDate));
if(d>__sp_camera_start_date){
var _11f={};
modifyObjectBaseProp(_11f);
var _120=item.FileNameAndPath.replace(/\\/g,"/");
var _121="file:///";
var _122="";
_122=_122.concat(_121,_120);
_11f.uri=_122;
var _123={};
_123.height=item.XPixels;
_123.width=item.YPixels;
_123.type=item.MimeType;
_11f.format=_123;
_11d.unshift(_11f);
if(_123){
}
}
}
var _124=0;
var _125=0;
_114(_11d);
};
try{
var mso=device.getServiceObject("Service.MediaManagement","IDataSource");
}
catch(e){
__device_handle_exception(e,"media service not available : "+e);
}
var _127={};
modifyObjectBaseProp(_127);
_127.Type="FileInfo";
_127.Filter={};
modifyObjectBaseProp(_127.Filter);
_127.Filter.FileType="Image";
_127.Sort={};
modifyObjectBaseProp(_127.Sort);
_127.Sort.Key="FileDate";
_127.Sort.Order="Descending";
try{
var rval=mso.IDataSource.GetList(_127,_117);
}
catch(error){
__device_handle_exception(error,"media service GetList failed: "+error);
}
};
__sp_camera_start_date=new Date();
__s60_start_and_wait(CAMERA_APP_ID,"",_116);
var _129=0;
return _129;
};
function __sp_supportedSizes(){
try{
var _12a=device.getServiceObject("Service.SysInfo","ISysInfo");
}
catch(e){
__device_handle_exception(e,"SysInfo Service not available : "+e);
}
var _12b={};
modifyObjectBaseProp(_12b);
_12b.Entity="Camera";
_12b.Key="CameraProperties";
try{
var rval=_12a.ISysInfo.GetInfo(_12b);
if(_12b){
delete _12b.Entity;
delete _12b.Key;
}
}
catch(error){
__device_handle_exception(error,"Camera : Failed to fetch supported size Info: "+error);
}
var _12d=rval.ReturnValue;
var _12e=[];
var _12f=[];
_12e=_12d.ResolutionList;
for(var i=0;i<_12e.length;i++){
var _131="";
_131=_131.concat(_12e[i].height,"X",_12e[i].width);
_12f.push(_131);
}
return _12f;
};
function __sp_supportedMediaTypes(){
try{
var _132=device.getServiceObject("Service.SysInfo","ISysInfo");
}
catch(e){
__device_handle_exception(e,"SysInfo Service not available : "+e);
}
var _133={};
modifyObjectBaseProp(_133);
_133.Entity="Camera";
_133.Key="CameraProperties";
try{
var rval=_132.ISysInfo.GetInfo(_133);
if(_133){
delete _133.Entity;
delete _133.Key;
}
}
catch(error){
__device_handle_exception(error,"Camera :Failed to fetch supported media type Info: "+error);
}
var _135=rval.ReturnValue;
var _136=[];
_136=_135.MimeTypeList;
return _136;
};
function __sp_camera_instance(){
this.descriptor=new __sp_camera_descriptor();
this.supportedMediaTypes=__sp_supportedMediaTypes();
this.supportedSizes=__sp_supportedSizes();
this.startCamera=__sp_startCamera;
this.stopViewfinder=__s60_api_not_supported;
this.takePicture=__s60_api_not_supported;
};
var invoker_notification;
var error=new DeviceException(0,"dummy");
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
function __Notification(_137,_138){
this.connectionId=_137;
this.callback=_138;
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
function __device_commlog_item(_13e){
if(!_13e){
return null;
}
var evt={};
evt.type=__get_const_string(__sp_commlog_type_constants,_13e.EventType);
if(evt.type==null||evt.type==undefined){
return null;
}
evt.phoneNumber=_13e.PhoneNumber;
if(evt.phoneNumber==null||evt.phoneNumber==undefined||evt.phoneNumber.length==0){
evt.phoneNumber="private number";
}
evt.time=_13e.EventTime;
evt.flag=(_13e.Direction==undefined)?null:__get_const_string(__sp_commlog_constants_output,_13e.Direction);
evt.summary=_13e.Description;
evt.logId=Number(_13e.id);
evt.contactName=_13e.RemoteParty;
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
var _141=new __device_commlog_item(b1);
return _141;
}else{
var _142;
if(this.iter!=undefined&&this.iter!=null){
_142=this.iter.getNext();
}
if(typeof _142=="undefined"){
return null;
}
var rval=new __device_commlog_item(_142);
_142.close();
return rval;
}
};
function __sp_commlog_iterator_has_next(){
if(this.iter!=undefined&&this.iter!=null){
this.buffer=this.iter.getNext();
}
if((typeof this.buffer=="object")&&(this.buffer!=null)){
return true;
}else{
return false;
}
};
function __sp_commlog_iterator_close(){
};
function __sp_commlog_iterator(_144){
this.iter=_144;
this.buffer=null;
this.next=__sp_commlog_iterator_get_next;
this.hasNext=__sp_commlog_iterator_has_next;
this.close=__sp_commlog_iterator_close;
this.nofLogs=__nofLogs;
};
function __sp_commlog_getList(_145,_146,_147){
if(_145==null||_145==undefined){
throw new DeviceException(error.MISSING_ARG_ERR,"CommLog:getList:callback is Required");
}else{
if(typeof _145!="function"){
throw new DeviceException(error.INVALID_ARG_ERR,"CommLog:getList:Invalid Callback");
}
}
if(_147){
if(typeof (_147)!="function"){
throw new DeviceException(error.INVALID_ARG_ERR,"CommLog: getList: ErrorCallback is invalid");
}
}
if(_146!=null&&_146!=undefined){
if(typeof _146!="object"||__device_typeof(_146)=="Array"){
throw new DeviceException(error.INVALID_ARG_ERR,"CommLog: getList: Match is not an object");
}
if(_146.type!=null&&_146.type!=undefined){
if(typeof _146.type!="string"){
throw new DeviceException(error.INVALID_ARG_ERR,"CommLog: getList: Type is not a string");
}
}
if(_146.flag!=null&&_146.flag!=undefined){
if(typeof _146.flag!="string"){
throw new DeviceException(error.INVALID_ARG_ERR,"CommLog: getList: Flag is not a string");
}
if(_146.type){
if(_146.type.toLowerCase()=="sms"&&_146.flag.toLowerCase()=="missed"){
if(_147){
setTimeout(function(){
_147(new DeviceException(error.DATA_OUT_OF_RANGE_ERR,"commlogs: getList: Missed is not supported for sms"));
},1000);
return;
}else{
throw new DeviceError("commlogs: getList: Missed is not supported for sms",error.DATA_OUT_OF_RANGE_ERR);
}
}
}
}
if(_146.nofLogs!=null&&_146.nofLogs!=undefined){
if(typeof _146.nofLogs!="number"){
throw new DeviceException(error.INVALID_ARG_ERR,"CommLog: getList: nofLogs is invalid");
}
}
}
try{
var _148={};
modifyObjectBaseProp(_148);
_148.Type="Log";
_148.Filter={};
modifyObjectBaseProp(_148.Filter);
if(_146){
if(_146.type){
var _149;
_149=__get_const_val(__sp_commlog_type_constants,_146.type.toLowerCase());
if(_149!=undefined){
_148.Filter.EventType=_149;
}else{
if(_147){
setTimeout(function(){
_147(new DeviceException(error.DATA_OUT_OF_RANGE_ERR,"CommLog: getList: Type is out of range"));
},1000);
return;
}else{
throw new DeviceException(error.DATA_OUT_OF_RANGE_ERR,"CommLog: getList: Type is out of range");
}
}
}
if(_146.nofLogs!=null&&_146.nofLogs!=undefined){
if((_146.nofLogs<0)||(_146.nofLogs!=(_146.nofLogs|0))){
if(_147){
setTimeout(function(){
_147(new DeviceException(error.DATA_OUT_OF_RANGE_ERR,"CommLog: getList: nofLogs is out of range"));
},1000);
return;
}else{
throw new DeviceException(error.DATA_OUT_OF_RANGE_ERR,"CommLog: getList: nofLogs is out of range");
}
}
__nofLogs=_146.nofLogs;
}
if(_146.flag){
var _14a;
_14a=__get_const_val(__sp_commlog_constants,_146.flag.toLowerCase());
if(_14a!=undefined){
_148.Filter.Direction=_14a;
}else{
if(_147){
setTimeout(function(){
_147(new DeviceException(error.DATA_OUT_OF_RANGE_ERR,"CommLog: getList: Flag is out of range"));
},1000);
}else{
throw new DeviceException(error.DATA_OUT_OF_RANGE_ERR,"CommLog: getList: Flag is out of range");
}
}
}
if(_146.phoneNumber!=null&&_146.phoneNumber!=undefined){
if(_146.phoneNumber!=""){
_148.Filter.PhoneNumber=_146.phoneNumber;
}
}
if(_146.contactName!=null&&_146.contactName!=undefined){
if(_146.contactName!=""){
_148.Filter.RemoteParty=_146.contactName;
}
}
if(_146.startTime!=null&&_146.startTime!=undefined){
_148.Filter.StartTime=_146.startTime;
}
if(_146.endTime!=null&&_146.endTime!=undefined){
_148.Filter.EndTime=_146.endTime;
}
}
var _14b=function(arg1,arg2,arg3){
var _14f=_145;
var _150=_147;
var iter=null;
var _152=null;
if(arg3.ErrorCode!=0){
if(arg3.ErrorMessage){
_152=splitErrorMessage(arg3.ErrorMessage);
}else{
_152="operation failed";
}
if(_150){
setTimeout(function(){
_150(new DeviceException(MapErrorCode[arg3.ErrorCode],"Commlog: getList: "+_152));
},1000);
return;
}
}else{
if(arg3.ReturnValue){
iter=new __sp_commlog_iterator(arg3.ReturnValue);
}
}
if(arg2!=event_cancelled){
_14f(iter);
}
};
var _153=this.so.IDataSource.GetList(_148,_14b);
if(_148.Filter){
delete _148.Filter.Direction;
delete _148.Filter.EventType;
delete _148.Filter.PhoneNumber;
}
if(_148){
delete _148.Filter;
delete _148.Type;
}
if(_153.ErrorCode!=0){
var _154="operation failed";
if(_153.ErrorMessage){
_154=splitErrorMessage(_153.ErrorMessage);
}
switch(MapErrorCode[_153.ErrorCode]){
case error.INVALID_ARG_ERR:
case error.MISSING_ARG_ERR:
case error.NOT_SUPPORTED_ERR:
throw new DeviceException(MapErrorCode[_153.ErrorCode],"CommLog:getList:"+_154);
break;
default:
if(_147){
_147(new DeviceException(MapErrorCode[_153.ErrorCode],"CommLog:getList:"+_154));
return;
}else{
throw new DeviceException(MapErrorCode[_153.ErrorCode],"CommLog:getList:"+_154);
}
}
}
return _153.TransactionID;
}
catch(e){
__device_handle_exception(e,"__sp_commlog_Input_validation: "+e);
}
};
function __sp_commlog_setNotification(_155,_156){
if(!_155){
throw new DeviceException(error.MISSING_ARG_ERR,"CommLog:setNotification:callback is missing");
}
if(typeof _155!="function"){
throw new DeviceException(error.INVALID_ARG_ERR,"CommLog:setNotification:callback is invalid");
}
if(_156){
if(typeof (_156)!="function"){
throw new DeviceException(error.INVALID_ARG_ERR,"CommLog: setNotification: ErrorCallback is invalid");
}
}
invoker_notification=function(arg1,arg2,arg3){
var _15a=_155;
var _15b=_156;
var _15c=null;
if(arg3.ErrorCode!=0){
if(arg3.ErrorMessage){
_15d=splitErrorMessage(arg3.ErrorMessage);
}else{
_15d="operation failed";
}
if(_15b){
_15b(new DeviceException(MapErrorCode[arg3.ErrorCode],"CommLog: getList: "+_15d));
return;
}
}else{
if(arg3.ReturnValue){
_15c=new __device_commlog_item(arg3.ReturnValue);
}
}
if(arg2!=event_cancelled){
for(i in __notifArr){
if(arg1==__notifArr[i].connectionId){
var _15e=__notifArr[i];
break;
}
}
if(_15e){
_15e.callback(_15c);
}
}
};
for(i in __notifArr){
var _15f=__notifArr[i];
__notifArr.splice(i,1);
__notifCount=__notifArr.length;
this.so.IDataSource.Cancel({TransactionID:_15f.connectionId});
break;
}
var _160={};
modifyObjectBaseProp(_160);
_160.Type="Log";
_160.Filter={DelayTime:0};
var _161=this.so.IDataSource.RequestNotification(_160,invoker_notification);
__notifArr[__notifCount++]=new __Notification(_161.TransactionID,_155);
if(_160){
delete _160.Type;
}
if(_161.ErrorCode!=0){
var _15d="operation failed";
if(_161.ErrorMessage){
_15d=splitErrorMessage(_161.ErrorMessage);
}
switch(MapErrorCode[_161.ErrorCode]){
case error.INVALID_ARG_ERR:
case error.MISSING_ARG_ERR:
case error.NOT_SUPPORTED_ERR:
throw new DeviceException(MapErrorCode[_161.ErrorCode],"CommLog:setNotification:"+_15d);
break;
default:
if(_156){
setTimeout(function(){
_156(new DeviceException(MapErrorCode[_161.ErrorCode],"CommLog:setNotification:"+_15d));
},1000);
}else{
throw new DeviceException(MapErrorCode[_161.ErrorCode],"CommLog:setNotification:"+_15d);
}
}
}
};
function __sp_commlog_cancelNotification(){
for(i in __notifArr){
if(__notifArr[i].connectionId){
var _162=__notifArr[i];
__notifArr.splice(i,1);
__notifCount=__notifArr.length;
break;
}
}
if(_162){
var _163=this.so.IDataSource.Cancel({TransactionID:_162.connectionId});
if(_163.ErrorCode!=0){
var _164="operation failed";
if(_163.ErrorMessage){
_164=splitErrorMessage(_163.ErrorMessage);
}
}
}
};
function __sp_commlog_cancel(_165){
if(!_165){
throw new DeviceException(error.MISSING_ARG_ERR,"CommLog:cancel:transactionId is missing");
}
if(typeof _165!="number"){
throw new DeviceException(error.INVALID_ARG_ERR,"CommLog:cancel:transactionId is invalid");
}
var _166=this.so.IDataSource.Cancel({TransactionID:_165});
if(_166.ErrorCode!=0){
var _167="operation failed";
if(_166.ErrorMessage){
_167=splitErrorMessage(_166.ErrorMessage);
}
throw new DeviceException(MapErrorCode[_166.ErrorCode],"CommLog:cancel:"+_167);
}
};
function __sp_commlog_deleteLogEntry(_168){
if(_168==null||_168==undefined){
throw new DeviceException(error.MISSING_ARG_ERR,"CommLog:deleteLogEntry:logId is missing");
}
if(typeof _168!="number"){
throw new DeviceException(error.INVALID_ARG_ERR,"CommLog:deleteLogEntry:logId is invalid");
}
var _169={};
modifyObjectBaseProp(_169);
_169.Type="Log";
_169.Data={id:_168.toString()};
modifyObjectBaseProp(_169.Data);
var _16a=this.so.IDataSource.Delete(_169);
if(_16a.ErrorCode!=0){
var _16b="operation failed";
if(_16a.ErrorMessage){
_16b=splitErrorMessage(_16a.ErrorMessage);
}
throw new DeviceException(MapErrorCode[_16a.ErrorCode],"CommLog:deleteLogEntry:"+_16b);
}
};
function __sp_commlog_instance(){
this.descriptor=new __sp_commlog_descriptor();
this.getList=__sp_commlog_getList;
this.setNotification=__sp_commlog_setNotification;
this.cancelNotification=__sp_commlog_cancelNotification;
this.cancel=__sp_commlog_cancel;
this.deleteLogEntry=__sp_commlog_deleteLogEntry;
try{
this.so=device.getServiceObject("Service.Logging","IDataSource");
}
catch(e){
this.so=null;
__device_handle_exception(e,"commlog service not available");
}
};
nokia.device.contacts.SORT_ASCENDING=0;
nokia.device.contacts.SORT_DESCENDING=1;
var SORT_ASCENDING=0;
var SORT_DESCENDING=1;
function __sp_contacts_descriptor(){
this.interfaceName="contacts";
if(window.__Service_Interface_Ver){
this.version=__Service_Interface_Ver;
}else{
this.version=1;
}
};
function __s60_enumerate_contact_object(_16c,_16d,func,_16f){
try{
var key;
for(key in _16c){
var _171;
if(_16d){
_171=_16d+"."+key;
}else{
_171=key;
}
var _172=_16c[key];
if(_172 instanceof Array){
func(_171,_172,_16f);
}else{
if(_172 instanceof Date){
func(_171,_172,_16f);
}else{
if(typeof _172=="object"){
__s60_enumerate_contact_object(_172,_171,func,_16f);
}else{
func(_171,_172,_16f);
}
}
}
}
}
catch(e){
throw e;
}
};
function __sp_contact_extract(name,_174,_175){
switch(name){
case "name.last":
_175.LastName={};
modifyObjectBaseProp(_175.LastName);
_175.LastName.Label="Last name";
_175.LastName.Value=_174;
break;
case "name.first":
_175.FirstName={};
modifyObjectBaseProp(_175.FirstName);
_175.FirstName.Label="First name";
_175.FirstName.Value=_174;
break;
case "name.middle":
_175.MiddleName={};
modifyObjectBaseProp(_175.MiddleName);
_175.MiddleName.Label="Middle name";
_175.MiddleName.Value=_174;
break;
case "name.prefix":
_175.Prefix={};
modifyObjectBaseProp(_175.Prefix);
_175.Prefix.Label="Prefix";
_175.Prefix.Value=_174;
break;
case "name.suffix":
_175.Suffix={};
modifyObjectBaseProp(_175.Suffix);
_175.Suffix.Label="Suffix";
_175.Suffix.Value=_174;
break;
case "tel.land":
_175.LandPhoneGen={};
modifyObjectBaseProp(_175.LandPhoneGen);
_175.LandPhoneGen.Label="Landline";
_175.LandPhoneGen.Value=_174;
break;
case "tel.mobile":
_175.MobilePhoneGen={};
modifyObjectBaseProp(_175.MobilePhoneGen);
_175.MobilePhoneGen.Label="Mobile";
_175.MobilePhoneGen.Value=_174;
break;
case "tel.video":
_175.VideoNumberGen={};
modifyObjectBaseProp(_175.VideoNumberGen);
_175.VideoNumberGen.Label="Video";
_175.VideoNumberGen.Value=_174;
break;
case "tel.fax":
_175.FaxNumberGen={};
modifyObjectBaseProp(_175.FaxNumberGen);
_175.FaxNumberGen.Label="Fax";
_175.FaxNumberGen.Value=_174;
break;
case "tel.voip":
_175.VOIPGen={};
modifyObjectBaseProp(_175.VOIPGen);
_175.VOIPGen.Label="Voip";
_175.VOIPGen.Value=_174;
break;
case "tel.home.land":
_175.LandPhoneHome={};
modifyObjectBaseProp(_175.LandPhoneHome);
_175.LandPhoneHome.Label="Home Landline";
_175.LandPhoneHome.Value=_174;
break;
case "tel.home.mobile":
_175.MobilePhoneHome={};
modifyObjectBaseProp(_175.MobilePhoneHome);
_175.MobilePhoneHome.Label="Home Mobile";
_175.MobilePhoneHome.Value=_174;
break;
case "tel.home.video":
_175.VideoNumberHome={};
modifyObjectBaseProp(_175.VideoNumberHome);
_175.VideoNumberHome.Label="Home Video";
_175.VideoNumberHome.Value=_174;
break;
case "tel.home.fax":
_175.FaxNumberHome={};
modifyObjectBaseProp(_175.FaxNumberHome);
_175.FaxNumberHome.Label="Home Fax";
_175.FaxNumberHome.Value=_174;
break;
case "tel.home.voip":
_175.VOIPHome={};
modifyObjectBaseProp(_175.VOIPHome);
_175.VOIPHome.Label="Home Voip";
_175.VOIPHome.Value=_174;
break;
case "tel.work.land":
_175.LandPhoneWork={};
modifyObjectBaseProp(_175.LandPhoneWork);
_175.LandPhoneWork.Label="Work Landline";
_175.LandPhoneWork.Value=_174;
break;
case "tel.work.mobile":
_175.MobilePhoneWork={};
modifyObjectBaseProp(_175.MobilePhoneWork);
_175.MobilePhoneWork.Label="Work Mobile";
_175.MobilePhoneWork.Value=_174;
break;
case "tel.work.video":
_175.VideoNumberWork={};
modifyObjectBaseProp(_175.VideoNumberWork);
_175.VideoNumberWork.Label="Work Video";
_175.VideoNumberWork.Value=_174;
break;
case "tel.work.fax":
_175.FaxNumberWork={};
modifyObjectBaseProp(_175.FaxNumberWork);
_175.FaxNumberWork.Label="Work Fax";
_175.FaxNumberWork.Value=_174;
break;
case "tel.work.voip":
_175.VOIPWork={};
modifyObjectBaseProp(_175.VOIPWork);
_175.VOIPWork.Label="Work Voip";
_175.VOIPWork.Value=_174;
break;
case "address.street":
_175.AddrStreetGen={};
modifyObjectBaseProp(_175.AddrStreetGen);
_175.AddrStreetGen.Label="Street Address";
_175.AddrStreetGen.Value=_174;
break;
case "address.local":
_175.AddrLocalGen={};
modifyObjectBaseProp(_175.AddrLocalGen);
_175.AddrLocalGen.Label="City";
_175.AddrLocalGen.Value=_174;
break;
case "address.region":
_175.AddrRegionGen={};
modifyObjectBaseProp(_175.AddrRegionGen);
_175.AddrRegionGen.Label="State/Province";
_175.AddrRegionGen.Value=_174;
break;
case "address.code":
_175.AddrPostCodeGen={};
modifyObjectBaseProp(_175.AddrPostCodeGen);
_175.AddrPostCodeGen.Label="Postal code";
_175.AddrPostCodeGen.Value=_174;
break;
case "address.country":
_175.AddrCountryGen={};
modifyObjectBaseProp(_175.AddrCountryGen);
_175.AddrCountryGen.Label="Country";
_175.AddrCountryGen.Value=_174;
break;
case "address.email":
_175.EmailGen={};
modifyObjectBaseProp(_175.EmailGen);
_175.EmailGen.Label="EMail";
_175.EmailGen.Value=_174;
break;
case "address.uri":
_175.URLGen={};
modifyObjectBaseProp(_175.URLGen);
_175.URLGen.Label="Website";
_175.URLGen.Value=_174;
break;
case "address.home.street":
_175.AddrStreetHome={};
modifyObjectBaseProp(_175.AddrStreetHome);
_175.AddrStreetHome.Label="Home Address";
_175.AddrStreetHome.Value=_174;
break;
case "address.home.local":
_175.AddrLocalHome={};
modifyObjectBaseProp(_175.AddrLocalHome);
_175.AddrLocalHome.Label="City";
_175.AddrLocalHome.Value=_174;
break;
case "address.home.region":
_175.AddrRegionHome={};
modifyObjectBaseProp(_175.AddrRegionHome);
_175.AddrRegionHome.Label="State/Province";
_175.AddrRegionHome.Value=_174;
break;
case "address.home.code":
_175.AddrPostCodeHome={};
modifyObjectBaseProp(_175.AddrPostCodeHome);
_175.AddrPostCodeHome.Label="Postal code";
_175.AddrPostCodeHome.Value=_174;
break;
case "address.home.country":
_175.AddrCountryHome={};
modifyObjectBaseProp(_175.AddrCountryHome);
_175.AddrCountryHome.Label="Country";
_175.AddrCountryHome.Value=_174;
break;
case "address.home.email":
_175.EmailHome={};
modifyObjectBaseProp(_175.EmailHome);
_175.EmailHome.Label="Home EMail";
_175.EmailHome.Value=_174;
break;
case "address.home.uri":
_175.URLHome={};
modifyObjectBaseProp(_175.URLHome);
_175.URLHome.Label="Home Website";
_175.URLHome.Value=_174;
break;
case "address.work.street":
_175.AddrStreetWork={};
modifyObjectBaseProp(_175.AddrStreetWork);
_175.AddrStreetWork.Label="Work Address";
_175.AddrStreetWork.Value=_174;
break;
case "address.work.local":
_175.AddrLocalWork={};
modifyObjectBaseProp(_175.AddrLocalWork);
_175.AddrLocalWork.Label="City";
_175.AddrLocalWork.Value=_174;
break;
case "address.work.region":
_175.AddrRegionWork={};
modifyObjectBaseProp(_175.AddrRegionWork);
_175.AddrRegionWork.Label="State/Province";
_175.AddrRegionWork.Value=_174;
break;
case "address.work.code":
_175.AddrPostCodeWork={};
modifyObjectBaseProp(_175.AddrPostCodeWork);
_175.AddrPostCodeWork.Label="Postal code";
_175.AddrPostCodeWork.Value=_174;
break;
case "address.work.country":
_175.AddrCountryWork={};
modifyObjectBaseProp(_175.AddrCountryWork);
_175.AddrCountryWork.Label="Country";
_175.AddrCountryWork.Value=_174;
break;
case "address.work.email":
_175.EmailWork={};
modifyObjectBaseProp(_175.EmailWork);
_175.EmailWork.Label="Work EMail";
_175.EmailWork.Value=_174;
break;
case "address.work.uri":
_175.URLWork={};
modifyObjectBaseProp(_175.URLWork);
_175.URLWork.Label="Work Website";
_175.URLWork.Value=_174;
break;
case "company.name":
_175.CompanyName={};
modifyObjectBaseProp(_175.CompanyName);
_175.CompanyName.Label="Company";
_175.CompanyName.Value=_174;
break;
case "company.title":
_175.JobTitle={};
modifyObjectBaseProp(_175.JobTitle);
_175.JobTitle.Label="Title";
_175.JobTitle.Value=_174;
break;
case "id":
_175.id=_174;
break;
case "notes":
_175.Note={};
modifyObjectBaseProp(_175.Note);
_175.Note.Label="Note";
_175.Note.Value=_174;
break;
case "anniversary":
_175.Anniversary={};
modifyObjectBaseProp(_175.Anniversary);
_175.Anniversary.Label="Anniversary";
_175.Anniversary.Value=_174;
break;
case "birthday":
_175.Date={};
modifyObjectBaseProp(_175.Date);
_175.Date.Label="BirthDay";
_175.Date.Value=_174;
break;
case "nickName":
_175.SecondName={};
modifyObjectBaseProp(_175.SecondName);
_175.SecondName.Label="NickName";
_175.SecondName.Value=_174;
break;
case "photo":
_175.CallerObjImg={};
modifyObjectBaseProp(_175.CallerObjImg);
_175.CallerObjImg.Label="CallerObjImg";
_175.CallerObjImg.Value=_174;
break;
case "xspid":
_175.IMPP={};
modifyObjectBaseProp(_175.IMPP);
_175.IMPP.Label="IMPP";
_175.IMPP.Value=_174;
break;
}
};
function __s60_enumerate_build_contact_object(_176,_177,func,_179){
var key;
for(key in _176){
var _17b;
if(_177){
_17b=_177+"."+key;
}else{
_17b=key;
}
var _17c=_176[key];
if(_17b=="IMPP"){
func(_17b,_17c,_179);
}
if(typeof _17c=="object"){
__s60_enumerate_build_contact_object(_17c,_17b,func,_179);
}else{
func(_17b,_17c,_179);
}
}
};
function __sp_device_contact_extract(name,_17e,_17f){
if(name=="id"){
_17f.id=_17e;
return;
}
if(!name.match(".Value")){
return;
}
try{
if(name.match("IMPP.Value.0")){
_17f.xspid=[];
}
if(name.match("Name")){
if(name.match("CompanyName")){
if(!_17f.company){
_17f.company={};
}
}else{
if(!_17f.name){
_17f.name={};
}
}
}else{
if(name.match("Phone")||name.match("Number")||name.match("VOIP")||name.match("Voip")){
if(!_17f.tel){
_17f.tel={};
}
if(name.match("Home")){
if(!_17f.tel.home){
_17f.tel.home={};
}
}else{
if(name.match("Work")){
if(!_17f.tel.work){
_17f.tel.work={};
}
}
}
}else{
if(name.match("Addr")||name.match("Email")||name.match("URL")){
if(!_17f.address){
_17f.address={};
}
if(name.match("Home")){
if(!_17f.address.home){
_17f.address.home={};
}
}else{
if(name.match("Work")){
if(!_17f.address.work){
_17f.address.work={};
}
}
}
}else{
if(name.match("JobTitle")){
if(!_17f.company){
_17f.company={};
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
var _180=name.split(".");
var _181=_180[2];
if(_181!=undefined){
_17f.xspid[_180[2]]=_17e;
return;
}
}
switch(name){
case "LastName.Value":
_17f.name.last=_17e;
break;
case "FirstName.Value":
_17f.name.first=_17e;
break;
case "MiddleName.Value":
_17f.name.middle=_17e;
break;
case "Prefix.Value":
_17f.name.prefix=_17e;
break;
case "Suffix.Value":
_17f.name.suffix=_17e;
break;
case "LandPhoneGen.Value":
_17f.tel.land=_17e;
break;
case "MobilePhoneGen.Value":
_17f.tel.mobile=_17e;
break;
case "VideoNumberGen.Value":
_17f.tel.video=_17e;
break;
case "FaxNumberGen.Value":
_17f.tel.fax=_17e;
break;
case "VOIPGen.Value":
_17f.tel.voip=_17e;
break;
case "LandPhoneHome.Value":
_17f.tel.home.land=_17e;
break;
case "MobilePhoneHome.Value":
_17f.tel.home.mobile=_17e;
break;
case "VideoNumberHome.Value":
_17f.tel.home.video=_17e;
break;
case "FaxNumberHome.Value":
_17f.tel.home.fax=_17e;
break;
case "VoipHome.Value":
_17f.tel.home.voip=_17e;
break;
case "LandPhoneWork.Value":
_17f.tel.work.land=_17e;
break;
case "MobilePhoneWork.Value":
_17f.tel.work.mobile=_17e;
break;
case "VideoNumberWork.Value":
_17f.tel.work.video=_17e;
break;
case "FaxNumberWork.Value":
_17f.tel.work.fax=_17e;
break;
case "VoipWork.Value":
_17f.tel.work.voip=_17e;
break;
case "AddrStreetGen.Value":
_17f.address.street=_17e;
break;
case "AddrLocalGen.Value":
_17f.address.local=_17e;
break;
case "AddrRegionGen.Value":
_17f.address.region=_17e;
break;
case "AddrPostCodeGen.Value":
_17f.address.code=_17e;
break;
case "AddrCountryGen.Value":
_17f.address.country=_17e;
break;
case "EmailGen.Value":
_17f.address.email=_17e;
break;
case "URLGen.Value":
_17f.address.uri=_17e;
break;
case "AddrStreetHome.Value":
_17f.address.home.street=_17e;
break;
case "AddrLocalHome.Value":
_17f.address.home.local=_17e;
break;
case "AddrRegionHome.Value":
_17f.address.home.region=_17e;
break;
case "AddrPostCodeHome.Value":
_17f.address.home.code=_17e;
break;
case "AddrCountryHome.Value":
_17f.address.home.country=_17e;
break;
case "EmailHome.Value":
_17f.address.home.email=_17e;
break;
case "URLHome.Value":
_17f.address.home.uri=_17e;
break;
case "AddrStreetWork.Value":
_17f.address.work.street=_17e;
break;
case "AddrLocalWork.Value":
_17f.address.work.local=_17e;
break;
case "AddrRegionWork.Value":
_17f.address.work.region=_17e;
break;
case "AddrPostCodeWork.Value":
_17f.address.work.code=_17e;
break;
case "AddrCountryWork.Value":
_17f.address.work.country=_17e;
break;
case "EmailWork.Value":
_17f.address.work.email=_17e;
break;
case "URLWork.Value":
_17f.address.work.uri=_17e;
break;
case "CompanyName.Value":
_17f.company.name=_17e;
break;
case "JobTitle.Value":
_17f.company.title=_17e;
break;
case "Note.Value":
_17f.notes=_17e;
break;
case "Anniversary.Value":
_17f.anniversary=_17e;
break;
case "Date.Value":
_17f.birthday=_17e;
break;
case "SecondName.Value":
_17f.nickName=_17e;
break;
case "CallerObjImg.Value":
_17f.photo=_17e;
break;
default:
}
};
function __sp_device_contact_build(_182,_183){
__s60_enumerate_build_contact_object(_182,null,__sp_device_contact_extract,_183);
};
function __sp_contact_iterator_get_next(){
var _184=this.iter.getNext();
if(typeof _184=="undefined"){
return null;
}
var rval={};
__sp_device_contact_build(_184,rval);
_184.close();
return rval;
};
function __sp_contact_iterator(_186){
this.iter=_186;
this.next=__sp_contact_iterator_get_next;
};
function __s60_enumerate_group_object(_187,func,_189){
var key;
for(key in _187){
var _18b=key;
var _18c=_187[key];
func(_18b,_18c,_189);
}
};
function __sp_device_groupinfo_extract(name,_18e,_18f){
if(_18f.group==undefined){
_18f.group={};
}
if(name=="id"){
_18f.group.groupId=_18e;
}else{
if(name=="GroupLabel"){
_18f.group.groupName=_18e;
}else{
if(name=="Contents"){
_18f.contents=_18e;
}
}
}
return;
};
function __sp_device_groupinfo_build(_190,_191){
__s60_enumerate_group_object(_190,__sp_device_groupinfo_extract,_191);
};
function __sp_device_group_extract(name,_193,_194){
if(name=="id"){
_194.groupId=_193;
return;
}
if(name=="GroupLabel"){
_194.groupName=_193;
return;
}
};
function __sp_device_group_build(_195,_196){
__s60_enumerate_object(_195,null,__sp_device_group_extract,_196);
};
function __sp_group_iterator_get_next(){
var _197=this.iter.getNext();
if(typeof _197=="undefined"){
return null;
}
var rval={};
__sp_device_group_build(_197,rval);
_197.close();
return rval;
};
function __sp_group_iterator(_199){
this.iter=_199;
this.next=__sp_group_iterator_get_next;
};
var CONTACTS_APP_ID=270486734;
function __sp_contacts_startEditor(_19a,_19b,_19c){
if(!_19a){
throw new DeviceException(MISSING_ARG_ERR,"Contacts: StartEditor:Missing Success Callback");
}
if((typeof _19a)!="function"){
throw new DeviceException(INVALID_ARG_ERR,"Contacts: StartEditor:Invalid Success Callback");
}
if((_19b)==null){
_19b={};
}
if((typeof _19b)=="undefined"){
_19b={};
}
if((_19b)==undefined){
_19b={};
}
if((typeof _19b)!="object"){
throw new DeviceException(INVALID_ARG_ERR,"Contacts: StartEditor:Invalid Contact Data");
}
if(_19c){
if((typeof _19c)!="function"){
throw new DeviceException(INVALID_ARG_ERR,"Contacts :StartEditor:Invalid Error Callback");
}
}
var _19d=function(arg1,arg2,arg3){
var iter=null;
_19a(iter);
};
__s60_start_and_wait(CONTACTS_APP_ID,"",_19d);
return 0;
};
function __sp_contacts_getContacts(_1a2,_1a3,_1a4,_1a5){
var _1a6={};
modifyObjectBaseProp(_1a6);
_1a6.Type="Contact";
if(_1a3){
_1a6.Filter={};
modifyObjectBaseProp(_1a6.Filter);
_1a6.Filter.SearchVal=_1a3;
}
if(_1a4){
_1a6.Sort={};
modifyObjectBaseProp(_1a6.Sort);
if(typeof _1a4=="number"){
if(_1a4==SORT_ASCENDING||_1a4==SORT_ASCENDING){
_1a6.Sort.Order="Ascending";
}else{
if(_1a4==SORT_DESCENDING||_1a4==SORT_DESCENDING){
_1a6.Sort.Order="Descending";
}else{
_1a6.Sort.Order=_1a4;
}
}
}else{
throw new DeviceException(INVALID_ARG_ERR,"Contacts: getContacts: callback is invalid");
}
}
try{
if(!_1a2){
throw new DeviceException(MISSING_ARG_ERR,"Contacts: getContacts: callback is missing");
}else{
if(typeof _1a2!="function"){
throw new DeviceException(INVALID_ARG_ERR,"Contacts: getContacts: callback is invalid");
}
}
if(_1a5){
if(typeof (_1a5)!="function"){
throw new DeviceException(INVALID_ARG_ERR,"Contacts: getContacts: ErrorCallback is invalid");
}
}
var _1a7=function(arg1,arg2,arg3){
var iter=null;
var _1ac=_1a5;
if(arg3.ReturnValue){
iter=new __sp_contact_iterator(arg3.ReturnValue);
}else{
if(arg3.ErrorCode!=0){
var _1ad;
if(arg3.ErrorMessage){
_1ad=splitErrorMessage(arg3.ErrorMessage);
}else{
_1ad="Operation Failed";
}
_1ac(new DeviceException(MapErrorCode[arg3.ErrorCode],"Contacts: getContacts: "+_1ad));
return;
}
}
_1a2(iter);
};
var rval=this.so.IDataSource.GetList(_1a6,_1a7);
if(_1a6.Sort){
delete _1a6.Sort.Order;
}
if(_1a6.Filter){
delete _1a6.Filter.SearchVal;
}
if(_1a6){
delete _1a6.Type;
delete _1a6.Filter;
delete _1a6.Sort;
}
if(rval.ErrorCode!=0){
var _1af=mappingVerification(rval.ErrorCode);
if(_1af){
switch(MapErrorCode[rval.ErrorCode]){
case MISSING_ARG_ERR:
case INVALID_ARG_ERR:
case NOT_SUPPORTED_ERR:
if(rval.ErrorMessage){
var _1b0=splitErrorMessage(rval.ErrorMessage);
throw new DeviceException(MapErrorCode[rval.ErrorCode],"Contacts: getContacts: ");
}else{
throw new DeviceException(MapErrorCode[rval.ErrorCode],"Contacts: getContacts:Operation Failed");
}
break;
default:
_1a2(iter);
}
}else{
_1a2(iter);
}
}
return rval.TransactionID;
}
catch(e){
__device_handle_exception(e,"__sp_contacts_getContacts: "+e);
}
};
function __sp_contacts_add(_1b1){
var _1b2={};
modifyObjectBaseProp(_1b2);
__s60_enumerate_contact_object(_1b1,null,__sp_contact_extract,_1b2);
var _1b3={};
modifyObjectBaseProp(_1b3);
_1b3.Type="Contact";
_1b3.Data=_1b2;
try{
if(_1b2.id){
throw new DeviceException(NOT_SUPPORTED_ERR,"Contacts: addContact: Id Not Supported");
}
var _1b4=this.so.IDataSource.Add(_1b3);
if(_1b2){
delete _1b2.id;
}
if(_1b3){
delete _1b3.Type;
delete _1b3.Data;
}
var _1b5=_1b4["ReturnValue"];
if(_1b4.ErrorCode!=0){
var _1b6=mappingVerification(_1b4.ErrorCode);
if(_1b4.ErrorMessage){
var _1b7=splitErrorMessage(_1b4.ErrorMessage);
if(_1b6){
throw new DeviceException(MapErrorCode[_1b4.ErrorCode],"Contacts: addContact: "+_1b7);
}else{
throw new DeviceException(_1b4.ErrorCode,"Contacts: addContact: "+_1b7);
}
}else{
if(_1b6){
throw new DeviceException(MapErrorCode[_1b4.ErrorCode],"Contacts: addContact: Operation Failed");
}else{
throw new DeviceException(_1b4.ErrorCode,"Contacts: addContact: Operation Failed");
}
}
}
return _1b5;
}
catch(e){
__device_handle_exception(e,"__sp_contacts_addContact: "+e);
}
};
function __sp_contacts_update(_1b8){
try{
if(!(_1b8&&_1b8.id)){
throw new DeviceException(INVALID_ARG_ERR,"Contacts: updateContact: contact is missing");
}
var _1b9={};
modifyObjectBaseProp(_1b9);
__s60_enumerate_contact_object(_1b8,null,__sp_contact_extract,_1b9);
if(typeof _1b9.id!="string"){
throw new DeviceException(INVALID_ARG_ERR,"Contacts: updateContact: Invalid id type");
}
if(_1b9.id==undefined){
throw new DeviceException(INVALID_ARG_ERR,"Contacts: updateContact: Invalid id type");
}
var _1ba={};
modifyObjectBaseProp(_1ba);
_1ba.Type="Contact";
_1ba.Data=_1b9;
var _1bb=this.so.IDataSource.Add(_1ba);
if(_1b9){
delete _1b9.id;
}
if(_1ba){
delete _1ba.Type;
delete _1ba.Data;
}
if(_1bb.ErrorCode!=0){
var _1bc=mappingVerification(_1bb.ErrorCode);
if(_1bb.ErrorMessage){
var _1bd=splitErrorMessage(_1bb.ErrorMessage);
if(_1bc){
throw new DeviceException(MapErrorCode[_1bb.ErrorCode],"Contacts: updateContact: "+_1bd);
}else{
throw new DeviceException(_1bb.ErrorCode,"Contacts: updateContact: "+_1bd);
}
}else{
if(_1bc){
throw new DeviceException(MapErrorCode[_1bb.ErrorCode],"Contacts: updateContact: Operation Failed");
}else{
throw new DeviceException(_1bb.ErrorCode,"Contacts: updateContact: Operation Failed");
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
var _1bf={};
modifyObjectBaseProp(_1bf);
if(id==undefined){
throw new DeviceException(MISSING_ARG_ERR,"Contacts: deleteContacts: idlist is missing");
}
if(typeof id=="object"){
_1bf.IdList=id;
}else{
_1bf.IdList=[];
_1bf.IdList[0]=id;
}
var _1c0={};
modifyObjectBaseProp(_1c0);
_1c0.Type="Contact";
_1c0.Data=_1bf;
try{
var _1c1=this.so.IDataSource.Delete(_1c0);
if(_1bf){
delete _1bf.IdList;
}
if(_1c0){
delete _1c0.Type;
delete _1c0.Data;
}
if(_1c1.ErrorCode!=0){
var _1c2=mappingVerification(_1c1.ErrorCode);
if(_1c1.ErrorMessage){
var _1c3=splitErrorMessage(_1c1.ErrorMessage);
if(_1c2){
throw new DeviceException(MapErrorCode[_1c1.ErrorCode],"Contacts: deleteContacts: "+_1c3);
}else{
throw new DeviceException(_1c1.ErrorCode,"Contacts: deleteContacts: "+_1c3);
}
}else{
if(_1c2){
throw new DeviceException(MapErrorCode[_1c1.ErrorCode],"Contacts: deleteContacts: Operation Failed");
}else{
throw new DeviceException(_1c1.ErrorCode,"Contacts: deleteContacts: Operation Failed");
}
}
}
}
catch(e){
__device_handle_exception(e,"__sp_contacts_deleteContacts: "+e);
}
};
function __sp_contacts_get(id){
var _1c5={};
modifyObjectBaseProp(_1c5);
_1c5.Type="Contact";
if(id==null){
throw new DeviceException(MISSING_ARG_ERR,"Contacts: getContactInfo: callback is missing");
}
_1c5.Filter={};
modifyObjectBaseProp(_1c5.Filter);
_1c5.Filter.id=id;
try{
var rval=this.so.IDataSource.GetList(_1c5);
if(_1c5.Filter){
delete _1c5.Filter.id;
}
if(_1c5){
delete _1c5.Type;
delete _1c5.Filter;
}
if(rval){
if(rval.ErrorCode!=0){
var _1c7=mappingVerification(rval.ErrorCode);
if(rval.ErrorMessage){
var _1c8=splitErrorMessage(rval.ErrorMessage);
if(_1c7){
throw new DeviceException(MapErrorCode[rval.ErrorCode],"Contacts: getContactInfo: "+_1c8);
}else{
throw new DeviceException(rval.ErrorCode,"Contacts: getContactInfo: "+_1c8);
}
}else{
if(_1c7){
throw new DeviceException(MapErrorCode[rval.ErrorCode],"Contacts: getContactInfo: Operation Failed");
}else{
throw new DeviceException(rval.ErrorCode,"Contacts: getContactInfo: Operation Failed");
}
}
}
var _1c9={};
modifyObjectBaseProp(_1c9);
var _1ca=rval.ReturnValue.getNext();
__sp_device_contact_build(_1ca,_1c9);
return _1c9;
}
}
catch(e){
__device_handle_exception(e,"__sp_contacts_getContactInfo:"+e);
}
};
function __sp_contacts_addGroup(_1cb){
var _1cc={};
modifyObjectBaseProp(_1cc);
_1cc.GroupLabel=_1cb;
if(typeof (_1cc.GroupLabel)==null){
throw new DeviceException(MISSING_ARG_ERR,"Contacts: addGroups: callback is missing");
}
if((typeof _1cc.GroupLabel)=="undefined"){
throw new DeviceException(MISSING_ARG_ERR,"addGroup:Group Data Needed");
}
if((_1cc.GroupLabel)==undefined){
throw new DeviceException(MISSING_ARG_ERR,"addGroup:Group Data Needed");
}
var _1cd={};
modifyObjectBaseProp(_1cd);
_1cd.Type="Group";
_1cd.Data=_1cc;
try{
var _1ce=this.so.IDataSource.Add(_1cd);
if(_1cc){
delete _1cc.GroupLabel;
}
if(_1cd){
delete _1cd.Type;
delete _1cd.Data;
}
var _1cf=_1ce["ReturnValue"];
if(_1ce.ErrorCode!=0){
var _1d0=mappingVerification(_1ce.ErrorCode);
if(_1ce.ErrorMessage){
var _1d1=splitErrorMessage(_1ce.ErrorMessage);
if(_1d0){
throw new DeviceException(MapErrorCode[_1ce.ErrorCode],"Contacts: addGroup: "+_1d1);
}else{
throw new DeviceException(_1d1,_1ce.ErrorCode,"Contacts: addGroup: ");
}
}else{
if(_1d0){
throw new DeviceException(MapErrorCode[_1ce.ErrorCode],"Contacts: addGroup: Operation Failed");
}else{
throw new DeviceException(_1ce.ErrorCode,"Contacts: addGroup: Operation Failed");
}
}
}
return _1cf;
}
catch(e){
__device_handle_exception(e,"__sp_contacts_addGroup: "+e);
}
};
function __sp_contacts_getGroups(_1d2,_1d3){
var _1d4={};
modifyObjectBaseProp(_1d4);
_1d4.Type="Group";
try{
if(!_1d2){
throw new DeviceException(MISSING_ARG_ERR,"Contacts: getGroups: callback is missing");
}else{
if(typeof _1d2!="function"){
throw new DeviceException(INVALID_ARG_ERR,"Contacts: getGroups: callback is invalid");
}
}
if(_1d3){
if(typeof (_1d3)!="function"){
throw new DeviceException(INVALID_ARG_ERR,"Contacts: getGroups: ErrorCallback is invalid");
}
}
var _1d5=function(arg1,arg2,arg3){
var iter=null;
var _1da=_1d3;
iter=arg3.ReturnValue;
if(arg3.ReturnValue){
iter=new __sp_group_iterator(arg3.ReturnValue);
}else{
if(arg3.ErrorCode!=0){
var _1db;
if(arg3.ErrorMessage){
_1db=splitErrorMessage(arg3.ErrorMessage);
}else{
_1db="Operation Failed";
}
_1da(new DeviceException(_1db,MapErrorCode[arg3.ErrorCode],"Contacts: getGroups:"));
return;
}
}
_1d2(iter);
};
var rval=this.so.IDataSource.GetList(_1d4,_1d5);
if(_1d4){
delete _1d4.Type;
}
if(rval.ErrorCode!=0){
var _1dd=mappingVerification(result.ErrorCode);
if(_1dd){
switch(MapErrorCode[rval.ErrorCode]){
case MISSING_ARG_ERR:
case INVALID_ARG_ERR:
case NOT_SUPPORTED_ERR:
if(rval.ErrorMessage){
var _1de=splitErrorMessage(rval.ErrorMessage);
throw new DeviceException(MapErrorCode[rval.ErrorCode],"Contacts: getGroups: "+_1de);
}else{
throw new DeviceException(MapErrorCode[rval.ErrorCode],"Contacts: getGroups: Operation Failed");
}
break;
default:
_1d2(iter);
}
}else{
_1d2(iter);
}
}
return rval.TransactionID;
}
catch(e){
__device_handle_exception(e,"__sp_contacts_getGroups: "+e);
}
};
function __sp_contacts_deleteGroups(id){
var _1e0={};
modifyObjectBaseProp(_1e0);
var _1e1=[];
if(typeof id=="object"){
var i=0;
for(var val in id){
_1e1[i]=id[val];
i++;
}
}else{
_1e1[0]=id;
}
_1e0.IdList=[];
_1e0.IdList=_1e1;
var _1e4={};
modifyObjectBaseProp(_1e4);
_1e4.Type="Group";
_1e4.Data=_1e0;
try{
var _1e5=this.so.IDataSource.Delete(_1e4);
if(_1e5.ErrorCode!=0){
var _1e6=mappingVerification(_1e5.ErrorCode);
if(_1e5.ErrorMessage){
var _1e7=splitErrorMessage(_1e5.ErrorMessage);
if(_1e6){
throw new DeviceException(MapErrorCode[_1e5.ErrorCode],"Contacts: deleteGroups: "+_1e7);
}else{
throw new DeviceException(_1e5.ErrorCode,"Contacts: deleteGroups: "+_1e7);
}
}else{
if(_1e6){
throw new DeviceException(MapErrorCode[_1e5.ErrorCode],"Contacts: deleteGroups: Operation Failed");
}else{
throw new DeviceException(_1e5.ErrorCode,"Contacts: deleteGroups: Operation Failed");
}
}
}
}
catch(e){
__device_handle_exception(e,"__sp_contacts_deleteGroups: "+e);
}
};
function __sp_contacts_addContactsToGroup(_1e8,id1){
try{
var _1ea={};
modifyObjectBaseProp(_1ea);
var _1eb=false;
_1ea.Type="Group";
var map={};
modifyObjectBaseProp(map);
var _1ed=[];
if(typeof id1=="object"){
var i=0;
for(var val in id1){
_1ed[i]=id1[val];
i++;
}
}else{
_1ed[0]=id1;
}
map.IdList=_1ed;
_1eb=true;
delete _1ed.index;
if(_1e8!=undefined){
map.id=_1e8;
_1eb=true;
}
if(_1eb){
_1ea.Data=map;
}
_1ea.OperationType="Associate";
var _1f0=this.so.IDataSource.Organise(_1ea);
if(map){
delete map.id;
delete map.IdList;
}
if(_1ea){
delete _1ea.Data;
delete _1ea.OperationType;
delete _1ea.Type;
}
if(_1f0.ErrorCode!=0){
var _1f1=mappingVerification(_1f0.ErrorCode);
if(_1f0.ErrorMessage){
var _1f2=splitErrorMessage(_1f0.ErrorMessage);
if(_1f1){
throw new DeviceException(MapErrorCode[_1f0.ErrorCode],"Contacts: addContactsToGroup: "+_1f2);
}else{
throw new DeviceException(_1f0.ErrorCode,"Contacts: addContactsToGroup: "+_1f2);
}
}else{
if(_1f1){
throw new DeviceException(MapErrorCode[_1f0.ErrorCode],"Contacts: addContactsToGroup: Operation Failed");
}else{
throw new DeviceException(_1f0.ErrorCode,"Contacts: addContactsToGroup: Operation Failed");
}
}
}
}
catch(e){
__device_handle_exception(e,"__sp_contacts_addContactsToGroup: "+e);
}
};
function __sp_contacts_getContactIds(_1f3,_1f4,_1f5,_1f6){
var _1f7={};
var _1f8=_1f6;
modifyObjectBaseProp(_1f7);
_1f7.Type="Contact";
if(_1f4){
_1f7.Filter={};
modifyObjectBaseProp(_1f7.Filter);
_1f7.Filter.SearchVal=_1f4;
}
if(_1f5){
_1f7.Sort={};
modifyObjectBaseProp(_1f7.Sort);
if(typeof _1f5=="number"){
if(_1f5==SORT_ASCENDING){
_1f7.Sort.Order="Ascending";
}else{
if(_1f5==SORT_DESCENDING){
_1f7.Sort.Order="Descending";
}else{
_1f7.Sort.Order=_1f5;
}
}
}else{
throw new DeviceException(INVALID_ARG_ERR,"Contacts: getContactIds: callback is missing");
}
}
try{
if(!_1f3){
throw new DeviceException(MISSING_ARG_ERR,"Contacts: getContactIds: callback is missing");
}else{
if(typeof _1f3!="function"){
throw new DeviceException(INVALID_ARG_ERR,"Contacts: getContactIds: callback is invalid");
}
}
if(_1f6){
if(typeof (_1f6)!="function"){
throw new DeviceException(INVALID_ARG_ERR,"Contacts: getContactIds: ErrorCallback is invalid");
}
}
var _1f9=function(arg1,arg2,arg3){
var item=null;
var _1fe=null;
var _1ff=_1f6;
var id=null;
if(arg3["ReturnValue"]!=undefined){
item=arg3["ReturnValue"];
id=item["IdList"];
_1fe=[];
_1fe=id;
delete _1fe.index;
}else{
if(arg3.ErrorCode!=0){
var _201;
if(arg3.ErrorMessage){
_201=splitErrorMessage(arg3.ErrorMessage);
}else{
_201="Operation Failed";
}
_1ff(new DeviceException(MapErrorCode[arg3.ErrorCode],"Contacts: getContactIds:"+_201));
return;
}
}
_1f3(_1fe);
};
var rval=this.so.IDataSource.GetIds(_1f7,_1f9);
if(rval.ErrorCode!=0){
var _203=mappingVerification(rval.ErrorCode);
if(_203){
switch(MapErrorCode[rval.ErrorCode]){
case MISSING_ARG_ERR:
case INVALID_ARG_ERR:
case NOT_SUPPORTED_ERR:
if(rval.ErrorMessage){
var _204=splitErrorMessage(rval.ErrorMessage);
throw new DeviceException(MapErrorCode[rval.ErrorCode],"Contacts: getContactIds: "+_204);
}else{
throw new DeviceException(MapErrorCode[rval.ErrorCode],"Contacts: getContactIds: Operation Failed");
}
break;
default:
_1f3(idList);
}
}else{
_1f3(idList);
}
}
return rval.TransactionID;
}
catch(e){
__device_handle_exception(e,"__sp_contacts_getContactIds: "+e);
}
};
function __sp_contacts_getGroupIds(_205,_206){
var _207={};
modifyObjectBaseProp(_207);
_207.Type="Group";
try{
if(!_205){
throw new DeviceException(MISSING_ARG_ERR,"Contacts: getGroupIds: callback is missing");
}else{
if(typeof _205!="function"){
throw new DeviceException(INVALID_ARG_ERR,"Contacts: getGroupIds: callback is invalid");
}
}
if(_206){
if(typeof (_206)!="function"){
throw new DeviceException(INVALID_ARG_ERR,"Contacts: getGroupIds: ErrorCallback is invalid");
}
}
var _208=function(arg1,arg2,arg3){
var _20c=_206;
var item=null;
var _20e=[];
if(arg3.ReturnValue){
item=arg3["ReturnValue"];
arg3.ReturnValue.close();
var id=item["IdList"];
_20e=id;
}else{
if(arg3.ErrorCode!=0){
var _210;
if(rval.ErrorMessage){
_210=splitErrorMessage(rval.ErrorMessage);
}else{
_210="Operation Failed";
}
_20c(new DeviceException(MapErrorCode[arg3.ErrorCode],"Contacts: getGroupIds:"+_210));
return;
}
}
_205(_20e);
delete _20e.index;
};
var rval=this.so.IDataSource.GetIds(_207,_208);
if(_207){
delete _207.Type;
}
if(rval.ErrorCode!=0){
var _212=mappingVerification(rval.ErrorCode);
if(_212){
switch(rval.ErrorCode){
case MISSING_ARG_ERR:
case INVALID_ARG_ERR:
case NOT_SUPPORTED_ERR:
if(rval.ErrorMessage){
var _213=splitErrorMessage(rval.ErrorMessage);
throw new DeviceException(MapErrorCode[rval.ErrorCode],"Contacts: getGroupIds: "+_213);
}else{
throw new DeviceException(MapErrorCode[rval.ErrorCode],"Contacts: getGroupIds: Operation Failed");
}
break;
default:
_205(idList);
}
}else{
_205(idList);
}
}
return rval.TransactionID;
}
catch(e){
__device_handle_exception(e,"__sp_contacts_getGroupIds: "+e);
}
};
function __sp_contacts_removeContactsFromGroup(_214,id){
try{
var _216={};
modifyObjectBaseProp(_216);
var _217=false;
_216.Type="Group";
var map={};
if(id!=undefined){
var _219=[];
if(typeof id=="object"){
var i=0;
for(var val in id){
_219[i]=id[val];
i++;
}
}else{
_219[0]=id;
}
map.IdList=_219;
_217=true;
}
if(_214!=undefined){
map.id=_214;
_217=true;
}
if(_217){
_216.Data=map;
}
_216.OperationType="Disassociate";
var _21c=this.so.IDataSource.Organise(_216);
if(map){
delete map.IdList;
}
if(_216){
delete _216.Data;
delete _216.OperationType;
delete _216.Type;
}
if(_21c.ErrorCode!=0){
var _21d=mappingVerification(_21c.ErrorCode);
if(_21c.ErrorMessage){
var _21e=splitErrorMessage(_21c.ErrorMessage);
if(_21d){
throw new DeviceException(MapErrorCode[_21c.ErrorCode],"Contacts: removeContactsFromGroup: "+_21e);
}else{
throw new DeviceException(_21c.ErrorCode,"Contacts: removeContactsFromGroup: "+_21e);
}
}else{
if(_21d){
throw new DeviceException(MapErrorCode[_21c.ErrorCode],"Contacts: removeContactsFromGroup: Operation Failed");
}else{
throw new DeviceException(_21c.ErrorCode,"Contacts: removeContactsFromGroup: Operation Failed");
}
}
}
}
catch(e){
__device_handle_exception(e,"__sp_contacts_removeContactsFromGroup: "+e);
}
};
function __sp_contacts_cancel(_21f){
try{
var _220={};
if((_21f)==null){
throw new DeviceException(MISSING_ARG_ERR,"Contacts: cancel: "+_221);
}
if((_21f)==undefined){
throw new DeviceException(MISSING_ARG_ERR,"Contacts: cancel: "+_221);
}
if((typeof _21f)=="undefined"){
throw new DeviceException(MISSING_ARG_ERR,"Contacts: cancel: "+_221);
}
if(((typeof _21f)!="number")||(_21f<=0)){
throw new DeviceException(INVALID_ARG_ERR,"Contacts: cancel: "+_221);
}
modifyObjectBaseProp(_220);
_220.TransactionID=_21f;
var _222=this.so.IDataSource.Cancel(_220);
if(_220){
delete _220.TransactionID;
}
var _223=_222["ErrorCode"];
if(_223!=0){
var _224=mappingVerification(_222.ErrorCode);
if(_222["ErrorMessage"]){
var _221=splitErrorMessage(_222.ErrorMessage);
if(_224){
throw new DeviceException(MapErrorCode[_223],"Contacts: cancel: "+_221);
}else{
throw new DeviceException(_223,"Contacts: cancel: "+_221);
}
}else{
if(_224){
throw new DeviceException(MapErrorCode[_223],"Contacts: cancel: Operation Failed");
}else{
throw new DeviceException(_223,"Contacts: cancel: Operation Failed");
}
}
}
}
catch(e){
__device_handle_exception(e,"__sp_contacts_cancel: "+e);
}
};
function __sp_contacts_updateGroup(_225){
if(!(_225)){
throw new DeviceException(MISSING_ARG_ERR,"updateGroup:Invalid Group Data");
}
if((typeof _225)!="object"){
throw new DeviceException(INVALID_ARG_ERR,"updateGroup:Invalid Group Data");
}
try{
var _226={};
modifyObjectBaseProp(_226);
_226.Type="Group";
var _227={};
modifyObjectBaseProp(_227);
if(_225!=undefined){
if(_225.groupId!=undefined){
_227["id"]=_225.groupId;
}else{
throw new DeviceException(MISSING_ARG_ERR,"Contacts: updateGroup: Id input is mandatory");
}
if(_225.groupName!=undefined){
_227["GroupLabel"]=_225.groupName;
}
}
_226.Data=_227;
var _228=this.so.IDataSource.Add(_226);
if(_227){
delete _227.prototype;
}
if(_226){
delete _226.Data;
delete _226.Type;
}
if(_228.ErrorCode!=0){
var _229=mappingVerification(_228.ErrorCode);
if(_228.ErrorMessage){
var _22a=splitErrorMessage(_228.ErrorMessage);
if(_229){
throw new DeviceException(MapErrorCode[_228.ErrorCode],"Contacts: updateGroup: "+_22a);
}else{
throw new DeviceException(_228.ErrorCode,"Contacts: updateGroup: "+_22a);
}
}else{
if(_229){
throw new DeviceException(MapErrorCode[_228.ErrorCode],"Contacts: updateGroup: Operation Failed");
}else{
throw new DeviceException(_228.ErrorCode,"Contacts: updateGroup: Operation Failed");
}
}
}
}
catch(e){
__device_handle_exception(e,"__sp_contacts_updateGroup: "+e);
}
};
function __sp_contacts_getGroupInfo(_22b){
try{
var _22c={};
modifyObjectBaseProp(_22c);
_22c.Type="Group";
_22c.Filter={};
modifyObjectBaseProp(_22c.Filter);
if(_22b==undefined){
throw new DeviceException(MISSING_ARG_ERR,"Contacts: getGroupInfo: Id input is mandatory");
}
if((typeof _22b)!="string"){
throw new DeviceException(INVALID_ARG_ERR,"Contacts: getGroupInfo: Id input is mandatory");
}
_22c.Filter.id=_22b;
var rval=this.so.IDataSource.GetList(_22c);
if(_22c.Filter){
delete _22c.Filter.id;
}
if(_22c){
delete _22c.Filter;
delete _22c.Type;
}
if(rval){
if(rval.ErrorCode!=0){
var _22e=mappingVerification(rval.ErrorCode);
if(rval.ErrorMessage){
var _22f=splitErrorMessage(rval.ErrorMessage);
if(_22e){
throw new DeviceException(MapErrorCode[rval.ErrorCode],"Contacts: getGroupInfo: "+_22f);
}else{
throw new DeviceException(rval.ErrorCode,"Contacts: getGroupInfo: "+_22f);
}
}else{
if(_22e){
throw new DeviceException(MapErrorCode[rval.ErrorCode],"Contacts: getGroupInfo: Operation Failed");
}else{
throw new DeviceException(rval.ErrorCode,"Contacts: getGroupInfo: Operation Failed");
}
}
}else{
var _230={};
modifyObjectBaseProp(_230);
var _231=rval.ReturnValue.getNext();
__sp_device_groupinfo_build(_231,_230);
return _230;
}
}
}
catch(e){
__device_handle_exception(e,"__sp_contacts_getGroupInfo:"+e);
}
};
function mappingVerification(_232){
if(_232===1016||_232===1012||_232===1010||_232===1009||_232===1005||_232===1000||_232===1011||_232===1007||_232===1003||_232===1002){
return true;
}else{
return false;
}
};
function __sp_contacts_instance(){
this.descriptor=new __sp_contacts_descriptor();
this.startEditor=__sp_contacts_startEditor;
this.getContacts=__sp_contacts_getContacts;
this.addContact=__sp_contacts_add;
this.updateContact=__sp_contacts_update;
this.deleteContacts=__sp_contacts_delete;
this.getContactInfo=__sp_contacts_get;
this.addGroup=__sp_contacts_addGroup;
this.getGroups=__sp_contacts_getGroups;
this.deleteGroups=__sp_contacts_deleteGroups;
this.addContactsToGroup=__sp_contacts_addContactsToGroup;
this.getContactIds=__sp_contacts_getContactIds;
this.getGroupIds=__sp_contacts_getGroupIds;
this.removeContactsFromGroup=__sp_contacts_removeContactsFromGroup;
this.cancel=__sp_contacts_cancel;
this.updateGroup=__sp_contacts_updateGroup;
this.getGroupInfo=__sp_contacts_getGroupInfo;
try{
this.so=device.getServiceObject("Service.Contact","IDataSource");
}
catch(e){
__device_handle_exception(e,"Contacts service not available "+e);
}
};
function PositionError(){
this.UNKNOWN_ERROR=0;
this.PERMISSION_DENIED=1;
this.POSITION_UNAVAILABLE=2;
this.TIMEOUT=3;
this.code;
this.message;
};
function Coordinates(){
this.latitude=null;
this.longitude=null;
this.altitude=null;
this.accuracy=null;
this.altitudeAccuracy=null;
this.heading=null;
this.speed=null;
};
function Position(){
this.coords=null;
this.timestamp=null;
};
function PositionOptions(){
this.enableHighAccuracy;
this.timeout;
this.maximumAge;
};
var __sp_location_trace_transactionId=-1;
function __sp_location_handle_error(_233,_234,_235){
if((_233!=undefined)&&(typeof _233=="function")&&(_233!=null)){
var _236=new PositionError();
if((-21)==_234){
_236.code=_236.PERMISSION_DENIED;
_236.message="permission denied";
}else{
if((-33)==_234){
_236.code=_236.TIMEOUT;
_236.message="request timed out";
}else{
_236.code=_236.UNKNOWN_ERROR;
_236.message="UnKnown Error";
}
}
_233(_236);
}else{
var _236=new PositionError();
_236.code=_236.UNKNOWN_ERROR;
_236.message="UnKnown Error";
throw _236;
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
function __sp_getLocation(_237,_238,_239){
var _23a=this;
var _23b=function(arg1,arg2,arg3){
var _23f=_237;
var _240=_238;
if(arg3.ErrorCode){
__sp_location_handle_error(_240,arg3.ErrorCode,arg3.ErrorMessage);
return;
}else{
var _241=new Coordinates();
_241.longitude=(arg3.ReturnValue.Longitude==undefined)?null:arg3.ReturnValue.Longitude;
_241.latitude=(arg3.ReturnValue.Latitude==undefined)?null:arg3.ReturnValue.Latitude;
_241.altitude=(arg3.ReturnValue.Altitude==undefined)?null:arg3.ReturnValue.Altitude;
_241.accuracy=(arg3.ReturnValue.HorizontalAccuracy==undefined)?null:arg3.ReturnValue.HorizontalAccuracy;
_241.altitudeAccuracy=(arg3.ReturnValue.VerticalAccuracy==undefined)?null:arg3.ReturnValue.VerticalAccuracy;
_241.heading=(arg3.ReturnValue.Heading==undefined)?null:arg3.ReturnValue.Heading;
_241.speed=(arg3.ReturnValue.HorizontalSpeed==undefined)?null:arg3.ReturnValue.HorizontalSpeed;
var _242=new Position();
_242.coords={};
modifyObjectBaseProp(_242.coords);
_242.coords=_241;
_242.timestamp=new Date();
_23f(_242);
delete _242.timestamp;
delete _242;
delete _241;
}
};
if((_237==undefined)||(_237==null)||(typeof (_237)!="function")){
var _243="Wrong callback type";
__sp_location_handle_error(_238,0,_243);
}
if((_238!=undefined)){
if((_238!=null)&&(_238!="")&&(typeof (_238)!="function")){
var _244=new PositionError();
_244.code=-1;
throw _244;
}
}
var _245;
var _246={};
modifyObjectBaseProp(_246);
_246.LocationInformationClass="GenericLocationInfo";
var _247={};
modifyObjectBaseProp(_247);
_247.UpdateInterval=0;
if(_239!=undefined&&_239!=null){
if((typeof (_239)!="object")){
var _248="Wrong posOptions type";
__sp_location_handle_error(_238,0,_248);
return;
}
}
if(_239!=undefined){
if(_239.maximumAge!=undefined){
if(_239.maximumAge){
if((_239.maximumAge==Infinity)){
if((_239.enableHighAccuracy==undefined)||(typeof (_239.enableHighAccuracy)=="boolean")){
var arg3=this.so.ILocation.GetLastPosition();
if(arg3.ErrorCode<0){
var _248="Invalid input type";
__sp_location_handle_error(_238,0,_248);
return;
}
var _24a=new Coordinates();
_24a.longitude=(arg3.ReturnValue.Longitude==undefined)?null:arg3.ReturnValue.Longitude;
_24a.latitude=(arg3.ReturnValue.Latitude==undefined)?null:arg3.ReturnValue.Latitude;
_24a.altitude=(arg3.ReturnValue.Altitude==undefined)?null:arg3.ReturnValue.Altitude;
_24a.accuracy=(arg3.ReturnValue.HorizontalAccuracy==undefined)?null:arg3.ReturnValue.HorizontalAccuracy;
_24a.altitudeAccuracy=(arg3.ReturnValue.VerticalAccuracy==undefined)?null:arg3.ReturnValue.VerticalAccuracy;
_24a.heading=(arg3.ReturnValue.Heading==undefined)?null:arg3.ReturnValue.Heading;
_24a.speed=(arg3.ReturnValue.HorizontalSpeed==undefined)?null:arg3.ReturnValue.HorizontalSpeed;
var _24b=new Position();
_24b.coords={};
modifyObjectBaseProp(_24b.coords);
_24b.coords=_24a;
_24b.timestamp=new Date();
_237(_24b);
delete _24b.timestamp;
delete _24b;
delete _24a;
return;
}
}
if(!(isNaN(parseInt(_239.maximumAge)))){
if((_239.maximumAge==0)){
var _248="Invalid input type";
__sp_location_handle_error(_238,0,_248);
return;
}
_247.UpdateMaxAge=_239.maximumAge;
}else{
var _248="Invalid input type";
__sp_location_handle_error(_238,0,_248);
return;
}
}else{
if((_239.maximumAge==null)||(_239.maximumAge=="")){
}
}
}
if((_239.enableHighAccuracy!==undefined)){
if(_239.enableHighAccuracy==true){
_246.EnableHighAccuracy=_239.enableHighAccuracy;
}else{
if(_239.enableHighAccuracy==false){
_246.EnableHighAccuracy=_239.enableHighAccuracy;
}else{
if((_239.enableHighAccuracy==null)||(_239.enableHighAccuracy=="")){
}else{
if((typeof (_239.enableHighAccuracy)!="boolean")){
var _24c="Wrong value for enableHighAccuracy param";
__sp_location_handle_error(_238,0,_24c);
return;
}
}
}
}
}
if(_239.timeout!==undefined){
if((_239.timeout!==null)||((_239.timeout!==""))){
if((_239.timeout==Infinity)){
var _248="Invalid input type";
__sp_location_handle_error(_238,0,_248);
return;
}else{
if(!(isNaN(parseInt(_239.timeout)))){
if((_239.timeout<=2147483647)){
if((_239.timeout==0)){
var _248="Invalid input type";
__sp_location_handle_error(_238,0,_248);
return;
}
_247.UpdateTimeOut=_239.timeout;
}else{
var _248="Invalid input type";
__sp_location_handle_error(_238,0,_248);
return;
}
}
}
}else{
if((_239.timeout===null)||((_239.timeout===""))){
}else{
var _248="Invalid input type";
__sp_location_handle_error(_238,0,_248);
return;
}
}
}
}
_247.PartialUpdates=false;
_246.Updateoptions=_247;
try{
var rval=this.so.ILocation.GetLocation(_246,_23b);
delete _247;
delete _246;
if(rval.ErrorCode!=0){
__sp_location_handle_error(_238,rval.ErrorCode,rval.ErrorMessage);
return;
}
}
catch(e){
__device_handle_exception(e,"__sp_getLocation: "+e);
}
};
var __sp_location_trace_ucb=null;
var __sp_location_fail_cb=null;
function __sp_traceLocation(_24e,_24f,_250){
if((_24e==undefined)||(_24e==null)||(typeof (_24e)!="function")){
var _251="Wrong callback type";
__sp_location_handle_error(_24f,0,_251);
return;
}
if((typeof _24e!="function")){
var _251="Wrong callback type";
__sp_location_handle_error(_24f,0,_251);
return;
}
if((_24f!=undefined)){
if((_24f!=null)&&(_24f!="")&&(typeof (_24f)!="function")){
var _252=new PositionError();
_252.code=-1;
throw _252;
}
}
var _253=this;
var _254=function(arg1,arg2,arg3){
var _258=_24e;
var _259=_24f;
if(arg3.ErrorCode){
__sp_location_handle_error(_259,arg3.ErrorCode,arg3.ErrorMessage);
}else{
var _25a=new Coordinates();
_25a.longitude=(arg3.ReturnValue.Longitude==undefined)?null:arg3.ReturnValue.Longitude;
_25a.latitude=(arg3.ReturnValue.Latitude==undefined)?null:arg3.ReturnValue.Latitude;
_25a.altitude=(arg3.ReturnValue.Altitude==undefined)?null:arg3.ReturnValue.Altitude;
_25a.accuracy=(arg3.ReturnValue.HorizontalAccuracy==undefined)?null:arg3.ReturnValue.HorizontalAccuracy;
_25a.altitudeAccuracy=(arg3.ReturnValue.VerticalAccuracy==undefined)?null:arg3.ReturnValue.VerticalAccuracy;
_25a.heading=(arg3.ReturnValue.Heading==undefined)?null:arg3.ReturnValue.Heading;
_25a.speed=(arg3.ReturnValue.HorizontalSpeed==undefined)?null:arg3.ReturnValue.HorizontalSpeed;
var _25b=new Position();
_25b.coords={};
modifyObjectBaseProp(_25b.coords);
_25b.coords=_25a;
_25b.timestamp=new Date();
_258(_25b);
delete _25b.timestamp;
delete _25b;
delete _25a;
return;
}
};
var _25c={};
modifyObjectBaseProp(_25c);
_25c.UpdateInterval=0;
var _25d={};
modifyObjectBaseProp(_25d);
_25d.LocationInformationClass="GenericLocationInfo";
if(_250!=undefined&&_250!=null){
if((typeof (_250)!="object")){
var _251="Wrong posOptions type";
__sp_location_handle_error(_24f,0,_251);
return;
}
}
if(_250!=undefined){
if((_250.enableHighAccuracy!==undefined)){
if(_250.enableHighAccuracy==true){
_25d.EnableHighAccuracy=_250.enableHighAccuracy;
}else{
if(_250.enableHighAccuracy==false){
_25d.EnableHighAccuracy=_250.enableHighAccuracy;
}else{
if((_250.enableHighAccuracy==null)||(_250.enableHighAccuracy=="")){
}else{
if((typeof (_250.enableHighAccuracy)!="boolean")){
var _25e="Wrong value for enableHighAccuracy param";
__sp_location_handle_error(_24f,0,_25e);
return;
}
}
}
}
}
if(_250.timeout!==undefined){
if((_250.timeout!==null)||((_250.timeout!==""))){
if((_250.timeout==Infinity)){
var _251="Invalid input type";
__sp_location_handle_error(_24f,0,_251);
return;
}else{
if(!(isNaN(parseInt(_250.timeout)))){
if((_250.timeout==0)){
var _251="Invalid input type";
__sp_location_handle_error(_24f,0,_251);
return;
}
_25c.UpdateTimeOut=_250.timeout;
}
}
}else{
if((_250.timeout===null)||((_250.timeout===""))){
}else{
var _251="Invalid input type";
__sp_location_handle_error(_24f,0,_251);
return;
}
}
}
if(typeof _250.maximumAge!="undefined"){
if(_250.maximumAge==_infinity){
_25c.UpdateTimeOut=0;
_25c.UpdateMaxAge=2147483647;
}else{
if(!(isNaN(parseInt(_250.maximumAge)))){
_25c.UpdateMaxAge=_250.maximumAge;
}else{
if((_250.maximumAge===null)||((_250.maximumAge===""))){
}else{
var _251="Invalid input type";
__sp_location_handle_error(_24f,0,_251);
return;
}
}
}
}
}
_25c.PartialUpdates=false;
_25d.Updateoptions=_25c;
try{
var rval=this.so.ILocation.Trace(_25d,_254);
delete _25c;
delete _25d;
if(rval.ErrorCode!=0){
__sp_location_handle_error(_24f,rval.ErrorCode,rval.ErrorMessage);
return;
}
return rval.TransactionID;
}
catch(e){
__device_handle_exception(e,"__sp_traceLocation: "+e);
}
};
function __sp_clearTrace(_260){
if(typeof _260!="number"){
var _261="Invalid input type";
__sp_location_handle_error(fail_cb,0,_261);
}
var _262={TransactionID:_260};
try{
var _263=this.so.ILocation.Cancel(_262);
}
catch(e){
__device_handle_exception(e,"__sp_clearTrace: "+e);
}
};
function __sp_location_instance(){
this.descriptor=new __sp_location_descriptor();
this.getLocation=__sp_getLocation;
this.traceLocation=__sp_traceLocation;
this.clearTrace=__sp_clearTrace;
try{
this.so=device.getServiceObject("Service.Location","ILocation");
}
catch(e){
this.so=null;
__device_handle_exception(e,"Location service not available");
}
};
var FILESCHMLEN=7;
function __sp_media_descriptor(){
this.interfaceName="media";
if(window.__Service_Interface_Ver){
this.version=__Service_Interface_Ver;
}else{
this.version=1;
}
};
function __sp_device_media_item_build(_264){
if(!_264){
return null;
}
var _265={};
modifyObjectBaseProp(_265);
if(_264.FileNameAndPath){
var _266=_264.FileNameAndPath.replace(/\\/g,"/");
var _267="file://";
_265.uri=_267+_266;
}
if(_264.MediaType){
var _268=_264.MediaType;
switch(_268){
case 1:
case 2:
_265.type="audio";
break;
case 3:
_265.type="image";
break;
case 4:
_265.type="video";
break;
case 5:
_265.type="stream";
break;
default:
break;
}
}
if(_264.FileName){
if(_264.MediaType==3){
_265.title=_264.FileName;
}
}
if(_264.FileDate){
_265.date=new Date(Date.parse(_264.FileDate));
}
if(_264.FileSize){
_265.size=_264.FileSize;
}
if(_264.SongName){
_265.title=_264.SongName;
}
if(_264.Artist){
_265.artist=_264.Artist;
}
if(_264.Album){
_265.album=_264.Album;
}
if(_264.Genre){
_265.genre=_264.Genre;
}
if(_264.TrackNumber){
_265.track=_264.TrackNumber;
}
if(_264.Composer){
_265.composer=_264.Composer;
}
return _265;
};
function __sp_media_iterator_get_next(){
var item=this.iter.getNext();
if(typeof item=="undefined"){
return null;
}
var _26a=__sp_device_media_item_build(item);
item.close();
return _26a;
};
function __sp_media_iterator(_26b){
this.iter=_26b;
this.next=__sp_media_iterator_get_next;
};
function __sp_media_get_field_name(name,type){
if(typeof name!="string"){
throw new DeviceException(INVALID_ARG_ERR,"Media:getList:field is of invalid type");
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
if(typeof name!="string"){
throw new DeviceException(INVALID_ARG_ERR,"Media:getList:sortBy is of invalid type");
}
var _270=name.toLowerCase();
if(_270=="date"){
return "FileDate";
}else{
return __sp_media_get_field_name(name,type);
}
};
function __sp_media_get_date_objct(date){
var _272="";
_272=date.getFullYear().toString();
if(date.getMonth()<10){
_272=_272+("0")+(date.getMonth().toString());
}else{
_272=_272+(date.getMonth().toString());
}
var day=date.getDate()-1;
if(day<10){
_272=_272+("0")+(day.toString());
}else{
_272=_272+(day.toString());
}
_272=_272+(":");
if(date.getHours()<10){
_272=_272+("0")+(date.getHours().toString());
}else{
_272=_272+(date.getHours().toString());
}
if(date.getMinutes()<10){
_272=_272+("0")+(date.getMinutes().toString());
}else{
_272=_272+(date.getMinutes().toString());
}
if(date.getSeconds()<10){
_272=_272+("0")+(date.getSeconds().toString());
}else{
_272=_272+(date.getSeconds().toString());
}
return _272;
};
function __sp_media_getList(_274,_275,_276,_277){
if(!_274){
throw new DeviceException(MISSING_ARG_ERR,"Media:getList:Callback is missing");
}else{
if(typeof _274!="function"){
throw new DeviceException(INVALID_ARG_ERR,"Media:getList:Callback is of invalid type");
}
}
if(_277){
if(typeof _277!="function"){
throw new DeviceException(INVALID_ARG_ERR,"Media: getList: error callback is invalid");
}
}
var _278=function(arg1,arg2,arg3){
if(arg3.ErrorCode!=0){
_277(new DeviceException(arg3.ErrorCode,"Media: getList: Operation Failed"));
return;
}
if(arg2!=event_cancelled){
var iter=null;
if(arg3.ReturnValue){
iter=new __sp_media_iterator(arg3.ReturnValue);
}
_274(iter);
}
};
var _27d={};
modifyObjectBaseProp(_27d);
_27d.Type="FileInfo";
_27d.Filter={};
modifyObjectBaseProp(_27d.Filter);
_27d.Sort={};
modifyObjectBaseProp(_27d.Sort);
if(_275){
if(_275.type){
if(typeof _275.type!="string"){
throw new DeviceException(INVALID_ARG_ERR,"Media:getList:type is of invalid type");
}
switch(_275.type.toLowerCase()){
case "audio":
_27d.Filter.FileType="audio";
break;
case "image":
_27d.Filter.FileType="Image";
break;
case "video":
_27d.Filter.FileType="Video";
break;
case "stream":
_27d.Filter.FileType="StreamingURL";
break;
default:
throw new DeviceException(INVALID_ARG_ERR,"Media:getList: type is invalid");
}
if(_275.field!=null){
_27d.Filter.Key=__sp_media_get_field_name(_275.field.name,_27d.Filter.FileType);
if(_27d.Filter.Key==null){
throw new DeviceException(INVALID_ARG_ERR,"Media:getList:key is invalid");
}
if(_275.field.value){
_27d.Filter.StartRange=_275.field.value;
if(_27d.Filter.Key=="TrackNumber"){
_27d.Filter.EndRange=_275.field.value;
}
}
}else{
if(_275.dateRange){
if(typeof _275.dateRange!="object"){
throw new DeviceException(INVALID_ARG_ERR,"Media:getList:dateRange is of invalid type");
}
_27d.Filter.Key="FileDate";
if((typeof _275.dateRange.start!="undefined")&&(typeof _275.dateRange.end!="undefined")){
_27d.Filter.StartRange=__sp_media_get_date_objct(_275.dateRange.start);
_27d.Filter.EndRange=__sp_media_get_date_objct(_275.dateRange.end);
}else{
throw new DeviceException(MISSING_ARG_ERR,"Media:getList:start or end of dateRange is missing");
}
}
}
if(_275.sortBy){
_27d.Sort.Key=__sp_media_get_sortfield_name(_275.sortBy,_27d.Filter.FileType);
if(_27d.Sort.Key==null){
throw new DeviceException(INVALID_ARG_ERR,"Media:getList:sortBy is invalid");
}
}else{
_27d.Sort.Key="FileDate";
}
if(_276){
if(_276==SORT_ASCENDING){
_27d.Sort.Order="Ascending";
}else{
if(_276==SORT_DESCENDING){
_27d.Sort.Order="Descending";
}
}
}else{
_27d.Sort.Order="Ascending";
}
}else{
throw new DeviceException(MISSING_ARG_ERR,"Media:type is missing");
}
}else{
_27d.Filter.FileType="all";
_27d.Sort.Key="FileDate";
_27d.Sort.Order="Ascending";
}
try{
var rval=this.so.IDataSource.GetList(_27d,_278);
if(_27d.Sort){
delete _27d.Sort;
}
if(_27d.Filter.StartRange){
delete _27d.Filter.StartRange;
}
if(_27d.Filter.EndRange){
delete _27d.Filter.EndRange;
}
if(_27d.Filter){
delete _27d.Filter;
}
if(rval.ErrorCode!=0){
switch(MapErrorCode[rval.ErrorCode]){
case MISSING_ARG_ERR:
case INVALID_ARG_ERR:
case err_missing_argument:
case err_bad_argument:
case err_InvalidService_Argument:
case err_ServiceNotSupported:
if(rval.ErrorMessage){
var _27f=splitErrorMessage(rval.ErrorMessage);
throw new DeviceException(MapErrorCode[rval.ErrorCode],"Media:getList:"+_27f);
}else{
throw new DeviceException(MapErrorCode[rval.ErrorCode],"Media:getList:Operation failed");
}
break;
default:
_274(iter);
}
}
return rval.TransactionID;
}
catch(e){
__device_handle_exception(e,"__sp_media_getList: "+e);
}
};
function __sp_media_getThumbnail(_280,_281,_282){
if(!_280){
throw new DeviceException(MISSING_ARG_ERR,"Media:getThumbnail:Callback is missing");
}else{
if(typeof _280!="function"){
throw new DeviceException(INVALID_ARG_ERR,"Media:getList:Callback is invalid");
}
}
if(_282){
var _283=_282;
if(typeof _282!="function"){
throw new DeviceException(INVALID_ARG_ERR,"Media: getThumbnail: error callback is invalid");
}
}
var _284=function(arg1,arg2,arg3){
if(arg3.ErrorCode!=0){
_282(new DeviceException(arg3.ErrorCode,"Media: getThumbnail: Operation Failed"));
return;
}
if(arg2!=event_cancelled){
var _288=null;
if(arg3.ReturnValue){
_288=arg3.ReturnValue.replace(/\\/g,"/");
var _289="file://";
_288=_289+_288;
}
_280(_288);
}
};
var _28a={};
modifyObjectBaseProp(_28a);
if(_281){
if(typeof _281!="object"){
throw new DeviceException(INVALID_ARG_ERR,"Media:getThumbnail:thumbnailInfo is of invalid type object");
}
if(_281.uri){
if(typeof _281.uri!="string"){
throw new DeviceException(INVALID_ARG_ERR,"Media:getThumbnail:uri is not of type string");
}
if(_281.uri.search("file://")==0){
url=_281.uri.slice(FILESCHMLEN);
_28a.Url=url.replace(/\//g,"\\");
}else{
throw new DeviceException(INVALID_ARG_ERR,"Media:getThumbnail:uri is not in file protocol");
}
}else{
throw new DeviceException(MISSING_ARG_ERR,"Media:getThumbnail:uri is missing");
}
}else{
throw new DeviceException(MISSING_ARG_ERR,"Media:thumbnailInfo is missing");
}
if(_281.size){
if(typeof _281.size!="object"){
throw new DeviceException(INVALID_ARG_ERR,"Media:getThumbnail:size is not of type Object");
}
if((typeof _281.size.width=="undefined")&&(typeof _281.size.height=="undefined")){
throw new DeviceException(MISSING_ARG_ERR,"Media:thumbnailInfo should have atleast width or height");
}else{
var _28b={};
modifyObjectBaseProp(_28b);
if(typeof _281.size.width!="undefined"){
_28b.width=_281.size.width;
}
if(typeof _281.size.height!="undefined"){
_28b.height=_281.size.height;
}
_28a.ThumbnailSize=_28b;
delete _28b;
}
}
try{
var rval=this.so.IDataSource.GetThumbnail(_28a,_284);
delete _28a;
if(rval.ErrorCode!=0){
switch(MapErrorCode[rval.ErrorCode]){
case MISSING_ARG_ERR:
_282(new DeviceException(MISSING_ARG_ERR,"Media: getThumbnail: Operation Failed"));
break;
case NOT_SUPPORTED_ERR:
_282(new DeviceException(MapErrorCode[rval.ErrorCode],"Media:getThumbnail:"+_28d));
break;
case INVALID_ARG_ERR:
case NOT_SUPPORTED_ERR:
if(rval.ErrorMessage){
var _28d=splitErrorMessage(rval.ErrorMessage);
throw new DeviceException(MapErrorCode[rval.ErrorCode],"Media:getThumbnail:"+_28d);
}else{
throw new DeviceException(MapErrorCode[rval.ErrorCode],"Media:getThumbnail:Operation failed");
}
break;
default:
throw new DeviceException(MapErrorCode[rval.ErrorCode],"Media:getThumbnail:Operation failed");
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
function __sp_media_cancel(_291){
try{
var rval=this.so.IDataSource.Cancel(_291);
if(rval.ErrorCode!=0){
switch(rval.ErrorCode){
case err_missing_argument:
case err_bad_argument:
case err_InvalidService_Argument:
case err_ServiceNotSupported:
if(rval.ErrorMessage){
var _293=splitErrorMessage(rval.ErrorMessage);
throw new DeviceException(MapErrorCode[rval.ErrorCode],"Media:cancel:"+_293);
}else{
throw new DeviceException(MapErrorCode[rval.ErrorCode],"Media:cancel:Operation failed");
}
break;
default:
}
}
}
catch(e){
__device_handle_exception(e,"__sp_media_refreshMediaDb: "+e);
}
};
function __sp_media_instance(){
this.descriptor=new __sp_media_descriptor();
this.getList=__sp_media_getList;
this.getThumbnail=__sp_media_getThumbnail;
this.addStreamUri=__sp_media_addStreamUri;
this.deleteStreamUri=__sp_media_deleteStreamUri;
this.refreshMediaDb=__sp_media_refreshMediaDb;
this.cancel=__sp_media_cancel;
try{
this.so=device.getServiceObject("Service.MediaManagement","IDataSource");
}
catch(e){
this.so=null;
__device_handle_exception(e,"media service not available");
}
};
var FILE_SCHEME="file://";
var INVALID_URI_ERR=108;
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
this.send=__sp_messaging_send;
this.setNotifier=__sp_messaging_setNotifier;
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
try{
this.so=device.getServiceObject("Service.Messaging","IMessaging");
}
catch(e){
this.so=null;
__device_handle_exception(e,"Messaging service not available");
}
};
function __sp_attachment_build(_294){
if(!_294){
return null;
}
var _295={};
modifyObjectBaseProp(_295);
if(_294.uri){
if(typeof _294.uri!="string"){
throw new DeviceException(INVALID_ARG_ERR,"uri is invalid");
}
if(_294.uri.slice(0,7)==FILE_SCHEME){
if(_294.uri.charAt(7)=="/"){
if(_294.uri.charAt(9)!=":"){
throw new DeviceException(URI_NOT_FOUND_ERR,"specified uri not found");
}
_295.FileName=_294.uri.slice(8).replace(/\057/g,"\\");
if(_295.FileName.length>256){
throw new DeviceException(DATA_OUT_OF_RANGE_ERR,"uri is out of range");
}
}else{
if(_294.uri.charAt(8)!=":"){
throw new DeviceException(URI_NOT_FOUND_ERR,"specified uri not found");
}
_295.FileName=_294.uri.slice(7).replace(/\057/g,"\\");
if(_295.FileName.length>256){
throw new DeviceException(DATA_OUT_OF_RANGE_ERR,"uri is out of range");
}
}
}else{
throw new DeviceException(INVALID_URI_ERR,"uri is invalid");
}
}
return _295;
};
function __sp_message_build(_296,id){
if(!_296){
return null;
}
var _298={};
modifyObjectBaseProp(_298);
var _299=0;
_298.MessageParam={};
modifyObjectBaseProp(_298.MessageParam);
_298.MessageParam.LaunchEditor=false;
_298.MessageType=(_296.type==undefined||_296.type==null)?"SMS":_296.type;
if(_296.to){
if(typeof (_296.to)=="string"){
_298.To=_296.to;
}else{
if(__device_typeof(_296.to)=="Array"&&_296.to.length>0){
if(_296.to[0]){
_298.To=_296.to[0];
}
if(_296.to.length>1){
if(_296.to.slice(1)){
_298.MessageParam.To=_296.to.slice(1);
}
}
}else{
_298.To=_296.to;
}
}
}
if(_296.cc){
_298.MessageParam.Cc=_296.cc;
}
if(id){
if((typeof (id)=="string")&&!(isNaN(id))){
id=Number(id);
}
_298.MessageParam.TemplateId=id;
}
if(_298.MessageType=="SMS"){
if(_296.body){
_298.BodyText=_296.body;
}
}
if(_298.MessageType=="MMS"){
if(_296.body){
_298.BodyText=_296.body;
}
if(_296.subject){
if(typeof _296.subject=="string"&&_296.subject.length>256){
throw new DeviceException(DATA_OUT_OF_RANGE_ERR,"subject length is greater than 256 characters");
}
_298.Subject=_296.subject;
}
if(_296.attachments){
_298.MessageParam.AttachmentList=[];
for(var a in _296.attachments){
if(typeof _296.attachments[a]=="object"&&__device_typeof(_296.attachments[a])!="Array"){
_298.MessageParam.AttachmentList.push(__sp_attachment_build(_296.attachments[a]));
_299=1;
}
}
if(_299==0){
throw new DeviceException(INVALID_ARG_ERR,"uri is invalid");
}
}
}
return _298;
};
function __sp_device_attachment_build(_29b){
if(!_29b){
return null;
}
var _29c={};
_29c.uri=FILE_SCHEME+_29b.FileName;
return _29c;
};
function __sp_device_message_build(_29d){
if(!_29d){
return null;
}
var _29e={};
_29e.body=null;
_29e.subject=null;
_29e.attachments=null;
_29e.to=null;
_29e.cc=null;
_29e.type=_29d.MessageType;
if(_29d.BodyText){
_29e.body=_29d.BodyText;
}
if(_29d.to){
_29e.to=_29d.To;
}
if(_29d.Subject){
_29e.subject=_29d.Subject;
}
_29e.attachment=false;
if(_29e.type=="MMS"){
if(_29d.Cc){
_29e.cc=_29d.Cc;
}
if(_29d.AttachmentList){
_29e.attachment=true;
_29e.attachments=[];
for(var a in _29d.AttachmentList){
if(_29d.AttachmentList.hasOwnProperty("a")){
_29e.attachments.push(__sp_device_attachment_build(_29d.AttachmentList[a]));
}
}
}
}
return _29e;
};
function __sp_device_message_info_build_notifier(_2a0){
if(!_2a0){
return null;
}
var _2a1={};
_2a1.message={};
_2a1.message.type=_2a0.MessageType;
_2a1.sender=_2a0.Sender;
_2a1.message.subject=_2a0.Subject;
_2a1.time=_2a0.Time;
_2a1.attachments=(_2a0.Attachments==undefined||_2a0.Attachments==null)?(!(_2a0.AttachmentList==undefined||_2a0.AttachmentList==null)):_2a0.Attachments;
_2a1.unread=_2a0.Unread;
_2a1.id=(_2a0.MessageId).toString();
return _2a1;
};
function __sp_device_message_info_build(_2a2){
if(!_2a2){
return null;
}
var _2a3={};
_2a3.message=__sp_device_message_build(_2a2);
_2a3.sender=_2a2.Sender;
_2a3.time=_2a2.Time;
_2a3.unread=_2a2.Unread;
_2a3.id=(_2a2.MessageId).toString();
return _2a3;
};
function __sp_message_iterator_get_next(){
var _2a4=this.iter.getNext();
if(typeof _2a4=="undefined"){
return null;
}
var _2a5=__sp_device_message_info_build(_2a4);
_2a4.close();
return _2a5;
};
function __sp_message_iterator(_2a6){
this.iter=_2a6;
this.next=__sp_message_iterator_get_next;
};
function __sp_messaging_getList(_2a7,_2a8,_2a9,_2aa,_2ab){
a("in getlist");
if(!_2a7){
throw new DeviceException(MISSING_ARG_ERR,"Messaging:getList:callback is missing");
}else{
if(typeof _2a7!="function"){
throw new DeviceException(INVALID_ARG_ERR,"Messaging:getList:callback is not a function");
}
}
if(_2a8!=null&&_2a8!=undefined&&typeof _2a8!="object"){
throw new DeviceException(INVALID_ARG_ERR,"Messaging:getList:match is invalid");
}
if(_2a9!=null&&_2a9!=undefined&&typeof _2a9!="number"){
throw new DeviceException(INVALID_ARG_ERR,"Messaging:getList:sortkey is invalid");
}
if(_2aa!=null&&_2aa!=undefined&&typeof _2aa!="number"){
throw new DeviceException(INVALID_ARG_ERR,"Messaging:getList:sortorder is invalid");
}
if(_2a9!=null&&_2a9!=undefined&&typeof _2a9=="number"){
if((_2a9!=0)&&(_2a9!=1)){
throw new DeviceException(INVALID_ARG_ERR,"Messaging:getList:sortkey is invalid");
}
}
if(_2aa!=null&&_2aa!=undefined&&typeof _2aa=="number"){
if((_2aa!=0)&&(_2aa!=1)){
throw new DeviceException(INVALID_ARG_ERR,"Messaging:getList:sortorder is invalid");
}
}
if(_2ab){
if(typeof (_2ab)!="function"){
throw new DeviceException(INVALID_ARG_ERR,"Messaging: startEditor: ErrorCallback is invalid");
}
}
var _2ac=function(arg1,arg2,arg3){
var _2b0=_2a7;
var _2b1=_2ab;
var iter=null;
if(arg3.ErrorCode!=0){
if(arg3.ErrorMessage){
_2b3=splitErrorMessage(arg3.ErrorMessage);
}else{
_2b3="Operation Failed";
}
if(_2b1){
_2b1(new DeviceException(MapErrorCode[arg3.ErrorCode],"Messaging: getList: "+_2b3));
return;
}
}else{
if(arg3.ReturnValue){
iter=new __sp_message_iterator(arg3.ReturnValue);
}
}
if(arg2!=event_cancelled){
_2b0(iter);
}
};
var _2b4={};
modifyObjectBaseProp(_2b4);
_2b4.Type="Inbox";
_2b4.Filter={};
modifyObjectBaseProp(_2b4.Filter);
if(_2a8){
if(_2a8.type!=null&&_2a8.type!=undefined){
_2b4.Filter.MessageTypeList=_2a8.type;
}
if(_2a8.senders!=null&&_2a8.senders!=undefined){
_2b4.Filter.SenderList=_2a8.senders;
}
if(_2a8.subject!=null&&_2a8.subject!=undefined){
if(_2a8.subject.length>256){
if(_2ab){
_2ab(new DeviceException(DATA_OUT_OF_RANGE_ERR,"Messaging:getList:subject is out of range"));
return;
}else{
throw new DeviceException(DATA_OUT_OF_RANGE_ERR,"Messaging:getList:subject is out of range");
}
}else{
_2b4.Filter.Subject=_2a8.subject;
}
}
if(_2a8.start!=null&&_2a8.start!=undefined){
_2b4.Filter.StartDate=_2a8.start;
}
if(_2a8.end!=null&&_2a8.end!=undefined){
_2b4.Filter.EndDate=_2a8.end;
}
}
if(_2a9||_2aa){
_2b4.SortOrder={};
modifyObjectBaseProp(_2b4.SortOrder);
if(_2a9){
if((_2a9==this.SORT_BY_DATE)){
_2b4.SortOrder.Key="Date";
}else{
if((_2a9==this.SORT_BY_SENDER)){
_2b4.SortOrder.Key="Sender";
}
}
}else{
_2b4.SortOrder.Key="Date";
}
if(_2aa){
if((_2aa==this.SORT_ASCENDING)){
_2b4.SortOrder.Order="Ascending";
}else{
if((_2aa==this.SORT_DESCENDING)){
_2b4.SortOrder.Order="Descending";
}
}
}else{
_2b4.SortOrder.Order="Ascending";
}
}
try{
var _2b5=this.so.IMessaging.GetList(_2b4,_2ac);
if(_2b4){
delete _2b4.Filter;
delete _2b4.SortOrder;
delete _2b4.Type;
}
if(_2b5.ErrorCode!=0){
var _2b3="operation failed";
if(_2b5.ErrorMessage){
_2b3=splitErrorMessage(_2b5.ErrorMessage);
}
switch(MapErrorCode[_2b5.ErrorCode]){
case INVALID_ARG_ERR:
case MISSING_ARG_ERR:
case NOT_SUPPORTED_ERR:
throw new DeviceException(MapErrorCode[_2b5.ErrorCode],"Messaging:getList:"+_2b3);
break;
default:
if(_2ab){
setTimeout(function(){
_2ab(new DeviceException(MapErrorCode[_2b5.ErrorCode],"Messaging:getList:"+_2b3));
},500);
}else{
throw new DeviceException(MapErrorCode[_2b5.ErrorCode],"Messaging:getList:"+_2b3);
}
}
}
return _2b5.TransactionID;
}
catch(e){
__device_handle_exception(e,"__sp_messaging_getList: "+e);
}
};
function __sp_messaging_send_common(_2b6,_2b7,_2b8,id,eCB){
var _2bb=function(arg1,arg2,arg3){
if(_2b8){
var _2bf="operation failed";
if(arg3.ErrorCode!=0){
if(arg3.ErrorMessage){
_2bf=splitErrorMessage(arg3.ErrorMessage);
}
if(eCB){
setTimeout(function(){
eCB(new DeviceException(MapErrorCode[arg3.ErrorCode],"Messaging: send: "+_2bf));
},500);
return;
}
}
if(arg2!=event_cancelled){
_2b8();
}
}
};
var _2c0=__sp_message_build(_2b6,id);
_2c0.MessageParam.LaunchEditor=_2b7;
var _2c1;
if(_2b7==false){
_2c1=this.so.IMessaging.Send(_2c0,_2bb);
if(_2c1.ErrorCode!=0){
var _2c2="operation failed";
if(_2c1.ErrorMessage){
_2c2=splitErrorMessage(_2c1.ErrorMessage);
}
switch(MapErrorCode[_2c1.ErrorCode]){
case INVALID_ARG_ERR:
case MISSING_ARG_ERR:
case NOT_SUPPORTED_ERR:
throw new DeviceException(MapErrorCode[_2c1.ErrorCode],_2c2);
break;
default:
if(eCB){
setTimeout(function(){
eCB(new DeviceException(MapErrorCode[_2c1.ErrorCode],_2c2));
},500);
return;
}else{
throw new DeviceException(MapErrorCode[_2c1.ErrorCode],_2c2);
}
}
}
var _2c3=_2c1.TransactionID;
return _2c3;
}else{
_2c1=this.so.IMessaging.Send(_2c0);
if(_2c1.ErrorCode!=0){
if(_2c1.ErrorMessage){
var _2c4=splitErrorMessage(_2c1.ErrorMessage);
throw new DeviceException(MapErrorCode[_2c1.ErrorCode],"Messaging:startEditor"+_2c4);
}else{
throw new DeviceException(MapErrorCode[_2c1.ErrorCode],"Messaging:startEditor:operation failed");
}
}
}
if(_2c0){
delete _2c0.MessageParam;
}
};
function __sp_messaging_startEditor(_2c5){
if(!_2c5){
throw new DeviceException(MISSING_ARG_ERR,"Messaging:startEditor:message is missing");
}else{
if(typeof _2c5!="object"){
throw new DeviceException(INVALID_ARG_ERR,"Messaging:startEditor:message is invalid");
}
}
if((_2c5.subject)){
if((_2c5.subject).length>256){
throw new DeviceException(DATA_OUT_OF_RANGE_ERR,"Messaging:startEditor:subject is too lengthy");
}
}
if(_2c5.to==undefined||_2c5.to==null){
throw new DeviceException(MISSING_ARG_ERR,"Messaging:startEditor:to field is missing");
}
if(_2c5.attachments!=undefined&&_2c5.attachments!=null&&typeof _2c5.attachments!="object"){
throw new DeviceException(INVALID_ARG_ERR,"Messaging:startEditor:attachment is invalid");
}
if(_2c5){
if(_2c5.body){
if(typeof (_2c5.body)!="string"){
throw new DeviceException(INVALID_ARG_ERR,"Messaging:startEditor:body is invalid");
}
}
}
try{
this.sendCommon(_2c5,true,null);
}
catch(e){
var _2c6=null;
if(e.message){
_2c6=new DeviceException(e.code,"Messaging:startEditor:"+e.message);
}else{
_2c6=new DeviceException(e.code,"Messaging:startEditor:operation failed");
}
__device_handle_exception(_2c6,"__sp_messaging_startEditor: "+_2c6);
}
};
function __sp_messaging_send(_2c7,_2c8,id,_2ca){
if(!_2c8){
throw new DeviceException(MISSING_ARG_ERR,"Messaging:send:message is missing");
}else{
if(typeof _2c8!="object"){
throw new DeviceException(INVALID_ARG_ERR,"Messaging:send:message is invalid");
}
}
if(!_2c7){
throw new DeviceException(MISSING_ARG_ERR,"Messaging:send:callback is missing");
}else{
if(typeof _2c7!="function"){
throw new DeviceException(INVALID_ARG_ERR,"Messaging:send:callback is invalid");
}
}
if(_2c8.to==undefined||_2c8.to==null){
throw new DeviceException(MISSING_ARG_ERR,"Messaging:send:to field is missing");
}
if(_2c8.attachments!=undefined&&_2c8.attachments!=null&&typeof _2c8.attachments!="object"){
throw new DeviceException(INVALID_ARG_ERR,"Messaging:send:attachment is invalid");
}
if(!id){
id="";
}
if((typeof id)=="function"){
var _2cb=id;
id="";
_2ca=_2cb;
}
if((typeof _2ca)=="undefined"||_2ca==null){
_2ca=null;
}else{
if((typeof _2ca)!="function"){
throw new DeviceException(INVALID_ARG_ERR,"Messaging:send:errorCallback is not a function");
}
}
var _2cc=function(arg1,arg2,arg3){
var _2d0=_2c7;
var _2d1=_2ca;
var iter=null;
if(arg3.ErrorCode!=0){
var _2d3;
if(arg3.ErrorMessage){
_2d3=splitErrorMessage(arg3.ErrorMessage);
}else{
_2d3="Operation Failed";
}
_2d1(new DeviceException(MapErrorCode[arg3.ErrorCode],"Messaging:startEditor: "+_2d3));
return;
}else{
if(arg3.ReturnValue){
iter=new __sp_message_iterator(arg3.ReturnValue);
_2d0(iter);
}
}
if(arg2!=event_cancelled){
_2d0(iter);
}
};
try{
var _2d4=this.sendCommon(_2c8,false,_2c7,id,_2ca);
return _2d4;
}
catch(e){
var _2d5=null;
switch(e.code){
case INVALID_ARG_ERR:
case MISSING_ARG_ERR:
case NOT_SUPPORTED_ERR:
throw new DeviceException(e.code,"Messaging:send:"+e.message);
break;
default:
if(_2ca){
setTimeout(function(){
_2ca(new DeviceException(e.code,"Messaging:send:"+e.message));
},1000);
}else{
throw new DeviceException(e.code,"Messaging:send:"+e.message);
}
}
}
};
function __sp_messaging_setNotifier(_2d6,_2d7){
if(!_2d6){
throw new DeviceException(MISSING_ARG_ERR,"Messaging:setNotifier:callback is missing");
}else{
if(typeof _2d6!="function"){
throw new DeviceException(INVALID_ARG_ERR,"Messaging:setNotifier:callback is invalid");
}
}
if(_2d7){
if(typeof (_2d7)!="function"){
throw new DeviceException(INVALID_ARG_ERR,"Messaging:setNotifier: ErrorCallback is invalid");
}
}
var _2d8=function(arg1,arg2,arg3){
var _2dc=_2d6;
var _2dd=_2d7;
var _2de=null;
var _2df=null;
if(arg3.ErrorCode!=0){
if(arg3.ErrorMessage){
_2df=splitErrorMessage(arg3.ErrorMessage);
}else{
_2df="operation failed";
}
if(_2dd){
_2dd(new DeviceException(MapErrorCode[arg3.ErrorCode],"Messaging:setNotifier: "+_2df));
return;
}
}else{
if(arg3.ReturnValue){
_2de=new __sp_device_message_info_build_notifier(arg3.ReturnValue);
arg3.ReturnValue.close();
}
}
if(arg2!=event_cancelled){
_2dc(_2de.id);
}
};
var _2e0={};
modifyObjectBaseProp(_2e0);
_2e0.Type="NewMessage";
try{
var _2e1=this.so.IMessaging.RegisterNotification(_2e0,_2d8);
if(_2e0){
delete _2e0.Type;
}
if(_2e1.ErrorCode!=0){
var _2e2="operation failed";
if(_2e1.ErrorMessage){
_2e2=splitErrorMessage(_2e1.ErrorMessage);
}
switch(MapErrorCode[_2e1.ErrorCode]){
case INVALID_ARG_ERR:
case MISSING_ARG_ERR:
case NOT_SUPPORTED_ERR:
throw new DeviceException(MapErrorCode[_2e1.ErrorCode],"Messaging:setNotifier:"+_2e2);
break;
default:
if(_2d7){
setTimeout(function(){
_2d7(new DeviceException(MapErrorCode[_2e1.ErrorCode],"Messaging:setNotifier:"+_2e2));
},1000);
}else{
throw new DeviceException(MapErrorCode[_2e1.ErrorCode],"Messaging:setNotifier:"+_2e2);
}
}
}
var _2e3=_2e1.TransactionID;
return _2e3;
}
catch(e){
__device_handle_exception(e,"__sp_messaging_setNotifier: "+e.toString());
}
};
function __sp_messaging_cancelNotifier(){
var _2e4={};
modifyObjectBaseProp(_2e4);
_2e4.Type="NewMessage";
try{
var _2e5=this.so.IMessaging.CancelNotification(_2e4);
if(_2e4){
delete _2e4.Type;
}
if(_2e5.ErrorCode!=0){
if(_2e5.ErrorMessage){
var _2e6=splitErrorMessage(_2e5.ErrorMessage);
throw new DeviceException(MapErrorCode[_2e5.ErrorCode],"Messaging:cancelNotifier"+_2e6);
}else{
throw new DeviceException(MapErrorCode[_2e5.ErrorCode],"Messaging:cancelNotifier:operation failed");
}
}
}
catch(e){
__device_handle_exception(e,"__sp_messaging_cancelNotifier: "+e);
}
};
function __sp_messaging_getMessage(id){
if(!id){
throw new DeviceException(MISSING_ARG_ERR,"Messaging:getMessage:id is missing");
}else{
if((typeof id)!="string"){
throw new DeviceException(INVALID_ARG_ERR,"Messaging:getMessage:MessageId should be a string");
}
}
if((typeof id=="string")&&!(isNaN(id))){
id=Number(id);
if(id==0){
throw new DeviceException(DATA_NOT_FOUND_ERR,"Messaging:getMessage:id not found");
}
if(id<0){
throw new DeviceException(DATA_OUT_OF_RANGE_ERR,"Messaging:getMessage:id is out of range");
}
}
var _2e8={};
modifyObjectBaseProp(_2e8);
_2e8.Type="Inbox";
_2e8.Filter={};
modifyObjectBaseProp(_2e8.Filter);
_2e8.Filter.MessageId=id;
try{
var _2e9=this.so.IMessaging.GetList(_2e8);
if(_2e8){
delete _2e8.Filter;
delete _2e8.Type;
}
if(_2e9.ErrorCode!=0){
if(_2e9.ErrorMessage){
var _2ea=splitErrorMessage(_2e9.ErrorMessage);
throw new DeviceException(MapErrorCode[_2e9.ErrorCode],"Messaging:getMessage"+_2ea);
}else{
throw new DeviceException(MapErrorCode[_2e9.ErrorCode],"Messaging:getMessage:operation failed");
}
}
if(_2e9.ReturnValue){
var iter=new __sp_message_iterator(_2e9.ReturnValue);
var _2ec=iter.next();
if(_2ec){
return _2ec;
}else{
throw new DeviceException(DATA_NOT_FOUND_ERR,"Messaging:getMessage:id not found");
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
throw new DeviceException(MISSING_ARG_ERR,"Messaging:delete:id is missing");
}else{
if((typeof id)!="string"){
throw new DeviceException(INVALID_ARG_ERR,"Messaging:deleteMessage:MessageId should be a string");
}
}
if((typeof id=="string")&&!(isNaN(id))){
id=Number(id);
if(id==0){
throw new DeviceException(DATA_NOT_FOUND_ERR,"Messaging:delete:id not found");
}
if(id<0){
throw new DeviceException(DATA_OUT_OF_RANGE_ERR,"Messaging:delete:id is out of range");
}
}
var _2ee={};
modifyObjectBaseProp(_2ee);
_2ee.MessageId=id;
try{
var _2ef=this.so.IMessaging.Delete(_2ee);
a("MapErrorCode[ result.ErrorCode ]"+MapErrorCode[_2ef.ErrorCode]);
if(_2ee){
delete _2ee.MessageId;
}
if(_2ef.ErrorCode!=0){
if(_2ef.ErrorMessage){
var _2f0=splitErrorMessage(_2ef.ErrorMessage);
throw new DeviceException(MapErrorCode[_2ef.ErrorCode],"Messaging:delete"+_2f0);
}else{
throw new DeviceException(MapErrorCode[_2ef.ErrorCode],"Messaging:delete:operation failed");
}
}
}
catch(e){
__device_handle_exception(e,"__sp_messaging_delete: "+e);
}
};
function __sp_messaging_setStatus(id,_2f2){
if(id==null||id==undefined||(id.length)<=0){
throw new DeviceException(MISSING_ARG_ERR,"Messaging:setStatus:id is missing");
}
if((typeof id)!="string"){
throw new DeviceException(INVALID_ARG_ERR,"Messaging:setStatus:id should be string");
}
if(_2f2==null||_2f2==undefined){
throw new DeviceException(MISSING_ARG_ERR,"Messaging:setStatus:status is missing");
}
if(typeof _2f2!="number"){
throw new DeviceException(INVALID_ARG_ERR,"Messaging:setStatus:status is invalid");
}
if(typeof _2f2=="number"&&_2f2!=0&&_2f2!=1){
throw new DeviceException(INVALID_ARG_ERR,"Messaging:setStatus:status is invalid");
}
if((typeof id=="string")&&!(isNaN(id))){
id=Number(id);
if(id==0){
throw new DeviceException(DATA_NOT_FOUND_ERR,"Messaging:setStatus:id not found");
}
if(id<0){
throw new DeviceException(DATA_OUT_OF_RANGE_ERR,"Messaging:setStatus:id is out of range");
}
}
var _2f3={};
modifyObjectBaseProp(_2f3);
_2f3.MessageId=id;
if((_2f2==this.STATUS_UNREAD)){
_2f3.Status="Unread";
}else{
if((_2f2==this.STATUS_READ)){
a("in read");
_2f3.Status="Read";
}
}
try{
var _2f4=this.so.IMessaging.ChangeStatus(_2f3);
if(_2f3){
delete _2f3.MessageId;
delete _2f3.Status;
}
if(_2f4.ErrorCode!=0){
if(_2f4.ErrorMessage){
var _2f5=splitErrorMessage(_2f4.ErrorMessage);
throw new DeviceException(MapErrorCode[_2f4.ErrorCode],"Messaging:setStatus"+_2f5);
}else{
throw new DeviceException(MapErrorCode[_2f4.ErrorCode],"Messaging:setStatus:operation failed");
}
}
}
catch(e){
__device_handle_exception(e,"__sp_messaging_setStatus: "+e);
}
};
function __sp_messaging_cancel(_2f6){
if(_2f6==null||_2f6==undefined){
throw new DeviceException(MISSING_ARG_ERR,"Messaging:setStatus:id is missing");
}
if(typeof _2f6!="number"){
throw new DeviceException(INVALID_ARG_ERR,"Messaging:cancel:id is invalid");
}
var _2f7={};
modifyObjectBaseProp(_2f7);
_2f7.TransactionID=_2f6;
try{
var _2f8=this.so.IMessaging.Cancel(_2f7);
if(_2f7){
delete _2f7.TransactionID;
}
if(_2f8.ErrorCode!=0){
var err;
if(_2f8.ErrorCode==1000){
err=DATA_NOT_FOUND_ERR;
}else{
err=MapErrorCode[_2f8.ErrorCode];
}
if(_2f8.ErrorMessage){
var _2fa=splitErrorMessage(_2f8.ErrorMessage);
throw new DeviceException(err,"Messaging:cancel"+_2fa);
}else{
throw new DeviceException(err,"Messaging:cancel:operation failed");
}
}
}
catch(e){
__device_handle_exception(e,"__sp_messaging_setStatus: "+e);
}
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
var _2fe=null;
if(arg3.ReturnValue){
var time=arg3.ReturnValue.TimeStamp;
var xrot=arg3.ReturnValue.XRotation;
var yrot=arg3.ReturnValue.YRotation;
var zrot=arg3.ReturnValue.ZRotation;
arg3.ReturnValue.close();
_2fe={};
modifyObjectBaseProp(_2fe);
_2fe.timeStamp=time;
_2fe.rotationAboutXAxis=xrot;
_2fe.rotationAboutYAxis=yrot;
_2fe.rotationAboutZAxis=zrot;
}
__rotation_channel.ucb(_2fe);
}
};
function __XYZ_cb(arg1,arg2,arg3){
if(arg2!=event_cancelled){
var _306=null;
if(arg3.ReturnValue){
var time=arg3.ReturnValue.TimeStamp;
var _308=arg3.ReturnValue.XAxisData;
var _309=arg3.ReturnValue.YAxisData;
var _30a=arg3.ReturnValue.ZAxisData;
arg3.ReturnValue.close();
_306={};
modifyObjectBaseProp(_306);
_306.timeStamp=time;
_306.axisX=_308;
_306.axisY=_309;
_306.axisZ=_30a;
}
__XYZ_channel.ucb(_306);
}
};
function __orientation_cb(arg1,arg2,arg3){
if(arg2!=event_cancelled){
var _30e=null;
if(arg3.ReturnValue){
var time=arg3.ReturnValue.TimeStamp;
var _310=arg3.ReturnValue.DeviceOrientation;
arg3.ReturnValue.close();
_30e={};
modifyObjectBaseProp(_30e);
_30e.timeStamp=time;
_30e.deviceOrientation=_310;
}
__orientation_channel.ucb(_30e);
}
};
function __sp_sensors_getChannels(){
return ["Rotation","AccelerometerAxis","Orientation"];
};
function __sp_sensors_setNotifier(_311,_312,_313){
var _314=new DeviceException(0,"dummy");
if(!_311){
throw new DeviceAPIError(_314.MISSING_ARG_ERR,"Callback is missing");
}
if((typeof _311)!="function"){
throw new DeviceAPIError(_314.INVALID_ARG_ERR,"Callback is of invalid type");
}
if(_313&&((typeof _313)!="function")){
throw new DeviceAPIError(_314.INVALID_ARG_ERR,"InValid error Callback");
}
if(!_312){
throw new DeviceAPIError(_314.MISSING_ARG_ERR,"Channel is missing");
}
if((typeof _312)!="string"){
throw new DeviceAPIError(_314.INVALID_ARG_ERR,"Channel is of invalid type");
}
var rval;
var cb;
var _317={};
modifyObjectBaseProp(_317);
switch(_312){
case "Rotation":
_317.SearchCriterion="Rotation";
cb=__rotation_cb;
__rotation_channel.ucb=_311;
break;
case "AccelerometerAxis":
_317.SearchCriterion="AccelerometerAxis";
cb=__XYZ_cb;
__XYZ_channel.ucb=_311;
break;
case "Orientation":
_317.SearchCriterion="Orientation";
cb=__orientation_cb;
__orientation_channel.ucb=_311;
break;
default:
throw new DeviceAPIError(_314.NOT_SUPPORTED_ERR,"Unsupported input channel");
}
try{
rval=this.so.ISensor.FindSensorChannel(_317);
if(_317){
delete _317.SearchCriterion;
}
if(rval.ErrorCode!=0){
throw new DeviceAPIError(_314.NOT_SUPPORTED_ERR,"StartChannel:Operation Failed");
}
var cmap=[];
var _319=[];
var _31a=rval["ReturnValue"];
var _31b=_31a.length;
cmap=_31a[0];
var _31c={};
modifyObjectBaseProp(_31c);
_31c.ListeningType="ChannelData";
_31c.ChannelInfoMap=cmap;
var _31d=this.so.ISensor.RegisterForNotification(_31c,cb);
if(_31c){
delete _31c.ChannelInfoMap;
delete _31c.ListeningType;
}
if(cmap){
delete cmap.index;
}
_319[0]=_31d["TransactionID"];
if(_31d.ErrorCode!=0){
if(_31d.ErrorCode==1005){
_313(new DeviceAPIError(_314.SERVICE_IN_USE_ERR,"Not Allowed Operation"));
return;
}else{
throw new DeviceAPIError(_314.NOT_SUPPORTED_ERR,"StartChannel:Operation Failed");
}
}
}
catch(e2){
__device_handle_exception(e2,"__sp_sensors_setNotifier: RegisterForNotification: "+e2);
}
switch(_312){
case "Rotation":
__rotation_channel.tid=_319;
break;
case "AccelerometerAxis":
__XYZ_channel.tid=_319;
break;
case "Orientation":
__orientation_channel.tid=_319;
break;
}
return _319;
};
function __sp_sensors_cancelNotifier(_31e){
var _31f=new DeviceException(0,"dummy");
if(!_31e){
throw new DeviceAPIError(_31f.MISSING_ARG_ERR,"Channel is missing");
}
if((typeof _31e)!="string"){
throw new DeviceAPIError(_31f.INVALID_ARG_ERR,"Channel is of invalid type");
}
var id;
switch(_31e){
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
throw new DeviceAPIError(_31f.NOT_SUPPORTED_ERR,"Unsupported input channel");
}
if(!id){
throw new DeviceAPIError(_31f.DATA_NOT_FOUND_ERR,"Stop Channel:Operation Failed");
}
var _321={};
modifyObjectBaseProp(_321);
for(var i in id){
_321.TransactionID=id[i];
try{
var _323=this.so.ISensor.Cancel(_321);
if(_321){
delete _321.TransactionID;
}
if(_323.ErrorCode!=0){
throw new DeviceAPIError(_31f.DATA_NOT_FOUND_ERR,"Stop Channel:Operation Failed");
}
}
catch(e1){
__device_handle_exception(e1,"__sp_sensors_cancelNotifier: "+e1);
}
}
};
function __sp_sensors_getScaleFactor(_324){
var _325=new DeviceException(0,"dummy");
if(!_324){
throw new DeviceAPIError(_325.MISSING_ARG_ERR,"Channel is missing");
}
if((typeof _324)!="string"){
throw new DeviceAPIError(_325.INVALID_ARG_ERR,"Channel is of invalid type");
}
if(_324!="AccelerometerAxis"){
throw new DeviceAPIError(_325.NOT_SUPPORTED_ERR,"Unsupported input channel");
}
try{
var _326={};
_326.SearchCriterion="AccelerometerAxis";
var rval=this.so.ISensor.FindSensorChannel(_326);
if(_326){
delete _326.SearchCriterion;
}
if(rval.ErrorCode!=0){
throw new DeviceAPIError(_325.NOT_SUPPORTED_ERR,"getScaleFactor:Operation Failed");
}
var cmap=[];
var _329=rval["ReturnValue"];
cmap=_329[0];
var _32a={};
modifyObjectBaseProp(_32a);
_32a.ListeningType="ChannelData";
_32a.ChannelInfoMap=cmap;
var _32b=this.so.ISensor.GetScaleFactor(_32a);
if(_32a){
delete _32a.ChannelInfoMap;
delete _32a.ListeningType;
}
if(cmap){
delete cmap.index;
}
if(_32b.ErrorCode!=0){
throw new DeviceAPIError(_325.NOT_SUPPORTED_ERR,"getScaleFactor:Operation Failed");
}
}
catch(e1){
__device_handle_exception(e1,"__sp_sensors_getScaleFactor: "+e1);
}
return _32b["ReturnValue"];
};
var DATA_NOT_FOUND_ERR=101;
var DATA_OUT_OF_RANGE_ERR=105;
var NOT_ALLOWED_ERR=106;
var error=new DeviceException();
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
this.startChannel=__sp_sysinfo_setNotifier;
this.stopChannel=__sp_sysinfo_cancelNotifier;
this.cancel=__sp_sysinfo_cancel;
try{
this.so=device.getServiceObject("Service.SysInfo","ISysInfo");
}
catch(e){
this.so=null;
__device_handle_exception(e,"Sysinfo service not available");
}
};
function __sp_channel_descriptors_get(){
var _32c=[{name:"Charging",data:[{name:"chargingStatus",range:"true or false",description:"Charging(true) ,Not charging(false)",}],style:["Sync","Oneshot","Notification"]},{name:"BluetoothOn",data:[{name:"btOn",range:"true or false",description:"BluetoothOn(true) ,BluetoothOff(false)",}],style:["Sync","Oneshot","Notification"]},{name:"PhoneLanguage",data:[{name:"phoneLanguage",range:"",description:"",}],style:["Sync","Oneshot"]},{name:"ProductType",data:[{name:"productType",range:"",description:"",}],style:["Sync","Oneshot"]},{name:"FirmwareVersion",data:[{name:"firmwareVersion",range:"",description:"",}],style:["Sync","Oneshot"]},{name:"BatteryLevel",data:[{name:"batteryLevel ",range:"0-100",description:"Percent battery charge"}],style:["Async","Oneshot","Notification"]},{name:"SignalStrength",data:[{name:"signalStrength",range:"0-100",description:"Signal Strength in Percentage"}],style:["Async","Oneshot","Notification"]},{name:"Network",data:[{name:"networkName ",description:"Network name"},{name:"networkStatus",range:"Available,Current,Forbidden",description:""},{name:"networkMode",range:"ModeGsm,ModeCdma,ModeWcdma",description:""},{name:"mobileCountryCode",range:"",description:""},{name:"mobileNetworkCode",range:"",description:""},{name:"locationStatus",range:"True, False",description:""},{name:"areaCode",range:"",description:""},{name:"cellID",range:"",description:""}],style:["Async","Oneshot","Notification"]},{name:"IMEI",data:[{name:"imei",range:"",description:""}],style:["Sync","Oneshot"]},{name:"OutOfMemory",data:[{name:"oomDrive",range:"",description:""}],style:["NA","NA","Notification"]},{name:"DeviceOrientation",data:[{name:"deviceOrientation",range:"Landscape,Portrait",description:""}],style:["Sync","Oneshot"]},{name:"RoamingFlag",data:[{name:"roamingFlag",range:"",description:""}],style:["Sync","Oneshot"]},{name:"DeviceInputMethod",data:[{name:"deviceInputMethod",range:"Touch,NonTouch,Hybrid",description:""}],style:["Sync","Oneshot"]},{name:"HomeNetwork",data:[{name:"networkName ",description:"Network name"},{name:"networkStatus",range:"Available,Current,Forbidden",description:""},{name:"networkMode",range:"ModeGsm,ModeCdma,ModeWcdma",description:""},{name:"mobileCountryCode",range:"",description:""},{name:"mobileNetworkCode",range:"",description:""},{name:"locationStatus",range:"True, False",description:""},{name:"areaCode",range:"",description:""},{name:"cellID",range:"",description:""}],style:["Async","Oneshot","Notification"]}];
return _32c;
};
var max=110;
var min=40;
var diff=max-min;
function __sp_device_sysinfo_toDecibel(_32d){
var _32e=_32d/100;
var _32f=max-(_32e*diff);
_32f=Math.round(_32f);
return _32f;
};
function __sp_device_sysinfo_toPercentage(_330){
if(_330==0){
return _330;
}else{
var _331=max-_330;
var _332=_331/diff;
_332*=100;
_332=Math.round(_332);
return _332;
}
};
function __sp_device_sysinfo_toBool(_333){
if(_333==0){
return false;
}else{
return true;
}
};
function mappingVerification(_334){
if(_334==1016||_334==1012||_334==1010||_334==1009||_334==1005||_334==1000||_334==1011||_334==1007||_334==1003||_334==1002){
return true;
}else{
return false;
}
};
function __sp_device_sysinfo_extract(_335){
var _336=_335.Key;
var _337={};
modifyObjectBaseProp(_337);
try{
switch(_336){
case "ChargingStatus":
_337.chargingStatus=__sp_device_sysinfo_toBool(_335.Status);
break;
case "BatteryStrength":
_337.batteryLevel=_335.Status;
break;
case "SignalStrength":
_337.signalStrength=__sp_device_sysinfo_toPercentage(_335.Status);
break;
case "CurrentNetwork":
var _338;
var mode;
switch(_335.NetworkStatus){
case 0:
_338="Available";
break;
case 1:
_338="Current";
break;
case 2:
_338="Forbidden";
break;
default:
_338="Unknown";
break;
}
switch(_335.NetworkMode){
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
_337.networkName=_335.NetworkName;
_337.networkStatus=_338;
_337.networkMode=mode;
_337.mobileCountryCode=_335.CountryCode;
_337.mobileNetworkCode=_335.NetworkCode;
_337.locationStatus=_335.LocationStatus;
_337.areaCode=_335.AreaCode;
_337.cellID=_335.CellId;
break;
case "DisplayLanguage":
_337.phoneLanguage=_335.StringData;
break;
case "BlueTooth":
_337.btOn=__sp_device_sysinfo_toBool(_335.Status);
break;
case "ProductType":
_337.productType=_335.StringData;
break;
case "FirmwareVersion":
_337.firmwareVersion=_335.StringData;
break;
case "DeviceInputMethod":
_337.deviceInputMethod=_335.StringData;
break;
default:
_337=_335;
break;
}
return _337;
}
catch(e){
__device_handle_exception(e,"__sp_device_sysinfo_extract: "+e);
}
};
function __sp_sysinfo_get(_33a,_33b,_33c){
var so;
var rval;
var _33f=function(arg1,arg2,arg3){
var _343=_33b;
var _344=_33c;
var op=null;
if(arg3.ErrorCode!=0){
var _346=splitErrorMessage(arg3.ErrorMessage);
_344(new DeviceException(MapErrorCode[arg3.ErrorCode],"SysInfo:getChannel: "+_346));
}else{
if(arg3.ReturnValue){
op=__sp_device_sysinfo_extract(arg3.ReturnValue);
arg3.ReturnValue.close();
_343(op);
}
}
};
var _347=false;
var _348="Status";
var _349;
var _34a={};
modifyObjectBaseProp(_34a);
try{
switch(_33a){
case "Charging":
_34a.Entity="Battery";
_34a.Key="ChargingStatus";
break;
case "BatteryLevel":
_34a.Entity="Battery";
_34a.Key="BatteryStrength";
_347=true;
break;
case "SignalStrength":
_34a.Entity="Network";
_34a.Key="SignalStrength";
_347=true;
break;
case "Network":
_34a.Entity="Network";
_34a.Key="CurrentNetwork";
_347=true;
break;
case "PhoneLanguage":
_34a.Entity="General";
_34a.Key="DisplayLanguage";
break;
case "BluetoothOn":
_34a.Entity="Connectivity";
_34a.Key="BlueTooth";
break;
case "ProductType":
_34a.Entity="Device";
_34a.Key="ProductType";
break;
case "FirmwareVersion":
_34a.Entity="Device";
_34a.Key="FirmwareVersion";
break;
case "DeviceInputMethod":
_34a.Entity="Device";
_34a.Key="DeviceInputMethod";
break;
default:
if(_33a==null){
throw new DeviceException(MISSING_ARG_ERR,"SysInfo:getChannel:channel is missing");
}else{
if(typeof _33a!="string"){
throw new DeviceException(error.INVALID_ARG_ERR,"SysInfo:getChannel:channel is of invalid type");
}else{
throw new DeviceException(INVALID_ARG_ERR,"SysInfo:getChannel:channel is invalid");
}
}
}
if(_347){
if(_33b==null){
throw new DeviceException(MISSING_ARG_ERR,"SysInfo:getChannel:callback is missing");
}
if(typeof _33b!="function"){
throw new DeviceException(INVALID_ARG_ERR,"SysInfo:getChannel:callback is invalid");
}
if(_33c){
if(typeof (_33c)!="function"){
throw new DeviceException(INVALID_ARG_ERR,"SysInfo:getChannel: ErrorCallback is invalid");
}
}
rval=this.so.ISysInfo.GetInfo(_34a,_33f);
if(rval.ErrorCode!=0){
var _34b=mappingVerification(rval.ErrorCode);
if(_34b){
switch(MapErrorCode[rval.ErrorCode]){
case MISSING_ARG_ERR:
case INVALID_ARG_ERR:
if(rval.ErrorMessage){
var _34c=splitErrorMessage(rval.ErrorMessage);
throw new DeviceException(MapErrorCode[rval.ErrorCode],"SysInfo: getChannel: "+_34c);
}else{
throw new DeviceException(MapErrorCode[rval.ErrorCode],"SysInfo:getChannel:Operation Failed");
}
break;
default:
_33b(0);
}
}else{
_33b(0);
}
}
return rval.TransactionID;
}else{
rval=this.so.ISysInfo.GetInfo(_34a);
if(rval.ErrorCode!=0){
if(rval.ErrorMessage){
var _34d=splitErrorMessage(rval.ErrorMessage);
throw new DeviceException(MapErrorCode[rval.ErrorCode],"SysInfo: getChannel: "+_34d);
}else{
throw new DeviceException(MapErrorCode[rval.ErrorCode],"SysInfo:getChannel:Operation Failed");
}
}
_349=__sp_device_sysinfo_extract(rval.ReturnValue);
return _349;
}
delete _34a;
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
function __sp_sysinfo_setNotifier(_366,_367,_368,_369){
var rval;
var _36b=null;
var cb=null;
var _36d={};
if(_366==null){
throw new DeviceException(MISSING_ARG_ERR,"SysInfo:startChannel:callback is missing");
}
if(typeof _366!="function"){
throw new DeviceException(INVALID_ARG_ERR,"SysInfo:startChannel:callback is invalid");
}
modifyObjectBaseProp(_36d);
try{
switch(_367){
case "Charging":
_36d.Entity="Battery";
_36d.Key="ChargingStatus";
_36b=__charging_status_channel;
cb=__charging_status_channel_cb;
break;
case "Network":
_36d.Entity="Network";
_36d.Key="CurrentNetwork";
_36b=__net_coverage_channel;
cb=__net_coverage_channel_cb;
break;
case "BatteryLevel":
_36d.Entity="Battery";
_36d.Key="BatteryStrength";
_36d.SystemData={};
modifyObjectBaseProp(_36d.SystemData);
if(_368==null){
_368=50;
}
if(!(_368>=0&&_368<=100)){
throw new DeviceException(DATA_OUT_OF_RANGE_ERR,"SysInfo:startChannel:trigger is out of range");
}
if(typeof _368!="number"){
throw new DeviceException(INVALID_ARG_ERR,"SysInfo:startChannel:trigger is of  invalid type");
}
_36d.SystemData.Status=_368;
_36b=__battery_level_channel;
cb=__battery_level_channel_cb;
break;
case "SignalStrength":
_36d.Entity="Network";
_36d.Key="SignalStrength";
_36d.SystemData={};
modifyObjectBaseProp(_36d.SystemData);
if(_368!=null){
if(!(_368>=0&&_368<=100)){
throw new DeviceException(DATA_OUT_OF_RANGE_ERR,"SysInfo:startChannel:trigger is out of range");
}
if(typeof _368!="number"){
throw new DeviceException(INVALID_ARG_ERR,"SysInfo:startChannel:trigger is of invalid type");
}
_36d.SystemData.Status=__sp_device_sysinfo_toDecibel(_368);
}
_36b=__signal_channel;
cb=__signal_channel_cb;
break;
case "BluetoothOn":
_36d.Entity="Connectivity";
_36d.Key="BlueTooth";
_36b=__bluetooth_on_channel;
cb=__bluetooth_on_channel_cb;
break;
default:
var _36e;
if(_367==null){
throw new DeviceException(MISSING_ARG_ERR,"SysInfo:startChannel:channel is missing");
}else{
if(typeof _367!="string"){
throw new DeviceException(INVALID_ARG_ERR,"SysInfo:startChannel:channel is of invalid type");
}else{
throw new DeviceException(INVALID_ARG_ERR,"SysInfo:startChannel:channel is invalid");
}
}
if(_36d.SystemData){
delete _36d.SystemData;
}
}
_36b.scb=_366;
_36b.ecb=_369;
if(_36b.ecb){
if(typeof (_36b.ecb)!="function"){
throw new DeviceException(INVALID_ARG_ERR,"SysInfo:startChannel: ErrorCallback is invalid");
}
}
if(_36b.cancel_id){
var _36f={};
modifyObjectBaseProp(_36f);
_36f.TransactionID=_36b.cancel_id;
this.so.ISysInfo.Cancel(_36f);
_36b.cancel_id=null;
delete _36f;
}
rval=this.so.ISysInfo.GetNotification(_36d,cb);
delete _36d;
if(rval.ErrorCode!=0){
switch(MapErrorCode[rval.ErrorCode]){
case MISSING_ARG_ERR:
case INVALID_ARG_ERR:
if(rval.ErrorMessage){
var _370=splitErrorMessage(rval.ErrorMessage);
throw new DeviceException(MapErrorCode[rval.ErrorCode],"SysInfo: startChannel: "+_370);
}else{
throw new DeviceException(MapErrorCode[rval.ErrorCode],"SysInfo:startChannel:Operation Failed");
}
break;
default:
_366(0);
}
}
_36b.cancel_id=rval.TransactionID;
return _36b.cancel_id;
}
catch(e){
__device_handle_exception(e,"__sp_sysinfo_startChannel: "+e);
}
};
function __sp_sysinfo_cancelNotifier(_371){
try{
switch(_371){
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
var _372;
if(_371==null){
throw new DeviceException(MISSING_ARG_ERR,"SysInfo:stopChannel:channel is missing");
}else{
if(typeof _371!="string"){
throw new DeviceException(INVALID_ARG_ERR,"SysInfo:stopChannel:channel is of invalid type");
}else{
throw new DeviceException(INVALID_ARG_ERR,"SysInfo:stopChannel:channel is invalid");
}
}
}
if(channel.cancel_id){
var _373={};
modifyObjectBaseProp(_373);
_373.TransactionID=channel.cancel_id;
var _374=this.so.ISysInfo.Cancel(_373);
delete _373;
if(_374.ErrorCode!=0){
if(_374.ErrorMessage){
var _375=splitErrorMessage(_374.ErrorMessage);
throw new DeviceException(MapErrorCode[_374.ErrorCode],"SysInfo: stopChannel: "+_375);
}else{
throw new DeviceException(MapErrorCode[_374.ErrorCode],"SysInfo:stopChannel:Operation Failed");
}
}
channel.cancel_id=null;
}else{
throw new DeviceException(DATA_NOT_FOUND_ERR,"SysInfo:stopChannel:channel not started");
}
}
catch(e){
__device_handle_exception(e,"__sp_sysinfo_stopChannel: "+e);
}
};
function __sp_sysinfo_cancel(_376){
try{
var _377=0;
if(_376==null){
throw new DeviceException(MISSING_ARG_ERR,"SysInfo:cancel:Id is missing");
}
if(typeof _376!="number"){
throw new DeviceException(INVALID_ARG_ERR,"SysInfo:cancel:Id is of invalid type");
}
if(_376==__charging_status_channel.cancel_id||_376==__net_coverage_channel.cancel_id||_376==__battery_level_channel.cancel_id||_376==__bluetooth_on_channel.cancel_id||_376==__signal_channel.cancel_id){
_377=1;
}
if(_377!=1){
var _378={TransactionID:_376};
var _379=this.so.ISysInfo.Cancel(_378);
if(_379.ErrorCode!=0){
if(_379.ErrorMessage){
var _37a=splitErrorMessage(_379.ErrorMessage);
throw new DeviceException(INVALID_ARG_ERR,"SysInfo:cancel: "+_37a);
}else{
throw new DeviceException(MapErrorCode[_379.ErrorCode],"SysInfo:cancel:Operation Failed");
}
}
}else{
_377=0;
throw new DeviceException(NOT_ALLOWED_ERR,"SysInfo:cancel:Cannot Cancel a channel started using startChannel ");
}
}
catch(e){
__device_handle_exception(e,"__sp_sysinfo_cancel: "+e);
}
};
var err_missing_argument=1003;
var err_bad_argument=1002;
var err_ServiceNotSupported=1004;
var err_InvalidService_Argument=1000;
function convertFromPS2JS(_37b){
var _37c=new DeviceAPIError(0,"dummy");
var _37d;
switch(_37b){
case 1016:
_37d=_37c.TIMEOUT_ERR;
break;
case 1012:
_37d=_37c.DATA_NOT_FOUND_ERR;
break;
case 1010:
_37d=_37c.DATA_ALREADY_EXISTS_ERR;
break;
case 1009:
_37d=_37c.SERVICE_BUSY_ERR;
break;
case 1005:
_37d=_37c.SERVICE_IN_USE_ERR;
break;
default:
_37d=1001;
}
return _37d;
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
this.addCategory=__sp_landmarks_category_add;
this.updateCategory=__sp_landmarks_category_update;
this.deleteCategory=__sp_landmarks_category_delete;
this.getLandmarks=__sp_landmarks_getList;
this.addLandmark=__sp_landmarks_add;
this.updateLandmark=__sp_landmarks_update;
this.deleteLandmark=__sp_landmarks_delete;
this.importLandmarks=__sp_landmarks_import;
this.exportLandmarks=__sp_landmarks_export;
this.organizeLandmarks=__sp_landmarks_organize;
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
function __sp_landmarks_category_iterator(_37e){
this.iter=_37e;
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
var _37f=new Object();
_37f=this.catItem;
this.catItem=this.iter.getNext();
if(typeof (this.catItem)=="undefined"){
this.catItem=null;
}
return new __sp_device_category_obj(_37f);
}else{
this.catItem=this.iter.getNext();
if(typeof this.catItem=="undefined"){
this.hasElement=true;
this.catItem=null;
return null;
}else{
this.hasElement=true;
var _380=new Object();
_380=this.lmItem;
this.catItem=this.iter.getNext();
if(typeof (this.catItem)=="undefined"){
this.catItem=null;
}
return new __sp_device_category_obj(_380);
}
}
};
function __sp_landmarks_iterator(_381){
this.iter=_381;
this.next=__sp_landmarks_iterator_get_next;
this.hasNext=__sp_landmarks_iterator_has_next;
this.hasElement=false;
this.lmItem=null;
this.close=__sp_landmarks_landmarkitem_close;
};
function __sp_landmarks_landmarkitem_close(){
this.iter.close();
};
function __sp_device_landmark_location_obj(_382){
this.longitude=(_382.Longitude==undefined)?null:_382.Longitude;
this.latitude=(_382.Latitude==undefined)?null:_382.Latitude;
if(_382.Altitude){
this.altitude=_382.Altitude;
}
if(_382.HAccuracy){
this.hAccuracy=_382.HAccuracy;
}
if(_382.VAccuracy){
this.vAccuracy=_382.VAccuracy;
}
};
function __sp_landmark_position_obj(_383){
if(_383.longitude!==undefined){
this.Longitude=_383.longitude;
}
if(_383.latitude!==undefined){
this.Longitude=_383.latitude;
}
};
function __sp_landmark_position_obj_fromJS_2LIW(_384){
this.Longitude=_384.longitude;
this.Latitude=_384.latitude;
if(_384.altitude){
this.Altitude=_384.altitude;
}
if(_384.hAccuracy){
this.HAccuracy=_384.hAccuracy;
}
if(_384.vAccuracy){
this.VAccuracy=_384.vAccuracy;
}
};
function __sp_landmark_bounded_area_obj(area){
this.NorthLatitude=area.coordinate1.latitude;
this.SouthLatitude=area.coordinate2.latitude;
this.EastLongitude=area.coordinate1.longitude;
this.WestLongitude=area.coordinate2.longitude;
};
function __sp_device_landmark_address_obj(_386){
if(_386.Street){
this.street=_386.Street;
}
if(_386.City){
this.city=_386.City;
}
if(_386.state){
this.state=_386.state;
}
if(_386.AreaCode){
this.postalCode=_386.AreaCode;
}
if(_386.Country){
this.country=_386.Country;
}
if(_386.BuildingName){
this.building=_386.BuildingName;
}
if(_386.Telephone){
this.phone=_386.Telephone;
}
};
function __sp_landmark_address_obj(_387){
if(_387.street){
this.Street=_387.street;
}
if(_387.locale){
this.City=_387.locale;
}
if(_387.region){
this.District=_387.region;
}
if(_387.code){
this.AreaCode=_387.code;
}
if(_387.country){
this.Country=_387.country;
}
};
function __sp_get_category_ids_for_names(_388){
var _389=new Array();
var _38a=0;
for(var i in _388){
for(var ii in __sp_category_list){
if(__sp_category_list[ii].name.toLowerCase()==_388[i].toLowerCase()){
_389.push(__sp_category_list[ii].id.toString());
_38a=1;
}
}
if(_38a==0){
return null;
}
_38a=0;
}
return _389;
};
function __sp_device_landmark_obj(_38d){
this.landmarkId=_38d.id;
if(_38d.LandmarkName){
this.name=_38d.LandmarkName;
}
if(_38d.LandmarkDesc){
this.description=_38d.LandmarkDesc;
}
if(_38d.CoverageRadius){
this.coverageRadius=_38d.CoverageRadius;
}
if(_38d.LandmarkPosition){
this.position=new __sp_device_landmark_location_obj(_38d.LandmarkPosition);
}
if(_38d.CategoryInfo){
this.categoryIds=_38d.CategoryInfo;
}
if(_38d.LandmarkFields){
this.address=new __sp_device_landmark_address_obj(_38d.LandmarkFields);
}
};
function __sp_landmark_obj(_38e,str){
if(_38e.name){
this.LandmarkName=_38e.name;
}
if(_38e.landmarkId){
this.id=_38e.landmarkId;
}
if(_38e.description){
this.LandmarkDesc=_38e.description;
}
if(_38e.position){
this.LandmarkPosition=new __sp_landmark_position_obj_fromJS_2LIW(_38e.position);
}
if(_38e.coverageRadius){
this.CoverageRadius=_38e.coverageRadius;
}
if(_38e.categories){
this.CategoryInfo=__sp_get_category_ids_for_names(_38e.categories);
if(!this.CategoryInfo){
throw new DeviceError("Landmarks: "+str+"Category is invalid",err_bad_argument);
}
}
if(_38e.address){
this.LandmarkFields=new __sp_landmark_address_obj(_38e.address);
}
if(_38e.building){
if(!this.LandmarkFields){
this.LandmarkFields=new Object();
modifyObjectBaseProp(this.LandmarkFields);
}
this.LandmarkFields.BuildingName=_38e.building;
}
if(_38e.phone){
if(!this.LandmarkFields){
this.LandmarkFields=new Object();
modifyObjectBaseProp(this.LandmarkFields);
}
this.LandmarkFields.Telephone=_38e.phone;
}
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
var _390=new Object();
_390=this.lmItem;
this.lmItem=this.iter.getNext();
if(typeof (this.lmItem)=="undefined"){
this.lmItem=null;
}
return new __sp_device_landmark_obj(_390);
}else{
this.lmItem=this.iter.getNext();
if(typeof this.lmItem=="undefined"){
this.hasElement=true;
this.lmItem=null;
return null;
}else{
this.hasElement=true;
var _391=new Object();
_391=this.lmItem;
this.lmItem=this.iter.getNext();
if(typeof (this.lmItem)=="undefined"){
this.lmItem=null;
}
return new __sp_device_landmark_obj(_391);
}
}
};
function __sp_category_obj(_392){
if(_392.name){
this.CategoryName=_392.name;
}
if(_392.categoryId){
this.id=_392.categoryId;
}
};
function __sp_device_category_obj(_393){
this.categoryId=_393.id;
this.name=_393.CategoryName;
};
var LANDMARKS_APP_ID=270501282;
function __sp_landmarks_startEditor(_394,_395,_396){
error=new DeviceAPIError(0,"dummy");
if((_394===undefined)||(_394===null)||(_394==="")){
throw new DeviceAPIError(error.MISSING_ARG_ERR,"StartEditor:Missing Success Callback");
}
if((typeof _394)!="function"){
throw new DeviceAPIError(error.INVALID_ARG_ERR,"StartEditor:Success Callback must be of type function");
}
if(_395!==undefined){
if((_395!==null)&&(_395!=="")){
throw new DeviceAPIError(error.NOT_SUPPORTED_ERR,"startEditor:landmark item is not supported");
}
}
if((_396!==undefined)&&(_396!==null)&&(_396!=="")){
if((typeof _396)!="function"){
throw new DeviceAPIError(error.INVALID_ARG_ERR,"StartEditor:error callback must be of type function");
}
}
var _397=270501282;
var _398;
function __s60_on_app_exit(){
window.xwidget.onshow=null;
if(_398){
_398();
}
};
var _399=function(arg1,arg2,arg3){
_394(arg1,arg2,arg3);
};
__s60_start_and_wait(_397,"",_399);
};
function __sp_landmarks_category_getList(_39d,name,_39f){
try{
var _3a0=new DeviceAPIError(0,"dummy");
if((_39d===undefined)||(_39d==="")||(_39d===null)){
throw new DeviceAPIError(_3a0.MISSING_ARG_ERR,"callback is missing");
}
if(typeof (_39d)!="function"){
throw new DeviceAPIError(_3a0.INVALID_ARG_ERR,"invalid callback argument");
}
var _3a1=false;
if((_39f!==undefined)&&(_39f!==null)&&(_39f!=="")){
if(typeof (_39f)!="function"){
throw new DeviceAPIError(_3a0.INVALID_ARG_ERR,"invalid error callback argument");
}else{
_3a1=true;
}
}
var _3a2=new Object();
modifyObjectBaseProp(_3a2);
_3a2.Type="Category";
if((name!==undefined)&&(name!==null)&&(name!=="")){
if(typeof (name)!="string"){
throw new DeviceAPIError(_3a0.INVALID_ARG_ERR,"name must be a string");
}
}
if(name){
_3a2.Filter=new Object();
modifyObjectBaseProp(_3a2.Filter);
_3a2.Filter.CategoryName=name;
_3a2.Filter.PreviousMatchesOnly=false;
}
this.invoker=function(arg1,arg2,arg3){
var iter=null;
if(arg3.ErrorCode||(arg2==4)){
var _3a7=convertFromPS2JS(arg3.ErrorCode);
var _3a8=new DeviceAPIError(_3a7,arg3.ErrorMessage);
if(_3a1){
_39f(_3a8);
}
}else{
if(arg3.ReturnValue){
iter=new __sp_landmarks_category_iterator(arg3.ReturnValue);
_39d(iter);
}
}
};
var rval=this.so.IDataSource.GetList(_3a2,this.invoker);
if(rval.ErrorCode!=0){
switch(rval.ErrorCode){
case 1003:
throw new DeviceAPIError(_3a0.MISSING_ARG_ERR,rval.ErrorMessage);
break;
case 1002:
throw new DeviceAPIError(_3a0.INVALID_ARG_ERR,rval.ErrorMessage);
break;
case 1004:
throw new DeviceAPIError(_3a0.NOT_SUPPORTED_ERR,rval.ErrorMessage);
break;
case 1000:
throw new DeviceAPIError(_3a0.INVALID_ARG_ERR,rval.ErrorMessage);
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
function __sp_landmarks_category_add(_3aa,_3ab,_3ac){
try{
var _3ad=new DeviceAPIError(0,"dummy");
var _3ae=true;
if(_3aa===undefined){
throw new DeviceAPIError(_3ad.MISSING_ARG_ERR,"AddSucessCallback is missing");
}else{
if(((_3aa===null)||(_3aa===""))&&(typeof (_3aa)!="number")){
throw new DeviceAPIError(_3ad.MISSING_ARG_ERR,"AddSucessCallback is missing");
}else{
if(typeof (_3aa)!="function"){
throw new DeviceAPIError(_3ad.INVALID_ARG_ERR,"invalid AddSucessCallback argument");
}
}
}
if(_3ab===undefined||_3ab===null){
throw new DeviceAPIError(_3ad.MISSING_ARG_ERR,"CategoryItem is missing");
}else{
if(typeof (_3ab)!=="object"){
throw new DeviceAPIError(_3ad.INVALID_ARG_ERR,"invalid CategoryItem argument");
}
}
if((_3ac!=undefined)){
if((!_3ac)&&(typeof (_3ac)!="number")){
_3ae=false;
}else{
if((typeof (_3ac)!="function")){
throw new DeviceAPIError(_3ad.INVALID_ARG_ERR,"invalid ErrorCallback callback");
}
}
}else{
_3ae=false;
}
this.invoker=function(arg1,arg2,arg3){
var id=null;
if(arg2==4||arg3.ErrorCode){
var _3b3=convertFromPS2JS(arg3.ErrorCode);
var _3b4=new DeviceAPIError(_3b3,arg3.ErrorMessage);
if(_3ae){
_3ac(_3b4);
}
}else{
if(arg3.ReturnValue){
id=arg3.ReturnValue;
}
_3aa(id);
}
};
var _3b5=new Object();
modifyObjectBaseProp(_3b5);
_3b5.Type="Category";
_3b5.Data=new __sp_category_obj(_3ab);
var rval=this.so.IDataSource.Add(_3b5,this.invoker);
if(rval.ErrorCode!=0){
switch(rval.ErrorCode){
case err_missing_argument:
throw new DeviceAPIError(_3ad.MISSING_ARG_ERR,rval.ErrorMessage);
break;
case err_bad_argument:
throw new DeviceAPIError(_3ad.INVALID_ARG_ERR,rval.ErrorMessage);
break;
case err_ServiceNotSupported:
throw new DeviceAPIError(_3ad.NOT_SUPPORTED_ERR,rval.ErrorMessage);
break;
case err_InvalidService_Argument:
throw new DeviceAPIError(_3ad.INVALID_ARG_ERR,rval.ErrorMessage);
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
function __sp_landmarks_add(_3b7,_3b8,_3b9){
try{
var _3ba=new DeviceAPIError(0,"dummy");
var _3bb=true;
if(_3b7===undefined){
throw new DeviceAPIError(_3ba.MISSING_ARG_ERR,"AddSucessCallback is missing");
}else{
if(((_3b7===null)||(_3b7===""))&&(typeof (_3b7)!="number")){
throw new DeviceAPIError(_3ba.MISSING_ARG_ERR,"AddSucessCallback is missing");
}else{
if(typeof (_3b7)!="function"){
throw new DeviceAPIError(_3ba.INVALID_ARG_ERR,"invalid AddSucessCallback argument");
}
}
}
if(_3b8===undefined||_3b8===null){
throw new DeviceAPIError(_3ba.MISSING_ARG_ERR,"LandmarkItem is missing");
}else{
if(typeof (_3b8)!=="object"){
throw new DeviceAPIError(_3ba.INVALID_ARG_ERR,"invalid LandmarkItem argument");
}
}
if((_3b9!=undefined)){
if((!_3b9)&&(typeof (_3b9)!="number")){
_3bb=false;
}else{
if((typeof (_3b9)!="function")){
throw new DeviceAPIError(_3ba.INVALID_ARG_ERR,"invalid ErrorCallback callback");
}
}
}else{
_3bb=false;
}
this.invoker=function(arg1,arg2,arg3){
var id=null;
if(arg2==4||arg3.ErrorCode){
var _3c0=convertFromPS2JS(arg3.ErrorCode);
var _3c1=new DeviceAPIError(_3c0,arg3.ErrorMessage);
if(_3bb){
_3b9(_3c1);
}
}else{
if(arg3.ReturnValue){
id=arg3.ReturnValue;
}
_3b7(id);
}
};
var str="addLandmark: ";
var _3c3=new Object();
modifyObjectBaseProp(_3c3);
_3c3.Type="Landmark";
_3c3.Data=new __sp_landmark_obj(_3b8,str);
var rval=this.so.IDataSource.Add(_3c3,this.invoker);
if(rval.ErrorCode!=0){
switch(rval.ErrorCode){
case err_missing_argument:
throw new DeviceAPIError(_3ba.MISSING_ARG_ERR,rval.ErrorMessage);
break;
case err_bad_argument:
throw new DeviceAPIError(_3ba.INVALID_ARG_ERR,rval.ErrorMessage);
break;
case err_ServiceNotSupported:
throw new DeviceAPIError(_3ba.NOT_SUPPORTED_ERR,rval.ErrorMessage);
break;
case err_InvalidService_Argument:
throw new DeviceAPIError(_3ba.INVALID_ARG_ERR,rval.ErrorMessage);
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
function __sp_landmarks_delete(_3c5,_3c6,_3c7){
try{
var _3c8=new DeviceAPIError(0,"dummy");
var _3c9=true;
if(_3c5===undefined){
throw new DeviceAPIError(_3c8.MISSING_ARG_ERR,"SucessCallback is missing");
}else{
if(((_3c5===null)||(_3c5===""))&&(typeof (_3c5)!="number")){
throw new DeviceAPIError(_3c8.MISSING_ARG_ERR,"SucessCallback is missing");
}else{
if(typeof (_3c5)!="function"){
throw new DeviceAPIError(_3c8.INVALID_ARG_ERR,"invalid SucessCallback argument");
}
}
}
if(_3c6===undefined||_3c6===null){
throw new DeviceAPIError(_3c8.MISSING_ARG_ERR,"landmarkId is missing");
}else{
if(typeof (_3c6)!=="string"){
throw new DeviceAPIError(_3c8.INVALID_ARG_ERR,"invalid landmarkId argument");
}
}
if((_3c7!=undefined)){
if((!_3c7)&&(typeof (_3c7)!="number")){
_3c9=false;
}else{
if((typeof (_3c7)!="function")){
throw new DeviceAPIError(_3c8.INVALID_ARG_ERR,"invalid ErrorCallback callback");
}
}
}else{
_3c9=false;
}
this.invoker=function(arg1,arg2,arg3){
if(arg2==4||arg3.ErrorCode){
var _3cd=convertFromPS2JS(arg3.ErrorCode);
var _3ce=new DeviceAPIError(_3cd,arg3.ErrorMessage);
if(_3c9){
_3c7(_3ce);
}
}else{
_3c5();
}
};
var _3cf=new Object();
modifyObjectBaseProp(_3cf);
_3cf.Type="Landmark";
_3cf.Data=new Object();
modifyObjectBaseProp(_3cf.Data);
_3cf.Data.id=_3c6;
var rval=this.so.IDataSource.Delete(_3cf,this.invoker);
if(rval.ErrorCode!=0){
switch(rval.ErrorCode){
case err_missing_argument:
throw new DeviceAPIError(_3c8.MISSING_ARG_ERR,rval.ErrorMessage);
break;
case err_bad_argument:
throw new DeviceAPIError(_3c8.INVALID_ARG_ERR,rval.ErrorMessage);
break;
case err_ServiceNotSupported:
throw new DeviceAPIError(_3c8.NOT_SUPPORTED_ERR,rval.ErrorMessage);
break;
case err_InvalidService_Argument:
throw new DeviceAPIError(_3c8.INVALID_ARG_ERR,rval.ErrorMessage);
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
function __sp_landmarks_update(_3d1,_3d2,_3d3){
try{
var _3d4=new DeviceAPIError(0,"dummy");
var _3d5=true;
if(_3d1===undefined){
throw new DeviceAPIError(_3d4.MISSING_ARG_ERR,"SuccessCallback is missing");
}else{
if(((_3d1===null)||(_3d1===""))&&(typeof (_3d1)!="number")){
throw new DeviceAPIError(_3d4.MISSING_ARG_ERR,"SuccessCallback is missing");
}else{
if(typeof (_3d1)!="function"){
throw new DeviceAPIError(_3d4.INVALID_ARG_ERR,"invalid SuccessCallback argument");
}
}
}
if(_3d2===undefined||_3d2===null){
throw new DeviceAPIError(_3d4.MISSING_ARG_ERR,"LandmarkItem is missing");
}else{
if(typeof (_3d2)!=="object"){
throw new DeviceAPIError(_3d4.INVALID_ARG_ERR,"invalid LandmarkItem argument");
}
}
if((_3d3!=undefined)){
if((!_3d3)&&(typeof (_3d3)!="number")){
_3d5=false;
}else{
if((typeof (_3d3)!="function")){
throw new DeviceAPIError(_3d4.INVALID_ARG_ERR,"invalid ErrorCallback callback");
}
}
}else{
_3d5=false;
}
this.invoker=function(arg1,arg2,arg3){
if(arg2==4||arg3.ErrorCode){
var _3d9=convertFromPS2JS(arg3.ErrorCode);
var _3da=new DeviceAPIError(_3d9,arg3.ErrorMessage);
if(_3d5){
_3d3(_3da);
}
}else{
_3d1();
}
};
var str="updateLandmark: ";
var _3dc=new Object();
modifyObjectBaseProp(_3dc);
_3dc.Type="Landmark";
_3dc.Data=new __sp_landmark_obj(_3d2,str);
var rval=this.so.IDataSource.Add(_3dc,this.invoker);
if(rval.ErrorCode!=0){
switch(rval.ErrorCode){
case err_missing_argument:
throw new DeviceAPIError(_3d4.MISSING_ARG_ERR,rval.ErrorMessage);
break;
case err_bad_argument:
throw new DeviceAPIError(_3d4.INVALID_ARG_ERR,rval.ErrorMessage);
break;
case err_ServiceNotSupported:
throw new DeviceAPIError(_3d4.NOT_SUPPORTED_ERR,rval.ErrorMessage);
break;
case err_InvalidService_Argument:
throw new DeviceAPIError(_3d4.INVALID_ARG_ERR,rval.ErrorMessage);
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
function __sp_landmarks_category_update(_3de,_3df,_3e0){
try{
var _3e1=new DeviceAPIError(0,"dummy");
var _3e2=true;
if(_3de===undefined){
throw new DeviceAPIError(_3e1.MISSING_ARG_ERR,"SucessCallback is missing");
}else{
if(((_3de===null)||(_3de===""))&&(typeof (_3de)!="number")){
throw new DeviceAPIError(_3e1.MISSING_ARG_ERR,"SucessCallback is missing");
}else{
if(typeof (_3de)!="function"){
throw new DeviceAPIError(_3e1.INVALID_ARG_ERR,"invalid SucessCallback argument");
}
}
}
if(_3df===undefined||_3df===null){
throw new DeviceAPIError(_3e1.MISSING_ARG_ERR,"CategoryItem is missing");
}else{
if(typeof (_3df)!=="object"){
throw new DeviceAPIError(_3e1.INVALID_ARG_ERR,"invalid CategoryItem argument");
}
}
if((_3e0!=undefined)){
if((!_3e0)&&(typeof (_3e0)!="number")){
_3e2=false;
}else{
if((typeof (_3e0)!="function")){
throw new DeviceAPIError(_3e1.INVALID_ARG_ERR,"invalid ErrorCallback callback");
}
}
}else{
_3e2=false;
}
this.invoker=function(arg1,arg2,arg3){
if(arg2==4||arg3.ErrorCode){
var _3e6=convertFromPS2JS(arg3.ErrorCode);
var _3e7=new DeviceAPIError(_3e6,arg3.ErrorMessage);
if(_3e2){
_3e0(_3e7);
}
}else{
_3de();
}
};
var _3e8=new Object();
modifyObjectBaseProp(_3e8);
_3e8.Type="Category";
_3e8.Data=new __sp_category_obj(_3df);
var rval=this.so.IDataSource.Add(_3e8,this.invoker);
if(rval.ErrorCode!=0){
switch(rval.ErrorCode){
case err_missing_argument:
throw new DeviceAPIError(_3e1.MISSING_ARG_ERR,rval.ErrorMessage);
break;
case err_bad_argument:
throw new DeviceAPIError(_3e1.INVALID_ARG_ERR,rval.ErrorMessage);
break;
case err_ServiceNotSupported:
throw new DeviceAPIError(_3e1.NOT_SUPPORTED_ERR,rval.ErrorMessage);
break;
case err_InvalidService_Argument:
throw new DeviceAPIError(_3e1.INVALID_ARG_ERR,rval.ErrorMessage);
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
function __sp_landmarks_category_delete(_3ea,_3eb,_3ec){
try{
var _3ed=new DeviceAPIError(0,"dummy");
var _3ee=true;
if(_3ea===undefined){
throw new DeviceAPIError(_3ed.MISSING_ARG_ERR,"SucessCallback is missing");
}else{
if(((_3ea===null)||(_3ea===""))&&(typeof (_3ea)!="number")){
throw new DeviceAPIError(_3ed.MISSING_ARG_ERR,"SucessCallback is missing");
}else{
if(typeof (_3ea)!="function"){
throw new DeviceAPIError(_3ed.INVALID_ARG_ERR,"invalid SucessCallback argument");
}
}
}
if(_3eb===undefined||_3eb===null){
throw new DeviceAPIError(_3ed.MISSING_ARG_ERR,"categoryId is missing");
}else{
if(typeof (_3eb)!=="string"){
throw new DeviceAPIError(_3ed.INVALID_ARG_ERR,"invalid categoryId argument");
}
}
if((_3ec!=undefined)){
if((!_3ec)&&(typeof (_3ec)!="number")){
_3ee=false;
}else{
if((typeof (_3ec)!="function")){
throw new DeviceAPIError(_3ed.INVALID_ARG_ERR,"invalid ErrorCallback callback");
}
}
}else{
_3ee=false;
}
this.invoker=function(arg1,arg2,arg3){
if(arg2==4||arg3.ErrorCode){
var _3f2=convertFromPS2JS(arg3.ErrorCode);
var _3f3=new DeviceAPIError(_3f2,arg3.ErrorMessage);
if(_3ee){
_3ec(_3f3);
}
}else{
_3ea();
}
};
var _3f4=new Object();
modifyObjectBaseProp(_3f4);
_3f4.Type="Category";
_3f4.Data=new Object();
modifyObjectBaseProp(_3f4.Data);
_3f4.Data.id=_3eb;
var rval=this.so.IDataSource.Delete(_3f4,this.invoker);
if(rval.ErrorCode!=0){
switch(rval.ErrorCode){
case err_missing_argument:
throw new DeviceAPIError(_3ed.MISSING_ARG_ERR,rval.ErrorMessage);
break;
case err_bad_argument:
throw new DeviceAPIError(_3ed.INVALID_ARG_ERR,rval.ErrorMessage);
break;
case err_ServiceNotSupported:
throw new DeviceAPIError(_3ed.NOT_SUPPORTED_ERR,rval.ErrorMessage);
break;
case err_InvalidService_Argument:
throw new DeviceAPIError(_3ed.INVALID_ARG_ERR,rval.ErrorMessage);
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
function __sp_landmarks_getList(_3f6,_3f7,_3f8){
try{
var _3f9=new DeviceAPIError(0,"dummy");
var _3fa=true;
var _3fb=false;
var _3fc=false;
if(_3f6===undefined){
throw new DeviceAPIError(_3f9.MISSING_ARG_ERR,"SucessCallback is missing");
}else{
if(((_3f6===null)||(_3f6===""))&&(typeof (_3f6)!="number")){
throw new DeviceAPIError(_3f9.MISSING_ARG_ERR,"SucessCallback is missing");
}else{
if(typeof (_3f6)!="function"){
throw new DeviceAPIError(_3f9.INVALID_ARG_ERR,"invalid SucessCallback argument");
}
}
}
if(_3f7!==undefined){
if((typeof (_3f7)!="object")){
if((_3f7===null||_3f7==="")&&(typeof (_3f7)!="number")){
_3fb=true;
_3fc=true;
}else{
if(typeof (_3f7)=="string"){
_3fb=true;
_3fc=false;
}else{
throw new DeviceAPIError(_3f9.INVALID_ARG_ERR,"invalid match criteria");
}
}
}
if(typeof (_3f7)!="object"){
if(!_3fb){
throw new DeviceAPIError(_3f9.INVALID_ARG_ERR,"invalid match criteria");
}
}
}
if((_3f8!=undefined)){
if((!_3f8)&&(typeof (_3f8)!="number")){
_3fa=false;
}else{
if((typeof (_3f8)!="function")){
throw new DeviceAPIError(_3f9.INVALID_ARG_ERR,"invalid error callback");
}
}
}else{
_3fa=false;
}
var _3fd=new Object();
modifyObjectBaseProp(_3fd);
_3fd.Type="Landmark";
if(_3f7){
_3fd.Filter=new Object();
modifyObjectBaseProp(_3fd.Filter);
if(typeof _3f7=="object"){
if(_3f7.name!==undefined){
_3fd.Filter.LandmarkName=_3f7.name;
}
if(_3f7.description!==undefined){
_3fd.Filter.LandmarkDesc=_3f7.description;
}
if(_3f7.categoryId!==undefined){
_3fd.Filter.categoryId=_3f7.categoryId;
}
if(_3f7.position!==undefined){
if((_3f7.position!==null)&&(_3f7.position!=="")&&(typeof (_3f7.position)!="object")){
throw new DeviceAPIError(_3f9.INVALID_ARG_ERR,"position must be an object");
}
if(_3f7.position===null){
}
if(_3f7.position===""){
throw new DeviceAPIError(_3f9.INVALID_ARG_ERR,"position must be an object");
}
if(_3f7.position){
_3fd.Filter.LandmarkPosition=new __sp_landmark_position_obj(_3f7.position);
}
}
if(_3f7.coverageRadiusUsed!==undefined){
_3fd.Filter.CoverageRadiusOption=_3f7.coverageRadiusUsed;
}
if(_3f7.searchRadius!==undefined){
_3fd.Filter.MaximumDistance=_3f7.searchRadius;
}
if(_3f7.area!==undefined){
if((_3f7.area!==null)&&(_3f7.area!=="")&&(typeof (_3f7.area)!="object")){
throw new DeviceAPIError(_3f9.INVALID_ARG_ERR,"area must be an object");
}
if(_3f7.area===null){
_3fd.Filter.BoundedArea=null;
}
if(_3f7.area===""){
throw new DeviceAPIError(_3f9.INVALID_ARG_ERR,"area must be an object");
}
if(_3f7.area){
_3fd.Filter.LandmarkPosition=new __sp_landmark_bounded_area_obj(_3f7.area);
}
}
}else{
if(__device_typeof(_3f7).toLowerCase()=="string"){
_3fd.Filter.LandmarkName=_3f7;
}
}
}
this.invoker=function(arg1,arg2,arg3){
var iter=null;
if(arg3.ErrorCode||(arg2==4)){
var _402=convertFromPS2JS(arg3.ErrorCode);
var _403=new DeviceAPIError(_402,arg3.ErrorMessage);
if(_3fa){
_3f8(_403);
}
}else{
if(arg3.ReturnValue){
iter=new __sp_landmarks_iterator(arg3.ReturnValue);
}
_3f6(iter);
}
};
var rval=this.so.IDataSource.GetList(_3fd,this.invoker);
if(rval.ErrorCode!=0){
switch(rval.ErrorCode){
case 1003:
throw new DeviceAPIError(_3f9.MISSING_ARG_ERR,rval.ErrorMessage);
break;
case 1002:
throw new DeviceAPIError(_3f9.INVALID_ARG_ERR,rval.ErrorMessage);
break;
case 1004:
throw new DeviceAPIError(_3f9.NOT_SUPPORTED_ERR,rval.ErrorMessage);
break;
case 1000:
throw new DeviceAPIError(_3f9.INVALID_ARG_ERR,rval.ErrorMessage);
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
function __sp_landmarks_import(_405,_406,_407,_408){
try{
var _409=new DeviceAPIError(0,"dummy");
var _40a=true;
if(_405===undefined){
throw new DeviceAPIError(_409.MISSING_ARG_ERR,"LandmarksItrCallback is missing");
}else{
if(((_405===null)||(_405===""))&&(typeof (_405)!="number")){
throw new DeviceAPIError(_409.MISSING_ARG_ERR,"LandmarksItrCallback is missing");
}else{
if(typeof (_405)!="function"){
throw new DeviceAPIError(_409.INVALID_ARG_ERR,"invalid LandmarksItrCallback argument");
}
}
}
if(_406===undefined||_406===null){
throw new DeviceAPIError(_409.MISSING_ARG_ERR,"sourceFileUri is missing");
}else{
if(typeof (_406)!=="string"){
throw new DeviceAPIError(_409.INVALID_ARG_ERR,"invalid sourceFileUri argument");
}
}
if(_407===undefined||_407===null){
throw new DeviceAPIError(_409.MISSING_ARG_ERR,"mimetype is missing");
}else{
if(typeof (_407)!=="string"){
throw new DeviceAPIError(_409.INVALID_ARG_ERR,"invalid mimetype argument");
}
}
if((_408!=undefined)){
if((!_408)&&(typeof (_408)!="number")){
_40a=false;
}else{
if((typeof (_408)!="function")){
throw new DeviceAPIError(_409.INVALID_ARG_ERR,"invalid ErrorCallback callback");
}
}
}else{
_40a=false;
}
this.invoker=function(arg1,arg2,arg3){
var iter=null;
if(arg2==4||arg3.ErrorCode){
var _40f=convertFromPS2JS(arg3.ErrorCode);
var _410=new DeviceAPIError(_40f,arg3.ErrorMessage);
if(_40a){
_408(_410);
}
}else{
if(arg3.ReturnValue){
iter=new __sp_landmarks_iterator(arg3.ReturnValue);
}
_405(iter);
}
};
var _411=new Object();
modifyObjectBaseProp(_411);
_411.Type="Landmark";
_411.Data=new Object();
modifyObjectBaseProp(_411.Data);
if(_406.slice(0,7)=="file://"){
_406=_406.slice(7);
}else{
if(_406.slice(0,8)=="file:///"){
_406=_406.slice(8);
}else{
throw new DeviceAPIError(_409.INVALID_ARG_ERR,"sourceFileUri is not in URI format");
}
}
while(_406.search("/")!=-1){
_406=_406.replace("/","\\");
}
_411.Data.SourceFile=_406;
_411.Data.MimeType=_407;
var rval=this.so.IDataSource.Import(_411,this.invoker);
if(rval.ErrorCode!=0){
switch(rval.ErrorCode){
case err_missing_argument:
throw new DeviceAPIError(_409.MISSING_ARG_ERR,rval.ErrorMessage);
break;
case err_bad_argument:
throw new DeviceAPIError(_409.INVALID_ARG_ERR,rval.ErrorMessage);
break;
case err_ServiceNotSupported:
throw new DeviceAPIError(_409.NOT_SUPPORTED_ERR,rval.ErrorMessage);
break;
case err_InvalidService_Argument:
throw new DeviceAPIError(_409.INVALID_ARG_ERR,rval.ErrorMessage);
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
function __sp_landmarks_export(_413,_414,_415,_416,_417){
try{
var _418=new DeviceAPIError(0,"dummy");
var _419=true;
if(_413===undefined){
throw new DeviceAPIError(_418.MISSING_ARG_ERR,"SuccessCallback is missing");
}else{
if(((_413===null)||(_413===""))&&(typeof (_413)!="number")){
throw new DeviceAPIError(_418.MISSING_ARG_ERR,"SuccessCallback is missing");
}else{
if(typeof (_413)!="function"){
throw new DeviceAPIError(_418.INVALID_ARG_ERR,"invalid SuccessCallback argument");
}
}
}
if(_414===undefined||_414===null){
throw new DeviceAPIError(_418.MISSING_ARG_ERR,"landmarkIdList is missing");
}else{
if(typeof (_414)!=="object"){
throw new DeviceAPIError(_418.INVALID_ARG_ERR,"invalid landmarkIdList argument");
}
}
if(_415===undefined||_415===null){
throw new DeviceAPIError(_418.MISSING_ARG_ERR,"destFileUri is missing");
}else{
if(typeof (_415)!=="string"){
throw new DeviceAPIError(_418.INVALID_ARG_ERR,"invalid destFileUri argument");
}
}
if(_416===undefined||_416===null){
throw new DeviceAPIError(_418.MISSING_ARG_ERR,"mimetype is missing");
}else{
if(typeof (_416)!=="string"){
throw new DeviceAPIError(_418.INVALID_ARG_ERR,"invalid mimetype argument");
}
}
if((_417!=undefined)){
if((!_417)&&(typeof (_417)!="number")){
_419=false;
}else{
if((typeof (_417)!="function")){
throw new DeviceAPIError(_418.INVALID_ARG_ERR,"invalid ErrorCallback callback");
}
}
}else{
_419=false;
}
this.invoker=function(arg1,arg2,arg3){
if(arg2==4||arg3.ErrorCode){
var _41d=convertFromPS2JS(arg3.ErrorCode);
var _41e=new DeviceAPIError(_41d,arg3.ErrorMessage);
if(_419){
_417(_41e);
}
}else{
_413();
}
};
var _41f=new Object();
modifyObjectBaseProp(_41f);
_41f.Type="Landmark";
_41f.Data=new Object();
modifyObjectBaseProp(_41f.Data);
if(_415.slice(0,7)=="file://"){
_415=_415.slice(7);
}else{
if(_415.slice(0,8)=="file:///"){
_415=_415.slice(8);
}else{
throw new DeviceAPIError(_418.INVALID_ARG_ERR,"destFileUri is not in URI format");
}
}
while(_415.search("/")!=-1){
_415=_415.replace("/","\\");
}
_41f.Data.DestinationFile=_415;
_41f.Data.IdList=_414;
_41f.Data.MimeType=_416;
var rval=this.so.IDataSource.Export(_41f,this.invoker);
if(rval.ErrorCode!=0){
switch(rval.ErrorCode){
case err_missing_argument:
throw new DeviceAPIError(_418.MISSING_ARG_ERR,rval.ErrorMessage);
break;
case err_bad_argument:
throw new DeviceAPIError(_418.INVALID_ARG_ERR,rval.ErrorMessage);
break;
case err_ServiceNotSupported:
throw new DeviceAPIError(_418.NOT_SUPPORTED_ERR,rval.ErrorMessage);
break;
case err_InvalidService_Argument:
throw new DeviceAPIError(_418.INVALID_ARG_ERR,rval.ErrorMessage);
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
function __sp_landmarks_organize(_421,_422,_423,_424,_425){
try{
var _426=new DeviceAPIError(0,"dummy");
var _427=true;
if(_421===undefined){
throw new DeviceAPIError(_426.MISSING_ARG_ERR,"SuccessCallback is missing");
}else{
if(((_421===null)||(_421===""))&&(typeof (_421)!="number")){
throw new DeviceAPIError(_426.MISSING_ARG_ERR,"SuccessCallback is missing");
}else{
if(typeof (_421)!="function"){
throw new DeviceAPIError(_426.INVALID_ARG_ERR,"invalid SuccessCallback argument");
}
}
}
if(_422===undefined||_422===null){
throw new DeviceAPIError(_426.MISSING_ARG_ERR,"landmarkIdList is missing");
}else{
if(typeof (_422)!=="object"){
throw new DeviceAPIError(_426.INVALID_ARG_ERR,"invalid LandmarkItem argument");
}
}
if(_423===undefined||_423===null){
throw new DeviceAPIError(_426.MISSING_ARG_ERR,"categoryId is missing");
}else{
if(typeof (_423)!=="string"){
throw new DeviceAPIError(_426.INVALID_ARG_ERR,"invalid categoryId argument");
}
}
if(_424===undefined||_424===null){
_424=true;
}else{
if(typeof (_424)!=="boolean"){
throw new DeviceAPIError(_426.INVALID_ARG_ERR,"invalid associate argument");
}
}
if((_425!=undefined)){
if((!_425)&&(typeof (_425)!="number")){
_427=false;
}else{
if((typeof (_425)!="function")){
throw new DeviceAPIError(_426.INVALID_ARG_ERR,"invalid ErrorCallback callback");
}
}
}else{
_427=false;
}
this.invoker=function(arg1,arg2,arg3){
if(arg2==4||arg3.ErrorCode){
var _42b=convertFromPS2JS(arg3.ErrorCode);
var _42c=new DeviceAPIError(_42b,arg3.ErrorMessage);
if(_427){
_425(_42c);
}
}else{
_421();
}
};
var _42d=new Object();
modifyObjectBaseProp(_42d);
_42d.Type="Landmark";
_42d.Data=new Object();
modifyObjectBaseProp(_42d.Data);
_42d.Data.id=_423;
_42d.Data.IdList=_422;
if(_424){
_42d.OperationType="Associate";
}else{
_42d.OperationType="Disassociate";
}
var rval=this.so.IDataSource.Organise(_42d,this.invoker);
if(rval.ErrorCode!=0){
switch(rval.ErrorCode){
case err_missing_argument:
throw new DeviceAPIError(_426.MISSING_ARG_ERR,rval.ErrorMessage);
break;
case err_bad_argument:
throw new DeviceAPIError(_426.INVALID_ARG_ERR,rval.ErrorMessage);
break;
case err_ServiceNotSupported:
throw new DeviceAPIError(_426.NOT_SUPPORTED_ERR,rval.ErrorMessage);
break;
case err_InvalidService_Argument:
throw new DeviceAPIError(_426.INVALID_ARG_ERR,rval.ErrorMessage);
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
function __sp_landmarks_cancel(_42f){
try{
if(_42f===undefined||_42f===null){
throw new DeviceAPIError(error.MISSING_ARG_ERR,"transactionId is missing");
}else{
if(typeof (_42f)!=="number"){
throw new DeviceAPIError(error.INVALID_ARG_ERR,"invalid transactionId argument");
}
}
var _430=new Object();
modifyObjectBaseProp(_430);
_430.TransactionID=_42f;
var rval=this.so.IDataSource.Cancel(_430);
if(rval.ErrorCode!=0){
switch(rval.ErrorCode){
case err_missing_argument:
throw new DeviceAPIError(error.MISSING_ARG_ERR,rval.ErrorMessage);
break;
case err_bad_argument:
throw new DeviceAPIError(error.INVALID_ARG_ERR,rval.ErrorMessage);
break;
case err_ServiceNotSupported:
throw new DeviceAPIError(error.NOT_SUPPORTED_ERR,rval.ErrorMessage);
break;
case err_InvalidService_Argument:
throw new DeviceAPIError(error.INVALID_ARG_ERR,rval.ErrorMessage);
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

