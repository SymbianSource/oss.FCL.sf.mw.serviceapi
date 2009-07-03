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
* Description:  CLandmarkProvider class
*
*/


#ifndef __LANDMARKPROVIDER_H__
#define __LANDMARKPROVIDER_H__

// INCLUDES
#include <liwserviceifbase.h>

/**
* CLandmarkProvider
* This class inherits from CLiwServiceIfBase and implements the
* InitialiseL( MLiwNotifyCallback& aFrameworkCallback,
*           const RCriteriaArray& aInterest) and
* HandleServiceCmdL( const TInt& aCmdId,
*           const CLiwGenericParamList& aInParamList,
*           CLiwGenericParamList& aOutParamList, TUint aCmdOptions = 0,
*           const MLiwNotifyCallback* aCallback = NULL) functions.
* It constructs and returns the interface to the client.
*/
// CLASS DECLARATION
class CLandmarkProvider: public CLiwServiceIfBase
    {
    public://New Methods

        /**
        * NewL.
        * Two-phased constructor.
        * Create a CLandmarkProvider object.
        * @return a pointer to the created instance of CLandmarkProvider.
        */
        static CLandmarkProvider* NewL();

        /**
        * ~CLandmarkProvider
        * Destructor.
        */
        ~CLandmarkProvider();

    public: // from CLiwServiceIfBase

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
        * CLandmarkProvider.
        * C++ default constructor.
        */
        CLandmarkProvider();
    };
#endif //__LANDMARKPROVIDER_H__