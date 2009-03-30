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

#include <rsendas.h>
#include <rsendasmessage.h>
#include <msvstd.h>
#include <msvapi.h>
#include <msvids.h>
////#include <senduiconsts.h>
#include <mmsconst.h>
#include <csendasaccounts.h>
#include <cmsvrecipientlist.h>

#include "s60_status.h"


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


void Cheader_test::TestFunc()
{
	
	TTime start; 
	TTime end;	
	TTimeIntervalMicroSeconds timeTaken ; 
	TInt64 aTimeDelay, aSum = 0.0, aAvgTime = 0.0 ;
	TInt i;
	TInt id = 1048801;
	
	fdsapis = fopen(logfst, "a");
	
   for(i = 0;i < 10; i++)
   {    
	id = id + 1;
	start.HomeTime(); 

    CSession* obs = CSession::NewL();
	CMsvSession* iSession = CMsvSession::OpenSyncL(*obs);
    
    CMsvEntry* iEntry = iSession->GetEntryL(id);    
    TMsvEntry index = iEntry->Entry();
    
    TBool iFlagValue;
//    if(i%2 == 0)
//    {
     iFlagValue = ETrue;
//    }
/*    else
    {
     iFlagValue = EFalse;
    }*/
    index.SetUnread( iFlagValue );   
	iEntry->ChangeL( index );
		      
	delete iEntry;
	delete iSession;
	delete obs;
	
	end.HomeTime();
	timeTaken = end.MicroSecondsFrom(start);
	fprintf(fdsapis ,"delay() - %lld\n",timeTaken);
	aTimeDelay = timeTaken.Int64() ;
	aSum = aSum + aTimeDelay ;
   }
    
    aAvgTime = aSum/10 ;
	fprintf(fdsapis ,"avg time taken() - %ld\n",aAvgTime);
	fprintf(fdsapis,"\n");
	fclose(fdsapis);
	
	iWaitSchedular->AsyncStop();
	
}

void SymbStartPerformanceTestL()
{

	CActiveScheduler* activeScheduler = new (ELeave) CActiveScheduler;
	CleanupStack::PushL(activeScheduler);

	CActiveScheduler::Install(activeScheduler);

	Cheader_test* p = Cheader_test::NewL();
	
	CActiveScheduler::Add(p);
	
	p->Start();	
	
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
	
	
	