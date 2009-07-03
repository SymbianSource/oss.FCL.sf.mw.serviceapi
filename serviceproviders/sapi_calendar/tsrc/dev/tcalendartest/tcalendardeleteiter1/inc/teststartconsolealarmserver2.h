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

#ifndef ALARMSERVERTEST_H
#define ALARMSERVERTEST_H
#include "startconsolealarmserver.h"

#include <calalarm.h>
#include <caluser.h>
#include<LiwCommon.h>
#include<LiwVariant.h>
#include<LiwServiceHandler.h>

#include "calendarconstants.h"
#include "calendarheader.h"
#include "EntryAttributes.h"
#include "calendarservice.h"

extern void GetGlobalUid( const TDesC& aGlobalUid, TDes8& aOutGlobalUid );
extern void GetLocalUid( const TDesC& aLocalUid, TCalLocalUid& aOutLocalUid );
TInt RemoveProvCalendar(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar)
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

void GetLocalUid( const TDesC& aLocalUid, TCalLocalUid& aOutLocalUid )
	{
	aOutLocalUid = 0;
	if( aLocalUid.Length() )
		{
		TInt sepPos = aLocalUid.Locate( TChar(KUidSeparator ));
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
	if( aGlobalUid.Length() )
		{
		/*TInt sepPos = aGlobalUid.Locate( TChar(KUidSeparator ));

		if( sepPos == KErrNotFound )
			{
			aOutGlobalUid.Copy( aGlobalUid.Mid(0) );
			}
		else
			{
			aOutGlobalUid.Copy( aGlobalUid.Mid( sepPos + 1 ) );
			}*/
		aOutGlobalUid.Copy(	aGlobalUid );
		}
	}
	
TInt AddProvAppointmentDailyRepeat(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset)
	{
	inparam->Reset();
	outparam->Reset();
	
   	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

    TLiwVariant content(_L("CalendarEntry"));
	TLiwGenericParam element1;	
	element1.SetNameAndValueL(_L8("Type"),content);
	inparam->AppendL(element1);
	content.Reset();
	element1.Reset();


    map->InsertL(_L8("CalendarName"), TLiwVariant(aCalendar) ); 
	map->InsertL(_L8("Type"), TLiwVariant( KEntryAppt ));
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

	TRAPD(err, interface->ExecuteCmdL( KCmdAdd, *inparam,*outparam ));
    TInt pos = 0 ;
    
    const TLiwGenericParam* output = outparam->FindFirst( pos,_L8("ErrorCode"));
	
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

				/*TLiwVariant luid;
				if(res->FindL(_L8("LocalUid"), luid))
					{
					localuid = luid.AsTUint();
					}
				else
					err = -1;
				TLiwVariant guid;
				if(res->FindL(_L8("GlobalUid"), guid))
					{
					globaluid = guid.AsData().AllocL();
					}
				else
					err = -1;
				
				luid.Reset();
				guid.Reset();	*/

				}
			else
				err = -1;
			}
		}
	
	inparam->Reset();
	outparam->Reset();
	return err;
	};
	
TInt AddProvAppointmentWeeklyRepeat(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset)
	{
	inparam->Reset();
	outparam->Reset();
	
   	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

    TLiwVariant content(_L("CalendarEntry"));
	TLiwGenericParam element1;	
	element1.SetNameAndValueL(_L8("Type"),content);
	inparam->AppendL(element1);
	content.Reset();
	element1.Reset();


  	map->InsertL(_L8("CalendarName"), TLiwVariant(aCalendar) ); 
	map->InsertL(_L8("Type"), TLiwVariant( KEntryAppt ));
	map->InsertL(_L8("StartTime"), TLiwVariant(TTime(TDateTime(2007,EOctober,23,10,0,0,0))));
	map->InsertL(_L8("EndTime"), TLiwVariant(TTime(TDateTime(2007,EOctober,23,10,30,0,0))));
	map->InsertL(_L8("Replication"), TLiwVariant(_L("Open")));
	map->InsertL(_L8("Description"), TLiwVariant(_L("Meeting")));
	map->InsertL(_L8("Status"), TLiwVariant(_L("Confirmed")));
	map->InsertL(_L8("Method"), TLiwVariant(_L("None")));
	
   	CLiwDefaultMap* repeatmap = CLiwDefaultMap::NewL();
	CleanupStack::PushL(repeatmap);
	repeatmap->InsertL(_L8("Type"), TLiwVariant(TInt32(2)));
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

	TRAPD(err, interface->ExecuteCmdL( KCmdAdd, *inparam,*outparam ));
    TInt pos = 0 ;
    
    const TLiwGenericParam* output = outparam->FindFirst( pos,_L8("ErrorCode"));
	
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

				/*TLiwVariant luid;
				if(res->FindL(_L8("LocalUid"), luid))
					{
					localuid = luid.AsTUint();
					}
				else
					err = -1;
				TLiwVariant guid;
				if(res->FindL(_L8("GlobalUid"), guid))
					{
					globaluid = guid.AsData().AllocL();
					}
				else
					err = -1;
				
				luid.Reset();
				guid.Reset();	*/

				}
			else
				err = -1;
			}
		}
	
	inparam->Reset();
	outparam->Reset();
	return err;
	};
TInt AddProvAppointmentMonthlyRepeat(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset)
	{
	inparam->Reset();
	outparam->Reset();
	
   	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

    TLiwVariant content(_L("CalendarEntry"));
	TLiwGenericParam element1;	
	element1.SetNameAndValueL(_L8("Type"),content);
	inparam->AppendL(element1);
	content.Reset();
	element1.Reset();


    map->InsertL(_L8("CalendarName"), TLiwVariant(aCalendar) ); 
	map->InsertL(_L8("Type"), TLiwVariant( KEntryAppt ));
	map->InsertL(_L8("StartTime"), TLiwVariant(TTime(TDateTime(2007,EOctober,23,10,0,0,0))));
	map->InsertL(_L8("EndTime"), TLiwVariant(TTime(TDateTime(2007,EOctober,23,10,30,0,0))));
	map->InsertL(_L8("Replication"), TLiwVariant(_L("Open")));
	map->InsertL(_L8("Description"), TLiwVariant(_L("Meeting")));
	map->InsertL(_L8("Status"), TLiwVariant(_L("Confirmed")));
	map->InsertL(_L8("Method"), TLiwVariant(_L("None")));
	
   	CLiwDefaultMap* repeatmap = CLiwDefaultMap::NewL();
	CleanupStack::PushL(repeatmap);
	repeatmap->InsertL(_L8("Type"), TLiwVariant(TInt32(3)));
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

	map->InsertL(_L8("RepeatRule"), TLiwVariant(repeatmap));
	CleanupStack::Pop(repeatmap);
	repeatmap->DecRef();

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

				/*TLiwVariant luid;
				if(res->FindL(_L8("LocalUid"), luid))
					{
					localuid = luid.AsTUint();
					}
				else
					err = -1;
				TLiwVariant guid;
				if(res->FindL(_L8("GlobalUid"), guid))
					{
					globaluid = guid.AsData().AllocL();
					}
				else
					err = -1;
				
				luid.Reset();
				guid.Reset();	*/

				}
			else
				err = -1;
			}
		}
	
	inparam->Reset();
	outparam->Reset();
	return err;
	};

TInt AddProvAppointmentWithoutRepeat(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset)
	{
	inparam->Reset();
	outparam->Reset();
	
   	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

    TLiwVariant content(_L("CalendarEntry"));
	TLiwGenericParam element1;	
	element1.SetNameAndValueL(_L8("Type"),content);
	inparam->AppendL(element1);
	content.Reset();
	element1.Reset();


  map->InsertL(_L8("CalendarName"), TLiwVariant(aCalendar) ); 
	map->InsertL(_L8("Type"), TLiwVariant( KEntryAppt ));
	map->InsertL(_L8("StartTime"), TLiwVariant(TTime(TDateTime(2007,EOctober,3,10,0,0,0))));
	map->InsertL(_L8("EndTime"), TLiwVariant(TTime(TDateTime(2007,EOctober,3,10,30,0,0))));
	map->InsertL(_L8("Replication"), TLiwVariant(_L("Open")));
	map->InsertL(_L8("Description"), TLiwVariant(_L("Meeting")));
	map->InsertL(_L8("Status"), TLiwVariant(_L("Confirmed")));
	map->InsertL(_L8("Method"), TLiwVariant(_L("None")));

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

				/*TLiwVariant luid;
				if(res->FindL(_L8("LocalUid"), luid))
					{
					localuid = luid.AsTUint();
					}
				else
					err = -1;
				TLiwVariant guid;
				if(res->FindL(_L8("GlobalUid"), guid))
					{
					globaluid = guid.AsData().AllocL();
					}
				else
					err = -1;
				
				luid.Reset();
				guid.Reset();	*/

				}
			else
				err = -1;
			}
		}
	
	inparam->Reset();
	outparam->Reset();
	return err;
	};

TInt AddProvToDo(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset)
	{
	inparam->Reset();
	outparam->Reset();

	
   	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

    TLiwVariant content(_L("CalendarEntry"));
	TLiwGenericParam element1;	
	element1.SetNameAndValueL(_L8("Type"),content);
	inparam->AppendL(element1);
	content.Reset();
	element1.Reset();


    map->InsertL(_L8("CalendarName"), TLiwVariant(aCalendar) ); 
	map->InsertL(_L8("Type"), TLiwVariant( KEntryTodo ));
	map->InsertL(_L8("EndTime"), TLiwVariant(TTime(TDateTime(2007,EAugust,20,0,0,0,0))));
	map->InsertL(_L8("Replication"), TLiwVariant(_L("Open")));
	map->InsertL(_L8("Description"), TLiwVariant(_L("New todo entry created")));
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

			/*	TLiwVariant luid;
				if(res->FindL(_L8("LocalUid"), luid))
					{
					localuid = luid.AsTUint();
					}
				else
					err = -1;
				TLiwVariant guid;
				if(res->FindL(_L8("GlobalUid"), guid))
					{
					globaluid = guid.AsData().AllocL();
					}
				else
					err = -1;
				
				luid.Reset();
				guid.Reset();*/	
				}
			else
				err = -1;
			}
		}
	
	inparam->Reset();
	outparam->Reset();


	return err;
	};
	
TInt AddProvAnni(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset)
	{
	inparam->Reset();
	outparam->Reset();

	
   	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

    TLiwVariant content(_L("CalendarEntry"));
	TLiwGenericParam element1;	
	element1.SetNameAndValueL(_L8("Type"),content);
	inparam->AppendL(element1);
	content.Reset();
	element1.Reset();


  map->InsertL(_L8("CalendarName"), TLiwVariant(aCalendar) ); 
	map->InsertL(_L8("Type"), TLiwVariant( KEntryAnniv ));
	map->InsertL(_L8("StartTime"), TLiwVariant(TTime(TDateTime(2007,EDecember,30,0,0,0,0))));
	map->InsertL(_L8("Replication"), TLiwVariant(_L("Open")));
	map->InsertL(_L8("Description"), TLiwVariant(_L("Anniversary")));
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
					TLiwVariant luid;
					if(res->FindL(_L8("LocalUid"), luid))
						{
						localuid = luid.AsTUint();
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
	
	inparam->Reset();
	outparam->Reset();

	return err;
	};
	
TInt AddProvDayEvent(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar,  TUIDSet*& uidset)
	{
	inparam->Reset();
	outparam->Reset();

	
   	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

    TLiwVariant content(_L("CalendarEntry"));
	TLiwGenericParam element1;	
	element1.SetNameAndValueL(_L8("Type"),content);
	inparam->AppendL(element1);
	content.Reset();
	element1.Reset();


  map->InsertL(_L8("CalendarName"), TLiwVariant(aCalendar) ); 
	map->InsertL(_L8("Type"), TLiwVariant( KEntryEvent ));
	map->InsertL(_L8("StartTime"), TLiwVariant(TTime(TDateTime(2007,EJuly,25,0,0,0,0))));
	map->InsertL(_L8("Replication"), TLiwVariant(_L("Open")));
	map->InsertL(_L8("Description"), TLiwVariant(_L("New Event entry created")));
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

			/*	const CLiwMap* res = output->Value().AsMap();
				if ( res )
					{

					TLiwVariant luid;
					if(res->FindL(_L8("LocalUid"), luid))
						{
						localuid = luid.AsTUint();
						}
					else
						err = -1;
					TLiwVariant guid;
					if(res->FindL(_L8("GlobalUid"), guid))
						{
						globaluid = guid.AsData().AllocL();
						}
					else
						err = -1;

					luid.Reset();
					guid.Reset();
					}
				else
					err = -1;	*/
				}
			else
				err = -1;
			}
		}
	
	inparam->Reset();
	outparam->Reset();

	return err;
	};
	
TInt AddProvReminder(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset)
	{
	inparam->Reset();
	outparam->Reset();
	
   	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

    TLiwVariant content(_L("CalendarEntry"));
	TLiwGenericParam element1;	
	element1.SetNameAndValueL(_L8("Type"),content);
	inparam->AppendL(element1);
	content.Reset();
	element1.Reset();


  map->InsertL(_L8("CalendarName"), TLiwVariant(aCalendar) ); 
	map->InsertL(_L8("Type"), TLiwVariant( KEntryReminder ));
	map->InsertL(_L8("StartTime"), TLiwVariant(TTime(TDateTime(2007,EJuly,22,10,30,0,0))));
	map->InsertL(_L8("Replication"), TLiwVariant(_L("Open")));
	map->InsertL(_L8("Description"), TLiwVariant(_L("New Reminder entry created")));
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

			/*	const CLiwMap* res = output->Value().AsMap();
				if ( res )
					{
					TLiwVariant luid;
					if(res->FindL(_L8("LocalUid"), luid))
						{
						localuid = luid.AsTUint();
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
	
	inparam->Reset();
	outparam->Reset();
	return err;
	};

TInt AddProvAppointmentDailyRepeatAndAttendees(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset)
	{
	inparam->Reset();
	outparam->Reset();
	
   	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

    TLiwVariant content(_L("CalendarEntry"));
	TLiwGenericParam element1;	
	element1.SetNameAndValueL(_L8("Type"),content);
	inparam->AppendL(element1);
	content.Reset();
	element1.Reset();


    map->InsertL(_L8("CalendarName"), TLiwVariant(aCalendar) ); 
	map->InsertL(_L8("Type"), TLiwVariant( KEntryAppt ));
	map->InsertL(_L8("StartTime"), TLiwVariant(TTime(TDateTime(2007,EOctober,23,10,0,0,0))));
	map->InsertL(_L8("EndTime"), TLiwVariant(TTime(TDateTime(2007,EOctober,23,10,30,0,0))));
	map->InsertL(_L8("Replication"), TLiwVariant(_L("Open")));
	map->InsertL(_L8("Description"), TLiwVariant(_L("Meeting")));
	map->InsertL(_L8("Status"), TLiwVariant(_L("Confirmed")));
	map->InsertL(_L8("Method"), TLiwVariant(_L("None")));
	
   	CLiwDefaultList* attlist = CLiwDefaultList::NewL();
	CleanupStack::PushL(attlist);

   	CLiwDefaultMap* attmap = CLiwDefaultMap::NewL();
	CleanupStack::PushL(attmap);
	attmap->InsertL(_L8("CommonName"), TLiwVariant(_L("sapi")));
	attmap->InsertL(_L8("Address"), TLiwVariant(_L("h2s@nokia.com")));
	attlist->AppendL( TLiwVariant(attmap));
	CleanupStack::Pop(attmap);
	attmap->DecRef();
	map->InsertL(_L8("Attendees"), TLiwVariant(attlist));
	map->InsertL(_L8("PhoneOwner"), TLiwVariant(_L("h2s@nokia.com")));
   	CLiwDefaultMap* orgmap = CLiwDefaultMap::NewL();
	CleanupStack::PushL(orgmap);
	orgmap->InsertL(_L8("CommonName"), TLiwVariant(_L("sapi")));
	orgmap->InsertL(_L8("Address"), TLiwVariant(_L("mdc@nokia.com")));
	map->InsertL(_L8("Organizer"), TLiwVariant(orgmap));
	CleanupStack::Pop(orgmap);
	orgmap->DecRef();

	CleanupStack::Pop(attlist);
	attlist->DecRef();
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

	TRAPD(err, interface->ExecuteCmdL( KCmdAdd, *inparam,*outparam ));
    TInt pos = 0 ;
    
    const TLiwGenericParam* output = outparam->FindFirst( pos,_L8("ErrorCode"));
	
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

				/*TLiwVariant luid;
				if(res->FindL(_L8("LocalUid"), luid))
					{
					localuid = luid.AsTUint();
					}
				else
					err = -1;
				TLiwVariant guid;
				if(res->FindL(_L8("GlobalUid"), guid))
					{
					globaluid = guid.AsData().AllocL();
					}
				else
					err = -1;
				
				luid.Reset();
				guid.Reset();	*/

				}
			else
				err = -1;
			}
		}
	
	inparam->Reset();
	outparam->Reset();
	return err;
	};
	
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

#endif