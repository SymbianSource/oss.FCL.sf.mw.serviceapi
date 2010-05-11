/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:   ?Description
*
*/




// INCLUDE FILES
#include "tloctest.h"

#include <e32svr.h>
#include <StifParser.h>
#include <StifTestInterface.h>
#include <AiwCommon.h>
#include <lbs.h>

const  TInt Ksecond = 1000000;

const TInt KUpdatetimeOut = 2*Ksecond ;
//Log file for math operation
_LIT(LogFileName , "C:\\mathlog.txt") ;
_LIT(KRequestor,"testapp");


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTLocTest::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTLocTest::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CTLocTest::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTLocTest::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "GetLocation",    CTLocTest::GetLocation ),
        ENTRY("LocationUpdates", CTLocTest :: LocationUpdates),
        ENTRY("CancelLocationUpdates1", CTLocTest :: CancelLocationUpdatesA),
        ENTRY("CancelLocationUpdates2", CTLocTest :: CancelLocationUpdatesB),
        ENTRY( "LastKnownLoc" ,  CTLocTest :: LastKnownLoc),
        ENTRY("FindDistance", CTLocTest :: FindDistance ),
        ENTRY("FindBearingTo", CTLocTest :: FindBearingTo ),
        ENTRY("MoveCoordinates",CTLocTest :: MoveCoordinates),
        ENTRY("GetLocationAsynch", CTLocTest :: GetLocationAsynch ),
        ENTRY("CancelLocationAsynch", CTLocTest :: CancelLocationAsynch ),
        ENTRY("StraySignal" , CTLocTest :: StraySignal),
        ENTRY("StraySignalGetLoc" , CTLocTest :: StraySignalGetLoc),
        ENTRY("ConcurrentCallsGetLoc" , CTLocTest:: ConcurrentCallsGetLoc),
        ENTRY("ConcurrentCallsTrace" , CTLocTest:: ConcurrentCallsTrace),
        ENTRY("EmptyCancelTrace" , CTLocTest:: EmptyCancelTrace),
            ENTRY("EmptyCancelLocAsynch" , CTLocTest:: EmptyCancelLocAsynch),
            ENTRY("TraceTimeOut" , CTLocTest:: TraceTimeOut)
        

        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CTLocTest::ExampleL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CTLocTest::GetLocation( CStifItemParser& /*aItem*/ )
    {

    // Print to UI
    __UHEAP_MARK ;
    _LIT( KTLocTest, "TLocTest" );
    _LIT( KExample, "GetLocation" );
    iLog->Log(KTLocTest) ;
   // iLog->Log(KExample) ;
    //TestModuleIf().Printf( 0, KTLocTest, KExample );
    // Print to log file
    
    TPositionInfo position;
    

    iLog->Log( KExample );
    CLocationService *CoreObj = CLocationService :: NewL();
    
    //not needed any more
    /*RRequestorStack infostack;
    
    const CRequestor* identityInfo = CRequestor::NewL(CRequestor::ERequestorService,CRequestor::EFormatApplication,
    												KRequestor) ;
    infostack.Append(identityInfo);
    CoreObj->SetRequestorIdentityL(infostack);*/
    
    
    
    TRAPD(Result,CoreObj->GetLocationL(&position)) ;
    TPosition pos ;
    
    position.GetPosition(pos) ;
    TReal64 aLatitude  = pos.Latitude();
    TReal64 aLongitude = pos.Longitude() ;
    TReal32 aAltitude  = pos.Altitude() ;
    delete CoreObj ;

    __UHEAP_MARKEND ;
    return Result ;

    }
 
   

            
//DummyCB MyUpdates             ;
//CGetLoc *Coreobj = NULL ;

            
TInt CTLocTest :: LocationUpdates(CStifItemParser& /*aItem*/)
	{
	_LIT(KTLocTest ,"TLocTest");
	iLog->Log(KTLocTest) ;
	
	TRequestStatus Status = KRequestPending  ;
	RThread FunctionThread ;
    
    TInt ret = FunctionThread.Create(_L(" LocationUpdates Thread") , GetLocUpdates ,KDefaultStackSize , 
    						KMinHeapSize , KDefaultStackSize ,(TAny *) NULL);
    						
    if(!ret)
	    {
	    FunctionThread.Logon(Status)	;
	    FunctionThread.Resume() ;
	    
	    User :: WaitForRequest (Status)	;				
	    FunctionThread.Close();

		ret = Status.Int() ;
	    }
	   return ret;
	}    

TInt CTLocTest :: LastKnownLoc(CStifItemParser& /*aItem*/)
	{
	_LIT(KTLocTest , "TLocTest") ;
	iLog->Log(KTLocTest) ;
    CLocationService *CoreObj = CLocationService :: NewL();
    TPosition LastKnownPos ;

    TInt err = CoreObj->GetLastKnownLoc(LastKnownPos) ;
    delete CoreObj;
    return err;
	}
	
	
TInt  CTLocTest ::GetLocationAsynch(CStifItemParser& /*aItem*/)
	{
	
		_LIT(KTLocTest ,"TLocTest");
	iLog->Log(KTLocTest) ;
	
	TRequestStatus Status = KRequestPending  ;
	RThread FunctionThread ;
    
    FunctionThread.Create(_L("GetLocationAsynch Thread") , FindLocationAsynch ,KDefaultStackSize , 
    						KMinHeapSize , KDefaultStackSize ,(TAny *) NULL);
    						
    FunctionThread.Logon(Status)	;
    FunctionThread.Resume() ;
    
    User :: WaitForRequest (Status)	;				
     FunctionThread.Close();

	return Status.Int() ;	
	
	
	}
	

	

	 
	
	
TInt CTLocTest :: FindDistance(CStifItemParser& /*aItem*/)
{
    __UHEAP_MARK ;
  		CLocationService *CoreObj = CLocationService :: NewL();
  
  
  		TReal32 distance;
  		TTime systemtime;
  		systemtime.HomeTime(); //for getting the system time
  		
  		
  		//scenarion 1: both input param are within the valid range
  		//coordinate1 =  ,coordinate2 = 
  		TCoordinate  cordinate1(22,88),cordinate2(13,77);
  		
  	
  
  		//preparing for input param
  		
  		inpparam input;
  		input.servicechoice = EDistance;
  		input.source = cordinate1;
  		input.destination = cordinate2;
  
  	
  	
        
  		 CoreObj->MathOperation(input) ;
  		
  	
  		distance = input.result;
  		
  		
  		//Logging result into a file
  		RFile LogFile ;
 		RFs LogSession ;
 		TBuf8<50> Buffer(_L8("Distance = ")) ;
 		LogSession.Connect() ;
 
 		if(LogFile.Open(LogSession ,LogFileName , EFileWrite | EFileShareAny )  == KErrNotFound)
 		{
  			LogFile.Create(LogSession ,LogFileName , EFileWrite | EFileShareAny ) ;
 	
 		}
 
 		TInt End = 0 ;
 
 		LogFile.Seek(ESeekEnd , End) ; //Seek to end of the file before writing 
 
 		TBuf8<50> num ;
 		TRealFormat format ;
 		//TReal64 Val = aPosition.Latitude() ;
 		num.Num(distance , format) ;

 		//Logging Latitude 
 		LogFile.Write(_L8("distance = "));
 		LogFile.Write(num) ;
 		LogFile.Write(_L8("\n")) ;
 		LogFile.Close() ;
 		LogSession.Close() ;
 		
 		//scenario 1 ends here 
 		
 		//scenario 2: longitude is out of range
 		
	TCoordinate  cordinate3(0,0,0),cordinate4(0,0,0);
  		
  		
  		//preparing for input param
  		
  		
  		input.servicechoice = EDistance;
  		input.source = cordinate3;
  		input.destination = cordinate4;
  
  		
  		
        
  	   CoreObj->MathOperation(input) ;
  		
  		
  		distance = input.result;
  		
  		
  		//Logging result into a file
  	
 		LogSession.Connect() ;
 
 		if(LogFile.Open(LogSession ,LogFileName , EFileWrite | EFileShareAny )  == KErrNotFound)
 		{
  			LogFile.Create(LogSession ,LogFileName , EFileWrite | EFileShareAny ) ;
 	
 		}
 
 	
 		LogFile.Seek(ESeekEnd , End) ; //Seek to end of the file before writing 
 
 
 		num.Num(distance , format) ;

 		//Logging Latitude 
 		LogFile.Write(_L8("distance(longitude out of range) = "));
 		LogFile.Write(num) ;
 		LogFile.Write(_L8("\n")) ;
 		LogFile.Close() ;
 		LogSession.Close() ;
 		//scenario 2: ends here
 		
 		//scenario 3: latitude is out of range
 			TCoordinate  cordinate5(91,172),cordinate6(94,145);
  		
  		
  
  		//preparing for input param
  		
  		
  		input.servicechoice = EDistance;
  		input.source = cordinate5;
  		input.destination = cordinate6;
  
  		
  		
  	
        
  	    CoreObj->MathOperation(input) ;
  		
  	
  		distance = input.result;
  		
  		
  		//Logging result into a file
  	
 		LogSession.Connect() ;
 
 		if(LogFile.Open(LogSession ,LogFileName , EFileWrite | EFileShareAny )  == KErrNotFound)
 		{
  			LogFile.Create(LogSession ,LogFileName , EFileWrite | EFileShareAny ) ;
 	
 		}
 
 	
 		LogFile.Seek(ESeekEnd , End) ; //Seek to end of the file before writing 
 
 
 		num.Num(distance , format) ;

 		//Logging Latitude 
 		LogFile.Write(_L8("distance(latitude out of range) = "));
 		LogFile.Write(num) ;
 		LogFile.Write(_L8("\n")) ;
 		LogFile.Close() ;
 		LogSession.Close() ;
 		
 		//scenario 3: ends here
 		
 		//scenario 4: both are out of range
 		TCoordinate  cordinate7(91,182),cordinate8(98,187);
  		
  		
  
  		//preparing for input param
  		
  		
  		input.servicechoice = EDistance;
  		input.source = cordinate7;
  		input.destination = cordinate8;
  
  		
  		
  	
        
  		 CoreObj->MathOperation(input) ;
  		
  		
     	distance = input.result;
  		
  		
  		//Logging result into a file
  	
 		LogSession.Connect() ;
 
 		if(LogFile.Open(LogSession ,LogFileName , EFileWrite | EFileShareAny )  == KErrNotFound)
 		{
  			LogFile.Create(LogSession ,LogFileName , EFileWrite | EFileShareAny ) ;
 	
 		}
 
 	
 		LogFile.Seek(ESeekEnd , End) ; //Seek to end of the file before writing 
 
 
 		num.Num(distance , format) ;

 		//Logging Latitude 
 		LogFile.Write(_L8("distance(both out of range) = "));
 		LogFile.Write(num) ;
 		LogFile.Write(_L8("\n")) ;
 		LogFile.Close() ;
 		LogSession.Close() ;
 		
 		
 		
 		//scenario 4: ends here
 		
  		
  		delete CoreObj;
    __UHEAP_MARKEND ;
  		return KErrNone ;
}
  
/** Manual test case for findbearingto
 */
TInt CTLocTest :: FindBearingTo(CStifItemParser& /*aItem*/)  
	{
    __UHEAP_MARK ;
	CLocationService *CoreObj = CLocationService :: NewL();


	TReal32 bearingTo;
	
	
	//scenarion 1: both input param are within the valid range
	//coordinate1 =  ,coordinate2 = 
	TCoordinate  cordinate1(22,88),cordinate2(13,77);
	
	

	//preparing for input param
	
	inpparam input;
	input.servicechoice = EBearingTo;
	input.source = cordinate1;
	input.destination = cordinate2;



    
	 CoreObj->MathOperation(input) ;
	

	bearingTo = input.result;
	
	
	//Logging result into a file
	RFile LogFile ;
	RFs LogSession ;
	TBuf8<50> Buffer(_L8("Bearing = ")) ;
	LogSession.Connect() ;

	if(LogFile.Open(LogSession ,LogFileName , EFileWrite | EFileShareAny )  == KErrNotFound)
	{
		LogFile.Create(LogSession ,LogFileName , EFileWrite | EFileShareAny ) ;

	}

	TInt End = 0 ;

	LogFile.Seek(ESeekEnd , End) ; //Seek to end of the file before writing 

	TBuf8<50> num ;
	TRealFormat format ;

	num.Num(bearingTo, format) ;

	//Logging 
	LogFile.Write(_L8("Bearing = "));
	LogFile.Write(num) ;
	LogFile.Write(_L8("\n")) ;
	LogFile.Close() ;
	LogSession.Close() ;
	
	//scenario 1 ends here 
	
	//scenario 2: 
	
	TCoordinate  cordinate3(0,0,0),cordinate4(0,0,0);
	
	
	//preparing for input param
	
	
	input.servicechoice = EBearingTo;
	input.source = cordinate3;
	input.destination = cordinate4;

	
	
    
    CoreObj->MathOperation(input) ;
	
	
	bearingTo = input.result;
	
	
	//Logging result into a file

	LogSession.Connect() ;

	if(LogFile.Open(LogSession ,LogFileName , EFileWrite | EFileShareAny )  == KErrNotFound)
	{
		LogFile.Create(LogSession ,LogFileName , EFileWrite | EFileShareAny ) ;

	}


	LogFile.Seek(ESeekEnd , End) ; //Seek to end of the file before writing 


	num.Num(bearingTo , format) ;

	//Logging 
	LogFile.Write(_L8("Bearing= "));
	LogFile.Write(num) ;
	LogFile.Write(_L8("\n")) ;
	LogFile.Close() ;
	LogSession.Close() ;
	//scenario 2: ends here
	
	//scenario 3: latitude is out of range
		TCoordinate  cordinate5(91,172),cordinate6(94,145);
	
	

	//preparing for input param
	
	
	input.servicechoice = EBearingTo;
	input.source = cordinate5;
	input.destination = cordinate6;

	
	

    
    CoreObj->MathOperation(input) ;
	

	bearingTo = input.result;
	
	
	//Logging result into a file

	LogSession.Connect() ;

	if(LogFile.Open(LogSession ,LogFileName , EFileWrite | EFileShareAny )  == KErrNotFound)
	{
		LogFile.Create(LogSession ,LogFileName , EFileWrite | EFileShareAny ) ;

	}


	LogFile.Seek(ESeekEnd , End) ; //Seek to end of the file before writing 


	num.Num(bearingTo , format) ;

	//Logging Latitude 
	LogFile.Write(_L8("Bearing(latitude out of range) = "));
	LogFile.Write(num) ;
	LogFile.Write(_L8("\n")) ;
	LogFile.Close() ;
	LogSession.Close() ;
	
	//scenario 3: ends here
	
	//scenario 4: both are out of range
	TCoordinate  cordinate7(91,182),cordinate8(98,187);
	
	

	//preparing for input param
	
	
	input.servicechoice = EBearingTo;
	input.source = cordinate7;
	input.destination = cordinate8;

	
	

    
	 CoreObj->MathOperation(input) ;
	
	
 	 bearingTo= input.result;
	
	
	//Logging result into a file

	LogSession.Connect() ;

	if(LogFile.Open(LogSession ,LogFileName , EFileWrite | EFileShareAny )  == KErrNotFound)
	{
		LogFile.Create(LogSession ,LogFileName , EFileWrite | EFileShareAny ) ;

	}


	LogFile.Seek(ESeekEnd , End) ; //Seek to end of the file before writing 


	num.Num(bearingTo , format) ;

	//Logging Latitude 
	LogFile.Write(_L8("Bearing(both out of range) = "));
	LogFile.Write(num) ;
	LogFile.Write(_L8("\n")) ;
	LogFile.Close() ;
	LogSession.Close() ;
	
	
	
	//scenario 4: ends here
	
	
	delete CoreObj;
    __UHEAP_MARKEND ;
	return KErrNone ;	
	}



/**
 * Manual test case for MathOperation Move
 */
 TInt CTLocTest :: MoveCoordinates(CStifItemParser& /*aItem*/)  
	{
    __UHEAP_MARK ;
	CLocationService *CoreObj = CLocationService :: NewL();


	
	
	
	
	TCoordinate  cordinate1(22,88);
	
	

	//preparing for input param
	
	inpparam input;
	input.servicechoice = EMove;
	input.source = cordinate1;
	input.bearing = 34;
	input.distance  = 234;
	



    
	 CoreObj->MathOperation(input) ;
	 TReal64 latitudeval = input.source.Latitude();
	 TReal64 longitudeval = input.source.Longitude();
	 
	 TReal64 altitudeval = input.source.Altitude();
	 
	 
	

	
	
	
	//Logging result into a file
	RFile LogFile ;
	RFs LogSession ;
	TBuf8<50> Buffer(_L8("Longitude = ")) ;
	LogSession.Connect() ;

	if(LogFile.Open(LogSession ,LogFileName , EFileWrite | EFileShareAny )  == KErrNotFound)
		{
		LogFile.Create(LogSession ,LogFileName , EFileWrite | EFileShareAny ) ;

		}

	TInt End = 0 ;

	LogFile.Seek(ESeekEnd , End) ; //Seek to end of the file before writing 

	TBuf8<50> num ;
	TRealFormat format ;

	num.Num(longitudeval, format) ;

	//Logging 
	LogFile.Write(_L8("Longitude = "));
	LogFile.Write(num) ;
	LogFile.Write(_L8("\n")) ;
	//LogFile.Seek(ESeekEnd , End) ;
	num.Num(latitudeval, format) ;
	LogFile.Write(_L8("Latitude = "));
	LogFile.Write(num) ;
	LogFile.Write(_L8("\n")) ;
	num.Num(altitudeval, format) ;
	LogFile.Write(_L8("altitude = "));
	LogFile.Write(num) ;
	LogFile.Write(_L8("\n")) ;
	
	
	LogFile.Close() ;
	LogSession.Close() ;
	delete CoreObj;
    __UHEAP_MARKEND ;
	return KErrNone ;
	}
/*
 * This is a manual test case were the service was available when the 
 * request was made and then   Lost the service (Contact to location servier lost
 */
 
  


/**
 *Stray signal test, tests for any unhandled events from location server
 */

TInt CTLocTest :: StraySignal(CStifItemParser& /*aItem*/)
{
	_LIT(KTLocTest ,"TLocTest");
	iLog->Log(KTLocTest) ;
	_LIT(KLog , "StraySignalTest ") ;
	iLog->Log(KTLocTest) ;
	
	TRequestStatus Status = KRequestPending  ;
	RThread FunctionThread ;
    
    TInt ret =  FunctionThread.Create(_L("stray signal") , StrayTest ,KDefaultStackSize , 
    						KMinHeapSize , KDefaultStackSize ,(TAny *) NULL);;
    						
    if(!ret)
	    {
	    
	    _LIT(Klog , "Created the thread ") ;
	    iLog->Log(Klog) ;
	    FunctionThread.Logon(Status)	;
	    FunctionThread.Resume() ;
	    
	    User :: WaitForRequest (Status)	;				
	    FunctionThread.Close();

		ret = Status.Int() ;
	    }
	   
	   return ret;	
}

TInt CTLocTest :: StraySignalGetLoc(CStifItemParser& /*aItem*/)
{
	_LIT(KTLocTest ,"TLocTest");
	iLog->Log(KTLocTest) ;
	_LIT(KLog , "StraySignalTestGetLoc ") ;
	iLog->Log(KTLocTest) ;
	
	TRequestStatus Status = KRequestPending  ;
	RThread FunctionThread ;
    
    TInt ret =  FunctionThread.Create(_L("stray signal GetLocation") , StrayTestGetLoc ,KDefaultStackSize , 
    						KMinHeapSize , KDefaultStackSize ,(TAny *) NULL);;
    						
    if(!ret)
	    {
	    
	    _LIT(Klog , "thread created ") ;
	    iLog->Log(Klog) ;
	    FunctionThread.Logon(Status)	;
	    FunctionThread.Resume() ;
	    
	    User :: WaitForRequest (Status)	;				
	    FunctionThread.Close();

		ret = Status.Int() ;
	    }
	    
		
	   return ret;	
}

TInt CTLocTest :: EmptyCancelTrace(CStifItemParser& /*aItem*/)
{
	/*_LIT(KTLocTest ,"TLocTest");
	iLog->Log(KTLocTest) ;
	_LIT(KLog , "EmptyCanceltest ") ;
	iLog->Log(KTLocTest) ;*/
    __UHEAP_MARK ;
	CLocationService *CoreObj = CLocationService ::NewL() ;
	//not needed any more
	/*RRequestorStack infostack;
    
    const CRequestor* identityInfo = CRequestor::NewL(CRequestor::ERequestorService,CRequestor::EFormatApplication,
    												KRequestor) ;
    infostack.Append(identityInfo);
    CoreObj->SetRequestorIdentityL(infostack);*/
    TInt error= CoreObj->CancelOnGoingService(ECancelTrace);
    if( error==KErrNotFound ) 
    {
    delete CoreObj;
        __UHEAP_MARKEND ;
    return KErrNone;	
    }
    
    delete CoreObj;
    __UHEAP_MARKEND ;
    return error;
}

TInt CTLocTest :: EmptyCancelLocAsynch(CStifItemParser& /*aItem*/)
{
	_LIT(KTLocTest ,"TLocTest");
	iLog->Log(KTLocTest) ;
	_LIT(KLog , "EmptyCanceltest ") ;
	iLog->Log(KTLocTest) ;
	
	CLocationService *CoreObj = CLocationService ::NewL() ;
	//not needed any more
	/*RRequestorStack infostack;
    
    const CRequestor* identityInfo = CRequestor::NewL(CRequestor::ERequestorService,CRequestor::EFormatApplication,
    												KRequestor) ;
    infostack.Append(identityInfo);
    CoreObj->SetRequestorIdentityL(infostack);*/
    TInt error= CoreObj->CancelOnGoingService(ECancelGetLocation);
    if( error==KErrNotFound ) 
    {
    delete CoreObj;
    return KErrNone;	
    }
    
    delete CoreObj;
    return KErrGeneral;
}


TInt CTLocTest :: TraceTimeOut(CStifItemParser& /*aItem*/)
    {
    _LIT(KTLocTest ,"TLocTest");
    iLog->Log(KTLocTest) ;
    _LIT(KLog , "TraceTimeOut ") ;
    iLog->Log(KTLocTest) ;

    TRequestStatus Status = KRequestPending  ;
    RThread FunctionThread ;

    TInt ret =  FunctionThread.Create(_L("TraceTimeOut Test") , TraceTimeOutFunc ,KDefaultStackSize , 
            KMinHeapSize , 0x5000 ,(TAny *) NULL);;

            if(!ret)
                {

                _LIT(Klog , "thread created ") ;
                iLog->Log(Klog) ;
                FunctionThread.Logon(Status)    ;
                FunctionThread.Resume() ;

                User :: WaitForRequest (Status) ;               
                FunctionThread.Close();

                ret = Status.Int() ;
                }


            return ret;  
    }


TInt CTLocTest:: ConcurrentCallsGetLoc(CStifItemParser& /*aItem*/)
    {
    _LIT(KTLocTest ,"TLocTest");
    iLog->Log(KTLocTest) ;

    TRequestStatus Status = KRequestPending  ;
    RThread FunctionThread ;

    TInt ret = FunctionThread.Create(_L(" ConcurrentCallsGetLoc Thread") , ConcurrentGetLocationCalls ,KDefaultStackSize , 
            KMinHeapSize , 0x5000 ,(TAny *) NULL);

    if(ret == KErrNone)
        {
        FunctionThread.Logon(Status)    ;
        FunctionThread.Resume() ;

        User :: WaitForRequest (Status) ;               


        ret = Status.Int() ;
        }
    FunctionThread.Close();  


    return ret;  
    }


TInt CTLocTest:: ConcurrentCallsTrace(CStifItemParser& /*aItem*/)
    {
    _LIT(KTLocTest ,"TLocTest");
    iLog->Log(KTLocTest) ;

    TRequestStatus Status = KRequestPending  ;
    RThread FunctionThread ;

    TInt ret = FunctionThread.Create(_L(" ConcurrentCallsGetLoc Thread") , ConcurrentTraceCalls ,KDefaultStackSize , 
            KMinHeapSize , 0x5000 ,(TAny *) NULL);

    if(ret == KErrNone)
        {
        FunctionThread.Logon(Status)    ;
        FunctionThread.Resume() ;

        User :: WaitForRequest (Status) ;               


        ret = Status.Int() ;
        }
    FunctionThread.Close();  


    return ret;  
    }
