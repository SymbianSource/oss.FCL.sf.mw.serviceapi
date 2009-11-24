/*
* Copyright (c) 2006-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Implements callback methods which is called my core dll call
*                                   callback methods.
*
*/

#include <liwserviceifbase.h>
#include <liwcommon.h>
#include <logwrap.h>
#include <logclientchangeobserver.h>

#include "logiter.h"
#include "logginginterface.h"
#include "loggingasyncservice.h"
#include "loggingcallback.h"
#include "loggingevent.h"
#include "liwlogiter.h"


/**
* OverLoaded constructor which accepts the callback adderss
* and registers it
*/
LoggingInterfaceCB :: LoggingInterfaceCB( MLiwNotifyCallback* aCallBack ) : iCallBack(aCallBack)
    {
    }

/**
* Default destructor
*/
LoggingInterfaceCB :: ~LoggingInterfaceCB()
    {
    //delete iOutParmList;
    }

/**
* overloaded NewL function for creating local call back objects
* as required by logginginterface.cpp
*/
LoggingInterfaceCB *LoggingInterfaceCB :: NewL( MLiwNotifyCallback* aCallBack )
    {
    LoggingInterfaceCB *self = new( ELeave ) LoggingInterfaceCB( aCallBack ) ;
    return self ;
    }

/**
* HandleNotifyL method, callback method, called by the core class
* for async events
*/

void  LoggingInterfaceCB :: HandleNotifyL( TUint aTransId, TUint aStatus, CLogIter *aIter )
    {
    CleanupStack :: PushL( this ) ;
    
    CLiwGenericParamList *OutParm = CLiwGenericParamList :: NewL() ;
    CleanupStack :: PushL(OutParm) ;
    CLiwGenericParamList *InParm = CLiwGenericParamList :: NewL() ;
    CleanupStack :: PushL(InParm) ;
    
    TInt32 sapierror  ;
    
    sapierror = CLoggingInterface::ConvertToSapiError( aStatus );
    
    OutParm->AppendL(TLiwGenericParam(KErrCode , TLiwVariant((TInt32)sapierror))) ;
    
    switch( iRequestType )
        {
        case EReadEvents :
            {
            CLiwLogIter *iter = CLiwLogIter :: NewL( aIter ) ;
            CleanupClosePushL( *iter );
            OutParm->AppendL( TLiwGenericParam ( KResponse , TLiwVariant( iter ) )  ) ;
            CleanupStack :: Pop( iter ) ;
            iter->DecRef();
            iCallBack->HandleNotifyL( aTransId, KLiwEventCompleted, *OutParm, *InParm ) ;
            CleanupStack::PopAndDestroy( InParm );
            CleanupStack::PopAndDestroy( OutParm );
            CleanupStack :: Pop( this ) ;
            delete this ;
            break ;
            }
    
        case EGetEvent :
            {
            CLiwLogIter *iter = CLiwLogIter :: NewL( aIter ) ;
            CleanupClosePushL( *iter );
            OutParm->AppendL( TLiwGenericParam ( KResponse , TLiwVariant( iter ) )  ) ;
            CleanupStack :: Pop( iter ) ;
            iter->DecRef();
            iCallBack->HandleNotifyL( aTransId, KLiwEventCompleted, *OutParm, *InParm ) ;
            CleanupStack::PopAndDestroy( InParm );
            CleanupStack::PopAndDestroy( OutParm );
            CleanupStack :: Pop( this ) ;
            delete this ;
            break ;
            }
    
        case EGetRecent :
            {
            CLiwLogIter *iter = CLiwLogIter :: NewL( aIter ) ;
            CleanupClosePushL( *iter );
            OutParm->AppendL( TLiwGenericParam ( KResponse , TLiwVariant( iter ) )  ) ;
            CleanupStack :: Pop( iter ) ;
            iter->DecRef();
            iCallBack->HandleNotifyL( aTransId, KLiwEventCompleted, *OutParm, *InParm ) ;
            CleanupStack::PopAndDestroy( InParm );
            CleanupStack::PopAndDestroy( OutParm );
            CleanupStack :: Pop( this ) ;
            delete this ;
            break ;
            }
    
        case EAddEvent :
            {
            if( aStatus == KErrNone )
                {
                TLogId ret=(aIter->Event())->Id();
                TBuf<8> des;
                des.Num( ret );
                OutParm->AppendL( TLiwGenericParam ( KResponse , TLiwVariant( des ) )  ) ;
                iCallBack->HandleNotifyL( aTransId, KLiwEventCompleted, *OutParm, *InParm ) ;
                }
            else
                {
                iCallBack->HandleNotifyL( aTransId, KLiwEventError, *OutParm, *InParm ) ;
                }    
            
            CleanupStack::PopAndDestroy( InParm );
            CleanupStack::PopAndDestroy( OutParm );
            CleanupStack :: Pop( this ) ;
            delete this ;
            delete aIter;
            break ;
            }
    
        case ENotification :
            {
            iCallBack->HandleNotifyL( aTransId, KLiwEventInProgress, *OutParm, *InParm ) ;
            CleanupStack::PopAndDestroy( InParm );
            CleanupStack::PopAndDestroy( OutParm );
            CleanupStack :: Pop( this ) ;
            break ;
            }
    
        case EDeleteEvent :
            {
            if( aStatus == KErrNone )
                {
                iCallBack->HandleNotifyL( aTransId, KLiwEventCompleted, *OutParm, *InParm ) ;
                }
            else
                {
                iCallBack->HandleNotifyL( aTransId, KLiwEventError, *OutParm, *InParm ) ;
                }    
            CleanupStack::PopAndDestroy( InParm );
            CleanupStack::PopAndDestroy( OutParm );
            CleanupStack :: Pop( this ) ;
            delete this;
            break ;
            }
            
        default :
            {
            break ;
            }
        }
    }   

 void  LoggingInterfaceCB :: CancelNotifyL( TUint aTransid )
    {
    CleanupStack :: PushL( this ) ;
    CLiwGenericParamList *OutParm = CLiwGenericParamList :: NewL() ;
    CleanupStack :: PushL( OutParm ) ;
    CLiwGenericParamList *InParm = CLiwGenericParamList :: NewL() ;
    CleanupStack :: PushL( InParm ) ;
    OutParm->AppendL( TLiwGenericParam( KErrCode , TLiwVariant( ( TInt32 )SErrNone ) ) ) ;
    iCallBack->HandleNotifyL( aTransid, KLiwEventCanceled, *OutParm, *InParm ) ;
    CleanupStack::PopAndDestroy( InParm );
    CleanupStack::PopAndDestroy( OutParm );
    CleanupStack :: Pop( this ) ;
    delete this;
    }
