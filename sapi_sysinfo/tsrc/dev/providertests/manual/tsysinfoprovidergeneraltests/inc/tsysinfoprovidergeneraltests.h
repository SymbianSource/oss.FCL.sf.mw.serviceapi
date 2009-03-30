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
* Description:   tsysinfoprovidergeneraltests
*
*/




#ifndef TSYSINFOPROVIDERGENERALTESTSBLOCKS_H
#define TSYSINFOPROVIDERGENERALTESTSBLOCKS_H

//  INCLUDES
#include <StifLogger.h>
#include <TestScripterInternal.h>
#include <StifTestModule.h>
//#include <sendmessage.h>
#include<e32des16.h>
#include"sysinfoservice.h"


//#include <SAPI_TEST\testprg.h>
// CONSTANTS
const TInt	PASS(0);
const TInt	FAIL(!PASS);

// MACROS
//#define ?macro ?macro_def
// Logging path
_LIT( KTMsgTestLogPath, "\\logs\\testframework\\" ); 
// Log file
_LIT( KTMsgTestLogFile, "Tsysinfoprovidergeneral.txt" ); 

// FUNCTION PROTOTYPES
//?type ?function_name(?arg_list);

// FORWARD DECLARATIONS
//class ?FORWARD_CLASSNAME;
class CTSysInfoProviderGeneralTests;

// DATA TYPES
//enum ?declaration
//typedef ?declaration
//extern ?data_type;

// CLASS DECLARATION

/**
*  CTLocTest test class for STIF Test Framework TestScripter.
*  ?other_description_lines
*
*  @lib ?library
*  @since ?Series60_version
*/
extern int VibraNotification(int, char**);
extern int ConnectionNotification(CStifLogger* aLog);
extern int ConnList(CStifLogger* aLog);
extern int AccIter(CStifLogger* aLog);

NONSHARABLE_CLASS(CTSysInfoProviderGeneralTests) : public CScriptBase 
    {
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        */
        static CTSysInfoProviderGeneralTests* NewL( CTestModuleIf& aTestModuleIf );

        /**
        * Destructor.
        */
        virtual ~CTSysInfoProviderGeneralTests();

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
        CTSysInfoProviderGeneralTests( CTestModuleIf& aTestModuleIf );

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
       
        virtual TInt ConnectedAcc(CStifItemParser &aItem );
	    virtual TInt ConnNotification(CStifItemParser &aItem );

	    virtual TInt MemoryCardNotifierL(CStifItemParser &aItem );
		virtual TInt CriticalMemOnDriveCL(CStifItemParser &aItem );
		virtual TInt CriticalMemOnDriveDL(CStifItemParser &aItem );
		virtual TInt CriticalMemOnDriveEL(CStifItemParser &aItem );	    

		virtual TInt UserActivityNotifierL(CStifItemParser &aItem );
		virtual TInt UserInactivityNotifierL(CStifItemParser &aItem );
		
	    virtual TInt ConnectionList(CStifItemParser &aItem );
	    virtual TInt AccessoryList(CStifItemParser &aItem );
    public:     // Data
        
        //?data_declaration;

    protected:  // Data
        // ?one_line_short_description_of_data
        //?data_declaration;

    private:    // Data
        // CLocCoreImp Core class that contains all the location functionalities
       
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
    
   TInt SendMsg(TAny *Arg);
   TInt ChngStatus(TAny *Arg);

#endif      // TSYSINFOPROVIDERGENERALTESTSBLOCKS_H

// End of File
