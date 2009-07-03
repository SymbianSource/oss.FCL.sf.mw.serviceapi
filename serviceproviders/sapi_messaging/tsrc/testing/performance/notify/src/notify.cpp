/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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



// INCLUDE FILES

#include <unistd.h>
#include <wchar.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <e32std.h>
#include <e32des16.h>
#include <f32file.h>
#include <pthread.h>
#include <semaphore.h>

#include <rsendas.h>
#include <rsendasmessage.h>
#include <msvstd.h>
#include <msvapi.h>
#include <msvids.h>
////#include <senduiconsts.h>
#include <mmsconst.h>
#include <csendasaccounts.h>
#include <cmsvrecipientlist.h>


#include "cliwbinding.h"
#include "notify.h"

const char *service_name   = "Service.Messaging";
const char *interface_name = "IMessaging";

int id ,flag1;

int MycallBack( GValue* output )
{
	GValue msgtypeval,msgaddrval,msgidval,msgflagval,msgtimeval,iter,key_value;
	wchar_t  msgtype[20], msgaddr[20],msgtime[20],msgsub[20];
	int cErr = 0;
	int msgid = 0,mCount,mess_id ;
	bool msgunread = TRUE, msgattach ;
	int rescnt;
	GType type;
	GValue resmap;
	
	TTime notify;
	notify.HomeTime();
	TDateTime date = notify.DateTime();
	TInt day = date.Day();
	TMonth month = date.Month();
	TInt hour = date.Hour();
	TInt min = date.Minute();
	TInt sec = date.Second();
	TInt micsec = date.MicroSecond();
	
	sapifd = fopen("C:\\cliwbinding_messaging.txt2", "a");
	fprintf(sapifd,"%s : %d\n", "day", day+1);
	fprintf(sapifd,"%s : %d\n", "month", month+1);
	fprintf(sapifd,"%s : %d\n", "hour", hour);
	fprintf(sapifd,"%s : %d\n", "min", min);
	fprintf(sapifd,"%s : %d\n", "sec", sec);
	fprintf(sapifd,"%s : %d\n", "microsec", micsec);
	fclose(sapifd);
	
	pthread_t tid1 = pthread_self();
	stopscheduler(tid1);
	
	rescnt = getoutputcount(*output);	
	type = getoutputatindex(*output, &resmap, 0);
 
    mCount = map_count(resmap);	           	
	cErr = map_findvaluewithkey(resmap, "Time", &key_value );
	getresult(key_value,G_BINDING_DERIVED_TYPE_UNICODE,&msgtime); 			   		
	
	sapifd = fopen("C:\\cliwbinding_messaging.txt2", "a");
	fwprintf(sapifd,L"%s : %ls\n", "Time", msgtime);
	fclose(sapifd);
	
	resetoutput(*output);

	return KErrNone;
}

void* MsgGetNotification(void *)
{	
	void *interface_pointer = NULL;	
	GValue outparam ,inplist, inparam, result, iter, key_value;	
	int error, messid,cErr,mCount ;

	cbindingattach();
	pthread_t tid =pthread_self();
	createnewscheduler(tid);
	interface_pointer = loadservice(service_name, interface_name);

	TRAPD(err ,requestservice(interface_pointer, "RegisterNotification" , 
	                          G_BINDING_DERIVED_TYPE_UNICODE,"Type",L"NewMessage",
	                          G_TYPE_INVALID,&outparam ,MycallBack ,0 , &error));

	startscheduler(tid);

	unloadservice(service_name, interface_name);
	closeinterface(interface_pointer);
	cbindingdetach();
	 
}

TInt E32Main()
{	
	pthread_t tid;	
	int ret = pthread_create(&tid, NULL, MsgGetNotification,NULL);

	if(ret)
	{
		printf("ERROR; return code from pthread_create() is %d\n", ret);
    	exit(-1);
	}

	pthread_join(tid, NULL);
	
	if(flag1 == 1)
	 return KErrNone;
	else
	 return KErrGeneral;
}

	
	