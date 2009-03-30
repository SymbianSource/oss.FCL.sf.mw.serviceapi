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




#ifndef TCALTEST_H
#define TCALTEST_H

//  INCLUDES
#include <StifLogger.h>
#include <TestScripterInternal.h>
#include <StifTestModule.h>
#include<e32des16.h>

extern int AddEntryWithAllAttributes();
extern int AddMonthlyRepeatingEntry();
extern int ModifyRepeatRule();
extern int UpdateApptInstanceWithRepeat();
extern int UpdateEntryWithRDates();
extern int TestForLongStrings();

//#include <SAPI_TEST\testprg.h>
// CONSTANTS
//const ?type ?constant_var = ?constant;

// MACROS
//#define ?macro ?macro_def
// FUNCTION PROTOTYPES
//?type ?function_name(?arg_list);

// FORWARD DECLARATIONS
//class ?FORWARD_CLASSNAME;
class CTCalendarAddTest;

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
NONSHARABLE_CLASS(CTCalendarAddTest) : public CScriptBase
    {
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        */
        static CTCalendarAddTest* NewL( CTestModuleIf& aTestModuleIf );

        /**
        * Destructor.
        */
        virtual ~CTCalendarAddTest();

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
        CTCalendarAddTest( CTestModuleIf& aTestModuleIf );

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
        virtual TInt InterfaceClassL( CStifItemParser& aItem );
        virtual TInt AddNewCalendar(CStifItemParser &aItem );
        virtual TInt AddApptWithDailyRepeat(CStifItemParser &aItem );
        virtual TInt AddApptWithWeeklyRepeat(CStifItemParser &aItem );
        virtual TInt AddApptWithMonthlyRepeat(CStifItemParser &aItem );
        virtual TInt AddApptWithAttendees(CStifItemParser &aItem );
        virtual TInt AddNewAnniversary(CStifItemParser &aItem );
       	virtual TInt AddNewDayEvent(CStifItemParser &aItem );
       	virtual TInt AddNewReminder(CStifItemParser &aItem );
        virtual TInt AddNewTodo(CStifItemParser &aItem );
        virtual TInt AddAll(CStifItemParser &aItem );
        virtual TInt ModifyRepeat(CStifItemParser &aItem );
        virtual TInt AddEntryWithMonthlyRpt(CStifItemParser &aItem );
        virtual TInt UpdateInstanceWithRepeat(CStifItemParser &aItem );
        virtual TInt UpdateEntryWithRepeatDates(CStifItemParser &aItem );
        virtual TInt TestForLongStringsInEntry(CStifItemParser &aItem );
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
    
struct ParamPass
    {
    	CStifItemParser* it;
    	CStifLogger *log; 
    	//TInt CmdId ; // 0 for GetFiles and 1 GetFilesInfo
    	
    };
#endif      // TCALTEST_H

// End of File
