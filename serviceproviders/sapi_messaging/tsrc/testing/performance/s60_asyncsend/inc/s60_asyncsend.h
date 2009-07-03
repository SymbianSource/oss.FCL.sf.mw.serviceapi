/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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



static FILE* fdsymas = NULL;	
static char logfase[25] = "c:\\symasend.txt";	

class CMsgCallback : public CBase
	{

	public:

		virtual void NotifyResultL(TInt aErrCode, TAny* aResult) = 0;

	};	


class Cheader_test : public CActive , public CMsgCallback
{
	public:
		
		static Cheader_test* NewL();
		~Cheader_test();
		void Start();

	private:
	
		void ConstructL();
		Cheader_test();		
		virtual void DoCancel();
		virtual void RunL();				
		void TestFunc();
		void NotifyResultL(TInt aErrCode, TAny* aResult);	
	
	private:
	
		CActiveSchedulerWait* 	iWaitSchedular;			
};

class CSendMessage : public CActive
	{
	
	public:
	
		enum TMessageState
		{
		EInitialize = 0,
		EValidate,
		ESend,
		EComplete
		};
 
     	static CSendMessage* NewL();
		virtual ~CSendMessage();
		CSendMessage();

	public:	
	
		RSendAs					iSend;
		RSendAsMessage			iMessage;
		TMessageState			iMessageState;
		CMsgCallback* 		    iNotifyCallback;		
		void ActivateRequest(TInt aReason);
		void NotifyRequestRes(TInt aReason);
		void InitializeL();
		void ValidateL();
		void SendL();
		virtual void DoCancel();
		
    private: 
    	
    	
        virtual void RunL();	
        CActiveSchedulerWait* 	iSchedular;	
	};
	
	
