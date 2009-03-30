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




#ifndef CLMCATEGORIESTEST_H
#define CLMCATEGORIESTEST_H

//  INCLUDES
#include <StifLogger.h>
#include <TestScripterInternal.h>
#include <StifTestModule.h>
#include <EPos_HPosLmDatabaseInfo.h> 
#include <EPos_CPosLmDatabaseManager.h> 
#include <epos_landmarks.h>
#include <EPos_CPosLandmarkCategory.h> 
#include <EPos_CPosLmCatNameCriteria.h> 
#include <epos_cposlmcategorymanager.h> 
#include <epos_cposlandmarkdatabase.h> 
#include "landmarkservice.h"
#include "mlandmarkobserver.h"

_LIT( KClmcategoriestestLogPath, "\\logs\\testframework\\Clmcategoriestest\\" ); 
_LIT( KClmcategoriestestLogFile, "Clmcategoriestest.txt" ); 

class CClmcategoriestest;


/**
*  CClmcategoriestest test class for STIF Test Framework TestScripter.
*  ?other_description_lines
*
*  @lib ?library
*  @since ?Series60_version
*/
NONSHARABLE_CLASS(CClmcategoriestest) : public CScriptBase, public MLandmarkObserver
    {
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        */
        static CClmcategoriestest* NewL( CTestModuleIf& aTestModuleIf );

        /**
        * Destructor.
        */
        virtual ~CClmcategoriestest();

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
        CClmcategoriestest( CTestModuleIf& aTestModuleIf );

        /**
        * By default Symbian 2nd phase constructor is private.
        */
        void ConstructL();

        /**
        * Frees all resources allocated from test methods.
        * @since ?Series60_version
        */
        void Delete();

        /**
        * Test methods are listed below. 
        */
		virtual TInt GetlistAsyncTest1(CStifItemParser &aItem );
		virtual TInt GetlistAsyncTest2(CStifItemParser &aItem );
		virtual TInt CategoryGetlistSync(CStifItemParser &aItem );
        virtual TInt AddCategoryL(CStifItemParser &aItem );
        virtual TInt UpdateCategoryL(CStifItemParser &aItem );
        virtual TInt RemoveCategoryL(CStifItemParser &aItem );
        virtual TInt LinkCategoryL(CStifItemParser &aItem );
        virtual TInt UnLinkCategoryL(CStifItemParser &aItem );

    public:     // Data
 
    protected:  // Data
        // MLandmarkObserver callback for catetories getlist iterator.
		void HandleCategoryItemsL( CPosLmItemIterator* aIterator,
            TInt32 aTransactionId, TInt aError, const TDesC& aDatabaseUri );
		// MLandmarkObserver callback for Landmarks getlist iterator.
		void HandleLandmarkItemsL( CPosLmItemIterator* aIterator,
            TInt32 aTransactionId, TInt aError, const TDesC& aDatabaseUri );

    private:    // Data
    	enum TestCaseId
    	{
    		ECategoryGetlist1=0,
    		ECategoryGetlist2,
    	};
    	
    	void CreateCategories ();
    	void RemoveAllCategories ( CPosLmCategoryManager* aHandle );

    public:     // Friend classes
        //?friend_class_declaration;
    protected:  // Friend classes
        //?friend_class_declaration;
    private:    // Friend classes
         CPosLmDatabaseManager* iDatabaseManager;
         CPosLandmarkDatabase*	iDefaultLmHandle;
		 CPosLmCategoryManager*	iDefaultCategoryHandle;
		 
         TInt iTestCaseId;
         TInt iResult;
    };

#endif      // CLMCATEGORIESTEST_H

// End of File
