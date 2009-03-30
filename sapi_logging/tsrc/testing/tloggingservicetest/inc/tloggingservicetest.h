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




#ifndef TLOGGINGSERVICETEST_H
#define TLOGGINGSERVICETEST_H

//  INCLUDES
#include <StifLogger.h>
#include <TestScripterInternal.h>
#include <StifTestModule.h>


// CONSTANTS
//const ?type ?constant_var = ?constant;

// MACROS
//#define ?macro ?macro_def
// Logging path
_LIT( KtloggingservicetestLogPath, "\\logs\\testframework\\tloggingservicetest\\" ); 
// Log file
_LIT( KtloggingservicetestLogFile, "tloggingservicetest.txt" ); 
_LIT( KtloggingservicetestLogFileWithTitle, "tloggingservicetest_[%S].txt" );

// FUNCTION PROTOTYPES
//?type ?function_name(?arg_list);

// FORWARD DECLARATIONS
//class ?FORWARD_CLASSNAME;
class Ctloggingservicetest;

class MLoggingCallback ;
class CLogsEvent ;
class CActiveSchedulerWait ;
class MLogCallback;
// DATA TYPES
//enum ?declaration
//typedef ?declaration
//extern ?data_type;

// CLASS DECLARATION

/**
*  Ctloggingservicetest test class for STIF Test Framework TestScripter.
*  ?other_description_lines
*
*  @lib ?library
*  @since ?Series60_version
*/
NONSHARABLE_CLASS(Ctloggingservicetest) : public CScriptBase
    {
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        */
        static Ctloggingservicetest* NewL( CTestModuleIf& aTestModuleIf );

        /**
        * Destructor.
        */
        virtual ~Ctloggingservicetest();

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
        Ctloggingservicetest( CTestModuleIf& aTestModuleIf );

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
        virtual TInt AddeventS1( );
                virtual TInt AddeventS2( );

        virtual TInt AddeventAS1( );
        virtual TInt AddeventAS2( );
        virtual TInt Isbusy();
        virtual TInt Getlist1( );
        virtual TInt Getlist2( );
           virtual TInt Getlist4( );

         virtual TInt Getevent1( );
         virtual TInt Getevent2( );
         virtual TInt Getevent3( );
         virtual TInt Getevent4( );
         virtual TInt Getevent5( );
          virtual TInt Getrecent1( );
          virtual TInt Getrecent2( );






        //ADD NEW METHOD DEC HERE
        //[TestMethods] - Do not remove

    public:     // Data
        // ?one_line_short_description_of_data
        //?data_declaration;

    protected:  // Data
        // ?one_line_short_description_of_data
        //?data_declaration;

    private:    // Data
        
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


TInt addevents1(void);
TInt addevents2(void);

TInt addeventas1(void);
TInt addeventas2(void);
TInt isbusy(void);
TInt getlist1(void);
TInt getlist2(void);
TInt getlist4(void);
TInt getevent1(void);
TInt getevent2(void);
TInt getevent3(void);
TInt getevent4(void);
TInt getevent5(void);
TInt getrecent1(void);
TInt getrecent2(void);



#endif      // TLOGGINGSERVICETEST_H




// End of File
