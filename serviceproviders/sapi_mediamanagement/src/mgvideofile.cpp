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


#include <mclfitem.h>
#include <e32base.h>
#include <liwvariant.h>

#include "mgvideofile.h"

_LIT8( KMgSongName, "SongName" );
_LIT8( KMgArtist, "Artist" );

// ---------------------------------------------------------------------------
// CMgVideoFile::NewL
// Two-phased constructor
// ---------------------------------------------------------------------------
//
 
CMgVideoFile* CMgVideoFile::NewL()
    {
    return new( ELeave ) CMgVideoFile();
    }

// ---------------------------------------------------------------------------
// CMgVideoFile::FillInfoL
// Fills the attributes specific to video files 
// ---------------------------------------------------------------------------
//
void CMgVideoFile::FillInfoL( CLiwDefaultMap *aOutputMap, const MCLFItem& aClfItem )
    {
    TPtrC artist; //artist of video file
    TPtrC title; //title of video file
    
    FillCommonAttributesL( aOutputMap, aClfItem );
    
    aOutputMap->InsertL( KMgArtist,TLiwVariant( artist ) );
    aOutputMap->InsertL( KMgSongName,TLiwVariant( title ) );
    
    }








