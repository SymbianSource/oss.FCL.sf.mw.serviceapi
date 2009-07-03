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
* Description:  This Class provides the interface for
*				 calling the functionality to Application Manager SAPI
*  Interface
*
*/


#include <ecom/implementationproxy.h>
#include <utf.h>

#include "appmanagerservicehandler.h"
#include "appmanagerinterface.h"
#include "serviceerrno.h"
#include "appserviceerrmsg.hrh"

//Input Keys
_LIT8(KAppManager, "IAppManager");

//Output Keys/arguments
_LIT8(KErrorCode,"ErrorCode");
_LIT8(KCommand, "cmd");

// -----------------------------------------------------------------------------
// CAppManagerServiceHandler::NewL
// Returns the instance of CAppManagerServiceHandler
// -----------------------------------------------------------------------------

CAppManagerServiceHandler* CAppManagerServiceHandler::NewL()
    {
    return new ( ELeave ) CAppManagerServiceHandler();
    }

// -----------------------------------------------------------------------------
// CAppManagerServiceHandler::~CAppManagerServiceHandler
// Class destructor
// -----------------------------------------------------------------------------

CAppManagerServiceHandler::~CAppManagerServiceHandler()
    {
    }

// -----------------------------------------------------------------------------
// CAppManagerServiceHandler::InitialiseL
// Initialises provider with necessary information
// -----------------------------------------------------------------------------

void CAppManagerServiceHandler::InitialiseL(MLiwNotifyCallback& /*aFrameworkCallback*/,
                    const RCriteriaArray& /*aInterest*/)
    {

    }

// -----------------------------------------------------------------------------
// CAppManagerServiceHandler::HandleServiceCmdL
// Executes generic service commands included in criteria.
// -----------------------------------------------------------------------------
void CAppManagerServiceHandler::HandleServiceCmdL(const TInt& aCmdId,
                    const CLiwGenericParamList& aInParamList,
                    CLiwGenericParamList& aOutParamList,
                    TUint aCmdOptions,
                    const MLiwNotifyCallback* aCallback)
    {
    if( ( aCallback ) ||  ( 0 != aCmdOptions  ) )
  	    {
  	      // report error if request is anything other than synchronous
  	      //or user sends a callback parameter
  	    aOutParamList.AppendL(TLiwGenericParam( KErrorCode , TLiwVariant( TInt32( SErrServiceNotSupported ) ) ) );
  	    // return from function
  	    return;
  	    }

  	TPtrC8 cmdName;
    const TLiwGenericParam* cmd = NULL;

	if ( aCmdId == KLiwCmdAsStr )
	    {
        TInt pos = 0;
        cmd = aInParamList.FindFirst( pos, KCommand );
     	if ( NULL != cmd )
     	    {
       	    cmdName.Set( cmd->Value().AsData() );
       	    }
       	else
       	    {
       	     aOutParamList.AppendL(
  	         TLiwGenericParam( KErrorCode, TLiwVariant( TInt32( SErrServiceNotSupported ) ) ) );
  	         aOutParamList.AppendL(TLiwGenericParam( KErrorMsg, TLiwVariant( KInterfaceNameMissing ) ) );
       	    }
        }
    else
        {
         aOutParamList.AppendL(
         TLiwGenericParam(KErrorCode, TLiwVariant( TInt32( SErrServiceNotSupported ) ) ) );
        }


    if( 0 == cmdName.CompareF( KAppManager ) )
        {
        //Create interface pointer and return the output param
        CAppManagerInterface* ifp =CAppManagerInterface::NewL();
        CleanupClosePushL( *ifp );
        aOutParamList.AppendL( TLiwGenericParam(KAppManager, TLiwVariant( ifp ) ) );
        CleanupStack::Pop( ifp );
        return;
        }
     else
        {
         aOutParamList.AppendL(
  	     TLiwGenericParam( KErrorCode, TLiwVariant( TInt32( SErrServiceNotSupported ) ) ) );
  	     
  	     aOutParamList.AppendL(TLiwGenericParam( KErrorMsg, TLiwVariant( KInterfaceNotSupported ) ) );
        }
    }

//
// Rest of the file is for ECom initialization.
//

// Map the interface UIDs to implementation factory functions
const TImplementationProxy ImplementationTable[] =
    {
    IMPLEMENTATION_PROXY_ENTRY(0x2000CFB9, CAppManagerServiceHandler::NewL)
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
