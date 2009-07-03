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
* Description:  This class is the observer of thumbanil generation
*  *
*/

#include<Liwcommon.h>
#include "serviceerrno.h"
#include "mgservicethumbnailobserver.h"
#include"mginterface.h"
_LIT8(KResponse,"ReturnValue");
_LIT8(KErrorCode,"ErrorCode");


// -----------------------------------------------------------------------------
// CServiceThumbanilObserver::NewL
// Returns the instance of CServiceThumbanilObserver.
// -----------------------------------------------------------------------------
CServiceThumbnailObserver* CServiceThumbnailObserver::NewL( MLiwNotifyCallback* aCallBack )
    {
    CServiceThumbnailObserver* self = new( ELeave ) CServiceThumbnailObserver(aCallBack);
    return self;
    }
// -----------------------------------------------------------------------------
// CServiceThumbanilObserver::~CServiceThumbnailObserver
// Destructor
// -----------------------------------------------------------------------------
CServiceThumbnailObserver::~CServiceThumbnailObserver()
    {
    iCallBack = NULL;
    }

// ---------------------------------------------------------------------------
// CServiceThumbnailObserver::ThumbnailReady
//  This method is called when thumbnail gets generated
// ---------------------------------------------------------------------------
//
void CServiceThumbnailObserver::ThumbnailReady(TInt aError, TDesC& aThumbnailURL,TInt32 aTransactionID)

    {
    CLiwGenericParamList* input = NULL;
    CLiwGenericParamList* output = CLiwGenericParamList::NewLC();
    
    output->Reset();
      
    TInt sapiErr = SErrNone;
        if (aError)
            {
            sapiErr = CMgInterface::SapiError( aError );
            }

    
    
        output->AppendL(TLiwGenericParam(KErrorCode,TLiwVariant((TInt32)sapiErr)));    
     
        output->AppendL( TLiwGenericParam ( KResponse, TLiwVariant ( aThumbnailURL ) ) );
        
        TRAP_IGNORE(iCallBack->HandleNotifyL ( aTransactionID, KLiwEventCompleted, *output,*input ));
        
 
     CleanupStack::PopAndDestroy( output );
     delete this;
    }

// ---------------------------------------------------------------------------
// CServiceThumbnailObserver::ThumbnailRequestCancel
// Callback method gets called when thumbnail request is canceled
// ---------------------------------------------------------------------------
//

void CServiceThumbnailObserver::ThumbnailRequestCancel(TInt aError,TInt32 aTransactionID)
    {
    CLiwGenericParamList* input = NULL;
     CLiwGenericParamList* output = CLiwGenericParamList::NewLC();
     
     output->Reset();
             
         output->AppendL(TLiwGenericParam(KErrorCode,TLiwVariant((TInt32)SErrNone)));    
         output->AppendL( TLiwGenericParam ( KResponse, TLiwVariant ( aError ) ) );
         
         TRAP_IGNORE(iCallBack->HandleNotifyL ( aTransactionID, KLiwEventCanceled, *output,*input ));
         
  
      CleanupStack::PopAndDestroy( output );
      delete this;
    }


// ---------------------------------------------------------------------------
// CServiceThumbnailObserver::CServiceThumbnailObserver
//  Constructor
// ---------------------------------------------------------------------------
//
CServiceThumbnailObserver::CServiceThumbnailObserver( MLiwNotifyCallback* aCallBack )
    {
     iCallBack = aCallBack;
     
    }
