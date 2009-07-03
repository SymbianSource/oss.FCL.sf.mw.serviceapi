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
* Description:  CSysInfoProvider class implementation
*
*/


#include <ecom/implementationproxy.h>

#include "sysinfoprovider.h"
#include "sysinfointerface.h"
#include "sysinfoaiwparams.hrh"
#include "errormsgs.h"
#include "../../inc/serviceerrno.h"

using namespace LIW ;
using namespace sysinfoaiwparams;
//CONSTANTS
_LIT8(KCmdName,"cmd");

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CSysInfoProvider::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CSysInfoProvider* CSysInfoProvider::NewL()
    {
    return new (ELeave) CSysInfoProvider();
    }

// -----------------------------------------------------------------------------
// CSysInfoProvider::CSysInfoProvider()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CSysInfoProvider :: CSysInfoProvider()
    {
    }

// -----------------------------------------------------------------------------
// CSysInfoProvider::~CSysInfoProvider()
// Destructor.
// -----------------------------------------------------------------------------
//
CSysInfoProvider :: ~CSysInfoProvider()
    {
    }

// -----------------------------------------------------------------------------
// CSysInfoProvider::InitialiseL(MLiwNotifyCallback& /*aFrameworkCallback*/,
//                                 const RCriteriaArray& aInterest)
// Called by the AIW framework to initialise provider with necessary information
// from the Service Handler.
// -----------------------------------------------------------------------------
//
void CSysInfoProvider::InitialiseL(MLiwNotifyCallback& /*aFrameworkCallback*/,
                                    const RCriteriaArray& /*aInterest*/)
    {
    }

// -----------------------------------------------------------------------------
// CSysInfoProvider::HandleServiceCmdL(const TInt& aCmdId,
//    const CLiwGenericParamList& aInParamList,
//    CLiwGenericParamList& aOutParamList,
//    TUint aCmdOptions,
//    const MLiwNotifyCallback* aCallback)
// Called by the AIW framework to initialise provider with necessary information
// from the Service Handler.
// -----------------------------------------------------------------------------
//
void CSysInfoProvider::HandleServiceCmdL( const TInt& aCmdId,
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
        CSysInfoInterface* interface = CSysInfoInterface::NewL();
        CleanupStack::PushL(interface);
        aOutParamList.AppendL(TLiwGenericParam(KErrorCode,
                                            TLiwVariant((TInt32)KErrNone)));
        aOutParamList.AppendL(TLiwGenericParam(KIDataSource,
                                            TLiwVariant(interface)));
        CleanupStack::Pop(interface);
        }
    else
        {
        aOutParamList.AppendL(TLiwGenericParam(KErrorCode,
                            TLiwVariant((TInt32)SErrServiceNotSupported)));
        aOutParamList.AppendL(TLiwGenericParam(KErrorMsg,
                                            TLiwVariant(KErrInterfaceNotSupported)));
        }
    }

//
// Rest of the file is for ECom initialization.
//

// Map the interface UIDs to implementation factory functions
const TImplementationProxy ImplementationTable[] =
    {
    IMPLEMENTATION_PROXY_ENTRY( 0x2000CFBF, CSysInfoProvider::NewL )
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
