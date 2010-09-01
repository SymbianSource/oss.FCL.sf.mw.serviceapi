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
#include "deleteguid.h"
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

_LIT8(KDeleteAll,"DeleteAll");
_LIT(KCalFileName1,"C:CalendarFileA");
_LIT8(KCalendarName,"CalendarName");

TInt AddProvCalendar(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar);
TInt RemoveProvCalendar(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar);
TInt AddProvToDo(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset);
TInt AddProvDayEvent(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset);
TInt AddProvAnni(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset);
TInt AddProvAppointmentDailyRepeat(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar,TUIDSet*& uidset);


CCalCallbackGuid* CCalCallbackGuid::NewL(CActiveSchedulerWait* aWaitSchedular, MLiwInterface* aInterface, TInt& aError, TInt& aFlag)
	{
	return new (ELeave) CCalCallbackGuid(aWaitSchedular, aInterface, aError, aFlag);
	}
		
TInt CCalCallbackGuid::HandleNotifyL(TInt aCmdId,
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
		if( iOption == 0 )
			{
			if(count != 0)
				errCode = KErrGeneral;	
			}
		if( iOption == 1 )
			{
			if(count != 7)
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



CTestAsyncGuid* CTestAsyncGuid::NewL()
	{
	CTestAsyncGuid* self = new (ELeave) CTestAsyncGuid();
	self->ConstructL();
	return self;
	}

CTestAsyncGuid::~CTestAsyncGuid()
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


void CTestAsyncGuid::ConstructL()
	{
	CActiveScheduler::Add(this);
	iWaitSchedular = new(ELeave) CActiveSchedulerWait();
	}


CTestAsyncGuid::CTestAsyncGuid() :
CActive(EPriorityStandard)
	{
	interface = NULL ;
	}

void CTestAsyncGuid::DoCancel()
	{

	}

void CTestAsyncGuid::RunL()
	{

	TestFunc();

	}


int CTestAsyncGuid::Start(int aFlag, TBool async)
	{
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iFlag = aFlag;
	iAsync = async;
	iWaitSchedular->Start();
	return iError;	
	}


void CTestAsyncGuid::TestFunc()
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
	TUIDSet* uidset1;
	TUIDSet* uidset2;
	TUIDSet* uidset3;
	
	//RPointerArray<TUIDSet> arruids(5);

    AddProvToDo(inparam, outparam, interface, KCalFileName1 ,uidset1);
        
    AddProvDayEvent(inparam, outparam, interface, KCalFileName1 ,uidset2)	;
    
    AddProvAppointmentDailyRepeat(inparam, outparam, interface, KCalFileName1 ,uidset3 );
        
	TLiwVariant dsName;
	dsName.Set(_L("CalendarEntry"));
    TLiwGenericParam dsNameParam(KContentType, dsName);
	inparam->AppendL(dsNameParam);
	dsName.Reset();

	CLiwDefaultMap *filterMap = CLiwDefaultMap::NewL();
	TLiwGenericParam filterParam(KData, TLiwVariant(filterMap));
	inparam->AppendL(filterParam);

    CLiwDefaultList *uidlist = CLiwDefaultList::NewL();
    TBuf<50> guid;
    guid.Copy(uidset1->iGlobalUID->Des());
    uidlist->AppendL(TLiwVariant(guid));
    guid.Copy(uidset2->iGlobalUID->Des());
    uidlist->AppendL(TLiwVariant(guid));
    guid.Copy(uidset3->iGlobalUID->Des());
    uidlist->AppendL(TLiwVariant(guid));
    
	TLiwVariant calname;
	TPtrC filename(_L("C:CalendarFileA"));
    calname.Set(filename);

    filterMap->InsertL(KCalendarName,calname);
	filterMap->InsertL(_L8("IdList"), TLiwVariant(uidlist));
	
	if( iFlag == 1 )
		{
    	filterMap->InsertL(_L8("StartRange"), TLiwVariant(TTime(TDateTime(2007,EJuly,20,0,0,0,0))));
		filterMap->InsertL(_L8("EndRange"), TLiwVariant(TTime(TDateTime(2007,EOctober,24,0,0,0,0))));
		}
		
	uidlist->DecRef();
	filterMap->DecRef();
	if(iAsync)
		{
		iCallback = CCalCallbackGuid::NewL(iWaitSchedular, interface, iError, iFlag);

		TRAPD(err1 ,interface->ExecuteCmdL(KCmd, *inparam, *outparam, KLiwOptASyncronous, iCallback));
		inparam->Reset();
		outparam->Reset();
		}
	else
		{
		TRAPD(err1 ,interface->ExecuteCmdL(KCmd, *inparam, *outparam));
		const TLiwGenericParam* p = outparam->FindFirst(pos, KErrorCode); // Finding Error Code
        TInt errCode = 0;
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
			if(iFlag==0)
				{
				if(count != 0)
					errCode = KErrGeneral;	
				}
			else if(iFlag==1)
				{
				if(count != 7)
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
		}			
	delete uidset1;
	delete uidset2;
	delete uidset3;
	calname.Reset();
	}


int DeleteGuidAsync(int flag, TBool async)
	{
    __UHEAP_MARK;
	CTestAsyncGuid* test = CTestAsyncGuid::NewL();
	int res = test->Start(flag, async);
	delete test;
    __UHEAP_MARKEND;
	return res;


	
	}

