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
* Description:  Implements CLiwIterable type
*
*/


#include "appitemslist.h"
#include "appinfomap.h"
#include "appmanagerservice.h"



// ---------------------------------------------------------------------------
// CAppItemsList::CAppItemsList
// Parameterised constructor
// ---------------------------------------------------------------------------
//

CAppItemsList::CAppItemsList( MIterator* aIter)
              : iIter(aIter)
    {

    }
// ---------------------------------------------------------------------------
// CAppItemsList::NewL
// Two-phased constructor
// ---------------------------------------------------------------------------
//

CAppItemsList* CAppItemsList::NewL( MIterator* aIter )
    {
    return new( ELeave ) CAppItemsList( aIter );
    }


// ---------------------------------------------------------------------------
// CAppItemsList::~CAppItemsList
// Class destructor
// ---------------------------------------------------------------------------
//
CAppItemsList::~CAppItemsList()
    {
	delete iIter;
	}
// ---------------------------------------------------------------------------
// CAppItemsList::Reset
// Resets the iterator to point to the beginning of list
// ---------------------------------------------------------------------------
//

void CAppItemsList::Reset()
    {
    iIter->Reset();
    }


// ---------------------------------------------------------------------------
// CAppItemsList::NextL
// Constructs the next media item in the form of a map
// ---------------------------------------------------------------------------
//
TBool CAppItemsList::NextL( TLiwVariant& aItem )
    {

     MInfoMap* coremap = NULL;
     if ( iIter->NextL( coremap ) )
        {
        CAppInfoMap *outputMap = CAppInfoMap::NewL( coremap );
        CleanupClosePushL( *outputMap );
        aItem.SetL( TLiwVariant( outputMap ) );
        outputMap->DecRef();
        CleanupStack::Pop( outputMap );
        return ETrue;
        }
     else
        {
            return EFalse;
        }
  
    }





