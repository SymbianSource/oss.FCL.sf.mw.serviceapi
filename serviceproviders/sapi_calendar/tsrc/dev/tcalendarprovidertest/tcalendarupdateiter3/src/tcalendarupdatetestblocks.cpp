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
#include<LiwCommon.h>
#include<LiwVariant.h>
#include<LiwServiceHandler.h>

#include "tcalendarupdatetest.h"
#include "calendarheader.h"
#include "calendarconstants.h"

_LIT8(KTestInterface, 	"IDataSource");
_LIT8(KTestContent,		"Service.Calendar");
_LIT(KKCalFileName11,"C:CalendarFileA");

/*TInt RemoveCalendarFile(void* aInterfaceptr, const wchar_t* aCalname);
TInt AddCalendarFile(void* aInterfaceptr, const wchar_t* aCalname);
TInt AddAnniversary(void* aInterfaceptr, const wchar_t* aCalname, TUIDSet*& uids);
TInt AddDayEvent(void* aInterfaceptr, const wchar_t* aCalname, TUIDSet*& uids);
TInt AddReminder(void* aInterfaceptr, const wchar_t* aCalname, TUIDSet*& uids);
TInt AddTodoEntry(void* aInterfaceptr, const wchar_t* aCalname, TUIDSet*& uids);
TInt AddAppointmentWithoutRepeat(void* aInterfaceptr, const wchar_t* aCalname, TUIDSet*& uids);
TInt AddAppointmentWithDailyRepeat(void* aInterfaceptr, const wchar_t* aCalname, TUIDSet*& uids);
void GetLocalUid( const TDesC& aLocalUid, TCalLocalUid& aOutLocalUid );
void GetGlobalUid( const TDesC& aGlobalUid, TDes8& aOutGlobalUid );


wchar_t  KCalFileName1[20] = L"C:CalendarFile1";*/
TInt doAddTest();
void GetLocalUid( const TDesC& aLocalUid, TCalLocalUid& aOutLocalUid );
TInt AddProvAppointmentDailyRepeatAndAttendees(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset);
TInt AddProvCalendar(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar);
TInt RemoveProvCalendar(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar);
TInt AddProvToDo(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset);
TInt AddProvDayEvent(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset);
TInt AddProvAppointmentDailyRepeat(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset);
TInt AddProvAppointmentWeeklyRepeat(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset);
TInt AddProvAppointmentMonthlyRepeat(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset);
TInt AddProvAppointmentWithoutRepeat(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset);
TInt AddProvAnni(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset);
TInt AddProvReminder(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset);
TInt AddNewCalendar();
class CTestUpdateSync : public CBase
{
public:
	static CTestUpdateSync* NewL();
	int UpdateAppointmentEntryL();
	int UpdateAppointmentEntryWithNewTimeL();
	int UpdateAppointmentEntryWithNewAttendeesL();
	int UpdateAppointmentEntryWithNewRepeatL();
	int UpdateAnniversaryL();
	int UpdateDayEventL();
	int UpdateReminderL();
	int UpdateTodoEntryL();
	int UpdateAppointmentEntryWithGlobalIdL();
    int UpdateAnniversaryWithGlobalIdL();
    int UpdateDayEventWithGlobalIdL();
    int UpdateReminderWithGlobalIdL();
    int UpdateTodoEntryWithGlobalIdL();
    int UpdateAppointmentEntryWithNewTimeAndGlobalIdL();
	
	TDesC& GetEntry(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, TPtrC globaluid, const TDesC& calname);
	CTestUpdateSync();
	~CTestUpdateSync();

private:
	void ConstructL();

	
	
private:	
	CLiwServiceHandler* 	iServiceHandler;
	TInt 					iResult;
	MLiwInterface* 			interface ;	
};		


CTestUpdateSync* CTestUpdateSync::NewL()
	{
	CTestUpdateSync* self = new (ELeave) CTestUpdateSync();
	self->ConstructL();
	return self;
	}

CTestUpdateSync::~CTestUpdateSync()
	{
	if( interface )
	interface->Close();
	
	delete iServiceHandler;
	}


void CTestUpdateSync::ConstructL()
	{
	}


CTestUpdateSync::CTestUpdateSync()
	{
	interface = NULL ;
	}
// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTCalendarUpdateTest::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTCalendarUpdateTest::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CTChangeStatusTest::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTCalendarUpdateTest::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        //TRY( "SendMessage",    CTDeleteMessageTest::SendMessage ),
        ENTRY( "UpdateAppointmentEntry",    	CTCalendarUpdateTest::UpdateAppointmentEntryL),
        ENTRY( "UpdateAppointmentEntryWithNewTime",    	 CTCalendarUpdateTest::UpdateAppointmentEntryWithNewTimeL ),
        ENTRY( "UpdateAppointmentEntryWithNewAttendees",    CTCalendarUpdateTest::UpdateAppointmentEntryWithNewAttendeesL),
        ENTRY( "UpdateAppointmentEntryWithNewRepeat",    CTCalendarUpdateTest::UpdateAppointmentEntryWithNewRepeatL),
        ENTRY( "UpdateAnniversary",    CTCalendarUpdateTest::UpdateAnniversaryL),
        ENTRY( "UpdateDayEvent",    CTCalendarUpdateTest::UpdateDayEventL),
        ENTRY( "UpdateReminder",    CTCalendarUpdateTest::UpdateReminderL),
        ENTRY( "UpdateTodoEntry",    CTCalendarUpdateTest::UpdateTodoEntryL),

        ENTRY( "UpdateAppointmentEntryWithGlobalId",        CTCalendarUpdateTest::UpdateAppointmentEntryWithGlobalIdL),
        ENTRY( "UpdateAnniversaryWithGlobalId",    CTCalendarUpdateTest::UpdateAnniversaryWithGlobalIdL),
        ENTRY( "UpdateDayEventWithGlobalId",    CTCalendarUpdateTest::UpdateDayEventWithGlobalIdL),
        ENTRY( "UpdateReminderWithGlobalId",    CTCalendarUpdateTest::UpdateReminderWithGlobalIdL),
        ENTRY( "UpdateTodoEntryWithGlobalId",    CTCalendarUpdateTest::UpdateTodoEntryWithGlobalIdL),
        ENTRY( "UpdateAppointmentEntryWithNewTimeAndGlobalId",      CTCalendarUpdateTest::UpdateAppointmentEntryWithNewTimeAndGlobalIdL ),

	    };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }


// -----------------------------------------------------------------------------
// CTCalendarUpdateTest::UpdateAppointmentEntryL
// Test Method to test the UpdateAsync(ASynchronous)
// Functionality of CalenderService
// -----------------------------------------------------------------------------
//
TInt  CTCalendarUpdateTest::UpdateAppointmentEntryL(CStifItemParser& /*aItem*/)
	{
	//__UHEAP_MARK;
	
	TInt result=KErrNone;
	
	__UHEAP_MARK;
	CTestUpdateSync* test = CTestUpdateSync::NewL();
    int res =  test->UpdateAppointmentEntryL();
	delete test;
	__UHEAP_MARKEND;
	return res;
	
	
//	__UHEAP_MARKEND;
	return result;
    }
    
TInt  CTCalendarUpdateTest::UpdateAppointmentEntryWithNewTimeL(CStifItemParser& /*aItem*/)
	{
	//__UHEAP_MARK;
	
	TInt result=KErrNone;
	
	__UHEAP_MARK;
	CTestUpdateSync* test = CTestUpdateSync::NewL();
    int res =  test->UpdateAppointmentEntryWithNewTimeL();
	delete test;
	__UHEAP_MARKEND;
	return res;
	
	
//	__UHEAP_MARKEND;
	return result;
    }
    
TInt  CTCalendarUpdateTest::UpdateAppointmentEntryWithNewAttendeesL(CStifItemParser& /*aItem*/)
	{
	//__UHEAP_MARK;
	
	TInt result=KErrNone;
	
	__UHEAP_MARK;
	CTestUpdateSync* test = CTestUpdateSync::NewL();
    int res =  test->UpdateAppointmentEntryWithNewAttendeesL();
	delete test;
	__UHEAP_MARKEND;
	return res;
	
	
//	__UHEAP_MARKEND;
	return result;
    }
    

TInt  CTCalendarUpdateTest::UpdateAnniversaryL(CStifItemParser& /*aItem*/)
	{
	//__UHEAP_MARK;
	
	TInt result=KErrNone;
	
	__UHEAP_MARK;
	CTestUpdateSync* test = CTestUpdateSync::NewL();
    int res =  test->UpdateAnniversaryL();
	delete test;
	__UHEAP_MARKEND;
	return res;
	
	
//	__UHEAP_MARKEND;
	return result;
    }
    
TInt  CTCalendarUpdateTest::UpdateDayEventL(CStifItemParser& /*aItem*/)
	{
	//__UHEAP_MARK;
	
	TInt result=KErrNone;
	
	__UHEAP_MARK;
	CTestUpdateSync* test = CTestUpdateSync::NewL();
    int res =  test->UpdateDayEventL();
	delete test;
	__UHEAP_MARKEND;
	return res;
	
	
//	__UHEAP_MARKEND;
	return result;
    }
    
TInt  CTCalendarUpdateTest::UpdateReminderL(CStifItemParser& /*aItem*/)
	{
	//__UHEAP_MARK;
	
	TInt result=KErrNone;
	
	__UHEAP_MARK;
	CTestUpdateSync* test = CTestUpdateSync::NewL();
    int res =  test->UpdateReminderL();
	delete test;
	__UHEAP_MARKEND;
	return res;
	
	
//	__UHEAP_MARKEND;
	return result;
    }   
TInt  CTCalendarUpdateTest::UpdateTodoEntryL(CStifItemParser& /*aItem*/)
	{
	//__UHEAP_MARK;
	
	TInt result=KErrNone;
	
	__UHEAP_MARK;
	CTestUpdateSync* test = CTestUpdateSync::NewL();
    int res =  test->UpdateReminderL();
	delete test;
	__UHEAP_MARKEND;
	return res;
	
	
//	__UHEAP_MARKEND;
	return result;
    }   

TInt  CTCalendarUpdateTest::UpdateAppointmentEntryWithNewRepeatL(CStifItemParser& /*aItem*/)
	{
	//__UHEAP_MARK;
	
	TInt result=KErrNone;
	
	__UHEAP_MARK;
	CTestUpdateSync* test = CTestUpdateSync::NewL();
    int res =  test->UpdateAppointmentEntryWithNewRepeatL();
	delete test;
	__UHEAP_MARKEND;
	return res;
	
	
//	__UHEAP_MARKEND;
	return result;
    }   
TInt  CTCalendarUpdateTest::UpdateAppointmentEntryWithGlobalIdL(CStifItemParser& /*aItem*/)
    {
    //__UHEAP_MARK;
    
    TInt result=KErrNone;
    
    __UHEAP_MARK;
    CTestUpdateSync* test = CTestUpdateSync::NewL();
    int res =  test->UpdateAppointmentEntryWithGlobalIdL();
    delete test;
    __UHEAP_MARKEND;
    return res;
    
    
//  __UHEAP_MARKEND;
    return result;
    }

TInt  CTCalendarUpdateTest::UpdateAnniversaryWithGlobalIdL(CStifItemParser& /*aItem*/)
    {
    //__UHEAP_MARK;
    
    TInt result=KErrNone;
    
    __UHEAP_MARK;
    CTestUpdateSync* test = CTestUpdateSync::NewL();
    int res =  test->UpdateAnniversaryWithGlobalIdL();
    delete test;
    __UHEAP_MARKEND;
    return res;
    
    
//  __UHEAP_MARKEND;
    return result;
    }
    
TInt  CTCalendarUpdateTest::UpdateDayEventWithGlobalIdL(CStifItemParser& /*aItem*/)
    {
    //__UHEAP_MARK;
    
    TInt result=KErrNone;
    
    __UHEAP_MARK;
    CTestUpdateSync* test = CTestUpdateSync::NewL();
    int res =  test->UpdateDayEventWithGlobalIdL();
    delete test;
    __UHEAP_MARKEND;
    return res;
    
    
//  __UHEAP_MARKEND;
    return result;
    }
    
TInt  CTCalendarUpdateTest::UpdateReminderWithGlobalIdL(CStifItemParser& /*aItem*/)
    {
    //__UHEAP_MARK;
    
    TInt result=KErrNone;
    
    __UHEAP_MARK;
    CTestUpdateSync* test = CTestUpdateSync::NewL();
    int res =  test->UpdateReminderWithGlobalIdL();
    delete test;
    __UHEAP_MARKEND;
    return res;
    
    
//  __UHEAP_MARKEND;
    return result;
    }   
TInt  CTCalendarUpdateTest::UpdateTodoEntryWithGlobalIdL(CStifItemParser& /*aItem*/)
    {
    //__UHEAP_MARK;
    
    TInt result=KErrNone;
    
    __UHEAP_MARK;
    CTestUpdateSync* test = CTestUpdateSync::NewL();
    int res =  test->UpdateReminderWithGlobalIdL();
    delete test;
    __UHEAP_MARKEND;
    return res;
    
    
//  __UHEAP_MARKEND;
    return result;
    }   
TInt  CTCalendarUpdateTest::UpdateAppointmentEntryWithNewTimeAndGlobalIdL(CStifItemParser& /*aItem*/)
    {
    //__UHEAP_MARK;
    
    TInt result=KErrNone;
    
    __UHEAP_MARK;
    CTestUpdateSync* test = CTestUpdateSync::NewL();
    int res =  test->UpdateAppointmentEntryWithNewTimeAndGlobalIdL();
    delete test;
    __UHEAP_MARKEND;
    return res;
    
    
//  __UHEAP_MARKEND;
    return result;
    }

TInt CTestUpdateSync::UpdateAppointmentEntryL()
	{
	iServiceHandler = CLiwServiceHandler::NewL();

	CLiwGenericParamList* inparam = &(iServiceHandler->InParamListL());
	CLiwGenericParamList* outparam = &(iServiceHandler->OutParamListL());


	TInt err; 
	RCriteriaArray interest;
    CleanupClosePushL(interest);
    
	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KTestInterface,KTestContent);
	crit->SetServiceClass(TUid::Uid(KLiwClassBase));
    CleanupStack::PushL(crit);
    interest.AppendL(crit);    
	
	iServiceHandler->AttachL(interest);
    iServiceHandler->ExecuteServiceCmdL(*crit, *inparam, *outparam); 

	TInt pos = 0;

	outparam->FindFirst( pos, KTestInterface );
	if(pos != KErrNotFound)
		{
		interface = (*outparam)[pos].Value().AsInterface();	
		}
    CleanupStack::PopAndDestroy(crit);
    CleanupStack::PopAndDestroy(&interest); 

	outparam->Reset();
	inparam->Reset();
	
	AddProvCalendar(inparam, outparam, interface, KKCalFileName11);
	TUIDSet* uidset1;
    TBuf<50> globaluid;
    TBuf<10> localuid;
    //AddProvAppointmentDailyRepeatAndAttendees(inparam, outparam, interface, KKCalFileName11 ,uidset1 );
    AddProvAppointmentWithoutRepeat(inparam, outparam, interface, KKCalFileName11 ,uidset1);
    //localuid.Num(TInt64(uidset1->iLocalUID));
    globaluid.Copy(uidset1->iGlobalUID->Des());
    localuid = GetEntry( inparam, outparam, globaluid, KKCalFileName11);
    
   	CLiwDefaultMap* map1 = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map1);

    TLiwVariant content(_L("CalendarEntry"));
	TLiwGenericParam element1;	
	element1.SetNameAndValueL(_L8("Type"),content);
	inparam->AppendL(element1);
	content.Reset();
	element1.Reset();


    map1->InsertL(_L8("CalendarName"), TLiwVariant(KKCalFileName11) ); 
    map1->InsertL(_L8("LocalId"),TLiwVariant(localuid));
	map1->InsertL(_L8("StartTime"), TLiwVariant(TTime(TDateTime(2007,EOctober,3,10,0,0,0))));
	map1->InsertL(_L8("EndTime"), TLiwVariant(TTime(TDateTime(2007,EOctober,3,10,30,0,0))));
	map1->InsertL(_L8("AlarmTime"), TLiwVariant(TTime(TDateTime(2007,EOctober,3,9,30,0,0))));
	TLiwGenericParam element;	
	element.SetNameAndValueL(_L8("Item"),TLiwVariant(map1));
	
	inparam->AppendL(element);
	element.Reset();
    map1->DecRef();
    CleanupStack::Pop(map1);

	TRAPD(err1, interface->ExecuteCmdL( KCmdAdd, *inparam,*outparam ));

	inparam->Reset();
	outparam->Reset();
    
    TLiwGenericParam dsNameParam(KContentType, TLiwVariant(_L("CalendarEntry")));
	inparam->AppendL(dsNameParam);
	
	CLiwDefaultMap *filterMap = CLiwDefaultMap::NewL();
	TLiwGenericParam filterParam(KFilter, TLiwVariant(filterMap));
	inparam->AppendL(filterParam);
	filterMap->DecRef();

    filterMap->InsertL(KCalendarName,TLiwVariant(_L("C:CalendarFileA")));
    filterMap->InsertL(_L8("LocalId"),TLiwVariant(localuid));

	TRAP(err,interface->ExecuteCmdL( _L8("GetList") ,*inparam ,*outparam));
    
    pos = 0 ;
    
    const TLiwGenericParam* finaloutput = outparam->FindFirst( pos,_L8("ReturnValue"));
    TInt count = 0;
    CLiwMap* map;
    TInt retvalue = KErrNone;
	if ( finaloutput )     
		{
		CLiwIterable* iterlist = finaloutput->Value().AsIterable();
      	if(iterlist)
      		{
		    TLiwVariant data1;
      		while(iterlist->NextL(data1) )
	      		{
				const CLiwMap* res = data1.AsMap();
				if ( res )
					{
					TLiwVariant data;
					if(res->FindL(_L8("StartTime"), data))
						{
						TTime ostime(TDateTime(2007,EOctober,3,10,0,0,0));
						TTime stime = data.AsTTime();
						if( ostime != stime)
							{
						    retvalue = KErrGeneral;
							break;
							}
						}

					if(res->FindL(_L8("EndTime"), data))
						{
						TTime ostime(TDateTime(2007,EOctober,3,10,30,0,0));
						TTime stime = data.AsTTime();
						if( ostime != stime)
							{
						    retvalue = KErrGeneral;
							break;
							}
						}

					data.Reset();	
					}
	      		}
      		data1.Reset();  
      		}
		}
	
	inparam->Reset();
	outparam->Reset();
	delete uidset1;
    RemoveProvCalendar(inparam, outparam, interface, KKCalFileName11);
    return retvalue;
	}
	
TInt CTestUpdateSync::UpdateAppointmentEntryWithNewTimeL()
	{
	iServiceHandler = CLiwServiceHandler::NewL();

	CLiwGenericParamList* inparam = &(iServiceHandler->InParamListL());
	CLiwGenericParamList* outparam = &(iServiceHandler->OutParamListL());


	TInt err; 
	RCriteriaArray interest;
    CleanupClosePushL(interest);
    
	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KTestInterface,KTestContent);
	crit->SetServiceClass(TUid::Uid(KLiwClassBase));
    CleanupStack::PushL(crit);
    interest.AppendL(crit);    
	
	iServiceHandler->AttachL(interest);
    iServiceHandler->ExecuteServiceCmdL(*crit, *inparam, *outparam); 

	TInt pos = 0;

	outparam->FindFirst( pos, KTestInterface );
	if(pos != KErrNotFound)
		{
		interface = (*outparam)[pos].Value().AsInterface();	
		}
    CleanupStack::PopAndDestroy(crit);
    CleanupStack::PopAndDestroy(&interest); 

	outparam->Reset();
	inparam->Reset();
	
	AddProvCalendar(inparam, outparam, interface, KKCalFileName11);
	TUIDSet* uidset1;
    TBuf<50> globaluid;
    TBuf<10> localuid;
    //AddProvAppointmentDailyRepeatAndAttendees(inparam, outparam, interface, KKCalFileName11 ,uidset1 );
    AddProvAppointmentDailyRepeat(inparam, outparam, interface, KKCalFileName11 ,uidset1);
    //localuid.Num(TInt64(uidset1->iLocalUID));
    globaluid.Copy(uidset1->iGlobalUID->Des());
	localuid = GetEntry( inparam, outparam, globaluid, KKCalFileName11);    
   	CLiwDefaultMap* map1 = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map1);

    TLiwVariant content(_L("CalendarEntry"));
	TLiwGenericParam element1;	
	element1.SetNameAndValueL(_L8("Type"),content);
	inparam->AppendL(element1);
	content.Reset();
	element1.Reset();


    map1->InsertL(_L8("CalendarName"), TLiwVariant(KKCalFileName11) ); 
    map1->InsertL(_L8("LocalId"),TLiwVariant(localuid));
	map1->InsertL(_L8("StartTime"), TLiwVariant(TTime(TDateTime(2007,EOctober,25,14,30,0,0))));
	map1->InsertL(_L8("EndTime"), TLiwVariant(TTime(TDateTime(2007,EOctober,25,15,30,0,0))));
	map1->InsertL(_L8("InstanceStartTime"), TLiwVariant(TTime(TDateTime(2007,EOctober,25,10,0,0,0))));
	
	TLiwGenericParam element;	
	element.SetNameAndValueL(_L8("Item"),TLiwVariant(map1));
	
	inparam->AppendL(element);
	element.Reset();
    map1->DecRef();
    CleanupStack::Pop(map1);

	TRAPD(err1, interface->ExecuteCmdL( KCmdAdd, *inparam,*outparam ));
    TInt pos1 = 0 ;
    
    const TLiwGenericParam* output = outparam->FindFirst( pos1,_L8("ErrorCode"));
	TBuf<10> local;
	if(output)
		{
		err = output->Value().AsTInt32();
		if ( err == KErrNone )
			{
			output = outparam->FindFirst( pos1,_L8("ReturnValue"));
			if(output)
				{
				TPtrC uidval = (TPtrC)(output->Value().AsDes());
				TBuf<50> uidg;
				uidg.Copy(uidval);
				local = GetEntry( inparam, outparam, uidg, KKCalFileName11);    
				}
			else
				err = -1;
			}
		}
    //TBuf<10> localuid1;
    //localuid1.Num(TInt64(local));
    
	inparam->Reset();
	outparam->Reset();
    
    TLiwGenericParam dsNameParam(KContentType, TLiwVariant(_L("CalendarEntry")));
	inparam->AppendL(dsNameParam);
	
	CLiwDefaultMap *filterMap = CLiwDefaultMap::NewL();
	TLiwGenericParam filterParam(KFilter, TLiwVariant(filterMap));
	inparam->AppendL(filterParam);
	filterMap->DecRef();

    filterMap->InsertL(KCalendarName,TLiwVariant(_L("C:CalendarFileA")));
    filterMap->InsertL(_L8("LocalId"),TLiwVariant(local));

	TRAP(err,interface->ExecuteCmdL( _L8("GetList") ,*inparam ,*outparam));
    
    pos = 0 ;
    
    const TLiwGenericParam* finaloutput = outparam->FindFirst( pos,_L8("ReturnValue"));
    TInt count = 0;
    CLiwMap* map;
    TInt retvalue = KErrNone;
	if ( finaloutput )     
		{
		CLiwIterable* iterlist = finaloutput->Value().AsIterable();
      	if(iterlist)
      		{
		    TLiwVariant data1;
      		while(iterlist->NextL(data1) )
	      		{
				const CLiwMap* res = data1.AsMap();
				if ( res )
					{
					TLiwVariant data;
					if(res->FindL(_L8("StartTime"), data))
						{
						TTime ostime(TDateTime(2007,EOctober,25,14,30,0,0));
						TTime stime = data.AsTTime();
						if( ostime != stime)
							{
						    retvalue = KErrGeneral;
							break;
							}
						}

					if(res->FindL(_L8("EndTime"), data))
						{
						TTime ostime(TDateTime(2007,EOctober,25,15,30,0,0));
						TTime stime = data.AsTTime();
						if( ostime != stime)
							{
						    retvalue = KErrGeneral;
							break;
							}
						}

					data.Reset();	
					}
	      		}
      		data1.Reset();  
      		}
		}
	
	inparam->Reset();
	outparam->Reset();
	delete uidset1;
    RemoveProvCalendar(inparam, outparam, interface, KKCalFileName11);
    return retvalue;
	}
	
TInt CTestUpdateSync::UpdateAppointmentEntryWithNewAttendeesL()
	{
	iServiceHandler = CLiwServiceHandler::NewL();

	CLiwGenericParamList* inparam = &(iServiceHandler->InParamListL());
	CLiwGenericParamList* outparam = &(iServiceHandler->OutParamListL());


	TInt err; 
	RCriteriaArray interest;
    CleanupClosePushL(interest);
    
	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KTestInterface,KTestContent);
	crit->SetServiceClass(TUid::Uid(KLiwClassBase));
    CleanupStack::PushL(crit);
    interest.AppendL(crit);    
	
	iServiceHandler->AttachL(interest);
    iServiceHandler->ExecuteServiceCmdL(*crit, *inparam, *outparam); 

	TInt pos = 0;

	outparam->FindFirst( pos, KTestInterface );
	if(pos != KErrNotFound)
		{
		interface = (*outparam)[pos].Value().AsInterface();	
		}
    CleanupStack::PopAndDestroy(crit);
    CleanupStack::PopAndDestroy(&interest); 

	outparam->Reset();
	inparam->Reset();
	
	AddProvCalendar(inparam, outparam, interface, KKCalFileName11);
	TUIDSet* uidset1;
    TBuf<50> globaluid;
    TBuf<10> localuid;
    //AddProvAppointmentDailyRepeatAndAttendees(inparam, outparam, interface, KKCalFileName11 ,uidset1 );
    AddProvAppointmentDailyRepeat(inparam, outparam, interface, KKCalFileName11 ,uidset1);
    //localuid.Num(TInt64(uidset1->iLocalUID));
    globaluid.Copy(uidset1->iGlobalUID->Des());
    localuid = GetEntry( inparam, outparam, globaluid, KKCalFileName11);
   	CLiwDefaultMap* map1 = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map1);

    TLiwVariant content(_L("CalendarEntry"));
	TLiwGenericParam element1;	
	element1.SetNameAndValueL(_L8("Type"),content);
	inparam->AppendL(element1);
	content.Reset();
	element1.Reset();


    map1->InsertL(_L8("CalendarName"), TLiwVariant(KKCalFileName11) ); 
    map1->InsertL(_L8("LocalId"),TLiwVariant(localuid));
	map1->InsertL(_L8("StartTime"), TLiwVariant(TTime(TDateTime(2007,EOctober,23,14,30,0,0))));
	map1->InsertL(_L8("EndTime"), TLiwVariant(TTime(TDateTime(2007,EOctober,23,15,30,0,0))));
	map1->InsertL(_L8("InstanceStartTime"), TLiwVariant(TTime(TDateTime(2007,EOctober,25,10,0,0,0))));
	
   	CLiwDefaultList* attlist = CLiwDefaultList::NewL();
	CleanupStack::PushL(attlist);

   	CLiwDefaultMap* attmap = CLiwDefaultMap::NewL();
	CleanupStack::PushL(attmap);
	attmap->InsertL(_L8("CommonName"), TLiwVariant(_L("sapi")));
	attmap->InsertL(_L8("Address"), TLiwVariant(_L("h2s@nokia.com")));
	attlist->AppendL( TLiwVariant(attmap));
	CleanupStack::Pop(attmap);
	attmap->DecRef();
	map1->InsertL(_L8("Attendees"), TLiwVariant(attlist));
	map1->InsertL(_L8("PhoneOwner"), TLiwVariant(_L("h2s@nokia.com")));
   	CLiwDefaultMap* orgmap = CLiwDefaultMap::NewL();
	CleanupStack::PushL(orgmap);
	orgmap->InsertL(_L8("CommonName"), TLiwVariant(_L("sapi")));
	orgmap->InsertL(_L8("Address"), TLiwVariant(_L("mdc@nokia.com")));
	map1->InsertL(_L8("Organizer"), TLiwVariant(orgmap));
	CleanupStack::Pop(orgmap);
	orgmap->DecRef();

	CleanupStack::Pop(attlist);
	attlist->DecRef();
	
	TLiwGenericParam element;	
	element.SetNameAndValueL(_L8("Item"),TLiwVariant(map1));
	
	inparam->AppendL(element);
	element.Reset();
    map1->DecRef();
    CleanupStack::Pop(map1);

	TRAPD(err1, interface->ExecuteCmdL( KCmdAdd, *inparam,*outparam ));
    TInt pos1 = 0 ;
    
    const TLiwGenericParam* output = outparam->FindFirst( pos1,_L8("ErrorCode"));
	TBuf<10> local;
	if(output)
		{
		err = output->Value().AsTInt32();
		if ( err == KErrNone )
			{
			output = outparam->FindFirst( pos1,_L8("ReturnValue"));
			if(output)
				{
				TPtrC uidval = (TPtrC)(output->Value().AsDes());
				local = GetEntry( inparam, outparam, uidval, KKCalFileName11);    
				}
			else
				err = -1;
			}
		}
    //TBuf<10> localuid1;
    //localuid1.Num(TInt64(local));
    
	inparam->Reset();
	outparam->Reset();
    
    TLiwGenericParam dsNameParam(KContentType, TLiwVariant(_L("CalendarEntry")));
	inparam->AppendL(dsNameParam);
	
	CLiwDefaultMap *filterMap = CLiwDefaultMap::NewL();
	TLiwGenericParam filterParam(KFilter, TLiwVariant(filterMap));
	inparam->AppendL(filterParam);
	filterMap->DecRef();

    filterMap->InsertL(KCalendarName,TLiwVariant(_L("C:CalendarFileA")));
    filterMap->InsertL(_L8("LocalId"),TLiwVariant(local));

	TRAP(err,interface->ExecuteCmdL( _L8("GetList") ,*inparam ,*outparam));
    
    pos = 0 ;
    
    const TLiwGenericParam* finaloutput = outparam->FindFirst( pos,_L8("ReturnValue"));
    TInt count = 0;
    CLiwMap* map;
    TInt retvalue = KErrNone;
	if ( finaloutput )     
		{
		CLiwIterable* iterlist = finaloutput->Value().AsIterable();
      	if(iterlist)
      		{
		    TLiwVariant data1;
      		while(iterlist->NextL(data1) )
	      		{
				const CLiwMap* res = data1.AsMap();
				if ( res )
					{
					TLiwVariant data;
					if(res->FindL(_L8("Organizer"), data))
						{
						const CLiwMap* map = data.AsMap();
						TLiwVariant rdata;
						if(map->FindL(_L8("CommonName"), rdata))
							{
							TPtrC cn = rdata.AsDes();
							if( cn.CompareF(_L("sapi")) != 0 )
								{
							    retvalue = KErrGeneral;
							    rdata.Reset();
								break;
								}
							}
						if(map->FindL(_L8("Address"), rdata))
							{
							TPtrC add = rdata.AsDes();
							if( add.CompareF(_L("mdc@nokia.com")) != 0 )
								{
							    retvalue = KErrGeneral;
							    rdata.Reset();
								break;
								}
							}
						rdata.Reset();	
						}

					if(res->FindL(_L8("PhoneOwner"), data))
						{
						TPtrC rep = data.AsDes();
						if(rep.CompareF(_L("h2s@nokia.com")) != 0 )
							{
						    retvalue = KErrGeneral;
							break;
							}
						}

					if(res->FindL(_L8("Attendees"), data))
						{
						const CLiwList* list = data.AsList();
						if ( list )
							{
							TInt count = list->Count();
							for ( int index = 0; index < count; index++ )
								{
								TLiwVariant element;
								list->AtL(index, element);
								const CLiwMap* map = element.AsMap();
								TLiwVariant attParam;
								if ( map && map->FindL(_L8("Address"), attParam) )
									{
									TPtrC address = attParam.AsDes();
									if( address.CompareF(_L("h2s@nokia.com")) != 0 )
										{
									    retvalue = KErrGeneral;
									    attParam.Reset();
									    element.Reset();
										break;
										}
									}
								if ( map->FindL( _L8("CommonName"), attParam ) ) 
									{
									TPtrC cn = attParam.AsDes();
									if( cn.CompareF(_L("sapi")) != 0 )
										{
									    retvalue = KErrGeneral;
									    attParam.Reset();
									    element.Reset();
										break;
										}
									}
								attParam.Reset();
		                        element.Reset();
								}
							}
						}

					data.Reset();	
					}
	      		}
      		data1.Reset();  
      		}
		}
	
	inparam->Reset();
	outparam->Reset();
	delete uidset1;
    RemoveProvCalendar(inparam, outparam, interface, KKCalFileName11);
    return retvalue;
	}
TInt CTestUpdateSync::UpdateAppointmentEntryWithNewRepeatL()
	{
	iServiceHandler = CLiwServiceHandler::NewL();

	CLiwGenericParamList* inparam = &(iServiceHandler->InParamListL());
	CLiwGenericParamList* outparam = &(iServiceHandler->OutParamListL());


	TInt err; 
	RCriteriaArray interest;
    CleanupClosePushL(interest);
    
	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KTestInterface,KTestContent);
	crit->SetServiceClass(TUid::Uid(KLiwClassBase));
    CleanupStack::PushL(crit);
    interest.AppendL(crit);    
	
	iServiceHandler->AttachL(interest);
    iServiceHandler->ExecuteServiceCmdL(*crit, *inparam, *outparam); 

	TInt pos = 0;

	outparam->FindFirst( pos, KTestInterface );
	if(pos != KErrNotFound)
		{
		interface = (*outparam)[pos].Value().AsInterface();	
		}
    CleanupStack::PopAndDestroy(crit);
    CleanupStack::PopAndDestroy(&interest); 

	outparam->Reset();
	inparam->Reset();
	
	AddProvCalendar(inparam, outparam, interface, KKCalFileName11);
	TUIDSet* uidset1;
    TBuf<50> globaluid;
    TBuf<10> localuid;
    //AddProvAppointmentDailyRepeatAndAttendees(inparam, outparam, interface, KKCalFileName11 ,uidset1 );
    AddProvAppointmentDailyRepeat(inparam, outparam, interface, KKCalFileName11 ,uidset1);
    //localuid.Num(TInt64(uidset1->iLocalUID));
    globaluid.Copy(uidset1->iGlobalUID->Des());
    localuid = GetEntry( inparam, outparam, globaluid, KKCalFileName11);
   	CLiwDefaultMap* map1 = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map1);

    TLiwVariant content(_L("CalendarEntry"));
	TLiwGenericParam element1;	
	element1.SetNameAndValueL(_L8("Type"),content);
	inparam->AppendL(element1);
	content.Reset();
	element1.Reset();


    map1->InsertL(_L8("CalendarName"), TLiwVariant(KKCalFileName11) ); 
    map1->InsertL(_L8("LocalId"),TLiwVariant(localuid));
	
   	CLiwDefaultMap* repeatmap = CLiwDefaultMap::NewL();
	CleanupStack::PushL(repeatmap);
	repeatmap->InsertL(_L8("Type"), TLiwVariant(TInt32(3)));
	//repeatmap->InsertL(_L8("StartDate"), TLiwVariant(TTime(TDateTime(2007,EAugust,23,10,0,0,0))));
	repeatmap->InsertL(_L8("UntilDate"), TLiwVariant(TTime(TDateTime(2009,EDecember,30,10,0,0,0))));
	
   	CLiwDefaultList* daysofmonthlist = CLiwDefaultList::NewL();
   	CLiwDefaultMap* map3 = CLiwDefaultMap::NewL();
    map3->InsertL(_L8("Day"), TLiwVariant(TInt32(0)) ); 
	map3->InsertL(_L8("WeekNum"), TLiwVariant( TInt32(1)));
   	daysofmonthlist->AppendL(TLiwVariant(map3));
   	map3->DecRef();
   	
   	CLiwDefaultMap* map2 = CLiwDefaultMap::NewL();
    map2->InsertL(_L8("Day"), TLiwVariant(TInt32(2)) ); 
	map2->InsertL(_L8("WeekNum"), TLiwVariant( TInt32(3)));
   	daysofmonthlist->AppendL(TLiwVariant(map2));
   	map2->DecRef();

	repeatmap->InsertL(_L8("DaysOfMonth"),TLiwVariant(daysofmonthlist));
   	daysofmonthlist->DecRef();

	map1->InsertL(_L8("RepeatRule"), TLiwVariant(repeatmap));
	CleanupStack::Pop(repeatmap);
	repeatmap->DecRef();

	TLiwGenericParam element;	
	element.SetNameAndValueL(_L8("Item"),TLiwVariant(map1));
	
	inparam->AppendL(element);
	element.Reset();
	CleanupStack::Pop(map1);
	map1->DecRef();
	TRAPD(err1, interface->ExecuteCmdL( KCmdAdd, *inparam,*outparam ));
    TInt pos1 = 0 ;
    
    const TLiwGenericParam* output = outparam->FindFirst( pos1,_L8("ErrorCode"));
	TBuf<10> local;
	if(output)
		{
		err = output->Value().AsTInt32();
		if ( err == KErrNone )
			{
			output = outparam->FindFirst( pos1,_L8("ReturnValue"));
			if(output)
				{
				TPtrC uidval = (TPtrC)(output->Value().AsDes());
				TBuf<50> uidg;
				uidg.Copy( uidval );
				local = GetEntry( inparam, outparam, uidg, KKCalFileName11);    
				}
			else
				err = -1;
			}
		}
    //TBuf<10> localuid1;
    //localuid1.Num(TInt64(local));
    
	inparam->Reset();
	outparam->Reset();
    
    TLiwGenericParam dsNameParam(KContentType, TLiwVariant(_L("CalendarEntry")));
	inparam->AppendL(dsNameParam);
	
	CLiwDefaultMap *filterMap = CLiwDefaultMap::NewL();
	TLiwGenericParam filterParam(KFilter, TLiwVariant(filterMap));
	inparam->AppendL(filterParam);
	filterMap->DecRef();

    filterMap->InsertL(KCalendarName,TLiwVariant(_L("C:CalendarFileA")));
    filterMap->InsertL(_L8("LocalId"),TLiwVariant(local));

	TRAP(err,interface->ExecuteCmdL( _L8("GetList") ,*inparam ,*outparam));
    
    pos = 0 ;
    
    const TLiwGenericParam* finaloutput = outparam->FindFirst( pos,_L8("ReturnValue"));
    TInt count = 0;
    CLiwMap* map;
    TInt retvalue = KErrNone;
	if ( finaloutput )     
		{
		CLiwIterable* iterlist = finaloutput->Value().AsIterable();
      	if(iterlist)
      		{
		    TLiwVariant data1;
      		while(iterlist->NextL(data1) )
	      		{
				const CLiwMap* res = data1.AsMap();
				if ( res )
					{
					TLiwVariant data;
					if(res->FindL(_L8("RepeatRule"), data))
						{
						const CLiwMap* map = data.AsMap();
						TLiwVariant rdata;
						if(map->FindL(_L8("Type"), rdata))
							{
							TInt type = rdata.AsTInt32();
							if( type != 3 )
								{
							    retvalue = KErrGeneral;
							    rdata.Reset();
								break;
								}
							}
						if(map->FindL(_L8("StartDate"), rdata))
							{
							TTime sdate = rdata.AsTTime();
							TDateTime stime = sdate.DateTime();
							TTime ostime(TDateTime(2007,ENovember,4,10,0,0,0));
							if( sdate != ostime)
								{
							    retvalue = KErrGeneral;
							    rdata.Reset();
								break;
								}
							}
						rdata.Reset();
						}

					data.Reset();	
					}
	      		}
      		data1.Reset();  
      		}
		}
	
	inparam->Reset();
	outparam->Reset();
	delete uidset1;
    RemoveProvCalendar(inparam, outparam, interface, KKCalFileName11);
    return retvalue;
	}
	

TInt CTestUpdateSync::UpdateAnniversaryL()
	{
	iServiceHandler = CLiwServiceHandler::NewL();

	CLiwGenericParamList* inparam = &(iServiceHandler->InParamListL());
	CLiwGenericParamList* outparam = &(iServiceHandler->OutParamListL());


	TInt err; 
	RCriteriaArray interest;
    CleanupClosePushL(interest);
    
	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KTestInterface,KTestContent);
	crit->SetServiceClass(TUid::Uid(KLiwClassBase));
    CleanupStack::PushL(crit);
    interest.AppendL(crit);    
	
	iServiceHandler->AttachL(interest);
    iServiceHandler->ExecuteServiceCmdL(*crit, *inparam, *outparam); 

	TInt pos = 0;

	outparam->FindFirst( pos, KTestInterface );
	if(pos != KErrNotFound)
		{
		interface = (*outparam)[pos].Value().AsInterface();	
		}
    CleanupStack::PopAndDestroy(crit);
    CleanupStack::PopAndDestroy(&interest); 

	outparam->Reset();
	inparam->Reset();
	
	AddProvCalendar(inparam, outparam, interface, KKCalFileName11);
	TUIDSet* uidset1;
    TBuf<50> globaluid;
    TBuf<10> localuid;
    //AddProvAppointmentDailyRepeatAndAttendees(inparam, outparam, interface, KKCalFileName11 ,uidset1 );
    AddProvAnni(inparam, outparam, interface, KKCalFileName11 ,uidset1);
    //localuid.Num(TInt64(uidset1->iLocalUID));
    globaluid.Copy(uidset1->iGlobalUID->Des());
    localuid = GetEntry( inparam, outparam, globaluid, KKCalFileName11); 
   	CLiwDefaultMap* map1 = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map1);

    TLiwVariant content(_L("CalendarEntry"));
	TLiwGenericParam element1;	
	element1.SetNameAndValueL(_L8("Type"),content);
	inparam->AppendL(element1);
	content.Reset();
	element1.Reset();


    map1->InsertL(_L8("CalendarName"), TLiwVariant(KKCalFileName11) ); 
    map1->InsertL(_L8("LocalId"),TLiwVariant(localuid));
	map1->InsertL(_L8("StartTime"), TLiwVariant(TTime(TDateTime(2007,EDecember,28,0,0,0,0))));
	map1->InsertL(_L8("Replication"), TLiwVariant(_L("Open")));
	map1->InsertL(_L8("Priority"), TLiwVariant(TInt32(1)));
	
	TLiwGenericParam element;	
	element.SetNameAndValueL(_L8("Item"),TLiwVariant(map1));
	
	inparam->AppendL(element);
	element.Reset();
    map1->DecRef();
    CleanupStack::Pop(map1);

	TRAPD(err1, interface->ExecuteCmdL( KCmdAdd, *inparam,*outparam ));
    TInt pos1 = 0 ;
    
    const TLiwGenericParam* output = outparam->FindFirst( pos1,_L8("ErrorCode"));
	TBuf<10> local;
	if(output)
		{
		err = output->Value().AsTInt32();
		if ( err == KErrNone )
			{
			output = outparam->FindFirst( pos1,_L8("ReturnValue"));
			if(output)
				{
				TPtrC uidval = (TPtrC)(output->Value().AsDes());
				local = GetEntry( inparam, outparam, uidval, KKCalFileName11);    
				}
			else
				err = -1;
			}
		}
    //TBuf<10> localuid1;
    //localuid1.Num(TInt64(local));
    
	inparam->Reset();
	outparam->Reset();
    
    TLiwGenericParam dsNameParam(KContentType, TLiwVariant(_L("CalendarEntry")));
	inparam->AppendL(dsNameParam);
	
	CLiwDefaultMap *filterMap = CLiwDefaultMap::NewL();
	TLiwGenericParam filterParam(KFilter, TLiwVariant(filterMap));
	inparam->AppendL(filterParam);
	filterMap->DecRef();

    filterMap->InsertL(KCalendarName,TLiwVariant(_L("C:CalendarFileA")));
    filterMap->InsertL(_L8("LocalId"),TLiwVariant(local));

	TRAP(err,interface->ExecuteCmdL( _L8("GetList") ,*inparam ,*outparam));
    
    pos = 0 ;
    
    const TLiwGenericParam* finaloutput = outparam->FindFirst( pos,_L8("ReturnValue"));
    TInt count = 0;
    CLiwMap* map;
    TInt retvalue = KErrNone;
	if ( finaloutput )     
		{
		CLiwIterable* iterlist = finaloutput->Value().AsIterable();
      	if(iterlist)
      		{
		    TLiwVariant data1;
      		while(iterlist->NextL(data1) )
	      		{
				const CLiwMap* res = data1.AsMap();
				if ( res )
					{
					TLiwVariant data;
					if(res->FindL(_L8("StartTime"), data))
						{
						TTime ostime(TDateTime(2007,EDecember,28,0,0,0,0));
						TTime stime = data.AsTTime();
						if( ostime != stime)
							{
						    retvalue = KErrGeneral;
							break;
							}
						}
						
					data.Reset();	
					}
	      		}
      		data1.Reset();  
      		}
		}
	
	inparam->Reset();
	outparam->Reset();
	delete uidset1;
    RemoveProvCalendar(inparam, outparam, interface, KKCalFileName11);
    return retvalue;
	}

TInt CTestUpdateSync::UpdateTodoEntryL()
	{
	iServiceHandler = CLiwServiceHandler::NewL();

	CLiwGenericParamList* inparam = &(iServiceHandler->InParamListL());
	CLiwGenericParamList* outparam = &(iServiceHandler->OutParamListL());


	TInt err; 
	RCriteriaArray interest;
    CleanupClosePushL(interest);
    
	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KTestInterface,KTestContent);
	crit->SetServiceClass(TUid::Uid(KLiwClassBase));
    CleanupStack::PushL(crit);
    interest.AppendL(crit);    
	
	iServiceHandler->AttachL(interest);
    iServiceHandler->ExecuteServiceCmdL(*crit, *inparam, *outparam); 

	TInt pos = 0;

	outparam->FindFirst( pos, KTestInterface );
	if(pos != KErrNotFound)
		{
		interface = (*outparam)[pos].Value().AsInterface();	
		}
    CleanupStack::PopAndDestroy(crit);
    CleanupStack::PopAndDestroy(&interest); 

	outparam->Reset();
	inparam->Reset();
	
	AddProvCalendar(inparam, outparam, interface, KKCalFileName11);
	TUIDSet* uidset1;
    TBuf<50> globaluid;
    TBuf<10> localuid;
    //AddProvAppointmentDailyRepeatAndAttendees(inparam, outparam, interface, KKCalFileName11 ,uidset1 );
    AddProvToDo(inparam, outparam, interface, KKCalFileName11 ,uidset1);
    //localuid.Num(TInt64(uidset1->iLocalUID));
    globaluid.Copy(uidset1->iGlobalUID->Des());
    localuid = GetEntry( inparam, outparam, globaluid, KKCalFileName11); 
    
   	CLiwDefaultMap* map1 = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map1);

    TLiwVariant content(_L("CalendarEntry"));
	TLiwGenericParam element1;	
	element1.SetNameAndValueL(_L8("Type"),content);
	inparam->AppendL(element1);
	content.Reset();
	element1.Reset();


    map1->InsertL(_L8("CalendarName"), TLiwVariant(KKCalFileName11) ); 
    map1->InsertL(_L8("LocalId"),TLiwVariant(localuid));
	map1->InsertL(_L8("StartTime"), TLiwVariant(TTime(TDateTime(2007,EAugust,19,0,0,0,0))));
	
	TLiwGenericParam element;	
	element.SetNameAndValueL(_L8("Item"),TLiwVariant(map1));
	
	inparam->AppendL(element);
	element.Reset();
    map1->DecRef();
    CleanupStack::Pop(map1);

	TRAPD(err1, interface->ExecuteCmdL( KCmdAdd, *inparam,*outparam ));
    TInt pos1 = 0 ;
    
    const TLiwGenericParam* output = outparam->FindFirst( pos1,_L8("ErrorCode"));
	TBuf<10> local;
	if(output)
		{
		err = output->Value().AsTInt32();
		if ( err == KErrNone )
			{
			output = outparam->FindFirst( pos1,_L8("ReturnValue"));
			if(output)
				{
				TPtrC uidval = (TPtrC)(output->Value().AsDes());
				local = GetEntry( inparam, outparam, uidval, KKCalFileName11);    
				}
			else
				err = -1;
			}
		}
    //TBuf<10> localuid1;
    //localuid1.Num(TInt64(local));
    
	inparam->Reset();
	outparam->Reset();
    
    TLiwGenericParam dsNameParam(KContentType, TLiwVariant(_L("CalendarEntry")));
	inparam->AppendL(dsNameParam);
	
	CLiwDefaultMap *filterMap = CLiwDefaultMap::NewL();
	TLiwGenericParam filterParam(KFilter, TLiwVariant(filterMap));
	inparam->AppendL(filterParam);
	filterMap->DecRef();

    filterMap->InsertL(KCalendarName,TLiwVariant(_L("C:CalendarFileA")));
    filterMap->InsertL(_L8("LocalId"),TLiwVariant(local));

	TRAP(err,interface->ExecuteCmdL( _L8("GetList") ,*inparam ,*outparam));
    
    pos = 0 ;
    
    const TLiwGenericParam* finaloutput = outparam->FindFirst( pos,_L8("ReturnValue"));
    TInt count = 0;
    CLiwMap* map;
    TInt retvalue = KErrNone;
	if ( finaloutput )     
		{
		CLiwIterable* iterlist = finaloutput->Value().AsIterable();
      	if(iterlist)
      		{
		    TLiwVariant data1;
      		while(iterlist->NextL(data1) )
	      		{
				const CLiwMap* res = data1.AsMap();
				if ( res )
					{
					TLiwVariant data;
					if(res->FindL(_L8("StartTime"), data))
						{
						TTime ostime(TDateTime(2007,EAugust,19,0,0,0,0));
						TTime stime = data.AsTTime();
						if( ostime != stime)
							{
						    retvalue = KErrGeneral;
							break;
							}
						}
						
					data.Reset();	
					}
	      		}
      		data1.Reset();  
      		}
		}
	
	inparam->Reset();
	outparam->Reset();
	delete uidset1;
    RemoveProvCalendar(inparam, outparam, interface, KKCalFileName11);
    return retvalue;
	}
TInt CTestUpdateSync::UpdateDayEventL()
	{
	iServiceHandler = CLiwServiceHandler::NewL();

	CLiwGenericParamList* inparam = &(iServiceHandler->InParamListL());
	CLiwGenericParamList* outparam = &(iServiceHandler->OutParamListL());


	TInt err; 
	RCriteriaArray interest;
    CleanupClosePushL(interest);
    
	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KTestInterface,KTestContent);
	crit->SetServiceClass(TUid::Uid(KLiwClassBase));
    CleanupStack::PushL(crit);
    interest.AppendL(crit);    
	
	iServiceHandler->AttachL(interest);
    iServiceHandler->ExecuteServiceCmdL(*crit, *inparam, *outparam); 

	TInt pos = 0;

	outparam->FindFirst( pos, KTestInterface );
	if(pos != KErrNotFound)
		{
		interface = (*outparam)[pos].Value().AsInterface();	
		}
    CleanupStack::PopAndDestroy(crit);
    CleanupStack::PopAndDestroy(&interest); 

	outparam->Reset();
	inparam->Reset();
	
	AddProvCalendar(inparam, outparam, interface, KKCalFileName11);
	TUIDSet* uidset1;
    TBuf<50> globaluid;
    TBuf<10> localuid;
    //AddProvAppointmentDailyRepeatAndAttendees(inparam, outparam, interface, KKCalFileName11 ,uidset1 );
    AddProvReminder(inparam, outparam, interface, KKCalFileName11 ,uidset1);
    //localuid.Num(TInt64(uidset1->iLocalUID));
    globaluid.Copy(uidset1->iGlobalUID->Des());
	localuid = GetEntry( inparam, outparam, globaluid, KKCalFileName11);    

    
   	CLiwDefaultMap* map1 = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map1);

    TLiwVariant content(_L("CalendarEntry"));
	TLiwGenericParam element1;	
	element1.SetNameAndValueL(_L8("Type"),content);
	inparam->AppendL(element1);
	content.Reset();
	element1.Reset();


    map1->InsertL(_L8("CalendarName"), TLiwVariant(KKCalFileName11) ); 
    map1->InsertL(_L8("LocalId"),TLiwVariant(localuid));
	map1->InsertL(_L8("StartTime"), TLiwVariant(TTime(TDateTime(2007,EJuly,22,11,30,0,0))));
	map1->InsertL(_L8("Description"), TLiwVariant(_L("New reminder created")));
	
	TLiwGenericParam element;	
	element.SetNameAndValueL(_L8("Item"),TLiwVariant(map1));
	
	inparam->AppendL(element);
	element.Reset();
    map1->DecRef();
    CleanupStack::Pop(map1);

	TRAPD(err1, interface->ExecuteCmdL( KCmdAdd, *inparam,*outparam ));
    TInt pos1 = 0 ;
    
    const TLiwGenericParam* output = outparam->FindFirst( pos1,_L8("ErrorCode"));
	TBuf<10> local;
	if(output)
		{
		err = output->Value().AsTInt32();
		if ( err == KErrNone )
			{
			output = outparam->FindFirst( pos1,_L8("ReturnValue"));
			if(output)
				{
				TPtrC uidval = (TPtrC)(output->Value().AsDes());
				local = GetEntry( inparam, outparam, uidval, KKCalFileName11);    
				}
			else
				err = -1;
			}
		}
    //TBuf<10> localuid1;
    //localuid1.Num(TInt64(local));
    
	inparam->Reset();
	outparam->Reset();
    
    TLiwGenericParam dsNameParam(KContentType, TLiwVariant(_L("CalendarEntry")));
	inparam->AppendL(dsNameParam);
	
	CLiwDefaultMap *filterMap = CLiwDefaultMap::NewL();
	TLiwGenericParam filterParam(KFilter, TLiwVariant(filterMap));
	inparam->AppendL(filterParam);
	filterMap->DecRef();

    filterMap->InsertL(KCalendarName,TLiwVariant(_L("C:CalendarFileA")));
    filterMap->InsertL(_L8("LocalId"),TLiwVariant(local));

	TRAP(err,interface->ExecuteCmdL( _L8("GetList") ,*inparam ,*outparam));
    
    pos = 0 ;
    
    const TLiwGenericParam* finaloutput = outparam->FindFirst( pos,_L8("ReturnValue"));
    TInt count = 0;
    CLiwMap* map;
    TInt retvalue = KErrNone;
	if ( finaloutput )     
		{
		CLiwIterable* iterlist = finaloutput->Value().AsIterable();
      	if(iterlist)
      		{
		    TLiwVariant data1;
      		while(iterlist->NextL(data1) )
	      		{
				const CLiwMap* res = data1.AsMap();
				if ( res )
					{
					TLiwVariant data;
					if(res->FindL(_L8("StartTime"), data))
						{
						TTime ostime(TDateTime(2007,EJuly,22,11,30,0,0));
						TTime stime = data.AsTTime();
						if( ostime != stime)
							{
						    retvalue = KErrGeneral;
							break;
							}
						}
						
					data.Reset();	
					}
	      		}
      		data1.Reset();  
      		}
		}
	
	inparam->Reset();
	outparam->Reset();
	delete uidset1;
    RemoveProvCalendar(inparam, outparam, interface, KKCalFileName11);
    return retvalue;

	}

TInt CTestUpdateSync::UpdateReminderL()  
	{
	iServiceHandler = CLiwServiceHandler::NewL();

	CLiwGenericParamList* inparam = &(iServiceHandler->InParamListL());
	CLiwGenericParamList* outparam = &(iServiceHandler->OutParamListL());


	TInt err; 
	RCriteriaArray interest;
    CleanupClosePushL(interest);
    
	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KTestInterface,KTestContent);
	crit->SetServiceClass(TUid::Uid(KLiwClassBase));
    CleanupStack::PushL(crit);
    interest.AppendL(crit);    
	
	iServiceHandler->AttachL(interest);
    iServiceHandler->ExecuteServiceCmdL(*crit, *inparam, *outparam); 

	TInt pos = 0;

	outparam->FindFirst( pos, KTestInterface );
	if(pos != KErrNotFound)
		{
		interface = (*outparam)[pos].Value().AsInterface();	
		}
    CleanupStack::PopAndDestroy(crit);
    CleanupStack::PopAndDestroy(&interest); 

	outparam->Reset();
	inparam->Reset();
	
	AddProvCalendar(inparam, outparam, interface, KKCalFileName11);
	TUIDSet* uidset1;
    TBuf<50> globaluid;
    TBuf<10> localuid;
    //AddProvAppointmentDailyRepeatAndAttendees(inparam, outparam, interface, KKCalFileName11 ,uidset1 );
    AddProvDayEvent(inparam, outparam, interface, KKCalFileName11 ,uidset1);
    //localuid.Num(TInt64(uidset1->iLocalUID));
    globaluid.Copy(uidset1->iGlobalUID->Des());
    localuid = GetEntry( inparam, outparam, globaluid, KKCalFileName11); 
    
   	CLiwDefaultMap* map1 = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map1);

    TLiwVariant content(_L("CalendarEntry"));
	TLiwGenericParam element1;	
	element1.SetNameAndValueL(_L8("Type"),content);
	inparam->AppendL(element1);
	content.Reset();
	element1.Reset();


    map1->InsertL(_L8("CalendarName"), TLiwVariant(KKCalFileName11) ); 
    map1->InsertL(_L8("LocalId"),TLiwVariant(localuid));
	map1->InsertL(_L8("StartTime"), TLiwVariant(TTime(TDateTime(2007,EJuly,26,8,0,0,0))));
	map1->InsertL(_L8("Replication"), TLiwVariant(_L("Open")));
	
	TLiwGenericParam element;	
	element.SetNameAndValueL(_L8("Item"),TLiwVariant(map1));
	
	inparam->AppendL(element);
	element.Reset();
    map1->DecRef();
    CleanupStack::Pop(map1);

	TRAPD(err1, interface->ExecuteCmdL( KCmdAdd, *inparam,*outparam ));
    TInt pos1 = 0 ;
    
    const TLiwGenericParam* output = outparam->FindFirst( pos1,_L8("ErrorCode"));
	TBuf<10> local;
	if(output)
		{
		err = output->Value().AsTInt32();
		if ( err == KErrNone )
			{
			output = outparam->FindFirst( pos1,_L8("ReturnValue"));
			if(output)
				{
				TPtrC uidval = (TPtrC)(output->Value().AsDes());
				local = GetEntry( inparam, outparam, uidval, KKCalFileName11);    
				}
			else
				err = -1;
			}
		}
   // TBuf<10> localuid1;
   // localuid1.Num(TInt64(local));
    
	inparam->Reset();
	outparam->Reset();
    
    TLiwGenericParam dsNameParam(KContentType, TLiwVariant(_L("CalendarEntry")));
	inparam->AppendL(dsNameParam);
	
	CLiwDefaultMap *filterMap = CLiwDefaultMap::NewL();
	TLiwGenericParam filterParam(KFilter, TLiwVariant(filterMap));
	inparam->AppendL(filterParam);
	filterMap->DecRef();

    filterMap->InsertL(KCalendarName,TLiwVariant(_L("C:CalendarFileA")));
    filterMap->InsertL(_L8("LocalId"),TLiwVariant(local));

	TRAP(err,interface->ExecuteCmdL( _L8("GetList") ,*inparam ,*outparam));
    
    pos = 0 ;
    
    const TLiwGenericParam* finaloutput = outparam->FindFirst( pos,_L8("ReturnValue"));
    TInt count = 0;
    CLiwMap* map;
    TInt retvalue = KErrNone;
	if ( finaloutput )     
		{
		CLiwIterable* iterlist = finaloutput->Value().AsIterable();
      	if(iterlist)
      		{
		    TLiwVariant data1;
      		while(iterlist->NextL(data1) )
	      		{
				const CLiwMap* res = data1.AsMap();
				if ( res )
					{
					TLiwVariant data;
					if(res->FindL(_L8("StartTime"), data))
						{
						TTime ostime(TDateTime(2007,EJuly,26,8,0,0,0));
						TTime stime = data.AsTTime();
						if( ostime != stime)
							{
						    retvalue = KErrGeneral;
							break;
							}
						}
						
					data.Reset();	
					}
	      		}
      		data1.Reset();  
      		}
		}
	
	inparam->Reset();
	outparam->Reset();
	delete uidset1;
    RemoveProvCalendar(inparam, outparam, interface, KKCalFileName11);
    return retvalue;

	}
 
TInt CTestUpdateSync::UpdateAppointmentEntryWithGlobalIdL()
    {
    iServiceHandler = CLiwServiceHandler::NewL();

    CLiwGenericParamList* inparam = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outparam = &(iServiceHandler->OutParamListL());


    TInt err; 
    RCriteriaArray interest;
    CleanupClosePushL(interest);
    
    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KTestInterface,KTestContent);
    crit->SetServiceClass(TUid::Uid(KLiwClassBase));
    CleanupStack::PushL(crit);
    interest.AppendL(crit);    
    
    iServiceHandler->AttachL(interest);
    iServiceHandler->ExecuteServiceCmdL(*crit, *inparam, *outparam); 

    TInt pos = 0;

    outparam->FindFirst( pos, KTestInterface );
    if(pos != KErrNotFound)
        {
        interface = (*outparam)[pos].Value().AsInterface(); 
        }
    CleanupStack::PopAndDestroy(crit);
    CleanupStack::PopAndDestroy(&interest); 

    outparam->Reset();
    inparam->Reset();
    
    AddProvCalendar(inparam, outparam, interface, KKCalFileName11);
    TUIDSet* uidset1;
    TBuf<50> globaluid;
    TBuf<10> localuid;
    //AddProvAppointmentDailyRepeatAndAttendees(inparam, outparam, interface, KKCalFileName11 ,uidset1 );
    AddProvAppointmentWithoutRepeat(inparam, outparam, interface, KKCalFileName11 ,uidset1);
    //localuid.Num(TInt64(uidset1->iLocalUID));
    globaluid.Copy(uidset1->iGlobalUID->Des());
    localuid = GetEntry( inparam, outparam, globaluid, KKCalFileName11);
    
    CLiwDefaultMap* map1 = CLiwDefaultMap::NewL();
    CleanupStack::PushL(map1);

    TLiwVariant content(_L("CalendarEntry"));
    TLiwGenericParam element1;  
    element1.SetNameAndValueL(_L8("Type"),content);
    inparam->AppendL(element1);
    content.Reset();
    element1.Reset();


    map1->InsertL(_L8("CalendarName"), TLiwVariant(KKCalFileName11) ); 
    map1->InsertL(_L8("id"),TLiwVariant(globaluid));
    map1->InsertL(_L8("StartTime"), TLiwVariant(TTime(TDateTime(2007,EOctober,3,10,0,0,0))));
    map1->InsertL(_L8("EndTime"), TLiwVariant(TTime(TDateTime(2007,EOctober,3,10,30,0,0))));
    map1->InsertL(_L8("AlarmTime"), TLiwVariant(TTime(TDateTime(2007,EOctober,3,9,30,0,0))));
    TLiwGenericParam element;   
    element.SetNameAndValueL(_L8("Item"),TLiwVariant(map1));
    
    inparam->AppendL(element);
    element.Reset();
    map1->DecRef();
    CleanupStack::Pop(map1);

    TRAPD(err1, interface->ExecuteCmdL( KCmdAdd, *inparam,*outparam ));

    inparam->Reset();
    outparam->Reset();
    
    TLiwGenericParam dsNameParam(KContentType, TLiwVariant(_L("CalendarEntry")));
    inparam->AppendL(dsNameParam);
    
    CLiwDefaultMap *filterMap = CLiwDefaultMap::NewL();
    TLiwGenericParam filterParam(KFilter, TLiwVariant(filterMap));
    inparam->AppendL(filterParam);
    filterMap->DecRef();

    filterMap->InsertL(KCalendarName,TLiwVariant(_L("C:CalendarFileA")));
    filterMap->InsertL(_L8("LocalId"),TLiwVariant(localuid));

    TRAP(err,interface->ExecuteCmdL( _L8("GetList") ,*inparam ,*outparam));
    
    pos = 0 ;
    
    const TLiwGenericParam* finaloutput = outparam->FindFirst( pos,_L8("ReturnValue"));
    TInt count = 0;
    CLiwMap* map;
    TInt retvalue = KErrNone;
    if ( finaloutput )     
        {
        CLiwIterable* iterlist = finaloutput->Value().AsIterable();
        if(iterlist)
            {
            TLiwVariant data1;
            while(iterlist->NextL(data1) )
                {
                const CLiwMap* res = data1.AsMap();
                if ( res )
                    {
                    TLiwVariant data;
                    if(res->FindL(_L8("StartTime"), data))
                        {
                        TTime ostime(TDateTime(2007,EOctober,3,10,0,0,0));
                        TTime stime = data.AsTTime();
                        if( ostime != stime)
                            {
                            retvalue = KErrGeneral;
                            break;
                            }
                        }

                    if(res->FindL(_L8("EndTime"), data))
                        {
                        TTime ostime(TDateTime(2007,EOctober,3,10,30,0,0));
                        TTime stime = data.AsTTime();
                        if( ostime != stime)
                            {
                            retvalue = KErrGeneral;
                            break;
                            }
                        }

                    data.Reset();   
                    }
                }
            data1.Reset();  
            }
        }
    
    inparam->Reset();
    outparam->Reset();
    delete uidset1;
    RemoveProvCalendar(inparam, outparam, interface, KKCalFileName11);
    return retvalue;
    }
TInt CTestUpdateSync::UpdateAnniversaryWithGlobalIdL()
    {
    iServiceHandler = CLiwServiceHandler::NewL();

    CLiwGenericParamList* inparam = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outparam = &(iServiceHandler->OutParamListL());


    TInt err; 
    RCriteriaArray interest;
    CleanupClosePushL(interest);
    
    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KTestInterface,KTestContent);
    crit->SetServiceClass(TUid::Uid(KLiwClassBase));
    CleanupStack::PushL(crit);
    interest.AppendL(crit);    
    
    iServiceHandler->AttachL(interest);
    iServiceHandler->ExecuteServiceCmdL(*crit, *inparam, *outparam); 

    TInt pos = 0;

    outparam->FindFirst( pos, KTestInterface );
    if(pos != KErrNotFound)
        {
        interface = (*outparam)[pos].Value().AsInterface(); 
        }
    CleanupStack::PopAndDestroy(crit);
    CleanupStack::PopAndDestroy(&interest); 

    outparam->Reset();
    inparam->Reset();
    
    AddProvCalendar(inparam, outparam, interface, KKCalFileName11);
    TUIDSet* uidset1;
    TBuf<50> globaluid;
    TBuf<10> localuid;
    //AddProvAppointmentDailyRepeatAndAttendees(inparam, outparam, interface, KKCalFileName11 ,uidset1 );
    AddProvAnni(inparam, outparam, interface, KKCalFileName11 ,uidset1);
    //localuid.Num(TInt64(uidset1->iLocalUID));
    globaluid.Copy(uidset1->iGlobalUID->Des());
    localuid = GetEntry( inparam, outparam, globaluid, KKCalFileName11); 
    CLiwDefaultMap* map1 = CLiwDefaultMap::NewL();
    CleanupStack::PushL(map1);

    TLiwVariant content(_L("CalendarEntry"));
    TLiwGenericParam element1;  
    element1.SetNameAndValueL(_L8("Type"),content);
    inparam->AppendL(element1);
    content.Reset();
    element1.Reset();


    map1->InsertL(_L8("CalendarName"), TLiwVariant(KKCalFileName11) ); 
    map1->InsertL(_L8("id"),TLiwVariant(globaluid));
    map1->InsertL(_L8("StartTime"), TLiwVariant(TTime(TDateTime(2007,EDecember,28,0,0,0,0))));
    map1->InsertL(_L8("Replication"), TLiwVariant(_L("Open")));
    map1->InsertL(_L8("Priority"), TLiwVariant(TInt32(1)));
    
    TLiwGenericParam element;   
    element.SetNameAndValueL(_L8("Item"),TLiwVariant(map1));
    
    inparam->AppendL(element);
    element.Reset();
    map1->DecRef();
    CleanupStack::Pop(map1);

    TRAPD(err1, interface->ExecuteCmdL( KCmdAdd, *inparam,*outparam ));
    TInt pos1 = 0 ;
    
    const TLiwGenericParam* output = outparam->FindFirst( pos1,_L8("ErrorCode"));
    TBuf<10> local;
    if(output)
        {
        err = output->Value().AsTInt32();
        if ( err == KErrNone )
            {
            output = outparam->FindFirst( pos1,_L8("ReturnValue"));
            if(output)
                {
                TPtrC uidval = (TPtrC)(output->Value().AsDes());
                local = GetEntry( inparam, outparam, uidval, KKCalFileName11);    
                }
            else
                err = -1;
            }
        }
    //TBuf<10> localuid1;
    //localuid1.Num(TInt64(local));
    
    inparam->Reset();
    outparam->Reset();
    
    TLiwGenericParam dsNameParam(KContentType, TLiwVariant(_L("CalendarEntry")));
    inparam->AppendL(dsNameParam);
    
    CLiwDefaultMap *filterMap = CLiwDefaultMap::NewL();
    TLiwGenericParam filterParam(KFilter, TLiwVariant(filterMap));
    inparam->AppendL(filterParam);
    filterMap->DecRef();

    filterMap->InsertL(KCalendarName,TLiwVariant(_L("C:CalendarFileA")));
    filterMap->InsertL(_L8("LocalId"),TLiwVariant(local));

    TRAP(err,interface->ExecuteCmdL( _L8("GetList") ,*inparam ,*outparam));
    
    pos = 0 ;
    
    const TLiwGenericParam* finaloutput = outparam->FindFirst( pos,_L8("ReturnValue"));
    TInt count = 0;
    CLiwMap* map;
    TInt retvalue = KErrNone;
    if ( finaloutput )     
        {
        CLiwIterable* iterlist = finaloutput->Value().AsIterable();
        if(iterlist)
            {
            TLiwVariant data1;
            while(iterlist->NextL(data1) )
                {
                const CLiwMap* res = data1.AsMap();
                if ( res )
                    {
                    TLiwVariant data;
                    if(res->FindL(_L8("StartTime"), data))
                        {
                        TTime ostime(TDateTime(2007,EDecember,28,0,0,0,0));
                        TTime stime = data.AsTTime();
                        if( ostime != stime)
                            {
                            retvalue = KErrGeneral;
                            break;
                            }
                        }
                        
                    data.Reset();   
                    }
                }
            data1.Reset();  
            }
        }
    
    inparam->Reset();
    outparam->Reset();
    delete uidset1;
    RemoveProvCalendar(inparam, outparam, interface, KKCalFileName11);
    return retvalue;
    }

TInt CTestUpdateSync::UpdateTodoEntryWithGlobalIdL()
    {
    iServiceHandler = CLiwServiceHandler::NewL();

    CLiwGenericParamList* inparam = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outparam = &(iServiceHandler->OutParamListL());


    TInt err; 
    RCriteriaArray interest;
    CleanupClosePushL(interest);
    
    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KTestInterface,KTestContent);
    crit->SetServiceClass(TUid::Uid(KLiwClassBase));
    CleanupStack::PushL(crit);
    interest.AppendL(crit);    
    
    iServiceHandler->AttachL(interest);
    iServiceHandler->ExecuteServiceCmdL(*crit, *inparam, *outparam); 

    TInt pos = 0;

    outparam->FindFirst( pos, KTestInterface );
    if(pos != KErrNotFound)
        {
        interface = (*outparam)[pos].Value().AsInterface(); 
        }
    CleanupStack::PopAndDestroy(crit);
    CleanupStack::PopAndDestroy(&interest); 

    outparam->Reset();
    inparam->Reset();
    
    AddProvCalendar(inparam, outparam, interface, KKCalFileName11);
    TUIDSet* uidset1;
    TBuf<50> globaluid;
    TBuf<10> localuid;
    //AddProvAppointmentDailyRepeatAndAttendees(inparam, outparam, interface, KKCalFileName11 ,uidset1 );
    AddProvToDo(inparam, outparam, interface, KKCalFileName11 ,uidset1);
    //localuid.Num(TInt64(uidset1->iLocalUID));
    globaluid.Copy(uidset1->iGlobalUID->Des());
    localuid = GetEntry( inparam, outparam, globaluid, KKCalFileName11); 
    
    CLiwDefaultMap* map1 = CLiwDefaultMap::NewL();
    CleanupStack::PushL(map1);

    TLiwVariant content(_L("CalendarEntry"));
    TLiwGenericParam element1;  
    element1.SetNameAndValueL(_L8("Type"),content);
    inparam->AppendL(element1);
    content.Reset();
    element1.Reset();


    map1->InsertL(_L8("CalendarName"), TLiwVariant(KKCalFileName11) ); 
    map1->InsertL(_L8("id"),TLiwVariant(globaluid));
    map1->InsertL(_L8("StartTime"), TLiwVariant(TTime(TDateTime(2007,EAugust,19,0,0,0,0))));
    
    TLiwGenericParam element;   
    element.SetNameAndValueL(_L8("Item"),TLiwVariant(map1));
    
    inparam->AppendL(element);
    element.Reset();
    map1->DecRef();
    CleanupStack::Pop(map1);

    TRAPD(err1, interface->ExecuteCmdL( KCmdAdd, *inparam,*outparam ));
    TInt pos1 = 0 ;
    
    const TLiwGenericParam* output = outparam->FindFirst( pos1,_L8("ErrorCode"));
    TBuf<10> local;
    if(output)
        {
        err = output->Value().AsTInt32();
        if ( err == KErrNone )
            {
            output = outparam->FindFirst( pos1,_L8("ReturnValue"));
            if(output)
                {
                TPtrC uidval = (TPtrC)(output->Value().AsDes());
                local = GetEntry( inparam, outparam, uidval, KKCalFileName11);    
                }
            else
                err = -1;
            }
        }
    //TBuf<10> localuid1;
    //localuid1.Num(TInt64(local));
    
    inparam->Reset();
    outparam->Reset();
    
    TLiwGenericParam dsNameParam(KContentType, TLiwVariant(_L("CalendarEntry")));
    inparam->AppendL(dsNameParam);
    
    CLiwDefaultMap *filterMap = CLiwDefaultMap::NewL();
    TLiwGenericParam filterParam(KFilter, TLiwVariant(filterMap));
    inparam->AppendL(filterParam);
    filterMap->DecRef();

    filterMap->InsertL(KCalendarName,TLiwVariant(_L("C:CalendarFileA")));
    filterMap->InsertL(_L8("LocalId"),TLiwVariant(local));

    TRAP(err,interface->ExecuteCmdL( _L8("GetList") ,*inparam ,*outparam));
    
    pos = 0 ;
    
    const TLiwGenericParam* finaloutput = outparam->FindFirst( pos,_L8("ReturnValue"));
    TInt count = 0;
    CLiwMap* map;
    TInt retvalue = KErrNone;
    if ( finaloutput )     
        {
        CLiwIterable* iterlist = finaloutput->Value().AsIterable();
        if(iterlist)
            {
            TLiwVariant data1;
            while(iterlist->NextL(data1) )
                {
                const CLiwMap* res = data1.AsMap();
                if ( res )
                    {
                    TLiwVariant data;
                    if(res->FindL(_L8("StartTime"), data))
                        {
                        TTime ostime(TDateTime(2007,EAugust,19,0,0,0,0));
                        TTime stime = data.AsTTime();
                        if( ostime != stime)
                            {
                            retvalue = KErrGeneral;
                            break;
                            }
                        }
                        
                    data.Reset();   
                    }
                }
            data1.Reset();  
            }
        }
    
    inparam->Reset();
    outparam->Reset();
    delete uidset1;
    RemoveProvCalendar(inparam, outparam, interface, KKCalFileName11);
    return retvalue;
    }
TInt CTestUpdateSync::UpdateDayEventWithGlobalIdL()
    {
    iServiceHandler = CLiwServiceHandler::NewL();

    CLiwGenericParamList* inparam = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outparam = &(iServiceHandler->OutParamListL());


    TInt err; 
    RCriteriaArray interest;
    CleanupClosePushL(interest);
    
    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KTestInterface,KTestContent);
    crit->SetServiceClass(TUid::Uid(KLiwClassBase));
    CleanupStack::PushL(crit);
    interest.AppendL(crit);    
    
    iServiceHandler->AttachL(interest);
    iServiceHandler->ExecuteServiceCmdL(*crit, *inparam, *outparam); 

    TInt pos = 0;

    outparam->FindFirst( pos, KTestInterface );
    if(pos != KErrNotFound)
        {
        interface = (*outparam)[pos].Value().AsInterface(); 
        }
    CleanupStack::PopAndDestroy(crit);
    CleanupStack::PopAndDestroy(&interest); 

    outparam->Reset();
    inparam->Reset();
    
    AddProvCalendar(inparam, outparam, interface, KKCalFileName11);
    TUIDSet* uidset1;
    TBuf<50> globaluid;
    TBuf<10> localuid;
    //AddProvAppointmentDailyRepeatAndAttendees(inparam, outparam, interface, KKCalFileName11 ,uidset1 );
    AddProvReminder(inparam, outparam, interface, KKCalFileName11 ,uidset1);
    //localuid.Num(TInt64(uidset1->iLocalUID));
    globaluid.Copy(uidset1->iGlobalUID->Des());
    localuid = GetEntry( inparam, outparam, globaluid, KKCalFileName11);    

    
    CLiwDefaultMap* map1 = CLiwDefaultMap::NewL();
    CleanupStack::PushL(map1);

    TLiwVariant content(_L("CalendarEntry"));
    TLiwGenericParam element1;  
    element1.SetNameAndValueL(_L8("Type"),content);
    inparam->AppendL(element1);
    content.Reset();
    element1.Reset();


    map1->InsertL(_L8("CalendarName"), TLiwVariant(KKCalFileName11) ); 
    map1->InsertL(_L8("id"),TLiwVariant(globaluid));
    map1->InsertL(_L8("StartTime"), TLiwVariant(TTime(TDateTime(2007,EJuly,22,11,30,0,0))));
    map1->InsertL(_L8("Description"), TLiwVariant(_L("New reminder created")));
    
    TLiwGenericParam element;   
    element.SetNameAndValueL(_L8("Item"),TLiwVariant(map1));
    
    inparam->AppendL(element);
    element.Reset();
    map1->DecRef();
    CleanupStack::Pop(map1);

    TRAPD(err1, interface->ExecuteCmdL( KCmdAdd, *inparam,*outparam ));
    TInt pos1 = 0 ;
    
    const TLiwGenericParam* output = outparam->FindFirst( pos1,_L8("ErrorCode"));
    TBuf<10> local;
    if(output)
        {
        err = output->Value().AsTInt32();
        if ( err == KErrNone )
            {
            output = outparam->FindFirst( pos1,_L8("ReturnValue"));
            if(output)
                {
                TPtrC uidval = (TPtrC)(output->Value().AsDes());
                local = GetEntry( inparam, outparam, uidval, KKCalFileName11);    
                }
            else
                err = -1;
            }
        }
    //TBuf<10> localuid1;
    //localuid1.Num(TInt64(local));
    
    inparam->Reset();
    outparam->Reset();
    
    TLiwGenericParam dsNameParam(KContentType, TLiwVariant(_L("CalendarEntry")));
    inparam->AppendL(dsNameParam);
    
    CLiwDefaultMap *filterMap = CLiwDefaultMap::NewL();
    TLiwGenericParam filterParam(KFilter, TLiwVariant(filterMap));
    inparam->AppendL(filterParam);
    filterMap->DecRef();

    filterMap->InsertL(KCalendarName,TLiwVariant(_L("C:CalendarFileA")));
    filterMap->InsertL(_L8("LocalId"),TLiwVariant(local));

    TRAP(err,interface->ExecuteCmdL( _L8("GetList") ,*inparam ,*outparam));
    
    pos = 0 ;
    
    const TLiwGenericParam* finaloutput = outparam->FindFirst( pos,_L8("ReturnValue"));
    TInt count = 0;
    CLiwMap* map;
    TInt retvalue = KErrNone;
    if ( finaloutput )     
        {
        CLiwIterable* iterlist = finaloutput->Value().AsIterable();
        if(iterlist)
            {
            TLiwVariant data1;
            while(iterlist->NextL(data1) )
                {
                const CLiwMap* res = data1.AsMap();
                if ( res )
                    {
                    TLiwVariant data;
                    if(res->FindL(_L8("StartTime"), data))
                        {
                        TTime ostime(TDateTime(2007,EJuly,22,11,30,0,0));
                        TTime stime = data.AsTTime();
                        if( ostime != stime)
                            {
                            retvalue = KErrGeneral;
                            break;
                            }
                        }
                        
                    data.Reset();   
                    }
                }
            data1.Reset();  
            }
        }
    
    inparam->Reset();
    outparam->Reset();
    delete uidset1;
    RemoveProvCalendar(inparam, outparam, interface, KKCalFileName11);
    return retvalue;

    }

TInt CTestUpdateSync::UpdateReminderWithGlobalIdL()  
    {
    iServiceHandler = CLiwServiceHandler::NewL();

    CLiwGenericParamList* inparam = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outparam = &(iServiceHandler->OutParamListL());


    TInt err; 
    RCriteriaArray interest;
    CleanupClosePushL(interest);
    
    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KTestInterface,KTestContent);
    crit->SetServiceClass(TUid::Uid(KLiwClassBase));
    CleanupStack::PushL(crit);
    interest.AppendL(crit);    
    
    iServiceHandler->AttachL(interest);
    iServiceHandler->ExecuteServiceCmdL(*crit, *inparam, *outparam); 

    TInt pos = 0;

    outparam->FindFirst( pos, KTestInterface );
    if(pos != KErrNotFound)
        {
        interface = (*outparam)[pos].Value().AsInterface(); 
        }
    CleanupStack::PopAndDestroy(crit);
    CleanupStack::PopAndDestroy(&interest); 

    outparam->Reset();
    inparam->Reset();
    
    AddProvCalendar(inparam, outparam, interface, KKCalFileName11);
    TUIDSet* uidset1;
    TBuf<50> globaluid;
    TBuf<10> localuid;
    //AddProvAppointmentDailyRepeatAndAttendees(inparam, outparam, interface, KKCalFileName11 ,uidset1 );
    AddProvDayEvent(inparam, outparam, interface, KKCalFileName11 ,uidset1);
    //localuid.Num(TInt64(uidset1->iLocalUID));
    globaluid.Copy(uidset1->iGlobalUID->Des());
    localuid = GetEntry( inparam, outparam, globaluid, KKCalFileName11); 
    
    CLiwDefaultMap* map1 = CLiwDefaultMap::NewL();
    CleanupStack::PushL(map1);

    TLiwVariant content(_L("CalendarEntry"));
    TLiwGenericParam element1;  
    element1.SetNameAndValueL(_L8("Type"),content);
    inparam->AppendL(element1);
    content.Reset();
    element1.Reset();


    map1->InsertL(_L8("CalendarName"), TLiwVariant(KKCalFileName11) ); 
    map1->InsertL(_L8("id"),TLiwVariant(globaluid));
    map1->InsertL(_L8("StartTime"), TLiwVariant(TTime(TDateTime(2007,EJuly,26,8,0,0,0))));
    map1->InsertL(_L8("Replication"), TLiwVariant(_L("Open")));
    
    TLiwGenericParam element;   
    element.SetNameAndValueL(_L8("Item"),TLiwVariant(map1));
    
    inparam->AppendL(element);
    element.Reset();
    map1->DecRef();
    CleanupStack::Pop(map1);

    TRAPD(err1, interface->ExecuteCmdL( KCmdAdd, *inparam,*outparam ));
    TInt pos1 = 0 ;
    
    const TLiwGenericParam* output = outparam->FindFirst( pos1,_L8("ErrorCode"));
    TBuf<10> local;
    if(output)
        {
        err = output->Value().AsTInt32();
        if ( err == KErrNone )
            {
            output = outparam->FindFirst( pos1,_L8("ReturnValue"));
            if(output)
                {
                TPtrC uidval = (TPtrC)(output->Value().AsDes());
                local = GetEntry( inparam, outparam, uidval, KKCalFileName11);    
                }
            else
                err = -1;
            }
        }
   // TBuf<10> localuid1;
   // localuid1.Num(TInt64(local));
    
    inparam->Reset();
    outparam->Reset();
    
    TLiwGenericParam dsNameParam(KContentType, TLiwVariant(_L("CalendarEntry")));
    inparam->AppendL(dsNameParam);
    
    CLiwDefaultMap *filterMap = CLiwDefaultMap::NewL();
    TLiwGenericParam filterParam(KFilter, TLiwVariant(filterMap));
    inparam->AppendL(filterParam);
    filterMap->DecRef();

    filterMap->InsertL(KCalendarName,TLiwVariant(_L("C:CalendarFileA")));
    filterMap->InsertL(_L8("LocalId"),TLiwVariant(local));

    TRAP(err,interface->ExecuteCmdL( _L8("GetList") ,*inparam ,*outparam));
    
    pos = 0 ;
    
    const TLiwGenericParam* finaloutput = outparam->FindFirst( pos,_L8("ReturnValue"));
    TInt count = 0;
    CLiwMap* map;
    TInt retvalue = KErrNone;
    if ( finaloutput )     
        {
        CLiwIterable* iterlist = finaloutput->Value().AsIterable();
        if(iterlist)
            {
            TLiwVariant data1;
            while(iterlist->NextL(data1) )
                {
                const CLiwMap* res = data1.AsMap();
                if ( res )
                    {
                    TLiwVariant data;
                    if(res->FindL(_L8("StartTime"), data))
                        {
                        TTime ostime(TDateTime(2007,EJuly,26,8,0,0,0));
                        TTime stime = data.AsTTime();
                        if( ostime != stime)
                            {
                            retvalue = KErrGeneral;
                            break;
                            }
                        }
                        
                    data.Reset();   
                    }
                }
            data1.Reset();  
            }
        }
    
    inparam->Reset();
    outparam->Reset();
    delete uidset1;
    RemoveProvCalendar(inparam, outparam, interface, KKCalFileName11);
    return retvalue;

    }
TInt CTestUpdateSync::UpdateAppointmentEntryWithNewTimeAndGlobalIdL()
    {
    iServiceHandler = CLiwServiceHandler::NewL();

    CLiwGenericParamList* inparam = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outparam = &(iServiceHandler->OutParamListL());


    TInt err; 
    RCriteriaArray interest;
    CleanupClosePushL(interest);
    
    CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KTestInterface,KTestContent);
    crit->SetServiceClass(TUid::Uid(KLiwClassBase));
    CleanupStack::PushL(crit);
    interest.AppendL(crit);    
    
    iServiceHandler->AttachL(interest);
    iServiceHandler->ExecuteServiceCmdL(*crit, *inparam, *outparam); 

    TInt pos = 0;

    outparam->FindFirst( pos, KTestInterface );
    if(pos != KErrNotFound)
        {
        interface = (*outparam)[pos].Value().AsInterface(); 
        }
    CleanupStack::PopAndDestroy(crit);
    CleanupStack::PopAndDestroy(&interest); 

    outparam->Reset();
    inparam->Reset();
    
    AddProvCalendar(inparam, outparam, interface, KKCalFileName11);
    TUIDSet* uidset1;
    TBuf<50> globaluid;
    TBuf<10> localuid;
    //AddProvAppointmentDailyRepeatAndAttendees(inparam, outparam, interface, KKCalFileName11 ,uidset1 );
    AddProvAppointmentDailyRepeat(inparam, outparam, interface, KKCalFileName11 ,uidset1);
    //localuid.Num(TInt64(uidset1->iLocalUID));
    globaluid.Copy(uidset1->iGlobalUID->Des());
    localuid = GetEntry( inparam, outparam, globaluid, KKCalFileName11);    
    CLiwDefaultMap* map1 = CLiwDefaultMap::NewL();
    CleanupStack::PushL(map1);

    TLiwVariant content(_L("CalendarEntry"));
    TLiwGenericParam element1;  
    element1.SetNameAndValueL(_L8("Type"),content);
    inparam->AppendL(element1);
    content.Reset();
    element1.Reset();


    map1->InsertL(_L8("CalendarName"), TLiwVariant(KKCalFileName11) ); 
    map1->InsertL(_L8("id"),TLiwVariant(globaluid));
    map1->InsertL(_L8("StartTime"), TLiwVariant(TTime(TDateTime(2007,EOctober,25,14,30,0,0))));
    map1->InsertL(_L8("EndTime"), TLiwVariant(TTime(TDateTime(2007,EOctober,25,15,30,0,0))));
    map1->InsertL(_L8("InstanceStartTime"), TLiwVariant(TTime(TDateTime(2007,EOctober,25,10,0,0,0))));
    
    TLiwGenericParam element;   
    element.SetNameAndValueL(_L8("Item"),TLiwVariant(map1));
    
    inparam->AppendL(element);
    element.Reset();
    map1->DecRef();
    CleanupStack::Pop(map1);

    TRAPD(err1, interface->ExecuteCmdL( KCmdAdd, *inparam,*outparam ));
    TInt pos1 = 0 ;
    
    const TLiwGenericParam* output = outparam->FindFirst( pos1,_L8("ErrorCode"));
    TBuf<10> local;
    if(output)
        {
        err = output->Value().AsTInt32();
        if ( err == KErrNone )
            {
            output = outparam->FindFirst( pos1,_L8("ReturnValue"));
            if(output)
                {
                TPtrC uidval = (TPtrC)(output->Value().AsDes());
                TBuf<50> uidg;
                uidg.Copy(uidval);
                local = GetEntry( inparam, outparam, uidg, KKCalFileName11);    
                }
            else
                err = -1;
            }
        }
    //TBuf<10> localuid1;
    //localuid1.Num(TInt64(local));
    
    inparam->Reset();
    outparam->Reset();
    
    TLiwGenericParam dsNameParam(KContentType, TLiwVariant(_L("CalendarEntry")));
    inparam->AppendL(dsNameParam);
    
    CLiwDefaultMap *filterMap = CLiwDefaultMap::NewL();
    TLiwGenericParam filterParam(KFilter, TLiwVariant(filterMap));
    inparam->AppendL(filterParam);
    filterMap->DecRef();

    filterMap->InsertL(KCalendarName,TLiwVariant(_L("C:CalendarFileA")));
    filterMap->InsertL(_L8("LocalId"),TLiwVariant(local));

    TRAP(err,interface->ExecuteCmdL( _L8("GetList") ,*inparam ,*outparam));
    
    pos = 0 ;
    
    const TLiwGenericParam* finaloutput = outparam->FindFirst( pos,_L8("ReturnValue"));
    TInt count = 0;
    CLiwMap* map;
    TInt retvalue = KErrNone;
    if ( finaloutput )     
        {
        CLiwIterable* iterlist = finaloutput->Value().AsIterable();
        if(iterlist)
            {
            TLiwVariant data1;
            while(iterlist->NextL(data1) )
                {
                const CLiwMap* res = data1.AsMap();
                if ( res )
                    {
                    TLiwVariant data;
                    if(res->FindL(_L8("StartTime"), data))
                        {
                        TTime ostime(TDateTime(2007,EOctober,25,14,30,0,0));
                        TTime stime = data.AsTTime();
                        if( ostime != stime)
                            {
                            retvalue = KErrGeneral;
                            break;
                            }
                        }

                    if(res->FindL(_L8("EndTime"), data))
                        {
                        TTime ostime(TDateTime(2007,EOctober,25,15,30,0,0));
                        TTime stime = data.AsTTime();
                        if( ostime != stime)
                            {
                            retvalue = KErrGeneral;
                            break;
                            }
                        }

                    data.Reset();   
                    }
                }
            data1.Reset();  
            }
        }
    
    inparam->Reset();
    outparam->Reset();
    delete uidset1;
    RemoveProvCalendar(inparam, outparam, interface, KKCalFileName11);
    return retvalue;
    }


TDesC& CTestUpdateSync::GetEntry(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, TPtrC globaluid, const TDesC& calname)
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
			      		result.Zero();
						const CLiwMap* res = data1.AsMap();
						if ( res )
							{
							TLiwVariant data;
							if(res->FindL(_L8("LocalId"), data))
								result.Copy( data.AsDes() );
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


// -----------------------------------------------------------------------------
// CTCalendarUpdateTest::ICALImportAsync
// Test Method to test the ICALImportAsync(ASynchronous)
// Functionality of CalenderService
// -----------------------------------------------------------------------------
//



	

