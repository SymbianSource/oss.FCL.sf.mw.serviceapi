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
* Description:   Tests battery notifications
*
*/


#ifndef __CTBATTERY_NOT_H__
#define __CTBATTERY_NOT_H__

#include "watchtimer.h"
#include "sysinfoservice.h"


class CBatteryNot : public CActive ,public ISystemObserver, public MTimeOutCallBack
{
public:
	static CBatteryNot* NewL(CStifLogger* aLog, TInt aCmdId);
	~CBatteryNot();
	void Start();
	TInt Result();

	 void HandleResponseL(const TDesC& aEntity,const TDesC& aKey,
	 					CSysData* aOutput, TInt32 aTransID, TSysRequest::TRequestType aType, TInt aError);
	 
	 void HandleTimeOut	();
     enum TTestId
     {
     EWrongData, 
     EWrongKey,	
     };
     
private:
	void ConstructL() ;
	CBatteryNot(CStifLogger* aLog, TInt aCmdId) ;
	
	virtual void DoCancel() ;
	virtual void RunL();
	void TestFuncL() ;
	void TestFunc1L() ;

private:	
    CWatchTimer*			iTimer;
	CActiveSchedulerWait* 	iWaitScheduler;
	CSysInfoService*		iSysInfoService;
	TInt                    iResult;
	TInt                    iError;
	TInt                    iCount;
	TInt                    iCmdId ;
	CStifLogger*			iLog;
};

#endif __CTBATTERY_NOT_H__