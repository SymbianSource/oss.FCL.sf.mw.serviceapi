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
* Description:   Tests sysinfo network information
*
*/




// INCLUDE FILES
#include <e32svr.h>
#include <StifParser.h>
#include <Stiftestinterface.h>
#include "tsysnetwork.h"

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
// Ctsysnetwork::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void Ctsysnetwork::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// Ctsysnetwork::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt Ctsysnetwork::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "RegStatus", Ctsysnetwork::RegStatus ),
        ENTRY( "NetworkMode", Ctsysnetwork::NetworkMode),
        ENTRY( "WrongEntity", Ctsysnetwork::WrongEntity),
        ENTRY( "WrongKey", Ctsysnetwork::WrongKey),
        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// Ctsysnetwork::RegStatus
// Test for getting the registration status
// -----------------------------------------------------------------------------
//
TInt Ctsysnetwork::RegStatus( CStifItemParser& aItem )
    {

     __UHEAP_MARK;
    
    _LIT(KEntity,"Network") ;
    _LIT(KKey,"RegistrationStatus") ;
    
    TPtrC entity(KEntity) ;
    TPtrC key(KKey) ;
    
    TInt returnCode = KErrNone ;
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
   	
   	
    iLog->Log(_L8("ExpStatus : %d"),expStatus) ;
    
    TRAPD(leaveCode, CoreObj->GetInfoL(entity,key,sysData) );
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
	    	iLog->Log(_L8("Failed.. @retStatus: %d"),retStatus) ;
	    	}
	   	else
	   		{
	   		iLog->Log(_L8("Passed..")) ; 	
	   		}
	   	  
	    }
	    
	else
		{
		returnCode = KErrGeneral ;	
		iLog->Log(_L8("Failed.. @retType %d"),retType) ;
		}    
    
    delete sysData ;
    
    }
    else
    	{
    	returnCode = KErrGeneral ; 
    	iLog->Log(_L8("Failed.. @TRAPD %d"),leaveCode) ;
    	}
    delete CoreObj ;
    
    #endif
        
    __UHEAP_MARKEND ;
    return returnCode ;
    
    }


// -----------------------------------------------------------------------------
// Ctsysnetwork::NetworkMode
// Test for getting the Network Mode
// -----------------------------------------------------------------------------
//
TInt Ctsysnetwork::NetworkMode( CStifItemParser& aItem )
    {

     __UHEAP_MARK;
    
    _LIT(KEntity,"Network") ;
    _LIT(KKey,"NetworkMode") ;
    
    TPtrC entity(KEntity) ;
    TPtrC key(KKey) ;
    
    _LIT8(KTest,"Network") ;
   /* TBuf8<32> eightBuf(KTest) ;
    TBuf16<32> sixteenBuf ;
    sixteenBuf.Copy(eightBuf) ;
    
    TPtrC copyPtr(sixteenBuf) ;
    TPtrC tobeCompPtr(sixteenBuf) ;
    copyPtr.Compare(tobeCompPtr) ;
   */ 
    TInt returnCode = KErrNone ;
    TInt expStatus = 0 ;
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
   	
   	
    iLog->Log(_L8("NetworkMode ExpStatus: %d"),expStatus) ;	
    TRAPD(leaveCode, CoreObj->GetInfoL(entity,key,sysData)) ;
    if(KErrNone == leaveCode)
	    {
	       
	    TInt retType = sysData->DataType() ;
	    
	    if(expDataType == retType)
		    {
		      
		    CStatus *status = (CStatus*)sysData ;
		    TInt retStatus = status->Status() ;

	    	iLog->Log(_L8("Passed.. @retStatus %d"),retStatus) ;
		     }
		    
		else
			{
			returnCode = KErrGeneral ;	
			iLog->Log(_L8("Failed.. @retType: %d"),retType);
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
// Ctsysnetwork::WrongEntity
// Test for wrong Entity input values
// -----------------------------------------------------------------------------
//
TInt Ctsysnetwork::WrongEntity( CStifItemParser& /*aItem*/ )
    {

     __UHEAP_MARK;
    
    _LIT(KEntity,"Networkk") ;
    _LIT(KKey,"NetworkMode") ;
    
    TPtrC entity(KEntity) ;
    TPtrC key(KKey) ;
    
    TInt returnCode = KErrNone ;
     
    CSysInfoService *CoreObj = CSysInfoService :: NewL() ;
    
    if( NULL == CoreObj)
	    {
	    iLog->Log(_L8("Failed.. @Core")) ;
	   	return KErrGeneral ;
	   	}
    
    CSysData *sysData ;
   	
   	iLog->Log(_L8("b4..")) ;
        
    TRAPD(leaveCode, CoreObj->GetInfoL(entity,key,sysData)) ;
    
    iLog->Log(_L8("af..")) ;
    
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
// Ctsysnetwork::WrongKey
// Test for wrong key input values
// -----------------------------------------------------------------------------
//
TInt Ctsysnetwork::WrongKey( CStifItemParser& /*aItem*/ )
    {

     __UHEAP_MARK;
    
    _LIT(KEntity,"Network") ;
    _LIT(KKey,"NetworkModde") ;
    
    TPtrC entity(KEntity) ;
    TPtrC key(KKey) ;
    
    TInt returnCode = KErrNone ;
        
    CSysInfoService *CoreObj = CSysInfoService :: NewL() ;
    
    if( NULL == CoreObj)
	    {
	    iLog->Log(_L8("Failed.. @Core")) ;
	   	return KErrGeneral ;
	   	}
    

    CSysData *sysData ;
   	
   	
    iLog->Log(_L8("b4..")) ;
    TRAPD(leaveCode, CoreObj->GetInfoL(entity,key,sysData)) ;
    iLog->Log(_L8("af..")) ;
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
// Ctsysnetwork::?member_function
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
/*
TInt Ctsysnetwork::?member_function(
   CItemParser& aItem )
   {

   ?code

   }
*/

// ========================== OTHER EXPORTED FUNCTIONS =========================
// None

//  End of File
