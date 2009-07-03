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
* Description:  CSysInfoObserver class for handling async requests
*
*/


#ifndef __SYSINFOOBSERVER_H__
#define __SYSINFOOBSERVER_H__

#include <e32base.h>
#include "sysinfoservice.h"
#include "sysrequest.h"

//FORWARD DECLARATION
class CLiwGenericParamList;
class CSysInfoInterface;

/**
* CSysInfoObserver
* This class acts as an observer for all asynchronous requests. After the request
* is completed, it checks for error and packs it in output param list. If there
* is no error, then the iterator is also packed into the output param list.
*/
// CLASS DECLARATION
NONSHARABLE_CLASS(CSysInfoObserver): public CBase, public ISystemObserver
    {
    public: // New methods

    /**
    * NewL.
    * Two-phased constructor.
    * Create a CSysInfoObserver object.
    * @param aLmIface The CSysInfoInterface instance.
    * @return A pointer to the newly created instance of CSysInfoObserver.
    */
    static CSysInfoObserver* NewL( CSysInfoInterface* aSysInfoIf );

    /**
    * ~CSysInfoObserver
    * Destructor.
    */
    ~CSysInfoObserver() {}

    public:// from ISystemObserver

    /**
    * HandleResponseL ()
    * Delegates asycn response to client by calling 
    * MLiwNotifyCallback::HandleNotifyL().
    */		
    void HandleResponseL(const TDesC& aEntity,const TDesC& aKey, 
                            CSysData* aOutput, TInt32 aTransID, 
                            TSysRequest::TRequestType aType, TInt aError);

    private: // Constructors

    /**
    * CSysInfoObserver.
    * C++ default constructor.
    * @param aSysInfoIf The CSysInfoInterface instance.
    */
    CSysInfoObserver( CSysInfoInterface* aSysInfoIf );

    private: //Data        

    /**
    * iSysInfoIf
    * Handle to CSysInfoInterface instance.
    */
    CSysInfoInterface* iSysInfoIf;
    };

#endif // __SYSINFOOBSERVER_H__

// End of File