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
#include <centralrepository.h>

#include "sysinfoutils.h"

// ---------------------------------------------------------------------------
// RPhoneInstance::Connect
// Connects to the RTelServer and the RMobilePhone classes
// ---------------------------------------------------------------------------
//
TInt RPhoneInstance::Connect(RTelServer& aTelServer,RMobilePhone& aMobilePhone) 
    {
    TInt PHONEINDEX = 0;

    RTelServer::TPhoneInfo PhoneInfo;
    TInt errorCode = KErrNone ;
    if( ( errorCode = aTelServer.Connect() ) != KErrNone )
        {
        return errorCode;
        }
    else 
        {
        if ( ( errorCode = aTelServer.LoadPhoneModule(KMmTsyModuleName) )
                                                    != KErrNone ||
        ( errorCode = aTelServer.GetPhoneInfo(PHONEINDEX, PhoneInfo) )
                                                    != KErrNone ||
        ( errorCode = aMobilePhone.Open(aTelServer, PhoneInfo.iName) )
                                                    != KErrNone )
            {
            // Close mTelServer handle on cleanup stack.
            aTelServer.Close();
            return errorCode;
            }
        }
    return KErrNone;
    }
// ---------------------------------------------------------------------------
// RepositoryUtil::SetRepositoryKeyL
// Modifies interger value of an Repository key.
// ---------------------------------------------------------------------------
//
void RepositoryUtil::SetRepositoryKeyL(const TUid& aUid,const TUint32& aKey,
                                                            const TInt& aValue)
    {
    CRepository* repository = CRepository::NewLC(aUid);
    User::LeaveIfError(repository->Set(aKey, aValue));
    CleanupStack::PopAndDestroy(repository);
    }

// ---------------------------------------------------------------------------
// RepositoryUtil::SetRepositoryKeyL
// Modifies descritor value of an Repository key.
// ---------------------------------------------------------------------------
//
void RepositoryUtil::GetRepositoryKeyL(const TUid& aUid,const TUint32& aKey,
                                                                TInt& aValue)
    {
    CRepository* repository = CRepository::NewLC(aUid);
    User::LeaveIfError(repository->Get(aKey, aValue));
    CleanupStack::PopAndDestroy(repository);
    }

// ---------------------------------------------------------------------------
// RepositoryUtil::GetRepositoryKeyL
// reads integer value of an Repository key.
// ---------------------------------------------------------------------------
//
void RepositoryUtil::GetRepositoryKeyL(const TUid& aUid,const TUint32& aKey,
                                                                TDes& aValue)
    {
    CRepository* repository = CRepository::NewLC(aUid);
    User::LeaveIfError(repository->Get(aKey, aValue));
    CleanupStack::PopAndDestroy(repository);
    }

// ---------------------------------------------------------------------------
// RepositoryUtil::GetRepositoryKeyL
// reads descritor value of an Repository key.
// ---------------------------------------------------------------------------
//
void RepositoryUtil::SetRepositoryKeyL(const TUid& aUid,const TUint32& aKey,
                                                        const TDesC& aValue)
    {
    CRepository* repository = CRepository::NewLC(aUid);
    User::LeaveIfError(repository->Set(aKey, aValue));
    CleanupStack::PopAndDestroy(repository);	
    }

//End of file.
