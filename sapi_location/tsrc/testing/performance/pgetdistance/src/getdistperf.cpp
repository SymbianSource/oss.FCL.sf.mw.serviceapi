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
* Description:   mathopperf performance test
*                (a) math operation
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
#include "getdistperf.h"

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
	
	GValue aMapId,aListId,aMapOut[2] ;	
	GValue aSource, aDestination, aDist ;
	GValue resMap[3] ; // glib datatypes used for constructing maps,lists etc
	GValue output[2] ;
	GValue result ;
	char key[3][20] ;
	double res[2][3] ;
	int error = -1, err = 0 ;
	int j, aActCount = 0, cntMap = 0 ;
	int returnStatus = 0, cntLoop ; 
	double aDistance = 0.0 ;
	TTime start ; // TTime class objects for storing time
    TTime end ;	
    TTimeIntervalMicroSeconds aTimeTaken ; 
    TInt64 aTimeDelay, aSum = 0.0, aAvgTime = 0.0 ;	
	TBool aFlag  = EFalse ;
	
	OpenFile() ;
	LogFile.Write(_L8("<SAPI Get Distance PERFORMANCE DATA>\n ")) ;
	CloseFile() ;

//	for( i = 0; i<3; i++ )
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
		
		map_construct(&aMapId, G_TYPE_INT, "RequestType", 1, G_TYPE_INT, "RequestFormat", 1, G_TYPE_STRING, "RequestData", "Kasthuri",G_TYPE_INVALID) ;
		
		/* construct the lists that has a map arg */
		list_construct(&aListId, G_BINDING_DERIVED_TYPE_MAP, aMapId, G_TYPE_INVALID) ;

		/* Invoking the request service function */

		requestservice(interfacePtr, "SetIdentity", G_BINDING_DERIVED_TYPE_LIST, "RequestorIdentityList",aListId, G_TYPE_INVALID, &aMapOut[0], NULL, 0, &error) ;
		
		if( error == 0 )
			{
			for( j=0; j<2; j++)
			{
				requestservice(interfacePtr,"GetLocation", G_TYPE_INVALID, &aMapOut[j], NULL, 0, &error) ;
				getoutputatindex(aMapOut[j], &output[j], 0) ;	
				cntMap = map_count(output[j]) ;
		
				for( cntLoop = 0; cntLoop<cntMap; cntLoop++ )
					{
					memset(&resMap[cntLoop], 0, sizeof(GValue)) ;
					
					err = map_findkeyatindex(output[j], cntLoop, key[cntLoop]) ;
					err = map_findvaluewithkey(output[j], key[cntLoop], &resMap[cntLoop] ) ;
					
					getresult(resMap[cntLoop], G_TYPE_DOUBLE, &res[j][cntLoop]) ;
					}
			 }

		/* construct the maps that are required by the request service */
		map_construct(&aSource, G_TYPE_DOUBLE, "Longitude", res[0][0], G_TYPE_DOUBLE, "Latitude", res[0][1], G_TYPE_DOUBLE, "Altitude", res[0][2], G_TYPE_INVALID) ;
		map_construct(&aDestination, G_TYPE_DOUBLE, "Longitude", res[1][0], G_TYPE_DOUBLE, "Latitude", res[1][1], G_TYPE_DOUBLE, "Altitude", res[1][2], G_TYPE_INVALID) ;

		/* Invoking the request service function */

		requestservice(interfacePtr, "Calculate", G_TYPE_STRING, "MathRequest", "FindDistance", 
						G_BINDING_DERIVED_TYPE_MAP, "DistanceParamSource", aSource, 
						G_BINDING_DERIVED_TYPE_MAP, "DistanceParamDestination", aDestination, 
						G_TYPE_INVALID,  &aDist, NULL, 0, &error) ;
		
		if( error == 0 )
			{
			getoutputatindex(aDist, &result, 0) ;
			getresult(result, G_TYPE_DOUBLE, &aDistance);
            }
		

		/* Get the system time after invoking the service */
		
		map_delete(aSource) ;
		map_delete(aDestination) ;
	//	map_delete(aDist) ;
		
		map_delete(aMapId) ;
		list_delete(aListId) ;
		map_delete(output[0]) ;
		map_delete(output[1]) ;
		
		resetoutput(aDist) ;
		resetoutput(aMapOut[0]) ;
		resetoutput(aMapOut[1]) ;
		closeinterface(interfacePtr) ;
		
		unloadservice(serviceName, interfaceName) ;
		
		cbindingdetach();
				
		end.HomeTime();  
		
		/* Delay measured interms of microseconds */
		
		aTimeTaken = end.MicroSecondsFrom(start) ;  
		aTimeDelay = aTimeTaken.Int64() ;
		
	
		if( aDistance >= 0 )
			{
			aFlag = ETrue ;
			aSum = aSum + aTimeDelay ;
            aActCount++ ; 
			}
		/* Log the delay into a file and repeat the operation in a Loop */

		OpenFile() ;
		
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
		}
	/* clean up of the maps that were constructed */

	aAvgTime = aSum/aActCount ;
	
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
    TPositionInfo aPosInfo[2] ;
    TPosition aPosition[2] ;
    TPositionUpdateOptions aOptions ;
    TTimeIntervalMicroSeconds aTimeOut = 15000000 ;
  	TCoordinate aSource, aDestination ;
  	TInt j, aError  =KErrNone, aActCount = 0 ;
	TTime start, end ;
	TTimeIntervalMicroSeconds aTimeTaken ;
	TInt64 aDelay, aSum = 0.0, aAvgTime = 0.0 ;
	TBool aFlag = EFalse ;
	TReal64 aLat[2], aLon[2] ;
	TReal32 aAlt[2] ;
    TReal32 aDistance ;
    TRequestStatus aStatus ;
    
	OpenFile() ;
	LogFile.Write(_L8("<S60 GetDistance PERFORMANCE DATA>\n ")) ;
	CloseFile() ;

	_LIT(KIdentity,"Performance measure") ;
	
//	for( i =0; i<10; i++ )
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
			 for( j=0; j<2; j++ )
				 {
				 aPositioner.NotifyPositionUpdate(aPosInfo[j], aStatus) ;
		         User::WaitForRequest(aStatus) ;
		         
		         if( KErrNone == aStatus.Int() )
		         	{
		         	aPosInfo[j].GetPosition(aPosition[j]) ;
		         	aLat[j] = aPosition[j].Latitude() ;
		         	aLon[j] = aPosition[j].Longitude() ;
		         	aAlt[j] = aPosition[j].Altitude() ;
		         	}	
				 }
			aPositioner.Close() ;
			aPosServer.Close() ;
			aSource.SetCoordinate(aLat[0], aLon[0], aAlt[0]) ;
			aDestination.SetCoordinate(aLat[1], aLon[1], aAlt[1]) ;
		
			aSource.Distance(aDestination, aDistance) ;

			end.HomeTime();
			
			aTimeTaken = end.MicroSecondsFrom(start) ;
			aDelay = aTimeTaken.Int64() ;
			
			
			if( aDistance>=0 )
				{
				aFlag = ETrue ;
				aSum = aSum + aDelay ;
	            aActCount++ ;
				}
			}
			/* Log the delay into a file and repeat the operation in a Loop */

			aAvgTime = aSum/aActCount ;
			
			OpenFile() ;
		
			if( aFlag )
				{
				buf.Num(aAvgTime , format) ;
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
		
	aAvgTime = aSum/aActCount ;
	
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
//  __UHEAP_MARK;
	CTrapCleanup* cleanup = CTrapCleanup::New();
	
	//MRT
	TRAPD(error, SapiPerformanceTestL());
   __ASSERT_ALWAYS(!error, User::Panic(_L("SAPIcode PANIC"), error));
 
	
	//Symbian
 //  TRAPD(error1, SymPerformanceTestL());
 //  __ASSERT_ALWAYS(!error1, User::Panic(_L("SYMcode PANIC"), error1));
	
	
	//Destroy cleanup stack
	delete cleanup;
//	__UHEAP_MARKEND;
		
	return 0;
	} //E32main() function ends here

//  End of File
