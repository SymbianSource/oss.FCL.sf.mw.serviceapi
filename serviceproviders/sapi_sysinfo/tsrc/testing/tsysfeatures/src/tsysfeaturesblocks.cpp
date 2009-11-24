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
* Description:   Tests phone features
*
*/




// INCLUDE FILES
#include <e32svr.h>
#include <StifParser.h>
#include <StifTestInterface.h>
#include "tsysfeatures.h"
#include "entitykeys.h"

using namespace SysInfo;

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
// Ctsysfeatures::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void Ctsysfeatures::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// Ctsysfeatures::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt Ctsysfeatures::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "BlueTooth", Ctsysfeatures::BlueTooth ),
        ENTRY( "InfraRed", Ctsysfeatures::InfraRed ),
        ENTRY( "Camera", Ctsysfeatures::Camera ),
        ENTRY( "MemoryCard", Ctsysfeatures::MemoryCard ),
        ENTRY( "FMRadio", Ctsysfeatures::FMRadio ),
        ENTRY( "Qwerty", Ctsysfeatures::Qwerty ),
        ENTRY( "WLan", Ctsysfeatures::WLan ),
        ENTRY( "Usb", Ctsysfeatures::Usb ),
        ENTRY( "Pen", Ctsysfeatures::Pen ),
        ENTRY( "LED", Ctsysfeatures::LED ),
        ENTRY( "CoverUI", Ctsysfeatures::CoverUI ),
        ENTRY( "SideVolumeKeys", Ctsysfeatures::SideVolumeKeys ),
        ENTRY( "Vibra", Ctsysfeatures::Vibra ),
        ENTRY( "WrongKey", Ctsysfeatures::WrongKey ),


        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// Ctsysfeatures::BlueTooth
// Test method for checking Bluetooth feature
// -----------------------------------------------------------------------------
//
TInt Ctsysfeatures::BlueTooth( CStifItemParser& /*aItem*/ )
    {

    __UHEAP_MARK;
    
    _LIT(KEntity,"Features") ;
    _LIT(KKey,"BlueTooth") ;
    
    TInt returnCode = KErrNone ;
    TInt expState = 0;
    TInt expDataType = 0 ;
    expState = FeatSupportInfo(KKey) ;
    
    CSysInfoService *CoreObj = CSysInfoService :: NewL() ;
    
    if( NULL == CoreObj)
	    {
	    iLog->Log(_L8("Failed.. @Core")) ;
	   	return KErrGeneral ;
	   	}

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
// Ctsysfeatures::InfraRed
// Test method for checking InfraRed feature
// -----------------------------------------------------------------------------
//
TInt Ctsysfeatures::InfraRed( CStifItemParser& /*aItem*/ )
    {

    __UHEAP_MARK;
    
    _LIT(KEntity,"Features") ;
    _LIT(KKey,"InfraRed") ;
    
    TInt returnCode = KErrNone ;
    TInt expState = 0;
    TInt expDataType = 0 ;
    expState = FeatSupportInfo(KKey) ;
    
    CSysInfoService *CoreObj = CSysInfoService :: NewL() ;
    
    if( NULL == CoreObj)
	    {
	    iLog->Log(_L8("Failed.. @Core")) ;
	   	return KErrGeneral ;
	   	}
    
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
// Ctsysfeatures::Camera
// Test method for checking Camera feature
// -----------------------------------------------------------------------------
//
TInt Ctsysfeatures::Camera( CStifItemParser& /*aItem*/ )
    {

    __UHEAP_MARK;
    
    _LIT(KEntity,"Features") ;
    _LIT(KKey,"Camera") ;
    
    TInt returnCode = KErrNone ;
    TInt expState = 0;
    TInt expDataType = 0 ;
    expState = FeatSupportInfo(KKey) ;
    
    CSysInfoService *CoreObj = CSysInfoService :: NewL() ;
    
    if( NULL == CoreObj)
	    {
	    iLog->Log(_L8("Failed.. @Core")) ;
	   	return KErrGeneral ;
	   	}
    
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
// Ctsysfeatures::MemoryCard
// Test method for checking MemoryCard feature
// -----------------------------------------------------------------------------
//
TInt Ctsysfeatures::MemoryCard( CStifItemParser& /*aItem*/ )
    {

    __UHEAP_MARK;
    
    _LIT(KEntity,"Features") ;
    _LIT(KKey,"MemoryCard") ;
    
    TInt returnCode = KErrNone ;
    TInt expState = 0;
    TInt expDataType = 0 ;
    expState = FeatSupportInfo(KKey) ;
    
    CSysInfoService *CoreObj = CSysInfoService :: NewL() ;
    
    if( NULL == CoreObj)
	    {
	    iLog->Log(_L8("Failed.. @Core")) ;
	   	return KErrGeneral ;
	   	}
 
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
// Ctsysfeatures::FMRadio
// Test method for checking FMRadio feature
// -----------------------------------------------------------------------------
//
TInt Ctsysfeatures::FMRadio( CStifItemParser& /*aItem*/ )
    {

    __UHEAP_MARK;
    
    _LIT(KEntity,"Features") ;
    _LIT(KKey,"FMRadio") ;
    
    TInt returnCode = KErrNone ;
    TInt expState = 0;
    TInt expDataType = 0 ;
    expState = FeatSupportInfo(KKey) ;
    
    CSysInfoService *CoreObj = CSysInfoService :: NewL() ;
    
    if( NULL == CoreObj)
	    {
	    iLog->Log(_L8("Failed.. @Core")) ;
	   	return KErrGeneral ;
	   	}
 
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
// Ctsysfeatures::Qwerty
// Test method for checking Qwerty feature
// -----------------------------------------------------------------------------
//
TInt Ctsysfeatures::Qwerty( CStifItemParser& /*aItem*/ )
    {

    __UHEAP_MARK;
    
    _LIT(KEntity,"Features") ;
    _LIT(KKey,"Qwerty") ;
    
    TInt returnCode = KErrNone ;
    TInt expState = 0;
    TInt expDataType = 0 ;
    expState = FeatSupportInfo(KKey) ;
    
    CSysInfoService *CoreObj = CSysInfoService :: NewL() ;
    
    if( NULL == CoreObj)
	    {
	    iLog->Log(_L8("Failed.. @Core")) ;
	   	return KErrGeneral ;
	   	}

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
// Ctsysfeatures::WLan
// Test method for checking WLan feature
// -----------------------------------------------------------------------------
//
TInt Ctsysfeatures::WLan( CStifItemParser& /*aItem*/ )
    {

    __UHEAP_MARK;
    
    _LIT(KEntity,"Features") ;
    _LIT(KKey,"WLan") ;
    
    TInt returnCode = KErrNone ;
    TInt expState = 0;
    TInt expDataType = 0 ;
    expState = FeatSupportInfo(KKey) ;
    
    CSysInfoService *CoreObj = CSysInfoService :: NewL() ;
    
    if( NULL == CoreObj)
	    {
	    iLog->Log(_L8("Failed.. @Core")) ;
	   	return KErrGeneral ;
	   	}
 
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
// Ctsysfeatures::Usb
// Test method for checking Usb feature
// -----------------------------------------------------------------------------
//
TInt Ctsysfeatures::Usb( CStifItemParser& /*aItem*/ )
    {

    __UHEAP_MARK;
    
    _LIT(KEntity,"Features") ;
    _LIT(KKey,"Usb") ;
    
    TInt returnCode = KErrNone ;
    TInt expState = 0;
    TInt expDataType = 0 ;
    expState = FeatSupportInfo(KKey) ;
    
    CSysInfoService *CoreObj = CSysInfoService :: NewL() ;
    
    if( NULL == CoreObj)
	    {
	    iLog->Log(_L8("Failed.. @Core")) ;
	   	return KErrGeneral ;
	   	}
    
 
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
// Ctsysfeatures::Pen
// Test method for checking Pen feature
// -----------------------------------------------------------------------------
//
TInt Ctsysfeatures::Pen( CStifItemParser& /*aItem*/ )
    {

    __UHEAP_MARK;
    
    _LIT(KEntity,"Features") ;
    _LIT(KKey,"Pen") ;
    
    TInt returnCode = KErrNone ;
    TInt expState = 0;
    TInt expDataType = 0 ;
    expState = FeatSupportInfo(KKey) ;
    
    CSysInfoService *CoreObj = CSysInfoService :: NewL() ;
    
    if( NULL == CoreObj)
	    {
	    iLog->Log(_L8("Failed.. @Core")) ;
	   	return KErrGeneral ;
	   	}
    
 
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
// Ctsysfeatures::LED
// Test method for checking LED feature
// -----------------------------------------------------------------------------
//
TInt Ctsysfeatures::LED( CStifItemParser& /*aItem*/ )
    {

    __UHEAP_MARK;
    
    _LIT(KEntity,"Features") ;
    _LIT(KKey,"LED") ;
    
    TInt returnCode = KErrNone ;
    TInt expState = 0;
    TInt expDataType = 0 ;
    expState = FeatSupportInfo(KKey) ;
    
    CSysInfoService *CoreObj = CSysInfoService :: NewL() ;
    
    if( NULL == CoreObj)
	    {
	    iLog->Log(_L8("Failed.. @Core")) ;
	   	return KErrGeneral ;
	   	}

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
// Ctsysfeatures::CoverUI
// Test method for checking CoverUI feature
// -----------------------------------------------------------------------------
//
TInt Ctsysfeatures::CoverUI( CStifItemParser& /*aItem*/ )
    {

    __UHEAP_MARK;
    
    _LIT(KEntity,"Features") ;
    _LIT(KKey,"CoverUI") ;
    
    TInt returnCode = KErrNone ;
    TInt expState = 0;
    TInt expDataType = 0 ;
    expState = FeatSupportInfo(KKey) ;
    
    CSysInfoService *CoreObj = CSysInfoService :: NewL() ;
    
    if( NULL == CoreObj)
	    {
	    iLog->Log(_L8("Failed.. @Core")) ;
	   	return KErrGeneral ;
	   	}
    
 //   CSysAttribute *attrib = CSysAttribute::NewL(KEntity,KKey) ;
 //   TSysRequest sysReq(attrib) ;
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
// Ctsysfeatures::SideVolumeKeys
// Test method for checking SideVolumeKeys feature
// -----------------------------------------------------------------------------
//
TInt Ctsysfeatures::SideVolumeKeys( CStifItemParser& /*aItem*/ )
    {

    __UHEAP_MARK;
    
    _LIT(KEntity,"Features") ;
    _LIT(KKey,"SideVolumeKeys") ;
    
    TInt returnCode = KErrNone ;
    TInt expState = 0;
    TInt expDataType = 0 ;
    expState = FeatSupportInfo(KKey) ;
    
    CSysInfoService *CoreObj = CSysInfoService :: NewL() ;
    
    if( NULL == CoreObj)
	    {
	    iLog->Log(_L8("Failed.. @Core")) ;
	   	return KErrGeneral ;
	   	}
    
 
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
// Ctsysfeatures::Vibra
// Test method for checking Vibra feature
// -----------------------------------------------------------------------------
//
TInt Ctsysfeatures::Vibra( CStifItemParser& /*aItem*/ )
    {

    __UHEAP_MARK;
    
    _LIT(KEntity,"Features") ;
    _LIT(KKey,"Vibra") ;
    
    TInt returnCode = KErrNone ;
    TInt expState = 0;
    TInt expDataType = 0 ;
    expState = FeatSupportInfo(KKey) ;
    
    CSysInfoService *CoreObj = CSysInfoService :: NewL() ;
    
    if( NULL == CoreObj)
	    {
	    iLog->Log(_L8("Failed.. @Core")) ;
	   	return KErrGeneral ;
	   	}
 
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
// Ctsysfeatures::WrongKey
// Test for wrong key input values
// -----------------------------------------------------------------------------
//
TInt Ctsysfeatures::WrongKey( CStifItemParser& /*aItem*/ )
    {

     __UHEAP_MARK;
    
    _LIT(KEntity,"Features") ;
    _LIT(KKey,"StatusCharging") ;
    
    TInt returnCode = KErrNone ;
        
    CSysInfoService *CoreObj = CSysInfoService :: NewL() ;
    
    if( NULL == CoreObj)
	    {
	    iLog->Log(_L8("Failed.. @Core")) ;
	   	return KErrGeneral ;
	   	}
    
 //   CSysAttribute *attrib = CSysAttribute::NewL(KEntity,KKey) ;
 //   TSysRequest sysReq(attrib) ;
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
  //  delete sysData ;
 //   delete attrib ;
    
    __UHEAP_MARKEND ;
    return returnCode ;
    
    }



// -----------------------------------------------------------------------------
// Ctsysfeatures::WrongKey
// Test for wrong key input values
// -----------------------------------------------------------------------------
//
TInt Ctsysfeatures::FeatSupportInfo( const TDesC& aFeature )
    {
	
	TInt featureID = 0 ;
	
	if( !aFeature.CompareF(KBlueTooth) )
		featureID = KFeatureIdBt;
	else if( !aFeature.CompareF(KInfraRed) )
		featureID = KFeatureIdIrda;
	else if( !aFeature.CompareF(KCamera) )
		featureID = KFeatureIdCamera;
	else if( !aFeature.CompareF(KMemoryCard) )
		featureID = KFeatureIdMmc;
	else if( !aFeature.CompareF(KFMRadio) )
		featureID = KFeatureIdFmRadio;
	else if( !aFeature.CompareF(KQwerty) )
		featureID = KFeatureIdQwertyInput;
	else if( !aFeature.CompareF(KWLan) )
		featureID = KFeatureIdProtocolWlan;
	else if( !aFeature.CompareF(KUsb) )
		featureID = KFeatureIdUsb;
	else if( !aFeature.CompareF(KPen) )
		featureID = KFeatureIdPenSupport;
	else if( !aFeature.CompareF(KLED) )
		featureID = KFeatureIdPenSupport;
	else if( !aFeature.CompareF(KCoverUI) )
		featureID = KFeatureIdCoverDisplay;
	else if( !aFeature.CompareF(KSideVolumeKeys) )
		featureID = KFeatureIdSideVolumeKeys;
	else if( !aFeature.CompareF(KVibra) )
		featureID = KFeatureIdVibra;
	else
		User::Leave(KErrNotFound);
	
	return(FeatureManager::FeatureSupported(featureID));
    }
// -----------------------------------------------------------------------------
// Ctsysfeatures::?member_function
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
/*
TInt Ctsysfeatures::?member_function(
   CItemParser& aItem )
   {

   ?code

   }
*/

// ========================== OTHER EXPORTED FUNCTIONS =========================
// None

//  End of File
