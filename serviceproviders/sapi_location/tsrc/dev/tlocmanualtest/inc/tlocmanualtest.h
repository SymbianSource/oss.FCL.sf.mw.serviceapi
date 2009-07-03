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




#ifndef TLOCMANUALTEST_H
#define TLOCMANUALTEST_H

//  INCLUDES
#include <StifLogger.h>
#include <TestScripterInternal.h>
#include <StifTestModule.h>
#include "locationservice.h"


// Logging path
_LIT( KTLocManualTestLogPath, "\\logs\\testframework\\TLocManualTest\\" ); 
// Log file
_LIT( KTLocManualTestLogFile, "TLocManualTest.txt" ); 




class CTLocManualTest;



// CLASS DECLARATION

/**
*  CTLocManualTest test class for STIF Test Framework TestScripter.
*  
*/
NONSHARABLE_CLASS(CTLocManualTest) : public CScriptBase
    {
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        */
        static CTLocManualTest* NewL( CTestModuleIf& aTestModuleIf );

        /**
        * Destructor.
        */
        virtual ~CTLocManualTest();

    
        

    public: // Functions from base classes

        
        virtual TInt RunMethodL( CStifItemParser& aItem );

    
       
    private:

        /**
        * C++ default constructor.
        */
        CTLocManualTest( CTestModuleIf& aTestModuleIf );

        /**
        * By default Symbian 2nd phase constructor is private.
        */
        void ConstructL();

        

        
        void Delete();

        /**
        * Test methods are listed below. 
        */

        
        
        virtual TInt GetLocationTimedOut(CStifItemParser& aItem) ;
        virtual TInt ServiceNotAvailable(CStifItemParser& aItem) ;
        virtual TInt ServiceFailed(CStifItemParser& aItem) ;
        
    

    };
    
    
    
    TInt ServiceFailedTest(TAny *Arg) ;
    

#endif      // TLOCMANUALTEST_H

// End of File
