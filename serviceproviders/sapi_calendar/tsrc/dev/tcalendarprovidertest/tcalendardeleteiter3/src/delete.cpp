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


#include<liwcommon.h>
#include<liwvariant.h>
#include<liwservicehandler.h>
#include "tcalendardeletetest.h"
#include "delete.h"
#include "calendarheader.h"

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
_LIT8(KCalendarList, 	"CalendarList");

_LIT8(KDeleteAll,"DeleteAll");
_LIT(KCalFileName1,"C:CalendarFileA");
_LIT8(KCalendarName,"CalendarName");

TInt AddProvCalendar(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar);
TInt RemoveProvCalendar(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar);
TInt AddProvToDo(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset);
TInt AddProvDayEvent(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset);
TInt AddProvAppointmentDailyRepeat(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset);


CCalCallback* CCalCallback::NewL(CActiveSchedulerWait* aWaitSchedular, MLiwInterface* aInterface, TInt& aRes, TInt& aFlag)
	{
	return new (ELeave) CCalCallback(aWaitSchedular, aInterface, aRes, aFlag);
	}
		
TInt CCalCallback::HandleNotifyL(TInt aCmdId,
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
   	            	count++;	
		      		}
	      		data.Reset();  
	      		}
			}
		if(iOption==1)
			{
			if(count != 8)
				errCode = KErrGeneral;	
			}
		else if(iOption==2)
			{
			if(count != 5)
				errCode = KErrGeneral;	
			}
		else if(iOption==3)
			{
			if(count != 4)
				errCode = KErrGeneral;	
			}
		else if(iOption==4)
			{
			if(count != 0)
				errCode = KErrGeneral;	
			}
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



CTestAsync* CTestAsync::NewL()
	{
	CTestAsync* self = new (ELeave) CTestAsync();
	self->ConstructL();
	return self;
	}

CTestAsync::~CTestAsync()
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


TInt CTestAsync::Start(TInt aFlag, TBool aAsync)
	{
	iFlag = aFlag;
	iAsync = aAsync;
	if(aAsync)
		{
		SetActive();
		TRequestStatus* temp = &iStatus;
		User::RequestComplete(temp, KErrNone);
		iWaitSchedular->Start();
		}
	else
		TestFunc();
	
	return iResult;	
	}


int CTestAsync::TestFunc()
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
	
	RemoveProvCalendar(inparam, outparam, interface, KCalFileName1);
	AddProvCalendar(inparam, outparam, interface, KCalFileName1);

	TUIDSet* uidset;
	//RPointerArray<TUIDSet> arruids(5);
  
    AddProvToDo(inparam, outparam, interface, KCalFileName1 ,uidset);
    delete uidset;
    
    AddProvDayEvent(inparam, outparam, interface, KCalFileName1 ,uidset)	;
    delete uidset;

    AddProvAppointmentDailyRepeat(inparam, outparam, interface, KCalFileName1 ,uidset );
    delete uidset;
    
	TLiwVariant dsName;
	dsName.Set(_L("CalendarEntry"));
    TLiwGenericParam dsNameParam(KContentType, dsName);
	inparam->AppendL(dsNameParam);
	dsName.Reset();

	CLiwDefaultMap *filterMap = CLiwDefaultMap::NewL();
	TLiwGenericParam filterParam(KData, TLiwVariant(filterMap));
	inparam->AppendL(filterParam);
	filterMap->DecRef();

    filterMap->InsertL(KCalendarName,TLiwVariant(_L("C:CalendarFileA")));
	if(iFlag == 1)
		{
		filterMap->InsertL(_L8("StartRange"), TLiwVariant(TTime(TDateTime(2007,EAugust,19,0,0,0,0))));
		filterMap->InsertL(_L8("EndRange"), TLiwVariant(TTime(TDateTime(2007,EOctober,24,0,0,0,0))));
		}

	else if(iFlag == 2)
		{
		filterMap->InsertL(_L8("EndRange"), TLiwVariant(TTime(TDateTime(2007,EOctober,25,11,0,0,0))));
		}
		
	else if(iFlag == 3)
		{
		filterMap->InsertL(_L8("StartRange"), TLiwVariant(TTime(TDateTime(2007,EOctober,25,10,0,0,0))));
		}
	
	else if(iFlag == 4)
		{
		filterMap->InsertL(_L8("DeleteAll"), TLiwVariant(TBool(ETrue)));
		}
		
	if(iAsync)
		{
		iCallback = CCalCallback::NewL(iWaitSchedular, interface, iResult, iFlag);
		TRAPD(err1 ,interface->ExecuteCmdL(KCmd, *inparam, *outparam, KLiwOptASyncronous, iCallback));
		inparam->Reset();
		outparam->Reset();
		}
	else
		{
		TRAPD(err1 ,interface->ExecuteCmdL(KCmd, *inparam, *outparam));
		const TLiwGenericParam* p = outparam->FindFirst(pos, KErrorCode); // Finding Error Code
        TInt errCode;
		if( p )
			{
			errCode = p->Value().AsTInt32();
			}
		inparam->Reset();
		outparam->Reset();
	  
	 	if ( errCode == KErrNone ) 
	 		{
		    TLiwGenericParam dsNameParam(KContentType, TLiwVariant(_L("CalendarEntry")));
			inparam->AppendL(dsNameParam);
			
			CLiwDefaultMap *filterMap = CLiwDefaultMap::NewL();
			TLiwGenericParam filterParam(KFilter, TLiwVariant(filterMap));
			inparam->AppendL(filterParam);
			filterMap->DecRef();

		    filterMap->InsertL(KCalendarName,TLiwVariant(_L("C:CalendarFileA")));
		    

			TInt err = 0;
			TRAP(err,interface->ExecuteCmdL( _L8("GetList") ,*inparam ,*outparam));
		    
		    pos = 0 ;
		    
		    const TLiwGenericParam* finaloutput = outparam->FindFirst( pos,_L8("ReturnValue"));
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
	   	            	count++;	
			      		}
		      		data.Reset();  
		      		}
				}
			if(iFlag==1)
				{
				if(count != 8)
					errCode = KErrGeneral;	
				}
			else if(iFlag==2)
				{
				if(count != 5)
					errCode = KErrGeneral;	
				}
			else if(iFlag==3)
				{
				if(count != 4)
					errCode = KErrGeneral;	
				}
			else if(iFlag==4)
				{
				if(count != 0)
					errCode = KErrGeneral;	
				}
			inparam->Reset();
			outparam->Reset();
		    RemoveProvCalendar(inparam, outparam, interface, KCalFileName1);
	 		}
		if ( iWaitSchedular && iWaitSchedular->IsStarted())
			{
			iWaitSchedular->AsyncStop();
			}
			iResult = errCode;
			return errCode;
			}
	}

	

int DeleteAllAsync(int flag, TBool async)
	{
    __UHEAP_MARK;
	CTestAsync* test = CTestAsync::NewL();
	int res = test->Start(flag, async);
	delete test;
    __UHEAP_MARKEND;
	return res;
	
	}


CTestSync* CTestSync::NewL()
	{
	CTestSync* self = new (ELeave) CTestSync();
	self->ConstructL();
	return self;
	}

CTestSync::~CTestSync()
	{
	if( interface )
	interface->Close();
	
	delete iServiceHandler;
	}


void CTestSync::ConstructL()
	{
	}


CTestSync::CTestSync()
	{
	interface = NULL ;
	}

int CTestSync::TestFunc()
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
	TLiwVariant dsName;
	dsName.Set(_L("CalendarEntry"));
    TLiwGenericParam dsNameParam(KContentType, dsName);
	inparam->AppendL(dsNameParam);
	dsName.Reset();
	
	CLiwDefaultMap *filterMap = CLiwDefaultMap::NewL();
	TLiwGenericParam filterParam(KData, TLiwVariant(filterMap));
	inparam->AppendL(filterParam);
	filterMap->DecRef();

	TLiwVariant calname;
    calname.Set(KCalFileName1);;
    filterMap->InsertL(_L8("CalendarName"),calname);
    calname.Reset();
	
	TLiwVariant flag;
    flag.Set(ETrue);;
    filterMap->InsertL(KDeleteAll,flag);
	flag.Reset();
	    
	TRAPD(err1 ,interface->ExecuteCmdL(KCmd, *inparam, *outparam/*, KLiwOptASyncronous, iCallback*/));
	inparam->Reset();
	outparam->Reset();
    return err1;
	}


int DeleteAllSync()
	{
	__UHEAP_MARK;
	CTestSync* test = CTestSync::NewL();
    int res =  test->TestFunc();
	delete test;
	__UHEAP_MARKEND;
	return 0;
	
	}
	
int DeleteDefaultSync()
	{
	__UHEAP_MARK;
	CTestSync* test = CTestSync::NewL();
	int res = test->DeleteDefaultCalendar();
	delete test;
	__UHEAP_MARKEND;
	return res;
	
	}
int DeleteWrongSync()
	{
	__UHEAP_MARK;
	CTestSync* test = CTestSync::NewL();
	int res = test->DeleteWrongCal();
	delete test;
	__UHEAP_MARKEND;
	return res;
	
	}
	
int CTestSync::DeleteDefaultCalendar()
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
	TLiwVariant dsName;
	dsName.Set(_L("Calendar"));
    TLiwGenericParam dsNameParam(KContentType, dsName);
	inparam->AppendL(dsNameParam);
	dsName.Reset();
	
	CLiwDefaultMap *filterMap = CLiwDefaultMap::NewL();
	TLiwGenericParam filterParam(KData, TLiwVariant(filterMap));
	inparam->AppendL(filterParam);
	filterMap->DecRef();

    filterMap->InsertL(KCalendarName,TLiwVariant(_L("C:Calendar")));
	    
	TRAPD(err1 ,interface->ExecuteCmdL(KCmd, *inparam, *outparam/*, KLiwOptASyncronous, iCallback*/));
	TInt errCode;
	const TLiwGenericParam* p = outparam->FindFirst(pos, KErrorCode); // Finding Error Code
	if( p )
		{
		errCode = p->Value().AsTInt32();
		}
	inparam->Reset();
	outparam->Reset();
	return errCode;	
	}
	
int CTestSync::DeleteWrongCal()
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
	TLiwVariant dsName;
	dsName.Set(_L("Calendar"));
    TLiwGenericParam dsNameParam(KContentType, dsName);
	inparam->AppendL(dsNameParam);
	dsName.Reset();
	
	CLiwDefaultMap *filterMap = CLiwDefaultMap::NewL();
	TLiwGenericParam filterParam(KData, TLiwVariant(filterMap));
	inparam->AppendL(filterParam);
	filterMap->DecRef();

    filterMap->InsertL(KCalendarName,TLiwVariant(_L("C:CalendarFileZ")));
	    
	TRAPD(err1 ,interface->ExecuteCmdL(KCmd, *inparam, *outparam/*, KLiwOptASyncronous, iCallback*/));
	TInt errCode;
	const TLiwGenericParam* p = outparam->FindFirst(pos, KErrorCode); // Finding Error Code
	if( p )
		{
		errCode = p->Value().AsTInt32();
		}
	inparam->Reset();
	outparam->Reset();
	return errCode;	
	}