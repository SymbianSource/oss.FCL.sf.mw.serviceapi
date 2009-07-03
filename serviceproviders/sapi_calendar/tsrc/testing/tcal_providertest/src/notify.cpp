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
#include<LiwCommon.h>
#include<LiwVariant.h>
#include<LiwServiceHandler.h>
#include "tcal_providertest.h"
#include"notify.h"

_LIT8(KTestInterface, 	"IDataSource");
_LIT8(KTestContent,		"Service.Calendar");
_LIT8(KCmd,				"RequestNotification");
_LIT(KTestCalendar, 	"c:CalChangeNotify");
_LIT(KEntryTypeMeeting,	"Meeting");

TBuf<100> globalid;


/*TInt RemoveProvCalendar1(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar);
TInt AddProvCalendar1(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar);
//TInt AddProvAppointmentDailyRepeat1(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUint& localuid);
TInt AddProvAppointmentDailyRepeat1(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset);*/
TInt GetLocalUid1( CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar,TCalLocalUid& aOutLocalUid );

CCalCallback* CCalCallback::NewL(CActiveSchedulerWait* aWaitSchedular, TInt32& aResult)
	{
	return new (ELeave) CCalCallback(aWaitSchedular, aResult);
	}
		
TInt CCalCallback::HandleNotifyL(TInt aCmdId,
									        TInt aEventId,
									        CLiwGenericParamList& aEventParamList,
									        const CLiwGenericParamList& aInParamList)
	{
	TInt pos = 0;
	TInt32 result = KErrNone;
    const TLiwGenericParam* output = aEventParamList.FindFirst( pos,_L8("ReturnValue"));
	
	if(iChangeType ==4)
		iChangeType = 3;
	
	
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
			
			if( Map->FindL(_L8("LocalUid"),varluid))
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
		}
	else if(iTestState == ETestProcessRequest)
		{
		if ( iChangeType == 1 )
			DoAddChange();
		else if ( iChangeType == 2 )
			DoDeleteChange();
		else if ( iChangeType == 3 )
			DoUpdateChange();
		else if( iChangeType == 4)
		{
			iChangeType = 3;
			DoExpUpdate();
		}
		
			
		}
	}


void CTestAsync::DoExpUpdate()
{
	TInt pos =0;
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
    map->InsertL(_L8("Format"), TLiwVariant(_L("VCal")) );
	map->InsertL(_L8("FileName"), TLiwVariant(_L("c:\\exportall.txt")));

    uidlist->DecRef();
    
    TLiwVariant filterparam(map);
	TLiwGenericParam element ;	
	element.SetNameAndValueL(_L8("Data"),filterparam);
	filterparam.Reset();
	
	inparam->AppendL(element);
	element.Reset();
    map->DecRef();
    CleanupStack::Pop(map);

	TRAPD(err1, interface->ExecuteCmdL(KCmdExport, *inparam, *outparam ));
	
	const TLiwGenericParam* exp_err = outparam->FindFirst(pos,KErrorCode);
   	if(exp_err)
   			iResult = exp_err->Value().AsTInt32();
   	
   	inparam->Reset();
	outparam->Reset();
   	if(iResult)
   	{
   		if ( iWaitSchedular && iWaitSchedular->IsStarted())
				iWaitSchedular->AsyncStop();		
   	}
   	else				
		DoUpdateChange();

	
}
void CTestAsync::DoAddChange()
	{
	CLiwGenericParamList* inparam = &(iServiceHandler->InParamListL());
	CLiwGenericParamList* outparam = &(iServiceHandler->OutParamListL());
//	TUint localUid;
	TUIDSet *uids = NULL;
	if(AddProvAppointmentDailyRepeat(inparam, outparam, interface, KTestCalendar, uids ) != KErrNone)
	{
		if(iWaitSchedular->IsStarted())
			iWaitSchedular->AsyncStop();
		RemoveProvCalendar(inparam, outparam, interface, KTestCalendar);
		interface->Close();
		inparam->Reset();
		outparam->Reset();		
	};	
//	iCallback->iLocalUid = localUid;
	delete uids;
	}
	
void CTestAsync::DoDeleteChange()
	{
	
	DoUpdateChange();
	if(!iResult)
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
	
		TInt pos=0;
	
		const TLiwGenericParam* del_err = outparam->FindFirst(pos,KErrorCode);
   		if(del_err)
   			iResult = del_err->Value().AsTInt32();
   	
   		if(iResult)
   		{
   			if ( iWaitSchedular && iWaitSchedular->IsStarted())
				iWaitSchedular->AsyncStop();		
   		}						
		inparam->Reset();
		outparam->Reset();
	}


	}

void CTestAsync::DoUpdateChange()
	{
	TInt pos=0;
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
	
	const TLiwGenericParam* update_err = outparam->FindFirst(pos,KErrorCode);
   	if(update_err)
   			iResult = update_err->Value().AsTInt32();
   	
   	if(iResult)
   	{
   		if ( iWaitSchedular && iWaitSchedular->IsStarted())
				iWaitSchedular->AsyncStop();		
   	}
   						
	inparam->Reset();
	outparam->Reset();
	
	}

TInt32 CTestAsync::Result()
	{
	return iResult;
	}

void CTestAsync::Start( TInt aChangeType, TBool aLocalUid )
	{
	iCheckLocalUid = aLocalUid;
	iChangeType = aChangeType;
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}

void CTestAsync::CancelNotification()
	{
	CLiwGenericParamList* inparam = &(iServiceHandler->InParamListL());
	CLiwGenericParamList* outparam = &(iServiceHandler->OutParamListL());
	
   	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

	TLiwGenericParam element1;	
	element1.SetNameAndValueL(_L8("Type"),TLiwVariant(_L("CalendarEntry")));
	inparam->AppendL(element1);
	element1.Reset();
    
	TLiwGenericParam element2;	
	element2.SetNameAndValueL(_L8("TransactionID"), TLiwVariant(iTransactionId));
	inparam->AppendL(element2);
	element2.Reset();
    
    
    TLiwVariant filterparam(map);
	TLiwGenericParam element ;	
	element.SetNameAndValueL(_L8("Item"),filterparam);
	filterparam.Reset();
	
	inparam->AppendL(element);
	element.Reset();
    map->DecRef();
    CleanupStack::Pop(map);

	TRAPD(err1, interface->ExecuteCmdL(KCmdCancel, *inparam, *outparam, KLiwOptCancel ));
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
	
	TUIDSet* uids = NULL;
	
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
	if( AddProvAppointmentDailyRepeat(inparam, outparam, interface, KTestCalendar, uids ) == KErrNone && uids)
	{
		globalid.Copy( uids->iGlobalUID->Des() );
		TInt lid_fetch_err = GetLocalUid1(inparam,outparam,interface,KTestCalendar,uids->iLocalUID)	;
		if(lid_fetch_err)
		{
				if(iWaitSchedular->IsStarted())
						iWaitSchedular->AsyncStop();
		    	RemoveProvCalendar(inparam, outparam, interface, KTestCalendar);
				interface->Close();
				iResult = lid_fetch_err;
				inparam->Reset();
				outparam->Reset();
				return;
		}	
	}	
	else
	{
		if(iWaitSchedular->IsStarted())
			iWaitSchedular->AsyncStop();
		inparam->Reset();
		outparam->Reset();
		return;
	};
	
/*	inparam->Reset();
	outparam->Reset();

	if( AddProvAppointmentDailyRepeat1(inparam, outparam, interface, KTestCalendar, localUid ) != KErrNone )
		{
		if(iWaitSchedular->IsStarted())
			iWaitSchedular->AsyncStop();
		inparam->Reset();
		outparam->Reset();
		return;
		};*/
	
	inparam->Reset();
	outparam->Reset();

   	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

	TLiwGenericParam element1;	
	element1.SetNameAndValueL(_L8("Type"),TLiwVariant(_L("CalendarEntry")));
	inparam->AppendL(element1);
	element1.Reset();
    
    map->InsertL(_L8("CalendarName"), TLiwVariant(KTestCalendar) ); 

    CLiwDefaultList* uidlist = CLiwDefaultList::NewL();
    TBuf<10> luid;
    luid.Num(TInt64(uids->iLocalUID));
    uidlist->AppendL(TLiwVariant(luid));
    
    if ( iChangeType != 1 )
    	map->InsertL(_L8("LocalIdList"), TLiwVariant(uidlist)); 

    uidlist->DecRef();
    
    TLiwVariant filterparam(map);
	TLiwGenericParam element ;	
	element.SetNameAndValueL(_L8("Filter"),filterparam);
	filterparam.Reset();
	
	inparam->AppendL(element);
	element.Reset();
    map->DecRef();
    CleanupStack::Pop(map);
	
	iCallback = CCalCallback::NewL(iWaitSchedular, iResult);

	iCallback->iChangeType = iChangeType;
	iCallback->iLocalUid = uids->iLocalUID;
	iCallback->iCheckLocalUid = iCheckLocalUid;
	iLocalUid = uids->iLocalUID;

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

	delete uids;
	inparam->Reset();
	outparam->Reset();
	}


TInt ReqNotification( TInt aChangeType, TBool aLocalUid  )
	{
	TInt32 result;
	
	__UHEAP_MARK;
	TInt cells = User::CountAllocCells();
	CTestAsync* test = CTestAsync::NewL();
	test->Start( aChangeType, aLocalUid );
	result = test->Result();
	test->CancelNotification();
	delete test;
	cells = User::CountAllocCells();
	__UHEAP_MARKEND;
	
	return result;
	}
	
/*TInt RemoveProvCalendar1(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar)
	{
	inparam->Reset();
	outparam->Reset();

   	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

    CLiwDefaultList* callist = CLiwDefaultList::NewL();
    CleanupStack::PushL(callist);
    
    TLiwVariant content(_L("Calendar"));
	TLiwGenericParam element1;	
	element1.SetNameAndValueL(_L8("Type"),content);
	inparam->AppendL(element1);
	content.Reset();
	element1.Reset();
    
    TLiwVariant smsmtm(aCalendar); 
    callist->AppendL(smsmtm);
    smsmtm.Reset();
    
    TLiwVariant add1(callist);
   // map->InsertL(_L8("CalendarList"), add1); 
    map->InsertL(_L8("CalendarName"), TLiwVariant(aCalendar) ); 
    callist->DecRef();
    CleanupStack::Pop(callist);
    add1.Reset();	
    
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
	
TInt AddProvCalendar1(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar)
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
	};*/
	
TInt GetLocalUid1( CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar,TCalLocalUid& aOutLocalUid )
	{
	TInt ret = 0;
	TInt pos = 0;
	aOutLocalUid = 0;
	
	inparam->Reset();
	outparam->Reset();			
					
	TLiwGenericParam dsNameParam(KContentType, TLiwVariant(_L("CalendarEntry")));
	inparam->AppendL(dsNameParam);
			
	CLiwDefaultMap* map1 = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map1);	

	map1->InsertL(_L8("CalendarName"), TLiwVariant(aCalendar) ); 
	map1->InsertL(_L8("id"),TLiwVariant(globalid));			
			
	TLiwVariant filterparam1(map1);
	TLiwGenericParam element2 ;	
	element2.SetNameAndValueL(_L8("Filter"),filterparam1);
	filterparam1.Reset();
			
	inparam->AppendL(element2);
	element2.Reset();			
			
	map1->DecRef();
	CleanupStack::Pop(map1);		    
		    
	interface->ExecuteCmdL( KCmdGetList ,*inparam ,*outparam);
	
	const TLiwGenericParam* getlist_err = outparam->FindFirst(pos,KErrorCode);
   	if(getlist_err)
   		ret = getlist_err->Value().AsTInt32();			
   	pos=0;
	const TLiwGenericParam* output = outparam->FindFirst( pos,_L8("ReturnValue"));
	TInt item_found = 0;
			
	if(!ret && output )     
	{
		CLiwIterable* iterlist = output->Value().AsIterable();
    	TLiwVariant data;	    	      
		while( iterlist->NextL(data))
		{
			const CLiwMap* res = data.AsMap();
			if ( res )
			{											
				TLiwVariant new_data;
				if(res->FindL(_L8("LocalId"), new_data))
				{
					TPtrC temp;
					temp.Set(new_data.AsDes()); 
					TBuf<40> buf;
					buf.Copy(temp);
				//	iLog->Log(_L("Local uid"));
				//	iLog->Log(buf);		
					TLex lex(temp);
					TInt32 num;
					if(lex.Val(num) == KErrNone)
						aOutLocalUid = TCalLocalUid(num);									
				}
				else
					ret = KErrGeneral;
				
				new_data.Reset();
			}
		}			  		
		data.Reset();	 		 
	}	
		
	inparam->Reset();
	outparam->Reset();	
	return ret;	
	}
	

//TInt AddProvAppointmentDailyRepeat1(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUint& localuid)
/*TInt AddProvAppointmentDailyRepeat1(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset)
	{
	inparam->Reset();
	outparam->Reset();
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
				TPtrC uidval = (TPtrC)(output->Value().AsDes());
				//GetLocalUid1( uidval, localuid );				
				uidset->iGlobalUID = HBufC8::NewL(uidval.Length());
				TPtr8 tmp = uidset->iGlobalUID->Des();
				tmp.Copy(uidval);
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
	};*/
		