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




#ifndef TLANDMARKPROVIDER_H
#define TLANDMARKPROVIDER_H

//  INCLUDES
#include <StifLogger.h>
#include <TestScripterInternal.h>
#include <StifTestModule.h>

// CONSTANTS
//const ?type ?constant_var = ?constant;
//const ?type ?constant_var = ?constant;
_LIT8(KServiceDomain,"Service.Landmark");
_LIT8(KServiceName,"IDataSource");
_LIT(KTestDbUri, "c:test1.ldb" );
_LIT(KTestDbUri1, "c:default.ldb" );
_LIT(KTestDbUri2, "c:default1.ldb" );
// MACROS
//#define ?macro ?macro_def
// Logging path
_LIT( KTLandmarkProviderLogPath, "\\logs\\testframework\\" ); 
// Log file
_LIT( KTLandmarkProviderLogFile, "TLandmarkProvider.txt" ); 


// FUNCTION PROTOTYPES
//?type ?function_name(?arg_list);

// FORWARD DECLARATIONS
//class ?FORWARD_CLASSNAME;
class CTLandmarkProvider;
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
*  CTLandmarkProvider test class for STIF Test Framework TestScripter.
*  ?other_description_lines
*
*  @lib ?library
*  @since ?Series60_version
*/
NONSHARABLE_CLASS(CTLandmarkProvider) : public CScriptBase, 
										public MLiwNotifyCallback
    {
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        */
        static CTLandmarkProvider* NewL( CTestModuleIf& aTestModuleIf );

        /**
        * Destructor.
        */
        virtual ~CTLandmarkProvider();

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
        CTLandmarkProvider( CTestModuleIf& aTestModuleIf );

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
        void CreateLandmarksL (CPosLandmarkDatabase* aLandmarkHandle);
        void RemoveAllCategories ( CPosLmCategoryManager* aHandle );
        void RemoveAllLandmarks ( CPosLandmarkDatabase* aLandmarkHandle );
        TInt HandleNotifyL( TInt aCmdId, TInt aEventId,
            CLiwGenericParamList& aEventParamList,
            const CLiwGenericParamList& aInParamList);
        TInt CheckErrorCode( const CLiwGenericParamList& aOutList, TInt32& aError ) const ;
        void DeleteAllLocalDatabasesL();
   		void CreateInterfaceL(CLiwServiceHandler*& aHandler,
								MLiwInterface*& aInterface);

        /**
        * Example test method.
        * @since ?Series60_version
        * @param aItem Script line containing parameters.
        * @return Symbian OS error code.
        */
        virtual TInt AddLandmarkL( CStifItemParser& aItem );
        virtual TInt UpdateLandmarkL( CStifItemParser& aItem );
        virtual TInt RemoveLandmarkL( CStifItemParser& aItem );
        virtual TInt ImportLandmarkL( CStifItemParser& aItem );
        virtual TInt ExportLandmarkL( CStifItemParser& aItem );
        virtual TInt LinkCategoryL( CStifItemParser& aItem );
        virtual TInt UnLinkCategoryL( CStifItemParser& aItem );
        virtual TInt LandmarksAsyncTest1L( CStifItemParser& aItem );
        virtual TInt LandmarksSyncTest1L( CStifItemParser& aItem );
        virtual TInt ExampleL( CStifItemParser& aItem );
    	virtual TInt AddLandmarkDbL( CStifItemParser& aItem );
        virtual TInt UpdateLandmarkDbL( CStifItemParser& aItem );
        virtual TInt RemoveLandmarkDbL( CStifItemParser& aItem );
        virtual TInt ImportLandmarkDbL( CStifItemParser& aItem );
        virtual TInt ExportLandmarkDbL( CStifItemParser& aItem );
        virtual TInt LinkCategoryDbL( CStifItemParser& aItem );
        virtual TInt UnLinkCategoryDbL( CStifItemParser& aItem );
        virtual TInt LandmarksAsyncTest1DbL( CStifItemParser& aItem );
        virtual TInt LandmarksSyncTest1DbL( CStifItemParser& aItem );
        virtual TInt LandmarksGtkL( CStifItemParser& aItem );
        
        virtual TInt AddLandmarkPosL( CStifItemParser& aItem );
        virtual TInt UpdateLandmarkPosL( CStifItemParser& aItem );
        virtual TInt RemoveLandmarkPosL( CStifItemParser& aItem );
        virtual TInt ImportLandmarkPosL( CStifItemParser& aItem );
        virtual TInt ExportLandmarkPosL( CStifItemParser& aItem );
        virtual TInt LinkCategoryPosL( CStifItemParser& aItem );
        virtual TInt UnLinkCategoryPosL( CStifItemParser& aItem );
        virtual TInt LandmarksAsyncTestPos1L( CStifItemParser& aItem );
        virtual TInt LandmarksSyncTestPos1L( CStifItemParser& aItem );
    public:     // Data
        // ?one_line_short_description_of_data
        //?data_declaration;

    protected:  // Data
        // ?one_line_short_description_of_data
        //?data_declaration;

    private:    // Data
        
        //handle to the service handler for landmarks
         CLiwServiceHandler* iServiceHandler; 
        //handle to the service Interface for landmarks
        MLiwInterface* iIflandmarks;        
        
        // ?one_line_short_description_of_data
        //?data_declaration;

        // Reserved pointer for future extension
        //TAny* iReserved;

    public:     // Friend classes
        //?friend_class_declaration;
    protected:  // Friend classes
        //?friend_class_declaration;
    private:    // Friend classes
	CPosLmDatabaseManager* iDatabaseManager;

    };

#endif      // TLANDMARKPROVIDER_H

// End of File
