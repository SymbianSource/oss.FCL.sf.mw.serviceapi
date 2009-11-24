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
//#include <SendUiConsts.h>
#include <badesca.h>
#include<liwcommon.h>
#include <f32file.h>

class CLiwServiceHandler;

/**
 * Callback class for asynchronous SAPI message header
*/	
class CCalCallback : public MLiwNotifyCallback
	{
	public:
		
		static CCalCallback* NewL(CActiveSchedulerWait* aWaitSchedular, TInt32& aResult );
		
		virtual ~CCalCallback(){}
		
		TInt HandleNotifyL(TInt aCmdId,
	            TInt aEventId,
	            CLiwGenericParamList& aEventParamList,
	            const CLiwGenericParamList& aInParamList);
		TInt			iChangeType;
		TUint			iLocalUid;
		TBool			iCheckLocalUid;
		
	private:
	
 		CCalCallback(CActiveSchedulerWait* aWaitSchedular, TInt32& aResult ):iWaitSchedular(aWaitSchedular), iResult(aResult){ }

		CActiveSchedulerWait* 	iWaitSchedular;
		TInt32& 			iResult;
		
			
	};


class CTestAsync : public CActive
{
	enum TTestState
		{
		ETestIssueRequest,
		ETestProcessRequest,
		ETestCompleted
		};
public:
	static CTestAsync* NewL();
	~CTestAsync();
	void Start(TInt aChangeType, TBool aLocalUid);
	void CancelNotification();
	
	TInt32 Result();
	
private:
	void ConstructL();
	CTestAsync();
	
	virtual void DoCancel();
	virtual void RunL();
	
	
	void TestFunc();

	void DoAddChange();
	void DoDeleteChange();
	void DoUpdateChange();
	void DoExpUpdate();
	
	
	
private:	
	CLiwServiceHandler* 	iServiceHandler;
	CActiveSchedulerWait* 	iWaitSchedular;
	TInt32 					iResult;
	TUint 					iLocalUid;	
	TInt 					iChangeType;	
	CCalCallback*			iCallback;
	MLiwInterface* 			interface;
	TInt32 					iTransactionId;
	TBool					iCheckLocalUid;
	
	TTestState				iTestState;		
};
