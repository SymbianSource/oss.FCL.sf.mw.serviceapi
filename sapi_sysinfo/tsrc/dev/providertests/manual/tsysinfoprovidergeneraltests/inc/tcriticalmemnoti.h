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
#include <liwcommon.h>
 
class CLiwServiceHandler;
class CLiwGenericParamList;
class MLiwInterface;

class CTCriticalMemNotification : public CActive ,public MLiwNotifyCallback, public MTimeOutCallBack
{
public:
	static CTCriticalMemNotification* NewL(CStifLogger* aLog,TInt aDrvNo);
	~CTCriticalMemNotification();
	void Start();
	TInt Result();

	TInt HandleNotifyL( TInt aCmdId, TInt aEventId,
            CLiwGenericParamList& aEventParamList,
            const CLiwGenericParamList& aInParamList);
	 
	 void HandleTimeOut	();

private:
	void ConstructL();
	CTCriticalMemNotification(CStifLogger* aLog,TInt aDrvNo);
	
	virtual void DoCancel();
	virtual void RunL();
	
	void TestFuncL();

	void CreateInterfaceL();

	TInt CheckErrorCode( const CLiwGenericParamList& aOutList, 
							TInt32 &aError );
private:	
	CWatchTimer*			iTimer;
	CLiwServiceHandler* 	iServiceHandler;
	CLiwGenericParamList* 	iInParamList;
	CLiwGenericParamList*	iOutParamList;
	MLiwInterface* 			iInterface;
	CActiveSchedulerWait* 	iWaitSchedular;
	TInt 					iResult;
	TInt32					iTransID;
	CStifLogger*			iLog;
	TInt					iDrvNo;
};

#endif __CTCRITICALMEMNOTIFIER_H__