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
* Description:  CLandmarkManageObjects class
 *
*/


#ifndef __CLANDMARKMANAGEOBJECTS_H__
#define __CLANDMARKMANAGEOBJECTS_H__

// INCLUDES
#include <e32base.h>

//FORWARD DECLARATION
class CLandmarkCmdBase;

/**
 * CLandmarkManageObjects
 * This class inherits from CActive. This acts as a garbage collector for inactive 
 * active objects.
 */
// CLASS DECLARATION
NONSHARABLE_CLASS(CLandmarkManageObjects) : public CActive
	{
public: // New methods

	/**
	 * NewL.
	 * Two-phased constructor.
	 * Create a CLandmarkManageObjects object.
	 * @return a pointer to the created instance of CLandmarkManageObjects.
	 */
	static CLandmarkManageObjects* NewL();

	/**
	 * ~CLandmarkManageObjects
	 * Destructor.
	 */
	~CLandmarkManageObjects();

public:

	/**
	 * Start
	 * This functions proceeds with the search for inactive active objects.
	 */
	void Start();

	/**
	 * AppendL
	 * This functions appends a newly created active object to its internal array.
	 * @param aObject The pointer to the newly created active object.
	 */
	void AppendL( CLandmarkCmdBase* aObject );

	/**
	 * CancelObject
	 * This functions cancels an ongoing asynchronous request.
	 * @param aTransactionId The transaction id of the asynchronous request to be cancelled.
	 */
	void CancelObject( TInt32 aTransactionId );

private://from CActive

	// RunL.
	// This functions gets called after completion of async request.
	void RunL();

	// DoCancel.
	// This function will cancel ongoing async call.
	void DoCancel();

private: // Constructors

	/**
	 * CLandmarkManageObjects.
	 * C++ default constructor.
	 */
	CLandmarkManageObjects();

private://Data

	/**
	 * iObjects
	 * Array of active object pointers.
	 */
	RPointerArray<CLandmarkCmdBase> iObjects;
	};

#endif // __CLANDMARKMANAGEOBJECTS_H__

// End of File
