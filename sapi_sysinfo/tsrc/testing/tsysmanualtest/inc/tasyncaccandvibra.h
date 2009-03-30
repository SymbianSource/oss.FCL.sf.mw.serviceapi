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



#ifndef __TASYNCIACCANDVIBRA_H__
#define __TASYNCIACCANDVIBRA_H__

#include "watchtimer.h"
#include "sysinfoservice.h"

class CTestAccAndVibraNot : public CActive ,public ISystemObserver
{
public:
	static CTestAccAndVibraNot* NewL(CStifLogger* aLog);
	
	~CTestAccAndVibraNot();
	
	void Start();
	
	TInt Result();

    void HandleResponseL(const TDesC& aEntity,const TDesC& aKey, 
									CSysData* aResponse, TInt32 aTransID, 
									TSysRequest::TRequestType aType,
									TInt aError=KErrNone);
  	
 	void TestSetup(TInt) ;
private:
	void ConstructL();
	
	CTestAccAndVibraNot(CStifLogger* aLog);
	
	virtual void DoCancel();

	virtual void RunL();
	
	void TestFunc();

	
	
private:	
	CActiveSchedulerWait* 	iWaitScheduler;
	CSysInfoService*		iSysInfoService;
	TInt 					iResult;
	TInt                    iCount ;	
	CStifLogger*			iLog;

};


#endif __TASYNCIACCANDVIBRA_H__