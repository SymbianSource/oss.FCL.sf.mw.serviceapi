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
////#include <senduiconsts.h>
#include <mmsconst.h>
#include <csendasaccounts.h>
#include <cmsvrecipientlist.h>


#include "cliwbinding.h"
#include "getlist.h"

#ifdef __WINSCW__ 
	#define KFolderID KMsvDraftEntryId;
#else
	#define KFolderID KMsvGlobalInBoxIndexEntryId;
#endif

const char *service_name   = "Service.Messaging";
const char *interface_name = "IMessaging";


void SAPIStartPerformanceTestL()
{
	
	void *interface_pointer = NULL;	
	GValue inparam, inparamlist, outparam, iter , map[10], errn , key_value;	
	TInt error , mCount, cErr , id , cnt=0 ,j;
	TTime start; 
    TTime end;	
    TTimeIntervalMicroSeconds timeTaken ; 
    TInt64 aTimeDelay, aSum = 0.0, aAvgTime = 0.0 ;
    char key[25];
    TPtrC sub , sen;
    TInt i;
    
    fdsapig = fopen(logfgl, "a");

	
	    
//   for(i=0;i<5;i++)
//   {
	start.HomeTime();
	cbindingattach();
	    
	interface_pointer = loadservice(service_name, interface_name);
		   
	list_construct(&inparamlist, G_BINDING_DERIVED_TYPE_UNICODE , L"SMS");
	
	map_construct(&inparam,G_BINDING_DERIVED_TYPE_LIST, "MessageTypeList",inparamlist, G_TYPE_INVALID);

	TRAPD(err ,requestservice(interface_pointer, "GetList" , G_BINDING_DERIVED_TYPE_MAP ,"Filter"
	                          ,inparam ,G_TYPE_INVALID, &outparam ,NULL ,0 , &error));
	        	
    
/*    for(j=0;j<2;j++)
    {
	 iterator_next(outparam , &iter);
    
     mCount = map_count(iter);	      
     
     while(mCount)
	        {
	        memset(&key_value, 0, sizeof(GValue));
	        mCount -= 1;
	        cErr = map_findkeyatindex(iter, mCount, key);	
	        cErr = map_findvaluewithkey(iter, key, &key_value );
	        if(!strcmp(key,"MessageId"))
	            {
	             getresult(key_value,G_TYPE_INT,&id);
	            }
	        }

    }*/
    
           
	if(err== 0)
	{ 	
	  end.HomeTime();
	  cnt++;
	  timeTaken = end.MicroSecondsFrom(start);  
	  fprintf(fdsapig ,"delay() - %lld\n",timeTaken);
	  aTimeDelay = timeTaken.Int64() ;	  
	  aSum = aSum + aTimeDelay ;
	}
	else
	{
	  User::Leave(err);
	}
	

	map_delete(inparam);
	list_delete(inparamlist);
	list_delete(outparam);
	
	unloadservice(service_name, interface_name);
	closeinterface(interface_pointer);
	cbindingdetach();
//   }	
	
//	aAvgTime = aSum/cnt ;
//	fprintf(fdsapig ,"avg time taken() - %ld\n",aAvgTime);
	fprintf(fdsapig,"\n");
	fclose(fdsapig);	

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
	
	
