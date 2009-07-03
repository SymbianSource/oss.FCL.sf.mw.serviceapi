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
* Description:   Contains functionality specific to playlist files
*
*/



#ifndef __CMGPLAYLISTFILE_H
#define __CMGPLAYLISTFILE_H

#include "mgmediaitem.h"

class MCLFItem;
/**
 *  This class is responsible for obtaining those parameters
 *  which are specific to playlist files
 *  
 *  @since S60 v3.2
 */
NONSHARABLE_CLASS( CMgPlaylistFile ) : public CMgMediaItem
    {

public:

    /**
     * Two-phased constructor.
     * @return A pointer to CMgPlaylistFile
     */
    static CMgPlaylistFile* NewL();
    
   /**
    * Destructor.
    */
    ~CMgPlaylistFile(){};

// from base class CMgMediaItem
   /**
     * This is responsible for filling only playlist file 
     * specific information
     * @param aOutputMap Contains the result in the form of 
     * name-value pairs
     * @param aClfItem A reference to the list model item to be processed
     * @return void
     */
    void FillInfo( CAiwDefaultMap *aOutputMap, const MCLFItem& aClfItem  );

   
    };

#endif // __CMGPLAYLISTFILE_H
