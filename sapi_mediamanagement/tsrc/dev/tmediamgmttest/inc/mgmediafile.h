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
* Description:   Contains media file specific information
*
*/



#ifndef __CMGMEDIAFILE_H
#define __CMGMEDIAFILE_H

#include "mgmediaitem.h"

class MCLFItem;
/**
 *  This class is responsible for obtaining those parameters
 *  which are specific to media files
 *  
 *  @since Series60 v3.2
 */
NONSHARABLE_CLASS( CMgMediaFile ) : public CMgMediaItem
    {

public:

    /**
     * Two-phased constructor.
     * @param aCLFItem This function accepts a reference to MCLFItem
     */
    static CMgMediaFile* NewL();
    
    /**
    * Destructor.
    */
    ~CMgMediaFile(){};
    
// from base class CMediaItem
    /**
     * This is responsible for filling only mediafile 
     * specific information
     * @param outputMap Contains the result in the form of 
     * name-value pairs
     */
     
    void FillInfo( CLiwDefaultMap *aOutputMap, const MCLFItem& aClfItem );


    };

#endif // __CMGMEDIAFILE_H
