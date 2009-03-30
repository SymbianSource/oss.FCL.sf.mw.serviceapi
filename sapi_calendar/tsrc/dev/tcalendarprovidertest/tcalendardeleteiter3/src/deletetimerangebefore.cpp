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


#include<LiwCommon.h>
#include<LiwVariant.h>
#include<LiwServiceHandler.h>
#include "tcalendardeletetest.h"
#include "deletetimerangebefore.h"

_LIT8(KTestInterface, 	"IDataSource");
_LIT8(KTestContent,		"Service.Calendar");
_LIT8(KCmd,				"Delete");
_LIT8(KCmdCancel,				"CancelNotification");
_LIT8(KMessageId,				"MessageId");
_LIT8(KMap,				"NotificationType");
_LIT8(KMessageList,			"MessageList" );
_LIT8(KMessage,				"Message" );
_LIT8(KErrorCode,"ErrorCode");
_LIT(KMsgType,"NewMessage");
_LIT8(KContentType,"Type");
_LIT8(KFilter,"Filter");
_LIT8(KData,"Data");

_LIT8(KDeleteAll,"DeleteAll");
_LIT(KCalFileName1,"C:CalendarFileA");
_LIT8(KCalendarName,"CalendarName");

TInt AddProvCalendar(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar);
TInt RemoveProvCalendar(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar);
TInt AddProvToDo(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUint& localuid,HBufC8*& globaluid);
TInt AddProvDayEvent(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUint& localuid);
TInt AddProvAnni(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUint& localuid);


CCalCallbackTimeBefore* CCalCallbackTimeBefore::NewL(CActiveSchedulerWait* aWaitSchedular, MLiwInterface* aInterface, TInt& aError)
	{
	return new (ELeave) CCalCallbackTimeBefore(aWaitSchedular, aInterface, aError);
	}
		
TInt CCalCallbackTimeBefore::HandleNotifyL(TInt aCmdId,
						        TInt aEventId,
						        CLiwGenericParamList& aEventParamList,
						        const CLiwGenericParamList& aInParamList)
	{
	TInt32 errCode;
	TInt pos = 0;

	// Traiverse the List and Fill in the Log Files
	const TLiwGenericParam* p = aEventParamList.FindFirst(pos, KErrorCode); // Finding Error Code
	if( p )
		{
		errCode = p->Value().AsTInt32();
		}
  
 	if ( errCode == KErrNone ) 
 		{
 		
	    CLiwGenericParamList* inParamList = CLiwGenericParamList::NewL();
	    CLiwGenericParamList* outParamList = CLiwGenericParamList::NewL();
 		
		TLiwVariant dsName;
		dsName.Set(_L("CalendarEntry"));
	    TLiwGenericParam dsNameParam(KContentType, dsName);
		inParamList->AppendL(dsNameParam);
		dsName.Reset();
		
		CLiwDefaultMap *filterMap = CLiwDefaultMap::NewL();
		TLiwGenericParam filterParam(KFilter, TLiwVariant(filterMap));
		inParamList->AppendL(filterParam);
		filterMap->DecRef();

		TLiwVariant calname;
	    calname.Set(KCalFileName1);;
	    filterMap->InsertL(KCalendarName,calname);
	    calname.Reset();
	    

		TInt err = 0;
		TRAP(err,iInterface->ExecuteCmdL( _L8("GetList") ,*inParamList ,*outParamList));
	    
	    pos = 0 ;
	    
	    const TLiwGenericParam* finaloutput = outParamList->FindFirst( pos,_L8("ReturnValue"));
	    TInt count = 0;
	    CLiwMap* map;

		if ( finaloutput )     
			{
			CLiwIterable* iterlist = finaloutput->Value().AsIterable();
	      	if(iterlist)
	      		{
			    TLiwVariant data;
	      		while(iterlist->NextL(data) )
		      		{
		      		map = (CLiwMap*)data.AsMap();
		      		map->DecRef();	
   	            	count++;	
		      		}
	      		data.Reset();  
	      		}
			}
		if(count != 1)
			errCode = KErrGeneral;	
		inParamList->Reset();
		outParamList->Reset();
	    RemoveProvCalendar(inParamList, outParamList, iInterface, KCalFileName1);
		delete inParamList;
		delete outParamList;
 		}
	if ( iWaitSchedular && iWaitSchedular->IsStarted())
		{
		iWaitSchedular->AsyncStop();
		}
    iResult = errCode;
	return errCode;
	}



CTestAsyncDeleteBefore* CTestAsyncDeleteBefore::NewL()
	{
	CTestAsyncDeleteBefore* self = new (ELeave) CTestAsyncDeleteBefore();
	self->ConstructL();
	return self;
	}

CTestAsyncDeleteBefore::~CTestAsyncDeleteBefore()
	{
	Cancel();
	
	if( interface )
	interface->Close();
	
	delete iServiceHandler;
	
	delete iCallback;

	if(iWaitSchedular && iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();

	delete iWaitSchedular;
	}


void CTestAsyncDeleteBefore::ConstructL()
	{
	CActiveScheduler::Add(this);
	iWaitSchedular = new(ELeave) CActiveSchedulerWait();
	}


CTestAsyncDeleteBefore::CTestAsyncDeleteBefore() :
CActive(EPriorityStandard)
	{
	interface = NULL ;
	}

void CTestAsyncDeleteBefore::DoCancel()
	{

	}

void CTestAsyncDeleteBefore::RunL()
	{

	TestFunc();

	}


int CTestAsyncDeleteBefore::Start()
	{
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();
	return iError;	
	}


void CTestAsyncDeleteBefore::TestFunc()
	{
	iServiceHandler = CLiwServiceHandler::NewL();

	CLiwGenericParamList* inparam = &(iServiceHandler->InParamListL());
	CLiwGenericParamList* outparam = &(iServiceHandler->OutParamListL());


	TInt err; 

	RCriteriaArray interest;
    CleanupClosePushL(interest);
    
	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KTestInterface,KTestContent);
	crit->SetServiceClass(TUid::Uid(KLiwClassBase));
    CleanupStack::PushL(crit);
    interest.AppendL(crit);    
 	iServiceHandler->AttachL(interest);
	iServiceHandler->ExecuteServiceCmdL(*crit, *inparam, *outparam); 
	
	TInt pos = 0;

	outparam->FindFirst( pos, KTestInterface );
	if(pos != KErrNotFound)
		{
		interface = (*outparam)[pos].Value().AsInterface();	
		}

    CleanupStack::PopAndDestroy(crit);
    CleanupStack::PopAndDestroy(&interest); 

	outparam->Reset();
	inparam->Reset();
	
	AddProvCalendar(inparam, outparam, interface, KCalFileName1);
	HBufC8* globaluid;
	TUint localuid;
    AddProvToDo(inparam, outparam, interface, KCalFileName1 ,localuid, globaluid)	;
    
    AddProvToDo(inparam, outparam, interface, KCalFileName1 ,localuid, globaluid)	;

    AddProvDayEvent(inparam, outparam, interface, KCalFileName1 ,localuid)	;
    
	TLiwVariant dsName;
	dsName.Set(_L("CalendarEntry"));
    TLiwGenericParam dsNameParam(KContentType, dsName);
	inparam->AppendL(dsNameParam);
	dsName.Reset();

	CLiwDefaultMap *filterMap = CLiwDefaultMap::NewL();
	TLiwGenericParam filterParam(KData, TLiwVariant(filterMap));
	inparam->AppendL(filterParam);

    CLiwDefaultList *uidlist = CLiwDefaultList::NewL();
    uidlist->AppendL(TLiwVariant(globaluid->Des()));
	TLiwVariant calname;
	TPtrC filename(_L("C:CalendarFileA"));
    calname.Set(filename);

    filterMap->InsertL(KCalendarName,calname);
	//filterMap->InsertL(_L8("GlobalUidList"), TLiwVariant(uidlist));
	uidlist->DecRef();
	filterMap->DecRef();

	iCallback = CCalCallbackTimeBefore::NewL(iWaitSchedular, interface, iError);

	TRAPD(err1 ,interface->ExecuteCmdL(KCmd, *inparam, *outparam, KLiwOptASyncronous, iCallback));
	TInt errCode;
	
	const TLiwGenericParam* p = outparam->FindFirst(pos, KErrorCode); // Finding Error Code
	if( p )
		{
		errCode = p->Value().AsTInt32();
		}
    if( errCode != KErrNone )
	    {
		inparam->Reset();
		outparam->Reset();
	    RemoveProvCalendar(inparam, outparam, interface, KCalFileName1);

		if ( iWaitSchedular && iWaitSchedular->IsStarted())
			{
			iWaitSchedular->AsyncStop();
			}
	    iError = errCode;	
	    }
	delete globaluid;
	inparam->Reset();
	outparam->Reset();
    calname.Reset();
	}


int DeleteGuidAsync()
	{
    __UHEAP_MARK;
	CTestAsyncDeleteBefore* test = CTestAsyncDeleteBefore::NewL();
	int res = test->Start();
	delete test;
	return res;

    __UHEAP_MARKEND;
	
	}

