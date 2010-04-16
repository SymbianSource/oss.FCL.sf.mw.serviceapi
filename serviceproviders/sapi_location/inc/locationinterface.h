/*
* Copyright (c) 2006-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Header file for location SAPI core implementation.
*
*/

#ifndef C_LOCINTERFACE_H
#define C_LOCINTERFACE_H


#include <liwcommon.h>
#include "locationcb.h"
#include "locationservice.h"
#include "serviceerrno.h"


// CONSTANTS



//Second
const TInt KLocSecond = 1000000;

//Update interval
const TInt KLocUpdateInterval = KLocSecond;

//Update time out
const TInt KLocUpdateTimeOut = 60*KLocSecond;

//MaxAge
const TInt KLocMaxAge = 0;


/**
 * Various command for Location service
 */
 
_LIT8( KCmdGetLocation , "GetLocation" ) ;
_LIT8( KCmdTraceLocation, "Trace" ) ;
_LIT8( KCmdCancelRequest, "CancelNotification" ) ;

_LIT8(KCmdLastLocation,"GetLastPosition");
_LIT( KRequestTrace ,"TraceCancel") ;
_LIT( KRequestGetLoc , "GetLocCancel" ) ;
_LIT8( KRequestCalculate , "Calculate") ;
 
_LIT8(	KMathRequest , "MathRequest") ;
_LIT8( KCancelType , "CancelRequestType") ;

/**
 * Error Indntifier in Output parameter list
 */
 _LIT8(KErrorCode , "ErrorCode") ; 
 
 /**
  * Error string 
  */
  _LIT8(KErrorMessage,"ErrorMessage");
 
 /**
  * Location SAPI result parmater identifiers
  */
 _LIT8(KLocationMap , "ReturnValue") ; 
 
/**
 * Update Options
 */
_LIT8(KUpdateOptionMap,"Updateoptions");
_LIT8(KUpdateOptionInterval,"UpdateInterval");
_LIT8(KUpdateOptionTimeOut,"UpdateTimeOut");
_LIT8(KUpdateOptionMaxAge,"UpdateMaxAge");
_LIT8(KPartialUpdates , "PartialUpdates");
/**
 * EnableHighAccuracy parameter
 */
_LIT8(KEnableHighAccuracy,"EnableHighAccuracy");

/**
 * Class of Location Information ;user is 
 * looking for
 */
_LIT8(KLocationInfoCategory,"LocationInformationClass");
_LIT(KLocationBasicinfo,"BasicLocationInformation");
_LIT(KLocationGenericInfo,"GenericLocationInfo");

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
 
  
/**
 * Speed informations which will be part of outparamlist 
 */
   
_LIT8(KPositionFieldHorizontalSpeed , "HorizontalSpeed") ;
_LIT8(KPositionFieldVerticalSpeed , "VeritcalSpeed") ;
_LIT8(KPositionFieldHorizontalSpeedError , "HorizontalSpeedError") ;
_LIT8(KPositionFieldVerticalSpeedError , "VeritcalSpeedError") ;
   
 /**
  * Satellite information which be part of outparm list
  */
_LIT8(KPositionFieldSatelliteNumInView , "SatelliteNumView") ;
_LIT8(KPositionFieldSatelliteNumUsed , "SatelliteNumViewUsed") ;
_LIT8(KPositionFieldSatelliteTime , "SatelliteTime") ;

/**
 * Compass information which will be part of outparmlist
 */
_LIT8(KPositionFieldHeading , "Heading") ;
_LIT8(KPositionFieldHeadingError , "HeadingError") ;
_LIT8(KPositionFieldMagneticHeading , "MagneticHeading") ;
_LIT8(KPositionFieldMagneticHeadingError , "MagneticHeadingError") ;
_LIT8(KTime , "timestamp") ;
  
/**
 * Direction course information which will be part of outparm list
 */
_LIT8(KPositionFieldTrueCourse , "TrueCourse") ;
_LIT8(KPositionFieldTrueCourseError , "TrueCourseError") ;
_LIT8(KPositionFieldMagneticCourse , "MagneticCourse") ;
_LIT8(KPositionFieldMagneticCourseError , "MagneticCourseError") ;


/**
 * Enum specifier for postion Info Category
 * 
 */
 enum TPositionCategory
	 {
	 EBasicPositionInfo   = 0,
	 EGenericPositionInfo = 1	
	 };

/**
 * Transaction id, which will be part of outparamlist for asynchronous request
 */
_LIT8(KTransactionId, "TransactionID");
  
/**
 * This is an interface class for Location SAPI   This class implements ExecuteCmdL() method
 * ExecuteCmdL() method is called directly by consumer after descovering the service 
 */
 
class CLocationInterface : public CBase ,public  MLiwInterface
    {
    public:
    enum TIndex
			{
			Index0 = 0,        
			Index1,
			Index2,
			Index3
			};
    /**
      * A static method for creating CLocationInterface object
      */
     static CLocationInterface *NewL() ;
    

    /**
     * Default destructor
     */
    virtual ~CLocationInterface() ;

    /**
     * ExecuteCmdL parses the input parameters and then calls an appropriate method on iLocationServic
     *
     * @param aCmdName the name of the service command which the consumer wants to invoke
     * @param aInParamList the input parameter list, can be empty list
     * @param [in,out] aOutParamList the output parameter list, can be empty lis. The
     * service provider can use the output parameter list to fill in necessary return values
     * @param aCmdOptions Options for the command, see TLiwServiceCmdOptions in LiwCommon.hrh.
     * @param aCallback callback to be registered by consumer application
     *               
     * @see TLiwServiceCmdOptions
     * @see CLiwGenericParamList
     * @see MLiwNotifyCallback
     */
    virtual void ExecuteCmdL( const TDesC8& aCmdName,
                           const CLiwGenericParamList& aInParamList,
                           CLiwGenericParamList& aOutParamList,
                           TUint aCmdOptions = 0,
                           MLiwNotifyCallback* aCallback = 0 );
	static TInt ConvertToSapiError(TInt aSymbianErrorCode);
                           
    /**
     * Close function called by consumer when it wants to delete the interface
     */
    virtual void Close() {delete this;}                          

    private :
   

    /**
     * Internal private function which extracts coordinate information from CLiwMap
     * passed by consumer, this is required for math operations
     *
     * @param aCoordinate which will contain extracted coordinate info from map
     * @param input map containing cooridinate information
     */
    void FillCoordinatesL( TCoordinate &aCoordinate , const CLiwMap *aMap ) ;
		
	/**
	 * SetUpdateOption construct a TPositionUpdateOptions object from the map containing
	 * different field of update optiin.
	 *
	 * @param aPositionUpdateoption object to be constructed
	 * @param aUpdatemap map containing values of different field of update option.
	 * return -1 if negative value for timeinterval is given
	 */
	 TInt SetUpdateOption(TPositionUpdateOptions& aPositionUpdateoption,const CLiwMap* aUpdatemap);
	 
    private :
    /**
     * By default Symbian 2nd phase constructor is private.
     * 
     */
    void ConstructL();
    /**
     *Default constructor
     */
     
    CLocationInterface() ;

    /**
     * Internal CmdExecute function which parses  the input parameters
     * this function is called by ExecuteCmdL() function 
     *
     * @param aCmdName the name of the service command which the consumer wants to invoke
     * @param aInParamList the input parameter list, can be empty list
     * @param [in,out] aOutParamList the output parameter list, can be empty lis. The
     * service provider can use the output parameter list to fill in necessary return values
     * @param aCmdOptions Options for the command, see TLiwServiceCmdOptions in LiwCommon.hrh.
     * @param aCallback callback to be registered by consumer application
     * @see TLiwServiceCmdOptions
     * @see CLiwGenericParamList
     * @see MLiwNotifyCallback
     *
     */
       
         
     void CmdExecuteL(
	         	const TDesC8& aCmdName,
	            const CLiwGenericParamList& aInParamList ,
	            CLiwGenericParamList& aOutParamList,
	            TUint aCmdOptions,
	            MLiwNotifyCallback* aCallback);
    	            
    /**
     * Internal utility function which fills iGenericPosinfo  accoriding to capability of 
     * Positioning module used for location estimation
     */	            
    	            

    /**
     * Internal utility function which gets all location information which module supports
     *
     * @param aOutParamList output list which is populated with location informatio
     * @param aPosInfoCategory position category (Basic or Generic)
     */
     
	void GetLocationInfo( CLiwGenericParamList& aOutParamList,TInt aPosInfoCategory) ;
	
	
            
    /**
     * Handle to core location class for performing location operations
     */
    CLocationService *iLocationService ;
    
    /**
     * Registration table for callbacks
     */
    RPointerArray<LocationInterfaceCB> iHandleCB; 
    

    /**
     * Class member which is used to obtain updates of Last Known Position
     */
    TPosition iPosition;
    /**
     * Generic position class
     */
    HPositionGenericInfo *iGenericPosition;

    };


#endif //C_LOCINTERFACE_H