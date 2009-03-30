/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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

class CGetLoc ; //Forward declaration
#include "TLocTest.h"
#include "locationservice.h"
#include <f32file.h>
#include <e32const.h>


_LIT(LogFileName , "C:\\Notifications.txt") ;
_LIT(KRequestor,"testapp");
//---------------------------------------------------------------------------------------------------------
/** 
  *@ This call back interface is for testing Trace 
 */
 //---------------------------------------------------------------------------------------------------------
  
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
   
    	
TInt GetLocFunctionL()
{
   
    	
    
    LocUpdateCallBack MyUpdates  ;
    CActiveScheduler *Scheduler = new CActiveScheduler ;
    
    CActiveScheduler :: Install(Scheduler) ;
    CLocationService *CoreObj = CLocationService ::NewL() ;
    
    //not needed any more
    /*RRequestorStack infostack;
    
    const CRequestor* identityInfo = CRequestor::NewL(CRequestor::ERequestorService,CRequestor::EFormatApplication,
    												KRequestor) ;
    infostack.Append(identityInfo);
    CoreObj->SetRequestorIdentityL(infostack);*/
   
   // GelocUpdateCallBack  MyUpdates(&CmdId  , (CLocationService *)NULL) ;
    CoreObj->TraceL(&MyUpdates,EBasicInfo) ;
    
    CActiveScheduler :: Start() ;
    return 0 ; // Controll never reaches here
}

TInt GetLocUpdates(TAny */*Arg*/)
{
	CTrapCleanup* cleanup = CTrapCleanup::New();
  //Install a new active scheduler to this thread 
  TRAPD(err , GetLocFunctionL()) ;
    delete cleanup ;
	return 0 ;
}

//---------------------------------------------------------------------------------------------------------
/** 
  *@ This call back interface is for testing GetLocation Asynchronous 
 */
 //---------------------------------------------------------------------------------------------------------
 
 class AsyncGetLoc : public MLocationCallBack
 {
   TInt iCount ;
   TInt iRetStatus ;
   public :
    	TInt HandleNotifyL(HPositionGenericInfo* aPosInfo, TInt aError) ;
    
    	AsyncGetLoc() :iCount(0) , iRetStatus(KErrGeneral)  //Default constructor 
    	{
    		;
    	}
  };
  
  
  
TInt AsyncGetLoc :: HandleNotifyL(HPositionGenericInfo* aPosInfo , TInt aError)
{
 RFile LogFile ;
 RFs LogSession ;
 TBuf8<50> Buffer(_L8("Latitude = ")) ;
 
 
 if(aError != KErrNone)
 	{
 	 iRetStatus = aError ;
 	 CActiveScheduler :: Stop() ;
 	 return KErrNone ;
 	}
 
 
 LogSession.Connect() ;
 
 if(LogFile.Open(LogSession ,LogFileName , EFileWrite | EFileShareAny )  == KErrNotFound)
 {
  LogFile.Create(LogSession ,LogFileName , EFileWrite | EFileShareAny ) ;
 	
 }
 
 TInt End = 0 ;
 
 LogFile.Seek(ESeekEnd , End) ; //Seek to end of the file before writing 
 
 TPosition aOutPos ;
 
 aPosInfo->GetPosition(aOutPos) ;
 TBuf8<50> num ;
 TRealFormat format ;
 TReal64 Val = aOutPos.Latitude() ;
 num.Num(Val , format) ;

 //Logging Latitude 
 LogFile.Write(_L8("Latitude = "));
 LogFile.Write(num) ;
 LogFile.Write(_L8("\n")) ;
	 
 Val = aOutPos.Longitude() ;
 num.Num(Val , format) ;
 
 //Logging Longitude
 
  LogFile.Write(_L8("Longitude = "));
  LogFile.Write(num) ;
  LogFile.Write(_L8("\n")) ;
 	
 	//Logging Altitude 
  Val = aOutPos.Altitude() ;
  num.Num(Val , format) ;
  LogFile.Write(_L8("Altitude = "));
  LogFile.Write(num) ;
  LogFile.Write(_L8("\n"))  ;
  LogFile.Close() ;
  LogSession.Close() ;
  iRetStatus = aError ;
  
  CActiveScheduler *Current = CActiveScheduler :: Current() ;
  Current->Stop() ;
  
  return KErrNone ;
  	
}

TInt GetLocAsynchFunctionL()
{
	CActiveScheduler *Scheduler = new CActiveScheduler ;
    
    CActiveScheduler :: Install(Scheduler) ;
    CLocationService *CoreObj = CLocationService ::NewL() ;
  
    AsyncGetLoc MyUpdates ;
    //not needed any more
    /*RRequestorStack infostack;
    
    const CRequestor* identityInfo = CRequestor::NewL(CRequestor::ERequestorService,CRequestor::EFormatApplication,
    												KRequestor) ;
    infostack.Append(identityInfo);
    CoreObj->SetRequestorIdentityL(infostack);*/
    CoreObj->GetLocationL(&MyUpdates,EBasicInfo) ;
    
    CActiveScheduler :: Start() ; 
    return 0 ;      //Controll never reaches here 
}




TInt FindLocationAsynch(TAny * /*Arg*/)
{
	CTrapCleanup* cleanup = CTrapCleanup::New();
  
    TRAPD(err , GetLocAsynchFunctionL()) ;
    delete cleanup ;
	return 0 ;
	
}

//---------------------------------------------------------------------------------------------------------
/** 
  *@ This call back interface is for testing  Service Not available  
 */
 //---------------------------------------------------------------------------------------------------------

TInt ServiceFailedFunctionL()
{
		
		CActiveScheduler *Scheduler = new CActiveScheduler ;
		CActiveScheduler :: Install(Scheduler) ;
		CLocationService *CoreObj = CLocationService ::NewL() ;
		
		//not needed any more
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



TInt ConcurrentGetLocCallsL()
	{
	LocUpdateCallBack MyUpdates  ;
    CActiveScheduler *Scheduler = new CActiveScheduler ;
    
    CActiveScheduler :: Install(Scheduler) ;
    CLocationService *CoreObj = CLocationService ::NewL() ;
    
    //not needed any more
    /*RRequestorStack infostack;
    
    const CRequestor* identityInfo = CRequestor::NewL(CRequestor::ERequestorService,CRequestor::EFormatApplication,
    												KRequestor) ;
    infostack.Append(identityInfo);
    CoreObj->SetRequestorIdentityL(infostack);*/
   
    
     CoreObj->GetLocationL(&MyUpdates,EBasicInfo) ;
    
     TInt error = CoreObj->GetLocationL(&MyUpdates,EBasicInfo) ;
    
    
    return error ; 

		
		
		
	}


TInt ConcurrentGetLocationCalls(TAny */*Arg*/)
{
  
	CTrapCleanup* cleanup = CTrapCleanup::New();
	TInt  Val ;
	//Install a new active scheduler to this thread 
	TRAPD(err ,( Val = ConcurrentGetLocCallsL()) );
	delete cleanup ;
 	
 	if(err)
 	    {
 	        return err ;
 	    }
	return Val ;
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
	    FunctionThread.Logon(Status)	;
	    FunctionThread.Resume() ;
	    
	    User :: WaitForRequest (Status)	;				
	    

	   ret = Status.Int() ;
	    }
	  FunctionThread.Close();  
	  
	  if(ret == KErrInUse)
	    return KErrNone ;
	  
	   return KErrGeneral;	
	}


TInt ConcurrentTraceCallsL()
	{
	LocUpdateCallBack MyUpdates  ;
    CActiveScheduler *Scheduler = new CActiveScheduler ;
    
    CActiveScheduler :: Install(Scheduler) ;
    CLocationService *CoreObj = CLocationService ::NewL() ;
    
    //not needed any more
    /*RRequestorStack infostack;
    
    const CRequestor* identityInfo = CRequestor::NewL(CRequestor::ERequestorService,CRequestor::EFormatApplication,
    												KRequestor) ;
    infostack.Append(identityInfo);
    CoreObj->SetRequestorIdentityL(infostack);*/
   
    
     CoreObj->TraceL(&MyUpdates,EBasicInfo) ;(&MyUpdates,EBasicInfo) ;
    
     TInt error = CoreObj->TraceL(&MyUpdates,EBasicInfo) ;
    
    
    return error ; 

		
		
		
	}


TInt ConcurrentTraceCalls(TAny */*Arg*/)
{
  
	CTrapCleanup* cleanup = CTrapCleanup::New();
	TInt  Val ;
	//Install a new active scheduler to this thread 
	TRAPD(err ,( Val = ConcurrentTraceCallsL()) );
	delete cleanup ;
 	
 	if(err)
 	    {
 	        return err ;
 	    }
	return Val ;
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
	    FunctionThread.Logon(Status)	;
	    FunctionThread.Resume() ;
	    
	    User :: WaitForRequest (Status)	;				
	    

	   ret = Status.Int() ;
	    }
	  FunctionThread.Close();  
	  
	  if(ret == KErrInUse)
	    return KErrNone ;
	  
	   return KErrGeneral;	
	}

