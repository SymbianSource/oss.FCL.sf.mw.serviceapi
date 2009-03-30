/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  
*
*/


#ifndef __MESSAGINGSERVICEHANDLER_H
#define __MESSAGINGSERVICEHANDLER_H

#include <LiwCommon.h>
#include <LiwServiceIfBase.h>

/**
* Provides implementation to CLiwServiceIfBase interface.
*
**/
class CMessagingServiceHandler : public CLiwServiceIfBase
	{
	public:
		static CMessagingServiceHandler* NewL();


	// CLiwServiceIfBase member functions
        /**
        * Called by the LIW framework to initialise necessary information 
        * from the Service Handler. This method is called when the consumer makes 
        * the attach operation.
        *
        * @param aFrameworkCallback Framework provided callback for provider to send 
        *                           events to framework.
        * @param aInterest List of criteria items which invoked the provider.
        */
		virtual void InitialiseL( 
						MLiwNotifyCallback& aFrameworkCallback, 
						const RCriteriaArray& aInterest);

        /**
        * Executes generic service commands included in criteria.
        *
        * @param aCmdId Command to be executed.
        * @param aInParamList Input parameters, can be an empty list.
        * @param aOutParamList Output parameters, can be an empty list.
        * @param aCmdOptions Options for the command, see KLiwOpt* in LiwCommon.hrh.
        * @param aCallback Callback for asynchronous command handling, parameter checking, etc.
        * @leave KErrArgument Callback is missing when required.
        * @leave KErrNotSupported No provider supports service.
        */
		virtual void HandleServiceCmdL( 
						const TInt& aCmdId, 
						const CLiwGenericParamList& aInParamList,
						CLiwGenericParamList& aOutParamList,
						TUint aCmdOptions = 0,
						const MLiwNotifyCallback* aCallback = NULL);

	private:
        /**
        * Constructor.
        */
		CMessagingServiceHandler();

	};

#endif __MESSAGINGSERVICEHANDLER_H