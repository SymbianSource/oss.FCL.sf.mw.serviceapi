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
#include <badesca.h>
#include<liwcommon.h>
#include <f32file.h>

class CLiwServiceHandler;

/**
 * Callback class for asynchronous SAPI message header
*/	
class CCalCallbackGuid : public MLiwNotifyCallback
	{
	public:
		
		static CCalCallbackGuid* NewL(CActiveSchedulerWait* aWaitSchedular, MLiwInterface* aInterface, TInt& aResult, TInt& aFlag);
		
		virtual ~CCalCallbackGuid(){}
		
		TInt HandleNotifyL(TInt aCmdId,
        TInt aEventId,
        CLiwGenericParamList& aEventParamList,
        const CLiwGenericParamList& aInParamList);
		
	private:
	
 		CCalCallbackGuid(CActiveSchedulerWait* aWaitSchedular, MLiwInterface* aInterface, TInt& aResult, TInt& aFlag):iWaitSchedular(aWaitSchedular), iInterface(aInterface), iResult(aResult), iOption(aFlag){ }

		CActiveSchedulerWait* 	iWaitSchedular;
		MLiwInterface* 			iInterface ;
		TInt& iResult;	
		TInt& iOption;	
	};


class CTestAsyncGuid : public CActive
{
public:
	static CTestAsyncGuid* NewL();
	~CTestAsyncGuid();
	int Start(int, TBool);
	void CancelNotification();
	
	
private:
	void ConstructL();
	CTestAsyncGuid();
	
	virtual void DoCancel();
	virtual void RunL();
	
	
	void TestFunc();

	
	
private:	
	CLiwServiceHandler* 	iServiceHandler;
	CActiveSchedulerWait* 	iWaitSchedular;
	TInt 					iResult;
	MLiwInterface* 			interface ;	
	CCalCallbackGuid*			iCallback;
	TInt iError;
	TInt iFlag;
	TBool iAsync;
};

