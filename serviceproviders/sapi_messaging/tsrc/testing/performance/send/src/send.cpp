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

#include <e32base.h>
#include <e32cons.h>
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
#include "send.h"

const char *service_name   = "Service.Messaging";
const char *interface_name = "IMessaging";


void SAPIStartPerformanceTestL()
{
	
	void *interface_pointer = NULL;	
	GValue inparam, inparamlist, outparam;	
	TInt error , cnt = 0 ,i ;
	TTime start; 
    TTime end;	
    TTimeIntervalMicroSeconds timeTaken ; 
    TInt64 aTimeDelay, aSum = 0.0, aAvgTime = 0.0 ;	
    
    fdsapi = fopen(logsa, "a");

   for(i = 0;i < 10; i++)
   {
	start.HomeTime();
	    
	cbindingattach();
	    
	interface_pointer = loadservice(service_name, interface_name);

	list_construct(&inparamlist, G_BINDING_DERIVED_TYPE_UNICODE ,L"9008032761",G_TYPE_INVALID);

	map_construct(&inparam,G_BINDING_DERIVED_TYPE_LIST, "To",inparamlist,
		          G_BINDING_DERIVED_TYPE_UNICODE,"BodyText", L"pinging" ,G_TYPE_INVALID);
		                       
	    
	TRAPD(err ,requestservice(interface_pointer, "Send" , G_BINDING_DERIVED_TYPE_UNICODE,
	                           "MessageType",L"SMS",G_BINDING_DERIVED_TYPE_MAP ,"MessageParam",
	                            inparam ,G_TYPE_INVALID,&outparam ,NULL ,0 , &error));
	        	
    
        
	if(error== 0)
	{ 	
	  end.HomeTime();
	  cnt++;
	  timeTaken = end.MicroSecondsFrom(start);
	  fprintf(fdsapi ,"delay() - %lld\n",timeTaken);
	  aTimeDelay = timeTaken.Int64() ;
	  aSum = aSum + aTimeDelay ;
	}
	else
	{
	  end.HomeTime();
	  User::Leave(err);
	}
	
	map_delete(inparam);
	list_delete(inparamlist);
	list_delete(outparam);
	
	closeinterface(interface_pointer);
	unloadservice(service_name, interface_name);	
	cbindingdetach();	
   }
	
	aAvgTime = aSum/cnt ;
	fprintf(fdsapi ,"avg time taken() - %ld\n",aAvgTime);
	fprintf(fdsapi,"\n");
	fclose(fdsapi);	

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
	
	

