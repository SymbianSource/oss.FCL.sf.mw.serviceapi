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
* Description:  describes system information utilities.
*
*/


#ifndef __SYSINFOUTILS_H__
#define __SYSINFOUTILS_H__


/**
*  @ref RPhoneInstance singleton pattern used to maintain one instance RMoblePhone
*  resource shared by other implementation class in sysinfo.
*
*  @lib sysinfoservice.lib
*  @since S60 3.2
*/
class RPhoneInstance
    {
    public:
    /**
    * Connects to the RTelServer and the RMobilePhone classes.
    *
    * @return @p KErrNone if the initialization succeeded, otherwise connetion
    * ErrorCode.
    */
    static TInt Connect( RTelServer& aTelServer,RMobilePhone& aMobilePhone );

    };

/**
*  @ref RepositoryUtil static interface class to access modify value of 
*  central repository UID,Keys.
*
*  @lib sysinfoservice.lib
*  @since S60 3.2
*/
class RepositoryUtil
    {
    public:
    /**
    * Modifies interger value of an Repository key.
    */
    static void SetRepositoryKeyL(const TUid& aUid, const TUint32& aKey,
                                                        const TInt& aValue);

    /**
    * Modifies Descriptor value of an Repository key.
    */
    static void SetRepositoryKeyL(const TUid& aUid, const TUint32& aKey, 
                                                        const TDesC& aValue);

    /**
    * reads interger value of an Repository key. On return aValue consists 
    * of Key value.
    */
    static void GetRepositoryKeyL(const TUid& aUid, const TUint32& aKey,
                                                        TInt& aValue);

    /**
    * reads descriptor value of an Repository key. On return aValue consists 
    * of descriptor.
    */
    static void GetRepositoryKeyL(const TUid& aUid, const TUint32& aKey,
                                                            TDes& aValue);
    };

#endif // __SYSINFO_UTILS_H__
