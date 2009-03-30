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
#include "cal_delete.h"
#include "calendarheader.h"
#include "calendarservice.h"
#include "entryattributes.h"
#include<ASCliClientUtils.h>

#include "teststartconsolealarmserver.h"



_LIT(KCalName                 ,"C:Calendar");


TInt AddRepeatingAptEntryL(CCalendarService* aService, const TDesC& name, TUIDSet*& uids);

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
	

_LIT(KTestCal1File ,"c:cal1");
_LIT(KTestCal2File ,"c:cal2");	
_LIT(KDelTestInvFile ,"Invalid");

			
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
		
		CEntryAttributes* entryObj = CEntryAttributes::NewL();
	    	    
	    entryObj->SetEntryStatusL(KNullStatus); 
	    
	    entryObj->SetLocalUid( iArruids[0]->iLocalUID );
	    
	    TUIDSet* entryUids = NULL;
	    
	    CCalendarFilter *getListfilter1 = CCalendarFilter::NewL();
	
		RPointerArray<CCalInstance> calInstanceArray;
	
		getListfilter1->SetFilterTypeL( KIncludeAll );
	
		iCalendarService->GetListL( KDelTestCalNameDeleteForGuids.operator()(), getListfilter1 , calInstanceArray );		
		
		delete getListfilter1;
		
		TInt count = calInstanceArray.Count();
		
		if ( calInstanceArray.Count() == 0 )
			{
			iResult = KErrGeneral;
		
			calInstanceArray.ResetAndDestroy();
			
			return iResult;
			}
			
			
	    TRAPD( iResult, iCalendarService->AddL(KDelTestCalNameDeleteForGuids.operator()(),entryObj,entryUids) );
	    
	    if(iResult != KErrNone)
	    {
	    	
	    	delete entryObj;
	    	
	    	calInstanceArray.ResetAndDestroy();
			
			RemoveCalendarFile(iCalendarService, KDelTestCalNameDeleteForGuids.operator()());
			
			return iResult;
	    }
	
		CCalendarFilter *filter = CCalendarFilter::NewL();
		
		filter->AddGuidL( *(iArruids[0])->iGlobalUID );
			
		
		TRAP( iResult, iCalendarService->DeleteL( KDelTestCalNameDeleteForGuids.operator()() , filter , NULL) );
		
		delete filter;		
		
		if(iResult != KErrNone)
	    {
	    	
	    	delete entryObj;
	    	
	    	calInstanceArray.ResetAndDestroy();
			
			RemoveCalendarFile(iCalendarService, KDelTestCalNameDeleteForGuids.operator()());
			
			delete entryUids;
		
			entryUids = NULL;
			
			return iResult;
	    }
		
		
		CCalendarFilter *getListfilter2 = CCalendarFilter::NewL();
	
		RPointerArray<CCalInstance> calInstanceArray2;
	
		getListfilter2->SetFilterTypeL( KIncludeAll );
	
		iCalendarService->GetListL( KDelTestCalNameDeleteForGuids.operator()(), getListfilter2 , calInstanceArray2 );		
		
		delete getListfilter2;
		
		delete entryObj;
		
		delete entryUids;
		
		entryUids = NULL;	
		
		TInt new_count = calInstanceArray2.Count();

		if ( calInstanceArray2.Count() != count-1 )
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
	
	iCalendarService->AddL( KDelTestCalNameDeleteForLuids.operator()() );
	
		CEntryAttributes* entryObj = CEntryAttributes::NewL();
		
		TUIDSet* entryUids = NULL;
		
		RPointerArray<CCalEntry> entryArray;
	
		TRAPD(err_apt,AddRepeatingAppointmentEntryL(iCalendarService, KDelTestCalNameDeleteForLuids.operator()(), entryUids));
		iArruids.Append(entryUids);
		entryUids = NULL;
		
		iCalendarService->GetListL( KDelTestCalNameDeleteForLuids.operator()(), *(iArruids[0]->iGlobalUID) , entryArray );		
			
		TInt count = entryArray.Count();
		count =0;
		entryArray.ResetAndDestroy();
			
		TTime stTime(TDateTime(2007, ESeptember, 28, 9, 0, 0, 0));
		entryObj->SetInstanceStartTimeL(stTime);
		TTime startTime(TDateTime(2007, ESeptember, 28, 14, 0, 0, 0));
		entryObj->SetStartTimeL(startTime);
		TTime endTime(TDateTime(2007, ESeptember, 28, 17, 30, 0, 0));
		entryObj->SetEndTimeL(endTime);
		
		TCalLocalUid luid = iArruids[0]->iLocalUID;
		
		entryObj->SetLocalUid( iArruids[0]->iLocalUID );
		
		TRAPD(err_update,iCalendarService->AddL(KDelTestCalNameDeleteForLuids.operator()(),entryObj,entryUids));
		
		TCalLocalUid modifiedEntryId = entryUids->iLocalUID;
		
									
		CCalendarFilter *filter = CCalendarFilter::NewL();
			
		filter->AddLocalUid( (iArruids[0])->iLocalUID );
		
		
		TRAP( iResult, iCalendarService->DeleteL( KDelTestCalNameDeleteForLuids.operator()() , filter , NULL) );

		delete filter;		
		
				
		iCalendarService->GetListL( KDelTestCalNameDeleteForLuids.operator()(), *(entryUids->iGlobalUID) , entryArray );		
		
	
		count = entryArray.Count();
		
		if ( count != 0 )
			{
			iResult = KErrGeneral;
			}
				
		entryArray.ResetAndDestroy();
		
	
		delete entryUids;
		entryUids = NULL;
		delete entryObj;
		
	RemoveCalendarFile(iCalendarService, KDelTestCalNameDeleteForLuids.operator()());
	
	return iResult;
	}

_LIT(KDelTestCalNameDeleteForGuidLuidsAndTm ,"c:deleteforGuidLuidsAndTmcal");
	
TInt CCalDelTestCases::TestDeleteGuidTmRgLocalUidL()
	{
		//No need to set it but for the sake of semanitics set to sync value
	iTestCaseType = KDeleteSync;
	
	RemoveCalendarFile(iCalendarService, KDelTestCalNameDeleteForGuidLuidsAndTm.operator()());
	
	iCalendarService->AddL( KDelTestCalNameDeleteForGuidLuidsAndTm.operator()() );
	
		
		addSomeEntries( KDelTestCalNameDeleteForGuidLuidsAndTm.operator()() );//adds the entries and fills up iArruids with UIDSets
		
		TUIDSet* entryUids = NULL;
		
		CCalendarFilter *getListfilter2 = CCalendarFilter::NewL();
	
		RPointerArray<CCalInstance> calInstanceArray2;
	
		getListfilter2->SetFilterTypeL( KIncludeAll );		
		
		AddRepeatingAppointmentEntryL(iCalendarService, KDelTestCalNameDeleteForGuidLuidsAndTm.operator()(), entryUids);
		iArruids.Append(entryUids);
	//	delete entryUids;
		entryUids = NULL;

		iCalendarService->GetListL( KDelTestCalNameDeleteForGuidLuidsAndTm.operator()(), getListfilter2 , calInstanceArray2 );		
		
		TInt count = calInstanceArray2.Count();
		count =0;
		calInstanceArray2.ResetAndDestroy();
		
		CCalendarFilter *filter = CCalendarFilter::NewL();
		
		filter->AddGuidL( *(iArruids[1])->iGlobalUID );
				
		filter->AddLocalUid( (iArruids[2])->iLocalUID );
		
		
		
		filter->SetStartTimeL( TTime(TDateTime(2007, EAugust, 5, 8, 0, 0, 0)) );
		
		filter->SetEndTimeL( TTime(TDateTime(2007, EOctober, 2, 0, 0, 0, 0)) );
		
		TRAPD( err_delete, iCalendarService->DeleteL( KDelTestCalNameDeleteForGuidLuidsAndTm.operator()() , filter , NULL) );

		delete filter;
		
			
		iCalendarService->GetListL( KDelTestCalNameDeleteForGuidLuidsAndTm.operator()(), getListfilter2 , calInstanceArray2 );		
		
		count = calInstanceArray2.Count();
		
		if ( calInstanceArray2.Count() != 19 )
			{
			iResult = KErrGeneral;
			}
				
		calInstanceArray2.ResetAndDestroy();
		
		delete getListfilter2;
	
	RemoveCalendarFile(iCalendarService, KDelTestCalNameDeleteForGuidLuidsAndTm.operator()());
	
	iResult = err_delete;
	
	return iResult;	
	}



_LIT(KDelTestCalNameDeleteForInvalidGuidLuid ,"c:deleteforInvalidGuidLuid");
_LIT(KDelTestCalNameDelete ,"c:testcal");
	
TInt CCalDelTestCases::TestDeleteInvalidGUidLuidL()	
	{
		//No need to set it but for the sake of semanitics set to sync value
	iTestCaseType = KDeleteSync;
	
	RemoveCalendarFile(iCalendarService, KDelTestCalNameDeleteForInvalidGuidLuid.operator()());
	RemoveCalendarFile(iCalendarService, KDelTestCalNameDelete.operator()());
	
	iCalendarService->AddL( KDelTestCalNameDeleteForInvalidGuidLuid.operator()() );
	iCalendarService->AddL( KDelTestCalNameDelete.operator()() );
	
			
		addSomeEntries( KDelTestCalNameDeleteForInvalidGuidLuid.operator()() );//adds the entries and fills up iArruids with UIDSets
		
	
		CCalendarFilter *filter = CCalendarFilter::NewL();
		
		CCalendarFilter *new_filter = CCalendarFilter::NewL();
		
		filter->AddGuidL( *(iArruids[0])->iGlobalUID );
		
		new_filter->AddLocalUid( 3000 );
		
		
	//	filter->SetStartTimeL( TTime(TDateTime(2005, EDecember, 30, 0, 0, 0, 0)) );
		
	//	filter->SetEndTimeL( TTime(TDateTime(2100, EDecember, 30, 0, 0, 0, 0)) );
		
		TRAPD( err_guid, iCalendarService->DeleteL( KDelTestCalNameDelete.operator()() , filter , NULL) );

		delete filter;
		
				
		TRAPD(err_luid,iCalendarService->DeleteL( KDelTestCalNameDeleteForInvalidGuidLuid.operator()() , new_filter , NULL) );
		
		delete new_filter;
		
		CCalendarFilter *getListfilter2 = CCalendarFilter::NewL();
	
		RPointerArray<CCalInstance> calInstanceArray2;
	
		getListfilter2->SetFilterTypeL( KIncludeAll );
		
		
		iCalendarService->GetListL( KDelTestCalNameDeleteForInvalidGuidLuid.operator()(), getListfilter2 , calInstanceArray2 );		
		
		TInt count = calInstanceArray2.Count();
		
		if ( calInstanceArray2.Count() != 4 )
			{
			iResult = KErrGeneral;
			}
				
		calInstanceArray2.ResetAndDestroy();
		
		delete getListfilter2;
				
		RemoveCalendarFile(iCalendarService, KDelTestCalNameDeleteForInvalidGuidLuid.operator()());
		RemoveCalendarFile(iCalendarService, KDelTestCalNameDelete.operator()());
		
	/*	if(err_guid != KErrNone)
			iResult = err_guid;
		else
			iResult = err_luid; */
	
	return iResult;		
	}



_LIT(KDelTestCalNameDeleteForTm ,"c:deleteforTmcal");	
	
TInt CCalDelTestCases::TestDeleteTmRgL()	
	{
		//No need to set it but for the sake of semanitics set to sync value
	iTestCaseType = KDeleteSync;
	
	RemoveCalendarFile(iCalendarService, KDelTestCalNameDeleteForTm.operator()());
	
	iCalendarService->AddL( KDelTestCalNameDeleteForTm.operator()() );
	
			
		addSomeEntries( KDelTestCalNameDeleteForTm.operator()() );//adds the entries and fills up iArruids with UIDSets
		
		TUIDSet* entryUids = NULL;
		
		
		AddRepeatingAptEntryL(iCalendarService, KDelTestCalNameDeleteForTm.operator()(), entryUids);
		
		iArruids.Append(entryUids);
	//	delete entryUids;
		entryUids = NULL;
		
		
		CCalendarFilter *filter = CCalendarFilter::NewL();

		filter->SetStartTimeL( TTime(TDateTime(2007, EAugust, 7, 8, 0, 0, 0)) );
		
		filter->SetEndTimeL( TTime(TDateTime(2007, ESeptember, 20, 9, 0, 0, 0)) );
		
		TRAP( iResult, iCalendarService->DeleteL( KDelTestCalNameDeleteForTm.operator()() , filter , NULL) );

		
		delete filter;
	
		
		CCalendarFilter *getListfilter2 = CCalendarFilter::NewL();
	
		RPointerArray<CCalInstance> calInstanceArray2;
	
		getListfilter2->SetFilterTypeL( KIncludeAll );
	
		iCalendarService->GetListL( KDelTestCalNameDeleteForTm.operator()(), getListfilter2 , calInstanceArray2 );		
		
		TInt count = calInstanceArray2.Count();
		
		for(TInt i=0;i<count;i++)
		{
	   			 	
	   		TInt day_no = calInstanceArray2[i]->Time().TimeLocalL().DateTime().Day();
	   			 				 	
	    }
		
		if ( calInstanceArray2.Count() != 12 )
			{
			iResult = KErrGeneral;
			}
		
		
		calInstanceArray2.ResetAndDestroy();
		delete getListfilter2;
		
	RemoveCalendarFile(iCalendarService, KDelTestCalNameDeleteForTm.operator()());
	
	return iResult;
	}


_LIT(KDefaultCal ,"C:Calendar");	
	
TInt CCalDelTestCases::TestDeleteByDefCalL()	
	{
		//No need to set it but for the sake of semanitics set to sync value
  		iTestCaseType = KDeleteSync;
	
		CCalendarFilter *filter = CCalendarFilter::NewL();

		filter->SetStartTimeL( TTime(TDateTime(2007, EAugust, 7, 8, 0, 0, 0)) );
		
		filter->SetEndTimeL( TTime(TDateTime(2007, ESeptember, 20, 8, 0, 0, 0)) );
		
	//	TRAPD( err_delete, iCalendarService->DeleteL( KDefaultCal.operator()() , NULL , NULL) );
		
		TRAPD( iResult, iCalendarService->DeleteL( KDefaultCal.operator()() , filter , NULL) );

		delete filter;
	


	
	return iResult;
	}


_LIT(KDelTestCalNameDeleteForGuidsAsync ,"c:deleteforGuidscalasync");

_LIT(KDelTestCalNameDeleteForLuidsAsync ,"c:deleteforLuidscalasync");

_LIT(KDelTestCalNameDeleteForInvalidGuidAsync ,"c:deleteforInvalidGuidLasync");
_LIT(KDelTestCalNameDeleteForInvalidLuidAsync ,"c:deleteforInvalidLuidLasync");
_LIT(KDelTestCalNameAsync ,"c:testcalasync");


_LIT(KDelTestCalNameDeleteForGuidLuidsAndTmAsync ,"c:deleteforGuidLuidsandtmcalasync");

_LIT(KDelTestCalNameDeleteAllAsync ,"c:deleteallcalasync");

_LIT(KDelTestCalNameDeleteForTmAsync ,"c:deleteforTmcalasync");


//Async things start here ***************************************************
	
void CCalDelTestCases::TestDeleteUsingGUidAsyncL()
	{
	iTestCaseType = KDeleteUsingGuidsAsync;	
	
	Start();
	}


//Asynchronous test cases so setting the iTestCaseType as it is to be handled in RunL
void CCalDelTestCases::TestDeleteUsingLocalUidAsyncL()
	{
	iTestCaseType = KDeleteUsingLuidsAsync;	
	
	Start();
	}

	
void CCalDelTestCases::TestDeleteGuidTmRgLocalUidAsyncL()
	{
	iTestCaseType = KDeleteUsingGuidLuidsAndTmRgAsync;	
	
	Start();
	}

	
void CCalDelTestCases::TestDeleteInvalidGUidAsyncL()	
	{
	iTestCaseType = KDeleteUsingInvalidGuidAsync;	
	
	Start();
	}


void CCalDelTestCases::TestDeleteInvalidLUidAsyncL()	
	{
	iTestCaseType = KDeleteUsingInvalidLuidAsync;	
	
	Start();
	}	
	
void CCalDelTestCases::TestDeleteTmRgAsyncL()	
	{
	iTestCaseType = KDeleteUsingTmRgAsync;
	
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


TInt CCalDelTestCases::RunError(TInt aError)
{
	if(aError != KErrNotFound)
		iResult = aError;
	
	return iResult;
}

void CCalDelTestCases::RunL()
	{	
	CCalendarFilter *getListfilter1 = CCalendarFilter::NewL();

	RPointerArray<CCalInstance> calInstanceArray;
	
	CCalendarFilter *filter = CCalendarFilter::NewL();
	
	CEntryAttributes* entryObj = CEntryAttributes::NewL();
	
	
	
	
	switch( iTestCaseType )
		{
		
			case KDeleteUsingGuidsAsync:
			
										TUIDSet* entryUids = NULL;
											
										RemoveCalendarFile(iCalendarService, KDelTestCalNameDeleteForGuidsAsync.operator()());
										
										iCalendarService->AddL( KDelTestCalNameDeleteForGuidsAsync.operator()() );
										
										addSomeEntries( KDelTestCalNameDeleteForGuidsAsync.operator()() );//adds the entries and fills up iArruids with UIDSets
										
										entryObj->SetEntryStatusL(KNullStatus); 
	    
	   									entryObj->SetLocalUid( iArruids[0]->iLocalUID );

										getListfilter1->SetFilterTypeL( KIncludeAll );

										iCalendarService->GetListL( KDelTestCalNameDeleteForGuidsAsync.operator()(), getListfilter1 , calInstanceArray );
										
																
										iCalendarService->AddL(KDelTestCalNameDeleteForGuidsAsync.operator()(),entryObj,entryUids);
										
										
										delete entryUids;
										entryUids = NULL;
										
																	
										filter->AddGuidL( *(iArruids[0])->iGlobalUID );
										
										TRAP( iResult, iCalendarService->DeleteL( KDelTestCalNameDeleteForGuidsAsync.operator()() , filter , this ) );
										
										
										break;
										
			case KDeleteUsingLuidsAsync:
										
										
										
										RemoveCalendarFile(iCalendarService, KDelTestCalNameDeleteForLuidsAsync.operator()());
										
										iCalendarService->AddL( KDelTestCalNameDeleteForLuidsAsync.operator()() );
										
																		
																			
										AddRepeatingAppointmentEntryL(iCalendarService, KDelTestCalNameDeleteForLuidsAsync.operator()(), entryUids);
										iArruids.Append(entryUids);
										entryUids = NULL;

										TTime stTime(TDateTime(2007, ESeptember, 28, 9, 0, 0, 0));
										entryObj->SetInstanceStartTimeL(stTime);
										TTime startTime(TDateTime(2007, ESeptember, 28, 14, 0, 0, 0));
										entryObj->SetStartTimeL(startTime);
										TTime endTime(TDateTime(2007, ESeptember, 28, 17, 30, 0, 0));
										entryObj->SetEndTimeL(endTime);
		
										entryObj->SetLocalUid( iArruids[0]->iLocalUID );
										
										iCalendarService->AddL(KDelTestCalNameDeleteForLuidsAsync.operator()(),entryObj,entryUids);
										
										delete entryUids;
										entryUids = NULL;
										
										filter->AddLocalUid( (iArruids[0])->iLocalUID );
									
																			
										TRAP( iResult, iCalendarService->DeleteL( KDelTestCalNameDeleteForLuidsAsync.operator()() , filter , this ) );
																	
										break;
										
			case KDeleteUsingInvalidGuidAsync:
										
										RemoveCalendarFile(iCalendarService, KDelTestCalNameDeleteForInvalidGuidAsync.operator()());
										RemoveCalendarFile(iCalendarService, KDelTestCalNameAsync.operator()());
										
										iCalendarService->AddL( KDelTestCalNameDeleteForInvalidGuidAsync.operator()() );
										iCalendarService->AddL( KDelTestCalNameAsync.operator()() ); 
										
										addSomeEntries( KDelTestCalNameDeleteForInvalidGuidAsync.operator()() );//adds the entries and fills up iArruids with UIDSets

										filter->AddGuidL( *(iArruids[0])->iGlobalUID );
																											
										
										TRAPD( iResult, iCalendarService->DeleteL( KDelTestCalNameAsync.operator()() , filter , this ) );
										
																																													
										break;
										
				case KDeleteUsingInvalidLuidAsync:
										
										RemoveCalendarFile(iCalendarService, KDelTestCalNameDeleteForInvalidLuidAsync.operator()());
																			
										iCalendarService->AddL( KDelTestCalNameDeleteForInvalidLuidAsync.operator()() );
																				
										addSomeEntries( KDelTestCalNameDeleteForInvalidLuidAsync.operator()() );//adds the entries and fills up iArruids with UIDSets

																												
										filter->AddLocalUid( 3000 );
																				
										TRAP( iResult, iCalendarService->DeleteL( KDelTestCalNameDeleteForInvalidLuidAsync.operator()() , filter , this ) );
																																						
										break;
										
			case KDeleteUsingGuidLuidsAndTmRgAsync:
										
										
										
										RemoveCalendarFile(iCalendarService, KDelTestCalNameDeleteForGuidLuidsAndTmAsync.operator()());
										
										TRAP( iResult , iCalendarService->AddL( KDelTestCalNameDeleteForGuidLuidsAndTmAsync.operator()() ) );
										
										addSomeEntries( KDelTestCalNameDeleteForGuidLuidsAndTmAsync.operator()() );//adds the entries and fills up iArruids with UIDSets
										
										AddRepeatingAptEntryL(iCalendarService, KDelTestCalNameDeleteForGuidLuidsAndTmAsync.operator()(), entryUids);
		
										iArruids.Append(entryUids);
									//	delete entryUids;
										entryUids = NULL;

										
										filter->AddGuidL( *(iArruids[1])->iGlobalUID );
				
										filter->AddLocalUid( (iArruids[2])->iLocalUID );
		
		
		
										filter->SetStartTimeL( TTime(TDateTime(2007, EAugust, 6, 8, 0, 0, 0)) );
		
										filter->SetEndTimeL( TTime(TDateTime(2007, EOctober, 2, 0, 0, 0, 0)) );
										
										
										TRAP( iResult, iCalendarService->DeleteL( KDelTestCalNameDeleteForGuidLuidsAndTmAsync.operator()() , filter , this ) );
										
										break;
										
			case KDeleteUsingTmRgAsync:											
										
										RemoveCalendarFile(iCalendarService, KDelTestCalNameDeleteForTmAsync.operator()());
										
										TRAP( iResult , iCalendarService->AddL( KDelTestCalNameDeleteForTmAsync.operator()() ) );
										
										addSomeEntries( KDelTestCalNameDeleteForTmAsync.operator()() );//adds the entries and fills up iArruids with UIDSets
										
										AddRepeatingAptEntryL(iCalendarService, KDelTestCalNameDeleteForTmAsync.operator()(), entryUids);
		
										iArruids.Append(entryUids);
									//	delete entryUids;
										entryUids = NULL;

										
									//	filter->AddGuidL( *(iArruids[1])->iGlobalUID );
				
								//		filter->AddLocalUid( (iArruids[2])->iLocalUID );
		
		
		
										filter->SetStartTimeL( TTime(TDateTime(2007, EAugust, 7, 8, 0, 0, 0)) );
										
										filter->SetEndTimeL( TTime(TDateTime(2007, ESeptember, 20, 10, 0, 0, 0)) );
									
										
										TRAP( iResult, iCalendarService->DeleteL( KDelTestCalNameDeleteForTmAsync.operator()() , filter , this ) );
										
										break;
										
									/*	addSomeEntries( KDelTestCalNameDeleteForTmAsync.operator()() );//adds the entries and fills up iArruids with UIDSets
										
										AddRepeatingAppointmentEntryL(iCalendarService, KDelTestCalNameDeleteForTmAsync.operator()(), entryUids);
		
										iArruids.Append(entryUids);
									//	delete entryUids;
										entryUids = NULL;

									
										filter->SetStartTimeL( TTime(TDateTime(2007, EAugust, 7, 8, 0, 0, 0)) );
										
										filter->SetEndTimeL( TTime(TDateTime(2007, ESeptember, 20, 8, 0, 0, 0)) );
									
										TRAP( iResult, iCalendarService->DeleteL( KDelTestCalNameDeleteForTmAsync.operator()() , filter , this ) );		
																	
										break;		*/								
		}
		
		delete getListfilter1;
		delete filter;
		delete entryObj;
		
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
								
			case KDeleteUsingGuidsAsync:	
										iCalendarService->GetListL( KDelTestCalNameDeleteForGuidsAsync.operator()(), getListfilter2 , calInstanceArray2 );		
										
										TInt count = calInstanceArray2.Count();
										
										calInstanceArray2.ResetAndDestroy();
	
										delete getListfilter2;

														
										if ( count != 3 && iResult == KErrNone)
										{
											iResult = KErrGeneral;
										}
										
										RemoveCalendarFile(iCalendarService, KDelTestCalNameDeleteForGuidsAsync.operator()());
										
										break;
										
			case KDeleteUsingLuidsAsync:
			
										RPointerArray<CCalEntry> entryArray;
											
										iCalendarService->GetListL( KDelTestCalNameDeleteForLuidsAsync.operator()(), *(iArruids[0]->iGlobalUID) , entryArray );
										
										count = entryArray.Count();
										
										if(count != 0)
											iResult = KErrGeneral;
										
										calInstanceArray2.ResetAndDestroy();
	
										delete getListfilter2;
										
										entryArray.ResetAndDestroy();
	
										RemoveCalendarFile(iCalendarService, KDelTestCalNameDeleteForLuidsAsync.operator()());
										
										break;
										
			case KDeleteUsingGuidLuidsAndTmRgAsync:	
			
										iCalendarService->GetListL( KDelTestCalNameDeleteForGuidLuidsAndTmAsync.operator()(), getListfilter2 , calInstanceArray2 );		
										
										count = calInstanceArray2.Count();
										
										calInstanceArray2.ResetAndDestroy();
	
										delete getListfilter2;
										
										if ( count != 19)
										{
											iResult = KErrGeneral;
										}
	
										RemoveCalendarFile(iCalendarService, KDelTestCalNameDeleteForGuidLuidsAndTmAsync.operator()());
										
										break;
										
																				
			case KDeleteUsingInvalidGuidAsync:	
											
										iCalendarService->GetListL( KDelTestCalNameDeleteForInvalidGuidAsync.operator()(), getListfilter2 , calInstanceArray2 );		
										
										count = calInstanceArray2.Count();
										
										calInstanceArray2.ResetAndDestroy();
	
										delete getListfilter2;
										
										if ( count != 4)
										{
											iResult = KErrGeneral;
										}
	
										
										RemoveCalendarFile(iCalendarService, KDelTestCalNameDeleteForInvalidGuidAsync.operator()());
										
										RemoveCalendarFile(iCalendarService, KDelTestCalNameAsync.operator()());
										
										break;
			case KDeleteUsingInvalidLuidAsync:	
											
										iCalendarService->GetListL( KDelTestCalNameDeleteForInvalidLuidAsync.operator()(), getListfilter2 , calInstanceArray2 );		
										
										count = calInstanceArray2.Count();
										
										calInstanceArray2.ResetAndDestroy();
	
										delete getListfilter2;
										
										if ( count != 4)
										{
											iResult = KErrGeneral;
										}
	
										
										RemoveCalendarFile(iCalendarService, KDelTestCalNameDeleteForInvalidLuidAsync.operator()());
										
																				
										break;
										
			case KDeleteUsingTmRgAsync:	
										iCalendarService->GetListL( KDelTestCalNameDeleteForTmAsync.operator()(), getListfilter2 , calInstanceArray2 );		
										
										count = calInstanceArray2.Count();
										
										calInstanceArray2.ResetAndDestroy();
	
										delete getListfilter2;
										
										if ( count != 12)
										{
											iResult = KErrGeneral;
										}
	
										RemoveCalendarFile(iCalendarService, KDelTestCalNameDeleteForTmAsync.operator()());
										
										break;		
		}
	
	

	
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
// Helper function to create a repeating entry

TInt AddRepeatingAptEntryL(CCalendarService* aService, const TDesC& name, TUIDSet*& uids)
	{
	
	CEntryAttributes* entryObj = CEntryAttributes::NewL( KEntryAppt );
	
    entryObj->SetDescriptionL(_L("SAPI weekly meeting"));
	entryObj->SetLocationL(_L("Hara"));
	entryObj->SetEntryStatusL(KStatusConfirmed);
	
	entryObj->SetMethodL(KMethodNone);
	CAttendeeInfo* organizer = CAttendeeInfo::NewL(_L("mcrasta@gmail.com"));
	organizer->SetCommonNameL(_L("SAPI"));
	entryObj->SetOrganizerDataL(organizer);
	delete organizer;
	
	entryObj->SetPhoneOwnerDataL(_L("h2s@gmail.com"));
	
	entryObj->SetPriority(5);
    entryObj->SetSummaryL(_L("Repeating entry"));
    
    TTime stTime(TDateTime(2007, ESeptember, 15, 9, 0, 0, 0));
	entryObj->SetStartTimeL(stTime);
	
	TTime endTime(TDateTime(2007, ESeptember, 15, 9, 30, 0, 0));
	entryObj->SetEndTimeL(endTime);
	
	CCalAlarm* alarm = CCalAlarm::NewL();
	TTime alarmTime(TDateTime(2007,ESeptember, 15, 7, 30, 0, 0));
	//entryObj->SetAlarm(alarmTime);
	delete alarm;
	
    CAttendeeInfo* attendee = CAttendeeInfo::NewL(_L("h2s@gmail.com"));
	attendee->SetRoleL(KAttRoleReqParticipant);
	attendee->SetStatusL(KAttStatusTentative);
    attendee->SetRsvp(EFalse);
    entryObj->AddAttendeeL(attendee);
    delete attendee;
	
	attendee = CAttendeeInfo::NewL(_L("mdcosta@gmail.com"));
	attendee->SetCommonNameL(_L("SAPI"));
	attendee->SetRoleL(KAttRoleReqParticipant);
	attendee->SetStatusL(KAttStatusTentative);
    attendee->SetRsvp(EFalse);
    entryObj->AddAttendeeL(attendee);
    delete attendee;
    
    CRepeatInfo* rrule = CRepeatInfo::NewL(TCalRRule::EDaily);
	//TCalRRule rrule(TCalRRule::EDaily);
	TCalTime startTime;
	startTime.SetTimeUtcL(stTime);
	rrule->SetStartTimeL(stTime);
	TCalTime uTime;
	uTime.SetTimeUtcL(TTime(TDateTime(2007, ESeptember, 29, 0, 0, 0, 0)));
	rrule->SetUntilTimeL(TTime(TDateTime(2007, ESeptember, 29, 9, 0, 0, 0)));
	rrule->SetWeekStart(EWednesday);
	entryObj->SetRepeatRule(rrule);	
	delete rrule;
	
	TTime exDate(TDateTime(2007, ESeptember, 20, 0, 0, 0, 0)); 
    TCalTime exTime;
    exTime.SetTimeUtcL(exDate);
    entryObj->AddExceptionDateL(exDate);
        
    TTime rDate(TDateTime(2007, EOctober, 0, 9, 0, 0, 0)); 
    TCalTime rTime;
    rTime.SetTimeUtcL(rDate);
    entryObj->AddRepeatDateL(rDate);
        
	TRAPD( errno, aService->AddL(name,entryObj,uids) );
	delete entryObj;
	return errno;

    }		
