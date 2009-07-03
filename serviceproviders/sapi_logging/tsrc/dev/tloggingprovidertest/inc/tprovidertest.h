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




#ifndef TPROVIDERTEST_H
#define TPROVIDERTEST_H

//  INCLUDES
#include <StifLogger.h>
#include <TestScripterInternal.h>
#include <StifTestModule.h>

#include <LiwServiceHandler.h>
#include <LiwCommon.h>





// CONSTANTS
//const ?type ?constant_var = ?constant;

// MACROS
//#define ?macro ?macro_def
// Logging path
_LIT( KtprovidertestLogPath, "\\logs\\testframework\\tprovidertest\\" ); 
// Log file
_LIT( KtprovidertestLogFile, "tprovidertest.txt" ); 

// FUNCTION PROTOTYPES
//?type ?function_name(?arg_list);

// FORWARD DECLARATIONS
//class ?FORWARD_CLASSNAME;
class Ctprovidertest;
class CEventDetails;
class CFilterDetails;

// DATA TYPES
//enum ?declaration
//typedef ?declaration
//extern ?data_type;

// CLASS DECLARATION

/**
*  Ctprovidertest test class for STIF Test Framework TestScripter.
*  ?other_description_lines
*
*  @lib ?library
*  @since ?Series60_version
*/
NONSHARABLE_CLASS(Ctprovidertest) : public CScriptBase
    {
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        */
        static Ctprovidertest* NewL( CTestModuleIf& aTestModuleIf );

        /**
        * Destructor.
        */
        virtual ~Ctprovidertest();

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
        Ctprovidertest( CTestModuleIf& aTestModuleIf );

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
        virtual TInt ExampleL( CStifItemParser& aItem );
        
        /**
         * Test case for add functionality
         */
        virtual TInt AddTest1L( CStifItemParser& aItem );
        virtual TInt AddTest2L( CStifItemParser& aItem );
        virtual TInt AddGenericL( CStifItemParser& aItem );
        
        /**
         * Test case for delete functionality
         */
         
        virtual TInt DeletetestL( CStifItemParser& aItem )  ;
        
        /**
         * Testcase for GetListFunctionality
         */
         
        virtual TInt GetListGenericL(CStifItemParser& aItem);
        
        /**
         * Position based add test case
         */
        virtual TInt AddGenericPosL(CStifItemParser& aItem);
        
        /**
         *Position based delete testcase
         */
        virtual TInt DeleteGenericPosL (CStifItemParser& aItem) ;
        
        /**
         * Position based GetList testcase
         */
        virtual TInt GetListGenericPosL(CStifItemParser& aItem);
        
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
        void  taddtest1L(void) ;
        void  taddtest2L(void) ;
        void  tlogresultsL(const TLiwGenericParam *aGenericParam , TInt aRequestType) ;
        void  taddresultsL(const TLiwGenericParam *aGenericParam ) ;
        void  tlogGetListL(const TLiwGenericParam *aGenericParam ) ;
        void  taddgenericL(CEventDetails *aDetails,TInt aParsedValue) ;
        
        void  taddsyncgenericL(CEventDetails *aDetails);
        void  taddasyncgenericL(CEventDetails *aDetails);
        
        void  tdeleteTestL(TInt aExpected) ;
        void  tdeleteFunctionalL(void) ;
        void  tdeleteNegativeL(void) ;
        void tdeleteTestasyncL(TInt aExpected) ;
        void tdeleteFunctionalAsyncL(void) ;
        void tdeleteNegativeasyncL(void);
        
        void tdeleteAllEventsL(TInt val) ;
        void tdeleteAllEventsSyncL(void) ;
        void tdeleteAllEventsAsyncL(void) ;
        
        void  tgetlistgenericL( CFilterDetails *aDetails,TInt aParsedValue) ;
        void  tgetlistsyncgenericL(CFilterDetails *aDetails);
        void  tgetlistasyncgenericL(CFilterDetails *aDetails);
       
        
        /**
         *Position based test cases
         */
         
         void  taddgenericPosL(CEventDetails *aDetails,TInt aParsedValue) ;
         void  taddsyncgenericPosL(CEventDetails *aDetails);
         void  taddasyncgenericPosL(CEventDetails *aDetails);
         
         /**
          * Delete Position Based
          */

        void tdeleteTestPosL(TInt aExpected) ;
        void tdeleteFunctionalPosL(void) ;
        void tdeleteNegativePosL(void) ;
        void tdeleteTestasyncPosL(TInt aExpected) ;
        void tdeleteFunctionalAsyncPosL(void) ;
        void tdeleteNegativeasyncPosL(void);    
        
        /**
         * GetList Position Based test cases
         */
         void  tgetlistgenericPosL( CFilterDetails *aDetails,TInt aParsedValue) ;
        void  tgetlistsyncgenericPosL(CFilterDetails *aDetails);
        void  tgetlistasyncgenericPosL(CFilterDetails *aDetails);
         
    };

#endif      // TPROVIDERTEST_H

// End of File
