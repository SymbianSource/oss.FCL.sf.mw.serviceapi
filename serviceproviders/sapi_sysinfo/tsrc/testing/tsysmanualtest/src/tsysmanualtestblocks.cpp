/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
#include <StifTestInterface.h>
#include "tsysmanualtest.h"
#include "tmemnot.h"
#include "tsysbatterynot.h"

// EXTERNAL DATA STRUCTURES
//extern  ?external_data;

// EXTERNAL FUNCTION PROTOTYPES  
//extern ?external_function( ?arg_type,?arg_type );

// CONSTANTS
//const ?type ?constant_var = ?constant;

// MACROS
//#define ?macro ?macro_def

// LOCAL CONSTANTS AND MACROS
//const ?type ?constant_var = ?constant;
//#define ?macro_name ?macro_def

// MODULE DATA STRUCTURES
//enum ?declaration
//typedef ?declaration

// LOCAL FUNCTION PROTOTYPES
//?type ?function_name( ?arg_type, ?arg_type );

// FORWARD DECLARATIONS
//class ?FORWARD_CLASSNAME;

// ============================= LOCAL FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// ?function_name ?description.
// ?description
// Returns: ?value_1: ?description
//          ?value_n: ?description_line1
//                    ?description_line2
// -----------------------------------------------------------------------------
//
/*
?type ?function_name(
    ?arg_type arg,  // ?description
    ?arg_type arg)  // ?description
    {

    ?code  // ?comment

    // ?comment
    ?code
    }
*/

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctsysmanualtest::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void Ctsysmanualtest::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// Ctsysmanualtest::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt Ctsysmanualtest::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "NotifyVibraAndAcc", Ctsysmanualtest::NotifyVibraAndAcc ),
		//Battery related
		ENTRY( "BatteryNotifications",Ctsysmanualtest::BatteryNotifications),
		ENTRY( "BatteryLevel", Ctsysmanualtest::BatteryLevel ),
		ENTRY( "ChargingStatus", Ctsysmanualtest::ChargingStatus ),
		
		//Memory related
		ENTRY( "MemoryCardState", Ctsysmanualtest::MemoryCardState ) ,
//		ENTRY( "CriticalMemNotification", Ctsysmanualtest::CriticalMemNotitication ),
//		ENTRY( "MemCardNotification", Ctsysmanualtest::MemCardNotification ),
        
        //Display related
        ENTRY( "DisplayOrientation", Ctsysmanualtest::DisplayOrientation ),
        ENTRY( "SetAndGetKeyLockTime", Ctsysmanualtest::SetAndGetKeyLockTime ),
        ENTRY( "SetAndGetKeyGuardTime", Ctsysmanualtest::SetAndGetKeyGuardTime ),
        
        //General related
        ENTRY( "GetFlipStatus", Ctsysmanualtest::GetFlipStatus ),
        ENTRY( "GetGripStatus", Ctsysmanualtest::GetGripStatus ),
        ENTRY( "GetConnAcc", Ctsysmanualtest::GetConnAcc ),
        ENTRY( "SetDisplayLanguage", Ctsysmanualtest::SetDisplayLanguage ),
        
        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// Ctsysmanualtest::NotifyVibraAndAcc
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctsysmanualtest::NotifyVibraAndAcc( CStifItemParser& /*aItem*/ )
    {
 __UHEAP_MARK;
 
    TInt returnCode = KErrNone ;
   
    returnCode = TestAccAndVibraNot(iLog) ;
   
    __UHEAP_MARKEND ;
    return returnCode ;

    }

// -----------------------------------------------------------------------------
// Ctsysmanualtest::BatteryNotifications
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctsysmanualtest::BatteryNotifications( CStifItemParser& /*aItem*/ )
    {
   	TInt Err = KErrNone ;
	
	#if ( !(defined(__WINS__) || defined(__WINSCW__)) )
	__UHEAP_MARK;

	CBatteryNot *test = CBatteryNot::NewL(iLog);
	test->Start();
	Err = test->Result();
	delete test;
    
    #endif
	__UHEAP_MARKEND;
	return Err;

    
    }
    
// -----------------------------------------------------------------------------
// Ctsysmanualtest::BatteryLevel
// Tests Battery level
// -----------------------------------------------------------------------------
//
TInt Ctsysmanualtest::BatteryLevel( CStifItemParser& aItem )
    {

    __UHEAP_MARK;
   
    TInt returnCode = KErrNone ;
  
    _LIT(KEntity,"Battery") ;
    _LIT(KKey,"BatteryLevel") ;
    
    
    TInt expLevel = 0;
    TInt expDataType = 0 ;
    aItem.GetNextInt ( expLevel ) ;
   
    #if ( !(defined(__WINS__) || defined(__WINSCW__)) )
    
    CSysInfoService *CoreObj = CSysInfoService :: NewL() ;
    
    if( NULL == CoreObj)
	    {
	    iLog->Log(_L8("Failed.. @Core")) ;
	   	return KErrGeneral ;
	   	}
    

    CSysData *sysData ;
   	
   	
    iLog->Log(_L8("expLevel : %d"),expLevel) ;
    
    TRAPD(leaveCode, CoreObj->GetInfoL(KEntity,KKey,sysData) );
    
    if(KErrNone == leaveCode)
    	{
        
	    TInt retType = sysData->DataType() ;
	    
	    if(expDataType == retType)
		    {
		      
		    CStatus *status = (CStatus*)sysData ;
		    TInt retStatus = status->Status() ;
	   
		    if(expLevel != retStatus)
		    	{
		        returnCode = KErrGeneral ; 
		    	iLog->Log(_L8("Failed.. @retStatus")) ;
		    	}
		   	else
		   		{
		   		iLog->Log(_L8("Passed..")) ; 	
		   		}
		   	  
		    }
		    
		else
			{
			returnCode = KErrGeneral ;	
			iLog->Log(_L8("Failed.. @retType")) ;
			}    
	    
	    delete sysData ;
	    
	    }
    else
    	{
    	returnCode = KErrGeneral ;
    	iLog->Log(_L8("Failed.. @TRAPD")) ;
    	}
    delete CoreObj ;
    
    #endif
    
    __UHEAP_MARKEND ;
 
    return returnCode ;
    
    }


// -----------------------------------------------------------------------------
// Ctsysmanualtest::ChargingStatus
// Tests Charging status
// -----------------------------------------------------------------------------
//
TInt Ctsysmanualtest::ChargingStatus( CStifItemParser& aItem )
    {

    __UHEAP_MARK;
    
    TInt returnCode = KErrNone ;
       
    _LIT(KEntity,"Battery") ;
    _LIT(KKey,"ChargingStatus") ;
    
    
    TInt expStatus = 0;
    TInt expDataType = 0 ;
    aItem.GetNextInt ( expStatus ) ;
    
    #if ( !(defined(__WINS__) || defined(__WINSCW__)) ) 
    
    CSysInfoService *CoreObj = CSysInfoService :: NewL() ;
    
    if( NULL == CoreObj)
	    {
	    iLog->Log(_L8("Failed.. @Core")) ;
	   	return KErrGeneral ;
	   	}
    
    CSysData *sysData ;
   	
    iLog->Log(_L8("expStatus : %d"),expStatus) ;
    
    TRAPD(leaveCode, CoreObj->GetInfoL(KEntity,KKey,sysData) );
    
    if(KErrNone == leaveCode)
    {
        
    TInt retType = sysData->DataType() ;
    
    if(expDataType == retType)
	    {
	      
	    CStatus *status = (CStatus*)sysData ;
	    TInt retStatus = status->Status() ;
   
	    if(expStatus != retStatus)
	    	{
	        returnCode = KErrGeneral ; 
	    	iLog->Log(_L8("Failed.. @retStatus")) ;
	    	}
	   	else
	   		{
	   		iLog->Log(_L8("Passed..")) ; 	
	   		}
	   	  
	    }
	    
	else
		{
		returnCode = KErrGeneral ;	
		iLog->Log(_L8("Failed.. @retType")) ;
		}    
   
    delete sysData ;
     
    }
    else
    	{
    	returnCode = KErrGeneral ;
    	iLog->Log(_L8("Failed.. @TRAPD")) ;
    	}
    delete CoreObj ;
    
    #endif
   
    __UHEAP_MARKEND ;
    return returnCode ;
    
    }

// -----------------------------------------------------------------------------
// Ctsysmanualtest::MemoryCardState
// Tests the MemoryCardState functionality
// -----------------------------------------------------------------------------
//
TInt Ctsysmanualtest::MemoryCardState( CStifItemParser& aItem )
    {

	 __UHEAP_MARK;
    
    _LIT(KEntity,"Memory") ;
    _LIT(KKey,"MemoryCard") ;
    
    TInt returnCode = KErrNone ;
    TInt expState = 0 ;
    TInt expDataType = 0 ;
    aItem.GetNextInt (expState) ;
    
    CSysInfoService *CoreObj = CSysInfoService :: NewL() ;
    
    if( NULL == CoreObj)
	    {
	    iLog->Log(_L8("Failed.. @Core")) ;
	   	return KErrGeneral ;
	   	}

    CSysData *sysData ;
   	
   	
    iLog->Log(_L8("expState : %d"),expState) ;	
    TRAPD(leaveCode, CoreObj->GetInfoL(KEntity,KKey,sysData)) ;
    if(KErrNone == leaveCode)
	    {
	       
	    TInt retType = sysData->DataType() ;
	    
	    if(expDataType == retType)
		    {
		      
		    CStatus *status = (CStatus*)sysData ;
		    TInt retStatus = status->Status() ;
		    	   
		    if(expState != retStatus)
		    	{
		        returnCode = KErrGeneral ; 
		    	iLog->Log(_L8("Failed.. @retStatus")) ;
		    	}
		    else
		    	{
		    	iLog->Log(_L8("Passed..")) ;	
		    	}
		     }
		    
		else
			{
			returnCode = KErrGeneral ;	
			iLog->Log(_L8("Failed.. @retType")) ;
			}    
	    
	    delete sysData ;
	    
	    }
    else
    	{
    	returnCode = KErrGeneral ;
    	iLog->Log(_L8("Failed.. @TRAPD")) ;
    	}
    delete CoreObj ;
   
    __UHEAP_MARKEND ;
    return returnCode ;

    }

// -----------------------------------------------------------------------------
// Ctsysmanualtest::DisplayOrientation
// Tests DisplayOrientation values
// -----------------------------------------------------------------------------
//
TInt Ctsysmanualtest::DisplayOrientation( CStifItemParser& aItem )
    {

   __UHEAP_MARK;
    
    _LIT(KEntity,"Display") ;
    _LIT(KKey,"DisplayOrientation") ;
    
    TInt returnCode = KErrNone ;
    TInt expDataType = 0 ;
    TInt expOrientation = 0;
    aItem.GetNextInt ( expOrientation ) ;   
    
    CSysInfoService *CoreObj = CSysInfoService :: NewL() ;
    
    if( NULL == CoreObj)
	    {
	    iLog->Log(_L8("Failed.. @Core")) ;
	   	return KErrGeneral ;
	   	}

    CSysData *sysData ;
   	
    iLog->Log(_L8("expOrientation : %d"),expOrientation) ;
       
    TRAPD(leaveCode, CoreObj->GetInfoL(KEntity,KKey,sysData) );
    
    if(KErrNone == leaveCode)
    {
        
    TInt retType = sysData->DataType() ;
    
    if(expDataType == retType)
	    {
	      
	    CStatus *status = (CStatus*)sysData ;
	    TInt retStatus = status->Status() ;
   		iLog->Log(_L8("retStatus : %d"),retStatus) ;
	    
	    if(expOrientation == retStatus) 
	    	{
	       	iLog->Log(_L8("Passed..")) ; 
	        }
	   	else
	   		{
	   		returnCode = KErrGeneral ; 
	    	iLog->Log(_L8("Failed.. @retStatus")) ;
	   		}
	   	  
	    }
	    
	else
		{
		returnCode = KErrGeneral ;	
		iLog->Log(_L8("Failed.. @retType")) ;
		}    
    
    delete sysData ;
    
    }
    else
    	{
    	iLog->Log(_L8("Failed.. @TRAPD")) ;
    	}
    delete CoreObj ;
    
    
    __UHEAP_MARKEND ;
    return returnCode ;
    

    }
    
 
 // -----------------------------------------------------------------------------
// Ctsysmanualtest::SetAndGetKeyLockTime
// Tests set and get KeylockTime values
// -----------------------------------------------------------------------------
//
TInt Ctsysmanualtest::SetAndGetKeyLockTime( CStifItemParser& aItem )
    {

   __UHEAP_MARK;
    
    _LIT(KEntity,"Display") ;
    _LIT(KKey,"AutoLockTime") ;
    
    TInt returnCode = KErrNone ;
    TInt expDataType = 0 ;
    TInt defValue = 0 ;
    TInt expTime = 0;
    aItem.GetNextInt ( expTime ) ;   
    
    CSysInfoService *CoreObj = CSysInfoService :: NewL() ;
    
    if( NULL == CoreObj)
	    {
	    iLog->Log(_L8("Failed.. @Core")) ;
	   	return KErrGeneral ;
	   	}
 	
 	CStatus *ipData = CStatus::NewL(expTime) ;
   	      
    TRAPD(leaveCode, CoreObj->SetInfoL(KEntity,KKey,ipData)) ;
    
    if(KErrNone == leaveCode)
	    {
	   
	    CSysData *sysData ;
	   	
	    iLog->Log(_L8("expTime : %d"),expTime) ;
	       
	    TRAPD(leaveCode, CoreObj->GetInfoL(KEntity,KKey,sysData) );
	    
	    if(KErrNone == leaveCode)
	    {
	        
	    TInt retType = sysData->DataType() ;
	    
	    if(expDataType == retType)
		    {
		      
		    CStatus *status = (CStatus*)sysData ;
		    TInt retStatus = status->Status() ;
	   		iLog->Log(_L8("retStatus : %d"),retStatus) ;
		    
		    if(expTime == retStatus) 
		    	{
		      	iLog->Log(_L8("Passed..")) ; 
		        }
		   	else
		   		{
		   		returnCode = KErrGeneral ; 
		    	iLog->Log(_L8("Failed.. @retStatus")) ;
		   		}
			    
		    }
		    
		else
			{
			returnCode = KErrGeneral ;	
			iLog->Log(_L8("Failed.. @retType")) ;
			}    
	    
	    delete sysData ;
	    
	    }
	    else
	    	{
	    	returnCode = KErrGeneral ;
	    	iLog->Log(_L8("Failed.. @2 TRAPD")) ;
	    	}
	         	
	    }
    
    else
    	{
    	returnCode = KErrGeneral ;
    	iLog->Log(_L8("Failed.. @TRAPD")) ;
    	}

   	CStatus *defData = CStatus::NewL(defValue) ;
   	      
//    CoreObj->SetInfoL(KEntity,KKey,defData) ;
    
    delete defData ;
    delete ipData ;
    delete CoreObj ;
     
    __UHEAP_MARKEND ;
    return returnCode ;
    

    }
       
// -----------------------------------------------------------------------------
// Ctsysmanualtest::SetAndGetKeyGuardTime
// Tests set and get KeyguardTime values
// -----------------------------------------------------------------------------
//
TInt Ctsysmanualtest::SetAndGetKeyGuardTime( CStifItemParser& aItem )
    {

   __UHEAP_MARK;
    
    _LIT(KEntity,"Display") ;
    _LIT(KKey,"KeyGaurdTime") ;
    
    TInt returnCode = KErrNone ;
    TInt expDataType = 0 ;
    TInt defValue = 0 ;
    TInt expTime = 0;
    aItem.GetNextInt ( expTime ) ;   
    
    CSysInfoService *CoreObj = CSysInfoService :: NewL() ;
    
    if( NULL == CoreObj)
	    {
	    iLog->Log(_L8("Failed.. @Core")) ;
	   	return KErrGeneral ;
	   	}
 	
 	CStatus *ipData = CStatus::NewL(expTime) ;
   	      
    TRAPD(leaveCode, CoreObj->SetInfoL(KEntity,KKey,ipData)) ;
    
    if(KErrNone == leaveCode)
	    {
	   
	    CSysData *sysData ;
	   	
	    iLog->Log(_L8("expTime : %d"),expTime) ;
	       
	    TRAPD(leaveCode, CoreObj->GetInfoL(KEntity,KKey,sysData) );
	    
	    if(KErrNone == leaveCode)
	    {
	        
	    TInt retType = sysData->DataType() ;
	    
	    if(expDataType == retType)
		    {
		      
		    CStatus *status = (CStatus*)sysData ;
		    TInt retStatus = status->Status() ;
	   		iLog->Log(_L8("retStatus : %d"),retStatus) ;
		    
		    if(expTime == retStatus) 
		    	{
		      	iLog->Log(_L8("Passed..")) ; 
		        }
		   	else
		   		{
		   		returnCode = KErrGeneral ; 
		    	iLog->Log(_L8("Failed.. @retStatus")) ;
		   		}
			    
		    }
		    
		else
			{
			returnCode = KErrGeneral ;	
			iLog->Log(_L8("Failed.. @retType")) ;
			}    
	    
	    delete sysData ;
	    
	    }
	    else
	    	{
	    	returnCode = KErrGeneral ;
	    	iLog->Log(_L8("Failed.. @2 TRAPD")) ;
	    	}
	         	
	    }
    
    else
    	{
    	returnCode = KErrGeneral ;
    	iLog->Log(_L8("Failed.. @TRAPD")) ;
    	}

   	CStatus *defData = CStatus::NewL(defValue) ;
   	      
 //   CoreObj->SetInfoL(KEntity,KKey,defData) ;
    
    delete defData ;
    delete ipData ;
    delete CoreObj ;
     
    __UHEAP_MARKEND ;
    return returnCode ;
    

    }
 
 // -----------------------------------------------------------------------------
// Ctsysmanualtest::GetFlipStatus
// Test method for getting FlipStatus 
// -----------------------------------------------------------------------------
//
TInt Ctsysmanualtest::GetFlipStatus( CStifItemParser& aItem )
    {

    __UHEAP_MARK;
    
    _LIT(KEntity,"General") ;
    _LIT(KKey,"FlipStatus") ;
    
    TInt returnCode = KErrNone ;
    TInt expState = 0 ;
    TInt expDataType = 0 ;
    aItem.GetNextInt (expState) ;
    
    CSysInfoService *CoreObj = CSysInfoService :: NewL() ;
    
    if( NULL == CoreObj)
	    {
	    iLog->Log(_L8("Failed.. @Core")) ;
	   	return KErrGeneral ;
	   	}
    

    CSysData *sysData ;
   	
   	
    iLog->Log(_L8("FlipStatus : %d"),expState) ;	
    TRAPD(leaveCode, CoreObj->GetInfoL(KEntity,KKey,sysData)) ;
    if(KErrNone == leaveCode)
	    {
	       
	    TInt retType = sysData->DataType() ;
	    
	    if(expDataType == retType)
		    {
		      
		    CStatus *status = (CStatus*)sysData ;
		    TInt retStatus = status->Status() ;
		    	   
		    if(expState != retStatus)
		    	{
		        returnCode = KErrGeneral ; 
		    	iLog->Log(_L8("Failed.. @retStatus")) ;
		    	}
		    else
		    	{
		    	iLog->Log(_L8("Passed..")) ;	
		    	}
		     }
		    
		else
			{
			returnCode = KErrGeneral ;	
			iLog->Log(_L8("Failed.. @retType")) ;
			}    
	    
	    delete sysData ;
	    
	    }
    else
    	{
    	returnCode = KErrGeneral ;
    	iLog->Log(_L8("Failed.. @TRAPD")) ;
    	}
    delete CoreObj ;

    __UHEAP_MARKEND ;
    return returnCode ;

    }
  
  
// -----------------------------------------------------------------------------
// Ctsysmanualtest::GetGripStatus
// Test method for getting GripStatus 
// -----------------------------------------------------------------------------
//
TInt Ctsysmanualtest::GetGripStatus( CStifItemParser& aItem )
    {

    __UHEAP_MARK;
    
    _LIT(KEntity,"General") ;
    _LIT(KKey,"GripStatus") ;
    
    TInt returnCode = KErrNone ;
    TInt expState = 0 ;
    TInt expDataType = 0 ;
    aItem.GetNextInt (expState) ;
    
    CSysInfoService *CoreObj = CSysInfoService :: NewL() ;
    
    if( NULL == CoreObj)
	    {
	    iLog->Log(_L8("Failed.. @Core")) ;
	   	return KErrGeneral ;
	   	}
    

    CSysData *sysData ;
   	
   	
    iLog->Log(_L8("GripStatus : %d"),expState) ;	
    TRAPD(leaveCode, CoreObj->GetInfoL(KEntity,KKey,sysData)) ;
    if(KErrNone == leaveCode)
	    {
	       
	    TInt retType = sysData->DataType() ;
	    
	    if(expDataType == retType)
		    {
		      
		    CStatus *status = (CStatus*)sysData ;
		    TInt retStatus = status->Status() ;
		    	   
		    if(expState != retStatus)
		    	{
		        returnCode = KErrGeneral ; 
		    	iLog->Log(_L8("Failed.. @retStatus")) ;
		    	}
		    else
		    	{
		    	iLog->Log(_L8("Passed..")) ;	
		    	}
		     }
		    
		else
			{
			returnCode = KErrGeneral ;	
			iLog->Log(_L8("Failed.. @retType")) ;
			}    
	    
	    delete sysData ;
	    
	    }
    else
    	{
    	returnCode = KErrGeneral ;
    	iLog->Log(_L8("Failed.. @TRAPD")) ;
    	}
    delete CoreObj ;

    __UHEAP_MARKEND ;
    return returnCode ;

    }  
    
// -----------------------------------------------------------------------------
// Ctsysmanualtest::GetConnAcc
// Test method for getting connected accessories 
// -----------------------------------------------------------------------------
//
TInt Ctsysmanualtest::GetConnAcc( CStifItemParser& aItem )
    {

    __UHEAP_MARK;
    
    _LIT(KEntity,"General") ;
    _LIT(KKey,"ConnectedAccessories") ;
    
    TInt expDataType = 8 ;
    TInt returnCode = KErrNone ;
    TInt expAcc ;
    TInt expAccStatus ;
    aItem.GetNextInt(expAcc) ;   
    aItem.GetNextInt(expAccStatus) ;
    
    CSysInfoService *CoreObj = CSysInfoService :: NewL() ;
    
    if( NULL == CoreObj)
	    {
	    iLog->Log(_L8("Failed.. @Core")) ;
	   	return KErrGeneral ;
	   	}
    
    CSysData *sysData ;
    
    TRAPD(leaveCode, CoreObj->GetInfoL(KEntity,KKey,sysData)) ;
    if(KErrNone == leaveCode)
	    {
	       
	    TInt retType = sysData->DataType() ;
	    
	    if(expDataType == retType)
		    {
		      
		    CAccList *retData = (CAccList*)sysData ;
		    TInt listCount ;
		    listCount = retData->Count() ;
		    
		    if(listCount)
			    {
			    	
			    const CAccessoryInfo* accInfo = NULL ;
			    for(TInt i=0; i<listCount; i++)
				    {
  				    TInt accType ;
  				    TInt accStatus ;
  				    retData->AtL(i,accInfo) ;
				    accType = accInfo->AccessoryType() ;
				    accStatus = accInfo->ConnectionState() ;
				    if((accType == expAcc) && (accStatus == expAccStatus))
				    	{
				    	TBuf<20> accBuf(accType) ;
				    	TBuf<20> accStatBuf(accStatus) ;
				    	iLog->Log(_L8("Accessory :")) ;		    	   
				    	iLog->Log(accBuf) ;	
				    	iLog->Log(_L8("Status :")) ;		    	   
				    	iLog->Log(accStatBuf) ;	
				    	}
					else
						{
						returnCode = KErrGeneral ;
						}	  
							   	
				   	}
			    
			    }
		    
		    else
		    	{
		    	returnCode = KErrGeneral ;
		    	}
		     }
		    
		else
			{
			returnCode = KErrGeneral ;	
			iLog->Log(_L8("Failed.. @retType")) ;
			}    
	    
	    delete sysData ;
	    
	    }
    else
    	{
    	returnCode = KErrGeneral ;
    	iLog->Log(_L8("Failed.. @TRAPD")) ;
    	}
    delete CoreObj ;
 
    __UHEAP_MARKEND ;
    return returnCode ;

    }
       

// -----------------------------------------------------------------------------
// Ctsysmanualtest::SetDisplayLanguage
// Test method for setting DisplayLanguage 
// -----------------------------------------------------------------------------
//
TInt Ctsysmanualtest::SetDisplayLanguage(CStifItemParser& aItem)
    {
    __UHEAP_MARK;

    _LIT(KEntity, "General") ;
    _LIT(KKey, "DisplayLanguage") ;

    TInt returnCode = KErrNone;
    TInt expLanguage = 0;
    TInt expDataType = 0;
    aItem.GetNextInt(expLanguage) ;

    CSysInfoService *CoreObj = CSysInfoService::NewL() ;

    if (NULL == CoreObj)
        {
        iLog->Log(_L8("Failed.. @Core")) ;
        return KErrGeneral;
        }

    CStatus *sysData = CStatus::NewL(expLanguage) ;

    iLog->Log(_L8("DisplayLanguage : %d"), expLanguage) ;

    TRAPD(leaveCode, CoreObj->SetInfoL(KEntity, KKey, sysData)) ;

    if (KErrNotFound == leaveCode)
        {
        returnCode = KErrNone;
        }
    else
        {
        returnCode = KErrGeneral;
        iLog->Log(_L8("Failed.. @TRAPD")) ;
        }
    delete sysData;
    delete CoreObj;
    __UHEAP_MARKEND;
    return returnCode;

    }


// -----------------------------------------------------------------------------
// Ctsysmanualtest::CriticalMemNotitication
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
/*TInt Ctsysmanualtest::CriticalMemNotitication( CStifItemParser& aItem )
    {
   	TInt Err = KErrNone ;
	TInt expDrive = 0 ;
	aItem.GetNextInt (expDrive) ;
//	#if ( !(defined(__WINS__) || defined(__WINSCW__)) )
	__UHEAP_MARK;

	CCriticalMemNot *test = CCriticalMemNot::NewL(iLog, expDrive, 0);
	test->Start();
	Err = test->Result();
	delete test;
    
//    #endif
	__UHEAP_MARKEND;
	return Err;

    
    }

*/
// -----------------------------------------------------------------------------
// Ctsysmanualtest::MemCardNotification
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
/*TInt Ctsysmanualtest::MemCardNotification( CStifItemParser& aItem )
    {
   	TInt Err = KErrNone ;
//	#if ( !(defined(__WINS__) || defined(__WINSCW__)) )
	__UHEAP_MARK;

	CCriticalMemNot *test = CCriticalMemNot::NewL(iLog, 1, 1);
	test->Start();
	Err = test->Result();
	delete test;
    
//    #endif
	__UHEAP_MARKEND;
	return Err;

    
    }
*/
// -----------------------------------------------------------------------------
// Ctsysmanualtest::?member_function
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
/*
TInt Ctsysmanualtest::?member_function(
   CItemParser& aItem )
   {

   ?code

   }
*/

// ========================== OTHER EXPORTED FUNCTIONS =========================
// None

//  End of File
