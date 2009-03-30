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




static FILE* fdsapis = NULL;	
static char logfst[25] = "c:\\symstatus.txt";	

class CSession : public CBase, public MMsvSessionObserver 
{

	public:
	
		static CSession* NewL( CMsvSession* aSession = NULL);

		virtual ~CSession();
		
		void SetSession( CMsvSession* aSession );
		
		void HandleSessionEventL( TMsvSessionEvent aEvent, 
											TAny* aArg1, 
											TAny* aArg2, 
											TAny* aArg3 )
											{}	
		
	private:
	
	    CSession( CMsvSession* aSession );
	
	    CMsvSession* iServerSession;	
	    	
	    	
};
	


class Cheader_test : public CActive
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
		//CMessagingService*		iMessagingService;
			
};
