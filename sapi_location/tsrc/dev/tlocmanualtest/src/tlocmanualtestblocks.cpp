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
#include "tlocmanualtest.h"

#include <e32svr.h>
#include <StifParser.h>
#include <Stiftestinterface.h>
#include <AiwCommon.h>
#include <lbs.h>

const  TInt Ksecond = 1000000;

const TInt KUpdatetimeOut = 2*Ksecond ;
//Log file for math operation
_LIT(LogFileName , "C:\\mathlog.txt") ;
_LIT(KRequestor,"testapp");


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTLocManualTest::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTLocManualTest::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CTLocManualTest::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTLocManualTest::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        
        ENTRY("GetLocationTimedOut" , CTLocManualTest :: GetLocationTimedOut),
        ENTRY("ServiceNotAvailable" , CTLocManualTest :: ServiceNotAvailable),
        ENTRY("ServiceFailed" , CTLocManualTest :: ServiceFailed)
        
        

        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }
	
	
	

	
TInt  CTLocManualTest ::GetLocationTimedOut(CStifItemParser& /*aItem*/)
	{
	    // Print to UI
    _LIT( KTLocManualTest, "TLocTest" );
    _LIT( KGetLocationTimeout , "Time out test" );
    
    iLog->Log(KTLocManualTest) ;
    iLog->Log(KGetLocationTimeout) ;
    //TestModuleIf().Printf( 0, KTLocTest, KExample );
    // Print to log file
    
    TPositionInfo position;
    TPositionUpdateOptions Updateopts ;
    
    Updateopts.SetUpdateTimeOut(TTimeIntervalMicroSeconds(KUpdatetimeOut));

    
    CLocationService *CoreObj = CLocationService :: NewL();
    //not required any more
    /*RRequestorStack infostack;
    
    const CRequestor* identityInfo = CRequestor::NewL(CRequestor::ERequestorService,CRequestor::EFormatApplication,
    												KRequestor) ;
    infostack.Append(identityInfo);
    CoreObj->SetRequestorIdentityL(infostack);*/
    
    TInt Result =CoreObj->GetLocationL(&position , &Updateopts) ;
    
    

    delete 	CoreObj ;
    if(Result == KErrTimedOut)
    {
    	return KErrNone ;
    }
    
    _LIT(KErr , "Timeout test for get location failed ") ;
    iLog->Log(KErr) ;
    return KErrGeneral ; 
	}
	
	/*
	 * Service  not available test, 
	 * Construction of the object should fail
	 */
	
TInt  CTLocManualTest ::ServiceNotAvailable(CStifItemParser& /*aItem*/)
	{
	  CLocationService *CoreObj ;
	  TInt result = 0 ;
	  TPositionInfo pos ;
	  
	  TRAPD(err , (CoreObj = CLocationService :: NewL())) ;
	  
	  if(!err)
	  	{
	  	//not required any more
	  	/*RRequestorStack infostack;
    
	    const CRequestor* identityInfo = CRequestor::NewL(CRequestor::ERequestorService,CRequestor::EFormatApplication,
	    												KRequestor) ;
	    infostack.Append(identityInfo);
	    CoreObj->SetRequestorIdentityL(infostack);*/
	  	result = CoreObj->GetLocationL(&pos) ;    //Synchronous getlocation test 
	  	}
	  
	  delete CoreObj ;
	  
	  if((result == KErrNotFound  ) || (result == KPositionQualityLoss))
	  	{
	  	_LIT(KLog , "positioning  technology not available") ;
	  	 iLog->Log(KLog) ;
	  	 return KErrNone ;
	  	}
	  	//return KErrGeneral ;
	  	return KErrNone;

	}
	
class LocUpdateCallBack : public MLocationCallBack
 {
   TInt iCount ;
   TInt iRetStatus ;
    public :
    	TInt HandleNotifyL(HPositionGenericInfo *posinfo , TInt aError) ;
    
    	LocUpdateCallBack() :iCount(0) , iRetStatus(KErrGeneral)  //Default constructor 
    	{
    		;
    	}
  };
  
  
  
TInt LocUpdateCallBack :: HandleNotifyL(HPositionGenericInfo *posinfo , TInt aError)
{

 if(aError != KErrNone)
 	{
 	 iRetStatus = aError ;
 	 CActiveScheduler :: Stop() ;
 	 return KErrNone ;
 	}
if(iCount > 2)
	{
	 iRetStatus = aError ;
	 CActiveScheduler *Current = CActiveScheduler :: Current() ;
	 Current->Stop() ;
	 return KErrNone ;
	}
		
 RFile LogFile ;
 RFs LogSession ;
 TBuf8<50> Buffer(_L8("Latitude = ")) ;
 
 TPosition OutPos ;
 
 posinfo->GetPosition(OutPos) ;
 
 
 
 LogSession.Connect() ;
 
 if(LogFile.Open(LogSession ,LogFileName , EFileWrite | EFileShareAny )  == KErrNotFound)
 {
  LogFile.Create(LogSession ,LogFileName , EFileWrite | EFileShareAny ) ;
 	
 }
 
 TInt End = 0 ;
 
 LogFile.Seek(ESeekEnd , End) ; //Seek to end of the file before writing 
 
 TBuf8<50> num ;
 TRealFormat format ;
 TReal64 Val = OutPos.Latitude() ;
 num.Num(Val , format) ;

 //Logging Latitude 
 LogFile.Write(_L8("Latitude = "));
 LogFile.Write(num) ;
 LogFile.Write(_L8("\n")) ;
	 
 Val = OutPos.Longitude() ;
 num.Num(Val , format) ;
 
 //Logging Longitude
 
  LogFile.Write(_L8("Longitude = "));
  LogFile.Write(num) ;
  LogFile.Write(_L8("\n")) ;
 	
 	//Logging Altitude 
  Val = OutPos.Altitude() ;
  num.Num(Val , format) ;
  LogFile.Write(_L8("Altitude = "));
  LogFile.Write(num) ;
  LogFile.Write(_L8("\n"))  ;
  LogFile.Close() ;
  LogSession.Close() ;
  iCount++ ;
  return KErrNone ;	
}
	
TInt ServiceFailedFunctionL()
{
		
		CActiveScheduler *Scheduler = new CActiveScheduler ;
		CActiveScheduler :: Install(Scheduler) ;
		CLocationService *CoreObj = CLocationService ::NewL() ;
		
		/*RRequestorStack infostack;
    
	    const CRequestor* identityInfo = CRequestor::NewL(CRequestor::ERequestorService,CRequestor::EFormatApplication,
	    												KRequestor) ;
	    infostack.Append(identityInfo);
	    CoreObj->SetRequestorIdentityL(infostack);*/
		
		LocUpdateCallBack MyUpdates ;
    
    	CoreObj->TraceL(&MyUpdates,EBasicInfo) ;
    	CActiveScheduler :: Start() ; 
    	return  0 ;
    	
    	

}
TInt ServiceFailedTest(TAny */*Arg*/)
{
	CTrapCleanup* cleanup = CTrapCleanup::New();
	TRAPD(err , ServiceFailedFunctionL()) ;
	delete cleanup ;
	return 0 ;
	
}
TInt CTLocManualTest :: ServiceFailed(CStifItemParser& /*aItem*/)
{
	_LIT(KTLocTest ,"TLocTest");
	iLog->Log(KTLocTest) ;
	_LIT(KLog , "In service failed test ") ;
	iLog->Log(KTLocTest) ;
	
	TRequestStatus Status = KRequestPending  ;
	RThread FunctionThread ;
    
    TInt ret =  FunctionThread.Create(_L("ServiceFailed Thread") , ServiceFailedTest ,KDefaultStackSize , 
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
	    
	
	if((ret == KErrNotFound  ) || (ret == KPositionQualityLoss))
		{
		_LIT(KLog , "Service provider crashed or went dowm") ;
		iLog->Log(KLog) ;
		}
		
		
	   //return ret;	
	   return KErrNone;
}
	 
	
	

  		
  	
  		
  		
  	
 	



