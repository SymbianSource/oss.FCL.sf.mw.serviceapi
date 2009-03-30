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



/*#ifndef __TMEMNOT_H__
#define __TMEMNOT_H__

#include "watchtimer.h"
#include "sysinfoservice.h"


class CCriticalMemNot : public CActive ,public ISystemObserver, public MTimeOutCallBack
{
public:
	static CCriticalMemNot* NewL(CStifLogger* aLog, TInt aDrive = 0, TInt aTestId = -1);
	
	~CCriticalMemNot();
	
	void Start();
	
	TInt Result();

    void HandleResponseL(const TDesC& aEntity,const TDesC& aKey, 
									CSysData* aResponse, TInt32 aTransID, 
									TInt aError=KErrNone);
  	
 	void HandleTimeOut();

	enum TTestId
	{
		ETestCriticalMem,
		ETestMemoryCard
	};

private:
	void ConstructL();
	
	CCriticalMemNot(CStifLogger* aLog, TInt aDrive, TInt aTestId);
	
	virtual void DoCancel();
	virtual void RunL();
	void TestFunc();
	void TestFunc1();

	
	
private:	
	CActiveSchedulerWait* 	iWaitScheduler;
	CSysInfoService*		iSysInfoService;
	CWatchTimer*			iTimer;
	TInt 					iResult;
	TInt                    iDrive ;
	TInt                    iCount ;
	TInt                    iTestId ;
	CStifLogger*			iLog;
	
};


#endif __TMEMNOT_H__*/