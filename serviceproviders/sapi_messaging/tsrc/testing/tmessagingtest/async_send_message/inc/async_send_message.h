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




#ifndef ASYNC_SEND_MESSAGE_H
#define ASYNC_SEND_MESSAGE_H

//  INCLUDES
//#include <StifLogger.h>
#include <TestScripterInternal.h>
#include <StifTestModule.h>


// CONSTANTS
//const ?type ?constant_var = ?constant;

// MACROS
//#define ?macro ?macro_def
// Logging path
//_LIT( Kasync_send_messageLogPath, "\\logs\\testframework\\async_send_message\\" ); 
// Log file
//_LIT( Kasync_send_messageLogFile, "async_send_message.txt" ); 

// FUNCTION PROTOTYPES
//?type ?function_name(?arg_list);

// FORWARD DECLARATIONS
//class ?FORWARD_CLASSNAME;
class Casync_send_message;

// DATA TYPES
//enum ?declaration
//typedef ?declaration
//extern ?data_type;

// CLASS DECLARATION

/**
*  Casync_send_message test class for STIF Test Framework TestScripter.
*  ?other_description_lines
*
*  @lib ?library
*  @since ?Series60_version
*/
NONSHARABLE_CLASS(Casync_send_message) : public CScriptBase
    {
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        */
        static Casync_send_message* NewL( CTestModuleIf& aTestModuleIf );

        /**
        * Destructor.
        */
        virtual ~Casync_send_message();

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
        Casync_send_message( CTestModuleIf& aTestModuleIf );

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
                virtual TInt Test1L( CStifItemParser& aItem );
        
        		TInt Casync_send_message::fromarray_func(CStifItemParser& aItem,TPtrC& fromarray); 
				TInt Casync_send_message::messtype_func(CStifItemParser& aItem,TPtrC& messtype);   
				TInt Casync_send_message::subject_func(CStifItemParser& aItem,TPtrC& subj);
			    TInt Casync_send_message::attach_func(CStifItemParser& aItem,TPtrC& attachm);
			    TInt Casync_send_message::attachtype_func(CStifItemParser& aItem,TPtrC& attachfiletype); 
			    TInt Casync_send_message::body_func(CStifItemParser& aItem,TPtrC& body);
			    TInt Casync_send_message::template_func(CStifItemParser& aItem,TInt& templateid);
				TInt Casync_send_message::editor_func(CStifItemParser& aItem,TInt& editorl);
				TInt Casync_send_message::flag_func(CStifItemParser& aItem,TInt& flag); 
				TInt Casync_send_message::sender_func(CStifItemParser& aItem,TPtrC& sender);
				TInt Casync_send_message::rec_func(CStifItemParser& aItem,TPtrC& recarray);        
				TInt Casync_send_message::messageid_func(CStifItemParser& aItem,TInt& id);

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

#endif      // ASYNC_SEND_MESSAGE_H

// End of File
