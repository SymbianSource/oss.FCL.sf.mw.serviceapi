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




#ifndef SENSRPROVIDERTEST_H
#define SENSRPROVIDERTEST_H

//  INCLUDES
#include <StifLogger.h>
#include <TestScripterInternal.h>
#include <StifTestModule.h>


#include <e32svr.h>
#include <f32file.h>
#include <StifParser.h>
#include <e32std.h>
#include <StifTestInterface.h>
#include <liwgenericparam.h>
#include <liwservicehandler.h>
#include <liwvariant.h>
#include <utf.h>

/*#include "sensorservice.h"
#include "sensorservice.hrh"
#include "sensrtestthread.h"*/

// Logging path
_LIT( KTSensrProviderLogPath, "\\logs\\testframework\\" ); 
// Log file
_LIT( KTSensrProviderLogFile, "sensrprovider.txt" ); 


_LIT8(KDataSource , "ISensor");
_LIT8(KService , "Service.Sensor") ;




// CLASS DECLARATION

/**
*  CSensrProviderTest test class for STIF Test Framework TestScripter.
*  ?other_description_lines
*
*  @lib ?library
*  @since ?Series60_version
*/
NONSHARABLE_CLASS(CSensrProviderTest) : public CScriptBase
    {
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        */
        static CSensrProviderTest* NewL( CTestModuleIf& aTestModuleIf );

        /**
        * Destructor.
        */
        virtual ~CSensrProviderTest();

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

    
    private:

        /**
        * C++ default constructor.
        */
        CSensrProviderTest( CTestModuleIf& aTestModuleIf );

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
        virtual TInt TestEcomDiscovery(CStifItemParser &aItem );
        virtual TInt TestFindSensorChannel(CStifItemParser &aItem );
        virtual TInt GeneralNeg1(CStifItemParser &aItem );
        virtual TInt GeneralNeg2(CStifItemParser &aItem );
        virtual TInt TestGetChannelProperty(CStifItemParser &aItem );
        virtual TInt TestRegisterForNotificationData(CStifItemParser &aItem );
    };
   
TInt GetChnlDataAsynch(TAny * aPtr);

#endif      // SENSRPROVIDERTEST_H

// End of File
