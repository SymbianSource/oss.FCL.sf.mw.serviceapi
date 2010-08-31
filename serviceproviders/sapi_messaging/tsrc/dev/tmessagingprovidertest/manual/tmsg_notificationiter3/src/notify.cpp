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


#include "messaginginterface.h"
#include<liwcommon.h>
#include<liwvariant.h>
#include<liwservicehandler.h>

#include"notify.h"

_LIT8(KTestInterface, 	"IMessaging");
_LIT8(KTestContent,		"Service.Messaging");
_LIT8(KCmd,				"RegisterNotification");
_LIT8(KCmdCancel,				"CancelNotification");
_LIT8(KMessageId,				"MessageId");
_LIT8(KMap,				"Type");
_LIT8(KMessageList,			"MessageList" );
_LIT8(KMessage,				"Message" );

_LIT(KMsgType,"NewMessage");



CMsgCallback* CMsgCallback::NewL(CActiveSchedulerWait* aWaitSchedular, MLiwInterface* aInterface)
	{
	return new (ELeave) CMsgCallback(aWaitSchedular, aInterface);
	}
		
TInt CMsgCallback::HandleNotifyL(TInt aCmdId,
									        TInt aEventId,
									        CLiwGenericParamList& aEventParamList,
									        const CLiwGenericParamList& aInParamList)
	{
	TInt pos = 0;
	TInt result = KErrNone;
    const TLiwGenericParam* output = aEventParamList.FindFirst( pos,_L8("ReturnValue"));
	
	const CLiwMap* header = output->Value().AsMap();
	TInt32 newmessageid = -1;
    if ( header )
    	{
    	TLiwVariant mesageid;
    	if( header->FindL(KMessageId, mesageid))
    		{
    		newmessageid  = mesageid.AsTInt32();
    		}
    	mesageid.Reset();	
    	}
  
 	if ( newmessageid ) 
 		{
 		
	    CLiwGenericParamList* inParamList = CLiwGenericParamList::NewL();
	    CLiwGenericParamList* outParamList = CLiwGenericParamList::NewL();
 		
	    TLiwVariant content(_L8("Inbox"));
		TLiwGenericParam elem ;	
		elem.SetNameAndValueL(_L8("Type"),content);
		inParamList->AppendL(elem);
		content.Reset();
		elem.Reset();
		
	   	CLiwDefaultMap* filtermap = CLiwDefaultMap::NewL();
		CleanupStack::PushL(filtermap);

	    TLiwVariant filterid( newmessageid );
	    filtermap->InsertL(KMessageId, filterid); // Mtmtype is added
	    filterid.Reset();	
    

	    TLiwVariant filterparam(filtermap);
		TLiwGenericParam element ;	
		element.SetNameAndValueL(_L8("Filter"),filterparam);
		filterparam.Reset();
		
		inParamList->AppendL(element);
		element.Reset();
		
	    filtermap->DecRef();
	    CleanupStack::Pop(filtermap);
	    

		TInt err = 0;
		TRAP(err,iInterface->ExecuteCmdL( _L8("GetList") ,*inParamList ,*outParamList));
	    
	    pos = 0 ;
	    
	    const TLiwGenericParam* finaloutput = outParamList->FindFirst( pos,_L8("ReturnValue"));
	
		if ( finaloutput )     
			{
			CLiwIterable* iterlist = finaloutput->Value().AsIterable();

	      	if(iterlist)
	      		{
			    TLiwVariant data;

	      		if ( iterlist->NextL(data) )
	      			result = KErrNone;	
	      		
	      		data.Reset();  

	      		}
			}
			
		inParamList->Reset();
		outParamList->Reset();
		
		delete inParamList;
		delete outParamList;
		
		}

	if ( iWaitSchedular && iWaitSchedular->IsStarted())
		{
		iWaitSchedular->AsyncStop();
		}
	}



CTestAsync* CTestAsync::NewL()
	{
	CTestAsync* self = new (ELeave) CTestAsync();
	self->ConstructL();
	return self;
	}

CTestAsync::~CTestAsync()
	{
	Cancel();
	
	interface->Close();
	
	delete iServiceHandler;
	
	delete iCallback;

	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();

	delete iWaitSchedular;
	}


void CTestAsync::ConstructL()
	{
	CActiveScheduler::Add(this);
	iWaitSchedular = new(ELeave) CActiveSchedulerWait();
	}


CTestAsync::CTestAsync() :
CActive(EPriorityStandard)
		{
		interface = NULL ;
		}

void CTestAsync::DoCancel()
	{

	}

void CTestAsync::RunL()
	{
	TestFunc();
	}


void CTestAsync::Start()
	{
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}


void CTestAsync::TestFunc()
	{
	iServiceHandler = CLiwServiceHandler::NewL();

	CLiwGenericParamList* inparam = &(iServiceHandler->InParamListL());
	CLiwGenericParamList* outparam = &(iServiceHandler->OutParamListL());


	TInt	err; 

	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KTestInterface,KTestContent);
	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray a;
	a.AppendL(crit);    
	
	iServiceHandler->AttachL(a);
	iServiceHandler->ExecuteServiceCmdL(*crit, *inparam, *outparam); 

	a.Reset();
	delete crit;
	
	TInt pos = 0;

	outparam->FindFirst( pos, KTestInterface );
	if(pos != KErrNotFound)
		{
		interface = (*outparam)[pos].Value().AsInterface();	
		}

	outparam->Reset();
	inparam->Reset();

	TLiwGenericParam element ;	
	element.SetNameAndValueL(KMap, TLiwVariant(KMsgType));
	inparam->AppendL(element);
	element.Reset();
	
	iCallback = CMsgCallback::NewL(iWaitSchedular, interface);

	TRAPD(err1 ,interface->ExecuteCmdL(KCmd, *inparam, *outparam, KLiwOptASyncronous, iCallback));
	inparam->Reset();
	outparam->Reset();
	}


int ReqNotification(int, char**)
	{
	__UHEAP_MARK;
	CTestAsync* test = CTestAsync::NewL();
	test->Start();
	delete test;
	__UHEAP_MARKEND;
	return 0;
	
	}