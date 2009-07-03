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


#ifndef SERVICEREGISTRYUTILITIES_H
#define SERVICEREGISTRYUTILITIES_H

#include "serviceerrno.h"


/**
 * Common utilities for HelloWorld Service API
 */
class TServiceRegistryUtilities
    {

public: // Construction

    /**
     * Constructor.
     */
    inline TServiceRegistryUtilities();

public: // Utility methods

    
    /**
     * Converts LIW type input Int32 into Symbian type.
     * @param aInParamList Input parameter list.
     * @param aName Parameter name.
     * @param aErrorMessage Reference to error message.
     * @param aParamIndex Index used to get value from aInParamList
     *        if name search fails.
     * @return Converted input string.
     */
    TInt32 ConvertInputInt32L( const CLiwGenericParamList& aInParamList,                                  
                              const TDesC8& aName,                              
                              const TInt aParamIndex = -1 );
    
    /**
     * Converts Symbian error code into Sapi error code.
     * Inlined in order to be accessible also from service side.
     * @param aError Symbian error code.
     * @return Corresponding SapiErrors
     */
    inline SapiErrors GetSapiErrorCode( TInt aError );
    
    };
        
// Including inline methods
#include "serviceregistryutilities.inl"

#endif // SERVICEREGISTRYUTILITIES_H

