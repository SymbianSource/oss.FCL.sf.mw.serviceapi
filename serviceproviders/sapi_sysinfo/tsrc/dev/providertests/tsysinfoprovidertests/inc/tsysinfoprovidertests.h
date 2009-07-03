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




#ifndef TSYSINFOPROVIDERTESTS_H
#define TSYSINFOPROVIDERTESTS_H

//  INCLUDES
#include <StifLogger.h>
#include <TestScripterInternal.h>
#include <StifTestModule.h>


// CONSTANTS
const TInt	PASS(0);
const TInt	FAIL(!PASS);

// MACROS
// Logging path
_LIT( KtsysinfoprovidertestsLogPath, "\\logs\\testframework" ); 
// Log file
_LIT( KtsysinfoprovidertestsLogFile, "tsysinfoprovidertests.txt" ); 
_LIT( KtsysinfoprovidertestsLogFileWithTitle, "tsysinfoprovidertests_[%S].txt" );


// FORWARD DECLARATIONS
class Ctsysinfoprovidertests;
class CLiwServiceHandler;
class MLiwInterface;
class CLiwGenericParamList;
class CLiwMap;

//
extern int VibraNotification(int, char**);
extern int ReqNotification();
extern int ActiveConnection(CStifLogger* aLog);
extern int BTAsyncReqCancel();
extern int ActiveConnectionReqCancel(CStifLogger* aLog);

// DATA TYPES


// CLASS DECLARATION

/**
*  Ctsysinfoprovidertests test class for STIF Test Framework TestScripter.
*  ?other_description_lines
*
*  @lib sysinfoprovider.lib
*  @since Series60_3.2
*/
NONSHARABLE_CLASS(Ctsysinfoprovidertests) : public CScriptBase
    {
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        */
        static Ctsysinfoprovidertests* NewL( CTestModuleIf& aTestModuleIf );

        /**
        * Destructor.
        */
        virtual ~Ctsysinfoprovidertests();

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
        Ctsysinfoprovidertests( CTestModuleIf& aTestModuleIf );

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

	    virtual TInt FirmwareVersionL(CStifItemParser &aItem );
	    virtual TInt PlatformVersionL(CStifItemParser &aItem );
//	    virtual TInt SymbianOSVersionL(CStifItemParser &aItem );
	    virtual TInt MachineIDL(CStifItemParser &aItem );
	    virtual TInt ProductTypeL(CStifItemParser &aItem );
	    virtual TInt ManufacturerL(CStifItemParser &aItem );
	    virtual TInt PhoneModelL(CStifItemParser &aItem );
	    virtual TInt IMEINumberL(CStifItemParser &aItem );

	    virtual TInt GetSetBrightnessL(CStifItemParser &aItem );
	    virtual TInt GetSetScreensaverTimeOutL(CStifItemParser &aItem );
	    virtual TInt UserInactivityNotifierL(CStifItemParser &aItem );
		virtual TInt SetGetAutoLockTimeL(CStifItemParser &aItem );
		virtual TInt AutoLockNotifierL(CStifItemParser &aItem );
		virtual TInt DisplayResolutionL(CStifItemParser &aItem );
		virtual TInt DisplayOrientationL(CStifItemParser &aItem );
		virtual TInt GetSetLightTimeOutL(CStifItemParser &aItem );
		virtual TInt GetSetWallPaperL(CStifItemParser &aItem );
		virtual TInt GetSetKeyGaurdL(CStifItemParser &aItem );		

	    virtual TInt GetListofDrivesL(CStifItemParser &aItem );
	    virtual TInt GetDriveInfoL(CStifItemParser &aItem );
	    virtual TInt GetDriveInfoNegTestL(CStifItemParser &aItem );
	    
	    virtual TInt VibraStatus(CStifItemParser &aItem );
	    virtual TInt SetInputLang(CStifItemParser &aItem );
	    virtual TInt SetDisplayLang(CStifItemParser &aItem );
	    virtual TInt SupportedLang(CStifItemParser &aItem );
	    virtual TInt AvailableUSBModes(CStifItemParser &aItem );
	    
	    virtual TInt ConnBluetooth(CStifItemParser &aItem );
	    virtual TInt GetActiveConnections(CStifItemParser &aItem );
	    virtual TInt BTAsyncRequestCancel(CStifItemParser &aItem );
	    virtual TInt GetActiveConnectionsReqCancel(CStifItemParser &aItem );


    public:    

    private:
  		void CreateInterfaceL(CLiwServiceHandler*& aHandler,
								MLiwInterface*& aInterface);

		TInt CheckErrorCode( const CLiwGenericParamList& aOutList, 
								TInt32 &aError );
								
    	void GetOSVersion(TInt& aMajor,TInt& aMinor);
    	void GetPlatformVersion(TInt& aMajor, TInt& aMinor);
		void ProcessDriveInfoL(const CLiwMap* aDriveInfo);
    };

#endif      // TSYSINFOPROVIDERTESTS_H

// End of File
