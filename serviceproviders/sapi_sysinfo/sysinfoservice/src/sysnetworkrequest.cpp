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

#include <etel.h>
#include <etelmm.h>
#include <mmtsy_names.h>

#include "sysinfoservice.h"
#include "sysnetworkrequest.h"
#include "entitykeys.h"
#include "sysrequest.h"
#include "sysinfoutils.h"

// --------------------------------------------------------------------
// CNetwork::CNetwork()
// C++ default constructor.
// --------------------------------------------------------------------
//
CNetwork::CNetwork( TSysRequest::TRequestType aReqType, TInt32 aTransID,
                TInt aNetworkInfoType, ISystemObserver* aObsrver )
                :CActiveRequest(aReqType,aTransID,aObsrver),
				iNetworkInfoType((TNetInfoType)aNetworkInfoType),
                iNetworkInfoBuf(iNetworkInfo), iIsThresholdSet(EFalse)
    {
    }

// --------------------------------------------------------------------
// CNetwork::~CNetwork()
// Destructor
// --------------------------------------------------------------------
//
CNetwork::~CNetwork()
    {
    Cancel();
    iMobilePhone.Close();
    iTelServer.Close();
    delete iEntity;
    delete iKey;
    }

// --------------------------------------------------------------------
// CNetwork::NewL()
// Two-phased constructor, returns instance of this class.
// --------------------------------------------------------------------
//
CNetwork* CNetwork::NewL( const TSysRequest& aRequest,TInt aNetworkInfoType )
    {
    CNetwork* self;
    self = new (ELeave) CNetwork(aRequest.RequestType(), aRequest.TransactionID(),
                                aNetworkInfoType, aRequest.Observer() );
    CleanupStack::PushL(self);
    self->ConstructL(aRequest);
    CleanupStack::Pop(self);
    return self;
    }

// --------------------------------------------------------------------
// CNetwork::ConstructL()
// 2nd Phase constructor to allocate required resources for this obj.
// --------------------------------------------------------------------
//
void CNetwork::ConstructL(const TSysRequest& aRequest)
    {
    //For Network signal strength and battery user can specify threshold.
    if( TSysRequest::ENotification == RequestType() &&
        (ESignalStrength == iNetworkInfoType || 
            EBatteryStrength == iNetworkInfoType) )
        {
        const CSysData* Input = aRequest.SystemData();
        // check if any input parameter
        if(Input)
            {
            //perform parameter validation.
            if( CSysData::EStatus != Input->DataType())
            User::Leave(KErrArgument);
            //get threshold value.
            iThreshold = ((CStatus*)Input)->Status();
            iIsThresholdSet = ETrue;
            }
        }

    //Create a handle to RMobile
    User::LeaveIfError(RPhoneInstance::Connect( iTelServer,iMobilePhone ));

    // Make local copy of SA.
    iEntity = aRequest.Entity().AllocL();
    iKey	= aRequest.Key().AllocL();
    }

// --------------------------------------------------------------------
// CNetwork::Request()
// Issues network request.
// --------------------------------------------------------------------
//
TInt CNetwork::Request()
    {
    TSysRequest::TRequestType ReqType = RequestType();

    if( !IsActive() )
        {
        // Issue request based on request type.
        if(TSysRequest::EASyncONESHOT == ReqType)
            {
            switch(iNetworkInfoType)
                {
                case ESignalStrength:
                    iMobilePhone.GetSignalStrength(iStatus,iSignalStrength,iBar); 
                    break;
// HomeNetwork info require ReadDeviceData, which is not user grantable permission, and 
// is currently not supported.                    
#ifdef _REQUIRE_READDEVICEDATA_
                case EHomeNetworkInfo:
                    iMobilePhone.GetHomeNetwork( iStatus, iNetworkInfoBuf ); 
                    break;
#endif
                case ECurrentNetworkInfo:
                    iMobilePhone.GetCurrentNetwork(iStatus,iNetworkInfoBuf,iArea); 
                    break;

                case EBatteryStrength:
                    iMobilePhone.GetBatteryInfo(iStatus,iBatteryInfo); 
                    break;

                default:
                    return KErrNotFound;
                }
            }
        else //Notification.
            {
            switch(iNetworkInfoType)
                {
                case ESignalStrength:
                    iMobilePhone.NotifySignalStrengthChange(iStatus,iSignalStrength,iBar); 
                    break;

                case ECurrentNetworkInfo:
                case ELocationAreaCode:
                case ECellId:
                    iMobilePhone.NotifyCurrentNetworkChange(iStatus,iNetworkInfoBuf,iArea); 
                    break;

                case EBatteryStrength:
                    iMobilePhone.NotifyBatteryInfoChange(iStatus,iBatteryInfo); 
                    break;

                default:
                    return KErrNotFound;
                }
            }
        SetActive ();
        }
    return KErrNone;
    }

// --------------------------------------------------------------------
// CNetwork::RunL()
// Gets called in event of request completion or error situation.
// --------------------------------------------------------------------
//
void CNetwork::RunL()
    {
    TSysRequest::TRequestType ReqType = RequestType();
    CSysData* OutputParam = NULL;
    TInt32 transId = this->TransactionID();
    TInt error( iStatus.Int() );

    if(KErrNone == error)
        {
        switch(iNetworkInfoType)
            {
            case ESignalStrength:
                //if threshold not specified. notify every change.
                if( !iIsThresholdSet )
                    OutputParam = CStatus::NewL(iSignalStrength);
                else if( (iSignalStrength > iThreshold) )
                    OutputParam = CStatus::NewL(iSignalStrength);
                break;

            case EHomeNetworkInfo:
            case ECurrentNetworkInfo:
                OutputParam = CNetworkInfo::NewL(iNetworkInfo,iArea);
                break;

            case ELocationAreaCode:
                if( iArea.iAreaKnown && iLocationAreaCodeOld != iArea.iLocationAreaCode )
                    {
                    OutputParam = CStatus::NewL(iArea.iLocationAreaCode);
                    iLocationAreaCodeOld = iArea.iLocationAreaCode;
                    }
                break;	

            case ECellId:
                if( iArea.iAreaKnown && iCellIdOld != iArea.iCellId )
                    {
                    OutputParam = CStatus::NewL(iArea.iCellId);
                    iCellIdOld = iArea.iCellId;
                    }
                break;	

            case EBatteryStrength:
                //if threshold not specified. notify every change.
                if( !iIsThresholdSet )
                    OutputParam = CStatus::NewL(iBatteryInfo.iChargeLevel);
                else if( (iSignalStrength <= iThreshold) )
                    OutputParam = CStatus::NewL(iBatteryInfo.iChargeLevel);
                break;

            default:
                break;
            }

        //In case notification Re-Issue Request.
        if (TSysRequest::ENotification == ReqType)
            Request();

        //Notify only if threshold reached.
        if(OutputParam)
            TRAP_IGNORE(SystemObserver()->HandleResponseL(*iEntity,*iKey,OutputParam,transId,RequestType(),error));

        }
    //If error
    else
        {
        TRAP_IGNORE(SystemObserver()->HandleResponseL(*iEntity,*iKey,NULL,transId,RequestType(),error));
        ActiveStore::RemoveRequest(TransactionID());
        }

    //If its a ONSHOT Requeust remove this from active store.
    if (TSysRequest::EASyncONESHOT == ReqType)
        ActiveStore::RemoveRequest(transId);
    }

// --------------------------------------------------------------------
// CNetwork::DoCancel()
// cancels ongoing network request.
// --------------------------------------------------------------------
//
void CNetwork::DoCancel()
    {
    TSysRequest::TRequestType ReqType = RequestType();

    //Cancel request based on type of request.
    if(TSysRequest::EASyncONESHOT == ReqType)
        {
        switch(iNetworkInfoType)
            {
            case ESignalStrength:
                iMobilePhone.CancelAsyncRequest(EMobilePhoneGetSignalStrength);
                break;

            case EHomeNetworkInfo:	
                iMobilePhone.CancelAsyncRequest(EMobilePhoneGetHomeNetwork);
                break;

            case ECurrentNetworkInfo:
            case ELocationAreaCode:
            case ECellId:
                iMobilePhone.CancelAsyncRequest(EMobilePhoneGetNetworkRegistrationStatus);
                break;

            case EBatteryStrength:
                iMobilePhone.CancelAsyncRequest(EMobilePhoneGetBatteryInfo);
                break;

            default:
                break;	
            }
        }
    //Notification
    else
        {	
        switch(iNetworkInfoType)
            {
            case ESignalStrength:
                iMobilePhone.CancelAsyncRequest(EMobilePhoneNotifySignalStrengthChange);
                break;

            case EHomeNetworkInfo:	
                iMobilePhone.CancelAsyncRequest(EMobilePhoneGetHomeNetwork);
                break;

            case ECurrentNetworkInfo:
            case ELocationAreaCode:
            case ECellId:
                iMobilePhone.CancelAsyncRequest(EMobilePhoneNotifyCurrentNetworkChange);
                break;

            case EBatteryStrength:
                iMobilePhone.CancelAsyncRequest(EMobilePhoneNotifyBatteryInfoChange);
                break;

            default:
                break;
            }
        }
    }

//End of File.
