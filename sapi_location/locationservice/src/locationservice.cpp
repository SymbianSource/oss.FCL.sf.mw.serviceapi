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
* Description:  Implements location SAPI core ;works as wrapper
*   around core implementaion.
*
*/



#include "locationcoreimp.h"
#include "locationservice.h"

/**
 * Maximum number of active objects that can be created : at present only each corresponding
 * to location-asynch and trace
 */
const TInt  KMAXAO = 2;




/**
 * Default constructor
 */
 
 
EXPORT_C CLocationService :: CLocationService()
    {
	//No Implementation Required Here
    }


/**
 * Destructor
 */

EXPORT_C CLocationService :: ~CLocationService()
    {
    iPositioner.Close();	
    
    
    //Destroy all the contents of the registration table 
    for(TInt iter = 0 ; iter < iRegTable.Count() ; ++iter)
        {
            if(iRegTable[iter])
                {
                if(iRegTable[iter]->IsActive())
                    {
                    iRegTable[iter]->Deque() ;
                    }
                delete iRegTable[iter];
                iRegTable[iter] = NULL ;

                }
        }
    iPosServer.Close();
    iRegTable.Close();

    }
 
/**
 * CLocationService::NewL
 * Two-phased constructor.
 */


EXPORT_C  CLocationService *CLocationService :: NewL()
    {
    CLocationService *self = new(ELeave)CLocationService() ;
    CleanupStack::PushL(self);
    self->ConstructL() ;
    CleanupStack::Pop(self) ;
    return self ;

    }
 
/**
 * CLocationService::ConstructL
 * Symbian 2nd phase constructor can leave.
 */

void CLocationService::ConstructL()
    {

    DoInitialiseL();
    }



/**
 * CLocationService::DoInitialiseL
 * Initialises position server and positioner and
 * begins the position request sequence.
 */

EXPORT_C void CLocationService :: DoInitialiseL()
    {
    TInt error = iPosServer.Connect( );
    // The connection failed
  
    User :: LeaveIfError(error) ;
    
    // Open subsession to the position server
    error = iPositioner.Open(iPosServer);

    // The opening of a subsession failed
    if ( KErrNone != error )
        {
        iPosServer.Close();
        User :: Leave( error );
        }


    //setting identity for this requestor
    User::LeaveIfError( iPositioner.SetRequestor( CRequestor::ERequestorService,
												  CRequestor::EFormatApplication,
												  KIdentity ) );
    
    //Initialise index which means there is no 
    //active object created yet
    iIndex = 0 ;
    //Initialising array pointer to NULL 

    for ( TInt count = 0;count < KMAXAO;count++)
        {
        iRegTable.Insert(NULL,count);
        }
    
       
     //Getthe module id used by location server for sapi location calls.
    error = iPosServer.GetDefaultModuleId(iModuleId);

    User :: LeaveIfError(error) ;

    }


/**
 * CLocationService :: GetLocationL with update options, this function gets users current location
 * returns 0 on success and Symbian specific error codes on failure
 */

EXPORT_C TInt  CLocationService :: GetLocationL( TPositionInfoBase* aInfoBase , const TPositionUpdateOptions* aUpdateOpts )
    {

    TRequestStatus status  ;

    if(aUpdateOpts)
        {
        TInt error;
        error = iPositioner.SetUpdateOptions(*aUpdateOpts);
        if( error)
	    	{
            return error ;
            }
        
        }
    else
        {
        TPositionUpdateOptions updateopts ;
        
        // Set update interval to one second to receive one position data per second
	    updateopts.SetUpdateInterval(TTimeIntervalMicroSeconds(KSUpdateInterval));

	    // If position server could not get position
	    // In two minutes it will terminate the position request
	    updateopts.SetUpdateTimeOut(TTimeIntervalMicroSeconds(KSUpdateTimeOut));

	    // Positions which have time stamp below KMaxAge can be reused
	    updateopts.SetMaxUpdateAge(TTimeIntervalMicroSeconds(KSMaxAge));

	    // Enables location framework to send partial position data
	    updateopts.SetAcceptPartialUpdates(FALSE);

        
        iPositioner.SetUpdateOptions(updateopts) ;
        }


    iPositioner.NotifyPositionUpdate( *aInfoBase, status );
    User :: WaitForRequest(status) ;

    return status.Int() ;
    }

/**
 * CLocationService::ModuleInfo, gets information about the location moudleid of currently used
 * positioning moulde, currently this methods only supports info of default module indentifier
 */

 EXPORT_C TInt CLocationService :: GetModuleInfo( TPositionModuleInfoBase& aModuleInfo )   const
    {
    return  iPosServer.GetModuleInfoById(iModuleId , aModuleInfo) ;

    }



/**
 * Function Name : GetLocation Asynchronous
 * This function gets users current location
 * returns status of job submitted 
 */
EXPORT_C TInt CLocationService :: GetLocationL( MLocationCallBack* aCallBackObj ,
													TInt aLocationInfoCategory, 
													TPositionFieldIdList aFieldList ,
													const TPositionUpdateOptions* aUpateOptions
													 )
    {

    if(iRegTable[KARRAY_INDEX_GETLOCATION])
        {
        if(iRegTable[KARRAY_INDEX_GETLOCATION]->IsActive())
            {
            return KErrInUse ;                //Return Error is Already registred 
            }

        delete iRegTable[KARRAY_INDEX_GETLOCATION] ;
        iRegTable[KARRAY_INDEX_GETLOCATION] = NULL ;

        }

    CGetLoc *activeGetLoc = CGetLoc :: NewL(iPosServer ,
    									    aFieldList ,	
                                            KGetLocationRequest,
                                            aLocationInfoCategory ) ;
    	//after creation of each active object increment counter by 1
    
    TInt err = 	activeGetLoc->GetLocation(aCallBackObj , aUpateOptions) ;
    	
    if ( KErrNone == err  )
        {

        iIndex = KARRAY_INDEX_GETLOCATION;  //for getlocation we are storing the pointer in 0th slot
        iRegTable[KARRAY_INDEX_GETLOCATION] = activeGetLoc ;
        }
        
    else 
        {
        delete activeGetLoc ;	//Clean up
        }	

    return err;	
    }



/**
 * CLocationService :: TraceL  Notifies user if any changes occurs to his  current position, 
 * types of updates required are specified as part of Updateoptions.
 * Returns 0 on success and symbian specific error codes on failures
 */

EXPORT_C TInt CLocationService :: TraceL( MLocationCallBack* aCallBackObj ,
												TInt aLocationInfoCategory, 
												TPositionFieldIdList aFiledList ,
												const TPositionUpdateOptions* aUpateOptions )
    {

    if(iRegTable[KARRAY_INDEX_TRACE]) //Return Error to user is the reg table slot is not free
        {
        if(iRegTable[KARRAY_INDEX_TRACE]->IsAdded())  
            {
            return KErrInUse ;            
            }
        //Reuse the existing inactive object
        delete iRegTable[KARRAY_INDEX_TRACE]  ; //Activate this asynchronous job
        iRegTable[KARRAY_INDEX_TRACE] = NULL ;

        }

    CGetLoc *activeTrace = CGetLoc :: NewL(iPosServer ,
                                           aFiledList , 
                                           KTraceRequest,
                                           aLocationInfoCategory) ;

    TInt ret  = activeTrace->GetLocationUpdates(aCallBackObj , aUpateOptions) ;

    if (ret == KErrNone)  
        {
        iIndex = KARRAY_INDEX_TRACE;	
        iRegTable[KARRAY_INDEX_TRACE] = activeTrace ;
        }
    else
        {         //Cleanup the allocated object
        delete activeTrace ;
        }	
       
    return ret;
    }

/**
 * MathOparation to find distance and bearingto  between two coordinates,and to move
 * (Translate)
 * one coordinate to another.
 * Before decoding result of a particular requested service consumer code must check
 * for the returned error code. Result field will be valid only when return code is
 * KErrNone.
 */

EXPORT_C TInt CLocationService :: MathOperation( inpparam& aInput )
	{
	if ( aInput.servicechoice == EDistance )  //find distance between two location
		{
		//get the distance between two specified position
		TInt error = aInput.source.Distance(aInput.destination , aInput.result);
		return error;

		}
	else if ( aInput.servicechoice == EBearingTo )
		{
		//get the bearingTo	between specified coordinates
		TInt error = aInput.source.BearingTo(aInput.destination,aInput.result);
		return error;
		}
	else if ( aInput.servicechoice == EMove )	
		{
		//Translate the source coordinate to the target coordinate by specified bearing and distance
		TInt error = aInput.source.Move(aInput.bearing,aInput.distance);
		return error;			
		}
	//In case service asked is not supported 
	return KErrNotSupported;	
	}


/**
 * Synchronous function which returns users last known position
 */

TInt CLocationService :: GetLastKnownLoc( TPosition& aResultPos )
    {
    TRequestStatus Status  = KRequestPending ;
    TPositionInfo  posinfo  ;
    TPositionInfoBase *posinfoBase =  &posinfo ;	

    iPositioner.GetLastKnownPosition(*posinfoBase,Status);
    User::WaitForRequest(Status);
    posinfo.GetPosition(aResultPos) ;

    return Status.Int() ;

    }

/**
 * CancelOnGoingService : Cancells Requested asynchronous requests,
 * Input : Type of request to be cancelled(Trace , Getlocation),
 * Returns success(KErrNone) if service cancelled or else error if 
 * input parameter is invalid
 */
EXPORT_C TInt CLocationService::CancelOnGoingService( TInt aCancelparam )
    {
    if ( (aCancelparam == ECancelGetLocation ) || (aCancelparam == ECancelTrace))
        {
        CGetLoc* ptr = iRegTable[aCancelparam];
        if(iRegTable[aCancelparam])
            {
            if(iRegTable[aCancelparam]->IsAdded())
                {
                iRegTable[aCancelparam]->Deque() ;
                }
            if( ( aCancelparam == ECancelTrace ) )
            	iRegTable[aCancelparam]->SetStatusComplete();
            	delete iRegTable[aCancelparam] ;
            iRegTable[aCancelparam] = NULL ;
            return KErrNone;
            }
        return KErrNotFound ;

        }

    return KErrArgument;

    }

