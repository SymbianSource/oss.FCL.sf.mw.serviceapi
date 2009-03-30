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
* Description:   getlocperf performance test
*                (a) getlocation
*
*/



//#include <unistd.h>

//#include <string.h>
//#include <ctype.h>
//#include <fcntl.h>
//#include <dirent.h>
//#include <utf.h>
//#include <pthread.h>
//#include <sys/mman.h>
//#include <sys/types.h>
//#include <sys/stat.h>
//#include <e32des16.h>




#include <e32std.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "getfileinfoperf.h"

_LIT(LogFileName , "C:\\Notifications.txt") ;
RFile LogFile ;
RFs LogSession ;
TBuf8<50> buf ;
TRealFormat format ;
double res[3] ;
sem_t mySemaphore = NULL; 
		
void OpenFile()
	{
	LogSession.Connect() ;

	if(LogFile.Open(LogSession ,LogFileName , EFileWrite | EFileShareAny )  == KErrNotFound)
		{
		LogFile.Replace(LogSession ,LogFileName , EFileWrite | EFileShareAny ) ;
		}

	TInt End = 0 ;
	LogFile.Seek(ESeekEnd , End) ; 
	}

void CloseFile()
	{
	LogFile.Close() ;
	LogSession.Close() ;
	}
  
int media_file_cb(GValue* value)
    {
    
    
    GValue media_map,key_value;
    gint error = -1;
    gint mCount = 0;
    gint cErr = 0;
    gchar key[32];
    wchar_t file_path[80];
    error = geterrorvalue(*value);  
        
    while(!iterator_next(*value,&media_map))
	    {
	    mCount = map_count(media_map);
	    while(mCount)
	        {
	        mCount -= 1;
	        cErr = map_findkeyatindex(media_map, mCount, key);	
	        cErr = map_findvaluewithkey(media_map, key, &key_value );
	        OpenFile();
	        if(!strcmp(key,"FileNameAndPath"))
	            {
	            getresult(key_value,G_BINDING_DERIVED_TYPE_UNICODE,file_path);
	            //LogFile.Write(_L8("\n") ) ;
	            //LogFile.Write(file_path) ;
	            }
	        CloseFile();
	        }
	    }
    free(value);
    sem_post(&mySemaphore);
    return error;

	 	
	}
	

TInt SapiPerformanceTestL()
	{
  	
	  	const gchar* operation = "GetList";
	  	const char *serviceName   = "Service.MediaManagement";
		const char *interfaceName = "IDataSource";
		
		void *interfacePtr = NULL ;  // handle for storing the interface instance
		
		GValue filter, sort;
	   	int error = -1;
		int returnStatus = 0;

		TBool aFlag  = EFalse ;
		interfacePtr = loadservice(serviceName, interfaceName) ;
		
		/* check if the pointer is valid */
		if(interfacePtr == NULL)
			{
			return (-1) ;
			}


	GValue *media_result = NULL;

	map_construct(&filter,G_BINDING_DERIVED_TYPE_UNICODE,"FileType",L"Music",
						  G_TYPE_INVALID);
	                      
	map_construct(&sort,G_BINDING_DERIVED_TYPE_UNICODE,"MetaData",L"Composer",
	                    G_BINDING_DERIVED_TYPE_UNICODE,"Order",L"Descending",
	                    G_TYPE_INVALID); 
	                    
	media_result = (GValue *)malloc(sizeof(GValue));
	if(media_result == NULL)
	    {
	    return (-1);
	    }
	  
	    
	  requestservice(interfacePtr, operation, 
				   G_BINDING_DERIVED_TYPE_UNICODE, "ContentType",L"File", 
				   G_BINDING_DERIVED_TYPE_MAP, "Filter", filter,
				   G_BINDING_DERIVED_TYPE_MAP, "Sort", sort,
				   G_TYPE_INVALID,
				   media_result, media_file_cb, 0, &error);
	
	aFlag  = ETrue ;			   
	if(sem_wait(&mySemaphore))
		{
			map_delete(filter);
			map_delete(sort);
	
			closeinterface(interfacePtr) ;
	
			unloadservice(serviceName, interfaceName) ;
	
			cbindingdetach();
	

		
		}
			 

		/* Get the system time after invoking the service */
		
		
		
		/* Delay measured interms of microseconds */
		
		
		OpenFile();
		
		if( aFlag )
			{
		
			LogFile.Write(_L8("Time = ")) ;
			LogFile.Write(buf) ;
			LogFile.Write(_L8("\n") ) ;
			}
		else
			{
			LogFile.Write(_L8("Failed..\n ")) ;
			}
		
		CloseFile() ;
		return 0 ;
		}
	/* clean up of the maps that were constructed */


    



TInt SymPerformanceTestL()
	{
	
	}	// Symbyian call measurement function ends here



//E32Main() function
TInt E32Main()
	{
	//TInt ret1,ret2;
//	__UHEAP_MARK;
	CTrapCleanup* cleanup = CTrapCleanup::New();
	
	//MRT
 	TRAPD(error, SapiPerformanceTestL());
    __ASSERT_ALWAYS(!error, User::Panic(_L("SAPIcode PANIC"), error));
 
	
	//Symbian
 //   TRAPD(error1, SymPerformanceTestL());
 //   __ASSERT_ALWAYS(!error1, User::Panic(_L("SYMcode PANIC"), error1));
	
	
	//Destroy cleanup stack
	delete cleanup;
//	__UHEAP_MARKEND;
		
	return 0;

	} //E32main() function ends here

//  End of File
