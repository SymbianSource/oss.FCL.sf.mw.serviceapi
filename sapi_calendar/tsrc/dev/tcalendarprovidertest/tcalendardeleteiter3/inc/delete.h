/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  
*
*/

#include <e32base.h>
#include <BADESCA.H>
#include<LiwCommon.h>
#include <f32file.h>

class CLiwServiceHandler;

/**
 * Callback class for asynchronous SAPI message header
*/	

class CCalCallback : public MLiwNotifyCallback
	{
	public:
		
		static CCalCallback* NewL(CActiveSchedulerWait* aWaitSchedular, MLiwInterface* aInterface, TInt& aRes, TInt& aFlag);
		
		virtual ~CCalCallback(){}
		
		TInt HandleNotifyL(TInt aCmdId,
        TInt aEventId,
        CLiwGenericParamList& aEventParamList,
        const CLiwGenericParamList& aInParamList);
		
	private:
	
 		CCalCallback(CActiveSchedulerWait* aWaitSchedular, MLiwInterface* aInterface, TInt& aRes, TInt& aFlag):iWaitSchedular(aWaitSchedular), iInterface(aInterface), iResult(aRes), iOption(aFlag){ }

		CActiveSchedulerWait* 	iWaitSchedular;
		MLiwInterface* 			iInterface ;
		TInt& iResult;
		TInt& iOption;	
	};


class CTestAsync : public CActive
{
public:
	static CTestAsync* NewL();
	~CTestAsync();
	TInt Start(TInt aFlag, TBool);
	void CancelNotification();
	
	
private:
	void ConstructL();
	CTestAsync();
	
	virtual void DoCancel();
	virtual void RunL();
	
	
	int TestFunc();
	
private:	
	CLiwServiceHandler* 	iServiceHandler;
	CActiveSchedulerWait* 	iWaitSchedular;
	TInt 					iResult;
	MLiwInterface* 			interface ;	
	CCalCallback*			iCallback;
	TInt iFlag;
	TBool iAsync;

};

class CTestSync : public CBase
{
public:
	static CTestSync* NewL();
	int TestFunc();
	int DeleteDefaultCalendar();
	int DeleteWrongCal();
	CTestSync();
	~CTestSync();

private:
	void ConstructL();

	
	
private:	
	CLiwServiceHandler* 	iServiceHandler;
	TInt 					iResult;
	MLiwInterface* 			interface ;	
};