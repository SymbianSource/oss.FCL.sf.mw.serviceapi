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
* Description:  
*				
*
*/

#include"mgimageresolution.h"


// -----------------------------------------------------------------------------
// CImageResolution::NewL
// Returns the instance of CImageResolution.
// -----------------------------------------------------------------------------
 CImageResolution* CImageResolution::NewL(TDesC& aUrl)
    {
    CImageResolution* self = new(ELeave)CImageResolution();
    CleanupStack::PushL(self);
    self->ConstructL(aUrl);
    CleanupStack::Pop(self);
    return self;
    }
 
 // -----------------------------------------------------------------------------
 // CImageResolution::ConstructL
 // Symbian C++ constructor
 // -----------------------------------------------------------------------------
 
 void CImageResolution::ConstructL(TDesC& aUrl)
     {
     User::LeaveIfError(iFs.Connect());
     
     User::LeaveIfError(iFile.Open(iFs,aUrl,EFileRead));
     
     iImageDecoder = CImageDecoder::FileNewL(iFile ,ContentAccess::EPeek );
     
     }
 
 // -----------------------------------------------------------------------------
 // CImageResolution::CImageResolution
 // C++ constructor
 // -----------------------------------------------------------------------------
 
 CImageResolution::CImageResolution():iImageDecoder(NULL)
     {
     // reset frame info
     iFrameInfo.iBitsPerPixel = 0;
     iFrameInfo.iFlags = 0;
     iFrameInfo.iOverallSizeInPixels = TSize( 0, 0 );    
     }
 
 // -----------------------------------------------------------------------------
 // CImageResolution::CImageResolution
 // Destructor
 // -----------------------------------------------------------------------------
  CImageResolution::~CImageResolution()
     {
     iFile.Close();
     iFs.Close();
     if(iImageDecoder)
         {
         delete iImageDecoder;
         }
     }
  // -----------------------------------------------------------------------------
  // CImageResolution::GetresolutionL
  // This method gets the resolution of image
  // ----------------------------------------------------------------------------- 
  EXPORT_C  TBool CImageResolution::GetresolutionL(TSize& aSize)
      {
      iFrameInfo = iImageDecoder->FrameInfo();
      
      aSize.iWidth  = iFrameInfo.iOverallSizeInPixels.iWidth;
      aSize.iHeight = iFrameInfo.iOverallSizeInPixels.iHeight;
      
      if(aSize == TSize(0,0))
          {
          return false;
          }
      
      return true;
      
      }
