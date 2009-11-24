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
* Description:  This class provides the interface for calling 
*                the functionalities of ServiceRegistry SAPI.
*
*/


#include <ecom/implementationproxy.h>
#include "serviceregistryservicehandler.h"
// Including a copy of common constants for this compilation unit
#include "serviceregistryservice.hrh"

#include "serviceinterface.h"

// -----------------------------------------------------------------------------
// CServiceRegistryServiceHandler::NewL
// Returns the instance of CServiceRegistryServiceHandler
// -----------------------------------------------------------------------------
//
CServiceRegistryServiceHandler* CServiceRegistryServiceHandler::NewL()
    {
    return new( ELeave ) CServiceRegistryServiceHandler;
    }

// -----------------------------------------------------------------------------
// CServiceRegistryServiceHandler::~CServiceRegistryServiceHandler
// Class destructor
// -----------------------------------------------------------------------------
//
CServiceRegistryServiceHandler::~CServiceRegistryServiceHandler()
    {
    }

// -----------------------------------------------------------------------------
// CServiceRegistryServiceHandler::InitialiseL
// Initializes provider with necessary information
// -----------------------------------------------------------------------------
//
void CServiceRegistryServiceHandler::InitialiseL(MLiwNotifyCallback& /*aFrameworkCallback*/,
                    const RCriteriaArray& /*aInterest*/)
    {
    // Domain Specific Initialization
    }

// -----------------------------------------------------------------------------
// CServiceRegistryServiceHandler::HandleServiceCmdL
// Executes generic service commands included in criteria.
// -----------------------------------------------------------------------------
//
void CServiceRegistryServiceHandler::HandleServiceCmdL(const TInt& aCmdId,
                    const CLiwGenericParamList& aInParamList,
                    CLiwGenericParamList& aOutParamList,
                    TUint aCmdOptions,
                    const MLiwNotifyCallback* aCallback)
    {
    if( ( aCallback ) ||  ( 0 != aCmdOptions  ) )
        {        
        aOutParamList.AppendL( TLiwGenericParam( KErrorCode , TLiwVariant( KErrNotSupported ) ) );
        // return from function
        return;
        }

    TPtrC8 cmdName;
    TLiwGenericParam cmd;

    if ( aCmdId == KLiwCmdAsStr )
        {
        TInt pos(0);
        aInParamList.FindFirst( pos, KCommand );
        if ( pos >= 0 )
            {
            cmd = aInParamList[pos];
            cmdName.Set( cmd.Value().AsData() );
            }
        else
            {            
            aOutParamList.AppendL( TLiwGenericParam(
                    KErrorCode, TLiwVariant( KErrArgument ) ) );
            return;
            }
        }
    else
        {        
        aOutParamList.AppendL( TLiwGenericParam(
                KErrorCode, TLiwVariant( KErrNotSupported ) ) );
        return;
        }

     // Resolving the requested interface
    if ( cmdName.CompareF( KService ) == 0 )
        {
        //Create interface pointer and return the output param
        CServiceInterface* ifp = CServiceInterface::NewL();
        CleanupClosePushL( *ifp );
        aOutParamList.AppendL( TLiwGenericParam( KService, TLiwVariant( ifp ) ) );
        CleanupStack::Pop( ifp );
        return;
        }
    else
        {        
        aOutParamList.AppendL(
                TLiwGenericParam( KErrorCode, TLiwVariant( KErrNotSupported ) ) );
        }    
    }

//
// Rest of the file is for ECom initialization.
//

// Map the interface UIDs to implementation factory functions

const TImplementationProxy ImplementationTable[] =
    {
    IMPLEMENTATION_PROXY_ENTRY(0x20022EE5, CServiceRegistryServiceHandler::NewL)
    };

// ---------------------------------------------------------
// Exported proxy for instantiation method resolution
// ---------------------------------------------------------
//
EXPORT_C const TImplementationProxy* ImplementationGroupProxy( TInt& aTableCount )
    {
    aTableCount = sizeof( ImplementationTable ) / sizeof( TImplementationProxy );
    return ImplementationTable;
    }
