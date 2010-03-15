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


CGetLoc::CGetLoc() :
CActive(CActive::EPriorityStandard)
                {

                }

CGetLoc::~CGetLoc()

    {
    iPositioner.Close() ;
    delete iGenericPosInfo;
    iLocationService = NULL;

    }
        
/**
 * Funtion name: ConstructL 
 * Constructs an active object and initalises this object 
 * with subsessions for communicating with location server
 */
        
void CGetLoc::ConstructL(RPositionServer& aPositionServer ,
        TPositionFieldIdList aList ,
        TInt aRequestType,        
        TPositionModuleId aModuleId)
    {
    // Initialise the position request sequence

    DoInitialiseL();


    if( aModuleId.iUid )
        {
        //Open a new subsession with position server
        User :: LeaveIfError((this->iPositioner).Open(aPositionServer,aModuleId)); 
        }

    else
        {
        //Open a new subsession with position server using default module
        User :: LeaveIfError((this->iPositioner).Open(aPositionServer)) ; 
        }

    //CleanupClosePushL(iPositioner);
    //Set the identity of this particular requestor
    User::LeaveIfError( (this->iPositioner).SetRequestor( 
            CRequestor::ERequestorService,
            CRequestor::EFormatApplication,
            KIdentity ) );

    this->iPosInfoBase = &(this->iPositionInfo);
    this->iRequestType = aRequestType;
    this->iGenericPosInfo = HPositionGenericInfo :: NewL();
    //CleanupStack :: PushL(this->iGenericPosInfo);

    if(aList)
        {
        User :: LeaveIfError((this->iGenericPosInfo)->SetRequestedFields(aList));
        }

    //CleanupStack ::Pop(this->iGenericPosInfo );
    //CleanupStack::Pop(&iPositioner);
    }
/**
 * Function name: NewL , 
 * Constructs a new core implementation object which will later 
 * Be added to active schedular 
 * on success returns pointer to constructed object, else leaves 
 * with various error codes 
*/
 
 
 
 
EXPORT_C CGetLoc* CGetLoc::NewL( RPositionServer& aPositionServer ,
        TPositionFieldIdList aList ,
        TInt aRequestType,
        TInt /*aLocationInfoCategory*/,
        TPositionModuleId aModuleId)
    {
    //Check for the presence of ActiveScheduler
    //Create the object

    CActiveScheduler* current = CActiveScheduler::Current();

    if(!current)
        {
        User::Leave(KErrNotFound); //Leave if consumer is not event driven
        }

    CGetLoc* self = new( ELeave ) CGetLoc();
    CleanupStack::PushL(self);

    self->ConstructL(aPositionServer ,
            aList ,
            aRequestType,               
            aModuleId);

    CleanupStack::Pop(self);

    //Return pointer to the created object
    return self;
    }


TInt CGetLoc::DoInitialiseL()
    {
    iCallBack = NULL ;
    iRequestStatus =0;      
    return KErrNone  ;
    }





/**
 * CGetLoc :: GetLocationUpdates  accepts update options from the consumers and 
 * submits an aynchronous request to the location server
 * Returns  the status of job submitted 
 */

TInt CGetLoc::GetLocationUpdates(CLocationService* aLocationService,MLocationCallBack* aCallBackObj,
        const TPositionUpdateOptions* aUpdateOptions)
    {
    //Pointer to CLocationService used in RunL
    iLocationService = aLocationService;

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
	    // updateopts.SetUpdateTimeOut(TTimeIntervalMicroSeconds(KSUpdateTimeOut));

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
    if (!IsActive())
        {
        SetActive();
        }
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
						if (!IsActive())
                            {
                            SetActive();
                            }
					}
					 	
				}
			}

			break ;
			}
        case KErrTimedOut:
            {
            iCallBack->HandleNotifyL(NULL , iStatus.Int()) ;
            //Re-issue the request even though there's an error
            if (iRequestType == KTraceRequest)
                {
                if (this->IsAdded() && !this->IsActive())
                    {          
                    if (!this->IsStatusComplete())
                        {
                        iPositioner.NotifyPositionUpdate( *iGenericPosInfo,
                                iStatus);
                        if (!IsActive())
                            {
                            SetActive();
                            }
                        }

                    }
                }
            break;
            }           
		case KErrArgument:
		case KPositionQualityLoss:         //Need to check this returnig s60 error code from here 
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
    if(iRequestType == KGetLocationRequest)
        {
        //Delete the Active Object associated with this request since it is completed

        if(iLocationService)
            {
            iLocationService->CancelService(iCallBack->GetTransactionId());
            }
        }    
	        	
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
