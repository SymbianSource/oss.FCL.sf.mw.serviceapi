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
////#include <senduiconsts.h>
#include <BADESCA.H>
#include<LiwCommon.h>
#include <f32file.h>

class CLiwServiceHandler;

/**
 * Callback class for asynchronous SAPI message header
*/	
class CMsgCallback : public MLiwNotifyCallback
	{
	public:
		
		static CMsgCallback* NewL(CActiveSchedulerWait* aWaitSchedular, MLiwInterface* aInterface);
		
		virtual ~CMsgCallback(){}
		
		TInt HandleNotifyL(TInt aCmdId,
	            TInt aEventId,
	            CLiwGenericParamList& aEventParamList,
	            const CLiwGenericParamList& aInParamList);
		
	private:
	
 		CMsgCallback(CActiveSchedulerWait* aWaitSchedular, MLiwInterface* aInterface):iWaitSchedular(aWaitSchedular), iInterface(aInterface){ }

		CActiveSchedulerWait* 	iWaitSchedular;
		MLiwInterface* 			iInterface ;	
	};


class CTestAsync : public CActive
{
public:
	static CTestAsync* NewL();
	~CTestAsync();
	void Start();
	void CancelNotification();
	
	
private:
	void ConstructL();
	CTestAsync();
	
	virtual void DoCancel();
	virtual void RunL();
	
	
	void TestFunc();

	
	
private:	
	CLiwServiceHandler* 	iServiceHandler;
	CActiveSchedulerWait* 	iWaitSchedular;
	TInt 					iResult;
	MLiwInterface* 			interface ;	
	CMsgCallback*			iCallback;
};