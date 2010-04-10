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


#ifndef _SYSREQUEST_H_
#define _SYSREQUEST_H_

/**
*   @ref TSysRequest
*   This is internal class to encapsulate all input parameters in 
*   specifying request.
*   A request typically contains 
*           1. Entity. 
*           2. Key.
*           3. @ref TRequestType enumerated request types. 
*           4. @ref CSysData optional input data Ex. threshold signal 
*                   strength for notification.
*           5. TransactionID for asynchronous requests.
*           6. Observer to handle async response.
*
*  @lib sysinfoservice.lib
*  @since S60 3.2
*/
class TSysRequest
    {
    public:
    // Enumeration of possible request types.
    enum TRequestType
        {
        ESynchronous,
        EASyncONESHOT,
        ENotification
        };

    public:	 // Constructors and destructor
        /**
        * C++ default constructor(s).
        */
        inline TSysRequest( const TPtrC aEntity, const TPtrC aKey, 
                            TInt32 aTransID,
                            ISystemObserver* aCallback,
                            TRequestType aReqType = ESynchronous);
        /**
        * C++ default constructor(s).
        */
        inline TSysRequest( const TDesC& aEntity, const TDesC& aKey, 
                            const CSysData* aData, 
                            TInt32 aTransactionID, 
                            ISystemObserver* aCallback,
                            TRequestType aReqType = ESynchronous);

    public:

        /**
        * @returns Entity of the System Infomation Identifier.
        */
        inline const TPtrC Entity() const;

        /**
        * @returns Entity of the System Infomation Identifier.
        */
        inline const TPtrC Key() const;

        /**
        * @returns Transaction ID associated with the request.
        */
        inline TInt32 TransactionID() const;

        /**
        * @returns System data.
        */		
        inline const CSysData* SystemData() const;

        /**
        * @returns Type of request @ref TRequestType.
        */		
        inline TRequestType RequestType() const;

        /**
        * @returns observer @ref TRequestType.
        */				
        inline ISystemObserver* Observer() const;

    private:	//DATA
        /**
        * Entity
        */		
        const TPtrC         iEntity;
        /**
        * Key
        */		
        const TPtrC         iKey;
        /**
        * Type of request.
        */
        TRequestType        iRequestType;
        /**
        * System data.
        */
        const CSysData*	    iSysData;
        /**
        * Transaction ID.
        */			
        TInt32              iTransactionID;
        /**
        * Observer
        */				
        ISystemObserver*    iObserver;
    };

#include "sysrequest.inl"

#endif // _SYSREQUEST_H_

//End of file
