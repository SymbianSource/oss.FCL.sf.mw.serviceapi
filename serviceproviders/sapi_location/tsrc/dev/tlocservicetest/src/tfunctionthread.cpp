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
#include "tloctest.h"
#include "locationservice.h"
#include <f32file.h>
#include <e32const.h>
#include<liwcommon.h>
TInt TraceTimeOutFuncL();

TInt reqErr;//To share the error value from callback
#define TRACE 1 
#define GETLOCATION 0

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
    TInt iRequestType;
    TInt iTransactionId;


public :
    TInt HandleNotifyL(HPositionGenericInfo *posinfo , TInt aError) ;


    LocUpdateCallBack(TInt transId,TInt req) :iCount(0) , iRetStatus(KErrGeneral)  //Default constructor 
    	        {
    	        iTransactionId = transId;
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
  
  
  
TInt LocUpdateCallBack :: HandleNotifyL(HPositionGenericInfo *posinfo , TInt aError)
{

 if(aError != KErrNone)
 	{
 	 iRetStatus = aError ;
        reqErr = KErrGeneral;
        CActiveScheduler :: Stop() ;
        return KErrGeneral ;
        }
    iCount++ ;
    if(iCount > 1)
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
    __UHEAP_MARK ;
    reqErr= KErrNone;

    LocUpdateCallBack MyUpdates(9,TRACE)  ;
    CActiveScheduler *Scheduler = new CActiveScheduler ;

    CActiveScheduler :: Install(Scheduler) ;
    CLocationService *CoreObj = CLocationService ::NewL() ;

   
    CoreObj->TraceL(&MyUpdates,EBasicInfo) ;

    CActiveScheduler :: Start() ;
    delete CoreObj;
    delete Scheduler;
    __UHEAP_MARKEND ;
    return  reqErr; 
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
    TInt iRequestType;
    TInt iTransactionId;
    public :
        TInt HandleNotifyL(HPositionGenericInfo* aPosInfo, TInt aError) ;

        AsyncGetLoc(TInt aTransId,TInt aReqType) :iCount(0) , iRetStatus(KErrGeneral)  //Default constructor 
    	        {
    	        iTransactionId = aTransId;
    	        iRequestType = aReqType;
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
  
  
  
TInt AsyncGetLoc :: HandleNotifyL(HPositionGenericInfo* aPosInfo , TInt aError)
{
 RFile LogFile ;
 RFs LogSession ;
 TBuf8<50> Buffer(_L8("Latitude = ")) ;
 
 
 if(aError != KErrNone)
 	{
 	 iRetStatus = aError ;
        reqErr = aError;
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
    __UHEAP_MARK ;
    reqErr = KErrNone;
    CActiveScheduler *Scheduler = new CActiveScheduler ;

    CActiveScheduler :: Install(Scheduler) ;
    CLocationService *CoreObj = CLocationService ::NewL() ;

    AsyncGetLoc MyUpdates(10,GETLOCATION) ;
    //not needed any more
    /*RRequestorStack infostack;

    const CRequestor* identityInfo = CRequestor::NewL(CRequestor::ERequestorService,CRequestor::EFormatApplication,
    												KRequestor) ;
    infostack.Append(identityInfo);
    CoreObj->SetRequestorIdentityL(infostack);*/
    CoreObj->GetLocationL(&MyUpdates,EBasicInfo) ;

    CActiveScheduler :: Start() ; 
    delete CoreObj;
    delete Scheduler;
    __UHEAP_MARKEND ;
    return reqErr ; 
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
    reqErr = KErrNone;
    __UHEAP_MARK ;
    CActiveScheduler *Scheduler = new CActiveScheduler ;
    CActiveScheduler :: Install(Scheduler) ;
    CLocationService *CoreObj = CLocationService ::NewL() ;

    LocUpdateCallBack MyUpdates(11,TRACE) ;

    CoreObj->TraceL(&MyUpdates,EBasicInfo) ;
    CActiveScheduler :: Start() ; 
    delete CoreObj;
    delete Scheduler;
    __UHEAP_MARKEND ;
    return  reqErr ;
    	
    	

}



TInt ServiceFailedTest(TAny */*Arg*/)
{
    TInt errRet = 0;
    CTrapCleanup* cleanup = CTrapCleanup::New();
    TRAPD(err , errRet = ServiceFailedFunctionL()) ;
    delete cleanup ;

    return errRet ;
	
}



TInt ConcurrentGetLocCallsL()
	{
    __UHEAP_MARK ;
    reqErr = KErrNone;
    LocUpdateCallBack MyUpdates(10,GETLOCATION)  ;
    CActiveScheduler *Scheduler = new CActiveScheduler ;

    CActiveScheduler :: Install(Scheduler) ;
    CLocationService *CoreObj = CLocationService ::NewL() ;



    CoreObj->GetLocationL(&MyUpdates,EBasicInfo) ;

    TRAPD(error, CoreObj->GetLocationL(&MyUpdates,EBasicInfo) );

    CActiveScheduler :: Start() ; 
    delete CoreObj;
    delete Scheduler;
    __UHEAP_MARKEND ;

    return error | reqErr ; 

		
		
		
	}


TInt ConcurrentGetLocationCalls(TAny */*Arg*/)
{
  
	CTrapCleanup* cleanup = CTrapCleanup::New();
	TInt  Val = 0;
	//Install a new active scheduler to this thread 
	TRAPD(err ,( Val = ConcurrentGetLocCallsL()) );
	delete cleanup ;
 	
 	if(err)
 	    {
 	        return err ;
 	    }
	return Val ;
}

  




TInt ConcurrentTraceCallsL()
	{
    __UHEAP_MARK ;
    reqErr = KErrNone;
    LocUpdateCallBack MyUpdates(12,TRACE)  ;
    CActiveScheduler *Scheduler = new CActiveScheduler ;

    CActiveScheduler :: Install(Scheduler) ;
    CLocationService *CoreObj = CLocationService ::NewL() ;

    //not needed any more
    /*RRequestorStack infostack;

    const CRequestor* identityInfo = CRequestor::NewL(CRequestor::ERequestorService,CRequestor::EFormatApplication,
    												KRequestor) ;
    infostack.Append(identityInfo);
    CoreObj->SetRequestorIdentityL(infostack);*/


    CoreObj->TraceL(&MyUpdates,EBasicInfo) ;

    TRAPD(error,CoreObj->TraceL(&MyUpdates,EBasicInfo)) ;

    CActiveScheduler :: Start() ; 
    delete CoreObj;
    delete Scheduler;
    __UHEAP_MARKEND ;
    return error | reqErr ; 

		
		
		
	}


TInt ConcurrentTraceCalls(TAny */*Arg*/)
{
  
	CTrapCleanup* cleanup = CTrapCleanup::New();
	TInt  Val = 0;
	//Install a new active scheduler to this thread 
	TRAPD(err ,( Val = ConcurrentTraceCallsL()) );
	delete cleanup ;
 	
 	if(err)
 	    {
 	        return err ;
 	    }
	return Val ;
}

	

TInt TraceTimeOutFunc(TAny */*Arg*/)
    {

    CTrapCleanup* cleanup = CTrapCleanup::New();
    TInt  Val = 0;
    //Install a new active scheduler to this thread 
    TRAPD(err ,( Val = TraceTimeOutFuncL()) );
    delete cleanup ;

    if(err)
        {
        return err ;
        }
    return Val ;
    }


class LocUpdateCallBackTO : public MLocationCallBack
    {
    TInt iCount ;
    TInt iRetStatus ;
    TInt iRequestType;
    TInt iTransactionId;
    public :
        TInt HandleNotifyL(HPositionGenericInfo *posinfo , TInt aError) ;

        LocUpdateCallBackTO(TInt transId,TInt req) :iCount(0) , iRetStatus(KErrGeneral)  //Default constructor 
               {
               iTransactionId = transId;
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



TInt LocUpdateCallBackTO :: HandleNotifyL(HPositionGenericInfo *posinfo , TInt aError)
    {
    iCount++;
    if(aError != KErrTimedOut)
        {
        iRetStatus = aError ;
        CActiveScheduler *Current = CActiveScheduler :: Current() ;
        reqErr = KErrGeneral;
        Current->Stop() ;

        return KErrGeneral ;
        }

    else if(iCount > 2)
        {
        iRetStatus = aError ;
        CActiveScheduler *Current = CActiveScheduler :: Current() ;
        Current->Stop() ;

        }
    return KErrNone ;   
    }


TInt TraceTimeOutFuncL()
    {
    __UHEAP_MARK ;
    reqErr = KErrNone;
    LocUpdateCallBackTO MyUpdates(14,TRACE)  ;
    CActiveScheduler *Scheduler = new CActiveScheduler ;

    CActiveScheduler :: Install(Scheduler) ;
    CLocationService *CoreObj = CLocationService ::NewL() ;



    TPositionUpdateOptions updateopts ;
    updateopts.SetUpdateTimeOut(3);
    TPositionFieldId FieldList[10] ;
    CoreObj->TraceL(&MyUpdates,EBasicInfo,FieldList,&updateopts) ;


    CActiveScheduler :: Start() ; 
    delete CoreObj;
    delete Scheduler;
    __UHEAP_MARKEND ;
    return reqErr;    
    }
