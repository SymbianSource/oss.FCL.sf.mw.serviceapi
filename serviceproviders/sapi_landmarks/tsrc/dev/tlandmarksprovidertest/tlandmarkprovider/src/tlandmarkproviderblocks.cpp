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
#include <f32file.h>
#include <StifParser.h>
#include <e32std.h>
#include <StifTestInterface.h>
#include <liwgenericparam.h>
#include <liwservicehandler.h>
#include <liwvariant.h>
#include <EPos_CPosLandmarkDatabase.h>
#include <EPos_CPosLandmark.h>
#include <EPos_CPosLandmarkEncoder.h>
#include <EPos_CPosLmCategoryManager.h>
#include <EPos_HPosLmDatabaseInfo.h>
#include <EPos_CPosLmDatabaseManager.h>
#include <lbsposition.h> 
#include "tlandmarkprovider.h"
#include "landmarkliwparams.hrh"

// EXTERNAL DATA STRUCTURES
//extern  ?external_data;

// EXTERNAL FUNCTION PROTOTYPES
//extern ?external_function( ?arg_type,?arg_type );

// CONSTANTS
//const ?type ?constant_var = ?constant;
_LIT(KLmName1, "lm1");
_LIT(KLmName2, "lma2");
_LIT(KLmName3, "lma3");
_LIT(KLmName4, "landmark1");
_LIT(KLmName5, "landmark2");
_LIT(KLmName6, "landmark3");

_LIT(KLmSearchString, "lm*");
_LIT(KLmSearchString1, "lma*");

// MACROS
//#define ?macro ?macro_def
#define PASS  TInt(0)
#define FAIL  (!PASS)


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CTLandmarkProvider::Delete
// Delete here all resources allocated and opened from test methods.
// Called from destructor.
// -----------------------------------------------------------------------------
//
void CTLandmarkProvider::Delete()
    {

    }

// -----------------------------------------------------------------------------
// CTLandmarkProvider::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTLandmarkProvider::RunMethodL(
    CStifItemParser& aItem )
    {

    static TStifFunctionInfo const KFunctions[] =
        {
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function.
        ENTRY( "AddLandmark", CTLandmarkProvider::AddLandmarkL ),
        ENTRY( "UpdateLandmark", CTLandmarkProvider::UpdateLandmarkL ),
        ENTRY( "RemoveLandmark", CTLandmarkProvider::RemoveLandmarkL ),
        ENTRY( "ImportLandmark", CTLandmarkProvider::ImportLandmarkL ),
        ENTRY( "ExportLandmark", CTLandmarkProvider::ExportLandmarkL ),
        ENTRY("LinkCategory", CTLandmarkProvider :: LinkCategoryL ),
        ENTRY("UnLinkCategory", CTLandmarkProvider :: UnLinkCategoryL ),
        ENTRY("LandmarksAsyncTest1", CTLandmarkProvider :: LandmarksAsyncTest1L ),
        ENTRY("LandmarksSyncTest1", CTLandmarkProvider :: LandmarksSyncTest1L ),
        ENTRY( "AddLandmarkDb", CTLandmarkProvider::AddLandmarkDbL ),
        ENTRY( "UpdateLandmarkDb", CTLandmarkProvider::UpdateLandmarkDbL ),
        ENTRY( "RemoveLandmarkDb", CTLandmarkProvider::RemoveLandmarkDbL ),
        ENTRY( "ImportLandmarkDb", CTLandmarkProvider::ImportLandmarkDbL ),
        ENTRY( "ExportLandmarkDb", CTLandmarkProvider::ExportLandmarkDbL ),
        ENTRY("LinkCategoryDb", CTLandmarkProvider :: LinkCategoryDbL ),
        ENTRY("UnLinkCategoryDb", CTLandmarkProvider :: UnLinkCategoryDbL ),
        ENTRY("LandmarksAsyncTest1Db", CTLandmarkProvider :: LandmarksAsyncTest1DbL ),
        ENTRY("LandmarksSyncTest1Db", CTLandmarkProvider :: LandmarksSyncTest1DbL ),
        ENTRY("GetLandmarkGtk", CTLandmarkProvider :: LandmarksGtkL ),
        ENTRY( "AddLandmarkPos", CTLandmarkProvider::AddLandmarkPosL ),
        ENTRY( "UpdateLandmarkPos", CTLandmarkProvider::UpdateLandmarkPosL ),
        ENTRY( "RemoveLandmarkPos", CTLandmarkProvider::RemoveLandmarkPosL ),
        ENTRY( "ImportLandmarkPos", CTLandmarkProvider::ImportLandmarkPosL ),
        ENTRY( "ExportLandmarkPos", CTLandmarkProvider::ExportLandmarkPosL ),
        ENTRY("LinkCategoryPos", CTLandmarkProvider :: LinkCategoryPosL ),
        ENTRY("UnLinkCategoryPos", CTLandmarkProvider :: UnLinkCategoryPosL ),
        ENTRY("LandmarksAsyncTestPos1", CTLandmarkProvider :: LandmarksAsyncTestPos1L ),
        ENTRY("LandmarksSyncTestPos1", CTLandmarkProvider :: LandmarksSyncTestPos1L ),
        };

    const TInt count = sizeof( KFunctions ) /
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CTLandmarkProvider::ExampleL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CTLandmarkProvider::ExampleL( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( KTLandmarkProvider, "TLandmarkProvider" );
    _LIT( KExample, "In Example" );
    TestModuleIf().Printf( 0, KTLandmarkProvider, KExample );
    // Print to log file
    iLog->Log( KExample );

    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, KTLandmarkProvider,
                                KParam, i, &string );
        i++;
        }

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CTLandmarkProvider::AddLandmarkL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CTLandmarkProvider::AddLandmarkL( CStifItemParser& aItem )
    {
    // Print to UI
    _LIT( KTLandmarkProvider, "TLandmarkProvider" );
    _LIT( KExample, "In AddLandmarkL" );
    TestModuleIf().Printf( 0, KTLandmarkProvider, KExample );
    // Print to log file
    iLog->Log( KExample );

	__UHEAP_MARK;
	
	CLiwServiceHandler* ServiceHandler;
	CLiwGenericParamList* inps,*outps;
	MLiwInterface* iIflandmarks;
	
	CreateInterfaceL(ServiceHandler,iIflandmarks);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*iIflandmarks);
	
    inps = &(ServiceHandler->InParamListL());
    outps = &(ServiceHandler->OutParamListL());

	inps->Reset();
	outps->Reset();	

    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, KTLandmarkProvider,
                                KParam, i, &string );
        i++;
        }

    TLiwGenericParam param;
    param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
    inps->AppendL(param);
    param.Reset();
    
    _LIT(KName,"Mainland China");
    _LIT(KDescription,"Extremely good chinese food");
    _LIT(KPhone1,"123456");
    _LIT(KOffice1,"eat");
    _LIT(KOffice2,"sleep");
    _LIT(KOffice3,"drink");
    TReal64 latitude = 45.1122;
    TReal64 longitude = 34.0099;
    TReal32 altitude = 41.0022;
    TReal32 hacc = 0.1234;
    TReal32 vacc = 0.3456;
    TPosition locale;
    locale.SetCurrentTime();
    
    CLiwMap* landmarkMap = CLiwDefaultMap::NewL();
    //uncomment after LIW changes    
    CleanupClosePushL(*landmarkMap);
    inps->AppendL(TLiwGenericParam(KDataFields,TLiwVariant(landmarkMap)));
    iIflandmarks->ExecuteCmdL(KAdd,*inps,*outps,0,0);

    CleanupStack::PopAndDestroy(landmarkMap);

    TInt index1 = 0;
    TInt32 err1 = -1;
    const TLiwGenericParam* outParam1 = outps->FindFirst(index1,KErrorCode);
    if( outParam1 )
      {
      outParam1->Value().Get(err1);
      }
    inps->Reset();
    outps->Reset(); 
    
    landmarkMap = CLiwDefaultMap::NewL();

    //name
    landmarkMap->InsertL(KLandmarkName,TLiwVariant(KName));
    //position
    CLiwMap* position = CLiwDefaultMap::NewL();

    position->InsertL(KLatitude,TLiwVariant(latitude));
    position->InsertL(KLongitude,TLiwVariant(longitude));
    position->InsertL(KAltitude,TLiwVariant(altitude));
    position->InsertL(KHAccuracy,TLiwVariant(hacc));
    position->InsertL(KVAccuracy,TLiwVariant(vacc));
    position->InsertL(KTStamp,TLiwVariant(locale.Time()));    
    landmarkMap->InsertL(KLandmarkPosition,TLiwVariant(position));

    position->DecRef();
    //coverage radius
    TReal32 covRad = 12.3456; 
    landmarkMap->InsertL(KCoverageRadius,TLiwVariant(covRad));
    //categoryInfo
    CLiwList* catList = CLiwDefaultList::NewL();
    CPosLandmarkDatabase* db = CPosLandmarkDatabase ::OpenL(KTestDbUri1);
    CleanupStack::PushL(db);
    ExecuteAndDeleteLD(db->InitializeL());
    CPosLmCategoryManager* catMan = CPosLmCategoryManager::NewL(*db);
    CleanupStack::PushL(catMan);
    RemoveAllCategories(catMan);
    CPosLandmarkCategory* category = CPosLandmarkCategory::NewLC();
    TPosLmItemId catId;
    category->SetCategoryNameL(KOffice1);
  	catId = catMan->AddCategoryL(*category);
  	TBuf<5> catIdString;
    catIdString.Num(catId,EDecimal);
    
    catList->AppendL(TLiwVariant(catIdString));
    category->SetCategoryNameL(KOffice2);
  	catId = catMan->AddCategoryL(*category);
  	TBuf<5> catIdString1;
    catIdString1.Num(catId,EDecimal);
  	catList->AppendL(TLiwVariant(catIdString1));
  	category->SetCategoryNameL(KOffice3);
  	catId = catMan->AddCategoryL(*category);
  	TBuf<5> catIdString2;
    catIdString2.Num(catId,EDecimal);
  	catList->AppendL(TLiwVariant(catIdString2));
    CleanupStack::PopAndDestroy(3,db);
    landmarkMap->InsertL(KCategoryInfo,TLiwVariant(catList));
    catList->DecRef();
    //icon
    _LIT(KFileName,"//s60//icons//qgn_graf_s60_logo.svg");
    landmarkMap->InsertL(KIconFile,TLiwVariant(KFileName));
    landmarkMap->InsertL(KIconIndex,TLiwVariant((TInt32)17));
    landmarkMap->InsertL(KIconMaskIndex,TLiwVariant((TInt32)17));
    //description
    landmarkMap->InsertL(KLandmarkDesc,TLiwVariant(KDescription));
    //lm fields
    CLiwMap* landmarkFields = CLiwDefaultMap::NewL();

    landmarkFields->InsertL(KLandmarkTelephone,TLiwVariant(KPhone1));
    landmarkMap->InsertL(KLandmarkFields,TLiwVariant(landmarkFields));
    landmarkFields->DecRef();
    param.SetNameAndValueL(KDataFields,TLiwVariant(landmarkMap));
    inps->AppendL(param);
    param.Reset();   
    landmarkMap->DecRef();
    
    param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
    inps->AppendL(param);
    param.Reset();

    iIflandmarks->ExecuteCmdL(KAdd,*inps,*outps,0,0);
    TInt index = 0;
    TInt32 err = -1;
    const TLiwGenericParam* outParam = outps->FindFirst(index,KErrorCode);
    //log data
    RFile LogResult;
    RFs LogResultSession;
    User::LeaveIfError(LogResultSession.Connect());
    if(LogResult.Open(LogResultSession ,_L("c:\\testlog1.txt") , EFileWrite | EFileShareAny )  == KErrNotFound)
        {
        TInt err1 = LogResult.Create(LogResultSession ,_L("c:\\testlog1.txt") , EFileWrite | EFileShareAny ) ;
        }
    TInt End = 0 ;
    LogResult.Seek(ESeekEnd , End) ; //Seek to end of the file before writing
    if( outParam )
      {
      outParam->Value().Get(err);
      TBuf8<50> error;
      TRealFormat format;
      error.Num(err,format) ;
      LogResult.Write(_L8("AddLandmarkL Error="));
      LogResult.Write(error);
      LogResult.Write(_L8("\n"));
      }
    LogResult.Close();
    LogResultSession.Close();
	CleanupStack::PopAndDestroy(2,ServiceHandler);
	__UHEAP_MARKEND;
	
    return err;

    }

// -----------------------------------------------------------------------------
// CTLandmarkProvider::AddLandmarkPosL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CTLandmarkProvider::AddLandmarkPosL( CStifItemParser& aItem )
    {
    // Print to UI
    _LIT( KTLandmarkProvider, "TLandmarkProvider" );
    _LIT( KExample, "In AddLandmarkPosL" );
    TestModuleIf().Printf( 0, KTLandmarkProvider, KExample );
    // Print to log file
    iLog->Log( KExample );

	__UHEAP_MARK;
	CLiwServiceHandler* ServiceHandler;
	CLiwGenericParamList* inps,*outps;
	MLiwInterface* iIflandmarks;
	
	CreateInterfaceL(ServiceHandler,iIflandmarks);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*iIflandmarks);
	
    inps = &(ServiceHandler->InParamListL());
    outps = &(ServiceHandler->OutParamListL());

	inps->Reset();
	outps->Reset();
	
    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, KTLandmarkProvider,
                                KParam, i, &string );
        i++;
        }

    TLiwGenericParam param;
    param.SetNameAndValueL(KNullDesC8,TLiwVariant(KLandmark));
    inps->AppendL(param);
    param.Reset();
    
    TPosition locale;
    locale.SetCurrentTime();
    
    CLiwMap* landmarkMap = CLiwDefaultMap::NewL();
    inps->AppendL(TLiwGenericParam(KNullDesC8,TLiwVariant(landmarkMap)));
    iIflandmarks->ExecuteCmdL(KAdd,*inps,*outps,0,0);
    landmarkMap->DecRef();
    TInt index = 0;
    TInt32 err = KErrGeneral;
        
    const TLiwGenericParam* outParam = outps->FindFirst(index,KErrorCode);
    //log data
    RFile LogResult;
    RFs LogResultSession;
    User::LeaveIfError(LogResultSession.Connect());
    if(LogResult.Open(LogResultSession ,_L("c:\\testlog1.txt") , EFileWrite | EFileShareAny )  == KErrNotFound)
        {
        TInt err1 = LogResult.Create(LogResultSession ,_L("c:\\testlog1.txt") , EFileWrite | EFileShareAny ) ;
        }
    TInt End = 0 ;
    LogResult.Seek(ESeekEnd , End) ; //Seek to end of the file before writing
    if( outParam )
      {
      outParam->Value().Get(err);
      TBuf8<50> error;
      TRealFormat format;
      error.Num(err,format) ;
      LogResult.Write(_L8("AddLandmarPoskL Error="));
      LogResult.Write(error);
      LogResult.Write(_L8("\n"));
      }
    LogResult.Close();
    LogResultSession.Close();

	CleanupStack::PopAndDestroy(2,ServiceHandler);
	__UHEAP_MARKEND;    
    return err;
    }
    
// -----------------------------------------------------------------------------
// CTLandmarkProvider::UpdateLandmarkL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CTLandmarkProvider::UpdateLandmarkL( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( KTLandmarkProvider, "TLandmarkProvider" );
    _LIT( KExample, "In Example" );
    TestModuleIf().Printf( 0, KTLandmarkProvider, KExample );
    // Print to log file
    iLog->Log( KExample );
	
	__UHEAP_MARK;
	CLiwServiceHandler* ServiceHandler;
	CLiwGenericParamList* inps,*outps;
	MLiwInterface* iIflandmarks;
	
	CreateInterfaceL(ServiceHandler,iIflandmarks);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*iIflandmarks);
	
    inps = &(ServiceHandler->InParamListL());
    outps = &(ServiceHandler->OutParamListL());

	inps->Reset();
	outps->Reset();
	
    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, KTLandmarkProvider,
                                KParam, i, &string );
        i++;
        }
  /*Preconditions*/
  _LIT(KName,"3QC");
  _LIT(KName1,"Mainland China");

  CPosLandmarkDatabase* db = CPosLandmarkDatabase::OpenL(KTestDbUri1);
  CleanupStack::PushL(db);
  ExecuteAndDeleteLD(db->InitializeL());
  RemoveAllLandmarks(db);

  TPosLmItemId lmId;
  CPosLandmark* lm = CPosLandmark::NewLC();
  lm->SetLandmarkNameL(KName1);
  lmId = db->AddLandmarkL(*lm);

  lm = db->ReadLandmarkLC(lmId);

  TLiwGenericParam param;
  param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
  inps->AppendL(param);
  param.Reset();

  CLiwMap* landmarkMap = CLiwDefaultMap::NewL();
  TBuf<5> lmIdString;
  lmIdString.Num(lm->LandmarkId(),EDecimal);
  landmarkMap->InsertL(KId,TLiwVariant(lmIdString));
  landmarkMap->InsertL(KLandmarkName,TLiwVariant(KName));
  param.SetNameAndValueL(KDataFields,TLiwVariant(landmarkMap));
  inps->AppendL(param);
  landmarkMap->DecRef();
  param.Reset();

  iIflandmarks->ExecuteCmdL(KAdd,*inps,*outps,0,0);
  TInt index = 0;
  TInt32 err = -1;
  const TLiwGenericParam* outParam = outps->FindFirst(index,KErrorCode);
  //log data
  RFile LogResult;
  RFs LogResultSession;
  User::LeaveIfError(LogResultSession.Connect());
  if(LogResult.Open(LogResultSession ,_L("c:\\testlog1.txt") , EFileWrite | EFileShareAny )  == KErrNotFound)
      {
      TInt err1 = LogResult.Create(LogResultSession ,_L("c:\\testlog1.txt") , EFileWrite | EFileShareAny ) ;
      }
  TInt End = 0 ;
  LogResult.Seek(ESeekEnd , End) ; //Seek to end of the file before writing
  if( outParam )
    {
    outParam->Value().Get(err);
    TBuf8<50> error;
    TRealFormat format;
    error.Num(err,format) ;
    LogResult.Write(_L8("UpdateLandmarkL Error="));
    LogResult.Write(error);
    LogResult.Write(_L8("\n"));
    }
  LogResult.Close();
  LogResultSession.Close();
  

  CleanupStack::PopAndDestroy(lm);

  CleanupStack::PopAndDestroy(2,db);

	CleanupStack::PopAndDestroy(2,ServiceHandler);
	ReleaseLandmarkResources();
	
	__UHEAP_MARKEND;  

  return err;
  }

// -----------------------------------------------------------------------------
// CTLandmarkProvider::UpdateLandmarkPosL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CTLandmarkProvider::UpdateLandmarkPosL( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( KTLandmarkProvider, "TLandmarkProvider" );
    _LIT( KExample, "In UpdateLandmarkPosL" );
    TestModuleIf().Printf( 0, KTLandmarkProvider, KExample );
    // Print to log file
    iLog->Log( KExample );

	__UHEAP_MARK;
	CLiwServiceHandler* ServiceHandler;
	CLiwGenericParamList* inps,*outps;
	MLiwInterface* iIflandmarks;
	
	CreateInterfaceL(ServiceHandler,iIflandmarks);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*iIflandmarks);
	
    inps = &(ServiceHandler->InParamListL());
    outps = &(ServiceHandler->OutParamListL());

	inps->Reset();
	outps->Reset();
	
    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, KTLandmarkProvider,
                                KParam, i, &string );
        i++;
        }
  /*Preconditions*/
  _LIT(KName,"3QC");
  _LIT(KName1,"Mainland China");

  CPosLandmarkDatabase* db = CPosLandmarkDatabase::OpenL(KTestDbUri1);
  CleanupStack::PushL(db);
  ExecuteAndDeleteLD(db->InitializeL());
  RemoveAllLandmarks(db);

  TPosLmItemId lmId;
  CPosLandmark* lm = CPosLandmark::NewLC();
  lm->SetLandmarkNameL(KName1);
  lmId = db->AddLandmarkL(*lm);

  lm = db->ReadLandmarkLC(lmId);

  TLiwGenericParam param;
  param.SetNameAndValueL(KNullDesC8,TLiwVariant(KLandmark));
  inps->AppendL(param);
  param.Reset();

  CLiwMap* landmarkMap = CLiwDefaultMap::NewL();
  TBuf<5> lmIdString;
  lmIdString.Num(lm->LandmarkId(),EDecimal);
  landmarkMap->InsertL(KId,TLiwVariant(lmIdString));
  landmarkMap->InsertL(KLandmarkName,TLiwVariant(KName));
  param.SetNameAndValueL(KNullDesC8,TLiwVariant(landmarkMap));
  inps->AppendL(param);
  landmarkMap->DecRef();
  param.Reset();

  iIflandmarks->ExecuteCmdL(KAdd,*inps,*outps,0,0);
  TInt index = 0;
  TInt32 err = -1;
  const TLiwGenericParam* outParam = outps->FindFirst(index,KErrorCode);
  //log data
  RFile LogResult;
  RFs LogResultSession;
  User::LeaveIfError(LogResultSession.Connect());
  if(LogResult.Open(LogResultSession ,_L("c:\\testlog1.txt") , EFileWrite | EFileShareAny )  == KErrNotFound)
      {
      TInt err1 = LogResult.Create(LogResultSession ,_L("c:\\testlog1.txt") , EFileWrite | EFileShareAny ) ;
      }
  TInt End = 0 ;
  LogResult.Seek(ESeekEnd , End) ; //Seek to end of the file before writing
  if( outParam )
    {
    outParam->Value().Get(err);
    TBuf8<50> error;
    TRealFormat format;
    error.Num(err,format) ;
    LogResult.Write(_L8("UpdateLandmarkL Error="));
    LogResult.Write(error);
    LogResult.Write(_L8("\n"));
    }
  LogResult.Close();
  LogResultSession.Close();
  

  CleanupStack::PopAndDestroy(lm);

  CleanupStack::PopAndDestroy(2,db);
  ReleaseLandmarkResources();
	
	CleanupStack::PopAndDestroy(2,ServiceHandler);
	ReleaseLandmarkResources(); 
	__UHEAP_MARKEND;
	
  return err;
  }
  
// -----------------------------------------------------------------------------
// CTLandmarkProvider::RemoveLandmarkL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CTLandmarkProvider::RemoveLandmarkL( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( KTLandmarkProvider, "TLandmarkProvider" );
    _LIT( KExample, "In Example" );
    TestModuleIf().Printf( 0, KTLandmarkProvider, KExample );
    // Print to log file
    iLog->Log( KExample );

	__UHEAP_MARK;
	CLiwServiceHandler* ServiceHandler;
	CLiwGenericParamList* inps,*outps;
	MLiwInterface* iIflandmarks;
	
	CreateInterfaceL(ServiceHandler,iIflandmarks);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*iIflandmarks);
	
    inps = &(ServiceHandler->InParamListL());
    outps = &(ServiceHandler->OutParamListL());

	inps->Reset();
	outps->Reset();
	
    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, KTLandmarkProvider,
                                KParam, i, &string );
        i++;
        }
    //preconditions
    _LIT(KName1,"Mainland China");
    CPosLandmarkDatabase* db = CPosLandmarkDatabase::OpenL(KTestDbUri1);
    CleanupStack::PushL(db);
    ExecuteAndDeleteLD(db->InitializeL());
    RemoveAllLandmarks(db);

    CPosLandmark* lm = CPosLandmark::NewLC();
    lm->SetLandmarkNameL(KName1);
    db->AddLandmarkL(*lm);

    TLiwGenericParam param;
    param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
    inps->AppendL(param);
    param.Reset();

    CLiwMap* landmarkMap = CLiwDefaultMap::NewL();
    //landmarkMap->InsertL(KId,TLiwVariant((TInt32)lm->LandmarkId()));
	TBuf<5> lmIdString;
	lmIdString.Num(lm->LandmarkId(),EDecimal);
    landmarkMap->InsertL(KId,TLiwVariant(lmIdString));
    param.SetNameAndValueL(KDataFields,TLiwVariant(landmarkMap));
    inps->AppendL(param);
    landmarkMap->DecRef();
    param.Reset();

    iIflandmarks->ExecuteCmdL(KRemove,*inps,*outps,0,0);
    TInt index = 0;
    TInt32 err = -1;
    const TLiwGenericParam* outParam = outps->FindFirst(index,KErrorCode);
    //log data
    RFile LogResult;
    RFs LogResultSession;
    User::LeaveIfError(LogResultSession.Connect());
    if(LogResult.Open(LogResultSession ,_L("c:\\testlog1.txt") , EFileWrite | EFileShareAny )  == KErrNotFound)
        {
        TInt err1 = LogResult.Create(LogResultSession ,_L("c:\\testlog1.txt") , EFileWrite | EFileShareAny ) ;
        }
    TInt End = 0 ;
    LogResult.Seek(ESeekEnd , End) ; //Seek to end of the file before writing
    if( outParam )
      {
      outParam->Value().Get(err);
      TBuf8<50> error;
      TRealFormat format;
      error.Num(err,format) ;
      LogResult.Write(_L8("RemoveLandmarkL Error="));
      LogResult.Write(error);
      LogResult.Write(_L8("\n"));
      }
    LogResult.Close();
    LogResultSession.Close();
    


    CleanupStack::PopAndDestroy(2,db);
    ReleaseLandmarkResources();
 	CleanupStack::PopAndDestroy(2,ServiceHandler);
	ReleaseLandmarkResources(); 
	__UHEAP_MARKEND;	
    return err;

    }

// -----------------------------------------------------------------------------
// CTLandmarkProvider::RemoveLandmarkPosL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CTLandmarkProvider::RemoveLandmarkPosL( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( KTLandmarkProvider, "TLandmarkProvider" );
    _LIT( KExample, "In RemoveLandmarkPosL" );
    TestModuleIf().Printf( 0, KTLandmarkProvider, KExample );
    // Print to log file
    iLog->Log( KExample );

	__UHEAP_MARK;
	CLiwServiceHandler* ServiceHandler;
	CLiwGenericParamList* inps,*outps;
	MLiwInterface* iIflandmarks;
	
	CreateInterfaceL(ServiceHandler,iIflandmarks);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*iIflandmarks);
	
    inps = &(ServiceHandler->InParamListL());
    outps = &(ServiceHandler->OutParamListL());

	inps->Reset();
	outps->Reset();
    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, KTLandmarkProvider,
                                KParam, i, &string );
        i++;
        }
    //preconditions
    _LIT(KName1,"Mainland China");
    CPosLandmarkDatabase* db = CPosLandmarkDatabase::OpenL(KTestDbUri1);
    CleanupStack::PushL(db);
    ExecuteAndDeleteLD(db->InitializeL());
    RemoveAllLandmarks(db);

    CPosLandmark* lm = CPosLandmark::NewLC();
    lm->SetLandmarkNameL(KName1);
    db->AddLandmarkL(*lm);

    TLiwGenericParam param;
    param.SetNameAndValueL(KNullDesC8,TLiwVariant(KLandmark));
    inps->AppendL(param);
    param.Reset();

    CLiwMap* landmarkMap = CLiwDefaultMap::NewL();
//    landmarkMap->InsertL(KId,TLiwVariant((TInt32)lm->LandmarkId()));
	TBuf<5> lmIdString;
	lmIdString.Num(lm->LandmarkId(),EDecimal);
    landmarkMap->InsertL(KId,TLiwVariant(lmIdString));
    param.SetNameAndValueL(KNullDesC8,TLiwVariant(landmarkMap));
    inps->AppendL(param);
    landmarkMap->DecRef();
    param.Reset();

    iIflandmarks->ExecuteCmdL(KRemove,*inps,*outps,0,0);
    TInt index = 0;
    TInt32 err = -1;
    const TLiwGenericParam* outParam = outps->FindFirst(index,KErrorCode);
    //log data
    RFile LogResult;
    RFs LogResultSession;
    User::LeaveIfError(LogResultSession.Connect());
    if(LogResult.Open(LogResultSession ,_L("c:\\testlog1.txt") , EFileWrite | EFileShareAny )  == KErrNotFound)
        {
        TInt err1 = LogResult.Create(LogResultSession ,_L("c:\\testlog1.txt") , EFileWrite | EFileShareAny ) ;
        }
    TInt End = 0 ;
    LogResult.Seek(ESeekEnd , End) ; //Seek to end of the file before writing
    if( outParam )
      {
      outParam->Value().Get(err);
      TBuf8<50> error;
      TRealFormat format;
      error.Num(err,format) ;
      LogResult.Write(_L8("RemoveLandmarkL Error="));
      LogResult.Write(error);
      LogResult.Write(_L8("\n"));
      }
    LogResult.Close();
    LogResultSession.Close();
    

    CleanupStack::PopAndDestroy(2,db);
 	CleanupStack::PopAndDestroy(2,ServiceHandler);
	ReleaseLandmarkResources(); 

	__UHEAP_MARKEND;
    return err;

    }

// -----------------------------------------------------------------------------
// CTLandmarkProvider::ImportLandmarkL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CTLandmarkProvider::ImportLandmarkL( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( KTLandmarkProvider, "TLandmarkProvider" );
    _LIT( KExample, "In Example" );
    TestModuleIf().Printf( 0, KTLandmarkProvider, KExample );
    // Print to log file
    iLog->Log( KExample );

	__UHEAP_MARK;
	CLiwServiceHandler* ServiceHandler;
	CLiwGenericParamList* inps,*outps;
	MLiwInterface* iIflandmarks;
	
	CreateInterfaceL(ServiceHandler,iIflandmarks);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*iIflandmarks);
	
    inps = &(ServiceHandler->InParamListL());
    outps = &(ServiceHandler->OutParamListL());

	inps->Reset();
	outps->Reset();

    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, KTLandmarkProvider,
                                KParam, i, &string );
        i++;
        }
    //preconditions
    _LIT(KFilePath, "c:\\eposLm.lmx");
    _LIT8(KPosMimeType, "application/vnd.nokia.landmarkcollection+xml");
    _LIT(KPosMimeType1, "application/vnd.nokia.landmarkcollection+xml");
    _LIT(KName1,"Mainland China");
    _LIT(KName2,"Chung Wah");
    _LIT(KName3,"Aromas of China");

    CPosLandmarkDatabase* db = CPosLandmarkDatabase::OpenL(KTestDbUri1);
    CleanupStack::PushL(db);
    ExecuteAndDeleteLD(db->InitializeL());
    RemoveAllLandmarks(db);

    TPosLmItemId lmId;
    CPosLandmark* lm = CPosLandmark::NewLC();
    lm->SetLandmarkNameL(KName1);
    db->AddLandmarkL(*lm);
    lm->SetLandmarkNameL(KName2);
    db->AddLandmarkL(*lm);
    lm->SetLandmarkNameL(KName3);
    db->AddLandmarkL(*lm);

    CPosLmItemIterator* iterLm = db->LandmarkIteratorL();
    CleanupStack::PushL(iterLm);

    CPosLandmarkEncoder* encoder = CPosLandmarkEncoder::NewL(KPosMimeType);
    CleanupStack::PushL(encoder);
    TRAPD(err,encoder->SetOutputFileL(KFilePath));
    if(KErrAlreadyExists == err)
      {
      RFs fs;
      CleanupClosePushL(fs);
      User::LeaveIfError(fs.Connect());
      fs.Delete(KFilePath);
      encoder->SetOutputFileL(KFilePath);
      CleanupStack::PopAndDestroy();
      }

    RArray<TPosLmItemId> landmarks;
    CleanupClosePushL(landmarks);


    while ((lmId = iterLm->NextL()) != KPosLmNullItemId)
      {
      User::LeaveIfError(landmarks.Append(lmId));
      }

    ExecuteAndDeleteLD(db->ExportLandmarksL(*encoder,landmarks,CPosLandmarkDatabase::EIncludeCategories));
    ExecuteAndDeleteLD(encoder->FinalizeEncodingL());
    CleanupStack::PopAndDestroy(5,db);
    ReleaseLandmarkResources();

    inps->AppendL(TLiwGenericParam(KContentType,TLiwVariant(KLandmark)));

    CLiwMap* landmarkMap = CLiwDefaultMap::NewL();
    landmarkMap->InsertL(KSourceFile,TLiwVariant(KFilePath));
    landmarkMap->InsertL(KMimeType,TLiwVariant(KPosMimeType1));
    inps->AppendL(TLiwGenericParam(KDataFields,TLiwVariant(landmarkMap)));
    landmarkMap->DecRef();
    iIflandmarks->ExecuteCmdL(KImport,*inps,*outps,0,0);
    TInt index = 0;
    TInt32 err2 = -1;
    const TLiwGenericParam* outParam = outps->FindFirst(index,KErrorCode);
    //log data
    RFile LogResult;
    RFs LogResultSession;
    User::LeaveIfError(LogResultSession.Connect());
    if(LogResult.Open(LogResultSession ,_L("c:\\testlog1.txt") , EFileWrite | EFileShareAny )  == KErrNotFound)
        {
        TInt err1 = LogResult.Create(LogResultSession ,_L("c:\\testlog1.txt") , EFileWrite | EFileShareAny ) ;
        }
    TInt End = 0 ;
    LogResult.Seek(ESeekEnd , End) ; //Seek to end of the file before writing
    if( outParam )
      {
      outParam->Value().Get(err2);
      TBuf8<50> error;
      TRealFormat format;
      error.Num(err2,format) ;
      LogResult.Write(_L8("ImportLandmarkL Error="));
      LogResult.Write(error);
      LogResult.Write(_L8("\n"));
      index = 0;
      outParam = outps->FindFirst(index,KReturnValue);
      if( outParam )
        {
        CLiwIterable* iterable = outParam->Value().AsIterable();
        if( iterable )
            {
            TLiwVariant lmVariant;
            while( iterable->NextL(lmVariant) )
                {
                const CLiwMap* landmark = lmVariant.AsMap();
                TLiwVariant variantField;
                TPtrC landmarkName;
                if( landmark )
                    {
                    if( landmark->FindL(KLandmarkName,variantField) )
                        {
                        variantField.Get(landmarkName);
                        LogResult.Write(_L8("in iter"));
                        LogResult.Write(_L8("\n"));
                        }
                    }
                variantField.Reset();
                lmVariant.Reset();
                }
            }
        
        }
      }

    inps->Reset();
    outps->Reset();
    LogResult.Write(_L8("End of Import"));
    LogResult.Close();
    LogResultSession.Close();

 	CleanupStack::PopAndDestroy(2,ServiceHandler);
    ReleaseLandmarkResources();
    __UHEAP_MARKEND;
    return err2;
    }

// -----------------------------------------------------------------------------
// CTLandmarkProvider::ImportLandmarkPosL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CTLandmarkProvider::ImportLandmarkPosL( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( KTLandmarkProvider, "TLandmarkProvider" );
    _LIT( KExample, "In ImportLandmarkPosL" );
    TestModuleIf().Printf( 0, KTLandmarkProvider, KExample );
    // Print to log file
    iLog->Log( KExample );

	__UHEAP_MARK;
	CLiwServiceHandler* ServiceHandler;
	CLiwGenericParamList* inps,*outps;
	MLiwInterface* iIflandmarks;
	
	CreateInterfaceL(ServiceHandler,iIflandmarks);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*iIflandmarks);
	
    inps = &(ServiceHandler->InParamListL());
    outps = &(ServiceHandler->OutParamListL());

	inps->Reset();
	outps->Reset();
	
    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, KTLandmarkProvider,
                                KParam, i, &string );
        i++;
        }
    //preconditions
    _LIT(KFilePath, "c:\\eposLm.lmx");
    _LIT8(KPosMimeType, "application/vnd.nokia.landmarkcollection+xml");
    _LIT(KPosMimeType1, "application/vnd.nokia.landmarkcollection+xml");
    _LIT(KName1,"Mainland China");
    _LIT(KName2,"Chung Wah");
    _LIT(KName3,"Aromas of China");

    CPosLandmarkDatabase* db = CPosLandmarkDatabase::OpenL(KTestDbUri1);
    CleanupStack::PushL(db);
    ExecuteAndDeleteLD(db->InitializeL());
    RemoveAllLandmarks(db);

    TPosLmItemId lmId;
    CPosLandmark* lm = CPosLandmark::NewLC();
    lm->SetLandmarkNameL(KName1);
    db->AddLandmarkL(*lm);
    lm->SetLandmarkNameL(KName2);
    db->AddLandmarkL(*lm);
    lm->SetLandmarkNameL(KName3);
    db->AddLandmarkL(*lm);

    CPosLmItemIterator* iterLm = db->LandmarkIteratorL();
    CleanupStack::PushL(iterLm);

    CPosLandmarkEncoder* encoder = CPosLandmarkEncoder::NewL(KPosMimeType);
    CleanupStack::PushL(encoder);
    TRAPD(err,encoder->SetOutputFileL(KFilePath));
    if(KErrAlreadyExists == err)
      {
      RFs fs;
      CleanupClosePushL(fs);
      User::LeaveIfError(fs.Connect());
      fs.Delete(KFilePath);
      encoder->SetOutputFileL(KFilePath);
      CleanupStack::PopAndDestroy();
      }

    RArray<TPosLmItemId> landmarks;
    CleanupClosePushL(landmarks);


    while ((lmId = iterLm->NextL()) != KPosLmNullItemId)
      {
      User::LeaveIfError(landmarks.Append(lmId));
      }

    ExecuteAndDeleteLD(db->ExportLandmarksL(*encoder,landmarks,CPosLandmarkDatabase::EIncludeCategories));
    ExecuteAndDeleteLD(encoder->FinalizeEncodingL());
    CleanupStack::PopAndDestroy(5,db);
    ReleaseLandmarkResources();

    inps->AppendL(TLiwGenericParam(KNullDesC8,TLiwVariant(KLandmark)));

    CLiwMap* landmarkMap = CLiwDefaultMap::NewL();
    landmarkMap->InsertL(KSourceFile,TLiwVariant(KFilePath));
    landmarkMap->InsertL(KMimeType,TLiwVariant(KPosMimeType1));
    inps->AppendL(TLiwGenericParam(KNullDesC8,TLiwVariant(landmarkMap)));
    landmarkMap->DecRef();
    iIflandmarks->ExecuteCmdL(KImport,*inps,*outps,0,0);
    TInt index = 0;
    TInt32 err2 = -1;
    const TLiwGenericParam* outParam = outps->FindFirst(index,KErrorCode);
    //log data
    RFile LogResult;
    RFs LogResultSession;
    User::LeaveIfError(LogResultSession.Connect());
    if(LogResult.Open(LogResultSession ,_L("c:\\testlog1.txt") , EFileWrite | EFileShareAny )  == KErrNotFound)
        {
        TInt err1 = LogResult.Create(LogResultSession ,_L("c:\\testlog1.txt") , EFileWrite | EFileShareAny ) ;
        }
    TInt End = 0 ;
    LogResult.Seek(ESeekEnd , End) ; //Seek to end of the file before writing
    if( outParam )
      {
      outParam->Value().Get(err2);
      TBuf8<50> error;
      TRealFormat format;
      error.Num(err2,format) ;
      LogResult.Write(_L8("ImportLandmarkL Error="));
      LogResult.Write(error);
      LogResult.Write(_L8("\n"));
      index = 0;
      outParam = outps->FindFirst(index,KReturnValue);
      if( outParam )
        {
        CLiwIterable* iterable = outParam->Value().AsIterable();
        if( iterable )
            {
            TLiwVariant lmVariant;
            while( iterable->NextL(lmVariant) )
                {
                const CLiwMap* landmark = lmVariant.AsMap();
                TLiwVariant variantField;
                TPtrC landmarkName;
                if( landmark )
                    {
                    if( landmark->FindL(KLandmarkName,variantField) )
                        {
                        variantField.Get(landmarkName);
                        LogResult.Write(_L8("in iter"));
                        LogResult.Write(_L8("\n"));
                        }
                    }
                variantField.Reset();
                lmVariant.Reset();
                }
            }
        
        }
      }


    inps->Reset();
    outps->Reset();
    LogResult.Write(_L8("End of Import"));
    LogResult.Close();
    LogResultSession.Close();
  	
  	CleanupStack::PopAndDestroy(2,ServiceHandler);
    ReleaseLandmarkResources();
    
    __UHEAP_MARKEND;
    return err2;
    }
    
// -----------------------------------------------------------------------------
// CTLandmarkProvider::ExportLandmarkL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CTLandmarkProvider::ExportLandmarkL( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( KTLandmarkProvider, "TLandmarkProvider" );
    _LIT( KExample, "In Example" );
    TestModuleIf().Printf( 0, KTLandmarkProvider, KExample );
    // Print to log file
    iLog->Log( KExample );

	__UHEAP_MARK;
	CLiwServiceHandler* ServiceHandler;
	CLiwGenericParamList* inps,*outps;
	MLiwInterface* iIflandmarks;
	
	CreateInterfaceL(ServiceHandler,iIflandmarks);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*iIflandmarks);
	
    inps = &(ServiceHandler->InParamListL());
    outps = &(ServiceHandler->OutParamListL());

	inps->Reset();
	outps->Reset();
	
    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, KTLandmarkProvider,
                                KParam, i, &string );
        i++;
        }
    //preconditions
    _LIT(KFilePath, "c:\\eposLmTest.lmx");
  _LIT(KPosMimeType, "application/vnd.nokia.landmarkcollection+xml");
  _LIT(KName1,"Mainland China");
  _LIT(KName2,"Chung Wah");
  _LIT(KName3,"Aromas of China");

  CPosLandmarkDatabase* db = CPosLandmarkDatabase::OpenL(KTestDbUri1);
  CleanupStack::PushL(db);
  ExecuteAndDeleteLD(db->InitializeL());
  RemoveAllLandmarks(db);

  TPosLmItemId lmId;
  CPosLandmark* lm = CPosLandmark::NewLC();
  lm->SetLandmarkNameL(KName1);
  db->AddLandmarkL(*lm);
  lm->SetLandmarkNameL(KName2);
  db->AddLandmarkL(*lm);
  lm->SetLandmarkNameL(KName3);
  db->AddLandmarkL(*lm);

  CPosLmItemIterator* iterLm = db->LandmarkIteratorL();
  CleanupStack::PushL(iterLm);

    RFs fs;
    CleanupClosePushL(fs);
    User::LeaveIfError(fs.Connect());
    fs.Delete(KFilePath);
    CleanupStack::PopAndDestroy();


  CLiwList* landmarkIdList = CLiwDefaultList::NewL();
  
  RPointerArray<HBufC> lmIdArray;
  //CleanupClosePushL(lmIdArray);
  while ((lmId = iterLm->NextL()) != KPosLmNullItemId)
    {
    //User::LeaveIfError(landmarks.Append(lmId));
    HBufC* lmIdString = HBufC::NewLC(5);
    lmIdArray.AppendL(lmIdString);
    CleanupStack::Pop(lmIdString);
    lmIdString->Des().Num(lmId,EDecimal);
    landmarkIdList->AppendL(TLiwVariant(lmIdString));
    }

  CleanupStack::PopAndDestroy(3,db);
  ReleaseLandmarkResources();


    TLiwGenericParam param;
    param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
    inps->AppendL(param);
    param.Reset();

    CLiwMap* landmarkMap = CLiwDefaultMap::NewL();
    landmarkMap->InsertL(KDestinationFile,TLiwVariant(KFilePath));
    landmarkMap->InsertL(KMimeType,TLiwVariant(KPosMimeType));

    landmarkMap->InsertL(KIdList,TLiwVariant(landmarkIdList));
    landmarkIdList->DecRef();
    param.SetNameAndValueL(KDataFields,TLiwVariant(landmarkMap));
    inps->AppendL(param);
    landmarkMap->DecRef();
    param.Reset();

    iIflandmarks->ExecuteCmdL(KExport,*inps,*outps,0,0);
    lmIdArray.ResetAndDestroy();
    lmIdArray.Close();
    TInt index = 0;
    TInt32 err = -1;
    const TLiwGenericParam* outParam = outps->FindFirst(index,KErrorCode);
    //log data
    RFile LogResult;
    RFs LogResultSession;
    User::LeaveIfError(LogResultSession.Connect());
    if(LogResult.Open(LogResultSession ,_L("c:\\testlog1.txt") , EFileWrite | EFileShareAny )  == KErrNotFound)
        {
        TInt err1 = LogResult.Create(LogResultSession ,_L("c:\\testlog1.txt") , EFileWrite | EFileShareAny ) ;
        }
    TInt End = 0 ;
    LogResult.Seek(ESeekEnd , End) ; //Seek to end of the file before writing
    if( outParam )
      {
      outParam->Value().Get(err);
      TBuf8<50> error;
      TRealFormat format;
      error.Num(err,format) ;
      LogResult.Write(_L8("ExportLandmarkL Error="));
      LogResult.Write(error);
      LogResult.Write(_L8("\n"));
      }

    LogResult.Close();
    LogResultSession.Close();
    
  	CleanupStack::PopAndDestroy(2,ServiceHandler);
    ReleaseLandmarkResources();    
	__UHEAP_MARKEND;
    return err;

    }

// -----------------------------------------------------------------------------
// CTLandmarkProvider::ExportLandmarkPosL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CTLandmarkProvider::ExportLandmarkPosL( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( KTLandmarkProvider, "TLandmarkProvider" );
    _LIT( KExample, "In ExportLandmarkPosL" );
    TestModuleIf().Printf( 0, KTLandmarkProvider, KExample );
    // Print to log file
    iLog->Log( KExample );

	__UHEAP_MARK;
	CLiwServiceHandler* ServiceHandler;
	CLiwGenericParamList* inps,*outps;
	MLiwInterface* iIflandmarks;
	
	CreateInterfaceL(ServiceHandler,iIflandmarks);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*iIflandmarks);
	
    inps = &(ServiceHandler->InParamListL());
    outps = &(ServiceHandler->OutParamListL());

	inps->Reset();
	outps->Reset();
    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, KTLandmarkProvider,
                                KParam, i, &string );
        i++;
        }
    //preconditions
    _LIT(KFilePath, "c:\\eposLmTest.lmx");
  _LIT(KPosMimeType, "application/vnd.nokia.landmarkcollection+xml");
  _LIT(KName1,"Mainland China");
  _LIT(KName2,"Chung Wah");
  _LIT(KName3,"Aromas of China");

  CPosLandmarkDatabase* db = CPosLandmarkDatabase::OpenL(KTestDbUri1);
  CleanupStack::PushL(db);
  ExecuteAndDeleteLD(db->InitializeL());
  RemoveAllLandmarks(db);

  TPosLmItemId lmId;
  CPosLandmark* lm = CPosLandmark::NewLC();
  lm->SetLandmarkNameL(KName1);
  db->AddLandmarkL(*lm);
  lm->SetLandmarkNameL(KName2);
  db->AddLandmarkL(*lm);
  lm->SetLandmarkNameL(KName3);
  db->AddLandmarkL(*lm);

  CPosLmItemIterator* iterLm = db->LandmarkIteratorL();
  CleanupStack::PushL(iterLm);

    RFs fs;
    CleanupClosePushL(fs);
    User::LeaveIfError(fs.Connect());
    fs.Delete(KFilePath);
    CleanupStack::PopAndDestroy();


  CLiwList* landmarkIdList = CLiwDefaultList::NewL();
  RPointerArray<HBufC> lmIdArray;
  while ((lmId = iterLm->NextL()) != KPosLmNullItemId)
    {
    //User::LeaveIfError(landmarks.Append(lmId));
    HBufC* lmIdString = HBufC::NewLC(5);
    lmIdArray.AppendL(lmIdString);
    CleanupStack::Pop(lmIdString);
    lmIdString->Des().Num(lmId,EDecimal);
    landmarkIdList->AppendL(TLiwVariant(lmIdString));
    }

  CleanupStack::PopAndDestroy(3,db);
  ReleaseLandmarkResources();


    TLiwGenericParam param;
    param.SetNameAndValueL(KNullDesC8,TLiwVariant(KLandmark));
    inps->AppendL(param);
    param.Reset();

    CLiwMap* landmarkMap = CLiwDefaultMap::NewL();
    landmarkMap->InsertL(KDestinationFile,TLiwVariant(KFilePath));
    landmarkMap->InsertL(KMimeType,TLiwVariant(KPosMimeType));

    landmarkMap->InsertL(KIdList,TLiwVariant(landmarkIdList));
    landmarkIdList->DecRef();
    param.SetNameAndValueL(KNullDesC8,TLiwVariant(landmarkMap));
    inps->AppendL(param);
    landmarkMap->DecRef();
    param.Reset();

    iIflandmarks->ExecuteCmdL(KExport,*inps,*outps,0,0);
    lmIdArray.ResetAndDestroy();
    lmIdArray.Close();
    TInt index = 0;
    TInt32 err = -1;
    const TLiwGenericParam* outParam = outps->FindFirst(index,KErrorCode);
    //log data
    RFile LogResult;
    RFs LogResultSession;
    User::LeaveIfError(LogResultSession.Connect());
    if(LogResult.Open(LogResultSession ,_L("c:\\testlog1.txt") , EFileWrite | EFileShareAny )  == KErrNotFound)
        {
        TInt err1 = LogResult.Create(LogResultSession ,_L("c:\\testlog1.txt") , EFileWrite | EFileShareAny ) ;
        }
    TInt End = 0 ;
    LogResult.Seek(ESeekEnd , End) ; //Seek to end of the file before writing
    if( outParam )
      {
      outParam->Value().Get(err);
      TBuf8<50> error;
      TRealFormat format;
      error.Num(err,format) ;
      LogResult.Write(_L8("ExportLandmarkL Error="));
      LogResult.Write(error);
      LogResult.Write(_L8("\n"));
      }

    LogResult.Close();
    LogResultSession.Close();
    
  	CleanupStack::PopAndDestroy(2,ServiceHandler);
    ReleaseLandmarkResources();    
	__UHEAP_MARKEND;
    return err;

    }


// -----------------------------------------------------------------------------
// CTLandmarkProvider::LinkCategoryL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CTLandmarkProvider::LinkCategoryL( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( KTLandmarkProvider, "TLandmarkProvider" );
    _LIT( KExample, "In Example" );
    TestModuleIf().Printf( 0, KTLandmarkProvider, KExample );
    // Print to log file
    iLog->Log( KExample );

	__UHEAP_MARK;
	CLiwServiceHandler* ServiceHandler;
	CLiwGenericParamList* inps,*outps;
	MLiwInterface* iIflandmarks;
	
	CreateInterfaceL(ServiceHandler,iIflandmarks);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*iIflandmarks);
	
    inps = &(ServiceHandler->InParamListL());
    outps = &(ServiceHandler->OutParamListL());

	inps->Reset();
	outps->Reset();
	
    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, KTLandmarkProvider,
                                KParam, i, &string );
        i++;
        }
  /*Preconditions*/
  _LIT(KOffice1,"NokiaPrevious");
  _LIT(KName1,"Mainland China");
  _LIT(KName2,"Chung Wah");
  _LIT(KName3,"Aromas of China");

  CPosLandmarkDatabase* db = CPosLandmarkDatabase::OpenL(KTestDbUri1);
  CleanupStack::PushL(db);
  ExecuteAndDeleteLD(db->InitializeL());

  TPosLmItemId lmId;
  //RArray<TPosLmItemId> landmarks;
  //CleanupClosePushL(landmarks);

  CLiwList* landmarkIdList = CLiwDefaultList::NewL();

  CPosLandmark* lm = CPosLandmark::NewLC();
  lm->SetLandmarkNameL(KName1);
  lmId = db->AddLandmarkL(*lm);
  //User::LeaveIfError(landmarks.Append(lmId));
  TBuf<5> lmIdString1;
  lmIdString1.Num(lmId,EDecimal);
  landmarkIdList->AppendL(TLiwVariant(lmIdString1));
  lm->SetLandmarkNameL(KName2);
  lmId = db->AddLandmarkL(*lm);
  //User::LeaveIfError(landmarks.Append(lmId));
  TBuf<5> lmIdString2;
  lmIdString2.Num(lmId,EDecimal);
  landmarkIdList->AppendL(TLiwVariant(lmIdString2));
  lm->SetLandmarkNameL(KName3);
  lmId = db->AddLandmarkL(*lm);
  //User::LeaveIfError(landmarks.Append(lmId));
  TBuf<5> lmIdString3;
  lmIdString3.Num(lmId,EDecimal);
  landmarkIdList->AppendL(TLiwVariant(lmIdString3));

  CPosLmCategoryManager* catManager= CPosLmCategoryManager::NewL(*db);
  CleanupStack::PushL(catManager);
  RemoveAllCategories(catManager);

  TPosLmItemId catId;
  CPosLandmarkCategory* category = CPosLandmarkCategory::NewLC();
  category->SetCategoryNameL(KOffice1);
  catId = catManager->AddCategoryL(*category);
  TBuf<5> catIdString;
  catIdString.Num(catId,EDecimal);
  
  CleanupStack::PopAndDestroy(4,db);
  ReleaseLandmarkResources();

  TLiwGenericParam param;
  param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
  inps->AppendL(param);
  param.Reset();

  CLiwMap* map = CLiwDefaultMap::NewL();
  
  map->InsertL(KId,TLiwVariant(catIdString));
  map->InsertL(KIdList,TLiwVariant(landmarkIdList));
  landmarkIdList->DecRef();
  param.SetNameAndValueL(KDataFields,TLiwVariant(map));
  inps->AppendL(param);
  map->DecRef();
  param.Reset();

  param.SetNameAndValueL(KOperationType,TLiwVariant(KAssociate));
  inps->AppendL(param);
  param.Reset();

  iIflandmarks->ExecuteCmdL(KOrganise,*inps,*outps,0,0);
  TInt index = 0;
  TInt32 err = -1;
  const TLiwGenericParam* outParam = outps->FindFirst(index,KErrorCode);
  //log data
  RFile LogResult;
  RFs LogResultSession;
  User::LeaveIfError(LogResultSession.Connect());
  if(LogResult.Open(LogResultSession ,_L("c:\\testlog1.txt") , EFileWrite | EFileShareAny )  == KErrNotFound)
      {
      TInt err1 = LogResult.Create(LogResultSession ,_L("c:\\testlog1.txt") , EFileWrite | EFileShareAny ) ;
      }
  TInt End = 0 ;
  LogResult.Seek(ESeekEnd , End) ; //Seek to end of the file before writing
  if( outParam )
    {
    outParam->Value().Get(err);
    TBuf8<50> error;
    TRealFormat format;
    error.Num(err,format) ;
    LogResult.Write(_L8("LinkCategoryL Error="));
    LogResult.Write(error);
    LogResult.Write(_L8("\n"));
    }
  LogResult.Close();
  LogResultSession.Close();
  
  	CleanupStack::PopAndDestroy(2,ServiceHandler);
    ReleaseLandmarkResources();    
	__UHEAP_MARKEND;
	  
  return err;
  }

// -----------------------------------------------------------------------------
// CTLandmarkProvider::LinkCategoryPosL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CTLandmarkProvider::LinkCategoryPosL( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( KTLandmarkProvider, "TLandmarkProvider" );
    _LIT( KExample, "In LinkCategoryPosL" );
    TestModuleIf().Printf( 0, KTLandmarkProvider, KExample );
    // Print to log file
    iLog->Log( KExample );
	__UHEAP_MARK;
	CLiwServiceHandler* ServiceHandler;
	CLiwGenericParamList* inps,*outps;
	MLiwInterface* iIflandmarks;
	
	CreateInterfaceL(ServiceHandler,iIflandmarks);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*iIflandmarks);
	
    inps = &(ServiceHandler->InParamListL());
    outps = &(ServiceHandler->OutParamListL());

	inps->Reset();
	outps->Reset();
	
    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, KTLandmarkProvider,
                                KParam, i, &string );
        i++;
        }
  /*Preconditions*/
  _LIT(KOffice1,"NokiaPrevious");
  _LIT(KName1,"Mainland China");
  _LIT(KName2,"Chung Wah");
  _LIT(KName3,"Aromas of China");

  CPosLandmarkDatabase* db = CPosLandmarkDatabase::OpenL(KTestDbUri1);
  CleanupStack::PushL(db);
  ExecuteAndDeleteLD(db->InitializeL());

  TPosLmItemId lmId;
  //RArray<TPosLmItemId> landmarks;
  //CleanupClosePushL(landmarks);

  CLiwList* landmarkIdList = CLiwDefaultList::NewL();

  CPosLandmark* lm = CPosLandmark::NewLC();
  lm->SetLandmarkNameL(KName1);
  lmId = db->AddLandmarkL(*lm);
  //User::LeaveIfError(landmarks.Append(lmId));
  TBuf<5> lmIdString1;
  lmIdString1.Num(lmId,EDecimal);
  landmarkIdList->AppendL(TLiwVariant(lmIdString1));
  lm->SetLandmarkNameL(KName2);
  lmId = db->AddLandmarkL(*lm);
  //User::LeaveIfError(landmarks.Append(lmId));
  TBuf<5> lmIdString2;
  lmIdString2.Num(lmId,EDecimal);
  landmarkIdList->AppendL(TLiwVariant(lmIdString2));
  lm->SetLandmarkNameL(KName3);
  lmId = db->AddLandmarkL(*lm);
  //User::LeaveIfError(landmarks.Append(lmId));
  TBuf<5> lmIdString3;
  lmIdString3.Num(lmId,EDecimal);
  landmarkIdList->AppendL(TLiwVariant(lmIdString3));

  CPosLmCategoryManager* catManager= CPosLmCategoryManager::NewL(*db);
  CleanupStack::PushL(catManager);
  RemoveAllCategories(catManager);

  TPosLmItemId catId;
  CPosLandmarkCategory* category = CPosLandmarkCategory::NewLC();
  category->SetCategoryNameL(KOffice1);
  catId = catManager->AddCategoryL(*category);
  TBuf<5> catIdString;
  catIdString.Num(catId,EDecimal);
    
  CleanupStack::PopAndDestroy(4,db);
  ReleaseLandmarkResources();

  TLiwGenericParam param;
  param.SetNameAndValueL(KNullDesC8,TLiwVariant(KLandmark));
  inps->AppendL(param);
  param.Reset();

  CLiwMap* map = CLiwDefaultMap::NewL();
  map->InsertL(KId,TLiwVariant(catIdString));
  map->InsertL(KIdList,TLiwVariant(landmarkIdList));
  landmarkIdList->DecRef();
  param.SetNameAndValueL(KNullDesC8,TLiwVariant(map));
  inps->AppendL(param);
  map->DecRef();
  param.Reset();

  param.SetNameAndValueL(KNullDesC8,TLiwVariant(KAssociate));
  inps->AppendL(param);
  param.Reset();

  iIflandmarks->ExecuteCmdL(KOrganise,*inps,*outps,0,0);
  TInt index = 0;
  TInt32 err = -1;
  const TLiwGenericParam* outParam = outps->FindFirst(index,KErrorCode);
  //log data
  RFile LogResult;
  RFs LogResultSession;
  User::LeaveIfError(LogResultSession.Connect());
  if(LogResult.Open(LogResultSession ,_L("c:\\testlog1.txt") , EFileWrite | EFileShareAny )  == KErrNotFound)
      {
      TInt err1 = LogResult.Create(LogResultSession ,_L("c:\\testlog1.txt") , EFileWrite | EFileShareAny ) ;
      }
  TInt End = 0 ;
  LogResult.Seek(ESeekEnd , End) ; //Seek to end of the file before writing
  if( outParam )
    {
    outParam->Value().Get(err);
    TBuf8<50> error;
    TRealFormat format;
    error.Num(err,format) ;
    LogResult.Write(_L8("LinkCategoryL Error="));
    LogResult.Write(error);
    LogResult.Write(_L8("\n"));
    }
  LogResult.Close();
  LogResultSession.Close();
  
  	CleanupStack::PopAndDestroy(2,ServiceHandler);
    ReleaseLandmarkResources();    
	__UHEAP_MARKEND;  
  return err;
  }


// -----------------------------------------------------------------------------
// CTLandmarkProvider::UnLinkCategoryL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CTLandmarkProvider::UnLinkCategoryL( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( KTLandmarkProvider, "TLandmarkProvider" );
    _LIT( KExample, "In Example" );
    TestModuleIf().Printf( 0, KTLandmarkProvider, KExample );
    // Print to log file
    iLog->Log( KExample );
	__UHEAP_MARK;
	CLiwServiceHandler* ServiceHandler;
	CLiwGenericParamList* inps,*outps;
	MLiwInterface* iIflandmarks;
	
	CreateInterfaceL(ServiceHandler,iIflandmarks);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*iIflandmarks);
	
    inps = &(ServiceHandler->InParamListL());
    outps = &(ServiceHandler->OutParamListL());

	inps->Reset();
	outps->Reset();
	
    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, KTLandmarkProvider,
                                KParam, i, &string );
        i++;
        }
  /*Preconditions*/
  _LIT(KOffice1,"NokiaPrevious");
  _LIT(KName1,"Mainland China");
  _LIT(KName2,"Chung Wah");
  _LIT(KName3,"Aromas of China");

  CPosLandmarkDatabase* db = CPosLandmarkDatabase::OpenL(KTestDbUri1);
  CleanupStack::PushL(db);
  ExecuteAndDeleteLD(db->InitializeL());

  TPosLmItemId lmId;
  RArray<TPosLmItemId> landmarks;
  CleanupClosePushL(landmarks);
  CLiwList* landmarkIdList = CLiwDefaultList::NewL();

  CPosLandmark* lm = CPosLandmark::NewLC();
  lm->SetLandmarkNameL(KName1);
  lmId = db->AddLandmarkL(*lm);
  User::LeaveIfError(landmarks.Append(lmId));
  TBuf<5> lmIdString1;
  lmIdString1.Num(lmId,EDecimal);
  landmarkIdList->AppendL(TLiwVariant(lmIdString1));
  lm->SetLandmarkNameL(KName2);
  lmId = db->AddLandmarkL(*lm);
  User::LeaveIfError(landmarks.Append(lmId));
  TBuf<5> lmIdString2;
  lmIdString2.Num(lmId,EDecimal);
  landmarkIdList->AppendL(TLiwVariant(lmIdString2));
  lm->SetLandmarkNameL(KName3);
  lmId = db->AddLandmarkL(*lm);
  User::LeaveIfError(landmarks.Append(lmId));
  TBuf<5> lmIdString3;
  lmIdString3.Num(lmId,EDecimal);
  landmarkIdList->AppendL(TLiwVariant(lmIdString3));

  CPosLmCategoryManager* catManager= CPosLmCategoryManager::NewL(*db);
  CleanupStack::PushL(catManager);
  RemoveAllCategories(catManager);

  TPosLmItemId catId;
  CPosLandmarkCategory* category = CPosLandmarkCategory::NewLC();
  category->SetCategoryNameL(KOffice1);
  catId = catManager->AddCategoryL(*category);
  ExecuteAndDeleteLD(catManager->AddCategoryToLandmarksL(catId,landmarks));
  TBuf<5> catIdString;
  catIdString.Num(catId,EDecimal);
    
  CleanupStack::PopAndDestroy(5,db);
  ReleaseLandmarkResources();

  TLiwGenericParam param;
  param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
  inps->AppendL(param);
  param.Reset();

  CLiwMap* map = CLiwDefaultMap::NewL();
  map->InsertL(KId,TLiwVariant(catIdString));
  map->InsertL(KIdList,TLiwVariant(landmarkIdList));
  landmarkIdList->DecRef();
  param.SetNameAndValueL(KDataFields,TLiwVariant(map));
  inps->AppendL(param);
  map->DecRef();
  param.Reset();

  param.SetNameAndValueL(KOperationType,TLiwVariant(KDisassociate));
  inps->AppendL(param);
  param.Reset();

  iIflandmarks->ExecuteCmdL(KOrganise,*inps,*outps,0,0);
  TInt index = 0;
  TInt32 err = -1;
  const TLiwGenericParam* outParam = outps->FindFirst(index,KErrorCode);
  //log data
  RFile LogResult;
  RFs LogResultSession;
  User::LeaveIfError(LogResultSession.Connect());
  if(LogResult.Open(LogResultSession ,_L("c:\\testlog1.txt") , EFileWrite | EFileShareAny )  == KErrNotFound)
      {
      TInt err1 = LogResult.Create(LogResultSession ,_L("c:\\testlog1.txt") , EFileWrite | EFileShareAny ) ;
      }
  TInt End = 0 ;
  LogResult.Seek(ESeekEnd , End) ; //Seek to end of the file before writing
  if( outParam )
    {
    outParam->Value().Get(err);
    TBuf8<50> error;
    TRealFormat format;
    error.Num(err,format) ;
    LogResult.Write(_L8("UnLinkCategoryL Error="));
    LogResult.Write(error);
    LogResult.Write(_L8("\n"));
    }
  LogResult.Close();
  LogResultSession.Close();
  
  	CleanupStack::PopAndDestroy(2,ServiceHandler);
    ReleaseLandmarkResources();    
	__UHEAP_MARKEND;  
  return err;
  }

// -----------------------------------------------------------------------------
// CTLandmarkProvider::UnLinkCategoryPosL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CTLandmarkProvider::UnLinkCategoryPosL( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( KTLandmarkProvider, "TLandmarkProvider" );
    _LIT( KExample, "In UnLinkCategoryPosL" );
    TestModuleIf().Printf( 0, KTLandmarkProvider, KExample );
    // Print to log file
    iLog->Log( KExample );

	__UHEAP_MARK;
	CLiwServiceHandler* ServiceHandler;
	CLiwGenericParamList* inps,*outps;
	MLiwInterface* iIflandmarks;
	
	CreateInterfaceL(ServiceHandler,iIflandmarks);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*iIflandmarks);
	
    inps = &(ServiceHandler->InParamListL());
    outps = &(ServiceHandler->OutParamListL());

	inps->Reset();
	outps->Reset();
	
    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, KTLandmarkProvider,
                                KParam, i, &string );
        i++;
        }
  /*Preconditions*/
  _LIT(KOffice1,"NokiaPrevious");
  _LIT(KName1,"Mainland China");
  _LIT(KName2,"Chung Wah");
  _LIT(KName3,"Aromas of China");

  CPosLandmarkDatabase* db = CPosLandmarkDatabase::OpenL(KTestDbUri1);
  CleanupStack::PushL(db);
  ExecuteAndDeleteLD(db->InitializeL());

  TPosLmItemId lmId;
  RArray<TPosLmItemId> landmarks;
  CleanupClosePushL(landmarks);
  CLiwList* landmarkIdList = CLiwDefaultList::NewL();

  CPosLandmark* lm = CPosLandmark::NewLC();
  lm->SetLandmarkNameL(KName1);
  lmId = db->AddLandmarkL(*lm);
  User::LeaveIfError(landmarks.Append(lmId));
  TBuf<5> lmIdString1;
  lmIdString1.Num(lmId,EDecimal);
  landmarkIdList->AppendL(TLiwVariant(lmIdString1));
  lm->SetLandmarkNameL(KName2);
  lmId = db->AddLandmarkL(*lm);
  User::LeaveIfError(landmarks.Append(lmId));
  TBuf<5> lmIdString2;
  lmIdString2.Num(lmId,EDecimal);
  landmarkIdList->AppendL(TLiwVariant(lmIdString2));
  lm->SetLandmarkNameL(KName3);
  lmId = db->AddLandmarkL(*lm);
  User::LeaveIfError(landmarks.Append(lmId));
  TBuf<5> lmIdString3;
  lmIdString3.Num(lmId,EDecimal);
  landmarkIdList->AppendL(TLiwVariant(lmIdString3));

  CPosLmCategoryManager* catManager= CPosLmCategoryManager::NewL(*db);
  CleanupStack::PushL(catManager);
  RemoveAllCategories(catManager);

  TPosLmItemId catId;
  CPosLandmarkCategory* category = CPosLandmarkCategory::NewLC();
  category->SetCategoryNameL(KOffice1);
  catId = catManager->AddCategoryL(*category);
  ExecuteAndDeleteLD(catManager->AddCategoryToLandmarksL(catId,landmarks));
  TBuf<5> catIdString;
  catIdString.Num(catId,EDecimal);
  
  CleanupStack::PopAndDestroy(5,db);
  ReleaseLandmarkResources();

  TLiwGenericParam param;
  param.SetNameAndValueL(KNullDesC8,TLiwVariant(KLandmark));
  inps->AppendL(param);
  param.Reset();

  CLiwMap* map = CLiwDefaultMap::NewL();
  map->InsertL(KId,TLiwVariant(catIdString));
  map->InsertL(KIdList,TLiwVariant(landmarkIdList));
  landmarkIdList->DecRef();
  param.SetNameAndValueL(KNullDesC8,TLiwVariant(map));
  inps->AppendL(param);
  map->DecRef();
  param.Reset();

  param.SetNameAndValueL(KNullDesC8,TLiwVariant(KDisassociate));
  inps->AppendL(param);
  param.Reset();

  iIflandmarks->ExecuteCmdL(KOrganise,*inps,*outps,0,0);
  TInt index = 0;
  TInt32 err = -1;
  const TLiwGenericParam* outParam = outps->FindFirst(index,KErrorCode);
  //log data
  RFile LogResult;
  RFs LogResultSession;
  User::LeaveIfError(LogResultSession.Connect());
  if(LogResult.Open(LogResultSession ,_L("c:\\testlog1.txt") , EFileWrite | EFileShareAny )  == KErrNotFound)
      {
      TInt err1 = LogResult.Create(LogResultSession ,_L("c:\\testlog1.txt") , EFileWrite | EFileShareAny ) ;
      }
  TInt End = 0 ;
  LogResult.Seek(ESeekEnd , End) ; //Seek to end of the file before writing
  if( outParam )
    {
    outParam->Value().Get(err);
    TBuf8<50> error;
    TRealFormat format;
    error.Num(err,format) ;
    LogResult.Write(_L8("UnLinkCategoryL Error="));
    LogResult.Write(error);
    LogResult.Write(_L8("\n"));
    }
  LogResult.Close();
  LogResultSession.Close();
  
  	CleanupStack::PopAndDestroy(2,ServiceHandler);
    ReleaseLandmarkResources();    
	__UHEAP_MARKEND;  
  return err;
  }


// -----------------------------------------------------------------------------
// CTLandmarkProvider::LandmarksSyncTest1
// Helper method to remove all landmarks for preconditional tests.
// -----------------------------------------------------------------------------
//
struct landmark
	{
	TUint id;
	HBufC* name;
	HBufC* desc;
	TReal64 latitude;
	TReal64 longitude;
	TReal32 altitude;
	TReal32 haccuracy;
	TReal32 vaccuracy;
	TReal32 covrad;
	landmark* next;
	};
TInt CTLandmarkProvider::LandmarksGtkL ( CStifItemParser& /*aItem*/ )
	{
	_LIT( KExample, "LandmarksGtkL" );
	iLog->Log( KExample );
	
	TInt32 err;
	TInt ret = 0;
	
	CPosLandmarkDatabase* db = CPosLandmarkDatabase::OpenL(KTestDbUri1);
	CleanupStack::PushL(db);
	ExecuteAndDeleteLD(db->InitializeL());
	RemoveAllLandmarks(db);
	CreateLandmarksL(db);
	CleanupStack::PopAndDestroy(db);
	
	CLiwGenericParamList* inps = &(iServiceHandler->InParamListL());
	CLiwGenericParamList* outps = &(iServiceHandler->OutParamListL());
	
	TLiwGenericParam param;
	param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
	inps->AppendL(param);
	param.Reset();
	
	iIflandmarks->ExecuteCmdL(KGetList,*inps,*outps,0,0);
	ret |= CheckErrorCode (*outps,err);
	if ( err != KErrNone )
	{
	iLog->Log( _L(" Getlist on database failed wiht err...") );
	ret |= FAIL;
	}
	
	landmark* new_node = NULL;
	landmark* cur_node = NULL;
	landmark* lm_head = NULL;
	const TInt NAME_MAX = 255;
	TInt Index = 0;
	const TLiwGenericParam* itr = outps->FindFirst(Index,KReturnValue);
	if ( Index > 0 || (0 == Index) )
		{
		iLog->Log( _L("Database iterator found in output ArgList") );
		CLiwIterable* iter = itr->Value().AsIterable();
		if( iter )
			{
			TLiwVariant lmVariant;
			while( iter->NextL(lmVariant) )
				{
				TRAPD(err,new_node = (landmark*) User::AllocL(sizeof(landmark)));
				User::LeaveIfError(err);    
	    		new_node->next = lm_head;
	    		lm_head = new_node;
	    		
				const CLiwMap* landmark = lmVariant.AsMap();
				TLiwVariant variantField;
				TPtrC landmarkName;
				TPtrC landmarkDesc;
				if( landmark )
					{
					if( landmark->FindL(KLandmarkName,variantField) )
						{
						variantField.Get(landmarkName);
						new_node->name = HBufC::NewL(NAME_MAX);
						(new_node->name->Des()).Copy(landmarkName);						
						}
					if( landmark->FindL(KLandmarkDesc,variantField) )
						{
						variantField.Get(landmarkDesc);
						/*new_node->desc = HBufC::NewL(NAME_MAX);
						(new_node->desc->Des()).Copy(landmarkDesc);	*/
						}
					if( landmark->FindL(KLandmarkPosition,variantField) )
						{
						const CLiwMap* landmarkPos = variantField.AsMap();
						TLiwVariant variantPos;
						TReal coord;
						if( landmarkPos->FindL(KLatitude,variantPos) )
						{
						variantPos.Get(coord);
						new_node->latitude = coord;
						}
						if( landmarkPos->FindL(KLongitude,variantPos) )
						{
						variantPos.Get(coord);
						new_node->longitude = coord;
						}
						variantPos.Reset();
						}
					
					}
				variantField.Reset();
				lmVariant.Reset();
				}
			}		
		}
	outps->Reset();
	cur_node = lm_head;
	while(cur_node)
		{
		lm_head = cur_node->next;
		User::Free(cur_node->name);
		User::Free(cur_node->desc);
		User::Free(cur_node);
		cur_node = lm_head;
		}
	return KErrNone;
	}
// -----------------------------------------------------------------------------
// CTLandmarkProvider::LandmarksSyncTest1
// Helper method to remove all landmarks for preconditional tests.
// -----------------------------------------------------------------------------
//
TInt CTLandmarkProvider::LandmarksSyncTest1L ( CStifItemParser& /*aItem*/ )
  {
  _LIT( KExample, "LandmarksSyncTest1" );
  iLog->Log( KExample );

  TInt32 err;
  TInt ret = 0;

	__UHEAP_MARK;
	CLiwServiceHandler* ServiceHandler;
	CLiwGenericParamList* inps,*outps;
	MLiwInterface* iIflandmarks;
	
	CreateInterfaceL(ServiceHandler,iIflandmarks);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*iIflandmarks);
	
    inps = &(ServiceHandler->InParamListL());
    outps = &(ServiceHandler->OutParamListL());

	inps->Reset();
	outps->Reset();
	
	
  CPosLandmarkDatabase* db = CPosLandmarkDatabase::OpenL(KTestDbUri1);
  CleanupStack::PushL(db);
  ExecuteAndDeleteLD(db->InitializeL());
  RemoveAllLandmarks(db);
  CreateLandmarksL(db);
  CleanupStack::PopAndDestroy(db);

  TLiwGenericParam param;
  param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
  inps->AppendL(param);
  param.Reset();

  CLiwMap* landmarkMap = CLiwDefaultMap::NewL();
  landmarkMap->InsertL(KLandmarkName,TLiwVariant(KLmSearchString));
  landmarkMap->InsertL(KMaximumMatches,TLiwVariant((TInt32)2));
  param.SetNameAndValueL(KFilter,TLiwVariant(landmarkMap));
  inps->AppendL(param);
  param.Reset();
  landmarkMap->DecRef();

  iIflandmarks->ExecuteCmdL(KGetList,*inps,*outps,0,0);
  ret |= CheckErrorCode (*outps,err);
  if ( err != KErrNone )
    {
    iLog->Log( _L(" Getlist on database failed wiht err...") );
    ret |= FAIL;
    }

  TInt Index = 0;
  const TLiwGenericParam* itr = outps->FindFirst(Index,KReturnValue);
  if ( Index > 0 || (0 == Index) )
    {
    iLog->Log( _L("Database iterator found in output ArgList") );
    CLiwIterable* iter = itr->Value().AsIterable();
    if( iter )
        {
        TLiwVariant lmVariant;
        while( iter->NextL(lmVariant) )
            {
            const CLiwMap* landmark = lmVariant.AsMap();
            TLiwVariant variantField;
            TPtrC landmarkName;
            if( landmark )
                {
                if( landmark->FindL(KLandmarkName,variantField) )
                    {
                     variantField.Get(landmarkName);
                    }
				if( landmark->FindL(KLandmarkPosition,variantField) )
                    {
                    const CLiwMap* landmarkPos = variantField.AsMap();
            		TLiwVariant variantPos;
            		TReal coord;
            		if( landmarkPos->FindL(KLatitude,variantPos) )
                    {
                     variantPos.Get(coord);
                    }
                    if( landmarkPos->FindL(KLongitude,variantPos) )
                    {
                     variantPos.Get(coord);
                    }
                    variantPos.Reset();
                    }
                }
            variantField.Reset();
            lmVariant.Reset();
            }
        }
    
    }
  //test prev match
  inps->Reset();
  outps->Reset();
  inps->AppendL(TLiwGenericParam(KContentType,TLiwVariant(KLandmark)));
  param.Reset();
    //try for previous matches
  landmarkMap = CLiwDefaultMap::NewL();
  landmarkMap->InsertL(KLandmarkName,TLiwVariant(KLmSearchString1));
  landmarkMap->InsertL(KPrevMatchesOnly,TLiwVariant((TBool)ETrue));
  param.SetNameAndValueL(KFilter,TLiwVariant(landmarkMap));
  inps->AppendL(param);
  landmarkMap->DecRef();
  param.Reset();

  iIflandmarks->ExecuteCmdL(KGetList,*inps,*outps,0,0);
  ret |= CheckErrorCode (*outps,err);
  if ( err != KErrNone )
    {
    iLog->Log( _L(" Getlist on database failed wiht err...") );
    ret |= FAIL;
    }

  Index = 0;
  itr = outps->FindFirst(Index,KReturnValue);
  if ( Index > 0 || (0 == Index) )
    {
    iLog->Log( _L("Database iterator found in output ArgList") );
    CLiwIterable* iter = itr->Value().AsIterable();
    if( iter )
        {
        TLiwVariant lmVariant;
        while( iter->NextL(lmVariant) )
            {
            const CLiwMap* landmark = lmVariant.AsMap();
            TLiwVariant variantField;
            TPtrC landmarkName;
            if( landmark )
                {
                if( landmark->FindL(KLandmarkName,variantField) )
                    {
                     variantField.Get(landmarkName);
                    }

                }
            variantField.Reset();
            lmVariant.Reset();
            }
        }
    
    }
    
  //test landmark desc
  _LIT(KLmDesSearchString,"welc*");
  inps->Reset();
  outps->Reset();
  inps->AppendL(TLiwGenericParam(KContentType,TLiwVariant(KLandmark)));
  param.Reset();    
  landmarkMap = CLiwDefaultMap::NewL();
  landmarkMap->InsertL(KLandmarkDesc,TLiwVariant(KLmDesSearchString));
  param.SetNameAndValueL(KFilter,TLiwVariant(landmarkMap));
  inps->AppendL(param);
  landmarkMap->DecRef();
  param.Reset();

  iIflandmarks->ExecuteCmdL(KGetList,*inps,*outps,0,0);
  ret |= CheckErrorCode (*outps,err);
  if ( err != KErrNone )
    {
    iLog->Log( _L(" Getlist on database failed wiht err...") );
    ret |= FAIL;
    }

  Index = 0;
  itr = outps->FindFirst(Index,KReturnValue);
  if ( Index > 0 || (0 == Index) )
    {
    iLog->Log( _L("Database iterator found in output ArgList") );
    CLiwIterable* iter = itr->Value().AsIterable();
    if( iter )
        {
        TLiwVariant lmVariant;
        while( iter->NextL(lmVariant) )
            {
            const CLiwMap* landmark = lmVariant.AsMap();
            TLiwVariant variantField;
            TPtrC landmarkName;
            if( landmark )
                {
                if( landmark->FindL(KLandmarkName,variantField) )
                    {
                     variantField.Get(landmarkName);
                    }

                }
            variantField.Reset();
            lmVariant.Reset();
            }
        }
    
    }
    
  //test nearest
  inps->Reset();
  outps->Reset();
  inps->AppendL(TLiwGenericParam(KContentType,TLiwVariant(KLandmark)));
  param.Reset();    
  landmarkMap = CLiwDefaultMap::NewL();
  CLiwDefaultMap* positionMap = CLiwDefaultMap::NewL();
  positionMap->InsertL(KLatitude,TLiwVariant((TReal)12.0));
  positionMap->InsertL(KLongitude,TLiwVariant((TReal)67.0));
  positionMap->InsertL(KCoverageRadiusOption,TLiwVariant(EFalse));
  positionMap->InsertL(KMaximumDistance,TLiwVariant((TReal)30.0));
  landmarkMap->InsertL(KLandmarkPosition,TLiwVariant(positionMap));
  positionMap->DecRef();
  param.SetNameAndValueL(KFilter,TLiwVariant(landmarkMap));
  inps->AppendL(param);
  landmarkMap->DecRef();
  param.Reset();

  iIflandmarks->ExecuteCmdL(KGetList,*inps,*outps,0,0);
  ret |= CheckErrorCode (*outps,err);
  if ( err != KErrNone )
    {
    iLog->Log( _L(" Getlist on database failed wiht err...") );
    ret |= FAIL;
    }

  Index = 0;
  itr = outps->FindFirst(Index,KReturnValue);
  if ( Index > 0 || (0 == Index) )
    {
    iLog->Log( _L("Database iterator found in output ArgList") );
    CLiwIterable* iter = itr->Value().AsIterable();
    if( iter )
        {
        TLiwVariant lmVariant;
        while( iter->NextL(lmVariant) )
            {
            const CLiwMap* landmark = lmVariant.AsMap();
            TLiwVariant variantField;
            TPtrC landmarkName;
            if( landmark )
                {
                if( landmark->FindL(KLandmarkName,variantField) )
                    {
                     variantField.Get(landmarkName);
                    }				
                }
            variantField.Reset();
            lmVariant.Reset();
            }
        }
    
    }
  
  //area criteria
  inps->Reset();
  outps->Reset();
  inps->AppendL(TLiwGenericParam(KContentType,TLiwVariant(KLandmark)));
  param.Reset();    
  landmarkMap = CLiwDefaultMap::NewL();
  CLiwDefaultMap* areaMap = CLiwDefaultMap::NewL();
  areaMap->InsertL(KSouthLatitude,TLiwVariant((TReal)10.0));
  areaMap->InsertL(KNorthLatitude,TLiwVariant((TReal)15.0));
  areaMap->InsertL(KWestLongitude,TLiwVariant((TReal)60.0));
  areaMap->InsertL(KEastLongitude,TLiwVariant((TReal)70.0));
  landmarkMap->InsertL(KBoundedArea,TLiwVariant(areaMap));
  areaMap->DecRef();
  param.SetNameAndValueL(KFilter,TLiwVariant(landmarkMap));
  inps->AppendL(param);
  landmarkMap->DecRef();
  param.Reset();

  iIflandmarks->ExecuteCmdL(KGetList,*inps,*outps,0,0);
  ret |= CheckErrorCode (*outps,err);
  if ( err != KErrNone )
    {
    iLog->Log( _L(" Getlist on database failed wiht err...") );
    ret |= FAIL;
    }

  Index = 0;
  itr = outps->FindFirst(Index,KReturnValue);
  if ( Index > 0 || (0 == Index) )
    {
    iLog->Log( _L("Database iterator found in output ArgList") );
    CLiwIterable* iter = itr->Value().AsIterable();
    if( iter )
        {
        TLiwVariant lmVariant;
        while( iter->NextL(lmVariant) )
            {
            const CLiwMap* landmark = lmVariant.AsMap();
            TLiwVariant variantField;
            TPtrC landmarkName;
            if( landmark )
                {
                if( landmark->FindL(KLandmarkName,variantField) )
                    {
                     variantField.Get(landmarkName);
                    }

                }
            variantField.Reset();
            lmVariant.Reset();
            }
        }
    
    }
   inps->Reset();
    outps->Reset();

  	CleanupStack::PopAndDestroy(2,ServiceHandler);
    ReleaseLandmarkResources();    
	__UHEAP_MARKEND; 

  return err;
  }

// -----------------------------------------------------------------------------
// CTLandmarkProvider::LandmarksSyncTest1
// Helper method to remove all landmarks for preconditional tests.
// -----------------------------------------------------------------------------
//
TInt CTLandmarkProvider::LandmarksSyncTestPos1L ( CStifItemParser& /*aItem*/ )
  {
  _LIT( KExample, "LandmarksSyncTestPos1L" );
  iLog->Log( KExample );

  TInt32 err;
  TInt ret = 0;

	__UHEAP_MARK;
	CLiwServiceHandler* ServiceHandler;
	CLiwGenericParamList* inps,*outps;
	MLiwInterface* iIflandmarks;
	
	CreateInterfaceL(ServiceHandler,iIflandmarks);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*iIflandmarks);
	
    inps = &(ServiceHandler->InParamListL());
    outps = &(ServiceHandler->OutParamListL());

	inps->Reset();
	outps->Reset();

  CPosLandmarkDatabase* db = CPosLandmarkDatabase::OpenL(KTestDbUri1);
  CleanupStack::PushL(db);
  ExecuteAndDeleteLD(db->InitializeL());
  RemoveAllLandmarks(db);
  CreateLandmarksL(db);
  CleanupStack::PopAndDestroy(db);

  TLiwGenericParam param;
  param.SetNameAndValueL(KNullDesC8,TLiwVariant(KLandmark));
  inps->AppendL(param);
  param.Reset();

  CLiwMap* landmarkMap = CLiwDefaultMap::NewL();
  landmarkMap->InsertL(KLandmarkName,TLiwVariant(KLmSearchString));
  landmarkMap->InsertL(KMaximumMatches,TLiwVariant((TInt32)2));
  param.SetNameAndValueL(KNullDesC8,TLiwVariant(landmarkMap));
  inps->AppendL(param);
  param.Reset();
  landmarkMap->DecRef();

  iIflandmarks->ExecuteCmdL(KGetList,*inps,*outps,0,0);
  ret |= CheckErrorCode (*outps,err);
  if ( err != KErrNone )
    {
    iLog->Log( _L(" Getlist on database failed wiht err...") );
    ret |= FAIL;
    }

  TInt Index = 0;
  const TLiwGenericParam* itr = outps->FindFirst(Index,KReturnValue);
  if ( Index > 0 || (0 == Index) )
    {
    iLog->Log( _L("Database iterator found in output ArgList") );
    CLiwIterable* iter = itr->Value().AsIterable();
    if( iter )
        {
        TLiwVariant lmVariant;
        while( iter->NextL(lmVariant) )
            {
            const CLiwMap* landmark = lmVariant.AsMap();
            TLiwVariant variantField;
            TPtrC landmarkName;
            if( landmark )
                {
                if( landmark->FindL(KLandmarkName,variantField) )
                    {
                     variantField.Get(landmarkName);
                    }
				if( landmark->FindL(KLandmarkPosition,variantField) )
                    {
                    const CLiwMap* landmarkPos = variantField.AsMap();
            		TLiwVariant variantPos;
            		TReal coord;
            		if( landmarkPos->FindL(KLatitude,variantPos) )
                    {
                     variantPos.Get(coord);
                    }
                    if( landmarkPos->FindL(KLongitude,variantPos) )
                    {
                     variantPos.Get(coord);
                    }
                    variantPos.Reset();
                    }
                }
            variantField.Reset();
            lmVariant.Reset();
            }
        }
    
    } 
 
  inps->Reset();
  outps->Reset();
  	
  	CleanupStack::PopAndDestroy(2,ServiceHandler);
    ReleaseLandmarkResources();    
	__UHEAP_MARKEND; 
  return err;
  }

// -----------------------------------------------------------------------------
// CTLandmarkProvider::LandmarksAsyncTest1
// Helper method to remove all landmarks for preconditional tests.
// -----------------------------------------------------------------------------
//
TInt CTLandmarkProvider::LandmarksAsyncTest1L  ( CStifItemParser& /*aItem*/ )
  {
  _LIT( KExample, "LandmarksAsyncTest1" );
  iLog->Log( KExample );

  TInt32 err;
  TInt ret = 0;

	__UHEAP_MARK;
	CLiwServiceHandler* ServiceHandler;
	CLiwGenericParamList* inps,*outps;
	MLiwInterface* iIflandmarks;
	
	CreateInterfaceL(ServiceHandler,iIflandmarks);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*iIflandmarks);
	
    inps = &(ServiceHandler->InParamListL());
    outps = &(ServiceHandler->OutParamListL());

	inps->Reset();
	outps->Reset();
	
  CPosLandmarkDatabase* db = CPosLandmarkDatabase::OpenL(KTestDbUri1);
  CleanupStack::PushL(db);
  ExecuteAndDeleteLD(db->InitializeL());
  RemoveAllLandmarks(db);
  CreateLandmarksL(db);
  CleanupStack::PopAndDestroy(db);

  TLiwGenericParam param;
  param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
  inps->AppendL(param);
  param.Reset();

  CLiwMap* landmarkMap = CLiwDefaultMap::NewL();
  landmarkMap->InsertL(KLandmarkName,TLiwVariant(KLmSearchString));
  param.SetNameAndValueL(KFilter,TLiwVariant(landmarkMap));
  inps->AppendL(param);
  landmarkMap->DecRef();
  param.Reset();

  iIflandmarks->ExecuteCmdL(KGetList,*inps,*outps,KLiwOptASyncronous,this);
  ret |= CheckErrorCode (*outps,err);
  if ( err != KErrNone )
    {
    iLog->Log( _L(" Getlist on database failed wiht err...") );
    ret |= FAIL;
    }

  if ( !ret )
    CActiveScheduler::Start();

  landmarkMap->Remove(KLandmarkName);
  landmarkMap->InsertL(KLandmarkName,TLiwVariant(KLmSearchString1));
  landmarkMap->InsertL(KMaximumMatches,TLiwVariant((TInt32)2));
  landmarkMap->InsertL(KPrevMatchesOnly,TLiwVariant((TBool)ETrue));
  param.SetNameAndValueL(KFilter,TLiwVariant(landmarkMap));
  inps->AppendL(param);
  landmarkMap->DecRef();
  param.Reset();

  iIflandmarks->ExecuteCmdL(KGetList,*inps,*outps,KLiwOptASyncronous,this);
  ret |= CheckErrorCode (*outps,err);
  if ( err != KErrNone )
    {
    iLog->Log( _L(" Getlist on database failed wiht err...") );
    ret |= FAIL;
    }

  if ( !ret )
    CActiveScheduler::Start();
  	
  	CleanupStack::PopAndDestroy(2,ServiceHandler);
    ReleaseLandmarkResources();    
	__UHEAP_MARKEND;   

  return ret;
  }
  
// -----------------------------------------------------------------------------
// CTLandmarkProvider::LandmarksAsyncTest1
// Helper method to remove all landmarks for preconditional tests.
// -----------------------------------------------------------------------------
//
TInt CTLandmarkProvider::LandmarksAsyncTestPos1L  ( CStifItemParser& /*aItem*/ )
  {
  _LIT( KExample, "LandmarksAsyncTestPos1L" );
  iLog->Log( KExample );

  TInt32 err;
  TInt ret = 0;

	__UHEAP_MARK;
	CLiwServiceHandler* ServiceHandler;
	CLiwGenericParamList* inps,*outps;
	MLiwInterface* iIflandmarks;
	
	CreateInterfaceL(ServiceHandler,iIflandmarks);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*iIflandmarks);
	
    inps = &(ServiceHandler->InParamListL());
    outps = &(ServiceHandler->OutParamListL());

	inps->Reset();
	outps->Reset();
	
  CPosLandmarkDatabase* db = CPosLandmarkDatabase::OpenL(KTestDbUri1);
  CleanupStack::PushL(db);
  ExecuteAndDeleteLD(db->InitializeL());
  RemoveAllLandmarks(db);
  CreateLandmarksL(db);
  CleanupStack::PopAndDestroy(db);

  TLiwGenericParam param;
  param.SetNameAndValueL(KNullDesC8,TLiwVariant(KLandmark));
  inps->AppendL(param);
  param.Reset();

  CLiwMap* landmarkMap = CLiwDefaultMap::NewL();
  landmarkMap->InsertL(KLandmarkName,TLiwVariant(KLmSearchString));
  param.SetNameAndValueL(KNullDesC8,TLiwVariant(landmarkMap));
  inps->AppendL(param);
  param.Reset();

  iIflandmarks->ExecuteCmdL(KGetList,*inps,*outps,KLiwOptASyncronous,this);
  ret |= CheckErrorCode (*outps,err);
  if ( err != KErrNone )
    {
    iLog->Log( _L(" Getlist on database failed wiht err...") );
    ret |= FAIL;
    }

  if ( !ret )
    CActiveScheduler::Start();
  
  inps->Reset();
  outps->Reset();

  param.SetNameAndValueL(KNullDesC8,TLiwVariant(KLandmark));
  inps->AppendL(param);
  param.Reset();

  landmarkMap->Remove(KLandmarkName);
  landmarkMap->InsertL(KLandmarkName,TLiwVariant(KLmSearchString1));
  landmarkMap->InsertL(KMaximumMatches,TLiwVariant((TInt32)2));
  landmarkMap->InsertL(KPrevMatchesOnly,TLiwVariant((TBool)ETrue));

  param.SetNameAndValueL(KFilter,TLiwVariant(landmarkMap));
  inps->AppendL(param);
  landmarkMap->DecRef();  
  param.Reset();

  iIflandmarks->ExecuteCmdL(KGetList,*inps,*outps,KLiwOptASyncronous,this);
  ret |= CheckErrorCode (*outps,err);
  if ( err != KErrNone )
    {
    iLog->Log( _L(" Getlist on database failed wiht err...") );
    ret |= FAIL;
    }

  if ( !ret )
    CActiveScheduler::Start();
  
   	CleanupStack::PopAndDestroy(2,ServiceHandler);
    ReleaseLandmarkResources();    
	__UHEAP_MARKEND;  
  return ret;
  }  
 
// -----------------------------------------------------------------------------
// CTLandmarkProvider::AddLandmarkL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CTLandmarkProvider::AddLandmarkDbL( CStifItemParser& aItem )
    {
    // Print to UI
    _LIT( KTLandmarkProvider, "TLandmarkProvider" );
    _LIT( KExample, "In AddLandmarkL" );
    TestModuleIf().Printf( 0, KTLandmarkProvider, KExample );
    // Print to log file
    iLog->Log( KExample );

	__UHEAP_MARK;
	CLiwServiceHandler* ServiceHandler;
	CLiwGenericParamList* inps,*outps;
	MLiwInterface* iIflandmarks;
	
	CreateInterfaceL(ServiceHandler,iIflandmarks);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*iIflandmarks);
	
    inps = &(ServiceHandler->InParamListL());
    outps = &(ServiceHandler->OutParamListL());

	inps->Reset();
	outps->Reset();
    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, KTLandmarkProvider,
                                KParam, i, &string );
        i++;
        }

    TLiwGenericParam param;
    param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
    inps->AppendL(param);
    param.Reset();

    _LIT(KName,"Mainland China");
    _LIT(KDescription,"Extremely good chinese food");
    _LIT(KPhone1,"123456");
    TReal64 latitude = 45.1122;
    TReal64 longitude = 34.0099;
    CLiwMap* landmarkMap = CLiwDefaultMap::NewL();
    //db
    landmarkMap->InsertL(KDbUri,TLiwVariant(KTestDbUri));
    landmarkMap->InsertL(KLandmarkName,TLiwVariant(KName));
    CLiwMap* position = CLiwDefaultMap::NewL();
    position->InsertL(KLatitude,TLiwVariant(latitude));
    position->InsertL(KLongitude,TLiwVariant(longitude));
    landmarkMap->InsertL(KLandmarkPosition,TLiwVariant(position));
    landmarkMap->InsertL(KLandmarkDesc,TLiwVariant(KDescription));
    CLiwMap* landmarkFields = CLiwDefaultMap::NewL();
    landmarkFields->InsertL(KLandmarkTelephone,TLiwVariant(KPhone1));
    landmarkMap->InsertL(KLandmarkFields,TLiwVariant(landmarkFields));
    param.SetNameAndValueL(KDataFields,TLiwVariant(landmarkMap));
    inps->AppendL(param);
    param.Reset();
    landmarkFields->DecRef();
    position->DecRef();
    landmarkMap->DecRef();

    iIflandmarks->ExecuteCmdL(KAdd,*inps,*outps,0,0);
    TInt index = 0;
    TInt32 err = -1;
    const TLiwGenericParam* outParam = outps->FindFirst(index,KErrorCode);
    //log data
    RFile LogResult;
    RFs LogResultSession;
    User::LeaveIfError(LogResultSession.Connect());
    if(LogResult.Open(LogResultSession ,_L("c:\\testlog1.txt") , EFileWrite | EFileShareAny )  == KErrNotFound)
        {
        TInt err1 = LogResult.Create(LogResultSession ,_L("c:\\testlog1.txt") , EFileWrite | EFileShareAny ) ;
        }
    TInt End = 0 ;
    LogResult.Seek(ESeekEnd , End) ; //Seek to end of the file before writing
    if( outParam )
      {
      outParam->Value().Get(err);
      TBuf8<50> error;
      TRealFormat format;
      error.Num(err,format) ;
      LogResult.Write(_L8("AddLandmarkL Error="));
      LogResult.Write(error);
      LogResult.Write(_L8("\n"));
      }
    LogResult.Close();
    LogResultSession.Close();
    position->DecRef();
    landmarkMap->DecRef();

   	CleanupStack::PopAndDestroy(2,ServiceHandler);
    ReleaseLandmarkResources();    
	__UHEAP_MARKEND;  
    return err;

    }

// -----------------------------------------------------------------------------
// CTLandmarkProvider::UpdateLandmarkL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CTLandmarkProvider::UpdateLandmarkDbL( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( KTLandmarkProvider, "TLandmarkProvider" );
    _LIT( KExample, "In Example" );
    TestModuleIf().Printf( 0, KTLandmarkProvider, KExample );
    // Print to log file
    iLog->Log( KExample );

	__UHEAP_MARK;
	CLiwServiceHandler* ServiceHandler;
	CLiwGenericParamList* inps,*outps;
	MLiwInterface* iIflandmarks;
	
	CreateInterfaceL(ServiceHandler,iIflandmarks);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*iIflandmarks);
	
    inps = &(ServiceHandler->InParamListL());
    outps = &(ServiceHandler->OutParamListL());

	inps->Reset();
	outps->Reset();
	
    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, KTLandmarkProvider,
                                KParam, i, &string );
        i++;
        }
  /*Preconditions*/
  _LIT(KName,"3QC");
  _LIT(KName1,"Mainland China");

  CPosLandmarkDatabase* db = CPosLandmarkDatabase::OpenL(KTestDbUri);
  CleanupStack::PushL(db);
  ExecuteAndDeleteLD(db->InitializeL());
  RemoveAllLandmarks(db);

  TPosLmItemId lmId;
  CPosLandmark* lm = CPosLandmark::NewLC();
  lm->SetLandmarkNameL(KName1);
  lmId = db->AddLandmarkL(*lm);

  lm = db->ReadLandmarkLC(lmId);


  TLiwGenericParam param;
  param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
  inps->AppendL(param);
  param.Reset();

  CLiwMap* landmarkMap = CLiwDefaultMap::NewL();
  //db
  landmarkMap->InsertL(KDbUri,TLiwVariant(KTestDbUri));
  TBuf<5> lmIdString1;
  lmIdString1.Num(lm->LandmarkId(),EDecimal);
  landmarkMap->InsertL(KId,TLiwVariant(lmIdString1));
  landmarkMap->InsertL(KLandmarkName,TLiwVariant(KName));
  param.SetNameAndValueL(KDataFields,TLiwVariant(landmarkMap));
  inps->AppendL(param);
  landmarkMap->DecRef();
  param.Reset();

  iIflandmarks->ExecuteCmdL(KAdd,*inps,*outps,0,0);
  TInt index = 0;
  TInt32 err = -1;
  const TLiwGenericParam* outParam = outps->FindFirst(index,KErrorCode);
  //log data
  RFile LogResult;
  RFs LogResultSession;
  User::LeaveIfError(LogResultSession.Connect());
  if(LogResult.Open(LogResultSession ,_L("c:\\testlog1.txt") , EFileWrite | EFileShareAny )  == KErrNotFound)
      {
      TInt err1 = LogResult.Create(LogResultSession ,_L("c:\\testlog1.txt") , EFileWrite | EFileShareAny ) ;
      }
  TInt End = 0 ;
  LogResult.Seek(ESeekEnd , End) ; //Seek to end of the file before writing
  if( outParam )
    {
    outParam->Value().Get(err);
    TBuf8<50> error;
    TRealFormat format;
    error.Num(err,format) ;
    LogResult.Write(_L8("UpdateLandmarkL Error="));
    LogResult.Write(error);
    LogResult.Write(_L8("\n"));
    }
  LogResult.Close();
  LogResultSession.Close();
  

  CleanupStack::PopAndDestroy(lm);

  CleanupStack::PopAndDestroy(2,db);

   	CleanupStack::PopAndDestroy(2,ServiceHandler);
    ReleaseLandmarkResources();    
	__UHEAP_MARKEND;  
  return err;
  }

// -----------------------------------------------------------------------------
// CTLandmarkProvider::RemoveLandmarkL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CTLandmarkProvider::RemoveLandmarkDbL( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( KTLandmarkProvider, "TLandmarkProvider" );
    _LIT( KExample, "In Example" );
    TestModuleIf().Printf( 0, KTLandmarkProvider, KExample );
    // Print to log file
    iLog->Log( KExample );

	__UHEAP_MARK;
	CLiwServiceHandler* ServiceHandler;
	CLiwGenericParamList* inps,*outps;
	MLiwInterface* iIflandmarks;
	
	CreateInterfaceL(ServiceHandler,iIflandmarks);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*iIflandmarks);
	
    inps = &(ServiceHandler->InParamListL());
    outps = &(ServiceHandler->OutParamListL());

	inps->Reset();
	outps->Reset();
	
    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, KTLandmarkProvider,
                                KParam, i, &string );
        i++;
        }
    //preconditions
    _LIT(KName1,"Mainland China");
    CPosLandmarkDatabase* db = CPosLandmarkDatabase::OpenL(KTestDbUri);
    CleanupStack::PushL(db);
    ExecuteAndDeleteLD(db->InitializeL());
    RemoveAllLandmarks(db);

    CPosLandmark* lm = CPosLandmark::NewLC();
    lm->SetLandmarkNameL(KName1);
    db->AddLandmarkL(*lm);

    TLiwGenericParam param;
    param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
    inps->AppendL(param);
    param.Reset();

    CLiwMap* landmarkMap = CLiwDefaultMap::NewL();
    landmarkMap->InsertL(KDbUri,TLiwVariant(KTestDbUri));
    TBuf<5> lmIdString1;
    lmIdString1.Num(lm->LandmarkId(),EDecimal);
    landmarkMap->InsertL(KId,TLiwVariant(lmIdString1));
    param.SetNameAndValueL(KDataFields,TLiwVariant(landmarkMap));
    inps->AppendL(param);
    landmarkMap->DecRef();
    param.Reset();

    iIflandmarks->ExecuteCmdL(KRemove,*inps,*outps,0,0);
    TInt index = 0;
    TInt32 err = -1;
    const TLiwGenericParam* outParam = outps->FindFirst(index,KErrorCode);
    //log data
    RFile LogResult;
    RFs LogResultSession;
    User::LeaveIfError(LogResultSession.Connect());
    if(LogResult.Open(LogResultSession ,_L("c:\\testlog1.txt") , EFileWrite | EFileShareAny )  == KErrNotFound)
        {
        TInt err1 = LogResult.Create(LogResultSession ,_L("c:\\testlog1.txt") , EFileWrite | EFileShareAny ) ;
        }
    TInt End = 0 ;
    LogResult.Seek(ESeekEnd , End) ; //Seek to end of the file before writing
    if( outParam )
      {
      outParam->Value().Get(err);
      TBuf8<50> error;
      TRealFormat format;
      error.Num(err,format) ;
      LogResult.Write(_L8("RemoveLandmarkL Error="));
      LogResult.Write(error);
      LogResult.Write(_L8("\n"));
      }
    LogResult.Close();
    LogResultSession.Close();
    


    CleanupStack::PopAndDestroy(2,db);
   	
   	CleanupStack::PopAndDestroy(2,ServiceHandler);
    ReleaseLandmarkResources();    
	__UHEAP_MARKEND;  
	
    return err;

    }

// -----------------------------------------------------------------------------
// CTLandmarkProvider::ImportLandmarkL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CTLandmarkProvider::ImportLandmarkDbL( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( KTLandmarkProvider, "TLandmarkProvider" );
    _LIT( KExample, "In Example" );
    TestModuleIf().Printf( 0, KTLandmarkProvider, KExample );
    // Print to log file
    iLog->Log( KExample );

	__UHEAP_MARK;
	CLiwServiceHandler* ServiceHandler;
	CLiwGenericParamList* inps,*outps;
	MLiwInterface* iIflandmarks;
	
	CreateInterfaceL(ServiceHandler,iIflandmarks);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*iIflandmarks);
	
    inps = &(ServiceHandler->InParamListL());
    outps = &(ServiceHandler->OutParamListL());

	inps->Reset();
	outps->Reset();
	
    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, KTLandmarkProvider,
                                KParam, i, &string );
        i++;
        }
    //preconditions
    _LIT(KFilePath, "c:\\eposLm.lmx");
    _LIT8(KPosMimeType, "application/vnd.nokia.landmarkcollection+xml");
    _LIT(KPosMimeType1, "application/vnd.nokia.landmarkcollection+xml");
    _LIT(KName1,"Mainland China");
    _LIT(KName2,"Chung Wah");
    _LIT(KName3,"Aromas of China");

    CPosLandmarkDatabase* db = CPosLandmarkDatabase::OpenL(KTestDbUri);
    CleanupStack::PushL(db);
    ExecuteAndDeleteLD(db->InitializeL());
    RemoveAllLandmarks(db);

    TPosLmItemId lmId;
    CPosLandmark* lm = CPosLandmark::NewLC();
    lm->SetLandmarkNameL(KName1);
    db->AddLandmarkL(*lm);
    lm->SetLandmarkNameL(KName2);
    db->AddLandmarkL(*lm);
    lm->SetLandmarkNameL(KName3);
    db->AddLandmarkL(*lm);

    CPosLmItemIterator* iterLm = db->LandmarkIteratorL();
    CleanupStack::PushL(iterLm);

    CPosLandmarkEncoder* encoder = CPosLandmarkEncoder::NewL(KPosMimeType);
    CleanupStack::PushL(encoder);
    TRAPD(err,encoder->SetOutputFileL(KFilePath));
    if(KErrAlreadyExists == err)
      {
      RFs fs;
      CleanupClosePushL(fs);
      User::LeaveIfError(fs.Connect());
      fs.Delete(KFilePath);
      encoder->SetOutputFileL(KFilePath);
      CleanupStack::PopAndDestroy();
      }

    RArray<TPosLmItemId> landmarks;
    CleanupClosePushL(landmarks);


    while ((lmId = iterLm->NextL()) != KPosLmNullItemId)
      {
      User::LeaveIfError(landmarks.Append(lmId));
      }

    ExecuteAndDeleteLD(db->ExportLandmarksL(*encoder,landmarks,CPosLandmarkDatabase::EIncludeCategories));
    ExecuteAndDeleteLD(encoder->FinalizeEncodingL());
    CleanupStack::PopAndDestroy(3,iterLm);


    TLiwGenericParam param;
    param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
    inps->AppendL(param);
    param.Reset();

    CLiwMap* landmarkMap = CLiwDefaultMap::NewL();
    landmarkMap->InsertL(KDbUri,TLiwVariant(KTestDbUri));
    landmarkMap->InsertL(KSourceFile,TLiwVariant(KFilePath));
    landmarkMap->InsertL(KMimeType,TLiwVariant(KPosMimeType1));
    param.SetNameAndValueL(KDataFields,TLiwVariant(landmarkMap));
    inps->AppendL(param);
    landmarkMap->DecRef();
    param.Reset();

    iIflandmarks->ExecuteCmdL(KImport,*inps,*outps,0,0);
    TInt index = 0;
    TInt32 err2 = -1;
    const TLiwGenericParam* outParam = outps->FindFirst(index,KErrorCode);
    //log data
    RFile LogResult;
    RFs LogResultSession;
    User::LeaveIfError(LogResultSession.Connect());
    if(LogResult.Open(LogResultSession ,_L("c:\\testlog1.txt") , EFileWrite | EFileShareAny )  == KErrNotFound)
        {
        TInt err1 = LogResult.Create(LogResultSession ,_L("c:\\testlog1.txt") , EFileWrite | EFileShareAny ) ;
        }
    TInt End = 0 ;
    LogResult.Seek(ESeekEnd , End) ; //Seek to end of the file before writing
    if( outParam )
      {
      outParam->Value().Get(err2);
      TBuf8<50> error;
      TRealFormat format;
      error.Num(err2,format) ;
      LogResult.Write(_L8("ImportLandmarkL Error="));
      LogResult.Write(error);
      LogResult.Write(_L8("\n"));
      index = 0;
      outParam = outps->FindFirst(index,KReturnValue);
      if( outParam )
        {
        CLiwIterable* iterable = outParam->Value().AsIterable();
        if( iterable )
            {
            TLiwVariant lmVariant;
            while( iterable->NextL(lmVariant) )
                {
                const CLiwMap* landmark = lmVariant.AsMap();
                TLiwVariant variantField;
                TPtrC landmarkName;
                if( landmark )
                    {
                    if( landmark->FindL(KLandmarkName,variantField) )
                        {
                        variantField.Get(landmarkName);
                        }
                    }
                variantField.Reset();
                lmVariant.Reset();
                }
            }
        
        }
      }
    LogResult.Close();
    LogResultSession.Close();
    CleanupStack::PopAndDestroy(2,db);
    ReleaseLandmarkResources();
    inps->Reset();
    outps->Reset();

   	CleanupStack::PopAndDestroy(2,ServiceHandler);
    ReleaseLandmarkResources();    
	__UHEAP_MARKEND;  
    return err2;

    }

// -----------------------------------------------------------------------------
// CTLandmarkProvider::ExportLandmarkL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CTLandmarkProvider::ExportLandmarkDbL( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( KTLandmarkProvider, "TLandmarkProvider" );
    _LIT( KExample, "In Example" );
    TestModuleIf().Printf( 0, KTLandmarkProvider, KExample );
    // Print to log file
    iLog->Log( KExample );

	__UHEAP_MARK;
	CLiwServiceHandler* ServiceHandler;
	CLiwGenericParamList* inps,*outps;
	MLiwInterface* iIflandmarks;
	
	CreateInterfaceL(ServiceHandler,iIflandmarks);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*iIflandmarks);
	
    inps = &(ServiceHandler->InParamListL());
    outps = &(ServiceHandler->OutParamListL());

	inps->Reset();
	outps->Reset();
	
    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, KTLandmarkProvider,
                                KParam, i, &string );
        i++;
        }
    //preconditions
    _LIT(KFilePath, "c:\\eposLmTest.lmx");
  _LIT(KPosMimeType, "application/vnd.nokia.landmarkcollection+xml");
  _LIT(KName1,"Mainland China");
  _LIT(KName2,"Chung Wah");
  _LIT(KName3,"Aromas of China");

  CPosLandmarkDatabase* db = CPosLandmarkDatabase::OpenL(KTestDbUri);
  CleanupStack::PushL(db);
  ExecuteAndDeleteLD(db->InitializeL());
  RemoveAllLandmarks(db);

  TPosLmItemId lmId;
  CPosLandmark* lm = CPosLandmark::NewLC();
  lm->SetLandmarkNameL(KName1);
  db->AddLandmarkL(*lm);
  lm->SetLandmarkNameL(KName2);
  db->AddLandmarkL(*lm);
  lm->SetLandmarkNameL(KName3);
  db->AddLandmarkL(*lm);

  CPosLmItemIterator* iterLm = db->LandmarkIteratorL();
  CleanupStack::PushL(iterLm);

    RFs fs;
    CleanupClosePushL(fs);
    User::LeaveIfError(fs.Connect());
    fs.Delete(KFilePath);
    CleanupStack::PopAndDestroy();


  CLiwList* landmarkIdList = CLiwDefaultList::NewL();
  RPointerArray<HBufC> lmIdArray;
  while ((lmId = iterLm->NextL()) != KPosLmNullItemId)
    {
    //User::LeaveIfError(landmarks.Append(lmId));
    HBufC* lmIdString = HBufC::NewLC(5);
    lmIdArray.AppendL(lmIdString);
    CleanupStack::Pop(lmIdString);
    lmIdString->Des().Num(lmId,EDecimal);
    landmarkIdList->AppendL(TLiwVariant(lmIdString));
    }

  CleanupStack::PopAndDestroy(3,db);
  ReleaseLandmarkResources();



    TLiwGenericParam param;
    param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
    inps->AppendL(param);
    param.Reset();

    CLiwMap* landmarkMap = CLiwDefaultMap::NewL();
    landmarkMap->InsertL(KDbUri,TLiwVariant(KTestDbUri));
    landmarkMap->InsertL(KDestinationFile,TLiwVariant(KFilePath));
    landmarkMap->InsertL(KMimeType,TLiwVariant(KPosMimeType));

    landmarkMap->InsertL(KIdList,TLiwVariant(landmarkIdList));
    landmarkIdList->DecRef();
    param.SetNameAndValueL(KDataFields,TLiwVariant(landmarkMap));
    inps->AppendL(param);
    landmarkMap->DecRef();
    param.Reset();

    iIflandmarks->ExecuteCmdL(KExport,*inps,*outps,0,0);
    lmIdArray.ResetAndDestroy();
    lmIdArray.Close();
    TInt index = 0;
    TInt32 err = -1;
    const TLiwGenericParam* outParam = outps->FindFirst(index,KErrorCode);
    //log data
    RFile LogResult;
    RFs LogResultSession;
    User::LeaveIfError(LogResultSession.Connect());
    if(LogResult.Open(LogResultSession ,_L("c:\\testlog1.txt") , EFileWrite | EFileShareAny )  == KErrNotFound)
        {
        TInt err1 = LogResult.Create(LogResultSession ,_L("c:\\testlog1.txt") , EFileWrite | EFileShareAny ) ;
        }
    TInt End = 0 ;
    LogResult.Seek(ESeekEnd , End) ; //Seek to end of the file before writing
    if( outParam )
      {
      outParam->Value().Get(err);
      TBuf8<50> error;
      TRealFormat format;
      error.Num(err,format) ;
      LogResult.Write(_L8("ExportLandmarkL Error="));
      LogResult.Write(error);
      LogResult.Write(_L8("\n"));
      }

    LogResult.Close();
    LogResultSession.Close();
    
   	CleanupStack::PopAndDestroy(2,ServiceHandler);
    ReleaseLandmarkResources();    
	__UHEAP_MARKEND;      

    return err;

    }

// -----------------------------------------------------------------------------
// CTLandmarkProvider::LinkCategoryL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CTLandmarkProvider::LinkCategoryDbL( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( KTLandmarkProvider, "TLandmarkProvider" );
    _LIT( KExample, "In Example" );
    TestModuleIf().Printf( 0, KTLandmarkProvider, KExample );
    // Print to log file
    iLog->Log( KExample );

	__UHEAP_MARK;
	CLiwServiceHandler* ServiceHandler;
	CLiwGenericParamList* inps,*outps;
	MLiwInterface* iIflandmarks;
	
	CreateInterfaceL(ServiceHandler,iIflandmarks);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*iIflandmarks);
	
    inps = &(ServiceHandler->InParamListL());
    outps = &(ServiceHandler->OutParamListL());

	inps->Reset();
	outps->Reset();
    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, KTLandmarkProvider,
                                KParam, i, &string );
        i++;
        }
  /*Preconditions*/
  _LIT(KOffice1,"NokiaPrevious");
  _LIT(KName1,"Mainland China");
  _LIT(KName2,"Chung Wah");
  _LIT(KName3,"Aromas of China");

  CPosLandmarkDatabase* db = CPosLandmarkDatabase::OpenL(KTestDbUri);
  CleanupStack::PushL(db);
  ExecuteAndDeleteLD(db->InitializeL());

  TPosLmItemId lmId;
  //RArray<TPosLmItemId> landmarks;
  //CleanupClosePushL(landmarks);

  CLiwList* landmarkIdList = CLiwDefaultList::NewL();

  CPosLandmark* lm = CPosLandmark::NewLC();
  lm->SetLandmarkNameL(KName1);
  lmId = db->AddLandmarkL(*lm);
  //User::LeaveIfError(landmarks.Append(lmId));
  TBuf<5> lmIdString1;
  lmIdString1.Num(lmId,EDecimal);
  landmarkIdList->AppendL(TLiwVariant(lmIdString1));
  lm->SetLandmarkNameL(KName2);
  lmId = db->AddLandmarkL(*lm);
  //User::LeaveIfError(landmarks.Append(lmId));
  TBuf<5> lmIdString2;
  lmIdString2.Num(lmId,EDecimal);
  landmarkIdList->AppendL(TLiwVariant(lmIdString2));
  lm->SetLandmarkNameL(KName3);
  lmId = db->AddLandmarkL(*lm);
  //User::LeaveIfError(landmarks.Append(lmId));
  TBuf<5> lmIdString3;
  lmIdString3.Num(lmId,EDecimal);
  landmarkIdList->AppendL(TLiwVariant(lmIdString3));

  CPosLmCategoryManager* catManager= CPosLmCategoryManager::NewL(*db);
  CleanupStack::PushL(catManager);
  RemoveAllCategories(catManager);

  TPosLmItemId catId;
  CPosLandmarkCategory* category = CPosLandmarkCategory::NewLC();
  category->SetCategoryNameL(KOffice1);
  catId = catManager->AddCategoryL(*category);
  TBuf<5> catIdString;
  catIdString.Num(catId,EDecimal);
  CleanupStack::PopAndDestroy(4,db);
  ReleaseLandmarkResources();


  TLiwGenericParam param;
  param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
  inps->AppendL(param);
  param.Reset();

  CLiwMap* map = CLiwDefaultMap::NewL();
  map->InsertL(KDbUri,TLiwVariant(KTestDbUri));
  map->InsertL(KId,TLiwVariant(catIdString));
  map->InsertL(KIdList,TLiwVariant(landmarkIdList));
  landmarkIdList->DecRef();
  param.SetNameAndValueL(KDataFields,TLiwVariant(map));
  inps->AppendL(param);
  map->DecRef();
  param.Reset();

  param.SetNameAndValueL(KOperationType,TLiwVariant(KAssociate));
  inps->AppendL(param);
  param.Reset();

  iIflandmarks->ExecuteCmdL(KOrganise,*inps,*outps,0,0);
  TInt index = 0;
  TInt32 err = -1;
  const TLiwGenericParam* outParam = outps->FindFirst(index,KErrorCode);
  //log data
  RFile LogResult;
  RFs LogResultSession;
  User::LeaveIfError(LogResultSession.Connect());
  if(LogResult.Open(LogResultSession ,_L("c:\\testlog1.txt") , EFileWrite | EFileShareAny )  == KErrNotFound)
      {
      TInt err1 = LogResult.Create(LogResultSession ,_L("c:\\testlog1.txt") , EFileWrite | EFileShareAny ) ;
      }
  TInt End = 0 ;
  LogResult.Seek(ESeekEnd , End) ; //Seek to end of the file before writing
  if( outParam )
    {
    outParam->Value().Get(err);
    TBuf8<50> error;
    TRealFormat format;
    error.Num(err,format) ;
    LogResult.Write(_L8("LinkCategoryL Error="));
    LogResult.Write(error);
    LogResult.Write(_L8("\n"));
    }
  LogResult.Close();
  LogResultSession.Close();
  
   	CleanupStack::PopAndDestroy(2,ServiceHandler);
    ReleaseLandmarkResources();    
	__UHEAP_MARKEND;  
	  
  return err;
  }

// -----------------------------------------------------------------------------
// CTLandmarkProvider::UnLinkCategoryL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CTLandmarkProvider::UnLinkCategoryDbL( CStifItemParser& aItem )
    {

    // Print to UI
    _LIT( KTLandmarkProvider, "TLandmarkProvider" );
    _LIT( KExample, "In Example" );
    TestModuleIf().Printf( 0, KTLandmarkProvider, KExample );
    // Print to log file
    iLog->Log( KExample );

	__UHEAP_MARK;
	CLiwServiceHandler* ServiceHandler;
	CLiwGenericParamList* inps,*outps;
	MLiwInterface* iIflandmarks;
	
	CreateInterfaceL(ServiceHandler,iIflandmarks);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*iIflandmarks);
	
    inps = &(ServiceHandler->InParamListL());
    outps = &(ServiceHandler->OutParamListL());

	inps->Reset();
	outps->Reset();
	
    TInt i = 0;
    TPtrC string;
    _LIT( KParam, "Param[%i]: %S" );
    while ( aItem.GetNextString ( string ) == KErrNone )
        {
        TestModuleIf().Printf( i, KTLandmarkProvider,
                                KParam, i, &string );
        i++;
        }
  /*Preconditions*/
  _LIT(KOffice1,"NokiaPrevious");
  _LIT(KName1,"Mainland China");
  _LIT(KName2,"Chung Wah");
  _LIT(KName3,"Aromas of China");

  CPosLandmarkDatabase* db = CPosLandmarkDatabase::OpenL(KTestDbUri);
  CleanupStack::PushL(db);
  ExecuteAndDeleteLD(db->InitializeL());

  TPosLmItemId lmId;
  RArray<TPosLmItemId> landmarks;
  CleanupClosePushL(landmarks);
  CLiwList* landmarkIdList = CLiwDefaultList::NewL();

  CPosLandmark* lm = CPosLandmark::NewLC();
  lm->SetLandmarkNameL(KName1);
  lmId = db->AddLandmarkL(*lm);
  User::LeaveIfError(landmarks.Append(lmId));
  TBuf<5> lmIdString1;
  lmIdString1.Num(lmId,EDecimal);
  landmarkIdList->AppendL(TLiwVariant(lmIdString1));
  lm->SetLandmarkNameL(KName2);
  lmId = db->AddLandmarkL(*lm);
  User::LeaveIfError(landmarks.Append(lmId));
  TBuf<5> lmIdString2;
  lmIdString2.Num(lmId,EDecimal);
  landmarkIdList->AppendL(TLiwVariant(lmIdString2));
  lm->SetLandmarkNameL(KName3);
  lmId = db->AddLandmarkL(*lm);
  User::LeaveIfError(landmarks.Append(lmId));
  TBuf<5> lmIdString3;
  lmIdString3.Num(lmId,EDecimal);
  landmarkIdList->AppendL(TLiwVariant(lmIdString3));
  CPosLmCategoryManager* catManager= CPosLmCategoryManager::NewL(*db);
  CleanupStack::PushL(catManager);
  RemoveAllCategories(catManager);

  TPosLmItemId catId;
  CPosLandmarkCategory* category = CPosLandmarkCategory::NewLC();
  category->SetCategoryNameL(KOffice1);
  catId = catManager->AddCategoryL(*category);
  ExecuteAndDeleteLD(catManager->AddCategoryToLandmarksL(catId,landmarks));
  TBuf<5> catIdString;
  catIdString.Num(catId,EDecimal);
  
  CleanupStack::PopAndDestroy(5,db);
  ReleaseLandmarkResources();


  TLiwGenericParam param;
  param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
  inps->AppendL(param);
  param.Reset();

  CLiwMap* map = CLiwDefaultMap::NewL();
  map->InsertL(KDbUri,TLiwVariant(KTestDbUri));
  map->InsertL(KId,TLiwVariant(catIdString));
  map->InsertL(KIdList,TLiwVariant(landmarkIdList));
  landmarkIdList->DecRef();
  param.SetNameAndValueL(KDataFields,TLiwVariant(map));
  inps->AppendL(param);
  map->DecRef();
  param.Reset();

  param.SetNameAndValueL(KOperationType,TLiwVariant(KDisassociate));
  inps->AppendL(param);
  param.Reset();

  iIflandmarks->ExecuteCmdL(KOrganise,*inps,*outps,0,0);
  TInt index = 0;
  TInt32 err = -1;
  const TLiwGenericParam* outParam = outps->FindFirst(index,KErrorCode);
  //log data
  RFile LogResult;
  RFs LogResultSession;
  User::LeaveIfError(LogResultSession.Connect());
  if(LogResult.Open(LogResultSession ,_L("c:\\testlog1.txt") , EFileWrite | EFileShareAny )  == KErrNotFound)
      {
      TInt err1 = LogResult.Create(LogResultSession ,_L("c:\\testlog1.txt") , EFileWrite | EFileShareAny ) ;
      }
  TInt End = 0 ;
  LogResult.Seek(ESeekEnd , End) ; //Seek to end of the file before writing
  if( outParam )
    {
    outParam->Value().Get(err);
    TBuf8<50> error;
    TRealFormat format;
    error.Num(err,format) ;
    LogResult.Write(_L8("UnLinkCategoryL Error="));
    LogResult.Write(error);
    LogResult.Write(_L8("\n"));
    }
  LogResult.Close();
  LogResultSession.Close();
  
   	CleanupStack::PopAndDestroy(2,ServiceHandler);
    ReleaseLandmarkResources();    
	__UHEAP_MARKEND;    
  return err;
  }

// -----------------------------------------------------------------------------
// CTLandmarkProvider::LandmarksSyncTest1
// Helper method to remove all landmarks for preconditional tests.
// -----------------------------------------------------------------------------
//
TInt CTLandmarkProvider::LandmarksSyncTest1DbL ( CStifItemParser& /*aItem*/ )
  {
  _LIT( KExample, "LandmarksSyncTest1" );
  iLog->Log( KExample );

	__UHEAP_MARK;
	CLiwServiceHandler* ServiceHandler;
	CLiwGenericParamList* inps,*outps;
	MLiwInterface* iIflandmarks;
	
	CreateInterfaceL(ServiceHandler,iIflandmarks);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*iIflandmarks);
	
    inps = &(ServiceHandler->InParamListL());
    outps = &(ServiceHandler->OutParamListL());

	inps->Reset();
	outps->Reset();
	
  TInt32 err;
  TInt ret = 0;

  CPosLandmarkDatabase* db = CPosLandmarkDatabase::OpenL(KTestDbUri);
  CleanupStack::PushL(db);
  ExecuteAndDeleteLD(db->InitializeL());
  RemoveAllLandmarks(db);
  CreateLandmarksL(db);
  CleanupStack::PopAndDestroy(db);


  TLiwGenericParam param;
  param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
  inps->AppendL(param);
  param.Reset();

  CLiwMap* landmarkMap = CLiwDefaultMap::NewL();
  landmarkMap->InsertL(KDbUri,TLiwVariant(KTestDbUri));
  landmarkMap->InsertL(KLandmarkName,TLiwVariant(KLmSearchString));
  param.SetNameAndValueL(KFilter,TLiwVariant(landmarkMap));
  inps->AppendL(param);
  landmarkMap->DecRef();
  param.Reset();

  iIflandmarks->ExecuteCmdL(KGetList,*inps,*outps,0,0);
  ret |= CheckErrorCode (*outps,err);
  if ( err != KErrNone )
    {
    iLog->Log( _L(" Getlist on database failed wiht err...") );
    ret |= FAIL;
    }

  TInt Index = 0;
  const TLiwGenericParam* itr = outps->FindFirst(Index,KReturnValue);
  if ( Index > 0 || (0 == Index) )
    {
    iLog->Log( _L("Database iterator found in output ArgList") );
    CLiwIterable* iter = itr->Value().AsIterable();
    if( iter )
        {
        TLiwVariant lmVariant;
        while( iter->NextL(lmVariant) )
            {
            const CLiwMap* landmark = lmVariant.AsMap();
            TLiwVariant variantField;
            TPtrC landmarkName;
            if( landmark )
                {
                if( landmark->FindL(KLandmarkName,variantField) )
                    {
                     variantField.Get(landmarkName);
                    }

                }
            variantField.Reset();
            lmVariant.Reset();
            }
        }
    
    }
  inps->Reset();
    outps->Reset();

   	CleanupStack::PopAndDestroy(2,ServiceHandler);
    ReleaseLandmarkResources();    
	__UHEAP_MARKEND;  
  return err;
  }

// -----------------------------------------------------------------------------
// CTLandmarkProvider::LandmarksAsyncTest1
// Helper method to remove all landmarks for preconditional tests.
// -----------------------------------------------------------------------------
//
TInt CTLandmarkProvider::LandmarksAsyncTest1DbL  ( CStifItemParser& /*aItem*/ )
  {
  _LIT( KExample, "LandmarksAsyncTest1" );
  iLog->Log( KExample );

  TInt32 err;
  TInt ret = 0;

	__UHEAP_MARK;
	CLiwServiceHandler* ServiceHandler;
	CLiwGenericParamList* inps,*outps;
	MLiwInterface* iIflandmarks;
	
	CreateInterfaceL(ServiceHandler,iIflandmarks);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*iIflandmarks);
	
    inps = &(ServiceHandler->InParamListL());
    outps = &(ServiceHandler->OutParamListL());

	inps->Reset();
	outps->Reset();
	
  CPosLandmarkDatabase* db = CPosLandmarkDatabase::OpenL(KTestDbUri);
  CleanupStack::PushL(db);
  ExecuteAndDeleteLD(db->InitializeL());
  RemoveAllLandmarks(db);
  CreateLandmarksL(db);
  CleanupStack::PopAndDestroy(db);


  TLiwGenericParam param;
  param.SetNameAndValueL(KContentType,TLiwVariant(KLandmark));
  inps->AppendL(param);
  param.Reset();

  CLiwMap* landmarkMap = CLiwDefaultMap::NewL();
  landmarkMap->InsertL(KDbUri,TLiwVariant(KTestDbUri));
//  landmarkMap->InsertL(KLandmarkName,TLiwVariant(KLmSearchString));
  param.SetNameAndValueL(KFilter,TLiwVariant(landmarkMap));
  inps->AppendL(param);
  landmarkMap->DecRef();
  param.Reset();

  iIflandmarks->ExecuteCmdL(KGetList,*inps,*outps,KLiwOptASyncronous,this);
  ret |= CheckErrorCode (*outps,err);
  if ( err != KErrNone )
    {
    iLog->Log( _L(" Getlist on database failed wiht err...") );
    ret |= FAIL;
    }

  if ( !ret )
    CActiveScheduler::Start();
  
   	CleanupStack::PopAndDestroy(2,ServiceHandler);
    ReleaseLandmarkResources();    
	__UHEAP_MARKEND;    
	return ret;
  }
// -----------------------------------------------------------------------------
// CTLandmarkProvider::HandleNotifyL
// This gets called on completion of async request.
// -----------------------------------------------------------------------------
//
TInt CTLandmarkProvider::HandleNotifyL(
            TInt /*aCmdId*/,
            TInt /*aEventId*/,
            CLiwGenericParamList& aEventParamList,
            const CLiwGenericParamList& /*aInputParam*/)
  {
  TInt Index = 0;
  const TLiwGenericParam* itr = aEventParamList.FindFirst(Index,KReturnValue);
  if ( Index > 0 || (0 == Index) )
    {
    iLog->Log( _L("Database iterator found in output ArgList") );
    CLiwIterable* iter = itr->Value().AsIterable();
    if( iter )
       {
       TLiwVariant lmVariant;
        while( iter->NextL(lmVariant) )
            {
            const CLiwMap* landmark = lmVariant.AsMap();
            TLiwVariant variantField;
            TPtrC landmarkName;
            if( landmark )
                {
                if( landmark->FindL(KLandmarkName,variantField) )
                    {
                     variantField.Get(landmarkName);
                    }
                }
            variantField.Reset();
            lmVariant.Reset();
            }
       }
    iter->DecRef();
    }

  CActiveScheduler::Stop();
  return KErrNone;
  }

// -----------------------------------------------------------------------------
// CTLandmarkProvider::CreateLandmarksL
// Helper method to add landmarks to a default database.
// -----------------------------------------------------------------------------
//
void CTLandmarkProvider::CreateLandmarksL (CPosLandmarkDatabase* aLandmarkHandle)
  {
  CPosLandmark* lm = CPosLandmark::NewLC ();
  _LIT(KStreet,"broadway");
//  _LIT(KIconFile,"//s60//icons//qgn_graf_s60_logo.svg");
  _LIT(KDesc,"welcome to galactica");
  TPosition locale;
  locale.SetCoordinate(12.345,67.89);
  lm->SetLandmarkNameL(KLmName1);  
  lm->SetPositionL(locale);
  lm->SetCoverageRadius(12.345);
  lm->SetPositionFieldL(EPositionFieldStreet,KStreet);
  lm->SetLandmarkDescriptionL(KDesc); 
  aLandmarkHandle->AddLandmarkL(*lm);
  CleanupStack::PopAndDestroy(lm);
  lm = CPosLandmark::NewLC ();	
  lm->SetLandmarkNameL  (KLmName2);
  aLandmarkHandle->AddLandmarkL  (*lm);

  lm->SetLandmarkNameL  (KLmName3);
  aLandmarkHandle->AddLandmarkL  (*lm);

  lm->SetLandmarkNameL  (KLmName4);
  aLandmarkHandle->AddLandmarkL  (*lm);

  lm->SetLandmarkNameL  (KLmName5);
  aLandmarkHandle->AddLandmarkL  (*lm);

  lm->SetLandmarkNameL  (KLmName6);
  aLandmarkHandle->AddLandmarkL  (*lm);

  CleanupStack::PopAndDestroy(lm);
  }

// -----------------------------------------------------------------------------
// CTLandmarkProvider::CheckErrorCode
// checks error code e
// called by all testcases.
// -----------------------------------------------------------------------------
//
TInt CTLandmarkProvider::CheckErrorCode( const CLiwGenericParamList& aOutList, TInt32& aError ) const
  {
  TInt Index = 0;
  const TLiwGenericParam* errcode = aOutList.FindFirst(Index,KErrorCode);
  if ( KErrNotFound == Index )
    {
    iLog->Log( _L("ErrorCode not found in output ArgList") );
    return FAIL;
    }
  else
  	{
  	aError = errcode->Value().AsTInt32();
  	return PASS;	
  	}
  
  }

// -----------------------------------------------------------------------------
// CTLandmarkProvider::RemoveAllLandmarks
// Helper method to remove all landmarks for preconditional tests.
// -----------------------------------------------------------------------------
//

void CTLandmarkProvider::RemoveAllLandmarks (CPosLandmarkDatabase* aLandmarkHandle)
  {
    ExecuteAndDeleteLD(aLandmarkHandle->RemoveAllLandmarksL());
  }
// -----------------------------------------------------------------------------
// CTLmAsyncTest::RemoveAllLandmarks
// Helper method to remove all categories for preconditional tests.
// -----------------------------------------------------------------------------
//
void CTLandmarkProvider::RemoveAllCategories  (CPosLmCategoryManager* aHandle)
  {
  TPosLmItemId catID;
  CPosLmItemIterator*iterator = aHandle->CategoryIteratorL();
  CleanupStack::PushL(iterator);

  while ((catID = iterator->NextL()) != KPosLmNullItemId)
    {
      TRAPD(err,ExecuteAndDeleteLD(aHandle->RemoveCategoryL( catID )));
       TBuf8<50> error;
      TRealFormat format;
      error.Num(err,format) ;
      iLog->Log( error );
    }
  CleanupStack::PopAndDestroy(iterator);
}

void CTLandmarkProvider::CreateInterfaceL(CLiwServiceHandler*& aHandler,
								MLiwInterface*& aInterface) 
	{
    iLog->Log( _L("In CreateInterfaceL") );	
	CLiwGenericParamList* InParamList,*OutParamList;

    TRAPD(Err,aHandler = CLiwServiceHandler::NewL());
	if(Err)
		{
		iLog->Log( _L("CLiwServiceHandler Created %d"),Err );
		User::Leave(Err);
		}
    		
    CleanupStack::PushL(aHandler);
 
    InParamList = &(aHandler->InParamListL());
    OutParamList = &(aHandler->OutParamListL());

	CLiwCriteriaItem* crit = CLiwCriteriaItem::NewL(1,KIDataSource,KService);
	CleanupStack::PushL(crit);
	crit->SetServiceClass(TUid::Uid(KLiwClassBase));
	RCriteriaArray a;
	CleanupClosePushL(a);
	a.AppendL(crit);

	aHandler->AttachL(a);

    InParamList->AppendL(TLiwGenericParam(KDbUri,TLiwVariant(KTestDbUri1)));
	  
	aHandler->ExecuteServiceCmdL(*crit,*InParamList,*OutParamList);
		
	TInt Index = 0;
	const TLiwGenericParam* param = OutParamList->FindFirst(Index,KIDataSource);
	if(!param)
		{
		iLog->Log( _L("Interface Not found "));
		User::Leave(KErrGeneral);
		}
		
	aInterface = param->Value().AsInterface();
	CleanupStack::PopAndDestroy(&a);	
	CleanupStack::PopAndDestroy (crit);
	
  	CleanupStack::Pop (aHandler); 
 	iLog->Log( _L("End of CreateInterfaceL") );
  	}

// -----------------------------------------------------------------------------
// CTLandmarkProvider::DeleteAllDatabases
// removes all local databases from the terminal
// called by all testcases.
// -----------------------------------------------------------------------------
//
void CTLandmarkProvider::DeleteAllLocalDatabasesL()
    {
  TInt count;

  CDesCArray* dbList = iDatabaseManager->ListDatabasesLC(_L("file"));
  count = dbList->Count();

  for ( TInt i = 0; i < count; i++ )
    {
    TPtrC db = (*dbList)[i];
    iDatabaseManager->DeleteDatabaseL ( db );
    }
  CleanupStack::PopAndDestroy (1);
    }


// ========================== OTHER EXPORTED FUNCTIONS =========================
// None

//  End of File
