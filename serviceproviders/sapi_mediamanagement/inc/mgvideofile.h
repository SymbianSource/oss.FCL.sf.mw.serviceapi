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
* Description:  Contains functionality specific to video files
*
*/


#ifndef __CMGVIDEOFILE_H
#define __CMGVIDEOFILE_H

#include <e32std.h>

#include "mgmediaitem.h"

class MCLFItem;
class CLiwDefaultMap;

/**
 *  This class is responsible for obtaining those parameters	
 *  which are specific to video files
 *
 *  
 *  @since Series60 v3.2
 */
NONSHARABLE_CLASS( CMgVideoFile ) : public CMgMediaItem
    {

public:

    /**
     * Two-phased constructor.
     * @return A pointer to CMgVideoFile class
     */
    static CMgVideoFile* NewL();
    
    /**
    * Destructor.
    */
    CMgVideoFile(){};

// from base class CMgMediaItem
    /**
     * This is responsible for filling only video file 
     * specific information
     * @param aOutputMap Contains the result in the form of 
     * name-value pairs
     * @param aClfItem A reference to the list model item to be processed
     * @return void
     */
    void FillInfoL( CLiwDefaultMap *aOutputMap, const MCLFItem& aClfItem );

    
    };

#endif // __CMGVIDEOFILE_H