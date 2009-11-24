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




#ifndef TLOGPROVIDERTEST_H
#define TLOGPROVIDERTEST_H

//  INCLUDES
#include <StifLogger.h>
#include <TestScripterInternal.h>
#include <StifTestModule.h>
#include <liwservicehandler.h>
#include <liwcommon.h>










// CONSTANTS
//const ?type ?constant_var = ?constant;

// MACROS
//#define ?macro ?macro_def
// Logging path
_LIT( KtlogprovidertestLogPath, "\\logs\\testframework\\tlogprovidertest\\" ); 
// Log file
_LIT( KtlogprovidertestLogFile, "tlogprovidertest.txt" ); 
_LIT( KtlogprovidertestLogFileWithTitle, "tlogprovidertest_[%S].txt" );

// FUNCTION PROTOTYPES
//?type ?function_name(?arg_list);

// FORWARD DECLARATIONS
//class ?FORWARD_CLASSNAME;
class Ctlogprovidertest;
class CEventDetails;
class CFilterDetails;
class CLiwLogIter;
//class CFilterDetails;

// DATA TYPES
//enum ?declaration
//typedef ?declaration
//extern ?data_type;

// CLASS DECLARATION

/**
*  Ctlogprovidertest test class for STIF Test Framework TestScripter.
*  ?other_description_lines
*
*  @lib ?library
*  @since ?Series60_version
*/
NONSHARABLE_CLASS(Ctlogprovidertest) : public CScriptBase
    {
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        */
        static Ctlogprovidertest* NewL( CTestModuleIf& aTestModuleIf );

        /**
        * Destructor.
        */
        virtual ~Ctlogprovidertest();

    public: // New functions

    
    
     enum 
          {
			EIndex0 = 0 ,
			EIndex1 ,
			EIndex2 ,
			EIndex3 ,
          };/**
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
        Ctlogprovidertest( CTestModuleIf& aTestModuleIf );

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
        virtual TInt addL( CStifItemParser& aItem );
        virtual TInt add2L( CStifItemParser& aItem );
                virtual TInt get1L( CStifItemParser& aItem );
                virtual TInt get2L( CStifItemParser& aItem );
                     virtual TInt delete1L( CStifItemParser& aItem );
                     virtual TInt delete2L( CStifItemParser& aItem );
virtual TInt deleteneg1L( CStifItemParser& aItem );
virtual TInt cancel1L( CStifItemParser& aItem );
virtual TInt cancel2L( CStifItemParser& aItem );

                 virtual TInt sapierrorsL( CStifItemParser& aItem );
 virtual TInt wronginterfaceL( CStifItemParser& aItem );
 virtual TInt loadtwiceL( CStifItemParser& aItem );
 virtual TInt wrongcommandL( CStifItemParser& aItem );

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
  TInt addtest1L(CEventDetails *aDetails);
TInt   addtest2L(CEventDetails *aDetails);
TInt   getlist1L(CFilterDetails *aDetails);
TInt   getlist2L(CFilterDetails *aDetails);
TInt deletetest1L(CEventDetails *aDetails);
TInt deletetest1_0L(CEventDetails *aDetails);
TInt deletetest2L(CEventDetails *aDetails);
TInt cancel1_0L(CEventDetails *aDetails);
TInt cancel1_1L(CEventDetails *aDetails);

TInt   sapierrors();
TInt wronginterface1(CEventDetails *aDetails);
TInt loadtwice(CEventDetails *aDetails);
TInt wrongcommand(CEventDetails *aDetails);
#endif      // TLOGPROVIDERTEST_H

// End of File
