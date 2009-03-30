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



#ifndef __CTAUTOLOCKNOTIFIER_H__
#define __CTAUTOLOCKNOTIFIER_H__

#include "watchtimer.h"
#include <liwcommon.h>

class CLiwServiceHandler;
class CLiwGenericParamList;
class MLiwInterface;

class CAutoLockNotifier : public CActive ,public MLiwNotifyCallback, public MTimeOutCallBack
{
public:
	static CAutoLockNotifier* NewL(CStifLogger* aLog,TInt aAutoLockTime);
	~CAutoLockNotifier();
	void Start();
	TInt Result();

	TInt HandleNotifyL( TInt aCmdId, TInt aEventId,
            CLiwGenericParamList& aEventParamList,
            const CLiwGenericParamList& aInParamList);
    
    void HandleTimeOut();

private:
	void ConstructL();
	CAutoLockNotifier(CStifLogger* aLog,TInt aAutoLockTime);
	
	virtual void DoCancel();
	virtual void RunL();
	
	void TestFuncL();

	void CreateInterfaceL();

	TInt CheckErrorCode( const CLiwGenericParamList& aOutList, 
							TInt32 &aError );

private:	
	CWatchTimer*			iTimer;
	CActiveSchedulerWait* 	iWaitSchedular;
	CLiwServiceHandler* 	iServiceHandler;
	CLiwGenericParamList* 	iInParamList;
	CLiwGenericParamList*	iOutParamList;
	MLiwInterface* 			iInterface;
	TInt 					iResult;
	TInt 					iAutoLockTime;
	TInt					iRestoreAutoLockTime;
	TInt					iTransID;
	CStifLogger*			iLog;
};

#endif __CTAUTOLOCKNOTIFIER_H__