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



// INCLUDE FILES

#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <e32std.h>
#include <e32des16.h>
#include <f32file.h>
#include <pthread.h>
#include <semaphore.h>

#include <rsendas.h>
#include <rsendasmessage.h>
#include <msvstd.h>
#include <msvapi.h>
#include <msvids.h>
////#include <senduiconsts.h>
#include <mmsconst.h>
#include <csendasaccounts.h>
#include <cmsvrecipientlist.h>

#include "s60_asyncsend.h"


CSendMessage* CSendMessage::NewL()
	{
	CSendMessage* self = new (ELeave) CSendMessage();
	return self;
	}

CSendMessage::~CSendMessage()
	{
	if ( IsActive() )
		{
		Cancel();
		}	

	}

CSendMessage::CSendMessage():
				CActive( EPriorityStandard )
	{
	}


Cheader_test* Cheader_test::NewL()
	{
	Cheader_test* self = new(ELeave)Cheader_test();
	self->ConstructL();
	return self;
	}


Cheader_test::~Cheader_test()
	{
	Cancel();
	
	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();
	
	
	if(iWaitSchedular)
		delete iWaitSchedular;
	}


void Cheader_test::ConstructL()
	{
		iWaitSchedular = new(ELeave) CActiveSchedulerWait();	
	}


Cheader_test::Cheader_test() :
CActive(EPriorityStandard)
	{
	}


void Cheader_test::DoCancel()
	{
		
	}

void CSendMessage::DoCancel()
	{
	
	}

void Cheader_test::Start()
	{
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}
	
void CSendMessage::ActivateRequest(TInt aReason)
    {
 	iStatus = KRequestPending;
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete( temp, aReason );		
    }

void Cheader_test::RunL()
	{
	TestFunc();
	}

void Cheader_test::TestFunc()
	{	    
	    CSendMessage* sent = CSendMessage::NewL();
	    sent->iNotifyCallback = (CMsgCallback*)this;
	    CActiveScheduler::Add( sent );
		sent->iMessageState = CSendMessage::TMessageState(0);
		sent->ActivateRequest( KErrNone );
	}   

void Cheader_test::NotifyResultL(TInt aErrCode, TAny* aResult)
	{ 
     TInt res = aErrCode;
     iWaitSchedular->AsyncStop();
    }

void CSendMessage::NotifyRequestRes(TInt aReason)
    {
     iNotifyCallback->NotifyResultL( aReason, NULL );
     delete this;
    }


void CSendMessage::RunL()
    {	      
	    
	    TInt err = iStatus.Int();
	    
	    if ( err == KErrNone )
		{	
			switch ( iMessageState )
			{
			case EInitialize: 
			   {						
				err = iSend.Connect();
				iMessage.CreateL(iSend, KSenduiMtmSmsUid);
				
				iMessageState = EValidate;
				ActivateRequest( err );
			   }
				break;	

			case EValidate: 
			   {
				TPtrC aAddr;
				_LIT(Kaddr,"9008032761");
				aAddr.Set(Kaddr);
				iMessage.AddRecipientL(aAddr,RSendAsMessage::TSendAsRecipientType(0));
				
				TPtrC aBody;
				_LIT(Kbody,"pinging");
				aBody.Set(Kbody);
				iMessage.SetBodyTextL(aBody);
				
				iMessageState = ESend;
				ActivateRequest( err );
			   }
				break;	

			case ESend: 
			   {
				iMessage.SendMessageAndCloseL();
				iMessageState = EComplete;
				ActivateRequest( err );
			   }		
				break;

			case EComplete: 
			   {
				iMessage.Close();
				iSend.Close();
				NotifyRequestRes(err);
			   }
				break;
					
			default:
				break;	
			}
		}	

       	
 	}



void SymbStartPerformanceTestL()
{
	
    CActiveScheduler* activeScheduler = new (ELeave) CActiveScheduler;
	CleanupStack::PushL(activeScheduler);

	CActiveScheduler::Install(activeScheduler);

	TTime start; 
	TTime end;	
	TTimeIntervalMicroSeconds timeTaken ; 
	TInt i;
		
    fdsymas = fopen(logfase, "a");
    
//    for(i=0;i<10;i++)
//    {
	start.HomeTime();
	
	Cheader_test* p = Cheader_test::NewL();
	
	CActiveScheduler::Add(p);
	
	p->Start();
	
	delete p;
	
	end.HomeTime();
	timeTaken = end.MicroSecondsFrom(start);
	fprintf(fdsymas ,"delay() - %lld\n",timeTaken);
	
//	}
		
	fprintf(fdsymas,"\n");
	fclose(fdsymas);	

}						


TInt E32Main()
	{
	__UHEAP_MARK;
	CTrapCleanup* cleanup = CTrapCleanup::New();
	
  	TRAPD(error, SymbStartPerformanceTestL());
    __ASSERT_ALWAYS(!error, User::Panic(_L("LIBC PANIC"), error));	

	delete cleanup;
	__UHEAP_MARKEND;
	return 0;
	} 

	
	