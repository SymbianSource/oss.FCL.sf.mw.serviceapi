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
#include "getlocperf.h"

_LIT(LogFileName , "C:\\performance.txt") ;
RFile LogFile ;
RFs LogSession ;
TBuf8<50> buf ;
TRealFormat format ;
		
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
  
TInt SapiPerformanceTestL()
	{
  	
  	const char *serviceName   = "Service.Location" ;
	const char *interfaceName = "ILocation" ;

	void *interfacePtr = NULL ;  // handle for storing the interface instance
	
	GValue aMapId,aListId,aMapOut, Result ; // glib datatypes used for constructing maps,lists etc
	GValue resMap[3] ;
	int error = -1, err = 0 ;
	int cntMap = 0, aActualCount = 0 ;
	int returnStatus = 0 ;
	int cntLoop ;
	char key[3][20] ;
	
	double res[3] ;
	TTime start ; // TTime class objects for storing time
    TTime end ;	
    TTimeIntervalMicroSeconds aTimeTaken ; 
    TInt64 aTimeDelay, aSum = 0.0, aAvgTime = 0.0 ;	
	TBool aFlag  = EFalse ;
	
	OpenFile() ;
	LogFile.Write(_L8("<SAPI GetLocation PERFORMANCE DATA>\n ")) ;
	CloseFile() ;

//	for( i = 0; i<2; i++)
		{
		
		start.HomeTime() ;  //  Get the system time before invoking the service
		
		cbindingattach() ;
		
		/* Invoke the LoadService function */
		interfacePtr = loadservice(serviceName, interfaceName) ;

		/* check if the pointer is valid */
		if(interfacePtr == NULL)
			{
			return (-1) ;
			}


		/* construct the maps that are required by the request service */
		map_construct(&aMapId, G_TYPE_INT, "RequestType", 1, G_TYPE_INT, "RequestFormat", 1, G_TYPE_STRING, "RequestData", "Kasthuri",G_TYPE_INVALID) ;
		
		/* construct the lists that has a map arg */
		list_construct(&aListId, G_BINDING_DERIVED_TYPE_MAP, aMapId, G_TYPE_INVALID) ;

		/* Invoking the request service function */

		requestservice(interfacePtr, "SetIdentity", G_BINDING_DERIVED_TYPE_LIST, "RequestorIdentityList",aListId, G_TYPE_INVALID, &aMapOut, NULL, 0, &error) ;
		
		if( error == 0 )
			{
			requestservice(interfacePtr,"GetLocation", G_TYPE_INVALID, &aMapOut, NULL, 0, &error) ;
			getoutputatindex(aMapOut, &Result, 0) ;	
			cntMap = map_count(Result) ;
		
			for(cntLoop = 0; cntLoop<cntMap; cntLoop++)
				{
				memset(&resMap[cntLoop], 0, sizeof(GValue)) ;
					
				err = map_findkeyatindex(Result, cntLoop, key[cntLoop]) ;
				err = map_findvaluewithkey(Result, key[cntLoop], &resMap[cntLoop] ) ;
				
				getresult(resMap[cntLoop], G_TYPE_DOUBLE, &res[cntLoop]) ;
				}
			 }
		

		/* Get the system time after invoking the service */
		
		
		map_delete(aMapId) ;
		list_delete(aListId) ;
		map_delete(Result) ;
	//	map_delete(aMapOut) ;
		resetoutput(aMapOut) ;
		closeinterface(interfacePtr) ;
		
		unloadservice(serviceName, interfaceName) ;
		
		cbindingdetach();
		
	
		end.HomeTime();  
		
		/* Delay measured interms of microseconds */
		
		aTimeTaken = end.MicroSecondsFrom(start) ;  
		aTimeDelay = aTimeTaken.Int64() ;
		
		
		if( (-90<=res[0]<=90) && (-180<=res[1]<=180) && (res[2]) )
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
  	return 0 ;
	}  // Sapi call measurement function ends here
    



TInt SymPerformanceTestL()
	{
	RPositionServer aPosServer ;
	RPositioner aPositioner ;
	TPositionUpdateOptions aOptions ;
    TTimeIntervalMicroSeconds aTimeOut = 15000000 ;
    TPositionInfo aPosInfo ;
    TPosition aPosition ;
  	TInt aError  =KErrNone, aActualCount = 0 ;
	TTime start, end ;
	TTimeIntervalMicroSeconds aTimeTaken ;
	TInt64 aDelay, aSum = 0.0, aAvgTime = 0.0 ;
	TBool aFlag = EFalse ;
	TReal64 aLat, aLon, aAlt ;
	TRequestStatus aStatus ;

	OpenFile() ;
	LogFile.Write(_L8("<S60 GetLocation PERFORMANCE DATA>\n ")) ;
	CloseFile() ;

	_LIT(KIdentity,"Performance measure") ;
	
//	for( i =0; i<20; i++ )
		{
		start.HomeTime() ;
		
		aError = aPosServer.Connect() ;
	    User :: LeaveIfError(aError) ;
	    
	    // Open subsession to the position server
	    aError = aPositioner.Open(aPosServer) ;
		User :: LeaveIfError(aError) ;
		
		aError = aPositioner.SetRequestor(1,1,KIdentity) ;
		if( KErrNone == aError )
			{
			 aOptions.SetUpdateTimeOut(aTimeOut) ;
			 aPositioner.SetUpdateOptions(aOptions) ;
			 aPositioner.NotifyPositionUpdate(aPosInfo, aStatus) ;
	         User::WaitForRequest(aStatus) ;
	         
	         if( KErrNone == aStatus.Int() )
	         	{
	         	aPosInfo.GetPosition(aPosition) ;
	         	aLat = aPosition.Latitude() ;
	         	aLon = aPosition.Longitude() ;
	         	aAlt = aPosition.Altitude() ;
	         	}

			aPositioner.Close() ;
			aPosServer.Close() ;

			end.HomeTime();
			
			aTimeTaken = end.MicroSecondsFrom(start) ;
			aDelay = aTimeTaken.Int64() ;
			
			
			if( (-90<=aLat<=90) && (-180<=aLon<=180) && (aAlt) )
				{
				aFlag = ETrue ;
				aSum = aSum + aDelay ;
				aActualCount++ ;
				}
		
		/* Log the delay into a file and repeat the operation in a Loop */

			OpenFile();
		
			if( aFlag )
				{
				buf.Num(aDelay , format) ;
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
		
		}
		
	aAvgTime = aSum/aActualCount ;
	
	OpenFile() ;
	
	buf.Num(aAvgTime , format) ;
	LogFile.Write(_L8("\n\n Averavge = ")) ;
	LogFile.Write(buf) ;
	LogFile.Write(_L8("\n\n") ) ;
	
	CloseFile() ;
	
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
//    TRAPD(error1, SymPerformanceTestL());
//   __ASSERT_ALWAYS(!error1, User::Panic(_L("SYMcode PANIC"), error1));
	
	
	//Destroy cleanup stack
	delete cleanup;
//	__UHEAP_MARKEND;
		
	return 0;
	} //E32main() function ends here

//  End of File
