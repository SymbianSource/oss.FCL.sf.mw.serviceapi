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
* Description:  CLandmarkCmdBase class
 *
*/


#ifndef __CLANDMARKCMDBASE_H__
#define __CLANDMARKCMDBASE_H__

// INCLUDES
#include <e32base.h>

//FORWARD DECLARATION
class CLandmarkHandler;
class CLandmarkFilter;
class MLandmarkObserver;
class CPosLmOperation;
class CLandmarkManageObjects;

/**
 * CLandmarkCmdBase
 * This class inherits from CActive. 
 * This forms the base class for all active objects related to landmarks database async requests.
 * TransactionId()  returns the transaction id of the active object.
 * StartL ( CLandmarkHandler* aHandle, TInt32 aTransactionId, 
 *					 CLandmarkFilter* aFilter ) is a pure virtual function that has to be implemented.
 */
// CLASS DECLARATION
NONSHARABLE_CLASS(CLandmarkCmdBase): public CActive
	{
public: //destructor

	/**
	 * ~CLandmarkCmdBase.
	 * Destructor.
	 */
	virtual ~CLandmarkCmdBase()
		{}

	/**
	 * TransactionId.
	 * @return The transaction id of the active object.
	 */
	inline TInt32 TransactionId();

	/**
	 * StartL.
	 * This function has to be implemented for starting the asynchronous search operation.
	 * @param aHandle The CLandmarkHandler instance that has the handle to the database 
	 * on which the search operation is to be made.
	 * @param aTransactionId The transaction id assigned to the asynchronous call.
	 * @param aFilter The filter to be used for the search.
	 */
	virtual void StartL ( CLandmarkHandler* aHandle, TInt32 aTransactionId,
			CLandmarkFilter& aFilter ) = 0;

protected: //constructor

	/**
	 * CLandmarkCmdBase.
	 * Constructor.
	 */
	inline CLandmarkCmdBase();

protected: // Data members

	/**
	 * iTransactionId
	 * The tranaction id assigned to aync request.
	 */
	TInt32 iTransactionId;

	/**
	 * iObserver
	 * The handle to the MLandmarkObserver.
	 */
	MLandmarkObserver* iObserver;

	/**
	 * iHandle
	 * The handle to the CLandmarkHandler.
	 */
	CLandmarkHandler* iHandle;

	/**
	 * iSearchOperation
	 * The handle to the CPosLmOperation.
	 */
	CPosLmOperation* iSearchOperation;

	/**
	 * iManageObjects
	 * The handle to the garbage collector.
	 */
	CLandmarkManageObjects* iManageObjects;

	/**
	 * iProgress
	 * To keep track of search progress.
	 */
	TReal32 iProgress;
	};

#include "clandmarkcmdbase.inl"

#endif // __CLANDMARKCMDBASE_H__

// End of File
