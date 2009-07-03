/*
* Copyright (c) 2005-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  describes system information notifiers.
*
*/


#ifndef __SYSUSERACTIVITY_H__
#define __SYSUSERACTIVITY_H__

//INCLUDES
#include "sysinfo.h"
#include "activerequests.h"

// FORWARD DECLARATIONS
class CUserActivityManager;


/**
*  @ref CUserActivity active object class to handle user activity and user 
*   inactivity notifications.
*
*  @lib sysinfoservice.lib
*  @since S60 3.2
*/
NONSHARABLE_CLASS(CUserActivity): public CActiveRequest
    {
    public:
    /**
    * Two-phased constructor.
    *
    * @return A new instance of this class.
    */    
    static CUserActivity* NewL(const TSysRequest& aRequest);
    /**
    * Destructor.
    */
    ~CUserActivity();

    private:
    // Enumeration of user events.
    enum TEvent
        {
        EUSERACTIVITY,
        EUSERINACTIVITY
        };

    /**
    * C++ default constructor.
    */
    CUserActivity( TSysRequest::TRequestType aReqType,TInt32 aTransID,
                                                ISystemObserver* aObsrvr );

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL(const TSysRequest& aRequest);

    public:	
    /**
    * Issues user activity and inactivity request.
    */
    TInt Request();

    protected: // from CActive
    void RunL();
    void DoCancel();

    protected:
    /**
    * call back handle to handle inactivity event.
    */
    static	TInt HandleInactiveEventL(TAny* aPtr);
    /**
    * call back handle to handle activity event.
    */
    static	TInt HandleActiveEventL(TAny* aPtr);
    /**
    * call back handle to handle activity event.
    */	
    void HandleReqResponseL(TEvent aEvent);

    private:	// DATA

    //Activity manager handle.
    CUserActivityManager*       iActivityManager;

    // TimeOut value for user inactivity notification.
    TInt                        iTimeout;
    };

#endif __SYSUSERACTIVITY_H__