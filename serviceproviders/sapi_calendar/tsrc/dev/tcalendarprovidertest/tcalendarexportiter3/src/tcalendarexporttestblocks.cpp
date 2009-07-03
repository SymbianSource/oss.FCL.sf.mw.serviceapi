/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:   ?Description
*
*/




// INCLUDE FILES
#include <e32svr.h>
#include <StifParser.h>
//#include <SAPI_TEST\testprg.h>
#include <Stiftestinterface.h>

#include <badesca.h>

#include<LiwServiceHandler.h>

#include "tcalendarexporttest.h"
#include "teststartconsolealarmserver2.h"
TDesC& GetEntry(MLiwInterface* interface, CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, TPtrC globaluid, const TDesC& calname);
_LIT(KCalNameExportTestDirect, "ExportTothisatProvider");
TInt AddProvAppointmentDailyRepeat(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset);

class CCalCallback : public MLiwNotifyCallback
	{
	public:
		
		static CCalCallback* NewL(CActiveSchedulerWait* aWaitSchedular, TInt& aResult );
		
		virtual ~CCalCallback(){}
		
		TInt HandleNotifyL(TInt aCmdId,
	            TInt aEventId,
	            CLiwGenericParamList& aEventParamList,
	            const CLiwGenericParamList& aInParamList);
		TInt			iEntryAdded;
		
	private:
	
 		CCalCallback(CActiveSchedulerWait* aWaitSchedular, TInt& aResult ):iWaitSchedular(aWaitSchedular), iResult(aResult){ }

		CActiveSchedulerWait* 	iWaitSchedular;
		TInt& 			iResult;
		
			
	};

class CTestAsync : public CActive
{
public:
	static CTestAsync* NewL();
	~CTestAsync();
	void Start(TInt flag, TInt option, TBool aICalFormat = EFalse, TBool aAsync = EFalse, TBool aPosBased = EFalse, TBool aInvalidFormat = EFalse);
	void CancelNotification();
	
	TInt Result();
	
private:
	void ConstructL();
	CTestAsync();
	
	virtual void DoCancel();
	virtual void RunL();
	
	void TestFunc();

	
private:	
	CLiwServiceHandler* 	iServiceHandler;
	CActiveSchedulerWait* 	iWaitSchedular;
	TInt 					iResult;
	TInt 					iEntryAdded;	
	CCalCallback*			iCallback;
	MLiwInterface* 			interface;
	TInt32 					iTransactionId;
	TBool					iICalFormat;
	TBool					iAsync;		
	TInt 					iOption;
	TInt                    iFunc; 
	TBool                   iPosBased;
	TBool                   iInvalidFormat;
};

_LIT8(KTestInterface, 	"IDataSource");
_LIT8(KTestContent,		"Service.Calendar");
_LIT8(KCmd,				"RequestNotification");


_LIT(KEntryTypeMeeting,	"Meeting");
_LIT(KCalTestImportSync1, "C:CalendarExportFile1");
_LIT(KCalTestImportSync2, "C:CalendarExportFile2");

TInt RemoveProvCalendar(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar);
TInt AddProvCalendar(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar);
TInt AddProvAppointmentDailyRepeat(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUint& localuid);

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTChangeStatusTest::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTCalendarExportTest::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CTChangeStatusTest::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTCalendarExportTest::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        //TRY( "SendMessage",    CTDeleteMessageTest::SendMessage ),
        
        ENTRY( "ExportAllProviderIter3",    	 	CTCalendarExportTest::ExportAll ),
        ENTRY( "ExportProviderIter3InvalidFormat",  CTCalendarExportTest::ExportProviderIter3InvalidFormat ),
        ENTRY( "ExportAllProviderIter3PosBased",    CTCalendarExportTest::ExportAllPosBased ),
		ENTRY( "ExportAllAsyncProviderIter3",    	CTCalendarExportTest::ExportAllAsync ),
		ENTRY( "ExportForGuidsProviderIter3",    	CTCalendarExportTest::ExportForGuids ),
		ENTRY( "ExportForGuidsAsyncProviderIter3",  CTCalendarExportTest::ExportForGuidsAsync ),
		ENTRY( "ExportForLuidsProviderIter3",    	CTCalendarExportTest::ExportForLuids ),
		ENTRY( "ExportForLuidsAsyncProviderIter3",  CTCalendarExportTest::ExportForLuidsAsync ),
		ENTRY( "ICALExportProviderIter3",     		CTCalendarExportTest::ICALExport ),
		ENTRY( "ICALExportAsyncProviderIter3",		CTCalendarExportTest::ICALExportAsync ),
        ENTRY( "ExportAllProviderFileIter3",    	 	CTCalendarExportTest::ExportAllFile ),
		ENTRY( "ExportAllAsyncProviderFileIter3",    	CTCalendarExportTest::ExportAllAsyncFile ),
		ENTRY( "ExportForGuidsProviderFileIter3",    	CTCalendarExportTest::ExportForGuidsFile ),
		ENTRY( "ExportForGuidsAsyncProviderFileIter3",  CTCalendarExportTest::ExportForGuidsAsyncFile ),
		ENTRY( "ExportForLuidsProviderFileIter3",    	CTCalendarExportTest::ExportForLuidsFile ),
		ENTRY( "ExportForLuidsAsyncProviderFileIter3",  CTCalendarExportTest::ExportForLuidsAsyncFile ),
		ENTRY( "ICALExportProviderFileIter3",     		CTCalendarExportTest::ICALExportFile ),
		ENTRY( "ICALExportAsyncProviderFileIter3",		CTCalendarExportTest::ICALExportAsyncFile ),        
		
		};

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }
	
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
		
		TInt returnItems = 0;

      	if(iterlist)
      		{
		    TLiwVariant data;

      		while ( iterlist->NextL(data) )
      			returnItems++;	
      		
      		data.Reset();  
      		}
      		
      	if(iEntryAdded == returnItems)	
      		iResult = KErrNone;
      	else
      		iResult = KErrGeneral;
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
		iResult = KErrGeneral;
		}

void CTestAsync::DoCancel()
	{

	}

void CTestAsync::RunL()
	{
	TestFunc();
	}

TInt CTestAsync::Result()
	{
	return iResult;
	}

void CTestAsync::Start(TInt flag, TInt option, TBool aICalFormat, TBool aAsync, TBool aPosBased, TBool aInvalidFormat)
	{
	iICalFormat = aICalFormat;
	iAsync = aAsync;
	iOption = flag;
	iFunc = option;
	iPosBased = aPosBased;
	iInvalidFormat = aInvalidFormat;
	if( iAsync )
		{
		SetActive();
		TRequestStatus* temp = &iStatus;
		User::RequestComplete(temp, KErrNone);
		iWaitSchedular->Start();	
		}
	else
		{
		TestFunc();
		}
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
	
TInt  CTCalendarExportTest::ExportAll(CStifItemParser& /*aItem*/)
	{	
	TInt result=KErrNone;
	
	if( result == KErrNone )
		{
		__UHEAP_MARK;	
		CTestAsync* test = CTestAsync::NewL();
		int flag = 0;
		int option = 1;
		test->Start(flag, option, EFalse );
		result = test->Result();
		delete test;
		__UHEAP_MARKEND;
		}
	return result;
    }

TInt  CTCalendarExportTest::ExportProviderIter3InvalidFormat(CStifItemParser& /*aItem*/)
	{	
	TInt result=KErrNone;
	
		{
		__UHEAP_MARK;	
		CTestAsync* test = CTestAsync::NewL();
		int flag = 1;
		int option = 1;
		test->Start(flag, option, EFalse, EFalse, EFalse, ETrue );
		result = test->Result();
		if(result == 1004)
			result = KErrNone;
		delete test;
		__UHEAP_MARKEND;
		}

	return result;
    }


   
TInt  CTCalendarExportTest::ExportAllPosBased(CStifItemParser& /*aItem*/)
	{	
	TInt result=KErrNone;
	
	if( result == KErrNone )
		{
		__UHEAP_MARK;	
		CTestAsync* test = CTestAsync::NewL();
		int flag = 0;
		int option = 1;
		test->Start(flag, option, EFalse, EFalse, ETrue);
		result = test->Result();
		delete test;
		__UHEAP_MARKEND;
		}
	return result;
    }

TInt  CTCalendarExportTest::ExportAllAsync(CStifItemParser& /*aItem*/)
	{	
	TInt result=KErrNone;
	
	if( result == KErrNone )
		{
		__UHEAP_MARK;	
		CTestAsync* test = CTestAsync::NewL();
		int flag = 0;
		int option = 1;
    	test->Start(flag, option, EFalse, ETrue);
		result = test->Result();
		delete test;
		__UHEAP_MARKEND;
		}
	return result;
    }
    
TInt  CTCalendarExportTest::ExportForGuids(CStifItemParser& /*aItem*/)
	{	
	TInt result=KErrNone;
	
	if( result == KErrNone )
		{
		__UHEAP_MARK;	
		CTestAsync* test = CTestAsync::NewL();
		int flag = 0;
		int option = 2;
		test->Start(flag, option, EFalse);
		result = test->Result();
		delete test;
		__UHEAP_MARKEND;
		}
	return result;
    }
    
TInt  CTCalendarExportTest::ExportForGuidsAsync(CStifItemParser& /*aItem*/)
	{	
	TInt result=KErrNone;
	
	if( result == KErrNone )
		{
		__UHEAP_MARK;	
		CTestAsync* test = CTestAsync::NewL();
		int flag = 0;
		int option = 2;
		test->Start(flag,option,EFalse, ETrue);
		result = test->Result();
		delete test;
		__UHEAP_MARKEND;
		}
	return result;
    }

TInt  CTCalendarExportTest::ExportForLuids(CStifItemParser& /*aItem*/)
	{	
	TInt result=KErrNone;
	
	if( result == KErrNone )
		{
		__UHEAP_MARK;	
		CTestAsync* test = CTestAsync::NewL();
		int flag = 0;
		int option = 3;
		test->Start(flag, option,EFalse);
		result = test->Result();
		delete test;
		__UHEAP_MARKEND;
		}
	return result;
    }    
    
TInt  CTCalendarExportTest::ExportForLuidsAsync(CStifItemParser& /*aItem*/)
	{	
	TInt result=KErrNone;
	
	if( result == KErrNone )
		{
		__UHEAP_MARK;	
		CTestAsync* test = CTestAsync::NewL();
		int flag = 0;
		int option = 3;
		test->Start(flag, option,EFalse, ETrue);
		result = test->Result();
		delete test;
		__UHEAP_MARKEND;
		}
	return result;
    }    
    
TInt  CTCalendarExportTest::ICALExport(CStifItemParser& /*aItem*/)
	{	
	TInt result=KErrNone;
	
	if( result == KErrNone )
		{
		__UHEAP_MARK;	
		CTestAsync* test = CTestAsync::NewL();
		int flag = 0;
		int option =1;
		test->Start(flag,option, ETrue);
		result = test->Result();
		delete test;
		__UHEAP_MARKEND;
		}
	return result;
    }    
	void Start(TInt flag, TInt option, TBool aICalFormat = EFalse, TBool aAsync = EFalse);
TInt  CTCalendarExportTest::ICALExportAsync(CStifItemParser& /*aItem*/)
	{	
	TInt result=KErrNone;
	
	if( result == KErrNone )
		{
		__UHEAP_MARK;	
		CTestAsync* test = CTestAsync::NewL();
		int flag = 0;
		int option = 1;
		test->Start(flag,option, ETrue, ETrue);
		result = test->Result();
		delete test;
		__UHEAP_MARKEND;
		}
	return result;
    }    
TInt  CTCalendarExportTest::ExportAllFile(CStifItemParser& /*aItem*/)
	{	
	TInt result=KErrNone;
	
	if( result == KErrNone )
		{
		__UHEAP_MARK;	
		CTestAsync* test = CTestAsync::NewL();
		int flag = 0;
		int option =1;
		test->Start(flag,option);
		result = test->Result();
		delete test;
		__UHEAP_MARKEND;
		}
	return result;
    }    
    
TInt  CTCalendarExportTest::ExportAllAsyncFile(CStifItemParser& /*aItem*/)
	{	
	TInt result=KErrNone;
	
	if( result == KErrNone )
		{
		__UHEAP_MARK;	
		CTestAsync* test = CTestAsync::NewL();
		int flag = 1;
		int option =1;
		test->Start(flag,option, EFalse, ETrue);
		result = test->Result();
		delete test;
		__UHEAP_MARKEND;
		}
	return result;
    }    
    
TInt  CTCalendarExportTest::ExportForGuidsFile(CStifItemParser& /*aItem*/)
	{	
	TInt result=KErrNone;
	
	if( result == KErrNone )
		{
		__UHEAP_MARK;	
		CTestAsync* test = CTestAsync::NewL();
		int flag = 1;
		int option =2;
		test->Start(flag,option);
		result = test->Result();
		delete test;
		__UHEAP_MARKEND;
		}
	return result;
    }    
    
TInt  CTCalendarExportTest::ExportForGuidsAsyncFile(CStifItemParser& /*aItem*/)
	{	
	TInt result=KErrNone;
	
	if( result == KErrNone )
		{
		__UHEAP_MARK;	
		CTestAsync* test = CTestAsync::NewL();
		int flag = 1;
		int option =2;
		test->Start(flag,option, EFalse, ETrue);
		result = test->Result();
		delete test;
		__UHEAP_MARKEND;
		}
	return result;
    }    
    
TInt  CTCalendarExportTest::ExportForLuidsFile(CStifItemParser& /*aItem*/)
	{	
	TInt result=KErrNone;
	
	if( result == KErrNone )
		{
		__UHEAP_MARK;	
		CTestAsync* test = CTestAsync::NewL();
		int flag = 1;
		int option =3;
		test->Start(flag,option);
		result = test->Result();
		delete test;
		__UHEAP_MARKEND;
		}
	return result;
    }    
    
TInt  CTCalendarExportTest::ExportForLuidsAsyncFile(CStifItemParser& /*aItem*/)
	{	
	TInt result=KErrNone;
	
	if( result == KErrNone )
		{
		__UHEAP_MARK;	
		CTestAsync* test = CTestAsync::NewL();
		int flag = 1;
		int option =3;
		test->Start(flag,option, EFalse, ETrue);
		result = test->Result();
		delete test;
		__UHEAP_MARKEND;
		}
	return result;
    }    
    
TInt  CTCalendarExportTest::ICALExportFile(CStifItemParser& /*aItem*/)
	{	
	TInt result=KErrNone;
	
	if( result == KErrNone )
		{
		__UHEAP_MARK;	
		CTestAsync* test = CTestAsync::NewL();
		int flag = 1;
		int option =1;
		test->Start(flag,option, ETrue);
		result = test->Result();
		delete test;
		__UHEAP_MARKEND;
		}
	return result;
    }    
    
TInt  CTCalendarExportTest::ICALExportAsyncFile(CStifItemParser& /*aItem*/)
	{	
	TInt result=KErrNone;
	
	if( result == KErrNone )
		{
		__UHEAP_MARK;	
		CTestAsync* test = CTestAsync::NewL();
		int flag = 1;
		int option =1;
		test->Start(flag,option, ETrue, ETrue);
		result = test->Result();
		delete test;
		__UHEAP_MARKEND;
		}
	return result;
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
	
	
	RemoveProvCalendar(inparam, outparam, interface, KCalTestImportSync1);
	RemoveProvCalendar(inparam, outparam, interface, KCalTestImportSync2);
	
	if( AddProvCalendar(inparam, outparam, interface, KCalTestImportSync1) != KErrNone)
		{
		if(iWaitSchedular->IsStarted())
			iWaitSchedular->AsyncStop();
		inparam->Reset();
		outparam->Reset();
		return;
		};

	if( AddProvCalendar(inparam, outparam, interface, KCalTestImportSync2) != KErrNone)
		{
		if(iWaitSchedular->IsStarted())
			iWaitSchedular->AsyncStop();
		inparam->Reset();
		outparam->Reset();
		return;
		};
	
	
	TUint localUid;
	TInt entryAdded = 0;
	TUIDSet* uidset1;
	TUIDSet* uidset2;
	if( AddProvAppointmentDailyRepeat(inparam, outparam, interface, KCalTestImportSync1 ,uidset1) != KErrNone )
		{
		if(iWaitSchedular->IsStarted())
			iWaitSchedular->AsyncStop();
		inparam->Reset();
		outparam->Reset();
		iResult = KErrGeneral;
		delete uidset1;
		return;
		};
	iEntryAdded++;	
	
	inparam->Reset();
	outparam->Reset();

	if( AddProvAppointmentDailyRepeat(inparam, outparam, interface, KCalTestImportSync1, uidset2 ) != KErrNone )
		{
		if(iWaitSchedular->IsStarted())
			iWaitSchedular->AsyncStop();
		inparam->Reset();
		outparam->Reset();
		iResult = KErrGeneral;
		delete uidset2;
		return;
		};
	iEntryAdded++;	
	
	inparam->Reset();
	outparam->Reset();

   	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

	TLiwGenericParam element1;	
	
	if ( iPosBased )
		element1.SetNameAndValueL(KNullDesC8,TLiwVariant(_L("CalendarEntry")));
	else
		element1.SetNameAndValueL(_L8("Type"),TLiwVariant(_L("CalendarEntry")));
	
  
    map->InsertL(_L8("CalendarName"), TLiwVariant(KCalTestImportSync1) );

	if(iInvalidFormat)
		map->InsertL(_L8("Format"), TLiwVariant(_L("InvalidFormat")) ); 
    else if(iICalFormat) 
    	map->InsertL(_L8("Format"), TLiwVariant(_L("ICal")) ); 
    else 
    	map->InsertL(_L8("Format"), TLiwVariant(_L("VCal")) ); 

    if( iOption == 1 )
	    {
	    map->InsertL(_L8("FileName"), TLiwVariant(_L("c:\\exportall.txt")));
	    }
    
    if( iFunc == 2 )
	    {
    	CLiwDefaultList *uidlist = CLiwDefaultList::NewL();
        TBuf<10> localuid;
        TBuf<50> globaluid;
	    globaluid.Copy(uidset1->iGlobalUID->Des());
	    localuid = GetEntry( interface, inparam, outparam, globaluid, KCalTestImportSync1);

    	//localuid.Num(TInt64(uidset1->iLocalUID));
    	uidlist->AppendL(TLiwVariant(localuid));
	    globaluid.Copy(uidset2->iGlobalUID->Des());
	    localuid = GetEntry( interface, inparam, outparam, globaluid, KCalTestImportSync1);

    	//localuid.Num(TInt64(uidset2->iLocalUID));
        uidlist->AppendL(TLiwVariant(localuid));
		map->InsertL(_L8("LocalIdList"), TLiwVariant(uidlist));
		uidlist->DecRef();
		}
	    
    if( iFunc == 3 )
	    {
	    CLiwDefaultList *uidlist = CLiwDefaultList::NewL();
	    TBuf<50> guid;
	    guid.Copy(uidset1->iGlobalUID->Des());
	    uidlist->AppendL(TLiwVariant(guid));
	    guid.Copy(uidset2->iGlobalUID->Des());
	    uidlist->AppendL(TLiwVariant(guid));
		map->InsertL(_L8("IdList"), TLiwVariant(uidlist));
		uidlist->DecRef();
	    }

	inparam->AppendL(element1);
	element1.Reset();


    TLiwVariant filterparam(map);
	TLiwGenericParam element ;	
	
	if ( iPosBased )
		element.SetNameAndValueL(KNullDesC8,filterparam);
	else
		element.SetNameAndValueL(_L8("Data"),filterparam);
	
	filterparam.Reset();
	
	inparam->AppendL(element);
	element.Reset();
    map->DecRef();
    CleanupStack::Pop(map);

	TRAPD(err1, interface->ExecuteCmdL(KCmdExport, *inparam, *outparam ));
	
	pos = 0;
    const TLiwGenericParam* output = outparam->FindFirst( pos,_L8("ErrorCode"));
	
	HBufC8* exportBuffer = NULL;
	delete uidset1;
	delete uidset2;	
	
	if( iOption == 0)
		{
		if(output)
			{
			err = output->Value().AsTInt32();
			if(err == KErrNone)
				{
				pos = 0;
				output = outparam->FindFirst( pos,_L8("ReturnValue"));
				if ( output )
					{
					exportBuffer = output->Value().AsData().AllocL();
					}
				}
			else
				{
				if(iWaitSchedular->IsStarted())
					iWaitSchedular->AsyncStop();
				}	

			}
		inparam->Reset();
		outparam->Reset();
		
		if ( exportBuffer )
			{
		   	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
			CleanupStack::PushL(map);

			TLiwGenericParam element1;	
			element1.SetNameAndValueL(_L8("Type"),TLiwVariant(_L("CalendarEntry")));
			inparam->AppendL(element1);
			element1.Reset();
		    
		    map->InsertL(_L8("CalendarName"), TLiwVariant(KCalTestImportSync2) ); 

		    if(iICalFormat) 
		    	map->InsertL(_L8("Format"), TLiwVariant(_L("ICal")) ); 
		    else 
		    	map->InsertL(_L8("Format"), TLiwVariant(_L("VCal")) ); 

		    map->InsertL(_L8("Buffer"), TLiwVariant( exportBuffer->Des() ) ); 

		    TLiwVariant filterparam(map);
			TLiwGenericParam element ;	
			element.SetNameAndValueL(_L8("Data"),filterparam);
			filterparam.Reset();
			
			inparam->AppendL(element);
			element.Reset();
		    map->DecRef();
		    CleanupStack::Pop(map);
		    
		    if(iAsync)
		    	{
				iCallback = CCalCallback::NewL(iWaitSchedular, iResult);

				iCallback->iEntryAdded = iEntryAdded;

				TRAPD(err1, interface->ExecuteCmdL(KCmdImport, *inparam, *outparam, KLiwOptASyncronous, iCallback));
				
				pos = 0;
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
		    else
		    	{
				TRAPD(err1, interface->ExecuteCmdL(KCmdImport, *inparam, *outparam ));
				pos = 0;
			    const TLiwGenericParam* output = outparam->FindFirst( pos,_L8("ErrorCode"));

				if(output)
					{
					err = output->Value().AsTInt32();
					if(err == KErrNone)
						{
						pos = 0;
						output = outparam->FindFirst( pos,_L8("ReturnValue"));
						if ( output )
							{
							CLiwIterable* iterlist = output->Value().AsIterable();
							
							TInt returnItems = 0;

					      	if(iterlist)
					      		{
							    TLiwVariant data;

					      		while ( iterlist->NextL(data) )
					      			returnItems++;	
					      		
					      		data.Reset();  
					      		}
					      		
					      	if(iEntryAdded == returnItems)	
					      		iResult = KErrNone;
							}
						}
					else
						{
						iResult = err;	
						}

					}
		    	}	
			}
		delete exportBuffer;	
		}
	else
		{
		if(output)
			{
			err = output->Value().AsTInt32();
			inparam->Reset();
			outparam->Reset();
		
			if(err == KErrNone)
				{
			   	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
				CleanupStack::PushL(map);

				TLiwGenericParam element1;	
				element1.SetNameAndValueL(_L8("Type"),TLiwVariant(_L("CalendarEntry")));
				inparam->AppendL(element1);
				element1.Reset();
			    
			    map->InsertL(_L8("CalendarName"), TLiwVariant(KCalTestImportSync2) ); 

			    if(iICalFormat) 
			    	map->InsertL(_L8("Format"), TLiwVariant(_L("ICal")) ); 
			    else 
			    	map->InsertL(_L8("Format"), TLiwVariant(_L("VCal")) ); 

			    map->InsertL(_L8("FileName"), TLiwVariant( _L("c:\\exportall.txt") ) ); 

			    TLiwVariant filterparam(map);
				TLiwGenericParam element ;	
				element.SetNameAndValueL(_L8("Data"),filterparam);
				filterparam.Reset();
				
				inparam->AppendL(element);
				element.Reset();
			    map->DecRef();
			    CleanupStack::Pop(map);
			    if(iAsync)
			    	{
					iCallback = CCalCallback::NewL(iWaitSchedular, iResult);

					iCallback->iEntryAdded = iEntryAdded;

					TRAPD(err1, interface->ExecuteCmdL(KCmdImport, *inparam, *outparam, KLiwOptASyncronous, iCallback));
					
					pos = 0;
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
			    else
			    	{
					TRAPD(err1, interface->ExecuteCmdL(KCmdImport, *inparam, *outparam ));
					pos = 0;
				    const TLiwGenericParam* output = outparam->FindFirst( pos,_L8("ErrorCode"));

					if(output)
						{
						err = output->Value().AsTInt32();
						if(err == KErrNone)
							{
							pos = 0;
							output = outparam->FindFirst( pos,_L8("ReturnValue"));
							if ( output )
								{
								CLiwIterable* iterlist = output->Value().AsIterable();
								
								TInt returnItems = 0;

						      	if(iterlist)
						      		{
								    TLiwVariant data;

						      		while ( iterlist->NextL(data) )
						      			returnItems++;	
						      		
						      		data.Reset();  
						      		}
						      		
						      	if(iEntryAdded == returnItems)	
						      		iResult = KErrNone;
								}
							}
						else
							{
							iResult = err;	
							}
						}
		    		}	
				}
			else
				{
				iResult = err;
				if(iWaitSchedular->IsStarted())
					iWaitSchedular->AsyncStop();
				}	
			}
		}	
	inparam->Reset();
	outparam->Reset();
	}