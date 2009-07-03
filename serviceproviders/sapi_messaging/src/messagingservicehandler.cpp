/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  
*
*/



#include <ecom/ImplementationProxy.h>

#include "messaginginterface.h"
#include "messagingservicehandler.h"
#include "serviceerrno.h"

using namespace LIW;

_LIT8(KMessagingInterface,	"IMessaging");
_LIT8(KMessagingService,	"Service.Messaging");
_LIT8(KCommand,	"cmd");
_LIT8( KErrorMessage1, "ErrorMessage"); 
_LIT( KInterfaceErrorMessage, "Invalid Interface"); 

// ---------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------
//
CMessagingServiceHandler* CMessagingServiceHandler::NewL()
	{
	return new(ELeave) CMessagingServiceHandler();
	}

// ---------------------------------------------------------
// Constructor.
// ---------------------------------------------------------
//
CMessagingServiceHandler::CMessagingServiceHandler()
	{
	}

// ---------------------------------------------------------
// Called by the LIW framework to initialise necessary information 
// from the Service Handler. This method is called when the consumer makes 
//the attach operation.
// ---------------------------------------------------------
//
void CMessagingServiceHandler::InitialiseL( 
		MLiwNotifyCallback& /*aFrameworkCallback*/, 
		const RCriteriaArray& aInterest)
	{
	TInt count = aInterest.Count();
	for(TInt index = 0; index < count ; index++)
		{
		if(aInterest[index]->ContentType() == KMessagingService)
			return;
		}

	User::Leave(SErrNotFound);
	}

// ---------------------------------------------------------
// Executes generic service commands included in criteria
// ---------------------------------------------------------
//
void CMessagingServiceHandler::HandleServiceCmdL( 
		const TInt& aCmdId, 
		const CLiwGenericParamList& aInParamList,
		CLiwGenericParamList& aOutParamList,
		TUint /*aCmdOptions*/,
		const MLiwNotifyCallback* /*aCallback*/)
	{
	TPtrC8 cmdName;
	
	if ( aCmdId == KLiwCmdAsStr )
		{
		TInt pos = 0;
		const TLiwGenericParam* cmd = aInParamList.FindFirst( pos, KCommand );
		if ( cmd )
			{
			cmdName.Set(cmd->Value().AsData());
			}
		}

	if ( cmdName == KMessagingInterface )
		{
		CMessagingInterface* msgInterface = CMessagingInterface::NewL();
		CleanupStack::PushL( msgInterface );
		aOutParamList.AppendL(TLiwGenericParam(KMessagingInterface, TLiwVariant(msgInterface)));
		CleanupStack::Pop( msgInterface );
		}
	else
		{
		aOutParamList.AppendL(TLiwGenericParam( KErrorMessage1, 
									TLiwVariant( KInterfaceErrorMessage.operator()() )));
		aOutParamList.AppendL(TLiwGenericParam(EGenericParamError, 
									TLiwVariant((TInt32)SErrInvalidServiceArgument)));
		}
	}

// ---------------------------------------------------------
// Map the interface UIDs to implementation factory functions
// ---------------------------------------------------------
//
const TImplementationProxy ImplementationTable[] =
    {
        IMPLEMENTATION_PROXY_ENTRY(0x10282CF9, CMessagingServiceHandler::NewL)
    };

// ---------------------------------------------------------
// Exported proxy for instantiation method resolution
// ---------------------------------------------------------
//
EXPORT_C const TImplementationProxy* ImplementationGroupProxy(TInt& aTableCount)
    {
    aTableCount = sizeof(ImplementationTable) / sizeof(TImplementationProxy);
    return ImplementationTable;
    }
