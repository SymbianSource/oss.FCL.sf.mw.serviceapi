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


#include "calendarinterface.h"
#include<liwcommon.h>
#include<liwvariant.h>
#include<liwservicehandler.h>

#include"notify.h"

_LIT8(KTestInterface, 	"IDataSource");
_LIT8(KTestContent,		"Service.Calendar");
_LIT8(KCmd,				"RequestNotification");
//_LIT8(KCmdAdd,			"Add");
//_LIT8(KCmdDelete,		"Delete");
//_LIT8(KCmdCancel,		"Cancel");

//_LIT8(KFilter,			"Filter");
//_LIT8(KItem,			"Item");
//_LIT8(KCalendarName,	"CalendarName");

_LIT(KEntryTypeMeeting,	"Meeting");
_LIT(KEntryTypeTodo,	"ToDo");

//const TChar KUidSeparator = ':';


_LIT(KTestCalendar, 	"c:CalChangeNotify");

TInt RemoveProvCalendar(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar);
TInt AddProvCalendar(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar);
TInt AddProvAppointmentDailyRepeat(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUint& localuid);
TInt AddProvTodo(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUint& localuid);

CCalCallback* CCalCallback::NewL(CActiveSchedulerWait* aWaitSchedular, TInt& aResult)
	{
	return new (ELeave) CCalCallback(aWaitSchedular, aResult);
	}
		
TInt CCalCallback::HandleNotifyL(TInt aCmdId,
									        TInt aEventId,
									        CLiwGenericParamList& aEventParamList,
									        const CLiwGenericParamList& aInParamList)
	{
	TInt pos = 0;
	TInt result = KErrNone;
    const TLiwGenericParam* output = aEventParamList.FindFirst( pos,_L8("ReturnValue"));
	
	if(output)
		{
		CLiwIterable* iterlist = output->Value().AsIterable();

	    TLiwVariant data;
      
        while( iterlist->NextL(data))
			{
			const CLiwMap* Map = data.AsMap(); 
			
			TLiwVariant varluid;
			TUint luid = 0;
			TInt changetype = -1;
			
			if( Map->FindL(_L8("LocalId"),varluid))
				{
				TLex lex(varluid.AsDes());
				TInt32 num;
				lex.Val(num);
				
				luid = TUint(num);
				}
			
			if( Map->FindL(_L8("ChangeType"),varluid))
				{
				TPtrC tmp = varluid.AsDes();
				if(tmp.CompareF(_L("Add")) == 0)
					changetype = 1;
				else if(tmp.CompareF(_L("Delete")) == 0)
					changetype = 2;
				else if(tmp.CompareF(_L("Modify")) == 0)
					changetype = 3;
				}
			varluid.Reset();
			
			if( ((luid == iLocalUid) || !iCheckLocalUid ) && (iChangeType == changetype))
				{
				iResult = KErrNone;
				break;
				}
			
			}
		data.Reset();
		}

	if ( iWaitSchedular && iWaitSchedular->IsStarted())
		{
		iWaitSchedular->AsyncStop();
		}
		return 0;
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
		iTestState = ETestIssueRequest;
		iResult = KErrGeneral;
		}

void CTestAsync::DoCancel()
	{

	}

void CTestAsync::RunL()
	{
	if(iTestState == ETestIssueRequest)
		{
		TestFunc();
		iTestState = ETestProcessRequest;

		iStatus = KRequestPending;
		SetActive();
		TRequestStatus* temp = &iStatus;
		User::RequestComplete(temp, KErrNone);
		if(iStopWaitSch && iWaitSchedular->IsStarted())
			iWaitSchedular->AsyncStop();
		}
	else if(iTestState == ETestProcessRequest)
		{
		if ( iChangeType == 1 )
			DoAddChange();
		else if ( iChangeType == 2 )
			DoDeleteChange();
		if ( iChangeType == 3 )
			DoUpdateChange();
		}
	}

void CTestAsync::DoAddChange()
	{
	CLiwGenericParamList* inparam = &(iServiceHandler->InParamListL());
	CLiwGenericParamList* outparam = &(iServiceHandler->OutParamListL());
	TUint localUid;
	AddProvAppointmentDailyRepeat(inparam, outparam, interface, KTestCalendar, localUid );
	iCallback->iLocalUid = localUid;
	}
	
void CTestAsync::DoDeleteChange()
	{
	CLiwGenericParamList* inparam = &(iServiceHandler->InParamListL());
	CLiwGenericParamList* outparam = &(iServiceHandler->OutParamListL());
	
   	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

	TLiwGenericParam element1;	
	element1.SetNameAndValueL(_L8("Type"),TLiwVariant(_L("CalendarEntry")));
	inparam->AppendL(element1);
	element1.Reset();
    
    map->InsertL(_L8("CalendarName"), TLiwVariant(KTestCalendar) ); 

    CLiwDefaultList* uidlist = CLiwDefaultList::NewL();
    
    TBuf<10> luid;
    luid.Num(TInt64(iLocalUid));
    uidlist->AppendL(TLiwVariant(luid));
    map->InsertL(_L8("LocalIdList"), TLiwVariant(uidlist)); 

    uidlist->DecRef();
    
    TLiwVariant filterparam(map);
	TLiwGenericParam element ;	
	element.SetNameAndValueL(_L8("Data"),filterparam);
	filterparam.Reset();
	
	inparam->AppendL(element);
	element.Reset();
    map->DecRef();
    CleanupStack::Pop(map);

	TRAPD(err1, interface->ExecuteCmdL(KCmdDelete, *inparam, *outparam ));
	inparam->Reset();
	outparam->Reset();
	}

void CTestAsync::DoUpdateChange()
	{
	CLiwGenericParamList* inparam = &(iServiceHandler->InParamListL());
	CLiwGenericParamList* outparam = &(iServiceHandler->OutParamListL());
	
   	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

	TLiwGenericParam element1;	
	element1.SetNameAndValueL(_L8("Type"),TLiwVariant(_L("CalendarEntry")));
	inparam->AppendL(element1);
	element1.Reset();
    
    map->InsertL(_L8("CalendarName"), TLiwVariant(KTestCalendar) ); 
    //map->InsertL(_L8("LocalUid"), TLiwVariant(iLocalUid) ); 
    TBuf<10> luid;
    luid.Num(TInt64(iLocalUid));
    map->InsertL(_L8("LocalId"), TLiwVariant(luid)); 
    map->InsertL(_L8("Description"), TLiwVariant(_L("New Description") )); 

    
    TLiwVariant filterparam(map);
	TLiwGenericParam element ;	
	element.SetNameAndValueL(_L8("Item"),filterparam);
	filterparam.Reset();
	
	inparam->AppendL(element);
	element.Reset();
    map->DecRef();
    CleanupStack::Pop(map);

	TRAPD(err1, interface->ExecuteCmdL(KCmdAdd, *inparam, *outparam ));
	inparam->Reset();
	outparam->Reset();
	}

TInt CTestAsync::Result()
	{
	return iResult;
	}

void CTestAsync::Start( TInt aChangeType, TBool aLocalUid, TBool aPosBased, TBool aStopWaitSch )
	{
	iCheckLocalUid = aLocalUid;
	iChangeType = aChangeType;
	iPosBased = aPosBased;
	iStopWaitSch = aStopWaitSch;
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}

void CTestAsync::CancelNotification(TBool aResetOutput)
	{
	CLiwGenericParamList* inparam = &(iServiceHandler->InParamListL());
	CLiwGenericParamList* outparam = &(iServiceHandler->OutParamListL());
	
	TLiwGenericParam element1;	
	
	if(iPosBased)
		element1.SetNameAndValueL(KNullDesC8,TLiwVariant(_L("CalendarEntry")));
	else
		element1.SetNameAndValueL(_L8("Type"),TLiwVariant(_L("CalendarEntry")));
	
	//inparam->AppendL(element1);
	element1.Reset();
    
	TLiwGenericParam element2;	

	if(iPosBased)
		element2.SetNameAndValueL(KNullDesC8,TLiwVariant(iTransactionId));
	else
		element2.SetNameAndValueL(_L8("TransactionID"), TLiwVariant(iTransactionId));
	inparam->AppendL(element2);
	element2.Reset();
    
    TRAPD(err1, interface->ExecuteCmdL(KCmdCancel, *inparam, *outparam, KLiwOptCancel ));
    
    TInt pos = 0 ;
    
    const TLiwGenericParam* output = outparam->FindFirst( pos,_L8("ErrorCode"));
	
	if ( aResetOutput && ( (err1 == KErrNone) && output ))
		{
		iResult = output->Value().AsTInt32();
		}
	
	inparam->Reset();
	outparam->Reset();
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
	
	
	// Add one entry and get the LocalUid
	RemoveProvCalendar(inparam, outparam, interface, KTestCalendar);
	
	if( AddProvCalendar(inparam, outparam, interface, KTestCalendar) != KErrNone)
		{
		if(iWaitSchedular->IsStarted())
			iWaitSchedular->AsyncStop();
		inparam->Reset();
		outparam->Reset();
		return;
		};
	
	
	TUint localUid;
	if( AddProvAppointmentDailyRepeat(inparam, outparam, interface, KTestCalendar, localUid ) != KErrNone )
		{
		if(iWaitSchedular->IsStarted())
			iWaitSchedular->AsyncStop();
		inparam->Reset();
		outparam->Reset();
		return;
		};
	
	inparam->Reset();
	outparam->Reset();

	if( AddProvAppointmentDailyRepeat(inparam, outparam, interface, KTestCalendar, localUid ) != KErrNone )
		{
		if(iWaitSchedular->IsStarted())
			iWaitSchedular->AsyncStop();
		inparam->Reset();
		outparam->Reset();
		return;
		};
	
	inparam->Reset();
	outparam->Reset();

   	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

	TLiwGenericParam element1;	
	
	if( iPosBased )
		element1.SetNameAndValueL(KNullDesC8,TLiwVariant(_L("CalendarEntry")));
	else
		element1.SetNameAndValueL(_L8("Type"),TLiwVariant(_L("CalendarEntry")));
	
	inparam->AppendL(element1);
	element1.Reset();
    
    map->InsertL(_L8("CalendarName"), TLiwVariant(KTestCalendar) ); 

    CLiwDefaultList* uidlist = CLiwDefaultList::NewL();
    TBuf<10> luid;
    luid.Num(TInt64(localUid));
    //map->InsertL(_L8("LocalUid"), TLiwVariant(luid)); 
    uidlist->AppendL(TLiwVariant(luid));
    
    if ( iChangeType != 1 )
    	map->InsertL(_L8("LocalIdList"), TLiwVariant(uidlist)); 

    uidlist->DecRef();
    
    TLiwVariant filterparam(map);
	TLiwGenericParam element ;	
	
	if( iPosBased )
		element.SetNameAndValueL(KNullDesC8,filterparam);
	else
		element.SetNameAndValueL(_L8("Filter"),filterparam);
	
	filterparam.Reset();
	
	inparam->AppendL(element);
	element.Reset();
    map->DecRef();
    CleanupStack::Pop(map);

	
	iCallback = CCalCallback::NewL(iWaitSchedular, iResult);

	iCallback->iChangeType = iChangeType;
	iCallback->iLocalUid = localUid;
	iCallback->iCheckLocalUid = iCheckLocalUid;
	iLocalUid = localUid;

	TRAPD(err1, interface->ExecuteCmdL(KCmd, *inparam, *outparam, KLiwOptASyncronous, iCallback));
	
	const TLiwGenericParam* output = outparam->FindFirst( pos,_L8("TransactionID"));
	
	if(output)
		{
		iTransactionId = output->Value().AsTInt32();
		}
	else
		{
		if(iWaitSchedular->IsStarted())
			iWaitSchedular->AsyncStop();
		}	

	
	inparam->Reset();
	outparam->Reset();
	}


TInt ReqNotification( TInt aChangeType, TBool aLocalUid, TBool aPosBased  )
	{
	TInt result;
	
	__UHEAP_MARK;
	TInt cells = User::CountAllocCells();
	CTestAsync* test = CTestAsync::NewL();
	test->Start( aChangeType, aLocalUid, aPosBased );
	result = test->Result();
	test->CancelNotification();
	delete test;
	cells = User::CountAllocCells();
	__UHEAP_MARKEND;
	
	return result;
	}
	
TInt ReqNotificationCancel( TInt aChangeType, TBool aLocalUid, TBool aPosBased, TBool aInvalidId, TBool aMultiCancel  )
	{
	TInt result;
	
	__UHEAP_MARK;
	TInt cells = User::CountAllocCells();
	CTestAsync* test = CTestAsync::NewL();
	test->Start( aChangeType, aLocalUid, aPosBased );
	result = test->Result();
	test->CancelNotification();
	
	if( aInvalidId )
		{
		test->CancelNotification(ETrue);
		result = test->Result();
		if(result == 1012)
			result = KErrNone;
		}

	if( aMultiCancel )
		{
		for(TInt i = 0; i < 100; i++)
			test->CancelNotification(ETrue);

		result = test->Result();
		if(result == 1012)
			result = KErrNone;
		}
	
	delete test;
	cells = User::CountAllocCells();
	__UHEAP_MARKEND;
	
	return result;
	}
	
TInt ReqNotificationWithoutWaitSch( TInt aChangeType, TBool aLocalUid, TBool aPosBased  )
	{
	__UHEAP_MARK;
	TInt cells = User::CountAllocCells();
	CTestAsync* test = CTestAsync::NewL();
	test->Start( aChangeType, aLocalUid, aPosBased, ETrue );
	//test->CancelNotification();
	delete test;
	cells = User::CountAllocCells();
	__UHEAP_MARKEND;
	
	return KErrNone;
	}
	
TInt RemoveProvCalendar(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar)
	{
	inparam->Reset();
	outparam->Reset();

   	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

    TLiwVariant content(_L("Calendar"));
	TLiwGenericParam element1;	
	element1.SetNameAndValueL(_L8("Type"),content);
	inparam->AppendL(element1);
	content.Reset();
	element1.Reset();
    
    map->InsertL(_L8("CalendarName"), TLiwVariant(aCalendar)); 
    
    TLiwVariant filterparam(map);
	TLiwGenericParam element ;	
	element.SetNameAndValueL(_L8("Data"),filterparam);
	filterparam.Reset();
	
	inparam->AppendL(element);
	element.Reset();
    map->DecRef();
    CleanupStack::Pop(map);

	TRAPD(err, interface->ExecuteCmdL( KCmdDelete ,*inparam,*outparam ));
    TInt pos = 0 ;
    
    const TLiwGenericParam* output = outparam->FindFirst( pos,_L8("ErrorCode"));
	
	if(output)
		{
		err = output->Value().AsTInt32();
		}
	
	inparam->Reset();
	outparam->Reset();

	return err;
	}
	
TInt AddProvCalendar(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar)
	{
	inparam->Reset();
	outparam->Reset();

   	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

    TLiwVariant content(_L("Calendar"));
	TLiwGenericParam element1;	
	element1.SetNameAndValueL(_L8("Type"),content);
	inparam->AppendL(element1);
	content.Reset();
	element1.Reset();
    
    
    map->InsertL(_L8("CalendarName"), TLiwVariant(aCalendar) ); 
    
	TLiwGenericParam element;	
	element.SetNameAndValueL(_L8("Item"),TLiwVariant(map));
	
	inparam->AppendL(element);
	element.Reset();
    map->DecRef();
    CleanupStack::Pop(map);

	TRAPD(err, interface->ExecuteCmdL( KCmdAdd, *inparam,*outparam ));
    TInt pos = 0 ;
    
    const TLiwGenericParam* output = outparam->FindFirst( pos,_L8("ErrorCode"));
	
	if(output)
		{
		err = output->Value().AsTInt32();
		}
	
	inparam->Reset();
	outparam->Reset();

	return err;
	};
	
void GetLocalId( CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aGlobalUid, const TDesC& calname, TUint& localuid )
	{
	/*aOutLocalUid = 0;
	if( aLocalUid.Length() )
		{
		TInt sepPos = aLocalUid.Locate( KUidSeparator );
		TPtrC temp;
		if( sepPos == KErrNotFound )
			{
			temp.Set(aLocalUid.Mid(0));
			}
		else
			{
			temp.Set(aLocalUid.Mid(0, sepPos));
			}

		TLex lex(temp);
		TInt32 num;

		if(lex.Val(num) == KErrNone)
			aOutLocalUid = TCalLocalUid(num);
		}*/
	TBuf<10> local;

	inparam->Reset();
	outparam->Reset();
    
    TLiwGenericParam dsNameParam(KContentType, TLiwVariant(_L("CalendarEntry")));
	inparam->AppendL(dsNameParam);
	
	CLiwDefaultMap *filterMap = CLiwDefaultMap::NewL();
	TLiwGenericParam filterParam(KFilter, TLiwVariant(filterMap));
	inparam->AppendL(filterParam);
	filterMap->DecRef();

    if(calname.Length())
    	filterMap->InsertL(KCalendarName,TLiwVariant(calname));
    filterMap->InsertL(_L8("id"),TLiwVariant(aGlobalUid));

	TRAPD(err,interface->ExecuteCmdL( _L8("GetList") ,*inparam ,*outparam));
    TInt pos = 0 ;
    TBuf<10> result;
    const TLiwGenericParam* output = outparam->FindFirst( pos,_L8("ErrorCode"));
	
	if(output)
		{
		err = output->Value().AsTInt32();
		if( err == KErrNone )
			{
			pos = 0;
            output = outparam->FindFirst( pos,_L8("ReturnValue"));
            CLiwMap* map;
    		TInt retvalue = KErrNone;
    
			if ( output )     
				{
				CLiwIterable* iterlist = output->Value().AsIterable();
		      	if(iterlist)
		      		{
				    TLiwVariant data1;
		      		while(iterlist->NextL(data1) )
			      		{
						const CLiwMap* res = data1.AsMap();
						if ( res )
							{
							TLiwVariant data;
							if(res->FindL(_L8("LocalId"), data))
								local.Copy( data.AsDes() ) ;
								TLex lex(local);
							TInt32 num;

							if(lex.Val(num) == KErrNone)
								localuid = TCalLocalUid(num);

							data.Reset();
							}
			      		}
		      		data1.Reset();  
		      		}
				}
			}
		}
	
	inparam->Reset();
	outparam->Reset();
	}

TInt AddProvAppointmentDailyRepeat(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUint& localuid)
	{
	inparam->Reset();
	outparam->Reset();
	TBuf<10> luid;
	luid.Zero();
	TBuf<50> uidval;
	TInt cells = User::CountAllocCells();
//	__UHEAP_MARK;

   	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

    TLiwVariant content(_L("CalendarEntry"));
	TLiwGenericParam element1;	
	element1.SetNameAndValueL(_L8("Type"),content);
	inparam->AppendL(element1);
	content.Reset();
	element1.Reset();


    map->InsertL(_L8("CalendarName"), TLiwVariant(aCalendar) ); 
	map->InsertL(_L8("Type"), TLiwVariant( KEntryTypeMeeting ));
	map->InsertL(_L8("StartTime"), TLiwVariant(TTime(TDateTime(2007,EOctober,23,10,0,0,0))));
	map->InsertL(_L8("EndTime"), TLiwVariant(TTime(TDateTime(2007,EOctober,23,10,30,0,0))));
	map->InsertL(_L8("Replication"), TLiwVariant(_L("Open")));
	map->InsertL(_L8("Description"), TLiwVariant(_L("Meeting")));
	map->InsertL(_L8("Status"), TLiwVariant(_L("Confirmed")));
	map->InsertL(_L8("Method"), TLiwVariant(_L("None")));
	
   	CLiwDefaultMap* repeatmap = CLiwDefaultMap::NewL();
	CleanupStack::PushL(repeatmap);
	repeatmap->InsertL(_L8("Type"), TLiwVariant(TInt32(1)));
	repeatmap->InsertL(_L8("StartDate"), TLiwVariant(TTime(TDateTime(2007,EOctober,23,10,0,0,0))));
	repeatmap->InsertL(_L8("UntilDate"), TLiwVariant(TTime(TDateTime(2007,EOctober,30,10,0,0,0))));
	map->InsertL(_L8("RepeatRule"), TLiwVariant(repeatmap));
	CleanupStack::Pop(repeatmap);
	repeatmap->DecRef();
	
    
	TLiwGenericParam element;	
	element.SetNameAndValueL(_L8("Item"),TLiwVariant(map));
	
	inparam->AppendL(element);
	element.Reset();
    map->DecRef();
    CleanupStack::Pop(map);
    
    cells = User::CountAllocCells();

	//TInt err;
	TRAPD(err, interface->ExecuteCmdL( KCmdAdd, *inparam,*outparam ));
    TInt pos = 0 ;
    
    cells = User::CountAllocCells();
    
    const TLiwGenericParam* output = outparam->FindFirst( pos,_L8("ErrorCode"));
	
	cells = User::CountAllocCells();
	
	if(output)
		{
		err = output->Value().AsTInt32();
		if ( err == KErrNone )
			{
			output = outparam->FindFirst( pos,_L8("ReturnValue"));
			if(output)
				{
				uidval.Copy((TPtrC)(output->Value().AsDes()))   ;
				TPtrC globaluid(uidval);
			    GetLocalId( inparam, outparam, interface, globaluid, aCalendar, localuid );
				/*const CLiwMap* res = output->Value().AsMap();
				if ( res )
					{
					TLiwVariant luid;
					if(res->FindL(_L8("LocalUid"), luid))
						{
						TLex lex(luid.AsDes());
						TInt32 num;
						lex.Val(num);
						
						TUint localuid = 0;
						localuid = TUint(num);
						}
					else
						err = -1;
					luid.Reset();	
					}
				else
					err = -1;*/
				}
			else
				err = -1;
			}
		}
cells = User::CountAllocCells();	
	inparam->Reset();
	outparam->Reset();
	cells = User::CountAllocCells();
//	__UHEAP_MARKEND;

	return err;
	};

TInt AddProvTodo(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUint& localuid)
	{
	inparam->Reset();
	outparam->Reset();
	TBuf<10> luid;
	luid.Zero();
	TBuf<50> uidval;
	TInt cells = User::CountAllocCells();
//	__UHEAP_MARK;

   	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

    TLiwVariant content(_L("CalendarEntry"));
	TLiwGenericParam element1;	
	element1.SetNameAndValueL(_L8("Type"),content);
	inparam->AppendL(element1);
	content.Reset();
	element1.Reset();


    map->InsertL(_L8("CalendarName"), TLiwVariant(aCalendar) ); 
	map->InsertL(_L8("Type"), TLiwVariant( KEntryTypeTodo ));
    map->InsertL(_L8("EndTime"), TLiwVariant(TTime(TDateTime(2007,EOctober,25,10,0,0,0)))); 
	map->InsertL(_L8("Replication"), TLiwVariant(_L("Open")));
	map->InsertL(_L8("Description"), TLiwVariant(_L("Todo entry")));
	
	TLiwGenericParam element;	
	element.SetNameAndValueL(_L8("Item"),TLiwVariant(map));
	
	inparam->AppendL(element);
	element.Reset();
    map->DecRef();
    CleanupStack::Pop(map);
    
    cells = User::CountAllocCells();

	//TInt err;
	TRAPD(err, interface->ExecuteCmdL( KCmdAdd, *inparam,*outparam ));
    TInt pos = 0 ;
    
    cells = User::CountAllocCells();
    
    const TLiwGenericParam* output = outparam->FindFirst( pos,_L8("ErrorCode"));
	
	cells = User::CountAllocCells();
	
	if(output)
		{
		err = output->Value().AsTInt32();
		if ( err == KErrNone )
			{
			output = outparam->FindFirst( pos,_L8("ReturnValue"));
			if(output)
				{
				uidval.Copy((TPtrC)(output->Value().AsDes()))   ;
				TPtrC globaluid(uidval);
			    GetLocalId( inparam, outparam, interface, globaluid, aCalendar, localuid );
				/*const CLiwMap* res = output->Value().AsMap();
				if ( res )
					{
					TLiwVariant luid;
					if(res->FindL(_L8("LocalUid"), luid))
						{
						TLex lex(luid.AsDes());
						TInt32 num;
						lex.Val(num);
						
						TUint localuid = 0;
						localuid = TUint(num);
						}
					else
						err = -1;
					luid.Reset();	
					}
				else
					err = -1;*/
				}
			else
				err = -1;
			}
		}
cells = User::CountAllocCells();	
	inparam->Reset();
	outparam->Reset();
	cells = User::CountAllocCells();
//	__UHEAP_MARKEND;

	return err;
	};
