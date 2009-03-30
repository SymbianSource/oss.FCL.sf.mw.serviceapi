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
* Description:  CSysInfoProvider class
*
*/


#ifndef __SYSINFOPROVIDER_H__
#define __SYSINFOPROVIDER_H__

// INCLUDES
#include <liwserviceifbase.h>

/**
* CSysInfoProvider
* This class inherits from CAiwServiceIfBase and implements the
* InitialiseL( MLiwNotifyCallback& aFrameworkCallback,
*           const RCriteriaArray& aInterest) and
* HandleServiceCmdL( const TInt& aCmdId,
*           const CLiwGenericParamList& aInParamList,
*           CLiwGenericParamList& aOutParamList, TUint aCmdOptions = 0,
*           const MLiwNotifyCallback* aCallback = NULL) functions.
* It constructs and returns the interface to the client.
*/
// CLASS DECLARATION
class CSysInfoProvider: public CLiwServiceIfBase
    {
    public://New Methods

        /**
        * NewL.
        * Two-phased constructor.
        * Create a CSysInfoProvider object.
        * @return a pointer to the created instance of CSysInfoProvider.
        */
        static CSysInfoProvider* NewL();

        /**
        * ~CSysInfoProvider
        * Destructor.
        */
        ~CSysInfoProvider();

    public: // from CAiwServiceIfBase

        // Called by the AIW framework to initialise provider with necessary information
        // from the Service Handler. This method is called when the consumer makes
        // the attach operation.
        void InitialiseL( MLiwNotifyCallback& aFrameworkCallback,
            const RCriteriaArray& aInterest);

        //Executes generic service commands included in criteria.
        void HandleServiceCmdL( const TInt& aCmdId,
            const CLiwGenericParamList& aInParamList,
            CLiwGenericParamList& aOutParamList, TUint aCmdOptions = 0,
            const MLiwNotifyCallback* aCallback = NULL);

    private:// Constructors

        /**
        * CSysInfoProvider.
        * C++ default constructor.
        */
        CSysInfoProvider();
    };
#endif //__SYSINFOPROVIDER_H__