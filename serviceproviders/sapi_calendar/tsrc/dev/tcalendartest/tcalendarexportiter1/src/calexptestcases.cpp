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
#include "calexptestcases.h"
#include "calendarheader.h"    
#include "calendarservice.h"

    
#include<ascliclientutils.h>



_LIT(KCalName                 ,"c:Calendar");

_LIT(KTestCal1Name                 ,"c:testcal1");
_LIT(KTestCal2Name                 ,"c:testcal2");


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
	

//	
//Whats done here? 
//	Export all the entries of default system calendar to exportall.txt file	
//
TInt CCalExpTestCases::TestExportAllL()
	{
	//No need to set it but for the sake of semanitics set to sync value
	iTestCaseType = KExportSync;
	
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
//	Get the List of GUIDS of entries of the Default system Calender Using GetList of CCalendarService
//	Then Export the entries corresponding to GUIDS to exportforguids.txt
//
TInt CCalExpTestCases::TestExportForGuidsL()
	{
	//No need to set it but for the sake of semanitics set to sync value
	iTestCaseType = KExportSync;
    
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
    
    TInt count = arruids.Count();
    for(TInt index = 0; index < count; ++index)
    	{
    	expParams->AddGuidL( (arruids[index]->iGlobalUID)->Des() );
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
	


//	
//Whats done here? 
//	Get the List of LUIDS of entries of the Default system Calender Using GetList of CCalendarService
//	Then Export the entries corresponding to LUIDS to exportforluids.txt
//	
TInt CCalExpTestCases::TestExportForLuidsL()
	{
		//No need to set it but for the sake of semanitics set to sync value
	iTestCaseType = KExportSync;
    
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



//	
//Whats done here?  
//	Get the List of GUIDS of entries of the Default system Calender Using GetList of CCalendarService
//	Then Export the entries aynchronously corresponding to GUIDS to exportforguidsasync.txt
//
//Asynchronous test case so setting the iTestCaseType as it is to be handled in RunL
void CCalExpTestCases::TestExportForGuidsAsyncL()
	{
	iTestCaseType = KExportForGuidsAsync;
	Start();
	
	}

//	
//Whats done here?  
//	Export all the entries of default system calendar asynchronously to exportallaync.txt file
//
//Asynchronous test case so setting the iTestCaseType as it is to be handled in RunL	
void CCalExpTestCases::TestExportAllAsyncL()
	{
	iTestCaseType = KExportAllAsync;
	Start();
	}


//	
//Whats done here?  
//	Get the List of GUIDS of entries of the Default system Calender Using GetList of CCalendarService
//	Then Export the entries aynchronously corresponding to GUIDS to exportforguidsasync.txt
//
//Asynchronous test case so setting the iTestCaseType as it is to be handled in RunL	
void CCalExpTestCases::TestExportForLuidsAsyncL()	
	{
	iTestCaseType = KExportForLuidsAsync;	
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
	
	
    CCalendarExportParams *expParams = CCalendarExportParams::NewL();

	TInt count;
	
	switch( iTestCaseType )
		{
			case KExportAllAsync:		
									if( iVCalOrICal == 1)
										{
										TRAP( iResult, iCalendarService->ExportL( KTestCal1Name.operator()() , KFormatVCal.operator()() , expParams , this ));
										}
									else
										{
										TRAP( iResult, iCalendarService->ExportL( KTestCal1Name.operator()() , KFormatICal.operator()() , expParams , this ));
										}
																			
										break;
										
			case KExportForGuidsAsync:	
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
										
			case KExportForLuidsAsync:	
										count = iArruids.Count();
									    for(TInt index = 0; index < count; ++index)
									    	{
									    	expParams->AddLocalUid( (iArruids[index]->iLocalUID) );
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

	if(iResult != KErrNone)
		goto EndPoint;
	
	//******************* set iResult ****************************
	
	
	RemoveCalendarFile(iCalendarService, KTestCal2Name.operator()());
	
	iResult = AddCalendarFile(iCalendarService, KTestCal2Name.operator()());
	
	if(iResult != KErrNone)
		goto EndPoint;
	
	RPointerArray<TUIDSet> uSet(5);
	
	if( iVCalOrICal == 1)
		{
		TRAP( iResult ,iCalendarService->ImportL( KTestCal2Name.operator()() , KFormatVCal.operator()() , *(HBufC8*)aResult ,uSet ) );
		}
	else
		{
		TRAP( iResult ,iCalendarService->ImportL( KTestCal2Name.operator()() , KFormatICal.operator()() , *(HBufC8*)aResult ,uSet ) );
		}
	
	
	if(iResult != KErrNone)
		{
		uSet.ResetAndDestroy();
		goto EndPoint;
		}
		
	if ( iArruids.Count() != uSet.Count() )	
		iResult = KErrGeneral;
	

	uSet.ResetAndDestroy();


EndPoint:	
	RemoveCalendarFile(iCalendarService, KTestCal1Name.operator()());
	RemoveCalendarFile(iCalendarService, KTestCal2Name.operator()());
		
	iWaitSchedular->AsyncStop();
	}
