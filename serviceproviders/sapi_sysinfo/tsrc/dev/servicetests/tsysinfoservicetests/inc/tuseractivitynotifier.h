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


#ifndef __CTUSERACTIVITY_NOTIFIER_H__
#define __CTUSERACTIVITY_NOTIFIER_H__

#include "watchtimer.h"
#include "sysinfoservice.h"

class CTestUserActivity : public CActive ,public ISystemObserver, public MTimeOutCallBack
{
public:
	enum Test_Type
	{
		ETESTINACTIVITY,
		ETESTACTIVITY
	};
public:
	static CTestUserActivity* NewL(CStifLogger* aLog,TInt aTimeOut,Test_Type aType);
	~CTestUserActivity();
	void Start();
	TInt Result();

	 void HandleResponseL(const TDesC& aEntity,const TDesC& aKey,
	 					CSysData* aOutput, TInt32 aTransID, TSysRequest::TRequestType aType, TInt aError);
	 
	 void HandleTimeOut	();

private:
	void ConstructL();
	CTestUserActivity(CStifLogger* aLog,TInt aTimeOut,Test_Type aType);
	
	virtual void DoCancel();
	virtual void RunL();
	
	
	void TestFuncL();

private:	
	CStifLogger*			iLog;
	CWatchTimer*			iTimer;
	CActiveSchedulerWait* 	iWaitSchedular;
	CSysInfoService*		iSysInfoService;
	TInt 					iInactivityTimeOut;
	TInt 					iResult;
	Test_Type				iTestType;
};

#endif __CTUSERACTIVITY_NOTIFIER_H__
