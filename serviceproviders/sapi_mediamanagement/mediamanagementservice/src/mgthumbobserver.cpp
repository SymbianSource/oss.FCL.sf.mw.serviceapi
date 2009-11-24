/*
* Copyright (c) 2007-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  This Class is observer for thumbnail generation
*
*/


#include<e32std.h>

#include<thumbnaildata.h>
#include<fbs.h>
#include"mgthumbobserver.h"
#include"mgthumbnailobserver.h"


const TInt KNulLen = 20;
const TInt KZero = 0;
// -----------------------------------------------------------------------------
// CThumbnailObserver::NewL
// Returns the instance of CThumbnailObserver.
// -----------------------------------------------------------------------------
CThumbnailObserver* CThumbnailObserver::NewL()
    {
    CThumbnailObserver* self = new ( ELeave )CThumbnailObserver();
    CActiveScheduler::Add(self);
    return self;
    }


// -----------------------------------------------------------------------------
// CThumbnailObserver::ThumbnailPreviewReady
// This method is called when thumbnail generation operation completes
// -----------------------------------------------------------------------------
 void CThumbnailObserver::ThumbnailPreviewReady(MThumbnailData& aThumbnail, TThumbnailRequestId aId)
    {
    // No implementation



    }

// -----------------------------------------------------------------------------
// CThumbnailObserver::ThumbnailPreviewReady
// This method is called when thumbnail generation operation completes
// -----------------------------------------------------------------------------
void CThumbnailObserver::ThumbnailReady(TInt aError, MThumbnailData& aThumbnail, TThumbnailRequestId aId)
    {
    	
   // Findingout the ThumbanilRequestInfo object
    TInt pos = iThumbnailRequestArray.Count() - 1;
    
    TThumbnailRequestInfo obj;
      for ( ; pos >= 0; pos-- )
          {
       
          obj =  iThumbnailRequestArray[pos];
          if(obj.iThumbnailRequestId == aId )
              {
              iThumbnailRequestArray.Remove(pos);
              iThumbnailRequestArray.Compress();
              
              break;
              
              }

          }   
    

    if( KErrNone == aError )
        {
  
        // Getting Bitmap of thumbnail
        CFbsBitmap* bitmap = aThumbnail.DetachBitmap();
        
           // Saving it to local path
        bitmap->Save(*(obj.iThumbnailPath));
        // calling observer with thumbanil path
        obj.iObserver->ThumbnailReady(aError,*(obj.iThumbnailPath),obj.iTransactionId);
	
        delete bitmap;
        }
    else if (KErrNotFound == aError ){
    
        obj.iObserver->ThumbnailReady(KErrAlreadyExists,*(obj.iThumbnailPath),obj.iTransactionId);
    
        }
    else
        {
     	
        TBuf<KNulLen> buf;
        buf.Append(KNullDesC);
        obj.iObserver->ThumbnailReady(aError,buf,obj.iTransactionId);
    
        }
   // Deleting the instance of ThumbanilRequestInfo
    // We need to delete only iThumbnailPath and need to make iObserver as NULL
    obj.iObserver = NULL;
    
    if(obj.iThumbnailPath)
    	delete obj.iThumbnailPath;
   
}



// -----------------------------------------------------------------------------
// CThumbnailObserver::CThumbnailObserver
// C++ Constructor
// -----------------------------------------------------------------------------
CThumbnailObserver::CThumbnailObserver():CActive(EPriorityHigh),iThumbnailManager(NULL)
    {
    
    }

// -----------------------------------------------------------------------------
// CThumbnailObserver::~CThumbnailObserver
// Destructor
// -----------------------------------------------------------------------------
CThumbnailObserver::~CThumbnailObserver()
    {
   
     // logic for cleaning up the array
    
    TInt pos = iThumbnailRequestArray.Count() - 1;
    TThumbnailRequestInfo obj;
     for ( ; pos >= 0; pos-- )
         {
         obj = iThumbnailRequestArray[pos];
         
         //calling Cancel for the request
         iThumbnailRequestArray.Remove(pos);
         iThumbnailRequestArray.Compress();
         if(iThumbnailManager)
         		{
         			TInt ret = iThumbnailManager->CancelRequest(obj.iThumbnailRequestId);
         	
         // Calling users callback for cancellig request
		         if(obj.iObserver)
		         		{
         	
		        	 	obj.iObserver->ThumbnailRequestCancel(ret,obj.iTransactionId);
		       			}
						
				}
         // Deleting the instance of ThumbanilRequestInfo
           // We need to delete only iThumbnailPath and need to make iObserver as NULL
         obj.iObserver = NULL;
         		
         	if(obj.iThumbnailPath)	
          		{
				delete obj.iThumbnailPath;
				}
           
    
          
             }
     iThumbnailRequestArray.Close();
    
     iThumbnailManager = NULL;
    
    }
// -----------------------------------------------------------------------------
// CThumbnailObserver::Cancel
// Cancels the request of thumbnail generation
// -----------------------------------------------------------------------------
TInt CThumbnailObserver::Cancel(TInt32 aTransactionID)
    {
    
    // Search for TThumbnailRequest corresponding to thumbanil request
    
    TInt pos = iThumbnailRequestArray.Count() - 1;
    TThumbnailRequestInfo obj;
     for ( ; pos >= 0; pos-- )
         {
         obj = iThumbnailRequestArray[pos];
                 
         if( obj.iTransactionId == aTransactionID )
             {
             iThumbnailRequestArray.Remove(pos);
             iThumbnailRequestArray.Compress();
             TInt ret = iThumbnailManager->CancelRequest(obj.iThumbnailRequestId);
             
              obj.iObserver->ThumbnailRequestCancel(ret,obj.iTransactionId);   
              
              // Deleting the instance of ThumbanilRequestInfo
               // We need to delete only iThumbnailPath and need to make iObserver as NULL
                  obj.iObserver = NULL;

               if(obj.iThumbnailPath)   	
               		{
					delete obj.iThumbnailPath;
					}
              
             return ret;
             }
         }
     return KErrNotFound;
    }

// -----------------------------------------------------------------------------
// CThumbnailObserver::AddToObserver
// Add ThumbnailRequestInfo to observer
// -----------------------------------------------------------------------------
void CThumbnailObserver::AddToObserverL(MThumbnailObserver* aObserver,TInt32 aTransactionID ,TDesC& aThumbnailPath , TThumbnailRequestId aThumbnailRequestId)
    {
    
    
    TThumbnailRequestInfo thumbnailRequestInfo ;
 
    thumbnailRequestInfo.iObserver = aObserver;
    thumbnailRequestInfo.iThumbnailPath = aThumbnailPath.Alloc();
    thumbnailRequestInfo.iThumbnailRequestId = aThumbnailRequestId;
    thumbnailRequestInfo.iTransactionId = aTransactionID;

      iThumbnailRequestArray.Append( thumbnailRequestInfo ) ;
 
    
    }
// -----------------------------------------------------------------------------
// CThumbnailObserver::ThumbnailAlreadyExists
// 
// -----------------------------------------------------------------------------
void CThumbnailObserver::ThumbnailAlreadyExists()
    {
 
    iStatus = KRequestPending;
    SetActive();
    TRequestStatus* temp = &iStatus;
    User::RequestComplete( temp, KErrNone );
    }

// -----------------------------------------------------------------------------
// CThumbnailObserver::SetThumbnailMangager
// Sets the thumbnail manager instance
// -----------------------------------------------------------------------------

void CThumbnailObserver:: SetThumbnailMangager(CThumbnailManager* aThumbnailManager)
{
iThumbnailManager = aThumbnailManager;

}
// -----------------------------------------------------------------------------
// CThumbnailObserver::RunL
// 
// -----------------------------------------------------------------------------
   
void CThumbnailObserver::RunL()
    {
    // calling callback method

    TInt pos = iThumbnailRequestArray.Count() - 1;
     TThumbnailRequestInfo obj;
      for ( ; pos >= 0; pos-- )
          {
          obj = iThumbnailRequestArray[pos];
                  
          if( obj.iThumbnailRequestId == KZero )
              {
              iThumbnailRequestArray.Remove(pos);
              iThumbnailRequestArray.Compress();
              
              
               obj.iObserver->ThumbnailReady(KErrAlreadyExists ,*obj.iThumbnailPath,obj.iTransactionId);   
               
               // Deleting the instance of ThumbanilRequestInfo
                // We need to delete only iThumbnailPath and need to make iObserver as NULL
                   obj.iObserver = NULL;
			   if(obj.iThumbnailPath)
		           {
				    delete obj.iThumbnailPath;
					}
					
              }
          }
      
              
  
    }
// -----------------------------------------------------------------------------
// CThumbnailObserver::DoCancel
// 
// -----------------------------------------------------------------------------
void CThumbnailObserver::DoCancel()
    {
    
    }
