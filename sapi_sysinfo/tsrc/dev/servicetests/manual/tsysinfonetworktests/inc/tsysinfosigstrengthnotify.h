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
* Description:   tsysinfosigstrengthnotify
*
*/


#ifndef __CTSYSINFOSIGSTRENGTHNOTIFIER_H__
#define __CTSYSINFOSIGSTRENGTHNOTIFIER_H__

#include "watchtimer.h"
#include "sysinfoservice.h"

class CSignalStrNotify : public CActive ,public ISystemObserver, public MTimeOutCallBack
{
public:
	static CSignalStrNotify* NewL(CStifLogger* aLog,TInt Strength);
	~CSignalStrNotify();
	void Start();
	TInt Result();

	 void HandleResponseL(const TDesC& aEntity,const TDesC& aKey,
	 					CSysData* aOutput, TInt32 aTransID, TSysRequest::TRequestType aType,TInt aError);
	 
	 void HandleTimeOut	();

private:
	void ConstructL();
	CSignalStrNotify(CStifLogger* aLog,TInt Strength);
	
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

#endif __CTSYSINFOSIGSTRENGTHNOTIFIER_H__