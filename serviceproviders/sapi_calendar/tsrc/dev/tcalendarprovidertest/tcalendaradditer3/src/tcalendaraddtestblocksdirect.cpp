/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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


#include<LiwCommon.h>
#include<LiwVariant.h>
#include<LiwServiceHandler.h>
#include "tcalendaraddtest.h"
#include "calendarheader.h"
#include "calendarconstants.h"

_LIT8(KTestInterface, 	"IDataSource");
_LIT8(KTestContent,		"Service.Calendar");
_LIT8(KCmd,				"Delete");
_LIT8(KMessageId,				"MessageId");
_LIT8(KMap,				"NotificationType");
_LIT8(KMessageList,			"MessageList" );
_LIT8(KMessage,				"Message" );
_LIT(KMsgType,"NewMessage");
//_LIT8(KContentType, 		"Type");
//_LIT8(KCalendarName,        "CalendarName");
//_LIT8(KFilter, 				"Filter");

_LIT(KCalFileName1,"C:Calendar");

TInt AddProvAppointmentDailyRepeatAndAttendees(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset);
TInt AddProvAppointmentWeeklyRepeat(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset);
void GetLocalUid( const TDesC& aLocalUid, TCalLocalUid& aOutLocalUid );
void GetGlobalUid( const TDesC& aGlobalUid, TDes8& aOutGlobalUid );
TInt AddProvAppointmentMonthlyRepeat(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset);
TInt AddProvAppointmentDailyRepeat(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset);
TInt RemoveProvCalendar(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar);
TInt AddProvToDo(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset);	
TInt AddProvCalendar(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar);
enum TFormat
	{
	ETestUnicode = 0x01,
	ETestAscii	 = 0x02,
	};

HBufC* FillBuffer(int size, TFormat encoding)
	{
	HBufC* buffer = NULL;
	if( encoding == ETestUnicode)
		{
		buffer = HBufC::NewL(size);
		for(int i=0;i<size;i++)
			buffer->Des().Append(0xE0FF); //append some unicode character	
		}
	else if(encoding == ETestAscii)
		{
		buffer = HBufC::NewL(size);
		for(int i=0;i<size;i++)
			buffer->Des().Append(0xFF); //append some ascii character	
		}
	return buffer;
	}

class CTestSync : public CBase
{
public:
	static CTestSync* NewL();
	int TestFunc();
	int TestFuncMonthly();
	void GetInterfaceHandle(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam);
	int UpdateRepeatRule();
	int UpdateInstanceWithRepeat();
	int UpdateEntryWithRepeatAndExceptionDates();
	int AddEntryWithVeryLongDescription();
	TDesC& GetEntry(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, TPtrC localuid, const TDesC& calname );
	CTestSync();
	~CTestSync();

private:
	void ConstructL();

	
	
private:	
	CLiwServiceHandler* 	iServiceHandler;
	TInt 					iResult;
	MLiwInterface* 			interface ;	
};		


CTestSync* CTestSync::NewL()
	{
	CTestSync* self = new (ELeave) CTestSync();
	self->ConstructL();
	return self;
	}

CTestSync::~CTestSync()
	{
	if( interface )
	interface->Close();
	
	delete iServiceHandler;
	}


void CTestSync::ConstructL()
	{
	}


CTestSync::CTestSync()
	{
	interface = NULL ;
	}

int CTestSync::TestFunc()
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
					if(res->FindL(_L8("Type"), data))
						{
						TPtrC type = data.AsDes();
						if(type.CompareF(_L("Meeting")) != 0 )
							{
						    retvalue = KErrGeneral;
							break;
							}
						}
					if(res->FindL(_L8("StartTime"), data))
						{
						TTime ostime(TDateTime(2007,EOctober,23,10,0,0,0));
						TTime stime = data.AsTTime();
						if( ostime != stime)
							{
						    retvalue = KErrGeneral;
							break;
							}
						}
					if(res->FindL(_L8("EndTime"), data))
						{
						TTime oetime(TDateTime(2007,EOctober,23,10,30,0,0));
						TTime etime = data.AsTTime();
						if( oetime != etime)
							{
						    retvalue = KErrGeneral;
							break;
							}
						}
					if(res->FindL(_L8("Replication"), data))
						{
						TPtrC rep = data.AsDes();
						if(rep.CompareF(_L("Open")) != 0 )
							{
						    retvalue = KErrGeneral;
							break;
							}
						}
					if(res->FindL(_L8("Description"), data))
						{
						TPtrC rep = data.AsDes();
						if(rep.CompareF(_L("Meeting")) != 0 )
							{
						    retvalue = KErrGeneral;
							break;
							}
						}
					if(res->FindL(_L8("Status"), data))
						{
						TPtrC rep = data.AsDes();
						if(rep.CompareF(_L("Confirmed")) != 0 )
							{
						    retvalue = KErrGeneral;
							break;
							}
						}
					if(res->FindL(_L8("Method"), data))
						{
						TPtrC rep = data.AsDes();
						if(rep.CompareF(_L("None")) != 0 )
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
						if(map->FindL(_L8("StartDate"), rdata))
							{
							TTime sdate = rdata.AsTTime();
							TTime ostime(TDateTime(2007,EOctober,23,10,0,0,0));
							if( sdate != ostime)
								{
							    retvalue = KErrGeneral;
							    rdata.Reset();
								break;
								}
							}
						if(map->FindL(_L8("UntilDate"), rdata))
							{
							TTime udate = rdata.AsTTime();
							//TTime outime(TDateTime(2007,EOctober,30,10,0,0,0));
							TTime outime(TDateTime(2007,ENovember,27,10,0,0,0));
							if( udate != outime )
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

int CTestSync::TestFuncMonthly()
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
					if(res->FindL(_L8("StartTime"), data))
						{
						TTime ostime(TDateTime(2007,EOctober,23,10,0,0,0));
						TTime stime = data.AsTTime();
						if( ostime != stime)
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
						if(map->FindL(_L8("StartDate"), rdata))
							{
							TTime sdate = rdata.AsTTime();
							TTime ostime(TDateTime(2007,EOctober,23,10,0,0,0));
							if( sdate != ostime)
								{
							    retvalue = KErrGeneral;
							    rdata.Reset();
								break;
								}
							}
						if(map->FindL(_L8("UntilDate"), rdata))
							{
							TTime udate = rdata.AsTTime();
							//TTime outime(TDateTime(2007,EOctober,30,10,0,0,0));
							TTime outime(TDateTime(2007,EDecember,23,10,0,0,0));
							if( udate != outime )
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

int AddEntryWithAllAttributes()
	{
	__UHEAP_MARK;
	CTestSync* test = CTestSync::NewL();
    int res =  test->TestFunc();
	delete test;
	__UHEAP_MARKEND;
	return res;
	
	}

int UpdateEntryWithRDates()
	{
	__UHEAP_MARK;
	CTestSync* test = CTestSync::NewL();
    int res =  test->UpdateEntryWithRepeatAndExceptionDates();
	delete test;
	__UHEAP_MARKEND;
	return res;
	
	}
		
int AddMonthlyRepeatingEntry()
	{
	__UHEAP_MARK;
	CTestSync* test = CTestSync::NewL();
    int res =  test->TestFuncMonthly();
	delete test;
	__UHEAP_MARKEND;
	return res;
	
	}
	
int ModifyRepeatRule()
	{
	__UHEAP_MARK;
	CTestSync* test = CTestSync::NewL();
    int res =  test->UpdateRepeatRule();
	delete test;
	__UHEAP_MARKEND;
	return res;
	
	}
int UpdateApptInstanceWithRepeat()
	{
	__UHEAP_MARK;
	CTestSync* test = CTestSync::NewL();
    int res =  test->UpdateInstanceWithRepeat();
	delete test;
	__UHEAP_MARKEND;
	return res;
	
	}
int TestForLongStrings()
	{
	__UHEAP_MARK;
	CTestSync* test = CTestSync::NewL();
    int res =  test->AddEntryWithVeryLongDescription();
	delete test;
	__UHEAP_MARKEND;
	return res;
	
	}	
	
/*int CTestSync::TestFunc()
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
    TBuf<10> localuid;
    //AddProvAppointmentDailyRepeatAndAttendees(inparam, outparam, interface, KCalFileName1 ,uidset1 );
    AddProvAppointmentWeeklyRepeat(inparam, outparam, interface, KCalFileName1 ,uidset1);
    localuid.Num(TInt64(uidset1->iLocalUID));
    
    TLiwGenericParam dsNameParam(KContentType, TLiwVariant(_L("CalendarEntry")));
	inparam->AppendL(dsNameParam);
	
	CLiwDefaultMap *filterMap = CLiwDefaultMap::NewL();
	TLiwGenericParam filterParam(KFilter, TLiwVariant(filterMap));
	inparam->AppendL(filterParam);
	filterMap->DecRef();

    filterMap->InsertL(KCalendarName,TLiwVariant(_L("C:CalendarFileA")));
    filterMap->InsertL(_L8("LocalUid"),TLiwVariant(localuid));

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
					if(res->FindL(_L8("Type"), data))
						{
						TPtrC type = data.AsDes();
						if(type.CompareF(_L("Meeting")) != 0 )
							{
						    retvalue = KErrGeneral;
							break;
							}
						}
					if(res->FindL(_L8("StartTime"), data))
						{
						TTime ostime(TDateTime(2007,EOctober,23,10,0,0,0));
						TTime stime = data.AsTTime();
						if( ostime != stime)
							{
						    retvalue = KErrGeneral;
							break;
							}
						}
					if(res->FindL(_L8("EndTime"), data))
						{
						TTime oetime(TDateTime(2007,EOctober,23,10,30,0,0));
						TTime etime = data.AsTTime();
						if( oetime != etime)
							{
						    retvalue = KErrGeneral;
							break;
							}
						}
					if(res->FindL(_L8("Replication"), data))
						{
						TPtrC rep = data.AsDes();
						if(rep.CompareF(_L("Open")) != 0 )
							{
						    retvalue = KErrGeneral;
							break;
							}
						}
					if(res->FindL(_L8("Description"), data))
						{
						TPtrC rep = data.AsDes();
						if(rep.CompareF(_L("Meeting")) != 0 )
							{
						    retvalue = KErrGeneral;
							break;
							}
						}
					if(res->FindL(_L8("Status"), data))
						{
						TPtrC rep = data.AsDes();
						if(rep.CompareF(_L("Confirmed")) != 0 )
							{
						    retvalue = KErrGeneral;
							break;
							}
						}
					if(res->FindL(_L8("Method"), data))
						{
						TPtrC rep = data.AsDes();
						if(rep.CompareF(_L("None")) != 0 )
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
							if( add.CompareF(_L("")) != 0 )
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
						if(rep.CompareF(_L("")) != 0 )
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
									if( address.CompareF(_L("")) != 0 )
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
						if(map->FindL(_L8("StartDate"), rdata))
							{
							TTime sdate = rdata.AsTTime();
							TTime ostime(TDateTime(2007,EOctober,23,10,0,0,0));
							if( sdate != ostime)
								{
							    retvalue = KErrGeneral;
							    rdata.Reset();
								break;
								}
							}
						if(map->FindL(_L8("UntilDate"), rdata))
							{
							TTime udate = rdata.AsTTime();
							//TTime outime(TDateTime(2007,EOctober,30,10,0,0,0));
							TTime outime(TDateTime(2007,ENovember,27,10,0,0,0));
							if( udate != outime )
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
	}*/

void CTestSync::GetInterfaceHandle(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam)
	{


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

	}
	
int CTestSync::UpdateRepeatRule()
	{
	iServiceHandler = CLiwServiceHandler::NewL();

	CLiwGenericParamList* inparam = &(iServiceHandler->InParamListL());
	CLiwGenericParamList* outparam = &(iServiceHandler->OutParamListL());

	GetInterfaceHandle(inparam, outparam);
	TUIDSet* uidset1;
    TBuf<50> globaluid;
    TBuf<10> localuid;
	AddProvAppointmentDailyRepeat(inparam, outparam, interface, KCalFileName1 ,uidset1);	
	//localuid.Num(TInt64(uidset1->iLocalUID));
	globaluid.Copy(uidset1->iGlobalUID->Des());

	delete uidset1;
    //update repeat from daily to weekly
   	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);
    localuid = GetEntry(inparam, outparam, globaluid, KCalFileName1);
    TLiwVariant content(_L("CalendarEntry"));
	TLiwGenericParam element1;	
	element1.SetNameAndValueL(_L8("Type"),content);
	inparam->AppendL(element1);
	content.Reset();
	element1.Reset();

   	CLiwDefaultMap* repeatmap = CLiwDefaultMap::NewL();
	CleanupStack::PushL(repeatmap);
	repeatmap->InsertL(_L8("Type"), TLiwVariant(TInt32(2)));
	repeatmap->InsertL(_L8("UntilDate"), TLiwVariant(TTime(TDateTime(2007,EDecember,30,10,0,0,0))));
	map->InsertL(_L8("RepeatRule"), TLiwVariant(repeatmap));
	CleanupStack::Pop(repeatmap);
	repeatmap->DecRef();
	
	map->InsertL(_L8("LocalId"), TLiwVariant(localuid));
    
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
		err = output->Value().AsTInt32();
	
	//update from weekly to monthly
	if( err == KErrNone )
		{
		inparam->Reset();
		outparam->Reset();
		
	   	CLiwDefaultMap* map1 = CLiwDefaultMap::NewL();
		CleanupStack::PushL(map1);

	    TLiwVariant content(_L("CalendarEntry"));
		TLiwGenericParam element1;	
		element1.SetNameAndValueL(_L8("Type"),content);
		inparam->AppendL(element1);
		content.Reset();
		element1.Reset();

	    map1->InsertL(_L8("LocalId"),TLiwVariant(localuid));
		
	   	CLiwDefaultMap* repeatmap = CLiwDefaultMap::NewL();
		CleanupStack::PushL(repeatmap);
		repeatmap->InsertL(_L8("Type"), TLiwVariant(TInt32(3)));
		repeatmap->InsertL(_L8("StartDate"), TLiwVariant(TTime(TDateTime(2007,EJanuary,30,10,0,0,0))));
		repeatmap->InsertL(_L8("UntilDate"), TLiwVariant(TTime(TDateTime(2009,EJanuary,30,10,0,0,0))));
		
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
		TRAP(err, interface->ExecuteCmdL( KCmdAdd, *inparam,*outparam ));
	    TInt pos1 = 0 ;
		const TLiwGenericParam* output = outparam->FindFirst( pos1,_L8("ErrorCode"));
		if(output)
			err = output->Value().AsTInt32();
		inparam->Reset();
		outparam->Reset();

		}
    return err;
	}
	
int CTestSync::UpdateInstanceWithRepeat()
	{
	iServiceHandler = CLiwServiceHandler::NewL();

	CLiwGenericParamList* inparam = &(iServiceHandler->InParamListL());
	CLiwGenericParamList* outparam = &(iServiceHandler->OutParamListL());

	GetInterfaceHandle(inparam, outparam);
	TUIDSet* uidset1;
    TBuf<10> localuid;
    TBuf<50> globaluid;
	AddProvAppointmentDailyRepeat(inparam, outparam, interface, KCalFileName1 ,uidset1);	
	//localuid.Num(TInt64(uidset1->iLocalUID));
	globaluid.Copy(uidset1->iGlobalUID->Des());
    localuid = GetEntry( inparam, outparam, globaluid, KCalFileName1);
	delete uidset1;
    //update repeat from daily to weekly
   	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

    TLiwVariant content(_L("CalendarEntry"));
	TLiwGenericParam element1;	
	element1.SetNameAndValueL(_L8("Type"),content);
	inparam->AppendL(element1);
	content.Reset();
	element1.Reset();

   	CLiwDefaultMap* repeatmap = CLiwDefaultMap::NewL();
	CleanupStack::PushL(repeatmap);
	repeatmap->InsertL(_L8("Type"), TLiwVariant(TInt32(2)));
	repeatmap->InsertL(_L8("UntilDate"), TLiwVariant(TTime(TDateTime(2007,EDecember,30,10,0,0,0))));
	map->InsertL(_L8("RepeatRule"), TLiwVariant(repeatmap));
	CleanupStack::Pop(repeatmap);
	repeatmap->DecRef();
	
	map->InsertL(_L8("LocalUid"), TLiwVariant(localuid));
	map->InsertL(_L8("InstanceStartTime"), TLiwVariant(TTime(TDateTime(2007,EDecember,30,10,0,0,0))));
	map->InsertL(_L8("CalendarName"), TLiwVariant(_L("C:Calendar")));
	
    
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
		err = output->Value().AsTInt32();
	
	//update from weekly to monthly
	if( err == KErrNone )
		{
		inparam->Reset();
		outparam->Reset();
		
	   	CLiwDefaultMap* map1 = CLiwDefaultMap::NewL();
		CleanupStack::PushL(map1);

	    TLiwVariant content(_L("CalendarEntry"));
		TLiwGenericParam element1;	
		element1.SetNameAndValueL(_L8("Type"),content);
		inparam->AppendL(element1);
		content.Reset();
		element1.Reset();

	    map1->InsertL(_L8("LocalId"),TLiwVariant(localuid));
		
	   	CLiwDefaultMap* repeatmap = CLiwDefaultMap::NewL();
		CleanupStack::PushL(repeatmap);
		repeatmap->InsertL(_L8("Type"), TLiwVariant(TInt32(3)));
		repeatmap->InsertL(_L8("StartDate"), TLiwVariant(TTime(TDateTime(2007,EJanuary,30,10,0,0,0))));
		repeatmap->InsertL(_L8("UntilDate"), TLiwVariant(TTime(TDateTime(2009,EJanuary,30,10,0,0,0))));
		
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
		if(output)
			err = output->Value().AsTInt32();
		inparam->Reset();
		outparam->Reset();

		}
    return err;
	}

int CTestSync::UpdateEntryWithRepeatAndExceptionDates()
	{
	iServiceHandler = CLiwServiceHandler::NewL();

	CLiwGenericParamList* inparam = &(iServiceHandler->InParamListL());
	CLiwGenericParamList* outparam = &(iServiceHandler->OutParamListL());

	GetInterfaceHandle(inparam, outparam);
	TUIDSet* uidset1;
    TBuf<10> localuid;
    TBuf<50> globaluid;
	AddProvToDo(inparam, outparam, interface, KCalFileName1 ,uidset1);	
	//localuid.Num(TInt64(uidset1->iLocalUID));
	globaluid.Copy(uidset1->iGlobalUID->Des());
    localuid = GetEntry( inparam, outparam, globaluid, KCalFileName1);
	delete uidset1;
    //update repeat from daily to weekly
   	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

    TLiwVariant content(_L("CalendarEntry"));
	TLiwGenericParam element1;	
	element1.SetNameAndValueL(_L8("Type"),content);
	inparam->AppendL(element1);
	content.Reset();
	element1.Reset();

    CLiwDefaultList* repeatdts = CLiwDefaultList::NewL(); 
    CleanupStack::PushL(repeatdts); 
    repeatdts->AppendL(TLiwVariant(TTime(TDateTime(2007,EDecember,30,10,0,0,0))));
    repeatdts->AppendL(TLiwVariant(TTime(TDateTime(2007,EDecember,30,10,0,0,0))));
    repeatdts->AppendL(TLiwVariant(TTime(TDateTime(2007,EDecember,30,10,0,0,0))));
    repeatdts->AppendL(TLiwVariant(TTime(TDateTime(2007,EDecember,30,10,0,0,0))));
	map->InsertL(_L8("RepeatDates"), TLiwVariant(repeatdts));
	CleanupStack::Pop(repeatdts);
	repeatdts->DecRef();

     
   	CLiwDefaultMap* repeatmap = CLiwDefaultMap::NewL();
	CleanupStack::PushL(repeatmap);
	repeatmap->InsertL(_L8("Type"), TLiwVariant(TInt32(2)));
	repeatmap->InsertL(_L8("UntilDate"), TLiwVariant(TTime(TDateTime(2007,EDecember,30,10,0,0,0))));
	map->InsertL(_L8("RepeatRule"), TLiwVariant(repeatmap));
	CleanupStack::Pop(repeatmap);
	repeatmap->DecRef();
	
	map->InsertL(_L8("LocalId"), TLiwVariant(localuid));
    
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
		err = output->Value().AsTInt32();
	
	//update from weekly to monthly
	if( err == KErrNone )
		{
		inparam->Reset();
		outparam->Reset();
		
	   	CLiwDefaultMap* map1 = CLiwDefaultMap::NewL();
		CleanupStack::PushL(map1);

	    TLiwVariant content(_L("CalendarEntry"));
		TLiwGenericParam element1;	
		element1.SetNameAndValueL(_L8("Type"),content);
		inparam->AppendL(element1);
		content.Reset();
		element1.Reset();

	    map1->InsertL(_L8("LocalUid"),TLiwVariant(localuid));
		
	   	CLiwDefaultMap* repeatmap = CLiwDefaultMap::NewL();
		CleanupStack::PushL(repeatmap);
		repeatmap->InsertL(_L8("Type"), TLiwVariant(TInt32(3)));
		repeatmap->InsertL(_L8("StartDate"), TLiwVariant(TTime(TDateTime(2007,EJanuary,30,10,0,0,0))));
		repeatmap->InsertL(_L8("UntilDate"), TLiwVariant(TTime(TDateTime(2009,EJanuary,30,10,0,0,0))));
		
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
		if(output)
			err = output->Value().AsTInt32();
		inparam->Reset();
		outparam->Reset();

		}
    return err;
	}

int CTestSync::AddEntryWithVeryLongDescription()
	{
	iServiceHandler = CLiwServiceHandler::NewL();

	CLiwGenericParamList* inparam = &(iServiceHandler->InParamListL());
	CLiwGenericParamList* outparam = &(iServiceHandler->OutParamListL());

	GetInterfaceHandle(inparam, outparam);
	
   	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

    TLiwVariant content(_L("CalendarEntry"));
	TLiwGenericParam element1;	
	element1.SetNameAndValueL(_L8("Type"),content);
	inparam->AppendL(element1);
	content.Reset();
	element1.Reset();


	map->InsertL(_L8("Type"), TLiwVariant( KEntryTodo ));
	map->InsertL(_L8("EndTime"), TLiwVariant(TTime(TDateTime(2007,EAugust,20,0,0,0,0))));
	map->InsertL(_L8("Replication"), TLiwVariant(_L("Open")));
	HBufC* description = FillBuffer(1000, ETestUnicode);
	map->InsertL(_L8("Description"), TLiwVariant(description->Des()));
	delete description;
	description = NULL;
	//map->InsertL(_L8("Method"), TLiwVariant(_L("None")));
	
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

	}

TDesC& CTestSync::GetEntry(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, TPtrC globaluid, const TDesC& calname)
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
