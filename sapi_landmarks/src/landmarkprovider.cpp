/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  CLandmarkService class implementation
*
*/


#include <ecom/implementationproxy.h>
#include "landmarkprovider.h"
#include "landmarkinterface.h"
#include "landmarkliwparams.hrh"
#include "../../inc/serviceerrno.h"

//CONSTANTS
_LIT8(KCmdName,"cmd");
// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CLandmarkProvider::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CLandmarkProvider* CLandmarkProvider::NewL()
    {
      return new (ELeave) CLandmarkProvider();
    }

// -----------------------------------------------------------------------------
// CLandmarkProvider::CLandmarkProvider()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CLandmarkProvider :: CLandmarkProvider()
    {
    }

// -----------------------------------------------------------------------------
// CLandmarkProvider::~CLandmarkProvider()
// Destructor.
// -----------------------------------------------------------------------------
//
CLandmarkProvider :: ~CLandmarkProvider()
    {
    }

// -----------------------------------------------------------------------------
// CLandmarkProvider::InitialiseL(MLiwNotifyCallback& /*aFrameworkCallback*/,
//                                 const RCriteriaArray& aInterest)
// Called by the AIW framework to initialise provider with necessary information
// from the Service Handler.
// -----------------------------------------------------------------------------
//
void CLandmarkProvider::InitialiseL(MLiwNotifyCallback& /*aFrameworkCallback*/,
                                 const RCriteriaArray& /*aInterest*/)
    {
    }

// -----------------------------------------------------------------------------
// CLandmarkProvider::HandleServiceCmdL(const TInt& aCmdId,
//    const CLiwGenericParamList& aInParamList,
//    CLiwGenericParamList& aOutParamList,
//    TUint aCmdOptions,
//    const MLiwNotifyCallback* aCallback)
// Called by the AIW framework to initialise provider with necessary information
// from the Service Handler.
// -----------------------------------------------------------------------------
//
void CLandmarkProvider::HandleServiceCmdL( const TInt& aCmdId,
    const CLiwGenericParamList& aInParamList,
    CLiwGenericParamList& aOutParamList,
    TUint aCmdOptions,
    const MLiwNotifyCallback* /*aCallback*/ )
    {
    // Cancel bit must always be checked. Support can be implemented if necessary.
    if ( aCmdOptions & KLiwOptCancel )
        {
        return;
        }
    TPtrC8 CmdName;
    const TLiwGenericParam* cmd;
    if ( aCmdId == KLiwCmdAsStr )
        {
        TInt pos = 0;
        cmd = aInParamList.FindFirst(pos,KCmdName);
        if ( NULL != cmd )
            {
            CmdName.Set( cmd->Value().AsData() );
            }
        }
    if ( CmdName == KIDataSource )
        {
        //Create interface pointer and return the output param
        CLandmarkInterface* interface = CLandmarkInterface::NewL();
        CleanupClosePushL(*interface);
        TRAPD (err,interface->SetActiveL(aInParamList));
        if( err )
        	{
        	err = interface->SapiError(err);
        	}
        aOutParamList.AppendL(TLiwGenericParam(KErrorCode,TLiwVariant((TInt32)err)));
        if( SErrBadArgumentType == err )
        	{
        	aOutParamList.AppendL(TLiwGenericParam(KErrorMsg,TLiwVariant(KInvalidDbUri())));
        	}
        aOutParamList.AppendL(TLiwGenericParam(KIDataSource,TLiwVariant(interface)));
        CleanupStack::Pop(interface);
        }
    else
        {
        aOutParamList.AppendL(TLiwGenericParam(KErrorCode,TLiwVariant((TInt32)SErrMissingArgument)));
        aOutParamList.AppendL(TLiwGenericParam(KErrorMsg,TLiwVariant(KInterfaceMissing())));
        }
    }

//
// Rest of the file is for ECom initialization.
//

// Map the interface UIDs to implementation factory functions
const TImplementationProxy ImplementationTable[] =
    {
    IMPLEMENTATION_PROXY_ENTRY( 0x10282CF6, CLandmarkProvider::NewL )
    };

// ---------------------------------------------------------
// Exported proxy for instantiation method resolution
// ---------------------------------------------------------
//
EXPORT_C const TImplementationProxy* ImplementationGroupProxy( TInt& aTableCount )
    {
    aTableCount = sizeof(ImplementationTable) / sizeof(TImplementationProxy);
    return ImplementationTable;
    }
