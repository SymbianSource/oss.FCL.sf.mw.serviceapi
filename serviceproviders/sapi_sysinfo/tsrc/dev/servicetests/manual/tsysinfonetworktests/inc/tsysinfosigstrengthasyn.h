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
* Description:   tsysinfosigstrengthasyn
*
*/


#ifndef __CTSYSINFOSIGSTRENGTHASYNC_H__
#define __CTSYSINFOSIGSTRENGTHASYNC_H__

#include "watchtimer.h"
#include "sysinfoservice.h"

class CSignalStrAsync : public CActive ,public ISystemObserver, public MTimeOutCallBack
{
public:
	static CSignalStrAsync* NewL(CStifLogger* aLog,TInt Strength);
	~CSignalStrAsync();
	void Start();
	TInt Result();

	 void HandleResponseL(const TDesC& aEntity,const TDesC& aKey,
	 					CSysData* aOutput, TInt32 aTransID, TSysRequest::TRequestType aType,TInt aError);
	 
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
	CSysInfoService*		iSysInfoService;
	TInt 					iSignalStrength ;
	TInt 					iResult;
	CStifLogger*			iLog;
};

#endif __CTSYSINFOSIGSTRENGTHASYNC_H__