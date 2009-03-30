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
*				 calling the functionality to Media Management SAPI.
*  Interface
*
*/


#include <ecom/implementationproxy.h>
#include <utf.h>

#include "mgservicehandler.h"
#include "mginterface.h"
#include "serviceerrno.h"

//Input Keys
_LIT8(KDataSource, "IDataSource");

//Output Keys/arguments
_LIT8(KErrorCode,"ErrorCode");
_LIT8(KErrorMessage,"ErrorMessage");
_LIT8(KCommand, "cmd");

// -----------------------------------------------------------------------------
// CMgServiceHandler::NewL
// Returns the instance of CMgServiceHandler
// -----------------------------------------------------------------------------

CMgServiceHandler* CMgServiceHandler::NewL()
    {
    return new ( ELeave ) CMgServiceHandler();
    }

// -----------------------------------------------------------------------------
// CMgServiceHandler::~CMgServiceHandler
// Class destructor
// -----------------------------------------------------------------------------

CMgServiceHandler::~CMgServiceHandler()
    {
    }

// -----------------------------------------------------------------------------
// CMgServiceHandler::InitialiseL
// Initialises provider with necessary information
// -----------------------------------------------------------------------------

void CMgServiceHandler::InitialiseL(MLiwNotifyCallback& /*aFrameworkCallback*/,
                    const RCriteriaArray& /*aInterest*/)
    {

    }

// -----------------------------------------------------------------------------
// CMgServiceHandler::HandleServiceCmdL
// Executes generic service commands included in criteria.
// -----------------------------------------------------------------------------
void CMgServiceHandler::HandleServiceCmdL(const TInt& aCmdId,
                    const CLiwGenericParamList& aInParamList,
                    CLiwGenericParamList& aOutParamList,
                    TUint aCmdOptions,
                    const MLiwNotifyCallback* aCallback)
    {
    TPtrC errmsg(KNullDesC);
    if( ( aCallback ) ||  ( 0 != aCmdOptions  ) )
  	    {
         errmsg.Set(_L("MediaMgmt:Command not supported"));
         aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,TLiwVariant(errmsg)));

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
       	     errmsg.Set(_L("MediaMgmt:Interface name missing"));
       	     aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,TLiwVariant(errmsg)));
       	     aOutParamList.AppendL(
  	         TLiwGenericParam( KErrorCode, TLiwVariant( TInt32( SErrServiceNotSupported ) ) ) );
       	    }
        }
    else
        {
         errmsg.Set(_L("MediaMgmt:Command not supported"));
         aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,TLiwVariant(errmsg)));
         aOutParamList.AppendL(
         TLiwGenericParam(KErrorCode, TLiwVariant( TInt32( SErrServiceNotSupported ) ) ) );
        }


    if( 0 == cmdName.CompareF( KDataSource ) )
        {

        //Create interface pointer and return the output param
        CMgInterface* ifp =CMgInterface::NewL();
        CleanupClosePushL( *ifp );
        aOutParamList.AppendL( TLiwGenericParam(KDataSource, TLiwVariant( ifp ) ) );
        CleanupStack::Pop( ifp );
        return;
        }
     else
        {
        errmsg.Set(_L("MediaMgmt:Requested interface not supported by the provider"));
        aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,TLiwVariant(errmsg)));

           aOutParamList.AppendL(
  	       TLiwGenericParam( KErrorCode, TLiwVariant( TInt32( SErrServiceNotSupported ) ) ) );
  	       
        }
    }

//
// Rest of the file is for ECom initialization.
//

// Map the interface UIDs to implementation factory functions
const TImplementationProxy ImplementationTable[] =
    {
    IMPLEMENTATION_PROXY_ENTRY(0x10282CF8, CMgServiceHandler::NewL)
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
