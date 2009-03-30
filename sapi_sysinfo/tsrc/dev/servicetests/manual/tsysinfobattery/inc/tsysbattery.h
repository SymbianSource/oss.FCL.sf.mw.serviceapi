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




#ifndef TSYSBATTERY_H
#define TSYSBATTERY_H

//  INCLUDES
#include <StifLogger.h>
#include <TestScripterInternal.h>
#include <StifTestModule.h>
#include <e32des16.h>
#include "sysinfoservice.h"


const TInt	PASS(0);
const TInt	FAIL(!PASS);


// MACROS
// Logging path
_LIT( KTSysBatteryLogPath, "\\logs\\testframework\\" ); 
// Log file
_LIT( KTSysBatteryLogFile, "TSysBattery.txt" );

// FUNCTION PROTOTYPES

// DATA TYPES

// CLASS DECLARATION

/**
*  CTSysBattery test class for STIF Test Framework TestScripter.
*  ?other_description_lines
*
*  @lib ?library
*  @since ?Series60_version
*/
NONSHARABLE_CLASS(CTSysBattery) : public CScriptBase,public ISystemObserver 
    {
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        */
        static CTSysBattery* NewL( CTestModuleIf& aTestModuleIf );

        /**
        * Destructor.
        */
        virtual ~CTSysBattery();

    public: // New functions

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
        CTSysBattery( CTestModuleIf& aTestModuleIf );

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

	    virtual TInt BatteryChargingL(CStifItemParser &aItem );
	    virtual TInt BatteryNotChargingL(CStifItemParser &aItem );
	    virtual TInt BatteryLevelL(CStifItemParser &aItem );
	    virtual TInt BatteryLvlNotiL(CStifItemParser &aItem );
	    virtual TInt ChargeStateNotiL(CStifItemParser &aItem );
	    virtual TInt BatteryStrengthNotiL(CStifItemParser &aItem );
	 	void HandleResponseL(const TDesC& aEntity,const TDesC& aKey,
	 					CSysData* aOutput, TInt32 aTransID, TSysRequest::TRequestType aType,TInt aError);
		
    public:     // Data
        


    protected:

    private: 
    		TInt TestE70();
    		TInt TestN6290();

    };

#endif      // TSYSBATTERY_H

// End of File
