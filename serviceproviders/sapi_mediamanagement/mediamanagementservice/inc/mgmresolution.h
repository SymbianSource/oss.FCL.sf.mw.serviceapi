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
* Description:  This Class is interface for resoluion class
*
*/

#ifndef MGMRESOLUTION_H_
#define MGMRESOLUTION_H_
#include<e32cmn.h>


/**
*  MResolution class This class is an interface class from which image and video resolution classes are derived  
*
*  @since  Series60 v3.2
*/
class MResolution
    {
    public:
    /**
      * Method to gert resolution of media file
     * @param aSize  Returns the size of media file
      *@ return TBool If it gets the resolution then ETrue or else EFalse                                 
      */                 
               
        IMPORT_C virtual TBool GetresolutionL(TSize& aSize) = 0 ;
    public:

        /**
         * Destructor
          */                 
        
      virtual  ~MResolution();
    };


/**
*  MediaResolutionFactory class This is a factory class    
*
*  @since  Series60 v3.2
*/

class MediaResolutionFactory
    {
    public:
        IMPORT_C static MResolution* CreateMediaResolutionobjL(TDesC& aMedia, TDesC& aUrl);
    };





#endif /* MGMRESOLUTION_H_ */
