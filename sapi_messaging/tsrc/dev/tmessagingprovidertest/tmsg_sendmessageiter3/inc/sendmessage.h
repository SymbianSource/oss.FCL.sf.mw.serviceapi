/*
* Copyright (c) 2006-2007 Nokia Corporation and/or its subsidiary(-ies).
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




#ifndef SENDMESSAGE_H 
#define SENDMESSAGE_H 

//  INCLUDES
//#include <StifLogger.h>
#include <TestScripterInternal.h>
#include <StifTestModule.h>


extern int sendmessage_test1(int, char**);
extern int sendmessage_test2(int, char**);
extern int sendmessage_test3(int, char**);
extern int sendmessage_test4(int, char**);
extern int sendmessage_test5(int, char**);
extern int sendmessage_test6(int, char**);
extern int sendmessage_test7(int, char**);
extern int sendmessage_test8(int, char**);
extern int sendmessage_test9(int, char**);
extern int sendmessage_test10(int, char**);




//extern int accum2_test(int, char**);
// CONSTANTS
//const ?type ?constant_var = ?constant;

// MACROS
//#define ?macro ?macro_def
// Logging path
//_LIT( Kstlport_sendmessageLogPath, "\\logs\\testframework\\sendmessage1\\" ); 
// Log file
//_LIT( Kstlport_sendmessageFile, "sendmessage1.txt" ); 

// FUNCTION PROTOTYPES
//?type ?function_name(?arg_list);

// FORWARD DECLARATIONS
//class ?FORWARD_CLASSNAME;
class Csapi_sendmessage;

// DATA TYPES
//enum ?declaration
//typedef ?declaration
//extern ?data_type;

// CLASS DECLARATION

/**
*  Cstlport_accum test class for STIF Test Framework TestScripter.
*  ?other_description_lines
*
*  @lib ?library
*  @since ?Series60_version
*/
NONSHARABLE_CLASS(Csapi_sendmessage) : public CScriptBase
    {
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        */
        static Csapi_sendmessage* NewL( CTestModuleIf& aTestModuleIf );

        /**
        * Destructor.
        */
        virtual ~Csapi_sendmessage();

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
        Csapi_sendmessage( CTestModuleIf& aTestModuleIf );

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
         
        virtual TInt sendmessage_test1L( CStifItemParser& aItem );
        virtual TInt sendmessage_test2L( CStifItemParser& aItem );
        virtual TInt sendmessage_test3L( CStifItemParser& aItem );
        virtual TInt sendmessage_test4L( CStifItemParser& aItem );
        virtual TInt sendmessage_test5L( CStifItemParser& aItem );
        virtual TInt sendmessage_test6L( CStifItemParser& aItem );
        virtual TInt sendmessage_test7L( CStifItemParser& aItem );
        virtual TInt sendmessage_test8L( CStifItemParser& aItem );
        virtual TInt sendmessage_test9L( CStifItemParser& aItem );
        virtual TInt sendmessage_test10L( CStifItemParser& aItem );
                           
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

#endif      // STLPORT_ACCUM_H

// End of File
