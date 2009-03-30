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




#ifndef LANDMARKS_INPUTPARAMS_H
#define LANDMARKS_INPUTPARAMS_H

//  INCLUDES
#include <StifLogger.h>
#include <TestScripterInternal.h>
#include <StifTestModule.h>

#include <liwcommon.h>

// MACROS
//#define ?macro ?macro_def
#define TEST_CLASS_VERSION_MAJOR 0
#define TEST_CLASS_VERSION_MINOR 0
#define TEST_CLASS_VERSION_BUILD 0

// Logging path
_LIT( Klandmarks_inputparamsLogPath, "\\logs\\testframework\\landmarks_inputparams\\" ); 
// Log file
_LIT( Klandmarks_inputparamsLogFile, "landmarks_inputparams.txt" ); 
_LIT( Klandmarks_inputparamsLogFileWithTitle, "landmarks_inputparams_[%S].txt" );

// FORWARD DECLARATIONS
//class ?FORWARD_CLASSNAME;
class Clandmarks_inputparams;
class CLiwServiceHandler;
class MLiwInterface;

// CLASS DECLARATION

/**
*  Clandmarks_inputparams test class for STIF Test Framework TestScripter.
*  ?other_description_lines
*
*  @lib ?library
*  @since ?Series60_version
*/
NONSHARABLE_CLASS(Clandmarks_inputparams) : public CScriptBase,
                                            public MLiwNotifyCallback
    {
    public: 
            enum TOperation
            {
                NoOp,
                Multiple,
                Default,
            };
            enum TType
            {
                NoType,
                Landmark,
                Category,
                Database,
            };
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        */
        static Clandmarks_inputparams* NewL( CTestModuleIf& aTestModuleIf );

        /**
        * Destructor.
        */
        virtual ~Clandmarks_inputparams();

   public: // Functions from base classes

        /**
        * From CScriptBase Runs a script line.
        * @since ?Series60_version
        * @param aItem Script line containing method name and parameters
        * @return Symbian OS error code
        */
        virtual TInt RunMethodL( CStifItemParser& aItem );

        virtual TInt HandleNotifyL(
                TInt aCmdId,
                TInt aEventId,
                CLiwGenericParamList& aEventParamList,
                const CLiwGenericParamList& aInParamList);
    private:

        /**
        * C++ default constructor.
        */
        Clandmarks_inputparams( CTestModuleIf& aTestModuleIf );

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
        void InitL();
        /**
         * Method used to log version of test class
         */
        void SendTestClassVersion();

        //ADD NEW METHOD DEC HERE
        //[TestMethods] - Do not remove
        /**
         * Example test method.
         * @since ?Series60_version
         * @param aItem Script line containing parameters.
         * @return Symbian OS error code.
         */
         virtual TInt GetListL( CStifItemParser& aItem );
         
         /**
          * Example test method.
          * @since ?Series60_version
          * @param aItem Script line containing parameters.
          * @return Symbian OS error code.
          */
         virtual TInt AddL( CStifItemParser& aItem );
          
         /**
          * Example test method.
          * @since ?Series60_version
          * @param aItem Script line containing parameters.
          * @return Symbian OS error code.
          */
         virtual TInt DeleteL( CStifItemParser& aItem ); 

         /**
          * Example test method.
          * @since ?Series60_version
          * @param aItem Script line containing parameters.
          * @return Symbian OS error code.
          */
         virtual TInt ImportL( CStifItemParser& aItem );

         /**
          * Example test method.
          * @since ?Series60_version
          * @param aItem Script line containing parameters.
          * @return Symbian OS error code.
          */
         virtual TInt ExportL( CStifItemParser& aItem );
         
         /**
          * Example test method.
          * @since ?Series60_version
          * @param aItem Script line containing parameters.
          * @return Symbian OS error code.
          */
         virtual TInt OrganiseL( CStifItemParser& aItem );
         
         /**
          * Example test method.
          * @since ?Series60_version
          * @param aItem Script line containing parameters.
          * @return Symbian OS error code.
          */
         virtual TInt CancelL( CStifItemParser& aItem );
         
         virtual TInt LiwL( CStifItemParser& aItem );
         
         TInt GetLandmarkL();
         TInt GetCategoryL();
         TInt GetDatabaseL();
         TInt GetLandmarkDefL();
         TInt GetCategoryDefL();
         TInt GetDatabaseDefL();
         TInt AddLandmarkL();
         TInt AddCategoryL();
         TInt DeleteLandmarkL();
         TInt DeleteCategoryL();
         TInt AddLmL( TInt32 count );
         TInt AddCatL( TInt32 count );
         TInt CheckAscending(TType aType, CLiwIterable* aIter);
         TInt CheckDescending(TType aType, CLiwIterable* aIter);
    private:    // Data
        
        // ?one_line_short_description_of_data
        //?data_declaration;
        CLiwServiceHandler*     iServiceHandler;
        MLiwInterface*          iLandmarkIf;
        TInt                    iResult;

    };

#endif      // LANDMARKS_INPUTPARAMS_H

// End of File
