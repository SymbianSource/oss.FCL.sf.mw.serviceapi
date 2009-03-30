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

/**
 * KMAXACTIVEOBJ identifies maximum number of entries in callback registration table
 * presently it stores only two entries .
 */
const TInt KMAXACTIVEOBJ = 2;


//Error code for bad time
const TInt KErrBadTime = -125;

/**
 * destructor
 */



CLocationInterface :: ~CLocationInterface()
    {
 	 
 	 delete iLocationService ;
 	  	 
 	 
 	 iLocationService = NULL ;
 	 
 	 for(TInt iter = 0 ; iter < iHandleCB.Count() ; ++iter)
 	 	{
 	 	 delete iHandleCB[iter] ;
 	 	}
 	 iHandleCB.Close();
	 delete iGenericPosInfo ;
 
 	
    }

/**
 * Default constructor
 */
 
 CLocationInterface :: CLocationInterface()
    {
 	iGenericPosInfo = HPositionGenericInfo :: NewL() ; 
 	
 	if(!iGenericPosInfo)
 	    {
 		User ::Leave(KErrNoMemory) ;
 	    }
 	
 	
 	for ( TInt count = 0;count < KMAXACTIVEOBJ ; count++)
    	{
		iHandleCB.Insert(NULL,count);
	    }
	
 	
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
          MLiwNotifyCallback* callBack = RequestCancel(transid) ;
          
          if (!callBack)
	          {
	          aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,
                                      TLiwVariant(KCancelInvalidTransactionId)));
              User::Leave(KErrNotFound);	
	          }
          
          
          
          //Send notification about the cancelled state to consumer
          callBack->HandleNotifyL(transid  , KLiwEventCanceled , 
                                    aOutParamList,   aInParamList) ;
            
          

        }

    
    //GetLocation request is made by consumer
    else if(aCmdName == KCmdGetLocation)                         
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
            LocationInterfaceCB  *callback = LocationInterfaceCB :: NewL (aCallback ,  &aInParamList , 
            														      &iModuleInfo , transid) ;
            CleanupStack :: PushL(callback) ;														      
            
            callback->SetRequestType(KGetLocationCB) ;

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
	        if (count == 2)	
		        {
		        smapparam = &aInParamList[Index1];
		        if (smapparam)
			        {
			        const CLiwMap  *updateOptionMap = (smapparam->Value() ).AsMap() ;
			        if( !updateOptionMap )
				        {
				        aOutParamList.AppendL( TLiwGenericParam( KErrorMessage,
                                               TLiwVariant( KGetLocationWrongupdateMap ) ) );
                        CleanupStack :: Pop( callback ) ;
                        delete callback;
                        User::Leave( KErrArgument );
				        }
                	TInt error = SetUpdateOption(updateOptionVal,updateOptionMap);
                	if( KErrBadTime == error )
	                	{
	                	aOutParamList.AppendL( TLiwGenericParam( KErrorMessage,
                                               TLiwVariant( KGetLocationNegativeTime ) ) );
                        CleanupStack :: Pop( callback ) ;
                        delete callback;
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
                    CleanupStack :: Pop( callback ) ;
                    delete callback;
                    User::Leave( KErrArgument );
			        }
    	        
                TInt error = SetUpdateOption(updateOptionVal,updateOptionMap);
            	if( KErrBadTime == error )
                	{
                	aOutParamList.AppendL( TLiwGenericParam( KErrorMessage,
                                           TLiwVariant( KGetLocationNegativeTime ) ) );
                    CleanupStack :: Pop( callback ) ;
                    delete callback;
                    
                    User::Leave( KErrArgument );
                	
                	}
                
                else if( KErrArgument == error )
	                {
	                aOutParamList.AppendL( TLiwGenericParam( KErrorMessage,
                                           TLiwVariant( KGetLocationBadUpdateOptions ) ) );
                    
                    CleanupStack :: Pop( callback ) ;
                    delete callback;
                    
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
                CleanupStack :: Pop( callback ) ;
                delete callback;
                User::Leave(KErrArgument);	
	            }
            
            //Extraction of update options and information complete so now send the request 
            //To core dll    

            ret = iLocationService->GetLocationL(callback ,category,iFieldList,updateoptions) ;	
         
            //aOutParamList.AppendL(TLiwGenericParam(KErrorCode , TLiwVariant((TInt32)ret))) ;
            
            if(KErrNone != ret)
                {
                    CleanupStack :: Pop(callback) ;
                    delete callback ;
                    User::Leave(ret);
                    
                }
                
            //Store the allocatioed address 
            iHandleCB[KGetLocationCB] = callback ; 
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
	        if (count == 2)	
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

            ret = iLocationService->GetLocationL(iGenericPosInfo,updateOptions) ; 
            //aOutParamList.AppendL(TLiwGenericParam (KErrorCode , TLiwVariant((TInt32)ret))) ;
            
            if(KErrNone != ret)
                {
                User::Leave(ret);
                 
                }
            GetLocationInfo(aOutParamList,category) ; 
            
            								                        

            } //End of Synchronous getlocationcall
        	
            
       	    
        } //End of KCmdGetLocation

    else if(  ( aCmdName == KCmdTraceLocation ) && ( aCallback ) && ( KLiwOptASyncronous & aCmdOptions ) )	//Trace request is made by consumer
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
        

        LocationInterfaceCB  *callback = LocationInterfaceCB :: NewL (aCallback,
        															  &aOutParamList,
        															  &iModuleInfo,
        															  transid ) ;
        CleanupStack :: PushL(callback) ;
        callback->SetRequestType(KTraceCB) ;
        

        
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
	        if (count == 2)	
		        {
		        smapparam = &aInParamList[Index1];
		        if (smapparam)
			        {
			        const CLiwMap  *updateOptionMap = (smapparam->Value() ).AsMap() ;
		        if( !updateOptionMap )
			        {
			        aOutParamList.AppendL( TLiwGenericParam( KErrorMessage,
                                           TLiwVariant( KTraceWrongupdateMap ) ) );
                    CleanupStack :: Pop( callback ) ;
                    delete callback;
                    
                    User::Leave( KErrArgument );
			        }

            	TInt error = SetUpdateOption(updateOptionVal,updateOptionMap);
            	if( KErrBadTime == error )
                	{
                	aOutParamList.AppendL( TLiwGenericParam( KErrorMessage,
                                           TLiwVariant( KTraceNegativeTime ) ) );
                    CleanupStack :: Pop( callback ) ;
                    delete callback;
                    User::Leave( KErrArgument );
                	
                	}
                else if( KErrArgument == error )
	                {
	                aOutParamList.AppendL( TLiwGenericParam( KErrorMessage,
                                           TLiwVariant( KTraceBadUpdateOptions ) ) );
                    
                    CleanupStack :: Pop( callback ) ;
                    delete callback;
                    
                    
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
	                CleanupStack :: Pop( callback ) ;
	                delete callback;
	                
	                User::Leave( KErrArgument );
			        }

	    	    TInt error = SetUpdateOption(updateOptionVal,updateOptionMap);
	        	if( KErrBadTime == error )
	            	{
	            	aOutParamList.AppendL( TLiwGenericParam( KErrorMessage,
	                                       TLiwVariant( KTraceNegativeTime ) ) );
	                CleanupStack :: Pop( callback ) ;
	                delete callback;
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
				
				CleanupStack::Pop(callback);
				delete callback;
	            User::Leave(KErrArgument);	
	            }
	        	
		ret = iLocationService->TraceL(callback , catergory , iFieldList , updateOption ) ;
        //TLiwGenericParam errorParm(KErrorCode , TLiwVariant((TInt32)ret)) ;
        //aOutParamList.AppendL(errorParm) ; 

        if(KErrNone != ret)
            {
                CleanupStack :: Pop(callback) ;
                delete callback ;
                User::Leave(ret);
            }

        
        iHandleCB[KTraceCB] = callback ;
        aOutParamList.AppendL(TLiwGenericParam (KTransactionId , TLiwVariant(transid))) ; //Append Transcationid to out list

        CleanupStack :: Pop(callback) ;
        
        } //End of KCmdTraceLocation

    else if(aCmdName == KCmdCancelRequest)	  //Cancel request is made by consumer 
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
            
            if(KErrNone == ret) ;
                {
                delete iHandleCB[KTraceCB] ;
                iHandleCB[KTraceCB] = NULL ;    //Mark the slot as free 	
                }
            

            }

        else if(requesttype == KRequestGetLoc )
            {
            		
            ret = iLocationService->CancelOnGoingService(ECancelGetLocation) ;
            
            if(!ret) 
                {
                delete iHandleCB[KGetLocationCB] ;
                iHandleCB[KGetLocationCB] = NULL ;    //Mark the slot as free 
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

    else if(aCmdName == KRequestCalculate)
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

TInt CLocationInterface :: SetSupportedFields()
    {
	//Extract all the information Accuracy, timestamp, satellite and course info and append 
	// to out parmlist

	
	
	TUint fieldIter = 0 ;

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
	
	/*if(currCapability & TPositionModuleInfo :: ECapabilityNmea)
    	{
		
		iFieldList[fieldIter++] = EPositionFieldNMEASentences ;
		iFieldList[fieldIter++] = EPositionFieldNMEASentencesStart ;
		
    	}*/
	iFieldList[fieldIter] = EPositionFieldNone  ;   //Field Termination 
   iGenericPosInfo->ClearRequestedFields() ;
   iGenericPosInfo->SetRequestedFields(iFieldList) ;
  
  
  return KErrNone ;
    }

/**
 * CLocationInterface :: GetLocationInfo an internal utility funtionin, gets all the location information 
 * which is supported by  this Module
 */
 
 
void CLocationInterface :: GetLocationInfo( CLiwGenericParamList& aOutParamList,TInt aPosInfoCategory)
    {
    TPosition pos ;
    iGenericPosInfo->GetPosition(pos) ; //Now populate outparam list with latitude, longitude and altitude data

    CLiwDefaultMap *Result = CLiwDefaultMap::NewL() ; 
    
    CleanupStack :: PushL(Result) ;
    TReal64 Val = pos.Longitude() ;

    //Inserting latitude , longitude ,  altitude .
    Result->InsertL(KLongitudeKey , TLiwVariant((TReal)Val)) ; 

    Val = pos.Latitude() ;
    Result->InsertL(KLatitudeKey , TLiwVariant((TReal)Val)) ; 
            
    TReal32 altitude = pos.Altitude() ;
            

    Result->InsertL(KAltitudeKey , TLiwVariant((TReal)altitude)) ; 

    
    TLiwVariant MapVariant(Result) ;
     
   
     TPositionModuleInfo :: TCapabilities  currCapability  = iModuleInfo.Capabilities() ;

	 if ( aPosInfoCategory == EGenericPositionInfo )
	     {
	     if(currCapability & TPositionModuleInfo :: ECapabilitySpeed) //Populate output param with speed info
		    {
		    TReal32 speedinfo = 0 ;

		    if(!iGenericPosInfo->GetValue(EPositionFieldHorizontalSpeed , speedinfo))  //Extract speed 
		    	{
		    	 Result->InsertL(KPositionFieldHorizontalSpeed ,TLiwVariant((TReal) speedinfo)) ;
		    	}



		    if(!iGenericPosInfo->GetValue(EPositionFieldHorizontalSpeedError , speedinfo) )
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


		    }   //End of EcapabilitySpeed 


		 if(currCapability & TPositionModuleInfo :: ECapabilitySatellite) //Extract satellitinfo if any and append it
		    {																//as part of out parm list
		    TInt8 satinfo  = 0;

		    if(!iGenericPosInfo->GetValue(EPositionFieldSatelliteNumInView , satinfo))
		        {
		        Result->InsertL(KPositionFieldSatelliteNumInView ,TLiwVariant((TReal) satinfo)) ;
		        }
			if(!iGenericPosInfo->GetValue(EPositionFieldSatelliteNumUsed , satinfo))
		        {
		        Result->InsertL(KPositionFieldSatelliteNumUsed ,TLiwVariant((TReal) satinfo)) ;
		        }
		    } //End of ECapabilitySatellite

		 if(currCapability & TPositionModuleInfo :: ECapabilityDirection) //Extract direction info if any and append it 
		 {                                                               // as part of out parm list
		 TReal32 direcinfo = 0;


		 if(!iGenericPosInfo->GetValue(EPositionFieldTrueCourse , direcinfo) )
		   {
		   Result->InsertL(KPositionFieldTrueCourse ,TLiwVariant((TReal) direcinfo)) ;
		   }


		 if(!iGenericPosInfo->GetValue(EPositionFieldTrueCourseError , direcinfo) )
		   {
		   Result->InsertL(KPositionFieldTrueCourseError ,TLiwVariant((TReal) direcinfo)) ;
		   }


		 if(!iGenericPosInfo->GetValue(EPositionFieldMagneticCourseError , direcinfo) )
		    {
		    Result->InsertL(KPositionFieldMagneticCourseError ,TLiwVariant((TReal) direcinfo)) ;
		    }


		 if(!iGenericPosInfo->GetValue(EPositionFieldMagneticCourse , direcinfo) )
		    {
		    Result->InsertL(KPositionFieldMagneticCourse ,TLiwVariant((TReal) direcinfo)) ;
		    }
		 } // End of ECapabilityDirection


		if(currCapability & TPositionModuleInfo :: ECapabilityCompass) //Extract compass info if any and append it 
	    	{                                                               // as part of out parm list
	    	TReal32 compassinfo ;

	    	
	    	if(!iGenericPosInfo->GetValue(EPositionFieldHeading , compassinfo) )
	        	{
	        	Result->InsertL(KPositionFieldHeading ,TLiwVariant((TReal) compassinfo)) ;	
	        	}


	    	if(!iGenericPosInfo->GetValue(EPositionFieldHeadingError , compassinfo) )
	        	{
	        	Result->InsertL(KPositionFieldHeadingError ,TLiwVariant((TReal) compassinfo)) ;
	        	}


	    	if(!iGenericPosInfo->GetValue(EPositionFieldMagneticHeading , compassinfo) )
	        	{
	        	Result->InsertL(KPositionFieldMagneticHeading ,TLiwVariant((TReal) compassinfo)) ;
	        	}



	    	if(!iGenericPosInfo->GetValue(EPositionFieldMagneticHeadingError , compassinfo) )
	            {
	            Result->InsertL(KPositionFieldMagneticHeadingError ,TLiwVariant((TReal) compassinfo)) ;

	            } 


	    	} //End of  ECapabilityCompass

		/*if( currCapability & TPositionModuleInfo :: ECapabilityNmea ) //Extract Nmea info if any and append it 	
		    {                                                             //as part of out param list  
		    TUint8 numSentences ;

		    if(!iGenericPosInfo->GetValue(EPositionFieldNMEASentences , numSentences) )
		        {
		        Result->InsertL(KPositionFieldNMEASentences ,TLiwVariant((TReal) numSentences)) ;
		        }


		    TBuf8 <20> nmeaSentences ;
		    if(!iGenericPosInfo->GetValue(EPositionFieldNMEASentencesStart , nmeaSentences) )
		        {
		        Result->InsertL(KPositionFieldNMEASentencesStart ,TLiwVariant( numSentences)) ;
		        }
		    }*/ //End of ECapabilityNmea

	     }
    aOutParamList.AppendL(TLiwGenericParam ( KLocationMap, TLiwVariant(Result))) ;
    Result->DecRef();
    CleanupStack :: Pop(Result) ;
    		
    }


/**
 * Function CLocationInterface :: RequestCancel is used to cancel the pending async request if 
 * returns the cancell status success if transaction id is valid else KErrGeneral error.
 */
 
MLiwNotifyCallback* CLocationInterface :: RequestCancel(TInt32 aTranactionId/*,MLiwNotifyCallback** aCallBack*/)
    {
        TInt ncalls = iHandleCB.Count() ;
        
        for(TInt iter = 0 ; iter < ncalls ;  ++iter )
            {
                
                if( iHandleCB[iter] )
	                {
	                if(iHandleCB[iter]->GetTransactionId() == aTranactionId)
                    	{
                        TInt requestType = iHandleCB[iter]->GetRequestType() ;
                        TInt cancelType = ECancelGetLocation ;
                        
                        
                        if(requestType == KTraceCB)
                            {
                                cancelType = ECancelTrace ;
                            }
                        iLocationService->CancelOnGoingService(cancelType ) ;
                        
                        MLiwNotifyCallback* callobj = iHandleCB[iter]->GetCallBackobj();
                        
                        return( callobj ) ;
                    	}	
	                }
                
            }
        
        //No TransactionId Match found, return Error 
        return NULL ;    
    }
 
 /**
  * This function is a static method to create iLocatinInterface object
  * return pointer to constructed object else paincs with symbian painc 
  * code
  */
  
 CLocationInterface * CLocationInterface :: NewL()
    {
    CLocationInterface *self =  new(ELeave)CLocationInterface() ;



     
    CleanupStack :: PushL(self) ;
    self->iLocationService =  CLocationService :: NewL() ;
    TInt error = (self->iLocationService)->GetModuleInfo(self->iModuleInfo) ;
    	

    User :: LeaveIfError(error) ;

    error = (self->SetSupportedFields()) ;

    User :: LeaveIfError(error) ;
    CleanupStack :: Pop(self) ;
    return self ;
    	
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
   * Function: ConvertPosToGenricList puts the latitude, longitude and altitude information 
   *  into generic parmater list
   *  This is an internal utility function
  */
  
 void CLocationInterface :: ConvertPosToGenricListL( TPosition& aPos , CLiwGenericParamList& aOutList )
    {
    CLiwDefaultMap *Result = CLiwDefaultMap::NewL() ; 
    TReal64 Val = aPos.Longitude() ;

    Result->InsertL(KLongitudeKey , TLiwVariant((TReal)Val)) ; //Inserting latitude

    Val = aPos.Latitude() ;
    Result->InsertL(KLatitudeKey , TLiwVariant((TReal)Val)) ; //Inserting latitude
            
    TReal32 altitude = aPos.Altitude() ;
            

    Result->InsertL(KAltitudeKey , TLiwVariant((TReal)altitude)) ; //Inserting altitude

    //Now Push this map into outparm list 
     TLiwVariant MapVariant(Result) ;
     
     TLiwGenericParam outParm(KLocationMap , TLiwVariant(MapVariant)) ;
    // outParm.SetSemanticId(EGenericParamLocation) ;
     aOutList.AppendL(outParm) ;
     Result->DecRef();
     
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

