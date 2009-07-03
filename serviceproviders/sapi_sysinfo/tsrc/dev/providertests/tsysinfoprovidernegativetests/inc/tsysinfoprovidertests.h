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
extern int VibraNotification(CStifLogger* aLog);
extern int ReqNotification();
extern int ActiveConnection(CStifLogger* aLog);
extern int BTAsyncReqCancel(CStifLogger* aLog);
extern int ActiveConnectionReqCancel(CStifLogger* aLog);
extern int VibraNotification1(CStifLogger* aLog);
extern int VibraAsyncReqCancel(CStifLogger* aLog);
extern int UserInactivity(CStifLogger* aLog);

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
        
        void Ctsysinfoprovidertests::Init();

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

	       
	    virtual TInt SetVibraInvalidParamSysDataList(CStifItemParser &aItem );
	    virtual TInt SetVibraInvalidParamSysData(CStifItemParser &aItem );
	    virtual TInt SetVibraInvalidParamEntity(CStifItemParser &aItem );
	    virtual TInt SetVibraInvalidParamKey(CStifItemParser &aItem );

	    virtual TInt VibraParamMissingEntity(CStifItemParser &aItem );
	    virtual TInt VibraParamMissingKey(CStifItemParser &aItem );
	    virtual TInt VibraParamMissingSysData(CStifItemParser &aItem );
	    virtual TInt VibraParamMissingEntityPos(CStifItemParser &aItem );
	    virtual TInt VibraParamMissingKeyPos(CStifItemParser &aItem );
	    virtual TInt VibraParamMissingSysDataPos(CStifItemParser &aItem );

	    virtual TInt WrongInterfaceName(CStifItemParser &aItem );
	    virtual TInt LoadingInterfaceMultipletime(CStifItemParser &aItem );

	    virtual TInt VibraSync(CStifItemParser &aItem );
	    virtual TInt VibraStatus(CStifItemParser &aItem );
	    virtual TInt VibraStatus1(CStifItemParser &aItem );
	    virtual TInt VibraInvalidCommand(CStifItemParser &aItem );

	    virtual TInt BtNotifyCancel(CStifItemParser &aItem );
	    virtual TInt ActiveConnectionMissingCallback(CStifItemParser &aItem );
	    virtual TInt ActiveConnReqCancelMissingTransId(CStifItemParser &aItem );

	    virtual TInt SupportedLang(CStifItemParser &aItem );

	    virtual TInt SetDisplayLang(CStifItemParser &aItem );
	    virtual TInt SetInputLang(CStifItemParser &aItem );
	    virtual TInt SetPredictiveText(CStifItemParser &aItem );
	    virtual TInt SetVibra(CStifItemParser &aItem );
	    virtual TInt SetBluetoothStatus(CStifItemParser &aItem );
	    virtual TInt SetInfraredStatus(CStifItemParser &aItem );
	    virtual TInt SetBrigthness(CStifItemParser &aItem );
	    virtual TInt SetScreenSaverTimeout(CStifItemParser &aItem );
	    virtual TInt SetKeyGuardTimeout(CStifItemParser &aItem );
	    virtual TInt SetAutoLockTimeout(CStifItemParser &aItem );
	    virtual TInt SetWallpaper(CStifItemParser &aItem );
	    virtual TInt SetLightTimeOut(CStifItemParser &aItem );
	    virtual TInt GetDriveInfoL(CStifItemParser &aItem );
	    virtual TInt UserInactivityNotify(CStifItemParser &aItem );
	    
    public:    
    	CLiwServiceHandler* iServiceHandler;
    	
		MLiwInterface* iInterface ;
		
		CLiwGenericParamList* iInparam ;
		
		CLiwGenericParamList* iOutparam ;
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
