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
* Description:   Tests device information
*
*/




// INCLUDE FILES
#include <e32svr.h>
#include <StifParser.h>
#include <StifTestInterface.h>
#include "tsysdevice.h"
#include <sysutil.h>

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
// Ctsysdevice::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void Ctsysdevice::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// Ctsysdevice::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt Ctsysdevice::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "FirmwareVersion", Ctsysdevice::FirmwareVersion ),
        ENTRY( "ProductType", Ctsysdevice::ProductType ),
        ENTRY( "Manufacturer", Ctsysdevice::Manufacturer ),
        ENTRY( "PhoneModel", Ctsysdevice::PhoneModel ),
		ENTRY( "IMEI", Ctsysdevice::IMEI ),
		ENTRY( "MachineID", Ctsysdevice::MachineID ),
		ENTRY( "PlatformVersion", Ctsysdevice::PlatformVersion ),
        ENTRY( "SymbianOsVersion", Ctsysdevice::SymbianOsVersion ),
        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// Ctsysdevice::FirmwareVersion
// Tests FirmwareVersion functionlity
// -----------------------------------------------------------------------------
//
TInt Ctsysdevice::FirmwareVersion( CStifItemParser& /*aItem*/ )
    {

    __UHEAP_MARK;
    
    _LIT(KEntity,"Device") ;
    _LIT(KKey,"FirmwareVersion") ;
    
    
    TInt returnCode = KErrNone ;
    TInt expDataType = 12 ;
        
    CSysInfoService *CoreObj = CSysInfoService :: NewL() ;
    
    if( NULL == CoreObj)
	    {
	    iLog->Log(_L8("Failed.. @Core")) ;
	   	return KErrGeneral ;
	   	}
    
 	CSysData *sysData ;
     
    TRAPD(leaveCode, CoreObj->GetInfoL(KEntity, KKey, sysData) );
    
    if(KErrNone == leaveCode)
    {
        
    TInt retType = sysData->DataType() ;
    
    if(expDataType == retType)
	    {
	      
	    CStringData *status = (CStringData*)sysData ;
	    TPtrC firmVersion ;
	    status->StringData(firmVersion) ;
   	   	if((firmVersion.Length()) > 0)
   	   		{
   	   		TBuf<KSysUtilVersionTextLength> firmVersionBuf(firmVersion) ;
   	   		iLog->Log(_L8("Firmware version")) ;
   	   		iLog->Log(firmVersionBuf) ;
   	   		}
	    else
	    	{
	    	returnCode = KErrGeneral ;
	    	iLog->Log(_L8("Firmware version wrong"));
	    	}
	    }
	    
	else
		{
		returnCode = KErrGeneral ;	
		iLog->Log(_L8("Failed.. @retType")) ;
		}    
    }
    else
    	{
    	iLog->Log(_L8("Failed.. @TRAPD")) ;
    	}
    delete CoreObj ;
    delete sysData ;
    
    __UHEAP_MARKEND ;
    return returnCode ;
   
    }


// -----------------------------------------------------------------------------
// Ctsysdevice::ProductType
// Tests ProductType functionlity
// -----------------------------------------------------------------------------
//
TInt Ctsysdevice::ProductType( CStifItemParser& /*aItem*/ )
    {

    __UHEAP_MARK;
    
    _LIT(KEntity,"Device") ;
    _LIT(KKey,"ProductType") ;
    
    
    TInt returnCode = KErrNone ;
    TInt expDataType = 12 ;
        
    CSysInfoService *CoreObj = CSysInfoService :: NewL() ;
    
    if( NULL == CoreObj)
	    {
	    iLog->Log(_L8("Failed.. @Core")) ;
	   	return KErrGeneral ;
	   	}
 
    CSysData *sysData ;
      
    TRAPD(leaveCode, CoreObj->GetInfoL(KEntity, KKey, sysData) );
    
    if(KErrNone == leaveCode)
    {
        
    TInt retType = sysData->DataType() ;
    
    if(expDataType == retType)
	    {
	    #if ( !((defined(__WINS__) || defined(__WINSCW__))) )
	    CStringData *status = (CStringData*)sysData ;
	    TPtrC prdType ;
	    status->StringData(prdType) ;
   	   	
   	   	if((prdType.Length()) > 0)
	   	   	{
	   	   	TBuf<50> prdTypeBuf(prdType) ;
	   	   	iLog->Log(_L8("Product Type ")) ;
	        iLog->Log(prdTypeBuf) ;
		    }
	   else
	   		{
	   		returnCode = KErrGeneral ;
	   		iLog->Log(_L8("Failed..@wrong prdType")) ;
	   		} 
		#endif
	    }
	    
	else
		{
		returnCode = KErrGeneral ;	
		iLog->Log(_L8("Failed.. @retType")) ;
		}    
    }
    else
    	{
    	iLog->Log(_L8("Failed.. @TRAPD")) ;
    	}
    delete CoreObj ;
    delete sysData ;
    
    __UHEAP_MARKEND ;
    return returnCode ;
   
    }




// -----------------------------------------------------------------------------
// Ctsysdevice::Manufacturer
// Tests Manufacturer functionlity
// -----------------------------------------------------------------------------
//
TInt Ctsysdevice::Manufacturer( CStifItemParser& /*aItem*/ )
    {

    __UHEAP_MARK;
    
    _LIT(KEntity,"Device") ;
    _LIT(KKey,"Manufacturer") ;
    
    
    TInt returnCode = KErrNone ;
    TInt expDataType = 12 ;
        
    CSysInfoService *CoreObj = CSysInfoService :: NewL() ;
    
    if( NULL == CoreObj)
	    {
	    iLog->Log(_L8("Failed.. @Core")) ;
	   	return KErrGeneral ;
	   	}

    CSysData *sysData ;
      
    TRAPD(leaveCode, CoreObj->GetInfoL(KEntity, KKey, sysData) );
    
    if(KErrNone == leaveCode)
	    {
	        
	    TInt retType = sysData->DataType() ;
	    
	    if(expDataType == retType)
		    {
		      
		    #if ( !((defined(__WINS__) || defined(__WINSCW__))) )
		    _LIT(expMfg,"NOKIA") ;
		    
		    #else
		    _LIT(expMfg,"PHONEMAKER") ; 
		    
		    #endif
		    
		    CStringData *status = (CStringData*)sysData ;
		    TPtrC  manufacturer ;
		    status->StringData(manufacturer) ;
	   	   	
	   	   	TBuf<50> mfdBuf(manufacturer) ;
	   	   	mfdBuf.UpperCase();
			
			if( !(mfdBuf.Compare(expMfg) ))
				{
				
		   	   	iLog->Log(_L8("Manufacturer")) ;
		        iLog->Log(mfdBuf) ;
				}
		    else
		    	{
		    	returnCode = KErrGeneral ;
		    	iLog->Log(_L8("Wrong manufacturere ret..")) ;
		    	}
		    }
		    
		else
			{
			returnCode = KErrGeneral ;	
			iLog->Log(_L8("Failed.. @retType")) ;
			}    
	    }
    else
    	{
    	iLog->Log(_L8("Failed.. @TRAPD")) ;
    	}
    delete CoreObj ;
    delete sysData ;

    __UHEAP_MARKEND ;
    return returnCode ;
   
    }




// -----------------------------------------------------------------------------
// Ctsysdevice::PhoneModel
// Tests PhoneModel functionlity
// -----------------------------------------------------------------------------
//
TInt Ctsysdevice::PhoneModel( CStifItemParser& /*aItem*/ )
    {

    __UHEAP_MARK;
    
    _LIT(KEntity,"Device") ;
    _LIT(KKey,"PhoneModel") ;
    
    
    TInt returnCode = KErrNone ;
    TInt expDataType = 12 ;
        
    CSysInfoService *CoreObj = CSysInfoService :: NewL() ;
    
    if( NULL == CoreObj)
	    {
	    iLog->Log(_L8("Failed.. @Core")) ;
	   	return KErrGeneral ;
	   	}
 
    CSysData *sysData ;
   	
   	
       
    TRAPD(leaveCode, CoreObj->GetInfoL(KEntity, KKey, sysData) );
    
    if(KErrNone == leaveCode)
    {
        
    TInt retType = sysData->DataType() ;
    
    if(expDataType == retType)
	    {
	      
	    CStringData *status = (CStringData*)sysData ;
	    TPtrC  phonemodel ;
	   
	    status->StringData(phonemodel) ;
   	    
   	    if((phonemodel.Length()) > 0)
	   	   	{
	   	   	TBuf<50>  phonemodelBuf(phonemodel) ;
	   	   	iLog->Log(_L8("PhoneModel")) ;
	   	   	iLog->Log(phonemodelBuf) ;
		    }
	   else
	   		{
	   		returnCode = KErrGeneral ;
	   		iLog->Log(_L8("Failed..@wrong phonemodel")) ;
	   		} 
	    }
	    
	else
		{
		returnCode = KErrGeneral ;	
		iLog->Log(_L8("Failed.. @retType")) ;
		}    
    }
    else
    	{
    	iLog->Log(_L8("Failed.. @TRAPD")) ;
    	}
    delete CoreObj ;
    delete sysData ;
 
    __UHEAP_MARKEND ;
    return returnCode ;
   
    }



// -----------------------------------------------------------------------------
// Ctsysdevice::IMEI
// Tests IMEI functionlity
// -----------------------------------------------------------------------------
//
TInt Ctsysdevice::IMEI( CStifItemParser& /*aItem*/ )
    {

    __UHEAP_MARK;
    
    _LIT(KEntity,"Device") ;
    _LIT(KKey,"IMEI") ;
    
    
    TInt returnCode = KErrNone ;
    TInt expDataType = 12 ;
        
    CSysInfoService *CoreObj = CSysInfoService :: NewL() ;
    
    if( NULL == CoreObj)
	    {
	    iLog->Log(_L8("Failed.. @Core")) ;
	   	return KErrGeneral ;
	   	}

    CSysData *sysData ;
       
    TRAPD(leaveCode, CoreObj->GetInfoL(KEntity, KKey, sysData) );
    
    if(KErrNone == leaveCode)
    {
        
    TInt retType = sysData->DataType() ;
    
    if(expDataType == retType)
	    {
	    #if ( !((defined(__WINS__) || defined(__WINSCW__))) )  
	    
	    CStringData *status = (CStringData*)sysData ;
	    TPtrC  imei ;
	    status->StringData(imei) ;
	    if((imei.Length()) >= 15)
		    {
		    TBuf<50> imeiBuf(imei) ;
	   	   	iLog->Log(_L8("IMEI") );
	   	   	iLog->Log(imeiBuf) ;
		    }
	    else
	    	{
	    	returnCode = KErrGeneral;
	    	iLog->Log(_L8("Wrong IMEI..")) ;
	    	}
	     #endif
	     }
	    
	else
		{
		returnCode = KErrGeneral ;	
		iLog->Log(_L8("Failed.. @retType")) ;
		}    
    }
    else
    	{
    	iLog->Log(_L8("Failed.. @TRAPD")) ;
    	}
    delete CoreObj ;
    delete sysData ;
  
    __UHEAP_MARKEND ;
    return returnCode ;
   
    }


// -----------------------------------------------------------------------------
// Ctsysdevice::MachineID
// Tests MachineID functionlity
// -----------------------------------------------------------------------------
//
TInt Ctsysdevice::MachineID( CStifItemParser& /*aItem*/ )
    {

    __UHEAP_MARK;
    
    _LIT(KEntity,"Device") ;
    _LIT(KKey,"MachineID") ;
    
    
    TInt returnCode = KErrNone ;
    TInt expDataType = 0 ;
        
    CSysInfoService *CoreObj = CSysInfoService :: NewL() ;
    
    if( NULL == CoreObj)
	    {
	    iLog->Log(_L8("Failed.. @Core")) ;
	   	return KErrGeneral ;
	   	}
    
    CSysData *sysData ;
  	
       
    TRAPD(leaveCode, CoreObj->GetInfoL(KEntity, KKey, sysData) );
    
    if(KErrNone == leaveCode)
    {
        
    TInt retType = sysData->DataType() ;
    
    if(expDataType == retType)
	    {
	    #if ( !((defined(__WINS__) || defined(__WINSCW__))) )   
	    
	    CStatus *status = (CStatus*)sysData ;
	    TInt  machineid ;
	    machineid = status->Status() ;
   	   	if(machineid > 0)
   	   		{
   	   		iLog->Log(_L8("machineid %d"),machineid) ;	
   	   		}
   	   	else
   	   		{
   	   		returnCode = KErrGeneral ;
   	   		iLog->Log(_L8("wrong machineid..")) ;
   	   		}
		#endif
	    
	    }
	    
	else
		{
		returnCode = KErrGeneral ;	
		iLog->Log(_L8("Failed.. @retType")) ;
		}    
    }
    else
    	{
    	iLog->Log(_L8("Failed.. @TRAPD")) ;
    	}
    delete CoreObj ;
    delete sysData ;

    __UHEAP_MARKEND ;
    return returnCode ;
   
    }
    
// -----------------------------------------------------------------------------
// Ctsysdevice::PlatformVersion
// Tests PlatformVersion functionlity
// -----------------------------------------------------------------------------
//
TInt Ctsysdevice::PlatformVersion( CStifItemParser& /*aItem*/ )
    {

    __UHEAP_MARK;
    
    _LIT(KEntity,"Device") ;
    _LIT(KKey,"PlatformVersion") ;
    
    
    TInt returnCode = KErrNone ;
    TInt expDataType = 1 ;
        
    CSysInfoService *CoreObj = CSysInfoService :: NewL() ;
    
    if( NULL == CoreObj)
	    {
	    iLog->Log(_L8("Failed.. @Core")) ;
	   	return KErrGeneral ;
	   	}
    
 
    CSysData *sysData ;
   	
       
    TRAPD(leaveCode, CoreObj->GetInfoL(KEntity, KKey, sysData) );
    
    if(KErrNone == leaveCode)
    {
        
    TInt retType = sysData->DataType() ;
    
    if(expDataType == retType)
	    {
	      
	    CVersion *status = (CVersion*)sysData ;
	    TInt  majorVersion ;
	    TInt  minorVersion ;
	    majorVersion = status->MajorVersion() ;
	    minorVersion = status->MinorVersion() ;
   	   	if((majorVersion > 0) && (minorVersion >= 0))
	   	   	{
	   	   	iLog->Log(_L8("MajorVersion %d"),majorVersion) ;
	   	  	iLog->Log(_L8("MinorVersion %d"),minorVersion) ;	
	   	   	}
   	   	else
   	   		{
   	   		returnCode = KErrGeneral ;
   	   		iLog->Log(_L8("Wrong s60 version..")) ;
   	   		}

	     }
	    
	else
		{
		returnCode = KErrGeneral ;	
		iLog->Log(_L8("Failed.. @retType")) ;
		}    
    }
    else
    	{
    	iLog->Log(_L8("Failed.. @TRAPD")) ;
    	}
    delete CoreObj ;
    delete sysData ;

    __UHEAP_MARKEND ;
    return returnCode ;
   
    }
    
// -----------------------------------------------------------------------------
// Ctsysdevice::SymbianOsVersion
// Tests SymbianOsVersion functionlity
// -----------------------------------------------------------------------------
//
TInt Ctsysdevice::SymbianOsVersion( CStifItemParser& /*aItem*/ )
    {

    __UHEAP_MARK;
    
    _LIT(KEntity,"Device") ;
    _LIT(KKey,"OsVersion") ;
    
    
    TInt returnCode = KErrNone ;
    TInt expDataType = 1 ;
        
    CSysInfoService *CoreObj = CSysInfoService :: NewL() ;
    
    if( NULL == CoreObj)
	    {
	    iLog->Log(_L8("Failed.. @Core")) ;
	   	return KErrGeneral ;
	   	}

    CSysData *sysData = NULL;
      
    TRAPD(leaveCode, CoreObj->GetInfoL(KEntity, KKey, sysData) );
    
    if(KErrNotFound == leaveCode)
    {
    	iLog->Log(_L8("Symbian OS Version Not Supported.."));
    	returnCode = KErrNone;
    }
	else if(KErrNone == leaveCode)
	{
	        
	    TInt retType = sysData->DataType() ;
	    
	    if(expDataType == retType)
		{
		    #if ( !((defined(__WINS__) || defined(__WINSCW__))) )     
		    CVersion *status = (CVersion*)sysData ;
		    TInt  majorVersion ;
		    TInt  minorVersion ;
		    majorVersion = status->MajorVersion() ;
		    minorVersion = status->MinorVersion() ;
	   	   
		  	if((majorVersion > 0) && (minorVersion >= 0))
		   	   	{
		   	   	iLog->Log(_L8("MajorVersion %d"),majorVersion) ;
		   	  	iLog->Log(_L8("MinorVersion %d"),minorVersion) ;	
		   	   	}
	   	   	else
	   	   		{
	   	   		returnCode = KErrGeneral ;
	   	   		iLog->Log(_L8("Wrong symbian os version..")) ;
	   	   		}
			#endif
		}
		    
		else
		{
			returnCode = KErrGeneral ;	
			iLog->Log(_L8("Failed.. @retType")) ;
		}    
	}
	else
	{
	   	iLog->Log(_L8("Failed.. @TRAPD")) ;
	}
    
    if(CoreObj)
    	delete CoreObj ;
    
    if(sysData)
    	delete sysData ;
 
     __UHEAP_MARKEND ;
    return returnCode ;
   
    }
// -----------------------------------------------------------------------------
// Ctsysdevice::?member_function
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
/*
TInt Ctsysdevice::?member_function(
   CItemParser& aItem )
   {

   ?code

   }
*/

// ========================== OTHER EXPORTED FUNCTIONS =========================
// None

//  End of File
