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




// SYSTEM INCLUDE FILES
#include <e32base.h>
#include <f32file.h> //for RFile and Rfs

#include "calendarheader.h"
#include "calendarservice.h"

// USER INCLUDE FILES
#include "calimptestcases.h"
#include "teststartconsolealarmserver.h"    
    
#include<ascliclientutils.h>


_LIT(KCalName              ,"c:Calendar");



_LIT(KImportGuidsFile      ,"C:\\ImportGuidsOutput.txt");
_LIT(KImportLuidsFile      ,"C:\\ImportLuidsOutput.txt");

_LIT(KImportAsyncGuidsFile ,"C:\\ImportGuidsOutputAsync.txt");
_LIT(KImportAsyncLuidsFile ,"C:\\ImportLuidsOutputAsync.txt");

_LIT8(KParseToken           ,"|");

_LIT(KICALImportGuidsFile      ,"C:\\ICALImportGuidsOutput.txt");
_LIT(KICALImportLuidsFile      ,"C:\\ICALImportLuidsOutput.txt");

_LIT(KICALImportAsyncGuidsFile ,"C:\\ICALImportAsyncGuidsOutput.txt");
_LIT(KICALImportAsyncLuidsFile ,"C:\\ICALImportAsyncLuidsOutput.txt");
		
		
		
_LIT(KTestCal1Name         ,"c:testcal1imp");
_LIT(KTestCal2Name         ,"c:testcal2imp");

_LIT(KTestCal1NameAsync    ,"c:testcal1impAsync");
_LIT(KTestCal2NameAsync    ,"c:testcal2impAsync");

CCalImpTestCases* CCalImpTestCases::NewL( TInt& aResult, TInt aVCalOrICal) //1 means VCal else ICal
	{
	CCalImpTestCases* self = new(ELeave)CCalImpTestCases( aResult, aVCalOrICal );
	
	self->ConstructL();
	
	return self;
	}

CCalImpTestCases::~CCalImpTestCases()
	{
	Cancel();
	
	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();
	
	if(iCalendarService)
		delete iCalendarService;
	
	if(iWaitSchedular)
		delete iWaitSchedular;
	
	if(iArruids.Count())
		iArruids.ResetAndDestroy();
	}
	
	
//	
//Whats done here? 
//	Export all the contents of Default System Calender to a buffer using Export of CCalendarService
//	Use the buffer to import them to "importtothiscalender" and the generated guids and luids are outputted to 
//	ImportGuidsOutput.txt and ImportLuidsOutput.txt respectively
//	
TInt CCalImpTestCases::TestImportL()
	{
	iTestCaseType = KImportSync;
	
	RemoveCalendarFile(iCalendarService, KTestCal1Name.operator()());
	
	iResult = AddCalendarFile(iCalendarService, KTestCal1Name.operator()());
	
	if(iResult != KErrNone)
		return iResult ;
	
	RPointerArray<TUIDSet> arruids(5);
	
	TUIDSet* uids = NULL;
	
	if(AddAppointment(iCalendarService, KTestCal1Name.operator()(), uids) == KErrNone && uids)
		{
		arruids.Append(uids);
		uids = NULL;
		}

	if(AddEvent(iCalendarService, KTestCal1Name.operator()(), uids) == KErrNone && uids)
		{
		arruids.Append(uids);
		uids = NULL;
		}

	if(AddReminder(iCalendarService, KTestCal1Name.operator()(), uids) == KErrNone && uids)
		{
		arruids.Append(uids);
		uids = NULL;
		}

	if(AddAnny(iCalendarService, KTestCal1Name.operator()(), uids) == KErrNone && uids)
		{
		arruids.Append(uids);
		uids = NULL;
		}

	if(AddToDo(iCalendarService, KTestCal1Name.operator()(), uids) == KErrNone && uids)
		{
		arruids.Append(uids);
		uids = NULL;
		}
	
	
    CCalendarExportParams *expParams = CCalendarExportParams::NewL();
    
	HBufC8* buffer = NULL;
	
	if( iVCalOrICal == 1)
		{
		TRAP( iResult ,iCalendarService->ExportL( KTestCal1Name.operator()() , KFormatVCal.operator()() , expParams ,buffer ) );
		}
	else
		{
		TRAP( iResult ,iCalendarService->ExportL( KTestCal1Name.operator()() , KFormatICal.operator()() , expParams ,buffer ) );
		}
	
	delete expParams;	
	
	if(iResult != KErrNone)
		{
		delete buffer;
		arruids.ResetAndDestroy();
		return iResult;
		}
	
	
	RemoveCalendarFile(iCalendarService, KTestCal2Name.operator()());
	
	iResult = AddCalendarFile(iCalendarService, KTestCal2Name.operator()());
	
	if(iResult != KErrNone)
		return iResult ;
	
	RPointerArray<TUIDSet> uIDSet(5);
	
	if( iVCalOrICal == 1)
		{
		TRAP( iResult ,iCalendarService->ImportL( KTestCal2Name.operator()() , KFormatVCal.operator()() , *buffer ,uIDSet ) );
		}
	else
		{
		TRAP( iResult ,iCalendarService->ImportL( KTestCal2Name.operator()() , KFormatICal.operator()() , *buffer ,uIDSet ) );
		}
	
	
	if(iResult != KErrNone)
		{
		delete buffer;
		arruids.ResetAndDestroy();
		uIDSet.ResetAndDestroy();
		return iResult;
		}
		
	if ( arruids.Count() != uIDSet.Count() )	
		iResult = KErrGeneral;
	
	delete buffer;
	arruids.ResetAndDestroy();
	uIDSet.ResetAndDestroy();
	
	RemoveCalendarFile(iCalendarService, KTestCal1Name.operator()());
	RemoveCalendarFile(iCalendarService, KTestCal2Name.operator()());
	
	return iResult;
	}
	

//	
//Whats done here? 
//	Export all the contents of Default System Calender to a buffer using Export of CCalendarService
//	Use the buffer to import them to "importtothiscalender" and the generated guids and luids are outputted to 
//	ImportGuidsOutputAsync.txt and ImportLuidsOutputAsync.txt respectively
//		
void CCalImpTestCases::TestImportAsyncL()
	{
	Start();
	}

TInt CCalImpTestCases::Result()
	{
	return iResult;
	}
	
void CCalImpTestCases::ConstructL()
	{
	CActiveScheduler::Add(this);
	
	iCalendarService = CCalendarService::NewL();
	
	iWaitSchedular = new(ELeave) CActiveSchedulerWait();
	}
	
CCalImpTestCases::CCalImpTestCases( TInt& aResult, TInt aVCalOrICal): CActive(EPriorityStandard), iResult(aResult) ,
														   iVCalOrICal(aVCalOrICal)	
	{
	
	}
	
//for the sake of ActiveObject
void CCalImpTestCases::DoCancel()
	{
	
	}

void CCalImpTestCases::RunL()
	{
	RemoveCalendarFile(iCalendarService, KTestCal1NameAsync.operator()());
	
	iResult = AddCalendarFile(iCalendarService, KTestCal1NameAsync.operator()());
	
	if(iResult != KErrNone)
		goto Final;

	TUIDSet* uids = NULL;
	
	if(AddAppointment(iCalendarService, KTestCal1NameAsync.operator()(), uids) == KErrNone && uids)
		{
		iArruids.Append(uids);
		uids = NULL;
		}

	if(AddEvent(iCalendarService, KTestCal1NameAsync.operator()(), uids) == KErrNone && uids)
		{
		iArruids.Append(uids);
		uids = NULL;
		}

	if(AddReminder(iCalendarService, KTestCal1NameAsync.operator()(), uids) == KErrNone && uids)
		{
		iArruids.Append(uids);
		uids = NULL;
		}

	if(AddAnny(iCalendarService, KTestCal1NameAsync.operator()(), uids) == KErrNone && uids)
		{
		iArruids.Append(uids);
		uids = NULL;
		}

	if(AddToDo(iCalendarService, KTestCal1NameAsync.operator()(), uids) == KErrNone && uids)
		{
		iArruids.Append(uids);
		uids = NULL;
		}
	
	
    CCalendarExportParams *expParams = CCalendarExportParams::NewL();


	HBufC8* buffer = NULL;
	
	if( iVCalOrICal == 1)
		{
		TRAP( iResult ,iCalendarService->ExportL( KTestCal1NameAsync.operator()() , KFormatVCal.operator()() , expParams ,buffer ) );
		}
	else
		{
		TRAP( iResult ,iCalendarService->ExportL( KTestCal1NameAsync.operator()() , KFormatICal.operator()() , expParams ,buffer ) );
		}
		
	delete expParams;
	
	if(iResult != KErrNone)
		{
		delete buffer;
		iWaitSchedular->AsyncStop();
		goto Final;
		}
	
	
	RemoveCalendarFile(iCalendarService, KTestCal2NameAsync.operator()());
	
	iResult = AddCalendarFile(iCalendarService, KTestCal2NameAsync.operator()());
	
	if(iResult != KErrNone)
		{
		delete buffer;
		iWaitSchedular->AsyncStop();
		goto Final;
		}
	
	if( iVCalOrICal == 1)
		{
		TRAP( iResult ,iCalendarService->ImportL( KTestCal2NameAsync.operator()() , KFormatVCal.operator()() , *buffer ,this ) );
		}
	else
		{
		TRAP( iResult ,iCalendarService->ImportL( KTestCal2NameAsync.operator()() , KFormatICal.operator()() , *buffer ,this ) );
		}

	if(iResult != KErrNone)
		{
		iWaitSchedular->AsyncStop();
		}

	delete buffer;	
	Final: ;		
	}
			

void CCalImpTestCases::Start()
	{
	SetActive();
	
	TRequestStatus* temp = &iStatus;
	
	User::RequestComplete(temp, KErrNone);
	
	iWaitSchedular->Start();	

	}

			
void CCalImpTestCases::NotifyResultL(TInt aErrCode, TAny* aResult)
	{
	//******************* set iResult ****************************
	iResult = aErrCode;
	//******************* set iResult ****************************
	//write the result to the corresponding file basing on the iTestCaseType
	
	RPointerArray<TUIDSet>* uIDSet = (RPointerArray<TUIDSet>*)aResult;
	if(iResult != KErrNone)
		goto EndPoint;
		
	if ( iArruids.Count() != uIDSet->Count() )	
		iResult = KErrGeneral;


EndPoint:	
	TRAPD(err,RemoveCalendarFile(iCalendarService, KTestCal1NameAsync.operator()()) );
//	TRAP(err ,RemoveCalendarFile(iCalendarService, KTestCal2NameAsync.operator()()) );
		
	iWaitSchedular->AsyncStop();
	
	}
