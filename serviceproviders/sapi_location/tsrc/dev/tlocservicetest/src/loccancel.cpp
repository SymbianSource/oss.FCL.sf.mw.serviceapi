/*
* Copyright (c) 2006-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:   contains test case implementation for CancelOngoingService location-SAPI
*  V	ersion     : %version: 6 % << Don't touch! Updated by Synergy at check-out.
*
*/


#include "tloctest.h"
#include "locationservice.h"
#include <f32file.h>
#include <e32const.h>
class CGetLoc ; //Forward declaration

#define GETLOCATION 0
#define TRACE 1

_LIT(LogFileName , "C:\\Notificationscan.txt") ;
_LIT(KRequestor,"testapp");

// INCLUDE FILES
#include "tloctest.h"

#include <e32svr.h>
#include <StifParser.h>

#include <StifTestInterface.h>

//#include <S60LocCoreImpl.h>
#include <AiwCommon.h>



enum ServiceType
     {
    		Trace = 0,
    		GetLocation = 1
     };
class CancelLocUpdateCallBack : public MLocationCallBack
 {
   TInt iCount ;
   TInt iRetStatus ;
   TInt iServiceId;
   CLocationService* iServicePtr;
    TInt iTransactionId;
    TInt iRequestType;
    public :
    	TInt HandleNotifyL(HPositionGenericInfo *aInfo , TInt aError) ;
    
    CancelLocUpdateCallBack(TInt trans,TInt req,CLocationService *CoreObj) :iCount(0) , iRetStatus(KErrGeneral),iServicePtr(CoreObj)  //Default constructor 
    	    {
    	    iTransactionId = trans;
    	    iRequestType = req;
    	    }
    inline TUint GetRequestType(void) 
        {
        return iRequestType ;
        }


    /**
     * GetTransactionId function returns transcation id associated with current async object
     *
     */
    inline TInt32 GetTransactionId(void)
        {
        return iTransactionId ;
        }    
  };


TInt CancelLocUpdateCallBack :: HandleNotifyL(HPositionGenericInfo *aInfo , TInt aError)
{
	
if(iCount > 2)
	{
	 iRetStatus = KErrNone ;
	 iServicePtr->CancelOnGoingService(ECancelTrace);
	 
	 CActiveScheduler *Current = CActiveScheduler :: Current() ;
	 Current->Stop() ;
	 return KErrNone ;
	}
		
 RFile LogFile ;
 RFs LogSession ;
 TBuf8<50> Buffer(_L8("Latitude = ")) ;
 
 
 
 
 
 LogSession.Connect() ;
 
 if(LogFile.Open(LogSession ,LogFileName , EFileWrite | EFileShareAny )  == KErrNotFound)
 {
  LogFile.Create(LogSession ,LogFileName , EFileWrite | EFileShareAny ) ;
 	
 }
 
 TInt End = 0 ;
 
 LogFile.Seek(ESeekEnd , End) ; //Seek to end of the file before writing 
 
 TBuf8<50> num ;
 TRealFormat format ;
 
 TPosition aOutPos ;
 
 aInfo->GetPosition(aOutPos) ;
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
  iCount++ ;
  return KErrNone ;	
}

/*Cancel Trace when a request is pending*/
   
TInt CancelLocFunctionAL()
{
   
    	
    __UHEAP_MARK ;
    
    CActiveScheduler *Scheduler = new CActiveScheduler ;
    
    CActiveScheduler :: Install(Scheduler) ;
    CLocationService *CoreObj = CLocationService ::NewL() ;
    CancelLocUpdateCallBack MyUpdates(10,TRACE,CoreObj)  ;
 
   
    CoreObj->TraceL((&MyUpdates),EBasicInfo) ;
    CoreObj->CancelOnGoingService(ECancelTrace);
    
    delete CoreObj;
    delete Scheduler;

    __UHEAP_MARKEND ;
    return 0 ; 
}	
TInt CancelLocUpdatesA(TAny */*Arg*/)
{
	CTrapCleanup* cleanup = CTrapCleanup::New();
  //Install a new active scheduler to this thread 
  TRAPD(err , CancelLocFunctionAL()) ;
    delete cleanup ;
	return 0 ;
}	  


TInt CTLocTest :: CancelLocationUpdatesA(CStifItemParser& /*aItem*/)
	{
	_LIT(KTLocTest ,"TLocTest");
	iLog->Log(KTLocTest) ;
	
	TRequestStatus Status = KRequestPending  ;
	RThread FunctionThread ;
    
    TInt ret = FunctionThread.Create(_L(" LocationUpdates Thread") , CancelLocUpdatesA ,KDefaultStackSize , 
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

/*Cancel Update when request has been served*/

TInt CancelLocFunctionBL()
{
   
    	
    __UHEAP_MARK ;
   
    CActiveScheduler *Scheduler = new CActiveScheduler ;
    
    CActiveScheduler :: Install(Scheduler) ;
    CLocationService *CoreObj = CLocationService ::NewL() ;
    CancelLocUpdateCallBack MyUpdates(11,TRACE,CoreObj)  ;
 
   
    CoreObj->TraceL((&MyUpdates),EBasicInfo) ;
    
    CActiveScheduler :: Start() ;
    delete CoreObj;
    delete Scheduler;
    __UHEAP_MARKEND ;
    
    
    return 0 ; 
}	
TInt CancelLocUpdatesB(TAny */*Arg*/)
{
	CTrapCleanup* cleanup = CTrapCleanup::New();
  //Install a new active scheduler to this thread 
  TRAPD(err , CancelLocFunctionBL()) ;
    delete cleanup ;
	return 0 ;
}	  

TInt CTLocTest :: CancelLocationUpdatesB(CStifItemParser& /*aItem*/)
	{
	_LIT(KTLocTest ,"TLocTest");
	iLog->Log(KTLocTest) ;
	
	TRequestStatus Status = KRequestPending  ;
	RThread FunctionThread ;
    
    TInt ret = FunctionThread.Create(_L(" LocationUpdates Thread") , CancelLocUpdatesB ,KDefaultStackSize , 
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
/*Location cancel test*/

TInt CancelLocAsynchFunctionL()
{
   
    	
    __UHEAP_MARK ;
    
    CActiveScheduler *Scheduler = new CActiveScheduler ;
    
    CActiveScheduler :: Install(Scheduler) ;
    CLocationService *CoreObj = CLocationService ::NewL() ;
    CancelLocUpdateCallBack MyUpdates(12,GETLOCATION,CoreObj)  ;
   
    CoreObj->GetLocationL((&MyUpdates),EBasicInfo) ;
    CoreObj->CancelOnGoingService(ECancelGetLocation);
    
    delete CoreObj;
    delete Scheduler;

    __UHEAP_MARKEND ;
    return 0 ; 
}	
TInt CancelLocAsynch(TAny */*Arg*/)
{
	CTrapCleanup* cleanup = CTrapCleanup::New();
  //Install a new active scheduler to this thread 
  TRAPD(err , CancelLocAsynchFunctionL()) ;
    delete cleanup ;
	return 0 ;
}	  


TInt CTLocTest :: CancelLocationAsynch(CStifItemParser& /*aItem*/)
	{
	_LIT(KTLocTest ,"TLocTest");
	iLog->Log(KTLocTest) ;
	
	TRequestStatus Status = KRequestPending  ;
	RThread FunctionThread ;
    
    TInt ret = FunctionThread.Create(_L(" LocationUpdates Thread") , CancelLocAsynch ,KDefaultStackSize , 
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


