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
* Description:  CLandmarkCmdGetLandmarks class
 *
*/

#ifndef CLANDMARKDUMMYAO_H_
#define CLANDMARKDUMMYAO_H_

// INCLUDES
#include <e32base.h>
#include <EPos_Landmarks.h>
/**
 * CLandmarkDummyAO
 * This class inherits from CActive. This class is used to emulate 
 * asynchronous processing.
 */
// CLASS DECLARATION
NONSHARABLE_CLASS(CLandmarkDummyAO) : public CActive
	{
public:
	enum TCommand
		{
		EAdd, EUpdate, ERemove,
		};
public:
	// New methods

	/**
	 * NewL.
	 * Two-phased constructor.
	 * Create a CLandmarkDummyAO object.
	 * @return a pointer to the created instance of CLandmarkDummyAO.
	 */
	CLandmarkDummyAO(MLandmarkObserver* aObserver,
			CLandmarkManageObjects* aManageObjects);

	/**
	 * ~CLandmarkDummyAO
	 * Destructor.
	 */
	~CLandmarkDummyAO();

public:

	void Start(TInt32 aTransactionId,
			CLandmarkDummyAO::TCommand aCmd, TPosLmItemId aId,
			TInt aError);

private:
    
    void Delay(TInt aError);
    
	//from CActive

	// RunL.
	// This functions gets called after completion of async request.
	void RunL();

	// DoCancel.
	// This function will cancel ongoing async call.
	void DoCancel();

private:
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
	 * iManageObjects
	 * The handle to the garbage collector.
	 */
	CLandmarkManageObjects* iManageObjects;

	TCommand iCmd;

	TPosLmItemId iId;

	TBool iIsDelay;
	};

#endif /* CLANDMARKDUMMYAO_H_ */

// End of File
