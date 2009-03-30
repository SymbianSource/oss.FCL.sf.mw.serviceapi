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
* Description:   Tests sysinfo general feautures
*
*/




#ifndef TSYSGENERAL_H
#define TSYSGENERAL_H

//  INCLUDES
#include <StifLogger.h>
#include <TestScripterInternal.h>
#include <StifTestModule.h>
#include "sysinfoservice.h"
#include "sysinfo.h"

// CONSTANTS
//const ?type ?constant_var = ?constant;

// MACROS
//#define ?macro ?macro_def
// Logging path
_LIT( KtsysgeneralLogPath, "\\logs\\" ); 
// Log file
_LIT( KtsysgeneralLogFile, "tsysgeneral_t.txt" ); 

// FUNCTION PROTOTYPES
//?type ?function_name(?arg_list);

// FORWARD DECLARATIONS
//class ?FORWARD_CLASSNAME;
class Ctsysgeneral;
extern int TestAsyncStatus(CStifLogger* aLog) ;
extern int TestIpAndPredTextNot(CStifLogger* aLog) ;
// DATA TYPES
//enum ?declaration
//typedef ?declaration
//extern ?data_type;

// CLASS DECLARATION

/**
*  Ctsysgeneral test class for STIF Test Framework TestScripter.
*  ?other_description_lines
*
*  @lib ?library
*  @since ?Series60_version
*/
NONSHARABLE_CLASS(Ctsysgeneral) : public CScriptBase
    {
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        */
        static Ctsysgeneral* NewL( CTestModuleIf& aTestModuleIf );

        /**
        * Destructor.
        */
        virtual ~Ctsysgeneral();

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
        Ctsysgeneral( CTestModuleIf& aTestModuleIf );

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
        virtual TInt GetDisplayLanguage( CStifItemParser& aItem );
        virtual TInt SetWrongDataType( CStifItemParser& aItem );
        virtual TInt SetAndGetInputLanguage( CStifItemParser& aItem );
        virtual TInt SetAndGetPridictiveText( CStifItemParser& aItem );
        virtual TInt SetAndGetVibraActive( CStifItemParser& aItem );
        virtual TInt GetActiveUSBMode( CStifItemParser& aItem ) ;
        virtual TInt GetAvblUSBMode( CStifItemParser& aItem ) ;
        virtual TInt AsyncGetinfoStatus( CStifItemParser& aItem ) ;
        virtual TInt NotifyIpAndPredText(CStifItemParser& aItem ) ;
        virtual TInt SetWrongKey( CStifItemParser& aItem );
        virtual TInt SetWrongEntity( CStifItemParser& aItem );
        virtual TInt GetWrongKey( CStifItemParser& aItem );
        //ADD NEW METHOD DEC HERE

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

#endif      // TSYSGENERAL_H

// End of File
