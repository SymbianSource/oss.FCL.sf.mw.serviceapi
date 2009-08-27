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




#ifndef TLOCTEST_H
#define TLOCTEST_H

//  INCLUDES
#include <StifLogger.h>
#include <TestScripterInternal.h>
#include <StifTestModule.h>
#include "locationservice.h"

// CONSTANTS
//const ?type ?constant_var = ?constant;

// MACROS
//#define ?macro ?macro_def
// Logging path
_LIT( KTLocTestLogPath, "\\logs\\testframework\\TLocTest\\" ); 
// Log file
_LIT( KTLocTestLogFile, "TLocTest.txt" ); 

// FUNCTION PROTOTYPES
//?type ?function_name(?arg_list);

// FORWARD DECLARATIONS
//class ?FORWARD_CLASSNAME;
class CTLocTest;

// DATA TYPES
//enum ?declaration
//typedef ?declaration
//extern ?data_type;

// CLASS DECLARATION

/**
*  CTLocTest test class for STIF Test Framework TestScripter.
*  ?other_description_lines
*
*  @lib ?library
*  @since ?Series60_version
*/
NONSHARABLE_CLASS(CTLocTest) : public CScriptBase
    {
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        */
        static CTLocTest* NewL( CTestModuleIf& aTestModuleIf );

        /**
        * Destructor.
        */
        virtual ~CTLocTest();

    public: // New functions

        /**
        * ?member_description.
        * @since ?Series60_version
        * @param ?arg1 ?description
        * @return ?description
        */
        //?type ?member_function( ?type ?arg1 );

    public: // Functions from base classes

        /**
        * From CScriptBase Runs a script line.
        * @since ?Series60_version
        * @param aItem Script line containing method name and parameters
        * @return Symbian OS error code
        */
        virtual TInt RunMethodL( CStifItemParser& aItem );

    protected:  // New functions

        /**
        * ?member_description.
        * @since ?Series60_version
        * @param ?arg1 ?description
        * @return ?description
        */
        //?type ?member_function( ?type ?arg1 );

    protected:  // Functions from base classes

        /**
        * From ?base_class ?member_description
        */
        //?type ?member_function();

    private:

        /**
        * C++ default constructor.
        */
        CTLocTest( CTestModuleIf& aTestModuleIf );

        /**
        * By default Symbian 2nd phase constructor is private.
        */
        void ConstructL();

        // Prohibit copy constructor if not deriving from CBase.
        // ?classname( const ?classname& );
        // Prohibit assigment operator if not deriving from CBase.
        // ?classname& operator=( const ?classname& );

        /**
        * Frees all resources allocated from test methods.
        * @since ?Series60_version
        */
        void Delete();

        /**
        * Test methods are listed below. 
        */

        /**
        * Example test method.
        * @since ?Series60_version
        * @param aItem Script line containing parameters.
        * @return Symbian OS error code.
        */
        virtual TInt GetLocation(CStifItemParser &aItem );
        virtual TInt LocationUpdates(CStifItemParser &aItem );
        virtual TInt CancelLocationUpdatesA(CStifItemParser &aItem );
        virtual TInt CancelLocationUpdatesB(CStifItemParser &aItem );
        virtual TInt  LastKnownLoc(CStifItemParser & aItem);
        virtual TInt  FindDistance(CStifItemParser & aItem);
        virtual TInt  FindBearingTo(CStifItemParser & aItem);
        virtual TInt  MoveCoordinates(CStifItemParser & aItem);
        virtual TInt GetLocationAsynch(CStifItemParser & aItem);
        virtual TInt CancelLocationAsynch(CStifItemParser & aItem);
        //virtual TInt GetLocationTimedOut(CStifItemParser& aItem) ;
        //virtual TInt ServiceNotAvailable(CStifItemParser& aItem) ;
        //virtual TInt ServiceFailed(CStifItemParser& aItem) ;
        virtual TInt StraySignal(CStifItemParser& aItem) ;
        virtual TInt StraySignalGetLoc(CStifItemParser& aItem) ;
        virtual TInt ConcurrentCallsGetLoc(CStifItemParser& aItem);
        virtual TInt ConcurrentCallsTrace(CStifItemParser& aItem);
        virtual TInt EmptyCancelTrace(CStifItemParser& aItem);
        virtual TInt EmptyCancelLocAsynch(CStifItemParser& aItem);
        virtual TInt TraceTimeOut(CStifItemParser& aItem);
    public:     // Data
        
        //?data_declaration;

    protected:  // Data
        // ?one_line_short_description_of_data
        //?data_declaration;

    private:    // Data
        // CGetLoc Core class that contains all the location functionalities
       
        // ?one_line_short_description_of_data
        //?data_declaration;

        // Reserved pointer for future extension
        //TAny* iReserved;

    public:     // Friend classes
        //?friend_class_declaration;
    protected:  // Friend classes
        //?friend_class_declaration;
    private:    // Friend classes
        //?friend_class_declaration;

    };
    
    TInt GetLocUpdates(TAny *aPtr);
    TInt FindLocationAsynch(TAny *aPtr);
    TInt ServiceFailedTest(TAny *Arg) ;
    TInt StrayTest(TAny *aArg) ;
    TInt StrayTestGetLoc(TAny *aArg) ;
    TInt ConcurrentGetLocationCalls(TAny *aArg) ;
    TInt TraceTimeOutFunc(TAny *aArg) ;
    TInt ConcurrentTraceCalls(TAny */*Arg*/);

#endif      // TLOCTEST_H

// End of File
