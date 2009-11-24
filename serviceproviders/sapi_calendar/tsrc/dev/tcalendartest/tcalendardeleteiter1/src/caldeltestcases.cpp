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
#include <calinstanceview.h>//for CCalInstance
#include <calcommon.h>//for Filter Type Enum Constants
#include <calinstance.h>
#include <caltime.h>
 
// USER INCLUDE FILES
#include "caldeltestcases.h"
#include "calendarheader.h"    
#include "calendarservice.h"
#include "entryattributes.h"    
#include<ascliclientutils.h>

#include "teststartconsolealarmserver.h"





_LIT(KCalName                 ,"c:Calendar");



CCalDelTestCases* CCalDelTestCases::NewL( TInt& aResult) //1 means VCal else ICal
	{
	CCalDelTestCases* self = new(ELeave)CCalDelTestCases( aResult); //1 means VCal else ICal;
	
	self->ConstructL();
	
	return self;
	}

CCalDelTestCases::~CCalDelTestCases()
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
	

_LIT(KDelTestCalNameDeleteCal ,"c:deletecalendarcasecal");	
			
TInt CCalDelTestCases::TestDeleteCalendarL()
	{
	//No need to set it but for the sake of semanitics set to sync value
	iTestCaseType = KDeleteSync;
	
	TRAP( iResult , iCalendarService->AddL( KDelTestCalNameDeleteCal.operator()() ) );
	
	if( iResult == KErrNone )
		{
		TRAP( iResult ,iCalendarService->DeleteL( KDelTestCalNameDeleteCal.operator()() ) );
		}

	return iResult;
	}
			

TInt CCalDelTestCases::TestDeleteDefaultCalendarL()
	{
	//No need to set it but for the sake of semanitics set to sync value
	iTestCaseType = KDeleteSync;
	
	TRAP( iResult , iCalendarService->DeleteL( KCalName.operator()()  ) );
	
	if( iResult == KErrNotSupported )
		iResult = KErrNone;

	return iResult;
	}
	
_LIT(KDelTestCalNameDeleteAll ,"c:deleteallcal");

TInt CCalDelTestCases::TestDeleteAllEntriesL()
	{
	//No need to set it but for the sake of semanitics set to sync value
	iTestCaseType = KDeleteSync;
	
	RemoveCalendarFile(iCalendarService, KDelTestCalNameDeleteAll.operator()());
	
	TRAP( iResult , iCalendarService->AddL( KDelTestCalNameDeleteAll.operator()() ) );
	
	if( iResult == KErrNone )
		{			
		addSomeEntries( KDelTestCalNameDeleteAll.operator()() );//adds the entries and fills up iArruids with UIDSets
		


		CCalendarFilter *getListfilter1 = CCalendarFilter::NewL();
	
		RPointerArray<CCalInstance> calInstanceArray;
	
		getListfilter1->SetFilterTypeL( KIncludeAll );
	
		iCalendarService->GetListL( KDelTestCalNameDeleteAll.operator()(), getListfilter1 , calInstanceArray );		
		
		if ( calInstanceArray.Count() == 0 )
			{
			iResult = KErrGeneral;
		
			calInstanceArray.ResetAndDestroy();
			
			return iResult;
			}
		
		delete getListfilter1;	
	
	
		CCalendarFilter *filter = CCalendarFilter::NewL();
		
		filter->SetDeleteAll( ETrue );
		
		TRAP( iResult, iCalendarService->DeleteL( KDelTestCalNameDeleteAll.operator()() , filter , NULL) );

		delete filter;			
		
		
		CCalendarFilter *getListfilter2 = CCalendarFilter::NewL();
	
		RPointerArray<CCalInstance> calInstanceArray2;
	
		getListfilter2->SetFilterTypeL( KIncludeAll );
	
		iCalendarService->GetListL( KDelTestCalNameDeleteAll.operator()(), getListfilter2 , calInstanceArray2 );		
		
		delete getListfilter2;			
 
 		if ( calInstanceArray2.Count() != 0 )
			{
			iResult = KErrGeneral;
			}
		calInstanceArray.ResetAndDestroy();
		
		calInstanceArray2.ResetAndDestroy();
		}
	RemoveCalendarFile(iCalendarService, KDelTestCalNameDeleteAll.operator()());
	
	return iResult;
	}
	
	
	
_LIT(KDelTestCalNameDeleteForGuids ,"c:deleteforGuidscal");

TInt CCalDelTestCases::TestDeleteUsingGUidL()
	{
	//No need to set it but for the sake of semanitics set to sync value
	iTestCaseType = KDeleteSync;
	
	RemoveCalendarFile(iCalendarService, KDelTestCalNameDeleteForGuids.operator()());
	
	TRAP( iResult , iCalendarService->AddL( KDelTestCalNameDeleteForGuids.operator()() ) );
	
	if( iResult == KErrNone )
		{			
		addSomeEntries( KDelTestCalNameDeleteForGuids.operator()() );//adds the entries and fills up iArruids with UIDSets
		


		CCalendarFilter *getListfilter1 = CCalendarFilter::NewL();
	
		RPointerArray<CCalInstance> calInstanceArray;
	
		getListfilter1->SetFilterTypeL( KIncludeAll );
	
		iCalendarService->GetListL( KDelTestCalNameDeleteForGuids.operator()(), getListfilter1 , calInstanceArray );		
		
		delete getListfilter1;
		
		if ( calInstanceArray.Count() == 0 )
			{
			iResult = KErrGeneral;
		
			calInstanceArray.ResetAndDestroy();
			
			return iResult;
			}
	
	
		CCalendarFilter *filter = CCalendarFilter::NewL();
		
		for( TInt x = 0; x < iArruids.Count(); ++x )
			{
			filter->AddGuidL( *(iArruids[x])->iGlobalUID );
			}
		
		TRAP( iResult, iCalendarService->DeleteL( KDelTestCalNameDeleteForGuids.operator()() , filter , NULL) );

		delete filter;		
		
		
		CCalendarFilter *getListfilter2 = CCalendarFilter::NewL();
	
		RPointerArray<CCalInstance> calInstanceArray2;
	
		getListfilter2->SetFilterTypeL( KIncludeAll );
	
		iCalendarService->GetListL( KDelTestCalNameDeleteForGuids.operator()(), getListfilter2 , calInstanceArray2 );		
		
		delete getListfilter2;		

		if ( calInstanceArray2.Count() != 0 )
			{
			iResult = KErrGeneral;
			}
		calInstanceArray.ResetAndDestroy();
		
		calInstanceArray2.ResetAndDestroy();
		}
	RemoveCalendarFile(iCalendarService, KDelTestCalNameDeleteForGuids.operator()());
	
	return iResult;
	}



_LIT(KDelTestCalNameDeleteForLuids ,"c:deleteforLuidscal");

//Asynchronous test cases so setting the iTestCaseType as it is to be handled in RunL
TInt CCalDelTestCases::TestDeleteUsingLocalUidL()
	{
		//No need to set it but for the sake of semanitics set to sync value
	iTestCaseType = KDeleteSync;
	
	RemoveCalendarFile(iCalendarService, KDelTestCalNameDeleteForLuids.operator()());
	
	TRAP( iResult , iCalendarService->AddL( KDelTestCalNameDeleteForLuids.operator()() ) );
	
	if( iResult == KErrNone )
		{			
		addSomeEntries( KDelTestCalNameDeleteForLuids.operator()() );//adds the entries and fills up iArruids with UIDSets
		


		CCalendarFilter *getListfilter1 = CCalendarFilter::NewL();
	
		RPointerArray<CCalInstance> calInstanceArray;
	
		getListfilter1->SetFilterTypeL( KIncludeAll );
	
		iCalendarService->GetListL( KDelTestCalNameDeleteForLuids.operator()(), getListfilter1 , calInstanceArray );		
		
		delete getListfilter1;
		
		if ( calInstanceArray.Count() == 0 )
			{
			iResult = KErrGeneral;
		
			calInstanceArray.ResetAndDestroy();
			
			return iResult;
			}
	
	
		CCalendarFilter *filter = CCalendarFilter::NewL();
		
		for( TInt x = 0; x < iArruids.Count(); ++x )
			{
			filter->AddLocalUid( (iArruids[x])->iLocalUID );
			}
		
		TRAP( iResult, iCalendarService->DeleteL( KDelTestCalNameDeleteForLuids.operator()() , filter , NULL) );

		delete filter;		
		
		
		CCalendarFilter *getListfilter2 = CCalendarFilter::NewL();
	
		RPointerArray<CCalInstance> calInstanceArray2;
	
		getListfilter2->SetFilterTypeL( KIncludeAll );
	
		iCalendarService->GetListL( KDelTestCalNameDeleteForLuids.operator()(), getListfilter2 , calInstanceArray2 );		
		
		if ( calInstanceArray2.Count() != 0 )
			{
			iResult = KErrGeneral;
			}
		calInstanceArray.ResetAndDestroy();
		
		calInstanceArray2.ResetAndDestroy();
		
		delete filter;
		}
	RemoveCalendarFile(iCalendarService, KDelTestCalNameDeleteForLuids.operator()());
	
	return iResult;
	}

_LIT(KDelTestCalNameDeleteForLuidsAndTm ,"c:deleteforLuidsAndTmcal");
	
TInt CCalDelTestCases::TestDeleteTmRgLocalUidL()
	{
		//No need to set it but for the sake of semanitics set to sync value
	iTestCaseType = KDeleteSync;
	
	RemoveCalendarFile(iCalendarService, KDelTestCalNameDeleteForLuidsAndTm.operator()());
	
	TRAP( iResult , iCalendarService->AddL( KDelTestCalNameDeleteForLuidsAndTm.operator()() ) );
	
	if( iResult == KErrNone )
		{			
		addSomeEntries( KDelTestCalNameDeleteForLuidsAndTm.operator()() );//adds the entries and fills up iArruids with UIDSets
		


		CCalendarFilter *getListfilter1 = CCalendarFilter::NewL();
	
		RPointerArray<CCalInstance> calInstanceArray;
	
		getListfilter1->SetFilterTypeL( KIncludeAll );
	
		iCalendarService->GetListL( KDelTestCalNameDeleteForLuidsAndTm.operator()(), getListfilter1 , calInstanceArray );		
		
		delete getListfilter1;
		
		if ( calInstanceArray.Count() == 0 )
			{
			iResult = KErrGeneral;
		
			calInstanceArray.ResetAndDestroy();
			
			return iResult;
			}
	
	
		CCalendarFilter *filter = CCalendarFilter::NewL();
		
		for( TInt x = 0; x < iArruids.Count(); ++x )
			{
			filter->AddLocalUid( (iArruids[x])->iLocalUID );
			}
		
		
		filter->SetStartTimeL( TTime(TDateTime(2005, EDecember, 30, 0, 0, 0, 0)) );
		
		filter->SetEndTimeL( TTime(TDateTime(2100, EDecember, 30, 0, 0, 0, 0)) );
		
		TRAP( iResult, iCalendarService->DeleteL( KDelTestCalNameDeleteForLuidsAndTm.operator()() , filter , NULL) );

		delete filter;
		
		
		CCalendarFilter *getListfilter2 = CCalendarFilter::NewL();
	
		RPointerArray<CCalInstance> calInstanceArray2;
	
		getListfilter2->SetFilterTypeL( KIncludeAll );
	
		iCalendarService->GetListL( KDelTestCalNameDeleteForLuidsAndTm.operator()(), getListfilter2 , calInstanceArray2 );		
		
		if ( calInstanceArray2.Count() != 0 )
			{
			iResult = KErrGeneral;
			}
		calInstanceArray.ResetAndDestroy();
		
		calInstanceArray2.ResetAndDestroy();
		
		delete getListfilter2;
		}
	RemoveCalendarFile(iCalendarService, KDelTestCalNameDeleteForLuidsAndTm.operator()());
	
	return iResult;	
	}



_LIT(KDelTestCalNameDeleteForGuidsAndTm ,"c:deleteforGuidsAndTmcal");
	
TInt CCalDelTestCases::TestDeleteTmRgGUidL()	
	{
		//No need to set it but for the sake of semanitics set to sync value
	iTestCaseType = KDeleteSync;
	
	RemoveCalendarFile(iCalendarService, KDelTestCalNameDeleteForGuidsAndTm.operator()());
	
	TRAP( iResult , iCalendarService->AddL( KDelTestCalNameDeleteForGuidsAndTm.operator()() ) );
	
	if( iResult == KErrNone )
		{			
		addSomeEntries( KDelTestCalNameDeleteForGuidsAndTm.operator()() );//adds the entries and fills up iArruids with UIDSets
		


		CCalendarFilter *getListfilter1 = CCalendarFilter::NewL();
	
		RPointerArray<CCalInstance> calInstanceArray;
	
		getListfilter1->SetFilterTypeL( KIncludeAll );
	
		iCalendarService->GetListL( KDelTestCalNameDeleteForGuidsAndTm.operator()(), getListfilter1 , calInstanceArray );		

		delete getListfilter1;
		
		if ( calInstanceArray.Count() == 0 )
			{
			iResult = KErrGeneral;
		
			calInstanceArray.ResetAndDestroy();
			
			return iResult;
			}
	
	
		CCalendarFilter *filter = CCalendarFilter::NewL();
		
		for( TInt x = 0; x < iArruids.Count(); ++x )
			{
			filter->AddGuidL( *(iArruids[x])->iGlobalUID );
			}
		
		filter->SetStartTimeL( TTime(TDateTime(2005, EDecember, 30, 0, 0, 0, 0)) );
		
		filter->SetEndTimeL( TTime(TDateTime(2100, EDecember, 30, 0, 0, 0, 0)) );
		
		TRAP( iResult, iCalendarService->DeleteL( KDelTestCalNameDeleteForGuidsAndTm.operator()() , filter , NULL) );

		delete filter;
		
		
		
		CCalendarFilter *getListfilter2 = CCalendarFilter::NewL();
	
		RPointerArray<CCalInstance> calInstanceArray2;
	
		getListfilter2->SetFilterTypeL( KIncludeAll );
	
		iCalendarService->GetListL( KDelTestCalNameDeleteForGuidsAndTm.operator()(), getListfilter2 , calInstanceArray2 );		
		
		if ( calInstanceArray2.Count() != 0 )
			{
			iResult = KErrGeneral;
			}
		calInstanceArray.ResetAndDestroy();
		
		calInstanceArray2.ResetAndDestroy();
		delete getListfilter2;
		}
	RemoveCalendarFile(iCalendarService, KDelTestCalNameDeleteForGuidsAndTm.operator()());
	
	return iResult;		
	}



_LIT(KDelTestCalNameDeleteForTm ,"c:deleteforTmcal");	
	
TInt CCalDelTestCases::TestDeleteTmRgL()	
	{
		//No need to set it but for the sake of semanitics set to sync value
	iTestCaseType = KDeleteSync;
	
	RemoveCalendarFile(iCalendarService, KDelTestCalNameDeleteForTm.operator()());
	
	TRAP( iResult , iCalendarService->AddL( KDelTestCalNameDeleteForTm.operator()() ) );
	
	if( iResult == KErrNone )
		{			
		addSomeEntries( KDelTestCalNameDeleteForTm.operator()() );//adds the entries and fills up iArruids with UIDSets
		


		CCalendarFilter *getListfilter1 = CCalendarFilter::NewL();
	
		RPointerArray<CCalInstance> calInstanceArray;
	
		getListfilter1->SetFilterTypeL( KIncludeAll );
	
		iCalendarService->GetListL( KDelTestCalNameDeleteForTm.operator()(), getListfilter1 , calInstanceArray );		
		
		delete getListfilter1;

		if ( calInstanceArray.Count() == 0 )
			{
			iResult = KErrGeneral;
		
			calInstanceArray.ResetAndDestroy();
			
			return iResult;
			}
	
	
	
		CCalendarFilter *filter = CCalendarFilter::NewL();

		filter->SetStartTimeL( TTime(TDateTime(2005, EDecember, 30, 0, 0, 0, 0)) );
		
		filter->SetEndTimeL( TTime(TDateTime(2100, EDecember, 30, 0, 0, 0, 0)) );
		
		TRAP( iResult, iCalendarService->DeleteL( KDelTestCalNameDeleteForTm.operator()() , filter , NULL) );

		
		delete filter;
	
		
		CCalendarFilter *getListfilter2 = CCalendarFilter::NewL();
	
		RPointerArray<CCalInstance> calInstanceArray2;
	
		getListfilter2->SetFilterTypeL( KIncludeAll );
	
		iCalendarService->GetListL( KDelTestCalNameDeleteForTm.operator()(), getListfilter2 , calInstanceArray2 );		
		
		if ( calInstanceArray2.Count() != 0 )
			{
			iResult = KErrGeneral;
			}
		calInstanceArray.ResetAndDestroy();
		
		calInstanceArray2.ResetAndDestroy();
		delete getListfilter2;
		}
	RemoveCalendarFile(iCalendarService, KDelTestCalNameDeleteForTm.operator()());
	
	return iResult;
	}



_LIT(KDelTestCalNameDeleteForGuidsAsync ,"c:deleteforGuidscalasync");

_LIT(KDelTestCalNameDeleteForLuidsAsync ,"c:deleteforLuidscalasync");

_LIT(KDelTestCalNameDeleteForGuidsAndTmAsync ,"c:deleteforGuidsandtmcalasync");

_LIT(KDelTestCalNameDeleteForLuidsAndTmAsync ,"c:deleteforLuidsandtmcalasync");

_LIT(KDelTestCalNameDeleteAllAsync ,"c:deleteallcalasync");

_LIT(KDelTestCalNameDeleteForTmAsync ,"c:deleteforTmcalasync");


//Async things start here ***************************************************
void CCalDelTestCases::TestDeleteAllEntriesAsyncL()
	{
	iTestCaseType = KDeleteAllAsync;	
	
	RemoveCalendarFile(iCalendarService, KDelTestCalNameDeleteAllAsync.operator()());
										
	TRAP( iResult , iCalendarService->AddL( KDelTestCalNameDeleteAllAsync.operator()() ) );	
	
	if(iResult == KErrNone )
		Start();
	}
	
	
void CCalDelTestCases::TestDeleteUsingGUidAsyncL()
	{
	iTestCaseType = KDeleteUsingGuidsAsync;	
	
	RemoveCalendarFile(iCalendarService, KDelTestCalNameDeleteForGuidsAsync.operator()());
										
	TRAP( iResult , iCalendarService->AddL( KDelTestCalNameDeleteForGuidsAsync.operator()() ) );	
	
	if(iResult == KErrNone )
		Start();
	}


//Asynchronous test cases so setting the iTestCaseType as it is to be handled in RunL
void CCalDelTestCases::TestDeleteUsingLocalUidAsyncL()
	{
	iTestCaseType = KDeleteUsingLuidsAsync;	
	
	RemoveCalendarFile(iCalendarService, KDelTestCalNameDeleteForLuidsAsync.operator()());
										
	TRAP( iResult , iCalendarService->AddL( KDelTestCalNameDeleteForLuidsAsync.operator()() ) );	
	
	if(iResult == KErrNone )
		Start();
	}

	
void CCalDelTestCases::TestDeleteTmRgLocalUidAsyncL()
	{
	iTestCaseType = KDeleteUsingLuidsAndTmRgAsync;	
	
	RemoveCalendarFile(iCalendarService, KDelTestCalNameDeleteForLuidsAndTmAsync.operator()());
										
	TRAP( iResult , iCalendarService->AddL( KDelTestCalNameDeleteForLuidsAndTmAsync.operator()() ) );	
	
	if(iResult == KErrNone )
		Start();
	}

	
void CCalDelTestCases::TestDeleteTmRgGUidAsyncL()	
	{
	iTestCaseType = KDeleteUsingGuidsAndTmRgAsync;	
	
	RemoveCalendarFile(iCalendarService, KDelTestCalNameDeleteForGuidsAndTmAsync.operator()());
										
	TRAP( iResult , iCalendarService->AddL( KDelTestCalNameDeleteForGuidsAndTmAsync.operator()() ) );	
	
	if(iResult == KErrNone )
		Start();
	}

	
	
void CCalDelTestCases::TestDeleteTmRgAsyncL()	
	{
	iTestCaseType = KDeleteUsingTmRgAsync;
	
	RemoveCalendarFile(iCalendarService, KDelTestCalNameDeleteForTmAsync.operator()());
										
	TRAP( iResult , iCalendarService->AddL( KDelTestCalNameDeleteForTmAsync.operator()() ) );	
	
	if(iResult == KErrNone )
		Start();
	}	

TInt CCalDelTestCases::Result()
	{
	return iResult;
	}
	
void CCalDelTestCases::ConstructL()
	{	
	iCalendarService = CCalendarService::NewL();
	
	iWaitSchedular = new(ELeave) CActiveSchedulerWait();
	}
	
CCalDelTestCases::CCalDelTestCases( TInt& aResult) : CActive(EPriorityStandard), iResult(aResult)
	{

	}
	
//for the sake of ActiveObject
void CCalDelTestCases::DoCancel()
	{
	
	}


void CCalDelTestCases::RunL()
	{	
	CCalendarFilter *getListfilter1 = CCalendarFilter::NewL();

	RPointerArray<CCalInstance> calInstanceArray;
	
	CCalendarFilter *filter = CCalendarFilter::NewL();
	
	
	switch( iTestCaseType )
		{
			case KDeleteAllAsync:	
											
										RemoveCalendarFile(iCalendarService, KDelTestCalNameDeleteAllAsync.operator()());
										
										TRAP( iResult , iCalendarService->AddL( KDelTestCalNameDeleteAllAsync.operator()() ) );
										
										addSomeEntries( KDelTestCalNameDeleteAllAsync.operator()() );//adds the entries and fills up iArruids with UIDSets

										getListfilter1->SetFilterTypeL( KIncludeAll );

										iCalendarService->GetListL( KDelTestCalNameDeleteAllAsync.operator()(), getListfilter1 , calInstanceArray );
										
										if ( calInstanceArray.Count() == 0 )
											{
											iResult = KErrGeneral;
											}
											
										filter->SetDeleteAll( ETrue );
										
										TRAP( iResult, iCalendarService->DeleteL( KDelTestCalNameDeleteAllAsync.operator()() , filter , this ) );
																			
										break;
										
			case KDeleteUsingGuidsAsync:	
										RemoveCalendarFile(iCalendarService, KDelTestCalNameDeleteForGuidsAsync.operator()());
										
										TRAP( iResult , iCalendarService->AddL( KDelTestCalNameDeleteForGuidsAsync.operator()() ) );
										
										addSomeEntries( KDelTestCalNameDeleteForGuidsAsync.operator()() );//adds the entries and fills up iArruids with UIDSets

										getListfilter1->SetFilterTypeL( KIncludeAll );

										iCalendarService->GetListL( KDelTestCalNameDeleteForGuidsAsync.operator()(), getListfilter1 , calInstanceArray );
										
										if ( calInstanceArray.Count() == 0 )
											{
											iResult = KErrGeneral;
											}
											
										for( TInt x = 0; x < iArruids.Count(); ++x )
											{
											filter->AddGuidL( *(iArruids[x])->iGlobalUID );
											}

										TRAP( iResult, iCalendarService->DeleteL( KDelTestCalNameDeleteForGuidsAsync.operator()() , filter , this ) );

										break;
										
			case KDeleteUsingLuidsAsync:
										
										RemoveCalendarFile(iCalendarService, KDelTestCalNameDeleteForLuidsAsync.operator()());
										
										TRAP( iResult , iCalendarService->AddL( KDelTestCalNameDeleteForLuidsAsync.operator()() ) );
										
										addSomeEntries( KDelTestCalNameDeleteForLuidsAsync.operator()() );//adds the entries and fills up iArruids with UIDSets

										getListfilter1->SetFilterTypeL( KIncludeAll );

										iCalendarService->GetListL( KDelTestCalNameDeleteForLuidsAsync.operator()(), getListfilter1 , calInstanceArray );
										
										if ( calInstanceArray.Count() == 0 )
											{
											iResult = KErrGeneral;
											}
											
										for( TInt x = 0; x < iArruids.Count(); ++x )
											{
											filter->AddLocalUid( (iArruids[x])->iLocalUID );
											}
										
										TRAP( iResult, iCalendarService->DeleteL( KDelTestCalNameDeleteForLuidsAsync.operator()() , filter , this ) );
																	
										break;
										
			case KDeleteUsingGuidsAndTmRgAsync:
										
										RemoveCalendarFile(iCalendarService, KDelTestCalNameDeleteForGuidsAndTmAsync.operator()());
										
										TRAP( iResult , iCalendarService->AddL( KDelTestCalNameDeleteForGuidsAndTmAsync.operator()() ) );
										
										addSomeEntries( KDelTestCalNameDeleteForGuidsAndTmAsync.operator()() );//adds the entries and fills up iArruids with UIDSets

										getListfilter1->SetFilterTypeL( KIncludeAll );

										iCalendarService->GetListL( KDelTestCalNameDeleteForGuidsAndTmAsync.operator()(), getListfilter1 , calInstanceArray );
										
										if ( calInstanceArray.Count() == 0 )
											{
											iResult = KErrGeneral;
											}
											
										for( TInt x = 0; x < iArruids.Count(); ++x )
											{
											filter->AddGuidL( *(iArruids[x])->iGlobalUID );
											}
											
										filter->SetStartTimeL( TTime(TDateTime(2005, EDecember, 30, 0, 0, 0, 0)) );
										
										filter->SetEndTimeL( TTime(TDateTime(2100, EDecember, 30, 0, 0, 0, 0)) );
									
										TRAP( iResult, iCalendarService->DeleteL( KDelTestCalNameDeleteForGuidsAndTmAsync.operator()() , filter , this ) );
																			
										break;
										
			case KDeleteUsingLuidsAndTmRgAsync:
										
										RemoveCalendarFile(iCalendarService, KDelTestCalNameDeleteForLuidsAndTmAsync.operator()());
										
										TRAP( iResult , iCalendarService->AddL( KDelTestCalNameDeleteForLuidsAndTmAsync.operator()() ) );
										
										addSomeEntries( KDelTestCalNameDeleteForLuidsAndTmAsync.operator()() );//adds the entries and fills up iArruids with UIDSets

										getListfilter1->SetFilterTypeL( KIncludeAll );

										iCalendarService->GetListL( KDelTestCalNameDeleteForLuidsAndTmAsync.operator()(), getListfilter1 , calInstanceArray );
										
										if ( calInstanceArray.Count() == 0 )
											{
											iResult = KErrGeneral;
											}
											
										for( TInt x = 0; x < iArruids.Count(); ++x )
											{
											filter->AddLocalUid( (iArruids[x])->iLocalUID );
											}
									
										filter->SetStartTimeL( TTime(TDateTime(2005, EDecember, 30, 0, 0, 0, 0)) );
										
										filter->SetEndTimeL( TTime(TDateTime(2100, EDecember, 30, 0, 0, 0, 0)) );
										
										TRAP( iResult, iCalendarService->DeleteL( KDelTestCalNameDeleteForLuidsAndTmAsync.operator()() , filter , this ) );
										
										break;
										
			case KDeleteUsingTmRgAsync:											
										
										addSomeEntries( KDelTestCalNameDeleteForTmAsync.operator()() );//adds the entries and fills up iArruids with UIDSets

										getListfilter1->SetFilterTypeL( KIncludeAll );

										iCalendarService->GetListL( KDelTestCalNameDeleteForTmAsync.operator()(), getListfilter1 , calInstanceArray );
										
										if ( calInstanceArray.Count() == 0 )
											{
											iResult = KErrGeneral;
											}
											
										filter->SetStartTimeL( TTime(TDateTime(2005, EDecember, 30, 0, 0, 0, 0)) );
										
										filter->SetEndTimeL( TTime(TDateTime(2100, EDecember, 30, 0, 0, 0, 0)) );
									
										TRAP( iResult, iCalendarService->DeleteL( KDelTestCalNameDeleteForTmAsync.operator()() , filter , this ) );		
																	
										break;										
		}
		
		delete getListfilter1;
		delete filter;
	Final:
		calInstanceArray.ResetAndDestroy();
	}
			
void CCalDelTestCases::Start()
	{
	CActiveScheduler::Add(this);
	
	SetActive();
	
	TRequestStatus* temp = &iStatus;
	
	User::RequestComplete(temp, KErrNone);
	
	iWaitSchedular->Start();	
	}

			
void CCalDelTestCases::NotifyResultL(TInt aErrCode, TAny* aResult)
	{
	//******************* set iResult ****************************
	iResult = aErrCode;
	//******************* set iResult ****************************
	
	//write the iResult to the corresponding file basing on the iTestCaseType
	
	CCalendarFilter *getListfilter2 = CCalendarFilter::NewL();

	RPointerArray<CCalInstance> calInstanceArray2;

	getListfilter2->SetFilterTypeL( KIncludeAll );
	
    switch( iTestCaseType )
		{
			case KDeleteAllAsync:	
										iCalendarService->GetListL( KDelTestCalNameDeleteAllAsync.operator()(), getListfilter2 , calInstanceArray2 );		
	
										RemoveCalendarFile(iCalendarService, KDelTestCalNameDeleteAllAsync.operator()());
										
										break;
										
			case KDeleteUsingGuidsAsync:	
										iCalendarService->GetListL( KDelTestCalNameDeleteForGuidsAsync.operator()(), getListfilter2 , calInstanceArray2 );		
	
										RemoveCalendarFile(iCalendarService, KDelTestCalNameDeleteForGuidsAsync.operator()());
										
										break;
										
			case KDeleteUsingLuidsAsync:	
										iCalendarService->GetListL( KDelTestCalNameDeleteForLuidsAsync.operator()(), getListfilter2 , calInstanceArray2 );		
	
										RemoveCalendarFile(iCalendarService, KDelTestCalNameDeleteForLuidsAsync.operator()());
										
										break;
										
			case KDeleteUsingGuidsAndTmRgAsync:	
										iCalendarService->GetListL( KDelTestCalNameDeleteForGuidsAndTmAsync.operator()(), getListfilter2 , calInstanceArray2 );		
	
										RemoveCalendarFile(iCalendarService, KDelTestCalNameDeleteForGuidsAndTmAsync.operator()());
										
										break;
										
			case KDeleteUsingLuidsAndTmRgAsync:	
										iCalendarService->GetListL( KDelTestCalNameDeleteForLuidsAndTmAsync.operator()(), getListfilter2 , calInstanceArray2 );		
	
										RemoveCalendarFile(iCalendarService, KDelTestCalNameDeleteForLuidsAndTmAsync.operator()());
										
										break;
										
			case KDeleteUsingTmRgAsync:	
										iCalendarService->GetListL( KDelTestCalNameDeleteForTmAsync.operator()(), getListfilter2 , calInstanceArray2 );		
	
										RemoveCalendarFile(iCalendarService, KDelTestCalNameDeleteForTmAsync.operator()());
										
										break;		
		}
	
	if ( calInstanceArray2.Count() != 0 )
		{
		iResult = KErrGeneral;
		}
	
	calInstanceArray2.ResetAndDestroy();
	
	delete getListfilter2;

	
	iWaitSchedular->AsyncStop();
	}


void CCalDelTestCases::addSomeEntries( const TDesC& aName)
	{
	TUIDSet* uids = NULL;
	
	if(AddAppointment(iCalendarService, aName, uids) == KErrNone && uids)
		{
		iArruids.Append(uids);
		uids = NULL;
		}

	if(AddEvent(iCalendarService, aName, uids) == KErrNone && uids)
		{
		iArruids.Append(uids);
		uids = NULL;
		}

	if(AddReminder(iCalendarService, aName, uids) == KErrNone && uids)
		{
		iArruids.Append(uids);
		uids = NULL;
		}

/*	if(AddAnny(iCalendarService, aName, uids) == KErrNone && uids)
		{
		iArruids.Append(uids);
		uids = NULL;
		}*/

	if(AddToDo(iCalendarService, aName, uids) == KErrNone && uids)
		{
		iArruids.Append(uids);
		uids = NULL;
		}
	}
/*
EAppt An appointment, which has a start time and end time. 
 
ETodo A to-do, which can have a start time and end time (the end time is the due date), or can be undated. 
 
EEvent An event, which has a start time and end time. 
 
EReminder A reminder, which has a start time only. 
 
EAnniv An anniversary, which has a start time and end time. 
*/	
	
	
void CCalDelTestCases::ExportAllToFileL( const TDesC16 &aCalFileName,  const TDesC16 &aFileName)
	{
	
	CCalendarExportParams *expParams = CCalendarExportParams::NewL();

	HBufC8* buffer;

	TRAPD( err ,iCalendarService->ExportL( aCalFileName , KFormatVCal.operator()() , expParams ,buffer ) );
	
	delete buffer;
	}