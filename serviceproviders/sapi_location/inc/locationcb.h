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

#ifndef C_LOCATIONCB_H
#define C_LOCATIONCB_H

#include <liwcommon.h> 
#include "locationservice.h"

const TInt KGetLocationCB = 0 ;
const TInt KTraceCB   = 1 ;

/**
 * CallBack fuction called by core dll locationnservice.lib on reciving
 * Location updates from location server
 * Implements HandleNotifyL() from base class MLocationCallBack
 *
 * @locationservice.lib dependency
 * @see MLocationCallBack in locationservice.h for details.
 */

class LocationInterfaceCB : public CBase , public MLocationCallBack
    {
    private :
    MLiwNotifyCallback  *iCallBack ;
    CLiwGenericParamList *iOutParmList ;
    CLiwGenericParamList *iInParmList ;
    TInt32 iTransactionId  ;
    TPositionModuleInfo *iModuleInfo ;  
    TUint iRequestType ;    
    /**
	 * Member variable representing what category of location information user is 
	 * interested in
	 */
	 
	 TInt iLocinfoCategory;      
      


    /**
     * Default constructor , to controlled construction
     */
    LocationInterfaceCB( ); 

    /**
     * Overloaded constructor which registers the callback adders
     *
     * @param aCallBack: Callback object after reciving location updates from core class
     * @param aInParamList: input paramater list for location request 
     * @param aOutParamList: out put paramater list to be which will contained location information
     * @param aModuleInfo module information of positioning module used
     * @param aTransactionId: Tracnsaction Id from recived from LIW 
     */
     
     LocationInterfaceCB( MLiwNotifyCallback* aCallBack , 
     					  const CLiwGenericParamList* aInParmList ,	
     				      //TPositionModuleInfo* aModuleInfo,
     				      TInt32 aTransactionId = 0 ) ;
     				      
    
     

    public :

    /**
     * Construction method for call back class
     *
     * @param aCallBack: Callback object after reciving location updates from core class
     * @param aInParamList: input paramater list for location request 
     * @param aOutParamList: out put paramater list to be which will contained location information
     * @param aModuleInfo module information of positioning module used
     * @param aTransactionId: Tracnsaction Id from recived from LIW 
     */

    static LocationInterfaceCB * NewL( MLiwNotifyCallback* aCallBack , 
    									 const CLiwGenericParamList* aInParmList, 
    									 //TPositionModuleInfo* aModuleInfo ,
    									 TInt32 aTransactionId = 0)  ;

    /**
     * Implementaion of HandleNotifyL() derived from  LocationInterfaceCB this function
     * is called by core dll locationservice.dll on reciving location updates
     *
     * @aOutPos GenericPositioninfo class which contains location information
     * @aError success/failure code passed by core dll.
     */
     
    TInt HandleNotifyL( HPositionGenericInfo* aOutPos , TInt aError ) ;
    
    /**
     * Function to set call back object type (Get location or Trace type), this is needed to 
     * for sending Event notifications to users(KLiwEventCompleted/KLiwEventInProgress) for
     * Getlocation and Trace Async calls 
     *
     * @aRequestType request type (Getlocation , Trace)
     */ 
    
    inline void SetRequestType(TInt aRequestType)
        {
            iRequestType = aRequestType ;
        }
    
    /**
     * Function to get the type of request(Trace/GetLocation) associated with this async 
     * object, 
     */
     
    TUint GetRequestType(void) 
        {
        return iRequestType ;
        }
    /**
     * This function returns transcation id associated with the Async request for 
     * which this callback is used
     */
    TInt32 GetTransactionId(void)
        {
        return iTransactionId ;
        }

    /**
     * Retruns the MLiwNotifyCallback object owned by this class
     */

    MLiwNotifyCallback* GetCallBackobj()
              {
              return iCallBack;  
              }
    /**
     * HandleL, an internal utility funtion which is called by HandleNotifyL method,
     * This methods encapsulates all the leaving methods which could be traped by 
     * HandleNotifyL method
     */
     
     void HandleL(HPositionGenericInfo* aOutPos , TInt aError )  ;  
     
      
    /**
     * destructor 
     */
    virtual ~LocationInterfaceCB( ) ;  //Default destructor   


    };

#endif // C_LOCATIONCB_H