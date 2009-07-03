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
* Description:   Tests memory notifications
*
*/


#ifndef __CTMEMORY_NOT_H__
#define __CTMEMORY_NOT_H__

#include "watchtimer.h"
#include "sysinfoservice.h"


class CMemNot : public CActive ,public ISystemObserver, public MTimeOutCallBack
{
public:
	static CMemNot* NewL(CStifLogger* aLog, TInt aCmdId);
	~CMemNot();
	void Start();
	TInt Result();

	 void HandleResponseL(const TDesC& aEntity,const TDesC& aKey,
	 					CSysData* aOutput, TInt32 aTransID, TSysRequest::TRequestType aType,TInt aError);
	 
	 void HandleTimeOut	();
     enum TTestId
     {
     EUnsupported, 
     EWrongKey,	
     };
     
private:
	void ConstructL() ;
	CMemNot(CStifLogger* aLog, TInt aCmdId) ;
	
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

#endif __CTMEMORY_NOT_H__