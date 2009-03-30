/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  class implementation
*
*/

#include <activitymanager.h>

#include "sysinfoservice.h"
#include "sysuseractivity.h"
#include "entitykeys.h"
#include "sysrequest.h"

using namespace SysInfo;
// --------------------------------------------------------------------
// CUserActivity::CUserActivity()
// C++ default constructor.
// --------------------------------------------------------------------
//
CUserActivity::CUserActivity( TSysRequest::TRequestType aReqType,
                        TInt32 aTransID,ISystemObserver* aObsrvr )
                        :CActiveRequest(aReqType,aTransID,aObsrvr)
    {
    	
    }
	
// --------------------------------------------------------------------
// CUserActivity::~CUserActivity()
// Destructor.
// --------------------------------------------------------------------
//
CUserActivity::~CUserActivity()
    {
    delete iActivityManager;
    }

// --------------------------------------------------------------------
// CUserActivity::NewL()
// Two-phased constructor, returns instance of this class.
// --------------------------------------------------------------------
//
CUserActivity* CUserActivity::NewL(const TSysRequest& aRequest)
    {
    CUserActivity* self;
    self = new (ELeave) CUserActivity(aRequest.RequestType(),
                        aRequest.TransactionID(),aRequest.Observer());

    CleanupStack::PushL(self);
    self->ConstructL (aRequest);
    CleanupStack::Pop(self);

    return self;
	}

// --------------------------------------------------------------------
// CUserActivity::ConstructL()
// 2nd Phase constructor to allocate required resources for this obj.
// --------------------------------------------------------------------
//
void CUserActivity::ConstructL(const TSysRequest& aRequest)
    {
    //supportes only notifications.
    if(TSysRequest::ENotification != RequestType())
        User::Leave(KErrNotSupported);

    //Validate input data. this is mandatatory input.
    const CSysData* Input = aRequest.SystemData();
    if(Input)
        {
        if( CSysData::EStatus == Input->DataType() )
        	iTimeout = ((CStatus*)Input)->Status();
        else
        	User::Leave(KErrArgument);
        }
    else
        User::Leave(KErrArgument);

    iActivityManager = CUserActivityManager::NewL( CActive::EPriorityStandard );
    }
	
// --------------------------------------------------------------------
// CUserActivity::Request()
// Issues user activity notification request.
// --------------------------------------------------------------------
//
TInt CUserActivity::Request()
    {
    if(iTimeout <= 0)
        return KErrArgument;
    else
        {
        if( !iActivityManager->IsActive() )
            iActivityManager->Start(iTimeout,
            TCallBack(HandleInactiveEventL,this ),
            TCallBack(HandleActiveEventL, this ) );
        
        return KErrNone;
        }
    }

// --------------------------------------------------------------------
// CUserActivity::RunL()
// never been called. This is not an active object implementation.
// --------------------------------------------------------------------
//
void CUserActivity::RunL()
    {
    User::Leave(KErrGeneral);
    }

// --------------------------------------------------------------------
// CUserActivity::DoCancel()
// never been called. This is not an active object implementation.
// --------------------------------------------------------------------
//
void CUserActivity::DoCancel()
    {
    }

// --------------------------------------------------------------------
// CUserActivity::HandleInactiveEventL()
// call back handle to handle In activity event.
// --------------------------------------------------------------------
//
TInt CUserActivity::HandleInactiveEventL(TAny* aPtr)
    {
    ((CUserActivity*)aPtr)->HandleReqResponseL(EUSERINACTIVITY);
    return KErrNone; 
    }

// --------------------------------------------------------------------
// CUserActivity::HandleActiveEventL()
// call back handle to handle user activity event.
// --------------------------------------------------------------------
//
TInt CUserActivity::HandleActiveEventL(TAny* aPtr)
    {
    ((CUserActivity*)aPtr)->HandleReqResponseL(EUSERACTIVITY);
    return KErrNone;
    }

// --------------------------------------------------------------------
// CUserActivity::HandleReqResponseL()
// gets called whenever an user activity/inactivity event triggered.
// --------------------------------------------------------------------
//
void CUserActivity::HandleReqResponseL(TEvent aEvent)
    {
    CStatus* status = CStatus::NewL(aEvent);
    CleanupStack::PushL(status);

    TRAP_IGNORE(SystemObserver()->HandleResponseL(KDisplay, KUserInactivity,
                status, TransactionID(), RequestType()));

    CleanupStack::Pop(status);
    }

// End of file.
