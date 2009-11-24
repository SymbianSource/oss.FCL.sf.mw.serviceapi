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
* Description:  This Class is observer for the Application Manager core class
*
*/


#include <liwcommon.h>
#include "appserviceobserver.h"
#include "serviceerrno.h"
//Output Keys/arguments
_LIT8(KResponse,"ReturnValue");
_LIT8(KErrorCode,"ErrorCode");

// -----------------------------------------------------------------------------
// CAppServiceObserver::NewL
// Returns the instance of CLauncherObserver.
// -----------------------------------------------------------------------------
CAppServiceObserver* CAppServiceObserver::NewL( MLiwNotifyCallback* aCallBack )
	{
	CAppServiceObserver* self = new( ELeave ) CAppServiceObserver(aCallBack);
	return self;
	}

// ---------------------------------------------------------------------------
// callback
// ---------------------------------------------------------------------------
//
void CAppServiceObserver::AppNotifyCallbackL( TInt32 aReason, TInt32 aTransactionID ,TAppOperationEvent& aOperationEvent )

	{
	CLiwGenericParamList* input = NULL;
	CLiwGenericParamList* ouput = CLiwGenericParamList::NewLC();
	
	ouput->Reset();
   
    if ( EAppCancel == aOperationEvent )
        {
        
        ouput->AppendL( TLiwGenericParam ( KErrorCode,TLiwVariant( (TInt32)SErrNone ) ) );
        TRAP_IGNORE(iCallBack->HandleNotifyL ( aTransactionID, KLiwEventCanceled, *ouput,*input ));
        
        }
    else
        {
           
        ouput->AppendL(TLiwGenericParam(KErrorCode,TLiwVariant((TInt32)SErrNone)));    
        
        ouput->AppendL( TLiwGenericParam ( KResponse, TLiwVariant ( aReason ) ) );
        
        TRAP_IGNORE(iCallBack->HandleNotifyL ( aTransactionID, KLiwEventCompleted, *ouput,*input ));
        
        }
     CleanupStack::PopAndDestroy( ouput );
     delete this;
	}




// ---------------------------------------------------------------------------
// consturctor
// ---------------------------------------------------------------------------
//
CAppServiceObserver::CAppServiceObserver( MLiwNotifyCallback* aCallBack )
	{
	 iCallBack = aCallBack;
     
	}