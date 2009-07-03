/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef __CLandmarkAsyncTests_H__
#define __CLandmarkAsyncTests_H__

#include <e32base.h>
#include "mlandmarkobserver.h"
#include "Clmlandmarkstest.h"

class CLandmarkService;
class CPosLmItemIterator;
class MAiwNotifyCallback;
class CPosLandmarkDatabase;

class CLandmarkAsyncTests : public CActive, public MLandmarkObserver
{
public:
	enum TESTID
	{
		ETEST1,
		ETEST2,
	};

	static CLandmarkAsyncTests* NewL(CLandmarkAsyncTests::TESTID aTestID);
	~CLandmarkAsyncTests();
	void StartL();
	TInt Result();
	
private:

	void ConstructL();
	CLandmarkAsyncTests(CLandmarkAsyncTests::TESTID );
	
	virtual void DoCancel();
	virtual void RunL();
	
	
	void AsyncTestFunc1L();
	void AsyncTestFunc2L();	
private:
	void CreateLandmarksL();
protected:
		// MLandmarkObserver callback for Landmarks getlist iterator.
		void HandleLandmarkItemsL( CPosLmItemIterator* aIterator,
            TInt32 aTransactionId, TInt aError, const TDesC& aDatabaseUri);
		// MLandmarkObserver callback for catetories getlist iterator.
		void HandleCategoryItemsL( CPosLmItemIterator* aIterator,
            TInt32 aTransactionId, TInt aError, const TDesC& aDatabaseUri);	

private:	
	CActiveSchedulerWait* 	iWaitSchedular;
	CPosLandmarkDatabase* 	iDefaultLmHandle;
	CLandmarkService*		iService;
	TInt 					iResult;
	TESTID					iTestID;	
};

#endif __CLandmarkAsyncTests_H__