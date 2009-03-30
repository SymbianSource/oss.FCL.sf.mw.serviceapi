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


#ifndef __CTCURRENTNETWORKNOTIFIER_H__
#define __CTCURRENTNETWORKNOTIFIER_H__

#include "watchtimer.h"
#include "sysinfoservice.h"

class CCurrentNetNotify : public CActive ,public MLiwNotifyCallback, public MTimeOutCallBack
{
public:
	static CCurrentNetNotify* NewL(CStifLogger* aLog);
	~CCurrentNetNotify();
	void Start();
	TInt Result();

   TInt HandleNotifyL(TInt aCmdId,
			            TInt aEventId,
			            CLiwGenericParamList& aEventParamList,
			            const CLiwGenericParamList& aInParamList);
	 void HandleTimeOut	();

private:
	void ConstructL();
	CCurrentNetNotify(CStifLogger* aLog);
	
	virtual void DoCancel();
	virtual void RunL();
	
	
	void TestFuncL();

private:	
	CWatchTimer*			iTimer;
	CActiveSchedulerWait* 	iWaitSchedular;
	CLiwServiceHandler* iServiceHandler;
	MLiwInterface* interface ;
	TInt 					iResult;
	CStifLogger*			iLog;
	TInt iTransId;

};

#endif __CTCURRENTNETWORKNOTIFIER_H__