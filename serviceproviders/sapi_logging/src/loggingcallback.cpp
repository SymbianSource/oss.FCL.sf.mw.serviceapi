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

#ifndef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <logwrap.h>
#else
#include <logwrap.h>
#include <logengevents.h>
#include <logwraplimits.h>
#include <logfilterandeventconstants.hrh>
#include <logengdurations.h>
#endif

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

void  LoggingInterfaceCB :: HandleReqeustL( TUint aTransId, TUint aStatus, CLogsEvent *aEvents )
    {
    TInt i = 0;
    CleanupStack :: PushL( this ) ;
    
    CLiwGenericParamList *OutParm = CLiwGenericParamList :: NewL() ;
    CleanupStack :: PushL(OutParm) ;
    CLiwGenericParamList *InParm = CLiwGenericParamList :: NewL() ;
    CleanupStack :: PushL(InParm) ;
    
    TInt32 sapierror  ;
    
    sapierror = CLoggingInterface::ConvertToSapiError( aStatus );
    
    OutParm->AppendL(TLiwGenericParam(KErrCode , TLiwVariant((TInt32)sapierror))) ;
    
    CleanupStack::PushL(aEvents);
    
    CLiwDefaultMap *evntmap = CLiwDefaultMap :: NewL() ;
    
    CleanupClosePushL( *evntmap );
    
    TLiwVariant entry;
    
    /**
     * Extract all the event details form CLogsEvent object
     * and push it to the aEntry
     */    
    
    TInt32 val = 0 ;
    
    switch( (aEvents->getEventType()).iUid )
        {
        case KLogCallEventType :
            {
            val = CLoggingInterface :: EKLogCallEventType ;
            break ;
            }
        
        case KLogDataEventType :
            {
            val = CLoggingInterface :: EKLogDataEventType ;
            break ;
            }
        
        case KLogFaxEventType :
            {
            val = CLoggingInterface :: EKLogFaxEventType ;
            break ;
            }
        
        case KLogShortMessageEventType :
            {
            val = CLoggingInterface :: EKLogShortMessageEventType ;
            break ;
            }
            
        case KLogPacketDataEventType :
            {
            val = CLoggingInterface :: EKLogPacketDataEventType ;
            break ;
            }     
        
        default :
            {
            break ;
            }
        }
    
    evntmap->InsertL(KEventTypeKey , TLiwVariant((TInt32)val));
    
    evntmap->InsertL(KRemotePartyKey , TLiwVariant(aEvents->getRemoteParty())) ;
    
    evntmap->InsertL(KEventDurationKey ,TLiwVariant((TInt32)aEvents->getDuration())) ;
    
    evntmap->InsertL(KEventTimeKey , TLiwVariant(aEvents->getTime())) ;
    
    val = 0 ;
    
    /**
     * Need to convert status to int value
     */    
    if( ( ( aEvents->getStatus() ).Compare( KStatusPending ) ) == KErrNone )
        {
        val = CLoggingInterface :: EStatusPending ;
        }
    else if( ( ( aEvents->getStatus() ).Compare( KStatusSent ) ) == KErrNone )
        {
        val =CLoggingInterface :: EStatusSent ;
        }
    else if( ( ( aEvents->getStatus() ).Compare( KStatusFalied ) ) == KErrNone )
        {
        val = CLoggingInterface :: EStatusFalied ;
        }
    else if( ( ( aEvents->getStatus() ).Compare( KStatusNone ) ) == KErrNone )
        {
        val = CLoggingInterface :: EStatusNone;
        }
    else if( ( ( aEvents->getStatus() ).Compare( KStatusDone ) ) == KErrNone )
        {
        val = CLoggingInterface :: EStatusDone;
        }
    else if( ( ( aEvents->getStatus() ).Compare( KStatusNotSent ) ) == KErrNone )
        {
        val = CLoggingInterface :: EStatusNotSent;
        }
    else if( ( ( aEvents->getStatus() ).Compare( KStatusScheduled ) ) == KErrNone )
        {
        val = CLoggingInterface :: EStatusScheduled;
        }
    else
        {
        val = CLoggingInterface :: EStatusNotPresent;
        }
        
    if( val != -1 )  
        {
        evntmap->InsertL(KDeliveryStatusKey , TLiwVariant((TInt32)val)) ;
        }
    
    evntmap->InsertL(KSubjectKey , TLiwVariant(aEvents->getSubject())) ;
    
    evntmap->InsertL(KPhoneNumberKey , TLiwVariant(aEvents->getNumber())) ;
    
    evntmap->InsertL(KDescriptionKey , TLiwVariant (aEvents->getDescription())) ;
    
    evntmap->InsertL(KLinkKey , TLiwVariant((TInt32)aEvents->getLink())) ;
    
    val = 0 ;
    
    if( aEvents->Flags() & KLogEventContactSearched )
        {
        val = CLoggingInterface :: EKLogEventContactSearched ;
        }
    else if( aEvents->Flags() & KLogEventRead )
        {
        val = CLoggingInterface :: EKLogEventRead ;
        }
    
    else
        {
        val = CLoggingInterface :: EFlagNotPresent;
        }
        
    if( val != -1 )  
        {    
        evntmap->InsertL(KFlagsKey , TLiwVariant((TInt32)val) );
        }
    
    TInt32 ret =  aEvents->Id();
    TBuf<8> des;
    des.Num(ret);
    evntmap->InsertL(KLogId , TLiwVariant( des)) ;
    
    val = 0 ;
    
    if( ( ( aEvents->getDirection() ).Compare( KIncomingEvent ) ) == KErrNone )
        {
        val = CLoggingInterface :: EIncomingEvent ;
        }
    else if( ( ( aEvents->getDirection() ).Compare( KOutgoingEvent ) ) == KErrNone )
        {
        val = CLoggingInterface :: EOutgoingEvent ;
        }
    else if( ( ( aEvents->getDirection() ).Compare( KIncomingEventAlternateline ) ) == KErrNone )
        {
        val = CLoggingInterface :: EIncomingEventAlternateline ;
        }
    else if( ( ( aEvents->getDirection() ).Compare( KOutgoingEventAlternateline ) ) == KErrNone )
        {
        val = CLoggingInterface :: EOutgoingEventAlternateline;
        }
    else if( ( ( aEvents->getDirection() ).Compare( KFetchedEvent ) ) == KErrNone )
        {
        val = CLoggingInterface :: EFetchedEvent;
        }
    else if( ( ( aEvents->getDirection() ).Compare( KMissedEvent ) ) == KErrNone )
        {
        val = CLoggingInterface :: EMissedEvent;
        }
    else if( ( ( aEvents->getDirection() ).Compare( KMissedEventAlternateline ) ) == KErrNone )
        {
        val = CLoggingInterface :: EMissedEventAlternateline;
        }
    else
        {
        val = CLoggingInterface :: EDirectionNotPresent;
        }
        
    if( val != -1 )  
        {    
        evntmap->InsertL(KDirectionKey , TLiwVariant((TInt32)val)) ;
        }
        
    evntmap->InsertL(KEventDataKey , TLiwVariant(aEvents->getDataL()));
    
    entry.SetL( evntmap ) ;
    OutParm->AppendL( TLiwGenericParam( KResponse , entry  ) ) ;
    CleanupStack :: Pop( evntmap ) ;
    evntmap->DecRef();
    CleanupStack::Pop( aEvents );
    delete aEvents;
        
        
    iCallBack->HandleNotifyL( aTransId, KLiwEventInProgress, *OutParm, *InParm ) ;
    
    CleanupStack::PopAndDestroy( InParm );
    CleanupStack::PopAndDestroy( OutParm );
    CleanupStack::Pop(this);   
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
