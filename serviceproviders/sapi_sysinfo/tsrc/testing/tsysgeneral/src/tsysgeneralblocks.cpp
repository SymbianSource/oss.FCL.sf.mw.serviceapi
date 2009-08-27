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
* Description:   Tests sysinfo general information 
*
*/




// INCLUDE FILES
#include <e32svr.h>
#include <StifParser.h>
#include <Stiftestinterface.h>
#include "tsysgeneral.h"
#include <COEMAIN.H> 
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
// Ctsysgeneral::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void Ctsysgeneral::Delete() 
    {

    }
// -----------------------------------------------------------------------------
// Ctsysgeneral::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt Ctsysgeneral::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "GetDisplayLanguage", Ctsysgeneral::GetDisplayLanguage ),
        ENTRY( "SetWrongDataType", Ctsysgeneral::SetWrongDataType ),
        ENTRY( "SetAndGetInputLanguage", Ctsysgeneral::SetAndGetInputLanguage ),
        ENTRY( "SetAndGetPridictiveText", Ctsysgeneral::SetAndGetPridictiveText ),
        ENTRY( "SetAndGetVibraActive", Ctsysgeneral::SetAndGetVibraActive ),
     	ENTRY( "GetActiveUSBMode", Ctsysgeneral::GetActiveUSBMode ),
 		ENTRY( "GetAvblUSBMode", Ctsysgeneral::GetAvblUSBMode ),
        ENTRY( "AsyncGetinfoStatus", Ctsysgeneral::AsyncGetinfoStatus) ,
        ENTRY( "NotifyIpAndPredText", Ctsysgeneral::NotifyIpAndPredText) ,
        ENTRY( "SetWrongKey", Ctsysgeneral::SetWrongKey ),
        ENTRY( "SetWrongEntity", Ctsysgeneral::SetWrongEntity ),
        ENTRY( "GetWrongKey", Ctsysgeneral::GetWrongKey ),
        
        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// Ctsysgeneral::GetDisplayLanguage
// Test method for Get DisplayLanguage 
// -----------------------------------------------------------------------------
//
TInt Ctsysgeneral::GetDisplayLanguage( CStifItemParser& aItem )
    {
    CCoeEnv* coeSupported = NULL;
    coeSupported = CCoeEnv::Static();
    if (coeSupported)
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
        CSysData *sysData = NULL;

        iLog->Log(_L8("DisplayLanguage : %d"), expLanguage) ;
        TRAPD(leaveCode, CoreObj->GetInfoL(KEntity, KKey, sysData)) ;
        if (KErrNotFound != leaveCode)
            {
            iLog->Log(_L("Failed, Set Display language found ret err: %d"),
                    leaveCode);
            returnCode = KErrGeneral;
            }
        else
            {
            returnCode = KErrNone;
            iLog->Log(_L8("P.. @TRAPD")) ;
            }

        delete sysData;
        delete CoreObj;
        __UHEAP_MARKEND;
        return returnCode;
        }
    else
        {
        iLog->Log(_L("CCoeEnv not supported . So passing the test case"));
        return 0;
        }
    }

// -----------------------------------------------------------------------------
// Ctsysgeneral::SetWrongDataType
// Test method for setting Wrong DataType 
// -----------------------------------------------------------------------------
//
TInt Ctsysgeneral::SetWrongDataType( CStifItemParser& /*aItem*/ )
    {

    __UHEAP_MARK;
    
    _LIT(KEntity,"Display") ;
    _LIT(KKey,"Brightness") ;
    
    TInt returnCode = KErrNone ;
    
    CSysInfoService *CoreObj = CSysInfoService :: NewL() ;
    
    if( NULL == CoreObj)
	    {
	    iLog->Log(_L8("Failed.. @Core")) ;
	   	return KErrGeneral ;
	   	}
    
   	CStringData *sysData = CStringData::NewL(KEntity) ;
   	
	TRAPD(leaveCode, CoreObj->SetInfoL(KEntity,KKey,sysData)) ;
    
    if(KErrArgument != leaveCode)
	    {
	   	returnCode = KErrGeneral ;
    	iLog->Log(_L8("Failed.. @TRAPD")) ;
    	}
    else
    	{
    	iLog->Log(_L8("Passed..")) ;
    	}
    
    delete sysData ;
    delete CoreObj ;
    
       
    __UHEAP_MARKEND ;
    return returnCode ;

    }



// -----------------------------------------------------------------------------
// Ctsysgeneral::SetAndGetInputLanguage
// Test method for Setting and Getting InputLanguage 
// -----------------------------------------------------------------------------
//
TInt Ctsysgeneral::SetAndGetInputLanguage( CStifItemParser& /*aItem*/ )
    {

    __UHEAP_MARK;
    
    _LIT(KEntity,"General") ;
    _LIT(KKey,"InputLanguage") ;
    _LIT(KLangListKey,"SupportedLanguages");
    
    TInt returnCode = KErrNone ;
    TInt expLanguage = 0 ;
    TInt expDataType = 0 ;
    TInt engLang = 1 ;
    //aItem.GetNextInt (expLanguage) ;             
    
    CSysInfoService *CoreObj = CSysInfoService :: NewL() ;
    
    if( NULL == CoreObj)
	    {
	    iLog->Log(_L8("Failed.. @Core")) ;
	   	return KErrGeneral ;
	   	}

	TInt currLang = -1;	
	
	//get the list of lang's available on the system	
	CSysData *sysData1 = NULL;		
	TRAPD(leaveCode, CoreObj->GetInfoL(KEntity,KLangListKey,sysData1)) ;	   	
	
	
	TInt langCount = 0;
	
	if(KErrNone == leaveCode)
	{
		//Get list of languages passed..
		
		CLanguageList *langListData = NULL;	        	  	    
	    TInt retType = sysData1->DataType() ;
	    if( CSysData::ELanguageList == retType )
	    {
	    	langListData = (CLanguageList*)sysData1 ;
	    	langCount = langListData->Count();

			if( langCount > 1 )
			{	
				//get current lang
				CSysData *sysData = NULL;	    	   	    	       	
				TRAPD(leaveCode1, CoreObj->GetInfoL(KEntity,KKey,sysData)) ;
				if(KErrNone == leaveCode1)
				{			       
					TInt retType = sysData->DataType() ;
		   
					if(expDataType == retType)
					{			      
						CStatus *status = (CStatus*)sysData ;
						currLang = status->Status();
						//got the current language..
						TInt i = 0,newLangCode = -1;
						while( i < langCount )
						{
							langListData->At(i,newLangCode);
							if( newLangCode != currLang )
							{//we got a new supported lang
								iLog->Log(_L8("New lang is %d"),newLangCode) ;
								break;
							}
							i++;																	
						}
																			       	
					   	CStatus *ipData = CStatus::NewL(newLangCode);
					    TRAPD(leaveCode2, CoreObj->SetInfoL(KEntity,KKey,ipData));
					    delete ipData;
					    if(KErrNone == leaveCode2)
					    {
					    	CSysData *sysData3 = NULL;
					 		TRAPD(leaveCode3, CoreObj->GetInfoL(KEntity,KKey,sysData3));
					    	if(KErrNone == leaveCode3)
						    {
						    	TInt retType = sysData3->DataType() ;
						    	TInt lang = -1;
						    	if(expDataType == retType)
								{
									CStatus *status = (CStatus*)sysData3 ;
									lang = status->Status();
									if( lang == newLangCode )
									{
										returnCode = KErrNone;
									}
									else
									{
										returnCode = KErrGeneral;
										iLog->Log(_L8("Failed.. Curr lang is @retType %d"),retType) ;
									}									
								}
								else
								{
									returnCode = KErrGeneral ;	
									iLog->Log(_L8("Failed.. Get Info @retType %d"),retType) ;
								}
						    }
						    else
						    {
					    		returnCode = KErrGeneral ;	
								iLog->Log(_L8("Failed..Get Lang @TrapD %d"),leaveCode3) ;					    							    	
						    }
						    if( sysData3 != NULL )
						    {
						    	delete sysData3;
						    	sysData3 = NULL;
						    }
					    }
					    else
					    {
					    	returnCode = KErrGeneral ;	
							iLog->Log(_L8("Failed..Set Lang @TrapD %d"),leaveCode2) ;					    	
					    }					    				    															
	    			} 
					else
					{
						returnCode = KErrGeneral ;	
						iLog->Log(_L8("Failed.. @retType %d"),retType) ;
					}    
		   	
		   			if(sysData)
		   			{
		   				delete sysData ;
		   				sysData = NULL;	    
		   			}
						
				}
				else
				{
	   				returnCode = KErrGeneral ;
	   				iLog->Log(_L8("Failed.. get current lang@2 TRAPD %d"),leaveCode1) ;
				}
			//lang count more than 1	
			}
			else
			{
				iLog->Log(_L8("There is only one lang"));				
			}
	    }
	    else
	    {
			returnCode = KErrGeneral ;	
			iLog->Log(_L8("Failed.. Get list of languages @retType %d"),retType) ;	    	

	    }
	    
		if(langListData)
		{
			delete langListData ;
		   	langListData = NULL;	    
		}
	//Get list of languages passed..	   	    
	 }
	 else
	 {	 	
    	iLog->Log(_L8("LeaveCode : %d"),leaveCode) ;
    	iLog->Log(_L8("Failed getting lsit of languages.. @TRAPD %d"),leaveCode);
    	returnCode = KErrGeneral ;
	 }	 	      	    	   	    	       		 	 
    
    //set lang back to English
    CStatus *defData = CStatus::NewL(engLang) ;   	
    CoreObj->SetInfoL(KEntity,KKey,defData) ;   
    delete defData ;
          
    delete CoreObj ;
    
       
    __UHEAP_MARKEND ;
    return returnCode ;

    }


// -----------------------------------------------------------------------------
// Ctsysgeneral::SetAndGetPridictiveText
// Test method for setting and getting PridictiveText 
// -----------------------------------------------------------------------------
//
TInt Ctsysgeneral::SetAndGetPridictiveText( CStifItemParser& aItem )
    {

    __UHEAP_MARK;
    
    _LIT(KEntity,"General") ;
    _LIT(KKey,"PredictiveText") ;
    
    TInt returnCode = KErrNone ;
    TInt expState = 0 ;
    TInt expDataType = 0 ;
    TInt defValue = 0 ;
    aItem.GetNextInt (expState) ;
    
    
    CSysInfoService *CoreObj = CSysInfoService :: NewL() ;
    
    if( NULL == CoreObj)
	    {
	    iLog->Log(_L8("Failed.. @Core")) ;
	   	return KErrGeneral ;
	   	}
    iLog->Log(_L8("PridictiveText : %d"),expState) ;
    
 	CStatus *ipData = CStatus::NewL(expState) ;
   	
    TRAPD(leaveCode, CoreObj->SetInfoL(KEntity,KKey,ipData)) ;
   
    
    if(KErrNone == leaveCode)
	    {
	        
	    CSysData *sysData ;
	   	
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
	    	iLog->Log(_L8("Failed.. @2 TRAPD")) ;
	    	}
	     
    	}
    else
    	{
    	returnCode = KErrGeneral ;
    	iLog->Log(_L8("Failed.. @TRAPD leavecode: %d"),leaveCode) ;
    	}
    
    CStatus *defData = CStatus::NewL(defValue) ;
   	
    CoreObj->SetInfoL(KEntity,KKey,defData) ;
    
    delete defData ;
    delete ipData ;
    delete CoreObj ;
    
    __UHEAP_MARKEND ;
    return returnCode ;

    }


// -----------------------------------------------------------------------------
// Ctsysgeneral::SetAndGetVibraActive
// Test method for setting and getting VibraActive 
// -----------------------------------------------------------------------------
//
TInt Ctsysgeneral::SetAndGetVibraActive( CStifItemParser& aItem )
    {

    __UHEAP_MARK;
    
    _LIT(KEntity,"General") ;
    _LIT(KKey,"VibraActive") ;
    
    TInt returnCode = KErrNone ;
    TInt expState = 0 ;
    TInt expDataType = 0 ;
    TInt defValue = 0 ;
    aItem.GetNextInt (expState) ;
    
    CSysInfoService *CoreObj = CSysInfoService :: NewL() ;
    
    if( NULL == CoreObj)
	    {
	    iLog->Log(_L8("Failed.. @Core")) ;
	   	return KErrGeneral ;
	   	}
    

 	CStatus *ipData = CStatus::NewL(expState) ;
   	
    TRAPD(leaveCode, CoreObj->SetInfoL(KEntity,KKey,ipData)) ;
    
    if(KErrNone == leaveCode)
	    {
	    	
	    CSysData *sysData ;
	   	
	   	iLog->Log(_L8("VibraActive : %d"),expState) ;	
	    
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
	    	iLog->Log(_L8("Failed.. @2TRAPD")) ;
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
    delete ipData ;
    delete CoreObj ;
    
    __UHEAP_MARKEND ;
    
    return returnCode ;

    }



// -----------------------------------------------------------------------------
// Ctsysgeneral::GetActiveUSBMode
// Test method for getting ActiveUSBMode 
// -----------------------------------------------------------------------------
//
TInt Ctsysgeneral::GetActiveUSBMode( CStifItemParser& /*aItem*/ )
    {

    __UHEAP_MARK;
    
    _LIT(KEntity,"General") ;
    _LIT(KKey,"ActiveUSBMode") ;
    _LIT(KexpMode, "PC Suite") ;
    TInt expDataType = 12 ;
    TInt returnCode = KErrNone ;
    TPtrC expDev(KexpMode) ; 
  //  aItem.GetNextString(expDev) ;   
    
    #if ( !(defined(__WINS__) || defined(__WINSCW__)) )
    
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
		      
		    CStringData *retData = (CStringData*)sysData ;
		    TPtrC retDev ;
	    	
	    	retData->StringData(retDev) ;
		    TBuf<50> retDevice(retDev) ;
		    iLog->Log(_L8("retPath")) ;		    	   
		   	iLog->Log(retDevice) ;
		   	iLog->Log(_L8("Passed..")) ; 	
		   	
		   	/*
		   	if(expDev.Compare(retDev)) 
		    	{
		       	returnCode = KErrGeneral ; 
		    	iLog->Log(_L8("Failed.. @retPath")) ;
		        }
		   	else
		   		{
		   		
		       	iLog->Log(_L8("Passed..")) ; 
		   		}
		   	  */
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
// Ctsysgeneral::GetAvblUSBMode
// Test method for getting available USBMode 
// -----------------------------------------------------------------------------
//
TInt Ctsysgeneral::GetAvblUSBMode( CStifItemParser& aItem )
    {

    __UHEAP_MARK;
    
    _LIT(KEntity,"General") ;
    _LIT(KKey,"AvailableUSBModes") ;
    
    TInt expDataType = 11 ;
    TInt returnCode = KErrNone ;
    TPtrC expDev ; 
    aItem.GetNextString(expDev) ;   
    
    #if ( !(defined(__WINS__) || defined(__WINSCW__)) )
    
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
		      
		    CStringList *retData = (CStringList*)sysData ;
		    TInt listCount ;
		    listCount = retData->Count() ;
		    
		    if(listCount)
			    {
			    	
			    for(TInt i=0; i<listCount; i++)
				    {
				    	
				    TPtrC retDev ;
			    	retData->At(i,retDev) ;
				    TBuf<50> retDevice(retDev) ;
				    iLog->Log(_L8("Available USB modes")) ;		    	   
				    iLog->Log(retDevice) ;	
				   	
				   	}
			    }
		    
		    else
		    	{
		    	returnCode = KErrGeneral ;
		    	iLog->Log(_L8("empty list")) ;		    
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
// Ctsysgeneral::AsyncAccStatus
// Test method for getting connected accessories 
// -----------------------------------------------------------------------------
//
TInt Ctsysgeneral::AsyncGetinfoStatus( CStifItemParser& /*aItem*/ )
    {

    __UHEAP_MARK;
 
    TInt returnCode = KErrNone ;
   
    returnCode = TestAsyncStatus(iLog) ;
   
    __UHEAP_MARKEND ;
    return returnCode ;

    }


// -----------------------------------------------------------------------------
// Ctsysgeneral::NotifyIpAndPredText
// Test method for getting notification for Input and predecitive text changes
// -----------------------------------------------------------------------------
//
TInt Ctsysgeneral::NotifyIpAndPredText( CStifItemParser& /*aItem*/ )
    {

    __UHEAP_MARK;
 
    TInt returnCode = KErrNone ;
   
    returnCode = TestIpAndPredTextNot(iLog) ;
   
    __UHEAP_MARKEND ;
    return returnCode ;

    }


// -----------------------------------------------------------------------------
// Ctsysgeneral::SetWrongKey
// Test method for setting Wrong Key 
// -----------------------------------------------------------------------------
//
TInt Ctsysgeneral::SetWrongKey( CStifItemParser& /*aItem*/ )
    {

    __UHEAP_MARK;
    
    _LIT(KEntity,"General") ;
    _LIT(KKey,"DisplayLanguagee") ;
    TInt expState = 1 ;
    TInt returnCode = KErrNone ;
    
    CSysInfoService *CoreObj = CSysInfoService :: NewL() ;
    
    if( NULL == CoreObj)
	    {
	    iLog->Log(_L8("Failed.. @Core")) ;
	   	return KErrGeneral ;
	   	}
    
   	CStatus *ipData = CStatus::NewL(expState) ;
   	
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
// Ctsysgeneral::SetWrongEntity
// Test method for setting Wrong Entity 
// -----------------------------------------------------------------------------
//
TInt Ctsysgeneral::SetWrongEntity( CStifItemParser& /*aItem*/ )
    {

    __UHEAP_MARK;
    
    _LIT(KEntity,"Genral") ;
    _LIT(KKey,"DisplayLanguagee") ;
    TInt expState = 1 ;
    TInt returnCode = KErrNone ;
    
    CSysInfoService *CoreObj = CSysInfoService :: NewL() ;
    
    if( NULL == CoreObj)
	    {
	    iLog->Log(_L8("Failed.. @Core")) ;
	   	return KErrGeneral ;
	   	}
    
   	CStatus *ipData = CStatus::NewL(expState) ;
   	
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
// Ctsysgeneral::GetWrongKey
// Test method for Getinfo with wrong key valye
// -----------------------------------------------------------------------------
//
TInt Ctsysgeneral::GetWrongKey( CStifItemParser& /*aItem*/ )
    {

    __UHEAP_MARK;
    
    _LIT(KEntity,"General") ;
    _LIT(KKey,"ActiveUSBModde") ;
        
    TInt returnCode = KErrNone ;
    
    CSysInfoService *CoreObj = CSysInfoService :: NewL() ;
    
    if( NULL == CoreObj)
	    {
	    iLog->Log(_L8("Failed.. @Core")) ;
	   	return KErrGeneral ;
	   	}
    

    CSysData *sysData ;
 
    TRAPD(leaveCode, CoreObj->GetInfoL(KEntity,KKey,sysData)) ;
    
    if(KErrNotFound != leaveCode)
	    {
	   	returnCode = KErrGeneral ;
    	iLog->Log(_L8("Failed.. @TRAPD")) ;
    	}
    else
    	{
    	iLog->Log(_L8("Passed..")) ;
    	}
    
    delete CoreObj ;
 
    __UHEAP_MARKEND ;
    return returnCode ;

    }
    
// -----------------------------------------------------------------------------
// Ctsysgeneral::?member_function
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
/*
TInt Ctsysgeneral::?member_function(
   CItemParser& aItem )
   {

   ?code

   }
*/

// ========================== OTHER EXPORTED FUNCTIONS =========================
// None

//  End of File
