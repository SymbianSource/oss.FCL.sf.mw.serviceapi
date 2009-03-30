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
* Description:   tsignalstrengthasyn
*
*/


#ifndef __CTSIGSTRENGTHASYNC_H__
#define __CTSIGSTRENGTHASYNC_H__

#include <Liwcommon.h>

#include "watchtimer.h"
#include "sysinfoservice.h"

class CSignalStrAsync : public CActive ,public MLiwNotifyCallback, public MTimeOutCallBack
{
public:
	static CSignalStrAsync* NewL(CStifLogger* aLog,TInt Strength);
	~CSignalStrAsync();
	void Start();
	TInt Result();

	TInt HandleNotifyL(TInt aCmdId,
			            TInt aEventId,
			            CLiwGenericParamList& aEventParamList,
			            const CLiwGenericParamList& aInParamList);
	 void HandleTimeOut	();

private:
	void ConstructL();
	CSignalStrAsync(CStifLogger* aLog,TInt Strength);
	
	virtual void DoCancel();
	virtual void RunL();
	
	
	void TestFuncL();

private:	
	CWatchTimer*			iTimer;
	CActiveSchedulerWait* 	iWaitSchedular;
	CLiwServiceHandler* iServiceHandler;
	MLiwInterface* interface ;
	TInt 					iSignalStrength ;
	TInt 					iResult;
	CStifLogger*			iLog;
};

#endif __CTSIGSTRENGTHASYNC_H__