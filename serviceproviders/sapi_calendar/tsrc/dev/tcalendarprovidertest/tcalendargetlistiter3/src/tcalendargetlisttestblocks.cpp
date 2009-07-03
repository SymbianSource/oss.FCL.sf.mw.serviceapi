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


#include <BADESCA.H>
#include<LiwServiceHandler.h>



#include "tcalendargetlisttest.h"
#include "calendarheader.h"
//#include "calendarconstants.h"
// ============================ MEMBER FUNCTIONS ===============================

TInt RemoveProvCalendar(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar);
TInt AddProvCalendar(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar);
TInt AddProvAppointmentDailyRepeat(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset);
TInt AddProvEvent(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset);
TInt AddAppointmentProvLocal(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset);

void GetLocalUid( const TDesC& aLocalUid, TCalLocalUid& aOutLocalUid );
void GetGlobalUid( const TDesC& aGlobalUid, TDes8& aOutGlobalUid );
TDesC& GetEntry(MLiwInterface* interface, CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, TPtrC globaluid, const TDesC& calname);

_LIT8(KIDataSource, "IDataSource");
_LIT8(KService, "Service.Calendar");

_LIT8(KCmdGetList,"GetList");
_LIT8(KCmdDelete,"Delete");
_LIT8(KCmdAdd,"Add");
_LIT8(KContentType, 		"Type");
_LIT8(KCalendarName,        "CalendarName");
_LIT8(KFilter, 				"Filter");	
const TChar KUidSeparator = ':';

// -----------------------------------------------------------------------------
// CTChangeStatusTest::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTCalendarGetListTest::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CTChangeStatusTest::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTCalendarGetListTest::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        //TRY( "SendMessage",    CTDeleteMessageTest::SendMessage ),
        
        ENTRY( "GetListCalendar",    	CTCalendarGetListTest::GetListCalendar ),
        ENTRY( "GetDefaultCalendar",    CTCalendarGetListTest::GetDefaultCalendar ),
        ENTRY( "GetListGUidFilter",    	CTCalendarGetListTest::GetListGUidFilter ),
        ENTRY( "GetListLocalUidFilter", CTCalendarGetListTest::GetListLocalUidFilter ),
        ENTRY( "GetListTimeRangeFilter",CTCalendarGetListTest::GetListTimeRangeFilter ),
        ENTRY( "GetListTextFilter",    	CTCalendarGetListTest::GetListTextFilter ),
        ENTRY( "GetListTypeFilter",    	CTCalendarGetListTest::GetListTypeFilter ),
		ENTRY( "GetListInvalidCalName", CTCalendarGetListTest::GetListInvalidCalName ),
		ENTRY( "GetListInvalidGUID"   , CTCalendarGetListTest::GetListInvalidGUID ),
		ENTRY( "GetListInvalidLUID"   , CTCalendarGetListTest::GetListInvalidLUID ),
        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

	
	
_LIT(KSearchTexttest                 ,"Meeting");

_LIT(KDefaultCalendar                ,"C:Calendar");

_LIT(KTestCal1File, "C:getlistcal1");
_LIT(KTestCal2File, "C:getlistcal2");


//	
//Whats done here? 
//	Get all the Calendars in the system using GetList of CCalendarService and output that to GetListallCalendars.txt
//
TInt CTCalendarGetListTest::GetListCalendar(CStifItemParser& /*aItem*/ )
	{
	TInt result=KErrNone;     
    
	__UHEAP_MARK;
// Iter-3 test work
	CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    
    CLiwGenericParamList* inParamList = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outParamList = &(iServiceHandler->OutParamListL());
    
    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);
    crit->SetServiceClass(TUid::Uid(KLiwClassBase));
    
    RCriteriaArray a;
    
    a.AppendL(crit);    
    
    iServiceHandler->AttachL(a);
    
	iServiceHandler->ExecuteServiceCmdL(*crit, *inParamList, *outParamList); 
	
	delete crit;
	crit = NULL;
	a.Reset();
	
	TInt pos = 0;
    MLiwInterface* interface = NULL;
    outParamList->FindFirst(pos,KIDataSource );
    if(pos != KErrNotFound)
        {
        interface = (*outParamList)[pos].Value().AsInterface();	
        }

	inParamList->Reset();
	outParamList->Reset();
	// Iter-2 same
	
	TInt added = 0;
	
	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal2File);


	if( AddProvCalendar(inParamList, outParamList, interface, KTestCal1File) == KErrNone)
		{
		added++;
		};
	
	if( AddProvCalendar(inParamList, outParamList, interface, KTestCal2File) == KErrNone)
		{
		added++;
		};
	
	TLiwVariant content(_L("Calendar"));
	TLiwGenericParam element1;	
	element1.SetNameAndValueL(_L8("Type"),content);
	inParamList->AppendL(element1);
	content.Reset();
	element1.Reset();


	TInt err = 0;
	TRAP(err,interface->ExecuteCmdL( KCmdGetList ,*inParamList ,*outParamList));
    pos = 0 ;
    
    const TLiwGenericParam* output = outParamList->FindFirst( pos,_L8("ReturnValue"));
	
	if(output)     
		{
		CLiwIterable* iterlist = output->Value().AsIterable();

	    TLiwVariant data;
	    TInt itemfound = 0;
      
        while( iterlist->NextL(data))
			{
			itemfound++;
	  		}
	  		
	  	data.Reset();	
	  	
	  	if(itemfound < added)	
	  	result = KErrGeneral;
		}

	inParamList->Reset();
	outParamList->Reset();

	interface->Close();
	iServiceHandler->Reset();
	delete iServiceHandler;

    __UHEAP_MARKEND;	

	return result;

    }

TInt CTCalendarGetListTest::GetDefaultCalendar(CStifItemParser& /*aItem*/ )
	{
	TInt result=KErrNone;     
    
	__UHEAP_MARK;
// Iter-3 test work
	CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    
    CLiwGenericParamList* inParamList = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outParamList = &(iServiceHandler->OutParamListL());
    
    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);
    crit->SetServiceClass(TUid::Uid(KLiwClassBase));
    
    RCriteriaArray a;
    
    a.AppendL(crit);    
    
    iServiceHandler->AttachL(a);
    
	iServiceHandler->ExecuteServiceCmdL(*crit, *inParamList, *outParamList); 
	
	delete crit;
	crit = NULL;
	a.Reset();
	
	TInt pos = 0;
    MLiwInterface* interface = NULL;
    outParamList->FindFirst(pos,KIDataSource );
    if(pos != KErrNotFound)
        {
        interface = (*outParamList)[pos].Value().AsInterface();	
        }

	inParamList->Reset();
	outParamList->Reset();
	// Iter-2 same
	
	TLiwVariant content(_L("Calendar"));
	TLiwGenericParam element1;	
	element1.SetNameAndValueL(_L8("Type"),content);
	inParamList->AppendL(element1);
	content.Reset();
	element1.Reset();
	
	
   	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

    map->InsertL(_L8("DefaultCalendar"), TLiwVariant(ETrue) ); 
    
    TLiwVariant filterparam(map);
	TLiwGenericParam element ;	
	element.SetNameAndValueL(_L8("Filter"),filterparam);
	filterparam.Reset();
	
	inParamList->AppendL(element);
	element.Reset();
    map->DecRef();
    CleanupStack::Pop(map);

	TInt err = 0;
	TRAP(err,interface->ExecuteCmdL( KCmdGetList ,*inParamList ,*outParamList));
    pos = 0 ;
    
    const TLiwGenericParam* output = outParamList->FindFirst( pos,_L8("ReturnValue"));
	
	if(output)     
		{
		CLiwIterable* iterlist = output->Value().AsIterable();

	    TLiwVariant data;
	    TInt itemfound = 0;
      
        while( iterlist->NextL(data))
			{
			itemfound++;
	  		}
	  		
	  	data.Reset();	
	  	
	  	if(itemfound != 1)	
	  		result = KErrGeneral;
		}

	inParamList->Reset();
	outParamList->Reset();

	interface->Close();
	iServiceHandler->Reset();
	delete iServiceHandler;

    __UHEAP_MARKEND;	

	return result;

    }
 
 
TInt CTCalendarGetListTest::GetListGUidFilter(CStifItemParser& /*aItem*/ )
	{
	TInt result=KErrNone;     
    
	__UHEAP_MARK;
// Iter-3 test work
	CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    
    CLiwGenericParamList* inParamList = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outParamList = &(iServiceHandler->OutParamListL());
    
    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);
    crit->SetServiceClass(TUid::Uid(KLiwClassBase));
    
    RCriteriaArray a;
    
    a.AppendL(crit);    
    
    iServiceHandler->AttachL(a);
    
	iServiceHandler->ExecuteServiceCmdL(*crit, *inParamList, *outParamList); 
	
	delete crit;
	crit = NULL;
	a.Reset();
	
	TInt pos = 0;
    MLiwInterface* interface = NULL;
    outParamList->FindFirst(pos,KIDataSource );
    if(pos != KErrNotFound)
        {
        interface = (*outParamList)[pos].Value().AsInterface();	
        }

	inParamList->Reset();
	outParamList->Reset();
	
	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	
	AddProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	
	RPointerArray<TUIDSet> arruids(5);
	
	TUIDSet* uids = NULL;
	
	if(AddProvAppointmentDailyRepeat(inParamList, outParamList, interface, KTestCal1File, uids) == KErrNone && uids)
		{
		arruids.Append(uids);
		uids = NULL;
		}

	if(AddProvEvent(inParamList, outParamList, interface, KTestCal1File, uids) == KErrNone && uids)
		{
		arruids.Append(uids);
		uids = NULL;
		}
	
	if ( arruids.Count() > 0 )
		{
			TLiwVariant content(_L("CalendarEntry"));
			TLiwGenericParam element1;	
			element1.SetNameAndValueL(_L8("Type"),content);
			inParamList->AppendL(element1);
			content.Reset();
			element1.Reset();
			
			
		   	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
			CleanupStack::PushL(map);

		    map->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal1File) ); 
		    
			TBuf<100> gid;
			gid.Copy( arruids[0]->iGlobalUID->Des() );
		    map->InsertL(_L8("id"), TLiwVariant(gid) ); 
		    
		    TLiwVariant filterparam(map);
			TLiwGenericParam element ;	
			element.SetNameAndValueL(_L8("Filter"),filterparam);
			filterparam.Reset();
			
			inParamList->AppendL(element);
			element.Reset();
		    map->DecRef();
		    CleanupStack::Pop(map);

			TInt err = 0;
			TRAP(err,interface->ExecuteCmdL( KCmdGetList ,*inParamList ,*outParamList));
		    pos = 0 ;
		    
		    const TLiwGenericParam* output = outParamList->FindFirst( pos,_L8("ReturnValue"));
			
			if(output)     
				{
				CLiwIterable* iterlist = output->Value().AsIterable();

			    TLiwVariant data;
			    TInt itemfound = 0;
			    TBool uidmatched = EFalse;
		      
		        while( iterlist->NextL(data))
					{
					const CLiwMap* res = data.AsMap();
					if ( res )
						{
						itemfound++;
						TLiwVariant guid;
						if(res->FindL(_L8("id"), guid))
							{
							HBufC8* globaluid = HBufC8::NewL(guid.AsDes().Length()) ;
							globaluid->Des().Copy(guid.AsDes());
							
							if(globaluid->Des().CompareF(arruids[0]->iGlobalUID->Des()) == 0)
								uidmatched = ETrue;	
							
							delete globaluid;
							}

						guid.Reset();	
						}
			  		}
			  		
			  	data.Reset();	
			  	
			  	if(itemfound != 1 || !uidmatched)	
			  		result = KErrGeneral;
				}

			inParamList->Reset();
			outParamList->Reset();
	    
	    arruids.ResetAndDestroy();
		}
	else
		result = KErrGeneral;	
	
	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	
	
	interface->Close();
	iServiceHandler->Reset();
	delete iServiceHandler;

    __UHEAP_MARKEND;	

	return result;

    }
 

TInt CTCalendarGetListTest::GetListLocalUidFilter(CStifItemParser& /*aItem*/ )
	{
	TInt result=KErrNone;     
    
	__UHEAP_MARK;
// Iter-3 test work
	CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    
    CLiwGenericParamList* inParamList = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outParamList = &(iServiceHandler->OutParamListL());
    
    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);
    crit->SetServiceClass(TUid::Uid(KLiwClassBase));
    
    RCriteriaArray a;
    
    a.AppendL(crit);    
    
    iServiceHandler->AttachL(a);
    
	iServiceHandler->ExecuteServiceCmdL(*crit, *inParamList, *outParamList); 
	
	delete crit;
	crit = NULL;
	a.Reset();
	
	TInt pos = 0;
    MLiwInterface* interface = NULL;
    outParamList->FindFirst(pos,KIDataSource );
    if(pos != KErrNotFound)
        {
        interface = (*outParamList)[pos].Value().AsInterface();	
        }

	inParamList->Reset();
	outParamList->Reset();
	
	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	
	AddProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	
	RPointerArray<TUIDSet> arruids(5);
	
	TUIDSet* uids = NULL;
	
	if(AddProvAppointmentDailyRepeat(inParamList, outParamList, interface, KTestCal1File, uids) == KErrNone && uids)
		{
		arruids.Append(uids);
		uids = NULL;
		}

	if(AddProvEvent(inParamList, outParamList, interface, KTestCal1File, uids) == KErrNone && uids)
		{
		arruids.Append(uids);
		uids = NULL;
		}
	
	if ( arruids.Count() > 0 )
		{
			TLiwVariant content(_L("CalendarEntry"));
			TLiwGenericParam element1;	
			element1.SetNameAndValueL(_L8("Type"),content);
			inParamList->AppendL(element1);
			content.Reset();
			element1.Reset();
			
			
		   	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
			CleanupStack::PushL(map);

		    map->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal1File) ); 
		    TBuf<50> globaluid;
		    TBuf<10> luid;
		    //luid.Num(TInt64(arruids[0]->iLocalUID));
		    globaluid.Copy(arruids[0]->iGlobalUID->Des());
		    luid = GetEntry(interface, inParamList, outParamList, globaluid, KTestCal1File);
		    map->InsertL(_L8("LocalId"), TLiwVariant(luid)); 
		    
		    TLiwVariant filterparam(map);
			TLiwGenericParam element ;	
			element.SetNameAndValueL(_L8("Filter"),filterparam);
			filterparam.Reset();
			
			inParamList->AppendL(element);
			element.Reset();
		    map->DecRef();
		    CleanupStack::Pop(map);

			TInt err = 0;
			TRAP(err,interface->ExecuteCmdL( KCmdGetList ,*inParamList ,*outParamList));
		    pos = 0 ;
		    
		    const TLiwGenericParam* output = outParamList->FindFirst( pos,_L8("ReturnValue"));
			
			if(output)     
				{
				CLiwIterable* iterlist = output->Value().AsIterable();

			    TLiwVariant data;
			    TInt itemfound = 0;
			    TBool uidmatched = EFalse;
		      
		        while( iterlist->NextL(data))
					{
					const CLiwMap* res = data.AsMap();
					if ( res )
						{
						itemfound++;
						TLiwVariant luid;
						if(res->FindL(_L8("id"), luid))
							{
							/*TLex lex(luid.AsDes());
							TInt32 num;
							lex.Val(num);
							
							TUint localuid = 0;
							localuid = TUint(num);
							
							if(localuid == arruids[0]->iLocalUID)
								uidmatched = ETrue;*/	
							
							

							HBufC8* globaluid = HBufC8::NewL(luid.AsDes().Length()) ;
							globaluid->Des().Copy(luid.AsDes());
							
							if(globaluid->Des().CompareF(arruids[0]->iGlobalUID->Des()) == 0)
								uidmatched = ETrue;	
							
							delete globaluid;
							}
						luid.Reset();	
						}
			  		}
			  		
			  	data.Reset();	
			  	
			  	if(itemfound != 1 || !uidmatched)	
			  		result = KErrGeneral;
				}

			inParamList->Reset();
			outParamList->Reset();
	    
	    arruids.ResetAndDestroy();
		}
	else
		result = KErrGeneral;	
	
	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	
	
	interface->Close();
	iServiceHandler->Reset();
	delete iServiceHandler;

    __UHEAP_MARKEND;	

	return result;
    }
    

//	
//Whats done here? 
//	Get the default system Calendar using GetList of CCalendarService and output that to GetListdefaultCalendar.txt
//    
TInt CTCalendarGetListTest::GetListTimeRangeFilter(CStifItemParser& /*aItem*/ )
	{
	TInt result=KErrNone;     
    
	__UHEAP_MARK;
// Iter-3 test work
	CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    
    CLiwGenericParamList* inParamList = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outParamList = &(iServiceHandler->OutParamListL());
    
    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);
    crit->SetServiceClass(TUid::Uid(KLiwClassBase));
    
    RCriteriaArray a;
    
    a.AppendL(crit);    
    
    iServiceHandler->AttachL(a);
    
	iServiceHandler->ExecuteServiceCmdL(*crit, *inParamList, *outParamList); 
	
	delete crit;
	crit = NULL;
	a.Reset();
	
	TInt pos = 0;
    MLiwInterface* interface = NULL;
    outParamList->FindFirst(pos,KIDataSource );
    if(pos != KErrNotFound)
        {
        interface = (*outParamList)[pos].Value().AsInterface();	
        }

	inParamList->Reset();
	outParamList->Reset();
	
	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	
	AddProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	
	TUIDSet* uids = NULL;
	
	if(AddAppointmentProvLocal(inParamList, outParamList, interface, KTestCal1File, uids) == KErrNone && uids)
		{
		}

	
	if ( uids )
		{
			TLiwVariant content(_L("CalendarEntry"));
			TLiwGenericParam element1;	
			element1.SetNameAndValueL(_L8("Type"),content);
			inParamList->AppendL(element1);
			content.Reset();
			element1.Reset();
			
			
		   	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
			CleanupStack::PushL(map);

		    map->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal1File) ); 
		    map->InsertL(_L8("StartRange"), TLiwVariant(TTime(TDateTime(2007,EOctober,23,10,0,0,0))) ); 
		    map->InsertL(_L8("EndRange"), TLiwVariant(TTime(TDateTime(2007,EOctober,30,10,30,0,0))) ); 
		    
		    TLiwVariant filterparam(map);
			TLiwGenericParam element ;	
			element.SetNameAndValueL(_L8("Filter"),filterparam);
			filterparam.Reset();
			
			inParamList->AppendL(element);
			element.Reset();
		    map->DecRef();
		    CleanupStack::Pop(map);

			TInt err = 0;
			TRAP(err,interface->ExecuteCmdL( KCmdGetList ,*inParamList ,*outParamList));
		    pos = 0 ;
		    
		    const TLiwGenericParam* output = outParamList->FindFirst( pos,_L8("ReturnValue"));
			
			if(output)     
				{
				CLiwIterable* iterlist = output->Value().AsIterable();

			    TLiwVariant data;
			    TInt itemfound = 0;
		      
		        while( iterlist->NextL(data))
					{
					const CLiwMap* res = data.AsMap();
					if ( res )
						{
						itemfound++;
						}
			  		}
			  		
			  	data.Reset();	
			  	
			  	if(itemfound != 8 )	
			  		result = KErrGeneral;
				}

			inParamList->Reset();
			outParamList->Reset();
	    
		}
	else
		result = KErrGeneral;	
	
	delete uids;
	
	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	
	
	interface->Close();
	iServiceHandler->Reset();
	delete iServiceHandler;

    __UHEAP_MARKEND;	

	return result;
	
	}

  
//	
//Whats done here? 
//	Get the default system Calendar using GetList of CCalendarService and output that to GetListdefaultCalendar.txt
//       
TInt CTCalendarGetListTest::GetListTextFilter(CStifItemParser& /*aItem*/ )
	{
	TInt result=KErrNone;     
    
	__UHEAP_MARK;
// Iter-3 test work
	CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    
    CLiwGenericParamList* inParamList = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outParamList = &(iServiceHandler->OutParamListL());
    
    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);
    crit->SetServiceClass(TUid::Uid(KLiwClassBase));
    
    RCriteriaArray a;
    
    a.AppendL(crit);    
    
    iServiceHandler->AttachL(a);
    
	iServiceHandler->ExecuteServiceCmdL(*crit, *inParamList, *outParamList); 
	
	delete crit;
	crit = NULL;
	a.Reset();
	
	TInt pos = 0;
    MLiwInterface* interface = NULL;
    outParamList->FindFirst(pos,KIDataSource );
    if(pos != KErrNotFound)
        {
        interface = (*outParamList)[pos].Value().AsInterface();	
        }

	inParamList->Reset();
	outParamList->Reset();
	
	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	
	AddProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	
	TUIDSet* uids = NULL;
	
	if(AddAppointmentProvLocal(inParamList, outParamList, interface, KTestCal1File, uids) == KErrNone && uids)
		{
		}

	
	if ( uids )
		{
			TLiwVariant content(_L("CalendarEntry"));
			TLiwGenericParam element1;	
			element1.SetNameAndValueL(_L8("Type"),content);
			inParamList->AppendL(element1);
			content.Reset();
			element1.Reset();
			
			
		   	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
			CleanupStack::PushL(map);

		    map->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal1File) ); 
		    map->InsertL(_L8("SearchText"), TLiwVariant(_L("Meeting")) ); 
		    
		    TLiwVariant filterparam(map);
			TLiwGenericParam element ;	
			element.SetNameAndValueL(_L8("Filter"),filterparam);
			filterparam.Reset();
			
			inParamList->AppendL(element);
			element.Reset();
		    map->DecRef();
		    CleanupStack::Pop(map);

			TInt err = 0;
			TRAP(err,interface->ExecuteCmdL( KCmdGetList ,*inParamList ,*outParamList));
		    pos = 0 ;
		    
		    const TLiwGenericParam* output = outParamList->FindFirst( pos,_L8("ReturnValue"));
			
			if(output)     
				{
				CLiwIterable* iterlist = output->Value().AsIterable();

			    TLiwVariant data;
			    TInt itemfound = 0;
		      
		        while( iterlist->NextL(data))
					{
					const CLiwMap* res = data.AsMap();
					if ( res )
						{
						TLiwVariant luid;
						if(res->FindL(_L8("Summary"), luid))
							{
							TPtrC localuid = luid.AsDes();
							if(localuid.FindF(_L("Meeting")) != KErrNotFound )
								itemfound++;
							}

						luid.Reset();	
						}
			  		}
			  		
			  	data.Reset();	
			  	
			  	if(itemfound != 8 )	
			  		result = KErrGeneral;
				}

			inParamList->Reset();
			outParamList->Reset();
	    
		}
	else
		result = KErrGeneral;	
	
	delete uids;
	
	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	
	
	interface->Close();
	iServiceHandler->Reset();
	delete iServiceHandler;

    __UHEAP_MARKEND;	

	return result;
	
	
    }
    

//	
//Whats done here? 
//	Get the default system Calendar using GetList of CCalendarService and output that to GetListdefaultCalendar.txt
//           
TInt CTCalendarGetListTest::GetListTypeFilter(CStifItemParser& /*aItem*/ )
	{

	TInt result=KErrNone;     
    
	__UHEAP_MARK;
// Iter-3 test work
	CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    
    CLiwGenericParamList* inParamList = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outParamList = &(iServiceHandler->OutParamListL());
    
    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);
    crit->SetServiceClass(TUid::Uid(KLiwClassBase));
    
    RCriteriaArray a;
    
    a.AppendL(crit);    
    
    iServiceHandler->AttachL(a);
    
	iServiceHandler->ExecuteServiceCmdL(*crit, *inParamList, *outParamList); 
	
	delete crit;
	crit = NULL;
	a.Reset();
	
	TInt pos = 0;
    MLiwInterface* interface = NULL;
    outParamList->FindFirst(pos,KIDataSource );
    if(pos != KErrNotFound)
        {
        interface = (*outParamList)[pos].Value().AsInterface();	
        }

	inParamList->Reset();
	outParamList->Reset();
	
	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	
	AddProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	
	TUIDSet* uids = NULL;
	
	if(AddAppointmentProvLocal(inParamList, outParamList, interface, KTestCal1File, uids) == KErrNone && uids)
		{
		}

	TUIDSet* tmpuids = NULL;
	
	if(AddProvEvent(inParamList, outParamList, interface, KTestCal1File, tmpuids) == KErrNone && tmpuids)
		{
		delete tmpuids;
		}
	
	
	if ( uids )
		{
			TLiwVariant content(_L("CalendarEntry"));
			TLiwGenericParam element1;	
			element1.SetNameAndValueL(_L8("Type"),content);
			inParamList->AppendL(element1);
			content.Reset();
			element1.Reset();
			
			
		   	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
			CleanupStack::PushL(map);

		    map->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal1File) ); 
		    map->InsertL(_L8("Type"), TLiwVariant(_L("Meeting")) ); 
		    
		    TLiwVariant filterparam(map);
			TLiwGenericParam element ;	
			element.SetNameAndValueL(_L8("Filter"),filterparam);
			filterparam.Reset();
			
			inParamList->AppendL(element);
			element.Reset();
		    map->DecRef();
		    CleanupStack::Pop(map);

			TInt err = 0;
			TRAP(err,interface->ExecuteCmdL( KCmdGetList ,*inParamList ,*outParamList));
		    pos = 0 ;
		    
		    const TLiwGenericParam* output = outParamList->FindFirst( pos,_L8("ReturnValue"));
			
			if(output)     
				{
				CLiwIterable* iterlist = output->Value().AsIterable();

			    TLiwVariant data;
			    TInt itemfound = 0;
		      
		        while( iterlist->NextL(data))
					{
					const CLiwMap* res = data.AsMap();
					if ( res )
						{
						TLiwVariant luid;
						if(res->FindL(_L8("Type"), luid))
							{
							TPtrC localuid = luid.AsDes();
							if(localuid.CompareF(_L("Meeting")) == 0 )
								itemfound++;
							}

						luid.Reset();	
						}
			  		}
			  		
			  	data.Reset();	
			  	
			  	if(itemfound != 8 )	
			  		result = KErrGeneral;
				}

			inParamList->Reset();
			outParamList->Reset();
	    
		}
	else
		result = KErrGeneral;	
	
	delete uids;
	
	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	
	
	interface->Close();
	iServiceHandler->Reset();
	delete iServiceHandler;

    __UHEAP_MARKEND;	

	return result;
	
	}
	
	
//	
//Whats done here? 
//	Get the default system Calendar using GetList of CCalendarService and output that to GetListdefaultCalendar.txt
//       
TInt CTCalendarGetListTest::GetListInvalidCalName(CStifItemParser& /*aItem*/ )
	{
	TInt result=KErrNone;     
    
	__UHEAP_MARK;
// Iter-3 test work
	CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    
    CLiwGenericParamList* inParamList = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outParamList = &(iServiceHandler->OutParamListL());
    
    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);
    crit->SetServiceClass(TUid::Uid(KLiwClassBase));
    
    RCriteriaArray a;
    
    a.AppendL(crit);    
    
    iServiceHandler->AttachL(a);
    
	iServiceHandler->ExecuteServiceCmdL(*crit, *inParamList, *outParamList); 
	
	delete crit;
	crit = NULL;
	a.Reset();
	
	TInt pos = 0;
    MLiwInterface* interface = NULL;
    outParamList->FindFirst(pos,KIDataSource );
    if(pos != KErrNotFound)
        {
        interface = (*outParamList)[pos].Value().AsInterface();	
        }

	inParamList->Reset();
	outParamList->Reset();
	// Iter-2 same
	
	TInt added = 0;
	
	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	
	TLiwVariant content(_L("CalendarEntry"));
	TLiwGenericParam element1;	
	element1.SetNameAndValueL(_L8("Type"),content);
	inParamList->AppendL(element1);
	content.Reset();
	element1.Reset();

   	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

    map->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal1File) ); 
    
    TLiwVariant filterparam(map);
	TLiwGenericParam element ;	
	element.SetNameAndValueL(_L8("Filter"),filterparam);
	filterparam.Reset();
	
	inParamList->AppendL(element);
	element.Reset();
    map->DecRef();
    CleanupStack::Pop(map);


	TInt err = 0;
	TRAP(err,interface->ExecuteCmdL( KCmdGetList ,*inParamList ,*outParamList));
    pos = 0 ;
    
    const TLiwGenericParam* output = outParamList->FindFirst( pos,_L8("ErrorCode"));
	
	if(output)     
		{
		TInt32 reterror = output->Value().AsTInt32();

		if ( reterror != 1012 )// Sapi error code ErrNotFound
			{
			result = KErrGeneral;	
	    	}
		}

	inParamList->Reset();
	outParamList->Reset();

	interface->Close();
	iServiceHandler->Reset();
	delete iServiceHandler;

    __UHEAP_MARKEND;	

	return result;

	}


//	
//Whats done here? 
//	Get the default system Calendar using GetList of CCalendarService and output that to GetListdefaultCalendar.txt
//       
TInt CTCalendarGetListTest::GetListInvalidGUID(CStifItemParser& /*aItem*/ )
	{
	TInt result=KErrNone;     
    
	__UHEAP_MARK;
// Iter-3 test work
	CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    
    CLiwGenericParamList* inParamList = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outParamList = &(iServiceHandler->OutParamListL());
    
    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);
    crit->SetServiceClass(TUid::Uid(KLiwClassBase));
    
    RCriteriaArray a;
    
    a.AppendL(crit);    
    
    iServiceHandler->AttachL(a);
    
	iServiceHandler->ExecuteServiceCmdL(*crit, *inParamList, *outParamList); 
	
	delete crit;
	crit = NULL;
	a.Reset();
	
	TInt pos = 0;
    MLiwInterface* interface = NULL;
    outParamList->FindFirst(pos,KIDataSource );
    if(pos != KErrNotFound)
        {
        interface = (*outParamList)[pos].Value().AsInterface();	
        }

	inParamList->Reset();
	outParamList->Reset();
	
	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	
	AddProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	
	RPointerArray<TUIDSet> arruids(5);
	
	TUIDSet* uids = NULL;
	
	if(AddProvAppointmentDailyRepeat(inParamList, outParamList, interface, KTestCal1File, uids) == KErrNone && uids)
		{
		arruids.Append(uids);
		uids = NULL;
		}

	if(AddProvEvent(inParamList, outParamList, interface, KTestCal1File, uids) == KErrNone && uids)
		{
		arruids.Append(uids);
		uids = NULL;
		}
	
	if ( arruids.Count() > 0 )
		{
			TLiwVariant content(_L("CalendarEntry"));
			TLiwGenericParam element1;	
			element1.SetNameAndValueL(_L8("Type"),content);
			inParamList->AppendL(element1);
			content.Reset();
			element1.Reset();
			
			
		   	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
			CleanupStack::PushL(map);

		    map->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal1File) ); 
		    map->InsertL(_L8("id"), TLiwVariant(_L("abc")) ); 
		    
		    TLiwVariant filterparam(map);
			TLiwGenericParam element ;	
			element.SetNameAndValueL(_L8("Filter"),filterparam);
			filterparam.Reset();
			
			inParamList->AppendL(element);
			element.Reset();
		    map->DecRef();
		    CleanupStack::Pop(map);

			TInt err = 0;
			TRAP(err,interface->ExecuteCmdL( KCmdGetList ,*inParamList ,*outParamList));
		    pos = 0 ;
		    
		    const TLiwGenericParam* output = outParamList->FindFirst( pos,_L8("ReturnValue"));
			
			if(output)     
				{
				CLiwIterable* iterlist = output->Value().AsIterable();

			    TLiwVariant data;
			    TInt itemfound = 0;
			    TBool uidmatched = EFalse;
		      
		        while( iterlist->NextL(data))
					{
					itemfound++;
			  		}
			  		
			  	data.Reset();	
			  	
			  	if(itemfound != 0)	
			  		result = KErrGeneral;
				}

			inParamList->Reset();
			outParamList->Reset();
	    
	    arruids.ResetAndDestroy();
		}
	else
		result = KErrGeneral;	
	
	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	
	
	interface->Close();
	iServiceHandler->Reset();
	delete iServiceHandler;

    __UHEAP_MARKEND;	

	return result;

	}	
	

//	
//Whats done here? 
//	Get the default system Calendar using GetList of CCalendarService and output that to GetListdefaultCalendar.txt
//       
TInt CTCalendarGetListTest::GetListInvalidLUID(CStifItemParser& /*aItem*/ )
	{
	TInt result=KErrNone;     
    
	__UHEAP_MARK;
// Iter-3 test work
	CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    
    CLiwGenericParamList* inParamList = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outParamList = &(iServiceHandler->OutParamListL());
    
    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);
    crit->SetServiceClass(TUid::Uid(KLiwClassBase));
    
    RCriteriaArray a;
    
    a.AppendL(crit);    
    
    iServiceHandler->AttachL(a);
    
	iServiceHandler->ExecuteServiceCmdL(*crit, *inParamList, *outParamList); 
	
	delete crit;
	crit = NULL;
	a.Reset();
	
	TInt pos = 0;
    MLiwInterface* interface = NULL;
    outParamList->FindFirst(pos,KIDataSource );
    if(pos != KErrNotFound)
        {
        interface = (*outParamList)[pos].Value().AsInterface();	
        }

	inParamList->Reset();
	outParamList->Reset();
	
	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	
	AddProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	
	RPointerArray<TUIDSet> arruids(5);
	
	TUIDSet* uids = NULL;
	
	if(AddProvAppointmentDailyRepeat(inParamList, outParamList, interface, KTestCal1File, uids) == KErrNone && uids)
		{
		arruids.Append(uids);
		uids = NULL;
		}

	if(AddProvEvent(inParamList, outParamList, interface, KTestCal1File, uids) == KErrNone && uids)
		{
		arruids.Append(uids);
		uids = NULL;
		}
	
	if ( arruids.Count() > 0 )
		{
			TLiwVariant content(_L("CalendarEntry"));
			TLiwGenericParam element1;	
			element1.SetNameAndValueL(_L8("Type"),content);
			inParamList->AppendL(element1);
			content.Reset();
			element1.Reset();
			
			
		   	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
			CleanupStack::PushL(map);

		    map->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal1File) ); 
		    map->InsertL(_L8("LocalId"), TLiwVariant(_L("0")) ); 
		    
		    TLiwVariant filterparam(map);
			TLiwGenericParam element ;	
			element.SetNameAndValueL(_L8("Filter"),filterparam);
			filterparam.Reset();
			
			inParamList->AppendL(element);
			element.Reset();
		    map->DecRef();
		    CleanupStack::Pop(map);

			TInt err = 0;
			TRAP(err,interface->ExecuteCmdL( KCmdGetList ,*inParamList ,*outParamList));
		    pos = 0 ;
		    
		    const TLiwGenericParam* output = outParamList->FindFirst( pos,_L8("ReturnValue"));
			
			if(output)     
				{
				CLiwIterable* iterlist = output->Value().AsIterable();

			    TLiwVariant data;
			    TInt itemfound = 0;
			    TBool uidmatched = EFalse;
		      
		        while( iterlist->NextL(data))
					{
					itemfound++;
			  		}
			  		
			  	data.Reset();	
			  	
			  	if(itemfound != 0)	
			  		result = KErrGeneral;
				}

			inParamList->Reset();
			outParamList->Reset();
	    
	    arruids.ResetAndDestroy();
		}
	else
		result = KErrGeneral;	
	
	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	
	
	interface->Close();
	iServiceHandler->Reset();
	delete iServiceHandler;

    __UHEAP_MARKEND;	

	return result;

	}		


TInt RemoveProvCalendar(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar)
	{
	inparam->Reset();
	outparam->Reset();
	__UHEAP_MARK;
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
	__UHEAP_MARKEND;

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
	

TInt AddProvAppointmentDailyRepeat(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset)
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
	map->InsertL(_L8("Type"), TLiwVariant( _L("Meeting") ));
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
			output = outparam->FindFirst( pos,_L8("ReturnValue"));
			if(output)
				{
				uidset = new (ELeave) TUIDSet;
				TPtrC uidval = (TPtrC)(output->Value().AsDes());
				//GetLocalUid( uidval, uidset->iLocalUID );
				
				uidset->iGlobalUID = HBufC8::NewL(uidval.Length());
				TPtr8 tmp = uidset->iGlobalUID->Des();
				GetGlobalUid( uidval, tmp );
				/*const CLiwMap* res = output->Value().AsMap();
				if ( res )
					{
					uidset = new (ELeave) TUIDSet;
					TLiwVariant luid;
					if(res->FindL(_L8("LocalUid"), luid))
						{
						uidset->iLocalUID = luid.AsTUint();
						}
					else
						err = -1;
					
					if(res->FindL(_L8("GlobalUid"), luid))
						{
						uidset->iGlobalUID = HBufC8::NewL(luid.AsDes().Length()) ;
						uidset->iGlobalUID->Des().Copy( luid.AsDes() );
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

void GetLocalUid( const TDesC& aLocalUid, TCalLocalUid& aOutLocalUid )
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
			aOutLocalUid = TCalLocalUid(num);
		}
	}

void GetGlobalUid( const TDesC& aGlobalUid, TDes8& aOutGlobalUid )
	{
	/*if( aGlobalUid.Length() )
		{
		TInt sepPos = aGlobalUid.Locate( KUidSeparator );

		if( sepPos == KErrNotFound )
			{
			aOutGlobalUid.Copy( aGlobalUid.Mid(0) );
			}
		else
			{
			aOutGlobalUid.Copy( aGlobalUid.Mid( sepPos + 1 ) );
			}	
		}*/
	aOutGlobalUid.Copy( aGlobalUid );
	}

TDesC& GetEntry(MLiwInterface* interface, CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, TPtrC globaluid, const TDesC& calname)
	{
	inparam->Reset();
	outparam->Reset();
    
    TLiwGenericParam dsNameParam(KContentType, TLiwVariant(_L("CalendarEntry")));
	inparam->AppendL(dsNameParam);
	
	CLiwDefaultMap *filterMap = CLiwDefaultMap::NewL();
	TLiwGenericParam filterParam(KFilter, TLiwVariant(filterMap));
	inparam->AppendL(filterParam);
	filterMap->DecRef();

    if(calname.Length())
    	filterMap->InsertL(KCalendarName,TLiwVariant(calname));
    filterMap->InsertL(_L8("id"),TLiwVariant(globaluid));

	TRAPD(err,interface->ExecuteCmdL( _L8("GetList") ,*inparam ,*outparam));
    TInt pos = 0 ;
    TBuf<10> result;
    const TLiwGenericParam* output = outparam->FindFirst( pos,_L8("ErrorCode"));
	
	if(output)
		{
		err = output->Value().AsTInt32();
		if( err == KErrNone )
			{
			pos = 0;
            output = outparam->FindFirst( pos,_L8("ReturnValue"));
            CLiwMap* map;
    		TInt retvalue = KErrNone;
    
			if ( output )     
				{
				CLiwIterable* iterlist = output->Value().AsIterable();
		      	if(iterlist)
		      		{
				    TLiwVariant data1;
		      		while(iterlist->NextL(data1) )
			      		{
						const CLiwMap* res = data1.AsMap();
						if ( res )
							{
							TLiwVariant data;
							if(res->FindL(_L8("LocalId"), data))
								result = data.AsDes();
							data.Reset();
							}
			      		}
		      		data1.Reset();  
		      		}
				}
			}
		}
	
	inparam->Reset();
	outparam->Reset();

	return result;
	}


TInt AddAppointmentProvLocal(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset)
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
	map->InsertL(_L8("Type"), TLiwVariant( _L("Meeting")  ));
	map->InsertL(_L8("StartTime"), TLiwVariant(TTime(TDateTime(2007,EOctober,23,10,0,0,0))));
	map->InsertL(_L8("EndTime"), TLiwVariant(TTime(TDateTime(2007,EOctober,23,10,30,0,0))));
	map->InsertL(_L8("SeqNum"), TLiwVariant(TInt32(1)));
	map->InsertL(_L8("Replication"), TLiwVariant(_L("Open")));
	map->InsertL(_L8("Location"), TLiwVariant(_L("Hara Room")));
	map->InsertL(_L8("Summary"), TLiwVariant(_L("Meeting happen at 10")));
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
			output = outparam->FindFirst( pos,_L8("ReturnValue"));
			if(output)
				{
				uidset = new (ELeave) TUIDSet;
				TPtrC uidval = (TPtrC)(output->Value().AsDes());
				//GetLocalUid( uidval, uidset->iLocalUID );
				
				uidset->iGlobalUID = HBufC8::NewL(uidval.Length());
				TPtr8 tmp = uidset->iGlobalUID->Des();
				GetGlobalUid( uidval, tmp );

				/*const CLiwMap* res = output->Value().AsMap();
				if ( res )
					{
					uidset = new (ELeave) TUIDSet;
					TLiwVariant luid;
					if(res->FindL(_L8("LocalUid"), luid))
						{
						uidset->iLocalUID = luid.AsTUint();
						}
					else
						err = -1;
					
					if(res->FindL(_L8("GlobalUid"), luid))
						{
						uidset->iGlobalUID = luid.AsData().AllocL();
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
    }



TInt AddProvEvent(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset)
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
	map->InsertL(_L8("Type"), TLiwVariant( _L("DayEvent")  ));
	map->InsertL(_L8("StartTime"), TLiwVariant(TTime(TDateTime(2007,EOctober,24,0,0,0,0))));
	map->InsertL(_L8("Replication"), TLiwVariant(_L("Open")));
	map->InsertL(_L8("Description"), TLiwVariant(_L("Event")));
	//map->InsertL(_L8("Method"), TLiwVariant(_L("None")));
	
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
			output = outparam->FindFirst( pos,_L8("ReturnValue"));
			if(output)
				{
				uidset = new (ELeave) TUIDSet;
				TPtrC uidval = (TPtrC)(output->Value().AsDes());
				//GetLocalUid( uidval, uidset->iLocalUID );
				
				uidset->iGlobalUID = HBufC8::NewL(uidval.Length());
				TPtr8 tmp = uidset->iGlobalUID->Des();
				GetGlobalUid( uidval, tmp );
				/*const CLiwMap* res = output->Value().AsMap();
				if ( res )
					{
					uidset = new (ELeave) TUIDSet;
					TLiwVariant luid;
					if(res->FindL(_L8("LocalUid"), luid))
						{
						uidset->iLocalUID = luid.AsTUint();
						}
					else
						err = -1;
					
					if(res->FindL(_L8("GlobalUid"), luid))
						{
						uidset->iGlobalUID = luid.AsData().AllocL();
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
				
				