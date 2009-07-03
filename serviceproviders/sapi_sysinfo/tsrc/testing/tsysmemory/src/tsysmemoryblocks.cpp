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
* Description:   Tests sysinfo memory entity
*
*/




// INCLUDE FILES
#include <e32svr.h>
#include <StifParser.h>
#include <Stiftestinterface.h>
#include "tsysmemory.h"
#include "tsysmemorynot.h"

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
// Ctsysmemory::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void Ctsysmemory::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// Ctsysmemory::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt Ctsysmemory::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "ListDrives", Ctsysmemory::ListDrives ),
	    ENTRY( "DriveInfo", Ctsysmemory::DriveInfo ),
	    ENTRY( "MemoryCardState", Ctsysmemory::MemoryCardState ),
   	    ENTRY( "MemGetInfoAsync", Ctsysmemory::MemGetAsync ),
   	    ENTRY( "MemNotWithWrongKey", Ctsysmemory::MemNotWithWrongKey ),

        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// Ctsysmemory::ListDrives
// Tests the ListDrives functionality
// -----------------------------------------------------------------------------
//
TInt Ctsysmemory::ListDrives( CStifItemParser& aItem )
    {

	 __UHEAP_MARK;
    
    _LIT(KEntity,"Memory") ;
    _LIT(KKey,"ListDrives") ;
    
    TInt returnCode = KErrNone ;
    TInt expListCount = 0 ;
    TInt expDataType = 7 ;
    aItem.GetNextInt (expListCount) ;
    
    CSysInfoService *CoreObj = CSysInfoService :: NewL() ;
    
    if( NULL == CoreObj)
	    {
	    iLog->Log(_L8("Failed.. @Core")) ;
	   	return KErrGeneral ;
	   	}

    CSysData *sysData ;
   	
    iLog->Log(_L8("expListCount : %d"),expListCount) ;	
 
    TRAPD(leaveCode, CoreObj->GetInfoL(KEntity,KKey,sysData)) ;
    if(KErrNone == leaveCode)
	    {
	       
	    TInt retType = sysData->DataType() ;
	    
	    if(expDataType == retType)
		    {
		      
		    CDriveList *status = (CDriveList*)sysData ;
		    TInt retStatus = status->Count() ;
		    	   
		    /*if(expListCount != retStatus)
		    	{
		        returnCode = KErrGeneral ; 
		    	iLog->Log(_L8("Failed.. @retStatus")) ;
		    	}
		    else
		    	{*/
		    	
		    	for(TInt count=0; count<expListCount; count++)
		    		{
		    		TInt driveNo = (*status)[count] ;
		    		iLog->Log(_L8("Drive No: %d"),driveNo) ;
		    		}
		    	iLog->Log(_L8("Passed..")) ;	
		    	}
		    // }
		    
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
// Ctsysmemory::DriveInfo
// Tests the DriveInfo functionality
// -----------------------------------------------------------------------------
//
TInt Ctsysmemory::DriveInfo( CStifItemParser& aItem )
    {

	 __UHEAP_MARK;
    
    _LIT(KEntity,"Memory") ;
    _LIT(KKey,"DriveInfo") ;
    
    TInt returnCode = KErrNone ;
    TInt expDrive = 0 ;
    TInt expDataType = 5 ;
    aItem.GetNextInt (expDrive) ;
    
    CSysInfoService *CoreObj = CSysInfoService :: NewL() ;
    
    if( NULL == CoreObj)
	    {
	    iLog->Log(_L8("Failed.. @Core")) ;
	   	return KErrGeneral ;
	   	}
    
 //   CSysAttribute* attrib = CSysAttribute::NewL(KEntity,KKey) ;
    CDriveInfo* driveInfo = CDriveInfo::NewL(expDrive) ;
//    TSysRequest sysReq(attrib, driveInfo) ;
    CSysData* sysData ;
   	
   	
    iLog->Log(_L8("expDrive : %d"),expDrive) ;	
    TRAPD(leaveCode, CoreObj->GetInfoL(KEntity,KKey,sysData,driveInfo)) ;
    
    if((0<=expDrive<=26) && (KErrNone == leaveCode))
	    {
	       
	    TInt retType = sysData->DataType() ;
	    
	    if(expDataType == retType)
		    {
		      
		    CDriveInfo *status = (CDriveInfo*)sysData ;

		    TInt retDrive = status->DriveNumber() ;
		    	   
		    if(expDrive != retDrive)
		    	{
		        returnCode = KErrGeneral ; 
		    	iLog->Log(_L8("Failed.. @retStatus")) ;
		    	}
		    else
		    	{
		    	TPtrC driveName ;
		      	status->DriveName(driveName) ;
		    	TBuf<50> bufName(driveName) ; 
		    	iLog->Log(_L8("DriveName : ")) ;	
		    	iLog->Log(bufName) ;
		    	iLog->Log(_L8("CriticalSpace : %d"),status->CriticalSpace()) ;	
		    	iLog->Log(_L8("MediaType : %d"),status->MediaType()) ;	
		    	iLog->Log(_L8("TotalSpace : %d"),status->TotalSpace()) ;	
		    	iLog->Log(_L8("FreeSpace : %d"),status->FreeSpace()) ;	
			   	iLog->Log(_L8("BatteryState : %d"),status->BatteryState()) ;	

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
    else if(((expDrive<0) || (expDrive>26)) && (KErrNotFound == leaveCode))
    	{
    	iLog->Log(_L8("Passed..")) ;	
    	}
    
    else
    	{
    	returnCode = KErrGeneral ;
    	iLog->Log(_L8("Failed.. @TRAPD")) ;
    	}
    delete CoreObj ;
    delete driveInfo ;
    
    __UHEAP_MARKEND ;
    return returnCode ;

    }



// -----------------------------------------------------------------------------
// Ctsysmemory::MemoryCardState
// Tests the MemoryCardState functionality
// -----------------------------------------------------------------------------
//
TInt Ctsysmemory::MemoryCardState( CStifItemParser& aItem )
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
        returnCode = KErrNone ; 
	    	iLog->Log(_L8("Passed.. MEM CARD STATE: %d"),retStatus) ;	
		     }
		else
			{
			returnCode = KErrGeneral ;	
			iLog->Log(_L8("Failed.. @retType: %d"),retType) ;
			}    
	    
	    delete sysData ;
	    
	    }
    else
    	{
    	returnCode = KErrGeneral ;
    	iLog->Log(_L8("Failed.. @TRAPD: %d"),leaveCode) ;
    	}
    delete CoreObj ;
   
    __UHEAP_MARKEND ;
    return returnCode ;

    }


// -----------------------------------------------------------------------------
// Ctsysmemory::MemGetAsync
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctsysmemory::MemGetAsync( CStifItemParser& aItem )
    {
   	TInt Err = KErrNone ;
   	TInt returnCode = KErrNone ;
	
	__UHEAP_MARK;

	CMemNot *test = CMemNot::NewL(iLog, 0);
	test->Start();
	Err = test->Result();
	delete test;
   
    if(KErrNotSupported != Err)
    returnCode = KErrGeneral ; 
   
	__UHEAP_MARKEND;
	return returnCode ;

    
    }   

// -----------------------------------------------------------------------------
// Ctsysmemory::MemNotWithWrongKey
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctsysmemory::MemNotWithWrongKey( CStifItemParser& aItem )
    {
   	TInt Err = KErrNone ;
   	TInt returnCode = KErrNone ;
	
	__UHEAP_MARK;

	CMemNot *test = CMemNot::NewL(iLog, 1);
	test->Start();
	Err = test->Result();
	delete test;
   
    if(KErrNotFound != Err)
    returnCode = KErrGeneral ; 
   
	__UHEAP_MARKEND;
	return returnCode ;

    
    }


// -----------------------------------------------------------------------------
// Ctsysmemory::?member_function
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
/*
TInt Ctsysmemory::?member_function(
   CItemParser& aItem )
   {

   ?code

   }
*/

// ========================== OTHER EXPORTED FUNCTIONS =========================
// None

//  End of File
