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
* Description:  Contains functionality common to media files
*
*/


#include <mclfitem.h>
#include <liwvariant.h>

#include "mgmediafile.h"


// ---------------------------------------------------------------------------
// 	CMgMediaFile::NewL
//  Two-phased constructor
// ---------------------------------------------------------------------------
//
 
CMgMediaFile* CMgMediaFile::NewL()
    {
    
    return new( ELeave ) CMgMediaFile();
    
    }


// ---------------------------------------------------------------------------
// CMgMediaFile::FillInfoL
// Fills the attributes specific to image and sound files 
// ---------------------------------------------------------------------------
//

void CMgMediaFile::FillInfoL( CLiwDefaultMap *aOutputMap, const MCLFItem& aClfItem )
    {
    
    FillCommonAttributesL( aOutputMap, aClfItem );
    
    }








