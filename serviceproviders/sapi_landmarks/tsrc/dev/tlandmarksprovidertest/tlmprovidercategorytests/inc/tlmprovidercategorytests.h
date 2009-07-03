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




#ifndef TLMPROVIDERCATEGORYTESTS_H__
#define TLMPROVIDERCATEGORYTESTS_H__

//  INCLUDES
#include <StifLogger.h>
#include <TestScripterInternal.h>
#include <StifTestModule.h>

class CPosLmCategoryManager;
class CLiwGenericParamList;
class CLiwServiceHandler;
class CPosLmDatabaseManager;
// Logging path
_LIT( KTLocTestLogPath, "\\logs\\testframework\\" ); 
// Log file
_LIT( KTLocTestLogFile, "tlmprovidercattests.txt" ); 

/**
*  CTLmCategoryTests test class for STIF Test Framework TestScripter.
*  ?other_description_lines
*
*  @lib ?library
*  @since ?Series60_version
*/
NONSHARABLE_CLASS(CTLmCategoryTests) : 	public CScriptBase, 
										public MLiwNotifyCallback
    {
    public:  // Constructors and destructor
		enum AsyncTestID
		{
			ETEST1,
			ETEST2,
			ETEST3,
		};
        /**
        * Two-phased constructor.
        */
        static CTLmCategoryTests* NewL( CTestModuleIf& aTestModuleIf );

        /**
        * Destructor.
        */
        virtual ~CTLmCategoryTests();

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
        CTLmCategoryTests( CTestModuleIf& aTestModuleIf );

        /**
        * By default Symbian 2nd phase constructor is private.
        */
        void ConstructL();

        /**
        * Test methods are listed below. 
        */
        virtual TInt AddCategoryL(CStifItemParser &aItem );
        virtual TInt AddCategory1L(CStifItemParser &aItem );
		virtual TInt UpdateCategoryL(CStifItemParser &aItem );
		virtual TInt UpdateCategory1L( CStifItemParser& aItem );
		virtual TInt CategoryAsyncTest1(CStifItemParser &aItem );
		virtual TInt CategoryAsyncTest2(CStifItemParser &aItem );
		virtual TInt CategorySyncTest1(CStifItemParser &aItem );
		virtual TInt CategorySyncTest2(CStifItemParser &aItem );
		virtual TInt RemoveCategoryL(CStifItemParser &aItem );
		virtual TInt RemoveCategory1L(CStifItemParser &aItem );
		virtual TInt CancelAsyncTest1(CStifItemParser &aItem );
		TInt HandleAsyncTest1 (const CLiwGenericParamList& );
		TInt HandleAsyncTest2 (const CLiwGenericParamList& );
		
		virtual TInt AddCategoryPosL(CStifItemParser &aItem );
    	virtual TInt UpdateCategoryPosL(CStifItemParser &aItem );
		virtual TInt CategoryAsyncTestPos1(CStifItemParser &aItem );
		virtual TInt CategorySyncTestPos1(CStifItemParser &aItem );
		virtual TInt RemoveCategoryPosL(CStifItemParser &aItem );
	private:
        TInt CheckErrorCode (const CLiwGenericParamList& aOutList, TInt32 &aError );
        void CreateCategoriesL (CPosLmCategoryManager* aHandle);
        void CreateCategoriesOtherL (CPosLmCategoryManager* aHandle);
        void DeleteAllLocalDatabasesL(void);
        void RemoveAllCategoriesL(CPosLmCategoryManager* );
		void ResetParams ();
		HBufC* GetCatNameLC (const CLiwMap* );
   		void CreateInterfaceL(CLiwServiceHandler*& aHandler,
								MLiwInterface*& aInterface);
	protected:
	        TInt HandleNotifyL(
            TInt aCmdId,
            TInt aEventId,
            CLiwGenericParamList& aEventParamList,
            const CLiwGenericParamList& aInParamList);
    private:
    	CPosLmDatabaseManager* 	iDatabaseManager;    	
    	CLiwServiceHandler*		iServiceHandler;
    	CLiwGenericParamList*	iInList;
    	CLiwGenericParamList*	iOutList;    	
    	MLiwInterface*			iLandmarkIf;
    	AsyncTestID				iTestID;
    	TInt 					iResult;
    	TInt					iAsyncCallCnt;
    };
    
#endif      // TLMPROVIDERCATEGORYTESTS_H__

// End of File
