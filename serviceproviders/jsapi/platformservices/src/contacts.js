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

function __device_contacts_descriptor(provider){
  this.interfaceName = provider.interfaceName;
  this.version = provider.version;
}

function __device_contacts_startEditor(callback, contact, ErrorCallback){
 return this.provider.startEditor(callback, contact, ErrorCallback);
}

function __device_contacts_getContacts(callback, match, sortOrder, ErrorCallback ){
  return this.provider.getContacts(callback, match, sortOrder, ErrorCallback );
}

function __device_contacts_add(contact){
  return this.provider.addContact(contact);
}

function __device_contacts_update(contact){
  this.provider.updateContact(contact);
}

function __device_contacts_delete(id){
  this.provider.deleteContacts(id);
}

function __device_contacts_getContactInfo(id){
  return this.provider.getContactInfo(id);
}
function __device_contacts_addGroup(groupName){
	return this.provider.addGroup(groupName);
}

function __device_contacts_getGroups(callback, ErrorCallback){
    return this.provider.getGroups(callback, ErrorCallback);
}

function __device_contacts_deleteGroups(id){
	this.provider.deleteGroups(id);
}

function __device_contacts_addContactsToGroup(groupId,id)
{
	this.provider.addContactsToGroup(groupId,id);
}

function __device_contacts_getContactIds(callback, match, sortOrder, ErrorCallback)
{
	return this.provider.getContactIds(callback, match, sortOrder, ErrorCallback);
}

function __device_contacts_getGroupIds(callback, ErrorCallback)
{
	return this.provider.getGroupIds(callback, ErrorCallback);
}

function __device_contacts_removeContactsFromGroup(groupId,id)
{
	this.provider.removeContactsFromGroup(groupId,id);
}

function __device_contacts_cancel(transactionId)
{
	this.provider.cancel(transactionId);
}

function __device_contacts_updateGroup(group)
{
	this.provider.updateGroup(group);
}

function __device_contacts_getGroupInfo(grpid)
{
	return this.provider.getGroupInfo(grpid);
}

// Private location prototype: called from service factory
function __device_contacts(provider){
//alert("inside ");
  //Private properties
  this.provider = provider;
  //Read-only properties
  this.interfaceName = provider.descriptor.interfaceName;
  this.version = provider.descriptor.version;
  
    //constants
  this.SORT_ASCENDING = 0;
  this.SORT_DESCENDING = 1;
  
  //Core methods
  this.startEditor = __device_contacts_startEditor;
  //Extended methods
  this.getContacts = __device_contacts_getContacts;
  this.addContact = __device_contacts_add;
  this.updateContact = __device_contacts_update;
  this.deleteContacts = __device_contacts_delete;
  this.getContactInfo = __device_contacts_getContactInfo;
  this.addGroup = __device_contacts_addGroup;
  this.getGroups = __device_contacts_getGroups;
  this.deleteGroups = __device_contacts_deleteGroups;
  this.addContactsToGroup = __device_contacts_addContactsToGroup;
  this.getContactIds = __device_contacts_getContactIds;
  this.getGroupIds = __device_contacts_getGroupIds;
  this.removeContactsFromGroup = __device_contacts_removeContactsFromGroup;
  this.cancel = __device_contacts_cancel;
  this.updateGroup = __device_contacts_updateGroup;
  this.getGroupInfo = __device_contacts_getGroupInfo;
}

// contacts service interface

// Namepace: com.nokia.device.service

var __device_contacts_service_entry = {"name": null, 
					  "version": null,
					  "proto": __device_contacts,
					  "descriptor": __device_contacts_descriptor,
					  "providers": [{"descriptor": __sp_contacts_descriptor, "instance": __sp_contacts_instance}]
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
// Table of user callbacks. These are "indexed" by transaction IDs.
// These need to be global since the actual sp callback does
// not have the location instance object in its scope chain

/*
 if((typeof (com.nokia.device.contacts) == 'undefined'))
 {
 com.nokia.device.contacts = {};
 }*/
nokia.device.contacts.SORT_ASCENDING = 0;
nokia.device.contacts.SORT_DESCENDING = 1;


//nokia.devive.
//SORT_ASCENDING = 0;
//SORT_DESCENDING = 1;

function __sp_contacts_descriptor(){
  //Read-only properties 
   this.interfaceName = "contacts";
  if(window.__Service_Interface_Ver){
//	alert('in __sp_contacts_descriptor'+window.__Service_Interface_Ver);
	this.version =__Service_Interface_Ver;
	}
  else{
	this.version =1.0;
	}
  //Class-static properties 
}


/*--------- device<->sp mapping functions --------*/
function __s60_enumerate_contact_object(object, namespace, func, param){
    try {
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
            if (value instanceof Array) {
                func(propname, value, param);
            }
            else 
                if (value instanceof Date) {
                    func(propname, value, param);
                }
                else 
                    if (typeof value == "object") {
                        __s60_enumerate_contact_object(value, propname, func, param);
                    }
                    else {
                        func(propname, value, param);
                    }
        }
    } 
    
    catch (e) {
		throw e;
		//alert("exception in __s60_enumerate_contact_object" + e.toString());
    }
}

// Map from device contact to sp contact

// TBD: labels need localization
function __sp_contact_extract(name, value, sp_contact){
    //__device_debug("sp_contact_extract: " + name + " " + value); 
    switch (name) {
        case "name.last":
            sp_contact.LastName = {};
            modifyObjectBaseProp(sp_contact.LastName);
            sp_contact.LastName.Label = "Last name";
            sp_contact.LastName.Value = value;
            break;
        case "name.first":
            sp_contact.FirstName = {};
            modifyObjectBaseProp(sp_contact.FirstName);
            sp_contact.FirstName.Label = "First name";
            sp_contact.FirstName.Value = value;
            break;
        case "name.middle":
            sp_contact.MiddleName = {};
            modifyObjectBaseProp(sp_contact.MiddleName);
            sp_contact.MiddleName.Label = "Middle name";
            sp_contact.MiddleName.Value = value;
            break;
        case "name.prefix":
            sp_contact.Prefix = {};
            modifyObjectBaseProp(sp_contact.Prefix);
            sp_contact.Prefix.Label = "Prefix";
            sp_contact.Prefix.Value = value;
            break;
        case "name.suffix":
            sp_contact.Suffix = {};
            modifyObjectBaseProp(sp_contact.Suffix);
            sp_contact.Suffix.Label = "Suffix";
            sp_contact.Suffix.Value = value;
            break;
        case "tel.land":
            sp_contact.LandPhoneGen = {};
            modifyObjectBaseProp(sp_contact.LandPhoneGen);
            sp_contact.LandPhoneGen.Label = "Landline";
            sp_contact.LandPhoneGen.Value = value;
            break;
        case "tel.mobile":
            sp_contact.MobilePhoneGen = {};
            modifyObjectBaseProp(sp_contact.MobilePhoneGen);
            sp_contact.MobilePhoneGen.Label = "Mobile";
            sp_contact.MobilePhoneGen.Value = value;
            break;
        case "tel.video":
            sp_contact.VideoNumberGen = {};
            modifyObjectBaseProp(sp_contact.VideoNumberGen);
            sp_contact.VideoNumberGen.Label = "Video";
            sp_contact.VideoNumberGen.Value = value;
            break;
        case "tel.fax":
            sp_contact.FaxNumberGen = {};
            modifyObjectBaseProp(sp_contact.FaxNumberGen);
            sp_contact.FaxNumberGen.Label = "Fax";
            sp_contact.FaxNumberGen.Value = value;
            break;
        case "tel.voip":
		//alert("adding gen"+value);
            sp_contact.VOIPGen = {};
            modifyObjectBaseProp(sp_contact.VOIPGen);
            sp_contact.VOIPGen.Label = "Voip";
            sp_contact.VOIPGen.Value = value;
            break;
        case "tel.home.land":
            sp_contact.LandPhoneHome = {};
            modifyObjectBaseProp(sp_contact.LandPhoneHome);
            sp_contact.LandPhoneHome.Label = "Home Landline";
            sp_contact.LandPhoneHome.Value = value;
            break;
        case "tel.home.mobile":
            sp_contact.MobilePhoneHome = {};
            modifyObjectBaseProp(sp_contact.MobilePhoneHome);
            sp_contact.MobilePhoneHome.Label = "Home Mobile";
            sp_contact.MobilePhoneHome.Value = value;
            break;
        case "tel.home.video":
            sp_contact.VideoNumberHome = {};
            modifyObjectBaseProp(sp_contact.VideoNumberHome);
            sp_contact.VideoNumberHome.Label = "Home Video";
            sp_contact.VideoNumberHome.Value = value;
            break;
        case "tel.home.fax":
            sp_contact.FaxNumberHome = {};
            modifyObjectBaseProp(sp_contact.FaxNumberHome);
            sp_contact.FaxNumberHome.Label = "Home Fax";
            sp_contact.FaxNumberHome.Value = value;
            break;
        case "tel.home.voip":
			//alert("adding home"+value);
            sp_contact.VoipHome = {};
            modifyObjectBaseProp(sp_contact.VoipHome);
            sp_contact.VoipHome.Label = "Home Voip";
            sp_contact.VoipHome.Value = value;
            break;
        case "tel.work.land":
            sp_contact.LandPhoneWork = {};
            modifyObjectBaseProp(sp_contact.LandPhoneWork);
            sp_contact.LandPhoneWork.Label = "Work Landline";
            sp_contact.LandPhoneWork.Value = value;
            break;
        case "tel.work.mobile":
            sp_contact.MobilePhoneWork = {};
            modifyObjectBaseProp(sp_contact.MobilePhoneWork);
            sp_contact.MobilePhoneWork.Label = "Work Mobile";
            sp_contact.MobilePhoneWork.Value = value;
            break;
        case "tel.work.video":
            sp_contact.VideoNumberWork = {};
            modifyObjectBaseProp(sp_contact.VideoNumberWork);
            sp_contact.VideoNumberWork.Label = "Work Video";
            sp_contact.VideoNumberWork.Value = value;
            break;
        case "tel.work.fax":
            sp_contact.FaxNumberWork = {};
            modifyObjectBaseProp(sp_contact.FaxNumberWork);
            sp_contact.FaxNumberWork.Label = "Work Fax";
            sp_contact.FaxNumberWork.Value = value;
            break;
        case "tel.work.voip":
		//alert("adding work"+value);
            sp_contact.VoipWork = {};
            modifyObjectBaseProp(sp_contact.VoipWork);
            sp_contact.VoipWork.Label = "Work Voip";
            sp_contact.VoipWork.Value = value;
            break;
        case "address.street":
            sp_contact.AddrStreetGen = {};
            modifyObjectBaseProp(sp_contact.AddrStreetGen);
            sp_contact.AddrStreetGen.Label = "Street Address";
            sp_contact.AddrStreetGen.Value = value;
            break;
        case "address.local":
            sp_contact.AddrLocalGen = {};
            modifyObjectBaseProp(sp_contact.AddrLocalGen);
            sp_contact.AddrLocalGen.Label = "City";
            sp_contact.AddrLocalGen.Value = value;
            break;
        case "address.region":
            sp_contact.AddrRegionGen = {};
            modifyObjectBaseProp(sp_contact.AddrRegionGen);
            sp_contact.AddrRegionGen.Label = "State/Province";
            sp_contact.AddrRegionGen.Value = value;
            break;
        case "address.code":
            sp_contact.AddrPostCodeGen = {};
            modifyObjectBaseProp(sp_contact.AddrPostCodeGen);
            sp_contact.AddrPostCodeGen.Label = "Postal code";
            sp_contact.AddrPostCodeGen.Value = value;
            break;
        case "address.country":
            sp_contact.AddrCountryGen = {};
            modifyObjectBaseProp(sp_contact.AddrCountryGen);
            sp_contact.AddrCountryGen.Label = "Country";
            sp_contact.AddrCountryGen.Value = value;
            break;
        case "address.email":
            sp_contact.EmailGen = {};
            modifyObjectBaseProp(sp_contact.EmailGen);
            sp_contact.EmailGen.Label = "EMail";
            sp_contact.EmailGen.Value = value;
            break;
        case "address.uri":
            sp_contact.URLGen = {};
            modifyObjectBaseProp(sp_contact.URLGen);
            sp_contact.URLGen.Label = "Website";
            sp_contact.URLGen.Value = value;
            break;
        case "address.home.street":
            sp_contact.AddrStreetHome = {};
            modifyObjectBaseProp(sp_contact.AddrStreetHome);
            sp_contact.AddrStreetHome.Label = "Home Address";
            sp_contact.AddrStreetHome.Value = value;
            break;
        case "address.home.local":
            sp_contact.AddrLocalHome = {};
            modifyObjectBaseProp(sp_contact.AddrLocalHome);
            sp_contact.AddrLocalHome.Label = "City";
            sp_contact.AddrLocalHome.Value = value;
            break;
        case "address.home.region":
            sp_contact.AddrRegionHome = {};
            modifyObjectBaseProp(sp_contact.AddrRegionHome);
            sp_contact.AddrRegionHome.Label = "State/Province";
            sp_contact.AddrRegionHome.Value = value;
            break;
        case "address.home.code":
            sp_contact.AddrPostCodeHome = {};
            modifyObjectBaseProp(sp_contact.AddrPostCodeHome);
            sp_contact.AddrPostCodeHome.Label = "Postal code";
            sp_contact.AddrPostCodeHome.Value = value;
            break;
        case "address.home.country":
            sp_contact.AddrCountryHome = {};
            modifyObjectBaseProp(sp_contact.AddrCountryHome);
            sp_contact.AddrCountryHome.Label = "Country";
            sp_contact.AddrCountryHome.Value = value;
            break;
        case "address.home.email":
            sp_contact.EmailHome = {};
            modifyObjectBaseProp(sp_contact.EmailHome);
            sp_contact.EmailHome.Label = "Home EMail";
            sp_contact.EmailHome.Value = value;
            break;
        case "address.home.uri":
            sp_contact.URLHome = {};
            modifyObjectBaseProp(sp_contact.URLHome);
            sp_contact.URLHome.Label = "Home Website";
            sp_contact.URLHome.Value = value;
            break;
        case "address.work.street":
            sp_contact.AddrStreetWork = {};
            modifyObjectBaseProp(sp_contact.AddrStreetWork);
            sp_contact.AddrStreetWork.Label = "Work Address";
            sp_contact.AddrStreetWork.Value = value;
            break;
        case "address.work.local":
            sp_contact.AddrLocalWork = {};
            modifyObjectBaseProp(sp_contact.AddrLocalWork);
            sp_contact.AddrLocalWork.Label = "City";
            sp_contact.AddrLocalWork.Value = value;
            break;
        case "address.work.region":
            sp_contact.AddrRegionWork = {};
            modifyObjectBaseProp(sp_contact.AddrRegionWork);
            sp_contact.AddrRegionWork.Label = "State/Province";
            sp_contact.AddrRegionWork.Value = value;
            break;
        case "address.work.code":
            sp_contact.AddrPostCodeWork = {};
            modifyObjectBaseProp(sp_contact.AddrPostCodeWork);
            sp_contact.AddrPostCodeWork.Label = "Postal code";
            sp_contact.AddrPostCodeWork.Value = value;
            break;
        case "address.work.country":
            sp_contact.AddrCountryWork = {};
            modifyObjectBaseProp(sp_contact.AddrCountryWork);
            sp_contact.AddrCountryWork.Label = "Country";
            sp_contact.AddrCountryWork.Value = value;
            break;
        case "address.work.email":
            sp_contact.EmailWork = {};
            modifyObjectBaseProp(sp_contact.EmailWork);
            sp_contact.EmailWork.Label = "Work EMail";
            sp_contact.EmailWork.Value = value;
            break;
        case "address.work.uri":
            sp_contact.URLWork = {};
            modifyObjectBaseProp(sp_contact.URLWork);
            sp_contact.URLWork.Label = "Work Website";
            sp_contact.URLWork.Value = value;
            break;
        case "company.name":
            sp_contact.CompanyName = {};
            modifyObjectBaseProp(sp_contact.CompanyName);
            sp_contact.CompanyName.Label = "Company";
            sp_contact.CompanyName.Value = value;
            break;
        case "company.title":
            sp_contact.JobTitle = {};
            modifyObjectBaseProp(sp_contact.JobTitle);
            sp_contact.JobTitle.Label = "Title";
            sp_contact.JobTitle.Value = value;
            break;
        case "id":
            sp_contact.id = value;
            break;
        case "notes":
            sp_contact.Note = {};
            modifyObjectBaseProp(sp_contact.Note);
            //sp_contact.Note = {};
            sp_contact.Note.Label = "Note";
            sp_contact.Note.Value = value;
            break;
        case "anniversary":
            sp_contact.Anniversary = {};
            modifyObjectBaseProp(sp_contact.Anniversary);
            //sp_contact.Anniversary = {};
            sp_contact.Anniversary.Label = "Anniversary";
            sp_contact.Anniversary.Value = value;
            break;
        case "birthday":
            sp_contact.Date = {};
            modifyObjectBaseProp(sp_contact.Date);
            //sp_contact.Date = {};
            sp_contact.Date.Label = "BirthDay";
            sp_contact.Date.Value = value;
            break;
        case "nickName":
            sp_contact.SecondName = {};
            modifyObjectBaseProp(sp_contact.SecondName);
            //sp_contact.SecondName = {};
            sp_contact.SecondName.Label = "NickName";
            sp_contact.SecondName.Value = value;
            break;
        case "photo":
            sp_contact.CallerObjImg = {};
            modifyObjectBaseProp(sp_contact.CallerObjImg);
            //sp_contact.CallerObjImg = {};
            sp_contact.CallerObjImg.Label = "CallerObjImg";
            sp_contact.CallerObjImg.Value = value;
            break;
        case "xspid":
            sp_contact.IMPP = {};
            modifyObjectBaseProp(sp_contact.IMPP);
            //sp_contact.IMPP = {};
            sp_contact.IMPP.Label = "IMPP";
            sp_contact.IMPP.Value = value;
            break;
            
    }
}

function __s60_enumerate_build_contact_object(object, namespace, func, param){
	//alert("In __s60_enumerate_build_contact_object");
    var key;
    for (key in object) {
        //if (object.hasOwnProperty('key')) {
        var propname;
        if (namespace) {
            propname = namespace + "." + key;
        }
        else {
            propname = key;
        }
        var value = object[key];
        //alert("propname"+propname);
        if (propname == "IMPP") {
            //	   //alert("val"+value[0]);
            func(propname, value, param);
        }
        if (typeof value == "object") {
            /*	if(value instanceof Array)
             {
             func(propname,value, param);
             }
             else
             {*/
            __s60_enumerate_build_contact_object(value, propname, func, param);
            //}
        }
        else {
            func(propname, value, param);
        }
    }
    //}
}

//Map from sp contact to device contact



function __sp_device_contact_extract(name, value, contact){
	
    if (name == "id") {
        contact.id = value;
        return;
    }
    
    // We only care about the Value fields
    if (!name.match(".Value")) {
        return;
    }
    //__device_debug("sp_device_contact_extract: " + name + ": " + value);
    
    try {
        if (name.match("IMPP.Value.0")) {
            contact.xspid = [];
        }
        if (name.match("Name")) {
            if (name.match("CompanyName")) {
                if (!contact.company) {
                    contact.company = {};
                }
            }
            else 
                if (!contact.name) {
                    contact.name = {};
                }
        }
        else 
            if (name.match("Phone") || name.match("Number") || name.match("VOIP") || name.match("Voip")) {
                if (!contact.tel) {
                    contact.tel = {};
                }
                if (name.match("Home")) {
                    if (!contact.tel.home) {
                        contact.tel.home = {};
                    }
                }
                else 
                    if (name.match("Work")) {
                        if (!contact.tel.work) {
                            contact.tel.work = {};
                        }
                    }
            }
            else 
                if (name.match("Addr") || name.match("Email") || name.match("URL")) {
                    if (!contact.address) {
                        contact.address = {};
                    }
                    if (name.match("Home")) {
                        if (!contact.address.home) {
                            contact.address.home = {};
                        }
                    }
                    else 
                        if (name.match("Work")) {
                            if (!contact.address.work) {
                                contact.address.work = {};
                            }
                        }
                }
                else 
                    if (name.match("JobTitle")) {
                        if (!contact.company) {
                            contact.company = {};
                        }
                    }
    } 
    catch (e) {
        __device_handle_exception(e, "__sp_device_contact_extract: " + e);
    }
    if (name.match("IMPP.Value")) {
        var splitstr = name.split(".");
        var index = splitstr[2];
        if (index != undefined) {
            contact.xspid[splitstr[2]] = value;
            //alert("after assigning" + contact.xspid[splitstr[2]]);
            return;
        }
    }
    switch (name) {
        case "LastName.Value":
            contact.name.last = value;
            break;
        case "FirstName.Value":
            contact.name.first = value;
            break;
        case "MiddleName.Value":
            contact.name.middle = value;
            break;
        case "Prefix.Value":
            contact.name.prefix = value;
            break;
        case "Suffix.Value":
            contact.name.suffix = value;
            break;
        case "LandPhoneGen.Value":
            contact.tel.land = value;
            break;
        case "MobilePhoneGen.Value":
            contact.tel.mobile = value;
            break;
        case "VideoNumberGen.Value":
            contact.tel.video = value;
            break;
        case "FaxNumberGen.Value":
            contact.tel.fax = value;
            break;
        case "VOIPGen.Value":
		//alert(" voip gen= "+value);
            contact.tel.voip = value;
            break;
        case "LandPhoneHome.Value":
            contact.tel.home.land = value;
            break;
        case "MobilePhoneHome.Value":
            contact.tel.home.mobile = value;
            break;
        case "VideoNumberHome.Value":
            contact.tel.home.video = value;
            break;
        case "FaxNumberHome.Value":
            contact.tel.home.fax = value;
            break;
        case "VoipHome.Value":
			//alert(" voip home Value = "+value);
            contact.tel.home.voip = value;
            break;
        case "LandPhoneWork.Value":
            contact.tel.work.land = value;
            break;
        case "MobilePhoneWork.Value":
            contact.tel.work.mobile = value;
            break;
        case "VideoNumberWork.Value":
            contact.tel.work.video = value;
            break;
        case "FaxNumberWork.Value":
            contact.tel.work.fax = value;
            break;
        case "VoipWork.Value":
		//alert(" voip work= "+value);
            contact.tel.work.voip = value;
            break;
        case "AddrStreetGen.Value":
            contact.address.street = value;
            break;
        case "AddrLocalGen.Value":
            contact.address.local = value;
            break;
        case "AddrRegionGen.Value":
            contact.address.region = value;
            break;
        case "AddrPostCodeGen.Value":
            contact.address.code = value;
            break;
        case "AddrCountryGen.Value":
            contact.address.country = value;
            break;
        case "EmailGen.Value":
            contact.address.email = value;
            break;
        case "URLGen.Value":
            contact.address.uri = value;
            break;
        case "AddrStreetHome.Value":
            contact.address.home.street = value;
            break;
        case "AddrLocalHome.Value":
            contact.address.home.local = value;
            break;
        case "AddrRegionHome.Value":
            contact.address.home.region = value;
            break;
        case "AddrPostCodeHome.Value":
            contact.address.home.code = value;
            break;
        case "AddrCountryHome.Value":
            contact.address.home.country = value;
            break;
        case "EmailHome.Value":
            contact.address.home.email = value;
            break;
        case "URLHome.Value":
            contact.address.home.uri = value;
            break;
        case "AddrStreetWork.Value":
            contact.address.work.street = value;
            break;
        case "AddrLocalWork.Value":
            contact.address.work.local = value;
            break;
        case "AddrRegionWork.Value":
            contact.address.work.region = value;
            break;
        case "AddrPostCodeWork.Value":
            contact.address.work.code = value;
            break;
        case "AddrCountryWork.Value":
            contact.address.work.country = value;
            break;
        case "EmailWork.Value":
            contact.address.work.email = value;
            break;
        case "URLWork.Value":
            contact.address.work.uri = value;
            break;
        case "CompanyName.Value":
            contact.company.name = value;
            break;
        case "JobTitle.Value":
            contact.company.title = value;
            break;
        case "Note.Value":
            contact.notes = value;
            break;
        case "Anniversary.Value":
            contact.anniversary = value;
            break;
        case "Date.Value":
            contact.birthday = value;
            break;
        case "SecondName.Value":
            //alert("nickname value"+value);
            contact.nickName = value;
            //alert("after assigning"+contact.nickName);
            break;
        case "CallerObjImg.Value":
            contact.photo = value;
            break;
            
        default:
        //__device_debug("Default: " + value );
    }
}

function __sp_device_contact_build(sp_contact, contact){
	//alert("In __sp_device_contact_build");
    __s60_enumerate_build_contact_object(sp_contact, null, __sp_device_contact_extract, contact);
	//alert("After __s60_enumerate_build_contact_object");
}

/* ------ Wrap sp iterator ------- */
function __sp_contact_iterator_get_next(){
    //__device_debug("__sp_contact_iterator_get_next"); 
	//alert("Before calling iter.getnext  "); 
    var sp_contact = this.iter.getNext();
	//alert("After calling iter.getnext  "); 
    if (typeof sp_contact == "undefined") {
		//alert("sp_contact == undefined  "); 
        return null;
    }	
    var rval = {};	
    __sp_device_contact_build(sp_contact, rval);	
    sp_contact.close();	
    return rval;
}

function __sp_contact_iterator(js_iterator){
    this.iter = js_iterator;
	//alert("before __sp_contact_iterator_get_next");
    this.next = __sp_contact_iterator_get_next;
	//alert("After __sp_contact_iterator_get_next ");
    this.close = function(){
        this.iter.close();
    };
}

function __s60_enumerate_group_object(object, func, param){
    var key;
    for (key in object) {
        //if (object.hasOwnProperty('key')) {
        var propname = key;
        var value = object[key];
        func(propname, value, param);
        //}
    }
}

function __sp_device_groupinfo_extract(name, value, groupinfo){

    if (groupinfo.group == undefined) {
        groupinfo.group = {};
    }
    if (name == "id") {
        groupinfo.group.groupId = value;
    }
    else 
        if (name == "GroupLabel") {
            groupinfo.group.groupName = value;
        }
        else 
            if (name == "Contents") {
                groupinfo.contents = value;
            }
    return;
}

function __sp_device_groupinfo_build(sp_group, groupinfo){
    __s60_enumerate_group_object(sp_group, __sp_device_groupinfo_extract, groupinfo);
}



//Build group data
function __sp_device_group_extract(name, value, group){
    if (name == "id") {
        group.groupId = value;
        return;
    }
    if (name == "GroupLabel") {
        group.groupName = value;
        return;
    }
}

function __sp_device_group_build(sp_group, group){
    __s60_enumerate_object(sp_group, null, __sp_device_group_extract, group);
}



//Iterate the group data
function __sp_group_iterator_get_next(){
    var sp_group = this.iter.getNext();
    if (typeof sp_group == "undefined") {
        return null;
    }
    var rval = {};
    __sp_device_group_build(sp_group, rval);
    sp_group.close();
    return rval;
}

function __sp_group_iterator(js_iterator){
    this.iter = js_iterator;
    this.next = __sp_group_iterator_get_next;
    this.close = function(){
        this.iter.close();
    };
}

/* --------- Public methods ---------- */


var CONTACTS_APP_ID = 0x101f4cce;

// Apps should take care that this is not reinvoked
// while the editor is already running. 

function __sp_contacts_startEditor(editor_cb, contact, ErrorCallback){
    if (!editor_cb) 
        throw new DeviceException(this.error.MISSING_ARG_ERR, "Contacts: StartEditor:Missing Success Callback");
    
    if ((typeof editor_cb) != "function") 
        throw new DeviceException(this.error.INVALID_ARG_ERR, "Contacts: StartEditor:Invalid Success Callback");
    
    if ((contact) == null) 
        contact = {};
    
    if ((typeof contact) == "undefined") 
        contact = {};
    
    if ((contact) == undefined) 
        contact = {};
    
    if ((typeof contact) != "object") {
        throw new DeviceException(this.error.INVALID_ARG_ERR, "Contacts: StartEditor:Invalid Contact Data");
    }
    
    
    if (ErrorCallback) 
        if ((typeof ErrorCallback) != "function") 
            throw new DeviceException(this.error.INVALID_ARG_ERR, "Contacts :StartEditor:Invalid Error Callback");
    
    var finished = function(arg1, arg2, arg3){
        var iter = null;
        editor_cb(iter);
        //editor_cb(arg1,arg2,arg3);
    };
    __s60_start_and_wait(CONTACTS_APP_ID, "", finished);
    return 0; //This value is returned as the transaction id is not supported
}

// TBD: add support for match patterns
function __sp_contacts_getContacts_cb(arg1, arg2, arg3){
	//alert(" __sp_contacts_getContacts_cb");
    var iter = null;
    var contacts_cb;
    var error_cb;
    var CbObj;
    
    //alert(" before getFromArray");
    CbObj = glob_obj.getFromArray(arg1);
	//alert("after getFromArray");
    
    
    if (CbObj) {
		//alert(" before CbObj.success_cb");
        contacts_cb = CbObj.success_cb;
		//alert(" After CbObj.success_cb");
        error_cb = CbObj.error_cb;
		//alert(" After CbObj.error_cb");
    }
    
    else {
        alert("Contacts: __sp_contacts_getContacts_cb : Callback not found ");
		return;
    }
    
    if (arg3.ReturnValue) {
        iter = new __sp_contact_iterator(arg3.ReturnValue);
    }
    else 
        if (arg3.ErrorCode != 0) {
            //alert(arg3.ErrorCode);
            var err_msg;
            if (arg3.ErrorMessage) 
                err_msg = splitErrorMessage(arg3.ErrorMessage);
            else 
                err_msg = "Operation Failed";
            
            error_cb(new DeviceException(MapErrorCode[arg3.ErrorCode], "Contacts: getContacts: " + err_msg));
            return;
        }
    contacts_cb(iter);
    glob_obj.removeFromArray(arg1);
}

function __sp_contacts_getContacts(contacts_cb, match, sortOrder, ErrorCallback){
    //alert("__sp_contacts_getContacts");
    var criteria = {};
    modifyObjectBaseProp(criteria);
    criteria.Type = 'Contact';
    if (match) {
        criteria.Filter = {};
        modifyObjectBaseProp(criteria.Filter);
        criteria.Filter.SearchVal = match;
        
    }
    
    //if (sortOrder) {
	if(sortOrder != null && sortOrder != undefined){		
        criteria.Sort = {};
        modifyObjectBaseProp(criteria.Sort);
        if (typeof sortOrder == "number") {
            if (sortOrder == this.SORT_ASCENDING) {
                criteria.Sort.Order = "Ascending";
            }
            else 
                if (sortOrder == this.SORT_DESCENDING) {
                    criteria.Sort.Order = "Descending";
                }
                
                
                else {   
						//alert(" In datanotfound");                
					 ErrorCallback(new DeviceException(this.error.DATA_OUT_OF_RANGE_ERR, "Contacts: getContacts: invalid sortOrder input"));
					 return;				
                }
        }
        else {			
            throw new DeviceException(this.error.INVALID_ARG_ERR, "Contacts: getContacts: invalid sortOrder input");
        }
    }
    
    try {
    
        if (!contacts_cb) {
			//alert(" ! contacts_cb");
            throw new DeviceException(this.error.MISSING_ARG_ERR, "Contacts: getContacts: callback is missing");
        }
        else 
            if (typeof contacts_cb != "function") {
                throw new DeviceException(this.error.INVALID_ARG_ERR, "Contacts: getContacts: callback is invalid");
            }
        if (ErrorCallback) {
            if (typeof(ErrorCallback) != 'function') {
                throw new DeviceException(this.error.INVALID_ARG_ERR, "Contacts: getContacts: ErrorCallback is invalid");
            }
        }
        
			temp_scb = contacts_cb;
			temp_ecb = ErrorCallback;
        var rval = this.so.IDataSource.GetList(criteria, this.getContactsCb);
        //alert(" errorcode = "+rval.ErrorCode);
        if (rval.TransactionID) {
			//alert(" if TransactionID ");
            glob_obj.addToGlobalArray(rval.TransactionID, contacts_cb, ErrorCallback);
        }
        //alert("error code = "+rval.ErrorCode);	
        if (criteria.Sort) {
            delete criteria.Sort.Order;
        }
        if (criteria.Filter) {
            delete criteria.Filter.SearchVal;
        }
        if (criteria) {
            delete criteria.Type;
            delete criteria.Filter;
            delete criteria.Sort;
        }
        if (rval.ErrorCode != 0) {			
            var doMap = mappingVerification(rval.ErrorCode);
            var err_msg = null;
            if (rval.ErrorMessage) {
                err_msg = splitErrorMessage(rval.ErrorMessage);
            }
            if (doMap) {
                switch (MapErrorCode[rval.ErrorCode]) {
                    case this.error.MISSING_ARG_ERR:
                    case this.error.INVALID_ARG_ERR:
                    case this.error.NOT_SUPPORTED_ERR:  {						
						if (err_msg) {
							throw new DeviceException(MapErrorCode[rval.ErrorCode], "Contacts: getContacts: " + err_msg);
						}
						else {
							throw new DeviceException(MapErrorCode[rval.ErrorCode], "Contacts: getContacts:Operation Failed");
						}
					}
                        break;
                    default:
                        //contacts_cb(0, MapErrorCode[rval.ErrorCode],0);
                        //contacts_cb(iter);
                        if (ErrorCallback != undefined) {
                            if (err_msg) {
                                ErrorCallback(new DeviceException(MapErrorCode[rval.ErrorCode], "Contacts: getContacts: " + err_msg));
                            }
                            else 
                                ErrorCallback(new DeviceException(MapErrorCode[rval.ErrorCode], "Contacts: getContacts:Operation Failed "));
                        }
                        else {
                            if (err_msg) 
                                throw new DeviceException(MapErrorCode[rval.ErrorCode], "Contacts: getContacts: " + err_msg);
                            else 
                                throw new DeviceException(MapErrorCode[rval.ErrorCode], "Contacts: getContacts:Operation Failed");
                        }
                }
            }
            else {
                if (ErrorCallback != undefined) {
                    if (err_msg) {
                        ErrorCallback(new DeviceException(rval.ErrorCode, "Contacts: getContacts: " + err_msg));
                    }
                    else 
                        ErrorCallback(new DeviceException(rval.ErrorCode, "getContacts:Operation Failed "));
                }
                else {
                    if (err_msg) 
                        throw new DeviceException(rval.ErrorCode, "Contacts: getContacts: " + err_msg);
                    else 
                        throw new DeviceException(rval.ErrorCode, "Contacts: getContacts:Operation Failed");
                }
            }
        }
        return rval.TransactionID;
    } 
    catch (e) {
        __device_handle_exception(e, "__sp_contacts_getContacts: " + e);
    }
}

function __sp_contacts_add(contact){
	
	if((contact) == null)
			throw new DeviceException(this.error.MISSING_ARG_ERR, 'addContact:Contact Data Needed');
			
	if((typeof contact) == "undefined")
		throw new DeviceException(this.error.MISSING_ARG_ERR, 'addContact:Contact Data Needed');
		
	if((contact) == undefined)
		throw new DeviceException(this.error.MISSING_ARG_ERR, 'addContact:Contact Data Needed');
		
	if ((typeof contact) != "object") {
		throw new DeviceException(this.error.INVALID_ARG_ERR, 'addContact:Invalid Contact Data');
	}
			
    var sp_data = {};
    modifyObjectBaseProp(sp_data);
    __s60_enumerate_contact_object(contact, null, __sp_contact_extract, sp_data);
    var criteria = {};
    modifyObjectBaseProp(criteria);
    criteria.Type = "Contact";
    criteria.Data = sp_data;
    try {
        if (sp_data.id) {
            throw new DeviceException(this.error.NOT_SUPPORTED_ERR, "Contacts: addContact: Id Not Supported");
        }
        var result = this.so.IDataSource.Add(criteria);
        //alert("res.errorcode = "+result.ErrorCode);
        if (sp_data) {
            delete sp_data.id;
        }
        if (criteria) {
            delete criteria.Type;
            delete criteria.Data;
        }
        var cntId = result["ReturnValue"];
        if (result.ErrorCode != 0) {
            var doMap = mappingVerification(result.ErrorCode);
            if (result.ErrorMessage) {
                var err_msg = splitErrorMessage(result.ErrorMessage);
                if (doMap) {
					//alert("In do map");
                    throw new DeviceException(MapErrorCode[result.ErrorCode], "Contacts: addContact: " + err_msg);
                }
                else {
					//alert("In do map else");
                    throw new DeviceException(result.ErrorCode, "Contacts: addContact: " + err_msg);
                }
            }
            else {
                if (doMap) {
                
                    throw new DeviceException(MapErrorCode[result.ErrorCode], "Contacts: addContact: Operation Failed");
                }
                else {
                    throw new DeviceException(result.ErrorCode, "Contacts: addContact: Operation Failed");
                }
            }
        }
        
        
        //Note: sp addContact no longer supports returning the new contact id
        //__device_debug("sp_contacts_add returns: " + result);
        //return result;
        return cntId;
    } 
    catch (e) {
        __device_handle_exception(e, "__sp_contacts_addContact: " + e);
    }
}

function __sp_contacts_update(contact){

    //alert("In  __sp_contacts_update");
    try {
        if (!(contact && contact.id)) {
			//alert(" contact && contact.id ");
            throw new DeviceException(this.error.MISSING_ARG_ERR, "Contacts: updateContact: contact is missing");
        }
        var sp_data = {};
        modifyObjectBaseProp(sp_data);
        __s60_enumerate_contact_object(contact, null, __sp_contact_extract, sp_data);
	if (sp_data.id == undefined) {
			//alert("sp_data.id == undefined");
            throw new DeviceException(this.error.INVALID_ARG_ERR, "Contacts: updateContact: Invalid id type");
            
        }
        
        if (typeof sp_data.id != "string") {
			//alert("typeof sp_data.id != string")
            throw new DeviceException(this.error.INVALID_ARG_ERR, "Contacts: updateContact: Invalid id type");
            
        }
        var criteria = {};
        modifyObjectBaseProp(criteria);
        criteria.Type = "Contact";
        criteria.Data = sp_data;
        var result = this.so.IDataSource.Add(criteria);
        //alert("result = "+ result.ErrorCode);
        if (sp_data) {
            delete sp_data.id;
        }
        if (criteria) {
            delete criteria.Type;
            delete criteria.Data;
        }
        if (result.ErrorCode != 0) {
            var doMap = mappingVerification(result.ErrorCode);
            if (result.ErrorMessage) {
                var err_msg = splitErrorMessage(result.ErrorMessage);
                if (doMap) {
                    throw new DeviceException(MapErrorCode[result.ErrorCode], "Contacts: updateContact: " + err_msg);
                }
                else {
                    throw new DeviceException(result.ErrorCode, "Contacts: updateContact: " + err_msg);
                }
            }
            else {
                if (doMap) {
                    throw new DeviceException(MapErrorCode[result.ErrorCode], "Contacts: updateContact: Operation Failed");
                }
                else {
                    throw new DeviceException(result.ErrorCode, "Contacts: updateContact: Operation Failed");
                }
            }
        }
    } 
    catch (e) {
        __device_handle_exception(e, "__sp_contacts_updateContact: " + e);
    }
    
}

function __sp_contacts_delete(id){
    __device_debug("sp_contacts_delete id: " + id);
    var contactdata = {};
    modifyObjectBaseProp(contactdata);
    if (id == undefined) {
        throw new DeviceException(this.error.MISSING_ARG_ERR, "Contacts: deleteContacts: idlist is missing");
    }
    
    if (typeof id == "object") {
        contactdata.IdList = id;
    }
    else {
        contactdata.IdList = [];
        contactdata.IdList[0] = id;
        //delete contactdata.IdList;
    }
    var criteria = {};
    modifyObjectBaseProp(criteria);
    
    criteria.Type = "Contact";
    criteria.Data = contactdata;
    
    try {
        var result = this.so.IDataSource.Delete(criteria);
       // alert(" result.errorcode = "+result.ErrorCode);
        if (contactdata) {
            delete contactdata.IdList;
        }
        if (criteria) {
            delete criteria.Type;
            delete criteria.Data;
        }
        
        if (result.ErrorCode != 0) {
            var doMap = mappingVerification(result.ErrorCode);
            if (result.ErrorMessage) {
                var err_msg = splitErrorMessage(result.ErrorMessage);
                if (doMap) {
                    throw new DeviceException(MapErrorCode[result.ErrorCode], "Contacts: deleteContacts: " + err_msg);
                }
                else {
                    throw new DeviceException(result.ErrorCode, "Contacts: deleteContacts: " + err_msg);
                }
            }
            else {
                if (doMap) {
                    throw new DeviceException(MapErrorCode[result.ErrorCode], "Contacts: deleteContacts: Operation Failed");
                }
                else {
                    throw new DeviceException(result.ErrorCode, "Contacts: deleteContacts: Operation Failed");
                }
            }
        }
    } 
    catch (e) {
        __device_handle_exception(e, "__sp_contacts_deleteContacts: " + e);
    }
}

function __sp_contacts_get(id){
    //alert("__sp_contacts_get"+typeof id);
    var criteria = {};
    modifyObjectBaseProp(criteria);
    criteria.Type = 'Contact';
    
    if (id == null) {
        throw new DeviceException(this.error.MISSING_ARG_ERR, "Contacts: getContactInfo: id should not be null");
    }
    if ( typeof id != "string") {
		throw new DeviceException(this.error.INVALID_ARG_ERR, 'Contacts: getContactInfo: id should be string');
	}
    criteria.Filter = {};
    modifyObjectBaseProp(criteria.Filter);
    criteria.Filter.id = id;
    
    try {
        var rval = this.so.IDataSource.GetList(criteria);
        //alert("rval .errorcode = "+rval.ErrorCode);
        
        if (criteria.Filter) {
            delete criteria.Filter.id;
        }
        if (criteria) {
            delete criteria.Type;
            delete criteria.Filter;
        }
        if (rval) {
            if (rval.ErrorCode != 0) {
                var doMap = mappingVerification(rval.ErrorCode);
                if (rval.ErrorMessage) {
                    var err_msg = splitErrorMessage(rval.ErrorMessage);
                    if (doMap) {
                        throw new DeviceException(MapErrorCode[rval.ErrorCode], "Contacts: getContactInfo: " + err_msg);
                    }
                    else {
                        throw new DeviceException(rval.ErrorCode, "Contacts: getContactInfo: " + err_msg);
                    }
                }
                else {
                    if (doMap) {
                        throw new DeviceException(MapErrorCode[rval.ErrorCode], "Contacts: getContactInfo: Operation Failed");
                    }
                    else {
                        throw new DeviceException(rval.ErrorCode, "Contacts: getContactInfo: Operation Failed");
                    }
                }
            }
            var contact = {};
            modifyObjectBaseProp(contact);
            var sp_contact = rval.ReturnValue.getNext();
            __sp_device_contact_build(sp_contact, contact);
            return contact;
        }
        
    } 
    catch (e) {
        __device_handle_exception(e, "__sp_contacts_getContactInfo:" + e);
    }
}

function __sp_contacts_addGroup(groupName){
    //alert(" In __sp_contacts_addGroup");
    var sp_data = {};
    modifyObjectBaseProp(sp_data);
    sp_data.GroupLabel = groupName;
    
    if (typeof(sp_data.GroupLabel) == null) {
        throw new DeviceException(this.error.MISSING_ARG_ERR, "Contacts: addGroups: callback is missing");
    }
    
    
    if ((typeof sp_data.GroupLabel) == "undefined") {
        throw new DeviceException(this.error.MISSING_ARG_ERR, 'addGroup:Group Data Needed');
    }
    
    if ((sp_data.GroupLabel) == undefined) {
        throw new DeviceException(this.error.MISSING_ARG_ERR, 'addGroup:Group Data Needed');
    }
    
    var criteria = {};
    modifyObjectBaseProp(criteria);
    criteria.Type = "Group";
    criteria.Data = sp_data;
    try {
        var result = this.so.IDataSource.Add(criteria);
        //alert(" In __sp_contacts_addGroup result = "+result.ErrorCode);
        if (sp_data) {
            delete sp_data.GroupLabel;
        }
        if (criteria) {
            delete criteria.Type;
            delete criteria.Data;
        }
        var grpId = result["ReturnValue"];
        if (result.ErrorCode != 0) {
            var doMap = mappingVerification(result.ErrorCode);
            if (result.ErrorMessage) {
                var err_msg = splitErrorMessage(result.ErrorMessage);
                if (doMap) {
                    throw new DeviceException(MapErrorCode[result.ErrorCode], "Contacts: addGroup: " + err_msg);
                }
                else {
                    throw new DeviceException(err_msg, result.ErrorCode, "Contacts: addGroup: Operation Failed ");
                }
            }
            else {
                if (doMap) {
                    throw new DeviceException(MapErrorCode[result.ErrorCode], "Contacts: addGroup: Operation Failed");
                }
                else {
                    throw new DeviceException(result.ErrorCode, "Contacts: addGroup: Operation Failed");
                }
            }
        }
        return grpId;
    } 
    catch (e) {
        __device_handle_exception(e, "__sp_contacts_addGroup: " + e);
    }
}

function __sp_contacts_getGroups_cb(arg1, arg2, arg3){
    var iter = null;
    var groups_cb;
    var error_cb;
    var CbObj;
    
    
    CbObj = glob_obj.getFromArray(arg1);
    
    if (CbObj) {
        groups_cb = CbObj.success_cb;
        error_cb = CbObj.error_cb;
    }
    
    else {
        //alert("Contacts : __sp_contacts_getGroups_cb : Callback not found ");
		return;
    }
    
    iter = arg3.ReturnValue;
    if (arg3.ReturnValue) {
        iter = new __sp_group_iterator(arg3.ReturnValue);
    }
    else 
        if (arg3.ErrorCode != 0) {
            var err_msg;
            if (arg3.ErrorMessage) 
                err_msg = splitErrorMessage(arg3.ErrorMessage);
            else 
                err_msg = "Operation Failed";
            
            error_cb(new DeviceException(err_msg, MapErrorCode[arg3.ErrorCode], "Contacts: getGroups:"));
            return;
        }
    
    groups_cb(iter);
    glob_obj.removeFromArray(arg1);
}

function __sp_contacts_getGroups(groups_cb, ErrorCallback){
    //alert("In __sp_contacts_getGroups");
    var criteria = {};
    modifyObjectBaseProp(criteria);
    criteria.Type = 'Group';
    
    try {
        if (!groups_cb) {
            throw new DeviceException(this.error.MISSING_ARG_ERR, "Contacts: getGroups: callback is missing");
        }
        else 
            if (typeof groups_cb != "function") {
                throw new DeviceException(this.error.INVALID_ARG_ERR, "Contacts: getGroups: callback is invalid");
            }
        if (ErrorCallback) {
            if (typeof(ErrorCallback) != 'function') {
                throw new DeviceException(this.error.INVALID_ARG_ERR, "Contacts: getGroups: ErrorCallback is invalid");
            }
        }
        
        temp_scb = groups_cb;
		temp_ecb = ErrorCallback;
        var rval = this.so.IDataSource.GetList(criteria, this.getGroupsCb);
       // alert(" errorcode = "+rval.ErrorCode);
        if (rval.TransactionID) {
            glob_obj.addToGlobalArray(rval.TransactionID, groups_cb, ErrorCallback);
        }
        //alert("In __sp_contacts_getGroups result = "+rval.ErrorCode);
        if (criteria) {
            delete criteria.Type;
        }
        if (rval.ErrorCode != 0) {
           // var doMap = mappingVerification(result.ErrorCode);
		   var doMap = mappingVerification(rval.ErrorCode);
            var err_msg = null;
            if (rval.ErrorMessage) {
                err_msg = splitErrorMessage(rval.ErrorMessage);
            }
            if (doMap) {
                switch (MapErrorCode[rval.ErrorCode]) {
                    case this.error.MISSING_ARG_ERR:
                    case this.error.INVALID_ARG_ERR:
                    case this.error.NOT_SUPPORTED_ERR:
                        if (err_msg) {
                            throw new DeviceException(MapErrorCode[rval.ErrorCode], "Contacts: getGroups: " + err_msg);
                        }
                        else {
                            throw new DeviceException(MapErrorCode[rval.ErrorCode], "Contacts: getGroups: Operation Failed");
                        }
                        break;
                    default:
                        //groups_cb(0,MapErrorCode[rval.ErrorCode] ,0) ;
                        //groups_cb(iter) ;
                        if (ErrorCallback != undefined) {
                            if (err_msg) {
                                ErrorCallback(new DeviceException(MapErrorCode[rval.ErrorCode], "Contacts: getGroups: " + err_msg));
                            }
                            else 
                                ErrorCallback(new DeviceException(MapErrorCode[rval.ErrorCode], "Contacts:  getGroups: Operation Failed "));
                        }
                        else {
                            if (err_msg) 
                                throw new DeviceException(MapErrorCode[rval.ErrorCode], "Contacts: getGroups: Operation Failed" + err_msg);
                            else 
                                throw new DeviceException(MapErrorCode[rval.ErrorCode], "Contacts: getGroups: Operation Failed");
                        }
                        
                }
            }
            else {
                //groups_cb(0,rval.ErrorCode ,0) ;
                //groups_cb(iter) ;
                if (ErrorCallback != undefined) {
                    if (err_msg) {
                        ErrorCallback(new DeviceException(rval.ErrorCode, "Contacts: getGroups: " + err_msg));
                    }
                    else 
                        ErrorCallback(new DeviceException(rval.ErrorCode, "Contacts: getGroups: Operation Failed"));
                }
                else {
                    if (err_msg) 
                        throw new DeviceException(rval.ErrorCode, "Contacts: getGroups: Operation Failed" + err_msg);
                    else 
                        throw new DeviceException(rval.ErrorCode, "Contacts: getGroups: Operation Failed");
                }
            }
        }
        
        return rval.TransactionID;
    } 
    catch (e) {
        __device_handle_exception(e, "__sp_contacts_getGroups: " + e);
    }
}

function __sp_contacts_deleteGroups(id){
    //alert("In __sp_contacts_deleteGroups");
    var contactdata = {};
    modifyObjectBaseProp(contactdata);
    var IdList = [];
    if (typeof id == "object") {
        var i = 0;
        for (var val in id) {
            //	if (id.hasOwnProperty('val')) {
            IdList[i] = id[val];
            i++;
            //}		
        }
    }
    else {
        IdList[0] = id;
    }
    contactdata.IdList = [];
    contactdata.IdList = IdList;
    var criteria = {};
    modifyObjectBaseProp(criteria);
    criteria.Type = "Group";
    criteria.Data = contactdata;
    
    try {
        var result = this.so.IDataSource.Delete(criteria);
        //alert("In __sp_contacts_deleteGroups result = "+result.ErrorCode);
        /*if (contactdata) {
         delete contactdata.IdList;
         }
         if (criteria) {
         delete criteria.Type;
         delete criteria.Data;
         }*/
        if (result.ErrorCode != 0) {
            var doMap = mappingVerification(result.ErrorCode);
            if (result.ErrorMessage) {
                var err_msg = splitErrorMessage(result.ErrorMessage);
                if (doMap) {
                    throw new DeviceException(MapErrorCode[result.ErrorCode], "Contacts: deleteGroups: " + err_msg);
                }
                else {
                    throw new DeviceException(result.ErrorCode, "Contacts: deleteGroups: " + err_msg);
                }
            }
            else {
                if (doMap) {
                    throw new DeviceException(MapErrorCode[result.ErrorCode], "Contacts: deleteGroups: Operation Failed");
                }
                else {
                    throw new DeviceException(result.ErrorCode, "Contacts: deleteGroups: Operation Failed");
                }
            }
        }
    } 
    catch (e) {
        __device_handle_exception(e, "__sp_contacts_deleteGroups: " + e);
    }
}

function __sp_contacts_addContactsToGroup(groupId, id1){
    //alert("__sp_contacts_addContactsToGroup");
    try {
        var criteria = {};
        modifyObjectBaseProp(criteria);
        var mapFound = false;
        criteria.Type = "Group";
        var map = {};
        modifyObjectBaseProp(map);
        //	if (id1 != undefined) {			
        var IdList = [];
        if (typeof id1 == "object") {
            var i = 0;
            for (var val in id1) {
                //if (id1.hasOwnProperty('val')) {						
                IdList[i] = id1[val];
                i++;
                //	}					
            }
        }
        else {
            IdList[0] = id1;
        }
        map.IdList = IdList;
        mapFound = true;
        delete IdList.index;
        //	} 
        if (groupId != undefined) {
            map.id = groupId;
            mapFound = true;
        }
        if (mapFound) {
            criteria.Data = map;
        }
        
        criteria.OperationType = "Associate";
        var result = this.so.IDataSource.Organise(criteria);
       // alert("__sp_contacts_addContactsToGroup result.errorCode = "+result.ErrorCode);
        if (map) {
            delete map.id;
            delete map.IdList;
        }
        if (criteria) {
            delete criteria.Data;
            delete criteria.OperationType;
            delete criteria.Type;
        }
        if (result.ErrorCode != 0) {
            var doMap = mappingVerification(result.ErrorCode);
            if (result.ErrorMessage) {
                var err_msg = splitErrorMessage(result.ErrorMessage);
                if (doMap) {
                    throw new DeviceException(MapErrorCode[result.ErrorCode], "Contacts: addContactsToGroup: " + err_msg);
                }
                else {
                    throw new DeviceException(result.ErrorCode, "Contacts: addContactsToGroup: " + err_msg);
                }
            }
            else {
                if (doMap) {
                    throw new DeviceException(MapErrorCode[result.ErrorCode], "Contacts: addContactsToGroup: Operation Failed");
                }
                else {
                    throw new DeviceException(result.ErrorCode, "Contacts: addContactsToGroup: Operation Failed");
                }
            }
        }
    } 
    catch (e) {
        __device_handle_exception(e, "__sp_contacts_addContactsToGroup: " + e);
    }
}

function __sp_contacts_getContactIds_cb(arg1, arg2, arg3){
    var item = null;
    var idList = null;
    var contacts_cb;
    var error_cb;
    var CbObj;
    
    
    CbObj = glob_obj.getFromArray(arg1);
    
    
    if (CbObj) {
        contacts_cb = CbObj.success_cb;
        error_cb = CbObj.error_cb;
    }
    
    else {
        alert("Contacts: __sp_contacts_getContactIds_cb : Callback not found ");
		return;
    }
    
    var id = null;
    if (arg3["ReturnValue"] != undefined) {
        item = arg3["ReturnValue"];
        id = item["IdList"];
        idList = [];
        idList = id;
        
        delete idList.index;
    }
    else 
        if (arg3.ErrorCode != 0) {
            var err_msg;
            if (arg3.ErrorMessage) 
                err_msg = splitErrorMessage(arg3.ErrorMessage);
            else 
                err_msg = "Operation Failed";
            
            error_cb(new DeviceException(MapErrorCode[arg3.ErrorCode], "Contacts: getContactIds:" + err_msg));
            return;
        }
    //var error = arg3.ErrorCode;
    contacts_cb(idList);
    glob_obj.removeFromArray(arg1);
}

function __sp_contacts_getContactIds(contacts_cb, match, sortOrder, ErrorCallback){
    //alert("__sp_contacts_getContactIds sortOrder =  " +sortOrder);	
    var criteria = {};
   // var errcb = ErrorCallback;
    modifyObjectBaseProp(criteria);
    criteria.Type = 'Contact';
    
    if (match) {
        criteria.Filter = {};
        modifyObjectBaseProp(criteria.Filter);
        criteria.Filter.SearchVal = match;
    }
    
//    if (sortOrder) {
  if(sortOrder != null && sortOrder != undefined){
        criteria.Sort = {};
        modifyObjectBaseProp(criteria.Sort);
        if (typeof sortOrder == "number") {
            if (sortOrder == this.SORT_ASCENDING) {
                criteria.Sort.Order = "Ascending";
            }
            else 
                if (sortOrder == this.SORT_DESCENDING) {
                    criteria.Sort.Order = "Descending";
                }
                else {
                   // criteria.Sort.Order = sortOrder; // sapi is taking care of this
				    ErrorCallback(new DeviceException(this.error.DATA_OUT_OF_RANGE_ERR, "Contacts: getContacts: invalid sortOrder input"));
					return;
                }
        }
        else {
            throw new DeviceException(this.error.INVALID_ARG_ERR, "Contacts: getContactIds: SortOrder is Invalid");
        }
        
    }
    
    try {
        if (!contacts_cb) {
            throw new DeviceException(this.error.MISSING_ARG_ERR, "Contacts: getContactIds: callback is missing");
        }
        
        else 
            if (typeof contacts_cb != "function") {
                throw new DeviceException(this.error.INVALID_ARG_ERR, "Contacts: getContactIds: callback is invalid");
            }
        if (ErrorCallback) {
            if (typeof(ErrorCallback) != 'function') {
                throw new DeviceException(this.error.INVALID_ARG_ERR, "Contacts: getContactIds: ErrorCallback is invalid");
            }
        }
        
        temp_scb = contacts_cb;
		temp_ecb = ErrorCallback;
        
        var rval = this.so.IDataSource.GetIds(criteria, this.getContactIdsCb);
        if (rval.TransactionID) {
            glob_obj.addToGlobalArray(rval.TransactionID, contacts_cb, ErrorCallback);
        }
        //alert(" rval.errorcode = "+rval.ErrorCode);
        /*if(criteria.Sort){
         delete criteria.Sort.Order;
         }
         if(criteria.Filter){
         delete criteria.Filter.SearchVal;
         }
         if (criteria) {
         delete criteria.Filter;
         delete criteria.Sort;
         delete criteria.Type;
         }*/
        if (rval.ErrorCode != 0) {
            var doMap = mappingVerification(rval.ErrorCode);
            var err_msg = null;
            if (rval.ErrorMessage) {
                var err_msg = splitErrorMessage(rval.ErrorMessage);
            }
            if (doMap) {
                switch (MapErrorCode[rval.ErrorCode]) {
                    case this.error.MISSING_ARG_ERR:
                    case this.error.INVALID_ARG_ERR:
                    case this.error.NOT_SUPPORTED_ERR:
                        if (err_msg) {
                            throw new DeviceException(MapErrorCode[rval.ErrorCode], "Contacts: getContactIds: " + err_msg);
                        }
                        else {
                            throw new DeviceException(MapErrorCode[rval.ErrorCode], "Contacts: getContactIds: Operation Failed");
                        }
                        break;
                    default:
                        //contacts_cb(0,MapErrorCode[rval.ErrorCode] ,0) ;
                        //contacts_cb(idList);
                        if (ErrorCallback != undefined) {
                            if (err_msg) {
                                ErrorCallback(new DeviceException(MapErrorCode[rval.ErrorCode], "Contacts: getContactIds: " + err_msg));
                            }
                            else 
                                ErrorCallback(new DeviceException(MapErrorCode[rval.ErrorCode], "Contacts: getContactIds: Operation Failed "));
                        }
                        else {
                            if (err_msg) {
                                throw new DeviceException(MapErrorCode[rval.ErrorCode], "Contacts: getContactIds:" + err_msg);
                            }
                            else 
                                throw new DeviceException(MapErrorCode[rval.ErrorCode], "Contacts: getContactIds: Operation Failed");
                        }
                }
            }
            else {
                //contacts_cb(0,rval.ErrorCode ,0) ;
                //contacts_cb(idList);
                if (ErrorCallback != undefined) {
                    if (err_msg) {
                        ErrorCallback(new DeviceException(rval.ErrorCode, "Contacts: getContactIds: " + err_msg));
                    }
                    else 
                        ErrorCallback(new DeviceException(rval.ErrorCode, "Contacts: getContactIds: Operation Failed "));
                }
                else {
                    if (err_msg) {
                        throw new DeviceException(rval.ErrorCode, "Contacts: getContactIds:" + err_msg);
                    }
                    else 
                        throw new DeviceException(rval.ErrorCode, "Contacts: getContactIds: Operation Failed");
                }
            }
        }
        return rval.TransactionID;
    } 
    catch (e) {
        __device_handle_exception(e, "__sp_contacts_getContactIds: " + e);
    }
    
}

function __sp_contacts_getGroupIds_cb(arg1, arg2, arg3){
	//alert("In __sp_contacts_getGroupIds_cb");
    var error_cb = null;
    var item = null;
    var idList = [];
    
    var contacts_cb;
    var error_cb;
    var CbObj;
    
    //alert("Before getfromarray ");
    CbObj = glob_obj.getFromArray(arg1);
	//alert("After getfromarray ");
    
    if (CbObj) {
        contacts_cb = CbObj.success_cb;
        error_cb = CbObj.error_cb;
    }
    
    else {
        //alert("Contacts: __sp_contacts_getGroupIds_cb : Callback not found ");
		return;
    }
    
    
    if (arg3.ReturnValue) {
        item = arg3["ReturnValue"];
        arg3.ReturnValue.close();
        var id = item["IdList"];
        idList = id;
    }
    else 
        if (arg3.ErrorCode != 0) {
            var err_msg;
            if (rval.ErrorMessage) 
                err_msg = splitErrorMessage(rval.ErrorMessage);
            else 
                err_msg = "Operation Failed";
            
            error_cb(new DeviceException(MapErrorCode[arg3.ErrorCode], "Contacts: getGroupIds:" + err_msg));
            return;
        }
    //var error = arg3.ErrorCode;	
    contacts_cb(idList);
    delete idList.index;
    glob_obj.removeFromArray(arg1);
}

function __sp_contacts_getGroupIds(contacts_cb, ErrorCallback){	
    var criteria = {};
    modifyObjectBaseProp(criteria);
    criteria.Type = 'Group';
    
    
    try {
        if (!contacts_cb) {
            throw new DeviceException(this.error.MISSING_ARG_ERR, "Contacts: getGroupIds: callback is missing");
        }
        else 
            if (typeof contacts_cb != "function") {
                throw new DeviceException(this.error.INVALID_ARG_ERR, "Contacts: getGroupIds: callback is invalid");
            }
        if (ErrorCallback) {
            if (typeof(ErrorCallback) != 'function') {
                throw new DeviceException(this.error.INVALID_ARG_ERR, "Contacts: getGroupIds: ErrorCallback is invalid");
            }
        }
        
        temp_scb = contacts_cb;
		temp_ecb = ErrorCallback;
        
        var rval = this.so.IDataSource.GetIds(criteria, this.getGroupIdsCb);
		//alert(" rval = "+rval.ErrorCode);
        if (rval.TransactionID) {
			//alert("if TransactionID");
            glob_obj.addToGlobalArray(rval.TransactionID, contacts_cb, ErrorCallback);
        }
        
        if (criteria) {
            delete criteria.Type;
        }
        if (rval.ErrorCode != 0) {
        
            var doMap = mappingVerification(rval.ErrorCode);
            var err_msg = null;
            if (rval.ErrorMessage) {
                var err_msg = splitErrorMessage(rval.ErrorMessage);
            }
            if (doMap) {
                switch (rval.ErrorCode) {
                    case this.error.MISSING_ARG_ERR:
                    case this.error.INVALID_ARG_ERR:
                    case this.error.NOT_SUPPORTED_ERR:
                        if (err_msg) {
                            throw new DeviceException(MapErrorCode[rval.ErrorCode], "Contacts: getGroupIds: " + err_msg);
                        }
                        else {
                            throw new DeviceException(MapErrorCode[rval.ErrorCode], "Contacts: getGroupIds: Operation Failed");
                        }
                        break;
                    default:
                        if (ErrorCallback != undefined) {
                            if (err_msg) {
                                ErrorCallback(new DeviceException(MapErrorCode[rval.ErrorCode], "Contacts: getGroupIds: " + err_msg));
                            }
                            else 
                                ErrorCallback(new DeviceException(MapErrorCode[rval.ErrorCode], "Contacts: getGroupIds: Operation Failed"));
                        }
                        else {
                            if (err_msg) {
                                throw new DeviceException(MapErrorCode[rval.ErrorCode], "Contacts: Contacts: getGroupIds:" + err_msg);
                            }
                            else 
                                throw new DeviceException(MapErrorCode[rval.ErrorCode], "Contacts: getGroupIds: Operation Failed");
                        }
                }
            }
            
            
            else {
                if (ErrorCallback != undefined) {
                    if (err_msg) {
                        ErrorCallback(new DeviceException(rval.ErrorCode, "Contacts: getGroupIds: " + err_msg));
                    }
                    else 
                        ErrorCallback(new DeviceException(rval.ErrorCode, "Contacts: getGroupIds: Operation Failed"));
                }
                else {
                    if (err_msg) {
                        throw new DeviceException(rval.ErrorCode, "Contacts: Contacts: getGroupIds:" + err_msg);
                    }
                    else 
                        throw new DeviceException(rval.ErrorCode, "Contacts: getGroupIds: Operation Failed");
                }
            }
        }
		//alert(" TransactionID = "+TransactionID);
        return rval.TransactionID;
    } 
    catch (e) {
        __device_handle_exception(e, "__sp_contacts_getGroupIds: " + e);
    }
    
}

function __sp_contacts_removeContactsFromGroup(groupId, id){
    //alert("__sp_contacts_removeContactsFromGroup");
    try {
        var criteria = {};
        modifyObjectBaseProp(criteria);
        var mapFound = false;
        criteria.Type = "Group";
        var map = {};
        if (id != undefined) {
            //alert("id != undefined");	
            var IdList = [];
            if (typeof id == "object") {
                var i = 0;
                for (var val in id) {
                    //	if (id.hasOwnProperty('val')) {
                    IdList[i] = id[val];
                    i++;
                    //	}
                }
            }
            else {
                //alert("id != undefined");
                IdList[0] = id;
            }
            map.IdList = IdList;
            mapFound = true;
            //delete IdList.index;
        }
        if (groupId != undefined) {
            map.id = groupId;
            mapFound = true;
        }
        if (mapFound) {
            criteria.Data = map;
        }
        
        criteria.OperationType = "Disassociate";
        var result = this.so.IDataSource.Organise(criteria);
        //alert("__sp_contacts_removeContactsFromGroup result"+result.ErrorCode);
        if (map) {
            delete map.IdList;
        }
        if (criteria) {
            delete criteria.Data;
            delete criteria.OperationType;
            delete criteria.Type;
        }
        if (result.ErrorCode != 0) {
            var doMap = mappingVerification(result.ErrorCode);
            if (result.ErrorMessage) {
                var err_msg = splitErrorMessage(result.ErrorMessage);
                if (doMap) {
                    throw new DeviceException(MapErrorCode[result.ErrorCode], "Contacts: removeContactsFromGroup: " + err_msg);
                }
                else {
                    throw new DeviceException(result.ErrorCode, "Contacts: removeContactsFromGroup: " + err_msg);
                }
            }
            else {
                if (doMap) {
                    throw new DeviceException(MapErrorCode[result.ErrorCode], "Contacts: removeContactsFromGroup: Operation Failed");
                }
                else {
                    throw new DeviceException(result.ErrorCode, "Contacts: removeContactsFromGroup: Operation Failed");
                }
            }
        }
    } 
    catch (e) {
        __device_handle_exception(e, "__sp_contacts_removeContactsFromGroup: " + e);
    }
}

function __sp_contacts_cancel(transactionId){
    //alert("__sp_contacts_cancel");
    try {
        var criteria = {};
        
        if ((transactionId) == null) 
            throw new DeviceException(this.error.MISSING_ARG_ERR, "Contacts: cancel: transactionId is missing " );
        
        if ((transactionId) == undefined) 
            throw new DeviceException(this.error.MISSING_ARG_ERR, "Contacts: cancel:transactionId is undefined ");
        
        if ((typeof transactionId) == "undefined") 
            throw new DeviceException(this.error.MISSING_ARG_ERR, "Contacts: cancel: transactionId is undefined ");
        
        if (((typeof transactionId) != "number") || (transactionId <= 0)) 
            throw new DeviceException(this.error.INVALID_ARG_ERR, "Contacts: cancel: transactionId is Invalid" );
        
        modifyObjectBaseProp(criteria);
        criteria.TransactionID = transactionId;
        var result = this.so.IDataSource.Cancel(criteria);
        //alert("result error code = " +result.ErrorCode);
        if (criteria) {
            delete criteria.TransactionID;
        }
        var errorcode = result["ErrorCode"];
        if (errorcode != 0) {
            var doMap = mappingVerification(result.ErrorCode);
            if (result["ErrorMessage"]) {
                var err_msg = splitErrorMessage(result.ErrorMessage);
                if (doMap) {
                    throw new DeviceException(MapErrorCode[errorcode], "Contacts: cancel: " + err_msg);
                }
                else {
                    throw new DeviceException(errorcode, "Contacts: cancel: " + err_msg);
                }
            }
            else {
                if (doMap) {
                    throw new DeviceException(MapErrorCode[errorcode], "Contacts: cancel: Operation Failed");
                }
                else {
                    throw new DeviceException(errorcode, "Contacts: cancel: Operation Failed");
                }
            }
        }
    } 
    catch (e) {
    
        __device_handle_exception(e, "__sp_contacts_cancel: " + e);
    }
}

function __sp_contacts_updateGroup(group){
    //alert("In __sp_contacts_updateGroup"+typeof group)
    
    if (!(group)) {
        throw new DeviceException(this.error.MISSING_ARG_ERR, "Contacts: updateGroup:Group Data is missing");
    }
    if ((typeof group) != "object") {
        //alert(" not object");
        throw new DeviceException(this.error.INVALID_ARG_ERR, 'Contacts: updateGroup:Invalid Group Data');
    }
    if (!(group && group.groupId)) {
			//alert(" contact && contact.id ");
            throw new DeviceException(this.error.MISSING_ARG_ERR, "Contacts: updateGroup: Group id is missing");
        }
	if(typeof group.groupId != "string")
	{
		   throw new DeviceException(this.error.INVALID_ARG_ERR, 'Contacts: updateGroup:Invalid Group id input');
	}
    
    try {
        var criteria = {};
        modifyObjectBaseProp(criteria);
        criteria.Type = "Group";
        var sp_data = {};
        modifyObjectBaseProp(sp_data);
        if (group != undefined) {
            if (group.groupId != undefined) {
                sp_data["id"] = group.groupId;
            }
            else {
                throw new DeviceException(this.error.MISSING_ARG_ERR, "Contacts: updateGroup: Id input is mandatory");
            }
            if (group.groupName != undefined) {
                sp_data["GroupLabel"] = group.groupName;
            }
        }
        criteria.Data = sp_data;
        
        var result = this.so.IDataSource.Add(criteria);
        //alert("In __sp_contacts_updateGroup result = "+result.ErrorCode);
        if (sp_data) {
            delete sp_data.prototype;
        }
        if (criteria) {
            delete criteria.Data;
            delete criteria.Type;
        }
        if (result.ErrorCode != 0) {
            var doMap = mappingVerification(result.ErrorCode);
            if (result.ErrorMessage) {
            
                var err_msg = splitErrorMessage(result.ErrorMessage);
                if (doMap) {
                    throw new DeviceException(MapErrorCode[result.ErrorCode], "Contacts: updateGroup: " + err_msg);
                }
                else {
                
                    throw new DeviceException(result.ErrorCode, "Contacts: updateGroup: " + err_msg);
                }
            }
            else {
                if (doMap) {
                
                    throw new DeviceException(MapErrorCode[result.ErrorCode], "Contacts: updateGroup: Operation Failed");
                }
                else {
                
                    throw new DeviceException(result.ErrorCode, "Contacts: updateGroup: Operation Failed");
                }
            }
        }
    } 
    catch (e) {
    
        __device_handle_exception(e, "__sp_contacts_updateGroup: " + e);
    }
}


function __sp_contacts_getGroupInfo(grpid){
    try {
        var criteria = {};
        modifyObjectBaseProp(criteria);
        criteria.Type = 'Group';
        
        criteria.Filter = {};
        modifyObjectBaseProp(criteria.Filter);
        if (grpid == undefined) {
            throw new DeviceException(this.error.MISSING_ARG_ERR, "Contacts: getGroupInfo: Id input is mandatory");
        }
        
        if ((typeof grpid) != "string") 
            throw new DeviceException(this.error.INVALID_ARG_ERR, "Contacts: getGroupInfo: Id input is mandatory");
        criteria.Filter.id = grpid;
        var rval = this.so.IDataSource.GetList(criteria);
        if (criteria.Filter) {
            delete criteria.Filter.id;
        }
        if (criteria) {
            delete criteria.Filter;
            delete criteria.Type;
        }
        if (rval) {
            if (rval.ErrorCode != 0) {
                var doMap = mappingVerification(rval.ErrorCode);
                if (rval.ErrorMessage) {
                    var err_msg = splitErrorMessage(rval.ErrorMessage);
                    if (doMap) {
                        throw new DeviceException(MapErrorCode[rval.ErrorCode], "Contacts: getGroupInfo: " + err_msg);
                    }
                    else {
                        throw new DeviceException(rval.ErrorCode, "Contacts: getGroupInfo: " + err_msg);
                    }
                }
                else {
                    if (doMap) {
                        throw new DeviceException(MapErrorCode[rval.ErrorCode], "Contacts: getGroupInfo: Operation Failed");
                    }
                    else {
                        throw new DeviceException(rval.ErrorCode, "Contacts: getGroupInfo: Operation Failed");
                    }
                }
                
            }
            else {
                var groupinfo = {};
                modifyObjectBaseProp(groupinfo);
                var sp_group = rval.ReturnValue.getNext();
                __sp_device_groupinfo_build(sp_group, groupinfo);
                return groupinfo;
            }
        }
    } 
    catch (e) {
        __device_handle_exception(e, "__sp_contacts_getGroupInfo:" + e);
    }
}


function mappingVerification(errorCode){
    //alert ("In mappingVerification errorCode = "+errorCode);	
    if (errorCode === 1016 || errorCode === 1012 || errorCode === 1010 || errorCode === 1009 || errorCode === 1005 || errorCode === 1000 || errorCode === 1011 || errorCode === 1007 || errorCode === 1003 || errorCode === 1002) {
        //alert("errorCode = "+errorCode);
        return true;
    }
    else {
        //alert("In mappingVerification errorCode **else part**");
        return false;
    }
}



function __sp_contacts_instance(){
    //alert(" In __sp_contacts_instance");
    
  	 	this.SORT_ASCENDING = 0;
  		this.SORT_DESCENDING = 1;
    
    //Descriptor
    this.descriptor = new __sp_contacts_descriptor();
    //Core methods
    this.startEditor = __sp_contacts_startEditor;
    //Extended methods
    this.getContacts = __sp_contacts_getContacts;
    this.getContactsCb = __sp_contacts_getContacts_cb;
    
    // this.getListSync = __sp_contacts_getListSync;
    this.addContact = __sp_contacts_add;
    this.updateContact = __sp_contacts_update;
    this.deleteContacts = __sp_contacts_delete;
    this.getContactInfo = __sp_contacts_get;
    this.addGroup = __sp_contacts_addGroup;
    
    this.getGroups = __sp_contacts_getGroups;
    this.getGroupsCb = __sp_contacts_getGroups_cb;
    
    this.deleteGroups = __sp_contacts_deleteGroups;
    this.addContactsToGroup = __sp_contacts_addContactsToGroup;
    
    this.getContactIds = __sp_contacts_getContactIds;
    this.getContactIdsCb = __sp_contacts_getContactIds_cb;
    
    this.getGroupIds = __sp_contacts_getGroupIds;
    this.getGroupIdsCb = __sp_contacts_getGroupIds_cb;
    
    this.removeContactsFromGroup = __sp_contacts_removeContactsFromGroup;
    this.cancel = __sp_contacts_cancel;
    this.updateGroup = __sp_contacts_updateGroup;
    this.getGroupInfo = __sp_contacts_getGroupInfo;
    this.error = new DeviceException(0, "Dummy");
    
    try {
        //__device_debug("Trying contacts service");
        this.so = device.getServiceObject("Service.Contact", "IDataSource");
        //__device_debug("Got contacts service object");    
    } 
    catch (e) {
        __device_handle_exception(e, "Contacts service not available " + e);
    }
}
