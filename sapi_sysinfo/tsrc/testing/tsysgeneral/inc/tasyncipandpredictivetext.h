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



#ifndef __TASYNCIPANDPREDECTIVETEXT_H__
#define __TASYNCIPANDPREDECTIVETEXT_H__

#include "watchtimer.h"
#include "sysinfoservice.h"

class CTestIpAndPredTextNot : public CActive ,public ISystemObserver
{
public:
	static CTestIpAndPredTextNot* NewL(CStifLogger* aLog);
	
	~CTestIpAndPredTextNot();
	
	void Start();
	
	TInt Result();

    void HandleResponseL(const TDesC& aEntity,const TDesC& aKey, 
									CSysData* aResponse, TInt32 aTransID, 
									TSysRequest::TRequestType aType,
									TInt aError=KErrNone);
  	
 	void TestSetup(TInt, TInt) ;
private:
	void ConstructL();
	
	CTestIpAndPredTextNot(CStifLogger* aLog);
	
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


#endif __TASYNCIPANDPREDECTIVETEXT_H__