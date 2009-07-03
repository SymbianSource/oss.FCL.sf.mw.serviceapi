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


#ifndef __SYSACCESSORYREQUEST_H__
#define __SYSACCESSORYREQUEST_H__

//INCLUDES
#include <AccessoryServer.h>
#include <AccessoryConnection.h>

#include "sysinfo.h"
#include "activerequests.h"

// CONSTANT DECLARATIONS

// FORWARD DECLARATIONS

/**
*  @ref CAccessory active object class to handle accessory notifications
*
*  @lib   sysinfoservice.lib
*  @since 3.2
*/
NONSHARABLE_CLASS(CAccessory): public CActiveRequest
    {
    public:
    /**
    * Two-phased constructor.
    *
    * @return A new instance of this class.
    */    
    static CAccessory* NewL( const TSysRequest& aRequest );
    /**
    * Destructor.
    */
    ~CAccessory();

    private:
    /**
    * C++ default constructor.
    */
    CAccessory( TSysRequest::TRequestType aReqType, TInt32 aTransID,
                                            ISystemObserver* aObsrvr );

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL();

    private:
    /**
    * On return aGenId consists of disconnected accessory.
    */
    void DisConnectedAccessoryL(TAccPolGenericID& aGenId);

    public:	
    /**
    * Issues accesssory request.
    */
    TInt Request();

    protected: // from CActive
    void RunL();
    void DoCancel();

    private:	// DATA

    //Handle to accessory server
    RAccessoryServer        iAccSrv;
    RAccessoryConnection    iAccessoryConnection;
    // current and old accssory ID list.
    TAccPolGenericIDArray   iGenIdArrayOld;
    TAccPolGenericIDArray   iGenIdArrayCur;
    // current and old accssory count.
    TInt                    iAccCountOld;
    TInt                    iAccCountCur;

    CAccessoryInfo::TAccessoryType  iAccType;
    CAccessoryInfo::TAccessoryState iAccState;
    };

#endif __SYSACCESSORYREQUEST_H__