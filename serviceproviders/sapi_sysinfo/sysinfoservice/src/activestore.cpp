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

#include "activerequests.h"
#include "entitykeys.h"
#include "sysnetworkrequest.h"
#include "sysaccessoryrequest.h"
#include "sysconnectionrequest.h"
#include "sysuseractivity.h"
#include "sysrequest.h"

using namespace SysInfo;

const TInt KGranularity(2);

RPointerArray<CActiveRequest> ActiveStore::iHandlers(KGranularity);

// --------------------------------------------------------------------
// CActiveRequest::CActiveRequest()
// C++ default constructor.
// --------------------------------------------------------------------
//
CActiveRequest::CActiveRequest(TSysRequest::TRequestType aReqType, 
                                TInt32 aTransID,
                                ISystemObserver* aObsrvr)
                                :CActive(EPriorityNormal),
                                iTransactionID(aTransID),
                                iRequestType(aReqType),
                                iObserver(aObsrvr)
								 
    {
    CActiveScheduler::Add(this);
    }

// --------------------------------------------------------------------
// CActiveRequest::~CActiveRequest()
// destructor
// --------------------------------------------------------------------
//
CActiveRequest::~CActiveRequest()
    {
    }

// --------------------------------------------------------------------
// CActiveRequest::CreateActiveRequestL()
// static factory method to create asynchronous requests.
// --------------------------------------------------------------------
//
void CActiveRequest::CreateActiveRequestL(const TSysRequest& aSysRequest,
                                            CActiveRequest*& aActiveObj)
    {
    const TPtrC Entity = aSysRequest.Entity();
    const TPtrC Key =	aSysRequest.Key();

    aActiveObj = NULL;

    if ( !Entity.CompareF(KNetwork) )
        CreateNetworkRequestL(aSysRequest,aActiveObj);

    else if( !Entity.CompareF(KGeneral) )
        CreateGeneralRequestL(aSysRequest,aActiveObj);

    else if( !Entity.CompareF(KBattery) )
        {
        // Battery Entity Keys.
        if( !Key.CompareF(KChargingStatus) )
            aActiveObj = CPubSubNotifier::NewL(aSysRequest,
                                            CPubSubNotifier::EChargingStatus);

        else if( !Key.CompareF(KBatteryStrength) )
            aActiveObj = CNetwork::NewL(aSysRequest,
                                                CNetwork::EBatteryStrength);

        else
            User::Leave(KErrNotFound);
        }

    else if( !Entity.CompareF(KConnectivity) )
        {
        // Connectivity Entity Keys.
        if( !Key.CompareF(KBlueTooth))
            aActiveObj = CCenrepNotifier::NewL(aSysRequest,
                                                CCenrepNotifier::EBlueTooth);

        else if( !Key.CompareF(KInfraRed) )
            aActiveObj = CPubSubNotifier::NewL(aSysRequest,
                                                CPubSubNotifier::EInfraRed);

        else if( (!Key.CompareF(SysInfo::KActiveConnections)) && (aSysRequest.RequestType() == TSysRequest::EASyncONESHOT) )
            aActiveObj = CConnection::NewL(aSysRequest);

        else if( (!Key.CompareF(SysInfo::KConnectionStatus)) && (aSysRequest.RequestType() == TSysRequest::ENotification) )
            aActiveObj = CConnection::NewL(aSysRequest);
        
        else
            User::Leave(KErrNotFound);
        }
    else if( !Entity.CompareF(KDisplay))
        {
        // Display keys.
        if ( !Key.CompareF(KUserInactivity) )
            aActiveObj = CUserActivity::NewL(aSysRequest);

        else if( !Key.CompareF(KAutoLockStatus) )
            aActiveObj = CCenrepNotifier::NewL(aSysRequest,
                                                CCenrepNotifier::EKeyLock);

        else
            User::Leave(KErrNotFound);
        }
    else if( !Entity.CompareF(KMemory))
        {
        if ( !Key.CompareF(KCriticalMemory) )
            aActiveObj = CCriticalMemNotifier::NewL(aSysRequest);

        else if( !Key.CompareF(KMemoryCard) )
            aActiveObj = CPubSubNotifier::NewL(aSysRequest,
                                            CPubSubNotifier::EMemoryCard);

        else
            User::Leave(KErrNotFound);
        }
    //Ensure we don't return NULL handle.
    if(!aActiveObj)
        User::Leave(KErrNotFound);
    }

// --------------------------------------------------------------------
// CActiveRequest::CreateActiveRequestL()
// creates active objs related to Network entity.
// --------------------------------------------------------------------
//
void CActiveRequest::CreateNetworkRequestL(const TSysRequest& aSysRequest,
                                            CActiveRequest*& aActiveObj)
    {
    TPtrC Key = aSysRequest.Key();
    // parse network entity keys.
    if ( !Key.CompareF(SysInfo::KSignalStrength) )
        aActiveObj = CNetwork::NewL(aSysRequest,CNetwork::ESignalStrength);

    else if ( !Key.CompareF(KRegistrationStatus) )
        aActiveObj = CPubSubNotifier::NewL(aSysRequest,
                                    CPubSubNotifier::ERegistrationStatus);

    else if ( !Key.CompareF(SysInfo::KNetworkMode) )
        aActiveObj = CPubSubNotifier::NewL(aSysRequest,
                                            CPubSubNotifier::ENetworkMode);

    else if ( !Key.CompareF(KHomeNetwork) )
        aActiveObj = CNetwork::NewL(aSysRequest,CNetwork::EHomeNetworkInfo);

    else if ( !Key.CompareF(KCurrentNetwork) )
        aActiveObj = CNetwork::NewL(aSysRequest,CNetwork::ECurrentNetworkInfo);

    else if ( !Key.CompareF(KLocationArea) )
        aActiveObj = CNetwork::NewL(aSysRequest,CNetwork::ELocationAreaCode);

    else if ( !Key.CompareF(KCellID) )
        aActiveObj = CNetwork::NewL(aSysRequest,CNetwork::ECellId);

    else
        User::Leave(KErrNotFound);
    }

// --------------------------------------------------------------------
// CActiveRequest::CreateGeneralRequestL()
// creates active objs related general entity.
// --------------------------------------------------------------------
//
void CActiveRequest::CreateGeneralRequestL(const TSysRequest& aSysRequest,
                                                CActiveRequest*& aActiveObj)
    {
    TPtrC Key = aSysRequest.Key();
    //parse general entity keys.
    if ( !Key.CompareF(KAccessoryStatus) )
        aActiveObj = CAccessory::NewL(aSysRequest);

    else if( !Key.CompareF(KInputLanguage) )
        aActiveObj = CCenrepNotifier::NewL(aSysRequest,
                                            CCenrepNotifier::EInputLanguage);

    else if( !Key.CompareF(KPridictiveText) )
        aActiveObj = CCenrepNotifier::NewL(aSysRequest,
                                            CCenrepNotifier::EPridictiveText);

    else if( !Key.CompareF(KVibraActive) )
        aActiveObj = CCenrepNotifier::NewL(aSysRequest,CCenrepNotifier::EVibra);

    else if( !Key.CompareF(KFlipStatus) )
        aActiveObj = CPubSubNotifier::NewL(aSysRequest,
                                                CPubSubNotifier::EFlipStatus);

    else if( !Key.CompareF(KGripStatus) )
        aActiveObj = CPubSubNotifier::NewL(aSysRequest,
                                                CPubSubNotifier::EGripStatus);

    else
        User::Leave(KErrNotFound);
    }

// --------------------------------------------------------------------
// ActiveStore::AddRequestL()
// appends an active request to the active obj store.
// --------------------------------------------------------------------
//
void ActiveStore::AddRequestL(const CActiveRequest* aActiveReq )
    {
    TInt ActiveReqCnt = iHandlers.Count();
    // add active obj to store only if this transaction id 
    // doesn't exists before.
	for(TInt i=0; i<ActiveReqCnt; i++)
        {
        if(iHandlers[i]->TransactionID() == aActiveReq->TransactionID())
            User::Leave(KErrAlreadyExists);
        }
    //append the request.
    iHandlers.AppendL(aActiveReq);
    }

// --------------------------------------------------------------------
// ActiveStore::RemoveRequest()
// removes an active request from active obj store or performs cancel
// operation on the active object.
// --------------------------------------------------------------------
//
TInt ActiveStore::RemoveRequest(TInt32 aTransID)
    {
    TInt ActiveReqCnt = iHandlers.Count();
    for(TInt i=0; i<ActiveReqCnt; i++)
        {
        // Identify object associated with this transaction ID.
        if(iHandlers[i]->TransactionID() == aTransID)
            {
            CActiveRequest* ActiveObject = iHandlers[i];
            //delete active request. 
            delete ActiveObject;
            //Removes this request from RPointerArray.
            iHandlers.Remove(i);
            return KErrNone;
            }
        }
    //specified transaction id doesn't exists in store.
    return KErrNotFound;
    }

// --------------------------------------------------------------------
// ActiveStore::ReleaseResourcesL()
// removes all active requests in active obj store and release all
// memory associated with this static class.
// --------------------------------------------------------------------
//
void ActiveStore::ReleaseResources()
    {
    TInt count = iHandlers.Count();

    if(count>0)
        {
        for(TInt i=0; i<count; i++)
            {
            CActiveRequest* activeObject = iHandlers[i];
            //delete active request.
            delete activeObject;
            }
        //de-allocate all the pointer memory allocated.
        iHandlers.Reset();
        }
    //Close the pointer array to free all the memory allocated to it.
    iHandlers.Close();
    }
