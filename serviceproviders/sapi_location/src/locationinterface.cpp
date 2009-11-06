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
* Description:  implements interface class for location sapi
*
*/

#include <e32base.h>
#include <LiwCommon.h>
#include <lbs.h>
#include <LbsRequestor.h>

#include <lbscommon.h>
#include <lbssatellite.h>
#include "locationinterface.h"
#include "locationcb.h"
#include "locationservice.h"
#include "locationerrormessage.hrh"
using namespace LIW;



//Error code for bad time
const TInt KErrBadTime = -125;

/**
 * destructor
 */



CLocationInterface :: ~CLocationInterface()
    {
 	 
 	 delete iLocationService ;
 	  	 
 	 
 	 
 	 for(TInt iter = 0 ; iter < iHandleCB.Count() ; ++iter)
 	 	{
 	 	 delete iHandleCB[iter] ;
 	 	}
 	 iHandleCB.Close();
	 delete iGenericPosition ;
 
 	
    }

/**
 * Default constructor
 */
 
CLocationInterface::CLocationInterface()
    {
    //No Implementation Required Here
    }
void CLocationInterface::ConstructL()
    {
    iGenericPosition = HPositionGenericInfo::NewL() ;

    if ( !iGenericPosition )
        {
        User::Leave( KErrNoMemory ) ;
        }

    iLocationService = CLocationService::NewL() ;
    //User::LeaveIfError( iLocationService->GetModuleInfo( iModuleInfo ) );
    //User::LeaveIfError( this->SetSupportedFields() );
    }


/**
 * This function is a static method to create iLocatinInterface object
 * return pointer to constructed object else paincs with symbian painc 
 * code
 */

CLocationInterface* CLocationInterface::NewL()
    {
    CLocationInterface* self = new(ELeave)CLocationInterface();

    CleanupStack::PushL( self ) ;

    self->ConstructL();

    CleanupStack::Pop( self ) ;
    return self;

    }
 TInt  CLocationInterface::ConvertToSapiError(TInt aSymbianErr)
	 {
	 TInt sapiErr(SErrGeneralError);
	 switch (aSymbianErr)
    	{
      //case EPosLmInvalidArgument:
   		case KErrBadName:
    	case KErrPositionIncalculable :
   		case KErrArgument:			
   		    {
   		    sapiErr = SErrBadArgumentType;
   		    break;
   		    }
   		case KErrNotSupported:
   		    {
   		    sapiErr = SErrServiceNotSupported;
   		    break;
   		    }   		
   		case KErrInUse:	
   		    {
   		    sapiErr = SErrServiceInUse;
   		    break;
   		    }
    	case KErrTimedOut:
	    	{
	    	sapiErr = SErrServiceTimedOut;
	    	break;
	    		
	    	}
    	case KErrAccessDenied:
	    	{
	    	sapiErr = SErrAccessDenied;
	    	break;	
	    	}
    	case KErrNone:
    		{
    		sapiErr = SErrNone;
    		break;	
    		}
   		
		case KErrNotFound:
    		{
    		sapiErr = SErrNotFound;
    		break;	
    		}
    		
		case SErrMissingArgument:
			{
				sapiErr = SErrMissingArgument;
				break;
			}
		case SErrServiceNotReady:
		    {
                sapiErr = SErrServiceNotReady;
		        break;
			}
		default:
			{
				sapiErr = SErrGeneralError;
			}
    }
    return sapiErr;

	 
	 }
 /**
  * CLocationInterface::CmdExecuteL, this method is called by CLocationInterface::HandleCmdL()
  * to catch any leaves that might occur during execution of a LiwCommand.This is an private 
  * method of this class.
  */

void CLocationInterface::CmdExecuteL(
         	 			    const TDesC8& aCmdName,
                            const CLiwGenericParamList& aInParamList ,
                            CLiwGenericParamList& aOutParamList,
                            TUint aCmdOptions,
                            MLiwNotifyCallback* aCallback )
    {


    aOutParamList.Reset() ;
    
    /*
     * To indicate position based parsing for all the parameters
     */
    TBool posBasedFlag = EFalse;
    if( aCmdOptions & KLiwOptCancel ) // for cancel asynchronous request
        {
          
          TInt ret = 0 ;
          
          const TLiwGenericParam *transidparam = aInParamList.FindFirst(ret , KTransactionId) ;
          
          if( !transidparam )
            {
            //Possibility of position based parsing
            
            TInt argCount = aInParamList.Count();
            if( argCount >= 1 )
	            {
	            transidparam = &aInParamList[Index0];	
	            }
	        if ( !transidparam )
		       {
		       aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
                                      TLiwVariant(KCancelTransactionIdMissing)));
		       User::Leave( KErrArgument );
		       }
                
            }
            
          TInt32 transid = (transidparam->Value()).AsTInt32() ;
        //Get Callback object curresponding to this transaction Id 
        MLiwNotifyCallback* callBack = NULL;
        TInt ncalls = iHandleCB.Count() ;

        for (TInt iter = 0; iter < ncalls; ++iter)
            {

            if (iHandleCB[iter])
                {
                if (iHandleCB[iter]->GetTransactionId() == transid)
                    {
                    //Get the callback object associated with this Transaction Id
                    callBack = iHandleCB[iter]->GetCallBackobj();

                    }
                }

            }
          if (!callBack)
	          {
	          aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
                                      TLiwVariant(KCancelInvalidTransactionId)));
              User::Leave(KErrNotFound);	
	          }
          
        //Cancel the exisiting request
        User::LeaveIfError(iLocationService->CancelService(transid));
          
          //Send notification about the cancelled state to consumer
          callBack->HandleNotifyL(transid  , KLiwEventCanceled , 
                                    aOutParamList,   aInParamList) ;
            
        }
          
    //LastKnownLocation Request is made by consumer
    else if( !(aCmdName.CompareF( KCmdLastLocation )) )
        {
        //Extract Update options from input List
        User::LeaveIfError(iLocationService->GetLastKnownLoc(iPosition)) ;            
        TUint category1 = EBasicInfo;

        iGenericPosition->SetPosition(iPosition);
        GetLocationInfo(aOutParamList, category1) ;

        }

    
    //GetLocation request is made by consumer
    else if( !( aCmdName.CompareF( KCmdGetLocation ) ) )                         
        {
        TInt ret  =KErrNone ;
        //Extract category of Location Information user is interested in
        TInt index = 0;
        TPtrC posInfoCategory(KLocationBasicinfo);
        TInt32 transid = aCallback->GetTransactionID() ;
        //This flag indicates whether user has supplied a value for category of
        //location information or not
        TBool infoFlag = FALSE;
        
        const TLiwGenericParam *smapparam = aInParamList.FindFirst(index , KLocationInfoCategory) ;
        
        
        
        //if smapparam is NULL still there exist possibility of position based parsing
        if ( !smapparam )
	        {
	        TInt count = aInParamList.Count();
	        if (count >= 1)	
		        {
		        smapparam = &aInParamList[Index0];
		        
		        if (smapparam && ( smapparam->Name() == KNullDesC8 ) )
			        {
			        TLiwVariant variant =  smapparam->Value();
			        
			        if( variant.TypeId() != LIW::EVariantTypeDesC )
				        {
				        aOutParamList.AppendL( TLiwGenericParam( KErrorMessage,
                                               TLiwVariant( KGetLocationWrongInfoType ) ) );
                        User::Leave( KErrArgument );
				        //Leave with error code	
				        }
                    //indicates that position based parsing has been done 
                    posBasedFlag = ETrue;
	                posInfoCategory.Set( variant.AsDes() );
	                
	                //Set infoFlag to indicate user has supplied category of location information
	                infoFlag = TRUE;
			        
			        	
			        }
		        	
		        }
	        }
        if(KErrNotFound != index)
            {
            TLiwVariant variant =  smapparam->Value();
            if( variant.TypeId() != LIW::EVariantTypeDesC )
		        {
		        aOutParamList.AppendL( TLiwGenericParam( KErrorMessage,
                                       TLiwVariant( KGetLocationWrongInfoType ) ) );
                User::Leave( KErrArgument );
		        //Leave with error code	
		        }
            posInfoCategory.Set( variant.AsDes() );
            //Set infoFlag to indicate user has supplied category of location information
	        infoFlag = TRUE;
            }

        //if callback is given for this command then it will be a async request
        if( aCallback && ( KLiwOptASyncronous & aCmdOptions ) ) 
            {

           //Extract Update options from input List
        	
        	index = 0;
        	const TLiwGenericParam *smapparam = aInParamList.FindFirst(index , KUpdateOptionMap) ;
        	TPositionUpdateOptions *updateoptions = NULL ;
        	TPositionUpdateOptions updateOptionVal;
        	TUint category = EBasicInfo ;
        	//Check for possibility of position based parsing
        	if ( !smapparam )
	        {
	        TInt count = aInParamList.Count();
                if ( count >= 2 && posBasedFlag )	
		        {
		        smapparam = &aInParamList[Index1];
		        if (smapparam)
			        {
			        const CLiwMap  *updateOptionMap = (smapparam->Value() ).AsMap() ;
			        if( !updateOptionMap )
				        {
				        aOutParamList.AppendL( TLiwGenericParam( KErrorMessage,
                                               TLiwVariant( KGetLocationWrongupdateMap ) ) );
                        User::Leave( KErrArgument );
				        }
                	TInt error = SetUpdateOption(updateOptionVal,updateOptionMap);
                	if( KErrBadTime == error )
	                	{
	                	aOutParamList.AppendL( TLiwGenericParam( KErrorMessage,
                                               TLiwVariant( KGetLocationNegativeTime ) ) );
                        User::Leave( KErrArgument );
	                	
	                	}
                	updateoptions = &updateOptionVal ;
			        
			        	
			        }
		        	
		        }
	        }
        	
        	if(KErrNotFound != index)
        	    {
    	        const CLiwMap  *updateOptionMap = (smapparam->Value() ).AsMap() ;
    	        if( !updateOptionMap )
			        {
			        aOutParamList.AppendL( TLiwGenericParam( KErrorMessage,
                                           TLiwVariant( KGetLocationWrongupdateMap ) ) );
                    User::Leave( KErrArgument );
			        }
    	        
                TInt error = SetUpdateOption(updateOptionVal,updateOptionMap);
            	if( KErrBadTime == error )
                	{
                	aOutParamList.AppendL( TLiwGenericParam( KErrorMessage,
                                           TLiwVariant( KGetLocationNegativeTime ) ) );
                    
                    User::Leave( KErrArgument );
                	
                	}
                
                else if( KErrArgument == error )
	                {
	                aOutParamList.AppendL( TLiwGenericParam( KErrorMessage,
                                           TLiwVariant( KGetLocationBadUpdateOptions ) ) );
                    
                    
                    User::Leave( KErrArgument );
	                	
	                }

                	
                updateoptions = &updateOptionVal ;
        	    }
           

            if ( posInfoCategory == KLocationGenericInfo )
                {
                category = EGenericInfo ;
                }
            else if ( ( posInfoCategory != KLocationBasicinfo ) && ( infoFlag ) )
	            {
	            //this indicates a wrong supplied location info category by the user
	            aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
                                      TLiwVariant(KGetLocationCategoryInfo)));
                User::Leave(KErrArgument);	
	            }
            
            //Extract EnableHighAccuracy param 
            index = 0;
            const TLiwGenericParam* highaccparam = 
            aInParamList.FindFirst(index , KEnableHighAccuracy) ;
            TBool enableHighAcc = false;
            if ( KErrNotFound == index )
                {
                highaccparam = 0;
                TInt count = aInParamList.Count();
                if ( count >= 3 && posBasedFlag ) 
                    {
                    //Possiblity of Position based parsing
                    highaccparam = &aInParamList[Index2];
                    }
                }

            if( highaccparam )
                {
                if((highaccparam->Value().TypeId()) == EVariantTypeTBool)
                    enableHighAcc = highaccparam->Value().AsTBool();

                else
                    {
                    aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
                            TLiwVariant(KGetLocationBadEnableHighAcc) ) );

                    User::Leave(KErrArgument);
                    }
                }
            LocationInterfaceCB* callback =
            LocationInterfaceCB::NewL(aCallback,
                    &aInParamList, /*&iModuleInfo,*/ transid) ;

            CleanupStack :: PushL(callback) ;                   
            callback->SetRequestType(KGetLocationCB) ;
            
            iLocationService->GetLocationL(callback ,category,
                    NULL,updateoptions,enableHighAcc) ;	                    
            //Store the allocatioed address 
            iHandleCB.Append(callback);
            //Append Transcationid to out list
            aOutParamList.AppendL(TLiwGenericParam(KTransactionId, TLiwVariant(transid)));
            CleanupStack :: Pop(callback) ;

            }
            
        // Command is synchronous GetLocationCall    
        else  
            {
            TPosition pos ;

            //Extract Update options from input List

            index = 0;
            const TLiwGenericParam *smapparam = aInParamList.FindFirst(index , KUpdateOptionMap) ;
            TUint category = EBasicInfo ;
            TPositionUpdateOptions updateOptionVal;
            const TPositionUpdateOptions* updateOptions = NULL ;
            //if a smapparam is NULL there exist possibility of position based parsing
            if ( !smapparam )
	        {
	        TInt count = aInParamList.Count();
                if (count >= 2 && posBasedFlag)	
		        {
		        smapparam = &aInParamList[Index1];
		        if (smapparam)
			        {
			        const CLiwMap  *updateOptionMap = (smapparam->Value() ).AsMap() ;
			        if( !updateOptionMap )
				        {
				        aOutParamList.AppendL( TLiwGenericParam( KErrorMessage,
	                                           TLiwVariant( KGetLocationWrongupdateMap ) ) );
	                    
	                    User::Leave( KErrArgument );
				        }
                	TInt error = SetUpdateOption(updateOptionVal,updateOptionMap);
                	if( KErrBadTime == error )
	                	{
	                	aOutParamList.AppendL( TLiwGenericParam( KErrorMessage,
                                               TLiwVariant( KGetLocationNegativeTime ) ) );
                        
                        User::Leave( KErrArgument );
	                	
	                	}
	                else if( KErrArgument == error )
		                {
		                aOutParamList.AppendL( TLiwGenericParam( KErrorMessage,
	                                           TLiwVariant( KGetLocationBadUpdateOptions ) ) );
	                    
	                    User::Leave( KErrArgument );
		                	
		                }

                	
                	updateOptions = &updateOptionVal ;
			        
			        	
			        }
		        	
		        }
	        }


            if( KErrNotFound != index)
                {

                const CLiwMap  *updateOptionMap = (smapparam->Value()).AsMap() ;  
                if( !updateOptionMap )
			        {
			        aOutParamList.AppendL( TLiwGenericParam( KErrorMessage,
                                           TLiwVariant( KGetLocationWrongupdateMap ) ) );
                    
                    User::Leave( KErrArgument );
			        }
  
                TInt error = SetUpdateOption(updateOptionVal,updateOptionMap);
            	if( KErrBadTime == error )
                	{
                	aOutParamList.AppendL( TLiwGenericParam( KErrorMessage,
                                           TLiwVariant( KGetLocationNegativeTime ) ) );
                    
                    User::Leave( KErrArgument );
                	
                	}
                else if( KErrArgument == error )
	                {
	                aOutParamList.AppendL( TLiwGenericParam( KErrorMessage,
                                           TLiwVariant( KGetLocationBadUpdateOptions ) ) );
                    
                    User::Leave( KErrArgument );
	                	
	                }
                updateOptions = &updateOptionVal ;

                }

            if ( posInfoCategory == KLocationGenericInfo )
                {
                category = EGenericInfo ;
                }
            else if( posInfoCategory != KLocationBasicinfo   )
	            {
	            //this indicates a wrong supplied location info category by the user
	            aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
                                      TLiwVariant(KGetLocationCategoryInfo)));
                User::Leave(KErrArgument);	
	            } 
            //Extract Enable High accuracy param 
            index = 0;
            const TLiwGenericParam* highaccparam = 
            aInParamList.FindFirst(index ,
                    KEnableHighAccuracy) ;
            TBool enableHighAcc = false;

            if ( KErrNotFound == index )
                {
                highaccparam = 0;
                TInt count = aInParamList.Count();
                if (count >= 3 && posBasedFlag) 
                    {
                    //Position based parsing to be done
                    highaccparam = &aInParamList[Index2];
                    }
                }

            if( highaccparam )
                {
                if((highaccparam->Value().TypeId()) == EVariantTypeTBool)
                    enableHighAcc = highaccparam->Value().AsTBool();

                else
                    {
                    aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
                            TLiwVariant(KGetLocationBadEnableHighAcc) ) );                                       
                    User::Leave(KErrArgument);
                    }
                }

            iLocationService->GetLocationL(iGenericPosition,
                    updateOptions,enableHighAcc) ;
            GetLocationInfo(aOutParamList,category) ; 
            
            								                        

            } //End of Synchronous getlocationcall
        	
            
       	    
        } //End of KCmdGetLocation

    else if(  ( !(aCmdName.CompareF( KCmdTraceLocation )) ) && ( aCallback ) && ( KLiwOptASyncronous & aCmdOptions ) )	//Trace request is made by consumer
        {

        TInt ret = KErrNone ;
        TInt32 transid  = aCallback->GetTransactionID() ;
        TInt index = 0;
        TPtrC posInfoCategory(KLocationBasicinfo);
        
        
      
        const TLiwGenericParam *smapparam = aInParamList.FindFirst(index , KLocationInfoCategory) ;
        
        //if smapparam is NULL still there exist possibility of position based parsing
        if ( !smapparam )
	        {
	        TInt count = aInParamList.Count();
	        if (count >= 1)	
		        {
		        smapparam = &aInParamList[Index0];
		        if (smapparam && ( smapparam->Name() == KNullDesC8 )  )
			        {
			        TLiwVariant variant =  smapparam->Value();
			        if( variant.TypeId() != LIW::EVariantTypeDesC )
				        {
				        aOutParamList.AppendL( TLiwGenericParam( KErrorMessage,
                                               TLiwVariant( KTraceWrongInfoType ) ) );
                        User::Leave( KErrArgument );
				        //Leave with error code	
				        }
	                posInfoCategory.Set( variant.AsDes() );
			        
			        	
                    posBasedFlag = ETrue;
			        }
		        	
		        }
	        }
        
        if(KErrNotFound != index)
            {
            //Extract location category information if specified by user
            TLiwVariant variant =  smapparam->Value();
	        if( variant.TypeId() != LIW::EVariantTypeDesC )
		        {
		        aOutParamList.AppendL( TLiwGenericParam( KErrorMessage,
                                       TLiwVariant( KTraceWrongInfoType ) ) );
                User::Leave( KErrArgument );
		        //Leave with error code	
		        }
            posInfoCategory.Set( variant.AsDes() );
			        
            
            }
        

        

        
        	//Default posinfo Category is basic info
        	TUint catergory = EBasicInfo ;
        	TPositionUpdateOptions updateOptionVal;
        	TPositionUpdateOptions* updateOption = NULL ;
        	
        	index = 0;
        	smapparam = aInParamList.FindFirst(index , KUpdateOptionMap) ;
        	//if a smapparam is NULL there exist possibility of position based parsing
            if ( !smapparam )
	        {
	        TInt count = aInParamList.Count();
            if (count >= 2 && posBasedFlag)	
		        {
		        smapparam = &aInParamList[Index1];
		        if (smapparam)
			        {
			        const CLiwMap  *updateOptionMap = (smapparam->Value() ).AsMap() ;
		        if( !updateOptionMap )
			        {
			        aOutParamList.AppendL( TLiwGenericParam( KErrorMessage,
                                           TLiwVariant( KTraceWrongupdateMap ) ) );
                    
                    User::Leave( KErrArgument );
			        }

            	TInt error = SetUpdateOption(updateOptionVal,updateOptionMap);
            	if( KErrBadTime == error )
                	{
                	aOutParamList.AppendL( TLiwGenericParam( KErrorMessage,
                                           TLiwVariant( KTraceNegativeTime ) ) );
                    User::Leave( KErrArgument );
                	
                	}
                else if( KErrArgument == error )
	                {
	                aOutParamList.AppendL( TLiwGenericParam( KErrorMessage,
                                           TLiwVariant( KTraceBadUpdateOptions ) ) );
                    
                    
                    
                    User::Leave( KErrArgument );
	                	
	                }
                	updateOption = &updateOptionVal ;
			        
			        	
			        }
		        	
		        }
	        }
        	
        
        	//Extract Update options from input List
        	if(KErrNotFound != index)
        	    { 
        	    const CLiwMap  *updateOptionMap = (smapparam->Value()).AsMap() ; 
	    	    if( !updateOptionMap )
			        {
			        aOutParamList.AppendL( TLiwGenericParam( KErrorMessage,
	                                       TLiwVariant( KGetLocationWrongupdateMap ) ) );
	                
	                User::Leave( KErrArgument );
			        }

	    	    TInt error = SetUpdateOption(updateOptionVal,updateOptionMap);
	        	if( KErrBadTime == error )
	            	{
	            	aOutParamList.AppendL( TLiwGenericParam( KErrorMessage,
	                                       TLiwVariant( KTraceNegativeTime ) ) );
	                User::Leave( KErrArgument );
	            	
	            	}
	             else if( KErrArgument == error )
	                {
	                aOutParamList.AppendL( TLiwGenericParam( KErrorMessage,
                                           TLiwVariant( KTraceBadUpdateOptions ) ) );
                    
                    User::Leave( KErrArgument );
	                	
	                }
                
	        	 updateOption = &updateOptionVal ;
	        	 }
        	    
         	
		    //Now set the category of info required before sending request to core dll
		    
		    if ( posInfoCategory == KLocationGenericInfo )
                {
                catergory = EGenericInfo ;
                }
            else if( posInfoCategory != KLocationBasicinfo   )
	            {
	            //this indicates a wrong supplied location info category by the user
	            aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
                                      TLiwVariant(KTraceCategoryInfo)));
				
	            User::Leave(KErrArgument);	
	            }
        //Extract Enable High accuracy param 
        index = 0;
        const TLiwGenericParam* highaccparam = aInParamList.FindFirst(index ,
                KEnableHighAccuracy) ;
        TBool enableHighAcc = false;
        if ( KErrNotFound == index )
            {
            highaccparam = 0;
            TInt count = aInParamList.Count();
            if (count >= 3 && posBasedFlag) 
                {
                //Possibility of Position based parsing
                highaccparam = &aInParamList[Index2];
                }
            }

        if( highaccparam )
            {
            if((highaccparam->Value().TypeId()) == EVariantTypeTBool)
                enableHighAcc = highaccparam->Value().AsTBool(); 

            else
                {
                aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
                        TLiwVariant(KGetLocationBadEnableHighAcc) ) );

                User::Leave(KErrArgument);
                }
            }       

        LocationInterfaceCB* callback =
        LocationInterfaceCB::NewL(aCallback,
                &aOutParamList,/* &iModuleInfo,*/ transid) ;
        CleanupStack :: PushL(callback) ;
        callback->SetRequestType(KTraceCB) ;


        iLocationService->TraceL( callback, catergory,NULL, 
                updateOption,enableHighAcc );
        iHandleCB.Append(callback);
        aOutParamList.AppendL(TLiwGenericParam(KTransactionId,
                TLiwVariant(transid))) ; //Append Transcationid to out list

        CleanupStack :: Pop(callback) ;
        
        } //End of KCmdTraceLocation

    else if(!( aCmdName.CompareF( KCmdCancelRequest ) ) )	  //Cancel request is made by consumer 
        {

         TInt index = 0 ;
         TInt count = aInParamList.Count();
         
         const TLiwGenericParam *genericParam = aInParamList.FindFirst(index , KCancelType) ;
         
         if(!genericParam)
            {
            //still exist possibility of position based parsing
            
            if ( count == 1 )
	            {
	            genericParam = &aInParamList[Index0];
	            }
            
            }
         
         	//Now genericParam must contain the Canceltype argument
			if (!genericParam)
	    	{
	  			  aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
	          TLiwVariant(KCancelMissingType)));
	    
	    			User::Leave(SErrMissingArgument);	
	    	}

         
        TLiwVariant variant =  genericParam->Value();
        if( variant.TypeId() != LIW::EVariantTypeDesC )
	        {
	        aOutParamList.AppendL( TLiwGenericParam( KErrorMessage,
                                   TLiwVariant( KCancelTypeMisMatch ) ) );
            User::Leave( KErrArgument );
	        //Leave with error code	
	        }
        TPtrC requesttype =  variant.AsDes() ;    
        TInt ret = KErrGeneral  ;	

        if(requesttype == KRequestTrace )
            {
            	
            ret = iLocationService->CancelOnGoingService(ECancelTrace) ;
            
            if (KErrNone == ret)
                {
                TInt ncal = iHandleCB.Count() ;

                for (TInt iter = 0; iter < ncal; ++iter)
                    {
                    if (iHandleCB[iter])
                        {                           
                        if(iHandleCB[iter]->GetRequestType() == KTraceCB)
                            {
                            delete iHandleCB[iter];
                            iHandleCB[iter] = NULL;
                            break;
                            }
                        }
                    }

                }
            }
        else if(requesttype == KRequestGetLoc )
            {
            		
            ret = iLocationService->CancelOnGoingService(ECancelGetLocation) ;
            
            if(!ret) 
                {
                TInt ncal1 = iHandleCB.Count() ;

                for (TInt iter = 0; iter < ncal1; ++iter)
                    {

                    if (iHandleCB[iter])
                        {

                        if(iHandleCB[iter]->GetRequestType() == KGetLocationCB)
                            {
                            delete iHandleCB[iter];
                            iHandleCB[iter] = NULL;
                            break;
                            }
                        }
                    }
                }
            
            }

        else        //Invalid command 
            {
            aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
                                      TLiwVariant(KCancelWrongType)));
            
            User::Leave(KErrArgument);
            }

    
        User::LeaveIfError(ret);

        } //End of KCmdCancelRequest 

    else if(( !aCmdName.CompareF(KRequestCalculate) ) )
        {
        TInt index = 0 ;
        //Flag set to 0 indicate no position based parsing need to be done
        // for subsequent parameters
        TInt paramparsingFlag = 0;
        const TLiwGenericParam *genericParam = aInParamList.FindFirst(index ,KMathRequest) ;

        if(!genericParam)
            {
            
            genericParam = &aInParamList[Index0];
            paramparsingFlag  = 1;
            if( !genericParam )
	            {
	            aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
                                      TLiwVariant(KMissingMathrequest)));
	            User::Leave(KErrArgument);	
	            }
	        
            
            } 

        TLiwVariant variant =  genericParam->Value();
        if( variant.TypeId() != EVariantTypeDesC )
	        {
	        aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
                                      TLiwVariant(KWrongMathrequest)));
	        User::Leave(KErrArgument);
	        	
	        }
        TPtrC requesttype =  variant.AsDes() ;
        TInt ret  ;	

        
	    if( requesttype == KRequestDistance )
	    	{
			TInt mathindex = 0 ;

			// calculation							  						
			const TLiwGenericParam *smapparam = aInParamList.FindFirst(mathindex , KDistanceParmSource) ;		
			//if smapparam is NULL still exist possibility of position based parsing
			if ( (!smapparam) && (paramparsingFlag) )
				{
				smapparam = &aInParamList[Index1];
				}
			

			mathindex = 0 ;
			const TLiwGenericParam *dmapparam = aInParamList.FindFirst(mathindex , KDistanceParmDestination) ;
			if ( (!dmapparam) && (paramparsingFlag) )
				{
				dmapparam = &aInParamList[Index2];
				}						  							
			if(!smapparam || !dmapparam)
				{
				aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
                                      TLiwVariant(KMissingParamCord)));
            	User::Leave(KErrArgument);
				}				  							

			TLiwVariant mapVariant= smapparam->Value() ; 
			const CLiwMap  *map = mapVariant.AsMap() ;
			if( !map )
		        {
		        aOutParamList.AppendL( TLiwGenericParam( KErrorMessage,
                                       TLiwVariant( KCalWrongSource ) ) );
                
                
                User::Leave( KErrArgument );
		        }
			TCoordinate source , destination ;

			FillCoordinatesL(source , map) ;  //Extract source coordinates 

			mapVariant = dmapparam->Value() ;
			map = mapVariant.AsMap() ;
			if( !map )
		        {
		        aOutParamList.AppendL( TLiwGenericParam( KErrorMessage,
                                       TLiwVariant( KCalWrongDest ) ) );
                
                
                User::Leave( KErrArgument );
		        }

			FillCoordinatesL(destination , map) ;

			inpparam distance ;

			 distance.source = source ;
			 distance.destination = destination ;
			 distance.servicechoice =  EDistance ;
			 
			 
			 ret = iLocationService->MathOperation(distance) ; //Calculate distance using core  class
			 

			//success/failure code to the outputlist
			//TLiwGenericParam errorParm(KErrorCode , TLiwVariant((TInt32)ret)) ;
			//aOutParamList.AppendL(errorParm) ;
			User::LeaveIfError(ret);
			TReal32 resultvalue = distance.result;

			if ( KErrNone == ret )
				{
				TLiwGenericParam opresult(KMathOpResult,TLiwVariant((TReal)resultvalue));
				aOutParamList.AppendL(opresult) ;
				}
		    
			} //End of KRequestDistance
		
		else if ( requesttype == KRequestBearingTo)
			{
			TInt mathindex = 0 ;

			// calculation							  						
			const TLiwGenericParam *smapparam = aInParamList.FindFirst(mathindex , KDistanceParmSource) ;		
			//if smapparam is NULL still exist possibility of position based parsing
			if ( (!smapparam) && (paramparsingFlag) )
				{
				smapparam = &aInParamList[Index1];
				}

			mathindex = 0 ;
			const TLiwGenericParam *dmapparam = aInParamList.FindFirst(mathindex , KDistanceParmDestination) ;
			if ( (!dmapparam) && (paramparsingFlag) )
				{
				dmapparam = &aInParamList[Index2];
				}
									  							
			if(!smapparam || !dmapparam)
				{
				aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
                                      TLiwVariant(KMissingParamCord)));
            	User::Leave(KErrArgument);
				}				  							

			TLiwVariant mapVariant= smapparam->Value() ; 
			const CLiwMap  *map = mapVariant.AsMap() ;
			if( !map )
		        {
		        aOutParamList.AppendL( TLiwGenericParam( KErrorMessage,
                                       TLiwVariant( KCalWrongSource ) ) );
                
                
                User::Leave( KErrArgument );
		        }
			TCoordinate source , destination ;

			FillCoordinatesL(source , map) ;  //Extract source coordinates 

			mapVariant = dmapparam->Value() ;
			map = mapVariant.AsMap() ;
			if( !map )
		        {
		        aOutParamList.AppendL( TLiwGenericParam( KErrorMessage,
                                       TLiwVariant( KCalWrongDest ) ) );
                
                
                User::Leave( KErrArgument );
		        }

			FillCoordinatesL(destination , map) ;

			inpparam bearingTo ;

			bearingTo.source = source ;
			bearingTo.destination = destination ;
			bearingTo.servicechoice =  EBearingTo ;
			 
			ret = iLocationService->MathOperation(bearingTo) ; 
			 

			
			User::LeaveIfError(ret);
			TReal32 resultvalue = bearingTo.result;

			if ( KErrNone == ret )
				{
				TLiwGenericParam opresult(KMathOpResult,TLiwVariant((TReal)resultvalue));
				aOutParamList.AppendL(opresult) ;
				}   
			} //End of KRequestBearingto
		else if ( requesttype == KRequestMove )
			{
			TInt mathindex = 0;
			
			// Extracting source coordinate from input parameter List							  						
			const TLiwGenericParam *smapparam = aInParamList.FindFirst(mathindex , KDistanceParmSource) ;		
			if ( (!smapparam) && (paramparsingFlag) )
				{
				smapparam = &aInParamList[Index1];
				}
			
			
									  							
			if( !smapparam )
				{
				aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
                                      TLiwVariant(KMissingParamCord)));
            	User::Leave( SErrMissingArgument );
				}				  							

			TLiwVariant mapVariant= smapparam->Value() ; 
			const CLiwMap  *map = mapVariant.AsMap() ;
			if( !map )
		        {
		        aOutParamList.AppendL( TLiwGenericParam( KErrorMessage,
                                       TLiwVariant( KCalWrongSource ) ) );
                
                
                User::Leave( KErrArgument );
		        }
			TCoordinate source  ;

			FillCoordinatesL(source , map) ;  
			
			mathindex = 0; 
			//Extracting distance by which coordinate should be moved
			const TLiwGenericParam *distanceParam = aInParamList.FindFirst(mathindex,KDistanceMove) ;
			if ( (!distanceParam) &&  (paramparsingFlag) )
			{
				distanceParam = &aInParamList[Index2];
				if ( !distanceParam )
					{
					aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
                                      TLiwVariant(KMissingDistanceParam)));
					User::Leave( SErrMissingArgument );	
					}
			}
			if( !distanceParam )
				{
				aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
                                  TLiwVariant(KMissingDistanceParam)));
				User::Leave( SErrMissingArgument );	
				}
			TLiwVariant distanceVariant = distanceParam->Value();
			if( ( distanceVariant.TypeId() != EVariantTypeTReal ) )
				{
				if ( ( distanceVariant.TypeId() != EVariantTypeTInt32 ) )
					{
					aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
                                      TLiwVariant(KCaluclateMoveDistance)));
				    User::Leave(KErrArgument);	
					}
				
				}
			
			const TReal64 distanceValue = distanceVariant.AsTReal();	
			

			//Extracting bearing by which coordinate should be moved
			mathindex = 0;
			
			const TLiwGenericParam *bearingParam = aInParamList.FindFirst(mathindex,KBearingMove);
			if ( (!bearingParam) && (paramparsingFlag) )
				{
				bearingParam = &aInParamList[Index3];
				if ( !bearingParam )
					{
					aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
                                      TLiwVariant(KMissingBearingParam)));
					User::Leave( SErrMissingArgument );	
					}
				}
			
			if( !bearingParam )
				{
				aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
                                      TLiwVariant(KMissingBearingParam)));
				User::Leave( SErrMissingArgument );
					
				}
			TLiwVariant bearingVariant = bearingParam->Value();
			if( ( bearingVariant.TypeId() != EVariantTypeTReal ) )
				{
				if ( ( bearingVariant.TypeId() != EVariantTypeTInt32 ) )
					{
					aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
                                      TLiwVariant(KCaluclateMoveBearing)));
				    User::Leave(KErrArgument);	
					}
				
				}
				
			const TReal32 bearingValue = bearingVariant.AsTReal();
			
			

			

			inpparam moveParam ;

			moveParam.source = source ;
			 
			 
			moveParam.servicechoice =  EMove ;
			 
			moveParam.bearing = bearingValue;
			moveParam.distance = distanceValue;
			 
			//Move Coordinates	
			ret = iLocationService->MathOperation(moveParam) ; 
			 
			if ( KErrNone == ret )
				{
				TReal64 inputParamLongitude = moveParam.source.Longitude();
				TReal64 inputParamLatitude = moveParam.source.Latitude();
				TReal64 inputParamAltitude = moveParam.source.Altitude();
				 
				 //Appending translated coordinate to outputParamList
				CLiwDefaultMap *result = CLiwDefaultMap::NewL() ;
				CleanupStack :: PushL(result) ;
		
                //Inserting longitude, Latitude and altitude 
				result->InsertL(KLongitudeKey , TLiwVariant((TReal)inputParamLongitude )) ; 
            	result->InsertL(KLatitudeKey , TLiwVariant((TReal)inputParamLatitude)) ;  
            	result->InsertL(KAltitudeKey , TLiwVariant((TReal)inputParamAltitude))   ;  
	    		TLiwVariant resVar(result) ;

				TLiwGenericParam outParm(KLocationMap , TLiwVariant(result)) ;
	   
				aOutParamList.AppendL(outParm) ;
				result->DecRef();
				 
				 
				 

				//success/failure code to the outputlist
				TLiwGenericParam errorParm(KErrorCode , TLiwVariant((TInt32)ret)) ;
				aOutParamList.AppendL(errorParm) ;
				CleanupStack :: Pop(result) ;
			
				 }//End of Move
			else
				{
				/*TLiwGenericParam errorParm(KErrorCode , TLiwVariant((TInt32)ret)) ;
				aOutParamList.AppendL(errorParm) ;*/
				User::LeaveIfError(ret);
				
				}
            
        	} 


        else
            {
            aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
                                      TLiwVariant(KWrongMathrequest)));
            User::Leave(KErrArgument);
            }

        }
    else//bad command
        {
        aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
                                              TLiwVariant(KCmdNotFound)));
        User::Leave(KErrNotSupported);
        
        }
            
	    
        
    }

/**
 * CLocationInterface :: SetSupportedFields fills iGenericPosInfo  as per the capability of the 
 * positioning module used
 */ 


/**
 * CLocationInterface :: GetLocationInfo an internal utility funtionin, gets all the location information 
 * which is supported by  this Module
 */
 
 
void CLocationInterface :: GetLocationInfo( CLiwGenericParamList& aOutParamList,TInt aPosInfoCategory)
    {
    TPosition pos ;
    iGenericPosition->GetPosition(pos) ; //Now populate outparam list with latitude, longitude and altitude data

    CLiwDefaultMap *Result = CLiwDefaultMap::NewL() ; 
    
    CleanupStack :: PushL(Result) ;
    TReal64 Val = pos.Longitude() ;

    //Inserting latitude , longitude ,  altitude .
    Result->InsertL(KLongitudeKey , TLiwVariant((TReal)Val)) ; 

    Val = pos.Latitude() ;
    Result->InsertL(KLatitudeKey , TLiwVariant((TReal)Val)) ; 
            
    TReal32 altitude = pos.Altitude() ;
            
    if (!(Math::IsNaN(altitude)))
        {
    Result->InsertL(KAltitudeKey , TLiwVariant((TReal)altitude)) ; 
        }

    TReal32 Val1;
    Val1 = pos.HorizontalAccuracy();
    if (!(Math::IsNaN(Val1)))
        {
        Result->InsertL(KHorAccuracy, TLiwVariant((TReal)Val1)) ;
        }

    Val1 = pos.VerticalAccuracy();
    if (!(Math::IsNaN(Val1)))
        {
        Result->InsertL(KVerAccuracy, TLiwVariant((TReal)Val1)) ;
        }
    TLiwVariant MapVariant(Result) ;
     
   
     //TPositionModuleInfo :: TCapabilities  currCapability  = iModuleInfo.Capabilities() ;

	 if ( aPosInfoCategory == EGenericPositionInfo )
	     {
	     
		    TReal32 speedinfo = 0 ;

        if(!iGenericPosition->GetValue(EPositionFieldHorizontalSpeed , speedinfo))  //Extract speed 
		    	{
		    	 Result->InsertL(KPositionFieldHorizontalSpeed ,TLiwVariant((TReal) speedinfo)) ;
		    	}



        if(!iGenericPosition->GetValue(EPositionFieldHorizontalSpeedError , speedinfo) )
		        {
		        Result->InsertL(KPositionFieldHorizontalSpeedError ,TLiwVariant((TReal) speedinfo)) ;
		        }

		    /*if(!iGenericPosInfo->GetValue(EPositionFieldVerticalSpeed , speedinfo))
		        {
		        Result->InsertL(KPositionFieldVerticalSpeed ,TLiwVariant((TReal) speedinfo)) ;

		        }

		    if(!iGenericPosInfo->GetValue(EPositionFieldVerticalSpeedError ,speedinfo))
		        {
		        Result->InsertL(KPositionFieldVerticalSpeedError ,TLiwVariant((TReal) speedinfo)) ;
		        }*/




        TInt8 satinfo  = 0;

        if(!iGenericPosition->GetValue(EPositionFieldSatelliteNumInView , satinfo))
            {
            Result->InsertL(KPositionFieldSatelliteNumInView ,TLiwVariant((TReal) satinfo)) ;
            }
        if(!iGenericPosition->GetValue(EPositionFieldSatelliteNumUsed , satinfo))
            {
            Result->InsertL(KPositionFieldSatelliteNumUsed ,TLiwVariant((TReal) satinfo)) ;
            }
		   

		 
		 TReal32 direcinfo = 0;


		 if(!iGenericPosition->GetValue(EPositionFieldTrueCourse , direcinfo) )
		   {
		   Result->InsertL(KPositionFieldTrueCourse ,TLiwVariant((TReal) direcinfo)) ;
		   }


		 if(!iGenericPosition->GetValue(EPositionFieldTrueCourseError , direcinfo) )
		   {
		   Result->InsertL(KPositionFieldTrueCourseError ,TLiwVariant((TReal) direcinfo)) ;
		   }


		 if(!iGenericPosition->GetValue(EPositionFieldMagneticCourseError , direcinfo) )
		    {
		    Result->InsertL(KPositionFieldMagneticCourseError ,TLiwVariant((TReal) direcinfo)) ;
		    }


		 if(!iGenericPosition->GetValue(EPositionFieldMagneticCourse , direcinfo) )
		    {
		    Result->InsertL(KPositionFieldMagneticCourse ,TLiwVariant((TReal) direcinfo)) ;
		    }
		


		
        TReal32 compassinfo ;

        
        if(!iGenericPosition->GetValue(EPositionFieldHeading , compassinfo) )
            {
            Result->InsertL(KPositionFieldHeading ,TLiwVariant((TReal) compassinfo)) ;	
            }


        if(!iGenericPosition->GetValue(EPositionFieldHeadingError , compassinfo) )
            {
            Result->InsertL(KPositionFieldHeadingError ,TLiwVariant((TReal) compassinfo)) ;
            }


        if(!iGenericPosition->GetValue(EPositionFieldMagneticHeading , compassinfo) )
            {
            Result->InsertL(KPositionFieldMagneticHeading ,TLiwVariant((TReal) compassinfo)) ;
            }



        if(!iGenericPosition->GetValue(EPositionFieldMagneticHeadingError , compassinfo) )
            {
            Result->InsertL(KPositionFieldMagneticHeadingError ,TLiwVariant((TReal) compassinfo)) ;

            } 
		        }


    aOutParamList.AppendL(TLiwGenericParam ( KLocationMap, TLiwVariant(Result))) ;
    Result->DecRef();
    CleanupStack :: Pop(Result) ;
    		
    }


 

/**
 * Function : ExecuteCmdL , called directly by consumer, parses the input parameters and 
 * then calls appropriate method on iLocationService object
 */
 
 
void CLocationInterface :: ExecuteCmdL( const TDesC8& aCmdName,
                              const CLiwGenericParamList& aInParamList ,
                              CLiwGenericParamList& aOutParamList,
                              TUint aCmdOptions,
                          MLiwNotifyCallback* aCallback )
    {

    TRAPD(error , CmdExecuteL(aCmdName , aInParamList , aOutParamList , aCmdOptions , aCallback)) ;

	
	TInt sapierror = ConvertToSapiError(error);
	aOutParamList.AppendL(TLiwGenericParam(KErrorCode , TLiwVariant((TInt32)sapierror))) ;	
	


    }


 

/**
 * Internal function which is used to extract the coordinates from CLiwMap passed by consumer
 */ 

void CLocationInterface :: FillCoordinatesL ( TCoordinate& aCoordinate , const CLiwMap* aMap )
    {
    TLiwVariant longitudevar ;
    TLiwVariant latitudevar ;
    TLiwVariant altitudevar ;
    
    

    if( !aMap->FindL(KLongitudeKey , longitudevar) ) 
    	User::Leave( SErrMissingArgument );
    
    if( !aMap->FindL(KLatitudeKey ,  latitudevar) ) 
    	User::Leave( SErrMissingArgument );
    
    
    if( !aMap->FindL(KAltitudeKey , altitudevar ) )	
    	User::Leave( SErrMissingArgument );
    
    
    TReal64 latitude = 0,longitude = 0,altitude = 0;
	if ( ( latitudevar.TypeId() == EVariantTypeTReal ) || ( latitudevar.TypeId() == EVariantTypeTInt32 )  )
		{
		latitude = (TReal64)latitudevar.AsTReal() ; 	
		}
	else
		User::Leave( KErrArgument );
    
    if ( ( longitudevar.TypeId() == EVariantTypeTReal ) || ( longitudevar.TypeId() == EVariantTypeTInt32 )  )
		{
		longitude = (TReal64)longitudevar.AsTReal() ;
		}
	else
		User::Leave( KErrArgument );
    
    if ( ( altitudevar.TypeId() == EVariantTypeTReal ) || ( altitudevar.TypeId() == EVariantTypeTInt32 )  )
		{
		altitude = (TReal64)altitudevar.AsTReal() ;
		}
	else
		User::Leave( KErrArgument );
    
    
    

    aCoordinate.SetCoordinate( latitude , longitude , altitude) ;


    }
    
/**
 * CLocationInterface ::SetUpdateOption extracts updates options from input CLiwMap into TpositonUpdatedOptions
 * This is an internal utility function
 */   
 TInt CLocationInterface ::SetUpdateOption(TPositionUpdateOptions& aPositionUpdateoption,const CLiwMap* aUpdatemap)
	 {
	
	 TLiwVariant options ;
	 
	 
	 
	 //Extrace Update interval
	 if(aUpdatemap->FindL(KUpdateOptionInterval,options))
	    {
	    if( ( options.TypeId() == LIW::EVariantTypeTInt32 ) || ( options.TypeId() == LIW::EVariantTypeTReal ) )
		    {
		    TInt interval = options.AsTInt32();
		    if( interval < 0 )
			     {
			     return KErrBadTime;	
			     }
		    aPositionUpdateoption.SetUpdateInterval(TTimeIntervalMicroSeconds(interval));
		    }
		else
			{
			return KErrArgument;

			}
	     
	    }
	 else//set the default value
		 {
		 aPositionUpdateoption.SetUpdateInterval(TTimeIntervalMicroSeconds(KLocUpdateInterval));
		 	
		 }
	    
	 //Update time out    
	 if(aUpdatemap->FindL(KUpdateOptionTimeOut,options))
	    {
	    if( ( options.TypeId() == LIW::EVariantTypeTInt32 ) || ( options.TypeId() == LIW::EVariantTypeTReal ) )
		    {
		    TInt timeOut = options.AsTInt32();
	     	if( timeOut < 0 )
			    {
			    return KErrBadTime;	
			    }
	     	aPositionUpdateoption.SetUpdateTimeOut(TTimeIntervalMicroSeconds(timeOut));
		    }
		else
			{
			return KErrArgument;	
			}
	     
	    }
	 else//set the default value
		 {
		 aPositionUpdateoption.SetUpdateTimeOut(TTimeIntervalMicroSeconds(KLocUpdateTimeOut));
		 	
		 }
	    
	 //Update maxage specifies    
	 if(aUpdatemap->FindL(KUpdateOptionMaxAge,options))  
        {
        if( ( options.TypeId() == LIW::EVariantTypeTInt32 ) || ( options.TypeId() == LIW::EVariantTypeTReal ) )
		    {
		    TInt maxAge = options.AsTInt32();
	        if( maxAge < 0 )
			     {
			     return KErrBadTime;	
			     }
	        
	        aPositionUpdateoption.SetMaxUpdateAge(TTimeIntervalMicroSeconds(maxAge)); 
		    }
		else
			{
			return KErrArgument;	
			}
        
        }
     else//set the default value
	     {
	     aPositionUpdateoption.SetMaxUpdateAge(TTimeIntervalMicroSeconds(KLocMaxAge)); 
	     	
	     }
	 //Partial Updates
	if(aUpdatemap->FindL(KPartialUpdates , options )) 
	    {
	    if( options.TypeId() != LIW::EVariantTypeTBool )
		    {
		    return KErrArgument;	
		    }
	    
	     TBool partialUpdates =  options.AsTBool() ;
         aPositionUpdateoption.SetAcceptPartialUpdates(partialUpdates) ;  
	    }
	else//set the default value 
		{
		aPositionUpdateoption.SetAcceptPartialUpdates(FALSE) ;
		
			
		}
	    
	return KErrNone;
	 
	 }

