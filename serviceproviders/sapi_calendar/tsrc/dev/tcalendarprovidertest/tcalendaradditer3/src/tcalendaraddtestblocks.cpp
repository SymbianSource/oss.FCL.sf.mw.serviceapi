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
#include <StifTestInterface.h>
#include<liwcommon.h>
#include<liwvariant.h>
#include<liwservicehandler.h>
#include "tcalendaraddtest.h"
#include "calendarheader.h"
#include "calendarconstants.h"
TInt doAddTest();
_LIT8(KTestInterface, 	"IDataSource");
_LIT8(KTestContent,		"Service.Calendar");
_LIT(KCalFileName1,"C:CalendarFileA");
_LIT(KCalFileName2,"C:CalendarFile1");

TInt AddProvAppointmentDailyRepeatAndAttendees(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset);
TInt AddProvCalendar(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar);
TInt RemoveProvCalendar(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar);
TInt AddProvToDo(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset);
TInt AddProvDayEvent(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset);
TInt AddProvAppointmentDailyRepeat(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset);
TInt AddProvAppointmentWeeklyRepeat(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset);
TInt AddProvAppointmentMonthlyRepeat(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset);
TInt AddProvAnni(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset);
TInt AddProvReminder(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset);
TInt AddNewCalendar();
class CTestAddSync : public CBase
{
public:
	static CTestAddSync* NewL();
	int AddNewCalendar();
	int AddNewApptWithDailyRepeat();
	int AddNewApptWithWeeklyRepeat();
	int AddNewApptWithMonthlyRepeat();
	int AddNewApptWithAttendees();
	int AddNewAnniversary();
	int AddNewReminder();
	int AddNewDayEvent();
	int AddNewTodo();
	int AddInvalidCalendar(TPtrC calname);
	
	CTestAddSync();
	~CTestAddSync();

private:
	void ConstructL();

	
	
private:	
	CLiwServiceHandler* 	iServiceHandler;
	TInt 					iResult;
	MLiwInterface* 			interface ;	
};		


CTestAddSync* CTestAddSync::NewL()
	{
	CTestAddSync* self = new (ELeave) CTestAddSync();
	self->ConstructL();
	return self;
	}

CTestAddSync::~CTestAddSync()
	{
	if( interface )
	interface->Close();
	
	delete iServiceHandler;
	}


void CTestAddSync::ConstructL()
	{
	}


CTestAddSync::CTestAddSync()
	{
	interface = NULL ;
	}
	

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTCalendarAddTest::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CTCalendarAddTest::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CTChangeStatusTest::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTCalendarAddTest::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        //TRY( "SendMessage",    CTDeleteMessageTest::SendMessage ),
        
        ENTRY( "AddCalendarIter3",    	 CTCalendarAddTest::AddNewCalendar ),
        ENTRY( "AddAppointmentWithDailyRepeat",    CTCalendarAddTest::AddApptWithDailyRepeat),
        ENTRY( "AddAppointmentWithWeeklyRepeat",    CTCalendarAddTest::AddApptWithWeeklyRepeat),
        ENTRY( "AddAppointmentWithMonthlyRepeat",    CTCalendarAddTest::AddApptWithMonthlyRepeat),
        ENTRY( "AddAppointmentWithAttendees",    CTCalendarAddTest::AddApptWithAttendees),
        ENTRY( "AddAnniversary",    CTCalendarAddTest::AddNewAnniversary),
        ENTRY( "AddDayEvent",    CTCalendarAddTest::AddNewDayEvent),
        ENTRY( "AddReminder",    CTCalendarAddTest::AddNewReminder),
        ENTRY( "AddTodo",    CTCalendarAddTest::AddNewTodo),
        ENTRY( "AddAllAttributes",    CTCalendarAddTest::AddAll),
        ENTRY( "ModifyRepeat",    CTCalendarAddTest::ModifyRepeat),
        ENTRY( "AddMonthlyRepeatingEntry",    CTCalendarAddTest::AddEntryWithMonthlyRpt),
        ENTRY( "AddCalendarNegative", CTCalendarAddTest::InterfaceClassL ),
        ENTRY( "AddCalendarInZDrive", CTCalendarAddTest::InterfaceClassL ),
        ENTRY( "AddCalendarWithFullPath", CTCalendarAddTest::InterfaceClassL ),
        ENTRY( "AddCalendarWithInvalidPath", CTCalendarAddTest::InterfaceClassL ),
        ENTRY( "UpdateInstanceWithRepeat", CTCalendarAddTest::UpdateInstanceWithRepeat ),
        ENTRY( "UpdateEntryWithRepeatDates", CTCalendarAddTest::UpdateEntryWithRepeatDates ),
        ENTRY( "TestForLongStringsInEntry", CTCalendarAddTest::TestForLongStringsInEntry ),
	    };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

TInt CTCalendarAddTest::InterfaceClassL( CStifItemParser& aItem )
    {
    struct ParamPass* arg1 = new ParamPass();
    arg1->it = &aItem;
    TPtrC calname;
    int res = 0;
    int errorcode = 0;
    if( arg1->it->GetNextString ( calname ) != KErrNone )
	    {
	    return KErrGeneral;
	    }
	_LIT(KNull,"NULL");
	_LIT(KCalNameLong,"C:shfwhfhjeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeekkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnlllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllllll");
	if( 0 == calname.CompareF(KNull) )
		calname.Set(KCalNameLong);
	__UHEAP_MARK;
	CTestAddSync* test = CTestAddSync::NewL();
	res = test->AddInvalidCalendar( calname );
    delete test;
	__UHEAP_MARKEND;
	
    if( arg1->it->GetNextInt ( errorcode ) != KErrNone )
    {
    return KErrGeneral;
    }
    if( errorcode == res )
    	res = KErrNone;
	return res;

    }

	
// -----------------------------------------------------------------------------
// CTCalendarAddTest::Import
// Test Method to test the Import(Synchronous)
// Functionality of CalenderService
// -----------------------------------------------------------------------------
//
TInt  CTCalendarAddTest::AddNewCalendar(CStifItemParser& /*aItem*/)
	{
	//__UHEAP_MARK;
	
	TInt result=KErrNone;
	
	result = doAddTest();
	
	
//	__UHEAP_MARKEND;
	return result;
    }
TInt  CTCalendarAddTest::AddApptWithDailyRepeat(CStifItemParser& /*aItem*/)
	{
	//__UHEAP_MARK;
	
	TInt result=KErrNone;
	
	__UHEAP_MARK;
	CTestAddSync* test = CTestAddSync::NewL();
    int res =  test->AddNewApptWithDailyRepeat();
	delete test;
	__UHEAP_MARKEND;
	return res;
	
	
//	__UHEAP_MARKEND;
	//return result;
    }
TInt  CTCalendarAddTest::AddApptWithWeeklyRepeat(CStifItemParser& /*aItem*/)
	{
	//__UHEAP_MARK;
	
	TInt result=KErrNone;
	
	__UHEAP_MARK;
	CTestAddSync* test = CTestAddSync::NewL();
    int res =  test->AddNewApptWithWeeklyRepeat();
	delete test;
	__UHEAP_MARKEND;
	return res;
	
	
//	__UHEAP_MARKEND;
//	return result;
    }
TInt  CTCalendarAddTest::AddApptWithMonthlyRepeat(CStifItemParser& /*aItem*/)
	{
	//__UHEAP_MARK;
	
	TInt result=KErrNone;
	
	__UHEAP_MARK;
	CTestAddSync* test = CTestAddSync::NewL();
    int res =  test->AddNewApptWithMonthlyRepeat();
	delete test;
	__UHEAP_MARKEND;
	return res;
	
	
//	__UHEAP_MARKEND;
//	return result;
    }
TInt  CTCalendarAddTest::AddApptWithAttendees(CStifItemParser& /*aItem*/)
	{
	//__UHEAP_MARK;
	
	TInt result=KErrNone;
	
	__UHEAP_MARK;
	CTestAddSync* test = CTestAddSync::NewL();
    int res =  test->AddNewApptWithAttendees();
	delete test;
	__UHEAP_MARKEND;
	return res;
	
	
//	__UHEAP_MARKEND;
//	return result;
    }    
TInt  CTCalendarAddTest::AddNewAnniversary(CStifItemParser& /*aItem*/)
	{
	//__UHEAP_MARK;
	
	TInt result=KErrNone;
	
	__UHEAP_MARK;
	CTestAddSync* test = CTestAddSync::NewL();
    int res =  test->AddNewAnniversary();
	delete test;
	__UHEAP_MARKEND;
	return res;
	
	
//	__UHEAP_MARKEND;
//	return result;
    }  
TInt  CTCalendarAddTest::AddNewDayEvent(CStifItemParser& /*aItem*/)
	{
	//__UHEAP_MARK;
	
	TInt result=KErrNone;
	
	__UHEAP_MARK;
	CTestAddSync* test = CTestAddSync::NewL();
    int res =  test->AddNewDayEvent();
	delete test;
	__UHEAP_MARKEND;
	return res;
	
	
//	__UHEAP_MARKEND;
//	return result;
    } 
TInt  CTCalendarAddTest::AddNewReminder(CStifItemParser& /*aItem*/)
	{
	//__UHEAP_MARK;
	
	TInt result=KErrNone;
	
	__UHEAP_MARK;
	CTestAddSync* test = CTestAddSync::NewL();
    int res =  test->AddNewReminder();
	delete test;
	__UHEAP_MARKEND;
	return res;
	
	
//	__UHEAP_MARKEND;
//	return result;
    }  
TInt  CTCalendarAddTest::AddNewTodo(CStifItemParser& /*aItem*/)
	{
	//__UHEAP_MARK;
	
	TInt result=KErrNone;
	
	__UHEAP_MARK;
	CTestAddSync* test = CTestAddSync::NewL();
    int res =  test->AddNewTodo();
	delete test;
	__UHEAP_MARKEND;
	return res;
	
	
//	__UHEAP_MARKEND;
//	return result;
    }      

TInt  CTCalendarAddTest::AddAll(CStifItemParser& aItem)
	{
    __UHEAP_MARK;
	
	TInt result=KErrNone;
	
	result = AddEntryWithAllAttributes();
	
	
	__UHEAP_MARKEND;
	return result;
    }

TInt  CTCalendarAddTest::ModifyRepeat(CStifItemParser& aItem)
	{
    __UHEAP_MARK;
	
	TInt result=KErrNone;
	
	result = ModifyRepeatRule();
	
	
	__UHEAP_MARKEND;
	return result;
    }
TInt  CTCalendarAddTest::UpdateInstanceWithRepeat(CStifItemParser& aItem)
	{
    __UHEAP_MARK;
	
	TInt result=KErrNone;
	
	result = UpdateApptInstanceWithRepeat();
	if( result = 1000 )
		result = KErrNone;
	__UHEAP_MARKEND;
	return result;
    }
    
    
TInt  CTCalendarAddTest::UpdateEntryWithRepeatDates(CStifItemParser& aItem)
	{
    __UHEAP_MARK;
	
	TInt result=KErrNone;
	
	result = UpdateEntryWithRDates();
	if( result = 1000 )
		result = KErrNone;
	__UHEAP_MARKEND;
	return result;
    }

TInt  CTCalendarAddTest::AddEntryWithMonthlyRpt(CStifItemParser& aItem)
	{
    __UHEAP_MARK;
	
	TInt result=KErrNone;
	
	result = AddMonthlyRepeatingEntry();
	
	
	__UHEAP_MARKEND;
	return result;
    }


TInt  CTCalendarAddTest::TestForLongStringsInEntry(CStifItemParser& aItem)
	{
    __UHEAP_MARK;
	
	TInt result=KErrNone;
	
	result = TestForLongStrings();
	
	
	__UHEAP_MARKEND;
	return result;
    }

 
 TInt CTestAddSync::AddInvalidCalendar( TPtrC calname) //cbinding stuff
	{
	iServiceHandler = CLiwServiceHandler::NewL();

	CLiwGenericParamList* inparam = &(iServiceHandler->InParamListL());
	CLiwGenericParamList* outparam = &(iServiceHandler->OutParamListL());


	TInt err  =0; 
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
	
	AddProvCalendar(inparam, outparam, interface, calname);
    pos = 0 ;
    
    const TLiwGenericParam* output = outparam->FindFirst( pos,_L8("ErrorCode"));
	
	if(output)
		{
		err = output->Value().AsTInt32();
		}
	
	inparam->Reset();
	outparam->Reset();   
	return err;
	}

// -----------------------------------------------------------------------------
// CTCalendarAddTest::ImportAsync
// Test Method to test the ImportAsync(ASynchronous)
// Functionality of CalenderService
// -----------------------------------------------------------------------------
//

// -----------------------------------------------------------------------------
// CTCalendarAddTest::ICALImport
// Test Method to test the ICALImport(Synchronous)
// Functionality of CalenderService
// -----------------------------------------------------------------------------
//


// -----------------------------------------------------------------------------
// CTCalendarAddTest::ICALImportAsync
// Test Method to test the ICALImportAsync(ASynchronous)
// Functionality of CalenderService
// -----------------------------------------------------------------------------
//


TInt CTestAddSync::AddNewAnniversary()
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
	
	AddProvCalendar(inparam, outparam, interface, KCalFileName1);
	TUIDSet* uidset1;
    TBuf<50> globaluid;
    AddProvAnni(inparam, outparam, interface, KCalFileName1 ,uidset1);
    //localuid.Num(TInt64(uidset1->iLocalUID));
    globaluid.Copy(uidset1->iGlobalUID->Des());
    
    TLiwGenericParam dsNameParam(KContentType, TLiwVariant(_L("CalendarEntry")));
	inparam->AppendL(dsNameParam);
	
	CLiwDefaultMap *filterMap = CLiwDefaultMap::NewL();
	TLiwGenericParam filterParam(KFilter, TLiwVariant(filterMap));
	inparam->AppendL(filterParam);
	filterMap->DecRef();

    filterMap->InsertL(KCalendarName,TLiwVariant(_L("C:CalendarFileA")));
    filterMap->InsertL(_L8("id"),TLiwVariant(globaluid));

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
					if(res->FindL(_L8("Description"), data))
						{
						TPtrC rep = data.AsDes();
						if(rep.CompareF(_L("Anniversary")) != 0 )
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
    RemoveProvCalendar(inparam, outparam, interface, KCalFileName1);
    return retvalue;
	
	}
	
TInt CTestAddSync::AddNewDayEvent()
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
	
	AddProvCalendar(inparam, outparam, interface, KCalFileName1);
	TUIDSet* uidset1;
    TBuf<50> globaluid;
    AddProvDayEvent(inparam, outparam, interface, KCalFileName1 ,uidset1);
    //localuid.Num(TInt64(uidset1->iLocalUID));
    globaluid.Copy(uidset1->iGlobalUID->Des());

    TLiwGenericParam dsNameParam(KContentType, TLiwVariant(_L("CalendarEntry")));
	inparam->AppendL(dsNameParam);
	
	CLiwDefaultMap *filterMap = CLiwDefaultMap::NewL();
	TLiwGenericParam filterParam(KFilter, TLiwVariant(filterMap));
	inparam->AppendL(filterParam);
	filterMap->DecRef();

    filterMap->InsertL(KCalendarName,TLiwVariant(_L("C:CalendarFileA")));
    filterMap->InsertL(_L8("id"),TLiwVariant(globaluid));

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
					if(res->FindL(_L8("Description"), data))
						{
						TPtrC rep = data.AsDes();
						if(rep.CompareF(_L("New Event entry created")) != 0 )
							{
						    retvalue = KErrGeneral;
							break;
							}
						}

					if(res->FindL(_L8("RepeatRule"), data))
						{
						const CLiwMap* map = data.AsMap();
						TLiwVariant rdata;
						if(map->FindL(_L8("Type"), rdata))
							{
							TInt type = rdata.AsTInt32();
							if( type != 1 )
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
    RemoveProvCalendar(inparam, outparam, interface, KCalFileName1);
    return retvalue;
	
	}
		
TInt CTestAddSync::AddNewReminder()
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
	
	AddProvCalendar(inparam, outparam, interface, KCalFileName1);
	TUIDSet* uidset1;
    TBuf<50> globaluid;
    AddProvReminder(inparam, outparam, interface, KCalFileName1 ,uidset1);
    //localuid.Num(TInt64(uidset1->iLocalUID));
    globaluid.Copy(uidset1->iGlobalUID->Des());

    TLiwGenericParam dsNameParam(KContentType, TLiwVariant(_L("CalendarEntry")));
	inparam->AppendL(dsNameParam);
	
	CLiwDefaultMap *filterMap = CLiwDefaultMap::NewL();
	TLiwGenericParam filterParam(KFilter, TLiwVariant(filterMap));
	inparam->AppendL(filterParam);
	filterMap->DecRef();

    filterMap->InsertL(KCalendarName,TLiwVariant(_L("C:CalendarFileA")));
    filterMap->InsertL(_L8("id"),TLiwVariant(globaluid));

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
					if(res->FindL(_L8("Description"), data))
						{
						TPtrC rep = data.AsDes();
						if(rep.CompareF(_L("New Reminder entry created")) != 0 )
							{
						    retvalue = KErrGeneral;
							break;
							}
						}

					if(res->FindL(_L8("RepeatRule"), data))
						{
						const CLiwMap* map = data.AsMap();
						TLiwVariant rdata;
						if(map->FindL(_L8("Type"), rdata))
							{
							TInt type = rdata.AsTInt32();
							if( type != 1 )
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
    RemoveProvCalendar(inparam, outparam, interface, KCalFileName1);
    return retvalue;
	
	}

TInt CTestAddSync::AddNewTodo()
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
	
	AddProvCalendar(inparam, outparam, interface, KCalFileName1);
	TUIDSet* uidset1;
    TBuf<50> globaluid;
    AddProvToDo(inparam, outparam, interface, KCalFileName1 ,uidset1);
    //localuid.Num(TInt64(uidset1->iLocalUID));
    globaluid.Copy(uidset1->iGlobalUID->Des());
   
    
    TLiwGenericParam dsNameParam(KContentType, TLiwVariant(_L("CalendarEntry")));
	inparam->AppendL(dsNameParam);
	
	CLiwDefaultMap *filterMap = CLiwDefaultMap::NewL();
	TLiwGenericParam filterParam(KFilter, TLiwVariant(filterMap));
	inparam->AppendL(filterParam);
	filterMap->DecRef();

    filterMap->InsertL(KCalendarName,TLiwVariant(_L("C:CalendarFileA")));
    filterMap->InsertL(_L8("id"),TLiwVariant(globaluid));

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
					if(res->FindL(_L8("Description"), data))
						{
						TPtrC rep = data.AsDes();
						if(rep.CompareF(_L("New todo entry created")) != 0 )
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
    RemoveProvCalendar(inparam, outparam, interface, KCalFileName1);
    return retvalue;
	
	}


int doAddTest()
	{
	__UHEAP_MARK;
	CTestAddSync* test = CTestAddSync::NewL();
    int res =  test->AddNewCalendar();
	delete test;
	__UHEAP_MARKEND;
	return res;
	
	}

TInt CTestAddSync::AddNewCalendar() //cbinding stuff
	{
	iServiceHandler = CLiwServiceHandler::NewL();

	CLiwGenericParamList* inparam = &(iServiceHandler->InParamListL());
	CLiwGenericParamList* outparam = &(iServiceHandler->OutParamListL());


	TInt err  =0; 
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
	
	err = AddProvCalendar(inparam, outparam, interface, KCalFileName2);
    /*pos = 0 ;
    
    const TLiwGenericParam* output = outparam->FindFirst( pos,_L8("ErrorCode"));
	
	if(output)
		{
		err = output->Value().AsTInt32();
		}
	
	inparam->Reset();
	outparam->Reset();*/
    int ret = KErrGeneral;
    if( err == KErrNone )
	    {
	    TLiwGenericParam dsNameParam(KContentType, TLiwVariant(_L("Calendar")));
		inparam->AppendL(dsNameParam);
		
		TInt err = 0;
		TRAP(err,interface->ExecuteCmdL( _L8("GetList") ,*inparam ,*outparam));
	    
	    pos = 0 ;
	    
	    const TLiwGenericParam* finaloutput = outparam->FindFirst( pos,_L8("ReturnValue"));
	    TInt count = 0;
	    CLiwMap* map;

		if ( finaloutput )     
			{
			CLiwIterable* iterlist = finaloutput->Value().AsIterable();

	      	if(iterlist)
	      		{
			    TLiwVariant data;
	      		while(iterlist->NextL(data) )
		      		{
		      		TPtrC cal = data.AsDes();
		      		if(cal.CompareF(_L("C:CalendarFile1")) == 0)
			      		{
			      		ret = KErrNone;
			      		break;	
			      		}
   	            	count++;	
		      		}
	      		data.Reset();  
	      		}
			}
	    
		inparam->Reset();
		outparam->Reset();
	    RemoveProvCalendar(inparam, outparam, interface, KCalFileName2);
	    }
    return ret;
	}
	
	
TInt  CTestAddSync::AddNewApptWithDailyRepeat()
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
	
	AddProvCalendar(inparam, outparam, interface, KCalFileName1);
	TUIDSet* uidset1;
    TBuf<50> globaluid;
    AddProvAppointmentDailyRepeat(inparam, outparam, interface, KCalFileName1 ,uidset1);
    //localuid.Num(TInt64(uidset1->iLocalUID));
    globaluid.Copy(uidset1->iGlobalUID->Des());
    
    TLiwGenericParam dsNameParam(KContentType, TLiwVariant(_L("CalendarEntry")));
	inparam->AppendL(dsNameParam);
	
	CLiwDefaultMap *filterMap = CLiwDefaultMap::NewL();
	TLiwGenericParam filterParam(KFilter, TLiwVariant(filterMap));
	inparam->AppendL(filterParam);
	filterMap->DecRef();

    filterMap->InsertL(KCalendarName,TLiwVariant(_L("C:CalendarFileA")));
    filterMap->InsertL(_L8("id"),TLiwVariant(globaluid));

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
					if(res->FindL(_L8("Description"), data))
						{
						TPtrC rep = data.AsDes();
						if(rep.CompareF(_L("Meeting")) != 0 )
							{
						    retvalue = KErrGeneral;
							break;
							}
						}

					if(res->FindL(_L8("RepeatRule"), data))
						{
						const CLiwMap* map = data.AsMap();
						TLiwVariant rdata;
						if(map->FindL(_L8("Type"), rdata))
							{
							TInt type = rdata.AsTInt32();
							if( type != 1 )
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
    RemoveProvCalendar(inparam, outparam, interface, KCalFileName1);
    return retvalue;
	
    }
TInt CTestAddSync::AddNewApptWithWeeklyRepeat()
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
	
	AddProvCalendar(inparam, outparam, interface, KCalFileName1);
	TUIDSet* uidset1;
    TBuf<50> globaluid;
    //AddProvAppointmentDailyRepeatAndAttendees(inparam, outparam, interface, KCalFileName1 ,uidset1 );
    AddProvAppointmentWeeklyRepeat(inparam, outparam, interface, KCalFileName1 ,uidset1);
    //localuid.Num(TInt64(uidset1->iLocalUID));
    globaluid.Copy(uidset1->iGlobalUID->Des());

    TLiwGenericParam dsNameParam(KContentType, TLiwVariant(_L("CalendarEntry")));
	inparam->AppendL(dsNameParam);
	
	CLiwDefaultMap *filterMap = CLiwDefaultMap::NewL();
	TLiwGenericParam filterParam(KFilter, TLiwVariant(filterMap));
	inparam->AppendL(filterParam);
	filterMap->DecRef();

    filterMap->InsertL(KCalendarName,TLiwVariant(_L("C:CalendarFileA")));
    filterMap->InsertL(_L8("LocalUid"),TLiwVariant(globaluid));

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
					if(res->FindL(_L8("Description"), data))
						{
						TPtrC rep = data.AsDes();
						if(rep.CompareF(_L("Meeting")) != 0 )
							{
						    retvalue = KErrGeneral;
							break;
							}
						}


					if(res->FindL(_L8("RepeatRule"), data))
						{
						const CLiwMap* map = data.AsMap();
						TLiwVariant rdata;
						if(map->FindL(_L8("Type"), rdata))
							{
							TInt type = rdata.AsTInt32();
							if( type != 2 )
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
    RemoveProvCalendar(inparam, outparam, interface, KCalFileName1);
    return retvalue;		
	}
TInt CTestAddSync::AddNewApptWithMonthlyRepeat()
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
	
	AddProvCalendar(inparam, outparam, interface, KCalFileName1);
	TUIDSet* uidset1;
    TBuf<50> globaluid;
    //AddProvAppointmentDailyRepeatAndAttendees(inparam, outparam, interface, KCalFileName1 ,uidset1 );
    AddProvAppointmentMonthlyRepeat(inparam, outparam, interface, KCalFileName1 ,uidset1);
    //localuid.Num(TInt64(uidset1->iLocalUID));
    globaluid.Copy(uidset1->iGlobalUID->Des());

    TLiwGenericParam dsNameParam(KContentType, TLiwVariant(_L("CalendarEntry")));
	inparam->AppendL(dsNameParam);
	
	CLiwDefaultMap *filterMap = CLiwDefaultMap::NewL();
	TLiwGenericParam filterParam(KFilter, TLiwVariant(filterMap));
	inparam->AppendL(filterParam);
	filterMap->DecRef();

    filterMap->InsertL(KCalendarName,TLiwVariant(_L("C:CalendarFileA")));
    filterMap->InsertL(_L8("id"),TLiwVariant(globaluid));

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
					if(res->FindL(_L8("Description"), data))
						{
						TPtrC rep = data.AsDes();
						if(rep.CompareF(_L("Meeting")) != 0 )
							{
						    retvalue = KErrGeneral;
							break;
							}
						}


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
    RemoveProvCalendar(inparam, outparam, interface, KCalFileName1);
    return retvalue;		
	
	}
	
TInt CTestAddSync::AddNewApptWithAttendees()
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
	
	AddProvCalendar(inparam, outparam, interface, KCalFileName1);
	TUIDSet* uidset1;
    TBuf<50> globaluid;
    AddProvAppointmentDailyRepeatAndAttendees(inparam, outparam, interface, KCalFileName1 ,uidset1 );
    //localuid.Num(TInt64(uidset1->iLocalUID));
    globaluid.Copy(uidset1->iGlobalUID->Des());
    TLiwGenericParam dsNameParam(KContentType, TLiwVariant(_L("CalendarEntry")));
	inparam->AppendL(dsNameParam);
	
	CLiwDefaultMap *filterMap = CLiwDefaultMap::NewL();
	TLiwGenericParam filterParam(KFilter, TLiwVariant(filterMap));
	inparam->AppendL(filterParam);
	filterMap->DecRef();

    filterMap->InsertL(KCalendarName,TLiwVariant(_L("C:CalendarFileA")));
    filterMap->InsertL(_L8("id"),TLiwVariant(globaluid));

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
					if(res->FindL(_L8("Description"), data))
						{
						TPtrC rep = data.AsDes();
						if(rep.CompareF(_L("Meeting")) != 0 )
							{
						    retvalue = KErrGeneral;
							break;
							}
						}
						
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
    RemoveProvCalendar(inparam, outparam, interface, KCalFileName1);
    return retvalue;		
	}	
