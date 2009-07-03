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
* Description:  ?Description
*
*/



#ifndef ISERVICETESTMODULE_H
#define ISERVICETESTMODULE_H

//  INCLUDES
#include <StifLogger.h>
#include <TestScripterInternal.h>
#include <StifTestModule.h>

#include <LiwCommon.h>
#include <LiwBufferExtension.h>
#include <LiwServiceHandler.h>

// CONSTANTS
//const ?type ?constant_var = ?constant;

// MACROS
//#define ?macro ?macro_def
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( KIServiceTestModuleLogPath, "\\logs\\testframework\\" ); 
// Log file
_LIT( KIServiceTestModuleLogFile, "IServiceTestModule.txt" ); 
_LIT( KIServiceTestModuleLogFileWithTitle, "IServiceTestModule_[%S].txt" );

// FUNCTION PROTOTYPES
//?type ?function_name(?arg_list);

// FORWARD DECLARATIONS
//class ?FORWARD_CLASSNAME;
class CIServiceTestModule;

/**
 *  CIServiceTestModule test class for STIF Test Framework TestScripter.
 *  ?other_description_lines
 *
 *  @lib ?library
 *  @since ?Series60_version
 */
NONSHARABLE_CLASS(CIServiceTestModule) : public CScriptBase,public MLiwNotifyCallback
    {
    public:  // Constructors and destructor
        
       /**
        * Two-phased constructor.
        */
        static CIServiceTestModule* NewL( CTestModuleIf& aTestModuleIf );

        /**
        * Destructor.
        */
        virtual ~CIServiceTestModule();

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
        
        TInt HandleNotifyL(TInt aCmdId,
            	           TInt aEventId,
            	           CLiwGenericParamList& aEventParamList,
            	           const CLiwGenericParamList& aInParamList);
        
        void LoadServiceRegistry();
        

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
        CIServiceTestModule( CTestModuleIf& aTestModuleIf );

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
        virtual TInt GetMetaDataListL( CStifItemParser& aItem );
        
        CLiwDefaultMap* SetInputFilterL( CStifItemParser& aItem );
        
        void SetExpectedOutputMap( CStifItemParser& aItem );
        
        
        TBool CompareMaps(CLiwMap* aExpectedMap,
                          const CLiwMap* aResultMap);
                                       
                                       
                                       
        TBool CompareTRealResult(const TDesC8& aKey,
                                 CLiwMap* aExpectedMap,
                                 const CLiwMap* aResultMap);
        
        
        TBool CompareStringResult(const TDesC8& aKey,
                                  CLiwMap* aExpectedMap,
                                  const CLiwMap* aResultMap);
                                          
        
        TBool IsExpectedResult(CLiwIterable* aResultlist);
        
        TInt LoadProviderTest(CStifItemParser& aItem);
        TInt GetListTwice(CStifItemParser& aItem);
        TInt InvalidCommand(CStifItemParser& aItem);
        TInt CancelInvalidTransID(CStifItemParser& aItem);
        TInt InvalidServiceValue(CStifItemParser& aItem);
        TInt InvalidInterfaceValue(CStifItemParser& aItem);
        TInt InvalidMinVerValue(CStifItemParser& aItem);
        TInt InvalidMaxVerValue(CStifItemParser& aItem);
        TInt InvalidFilterValue(CStifItemParser& aItem);
       
        /**
         * Method used to log version of test class
         */
        void SendTestClassVersion();
 

    private: 
            CLiwServiceHandler* iServiceHandler;
            MLiwInterface* iIface;            
            CLiwCriteriaItem* iCriteria;
            RCriteriaArray iCriteriaArray;
                                    
            CLiwGenericParamList* iInparams;
            CLiwGenericParamList* iOutparams;   // Data
                        
            TInt iResult;
            TInt iExpectedError;    
            RPointerArray<CLiwMap> iExpectedOutPutArray;           
    };

#endif      // ISERVICETESTMODULE_H
