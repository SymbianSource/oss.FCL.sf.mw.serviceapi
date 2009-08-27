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
* Description:  Header file for location SAPI service implementation.
*
*/

#ifndef LOCATIONSERVICE_H
#define LOCATIONSERVICE_H

#include <lbs.h>
class CGetLoc;
/**
 * Identity for location SAPI lib 
 * This will be appended to requestor identity information stack received from the 
 * client and will be passed onto location server
 */

_LIT(KIdentity,"Location SAPI");



/**
 * Key for locating location information in CLiwGenericParamList
 */
_LIT8(KLongitudeKey,"Longitude") ;
_LIT8(KLatitudeKey , "Latitude") ;
_LIT8(KAltitudeKey , "Altitude") ;
_LIT8(KHorAccuracy,"HorizontalAccuracy");
_LIT8(KVerAccuracy,"VerticalAccuracy");

_LIT(KUnknown,"Unknown");

/**
 * Default Update options
 */
//Second
const TInt KSSecond = 1000000;

//Update interval
const TInt KSUpdateInterval = KSSecond;

//Update time out
const TInt KSUpdateTimeOut = 15*KSSecond;

//MaxAge
const TInt KSMaxAge = 0;
const TInt KGetLocationReq = 0 ;
const TInt KTraceReq   = 1 ;

/**
 * Enums required for mathoperations
 */
enum TMathOperationChoice
	{
	EDistance  = 0,
	EBearingTo = 1,
	EMove      = 2
	};

/**
 * Notification Type to be cancelled
 */
enum TCancelParam
    {
	ECancelGetLocation = 0,
	ECancelTrace = 1
    }; 
/**
 * Enumeration used to identify category of location information user intends to 
 * retrieve
 * Example: specifying EBasic user will get only longitude,latitude and altitude
 */
 enum TLocationInfoType
	 {
	 EBasicInfo = 0,
	 EGenericInfo = 1	
	 };

/**
 * used by the caller of math operation to send input parameters 
 * after computation MathOperation wil fill in result field of this
 * struct.
 */
struct _INPPARM
	{
    //specifies option for mathoperation
	TInt servicechoice;
	//result of the computation
	TReal32 result ;
	//Source Coordinate for math operation
	TCoordinate source;
	//Destination Coordinate for math operation
	TCoordinate destination ;
	//In case of find bearingto following two should be supplied by the consumer
	TReal32 bearing;
	TReal32 distance;
	
	};

typedef struct _INPPARM inpparam;



/**
 *  Location callback interface, its pure interface class, application need to 
 *  Write there own callback derriving from this class.
 *  @Depenedency lbs.lib
 */
 
 class MLocationCallBack 
    {
    /**
     * Handles notifications caused by an asynchronous GetLocationL,
     * or by trace.
     *
     * @param aOutPos updated position got from location server
     * @return Success/Error code for the callback.
     *
     * @see HPositionGenericInfo in LbsPositionInfo.h for details
     *
     */
    public :
    virtual TInt HandleNotifyL(HPositionGenericInfo* aOutPos , TInt aError) = 0 ;
    /*
     * To be implemented by every class that derives from this. This function should return 
     * the Async Request type for which this callback is used.
     */ 
    
    virtual TUint GetRequestType(void) = 0; 
    
    /*
     * To be implemented by every class that derives from this. This returns the 
     * TransactionId associated with the Async request for which this Callback
     * object is used.
     */
    
    virtual TInt32 GetTransactionId(void) = 0;
    
    
    virtual ~MLocationCallBack(){}
    };


/**
 * CLocationService class : This is a wrapper class for the Functionalities 
 * offered by Location Retreival APIs.
 * In case of An Asynchronus request it has method which Instantiates and delegate 
 * the job to another class which  also opens new sub-session with
 * Location server.
 */ 


class CLocationService : public CBase 
    {
    public :
	    /**
        * Creates a new instance of a @ref CLocationService
        * @return The newly created CLocationService object
        */
	    IMPORT_C static CLocationService *NewL() ;

	     
		 /*
		  * @Destructor
		  */
	    virtual ~CLocationService() ; 

	    /**
	     * Methods on the  Core Location implementation
	     */



	    /**
	     * Synchronous get location with update options returns current location of the user
	     *
	     * @param aPosinfobase input TPositionInfoBase object which will hold location details
	     * @param aUpdateOpts updateoptions for synchronous calls 
	     * @param aEnableHighAcc - Tells whether to use greater accuracy modules to obtain updates
	     */
	    IMPORT_C void GetLocationL( TPositionInfoBase* aPos ,
	    							const TPositionUpdateOptions* aUpdateOpts= NULL,
	    							TBool aEnableHighAcc = false ) ;
	    							

	    /**
	     * Gets the current location of user asynchronosly calls the users callback handle on reciving 
	     * location updates
	     * @param aCallBack callback object after reciving the position updates 
	     * @param aLocationInfoCategory specifying one of the enumeration in TLocationInfoType.
	     * @param aFieldIdList specifies field of HPositionGenericInfo that user intend to retrieve.
	     * @param aUpdateoptions update options for asynchronous requests.
	     * @param aEnableHighAcc - Tells whether to use greater accuracy modules to obtain updates
	     * @see Lsbcommon.h for details of TPositionFieldIdList and TPositionUpdateOptions
	     */
	    IMPORT_C void GetLocationL( MLocationCallBack* aCallBackObj ,
	    							TInt aLocationInfoCategory = 0, 
	    							TPositionFieldIdList aFieldIdList = NULL ,
	    							const TPositionUpdateOptions* aUpdateopts = NULL,
	    							TBool aEnableHighAcc = false
	    							 );
	    							
	    /**
	     * Gets module information of the Positioning module specified my aModuleId
	     *
	     * @param TPositionModuleId param to store the obtained module information
	     *
	     * @see lsbcommon.h for details of TPositionModuleInfoBase
	     */								
	    IMPORT_C TInt GetModuleInfo( TPositionModuleInfoBase& aModuleInfo ) const ;	
    
	    /**
	     * Performs mathoperations (move,distance,bearingto) by parsing contents of input param
	     *							
	     * @param aInput input paramater for math opertaions
	     * 
	     * @see inparam in this file for detailed math operation list
	     */
	       							

	    IMPORT_C TInt MathOperation( inpparam& aInput );

	    /**
	     * Trace function traces users location changes any change in users current location is notificed 
	     * to user via call back function
	     *
	     * @param aCallBackObj callback object after reciving location updates 
	     * @param aLocationInfoCategory specifying one of the enumeration in TLocationInfoType.
	     * @param aFiledList List of position fields that should be retrived 
	     * @param aUpdateOptions update options for trace
	     * @param aEnableHighAcc Tells whether to use greater accuracy modules to obtain updates
	     * @see Lsbcommon.h for details of TPositionFieldIdList and TPositionUpdateOptions
	     */ 

	    IMPORT_C void TraceL(MLocationCallBack* aCallBackObj , 
	    						TInt aLocationInfoCategory = 0,
	    						TPositionFieldIdList aFiledList = NULL ,
	    						const TPositionUpdateOptions* aUpateOptions= NULL,
	    						TBool aEnableHighAcc = false);
	    						

	    /**
	     * Method to cancell pending async request
	     * 
	     * aCancelparam cancellation type (trace,getlocation)
	     *
	     * @see TCancelParam for cancellation options
	     */

	     IMPORT_C TInt CancelOnGoingService( TInt aCancelparam ) ;
	    
	    /**
         * Method to cancel pending async request
         * 
         * aTransId Transaction Id that was returned for an Async request         
         */
	     IMPORT_C TInt CancelService( TInt aTransId);
	     
	    /**
	     * Method to fetch last known location from location server
	     */

	     IMPORT_C TInt GetLastKnownLoc( TPosition& aResultPos ) ; 

	     /**
	      * Method to obtain the High Accuracy module out of the 
	      * currently available modules on the phone
	      */
	     
	     void GetHighAccuracyModuleL(TPositionModuleId* aModId);



    protected:
	    /**
	     * internal method to construct class members 
	     */
	    void ConstructL() ; 
	    
	    /**
	     * Default constructor 
	     */
	    CLocationService() ;  
	    

	    private :
	    
	    /**
	     * Subsession used to fetch location information
	     */

	    RPositioner iPositioner;
	    
	    /**
	     * Session used for getting location information
	     */

	    RPositionServer iPosServer;
	    
	    /**
	     * Registration table for callbacks
	     */
	          
	    RPointerArray<CGetLoc> iRegTable; 

	    
	    /**
	     * Module indtifier used by location server for getting location information
	     */
	    TPositionModuleId iModuleId ; 

    };


#endif // LOCATIONSERVICE_H