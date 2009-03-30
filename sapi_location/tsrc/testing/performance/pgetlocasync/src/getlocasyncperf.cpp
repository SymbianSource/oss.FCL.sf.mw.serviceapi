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
* Description:   getlocperf async performance test
*                (a) getlocationasync
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
#include "getlocasyncperf.h"

_LIT(LogFileName , "C:\\Noti_async.txt") ;
RFile LogFile ;
RFs LogSession ;
TBuf8<50> buf ;
TRealFormat format ;
//double res[3] ;
TTime start ; // TTime class objects for storing time
TTime end ;	
TTimeIntervalMicroSeconds aTimeTaken ; 
sem_t mySemaphore = NULL; 
		
void OpenFile()
	{
	LogSession.Connect() ;

	if(LogFile.Open(LogSession ,LogFileName , EFileWrite | EFileShareAny )  == KErrNotFound)
		{
		LogFile.Create(LogSession ,LogFileName , EFileWrite | EFileShareAny ) ;
		}

	TInt End = 0 ;
	LogFile.Seek(ESeekEnd , End) ; 
	}

void CloseFile()
	{
	LogFile.Close() ;
	LogSession.Close() ;
	}
  
void MycallBack( GValue* aValue )
	{
	GValue resMap[3], aMapOut ;
	GType type ;
	int mCount ;
	char key[3][20];
	double res[3] ;
	int i;
	mCount = getoutputcount(*aValue);
	type = getoutputatindex(*aValue, &aMapOut, 0);		
	mCount= map_count(aMapOut);
	OpenFile() ;
	LogFile.Write(_L8("<inside callback>\n ")) ;
	CloseFile() ;

	for(i=0; i<mCount; i++)
		{
		memset(&resMap[i], 0, sizeof(GValue));
		res[i] = 0.0;
		
		 map_findkeyatindex(aMapOut, i, key[i]);
		 map_findvaluewithkey(aMapOut, key[i], &resMap[i] );
		
		 getresult(resMap[i], G_TYPE_DOUBLE, &res[i]);
		 printf("%f", res[i]) ;		
		}	
	getchar() ;
    resetoutput(*aValue) ;
    map_delete(aMapOut) ;
    	
	pthread_t tId1 = pthread_self();	
	stopscheduler(tId1);
	
	sem_post(&mySemaphore);
	 	
	}

void* sapiperformancetestL(void* )
	{
  	
  	const char *serviceName   = "Service.Location" ;
	const char *interfaceName = "ILocation" ;

	void *interfacePtr = NULL ;  // handle for storing the interface instance
	
	GValue aMapId,aListId,aMapOut ; // glib datatypes used for constructing maps,lists etc
	TInt error = -1 ;/*, err = 0*/ 
	TInt /*cntMap = 0,*/ aActualCount = 0 ;
//	TInt returnStatus = 0 ;
	
	
/*	TTime start ; // TTime class objects for storing time
    TTime end ;	
    TTimeIntervalMicroSeconds aTimeTaken ; 
 */  TInt64 aTimeDelay, aSum = 0.0, aAvgTime = 0.0 ;	
	TBool aFlag  = EFalse ;
	
	OpenFile() ;
	LogFile.Write(_L8("<SAPI GetLocation Async PERFORMANCE DATA>\n ")) ;
	CloseFile() ;

//	for( i = 0; i<100; i++)
		{
		
		start.HomeTime() ;  //  Get the system time before invoking the service
		
		cbindingattach() ;
		
		/* Invoke the LoadService function */
		interfacePtr = loadservice(serviceName, interfaceName) ;

		/* check if the pointer is valid */
		if(interfacePtr == NULL)
			{
			exit(-1) ;
			}


		/* construct the maps that are required by the request service */
		map_construct(&aMapId, G_TYPE_INT, "RequestType", 1, G_TYPE_INT, "RequestFormat", 1, G_BINDING_DERIVED_TYPE_UNICODE, "RequestData", L"Kasthuri",G_TYPE_INVALID) ;
		
		/* construct the lists that has a map arg */
		list_construct(&aListId, G_BINDING_DERIVED_TYPE_MAP, aMapId, G_TYPE_INVALID) ;

		/* Invoking the request service function */

		requestservice(interfacePtr, "SetIdentity", G_BINDING_DERIVED_TYPE_LIST, "RequestorIdentityList",aListId, G_TYPE_INVALID, &aMapOut, NULL, 0, &error) ;
		
		if( error == 0 )
			{
					
			pthread_t tId =pthread_self();
			
			createnewscheduler(tId);
			
			requestservice(interfacePtr,"GetLocation", G_TYPE_INVALID, &aMapOut, MycallBack, 0, &error) ;
			
			if( error == 0)
				{
				startscheduler(tId);
				if(sem_wait(&mySemaphore))
					{
					}
					
					map_delete(aMapId) ;
					list_delete(aListId) ;
					map_delete(aMapOut) ;
			
					closeinterface(interfacePtr) ;
			
					unloadservice(serviceName, interfaceName) ;
			
					cbindingdetach();
			
		
					end.HomeTime();  
					
				}
			 }

		/* Get the system time after invoking the service */
		
		
		
		/* Delay measured interms of microseconds */
		
		aTimeTaken = end.MicroSecondsFrom(start) ;  
		aTimeDelay = aTimeTaken.Int64() ;
			
//		if( (-90<=res[0]<=90) && (-180<=res[1]<=180) && (res[2]) )
			{
			aFlag = ETrue ;
			aSum = aSum + aTimeDelay ;
			aActualCount++ ;
			}
		/* Log the delay into a file and repeat the operation in a Loop */

		OpenFile();
		
		if( aFlag )
			{
			buf.Num(aTimeDelay , format) ;
			LogFile.Write(_L8("Time = ")) ;
			LogFile.Write(buf) ;
			LogFile.Write(_L8("\n") ) ;
			}
		else
			{
			LogFile.Write(_L8("Failed..\n ")) ;
			}
		
		CloseFile() ;
		}
	/* clean up of the maps that were constructed */

	aAvgTime = aSum/aActualCount ;
	
	OpenFile() ;
	
	buf.Num(aAvgTime , format) ;
	LogFile.Write(_L8("\n\nAverage = ")) ;
	LogFile.Write(buf) ;
	LogFile.Write(_L8("\n\n") ) ;
	
	CloseFile() ;		
  	}  // Sapi call measurement function ends here
    
TInt SapiPerformanceTestL()

	{
	pthread_t aThreads ;
	TInt aRet ;
	
	if(sem_init(&mySemaphore,0,0)<0)
		{
		exit(-1);
		}
	
	aRet = pthread_create(&aThreads, NULL, sapiperformancetestL,NULL);
	
	if (aRet)
		{
	   	exit(-1);
	  	}
	 else
	 	{
	 	aRet = pthread_join(aThreads,NULL);	
	 	}   
	    
	return 0 ;
	
	}

TInt SymPerformanceTestL()
	{
	
	TPositionUpdateOptions aOptions ;
    TTimeIntervalMicroSeconds aTimeOut = 15000000 ;
	RRequestorStack aRequestorStack;
	TInt aError, aActualCount = 0 ;
	TBool aFlag = EFalse ;
	TInt64 aTimeDelay, aSum = 0.0, aAvgTime = 0.0 ;
	
	_LIT(Kidentity ,"Performance" ) ;
	
	start.HomeTime() ;
	
	CActiveScheduler *mySched=new (ELeave) CActiveScheduler;
	CActiveScheduler::Install(mySched);

	

	const CRequestor* identityInfo = CRequestor::NewL(1 , 1 , Kidentity) ;
    
    
    aRequestorStack.Insert(identityInfo,0);
	aOptions.SetUpdateTimeOut(aTimeOut) ;
	
	CMyActiveObj* obj = CMyActiveObj :: NewL() ;
	
	aError = obj->MyAsyncInvoc(aRequestorStack,aOptions) ;
	
	if(KErrNone == aError)
		{
		CActiveScheduler::Start() ;
		end.HomeTime() ;
		}
		
		aTimeTaken = end.MicroSecondsFrom(start) ;  
		aTimeDelay = aTimeTaken.Int64() ;
		
		
		if( (-90<=obj->iLatitude<=90) && (-180<=obj->iLongitude<=180) && (obj->iAltitude) )
			{
			aFlag = ETrue ;
			aSum = aSum + aTimeDelay ;
			aActualCount++ ;
			}
		/* Log the delay into a file and repeat the operation in a Loop */

		OpenFile();
		
		if( aFlag )
			{
			buf.Num(aTimeDelay , format) ;
			LogFile.Write(_L8("Time = ")) ;
			LogFile.Write(buf) ;
			LogFile.Write(_L8("\n") ) ;
			}
		else
			{
			LogFile.Write(_L8("Failed..\n ")) ;
			}
		
		CloseFile() ;
		/* clean up of the maps that were constructed */

	aAvgTime = aSum/aActualCount ;
	
	OpenFile() ;
	
	buf.Num(aAvgTime , format) ;
	LogFile.Write(_L8("\n\nAverage = ")) ;
	LogFile.Write(buf) ;
	LogFile.Write(_L8("\n\n") ) ;
	
	CloseFile() ;			
	aRequestorStack.Close();
	delete identityInfo;
	return 0 ;
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
 
//  TRAPD(error1, SymPerformanceTestL());
//   __ASSERT_ALWAYS(!error1, User::Panic(_L("SYMcode PANIC"), error1));
	
	
	//Destroy cleanup stack
	delete cleanup;
//	__UHEAP_MARKEND;
		
	return 0;
	} //E32main() function ends here

//  End of File
