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


#include "appinfomap.h"
#include "appmanagerservice.h"




// ---------------------------------------------------------------------------
// CAppInfoMap::NewL
// Two-phased constructor
// ---------------------------------------------------------------------------
//

CAppInfoMap* CAppInfoMap::NewL( MInfoMap* aMap )
    {
    return new( ELeave ) CAppInfoMap( aMap );
    }


// ---------------------------------------------------------------------------
// CAppInfoMap::~CAppInfoMap
// Class destructor
// ---------------------------------------------------------------------------
//
CAppInfoMap::~CAppInfoMap()
    {

	delete iMap;

	}
// ---------------------------------------------------------------------------
// CAppInfoMap::FindL
// ---------------------------------------------------------------------------

TBool CAppInfoMap::FindL(const TDesC8& aKey, TLiwVariant& aFndValue) const
    {
    
    
    TPtrC val;
    if ( iMap->FindL(aKey, val ) )
        {
        aFndValue.Set( val );
        return ETrue;
        }
    else
        {
         return EFalse;
        }
   
    }
 
// ---------------------------------------------------------------------------
// CAppInfoMap::Count
// ---------------------------------------------------------------------------
    
TInt CAppInfoMap::CAppInfoMap::Count() const 
    {
    return iMap->Count();
    }


// ---------------------------------------------------------------------------
// CAppInfoMap::InsertL
// ---------------------------------------------------------------------------
    
void CAppInfoMap::InsertL(const TDesC8& /*aKey*/, const TLiwVariant& /*aValue*/)
    {
        // Not Supported Right now.
        User::Leave( KErrNotSupported );
    }
    
    
// ---------------------------------------------------------------------------
// CAppInfoMap::Remove
// ---------------------------------------------------------------------------
    
void CAppInfoMap::Remove(const TDesC8& /* aKey */)
    {
        // Not Supported Right now.
    }    
    
    
// ---------------------------------------------------------------------------
// CAppInfoMap::Remove
// ---------------------------------------------------------------------------
    
TBool CAppInfoMap::operator==(const CLiwMap& /* aMap */) const
    {

        // Not Supported Right now.
        return ETrue ; 
    }    
    

    
// ---------------------------------------------------------------------------
// CAppInfoMap::AtL
// ---------------------------------------------------------------------------
    
TBool CAppInfoMap::AtL(TInt aIndex, TDes8& aFndKey) const
    {
    return iMap->AtL( aIndex, aFndKey );
    }  
    
    
    
    
  
// ---------------------------------------------------------------------------
// CAppInfoMap::CAppInfoMap
// Parameterised constructor
// ---------------------------------------------------------------------------
//

CAppInfoMap::CAppInfoMap( MInfoMap* aMap)
            : iMap(aMap)
    {

    }
  