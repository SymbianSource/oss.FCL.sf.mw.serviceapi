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
* Description:   ?Description
*
*/


#include "watchtimer.h"

CWatchTimer::CWatchTimer(TInt aPriority,MTimeOutCallBack* aCallback)
						:CTimer(aPriority),iCallback(aCallback)
{
	CActiveScheduler::Add(this);
}

CWatchTimer* CWatchTimer::NewL(TInt aPriority,MTimeOutCallBack* aCallback)
{
	CWatchTimer* self = new (ELeave) CWatchTimer(aPriority,aCallback);
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
}

void CWatchTimer::ConstructL()
{
	CTimer::ConstructL();
}

void CWatchTimer::RunL()
{
	iCallback->HandleTimeOut();
}