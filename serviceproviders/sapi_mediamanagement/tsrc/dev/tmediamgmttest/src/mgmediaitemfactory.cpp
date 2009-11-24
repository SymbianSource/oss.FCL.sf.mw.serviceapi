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
* Description:   Factory method for media types
*
*/



#include <e32base.h>
#include <MCLFItem.h>
 
#include "mgmediaitemfactory.h"
#include "mglinkfile.h"
#include "mgmusicfile.h"
#include "mgvideofile.h"
#include "mgmediaitem.h"
#include "mgmediafile.h"

// ---------------------------------------------------------------------------
// CMgMediaItemFactory::NewL
// Two-phased constructor
// ---------------------------------------------------------------------------
//
 
CMgMediaItemFactory* CMgMediaItemFactory::NewL()
    {
    CMgMediaItemFactory* self = new( ELeave ) CMgMediaItemFactory;
    return self;
    }

// ---------------------------------------------------------------------------
// CMgMediaItemFactory::GetMediaItem
// Returns a pointer to an appropriate media type 
// ---------------------------------------------------------------------------
//
    
CMgMediaItem* CMgMediaItemFactory::GetMediaItemL( const MCLFItem& aClfItem )
    {
    CMgMediaItem* mediaItem = NewMediaItemL( aClfItem );
    return mediaItem;
    }
// ---------------------------------------------------------------------------
// CMgMediaItemFactory::NewMediaItemLC
// Checks the media type and returns an instance of the appropriate media item
// ---------------------------------------------------------------------------
//    
CMgMediaItem* CMgMediaItemFactory::NewMediaItemL( const MCLFItem& aClfItem )
    {
    TInt32 data( 0 );
    if( aClfItem.GetField( ECLFFieldIdMediaType, data ) == KErrNone )
        {
        switch ( data )
            {
            case ECLFMediaTypeStreamingURL:
                {
                return CMgLinkFile::NewL();
                }
            case ECLFMediaTypeMusic:
                {
                return CMgMusicFile::NewL();
                }
            case ECLFMediaTypeVideo:
                {
                return CMgVideoFile::NewL();
                }
            default:
                {
                return CMgMediaFile::NewL();
                }
            }
        }
    return NULL;
    }







