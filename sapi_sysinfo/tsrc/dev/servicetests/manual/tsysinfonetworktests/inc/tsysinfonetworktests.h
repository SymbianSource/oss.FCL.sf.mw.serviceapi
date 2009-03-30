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
* Description:   tsysinfonetworktests
*
*/




#ifndef _TSYSINFONETWORKTETS_H
#define _TSYSINFONETWORKTETS_H

//  INCLUDES
#include <StifLogger.h>
#include <TestScripterInternal.h>
#include <StifTestModule.h>
#include<e32des16.h>
#include "sysinfoservice.h"


const TInt	PASS(0);
const TInt	FAIL(!PASS);

// Logging path
_LIT( KTSysNetworkLogPath, "\\logs\\testframework\\" ); 
// Log file
_LIT( KTSysNetworkLogFile, "tsysinfonetworktests.txt" );
// CLASS DECLARATION

/**
*  CTSysInfoNetworkTests test class for STIF Test Framework TestScripter.
*  ?other_description_lines
*
*  @lib ?library
*  @since ?Series60_version
*/
NONSHARABLE_CLASS(CTSysInfoNetworkTests) : public CScriptBase,public ISystemObserver  
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
    ENWNetworkModeUnknown = -1,
    ENWNetworkModeGsm,
    ENWNetworkModeCdma,
    ENWNetworkModeWcdma
    };
        /**
        * Two-phased constructor.
        */
        static CTSysInfoNetworkTests* NewL( CTestModuleIf& aTestModuleIf );

        /**
        * Destructor.
        */
        virtual ~CTSysInfoNetworkTests();

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
        CTSysInfoNetworkTests( CTestModuleIf& aTestModuleIf );

        /**
        * By default Symbian 2nd phase constructor is private.
        */
        void ConstructL();

        void Delete();

        /**
        * Test methods are listed below. 
        */

	    virtual TInt RegisteredOnHomeNwL(CStifItemParser &aItem );
	    virtual TInt RegStatusNoServiceL(CStifItemParser &aItem );
	    virtual TInt GetNwModeGSML(CStifItemParser &aItem );
	    virtual TInt SignalStrengthAsyncL(CStifItemParser &aItem );
	    virtual TInt SignalLevelAsyncL(CStifItemParser &aItem );
	    virtual TInt SignalLevelNotiL(CStifItemParser &aItem );
	    virtual TInt SignalStrengthNotiL(CStifItemParser &aItem );

	    virtual TInt NetworkModeNotifyL(CStifItemParser &aItem );
	    virtual TInt RegStatusNotifyL(CStifItemParser &aItem );
	    virtual TInt HomeNwAsyncL(CStifItemParser &aItem );
   	    virtual TInt HomeNetworkNotifyL(CStifItemParser &aItem );
	    virtual TInt CurrentNwAsyncL(CStifItemParser &aItem );
	    virtual TInt CurrentNwNotiL(CStifItemParser &aItem );
   	    virtual TInt LACNotiL(CStifItemParser &aItem );
   	    virtual TInt CellIdNotifyL(CStifItemParser &aItem );
   	    virtual TInt CellIdAsyncL(CStifItemParser &aItem );
   	    virtual TInt LACAsyncL(CStifItemParser &aItem );

	private:
	 void HandleResponseL(const TDesC& aEntity,const TDesC& aKey,
	 					CSysData* aOutput, TInt32 aTransID, TSysRequest::TRequestType aType,TInt aError);
	
    };

#endif      // _TSYSINFONETWORKTETS_H

// End of File
