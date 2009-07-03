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




#ifndef TLOGGING_H
#define TLOGGING_H

//  INCLUDES
#include <StifLogger.h>
#include <TestScripterInternal.h>
#include <StifTestModule.h>
#include <logview.h>
#include "loggingservice.h"


// CONSTANTS
//const ?type ?constant_var = ?constant;

// MACROS
//#define ?macro ?macro_def
// Logging path
_LIT( KtloggingLogPath, "\\logs\\testframework\\tlogging\\" ); 
// Log file
_LIT( KtloggingLogFile, "tlogging.txt" ); 

// FUNCTION PROTOTYPES
//?type ?function_name(?arg_list);

// FORWARD DECLARATIONS
//class ?FORWARD_CLASSNAME;
class Ctlogging;
class MLoggingCallback ;

// DATA TYPES
//enum ?declaration
//typedef ?declaration
//extern ?data_type;

// CLASS DECLARATION


/**
*  Ctlogging test class for STIF Test Framework TestScripter.
*  ?other_description_lines
*
*  @lib ?library
*  @since ?Series60_version
*/
NONSHARABLE_CLASS(Ctlogging) : public CScriptBase
    {
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        */
        static Ctlogging* NewL( CTestModuleIf& aTestModuleIf );

        /**
        * Destructor.
        */
        virtual ~Ctlogging();

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
        Ctlogging( CTestModuleIf& aTestModuleIf );

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
        //virtual TInt ExampleL( CStifItemParser& aItem );
        //ADD NEW METHOD DEC HERE
        //virtual TInt AddEventTest(CStifItemParser& aItem) ;
        virtual TInt GetListSimpleL(CStifItemParser& aItem) ;
        virtual TInt GetListAsyncL(CStifItemParser& aItem) ;
        
        // addsynctestcase
        virtual TInt AddEventSync1(CStifItemParser& aItem) ;
        virtual TInt AddEventSync2(CStifItemParser& aItem) ;
        virtual TInt AddEventSync3(CStifItemParser& aItem) ;
        virtual TInt AddEventSync4(CStifItemParser& aItem) ;
        virtual TInt AddEventSync5(CStifItemParser& aItem) ;
        
        //addasynctestcase
        virtual TInt AddEventAsync1(CStifItemParser& aItem) ;
        virtual TInt AddEventAsync2(CStifItemParser& aItem) ;
        virtual TInt AddEventAsync3(CStifItemParser& aItem) ;
        virtual TInt AddEventAsync4(CStifItemParser& aItem) ;
        virtual TInt AddEventAsync5(CStifItemParser& aItem) ;
        
        //deletesync
        virtual TInt DeleteEventSync(CStifItemParser& aItem) ;
        
        //deleteasync
        virtual TInt DeleteEventAsync(CStifItemParser& aItem) ;
        
        virtual TInt ConcurrentTestL1(CStifItemParser& aItem);
        virtual TInt ConcurrentTestL2(CStifItemParser& aItem);
        virtual TInt ConcurrentTestL3(CStifItemParser& aItem);
        virtual TInt ConcurrentTestL4(CStifItemParser& aItem);
        virtual TInt ConcurrentTestL5(CStifItemParser& aItem);
        virtual TInt ConcurrentTestL6(CStifItemParser& aItem);
        
        virtual TInt GetRecentListL1(CStifItemParser& aItem);
        virtual TInt GetRecentListL2(CStifItemParser& aItem);
        virtual TInt GetRecentListL3(CStifItemParser& aItem);
        
        virtual TInt GetEventL1(CStifItemParser& aItem);
        virtual TInt GetEventL2(CStifItemParser& aItem);
        virtual TInt GetEventL3(CStifItemParser& aItem);
       

    public: 
     /**
      * Add event test
      */
     // TInt AddEventTest(void) ;
      

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
    
  
TInt GetListSimple(void) ;  
TInt getlistasyncL1(void) ;

TInt concurrenttest1(void) ;
TInt concurrenttest2(void) ;
TInt concurrenttest3(void) ;
TInt concurrenttest4(void) ;
TInt concurrenttest5(void) ;
TInt concurrenttest6(void) ;

TInt getRecentList1(void) ;
TInt getRecentList2(void) ;
TInt getRecentlist3(void) ;

TInt getEvent1(void) ;
TInt getEvent2(void) ;
TInt getEvent3(void) ;

//addsynctest
TInt AddEventSync1(void);
TInt AddEventSync2(void);
TInt AddEventSync3(void);
TInt AddEventSync4(void);
TInt AddEventSync5(void);

//addasynctest
TInt AddEventasync1(void);
TInt AddEventasync2(void);
TInt AddEventasync3(void);
TInt AddEventasync4(void);
TInt AddEventasync5(void);

//delete
TInt DeleteEventsync(void);
TInt DeleteEventasync(void);
#endif      // TLOGGING_H

// End of File
