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


#ifndef __CTSYSCONNECTIVITY_NOT_H__
#define __CTSYSCONNECTIVITY_NOT_H__


#include "sysinfoservice.h"


class CConnectivityNot : public CActive ,public ISystemObserver
{
public:
	static CConnectivityNot* NewL(CStifLogger* aLog, TInt aCmdId);
	~CConnectivityNot();
	void Start();
	TInt Result();

	 void HandleResponseL(const TDesC& aEntity,const TDesC& aKey,
	 					CSysData* aOutput, TInt32 aTransID,TSysRequest::TRequestType aType, TInt aError);
	 
	 
     enum TTestId
     {
     EWrongKey, 
     };
     
private:
	void ConstructL() ;
	CConnectivityNot(CStifLogger* aLog, TInt aCmdId) ;
	
	virtual void DoCancel() ;
	virtual void RunL();
	void TestFuncL() ;
	void TestFunc1L() ;
	void TestFunc2L() ;

private:	
   	CActiveSchedulerWait* 	iWaitScheduler;
	CSysInfoService*		iSysInfoService;
	TInt                    iResult;
	TInt                    iError;
	TInt                    iCount;
	TInt                    iCmdId ;
	CStifLogger*			iLog;
};

#endif __CTSYSCONNECTIVITY_NOT_H__