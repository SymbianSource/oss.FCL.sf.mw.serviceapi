/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  
*
*/

#ifndef ALARMSERVERTEST3_H
#define ALARMSERVERTEST3_H

#include "startconsolealarmserver.h"



#include <calalarm.h>
#include <caluser.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "cliwbinding.h"

#include "calendarconstants.h"
#include "calendarheader.h"
#include "EntryAttributes.h"
#include "calendarservice.h"
		

TInt RemoveCalendarFile(void* aInterfaceptr, const wchar_t* aCalname)	
	{
	GValue outparam, filterMap, error;
	
    map_construct( &filterMap, G_BINDING_DERIVED_TYPE_UNICODE, "CalendarName" , aCalname, 
                              G_TYPE_INVALID );
    
    TRAPD( err , requestservice( aInterfaceptr, "Delete" , 
	                             G_BINDING_DERIVED_TYPE_UNICODE, "Type" , L"Calendar",
	                             G_BINDING_DERIVED_TYPE_MAP    , "Data"      , filterMap, 
	                             G_TYPE_INVALID ,
	                             &outparam, NULL ,0 , &error));
			 
	map_delete(filterMap);

	resetoutput(outparam);
	
	return err;	
	
	
	}	
	
TInt AddCalendarFile(void* aInterfaceptr, const wchar_t* aCalname)	
	{
	GValue outparam, filterMap, error;
	
    map_construct( &filterMap, G_BINDING_DERIVED_TYPE_UNICODE, "CalendarName" , aCalname, 
                              G_TYPE_INVALID );
    
    TRAPD( err , requestservice( aInterfaceptr, "Add" , 
	                             G_BINDING_DERIVED_TYPE_UNICODE, "Type" , L"Calendar",
	                             G_BINDING_DERIVED_TYPE_MAP    , "Item"      , filterMap, 
	                             G_TYPE_INVALID ,
	                             &outparam, NULL ,0 , &error));
			 
	map_delete(filterMap);
	
	resetoutput(outparam);
	
	return err;	
	}		

void GetLocalUid( const TDesC& aLocalUid, TCalLocalUid& aOutLocalUid )
	{
	aOutLocalUid = 0;
	if( aLocalUid.Length() )
		{
		TInt sepPos = aLocalUid.Locate( TChar(KUidSeparator ));
		TPtrC temp;
		if( sepPos == KErrNotFound )
			{
			temp.Set(aLocalUid.Mid(0));
			}
		else
			{
			temp.Set(aLocalUid.Mid(0, sepPos));
			}

		TLex lex(temp);
		TInt32 num;

		if(lex.Val(num) == KErrNone)
			aOutLocalUid = TUint(num);
		}
	}

void GetGlobalUid( const TDesC& aGlobalUid, TDes8& aOutGlobalUid )
	{
	if( aGlobalUid.Length() )
		{
		TInt sepPos = aGlobalUid.Locate( TChar(KUidSeparator ));

		if( sepPos == KErrNotFound )
			{
			aOutGlobalUid.Copy( aGlobalUid.Mid(0) );
			}
		else
			{
			aOutGlobalUid.Copy( aGlobalUid.Mid( sepPos + 1 ) );
			}	
		}
	}
	
TInt DeleteAllCalendarEntry(void* aInterfaceptr, const wchar_t* aCalname)	
	{
	GValue outparam, filterMap, error, result;
	
    map_construct( &filterMap, G_TYPE_BOOLEAN, "DeleteAll" , 1, 
    							G_BINDING_DERIVED_TYPE_UNICODE, "CalendarName" , aCalname,
                              	G_TYPE_INVALID );
    
    TRAPD( err , requestservice( aInterfaceptr, "Delete" , 
	                             G_BINDING_DERIVED_TYPE_UNICODE, "Type" , L"CalendarEntry",
	                             G_BINDING_DERIVED_TYPE_MAP    , "Data"      , filterMap, 
	                             G_TYPE_INVALID ,
	                             &outparam, NULL ,0 , &error));
	                             
			 
	map_delete(filterMap);
	
	resetoutput(outparam);
	
	return err;	


	}
		
TInt AddEvent(void* aInterfaceptr, const wchar_t* aCalname, TUIDSet*& uids)
	{
	GValue outparam, inparam, repeatMap, result, res, value, getlistparam;
	
	GType type;	
		
	TInt error = KErrNone;

	const char *service_name   = "Service.Calendar";
	
	const char *interface_name = "IDataSource";

	int seqnum,rtype, rescnt;
		
	int cerr = 0;
	
	gint mCount = 0;
	gchar key[32];
	wchar_t  desc[20];
	wchar_t  desc1[20] = L"Meeting";
	
    TInt num = User::CountAllocCells();
    seqnum = 1;
    rtype = 1;
    int ret;

    map_construct( &inparam , G_BINDING_DERIVED_TYPE_UNICODE , "CalendarName", aCalname , 
                              G_BINDING_DERIVED_TYPE_UNICODE , "Type", L"DayEvent" ,
                              G_BINDING_DERIVED_TYPE_DATE , "StartTime" , L"20070903:093000" ,
                              G_BINDING_DERIVED_TYPE_UNICODE , "Replication", L"Open" ,
                              G_BINDING_DERIVED_TYPE_UNICODE , "Description", L"DayEvent" ,
                              G_TYPE_INVALID );
		                      
         
    TRAPD( err , requestservice( aInterfaceptr, "Add" , 
	                             G_BINDING_DERIVED_TYPE_UNICODE, "Type" , L"CalendarEntry",
	                             G_BINDING_DERIVED_TYPE_MAP    , "Item"      , inparam , 
	                             G_TYPE_INVALID ,
	                             &outparam     , NULL ,0 , &error));
	                            
	if ( err == KErrNone )
		{
		TInt x = 0;
		unsigned int luid;
		//char guid[100]; 
		wchar_t guid[100]; 
		TInt rescnt = getoutputcount(outparam);
		const char * localuid = "LocalUid";
		const char * globaluid = "GlobalUid";
		
		GType type = getoutputatindex(outparam, &result, 0);
		
		getresult(result,G_BINDING_DERIVED_TYPE_UNICODE,&guid);
		TPtrC temp((TUint16 *)guid);
        uids = new TUIDSet;
        uids->iGlobalUID = HBufC8::NewL(temp.Length());
		GetLocalUid( temp, uids->iLocalUID );
		TPtr8 tmpguid = uids->iGlobalUID->Des();
		GetGlobalUid( temp, tmpguid );
	    /*map_findvaluewithkey(result, localuid, &value );
        getresult(value,G_TYPE_UINT,&luid);

	    map_findvaluewithkey(result, globaluid, &value );
        getresult(value,G_TYPE_STRING,&guid);
        
        TPtrC8 temp((const unsigned char *)guid);
        uids = new TUIDSet;
       uids->iLocalUID = luid;
        uids->iGlobalUID = temp.AllocL();*/
		}
			 
	map_delete(inparam);
	
	resetoutput(outparam);
	
	return err;	
	
	}
 

TInt AddAppointmentWithDailyRepeat(void* aInterfaceptr, const wchar_t* aCalname, TUIDSet*& uids)
	{
	
	GValue outparam, inparam, repeatMap, result, res, value, getlistparam;
	
	GType type;	
		
	TInt error = KErrNone;

	const char *service_name   = "Service.Calendar";
	
	const char *interface_name = "IDataSource";

	int seqnum,rtype, rescnt;
		
	int cerr = 0;
	
	gint mCount = 0;
	gchar key[32];
	wchar_t  desc[20];
	wchar_t  desc1[20] = L"Meeting";
	
    TInt num = User::CountAllocCells();
    seqnum = 1;
    rtype = 1;
    int ret;
    map_construct( &repeatMap , G_TYPE_INT, "Type" , rtype , 
                              G_BINDING_DERIVED_TYPE_DATE , "StartDate" , L"20070903:093000" ,
                              G_BINDING_DERIVED_TYPE_DATE , "UntilDate" , L"20070907:103000" ,
                              G_TYPE_INVALID );
    
    map_construct( &inparam , G_BINDING_DERIVED_TYPE_UNICODE , "CalendarName", aCalname , 
                              G_BINDING_DERIVED_TYPE_UNICODE , "Type", L"Meeting" ,
                              G_TYPE_INT, "SeqNum" , seqnum ,
                              G_BINDING_DERIVED_TYPE_DATE , "StartTime" , L"20070903:093000" ,
                              G_BINDING_DERIVED_TYPE_DATE , "EndTime" , L"20070903:103000" ,
                              G_BINDING_DERIVED_TYPE_UNICODE , "Replication", L"Open" ,
                              G_BINDING_DERIVED_TYPE_UNICODE , "Description", L"Meeting" ,
                              G_BINDING_DERIVED_TYPE_UNICODE , "Location", L"Hara" ,
                              G_BINDING_DERIVED_TYPE_UNICODE , "Status", L"Confirmed" ,
                              G_BINDING_DERIVED_TYPE_UNICODE , "Method", L"None" ,
                              G_BINDING_DERIVED_TYPE_MAP, "RepeatRule" , repeatMap ,
                              G_TYPE_INVALID );
		                      
         
    TRAPD( err , requestservice( aInterfaceptr, "Add" , 
	                             G_BINDING_DERIVED_TYPE_UNICODE, "Type" , L"CalendarEntry",
	                             G_BINDING_DERIVED_TYPE_MAP    , "Item"      , inparam , 
	                             G_TYPE_INVALID ,
	                             &outparam     , NULL ,0 , &error));
	                            
	if ( err == KErrNone )
		{
		TInt x = 0;
		unsigned int luid;
		//char guid[100]; 
		wchar_t guid[100]; 
		TInt rescnt = getoutputcount(outparam);
		const char * localuid = "LocalUid";
		const char * globaluid = "GlobalUid";
		
		GType type = getoutputatindex(outparam, &result, 0);
		
		getresult(result,G_BINDING_DERIVED_TYPE_UNICODE,&guid);
		TPtrC temp((TUint16 *)guid);
        uids = new TUIDSet;
        uids->iGlobalUID = HBufC8::NewL(temp.Length());
		GetLocalUid( temp, uids->iLocalUID );
		TPtr8 tmpguid = uids->iGlobalUID->Des();
		GetGlobalUid( temp, tmpguid );
	    /*map_findvaluewithkey(result, localuid, &value );
        getresult(value,G_TYPE_UINT,&luid);

	    map_findvaluewithkey(result, globaluid, &value );
        getresult(value,G_TYPE_STRING,&guid);
        
        TPtrC8 temp((const unsigned char *)guid);
        uids = new TUIDSet;
       uids->iLocalUID = luid;
        uids->iGlobalUID = temp.AllocL();*/
		}
			 
	map_delete(repeatMap);
	
	map_delete(inparam);
	
	resetoutput(outparam);
	
	return err;	
	
    }
    
TInt AddTodoEntry(void* aInterfaceptr, const wchar_t* aCalname, TUIDSet*& uids)
	{
	
	GValue outparam, inparam, repeatMap, result, res, value, getlistparam;
	
	GType type;	
		
	TInt error = KErrNone;

	const char *service_name   = "Service.Calendar";
	
	const char *interface_name = "IDataSource";

	int seqnum,rtype, rescnt;
		
	int cerr = 0;
	
	gint mCount = 0;
	gchar key[32];
	wchar_t  desc[20];
	wchar_t  desc1[20] = L"Meeting";
	
    TInt num = User::CountAllocCells();
    seqnum = 1;
    rtype = 1;
    int ret;
    
    map_construct( &inparam , G_BINDING_DERIVED_TYPE_UNICODE , "CalendarName", aCalname , 
                              G_BINDING_DERIVED_TYPE_UNICODE , "Type", L"ToDo" ,
                              G_TYPE_INT, "SeqNum" , seqnum ,
                              G_BINDING_DERIVED_TYPE_DATE , "EndTime" , L"20070820:000000" ,
                              G_BINDING_DERIVED_TYPE_UNICODE , "Replication", L"Open" ,
                              G_BINDING_DERIVED_TYPE_UNICODE , "Description", L"ToDo entry" ,
                              G_BINDING_DERIVED_TYPE_UNICODE , "Method", L"None" ,
                              G_TYPE_INVALID );
		                      
         
    TRAPD( err , requestservice( aInterfaceptr, "Add" , 
	                             G_BINDING_DERIVED_TYPE_UNICODE, "Type" , L"CalendarEntry",
	                             G_BINDING_DERIVED_TYPE_MAP    , "Item"      , inparam , 
	                             G_TYPE_INVALID ,
	                             &outparam     , NULL ,0 , &error));
	                            
			 
	if ( err == KErrNone )
		{
		TInt x = 0;
		unsigned int luid;
		//char guid[100]; 
		wchar_t guid[100]; 
		TInt rescnt = getoutputcount(outparam);
		const char * localuid = "LocalUid";
		const char * globaluid = "GlobalUid";
		
		GType type = getoutputatindex(outparam, &result, 0);
		
		getresult(result,G_BINDING_DERIVED_TYPE_UNICODE,&guid);
		TPtrC temp((TUint16 *)guid);
        uids = new TUIDSet;
        uids->iGlobalUID = HBufC8::NewL(temp.Length());
		GetLocalUid( temp, uids->iLocalUID );
		TPtr8 tmpguid = uids->iGlobalUID->Des();
		GetGlobalUid( temp, tmpguid );
	    /*map_findvaluewithkey(result, localuid, &value );
        getresult(value,G_TYPE_UINT,&luid);

	    map_findvaluewithkey(result, globaluid, &value );
        getresult(value,G_TYPE_STRING,&guid);
        
        TPtrC8 temp((const unsigned char *)guid);
        uids = new TUIDSet;
       uids->iLocalUID = luid;
        uids->iGlobalUID = temp.AllocL();*/
		}
			 
	map_delete(inparam);
	
	resetoutput(outparam);
	
	return err;	
	
    }
    
TInt AddDayEvent(void* aInterfaceptr, const wchar_t* aCalname, TUIDSet*& uids)
	{
	
	GValue outparam, inparam, repeatMap, result, res, value, getlistparam;
	
	GType type;	
		
	TInt error = KErrNone;

	const char *service_name   = "Service.Calendar";
	
	const char *interface_name = "IDataSource";

	int seqnum,rtype, rescnt;
		
	int cerr = 0;
	
	gint mCount = 0;
	gchar key[32];
	wchar_t  desc[20];
	wchar_t  desc1[20] = L"Meeting";
	
    TInt num = User::CountAllocCells();
    seqnum = 1;
    rtype = 1;
    int ret;
    
    map_construct( &inparam , G_BINDING_DERIVED_TYPE_UNICODE , "CalendarName", aCalname , 
                              G_BINDING_DERIVED_TYPE_UNICODE , "Type", L"DayEvent" ,
                              G_TYPE_INT, "SeqNum" , seqnum ,
                              G_BINDING_DERIVED_TYPE_DATE , "StartTime" , L"20070620:000000" ,
                              G_BINDING_DERIVED_TYPE_UNICODE , "Replication", L"Open" ,
                              G_BINDING_DERIVED_TYPE_UNICODE , "Description", L"Day event created" ,
                              G_BINDING_DERIVED_TYPE_UNICODE , "Method", L"None" ,
                              G_TYPE_INVALID );
		                      
         
    TRAPD( err , requestservice( aInterfaceptr, "Add" , 
	                             G_BINDING_DERIVED_TYPE_UNICODE, "Type" , L"CalendarEntry",
	                             G_BINDING_DERIVED_TYPE_MAP    , "Item"      , inparam , 
	                             G_TYPE_INVALID ,
	                             &outparam     , NULL ,0 , &error));
	                            
			 
	if ( err == KErrNone )
		{
		TInt x = 0;
		unsigned int luid;
		//char guid[100]; 
		wchar_t guid[100]; 
		TInt rescnt = getoutputcount(outparam);
		const char * localuid = "LocalUid";
		const char * globaluid = "GlobalUid";
		
		GType type = getoutputatindex(outparam, &result, 0);
		
		getresult(result,G_BINDING_DERIVED_TYPE_UNICODE,&guid);
		TPtrC temp((TUint16 *)guid);
        uids = new TUIDSet;
        uids->iGlobalUID = HBufC8::NewL(temp.Length());
		GetLocalUid( temp, uids->iLocalUID );
		TPtr8 tmpguid = uids->iGlobalUID->Des();
		GetGlobalUid( temp, tmpguid );
	    /*map_findvaluewithkey(result, localuid, &value );
        getresult(value,G_TYPE_UINT,&luid);

	    map_findvaluewithkey(result, globaluid, &value );
        getresult(value,G_TYPE_STRING,&guid);
        
        TPtrC8 temp((const unsigned char *)guid);
        uids = new TUIDSet;
       uids->iLocalUID = luid;
        uids->iGlobalUID = temp.AllocL();*/
		}
			 
	map_delete(inparam);
	
	resetoutput(outparam);
	
	return err;	
	
    }
    
TInt AddAnniversary(void* aInterfaceptr, const wchar_t* aCalname, TUIDSet*& uids)
	{
	
	GValue outparam, inparam, repeatMap, result, res, value, getlistparam;
	
	GType type;	
		
	TInt error = KErrNone;

	const char *service_name   = "Service.Calendar";
	
	const char *interface_name = "IDataSource";

	int seqnum,rtype, rescnt;
		
	int cerr = 0;
	
	gint mCount = 0;
	gchar key[32];
	wchar_t  desc[20];
	wchar_t  desc1[20] = L"Meeting";
	
    TInt num = User::CountAllocCells();
    seqnum = 1;
    rtype = 1;
    int ret;
    
    map_construct( &inparam , G_BINDING_DERIVED_TYPE_UNICODE , "CalendarName", aCalname , 
                              G_BINDING_DERIVED_TYPE_UNICODE , "Type", L"Anniversary" ,
                              G_TYPE_INT, "SeqNum" , seqnum ,
                              G_BINDING_DERIVED_TYPE_DATE , "StartTime" , L"20071129:000000" ,
                              G_BINDING_DERIVED_TYPE_UNICODE , "Replication", L"Private" ,
                              G_BINDING_DERIVED_TYPE_UNICODE , "Description", L"Anniversary created" ,
                              G_BINDING_DERIVED_TYPE_UNICODE , "Method", L"None" ,
                              G_TYPE_INVALID );
		                      
         
    TRAPD( err , requestservice( aInterfaceptr, "Add" , 
	                             G_BINDING_DERIVED_TYPE_UNICODE, "Type" , L"CalendarEntry",
	                             G_BINDING_DERIVED_TYPE_MAP    , "Item"      , inparam , 
	                             G_TYPE_INVALID ,
	                             &outparam     , NULL ,0 , &error));
	                            
			 
	if ( err == KErrNone )
		{
		TInt x = 0;
		unsigned int luid;
		//char guid[100]; 
		wchar_t guid[100]; 
		TInt rescnt = getoutputcount(outparam);
		const char * localuid = "LocalUid";
		const char * globaluid = "GlobalUid";
		
		GType type = getoutputatindex(outparam, &result, 0);
		
		getresult(result,G_BINDING_DERIVED_TYPE_UNICODE,&guid);
		TPtrC temp((TUint16 *)guid);
        uids = new TUIDSet;
        uids->iGlobalUID = HBufC8::NewL(temp.Length());
		GetLocalUid( temp, uids->iLocalUID );
		TPtr8 tmpguid = uids->iGlobalUID->Des();
		GetGlobalUid( temp, tmpguid );
	    /*map_findvaluewithkey(result, localuid, &value );
        getresult(value,G_TYPE_UINT,&luid);

	    map_findvaluewithkey(result, globaluid, &value );
        getresult(value,G_TYPE_STRING,&guid);
        
        TPtrC8 temp((const unsigned char *)guid);
        uids = new TUIDSet;
       uids->iLocalUID = luid;
        uids->iGlobalUID = temp.AllocL();*/
		}
			 
	map_delete(inparam);
	
	resetoutput(outparam);
	
	return err;	
	
    }
    
TInt AddReminder(void* aInterfaceptr, const wchar_t* aCalname, TUIDSet*& uids)
	{
	
	GValue outparam, inparam, repeatMap, result, res, value, getlistparam;
	
	GType type;	
		
	TInt error = KErrNone;

	const char *service_name   = "Service.Calendar";
	
	const char *interface_name = "IDataSource";

	int seqnum,rtype, rescnt;
		
	int cerr = 0;
	
	gint mCount = 0;
	gchar key[32];
	wchar_t  desc[20];
	wchar_t  desc1[20] = L"Meeting";
	
    TInt num = User::CountAllocCells();
    seqnum = 1;
    rtype = 1;
    int ret;
    
    map_construct( &inparam , G_BINDING_DERIVED_TYPE_UNICODE , "CalendarName", aCalname , 
                              G_BINDING_DERIVED_TYPE_UNICODE , "Type", L"Reminder" ,
                              G_TYPE_INT, "SeqNum" , seqnum ,
                              G_BINDING_DERIVED_TYPE_DATE , "StartTime" , L"20070621:103000" ,
                              G_BINDING_DERIVED_TYPE_UNICODE , "Replication", L"Private" ,
                              G_BINDING_DERIVED_TYPE_UNICODE , "Description", L"Reminder created" ,
                              G_BINDING_DERIVED_TYPE_UNICODE , "Method", L"None" ,
                              G_TYPE_INVALID );
		                      
         
    TRAPD( err , requestservice( aInterfaceptr, "Add" , 
	                             G_BINDING_DERIVED_TYPE_UNICODE, "Type" , L"CalendarEntry",
	                             G_BINDING_DERIVED_TYPE_MAP    , "Item"      , inparam , 
	                             G_TYPE_INVALID ,
	                             &outparam     , NULL ,0 , &error));
	                            
			 
	if ( err == KErrNone )
		{
		TInt x = 0;
		unsigned int luid;
		//char guid[100]; 
		wchar_t guid[100]; 
		TInt rescnt = getoutputcount(outparam);
		const char * localuid = "LocalUid";
		const char * globaluid = "GlobalUid";
		
		GType type = getoutputatindex(outparam, &result, 0);
		
		getresult(result,G_BINDING_DERIVED_TYPE_UNICODE,&guid);
		TPtrC temp((TUint16 *)guid);
        uids = new TUIDSet;
        uids->iGlobalUID = HBufC8::NewL(temp.Length());
		GetLocalUid( temp, uids->iLocalUID );
		TPtr8 tmpguid = uids->iGlobalUID->Des();
		GetGlobalUid( temp, tmpguid );
	    /*map_findvaluewithkey(result, localuid, &value );
        getresult(value,G_TYPE_UINT,&luid);

	    map_findvaluewithkey(result, globaluid, &value );
        getresult(value,G_TYPE_STRING,&guid);
        
        TPtrC8 temp((const unsigned char *)guid);
        uids = new TUIDSet;
       uids->iLocalUID = luid;
        uids->iGlobalUID = temp.AllocL();*/
		}
			 
	map_delete(inparam);
	
	resetoutput(outparam);
	
	return err;	
	
    }
TInt AddAppointmentWithoutRepeat(void* aInterfaceptr, const wchar_t* aCalname, TUIDSet*& uids)
	{
	
	GValue outparam, inparam, repeatMap, result, res, value, getlistparam;
	
	GType type;	
		
	TInt error = KErrNone;

	const char *service_name   = "Service.Calendar";
	
	const char *interface_name = "IDataSource";

	int seqnum,rtype, rescnt;
		
	int cerr = 0;
	
	gint mCount = 0;
	gchar key[32];
	wchar_t  desc[20];
	wchar_t  desc1[20] = L"Meeting";
	
    TInt num = User::CountAllocCells();
    seqnum = 1;
    rtype = 1;
    int ret;
    
    map_construct( &inparam , G_BINDING_DERIVED_TYPE_UNICODE , "CalendarName", aCalname , 
                              G_BINDING_DERIVED_TYPE_UNICODE , "Type", L"Meeting" ,
                              G_TYPE_INT, "SeqNum" , seqnum ,
                              G_BINDING_DERIVED_TYPE_DATE , "StartTime" , L"20070903:093000" ,
                              G_BINDING_DERIVED_TYPE_DATE , "EndTime" , L"20070903:103000" ,
                              G_BINDING_DERIVED_TYPE_UNICODE , "Replication", L"Open" ,
                              G_BINDING_DERIVED_TYPE_UNICODE , "Description", L"Meeting" ,
                              G_BINDING_DERIVED_TYPE_UNICODE , "Location", L"Hara" ,
                              G_BINDING_DERIVED_TYPE_UNICODE , "Status", L"Confirmed" ,
                              G_BINDING_DERIVED_TYPE_UNICODE , "Method", L"None" ,
                              G_TYPE_INVALID );
		                      
         
    TRAPD( err , requestservice( aInterfaceptr, "Add" , 
	                             G_BINDING_DERIVED_TYPE_UNICODE, "Type" , L"CalendarEntry",
	                             G_BINDING_DERIVED_TYPE_MAP    , "Item"      , inparam , 
	                             G_TYPE_INVALID ,
	                             &outparam     , NULL ,0 , &error));
	                            
			 
	if ( err == KErrNone )
		{
		TInt x = 0;
		unsigned int luid;
		//char guid[100]; 
		wchar_t guid[100]; 
		TInt rescnt = getoutputcount(outparam);
		const char * localuid = "LocalUid";
		const char * globaluid = "GlobalUid";
		
		GType type = getoutputatindex(outparam, &result, 0);
		
		getresult(result,G_BINDING_DERIVED_TYPE_UNICODE,&guid);
		TPtrC temp((TUint16 *)guid);
        uids = new TUIDSet;
        uids->iGlobalUID = HBufC8::NewL(temp.Length());
		GetLocalUid( temp, uids->iLocalUID );
		TPtr8 tmpguid = uids->iGlobalUID->Des();
		GetGlobalUid( temp, tmpguid );
	    /*map_findvaluewithkey(result, localuid, &value );
        getresult(value,G_TYPE_UINT,&luid);

	    map_findvaluewithkey(result, globaluid, &value );
        getresult(value,G_TYPE_STRING,&guid);
        
        TPtrC8 temp((const unsigned char *)guid);
        uids = new TUIDSet;
       uids->iLocalUID = luid;
        uids->iGlobalUID = temp.AllocL();*/
		}
			 
	map_delete(inparam);
	
	resetoutput(outparam);
	
	return err;	
	
    }

#endif	
