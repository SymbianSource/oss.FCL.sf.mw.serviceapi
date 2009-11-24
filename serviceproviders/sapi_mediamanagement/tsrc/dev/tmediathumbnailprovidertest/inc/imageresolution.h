/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
*/
/*
 * mgimageresolution.h
 *
 *  Created on: Mar 24, 2009
 *      Author: lgaur
 */

#ifndef MGIMAGERESOLUTION_H_
#define MGIMAGERESOLUTION_H_

#include<e32base.h>
#include<imageconversion.h>
#include<icl/imagedata.h>
#include<f32file.h>





class CImageResolution : public CBase
    {
    public:
       static  CImageResolution* NewL(TDesC& aUrl);
       TBool getresolutionL(TSize& aSize);
       ~CImageResolution();

    private:
        void ConstructL(TDesC& aUrl);
        CImageResolution();
    
    private:        
        CImageDecoder* iImageDecoder;
        TFrameInfo iFrameInfo;
        RFs iFs;
        RFile iFile;
    };


#endif /* MGIMAGERESOLUTION_H_ */
