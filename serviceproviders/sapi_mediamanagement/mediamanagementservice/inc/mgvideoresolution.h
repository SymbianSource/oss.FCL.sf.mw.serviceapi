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
* Description:  This Class is used to find resolution of video file
*
*/

#ifndef MGVIDEORESOLUTION_H_
#define MGVIDEORESOLUTION_H_


#include <VideoPlayer.h>

#include<e32std.h>
#include<e32base.h>
#include"mgmresolution.h"

class CMediaContainer;
/**
*  CVideoResolution class This class is used to find resolution of video file
*  @since  Series60 v3.2
*/
class CVideoResolution: public CBase , public MResolution,public MVideoPlayerUtilityObserver
    {
    public:
        /**
         * Two-phased constructor
        * @return CVideoResolution*  Returns the instance of
         *                                 CVideoResolution.
         */         
        static CVideoResolution* NewL(TDesC& aUrl);
        /**
         * This method gets the resolution
         * @param  aSize  On return it is the resolution of media file 
         * @return TBool                                
         */   
        TBool GetresolutionL(TSize& aSize);
        /**
         * Destructor
         */   
        ~CVideoResolution();
    
    public:

        /**
         * Protected method derived from MVideoPlayerUtilityObserver
         * @aError Error returned 
         */           
         void MvpuoOpenComplete(TInt aError);
         /**
          * Protected method derived from MVideoPlayerUtilityObserver
          * @aError Error returned 
          */           

         void MvpuoPrepareComplete(TInt aError);
         /**
          * Protected method derived from MVideoPlayerUtilityObserver
          * @aFrame Bitmap 
          * @aError  Errorcoede
          */           

         void MvpuoFrameReady(CFbsBitmap& aFrame,TInt aError);

         /**
          * Protected method derived from MVideoPlayerUtilityObserver
          * @aError Error returned 
          */           
         
         void MvpuoPlayComplete(TInt aError);
         /**
          * Protected method derived from MVideoPlayerUtilityObserver
          * @aError Error returned 
          */           
 
         void MvpuoEvent(const TMMFEvent& aEvent);
    private:
        /**
         * Constructor
         */           
        
        CVideoResolution();
        /**
         * Two phase construction
         * @aUrl Url of the video file
         */           

        void ConstructL(TDesC& aUrl);
        
    private:
        
        /**
         * Pointer to  CMediaContainer
         */           
        
        CMediaContainer* iMediaContainer;
        /**
         * Pointer to  CVideoPlayerUtility
         */     
        CVideoPlayerUtility* iVideoUtility ;
        /**
         * Video filepath
         */    
        HBufC* iVideoFilePath;
        /**
         * Error
         */    
        TInt iErr;
    
    };


#endif /* MGVIDEORESOLUTION_H_ */
