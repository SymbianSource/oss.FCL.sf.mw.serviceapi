/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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


// SYSTEM INCLUDE FILES
#include <e32base.h>
#include <f32file.h> //for RFile and Rfs

#include <calentry.h>//for CCalEntry
#include <calinstanceview.h>//for CCalInstance
#include <calcommon.h>//for Filter Type Enum Constants
#include <calinstance.h>
#include <caltime.h>
 
// USER INCLUDE FILES
#include "calgetlisttestcases.h"
#include "entryattributes.h"    
//#include <ASCliClientUtils.h>
#include "calendarservice.h"
#include "calendarconstants.h"



CCalGetlistTestCases* CCalGetlistTestCases::NewL( TInt& aResult, TBool aEntryArray) 
	{
	CCalGetlistTestCases* self = new(ELeave)CCalGetlistTestCases( aResult, aEntryArray); 
	
	self->ConstructL();
	
	return self;
	}

CCalGetlistTestCases::~CCalGetlistTestCases()
	{
	Cancel();


    if(iWaitSchedular->IsStarted())
        iWaitSchedular->AsyncStop();
    
    if(iCalendarService)
        delete iCalendarService;
    
    if(iWaitSchedular)
        delete iWaitSchedular;
    

	
	}
	

_LIT(KGetlistTestCalNameGetlistGuidFilterAsync ,"c:getlistcalguidFilterasync");

_LIT(KGetlistTestCalNameGetlistLuidFilterAsync ,"c:getlistcalluidFilterasync");

_LIT(KGetlistTestCalNameGetlistTmRgFilterAsync ,"c:getlistcaltmrgFilterasync");

_LIT(KGetlistTestCalNameGetlistTextFilterAsync ,"c:getlistcaltextFilterasync");

_LIT(KGetlistTestCalNameGetlistTypeFilterAsync ,"c:getlistcaltypeFilterasync");

_LIT(KGetlistTestCalNameGetlistInvalidGuidFilterAsync ,"c:getlistcalinvalidguidFilterasync");

_LIT(KGetlistTestCalNameGetlistInvalidLuidFilterAsync ,"c:getlistcalinvalidluidFilterasync");
	
void CCalGetlistTestCases::TestGetlistGuidFilterAsyncL()	
	{
	iTestCaseType = KGetlistGuidFilterAsync;

	//RemoveCalendarFile(iCalendarService, KGetlistTestCalNameGetlistGuidFilterAsync.operator()());
	TRAP( iResult , iCalendarService->DeleteL( KGetlistTestCalNameGetlistGuidFilterAsync.operator()() ) );
    TRAP( iResult , iCalendarService->AddL( KGetlistTestCalNameGetlistGuidFilterAsync.operator()() ) ); 
	
        
	if(iResult == KErrNone)
		Start();
	}	

void CCalGetlistTestCases::TestGetlistLuidFilterAsyncL()    
    {
    iTestCaseType = KGetlistLuidFilterAsync;

    //RemoveCalendarFile(iCalendarService, KGetlistTestCalNameGetlistLuidiiFilterAsync.operator()());
    TRAP( iResult , iCalendarService->DeleteL( KGetlistTestCalNameGetlistLuidFilterAsync.operator()() ) );
                                        
    TRAP( iResult , iCalendarService->AddL( KGetlistTestCalNameGetlistLuidFilterAsync.operator()() ) ); 
    
    if(iResult == KErrNone)
        Start();
    }   

void CCalGetlistTestCases::TestGetlistTmRgFilterAsyncL()    
    {
    iTestCaseType = KGetlistTmRgFilterAsync;

    //RemoveCalendarFile(iCalendarService, KGetlistTestCalNameGetlistTmRgiiFilterAsync.operator()());
    TRAP( iResult , iCalendarService->DeleteL( KGetlistTestCalNameGetlistTmRgFilterAsync.operator()() ) );
    TRAP( iResult , iCalendarService->AddL( KGetlistTestCalNameGetlistTmRgFilterAsync.operator()() ) ); 
    
    if(iResult == KErrNone)
        Start();
    }   

void CCalGetlistTestCases::TestGetlistTextFilterAsyncL()    
    {
    iTestCaseType = KGetlistTextFilterAsync;

    //RemoveCalendarFile(iCalendarService, KGetlistTestCalNameGetlistTextiiFilterAsync.operator()());
    TRAP( iResult , iCalendarService->DeleteL( KGetlistTestCalNameGetlistTextFilterAsync.operator()() ) );
    TRAP( iResult , iCalendarService->AddL( KGetlistTestCalNameGetlistTextFilterAsync.operator()() ) ); 
    
    if(iResult == KErrNone)
        Start();
    }   

void CCalGetlistTestCases::TestGetlistTypeFilterAsyncL()    
    {
    iTestCaseType = KGetlistTypeFilterAsync;

    //RemoveCalendarFile(iCalendarService, KGetlistTestCalNameGetlistTypeiiFilterAsync.operator()());
    TRAP( iResult , iCalendarService->DeleteL( KGetlistTestCalNameGetlistTypeFilterAsync.operator()() ) );
    TRAP( iResult , iCalendarService->AddL( KGetlistTestCalNameGetlistTypeFilterAsync.operator()() ) ); 
    
    if(iResult == KErrNone)
        Start();
    }  

void CCalGetlistTestCases::TestGetlistInvalidGuidFilterAsyncL()    
    {
    iTestCaseType = KGetlistInvalidGuidFilterAsync;

    //RemoveCalendarFile(iCalendarService, KGetlistTestCalNameGetlistGuidFilterAsync.operator()());
    TRAP( iResult , iCalendarService->DeleteL( KGetlistTestCalNameGetlistInvalidGuidFilterAsync.operator()() ) );
    TRAP( iResult , iCalendarService->AddL( KGetlistTestCalNameGetlistInvalidGuidFilterAsync.operator()() ) ); 
    
        
    if(iResult == KErrNone)
        Start();
    }   

void CCalGetlistTestCases::TestGetlistInvalidLuidFilterAsyncL()    
    {
    iTestCaseType = KGetlistInvalidLuidFilterAsync;

    //RemoveCalendarFile(iCalendarService, KGetlistTestCalNameGetlistLuidiiFilterAsync.operator()());
    TRAP( iResult , iCalendarService->DeleteL( KGetlistTestCalNameGetlistInvalidLuidFilterAsync.operator()() ) );
                                        
    TRAP( iResult , iCalendarService->AddL( KGetlistTestCalNameGetlistInvalidLuidFilterAsync.operator()() ) ); 
    
    if(iResult == KErrNone)
        Start();
    }   

TInt CCalGetlistTestCases::Result()
	{
	return iResult;
	}
	
void CCalGetlistTestCases::ConstructL()
	{	
    CActiveScheduler::Add(this);
    
    iCalendarService = CCalendarService::NewL();
    
    iWaitSchedular = new(ELeave) CActiveSchedulerWait();
	}
	
CCalGetlistTestCases::CCalGetlistTestCases( TInt& aResult, TBool aEntryArray) : CActive(EPriorityStandard), iResult(aResult),
                                                    iEntryArray(aEntryArray),iTestCaseType(KGetlistGuidFilterAsync)
	{

	}
	
//for the sake of ActiveObject
void CCalGetlistTestCases::DoCancel()
	{
	
	}

_LIT(KSearchTexttest                 ,"Meeting");
void CCalGetlistTestCases::RunL()
	{	
    CCalendarFilter *filter = NULL;
    
    CEntryAttributes* entryObj = NULL;
    
    RPointerArray<TUIDSet> arruids(5);
    TUIDSet* uids = NULL;
	
	switch( iTestCaseType )
	    {
	    case KGetlistGuidFilterAsync :
                                        
                                        entryObj = CEntryAttributes::NewL( KEntryAppt );
                                        
                                        entryObj->SetDescriptionL(_L("SAPI weekly meeting"));
                                        entryObj->SetLocationL(_L("Hara"));
                                        entryObj->SetEntryStatusL(KStatusConfirmed);
                                        entryObj->SetMethodL(KMethodNone);
                                        entryObj->SetPriority(5);
                                        entryObj->SetSummaryL(_L("Happens from 9 to 9:30"));
                                        
                                        entryObj->SetStartTimeL( TTime(TDateTime(2007, EAugust, 8, 9, 0, 0, 0)) );
                                        
                                        entryObj->SetEndTimeL(TTime(TDateTime(2007, EAugust, 8, 9, 30, 0, 0)));
                                        
                                        iCalendarService->AddL(KGetlistTestCalNameGetlistGuidFilterAsync,entryObj,uids) ;
                                    
                                        arruids.Append(uids);
                                        uids = NULL;
                                        if ( arruids.Count() > 0 )
                                            {
                                            TRAPD(  err , iCalendarService->GetListL( KGetlistTestCalNameGetlistGuidFilterAsync, *(arruids[0]->iGlobalUID), this ));
                                            if(err != KErrNone)
                                                {
                                                iResult = KErrGeneral;
                                                }
                                            }
                                        
                                   /*     if(iResult != KErrNone)
                                            {
                                            iWaitSchedular->AsyncStop();
                                            }*/
                                        delete entryObj;
                                        arruids.ResetAndDestroy();
                                        break;
        case KGetlistLuidFilterAsync :
                                        entryObj = CEntryAttributes::NewL( KEntryAppt );
                                         
                                         entryObj->SetDescriptionL(_L("SAPI weekly meeting"));
                                         entryObj->SetLocationL(_L("Hara"));
                                         entryObj->SetEntryStatusL(KStatusConfirmed);
                                         entryObj->SetMethodL(KMethodNone);
                                         entryObj->SetPriority(5);
                                         entryObj->SetSummaryL(_L("Happens from 9 to 9:30"));
                                         
                                         entryObj->SetStartTimeL( TTime(TDateTime(2007, EAugust, 8, 9, 0, 0, 0)) );
                                         
                                         entryObj->SetEndTimeL(TTime(TDateTime(2007, EAugust, 8, 9, 30, 0, 0)));
                                         
                                         iCalendarService->AddL(KGetlistTestCalNameGetlistLuidFilterAsync,entryObj,uids) ;
                                         arruids.Append(uids);
                                         uids = NULL;
                                         delete entryObj;
                                         entryObj = CEntryAttributes::NewL( KEntryEvent );
                                             
                                         entryObj->SetDescriptionL(_L("New Event entry created"));
                                         entryObj->SetSummaryL(_L("Event Entry"));
                                         TTime stTime1(TDateTime(2007, EJuly, 25, 0, 0, 0, 0));
                                         entryObj->SetStartTimeL(stTime1);
                                         entryObj->SetReplicationL(KReplPrivate);
                                         
                                         iCalendarService->AddL(KGetlistTestCalNameGetlistLuidFilterAsync,entryObj,uids);
                                         arruids.Append(uids);
                                         uids = NULL;
                                     
                                         if ( arruids.Count() > 0 )
                                             {
                                             TRAPD(  err , iCalendarService->GetListL( KGetlistTestCalNameGetlistLuidFilterAsync, arruids[0]->iLocalUID, this ));
                                             if(err != KErrNone)
                                                 {
                                                 iResult = KErrGeneral;
                                                 }
                                             }
                                         delete entryObj;
                                         arruids.ResetAndDestroy();
                                                                    
                                        break;
        case KGetlistTmRgFilterAsync :
                                        iEntryArray = EFalse;
                                        
                                        entryObj = CEntryAttributes::NewL(KEntryAppt);
                                        entryObj->SetDescriptionL(_L("SAPI weekly meeting"));
                                        entryObj->SetLocationL(_L("Hara"));
                                        entryObj->SetEntryStatusL(KStatusConfirmed);
                                        entryObj->SetMethodL(KMethodNone);
                                        entryObj->SetPriority(5);
                                        entryObj->SetSummaryL(_L("Happens from 9 to 9:30"));
                                        
                                        entryObj->SetStartTimeL( TTime(TDateTime(2007, EAugust, 8, 9, 0, 0, 0)) );
                                        
                                        entryObj->SetEndTimeL(TTime(TDateTime(2007, EAugust, 8, 9, 30, 0, 0)));
                                        
                                        TCalTime stTime;
                                        stTime.SetTimeLocalL(TTime(TDateTime(2007, EAugust, 8, 9, 0, 0, 0)));
                                        entryObj->SetStartTimeL(TTime(TDateTime(2007, EAugust, 8, 9, 0, 0, 0)));
                                        
                                        TCalTime endTime;
                                        endTime.SetTimeLocalL(TTime(TDateTime(2007, EAugust, 8, 9, 30, 0, 0)));
                                        entryObj->SetEndTimeL(TTime(TDateTime(2007, EAugust, 8, 9, 30, 0, 0)));
                                        
                                        CRepeatInfo* rrule = CRepeatInfo::NewL(TCalRRule::EWeekly);
                                        rrule->SetStartTimeL(TTime(TDateTime(2007, EAugust, 8, 9, 0, 0, 0)));
                                        
                                        RArray<TDay> dayArray;
                                        dayArray.Append( stTime.TimeLocalL().DayNoInWeek() );
                                        rrule->SetDaysInWeek( dayArray );
                                        rrule->SetCount( 10 );

                                        entryObj->SetRepeatRule( rrule );
                                        dayArray.Reset();
                                        delete rrule;
                                        
                                        
                                        iCalendarService->AddL(KGetlistTestCalNameGetlistTmRgFilterAsync.operator()(),entryObj,uids);
                                        
                                        
                                        //delete uids;
                                        
                                        
                                        arruids.Append(uids);
                                        uids = NULL;
                                        //delete uids;

                                        if ( arruids.Count() > 0 )
                                            {
                                         //  addSomeEntries( KGetlistTestCalNameGetlistTmRgFilterAsync.operator()() );//adds the entries and fills up iArruids with UIDSets
                                            filter = CCalendarFilter::NewL();
                                            filter->SetStartTimeL(TTime(TDateTime(2007, EAugust, 8, 9, 0, 0, 0)));
                                            filter->SetEndTimeL(TTime(TDateTime(2008, EAugust, 8, 9, 0, 0, 0)));
                                        
                                            TRAP( iResult, iCalendarService->GetListL( KGetlistTestCalNameGetlistTmRgFilterAsync.operator()() , filter , this ) );     
                                            }
                                        if(iResult != KErrNone)
                                            {
                                            iWaitSchedular->AsyncStop();
                                            }
                                        delete entryObj;
                                        arruids.ResetAndDestroy();
                                        delete filter;
 
                                        break;
        case KGetlistTextFilterAsync :
                                        iEntryArray = EFalse;
                                        entryObj = CEntryAttributes::NewL(KEntryAppt);
                                        
                                        entryObj->SetDescriptionL(_L("SAPI weekly meeting"));
                                        entryObj->SetLocationL(_L("Hara"));
                                        entryObj->SetEntryStatusL(KStatusConfirmed);
                                        entryObj->SetMethodL(KMethodNone);
                                        entryObj->SetPriority(5);
                                        entryObj->SetSummaryL(_L("Meeting Happens from 9 to 9:30"));
                                        
                                        TCalTime stTime3;
                                        stTime3.SetTimeLocalL(TTime(TDateTime(2007, EAugust, 8, 9, 0, 0, 0)));
                                        entryObj->SetStartTimeL(TTime(TDateTime(2007, EAugust, 8, 9, 0, 0, 0)));
                                        
                                        TCalTime endTime3;
                                        endTime3.SetTimeLocalL(TTime(TDateTime(2007, EAugust, 8, 9, 30, 0, 0)));
                                        entryObj->SetEndTimeL(TTime(TDateTime(2007, EAugust, 8, 9, 30, 0, 0)));
                                        
                                        iCalendarService->AddL(KGetlistTestCalNameGetlistTextFilterAsync.operator()(),entryObj,uids);
                                        arruids.Append(uids);
                                        uids = NULL;
                        
                                        if ( arruids.Count() > 0 )
                                            {
                                         //  addSomeEntries( KGetlistTestCalNameGetlistTmRgFilterAsync.operator()() );//adds the entries and fills up iArruids with UIDSets
                                            filter = CCalendarFilter::NewL();
                                            filter->SetFilterTextL( KSearchTexttest );
                                         
                                            TRAP( iResult, iCalendarService->GetListL( KGetlistTestCalNameGetlistTextFilterAsync.operator()() , filter , this ) );     
                                            }
                                        if(iResult != KErrNone)
                                            {
                                            iWaitSchedular->AsyncStop();
                                            }
                                        delete entryObj;
                                        arruids.ResetAndDestroy();
                                        delete filter;
                    
                                        break;
        case KGetlistTypeFilterAsync :
                                        iEntryArray = EFalse;
                                        entryObj = CEntryAttributes::NewL(KEntryAppt);
                                        
                                        entryObj->SetDescriptionL(_L("SAPI weekly meeting"));
                                        entryObj->SetLocationL(_L("Hara"));
                                        entryObj->SetEntryStatusL(KStatusConfirmed);
                                        entryObj->SetMethodL(KMethodNone);
                                        entryObj->SetPriority(5);
                                        entryObj->SetSummaryL(_L("Meeting Happens from 9 to 9:30"));
                                        
                                        TCalTime stTime2;
                                        stTime2.SetTimeLocalL(TTime(TDateTime(2007, EAugust, 8, 9, 0, 0, 0)));
                                        entryObj->SetStartTimeL(TTime(TDateTime(2007, EAugust, 8, 9, 0, 0, 0)));
                                        
                                        TCalTime endTime2;
                                        endTime2.SetTimeLocalL(TTime(TDateTime(2007, EAugust, 8, 9, 30, 0, 0)));
                                        entryObj->SetEndTimeL(TTime(TDateTime(2007, EAugust, 8, 9, 30, 0, 0)));
                                        
                                        iCalendarService->AddL(KGetlistTestCalNameGetlistTextFilterAsync.operator()(),entryObj,uids);
                                        arruids.Append(uids);
                                        uids = NULL;
                            
                                        if ( arruids.Count() > 0 )
                                            {
                                         //  addSomeEntries( KGetlistTestCalNameGetlistTmRgFilterAsync.operator()() );//adds the entries and fills up iArruids with UIDSets
                                            filter = CCalendarFilter::NewL();
                                            filter->SetFilterTypeL( KEntryAppt );
                                         
                                            TRAP( iResult, iCalendarService->GetListL( KGetlistTestCalNameGetlistTextFilterAsync.operator()() , filter , this ) );     
                                            }
                                        if(iResult != KErrNone)
                                            {
                                            iWaitSchedular->AsyncStop();
                                            }
                                        delete entryObj;
                                        arruids.ResetAndDestroy();
                                        delete filter;
                            
                                        break;
        case KGetlistInvalidGuidFilterAsync :
                                        
                                        entryObj = CEntryAttributes::NewL( KEntryAppt );
                                        
                                        entryObj->SetDescriptionL(_L("SAPI weekly meeting"));
                                        entryObj->SetLocationL(_L("Hara"));
                                        entryObj->SetEntryStatusL(KStatusConfirmed);
                                        entryObj->SetMethodL(KMethodNone);
                                        entryObj->SetPriority(5);
                                        entryObj->SetSummaryL(_L("Happens from 9 to 9:30"));
                                        
                                        entryObj->SetStartTimeL( TTime(TDateTime(2007, EAugust, 8, 9, 0, 0, 0)) );
                                        
                                        entryObj->SetEndTimeL(TTime(TDateTime(2007, EAugust, 8, 9, 30, 0, 0)));
                                        
                                        iCalendarService->AddL(KGetlistTestCalNameGetlistInvalidGuidFilterAsync,entryObj,uids) ;
                                    
                                        arruids.Append(uids);
                                        uids = NULL;
                                        if ( arruids.Count() > 0 )
                                            {
                                            TRAPD(  err , iCalendarService->GetListL( KGetlistTestCalNameGetlistInvalidGuidFilterAsync,_L8("xyz"), this ));
                                            if(err != KErrNone)
                                                {
                                                iResult = KErrGeneral;
                                                }
                                            }
                                        
                                        if(iResult != KErrNone)
                                            {
                                            iWaitSchedular->AsyncStop();
                                            }
                                        delete entryObj;
                                        arruids.ResetAndDestroy();
                                        break;
        case KGetlistInvalidLuidFilterAsync :
                                        entryObj = CEntryAttributes::NewL( KEntryAppt );
                                         
                                         entryObj->SetDescriptionL(_L("SAPI weekly meeting"));
                                         entryObj->SetLocationL(_L("Hara"));
                                         entryObj->SetEntryStatusL(KStatusConfirmed);
                                         entryObj->SetMethodL(KMethodNone);
                                         entryObj->SetPriority(5);
                                         entryObj->SetSummaryL(_L("Happens from 9 to 9:30"));
                                         
                                         entryObj->SetStartTimeL( TTime(TDateTime(2007, EAugust, 8, 9, 0, 0, 0)) );
                                         
                                         entryObj->SetEndTimeL(TTime(TDateTime(2007, EAugust, 8, 9, 30, 0, 0)));
                                         
                                         iCalendarService->AddL(KGetlistTestCalNameGetlistInvalidLuidFilterAsync,entryObj,uids) ;
                                         arruids.Append(uids);
                                         uids = NULL;
                                     
                                         if ( arruids.Count() > 0 )
                                             {
                                             TRAPD(  err , iCalendarService->GetListL( KGetlistTestCalNameGetlistInvalidLuidFilterAsync, _L8("0"), this ));
                                             if(err != KErrNone)
                                                 {
                                                 iResult = KErrGeneral;
                                                 }
                                             }
                                         if(iResult != KErrNone)
                                             {
                                             iWaitSchedular->AsyncStop();
                                             }
                                         delete entryObj;
                                         arruids.ResetAndDestroy();
                                                                    
                                        break;
                           
	    }

	}
			
void CCalGetlistTestCases::Start()
	{
    SetActive();
    TRequestStatus* temp = &iStatus;
    
    User::RequestComplete(temp, KErrNone);
    
    iWaitSchedular->Start();    
	}

			
void CCalGetlistTestCases::NotifyResultL(TInt aErrCode, TAny* aResult)
	{
    //******************* set iResult ****************************
    iResult = aErrCode;
    //******************* set iResult ****************************
    //write the result to the corresponding file basing on the iTestCaseType
    RPointerArray<CCalEntry> entryList;
    
    RPointerArray<CCalInstance> instanceList;
    
    if(iEntryArray)
        {
        entryList = *(RPointerArray<CCalEntry>*)(aResult);
        }
    else
        {
        instanceList = *(RPointerArray<CCalInstance>*)(aResult);
        }
    switch( iTestCaseType )
        {
        case KGetlistGuidFilterAsync :
        case KGetlistLuidFilterAsync :
        case KGetlistTmRgFilterAsync :
        case KGetlistTextFilterAsync :
        case KGetlistTypeFilterAsync :
                                       if(iEntryArray)
                                           {
                                           if ( entryList.Count() == 0)
                                                       {
                                                       iResult = KErrGeneral;
                                                       }
                                           else
                                               {
                                               for(TInt i = 0; i<entryList.Count(); i++)
                                                   {
                                                   delete entryList[i];
                                                   }
                                               }
                                           }
                                       else
                                           {
                                           if((instanceList.Count() == 0))
                                                       {
                                                       iResult = KErrGeneral;
                                                       }
                                           else
                                               {
                                               for(TInt i = 0; i<instanceList.Count(); i++)
                                                   {
                                                   delete instanceList[i];
                                                   }
                                               }
                                           
                                           }
                                       break;
        case KGetlistInvalidLuidFilterAsync :
        case KGetlistInvalidGuidFilterAsync :
                                        if ( entryList.Count() > 0)
                                                    {
                                                    iResult = KErrGeneral;
                                                    }
                                        break;
       }
    iWaitSchedular->AsyncStop();
    
	}
