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
#include <e32svr.h>
#include <StifParser.h>
#include <Stiftestinterface.h>
#include "SAPILocTest.h"
#include <f32file.h>
#include <LbsPosition.h>
#include <LbsPositionInfo.h> 
#include <LbsCommon.h>


_LIT(LogFileName , "C:\\tsapiloctest.txt") ;
TInt returnCode;
RFile LogFile ;
RFs LogSession ;

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

TInt ValidatePosition(TPosition& aPos)
	{
	TReal64 aLatitude  = aPos.Latitude();
	TReal64 aLongitude = aPos.Longitude() ;
	TReal32 aAltitude  = aPos.Altitude() ;

	if( (-90<=aLatitude<=90) && (-180<=aLongitude<=180) && (aAltitude) )
		{
		OpenFile();
		TBuf8<50> buf ;
		TRealFormat format ;
		
	    //Logging Latitude 
		buf.Num(aLatitude , format) ;
		LogFile.Write(_L8("Latitude = "));
		LogFile.Write(buf) ;
		LogFile.Write(_L8("\n")) ;
		//Logging Longitude
		buf.Num(aLongitude , format); 
		LogFile.Write(_L8("Longitude = "));
		LogFile.Write(buf) ;
		LogFile.Write(_L8("\n")) ;
		//Logging Altitude 
		buf.Num(aAltitude , format) ;
		LogFile.Write(_L8("Altitude = "));
		LogFile.Write(buf) ;
		LogFile.Write(_L8("\n")) ;
		CloseFile();
	    return KErrNone; 
		 }
	 else
		 {
	     OpenFile();
	     LogFile.Write(_L8("Test case failed.."));
		 CloseFile();
		 return KErrGeneral;	
		 }
	}
    



// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CSAPILocTest::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CSAPILocTest::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CSAPILocTest::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CSAPILocTest::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
         ENTRY( "CreateLocObjWSer",    CSAPILocTest::CreateLocObjWSer ),
         ENTRY( "CreateLocObjs",    CSAPILocTest::CreateLocObjs ),
      // ENTRY( "CreateLocObjWOSer",    CSAPILocTest::CreateLocObjWOSer ),
         ENTRY( "GetPosition",    CSAPILocTest::GetPosition ),
         ENTRY( "GetPosition1",    CSAPILocTest::GetPosition1 ),
         ENTRY( "GetPosition2",    CSAPILocTest::GetPosition2 ),
      // ENTRY( "GetPositionTO",    CSAPILocTest::GetPositionTO ),
         ENTRY( "GetPositionAsync",    CSAPILocTest::GetPositionAsync ),
     //  ENTRY( "GetPositionAsyncTO",    CSAPILocTest::GetPositionAsyncTO ),
      // ENTRY( "GetPositionAsyncOpts",    CSAPILocTest::GetPositionAsyncOpts),
         ENTRY( "GetPositionAsyncOpts1",    CSAPILocTest::GetPositionAsyncOpts1),
         ENTRY( "GetPositionAsyncOpts2",    CSAPILocTest::GetPositionAsyncOpts2),
         ENTRY( "GetPositionAsyncOpts3",    CSAPILocTest::GetPositionAsyncOpts3),
         ENTRY( "GetPositionAsyncOpts4",    CSAPILocTest::GetPositionAsyncOpts4),
         ENTRY( "GetPositionAsyncOpts5",    CSAPILocTest::GetPositionAsyncOpts5),
         ENTRY( "GetPositionAsyncOpts6",    CSAPILocTest::GetPositionAsyncOpts6),
         ENTRY( "TraceLPosition",    CSAPILocTest::TraceLPosition),
         ENTRY( "TraceLPosition1",    CSAPILocTest::TraceLPosition1),
      // ENTRY( "TraceLPositionTO",    CSAPILocTest::TraceLPositionTO),
         ENTRY( "TraceLPosition2",    CSAPILocTest::TraceLPosition2),
         ENTRY( "TraceLPosition3",    CSAPILocTest::TraceLPosition3),
         ENTRY( "TraceLPosition4",    CSAPILocTest::TraceLPosition4),
         ENTRY( "TraceLPosition5",    CSAPILocTest::TraceLPosition5),
         ENTRY( "TraceLPosition6",    CSAPILocTest::TraceLPosition6),
         ENTRY( "TraceLPosition7",    CSAPILocTest::TraceLPosition7),
         ENTRY( "TraceLPosition8",    CSAPILocTest::TraceLPosition8),
         ENTRY( "TraceLPositionOpts",    CSAPILocTest::TraceLPositionOpts),
         ENTRY( "TraceLPositionOpts1",    CSAPILocTest::TraceLPositionOpts1),
         ENTRY( "TraceLPositionOpts2",    CSAPILocTest::TraceLPositionOpts2),
         ENTRY( "TraceLPositionOpts3",    CSAPILocTest::TraceLPositionOpts3),
         ENTRY( "CancelService1",    CSAPILocTest::CancelService1 ),
         ENTRY( "CancelService2",    CSAPILocTest::CancelService2 ),
         ENTRY( "GetTime",    CSAPILocTest::GetTime ),
         ENTRY( "GetSpeed",    CSAPILocTest::GetSpeed ),
         ENTRY( "GetPositionOpts",    CSAPILocTest::GetPositionOpts ),
         ENTRY( "GetPositionOpts1",    CSAPILocTest::GetPositionOpts1 ),
         ENTRY( "GetPositionOpts2",    CSAPILocTest::GetPositionOpts2 ),
         ENTRY( "GetPositionOpts3",    CSAPILocTest::GetPositionOpts3 ),
         ENTRY( "GetPositionOpts4",    CSAPILocTest::GetPositionOpts4 ),
         ENTRY( "GetPositionOpts5",    CSAPILocTest::GetPositionOpts5 ),
     //  ENTRY( "GetLastPosition",    CSAPILocTest::GetLastPosition ),
     //  ENTRY( "GetLastPosition1",    CSAPILocTest::GetLastPosition1 ),
         ENTRY( "GetDistance",    CSAPILocTest::GetDistance ),
         ENTRY( "GetDistance2",    CSAPILocTest::GetDistance2 ),
         ENTRY( "GetDistance3",    CSAPILocTest::GetDistance3 ),
         ENTRY( "GetDistance4",    CSAPILocTest::GetDistance4 ),
         ENTRY( "GetDistance5",    CSAPILocTest::GetDistance5 ),
         ENTRY( "GetDistance6",    CSAPILocTest::GetDistance6 ),
         ENTRY( "GetDistance7",    CSAPILocTest::GetDistance7 ),
         ENTRY( "GetDistance8",    CSAPILocTest::GetDistance8),
         ENTRY( "GetDistance9",    CSAPILocTest::GetDistance9),
         ENTRY( "GetDistance10",    CSAPILocTest::GetDistance10),
         ENTRY( "GetDistance11",    CSAPILocTest::GetDistance11),
         ENTRY( "GetDistance12",    CSAPILocTest::GetDistance12),
         ENTRY( "GetBearing",    CSAPILocTest::GetBearing),
         ENTRY( "GetBearing1",    CSAPILocTest::GetBearing1),
         ENTRY( "GetBearing2",    CSAPILocTest::GetBearing2),
         ENTRY( "GetBearing3",    CSAPILocTest::GetBearing3),
         ENTRY( "GetBearing4",    CSAPILocTest::GetBearing4),
         ENTRY( "GetBearing5",    CSAPILocTest::GetBearing5),
         ENTRY( "GetBearing6",    CSAPILocTest::GetBearing6),
         ENTRY( "GetBearing7",    CSAPILocTest::GetBearing7),
         ENTRY( "GetBearing8",    CSAPILocTest::GetBearing8),
         ENTRY( "GetBearing9",    CSAPILocTest::GetBearing9),
         ENTRY( "GetBearing10",    CSAPILocTest::GetBearing10),
         ENTRY( "GetBearing11",    CSAPILocTest::GetBearing11),
         ENTRY( "GetBearing12",    CSAPILocTest::GetBearing12),
         ENTRY( "GetBearing13",    CSAPILocTest::GetBearing13),
         ENTRY( "GetBearing14",    CSAPILocTest::GetBearing14),
         ENTRY( "Move1",    CSAPILocTest::Move1),
         ENTRY( "Move2",    CSAPILocTest::Move2),
         ENTRY( "Move3",    CSAPILocTest::Move3),
         ENTRY( "Move4",    CSAPILocTest::Move4),
         ENTRY( "Move5",    CSAPILocTest::Move5),
         ENTRY( "Move6",    CSAPILocTest::Move6),
         ENTRY( "Move7",    CSAPILocTest::Move7),
         ENTRY( "Move8",    CSAPILocTest::Move8),
         ENTRY( "Modinfo1",    CSAPILocTest::Modinfo1),
        };
        

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }
    
    
    

// -----------------------------------------------------------------------------
// CSAPILocTest::CreateLocObjWSer
// -----------------------------------------------------------------------------
//
TInt CSAPILocTest::CreateLocObjWSer( CStifItemParser& /*aItem*/ )
    {
    returnCode = KErrNone;
    // Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "CreateLocationObjWSer" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
    
    __UHEAP_MARK;
    
    CLocationService *CoreObj = CLocationService :: NewL();
    
    if( NULL == CoreObj)
	    {
    	OpenFile();
        LogFile.Write(_L8("\n<CreateLocObjWSer Test>\n"));
        LogFile.Write(_L8("Failed..\n"));
    	CloseFile();
    	returnCode = KErrGeneral;
   		}
    else
	    {
        delete CoreObj;
    	OpenFile();
        LogFile.Write(_L8("\n<CreateLocObjWSer Test>\n"));
        LogFile.Write(_L8("Passed..\n"));
    	CloseFile();
     	returnCode = KErrNone;
	    }
    __UHEAP_MARKEND;
    return returnCode;
    }
    
    
// -----------------------------------------------------------------------------
// CSAPILocTest::CreateLocObjs
// -----------------------------------------------------------------------------
//
TInt CSAPILocTest::CreateLocObjs( CStifItemParser& /*aItem*/ )
    {
    // Print to UI
    TInt aLoopCount = 0;
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "CreateLocationObjs" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
    
    __UHEAP_MARK;
    
    CLocationService *CoreObj[10];
     
    while( aLoopCount<10 )
	    {
	    CoreObj[aLoopCount] = CLocationService :: NewL();	
	    if( NULL == CoreObj)
	    	{
	     	OpenFile();
		    LogFile.Write(_L8("\n<CreateLocObjs Test>\n"));
		    LogFile.Write(_L8("Failed..\n"));
		    CloseFile();
		    __UHEAP_MARKEND;
		   	return KErrGeneral;		
	   	  	} 
	   	aLoopCount++;
	   	}
      
   	aLoopCount=0;
    
   	while( aLoopCount<10 )
    	{
    	delete CoreObj[aLoopCount];
    	aLoopCount++;
    	}
	    
	OpenFile();
    LogFile.Write(_L8("\n<CreateLocObjs  Test>\n"));
    LogFile.Write(_L8("Passed..\n"));
	CloseFile();
	
    __UHEAP_MARKEND;
    
    return KErrNone; 
      
	}


// -----------------------------------------------------------------------------
// CSAPILocTest::GetPosition
// -----------------------------------------------------------------------------
//
TInt CSAPILocTest::GetPosition( CStifItemParser& /*aItem*/ )
    {
    TInt aRet = KErrNone;
    TPositionInfo currPos;
    returnCode = KErrNone;
    // Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "GetLocation" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
    
    __UHEAP_MARK;
    
    CLocationService *CoreObj = CLocationService :: NewL();
    	
    if( NULL == CoreObj)
	    {
	    OpenFile();
	    LogFile.Write(_L8("\n<GetPosition Test>\n"));
	    LogFile.Write(_L8("Failed..\n"));
	    CloseFile();
	   	return KErrGeneral;
	   	}
    //This is not required now
    /*TRAPD( error,aRet = CoreObj->GetLocationL(&currPos) );
    
    if( KErrAccessDenied == aRet)
    	{
    	OpenFile();
	    LogFile.Write(_L8("\n<GetPosition Test>\n"));
	    LogFile.Write(_L8("Passed..\n"));
	    CloseFile();
	    delete CoreObj;
    	__UHEAP_MARKEND;
    	return KErrNone;	
    	}
 
      else
    	{
    	OpenFile();
	    LogFile.Write(_L8("\n<GetPosition Test>\n"));
	    LogFile.Write(_L8("Failed..\n"));
	    CloseFile();
	    delete CoreObj;
    	__UHEAP_MARKEND;
    	return KErrGeneral;	
    	}*/
    else
    	{
    	OpenFile();
	    LogFile.Write(_L8("\n<GetPosition Test>\n"));
	    LogFile.Write(_L8("Passed..\n"));
	    CloseFile();
	    delete CoreObj;
    	__UHEAP_MARKEND;
    	return KErrNone;	
    		
    	}	
  }
    

// -----------------------------------------------------------------------------
// CSAPILocTest::GetPosition1
// -----------------------------------------------------------------------------
//
TInt CSAPILocTest::GetPosition1( CStifItemParser& /*aItem*/ )
    {
    TInt aRet = KErrNone,aFlag;
    TPositionInfo currPos;
    returnCode = KErrNone;
    // Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "GetLocation" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
    
    __UHEAP_MARK;
    
    CLocationService *CoreObj = CLocationService :: NewL();
    	
    if( NULL == CoreObj)
	    {
	    OpenFile();
	    LogFile.Write(_L8("\n<GetPosition1 Test>\n"));
	    LogFile.Write(_L8("Failed..\n"));
	    CloseFile();
	   	return KErrGeneral;
	   	}
    
    _LIT(Kidentity ,"Coreclass Testing" ) ;
    //not needed any more
	/*RRequestorStack aRequestorStack;
	const CRequestor* identityInfo = CRequestor::NewL(1 , 1 , Kidentity) ;
    aRequestorStack.Insert(identityInfo,0);
    CoreObj->SetRequestorIdentityL(aRequestorStack) ;*/

    
    TRAPD( error,aRet = CoreObj->GetLocationL(&currPos) );
    
    if( KErrNone == aRet )
    	{
    	OpenFile();
    	LogFile.Write(_L8("\n<GetPosition Test>\n"));
    	CloseFile();
    	TPosition currPos1; 
    	currPos.GetPosition(currPos1);
    	aFlag = ValidatePosition(currPos1);
    	returnCode = aFlag ;    
    	}
    
    else
    	{
        OpenFile();
	    LogFile.Write(_L8("\n<GetPosition1 Test>\n"));
	    LogFile.Write(_L8("Failed..\n"));
	    CloseFile();
    	returnCode = KErrGeneral;
    	}
 	/*aRequestorStack.Close();
    delete identityInfo;*/
    delete CoreObj;
   	__UHEAP_MARKEND;
	
	return returnCode;	
 	}
        
// -----------------------------------------------------------------------------
// CSAPILocTest::GetPosition2
// -----------------------------------------------------------------------------
//
TInt CSAPILocTest::GetPosition2( CStifItemParser& /*aItem*/ )
    {
	TInt aRet1,aRet2,aFlag1,aFlag2;
	TInt aError[2];
	TPositionInfo currPos1;
	TPositionInfo currPos2;
	TPosition currPosition1;
	TPosition currPosition2;
    returnCode = KErrNone;
    	
    // Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "GetLocation2" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
    
    __UHEAP_MARK;
    
    CLocationService *CoreObj = CLocationService :: NewL();
    
    if( NULL == CoreObj )
    	{
    	OpenFile();
	    LogFile.Write(_L8("\n<GetPosition2 Test>\n"));
	    LogFile.Write(_L8("Failed(Null CoreObj)..\n"));
	    CloseFile();
   		return KErrGeneral;
   		}
    
    _LIT(Kidentity ,"Coreclass Testing" ) ;
    //not needed any more
	/*RRequestorStack aRequestorStack;
	const CRequestor* identityInfo = CRequestor::NewL(1 , 1 , Kidentity) ;
    aRequestorStack.Insert(identityInfo,0);
    CoreObj->SetRequestorIdentityL(aRequestorStack) ;*/
	
	User::After(120000000) ;	
    aRet1 = CoreObj->GetLocationL(&currPos1) ;
    
    
    if (KErrNone == aRet1)
    	{
        aRet2 = CoreObj->GetLocationL(&currPos2) ;
        
        OpenFile();
    	LogFile.Write(_L8("\n<GetPosition2 Test>\n"));
    	CloseFile();
    	
    	currPos1.GetPosition(currPosition1);
    	currPos2.GetPosition(currPosition2);
    	aFlag1 = ValidatePosition(currPosition1);
    	aFlag2 = ValidatePosition(currPosition2);
    	
       	if((KErrNone == aFlag1) && (KErrNone == aFlag2))
    		{
    		OpenFile();
	    	LogFile.Write(_L8("Passed..\n"));
	    	CloseFile();
	    	returnCode = KErrNone;
    		}
    	else
    		{
    		OpenFile();
    		LogFile.Write(_L8("Failed..\n"));
    		CloseFile();
    		returnCode = KErrGeneral;	
    		}
    	}
    else
    	{
       	OpenFile();
    	LogFile.Write(_L8("\n<GetPosition2 Test>\n"));
    	LogFile.Write(_L8("Failed(getloc error)..\n"));
    	CloseFile();
    	returnCode = KErrGeneral;
    	}
    
     /*aRequestorStack.Close();
	 delete identityInfo;*/
	 delete CoreObj;
    
    __UHEAP_MARKEND;
    
    return returnCode;	
    
    }
	    
    

    
// -----------------------------------------------------------------------------
// CSAPILocTest::GetPositionAsync
// -----------------------------------------------------------------------------
//

class LocUpdateCallBack : public MLocationCallBack
	{
    TInt iCount ;
    TInt iRetStatus ;
    public :
    TInt HandleNotifyL(HPositionGenericInfo* aOutPos , TInt aError) ;
    LocUpdateCallBack() :iCount(0) , iRetStatus(KErrGeneral){;}
	};
  
   
TInt LocUpdateCallBack :: HandleNotifyL(HPositionGenericInfo *currPos , TInt /*aError*/)
	{
//	User::After(60000000);
	TInt aRetVal = KErrNone;
	
	OpenFile();
	LogFile.Write(_L8("\n<GetPositionAsync Test>\n "));
	CloseFile();
	TPosition outPos ;
  	currPos->GetPosition(outPos) ;
	aRetVal = ValidatePosition(outPos);
    
    if( KErrNone == aRetVal )
	    {
    	OpenFile();
    	LogFile.Write(_L8("Passed..\n"));
    	CloseFile();
    	returnCode = KErrNone;
	    }
   else
	   	{
   		OpenFile();
   		LogFile.Write(_L8("Failed..\n"));
   		CloseFile();
   		returnCode = KErrGeneral;
	   	}
    
    CActiveScheduler *Current = CActiveScheduler :: Current() ;
	Current->Stop() ;
	return KErrNone ;
	}

TInt GetLocFunctionL()
	{
    TBuf8<20> retBuf;
    TRealFormat retFormat;
  
    CLocationService *CoreObj = CLocationService ::NewL() ;
    
    if( NULL == CoreObj )
    	{
    	OpenFile();
	    LogFile.Write(_L8("\n<GetPositionAsync Test>\n"));
	    LogFile.Write(_L8("Failed(CoreObj Creation)..\n"));
	    CloseFile();
   		return KErrGeneral;
   		}
    
    _LIT(Kidentity ,"Coreclass Testing" ) ;
	//not needed any more
	/*RRequestorStack aRequestorStack;
	const CRequestor* identityInfo = CRequestor::NewL(1 , 1 , Kidentity) ;
    aRequestorStack.Insert(identityInfo,0);
    
    CoreObj->SetRequestorIdentityL(aRequestorStack) ;*/
		
    LocUpdateCallBack MyUpdates  ;
    
    CoreObj->GetLocationL(&MyUpdates) ;
    
    User::After(60000000);
    CActiveScheduler :: Start() ;
        
    retBuf.Num(returnCode,retFormat) ;
    OpenFile();
    LogFile.Write(_L8("\nreturnCode : "));
    LogFile.Write(retBuf);
    CloseFile();
    /*aRequestorStack.Close();
    delete identityInfo;*/
    delete CoreObj;
    return 0;
	}

TInt CSAPILocTest::GetPositionAsync( CStifItemParser& /*aItem*/ )
	{
    TRequestStatus status = KRequestPending;
    TInt aRet = KErrNone;
    returnCode = KErrNone;
    // Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "GetPositionAsync" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
    
     __UHEAP_MARK;
    
    TRAPD(err , aRet = GetLocFunctionL()) ;
    if( err || aRet )
    returnCode = KErrGeneral; 
    
    __UHEAP_MARKEND;
 
    return returnCode;  
    }
    
   

// -----------------------------------------------------------------------------
// CSAPILocTest::GetPositionAsyncOpts1
// -----------------------------------------------------------------------------
//
class LocUpdateCallBackOpts1 : public MLocationCallBack
	{
	TInt iCount ;
	TInt iRetStatus ;
	public :
	TInt HandleNotifyL(HPositionGenericInfo* aOutPos , TInt aError) ;
	LocUpdateCallBackOpts1() :iCount(0) , iRetStatus(KErrGeneral)  //Default constructor 
		{;}
	};
   
TInt LocUpdateCallBackOpts1 :: HandleNotifyL(HPositionGenericInfo* /*currPos*/ , TInt aError)
	{
	if(KErrTimedOut == aError)
 		{
	    OpenFile();
	    LogFile.Write(_L8("\n<GetPositionAsyncOpts1 Async test>\n "));
	    LogFile.Write(_L8("Passed..\n "));
	    CloseFile(); 
	 	returnCode = KErrNone;
	    }
 
 	else
	 	{
	 	OpenFile();
	 	LogFile.Write(_L8("GetPositionAsyncOpts1 Async failed "));
	    CloseFile();
	  	returnCode = KErrGeneral;
		}
 
 
  CActiveScheduler *Current = CActiveScheduler :: Current() ;
  Current->Stop() ;
  
  return KErrNone ;
	}

TInt GetLocFunctionOpts1L()
	{
    TInt ret;
    TPositionUpdateOptions aOptions;
    TTimeIntervalMicroSeconds aTimeOut = 100;
  
    CLocationService *CoreObj = CLocationService ::NewL() ;
    if( NULL == CoreObj )
    	{
    	OpenFile();
	    LogFile.Write(_L8("\n<GetPositionAsyncOpts1 Test>\n"));
	    LogFile.Write(_L8("Failed..\n"));
	    CloseFile();
   		return KErrGeneral;
   		}
    
    _LIT(Kidentity ,"Coreclass Testing" ) ;
	//not needed any more
	/*RRequestorStack aRequestorStack;
	
	const CRequestor* identityInfo = CRequestor::NewL(1 , 1 , Kidentity) ;
    aRequestorStack.Insert(identityInfo,0);
    
    CoreObj->SetRequestorIdentityL(aRequestorStack) ;*/
		
    LocUpdateCallBackOpts1 MyUpdates ;
    
    aOptions.SetUpdateTimeOut(aTimeOut);
    
    ret = CoreObj->GetLocationL(&MyUpdates,0,NULL ,&aOptions) ;
    
    if(KErrNone == ret)
	    {
	    CActiveScheduler :: Start() ;	
	    }
    
    else
    	{
    	returnCode = KErrGeneral;	
    	}
        
    //aRequestorStack.Close();
    
    delete CoreObj;
    return KErrNone;;
	}


TInt CSAPILocTest::GetPositionAsyncOpts1( CStifItemParser& /*aItem*/ )
	{
    TRequestStatus status = KRequestPending;
    TInt aRet = KErrNone;
    returnCode = KErrNone;
    
    // Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "GetPositionAsyncOpts1" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
    
	__UHEAP_MARK;
	
    TInt start = User::CountAllocCells();
    TRAPD(err ,aRet = GetLocFunctionOpts1L()) ;
    if( err || aRet)
    returnCode = KErrGeneral;
    
    TInt end = User::CountAllocCells();
    
    __UHEAP_MARKEND;
    
     return returnCode;  
	}


// -----------------------------------------------------------------------------
// CSAPILocTest::GetPositionAsyncOpts2
// -----------------------------------------------------------------------------
//

class LocUpdateCallBackOpts2 : public MLocationCallBack
	{
    TInt iCount ;
    TInt iRetStatus ;
    public :
    TInt HandleNotifyL(HPositionGenericInfo* aOutPos , TInt aError) ;
    LocUpdateCallBackOpts2() :iCount(0) , iRetStatus(KErrGeneral){;}
	};
  
   
TInt LocUpdateCallBackOpts2 :: HandleNotifyL(HPositionGenericInfo* currPos , TInt aError)
	{
    User::After(60000000);
    if(KErrNone == aError)
   		{
	 	 TPosition currPos1;
	 	 currPos->GetPosition(currPos1);
	 //	 ValidatePosition(currPos1);
		 TBuf8<50> buf;
		 TRealFormat format ;
		 TInt64 aTime1;;
		 TTime aTimeStamp1;
		 aTimeStamp1 = currPos1.Time();
         aTime1 = aTimeStamp1.Int64();
         buf.Num(aTime1 , format) ;
         if(aTime1) 
         	{
          	OpenFile();
            LogFile.Write(_L8("Time = "));
		    LogFile.Write(buf) ;
		    CloseFile();
		    returnCode = KErrNone;
	     	}
	     else
	    	{
	    	OpenFile();
            LogFile.Write(_L8("\nFailed(Time value).."));
		    CloseFile();
		    returnCode = KErrGeneral;
	    	}
		 
	  	 }
	 
	 else
	 	{
	 	OpenFile();
        LogFile.Write(_L8("\nFailed(Handlenotifyl error).."));
		CloseFile();
		returnCode = KErrGeneral;
		}
	 
	  CActiveScheduler *Current = CActiveScheduler :: Current() ;
	  Current->Stop() ;
	  return KErrNone ;
}


TInt GetLocFunctionOpts2L()
	{
    TInt ret;
    TPositionInfo aPosition1,aPosition2,aPosition3;  
    TPosition aPos1,aPos2,aPos3;
    TPositionUpdateOptions aOptions;
    TTime start,end;
    TTimeIntervalMicroSeconds aTimeOut =  6000000;
	TTimeIntervalMicroSeconds aInterval = 60000000;
    TTimeIntervalMicroSeconds aActualInterval;
    
    CLocationService *CoreObj = CLocationService ::NewL() ;
   
    if( NULL == CoreObj )
    	{
    	OpenFile();
	    LogFile.Write(_L8("\n<GetPositionAsyncOpts2 Test>\n"));
	    LogFile.Write(_L8("Failed..\n"));
	    CloseFile();
   		return KErrGeneral;
   		}
   	
    _LIT(Kidentity ,"Coreclass Testing" ) ;
	//not needed any more
	/*RRequestorStack aRequestorStack;
	const CRequestor* identityInfo = CRequestor::NewL(1 , 1 , Kidentity) ;
    aRequestorStack.Insert(identityInfo,0);
    
    CoreObj->SetRequestorIdentityL(aRequestorStack) ;*/
			
   	LocUpdateCallBackOpts2 MyUpdates ;
    aOptions.SetUpdateTimeOut(aTimeOut);
    aOptions.SetUpdateInterval(aInterval);
    
    ret = CoreObj->GetLocationL(&MyUpdates,0,NULL,&aOptions) ;
    
    if( KErrArgument == ret )
    	{
        OpenFile();
		LogFile.Write(_L8("\n<GetPositionAsyncOpts1 test>\n"));
    	LogFile.Write(_L8("Passed\n"));
    	CloseFile();
        returnCode = KErrNone;
	    /*aRequestorStack.Close();
	    delete identityInfo;*/
	    delete CoreObj;
	    return returnCode;	
	   	}
   	
   	else
    	{
        /*aRequestorStack.Close();
	    delete identityInfo;*/
	    delete CoreObj;
    	returnCode = KErrGeneral;
    	return returnCode;
    	}
 }


TInt CSAPILocTest::GetPositionAsyncOpts2( CStifItemParser& /*aItem*/ )
	{
    TRequestStatus status = KRequestPending;
	TInt aRet = KErrNone;
	returnCode = KErrNone;	    
    // Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "GetPositionAsyncOpts2" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
   
    __UHEAP_MARK;
    
    TRAPD(err ,aRet = GetLocFunctionOpts2L()) ;
    if( err || aRet )
    returnCode = KErrGeneral;
  
    __UHEAP_MARKEND;
    
    return returnCode;  
	}



// -----------------------------------------------------------------------------
// CSAPILocTest::GetPositionAsyncOpts3
// -----------------------------------------------------------------------------
//

class LocUpdateCallBackOpts3 : public MLocationCallBack
	{
    TInt iCount ;
    TInt iRetStatus ;
    public :
    TInt HandleNotifyL(HPositionGenericInfo* aOutPos , TInt aError) ;
    LocUpdateCallBackOpts3() :iCount(0) , iRetStatus(KErrGeneral){;}
    };
 
   
TInt LocUpdateCallBackOpts3 :: HandleNotifyL(HPositionGenericInfo* currPos , TInt aError)
	{
    User::After(60000000);
    if(KErrNone == aError)
		 {
		 OpenFile();
		 LogFile.Write(_L8("\n<GetPositionAsyncOpts3 test>\n"));
	     CloseFile();
	     TBuf8<50> buf;
		 TRealFormat format ;
		 TInt64 aTime1;;
		 TTime aTimeStamp1;
		 TPosition currPos1;
		 currPos->GetPosition(currPos1);
		 aTimeStamp1 = currPos1.Time();
	     aTime1 = aTimeStamp1.Int64();
	     buf.Num(aTime1 , format) ;
	     if(aTime1) 
	     	{
	        OpenFile();
	        LogFile.Write(_L8("Time = "));
			LogFile.Write(buf) ;
			LogFile.Write(_L8("\n"));
			CloseFile();
			returnCode = KErrNone;
		    }
		 else
		    {
		    OpenFile();
	        LogFile.Write(_L8("\nFailed to write Time value"));
		    CloseFile();
		    returnCode = KErrGeneral;
		    }
		 }
		
     else
	 	{
	 	OpenFile();
        LogFile.Write(_L8("\nFailed.."));
		CloseFile();
		returnCode = KErrGeneral;
	 	}
		 
	  CActiveScheduler *Current = CActiveScheduler :: Current() ;
	  Current->Stop() ;
	  return KErrNone ;
}


TInt GetLocFunctionOpts3L()
	{
    TInt ret;
    TPositionInfo aPosition1,aPosition2,aPosition3;  
    TPosition aPos1,aPos2,aPos3;
    TPositionUpdateOptions aOptions;
    TTimeIntervalMicroSeconds aTimeOut =  60000000;
	TTimeIntervalMicroSeconds aInterval = 6000000;
	TBool aAcceptPartialUpdates = ETrue;
    
    CLocationService *CoreObj = CLocationService ::NewL() ;
    if( NULL == CoreObj )
    	{
    	OpenFile();
	    LogFile.Write(_L8("\n<GetPositionAsyncOpts3 Test>\n"));
	    LogFile.Write(_L8("Failed..\n"));
	    CloseFile();
   		return KErrGeneral;
   		}
   	
    _LIT(Kidentity ,"Coreclass Testing" ) ;
	//not needed any more
	/*RRequestorStack aRequestorStack;
	const CRequestor* identityInfo = CRequestor::NewL(1 , 1 , Kidentity) ;
    aRequestorStack.Insert(identityInfo,0);
    
    CoreObj->SetRequestorIdentityL(aRequestorStack) ;*/
			
    LocUpdateCallBackOpts3 MyUpdates ;
    
    aOptions.SetUpdateTimeOut(aTimeOut);
    aOptions.SetUpdateInterval(aInterval);
    aOptions.SetAcceptPartialUpdates(aAcceptPartialUpdates);
    
    ret = CoreObj->GetLocationL(&MyUpdates,0,NULL,&aOptions) ;
    
    if( KErrNone == ret)
    	{
    	CActiveScheduler :: Start() ;
	    if( KErrNone == returnCode )
	    	{
		    CoreObj->GetLocationL(&aPosition1,&aOptions);
		    //CoreObj->GetLocationL(&aPosition2,&aOptions);
		    //CoreObj->GetLocationL(&aPosition3,&aOptions);
		    
		    aPosition1.GetPosition(aPos1);
		    
		    returnCode = ValidatePosition(aPos1);
			    
			/*    if( KErrNone == returnCode)
			    	{
			       	aPosition2.GetPosition(aPos2);
			       	returnCode = ValidatePosition(aPos2);
			    	}
			    
			    if( KErrNone == returnCode)
			    	{
			       	aPosition3.GetPosition(aPos3);
			    	returnCode = ValidatePosition(aPos3);
			    	}
		    */
		    //aRequestorStack.Close();
		    
		    delete CoreObj;
			return returnCode;	
	    	}
	    else
	    	{
	    	//aRequestorStack.Close();
			
			delete CoreObj;
	    	return returnCode;
	    	}
	   	}
    
    else
    	{
    	/*aRequestorStack.Close();
	    delete identityInfo;*/
	    delete CoreObj;
    	return KErrGeneral;
    	}
	}


TInt CSAPILocTest::GetPositionAsyncOpts3( CStifItemParser& /*aItem*/ )
{
    
   TRequestStatus status = KRequestPending;
   TInt aRet = KErrNone;
   returnCode = KErrNone;
	    
    // Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "GetPositionAsyncOpts3" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
    
    __UHEAP_MARK;
   
    TRAPD(err , aRet = GetLocFunctionOpts3L()) ;
    if( err || aRet )
    returnCode = KErrGeneral;
   
    __UHEAP_MARKEND;
    
     return returnCode;  
}


// -----------------------------------------------------------------------------
// CSAPILocTest::GetPositionAsyncOpts4
// -----------------------------------------------------------------------------
//

class LocUpdateCallBackOpts4 : public MLocationCallBack
	{
    TInt iCount ;
    TInt iRetStatus ;
    public :
    TInt HandleNotifyL(HPositionGenericInfo* aOutPos , TInt aError) ;
    LocUpdateCallBackOpts4() :iCount(0) , iRetStatus(KErrGeneral){;}
    };
  
   
TInt LocUpdateCallBackOpts4 :: HandleNotifyL(HPositionGenericInfo* currPos , TInt aError)
	{
    User::After(120000000);

    if(KErrNone == aError)
    {
 	TPosition currPos1;
 	currPos->GetPosition(currPos1);
 	
	TBuf8<50> buf;
	TRealFormat format ;
	TInt64 aTime1;
	TTime aTimeStamp1;
	
	aTimeStamp1 = currPos1.Time();
    aTime1 = aTimeStamp1.Int64();
    buf.Num(aTime1 , format) ;
    
    if(aTime1) 
    	{
      	OpenFile();
        LogFile.Write(_L8("Time = "));
	    LogFile.Write(buf) ;
	    LogFile.Write(_L8("\n"));
	    CloseFile();
	    returnCode = KErrNone;
     	}
    else
    	{
    	OpenFile();
        LogFile.Write(_L8("\nFailed(No TimeStamp).. "));
	    CloseFile();
	    returnCode = KErrGeneral;
    	}
	}
	
 else
 	{
 	OpenFile();
    LogFile.Write(_L8("\nFailed(HandleNotifyL error).."));
	CloseFile();
	returnCode = KErrGeneral;
 	}
	 
  CActiveScheduler *Current = CActiveScheduler :: Current() ;
  Current->Stop() ;
  return returnCode ;
}


TInt GetLocFunctionOpts4L()
{
    TInt ret;
    TPositionInfo aPosition1;  
    TPosition aPos1;
    TPositionUpdateOptions aOptions;
    TTimeIntervalMicroSeconds aTimeOut =  10000000;
	TTimeIntervalMicroSeconds aInterval = 6000000;
	TBool aAcceptPartialUpdates = EFalse;
    
    CLocationService *CoreObj = CLocationService ::NewL() ;
    
    if( NULL == CoreObj )
    	{
    	OpenFile();
	    LogFile.Write(_L8("\n<GetPositionAsyncOpts4 Test>\n"));
	    LogFile.Write(_L8("Failed(Null CoreObj)..\n"));
	    CloseFile();
   		return KErrGeneral;
   		}
    
    _LIT(Kidentity ,"Coreclass Testing" ) ;
	//not needed any more
	/*RRequestorStack aRequestorStack;
	const CRequestor* identityInfo = CRequestor::NewL(1 , 1 , Kidentity) ;
    aRequestorStack.Insert(identityInfo,0);
    
    CoreObj->SetRequestorIdentityL(aRequestorStack) ;*/
		
    LocUpdateCallBackOpts4 MyUpdates ;
    
    aOptions.SetUpdateTimeOut(aTimeOut);
    aOptions.SetUpdateInterval(aInterval);
    aOptions.SetAcceptPartialUpdates(aAcceptPartialUpdates);
    
   	OpenFile();
	LogFile.Write(_L8("\n<GetPositionAsyncOpts4 test>\n"));
	CloseFile();
    ret = CoreObj->GetLocationL(&MyUpdates,0,NULL,&aOptions) ;
    if( KErrNone == ret)
    	{
    	CActiveScheduler :: Start() ;
	    if( KErrNone == returnCode )
		    {
		    CoreObj->GetLocationL(&aPosition1,&aOptions);
		    aPosition1.GetPosition(aPos1);
		    
		   // ValidatePosition(aPos1);
	
			/*aRequestorStack.Close();
		    delete identityInfo;*/
		    delete CoreObj;
			return returnCode;	
		    }
		  else
		  	{
		  	/*aRequestorStack.Close();
		    delete identityInfo;*/
		    delete CoreObj;
		  	return returnCode;
		  	}
    	}
    
    else
    	{
    	/*aRequestorStack.Close();
	    delete identityInfo;*/
	    delete CoreObj;
    	return returnCode;
    	}
}


TInt CSAPILocTest::GetPositionAsyncOpts4( CStifItemParser& /*aItem*/ )
	{
    
    TInt aRet = KErrNone;
    returnCode = KErrNone;
    // Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "GetPositionAsyncOpts4" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
    
    __UHEAP_MARK;
    
    TRAPD(err , aRet = GetLocFunctionOpts4L()) ;
    if( err )
    returnCode = KErrGeneral; 
    
    __UHEAP_MARKEND;
    
     return returnCode;  
	}


// -----------------------------------------------------------------------------
// CSAPILocTest::GetPositionAsyncOpts5
// -----------------------------------------------------------------------------
//

TInt GetLocFunctionOpts5L()
	{
    TInt ret1,ret2;
    TPositionInfo aPosition1,aPosition2,aPosition3;  
    TPosition aPos1,aPos2,aPos3;
    TPositionUpdateOptions aOptions;
    TTimeIntervalMicroSeconds aTimeOut =  10000000;
	TTimeIntervalMicroSeconds aInterval = 6000000;
	TBool aAcceptPartialUpdates = ETrue;
    
    CLocationService *CoreObj = CLocationService ::NewL() ;
    if( NULL == CoreObj )
    	{
    	OpenFile();
	    LogFile.Write(_L8("\n<GetPositionAsyncOpts5 Test>\n"));
	    LogFile.Write(_L8("Failed(CoreObj Creation)..\n"));
	    CloseFile();
   		return KErrGeneral;
   		}
    
    _LIT(Kidentity ,"Coreclass Testing" ) ;
	//not needed any more
	/*RRequestorStack aRequestorStack;
	const CRequestor* identityInfo = CRequestor::NewL(1 , 1 , Kidentity) ;
    aRequestorStack.Insert(identityInfo,0);
    
    CoreObj->SetRequestorIdentityL(aRequestorStack) ;*/
		
    LocUpdateCallBackOpts4 MyUpdates1 ;
    LocUpdateCallBackOpts4 MyUpdates2 ;
    
    aOptions.SetUpdateTimeOut(aTimeOut);
    aOptions.SetUpdateInterval(aInterval);
    aOptions.SetAcceptPartialUpdates(aAcceptPartialUpdates);
    
   	OpenFile();
	LogFile.Write(_L8("\n<GetPositionAsyncOpts5 test>\n"));
	CloseFile();
	
	ret1 = CoreObj->GetLocationL(&MyUpdates1) ;
    
    ret2 = CoreObj->GetLocationL(&MyUpdates2) ;
    
    if( KErrNone == ret1 && KErrInUse == ret2 )
    	{
    	TBuf8<20> retBuf;
    	TRealFormat retFormat;
    	
    	CActiveScheduler :: Start() ;
		
		OpenFile();
		LogFile.Write(_L8("\nreturnCode : "));
		LogFile.Write(retBuf);
		CloseFile();
		}
    
    else
    	{
    	returnCode = KErrGeneral;	
    	}
    //aRequestorStack.Close();
    
    delete CoreObj;
    return 0;
	}


TInt CSAPILocTest::GetPositionAsyncOpts5( CStifItemParser& /*aItem*/ )
	{
     TInt aRet = KErrNone;
     returnCode = KErrNone;
     // Print to UI
     _LIT( KSAPILocTest, "SAPILocTest" );
     _LIT( KExample, "GetPositionAsyncOpts5" );
     TestModuleIf().Printf( 0, KSAPILocTest, KExample );
    
     __UHEAP_MARK;
   
    TRAPD(err ,aRet =  GetLocFunctionOpts5L()) ;
    if( err || aRet )
    returnCode = KErrGeneral;
   
    __UHEAP_MARKEND;
   
    return returnCode;  
	}



// -----------------------------------------------------------------------------
// CSAPILocTest::GetPositionAsyncOpts6
// -----------------------------------------------------------------------------
//
TInt GetLocFunctionOpts6L()
	{
    TInt aRet,aRet1;
    TPosition aPosition1;  
    TPositionUpdateOptions aOptions;
    TTimeIntervalMicroSeconds aTimeOut =  60000000;
	TTimeIntervalMicroSeconds aInterval = 6000000;
	TBool aAcceptPartialUpdates = ETrue;
    
    CLocationService *CoreObj = CLocationService ::NewL() ;
    if( NULL == CoreObj )
    	{
    	OpenFile();
	    LogFile.Write(_L8("\n<GetPositionAsyncOpts6 Test>\n"));
	    LogFile.Write(_L8("Failed(Null CoreObj)..\n"));
	    CloseFile();
   		return KErrGeneral;
   		}
   
    _LIT(Kidentity ,"Coreclass Testing" ) ;
	//not needed any more
	/*RRequestorStack aRequestorStack;
	const CRequestor* identityInfo = CRequestor::NewL(1 , 1 , Kidentity) ;
    aRequestorStack.Insert(identityInfo,0);
    
    CoreObj->SetRequestorIdentityL(aRequestorStack) ;*/
				
    LocUpdateCallBackOpts2 MyUpdates ;
    
    aOptions.SetUpdateTimeOut(aTimeOut);
    aOptions.SetUpdateInterval(aInterval);
    aOptions.SetAcceptPartialUpdates(aAcceptPartialUpdates);
    
    aRet = CoreObj->GetLocationL(&MyUpdates) ;
    
    if( KErrNone == aRet )
    	{
    	aRet1 = CoreObj->CancelOnGoingService(0);
    	if( KErrNone == aRet1 )
    		{
    	    TBuf8<20> retBuf;
    	    TRealFormat retFormat;
    	    aRet = CoreObj->GetLocationL(&MyUpdates) ;
    	    if( KErrNone == aRet)
    	    OpenFile();
		 	LogFile.Write(_L8("\n<GetPositionAsyncOpts6 test>\n"));
    	 	CloseFile();
    	    CActiveScheduler :: Start() ;
    		retBuf.Num(returnCode,retFormat);
    		OpenFile();
    		LogFile.Write(_L8("\nreturnCode : "));
    		LogFile.Write(retBuf);
    		CloseFile();
    		}
    	else
    		{
    		returnCode = KErrGeneral;
    		}
    	}
    else
    	{
    	returnCode = KErrGeneral;	
    	}
    
    //aRequestorStack.Close();
	
	delete CoreObj;
    return 0;
	}


TInt CSAPILocTest::GetPositionAsyncOpts6( CStifItemParser& /*aItem*/ )
	{
    TInt aRet = KErrNone;
    returnCode = KErrNone;
   
    // Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "GetPositionAsyncOpts6" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
    
    __UHEAP_MARK;
    
    TRAPD(err , aRet = GetLocFunctionOpts6L()) ;
    
    __UHEAP_MARKEND;
   
    return returnCode;  
	}


// -----------------------------------------------------------------------------
// CSAPILocTest::TraceLPosition
// -----------------------------------------------------------------------------
//

class TraceLCallBack : public MLocationCallBack
	{
    TInt iCount ;
    TInt iRetStatus ;
    public :
    TInt HandleNotifyL(HPositionGenericInfo* aOutPos , TInt aError) ;
    TraceLCallBack() :iCount(0) , iRetStatus(KErrGeneral){;}
    };
  
  
  
TInt TraceLCallBack :: HandleNotifyL(HPositionGenericInfo* currPos , TInt aError)
	{
//	User::After(60000000);
	if(KErrNone == aError && iCount<2)
		{
		TPosition currPos1;
		currPos->GetPosition(currPos1);
	//	ValidatePosition(currPos1);
	    iCount++;	 
		}
	 else
	 	{
	 	 CActiveScheduler *Current = CActiveScheduler :: Current() ;
	  	 Current->Stop() ;
	  	// returnCode = KErrNone;
	  	}
	 return returnCode;
	 }
	 

TInt TraceLFunctionL()
	{
    TInt ret;
    TPosition aPosition1;  
    
    CLocationService *CoreObj = CLocationService ::NewL() ;
    if( NULL == CoreObj )
    	{
    	OpenFile();
	    LogFile.Write(_L8("\n<TraceLPosition Test>\n"));
	    LogFile.Write(_L8("Failed..\n"));
	    CloseFile();
   		return KErrGeneral;
   		}
    
    _LIT(Kidentity ,"Coreclass Testing" ) ;
	//not needed any more
	/*RRequestorStack aRequestorStack;
	const CRequestor* identityInfo = CRequestor::NewL(1 , 1 , Kidentity) ;
    aRequestorStack.Insert(identityInfo,0);
    
    CoreObj->SetRequestorIdentityL(aRequestorStack) ;*/
		
    TraceLCallBack MyUpdates ;
    
    ret = CoreObj->TraceL(&MyUpdates) ;
    if( KErrNone == ret)
    	{
        TBuf8<20> retBuf;
        TRealFormat retFormat;
        
        OpenFile();
	 	LogFile.Write(_L8("\n<TraceLPosition test>\n"));
	 	CloseFile();
        CActiveScheduler :: Start() ;
		
		retBuf.Num(returnCode,retFormat);
		OpenFile();
		LogFile.Write(_L8("\nreturnCode : "));
		LogFile.Write(retBuf);
		CloseFile();
		}
    else
    	{
    	returnCode = KErrGeneral;	
    	}
    
 	//aRequestorStack.Close();
    
    delete CoreObj;
	return 0;
	}	


TInt CSAPILocTest::TraceLPosition( CStifItemParser& /*aItem*/ )
	{
    TInt aRet = KErrNone;
    returnCode = KErrNone;
   
    // Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "TraceLPosition" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
    
    __UHEAP_MARK;
    
    TRAPD(err ,aRet = TraceLFunctionL() ) ;
    
    if( err || aRet )
    returnCode = KErrGeneral;
    
    __UHEAP_MARKEND;
  
     return returnCode;  
	}


// -----------------------------------------------------------------------------
// CSAPILocTest::TraceLPosition1
// -----------------------------------------------------------------------------
//
TInt TraceLFunction1L()
	{
    TInt ret1,ret2;
    TPosition aPosition1;  
    
    CLocationService *CoreObj = CLocationService ::NewL() ;
    if( NULL == CoreObj )
    	{
    	OpenFile();
	    LogFile.Write(_L8("\n<TraceLPosition1 Test>\n"));
	    LogFile.Write(_L8("Failed(Null CoreObj)..\n"));
	    CloseFile();
   		return KErrGeneral;
   		}
    
    _LIT(Kidentity ,"Coreclass Testing" ) ;
	//not needed any more
	/*RRequestorStack aRequestorStack;
	const CRequestor* identityInfo = CRequestor::NewL(1 , 1 , Kidentity) ;
    aRequestorStack.Insert(identityInfo,0);
    
    CoreObj->SetRequestorIdentityL(aRequestorStack) ;*/
		
    TraceLCallBack MyUpdates ;
    
    ret1 = CoreObj->TraceL(&MyUpdates) ;
    ret2 = CoreObj->TraceL(&MyUpdates) ;
    
    if( KErrNone == ret1 && KErrInUse == ret2)
    	{
        TBuf8<20> retBuf;
        TRealFormat retFormat;
        
        OpenFile();
	 	LogFile.Write(_L8("\n<TraceLPosition1 test>\n"));
	 	CloseFile();
        
        CActiveScheduler :: Start() ;
		
		retBuf.Num(returnCode,retFormat);
		OpenFile();
		LogFile.Write(_L8("\nreturnCode : "));
		LogFile.Write(retBuf);
		CloseFile();
		}
    
    else
      	{
    	returnCode = KErrGeneral;	
    	}
    //aRequestorStack.Close();
    
    delete CoreObj;
    return 0;
	}


TInt CSAPILocTest::TraceLPosition1( CStifItemParser& /*aItem*/ )
	{
     TInt aRet = KErrNone;
     returnCode = KErrNone;
     
    // Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "TraceLPosition1" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
    
    __UHEAP_MARK;
    
    TRAPD(err ,aRet = TraceLFunction1L()) ;
    
    if( err || aRet )
    returnCode = KErrGeneral;
    
    __UHEAP_MARKEND;
    
     return returnCode;  
	}


// -----------------------------------------------------------------------------
// CSAPILocTest::TraceLPosition2
// -----------------------------------------------------------------------------
//

class TraceLCallBack2 : public MLocationCallBack
	{
    TInt iCount ;
    TInt iRetStatus ;
    CLocationService *CoreObj;
    public :
    TInt HandleNotifyL(HPositionGenericInfo* aOutPos , TInt aError) ;
    TraceLCallBack2(CLocationService* LocObj,TInt count = 0,TInt status = KErrGeneral)
   		{
   	    iCount = count;
   	    iRetStatus = status;
   	    CoreObj = LocObj;	
   		}
 	};
  
  
  
TInt TraceLCallBack2 :: HandleNotifyL(HPositionGenericInfo* currPos , TInt aError)
	{
//	 User::After(60000000);
	 TInt aRet1;
	 if(KErrNone == aError && iCount<2)
	 	{
	  	TBuf8<20> retBuf;
        TRealFormat retFormat;
        retBuf.Num(aError,retFormat);
        
        OpenFile();
	 	LogFile.Write(_L8("\n<TraceLPosition2 HandleNotifyL>\n"));
	 	LogFile.Write(retBuf);
	 	CloseFile();
	  	TPosition currPos1;
	  	currPos->GetPosition(currPos1);
	  //	ValidatePosition(currPos1);
    	iCount++;	 
	 	
	 	}
		
     else
	 	{
	 	aRet1 = CoreObj->CancelOnGoingService(1);
    		TBuf8<20> retBuf;
        TRealFormat retFormat;
        retBuf.Num(aRet1,retFormat);
        
        OpenFile();
	 	LogFile.Write(_L8("\n<TraceLPosition2 CancelOnGoingService>\n"));
	 	LogFile.Write(retBuf);
	 	CloseFile();
    	if( KErrNone == aRet1 )
    		{
    		returnCode = KErrNone;
    		CActiveScheduler *Current = CActiveScheduler :: Current() ;
	  	    Current->Stop() ;
       		}
    	else
    		{
    		returnCode = KErrGeneral;
    		CActiveScheduler *Current = CActiveScheduler :: Current() ;
	  	    Current->Stop() ;
    		}
    			
	 	}
	return KErrNone; 
	}


TInt TraceLFunction2L()
	{
    TInt ret;
    TPosition aPosition1;  
    
    CLocationService *CoreObj = CLocationService ::NewL() ;
    if( NULL == CoreObj )
    	{
    	OpenFile();
	    LogFile.Write(_L8("\n<TraceLPosition2 Test>\n"));
	    LogFile.Write(_L8("Failed(CoreObj Creation)..\n"));
	    CloseFile();
   		return KErrGeneral;
   		}
    
    _LIT(Kidentity ,"Coreclass Testing" ) ;
    //not needed any more
	
	/*RRequestorStack aRequestorStack;
	const CRequestor* identityInfo = CRequestor::NewL(1 , 1 , Kidentity) ;
    aRequestorStack.Insert(identityInfo,0);
    
    CoreObj->SetRequestorIdentityL(aRequestorStack) ;*/
		
    TraceLCallBack2 MyUpdates(CoreObj) ;
    
    ret = CoreObj->TraceL(&MyUpdates) ;
    
    if( KErrNone == ret)
    	{
        TBuf8<20> retBuf;
        TRealFormat retFormat;
        OpenFile();
	 	LogFile.Write(_L8("\n<TraceLPosition2 test>\n"));
	 	CloseFile();
        CActiveScheduler :: Start() ;
        retBuf.Num(returnCode,retFormat);
        OpenFile();
        LogFile.Write(_L8("\nreturnCode : "));
        LogFile.Write(retBuf);
        CloseFile();
		}
    else
    	{
    	returnCode = KErrGeneral;	
    	}
    	
    //aRequestorStack.Close();
	
	delete CoreObj;
    return 0;
	}


TInt CSAPILocTest::TraceLPosition2( CStifItemParser& /*aItem*/ )
	{
    TInt aRet = KErrNone;
    returnCode = KErrNone; 
   
    // Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "TraceLPosition2" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
    
    __UHEAP_MARK;
    
    TRAPD(err , aRet = TraceLFunction2L()) ;
    if( err || aRet )
    returnCode = KErrGeneral;
    
     __UHEAP_MARKEND;
    
     return returnCode;  
	}


// -----------------------------------------------------------------------------
// CSAPILocTest::TraceLPosition3
// -----------------------------------------------------------------------------
//
TInt TraceLFunction3L()
	{
    TInt ret1,ret2,ret3;
    TPosition aPosition1;  
    
    CLocationService *CoreObj = CLocationService ::NewL() ;
    if( NULL == CoreObj )
    	{
    	OpenFile();
	    LogFile.Write(_L8("\n<TraceLPosition3 Test>\n"));
	    LogFile.Write(_L8("Failed(Null CoreObj)..\n"));
	    CloseFile();
   		return KErrGeneral;
   		}
   	
    _LIT(Kidentity ,"Coreclass Testing" ) ;
    //not needed any more
	
	/*RRequestorStack aRequestorStack;
	const CRequestor* identityInfo = CRequestor::NewL(1 , 1 , Kidentity) ;
    aRequestorStack.Insert(identityInfo,0);
    
    CoreObj->SetRequestorIdentityL(aRequestorStack) ;*/
			
    TraceLCallBack MyUpdates ;
    
    ret1 = CoreObj->TraceL(&MyUpdates) ;
    
    ret2 = CoreObj->TraceL(&MyUpdates) ;
    
    if( KErrNone == ret1 && KErrInUse == ret2)
    	{
        ret3 = CoreObj->CancelOnGoingService(1);
        
        if( KErrNone == ret3 )
            {
        	TBuf8<20> retBuf;
        	TRealFormat retFormat;
        	OpenFile();
		 	LogFile.Write(_L8("\n<TraceLPosition3 test>\n"));
		 	CloseFile();
		 	ret1 = CoreObj->TraceL(&MyUpdates) ;
		 	if(KErrNone == ret1)
	        CActiveScheduler :: Start() ;
        	retBuf.Num(returnCode,retFormat);
			OpenFile();
			LogFile.Write(_L8("\nreturnCode : "));
			LogFile.Write(retBuf);
			CloseFile();
			}
        else
        	{
        	returnCode = KErrGeneral;
        	}
    	}
    
    else
   		{
		returnCode = KErrGeneral;
   		}
	
    //aRequestorStack.Close();
    
    delete CoreObj;
	return KErrNone;
	}


TInt CSAPILocTest::TraceLPosition3( CStifItemParser& /*aItem*/ )
	{
    TInt aRet = KErrNone;
    returnCode = KErrNone;
    
    // Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "TraceLPosition3" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
    
    __UHEAP_MARK;
    
    TRAPD(err , aRet = TraceLFunction3L()) ;
    if( err || aRet )
      returnCode = KErrGeneral;
   
    __UHEAP_MARKEND;
    
    return returnCode;  
	}

// -----------------------------------------------------------------------------
// CSAPILocTest::TraceLPosition4
// -----------------------------------------------------------------------------
//
class TraceLCallBack4 : public MLocationCallBack
	{
    TInt iCount ;
    TInt iRetStatus ;
    TInt iCallIdentity;
    public :
    TInt HandleNotifyL(HPositionGenericInfo* aOutPos , TInt aError) ;
    TraceLCallBack4(TInt identity, TInt count = 0 , TInt status = KErrGeneral)
   		{
   		iCallIdentity = identity;
   		iCount = count;
        iRetStatus = status;  
   		}
    };
 
  
TInt TraceLCallBack4 :: HandleNotifyL(HPositionGenericInfo* currPos , TInt aError)
	{
	  if(iCallIdentity == 1 && KErrNone == aError )
	  	{
	  	TPosition currPos1;
	  	currPos->GetPosition(currPos1);
	//  	ValidatePosition(currPos1);
    //  	returnCode = KErrNone ;
	  	}
	  else if(KErrNone == aError && iCount<2)
	  	{
		 TPosition currPos1;
		 currPos->GetPosition(currPos1);
	//	 ValidatePosition(currPos1);
	     iCount++;	 
	  	}
			
  	  else if(iCount>=2)
	  	{
		CActiveScheduler *Current = CActiveScheduler :: Current() ;
  	    Current->Stop() ;
  	    returnCode = KErrNone; 
	  	}
	  else
	  	{
	  	returnCode = KErrGeneral;	
	  	}
	  	
	return returnCode;
	}
	
TInt TraceLFunction4L()
	{
    TInt ret1,ret2;
    TPosition aPosition1;  
    
    CLocationService *CoreObj = CLocationService ::NewL() ;
    
    TraceLCallBack4 MyUpdates1(1) ;
    
    TraceLCallBack4 MyUpdates2(2) ;
    
    _LIT(Kidentity ,"Coreclass Testing" ) ;
    //not needed any more
	
	/*RRequestorStack aRequestorStack;
	const CRequestor* identityInfo = CRequestor::NewL(1 , 1 , Kidentity) ;
    aRequestorStack.Insert(identityInfo,0);
    
    CoreObj->SetRequestorIdentityL(aRequestorStack) ;*/
		
    ret1 = CoreObj->GetLocationL(&MyUpdates1) ;
    
    ret2 = CoreObj->TraceL(&MyUpdates2) ;
    
    
    if( KErrNone == ret1 && KErrNone == ret2)
    	{
       	TBuf8<50> buf ;
		TRealFormat format ;
		
       	OpenFile();
	 	LogFile.Write(_L8("\n<TraceLPosition4 test>\n"));
	 	CActiveScheduler :: Start() ;
    	
	    //Logging returnCode 
		buf.Num(returnCode , format) ;
		LogFile.Write(_L8("returnCode = "));
		LogFile.Write(buf) ;
		LogFile.Write(_L8("\n")) ;
	    CloseFile();
	    }
    else
    	{
      	returnCode = KErrGeneral;
    	}
    //aRequestorStack.Close();
	
	delete CoreObj;
    return KErrNone;
        
	}



TInt CSAPILocTest::TraceLPosition4( CStifItemParser& /*aItem*/ )
	{
    TInt aRet = KErrNone;
    returnCode = KErrNone;
    
    // Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "TraceLPosition4" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
    
    __UHEAP_MARK;
    
    TRAPD(err ,aRet = TraceLFunction4L()) ;
    if( err || aRet )
    returnCode = KErrGeneral;
    
    __UHEAP_MARKEND;
    
     return returnCode;  
	}


// -----------------------------------------------------------------------------
// CSAPILocTest::TraceLPosition5
// -----------------------------------------------------------------------------
//

class CTraceLCallBack5 : public CBase , public MLocationCallBack 
	{
   TInt iCount ;
   TInt iRetStatus ;
   CLocationService *CoreObj;
   CTraceLCallBack5* iSelf;  
   public :
   TInt HandleNotifyL(HPositionGenericInfo* aOutPos , TInt aError) ;
   CTraceLCallBack5(CLocationService* LocObj,TInt count = 0,TInt status = KErrGeneral)
   		{
   	    iCount = count;
   	    iRetStatus = status;
   	    CoreObj = LocObj;	
   		}
   
   virtual ~CTraceLCallBack5();
   static CTraceLCallBack5* NewL(CLocationService*) ;
 	};
  
 CTraceLCallBack5* CTraceLCallBack5 :: NewL(CLocationService* obj)
 	{
 	CTraceLCallBack5* temp = new(ELeave) CTraceLCallBack5(obj);
 	temp->iSelf = temp;
 	return temp;
 	}
 
 CTraceLCallBack5 :: ~CTraceLCallBack5()
 	{
  	delete (this->CoreObj);
  	}
  
TInt CTraceLCallBack5 :: HandleNotifyL(HPositionGenericInfo* currPos , TInt aError)
	{
	 User::After(30000000);
	 TInt aRet1;
	 if(KErrNone == aError && iCount<2)
	 	{
	    TPosition currPos1;
	    currPos->GetPosition(currPos1);
	    ValidatePosition(currPos1);
        iCount++;	 
	 	}
		
     else
	 	{
	   	aRet1 = CoreObj->CancelOnGoingService(1);
    	if( KErrNone == aRet1 )
    		{	
    		returnCode = KErrNone;
    		delete this;
    		CActiveScheduler *Current = CActiveScheduler :: Current() ;
    		Current->Stop() ;
       		}
    	else
    		{
    		returnCode = KErrGeneral;
       		delete this;
       		CActiveScheduler *Current = CActiveScheduler :: Current() ;
    		Current->Stop() ;
       		}	
	 	}
	
	return KErrNone; 
	}
	
class LocUpdateCallBack5 : public MLocationCallBack
 	{
    TInt iCount ;
    TInt iRetStatus ;
    public :
    TInt HandleNotifyL(HPositionGenericInfo* aOutPos , TInt aError) ;
    LocUpdateCallBack5() :iCount(0) , iRetStatus(KErrGeneral){;}
  	};
  
    
TInt LocUpdateCallBack5 :: HandleNotifyL(HPositionGenericInfo* currPos , TInt /*aError*/)
	{
	  
	 TInt aRet;
	 TPosition currPos1;
	 currPos->GetPosition(currPos1);
	 aRet = ValidatePosition(currPos1);
     
     if ( KErrNone == aRet )
     	{
      	TPosition aPosition2;  
	    CLocationService *CoreObj1 = CLocationService ::NewL() ;
	    
	    _LIT(Kidentity ,"Coreclass Testing" ) ;
		//not needed any more
		/*RRequestorStack aRequestorStack;
		const CRequestor* identityInfo = CRequestor::NewL(1 , 1 , Kidentity) ;
	    aRequestorStack.Insert(identityInfo,0);
	    
	    CoreObj1->SetRequestorIdentityL(aRequestorStack) ;*/
		
	    CTraceLCallBack5 *MyUpdates2 = CTraceLCallBack5::NewL(CoreObj1);
	    
	    CoreObj1->TraceL(MyUpdates2) ;
	    
	    //aRequestorStack.Close();
		
	    }
     return KErrNone ;
	}


TInt TraceLFunction5L()
	{
    TInt ret1;
    TPosition aPosition1;  
    CLocationService *CoreObj = CLocationService ::NewL() ;
    LocUpdateCallBack5 MyUpdates1 ;
    
    _LIT(Kidentity ,"Coreclass Testing" ) ;
	//not needed any more
	/*RRequestorStack aRequestorStack;
	const CRequestor* identityInfo = CRequestor::NewL(1 , 1 , Kidentity) ;
    aRequestorStack.Insert(identityInfo,0);
    
    CoreObj->SetRequestorIdentityL(aRequestorStack) ;*/
		
    ret1 = CoreObj->GetLocationL(&MyUpdates1) ;
    
    if( KErrNone == ret1)
    	{
       	TBuf8<20> retBuf;
       	TRealFormat retFormat;
       	OpenFile();
	 	LogFile.Write(_L8("\n<TraceLPosition5 test>\n"));
	 	CloseFile();
	 	CActiveScheduler :: Start() ;
    	retBuf.Num(returnCode,retFormat);
    	OpenFile();
    	LogFile.Write(_L8("\nreturn code : "));
    	LogFile.Write(retBuf);
    	CloseFile();
    	}
    else
    	{
      	returnCode = KErrGeneral;
    	}
    
    //aRequestorStack.Close();
	
	delete CoreObj;
    return KErrNone;
	}

TInt CSAPILocTest::TraceLPosition5( CStifItemParser& /*aItem*/ )
	{
    returnCode = KErrNone;
    // Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "TraceLPosition5" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
    
    __UHEAP_MARK;
    
    TRAPD(err , TraceLFunction5L()) ;
    if(err)
    returnCode = KErrGeneral;
    
     __UHEAP_MARKEND;
  
     return returnCode;  
	}

// -----------------------------------------------------------------------------
// CSAPILocTest::TraceLPosition6
// -----------------------------------------------------------------------------
//

class CLocUpdateCallBack6 : public CBase , public MLocationCallBack
	{
    TInt iCount ;
    TInt iRetStatus ;
    CLocUpdateCallBack6* iSelf;
    CLocationService *CoreObj;
    public :
    TInt HandleNotifyL(HPositionGenericInfo* aOutPos , TInt aError) ;
    CLocUpdateCallBack6(CLocationService* LocObj,TInt count = 0,TInt status = KErrGeneral) 
   		{
    	iCount = count;
   	    iRetStatus = status;
   	 	CoreObj = LocObj;	
   		}
    static CLocUpdateCallBack6* NewL(CLocationService* obj);
    virtual ~CLocUpdateCallBack6();
  	};
  
 CLocUpdateCallBack6* CLocUpdateCallBack6 :: NewL(CLocationService* obj)
 	{
 	CLocUpdateCallBack6* temp = new(ELeave) CLocUpdateCallBack6(obj);
 	temp->iSelf = temp;
 	return temp;
 	}
 
 CLocUpdateCallBack6 :: ~CLocUpdateCallBack6()
	 {
 	 delete (this->CoreObj);
 	 }
TInt CLocUpdateCallBack6 :: HandleNotifyL(HPositionGenericInfo* currPos , TInt /*aError*/)
	{
	TInt aRet;
	TPosition currPos1;
	
	currPos->GetPosition(currPos1);
	
	aRet = ValidatePosition(currPos1);
    
    if( KErrNone == aRet )
    	{
      	CActiveScheduler *Current = CActiveScheduler :: Current() ;
	  	Current->Stop() ;
        returnCode = KErrNone;
        delete this;
        }
    else  
	    {
	 	CActiveScheduler *Current = CActiveScheduler :: Current() ;
	 	Current->Stop() ;
	  	returnCode = KErrGeneral;
	  	delete this;
	    }
    return KErrNone ;
 	}
 	
class TraceLCallBack6 : public MLocationCallBack
 	{
  	TInt iCount ;
    TInt iRetStatus ;
    CLocationService *CoreObj;
    public :
    TInt HandleNotifyL(HPositionGenericInfo* aOutPos , TInt aError) ;
    TraceLCallBack6(CLocationService* LocObj,TInt count = 0,TInt status = KErrGeneral)
   		{
   	 	iCount = count;
   	 	iRetStatus = status;
   	 	CoreObj = LocObj;	
   		}
 	};
  
    
TInt TraceLCallBack6 :: HandleNotifyL(HPositionGenericInfo* currPos , TInt aError)
	{
	 TInt aRet1;
	 if(KErrNone == aError && iCount<1)
	 	{
	    TPosition currPos1;
	   	currPos->GetPosition(currPos1);
	   	ValidatePosition(currPos1);
    	iCount++;	 
	 	}
		
     else
	 	{
	   	aRet1 = CoreObj->CancelOnGoingService(1);
    	
    	if( KErrNone == aRet1 )
    		{
    		TPosition aPosition2;  
		    CLocationService *CoreObj1 = CLocationService ::NewL() ;
		    
	    	_LIT(Kidentity ,"Coreclass Testing" ) ;
			//not needed any more
			/*RRequestorStack aRequestorStack;
			const CRequestor* identityInfo = CRequestor::NewL(1 , 1 , Kidentity) ;
		    aRequestorStack.Insert(identityInfo,0);
		    
		    CoreObj1->SetRequestorIdentityL(aRequestorStack) ;*/
    
		    CLocUpdateCallBack6 *MyUpdates1 =  CLocUpdateCallBack6 :: NewL(CoreObj1);
		    
		    CoreObj1->GetLocationL(MyUpdates1) ;
		    
		    //aRequestorStack.Close();
    		
		    
		    returnCode = KErrNone;
    		}
    	else
    		{
    		returnCode = KErrGeneral;
       		}	
	 	}
	return KErrNone; 
	}
  
  
TInt TraceLFunction6L()
	{
    TInt ret1;
    TPosition aPosition1;  
    CLocationService *CoreObj = CLocationService ::NewL() ;
    TraceLCallBack6 MyUpdates2(CoreObj) ;
    
    _LIT(Kidentity ,"Coreclass Testing" ) ;
	//not needed any more
	/*RRequestorStack aRequestorStack;
	const CRequestor* identityInfo = CRequestor::NewL(1 , 1 , Kidentity) ;
    aRequestorStack.Insert(identityInfo,0);
    
    CoreObj->SetRequestorIdentityL(aRequestorStack) ;*/
    
    ret1 = CoreObj->TraceL(&MyUpdates2) ;
    
    if( KErrNone == ret1)
    	{	
       	OpenFile();
	 	LogFile.Write(_L8("\n<TraceLPosition6 test>\n"));
	 	CloseFile();
	 	CActiveScheduler :: Start() ;
    	}
    else
    	{
      	returnCode = KErrGeneral;
    	}
   
    //aRequestorStack.Close();
    
    delete CoreObj;
   return KErrNone;
   }



TInt CSAPILocTest::TraceLPosition6( CStifItemParser& /*aItem*/ )
	{
    returnCode = KErrNone;
     // Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "TraceLPosition6" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
    
   __UHEAP_MARK;
   
   TRAPD(err , TraceLFunction6L()) ;
   if(err)
   returnCode = KErrGeneral;
   
   __UHEAP_MARKEND;
    
   return returnCode;  
	}
	
	
// -----------------------------------------------------------------------------
// CSAPILocTest::TraceLPosition7
// -----------------------------------------------------------------------------
//
 	
class TraceLCallBack7 : public MLocationCallBack
 	{
  	TInt iCount ;
    TInt iRetStatus ;
    CLocationService *CoreObj;
    public :
    TInt HandleNotifyL(HPositionGenericInfo* aOutPos , TInt aError) ;
    TraceLCallBack7(CLocationService* LocObj,TInt count = 0,TInt status = KErrGeneral)
   		{
   	 	iCount = count;
   	 	iRetStatus = status;
   	 	CoreObj = LocObj;	
   		}
 	};
  
    
TInt TraceLCallBack7 :: HandleNotifyL(HPositionGenericInfo* currPos , TInt aError)
	{
	 User::After(30000000);
	 TInt aRet1;
	 if(KErrNone == aError && iCount<2)
	 	{
	   	TPosition currPos1;
	   	currPos->GetPosition(currPos1);
	//   	ValidatePosition(currPos1);
    	iCount++;	 
	 	}
		
     else
	 	{
	   	aRet1 = CoreObj->CancelOnGoingService(1);
    	if( KErrNone == aRet1 )
    		{
    		TPosition aPosition2;  
		    CLocationService *CoreObj1 = CLocationService ::NewL() ;
		    
		    _LIT(Kidentity ,"Coreclass Testing" ) ;
			//not needed any more
			/*RRequestorStack aRequestorStack;
			const CRequestor* identityInfo = CRequestor::NewL(1 , 1 , Kidentity) ;
		    aRequestorStack.Insert(identityInfo,0);
		    
		    CoreObj1->SetRequestorIdentityL(aRequestorStack) ;*/
    
		    CTraceLCallBack5 *MyUpdates2 = CTraceLCallBack5::NewL(CoreObj1);
	    	
	    	CoreObj1->TraceL(MyUpdates2) ;
		    
		    User::After(30000000) ;
		    //aRequestorStack.Close();
    		
		    
		    returnCode = KErrNone;
    		}
    	else
    		{
    		returnCode = KErrGeneral;
       		}	
	 	}
	return KErrNone; 
	}
  
  
TInt TraceLFunction7L()
	{
    TInt ret1;
    TPosition aPosition1;  
    CLocationService *CoreObj = CLocationService ::NewL() ;
    
    _LIT(Kidentity ,"Coreclass Testing" ) ;
    //not needed any more
	
	/*RRequestorStack aRequestorStack;
	const CRequestor* identityInfo = CRequestor::NewL(1 , 1 , Kidentity) ;
    aRequestorStack.Insert(identityInfo,0);
    
    CoreObj->SetRequestorIdentityL(aRequestorStack) ;*/
    
    TraceLCallBack7 MyUpdates1(CoreObj) ;
    
    ret1 = CoreObj->TraceL(&MyUpdates1) ;
    
    if( KErrNone == ret1)
    	{	
       	OpenFile();
	 	LogFile.Write(_L8("\n<TraceLPosition7 test>\n"));
	 	CloseFile();
	 	CActiveScheduler :: Start() ;
    	}
    else
    	{
      	returnCode = KErrGeneral;
    	}
   
   //aRequestorStack.Close();
   
   delete CoreObj;
   return KErrNone;
   }



TInt CSAPILocTest::TraceLPosition7( CStifItemParser& /*aItem*/ )
	{
    returnCode = KErrNone;
     // Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "TraceLPosition7" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
    
   __UHEAP_MARK;
   
   TRAPD(err , TraceLFunction7L()) ;
   if(err)
   returnCode = KErrGeneral;
   
   __UHEAP_MARKEND;
    
   return returnCode;  
	}

// -----------------------------------------------------------------------------
// CSAPILocTest::TraceLPosition8
// -----------------------------------------------------------------------------
//
	
class LocUpdateCallBack8 : public MLocationCallBack
 	{
    TInt iCount ;
    TInt iRetStatus ;
    public :
    TInt HandleNotifyL(HPositionGenericInfo* aOutPos , TInt aError) ;
    LocUpdateCallBack8() :iCount(0) , iRetStatus(KErrGeneral){;}
  	};
  
    
TInt LocUpdateCallBack8 :: HandleNotifyL(HPositionGenericInfo* currPos , TInt /*aError*/)
	{
	  
	 TInt aRet;
	 TPosition currPos1;
	 currPos->GetPosition(currPos1);
	 aRet = ValidatePosition(currPos1);
     if ( KErrNone == aRet)
     	{
      	TPosition aPosition2;  
	    CLocationService *CoreObj1 = CLocationService ::NewL() ;
	    
	    _LIT(Kidentity ,"Coreclass Testing" ) ;
		//not needed any more
		/*RRequestorStack aRequestorStack;
		const CRequestor* identityInfo = CRequestor::NewL(1 , 1 , Kidentity) ;
	    
	    aRequestorStack.Insert(identityInfo,0);
	    	    
	    CoreObj1->SetRequestorIdentityL(aRequestorStack) ;*/
    
	    CLocUpdateCallBack6 *MyUpdates2 =  CLocUpdateCallBack6 :: NewL(CoreObj1);
		
		CoreObj1->GetLocationL(MyUpdates2) ;
	    
	    /*aRequestorStack.Close();
    	delete identityInfo;*/
	    }
     return KErrNone ;
	}


TInt TraceLFunction8L()
	{
    TInt ret1;
    TPosition aPosition1;  
    CLocationService *CoreObj = CLocationService ::NewL() ;
    LocUpdateCallBack8 MyUpdates1 ;
    
    _LIT(Kidentity ,"Coreclass Testing" ) ;
	//not needed any more
	/*RRequestorStack aRequestorStack;
	const CRequestor* identityInfo = CRequestor::NewL(1 , 1 , Kidentity) ;
    aRequestorStack.Insert(identityInfo,0);
    
    CoreObj->SetRequestorIdentityL(aRequestorStack) ;*/
    
    ret1 = CoreObj->GetLocationL(&MyUpdates1) ;
    
    if( KErrNone == ret1)
    	{
       	OpenFile();
	 	LogFile.Write(_L8("\n<TraceLPosition8 test>\n"));
	 	CloseFile();
	 	CActiveScheduler :: Start() ;
    	}
    else
    	{
      	returnCode = KErrGeneral;
    	}
    
    /*aRequestorStack.Close();
    delete identityInfo;*/
    delete CoreObj;
    
    return KErrNone;
	}

TInt CSAPILocTest::TraceLPosition8( CStifItemParser& /*aItem*/ )
	{
    returnCode = KErrNone;
    // Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "TraceLPosition8" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
    
    
    __UHEAP_MARK;
    
    TRAPD(err , TraceLFunction8L()) ;
    if(err)
    returnCode = KErrGeneral;
    
     __UHEAP_MARKEND;
  
     return returnCode;  
	}
	
	
// -----------------------------------------------------------------------------
// CSAPILocTest::TraceLPositionOpts
// -----------------------------------------------------------------------------
//
class TraceLCallBackTO : public MLocationCallBack
	{
    TInt iCount ;
    TInt iRetStatus ;
    public :
    TInt HandleNotifyL(HPositionGenericInfo* aOutPos , TInt aError) ;
    TraceLCallBackTO() :iCount(0) , iRetStatus(KErrGeneral){;}
    };
  
TInt TraceLCallBackTO :: HandleNotifyL(HPositionGenericInfo* /*currPos*/ , TInt aError)
	{
	if(KErrTimedOut == aError)
		 {
	 	 CActiveScheduler *Current = CActiveScheduler :: Current() ;
	  	 Current->Stop() ;
	  	 OpenFile();
	  	 LogFile.Write(_L8("Passed..\n"));
	  	 CloseFile();
	  	 returnCode = KErrNone;
	  	 return KErrNone ;	
    	 }
    else
		 {
	 	 CActiveScheduler *Current = CActiveScheduler :: Current() ;
	  	 Current->Stop() ;
	  	 OpenFile();
	  	 LogFile.Write(_L8("Failed..\n"));
	  	 CloseFile();
	  	 returnCode = KErrGeneral;
	 	 return KErrNone; 
		 }
	}


TInt TraceLFunctionOptsL()
	{
    TInt ret1;
    TPosition aPosition1;
    TPositionUpdateOptions aOptions;
    TTimeIntervalMicroSeconds aTimeOut = 10;  
    CLocationService *CoreObj = CLocationService ::NewL() ;
    
    _LIT(Kidentity ,"Coreclass Testing" ) ;
	//not needed any more
	/*RRequestorStack aRequestorStack;
	const CRequestor* identityInfo = CRequestor::NewL(1 , 1 , Kidentity) ;
    aRequestorStack.Insert(identityInfo,0);
    
    CoreObj->SetRequestorIdentityL(aRequestorStack) ;*/
    
    aOptions.SetUpdateTimeOut(aTimeOut);
    
    TraceLCallBackTO MyUpdates;
    
    ret1 = CoreObj->TraceL(&MyUpdates,0,NULL,&aOptions) ;
    
    if( KErrNone == ret1)
    	{
        OpenFile();
	 	LogFile.Write(_L8("\n<TraceLPositionOpts test>\n"));
	 	CloseFile();
	 	CActiveScheduler::Start();
   		}
    
    else
    	{
    	returnCode = KErrGeneral;	
    	}
    /*aRequestorStack.Close();
    delete identityInfo;*/
    delete CoreObj;
    return 0;
	}

TInt CSAPILocTest::TraceLPositionOpts( CStifItemParser& /*aItem*/ )
	{
    returnCode = KErrNone;
    // Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "TraceLPositionOpts" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
   
	 __UHEAP_MARK;
    
    TRAPD(err , TraceLFunctionOptsL()) ;
    if(err)
    returnCode = KErrGeneral;
    
    __UHEAP_MARKEND;
    
    return returnCode;  
	}

// -----------------------------------------------------------------------------
// CSAPILocTest::TraceLPositionOpts1
// -----------------------------------------------------------------------------
//
class TraceLCallBackOpts1 : public MLocationCallBack
	{
    TInt iCount ;
    TInt iRetStatus ;
    CLocationService *CoreObj;
    public :
    TInt HandleNotifyL(HPositionGenericInfo* aOutPos , TInt aError) ;
    TraceLCallBackOpts1(TInt count = 0,TInt status = KErrGeneral)
   		{
   	 	iCount = count;
   	 	iRetStatus = status;
   		}
  	};
  
 
TInt TraceLCallBackOpts1 :: HandleNotifyL(HPositionGenericInfo* /*currPos*/ , TInt /*aError*/){return 0;}



TInt TraceLFunctionOpts1L()
	{
    TInt ret1;
    TPosition aPosition1;
    TPositionUpdateOptions aOptions;
    TTimeIntervalMicroSeconds aTimeOut = 10000000; 
    TTimeIntervalMicroSeconds aTimeInterval = 30000000; 
    
    CLocationService *CoreObj = CLocationService ::NewL() ;
    
    _LIT(Kidentity ,"Coreclass Testing" ) ;
	//not needed any more
	/*RRequestorStack aRequestorStack;
	const CRequestor* identityInfo = CRequestor::NewL(1 , 1 , Kidentity) ;
    aRequestorStack.Insert(identityInfo,0);
    
    CoreObj->SetRequestorIdentityL(aRequestorStack) ;*/
    
    aOptions.SetUpdateTimeOut(aTimeOut);
    aOptions.SetUpdateInterval(aTimeInterval);
    
    TraceLCallBackOpts1 MyUpdates;
    
    ret1 = CoreObj->TraceL(&MyUpdates,0,NULL,&aOptions) ;
    
    if( KErrArgument == ret1)
    	{
        OpenFile();
	 	LogFile.Write(_L8("\n<TraceLPositionOpts1 test>\n"));
	 	LogFile.Write(_L8("Passed\n"));
	 	CloseFile();
	 	returnCode = KErrNone;
	 	}
    
    else
    	{
    	returnCode = KErrGeneral;
    	}
   	
   	/*aRequestorStack.Close();
    delete identityInfo;*/
    delete CoreObj;
    return 0;
	}


TInt CSAPILocTest::TraceLPositionOpts1( CStifItemParser& /*aItem*/ )
	{
    returnCode = KErrNone;
   
    // Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "TraceLPositionOpts1" );
     TestModuleIf().Printf( 0, KSAPILocTest, KExample );
    
     __UHEAP_MARK;
   
    TRAPD(err , TraceLFunctionOpts1L()) ;
    if(err)
    returnCode = KErrGeneral;
   
     __UHEAP_MARKEND;
    
    return returnCode;  
	}


// -----------------------------------------------------------------------------
// CSAPILocTest::TraceLPositionOpts2
// -----------------------------------------------------------------------------
//
TInt TraceLFunctionOpts2L()
	{
    TInt ret1;
    TPosition aPosition1;
    TPositionUpdateOptions aOptions;
    TTimeIntervalMicroSeconds aTimeOut = 60000000; 
    TTimeIntervalMicroSeconds aTimeInterval = 30000000;
    TTimeIntervalMicroSeconds aInterval;
    TTime start,end;
    
    CLocationService *CoreObj = CLocationService ::NewL() ;
    //not needed any more
    /*_LIT(Kidentity ,"Coreclass Testing" ) ;
	RRequestorStack aRequestorStack;
	const CRequestor* identityInfo = CRequestor::NewL(1 , 1 , Kidentity) ;
    aRequestorStack.Insert(identityInfo,0);
    
    CoreObj->SetRequestorIdentityL(aRequestorStack) ;*/
    
    aOptions.SetUpdateTimeOut(aTimeOut);
    aOptions.SetUpdateInterval(aTimeInterval);
    
    TraceLCallBack MyUpdates;
    
    ret1 = CoreObj->TraceL(&MyUpdates,0,NULL,&aOptions) ;
    
    if( KErrNone == ret1)
    	{
        OpenFile();
	 	LogFile.Write(_L8("\n<TraceLPositionOpts2 test>\n"));
	 	CloseFile();
	 	start.HomeTime();
	 	CActiveScheduler::Start();
	 	end.HomeTime();
	 	aInterval = end.MicroSecondsFrom(start);
//	 	if(aInterval<150000000)
//	 	returnCode = KErrGeneral;
   		}
    
    else
    	{
    	returnCode = KErrGeneral;	
    	}
    
    /*aRequestorStack.Close();
    delete identityInfo;*/
    delete CoreObj;
    return 0;
	}

TInt CSAPILocTest::TraceLPositionOpts2( CStifItemParser& /*aItem*/ )
	{
    returnCode = KErrNone;
    // Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "TraceLPositionOpts2" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
   
    __UHEAP_MARK;
    
    TRAPD(err , TraceLFunctionOpts2L()) ;
    if(err)
    returnCode = KErrGeneral;
    
    __UHEAP_MARKEND;
    
    return returnCode;  
	}

// -----------------------------------------------------------------------------
// CSAPILocTest::TraceLPositionOpts3
// -----------------------------------------------------------------------------
//
class TraceLCallBackOpts3 : public MLocationCallBack
	{
    TInt iCount ;
    TInt iRetStatus ;
    public :
    TInt HandleNotifyL(HPositionGenericInfo* aOutPos , TInt aError) ;
    TraceLCallBackOpts3() :iCount(0) , iRetStatus(KErrGeneral){;}
  	};
  
  
  
TInt TraceLCallBackOpts3 :: HandleNotifyL(HPositionGenericInfo* currPos , TInt aError)
	{
	 TTime timeStamp;
	 TInt64 timeInt;
	 TBuf8<50> buf ;
 	 TRealFormat format ;
	 if(KErrNone == aError && iCount<2)
	 	{
	 	User::After(60000000);
	 	TPosition currPos1;
	 	currPos->GetPosition(currPos1);
	 	timeStamp = currPos1.Time();
        timeInt = timeStamp.Int64();
        if(timeInt)
        	{
            OpenFile();
	        buf.Num(timeInt , format) ;
 		    LogFile.Write(_L8("\nTimestamp = "));
 		    LogFile.Write(buf) ;
	        CloseFile();
	        returnCode = KErrNone;
	        }
        else
        	{
        	returnCode = KErrGeneral;
        	return 0;
        	}
    	 iCount++;	 
	 	}
		
     else
	 	{
	 	CActiveScheduler *Current = CActiveScheduler :: Current() ;
	  	Current->Stop() ;
	 	}
	 return 0;
	}

TInt TraceLFunctionOpts3L()
	{
    TInt ret1;
    TPosition aPosition1;
    TPositionUpdateOptions aOptions;
    TTimeIntervalMicroSeconds aTimeOut = 20000000; 
    TTimeIntervalMicroSeconds aTimeInterval = 5000000;
    TTimeIntervalMicroSeconds aInterval;
    TTime start,end;
   	TBool aAcceptPartialUpdates = ETrue;
    
    CLocationService *CoreObj = CLocationService ::NewL() ;
    
    _LIT(Kidentity ,"Coreclass Testing" ) ;
	//not needed any more
	/*RRequestorStack aRequestorStack;
	const CRequestor* identityInfo = CRequestor::NewL(1 , 1 , Kidentity) ;
    aRequestorStack.Insert(identityInfo,0);
   
    CoreObj->SetRequestorIdentityL(aRequestorStack) ;*/
    
    aOptions.SetUpdateTimeOut(aTimeOut);
    aOptions.SetUpdateInterval(aTimeInterval);
    aOptions.SetAcceptPartialUpdates(aAcceptPartialUpdates);
    
    TraceLCallBackOpts3 MyUpdates;
    
    ret1 = CoreObj->TraceL(&MyUpdates,0,NULL,&aOptions) ;
    
    if( KErrNone == ret1)
    	{
        TBuf8<20> retBuf;
        TRealFormat retFormat;
        OpenFile();
	 	LogFile.Write(_L8("\n<TraceLPositionOpts3 test>\n"));
	 	CloseFile();

	 	start.HomeTime();
	 	CActiveScheduler::Start();
	 	end.HomeTime();
	 	aInterval = end.MicroSecondsFrom(start);
	// 	if(aInterval<150000000)
	// 	returnCode = KErrGeneral;
        retBuf.Num(returnCode,retFormat);
        OpenFile();
        LogFile.Write(_L8("\nreturnCode : "));
        LogFile.Write(retBuf);
        CloseFile();
   		}
    
    else
      	{
    	returnCode = KErrGeneral;	
    	}
    /*aRequestorStack.Close();
    delete identityInfo;*/
    delete CoreObj;
    return 0;
	}


TInt CSAPILocTest::TraceLPositionOpts3( CStifItemParser& /*aItem*/ )
	{
    returnCode = KErrNone;      
    // Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "TraceLPositionOpts3" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
    
   __UHEAP_MARK;
   
   TRAPD(err , TraceLFunctionOpts3L()) ;
   
   if(err)
   returnCode = KErrGeneral;
   
   __UHEAP_MARKEND;
    
     return returnCode;  
	}

// -----------------------------------------------------------------------------
// CSAPILocTest::CancelService1
// -----------------------------------------------------------------------------
//
TInt CancelFunction1L()
	{
    TInt ret1,ret2;
    CLocationService *CoreObj = CLocationService ::NewL() ;
    
    _LIT(Kidentity ,"Coreclass Testing" ) ;
	//not needed any more
	/*RRequestorStack aRequestorStack;
	const CRequestor* identityInfo = CRequestor::NewL(1 , 1 , Kidentity) ;
    aRequestorStack.Insert(identityInfo,0);
    
    CoreObj->SetRequestorIdentityL(aRequestorStack) ;*/
    
    ret1 = CoreObj->CancelOnGoingService(0) ;
    
    ret2 = CoreObj->CancelOnGoingService(1) ;
    
    if( KErrNotFound == ret1 && KErrNotFound == ret2 )
    	{
      	OpenFile();
	 	LogFile.Write(_L8("\n<CancelService1 test>\n"));
	 	LogFile.Write(_L8("Passed..\n"));
	 	CloseFile();
	 	returnCode = KErrNone; 
   		}
    
    else
    	{
    	returnCode = KErrGeneral;	
    	}
    	
    /*aRequestorStack.Close();
    delete identityInfo;*/
    delete CoreObj;
    return 0;
	}

TInt CSAPILocTest::CancelService1( CStifItemParser& /*aItem*/ )
	{
    returnCode = KErrNone;
    // Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "CancelService1" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
    
    __UHEAP_MARK;
    
    TRAPD(err , CancelFunction1L()) ;
    if(err)
    returnCode = KErrGeneral;
    
    __UHEAP_MARKEND;
    
    return returnCode;  
	}

// -----------------------------------------------------------------------------
// CSAPILocTest::CancelService2
// -----------------------------------------------------------------------------
//
TInt CancelFunction2L()
	{
    TInt ret1,ret2;
    CLocationService *CoreObj = CLocationService ::NewL() ;
    
    _LIT(Kidentity ,"Coreclass Testing" ) ;
	//not needed any more
	/*RRequestorStack aRequestorStack;
	const CRequestor* identityInfo = CRequestor::NewL(1 , 1 , Kidentity) ;
    aRequestorStack.Insert(identityInfo,0);
    
    CoreObj->SetRequestorIdentityL(aRequestorStack) ;*/
    
    ret1 = CoreObj->CancelOnGoingService(4) ;
    
    ret2 = CoreObj->CancelOnGoingService(6) ;
    
    if( KErrArgument == ret1 && KErrArgument == ret2 )
    	{
      	OpenFile();
	 	LogFile.Write(_L8("\n<CancelService2 test>\n"));
	 	LogFile.Write(_L8("Passed..\n"));
	 	CloseFile();
	 	returnCode = KErrNone; 
   		}
    
    else
       	{
    	returnCode = KErrGeneral;	
    	}
    	
    /*aRequestorStack.Close();
    delete identityInfo;*/
    delete CoreObj;
    return 0;
	}


TInt CSAPILocTest::CancelService2( CStifItemParser& /*aItem*/ )
	{
    returnCode = KErrNone;
     // Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "CancelService2" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
    __UHEAP_MARK;
    
    TRAPD(err , CancelFunction2L()) ;
    if(err)
    returnCode = KErrGeneral;
    __UHEAP_MARKEND;
    
     return returnCode;  
	}

// -----------------------------------------------------------------------------
// CSAPILocTest::GetTime
// -----------------------------------------------------------------------------
//
TInt CSAPILocTest::GetTime( CStifItemParser& /*aItem*/ )
	{
	TInt ret;
	TPositionInfo currPos;
	TPosition currPos1;
	TTime currPosTime;
	TDateTime currPosDateTime;
	TBuf8<50> buf ;
	TRealFormat format ;
  	returnCode = KErrNone;
  	// Print to UI
 	_LIT( KSAPILocTest, "SAPILocTest" );
  	_LIT( KExample, "GetTime" );
  	TestModuleIf().Printf( 0, KSAPILocTest, KExample );
    
 	 __UHEAP_MARK;
  
 	 CLocationService *CoreObj = CLocationService :: NewL();
  
 	 if( NULL == CoreObj)
  		{
  		OpenFile();
		LogFile.Write(_L8("\n<GetTime Test>\n"));
		LogFile.Write(_L8("Failed..\n"));
		CloseFile();
   		returnCode = KErrGeneral;
 		}
  
    _LIT(Kidentity ,"Coreclass Testing" ) ;
	//not needed any more
	/*RRequestorStack aRequestorStack;
	const CRequestor* identityInfo = CRequestor::NewL(1 , 1 , Kidentity) ;
    aRequestorStack.Insert(identityInfo,0);
    
    CoreObj->SetRequestorIdentityL(aRequestorStack) ;*/
    
  	ret = CoreObj->GetLocationL(&currPos);
  	
  	if(KErrNone == ret)
  	  {
      currPos.GetPosition(currPos1);
	  currPosTime = currPos1.Time();
	  currPosDateTime = currPosTime.DateTime();
	  
	  TInt aDay = currPosDateTime.Day();
	  TInt aHour = currPosDateTime.Hour();
	  TInt aMicroSecond = currPosDateTime.MicroSecond();
	  TInt aMinute = currPosDateTime.Minute();
	  TInt aMonth = currPosDateTime.Month();
	  TInt aSecond = currPosDateTime.Second();
	  TInt aYear = currPosDateTime.Year();
	  TReal32 aVerAcc = currPos1.VerticalAccuracy();
	  TReal32 aHorAcc = currPos1.HorizontalAccuracy();
	    
	  OpenFile();

  	  LogFile.Write(_L8("\n<GetTime test> \n"));
	  buf.Num(aHorAcc,format);
	  LogFile.Write(_L8("Horizontal Acc = "));
	  LogFile.Write(buf) ;
	  LogFile.Write(_L8("\n")) ;
	
  	  buf.Num(aVerAcc,format);
	  LogFile.Write(_L8("Vertical Acc = "));
	  LogFile.Write(buf) ;
	  LogFile.Write(_L8("\n")) ;
	
  	  buf.Num(aDay , format) ;
	  LogFile.Write(_L8("Time = "));
	  LogFile.Write(buf) ;
	  LogFile.Write(_L8("-")) ;
	
 	  buf.Num(aMonth , format) ;
  	  LogFile.Write(buf) ;
	  LogFile.Write(_L8("-")) ;
	
	  buf.Num(aYear , format) ;
	  LogFile.Write(buf) ;
	  LogFile.Write(_L8("  ")) ;
	
	  buf.Num(aHour , format) ;
	  LogFile.Write(buf) ;
	  LogFile.Write(_L8(":")) ;
	
	  buf.Num(aMinute , format) ;
	  LogFile.Write(buf) ;
	  LogFile.Write(_L8(":")) ;
	
	  buf.Num(aSecond , format) ;
	  LogFile.Write(buf) ;
	  LogFile.Write(_L8(":")) ;
	
	  buf.Num(aMicroSecond , format) ;
	  LogFile.Write(buf) ;
	  LogFile.Write(_L8("\n")) ;
	  CloseFile();
		
	  ValidatePosition(currPos1);
      }
	else
		{
	  	OpenFile();
	  	LogFile.Write(_L8("\n<GetTime Test>\n"));
	  	LogFile.Write(_L8("Failed..\n"));
	  	CloseFile();
	  	returnCode = KErrGeneral;	
  		}
	  	 /*aRequestorStack.Close();
	    delete identityInfo;*/
	    delete CoreObj;
	    
	__UHEAP_MARKEND;       
	    
	return returnCode;    
	}


    
// -----------------------------------------------------------------------------
// CSAPILocTest::GetSpeed
// -----------------------------------------------------------------------------
//
TInt CSAPILocTest::GetSpeed( CStifItemParser& /*aItem*/ )
    {
	TInt ret;
	TPositionInfo currPos;
	TPosition currPos1,fromPos;
	TTime currPosTime;
	TTime fromPosTime;
	TDateTime currPosDateTime;
	TReal64 aLatitude1  = 8;
	TReal64 aLongitude1 = 70;
	TReal32 aAltitude1  = 700;
	TReal32 aSpeed;
	fromPosTime = 63342890700000000;
	
	fromPos.SetCoordinate(aLatitude1,aLongitude1,aAltitude1);
	fromPos.SetTime(fromPosTime);
	
	returnCode =KErrNone;
		
    // Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "GetSpeed" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
   
    __UHEAP_MARK;
    
    CLocationService *CoreObj = CLocationService :: NewL();
    
    if( NULL == CoreObj)
    	{
    	OpenFile();
	    LogFile.Write(_L8("\n<GetSpeed Test>\n"));
	    LogFile.Write(_L8("Failed(CoreObj creation)..\n"));
	    CloseFile();
	   	returnCode = KErrGeneral;
   		}
    //not needed any more
    /*_LIT(Kidentity ,"Coreclass Testing" ) ;
	RRequestorStack aRequestorStack;
	const CRequestor* identityInfo = CRequestor::NewL(1 , 1 , Kidentity) ;
    aRequestorStack.Insert(identityInfo,0);
    CoreObj->SetRequestorIdentityL(aRequestorStack) ;*/
    	
    User::After(120000000);
    ret = CoreObj->GetLocationL(&currPos);
    
    if(KErrNone == ret)
    	{
    	currPos.GetPosition(currPos1);
	    currPos1.Speed(fromPos,aSpeed);
	    
		OpenFile();
		TBuf8<50> buf ;
		TRealFormat format ;
		LogFile.Write(_L8("\n<GetSpeed test> \n"));
		buf.Num(aSpeed , format) ;
		LogFile.Write(_L8("Speed = "));
		LogFile.Write(buf) ;
		LogFile.Write(_L8("\n")) ;
		CloseFile();
	    ValidatePosition(currPos1);
	    returnCode = KErrNone;
	   	}
	  else
	  	{
	  	OpenFile();
	  	LogFile.Write(_L8("\n<GetSpeed Test>\n"));
	  	LogFile.Write(_L8("Failed(getloc error)..\n"));
	  	
		TBuf8<50> buf ;
		TRealFormat format ;
		LogFile.Write(_L8("\n<GetSpeed test> \n"));
		buf.Num(ret , format) ;
	  	LogFile.Write(buf);
	  	CloseFile();
	   	returnCode = KErrGeneral;
    	
	  	}
    
    /*aRequestorStack.Close();
	delete identityInfo;*/
	delete CoreObj;
    __UHEAP_MARKEND;       
   
    return returnCode;    
    }
    
    
// -----------------------------------------------------------------------------
// CSAPILocTest::GetPositionOpts
// -----------------------------------------------------------------------------
//
TInt CSAPILocTest::GetPositionOpts( CStifItemParser& /*aItem*/ )
	{
	TInt ret;
	TPositionInfo currPos;
	TPosition currPos1;
	TPositionUpdateOptions aOptions;
	TTimeIntervalMicroSeconds aTimeOut = 100;
	returnCode = KErrNone;
	
	// Print to UI
	_LIT( KSAPILocTest, "SAPILocTest" );
	_LIT( KExample, "GetPositionOpts" );
	TestModuleIf().Printf( 0, KSAPILocTest, KExample );

	 __UHEAP_MARK;
	
	CLocationService *CoreObj = CLocationService :: NewL();

	if( NULL == CoreObj)
		{
		OpenFile();
		LogFile.Write(_L8("\n<GetPositionOpts Test>\n"));
		LogFile.Write(_L8("Failed..\n"));
		CloseFile();
		return KErrGeneral;
		}
	//not needed any more
    /*_LIT(Kidentity ,"Coreclass Testing" ) ;
	RRequestorStack aRequestorStack;
	const CRequestor* identityInfo = CRequestor::NewL(1 , 1 , Kidentity) ;
    aRequestorStack.Insert(identityInfo,0);
    CoreObj->SetRequestorIdentityL(aRequestorStack) ;*/
    
	aOptions.SetUpdateTimeOut(aTimeOut);
	
	ret = CoreObj->GetLocationL(&currPos,&aOptions);
	    
	if(KErrTimedOut==ret)
		{
		OpenFile();
		LogFile.Write(_L8("\n<GetPositionOpts Test>\n"));
		LogFile.Write(_L8("Passed..\n"));
		CloseFile();
	  	returnCode = KErrNone;	
		}
	else
		{
		OpenFile();
		LogFile.Write(_L8("\n<GetPositionOpts Test>\n"));
		LogFile.Write(_L8("Failed..\n"));
		CloseFile();
		returnCode = KErrGeneral;
		}
		
	/*aRequestorStack.Close();
    delete identityInfo;*/
    delete CoreObj;
	
	__UHEAP_MARKEND; 
	
	return returnCode;
	
	}
    

// -----------------------------------------------------------------------------
// CSAPILocTest::GetPositionOpts1
// -----------------------------------------------------------------------------
//
TInt CSAPILocTest::GetPositionOpts1( CStifItemParser& /*aItem*/ )
    {
    TInt ret;
    TPositionInfo currPos;
    TPositionUpdateOptions options;
    TTimeIntervalMicroSeconds aTimeOut = 0;
    returnCode = KErrNone;
    
    // Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "GetPositionOpts1" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
   
    __UHEAP_MARK;
    
    CLocationService *CoreObj = CLocationService :: NewL();
    
    if( NULL == CoreObj)
    	{
    	OpenFile();
		LogFile.Write(_L8("\n<GetPositionOpts1 Test>\n"));
		LogFile.Write(_L8("Failed..\n"));
		CloseFile();
	   	return KErrGeneral;
   		}
    
    _LIT(Kidentity ,"Coreclass Testing" ) ;
	//not needed any more
	/*RRequestorStack aRequestorStack;
	const CRequestor* identityInfo = CRequestor::NewL(1 , 1 , Kidentity) ;
    aRequestorStack.Insert(identityInfo,0);
    
    CoreObj->SetRequestorIdentityL(aRequestorStack) ;
    
    options.SetUpdateTimeOut(aTimeOut);
    
    ret = CoreObj->GetLocationL(&currPos,&options);*/
        
    if(KErrTimedOut==ret)
    	{
    	OpenFile();
    	LogFile.Write(_L8("\n<GetPositionOpts1 Test>\n"));
    	LogFile.Write(_L8("Failed(timed out)..\n"));
    	CloseFile();
    	returnCode = KErrGeneral;	
    	}
    else
    	{
    	OpenFile();
    	LogFile.Write(_L8("\n<GetPositionOpts1 Test>\n"));
    	LogFile.Write(_L8("Passed..\n"));
    	CloseFile();
    	returnCode = KErrNone;
    	}
    
    /*aRequestorStack.Close();
    delete identityInfo;*/
    delete CoreObj;
     __UHEAP_MARKEND; 
     
     return returnCode;
     }
    
    
 // -----------------------------------------------------------------------------
// CSAPILocTest::GetPositionOpts2
// -----------------------------------------------------------------------------
//
TInt CSAPILocTest::GetPositionOpts2( CStifItemParser& /*aItem*/ )
	{
	TInt ret1,ret2;
	TPositionInfo currPos1,currPos2;
	TPosition cPos1,cPos2;
	TPositionUpdateOptions options;
//	TTimeIntervalMicroSeconds aTimeOut = 0;
//	TTimeIntervalMicroSeconds aInterval = 30000000;
	TTimeIntervalMicroSeconds aActualInterval;
	TTime start;
	TTime end;
	TInt64 aActualInt;
	returnCode = KErrNone;
	
  	// Print to UI
  	_LIT( KSAPILocTest, "SAPILocTest" );
 	_LIT( KExample, "GetPostionOpts2" );
 	TestModuleIf().Printf( 0, KSAPILocTest, KExample );
  
  	__UHEAP_MARK;
  	
  	CLocationService *CoreObj = CLocationService :: NewL();
    
 	 if( NULL == CoreObj)
  		{
    	OpenFile();
  		LogFile.Write(_L8("\n<GetPositionOpts2 Test>\n"));
  		LogFile.Write(_L8("Failed..\n"));
  		CloseFile();
   		return KErrGeneral;
   		}
    
    _LIT(Kidentity ,"Coreclass Testing" ) ;
	//not needed any more
	/*RRequestorStack aRequestorStack;
	const CRequestor* identityInfo = CRequestor::NewL(1 , 1 , Kidentity) ;
    aRequestorStack.Insert(identityInfo,0);
    
    CoreObj->SetRequestorIdentityL(aRequestorStack) ;*/
    
 //   options.SetUpdateTimeOut(aTimeOut);
    
 //   options.SetUpdateInterval(aInterval);
    
    User::After(120000000);
    ret1 = CoreObj->GetLocationL(&currPos1/*,&options*/);
    
    
    
    if( (KErrNone != ret1))
    	{
    	OpenFile();
    	LogFile.Write(_L8("\n<GetPositionOpts2 Test>\n"));
    	LogFile.Write(_L8("Failed(coreobj 1)..\n"));
    	CloseFile();
    	returnCode = KErrGeneral;
    	}
    else
   	    {
		
		start.HomeTime();
	    ret2 = CoreObj->GetLocationL(&currPos2/*,&options*/);
	    end.HomeTime();
	    
	    aActualInterval=end.MicroSecondsFrom(start);
	    aActualInt = aActualInterval.Int64();
	    if(KErrNone == ret2)
		    {
		    OpenFile();
		   	TBuf8<50> buf ;
			TRealFormat format ;
			LogFile.Write(_L8("\n<GetPositionOpts2 Test>\n"));
			buf.Num(aActualInt, format) ;
			LogFile.Write(_L8("TimeTaken = "));
		 	LogFile.Write(buf) ;
		    CloseFile();
		    currPos1.GetPosition(cPos1);
		    currPos2.GetPosition(cPos2);
		    ValidatePosition(cPos1);
		    ValidatePosition(cPos2);
		    returnCode = KErrNone;	
		    }
		 else
		 	{
		 	OpenFile();
	    	LogFile.Write(_L8("\n<GetPositionOpts2 Test>\n"));
	    	LogFile.Write(_L8("Failed(coreObj 2)..\n"));
	    	CloseFile();
	    	returnCode = KErrGeneral;	
		 	}
        }
   
    /*aRequestorStack.Close();
    delete identityInfo;*/
    delete CoreObj;

    __UHEAP_MARKEND; 
   
    return returnCode;
	}
   
   
// -----------------------------------------------------------------------------
// CSAPILocTest::GetPositionOpts3
// -----------------------------------------------------------------------------
//
TInt CSAPILocTest::GetPositionOpts3( CStifItemParser& /*aItem*/ )
	{
	TInt ret1,ret2,ret3;
	TPositionInfo currPos1,currPos2,currPos3;
	TPosition cPos1,cPos2,cPos3;
	TPositionUpdateOptions options;
	TTimeIntervalMicroSeconds aTimeOut =  30000000;
	TTimeIntervalMicroSeconds aInterval = 120000000;
	TTimeIntervalMicroSeconds aActualInterval;
	returnCode = KErrNone;
    
  // Print to UI
  _LIT( KSAPILocTest, "SAPILocTest" );
  _LIT( KExample, "GetPostionOpts3");
  TestModuleIf().Printf( 0, KSAPILocTest, KExample );
  
  __UHEAP_MARK;
  
  CLocationService *CoreObj = CLocationService :: NewL();
  
  if( NULL == CoreObj)
  	{
  	OpenFile();
    LogFile.Write(_L8("\n<GetPositionOpts3 Test>\n"));
    LogFile.Write(_L8("Failed..\n"));
    CloseFile();
   	return KErrGeneral;
 	}
  
    _LIT(Kidentity ,"Coreclass Testing" ) ;
	//not needed any more
	/*RRequestorStack aRequestorStack;
	const CRequestor* identityInfo = CRequestor::NewL(1 , 1 , Kidentity) ;
    aRequestorStack.Insert(identityInfo,0);
    
    CoreObj->SetRequestorIdentityL(aRequestorStack) ;*/
    
    options.SetUpdateTimeOut(aTimeOut);
    options.SetUpdateInterval(aInterval);
  
    ret1 = CoreObj->GetLocationL(&currPos1,&options);
    ret2 = CoreObj->GetLocationL(&currPos2,&options);
    ret3 = CoreObj->GetLocationL(&currPos2,&options);
   
  
  if( KErrArgument == ret1 && KErrArgument == ret2 && KErrArgument == ret3 )
	  {
	  OpenFile();
	  LogFile.Write(_L8("\n<GetPositionOpts3 Test>\n"));
	  LogFile.Write(_L8("Passed..\n"));
	  CloseFile();
	  returnCode = KErrNone;
	  }
  
  else
  	  {
      OpenFile();
	  LogFile.Write(_L8("\n<GetPositionOpts3 Test>\n"));
	  LogFile.Write(_L8("Failed..\n"));
	  CloseFile();
   	  returnCode = KErrGeneral;
      }
  
  /*aRequestorStack.Close();
  delete identityInfo;*/
  delete CoreObj;
	 
  __UHEAP_MARKEND; 
   
  return returnCode; 
 }
   
// -----------------------------------------------------------------------------
// CSAPILocTest::GetPositionOpts4
// -----------------------------------------------------------------------------
//
TInt CSAPILocTest::GetPositionOpts4( CStifItemParser& /*aItem*/ )
	{
	TInt ret1,ret2;
	TPositionInfo currPos1,currPos2,currPos3;
	TPosition cPos1,cPos2,cPos3;
	TPositionUpdateOptions options;
	TTimeIntervalMicroSeconds aTimeOut =  80000000;
	TTimeIntervalMicroSeconds aInterval = 10000000;
	TTimeIntervalMicroSeconds aMaxAge = 5000000;
	TTimeIntervalMicroSeconds aActualInterval;
	TTime start;
	TTime end;
	TInt64 aActualInt;
    returnCode = KErrNone;
    
  // Print to UI
  _LIT( KSAPILocTest, "SAPILocTest" );
  _LIT( KExample, "GetPostionOpts4");
  TestModuleIf().Printf( 0, KSAPILocTest, KExample );
  
  __UHEAP_MARK;
  
  CLocationService *CoreObj = CLocationService :: NewL();
    
  if( NULL == CoreObj)
  	{
  	OpenFile();
  	LogFile.Write(_L8("\n<GetPositionOpts4 Test>\n"));
  	LogFile.Write(_L8("Failed..\n"));
  	CloseFile();
   	return KErrGeneral;
 	}
    
    _LIT(Kidentity ,"Coreclass Testing" ) ;
	//not needed any more
	/*RRequestorStack aRequestorStack;
	const CRequestor* identityInfo = CRequestor::NewL(1 , 1 , Kidentity) ;
    aRequestorStack.Insert(identityInfo,0);
    CoreObj->SetRequestorIdentityL(aRequestorStack) ;*/
    
    options.SetUpdateTimeOut(aTimeOut);
    options.SetUpdateInterval(aInterval);
    options.SetMaxUpdateAge(aMaxAge);
    
    ret1 = CoreObj->GetLocationL(&currPos1,&options);
    
    start.HomeTime();
    ret2 = CoreObj->GetLocationL(&currPos2,&options);
    end.HomeTime();
    
    aActualInterval=end.MicroSecondsFrom(start);
    
  //  if( aActualInterval<=10000000 || ret1 || ret2 )
    if( (KErrNone == ret1) && (KErrNone == ret2 ))
    	{
      	aActualInt = aActualInterval.Int64();
    	OpenFile();
    	TBuf8<50> buf ;
 		TRealFormat format ;
 		LogFile.Write(_L8("\n<GetPositionOpts4 Test> \n"));
 		buf.Num(aActualInt, format) ;
 		LogFile.Write(_L8("TimeTaken = "));
 		LogFile.Write(buf) ;
     	CloseFile();
     	currPos1.GetPosition(cPos1);
     	currPos2.GetPosition(cPos2);
     //	ValidatePosition(cPos1);
     //	ValidatePosition(cPos2);
     	returnCode = KErrNone;	
      	
    	}
    else
    	{
        OpenFile();
    	LogFile.Write(_L8("\n<GetPositionOpts4 Test>\n"));
    	LogFile.Write(_L8("Failed(error in ret values)..\n"));
    	CloseFile();	
    	returnCode = KErrGeneral;
        }
        
    /*aRequestorStack.Close();
    delete identityInfo;*/
    delete CoreObj;
    
    __UHEAP_MARKEND; 
    
	  return returnCode;
	}
   

// -----------------------------------------------------------------------------
// CSAPILocTest::GetPositionOpts5
// -----------------------------------------------------------------------------
//
TInt CSAPILocTest::GetPositionOpts5( CStifItemParser& /*aItem*/ )
	{
	TInt ret1,ret2;
	TInt64 aTime1,aTime2;
	TPositionInfo currPos1,currPos2;
	TPosition cPos1,cPos2;
	TPositionUpdateOptions options;
	TTimeIntervalMicroSeconds aTimeOut =  10000000;
	TTimeIntervalMicroSeconds aInterval = 2000000;
	TTimeIntervalMicroSeconds aActualInterval;
	TTime aTimeStamp1,aTimeStamp2;
	TBool aAcceptPartialUpdates = ETrue;
    returnCode = KErrNone;
  
  // Print to UI
  _LIT( KSAPILocTest, "SAPILocTest" );
  _LIT( KExample, "GetPostionOpts5");
  TestModuleIf().Printf( 0, KSAPILocTest, KExample );
  
  __UHEAP_MARK;
  
  CLocationService *CoreObj = CLocationService :: NewL();
  
  if( NULL == CoreObj)
  	{
  	OpenFile();
    LogFile.Write(_L8("\n<GetPositionOpts5 Test>\n"));
    LogFile.Write(_L8("Failed(Null CoreObj)..\n"));
    CloseFile();
   	return KErrGeneral;
   	}
    
    _LIT(Kidentity ,"Coreclass Testing" ) ;
	//not needed any more
	/*RRequestorStack aRequestorStack;
	const CRequestor* identityInfo = CRequestor::NewL(1 , 1 , Kidentity) ;
    aRequestorStack.Insert(identityInfo,0);
  
    CoreObj->SetRequestorIdentityL(aRequestorStack) ;*/
    
    options.SetUpdateTimeOut(aTimeOut);
    options.SetUpdateInterval(aInterval);
    options.SetAcceptPartialUpdates(aAcceptPartialUpdates);
    
    User::After(120000000);
    ret1 = CoreObj->GetLocationL(&currPos1,&options);
  
    if(KErrNone == ret1)
    	{
	    ret2 = CoreObj->GetLocationL(&currPos2,&options);
	    if(KErrNone == ret2)
		    {
		    currPos1.GetPosition(cPos1);
		    currPos2.GetPosition(cPos2);
		    aTimeStamp1 = cPos1.Time();
		    aTimeStamp2 = cPos2.Time();
		    aTime1 = aTimeStamp1.Int64();
		    aTime2 = aTimeStamp2.Int64();
		    if((aTime1) && (aTime2))
		      	{
		        OpenFile();
		       	LogFile.Write(_L8("\n<GetPositionOpts5 Test>\n"));
		       	LogFile.Write(_L8("Passed..\n"));
		       	CloseFile();
		        returnCode = KErrNone;	
		        }
		     else
		      	{
		        OpenFile();
		    	LogFile.Write(_L8("\n<GetPositionOpts5 Test>\n"));
		    	LogFile.Write(_L8("Failed(no timeStamp)..\n"));
		    	CloseFile();
		       	returnCode = KErrGeneral;	
		      	}
		    }
		 else
		 	{
		 	OpenFile();
		    LogFile.Write(_L8("\n<GetPositionOpts5 Test>\n"));
		    LogFile.Write(_L8("Failed(getLoc2 error)..\n"));
		    CloseFile();
		    returnCode = KErrGeneral;		
		 	}
    	}
   
    else
    	{
	    OpenFile();
	    LogFile.Write(_L8("\n<GetPositionOpts5 Test>\n"));
	    LogFile.Write(_L8("Failed(getLoc error)..\n"));
	    CloseFile();
	    returnCode = KErrGeneral;	
   		}

	/*aRequestorStack.Close();
	delete identityInfo;*/
	delete CoreObj;
	__UHEAP_MARKEND;   
	return returnCode;
	}
   
 // -----------------------------------------------------------------------------
// CSAPILocTest::GetLastPosition
// -----------------------------------------------------------------------------
//
//TInt CSAPILocTest::GetLastPosition( CStifItemParser& /*aItem*/ )
  /*  {
    	TInt ret;
    	TPosition currPos;
    	TTime currPosTime;
    	TDateTime currPosDateTime;
    // Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "GetLastPosition" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
    
    // Print to log file
    iLog->Log( KExample );

    __UHEAP_MARK;
    CLocationService *CoreObj = CLocationService :: NewL();
    
    if( NULL == CoreObj)
    {
    	iLog->Log( _L("CLocationService object creation failed") );	
   		return KErrGeneral;
   	}
    
    ret = CoreObj->GetLastKnownLoc(currPos);
    if( KErrUnknown==ret )
    {
    	iLog->Log( _L("GetLastLocation failed to return values") );
    	 aRequestorStack.Close();
	    delete identityInfo;
	    delete CoreObj;
    	 __UHEAP_MARKEND;
    	return KErrNone;	
    }
    
    else
    {
    	iLog->Log( _L("GetLastLocation returned") );
    	 aRequestorStack.Close();
	    delete identityInfo;
	    delete CoreObj;
    	 __UHEAP_MARKEND;
    	return KErrGeneral;
    }
    
       
    }*/
    
    
 // -----------------------------------------------------------------------------
// CSAPILocTest::GetLastPosition1
// -----------------------------------------------------------------------------
//
//TInt CSAPILocTest::GetLastPosition1( CStifItemParser& /*aItem*/ )
/*    {
    	TInt aRet,aRet1;
    	TPosition aCurrPos,aLastPos;
    	TTime aCurrPosTime,aLastPosTime;
    	TDateTime aCurrPosDateTime;
    	TReal64 aLatitude1,aLatitude2;  
    	TReal64 aLongitude1,aLongitude2;
    	TReal32 aAltitude1,aAltitude2; 
    // Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "GetLastPosition1" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
    
    // Print to log file
    iLog->Log( KExample );

    __UHEAP_MARK;
    CLocationService *CoreObj = CLocationService :: NewL();
    
    if( NULL == CoreObj)
    {
    	iLog->Log( _L("CLocationService object creation failed") );	
   		__UHEAP_MARKEND;
   		return KErrGeneral;
   	}
    
    aRet = CoreObj->GetLocationL(aCurrPos);
    if(aRet)
    {
    	iLog->Log( _L("GetLocationL failed") );
    	 aRequestorStack.Close();
	    delete identityInfo;
	    delete CoreObj;
    	__UHEAP_MARKEND;
    	return KErrGeneral;	
    }
    
    aCurrPosTime = aCurrPos.Time();
    aRet1 = CoreObj->GetLastKnownLoc(aLastPos);
    if(!aRet1)
    {
    	aLastPosTime = aLastPos.Time();
    	if( aCurrPosTime != aLastPosTime )
    	{
    		iLog->Log( _L("Timestamp mismatch") );
    		 aRequestorStack.Close();
	    delete identityInfo;
	    delete CoreObj;
    		__UHEAP_MARKEND;
    		return KErrGeneral;	
    	}
    	else
    	{
    		aLatitude1  = aCurrPos.Latitude();
    		aLongitude1 = aCurrPos.Longitude();
    		aAltitude1 = aCurrPos.Altitude();
            aLatitude2  = aLastPos.Latitude();
    		aLongitude2 = aLastPos.Longitude();
    		aAltitude2 = aLastPos.Altitude();
    		
    		if( (aLatitude1 != aLatitude2) || (aLongitude1 != aLongitude2) || (aAltitude1 != aAltitude2 ))
    		{
    			iLog->Log( _L("Returned coordinates are wrong") );
    			 aRequestorStack.Close();
	    delete identityInfo;
	    delete CoreObj;
    			__UHEAP_MARKEND;
    			return KErrGeneral;	
   			}
            else
            {
            	iLog->Log( _L("Last postion value returned") );
    			 aRequestorStack.Close();
	    delete identityInfo;
	    delete CoreObj;
    			__UHEAP_MARKEND;
    			return KErrNone;	
            }  
               
        }
    }
    
       
    else
    {
    	iLog->Log( _L("GetLastKnownLoc failed"));
         aRequestorStack.Close();
	    delete identityInfo;
	    delete CoreObj;
	    __UHEAP_MARKEND;       
        return KErrNone;    
    }
    
    
    }*/
    
    
// -----------------------------------------------------------------------------
// CSAPILocTest::GetDistance
// -----------------------------------------------------------------------------
//
TInt CSAPILocTest::GetDistance( CStifItemParser& /*aItem*/ )
    {
    TInt aRet;
    inpparam aInputParam;
    returnCode = KErrNone;
     // Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "GetDistance" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
  
    __UHEAP_MARK;
    
    CLocationService *CoreObj = CLocationService :: NewL();
  
    if( NULL == CoreObj)
    	{
    	OpenFile();
	    LogFile.Write(_L8("\n<GetDistance Test>\n"));
	    LogFile.Write(_L8("Failed..\n"));
	    CloseFile();
   		return KErrGeneral;
   		}
    
    aInputParam.servicechoice = 0;
    aRet = CoreObj->MathOperation(aInputParam);
    if( KErrArgument == aRet )
		{
		OpenFile();
    	LogFile.Write(_L8("\n<GetDistance test> \n"));
 		LogFile.Write(_L8("Passed..\n")) ;
 		CloseFile();
      	returnCode = KErrNone;  
		}
    else
    	{
 		OpenFile();
 		LogFile.Write(_L8("\n<GetDistance test> \n"));
 		LogFile.Write(_L8("Failed..\n")) ;
 		CloseFile();
      	returnCode = KErrGeneral;     	
    	}		
   
   
   delete CoreObj;

	__UHEAP_MARKEND;       
    return KErrNone;    
  }
    
// -----------------------------------------------------------------------------
// CSAPILocTest::GetDistance2
// -----------------------------------------------------------------------------
//
TInt CSAPILocTest::GetDistance2( CStifItemParser& /*aItem*/ )
    {
  	TInt aRet;
 // 	TPositionInfo currPos[2];
  	TPosition currPos1[2];
  	inpparam aInputParam;
    TReal64 aLatitude1 = 10,aLatitude2 = 20;
	TReal64 aLongitude1 = 120,aLongitude2 = 140;
	TReal32 aAltitude1 = 500,aAltitude2 = 500; 
  	returnCode = KErrNone;
  	
    // Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "GetDistance2" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
    
    __UHEAP_MARK;
  
    CLocationService *CoreObj = CLocationService :: NewL();
    
    if( NULL == CoreObj)
    	{
    	OpenFile();
	    LogFile.Write(_L8("\n<GetDistance2 Test>\n"));
	    LogFile.Write(_L8("Failed(CoreObj Creation)..\n"));
	    CloseFile();
   		return KErrGeneral;
   		}
    
    _LIT(Kidentity ,"Coreclass Testing" ) ;
	//not needed any more
	/*RRequestorStack aRequestorStack;
	const CRequestor* identityInfo = CRequestor::NewL(1 , 1 , Kidentity) ;
    aRequestorStack.Insert(identityInfo,0);
    
    CoreObj->SetRequestorIdentityL(aRequestorStack) ;*/
    
    /*for( TInt i=0;i<2;i++)
    	{
        ret[i] = CoreObj->GetLocationL(&currPos[i]);
    	}
    if( !ret[0] && !ret[1])
    	{
    
    	
   		currPos[0].GetPosition(currPos1[0]);
    	currPos[1].GetPosition(currPos1[1]);
    	
    	aLatitude1  = currPos1[0].Latitude();
		aLongitude1 = currPos1[0].Longitude() ;
		aAltitude1  = currPos1[0].Altitude() ;
	   	aLatitude2  = currPos1[1].Latitude();
		aLongitude2 = currPos1[1].Longitude() ;
		aAltitude2  = currPos1[1].Altitude() ;
	*/	
    	aInputParam.servicechoice = 10;
    	aInputParam.source.SetCoordinate(aLatitude1,aLongitude1,aAltitude1);
    	aInputParam.destination.SetCoordinate(aLatitude2,aLongitude2,aAltitude2);
    	
    	aRet = CoreObj->MathOperation(aInputParam);
    	
    	if(KErrNotSupported == aRet)
    		{
    		OpenFile();
	    	TBuf8<50> buf ;
	 		TRealFormat format; 
	 		LogFile.Write(_L8("\n<GetDistance2 test> \n"));
	 		LogFile.Write(_L8("Passed..\n"));
	 		CloseFile();
	        returnCode = KErrNone;  
    		}
	    else
       		{
   			OpenFile();
     		LogFile.Write(_L8("\n<GetDistance2 test> \n"));
 		 	LogFile.Write(_L8("Failed(Wrong error)..\n"));
 		 	CloseFile();
 		 	returnCode = KErrGeneral;
       		}
    /*	}
    else
    	{
    	OpenFile();
    	LogFile.Write(_L8("\n<GetDistance2 test> \n"));
 	    LogFile.Write(_L8("Failed..\n"));
 	    CloseFile();
 	    returnCode = KErrGeneral;	
    	}
    */
   /*aRequestorStack.Close();
   delete identityInfo;*/
   delete CoreObj;
   
   __UHEAP_MARKEND;
   return returnCode;
    }
// -----------------------------------------------------------------------------
// CSAPILocTest::GetDistance3
// -----------------------------------------------------------------------------
//
TInt CSAPILocTest::GetDistance3( CStifItemParser& /*aItem*/ )
    {
  	TInt ret[2],aRet;
  	TPositionInfo currPos[2];
  	TPosition currPos1[2];
  	inpparam aInputParam;
    returnCode = KErrNone;
    TReal64 aLatitude1,aLatitude2;
	TReal64 aLongitude1,aLongitude2;
	TReal32 aAltitude1,aAltitude2; 
      // Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "GetDistance3" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
  
    __UHEAP_MARK;
  
    CLocationService *CoreObj = CLocationService :: NewL();
    
    if( NULL == CoreObj)
    	{
    	OpenFile();
	    LogFile.Write(_L8("\n<GetDistance3 Test>\n"));
	    LogFile.Write(_L8("Failed..\n"));
	    CloseFile();
   		return KErrGeneral;
   		}
    
    _LIT(Kidentity ,"Coreclass Testing" ) ;
    //not needed any more
	/*RRequestorStack aRequestorStack;
	const CRequestor* identityInfo = CRequestor::NewL(1 , 1 , Kidentity) ;
    aRequestorStack.Insert(identityInfo,0);
    
    CoreObj->SetRequestorIdentityL(aRequestorStack) ;*/
    
    for( TInt i=0;i<2;i++)
    	{
        ret[i] = CoreObj->GetLocationL(&currPos[i]);
    	}
    if( (KErrNone == ret[0]) && (KErrNone == ret[1] ))
    	{
    	currPos[0].GetPosition(currPos1[0]);
    	currPos[1].GetPosition(currPos1[1]);
    	aLatitude1  = currPos1[0].Latitude();
		aLongitude1 = currPos1[0].Longitude() ;
		aAltitude1  = currPos1[0].Altitude() ;
	   	aLatitude2  = currPos1[1].Latitude();
		aLongitude2 = currPos1[1].Longitude() ;
		aAltitude2  = currPos1[1].Altitude() ;
	    
	    aInputParam.servicechoice = 0;
    	aInputParam.source.SetCoordinate(aLatitude1,aLongitude1,aAltitude1);
    	aInputParam.destination.SetCoordinate(aLatitude2,aLongitude2,aAltitude2);
    	
    	aRet = CoreObj->MathOperation(aInputParam);
    	
    	if( KErrNone == aRet )
    		{
    		OpenFile();
	    	TBuf8<50> buf ;
	 		TRealFormat format; 
	 		LogFile.Write(_L8("\n<GetDistance3 test> \n"));
	 		buf.Num(aInputParam.result, format) ;
	 		LogFile.Write(_L8("Distance = "));
	 		LogFile.Write(buf) ;
	 		LogFile.Write(_L8("\n")) ;
	 		CloseFile();
	      	if( aInputParam.result<0 )
	      		{
	      		returnCode = KErrGeneral; 
	      		}
	      	else
	      		{
	      		returnCode = KErrNone;  
	      		}
	      	}
    	else
    		{
    		OpenFile();
       		LogFile.Write(_L8("\n<GetDistance3 test> \n"));
	    	LogFile.Write(_L8("Failed(Math op).. \n"));
	 	    CloseFile();
	 	    returnCode = KErrGeneral;
    		}
	   	}
    else
    	{  
    	OpenFile();
     	LogFile.Write(_L8("\n<GetDistance3 test> \n"));
	   	LogFile.Write(_L8("Failed(getloc error).. \n"));
	    CloseFile();
	    returnCode = KErrGeneral;	
    	}
   
   /*aRequestorStack.Close();
   delete identityInfo;*/
   delete CoreObj;
	  
	  __UHEAP_MARKEND; 	
   
    return returnCode;
    }
        
// -----------------------------------------------------------------------------
// CSAPILocTest::GetDistance4
// -----------------------------------------------------------------------------
//
TInt CSAPILocTest::GetDistance4( CStifItemParser& /*aItem*/ )
    {
    TInt aRet;
  	inpparam aInputParam;
    TTime aCurrentTime;
    returnCode = KErrNone;
    
    TCoordinate  aCoordinate1(90,180),aCoordinate2(-90,0);
//	TLocality aLocality1(aCordinate1,5),aLocality2(aCordinate2,5);
//	TPosition aPosition1(aLocality1,aCurrentTime),aPosition2(aLocality2,aCurrentTime);
		 
		// Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "GetDistance4" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
  
    __UHEAP_MARK;
  
    CLocationService *CoreObj = CLocationService :: NewL();
    
    if( NULL == CoreObj)
    	{
    	OpenFile();
	    LogFile.Write(_L8("\n<GetDistance4 Test>\n"));
	    LogFile.Write(_L8("Failed..\n"));
	    CloseFile();
   		return KErrGeneral;
   		}
    
   		
    	aInputParam.servicechoice = 0;
      	aInputParam.source = aCoordinate1;
      	aInputParam.destination = aCoordinate2;
    //	aInputParam.source.SetPosition(aPosition1);
    //	aInputParam.destination.SetPosition(aPosition2);
    	
    	aRet = CoreObj->MathOperation(aInputParam);
    	if(KErrNone == aRet)
    		{
    		OpenFile();
	    	TBuf8<50> buf ;
	 		TRealFormat format; 
	 		LogFile.Write(_L8("\n<GetDistance4 test> \n"));
	 		buf.Num(aInputParam.result, format) ;
	 		LogFile.Write(_L8("Distance = "));
	 		LogFile.Write(buf) ;
	 		LogFile.Write(_L8("\n")) ;
	 		CloseFile();
	        
	        if( aInputParam.result<0 )
	      		{
	      		returnCode = KErrGeneral; 
	      		}
	      	else
	      		{
	      		returnCode = KErrNone;  
	      		}
    		
    		}
	    
     else
        {
        OpenFile();
    	LogFile.Write(_L8("\n<GetDistance4 test> \n"));
 	    LogFile.Write(_L8("Failed..\n"));
 	    CloseFile();
 	    returnCode = KErrGeneral;	
        }
    delete CoreObj;
    
    __UHEAP_MARKEND;	
    
    return returnCode;	
	}


// -----------------------------------------------------------------------------
// CSAPILocTest::GetDistance5
// -----------------------------------------------------------------------------
//
TInt CSAPILocTest::GetDistance5( CStifItemParser& /*aItem*/ )
    {
    TInt aRet;
  	inpparam aInputParam;
    TTime aCurrentTime;
    returnCode = KErrNone;
    
    TCoordinate  aCoordinate1(0,0),aCoordinate2(0,0);
//	TLocality aLocality1(aCordinate1,5),aLocality2(aCordinate2,5);
//	TPosition aPosition1(aLocality1,aCurrentTime),aPosition2(aLocality2,aCurrentTime);
	 
		// Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "GetDistance5" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
  
   __UHEAP_MARK;
  
   CLocationService *CoreObj = CLocationService :: NewL();
    
    if( NULL == CoreObj)
    	{
    	OpenFile();
	    LogFile.Write(_L8("\n<GetDistance5 Test>\n"));
	    LogFile.Write(_L8("Failed..\n"));
	    CloseFile();
   		return KErrGeneral;
   		}
    
   	
    	aInputParam.servicechoice = 0;
    	aInputParam.source = aCoordinate1;
    	aInputParam.destination = aCoordinate2;
    //	aInputParam.source.SetPosition(aPosition1);
    //	aInputParam.destination.SetPosition(aPosition2);
    	
    	aRet = CoreObj->MathOperation(aInputParam);
    	
    	if(( KErrNone == aRet ) && (aInputParam.result == 0))
    		{
    		OpenFile();
	    	TBuf8<50> buf ;
	 		TRealFormat format; 
	 		LogFile.Write(_L8("\n<GetDistance5 test> \n"));
	 		buf.Num(aInputParam.result, format) ;
	 		LogFile.Write(_L8("Distance = "));
	 		LogFile.Write(buf) ;
	 		LogFile.Write(_L8("\n")) ;
	 		CloseFile();
	      	
	      	if( aInputParam.result<0 )
	      		{
	      		returnCode = KErrGeneral; 
	      		}
	      	else
	      		{
	      		returnCode = KErrNone;  
	      		} 
    		}
	   
	    else
        {
        OpenFile();
    	LogFile.Write(_L8("\n<GetDistance5 test> \n"));
 	    LogFile.Write(_L8("Failed..\n"));
 	    CloseFile();
 	    returnCode = KErrGeneral;	
        }
        
     delete CoreObj;
	  __UHEAP_MARKEND;
 	  return returnCode;  		
   	 }

// -----------------------------------------------------------------------------
// CSAPILocTest::GetDistance6
// -----------------------------------------------------------------------------
//
TInt CSAPILocTest::GetDistance6( CStifItemParser& /*aItem*/ )
    {
    TInt aRet;
  	inpparam aInputParam;
    TTime aCurrentTime;
    returnCode = KErrNone;
    TCoordinate  aCordinate1(80,190),aCordinate2(-80,-210);
//	TLocality aLocality1(aCordinate1,5),aLocality2(aCordinate2,5);
//	TPosition aPosition1(aLocality1,aCurrentTime),aPosition2(aLocality2,aCurrentTime);
	 
		// Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "GetDistance6" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
  
    __UHEAP_MARK;
  
    CLocationService *CoreObj = CLocationService :: NewL();
    
    if( NULL == CoreObj)
    	{
    	OpenFile();
	    LogFile.Write(_L8("\n<GetDistance6 Test>\n"));
	    LogFile.Write(_L8("Failed..\n"));
	    CloseFile();
   		return KErrGeneral;
   		}
    
   	
    	aInputParam.servicechoice = 0;
    	aInputParam.source = aCordinate1;
    	aInputParam.destination = aCordinate2;
  //  	aInputParam.source.SetPosition(aPosition1);
  //  	aInputParam.destination.SetPosition(aPosition2);
    	
    	aRet = CoreObj->MathOperation(aInputParam);
    	
    	if( KErrNone == aRet )
    		{
    		OpenFile();
	    	TBuf8<50> buf ;
	 		TRealFormat format; 
	 		LogFile.Write(_L8("\n<GetDistance6 test> \n"));
	 		buf.Num(aInputParam.result, format) ;
	 		LogFile.Write(_L8("Distance = "));
	 		LogFile.Write(buf) ;
	 		LogFile.Write(_L8("\n")) ;
	 		CloseFile();
      		
      		if( aInputParam.result<0 )
	      		{
	      		returnCode = KErrGeneral; 
	      		}
	      	else
	      		{
	      		returnCode = KErrNone;  
	      		}
    		}
	    
       else
       	{
       	OpenFile();
    	LogFile.Write(_L8("\n<GetDistance6 test> \n"));
 	    LogFile.Write(_L8("Failed..\n"));
 	    CloseFile();
 	    returnCode = KErrGeneral;	
       	} 
       	
   delete CoreObj;
   __UHEAP_MARKEND; 
   return returnCode; 		
   }


// -----------------------------------------------------------------------------
// CSAPILocTest::GetDistance7
// -----------------------------------------------------------------------------
//
TInt CSAPILocTest::GetDistance7( CStifItemParser& /*aItem*/ )
    {
    TInt aRet;
  	inpparam aInputParam;
    TTime aCurrentTime;
    returnCode = KErrNone;
    
    TCoordinate  aCordinate1(105,190),aCordinate2(-105,-210);
//	TLocality aLocality1(aCordinate1,5),aLocality2(aCordinate2,5);
//	TPosition aPosition1(aLocality1,aCurrentTime),aPosition2(aLocality2,aCurrentTime);
	 
		// Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "GetDistance7" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
    
    __UHEAP_MARK;
    
    CLocationService *CoreObj = CLocationService :: NewL();
    
    if( NULL == CoreObj)
    	{
    	OpenFile();
	    LogFile.Write(_L8("\n<GetDistance7 Test>\n"));
	    LogFile.Write(_L8("Failed..\n"));
	    CloseFile();
   		return KErrGeneral;
   		}
       	
    	aInputParam.servicechoice = 0;
    	aInputParam.source = aCordinate1;
    	aInputParam.destination = aCordinate2;
//    	aInputParam.source.SetPosition(aPosition1);
//    	aInputParam.destination.SetPosition(aPosition2);
    	aRet = CoreObj->MathOperation(aInputParam);
    	
    	if( KErrNone == aRet)
    		{
    		OpenFile();
	    	TBuf8<50> buf ;
	 		TRealFormat format; 
	 		LogFile.Write(_L8("\n<GetDistance7 test> \n"));
	 		buf.Num(aInputParam.result, format) ;
	 		LogFile.Write(_L8("Distance = "));
	 		LogFile.Write(buf) ;
	 		LogFile.Write(_L8("\n")) ;
	 		CloseFile();
	      	
	      	if( aInputParam.result<0 )
	      		{
	      		returnCode = KErrGeneral; 
	      		}
	      	else
	      		{
	      		returnCode = KErrNone;  
	      		}
    		}
	    else
        	{
       		OpenFile();
	    	LogFile.Write(_L8("\n<GetDistance7 position returned error> \n"));
	 	    LogFile.Write(_L8("Failed..\n"));
	 	    CloseFile();
	 	    returnCode = KErrGeneral;
	 	  	}
	 	  
   delete CoreObj;
   __UHEAP_MARKEND;
   return returnCode;	
   }

// -----------------------------------------------------------------------------
// CSAPILocTest::GetDistance8
// -----------------------------------------------------------------------------
//
TInt CSAPILocTest::GetDistance8( CStifItemParser& /*aItem*/ )
	{
    TInt aRet;
  	inpparam aInputParam;
    TTime aCurrentTime;
    returnCode = KErrNone;
    
    TCoordinate  aCordinate1(360,400),aCordinate2(200,480);
//	TLocality aLocality1(aCordinate1,5),aLocality2(aCordinate2,5);
//	TPosition aPosition1(aLocality1,aCurrentTime),aPosition2(aLocality2,aCurrentTime);
		 
		// Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "GetDistance8" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
   
    __UHEAP_MARK;
   
    CLocationService *CoreObj = CLocationService :: NewL();
    
    if( NULL == CoreObj)
    	{
    	OpenFile();
	    LogFile.Write(_L8("\n<GetDistance8 Test>\n"));
	    LogFile.Write(_L8("Failed..\n"));
	    CloseFile();
   		return KErrGeneral;
   		}
    
   	
    	aInputParam.servicechoice = 0;
    	aInputParam.source = aCordinate1;
    	aInputParam.destination = aCordinate2;
//    	aInputParam.source.SetPosition(aPosition1);
//    	aInputParam.destination.SetPosition(aPosition2);
    	
    	aRet = CoreObj->MathOperation(aInputParam);
    
    	if( KErrNone == aRet )
    		{
    		OpenFile();
	    	TBuf8<50> buf ;
	 		TRealFormat format; 
	 		LogFile.Write(_L8("\n<GetDistance8 test> \n"));
	 		buf.Num(aInputParam.result, format) ;
	 		LogFile.Write(_L8("Distance = "));
	 		LogFile.Write(buf) ;
	 		LogFile.Write(_L8("\n")) ;
	 		CloseFile();
	      	if( aInputParam.result<0 )
	      		{
	      		returnCode = KErrGeneral; 
	      		}
	      	else
	      		{
	      		returnCode = KErrNone;  
	      		}  
    		}
	   	else
	   		{
		   	OpenFile();
		   	LogFile.Write(_L8("\n<GetDistance8 test> \n"));
		   	LogFile.Write(_L8("Failed..\n"));
            CloseFile();
		    returnCode = KErrGeneral;
		 	}
		 	
    delete CoreObj;
 	__UHEAP_MARKEND;
    return returnCode;	
   }

// -----------------------------------------------------------------------------
// CSAPILocTest::GetDistance9
// -----------------------------------------------------------------------------
//
TInt CSAPILocTest::GetDistance9( CStifItemParser& /*aItem*/ )
	{
    TInt aRet;
  	inpparam aInputParam;
    TTime aCurrentTime;
    returnCode = KErrNone;
    TRealX nan;
    nan.SetNaN();
    TCoordinate  aCordinate1(nan,170),aCordinate2(70,170);

	// Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "GetDistance9" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
   
    __UHEAP_MARK;
   
    CLocationService *CoreObj = CLocationService :: NewL();
    
    if( NULL == CoreObj)
    	{
    	OpenFile();
	    LogFile.Write(_L8("\n<GetDistance9 Test>\n"));
	    LogFile.Write(_L8("Failed..\n"));
	    CloseFile();
   		return KErrGeneral;
   		}
    
   	
    	aInputParam.servicechoice = 0;
    	aInputParam.source = aCordinate1;
    	aInputParam.destination = aCordinate2;
  		aRet = CoreObj->MathOperation(aInputParam);
    
    	if( KErrArgument == aRet )
    		{
    		OpenFile();
	    	LogFile.Write(_L8("\n<GetDistance9 test> \n"));
	 		LogFile.Write(_L8("Passed..\n")) ;
	 		CloseFile();
	      	returnCode = KErrNone;  
    		}
	   	else
	   		{
		   	OpenFile();
		   	LogFile.Write(_L8("\n<GetDistance9 test> \n"));
		   	LogFile.Write(_L8("Failed..\n"));
            CloseFile();
		    returnCode = KErrGeneral;
		 	}
		 	
    delete CoreObj;
 	__UHEAP_MARKEND;
    return returnCode;	
   }


// -----------------------------------------------------------------------------
// CSAPILocTest::GetDistance10
// -----------------------------------------------------------------------------
//
TInt CSAPILocTest::GetDistance10( CStifItemParser& /*aItem*/ )
	{
    TInt aRet;
  	inpparam aInputParam;
    TTime aCurrentTime;
    returnCode = KErrNone;
    TRealX nan;
    nan.SetNaN();
    TCoordinate  aCordinate1(30,nan),aCordinate2(70,170);

	// Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "GetDistance10" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
   
    __UHEAP_MARK;
   
    CLocationService *CoreObj = CLocationService :: NewL();
    
    if( NULL == CoreObj)
    	{
    	OpenFile();
	    LogFile.Write(_L8("\n<GetDistance10 Test>\n"));
	    LogFile.Write(_L8("Failed..\n"));
	    CloseFile();
   		return KErrGeneral;
   		}
    
   	
    	aInputParam.servicechoice = 0;
    	aInputParam.source = aCordinate1;
    	aInputParam.destination = aCordinate2;
  		aRet = CoreObj->MathOperation(aInputParam);
    
    	if( KErrArgument == aRet )
    		{
    		OpenFile();
	    	LogFile.Write(_L8("\n<GetDistance10 test> \n"));
	 		LogFile.Write(_L8("Passed..\n")) ;
	 		CloseFile();
	      	returnCode = KErrNone;  
    		}
	   	else
	   		{
		   	OpenFile();
		   	LogFile.Write(_L8("\n<GetDistance10 test> \n"));
		   	LogFile.Write(_L8("Failed..\n"));
            CloseFile();
		    returnCode = KErrGeneral;
		 	}
		 	
   delete CoreObj;
 	__UHEAP_MARKEND;
    return returnCode;	
   }


// -----------------------------------------------------------------------------
// CSAPILocTest::GetDistance11
// -----------------------------------------------------------------------------
//
TInt CSAPILocTest::GetDistance11( CStifItemParser& /*aItem*/ )
	{
    TInt aRet;
  	inpparam aInputParam;
    TTime aCurrentTime;
    returnCode = KErrNone;
    TRealX nan;
    nan.SetNaN();
    TCoordinate  aCordinate1(30,110),aCordinate2(nan,170);

	// Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "GetDistance11" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
   
    __UHEAP_MARK;
   
    CLocationService *CoreObj = CLocationService :: NewL();
    
    if( NULL == CoreObj)
    	{
    	OpenFile();
	    LogFile.Write(_L8("\n<GetDistance11 Test>\n"));
	    LogFile.Write(_L8("Failed..\n"));
	    CloseFile();
   		return KErrGeneral;
   		}
    
   	
	aInputParam.servicechoice = 0;
	aInputParam.source = aCordinate1;
	aInputParam.destination = aCordinate2;
	aRet = CoreObj->MathOperation(aInputParam);

	if( KErrArgument == aRet )
		{
		OpenFile();
    	LogFile.Write(_L8("\n<GetDistance11 test> \n"));
 		LogFile.Write(_L8("Passed..\n")) ;
 		CloseFile();
      	returnCode = KErrNone;  
		}
   	else
   		{
	   	OpenFile();
	   	LogFile.Write(_L8("\n<GetDistance11 test> \n"));
	   	LogFile.Write(_L8("Failed..\n"));
        CloseFile();
	    returnCode = KErrGeneral;
	 	}
		 	
    delete CoreObj;
 	__UHEAP_MARKEND;
    return returnCode;	
   }


// -----------------------------------------------------------------------------
// CSAPILocTest::GetDistance12
// -----------------------------------------------------------------------------
//
TInt CSAPILocTest::GetDistance12( CStifItemParser& /*aItem*/ )
	{
    TInt aRet;
  	inpparam aInputParam;
    TTime aCurrentTime;
    returnCode = KErrNone;
    TRealX nan;
    nan.SetNaN();
    TCoordinate  aCordinate1(30,110),aCordinate2(40,nan);

	// Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "GetDistance12" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
   
    __UHEAP_MARK;
   
    CLocationService *CoreObj = CLocationService :: NewL();
    
    if( NULL == CoreObj)
    	{
    	OpenFile();
	    LogFile.Write(_L8("\n<GetDistance12 Test>\n"));
	    LogFile.Write(_L8("Failed..\n"));
	    CloseFile();
   		return KErrGeneral;
   		}
    
   	
	aInputParam.servicechoice = 0;
	aInputParam.source = aCordinate1;
	aInputParam.destination = aCordinate2;
	aRet = CoreObj->MathOperation(aInputParam);

	if( KErrArgument == aRet )
		{
		OpenFile();
    	LogFile.Write(_L8("\n<GetDistance12 test> \n"));
 		LogFile.Write(_L8("Passed..\n")) ;
 		CloseFile();
      	returnCode = KErrNone;  
		}
   	else
   		{
	   	OpenFile();
	   	LogFile.Write(_L8("\n<GetDistance12 test> \n"));
	   	LogFile.Write(_L8("Failed..\n"));
        CloseFile();
	    returnCode = KErrGeneral;
	 	}
		 	
    delete CoreObj;
 	__UHEAP_MARKEND;
    return returnCode;	
   }

// -----------------------------------------------------------------------------
// CSAPILocTest::GetBearing
// -----------------------------------------------------------------------------
//
TInt CSAPILocTest::GetBearing( CStifItemParser& /*aItem*/ )
	{
    TInt aRet;
  	inpparam aInputParam;
    TTime aCurrentTime;
    returnCode = KErrNone;
    
	// Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "GetBearing" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
   
    __UHEAP_MARK;
   
    CLocationService *CoreObj = CLocationService :: NewL();
    
    if( NULL == CoreObj)
    	{
    	OpenFile();
	    LogFile.Write(_L8("\n<GetBearing Test>\n"));
	    LogFile.Write(_L8("Failed..\n"));
	    CloseFile();
   		return KErrGeneral;
   		}
    
   	
	aInputParam.servicechoice = 1;
	aRet = CoreObj->MathOperation(aInputParam);

	if( KErrArgument == aRet )
		{
		OpenFile();
    	LogFile.Write(_L8("\n<GetBearing test> \n"));
 		LogFile.Write(_L8("Passed..\n")) ;
 		CloseFile();
      	returnCode = KErrNone;  
		}
   	else
   		{
	   	OpenFile();
	   	LogFile.Write(_L8("\n<GetBearing test> \n"));
	   	LogFile.Write(_L8("Failed..\n"));
        CloseFile();
	    returnCode = KErrGeneral;
	 	}
		 	
    delete CoreObj;
 	__UHEAP_MARKEND;
    return returnCode;	
   }


// -----------------------------------------------------------------------------
// CSAPILocTest::GetBearing1
// -----------------------------------------------------------------------------
//
TInt CSAPILocTest::GetBearing1( CStifItemParser& /*aItem*/ )
	{
    TInt ret[2],aRet;
  	TPositionInfo currPos[2];
  	TPosition currPos1[2];
  	inpparam aInputParam;
    TReal64 aLatitude1,aLatitude2;
	TReal64 aLongitude1,aLongitude2;
	TReal32 aAltitude1,aAltitude2; 
  	returnCode = KErrNone;
    
	// Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "GetBearing1" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
   
    __UHEAP_MARK;
    
    CLocationService *CoreObj = CLocationService :: NewL();
    
    if( NULL == CoreObj)
    	{
    	OpenFile();
	    LogFile.Write(_L8("\n<GetBearing1 Test>\n"));
	    LogFile.Write(_L8("Failed..\n"));
	    CloseFile();
   		return KErrGeneral;
   		}
    
    _LIT(Kidentity ,"Coreclass Testing" ) ;
	//not needed any more
	/*RRequestorStack aRequestorStack;
	const CRequestor* identityInfo = CRequestor::NewL(1 , 1 , Kidentity) ;
    aRequestorStack.Insert(identityInfo,0);
    
    CoreObj->SetRequestorIdentityL(aRequestorStack) ;*/
    
   /* for( TInt i=0;i<2;i++)
    	{
      ret[i] = CoreObj->GetLocationL(&currPos[i]);
    	}
   */
    
    ret[0] = CoreObj->GetLocationL(&currPos[0]) ;
    
    User::After(30000000) ;
    
    ret[1] = CoreObj->GetLocationL(&currPos[1]) ;
    
    if( !ret[0] && !ret[1])
    	{
    	aInputParam.servicechoice = 1;
    	currPos[0].GetPosition(currPos1[0]);
    	currPos[1].GetPosition(currPos1[1]);
    	aLatitude1  = currPos1[0].Latitude();
		aLongitude1 = currPos1[0].Longitude() ;
		//aAltitude1  = currPos1[0].Altitude() ;
		//aAltitude1  = NaN;
	   	aLatitude2  = currPos1[1].Latitude();
		aLongitude2 = currPos1[1].Longitude() ;
		//aAltitude2  = currPos1[1].Altitude() ;
		
    	aInputParam.source.SetCoordinate(aLatitude1,aLongitude1/*,aAltitude1*/);
    	aInputParam.destination.SetCoordinate(aLatitude2,aLongitude2/*,aAltitude2*/);
    	
    	aRet = CoreObj->MathOperation(aInputParam);
    	
    	if(KErrNone == aRet)
    		{
    		OpenFile();
	    	TBuf8<50> buf ;
	 		TRealFormat format; 
	 		LogFile.Write(_L8("\n<GetBearing1 test> \n"));
	 		buf.Num(aInputParam.result, format) ;
	 		LogFile.Write(_L8("Bearing = "));
	 		LogFile.Write(buf) ;
	 		LogFile.Write(_L8("\n")) ;
	 		CloseFile();
	      	returnCode = KErrNone;  
    		}
    	else if(aRet == KErrPositionIncalculable )
	    	{
	    	CloseFile();
	      	returnCode = KErrNone; 
	    		
	    	}
	    else
       		{
   			OpenFile();
     		LogFile.Write(_L8("\n<GetBearing1 test> \n"));
 		 	LogFile.Write(_L8("Failed @ math op..\n"));
 		 	CloseFile();
 		 	returnCode = KErrGeneral;
       		}
    	}
    else
    	{
    	OpenFile();
    	LogFile.Write(_L8("\n<GetBearing1 test> \n"));
 	    LogFile.Write(_L8("Failed * coreob..\n"));
 	    CloseFile();
 	    returnCode = KErrGeneral;	
    	}
    
   
   delete CoreObj;
   __UHEAP_MARKEND;
   return returnCode;
   }


// -----------------------------------------------------------------------------
// CSAPILocTest::GetBearing2
// -----------------------------------------------------------------------------
//
TInt CSAPILocTest::GetBearing2( CStifItemParser& /*aItem*/ )
    {
    TInt aRet;
  	inpparam aInputParam;
    returnCode = KErrNone;
    
    TCoordinate  aCordinate1(90,90),aCordinate2(90,90);

	// Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "GetBearing2" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
    
    __UHEAP_MARK;
    
    CLocationService *CoreObj = CLocationService :: NewL();
    
    if( NULL == CoreObj)
    	{
    	OpenFile();
	    LogFile.Write(_L8("\n<GetBearing2 Test>\n"));
	    LogFile.Write(_L8("Failed..\n"));
	    CloseFile();
   		return KErrGeneral;
   		}
       	
	aInputParam.servicechoice = 1;
	aInputParam.source = aCordinate1;
	aInputParam.destination = aCordinate2;

	aRet = CoreObj->MathOperation(aInputParam);
	
	if(KErrPositionIncalculable == aRet)
		{
		OpenFile();
    	TBuf8<50> buf ;
 		TRealFormat format; 
 		LogFile.Write(_L8("\n<GetBearing2 test> \n"));
 		LogFile.Write(_L8("Passed..\n"));
 		CloseFile();
        returnCode = KErrNone;  
		}
    else
   		{
		OpenFile();
 		LogFile.Write(_L8("\n<GetBearing2 test> \n"));
	 	LogFile.Write(_L8("Failed..\n"));
	 	CloseFile();
	 	returnCode = KErrGeneral;
   		}
   delete CoreObj;
   __UHEAP_MARKEND;
   return returnCode;	
   }


// -----------------------------------------------------------------------------
// CSAPILocTest::GetBearing3
// -----------------------------------------------------------------------------
//
TInt CSAPILocTest::GetBearing3( CStifItemParser& /*aItem*/ )
    {
    TInt aRet;
  	inpparam aInputParam;
    returnCode = KErrNone;
    
    TCoordinate  aCordinate1(0,0),aCordinate2(0,0);

	// Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "GetBearing3" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
    
    __UHEAP_MARK;
    
    CLocationService *CoreObj = CLocationService :: NewL();
    
    if( NULL == CoreObj)
    	{
    	OpenFile();
	    LogFile.Write(_L8("\n<GetBearing3 Test>\n"));
	    LogFile.Write(_L8("Failed..\n"));
	    CloseFile();
   		return KErrGeneral;
   		}
       	
	aInputParam.servicechoice = 1;
	aInputParam.source = aCordinate1;
	aInputParam.destination = aCordinate2;

	aRet = CoreObj->MathOperation(aInputParam);
	
	if(KErrPositionIncalculable == aRet )
		{
		OpenFile();
    	TBuf8<50> buf ;
 		TRealFormat format; 
 		LogFile.Write(_L8("\n<GetBearing3 test> \n"));
 		LogFile.Write(_L8("Passed..\n"));
 		CloseFile();
        returnCode = KErrNone;  
		}
   	else
   		{
	   	OpenFile();
	   	LogFile.Write(_L8("\n<GetBearing3 test> \n"));
	   	LogFile.Write(_L8("Failed..\n"));
        CloseFile();
	    returnCode = KErrGeneral;
	 	}
   delete CoreObj;
   __UHEAP_MARKEND;
   return returnCode;	
   }


// -----------------------------------------------------------------------------
// CSAPILocTest::GetBearing4
// -----------------------------------------------------------------------------
//
TInt CSAPILocTest::GetBearing4( CStifItemParser& /*aItem*/ )
    {
    TInt aRet;
  	inpparam aInputParam;
    returnCode = KErrNone;
    
    TCoordinate  aCordinate1(40,90),aCordinate2(30,120);

	// Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "GetBearing4" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
    
    __UHEAP_MARK;
    
    CLocationService *CoreObj = CLocationService :: NewL();
    
    if( NULL == CoreObj)
    	{
    	OpenFile();
	    LogFile.Write(_L8("\n<GetBearing4 Test>\n"));
	    LogFile.Write(_L8("Failed..\n"));
	    CloseFile();
   		return KErrGeneral;
   		}
       	
	aInputParam.servicechoice = 1;
	aInputParam.source = aCordinate1;
	aInputParam.destination = aCordinate2;

	aRet = CoreObj->MathOperation(aInputParam);
	
	if( KErrNone == aRet )
		{
		OpenFile();
    	TBuf8<50> buf ;
 		TRealFormat format; 
 		LogFile.Write(_L8("\n<GetBearing4 test> \n"));
 		buf.Num(aInputParam.result, format) ;
 		LogFile.Write(_L8("Bearing = "));
 		LogFile.Write(buf) ;
 		LogFile.Write(_L8("\n")) ;
 		CloseFile();
      	returnCode = KErrNone;  
		}
   	else
   		{
	   	OpenFile();
	   	LogFile.Write(_L8("\n<GetBearing4 test> \n"));
	   	LogFile.Write(_L8("Failed..\n"));
        CloseFile();
	    returnCode = KErrGeneral;
	 	}
   delete CoreObj;
   __UHEAP_MARKEND;
   return returnCode;	
   }


// -----------------------------------------------------------------------------
// CSAPILocTest::GetBearing5
// -----------------------------------------------------------------------------
//
TInt CSAPILocTest::GetBearing5( CStifItemParser& /*aItem*/ )
    {
    TInt aRet;
  	inpparam aInputParam;
    returnCode = KErrNone;
    
    TCoordinate  aCordinate1(90,180),aCordinate2(-90,-180);

	// Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "GetBearing5" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
    
    __UHEAP_MARK;
    
    CLocationService *CoreObj = CLocationService :: NewL();
    
    if( NULL == CoreObj)
    	{
    	OpenFile();
	    LogFile.Write(_L8("\n<GetBearing5 Test>\n"));
	    LogFile.Write(_L8("Failed..\n"));
	    CloseFile();
   		return KErrGeneral;
   		}
       	
	aInputParam.servicechoice = 1;
	aInputParam.source = aCordinate1;
	aInputParam.destination = aCordinate2;

	aRet = CoreObj->MathOperation(aInputParam);
	
	if(KErrPositionIncalculable == aRet )
		{
		OpenFile();
    	TBuf8<50> buf ;
 		TRealFormat format; 
 		LogFile.Write(_L8("\n<GetBearing5 test> \n"));
 		LogFile.Write(_L8("Passed..\n"));
 		CloseFile();
        returnCode = KErrNone;  
		}
   	else
   		{
	   	OpenFile();
	   	LogFile.Write(_L8("\n<GetBearing5 test> \n"));
	   	LogFile.Write(_L8("Failed..\n"));
        CloseFile();
	    returnCode = KErrGeneral;
	 	}
   delete CoreObj;
   __UHEAP_MARKEND;
   return returnCode;	
   }


// -----------------------------------------------------------------------------
// CSAPILocTest::GetBearing6
// -----------------------------------------------------------------------------
//
TInt CSAPILocTest::GetBearing6( CStifItemParser& /*aItem*/ )
    {
    TInt aRet;
  	inpparam aInputParam;
    returnCode = KErrNone;
    
    TCoordinate  aCordinate1(-120,-180),aCordinate2(160,180);

	// Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "GetBearing6" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
    
    __UHEAP_MARK;
    
    CLocationService *CoreObj = CLocationService :: NewL();
    
    if( NULL == CoreObj)
    	{
    	OpenFile();
	    LogFile.Write(_L8("\n<GetBearing6 Test>\n"));
	    LogFile.Write(_L8("Failed..\n"));
	    CloseFile();
   		return KErrGeneral;
   		}
       	
	aInputParam.servicechoice = 1;
	aInputParam.source = aCordinate1;
	aInputParam.destination = aCordinate2;

	aRet = CoreObj->MathOperation(aInputParam);
	
	if( KErrNone == aRet )
		{
		OpenFile();
    	TBuf8<50> buf ;
 		TRealFormat format; 
 		LogFile.Write(_L8("\n<GetBearing6 test> \n"));
 		buf.Num(aInputParam.result, format) ;
 		LogFile.Write(_L8("Bearing = "));
 		LogFile.Write(buf) ;
 		LogFile.Write(_L8("\n")) ;
 		CloseFile();
      	returnCode = KErrNone;  
		}
   	else
   		{
	   	OpenFile();
	   	LogFile.Write(_L8("\n<GetBearing6 test> \n"));
	   	LogFile.Write(_L8("Failed..\n"));
        CloseFile();
	    returnCode = KErrGeneral;
	 	}
 	  
   delete CoreObj;
   __UHEAP_MARKEND;
   return returnCode;	
   }


// -----------------------------------------------------------------------------
// CSAPILocTest::GetBearing7
// -----------------------------------------------------------------------------
//
TInt CSAPILocTest::GetBearing7( CStifItemParser& /*aItem*/ )
    {
    TInt aRet;
  	inpparam aInputParam;
    returnCode = KErrNone;
    
    TCoordinate  aCordinate1(35,360),aCordinate2(-80,-200);

	// Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "GetBearing7" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
    
    __UHEAP_MARK;
    
    CLocationService *CoreObj = CLocationService :: NewL();
    
    if( NULL == CoreObj)
    	{
    	OpenFile();
	    LogFile.Write(_L8("\n<GetBearing7 Test>\n"));
	    LogFile.Write(_L8("Failed..\n"));
	    CloseFile();
   		return KErrGeneral;
   		}
       	
	aInputParam.servicechoice = 1;
	aInputParam.source = aCordinate1;
	aInputParam.destination = aCordinate2;

	aRet = CoreObj->MathOperation(aInputParam);
	
	if( KErrNone == aRet )
		{
		OpenFile();
    	TBuf8<50> buf ;
 		TRealFormat format; 
 		LogFile.Write(_L8("\n<GetBearing7 test> \n"));
 		buf.Num(aInputParam.result, format) ;
 		LogFile.Write(_L8("Bearing = "));
 		LogFile.Write(buf) ;
 		LogFile.Write(_L8("\n")) ;
 		CloseFile();
      	returnCode = KErrNone;  
		}
   	else
   		{
	   	OpenFile();
	   	LogFile.Write(_L8("\n<GetBearing7 test> \n"));
	   	LogFile.Write(_L8("Failed..\n"));
        CloseFile();
	    returnCode = KErrGeneral;
	 	}
	 	
   delete CoreObj;
   __UHEAP_MARKEND;
   return returnCode;	
   }


// -----------------------------------------------------------------------------
// CSAPILocTest::GetBearing8
// -----------------------------------------------------------------------------
//
TInt CSAPILocTest::GetBearing8( CStifItemParser& /*aItem*/ )
    {
    TInt aRet;
  	inpparam aInputParam;
    returnCode = KErrNone;
    
    TCoordinate  aCordinate1(-30,160),aCordinate2(120,240);

	// Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "GetBearing8" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
    
    __UHEAP_MARK;
    
    CLocationService *CoreObj = CLocationService :: NewL();
    
    if( NULL == CoreObj)
    	{
    	OpenFile();
	    LogFile.Write(_L8("\n<GetBearing8 Test>\n"));
	    LogFile.Write(_L8("Failed..\n"));
	    CloseFile();
   		return KErrGeneral;
   		}
       	
	aInputParam.servicechoice = 1;
	aInputParam.source = aCordinate1;
	aInputParam.destination = aCordinate2;

	aRet = CoreObj->MathOperation(aInputParam);
	
   	if( KErrNone == aRet )
		{
		OpenFile();
    	TBuf8<50> buf ;
 		TRealFormat format; 
 		LogFile.Write(_L8("\n<GetBearing8 test> \n"));
 		buf.Num(aInputParam.result, format) ;
 		LogFile.Write(_L8("Bearing = "));
 		LogFile.Write(buf) ;
 		LogFile.Write(_L8("\n")) ;
 		CloseFile();
      	returnCode = KErrNone;  
		}
   	else
   		{
	   	OpenFile();
	   	LogFile.Write(_L8("\n<GetBearing8 test> \n"));
	   	LogFile.Write(_L8("Failed..\n"));
        CloseFile();
	    returnCode = KErrGeneral;
	 	}
	 	
   delete CoreObj;
   __UHEAP_MARKEND;
   return returnCode;	
   }
   

// -----------------------------------------------------------------------------
// CSAPILocTest::GetBearing9
// -----------------------------------------------------------------------------
//
TInt CSAPILocTest::GetBearing9( CStifItemParser& /*aItem*/ )
    {
    TInt aRet;
  	inpparam aInputParam;
    returnCode = KErrNone;
    
    TCoordinate  aCordinate1(105,190),aCordinate2(-105,-210);

	// Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "GetBearing9" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
    
    __UHEAP_MARK;
    
    CLocationService *CoreObj = CLocationService :: NewL();
    
    if( NULL == CoreObj)
    	{
    	OpenFile();
	    LogFile.Write(_L8("\n<GetBearing9 Test>\n"));
	    LogFile.Write(_L8("Failed..\n"));
	    CloseFile();
   		return KErrGeneral;
   		}
       	
	aInputParam.servicechoice = 1;
	aInputParam.source = aCordinate1;
	aInputParam.destination = aCordinate2;

	aRet = CoreObj->MathOperation(aInputParam);
    	
    if( KErrNone == aRet )
		{
		OpenFile();
    	TBuf8<50> buf ;
 		TRealFormat format; 
 		LogFile.Write(_L8("\n<GetBearing9 test> \n"));
 		buf.Num(aInputParam.result, format) ;
 		LogFile.Write(_L8("Bearing = "));
 		LogFile.Write(buf) ;
 		LogFile.Write(_L8("\n")) ;
 		CloseFile();
      	returnCode = KErrNone;  
		}
   	else
   		{
	   	OpenFile();
	   	LogFile.Write(_L8("\n<GetBearing9 test> \n"));
	   	LogFile.Write(_L8("Failed..\n"));
        CloseFile();
	    returnCode = KErrGeneral;
	 	}
	 	  
   delete CoreObj;
   __UHEAP_MARKEND;
   return returnCode;	
   }


// -----------------------------------------------------------------------------
// CSAPILocTest::GetBearing10
// -----------------------------------------------------------------------------
//
TInt CSAPILocTest::GetBearing10( CStifItemParser& /*aItem*/ )
    {
    TInt aRet;
  	inpparam aInputParam;
    returnCode = KErrNone;
    
    TCoordinate  aCordinate1(75,190),aCordinate2(-20,-220);

	// Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "GetBearing10" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
    
    __UHEAP_MARK;
    
    CLocationService *CoreObj = CLocationService :: NewL();
    
    if( NULL == CoreObj)
    	{
    	OpenFile();
	    LogFile.Write(_L8("\n<GetBearing10 Test>\n"));
	    LogFile.Write(_L8("Failed..\n"));
	    CloseFile();
   		return KErrGeneral;
   		}
       	
	aInputParam.servicechoice = 1;
	aInputParam.source = aCordinate1;
	aInputParam.destination = aCordinate2;

	aRet = CoreObj->MathOperation(aInputParam);
    	
	if( KErrNone == aRet )
		{
		OpenFile();
    	TBuf8<50> buf ;
 		TRealFormat format; 
 		LogFile.Write(_L8("\n<GetBearing10 test> \n"));
 		buf.Num(aInputParam.result, format) ;
 		LogFile.Write(_L8("Bearing = "));
 		LogFile.Write(buf) ;
 		LogFile.Write(_L8("\n")) ;
 		CloseFile();
      	returnCode = KErrNone;  
		}
   	else
   		{
	   	OpenFile();
	   	LogFile.Write(_L8("\n<GetBearing10 test> \n"));
	   	LogFile.Write(_L8("Failed..\n"));
        CloseFile();
	    returnCode = KErrGeneral;
	 	}
	 	
   delete CoreObj;
   __UHEAP_MARKEND;
   return returnCode;	
   }


// -----------------------------------------------------------------------------
// CSAPILocTest::GetBearing11
// -----------------------------------------------------------------------------
//
TInt CSAPILocTest::GetBearing11( CStifItemParser& /*aItem*/ )
    {
    TInt aRet;
  	inpparam aInputParam;
    returnCode = KErrNone;
    TRealX nan;
    nan.SetNaN();
    TCoordinate  aCordinate1(nan,190),aCordinate2(-20,-220);

	// Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "GetBearing11" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
    
    __UHEAP_MARK;
    
    CLocationService *CoreObj = CLocationService :: NewL();
    
    if( NULL == CoreObj)
    	{
    	OpenFile();
	    LogFile.Write(_L8("\n<GetBearing11 Test>\n"));
	    LogFile.Write(_L8("Failed..\n"));
	    CloseFile();
   		return KErrGeneral;
   		}
       	
	aInputParam.servicechoice = 1;
	aInputParam.source = aCordinate1;
	aInputParam.destination = aCordinate2;

	aRet = CoreObj->MathOperation(aInputParam);
	
	if( KErrArgument == aRet )
		{
		OpenFile();
    	LogFile.Write(_L8("\n<GetBearing11 test> \n"));
 		LogFile.Write(_L8("Passed..\n")) ;
 		CloseFile();
      	returnCode = KErrNone;  
		}
   	else
   		{
	   	OpenFile();
	   	LogFile.Write(_L8("\n<GetBearing11 test> \n"));
	   	LogFile.Write(_L8("Failed..\n"));
        CloseFile();
	    returnCode = KErrGeneral;
	 	}
   delete CoreObj;
   __UHEAP_MARKEND;
   return returnCode;	
   }


// -----------------------------------------------------------------------------
// CSAPILocTest::GetBearing12
// -----------------------------------------------------------------------------
//
TInt CSAPILocTest::GetBearing12( CStifItemParser& /*aItem*/ )
    {
    TInt aRet;
  	inpparam aInputParam;
    returnCode = KErrNone;
    TRealX nan;
    nan.SetNaN();
    TCoordinate  aCordinate1(40,nan),aCordinate2(-20,-220);

	// Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "GetBearing12" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
    
    __UHEAP_MARK;
    
    CLocationService *CoreObj = CLocationService :: NewL();
    
    if( NULL == CoreObj)
    	{
    	OpenFile();
	    LogFile.Write(_L8("\n<GetBearing12 Test>\n"));
	    LogFile.Write(_L8("Failed..\n"));
	    CloseFile();
   		return KErrGeneral;
   		}
       	
	aInputParam.servicechoice = 1;
	aInputParam.source = aCordinate1;
	aInputParam.destination = aCordinate2;

	aRet = CoreObj->MathOperation(aInputParam);
	
    if( KErrArgument == aRet )
    	{
		OpenFile();
    	LogFile.Write(_L8("\n<GetBearing12 test> \n"));
 		LogFile.Write(_L8("Passed..\n")) ;
 		CloseFile();
      	returnCode = KErrNone;  
		}
   	else
   		{
	   	OpenFile();
	   	LogFile.Write(_L8("\n<GetBearing12 test> \n"));
	   	LogFile.Write(_L8("Failed..\n"));
        CloseFile();
	    returnCode = KErrGeneral;
	 	}
   delete CoreObj;
   __UHEAP_MARKEND;
   return returnCode;	
   }



// -----------------------------------------------------------------------------
// CSAPILocTest::GetBearing13
// -----------------------------------------------------------------------------
//
TInt CSAPILocTest::GetBearing13( CStifItemParser& /*aItem*/ )
    {
    TInt aRet;
  	inpparam aInputParam;
    returnCode = KErrNone;
    TRealX nan;
    nan.SetNaN();
    TCoordinate  aCordinate1(40,140),aCordinate2(nan,-220);

	// Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "GetBearing13" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
    
    __UHEAP_MARK;
    
    CLocationService *CoreObj = CLocationService :: NewL();
    
    if( NULL == CoreObj)
    	{
    	OpenFile();
	    LogFile.Write(_L8("\n<GetBearing13 Test>\n"));
	    LogFile.Write(_L8("Failed..\n"));
	    CloseFile();
   		return KErrGeneral;
   		}
       	
	aInputParam.servicechoice = 1;
	aInputParam.source = aCordinate1;
	aInputParam.destination = aCordinate2;

	aRet = CoreObj->MathOperation(aInputParam);
	
	if( KErrArgument == aRet )
		{
		OpenFile();
    	LogFile.Write(_L8("\n<GetBearing13 test> \n"));
 		LogFile.Write(_L8("Passed..\n")) ;
 		CloseFile();
      	returnCode = KErrNone;  
		}
   	else
   		{
	   	OpenFile();
	   	LogFile.Write(_L8("\n<GetBearing13 test> \n"));
	   	LogFile.Write(_L8("Failed..\n"));
        CloseFile();
	    returnCode = KErrGeneral;
	 	}
	 	  
   delete CoreObj;
   __UHEAP_MARKEND;
   return returnCode;	
   }



// -----------------------------------------------------------------------------
// CSAPILocTest::GetBearing14
// -----------------------------------------------------------------------------
//
TInt CSAPILocTest::GetBearing14( CStifItemParser& /*aItem*/ )
    {
    TInt aRet;
  	inpparam aInputParam;
    returnCode = KErrNone;
    TRealX nan;
    nan.SetNaN();
    TCoordinate  aCordinate1(40,140),aCordinate2(60,nan);

	// Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "GetBearing14" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
    
    __UHEAP_MARK;
    
    CLocationService *CoreObj = CLocationService :: NewL();
    
    if( NULL == CoreObj)
    	{
    	OpenFile();
	    LogFile.Write(_L8("\n<GetBearing14 Test>\n"));
	    LogFile.Write(_L8("Failed..\n"));
	    CloseFile();
   		return KErrGeneral;
   		}
       	
	aInputParam.servicechoice = 1;
	aInputParam.source = aCordinate1;
	aInputParam.destination = aCordinate2;

	aRet = CoreObj->MathOperation(aInputParam);
	
	if( KErrArgument == aRet )
		{
		OpenFile();
    	LogFile.Write(_L8("\n<GetBearing14 test> \n"));
 		LogFile.Write(_L8("Passed..\n")) ;
 		CloseFile();
      	returnCode = KErrNone;  
		}
   	else
   		{
	   	OpenFile();
	   	LogFile.Write(_L8("\n<GetBearing14 test> \n"));
	   	LogFile.Write(_L8("Failed..\n"));
        CloseFile();
	    returnCode = KErrGeneral;
	 	}
   delete CoreObj;
   __UHEAP_MARKEND;
   return returnCode;	
   }


// -----------------------------------------------------------------------------
// CSAPILocTest::Move1
// -----------------------------------------------------------------------------
//
TInt CSAPILocTest::Move1( CStifItemParser& /*aItem*/ )
    {
    TInt aRet;
  	inpparam aInputParam;
    returnCode = KErrNone;
    TRealX nan;
    nan.SetNaN();
    TCoordinate  aCordinate1(nan,140);
	TReal32 aDist=1000,aBearing=100;
	// Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "Move1" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
    
    __UHEAP_MARK;
    
    CLocationService *CoreObj = CLocationService :: NewL();
    
    if( NULL == CoreObj)
    	{
    	OpenFile();
	    LogFile.Write(_L8("\n<Move1 Test>\n"));
	    LogFile.Write(_L8("Failed..\n"));
	    CloseFile();
   		return KErrGeneral;
   		}
       	
	aInputParam.servicechoice = 2;
	aInputParam.source = aCordinate1;
	aInputParam.bearing = aBearing;
	aInputParam.distance = aDist;
	
	aRet = CoreObj->MathOperation(aInputParam);
	
	if( KErrArgument == aRet )
		{
		OpenFile();
    	LogFile.Write(_L8("\n<Move1 test> \n"));
 		LogFile.Write(_L8("Passed..\n")) ;
 		CloseFile();
      	returnCode = KErrNone;  
		}
   	else
   		{
	   	OpenFile();
	   	LogFile.Write(_L8("\n<Move1 test> \n"));
	   	LogFile.Write(_L8("Failed..\n"));
        CloseFile();
	    returnCode = KErrGeneral;
	 	}
   delete CoreObj;
   __UHEAP_MARKEND;
   return returnCode;	
   }



// -----------------------------------------------------------------------------
// CSAPILocTest::Move2
// -----------------------------------------------------------------------------
//
TInt CSAPILocTest::Move2( CStifItemParser& /*aItem*/ )
    {
    TInt aRet;
  	inpparam aInputParam;
    returnCode = KErrNone;
    TRealX nan;
    nan.SetNaN();
    TCoordinate  aCordinate1(40,nan);
	TReal32 aDist=1000,aBearing=100;
	// Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "Move2" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
    
    __UHEAP_MARK;
    
    CLocationService *CoreObj = CLocationService :: NewL();
    
    if( NULL == CoreObj)
    	{
    	OpenFile();
	    LogFile.Write(_L8("\n<Move2 Test>\n"));
	    LogFile.Write(_L8("Failed..\n"));
	    CloseFile();
   		return KErrGeneral;
   		}
       	
	aInputParam.servicechoice = 2;
	aInputParam.source = aCordinate1;
	aInputParam.bearing = aBearing;
	aInputParam.distance = aDist;
	
	aRet = CoreObj->MathOperation(aInputParam);
	
	if( KErrArgument == aRet )
		{
		OpenFile();
    	LogFile.Write(_L8("\n<Move2 test> \n"));
 		LogFile.Write(_L8("Passed..\n")) ;
 		CloseFile();
      	returnCode = KErrNone;  
		}
   	else
   		{
	   	OpenFile();
	   	LogFile.Write(_L8("\n<Move2 test> \n"));
	   	LogFile.Write(_L8("Failed..\n"));
        CloseFile();
	    returnCode = KErrGeneral;
	 	}
   delete CoreObj;
   __UHEAP_MARKEND;
   return returnCode;	
   }



// -----------------------------------------------------------------------------
// CSAPILocTest::Move3
// -----------------------------------------------------------------------------
//
TInt CSAPILocTest::Move3( CStifItemParser& /*aItem*/ )
    {
    TInt aRet;
  	inpparam aInputParam;
    returnCode = KErrNone;
    TRealX nan;
    nan.SetNaN();
    TCoordinate  aCordinate1(90,0);
	TReal32 aDist=1000,aBearing=100;
	// Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "Move3" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
    
    __UHEAP_MARK;
    
    CLocationService *CoreObj = CLocationService :: NewL();
    
    if( NULL == CoreObj)
    	{
    	OpenFile();
	    LogFile.Write(_L8("\n<Move3 Test>\n"));
	    LogFile.Write(_L8("Failed..\n"));
	    CloseFile();
   		return KErrGeneral;
   		}
       	
	aInputParam.servicechoice = 2;
	aInputParam.source = aCordinate1;
	aInputParam.bearing = aBearing;
	aInputParam.distance = aDist;
	
	aRet = CoreObj->MathOperation(aInputParam);
	
	if( KErrPositionIncalculable == aRet )
		{
		OpenFile();
    	LogFile.Write(_L8("\n<Move3 test> \n"));
 		LogFile.Write(_L8("Passed..\n")) ;
 		CloseFile();
      	returnCode = KErrNone;  
		}
   	else
   		{
	   	OpenFile();
	   	LogFile.Write(_L8("\n<Move3 test> \n"));
	   	LogFile.Write(_L8("Failed..\n"));
        CloseFile();
	    returnCode = KErrGeneral;
	 	}
	 	  
   delete CoreObj;
   __UHEAP_MARKEND;
   return returnCode;	
   }




// -----------------------------------------------------------------------------
// CSAPILocTest::Move4
// -----------------------------------------------------------------------------
//
TInt CSAPILocTest::Move4( CStifItemParser& /*aItem*/ )
    {
    TInt aRet;
  	inpparam aInputParam;
    returnCode = KErrNone;
    TRealX nan;
    nan.SetNaN();
    TCoordinate  aCordinate1(-90,0);
	TReal32 aDist=1000,aBearing=100;
	// Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "Move4" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
    
    __UHEAP_MARK;
    
    CLocationService *CoreObj = CLocationService :: NewL();
    
    if( NULL == CoreObj)
    	{
    	OpenFile();
	    LogFile.Write(_L8("\n<Move4 Test>\n"));
	    LogFile.Write(_L8("Failed..\n"));
	    CloseFile();
   		return KErrGeneral;
   		}
       	
	aInputParam.servicechoice = 2;
	aInputParam.source = aCordinate1;
	aInputParam.bearing = aBearing;
	aInputParam.distance = aDist;
	
	aRet = CoreObj->MathOperation(aInputParam);
	
	if( KErrPositionIncalculable == aRet )
		{
		OpenFile();
    	LogFile.Write(_L8("\n<Move4 test> \n"));
 		LogFile.Write(_L8("Passed..\n")) ;
 		CloseFile();
      	returnCode = KErrNone;  
		}
   	else
   		{
	   	OpenFile();
	   	LogFile.Write(_L8("\n<Move4 test> \n"));
	   	LogFile.Write(_L8("Failed..\n"));
        CloseFile();
	    returnCode = KErrGeneral;
	 	}
	 	  
   delete CoreObj;
   __UHEAP_MARKEND;
   return returnCode;	
   }




// -----------------------------------------------------------------------------
// CSAPILocTest::Move5
// -----------------------------------------------------------------------------
//
TInt CSAPILocTest::Move5( CStifItemParser& /*aItem*/ )
    {
    TInt aRet;
  	inpparam aInputParam;
    returnCode = KErrNone;
    TRealX nan;
    nan.SetNaN();
    TCoordinate  aCordinate1(0,0);
	TReal32 aDist=1000,aBearing=100;
	// Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "Move5" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
    
    __UHEAP_MARK;
    
    CLocationService *CoreObj = CLocationService :: NewL();
    
    if( NULL == CoreObj)
    	{
    	OpenFile();
	    LogFile.Write(_L8("\n<Move5 Test>\n"));
	    LogFile.Write(_L8("Failed..\n"));
	    CloseFile();
   		return KErrGeneral;
   		}
       	
	aInputParam.servicechoice = 2;
	aInputParam.source = aCordinate1;
	aInputParam.bearing = aBearing;
	aInputParam.distance = aDist;
	
	aRet = CoreObj->MathOperation(aInputParam);
	
	if( KErrNone == aRet )
		{
		OpenFile();
    	LogFile.Write(_L8("\n<Move5 test> \n"));
 		LogFile.Write(_L8("Passed..\n")) ;
 		CloseFile();
      	returnCode = KErrNone;  
		}
   	else
   		{
	   	OpenFile();
	   	LogFile.Write(_L8("\n<Move5 test> \n"));
	   	LogFile.Write(_L8("Failed..\n"));
        CloseFile();
	    returnCode = KErrGeneral;
	 	}
	 	  
   delete CoreObj;
   __UHEAP_MARKEND;
   return returnCode;	
   }


// -----------------------------------------------------------------------------
// CSAPILocTest::Move6
// -----------------------------------------------------------------------------
//
TInt CSAPILocTest::Move6( CStifItemParser& /*aItem*/ )
    {
    TInt aRet;
  	inpparam aInputParam;
    returnCode = KErrNone;
    TRealX nan;
    nan.SetNaN();
    TCoordinate  aCordinate1(20,120);
	TReal32 aDist=1000,aBearing=100;
	// Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "Move6" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
    
    __UHEAP_MARK;
    
    CLocationService *CoreObj = CLocationService :: NewL();
    
    if( NULL == CoreObj)
    	{
    	OpenFile();
	    LogFile.Write(_L8("\n<Move6 Test>\n"));
	    LogFile.Write(_L8("Failed..\n"));
	    CloseFile();
   		return KErrGeneral;
   		}
       	
	aInputParam.servicechoice = 2;
	aInputParam.source = aCordinate1;
	aInputParam.bearing = aBearing;
	aInputParam.distance = aDist;
	
	aRet = CoreObj->MathOperation(aInputParam);
	
	if( KErrNone == aRet )
		{
		OpenFile();
		TBuf8<50> buf ;
 		TRealFormat format; 
 	   	LogFile.Write(_L8("\n<Move6 test> \n"));
 		TReal64 aLatitude  = aCordinate1.Latitude();
 		buf.Num(aLatitude, format) ;
 		LogFile.Write(_L8("Latitude = "));
 		LogFile.Write(buf) ;
 		TReal64 aLongitude  = aCordinate1.Longitude();
 		buf.Num(aLongitude, format) ;
 		LogFile.Write(_L8("Longitude = "));
 		LogFile.Write(buf) ;
 		LogFile.Write(_L8("Passed..\n")) ;
 		CloseFile();
      	returnCode = KErrNone;  
		}
   	else
   		{
	   	OpenFile();
	   	LogFile.Write(_L8("\n<Move6 test> \n"));
	   	LogFile.Write(_L8("Failed..\n"));
        CloseFile();
	    returnCode = KErrGeneral;
	 	}
	 	  
   delete CoreObj;
   __UHEAP_MARKEND;
   return returnCode;	
   }

// -----------------------------------------------------------------------------
// CSAPILocTest::Move7
// -----------------------------------------------------------------------------
//
TInt CSAPILocTest::Move7( CStifItemParser& /*aItem*/ )
    {
    TInt aRet;
  	inpparam aInputParam;
    returnCode = KErrNone;
    TRealX nan;
    nan.SetNaN();
    TCoordinate  aCordinate1(-30,-70);
	TReal32 aDist=1000,aBearing=100;
	// Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "Move7" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
    
    __UHEAP_MARK;
    
    CLocationService *CoreObj = CLocationService :: NewL();
    
    if( NULL == CoreObj)
    	{
    	OpenFile();
	    LogFile.Write(_L8("\n<Move7 Test>\n"));
	    LogFile.Write(_L8("Failed..\n"));
	    CloseFile();
   		return KErrGeneral;
   		}
       	
	aInputParam.servicechoice = 2;
	aInputParam.source = aCordinate1;
	aInputParam.bearing = aBearing;
	aInputParam.distance = aDist;
	
	aRet = CoreObj->MathOperation(aInputParam);
	
	if( KErrNone == aRet )
		{
		OpenFile();
		TBuf8<50> buf ;
 		TRealFormat format; 
 	   	LogFile.Write(_L8("\n<Move7 test> \n"));
 		TReal64 aLatitude  = aCordinate1.Latitude();
 		buf.Num(aLatitude, format) ;
 		LogFile.Write(_L8("Latitude = "));
 		LogFile.Write(buf) ;
 		TReal64 aLongitude  = aCordinate1.Longitude();
 		buf.Num(aLongitude, format) ;
 		LogFile.Write(_L8("Longitude = "));
 		LogFile.Write(buf) ;
 		LogFile.Write(_L8("Passed..\n")) ;
 		CloseFile();
      	returnCode = KErrNone;  
		}
   	else
   		{
	   	OpenFile();
	   	LogFile.Write(_L8("\n<Move7 test> \n"));
	   	LogFile.Write(_L8("Failed..\n"));
        CloseFile();
	    returnCode = KErrGeneral;
	 	}
	 	  
    delete CoreObj;
   __UHEAP_MARKEND;
   return returnCode;	
   }


// -----------------------------------------------------------------------------
// CSAPILocTest::Move8
// -----------------------------------------------------------------------------
//
TInt CSAPILocTest::Move8( CStifItemParser& /*aItem*/ )
    {
    TInt aRet;
  	inpparam aInputParam;
    returnCode = KErrNone;
    TRealX nan;
    nan.SetNaN();
    TCoordinate  aCordinate1(20,120);
	TReal32 aDist=0,aBearing=0;
	// Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "Move8" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
    
    __UHEAP_MARK;
    
    CLocationService *CoreObj = CLocationService :: NewL();
    
    if( NULL == CoreObj)
    	{
    	OpenFile();
	    LogFile.Write(_L8("\n<Move8 Test>\n"));
	    LogFile.Write(_L8("Failed..\n"));
	    CloseFile();
   		return KErrGeneral;
   		}
       	
	aInputParam.servicechoice = 2;
	aInputParam.source = aCordinate1;
	aInputParam.bearing = aBearing;
	aInputParam.distance = aDist;
	
	aRet = CoreObj->MathOperation(aInputParam);
	
	if( KErrNone == aRet )
		{
		OpenFile();
		TBuf8<50> buf ;
 		TRealFormat format; 
 	   	LogFile.Write(_L8("\n<Move8 test> \n"));
 		TReal64 aLatitude  = aCordinate1.Latitude();
 		buf.Num(aLatitude, format) ;
 		LogFile.Write(_L8("Latitude = "));
 		LogFile.Write(buf) ;
 		TReal64 aLongitude  = aCordinate1.Longitude();
 		buf.Num(aLongitude, format) ;
 		LogFile.Write(_L8("Longitude = "));
 		LogFile.Write(buf) ;
 		CloseFile();
      	if( aLatitude != 20 || aLongitude != 120)
      		returnCode = KErrGeneral;
      	else
      		returnCode = KErrNone;  
		}
   	else
   		{
	   	OpenFile();
	   	LogFile.Write(_L8("\n<Move8 test> \n"));
	   	LogFile.Write(_L8("Failed..\n"));
        CloseFile();
	    returnCode = KErrGeneral;
	 	}
	 	  
   delete CoreObj;
   __UHEAP_MARKEND;
   return returnCode;	
   }

// -----------------------------------------------------------------------------
// CSAPILocTest::Modinfo1
// -----------------------------------------------------------------------------
//
//TInt CSAPILocTest::Modinfo1( CStifItemParser& /*aItem*/ )
  /*  {
    TInt aRet;
    TPositionModuleInfo currPos;
  	inpparam aInputParam;
    returnCode = KErrNone;
    TReal32 aDist=0,aBearing=0;
	// Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "Modinfo1" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
    
    __UHEAP_MARK;
    
    CLocationService *CoreObj = CLocationService :: NewL();
    
    if( NULL == CoreObj)
    	{
    	OpenFile();
	    LogFile.Write(_L8("\n<Move8 Test>\n"));
	    LogFile.Write(_L8("Failed..\n"));
	    CloseFile();
   		return KErrGeneral;
   		}
       	
	aRet = CoreObj->GetModuleInfo(currPos);
	TPositionModuleInfo :: TCapabilities  currCapability  = currPos.Capabilities() ;
	
	if ( iLocinfoCategory == EGenericInfo )
	    {
	    if(currCapability & TPositionModuleInfo :: ECapabilitySpeed) //Populate output param with speed info
        {
        TReal32 speedinfo = 0 ;

        if(!aGenericInfo->GetValue(EPositionFieldHorizontalSpeed , speedinfo) ) //Extract speed 
            {
            iOutParmList->AppendL(TAiwGenericParam(KPositionFieldHorizontalSpeed , TAiwVariant((TReal)speedinfo))) ;
            }

        if(!aGenericInfo->GetValue(EPositionFieldHorizontalSpeedError , speedinfo))
            {
            iOutParmList->AppendL(TAiwGenericParam(KPositionFieldHorizontalSpeedError , TAiwVariant((TReal)speedinfo))) ;	
            }



        }   //End of EcapabilitySpeed 


	    if(currCapability & TPositionModuleInfo :: ECapabilitySatellite) //Extract satellitinfo if any and append it
	        {																//as part of out parm list
	        TInt8 satinfo  = 0;

	        if(!aGenericInfo->GetValue(EPositionFieldSatelliteNumInView , satinfo))
	            {
	            iOutParmList->AppendL(TAiwGenericParam(KPositionFieldSatelliteNumInView ,TAiwVariant((TInt32)satinfo) )) ;	
	            }


	        }

	    if(currCapability & TPositionModuleInfo :: ECapabilityDirection) //Extract direction info if any and append it 
	        {                                                               // as part of out parm list
	        TReal32 direcinfo = 0;

	        if(!aGenericInfo->GetValue(EPositionFieldTrueCourse , direcinfo) )
	            {
	            iOutParmList->AppendL(TAiwGenericParam(KPositionFieldTrueCourse , TAiwVariant((TInt32)direcinfo))) ;	
	            }


	        if(!aGenericInfo->GetValue(EPositionFieldTrueCourseError , direcinfo) )
	            {
	            iOutParmList->AppendL(TAiwGenericParam(KPositionFieldTrueCourseError , TAiwVariant((TInt32)direcinfo))) ;
	            }


	        if(!aGenericInfo->GetValue(EPositionFieldMagneticCourseError , direcinfo) )
	            {
	            iOutParmList->AppendL(TAiwGenericParam(KPositionFieldMagneticCourseError , TAiwVariant((TInt32)direcinfo))) ;
	            }

	        if(!aGenericInfo->GetValue(EPositionFieldMagneticCourse , direcinfo) )
	            {
	            iOutParmList->AppendL(TAiwGenericParam(KPositionFieldMagneticCourse , TAiwVariant((TInt32)direcinfo))) ;	
	            }

	        }


	    if(currCapability & TPositionModuleInfo :: ECapabilityCompass) //Extract compass info if any and append it 
	        {                                                               // as part of out parm list
	        TReal32 compassinfo ;

	        if(!aGenericInfo->GetValue(EPositionFieldHeading , compassinfo) )
	            {
	            iOutParmList->AppendL(TAiwGenericParam(KPositionFieldHeading , TAiwVariant((TInt32)compassinfo))) ;
	            }


	        if(!aGenericInfo->GetValue(EPositionFieldHeadingError , compassinfo) )
	            {
	            iOutParmList->AppendL(TAiwGenericParam(KPositionFieldHeadingError , TAiwVariant((TInt32)compassinfo))) ;
	            }

	        if(!aGenericInfo->GetValue(EPositionFieldMagneticHeading , compassinfo) )
	            {
	            iOutParmList->AppendL(TAiwGenericParam(KPositionFieldMagneticHeading , TAiwVariant((TInt32)compassinfo))) ;
	            }



	        if(!aGenericInfo->GetValue(EPositionFieldMagneticHeadingError , compassinfo) )
	            {
	            iOutParmList->AppendL(TAiwGenericParam(KPositionFieldMagneticHeadingError , TAiwVariant((TInt32)compassinfo))) ;	
	            }



	        }

	    if( currCapability & TPositionModuleInfo :: ECapabilityNmea ) //Extract Nmea info if any and append it 	
	        {                                                             //as part of out param list  
	        TUint8 numSentences ;

	        if(!aGenericInfo->GetValue(EPositionFieldNMEASentences , numSentences) )
	            {
	            iOutParmList->AppendL(TAiwGenericParam (KPositionFieldNMEASentences ,TAiwVariant((TInt32)numSentences) )) ;	
	            }


	        TBuf8 <20> nmeaSentences ;

	        if(!aGenericInfo->GetValue(EPositionFieldNMEASentencesStart , nmeaSentences) )
	            {
	            iOutParmList->AppendL(TAiwGenericParam (KPositionFieldNMEASentencesStart , TAiwVariant(nmeaSentences))) ;	
	            }
	        }

	 	  
    aRequestorStack.Close();
	    delete identityInfo;
	    delete CoreObj;
   __UHEAP_MARKEND;
   return returnCode;	
   }*/


// -----------------------------------------------------------------------------
// CSAPILocTest::Modinfo1
// -----------------------------------------------------------------------------
//
class Modinfo1CallBack : public MLocationCallBack
	{
    TInt iCount ;
    TInt iRetStatus ;
    CLocationService *iCoreObj; 
    public :
    TInt HandleNotifyL(HPositionGenericInfo* aOutPos , TInt aError) ;
    Modinfo1CallBack(CLocationService *obj,TInt cnt=0,TInt retStatus=KErrGeneral) 
    	{
		iCoreObj = obj;
		iCount = cnt;
		iRetStatus = retStatus;    
    	}
	};
  
   
TInt Modinfo1CallBack :: HandleNotifyL(HPositionGenericInfo *currPos , TInt /*aError*/)
	{
	TInt aRetVal = KErrNone;
	TPositionModuleInfo modInfo;
	OpenFile();
	LogFile.Write(_L8("\n<Modinfo1 Test>\n "));
	CloseFile();
	TPosition outPos ;
  	currPos->GetPosition(outPos) ;
	aRetVal = ValidatePosition(outPos);
    
    if( KErrNone == aRetVal )
	    {
    	aRetVal = iCoreObj->GetModuleInfo(modInfo);
    	TPositionModuleInfo :: TCapabilities  currCapability  = modInfo.Capabilities() ;
	
	//	if ( iLocinfoCategory == EGenericInfo )
	 //   	{
	    	//if( (currCapability & TPositionModuleInfo :: ECapabilitySpeed) && returnCode == KErrNone) //Populate output param with speed info
        	if (currCapability & TPositionModuleInfo :: ECapabilitySpeed)	
        		{
        		TReal32 speedinfo = 0 ;

        		if(!currPos->GetValue(EPositionFieldHorizontalSpeed , speedinfo) ) //Extract speed 
            		{
            		TBuf8<50> buf ;
					TRealFormat format ;
					buf.Num(speedinfo , format) ;
					OpenFile();
					LogFile.Write(_L8("HorizontalSpeed = "));
					LogFile.Write(buf) ;
					LogFile.Write(_L8("\n")) ;
					CloseFile();
           			}

		        else if(!currPos->GetValue(EPositionFieldHorizontalSpeedError , speedinfo))
		            {
		            TBuf8<50> buf ;
					TRealFormat format ;
					buf.Num(speedinfo , format) ;
					OpenFile();
					LogFile.Write(_L8("HorizontalSpeedError = "));
					LogFile.Write(buf) ;
					LogFile.Write(_L8("\n")) ;
					CloseFile();
		            }
		      /*   else
		         {
		         	returnCode = KErrGeneral;
		         }
              */    
        	}   //End of EcapabilitySpeed 


	  //  if((currCapability & TPositionModuleInfo :: ECapabilitySatellite) && returnCode == KErrNone ) //Extract satellitinfo if any and append it
	     if(currCapability & TPositionModuleInfo :: ECapabilitySatellite)   
	        {																//as part of out parm list
	        TInt8 satinfo  = 0;

	        if(!currPos->GetValue(EPositionFieldSatelliteNumInView , satinfo))
	            {
	            TBuf8<50> buf ;
				TRealFormat format ;
				buf.Num(satinfo , format) ;
				OpenFile();
				LogFile.Write(_L8("SatelliteNumInView = "));
				LogFile.Write(buf) ;
				LogFile.Write(_L8("\n")) ;
				CloseFile();
	            }
	        /* else
	         	{
	         	returnCode = KErrGeneral;
	         	}
	        */
	        }

	    if( (currCapability & TPositionModuleInfo :: ECapabilityDirection) && returnCode == KErrNone) //Extract direction info if any and append it 
	        {                                                               // as part of out parm list
	        TReal32 direcinfo = 0;

	        if(!currPos->GetValue(EPositionFieldTrueCourse , direcinfo) )
	            {
	            TBuf8<50> buf ;
				TRealFormat format ;
				buf.Num(direcinfo , format) ;
				OpenFile();
				LogFile.Write(_L8("TrueCourse  = "));
				LogFile.Write(buf) ;
				LogFile.Write(_L8("\n")) ;
				CloseFile();
	            }

	        else if(!currPos->GetValue(EPositionFieldTrueCourseError , direcinfo) )
	            {
				TBuf8<50> buf ;
				TRealFormat format ;
				buf.Num(direcinfo , format) ;
				OpenFile();
				LogFile.Write(_L8("TrueCourseError = "));
				LogFile.Write(buf) ;
				LogFile.Write(_L8("\n")) ;
				CloseFile();	            
				}

	        else if(!currPos->GetValue(EPositionFieldMagneticCourseError , direcinfo) )
	            {
				TBuf8<50> buf ;
				TRealFormat format ;
				buf.Num(direcinfo , format) ;
				OpenFile();
				LogFile.Write(_L8("MagneticCourseError = "));
				LogFile.Write(buf) ;
				LogFile.Write(_L8("\n")) ;
				CloseFile();	           
				}

	        else if(!currPos->GetValue(EPositionFieldMagneticCourse , direcinfo) )
	            {
				TBuf8<50> buf ;
				TRealFormat format ;
				buf.Num(direcinfo , format) ;
				OpenFile();
				LogFile.Write(_L8("MagneticCourse = "));
				LogFile.Write(buf) ;
				LogFile.Write(_L8("\n")) ;
				CloseFile();	 	            
				}
			/*else
				{
				returnCode = KErrGeneral;
				}
             */
	        }


	    //if((currCapability & TPositionModuleInfo :: ECapabilityCompass) && returnCode == KErrNone) //Extract compass info if any and append it 
	      if(currCapability & TPositionModuleInfo :: ECapabilityCompass)
	        {                                                               // as part of out parm list
	        TReal32 compassinfo ;

	        if(!currPos->GetValue(EPositionFieldHeading , compassinfo) )
	            {
				TBuf8<50> buf ;
				TRealFormat format ;
				buf.Num(compassinfo , format) ;
				OpenFile();
				LogFile.Write(_L8("FieldHeading = "));
				LogFile.Write(buf) ;
				LogFile.Write(_L8("\n")) ;
				CloseFile();	           
				}


	        else if(!currPos->GetValue(EPositionFieldHeadingError , compassinfo) )
	            {
				TBuf8<50> buf ;
				TRealFormat format ;
				buf.Num(compassinfo , format) ;
				OpenFile();
				LogFile.Write(_L8("FieldHeadingError = "));
				LogFile.Write(buf) ;
				LogFile.Write(_L8("\n")) ;
				CloseFile();		           
				}

	        else if(!currPos->GetValue(EPositionFieldMagneticHeading , compassinfo) )
	            {
				TBuf8<50> buf ;
				TRealFormat format ;
				buf.Num(compassinfo , format) ;
				OpenFile();
				LogFile.Write(_L8("MagneticHeading = "));
				LogFile.Write(buf) ;
				LogFile.Write(_L8("\n")) ;
				CloseFile();		           
				}
	
	        else if(!currPos->GetValue(EPositionFieldMagneticHeadingError , compassinfo) )
	            {
				TBuf8<50> buf ;
				TRealFormat format ;
				buf.Num(compassinfo , format) ;
				OpenFile();
				LogFile.Write(_L8("MagneticHeadingError = "));
				LogFile.Write(buf) ;
				LogFile.Write(_L8("\n")) ;
				CloseFile();	            
				}

			/*else
				{
				returnCode = KErrGeneral; 
				}
            */  
	        }

	    //if( (currCapability & TPositionModuleInfo :: ECapabilityNmea) && returnCode == KErrNone )//Extract Nmea info if any and append it 	
	      if(currCapability & TPositionModuleInfo :: ECapabilityNmea)  
	      		{                                                             //as part of out param list  
	        	TUint8 numSentences ;
				TBuf8 <20> nmeaSentences ;
	        	if(!currPos->GetValue(EPositionFieldNMEASentences , numSentences) )
	            {
				TBuf8<50> buf ;
				TRealFormat format ;
				buf.Num(numSentences , format) ;
				OpenFile();
				LogFile.Write(_L8("NMEASentences = "));
				LogFile.Write(buf) ;
				LogFile.Write(_L8("\n")) ;
				CloseFile();	            
				}

	       else if(!currPos->GetValue(EPositionFieldNMEASentencesStart , nmeaSentences) )
	            {
				TRealFormat format ;
				OpenFile();
				LogFile.Write(_L8("NMEASentencesStart = "));
				LogFile.Write(nmeaSentences) ;
				LogFile.Write(_L8("\n")) ;
				CloseFile();	            
				}
		/*	else
				{
				returnCode = KErrGeneral;
				}
	     */ 
	        }

	    }
   else
	   	{
   		OpenFile();
   		LogFile.Write(_L8("Failed..\n"));
   		CloseFile();
   		returnCode = KErrGeneral;
	   	}
    
    CActiveScheduler *Current = CActiveScheduler :: Current() ;
	Current->Stop() ;
	return KErrNone ;
	}

TInt ModinfoFunctionL()
	{
    CLocationService *CoreObj = CLocationService ::NewL() ;
    
    if( NULL == CoreObj )
    	{
    	OpenFile();
	    LogFile.Write(_L8("\n<Modinfo1 Test>\n"));
	    LogFile.Write(_L8("Failed..\n"));
	    CloseFile();
   		return KErrGeneral;
   		}
    
    _LIT(Kidentity ,"Coreclass Testing" ) ;
    //not needed any more
	/*RRequestorStack aRequestorStack;
	const CRequestor* identityInfo = CRequestor::NewL(1 , 1 , Kidentity) ;
    aRequestorStack.Insert(identityInfo,0);
    CoreObj->SetRequestorIdentityL(aRequestorStack) ;*/
		
    Modinfo1CallBack MyUpdates(CoreObj)  ;
    CoreObj->GetLocationL(&MyUpdates) ;
    CActiveScheduler :: Start() ;
     /*aRequestorStack.Close();
	    delete identityInfo;*/
	    delete CoreObj;
    return 0;
	}

TInt CSAPILocTest::Modinfo1( CStifItemParser& /*aItem*/ )
	{
    TRequestStatus status = KRequestPending;
    TInt aRet = KErrNone;
    returnCode = KErrNone;
    // Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "Modinfo1" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
    
     __UHEAP_MARK;
    
    TRAPD(err , aRet = ModinfoFunctionL()) ;
    if( err || aRet )
    returnCode = KErrGeneral; 
    
    __UHEAP_MARKEND;
 
    return returnCode;  
    }
    
    