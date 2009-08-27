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




#ifndef TCOMPLUGIN_H
#define TCOMPLUGIN_H

//  INCLUDES
#include <StifLogger.h>
#include <TestScripterInternal.h>
#include <StifTestModule.h>

#include "serviceerrno.h"

// CONSTANTS
//const ?type ?constant_var = ?constant;

// MACROS
//#define ?macro ?macro_def
// Logging path
_LIT( KTcompluginLogPath, "\\logs\\testframework\\Tcomplugin\\" ); 
// Log file
_LIT( KTcompluginLogFile, "Tcomplugin.txt" ); 

_LIT8(KLocationContents , "Service.Location");
 _LIT8(KLocationInterface , "ILocation") ;
 _LIT8(KDataSource , "ILocation") ;
_LIT8(KGetLocation , "GetLocation") ;
_LIT8(KTraceLocation ,"Trace") ;
_LIT8(KErrCode , "ErrorCode") ; 
_LIT8(KService , "Service.Location") ;
_LIT8(KContents , "ILocation") ;
_LIT8( KCancelType , "CancelRequestType") ;
_LIT8(KLsInterfaceName , "ILocation") ; 


/**
 * Error Indntifier in Output parameter list
 */
 _LIT8(KErrorCode , "ErrorCode") ; 
 
 /**
  * Location SAPI result parmater identifiers
  */
 _LIT8(KLocationMap , "ReturnValue") ; 
 
 /**
 * Key for locating location information in CLiwGenericParamList
 */
_LIT8(KLongitudeKey,"Longitude") ;
_LIT8(KLatitudeKey , "Latitude") ;
_LIT8(KAltitudeKey , "Altitude") ;



/**
 * Various command for Location service
 */
 
_LIT8( KCmdGetLocation , "GetLocation" ) ;
_LIT8( KCmdTraceLocation, "Trace" ) ;
_LIT8( KCmdCancelRequest, "CancelNotification" ) ;

_LIT8( KRequestTrace ,"TraceCancel") ;
_LIT8( KRequestGetLoc , "GetLocCancel" ) ;
_LIT8( KRequestCalculate , "Calculate") ;


/**
 * Update Options
 */
_LIT8(KUpdateOptionMap,"Updateoptions");
_LIT8(KUpdateOptionInterval,"UpdateInterval");
_LIT8(KUpdateOptionTimeOut,"UpdateTimeOut");
_LIT8(KUpdateOptionMaxAge,"UpdateMaxAge");
_LIT8(KPartialUpdates , "PartialUpdates");

/**
 * Math operations request identifiers 
 */
_LIT( KRequestDistance , "FindDistance") ;
_LIT(KRequestBearingTo,"FindBearingTo");
_LIT(KRequestMove,"MoveCoordinates");
_LIT8(KDistanceParmSource , "DistanceParamSource") ;
_LIT8(KDistanceMove , "MoveByThisDistance");
_LIT8(KBearingMove , "MoveByThisBearing");
_LIT8(KDistanceParmDestination , "DistanceParamDestination") ;
_LIT8(KMathOpResult,"ReturnValue");
_LIT8(	KMathRequest , "MathRequest") ;


/**
 * Class of Location Information ;user is 
 * looking for
 */
_LIT8(KLocationInfoCategory,"LocationInformationClass");
_LIT8(KLocationBasicinfo,"BasicLocationInformation");
_LIT8(KLocationGenericInfo,"GenericLocationInfo");


class CTestProvider;


/**
*  CTestProvider test class for STIF Test Framework TestScripter.
*  ?other_description_lines
*
*  @lib ?library
*  @since ?Series60_version
*/
NONSHARABLE_CLASS(CTestProvider) : public CScriptBase
    {
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        */
        static CTestProvider* NewL( CTestModuleIf& aTestModuleIf );

        /**
        * Destructor.
        */
        virtual ~CTestProvider();

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
        CTestProvider( CTestModuleIf& aTestModuleIf );
        

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
        virtual TInt GetLocation(CStifItemParser &aItem );
        virtual TInt LocationUpdates(CStifItemParser& aItem) ;
        virtual TInt GetLocationAsynch(CStifItemParser& aItem) ;
        virtual TInt ServiceFailed(CStifItemParser& aItem) ;
        virtual TInt ServiceNotAvailable(CStifItemParser& aItem) ;
        virtual TInt StraySignal(CStifItemParser& aItem) ;
		virtual TInt StraySignalGetLoc(CStifItemParser& aItem) ;
		virtual TInt ConcurrentCallsGetLoc(CStifItemParser& aItem);
		virtual TInt ConcurrentCallsTrace(CStifItemParser& aItem);
		virtual TInt EmptyCancelTraceTest(CStifItemParser& aItem);
		virtual TInt EmptyCancelGetLocTest(CStifItemParser& aItem);
		virtual TInt CancelWrongNotification1(CStifItemParser& aItem);
		virtual TInt CancelWrongNotification2(CStifItemParser& /*aItem*/) ;
		virtual TInt GetLocationCancel(CStifItemParser& /*aItem*/) ;
		virtual TInt TraceLocationCancel(CStifItemParser& /*aItem*/) ;
		virtual TInt GetLocationTimedOut(CStifItemParser& /*aItem*/) ;
		virtual TInt BearingToTest(CStifItemParser& /*aItem*/) ;
		virtual TInt FindDistance(CStifItemParser& /*aItem*/) ;
		virtual TInt FindDistanceAgain(CStifItemParser& /*aItem*/) ;
		virtual TInt GetLocationUpdateOpts(CStifItemParser& /*aItem*/) ;
        virtual TInt MoveCoordinates(CStifItemParser& /*aItem*/) ;
        
        virtual TInt GetLocationSynchWrongUpdateMapType(CStifItemParser& /*aItem*/) ;
        virtual TInt CancelWithInvalidTransId(CStifItemParser& /*aItem*/) ;
        virtual TInt getlocationPostionbased(CStifItemParser& /*aItem*/) ;
        virtual TInt getlocationPostionbasedwithupdateoption(CStifItemParser& /*aItem*/) ;
    	virtual TInt getlocationPostionbasedpdateoption(CStifItemParser& /*aItem*/) ;
    	virtual TInt GetLocationWrongInfoClass(CStifItemParser& /*aItem*/) ;
    	virtual TInt TraceWrongInfoClass(CStifItemParser& /*aItem*/) ;
    	virtual TInt GetLocNegativeUpdateoption(CStifItemParser& /*aItem*/) ;
    	virtual TInt TraceNegativeUpdateoption(CStifItemParser& /*aItem*/) ;
    	virtual TInt TestWrongInterfaceName(CStifItemParser& /*aItem*/) ;
    	virtual TInt TestAllApi(CStifItemParser& /*aItem*/) ;
    	virtual TInt CancelTwice(CStifItemParser& /*aItem*/) ;
    	virtual TInt GetLastLocation(CStifItemParser& /*aItem*/) ;
    	virtual TInt GetLocationMultiple(CStifItemParser& /*aItem*/) ;
    	virtual TInt TraceMultiple(CStifItemParser& /*aItem*/) ;
    	virtual TInt TraceTimeOut(CStifItemParser& /*aItem*/) ;
    	virtual TInt TraceMultipleWrongCancel(CStifItemParser& /*aItem*/);
    	virtual TInt EnableAccTrueGetLoc(CStifItemParser& /*aItem*/);
    	virtual TInt EnableAccFalseGetLoc(CStifItemParser& /*aItem*/);
    	virtual TInt EnableAccTrueTrace(CStifItemParser& /*aItem*/);
    	virtual TInt EnableAccFalseTrace(CStifItemParser& /*aItem*/);
    	
    	virtual TInt EnableAccPosBasedGetloc(CStifItemParser& /*aItem*/);
    	virtual TInt EnableAccPosBasedWrongTypeGetloc(CStifItemParser& /*aItem*/);
    	virtual TInt EnableAccPosBasedTrace(CStifItemParser& /*aItem*/);
    	virtual TInt EnableAccPosBasedWrongTypeTrace(CStifItemParser& /*aItem*/);

    	virtual TInt GetLocationPosBasedWrongVal(CStifItemParser& /*aItem*/);
    	virtual TInt CancelTransIdPosBased(CStifItemParser& /*aItem*/);
    	virtual TInt CancelWithoutTransId(CStifItemParser& /*aItem*/);
    	virtual TInt GetLocationAsyncPosBasedUpdate(CStifItemParser& /*aItem*/);
    	virtual TInt GetLocationAsyncWrongUpdate(CStifItemParser& /*aItem*/);
    	virtual TInt GetLocPosBasedWrongVal(CStifItemParser& /*aItem*/);
    	virtual TInt GetLocPosBasedWrongVal1(CStifItemParser& /*aItem*/);
    	virtual TInt TracePosBasedWrongVal( CStifItemParser& /*aItem*/ );
    	virtual TInt TracePosBasedUpdateOpts(CStifItemParser& /*aItem*/);
    	virtual TInt TracePosBasedUpdateWrongVal(CStifItemParser& /*aItem*/);
    	virtual TInt FindDistancePositionBased(CStifItemParser& /*aItem*/);
    	virtual TInt MoveCoordinatePosBased(CStifItemParser& /*aItem*/);
    	virtual TInt FindBearingPosBased(CStifItemParser& /*aItem*/);
    public:     // Data
        // ?one_line_short_description_of_data
        //?data_declaration;

    protected:  // Data
        // ?one_line_short_description_of_data
        //?data_declaration;

    private:    // Data
        
        // ?one_line_short_description_of_data
        //?data_declaration;
        TInt CTestGetLocation() ;

        // Reserved pointer for future extension
        //TAny* iReserved;

    public:     // Friend classes
        //?friend_class_declaration;
    protected:  // Friend classes
        //?friend_class_declaration;
    private:    // Friend classes
        //?friend_class_declaration;

    };
    TInt GetLocUpdates(TAny *aPtr);
    TInt FindLocationAsynch(TAny *aPtr);
    TInt ServiceFailedTest(TAny *Arg) ;
    TInt StrayTest(TAny *aArg) ;
    TInt ConcurrentGetLocationCalls(TAny *aArg) ;

    TInt StrayTestGetLoc(TAny *aArg) ;
    TInt TraceConcurrent(TAny */*Arg*/);
    TInt GetLocWrongCancel(TAny */*Arg*/);
    TInt TraceLocWrongCancel(TAny */*Arg*/);
    TInt GetLocCancel(TAny */*Arg*/);
    TInt TraceLocCancel(TAny */*Arg*/);
    
    TInt TraceTO(TAny */*Arg*/);
    TInt TraceTOL(TAny */*Arg*/);
    TInt EnableHighAcc(TAny *aFlag);
    TInt EnableHighAccL(TInt aCallType,TBool enableAcc);
    TInt EnableHighAcc_PosBased(TAny *aFlag);
    TInt EnableHighAcc_PosBasedL(TInt aCallType,TBool enableAcc);
    
    TInt GetLocAsynchPosBased(TAny * /*Arg*/);
    TInt GetLocAsynchPosBasedL();
    TInt GetLocAsynchWrongVal(TAny * /*Arg*/);
    TInt GetLocAsynchWrongValL();


#endif      // TCOMPLUGIN_H

// End of File
