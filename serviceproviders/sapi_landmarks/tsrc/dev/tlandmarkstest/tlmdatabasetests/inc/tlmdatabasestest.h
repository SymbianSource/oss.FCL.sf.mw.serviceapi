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




#ifndef TLMDBTEST_H
#define TLMDBTEST_H

//  INCLUDES
#include <StifLogger.h>
#include <TestScripterInternal.h>
#include <StifTestModule.h>
#include <EPos_HPosLmDatabaseInfo.h> 
#include <EPos_CPosLmDatabaseManager.h> 
#include <EPos_Landmarks.h>

// MACROS
// Logging path
_LIT( KTLocTestLogPath, "\\logs\\testframework\\" ); 
// Log file
_LIT( KTLocTestLogFile, "TLmDbTest.txt" ); 


// FORWARD DECLARATIONS
//class ?FORWARD_CLASSNAME;
class CTLmDbTest;

// CLASS DECLARATION

/**
*  CTLmDbTest test class for STIF Test Framework TestScripter.
*  ?other_description_lines
*
*  @lib ?library
*  @since ?Series60_version
*/
NONSHARABLE_CLASS(CTLmDbTest) : public CScriptBase
    {
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        */
        static CTLmDbTest* NewL( CTestModuleIf& aTestModuleIf );

        /**
        * Destructor.
        */
        virtual ~CTLmDbTest();

    public: // Functions from base classes

        /**
        * From CScriptBase Runs a script line.
        * @since ?Series60_version
        * @param aItem Script line containing method name and parameters
        * @return Symbian OS error code
        */
        virtual TInt RunMethodL( CStifItemParser& aItem );

    private:

        /**
        * C++ default constructor.
        */
        CTLmDbTest( CTestModuleIf& aTestModuleIf );

        /**
        * By default Symbian 2nd phase constructor is private.
        */
        void ConstructL();

        /**
        * Frees all resources allocated from test methods.
        * @since ?Series60_version
        */
        void DeleteAllLocalDatabasesL();

        /**
        * Test methods are listed below. 
        */

        /**
        * Example test method.
        * @since ?Series60_version
        * @param aItem Script line containing parameters.
        * @return Symbian OS error code.
        */
        virtual TInt AddDatabase(CStifItemParser &aItem );
				virtual TInt AddExistingDatabase(CStifItemParser &aItem );
        virtual TInt DeleteDatabase(CStifItemParser &aItem );
        virtual TInt AddInvalidDatabase(CStifItemParser &aItem );
        virtual TInt AddRemoteDatabase(CStifItemParser &aItem );
				virtual TInt UpdateDatabase(CStifItemParser &aItem );
				virtual TInt SetActiveDb(CStifItemParser &aItem );
        virtual TInt GetDbList(CStifItemParser &aItem );

    public:     // Data
        

    protected:  // Data

    private:    // Data
       
            CPosLmDatabaseManager* iDatabaseManager;

    public:     // Friend classes
        //?friend_class_declaration;
    protected:  // Friend classes
        //?friend_class_declaration;
    private:    // Friend classes
    };
    
#endif      // TLMDBTEST_H

// End of File
