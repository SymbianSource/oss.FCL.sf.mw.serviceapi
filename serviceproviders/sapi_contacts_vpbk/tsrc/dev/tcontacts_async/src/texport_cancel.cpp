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

 

#include<e32base.h>

#include "contactservice.h"
#include "contactcallback.h"
#include "tcontacts_async.h"
#include "contactiter.h" // Iterator 


_LIT(KError,"Error code is");
_LIT(KSuccess,"Successful");
_LIT(KNewLine,"\n");
_LIT(KServiceOpen,"Service handle created");
_LIT(KServiceClose,"Service handle deleted");
_LIT(KPhoneNumber,"9886431364");
 _LIT(KGroup1,"Test1");
 
 
#ifdef MAIN
#define export_cancel main
#endif

class CExportTestAsync: public CActive, public MContactCallback
{
public:
	static CExportTestAsync* NewL();
	~CExportTestAsync();
	void Start();
	TInt Result();
	void AddOneContactL(TDesC& aName);
	void DeleteAllL();

private:
	void ConstructL();
	CExportTestAsync();
	
	virtual void DoCancel();
	virtual void RunL();
	
	
	void TestFunc();
	
	void HandleReturnValue(TOperationEvent aEvent, const TInt& aError , TInt aTransId);
	
	void HandleReturnIter( const TInt& aError, CContactIter* aIter, TInt aTransId );
	
	
private:	
	CActiveSchedulerWait* 	iWaitSchedular;
	CContactService*		iContactService;
	TInt 					iResult;	
    MVPbkContactOperationBase* iOp;
    HBufC8* 				iBuffer;
};

CExportTestAsync* CExportTestAsync::NewL()
	{
	CExportTestAsync* self = new(ELeave)CExportTestAsync();
	self->ConstructL();
	return self;
	}

CExportTestAsync::~CExportTestAsync()
	{
	Cancel();
	
	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();
	
	if(iContactService)
		delete iContactService;
	
	if(iWaitSchedular)
		delete iWaitSchedular;
	
	}

void CExportTestAsync::ConstructL()
	{
	CActiveScheduler::Add(this);
	iContactService = CContactService::NewL();
	iWaitSchedular = new(ELeave) CActiveSchedulerWait();
	}

CExportTestAsync::CExportTestAsync() :
CActive(EPriorityStandard)
	{
	}

void CExportTestAsync::DoCancel()
	{
		
	}

void CExportTestAsync::RunL()
	{
	TestFunc();
	}

void CExportTestAsync::Start()
	{
	SetActive();
	TRequestStatus* temp = &iStatus;
	User::RequestComplete(temp, KErrNone);
	iWaitSchedular->Start();	
	}

void CExportTestAsync::HandleReturnValue(TOperationEvent aEvent, const TInt& aError , TInt aTransId)
	{
	//******************* set iResult ****************************
	
	if(aEvent ==EOpCancel)
		iResult = KErrNone;
	else
		iResult = KErrGeneral;
		
	
	iWaitSchedular->AsyncStop();
	}
	
void CExportTestAsync::HandleReturnIter( const TInt& aError, CContactIter* aIter, TInt aTransId )
	{
    _LIT(KFileName,"c:\\vcardim.vcf");
    TFileName file(KFileName);

	// It should not be called
    CSingleContact* singleContact = NULL;  
    HBufC8* buf = NULL;
    TInt count = 0; 
    aIter->NextL(singleContact,buf);
    iBuffer = buf;
    
    iContactService->ExportVCardL(this,0,file,*iBuffer);
	iContactService->Cancel(0);

    delete buf;
    delete singleContact;
    delete aIter;

	}

	
TInt CExportTestAsync::Result()
	{
	return iResult;
	}

void CExportTestAsync::TestFunc()
	{

	TRAPD(err,iContactService->GetListL(this,1,EContacts,KNullDesC8,KNullDesC,NULL,EAsc ));

 	}


int export_cancel(int, char**)
	{
	__UHEAP_MARK;
	CExportTestAsync* test = CExportTestAsync::NewL();
	
	test->Start();
	
	TInt result = test->Result();
	
	delete test;
	__UHEAP_MARKEND;
	
	return  result;
	}






