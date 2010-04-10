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


#ifndef __SYSCONNECTIONREQUEST_H__
#define __SYSCONNECTIONREQUEST_H__

//INCLUDES
#include<rconnmon.h>

#include "sysinfo.h"
#include "activerequests.h"

// CONSTANT DECLARATIONS
const TInt KMaxConnName = 256;

// FORWARD DECLARATIONS

/**
*   @ref MConnectInfoCallback
*   Observer class to handle to async response.
*
*/
class MConnectInfoCallback
    {
    public:
    //Gets called when complete connection attributes are read.
    virtual void HandleConnectionInfoL(CConnectionInfo*& aInfo,TInt error=0)=0;
    virtual ~MConnectInfoCallback()	{ };
    };

/**
*	@ref CReadConnectionInfo
*	active object class to read all connection attributes of an ConnectionID.
*
*/
NONSHARABLE_CLASS(CReadConnectionInfo):public CActive
    {
    public:
    /**
    * Two-phased constructor.
    *
    * @return A new instance of this class.
    */    
    static CReadConnectionInfo* NewL(RConnectionMonitor& aConnMon,TUint aConnId,
                                    MConnectInfoCallback* aCallBack,
                                    CConnectionInfo::TConnectionState aState,
                                    TSysRequest::TRequestType aReqType);

    /**
    * Destructor.
    */
    ~CReadConnectionInfo();
    
    private:
    /**
    * C++ default constructor.
    */
    CReadConnectionInfo(RConnectionMonitor& aConnMon,TUint aConnId,
                                    MConnectInfoCallback* aCallBack,
                                    CConnectionInfo::TConnectionState aState,
                                    TSysRequest::TRequestType aReqType);

    public:
    /**
    * Issues asynchronous request.
    */
    TInt Request();

    protected: // From CActive 
    void RunL();
    void DoCancel();

    private:
    //Enumeration of states involved in getting connection information.
    typedef enum{
        EInitial,
        EIAPId,
        EBearerType,
        EIAPName,
        ENetworkName,
        EIAPConnectionName,
        EComplete
    }TConnstate;

    //ConnectionID whose attributes to be read.
    TUint                   iConnectionID;
    //Observer to handle response.
    MConnectInfoCallback*   iCallBack;
    //Connection to Connection Server.
    RConnectionMonitor      iConnMon;

    //Access point ID.
    TUint                   iIAPId;
    //Connection Type.
    TInt                    iBearerType;
    //Access point name.
    HBufC*                  iIAPName;
    //Network name.
    HBufC*                  iNetworkName;
    //Connection Name.
    HBufC*                  iConnectionName;
    //State variable for reading attributes.
    TConnstate              iState;
    //Connection State.
    CConnectionInfo::TConnectionState   iConnState;

    TBuf<KMaxConnName>      iNameBuf;

    TSysRequest::TRequestType   iReqType ; 
    };

/**
*	@ref CReadConnectionInfo
*	active object class to read all connection attributes of an ConnectionID.
*
*/
NONSHARABLE_CLASS(CConnection): public CActiveRequest, 
                                private MConnectionMonitorObserver,
                                private MConnectInfoCallback
    {
    public:	// Constructors and destructor
    /**
    * Two-phased constructor.
    *
    * @return A new instance of this class.
    */    
    static CConnection* NewL(const TSysRequest& aRequest);

    /**
    * Destructor.
    */
    ~CConnection();

    private:
    /**
    * C++ default constructor.
    */
    CConnection(TSysRequest::TRequestType aReqType,TInt32 aTransID,
                                        ISystemObserver* aObsrvr);

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    void ConstructL(const TSysRequest& aRequest);

    private:
    void ReadNextConnectionL();
    
    private:
    /**
    * MConnectionMonitorObserver call back funtion.
    */	
    void EventL(const CConnMonEventBase& aEvent);

    void HandleConnectionInfoL(CConnectionInfo*& aInfo,TInt error);
    
    public:	
    /**
    * Issues asynchronous request.
    */
    TInt Request();

    protected: // from CActive
    void RunL();
    void DoCancel();

    private:	// DATA
    enum { 
    EMAXCONNECTIONS=10,
    };	

    //	Local copy of Entity.
    HBufC*              iEntity;

    //	Local copy of Key.
    HBufC*              iKey;

    RConnectionMonitor  iConnMonitor;

    TUint               iConnectionIds[EMAXCONNECTIONS];

    TUint               iConnectionCount;

    TInt                iConnectionIndex;

    RPointerArray<CConnectionInfo> iConnectionInfoArray;

    CReadConnectionInfo*    iReadConnectionInfo;

    TBool                   iConnectionInit;
    };

#endif // __SYSCONNECTIONREQUEST_H__
