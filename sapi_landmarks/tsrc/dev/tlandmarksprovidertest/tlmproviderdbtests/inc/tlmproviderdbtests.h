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




#ifndef TLMPROVIDERDBTESTS_H__
#define TLMPROVIDERDBTESTS_H__

//  INCLUDES
#include <StifLogger.h>
#include <TestScripterInternal.h>
#include <StifTestModule.h>

class CPosLmDatabaseManager;
class MLiwNotifyCallback;
class CLiwGenericParamList;
class CLiwServiceHandler;
// Logging path
_LIT( KTLocTestLogPath, "\\logs\\testframework\\" ); 
// Log file
_LIT( KTLocTestLogFile, "tlmdbmoduletests.txt" ); 



/**
*  TLmDbmoduletest test class for STIF Test Framework TestScripter.
*  ?other_description_lines
*
*  @lib ?library
*  @since ?Series60_version
*/
NONSHARABLE_CLASS(CTLmDbTests) : public CScriptBase
    {
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        */
        static CTLmDbTests* NewL( CTestModuleIf& aTestModuleIf );

        /**
        * Destructor.
        */
        virtual ~CTLmDbTests();

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
        CTLmDbTests( CTestModuleIf& aTestModuleIf );

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
        
        virtual TInt AddDatabasePos(CStifItemParser &aItem );
		virtual TInt AddExistingDatabasePos(CStifItemParser &aItem );
        virtual TInt DeleteDatabasePos(CStifItemParser &aItem );
        virtual TInt AddInvalidDatabasePos(CStifItemParser &aItem );
        virtual TInt AddRemoteDatabasePos(CStifItemParser &aItem );
		virtual TInt UpdateDatabasePos(CStifItemParser &aItem );
	    virtual TInt GetDbListPos(CStifItemParser &aItem );
        
        TInt CheckErrorCode (const CLiwGenericParamList& aOutList, TInt32 &aError );
//		void ResetParams ();
   		void CreateInterfaceL(CLiwServiceHandler*& aHandler,
								MLiwInterface*& aInterface);

    private:
    	
    	CPosLmDatabaseManager* 	iDatabaseManager;
    };
    
#endif      // TLMPROVIDERDBTESTS_H__

// End of File
