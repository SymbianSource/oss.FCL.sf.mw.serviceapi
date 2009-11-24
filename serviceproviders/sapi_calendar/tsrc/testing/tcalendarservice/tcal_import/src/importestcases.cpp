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
#include "importestcases.h"
#include "teststartconsolealarmserver.h"    
    
#include<ascliclientutils.h>


_LIT(KCalName              ,"c:Calendar");
_LIT8(KTest,          "abc");



_LIT(KImportGuidsFile      ,"C:\\ImportGuidsOutput.txt");
_LIT(KVcalImportGuidsFile      ,"C:\\ImportVcalGuidsOutput.txt");
_LIT(KImportGuidsTestFile      ,"C:\\ImportGuidsOutput");
_LIT(KImportInvalidFile      ,"xyz");
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
_LIT(KTestCal3Name         ,"c:testcal3imp");

_LIT(KTestCal1NameAsync    ,"c:testcal1impAsync");
_LIT(KTestCal2NameAsync    ,"c:testcal2impAsync");
_LIT(KTestCal3NameAsync    ,"c:testcal3impAsync");



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
	
	if(iArruids.Count())
		iArruids.ResetAndDestroy();
	RemoveCalendarFile(iCalendarService, KTestCal2NameAsync.operator()());
	if(iCalendarService)
		delete iCalendarService;
	
	if(iWaitSchedular)
		delete iWaitSchedular;
	
	}
	
	
//	
//Whats done here? 
//	Export all the contents of Default System Calender to a buffer using Export of CCalendarService
//	Use the buffer to import them to "importtothiscalender" and the generated guids and luids are outputted to 
//	ImportGuidsOutput.txt and ImportLuidsOutput.txt respectively
//	
TInt CCalImpTestCases::TestImportGuidL()
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
    
    expParams->AddGuidL( *(arruids[0])->iGlobalUID );
    expParams->AddGuidL( *(arruids[4])->iGlobalUID );
    expParams->AddGuidL( *(arruids[3])->iGlobalUID );
   // expParams->AddLocalUid( arruids[2]->iLocalUID );
    
    
	HBufC8* buffer = NULL;
	TInt err_export;
	
	if( iVCalOrICal == 1)
		{
		TRAP( err_export ,iCalendarService->ExportL( KTestCal1Name.operator()() , KFormatVCal.operator()() , expParams ,buffer ) );
		}
	else
		{
		TRAP( err_export ,iCalendarService->ExportL( KTestCal1Name.operator()() , KFormatICal.operator()() , expParams ,buffer ) );
		}
	
	delete expParams;	
	
	if(err_export != KErrNone)
		{
		delete buffer;
		arruids.ResetAndDestroy();
		return iResult;
		}
	
	
	RemoveCalendarFile(iCalendarService, KTestCal2Name.operator()());
	
	AddCalendarFile(iCalendarService, KTestCal2Name.operator()());
	
	
	
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
	TInt count = uIDSet.Count();
	TInt arr_count = arruids.Count() - 2;
	
	if ( arr_count != uIDSet.Count() )	
		iResult = KErrGeneral;
	
	delete buffer;
	arruids.ResetAndDestroy();
	uIDSet.ResetAndDestroy();
	
	RemoveCalendarFile(iCalendarService, KTestCal1Name.operator()());
	RemoveCalendarFile(iCalendarService, KTestCal2Name.operator()());
	
	return iResult;
	}
	


TInt CCalImpTestCases::TestImportLuidL()
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
    
   expParams->AddLocalUid( arruids[2]->iLocalUID );
   expParams->AddLocalUid( arruids[3]->iLocalUID );
   expParams->AddLocalUid( arruids[4]->iLocalUID );
    
    
	HBufC8* buffer = NULL;
	TInt err_export;
	
	if( iVCalOrICal == 1)
		{
		TRAP( err_export ,iCalendarService->ExportL( KTestCal1Name.operator()() , KFormatVCal.operator()() , expParams ,buffer ) );
		}
	else
		{
		TRAP( err_export ,iCalendarService->ExportL( KTestCal1Name.operator()() , KFormatICal.operator()() , expParams ,buffer ) );
		}
	
	delete expParams;	
	
	if(err_export != KErrNone)
		{
		delete buffer;
		arruids.ResetAndDestroy();
		return iResult;
		}
	
	
	RemoveCalendarFile(iCalendarService, KTestCal2Name.operator()());
	
	AddCalendarFile(iCalendarService, KTestCal2Name.operator()());
	
	
	
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
	TInt count = uIDSet.Count();
	TInt arr_count = arruids.Count() - 2;
	
	if ( arr_count != uIDSet.Count() )	
		iResult = KErrGeneral;
	
	delete buffer;
	arruids.ResetAndDestroy();
	uIDSet.ResetAndDestroy();
	
	RemoveCalendarFile(iCalendarService, KTestCal1Name.operator()());
	RemoveCalendarFile(iCalendarService, KTestCal2Name.operator()());
	
	return iResult;
	}


TInt CCalImpTestCases::TestImportCases1()
	{
	iTestCaseType = KImportSync;
	
	RemoveCalendarFile(iCalendarService, KTestCal1Name.operator()());
	
	AddCalendarFile(iCalendarService, KTestCal1Name.operator()());
	
		
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


	HBufC8* buffer = NULL;
	TInt err_export;
	CCalendarExportParams *expParams = CCalendarExportParams::NewL();
    
    
    expParams->AddLocalUid( arruids[2]->iLocalUID );
    expParams->AddLocalUid( arruids[3]->iLocalUID );
    
	
	if( iVCalOrICal == 1)
		{
		TRAP( err_export ,iCalendarService->ExportL( KTestCal1Name.operator()() , KFormatVCal.operator()() , expParams ,buffer ) );
		}
	else
		{
		TRAP( err_export ,iCalendarService->ExportL( KTestCal1Name.operator()() , KFormatICal.operator()() , expParams ,buffer ) );
		}
	
//	delete expParams;	
	
	if(err_export != KErrNone)
		{
		delete buffer;
		delete expParams;
		delete uids;
		uids = NULL;
		arruids.ResetAndDestroy();
		iResult = err_export;
		return iResult;
		}
    
    
	RemoveCalendarFile(iCalendarService, KTestCal2Name.operator()());
	
	AddCalendarFile(iCalendarService, KTestCal2Name.operator()());
	
	

	
	RPointerArray<TUIDSet> uIDSet(5);
	TInt err_import;
	//import from unexisting file
	if( iVCalOrICal == 1)
		{
		TRAP( err_import ,iCalendarService->ImportL( KTestCal2Name.operator()() , KFormatVCal.operator()() , KImportLuidsFile.operator()() ,uIDSet ) );
		}
	else
		{
		TRAP( err_import ,iCalendarService->ImportL( KTestCal2Name.operator()() , KFormatICal.operator()() , KImportLuidsFile.operator()() ,uIDSet ) );
		}
	
	
	
	if(err_import != KErrNotFound)
		{
		delete uids;
		delete buffer;
		delete expParams;
		uids = NULL;
		arruids.ResetAndDestroy();
		uIDSet.ResetAndDestroy();
		iResult = err_import;
		return iResult;
		}
	
	//import from calendar file 
	if( iVCalOrICal == 1)
		{
		TRAP( err_import ,iCalendarService->ImportL( KTestCal2Name.operator()() , KFormatVCal.operator()() , KTestCal1Name.operator()() ,uIDSet ) );
		}
	else
		{
		TRAP( err_import ,iCalendarService->ImportL( KTestCal2Name.operator()() , KFormatICal.operator()() , KTestCal1Name.operator()() ,uIDSet ) );
		}
	
	
			
	if(err_import != KErrPathNotFound)
		{
		delete uids;
		uids = NULL;
		delete buffer;
		delete expParams;
		arruids.ResetAndDestroy();
		uIDSet.ResetAndDestroy();
		iResult = err_import;
		return iResult;
		}
	
	//file name as Null
	if( iVCalOrICal == 1)
		{
		TRAP( err_import ,iCalendarService->ImportL( KTestCal2Name.operator()() , KFormatVCal.operator()() , KNullDesC ,uIDSet ) );
		}
	else
		{
		TRAP( err_import ,iCalendarService->ImportL( KTestCal2Name.operator()() , KFormatICal.operator()() , KNullDesC ,uIDSet ) );
		}
		

	if(err_import != KErrBadName)
	{
		
		delete uids;
		delete buffer;
		delete expParams;
		arruids.ResetAndDestroy();
		uIDSet.ResetAndDestroy();
		iResult = err_import;
		return iResult;
	}
	
	
	
	delete expParams;
	delete buffer;
	delete uids;
	uids=NULL;
	arruids.ResetAndDestroy();
	uIDSet.ResetAndDestroy();
	
	
	RemoveCalendarFile(iCalendarService, KTestCal1Name.operator()());
	RemoveCalendarFile(iCalendarService, KTestCal2Name.operator()());
	
	return iResult;
	}
	

TInt CCalImpTestCases::TestImportCases2()
	{
	iTestCaseType = KImportSync;
	
	RemoveCalendarFile(iCalendarService, KTestCal1Name.operator()());
	
	AddCalendarFile(iCalendarService, KTestCal1Name.operator()());
	
	RPointerArray<TUIDSet> arruids;
	
	TUIDSet* uids = NULL;
	TUIDSet* new_uids = NULL;
	
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

	
	
    CCalendarExportParams *expParams = CCalendarExportParams::NewL();
    
    expParams->AddGuidL( *(arruids[0])->iGlobalUID );
    expParams->AddGuidL( *(arruids[1])->iGlobalUID );
    expParams->AddGuidL( *(arruids[2])->iGlobalUID );
       
    
	HBufC8* buffer = NULL;
	TInt err_export;
	
	if( iVCalOrICal == 1)
		{
		TRAP( err_export ,iCalendarService->ExportL( KTestCal1Name.operator()() , KFormatVCal.operator()() , expParams ,buffer ) );
		}
	else
		{
		TRAP( err_export ,iCalendarService->ExportL( KTestCal1Name.operator()() , KFormatICal.operator()() , expParams ,buffer ) );
		}
	
	delete expParams;	
	
	RemoveCalendarFile(iCalendarService, KTestCal2Name.operator()());
	
	AddCalendarFile(iCalendarService, KTestCal2Name.operator()());
	
	AddAnny(iCalendarService, KTestCal1Name.operator()(), new_uids);
	delete new_uids;
	new_uids = NULL;
	
		
	RPointerArray<TUIDSet> uIDSet;
	
	if( iVCalOrICal == 1)
		{
		TRAP( iResult ,iCalendarService->ImportL( KTestCal2Name.operator()() , KFormatVCal.operator()() , *buffer ,uIDSet ) );
		}
	else
		{
		TRAP( iResult ,iCalendarService->ImportL( KTestCal2Name.operator()() , KFormatICal.operator()() , *buffer ,uIDSet ) );
		}
	
	
	TInt count = uIDSet.Count();
	if(count != 3)
		iResult = KErrGeneral;
	
	delete buffer;
//	delete filter;
	arruids.ResetAndDestroy();
	uIDSet.ResetAndDestroy();
	
	RemoveCalendarFile(iCalendarService, KTestCal1Name.operator()());
	RemoveCalendarFile(iCalendarService, KTestCal2Name.operator()());
	
	return iResult;
	}

//Import cases - Three
TInt CCalImpTestCases::TestImportCases3()
	{
	iTestCaseType = KImportSync;
	
	RemoveCalendarFile(iCalendarService, KTestCal1Name.operator()());
	
	AddCalendarFile(iCalendarService, KTestCal1Name.operator()());
	
	RPointerArray<TUIDSet> arruids;
	
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


	
    CCalendarExportParams *expParams = CCalendarExportParams::NewL();
    CCalendarExportParams *new_expParams = CCalendarExportParams::NewL();
    
   // expParams->AddLocalUid( arruids[2]->iLocalUID );
    //expParams->AddLocalUid( arruids[3]->iLocalUID );
   expParams->SetExportFileNameL(KImportGuidsTestFile);
    
	HBufC8* buffer = NULL;
	TInt err_export;
	TInt err_import;
	
	if( iVCalOrICal == 1)
		{
		TRAP( err_export ,iCalendarService->ExportL( KTestCal1Name.operator()() , KFormatVCal.operator()() , expParams ,buffer ) );
		}
	else
		{
		TRAP( err_export ,iCalendarService->ExportL( KTestCal1Name.operator()() , KFormatICal.operator()() , expParams ,buffer ) );
		}
	
//	delete expParams;	
	
	
	RemoveCalendarFile(iCalendarService, KTestCal2Name.operator()());
	
	AddCalendarFile(iCalendarService, KTestCal2Name.operator()());
	
	delete uids;
	uids = NULL;
	
	
	
	RPointerArray<TUIDSet> uIDSet;
	
	if( iVCalOrICal == 1)
		{
		TRAP( iResult ,iCalendarService->ImportL( KTestCal2Name.operator()() , KFormatVCal.operator()() , KImportGuidsTestFile.operator()() ,uIDSet ) );
		}
	else
		{
		TRAP( iResult ,iCalendarService->ImportL( KTestCal2Name.operator()() , KFormatICal.operator()() , KImportGuidsTestFile.operator()() ,uIDSet ) );
		}
	
	TInt count = uIDSet.Count();
	if(count != 3 && iResult == KErrNone)
		iResult = KErrGeneral;
	count =0;
	
	
	// import - export for invalid file
	TRAPD(err_setfile,expParams->SetExportFileNameL(KImportInvalidFile));
	
	if( iVCalOrICal == 1)
		{
		TRAP( err_export ,iCalendarService->ExportL( KTestCal1Name.operator()() , KFormatVCal.operator()() , expParams ,buffer ) );
		}
	else
		{
		TRAP( err_export ,iCalendarService->ExportL( KTestCal1Name.operator()() , KFormatICal.operator()() , expParams ,buffer ) );
		}
		
		
		
	uIDSet.ResetAndDestroy();	
	if( iVCalOrICal == 1)
		{
		TRAP( err_import ,iCalendarService->ImportL( KTestCal2Name.operator()() , KFormatVCal.operator()() , KImportInvalidFile.operator()() ,uIDSet ) );
		}
	else
		{
		TRAP( err_import ,iCalendarService->ImportL( KTestCal2Name.operator()() , KFormatICal.operator()() , KImportInvalidFile.operator()() ,uIDSet ) );
		}
		
	count = uIDSet.Count();
	if((count != 0 || err_export != KErrPathNotFound) && iResult == KErrNone)
		iResult = KErrGeneral;
	count =0;
	
	// Import from file multiple times
	
	expParams->SetExportFileNameL(KImportGuidsFile);
	 expParams->AddLocalUid( arruids[1]->iLocalUID );
    expParams->AddLocalUid( arruids[2]->iLocalUID );
	
	if( iVCalOrICal == 1)
		{
		TRAP( err_export ,iCalendarService->ExportL( KTestCal1Name.operator()() , KFormatVCal.operator()() , expParams ,buffer ) );
		}
	else
		{
		TRAP( err_export ,iCalendarService->ExportL( KTestCal1Name.operator()() , KFormatICal.operator()() , expParams ,buffer ) );
		}
		
	uIDSet.ResetAndDestroy();	
	if( iVCalOrICal == 1)
		{
		TRAP( err_import ,iCalendarService->ImportL( KTestCal2Name.operator()() , KFormatVCal.operator()() , KImportGuidsFile.operator()() ,uIDSet ) );
		}
	else
		{
		TRAP( err_import ,iCalendarService->ImportL( KTestCal2Name.operator()() , KFormatICal.operator()() , KImportGuidsFile.operator()() ,uIDSet ) );
		}
		
	count = uIDSet.Count();
	count =0;	
		
	if( iVCalOrICal == 1)
		{
		TRAP( err_import ,iCalendarService->ImportL( KTestCal2Name.operator()() , KFormatVCal.operator()() , KImportGuidsFile.operator()() ,uIDSet ) );
		}
	else
		{
		TRAP( err_import ,iCalendarService->ImportL( KTestCal2Name.operator()() , KFormatICal.operator()() , KImportGuidsFile.operator()() ,uIDSet ) );
		}
		
	count = uIDSet.Count();
	if(count != 4 && iResult == KErrNone)
		iResult = KErrGeneral;
	count =0;	
	
	
	// Try to import from default calendar 
	
	uIDSet.ResetAndDestroy();
	
	if( iVCalOrICal == 1)
		{
		TRAP( err_import ,iCalendarService->ImportL( KTestCal2Name.operator()() , KFormatVCal.operator()() , KCalName.operator()() ,uIDSet ) );
		}
	else
		{
		TRAP( err_import ,iCalendarService->ImportL( KTestCal2Name.operator()() , KFormatICal.operator()() , KCalName.operator()() ,uIDSet ) );
		}
		
	
	if(err_import != KErrPathNotFound && iResult == KErrNone)
		iResult = KErrGeneral;
	
	
	// Import with invalid format
	expParams->SetExportFileNameL(KImportGuidsFile);
	
		uIDSet.ResetAndDestroy();
	
	if( iVCalOrICal == 1)
		{
		TRAP( err_export ,iCalendarService->ExportL( KTestCal1Name.operator()() , KFormatVCal.operator()() , expParams ,buffer ) );
		}
	else
		{
		TRAP( err_export ,iCalendarService->ExportL( KTestCal1Name.operator()() , KFormatICal.operator()() , expParams ,buffer ) );
		}
		
		
		
	if( iVCalOrICal == 1)
		{
		TRAP( err_import ,iCalendarService->ImportL( KTestCal2Name.operator()() , KTest.operator()() , KImportGuidsFile.operator()() ,uIDSet ) );
		}
	else
		{
		TRAP( err_import ,iCalendarService->ImportL( KTestCal2Name.operator()() , KTest.operator()() , KImportGuidsFile.operator()() ,uIDSet ) );
		}
			
	if(err_import != KErrNotSupported && iResult == KErrNone)
		iResult = KErrGeneral;		
			
	// Import with invalid luid
	
	new_expParams->AddLocalUid( 10000 );
    new_expParams->AddLocalUid( -3000 );
    new_expParams->SetExportFileNameL(KVcalImportGuidsFile);
    delete buffer;
    buffer = NULL;
    
    if( iVCalOrICal == 1)
		{
		TRAP( err_export ,iCalendarService->ExportL( KTestCal1Name.operator()() , KFormatVCal.operator()() , new_expParams ,buffer ) );
		}
	else
		{
		TRAP( err_export ,iCalendarService->ExportL( KTestCal1Name.operator()() , KFormatICal.operator()() , new_expParams ,buffer ) );
		}
		
	uIDSet.ResetAndDestroy();	
	if( iVCalOrICal == 1)
		{
		TRAP( err_import ,iCalendarService->ImportL( KTestCal2Name.operator()() , KFormatVCal.operator()() , KVcalImportGuidsFile.operator()() ,uIDSet ) );
		}
	else
		{
		TRAP( err_import ,iCalendarService->ImportL( KTestCal2Name.operator()() , KFormatICal.operator()() , KVcalImportGuidsFile.operator()() ,uIDSet ) );
		}
		
	count = uIDSet.Count();
	if(count != 0)
		iResult = KErrGeneral;
	
	
//	delete buffer;
	delete new_expParams;
	delete expParams;
	arruids.ResetAndDestroy();
	uIDSet.ResetAndDestroy();
	
	RemoveCalendarFile(iCalendarService, KTestCal1Name.operator()());
	RemoveCalendarFile(iCalendarService, KTestCal2Name.operator()());
	
	return iResult;
	}	
	
TInt CCalImpTestCases::TestImportFromFileL()
	{
	iTestCaseType = KImportSync;
	
	RemoveCalendarFile(iCalendarService, KTestCal1Name.operator()());
	
	 AddCalendarFile(iCalendarService, KTestCal1Name.operator()());
	
		
	RPointerArray<TUIDSet> arruids;
	
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
	
	delete uids;
	uids = NULL;
	
    CCalendarExportParams *expParams = CCalendarExportParams::NewL();
    
    
    
    expParams->AddGuidL( *(arruids[0])->iGlobalUID );
    expParams->AddGuidL( *(arruids[4])->iGlobalUID );
    expParams->AddGuidL( *(arruids[3])->iGlobalUID );
   expParams->SetExportFileNameL(KImportGuidsFile);
    
    
	HBufC8* buffer = NULL;
	TInt err_export;
	
	if( iVCalOrICal == 1)
		{
		TRAP( err_export ,iCalendarService->ExportL( KTestCal1Name.operator()() , KFormatVCal.operator()() , expParams ,buffer ) );
		}
	else
		{
		TRAP( err_export ,iCalendarService->ExportL( KTestCal1Name.operator()() , KFormatICal.operator()() , expParams ,buffer ) );
		}
	
	delete expParams;	
	
	if(buffer != NULL)
		{
		delete buffer;
		arruids.ResetAndDestroy();
		iResult = KErrGeneral;
		return iResult;
		}
	
	
	RemoveCalendarFile(iCalendarService, KTestCal2Name.operator()());
	
	AddCalendarFile(iCalendarService, KTestCal2Name.operator()());
	
		
	RPointerArray<TUIDSet> uIDSet(5);
	TInt err_import;
	
	if( iVCalOrICal == 1)
		{
		TRAP( err_import ,iCalendarService->ImportL( KTestCal2Name.operator()() , KFormatVCal.operator()() , KImportGuidsFile.operator()() ,uIDSet ) );
		}
	else
		{
		TRAP( err_import ,iCalendarService->ImportL( KTestCal2Name.operator()() , KFormatICal.operator()() , KImportGuidsFile.operator()() ,uIDSet ) );
		}
	
	
	if(err_import != KErrNone)
		{
		delete buffer;
		arruids.ResetAndDestroy();
		uIDSet.ResetAndDestroy();
		iResult = err_import;
		return iResult;
		}
		
	TInt count = uIDSet.Count();
	TInt arr_count = arruids.Count() - 2;
	
	if ( arr_count != uIDSet.Count() )	
		iResult = KErrGeneral;
	
	delete buffer;
	arruids.ResetAndDestroy();
	uIDSet.ResetAndDestroy();
	
	RemoveCalendarFile(iCalendarService, KTestCal1Name.operator()());
	RemoveCalendarFile(iCalendarService, KTestCal2Name.operator()());
	
	return iResult;
	}
	
	
TInt CCalImpTestCases::TestImportMultipleEntry()
	{
	iTestCaseType = KImportSync;
	
	RemoveCalendarFile(iCalendarService, KTestCal1Name.operator()());
	
	 AddCalendarFile(iCalendarService, KTestCal1Name.operator()());
	 
	 RemoveCalendarFile(iCalendarService, KTestCal2Name.operator()());
	
	 AddCalendarFile(iCalendarService, KTestCal2Name.operator()());
	
		
	RPointerArray<TUIDSet> arruids;
	
	TUIDSet* uids = NULL;
	TUIDSet* new_uids = NULL;
	
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

	if(AddReminder(iCalendarService, KTestCal2Name.operator()(), new_uids) == KErrNone && new_uids)
		{
		arruids.Append(new_uids);
		new_uids = NULL;
		}

	if(AddAnny(iCalendarService, KTestCal2Name.operator()(), new_uids) == KErrNone && new_uids)
		{
		arruids.Append(new_uids);
		new_uids = NULL;
		}

	if(AddToDo(iCalendarService, KTestCal2Name.operator()(), new_uids) == KErrNone && new_uids)
		{
		arruids.Append(new_uids);
		new_uids = NULL;
		}
	
	delete uids;
	uids = NULL;
	delete new_uids;
	new_uids = NULL;
	
    CCalendarExportParams *expParams = CCalendarExportParams::NewL();
    
    
    
   /* expParams->AddGuidL( *(arruids[0])->iGlobalUID );
    expParams->AddGuidL( *(arruids[4])->iGlobalUID );
    expParams->AddGuidL( *(arruids[3])->iGlobalUID );*/
    expParams->SetExportFileNameL(KImportGuidsFile);
    
    
	HBufC8* buffer = NULL;
	TInt err_export;
	
	if( iVCalOrICal == 1)
		{
		TRAP( err_export ,iCalendarService->ExportL( KTestCal2Name.operator()() , KFormatVCal.operator()() , expParams ,buffer ) );
		}
	else
		{
		TRAP( err_export ,iCalendarService->ExportL( KTestCal2Name.operator()() , KFormatICal.operator()() , expParams ,buffer ) );
		}
		
	if( iVCalOrICal == 1)
		{
		TRAP( err_export ,iCalendarService->ExportL( KTestCal1Name.operator()() , KFormatVCal.operator()() , expParams ,buffer ) );
		}
	else
		{
		TRAP( err_export ,iCalendarService->ExportL( KTestCal1Name.operator()() , KFormatICal.operator()() , expParams ,buffer ) );
		}
	
	delete expParams;	
	
	if(buffer != NULL)
		{
		delete buffer;
		arruids.ResetAndDestroy();
		iResult = KErrGeneral;
		return iResult;
		}
	
	
	RemoveCalendarFile(iCalendarService, KTestCal3Name.operator()());
	
	AddCalendarFile(iCalendarService, KTestCal3Name.operator()());
	
		
	RPointerArray<TUIDSet> uIDSet(5);
	TInt err_import;
	
	if( iVCalOrICal == 1)
		{
		TRAP( err_import ,iCalendarService->ImportL( KTestCal3Name.operator()() , KFormatVCal.operator()() , KImportGuidsFile.operator()() ,uIDSet ) );
		}
	else
		{
		TRAP( err_import ,iCalendarService->ImportL( KTestCal3Name.operator()() , KFormatICal.operator()() , KImportGuidsFile.operator()() ,uIDSet ) );
		}
	
	
	if(err_import != KErrNone)
		{
		delete buffer;
		arruids.ResetAndDestroy();
		uIDSet.ResetAndDestroy();
		iResult = err_import;
		return iResult;
		}
		
	TInt count = uIDSet.Count();
	TInt arr_count = arruids.Count() ;
	
	if ( count != 2 )	
		iResult = KErrGeneral;
	
	delete buffer;
	arruids.ResetAndDestroy();
	uIDSet.ResetAndDestroy();
	
	RemoveCalendarFile(iCalendarService, KTestCal1Name.operator()());
	RemoveCalendarFile(iCalendarService, KTestCal2Name.operator()());
	RemoveCalendarFile(iCalendarService, KTestCal3Name.operator()());
	return iResult;
	}
	
	
	
			
//	
//Whats done here? 
//	Export all the contents of Default System Calender to a buffer using Export of CCalendarService
//	Use the buffer to import them to "importtothiscalender" and the generated guids and luids are outputted to 
//	ImportGuidsOutputAsync.txt and ImportLuidsOutputAsync.txt respectively
//		
void CCalImpTestCases::TestImportUsingGuidAsyncL()
	{
	iTestCaseType = KImportGuidAsync;
	Start();
	}
	
void CCalImpTestCases::TestImportUsingLuidAsyncL()
	{
	iTestCaseType = KImportLuidAsync;
	Start();
	}
	
void CCalImpTestCases::TestImportUsingFileAsyncL()
	{
	iTestCaseType = KImportUsingFileAsync;
	Start();
	}

void CCalImpTestCases::TestImportMultipleEntryAsyncL()
	{
	iTestCaseType = KMultipleImportUsingFileAsync;
	Start();
	}
void CCalImpTestCases::TestImportCaseAsyncL()
	{
	iTestCaseType = KImportAsync;
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
	
	AddCalendarFile(iCalendarService, KTestCal1NameAsync.operator()());
	
	
	RemoveCalendarFile(iCalendarService, KTestCal2NameAsync.operator()());
	
	AddCalendarFile(iCalendarService, KTestCal2NameAsync.operator()());
	
	
	
	

	TUIDSet* uids = NULL;
	TUIDSet* new_uids = NULL;
	
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
		iArruids.Append(new_uids);
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
    
    switch(iTestCaseType)
    {
    	case KImportGuidAsync : 
    							expParams->AddGuidL( *(iArruids[0])->iGlobalUID );
   								expParams->AddGuidL( *(iArruids[4])->iGlobalUID );
   								expParams->AddGuidL( *(iArruids[3])->iGlobalUID );
   								
   								
   								HBufC8* buffer = NULL;
	
								if( iVCalOrICal == 1)
								{
									TRAP( iResult ,iCalendarService->ExportL( KTestCal1NameAsync.operator()() , KFormatVCal.operator()() , expParams ,buffer ) );
								}
								else
								{
									TRAP( iResult ,iCalendarService->ExportL( KTestCal1NameAsync.operator()() , KFormatICal.operator()() , expParams ,buffer ) );
								}
								
								if( iVCalOrICal == 1)
								{
									TRAP( iResult ,iCalendarService->ImportL( KTestCal2NameAsync.operator()() , KFormatVCal.operator()() , *buffer ,this ) );
								}
								else
								{
									TRAP( iResult ,iCalendarService->ImportL( KTestCal2NameAsync.operator()() , KFormatICal.operator()() , *buffer ,this ) );
								}
								delete buffer;
								buffer = NULL;
								break;
		
    	case KImportLuidAsync :
    							expParams->AddLocalUid( iArruids[0]->iLocalUID );
   								expParams->AddLocalUid( iArruids[4]->iLocalUID );
   								
   								  								
   								//HBufC8* buffer = NULL;
								TInt err_exp;
								
								if( iVCalOrICal == 1)
								{
									TRAP( err_exp ,iCalendarService->ExportL( KTestCal1NameAsync.operator()() , KFormatVCal.operator()() , expParams ,buffer ) );
								}
								else
								{
									TRAP( err_exp ,iCalendarService->ExportL( KTestCal1NameAsync.operator()() , KFormatICal.operator()() , expParams ,buffer ) );
								}
								
								if( iVCalOrICal == 1)
								{
									TRAP( iResult ,iCalendarService->ImportL( KTestCal2NameAsync.operator()() , KFormatVCal.operator()() , *buffer ,this ) );
								}
								else
								{
									TRAP( iResult ,iCalendarService->ImportL( KTestCal2NameAsync.operator()() , KFormatICal.operator()() , *buffer ,this ) );
								}
								delete buffer;
								buffer = NULL;
								break;
    							
    						/*	expParams->AddLocalUid( iArruids[2]->iLocalUID );
    							expParams->AddLocalUid( iArruids[4]->iLocalUID );
    							
    							HBufC8* new_buffer = NULL;
	
								if( iVCalOrICal == 1)
								{
									TRAP( iResult ,iCalendarService->ExportL( KTestCal1NameAsync.operator()() , KFormatVCal.operator()() , expParams ,new_buffer ) );
								}
								else
								{
									TRAP( iResult ,iCalendarService->ExportL( KTestCal1NameAsync.operator()() , KFormatICal.operator()() , expParams ,new_buffer ) );
								}
								
								if( iVCalOrICal == 1)
								{
									TRAP( iResult ,iCalendarService->ImportL( KTestCal2NameAsync.operator()() , KFormatVCal.operator()() , *new_buffer ,this ) );
								}
								else
								{
									TRAP( iResult ,iCalendarService->ImportL( KTestCal2NameAsync.operator()() , KFormatICal.operator()() , *new_buffer ,this ) );
								}
								delete new_buffer;
								new_buffer = NULL;
								break; */
								
    	case KImportUsingFileAsync :
								expParams->AddGuidL( *(iArruids[0])->iGlobalUID );
   								expParams->AddGuidL( *(iArruids[4])->iGlobalUID );
   								expParams->AddGuidL( *(iArruids[3])->iGlobalUID );
   								
   								expParams->SetExportFileNameL(KImportAsyncGuidsFile);
   								if( iVCalOrICal == 1)
								{
									TRAP( iResult ,iCalendarService->ExportL( KTestCal1NameAsync.operator()() , KFormatVCal.operator()() , expParams ,buffer ) );
								}
								else
								{
									TRAP( iResult ,iCalendarService->ExportL( KTestCal1NameAsync.operator()() , KFormatICal.operator()() , expParams ,buffer ) );
								}
								
								if( iVCalOrICal == 1)
								{
									TRAP( iResult ,iCalendarService->ImportL( KTestCal2NameAsync.operator()() , KFormatVCal.operator()() , KImportAsyncGuidsFile.operator()() ,this ) );
								}
								else
								{
									TRAP( iResult ,iCalendarService->ImportL( KTestCal2NameAsync.operator()() , KFormatICal.operator()() , KImportAsyncGuidsFile.operator()() ,this ) );
								}
								break;
								
    	case KMultipleImportUsingFileAsync : 
    	
    							RemoveCalendarFile(iCalendarService, KTestCal3NameAsync.operator()());
	
								AddCalendarFile(iCalendarService, KTestCal3NameAsync.operator()());
    							expParams->SetExportFileNameL(KImportAsyncGuidsFile);
    							AddReminder(iCalendarService, KTestCal3NameAsync.operator()(), new_uids);
		
								AddAnny(iCalendarService, KTestCal3NameAsync.operator()(), new_uids);
								if( iVCalOrICal == 1)
								{
									TRAP( iResult ,iCalendarService->ExportL( KTestCal1NameAsync.operator()() , KFormatVCal.operator()() , expParams ,buffer ) );
								}
								else
								{
									TRAP( iResult ,iCalendarService->ExportL( KTestCal1NameAsync.operator()() , KFormatICal.operator()() , expParams ,buffer ) );
								}
								
								if( iVCalOrICal == 1)
								{
									TRAP( iResult ,iCalendarService->ExportL( KTestCal3NameAsync.operator()() , KFormatVCal.operator()() , expParams ,buffer ) );
								}
								else
								{
									TRAP( iResult ,iCalendarService->ExportL( KTestCal3NameAsync.operator()() , KFormatICal.operator()() , expParams ,buffer ) );
								}
								
								if( iVCalOrICal == 1)
								{
									TRAP( iResult ,iCalendarService->ImportL( KTestCal2NameAsync.operator()() , KFormatVCal.operator()() , KImportAsyncGuidsFile.operator()() ,this ) );
								}
								else
								{
									TRAP( iResult ,iCalendarService->ImportL( KTestCal2NameAsync.operator()() , KFormatICal.operator()() , KImportAsyncGuidsFile.operator()() ,this ) );
								}
								
								delete new_uids;
								new_uids = NULL;
								break;
								
    	case KImportAsync :
    							if( iVCalOrICal == 1)
								{
									TRAP( iResult ,iCalendarService->ImportL( KTestCal2NameAsync.operator()() , KFormatVCal.operator()() , KCalName.operator()() ,this ) );
								}
								else
								{
									TRAP( iResult ,iCalendarService->ImportL( KTestCal2NameAsync.operator()() , KFormatICal.operator()() , KCalName.operator()() ,this ) );
								}
								break;
	
    }

	delete expParams;
	delete uids;
	uids = NULL;
	
  		
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
	switch(iTestCaseType)
    {
    	case KImportGuidAsync :
    							TInt count = uIDSet->Count();
    							if ( iArruids.Count() -2 != uIDSet->Count() )	
									iResult = KErrGeneral;
    							uIDSet->ResetAndDestroy();
								
    							break;
    	case KImportLuidAsync :
    							count = uIDSet->Count();
    							if ( iArruids.Count() -3 != uIDSet->Count() )	
									iResult = KErrGeneral;
    							uIDSet->ResetAndDestroy();
								
    							break;
    	case KImportUsingFileAsync :
    							count = uIDSet->Count();
    							if(count != 3)
    								iResult = KErrGeneral;
    							uIDSet->ResetAndDestroy();
							
    							break;
    	case KMultipleImportUsingFileAsync:
    							count = uIDSet->Count();
    							if(count != 2)
    								iResult = KErrGeneral;
    							uIDSet->ResetAndDestroy();
								
    							RemoveCalendarFile(iCalendarService, KTestCal3NameAsync.operator()());
    							break;
    		case KImportAsync : if(iResult != KErrPathNotFound)
    								iResult = KErrGeneral;
    							else 
    								iResult = KErrNone;
    							break;
    }
    
    


	TInt err;
	RemoveCalendarFile(iCalendarService, KTestCal1NameAsync.operator()());
	//RemoveCalendarFile(iCalendarService, KTestCal2NameAsync.operator()());
		
	iWaitSchedular->AsyncStop();
	
	}
