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




#ifndef SAPILOCTEST_H
#define SAPILOCTEST_H

//  INCLUDES
#include <StifLogger.h>
#include <TestScripterInternal.h>
#include <StifTestModule.h>
//#include <S60LocCoreImpl.h>
//#include <s60locservice.h>
//#include <SAPI_TEST\testprg.h>
#include "locationservice.h" 
// CONSTANTS
//const ?type ?constant_var = ?constant;

 
// MACROS
//#define ?macro ?macro_def
// Logging path
_LIT( KSAPILocTestLogPath, "\\logs\\testframework\\SAPILocTest\\" ); 
// Log file
_LIT( KSAPILocTestLogFile, "SAPILocTest.txt" ); 

//_LIT(LogFileName1 , "C:\\SAPILocation.txt") ;
// FUNCTION PROTOTYPES
//?type ?function_name(?arg_list);

// FORWARD DECLARATIONS
//class ?FORWARD_CLASSNAME;
class CSAPILocTest;




// DATA TYPES
//enum ?declaration
//typedef ?declaration
//extern ?data_type;

// CLASS DECLARATION

/**
*  CSAPILocTest test class for STIF Test Framework TestScripter.
*  ?other_description_lines
*
*  @lib ?library
*  @since ?Series60_version
*/
NONSHARABLE_CLASS(CSAPILocTest) : public CScriptBase
    {
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        */
        static CSAPILocTest* NewL( CTestModuleIf& aTestModuleIf );

        /**
        * Destructor.
        */
        virtual ~CSAPILocTest();

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
        CSAPILocTest( CTestModuleIf& aTestModuleIf );

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
       // virtual TInt ExampleL( CStifItemParser& aItem );
        virtual TInt CreateLocObjWSer(CStifItemParser &aItem );
        virtual TInt CreateLocObjs(CStifItemParser &aItem );
     // virtual TInt CreateLocObjWOSer(CStifItemParser &aItem );
        virtual TInt GetPosition(CStifItemParser &aItem );
        virtual TInt GetPosition1(CStifItemParser &aItem );
        virtual TInt GetPosition2(CStifItemParser &aItem );
     // virtual TInt GetPositionTO(CStifItemParser &aItem );
        virtual TInt GetPositionAsync(CStifItemParser &aItem );
     // virtual TInt GetPositionAsyncTO(CStifItemParser &aItem );
     // virtual TInt GetPositionAsyncOpts(CStifItemParser &aItem );
        virtual TInt GetPositionAsyncOpts1(CStifItemParser &aItem );
        virtual TInt GetPositionAsyncOpts2(CStifItemParser &aItem );
        virtual TInt GetPositionAsyncOpts3(CStifItemParser &aItem );
        virtual TInt GetPositionAsyncOpts4(CStifItemParser &aItem );
        virtual TInt GetPositionAsyncOpts5(CStifItemParser &aItem );
        virtual TInt GetPositionAsyncOpts6(CStifItemParser &aItem );
        virtual TInt TraceLPosition(CStifItemParser &aItem );
        virtual TInt TraceLPosition1(CStifItemParser &aItem );
     // virtual TInt TraceLPositionTO(CStifItemParser &aItem );
        virtual TInt TraceLPosition2(CStifItemParser &aItem );
        virtual TInt TraceLPosition3(CStifItemParser &aItem );
        virtual TInt TraceLPosition4(CStifItemParser &aItem );
        virtual TInt TraceLPosition5(CStifItemParser &aItem );
        virtual TInt TraceLPosition6(CStifItemParser &aItem );
        virtual TInt TraceLPosition7(CStifItemParser &aItem );
        virtual TInt TraceLPosition8(CStifItemParser &aItem );
        virtual TInt TraceLPositionOpts(CStifItemParser &aItem );
        virtual TInt TraceLPositionOpts1(CStifItemParser &aItem );
        virtual TInt TraceLPositionOpts2(CStifItemParser &aItem );
        virtual TInt TraceLPositionOpts3(CStifItemParser &aItem );
        virtual TInt CancelService1(CStifItemParser &aItem );
        virtual TInt CancelService2(CStifItemParser &aItem );
        virtual TInt GetTime(CStifItemParser &aItem );
        virtual TInt GetSpeed(CStifItemParser &aItem );
        virtual TInt GetPositionOpts(CStifItemParser &aItem );
        virtual TInt GetPositionOpts1(CStifItemParser &aItem );
        virtual TInt GetPositionOpts2(CStifItemParser &aItem );
        virtual TInt GetPositionOpts3(CStifItemParser &aItem );
        virtual TInt GetPositionOpts4(CStifItemParser &aItem );
        virtual TInt GetPositionOpts5(CStifItemParser &aItem );
     // virtual TInt GetLastPosition(CStifItemParser &aItem );
     // virtual TInt GetLastPosition1(CStifItemParser &aItem );
        virtual TInt GetDistance(CStifItemParser &aItem );
        virtual TInt GetDistance2(CStifItemParser &aItem );
        virtual TInt GetDistance3(CStifItemParser &aItem );
        virtual TInt GetDistance4(CStifItemParser &aItem );
        virtual TInt GetDistance5(CStifItemParser &aItem );
        virtual TInt GetDistance6(CStifItemParser &aItem );
        virtual TInt GetDistance7(CStifItemParser &aItem );
        virtual TInt GetDistance8(CStifItemParser &aItem );
        virtual TInt GetDistance9(CStifItemParser &aItem );
        virtual TInt GetDistance10(CStifItemParser &aItem );
        virtual TInt GetDistance11(CStifItemParser &aItem );
        virtual TInt GetDistance12(CStifItemParser &aItem );
        virtual TInt GetBearing(CStifItemParser &aItem );
        virtual TInt GetBearing1(CStifItemParser &aItem );
        virtual TInt GetBearing2(CStifItemParser &aItem );
        virtual TInt GetBearing3(CStifItemParser &aItem );
        virtual TInt GetBearing4(CStifItemParser &aItem );
        virtual TInt GetBearing5(CStifItemParser &aItem );
        virtual TInt GetBearing6(CStifItemParser &aItem );
        virtual TInt GetBearing7(CStifItemParser &aItem );
        virtual TInt GetBearing8(CStifItemParser &aItem );
        virtual TInt GetBearing9(CStifItemParser &aItem );
        virtual TInt GetBearing10(CStifItemParser &aItem );
        virtual TInt GetBearing11(CStifItemParser &aItem );
        virtual TInt GetBearing12(CStifItemParser &aItem );
        virtual TInt GetBearing13(CStifItemParser &aItem );
        virtual TInt GetBearing14(CStifItemParser &aItem );
        virtual TInt Move1(CStifItemParser &aItem );
        virtual TInt Move2(CStifItemParser &aItem );
        virtual TInt Move3(CStifItemParser &aItem );
        virtual TInt Move4(CStifItemParser &aItem );
        virtual TInt Move5(CStifItemParser &aItem );
        virtual TInt Move6(CStifItemParser &aItem );
        virtual TInt Move7(CStifItemParser &aItem );
        virtual TInt Move8(CStifItemParser &aItem );
        virtual TInt Modinfo1(CStifItemParser &aItem );
        
       // virtual TInt ValidatePosition(TPosition& aPos);
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

TInt TraceLPosition6T(TAny */*Arg*/);
TInt threadFunc1(TAny */*Arg*/);
TInt threadFuncTO(TAny */*Arg*/);
TInt threadFunc2(TAny */*Arg*/);
TInt threadFuncOpts1(TAny */*Arg*/);
TInt threadFuncOpts2(TAny */*Arg*/);
TInt threadFuncOpts3(TAny */*Arg*/);
TInt threadFuncOpts4(TAny */*Arg*/);
TInt threadFuncOpts5(TAny */*Arg*/);
TInt threadFuncOpts6(TAny */*Arg*/);
TInt threadTraceL(TAny */*Arg*/);
TInt threadTraceL1(TAny */*Arg*/);
TInt threadTraceLTO(TAny */*Arg*/);
TInt threadTraceL2(TAny */*Arg*/);
TInt threadTraceL3(TAny */*Arg*/);
TInt threadTraceL4(TAny */*Arg*/);
TInt threadTraceLOpts(TAny */*Arg*/);
TInt threadTraceLOpts1(TAny */*Arg*/);
TInt threadTraceLOpts2(TAny */*Arg*/);
TInt threadTraceLOpts3(TAny */*Arg*/);
TInt threadCancel1(TAny */*Arg*/);
TInt threadCancel2(TAny */*Arg*/);
TInt ModinfoFunctionL();
TInt ValidatePosition(TPosition& aPos);
void OpenFile();
void CloseFile();
void ValidatePosition1(TPosition& aPos);

#endif      // SAPILOCTEST_H

// End of File
