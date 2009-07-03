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
* Description:   Includes wrapper over Clogevent.
*
*/


#ifndef SAPIEVENT_H
#define SAPIEVENT_H

#include <logwrap.h>
#include <CNTDEF.H>

/**
* CLogsEvent:this is a wrapper class for the symbian CLogEvent class.
*/

class CLogsEvent : public CBase
    {
    public :

        /**
        * NewL: Two phased construction
        */

        IMPORT_C static CLogsEvent *NewL() ;

        /**
        * NewLC: Creates an instance of CLogSyncServiceClass
        * Two Phased constructor
        * returns newly allocated object.
        */

        static CLogsEvent* NewLC() ;

        /**
        * Default Destructor
        */

        ~CLogsEvent() ;

        /**
        * Sets unique id to identify event type.
        */

        inline  void SetEventType(TUid aEventTypeId)
            {
            iLogEvent->SetEventType(aEventTypeId);
            }

        /**
        * Sets the duration of the event.
        */

        inline void SetDuration(TLogDuration aDuration)
            {
            iLogEvent->SetDuration(aDuration);
            }
            
        /**
        * Sets the durationType of the event.
        */    
            
        inline void SetDurationType(TLogDurationType aDurationType)
            {
            iLogEvent->SetDurationType( aDurationType );
            }
    
        /**
        * Sets the subject of the event.
        */

        inline void SetSubject(const TDesC &aSubject)
            {
            iLogEvent->SetSubject(aSubject);
            }

        /**
        * Sets the time of the event.
        */

        inline void SetTime(const TTime &aTime)
            {
            iLogEvent->SetTime(aTime);
            }

        /**
        * Sets the number associated with the event..
        */

        inline void SetNumber(const TDesC &aNumber)
            {
            iLogEvent->SetNumber(aNumber);
            }

        /**
        * Sets the remote party associated with the event.
        */

        inline void SetRemoteParty(const TDesC &aRemote)
            {
            iLogEvent->SetRemoteParty(aRemote);
            }

        /**
        * Sets the Direction of the .event
        */

        IMPORT_C void SetDirection(TInt aDirection) ;


        /**
        * Sets the contact id.
        */

        inline void SetContact(TContactItemId aContact)
            {
            iLogEvent->SetContact(aContact);
            }

        /**
        * Sets description of event type
        */

        inline void SetDescription(const TDesC &aDescription)
            {
            iLogEvent->SetDescription(aDescription);
            }

        /**
        * Sets data of event type
        */
        inline void SetDataL(const TDesC8 &aData)
            {
            iLogEvent->SetDataL(aData);
            }

        /**
        * Sets link value
        */

        inline void SetLink(TLogLink aLink)
            {
            iLogEvent->SetLink(aLink);
            }

        /**
        *  Sets status of event
        */

        IMPORT_C void SetStatus(TInt aStatus) ;


        /**
        * Sets unique id to identify event type.
        *  @param aEvent, event details to be copied
        */

        inline void SetEvent(const CLogEvent& aEvent)
            {
            iLogEvent->CopyL(aEvent) ;
            }

        /**
        *  get logid
        */

        inline TLogId Id()
            {
            return iLogEvent->Id() ;
            }

        /**
        *  copy function
        */

        inline  void Copy(CLogEvent* aEvent)
            {
            iLogEvent->CopyL(*aEvent);
            }

        /**
        *  gets eventtype
        */

        TUid getEventType() const
            {
            return iLogEvent->EventType();
            }

        /**
        *  gets eventduration
        */

        TLogDuration getDuration() const
            {
            return iLogEvent->Duration();
            }

        /**
        *  gets subject
        */

        const TDesC& getSubject() const
            {
            return iLogEvent->Subject() ;
            }

        /**
        *  gets time
        */

        TTime getTime() const
            {
            return iLogEvent->Time();
            }

        /**
        *  gets number
        */

        const TDesC& getNumber() const
            {
            return iLogEvent->Number();
            }

        /**
        *  gets remoteparty
        */

        const TDesC& getRemoteParty() const
            {
            return iLogEvent->RemoteParty();
            }

        /**
        *  gets direction
        */

        const TDesC& getDirection() const
            {
            return iLogEvent->Direction();
            }

        /**
        *  gets contactid
        */

        TContactItemId getContact() const
            {
            return iLogEvent->Contact();
            }

        /**
        *  gets description
        */

        const TDesC& getDescription() const
            {
            return iLogEvent->Description();
            }

        /**
        *  gets data
        */


        const TDesC8& getDataL() const
            {
            return iLogEvent->Data();
            }

        /**
        *  gets linkvalue
        */


        TLogLink getLink() const
            {
            return iLogEvent->Link();
            }

        /**
        *  gets status
        */

        const TDesC& getStatus() const
            {
            return iLogEvent->Status();
            }

        /**
        * getEvents: Gets the event .
        */

        inline CLogEvent* getEvent()
            {
            return iLogEvent ;
            }

        /**
        *  setid function
        */

        inline void SetId(TLogId aId)
            {
            iLogEvent->SetId(aId);
            }

        /**
        * Gets the flag associated with the event
        */

        inline TLogFlags Flags()
            {
            return iLogEvent->Flags() ;
            }

        /**
        * Gets the flags associated with the event
        * @param aFlags , flags to be set
        */

        inline void SetFlags(TLogFlags aFlags)
            {
            iLogEvent->SetFlags(aFlags) ;
            }

    protected:

        /**
        * ConstructL(): Internal method to construct members
        */

        void ConstructL() ;

        /**
        * Default constructor
        */

        CLogsEvent() ;

    private:

        /**
        *  contains the details of an event
        */

        CLogEvent* iLogEvent;

        /**
        * Required for the Setting Direction and the status for
        * the event
        */

        RFs iFs ;
        CLogClient *iLogClient ;

    };


#endif