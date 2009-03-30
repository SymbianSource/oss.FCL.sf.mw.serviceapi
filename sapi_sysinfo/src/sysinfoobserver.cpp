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
* Description:  CSysInfoObserver class implementation
*
*/


// INCLUDE FILES
#include <liwgenericparam.h>
#include <liwcommon.h>

#include "sysinfointerface.h"
#include "sysinfoobserver.h"
#include "../../inc/serviceerrno.h"
#include "sysinfoaiwparams.hrh"

using namespace LIW;
using namespace sysinfoaiwparams;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CSysInfoObserver::NewL( CSysInfoInterface* aSysInfoIf )
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CSysInfoObserver* CSysInfoObserver::NewL( CSysInfoInterface* aSysInfoIf )
    {
    CSysInfoObserver* self = new (ELeave) CSysInfoObserver(aSysInfoIf);
    return self;
    }

// -----------------------------------------------------------------------------
// CSysInfoObserver::CSysInfoObserver( CSysInfoInterface* aSysInfoIf )
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CSysInfoObserver::CSysInfoObserver( CSysInfoInterface* aSysInfoIf )
                                                :iSysInfoIf(aSysInfoIf)
    {
    }

// -----------------------------------------------------------------------------
// CSysInfoObserver::HandleResponseL( const TDesC& aEntity,const TDesC& aKey, 
// 		CSysData* aOutput, TInt32 aTransID,TInt aError) 
// Pack the outputs and call the callback function.
// -----------------------------------------------------------------------------
//
void CSysInfoObserver::HandleResponseL(const TDesC& aEntity,const TDesC& aKey, 
                                            CSysData* aOutput, TInt32 aTransID, 
                                            TSysRequest::TRequestType aType,
                                            TInt aError )
    {
    TInt SapiErr = SErrNone;
    TBool ownership(EFalse);
    MLiwNotifyCallback* callback=NULL;
    //retrieve callback
    if( TSysRequest::EASyncONESHOT == aType )
        callback = iSysInfoIf->GetCallbackAndRemove(aTransID);
    else
        callback = iSysInfoIf->GetCallback(aTransID);

    if( !callback )
        {
        delete aOutput;
        return;
        }

    //Create param list
    CLiwGenericParamList* eventParamList = CLiwGenericParamList::NewL();
    CleanupStack::PushL(eventParamList);
    CLiwGenericParamList* inParamList = CLiwGenericParamList::NewL();
    CleanupStack::PushL(inParamList);

    if ( aError != KErrNone )
        {
        SapiErr = iSysInfoIf->SapiError(aError);
        eventParamList->AppendL(TLiwGenericParam(KErrorCode,TLiwVariant(SapiErr)));
        TRAP_IGNORE(callback->HandleNotifyL(aTransID, KLiwEventError,
                                        *eventParamList,*inParamList));
        }
    else
        {
        //pack to aOutParamList
        eventParamList->AppendL(TLiwGenericParam(KErrorCode,TLiwVariant((TInt32)SapiErr)));
        CLiwMap* outparam=NULL;

        if( (aOutput->DataType() == CSysData::EAccessoryList) ||
                (aOutput->DataType() == CSysData::EConnectionList) )
            ownership = ETrue;

        CSysInfoInterface::ConvertSysData2AiwParamL(aOutput,outparam);
        //Add Entity and Key to the output map.
        if(outparam)
            {
            outparam->InsertL(KEntity,TLiwVariant(aEntity));
            outparam->InsertL(KKey,TLiwVariant(aKey));
            }

        eventParamList->AppendL(TLiwGenericParam(KReturnValue,TLiwVariant(outparam)));
        outparam->DecRef();
        if( TSysRequest::EASyncONESHOT == aType )
            {
            TRAP_IGNORE(callback->HandleNotifyL(aTransID, KLiwEventCompleted,
                                            *eventParamList,*inParamList));
            }
        else
            {
            TRAP_IGNORE(callback->HandleNotifyL(aTransID, KLiwEventInProgress,
                                            *eventParamList,*inParamList));
            }

        if(!ownership)
            {
            delete 	aOutput;
            aOutput = NULL;
            }
        }
    CleanupStack::PopAndDestroy(inParamList);
    CleanupStack::PopAndDestroy(eventParamList);
    }

//End of file


