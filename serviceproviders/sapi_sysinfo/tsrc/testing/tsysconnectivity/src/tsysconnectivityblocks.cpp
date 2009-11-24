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
* Description:   Tests sysinfo connectivity information 
*
*/




// INCLUDE FILES
#include <e32svr.h>
#include <StifParser.h>
#include <StifTestInterface.h>


#include "tsysconnectivity.h"
#include "tsysconnectivitynot.h"

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
// Ctsysconnectivity::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void Ctsysconnectivity::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// Ctsysconnectivity::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt Ctsysconnectivity::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "SetAndGetBtState", Ctsysconnectivity::SetAndGetBtState ),
		ENTRY( "SetAndGetIRState", Ctsysconnectivity::SetAndGetIRState ),
		ENTRY( "WLanMACAdd", Ctsysconnectivity::WLanMACAdd ),
		ENTRY( "WrongKey", Ctsysconnectivity::WrongKey ),
		ENTRY( "SetWrongDataType", Ctsysconnectivity::SetWrongDataType ),
		ENTRY( "SetWrongKey", Ctsysconnectivity::SetWrongKey ),
        ENTRY( "ConnNotWithWrongKey", Ctsysconnectivity::ConnNotWithWrongKey ),
        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// Ctsysconnectivity::SetAndGetBtState
// Tests Bluetooth state
// -----------------------------------------------------------------------------
//
TInt Ctsysconnectivity::SetAndGetBtState( CStifItemParser& aItem )
    {

   __UHEAP_MARK;
    
    _LIT(KEntity,"Connectivity") ;
    _LIT(KKey,"BlueTooth") ;
    
    TInt returnCode = KErrNone ;
    TInt expState = 0;
    TInt expDataType = 0 ;
    TInt defValue = 0 ;
    aItem.GetNextInt ( expState ) ;
    
    CSysInfoService *CoreObj = CSysInfoService :: NewL() ;
    
    if( NULL == CoreObj)
	    {
	    iLog->Log(_L8("Failed.. @Core")) ;
	   	return KErrGeneral ;
	   	}
    
	iLog->Log(_L8("expState : %d"),expState) ;
    CStatus *ipData = CStatus::NewL(expState) ;
   	      
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
		   
			    if(expState != retStatus)
			    	{
			        returnCode = KErrGeneral ;
			        iLog->Log(_L8("retStatus : %d"),retStatus) ; 
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
// Ctsysconnectivity::SetAndGetIRState
// Tests Set and Get InfraRed state
// -----------------------------------------------------------------------------
//
TInt Ctsysconnectivity::SetAndGetIRState( CStifItemParser& aItem )
    {

   __UHEAP_MARK;
    
    _LIT(KEntity,"Connectivity") ;
    _LIT(KKey,"InfraRed") ;
    
    TInt returnCode = KErrNone ;
    TInt expState = 0;
    TInt expDataType = 0 ;
    TInt defValue = 0 ;
    aItem.GetNextInt ( expState ) ;
    
    CSysInfoService *CoreObj = CSysInfoService :: NewL() ;
    
    if( NULL == CoreObj)
	    {
	    iLog->Log(_L8("Failed.. @Core")) ;
	   	return KErrGeneral ;
	   	}
    
   CStatus *ipData = CStatus::NewL(expState) ;
   	      
   TRAPD(leaveCode, CoreObj->SetInfoL(KEntity,KKey,ipData)) ;
   
   /* 
   if(KErrNone == leaveCode) 
	   {
	    
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
// Ctsysconnectivity::WLanMACAdd
// Tests WLanMACAdd state
// -----------------------------------------------------------------------------
//
TInt Ctsysconnectivity::WLanMACAdd( CStifItemParser& /*aItem*/ )
    {

   __UHEAP_MARK;
    
    _LIT(KEntity1,"Features") ;
    _LIT(KKey1,"WLan") ;
    _LIT(KEntity2,"Connectivity") ;
    _LIT(KKey2,"WLanMacAddress") ;
    
    
    TInt returnCode = KErrNone ;
    
    #if (!(defined(__WINS__) || defined(__WINSCW__))) 
    
    TInt featureID = KFeatureIdProtocolWlan ;
    TInt expDataType = 12 ;
    TInt expLength = 17 ;
    TInt isWLanSupported = FeatureManager::FeatureSupported(featureID) ;
    
    if(isWLanSupported)
	    {
	    	
	    CSysInfoService *CoreObj = CSysInfoService :: NewL() ;
	    
	    if( NULL == CoreObj)
		    {
		    iLog->Log(_L8("Failed.. @Core")) ;
		   	return KErrGeneral ;
		   	}
	    

	    CSysData *sysData ;
	   	
	   	
	   	TRAPD(leaveCode, CoreObj->GetInfoL(KEntity1,KKey1,sysData) );
	    
	    if(KErrNone == leaveCode)
		    {
		    TInt IsSupported = ((CStatus*)sysData)->Status();
							
			if(IsSupported)	
		  	{
				
			TRAP(leaveCode, CoreObj->GetInfoL(KEntity2,KKey2,sysData) );
		    
		    if(KErrNone == leaveCode)
			    {
			    TInt retType = sysData->DataType() ;
			    
			    if(expDataType == retType)
				    {
				    CStringData *status = (CStringData*)sysData ;
				    TPtrC retAddress ;
				    status->StringData(retAddress) ;
			   
				    if(expLength != (retAddress.Length()))
				    	{
				        returnCode = KErrGeneral ; 
				    	iLog->Log(_L8("Failed.. @retStatus")) ;
				    	}
				   	else
				   		{
				   		iLog->Log(_L8("Passed..")) ; 	
				   		TBuf8<20> buf;
						buf.Copy(retAddress);
						iLog->Log(_L8("WLanMAC Address")) ;
						iLog->Log(buf);
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
		    	returnCode = KErrGeneral ;
		    	iLog->Log(_L8("Failed.. @TRAPD2")) ;
		    	}
		    }
		   
		    }
	    else
	    	{
	    	returnCode = KErrGeneral ;
	    	iLog->Log(_L8("Failed.. @TRAPD")) ;
	    	}
	    
	    delete sysData ;
	    delete CoreObj ;
	  
	    }
    
    #endif
    
    __UHEAP_MARKEND ;
    return returnCode ;
    

    }
    
    
    
// -----------------------------------------------------------------------------
// Ctsysconnectivity::WrongKey
// Test for wrong key input values
// -----------------------------------------------------------------------------
//
TInt Ctsysconnectivity::WrongKey( CStifItemParser& /*aItem*/ )
    {

     __UHEAP_MARK;
    
    _LIT(KEntity,"Connectivity") ;
    _LIT(KKey,"StatusCharging") ;
    
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
// Ctsysconnectivity::SetWrongDataType
// Tests setinfo with wrong data type
// -----------------------------------------------------------------------------
//
TInt Ctsysconnectivity::SetWrongDataType( CStifItemParser&/* aItem */)
    {

   __UHEAP_MARK;
    
    _LIT(KEntity,"Connectivity") ;
    _LIT(KKey,"InfraRed") ;
    
    TInt returnCode = KErrNone ;
       
    CSysInfoService *CoreObj = CSysInfoService :: NewL() ;
    
    if( NULL == CoreObj)
	    {
	    iLog->Log(_L8("Failed.. @Core")) ;
	   	return KErrGeneral ;
	   	}
    
   CStringData *ipData = CStringData::NewL(KEntity) ;
   	      
   TRAPD(leaveCode, CoreObj->SetInfoL(KEntity,KKey,ipData)) ;
   /* 
   if(KErrArgument != leaveCode)
	    {
	   	returnCode = KErrGeneral ;
    	iLog->Log(_L8("Failed.. @TRAPD")) ;
    	}
    else
    	{
    	iLog->Log(_L8("Passed..")) ;
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
// Ctsysconnectivity::SetWrongKey
// Tests setinfo with wrong Key
// -----------------------------------------------------------------------------
//
TInt Ctsysconnectivity::SetWrongKey( CStifItemParser&/* aItem */)
    {

   __UHEAP_MARK;
    
    _LIT(KEntity,"Connectivity") ;
    _LIT(KKey,"InfraRedd") ;
    
    TInt returnCode = KErrNone ;
       
    CSysInfoService *CoreObj = CSysInfoService :: NewL() ;
    
    if( NULL == CoreObj)
	    {
	    iLog->Log(_L8("Failed.. @Core")) ;
	   	return KErrGeneral ;
	   	}
    
   CStatus *ipData = CStatus::NewL(returnCode) ;
   	      
   TRAPD(leaveCode, CoreObj->SetInfoL(KEntity,KKey,ipData)) ;
    
   if(KErrNotFound != leaveCode)
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
// Ctsysconnectivity::ConnNotWithWrongKey
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctsysconnectivity::ConnNotWithWrongKey( CStifItemParser& /*aItem*/ )
    {
   	TInt Err = KErrNone ;
   	TInt returnCode = KErrNone ;
	
	__UHEAP_MARK;

	CConnectivityNot *test = CConnectivityNot::NewL(iLog, 0);
	test->Start();
	Err = test->Result();
	delete test;
   
    if(KErrNotFound != Err)
    returnCode = KErrGeneral ; 
   
	__UHEAP_MARKEND;
	return returnCode ;

    
    }      
// -----------------------------------------------------------------------------
// Ctsysconnectivity::?member_function
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
/*
TInt Ctsysconnectivity::?member_function(
   CItemParser& aItem )
   {

   ?code

   }
*/

// ========================== OTHER EXPORTED FUNCTIONS =========================
// None

//  End of File
