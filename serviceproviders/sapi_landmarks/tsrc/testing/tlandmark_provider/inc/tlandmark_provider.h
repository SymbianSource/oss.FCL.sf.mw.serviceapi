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




#ifndef TLANDMARK_PROVIDER_H
#define TLANDMARK_PROVIDER_H

//  INCLUDES
#include <StifLogger.h>
#include <TestScripterInternal.h>
#include <StifTestModule.h>


// CONSTANTS
//const ?type ?constant_var = ?constant;

// MACROS
//#define ?macro ?macro_def
// Logging path
//_LIT( Ktlandmark_providerLogPath, "\\logs\\testframework\\tlandmark_provider\\" ); 
//_LIT( Ktlandmark_providerLogPath, "\\logs\\testframework\\" ); 
_LIT( Ktlandmark_providerLogPath, "\\logs\\" ); 
// Log file
_LIT( Ktlandmark_providerLogFile, "tlandmark_provider.txt" ); 
_LIT( Ktlandmark_providerLogFileWithTitle, "tlandmark_provider_[%S].txt" );
_LIT(KTestDbUri, "c:test1.ldb" );
_LIT(KTestDbUri1, "c:default.ldb" );

// FUNCTION PROTOTYPES
//?type ?function_name(?arg_list);

// FORWARD DECLARATIONS
//class ?FORWARD_CLASSNAME;
class Ctlandmark_provider;
class CLiwServiceHandler;
class CPosLandmarkDatabase;
class CPosLmCategoryManager;
class CPosLmDatabaseManager;

// DATA TYPES
//enum ?declaration
//typedef ?declaration
//extern ?data_type;

// CLASS DECLARATION

/**
*  Ctlandmark_provider test class for STIF Test Framework TestScripter.
*  ?other_description_lines
*
*  @lib ?library
*  @since ?Series60_version
*/
NONSHARABLE_CLASS(Ctlandmark_provider) : public CScriptBase
    {
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        */
        static Ctlandmark_provider* NewL( CTestModuleIf& aTestModuleIf );

        /**
        * Destructor.
        */
        virtual ~Ctlandmark_provider();

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
        Ctlandmark_provider( CTestModuleIf& aTestModuleIf );

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
        virtual TInt TestNoTid( CStifItemParser& aItem );
        virtual TInt TestInvalidTid( CStifItemParser& aItem );
        virtual TInt TestTidByorder( CStifItemParser& aItem );
        virtual TInt TestTidByPos( CStifItemParser& aItem );
        virtual TInt TestHugeTid( CStifItemParser& aItem );
        virtual TInt TestTidInvalidType( CStifItemParser& aItem );
        virtual TInt TestCancelInvalidCmdOption( CStifItemParser& aItem );
        
        virtual TInt TestAddLMVarByOrder( CStifItemParser& aItem );
        virtual TInt TestAddLMVarByPos( CStifItemParser& aItem );
        virtual TInt TestAddCTVarByOrder( CStifItemParser& aItem );
        virtual TInt TestAddCTVarByPos( CStifItemParser& aItem );
        
        virtual TInt TestGetListLMVarByOrder( CStifItemParser& aItem );
        virtual TInt TestGetListLMVarByPos( CStifItemParser& aItem );
        virtual TInt TestGetListCTVarByOrder ( CStifItemParser& aItem );
        virtual TInt TestGetListCTVarByPos( CStifItemParser& aItem );
        
        virtual TInt TestRemoveLMVarByOrder( CStifItemParser& aItem );
        virtual TInt TestRemoveLMVarByPos( CStifItemParser& aItem );
        virtual TInt TestRemoveCTVarByOrder ( CStifItemParser& aItem );
        virtual TInt TestRemoveCTVarByPos( CStifItemParser& aItem );
        
        virtual TInt TestExportVarByOrder( CStifItemParser& aItem );
        virtual TInt TestExportVarByPos( CStifItemParser& aItem );
        
        virtual TInt TestImportVarByOrder( CStifItemParser& aItem );
        virtual TInt TestImportVarByPos( CStifItemParser& aItem );
        
        virtual TInt TestOrganiseVarByOrder( CStifItemParser& aItem );
        virtual TInt TestOrganiseVarByPos( CStifItemParser& aItem );
        
        virtual TInt TestInvalidServiceDataSourceCombination( CStifItemParser& aItem );
        
        virtual TInt TestAddSyncAsyncbitcheck( CStifItemParser& aItem );
        virtual TInt TestGetListSyncAsyncbitcheck( CStifItemParser& aItem );
        
        virtual TInt TestGetListCancel ( CStifItemParser& aItem );
        virtual TInt GetListStressTest ( CStifItemParser& aItem );
        
        virtual TInt GetListIteratorTestLM ( CStifItemParser& aItem );
        virtual TInt GetListIteratorTestCT ( CStifItemParser& aItem );
        
        virtual TInt TestTemplateInvalidCase ( CStifItemParser& aItem );
        virtual TInt TestTemplateLM ( CStifItemParser& aItem );
        virtual TInt TestTemplateCT( CStifItemParser& aItem );
        
        virtual TInt TestGetListCTWithSortOrder( CStifItemParser& aItem );
        virtual TInt TestAddMultipleLM( CStifItemParser& aItem );
        
        virtual TInt ImportDBTypeIdCheck( CStifItemParser& aItem );
        virtual TInt ImportNullDB( CStifItemParser& aItem );
        
        virtual TInt AddSyncBitCheck( CStifItemParser& aItem );
        virtual TInt CombineAPI( CStifItemParser& aItem );
        
        virtual TInt AddVerifyTimeStamp( CStifItemParser& aItem );
        
        virtual TInt ExportHugeFilename( CStifItemParser& aItem );
        virtual TInt ExportNullFilename( CStifItemParser& aItem );
        virtual TInt ExportInvalidFilename( CStifItemParser& aItem );
			            
     //   virtual TInt AddLMInputValidation ( CStifItemParser& aItem );
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

#endif      // TLANDMARK_PROVIDER_H

// End of File
