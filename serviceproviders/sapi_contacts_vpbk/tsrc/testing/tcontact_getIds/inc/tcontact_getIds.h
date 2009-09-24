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




#ifndef TMANUALCONTACTS_H
#define TMANUALCONTACTS_H

//  INCLUDES
#include <StifLogger.h>
#include <TestScripterInternal.h>
#include <StifTestModule.h>
#include <stringloader.h>//for StringLoaderLC
#include <barsread.h>//resource reader
#include <aknnotewrappers.h>//for note
#include <cvpbkvcardeng.h>//for the vcard engin
#include <cvpbkcontactmanager.h>// for iContactManager
#include <mvpbkcontactstore.h>// for iContactStore
#include <tvpbkcontactstoreuriPtr.h>//used in SetupL
#include <mvpbkcontactstorelist.h>//used in SetupL to get contact stores
#include <mvpbkstorecontactfield.h>//used in AddFieldToContactL
#include <mvpbkstorecontact.h>// used in many function to get the store contact
#include <mvpbkcontactfieldtextdata.h>//for the field text data
#include <tvpbkfieldtypemapping.h>//used in CreateFieldTypeL()
#include <mvpbkfieldtype.h>//return type of CreateFieldTypeL()
#include <mvpbkcontactoperationbase.h>//for observer
#include <mvpbkcontactfielddatetimedata.h>//Used in AddDateFieldToContactL
#include <mvpbkcontactlink.h>//for param in ContactsSaved()
#include <cvpbkcontactstoreuriarray.h>//used in SetupL
#include "contactservice.h"
 #include<cntitem.h> 
 #include<cntdb.h>
 #include <e32base.h>
#include <e32cons.h>
#include<cntfldst.h> 
#include  "contactiter.h"
#include  "contactcallback.h"
#include <MVPbkStoreContact.h>
#include <MVpbkFieldType.h>
#include <VPbkEng.rsg>
#include <MVPbkStoreContact.h>


class CContactCallback : public MContactCallback
    {
    public:
        

        virtual void HandleReturnValue( TOperationEvent aEventId, const TInt& aError, TInt aTransId );
        
        virtual void HandleReturnIter( const TInt& aError, CContactIter* aIter, TInt aTransId );
        

        virtual void HandleReturnArray(const TInt& aError, RPointerArray<HBufC8>& aArray, TInt aTransId );
        virtual void HandleReturnId(const TInt& aError, HBufC8* aId, TInt aTransId );
	   TInt iError;      
    };


// CONSTANTS
//const ?type ?constant_var = ?constant;

// MACROS
//#define ?macro ?macro_def
// Logging path
_LIT( KtmanualcontactsLogPath, "\\logs\\testframework\\tmanualcontacts\\" ); 
// Log file
_LIT( KtmanualcontactsLogFile, "tmanualcontacts.txt" ); 


// FUNCTION PROTOTYPES
//?type ?function_name(?arg_list);

// FORWARD DECLARATIONS
//class ?FORWARD_CLASSNAME;
class Ctcontactgetids;

// DATA TYPES
//enum ?declaration
//typedef ?declaration
//extern ?data_type;

// CLASS DECLARATION

/**
*  Ctmanualcontacts test class for STIF Test Framework TestScripter.
*  ?other_description_lines
*
*  @lib ?library
*  @since ?Series60_version
*/
NONSHARABLE_CLASS(Ctcontactgetids) : public CScriptBase
    {
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        */
        static Ctcontactgetids* NewL( CTestModuleIf& aTestModuleIf );

        /**
        * Destructor.
        */
        virtual ~Ctcontactgetids();

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
        Ctcontactgetids( CTestModuleIf& aTestModuleIf );

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
        virtual TInt GetIds_Test1L( CStifItemParser& aItem );
        virtual TInt GetIds_Test2L( CStifItemParser& aItem );
        virtual TInt GetIds_Test3L( CStifItemParser& aItem );
        virtual TInt GetIds_Test4L( CStifItemParser& aItem );
        virtual TInt GetIds_Test5L( CStifItemParser& aItem );
        virtual TInt GetIds_Test6L( CStifItemParser& aItem ); 
        virtual TInt GetIds_Test7L( CStifItemParser& aItem ); 
        virtual TInt GetIds_Test8L( CStifItemParser& aItem );   
        virtual TInt GetIds_Test9L( CStifItemParser& aItem );
        virtual TInt AddContactL( CStifItemParser& aItem );
        virtual TInt AddGroupsL( CStifItemParser& aItem );
             
        //ADD NEW METHOD DEC HERE

    public:     // Data
        // ?one_line_short_description_of_data
        //?data_declaration;

    protected:  // Data
        // ?one_line_short_description_of_data
        //?data_declaration;

    private:    // Data
    
        CContactService* icontactservice;
        CContactCallback* icallback; 
        
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

#endif      // TMANUALCONTACTS_H

// End of File
