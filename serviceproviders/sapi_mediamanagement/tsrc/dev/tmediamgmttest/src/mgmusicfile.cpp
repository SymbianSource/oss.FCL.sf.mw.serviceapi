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
* Description:   Contains music file specific information
*
*/



#include <MCLFItem.h>

#include <liwgenericparam.h> 
#include "mgmusicfile.h"



_LIT8( KMgSongName, "SongName" );
_LIT8( KMgArtist, "Artist" );
_LIT8( KMgAlbum, "Album" );
_LIT8( KMgGenre, "Genre" );
_LIT8( KMgTrackNumber, "TrackNumber" );
_LIT8( KMgComposer, "Composer" );


const TInt KMGServiceMaxTIntLength = 11;

// ---------------------------------------------------------------------------
// CMgMusicFile::NewL
// Two-phased constructor
// ---------------------------------------------------------------------------
//
 
CMgMusicFile* CMgMusicFile::NewL()
    {
    CMgMusicFile* self = new( ELeave ) CMgMusicFile();
    return self;
    }


// ---------------------------------------------------------------------------
// CMgMusicFile::FillInfo
// Fills the attributes specific to music files
// ---------------------------------------------------------------------------
//
void CMgMusicFile::FillInfo( CLiwDefaultMap *aOutputMap, const MCLFItem& aClfItem  )
    {
    
    TPtrC artist; //  artist name 
    TPtrC songName; // songname
    TBuf<KMGServiceMaxTIntLength> trackNumber; // track number
    TPtrC album; // album of the song
    TPtrC genre; // song genre
    TPtrC composer; // song composer
    FillCommonAttributes( aOutputMap, aClfItem );    
    aClfItem.GetField( ECLFFieldIdArtist, artist );
    aClfItem.GetField( ECLFFieldIdSongName, songName );
    TInt32 trackNo( 0 );    
    if( KErrNone == aClfItem.GetField( ECLFFieldIdTrackNumber, trackNo ) )
        {
        trackNumber.Num( trackNo );
        }
    aClfItem.GetField( ECLFFieldIdAlbum, album );
    aClfItem.GetField( ECLFFieldIdGenre, genre );
    aClfItem.GetField( ECLFFieldIdComposer, composer );
    aOutputMap->InsertL( KMgArtist,TLiwVariant( artist ) );
    aOutputMap->InsertL( KMgSongName,TLiwVariant( songName) );
    aOutputMap->InsertL( KMgTrackNumber,TLiwVariant( trackNumber) );
    aOutputMap->InsertL( KMgAlbum,TLiwVariant( album) );
    aOutputMap->InsertL( KMgGenre,TLiwVariant( genre) );
    aOutputMap->InsertL( KMgComposer,TLiwVariant( composer) );
    }








