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

class CLocCoreImp ; //Forward declaration
#include "TMsgTest.h"
#include<MSVAPI.H>
#include <msvids.h> 

void SendMsgFuncL()
{
		TBuf16<256> Kmsgtype(_L("KUidMsgTypeSMS"));
  
    CActiveScheduler *Scheduler = new CActiveScheduler ;
    
    CActiveScheduler :: Install(Scheduler) ;
   MMsvSessionObserver* SessionObserver = CMessageObserver::NewL();
 CMsvSession* session = CMsvSession::OpenSyncL(*SessionObserver);
     CSendMessage* obj = CSendMessage::NewL(*session);
     obj->SetMessageParameters(Kmsgtype,NULL,NULL,NULL,NULL,NULL,NULL);
	 obj->SendMessage();
    CActiveScheduler :: Start() ;
}

TInt SendMsg(TAny *Arg)
{
	CTrapCleanup* cleanup = CTrapCleanup::New();
  //Install a new active scheduler to this thread 
  TRAPD(err , SendMsgFuncL()) ;
    delete cleanup ;
	return 0 ;
}


void ChngStL()
{
  
    CActiveScheduler *Scheduler = new CActiveScheduler ;
    
    CActiveScheduler :: Install(Scheduler) ;
  	MMsvSessionObserver* SessionObserver = CMessageObserver::NewL();
 	CMsvSession* session = CMsvSession::OpenAsyncL(*SessionObserver);
    
   // User::WaitForRequest(session->iStatus);
     
     CActiveScheduler :: Start() ;
    CMsvEntry* entry = session->GetEntryL(KMsvGlobalInBoxIndexEntryId); 
    CMsvEntrySelection* entries = entry->ChildrenL();
    
	    TMsvId entryID = entries->At(0);
	    CMessageChangeStatus* obj = CMessageChangeStatus::NewL(*session);
	    
	    obj->ChangeStatus(entryID,CMessageChangeStatus::ERead,FALSE,NULL);
	    
	    
    
}

TInt ChngStatus(TAny *Arg)
{
	CTrapCleanup* cleanup = CTrapCleanup::New();
  //Install a new active scheduler to this thread 
  TRAPD(err , ChngStL()) ;
    delete cleanup ;
	return 0 ;
}