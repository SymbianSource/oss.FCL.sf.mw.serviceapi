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
#include "sapiloctotest.h"
#include <f32file.h>
#include <LbsPosition.h>


_LIT(LogFileName , "C:\\Notifications.txt") ;
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
    
void Csapiloctotest::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// Csapiloctotest::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt Csapiloctotest::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "GetPositionTO",    Csapiloctotest::GetPositionTO ),
   //     ENTRY( "GetPositionAsyncTO",    Csapiloctotest::GetPositionAsyncTO ),
  //      ENTRY( "TraceLPositionTO",    Csapiloctotest::TraceLPositionTO),

        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// Csapiloctotest::GetPositionTO
// -----------------------------------------------------------------------------
//
TInt Csapiloctotest::GetPositionTO( CStifItemParser& /*aItem*/ )
    {
	TInt aRet;
	TPositionInfo currpos;
	returnCode = KErrNone;
	
    // Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "GetLocationTO" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
    
    __UHEAP_MARK;
    
    CLocationService *CoreObj = CLocationService :: NewL();
    
    if( NULL == CoreObj )
    	{
    	OpenFile();
	    LogFile.Write(_L8("\n<GetPositionTO Test>\n"));
	    LogFile.Write(_L8("Failed..\n"));
	    CloseFile();
   		return KErrGeneral;
   		}
    
    _LIT(Kidentity ,"Coreclass Testing" ) ;
    //Not required anymore
	/*RRequestorStack aRequestorStack;
	const CRequestor* identityInfo = CRequestor::NewL(1 , 1 , Kidentity) ;
    aRequestorStack.Insert(identityInfo,0);
    CoreObj->SetRequestorIdentityL(aRequestorStack) ;*/
		
    aRet = CoreObj->GetLocationL(&currpos);
    
    if( KErrTimedOut == aRet )
    	{
    	OpenFile();
		LogFile.Write(_L8("\n<GetPositionTO Test>\n"));
		LogFile.Write(_L8("Passed..\n"));
		CloseFile();
	   	returnCode = KErrNone;	
    	}
    
    else
    	{
    	OpenFile();
		LogFile.Write(_L8("\n<GetPositionTO Test>\n"));
		LogFile.Write(_L8("Failed..\n"));
		CloseFile();
    	returnCode = KErrGeneral;
    	}
    
    /*delete identityInfo;
    aRequestorStack.Close();*/
    delete CoreObj;
    
    __UHEAP_MARKEND;
    
    return KErrNone;
    
    }


// -----------------------------------------------------------------------------
// Csapiloctotest::GetPositionAsyncTO
// -----------------------------------------------------------------------------
//
/*class LocUpdateCallBackTO : public MLocationCallBack
	{
	TInt iCount ;
	TInt iRetStatus ;
	public :
	TInt HandleNotifyL(HPositionGenericInfo *aOutPos , TInt aError) ;
	LocUpdateCallBackTO() :iCount(0) , iRetStatus(KErrGeneral)  //Default constructor 
		{;}
	};
  
  
TInt LocUpdateCallBackTO :: HandleNotifyL(HPositionGenericInfo *currPos , TInt aError)
	{
    
    if(KErrTimedOut == aError)
  		{
	    OpenFile();
		LogFile.Write(_L8("\n<GetPositionAsyncTO test>\n "));
		LogFile.Write(_L8("Passed..\n "));
		CloseFile();
		returnCode = KErrNone;
   		}
 
    else
	 	{
	 	OpenFile();
	 	LogFile.Write(_L8("\n<GetPositionAsyncTO test>\n "));
	 	LogFile.Write(_L8("Failed..\n "));
	 	CloseFile();
	  	returnCode = KErrGeneral;
	 	}
 
  CActiveScheduler *Current = CActiveScheduler :: Current() ;
  
  Current->Stop() ;
  
  return KErrNone ;
  }

TInt GetLocFunctionTOL()
	{
    CLocationService *CoreObj = CLocationService ::NewL() ;
    
    if( NULL == CoreObj )
    	{
    	OpenFile();
	    LogFile.Write(_L8("\n<GetPositionAsyncTO Test>\n"));
	    LogFile.Write(_L8("Failed..\n"));
	    CloseFile();
   		return KErrGeneral;
   		}
    
    _LIT(Kidentity ,"Coreclass Testing" ) ;
	
	RRequestorStack aRequestorStack;
	const CRequestor* identityInfo = CRequestor::NewL(1 , 1 , Kidentity) ;
    aRequestorStack.Insert(identityInfo,0);
    
    CoreObj->SetRequestorIdentityL(aRequestorStack) ;
		
    LocUpdateCallBackTO MyUpdates  ;
    CoreObj->GetLocationL(&MyUpdates) ;
    CActiveScheduler :: Start() ;
    
    aRequestorStack.Close();
    delete identityInfo;
    delete CoreObj;
    return KErrNone;
	}


TInt Csapiloctotest::GetPositionAsyncTO( CStifItemParser& aItem )
	{
  	TInt aRet = KErrNone;
  	TRequestStatus status = KRequestPending;
  	returnCode = KErrNone;
    // Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "GetPositionAsyncTO" );
	TestModuleIf().Printf( 0, KSAPILocTest, KExample );
	 
	__UHEAP_MARK;
	
	TRAPD(err , aRet = GetLocFunctionTOL()) ;
    
    if( err || aRet )
    returnCode = KErrGeneral; 
	
	__UHEAP_MARKEND;
	
	return returnCode;
	}

*/
// -----------------------------------------------------------------------------
// Csapiloctotest::TraceLPositionTO
// -----------------------------------------------------------------------------
//

/*class TraceLCallBackTO : public MLocationCallBack
	{
    TInt iCount ;
    TInt iRetStatus ;
    public :
    TInt HandleNotifyL(HPositionGenericInfo *aOutPos , TInt aError) ;
    TraceLCallBackTO() :iCount(0) , iRetStatus(KErrGeneral){;}
    };
  
TInt TraceLCallBackTO :: HandleNotifyL(HPositionGenericInfo *currPos , TInt aError)
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


TInt TraceLFunctionTOL()
	{
    TInt ret1;
    TPositionInfo aPosition1;  
    CLocationService *CoreObj = CLocationService ::NewL() ;
    
    if( NULL == CoreObj )
    	{
    	OpenFile();
	    LogFile.Write(_L8("\n<TraceLPositionTO Test>\n"));
	    LogFile.Write(_L8("Failed..\n"));
	    CloseFile();
   		return KErrGeneral;
   		}
    
    _LIT(Kidentity ,"Coreclass Testing" ) ;
	RRequestorStack aRequestorStack;
	const CRequestor* identityInfo = CRequestor::NewL(1 , 1 , Kidentity) ;
    aRequestorStack.Insert(identityInfo,0);
    CoreObj->SetRequestorIdentityL(aRequestorStack) ;
		    
    TraceLCallBackTO MyUpdates ;
    
    ret1 = CoreObj->TraceL(&MyUpdates) ;
    
    if( KErrNone == ret1 )
    	{
        OpenFile();
	 	LogFile.Write(_L8("\n<TraceLPosition test>\n"));
	    CloseFile();
	 	returnCode = KErrNone;
	 	CActiveScheduler :: Start() ;
    	}
    	
    else
    	{
    	returnCode = KErrGeneral;	
    	}
    
    aRequestorStack.Close();
    delete identityInfo;
    delete CoreObj;
    return 0;
	}


TInt Csapiloctotest::TraceLPositionTO( CStifItemParser& aItem )
	{
    TInt aRet = KErrNone;
    returnCode = KErrNone;
   
    // Print to UI
    _LIT( KSAPILocTest, "SAPILocTest" );
    _LIT( KExample, "TraceLPositionTO" );
    TestModuleIf().Printf( 0, KSAPILocTest, KExample );
    
    __UHEAP_MARK;
    
    TRAPD(err ,aRet = TraceLFunctionTOL()) ;
    if( err || aRet )
    returnCode = KErrGeneral;
    
    __UHEAP_MARKEND;
    
    return returnCode;  
	}	*/