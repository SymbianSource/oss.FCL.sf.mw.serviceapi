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
#include "asyncsend.h"

const char *service_name   = "Service.Messaging";
const char *interface_name = "IMessaging";
	
int MycallBack( GValue* output )
{	
	FILE* fp = NULL;
	
	pthread_t tid1 = pthread_self();
	stopscheduler(tid1);
	
//	resetoutput(*output);
	return 0;
}

void* MsgGetNotification(void * /*x*/)
{	
	void *interface_pointer = NULL;	
	GValue outparam ,inparam ,inparamlist, result ,key_value, iter;	
	TInt error, messid ,cErr ,mCount ;
	TTime start; 
  TTime end;	
  TTimeIntervalMicroSeconds timeTaken ; 

	const char *service_name   = "Service.Messaging";
	const char *interface_name = "IMessaging";
	
	start.HomeTime();
	cbindingattach();
	
	pthread_t tid =pthread_self();
	createnewscheduler(tid);
	
	interface_pointer = loadservice(service_name, interface_name);
	

	list_construct(&inparamlist, G_BINDING_DERIVED_TYPE_UNICODE ,L"9008032761",G_TYPE_INVALID);


	map_construct(&inparam,G_BINDING_DERIVED_TYPE_LIST, "To",inparamlist,
	               G_BINDING_DERIVED_TYPE_UNICODE,"BodyText", L"pinging" ,G_TYPE_INVALID);


	TRAPD(err1 ,requestservice(interface_pointer, "Send" , G_BINDING_DERIVED_TYPE_UNICODE,
	                           "MessageType",L"SMS",G_BINDING_DERIVED_TYPE_MAP ,"MessageParam",
	                            inparam ,G_TYPE_INVALID,&outparam ,MycallBack ,0 , &error));


	startscheduler(tid);
 
	
	list_delete(inparamlist);
	map_delete(inparam);
	
	unloadservice(service_name, interface_name);
	closeinterface(interface_pointer);
	cbindingdetach();
	
	end.HomeTime();
	timeTaken = end.MicroSecondsFrom(start);  
	
	fdsapias = fopen("C:\\cliwbinding_messaging.txt1", "a");	
	fprintf(fdsapias ,"delay() - %lld\n",timeTaken);
	fclose(fdsapias); 

	return NULL;
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
	
	return KErrNone;
	} 

	
	