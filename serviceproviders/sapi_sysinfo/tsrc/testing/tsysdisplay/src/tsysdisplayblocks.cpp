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
* Description:   Tests sysinfo display functions
*
*/




// INCLUDE FILES
#include <e32svr.h>
#include <StifParser.h>
#include <StifTestInterface.h>
#include <escapeutils.h> 

#include "tsysdisplay.h"
#include "tsysdisplaynot.h"

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
// Ctsysdisplay::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void Ctsysdisplay::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// Ctsysdisplay::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt Ctsysdisplay::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "SetAndGetBrightness", Ctsysdisplay::SetAndGetBrightness ),
        ENTRY( "SetAndGetScreenSaverTO", Ctsysdisplay::SetAndGetScreenSaverTO ),
		ENTRY( "SetAndGetKeyLockTime", Ctsysdisplay::SetAndGetKeyLockTime ),
		ENTRY( "SetAndGetKeyLockStatus", Ctsysdisplay::SetAndGetKeyLockStatus ),
		ENTRY( "SetAndGetWallpaper", Ctsysdisplay::SetAndGetWallpaper ),
		ENTRY( "SetAndGetLightTimeOut", Ctsysdisplay::SetAndGetLightTimeOut ),
		ENTRY( "SetAndGetKeyGuardTime", Ctsysdisplay::SetAndGetKeyGuardTime ),
		ENTRY( "DisplayResolution", Ctsysdisplay::DisplayResolution ),
  		ENTRY( "DisplayOrientation", Ctsysdisplay::DisplayOrientation ),
		ENTRY( "WrongKey", Ctsysdisplay::WrongKey ),
		ENTRY( "SetWrongDataType", Ctsysdisplay::SetWrongDataType ),
		ENTRY( "UserActGetAsync", Ctsysdisplay::UserActGetAsync ),
		ENTRY( "UserActNotWithWrongIp", Ctsysdisplay::UserActNotWithWrongIp ),
		ENTRY( "UserActNotWithWrongKey", Ctsysdisplay::UserActNotWithWrongKey ),
        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// Ctsysdisplay::SetAndGetBrightness
// Tests Set and Get brightness values
// -----------------------------------------------------------------------------
//
TInt Ctsysdisplay::SetAndGetBrightness( CStifItemParser& aItem )
    {

   __UHEAP_MARK;
    
    _LIT(KEntity,"Display") ;
    _LIT(KKey,"Brightness") ;
    
    TInt returnCode = KErrNone ;
    TInt expDataType = 0 ;
    TInt expPercent = 0;
    TInt defPercent = 50 ;
   //  #ifndef __WINSCW__ || __WINS__
     aItem.GetNextInt( expPercent ) ;   
  //   #else
  //   expPercent = 50 ;
 //    #endif
        
    CSysInfoService *CoreObj = CSysInfoService :: NewL() ;
    
    if( NULL == CoreObj)
	    {
	    iLog->Log(_L8("Failed.. @Core")) ;
	   	return KErrGeneral ;
	   	}
    
 	CStatus *ipData = CStatus::NewL(expPercent) ;
   	      
    TRAPD(leaveCode, CoreObj->SetInfoL(KEntity,KKey,ipData)) ;
    /*
    if(KErrNone == leaveCode)
	    {
	    
	    CSysData *sysData ;
	   	      
	    TRAPD(leaveCode, CoreObj->GetInfoL(KEntity,KKey,sysData) );
	    
	    if(KErrNone == leaveCode)
	    {
	        
	    TInt retType = sysData->DataType() ;
	    
	    if(expDataType == retType)
		    {
		      
		    CStatus *status = (CStatus*)sysData ;
		    TInt retStatus = status->Status() ;
	   		iLog->Log(_L8("Brightness:%d"),retStatus) ;
		    
		    if(expPercent == retStatus)
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
	else if(KErrArgument == leaveCode)
	{
		returnCode = KErrNone;
		iLog->Log(_L8("Min or Max values out of bounds")) ;		
	}
    else
    	{
    	returnCode = KErrGeneral ;
    	iLog->Log(_L8("Failed.. @TRAPD")) ;
    	}
    
    
    CStatus *defData = CStatus::NewL(defPercent) ;
   	      
 //   CoreObj->SetInfoL(KEntity,KKey,defData) ;
    
    delete defData ;
    */
    
    if(KErrNotFound == leaveCode)
    {
    	iLog->Log(_L8("Passed..")) ; 
    }
    else
    {
    	returnCode = KErrGeneral ;
    	iLog->Log(_L8("Failed.. @TRAPD")) ;    	
    }
    delete ipData ;
    delete CoreObj ;
        
    __UHEAP_MARKEND ;
    return returnCode ;
    

    }
    
    
// -----------------------------------------------------------------------------
// Ctsysdisplay::SetAndGetScreenSaverTO
// Tests Set and Get ScreenSaverTimeOut values
// -----------------------------------------------------------------------------
//
TInt Ctsysdisplay::SetAndGetScreenSaverTO( CStifItemParser& aItem )
    {

   __UHEAP_MARK;
    
    _LIT(KEntity,"Display") ;
    _LIT(KKey,"ScreenSaverTimeOut") ;
    
    TInt returnCode = KErrNone ;
    TInt expDataType = 0 ;
    TInt expTimeOut = 0;
    TInt defTimeOut = 15 ;
    aItem.GetNextInt( expTimeOut ) ;  
        
    CSysInfoService *CoreObj = CSysInfoService :: NewL() ;
    
    if( NULL == CoreObj)
	    {
	    iLog->Log(_L8("Failed.. @Core")) ;
	   	return KErrGeneral ;
	   	}
    
	CStatus *ipData = CStatus::NewL(expTimeOut) ;
   	      
    TRAPD(leaveCode, CoreObj->SetInfoL(KEntity,KKey,ipData)) ;
    /*
    if(KErrNone == leaveCode)
	    {

	    CSysData *sysData ;
	   	       
	    TRAPD(leaveCode, CoreObj->GetInfoL(KEntity,KKey,sysData) );
	    
	    if(KErrNone == leaveCode)
	    {
	        
	    TInt retType = sysData->DataType() ;
	    
	    if(expDataType == retType)
		    {
		      
		    CStatus *status = (CStatus*)sysData ;
		    TInt retStatus = status->Status() ;
	   		iLog->Log(_L8("ScreenSaverTimeOut:%d"),retStatus) ;
		    
		    if(expTimeOut == retStatus)
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
   
    CStatus *defData = CStatus::NewL(defTimeOut) ;
   	      
//    CoreObj->SetInfoL(KEntity,KKey,defData) ;
        
    delete defData ;
    */
    
    if(KErrNotFound == leaveCode)
    {
    	iLog->Log(_L8("Passed..")) ; 
    }
    else
    {
    	returnCode = KErrGeneral ;
    	iLog->Log(_L8("Failed.. @TRAPD")) ;    	
    }
    
    delete ipData ;
    delete CoreObj ;
    
   
    __UHEAP_MARKEND ;
    return returnCode ;
    

    }



// -----------------------------------------------------------------------------
// Ctsysdisplay::SetAndGetKeyLockTime
// Tests set and get KeylockTime values
// -----------------------------------------------------------------------------
//
TInt Ctsysdisplay::SetAndGetKeyLockTime( CStifItemParser& aItem )
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
    /*    
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
   	      
    CoreObj->SetInfoL(KEntity,KKey,defData) ;
    
    delete defData ;
    */
    
    if(KErrNotFound == leaveCode)
    {
    	iLog->Log(_L8("Passed..")) ; 
    }
    else
    {
    	returnCode = KErrGeneral ;
    	iLog->Log(_L8("Failed.. @TRAPD")) ;    	
    }
    
    delete ipData ;
    delete CoreObj ;
     
    __UHEAP_MARKEND ;
    return returnCode ;
    

    }
    


// -----------------------------------------------------------------------------
// Ctsysdisplay::SetAndGetKeyLockStatus
// Tests set and get Keylock status values
// -----------------------------------------------------------------------------
//
TInt Ctsysdisplay::SetAndGetKeyLockStatus( CStifItemParser& aItem )
    {

   __UHEAP_MARK;
    
    _LIT(KEntity,"Display") ;
    _LIT(KKey,"AutoLockStatus") ;
    
    TInt returnCode = KErrNone ;
    TInt expDataType = 0 ;
    TInt expState = 0;
    aItem.GetNextInt ( expState ) ;   
    
    CSysInfoService *CoreObj = CSysInfoService :: NewL() ;
    
    if( NULL == CoreObj)
	    {
	    iLog->Log(_L8("Failed.. @Core")) ;
	   	return KErrGeneral ;
	   	}
 	
 /*	CStatus *ipData = CStatus::NewL(expState) ;
   	      
    TRAPD(leaveCode, CoreObj->SetInfoL(KEntity,KKey,ipData)) ;
    
    if(KErrNone == leaveCode)
	    {
*/	   
	    CSysData *sysData ;
	   	
	    iLog->Log(_L8("expState : %d"),expState) ;
	       
	    TRAPD(leaveCode, CoreObj->GetInfoL(KEntity,KKey,sysData) );
	    
	    if(KErrNone == leaveCode)
	    {
	        
	    TInt retType = sysData->DataType() ;
	    
	    if(expDataType == retType)
		    {
		      
		    CStatus *status = (CStatus*)sysData ;
		    TInt retStatus = status->Status() ;
	   		iLog->Log(_L8("retStatus : %d"),retStatus) ;
		    
		    if(expState == retStatus) 
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
	         	
/*	    }
    else
	    	{
	    	returnCode = KErrGeneral ;
	    	iLog->Log(_L8("Failed.. @TRAPD")) ;
	    	}
    
    delete ipData ;
  */
    delete CoreObj ;
     
    __UHEAP_MARKEND ;
    return returnCode ;
    

    }
    
    
// -----------------------------------------------------------------------------
// Ctsysdisplay::SetAndGetWallpaper
// Tests Wallpaper Path
// -----------------------------------------------------------------------------
//
TInt Ctsysdisplay::SetAndGetWallpaper( CStifItemParser& aItem )
    {

   __UHEAP_MARK;
    
    _LIT(KEntity,"Display") ;
    _LIT(KKey,"Wallpaper") ;
    _LIT(KNoFile, "No") ; 
    TInt returnCode = KErrNone ;
 //   TInt expDataType = 12 ;
 //   TInt fileLength = 50 ;
    TPtrC expPath ; 
   // TPtrC8 eightRetPath ;
    
    aItem.GetNextString(expPath) ;   
    
  //  HBufC8* operName = EscapeUtils::ConvertFromUnicodeToUtf8L(expPath);
//	eightRetPath.Set(*operName) ;
    
    TBuf<500> fileName(expPath);
    CSysInfoService *CoreObj = CSysInfoService :: NewL() ;
    
    if( NULL == CoreObj)
	    {
	    iLog->Log(_L("Failed.. @Core")) ;
	   	return KErrGeneral ;
	   	}
    	
    iLog->Log(_L8("expPath:")) ;
    iLog->Log(fileName) ;
       
		CStringData *ipData ;
	
	if(!expPath.Compare(KNoFile))
		{
		ipData = CStringData::NewL(KNullDesC) ;	
		}
   	else
	   	{
	    ipData = CStringData::NewL(expPath) ;	
	   	}
   	
   	      
    TRAPD(leaveCode, CoreObj->SetInfoL(KEntity,KKey,ipData)) ;
    
    if(KErrNone == leaveCode)
	    {
/*	   
	    CSysData *sysData ;
	   
	    TRAPD(leaveCode, CoreObj->GetInfoL(KEntity,KKey,sysData) );
	    
	    if(KErrNone == leaveCode)
	    {
	        
	    TInt retType = sysData->DataType() ;
	    
	    if(expDataType == retType)
		    {
		      
		    CStringData *retData = (CStringData*)sysData ;
		    TPtrC retPath ;
		    
		    
		    retData->StringData(retPath) ;
		    TBuf<50> retFileName(retPath);
		    
		    if(expPath.Compare(KNoFile))
			    {
			    iLog->Log(_L("retPath ")) ; 
			    iLog->Log(retFileName) ; 
			    if(expPath.Compare(retPath)) 
			    	{
			       	returnCode = KErrGeneral ; 
			    	iLog->Log(_L8("Failed.. @retPath")) ;
			        }
			   	else
			   		{
			   	   	iLog->Log(_L8("Passed..")) ; 
			   		}
			   	  
			    }
		    
		    else
		    	{
		    	if(retPath.Compare(KNullDesC))
		    		{
		    		returnCode = KErrGeneral ;
		    		iLog->Log(_L8("Failed.. @retPath")) ;
		    		}
		    	else
		    		{
		    		iLog->Log(_L8("Passed..")) ; 	
		    		}
		    		
		    	}
		    
		    delete sysData ;	
		    
		    }
		    
		else
			{
			returnCode = KErrGeneral ;	
			iLog->Log(_L8("Failed.. @2 retType")) ;
			}    
	    }
	    else
	    	{
	    	returnCode = KErrGeneral ;
	    	iLog->Log(_L8("Failed.. @TRAPD")) ;
	    	}
*/
	     	
	    }
    
     else
    	{
    	returnCode = KErrGeneral ;
    	iLog->Log(_L8("Failed.. @TRAPD")) ;
    	}
    
    delete ipData ;
    delete CoreObj ;

    
    __UHEAP_MARKEND ;
    return returnCode ;
    

    }


// -----------------------------------------------------------------------------
// Ctsysdisplay::SetAndGetLightTimeOut
// Tests set and get LightTimeOut values
// -----------------------------------------------------------------------------
//
TInt Ctsysdisplay::SetAndGetLightTimeOut( CStifItemParser& aItem )
    {

   __UHEAP_MARK;
    
    _LIT(KEntity,"Display") ;
    _LIT(KKey,"LightTimeOut") ;
    
    TInt returnCode = KErrNone ;
    TInt expDataType = 0 ;
    TInt expTimeOut = 0;
    aItem.GetNextInt ( expTimeOut ) ;   
    
    CSysInfoService *CoreObj = CSysInfoService :: NewL() ;
    
    if( NULL == CoreObj)
	    {
	    iLog->Log(_L8("Failed.. @Core")) ;
	   	return KErrGeneral ;
	   	}
	
	CStatus *ipData = CStatus::NewL(expTimeOut) ;
         
    TRAPD(leaveCode, CoreObj->SetInfoL(KEntity,KKey,ipData)) ;
    /*
    if(KErrNone == leaveCode)
	    {
	   
	    CSysData *sysData ;
	   	
	    iLog->Log(_L8("expTimeOut : %d"),expTimeOut) ;
	       
	    TRAPD(leaveCode, CoreObj->GetInfoL(KEntity,KKey,sysData) );
	    
	    if(KErrNone == leaveCode)
		    {
		        
		    TInt retType = sysData->DataType() ;
		    
		    if(expDataType == retType)
			    {
			      
			    CStatus *status = (CStatus*)sysData ;
			    TInt retStatus = status->Status() ;
		   
			    if(expTimeOut == retStatus) 
			    	{
			       	iLog->Log(_L8("retStatus : %d"),retStatus) ;
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
	    	iLog->Log(_L8("Failed.. @TRAPD")) ;
	    	}
	        
	    }
    
    else
    	{
    	returnCode = KErrGeneral ;
    	iLog->Log(_L8("Failed.. @TRAPD")) ;
    	}
   */
   
    if(KErrNotFound == leaveCode)
    {
    	iLog->Log(_L8("Passed..")) ; 
    }
    else
    {
    	returnCode = KErrGeneral ;
    	iLog->Log(_L8("Failed.. @TRAPD")) ;    	
    }
       
   delete ipData ;  
   delete CoreObj ;
    
    
    __UHEAP_MARKEND ;
    return returnCode ;
    

    }
    



// -----------------------------------------------------------------------------
// Ctsysdisplay::SetAndGetKeyGuardTime
// Tests set and get KeyguardTime values
// -----------------------------------------------------------------------------
//
TInt Ctsysdisplay::SetAndGetKeyGuardTime( CStifItemParser& aItem )
    {

   __UHEAP_MARK;
    
    _LIT(KEntity,"Display") ;
    _LIT(KKey,"KeyGuardTime") ;
    
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
    /*
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
    */

    if(KErrNotFound == leaveCode)
    {
    	iLog->Log(_L8("Passed..")) ; 
    }
    else
    {
    	returnCode = KErrGeneral ;
    	iLog->Log(_L8("Failed.. @TRAPD")) ;    	
    }
        
    delete ipData ;
    delete CoreObj ;
     
    __UHEAP_MARKEND ;
    return returnCode ;
    

    }
    

// -----------------------------------------------------------------------------
// Ctsysdisplay::DisplayResolution
// Tests DisplayResolution values
// -----------------------------------------------------------------------------
//
TInt Ctsysdisplay::DisplayResolution( CStifItemParser& /*aItem*/ )
    {

   __UHEAP_MARK;
    
    _LIT(KEntity,"Display") ;
    _LIT(KKey,"DisplayResolution") ;
    
    TInt returnCode = KErrNone ;
    TInt expDataType = 10 ;
    
    CSysInfoService *CoreObj = CSysInfoService :: NewL() ;
    
    if( NULL == CoreObj)
	    {
	    iLog->Log(_L8("Failed.. @Core")) ;
	   	return KErrGeneral ;
	   	}
    
 //   CSysAttribute *attrib = CSysAttribute::NewL(KEntity,KKey) ;
 //   TSysRequest sysReq(attrib) ;
    CSysData *sysData ;
   	
    //iLog->Log(_L8("expTimeOut : %d"),expTimeOut) ;
       
    TRAPD(leaveCode, CoreObj->GetInfoL(KEntity,KKey,sysData) );
    
    if(KErrNone == leaveCode)
    {
        
    TInt retType = sysData->DataType() ;
    
    if(expDataType == retType)
	    {
	      
	    CResolution *resol = (CResolution*)sysData ;
	    TInt resolX = resol->XPixels() ;
        TInt resolY = resol->YPixels() ;
	    if(resolX && resolY) 
	    	{
	       	iLog->Log(_L8("X-Resolution : %d"),resolX) ;
	       	iLog->Log(_L8("Y-Resolution : %d"),resolY) ;
	       	iLog->Log(_L8("Passed..")) ; 
	        }
	   	else
	   		{
	   		returnCode = KErrGeneral ; 
	    	iLog->Log(_L8("Failed.. @resolution")) ;
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
    
//    delete attrib ;
    
    __UHEAP_MARKEND ;
    return returnCode ;
    

    }
  
  
// -----------------------------------------------------------------------------
// Ctsysdisplay::DisplayOrientation
// Tests DisplayOrientation values
// -----------------------------------------------------------------------------
//
TInt Ctsysdisplay::DisplayOrientation( CStifItemParser& aItem )
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
    
//    CSysAttribute *attrib = CSysAttribute::NewL(KEntity,KKey) ;
//    TSysRequest sysReq(attrib) ;
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
	    iLog->Log(_L8("Passed..")) ;
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
    	iLog->Log(_L8("Failed.. @TRAPD: %d"),leaveCode) ;
    	}
    delete CoreObj ;
    
//    delete attrib ;
    
    __UHEAP_MARKEND ;
    return returnCode ;
    

    }
    


// -----------------------------------------------------------------------------
// Ctsysdisplay::WrongKey
// Tests WrongKey values
// -----------------------------------------------------------------------------
//
TInt Ctsysdisplay::WrongKey( CStifItemParser&/* aItem */)
    {

   __UHEAP_MARK;
    
    _LIT(KEntity,"Display") ;
    _LIT(KKey,"WrongKey") ;
    
    TInt returnCode = KErrNone ;
        
    CSysInfoService *CoreObj = CSysInfoService :: NewL() ;
    
    if( NULL == CoreObj)
	    {
	    iLog->Log(_L8("Failed.. @Core")) ;
	   	return KErrGeneral ;
	   	}

    CSysData *sysData ;
    
    TRAPD(leaveCode, CoreObj->GetInfoL(KEntity,KKey,sysData)) ;
    
    if(KErrNotFound == leaveCode)
    	{
    	iLog->Log(_L8("Passed..")) ;
    	}
	else
		{
		returnCode = KErrGeneral ;	
		iLog->Log(_L8("Failed..")) ;
		}    
    
    delete CoreObj ;
 
    __UHEAP_MARKEND ;
    return returnCode ;
    

    }  


// -----------------------------------------------------------------------------
// Ctsysdisplay::SetWrongDataType
// Tests SetWrongDataType
// -----------------------------------------------------------------------------
//
TInt Ctsysdisplay::SetWrongDataType( CStifItemParser& /*aItem*/ )
    {

   __UHEAP_MARK;
    
    _LIT(KEntity,"Display") ;
    _LIT(KKey,"ScreenSaverTimeOut") ;
    
    TInt returnCode = KErrNone ;
   
    CSysInfoService *CoreObj = CSysInfoService :: NewL() ;
    
    if( NULL == CoreObj)
	    {
	    iLog->Log(_L8("Failed.. @Core")) ;
	   	return KErrGeneral ;
	   	}
    
	CStringData *ipData = CStringData::NewL(KEntity) ;
    
    TRAPD(leaveCode, CoreObj->SetInfoL(KEntity,KKey,ipData)) ;
    
    if(KErrArgument != leaveCode)
	    {
	   	returnCode = KErrGeneral ;
    	iLog->Log(_L8("Failed.. @TRAPD")) ;
    	}
    else
    	{
    	iLog->Log(_L8("Passed..")) ;
    	}
    
    delete ipData ;
    delete CoreObj ;
    
   
    __UHEAP_MARKEND ;
    return returnCode ;
    

    }


// -----------------------------------------------------------------------------
// Ctsysdisplay::UserActGetAsync
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctsysdisplay::UserActGetAsync( CStifItemParser& /*aItem*/ )
    {
   	TInt Err = KErrNone ;
   	TInt returnCode = KErrNone ;
	
	__UHEAP_MARK;

	CDisplayNot *test = CDisplayNot::NewL(iLog, 0);
	test->Start();
	Err = test->Result();
	delete test;
   
    if(KErrNotSupported != Err)
    returnCode = KErrGeneral ; 
   
	__UHEAP_MARKEND;
	return returnCode ;

    
    }   

 
 // -----------------------------------------------------------------------------
// Ctsysdisplay::UserActNotWithWrongIp
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctsysdisplay::UserActNotWithWrongIp( CStifItemParser& /*aItem*/ )
    {
   	TInt Err = KErrNone ;
   	TInt returnCode = KErrNone ;
	
	__UHEAP_MARK;

	CDisplayNot *test = CDisplayNot::NewL(iLog, 1);
	test->Start();
	Err = test->Result();
	delete test;
   
    if(KErrArgument != Err)
    returnCode = KErrGeneral ; 
   
	__UHEAP_MARKEND;
	return returnCode ;

    
    }      
    
// -----------------------------------------------------------------------------
// Ctsysdisplay::UserActNotWithWrongKey
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctsysdisplay::UserActNotWithWrongKey( CStifItemParser& /*aItem*/ )
    {
   	TInt Err = KErrNone ;
   	TInt returnCode = KErrNone ;
	
	__UHEAP_MARK;

	CDisplayNot *test = CDisplayNot::NewL(iLog, 2);
	test->Start();
	Err = test->Result();
	delete test;
   
    if(KErrNotFound != Err)
    returnCode = KErrGeneral ; 
   
	__UHEAP_MARKEND;
	return returnCode ;

    
    }      
// -----------------------------------------------------------------------------
// Ctsysdisplay::?member_function
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
/*
TInt Ctsysdisplay::?member_function(
   CItemParser& aItem )
   {

   ?code

   }
*/

// ========================== OTHER EXPORTED FUNCTIONS =========================
// None

//  End of File
