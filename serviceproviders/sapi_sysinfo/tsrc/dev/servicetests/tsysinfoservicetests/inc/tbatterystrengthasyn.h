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


#ifndef __CTBATTERY_STRENGTH_ASYNC_H__
#define __CTBATTERY_STRENGTH_ASYNC_H__

#include "watchtimer.h"
#include "sysinfoservice.h"

class CBatteryStrengthAsync : public CActive ,public ISystemObserver, public MTimeOutCallBack
{
public:
	static CBatteryStrengthAsync* NewL(CStifLogger* aLog);
	~CBatteryStrengthAsync();
	void Start();
	TInt Result();

	 void HandleResponseL(const TDesC& aEntity,const TDesC& aKey,
	 					CSysData* aOutput, TInt32 aTransID, TSysRequest::TRequestType aType, TInt aError);
	 
	 void HandleTimeOut	();

private:
	void ConstructL();
	CBatteryStrengthAsync(CStifLogger* aLog);
	
	virtual void DoCancel();
	virtual void RunL();
	
	
	void TestFuncL();

private:	
	CWatchTimer*			iTimer;
	CActiveSchedulerWait* 	iWaitSchedular;
	CSysInfoService*		iSysInfoService;
	TInt 					iResult;
	CStifLogger*			iLog;
};

#endif __CTBATTERY_STRENGTH_ASYNC_H__