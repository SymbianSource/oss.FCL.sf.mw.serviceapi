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
//#include "teststartconsolealarmserver3.h"
#include<LiwServiceHandler.h>


#include "tcalendarimporttest.h"
#include "startconsolealarmserver.h"

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
	void Start(TInt flag, TBool aICalFormat = EFalse, TBool aAsync = EFalse, TBool aWrong = EFalse, TBool aPosBased = EFalse, TBool aInvalidFormat = EFalse  );
	void CancelNotification();
	void ImportInvalidFile();
	
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
	TBool                   iWrongCal;
	TBool                   iPosBased;
	TBool                   iInvalidFormat;
};

_LIT8(KTestInterface, 	"IDataSource");
_LIT8(KTestContent,		"Service.Calendar");
_LIT8(KCmd,				"RequestNotification");
_LIT8(KCmdAdd,			"Add");
_LIT8(KCmdDelete,		"Delete");
_LIT8(KCmdCancel,		"Cancel");
_LIT8(KCmdExport,			"Export");
_LIT8(KCmdImport,			"Import");

_LIT8(KFilter,			"Filter");
_LIT8(KItem,			"Item");
_LIT8(KCalendarName,	"CalendarName");

_LIT(KEntryTypeMeeting,	"Meeting");

const TChar KUidSeparator = ':';

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
void CTCalendarImportTest::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CTChangeStatusTest::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTCalendarImportTest::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        //TRY( "SendMessage",    CTDeleteMessageTest::SendMessage ),
        
        ENTRY( "ImportProviderIter3",    	 CTCalendarImportTest::Import ),
        ENTRY( "ImportProviderIter3File",    	 CTCalendarImportTest::ImportProviderIter3File ),
        ENTRY( "ImportAsyncProviderIter3File",    	 CTCalendarImportTest::ImportAsyncProviderIter3File ),
		ENTRY( "ImportAsyncProviderIter3",    CTCalendarImportTest::ImportAsync ),
		ENTRY( "ICALImportProviderIter3",     CTCalendarImportTest::ICALImport ),
		ENTRY( "ICALImportAsyncProviderIter3",CTCalendarImportTest::ICALImportAsync ),
		ENTRY( "ICALImportProviderIter3File",     CTCalendarImportTest::ICALImportProviderIter3File ),
		ENTRY( "ICALImportAsyncProviderIter3File",CTCalendarImportTest::ICALImportAsyncProviderIter3File ),
		ENTRY( "ImportProviderIter3WrongCal",CTCalendarImportTest::ImportProviderIter3WrongCal ),
		ENTRY( "ImportProviderIter3PositionBased",CTCalendarImportTest::ImportProviderIter3PositionBased ),
		ENTRY( "ImportProviderIter3InvalidFile",CTCalendarImportTest::ImportProviderIter3InvalidFile ),
		ENTRY( "ImportProviderIter3InvalidFormat",CTCalendarImportTest::ImportProviderIter3InvalidFormat ),
        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

   
#include<LiwCommon.h>    

class CTestAsync;
	
// -----------------------------------------------------------------------------
// CTCalendarImportTest::Import
// Test Method to test the Import(Synchronous)
// Functionality of CalenderService
// -----------------------------------------------------------------------------
//
TInt  CTCalendarImportTest::Import(CStifItemParser& /*aItem*/)
	{
	TInt result=KErrNone;
	
		{
		__UHEAP_MARK;	
		CTestAsync* test = CTestAsync::NewL();
		TInt flag = 0;
		test->Start(flag);
		result = test->Result();
		delete test;
		__UHEAP_MARKEND;
		}

	return result;
    }

TInt  CTCalendarImportTest::ImportProviderIter3File(CStifItemParser& /*aItem*/)
	{
	TInt result=KErrNone;
	
		{
		__UHEAP_MARK;	
		CTestAsync* test = CTestAsync::NewL();
		TInt flag = 1;
		test->Start(flag);
		result = test->Result();
		delete test;
		__UHEAP_MARKEND;
		}

	return result;
    }
// -----------------------------------------------------------------------------
// CTCalendarImportTest::ImportAsync
// Test Method to test the ImportAsync(ASynchronous)
// Functionality of CalenderService
// -----------------------------------------------------------------------------
//
TInt  CTCalendarImportTest::ImportAsync(CStifItemParser& /*aItem*/)
	{	
	TInt result=KErrNone;
	
		{
		__UHEAP_MARK;	
		CTestAsync* test = CTestAsync::NewL();
		int flag = 0;
		test->Start(flag, EFalse, ETrue);
		result = test->Result();
		delete test;
		__UHEAP_MARKEND;
		}

	return result;
    }

TInt  CTCalendarImportTest::ImportAsyncProviderIter3File(CStifItemParser& /*aItem*/)
	{
	TInt result=KErrNone;
	
		{
		__UHEAP_MARK;	
		CTestAsync* test = CTestAsync::NewL();
		TInt flag = 1;
		test->Start(flag, EFalse, ETrue);
		result = test->Result();
		delete test;
		__UHEAP_MARKEND;
		}

	return result;
    }
// -----------------------------------------------------------------------------
// CTCalendarImportTest::ICALImport
// Test Method to test the ICALImport(Synchronous)
// Functionality of CalenderService
// -----------------------------------------------------------------------------
//
TInt  CTCalendarImportTest::ICALImport(CStifItemParser& /*aItem*/)
	{
	TInt result=KErrNone;
	
		{
		__UHEAP_MARK;	
		CTestAsync* test = CTestAsync::NewL();
		int flag = 0;
		test->Start( flag , ETrue );
		result = test->Result();
		delete test;
		__UHEAP_MARKEND;
		}

	return result;
    }

TInt  CTCalendarImportTest::ICALImportProviderIter3File(CStifItemParser& /*aItem*/)
	{
	TInt result=KErrNone;
	
		{
		__UHEAP_MARK;
		int flag = 1;	
		CTestAsync* test = CTestAsync::NewL();
		test->Start( flag , ETrue );
		result = test->Result();
		delete test;
		__UHEAP_MARKEND;
		}

	return result;
    }


// -----------------------------------------------------------------------------
// CTCalendarImportTest::ICALImportAsync
// Test Method to test the ICALImportAsync(ASynchronous)
// Functionality of CalenderService
// -----------------------------------------------------------------------------
//
TInt  CTCalendarImportTest::ICALImportAsync(CStifItemParser& /*aItem*/)
	{
	TInt result=KErrNone;
	
		{
		__UHEAP_MARK;	
		CTestAsync* test = CTestAsync::NewL();
		int flag = 0;
		test->Start( flag, ETrue, ETrue );
		result = test->Result();
		delete test;
		__UHEAP_MARKEND;
		}

	return result;
    }
 
TInt  CTCalendarImportTest::ICALImportAsyncProviderIter3File(CStifItemParser& /*aItem*/)
	{
	TInt result=KErrNone;

		{
		__UHEAP_MARK;	
		CTestAsync* test = CTestAsync::NewL();
		int flag = 1;
		test->Start( flag, ETrue, ETrue );
		result = test->Result();
		delete test;
		__UHEAP_MARKEND;
		}

	return result;
	}

TInt  CTCalendarImportTest::ImportProviderIter3WrongCal(CStifItemParser& /*aItem*/)
	{
	TInt result=KErrNone;

		{
		__UHEAP_MARK;	
		CTestAsync* test = CTestAsync::NewL();
		int flag = 0;
		test->Start( flag, EFalse, EFalse, ETrue );
		result = test->Result();
		if(result > 0 )
			result = KErrNone;
		delete test;
		__UHEAP_MARKEND;
		}

	return result;
	}
	
TInt CTCalendarImportTest::ImportProviderIter3PositionBased(CStifItemParser& /*aItem*/ )
	{
	TInt result=KErrNone;

		{
		__UHEAP_MARK;	
		CTestAsync* test = CTestAsync::NewL();
		int flag = 0;
		test->Start( flag, EFalse, EFalse, EFalse, ETrue );
		result = test->Result();
		delete test;
		__UHEAP_MARKEND;
		}
	return result;
	}
	
TInt CTCalendarImportTest::ImportProviderIter3InvalidFile(CStifItemParser& /*aItem*/ )
	{
	TInt result=KErrNone;

		{
		__UHEAP_MARK;	
		CTestAsync* test = CTestAsync::NewL();
		int flag = 0;
		test->ImportInvalidFile();
		result = test->Result();
		delete test;
		__UHEAP_MARKEND;
		}

	return result;
	}
	
TInt CTCalendarImportTest::ImportProviderIter3InvalidFormat(CStifItemParser& /*aItem*/ )
	{
	TInt result=KErrNone;

		{
		__UHEAP_MARK;	
		CTestAsync* test = CTestAsync::NewL();
		int flag = 0;
		test->Start( flag, EFalse, EFalse, EFalse, EFalse, ETrue );
		result = test->Result();
		if(result == 1004 )
			result = KErrNone;
		else if(result == KErrNone)
			result = KErrGeneral;
		
		delete test;
		__UHEAP_MARKEND;
		}

	return result;
	}
	


/*TInt  CTCalendarImportTest::ImportInvalidParamTest(CStifItemParser& aItem)
	{
	
	}*/
	
_LIT(KCalTestImportSync1, "c:importsynctestcal1");
_LIT(KCalTestImportSync2, "c:importsynctestcal2");
	
	
/**
 * Callback class for asynchronous SAPI message header
*/	
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

void CTestAsync::Start(TInt flag, TBool aICalFormat, TBool aAsync, TBool aWrongCal, TBool aPosBased, TBool aInvalidFormat )
	{
	iICalFormat = aICalFormat;
	iAsync = aAsync;
	iOption = flag;
	iWrongCal = aWrongCal;
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

	if(!iWrongCal)
		{
		if( AddProvCalendar(inparam, outparam, interface, KCalTestImportSync2) != KErrNone)
			{
			if(iWaitSchedular->IsStarted())
				iWaitSchedular->AsyncStop();
			inparam->Reset();
			outparam->Reset();
			return;
			};
		}
	
	
	TUint localUid;
	TInt entryAdded = 0;
	if( AddProvAppointmentDailyRepeat(inparam, outparam, interface, KCalTestImportSync1, localUid ) != KErrNone )
		{
		if(iWaitSchedular->IsStarted())
			iWaitSchedular->AsyncStop();
		inparam->Reset();
		outparam->Reset();
		return;
		};
	iEntryAdded++;	
	
	inparam->Reset();
	outparam->Reset();

	if( AddProvAppointmentDailyRepeat(inparam, outparam, interface, KCalTestImportSync1, localUid ) != KErrNone )
		{
		if(iWaitSchedular->IsStarted())
			iWaitSchedular->AsyncStop();
		inparam->Reset();
		outparam->Reset();
		return;
		};
	iEntryAdded++;	
	
	inparam->Reset();
	outparam->Reset();

   	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

	TLiwGenericParam element1;	
	element1.SetNameAndValueL(_L8("Type"),TLiwVariant(_L("CalendarEntry")));
	inparam->AppendL(element1);
	element1.Reset();
    
    map->InsertL(_L8("CalendarName"), TLiwVariant(KCalTestImportSync1) );

    if(iICalFormat) 
    	map->InsertL(_L8("Format"), TLiwVariant(_L("ICal")) ); 
    else 
    	map->InsertL(_L8("Format"), TLiwVariant(_L("VCal")) ); 

    if( iOption == 1 )
	    {
	    map->InsertL(_L8("FileName"), TLiwVariant(_L("c:\\exportall.txt")));
	    }

    TLiwVariant filterparam(map);
	TLiwGenericParam element ;	
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

			if(iPosBased)
				element1.SetNameAndValueL( KNullDesC8, TLiwVariant(_L("CalendarEntry")));
			else
				element1.SetNameAndValueL( _L8("Type"),TLiwVariant(_L("CalendarEntry")));
		

			inparam->AppendL(element1);
			element1.Reset();
		    
		    map->InsertL(_L8("CalendarName"), TLiwVariant(KCalTestImportSync2) ); 

			if(iInvalidFormat)
				map->InsertL(_L8("Format"), TLiwVariant(_L("InvalidFormat")) ); 
		    else if(iICalFormat) 
		    	map->InsertL(_L8("Format"), TLiwVariant(_L("ICal")) ); 
		    else 
		    	map->InsertL(_L8("Format"), TLiwVariant(_L("VCal")) ); 

		    map->InsertL(_L8("Buffer"), TLiwVariant( exportBuffer->Des() ) ); 

		    TLiwVariant filterparam(map);
			TLiwGenericParam element ;	

			if(iPosBased)
				element.SetNameAndValueL( KNullDesC8, filterparam );
			else
				element.SetNameAndValueL( _L8("Data"), filterparam);
			
			
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
				if(iWaitSchedular->IsStarted())
					iWaitSchedular->AsyncStop();
				}	
			}
		}	
	inparam->Reset();
	outparam->Reset();
	}

void CTestAsync::ImportInvalidFile()
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
	
	if( AddProvCalendar(inparam, outparam, interface, KCalTestImportSync1) != KErrNone)
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
	element1.SetNameAndValueL(_L8("Type"),TLiwVariant(_L("CalendarEntry")));
	inparam->AppendL(element1);
	element1.Reset();
    
    map->InsertL(_L8("CalendarName"), TLiwVariant(KCalTestImportSync1) );

    if(iICalFormat) 
    	map->InsertL(_L8("Format"), TLiwVariant(_L("ICal")) ); 
    else 
    	map->InsertL(_L8("Format"), TLiwVariant(_L("VCal")) ); 

    map->InsertL(_L8("FileName"), TLiwVariant(_L("c:\\importfrominvalid.txt")));
	 

    TLiwVariant filterparam(map);
	TLiwGenericParam element ;	
	element.SetNameAndValueL(_L8("Data"),filterparam);
	filterparam.Reset();
	
	inparam->AppendL(element);
	element.Reset();
    map->DecRef();
    CleanupStack::Pop(map);


	TRAPD(err1, interface->ExecuteCmdL(KCmdImport, *inparam, *outparam ));
	pos = 0;

    const TLiwGenericParam* output = outparam->FindFirst( pos,_L8("ErrorCode"));

	if(output)
		{
		err = output->Value().AsTInt32();
		if(err == 1012)
			{
			iResult = KErrNone;
			}
		else
			{
			iResult = err;	
			}
		}
	else
		{
		iResult = err1;
		}	

	RemoveProvCalendar(inparam, outparam, interface, KCalTestImportSync1);

	inparam->Reset();
	outparam->Reset();
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
	
void GetLocalUid( const TDesC& aLocalUid, TUint& aOutLocalUid )
	{
	aOutLocalUid = 0;
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
			aOutLocalUid = TUint(num);
		}
	}

TInt AddProvAppointmentDailyRepeat(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUint& localuid)
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
			pos = 0;
			output = outparam->FindFirst( pos,_L8("ReturnValue"));
			if(output)
				{
				TPtrC uidval = (TPtrC)(output->Value().AsDes());
				GetLocalUid( uidval, localuid );
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