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
* Description:   Holds information common to all media types
*
*/



#include <MCLFItem.h>
#include <pathinfo.h>
#include <liwvariant.h>


#include "mgmediaitem.h"

// Keys // used by service class and iterator
_LIT8( KMgFileName, "FileName" );
_LIT8( KMgFileExtension, "FileExtension" );
_LIT8( KMgDrive, "Drive" );
_LIT8( KMgFileSize, "FileSize" );
_LIT8( KMgFileDate, "FileDate" );
_LIT8( KMgMediaType, "MediaType" );
_LIT8( KMgMimeType, "MimeType" ); 


_LIT(EMgPhoneMemory,"C:");
_LIT(EMgMmc,"E:");
// ---------------------------------------------------------------------------
// CMgMediaItem::FillCommonAttributes
// Fills the attributes common to all media types
// ---------------------------------------------------------------------------
//

void CMgMediaItem::FillCommonAttributes(CLiwDefaultMap* aOutputMap, const MCLFItem& aClfItem) 
    {
    TPtrC fullName; 
    TPtrC name;
    TPtrC ext;
    TTime time;
    TBuf<2> memory;
    TInt32 size;
    TPtrC mimeType;
    TInt32 mediaType;
    if( aClfItem.GetField( ECLFFieldIdFileNameAndPath, fullName )
                                                        == KErrNone )
        {
        name.Set( TParsePtrC( fullName ).Name() );
        ext.Set( TParsePtrC( fullName ).Ext() ); 
        if( fullName.Length() > 0 )
            {
            TCharF mmcMemory( PathInfo::MemoryCardRootPath()[0] );
            TCharF itemPath( fullName[0] );
            if( mmcMemory == itemPath )
                { // by default phone memory
                memory = EMgMmc; 
                }
            else
                {
            	memory = EMgPhoneMemory;
                }
            }
        }
    aClfItem.GetField( ECLFFieldIdMimeType, mimeType );
    aClfItem.GetField( ECLFFieldIdFileSize, size );
    aClfItem.GetField( ECLFFieldIdFileDate, time );
    aClfItem.GetField( ECLFFieldIdMediaType, mediaType );  
    // insert all above attribute in map 
    aOutputMap->InsertL(KMgFileName,TLiwVariant(name));
    aOutputMap->InsertL(KMgFileExtension,TLiwVariant(ext));
    aOutputMap->InsertL(KMgDrive,TLiwVariant(memory));
    aOutputMap->InsertL(KMgMimeType,TLiwVariant(mimeType));
    aOutputMap->InsertL(KMgMediaType,TLiwVariant(mediaType));
    //aOutputMap->InsertL(KMgFileDate,TLiwVariant(time));
    aOutputMap->InsertL(KMgFileSize,TLiwVariant(size));
    
    }





