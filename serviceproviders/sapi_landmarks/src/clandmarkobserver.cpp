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
* Description:  CLandmarkObserver class implementation
*
*/


// INCLUDE FILES
#include <liwgenericparam.h>
#include <liwcommon.h>
#include "clandmarkobserver.h"
#include "clandmarkiterable.h"
#include "clandmarkcategoryiterable.h"
#include "clandmarkmanagehandlers.h"
#include "landmarkinterface.h"
#include "landmarkliwparams.hrh"
#include "../../inc/serviceerrno.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CLandmarkObserver::NewL( CLandmarkInterface* aLmIface )
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CLandmarkObserver* CLandmarkObserver::NewL( CLandmarkInterface* aLmIface )
    {
    CLandmarkObserver* self = new (ELeave) CLandmarkObserver(aLmIface);
    return self;
    }

// -----------------------------------------------------------------------------
// CLandmarkObserver::CLandmarkObserver( CLandmarkInterface* aLmIface )
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CLandmarkObserver::CLandmarkObserver( CLandmarkInterface* aLmIface )
									: iLmIface(aLmIface)
    {
    }

CLandmarkObserver::~CLandmarkObserver()
	{
	delete iId;
	}
// -----------------------------------------------------------------------------
// CLandmarkObserver::HandleCategoryItems( CPosLmItemIterator* aIterator, 
// 		TInt32 aTransactionId, TInt aError, const TDesC aDatabaseUri )
// Pack the outputs and call the callback function.
// -----------------------------------------------------------------------------
//
void CLandmarkObserver::HandleLandmarkItemsL( CPosLmItemIterator* aIterator, 
		TInt32 aTransactionId, TInt aError, CLandmarkHandler* aHandler )
    {
    TInt SapiErr = SErrNone;
    //retrieve callback
    MLiwNotifyCallback* callback = iLmIface->Callback(aTransactionId);
    if( !callback )
    	{
    	//how to flag error
    	return;
    	}
    //Create param list
    CLiwGenericParamList* eventParamList = CLiwGenericParamList::NewL();
    CleanupStack::PushL(eventParamList);
    CLiwGenericParamList* inParamList = CLiwGenericParamList::NewL();
    CleanupStack::PushL(inParamList);
    
    if ( aError != KErrNone )
        {
        SapiErr = iLmIface->SapiError(aError);
        eventParamList->AppendL(TLiwGenericParam(KErrorCode,TLiwVariant((TInt32)SapiErr)));
        callback->HandleNotifyL(aTransactionId,KLiwEventError,*eventParamList,*inParamList);
        }
    else
    	{
    	//instantiate CLandmarkIterable
    	TPtrC dbUri;
    	aHandler->GetDatabaseUri (dbUri );
    	CLandmarkIterable* iterable = CLandmarkIterable::NewL(aIterator,dbUri);
        iterable->PushL();
        //pack to aOutParamList
        iterable->SetHandler(aHandler);
        eventParamList->AppendL(TLiwGenericParam(KErrorCode,TLiwVariant((TInt32)SapiErr)));
        eventParamList->AppendL(TLiwGenericParam(KReturnValue,TLiwVariant(iterable)));
        callback->HandleNotifyL(aTransactionId,KLiwEventCompleted,*eventParamList,*inParamList);
        CleanupStack::PopAndDestroy(iterable);
    	}
    CleanupStack::PopAndDestroy(inParamList);
    CleanupStack::PopAndDestroy(eventParamList);
    }

// -----------------------------------------------------------------------------
// CLandmarkObserver::HandleCategoryItems( CPosLmItemIterator* aIterator, 
// 		TInt32 aTransactionId, TInt aError, const TDesC aDatabaseUri  )
// Pack the outputs and call the callback function.
// -----------------------------------------------------------------------------
//
void CLandmarkObserver::HandleCategoryItemsL( CPosLmItemIterator* aIterator, 
		TInt32 aTransactionId, TInt aError, CLandmarkHandler* aHandler )
    {
    TInt SapiErr = SErrNone;
    //retrieve callback
    MLiwNotifyCallback* callback = iLmIface->Callback(aTransactionId);
    if( !callback )
    	{
    	//how to flag error
    	return;
    	}
    //Create param list
    CLiwGenericParamList* eventParamList = CLiwGenericParamList::NewL();
    CleanupStack::PushL(eventParamList);
    CLiwGenericParamList* inParamList = CLiwGenericParamList::NewL();
    CleanupStack::PushL(inParamList);
    
    if ( aError != KErrNone )
        {
        SapiErr = iLmIface->SapiError(aError);
        eventParamList->AppendL(TLiwGenericParam(KErrorCode,TLiwVariant((TInt32)SapiErr)));
        callback->HandleNotifyL(aTransactionId,KLiwEventError,*eventParamList,*inParamList);
        }
    else
    	{
    	//instantiate CLandmarkIterable
    	TPtrC dbUri;
        aHandler->GetDatabaseUri (dbUri );
        CLandmarkCategoryIterable* iterable = CLandmarkCategoryIterable::NewL(aIterator,dbUri);
        iterable->PushL();
        //pack to aOutParamList
        iterable->SetHandler(aHandler);
        eventParamList->AppendL(TLiwGenericParam(KErrorCode,TLiwVariant((TInt32)SapiErr)));
        eventParamList->AppendL(TLiwGenericParam(KReturnValue,TLiwVariant(iterable)));
        callback->HandleNotifyL(aTransactionId,KLiwEventCompleted,*eventParamList,*inParamList);
        CleanupStack::PopAndDestroy(iterable);
    	}
    CleanupStack::PopAndDestroy(inParamList);
    CleanupStack::PopAndDestroy(eventParamList);
    }

void CLandmarkObserver::HandleAddItemsL(TPosLmItemId aId,
		TInt32 aTransactionId, TInt aError)
	{
	if (iId)
		{
		delete iId;
		iId = NULL;
		}
	TInt SapiErr = SErrNone;
	//retrieve callback
	MLiwNotifyCallback* callback = iLmIface->Callback(aTransactionId);
	if (!callback)
		{
		//how to flag error
		return;
		}
	//Create param list
	CLiwGenericParamList* eventParamList = CLiwGenericParamList::NewL();
	CleanupStack::PushL(eventParamList);
	CLiwGenericParamList* inParamList = CLiwGenericParamList::NewL();
	CleanupStack::PushL(inParamList);

	if (aError != KErrNone)
		{
		SapiErr = iLmIface->SapiError(aError);
		eventParamList->AppendL(TLiwGenericParam(KErrorCode, TLiwVariant(
				(TInt32) SapiErr)));
		callback->HandleNotifyL(aTransactionId, KLiwEventError,
				*eventParamList, *inParamList);
		}
	else
		{
		iId = HBufC::NewL(KMaxIDStringLength);
		iId->Des().Num(aId, EDecimal);
		//pack to aOutParamList
		eventParamList->AppendL(TLiwGenericParam(KErrorCode, TLiwVariant(
				(TInt32) SapiErr)));
		eventParamList->AppendL(TLiwGenericParam(KReturnValue, TLiwVariant(iId)));
		callback->HandleNotifyL(aTransactionId, KLiwEventCompleted,
				*eventParamList, *inParamList);
		}
	CleanupStack::PopAndDestroy(inParamList);
	CleanupStack::PopAndDestroy(eventParamList);
	}

void CLandmarkObserver::HandleItemsL(TInt32 aTransactionId, TInt aError)
	{
	TInt SapiErr = SErrNone;
	//retrieve callback
	MLiwNotifyCallback* callback = iLmIface->Callback(aTransactionId);
	if (!callback)
		{
		//how to flag error
		return;
		}
	//Create param list
	CLiwGenericParamList* eventParamList = CLiwGenericParamList::NewL();
	CleanupStack::PushL(eventParamList);
	CLiwGenericParamList* inParamList = CLiwGenericParamList::NewL();
	CleanupStack::PushL(inParamList);

	if (aError != KErrNone)
		{
		SapiErr = iLmIface->SapiError(aError);
		eventParamList->AppendL(TLiwGenericParam(KErrorCode, TLiwVariant(
				(TInt32) SapiErr)));
		callback->HandleNotifyL(aTransactionId, KLiwEventError,
				*eventParamList, *inParamList);
		}
	else
		{
		//pack to aOutParamList
		eventParamList->AppendL(TLiwGenericParam(KErrorCode, TLiwVariant(
				(TInt32) SapiErr)));
		callback->HandleNotifyL(aTransactionId, KLiwEventCompleted,
				*eventParamList, *inParamList);
		}
	CleanupStack::PopAndDestroy(inParamList);
	CleanupStack::PopAndDestroy(eventParamList);
	}
//End of file
