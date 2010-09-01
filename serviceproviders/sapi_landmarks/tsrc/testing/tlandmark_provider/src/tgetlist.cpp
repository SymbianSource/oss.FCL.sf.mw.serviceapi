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



#include <e32std.h>
#include <StifTestInterface.h>
#include <liwservicehandler.h>
#include <StifLogger.h>
#include "getlist.h"
#include<liwcommon.h>
#include<liwvariant.h>
#include "landmarkliwparams.hrh"
#include <EPos_CPosLandmarkDatabase.h>
#include <EPos_CPosLandmark.h>
#include <EPos_CPosLandmarkEncoder.h>
#include <EPos_CPosLmCategoryManager.h>
#include "tlandmark_provider.h"
#include <EPos_HPosLmDatabaseInfo.h>
#include <EPos_CPosLmDatabaseManager.h>
#include <lbsposition.h>
#include "serviceerrno.h"
#include "tlandmark_provider.h"

using namespace LIW ;

_LIT8(KTestInterface, 	"IDataSource");
_LIT8(KTestContent,		"Service.Calendar");
_LIT8(KCmd,				"RequestNotification");
_LIT(KTestCalendar, 	"CalChangeNotify");
_LIT8(KErrCode , "ErrorCode") ;
_LIT(KLmName1, "lm1");
_LIT(KLmName2, "lma2");
_LIT(KLmName3, "lma3");
_LIT(KLmName4, "landmark1");
_LIT(KLmName5, "landmark2");
_LIT(KLmName6, "landmark3");

_LIT(KLmSearchString, "lm*");
_LIT(KLmSearchString1, "lma*");

#define PASS  TInt(0)
#define FAIL  (!PASS)

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
	
	const TLiwGenericParam* err = aEventParamList.FindFirst(pos,KErrCode);
	if(err)
		result = err->Value().AsTInt32();
		
	if(!result && aEventId != KLiwEventCanceled)
	{
	iResult = result;	
	pos=0;	
    const TLiwGenericParam* output = aEventParamList.FindFirst( pos,_L8("ReturnValue"));
	
	if(output)
		{

		}
	}
	
	else if(!result && aEventId == KLiwEventCanceled)
		iResult = KErrNone;
	else
		iResult = result;

	if ( iWaitSchedular && iWaitSchedular->IsStarted())
		{
		iWaitSchedular->AsyncStop();
		}
		return 0;
}

CTestAsync* CTestAsync::NewL(TInt type)
	{
	CTestAsync* self = new (ELeave) CTestAsync();
	self->ConstructL(type);
	return self;
	}

CTestAsync::~CTestAsync()
	{
	Cancel();
	delete gLog;
	inparam->Reset();
	outparam->Reset();
	
	interface->Close();
	
	delete iServiceHandler;
	
	delete iCallback;

	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();

	delete iWaitSchedular;
	}


void CTestAsync::ConstructL(TInt case_type)
	{
	TFileName glogFileName;
	gLog = CStifLogger::NewL( Ktlandmark_providerLogPath, 
                          glogFileName,
                          CStifLogger::ETxt,
                          CStifLogger::EFile,
                          EFalse );
                          
	iTestCaseType = case_type;
	interface = CreateInterface();
	CActiveScheduler::Add(this);
	iWaitSchedular = new(ELeave) CActiveSchedulerWait();
	}

MLiwInterface* CTestAsync::CreateInterface()
{
	
	iServiceHandler = CLiwServiceHandler::NewL();

	inparam = &(iServiceHandler->InParamListL());
	outparam = &(iServiceHandler->OutParamListL());
	
	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);

	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray a;
	a.AppendL(crit);    
	
	iServiceHandler->AttachL(a);
	iServiceHandler->ExecuteServiceCmdL(*crit, *inparam, *outparam); 

	a.Reset();
	delete crit;
	
	TInt pos = 0;

	outparam->FindFirst( pos, KIDataSource );
	if(pos != KErrNotFound)
		{
		interface = (*outparam)[pos].Value().AsInterface();	
		}

	outparam->Reset();
	inparam->Reset();
	
	return interface;
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
		switch(iTestCaseType)
		{
			case 1 : TestFunc();
					  break;
			case 2 : GetListInvalidCase();
					  break;
			case 3 : AddGetListCancel();
					 break;
			case 4 : CancelWithInvalidTid();
					 break;
			case 5 : CallGetListMultipleTimes();
					 break;
			case 6 : CancelKeyBasedTid();
					 break;
			case 7 : CancelPosBasedTid();
					 break;
			case 8 : CancelLargeTid();
					 break;
			case 9 : CancelInvalidTidType();
					 break;
			case 10 : CancelInvalidCmd();
					  break;
		}
	}


TInt32 CTestAsync::Result()
	{
	return iResult;
	}

void CTestAsync::Start()
	{
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}

void CTestAsync::CancelInvalidCmd()
{
       	TLiwGenericParam param;
		iCallback = CCalCallback::NewL(iWaitSchedular, iResult);
		CLiwMap* getlistlandmark_map = CLiwDefaultMap::NewL();
   		param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
   		inparam->AppendL(param);
   		param.Reset();
    		
    	TRAPD(err_getlist, interface->ExecuteCmdL(KGetList, *inparam, *outparam, KLiwOptASyncronous, iCallback));
		getlistlandmark_map->DecRef();
	
		TInt pos=0;
		const TLiwGenericParam* output = outparam->FindFirst( pos,_L8("TransactionID"));
	
		if(output)
		{
			iTransactionId = output->Value().AsTInt32();
			CancelNotification_InvalidCmd(); //Call cancel 
		}
		else
		{
			if(iWaitSchedular->IsStarted())
				iWaitSchedular->AsyncStop();
			iResult = SErrBadArgumentType;
		}   
    		
	inparam->Reset();
	outparam->Reset();	
    
}

void CTestAsync::CancelNotification_InvalidCmd()
{
    CLiwGenericParamList* inparam = &(iServiceHandler->InParamListL());
	CLiwGenericParamList* outparam = &(iServiceHandler->OutParamListL());
	
    TLiwGenericParam param;
    param.SetNameAndValueL(KNullDesC8,TLiwVariant((TReal32)44.55));
    inparam->AppendL(param);
   	param.Reset();
    		
    TRAPD(err_cancel,interface->ExecuteCmdL(KCancel, *inparam, *outparam,KLiwOptASyncronous,iCallback ));
      
    TInt pos=0;  
    const TLiwGenericParam* err = outparam->FindFirst(pos,KErrCode);
	if(err)
	{
			if(iWaitSchedular->IsStarted())
				iWaitSchedular->AsyncStop();
			if(iResult == KErrGeneral)
				iResult = err->Value().AsTInt32();	
	}		
	
	inparam->Reset();
	outparam->Reset();  	
    
}

void CTestAsync::CancelInvalidTidType()
{
       	TLiwGenericParam param;
		iCallback = CCalCallback::NewL(iWaitSchedular, iResult);
		CLiwMap* getlistlandmark_map = CLiwDefaultMap::NewL();
   		param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
   		inparam->AppendL(param);
   		param.Reset();
    		
    	TRAPD(err_getlist, interface->ExecuteCmdL(KGetList, *inparam, *outparam, KLiwOptASyncronous, iCallback));
		getlistlandmark_map->DecRef();
	
		TInt pos=0;
		const TLiwGenericParam* output = outparam->FindFirst( pos,_L8("TransactionID"));
	
		if(output)
		{
			iTransactionId = output->Value().AsTInt32();
			CancelNotification_InvalidTidType(); //Call cancel 
		}
		else
		{
			if(iWaitSchedular->IsStarted())
				iWaitSchedular->AsyncStop();
			iResult = SErrBadArgumentType;
		}   
    		
	inparam->Reset();
	outparam->Reset();	
    
}

void CTestAsync::CancelNotification_InvalidTidType()
{
    CLiwGenericParamList* inparam = &(iServiceHandler->InParamListL());
	CLiwGenericParamList* outparam = &(iServiceHandler->OutParamListL());
	
    TLiwGenericParam param;
    param.SetNameAndValueL(KNullDesC8,TLiwVariant((TReal32)44.55));
    inparam->AppendL(param);
   	param.Reset();
    		
    TRAPD(err_cancel,interface->ExecuteCmdL(KCancel, *inparam, *outparam,KLiwOptCancel,0 ));
      
    TInt pos=0;  
    const TLiwGenericParam* err = outparam->FindFirst(pos,KErrCode);
	if(err)
	{
			if(iWaitSchedular->IsStarted())
				iWaitSchedular->AsyncStop();
			if(iResult == KErrGeneral)
				iResult = err->Value().AsTInt32();	
	}		
	
	inparam->Reset();
	outparam->Reset();  	
    
}

void CTestAsync::CancelLargeTid()
{
       	TLiwGenericParam param;
		iCallback = CCalCallback::NewL(iWaitSchedular, iResult);
		CLiwMap* getlistlandmark_map = CLiwDefaultMap::NewL();
   		param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
   		inparam->AppendL(param);
   		param.Reset();
    		
    	TRAPD(err_getlist, interface->ExecuteCmdL(KGetList, *inparam, *outparam, KLiwOptASyncronous, iCallback));
		getlistlandmark_map->DecRef();
	
		TInt pos=0;
		const TLiwGenericParam* output = outparam->FindFirst( pos,_L8("TransactionID"));
	
		if(output)
		{
			iTransactionId = output->Value().AsTInt32();
			CancelNotification(1,534); //Call cancel 
		}
		else
		{
			if(iWaitSchedular->IsStarted())
				iWaitSchedular->AsyncStop();
			iResult = SErrBadArgumentType;
		}   
    		
	inparam->Reset();
	outparam->Reset();	
    
}


void CTestAsync::CancelPosBasedTid()
{
       	TLiwGenericParam param;
		iCallback = CCalCallback::NewL(iWaitSchedular, iResult);
		CLiwMap* getlistlandmark_map = CLiwDefaultMap::NewL();
   		param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
   		inparam->AppendL(param);
   		param.Reset();
    		
    	TRAPD(err_getlist, interface->ExecuteCmdL(KGetList, *inparam, *outparam, KLiwOptASyncronous, iCallback));
		getlistlandmark_map->DecRef();
	
		TInt pos=0;
		const TLiwGenericParam* output = outparam->FindFirst( pos,_L8("TransactionID"));
	
		if(output)
		{
			iTransactionId = output->Value().AsTInt32();
			CancelNotification_PosBased(); //Call cancel 
		}
		else
		{
			if(iWaitSchedular->IsStarted())
				iWaitSchedular->AsyncStop();
			iResult = SErrBadArgumentType;
		}   
    		
	inparam->Reset();
	outparam->Reset();	
    
}

void CTestAsync::CancelNotification_PosBased()
{
	CLiwGenericParamList* inparam = &(iServiceHandler->InParamListL());
	CLiwGenericParamList* outparam = &(iServiceHandler->OutParamListL());
	
    TLiwGenericParam param;
    param.SetNameAndValueL(KNullDesC8,TLiwVariant(iTransactionId));
    inparam->AppendL(param);
   	param.Reset();
    		
    TRAPD(err_cancel,interface->ExecuteCmdL(KCancel, *inparam, *outparam,KLiwOptCancel,0 ));
      
    TInt pos=0;  
    const TLiwGenericParam* err = outparam->FindFirst(pos,KErrCode);
	if(err)
	{
			if(iWaitSchedular->IsStarted())
				iWaitSchedular->AsyncStop();
			if(iResult == KErrGeneral)
				iResult = err->Value().AsTInt32();	
	}		
	
	inparam->Reset();
	outparam->Reset();
}


void CTestAsync::CancelKeyBasedTid()
{
       	TLiwGenericParam param;
		iCallback = CCalCallback::NewL(iWaitSchedular, iResult);
		CLiwMap* getlistlandmark_map = CLiwDefaultMap::NewL();
   		param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
   		inparam->AppendL(param);
   		param.Reset();
    		
    	TRAPD(err_getlist, interface->ExecuteCmdL(KGetList, *inparam, *outparam, KLiwOptASyncronous, iCallback));
		getlistlandmark_map->DecRef();
	
		TInt pos=0;
		const TLiwGenericParam* output = outparam->FindFirst( pos,_L8("TransactionID"));
	
		if(output)
		{
			iTransactionId = output->Value().AsTInt32();
			CancelNotification_KeyBased(); //Call cancel 
		}
		else
		{
			if(iWaitSchedular->IsStarted())
				iWaitSchedular->AsyncStop();
			iResult = SErrBadArgumentType;
		}   
    		
	inparam->Reset();
	outparam->Reset();	
    
}

void CTestAsync::CancelNotification_KeyBased()
{
	CLiwGenericParamList* inparam = &(iServiceHandler->InParamListL());
	CLiwGenericParamList* outparam = &(iServiceHandler->OutParamListL());
	
    TLiwGenericParam param;
    param.SetNameAndValueL(KTransactionId,TLiwVariant(iTransactionId));
    inparam->AppendL(param);
   	param.Reset();
    		
    TRAPD(err_cancel,interface->ExecuteCmdL(KCancel, *inparam, *outparam,KLiwOptCancel,0 ));
      
    TInt pos=0;  
    const TLiwGenericParam* err = outparam->FindFirst(pos,KErrCode);
	if(err)
	{
			if(iWaitSchedular->IsStarted())
				iWaitSchedular->AsyncStop();
			if(iResult == KErrGeneral)
				iResult = err->Value().AsTInt32();	
	}		
	
	inparam->Reset();
	outparam->Reset();
}


void CTestAsync::CallGetListMultipleTimes()
{
	// Add landmark
	_LIT(KName,"GetListstress");
    _LIT(KDescription,"stress on getlist Api");
    
    CLiwMap* landmarkMap = CLiwDefaultMap::NewL();
    TLiwGenericParam param;
    TInt32 res = KErrGeneral;
         
    //name
    landmarkMap->InsertL(KLandmarkName,TLiwVariant(KName));
      
    //description
    landmarkMap->InsertL(KLandmarkDesc,TLiwVariant(KDescription));
    
    param.SetNameAndValueL(KDataFields,TLiwVariant(landmarkMap));
    inparam->AppendL(param);
    param.Reset();       
    
    param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
    inparam->AppendL(param);
    param.Reset();
    
    interface->ExecuteCmdL(KAdd,*inparam,*outparam,0,0);
    landmarkMap->DecRef();
    
    TInt index = 0;
    
    const TLiwGenericParam* err = outparam->FindFirst(index,KErrorCode);
    if(err)
    	res = err->Value().AsTInt32();
    
    if(!res)
    {
    	inparam->Reset();
		outparam->Reset();	
    	iCallback = CCalCallback::NewL(iWaitSchedular, iResult);
		TLiwGenericParam param;
		
		CLiwMap* getlistlandmark_map = CLiwDefaultMap::NewL();
    	param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
   		inparam->AppendL(param);
   		param.Reset();	
   		
    
    	param.SetNameAndValueL(KFilter,TLiwVariant(getlistlandmark_map));
    	inparam->AppendL(param);
    	param.Reset();
    	
    		
    	 interface->ExecuteCmdL(KGetList, *inparam, *outparam, KLiwOptASyncronous, iCallback);
		 outparam->Reset();
		 User::After(10);
		 interface->ExecuteCmdL(KGetList, *inparam, *outparam, KLiwOptASyncronous, iCallback);
	 	 getlistlandmark_map->DecRef();	
	 			
		index=0;
		const TLiwGenericParam* getlist_err = outparam->FindFirst(index,KErrCode);
		if(getlist_err)
		{
			 iResult = getlist_err->Value().AsTInt32();	
			 if(iResult)
			 {
			 	if(iWaitSchedular->IsStarted())
						iWaitSchedular->AsyncStop();
			 }
		}	
	
		inparam->Reset();
			
    }      
    		
	inparam->Reset();
	outparam->Reset();	
}

void CTestAsync::CancelNotification(TBool include_tid, TInt32 tid)
{
	gLog->Log(_L("inside cancel notification function"));
	CLiwGenericParamList* inparam = &(iServiceHandler->InParamListL());
	CLiwGenericParamList* outparam = &(iServiceHandler->OutParamListL());
	
   	if(include_tid)
   	{
   		CLiwDefaultMap* map = CLiwDefaultMap::NewL();
		CleanupStack::PushL(map);

		TLiwGenericParam element;
		if(tid > 0)		
				tid = tid * 20000000000000;
		element.SetNameAndValueL(_L8("TransactionID"), TLiwVariant(tid));
		inparam->AppendL(element);
		element.Reset();    
	
		map->DecRef();
    	CleanupStack::Pop(map);
   	}   
   	
    TRAPD(err_cancel,interface->ExecuteCmdL(KCancel, *inparam, *outparam,KLiwOptCancel,0 ));
      
    TInt pos=0;  
    const TLiwGenericParam* err = outparam->FindFirst(pos,KErrCode);
	if(err)
	{
			gLog->Log(_L("after call to cancel function"));
			if(iWaitSchedular->IsStarted())
				iWaitSchedular->AsyncStop();
			if(iResult == KErrGeneral)
				iResult = err->Value().AsTInt32();	
	}		
	
	inparam->Reset();
	outparam->Reset();
}

void CTestAsync::AddGetListCancel()
{
	// Add landmark
	_LIT(KName,"ktaka");
    _LIT(KDescription,"Indian state");
    
    CLiwMap* landmarkMap = CLiwDefaultMap::NewL();
    TLiwGenericParam param;
    TInt32 res = KErrGeneral;
         
    //name
    landmarkMap->InsertL(KLandmarkName,TLiwVariant(KName));
      
    //description
    landmarkMap->InsertL(KLandmarkDesc,TLiwVariant(KDescription));
    
    param.SetNameAndValueL(KDataFields,TLiwVariant(landmarkMap));
    inparam->AppendL(param);
    param.Reset();       
    
    param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
    inparam->AppendL(param);
    param.Reset();
    
    interface->ExecuteCmdL(KAdd,*inparam,*outparam,0,0);
    landmarkMap->DecRef();
    
    TInt index = 0;
    
    const TLiwGenericParam* err = outparam->FindFirst(index,KErrorCode);
    if(err)
    	res = err->Value().AsTInt32();
    
    if(!res)
    {
    	inparam->Reset();
		outparam->Reset();	
    	iCallback = CCalCallback::NewL(iWaitSchedular, iResult);
		TLiwGenericParam param;
	
		CLiwMap* getlistlandmark_map = CLiwDefaultMap::NewL();
   		param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
   		inparam->AppendL(param);
   		param.Reset();
    		
    	TRAPD(err_getlist, interface->ExecuteCmdL(KGetList, *inparam, *outparam, KLiwOptASyncronous, iCallback));
		getlistlandmark_map->DecRef();
	
		TInt pos=0;
		const TLiwGenericParam* output = outparam->FindFirst( pos,_L8("TransactionID"));
	
		if(output)
		{
			iTransactionId = output->Value().AsTInt32();
			CancelNotification(1,iTransactionId); //Call cancel 
		}
		else
		{
			if(iWaitSchedular->IsStarted())
				iWaitSchedular->AsyncStop();
			if(iResult == KErrGeneral)
				iResult = SErrBadArgumentType;
		}
			
    }      
    		
	inparam->Reset();
	outparam->Reset();	
    
}


void CTestAsync::CancelWithInvalidTid()
{
       	iCallback = CCalCallback::NewL(iWaitSchedular, iResult);
		TLiwGenericParam param;
	
		CLiwMap* getlistlandmark_map = CLiwDefaultMap::NewL();
   		param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
   		inparam->AppendL(param);
   		param.Reset();
    		
    	TRAPD(err_getlist, interface->ExecuteCmdL(KGetList, *inparam, *outparam, KLiwOptASyncronous, iCallback));
		getlistlandmark_map->DecRef();
	
		TInt pos=0;
		const TLiwGenericParam* output = outparam->FindFirst( pos,_L8("TransactionID"));
	
		if(output)
		{
			iTransactionId = output->Value().AsTInt32();
			CancelNotification(1,-25); //Call cancel 
		}
		else
		{
			if(iWaitSchedular->IsStarted())
				iWaitSchedular->AsyncStop();
			iResult = SErrBadArgumentType;
		}   
    		
	inparam->Reset();
	outparam->Reset();	
    
}


void CTestAsync::GetListInvalidCase()
{
	
	iCallback = CCalCallback::NewL(iWaitSchedular, iResult);
	TLiwGenericParam param;
	
	CLiwMap* getlistlandmark_map = CLiwDefaultMap::NewL();
   	param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
   	inparam->AppendL(param);
   	param.Reset();
    		
    TRAPD(err_getlist, interface->ExecuteCmdL(KGetList, *inparam, *outparam, KLiwOptASyncronous, NULL));
	getlistlandmark_map->DecRef();
	
	TInt pos=0;
	const TLiwGenericParam* output = outparam->FindFirst( pos,_L8("TransactionID"));
	
	if(output)
	{
		iTransactionId = output->Value().AsTInt32();
	}
	else
	{
		if(iWaitSchedular->IsStarted())
			iWaitSchedular->AsyncStop();
		iResult = SErrBadArgumentType;
	}	
}

void CTestAsync::TestFunc()
	{
/*	iServiceHandler = CLiwServiceHandler::NewL();

	CLiwGenericParamList* inparam = &(iServiceHandler->InParamListL());
	CLiwGenericParamList* outparam = &(iServiceHandler->OutParamListL());

	TInt	err; 

	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);

	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray a;
	a.AppendL(crit);    
	
	iServiceHandler->AttachL(a);
	iServiceHandler->ExecuteServiceCmdL(*crit, *inparam, *outparam); 

	a.Reset();
	delete crit;
	
	TInt pos = 0;

	outparam->FindFirst( pos, KIDataSource );
	if(pos != KErrNotFound)
		{
		interface = (*outparam)[pos].Value().AsInterface();	
		}

	outparam->Reset();
	inparam->Reset();*/
	
	iCallback = CCalCallback::NewL(iWaitSchedular, iResult);
	
/*	CPosLandmarkDatabase* db = CPosLandmarkDatabase::OpenL(KTestDbUri1);
	CleanupStack::PushL(db);
	ExecuteAndDeleteLD(db->InitializeL());
	RemoveAllLandmarks(db);
	CreateLandmarksL(db);
	CleanupStack::PopAndDestroy(db);
	
	TLiwGenericParam param;
	param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
	inparam->AppendL(param);
	param.Reset();

	TRAPD(err_getlist, interface->ExecuteCmdL(KGetList, *inparam, *outparam, KLiwOptASyncronous, iCallback));*/
	
	TLiwGenericParam param;
	
	CLiwMap* getlistlandmark_map = CLiwDefaultMap::NewL();
	param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
	inparam->AppendL(param);
	param.Reset();
   		
   	TRAPD(err_getlist, interface->ExecuteCmdL(KGetList, *inparam, *outparam, KLiwOptASyncronous, iCallback));
	getlistlandmark_map->DecRef();	

	TInt pos=0;
	const TLiwGenericParam* output = outparam->FindFirst( pos,_L8("TransactionID"));
	
	if(output)
		{
		iTransactionId = output->Value().AsTInt32();
		gLog->Log(_L("calling cancel function from testfunc"));
		CancelNotification(0,iTransactionId); //Call cancel with no trans Id
		}
	else
		{
		if(iWaitSchedular->IsStarted())
			iWaitSchedular->AsyncStop();
		}	
	
	inparam->Reset();
	outparam->Reset();
	}


//Helper functions

// -----------------------------------------------------------------------------
// CreateLandmarksL
// Helper method to add landmarks to a default database.
// -----------------------------------------------------------------------------
//
void CreateLandmarksL (CPosLandmarkDatabase* aLandmarkHandle)
  {
  CPosLandmark* lm = CPosLandmark::NewLC ();
  _LIT(KStreet,"broadway");
//  _LIT(KIconFile,"//s60//icons//qgn_graf_s60_logo.svg");
  _LIT(KDesc,"welcome to galactica");
  TPosition locale;
  locale.SetCoordinate(12.345,67.89);
  lm->SetLandmarkNameL(KLmName1);  
  lm->SetPositionL(locale);
  lm->SetCoverageRadius(12.345);
  lm->SetPositionFieldL(EPositionFieldStreet,KStreet);
  lm->SetLandmarkDescriptionL(KDesc); 
  aLandmarkHandle->AddLandmarkL(*lm);
  CleanupStack::PopAndDestroy(lm);
  lm = CPosLandmark::NewLC ();	
  lm->SetLandmarkNameL  (KLmName2);
  aLandmarkHandle->AddLandmarkL  (*lm);

  lm->SetLandmarkNameL  (KLmName3);
  aLandmarkHandle->AddLandmarkL  (*lm);

  lm->SetLandmarkNameL  (KLmName4);
  aLandmarkHandle->AddLandmarkL  (*lm);

  lm->SetLandmarkNameL  (KLmName5);
  aLandmarkHandle->AddLandmarkL  (*lm);

  lm->SetLandmarkNameL  (KLmName6);
  aLandmarkHandle->AddLandmarkL  (*lm);

  CleanupStack::PopAndDestroy(lm);
  }

// -----------------------------------------------------------------------------
// CheckErrorCode
// checks error code e
// called by all testcases.
// -----------------------------------------------------------------------------
//
TInt CheckErrorCode( const CLiwGenericParamList& aOutList, TInt32& aError ) 
  {
  TInt Index = 0;
  const TLiwGenericParam* errcode = aOutList.FindFirst(Index,KErrorCode);
  if ( KErrNotFound == Index )
    {
  //  iLog->Log( _L("ErrorCode not found in output ArgList") );
    return FAIL;
    }
  else
  	{
  	aError = errcode->Value().AsTInt32();
  	return PASS;	
  	}
  
  }

// -----------------------------------------------------------------------------
// RemoveAllLandmarks
// Helper method to remove all landmarks for preconditional tests.
// -----------------------------------------------------------------------------
//

void RemoveAllLandmarks (CPosLandmarkDatabase* aLandmarkHandle)
  {
    ExecuteAndDeleteLD(aLandmarkHandle->RemoveAllLandmarksL());
  }
// -----------------------------------------------------------------------------
// RemoveAllLandmarks
// Helper method to remove all categories for preconditional tests.
// -----------------------------------------------------------------------------
//
void RemoveAllCategories  (CPosLmCategoryManager* aHandle)
  {
  TPosLmItemId catID;
  CPosLmItemIterator*iterator = aHandle->CategoryIteratorL();
  CleanupStack::PushL(iterator);

  while ((catID = iterator->NextL()) != KPosLmNullItemId)
    {
      TRAPD(err,ExecuteAndDeleteLD(aHandle->RemoveCategoryL( catID )));
       TBuf8<50> error;
      TRealFormat format;
      error.Num(err,format) ;
   //   iLog->Log( error );
    }
  CleanupStack::PopAndDestroy(iterator);
}


// -----------------------------------------------------------------------------
// DeleteAllDatabases
// removes all local databases from the terminal
// called by all testcases.
// -----------------------------------------------------------------------------
//
/*void DeleteAllLocalDatabasesL()
    {
  TInt count;

  CDesCArray* dbList = iDatabaseManager->ListDatabasesLC(_L("file"));
  count = dbList->Count();

  for ( TInt i = 0; i < count; i++ )
    {
    TPtrC db = (*dbList)[i];
    iDatabaseManager->DeleteDatabaseL ( db );
    }
  CleanupStack::PopAndDestroy (1);
    }*/

