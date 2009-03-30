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
* Description:   Declars  logging Iterator 
*
*/


#ifndef LIWLOGITER_H
#define LIWLOGITER_H

/**
* LIT Declarations for direction and Status
*/

_LIT(KIncomingEvent , "Incoming") ;
_LIT(KOutgoingEvent , "Outgoing") ;
_LIT(KIncomingEventAlternateline , "Incoming on alternate line") ;
_LIT(KOutgoingEventAlternateline  , "Outgoing on alternate line") ;
_LIT(KFetchedEvent , "Fetched") ;
_LIT(KMissedEvent , "Missed call") ;
_LIT(KMissedEventAlternateline , "Missed call on alternate line") ;
_LIT(KStatusPending , "Pending") ;
_LIT(KStatusSent , "Sent") ;
_LIT(KStatusFalied , "Failed") ;
_LIT(KStatusNone , "No delivery") ;
_LIT(KStatusDone , "Delivered") ;
_LIT(KStatusNotSent , "Not sent") ;
_LIT(KStatusScheduled , "Scheduled") ;

/**
* Forward declarations
*/
class CLiwIterable ;
class CLogIter ;

class CLiwLogIter : public CLiwIterable
    {
    public:

        /**
        * Resets the iterator. The service provider should provide a concrete
        * implementation to reset the iterator.
        *
        */
        IMPORT_C void Reset() ;

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
        IMPORT_C TBool NextL( TLiwVariant& aEntry ) ;

        /**
        * Default equality operator implementation
        * 
        * @param aIterable the iterator instance to be compared
        * 
        */
        IMPORT_C  TBool operator==( CLiwIterable& aIterable );

        /**
        * Two phase constructors 
        */
        static  CLiwLogIter * NewL( CLogIter *aIter ) ;
        
        /**
        * NewLC: Creates an instance of CLiwLogIterClass
        * Two Phased constructor
        * returns newly allocated object.
        */
        static  CLiwLogIter * NewLC( CLogIter *aIter );
        
        /**
        * SetCLogIter 
        */
        inline void  SetCLogIter( CLogIter *aIter )
            {
            iLogIter = aIter  ;
            }

    protected :

        /**
        * ConstructL function to construct the members of the class
        */
        void ConstructL( CLogIter *aIter ) ;

        /**
        * Default Constructor
        */
        CLiwLogIter() ;

        /**
        * Default destructor
        */
        ~CLiwLogIter() ; 

    private :
    
        /**
        * private member
        */
        CLogIter *iLogIter  ;

    }  ;

#endif 	