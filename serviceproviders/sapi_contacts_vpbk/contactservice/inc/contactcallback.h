/*
* Copyright (c) 2006-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Provides the callback interface
*
*/

#ifndef M_CCONTACTCALLBACK_H
#define M_CCONTACTCALLBACK_H

#include "contactservice.hrh"
// FORWARD DECLARATIONS
class CContactIter;

/**
 * MContactCallback - callback interface class
 * 
 */
class MContactCallback
    {
    public:
		/*
		 *Called to Indicate success or failure for sapis other than GetList
		 */
        virtual void HandleReturnValue(TOperationEvent aEventId, const TInt& aError, 
                                       TInt aTransId ) = 0;
        /*
         *Called after GetList async call is complete
         */
        virtual void HandleReturnIter(const TInt& aError, 
                                      CContactIter* aIter,
                                      TInt aTransId ) = 0;
        
        virtual void HandleReturnId(const TInt& aError, 
                                    HBufC8* aId,
                                    TInt aTransId ) = 0;
        

        virtual void HandleReturnArray(const TInt& aError, 
                RPointerArray<HBufC8>& aArray,
                                              TInt aTransId ) = 0;
    };
        
#endif // M_CONTACTCALLBACK_H