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
* Description:  This class contains functions for populating link files
*                 with appropriate data
*
*/


#ifndef __CMGLINKFILE_H
#define __CMGLINKFILE_H

#include "mgmediaitem.h"

class MCLFItem;
/**
 *  This class contains functions for populating link files with 
 *  appropriate data
 *
 *  
 *  @since  Series60 v3.2
 */
 
NONSHARABLE_CLASS( CMgLinkFile ) : public CMgMediaItem
    {

public:

    /**
     * Two-phased constructor.
     * 
     */
    static CMgLinkFile* NewL();
    
    /**
    * Destructor.
    */
    ~CMgLinkFile(){};
    
    // from base class CMediaItem
    /**
     * This is responsible for filling only linkfile 
     * specific information
     * @param  outputMap This contains the result in the 
     *         form of key-value pairs
     * @return void
     */
    void FillInfoL( CLiwDefaultMap *aOutputMap, const MCLFItem& aClfItem );

    };

#endif // __CMGLINKFILE_H
