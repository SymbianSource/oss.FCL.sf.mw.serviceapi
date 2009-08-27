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




#ifndef TSYSINFOSERVICETESTS_H
#define TSYSINFOSERVICETESTS_H

//  INCLUDES
#include <StifLogger.h>
#include <TestScripterInternal.h>
#include <StifTestModule.h>


// CONSTANTS
const TInt	PASS(0);
const TInt	FAIL(!PASS);

// MACROS
// Logging path
_LIT( KtsysinfoservicetestsLogPath, "\\logs\\testframework\\" ); 
// Log file
_LIT( KtsysinfoservicetestsLogFile, "tsysinfoservicetests.txt" ); 
_LIT( KtsysinfoservicetestsLogFileWithTitle, "tsysinfoservicetests_[%S].txt" );

// FORWARD DECLARATIONS
class Ctsysinfoservicetests;
class CSysData;
//
extern int VibraNotification();
extern int InputLangNotification();
extern int PredTextNotification();
extern int VibraNotificationCancel();
extern int ReqNotification(int, char**);
extern int IRNotification(int, char**);
extern int ActiveConnection(CStifLogger* aLog);
extern int GetActiveConnReqCancel();

// DATA TYPES

// CLASS DECLARATION

/**
*  Ctsysinfoservicetests test class for STIF Test Framework TestScripter.
*  ?other_description_lines
*
*  @lib sysinfoservice.lib
*  @since Series60_3.2
*/
NONSHARABLE_CLASS(Ctsysinfoservicetests) : public CScriptBase
    {
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        */
        static Ctsysinfoservicetests* NewL( CTestModuleIf& aTestModuleIf );

        /**
        * Destructor.
        */
        virtual ~Ctsysinfoservicetests();

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

     protected:  // Functions from base classes

        /**
        * From ?base_class ?member_description
        */
        //?type ?member_function();

    private:

        /**
        * C++ default constructor.
        */
        Ctsysinfoservicetests( CTestModuleIf& aTestModuleIf );

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
	    virtual TInt FirmwareVersionL(CStifItemParser &aItem );
	    virtual TInt PlatformVersionL(CStifItemParser &aItem );
	    virtual TInt SymbianOSVersionL(CStifItemParser &aItem );
	    virtual TInt MachineIDL(CStifItemParser &aItem );
	    virtual TInt ProductTypeL(CStifItemParser &aItem );
	    virtual TInt ManufacturerL(CStifItemParser &aItem );
	    virtual TInt PhoneModelL(CStifItemParser &aItem );
	    virtual TInt IMEINumberL(CStifItemParser &aItem );

	    virtual TInt BatteryLevelAutoL(CStifItemParser &aItem );
	    virtual TInt BatteryChargingAutoL(CStifItemParser &aItem );
	    virtual TInt BatteryStrengthAsyncL(CStifItemParser &aItem );
	    
	    virtual TInt FeaturesL(CStifItemParser &aItem );
	    
	    
	    virtual TInt ConnectedAcc(CStifItemParser &aItem );
	    virtual TInt InputLang(CStifItemParser &aItem );
	    virtual TInt VibraStatus(CStifItemParser &aItem );
	    virtual TInt PredText(CStifItemParser &aItem );
	    virtual TInt SetInputLang(CStifItemParser &aItem );
	    virtual TInt SetDisplayLang(CStifItemParser &aItem );
	    virtual TInt GetDisplayLang(CStifItemParser &aItem );
	    virtual TInt SupportedLang(CStifItemParser &aItem );
	    virtual TInt AvailableUSBModes(CStifItemParser &aItem );
	    virtual TInt ActiveUSBModes(CStifItemParser &aItem );
	    virtual TInt NotificationCancelVibra(CStifItemParser &aItem );
	    virtual TInt CameraData(CStifItemParser &aItem );
	    virtual TInt CameraDataNegativeEntity(CStifItemParser &aItem );
	    virtual TInt CameraDataNegativeKey(CStifItemParser &aItem );
	    
        virtual TInt IRStatus(CStifItemParser &aItem );
	    virtual TInt ConnBluetooth(CStifItemParser &aItem );
	    virtual TInt GetActiveConnections(CStifItemParser &aItem );
	    virtual TInt GetWlanMacAddress(CStifItemParser &aItem );
	    virtual TInt GetActiveConnectionsCancel(CStifItemParser &aItem );

	    virtual TInt GetSetBrightnessL(CStifItemParser &aItem );
	    virtual TInt GetSetScreensaverTimeOutL(CStifItemParser &aItem );
	    virtual TInt UserInactivityNotifierL(CStifItemParser &aItem );
		virtual TInt UserActivityNotifierL(CStifItemParser &aItem );
		virtual TInt SetGetAutoLockTimeL(CStifItemParser &aItem );
		virtual TInt AutoLockNotifierL(CStifItemParser &aItem );
		virtual TInt DisplayResolutionL(CStifItemParser &aItem );
		virtual TInt DisplayOrientationL(CStifItemParser &aItem );
		virtual TInt GetSetLightTimeOutL(CStifItemParser &aItem );
		virtual TInt GetSetWallPaperL(CStifItemParser &aItem );
		virtual TInt GetSetKeyGaurdL(CStifItemParser &aItem );

	    virtual TInt GetListofDrivesL(CStifItemParser &aItem );
	    virtual TInt GetDriveInfoL(CStifItemParser &aItem );	    
    private:    // Data
    	void GetOSVersion(TInt& aMajor,TInt& aMinor);
    	void GetPlatformVersion(TInt& aMajor, TInt& aMinor);
    	TInt TestN6290();
    	TInt TestE70();
    	TInt TestDevlon();
    	TInt DriveInfoL(CSysData* aOutput);
    };

#endif      // TSYSINFOSERVICETESTS_H

// End of File
