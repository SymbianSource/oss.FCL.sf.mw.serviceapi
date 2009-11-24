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



#include <ecom/implementationproxy.h>

#include "calendarinterface.h"
#include "calendarservicehandler.h"
#include "serviceerrno.h"
#include "calendarconstants.h"

using namespace LIW;

_LIT8(KCalendarInterface,	"IDataSource");
_LIT8(KCalendarService,		"Service.Calendar");
_LIT8(KCommand,	"cmd");

// ---------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------
//
CCalendarServiceHandler* CCalendarServiceHandler::NewL()
	{
	return new(ELeave) CCalendarServiceHandler();
	}

// ---------------------------------------------------------
// Constructor.
// ---------------------------------------------------------
//
CCalendarServiceHandler::CCalendarServiceHandler()
	{
	}

// ---------------------------------------------------------
// Called by the LIW framework to initialise necessary information 
// from the Service Handler. This method is called when the consumer makes 
//the attach operation.
// ---------------------------------------------------------
//
void CCalendarServiceHandler::InitialiseL( 
		MLiwNotifyCallback& /*aFrameworkCallback*/, 
		const RCriteriaArray& aInterest)
	{
	TInt count = aInterest.Count();
	for(TInt index = 0; index < count ; index++)
		{
		if(aInterest[index]->ContentType() == KCalendarService)
			return;
		}

	User::Leave( SErrNotFound );
	}

// ---------------------------------------------------------
// Executes generic service commands included in criteria
// ---------------------------------------------------------
//
void CCalendarServiceHandler::HandleServiceCmdL( 
		const TInt& aCmdId, 
		const CLiwGenericParamList& aInParamList,
		CLiwGenericParamList& aOutParamList,
		TUint /*aCmdOptions*/,
		const MLiwNotifyCallback* /*aCallback*/)
	{
	TPtrC8 cmdName;
	TPtrC errmsg(KNullDesC);

	if ( aCmdId == KLiwCmdAsStr )
		{
		TInt pos = 0;
		const TLiwGenericParam* cmd = aInParamList.FindFirst( pos, KCommand );
		if ( cmd )
			{
			cmdName.Set(cmd->Value().AsData());
			}
       	else
       	    {
       	     errmsg.Set(_L("Calendar:Interface name missing"));
       	     aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,TLiwVariant(errmsg)));
       	     aOutParamList.AppendL(TLiwGenericParam( KErrorCode, TLiwVariant( TInt32( SErrInvalidServiceArgument ) ) ) );
       	    }
		}

	if ( cmdName == KCalendarInterface )
		{
		CCalendarInterface* calInterface = CCalendarInterface::NewL();
		CleanupStack::PushL( calInterface );
		aOutParamList.AppendL(TLiwGenericParam(KCalendarInterface, TLiwVariant(calInterface)));
		CleanupStack::Pop( calInterface );
		}
	else
		{
		aOutParamList.AppendL(TLiwGenericParam(KErrorCode, TLiwVariant((TInt32)SErrInvalidServiceArgument)));
		aOutParamList.AppendL(TLiwGenericParam( KErrorMessage, 
										TLiwVariant(_L("Calendar:Interface not supported"))));		
		}
	}

// ---------------------------------------------------------
// Map the interface UIDs to implementation factory functions
// ---------------------------------------------------------
//
const TImplementationProxy ImplementationTable[] =
    {
        IMPLEMENTATION_PROXY_ENTRY(0x2000CFBD, CCalendarServiceHandler::NewL)
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
