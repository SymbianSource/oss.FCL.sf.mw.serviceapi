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



#ifndef __CTCRITICALMEMNOTIFIER_H__
#define __CTCRITICALMEMNOTIFIER_H__

#include "watchtimer.h"
#include "sysinfoservice.h"

class CTCriticalMemNotification : public CActive ,public ISystemObserver, public MTimeOutCallBack
{
public:
	static CTCriticalMemNotification* NewL(CStifLogger* aLog,TInt aDrvNo);
	~CTCriticalMemNotification();
	void Start();
	TInt Result();

	 void HandleResponseL(const TDesC& aEntity,const TDesC& aKey,
	 					CSysData* aOutput, TInt32 aTransID, TSysRequest::TRequestType aType, TInt aError);
	 
	 void HandleTimeOut	();

private:
	void ConstructL();
	CTCriticalMemNotification(CStifLogger* aLog,TInt aDrvNo);
	
	virtual void DoCancel();
	virtual void RunL();
	
	
	void TestFuncL();

private:	
	CWatchTimer*			iTimer;
	CActiveSchedulerWait* 	iWaitSchedular;
	CSysInfoService*		iSysInfoService;
	TInt 					iResult;
	CStifLogger*			iLog;
	TInt					iDrvNo;
};

#endif __CTCRITICALMEMNOTIFIER_H__