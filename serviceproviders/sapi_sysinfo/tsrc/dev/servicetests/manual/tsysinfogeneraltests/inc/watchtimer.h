/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:   twatchtimer
*
*/



#ifndef _CWATCHTIMER_H_
#define _CWATCHTIMER_H_

#include <e32base.h>

class MTimeOutCallBack
{
public:
	virtual void HandleTimeOut() = 0;
};

class CWatchTimer:public CTimer
{
	public:
		static CWatchTimer* NewL(TInt aPriority,MTimeOutCallBack* aCallback);
		
	protected:
	
		void RunL();
	private:
		CWatchTimer(TInt aPriority,MTimeOutCallBack* aCallback);
		void ConstructL();
	private:
		MTimeOutCallBack* iCallback;
};

#endif _CWATCHTIMER_H_