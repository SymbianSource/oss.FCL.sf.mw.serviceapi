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




#ifndef TMSGTEST_H
#define TMSGTEST_H

//  INCLUDES
#include <StifLogger.h>
#include <TestScripterInternal.h>
#include <StifTestModule.h>
#include<e32des16.h>
//#include<messagenotify.h>
//#include<changestatus.h>


//#include <SAPI_TEST\testprg.h>
// CONSTANTS
//const ?type ?constant_var = ?constant;

// MACROS
//#define ?macro ?macro_def
// FUNCTION PROTOTYPES
//?type ?function_name(?arg_list);

// FORWARD DECLARATIONS
//class ?FORWARD_CLASSNAME;
class CTCalendarGetListTest;

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
NONSHARABLE_CLASS(CTCalendarGetListTest) : public CScriptBase
    {
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        */
        static CTCalendarGetListTest* NewL( CTestModuleIf& aTestModuleIf );

        /**
        * Destructor.
        */
        virtual ~CTCalendarGetListTest();

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
        CTCalendarGetListTest( CTestModuleIf& aTestModuleIf );

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
       
		virtual TInt GetListCalendar(CStifItemParser &aItem );
		virtual TInt GetDefaultCalendar(CStifItemParser &aItem );
		virtual TInt GetListGUidFilter(CStifItemParser &aItem );
		virtual TInt GetListLocalUidFilter(CStifItemParser &aItem );
		virtual TInt GetListTimeRangeFilter(CStifItemParser &aItem );
		virtual TInt GetListTextFilter(CStifItemParser &aItem );
		virtual TInt GetListTypeFilter(CStifItemParser &aItem );
		virtual TInt GetListInvalidLUID(CStifItemParser &aItem );
		virtual TInt GetListInvalidGUID(CStifItemParser &aItem );
		virtual TInt GetListInvalidCalName(CStifItemParser &aItem );
		
		virtual TInt GetListGUidFilterAsync(CStifItemParser &aItem );
        virtual TInt GetListLocalUidFilterAsync(CStifItemParser &aItem );
        virtual TInt GetListTimeRangeFilterAsync(CStifItemParser &aItem );
        virtual TInt GetListTextFilterAsync(CStifItemParser &aItem );
        virtual TInt GetListTypeFilterAsync(CStifItemParser &aItem );
        virtual TInt GetListInvalidGUidFilterAsync(CStifItemParser &aItem );
        virtual TInt GetListInvalidLocalUidFilterAsync(CStifItemParser &aItem );
        
        virtual TInt GetListGUidFilterCancelAsync(CStifItemParser &aItem );
        virtual TInt GetListLocalUidFilterCancelAsync(CStifItemParser &aItem );
        virtual TInt GetListTimeRangeFilterCancelAsync(CStifItemParser &aItem );
        virtual TInt GetListTextFilterCancelAsync(CStifItemParser &aItem );
        virtual TInt GetListTypeFilterCancelAsync(CStifItemParser &aItem );

	
    public:     // Data
        
        //?data_declaration;

    protected:  // Data
        // ?one_line_short_description_of_data
        //?data_declaration;

    private:    // Data
        // CLocCoreImp Core class that contains all the location functionalities
       
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
    

#endif      // TLOCTEST_H

// End of File
