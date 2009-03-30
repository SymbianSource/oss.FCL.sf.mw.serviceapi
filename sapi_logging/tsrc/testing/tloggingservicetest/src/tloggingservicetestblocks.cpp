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




// [INCLUDE FILES] - do not remove
#include <e32svr.h>
#include <StifParser.h>
#include <Stiftestinterface.h>
#include "tloggingservicetest.h"

#include <logcli.h>
#include <logwrap.h>
#include "loggingasyncservice.h"
#include "loggingsyncservice.h"
#include "loggingfilter.h"
#include "loggingservice.h"
#include "loggingevent.h"
#include "logiter.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctloggingservicetest::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void Ctloggingservicetest::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// Ctloggingservicetest::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt Ctloggingservicetest::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "AddeventS1", Ctloggingservicetest::AddeventS1 ),
       	ENTRY( "AddeventS2", Ctloggingservicetest::AddeventS2 ),
        ENTRY( "AddeventAS1", Ctloggingservicetest::AddeventAS1 ),
        ENTRY( "AddeventAS2", Ctloggingservicetest::AddeventAS2 ),
        ENTRY( "Isbusy", Ctloggingservicetest::Isbusy ),

        
        ENTRY( "Getlist1", Ctloggingservicetest::Getlist1 ),
        ENTRY( "Getlist2", Ctloggingservicetest::Getlist2 ),
        ENTRY( "Getlist4", Ctloggingservicetest::Getlist4 ),
        ENTRY( "Getevent1", Ctloggingservicetest::Getevent1),
        ENTRY( "Getevent2", Ctloggingservicetest::Getevent2),
        ENTRY( "Getevent3", Ctloggingservicetest::Getevent3),
        ENTRY( "Getevent4", Ctloggingservicetest::Getevent4),
        ENTRY( "Getevent5", Ctloggingservicetest::Getevent5),
        ENTRY( "Getrecent1", Ctloggingservicetest::Getrecent1),
        ENTRY( "Getrecent2", Ctloggingservicetest::Getrecent2),









        //ADD NEW ENTRY HERE
        // [test cases entries] - Do not remove

        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// Ctloggingservicetest::AddeventS1
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctloggingservicetest::AddeventS1()
    {
__UHEAP_MARK;
 TInt ret = addevents1();
 
 __UHEAP_MARKEND;
return ret;
    }
    
    
    
    
    // -----------------------------------------------------------------------------
// Ctloggingservicetest::AddeventS2
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctloggingservicetest::AddeventS2()
    {
__UHEAP_MARK;
 TInt ret = addevents2();
 
 __UHEAP_MARKEND;
return ret;
    }
    
    
// -----------------------------------------------------------------------------
// Ctloggingservicetest::AddeventAS1
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//


TInt Ctloggingservicetest::AddeventAS1()
    {
__UHEAP_MARK;
 TInt ret = addeventas1();
 
 __UHEAP_MARKEND;
 
 return ret;

    }
    
    
    
    TInt Ctloggingservicetest::AddeventAS2()
    {
__UHEAP_MARK;
 TInt ret = addeventas2();
 
 __UHEAP_MARKEND;
 
 return ret;

    }
    
    
    TInt Ctloggingservicetest::Isbusy()
    {
__UHEAP_MARK;
 TInt ret = isbusy();
 
 __UHEAP_MARKEND;
 
 return ret;

    }
    
    
    
    
    
    
    
    
    
  TInt Ctloggingservicetest::Getlist1()
    {
__UHEAP_MARK;
 TInt ret = getlist1();
 
 __UHEAP_MARKEND;
 
 return ret;

    }
    
    
     TInt Ctloggingservicetest::Getlist2()
    {
__UHEAP_MARK;
 TInt ret = getlist2();
 
 __UHEAP_MARKEND;
 
 return ret;

    }
    
    
 
    
    
    
    TInt Ctloggingservicetest::Getlist4()
    {
__UHEAP_MARK;
 TInt ret = getlist4();
 
 __UHEAP_MARKEND;
  
 return ret;

    }
    
    
    
    
      TInt Ctloggingservicetest::Getevent1()
    {
__UHEAP_MARK;
 TInt ret = getevent1();
 
 __UHEAP_MARKEND;
 
 return ret;

    }
    
    
          TInt Ctloggingservicetest::Getevent2()
    {
__UHEAP_MARK;
 TInt ret = getevent2();
 
 __UHEAP_MARKEND;
 
 return ret;

    }

          
          
          TInt Ctloggingservicetest::Getevent3()
        	    {
        	__UHEAP_MARK;
        	 TInt ret = getevent3();
        	 
        	 __UHEAP_MARKEND;
        	 
        	 return ret;

        	    }
          
          
          TInt Ctloggingservicetest::Getevent4()
      	    {
      	__UHEAP_MARK;
      	 TInt ret = getevent4();
      	 
      	 __UHEAP_MARKEND;
      	 
      	 return ret;

      	    }
          
          
          
          
          TInt Ctloggingservicetest::Getevent5()
        	    {
        	__UHEAP_MARK;
        	 TInt ret = getevent5();
        	 
        	 __UHEAP_MARKEND;
        	 
        	 return ret;

        	    }

              TInt Ctloggingservicetest::Getrecent1()
    {
__UHEAP_MARK;

 TInt ret = getrecent1();
 
 __UHEAP_MARKEND;
 
 return ret;

    }
    
    
    
    
    
 TInt Ctloggingservicetest::Getrecent2()
    {
__UHEAP_MARK;
 TInt ret = getrecent2();
 
 __UHEAP_MARKEND;
 
 return ret;

    }
//  [End of File] - Do not remove
