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




#ifndef CLMLANDMARKSTEST_H
#define CLMLANDMARKSTEST_H

//  INCLUDES
#include <StifLogger.h>
#include <TestScripterInternal.h>
#include <StifTestModule.h>
#include <EPos_HPosLmDatabaseInfo.h> 
#include <EPos_CPosLmDatabaseManager.h> 
#include <epos_landmarks.h>
#include <EPos_CPosLandmarkCategory.h> 
#include <EPos_CPosLmSearchCriteria.h>
#include <epos_cposlandmarkdatabase.h> 
#include "mlandmarkobserver.h"
#include "landmarkservice.h"

// CONSTANTS
//const ?type ?constant_var = ?constant;

// MACROS
//#define ?macro ?macro_def
// Logging path
_LIT( KClmlandmarkstestLogPath, "\\logs\\testframework\\Clmlandmarkstest\\" ); 
// Log file
_LIT( KClmlandmarkstestLogFile, "Clmlandmarkstest.txt" ); 

// FUNCTION PROTOTYPES
//?type ?function_name(?arg_list);

// FORWARD DECLARATIONS
//class ?FORWARD_CLASSNAME;
class CClmlandmarkstest;

// DATA TYPES
//enum ?declaration
//typedef ?declaration
//extern ?data_type;

// CLASS DECLARATION

/**
*  CClmlandmarkstest test class for STIF Test Framework TestScripter.
*  ?other_description_lines
*
*  @lib ?library
*  @since ?Series60_version
*/
NONSHARABLE_CLASS(CClmlandmarkstest) : public CScriptBase
    {
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        */
        static CClmlandmarkstest* NewL( CTestModuleIf& aTestModuleIf );

        /**
        * Destructor.
        */
        virtual ~CClmlandmarkstest();

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
        CClmlandmarkstest( CTestModuleIf& aTestModuleIf );

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
        virtual TInt AddLandmarkL(CStifItemParser &aItem );
        virtual TInt UpdateLandmarkL(CStifItemParser &aItem );
        virtual TInt RemoveLandmarkL(CStifItemParser &aItem );
        virtual TInt ImportLandmarkL(CStifItemParser &aItem );
        virtual TInt ExportLandmarkL(CStifItemParser &aItem );
        virtual TInt GetlistAsyncTest1(CStifItemParser &aItem );
        virtual TInt GetlistAsyncTest2(CStifItemParser &aItem );
        virtual TInt LandmarkGetlistSync( CStifItemParser &aItem );
        virtual TInt LandmarkGetlistGtk( CStifItemParser &aItem );
        enum TestCaseId
    		{
    		ELandmarksGetlist=0,
    		ECategoryGetlist,
    		};
    	
    		void RemoveAllLandmarks ( CPosLandmarkDatabase* aLandmarkHandle );

    public:     // Data
        // ?one_line_short_description_of_data
        //?data_declaration;

    protected:  // Data
        // ?one_line_short_description_of_data
        //?data_declaration;

    private:    // Data
        CPosLmDatabaseManager* iDatabaseManager;
        CPosLandmarkDatabase*	iDefaultLmHandle;
		TInt iTestCaseId;
    };

#endif      // CLMLANDMARKSTEST_H

// End of File
