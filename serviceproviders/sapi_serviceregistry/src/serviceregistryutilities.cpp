/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Common utilities for ServiceRegistry Service API
*                THIS FILE IS GENERATED - DO NOT MODIFY!!!
*
*/


#include <liwcommon.h>

#include "serviceregistryutilities.h"
#include "serviceregistryservice.hrh"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// TServiceRegistryUtilities::ConvertInputInt32L
//  Converts LIW type input Int32 into Symbian type.
// ---------------------------------------------------------------------------
//
TInt32 TServiceRegistryUtilities::ConvertInputInt32L( const CLiwGenericParamList& aInParamList,
                                                const TDesC8& aName,                                                
                                                const TInt aParamIndex )
    {
    // Local parameter storage
    TLiwGenericParam inParam;
    // Storage for return value
    TInt32 retInt32( 0 );
    // Default start position for Find 
    TInt FindStartIndex = 0;
    // Get input parameter
    aInParamList.FindFirst( FindStartIndex, aName );
    if ( FindStartIndex < 0 )
        {
        // Using position based parsing, if param was not found by name.
        if ( aParamIndex != -1 && aInParamList.Count() > aParamIndex )
            {
            inParam = aInParamList[aParamIndex];
            }
        else
            {
            
            User::Leave( SErrMissingArgument );
            }
        }
    else
        {
        inParam = aInParamList[FindStartIndex];
        }
        
    // Check variant type
    if ( inParam.Value().TypeId() != LIW::EVariantTypeTInt32 )
        {
        
        User::Leave( SErrBadArgumentType );
        }
    inParam.Value().Get( retInt32 );
    return retInt32;
    }

