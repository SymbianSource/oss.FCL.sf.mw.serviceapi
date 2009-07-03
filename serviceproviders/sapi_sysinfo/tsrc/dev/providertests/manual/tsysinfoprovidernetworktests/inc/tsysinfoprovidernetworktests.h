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




#ifndef _TSysInfoProviderNetworkTests_H
#define _TSysInfoProviderNetworkTests_H

//  INCLUDES
#include <StifLogger.h>
#include <TestScripterInternal.h>
#include <StifTestModule.h>
#include<e32des16.h>


const TInt	PASS(0);
const TInt	FAIL(!PASS);

// Logging path
_LIT( KTSysNetworkLogPath, "\\logs\\testframework\\" ); 
// Log file
_LIT( KTSysNetworkLogFile, "TSysNetwork.txt" );
extern int NetModeNotification(int, char**);
// CLASS DECLARATION

/**
*  CTSysInfoProviderNetworkTests test class for STIF Test Framework TestScripter.
*  ?other_description_lines
*
*  @lib ?library
*  @since ?Series60_version
*/
NONSHARABLE_CLASS(CTSysInfoProviderNetworkTests) : public CScriptBase 
    {
    public:  // Constructors and destructor
		enum
		{
			UNKNOWN = -1,
			NOSERVICE,
			EMERGENCY,
			NOTREGISTEREDSERCHING,
			REGISTEREDBUSY,
			REGISTEREDONHOMENW,
			REGISTRATIONDENIED,
			REGISTEREDROAMING,
		};
		enum
			{
	    UNKNOWNMODE =-1,
	    GSM,
	    CDMA,
	    WCDMA
	    };
        /**
        * Two-phased constructor.
        */
        static CTSysInfoProviderNetworkTests* NewL( CTestModuleIf& aTestModuleIf );

        /**
        * Destructor.
        */
        virtual ~CTSysInfoProviderNetworkTests();

    public: // Functions from base classes

        /**
        * From CScriptBase Runs a script line.
        * @since ?Series60_version
        * @param aItem Script line containing method name and parameters
        * @return Symbian OS error code
        */
        virtual TInt RunMethodL( CStifItemParser& aItem );

    protected:  // New functions

    private:

        /**
        * C++ default constructor.
        */
        CTSysInfoProviderNetworkTests( CTestModuleIf& aTestModuleIf );

        /**
        * By default Symbian 2nd phase constructor is private.
        */
        void ConstructL();

        void Delete();

        /**
        * Test methods are listed below. 
        */

	    virtual TInt RegisteredOnHomeNwL(CStifItemParser &aItem );
	    virtual TInt GetNwModeGSML(CStifItemParser &aItem );
	    virtual TInt SignalStrengthAsyncL(CStifItemParser &aItem );
	    virtual TInt SignalStrengthNotiL(CStifItemParser &aItem );

	    virtual TInt HomeNwAsyncL(CStifItemParser &aItem );
	    virtual TInt CurrentNwNotiL(CStifItemParser &aItem );

	private:
	
    };

#endif      // _TSysInfoProviderNetworkTests_H

// End of File
