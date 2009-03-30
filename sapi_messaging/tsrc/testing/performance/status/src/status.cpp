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

#include <rsendas.h>
#include <rsendasmessage.h>
#include <msvstd.h>
#include <msvapi.h>
#include <msvids.h>
//#include <senduiconsts.h>
#include <mmsconst.h>
#include <csendasaccounts.h>
#include <cmsvrecipientlist.h>


#include "cliwbinding.h"
#include "status.h"


void SAPIStartPerformanceTestL()
{
	
	char *service_name   = "Service.Messaging";
	char *interface_name = "IMessaging";
	
	void *interface_pointer = NULL;	
	GValue outparam;	
	TInt error , cnt=0, i;
	TTime start; 
    TTime end;	
    TTimeIntervalMicroSeconds timeTaken ; 
    TInt64 aTimeDelay, aSum = 0.0, aAvgTime = 0.0 ;
    TInt id = 1048801;
        
    fdst = fopen(logfst, "a");

   for(i = 0;i < 10; i++)
   {
	id = id + 1;
	start.HomeTime();
	    
	cbindingattach();
	    
	interface_pointer = loadservice(service_name, interface_name);		                 
	    
//	if(i%2 == 0)
//	{
	 TRAPD(err ,requestservice(interface_pointer, "ChangeStatus" , G_TYPE_INT, "MessageId", 
	                           id ,G_BINDING_DERIVED_TYPE_UNICODE, "Status", L"Unread", 
	                           G_TYPE_INVALID, &outparam ,NULL ,0 , &error));
//	}  
/*	else
	{
	 TRAPD(err ,requestservice(interface_pointer, "ChangeStatus" , G_TYPE_INT, "MessageId", 
	                           1048782 ,G_BINDING_DERIVED_TYPE_UNICODE, "Status", L"Read", 
	                           G_TYPE_INVALID, &outparam ,NULL ,0 , &error));	
	}  */   	

        
	if(error== 0)
	{ 	
	  end.HomeTime();
	  cnt++;
	  timeTaken = end.MicroSecondsFrom(start);
	  fprintf(fdst ,"delay() - %lld\n",timeTaken);
	  aTimeDelay = timeTaken.Int64() ;
	  aSum = aSum + aTimeDelay ;
	}
	else
	{
	  end.HomeTime();
	  User::Leave(error);
	}

	list_delete(outparam);
	
	unloadservice(service_name, interface_name);
	closeinterface(interface_pointer);
	cbindingdetach();
   }
   
	aAvgTime = aSum/cnt ;
	fprintf(fdst ,"avg time taken() - %ld\n",aAvgTime);	
	fprintf(fdst,"\n");
	fclose(fdst);

}

TInt E32Main()
	{
	__UHEAP_MARK;
	CTrapCleanup* cleanup = CTrapCleanup::New();
	
  	TRAPD(error, SAPIStartPerformanceTestL());
    __ASSERT_ALWAYS(!error, User::Panic(_L("LIBC PANIC"), error));

	delete cleanup;
	__UHEAP_MARKEND;
	return 0;
	} 
	
	
	