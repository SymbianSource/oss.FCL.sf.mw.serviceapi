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
#include <calentry.h>//for CCalEntry
#include <calinstance.h>

#include "teststartconsolealarmserver.h"

// USER INCLUDE FILES
#include "exportestcases.h"
#include "calendarheader.h"    
#include "calendarservice.h"

    
#include<ASCliClientUtils.h>

_LIT(KCalName                 ,"c:Calendar");

_LIT(KTestCal1Name                 ,"c:testcal1");
_LIT(KTestCal2Name                 ,"c:testcal2");
_LIT(KTestCal3Name                 ,"c:testcal3");


_LIT(KExportAllFileName       ,"C:\\exportAll.txt");
_LIT(KExportAllAsyncFileName  ,"C:\\exportAllAsync.txt");

_LIT(KExportGuidsFileName     ,"C:\\exportForGuids.txt");
_LIT(KExportGuidsAsyncFileName,"C:\\exportForGuidsAsync.txt");

_LIT(KExportLuidsFileName     ,"C:\\exportForLuids.txt");
_LIT(KExportLuidsAsyncFileName,"C:\\exportForLuidsAsync.txt");

_LIT(KICALExportAllFileName       ,"C:\\icalexportAll.txt");
_LIT(KICALExportAllAsyncFileName  ,"C:\\icalexportAllAsync.txt");

_LIT(KICALExportGuidsFileName     ,"C:\\icalexportForGuids.txt");
_LIT(KICALExportGuidsAsyncFileName,"C:\\icalexportForGuidsAsync.txt");

_LIT(KICALExportLuidsFileName     ,"C:\\icalexportForLuids.txt");
_LIT(KICALExportLuidsAsyncFileName,"C:\\icalexportForLuidsAsync.txt");


CCalExpTestCases* CCalExpTestCases::NewL(TInt& aResult,  TInt aVCalOrICal) //1 means VCal else ICal
	{
	CCalExpTestCases* self = new(ELeave)CCalExpTestCases(aResult, aVCalOrICal); //1 means VCal else ICal;
	
	self->ConstructL();
	
	return self;
	}

CCalExpTestCases::~CCalExpTestCases()
	{
	Cancel();
	
	if(iWaitSchedular->IsStarted())
		iWaitSchedular->AsyncStop();
	
	if(iCalendarService)
		delete iCalendarService;
	
	if(iWaitSchedular)
		delete iWaitSchedular;
	
	iArruids.ResetAndDestroy();
	}
	

	

TInt CCalExpTestCases::TestExportCasesL()
	{
	//No need to set it but for the sake of semanitics set to sync value
	iTestCaseType = KExportSync;
	
	RemoveCalendarFile(iCalendarService, KTestCal1Name.operator()());
	
	AddCalendarFile(iCalendarService, KTestCal1Name.operator()());
	
	RemoveCalendarFile(iCalendarService, KTestCal2Name.operator()());
	
	AddCalendarFile(iCalendarService, KTestCal2Name.operator()());	
	
	
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
    
    // export to cal file - default cal
    expParams->SetExportFileNameL(KCalName);
    TInt err_export;
    TInt err_import,count;
    
	HBufC8* buffer = NULL;
	if( iVCalOrICal == 1)
		{
		TRAP( err_export ,iCalendarService->ExportL( KTestCal1Name.operator()() , KFormatVCal.operator()() , expParams ,buffer ) );
		}
	else
		{
		TRAP( err_export ,iCalendarService->ExportL( KTestCal1Name.operator()() , KFormatICal.operator()() , expParams ,buffer ) );
		}
		
	
	if(err_export != KErrPathNotFound)
		iResult = KErrGeneral;

	//set null desc for file name
	
	TRAPD(err_setfile,expParams->SetExportFileNameL(KNullDesC));
	
	if( iVCalOrICal == 1)
		{
		TRAP( err_export ,iCalendarService->ExportL( KTestCal1Name.operator()() , KFormatVCal.operator()() , expParams ,buffer ) );
		}
	else
		{
		TRAP( err_export ,iCalendarService->ExportL( KTestCal1Name.operator()() , KFormatICal.operator()() , expParams ,buffer ) );
		}

	
	
	RPointerArray<TUIDSet> uSet(5);
	expParams->SetExportFileNameL(KExportGuidsFileName);
	
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
		TRAP( err_import ,iCalendarService->ImportL( KTestCal2Name.operator()() , KFormatVCal.operator()() , KExportGuidsFileName.operator()() ,uSet ) );
	}
	else
	{
		TRAP( err_import ,iCalendarService->ImportL( KTestCal2Name.operator()() , KFormatICal.operator()() , KExportGuidsFileName.operator()() ,uSet ) );
	}
	
	count = uSet.Count();
	uSet.ResetAndDestroy();
	
	
	if( iVCalOrICal == 1)
	{
		TRAP( err_import ,iCalendarService->ImportL( KTestCal2Name.operator()() , KFormatVCal.operator()() , *buffer ,uSet ) );
	}
	else
	{
		TRAP( err_import ,iCalendarService->ImportL( KTestCal2Name.operator()() , KFormatICal.operator()() , *buffer ,uSet ) );
	}
	
	TInt new_count = uSet.Count();
	
	if(count != new_count)
		iResult = KErrGeneral;
	
	if(buffer != NULL)
	{
		delete buffer;
		buffer = NULL;
	}	
	
	delete expParams;
	arruids.ResetAndDestroy();
	uSet.ResetAndDestroy();
	delete uids;
	uids = NULL;
	
	RemoveCalendarFile(iCalendarService, KTestCal1Name.operator()());	
	
	return iResult;
	
	}
			



TInt CCalExpTestCases::TestExportForGuidsL()
	{
		TInt cells = User::CountAllocCells();
	
		
	//No need to set it but for the sake of semanitics set to sync value
	iTestCaseType = KExportSync;
    
    RemoveCalendarFile(iCalendarService, KTestCal1Name.operator()());
	
	AddCalendarFile(iCalendarService, KTestCal1Name.operator()());
	
	RemoveCalendarFile(iCalendarService, KTestCal2Name.operator()());
	
	AddCalendarFile(iCalendarService, KTestCal2Name.operator()());		

	
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
    CCalendarExportParams *new_expParams = CCalendarExportParams::NewL();
    
    TInt count = arruids.Count() -1 ;
    
    expParams->AddGuidL( (arruids[0]->iGlobalUID)->Des() );
    expParams->AddGuidL( (arruids[1]->iGlobalUID)->Des() );
    
    	
    count =0;	   
      	
    
	HBufC8* buffer = NULL;
	HBufC8* new_buffer = NULL;
	
	TInt err_export;
	if( iVCalOrICal == 1)
		{
		TRAP( err_export ,iCalendarService->ExportL( KTestCal1Name.operator()() , KFormatVCal.operator()() , expParams ,buffer ) );
		}
	else
		{
		TRAP( err_export ,iCalendarService->ExportL( KTestCal1Name.operator()() , KFormatICal.operator()() , expParams ,buffer ) );
		}
	
	expParams->AddGuidL( (arruids[2]->iGlobalUID)->Des() );
	
	delete buffer;
	buffer = NULL;
	
	if( iVCalOrICal == 1)
		{
		TRAP( err_export ,iCalendarService->ExportL( KTestCal1Name.operator()() , KFormatVCal.operator()() , expParams ,new_buffer ) );
		}
	else
		{
		TRAP( err_export ,iCalendarService->ExportL( KTestCal1Name.operator()() , KFormatICal.operator()() , expParams ,new_buffer ) );
		} 
	
	RemoveCalendarFile(iCalendarService, KTestCal2Name.operator()());
	
	AddCalendarFile(iCalendarService, KTestCal2Name.operator()());
	
	
	RPointerArray<TUIDSet> uIDSet(5);
	TInt err_import;
	
	if( iVCalOrICal == 1)
		{
		TRAP( err_import ,iCalendarService->ImportL( KTestCal2Name.operator()() , KFormatVCal.operator()() , *new_buffer ,uIDSet ) );
		}
	else
		{
		TRAP( err_import ,iCalendarService->ImportL( KTestCal2Name.operator()() , KFormatICal.operator()() , *new_buffer ,uIDSet ) );
		}
		

	count = uIDSet.Count();
	if(count != 3)
		iResult = KErrGeneral;
	
//	count =0;
	uIDSet.ResetAndDestroy();
	delete new_buffer;
	new_buffer = NULL;

	err_export = KErrNone;
	err_import = KErrNone;
	
	new_expParams->SetExportFileNameL(KExportGuidsFileName);
	
	new_expParams->AddGuidL( (arruids[0]->iGlobalUID)->Des() );
    new_expParams->AddGuidL( (arruids[1]->iGlobalUID)->Des() );
    
    if( iVCalOrICal == 1)
		{
		TRAP( err_export ,iCalendarService->ExportL( KTestCal1Name.operator()() , KFormatVCal.operator()() , new_expParams ,buffer ) );
		}
	else
		{
		TRAP( err_export ,iCalendarService->ExportL( KTestCal1Name.operator()() , KFormatICal.operator()() , new_expParams ,buffer ) );
		}
		
	
	new_expParams->AddGuidL( (arruids[2]->iGlobalUID)->Des() );	
	new_expParams->SetExportFileNameL(KExportGuidsFileName);
	
	if( iVCalOrICal == 1)
		{
		TRAP( err_export ,iCalendarService->ExportL( KTestCal1Name.operator()() , KFormatVCal.operator()() , new_expParams ,new_buffer ) );
		}
	else
		{
		TRAP( err_export ,iCalendarService->ExportL( KTestCal1Name.operator()() , KFormatICal.operator()() , new_expParams ,new_buffer ) );
		}
		
		
	
	if( iVCalOrICal == 1)
		{
		TRAP( err_import ,iCalendarService->ImportL( KTestCal2Name.operator()() , KFormatVCal.operator()() , KExportGuidsFileName.operator()() ,uIDSet ) );
		}
	else
		{
		TRAP( err_import ,iCalendarService->ImportL( KTestCal2Name.operator()() , KFormatICal.operator()() , KExportGuidsFileName.operator()() ,uIDSet ) );
		}
		
		
	TInt new_count = uIDSet.Count();		
	
	if(count != new_count && iResult == KErrNone)
		iResult = KErrGeneral; 

	
	if(buffer)
		delete buffer;
	if(new_buffer)
		delete new_buffer;
	    
	delete expParams;
	delete new_expParams;
	arruids.ResetAndDestroy();
	uIDSet.ResetAndDestroy();
	delete uids;    
    uids = NULL;
	arruids.Close() ;
	uIDSet.Close() ;	
	RemoveCalendarFile(iCalendarService, KTestCal1Name.operator()());
	RemoveCalendarFile(iCalendarService, KTestCal2Name.operator()());
	
	cells = User::CountAllocCells();
	
	return iResult;
	
	}
	



	
TInt CCalExpTestCases::TestExportForLuidsL()
	{
		//No need to set it but for the sake of semanitics set to sync value
	iTestCaseType = KExportSync;
    
     RemoveCalendarFile(iCalendarService, KTestCal1Name.operator()());
	
	iResult = AddCalendarFile(iCalendarService, KTestCal1Name.operator()());
	
	RemoveCalendarFile(iCalendarService, KTestCal2Name.operator()());
	
	AddCalendarFile(iCalendarService, KTestCal2Name.operator()());		

	
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
    
    TInt count = arruids.Count();
    for(TInt index = 0; index < count; ++index)
    	{
    	expParams->AddLocalUid( (arruids[index]->iLocalUID) );
    	}
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




void CCalExpTestCases::TestExportForGuidsBufAsyncL()
	{
	iTestCaseType = KExportForGuidsBufAsync;
	Start();
	
	}


	
void CCalExpTestCases::TestExportForGuidsFileAsyncL()	
	{
	iTestCaseType = KExportForGuidsFileAsync;	
	Start();
	}

void CCalExpTestCases::TestExportForLuidAsyncL()	
	{
	iTestCaseType = KExportAllAsyncVCAL;	
	Start();
	}
	
void CCalExpTestCases::TestExportCaseAsyncL()	
	{
	iTestCaseType = KExportAllAsync;	
	Start();
	}




TInt CCalExpTestCases::Result()
	{
	return iResult;
	}
	
void CCalExpTestCases::ConstructL()
	{	
	iCalendarService = CCalendarService::NewL();
	
	iWaitSchedular = new(ELeave) CActiveSchedulerWait();
	}
	
CCalExpTestCases::CCalExpTestCases(TInt& aResult, TInt aVCalOrICal ) : 
								CActive(EPriorityStandard), iResult( aResult ) ,
														 iVCalOrICal(aVCalOrICal)
	{

	}
	
//for the sake of ActiveObject
void CCalExpTestCases::DoCancel()
	{
	
	}

void CCalExpTestCases::RunL()
	{
	RemoveCalendarFile(iCalendarService, KTestCal1Name.operator()());
	
	iResult = AddCalendarFile(iCalendarService, KTestCal1Name.operator()());
	
	if(iResult != KErrNone)
		goto Final;

	TUIDSet* uids = NULL;
	
	if(AddAppointment(iCalendarService, KTestCal1Name.operator()(), uids) == KErrNone && uids)
		{
		iArruids.Append(uids);
		uids = NULL;
		}

	if(AddEvent(iCalendarService, KTestCal1Name.operator()(), uids) == KErrNone && uids)
		{
		iArruids.Append(uids);
		uids = NULL;
		}

	if(AddReminder(iCalendarService, KTestCal1Name.operator()(), uids) == KErrNone && uids)
		{
		iArruids.Append(uids);
		uids = NULL;
		}

	if(AddAnny(iCalendarService, KTestCal1Name.operator()(), uids) == KErrNone && uids)
		{
		iArruids.Append(uids);
		uids = NULL;
		}

	if(AddToDo(iCalendarService, KTestCal1Name.operator()(), uids) == KErrNone && uids)
		{
		iArruids.Append(uids);
		uids = NULL;
		}
	
	delete uids;
	uids = NULL;
    CCalendarExportParams *expParams = CCalendarExportParams::NewL();

	TInt count;
	
	switch( iTestCaseType )
		{
			case KExportAllAsyncVCAL:		
									if( iVCalOrICal == 1)
										{
										TRAP( iResult, iCalendarService->ExportL( KTestCal1Name.operator()() , KFormatVCal.operator()() , expParams , this ));
										}
									else
										{
										TRAP( iResult, iCalendarService->ExportL( KTestCal1Name.operator()() , KFormatICal.operator()() , expParams , this ));
										}
																			
										break;
										
			case KExportForGuidsBufAsync:	
										count = iArruids.Count();
									    for(TInt index = 0; index < count; ++index)
									    	{
									    	expParams->AddGuidL( (iArruids[index]->iGlobalUID)->Des() );
									    	}										

									if( iVCalOrICal == 1)
										{
										TRAP( iResult, iCalendarService->ExportL( KTestCal1Name.operator()() , KFormatVCal.operator()() , expParams, this ) );
										}
									else
										{
										TRAP( iResult, iCalendarService->ExportL( KTestCal1Name.operator()() , KFormatICal.operator()() , expParams, this ) );
										}	
						
										break;
										
			case KExportForGuidsFileAsync:	
										count = iArruids.Count();
									    for(TInt index = 0; index < count; ++index)
									    	{
									    	expParams->AddLocalUid( (iArruids[index]->iLocalUID) );
									    	}
									    	
									    expParams->SetExportFileNameL(KExportGuidsAsyncFileName);
									if( iVCalOrICal == 1)
										{
										TRAP( iResult, iCalendarService->ExportL( KTestCal1Name.operator()() , KFormatVCal.operator()() , expParams, this ) );
										}
									else
										{
										TRAP( iResult, iCalendarService->ExportL( KTestCal1Name.operator()() , KFormatICal.operator()() , expParams, this ) );
										}	
					
										break;
										
		 	case KExportAllAsync :
		 							expParams->SetExportFileNameL(KCalName);
									if( iVCalOrICal == 1)
										{
										TRAP( iResult, iCalendarService->ExportL( KTestCal1Name.operator()() , KFormatVCal.operator()() , expParams , this ));
										}
									else
										{
										TRAP( iResult, iCalendarService->ExportL( KTestCal1Name.operator()() , KFormatICal.operator()() , expParams , this ));
										}
																			
										break;
		}
	delete expParams;	
Final:		;
	}
			
void CCalExpTestCases::Start()
	{
	CActiveScheduler::Add(this);
	
	SetActive();
	
	TRequestStatus* temp = &iStatus;
	
	User::RequestComplete(temp, KErrNone);
	
	iWaitSchedular->Start();	
	}

			
void CCalExpTestCases::NotifyResultL(TInt aErrCode, TAny* aResult)
	{
	//******************* set iResult ****************************
	iResult = aErrCode;

	
	//******************* set iResult ****************************
	
	
	RemoveCalendarFile(iCalendarService, KTestCal2Name.operator()());
	
	AddCalendarFile(iCalendarService, KTestCal2Name.operator()());
	TInt count;
	
	
	RPointerArray<TUIDSet> uSet(5);
	
	switch(iTestCaseType)
	{
		case KExportForGuidsBufAsync: 
									if( iVCalOrICal == 1)
									{
										TRAP( iResult ,iCalendarService->ImportL( KTestCal2Name.operator()() , KFormatVCal.operator()() , *(HBufC8*)aResult ,uSet ) );
									}
									else
									{
										TRAP( iResult ,iCalendarService->ImportL( KTestCal2Name.operator()() , KFormatICal.operator()() , *(HBufC8*)aResult ,uSet ) );
									}
									count = uSet.Count();
									if(count != 5)
										iResult = KErrGeneral;
									break;
		case KExportForGuidsFileAsync: 
									if( iVCalOrICal == 1)
									{
										TRAP( iResult ,iCalendarService->ImportL( KTestCal2Name.operator()() , KFormatVCal.operator()() , KExportGuidsAsyncFileName.operator()() ,uSet ) );
									}
									else
									{
										TRAP( iResult ,iCalendarService->ImportL( KTestCal2Name.operator()() , KFormatICal.operator()() , KExportGuidsAsyncFileName.operator()() ,uSet ) );
									}
									count = uSet.Count();
									if(count != 5)
										iResult = KErrGeneral;
									break;
									
		case KExportAllAsyncVCAL :
									if( iVCalOrICal == 1)
									{
										TRAP( iResult ,iCalendarService->ImportL( KTestCal2Name.operator()() , KFormatVCal.operator()() , *(HBufC8*)aResult ,uSet ) );
									}
									else
									{
										TRAP( iResult ,iCalendarService->ImportL( KTestCal2Name.operator()() , KFormatICal.operator()() , *(HBufC8*)aResult ,uSet ) );
									}
									count = uSet.Count();
									if(count != 5)
										iResult = KErrGeneral;
									break;
									
		case KExportAllAsync :
								if(iResult != KErrPathNotFound)
									iResult = KErrGeneral;
								else
									iResult = KErrNone;
										
	}
	
	
	uSet.ResetAndDestroy();	
	
	
	RemoveCalendarFile(iCalendarService, KTestCal1Name.operator()());
	RemoveCalendarFile(iCalendarService, KTestCal2Name.operator()());
		
	iWaitSchedular->AsyncStop();
	}

