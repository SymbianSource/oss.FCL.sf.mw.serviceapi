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


#ifndef C_LOCATIONCOREIMP_H
#define C_LOCATIONCOREIMP_H

#include <lbs.h>
#include <LbsSatellite.h>
#include "locationservice.h"


/**
 * Consts to identify the type of location request (trace, getlocation
 */

const TInt KTraceRequest = 1 ;
const TInt KGetLocationRequest = 2 ;





/**
 * This class implements Location SAPI core logic.It has  methods
 * for retreving information location asynchronusly .  
 */

class CGetLoc : public CActive
    {
    public: 

    
    
	    /**
	     * Creates a new instance of a @ref CGetLoc
	     *
	     * @param aPositionServer subsession to location server
	     * @param aRequestorInfoStack requestor indenty
	     * @param aList List of position fields that should be retrived
	     * @param aLocationInfoCategory information type required(Basic, Generic)
	     * @param aModuleId the unique id of the module which should be used to 
	     *         open the subsession with location server
	     */
	    								
		IMPORT_C static CGetLoc* NewL( RPositionServer &aPositionServer , 
									   TPositionFieldIdList aList ,
									   TInt aRequestType,
            TInt aLocationInfoCategory,
            TPositionModuleId aModuleId) ;		

	    /**
	     * Destructor.
	     */
	    virtual ~CGetLoc() ; 



    /**
     * Gets users current location Asynchronously calls the users callback 
     * function when updates are recived from location server
     * @param aLocationService pointer to the CLocationService class used in RunL
     * @param aCallBackObj callback object for updates notification
     * @param aUpdatesOptions update options for asynchronous calls
     *
     * @see TPositionUpdateOptions in LbsCommon.h for details
     */ 
    TInt GetLocationUpdates( CLocationService* aLocationService, MLocationCallBack* aCallBackObj ,
            const TPositionUpdateOptions* aUpdateOptions = NULL );

		
		void SetStatusComplete()
	    {
	    	iRequestStatus = 1;
	    }
	    TBool IsStatusComplete()
	    {
	    	if(iRequestStatus == 0)
	    		return false;
	    	else
	    		return true;
	    }	    						 
    /*
     * Returns the MLocationCallBack object pointer stored by this class
     */

    MLocationCallBack* GetCallBackobj() const
    {
    return iCallBack;  
    }					 
    				 
    protected:  

	    /**
	     * From CActive
	     */
	    void DoCancel();
	    void RunL();


	    private:  

    /**
     * By default Symbian 2nd phase constructor is private.
     * @param aPositionServer subsession to location server
     * @param aList List of position fields that should be retrived
     * @param aRequestType The type of request serviced by this Active object(GetLocation,Trace)          
     * @param aModuleId aModuleId the unique id of the module which should be used to 
	   *         open the subsession with location server
     */

    void ConstructL(RPositionServer &aPositionServer ,
            TPositionFieldIdList aList ,
            TInt aRequestType,	            
            TPositionModuleId aModuleId);
	    /**
	     * Default constructor
	     */
	     
	    CGetLoc(); 
	    TInt DoInitialiseL();

	    private:    




	    /**
	     * Class Member which holds location server subsession 
	     */
	    RPositioner iPositioner;

	    /**
	     * Basic info
	     */
	    TPositionInfo iPositionInfo;  
	           

	    /**
	     * Basic info base
	     */
	    TPositionInfoBase* iPosInfoBase;
	    /**
	     * Generic info 
	     */
	    HPositionGenericInfo *iGenericPosInfo ;
	    /**
	     * callback object
	     */
	    MLocationCallBack *iCallBack ; 
	    
	    /**
	     * Request type (Getlocation or Trace)
	     */
	    TInt iRequestType ; 
	    
	    TInt iRequestStatus;      

    /**
     * Pointer to CLocationService used in RunL()
     */
    CLocationService* iLocationService;

    };



#endif //C_LOCATIONCOREIMP_H

  			