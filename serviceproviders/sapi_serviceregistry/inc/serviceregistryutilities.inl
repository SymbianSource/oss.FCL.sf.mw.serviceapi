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


#ifndef SERVICEREGISTRYUTILITIES_INL
#define SERVICEREGISTRYUTILITIES_INL

#include "serviceerrno.h"

// ======== THIS FILE IS GENERATED - DO NOT MODIFY!!! ========================

// ---------------------------------------------------------------------------
// TServiceRegistryUtilities::TServiceRegistryUtilities
// Constructor.
// ---------------------------------------------------------------------------
//
inline TServiceRegistryUtilities::TServiceRegistryUtilities()
    {
    }
    
// -----------------------------------------------------------------------------
// TServiceRegistryUtilities::GetSapiErrorCode
// Returns the Sapi Error Code.
// -----------------------------------------------------------------------------
//
inline SapiErrors TServiceRegistryUtilities::GetSapiErrorCode( TInt aError )
    {
    SapiErrors err;
    switch( aError )
        {
            case KErrCancel:
                            err = SErrCancelSuccess;
                            break;
                            
            case KErrNone:
                            err= SErrNone;
                            break;

            case KErrNotFound:
                            err= SErrNotFound;
                            break;

            case KErrNoMemory:
                            err = SErrNoMemory;
                            break;

            case KErrInUse:
                            err = SErrServiceInUse;
                            break;

            case KErrNotSupported:
                            err = SErrServiceNotSupported;
                            break;

            case KErrBadName:
                            err = SErrBadArgumentType;
                            break;

            case KErrArgument: 
                            err = SErrInvalidServiceArgument;
                            break;

            case KErrNotReady: 
                            err = SErrServiceNotReady;
                            break;

            case KErrHardwareNotAvailable: 
                            err = SErrHardwareNotAvailable;
                            break;

			// These fallbacks make it possible to return service errors inside provider.
            case SErrInvalidServiceArgument:
            case SErrUnknownArgumentName:
            case SErrBadArgumentType:
            case SErrMissingArgument:
            case SErrServiceNotSupported:
            case SErrServiceInUse:
            case SErrServiceNotReady:
            case SErrNoMemory:
            case SErrHardwareNotAvailable:
            case SErrServerBusy:
            case SErrEntryExists:
            case SErrAccessDenied:
            case SErrNotFound:
            case SErrUnknownFormat:
            case SErrGeneralError:
            case SErrCancelSuccess:
            case SErrServiceTimedOut:
                            err = (SapiErrors)aError;
                            break;
        
            default         :
                            err = SErrGeneralError;
                            break;
        }

        return err;    
    }

#endif // SERVICEREGISTRYUTILITIES_INL

// ======== THIS FILE IS GENERATED - DO NOT MODIFY!!! ========================
