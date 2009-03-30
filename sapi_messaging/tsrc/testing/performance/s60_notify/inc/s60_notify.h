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





static FILE* fdsymno = NULL;
static char logfnot[25] = "c:\\symnotify.txt";


class CMsgCallback : public CBase
	{

	public:

		virtual void NotifyResultL(TInt aErrCode, TAny* aResult) = 0;

	};	


class CSession : public CBase, public MMsvSessionObserver 
{

	public:
	
		static CSession* NewL( CMsvSession* aSession = NULL);

		virtual ~CSession();
		
		void SetSession( CMsvSession* aSession );
		
		CMsgCallback* iNotifyCallback;
		
		virtual void HandleSessionEventL( TMsvSessionEvent aEvent, 
											TAny* aArg1, 
											TAny* aArg2, 
											TAny* aArg3 );
												
		
	
		CMsvSession* iServerSession;
	
	
	private:
	
	    CSession( CMsvSession* aSession );
	
	    
	    
	   	
	    	
	    	
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