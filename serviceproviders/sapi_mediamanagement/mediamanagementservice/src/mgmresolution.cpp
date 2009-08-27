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
* Description:  This Class is interface for media resolution class
*				
*
*/


#include"mgmresolution.h"
#include"mgimageresolution.h"
#include"mgvideoresolution.h"
_LIT(KImage,"image");
_LIT(KVideo,"video");

// -----------------------------------------------------------------------------
// MResolution::~MResolution
// Destructor
// -----------------------------------------------------------------------------
MResolution::~MResolution(){

}

// -----------------------------------------------------------------------------
// MediaResolutionFactory::CreateMediaResolutionobjL
// Factory method which gives instance of Resolution 
// -----------------------------------------------------------------------------


EXPORT_C MResolution* MediaResolutionFactory::CreateMediaResolutionobjL(TDesC& aMedia, TDesC& aUrl)
    {
   MResolution* object = NULL;
   
   if(aMedia.Compare(KImage)== 0)
       {
       object = CImageResolution::NewL(aUrl);
       }
   else if(aMedia.Compare(KVideo)== 0)
       {
       object = CVideoResolution::NewL(aUrl);
       }
    
    
   return object ; 
    
    }
