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
* Description:  MLandmarkObserver class
 *
*/


#ifndef __MLANDMARKOBSERVER_H__
#define __MLANDMARKOBSERVER_H__

#include <EPos_Landmarks.h>
// FORWARD DECLARATION
class CPosLmItemIterator;
class CLandmarkHandler;
/**
 * MLandmarkObserver
 * This class is an observer interface.
 */
// CLASS DECLARATION
NONSHARABLE_CLASS(MLandmarkObserver )
	{
public:
	/**
	 * HandleLandmarkItemsL.
	 * This is a pure virtual method that has to be implemented.
	 * It should notify the client with the status of the asynchronous request.
	 * @param aIterator The iterator to iterate through the list of landmarks.
	 * @param aTransactionId The transaction id of the async call.
	 * @param aError Whether the async call was able to complete without errors.
	 * @param aDatabaseUri The uri of the database on which the iterator can be used.
	 */
	virtual void HandleLandmarkItemsL( CPosLmItemIterator* aIterator,
			TInt32 aTransactionId, TInt aError, CLandmarkHandler* aHandler ) = 0;

	/**
	 * HandleCategoryItemsL.
	 * This is a pure virtual method that has to be implemented.
	 * It should notify the client with the status of the asynchronous request.
	 * @param aIterator The iterator to iterate through the list of landmark categories.
	 * @param aTransactionId The transaction id of the async call.
	 * @param aError Whether the async call was able to complete without errors.
	 * @param aDatabaseUri The uri of the database on which the iterator can be used.
	 */
	virtual void HandleCategoryItemsL( CPosLmItemIterator* aIterator,
			TInt32 aTransactionId, TInt aError, CLandmarkHandler* aHandler ) = 0;
	
	virtual void HandleAddItemsL( TPosLmItemId aId,
				TInt32 aTransactionId, TInt aError ) = 0;
	
	virtual void HandleItemsL( TInt32 aTransactionId, TInt aError ) = 0;
	
	}
;

#endif // __MLANDMARKOBSERVER_H__

// End of File
