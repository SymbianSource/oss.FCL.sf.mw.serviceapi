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
* Description:  Implements logging service handler (This will be part of
*                                   Ecom plugin.
*
*/


#include <LiwVariant.h>
#include <logwrap.h>
#include <logwrap.hrh>
#include <LOGCLIENTCHANGEOBSERVER.H>

#include "logiter.h"
#include "logginginterface.h"
#include "loggingasyncservice.h"
#include "loggingevent.h"
#include  <utf.h>
#include "liwlogiter.h"

/**
 * Two phase constructor implementation of the
 *  log iterator
 */
CLiwLogIter * CLiwLogIter :: NewL( CLogIter *aIter )
    {
    CLiwLogIter* self = CLiwLogIter :: NewLC( aIter ) ;
    CleanupStack :: Pop( self ) ;
    return self ;
    }

/**
 * Two phase constructor implementation of the
 *  log iterator
 */
CLiwLogIter * CLiwLogIter :: NewLC( CLogIter *aIter )
    {
    CLiwLogIter *self = new ( ELeave ) CLiwLogIter() ;
    CleanupStack :: PushL( self ) ;
    self->ConstructL( aIter ) ;
    return self ;
    }

/**
 * ConstructL , function to construct the members of the CLiwLogIter
 */
void CLiwLogIter :: ConstructL( CLogIter *aIter )
    {
    iLogIter = aIter ;
    }

/**
 * Default constructor
 */

CLiwLogIter :: CLiwLogIter()
    {
    }

/**
 * Default Desturctor
 */
CLiwLogIter :: ~CLiwLogIter()
    {
    delete iLogIter ;
    }

/**
 * Resets the iterator. The service provider should provide a concrete
 * implementation to reset the iterator.
 *
 */
EXPORT_C  void CLiwLogIter :: Reset()
    {
    if( iLogIter )
        {
        iLogIter->Reset();    
        }
    }

/**
 * Iterates over the collection entries to fetch the next data element.
 * The service provider should provide a concrete implementation
 * for this method.
 *
 * @param aEntry contains the next data element and its corresponding data type
 *
 * @return false if there are no more data elements to be fetched;
 * true otherwise
 */
EXPORT_C TBool CLiwLogIter :: NextL(TLiwVariant& aEntry)
    {
    
    /**
    * In case of empty iterator return false
    */
    
    if( !iLogIter )
        {
        return EFalse ;
        }
    
    CLogsEvent *event = iLogIter->NextL() ;
    
    if( !event )
        {
        return EFalse ;
        }
    
    CleanupStack::PushL(event);
    
    CLiwDefaultMap *evntmap = CLiwDefaultMap :: NewL() ;
    
    CleanupClosePushL( *evntmap );
    
    /**
    * Extract all the event details form CLogsEvent object
    * and push it to the aEntry
    */
    
    TInt32 val = 0 ;
    
    switch( (event->getEventType()).iUid )
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
    
    evntmap->InsertL(KRemotePartyKey , TLiwVariant(event->getRemoteParty())) ;
    
    evntmap->InsertL(KEventDurationKey ,TLiwVariant((TInt32)event->getDuration())) ;
    
    evntmap->InsertL(KEventTimeKey , TLiwVariant(event->getTime())) ;
    
    val = 0 ;
    
    /**
    * Need to convert status to int value
    */
    if( ( ( event->getStatus() ).Compare( KStatusPending ) ) == KErrNone )
        {
        val = CLoggingInterface :: EStatusPending ;
        }
    else if( ( ( event->getStatus() ).Compare( KStatusSent ) ) == KErrNone )
        {
        val =CLoggingInterface :: EStatusSent ;
        }
    else if( ( ( event->getStatus() ).Compare( KStatusFalied ) ) == KErrNone )
        {
        val = CLoggingInterface :: EStatusFalied ;
        }
    else if( ( ( event->getStatus() ).Compare( KStatusNone ) ) == KErrNone )
        {
        val = CLoggingInterface :: EStatusNone;
        }
    else if( ( ( event->getStatus() ).Compare( KStatusDone ) ) == KErrNone )
        {
        val = CLoggingInterface :: EStatusDone;
        }
    else if( ( ( event->getStatus() ).Compare( KStatusNotSent ) ) == KErrNone )
        {
        val = CLoggingInterface :: EStatusNotSent;
        }
    else if( ( ( event->getStatus() ).Compare( KStatusScheduled ) ) == KErrNone )
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
    
    evntmap->InsertL(KSubjectKey , TLiwVariant(event->getSubject())) ;
    
    evntmap->InsertL(KPhoneNumberKey , TLiwVariant(event->getNumber())) ;
    
    evntmap->InsertL(KDescriptionKey , TLiwVariant (event->getDescription())) ;
    
    evntmap->InsertL(KLinkKey , TLiwVariant((TInt32)event->getLink())) ;
    
    val = 0 ;
    
    if( event->Flags() & KLogEventContactSearched )
        {
        val = CLoggingInterface :: EKLogEventContactSearched ;
        }
    else if( event->Flags() & KLogEventRead )
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
    
    TInt32 ret =  event->Id();
    TBuf<8> des;
    des.Num(ret);
    evntmap->InsertL(KLogId , TLiwVariant( des)) ;
    
    val = 0 ;
    
    if( ( ( event->getDirection() ).Compare( KIncomingEvent ) ) == KErrNone )
        {
        val = CLoggingInterface :: EIncomingEvent ;
        }
    else if( ( ( event->getDirection() ).Compare( KOutgoingEvent ) ) == KErrNone )
        {
        val = CLoggingInterface :: EOutgoingEvent ;
        }
    else if( ( ( event->getDirection() ).Compare( KIncomingEventAlternateline ) ) == KErrNone )
        {
        val = CLoggingInterface :: EIncomingEventAlternateline ;
        }
    else if( ( ( event->getDirection() ).Compare( KOutgoingEventAlternateline ) ) == KErrNone )
        {
        val = CLoggingInterface :: EOutgoingEventAlternateline;
        }
    else if( ( ( event->getDirection() ).Compare( KFetchedEvent ) ) == KErrNone )
        {
        val = CLoggingInterface :: EFetchedEvent;
        }
    else if( ( ( event->getDirection() ).Compare( KMissedEvent ) ) == KErrNone )
        {
        val = CLoggingInterface :: EMissedEvent;
        }
    else if( ( ( event->getDirection() ).Compare( KMissedEventAlternateline ) ) == KErrNone )
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
        
    evntmap->InsertL(KEventDataKey , TLiwVariant(event->getDataL()));
    
    aEntry.SetL( evntmap ) ;
    CleanupStack :: Pop( evntmap ) ;
    evntmap->DecRef();
    CleanupStack::Pop( event );
    delete event;
    return true ;
    }

/**
 * Default equality operator implementation
 *
 * @param aIterable the iterator instance to be compared
 *
 */
 
EXPORT_C  TBool CLiwLogIter :: operator==(CLiwIterable&/* aIterable*/)
    {
    /**
     * Currently Not Implemented
     */
    return true ;
    }

 //End of File
