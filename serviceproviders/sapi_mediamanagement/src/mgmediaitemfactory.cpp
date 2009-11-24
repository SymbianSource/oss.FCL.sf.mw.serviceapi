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
* Description:  Factory method for media types
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
// MgMediaItemFactory::NewMediaItemLC
// Checks the media type and returns an instance of the appropriate media item
// ---------------------------------------------------------------------------
//    
CMgMediaItem* MgMediaItemFactory::GetMediaItemL( const MCLFItem& aClfItem )
    {
    TInt32 data( 0 );
    CMgMediaItem* mediaItem = NULL;
    if( aClfItem.GetField( ECLFFieldIdMediaType, data ) == KErrNone )
        {
        switch ( data )
            {
            case ECLFMediaTypeStreamingURL:
                {
                mediaItem = CMgLinkFile::NewL();
                break;
                }
            case ECLFMediaTypeMusic:
                {
                mediaItem = CMgMusicFile::NewL();
                break;
                }
            case ECLFMediaTypeVideo:
                {
                mediaItem = CMgVideoFile::NewL();
                break;
                }
            default:
                {
                mediaItem = CMgMediaFile::NewL();
                break;
                }
            }
        }
    return mediaItem;
    }







