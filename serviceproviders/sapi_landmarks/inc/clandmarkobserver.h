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
* Description:  CLandmarkObserver class for handling async requests
*
*/


#ifndef __CLANDMARKOBSERVER_H__
#define __CLANDMARKOBSERVER_H__

#include <e32base.h>
#include "mlandmarkobserver.h"

//FORWARD DECLARATION
class CLiwGenericParamList;
class CLandmarkInterface;

/**
* CLandmarkObserver
* This class acts as an observer for all asynchronous requests. After the request
* is completed, it checks for error and packs it in output param list. If there
* is no error, then the iterator is also packed into the output param list.
*/
// CLASS DECLARATION
NONSHARABLE_CLASS(CLandmarkObserver): public CBase, public MLandmarkObserver
    {
    public: // New methods

        /**
        * NewL.
        * Two-phased constructor.
        * Create a CLandmarkObserver object.
        * @param aLmIface The CLandmarkInterface instance.
        * @return A pointer to the newly created instance of CLandmarkObserver.
        */
        static CLandmarkObserver* NewL( CLandmarkInterface* aLmIface );

	/**
	 * ~CLandmarkObserver
	 * Destructor.
	 */
	~CLandmarkObserver();

    public:// from MLandmarkObserver

	// HandleLandmarkItemsL.
	// Notifies client of state change and calls MLiwNotifyCallback::HandleNotifyL().
	void HandleLandmarkItemsL(CPosLmItemIterator* aIterator,
			TInt32 aTransactionId, TInt aError, CLandmarkHandler* aHandler);

	// HandleCategoryItemsL.
	// Notifies client of state change and calls MLiwNotifyCallback::HandleNotifyL().
	void HandleCategoryItemsL(CPosLmItemIterator* aIterator,
			TInt32 aTransactionId, TInt aError, CLandmarkHandler* aHandler);

	void HandleAddItemsL(TPosLmItemId aId, TInt32 aTransactionId, TInt aError);

	void HandleItemsL(TInt32 aTransactionId, TInt aError);


    private: // Constructors

        /**
        * CLandmarkObserver.
        * C++ default constructor.
        * @param aLmIface The CLandmarkInterface instance.
        */
        CLandmarkObserver( CLandmarkInterface* aLmIface );

    private: //Data        
        
        /**
        * iLmIface
        * Handle to CLandmarkInterface instance.
        */
        CLandmarkInterface* iLmIface;
	/**
	 * iId
	 * The id of the added/modified landmark/category.
	 */
	HBufC* iId;
    };

#endif // __CLANDMARKOBSERVER_H__

// End of File