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
* Description:  This Class provides the core functionality to thumbnail generation 
*               
*
*/


#include<e32cmn.h>

#include<f32file.h>
#include<APGCLI.H>
#include<APMREC.H> // For TDataRecognitionResult
#include<APMSTD.H> 
#include<thumbnailmanager.h>
#include"mgthumbnailgeneration.h"

#include"mgmresolution.h"
#include"mgthumbobserver.h"
_LIT(KImage,"image");
_LIT(KVideo,"video");
_LIT(KThumbFolder,"_PAlbTN_");
const TInt KHeight = 74 ;
const TInt KWidth = 104;
const TInt KThumbnailPathMaxLen = 255;
const TInt KBufLen = 20;
const TInt KZero = 0;

// -----------------------------------------------------------------------------
// CThumbnailGeneration::NewL
// Returns the instance of CThumbnailGeneration class.
// -----------------------------------------------------------------------------
 CThumbnailGeneration* CThumbnailGeneration::NewL()
    {
    CThumbnailGeneration* self = new(ELeave)CThumbnailGeneration();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
     return self;
    }

 // -----------------------------------------------------------------------------
 // CThumbnailGeneration::ConstructL
 // It creates the instance of TNM and Observer
 // -----------------------------------------------------------------------------
void  CThumbnailGeneration::ConstructL()
     {
      // Creating instance of observer class
     iThumbnailObserver = CThumbnailObserver::NewL();
     //Creating instance of ThumbnailManger 
     iThumbnailManager = CThumbnailManager::NewL(*iThumbnailObserver);  
     iThumbnailObserver->SetThumbnailMangager(iThumbnailManager);
  
      }
 
// -----------------------------------------------------------------------------
// CThumbnailGeneration::~CThumbnailGeneration
// Destructor
// -----------------------------------------------------------------------------
CThumbnailGeneration::~CThumbnailGeneration()
    {
    if(iThumbnailObserver)
        {
        delete iThumbnailObserver;
        }
    if(iThumbnailManager)
        {
        delete iThumbnailManager;
        }

    }

// -----------------------------------------------------------------------------
 // CThumbnailGeneration::CThumbnailGeneration
 // C++ Constructor 
 // -----------------------------------------------------------------------------
 CThumbnailGeneration::CThumbnailGeneration():iThumbnailObserver(NULL),iThumbnailManager(NULL)
    {
    
    }
 
 // -----------------------------------------------------------------------------
  // CThumbnailGeneration::Cancel
  // Cancels the thumbnail generation request
  // -----------------------------------------------------------------------------
 TInt CThumbnailGeneration::Cancel(TInt32 aTransactionId)
     {
     return iThumbnailObserver->Cancel(aTransactionId);
     }
 
 
 // -----------------------------------------------------------------------------
 // CThumbnailGeneration::GetThumbnailL
 // This method makes request for thumbnail generation
 // -----------------------------------------------------------------------------
 
  
 void CThumbnailGeneration::GetThumbnailL(MThumbnailObserver* aObserver,TInt32 aTransactionID, TDesC& aUrl, TInt aHeight, TInt aWidth)
    {
   	
     // Check whether uri is valid
     TBuf<KThumbnailPathMaxLen> thumbnailpath;
     TBuf<KThumbnailPathMaxLen> refDir;
      
     // Checking validity of media file name
     IsUrlValidL( aUrl);
    
     // getting thumbnail size
     TSize thumbsize = GetthumbsizeL(aUrl,aHeight,aWidth);
     
     //creating thumbnail path
     CreateThumbnailPathL(aUrl,thumbsize,refDir,thumbnailpath);
        
     // If thumbnail already exists then give a call to users callback 
     if(IsThumbnailExistL(thumbnailpath,refDir))
         {
         iThumbnailObserver->AddToObserverL(aObserver,aTransactionID,thumbnailpath,KZero);
         iThumbnailObserver->ThumbnailAlreadyExists();
         return ;
         }
     
     
        iThumbnailManager->SetFlagsL(CThumbnailManager::ECropToAspectRatio);
    
        
        // Setting thumbnail size
        iThumbnailManager->SetThumbnailSizeL( thumbsize );
  
        // Prefer thumbnails in the highest quality possible disregarding
        // any negative impact on performance.
        iThumbnailManager->SetQualityPreferenceL(CThumbnailManager::EOptimizeForQuality );
  
        //setting display mode EColor16M for both video and image it works
        iThumbnailManager->SetDisplayModeL( EColor16M  );
  
        // Create an object source representing a path to a file on local
        // file system.
        CThumbnailObjectSource*  source = CThumbnailObjectSource::NewLC(aUrl,KNullDesC); 
  
        // Issue the request using default priority
        TInt thumbnailRequestId = iThumbnailManager->GetThumbnailL( *source );
  
        CleanupStack::PopAndDestroy(source);

           
        
        // Adding thumbanilrequestinfo to observer
        
        iThumbnailObserver->AddToObserverL(aObserver,aTransactionID,thumbnailpath,thumbnailRequestId);
  
     }
  
 // -----------------------------------------------------------------------------
 // CThumbnailGeneration::getthumbsizeL
 // This method gets the size for thumbnail 
 // -----------------------------------------------------------------------------
  TSize CThumbnailGeneration::GetthumbsizeL(TDesC& aUrl,TInt aHeight, TInt aWidth)
      {
      // Creating media resolution object 
      TSize mediaRes(0,0);
      TSize thumbsize(0,0);
      MResolution* mediaResObj= GetResolutionobjL(aUrl);
      CleanupStack::PushL(mediaResObj);
      // Getting resolution for media file
      mediaResObj->GetresolutionL(mediaRes);
      
      // calculating size for thumbnail
      thumbsize = CalculateSize(mediaRes,aHeight,aWidth);
      CleanupStack::Pop(mediaResObj);
      delete mediaResObj;
      return thumbsize;
      
      }
  
  // -----------------------------------------------------------------------------
  // CThumbnailGeneration::CalculateSize
  // This method calculates the size for thumbnail 
  // -----------------------------------------------------------------------------
  TSize CThumbnailGeneration::CalculateSize(TSize aRes, TInt aHeight, TInt aWidth)
       {
       TSize thumbnailsize;
       
       if(KNegVal == aHeight && KNegVal == aWidth ) 
	       {
	       	if( (aRes.iWidth < KWidth)  || (aRes.iHeight< KHeight) ) // if the resolution of media file is less than that of plaformspecific
		       	{
		        thumbnailsize.iWidth = aRes.iWidth; 
		               
		        thumbnailsize.iHeight =aRes.iHeight;	       		
		       	}
	       	else // if resolution of video file is greater that platform specific
		       	{
		        thumbnailsize.iWidth = KWidth; 
		               
		        thumbnailsize.iHeight = KHeight;
	
		       	}
					return thumbnailsize;
	      	}
       
       if(TSize(0,0) == aRes )
           {
           // If both height and width are not given or either of them are having value than that of platformspecific resolution
           // then we will use platform specific size
           if( (aHeight >KZero && (aHeight>KHeight) ) || (aWidth >KZero && (aWidth >KWidth ))  )
               {
                             
               thumbnailsize.iWidth = KWidth; 
               
               thumbnailsize.iHeight = KHeight;

               }
           else if(KNegVal == aWidth ) // if height is given and width not given
               {
                thumbnailsize.iWidth = (TInt)((TReal)(KWidth/KHeight)* aHeight);
                
                thumbnailsize.iHeight = aHeight ;
          
                }
           else if(KNegVal == aHeight)// if width is given and height not given
               {
               thumbnailsize.iHeight = (TInt)(((TReal)KHeight/KWidth ) * aWidth) ;
               thumbnailsize.iWidth = aWidth ;
               }
           else // when both are given 
               {
               thumbnailsize.iWidth = aWidth; 
               
               thumbnailsize.iHeight = aHeight;
               
               }
           
           }
       else // When we get the resolution of media file
           {
           
           // If both height and width are not given or either of them are having value greater than that of media file 
            // then we will use platform specific size
            if( (aHeight >KZero && (aHeight > aRes.iHeight) ) || (aWidth >KZero && (aWidth > aRes.iWidth ))  )
                {
                              
                thumbnailsize.iWidth = aRes.iWidth ;
                thumbnailsize.iHeight = aRes.iHeight ;

                }
            else if(KNegVal == aWidth )// if height is given and width is not given
                {
                 thumbnailsize.iWidth = (TInt)((TReal)(aRes.iWidth/aRes.iHeight)* aHeight);
                 
                 thumbnailsize.iHeight = aHeight ;
           
                 }
            else if(KNegVal == aHeight)// if width is given and height not given
                {
                thumbnailsize.iHeight = (TInt)(((TReal)aRes.iHeight/aRes.iWidth ) * aWidth) ;
                thumbnailsize.iWidth = aWidth ;
                }
            else // when both are given 
                {
                thumbnailsize.iWidth = aWidth; 
                 
                 thumbnailsize.iHeight = aHeight;               
                }

           

           }
       return thumbnailsize;
       }

// -----------------------------------------------------------------------------
// CThumbnailGeneration::GetResolutionobj
// This method gets the MResolution object 
// -----------------------------------------------------------------------------
 MResolution* CThumbnailGeneration::GetResolutionobjL(TDesC& aUrl)
        {
      
        RFs fs;
        TBuf8<KThumbnailPathMaxLen> filebuf;
        TInt fileSize = KThumbnailPathMaxLen;
        User::LeaveIfError(fs.Connect());
        CleanupClosePushL(fs);
        
        User::LeaveIfError(fs.ReadFileSection(aUrl,KZero,filebuf,fileSize));
        
              
        // Opening RApaLsSession to get mimetype of media file
        RApaLsSession aPaSession;
        User::LeaveIfError(aPaSession.Connect());
        CleanupClosePushL(aPaSession);
        
        TDataRecognitionResult mimeTypeResult;
        TBuf<KBufLen> media;
        if(KErrNone == aPaSession.RecognizeData(aUrl,filebuf,*&mimeTypeResult))
            {
            // If media type is of image then creating image resolution object
            if(KZero == mimeTypeResult.iDataType.Des().Find(KImage) )
                {
                media.Append(KImage);
                }
            else if(KZero == mimeTypeResult.iDataType.Des().Find(KVideo))
                {
                 media.Append(KVideo);
                }
            else
                {
                User::Leave(KErrNotSupported);
                }
            }
        else
            {
            // Need to leave from here
            User::Leave(KErrNotSupported);
            }
       
        CleanupStack::PopAndDestroy(&aPaSession); // aPaSession
        CleanupStack::PopAndDestroy(&fs);  // fs
        
        
        return MediaResolutionFactory::CreateMediaResolutionobjL(media,aUrl);
        }
 

// -----------------------------------------------------------------------------
// CThumbnailGeneration::IsThumbnailExist
// This method checks if the requested thumbnail already exists 
// -----------------------------------------------------------------------------
TBool CThumbnailGeneration::IsThumbnailExistL(const TDesC& aThumbpath,const TDesC& aRefDir)
    {
    // Need to check whether thumbnail exists .
    
    RFs fs;
    User::LeaveIfError(fs.Connect());
    CleanupClosePushL(fs);
    RFile file;
 
    if(KErrNone == file.Open(fs,aThumbpath,EFileRead))
        {
        // thumbnail exist so return ETrue
        file.Close();
        CleanupStack::PopAndDestroy(&fs);
        return ETrue;
        }
    
    
    
    // Need to check whether dir panltn exist
    TInt ret = fs.MkDirAll(aRefDir);
    
    if( !(KErrNone == ret || KErrAlreadyExists == ret)  )
        {
        User::Leave(ret);
        }
    
  
      
    CleanupStack::PopAndDestroy(&fs);
    return EFalse;
    
    
    }

// -----------------------------------------------------------------------------
// CThumbnailGeneration::IsUrlValid
// This method checks the validity of Url
// -----------------------------------------------------------------------------
void   CThumbnailGeneration::IsUrlValidL(TDesC& aUrl)
    {
     RFs fs;
     User::LeaveIfError(fs.Connect());
     
     // If the url is not in correct filepath format
     if(!fs.IsValidName(aUrl))
         {
         fs.Close();
         User::Leave(KErrBadName);
         
         }

     // If file is not present
     RFile file;
   
     if(KErrNone != file.Open(fs,aUrl,EFileRead))
         {
         file.Close();
         fs.Close();
         User::Leave(KErrNotFound);
         
         }
     
     file.Close();
     fs.Close();
      }

// -----------------------------------------------------------------------------
// CThumbnailGeneration::createThumbnailPath
// This method creates the thumbnail path 
// -----------------------------------------------------------------------------
void CThumbnailGeneration::CreateThumbnailPathL(TDesC& aUri, TSize aThumbsize,TDes& aRefDir ,TDes& aThumbnailPath)
    {
     
    
    TInt strlength = aUri.Length();
    TChar chr('\\'); 
   TInt len = aUri.LocateReverseF(chr);
   
   if(KErrNotFound == len)
       {
       User::Leave(KErrBadName);
       }
   
  
   TBuf<KThumbnailPathMaxLen> refpathbuf;
   TBuf<KThumbnailPathMaxLen> buf;
   buf.Append(aUri.Left(len+1));
   buf.Append(KThumbFolder);
   refpathbuf.Append(buf);
   refpathbuf.Append(_L("\\"));
   aRefDir.Append(refpathbuf);  // setting refdir argument
   buf.Append(aUri.Right(strlength-len));
   buf.Append('_');
   buf.AppendNum(aThumbsize.iWidth);
   buf.Append('x');
   buf.AppendNum(aThumbsize.iHeight);
   aThumbnailPath.Append(buf);
    
   return;
    
    
    }


