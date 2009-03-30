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

#include "s60_notify.h"

#ifdef __WINSCW__
const TMsvId KObservedFolderId = KMsvDraftEntryId;
#else
const TMsvId KObservedFolderId =  KMsvGlobalInBoxIndexEntryId;
#endif

TMsvId iNewMessageId;
TTime tim;

class CSession;
class Cheader_test;


CSession* CSession::NewL( CMsvSession* aSession )
	{
	 return new(ELeave) CSession( aSession );
	}
	

CSession::~CSession()
	{
	 
	}


CSession::CSession( CMsvSession* aSession ) :
					iServerSession( aSession )
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


void Cheader_test::RunL()
	{
	TestFunc();
	}


void Cheader_test::Start()
	{
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}
	
void Cheader_test::NotifyResultL(TInt aErrCode, TAny* aResult)
	{ 
     TInt res = aErrCode;
     
     TTime notify;
	 notify.HomeTime();
	 
	 TTimeIntervalMicroSeconds tk = notify.MicroSecondsFrom(tim);
	 
	 TDateTime date = notify.DateTime();
	 TInt day = date.Day();
	 TMonth month = date.Month();
	 TInt hour = date.Hour();
	 TInt min = date.Minute();
	 TInt sec = date.Second();
	 TInt micsec = date.MicroSecond();
	
	 fprintf(fdsymno,"%s : %lld\n", "delay", tk);
	 fprintf(fdsymno,"message notify time:\n");
	 fprintf(fdsymno,"%s : %d\n", "day", day+1);
	 fprintf(fdsymno,"%s : %d\n", "month", month+1);
	 fprintf(fdsymno,"%s : %d\n", "hour", hour);
	 fprintf(fdsymno,"%s : %d\n", "min", min);
	 fprintf(fdsymno,"%s : %d\n", "sec", sec);
	 fprintf(fdsymno,"%s : %d\n", "microsec", micsec);
	 fprintf(fdsymno,"\n");
	 
	 TDateTime date1 = tim.DateTime();
	 TInt day1 = date1.Day();
	 TMonth month1 = date1.Month();
	 TInt hour1 = date1.Hour();
	 TInt min1 = date1.Minute();
	 TInt sec1 = date1.Second();
	 TInt micsec1 = date1.MicroSecond();
	
	 fprintf(fdsymno,"message creation time:\n");
	 fprintf(fdsymno,"%s : %d\n", "day", day1 + 1);
	 fprintf(fdsymno,"%s : %d\n", "month", month1 + 1);
	 fprintf(fdsymno,"%s : %d\n", "hour", hour1);
	 fprintf(fdsymno,"%s : %d\n", "min", min1);
	 fprintf(fdsymno,"%s : %d\n", "sec", sec1);
	 fprintf(fdsymno,"%s : %d\n", "microsec", micsec1);
	 
          
     iWaitSchedular->AsyncStop();
    }
    
void CSession::HandleSessionEventL(TMsvSessionEvent aEvent, 
											TAny* aArg1, 
											TAny* aArg2, 
											TAny* aArg3 )
	{
		
		if ( iNotifyCallback )
			{
			switch ( aEvent )
				{
				case EMsvEntriesCreated:
					{
					if ( aArg2 && *(static_cast<TMsvId*> (aArg2)) == KObservedFolderId )
						{
						CMsvEntrySelection* entries = static_cast<CMsvEntrySelection*>( aArg1 );
						if ( entries->Count() > 0 )
							{
							iNewMessageId = entries->At(0);
							}
						}
					}
					break; 
				
				case EMsvEntriesChanged:
					{
					if ( aArg2 && *(static_cast<TMsvId*>(aArg2)) == KObservedFolderId )
						{
						CMsvEntrySelection* entries = static_cast<CMsvEntrySelection*>( aArg1 );
						if( entries->Count() > 0 && iNewMessageId == entries->At(0) )
							{
							User::After(1000000);
							TMsvEntry newEntry;
							TMsvId serviceId;
							iServerSession->GetEntry( iNewMessageId, serviceId, newEntry );
							tim = newEntry.iDate;
							
							iNotifyCallback->NotifyResultL(KErrNone , NULL);
							}
						}
					}
					break;
				
				default: break;
			}
		}
	}

void Cheader_test::TestFunc()
	{
    
		TInt i;
		
		fdsymno = fopen(logfnot, "a");
	       	    
	    CSession* obs = CSession::NewL();
	    CMsvSession* iSession = CMsvSession::OpenSyncL(*obs);
	    obs->iServerSession = iSession ;
		obs->iNotifyCallback = (CMsgCallback*)this;
       	
 	}

	
void SymbStartPerformanceTestL()
{	

	CActiveScheduler* activeScheduler = new (ELeave) CActiveScheduler;


	CActiveScheduler::Install(activeScheduler);

	Cheader_test* p = Cheader_test::NewL();
	
	CActiveScheduler::Add(p);
	
	p->Start();	

	delete p;
	
	fprintf(fdsymno,"\n");
	fclose(fdsymno);
	
}					



TInt E32Main()
	{
	__UHEAP_MARK;
	CTrapCleanup* cleanup = CTrapCleanup::New();
	
  	TRAPD(error1, SymbStartPerformanceTestL());
 	__ASSERT_ALWAYS(!error1, User::Panic(_L("SYMcode PANIC"), error1));	
 	
	delete cleanup;
	__UHEAP_MARKEND;
	return 0;
	} 

	
	