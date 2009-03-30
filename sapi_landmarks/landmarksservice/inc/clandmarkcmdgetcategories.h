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
* Description:  CLandmarkCmdGetCategories class
 *
*/


#ifndef __CLANDMARKCMDGETCATEGORIES_H__
#define __CLANDMARKCMDGETCATEGORIES_H__

// INCLUDES
#include "clandmarkcmdbase.h"

/**
 * CLandmarkCmdGetCategories
 * This class processes the async request for retrieval of landmark categories from the landmark
 * database. It implements the StartL ( CLandmarkHandler* aHandle, TInt32 aTransactionId, CLandmarkFilter* aFilter )
 * of CLandmarkCmdBase. After completion of the aynchronous request the MLandmarkObserver instance is notified
 * and the garbage collector is set active.
 */
// CLASS DECLARATION
NONSHARABLE_CLASS(CLandmarkCmdGetCategories) : public CLandmarkCmdBase
	{
public: // New methods

	/**
	 * NewL.
	 * Two-phased constructor.
	 * Create a CLandmarkCmdGetCategories object.
	 * @param aObserver The pointer to the observer for this object.
	 * @param aManageObjects The pointer to the garbage collector.
	 * @return A pointer to the created instance of CLandmarkCmdGetCategories.
	 */
	static CLandmarkCmdGetCategories* NewL( MLandmarkObserver* aObserver,
			CLandmarkManageObjects* aManageObjects );

	/**
	 * NewLC.
	 * Two-phased constructor.
	 * Create a CLandmarkCmdGetCategories object.
	 * @param aObserver The pointer to the observer for this object.
	 * @param aManageObjects The pointer to the garbage collector.
	 * @return A pointer to the created instance of CLandmarkCmdGetCategories.
	 */
	static CLandmarkCmdGetCategories* NewLC( MLandmarkObserver* aObserver,
			CLandmarkManageObjects* aManageObjects );

	/**
	 * ~CLandmarkCmdGetCategories
	 * Destructor.
	 */
	~CLandmarkCmdGetCategories();

public: // From CLandmarkCmdBase

	//StartL
	// This functions proceeds with the incremental search.
	void StartL ( CLandmarkHandler* aHandle,
			TInt32 aTransactionId, CLandmarkFilter& aFilter );

private:

	/**
	 * NextStep
	 * This functions proceeds with the incremental search.
	 */
	void NextStep ();

private: // From CActive

	// RunL.
	// This functions gets called after completion of async request.
	void RunL();

	// DoCancel.
	// This function will cancel ongoing async call.
	void DoCancel();

	// RunError.
	// This functions handles a leave occurring in the request completion event handler
	TInt RunError(TInt aError);

private: // Constructors

	/**
	 * CLandmarkCmdGetCategories.
	 * C++ default constructor.
	 * @param aObserver The pointer to the observer for this object.
	 * @param aManageObjects The pointer to the garbage collector.
	 */
	CLandmarkCmdGetCategories ( MLandmarkObserver* aObserver,
			CLandmarkManageObjects* aManageObjects );

	};

#endif // __CLANDMARKCMDGETCATEGORIES_H__

// End of File
