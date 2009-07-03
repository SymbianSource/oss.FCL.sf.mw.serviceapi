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
* Description:   Contains functionality specific to link files
*
*/



#include <mclfitem.h>
#include <e32base.h>
#include <liwvariant.h>

#include "mglinkfile.h"


_LIT8( KMgLinkFirstURL, "LinkFirstURL" );

// ---------------------------------------------------------------------------
// 	CMgLinkFile::NewL
//  Two-phased constructor
// ---------------------------------------------------------------------------
//
 
CMgLinkFile* CMgLinkFile::NewL()
    {
    CMgLinkFile* self = new( ELeave ) CMgLinkFile();
    return self;
    }


// ---------------------------------------------------------------------------
// CMgLinkFile::FillInfo
// Fills the attributes specific to link files
// ---------------------------------------------------------------------------
//
void CMgLinkFile::FillInfo( CLiwDefaultMap *aOutputMap, const MCLFItem& aClfItem )
    {
    TPtrC firstUrl; // url of the link file
    FillCommonAttributes( aOutputMap, aClfItem );
    if( aClfItem.GetField( ECLFFieldIdRamLinkFirstURL, firstUrl ) != KErrNone )
        {
        firstUrl.Set( KNullDesC );
        }
    aOutputMap->InsertL(KMgLinkFirstURL,TLiwVariant( firstUrl ) );
    }

    








