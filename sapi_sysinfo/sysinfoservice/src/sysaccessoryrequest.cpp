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

#include <AccessoryConnection.h>

#include "sysinfoservice.h"
#include "sysaccessoryrequest.h"
#include "entitykeys.h"
#include "sysrequest.h"

using namespace SysInfo;

// --------------------------------------------------------------------
// CAccessory::CAccessory()
// C++ default constructor.
// --------------------------------------------------------------------
//
CAccessory::CAccessory( TSysRequest::TRequestType aReqType, TInt32 aTransID,
                    ISystemObserver* aObsrvr ): CActiveRequest(
                    aReqType, aTransID, aObsrvr), iAccCountOld(0),
                    iAccState(CAccessoryInfo::EDisconnected)
    {
    }

// --------------------------------------------------------------------
// CAccessory::~CAccessory()
// destructor.
// --------------------------------------------------------------------
//
CAccessory::~CAccessory()
    {
    Cancel();
    iAccessoryConnection.CloseSubSession();
    iAccSrv.Disconnect();
    }

// --------------------------------------------------------------------
// CAccessory::NewL()
// Two-phased constructor, returns instance of this class.
// --------------------------------------------------------------------
//
CAccessory* CAccessory::NewL(const TSysRequest& aRequest)
    {
    CAccessory* self;
    self = new (ELeave) CAccessory(aRequest.RequestType(),
                            aRequest.TransactionID(), aRequest.Observer());

    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }
	
// --------------------------------------------------------------------
// CAccessory::ConstructL()
// 2nd Phase constructor to allocate required resources for this obj.
// --------------------------------------------------------------------
//
void CAccessory::ConstructL()
    {
    //Supportes Only Notifications.
    if( TSysRequest::ENotification != RequestType())
        User::Leave(KErrNotSupported);

    User::LeaveIfError(iAccSrv.Connect());
    TInt err = iAccessoryConnection.CreateSubSession(iAccSrv);
    if( err )
        {
        iAccSrv.Disconnect();
        User::Leave(err);
        }
    }
	
// --------------------------------------------------------------------
// CAccessory::Request()
// Issues accesssory request.
// --------------------------------------------------------------------
//
TInt CAccessory::Request()
    {
    if(!iAccCountOld)
        {
        // get all connected accessories into iGenIdArrayOld.
        iAccessoryConnection.GetAccessoryConnectionStatus(iGenIdArrayOld);
        //Store Connection Count.
        iAccCountOld = iGenIdArrayOld.Count();
        }

    //Issue request.
    if( !IsActive() )
        {
        iAccessoryConnection.NotifyAccessoryConnectionStatusChanged(iStatus, 
                                                                iGenIdArrayCur);
        SetActive ();
        }
    return KErrNone;
    }
	
// --------------------------------------------------------------------
// CAccessory::RunL()
// Gets called in event of request completion or error situation.
// --------------------------------------------------------------------
//
void CAccessory::RunL()
    {
    TSysRequest::TRequestType ReqType = RequestType();
    TInt32 transId = this->TransactionID();

    // get accessory count.
    iAccCountCur = iGenIdArrayCur.Count();
    iAccCountOld = iGenIdArrayOld.Count();

    // Check if it a was a connect or a disconnect
    if( iAccCountCur > iAccCountOld )
        iAccState = CAccessoryInfo::EConnected;
    else
        iAccState = CAccessoryInfo::EDisconnected;

    TInt error(iStatus.Int());
    
    if(error == KErrNone)
        {
        CAccessoryInfo* accInfo = NULL;
        //newly connected accessory will be at index '0'.
        if(iAccState == CAccessoryInfo::EConnected)
            {
            TAccPolGenericID ConnectedID;
            ConnectedID = iGenIdArrayCur.GetGenericIDL(0);
            accInfo = CAccessoryInfo::NewL(ConnectedID,iAccState);
            }
        else
            {
            TAccPolGenericID DisConnectedID;
            //get DisConnected accessory ID.
            DisConnectedAccessoryL(DisConnectedID);
            accInfo = CAccessoryInfo::NewL(DisConnectedID,iAccState);
            }

        CleanupStack::PushL(accInfo);
        TRAP_IGNORE(SystemObserver()->HandleResponseL(KGeneral, KAccessoryStatus,
                                        accInfo, transId, RequestType(), error));
        CleanupStack::Pop(accInfo);
        //Re-Issue request
        Request();
        }
    else
        {
        TRAP_IGNORE(SystemObserver()->HandleResponseL(KGeneral, KAccessoryStatus, 
                                        NULL, transId, RequestType(), error));
        }
    //copy current list to old list.
    iGenIdArrayOld = iGenIdArrayCur;
    }

// --------------------------------------------------------------------
// CAccessory::DoCancel()
// Gets called in event of request completion or error situation.
// --------------------------------------------------------------------
//
void CAccessory::DoCancel()
    {
    if(IsActive())
        iAccessoryConnection.CancelNotifyAccessoryConnectionStatusChanged();
    }
	
// --------------------------------------------------------------------
// CAccessory::DisConnectedAccessoryL()
// retruns disconnected accessory GenericID.
// --------------------------------------------------------------------
//
void CAccessory::DisConnectedAccessoryL(TAccPolGenericID& aGenId)
    {
    for(TInt i=0; i<iAccCountOld; i++)
        {
        TAccPolGenericID DisConnected;
        //Take a GenericID in old list and search for it in cur list.
        //if present, continue with next.
        DisConnected = iGenIdArrayOld.GetGenericIDL(i);
        aGenId= DisConnected;

        for(TInt j=0; j<iAccCountCur;j++)
            {
            //stop searching when a missing entry in old list is found.
            if( DisConnected.UniqueID() != 
                        (iGenIdArrayCur.GetGenericIDL(j)).UniqueID() )
                {
                return;
                }
            }
        }
    }

// End of file.
