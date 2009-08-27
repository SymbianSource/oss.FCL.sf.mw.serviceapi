/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Implementation of the sync api's of the contact sapi's.
*
*/



//user includes
#include "contactservice.h"
#include "contactsynccallback.h"


/*
-----------------------------------------------------------------------------
    CContactService     :: GetListL
    Description          : synchronous implementation of GetList api.                        
    Return values        : CContactIter*
-----------------------------------------------------------------------------
*/
EXPORT_C
CContactIter* CContactService::GetListL(Ttype atype,
        	    						const TDesC8& aContactId,        	    						
        	    						const TDesC& aSearchVal,
        	    						CSearchFields* aSearchFields,
        	    						TOrder aSortOrder,
        	    						const TDesC& aStoreUri,
        	    						TCmdType aval)
    {    
    //create the callback object internally
    CContactSyncCallback* callback = new(ELeave) CContactSyncCallback();    
    CleanupStack::PushL(callback);
    //create the wait scheduler instance
    CActiveSchedulerWait* waitScheduler = new(ELeave) CActiveSchedulerWait(); 
    CleanupStack::PushL(waitScheduler); 
    //needed to stop the scheduler by the callback instance       
    callback->SetWaitScheduler(waitScheduler);  
    //call the asynch sapi with all the params  
    TRAPD(err,GetListL(callback,
        			   0,
        			   atype,
        			   aContactId,        			   
        			   aSearchVal,
        			   aSearchFields,
        			   aSortOrder,
        			   aStoreUri,
        			   aval));
    //TRAP harness is used to unset the sync flag in leaving condition
    //since we r using the same async apis for sync implementation       			   
    if(KErrNone != err)    
        {
        User::Leave(err);
        }    			   
	//start the wait scheduler and wait untill the operation finishes
	waitScheduler->Start();
    //Unset the callbak pointer 	
	callback->SetWaitScheduler(NULL);	
    //check for any errors 
	TInt error = callback->GetErrorCode();
	if(KErrNone != error)    
        {
        User::Leave(error);
        }
	CContactIter* tempIter = callback->GetIter();
	CleanupStack::PopAndDestroy(waitScheduler);
    CleanupStack::PopAndDestroy(callback);
	return tempIter;           
    }


/*
-----------------------------------------------------------------------------
    CContactService     :: GetIdsL
    Description          : synchronous implementation of GetIds api.                        
    Return values        : RPointerArray<HBufC8>&
-----------------------------------------------------------------------------
*/

EXPORT_C
RPointerArray<HBufC8>& CContactService::GetIdsL(Ttype atype,                                     
                                        const TDesC& aSearchVal,
                                        CSearchFields* aSearchFields,
                                        TOrder aSortOrder,
                                        const TDesC& aStoreUri,
                                        TCmdType aval)
    {    
    //create the callback object internally
    CContactSyncCallback* callback = new(ELeave) CContactSyncCallback();    
    CleanupStack::PushL(callback);
    //create the wait scheduler instance
    CActiveSchedulerWait* waitScheduler = new(ELeave) CActiveSchedulerWait(); 
    CleanupStack::PushL(waitScheduler); 
    //needed to stop the scheduler by the callback instance       
    callback->SetWaitScheduler(waitScheduler);  
    //call the asynch sapi with all the params  
    TRAPD(err,GetListL(callback,
                       0,
                       atype,
                       KNullDesC8,                     
                       aSearchVal,
                       aSearchFields,
                       aSortOrder,
                       aStoreUri,
                       aval));
    //TRAP harness is used to unset the sync flag in leaving condition
    //since we r using the same async apis for sync implementation                     
    if(KErrNone != err)    
        {
        User::Leave(err);
        }                  
    //start the wait scheduler and wait untill the operation finishes
    waitScheduler->Start();
    //Unset the callbak pointer     
    callback->SetWaitScheduler(NULL);   
    //check for any errors 
    TInt error = callback->GetErrorCode();
    if(KErrNone != error)    
        {
        User::Leave(error);
        }
    RPointerArray<HBufC8>* tempArray = new (ELeave) RPointerArray<HBufC8>;
    //get the array of ids of contacts/groups
    callback->GetArray(tempArray);
    CleanupStack::PopAndDestroy(waitScheduler);
    CleanupStack::PopAndDestroy(callback);
    return *tempArray;           
    }
/*
-----------------------------------------------------------------------------
    CContactService     :: AddL
    Description          : synchronous implementation of AddL api.                        
    Return values        : CContactIter*
-----------------------------------------------------------------------------
*/

EXPORT_C
HBufC8* CContactService:: AddL( CSingleContact* aContact,        
    						 const TDesC8& aGroupId,
    						 const TDesC& aGroupLabel,
    						 const TDesC& aStoreUri)
    {
    iErrKey = 0;
    //create the callback object internally
    CContactSyncCallback* callback = new(ELeave) CContactSyncCallback();
    CleanupStack::PushL(callback);
    //create the wait scheduler instance
    CActiveSchedulerWait* waitScheduler = new(ELeave) CActiveSchedulerWait(); 
    CleanupStack::PushL(waitScheduler); 
     //needed to stop the scheduler by the callback instance       
    callback->SetWaitScheduler(waitScheduler);
    //call the asynch sapi with all the params 
    TRAPD(err,AddL(callback,
            	   0,
            	   aContact,
            	   aGroupId,
            	   aGroupLabel,
            	   aStoreUri));
    //TRAP harness is used to unset the sync flag in leaving condition
    //since we are using the same async apis for sync implementation           	   
    if(err!= KErrNone)
        {
        User::Leave(err);
        }        	   
    //start the wait scheduler and wait untill the operation finishes
	waitScheduler->Start();
	//Unset the callbak pointer
	callback->SetWaitScheduler(NULL);	    
    //check for any errors 
	TInt error = callback->GetErrorCode();
	if(  error!= KErrNone )							
        {
        if(error == KErrNotSupported && callback->iErrKey != 0)
            {
            iErrKey = callback->iErrKey;    
            }
        User::Leave(error);
        }
   
	    HBufC8* cntIdVal = callback->GetId();
        
       CleanupStack::PopAndDestroy(waitScheduler);    
       CleanupStack::PopAndDestroy(callback);
       return cntIdVal;
	   
    }


/*
-----------------------------------------------------------------------------
    CContactService     :: DeleteL
    Description          : synchronous implementation of DeleteL api.                        
    Return values        : CContactIter*
-----------------------------------------------------------------------------
*/


EXPORT_C void CContactService:: DeleteL(RPointerArray<TDesC8>& aContactIdArray,
   						                const TDesC& aStoreUri)
    {
    //create the callback object internally
    CContactSyncCallback* callback = new(ELeave) CContactSyncCallback();
    CleanupStack::PushL(callback);
    //create the wait scheduler instance
    CActiveSchedulerWait* waitScheduler = new(ELeave) CActiveSchedulerWait(); 
    CleanupStack::PushL(waitScheduler); 
     //needed to stop the scheduler by the callback instance        
    callback->SetWaitScheduler(waitScheduler);
    //call the asynch sapi with all the params 
    TRAPD(err,DeleteL(callback,
                      0,
                      aContactIdArray,
                      aStoreUri));
    //TRAP harness is used to unset the sync flag in leaving condition
    //since we r using the same async apis for sync implementation                     
    if(err!= KErrNone)
        {
        User::Leave(err);
        }        
	//start the wait scheduler and wait untill the operation finishes
	waitScheduler->Start();
	//Unset the callbak pointer
	callback->SetWaitScheduler(NULL);	
    //check for any errors 
	TInt error = callback->GetErrorCode();
	if(  error!= KErrNone )
        {
        User::Leave(error);
        }
    CleanupStack::PopAndDestroy(waitScheduler);    
    CleanupStack::PopAndDestroy(callback);
    }


 
/*
-----------------------------------------------------------------------------
    CContactService     :: OrganiseGroupsL
    Description          : synchronous implementation of OrganiseGroupsL api.                        
    Return values        : CContactIter*
-----------------------------------------------------------------------------
*/


  EXPORT_C void CContactService:: OrganiseGroupsL(	const TDesC8& aGroupId,
                   								  	RPointerArray<TDesC8>& aContactIdArray,
                   								  	TBool aAssociateFlag,
                   								    const TDesC& aStoreUri)
    {
    //create the callback object internally
    CContactSyncCallback* callback = new(ELeave) CContactSyncCallback();    
    CleanupStack::PushL(callback);
    //create the wait scheduler instance
    CActiveSchedulerWait* waitScheduler = new(ELeave) CActiveSchedulerWait(); 
    CleanupStack::PushL(waitScheduler);   
     //needed to stop the scheduler by the callback instance      
    callback->SetWaitScheduler(waitScheduler);
    //call the asynch sapi with all the params 
    //TInt err = KErrNone;
    TRAPD(err,OrganiseGroupsL(callback,
                    0,
                    aGroupId,
                    aContactIdArray,
                    aAssociateFlag,
                    aStoreUri));
    //TRAP harness is used to unset the sync flag in leaving condition
    //since we r using the same async apis for sync implementation                
	if(err!= KErrNone)
        {
        User::Leave(err);
        }                
	//start the wait scheduler and wait untill the operation finishes
	waitScheduler->Start();
	//Unset the callbak pointer
	callback->SetWaitScheduler(NULL);	
    //check for any errors 
	TInt error = callback->GetErrorCode();
	if(error!= KErrNone)
        {
        User::Leave(error);
        }
    CleanupStack::PopAndDestroy(waitScheduler);
    CleanupStack::PopAndDestroy(callback);
    }


/*
-----------------------------------------------------------------------------
    CContactService     :: ExportVCardL
    Description          : synchronous implementation of ExportVCardL api.                        
    Return values        : CContactIter*
-----------------------------------------------------------------------------
*/


  EXPORT_C void CContactService::ExportVCardL(const TFileName& aFileName,
                                              const TDesC8& aContactId,
                                              const TDesC& aStoreUri)

    {
    //create the callback object internally
    CContactSyncCallback* callback = new(ELeave) CContactSyncCallback();
    CleanupStack::PushL(callback);
    //create the wait scheduler instance
    CActiveSchedulerWait* waitScheduler = new(ELeave) CActiveSchedulerWait(); 
    CleanupStack::PushL(waitScheduler); 
     //needed to stop the scheduler by the callback instance       
    callback->SetWaitScheduler(waitScheduler);
    //call the asynch sapi with all the params 
    TRAPD(err,ExportVCardL(callback,
                           0,
                           aFileName,
                           aContactId,
                           aStoreUri));
    //TRAP harness is used to unset the sync flag in leaving condition
    //since we r using the same async apis for sync implementation                          
    if(err!= KErrNone)
        {
        User::Leave(err);
        } 
	//start the wait scheduler and wait untill the operation finishes
	waitScheduler->Start();
	//Unset the callbak pointer
	callback->SetWaitScheduler(NULL);
    //check for any errors 
	TInt error = callback->GetErrorCode();
	if(  error!= KErrNone )
        {
        User::Leave(error);
        }
    CleanupStack::PopAndDestroy(waitScheduler);    
    CleanupStack::PopAndDestroy(callback);
    }

/*
-----------------------------------------------------------------------------
    CContactService     :: ImportVCardToStoreL
    Description          : synchronous implementation of ImportVCardToStoreL api.                        
    Return values        : CContactIter*
-----------------------------------------------------------------------------
*/

 EXPORT_C void CContactService::ImportVCardToStoreL(const TFileName& aFilename,
                                                    const TDesC& aStoreUri)
    {
    //create the callback object internally
    CContactSyncCallback* callback = new(ELeave) CContactSyncCallback();
    CleanupStack::PushL(callback);
    //create the wait scheduler instance
    CActiveSchedulerWait* waitScheduler = new(ELeave) CActiveSchedulerWait(); 
    CleanupStack::PushL(waitScheduler); 
     //needed to stop the scheduler by the callback instance       
    callback->SetWaitScheduler(waitScheduler);
    //call the asynch sapi with all the params 
    TRAPD(err,ImportVCardToStoreL(callback,
                                  0,
                                  aFilename,
                                  aStoreUri));
    //TRAP harness is used to unset the sync flag in leaving condition
    //since we r using the same async apis for sync implementation                                 
    if(err!= KErrNone)
        {
        User::Leave(err);
        } 
	//start the wait scheduler and wait untill the operation finishes
	waitScheduler->Start();
	//Unset the callbak pointer
	callback->SetWaitScheduler(NULL);    
    //check for any errors 
	TInt error = callback->GetErrorCode();
	if(  error!= KErrNone )
        {
        User::Leave(error);
        }
    CleanupStack::PopAndDestroy(waitScheduler);    
    CleanupStack::PopAndDestroy(callback);
    }

