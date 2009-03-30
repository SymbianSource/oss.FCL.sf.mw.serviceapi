/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Implements location SAPI core class.
*
*/




#include "locationcoreimp.h"
#include "locationservice.h"





//Constructor

CGetLoc :: CGetLoc():CActive( CActive::EPriorityStandard )
    {
    
    }
        
/**
 * Funtion name: ConstructL 
 * Constructs an active object and initalises this object 
 * with subsessions for communicating with location server
 */
        
void CGetLoc::ConstructL()
    {
    // Initialise the position request sequence
  
    DoInitialiseL();
    
    }


/**
 * Function name: NewL , 
 * Constructs a new core implementation object which will later 
 * Be added to active schedular 
 * on success returns pointer to constructed object, else leaves 
 * with various error codes 
*/
 
 
 
 
EXPORT_C CGetLoc* CGetLoc::NewL( RPositionServer &aPositionServer , 
								 TPositionFieldIdList aList ,
								 TInt aRequestType,
								 TInt /*aLocationInfoCategory*/  )
	{
	//Check for the presence of ActiveScheduler
    //Create the object
    CActiveScheduler *current = CActiveScheduler::Current() ;

    if(!current)
        {
        User::Leave(KErrNotFound); //Leave if consumer is not event driven
        }
    	

    CGetLoc* self = new( ELeave ) CGetLoc();
    CleanupStack::PushL(self);

    TInt error = (self->iPositioner).Open(aPositionServer) ; //Open a new subsession with position server
    
    if(error)
        {
        User :: Leave( error) ;
        }
    
    //Set the identity of this particular requestor
    User::LeaveIfError( (self->iPositioner).SetRequestor( CRequestor::ERequestorService,
													      CRequestor::EFormatApplication,
													      KIdentity ) );
    


    self->iPosInfoBase = &(self->iPositionInfo) ; 
    self->iRequestType = aRequestType ;
    self->iGenericPosInfo = HPositionGenericInfo :: NewL() ;

    if(aList)
        {
        error = (self->iGenericPosInfo)->SetRequestedFields(aList) ;
        }

    User :: LeaveIfError(error) ;
    CleanupStack :: PushL(self->iGenericPosInfo) ;

    self->ConstructL();
    CleanupStack ::Pop(self->iGenericPosInfo );
    CleanupStack::Pop( self );

    //Return pointer to the created object
    return self;
	}

CGetLoc ::~CGetLoc()

    {
    iPositioner.Close() ;
    delete iGenericPosInfo ;

    }

TInt CGetLoc::DoInitialiseL()
    {
    iCallBack = NULL ;
    iRequestStatus =0;      
    return KErrNone  ;
    }





/**
 * CGetLoc :: GetLocation  accepts update options from the consumers 
 * returns  the status of job submitted 
 */

 TInt CGetLoc :: GetLocation( MLocationCallBack* aCallBackObj ,  
 									const TPositionUpdateOptions* aUpdateOptions )
    {

    //Register the call back address 
    iCallBack  = aCallBackObj ;
    TInt error = KErrNone ;
    //First set the update options before Issuing Notification request to server
    if(aUpdateOptions)
    	{
    	error = iPositioner.SetUpdateOptions(*aUpdateOptions);
    	if(error)
		    {
		    return error ;
		    }

    	}
    else //set the default values
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


    

    

    //Now add this object as part of active schedular

    if(!(this->IsAdded()))
    {
    CActiveScheduler :: Add(this) 	;
    }

    iPositioner.NotifyPositionUpdate( *iGenericPosInfo, iStatus );
    SetActive() ;
    return KErrNone ;
    }





/**
 * Function Name :GetLocationUpdates
 * Notifies the user whenever his position changes
 * Returns status of the submitted job
 */

 TInt CGetLoc:: GetLocationUpdates( MLocationCallBack* aCallBackObj ,
 										 const TPositionUpdateOptions* aUpdateOptions )
    {

    //Register the call back address
    iCallBack = aCallBackObj ;

    if(aUpdateOptions)
    	{
    	 TInt error = iPositioner.SetUpdateOptions(*aUpdateOptions) ;
    	 
    	 if(error)     //If update options failed then no return error to caller
     		{
    	 	return error ; 
     		}
    	}
    else //set the default values
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


    if(!(this->IsAdded()))  //Add to the active list if not added 
    {
    	CActiveScheduler :: Add(this) 	;
    }


    iPositioner.NotifyPositionUpdate( *iGenericPosInfo, iStatus );
    SetActive() ;
    return KErrNone ;
    }


/**
 * RunL Method called by Active Scheduler after reciving an event 
 * This method actually calls the registered callbacks 
 */

void CGetLoc :: RunL()
	{
	switch ( iStatus.Int() )
	{

		case KErrNone:                    //For both KErrNone nad partial update call the same call back
		case KPositionPartialUpdate :
		{
		
			if(iCallBack)
			{
					iCallBack->HandleNotifyL(iGenericPosInfo , KErrNone ) ;	        		
			}

			if(iRequestType == KTraceRequest)	
			{
				if(this->IsAdded())
				
				{
					if(!this->IsStatusComplete())
					{
						iPositioner.NotifyPositionUpdate( *iGenericPosInfo, iStatus );
						SetActive();
					}
					 	
				}
			}

			break ;
			}

		case KErrArgument:
		case KPositionQualityLoss:         //Need to check this returnig s60 error code from here 
		case KErrTimedOut :
		case KErrNotFound :       //Service provider not available, or gone down in between
		{

			iCallBack->HandleNotifyL(NULL , iStatus.Int()) ;
			break ;
		}

		default :
		{

			iCallBack->HandleNotifyL(NULL , iStatus.Int()) ;
			break ;

		}
	} //End of Switch

	        	
	}

/**
 *DoCancel Method called by Cancel Method 
 */
void CGetLoc :: DoCancel()
    {
    //Check weather any one has registered for callbacks then
    if(iCallBack)
    	{
    	iPositioner.CancelRequest(EPositionerNotifyPositionUpdate);
    	}


    }
