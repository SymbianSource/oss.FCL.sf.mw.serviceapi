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
* Description:  This Class is used to find resolution of image file
*
*/

#ifndef MGIMAGERESOLUTION_H_
#define MGIMAGERESOLUTION_H_

#include<e32base.h>
#include<imageconversion.h>
#include<icl/imagedata.h>
#include<f32file.h>


#include"mgmresolution.h"

// CLASS DECLARATION

/**
*  CImageResolution class This class can be used to find the resolution of image file
*
*  @since  Series60 v3.2
*/
class CImageResolution : public CBase , public MResolution
    {
    public:
        
        /**
        * Two-phased constructor
        * @since  Series60 v3.2
        * @param  aUrl   Url of the image file
        * @return CImageResolution*  Returns the instance of
        *                                 CImageResolution.
        */        
       static  CImageResolution* NewL(TDesC& aUrl);
       
       /**
       * Method to get resolution of image file
       * @since  Series60 v3.2
       * @param  aSize In return it contains size of image file
       * @return TBool ETrue when it is able to get resolution of image else EFalse
       *               
       */        
       TBool GetresolutionL(TSize& aSize);
       /**
        * Destructor
        */        
       ~CImageResolution();

    private:
        /**
         * Symbian ConstructL
         * @since  Series60 v3.2
         * @param  aUrl Url of the image file
         * 
         */        

        void ConstructL(TDesC& aUrl);
        /**
        * C++ constructor
        */    
        CImageResolution();
    
    private:        
        /**
        * Image decoder instance
        */    
  
        CImageDecoder* iImageDecoder;
        /**
        * TFrameInfo instance
        */    

        TFrameInfo iFrameInfo;
        /**
        * File server session
        */    

        RFs iFs;
        /**
        * RFile instance
        */    
        
        RFile iFile;
    };


#endif /* MGIMAGERESOLUTION_H_ */
