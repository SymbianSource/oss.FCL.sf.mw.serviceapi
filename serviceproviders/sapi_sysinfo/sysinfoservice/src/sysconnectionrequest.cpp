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


#include "sysinfoservice.h"
#include "sysconnectionrequest.h"
#include "sysrequest.h"

const TInt KGranularity(2);

// --------------------------------------------------------------------
// CConnection::CConnection()
// C++ default constructor.
// --------------------------------------------------------------------
//
CConnection::CConnection( TSysRequest::TRequestType aReqType, TInt32 aTransID,
                            ISystemObserver* aObsrver):
                            CActiveRequest(aReqType,aTransID,aObsrver),
                            iConnectionCount(0), iConnectionIndex(1),
                            iConnectionInfoArray(KGranularity),	
                            iConnectionInit(ETrue)
    {
    }

// --------------------------------------------------------------------
// CConnection::~CConnection()
// Destructor.
// --------------------------------------------------------------------
//
CConnection::~CConnection()
    {
    Cancel();

    iConnectionInfoArray.Close();
    iConnMonitor.Close();

    delete iReadConnectionInfo;

    delete iEntity;
    delete iKey;
    }

// --------------------------------------------------------------------
// CConnection::NewL
// Two-phased constructor, returns instance of this class.
// --------------------------------------------------------------------
//
CConnection* CConnection::NewL(const TSysRequest& aRequest)
    {
    CConnection* self;
    self = new (ELeave) CConnection(aRequest.RequestType(),
                            aRequest.TransactionID(), aRequest.Observer());

    CleanupStack::PushL(self);
    self->ConstructL (aRequest);
    CleanupStack::Pop(self);

    return self;
    }

// --------------------------------------------------------------------
// CConnection::ConstructL
// 2nd Phase constructor to allocate required resources for this obj.
// --------------------------------------------------------------------
//
void CConnection::ConstructL(const TSysRequest& aRequest)
    {
    //connect
    User::LeaveIfError(iConnMonitor.ConnectL());

    // Make local copy of SA.
    iEntity = aRequest.Entity().AllocL();

    iKey	= aRequest.Key().AllocL();
    }
	
// --------------------------------------------------------------------
// CConnection::Request
// Issues connection request.
// --------------------------------------------------------------------
//
TInt CConnection::Request()
    {
    TInt err = KErrNone;
    if( !IsActive() )
        {
        //Retrieve all connections.		
        iConnMonitor.GetConnectionCount(iConnectionCount, iStatus);
        SetActive();
        if(TSysRequest::ENotification == RequestType())
            TRAP(err,iConnMonitor.NotifyEventL(*this));
        }
    return err;
    }

// --------------------------------------------------------------------
// CConnection::RunL
// Gets called in event of request completion or error situation.
// --------------------------------------------------------------------
//
void CConnection::RunL()
    {
    TSysRequest::TRequestType ReqType = RequestType();
    TInt32 transId = this->TransactionID();
    TInt error(iStatus.Int());

    if(error >= KErrNone)
        {
        // Read All Connected Connection IDs.
        for(TInt i=1; i<=iConnectionCount; i++)
            {
            TUint	ConnectioID,IgnoreSubConnects;
            iConnMonitor.GetConnectionInfo(i, ConnectioID, IgnoreSubConnects);
            iConnectionIds[i-1] = ConnectioID;
            }

        // read if thr are connections.
        if ( iConnectionCount > 0 )
            {
            //read the connections.
            ReadNextConnectionL();
            }
        else if( ReqType == TSysRequest::EASyncONESHOT )
            {	
            //create a copy of SA for response.
            CConnectionList* connList = CConnectionList::
                                            NewL(iConnectionInfoArray);
            //call observer.
            TRAP_IGNORE(SystemObserver()->HandleResponseL(*iEntity,*iKey,
                                    connList,transId,RequestType(),error));
            //remove this from active store.
            ActiveStore::RemoveRequest(transId);
            }
        }
    else // in case error.
        {
        //call observer.
        TRAP_IGNORE(SystemObserver()->HandleResponseL(*iEntity,*iKey,
                                    NULL,transId,RequestType(),error));
        }
    }

// --------------------------------------------------------------------
// CConnection::HandleConnectionInfoL
// Gets called when an ConnectionID Connection information is read.
// --------------------------------------------------------------------
//
void CConnection::HandleConnectionInfoL(CConnectionInfo*& aInfo,TInt error)
    {
    TInt32 transId = this->TransactionID();
    iReadConnectionInfo = NULL;

    if(TSysRequest::ENotification == RequestType() )
        {
        if(!error)
            {
            iConnectionInfoArray.AppendL(aInfo);
            if( !iConnectionInit )
                {
                CConnectionInfo* conninfo = aInfo->CopyL();
                TRAP_IGNORE(SystemObserver()->HandleResponseL(*iEntity, *iKey,
                                        conninfo, transId, RequestType(), error));
                }
            }
        else
            {
            TRAP_IGNORE(SystemObserver()->HandleResponseL(*iEntity, *iKey,
                            NULL, transId, RequestType(), error));
        
            }
        }
    else
        {
        //Inc index.
        ++iConnectionIndex;

        //Add connection info to RArrayPointer.
        if( !error ) 
            iConnectionInfoArray.AppendL(aInfo);

        // check if some more connections exists.
        if( iConnectionIndex <= iConnectionCount)
            {
            ReadNextConnectionL();
            // don't send response.
            return;
            }

        //create a ConnectionList object.
        CConnectionList* connList = CConnectionList::NewL(iConnectionInfoArray);
        //call observer.
        TRAP_IGNORE(SystemObserver()->HandleResponseL(*iEntity, *iKey,
                                 connList, transId, RequestType(), error));

        // Remove this from active store.
        ActiveStore::RemoveRequest(TransactionID());
        }
    }

// --------------------------------------------------------------------
// CConnection::ReadNextConnectionL
// Creates CReadConnectionInfo request for an ConnectionID.
// --------------------------------------------------------------------
//
void CConnection::ReadNextConnectionL()
    {
    iReadConnectionInfo = CReadConnectionInfo::NewL(iConnMonitor,
                                    iConnectionIds[iConnectionIndex-1],
                                    this,CConnectionInfo::EConnected,
                                    TSysRequest::EASyncONESHOT);

    iReadConnectionInfo->Request();
    }

// --------------------------------------------------------------------
// CConnection::DoCancel
// cancel any notificatons.
// --------------------------------------------------------------------
//
void CConnection::DoCancel()
    {
    TSysRequest::TRequestType ReqType = RequestType();
    if(ReqType ==TSysRequest::ENotification )
        iConnMonitor.CancelNotifications();		
    }

// --------------------------------------------------------------------
// CConnection::EventL
// gets called whenever there is change in connections.
// --------------------------------------------------------------------
//
void CConnection::EventL(const CConnMonEventBase& aEvent)
    {
    TUint connectionId =0;
    CReadConnectionInfo* rdConnectionInfo = NULL;
    
    switch( aEvent.EventType() )
        {
        case EConnMonCreateConnection:
            iConnectionInit = EFalse;
            CConnMonCreateConnection* eventCreate; 
            eventCreate = (CConnMonCreateConnection*)& aEvent;
            connectionId = eventCreate->ConnectionId();	
            rdConnectionInfo = CReadConnectionInfo::NewL(iConnMonitor,
            					connectionId,
            					this,
            					CConnectionInfo::EConnected,
            					TSysRequest::ENotification);
            CleanupStack::PushL(rdConnectionInfo);
            // get connection details.
            User::LeaveIfError(rdConnectionInfo->Request());
            CleanupStack::Pop(rdConnectionInfo);
            break;

        case EConnMonDeleteConnection:
            CConnMonDeleteConnection* eventDelete; 
            eventDelete = (CConnMonDeleteConnection*)& aEvent;
            connectionId  = eventDelete->ConnectionId();

            for(TInt i=0; i<iConnectionInfoArray.Count(); i++)
                {
                CConnectionInfo* conninfo = iConnectionInfoArray[i];
                if( connectionId == conninfo->ConnectionId() )
                    {
                    CConnectionInfo* info = conninfo->CopyL();
                    info->SetConnectionState(CConnectionInfo::EDisconnected);
                    TRAP_IGNORE(SystemObserver()->HandleResponseL(
                                    *iEntity,*iKey,info,TransactionID(),
                                    RequestType(),KErrNone));
                                    
                    iConnectionInfoArray.Remove(i);
                    delete conninfo;
                    break;
                    }
                }
            break;

        default:
            break;
        }
    }
    
// --------------------------------------------------------------------
// CReadConnectionInfo::CReadConnectionInfo
// C++ default constructor.
// --------------------------------------------------------------------
//
CReadConnectionInfo::CReadConnectionInfo( RConnectionMonitor& aConnMon,
                        TUint aConnId, MConnectInfoCallback* aCallBack, 
                        CConnectionInfo::TConnectionState aState,
                        TSysRequest::TRequestType aReqType ) :
                        CActive(EPriorityNormal), iConnectionID(aConnId),
                        iCallBack(aCallBack), iConnMon(aConnMon),
                        iState(EInitial), iConnState(aState),iReqType(aReqType)
    {
    CActiveScheduler::Add(this);
    }

// --------------------------------------------------------------------
// CReadConnectionInfo::~CReadConnectionInfo
// Destructor.
// --------------------------------------------------------------------
//
CReadConnectionInfo::~CReadConnectionInfo()
    {
    Cancel();
    delete iIAPName;
    delete iNetworkName;
    delete iConnectionName;
    }

// --------------------------------------------------------------------
// CReadConnectionInfo::NewL
// Two-phased constructor, returns instance of this class.
// --------------------------------------------------------------------
//
CReadConnectionInfo* CReadConnectionInfo::NewL(RConnectionMonitor& aConnMon,
                            TUint aConnId,MConnectInfoCallback* aCallBack,
                            CConnectionInfo::TConnectionState aState,
                            TSysRequest::TRequestType aReqType )
    {
    CReadConnectionInfo* self = new (ELeave) CReadConnectionInfo(aConnMon,
                                        aConnId, aCallBack, aState, aReqType);
    return self;
    }

// --------------------------------------------------------------------
// CReadConnectionInfo::Request
// Issues ConnectionInfo read request.
// --------------------------------------------------------------------
//
TInt CReadConnectionInfo::Request()
    {
    if(!IsActive())
        {
        TRequestStatus* status = &iStatus;
        User::RequestComplete(status,KErrNone);
        SetActive();
        }
    return KErrNone;
    }

// --------------------------------------------------------------------
// CReadConnectionInfo::RunL
// Gets called in event of request completion or error situation.
// --------------------------------------------------------------------
//
void CReadConnectionInfo::RunL()
    {
    CConnectionInfo* connectionInfo=NULL;

    TInt error(iStatus.Int());
    if(error >= KErrNone)
    {
        switch(iState)
            {
            case EInitial:
                iConnMon.GetUintAttribute(iConnectionID, 0, KIAPId, iIAPId, iStatus);
                iState = EIAPId;
                break;

            case EIAPId:
                iConnMon.GetIntAttribute(iConnectionID, 0, KBearer,iBearerType, iStatus);
                iState = EBearerType;
                break;

            case EBearerType:
                iConnMon.GetStringAttribute(iConnectionID, 0, KIAPName, iNameBuf, iStatus);
                iState = EIAPName; 
                break;

            case EIAPName:
                iIAPName = iNameBuf.AllocL();
                iNameBuf.Zero();

                if(iBearerType == EBearerWLAN )
                    {
                    iConnMon.GetStringAttribute(iConnectionID, 0, 
                                        KNetworkName, iNameBuf, iStatus);
                    iState = ENetworkName;
                    }
                else
                    {
                    iConnMon.GetStringAttribute(iConnectionID, 0, 
                                    KAccessPointName, iNameBuf, iStatus);	
                    iState = EIAPConnectionName;
                    }
                break;

            case ENetworkName :
                iNetworkName = iNameBuf.AllocL();
                iNameBuf.Zero();
                connectionInfo = CConnectionInfo::NewL(iConnectionID, iIAPId,
                                        iBearerType, iConnState, *iIAPName,
                                        *iNetworkName, KNullDesC);

                iState = EComplete;
                break;

            case EIAPConnectionName:
                iConnectionName = iNameBuf.AllocL();	
                iNameBuf.Zero();

                connectionInfo = CConnectionInfo::NewL(iConnectionID, iIAPId,
                                        iBearerType, iConnState, *iIAPName,
                                        KNullDesC, *iConnectionName);
                iState = EComplete;	
            }
        }
    else
        {
        if (iState == EIAPConnectionName || iState == ENetworkName) 
            {
            connectionInfo = CConnectionInfo::NewL(iConnectionID, iIAPId,
                                    iBearerType, iConnState, *iIAPName,
                                    KNullDesC, KNullDesC);
            error = KErrNone;
            }
        iState = EComplete;
        }

    //if not complete read next attribute.
    if(iState != EComplete)
        SetActive();
    else
        {
        iCallBack->HandleConnectionInfoL(connectionInfo,error);
        delete this;
        }
    }

// --------------------------------------------------------------------
// CReadConnectionInfo::DoCancel
// cancels any ongoing request.
// --------------------------------------------------------------------
//
void CReadConnectionInfo::DoCancel()
    {
    if( IsActive() )
        {
        switch(iState)
            {
            case EIAPId:
                iConnMon.CancelAsyncRequest(EConnMonGetUintAttribute);
                break;
            case EBearerType: 
                iConnMon.CancelAsyncRequest(EConnMonGetIntAttribute);
                break;
            case EIAPName:
            case ENetworkName:
            case EIAPConnectionName:
                iConnMon.CancelAsyncRequest(EConnMonGetStringAttribute);
                break;

            default:
                iConnMon.CancelNotifications();
                break;
            }
        }
    }

// End of file
