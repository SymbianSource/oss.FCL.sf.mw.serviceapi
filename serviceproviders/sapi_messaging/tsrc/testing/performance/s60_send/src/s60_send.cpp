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

#include <e32base.h>
#include <e32cons.h>
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

#include "s60_send.h"


void SymbStartPerformanceTestL()
{

	TTime start; 
    TTime end;	
    TTimeIntervalMicroSeconds timeTaken ; 
	TInt64 aTimeDelay, aSum = 0.0, aAvgTime = 0.0 ;
	TInt i;	
	
	fdsym = fopen(logf, "a");
	
   for(i = 0;i < 10; i++)
   {
	TInt Err;
	RSendAs  iSend;
	
	start.HomeTime();
	Err = iSend.Connect();
	
	RSendAsMessage   iMessage;
	iMessage.CreateL(iSend, KSenduiMtmSmsUid);
	
	TPtrC aAddr;
	_LIT(Kaddr,"9008032761");
	aAddr.Set(Kaddr);
	iMessage.AddRecipientL(aAddr,RSendAsMessage::TSendAsRecipientType(0));
	
	TPtrC aBody;
	_LIT(Kbody,"pinging");
	aBody.Set(Kbody);
	iMessage.SetBodyTextL(aBody);
	
	iMessage.SendMessageAndCloseL();
	
	iMessage.Close();
	iSend.Close();
	
	end.HomeTime();
	timeTaken = end.MicroSecondsFrom(start);
	fprintf(fdsym ,"delay() - %lld\n",timeTaken);
	aTimeDelay = timeTaken.Int64() ;
	aSum = aSum + aTimeDelay ;
   }
	
	aAvgTime = aSum/10 ;
	fprintf(fdsym ,"avg time taken() - %ld\n",aAvgTime);
	
	
/* _LIT(KMsgTestUITitle, "window");
 CConsoleBase* console = Console::NewL(KMsgTestUITitle, TSize(KConsFullScreen,KConsFullScreen));
 TBuf <10> testin;
 _LIT(KFormat, "%ld");  
 testin.Format (KFormat, aAvgTime);
 console->Printf(testin);*/
		
	fprintf(fdsym,"\n");
	fclose(fdsym);
	
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
	
	

