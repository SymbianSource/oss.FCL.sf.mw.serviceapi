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
* Description:  Includes logging core class filter methods.
*
*/

#ifndef LOGGINGFILTER_H
#define LOGGINGFILTER_H

#include <cntdef.h>

/**
* Forward Declarations
*/

class CLogFilter ;
class CLogsEvent ;

/**
* CLogsFilter:this is a wrapper class for the symbian CLogFilter class.
*/

class CLogsFilter : public CBase
    {
    public :

        /**
        * NewL and NewLC method to construct the sapiFilter
        */

        IMPORT_C static CLogsFilter* NewL() ;

        static CLogsFilter* NewLC() ;

        /**
        * Gets the associated filter
        */

        inline CLogFilter* getFilter()
            {
            return iLogFilter ;
            }

        /**
        * Sets the filter
        */

        inline void setFilter(CLogFilter& aLogFilter)
            {
            aLogFilter.Copy(*iLogFilter);
            }

        /**
        * Copy function, does a deep copy of SapiFilter
        */

        inline void Copy(CLogsFilter& aLogFilter)
            {
            (aLogFilter.getFilter())->Copy(*iLogFilter) ;
            }

        /**
        * Clears the flags to be used by filter
        */

        inline void ClearFlags(TLogFlags aFlags)
            {
            iLogFilter->ClearFlags(aFlags) ;
            }

        /**
        * Returns Null Fields in the filter
        */

        inline TUint32 NullFields()
            {
            return iLogFilter->NullFields() ;
            }

        /**
        * Sets the Null Fields in the filter
        * These are the fields that the filter expects to be NULL in the database.
        *
        */

        inline void SetNullFields(TUint32 aNullFields)
            {
            iLogFilter->SetNullFields(aNullFields) ;
            }

        /**
        * Gets the event type used by this filter
        */
        inline TUid EventType()
            {
            return iLogFilter->EventType() ;
            }

        /**
        * Sets the event type to be used by this filter
        *
        * @param aEventType, event type to be set
        */

        inline void SetEventType(TUid aEventType)
            {
            iLogFilter->SetEventType(aEventType) ;
            }

        /**
        * Gets the Remot party used by the filter
        */

        inline const TDesC& RemoteParty()
            {
            return iLogFilter->RemoteParty() ;
            }

        /**
        * Sets the remot party used by this filter
        *
        * @param TDesC aRemotParty, Remot party description
        */

        inline void SetRemoteParty(const TDesC &aRemoteParty)
            {
            iLogFilter->SetRemoteParty(aRemoteParty) ;
            }

        /**
        * Direction, Get the direction of this filter
        * INCOMING , OUTGOING
        */

        inline const TDesC& Direction()
            {
            return iLogFilter->Direction() ;
            }

        /**
        * Sets the direction of the filter
        *
        * @param aDirection , direction of the filter
        */

        IMPORT_C void SetDirection(TInt aDirection) ;

        /**
        * DurationType Gets the log duration used by the filter
        */

        inline TLogDurationType DurationType()
            {
            return iLogFilter->DurationType() ;
            }

        /**
        * SetDurationType, sets the duration type used by this filter
        *
        * @param aDurationType, duration type to be set
        */

        inline void SetDurationType(TLogDurationType aDurationType)
            {
            iLogFilter->SetDurationType(aDurationType) ;
            }

        /**
        * Status, gets the Delivery status used by this filter
        */

        inline const TDesC &Status()
            {
            return iLogFilter->Status() ;
            }

        /**
        * SetStatus, sets the Delivery status used by this filter
        *
        * @param aStatus, status to be set for this filter
        */

        IMPORT_C void SetStatus(TInt aStatus) ;


        /**
        * SetRequestType, set the request type (GetEvent or GetList)
        *
        * @param aTaskId, Task Id for this filter
        */

        inline void SetRequestType(TInt aTaskId)
            {
            iTaskId = aTaskId ;
            }

        /**
        * GetRequestType, gets the request type of
        */

        inline TInt GetRequestType(void)
            {
            return iTaskId ;
            }

        /**
        * GetEvent, gets the request type of
        */

        inline CLogsEvent* GetEvent(void)
            {
            return iEvent  ;
            }

        /**
        * SetEvent, Sets the event for the filer
        *
        * @param aEvent , event to be set
        */

        IMPORT_C void SetEventL(CLogsEvent *aEvent) ;


        /**
        * GetRecentList , gets the recent list
        */

        inline TLogRecentList GetRecentList(void)
            {
            return iRecentList;
            }

        /**
        * SetRecentList, sets the recent List for recent view
        *
        * @param aRecentList, recent list to be set for recent view
        */

        inline void SetRecentList(TLogRecentList aRecentList)
            {
            iRecentList = aRecentList;
            }

        /**
        * SetNumber, sets the number view filter
        *
        * @param aNumber, number to be set
        */

        inline void SetNumber (const TDesC& aNumber)
            {
            iLogFilter->SetNumber(aNumber) ;
            }

        /**
        * get the number used by the filter
        */

        inline const TDesC& Number()
            {
            return iLogFilter->Number() ;
            }

        /**
        * Set EndTime for the event filter
        *
        * @param aEndTime, EndTime to be set
        */

        inline void SetEndTime(const TTime& aEndTime)
            {
            iLogFilter->SetEndTime(aEndTime) ;
            }

        /**
        *  get function
        */

        TTime getTime() const
            {
            return iLogFilter->EndTime();
            }

        /**
        * Set the contact id
        *
        * @param aContactId , contact id to  be set
        */

        inline void SetContact(TContactItemId aId)
            {
            iLogFilter->SetContact(aId) ;
            }

        /**
        * get the contact id
        */

        TContactItemId getContact() const
            {
            return iLogFilter->Contact();
            }

        /**
        * Gets the flag associated with the event
        */

        inline TLogFlags Flags()
            {
            return iLogFilter->Flags() ;
            }

        /**
        * Gets the flags associated with the event
        * @param aFlags , flags to be set
        */

        inline void SetFlags(TLogFlags aFlags)
            {
            iLogFilter->SetFlags(aFlags) ;
            }

        /**
        * Default Destructor
        */

        ~CLogsFilter() ;


    protected :

        /**
        * Default consturctor
        */

        CLogsFilter() ;

        /**
        * ConstructL: Function to consturct members of Filter class
        */

        void ConstructL() ;

    private :

        CLogFilter *iLogFilter ;
        //  CLogViewRecent *iRecentList ;
        TLogRecentList iRecentList;
        CLogsEvent*    iEvent ;
        /**
        * To fetch direction strings and status strings
        */
        CLogClient*     iLogClient ;
        RFs        iFs ;
        TInt iTaskId  ;

    } ;

#endif