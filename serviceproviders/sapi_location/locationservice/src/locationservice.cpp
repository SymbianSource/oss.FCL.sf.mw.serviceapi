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
 * Default constructor
 */
 
 
EXPORT_C CLocationService :: CLocationService()
						  :iGenericPosInfo(NULL)
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

                }
        }
    iPosServer.Close();
    iRegTable.Close();
    delete iGenericPosInfo;

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
 * Initialises position server and positioner and
 * begins the position request sequence.
 */

void CLocationService::ConstructL()
    {
    User :: LeaveIfError(iPosServer.Connect());
    //CleanupClosePushL(iPosServer);
    iGenericPosInfo = HPositionGenericInfo::NewL() ;

    if ( !iGenericPosInfo )
        {
        User::Leave( KErrNoMemory ) ;
        }
    
    //Get the module id of the default module available
    //User :: LeaveIfError(iPosServer.GetDefaultModuleId(iModuleId));

    //CleanupStack::Pop(&iPosServer);
    }

/**
 * CLocationService::GetHighAccuracyModule
 * This function returns the module id of highest accuracy 
 * module that is available on the phone currently.
 */
void CLocationService::GetHighAccuracyModuleL(TPositionModuleId* aModId)
    {
    TPositionModuleId moduleId = TUid::Null();
    TPositionModuleInfo modInfo;
    TUint numOfModules = 0;

    //Flags used for indicating if a particular module is found
    TInt termInternalFlag = 0;   
    TInt termFlag = 0 ,assisFlag = 0 ,networkFlag = 0,unknownFlag = 0;
    //TInt err;
    
    User::LeaveIfError(iPosServer.GetNumModules(numOfModules));
        

    for( TInt i=0;i< numOfModules;i++ )
        {
        iPosServer.GetModuleInfoByIndex(i,modInfo);

				if( modInfo.TechnologyType() == modInfo.ETechnologyAssisted  && 
                 modInfo.IsAvailable())
            {

            assisFlag = 1;
            moduleId = modInfo.ModuleId();
						break;
            }
            
        if( modInfo.TechnologyType() == modInfo.ETechnologyTerminal  && 
                !assisFlag && !termInternalFlag && modInfo.IsAvailable() )
            {

            termFlag = 1;
            moduleId = modInfo.ModuleId();

            //Internal Module takes higher priority than External module 
            if(modInfo.DeviceLocation() == modInfo.EDeviceInternal)
                {
                termInternalFlag = 1;                
                }

            }

        if(modInfo.TechnologyType() == modInfo.ETechnologyNetwork && 
                !assisFlag  && !termFlag && modInfo.IsAvailable())
            {

            networkFlag = 1;
            moduleId = modInfo.ModuleId();

            }

        if( modInfo.TechnologyType() == modInfo.ETechnologyUnknown && 
                !assisFlag  && !termFlag && 
                !networkFlag && modInfo.IsAvailable() )
            {

            unknownFlag = 1;
            moduleId = modInfo.ModuleId();                            
            }
        }
    *aModId =  moduleId;
    }

/**
 * CLocationService :: GetLocationL with update options, this function gets users current location
 * returns 0 on success and Symbian specific error codes on failure
 */

EXPORT_C void  CLocationService :: GetLocationL( TPositionInfoBase* aInfoBase ,
                                                 const TPositionUpdateOptions* aUpdateOpts,
                                                 TBool aEnableHighAcc )
    {
    //Check if atleast one of the module is enabled
    TInt modError = iPosServer.GetDefaultModuleId(iModuleId);
    if (modError)
        {
        User::Leave(errServiceNotReady);
        }
    // Open subsession to the position server
    TPositionModuleId ModuleId;
    //TInt error;
    if(aEnableHighAcc)
        {
        GetHighAccuracyModuleL(&ModuleId);
       
        User::LeaveIfError(iPositioner.Open(iPosServer,ModuleId));
        
        iModuleId = ModuleId;
        }
    else
        {
        User::LeaveIfError(iPositioner.Open(iPosServer));
        User::LeaveIfError(iPosServer.GetDefaultModuleId(iModuleId));
        }

    
    //CleanupClosePushL(iPositioner);
    TInt errorInprocessing = KErrNone;
    errorInprocessing = SetRequestingField();
    if(errorInprocessing)
        {
        iPositioner.Close();
        User::Leave(errorInprocessing);
        }
   // (static_cast<HPositionGenericInfo*>(aInfoBase))->ClearRequestedFields() ;
    (static_cast<HPositionGenericInfo*>(aInfoBase))->SetRequestedFields(iFieldList) ;
    //setting identity for this requestor
    User::LeaveIfError( iPositioner.SetRequestor( CRequestor::ERequestorService,
            CRequestor::EFormatApplication,
            KIdentity ) );

    TRequestStatus status;

    if(aUpdateOpts)
        {
        TInt errorInprocessing = iPositioner.SetUpdateOptions(*aUpdateOpts);
        
        if(errorInprocessing)
           {
           iPositioner.Close();
           User::Leave(errorInprocessing);
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
    //CleanupStack::PopAndDestroy(&iPositioner);
    iPositioner.Close();
    
    User::LeaveIfError(status.Int());
    }

/**
 * CLocationService::ModuleInfo, gets information about the location moudleid of currently used
 * positioning moulde, currently this methods only supports info of default module indentifier
 */

EXPORT_C TInt CLocationService :: GetModuleInfo( 
        TPositionModuleInfoBase& aModuleInfo ) const
    {
    return  iPosServer.GetModuleInfoById(iModuleId , aModuleInfo) ;

    }



/**
 * Function Name : GetLocation Asynchronous
 * This function gets users current location
 * returns status of job submitted 
 */
EXPORT_C void CLocationService :: GetLocationL( MLocationCallBack* aCallBackObj ,
        TInt aLocationInfoCategory,
        TPositionFieldIdList/* aFieldList*/ ,
        const TPositionUpdateOptions* aUpateOptions,
        TBool aEnableHighAcc 
)
    {  
    TInt modError = iPosServer.GetDefaultModuleId(iModuleId);
    if (modError)
        {
        User::Leave(errServiceNotReady);
        }
    TPositionModuleId ModuleId;
    if(aEnableHighAcc)
        {
        GetHighAccuracyModuleL(&ModuleId);
        iModuleId = ModuleId;
        
        }
    else
        {
        //Indicates that when opening the subsession ,moudleId need not be specified
        ModuleId.iUid = 0;       
        User::LeaveIfError(iPosServer.GetDefaultModuleId(iModuleId));
        }

    TInt err = KErrGeneral;
    User::LeaveIfError(SetSupportedFields());

    CGetLoc* activeGetLoc = CGetLoc :: NewL(iPosServer ,
            iFieldList ,
            KGetLocationRequest,
            aLocationInfoCategory,
            ModuleId) ;

    err = activeGetLoc->GetLocationUpdates(this,aCallBackObj,aUpateOptions);

    if ( KErrNone == err )
        {
        iRegTable.Append(activeGetLoc);
        }
    else
        {
        delete activeGetLoc; //Clean up
        User::Leave(err);
        }
    }



/**
 * CLocationService :: TraceL  Notifies user if any changes occurs to his  current position, 
 * types of updates required are specified as part of Updateoptions.
 * Returns 0 on success and symbian specific error codes on failures
 */

EXPORT_C void CLocationService :: TraceL( MLocationCallBack* aCallBackObj ,
        TInt aLocationInfoCategory,
        TPositionFieldIdList/* aFiledList*/ ,
        const TPositionUpdateOptions* aUpateOptions,
        TBool aEnableHighAcc )
    {
    TInt modError = iPosServer.GetDefaultModuleId(iModuleId);
    if (modError)
        {
        User::Leave(errServiceNotReady);
        }
    TPositionModuleId ModuleId;
    if(aEnableHighAcc)
        {
        GetHighAccuracyModuleL(&ModuleId);
        if(ModuleId.iUid == NULL)
            {
            User::Leave(KErrGeneral);
            }
        iModuleId = ModuleId;
        }
    else
        {
        //Indicates that when opening the subsession ,moudleId need not be specified
        ModuleId.iUid = 0;          
        User::LeaveIfError(iPosServer.GetDefaultModuleId(iModuleId));
        }
    
    CGetLoc* activeTrace = CGetLoc :: NewL(iPosServer ,
            iFieldList ,
            KTraceRequest,
            aLocationInfoCategory,
            ModuleId) ;

    TInt ret = activeTrace->GetLocationUpdates(this,aCallBackObj , aUpateOptions);

    if (ret == KErrNone)
        {        
        iRegTable.Append(activeTrace);
        }
    else
        { 
        //Cleanup the allocated object
        delete activeTrace;
        User::Leave(ret);
        }

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

EXPORT_C TInt CLocationService :: GetLastKnownLoc( TPosition& aResultPos )
    {
    TInt error = iPositioner.Open(iPosServer);


    // The opening of a subsession failed
    if ( KErrNone != error )
        {
        iPosServer.Close();
        return error ;
        }
		
    //setting identity for this requestor
    error = iPositioner.SetRequestor( CRequestor::ERequestorService,
            CRequestor::EFormatApplication,
            KIdentity ) ;

	  if ( KErrNone != error )
        {
        iPositioner.Close();
        return error ;
        }
	
    TRequestStatus Status  = KRequestPending ;
    TPositionInfo  posinfo  ;
    TPositionInfoBase *posinfoBase =  &posinfo ;	

    iPositioner.GetLastKnownPosition(*posinfoBase,Status);
    User::WaitForRequest(Status);
    posinfo.GetPosition(aResultPos) ;
    
    iPositioner.Close();
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
        TInt i;
        for( i = 0; i< iRegTable.Count(); i++)
            {
            if(iRegTable[i] )
                {

                if((((iRegTable[i]->GetCallBackobj())->GetRequestType()) == 
                KGetLocationReq) && (aCancelparam == ECancelGetLocation ))              
                    {                  
                    if(iRegTable[i]->IsAdded())
                        {         
                        iRegTable[i]->Deque();
                        }


                    delete iRegTable[i];
                    iRegTable[i] = NULL;
                    return KErrNone;
                    }

                else if ((((iRegTable[i]->GetCallBackobj())->GetRequestType()) == 
                KTraceReq) &&  (aCancelparam == ECancelTrace ))
                    {
                    if(iRegTable[i]->IsAdded())
                        {
                        iRegTable[i]->Deque();
                        }

                    iRegTable[i]->SetStatusComplete();

                    delete iRegTable[i];
                    iRegTable[i] = NULL;
                    return KErrNone;
                    }
                }  
            }    
        return KErrNotFound;
        }

    return KErrArgument;
    }

/**
 * CancelService : Cancels Requested asynchronous requests,
 * Input : TransactionId returned by the Async request,
 * Returns success(KErrNone) if service canceled or else error if 
 * input parameter is invalid
 */
EXPORT_C TInt CLocationService::CancelService( TInt aTransId)
    {
    TInt i;
    for( i = 0; i< iRegTable.Count(); i++)
        {
        if(iRegTable[i])
            {
            if(aTransId == 
            (iRegTable[i]->GetCallBackobj())->GetTransactionId())
                {
                if(iRegTable[i]->IsAdded())
                    {
                    iRegTable[i]->Deque();
                    }
                if(((iRegTable[i]->GetCallBackobj())->GetRequestType()) == 
                KTraceReq)
                    {
                    iRegTable[i]->SetStatusComplete();
                    }
                delete iRegTable[i];
                iRegTable[i] = NULL;
                return KErrNone;
                }
            }
        }

    return KErrNotFound;
    }
TInt CLocationService :: SetSupportedFields()
    {
    
    TUint fieldIter = 0 ;
    //get positioning module information
    TInt infoerr = GetModuleInfo(iModuleInfo);
    if (infoerr)
        {
        return infoerr;
        }

    TPositionModuleInfo :: TCapabilities  currCapability  = iModuleInfo.Capabilities() ;

    if(currCapability & TPositionModuleInfo :: ECapabilitySpeed) //set horizontal,vertical speeds along with errros 
        {   
        iFieldList[fieldIter++] = EPositionFieldHorizontalSpeed ;
        
        iFieldList[fieldIter++] = EPositionFieldHorizontalSpeedError ;
        iFieldList[fieldIter++] = EPositionFieldVerticalSpeed ;
        iFieldList[fieldIter++] = EPositionFieldVerticalSpeedError ;
        }

    if(currCapability & TPositionModuleInfo :: ECapabilitySatellite) //Set satellite info fields if positioning module supports
        {                                                               //
        
        iFieldList[fieldIter++] = EPositionFieldSatelliteNumInView ;
        iFieldList[fieldIter++] = EPositionFieldSatelliteNumUsed ;
        iFieldList[fieldIter++] = EPositionFieldSatelliteTime ;
        iFieldList[fieldIter++] = EPositionFieldSatelliteHorizontalDoP ;
        iFieldList[fieldIter++] = EPositionFieldSatelliteVerticalDoP ;
        
        }

    if(currCapability & TPositionModuleInfo :: ECapabilityDirection) //Set Direction info fields if positioning module supports
        {
        
        iFieldList[fieldIter++] = EPositionFieldTrueCourse ;
        iFieldList[fieldIter++] = EPositionFieldTrueCourseError ;
        iFieldList[fieldIter++] = EPositionFieldMagneticCourse ;
        iFieldList[fieldIter++] = EPositionFieldMagneticCourseError ;
        
        }
    

    if(currCapability & TPositionModuleInfo :: ECapabilityCompass) //Set NMEA fields if positioning module supports 
        {
            
        iFieldList[fieldIter++] = EPositionFieldHeading ;
        iFieldList[fieldIter++] = EPositionFieldHeadingError ;
        iFieldList[fieldIter++] = EPositionFieldMagneticHeading ;
        iFieldList[fieldIter++] = EPositionFieldMagneticHeadingError ;
        
        }
    
    
   iFieldList[fieldIter] = EPositionFieldNone  ;   //Field Termination 
   iGenericPosInfo->ClearRequestedFields() ;
   iGenericPosInfo->SetRequestedFields(iFieldList) ;
  
  
   return KErrNone ;
   }
TInt CLocationService :: SetRequestingField()
    {
    
    TUint fieldIter = 0 ;
    //get positioning module information
    TInt infoerr = GetModuleInfo(iModuleInfo);
    if (infoerr)
        {
        return infoerr;
        }

    TPositionModuleInfo :: TCapabilities  currCapability  = iModuleInfo.Capabilities() ;

    if(currCapability & TPositionModuleInfo :: ECapabilitySpeed) //set horizontal,vertical speeds along with errros 
        {   
        iFieldList[fieldIter++] = EPositionFieldHorizontalSpeed ;
        
        iFieldList[fieldIter++] = EPositionFieldHorizontalSpeedError ;
        iFieldList[fieldIter++] = EPositionFieldVerticalSpeed ;
        iFieldList[fieldIter++] = EPositionFieldVerticalSpeedError ;
        }

    if(currCapability & TPositionModuleInfo :: ECapabilitySatellite) //Set satellite info fields if positioning module supports
        {                                                               //
        
        iFieldList[fieldIter++] = EPositionFieldSatelliteNumInView ;
        iFieldList[fieldIter++] = EPositionFieldSatelliteNumUsed ;
        iFieldList[fieldIter++] = EPositionFieldSatelliteTime ;
        iFieldList[fieldIter++] = EPositionFieldSatelliteHorizontalDoP ;
        iFieldList[fieldIter++] = EPositionFieldSatelliteVerticalDoP ;
        
        }

    if(currCapability & TPositionModuleInfo :: ECapabilityDirection) //Set Direction info fields if positioning module supports
        {
        
        iFieldList[fieldIter++] = EPositionFieldTrueCourse ;
        iFieldList[fieldIter++] = EPositionFieldTrueCourseError ;
        iFieldList[fieldIter++] = EPositionFieldMagneticCourse ;
        iFieldList[fieldIter++] = EPositionFieldMagneticCourseError ;
        
        }
    

    if(currCapability & TPositionModuleInfo :: ECapabilityCompass) //Set NMEA fields if positioning module supports 
        {
            
        iFieldList[fieldIter++] = EPositionFieldHeading ;
        iFieldList[fieldIter++] = EPositionFieldHeadingError ;
        iFieldList[fieldIter++] = EPositionFieldMagneticHeading ;
        iFieldList[fieldIter++] = EPositionFieldMagneticHeadingError ;
        
        }
    
    
   iFieldList[fieldIter] = EPositionFieldNone  ;   //Field Termination 
   
  
  
   return KErrNone ;
   }

