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
* Description:  A class to simulate sync behaviour for getlist Iterator.
*
*/




#ifndef SYNCBEHAVIOUR_H
#define SYNCBEHAVIOUR_H

#include <e32base.h>


class CContactSyncIter:public CActive
{
	CContactSyncIter();

	public:
		static CContactSyncIter* NewL();
		
		// Sets the request status to KRequestPending and Starts the Scheduler
		void Wait();
		
		//Called from RunL(). Stops the Scheduler
		void Signal();
		
		~CContactSyncIter();
	private:
		void RunL();
		void DoCancel();
		void ConstructL();
		
		// In case that a scheduler is not already installed
		CActiveScheduler* 		iNewscheduler;
		
		// Used to Wait for completion
		CActiveSchedulerWait* 	iWaitScheduler;

		TInt iInstalled;

};

#endif //SYNCBEHAVIOUR_H