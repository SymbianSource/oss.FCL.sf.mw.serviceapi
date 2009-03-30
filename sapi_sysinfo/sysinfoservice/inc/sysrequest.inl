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
* Description:  CSysInfoService class implementation
*
*/


// --------------------------------------------------------------------
// TSysRequest::TSysRequest()
// Constructor
// --------------------------------------------------------------------
//
inline TSysRequest::TSysRequest(const TPtrC aEntity, const TPtrC aKey,
                                TInt32 aTransactionID, 
                                ISystemObserver* aCallback,
                                TRequestType aReqType): 
                                iEntity(aEntity),iKey(aKey),
                                iRequestType(aReqType),
                                iSysData(NULL),
                                iTransactionID(aTransactionID),
                                iObserver(aCallback)
{
	
}

// --------------------------------------------------------------------
// TSysRequest::TSysRequest()
// overloaded constructor.
// --------------------------------------------------------------------
//
inline TSysRequest::TSysRequest(const TDesC& aEntity, const TDesC& aKey, 
                                const CSysData* aData, TInt32 aTransactionID,
                                ISystemObserver* aCallback,
                                TRequestType aReqType):
                                iEntity(aEntity),iKey(aKey),
                                iRequestType(aReqType),
                                iSysData(aData),
                                iTransactionID(aTransactionID),
                                iObserver(aCallback)
    {
    }

// --------------------------------------------------------------------
// TSysRequest::Entity()
// returns Entity.
// --------------------------------------------------------------------
//
inline const TPtrC TSysRequest::Entity() const
    {
    return iEntity;
    }

// --------------------------------------------------------------------
// TSysRequest::Key()
// returns Key.
// --------------------------------------------------------------------
//
inline const TPtrC TSysRequest::Key() const
    {
    return iKey;
    }

// --------------------------------------------------------------------
// TSysRequest::RequestType()
// returns type of request.
// --------------------------------------------------------------------
//
inline TSysRequest::TRequestType TSysRequest::RequestType () const
    {
    return iRequestType;
    }

// --------------------------------------------------------------------
// TSysRequest::TransactionID()
// returns TransactionID.
// --------------------------------------------------------------------
//
inline TInt32 TSysRequest::TransactionID() const
    {
    return iTransactionID;
    }

// --------------------------------------------------------------------
// TSysRequest::SystemData()
// returns stored CSysData.
// --------------------------------------------------------------------
//
inline const CSysData* TSysRequest::SystemData() const
    {
    return iSysData;
    }

inline ISystemObserver* TSysRequest ::Observer() const
    {
    return iObserver;
    }
    
