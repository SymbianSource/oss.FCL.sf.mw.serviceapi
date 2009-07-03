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
#include <f32file.h>
#include <StifParser.h>
#include <e32std.h>
#include <Stiftestinterface.h>
#include <liwgenericparam.h>
#include <liwservicehandler.h>
#include <liwvariant.h>
#include <epos_cposlandmarkdatabase.h>
#include <epos_cposlandmark.h>
#include <epos_cposlandmarkencoder.h>
#include <epos_cposlmcategorymanager.h>
#include <EPos_HPosLmDatabaseInfo.h>
#include <EPos_CPosLmDatabaseManager.h>
#include <lbsposition.h> 
#include "landmarkliwparams.hrh"
#include "tlandmark_provider.h"
#include "getlist.h"
#include "serviceerrno.h"

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

TInt AddLandMark(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface,const TDesC &landmark_name,const TDesC &landmark_description);
TInt AddCategory(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface,const TDesC &category_name);     
void GetCatId(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface,const TDesC &category_name);
void GetLandMarkId(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface,const TDesC &landmark_name,const TDesC &landmark_description);
TInt RemoveLandmark(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface);
TInt RemoveCategory(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface);

TBuf<40> landmark_id;
TBuf<40> category_id;
_LIT8(KMsgService,"Service.Messaging");
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

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// Ctlandmark_provider::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void Ctlandmark_provider::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// Ctlandmark_provider::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt Ctlandmark_provider::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "TestNoTid", Ctlandmark_provider::TestNoTid ),
        ENTRY( "TestInvalidTid", Ctlandmark_provider::TestInvalidTid ),
        ENTRY( "TestTidByorder", Ctlandmark_provider::TestTidByorder ),
        ENTRY( "TestTidByPos", Ctlandmark_provider::TestTidByPos ),
        ENTRY( "TestHugeTid", Ctlandmark_provider::TestHugeTid ),
        ENTRY( "TestTidInvalidType", Ctlandmark_provider::TestTidInvalidType ),
        ENTRY( "TestCancelInvalidCmdOption", Ctlandmark_provider::TestCancelInvalidCmdOption ),
        
        ENTRY( "TestAddLMVarByOrder", Ctlandmark_provider::TestAddLMVarByOrder ),
        ENTRY( "TestAddLMVarByPos", Ctlandmark_provider::TestAddLMVarByPos ),
        ENTRY( "TestAddCTVarByOrder", Ctlandmark_provider::TestAddCTVarByOrder ),
        ENTRY( "TestAddCTVarByPos", Ctlandmark_provider::TestAddCTVarByPos ),
        
        ENTRY( "TestGetListLMVarByOrder", Ctlandmark_provider::TestGetListLMVarByOrder ),
        ENTRY( "TestGetListLMVarByPos", Ctlandmark_provider::TestGetListLMVarByPos ),
        ENTRY( "TestGetListCTVarByOrder", Ctlandmark_provider::TestGetListCTVarByOrder ),
        ENTRY( "TestGetListCTVarByPos", Ctlandmark_provider::TestGetListCTVarByPos ),
        
        ENTRY( "TestRemoveLMVarByOrder", Ctlandmark_provider::TestRemoveLMVarByOrder ),
        ENTRY( "TestRemoveLMVarByPos", Ctlandmark_provider::TestRemoveLMVarByPos ),
        ENTRY( "TestRemoveCTVarByOrder", Ctlandmark_provider::TestRemoveCTVarByOrder ),
        ENTRY( "TestRemoveCTVarByPos", Ctlandmark_provider::TestRemoveCTVarByPos ),
        
        ENTRY( "TestExportVarByOrder", Ctlandmark_provider::TestExportVarByOrder ),
        ENTRY( "TestExportVarByPos", Ctlandmark_provider::TestExportVarByPos ),
        
        ENTRY( "TestImportVarByOrder", Ctlandmark_provider::TestImportVarByOrder ),
        ENTRY( "TestImportVarByPos", Ctlandmark_provider::TestImportVarByPos ),
        
        ENTRY( "TestOrganiseVarByOrder", Ctlandmark_provider::TestOrganiseVarByOrder ),
        ENTRY( "TestOrganiseVarByPos", Ctlandmark_provider::TestOrganiseVarByPos ),
        
        ENTRY( "TestInvalidServiceDataSourceCombination", Ctlandmark_provider::TestInvalidServiceDataSourceCombination ),
        
        ENTRY( "TestAddSyncAsyncbitcheck", Ctlandmark_provider::TestAddSyncAsyncbitcheck ),
        ENTRY( "TestGetListSyncAsyncbitcheck", Ctlandmark_provider::TestGetListSyncAsyncbitcheck ),
        
        ENTRY( "TestGetListCancel", Ctlandmark_provider::TestGetListCancel ),
        ENTRY( "GetListStressTest", Ctlandmark_provider::GetListStressTest ),
        ENTRY( "GetListIteratorTestLM", Ctlandmark_provider::GetListIteratorTestLM ),
        ENTRY( "GetListIteratorTestCT", Ctlandmark_provider::GetListIteratorTestCT ),
        
        ENTRY( "TestTemplateInvalidCase", Ctlandmark_provider::TestTemplateInvalidCase ),
        ENTRY( "TestTemplateLM", Ctlandmark_provider::TestTemplateLM ),
        ENTRY( "TestTemplateCT", Ctlandmark_provider::TestTemplateCT ),
        
        ENTRY( "TestGetListCTWithSortOrder", Ctlandmark_provider::TestGetListCTWithSortOrder ),
        ENTRY( "TestAddMultipleLM", Ctlandmark_provider::TestAddMultipleLM ),
        
        ENTRY( "ImportDBTypeIdCheck", Ctlandmark_provider::ImportDBTypeIdCheck ),
        ENTRY( "ImportNullDB", Ctlandmark_provider::ImportNullDB ),
        
        ENTRY( "AddSyncBitCheck", Ctlandmark_provider::AddSyncBitCheck ),
        ENTRY( "CombineAPI", Ctlandmark_provider::CombineAPI ),
        
        ENTRY( "AddVerifyTimeStamp", Ctlandmark_provider::AddVerifyTimeStamp ),
        
        ENTRY( "ExportHugeFilename", Ctlandmark_provider::ExportHugeFilename ),
        ENTRY( "ExportNullFilename", Ctlandmark_provider::ExportNullFilename ),
        ENTRY( "ExportInvalidFilename", Ctlandmark_provider::ExportInvalidFilename ),
        
        //ADD NEW ENTRY HERE

        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// Ctlandmark_provider::ExportInvalidFilename
// To test export with invalid file name
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctlandmark_provider::ExportInvalidFilename( CStifItemParser& aItem )
    { 
     __UHEAP_MARK;     
    _LIT(KName,"exportinvalidfilename");
    _LIT(KDescription,"export with invalid file name string");
     _LIT(KFilePath, "test");
     _LIT(KPosMimeType, "application/vnd.nokia.landmarkcollection+xml");
 
    TInt32 result = KErrNone;
    TBuf<40> buf;
    TInt add_flag =0;  
 
 /*	RFile LogResult;
    RFs LogResultSession;
    User::LeaveIfError(LogResultSession.Connect());
    if(LogResult.Open(LogResultSession ,KFilePath , EFileWrite | EFileShareAny )  != KErrNotFound)
        {
        LogResult.Close();

		LogResultSession.Delete(KFilePath);
		
        LogResultSession.Close();
        }
    
    LogResult.Close();
    LogResultSession.Close();*/
    
    
    
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    MLiwInterface* interface = NULL;
    CLiwGenericParamList* inps = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outps = &(iServiceHandler->OutParamListL());

 	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);

	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray a;
	a.AppendL(crit);    
	
	iServiceHandler->AttachL(a);
	iServiceHandler->ExecuteServiceCmdL(*crit, *inps, *outps); 

	a.Reset();
	delete crit;
	
	TInt pos = 0;

	outps->FindFirst( pos, KIDataSource );
	if(pos != KErrNotFound)
		{
		interface = (*outps)[pos].Value().AsInterface();	
		}

	outps->Reset();
	inps->Reset();
	
	TLiwGenericParam param;
	TInt index = 0;
    
    result = AddLandMark(inps,outps,interface,KName,KDescription);
    
    if(!result)
    {
    	add_flag = 1;
    	GetLandMarkId(inps,outps,interface,KName,KDescription);    
	
		// Call Export 
    	
   		CLiwMap* export_map = CLiwDefaultMap::NewL();
   		
    	CLiwList* landmarkIdList = CLiwDefaultList::NewL();
    	landmarkIdList->AppendL(TLiwVariant(landmark_id));       	   
    	
   		export_map->InsertL(KDestinationFile,TLiwVariant(KFilePath));
        export_map->InsertL(KMimeType,TLiwVariant(KPosMimeType));
        export_map->InsertL(KIdList,TLiwVariant(landmarkIdList));
    	landmarkIdList->DecRef();       	
    	
    	param.SetNameAndValueL(KDataFields,TLiwVariant(export_map));
    	inps->AppendL(param);
    	param.Reset();
    
    	param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
    	inps->AppendL(param);
    	param.Reset();
    	
    	interface->ExecuteCmdL(KExport,*inps,*outps,0,0);
    	export_map->DecRef();    	
    	index=0;
    	
    	const TLiwGenericParam* export_err = outps->FindFirst(index,KErrorCode);
    	if(export_err)
    	result = export_err->Value().AsTInt32();         
    }    
    
    iLog->Log(_L("result value of export with invalid file name : %D"),result);
    
    outps->Reset();
	inps->Reset();
	if(add_flag)
    	RemoveLandmark(inps,outps,interface);  	    	
   
    interface->Close();	
    
    if(result == SErrPathNotFound)
    	result = KErrNone;
    
	delete iServiceHandler;  
	__UHEAP_MARKEND;
  	return result;
    }     
    
    
    
// -----------------------------------------------------------------------------
// Ctlandmark_provider::ExportNullFilename
// To test export with NUll file name
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctlandmark_provider::ExportNullFilename( CStifItemParser& aItem )
    { 
     __UHEAP_MARK;     
    _LIT(KName,"exportnullfilename");
    _LIT(KDescription,"export with null file name string");
    _LIT(KPosMimeType, "application/vnd.nokia.landmarkcollection+xml");
 
    TInt32 result = KErrNone;
    TBuf<40> buf;
    TInt add_flag =0;  
 
 /*	RFile LogResult;
    RFs LogResultSession;
    User::LeaveIfError(LogResultSession.Connect());
    if(LogResult.Open(LogResultSession ,KFilePath , EFileWrite | EFileShareAny )  != KErrNotFound)
        {
        LogResult.Close();

		LogResultSession.Delete(KFilePath);
		
        LogResultSession.Close();
        }
    
    LogResult.Close();
    LogResultSession.Close();*/
    
    
    
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    MLiwInterface* interface = NULL;
    CLiwGenericParamList* inps = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outps = &(iServiceHandler->OutParamListL());

 	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);

	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray a;
	a.AppendL(crit);    
	
	iServiceHandler->AttachL(a);
	iServiceHandler->ExecuteServiceCmdL(*crit, *inps, *outps); 

	a.Reset();
	delete crit;
	
	TInt pos = 0;

	outps->FindFirst( pos, KIDataSource );
	if(pos != KErrNotFound)
		{
		interface = (*outps)[pos].Value().AsInterface();	
		}

	outps->Reset();
	inps->Reset();
	
	TLiwGenericParam param;
	TInt index = 0;
    
    result = AddLandMark(inps,outps,interface,KName,KDescription);
    
    if(!result)
    {
    	add_flag = 1;
    	GetLandMarkId(inps,outps,interface,KName,KDescription);    
	
		// Call Export 
    	
   		CLiwMap* export_map = CLiwDefaultMap::NewL();
   		
    	CLiwList* landmarkIdList = CLiwDefaultList::NewL();
    	landmarkIdList->AppendL(TLiwVariant(landmark_id));       	   
    	
   		export_map->InsertL(KDestinationFile,TLiwVariant(KNullDesC));
        export_map->InsertL(KMimeType,TLiwVariant(KPosMimeType));
        export_map->InsertL(KIdList,TLiwVariant(landmarkIdList));
    	landmarkIdList->DecRef();       	
    	
    	param.SetNameAndValueL(KDataFields,TLiwVariant(export_map));
    	inps->AppendL(param);
    	param.Reset();
    
    	param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
    	inps->AppendL(param);
    	param.Reset();
    	
    	interface->ExecuteCmdL(KExport,*inps,*outps,0,0);
    	export_map->DecRef();    	
    	index=0;
    	
    	const TLiwGenericParam* export_err = outps->FindFirst(index,KErrorCode);
    	if(export_err)
    	result = export_err->Value().AsTInt32();         
    }    
    
    iLog->Log(_L("result value of export with null file name : %D"),result);
    
    outps->Reset();
	inps->Reset();
	if(add_flag)
    	RemoveLandmark(inps,outps,interface);  	    	
   
    interface->Close();	
    
    if(result == SErrBadArgumentType || result == SErrInvalidServiceArgument)
    	result = KErrNone;
    
	delete iServiceHandler;  
	__UHEAP_MARKEND;
  	return result;
    }     
    
    
// -----------------------------------------------------------------------------
// Ctlandmark_provider::ExportHugeFilename
// To test export with huge file name
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctlandmark_provider::ExportHugeFilename( CStifItemParser& aItem )
    { 
     __UHEAP_MARK;     
    _LIT(KName,"exporthugefilename");
    _LIT(KDescription,"export with huge file name string");
     _LIT(KFilePath, "HiThisisRoshanfromNokiaIndiaPvtLtd.IhopeyouaredoingfinebecauseIalwaysdofineandexpectthesamefromyou.Thisbringstothepointthatwhyiaskedyouthisstupidquestionwheniknowthaturfine.Nokiaisagreatcompanyanditpresentsgreatopportunity##$$$$&&&-=+++~~~@@@@@sothatsitfrommeletscontinueontheworkfortodayok");
     _LIT(KPosMimeType, "application/vnd.nokia.landmarkcollection+xml");
 
    TInt32 result = KErrNone;
    TBuf<40> buf;
    TInt add_flag =0;  
 
 /*	RFile LogResult;
    RFs LogResultSession;
    User::LeaveIfError(LogResultSession.Connect());
    if(LogResult.Open(LogResultSession ,KFilePath , EFileWrite | EFileShareAny )  != KErrNotFound)
        {
        LogResult.Close();

		LogResultSession.Delete(KFilePath);
		
        LogResultSession.Close();
        }
    
    LogResult.Close();
    LogResultSession.Close();*/
    
    
    
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    MLiwInterface* interface = NULL;
    CLiwGenericParamList* inps = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outps = &(iServiceHandler->OutParamListL());

 	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);

	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray a;
	a.AppendL(crit);    
	
	iServiceHandler->AttachL(a);
	iServiceHandler->ExecuteServiceCmdL(*crit, *inps, *outps); 

	a.Reset();
	delete crit;
	
	TInt pos = 0;

	outps->FindFirst( pos, KIDataSource );
	if(pos != KErrNotFound)
		{
		interface = (*outps)[pos].Value().AsInterface();	
		}

	outps->Reset();
	inps->Reset();
	
	TLiwGenericParam param;
	TInt index = 0;
    
    result = AddLandMark(inps,outps,interface,KName,KDescription);
    
    if(!result)
    {
    	add_flag = 1;
    	GetLandMarkId(inps,outps,interface,KName,KDescription);    
	
		// Call Export 
    	
   		CLiwMap* export_map = CLiwDefaultMap::NewL();
   		
    	CLiwList* landmarkIdList = CLiwDefaultList::NewL();
    	landmarkIdList->AppendL(TLiwVariant(landmark_id));       	   
    	
   		export_map->InsertL(KDestinationFile,TLiwVariant(KFilePath));
        export_map->InsertL(KMimeType,TLiwVariant(KPosMimeType));
        export_map->InsertL(KIdList,TLiwVariant(landmarkIdList));
    	landmarkIdList->DecRef();       	
    	
    	param.SetNameAndValueL(KDataFields,TLiwVariant(export_map));
    	inps->AppendL(param);
    	param.Reset();
    
    	param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
    	inps->AppendL(param);
    	param.Reset();
    	
    	interface->ExecuteCmdL(KExport,*inps,*outps,0,0);
    	export_map->DecRef();    	
    	index=0;
    	
    	const TLiwGenericParam* export_err = outps->FindFirst(index,KErrorCode);
    	if(export_err)
    	{
    		result = export_err->Value().AsTInt32(); 
    		index=1;
    		const TLiwGenericParam* err_msg = outps->FindFirst(index,KErrorMsg);
    		if(err_msg)
    			iLog->Log(_L("err msg of export with huge file name : %S"),err_msg->Value().AsDes());			    		   
    	}
    }    
    
 //   iLog->Log("result value of export with huge file name :  %D",result);
	  iLog->Log(_L("result value of export with huge file name : %D"),result);
		    
    outps->Reset();
	inps->Reset();
	if(add_flag)
    	RemoveLandmark(inps,outps,interface);  	    	
   
    interface->Close();	
    
    if(result == SErrBadArgumentType || result == SErrInvalidServiceArgument)
    	result = KErrNone;
    
	delete iServiceHandler;  
	__UHEAP_MARKEND;
  	return result;
    }     
    
    
    
// -----------------------------------------------------------------------------
// Ctlandmark_provider::AddVerifyTimeStamp
// Add landmark with a timestamp value for position and verify the same
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctlandmark_provider::AddVerifyTimeStamp( CStifItemParser& aItem )
 {
 	__UHEAP_MARK;
	_LIT(KName,"TSlandmark1");
	_LIT(KDesc,"Landmark with time stamp - case one");
   
    TInt32 result = KErrNone;
    TReal32 acc_data = 22.7;
    TInt item_count_before_reset = 0;
    TInt item_count_after_reset = 0;
    TBuf<40> first_cid_before_reset;
    TBuf<40> first_cid_after_reset;
    TLiwGenericParam param;    

    
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    MLiwInterface* interface = NULL;
    CLiwGenericParamList* inps = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outps = &(iServiceHandler->OutParamListL());

 	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);

	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray a;
	a.AppendL(crit);    
	
	iServiceHandler->AttachL(a);
	iServiceHandler->ExecuteServiceCmdL(*crit, *inps, *outps); 

	a.Reset();
	delete crit;
	
	TInt pos = 0;
	
	outps->FindFirst( pos, KIDataSource );
	if(pos != KErrNotFound)
		{
		interface = (*outps)[pos].Value().AsInterface();	
		}

	outps->Reset();
	inps->Reset();
	
	CLiwMap* landmarkMap = CLiwDefaultMap::NewL();
	CLiwMap* pos_map = CLiwDefaultMap::NewL();
	pos_map->InsertL(KVAccuracy,TLiwVariant(acc_data));
	TTime settime(TDateTime(2008,EApril,16,16,15,0,0));
	pos_map->InsertL(KTStamp,TLiwVariant(TTime(TDateTime(2008,EApril,16,16,15,0,0))));
	
	landmarkMap->InsertL(KLandmarkName,TLiwVariant(KName));
      
    //description
    landmarkMap->InsertL(KLandmarkDesc,TLiwVariant(KDesc));
    
    landmarkMap->InsertL(KLandmarkPosition,TLiwVariant(pos_map));
    pos_map->DecRef();
    
    param.SetNameAndValueL(KDataFields,TLiwVariant(landmarkMap));
    inps->AppendL(param);
    param.Reset();       
    
    param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
    inps->AppendL(param);
    param.Reset();
    
    interface->ExecuteCmdL(KAdd,*inps,*outps,0,0);
    landmarkMap->DecRef();    
    
    pos=0; 
    const TLiwGenericParam* err = outps->FindFirst(pos,KErrorCode);
    if(err)
    	result = err->Value().AsTInt32();
    
    outps->Reset();
	inps->Reset();
    
    if(!result)
    {
    	outps->Reset();
		inps->Reset();
		
    	CLiwMap* getlistlandmark_map = CLiwDefaultMap::NewL();      
      	getlistlandmark_map->InsertL(KLandmarkName,TLiwVariant(KName));     
      	getlistlandmark_map->InsertL(KLandmarkDesc,TLiwVariant(KDesc));       
    
    	param.SetNameAndValueL(KFilter,TLiwVariant(getlistlandmark_map));
    	inps->AppendL(param);
    	param.Reset();
    
    	param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
    	inps->AppendL(param);
    	param.Reset();
    	
    	interface->ExecuteCmdL(KGetList,*inps,*outps,0,0);
    	getlistlandmark_map->DecRef();
    
    	pos=0;
    	const TLiwGenericParam* getlist_err = outps->FindFirst(pos,KErrorCode);
    	if(getlist_err)
    		result = getlist_err->Value().AsTInt32();
    }    
      	
    
	if(!result)
	{
		// Iterate through the list
		pos=0;
		const TLiwGenericParam* output = outps->FindFirst( pos,_L8("ReturnValue"));
			
		if(output)     
		{
			CLiwIterable* iterlist = output->Value().AsIterable();

		    TLiwVariant data;
	    	      
		    while( iterlist->NextL(data))
			{
				item_count_before_reset++;
				const CLiwMap* res = data.AsMap();
				if ( res )
				{
					TLiwVariant new_data;
					if(res->FindL(KLandmarkPosition, new_data))
					{
						const CLiwMap* p_map = new_data.AsMap();
						if(p_map)
						{
							TLiwVariant pos_data;
							if(p_map->FindL(KTStamp, pos_data))
							{
								if(pos_data.AsTTime() != settime)
									result = KErrGeneral;
							}
							pos_data.Reset();
						}
					}
					new_data.Reset();
				}
			 }			  		
			 data.Reset();			 
		}
		
		outps->Reset();
		inps->Reset();	
    }
    
    
    RemoveLandmark(inps,outps,interface);
    interface->Close();
	delete iServiceHandler;
	__UHEAP_MARKEND;
	return result;
 }
 
     
// -----------------------------------------------------------------------------
// Ctlandmark_provider::CombineAPI
// To combine add/getlist/organise/delete api
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctlandmark_provider::CombineAPI( CStifItemParser& aItem )
    {      
    __UHEAP_MARK; 
    _LIT(KName,"combine");
    _LIT(KCatName,"cat_for_combine");
    _LIT(KDescription,"combine_api");
      
    TInt32 result = KErrNone;
    TBuf<40> buf;
    TInt add_lmflag =0;  
 	TInt add_ctflag =0;  
    
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    MLiwInterface* interface = NULL;
    CLiwGenericParamList* inps = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outps = &(iServiceHandler->OutParamListL());

 	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);

	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray a;
	a.AppendL(crit);    
	
	iServiceHandler->AttachL(a);
	iServiceHandler->ExecuteServiceCmdL(*crit, *inps, *outps); 

	a.Reset();
	delete crit;
	
	TInt pos = 0;

	outps->FindFirst( pos, KIDataSource );
	if(pos != KErrNotFound)
		{
		interface = (*outps)[pos].Value().AsInterface();	
		}

	outps->Reset();
	inps->Reset();
	
	TLiwGenericParam param;
	TInt index = 0;
    
    result = AddLandMark(inps,outps,interface,KName,KDescription);
    
    if(!result)
    {
    	add_lmflag = 1;
    	AddCategory(inps,outps,interface,KCatName);
    	add_ctflag=1;
    	GetLandMarkId(inps,outps,interface,KName,KDescription);    
	    GetCatId(inps,outps,interface,KCatName);    
		
		CLiwMap* organise_map = CLiwDefaultMap::NewL();      
    	organise_map->InsertL(KId,TLiwVariant(category_id));
    	    	
    	CLiwList* landmarkIdList = CLiwDefaultList::NewL();
    	landmarkIdList->AppendL(TLiwVariant(landmark_id));       	   
    	organise_map->InsertL(KIdList,TLiwVariant(landmarkIdList));
    	landmarkIdList->DecRef();  
    	    	
    	param.SetNameAndValueL(KDataFields,TLiwVariant(organise_map));
    	inps->AppendL(param);
    	param.Reset();
    
   		param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
   		inps->AppendL(param);
   		param.Reset();
   		
   		param.SetNameAndValueL(KOperationType,TLiwVariant(KAssociate));
   		inps->AppendL(param);
   		param.Reset();
    	
   		interface->ExecuteCmdL(KOrganise,*inps,*outps,0,0);
   		organise_map->DecRef();
    
   		const TLiwGenericParam* organise_err = outps->FindFirst(pos,KErrorCode);
   		if(organise_err)
   			result = organise_err->Value().AsTInt32();   
    
    	
    	outps->Reset();
		inps->Reset();        
    }    
    
  	if(add_lmflag)
    	RemoveLandmark(inps,outps,interface);  	    	
  	if(add_ctflag)
   		RemoveCategory(inps,outps,interface);  	    	
  	
    interface->Close();	
	delete iServiceHandler;
	__UHEAP_MARKEND;
   	return result;
    }     
// -----------------------------------------------------------------------------
// Ctlandmark_provider::AddSyncBitCheck
// To test add for sync bit check
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctlandmark_provider::AddSyncBitCheck( CStifItemParser& aItem )
    {       
    _LIT(KName,"xyz");
    _LIT(KDescription,"123");
    
    TInt32 result = KErrNone;
    TInt count = 0;
    __UHEAP_MARK;
    
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    MLiwInterface* interface = NULL;
    CLiwGenericParamList* inps = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outps = &(iServiceHandler->OutParamListL());

 	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);

	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray a;
	a.AppendL(crit);    
	
	iServiceHandler->AttachL(a);
	iServiceHandler->ExecuteServiceCmdL(*crit, *inps, *outps); 

	a.Reset();
	delete crit;
	
	TInt pos = 0;

	outps->FindFirst( pos, KIDataSource );
	if(pos != KErrNotFound)
		{
		interface = (*outps)[pos].Value().AsInterface();	
		}

	outps->Reset();
	inps->Reset();
	
	
    TPosition locale;
    locale.SetCurrentTime();    
    
    CLiwMap* landmarkMap = CLiwDefaultMap::NewL();
    TLiwGenericParam param;    
         
    //name
    landmarkMap->InsertL(KLandmarkName,TLiwVariant(KName));
      
    //description
    landmarkMap->InsertL(KLandmarkDesc,TLiwVariant(KDescription));
    
    param.SetNameAndValueL(KDataFields,TLiwVariant(landmarkMap));
    inps->AppendL(param);
    param.Reset();       
    
    param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
    inps->AppendL(param);
    param.Reset();
    
    TInt32 temp = 0;
    CActiveSchedulerWait *schedular;
    schedular = new(ELeave) CActiveSchedulerWait();
    CCalCallback *Callback = CCalCallback::NewL(schedular, temp);
    interface->ExecuteCmdL(KAdd,*inps,*outps,KLiwOptASyncronous,Callback);
    delete Callback;
    delete schedular;
    landmarkMap->DecRef();
    
    TInt index = 0;
    
    const TLiwGenericParam* err = outps->FindFirst(index,KErrorCode);
    if(err)
    	result = err->Value().AsTInt32();
    
    outps->Reset();
	inps->Reset();    	      
	
    interface->Close();	
	delete iServiceHandler;
  
  	__UHEAP_MARKEND;
  	if(result == 1000)
  		result = 0;
  	return result;
    }
    
// -----------------------------------------------------------------------------
// Ctlandmark_provider::TestCancelInvalidCmdOption
// To test cancel passing invalid cmd type
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctlandmark_provider::TestCancelInvalidCmdOption( CStifItemParser& aItem )
    {
	__UHEAP_MARK;
  	CTestAsync* test = CTestAsync::NewL(10);
	test->Start();
	TInt32 Err = test->Result();
	delete test;
	__UHEAP_MARKEND;
	if(Err == 1000)
		Err = 0;	
	return Err;
    }
     
// -----------------------------------------------------------------------------
// Ctlandmark_provider::TestTidInvalidType
// To test cancel passing invalid tid type
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctlandmark_provider::TestTidInvalidType( CStifItemParser& aItem )
    {
	__UHEAP_MARK;
  	CTestAsync* test = CTestAsync::NewL(9);
	test->Start();
	TInt32 Err = test->Result();
	delete test;
	__UHEAP_MARKEND;
	if(Err == 1002)
		Err = 0;	
	return Err;
    }
    
     
// -----------------------------------------------------------------------------
// Ctlandmark_provider::TestHugeTid
// To test cancel passing huge tid value
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctlandmark_provider::TestHugeTid( CStifItemParser& aItem )
    {
	__UHEAP_MARK;
  	CTestAsync* test = CTestAsync::NewL(8);
	test->Start();
	TInt32 Err = test->Result();
	delete test;
	__UHEAP_MARKEND;	
	return Err;
    }
       
// -----------------------------------------------------------------------------
// Ctlandmark_provider::TestTidByPos
// To test cancel passing tid By position
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctlandmark_provider::TestTidByPos( CStifItemParser& aItem )
    {
	__UHEAP_MARK;
  	CTestAsync* test = CTestAsync::NewL(7);
	test->Start();
	TInt32 Err = test->Result();
	delete test;
	__UHEAP_MARKEND;	
	return Err;
    }
    
    
    
// -----------------------------------------------------------------------------
// Ctlandmark_provider::TestTidByorder
// To test cancel passing tid By order
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctlandmark_provider::TestTidByorder( CStifItemParser& aItem )
    {
	__UHEAP_MARK;
  	CTestAsync* test = CTestAsync::NewL(6);
	test->Start();
	TInt32 Err = test->Result();
	delete test;
	__UHEAP_MARKEND;	
	return Err;
    }
    
// -----------------------------------------------------------------------------
// Ctlandmark_provider::ImportNullDB
// To test import with Null as database Uri
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctlandmark_provider::ImportNullDB( CStifItemParser& aItem )
    { 
     __UHEAP_MARK;     
    _LIT(KName,"ImportNullDB");
    _LIT(KDescription,"ImportDb Null");
     _LIT(KFilePath, "c:\\importNullDB.lmx");
     _LIT(KPosMimeType, "application/vnd.nokia.landmarkcollection+xml");
 
    TInt32 result = KErrNone;
    TBuf<40> buf;
    TInt add_flag =0;  
 
 	RFile LogResult;
    RFs LogResultSession;
    User::LeaveIfError(LogResultSession.Connect());
    if(LogResult.Open(LogResultSession ,KFilePath , EFileWrite | EFileShareAny )  != KErrNotFound)
        {
        LogResult.Close();

		LogResultSession.Delete(KFilePath);
		
        LogResultSession.Close();
        }
    
    LogResult.Close();
    LogResultSession.Close();
    
    
    
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    MLiwInterface* interface = NULL;
    CLiwGenericParamList* inps = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outps = &(iServiceHandler->OutParamListL());

 	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);

	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray a;
	a.AppendL(crit);    
	
	iServiceHandler->AttachL(a);
	iServiceHandler->ExecuteServiceCmdL(*crit, *inps, *outps); 

	a.Reset();
	delete crit;
	
	TInt pos = 0;

	outps->FindFirst( pos, KIDataSource );
	if(pos != KErrNotFound)
		{
		interface = (*outps)[pos].Value().AsInterface();	
		}

	outps->Reset();
	inps->Reset();
	
	TLiwGenericParam param;
	TInt index = 0;
    
    result = AddLandMark(inps,outps,interface,KName,KDescription);
    
    if(!result)
    {
    	add_flag = 1;
    	GetLandMarkId(inps,outps,interface,KName,KDescription);    
	
		// Call Export and then Import
    	
   		CLiwMap* export_map = CLiwDefaultMap::NewL();
   		
    	CLiwList* landmarkIdList = CLiwDefaultList::NewL();
    	landmarkIdList->AppendL(TLiwVariant(landmark_id));       	   
    	
   		export_map->InsertL(KDestinationFile,TLiwVariant(KFilePath));
        export_map->InsertL(KMimeType,TLiwVariant(KPosMimeType));
        export_map->InsertL(KIdList,TLiwVariant(landmarkIdList));
    	landmarkIdList->DecRef();       	
    	
    	param.SetNameAndValueL(KDataFields,TLiwVariant(export_map));
    	inps->AppendL(param);
    	param.Reset();
    
    	param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
    	inps->AppendL(param);
    	param.Reset();
    	
    	interface->ExecuteCmdL(KExport,*inps,*outps,0,0);
    	export_map->DecRef();    	
    	index=0;
    	
    	const TLiwGenericParam* export_err = outps->FindFirst(index,KErrorCode);
    	if(export_err)
    	result = export_err->Value().AsTInt32();     	
       	     
       	if(!result)
       	{
       		outps->Reset();
			inps->Reset();
			CLiwMap* import_map = CLiwDefaultMap::NewL();
			import_map->InsertL(KMimeType,TLiwVariant(KPosMimeType));
    		import_map->InsertL(KSourceFile,TLiwVariant(KFilePath));
    		import_map->InsertL(KDbUri,TLiwVariant(KNullDesC));
    	
    		param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
    		inps->AppendL(param);
    		param.Reset();
    		
        	param.SetNameAndValueL(KDataFields,TLiwVariant(import_map));
    		inps->AppendL(param);
    		param.Reset();   	
    	
    		interface->ExecuteCmdL(KImport,*inps,*outps,0,0);
    		import_map->DecRef();    	
    		index=0;
    	
    		const TLiwGenericParam* import_err = outps->FindFirst(index,KErrorCode);
    		if(import_err)
    		result = import_err->Value().AsTInt32(); 
       	}        
    }    
    
    outps->Reset();
	inps->Reset();
	if(add_flag)
    	RemoveLandmark(inps,outps,interface);  	    	
   
    interface->Close();	
	delete iServiceHandler;  
	__UHEAP_MARKEND;
  	return result;
    }     
    
    
    
// -----------------------------------------------------------------------------
// Ctlandmark_provider::ImportDBTypeIdCheck
// To test import and database URI type id check
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctlandmark_provider::ImportDBTypeIdCheck( CStifItemParser& aItem )
    {       
    __UHEAP_MARK;
    _LIT(KName,"ImportTypeID");
    _LIT(KDescription,"ImportDb TypeID");
     _LIT(KFilePath, "c:\\importtypeid.lmx");
     //_LIT(KFilePath, "c:\\eposLmTestPos.lmx");
 	 _LIT(KPosMimeType, "application/vnd.nokia.landmarkcollection+xml");
 
    TInt32 result = KErrNone;
    TBuf<40> buf;
    TInt add_flag =0;  
 
 	RFile LogResult;
    RFs LogResultSession;
    User::LeaveIfError(LogResultSession.Connect());
    if(LogResult.Open(LogResultSession ,KFilePath , EFileWrite | EFileShareAny )  != KErrNotFound)
        {
        LogResult.Close();

		LogResultSession.Delete(KFilePath);
		
        LogResultSession.Close();
        }
    
    LogResult.Close();
    LogResultSession.Close();
    
    
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    MLiwInterface* interface = NULL;
    CLiwGenericParamList* inps = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outps = &(iServiceHandler->OutParamListL());

 	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);

	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray a;
	a.AppendL(crit);    
	
	iServiceHandler->AttachL(a);
	iServiceHandler->ExecuteServiceCmdL(*crit, *inps, *outps); 

	a.Reset();
	delete crit;
	
	TInt pos = 0;

	outps->FindFirst( pos, KIDataSource );
	if(pos != KErrNotFound)
		{
		interface = (*outps)[pos].Value().AsInterface();	
		}

	outps->Reset();
	inps->Reset();
	
	TLiwGenericParam param;
	TInt index = 0;
    
    result = AddLandMark(inps,outps,interface,KName,KDescription);
    
    if(!result)
    {
    	add_flag = 1;
    	GetLandMarkId(inps,outps,interface,KName,KDescription);    
	
		// Call Export and then Import
    	
   		CLiwMap* export_map = CLiwDefaultMap::NewL();
   		
    	CLiwList* landmarkIdList = CLiwDefaultList::NewL();
    	landmarkIdList->AppendL(TLiwVariant(landmark_id));       	   
    	
   		export_map->InsertL(KDestinationFile,TLiwVariant(KFilePath));
        export_map->InsertL(KMimeType,TLiwVariant(KPosMimeType));
        export_map->InsertL(KIdList,TLiwVariant(landmarkIdList));
    	landmarkIdList->DecRef();       	
    	
    	param.SetNameAndValueL(KDataFields,TLiwVariant(export_map));
    	inps->AppendL(param);
    	param.Reset();
    
    	param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
    	inps->AppendL(param);
    	param.Reset();
    	
    	interface->ExecuteCmdL(KExport,*inps,*outps,0,0);
    	export_map->DecRef();    	
    	index=0;
    	
    	const TLiwGenericParam* export_err = outps->FindFirst(index,KErrorCode);
    	if(export_err)
    	result = export_err->Value().AsTInt32();     	
       	     
       	if(!result)
       	{
       		outps->Reset();
			inps->Reset();
			CLiwMap* import_map = CLiwDefaultMap::NewL();
			import_map->InsertL(KMimeType,TLiwVariant(KPosMimeType));
    		import_map->InsertL(KSourceFile,TLiwVariant(KFilePath));
    		import_map->InsertL(KDbUri,TLiwVariant((TInt32)25));
    	
    		param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
    		inps->AppendL(param);
    		param.Reset();
    		
        	param.SetNameAndValueL(KDataFields,TLiwVariant(import_map));
    		inps->AppendL(param);
    		param.Reset();   	
    	
    		interface->ExecuteCmdL(KImport,*inps,*outps,0,0);
    		import_map->DecRef();    	
    		index=0;
    	
    		const TLiwGenericParam* import_err = outps->FindFirst(index,KErrorCode);
    		if(import_err)
    		result = import_err->Value().AsTInt32(); 
       	}        
    }    
    
    outps->Reset();
	inps->Reset();
	if(add_flag)
    	RemoveLandmark(inps,outps,interface);  	    	
   
    interface->Close();	
	delete iServiceHandler;
  
  	if(result == SErrBadArgumentType)
  		result = KErrNone;
  	__UHEAP_MARKEND;
  	return result;
    }     
    
// -----------------------------------------------------------------------------
// Ctlandmark_provider::TestAddMultipleLM
// To add multiple landmarks with same name and description and verifying the same using GetList
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctlandmark_provider::TestAddMultipleLM( CStifItemParser& aItem )
    {       
    _LIT(KName,"MultipleAdd");
    _LIT(KDescription,"Adding same landmark multiple times");  
    TInt32 result = KErrNone;
    TInt count = 0;
    __UHEAP_MARK;
    
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    MLiwInterface* interface = NULL;
    CLiwGenericParamList* inps = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outps = &(iServiceHandler->OutParamListL());

 	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);

	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray a;
	a.AppendL(crit);    
	
	iServiceHandler->AttachL(a);
	iServiceHandler->ExecuteServiceCmdL(*crit, *inps, *outps); 

	a.Reset();
	delete crit;
	
	TInt pos = 0;

	outps->FindFirst( pos, KIDataSource );
	if(pos != KErrNotFound)
		{
		interface = (*outps)[pos].Value().AsInterface();	
		}

	outps->Reset();
	inps->Reset();
	
	
    TPosition locale;
    locale.SetCurrentTime();     
    TLiwGenericParam param; 
    
    // Add landmark twice
    result = AddLandMark(inps,outps,interface,KName,KDescription);
    
    if(!result)
    	result = AddLandMark(inps,outps,interface,KName,KDescription);
    
    if(!result)
    {
    	// Call GetList
    	
    	CLiwMap* getlistlandmark_map = CLiwDefaultMap::NewL();
        CLiwMap* sort_map = CLiwDefaultMap::NewL();
        sort_map->InsertL(KSortOrder,TLiwVariant(KAscending));
        getlistlandmark_map->InsertL(KLandmarkName,TLiwVariant(KName));
        getlistlandmark_map->InsertL(KLandmarkDesc,TLiwVariant(KDescription));
        
    	param.SetNameAndValueL(KFilter,TLiwVariant(getlistlandmark_map));
    	inps->AppendL(param);
    	param.Reset();
    
    	param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
    	inps->AppendL(param);
    	param.Reset();
    	
    	param.SetNameAndValueL(KSort,TLiwVariant(sort_map));
    	inps->AppendL(param);
    	param.Reset();    	
    	
    	interface->ExecuteCmdL(KGetList,*inps,*outps,0,0);
    	getlistlandmark_map->DecRef();
    	sort_map->DecRef();
    	
    	TInt index=0;
    	
    	const TLiwGenericParam* getlist_err = outps->FindFirst(index,KErrorCode);
    	if(getlist_err)
    	result = getlist_err->Value().AsTInt32();   
    	
    	if(!result)
    	{
    		//Get count of no of categories in the database.
    		pos=0;
			const TLiwGenericParam* output = outps->FindFirst( pos,_L8("ReturnValue"));
					
			if(output)     
			{
				CLiwIterable* iterlist = output->Value().AsIterable();

		    	TLiwVariant data;
	    	      
		    	while( iterlist->NextL(data))
				{
					count++;
					const CLiwMap* res = data.AsMap();
					if ( res )
					{
						TLiwVariant new_data;					
						TLiwVariant desc_data;					
						if(res->FindL(KLandmarkName, new_data))
						{
							TPtrC name = new_data.AsDes();
							TBuf<40> name_data;
							name_data.Copy(name);
							iLog->Log(name_data);						
						}
						if(res->FindL(KLandmarkDesc, desc_data))
						{
							TPtrC desc = desc_data.AsDes();
							TBuf<40> description;
							description.Copy(desc);
							iLog->Log(description);						
						}												
						new_data.Reset();		
						desc_data.Reset();						
					}
					
				 }			  		
			 	data.Reset();	
			}			
    	}
    	
    }
       
    outps->Reset();
	inps->Reset();
	    
	
    interface->Close();	
	delete iServiceHandler;
  
  	__UHEAP_MARKEND;
  	return result;
    }
    
    
    
// -----------------------------------------------------------------------------
// Ctlandmark_provider::TestGetListCTWithSortOrder
// To test GetList on category with sort order mentioned
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctlandmark_provider::TestGetListCTWithSortOrder( CStifItemParser& aItem )
    {       
      
    TInt32 result = KErrNone;
    TInt count = 0;
    __UHEAP_MARK;
    
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    MLiwInterface* interface = NULL;
    CLiwGenericParamList* inps = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outps = &(iServiceHandler->OutParamListL());

 	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);

	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray a;
	a.AppendL(crit);    
	
	iServiceHandler->AttachL(a);
	iServiceHandler->ExecuteServiceCmdL(*crit, *inps, *outps); 

	a.Reset();
	delete crit;
	
	TInt pos = 0;

	outps->FindFirst( pos, KIDataSource );
	if(pos != KErrNotFound)
		{
		interface = (*outps)[pos].Value().AsInterface();	
		}

	outps->Reset();
	inps->Reset();
	
	
    TPosition locale;
    locale.SetCurrentTime();     
    TLiwGenericParam param; 
    
    if(!result)
    {
    	// Call GetList
    	
    	CLiwMap* getlistcategory_map = CLiwDefaultMap::NewL();
        CLiwMap* sort_map = CLiwDefaultMap::NewL();
        sort_map->InsertL(KSortOrder,TLiwVariant(KAscending));
        
    	param.SetNameAndValueL(KFilter,TLiwVariant(getlistcategory_map));
    	inps->AppendL(param);
    	param.Reset();
    
    	param.SetNameAndValueL(KContentType,TLiwVariant(KCategory));
    	inps->AppendL(param);
    	param.Reset();
    	
    	param.SetNameAndValueL(KSort,TLiwVariant(sort_map));
    	inps->AppendL(param);
    	param.Reset();    	
    	
    	interface->ExecuteCmdL(KGetList,*inps,*outps,0,0);
    	getlistcategory_map->DecRef();
    	sort_map->DecRef();
    	
    	TInt index=0;
    	
    	const TLiwGenericParam* getlist_err = outps->FindFirst(index,KErrorCode);
    	if(getlist_err)
    	result = getlist_err->Value().AsTInt32();   
    	
    	if(!result)
    	{
    		//Get count of no of categories in the database.
    		pos=0;
			const TLiwGenericParam* output = outps->FindFirst( pos,_L8("ReturnValue"));
					
			if(output)     
			{
				CLiwIterable* iterlist = output->Value().AsIterable();

		    	TLiwVariant data;
	    	      
		    	while( iterlist->NextL(data))
				{
					count++;
					const CLiwMap* res = data.AsMap();
					if ( res )
					{
						TLiwVariant new_data;					
						if(res->FindL(KCategoryName, new_data))
						{
							TPtrC name = new_data.AsDes();
							TBuf<40> name_data;
							name_data.Copy(name);
							iLog->Log(name_data);						
						}						
						new_data.Reset();						
					}
					
				 }			  		
			 	data.Reset();	
			}			
    	}
    	
    }
       
    outps->Reset();
	inps->Reset();
	    
	
    interface->Close();	
	delete iServiceHandler;
  
  	__UHEAP_MARKEND;
  	return result;
    }
    
    
// -----------------------------------------------------------------------------
// Ctlandmark_provider::TestTemplateInvalidCase
// To test new template API for no content type and invalid content type
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctlandmark_provider::TestTemplateInvalidCase( CStifItemParser& aItem )
    {       
    TInt32 result = KErrNone;
    
    __UHEAP_MARK;
    
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    MLiwInterface* interface = NULL;
    CLiwGenericParamList* inps = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outps = &(iServiceHandler->OutParamListL());

 	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);

	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray a;
	a.AppendL(crit);    
	
	iServiceHandler->AttachL(a);
	iServiceHandler->ExecuteServiceCmdL(*crit, *inps, *outps); 

	a.Reset();
	delete crit;
	
	TInt pos = 0;

	outps->FindFirst( pos, KIDataSource );
	if(pos != KErrNotFound)
		{
		interface = (*outps)[pos].Value().AsInterface();	
		}

	outps->Reset();
	inps->Reset();
	
   
    TLiwGenericParam param;   
    
	// No INput == No content type
    interface->ExecuteCmdL(KNew,*inps,*outps,0,0);
      
    TInt index = 0;
    
    const TLiwGenericParam* err = outps->FindFirst(index,KErrorCode);
    if(err)
    	result = err->Value().AsTInt32();
    
    if(result == SErrMissingArgument)
    {
    	// invalid content type
    	outps->Reset();
		inps->Reset();
    	param.SetNameAndValueL(KContentType,TLiwVariant(_L("Test")));
  	    inps->AppendL(param);
   		param.Reset();
   		
   		 interface->ExecuteCmdL(KNew,*inps,*outps,0,0);      
   		index =0;    
     	const TLiwGenericParam* err1 = outps->FindFirst(index,KErrorCode);
    	if(err1)
    		result = err1->Value().AsTInt32();	

    }
    
    outps->Reset();
	inps->Reset();
    interface->Close();	
	delete iServiceHandler;
  
  	__UHEAP_MARKEND;
  	if(result == SErrInvalidServiceArgument)
  		return KErrNone;
  	else
  		return result;
    }


// -----------------------------------------------------------------------------
// Ctlandmark_provider::TestTemplateLM
// To test new template API for landmarks 
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctlandmark_provider::TestTemplateLM( CStifItemParser& aItem )
    {       
    TInt32 result = KErrNone;
    
    __UHEAP_MARK;
    
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    MLiwInterface* interface = NULL;
    CLiwGenericParamList* inps = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outps = &(iServiceHandler->OutParamListL());

 	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);

	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray a;
	a.AppendL(crit);    
	
	iServiceHandler->AttachL(a);
	iServiceHandler->ExecuteServiceCmdL(*crit, *inps, *outps); 

	a.Reset();
	delete crit;
	
	TInt pos = 0;

	outps->FindFirst( pos, KIDataSource );
	if(pos != KErrNotFound)
		{
		interface = (*outps)[pos].Value().AsInterface();	
		}

	outps->Reset();
	inps->Reset();
	
   
    TLiwGenericParam param;   
    
  	param.SetNameAndValueL(KNullDesC8,TLiwVariant(KLandmark));
    inps->AppendL(param);
	param.Reset();
   		
	 interface->ExecuteCmdL(KNew,*inps,*outps,0,0);
    pos = 0;    	
    
   	const TLiwGenericParam* err = outps->FindFirst(pos,KErrorCode);
   	if(err)
    		result = err->Value().AsTInt32();	
   	
   	if(!result)
   	{
   		// retreive the map
   		pos=0;
   		const TLiwGenericParam* output = outps->FindFirst( pos,_L8("ReturnValue"));					
		if(output)     
		{
			const CLiwMap *lm_template = NULL;
			lm_template = output->Value().AsMap();
		    if(!lm_template)
		    	result = KErrGeneral;
		}		
   	}
   	outps->Reset();
	inps->Reset();
    interface->Close();	
	delete iServiceHandler;
  
  	__UHEAP_MARKEND;
  	return result;
    }


// -----------------------------------------------------------------------------
// Ctlandmark_provider::TestTemplateCT
// To test new template API for landmarks 
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctlandmark_provider::TestTemplateCT( CStifItemParser& aItem )
    {       
    TInt32 result = KErrNone;
    
    __UHEAP_MARK;
    
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    MLiwInterface* interface = NULL;
    CLiwGenericParamList* inps = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outps = &(iServiceHandler->OutParamListL());

 	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);

	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray a;
	a.AppendL(crit);    
	
	iServiceHandler->AttachL(a);
	iServiceHandler->ExecuteServiceCmdL(*crit, *inps, *outps); 

	a.Reset();
	delete crit;
	
	TInt pos = 0;

	outps->FindFirst( pos, KIDataSource );
	if(pos != KErrNotFound)
		{
		interface = (*outps)[pos].Value().AsInterface();	
		}

	outps->Reset();
	inps->Reset();
	
   
    TLiwGenericParam param;   
    
  	param.SetNameAndValueL(KNullDesC8,TLiwVariant(KCategory));
    inps->AppendL(param);
	param.Reset();
   		
	 interface->ExecuteCmdL(KNew,*inps,*outps,0,0);
     pos = 0;    	
    
   	const TLiwGenericParam* err = outps->FindFirst(pos,KErrorCode);
   	if(err)
    		result = err->Value().AsTInt32();	
   	
   	if(!result)
   	{
   		// retreive the map
   		pos=0;
   		const TLiwGenericParam* output = outps->FindFirst( pos,_L8("ReturnValue"));					
		if(output)     
		{
			const CLiwMap *ct_template = NULL;
			ct_template = output->Value().AsMap();
		    if(!ct_template)
		    	result = KErrGeneral;
		}		
   	}
   	outps->Reset();
	inps->Reset();
    interface->Close();	
	delete iServiceHandler;
  
  	__UHEAP_MARKEND;
  	return result;
    }


// -----------------------------------------------------------------------------
// Ctlandmark_provider::TestNoTid
// To cancel async call with no transaction Id
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctlandmark_provider::TestNoTid( CStifItemParser& aItem )
    {
	
	__UHEAP_MARK;
	CTestAsync* test = CTestAsync::NewL(1);
	test->Start();
	TInt32 Err = test->Result();
	delete test;
	__UHEAP_MARKEND;
	iLog->Log(_L("back to test case"));	
	if(Err != SErrMissingArgument)
		return Err;
	else
		return KErrNone;
    }
    
// -----------------------------------------------------------------------------
// Ctlandmark_provider::TestInvalidTid
// To cancel async call with Invalid transaction Id
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctlandmark_provider::TestInvalidTid( CStifItemParser& aItem )
    {
	__UHEAP_MARK;
  	CTestAsync* test = CTestAsync::NewL(4);
	test->Start();
	TInt32 Err = test->Result();
	delete test;
	__UHEAP_MARKEND;	
	return Err;
    }
    
// -----------------------------------------------------------------------------
// Ctlandmark_provider::TestAddLMVarByOrder
// To call Add with diff order of inputs
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctlandmark_provider::TestAddLMVarByOrder( CStifItemParser& aItem )
    {       
    _LIT(KName,"Mainland india");
    _LIT(KDescription,"Extremely good indian food");
    _LIT(KPhone1,"123456");
    _LIT(KOffice1,"eat");
    _LIT(KOffice2,"sleep");
    _LIT(KOffice3,"drink");
    TReal64 latitude = 45.1122;
    TReal64 longitude = 34.0099;
    TReal32 altitude = 41.0022;
    TReal32 hacc = 0.1234;
    TReal32 vacc = 0.3456;
    TInt32 result = KErrNone;
    
    __UHEAP_MARK;
    
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    MLiwInterface* interface = NULL;
    CLiwGenericParamList* inps = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outps = &(iServiceHandler->OutParamListL());

 	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);

	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray a;
	a.AppendL(crit);    
	
	iServiceHandler->AttachL(a);
	iServiceHandler->ExecuteServiceCmdL(*crit, *inps, *outps); 

	a.Reset();
	delete crit;
	
	TInt pos = 0;

	outps->FindFirst( pos, KIDataSource );
	if(pos != KErrNotFound)
		{
		interface = (*outps)[pos].Value().AsInterface();	
		}

	outps->Reset();
	inps->Reset();
	
	
    TPosition locale;
    locale.SetCurrentTime();    
    
    CLiwMap* landmarkMap = CLiwDefaultMap::NewL();
    TLiwGenericParam param;
    
         
    //name
    landmarkMap->InsertL(KLandmarkName,TLiwVariant(KName));    
     
    //description
    landmarkMap->InsertL(KLandmarkDesc,TLiwVariant(KDescription));    
    
    param.SetNameAndValueL(KDataFields,TLiwVariant(landmarkMap));
    inps->AppendL(param);
    param.Reset();   
    
    
    param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
    inps->AppendL(param);
    param.Reset();

    interface->ExecuteCmdL(KAdd,*inps,*outps,0,0);
    landmarkMap->DecRef();
    
    TInt index = 0;
    
    const TLiwGenericParam* err = outps->FindFirst(index,KErrorCode);
    if(err)
    	result = err->Value().AsTInt32();
    
    outps->Reset();
	inps->Reset();
    // Remove the landmark added
    
    if(!result)
    {
    	GetLandMarkId(inps,outps,interface,KName,KDescription);
    	result = RemoveLandmark(inps,outps,interface);	
    }    
    
    interface->Close();	
	delete iServiceHandler;
  
  	__UHEAP_MARKEND;
  	return result;
  	
    }
    
 // -----------------------------------------------------------------------------
// Ctlandmark_provider::TestAddLMVarByPos
// To test position based parsing for Add
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctlandmark_provider::TestAddLMVarByPos( CStifItemParser& aItem )
    {       
    _LIT(KName,"Mainland India");
    _LIT(KDescription,"Extremely food");
    _LIT(KPhone1,"123456");
    _LIT(KOffice1,"eat");
    _LIT(KOffice2,"sleep");
    _LIT(KOffice3,"drink");
    TReal64 latitude = 45.1122;
    TReal64 longitude = 34.0099;
    TReal32 altitude = 41.0022;
    TReal32 hacc = 0.1234;
    TReal32 vacc = 0.3456;
    TInt32 result = KErrNone;
    
    __UHEAP_MARK;
    
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    MLiwInterface* interface = NULL;
    CLiwGenericParamList* inps = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outps = &(iServiceHandler->OutParamListL());

 	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);

	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray a;
	a.AppendL(crit);    
	
	iServiceHandler->AttachL(a);
	iServiceHandler->ExecuteServiceCmdL(*crit, *inps, *outps); 

	a.Reset();
	delete crit;
	
	TInt pos = 0;

	outps->FindFirst( pos, KIDataSource );
	if(pos != KErrNotFound)
		{
		interface = (*outps)[pos].Value().AsInterface();	
		}

	outps->Reset();
	inps->Reset();
	
	
    TPosition locale;
    locale.SetCurrentTime();    
    
    CLiwMap* landmarkMap = CLiwDefaultMap::NewL();
    TLiwGenericParam param;
    
    param.SetNameAndValueL(KNullDesC8,TLiwVariant(KLandmark));
    inps->AppendL(param);
    param.Reset();    
    
    landmarkMap->InsertL(KLandmarkName,TLiwVariant(KName)); 
    //description
    landmarkMap->InsertL(KLandmarkDesc,TLiwVariant(KDescription));    
    
    param.SetNameAndValueL(KNullDesC8,TLiwVariant(landmarkMap));
    inps->AppendL(param);
    param.Reset();      
    

    interface->ExecuteCmdL(KAdd,*inps,*outps,0,0);
    landmarkMap->DecRef();
    
    TInt index = 0;
    
    const TLiwGenericParam* err = outps->FindFirst(index,KErrorCode);
    if(err)
    	result = err->Value().AsTInt32();
    
    outps->Reset();
	inps->Reset();
    // Remove the landmark added
    
    if(!result)
    {
    	GetLandMarkId(inps,outps,interface,KName,KDescription);
    	result = RemoveLandmark(inps,outps,interface);	
    }   
    
    interface->Close();	
	delete iServiceHandler;
  
  	__UHEAP_MARKEND;
  	return result;
    }

// -----------------------------------------------------------------------------
// Ctlandmark_provider::TestAddCTVarByOrder
// To call Add (category)with diff order of inputs
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctlandmark_provider::TestAddCTVarByOrder( CStifItemParser& aItem )
    {       
    _LIT(KName,"New cat");
     TInt32 result = KErrNone;
    
    __UHEAP_MARK;
    
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    MLiwInterface* interface = NULL;
    CLiwGenericParamList* inps = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outps = &(iServiceHandler->OutParamListL());

 	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);

	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray a;
	a.AppendL(crit);    
	
	iServiceHandler->AttachL(a);
	iServiceHandler->ExecuteServiceCmdL(*crit, *inps, *outps); 

	a.Reset();
	delete crit;
	
	TInt pos = 0;

	outps->FindFirst( pos, KIDataSource );
	if(pos != KErrNotFound)
		{
		interface = (*outps)[pos].Value().AsInterface();	
		}

	outps->Reset();
	inps->Reset();
	
	
    TPosition locale;
    locale.SetCurrentTime();    
    
    CLiwMap* categoryMap = CLiwDefaultMap::NewL();
    TLiwGenericParam param;    
    
      
    //name
    categoryMap->InsertL(KCategoryName,TLiwVariant(KName));
    
     
    param.SetNameAndValueL(KDataFields,TLiwVariant(categoryMap));
    inps->AppendL(param);
    param.Reset();   
    
    
    param.SetNameAndValueL(KContentType,TLiwVariant(KCategory));
    inps->AppendL(param);
    param.Reset();

    interface->ExecuteCmdL(KAdd,*inps,*outps,0,0);
    categoryMap->DecRef();
    
    TInt index = 0;
    
    const TLiwGenericParam* err = outps->FindFirst(index,KErrorCode);
    if(err)
    	result = err->Value().AsTInt32();
    
    outps->Reset();
	inps->Reset();
    // Remove the category added
    
    if(!result || result == SErrEntryExists)
    {
    	GetCatId(inps,outps,interface,KName);
    	result = RemoveCategory(inps,outps,interface);	
    }   
    
    interface->Close();	
	delete iServiceHandler;
  
  	__UHEAP_MARKEND;
  	return result;
    }
    
// -----------------------------------------------------------------------------
// Ctlandmark_provider::TestAddCTVarByPos
// To call Add (category)with diff order of inputs
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctlandmark_provider::TestAddCTVarByPos( CStifItemParser& aItem )
    {       
    _LIT(KName,"New cat");
     TInt32 result = KErrNone;
    
    __UHEAP_MARK;
    
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    MLiwInterface* interface = NULL;
    CLiwGenericParamList* inps = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outps = &(iServiceHandler->OutParamListL());

 	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);

	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray a;
	a.AppendL(crit);    
	
	iServiceHandler->AttachL(a);
	iServiceHandler->ExecuteServiceCmdL(*crit, *inps, *outps); 

	a.Reset();
	delete crit;
	
	TInt pos = 0;

	outps->FindFirst( pos, KIDataSource );
	if(pos != KErrNotFound)
		{
		interface = (*outps)[pos].Value().AsInterface();	
		}

	outps->Reset();
	inps->Reset();
	
	
    TPosition locale;
    locale.SetCurrentTime();    
    
    CLiwMap* categoryMap = CLiwDefaultMap::NewL();
    TLiwGenericParam param;
    param.SetNameAndValueL(KNullDesC8,TLiwVariant(KCategory));
    inps->AppendL(param);
    param.Reset();

     //name
    categoryMap->InsertL(KCategoryName,TLiwVariant(KName));    
     
    param.SetNameAndValueL(KNullDesC8,TLiwVariant(categoryMap));
    inps->AppendL(param);
    param.Reset();     
    
   
    interface->ExecuteCmdL(KAdd,*inps,*outps,0,0);
    categoryMap->DecRef();
    
    TInt index = 0;
    
    const TLiwGenericParam* err = outps->FindFirst(index,KErrorCode);
    if(err)
    	result = err->Value().AsTInt32(); 
  	
  	outps->Reset();
	inps->Reset();
  	// Remove the category added
    
    if(!result || result == SErrEntryExists)
    {
    	GetCatId(inps,outps,interface,KName);
    	result = RemoveCategory(inps,outps,interface);	
    }   
    interface->Close();	
	delete iServiceHandler;
  
    __UHEAP_MARKEND;
  	return result;
  	
    }
    
// -----------------------------------------------------------------------------
// Ctlandmark_provider::TestGetListLMVarByOrder
// To test GetList on landmark changing the order of arguments
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctlandmark_provider::TestGetListLMVarByOrder( CStifItemParser& aItem )
    {       
    _LIT(KName,"GetListLandmark_byorder");
    _LIT(KDescription,"TestGetListLandmark_byorder");
    
    TInt32 result = KErrNone;
    TInt count = 0;
    __UHEAP_MARK;
    
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    MLiwInterface* interface = NULL;
    CLiwGenericParamList* inps = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outps = &(iServiceHandler->OutParamListL());

 	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);

	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray a;
	a.AppendL(crit);    
	
	iServiceHandler->AttachL(a);
	iServiceHandler->ExecuteServiceCmdL(*crit, *inps, *outps); 

	a.Reset();
	delete crit;
	
	TInt pos = 0;

	outps->FindFirst( pos, KIDataSource );
	if(pos != KErrNotFound)
		{
		interface = (*outps)[pos].Value().AsInterface();	
		}

	outps->Reset();
	inps->Reset();
	
	
    TPosition locale;
    locale.SetCurrentTime();    
    
    CLiwMap* landmarkMap = CLiwDefaultMap::NewL();
    TLiwGenericParam param;
    
         
    //name
    landmarkMap->InsertL(KLandmarkName,TLiwVariant(KName));
      
    //description
    landmarkMap->InsertL(KLandmarkDesc,TLiwVariant(KDescription));
    
    param.SetNameAndValueL(KDataFields,TLiwVariant(landmarkMap));
    inps->AppendL(param);
    param.Reset();       
    
    param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
    inps->AppendL(param);
    param.Reset();
    
    interface->ExecuteCmdL(KAdd,*inps,*outps,0,0);
    landmarkMap->DecRef();
    
    TInt index = 0;
    
    const TLiwGenericParam* err = outps->FindFirst(index,KErrorCode);
    if(err)
    	result = err->Value().AsTInt32();
    
    outps->Reset();
	inps->Reset();
    if(!result)
    {
    	// Call GetList
    	
    	CLiwMap* getlistlandmark_map = CLiwDefaultMap::NewL();
    	getlistlandmark_map->InsertL(KLandmarkName,TLiwVariant(KName));
      
    	//description
    	getlistlandmark_map->InsertL(KLandmarkDesc,TLiwVariant(KDescription));
    
    	param.SetNameAndValueL(KFilter,TLiwVariant(getlistlandmark_map));
    	inps->AppendL(param);
    	param.Reset();
    
    	param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
    	inps->AppendL(param);
    	param.Reset();
    	
    	interface->ExecuteCmdL(KGetList,*inps,*outps,0,0);
    	getlistlandmark_map->DecRef();
    	
    	index=0;
    	
    	const TLiwGenericParam* getlist_err = outps->FindFirst(index,KErrorCode);
    	if(getlist_err)
    	result = getlist_err->Value().AsTInt32();   
    	
    	if(!result)
    	{
    		//Get count of no of landmarks in the database. It should be atleast one
    		pos=0;
			const TLiwGenericParam* output = outps->FindFirst( pos,_L8("ReturnValue"));
					
			if(output)     
			{
				CLiwIterable* iterlist = output->Value().AsIterable();

		    	TLiwVariant data;
	    	      
		    	while( iterlist->NextL(data))
				{
					count++;
					
				 }			  		
			 	data.Reset();	
			}			
    	}
    	
    }
    if(count == 0)
    	result = KErrGeneral;
    
    outps->Reset();
	inps->Reset();
	
	// Remove the landmark added
    
    GetLandMarkId(inps,outps,interface,KName,KDescription);
    RemoveLandmark(inps,outps,interface);	      
	
    interface->Close();	
	delete iServiceHandler;
  
  	__UHEAP_MARKEND;
  	return result;
    }
    
// -----------------------------------------------------------------------------
// Ctlandmark_provider::TestGetListLMVarByPos
// To test GetList for position based parsing for landmarks
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctlandmark_provider::TestGetListLMVarByPos( CStifItemParser& aItem )
    {       
    _LIT(KName,"Landmark1");
    _LIT(KDescription,"TestLandmark1");
    
    TInt32 result = KErrNone;
    
    __UHEAP_MARK;
    
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    MLiwInterface* interface = NULL;
    CLiwGenericParamList* inps = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outps = &(iServiceHandler->OutParamListL());

 	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);

	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray a;
	a.AppendL(crit);    
	
	iServiceHandler->AttachL(a);
	iServiceHandler->ExecuteServiceCmdL(*crit, *inps, *outps); 

	a.Reset();
	delete crit;
	
	TInt pos = 0;

	outps->FindFirst( pos, KIDataSource );
	if(pos != KErrNotFound)
		{
		interface = (*outps)[pos].Value().AsInterface();	
		}

	outps->Reset();
	inps->Reset();
	
	
    TPosition locale;
    locale.SetCurrentTime();    
    
    CLiwMap* landmarkMap = CLiwDefaultMap::NewL();
    TLiwGenericParam param;
    
    
    //name
    landmarkMap->InsertL(KLandmarkName,TLiwVariant(KName));
      
    //description
    landmarkMap->InsertL(KLandmarkDesc,TLiwVariant(KDescription));
    
    param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
    inps->AppendL(param);
    param.Reset();
    
    param.SetNameAndValueL(KDataFields,TLiwVariant(landmarkMap));
    inps->AppendL(param);
    param.Reset();        
    
    
    interface->ExecuteCmdL(KAdd,*inps,*outps,0,0);
    landmarkMap->DecRef();
    
    TInt index = 0;
    
    const TLiwGenericParam* err = outps->FindFirst(index,KErrorCode);
    if(err)
    	result = err->Value().AsTInt32();
    
    outps->Reset();
	inps->Reset();
    if(!result)
    {
    	// Call GetList
    	
    	CLiwMap* getlistlandmark_map = CLiwDefaultMap::NewL();
    	getlistlandmark_map->InsertL(KLandmarkName,TLiwVariant(KName));
      
    	//description
    	getlistlandmark_map->InsertL(KLandmarkDesc,TLiwVariant(KDescription));
    
    	param.SetNameAndValueL(KNullDesC8,TLiwVariant(KLandmark));
    	inps->AppendL(param);
    	param.Reset();
    	
    	param.SetNameAndValueL(KNullDesC8,TLiwVariant(getlistlandmark_map));
    	inps->AppendL(param);
    	param.Reset();   
    	
    	interface->ExecuteCmdL(KGetList,*inps,*outps,0,0);
    	getlistlandmark_map->DecRef();
    	
    	index=0;
    	
    	const TLiwGenericParam* getlist_err = outps->FindFirst(index,KErrorCode);
    	if(getlist_err)
    	result = getlist_err->Value().AsTInt32();    	
    	
    }
    
    outps->Reset();
	inps->Reset();
	
    // Remove the landmark added
    
    GetLandMarkId(inps,outps,interface,KName,KDescription);
    RemoveLandmark(inps,outps,interface);
    
    interface->Close();	
	delete iServiceHandler;
  
  	__UHEAP_MARKEND;
  	return result;
    }

// -----------------------------------------------------------------------------
// Ctlandmark_provider::TestGetListCTVarByOrder
// To test GetList on category changing the order of arguments
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctlandmark_provider::TestGetListCTVarByOrder( CStifItemParser& aItem )
    {       
    _LIT(KName,"India");
    _LIT(KDescription,"Culture");
    
    TInt32 result = KErrNone;
    
    __UHEAP_MARK;
    
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    MLiwInterface* interface = NULL;
    CLiwGenericParamList* inps = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outps = &(iServiceHandler->OutParamListL());

 	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);

	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray a;
	a.AppendL(crit);    
	
	iServiceHandler->AttachL(a);
	iServiceHandler->ExecuteServiceCmdL(*crit, *inps, *outps); 

	a.Reset();
	delete crit;
	
	TInt pos = 0;

	outps->FindFirst( pos, KIDataSource );
	if(pos != KErrNotFound)
		{
		interface = (*outps)[pos].Value().AsInterface();	
		}

	outps->Reset();
	inps->Reset();
	
	
    TPosition locale;
    locale.SetCurrentTime();    
    
    CLiwMap* categoryMap = CLiwDefaultMap::NewL();
    TLiwGenericParam param;
    
    
    //name
    categoryMap->InsertL(KCategoryName,TLiwVariant(KName));
      
    param.SetNameAndValueL(KDataFields,TLiwVariant(categoryMap));
    inps->AppendL(param);
    param.Reset();       
    
    param.SetNameAndValueL(KContentType,TLiwVariant(KCategory));
    inps->AppendL(param);
    param.Reset();
    
    interface->ExecuteCmdL(KAdd,*inps,*outps,0,0);
    categoryMap->DecRef();
    
    TInt index = 0;
    
    const TLiwGenericParam* err = outps->FindFirst(index,KErrorCode);
    if(err)
    	result = err->Value().AsTInt32();
    
    outps->Reset();
	inps->Reset();
    if(!result || result == SErrEntryExists)
    {
    	// Call GetList
    	
    	CLiwMap* getlistcategory_map = CLiwDefaultMap::NewL();
    	getlistcategory_map->InsertL(KCategoryName,TLiwVariant(KName));
      
      	getlistcategory_map->InsertL(KMaximumMatches,TLiwVariant(TInt32(10)));
     // 	getlistcategory_map->InsertL(KPrevMatchesOnly,TLiwVariant(TBool(ETrue)));
    
    	param.SetNameAndValueL(KFilter,TLiwVariant(getlistcategory_map));
    	inps->AppendL(param);
    	param.Reset();
    
    	param.SetNameAndValueL(KContentType,TLiwVariant(KCategory));
    	inps->AppendL(param);
    	param.Reset();
    	
    	interface->ExecuteCmdL(KGetList,*inps,*outps,0,0);
    	getlistcategory_map->DecRef();
    	
    	index=0;
    	
    	const TLiwGenericParam* getlist_err = outps->FindFirst(index,KErrorCode);
    	if(getlist_err)
    	result = getlist_err->Value().AsTInt32();    	
    	
    }
    
    outps->Reset();
	inps->Reset();
	
    // Remove the category added
    
    GetCatId(inps,outps,interface,KName);
    RemoveCategory(inps,outps,interface);
    
    interface->Close();	
	delete iServiceHandler;
  
  	__UHEAP_MARKEND;
  	return result;
    }
    
// -----------------------------------------------------------------------------
// Ctlandmark_provider::TestGetListCTVarByPos
// To test position based parsing for getlist category
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctlandmark_provider::TestGetListCTVarByPos( CStifItemParser& aItem )
    {       
    _LIT(KName,"India");
    _LIT(KDescription,"Culture");
    
    TInt32 result = KErrNone;
    
    __UHEAP_MARK;
    
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    MLiwInterface* interface = NULL;
    CLiwGenericParamList* inps = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outps = &(iServiceHandler->OutParamListL());

 	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);

	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray a;
	a.AppendL(crit);    
	
	iServiceHandler->AttachL(a);
	iServiceHandler->ExecuteServiceCmdL(*crit, *inps, *outps); 

	a.Reset();
	delete crit;
	
	TInt pos = 0;

	outps->FindFirst( pos, KIDataSource );
	if(pos != KErrNotFound)
		{
		interface = (*outps)[pos].Value().AsInterface();	
		}

	outps->Reset();
	inps->Reset();
	
	
    TPosition locale;
    locale.SetCurrentTime();    
    
    CLiwMap* categoryMap = CLiwDefaultMap::NewL();
    TLiwGenericParam param;
    
    
    //name
    categoryMap->InsertL(KCategoryName,TLiwVariant(KName));
      
    param.SetNameAndValueL(KDataFields,TLiwVariant(categoryMap));
    inps->AppendL(param);
    param.Reset();       
    
    param.SetNameAndValueL(KContentType,TLiwVariant(KCategory));
    inps->AppendL(param);
    param.Reset();
    
    interface->ExecuteCmdL(KAdd,*inps,*outps,0,0);
    categoryMap->DecRef();
    
    TInt index = 0;
    
    const TLiwGenericParam* err = outps->FindFirst(index,KErrorCode);
    if(err)
    	result = err->Value().AsTInt32();
    
    outps->Reset();
	inps->Reset();
    if(!result || result == SErrEntryExists)
    {
    	// Call GetList
    	
    	CLiwMap* getlistcategory_map = CLiwDefaultMap::NewL();
    	CLiwMap* sort_map = CLiwDefaultMap::NewL();
    	
    	sort_map->InsertL(KCategoryName,TLiwVariant(KName));
    	sort_map->InsertL(KSortOrder,TLiwVariant(KDescending));
    	getlistcategory_map->InsertL(KCategoryName,TLiwVariant(KName));
      
      	getlistcategory_map->InsertL(KMaximumMatches,TLiwVariant(TInt32(10)));
         
    	param.SetNameAndValueL(KNullDesC8,TLiwVariant(KCategory));
    	inps->AppendL(param);
    	param.Reset();
    	
    	param.SetNameAndValueL(KNullDesC8,TLiwVariant(getlistcategory_map));
    	inps->AppendL(param);
    	param.Reset();       
    	
    	param.SetNameAndValueL(KNullDesC8,TLiwVariant(sort_map));
    	inps->AppendL(param);
    	param.Reset();
    	
    	interface->ExecuteCmdL(KGetList,*inps,*outps,0,0);
    	getlistcategory_map->DecRef();
    	sort_map->DecRef();
    	
    	index=0;
    	
    	const TLiwGenericParam* getlist_err = outps->FindFirst(index,KErrorCode);
    	if(getlist_err)
    	result = getlist_err->Value().AsTInt32();    	
    	
    }
    outps->Reset();
	inps->Reset();
	
    // Remove the category added
    
    GetCatId(inps,outps,interface,KName);
    RemoveCategory(inps,outps,interface);
    
    interface->Close();	
	delete iServiceHandler;
  
  	__UHEAP_MARKEND;
  	return result;
    }
        
// -----------------------------------------------------------------------------
// Ctlandmark_provider::TestGetRemoveLMVarByOrder
// To test delete on landmark by changing order of input params with Null/invalid landmark Id
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctlandmark_provider::TestRemoveLMVarByOrder( CStifItemParser& aItem )
    {       
    _LIT(KName,"Landmark1");
    _LIT(KDescription,"TestLandmark1");
    
    TInt32 result = KErrNone;
    
    __UHEAP_MARK;
    
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    MLiwInterface* interface = NULL;
    CLiwGenericParamList* inps = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outps = &(iServiceHandler->OutParamListL());

 	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);

	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray a;
	a.AppendL(crit);    
	
	iServiceHandler->AttachL(a);
	iServiceHandler->ExecuteServiceCmdL(*crit, *inps, *outps); 

	a.Reset();
	delete crit;
	
	TInt pos = 0;

	outps->FindFirst( pos, KIDataSource );
	if(pos != KErrNotFound)
		{
		interface = (*outps)[pos].Value().AsInterface();	
		}

	outps->Reset();
	inps->Reset();
	
	
    TPosition locale;
    locale.SetCurrentTime();    
    
    CLiwMap* landmarkMap = CLiwDefaultMap::NewL();
    TLiwGenericParam param;
    
    //name
    landmarkMap->InsertL(KLandmarkName,TLiwVariant(KName));
      
    //description
    landmarkMap->InsertL(KLandmarkDesc,TLiwVariant(KDescription));
    
    param.SetNameAndValueL(KDataFields,TLiwVariant(landmarkMap));
    inps->AppendL(param);
    param.Reset();       
    
    param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
    inps->AppendL(param);
    param.Reset();
    
    interface->ExecuteCmdL(KAdd,*inps,*outps,0,0);
    landmarkMap->DecRef();
    
    TInt index = 0;
    
    const TLiwGenericParam* err = outps->FindFirst(index,KErrorCode);
    if(err)
    	result = err->Value().AsTInt32();
    
    outps->Reset();
	inps->Reset();
    if(!result)
    {
    	// Call Remove
    	
    	CLiwMap* remove_map = CLiwDefaultMap::NewL();
    	remove_map->InsertL(KId,TLiwVariant(_L("12345")));
      
    	param.SetNameAndValueL(KDataFields,TLiwVariant(remove_map));
    	inps->AppendL(param);
    	param.Reset();
    
    	param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
    	inps->AppendL(param);
    	param.Reset();
    	
    	interface->ExecuteCmdL(KRemove,*inps,*outps,0,0);
    	remove_map->DecRef();    	
    	index=0;
    	
    	const TLiwGenericParam* remove_err = outps->FindFirst(index,KErrorCode);
    	if(remove_err)
    	result = remove_err->Value().AsTInt32();    	
    	
    }
    
    
    interface->Close();	
	delete iServiceHandler;
  
  	__UHEAP_MARKEND;
  	return result;
    }

// -----------------------------------------------------------------------------
// Ctlandmark_provider::TestGetRemoveLMVarByPos
// To test delete on landmark with position based parsing of input params with Null/invalid landmark Id
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctlandmark_provider::TestRemoveLMVarByPos( CStifItemParser& aItem )
    {       
    _LIT(KName,"Landmark1");
    _LIT(KDescription,"TestLandmark1");
    
    TInt32 result = KErrNone;
    
    __UHEAP_MARK;
    
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    MLiwInterface* interface = NULL;
    CLiwGenericParamList* inps = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outps = &(iServiceHandler->OutParamListL());

 	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);

	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray a;
	a.AppendL(crit);    
	
	iServiceHandler->AttachL(a);
	iServiceHandler->ExecuteServiceCmdL(*crit, *inps, *outps); 

	a.Reset();
	delete crit;
	
	TInt pos = 0;

	outps->FindFirst( pos, KIDataSource );
	if(pos != KErrNotFound)
		{
		interface = (*outps)[pos].Value().AsInterface();	
		}

	outps->Reset();
	inps->Reset();
	
	
    TPosition locale;
    locale.SetCurrentTime();    
    
    CLiwMap* landmarkMap = CLiwDefaultMap::NewL();
    TLiwGenericParam param;
    
    //name
    landmarkMap->InsertL(KLandmarkName,TLiwVariant(KName));
      
    //description
    landmarkMap->InsertL(KLandmarkDesc,TLiwVariant(KDescription));
    
    param.SetNameAndValueL(KDataFields,TLiwVariant(landmarkMap));
    inps->AppendL(param);
    param.Reset();       
    
    param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
    inps->AppendL(param);
    param.Reset();
    
    interface->ExecuteCmdL(KAdd,*inps,*outps,0,0);
    landmarkMap->DecRef();
    
    TInt index = 0;
    
    const TLiwGenericParam* err = outps->FindFirst(index,KErrorCode);
    if(err)
    	result = err->Value().AsTInt32();
    
    outps->Reset();
	inps->Reset();
    if(!result)
    {
    	// Call Remove
    	
    	CLiwMap* remove_map = CLiwDefaultMap::NewL();
    	remove_map->InsertL(KId,TLiwVariant(KNullDesC));
      
      	param.SetNameAndValueL(KNullDesC8,TLiwVariant(KLandmark));
    	inps->AppendL(param);
    	param.Reset();
    	
    	param.SetNameAndValueL(KNullDesC8,TLiwVariant(remove_map));
    	inps->AppendL(param);
    	param.Reset();    
    	
    	interface->ExecuteCmdL(KRemove,*inps,*outps,0,0);
    	remove_map->DecRef();    	
    	index=0;
    	
    	const TLiwGenericParam* remove_err = outps->FindFirst(index,KErrorCode);
    	if(remove_err)
    	result = remove_err->Value().AsTInt32();    	    	
    }   
    
    
    interface->Close();	
	delete iServiceHandler;
  
  	__UHEAP_MARKEND;
	if(result == 1000)
		result = KErrNone;
  	return result;
    }   
    
// -----------------------------------------------------------------------------
// Ctlandmark_provider::TestRemoveCTVarByOrder
// To test Remove on category changing the order of arguments and with Null/Invalid categoryId
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctlandmark_provider::TestRemoveCTVarByOrder( CStifItemParser& aItem )
    {       
    _LIT(KName,"India");
    _LIT(KDescription,"Culture");
    
    TInt32 result = KErrNone;
    
    __UHEAP_MARK;
    
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    MLiwInterface* interface = NULL;
    CLiwGenericParamList* inps = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outps = &(iServiceHandler->OutParamListL());

 	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);

	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray a;
	a.AppendL(crit);    
	
	iServiceHandler->AttachL(a);
	iServiceHandler->ExecuteServiceCmdL(*crit, *inps, *outps); 

	a.Reset();
	delete crit;
	
	TInt pos = 0;

	outps->FindFirst( pos, KIDataSource );
	if(pos != KErrNotFound)
		{
		interface = (*outps)[pos].Value().AsInterface();	
		}

	outps->Reset();
	inps->Reset();
	
	
    TPosition locale;
    locale.SetCurrentTime();    
    
    CLiwMap* categoryMap = CLiwDefaultMap::NewL();
    TLiwGenericParam param;
    
    
    //name
    categoryMap->InsertL(KCategoryName,TLiwVariant(KName));
      
    param.SetNameAndValueL(KDataFields,TLiwVariant(categoryMap));
    inps->AppendL(param);
    param.Reset();       
    
    param.SetNameAndValueL(KContentType,TLiwVariant(KCategory));
    inps->AppendL(param);
    param.Reset();
    
    interface->ExecuteCmdL(KAdd,*inps,*outps,0,0);
    categoryMap->DecRef();
    
    TInt index = 0;
    
    const TLiwGenericParam* err = outps->FindFirst(index,KErrorCode);
    if(err)
    	result = err->Value().AsTInt32();
    
    outps->Reset();
	inps->Reset();
    if(!result || result == SErrEntryExists)
    {
    	// Call Remove
    	
    	CLiwMap* removecategory_map = CLiwDefaultMap::NewL();
    	removecategory_map->InsertL(KId,TLiwVariant(KNullDesC));
      
      	param.SetNameAndValueL(KDataFields,TLiwVariant(removecategory_map));
    	inps->AppendL(param);
    	param.Reset();
    
    	param.SetNameAndValueL(KContentType,TLiwVariant(KCategory));
    	inps->AppendL(param);
    	param.Reset();
    	
    	interface->ExecuteCmdL(KRemove,*inps,*outps,0,0);
    	removecategory_map->DecRef();
    	
    	index=0;
    	
    	const TLiwGenericParam* remove_err = outps->FindFirst(index,KErrorCode);
    	if(remove_err)
    	result = remove_err->Value().AsTInt32();    	
    	
    }
    
    
    interface->Close();	
	delete iServiceHandler;
  
  	__UHEAP_MARKEND;
  if(result == 1000)
  	result = KErrNone;
  	return result;
    }

// -----------------------------------------------------------------------------
// Ctlandmark_provider::TestRemoveCTVarByPos
// To test Remove on category changing the order of arguments and with Null/Invalid categoryId
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctlandmark_provider::TestRemoveCTVarByPos( CStifItemParser& aItem )
    {       
    _LIT(KName,"India");
    _LIT(KDescription,"Culture");
    
    TInt32 result = KErrNone;
    
    __UHEAP_MARK;
    
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    MLiwInterface* interface = NULL;
    CLiwGenericParamList* inps = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outps = &(iServiceHandler->OutParamListL());

 	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);

	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray a;
	a.AppendL(crit);    
	
	iServiceHandler->AttachL(a);
	iServiceHandler->ExecuteServiceCmdL(*crit, *inps, *outps); 

	a.Reset();
	delete crit;
	
	TInt pos = 0;

	outps->FindFirst( pos, KIDataSource );
	if(pos != KErrNotFound)
		{
		interface = (*outps)[pos].Value().AsInterface();	
		}

	outps->Reset();
	inps->Reset();
	
	
    TPosition locale;
    locale.SetCurrentTime();    
    
    CLiwMap* categoryMap = CLiwDefaultMap::NewL();
    TLiwGenericParam param;
    
    
    //name
    categoryMap->InsertL(KCategoryName,TLiwVariant(KName));
      
    param.SetNameAndValueL(KDataFields,TLiwVariant(categoryMap));
    inps->AppendL(param);
    param.Reset();       
    
    param.SetNameAndValueL(KContentType,TLiwVariant(KCategory));
    inps->AppendL(param);
    param.Reset();
    
    interface->ExecuteCmdL(KAdd,*inps,*outps,0,0);
    categoryMap->DecRef();
    
    TInt index = 0;
    
    const TLiwGenericParam* err = outps->FindFirst(index,KErrorCode);
    if(err)
    	result = err->Value().AsTInt32();
    
    outps->Reset();
	inps->Reset();
    if(!result || result == SErrEntryExists)
    {
    	// Call Remove
    	
    	CLiwMap* removecategory_map = CLiwDefaultMap::NewL();
    	removecategory_map->InsertL(KId,TLiwVariant(_L("-255.45")));
      
      	param.SetNameAndValueL(KNullDesC8,TLiwVariant(KCategory));
    	inps->AppendL(param);
    	param.Reset();
    	
      	param.SetNameAndValueL(KNullDesC8,TLiwVariant(removecategory_map));
    	inps->AppendL(param);
    	param.Reset();    	
    	
    	interface->ExecuteCmdL(KRemove,*inps,*outps,0,0);
    	removecategory_map->DecRef();
    	
    	index=0;
    	
    	const TLiwGenericParam* remove_err = outps->FindFirst(index,KErrorCode);
    	if(remove_err)
    	result = remove_err->Value().AsTInt32();    	
    	
    }
    
    
    interface->Close();	
	delete iServiceHandler;
  
  	__UHEAP_MARKEND;
  	if(result == 1000)
  		result = KErrNone;
  	return result;
    }      
    
// -----------------------------------------------------------------------------
// Ctlandmark_provider::TestExportVarByOrder
// To test export by changing order of input params with Null/invalid landmark Id
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctlandmark_provider::TestExportVarByOrder( CStifItemParser& aItem )
    {       
    _LIT(KName,"Landmark1");
    _LIT(KDescription,"TestLandmark1");
     _LIT(KFilePath, "c:\\eposLmTestOrder.lmx");
 	 _LIT(KPosMimeType, "application/vnd.nokia.landmarkcollection+xml");
    TInt32 result = KErrNone;
    
    __UHEAP_MARK;
    
    RFile LogResult;
    RFs LogResultSession;
    User::LeaveIfError(LogResultSession.Connect());
    if(LogResult.Open(LogResultSession ,KFilePath , EFileWrite | EFileShareAny )  != KErrNotFound)
        {
        LogResult.Close();

		LogResultSession.Delete(KFilePath);
		
        LogResultSession.Close();
        }
    
    LogResult.Close();
    LogResultSession.Close();
    
    
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    MLiwInterface* interface = NULL;
    CLiwGenericParamList* inps = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outps = &(iServiceHandler->OutParamListL());

 	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);

	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray a;
	a.AppendL(crit);    
	
	iServiceHandler->AttachL(a);
	iServiceHandler->ExecuteServiceCmdL(*crit, *inps, *outps); 

	a.Reset();
	delete crit;
	
	TInt pos = 0;

	outps->FindFirst( pos, KIDataSource );
	if(pos != KErrNotFound)
		{
		interface = (*outps)[pos].Value().AsInterface();	
		}

	outps->Reset();
	inps->Reset();
	
	TLiwGenericParam param;
	TInt index = 0;
    TPosition locale;
    locale.SetCurrentTime();    
    
    CLiwMap* landmarkMap = CLiwDefaultMap::NewL();    
    
    //name
  	landmarkMap->InsertL(KLandmarkName,TLiwVariant(KName));  	  
      
    //description
    landmarkMap->InsertL(KLandmarkDesc,TLiwVariant(KDescription));
    
    param.SetNameAndValueL(KDataFields,TLiwVariant(landmarkMap));
    inps->AppendL(param);
    param.Reset();       
    
    param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
    inps->AppendL(param);
    param.Reset();
    
    interface->ExecuteCmdL(KAdd,*inps,*outps,0,0);
    landmarkMap->DecRef();    
    
    
    const TLiwGenericParam* err = outps->FindFirst(index,KErrorCode);
    if(err)
    	result = err->Value().AsTInt32();
    
    outps->Reset();
	inps->Reset();
    if(!result)
    {
    	// Call Export
    	
    	CLiwMap* export_map = CLiwDefaultMap::NewL();
    	CLiwList* landmarkIdList = CLiwDefaultList::NewL();
    	landmarkIdList->AppendL(TLiwVariant(_L("-25")));
    	landmarkIdList->AppendL(TLiwVariant(_L("3.5")));
    	
   		export_map->InsertL(KDestinationFile,TLiwVariant(KFilePath));
        export_map->InsertL(KMimeType,TLiwVariant(KPosMimeType));
        export_map->InsertL(KIdList,TLiwVariant(landmarkIdList));
    	landmarkIdList->DecRef();
            
    	param.SetNameAndValueL(KDataFields,TLiwVariant(export_map));
    	inps->AppendL(param);
    	param.Reset();
    
    	param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
    	inps->AppendL(param);
    	param.Reset();
    	
    	interface->ExecuteCmdL(KExport,*inps,*outps,0,0);
    	export_map->DecRef();    	
    	index=0;
    	
    	const TLiwGenericParam* export_err = outps->FindFirst(index,KErrorCode);
    	if(export_err)
    	result = export_err->Value().AsTInt32();    	    	
    }    
    
    outps->Reset();
	inps->Reset();	
   
    
    GetLandMarkId(inps,outps,interface,KName,KDescription);
    RemoveLandmark(inps,outps,interface);
    
    interface->Close();	
	delete iServiceHandler;
  
  	__UHEAP_MARKEND;
  	if(result == 1000)
  		result = KErrNone;
  	return result;
    }
 
// -----------------------------------------------------------------------------
// Ctlandmark_provider::TestExportVarByPos
// To test export by changing order of input params with Null/invalid landmark Id
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctlandmark_provider::TestExportVarByPos( CStifItemParser& aItem )
    {       
    _LIT(KName,"Landmark1");
    _LIT(KDescription,"TestLandmark1");
     _LIT(KFilePath, "c:\\eposLmTestPos.lmx");
 	 _LIT(KPosMimeType, "application/vnd.nokia.landmarkcollection+xml");
    TInt32 result = KErrNone;
    
    __UHEAP_MARK;
    RFile LogResult;
    RFs LogResultSession;
    User::LeaveIfError(LogResultSession.Connect());
    if(LogResult.Open(LogResultSession ,KFilePath , EFileWrite | EFileShareAny )  != KErrNotFound)
        {
        LogResult.Close();

		LogResultSession.Delete(KFilePath);
		
        LogResultSession.Close();
        }
    
    LogResult.Close();
    LogResultSession.Close();
    
    
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    MLiwInterface* interface = NULL;
    CLiwGenericParamList* inps = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outps = &(iServiceHandler->OutParamListL());

 	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);

	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray a;
	a.AppendL(crit);    
	
	iServiceHandler->AttachL(a);
	iServiceHandler->ExecuteServiceCmdL(*crit, *inps, *outps); 

	a.Reset();
	delete crit;
	
	TInt pos = 0;

	outps->FindFirst( pos, KIDataSource );
	if(pos != KErrNotFound)
		{
		interface = (*outps)[pos].Value().AsInterface();	
		}

	outps->Reset();
	inps->Reset();
	
	TLiwGenericParam param;
	TInt index = 0;
    if(!result)
    {
    	// Call Export
    	
    	CLiwMap* export_map = CLiwDefaultMap::NewL();
    	CLiwList* landmarkIdList = CLiwDefaultList::NewL();
    	landmarkIdList->AppendL(TLiwVariant(_L("-25")));
    	    	
   		export_map->InsertL(KDestinationFile,TLiwVariant(KFilePath));
        export_map->InsertL(KMimeType,TLiwVariant(KPosMimeType));
        export_map->InsertL(KIdList,TLiwVariant(landmarkIdList));
    	landmarkIdList->DecRef();
        
        param.SetNameAndValueL(KNullDesC8,TLiwVariant(KLandmark));
    	inps->AppendL(param);
    	param.Reset();
    	
    	param.SetNameAndValueL(KNullDesC8,TLiwVariant(export_map));
    	inps->AppendL(param);
    	param.Reset();    
    	
    	interface->ExecuteCmdL(KExport,*inps,*outps,0,0);
    	export_map->DecRef();    	
    	index=0;
    	
    	const TLiwGenericParam* export_err = outps->FindFirst(index,KErrorCode);
    	if(export_err)
    	result = export_err->Value().AsTInt32();    	    	
    }    
    
    outps->Reset();
	inps->Reset();
	
	GetLandMarkId(inps,outps,interface,KName,KDescription);
    RemoveLandmark(inps,outps,interface);
    
    interface->Close();	
	delete iServiceHandler;
  
  	__UHEAP_MARKEND;
  	if(result == 1000)
  		result = KErrNone;
  	return result;
    }
    
    
// -----------------------------------------------------------------------------
// Ctlandmark_provider::TestImportVarByOrder
// To test import by changing order of input params with file available/not available
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctlandmark_provider::TestImportVarByOrder( CStifItemParser& aItem )
    {       
    _LIT(KName,"Landmark_ImportOrder");
    _LIT(KDescription,"TestLandmark_ImportOrder");
     _LIT(KFilePath, "c:\\importLmTestOrder.lmx");
 	 _LIT(KPosMimeType, "application/vnd.nokia.landmarkcollection+xml");
 
    TInt32 result = KErrNone;
    TBuf<40> buf;
    
    __UHEAP_MARK;
  
  	RFile LogResult;
    RFs LogResultSession;
    User::LeaveIfError(LogResultSession.Connect());
    if(LogResult.Open(LogResultSession ,KFilePath , EFileWrite | EFileShareAny )  != KErrNotFound)
        {
        LogResult.Close();

		LogResultSession.Delete(KFilePath);
		
        LogResultSession.Close();
        }
    
    LogResult.Close();
    LogResultSession.Close();
    
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    MLiwInterface* interface = NULL;
    CLiwGenericParamList* inps = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outps = &(iServiceHandler->OutParamListL());

 	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);

	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray a;
	a.AppendL(crit);    
	
	iServiceHandler->AttachL(a);
	iServiceHandler->ExecuteServiceCmdL(*crit, *inps, *outps); 

	a.Reset();
	delete crit;
	
	TInt pos = 0;

	outps->FindFirst( pos, KIDataSource );
	if(pos != KErrNotFound)
		{
		interface = (*outps)[pos].Value().AsInterface();	
		}

	outps->Reset();
	inps->Reset();
	
	TLiwGenericParam param;
	TInt index = 0;
    // Add landmark, fetch its id using getlist
       
    CLiwMap* landmarkMap = CLiwDefaultMap::NewL();
             
    //name
    landmarkMap->InsertL(KLandmarkName,TLiwVariant(KName));
      
    //description
    landmarkMap->InsertL(KLandmarkDesc,TLiwVariant(KDescription));
    
    param.SetNameAndValueL(KDataFields,TLiwVariant(landmarkMap));
    inps->AppendL(param);
    param.Reset();       
    
    param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
    inps->AppendL(param);
    param.Reset();
    
    interface->ExecuteCmdL(KAdd,*inps,*outps,0,0);
    landmarkMap->DecRef();    
     
    const TLiwGenericParam* err = outps->FindFirst(index,KErrorCode);
    if(err)
    	result = err->Value().AsTInt32();
    
    if(!result)
    {
    	outps->Reset();
		inps->Reset();
		
    	CLiwMap* getlistlandmark_map = CLiwDefaultMap::NewL();      
      	getlistlandmark_map->InsertL(KLandmarkName,TLiwVariant(KName));
      
    	//description
    	getlistlandmark_map->InsertL(KLandmarkDesc,TLiwVariant(KDescription));
    
    	param.SetNameAndValueL(KFilter,TLiwVariant(getlistlandmark_map));
    	inps->AppendL(param);
    	param.Reset();
    
    	param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
    	inps->AppendL(param);
    	param.Reset();
    	
    	interface->ExecuteCmdL(KGetList,*inps,*outps,0,0);
    	getlistlandmark_map->DecRef();
    
    	const TLiwGenericParam* getlist_err = outps->FindFirst(index,KErrorCode);
    	if(getlist_err)
    		result = getlist_err->Value().AsTInt32();
    }    
      	
    
	if(!result)
	{
		// Get the landmark Id
		pos=0;
		const TLiwGenericParam* output = outps->FindFirst( pos,_L8("ReturnValue"));
		TInt item_found = 0;
			
		if(output)     
		{
			CLiwIterable* iterlist = output->Value().AsIterable();

		    TLiwVariant data;
	    	      
		    while( iterlist->NextL(data))
			{
				const CLiwMap* res = data.AsMap();
				if ( res )
				{
					TLiwVariant new_data;
					if(res->FindL(KId, new_data))
					{
						TPtrC lid = new_data.AsDes();
						buf.Copy(lid);
						iLog->Log(buf);
						iLog->Log(_L("found landmark Id of the entry"));																						
					}
					new_data.Reset();
				}
			 }			  		
			 data.Reset();	
		}
		
		outps->Reset();
		inps->Reset();	
	
		// Call Export and then Import
    	
   		CLiwMap* export_map = CLiwDefaultMap::NewL();
   		
    	CLiwList* landmarkIdList = CLiwDefaultList::NewL();
    	landmarkIdList->AppendL(TLiwVariant(buf));       	   
    	
   		export_map->InsertL(KDestinationFile,TLiwVariant(KFilePath));
        export_map->InsertL(KMimeType,TLiwVariant(KPosMimeType));
        export_map->InsertL(KIdList,TLiwVariant(landmarkIdList));
    	landmarkIdList->DecRef();   
    	
    	
    	param.SetNameAndValueL(KDataFields,TLiwVariant(export_map));
    	inps->AppendL(param);
    	param.Reset();
    
    	param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
    	inps->AppendL(param);
    	param.Reset();
    	
    	interface->ExecuteCmdL(KExport,*inps,*outps,0,0);
    	export_map->DecRef();    	
    	index=0;
    	
    	const TLiwGenericParam* export_err = outps->FindFirst(index,KErrorCode);
    	if(export_err)
    	result = export_err->Value().AsTInt32();     	
       	     
       	if(!result)
       	{
       		outps->Reset();
			inps->Reset();
			CLiwMap* import_map = CLiwDefaultMap::NewL();
			import_map->InsertL(KMimeType,TLiwVariant(KPosMimeType));
    		import_map->InsertL(KSourceFile,TLiwVariant(KFilePath));    	
    		
        	param.SetNameAndValueL(KDataFields,TLiwVariant(import_map));
    		inps->AppendL(param);
    		param.Reset();  
    		
    		param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
    		inps->AppendL(param);
    		param.Reset(); 	
    	
    		interface->ExecuteCmdL(KImport,*inps,*outps,0,0);
    		import_map->DecRef();    	
    		index=0;
    	
    		const TLiwGenericParam* import_err = outps->FindFirst(index,KErrorCode);
    		if(import_err)
    		result = import_err->Value().AsTInt32(); 
       	}
        
    }    
    
    // Remove the landmark added
        
    outps->Reset();
	inps->Reset();
	
   	CLiwMap* remove_map = CLiwDefaultMap::NewL();
   	remove_map->InsertL(KId,TLiwVariant(buf));
      
   	param.SetNameAndValueL(KNullDesC8,TLiwVariant(KLandmark));
   	inps->AppendL(param);
   	param.Reset();
    	
   	param.SetNameAndValueL(KNullDesC8,TLiwVariant(remove_map));
   	inps->AppendL(param);
   	param.Reset();    
    	
   	interface->ExecuteCmdL(KRemove,*inps,*outps,0,0);
   	remove_map->DecRef();    	
   	index=0;
    	
   	const TLiwGenericParam* remove_err = outps->FindFirst(index,KErrorCode);
   	if(remove_err)
    	result = remove_err->Value().AsTInt32();    	
    	
    outps->Reset();
	inps->Reset();
    interface->Close();	
	delete iServiceHandler;
  
  	__UHEAP_MARKEND;
  	if(result == SErrNotFound)
  		result = KErrNone;
  	return result;
    }

// -----------------------------------------------------------------------------
// Ctlandmark_provider::TestImportVarByPos
// To test import for position based parsing 
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctlandmark_provider::TestImportVarByPos( CStifItemParser& aItem )
    {       
    _LIT(KName,"Landmark_Import");
    _LIT(KDescription,"TestLandmark_ImportPos");
     _LIT(KFilePath, "c:\\importLmTestPos.lmx");
 	 _LIT(KPosMimeType, "application/vnd.nokia.landmarkcollection+xml");
 
    TInt32 result = KErrNone;
    TBuf<40> buf;
    
    __UHEAP_MARK;
   
   RFile LogResult;
    RFs LogResultSession;
    User::LeaveIfError(LogResultSession.Connect());
    if(LogResult.Open(LogResultSession ,KFilePath , EFileWrite | EFileShareAny )  != KErrNotFound)
        {
        LogResult.Close();

		LogResultSession.Delete(KFilePath);
		
        LogResultSession.Close();
        }
    
    LogResult.Close();
    LogResultSession.Close();
    
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    MLiwInterface* interface = NULL;
    CLiwGenericParamList* inps = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outps = &(iServiceHandler->OutParamListL());

 	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);

	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray a;
	a.AppendL(crit);    
	
	iServiceHandler->AttachL(a);
	iServiceHandler->ExecuteServiceCmdL(*crit, *inps, *outps); 

	a.Reset();
	delete crit;
	
	TInt pos = 0;

	outps->FindFirst( pos, KIDataSource );
	if(pos != KErrNotFound)
		{
		interface = (*outps)[pos].Value().AsInterface();	
		}

	outps->Reset();
	inps->Reset();
	
	TLiwGenericParam param;
	TInt index = 0;
    // Add landmark, fetch its id using getlist
       
    CLiwMap* landmarkMap = CLiwDefaultMap::NewL();
             
    //name
    landmarkMap->InsertL(KLandmarkName,TLiwVariant(KName));
      
    //description
    landmarkMap->InsertL(KLandmarkDesc,TLiwVariant(KDescription));
    
    param.SetNameAndValueL(KDataFields,TLiwVariant(landmarkMap));
    inps->AppendL(param);
    param.Reset();       
    
    param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
    inps->AppendL(param);
    param.Reset();
    
    interface->ExecuteCmdL(KAdd,*inps,*outps,0,0);
    landmarkMap->DecRef();    
     
    const TLiwGenericParam* err = outps->FindFirst(index,KErrorCode);
    if(err)
    	result = err->Value().AsTInt32();
    
    if(!result)
    {
    	outps->Reset();
		inps->Reset();
		
    	CLiwMap* getlistlandmark_map = CLiwDefaultMap::NewL();      
      	getlistlandmark_map->InsertL(KLandmarkName,TLiwVariant(KName));
      
    	//description
    	getlistlandmark_map->InsertL(KLandmarkDesc,TLiwVariant(KDescription));
    
    	param.SetNameAndValueL(KFilter,TLiwVariant(getlistlandmark_map));
    	inps->AppendL(param);
    	param.Reset();
    
    	param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
    	inps->AppendL(param);
    	param.Reset();
    	
    	interface->ExecuteCmdL(KGetList,*inps,*outps,0,0);
    	getlistlandmark_map->DecRef();
    
    	const TLiwGenericParam* getlist_err = outps->FindFirst(index,KErrorCode);
    	if(getlist_err)
    		result = getlist_err->Value().AsTInt32();
    }    
      	
    
	if(!result)
	{
		// Get the landmark Id
		pos=0;
		const TLiwGenericParam* output = outps->FindFirst( pos,_L8("ReturnValue"));
		TInt item_found = 0;
			
		if(output)     
		{
			CLiwIterable* iterlist = output->Value().AsIterable();

		    TLiwVariant data;
	    	      
		    while( iterlist->NextL(data))
			{
				const CLiwMap* res = data.AsMap();
				if ( res )
				{
					TLiwVariant new_data;
					if(res->FindL(KId, new_data))
					{
						TPtrC lid = new_data.AsDes();
						buf.Copy(lid);
						iLog->Log(buf);
						iLog->Log(_L("found landmark Id of the entry"));																						
					}
					new_data.Reset();
				}
			 }			  		
			 data.Reset();	
		}
		
		outps->Reset();
		inps->Reset();	
	
		// Call Export and then Import
    	
   		CLiwMap* export_map = CLiwDefaultMap::NewL();
   		
    	CLiwList* landmarkIdList = CLiwDefaultList::NewL();
    	landmarkIdList->AppendL(TLiwVariant(buf));       	   
    	
   		export_map->InsertL(KDestinationFile,TLiwVariant(KFilePath));
        export_map->InsertL(KMimeType,TLiwVariant(KPosMimeType));
        export_map->InsertL(KIdList,TLiwVariant(landmarkIdList));
    	landmarkIdList->DecRef();   
    	
    	
    	param.SetNameAndValueL(KDataFields,TLiwVariant(export_map));
    	inps->AppendL(param);
    	param.Reset();
    
    	param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
    	inps->AppendL(param);
    	param.Reset();
    	
    	interface->ExecuteCmdL(KExport,*inps,*outps,0,0);
    	export_map->DecRef();    	
    	index=0;
    	
    	const TLiwGenericParam* export_err = outps->FindFirst(index,KErrorCode);
    	if(export_err)
    	result = export_err->Value().AsTInt32();     	
       	     
       	if(!result)
       	{
       		outps->Reset();
			inps->Reset();
			CLiwMap* import_map = CLiwDefaultMap::NewL();
			import_map->InsertL(KMimeType,TLiwVariant(KPosMimeType));
    		import_map->InsertL(KSourceFile,TLiwVariant(KFilePath));
    	
    		param.SetNameAndValueL(KNullDesC8,TLiwVariant(KLandmark));
    		inps->AppendL(param);
    		param.Reset();
    		
        	param.SetNameAndValueL(KNullDesC8,TLiwVariant(import_map));
    		inps->AppendL(param);
    		param.Reset();   	
    	
    		interface->ExecuteCmdL(KImport,*inps,*outps,0,0);
    		import_map->DecRef();    	
    		index=0;
    	
    		const TLiwGenericParam* import_err = outps->FindFirst(index,KErrorCode);
    		if(import_err)
    		result = import_err->Value().AsTInt32(); 
       	}
        
    }    
    
    // Remove the landmark added
        
    outps->Reset();
	inps->Reset();
	
   	CLiwMap* remove_map = CLiwDefaultMap::NewL();
   	remove_map->InsertL(KId,TLiwVariant(buf));
      
   	param.SetNameAndValueL(KNullDesC8,TLiwVariant(KLandmark));
   	inps->AppendL(param);
   	param.Reset();
    	
   	param.SetNameAndValueL(KNullDesC8,TLiwVariant(remove_map));
   	inps->AppendL(param);
   	param.Reset();    
    	
   	interface->ExecuteCmdL(KRemove,*inps,*outps,0,0);
   	remove_map->DecRef();    	
   	index=0;
    	
   	const TLiwGenericParam* remove_err = outps->FindFirst(index,KErrorCode);
   	if(remove_err)
    	result = remove_err->Value().AsTInt32();    	
    	
    outps->Reset();
	inps->Reset();
    interface->Close();	
	delete iServiceHandler;
  
  	__UHEAP_MARKEND;
  	if(result == SErrNotFound)
  		result = KErrNone;
  	return result;
    }     
    
// -----------------------------------------------------------------------------
// Ctlandmark_provider::TestOrganiseVarByOrder
// To test organise passing input not in order
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctlandmark_provider::TestOrganiseVarByOrder( CStifItemParser& aItem )
    {       
    _LIT(KName,"Landmark_OrgOrder");
    _LIT(KDescription,"TestLandmark_OrgOrder");
    _LIT(CatName,"Category_OrgOrder");
    TInt32 result = KErrNone;
    TInt add_lmresult = 0;
    TInt add_ctresult = -2;
    TInt del_lmresult = 0;
    TInt del_ctresult =0;
    
     
    __UHEAP_MARK;
           
    TBuf<40> Lid;
    TBuf<40> Cid;
    TPtr lid_ptr();
    TPtr cid_ptr();
    
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    MLiwInterface* interface = NULL;
    CLiwGenericParamList* inps = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outps = &(iServiceHandler->OutParamListL());

 	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);

	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray a;
	a.AppendL(crit);    
	
	iServiceHandler->AttachL(a);
	iServiceHandler->ExecuteServiceCmdL(*crit, *inps, *outps); 

	a.Reset();
	delete crit;
	
	TInt pos = 0;

	outps->FindFirst( pos, KIDataSource );
	if(pos != KErrNotFound)
		{
		interface = (*outps)[pos].Value().AsInterface();	
		}

	outps->Reset();
	inps->Reset();
	
	TLiwGenericParam param;
	TInt index = 0;
       
   	add_lmresult = AddLandMark(inps,outps,interface,KName,KDescription);
   	if(!add_lmresult)
   		add_ctresult = AddCategory(inps,outps,interface,CatName);
   	if(!add_lmresult && (!add_ctresult || add_ctresult == SErrEntryExists))
   	{
   		GetLandMarkId(inps,outps,interface,KName,KDescription);
   		GetCatId(inps,outps,interface,CatName);   	
   	   	
   	   	// Associate the landmark added to the category added
   	   	
   		CLiwMap* organise_map = CLiwDefaultMap::NewL();      
    	organise_map->InsertL(KId,TLiwVariant(category_id));
    	    	
    	CLiwList* landmarkIdList = CLiwDefaultList::NewL();
    	landmarkIdList->AppendL(TLiwVariant(landmark_id));       	   
    	organise_map->InsertL(KIdList,TLiwVariant(landmarkIdList));
    	landmarkIdList->DecRef();  
    	    	
    	param.SetNameAndValueL(KDataFields,TLiwVariant(organise_map));
    	inps->AppendL(param);
    	param.Reset();
    
   		param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
   		inps->AppendL(param);
   		param.Reset();
   		
   		param.SetNameAndValueL(KOperationType,TLiwVariant(KAssociate));
   		inps->AppendL(param);
   		param.Reset();
    	
   		interface->ExecuteCmdL(KOrganise,*inps,*outps,0,0);
   		organise_map->DecRef();
    
   		const TLiwGenericParam* organise_err = outps->FindFirst(pos,KErrorCode);
   		if(organise_err)
   			result = organise_err->Value().AsTInt32();     
    
    	
    	outps->Reset();
		inps->Reset();        
   	}
   	else
   		result = KErrGeneral; // not able to add landmark and category successfully
   	
   	// Remove the landmark and category
    if(!add_lmresult)	
    	del_lmresult = RemoveLandmark(inps,outps,interface);
       
    if(!add_ctresult || add_ctresult == SErrEntryExists)
    	del_ctresult = RemoveCategory(inps,outps,interface);
    
    if(!result)
    {
    	if(del_lmresult)
    		result = del_lmresult;
    	else
    		result = del_ctresult;
    }
    
    outps->Reset();
	inps->Reset();
    interface->Close();	
	delete iServiceHandler;
  
  	__UHEAP_MARKEND;
   	return result;
    }


// -----------------------------------------------------------------------------
// Ctlandmark_provider::TestOrganiseVarByOrder
// To test parsing by position for organise api
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctlandmark_provider::TestOrganiseVarByPos( CStifItemParser& aItem )
    {       
    _LIT(KName,"Landmark_OrgPos");
    _LIT(KDescription,"TestLandmark_OrgPos");
    _LIT(CatName,"Category_OrgPos");
    TInt32 result = KErrNone;
    TInt add_lmresult = 0;
    TInt add_ctresult = -2;
    TInt del_lmresult = 0;
    TInt del_ctresult =0;
    
     
    __UHEAP_MARK;
           
    TBuf<40> Lid;
    TBuf<40> Cid;
    TPtr lid_ptr();
    TPtr cid_ptr();
    
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    MLiwInterface* interface = NULL;
    CLiwGenericParamList* inps = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outps = &(iServiceHandler->OutParamListL());

 	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);

	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray a;
	a.AppendL(crit);    
	
	iServiceHandler->AttachL(a);
	iServiceHandler->ExecuteServiceCmdL(*crit, *inps, *outps); 

	a.Reset();
	delete crit;
	
	TInt pos = 0;

	outps->FindFirst( pos, KIDataSource );
	if(pos != KErrNotFound)
		{
		interface = (*outps)[pos].Value().AsInterface();	
		}

	outps->Reset();
	inps->Reset();
	
	TLiwGenericParam param;
	TInt index = 0;
       
   	add_lmresult = AddLandMark(inps,outps,interface,KName,KDescription);
   	if(!add_lmresult)
   		add_ctresult = AddCategory(inps,outps,interface,CatName);
   	if(!add_lmresult && (!add_ctresult || add_ctresult == SErrEntryExists))
   	{
   		GetLandMarkId(inps,outps,interface,KName,KDescription);
   		GetCatId(inps,outps,interface,CatName);   	
   	   	
   	   	// Associate the landmark added to the category added
   	   	
   		CLiwMap* organise_map = CLiwDefaultMap::NewL();      
    	organise_map->InsertL(KId,TLiwVariant(category_id));
    	    	
    	CLiwList* landmarkIdList = CLiwDefaultList::NewL();
    	landmarkIdList->AppendL(TLiwVariant(landmark_id));       	   
    	organise_map->InsertL(KIdList,TLiwVariant(landmarkIdList));
    	landmarkIdList->DecRef();  
    	  
    	param.SetNameAndValueL(KNullDesC8,TLiwVariant(KLandmark));
   		inps->AppendL(param);
   		param.Reset();
   		  	
    	param.SetNameAndValueL(KNullDesC8,TLiwVariant(organise_map));
    	inps->AppendL(param);
    	param.Reset();   
   		
   		
   		param.SetNameAndValueL(KSort,TLiwVariant(KAssociate));
   		inps->AppendL(param);
   		param.Reset();
    	
   		interface->ExecuteCmdL(KOrganise,*inps,*outps,0,0);
   		organise_map->DecRef();
    
   		const TLiwGenericParam* organise_err = outps->FindFirst(pos,KErrorCode);
   		if(organise_err)
   			result = organise_err->Value().AsTInt32();     
    
    	
    	outps->Reset();
		inps->Reset();        
   	}
   	else
   		result = KErrGeneral; // not able to add landmark and category successfully
   	
   	// Remove the landmark and category
    if(!add_lmresult)	
    	del_lmresult = RemoveLandmark(inps,outps,interface);
       
    if(!add_ctresult || add_ctresult == SErrEntryExists)
    	del_ctresult = RemoveCategory(inps,outps,interface);
    
    if(!result)
    {
    	if(del_lmresult)
    		result = del_lmresult;
    	else
    		result = del_ctresult;
    }
    
    outps->Reset();
	inps->Reset();
    interface->Close();	
	delete iServiceHandler;
  
  	__UHEAP_MARKEND;
   	return result;
    }
    
// -----------------------------------------------------------------------------
// Ctlandmark_provider::TestInvalidServiceDataSourceCombination
// To test invalid service and data source combination for landmarks
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctlandmark_provider::TestInvalidServiceDataSourceCombination( CStifItemParser& aItem )
    {       
    
    TInt32 result = KErrNone;
        
    __UHEAP_MARK;           
  
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    CLiwGenericParamList* inps = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outps = &(iServiceHandler->OutParamListL());

 	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KMsgService);

	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray a;
	a.AppendL(crit);    
	
	iServiceHandler->AttachL(a);
	iServiceHandler->ExecuteServiceCmdL(*crit, *inps, *outps); 

	a.Reset();
	delete crit;
	
	TInt pos = 0;

	outps->FindFirst( pos, KIDataSource );
	if(pos != KErrNotFound)
		{
		result = KErrGeneral;
		}
		

	outps->Reset();
	inps->Reset();

    delete iServiceHandler;
  
  	__UHEAP_MARKEND;
   	return result;
    }
    
    
// -----------------------------------------------------------------------------
// Ctlandmark_provider::TestAddSyncAsyncbitcheck
// To test sync/async bit check for Add Api
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctlandmark_provider::TestAddSyncAsyncbitcheck( CStifItemParser& aItem )
    {    
     _LIT(KName,"Add_Invalid");
    _LIT(KDescription,"Invalid_case_add");
    
    TInt32 result = KErrNone;
       
    __UHEAP_MARK;    
    
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    MLiwInterface* interface = NULL;
    CLiwGenericParamList* inps = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outps = &(iServiceHandler->OutParamListL());

 	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);

	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray a;
	a.AppendL(crit);    
	
	iServiceHandler->AttachL(a);
	iServiceHandler->ExecuteServiceCmdL(*crit, *inps, *outps); 

	a.Reset();
	delete crit;
	
	TInt pos = 0;

	outps->FindFirst( pos, KIDataSource );
	if(pos != KErrNotFound)
		{
		interface = (*outps)[pos].Value().AsInterface();	
		}

	if(!interface)
	{
		delete iServiceHandler;
		return KErrGeneral;
	};
	
	outps->Reset();
	inps->Reset();
	
	TLiwGenericParam param;
	TInt index = 0;	 
	CActiveSchedulerWait* WaitSchedular;
	CLiwMap* landmarkMap = CLiwDefaultMap::NewL();
    TInt32 test_val = KErrGeneral;
      
    CCalCallback *Callback = CCalCallback::NewL(WaitSchedular,test_val);    
    //name
    landmarkMap->InsertL(KLandmarkName,TLiwVariant(KName));
      
    //description
    landmarkMap->InsertL(KLandmarkDesc,TLiwVariant(KDescription));
    
    param.SetNameAndValueL(KDataFields,TLiwVariant(landmarkMap));
    inps->AppendL(param);
    param.Reset();       
    
    param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
    inps->AppendL(param);
    param.Reset();
    
    interface->ExecuteCmdL(KAdd,*inps,*outps,0,Callback);
    landmarkMap->DecRef();
        
    const TLiwGenericParam* err = outps->FindFirst(index,KErrorCode);
    if(err)
    	result = err->Value().AsTInt32();
	
	outps->Reset();
	inps->Reset();
    
	delete Callback;
	interface->Close();
	delete iServiceHandler;
	
	__UHEAP_MARKEND;
	if(result == 1000)
		return KErrNone;
	else
		return result;
	
    }
 
// -----------------------------------------------------------------------------
// Ctlandmark_provider::TestGetListSyncAsyncbitcheck
// To test sync/async bit check for GetList Api
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctlandmark_provider::TestGetListSyncAsyncbitcheck( CStifItemParser& aItem )
    {    
    __UHEAP_MARK; 
	CTestAsync* test = CTestAsync::NewL(2);
	test->Start();
	TInt32 result = test->Result();
	delete test;	
	__UHEAP_MARKEND;
	
	if(result == SErrBadArgumentType)
		return KErrNone;
	else
		return result;
    }


// -----------------------------------------------------------------------------
// Ctlandmark_provider::TestGetListCancel
// To call cancel and check for error value and event flag
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctlandmark_provider::TestGetListCancel( CStifItemParser& aItem )
    {
	__UHEAP_MARK;
  	CTestAsync* test = CTestAsync::NewL(3);
	test->Start();
	TInt32 result = test->Result();
	delete test;
	__UHEAP_MARKEND;	
	return result;
    }
    
// -----------------------------------------------------------------------------
// Ctlandmark_provider::GetListStressTest
// calling getlist async api multiple times
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctlandmark_provider::GetListStressTest( CStifItemParser& aItem )
    {
	__UHEAP_MARK;
  	CTestAsync* test = CTestAsync::NewL(5);
	test->Start();
	TInt32 result = test->Result();
	delete test;
	__UHEAP_MARKEND;
	if(result !=  SErrServiceInUse)
		return KErrGeneral;
	else
	return KErrNone;
    }

// -----------------------------------------------------------------------------
// Ctlandmark_provider::GetListIteratorTestLM
// calling getlist and checking the functionality of Nextl and reset functions on the iterator for landmarks
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctlandmark_provider::GetListIteratorTestLM( CStifItemParser& aItem )
 {
 	__UHEAP_MARK;
	_LIT(KName,"GetList_Iterator");
    _LIT(KDescription,"Iterator Tests");     
 
    TInt32 result = KErrNone;
    TInt item_count_before_reset = 0;
    TInt item_count_after_reset = 0;
    TBuf<40> first_lid_before_reset;
    TBuf<40> first_lid_after_reset;
    TLiwGenericParam param;
    
 
    
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    MLiwInterface* interface = NULL;
    CLiwGenericParamList* inps = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outps = &(iServiceHandler->OutParamListL());

 	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);

	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray a;
	a.AppendL(crit);    
	
	iServiceHandler->AttachL(a);
	iServiceHandler->ExecuteServiceCmdL(*crit, *inps, *outps); 

	a.Reset();
	delete crit;
	
	TInt pos = 0;
	
	outps->FindFirst( pos, KIDataSource );
	if(pos != KErrNotFound)
		{
		interface = (*outps)[pos].Value().AsInterface();	
		}

	outps->Reset();
	inps->Reset();
	
	result = AddLandMark(inps,outps,interface,KName,KDescription);
    
    if(!result)
    {
    	outps->Reset();
		inps->Reset();
		
    	CLiwMap* getlistlandmark_map = CLiwDefaultMap::NewL();      
      	getlistlandmark_map->InsertL(KLandmarkName,TLiwVariant(KName));
      
    	//description
    	getlistlandmark_map->InsertL(KLandmarkDesc,TLiwVariant(KDescription));
    
    	param.SetNameAndValueL(KFilter,TLiwVariant(getlistlandmark_map));
    	inps->AppendL(param);
    	param.Reset();
    
    	param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
    	inps->AppendL(param);
    	param.Reset();
    	
    	interface->ExecuteCmdL(KGetList,*inps,*outps,0,0);
    	getlistlandmark_map->DecRef();
    
    	pos=0;
    	const TLiwGenericParam* getlist_err = outps->FindFirst(pos,KErrorCode);
    	if(getlist_err)
    		result = getlist_err->Value().AsTInt32();
    }    
      	
    
	if(!result)
	{
		// Iterate through the list
		pos=0;
		const TLiwGenericParam* output = outps->FindFirst( pos,_L8("ReturnValue"));
			
		if(output)     
		{
			CLiwIterable* iterlist = output->Value().AsIterable();

		    TLiwVariant data;
	    	      
		    while( iterlist->NextL(data))
			{
				item_count_before_reset++;
				const CLiwMap* res = data.AsMap();
				if ( res )
				{
					TLiwVariant new_data;
					if(res->FindL(KId, new_data))
					{
						TPtrC lid = new_data.AsDes();																										
						first_lid_before_reset.Copy(lid);
						landmark_id.Copy(lid);
					}
					new_data.Reset();
				}
			 }			  		
			 data.Reset();
			 
			 iterlist->Reset();
			 while( iterlist->NextL(data))
			 {
				item_count_after_reset++;
				const CLiwMap* res = data.AsMap();
				if ( res )
				{
					TLiwVariant new_data;
					if(res->FindL(KId, new_data))
					{
						TPtrC lid = new_data.AsDes();																										
						first_lid_after_reset.Copy(lid);
					}
					new_data.Reset();
				}			
			 }			  		
			 data.Reset();	
		}
		
		outps->Reset();
		inps->Reset();	
    }
    
    if((item_count_before_reset != item_count_after_reset) || (first_lid_before_reset.Compare(first_lid_after_reset)))
    	result = KErrGeneral;
    
    RemoveLandmark(inps,outps,interface);
    
    interface->Close();
	delete iServiceHandler;
	__UHEAP_MARKEND;
	return result;
 }
             
// -----------------------------------------------------------------------------
// Ctlandmark_provider::GetListIteratorTestCT
// calling getlist and checking the functionality of Nextl and reset functions on the iterator for category
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt Ctlandmark_provider::GetListIteratorTestCT( CStifItemParser& aItem )
 {
 	__UHEAP_MARK;
	_LIT(KCatName,"GetList_IteratorCT");
   
    TInt32 result = KErrNone;
    TInt item_count_before_reset = 0;
    TInt item_count_after_reset = 0;
    TBuf<40> first_cid_before_reset;
    TBuf<40> first_cid_after_reset;
    TLiwGenericParam param;    

    
    CLiwServiceHandler* iServiceHandler = CLiwServiceHandler::NewL();
    MLiwInterface* interface = NULL;
    CLiwGenericParamList* inps = &(iServiceHandler->InParamListL());
    CLiwGenericParamList* outps = &(iServiceHandler->OutParamListL());

 	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1, KIDataSource,KService);

	crit->SetServiceClass(TUid::Uid(KLiwClassBase));

	RCriteriaArray a;
	a.AppendL(crit);    
	
	iServiceHandler->AttachL(a);
	iServiceHandler->ExecuteServiceCmdL(*crit, *inps, *outps); 

	a.Reset();
	delete crit;
	
	TInt pos = 0;
	
	outps->FindFirst( pos, KIDataSource );
	if(pos != KErrNotFound)
		{
		interface = (*outps)[pos].Value().AsInterface();	
		}

	outps->Reset();
	inps->Reset();
	
	result = AddCategory(inps,outps,interface,KCatName);
    
    if(!result)
    {
    	outps->Reset();
		inps->Reset();
		
    	CLiwMap* getlistcategory_map = CLiwDefaultMap::NewL();      
      	getlistcategory_map->InsertL(KCategoryName,TLiwVariant(KCatName));      
    
    	param.SetNameAndValueL(KFilter,TLiwVariant(getlistcategory_map));
    	inps->AppendL(param);
    	param.Reset();
    
    	param.SetNameAndValueL(KContentType,TLiwVariant(KCategory));
    	inps->AppendL(param);
    	param.Reset();
    	
    	interface->ExecuteCmdL(KGetList,*inps,*outps,0,0);
    	getlistcategory_map->DecRef();
    
    	pos=0;
    	const TLiwGenericParam* getlist_err = outps->FindFirst(pos,KErrorCode);
    	if(getlist_err)
    		result = getlist_err->Value().AsTInt32();
    }    
      	
    
	if(!result)
	{
		// Iterate through the list
		pos=0;
		const TLiwGenericParam* output = outps->FindFirst( pos,_L8("ReturnValue"));
			
		if(output)     
		{
			CLiwIterable* iterlist = output->Value().AsIterable();

		    TLiwVariant data;
	    	      
		    while( iterlist->NextL(data))
			{
				item_count_before_reset++;
				const CLiwMap* res = data.AsMap();
				if ( res )
				{
					TLiwVariant new_data;
					if(res->FindL(KId, new_data))
					{
						TPtrC cid = new_data.AsDes();																										
						first_cid_before_reset.Copy(cid);
						category_id.Copy(cid);
					}
					new_data.Reset();
				}
			 }			  		
			 data.Reset();
			 
			 iterlist->Reset();
			 while( iterlist->NextL(data))
			 {
				item_count_after_reset++;
				const CLiwMap* res = data.AsMap();
				if ( res )
				{
					TLiwVariant new_data;
					if(res->FindL(KId, new_data))
					{
						TPtrC cid = new_data.AsDes();																										
						first_cid_after_reset.Copy(cid);
					}
					new_data.Reset();
				}			
			 }			  		
			 data.Reset();	
		}
		
		outps->Reset();
		inps->Reset();	
    }
    
    if((item_count_before_reset != item_count_after_reset) || (first_cid_before_reset.Compare(first_cid_after_reset)))
    	result = KErrGeneral;
    
    RemoveCategory(inps,outps,interface);
    interface->Close();
	delete iServiceHandler;
	__UHEAP_MARKEND;
	return result;
 }
                                       
// Helper functions

TInt RemoveLandmark(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface)
{
	TInt ret = 0;
	TLiwGenericParam param;
	TInt pos = 0;
	
	CLiwMap* remove_map = CLiwDefaultMap::NewL();
    remove_map->InsertL(KId,TLiwVariant(landmark_id));
      
    param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
    inparam->AppendL(param);
    param.Reset();
    	
    param.SetNameAndValueL(KDataFields,TLiwVariant(remove_map));
    inparam->AppendL(param);
    param.Reset();    
    	
    interface->ExecuteCmdL(KRemove,*inparam,*outparam,0,0);
    remove_map->DecRef();    	
        	
    const TLiwGenericParam* remove_err = outparam->FindFirst(pos,KErrorCode);
    if(remove_err)
    	ret = remove_err->Value().AsTInt32();        
      	
   	outparam->Reset();
	inparam->Reset();
	return ret;
}

TInt RemoveCategory(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface)
{
	TInt ret = 0;
	TLiwGenericParam param;
	TInt pos = 0;
	
	CLiwMap* remove_map = CLiwDefaultMap::NewL();
    remove_map->InsertL(KId,TLiwVariant(category_id));
      
    param.SetNameAndValueL(KContentType,TLiwVariant(KCategory));
    inparam->AppendL(param);
    param.Reset();
    	
    param.SetNameAndValueL(KDataFields,TLiwVariant(remove_map));
    inparam->AppendL(param);
    param.Reset();    
    	
    interface->ExecuteCmdL(KRemove,*inparam,*outparam,0,0);
    remove_map->DecRef();    	
        	
    const TLiwGenericParam* remove_err = outparam->FindFirst(pos,KErrorCode);
    if(remove_err)
    	ret = remove_err->Value().AsTInt32();        
      	
   	outparam->Reset();
	inparam->Reset();
	return ret;
}
void GetLandMarkId(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface,const TDesC &landmark_name,const TDesC &landmark_description)
{
	TInt ret = 0;	
	TLiwGenericParam param;
	TInt pos = 0;
	
	CLiwMap* getlistlandmark_map = CLiwDefaultMap::NewL();      
    getlistlandmark_map->InsertL(KLandmarkName,TLiwVariant(landmark_name));
      
    //description
    getlistlandmark_map->InsertL(KLandmarkDesc,TLiwVariant(landmark_description));
    
    param.SetNameAndValueL(KFilter,TLiwVariant(getlistlandmark_map));
    inparam->AppendL(param);
    param.Reset();
    
   	param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
   	inparam->AppendL(param);
   	param.Reset();
    	
   	interface->ExecuteCmdL(KGetList,*inparam,*outparam,0,0);
   	getlistlandmark_map->DecRef();
    
   	const TLiwGenericParam* getlist_err = outparam->FindFirst(pos,KErrorCode);
   	if(getlist_err)
   		ret = getlist_err->Value().AsTInt32();       
      	
    
	if(!ret)
	{
		// Get the landmark Id
		pos=0;
		const TLiwGenericParam* output = outparam->FindFirst( pos,_L8("ReturnValue"));
					
		if(output)     
		{
			CLiwIterable* iterlist = output->Value().AsIterable();

		    TLiwVariant data;
	    	      
		    while( iterlist->NextL(data))
			{
				const CLiwMap* res = data.AsMap();
				if ( res )
				{
					TLiwVariant new_data;
					if(res->FindL(KId, new_data))
					{
						TPtrC lid = new_data.AsDes();
						landmark_id.Copy(lid);					
					}
					new_data.Reset();
				}
			 }			  		
			 data.Reset();	
		}
	}
		
		outparam->Reset();
		inparam->Reset();	
}

void GetCatId(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface,const TDesC &category_name)
{
	TInt ret = 0;	
	TLiwGenericParam param;
	TInt pos = 0;
	
	CLiwMap* getlistcategory_map = CLiwDefaultMap::NewL();      
    getlistcategory_map->InsertL(KCategoryName,TLiwVariant(category_name));      
       
    param.SetNameAndValueL(KFilter,TLiwVariant(getlistcategory_map));
    inparam->AppendL(param);
    param.Reset();
    
   	param.SetNameAndValueL(KContentType,TLiwVariant(KCategory));
   	inparam->AppendL(param);
   	param.Reset();
    	
   	interface->ExecuteCmdL(KGetList,*inparam,*outparam,0,0);
   	getlistcategory_map->DecRef();
    
   	const TLiwGenericParam* getlist_err = outparam->FindFirst(pos,KErrorCode);
   	if(getlist_err)
   		ret = getlist_err->Value().AsTInt32();       
      	
    
	if(!ret)
	{
		// Get the category Id
		pos=0;
		const TLiwGenericParam* output = outparam->FindFirst( pos,_L8("ReturnValue"));
					
		if(output)     
		{
			CLiwIterable* iterlist = output->Value().AsIterable();

		    TLiwVariant data;
	    	      
		    while( iterlist->NextL(data))
			{
				const CLiwMap* res = data.AsMap();
				if ( res )
				{
					TLiwVariant new_data;
					if(res->FindL(KId, new_data))
					{
						TPtrC c_id = new_data.AsDes();
						category_id.Copy(c_id);					
					}
					new_data.Reset();
				}
			 }			  		
			 data.Reset();	
		}
	}
		outparam->Reset();
		inparam->Reset();	
}


TInt AddLandMark(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface,const TDesC &landmark_name,const TDesC &landmark_description)     
{
	TInt ret = 0;
	
	TLiwGenericParam param;
	TInt index = 0;
           
    CLiwMap* landmarkMap = CLiwDefaultMap::NewL();
	landmarkMap->InsertL(KLandmarkName,TLiwVariant(landmark_name));
      
    //description
    landmarkMap->InsertL(KLandmarkDesc,TLiwVariant(landmark_description));
    
    param.SetNameAndValueL(KDataFields,TLiwVariant(landmarkMap));
    inparam->AppendL(param);
    param.Reset();       
    
    param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
    inparam->AppendL(param);
    param.Reset();
    
    interface->ExecuteCmdL(KAdd,*inparam,*outparam,0,0);
    landmarkMap->DecRef();    
     
    const TLiwGenericParam* err = outparam->FindFirst(index,KErrorCode);
    if(err)
    	ret = err->Value().AsTInt32();
    outparam->Reset();
	inparam->Reset();
    return ret;
}

TInt AddCategory(CLiwGenericParamList* inparam, CLiwGenericParamList* outparam, MLiwInterface* interface,const TDesC &category_name)     
{
	TInt ret = 0;
	CLiwMap* categoryMap = CLiwDefaultMap::NewL();
    TLiwGenericParam param;    
    
    //name
    categoryMap->InsertL(KCategoryName,TLiwVariant(category_name));
      
    param.SetNameAndValueL(KDataFields,TLiwVariant(categoryMap));
    inparam->AppendL(param);
    param.Reset();       
    
    param.SetNameAndValueL(KContentType,TLiwVariant(KCategory));
    inparam->AppendL(param);
    param.Reset();
    
    interface->ExecuteCmdL(KAdd,*inparam,*outparam,0,0);
    categoryMap->DecRef();
    
    TInt index = 0;
    
    const TLiwGenericParam* err = outparam->FindFirst(index,KErrorCode);
    if(err)
    	ret = err->Value().AsTInt32();
    
    outparam->Reset();
	inparam->Reset();
	return ret;
}

// -----------------------------------------------------------------------------
// Ctlandmark_provider::?member_function
// ?implementation_description
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
/*
TInt Ctlandmark_provider::?member_function(
   CItemParser& aItem )
   {

   ?code

   }
*/

// ========================== OTHER EXPORTED FUNCTIONS =========================
// None

//  End of File
