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




#ifndef TCAL_PROVIDERTEST_H
#define TCAL_PROVIDERTEST_H

//  INCLUDES
#include <StifLogger.h>
#include <TestScripterInternal.h>
#include <StifTestModule.h>

#include <liwcommon.h>
#include <liwvariant.h>
#include <liwservicehandler.h>
#include "calendarheader.h"
#include "calendarconstants.h"
#include <badesca.h>
// CONSTANTS
//const ?type ?constant_var = ?constant;

// MACROS
//#define ?macro ?macro_def
// Logging path
_LIT( Ktcal_providertestLogPath, "\\logs\\testframework\\" ); 
// Log file
_LIT( Ktcal_providertestLogFile, "tcal_providertest.txt" ); 
_LIT( Ktcal_providertestLogFileWithTitle, "tcal_providertest_[%S].txt" );

// FUNCTION PROTOTYPES
TInt RemoveProvCalendar(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar);
TInt AddProvCalendar(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar);
TInt AddProvAppointmentDailyRepeat(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset);
TInt AddProvEvent(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset);
TInt AddProvToDo(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset);
TInt AddAppointmentProvLocal(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset);
TInt GetLocalUid( CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar,TCalLocalUid& aOutLocalUid );
void GetGlobalUid( const TDesC& aGlobalUid, TDes8& aOutGlobalUid );

// FORWARD DECLARATIONS
//class ?FORWARD_CLASSNAME;
class Ctcal_providertest;

// DATA TYPES
//enum ?declaration
//typedef ?declaration
//extern ?data_type;

// CLASS DECLARATION

/**
*  Ctcal_providertest test class for STIF Test Framework TestScripter.
*  ?other_description_lines
*
*  @lib ?library
*  @since ?Series60_version
*/
NONSHARABLE_CLASS(Ctcal_providertest) : public CScriptBase
    {
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        */
        static Ctcal_providertest* NewL( CTestModuleIf& aTestModuleIf );

        /**
        * Destructor.
        */
        virtual ~Ctcal_providertest();

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
        Ctcal_providertest( CTestModuleIf& aTestModuleIf );

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
        virtual TInt RemoveFile( CStifItemParser& aItem );
        
        
        virtual TInt Calendar_ops1( CStifItemParser& aItem );
        virtual TInt Calendar_ops2( CStifItemParser& aItem );
        virtual TInt Calendar_ops3( CStifItemParser& aItem );
        virtual TInt Calendar_ops4( CStifItemParser& aItem );
        virtual TInt Calendar_ops5( CStifItemParser& aItem );
        virtual TInt Calendar_ops6( CStifItemParser& aItem );
        virtual TInt Calendar_ops7( CStifItemParser& aItem );
        virtual TInt Calendar_ops8( CStifItemParser& aItem );
        virtual TInt Calendar_ops9( CStifItemParser& aItem );
        virtual TInt Calendar_ops10( CStifItemParser& aItem );
        virtual TInt Calendar_ops11( CStifItemParser& aItem );
        virtual TInt Calendar_ops12( CStifItemParser& aItem );
        virtual TInt Calendar_ops13( CStifItemParser& aItem );
        virtual TInt Calendar_ops14( CStifItemParser& aItem );
        virtual TInt Calendar_ops15( CStifItemParser& aItem );
        virtual TInt Calendar_ops16( CStifItemParser& aItem );
        virtual TInt Calendar_ops17( CStifItemParser& aItem );
        
        //ADD NEW METHOD DEC HERE

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

#endif      // TCAL_PROVIDERTEST_H

// End of File
