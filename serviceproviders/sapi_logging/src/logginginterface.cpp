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
* Description:  implements interface class for logging sapi
*
*/


#include <e32base.h>
#include <e32def.h>
#include <f32file.h>
#include <cntdef.h>
#ifndef SYMBIAN_ENABLE_SPLIT_HEADERS
#include <logwrap.h>
#else
#include <logwrap.h>
#include <logengevents.h>
#include <logwraplimits.h>
#include <logfilterandeventconstants.hrh>
#include <logengdurations.h>
#endif
#include <liwserviceifbase.h>
#include <liwcommon.h>
#include <ecom/implementationproxy.h>
#include  <utf.h>
#include "loggingasyncservice.h"


#include "logclientchangeobserver.h"
#include "logiter.h"
#include "loggingservice.h"
#include "loggingasyncservice.h"
#include "loggingsyncservice.h"
#include "loggingevent.h"
#include "loggingfilter.h"
#include "loggingcallbackslot.h"
#include "logobserver.h"
#include "logginginterface.h"
#include "liwlogiter.h"
#include "loggingcallback.h"



/**
 * Default Constructor Method
 */
CLoggingInterface :: CLoggingInterface()
    {
    }
    
/**
 * Default Destructor
 */
CLoggingInterface :: ~CLoggingInterface()
    {
    delete iErrorString;
    delete iLogService;
    }

/**
 * Two phased constructor implementation
 */
CLoggingInterface* CLoggingInterface :: NewL()
    {
    CLoggingInterface* self = CLoggingInterface::NewLC();
    CleanupStack::Pop( self );
    return self;
    }

/**
 * Two phased constructor implementation
 */
CLoggingInterface* CLoggingInterface :: NewLC()
    {
    CLoggingInterface* self = new ( ELeave ) CLoggingInterface();
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }

/**
 * This function constructs the member elements of CLoggingInterface Class
 */
void CLoggingInterface :: ConstructL()
    {
    iLogService = CLoggingService::NewL();
    }

/**
 * closes the interface
 */
void CLoggingInterface::Close()
    {
    delete this;
    }

/**
 * Convert to sapiError Function
 */
TInt  CLoggingInterface::ConvertToSapiError( TInt aSymbianErr )
    {
    TInt sapiErr( SErrGeneralError );

    switch ( aSymbianErr )
        {
        case KErrArgument:
            {
            sapiErr = SErrBadArgumentType;
            break;
            }
        case KErrNotSupported:
            {
            sapiErr = SErrServiceNotSupported;
            break;
            }
        case KErrServerBusy:
            {
            sapiErr = SErrServerBusy;
            break;
            }
        case KErrGeneral:
            {
            sapiErr = SErrGeneralError;
            break;
            }
        case KErrCancel:
            {
            sapiErr = SErrCancelSuccess;
            break;
            }
        case KErrNone:
            {
            sapiErr= SErrNone;
            break;
            }
        case KErrNotFound:
            {
            sapiErr= SErrNotFound;
            break;
            }
        case KErrNoMemory:
            {
            sapiErr = SErrNoMemory;
            break;
            }
        case KErrInUse:
            {
            sapiErr = SErrServiceInUse;
            break;
            }
        case KErrNotReady:
            {
            sapiErr = SErrServiceNotReady;
            break;
            }
        case SErrMissingArgument:
            {
            sapiErr = SErrMissingArgument;
            break;
            }
        case SErrInvalidServiceArgument :
            {
            sapiErr = SErrInvalidServiceArgument;
            break;    
            } 
        }
    return sapiErr;
    }

void CLoggingInterface::CheckInputTypeL( const TLiwVariant* aSource, LIW::TVariantTypeId aExpectedtype, const TDesC8* aErrorArgument )
    {
    if( aSource->TypeId() != aExpectedtype )
        {
        iErrorString = HBufC::NewL(KMaxMsgSize);
        TPtr ptr(iErrorString->Des());
        TBuf<KMaxKeySize> buf;
        buf.Copy( *aErrorArgument );
        ptr.Append(buf);
        ptr.Append( KInvalid.operator()());
        ((TLiwVariant*)aSource)->Reset();
        User::Leave( KErrArgument );
        }
    }

void CLoggingInterface::IncorrectValueL( const TDesC8* aErrorArgument )
    {
    iErrorString = HBufC::NewL(KMaxMsgSize);
    TPtr ptr(iErrorString->Des());
    TBuf<KMaxKeySize> buf;
    buf.Copy( *aErrorArgument );
    ptr.Append(buf);
    ptr.Append( KInvalid.operator()());
    }

void CLoggingInterface::MissingValueL( const TDesC8* aErrorArgument )
    {
    iErrorString = HBufC::NewL(KMaxMsgSize);
    TPtr ptr(iErrorString->Des());
    TBuf<KMaxKeySize> buf;
    buf.Copy( *aErrorArgument );
    ptr.Append(buf);
    ptr.Append( KMissing.operator()());
    User::Leave( SErrMissingArgument );
    }

/**
 * Function : ExecuteCmdL , called directly by consumer, parses the input parameters and
 * then calls appropriate method on iLocationService object
 */
void CLoggingInterface :: ExecuteCmdL( const TDesC8& aCmdName,
                                       const CLiwGenericParamList& aInParamList,
                                       CLiwGenericParamList& aOutParamList,
                                       TUint aCmdOptions,
                                       MLiwNotifyCallback* aCallback )
    {
    TRAPD( error , CmdExecuteL( aCmdName , aInParamList , aOutParamList , aCmdOptions , aCallback ) ) ;
    if( error != KErrNone )
        {
        if( iErrorString )
            {
            TBuf<150> errorMessage;
            errorMessage.Append( KMsgErr.operator()() );
            TBuf<40> commandName;
            commandName.Copy( aCmdName );
            errorMessage.Append( commandName );
            errorMessage.Append( KColon.operator()());
            
            errorMessage.Append( iErrorString->Des() );
            
            aOutParamList.AppendL(TLiwGenericParam( KErrorMessage,
                        TLiwVariant( errorMessage )));
            delete iErrorString;
            iErrorString = NULL;
            }
        }
    TInt sapierror = ConvertToSapiError( error );
    aOutParamList.AppendL(TLiwGenericParam(KErrorCode , TLiwVariant((TInt32)sapierror))) ;
    }

/**
 * CLoggingInterface::CmdExecuteL, this method is called by CLoggingInterface::HandleCmdL()
 * to catch any leaves that might occur during execution of a LiwCommand.
 *
 * @param aCmdName the name of the service command which the consumer wants to invoke
 * @param aInParamList the input parameter list, can be empty list
 * @param [in,out] aOutParamList the output parameter list, can be empty lis. The
 * service provider can use the output parameter list to fill in necessary return values
 * @param aCmdOptions Options for the command, see TLiwServiceCmdOptions in LiwCommon.hrh.
 * @param aCallback callback to be registered by consumer application
 * @see TLiwServiceCmdOptions
 * @see CLiwGenericParamList
 * @see MLiwNotifyCallback
 */
void CLoggingInterface :: CmdExecuteL( const TDesC8& aCmdName,
                                       const CLiwGenericParamList& aInParamList,
                                       CLiwGenericParamList& aOutParamList,
                                       TUint aCmdOptions,
                                       MLiwNotifyCallback* aCallback )
    {
    aOutParamList.Reset() ;
    
    if(!aCmdName.CompareF( KCmdCancel ))
        {
        if( aCmdOptions & KLiwOptCancel )
            {
            TInt ret = 0 ;
            
            const TLiwGenericParam *transidparam = aInParamList.FindFirst( ret , KTransactionId ) ;
            
            if(!transidparam && ( aInParamList.Count() > 0 ) )
                {
                transidparam  = &(aInParamList[EIndex0])  ;
                
                if( transidparam->Name().Compare( KNullDesC8 ) )
                    {
                    MissingValueL( KTransactionId.operator&() );
                    }
                }
                
            if( !transidparam )
                {
                MissingValueL( KTransactionId.operator&() );
                }
                
            CheckInputTypeL( &transidparam->Value(), LIW::EVariantTypeTInt32, KTransactionId.operator&() );  
            TInt32 transid = (transidparam->Value()).AsTInt32() ;
            
            if( transid<0 )
                {
                IncorrectValueL( KTransactionId.operator&() );
                User::Leave( KErrNotFound );
                }
                
            ret = iLogService->CancelServiceL( transid ) ;
            
            if( ret == KErrNotFound )
                {
                IncorrectValueL( KTransactionId.operator&() );
                User::Leave( KErrNotFound );
                }
                
            return ;
            }
        }
        
    else if(!aCmdName.CompareF( KCmdAdd ))
        {
        TBool indexBaseInp = ETrue;
        TInt Index = 0 ;
        
        const TLiwGenericParam *contentType = aInParamList.FindFirst( Index , KContentTypeKey ) ;
        
        if( !contentType && ( aInParamList.Count() > 0 ) )
            {
            contentType = &(aInParamList[EIndex0]) ;
            
            if( contentType->Name().Compare( KNullDesC8 ) )
                {
                MissingValueL( KContentTypeKey.operator&() );
                }
            }
        else
            {
            indexBaseInp = EFalse ;
            }
           
        if( !contentType )
            {
            MissingValueL( KContentTypeKey.operator&() );
            }
        
        CheckInputTypeL( &contentType->Value(), LIW::EVariantTypeDesC, KContentTypeKey.operator&() );
        TPtrC content = (contentType->Value()).AsDes() ;
        
        if(content.CompareF( KContentType ))
            {
            IncorrectValueL( KContentTypeKey.operator&() );
            User::Leave( SErrInvalidServiceArgument );
            }
        
        TInt index = 0 ;
        const TLiwGenericParam *eventdetails = NULL ;
        TUint transid ;
        
        if ( indexBaseInp ) 
            {
            if( aInParamList.Count() > 1 )
                {
                eventdetails  = &(aInParamList[EIndex1]) ;
                }
            }
        else
            {
            eventdetails = aInParamList.FindFirst( index , KEventDetails );
            }    
        
        if( !eventdetails )
            {
            MissingValueL( KEventDetails.operator&() );
            }
        
        TInt32  ret = AddEventL( eventdetails, transid, aCmdOptions, aCallback ) ;
        
        if( aCallback )
            {
            aOutParamList.AppendL( TLiwGenericParam( KTransactionId , TLiwVariant ( ( TInt32 )transid ) ) ) ;
            }
        else
            {
            TBuf<8> des;
            des.Num( ret );
            aOutParamList.AppendL( TLiwGenericParam( KResponse , TLiwVariant( des ) ) ) ;
            }
        }
    
    else if(!aCmdName.CompareF( KCmdGetList ))
        {
        TBool indexBaseInp = ETrue;
        TInt Index = 0 ;
        
        const TLiwGenericParam *contentType = aInParamList.FindFirst(Index , KContentTypeKey) ;
        
        if( !contentType && ( aInParamList.Count() > 0 ) )
            {
            contentType = &(aInParamList[EIndex0]) ;
            
            if( contentType->Name().Compare( KNullDesC8 ) )
                {
                MissingValueL( KContentTypeKey.operator&() );
                }
            }
         else
            {
            indexBaseInp = EFalse ;
            }    
        
        if( !contentType )
            {
            MissingValueL( KContentTypeKey.operator&() );
            }
        
        CheckInputTypeL( &contentType->Value(), LIW::EVariantTypeDesC ,KContentTypeKey.operator&() );
        TPtrC content = (contentType->Value()).AsDes() ;
        
        if( content.CompareF( KContentType ) )
            {
            IncorrectValueL( KContentTypeKey.operator&() );
            User::Leave( SErrInvalidServiceArgument );
            }
        
        TInt index = 0 ;
        const TLiwGenericParam *flrParam = NULL ;
        TUint transid ;
       
        if ( indexBaseInp ) 
            {
            if( aInParamList.Count() > 1 )
                {
                flrParam = &aInParamList[EIndex1] ;
                }
            }
        else
            {
            flrParam = aInParamList.FindFirst( index , KFilter ) ; 
            }    
        
       
       CLogIter *iter = this->GetListL(flrParam , transid ,aCmdOptions, aCallback) ;
              
        /*Ownership of logiter will be with the consumer*/
        if( aCallback )
            {
            aOutParamList.AppendL( TLiwGenericParam( KTransactionId , TLiwVariant( ( TInt32 )transid ) ) ) ;
            }
        else
            {
            CLiwLogIter *logiter = CLiwLogIter :: NewL( iter ) ;
            CleanupClosePushL( *logiter );
            aOutParamList.AppendL( TLiwGenericParam( KResponse , TLiwVariant( logiter ) ) ) ;
            CleanupStack :: Pop( logiter ) ;
            logiter->DecRef() ;
            }
        }
     
    else if(!aCmdName.CompareF( KCmdRequestNotification ))
        {
        TBool indexBaseInp = ETrue;
        TInt Index = 0 ;
        
        const TLiwGenericParam *contentType = aInParamList.FindFirst( Index , KContentTypeKey ) ;
        
        if( !contentType && ( aInParamList.Count() > 0 ) )
            {
            contentType = &(aInParamList[EIndex0]) ;
            
            if( contentType->Name().Compare( KNullDesC8 ) )
                {
                MissingValueL( KContentTypeKey.operator&() );
                }
            }
        else
            {
            indexBaseInp = EFalse ;
            }    
        
        if( !contentType )
            {
            MissingValueL( KContentTypeKey.operator&() );
            }
        
        CheckInputTypeL( &contentType->Value(), LIW::EVariantTypeDesC, KContentTypeKey.operator&() );
        
        TPtrC content = (contentType->Value()).AsDes() ;
        
        if(content.CompareF( KContentType ))
            {
            IncorrectValueL( KContentTypeKey.operator&() );
            User::Leave( SErrInvalidServiceArgument );
            }
                
        TInt index = 0 ;
        TUint transid ;
        const TLiwGenericParam *interval = NULL ;
        
        if ( indexBaseInp ) 
            {
            if( aInParamList.Count() > 1 )
                {
                interval = &(aInParamList[EIndex1]) ;
                }
            }
        else
            {
            interval = aInParamList.FindFirst( index , KFilter ) ;
            }    
        
       if( !interval )
            {
            MissingValueL( KFilter.operator&() );
            }
        
        this->RequestNotificationsL( interval, aCallback, transid, aCmdOptions ) ;
        
        aOutParamList.AppendL( TLiwGenericParam( KTransactionId , TLiwVariant( ( TInt32 )transid ) ) ) ;
        }
    
    else if(!aCmdName.CompareF( KCmdDelete ))
        {
        TBool indexBaseInp = ETrue;
        TInt Index = 0 ;
        
        const TLiwGenericParam *contentType = aInParamList.FindFirst( Index , KContentTypeKey ) ;
        
        if( !contentType && ( aInParamList.Count() > 0 ))
            {
            contentType = &(aInParamList[EIndex0]) ;
            
            if( contentType->Name().Compare( KNullDesC8 ) )
                {
                MissingValueL( KContentTypeKey.operator&() );
                }
            }
        else
            {
            indexBaseInp = EFalse ;
            }        
        
        if( !contentType )
            {
            MissingValueL( KContentTypeKey.operator&() );
            }
        
        CheckInputTypeL( &contentType->Value(), LIW::EVariantTypeDesC ,KContentTypeKey.operator&() );
        
        TPtrC content = (contentType->Value()).AsDes() ;
        
        if(content.CompareF(KContentType))
            {
            IncorrectValueL( KContentTypeKey.operator&() );
            User::Leave( SErrInvalidServiceArgument );
            }
        
        TInt index = 0;
        TUint transid;
        const TLiwGenericParam *logid = NULL ;
        
        if ( indexBaseInp ) 
            {
            if( aInParamList.Count() > 1 )
                {
                logid = &aInParamList[EIndex1] ;
                }
            }
        else
            {
            logid = aInParamList.FindFirst( index , KData ) ;
            }    
        
        if( !logid )
            {
            MissingValueL( KData.operator&() );
            }
        
        TInt ret = DeleteEventL( logid, transid, aCmdOptions, aCallback );
        
        if( ret != KErrNone )
            {
            IncorrectValueL( KLogId.operator&() );
            User::Leave( KErrNotFound );
            }
        
        if( aCallback )
             {
             aOutParamList.AppendL(TLiwGenericParam( KTransactionId , TLiwVariant( ( TInt32 )transid ) ) ) ;
             }
        }
    
    else
        {
        iErrorString = KErrLogCmdName.operator()().Alloc();
        User :: Leave( KErrNotSupported ) ;
        }
    }

/**
 * Internal utility method, used to Add from the core class
 *
 * @param aeventdetails,
 * @param aTransId,
 * @param aCallback, callback method for async events
 */
TInt32 CLoggingInterface::AddEventL( const TLiwGenericParam *eventdetails ,
                                     TUint& aTansId ,
                                     TUint aCmdOptions,
                                     MLiwNotifyCallback* aCallback )
    {
    CheckInputTypeL( &eventdetails->Value(), LIW::EVariantTypeMap, KEventDetails.operator&() );
    
    CLogsEvent *event  = CLogsEvent :: NewL() ;
    
    CleanupStack :: PushL( event ) ;
    
    const CLiwMap *evtmap = (eventdetails->Value()).AsMap() ;
    
    if( !evtmap )
        {
        MissingValueL( KEventDetails.operator&() );
        }
    
    TLiwVariant mapVar;
    
    CleanupStack::PushL( TCleanupItem( TLiwVariant::VariantCleanup , &mapVar) );
    
    /**
    * Extract the contents of Add Event Details
    * and issue request to the core class  accordingly
    */
    if( evtmap->FindL( KEventTypeKey , mapVar ) )
        {
        CheckInputTypeL( &mapVar, LIW::EVariantTypeTInt32, KEventTypeKey.operator&() );
        TUid val = TUid::Null() ;
        
        switch( mapVar.AsTInt32() )
            {
            case EKLogCallEventType :
                {
                val =  TUid :: Uid( KLogCallEventType );
                break ;
                }
            
            case EKLogDataEventType :
                {
                val = TUid :: Uid ( KLogDataEventType );
                break ;
                }
            
            case EKLogFaxEventType :
                {
                val = TUid :: Uid ( KLogFaxEventType );
                break ;
                }
            
            case EKLogShortMessageEventType :
                {
                val = TUid :: Uid ( KLogShortMessageEventType );
                break ;
                }
                
            case EKLogPacketDataEventType :
                {
                val = TUid :: Uid ( KLogPacketDataEventType ) ;
                break ;
                }     
            
            default :
                {
                mapVar.Reset();
                IncorrectValueL( KEventTypeKey.operator&() ); 
                User::Leave( SErrInvalidServiceArgument );
                }
            }
        event->SetEventType( val ) ;
        }
    else
        {
        mapVar.Reset();
        MissingValueL( KEventTypeKey.operator&() );
        }
    
    if( evtmap->FindL( KRemotePartyKey , mapVar ) )
        {
        CheckInputTypeL( &mapVar, LIW::EVariantTypeDesC, KRemotePartyKey.operator&() );
        event->SetRemoteParty(mapVar.AsDes()) ;
        }
    
    if(evtmap->FindL( KDirectionKey , mapVar ))
        {
        CheckInputTypeL( &mapVar, LIW::EVariantTypeTInt32, KDirectionKey.operator&() );
        TInt val = 0 ;
        
        switch(mapVar.AsTInt32())
            {
            case EIncomingEvent :
                {
                val = R_LOG_DIR_IN ;
                break ;
                }
        
            case EOutgoingEvent :
                {
                val = R_LOG_DIR_OUT ;
                break ;
                }
        
            case EIncomingEventAlternateline :
                {
                val = R_LOG_DIR_IN_ALT ;
                break ;
                }
        
            case EOutgoingEventAlternateline :
                {
                val = R_LOG_DIR_OUT_ALT  ;
                break ;
                }
        
            case  EFetchedEvent :
                {
                val = R_LOG_DIR_FETCHED ;
                break ;
                }
        
            case EMissedEvent :
                {
                val = R_LOG_DIR_MISSED ;
                break ;
                }
        
            case EMissedEventAlternateline :
                {
                val = R_LOG_DIR_MISSED_ALT ;
                break ;
                }
                
            default :
                {
                mapVar.Reset();
                IncorrectValueL( KDirectionKey.operator&() );  
                User::Leave( SErrInvalidServiceArgument );
                }
            }
        
        if( val )
            {
            event->SetDirection( val ) ;
            }
        }
    
    
    if(evtmap->FindL(KEventDurationKey , mapVar))
        {
        CheckInputTypeL( &mapVar, LIW::EVariantTypeTInt32, KEventDurationKey.operator&() );
        
        if( mapVar.AsTInt32()<0 )
              {
              mapVar.Reset();
              IncorrectValueL( KEventDurationKey.operator&() );
              User::Leave( SErrInvalidServiceArgument );
              }
        event->SetDurationType( KLogDurationValid ) ;
        event->SetDuration( mapVar.AsTInt32() ) ;
        }
    
    if(evtmap->FindL( KDeliveryStatusKey , mapVar ))
        {
        CheckInputTypeL( &mapVar, LIW::EVariantTypeTInt32, KDeliveryStatusKey.operator&() );
        TInt val = 0 ;
        
        switch( mapVar.AsTInt32() )
            {
            case EStatusPending :
                {
                val =  R_LOG_DEL_PENDING ;
                break ;
                }
        
            case EStatusSent :
                {
                val = R_LOG_DEL_SENT ;
                break ;
                }
        
            case EStatusFalied :
                {
                val = R_LOG_DEL_FAILED ;
                break ;
                }
        
            case EStatusNone :
                {
                val = R_LOG_DEL_NONE  ;
                break ;
                }
        
            case  EStatusDone :
                {
                val = R_LOG_DEL_DONE ;
                break ;
                }
        
            case EStatusNotSent :
                {
                val = R_LOG_DEL_NOT_SENT ;
                break ;
                }
        
            case EStatusScheduled :
                {
                val = R_LOG_DEL_SCHEDULED ;
                break ;
                }
                
            default :
                {
                mapVar.Reset();
                IncorrectValueL( KDeliveryStatusKey.operator&() );  
                User::Leave( SErrInvalidServiceArgument );
                }
            }
        
        if( val )
            {
            event->SetStatus( val ) ;
            }
        }
    
    if(evtmap->FindL(KFlagsKey , mapVar))
        {
        CheckInputTypeL( &mapVar, LIW::EVariantTypeTInt32, KFlagsKey.operator&() );
        TUint8 val = 0 ;
        
        switch(mapVar.AsTInt32())
            {
            case EKLogEventContactSearched :
                {
                val = KLogEventContactSearched ;
                break ;
                }
            
            case EKLogEventRead :
                {
                val = KLogEventRead ;
                break ;
                }
            
            default :
                {
                mapVar.Reset();
                IncorrectValueL( KFlagsKey.operator&() );  
                User::Leave( SErrInvalidServiceArgument );
                }
            }
        
        if( val )
            {
            event->SetFlags( val ) ;
            }
        }
    
    if(evtmap->FindL( KSubjectKey , mapVar ))
        {
        CheckInputTypeL( &mapVar, LIW::EVariantTypeDesC, KSubjectKey.operator&() );
        event->SetSubject( mapVar.AsDes() ) ;
        }
    
    if(evtmap->FindL( KPhoneNumberKey , mapVar ))
        {
        CheckInputTypeL( &mapVar, LIW::EVariantTypeDesC, KPhoneNumberKey.operator&() );
        event->SetNumber( mapVar.AsDes() ) ;
        }
        
    if(evtmap->FindL( KEventDataKey , mapVar ))
        {
        CheckInputTypeL( &mapVar, LIW::EVariantTypeDesC8, KEventDataKey.operator&() );
        event->SetDataL( mapVar.AsData() ) ;
        }
    
    if(evtmap->FindL( KLinkKey , mapVar ))
        {
        CheckInputTypeL( &mapVar, LIW::EVariantTypeTInt32, KLinkKey.operator&() );
        
        if( mapVar.AsTInt32()<0 )
          {
           mapVar.Reset();
           IncorrectValueL( KLinkKey.operator&() );
           User::Leave( SErrInvalidServiceArgument );
          }
         event->SetLink( mapVar.AsTInt32() ) ;
        }
    
    CleanupStack::Pop( &mapVar );
    
    mapVar.Reset();
        
    if( KLiwOptASyncronous & aCmdOptions )
        {
        if( aCallback!=NULL )
            {
            aTansId = MLiwNotifyCallback :: GetTransactionID() ;
            LoggingInterfaceCB *cb = LoggingInterfaceCB :: NewL( aCallback ) ;
            CleanupStack :: PushL( cb ) ;
            cb->SetRequestType( EAddEvent ) ;
            iLogService->AddEventL( aTansId, event, cb );
            CleanupStack::Pop( cb );
            CleanupStack::Pop( event );
            delete event ;
            return 0;
            }
        else
            {
            iErrorString = KErrMissingCallback.operator()().Alloc();
            User::Leave( SErrInvalidServiceArgument );
            }
        }
    else
        {
        TInt32 logid = iLogService->AddEventL(event) ;
        
        if(logid<0)
            {
            IncorrectValueL( KLogId.operator&() );
            User::Leave( SErrInvalidServiceArgument );
            }
            
        CleanupStack::Pop(event);
        delete event ;
        return  logid ;
        }
    
    return 0;
    }

/**
 * Internal utility method, used to getlist from the core class
 *
 * @param aFilter, filter for getlist on core class
 * @param aTransid , value/result argument(TransactionId
 * @param aCallback, callback method for async events
 */
CLogIter*  CLoggingInterface :: GetListL(  const TLiwGenericParam  *aFilter,
                                           TUint& aTansId,
                                           TUint aCmdOptions,
                                           MLiwNotifyCallback  *aCallback )
    {
    if( aFilter && (aFilter->Value().TypeId() != LIW::EVariantTypeNull) )
        {
        CheckInputTypeL( &aFilter->Value(), LIW::EVariantTypeMap ,KFilter.operator&() );
        
        CLogsFilter *filter = CLogsFilter :: NewL() ;
        
        filter->SetRequestType( EReadEvents ) ;
        
        CleanupStack :: PushL( filter ) ;
        
        const CLiwMap *mapParam = (aFilter->Value()).AsMap() ;
        
        TLiwVariant var ;
        
        CleanupStack::PushL( TCleanupItem( TLiwVariant::VariantCleanup , &var) );
        
        /**
        * Extract the contents of getlist filter
        * and issue request to the core class  accordingly
        */
        
        if( mapParam->FindL( KLogId ,var ) )
            {
            TInt32 logid;
            CheckInputTypeL( &var, LIW::EVariantTypeDesC, KLogId.operator&() );
            if( var.AsDes()!=KNullDesC16 )
                {
                if( var.AsDes().Length() < 256 )
                    {
                    TBuf<256> Val2 = var.AsDes();
                    TLex lex(Val2);
                    TInt32 error = lex.Val( logid );
                    if( error!=KErrNone )
                        {
                        var.Reset();
                        IncorrectValueL( KLogId.operator&() );
                        User::Leave( SErrInvalidServiceArgument );
                        }
                    }
                else
                    {
                    var.Reset();
                    IncorrectValueL( KLogId.operator&() );
                    User::Leave( SErrInvalidServiceArgument );
                    }
                    
                if( logid>-1 )
                    {
                    CleanupStack::Pop( &var );
                    var.Reset();
                    CLogsEvent *event =  CLogsEvent :: NewL();
                    CleanupStack :: PushL( event ) ;
                    event->SetId( logid );
                    filter->SetEventL( event ) ;
                    CleanupStack :: Pop( event ) ;
                    delete event ;
                    filter->SetRequestType( EGetEvent ) ;
        
                    if( KLiwOptASyncronous & aCmdOptions )
                        {
                        if( aCallback!=NULL )
                            {
                            aTansId = MLiwNotifyCallback :: GetTransactionID() ;
                            LoggingInterfaceCB *cb = LoggingInterfaceCB :: NewL(aCallback) ;
                            CleanupStack :: PushL( cb ) ;
                            cb->SetRequestType( EGetEvent ) ;
                            iLogService->GetListL( aTansId, filter, cb) ;
                            CleanupStack :: Pop( cb ) ;
                            CleanupStack :: Pop( filter ) ;
                            delete filter ;
                            return NULL;
                            }
                        else
                            {
                            iErrorString = KErrMissingCallback.operator()().Alloc();
                            User::Leave( SErrInvalidServiceArgument );
                            }
                        }
                     else
                        {
                        CLogIter *Iter = iLogService->GetListL( filter ) ;
                        CleanupStack :: Pop( filter ) ;
                        delete filter;
                        return Iter ;
                        }
                    }
                  else
                      {
                      var.Reset();
                      User::Leave( SErrInvalidServiceArgument );
                      }
                }
            }
                
        if( mapParam->FindL(KRecentListKey , var) )
            {
            CheckInputTypeL( &var, LIW::EVariantTypeTInt32, KRecentListKey.operator&() );
        
            TInt Val3 = var.AsTInt32();
        
            switch( Val3 )
                {
                case EKLogNullRecentList :
                    {
                    filter->SetRecentList( KLogNullRecentList ) ;
                    break;
                    }
        
                case EKLogRecentIncomingCalls :
                    {
                    filter->SetRecentList( KLogRecentIncomingCalls );
                    break;
                    }
    
                case EKLogRecentOutgoingCalls :
                    {
                    filter->SetRecentList( KLogRecentOutgoingCalls );
                    break;
                    }
    
                case EKLogRecentMissedCalls :
                    {
                    filter->SetRecentList( KLogRecentMissedCalls );
                    break;
                    }
                    
                default :
                    {
                    var.Reset();
                    IncorrectValueL( KRecentListKey.operator&() );  
                    User::Leave( SErrInvalidServiceArgument );
                    break ;
                    }
                }
                    
                
            CleanupStack::Pop( &var );
            var.Reset();    
            
            filter->SetRequestType(EGetRecent) ;
        
            if ( KLiwOptASyncronous & aCmdOptions )
                 {
                 if( aCallback!=NULL )
                     {
                     aTansId = MLiwNotifyCallback :: GetTransactionID() ;
                     LoggingInterfaceCB *cb = LoggingInterfaceCB :: NewL( aCallback ) ;
                     CleanupStack :: PushL( cb ) ;
                     cb->SetRequestType( EGetRecent ) ;
                     iLogService->GetListL( aTansId, filter, cb) ;
                     CleanupStack :: Pop( cb ) ;
                     CleanupStack :: Pop( filter ) ;
                     delete filter ;
                     return NULL;
                     }
                 else
                     {
                     iErrorString = KErrMissingCallback.operator()().Alloc();
                     User::Leave( SErrInvalidServiceArgument );
                     }
                 }
             else
                 {
                 CLogIter *Iter = iLogService->GetListL( filter ) ;
                 CleanupStack :: Pop( filter ) ;
                 delete filter;
                 return Iter;
                 }
                    
            }
        
        if( mapParam->FindL( KPhoneNumberKey ,var ) )
            {
            CheckInputTypeL( &var, LIW::EVariantTypeDesC, KPhoneNumberKey.operator&() );
            filter->SetNumber( var.AsDes() ) ;
            }
        
        if( mapParam->FindL( KDirectionKey ,var ) )
            {
            CheckInputTypeL( &var, LIW::EVariantTypeTInt32, KDirectionKey.operator&() );
            TInt val = 0 ;
        
            switch( var.AsTInt32() )
                {
                case EIncomingEvent:
                    {
                    val = R_LOG_DIR_IN ;
                    break ;
                    }
        
                case EOutgoingEvent :
                    {
                    val = R_LOG_DIR_OUT ;
                    break ;
                    }
        
                case EIncomingEventAlternateline :
                    {
                    val = R_LOG_DIR_IN_ALT ;
                    break ;
                    }
        
                case EOutgoingEventAlternateline :
                    {
                    val = R_LOG_DIR_OUT_ALT  ;
                    break ;
                    }
        
                case  EFetchedEvent :
                    {
                    val = R_LOG_DIR_FETCHED ;
                    break ;
                    }
        
                case EMissedEvent :
                    {
                    val = R_LOG_DIR_MISSED ;
                    break ;
                    }
        
                case EMissedEventAlternateline :
                    {
                    val = R_LOG_DIR_MISSED_ALT ;
                    break ;
                    }
        
                default :
                    {
                    var.Reset();
                    IncorrectValueL( KDirectionKey.operator&() );  
                    User::Leave( SErrInvalidServiceArgument );
                    }
                }
        
            if( val )
                {
                filter->SetDirection( val ) ;
                }
            }
        
        if( mapParam->FindL(KDeliveryStatusKey ,var) )
            {
            CheckInputTypeL( &var, LIW::EVariantTypeTInt32, KDeliveryStatusKey.operator&() );
            TInt val = 0 ;
        
            switch( var.AsTInt32() )
                {
                case EStatusPending :
                    {
                    val =  R_LOG_DEL_PENDING ;
                    break ;
                    }
        
                case EStatusSent :
                    {
                    val = R_LOG_DEL_SENT ;
                    break ;
                    }
        
                case EStatusFalied :
                    {
                    val = R_LOG_DEL_FAILED ;
                    break ;
                    }
        
                case EStatusNone :
                    {
                    val = R_LOG_DEL_NONE  ;
                    break ;
                    }
        
                case  EStatusDone :
                    {
                    val = R_LOG_DEL_DONE ;
                    break ;
                    }
        
                case EStatusNotSent :
                    {
                    val = R_LOG_DEL_NOT_SENT ;
                    break ;
                    }
        
                case EStatusScheduled :
                    {
                    val = R_LOG_DEL_SCHEDULED ;
                    break ;
                    }
        
                default :
                    {
                    var.Reset();
                    IncorrectValueL( KDeliveryStatusKey.operator&() ); 
                    User::Leave( SErrInvalidServiceArgument ); 
                    }
                }
        
            if( val )
                {
                filter->SetStatus(val) ;
                }
            }
        
        if( mapParam->FindL( KFlagsKey , var ) )
            {
            CheckInputTypeL( &var, LIW::EVariantTypeTInt32, KFlagsKey.operator&() );
            TUint8 val = 0 ;
            
            switch( var.AsTInt32() )
                {
                case EKLogEventContactSearched :
                    {
                    val = KLogEventContactSearched ;
                    break ;
                    }
            
                case EKLogEventRead :
                    {
                    val = KLogEventRead ;
                    break ;
                    }
            
                default :
                    {
                    var.Reset();
                    IncorrectValueL( KFlagsKey.operator&() );  
                    User::Leave( SErrInvalidServiceArgument );
                    }
                }
            
            if( val )
                {
                filter->SetFlags( val ) ;
                }
            }
                
        if( mapParam->FindL( KEndTimeKey , var ) )
            {
            CheckInputTypeL( &var, LIW::EVariantTypeTTime, KEndTimeKey.operator&() );
            filter->SetEndTime( var.AsTTime() ) ;
            }
               
        if( mapParam->FindL( KRemotePartyKey , var ) )
            {
            CheckInputTypeL( &var, LIW::EVariantTypeDesC, KRemotePartyKey.operator&() );
            filter->SetRemoteParty( var.AsDes() ) ;
            }
                
        if( mapParam->FindL( KEventTypeKey , var ) )
            {
            CheckInputTypeL( &var, LIW::EVariantTypeTInt32, KEventTypeKey.operator&() );
            TUid val = TUid::Null() ;
            
            switch( var.AsTInt32() )
                {
                case EKLogCallEventType :
                    {
                    val =  TUid :: Uid(KLogCallEventType);
                    break ;
                    }
        
                case EKLogDataEventType :
                    {
                    val = TUid :: Uid (KLogDataEventType);
                    break ;
                    }
        
                case EKLogFaxEventType :
                    {
                    val = TUid :: Uid (KLogFaxEventType);
                    break ;
                    }
        
                case EKLogShortMessageEventType :
                    {
                    val = TUid :: Uid (KLogShortMessageEventType);
                    break ;
                    }
                    
               case EKLogPacketDataEventType :
                    {
                    val = TUid :: Uid (KLogPacketDataEventType) ;
                    break ;
                    }          
        
               default :
                    {
                    var.Reset();
                    IncorrectValueL( KFlagsKey.operator&() );  
                    User::Leave( SErrInvalidServiceArgument );
                    }
                }
                
            if( val!=TUid::Null() )
                {
                filter->SetEventType( val ) ;
                }
            }
        
        CleanupStack::Pop( &var );
        
        var.Reset();
        
        if ( KLiwOptASyncronous & aCmdOptions )
            {
            if( aCallback!=NULL )
                {
                aTansId = MLiwNotifyCallback :: GetTransactionID() ;
                LoggingInterfaceCB *cb = LoggingInterfaceCB :: NewL( aCallback ) ;
                CleanupStack :: PushL( cb ) ;
                cb->SetRequestType( EReadEvents ) ;
                iLogService->GetListL( aTansId, filter, cb ) ;
                CleanupStack :: Pop( cb ) ;
                CleanupStack :: Pop( filter ) ;
                delete filter ;
                return NULL;
                }
            else
                {
                iErrorString = KErrMissingCallback.operator()().Alloc();
                User::Leave( SErrInvalidServiceArgument );
                }
            }
        else
            {
            CLogIter *Iter = iLogService->GetListL(filter) ;
            CleanupStack :: Pop(filter) ;
            delete filter;
            return Iter;
            }
        }
    else
        {
        CLogsFilter *filter = CLogsFilter :: NewL() ;
        
        filter->SetRequestType( EReadEvents ) ;
        
        CleanupStack :: PushL( filter ) ;
        
        if ( KLiwOptASyncronous & aCmdOptions )
            {
            if( aCallback!=NULL )
                {
                aTansId = MLiwNotifyCallback :: GetTransactionID() ;
                LoggingInterfaceCB *cb = LoggingInterfaceCB :: NewL( aCallback ) ;
                CleanupStack :: PushL( cb ) ;
                cb->SetRequestType( EReadEvents ) ;
                iLogService->GetListL( aTansId , filter , cb ) ;
                CleanupStack :: Pop( cb ) ;
                CleanupStack :: Pop( filter ) ;
                delete filter ;
                return NULL;
                }
            else
                {
                iErrorString = KErrMissingCallback.operator()().Alloc();
                User::Leave( SErrInvalidServiceArgument );
                }
            }
        else
            {
            CLogIter *Iter = iLogService->GetListL(filter) ;
            CleanupStack :: Pop(filter) ;
            delete filter;
            return Iter;
            }
        }
    
    return 0;
    }

/**
 * Internal utility method, used for notification registration
 *
 * @param aCallback, callback address for notification requests.
 */

TInt CLoggingInterface :: RequestNotificationsL( const TLiwGenericParam *aParam ,
                                                 MLiwNotifyCallback *aCallback ,
                                                 TUint& aTransId,
                                                 TUint aCmdOptions )
    {
    TInt32 timeDelay = 0;
    
    CheckInputTypeL( &aParam->Value(), LIW::EVariantTypeMap ,KFilter.operator&() );
    
    const CLiwMap *notifymap = (aParam->Value()).AsMap() ;
    
     if( !notifymap )
        {
        MissingValueL( KFilter.operator&() );
        }
        
    TLiwVariant variant ;  
    
    if( notifymap->FindL( KDelayTime , variant ) ) 
        {
        CheckInputTypeL( &variant, LIW::EVariantTypeTInt32, KDelayTime.operator&() );
        timeDelay = variant.AsTInt32() ; 
        }
    else
        {
        MissingValueL( KDelayTime.operator&() );
        }   
        
    if( timeDelay < 0 )
        {
        variant.Reset();
        IncorrectValueL( KDelayTime.operator&() );
        User::Leave( SErrInvalidServiceArgument );
        }
        
    variant.Reset();
    
    TTimeIntervalMicroSeconds32 DelayInterval = timeDelay ;
    
    if( aCallback && ( KLiwOptASyncronous & aCmdOptions ) )
        {
        aTransId = MLiwNotifyCallback :: GetTransactionID() ;
        LoggingInterfaceCB *cb = LoggingInterfaceCB :: NewL( aCallback ) ;
        CleanupStack :: PushL( cb ) ;
        cb->SetRequestType( ENotification ) ;
        iLogService->NotifyUpdatesL( aTransId, DelayInterval, cb) ;
        CleanupStack :: Pop( cb ) ;
        return 0 ;
        }
    else
        {
        iErrorString = KErrMissingCallback.operator()().Alloc();
        User::Leave( SErrInvalidServiceArgument );
        }
    
    return 0;    
    }

 /**
  * Internal utility method, used for Delete from the core class
  *
  * @param aParam, input paramater containg the logid
  * @param aCallback, callback address for notification requests.
  * @param aTransId, transaction id.
  */
TInt CLoggingInterface::DeleteEventL( const TLiwGenericParam *aParam ,
                                      TUint& aTansId ,
                                      TUint aCmdOptions,
                                      MLiwNotifyCallback* aCallback )
    {
    TInt32 logid;
    
    CheckInputTypeL( &aParam->Value(), LIW::EVariantTypeMap ,KData.operator&() );
    
    const CLiwMap *delmap = (aParam->Value()).AsMap() ;
    
    if( !delmap )
        {
        MissingValueL( KData.operator&() );
        }
    
    TLiwVariant variant ;
    
    if( delmap->FindL( KLogId , variant ) )
        {
        CheckInputTypeL( &variant, LIW::EVariantTypeDesC, KLogId.operator&() );
        
        if( variant.AsDes().Length() < 256 )
            {
            TBuf<256> itemid = variant.AsDes();
            TLex lex(itemid);
            TInt32 error = lex.Val(logid);
        
            if( error!=KErrNone )
                {
                variant.Reset();
                IncorrectValueL( KLogId.operator&() );
                User::Leave( SErrInvalidServiceArgument );
                }
            }
        else
            {
            variant.Reset();
            IncorrectValueL( KLogId.operator&() );
            User::Leave( SErrInvalidServiceArgument );
            }
        }
    else
        {
        MissingValueL( KLogId.operator&() );
        }
    
    variant.Reset();
        
    if( KLiwOptASyncronous & aCmdOptions )
        {
        if( aCallback!=NULL )
            {
            aTansId = MLiwNotifyCallback :: GetTransactionID() ;
            LoggingInterfaceCB *cb = LoggingInterfaceCB :: NewL( aCallback ) ;
            CleanupStack :: PushL( cb ) ;
            cb->SetRequestType( EDeleteEvent ) ;
            iLogService->DeleteEventL( aTansId, logid, cb );
            CleanupStack :: Pop( cb ) ;
            return 0;
            }
        else
            {
            iErrorString = KErrMissingCallback.operator()().Alloc();
            User::Leave( SErrInvalidServiceArgument );
            }
        }
    else
        {
        return iLogService->DeleteEventL(logid );
        }
    
    return 0;
    }





