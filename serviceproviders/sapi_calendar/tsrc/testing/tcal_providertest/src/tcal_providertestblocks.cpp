/*
* Copyright (c) 2002 - 2007 Nokia Corporation and/or its subsidiary(-ies).
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
#include <StifTestInterface.h>
#include "tcal_providertest.h"
#include <liwcommon.h>
#include <liwvariant.h>
#include <liwservicehandler.h>
#include "calendarheader.h"
#include "calendarconstants.h"
#include <badesca.h>
#include "notify.h"
//#include <SendUiConsts.h>
#include "messaginginterface.h"
#include "sendmessage.h"
#include <f32file.h>
#include "messageheader.h"
#include "serviceerrno.h"

using namespace LIW;

// EXTERNAL DATA STRUCTURES
//extern  ?external_data;

// EXTERNAL FUNCTION PROTOTYPES
//extern ?external_function( ?arg_type,?arg_type );

// CONSTANTS
//const ?type ?constant_var = ?constant;

// MACROS
//#define ?macro ?macro_def

// LOCAL CONSTANTS AND MACROS
//const ?type ?constant_var = ?constant;
//#define ?macro_name ?macro_def

// MODULE DATA STRUCTURES
//enum ?declaration
//typedef ?declaration

// LOCAL FUNCTION PROTOTYPES
//?type ?function_name( ?arg_type, ?arg_type );

// FORWARD DECLARATIONS
//class ?FORWARD_CLASSNAME;

// ============================= LOCAL FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// ?function_name ?description.
// ?description
// Returns: ?value_1: ?description
//          ?value_n: ?description_line1
//                    ?description_line2
// -----------------------------------------------------------------------------
//
/*
?type ?function_name(
    ?arg_type arg,  // ?description
    ?arg_type arg)  // ?description
    {

    ?code  // ?comment

    // ?comment
    ?code
    }
*/


/*TInt RemoveProvCalendar(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar);
TInt AddProvCalendar(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar);
TInt AddProvAppointmentDailyRepeat(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset);
TInt AddProvEvent(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset);
TInt AddProvToDo(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset);
TInt AddAppointmentProvLocal(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset);

//void GetLocalUid( const TDesC& aLocalUid, TCalLocalUid& aOutLocalUid );
//TInt GetLocalUid( CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar,const TDesC& type, TCalLocalUid& aOutLocalUid );
TInt GetLocalUid( CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar,TCalLocalUid& aOutLocalUid );
void GetGlobalUid( const TDesC& aGlobalUid, TDes8& aOutGlobalUid );*/
TInt ReqNotification( TInt aChangeType, TBool aLocalUid );

TBuf<100> gid;
_LIT8(KIDataSource, "IDataSource");
_LIT8(KService, "Service.Calendar");
_LIT8(KMsgService, 		"Service.Messaging");
_LIT8(KMsgIDataSource,		"IMessaging");
_LIT8(KMsgSendCmd,				"Send");
_LIT8(KMsgDelete,				"Delete");
_LIT8(KErrCode,"ErrorCode");
_LIT8(KMsgGetListCmd,"GetList");
_LIT(KSearchTexttest                 ,"Meeting");
_LIT(KDefaultCalendar                ,"C:Calendar");
_LIT(KTestCal1File, "C:getlistcal1");
_LIT(KTestCalFile, "C:ccc");
_LIT(KTestCal2File, "C:getlistcal2");

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctcal_providertest::Delete
// Delete here all resources allocated and opened from test methods.
// Called from destructor.
// -----------------------------------------------------------------------------
//
void Ctcal_providertest::Delete()
    {

    }

// -----------------------------------------------------------------------------
// Ctcal_providertest::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt Ctcal_providertest::RunMethodL(
    CStifItemParser& aItem )
    {

    static TStifFunctionInfo const KFunctions[] =
        {
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function.
        ENTRY( "Calendar_ops1", Ctcal_providertest::Calendar_ops1 ),
        ENTRY( "Calendar_ops2", Ctcal_providertest::Calendar_ops2 ),
        ENTRY( "Calendar_ops3", Ctcal_providertest::Calendar_ops3 ),
        ENTRY( "Calendar_ops4", Ctcal_providertest::Calendar_ops4 ),
        ENTRY( "Calendar_ops5", Ctcal_providertest::Calendar_ops5 ),
        ENTRY( "Calendar_ops6", Ctcal_providertest::Calendar_ops6 ),
        ENTRY( "Calendar_ops7", Ctcal_providertest::Calendar_ops7 ),
        ENTRY( "Calendar_ops8", Ctcal_providertest::Calendar_ops8 ),
        ENTRY( "Calendar_ops9", Ctcal_providertest::Calendar_ops9 ),
        ENTRY( "Calendar_ops10", Ctcal_providertest::Calendar_ops10 ),
        ENTRY( "Calendar_ops11", Ctcal_providertest::Calendar_ops11 ),
        ENTRY( "Calendar_ops12", Ctcal_providertest::Calendar_ops12 ),
        ENTRY( "Calendar_ops13", Ctcal_providertest::Calendar_ops13 ),
        ENTRY( "Calendar_ops14", Ctcal_providertest::Calendar_ops14 ),
        ENTRY( "Calendar_ops15", Ctcal_providertest::Calendar_ops15 ),
        ENTRY( "Calendar_ops16", Ctcal_providertest::Calendar_ops16 ),
        ENTRY( "Calendar_ops17", Ctcal_providertest::Calendar_ops17 ),

        ENTRY( "RemoveFile", Ctcal_providertest::RemoveFile ),
        //ADD NEW ENTRY HERE

        };

    const TInt count = sizeof( KFunctions ) /
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// Function to remove a file
TInt Ctcal_providertest::RemoveFile( CStifItemParser& aItem )
    {
		TPtrC16 file;
    	aItem.GetNextString(file);
  		RFile LogResult;
    	RFs LogResultSession;
    	User::LeaveIfError(LogResultSession.Connect());
    	if(LogResult.Open(LogResultSession ,file , EFileWrite | EFileShareAny )  != KErrNotFound)
        {
        	LogResult.Close();

			LogResultSession.Delete(file);

        	LogResultSession.Close();
        }

    	LogResult.Close();
    	LogResultSession.Close();
		return KErrNone;

    }


// -----------------------------------------------------------------------------
// Ctcal_providertest::Calendar_ops1
// Example test method function to combine Add/Update operations on calendar entries.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_providertest::Calendar_ops1( CStifItemParser& aItem )
    {

    	TInt32 result=KErrNone;
    TLiwGenericParam param;
	__UHEAP_MARK;

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

	iLog->Log(_L("interface created for calendar_ops1"));

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
			iLog->Log(_L("cal entries added for calendar_ops1"));

		   	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
			CleanupStack::PushL(map);

		    map->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal1File) );

		    gid.Copy( arruids[0]->iGlobalUID->Des() );
		    TInt lid_fetch_err = GetLocalUid(inParamList,outParamList,interface,KTestCal1File,arruids[0]->iLocalUID)	;
		    if(lid_fetch_err)
		    {
		    	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
				interface->Close();
				iServiceHandler->Reset();
				delete iServiceHandler;
				__UHEAP_MARKEND;
				return lid_fetch_err;
		    }

			TBuf<10> localuid;
			localuid.Num(TInt64(arruids[0]->iLocalUID));

		    map->InsertL(_L8("LocalId"),TLiwVariant(localuid));
		    map->InsertL(_L8("Summary"), TLiwVariant(_L("test")));


		    param.SetNameAndValueL(KContentType,TLiwVariant(_L("CalendarEntry")));
   			inParamList->AppendL(param);
   			param.Reset();

		    param.SetNameAndValueL(_L8("Item"),TLiwVariant(map));
   			inParamList->AppendL(param);
   			param.Reset();

			map->DecRef();
		    CleanupStack::Pop(map);

			interface->ExecuteCmdL( KCmdAdd, *inParamList ,*outParamList );
			pos=0;

			const TLiwGenericParam* update_err = outParamList->FindFirst(pos,KErrorCode);
   			if(update_err)
   			result = update_err->Value().AsTInt32();


			if(!result)
			{
				inParamList->Reset();
				outParamList->Reset();

				TLiwGenericParam dsNameParam(KContentType, TLiwVariant(_L("CalendarEntry")));
				inParamList->AppendL(dsNameParam);

				CLiwDefaultMap* map1 = CLiwDefaultMap::NewL();
				CleanupStack::PushL(map1);

		    	map1->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal1File) );
		    	map1->InsertL(_L8("LocalId"),TLiwVariant(localuid));

				TLiwVariant filterparam1(map1);
				TLiwGenericParam element2 ;
				element2.SetNameAndValueL(_L8("Filter"),filterparam1);
				filterparam1.Reset();

				inParamList->AppendL(element2);
				element2.Reset();

				map1->DecRef();
		    	CleanupStack::Pop(map1);

				interface->ExecuteCmdL( KCmdGetList ,*inParamList ,*outParamList);

		    	pos = 0 ;
		    	const TLiwGenericParam* getlist_err = outParamList->FindFirst(pos,KErrorCode);
   				if(getlist_err)
   				result = getlist_err->Value().AsTInt32();
   				pos=0;
		    	const TLiwGenericParam* output = outParamList->FindFirst( pos,_L8("ReturnValue"));
				TInt item_found = 0;

				if(!result && output )
				{
					CLiwIterable* iterlist = output->Value().AsIterable();

			    	TLiwVariant data;

		        	while( iterlist->NextL(data))
					{
						const CLiwMap* res = data.AsMap();
						if ( res )
						{
							TLiwVariant new_data;
							if(res->FindL(_L8("Summary"), new_data))
							{
								TPtrC loc = new_data.AsDes();
								TBuf<40> buf;
								buf.Copy(loc);
								iLog->Log(buf);
								iLog->Log(_L("found entry whose summary field is being examined"));

								if( loc.CompareF(_L("test")) != 0 )
								{
									result = KErrGeneral;
									new_data.Reset();
									break;
								}
								else
									iLog->Log(_L("summar is test"));

							}
							new_data.Reset();
						}
			  		}

			  		data.Reset();
				}
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


// -----------------------------------------------------------------------------
// Ctcal_providertest::Calendar_ops2
// Example test method function to combine import/export/Delete operations on calendar entries.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_providertest::Calendar_ops2( CStifItemParser& aItem )
    {

    	TInt32 result=KErrNone;

	__UHEAP_MARK;

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


	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal2File);

	AddProvCalendar(inParamList, outParamList, interface, KTestCal2File);


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
	TInt count = 0;

	if ( arruids.Count() > 0 )
		{
			CLiwDefaultMap* map = CLiwDefaultMap::NewL();
			CleanupStack::PushL(map);

		    map->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal1File) );

		    gid.Copy( arruids[0]->iGlobalUID->Des() );
		    TInt lid_fetch_err = GetLocalUid(inParamList,outParamList,interface,KTestCal1File,arruids[0]->iLocalUID)	;
		    if(lid_fetch_err)
		    {
		    	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
		    	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal2File);
				interface->Close();
				iServiceHandler->Reset();
				delete iServiceHandler;
				__UHEAP_MARKEND;
				return lid_fetch_err;
		    }

			TBuf<10> localuid;
			localuid.Num(TInt64(arruids[0]->iLocalUID));

		    map->InsertL(_L8("Format"), TLiwVariant(_L("VCal")) );
		    map->InsertL(_L8("FileName"), TLiwVariant(_L("c:\\exportall.txt")));

		    TLiwVariant content(_L("CalendarEntry"));
			TLiwGenericParam element1;
			element1.SetNameAndValueL(_L8("Type"),content);
			inParamList->AppendL(element1);
			content.Reset();
			element1.Reset();

		    TLiwVariant filterparam(map);
			TLiwGenericParam element ;
			element.SetNameAndValueL(_L8("Data"),filterparam);
			filterparam.Reset();

			inParamList->AppendL(element);
			element.Reset();
		    map->DecRef();
		    CleanupStack::Pop(map);

			interface->ExecuteCmdL( KCmdExport, *inParamList ,*outParamList );
			pos=0;
			const TLiwGenericParam* export_err = outParamList->FindFirst(pos,KErrorCode);
   			if(export_err)
   			result = export_err->Value().AsTInt32();

			if(!result)
			{
				inParamList->Reset();
				outParamList->Reset();

				// Do an Import.

				TLiwGenericParam dsNameParam(KContentType, TLiwVariant(_L("CalendarEntry")));
				inParamList->AppendL(dsNameParam);

				CLiwDefaultMap* map1 = CLiwDefaultMap::NewL();
				CleanupStack::PushL(map1);

		   		map1->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal2File) );
		    	map1->InsertL(_L8("Format"), TLiwVariant(_L("VCal")) );
				map1->InsertL(_L8("FileName"), TLiwVariant(_L("c:\\exportall.txt")));

				TLiwVariant filterparam1(map1);
				TLiwGenericParam element2 ;
				element2.SetNameAndValueL(_L8("Data"),filterparam1);
				filterparam1.Reset();

				inParamList->AppendL(element2);
				element2.Reset();

				map1->DecRef();
		    	CleanupStack::Pop(map1);

				interface->ExecuteCmdL( KCmdImport ,*inParamList ,*outParamList);
		    	pos = 0 ;
		    	const TLiwGenericParam* import_err = outParamList->FindFirst(pos,KErrorCode);
   				if(import_err)
   					result = import_err->Value().AsTInt32();

				if(!result)
				{
					inParamList->Reset();
					outParamList->Reset();

					TLiwGenericParam dsNameParam1(KContentType, TLiwVariant(_L("CalendarEntry")));
					inParamList->AppendL(dsNameParam1);

					CLiwDefaultMap* map2 = CLiwDefaultMap::NewL();
					CleanupStack::PushL(map2);

		    		map2->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal2File) );
		    		map2->InsertL(_L8("DeleteAll"), TLiwVariant(TBool(ETrue)) );

					TLiwVariant filterparam2(map2);
					TLiwGenericParam element3 ;
					element3.SetNameAndValueL(_L8("Data"),filterparam2);
					filterparam2.Reset();

					inParamList->AppendL(element3);
					element3.Reset();

					map2->DecRef();
		   			 CleanupStack::Pop(map2);

		    		interface->ExecuteCmdL( KCmdDelete ,*inParamList ,*outParamList);
		   			const TLiwGenericParam* delete_err = outParamList->FindFirst(pos,KErrorCode);
   					if(delete_err)
   						result = delete_err->Value().AsTInt32();

   					if(!result)
   					{
   						inParamList->Reset();
						outParamList->Reset();

						TLiwGenericParam dsNameParam2(KContentType, TLiwVariant(_L("CalendarEntry")));
						inParamList->AppendL(dsNameParam2);

						CLiwDefaultMap* map3 = CLiwDefaultMap::NewL();
						CleanupStack::PushL(map3);

		    			map3->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal2File) );
		    			map3->InsertL(_L8("LocalUid"),TLiwVariant(localuid));

						TLiwVariant filterparam3(map3);
						TLiwGenericParam element4 ;
						element4.SetNameAndValueL(_L8("Filter"),filterparam3);
						filterparam3.Reset();

						inParamList->AppendL(element4);
						element4.Reset();

						map3->DecRef();
		    			CleanupStack::Pop(map3);

						interface->ExecuteCmdL( KCmdGetList ,*inParamList ,*outParamList);
		    			pos = 0 ;
		    			const TLiwGenericParam* getlist_err = outParamList->FindFirst(pos,KErrorCode);
   						if(getlist_err)
   						result = getlist_err->Value().AsTInt32();
   						pos=0;
		    			const TLiwGenericParam* output = outParamList->FindFirst( pos,_L8("ReturnValue"));
						if(!result && output)
						{
							CLiwIterable* iterlist = output->Value().AsIterable();
			    			TLiwVariant data;
		        			while( iterlist->NextL(data))
							{
								count ++;
			  				}
			  				data.Reset();
						}
   					}
				}
			}

	    inParamList->Reset();
		outParamList->Reset();
	    arruids.ResetAndDestroy();
		}
	else
		result = KErrGeneral;

	if(!result && count != 0)
		result = KErrGeneral;
	else
		iLog->Log(_L("result pass in calendar_ops2"));

	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal2File);

	interface->Close();
	iServiceHandler->Reset();
	delete iServiceHandler;

    __UHEAP_MARKEND;

	return result;

    }

// -----------------------------------------------------------------------------
// Ctcal_providertest::Calendar_ops3
// Example test method function to combine import/export/Update operations on calendar entries.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_providertest::Calendar_ops3( CStifItemParser& aItem )
    {

    	TInt32 result=KErrNone;

	__UHEAP_MARK;

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


	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal2File);

	AddProvCalendar(inParamList, outParamList, interface, KTestCal2File);


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
	TInt count = 0;

	if ( arruids.Count() > 0 )
		{
			CLiwDefaultMap* map = CLiwDefaultMap::NewL();
			CleanupStack::PushL(map);
		    map->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal1File) );

		    gid.Copy( arruids[0]->iGlobalUID->Des() );
		    TInt lid_fetch_err = GetLocalUid(inParamList,outParamList,interface,KTestCal1File,arruids[0]->iLocalUID)	;
		    if(lid_fetch_err)
		    {
		    	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
		    	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal2File);
				interface->Close();
				iServiceHandler->Reset();
				delete iServiceHandler;
				__UHEAP_MARKEND;
				return lid_fetch_err;
		    }

			TBuf<10> localuid;
			localuid.Num(TInt64(arruids[0]->iLocalUID));

			TLiwVariant content(_L("CalendarEntry"));
			TLiwGenericParam element1;
			element1.SetNameAndValueL(_L8("Type"),content);
			inParamList->AppendL(element1);
			content.Reset();
			element1.Reset();

			map->InsertL(_L8("Format"), TLiwVariant(_L("VCal")) );
		    map->InsertL(_L8("FileName"), TLiwVariant(_L("c:\\exportall.txt")));

		    TLiwVariant filterparam(map);
			TLiwGenericParam element ;
			element.SetNameAndValueL(_L8("Data"),filterparam);
			filterparam.Reset();

			inParamList->AppendL(element);
			element.Reset();
		    map->DecRef();
		    CleanupStack::Pop(map);

			interface->ExecuteCmdL( KCmdExport, *inParamList ,*outParamList );
			pos = 0 ;
		    const TLiwGenericParam* export_err = outParamList->FindFirst(pos,KErrorCode);
   			if(export_err)
   				result = export_err->Value().AsTInt32();

   			if(!result)
   			{
   				inParamList->Reset();
				outParamList->Reset();

				// Do an Import.

				TLiwGenericParam dsNameParam(KContentType, TLiwVariant(_L("CalendarEntry")));
				inParamList->AppendL(dsNameParam);

				CLiwDefaultMap* map1 = CLiwDefaultMap::NewL();
				CleanupStack::PushL(map1);

		    	map1->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal2File) );
		    	map1->InsertL(_L8("Format"), TLiwVariant(_L("VCal")) );
				map1->InsertL(_L8("FileName"), TLiwVariant(_L("c:\\exportall.txt")));

				TLiwVariant filterparam1(map1);
				TLiwGenericParam element2 ;
				element2.SetNameAndValueL(_L8("Data"),filterparam1);
				filterparam1.Reset();

				inParamList->AppendL(element2);
				element2.Reset();

				map1->DecRef();
		    	CleanupStack::Pop(map1);

				interface->ExecuteCmdL( KCmdImport ,*inParamList ,*outParamList);
				pos=0;
				const TLiwGenericParam* import_err = outParamList->FindFirst(pos,KErrorCode);
   				if(import_err)
   					result = import_err->Value().AsTInt32();

   				if(!result)
   				{
   					inParamList->Reset();
					outParamList->Reset();

					TLiwGenericParam dsNameParam1(KContentType, TLiwVariant(_L("CalendarEntry")));
					inParamList->AppendL(dsNameParam1);

					CLiwDefaultMap* map2 = CLiwDefaultMap::NewL();
					CleanupStack::PushL(map2);

		    		map2->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal2File) );
		    		map2->InsertL(_L8("Summary"), TLiwVariant(_L("meeting")) );
		    		map2->InsertL(_L8("LocalId"),TLiwVariant(localuid));

					TLiwVariant filterparam2(map2);
					TLiwGenericParam element3 ;
					element3.SetNameAndValueL(_L8("Item"),filterparam2);
					filterparam2.Reset();

					inParamList->AppendL(element3);
					element3.Reset();

					map2->DecRef();
		    		CleanupStack::Pop(map2);

		    		interface->ExecuteCmdL( KCmdAdd ,*inParamList ,*outParamList);
		    		pos=0;
		    		const TLiwGenericParam* update_err = outParamList->FindFirst(pos,KErrorCode);
   					if(update_err)
   						result = update_err->Value().AsTInt32();

   					if(!result)
   					{
   						inParamList->Reset();
						outParamList->Reset();

						TLiwGenericParam dsNameParam2(KContentType, TLiwVariant(_L("CalendarEntry")));
						inParamList->AppendL(dsNameParam2);

						CLiwDefaultMap* map3 = CLiwDefaultMap::NewL();
						CleanupStack::PushL(map3);

		    			map3->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal2File) );
		    			map3->InsertL(_L8("LocalId"),TLiwVariant(localuid));

						TLiwVariant filterparam3(map3);
						TLiwGenericParam element4 ;
						element4.SetNameAndValueL(_L8("Filter"),filterparam3);
						filterparam3.Reset();

						inParamList->AppendL(element4);
						element4.Reset();

						map3->DecRef();
		    			CleanupStack::Pop(map3);

						interface->ExecuteCmdL( KCmdGetList ,*inParamList ,*outParamList);
		    			pos = 0 ;
		    			const TLiwGenericParam* getlist_err = outParamList->FindFirst(pos,KErrorCode);
   						if(getlist_err)
   							result = getlist_err->Value().AsTInt32();
   						pos=0;
		    			const TLiwGenericParam* output = outParamList->FindFirst( pos,_L8("ReturnValue"));

		    			if(!result && output)
						{
							CLiwIterable* iterlist = output->Value().AsIterable();
			    			TLiwVariant data;
	    	    			while( iterlist->NextL(data))
							{
								const CLiwMap* res = data.AsMap();
								if ( res )
								{
									TLiwVariant new_data;
									if(res->FindL(_L8("Summary"), new_data))
									{
										TPtrC p_owner = new_data.AsDes();
										if( p_owner.CompareF(_L("meeting")) != 0 )
										{
											result = KErrGeneral;
											new_data.Reset();
											break;
										}
									}
									else
										result = KErrGeneral;
									new_data.Reset();
								}
								else
									result = KErrGeneral;
			  				}
			  				data.Reset();
						}
   					}
   				}
   			}

	    inParamList->Reset();
		outParamList->Reset();
	    arruids.ResetAndDestroy();
		}
	else
		result = KErrGeneral;

	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal2File);

	interface->Close();
	iServiceHandler->Reset();
	delete iServiceHandler;

    __UHEAP_MARKEND;
	return result;
    }

// -----------------------------------------------------------------------------
// Ctcal_providertest::Calendar_ops4
// Example test method function to combine notify/add ops on calendar entries.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_providertest::Calendar_ops4( CStifItemParser& aItem )
	{
	TInt32 result = KErrNone;
	__UHEAP_MARK;

	result = ReqNotification(1, EFalse);

	__UHEAP_MARKEND;
	return result;

    }

// -----------------------------------------------------------------------------
// Ctcal_providertest::Calendar_ops5
// Example test method function to combine notify/update/delete operations on calendar entries.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_providertest::Calendar_ops5( CStifItemParser& aItem )
	{
	TInt32 result = KErrNone;
	__UHEAP_MARK;

	result = ReqNotification(2, EFalse);

	__UHEAP_MARKEND;
	return result;

    }


 // -----------------------------------------------------------------------------
// Ctcal_providertest::Calendar_ops6
// Example test method function to combine add/notify/update operations on calendar entries.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_providertest::Calendar_ops6( CStifItemParser& aItem )
	{

	TInt32 result = KErrNone;
	__UHEAP_MARK;

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


	CTestAsync* test = CTestAsync::NewL();
	test->Start( 3, EFalse );
	result = test->Result();
	test->CancelNotification();
	delete test;


	inParamList->Reset();
	outParamList->Reset();

	arruids.ResetAndDestroy();

	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);


	interface->Close();
	iServiceHandler->Reset();
	delete iServiceHandler;
	__UHEAP_MARKEND;
	return result;

    }


// -----------------------------------------------------------------------------
// Ctcal_providertest::Calendar_ops7
// Example test method function to combine add/export/notify/update ops on calendar entries.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_providertest::Calendar_ops7( CStifItemParser& aItem )
	{
	TInt32 result = KErrNone;
	__UHEAP_MARK;

	result = ReqNotification(4, EFalse);

	__UHEAP_MARKEND;
	return result;

    }

  // -----------------------------------------------------------------------------
// Ctcal_providertest::Calendar_ops8
// Example test method function to combine add/update/exp-upd/imp/getlist ops on calendar entries.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_providertest::Calendar_ops8( CStifItemParser& aItem )
	{
		TInt32 result=KErrNone;

	__UHEAP_MARK;

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


	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal2File);

	AddProvCalendar(inParamList, outParamList, interface, KTestCal2File);


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
	TInt count = 0;

	if ( arruids.Count() > 0 )
		{
		   	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
			CleanupStack::PushL(map);

		    map->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal1File) );
		    gid.Copy( arruids[0]->iGlobalUID->Des() );
		    TInt lid_fetch_err = GetLocalUid(inParamList,outParamList,interface,KTestCal1File,arruids[0]->iLocalUID)	;
		    if(lid_fetch_err)
		    {
		    	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
		    	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal2File);
				interface->Close();
				iServiceHandler->Reset();
				delete iServiceHandler;
				__UHEAP_MARKEND;
				return lid_fetch_err;
		    }

			TBuf<10> localuid;
			localuid.Num(TInt64(arruids[0]->iLocalUID));

			// update the entry

		     map->InsertL(_L8("Summary"), TLiwVariant(_L("meeting")));
		     map->InsertL(_L8("LocalId"),TLiwVariant(localuid));

		    TLiwVariant content(_L("CalendarEntry"));
			TLiwGenericParam element1;
			element1.SetNameAndValueL(_L8("Type"),content);
			inParamList->AppendL(element1);
			content.Reset();
			element1.Reset();


		    TLiwVariant filterparam(map);
			TLiwGenericParam element ;
			element.SetNameAndValueL(_L8("Item"),filterparam);
			filterparam.Reset();

			inParamList->AppendL(element);
			element.Reset();
		    map->DecRef();
		    CleanupStack::Pop(map);

			interface->ExecuteCmdL( KCmdAdd, *inParamList ,*outParamList );
			pos=0;
			const TLiwGenericParam* update_err = outParamList->FindFirst(pos,KErrorCode);
   			if(update_err)
   				result = update_err->Value().AsTInt32();

			if(!result)
			{
				inParamList->Reset();
				outParamList->Reset();

				// Do an export of updated entry.

				TLiwGenericParam dsNameParam(KContentType, TLiwVariant(_L("CalendarEntry")));
				inParamList->AppendL(dsNameParam);

				CLiwDefaultMap* map1 = CLiwDefaultMap::NewL();
				CleanupStack::PushL(map1);

				CLiwDefaultList* attlist = CLiwDefaultList::NewL();
				CleanupStack::PushL(attlist);
				attlist->AppendL( TLiwVariant(localuid));

		    	map1->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal1File) );
		    	map1->InsertL(_L8("Format"), TLiwVariant(_L("VCal")) );
				map1->InsertL(_L8("FileName"), TLiwVariant(_L("c:\\exportall.txt")));
				map1->InsertL(_L8("LocalIdList"),TLiwVariant(attlist));

				CleanupStack::Pop(attlist);
				attlist->DecRef();

				TLiwVariant filterparam1(map1);
				TLiwGenericParam element2 ;
				element2.SetNameAndValueL(_L8("Data"),filterparam1);
				filterparam1.Reset();

				inParamList->AppendL(element2);
				element2.Reset();

				map1->DecRef();
		    	CleanupStack::Pop(map1);

				interface->ExecuteCmdL( KCmdExport ,*inParamList ,*outParamList);
				pos = 0 ;
				const TLiwGenericParam* export_err = outParamList->FindFirst(pos,KErrorCode);
   				if(export_err)
   					result = export_err->Value().AsTInt32();

   				if(!result)
   				{
   					inParamList->Reset();
					outParamList->Reset();

					// Import updated entry

					TLiwGenericParam dsNameParam1(KContentType, TLiwVariant(_L("CalendarEntry")));
					inParamList->AppendL(dsNameParam1);

					CLiwDefaultMap* map2 = CLiwDefaultMap::NewL();
					CleanupStack::PushL(map2);

		    		map2->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal2File) );
		    		map2->InsertL(_L8("Format"), TLiwVariant(_L("VCal")) );
					map2->InsertL(_L8("FileName"), TLiwVariant(_L("c:\\exportall.txt")));

					TLiwVariant filterparam2(map2);
					TLiwGenericParam element3 ;
					element3.SetNameAndValueL(_L8("Data"),filterparam2);
					filterparam2.Reset();

					inParamList->AppendL(element3);
					element3.Reset();

					map2->DecRef();
		    		CleanupStack::Pop(map2);

		    		interface->ExecuteCmdL( KCmdImport ,*inParamList ,*outParamList);
		    		pos=0;
		    		const TLiwGenericParam* import_err = outParamList->FindFirst(pos,KErrorCode);
   					if(import_err)
   						result = import_err->Value().AsTInt32();

   					if(!result)
   					{
   						inParamList->Reset();
						outParamList->Reset();
						// Check the updated entry

						TLiwGenericParam dsNameParam2(KContentType, TLiwVariant(_L("CalendarEntry")));
						inParamList->AppendL(dsNameParam2);

						CLiwDefaultMap* map3 = CLiwDefaultMap::NewL();
						CleanupStack::PushL(map3);

				    	map3->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal2File) );
		    			map3->InsertL(_L8("LocalId"),TLiwVariant(localuid));

						TLiwVariant filterparam3(map3);
						TLiwGenericParam element4 ;
						element4.SetNameAndValueL(_L8("Filter"),filterparam3);
						filterparam3.Reset();

						inParamList->AppendL(element4);
						element4.Reset();

						map3->DecRef();
		    			CleanupStack::Pop(map3);

						interface->ExecuteCmdL( KCmdGetList ,*inParamList ,*outParamList);
		    			pos = 0 ;
		    			const TLiwGenericParam* getlist_err = outParamList->FindFirst(pos,KErrorCode);
   						if(getlist_err)
   							result = getlist_err->Value().AsTInt32();
   						pos=0;
		    			const TLiwGenericParam* output = outParamList->FindFirst( pos,_L8("ReturnValue"));

		    			if(!result && output)
						{
							CLiwIterable* iterlist = output->Value().AsIterable();
			    			TLiwVariant data;
	    	    			while( iterlist->NextL(data))
							{
								const CLiwMap* res = data.AsMap();
								if ( res )
								{
									TLiwVariant new_data;
									if(res->FindL(_L8("Summary"), new_data))
									{
										TPtrC p_owner = new_data.AsDes();
										if( p_owner.CompareF(_L("meeting")) != 0 )
										{
											result = KErrGeneral;
											new_data.Reset();
											break;
										}
									}
									else
										result = KErrGeneral;
									new_data.Reset();
								}
								else
									result = KErrGeneral;
			  				}
			  				data.Reset();
						}
   					}
   				}
			}
	    inParamList->Reset();
		outParamList->Reset();
	    arruids.ResetAndDestroy();
		}
	else
		result = KErrGeneral;

	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal2File);

	interface->Close();
	iServiceHandler->Reset();
	delete iServiceHandler;

    __UHEAP_MARKEND;

	return result;

    }

  // -----------------------------------------------------------------------------
// Ctcal_providertest::Calendar_ops9
// Example test method function to combine add/delete/getlist-Guid ops on calendar entries.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_providertest::Calendar_ops9( CStifItemParser& aItem )
	{
		TInt32 result=KErrNone;
		TInt item_found = 0;

	__UHEAP_MARK;

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
	TInt count = 0;

	if ( arruids.Count() > 0 )
		{
			CLiwDefaultMap* map = CLiwDefaultMap::NewL();
			CleanupStack::PushL(map);

		    map->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal1File) );
		    gid.Copy( arruids[0]->iGlobalUID->Des() );

		    TInt lid_fetch_err = GetLocalUid(inParamList,outParamList,interface,KTestCal1File,arruids[0]->iLocalUID)	;
		    if(lid_fetch_err)
		    {
		    	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
		    	interface->Close();
				iServiceHandler->Reset();
				delete iServiceHandler;
				__UHEAP_MARKEND;
				return lid_fetch_err;
		    }

			TBuf<10> localuid;
			localuid.Num(TInt64(arruids[0]->iLocalUID));
			TBuf<50> guid;
	   		guid.Copy(arruids[0]->iGlobalUID->Des());
			// delete the entry	by GUID

			CLiwDefaultList* attlist = CLiwDefaultList::NewL();
			CleanupStack::PushL(attlist);
			attlist->AppendL( TLiwVariant(guid));

		    map->InsertL(_L8("IdList"),TLiwVariant(attlist));

		 	CleanupStack::Pop(attlist);
			attlist->DecRef();

			TLiwVariant content(_L("CalendarEntry"));
			TLiwGenericParam element1;
			element1.SetNameAndValueL(_L8("Type"),content);
			inParamList->AppendL(element1);
			content.Reset();
			element1.Reset();

		    TLiwVariant filterparam(map);
			TLiwGenericParam element ;
			element.SetNameAndValueL(_L8("Data"),filterparam);
			filterparam.Reset();

			inParamList->AppendL(element);
			element.Reset();
		    map->DecRef();
		    CleanupStack::Pop(map);

			interface->ExecuteCmdL( KCmdDelete, *inParamList ,*outParamList );
			pos = 0 ;
		    const TLiwGenericParam* delete_err = outParamList->FindFirst(pos,KErrorCode);
   			if(delete_err)
   				result = delete_err->Value().AsTInt32();

   			if(!result)
   			{

   				inParamList->Reset();
				outParamList->Reset();

				// Check the deleted entry

				TLiwGenericParam dsNameParam2(KContentType, TLiwVariant(_L("CalendarEntry")));
				inParamList->AppendL(dsNameParam2);

				CLiwDefaultMap* map3 = CLiwDefaultMap::NewL();
				CleanupStack::PushL(map3);
		    	map3->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal1File) );
		    	map3->InsertL(_L8("LocalId"),TLiwVariant(localuid));

				TLiwVariant filterparam3(map3);
				TLiwGenericParam element4 ;
				element4.SetNameAndValueL(_L8("Filter"),filterparam3);
				filterparam3.Reset();

				inParamList->AppendL(element4);
				element4.Reset();

				map3->DecRef();
		    	CleanupStack::Pop(map3);

				interface->ExecuteCmdL( KCmdGetList ,*inParamList ,*outParamList);
		    	pos = 0 ;
		    	const TLiwGenericParam* getlist_err = outParamList->FindFirst(pos,KErrorCode);
   				if(getlist_err)
   					result = getlist_err->Value().AsTInt32();
		    	pos=0;
		    	const TLiwGenericParam* output = outParamList->FindFirst( pos,_L8("ReturnValue"));

				if(!result && output)
				{
					CLiwIterable* iterlist = output->Value().AsIterable();
			    	TLiwVariant data;
	    	    	while( iterlist->NextL(data))
					{
						const CLiwMap* res = data.AsMap();
						if ( res )
						{
							item_found++;
						}
			  		}
			  		data.Reset();
				}
   			}
	    inParamList->Reset();
		outParamList->Reset();
	    arruids.ResetAndDestroy();
		}
	else
		result = KErrGeneral;

	if(!result && item_found != 0)
		result = KErrGeneral;

	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	//RmoveProvCalendar(inParamList, outParamList, interface, KTestCal2File);

	interface->Close();
	iServiceHandler->Reset();
	delete iServiceHandler;

    __UHEAP_MARKEND;

	return result;

    }


 // -----------------------------------------------------------------------------
// Ctcal_providertest::Calendar_ops10
// Example test method function to combine add/update/exp!upd/imp/getlist ops on calendar entries.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_providertest::Calendar_ops10( CStifItemParser& aItem )
	{
		TInt32 result=KErrNone;
		TInt item_found = 0;
		TInt item_found1 = 0;

	__UHEAP_MARK;

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


	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal2File);

	AddProvCalendar(inParamList, outParamList, interface, KTestCal2File);


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
	TInt count = 0;

	if ( arruids.Count() > 0 )
		{
			CLiwDefaultMap* map = CLiwDefaultMap::NewL();
			CleanupStack::PushL(map);

		    map->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal1File) );

		    gid.Copy( arruids[0]->iGlobalUID->Des() );

		    TInt lid_fetch_err = GetLocalUid(inParamList,outParamList,interface,KTestCal1File,arruids[0]->iLocalUID)	;
		    if(lid_fetch_err)
		    {
		    	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
		    	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal2File);
		    	interface->Close();
				iServiceHandler->Reset();
				delete iServiceHandler;
				__UHEAP_MARKEND;
				return lid_fetch_err;
		    }

		    gid.Copy( arruids[1]->iGlobalUID->Des() );

		    TInt lid_fetch_err1 = GetLocalUid(inParamList,outParamList,interface,KTestCal1File,arruids[1]->iLocalUID)	;
		    if(lid_fetch_err1)
		    {
		    	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
		    	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal2File);
		    	interface->Close();
				iServiceHandler->Reset();
				delete iServiceHandler;
				__UHEAP_MARKEND;
				return lid_fetch_err1;
		    }

			TBuf<10> localuid;
			localuid.Num(TInt64(arruids[0]->iLocalUID));
			TBuf<10> localuid1;
			localuid1.Num(TInt64(arruids[1]->iLocalUID));
			TBuf<50> guid;
	   		guid.Copy(arruids[0]->iGlobalUID->Des());

			// update the entry

		     map->InsertL(_L8("Summary"), TLiwVariant(_L("meeting")) );
		     map->InsertL(_L8("LocalId"),TLiwVariant(localuid));

		     TLiwVariant content(_L("CalendarEntry"));
			TLiwGenericParam element1;
			element1.SetNameAndValueL(_L8("Type"),content);
			inParamList->AppendL(element1);
			content.Reset();
			element1.Reset();

		    TLiwVariant filterparam(map);
			TLiwGenericParam element ;
			element.SetNameAndValueL(_L8("Item"),filterparam);
			filterparam.Reset();

			inParamList->AppendL(element);
			element.Reset();
		    map->DecRef();
		    CleanupStack::Pop(map);

			interface->ExecuteCmdL( KCmdAdd, *inParamList ,*outParamList );
			pos=0;
			const TLiwGenericParam* update_err = outParamList->FindFirst(pos,KErrorCode);
   			if(update_err)
   				result = update_err->Value().AsTInt32();

   			if(!result)
   			{

   				inParamList->Reset();
				outParamList->Reset();

				// Do an export of updated entry.

				TLiwGenericParam dsNameParam(KContentType, TLiwVariant(_L("CalendarEntry")));
				inParamList->AppendL(dsNameParam);

				CLiwDefaultMap* map1 = CLiwDefaultMap::NewL();
				CleanupStack::PushL(map1);

				CLiwDefaultList* attlist = CLiwDefaultList::NewL();
				CleanupStack::PushL(attlist);
				attlist->AppendL( TLiwVariant(localuid1));

		    	map1->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal1File) );
		    	map1->InsertL(_L8("Format"), TLiwVariant(_L("VCal")) );
				map1->InsertL(_L8("FileName"), TLiwVariant(_L("c:\\exportall.txt")));
				map1->InsertL(_L8("LocalIdList"),TLiwVariant(attlist));

				CleanupStack::Pop(attlist);
				attlist->DecRef();

				TLiwVariant filterparam1(map1);
				TLiwGenericParam element2 ;
				element2.SetNameAndValueL(_L8("Data"),filterparam1);
				filterparam1.Reset();

				inParamList->AppendL(element2);
				element2.Reset();

				map1->DecRef();
		    	CleanupStack::Pop(map1);

				interface->ExecuteCmdL( KCmdExport ,*inParamList ,*outParamList);
		    	pos = 0 ;
		    	const TLiwGenericParam* export_err = outParamList->FindFirst(pos,KErrorCode);
   				if(export_err)
   					result = export_err->Value().AsTInt32();

   				if(!result)
   				{
   					inParamList->Reset();
					outParamList->Reset();

					// Import updated entry

					TLiwGenericParam dsNameParam1(KContentType, TLiwVariant(_L("CalendarEntry")));
					inParamList->AppendL(dsNameParam1);

					CLiwDefaultMap* map2 = CLiwDefaultMap::NewL();
					CleanupStack::PushL(map2);

		   			map2->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal2File) );
		    		map2->InsertL(_L8("Format"), TLiwVariant(_L("VCal")) );
					map2->InsertL(_L8("FileName"), TLiwVariant(_L("c:\\exportall.txt")));

					TLiwVariant filterparam2(map2);
					TLiwGenericParam element3 ;
					element3.SetNameAndValueL(_L8("Data"),filterparam2);
					filterparam2.Reset();

					inParamList->AppendL(element3);
					element3.Reset();

					map2->DecRef();
		    		CleanupStack::Pop(map2);

		    		interface->ExecuteCmdL( KCmdImport ,*inParamList ,*outParamList);
		    		const TLiwGenericParam* import_err = outParamList->FindFirst(pos,KErrorCode);
   					if(import_err)
   						result = import_err->Value().AsTInt32();

   					if(!result)
   					{
   						inParamList->Reset();
						outParamList->Reset();

						// Check for the unexported updated entry

						TLiwGenericParam dsNameParam2(KContentType, TLiwVariant(_L("CalendarEntry")));
						inParamList->AppendL(dsNameParam2);

						CLiwDefaultMap* map3 = CLiwDefaultMap::NewL();
						CleanupStack::PushL(map3);

		   				map3->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal1File) );
		    			map3->InsertL(_L8("LocalId"),TLiwVariant(localuid));


						TLiwVariant filterparam3(map3);
						TLiwGenericParam element4 ;
						element4.SetNameAndValueL(_L8("Filter"),filterparam3);
						filterparam3.Reset();

						inParamList->AppendL(element4);
						element4.Reset();

						map3->DecRef();
		    			CleanupStack::Pop(map3);

						interface->ExecuteCmdL( KCmdGetList ,*inParamList ,*outParamList);
		    			pos = 0 ;
		    			const TLiwGenericParam* getlist_err = outParamList->FindFirst(pos,KErrorCode);
   						if(getlist_err)
   							result = getlist_err->Value().AsTInt32();
   						pos=0;
		    			const TLiwGenericParam* output = outParamList->FindFirst( pos,_L8("ReturnValue"));

		    			if(!result && output)
						{
							CLiwIterable* iterlist = output->Value().AsIterable();
			    			TLiwVariant data;
	    	    			while( iterlist->NextL(data))
							{
								const CLiwMap* res = data.AsMap();
								if ( res )
								{
									item_found++;
									TLiwVariant new_data;
									if(res->FindL(_L8("Summary"), new_data))
									{
										TPtrC p_owner = new_data.AsDes();
										if( p_owner.CompareF(_L("meeting")) != 0 )
										{
											result = KErrGeneral;
											new_data.Reset();
											break;
										}
									}
									else
										result = KErrGeneral;
									new_data.Reset();
								}
								else
									result = KErrGeneral;
			  				}
			  				data.Reset();
						}
   					}
   				}
   			}
		inParamList->Reset();
		outParamList->Reset();
	    arruids.ResetAndDestroy();
		}
	else
		result = KErrGeneral;

	if(!result && item_found != 1)
		result = KErrGeneral;

	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal2File);

	interface->Close();
	iServiceHandler->Reset();
	delete iServiceHandler;

    __UHEAP_MARKEND;
	return result;
    }


// -----------------------------------------------------------------------------
// Ctcal_providertest::Calendar_ops11
// Example test method function to combine add/deleteall/exp/imp/getlist ops on calendar entries.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_providertest::Calendar_ops11( CStifItemParser& aItem )
	{
		TInt32 result=KErrNone;
		TInt item_found = 0;
		TInt item_found1 = 0;

	__UHEAP_MARK;

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


	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal2File);

	AddProvCalendar(inParamList, outParamList, interface, KTestCal2File);


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
	TInt count = 0;

	if ( arruids.Count() > 0 )
		{
			CLiwDefaultMap* map = CLiwDefaultMap::NewL();
			CleanupStack::PushL(map);

		    map->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal1File) );

		    gid.Copy( arruids[0]->iGlobalUID->Des() );

		    TInt lid_fetch_err = GetLocalUid(inParamList,outParamList,interface,KTestCal1File,arruids[0]->iLocalUID)	;
		    if(lid_fetch_err)
		    {
		    	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
		    	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal2File);
		    	interface->Close();
				iServiceHandler->Reset();
				delete iServiceHandler;
				__UHEAP_MARKEND;
				return lid_fetch_err;
		    }

			TBuf<10> localuid;
			localuid.Num(TInt64(arruids[0]->iLocalUID));

			// delete all

		    // map->InsertL(_L8("LocalUid"),TLiwVariant(localuid));
		     map->InsertL(_L8("DeleteAll"), TLiwVariant(TBool(ETrue)) );

		 	TLiwVariant content(_L("CalendarEntry"));
			TLiwGenericParam element1;
			element1.SetNameAndValueL(_L8("Type"),content);
			inParamList->AppendL(element1);
			content.Reset();
			element1.Reset();

		    TLiwVariant filterparam(map);
			TLiwGenericParam element ;
			element.SetNameAndValueL(_L8("Data"),filterparam);
			filterparam.Reset();

			inParamList->AppendL(element);
			element.Reset();
		    map->DecRef();
		    CleanupStack::Pop(map);

			interface->ExecuteCmdL( KCmdDelete, *inParamList ,*outParamList );
			pos=0;
			const TLiwGenericParam* delete_err = outParamList->FindFirst(pos,KErrorCode);
   			if(delete_err)
   				result = delete_err->Value().AsTInt32();

   			if(!result)
   			{
   				inParamList->Reset();
				outParamList->Reset();

				// Do an export .

				TLiwGenericParam dsNameParam(KContentType, TLiwVariant(_L("CalendarEntry")));
				inParamList->AppendL(dsNameParam);

				CLiwDefaultMap* map1 = CLiwDefaultMap::NewL();
				CleanupStack::PushL(map1);

				map1->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal1File) );
		    	map1->InsertL(_L8("Format"), TLiwVariant(_L("VCal")) );
				map1->InsertL(_L8("FileName"), TLiwVariant(_L("c:\\exportall.txt")));

				TLiwVariant filterparam1(map1);
				TLiwGenericParam element2 ;
				element2.SetNameAndValueL(_L8("Data"),filterparam1);
				filterparam1.Reset();

				inParamList->AppendL(element2);
				element2.Reset();

				map1->DecRef();
		    	CleanupStack::Pop(map1);

				interface->ExecuteCmdL( KCmdExport ,*inParamList ,*outParamList);
		    	pos = 0 ;
		    	const TLiwGenericParam* export_err = outParamList->FindFirst(pos,KErrorCode);
   				if(export_err)
   					result = export_err->Value().AsTInt32();

   				if(!result)
   				{
   					inParamList->Reset();
					outParamList->Reset();

					// Import

					TLiwGenericParam dsNameParam1(KContentType, TLiwVariant(_L("CalendarEntry")));
					inParamList->AppendL(dsNameParam1);

					CLiwDefaultMap* map2 = CLiwDefaultMap::NewL();
					CleanupStack::PushL(map2);

		    		map2->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal2File) );
		    		map2->InsertL(_L8("Format"), TLiwVariant(_L("VCal")) );
					map2->InsertL(_L8("FileName"), TLiwVariant(_L("c:\\exportall.txt")));

					TLiwVariant filterparam2(map2);
					TLiwGenericParam element3 ;
					element3.SetNameAndValueL(_L8("Data"),filterparam2);
					filterparam2.Reset();

					inParamList->AppendL(element3);
					element3.Reset();

					map2->DecRef();
		    		CleanupStack::Pop(map2);

		    		interface->ExecuteCmdL( KCmdImport ,*inParamList ,*outParamList);
		    		pos=0;
		    		const TLiwGenericParam* import_err = outParamList->FindFirst(pos,KErrorCode);
   					if(import_err)
   						result = import_err->Value().AsTInt32();

   					if(!result)
   					{
   						inParamList->Reset();
						outParamList->Reset();

						// Check for the entry

						TLiwGenericParam dsNameParam2(KContentType, TLiwVariant(_L("CalendarEntry")));
						inParamList->AppendL(dsNameParam2);

						CLiwDefaultMap* map3 = CLiwDefaultMap::NewL();
						CleanupStack::PushL(map3);

		    			map3->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal1File) );
		    			map3->InsertL(_L8("LocalId"),TLiwVariant(localuid));

						TLiwVariant filterparam3(map3);
						TLiwGenericParam element4 ;
						element4.SetNameAndValueL(_L8("Filter"),filterparam3);
						filterparam3.Reset();

						inParamList->AppendL(element4);
						element4.Reset();

						map3->DecRef();
		    			CleanupStack::Pop(map3);

						interface->ExecuteCmdL( KCmdGetList ,*inParamList ,*outParamList);
		    			pos = 0 ;
		    			const TLiwGenericParam* getlist_err = outParamList->FindFirst(pos,KErrorCode);
   						if(getlist_err)
   							result = getlist_err->Value().AsTInt32();
   						pos=0;
		    			const TLiwGenericParam* output = outParamList->FindFirst( pos,_L8("ReturnValue"));

						if(!result && output)
						{
							CLiwIterable* iterlist = output->Value().AsIterable();
			    			TLiwVariant data;

	    	    			while( iterlist->NextL(data))
							{
								const CLiwMap* res = data.AsMap();
								if ( res )
								{
									item_found++;
								}
								else
									result = KErrGeneral;
			  				}
			  				data.Reset();
						}
   					}
   				}
   			}
		inParamList->Reset();
		outParamList->Reset();
	    arruids.ResetAndDestroy();
		}
	else
		result = KErrGeneral;

	if(!result && item_found != 0)
		result = KErrGeneral;


	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal2File);


	interface->Close();
	iServiceHandler->Reset();
	delete iServiceHandler;

    __UHEAP_MARKEND;

	return result;


    }

 // -----------------------------------------------------------------------------
// Ctcal_providertest::Calendar_ops12
// Example test method function to combine add/del-tmrg/exp-Null/imp/getlist ops on calendar entries.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_providertest::Calendar_ops12( CStifItemParser& aItem )
	{
		TInt32 result=KErrNone;
		TInt item_found = 0;
		TInt item_found1 = 0;

	__UHEAP_MARK;

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


	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal2File);

	AddProvCalendar(inParamList, outParamList, interface, KTestCal2File);


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
	TInt count = 0;

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

			TBuf<10> localuid;
			localuid.Num(TInt64(arruids[0]->iLocalUID));


			// delete with time range

		     map->InsertL(_L8("StartRange"),TLiwVariant(TTime(TDateTime(2007,EOctober,22,10,0,0,0))));
		     map->InsertL(_L8("EndRange"),TLiwVariant(TTime(TDateTime(2007,EOctober,25,10,0,0,0))));

		    TLiwVariant filterparam(map);
			TLiwGenericParam element ;
			element.SetNameAndValueL(_L8("Data"),filterparam);
			filterparam.Reset();

			inParamList->AppendL(element);
			element.Reset();
		    map->DecRef();
		    CleanupStack::Pop(map);

			interface->ExecuteCmdL( KCmdDelete, *inParamList ,*outParamList );
			pos=0;
			const TLiwGenericParam* delete_err = outParamList->FindFirst(pos,KErrorCode);
   			if(delete_err)
   				result = delete_err->Value().AsTInt32();

   			if(!result)
   			{
   				inParamList->Reset();
				outParamList->Reset();
				// Do an export .

				TLiwGenericParam dsNameParam(KContentType, TLiwVariant(_L("CalendarEntry")));
				inParamList->AppendL(dsNameParam);

				CLiwDefaultMap* map1 = CLiwDefaultMap::NewL();
				CleanupStack::PushL(map1);

			    map1->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal1File) );
			    map1->InsertL(_L8("Format"), TLiwVariant(_L("VCal")) );
				map1->InsertL(_L8("FileName"), TLiwVariant(_L("c:\\exportall.txt")));

				TLiwVariant filterparam1(map1);
				TLiwGenericParam element2 ;
				element2.SetNameAndValueL(_L8("Data"),filterparam1);
				filterparam1.Reset();

				inParamList->AppendL(element2);
				element2.Reset();

				map1->DecRef();
		    	CleanupStack::Pop(map1);

				interface->ExecuteCmdL( KCmdExport ,*inParamList ,*outParamList);
		    	pos = 0 ;
				const TLiwGenericParam* export_err = outParamList->FindFirst(pos,KErrorCode);
   				if(export_err)
   					result = export_err->Value().AsTInt32();

   				if(!result)
   				{
   					inParamList->Reset();
					outParamList->Reset();

					// Import

					TLiwGenericParam dsNameParam1(KContentType, TLiwVariant(_L("CalendarEntry")));
					inParamList->AppendL(dsNameParam1);

					CLiwDefaultMap* map2 = CLiwDefaultMap::NewL();
					CleanupStack::PushL(map2);

		    		map2->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal2File) );
		    		map2->InsertL(_L8("Format"), TLiwVariant(_L("VCal")) );
					map2->InsertL(_L8("FileName"), TLiwVariant(_L("c:\\exportall.txt")));

					TLiwVariant filterparam2(map2);
					TLiwGenericParam element3 ;
					element3.SetNameAndValueL(_L8("Data"),filterparam2);
					filterparam2.Reset();

					inParamList->AppendL(element3);
					element3.Reset();

					map2->DecRef();
		    		CleanupStack::Pop(map2);

		    		interface->ExecuteCmdL( KCmdImport ,*inParamList ,*outParamList);
		    		pos=0;
		    		const TLiwGenericParam* import_err = outParamList->FindFirst(pos,KErrorCode);
   					if(import_err)
   						result = import_err->Value().AsTInt32();

   					if(!result)
   					{
   						inParamList->Reset();
						outParamList->Reset();

						// Check for entries

						TLiwGenericParam dsNameParam2(KContentType, TLiwVariant(_L("CalendarEntry")));
						inParamList->AppendL(dsNameParam2);

						CLiwDefaultMap* map3 = CLiwDefaultMap::NewL();
						CleanupStack::PushL(map3);

		   			 	map3->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal1File) );
		   				 map3->InsertL(_L8("Type"),TLiwVariant(_L("IncludeAll")));

						TLiwVariant filterparam3(map3);
						TLiwGenericParam element4 ;
						element4.SetNameAndValueL(_L8("Filter"),filterparam3);
						filterparam3.Reset();

						inParamList->AppendL(element4);
						element4.Reset();

						map3->DecRef();
		    			CleanupStack::Pop(map3);

						interface->ExecuteCmdL( KCmdGetList ,*inParamList ,*outParamList);
		    			pos = 0 ;
		    			const TLiwGenericParam* getlist_err = outParamList->FindFirst(pos,KErrorCode);
   						if(getlist_err)
   							result = getlist_err->Value().AsTInt32();
   						pos=0;
		    			const TLiwGenericParam* output = outParamList->FindFirst( pos,_L8("ReturnValue"));
						if(!result && output)
						{
							CLiwIterable* iterlist = output->Value().AsIterable();
			    			TLiwVariant data;

	    	    			while( iterlist->NextL(data))
							{
								const CLiwMap* res = data.AsMap();
								if ( res )
								{
									item_found++;
								}
								else
									result = KErrGeneral;
						  	}
			  				data.Reset();
			  			}
   					}
   				}
   			}

		inParamList->Reset();
		outParamList->Reset();
	    arruids.ResetAndDestroy();
		}
	else
		result = KErrGeneral;

	if(!result && item_found != 6)
		result = KErrGeneral;


	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal2File);


	interface->Close();
	iServiceHandler->Reset();
	delete iServiceHandler;

    __UHEAP_MARKEND;

	return result;


    }

 // -----------------------------------------------------------------------------
// Ctcal_providertest::Calendar_ops13
// Example test method function to combine add/upd-inst/getlist/del/getlist ops on calendar entries.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_providertest::Calendar_ops13( CStifItemParser& aItem )
	{
		TInt32 result=KErrNone;
		TInt item_found = 0;
		TInt item_found1 = 0;

	__UHEAP_MARK;

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


	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal2File);

	AddProvCalendar(inParamList, outParamList, interface, KTestCal2File);


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
	TInt count = 0;

	if ( arruids.Count() > 0 )
		{
		   	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
			CleanupStack::PushL(map);

		    map->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal1File) );

		    gid.Copy( arruids[0]->iGlobalUID->Des() );

		    TInt lid_fetch_err = GetLocalUid(inParamList,outParamList,interface,KTestCal1File,arruids[0]->iLocalUID)	;
		    if(lid_fetch_err)
		    {
		    	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
		    	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal2File);
		    	interface->Close();
				iServiceHandler->Reset();
				delete iServiceHandler;
				__UHEAP_MARKEND;
				return lid_fetch_err;
		    }

			TBuf<10> localuid;
			localuid.Num(TInt64(arruids[0]->iLocalUID));
			TBuf<50> guid;
	   		guid.Copy(arruids[0]->iGlobalUID->Des());

			// update instance
			map->InsertL(_L8("StartTime"), TLiwVariant(TTime(TDateTime(2007,EOctober,25,14,30,0,0))));
			map->InsertL(_L8("EndTime"), TLiwVariant(TTime(TDateTime(2007,EOctober,25,15,30,0,0))));
			map->InsertL(_L8("InstanceStartTime"), TLiwVariant(TTime(TDateTime(2007,EOctober,25,10,0,0,0))));
		    map->InsertL(_L8("LocalId"),TLiwVariant(localuid));

		 	TLiwVariant content(_L("CalendarEntry"));
			TLiwGenericParam element1;
			element1.SetNameAndValueL(_L8("Type"),content);
			inParamList->AppendL(element1);
			content.Reset();
			element1.Reset();


		    TLiwVariant filterparam(map);
			TLiwGenericParam element ;
			element.SetNameAndValueL(_L8("Item"),filterparam);
			filterparam.Reset();

			inParamList->AppendL(element);
			element.Reset();
		    map->DecRef();
		    CleanupStack::Pop(map);

			interface->ExecuteCmdL( KCmdAdd, *inParamList ,*outParamList );
			pos=0;
			const TLiwGenericParam* update_err = outParamList->FindFirst(pos,KErrorCode);
   			if(update_err)
   				result = update_err->Value().AsTInt32();

   			if(!result)
   			{
   				inParamList->Reset();
				outParamList->Reset();

				// Do an getlist by Guid .

				TLiwGenericParam dsNameParam(KContentType, TLiwVariant(_L("CalendarEntry")));
				inParamList->AppendL(dsNameParam);

				CLiwDefaultMap* map1 = CLiwDefaultMap::NewL();
				CleanupStack::PushL(map1);

		  		map1->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal1File) );
		 		map1->InsertL(_L8("id"),TLiwVariant(guid));

				TLiwVariant filterparam1(map1);
				TLiwGenericParam element2 ;
				element2.SetNameAndValueL(_L8("Filter"),filterparam1);
				filterparam1.Reset();

				inParamList->AppendL(element2);
				element2.Reset();

				map1->DecRef();
		    	CleanupStack::Pop(map1);

				interface->ExecuteCmdL( KCmdGetList ,*inParamList ,*outParamList);
		    	pos = 0 ;
		    	const TLiwGenericParam* getlist_err = outParamList->FindFirst(pos,KErrorCode);
   				if(getlist_err)
   					result = getlist_err->Value().AsTInt32();
   				pos=0;
			    const TLiwGenericParam* output = outParamList->FindFirst( pos,_L8("ReturnValue"));
				if(!result && output)
				{
					TInt err = output->Value().AsTInt32();
					CLiwIterable* iterlist = output->Value().AsIterable();
			    	TLiwVariant data;

	    	    	while( iterlist->NextL(data))
					{
						const CLiwMap* res = data.AsMap();
						if ( res )
						{
							item_found++;
						}
						else
							result = KErrGeneral;
			  		}
			  		data.Reset();
			  	}

			  	if(!result)
			  	{
			  		inParamList->Reset();
					outParamList->Reset();

					// Delete by Guid

					TLiwGenericParam dsNameParam1(KContentType, TLiwVariant(_L("CalendarEntry")));
					inParamList->AppendL(dsNameParam1);

					CLiwDefaultMap* map2 = CLiwDefaultMap::NewL();
					CleanupStack::PushL(map2);

					CLiwDefaultList* attlist = CLiwDefaultList::NewL();
					CleanupStack::PushL(attlist);
					attlist->AppendL( TLiwVariant(guid));


		    		map2->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal1File) );
		    		map2->InsertL(_L8("IdList"),TLiwVariant(attlist));

					CleanupStack::Pop(attlist);
					attlist->DecRef();

					TLiwVariant filterparam2(map2);
					TLiwGenericParam element3 ;
					element3.SetNameAndValueL(_L8("Data"),filterparam2);
					filterparam2.Reset();

					inParamList->AppendL(element3);
					element3.Reset();

					map2->DecRef();
		    		CleanupStack::Pop(map2);

		    		interface->ExecuteCmdL( KCmdDelete ,*inParamList ,*outParamList);
		    		pos=0;
		    		const TLiwGenericParam* delete_err = outParamList->FindFirst(pos,KErrorCode);
   					if(delete_err)
   						result = delete_err->Value().AsTInt32();

   					if(!result)
   					{
   						inParamList->Reset();
						outParamList->Reset();

						// Check for deleted entry

						TLiwGenericParam dsNameParam2(KContentType, TLiwVariant(_L("CalendarEntry")));
						inParamList->AppendL(dsNameParam2);

						CLiwDefaultMap* map3 = CLiwDefaultMap::NewL();
						CleanupStack::PushL(map3);

		    			map3->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal1File) );
		    			map3->InsertL(_L8("Type"),TLiwVariant(_L("IncludeAll")));


						TLiwVariant filterparam3(map3);
						TLiwGenericParam element4 ;
						element4.SetNameAndValueL(_L8("Filter"),filterparam3);
						filterparam3.Reset();

						inParamList->AppendL(element4);
						element4.Reset();

						map3->DecRef();
		    			CleanupStack::Pop(map3);


						interface->ExecuteCmdL( KCmdGetList ,*inParamList ,*outParamList);
		    			pos = 0 ;
		    			const TLiwGenericParam* getlist_err = outParamList->FindFirst(pos,KErrorCode);
   						if(getlist_err)
   							result = getlist_err->Value().AsTInt32();
   						pos=0;

		    			const TLiwGenericParam* output1 = outParamList->FindFirst( pos,_L8("ReturnValue"));

						if(!result && output1)
						{
							CLiwIterable* iterlist1 = output1->Value().AsIterable();

			    			TLiwVariant data1;

	    	    			while( iterlist1->NextL(data1))
							{
								const CLiwMap* res1 = data1.AsMap();
								if ( res1 )
								{
									item_found1++;

								}
								else
									result = KErrGeneral;
			  				}

			  				data1.Reset();
						}
   					}
			  	}
   			}

		inParamList->Reset();
		outParamList->Reset();
	    arruids.ResetAndDestroy();
		}
	else
		result = KErrGeneral;

	if(!result && (item_found1 != 1 || item_found != 2))
		result = KErrGeneral;


	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal2File);


	interface->Close();
	iServiceHandler->Reset();
	delete iServiceHandler;

    __UHEAP_MARKEND;

	return result;


    }

// -----------------------------------------------------------------------------
// Ctcal_providertest::Calendar_ops14
// Example test method function to test for invalid values
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_providertest::Calendar_ops14( CStifItemParser& aItem )
	{

	TInt32 result=KErrNone;
	TInt item_found = 0;

	__UHEAP_MARK;

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
	TInt count = 0;

	if ( arruids.Count() > 0 )
		{

			TLiwGenericParam dsNameParam2(KContentType, TLiwVariant(_L("CalendarEntry")));
			inParamList->AppendL(dsNameParam2);

			CLiwDefaultMap* map3 = CLiwDefaultMap::NewL();
			CleanupStack::PushL(map3);

		    map3->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal1File) );
		    map3->InsertL(_L8("Type"),TLiwVariant(_L("Include")));

			TLiwVariant filterparam3(map3);
			TLiwGenericParam element4 ;
			element4.SetNameAndValueL(_L8("Filter"),filterparam3);
			filterparam3.Reset();

			inParamList->AppendL(element4);
			element4.Reset();

			map3->DecRef();
		    CleanupStack::Pop(map3);


			interface->ExecuteCmdL( KCmdGetList ,*inParamList ,*outParamList);
		    pos = 0 ;

		    const TLiwGenericParam* err_output3 = outParamList->FindFirst( pos,_L8("ErrorCode"));


			if(err_output3)
			{
				TInt err3 = err_output3->Value().AsTInt32();
				if(err3 == KErrNone)
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

// -----------------------------------------------------------------------------
// Ctcal_providertest::Calendar_ops15
// Example test method function to check if apt cal entry exists and include the data in a message
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_providertest::Calendar_ops15( CStifItemParser& aItem )
	{
		TInt32 result=KErrNone;
		TInt32 message_id = 0;
		TInt err;

		TInt flag =0;


	__UHEAP_MARK;

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
	TInt count = 0;


			TLiwGenericParam dsNameParam(KContentType, TLiwVariant(_L("CalendarEntry")));
			inParamList->AppendL(dsNameParam);

			CLiwDefaultMap* map = CLiwDefaultMap::NewL();
			CleanupStack::PushL(map);

		    map->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal1File) );
		    map->InsertL(_L8("Type"),TLiwVariant(_L("Meeting")));


			TLiwVariant filterparam(map);
			TLiwGenericParam element ;
			element.SetNameAndValueL(_L8("Filter"),filterparam);
			filterparam.Reset();

			inParamList->AppendL(element);
			element.Reset();

			map->DecRef();
		    CleanupStack::Pop(map);


			interface->ExecuteCmdL( KCmdGetList ,*inParamList ,*outParamList);
		    pos = 0 ;
			const TLiwGenericParam* output = outParamList->FindFirst( pos,_L8("ReturnValue"));

			if(output)
			{
				CLiwIterable* iterlist1 = output->Value().AsIterable();
			    TLiwVariant data;
	    	    while( iterlist1->NextL(data))
	    	   	{
					const CLiwMap* res = data.AsMap();
					if ( res )
					{
						flag = 1;
						break;
					}
					else
						result = KErrGeneral;
			  	}
			  	data.Reset();
			}
	inParamList->Reset();
	outParamList->Reset();
	arruids.ResetAndDestroy();

	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	interface->Close();

	// Send Msg with guid of meeting entry

	CLiwGenericParamList* inParam = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outParam = &(iServiceHandler->OutParamListL());
	CLiwCriteriaItem* crit_msg = CLiwCriteriaItem::NewL(1, KMsgIDataSource,KMsgService);

    crit_msg->SetServiceClass(TUid::Uid(KLiwClassBase));

    RCriteriaArray a_msg;
    a_msg.AppendL(crit_msg);

    iServiceHandler->AttachL(a_msg);

	iServiceHandler->ExecuteServiceCmdL(*crit_msg, *inParam, *outParam);

	TInt pos_msg = 0;
    MLiwInterface* interface_msg = NULL;

    outParam->FindFirst(pos_msg,KMsgIDataSource);
    if(pos_msg != KErrNotFound)
        {
        interface_msg = (*outParam)[pos_msg].Value().AsInterface();
        }

	inParam->Reset();
	outParam->Reset();

	delete crit_msg;
	crit_msg = NULL;
	a_msg.Reset();

	inParam->AppendL(TLiwGenericParam( _L8("MessageType"), TLiwVariant( _L("SMS") )));
	inParam->AppendL(TLiwGenericParam( _L8("To"), TLiwVariant( _L("9740067386") )));
	if(flag)
	inParam->AppendL(TLiwGenericParam( _L8("BodyText"), TLiwVariant( _L("Appointment") )));
	else
    inParam->AppendL(TLiwGenericParam( _L8("BodyText"), TLiwVariant( _L("No Apt") )));

	interface_msg->ExecuteCmdL( KMsgSendCmd ,*inParam ,*outParam,0,NULL );

 	TInt index = 0;
	const TLiwGenericParam* err2 = outParam->FindFirst(index,KErrCode);
	result = err2->Value().AsTInt32();



 /*	if(!result)
 	{
 		inParam->Reset();
		outParam->Reset();

    	TLiwVariant content(_L8("Inbox"));
		TLiwGenericParam element1 ;
		element1.SetNameAndValueL(_L8("Type"),_L("Inbox"));
		inParam->AppendL(element1);
		content.Reset();
		element1.Reset();
   		CLiwDefaultMap* map1 = CLiwDefaultMap::NewL();
		CleanupStack::PushL(map1);

    	CLiwDefaultList* mtmtypelist = CLiwDefaultList::NewL();
    	CleanupStack::PushL(mtmtypelist);

    	TLiwVariant mmsmtm(KMessageTypeSMS);
    	mtmtypelist->AppendL(mmsmtm);
    	mmsmtm.Reset();

    	TLiwVariant add1(mtmtypelist);

    	map1->InsertL(_L8("MessageTypeList"), add1); // Mtmtype is added
    	mtmtypelist->DecRef();
    	CleanupStack::Pop(mtmtypelist);
    	add1.Reset();

    	TLiwVariant filterparam1(map1);
		TLiwGenericParam element2 ;
		element2.SetNameAndValueL(_L8("Filter"),filterparam1);
		filterparam1.Reset();

    	inParam->AppendL(element2);
		element2.Reset();

    	map1->DecRef();
    	CleanupStack::Pop(map1);

    	interface_msg->ExecuteCmdL( KMsgGetListCmd ,*inParam ,*outParam);
    	pos = 0 ;
    	const TLiwGenericParam* getlistmsg_err = outParam->FindFirst(pos,KErrCode);
    	if(getlistmsg_err)
			result = getlistmsg_err->Value().AsTInt32();
    	pos=0;
    	const TLiwGenericParam* output1 = outParam->FindFirst( pos,_L8("ReturnValue"));

    	if(!result && output1)
			{
				TInt err = output1->Value().AsTInt32();
				CLiwIterable* iterlist2 = output1->Value().AsIterable();

			    TLiwVariant data;

	    	    while( iterlist2->NextL(data))
				{
					const CLiwMap* res = data.AsMap();
					if ( res )
					{
						TLiwVariant text;
						if(res->FindL(_L8("BodyText"), text))
						{
							TPtrC apt_text = text.AsDes();
							TBuf<40> buf ;
							buf.Copy(apt_text) ;
							iLog->Log(buf) ;

							TInt val = apt_text.Compare(_L("Appointment"));

							if(apt_text.Compare(_L("Appointment")) != 0)
								result = KErrGeneral;

						}
						text.Reset();

						TLiwVariant mid;
						if(res->FindL(_L8("MessageId"), mid))
						{
							message_id = mid.AsTInt32();

						}
						mid.Reset();
					}
					else
						result = KErrGeneral;
			  	}
			  	data.Reset();

			}
 	}

 	if(!result && message_id)
 	{
 		//Delete the message
 		inParam->Reset();
		outParam->Reset();
 		inParam->AppendL(TLiwGenericParam( _L8("MessageId"), TLiwVariant( TInt32(message_id) )));

		interface_msg->ExecuteCmdL( KMsgDelete ,*inParam ,*outParam,0,NULL );

 		index = 0;
		const TLiwGenericParam* err_del = outParam->FindFirst(index,KErrCode);
		result = err_del->Value().AsTInt32();
 	}*/

	inParam->Reset();
	outParam->Reset();

	interface_msg->Close();
	iServiceHandler->Reset();
	delete iServiceHandler;
    __UHEAP_MARKEND;
	return result;
    }


 // -----------------------------------------------------------------------------
// Ctcal_providertest::Calendar_ops16
// Example test method function to create to-do entry,send a message and change status of to-do
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_providertest::Calendar_ops16( CStifItemParser& aItem )
	{
		TInt32 result=KErrNone;
		TInt32 message_id = 0;
		TInt err;


	__UHEAP_MARK;

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

	if(AddProvToDo(inParamList, outParamList, interface, KTestCal1File, uids) == KErrNone && uids)
		{
		arruids.Append(uids);
		uids = NULL;
		}
	TInt count = arruids.Count();


	if ( arruids.Count() > 0 )
		{
			CLiwGenericParamList* inParam = &(iServiceHandler->InParamListL());
   			CLiwGenericParamList* outParam = &(iServiceHandler->OutParamListL());
			CLiwCriteriaItem* crit_msg = CLiwCriteriaItem::NewL(1, KMsgIDataSource,KMsgService);

    		crit_msg->SetServiceClass(TUid::Uid(KLiwClassBase));

    		RCriteriaArray a_msg;
   			a_msg.AppendL(crit_msg);

   		    iServiceHandler->AttachL(a_msg);

			iServiceHandler->ExecuteServiceCmdL(*crit_msg, *inParam, *outParam);

			TInt pos_msg = 0;
   			 MLiwInterface* interface_msg = NULL;

   			 outParam->FindFirst(pos_msg,KMsgIDataSource);
   			 if(pos_msg != KErrNotFound)
     		  {
       			 interface_msg = (*outParam)[pos_msg].Value().AsInterface();
        	  }

			inParam->Reset();
			outParam->Reset();

			delete crit_msg;
			crit_msg = NULL;
			a_msg.Reset();

			inParam->AppendL(TLiwGenericParam( _L8("MessageType"), TLiwVariant( _L("SMS") )));
			inParam->AppendL(TLiwGenericParam( _L8("To"), TLiwVariant( _L("9740067386") )));
			inParam->AppendL(TLiwGenericParam( _L8("BodyText"), TLiwVariant( _L("Test Message") )));

			interface_msg->ExecuteCmdL( KMsgSendCmd ,*inParam ,*outParam,0,NULL );

 			TInt index = 0;
			const TLiwGenericParam* err2 = outParam->FindFirst(index,KErrCode);
	   		result = err2->Value().AsTInt32();

	   	/*	if(!result)
	   		{
	   			inParam->Reset();
				outParam->Reset();

    			TLiwVariant content(_L8("Inbox"));
				TLiwGenericParam element1 ;
				element1.SetNameAndValueL(_L8("Type"),_L("Inbox"));
				inParam->AppendL(element1);
				content.Reset();
				element1.Reset();
   				CLiwDefaultMap* map1 = CLiwDefaultMap::NewL();
				CleanupStack::PushL(map1);

    			CLiwDefaultList* mtmtypelist = CLiwDefaultList::NewL();
    			CleanupStack::PushL(mtmtypelist);

    			TLiwVariant mmsmtm(KMessageTypeSMS);
    			mtmtypelist->AppendL(mmsmtm);
    			mmsmtm.Reset();

    			TLiwVariant add1(mtmtypelist);

    			map1->InsertL(_L8("MessageTypeList"), add1); // Mtmtype is added
    			mtmtypelist->DecRef();
    			CleanupStack::Pop(mtmtypelist);
    			add1.Reset();

    			TLiwVariant filterparam1(map1);
				TLiwGenericParam element2 ;
				element2.SetNameAndValueL(_L8("Filter"),filterparam1);
				filterparam1.Reset();

    			inParam->AppendL(element2);
				element2.Reset();

    			map1->DecRef();
    			CleanupStack::Pop(map1);

    			interface_msg->ExecuteCmdL( KMsgGetListCmd ,*inParam ,*outParam);
    			index = 0 ;
    			const TLiwGenericParam* getlistmsg_err = outParam->FindFirst(index,KErrCode);
    			if(getlistmsg_err)
					result = getlistmsg_err->Value().AsTInt32();
    			index=0;
    			const TLiwGenericParam* output1 = outParam->FindFirst( index,_L8("ReturnValue"));

    			if(!result && output1)
				{
					TInt err = output1->Value().AsTInt32();
					CLiwIterable* iterlist2 = output1->Value().AsIterable();

			    	TLiwVariant data;

	    	    	while( iterlist2->NextL(data))
					{
						const CLiwMap* res = data.AsMap();
						if ( res )
						{

							TLiwVariant mid;
							if(res->FindL(_L8("MessageId"), mid))
							{
								message_id = mid.AsTInt32();
							}
							mid.Reset();
						}
						else
							result = KErrGeneral;
			  		}
			  		data.Reset();
				}

 				if(!result && message_id)
 				{
 					//Delete the message
 					inParam->Reset();
					outParam->Reset();
 					inParam->AppendL(TLiwGenericParam( _L8("MessageId"), TLiwVariant( TInt32(message_id) )));

					interface_msg->ExecuteCmdL( KMsgDelete ,*inParam ,*outParam,0,NULL );

		 			index = 0;
					const TLiwGenericParam* err_del = outParam->FindFirst(index,KErrCode);
					result = err_del->Value().AsTInt32();
 				}
	   		}*/

			inParam->Reset();
			outParam->Reset();

			interface_msg->Close();

		}
	else
		result = KErrGeneral;

	//Update to-Do status to completed
	if(!result)
	{

		inParamList->Reset();
		outParamList->Reset();

		CLiwDefaultMap* map = CLiwDefaultMap::NewL();
		CleanupStack::PushL(map);

		map->InsertL(_L8("CalendarName"), TLiwVariant(KTestCal1File) );

		gid.Copy( arruids[1]->iGlobalUID->Des() );

		TInt lid_fetch_err = GetLocalUid(inParamList,outParamList,interface,KTestCal1File,arruids[1]->iLocalUID)	;
		if(lid_fetch_err)
		{
		   	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
		   	interface->Close();
			iServiceHandler->Reset();
			delete iServiceHandler;
			__UHEAP_MARKEND;
			return lid_fetch_err;
		}

		TBuf<10> localuid;
		localuid.Num(TInt64(arruids[1]->iLocalUID));

    	map->InsertL(_L8("LocalId"),TLiwVariant(localuid));
    	map->InsertL(_L8("Status"), TLiwVariant(_L("TodoCompleted")));

    	TLiwVariant content(_L("CalendarEntry"));
		TLiwGenericParam element1;
		element1.SetNameAndValueL(_L8("Type"),content);
		inParamList->AppendL(element1);
		content.Reset();
		element1.Reset();

		TLiwVariant filterparam(map);
		TLiwGenericParam element ;
		element.SetNameAndValueL(_L8("Item"),filterparam);
		filterparam.Reset();

		inParamList->AppendL(element);
		element.Reset();
		map->DecRef();
		CleanupStack::Pop(map);

		interface->ExecuteCmdL( KCmdAdd, *inParamList ,*outParamList );
		pos=0;
		const TLiwGenericParam* update_err = outParamList->FindFirst(pos,KErrorCode);
		if(update_err)
	   		result = update_err->Value().AsTInt32();
	}

	inParamList->Reset();
	outParamList->Reset();
	arruids.ResetAndDestroy();
	RemoveProvCalendar(inParamList, outParamList, interface, KTestCal1File);
	interface->Close();
	iServiceHandler->Reset();
	delete iServiceHandler;

    __UHEAP_MARKEND;

	return result;


    }

// -----------------------------------------------------------------------------
// Ctcal_providertest::Calendar_ops17
// Example test method function to send msg with path of cal file
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctcal_providertest::Calendar_ops17( CStifItemParser& aItem )
	{
		TInt32 result=KErrNone;
		TInt err;
		TInt32 message_id =0;

	__UHEAP_MARK;

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

	if(AddProvToDo(inParamList, outParamList, interface, KTestCal1File, uids) == KErrNone && uids)
		{
		arruids.Append(uids);
		uids = NULL;
		}
	TInt count = arruids.Count();


	if ( arruids.Count() > 0 )
		{
			CLiwGenericParamList* inParam = &(iServiceHandler->InParamListL());
   			CLiwGenericParamList* outParam = &(iServiceHandler->OutParamListL());
			CLiwCriteriaItem* crit_msg = CLiwCriteriaItem::NewL(1, KMsgIDataSource,KMsgService);

    		crit_msg->SetServiceClass(TUid::Uid(KLiwClassBase));

    		RCriteriaArray a_msg;
   			a_msg.AppendL(crit_msg);

   		    iServiceHandler->AttachL(a_msg);

			iServiceHandler->ExecuteServiceCmdL(*crit_msg, *inParam, *outParam);

			TInt pos_msg = 0;
   			 MLiwInterface* interface_msg = NULL;

   			 outParam->FindFirst(pos_msg,KMsgIDataSource);
   			 if(pos_msg != KErrNotFound)
     		  {
       			 interface_msg = (*outParam)[pos_msg].Value().AsInterface();
        	  }

			inParam->Reset();
			outParam->Reset();

			delete crit_msg;
			crit_msg = NULL;
			a_msg.Reset();

		//	inParam->AppendL(TLiwGenericParam( _L8("MessageType"), TLiwVariant( _L("MMS") )));
		//	inParam->AppendL(TLiwGenericParam( _L8("To"), TLiwVariant( _L("9740067386") )));
		//	inParam->AppendL(TLiwGenericParam( _L8("Subject"), TLiwVariant( _L("Send attachment") )));
		//	inParam->AppendL(TLiwGenericParam( _L8("Attachment"), TLiwVariant( _L("c\\private\\10003a5b\\getlistcal1") )));
			inParam->AppendL(TLiwGenericParam( _L8("MimeType"), TLiwVariant( _L("text/plain") )));

			inParam->AppendL(TLiwGenericParam( _L8("MessageType"), TLiwVariant( _L("SMS") )));
			inParam->AppendL(TLiwGenericParam( _L8("To"), TLiwVariant( _L("9008032761") )));
			inParam->AppendL(TLiwGenericParam( _L8("BodyText"), TLiwVariant( _L("C\\private\\10003a5b\\getlistcal1") )));
			//inParam->AppendL(TLiwGenericParam( _L8("Subject"), TLiwVariant( _L("Test") )));
			//inParam->AppendL(TLiwGenericParam( _L8("Attachment"), TLiwVariant( _L("C\\private\\10003a5b\\getlistcal1") )));

			interface_msg->ExecuteCmdL( KMsgSendCmd ,*inParam ,*outParam,0,NULL );

 			TInt index = 0;
			const TLiwGenericParam* err2 = outParam->FindFirst(index,KErrCode);
	   		result = err2->Value().AsTInt32();

		//	if(result == SErrBadArgumentType)
		//		result = KErrNone;

		/*	if(!result)
	   		{
	   			inParam->Reset();
				outParam->Reset();

    			TLiwVariant content(_L8("Inbox"));
				TLiwGenericParam element1 ;
				element1.SetNameAndValueL(_L8("Type"),_L("Inbox"));
				inParam->AppendL(element1);
				content.Reset();
				element1.Reset();
   				CLiwDefaultMap* map1 = CLiwDefaultMap::NewL();
				CleanupStack::PushL(map1);

    			CLiwDefaultList* mtmtypelist = CLiwDefaultList::NewL();
    			CleanupStack::PushL(mtmtypelist);

    			TLiwVariant mmsmtm(KMessageTypeSMS);
    			mtmtypelist->AppendL(mmsmtm);
    			mmsmtm.Reset();

    			TLiwVariant add1(mtmtypelist);

    			map1->InsertL(_L8("MessageTypeList"), add1); // Mtmtype is added
    			mtmtypelist->DecRef();
    			CleanupStack::Pop(mtmtypelist);
    			add1.Reset();

    			TLiwVariant filterparam1(map1);
				TLiwGenericParam element2 ;
				element2.SetNameAndValueL(_L8("Filter"),filterparam1);
				filterparam1.Reset();

    			inParam->AppendL(element2);
				element2.Reset();

    			map1->DecRef();
    			CleanupStack::Pop(map1);

    			interface_msg->ExecuteCmdL( KMsgGetListCmd ,*inParam ,*outParam);
    			index = 0 ;
    			const TLiwGenericParam* getlistmsg_err = outParam->FindFirst(index,KErrCode);
    			if(getlistmsg_err)
					result = getlistmsg_err->Value().AsTInt32();
    			index=0;
    			const TLiwGenericParam* output1 = outParam->FindFirst( index,_L8("ReturnValue"));

    			if(!result && output1)
				{
					TInt err = output1->Value().AsTInt32();
					CLiwIterable* iterlist2 = output1->Value().AsIterable();

			    	TLiwVariant data;

	    	    	while( iterlist2->NextL(data))
					{
						const CLiwMap* res = data.AsMap();
						if ( res )
						{

							TLiwVariant mid;
							if(res->FindL(_L8("MessageId"), mid))
							{
								message_id = mid.AsTInt32();
							}
							mid.Reset();
						}
						else
							result = KErrGeneral;
			  		}
			  		data.Reset();
				}

 				if(!result && message_id)
 				{
 					//Delete the message
 					inParam->Reset();
					outParam->Reset();
 					inParam->AppendL(TLiwGenericParam( _L8("MessageId"), TLiwVariant( TInt32(message_id) )));

					interface_msg->ExecuteCmdL( KMsgDelete ,*inParam ,*outParam,0,NULL );

		 			index = 0;
					const TLiwGenericParam* err_del = outParam->FindFirst(index,KErrCode);
					result = err_del->Value().AsTInt32();
 				}
	   		}*/

			inParam->Reset();
			outParam->Reset();

			interface_msg->Close();


		}
	else
		result = KErrGeneral;



	inParamList->Reset();
	outParamList->Reset();
	arruids.ResetAndDestroy();
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

    CLiwDefaultList* callist = CLiwDefaultList::NewL();
    CleanupStack::PushL(callist);

    TLiwVariant content(_L("Calendar"));
	TLiwGenericParam element1;
	element1.SetNameAndValueL(_L8("Type"),content);
	inparam->AppendL(element1);
	content.Reset();
	element1.Reset();

    TLiwVariant smsmtm(aCalendar);
    callist->AppendL(smsmtm);
    smsmtm.Reset();

    TLiwVariant add1(callist);
  //  map->InsertL(_L8("CalendarList"), add1);
  	map->InsertL(_L8("CalendarName"), TLiwVariant(aCalendar) );
    callist->DecRef();
    CleanupStack::Pop(callist);
    add1.Reset();

    TLiwVariant filterparam(map);
	TLiwGenericParam element ;
	element.SetNameAndValueL(_L8("Data"),filterparam);
	filterparam.Reset();

	inparam->AppendL(element);
	element.Reset();
    map->DecRef();
    CleanupStack::Pop(map);

	interface->ExecuteCmdL( KCmdDelete ,*inparam,*outparam );
    TInt pos = 0 ;

    const TLiwGenericParam* output = outparam->FindFirst( pos,_L8("ErrorCode"));
	TInt32 err = 0;
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

	interface->ExecuteCmdL( KCmdAdd, *inparam,*outparam );
    TInt pos = 0 ;

    const TLiwGenericParam* output = outparam->FindFirst( pos,_L8("ErrorCode"));
	TInt32 err = 0;
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
	repeatmap->InsertL(_L8("UntilDate"), TLiwVariant(TTime(TDateTime(2007,ENovember,0,10,0,0,0))));
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


	 interface->ExecuteCmdL( KCmdAdd, *inparam,*outparam );
    TInt pos = 0 ;

    cells = User::CountAllocCells();

    const TLiwGenericParam* output = outparam->FindFirst( pos,_L8("ErrorCode"));

	cells = User::CountAllocCells();
	TInt32 err = 0;
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
			//	GetLocalUid( uidval, uidset->iLocalUID );

				uidset->iGlobalUID = HBufC8::NewL(uidval.Length());
				TPtr8 tmp = uidset->iGlobalUID->Des();
			//	GetGlobalUid( uidval, tmp );
				tmp.Copy(uidval);
				}
			else
				err = -1;
			}
		}
	cells = User::CountAllocCells();
	inparam->Reset();
	outparam->Reset();
	cells = User::CountAllocCells();


	return err;
	};


//TInt GetLocalUid( CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar,const TDesC& type, TCalLocalUid& aOutLocalUid )
TInt GetLocalUid( CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar,TCalLocalUid& aOutLocalUid )
	{
	TInt ret = 0;
	TInt pos = 0;
	aOutLocalUid = 0;

	inparam->Reset();
	outparam->Reset();

	TLiwGenericParam dsNameParam(KContentType, TLiwVariant(_L("CalendarEntry")));
	inparam->AppendL(dsNameParam);

	CLiwDefaultMap* map1 = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map1);

	map1->InsertL(_L8("CalendarName"), TLiwVariant(aCalendar) );
	map1->InsertL(_L8("id"),TLiwVariant(gid));

	TLiwVariant filterparam1(map1);
	TLiwGenericParam element2 ;
	element2.SetNameAndValueL(_L8("Filter"),filterparam1);
	filterparam1.Reset();

	inparam->AppendL(element2);
	element2.Reset();

	map1->DecRef();
	CleanupStack::Pop(map1);

	interface->ExecuteCmdL( KCmdGetList ,*inparam ,*outparam);

	const TLiwGenericParam* getlist_err = outparam->FindFirst(pos,KErrorCode);
   	if(getlist_err)
   		ret = getlist_err->Value().AsTInt32();
   	pos=0;
	const TLiwGenericParam* output = outparam->FindFirst( pos,_L8("ReturnValue"));
	TInt item_found = 0;

	if(!ret && output )
	{
		CLiwIterable* iterlist = output->Value().AsIterable();
    	TLiwVariant data;
		while( iterlist->NextL(data))
		{
			const CLiwMap* res = data.AsMap();
			if ( res )
			{
				TLiwVariant new_data;
				if(res->FindL(_L8("LocalId"), new_data))
				{
					TPtrC temp;
					temp.Set(new_data.AsDes());
					TBuf<40> buf;
					buf.Copy(temp);
				//	iLog->Log(_L("Local uid"));
				//	iLog->Log(buf);
					TLex lex(temp);
					TInt32 num;
					if(lex.Val(num) == KErrNone)
						aOutLocalUid = TCalLocalUid(num);
				}
				else
					ret = KErrGeneral;

				new_data.Reset();
			}
		}
		data.Reset();
	}

	inparam->Reset();
	outparam->Reset();
	return ret;
	}


void GetGlobalUid( const TDesC& aGlobalUid, TDes8& aOutGlobalUid )
	{
	if( aGlobalUid.Length() )
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
		}
	}


TInt AddAppointmentProvLocal(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset)
	{

	inparam->Reset();
	outparam->Reset();
	TInt cells = User::CountAllocCells();


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
	map->InsertL(_L8("SeqNum"), TLiwVariant(1));
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
	interface->ExecuteCmdL( KCmdAdd, *inparam,*outparam );
    TInt pos = 0 ;

    cells = User::CountAllocCells();

    const TLiwGenericParam* output = outparam->FindFirst( pos,_L8("ErrorCode"));

	cells = User::CountAllocCells();
	TInt32 err = 0;
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
			//	GetLocalUid( uidval, uidset->iLocalUID );

				uidset->iGlobalUID = HBufC8::NewL(uidval.Length());
				TPtr8 tmp = uidset->iGlobalUID->Des();
			//	GetGlobalUid( uidval, tmp );
				tmp.Copy(uidval);

				}
			else
				err = -1;
			}
		}
	cells = User::CountAllocCells();
	inparam->Reset();
	outparam->Reset();
	cells = User::CountAllocCells();


	return err;
    }

TInt AddProvToDo(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset)
	{
	inparam->Reset();
	outparam->Reset();

	TInt cells = User::CountAllocCells();


   	CLiwDefaultMap* map = CLiwDefaultMap::NewL();
	CleanupStack::PushL(map);

    TLiwVariant content(_L("CalendarEntry"));
	TLiwGenericParam element1;
	element1.SetNameAndValueL(_L8("Type"),content);
	inparam->AppendL(element1);
	content.Reset();
	element1.Reset();


    map->InsertL(_L8("CalendarName"), TLiwVariant(aCalendar) );
	map->InsertL(_L8("Type"), TLiwVariant( _L("ToDo")  ));
	map->InsertL(_L8("EndTime"), TLiwVariant(TTime(TDateTime(2007,EOctober,25,0,0,0,0))));
	map->InsertL(_L8("Replication"), TLiwVariant(_L("Private")));
	map->InsertL(_L8("Description"), TLiwVariant(_L("To do")));
	map->InsertL(_L8("Status"), TLiwVariant(_L("TodoNeedsAction")));


	TLiwGenericParam element;
	element.SetNameAndValueL(_L8("Item"),TLiwVariant(map));

	inparam->AppendL(element);
	element.Reset();
    map->DecRef();
    CleanupStack::Pop(map);

    cells = User::CountAllocCells();

	//TInt err;
	interface->ExecuteCmdL( KCmdAdd, *inparam,*outparam );
    TInt pos = 0 ;

    cells = User::CountAllocCells();

    const TLiwGenericParam* output = outparam->FindFirst( pos,_L8("ErrorCode"));

	cells = User::CountAllocCells();
	TInt32 err = 0;
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
			//	GetGlobalUid( uidval, tmp );
				tmp.Copy(uidval);

				}
			else
				err = -1;
			}
		}
	cells = User::CountAllocCells();
	inparam->Reset();
	outparam->Reset();
	cells = User::CountAllocCells();


	return err;
	}


TInt AddProvEvent(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface, const TDesC& aCalendar, TUIDSet*& uidset)
	{
	inparam->Reset();
	outparam->Reset();

	TInt cells = User::CountAllocCells();


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
	interface->ExecuteCmdL( KCmdAdd, *inparam,*outparam );
    TInt pos = 0 ;

    cells = User::CountAllocCells();

    const TLiwGenericParam* output = outparam->FindFirst( pos,_L8("ErrorCode"));

	cells = User::CountAllocCells();
	TInt32 err = 0;
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
			//	GetGlobalUid( uidval, tmp );
				tmp.Copy(uidval);

				}
			else
				err = -1;
			}
		}
	cells = User::CountAllocCells();
	inparam->Reset();
	outparam->Reset();
	cells = User::CountAllocCells();


	return err;
	};

