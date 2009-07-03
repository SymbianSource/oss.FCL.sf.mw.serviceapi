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


#include <e32svr.h>
#include <f32file.h>
#include <StifParser.h>
#include <e32std.h>
#include <Stiftestinterface.h>
#include <LiwGenericParam.h>
#include <LiwServiceHandler.h>
#include <epos_cposlandmarkdatabase.h> 
#include <EPos_CPosLmDatabaseManager.h> 
#include <epos_cposlandmark.h> 
#include <epos_cposlandmarkencoder.h> 
#include <epos_cposlmcategorymanager.h> 
#include "tlmprovidercategorytests.h"
#include "landmarkliwparams.hrh"

#define PASS	TInt(0)
#define FAIL	(!PASS)

_LIT(KDefaultDatabase,"c:default.ldb");
// CONSTANTS
_LIT(KCatName1, "lc1");
_LIT(KCatName2, "lca2");
_LIT(KCatName3, "lca3");
_LIT(KCatName4, "category1");
_LIT(KCatName5, "category2");
_LIT(KCatName6, "category3");

_LIT(KOtherCatName1, "loc1");
_LIT(KOtherCatName2, "loc2");
_LIT(KOtherCatName3, "loc3");
_LIT(KOtherCatName4, "othercategory1");
_LIT(KOtherCatName5, "othercategory2");
_LIT(KOtherCatName6, "othercategory3");

_LIT(KCatSearchString, "lc*");
_LIT(KCatSearchString1, "lo*");
_LIT(KCatSearchString2, "lca*");
_LIT(KOtherDatabase,"c:database1.ldb");

// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CTLmCategoryTests::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTLmCategoryTests::RunMethodL( 
    CStifItemParser& aItem ) 
    {
    static TStifFunctionInfo const KFunctions[] =
        {  
        ENTRY( "AddCategory",    		CTLmCategoryTests::AddCategoryL ),
        ENTRY( "AddCategory1",    		CTLmCategoryTests::AddCategory1L ),
        ENTRY( "UpdateCategory", 		CTLmCategoryTests::UpdateCategoryL),
        ENTRY( "UpdateCategory1", 		CTLmCategoryTests::UpdateCategory1L),
        ENTRY( "CategoryAsyncTest1", 		CTLmCategoryTests::CategoryAsyncTest1),
        ENTRY( "CategoryAsyncTest2", 		CTLmCategoryTests::CategoryAsyncTest2),        
        ENTRY( "CategorySyncTest1", 		CTLmCategoryTests::CategorySyncTest1),
        ENTRY( "CategorySyncTest2", 		CTLmCategoryTests::CategorySyncTest2),
        ENTRY( "RemoveCategory", 		CTLmCategoryTests::RemoveCategoryL),
        ENTRY( "RemoveCategory1", 		CTLmCategoryTests::RemoveCategory1L),
        ENTRY( "CancelAsyncTest1", 		CTLmCategoryTests::CancelAsyncTest1),             
        ENTRY( "AddCategoryPos",    		CTLmCategoryTests::AddCategoryL ),
        ENTRY( "UpdateCategoryPos", 		CTLmCategoryTests::UpdateCategoryL),
        ENTRY( "CategoryAsyncTestPos1", 		CTLmCategoryTests::CategoryAsyncTest1),
        ENTRY( "CategorySyncTestPos1", 		CTLmCategoryTests::CategorySyncTest1),
        ENTRY( "RemoveCategoryPos", 		CTLmCategoryTests::RemoveCategoryL),
        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }


// -----------------------------------------------------------------------------
// CTLmCategoryTests::CategorySyncTest1
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CTLmCategoryTests::CategorySyncTest1	( CStifItemParser& /*aItem */ )
	{
	_LIT( KExample, "CategorySyncTest1" );
	iLog->Log( KExample );

	__UHEAP_MARK;
	CLiwServiceHandler* ServiceHandler;
	
	CreateInterfaceL(ServiceHandler,iLandmarkIf);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*iLandmarkIf);
	
    iInList = &(ServiceHandler->InParamListL());
    iOutList = &(ServiceHandler->OutParamListL());

	ResetParams();
	
	TInt32 err;
	TInt ret = 0;
	/*Preconditions*/
	CPosLandmarkDatabase* db = CPosLandmarkDatabase::OpenL(KDefaultDatabase);
	CleanupStack::PushL(db);
	ExecuteAndDeleteLD(db->InitializeL());
	CPosLmCategoryManager* catManager= CPosLmCategoryManager::NewL(*db);
	CleanupStack::PushL(catManager);
	CreateCategoriesL(catManager);
	CleanupStack::PopAndDestroy(2,db);
	
	TLiwGenericParam param;
    param.SetNameAndValueL(KContentType,TLiwVariant(KCategory));    
    iInList->AppendL(param);
    param.Reset();
    
    CLiwMap* categoryMap = CLiwDefaultMap::NewL();
    categoryMap->InsertL(KCategoryName,TLiwVariant(KCatSearchString));
    param.SetNameAndValueL(KFilter,TLiwVariant(categoryMap));    
    iInList->AppendL(param);
    categoryMap->DecRef();
    param.Reset();
    
    iLandmarkIf->ExecuteCmdL(KGetList,*iInList,*iOutList,0,0);
 	ret |= CheckErrorCode (*iOutList,err);
 	if ( err != KErrNone )
		{
		iLog->Log( _L(" Getlist on database failed wiht err...") );
		ret |= FAIL;
		}   

	TInt Index = 0;
	const TLiwGenericParam* itrparm = iOutList->FindFirst(Index,KReturnValue);
	if ( !itrparm )
		{
		iLog->Log( _L("Database iterator not found in output ArgList") );
		ret |= FAIL;
		}
	else
		{
		TLiwVariant cat;
		CLiwIterable* iter = itrparm->Value().AsIterable();
		TInt cnt = 0;
		while ( iter->NextL(cat) )
			{
			const CLiwMap* CategoryMap = cat.AsMap();
			HBufC* category = GetCatNameLC (CategoryMap);
			TPtrC categoryName = category->Des(); 

			if (categoryName == KCatName1 ||
				categoryName == KCatName2 ||
				categoryName == KCatName3)
				{
				cnt++;
				CleanupStack::PopAndDestroy(category);
				}
				
			cat.Reset();
			}
		if ( 3 != cnt )
			{
			iLog->Log( _L("All expected categories not listed") );
			ret |= FAIL;
			}

		iter->Reset();
		cnt = 0;
		while ( iter->NextL(cat) )
			{
			const CLiwMap* CategoryMap = cat.AsMap();
			HBufC* category = GetCatNameLC (CategoryMap);
			TPtrC categoryName = category->Des(); 

			if (categoryName == KCatName1 ||
				categoryName == KCatName2 ||
				categoryName == KCatName3)
				{
				cnt++;
				CleanupStack::PopAndDestroy(category);
				}

			cat.Reset();
			}		
		if ( 3 != cnt )
			{
			iLog->Log( _L("All expected categories not listed after reset") );
			ret |= FAIL;
			}
		}
	
	//prev matches
		iInList->Reset();
		iOutList->Reset();
	  param.SetNameAndValueL(KContentType,TLiwVariant(KCategory));    
    iInList->AppendL(param);
    param.Reset();
    
    categoryMap = CLiwDefaultMap::NewL();
    categoryMap->InsertL(KCategoryName,TLiwVariant(KCatSearchString2));
    categoryMap->InsertL(KPrevMatchesOnly,TLiwVariant((TBool)ETrue));
    param.SetNameAndValueL(KFilter,TLiwVariant(categoryMap));    
    iInList->AppendL(param);
    categoryMap->DecRef();
    param.Reset();
    
    iLandmarkIf->ExecuteCmdL(KGetList,*iInList,*iOutList,0,0);
 	ret |= CheckErrorCode (*iOutList,err);
 	if ( err != KErrNone )
		{
		iLog->Log( _L(" Getlist on database failed wiht err...") );
		ret |= FAIL;
		}   

	Index = 0;
	itrparm = iOutList->FindFirst(Index,KReturnValue);
	if ( !itrparm )
		{
		iLog->Log( _L("Database iterator not found in output ArgList") );
		ret |= FAIL;
		}
	else
		{
		TLiwVariant cat;
		CLiwIterable* iter = itrparm->Value().AsIterable();
		TInt cnt = 0;
		while ( iter->NextL(cat) )
			{
			const CLiwMap* CategoryMap = cat.AsMap();
			HBufC* category = GetCatNameLC (CategoryMap);
			TPtrC categoryName = category->Des(); 

			if (categoryName == KCatName2 ||
				categoryName == KCatName3)
				{
				cnt++;
				CleanupStack::PopAndDestroy(category);
				}

			cat.Reset();
			}
		if ( 2 != cnt )
			{
			iLog->Log( _L("All expected categories not listed") );
			ret |= FAIL;
			}
		}
	iInList->Reset();
	iOutList->Reset();

	iLog->Log( _L("End of CategorySyncTest1") );

  	CleanupStack::PopAndDestroy(2,ServiceHandler);
    ReleaseLandmarkResources();    
	__UHEAP_MARKEND;
	
	return ret;
	}

// -----------------------------------------------------------------------------
// CTLmCategoryTests::CategorySyncTest1
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CTLmCategoryTests::CategorySyncTestPos1	( CStifItemParser& /*aItem */ )
	{
	_LIT( KExample, "CategorySyncTestPos1" );
	iLog->Log( KExample );

	TInt32 err;
	TInt ret = 0;
	__UHEAP_MARK;
	CLiwServiceHandler* ServiceHandler;
	
	CreateInterfaceL(ServiceHandler,iLandmarkIf);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*iLandmarkIf);
	
    iInList = &(ServiceHandler->InParamListL());
    iOutList = &(ServiceHandler->OutParamListL());

	ResetParams();

	/*Preconditions*/
	CPosLandmarkDatabase* db = CPosLandmarkDatabase::OpenL(KDefaultDatabase);
	CleanupStack::PushL(db);
	ExecuteAndDeleteLD(db->InitializeL());
	CPosLmCategoryManager* catManager= CPosLmCategoryManager::NewL(*db);
	CleanupStack::PushL(catManager);
	CreateCategoriesL(catManager);
	CleanupStack::PopAndDestroy(2,db);
	
	TLiwGenericParam param;
    param.SetNameAndValueL(KNullDesC8,TLiwVariant(KCategory));    
    iInList->AppendL(param);
    param.Reset();
    
    CLiwMap* categoryMap = CLiwDefaultMap::NewL();
    categoryMap->InsertL(KCategoryName,TLiwVariant(KCatSearchString));
    param.SetNameAndValueL(KNullDesC8,TLiwVariant(categoryMap));    
    iInList->AppendL(param);
    categoryMap->DecRef();
    param.Reset();
    
    iLandmarkIf->ExecuteCmdL(KGetList,*iInList,*iOutList,0,0);
 	ret |= CheckErrorCode (*iOutList,err);
 	if ( err != KErrNone )
		{
		iLog->Log( _L(" Getlist on database failed wiht err...") );
		ret |= FAIL;
		}   

	TInt Index = 0;
	const TLiwGenericParam* itrparm = iOutList->FindFirst(Index,KReturnValue);
	if ( !itrparm )
		{
		iLog->Log( _L("Database iterator not found in output ArgList") );
		ret |= FAIL;
		}
	else
		{
		TLiwVariant cat;
		CLiwIterable* iter = itrparm->Value().AsIterable();
		TInt cnt = 0;
		while ( iter->NextL(cat) )
			{
			const CLiwMap* CategoryMap = cat.AsMap();
			HBufC* category = GetCatNameLC (CategoryMap);
			TPtrC categoryName = category->Des(); 

			if (categoryName == KCatName1 ||
				categoryName == KCatName2 ||
				categoryName == KCatName3)
				{
				cnt++;
				CleanupStack::PopAndDestroy(category);
				}

			}
		if ( 3 != cnt )
			{
			iLog->Log( _L("All expected categories not listed") );
			ret |= FAIL;
			}

		iter->Reset();
		cnt = 0;
		while ( iter->NextL(cat) )
			{
			const CLiwMap* CategoryMap = cat.AsMap();
			HBufC* category = GetCatNameLC (CategoryMap);
			TPtrC categoryName = category->Des(); 

			if (categoryName == KCatName1 ||
				categoryName == KCatName2 ||
				categoryName == KCatName3)
				{
				cnt++;
				CleanupStack::PopAndDestroy(category);
				}

			}		
		if ( 3 != cnt )
			{
			iLog->Log( _L("All expected categories not listed after reset") );
			ret |= FAIL;
			}
		}
	
	iInList->Reset();
		iOutList->Reset();
	iLog->Log( _L("End of CategorySyncTest1") );

  	CleanupStack::PopAndDestroy(2,ServiceHandler);
    ReleaseLandmarkResources();    
	__UHEAP_MARKEND;
	
	return ret;
	}


// -----------------------------------------------------------------------------
// CTLmCategoryTests::CategorySyncTest1
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CTLmCategoryTests::CategorySyncTest2	( CStifItemParser& /*aItem */ )
	{
	_LIT( KExample, "CategorySyncTest2" );
	iLog->Log( KExample );

	TInt32 err;
	TInt ret = 0;

	__UHEAP_MARK;
	CLiwServiceHandler* ServiceHandler;
	
	CreateInterfaceL(ServiceHandler,iLandmarkIf);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*iLandmarkIf);
	
    iInList = &(ServiceHandler->InParamListL());
    iOutList = &(ServiceHandler->OutParamListL());

	ResetParams();

	/*Preconditions*/
	CPosLandmarkDatabase* db = CPosLandmarkDatabase::OpenL(KDefaultDatabase);
	CleanupStack::PushL(db);
	ExecuteAndDeleteLD(db->InitializeL());
	CPosLmCategoryManager* catManager= CPosLmCategoryManager::NewL(*db);
	CleanupStack::PushL(catManager);
	CreateCategoriesL(catManager);
	CleanupStack::PopAndDestroy(2,db);
	
	HPosLmDatabaseInfo*	 dbInfo	=	HPosLmDatabaseInfo::NewLC(KOtherDatabase);
	iDatabaseManager-> CreateDatabaseL(*dbInfo);
	CleanupStack::PopAndDestroy(dbInfo);
	
	db = CPosLandmarkDatabase::OpenL(KOtherDatabase);
	CleanupStack::PushL(db);
	ExecuteAndDeleteLD(db->InitializeL());
	catManager = CPosLmCategoryManager::NewL(*db);
	CleanupStack::PushL(catManager);
	CreateCategoriesOtherL(catManager);
	CleanupStack::PopAndDestroy(2,db);	
	
		
	TLiwGenericParam param;
    param.SetNameAndValueL(KContentType,TLiwVariant(KCategory));    
    iInList->AppendL(param);
    param.Reset();
    
    CLiwMap* categoryMap = CLiwDefaultMap::NewL();
    categoryMap->InsertL(KCategoryName,TLiwVariant(KCatSearchString));
    param.SetNameAndValueL(KFilter,TLiwVariant(categoryMap));    
    iInList->AppendL(param);
    categoryMap->DecRef();
    param.Reset();
    iLandmarkIf->ExecuteCmdL(KGetList,*iInList,*iOutList,0,0);
 	ret |= CheckErrorCode (*iOutList,err);
 	if ( err != KErrNone )
		{
		iLog->Log( _L(" Getlist on database failed wiht err...") );
		ret |= FAIL;
		}   

	TInt Index = 0;
	const TLiwGenericParam* itrparm = iOutList->FindFirst(Index,KReturnValue);
	if ( !itrparm )
		{
		iLog->Log( _L("Database iterator not found in output ArgList") );
		ret |= FAIL;
		}
	else
		{
		TLiwVariant cat;
		CLiwIterable* iter = itrparm->Value().AsIterable();
		TInt cnt = 0;
		while ( iter->NextL(cat) )
			{
			const CLiwMap* CategoryMap = cat.AsMap();
			HBufC* category = GetCatNameLC (CategoryMap);
			TPtrC categoryName = category->Des(); 

			if (categoryName == KCatName1 ||
				categoryName == KCatName2 ||
				categoryName == KCatName3)
				{
				cnt++;
				CleanupStack::PopAndDestroy(category);
				}
			cat.Reset();
			}
		if ( 3 != cnt )
			{
			iLog->Log( _L("All expected categories not listed") );
			ret |= FAIL;
			}

		iter->Reset();
		cnt = 0;
		while ( iter->NextL(cat) )
			{
			const CLiwMap* CategoryMap = cat.AsMap();
			HBufC* category = GetCatNameLC (CategoryMap);
			TPtrC categoryName = category->Des(); 

			if (categoryName == KCatName1 ||
				categoryName == KCatName2 ||
				categoryName == KCatName3)
				{
				cnt++;
				CleanupStack::PopAndDestroy(category);
				}
			cat.Reset();
			}		
		if ( 3 != cnt )
			{
			iLog->Log( _L("All expected categories not listed after reset") );
			ret |= FAIL;
			}
		
		}
	ResetParams ();
	categoryMap->DecRef();


    param.SetNameAndValueL(KContentType,TLiwVariant(KCategory));    
    iInList->AppendL(param);
    param.Reset();
    
	categoryMap = CLiwDefaultMap::NewL();
    categoryMap->InsertL(KCategoryName,TLiwVariant(KCatSearchString1));
    categoryMap->InsertL(KDbUri,TLiwVariant(KOtherDatabase));
    param.SetNameAndValueL(KFilter,TLiwVariant(categoryMap));    
    iInList->AppendL(param);
    categoryMap->DecRef();
    param.Reset();
    iLandmarkIf->ExecuteCmdL(KGetList,*iInList,*iOutList,0,0);
 	ret |= CheckErrorCode (*iOutList,err);
 	if ( err != KErrNone )
		{
		iLog->Log( _L(" Getlist on database failed wiht err...") );
		ret |= FAIL;
		}   

	Index = 0;
	itrparm = iOutList->FindFirst(Index,KReturnValue);
	if ( !itrparm )
		{
		iLog->Log( _L("Database iterator not found in output ArgList") );
		ret |= FAIL;
		}
	else
		{
		TLiwVariant cat;
		CLiwIterable* iter = itrparm->Value().AsIterable();
		TInt cnt = 0;
		while ( iter->NextL(cat) )
			{
			const CLiwMap* CategoryMap = cat.AsMap();
			HBufC* category = GetCatNameLC (CategoryMap);
			TPtrC categoryName = category->Des(); 

			if (categoryName == KOtherCatName1 ||
				categoryName == KOtherCatName2 ||
				categoryName == KOtherCatName3)
				{
				cnt++;
				CleanupStack::PopAndDestroy(category);
				}
			cat.Reset();
			}
		if ( 3 != cnt )
			{
			iLog->Log( _L("All expected categories not listed") );
			ret |= FAIL;
			}

		iter->Reset();
		cnt = 0;
		while ( iter->NextL(cat) )
			{
			const CLiwMap* CategoryMap = cat.AsMap();
			HBufC* category = GetCatNameLC (CategoryMap);
			TPtrC categoryName = category->Des(); 

			if (categoryName == KOtherCatName1 ||
				categoryName == KOtherCatName2 ||
				categoryName == KOtherCatName3)
				{
				cnt++;
				CleanupStack::PopAndDestroy(category);
				}
			cat.Reset();
			}		
		if ( 3 != cnt )
			{
			iLog->Log( _L("All expected categories not listed after reset") );
			ret |= FAIL;
			}
		
		}    
	categoryMap->DecRef();
 	iInList->Reset();
	iOutList->Reset();

	iLog->Log( _L("End of CategorySyncTest2") );

  	CleanupStack::PopAndDestroy(2,ServiceHandler);
    ReleaseLandmarkResources();    
	__UHEAP_MARKEND;
	return ret;
	}

// -----------------------------------------------------------------------------
// CTLmCategoryTests::CategoryAsyncTest1
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//		
TInt CTLmCategoryTests::CategoryAsyncTest1	( CStifItemParser& /*aItem */ )
	{
	_LIT( KExample, "CategoryAsyncTest1" );
	iLog->Log( KExample );
	iTestID = ETEST1;
	iResult = 0;

	TInt32 err;
	TInt ret = 0;

	__UHEAP_MARK;
	CLiwServiceHandler* ServiceHandler;
	
	CreateInterfaceL(ServiceHandler,iLandmarkIf);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*iLandmarkIf);
	
    iInList = &(ServiceHandler->InParamListL());
    iOutList = &(ServiceHandler->OutParamListL());

	ResetParams();
	
 	/*Preconditions*/
	CPosLandmarkDatabase* db = CPosLandmarkDatabase::OpenL(KDefaultDatabase);
	CleanupStack::PushL(db);
	ExecuteAndDeleteLD(db->InitializeL());
	CPosLmCategoryManager* catManager= CPosLmCategoryManager::NewL(*db);
	CleanupStack::PushL(catManager);
	CreateCategoriesL(catManager);
	CleanupStack::PopAndDestroy(2,db);

	TLiwGenericParam param;
    param.SetNameAndValueL(KContentType,TLiwVariant(KCategory));    
    iInList->AppendL(param);
    param.Reset();
    
    CLiwMap* categoryMap = CLiwDefaultMap::NewL();
    categoryMap->InsertL(KCategoryName,TLiwVariant(KCatSearchString));
    param.SetNameAndValueL(KFilter,TLiwVariant(categoryMap));    
    iInList->AppendL(param);
    categoryMap->DecRef();
    param.Reset();
    
    iLandmarkIf->ExecuteCmdL(KGetList,*iInList,*iOutList,KLiwOptASyncronous,this);
 	ret |= CheckErrorCode (*iOutList,err);
 	if ( err != KErrNone )
		{
		iLog->Log( _L(" Getlist on database failed wiht err...") );
		ret |= FAIL;
		}   

	TInt Index = -1;
	const TLiwGenericParam* cparam = iOutList->FindFirst(Index,KReturnValue);
	if ( cparam )
		{
		iLog->Log( _L("Database iterator found in output ArgList") );
		ret |= FAIL;
		}

	Index = 0;
	cparam = iOutList->FindFirst(Index,KTransactionId);
	if ( !cparam )
		{
		iLog->Log( _L("TransactionID not found in output ArgList") );
		ret |= FAIL;
		}

	if ( !ret )
		CActiveScheduler::Start();

	iLog->Log( _L("End of CategoryAsyncTest1") );	
	ret |= iResult;

  	CleanupStack::PopAndDestroy(2,ServiceHandler);
    ReleaseLandmarkResources();    
	__UHEAP_MARKEND;
	
	return ret;
	}
	
	// -----------------------------------------------------------------------------
// CTLmCategoryTests::CategoryAsyncTestPos1
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//		
TInt CTLmCategoryTests::CategoryAsyncTestPos1	( CStifItemParser& /*aItem */ )
	{
	_LIT( KExample, "CategoryAsyncTestPos1" );
	iLog->Log( KExample );
	iTestID = ETEST1;
	iResult = 0;

	TInt32 err;
	TInt ret = 0;
	
	__UHEAP_MARK;
	CLiwServiceHandler* ServiceHandler;
	
	CreateInterfaceL(ServiceHandler,iLandmarkIf);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*iLandmarkIf);
	
    iInList = &(ServiceHandler->InParamListL());
    iOutList = &(ServiceHandler->OutParamListL());

	ResetParams();
	 
 	/*Preconditions*/
	CPosLandmarkDatabase* db = CPosLandmarkDatabase::OpenL(KDefaultDatabase);
	CleanupStack::PushL(db);
	ExecuteAndDeleteLD(db->InitializeL());
	CPosLmCategoryManager* catManager= CPosLmCategoryManager::NewL(*db);
	CleanupStack::PushL(catManager);
	CreateCategoriesL(catManager);
	CleanupStack::PopAndDestroy(2,db);

	TLiwGenericParam param;
    param.SetNameAndValueL(KNullDesC8,TLiwVariant(KCategory));    
    iInList->AppendL(param);
    param.Reset();
    
    CLiwMap* categoryMap = CLiwDefaultMap::NewL();
    categoryMap->InsertL(KCategoryName,TLiwVariant(KCatSearchString));
    param.SetNameAndValueL(KNullDesC8,TLiwVariant(categoryMap));    
    iInList->AppendL(param);
    categoryMap->DecRef();
    param.Reset();
    
    iLandmarkIf->ExecuteCmdL(KGetList,*iInList,*iOutList,KLiwOptASyncronous,this);
 	ret |= CheckErrorCode (*iOutList,err);
 	if ( err != KErrNone )
		{
		iLog->Log( _L(" Getlist on database failed wiht err...") );
		ret |= FAIL;
		}   

	TInt Index = -1;
	const TLiwGenericParam* cparam = iOutList->FindFirst(Index,KReturnValue);
	if ( cparam )
		{
		iLog->Log( _L("Database iterator found in output ArgList") );
		ret |= FAIL;
		}

	Index = 0;
	cparam = iOutList->FindFirst(Index,KTransactionId);
	if ( !cparam )
		{
		iLog->Log( _L("TransactionID not found in output ArgList") );
		ret |= FAIL;
		}

	if ( !ret )
		CActiveScheduler::Start();

	iLog->Log( _L("End of CategoryAsyncTest1") );	
	ret |= iResult;

  	CleanupStack::PopAndDestroy(2,ServiceHandler);
    ReleaseLandmarkResources();    
	__UHEAP_MARKEND;
	
	return ret;
	}
	
// -----------------------------------------------------------------------------
// CTLmCategoryTests::AddCategoryL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CTLmCategoryTests::AddCategoryL( CStifItemParser& /*aItem */ )
    {
	_LIT( KExample, "In AddCategoryL" );
	_LIT(KOffice,"NokiaUpdate");
	iLog->Log( KExample );

	TInt ret=0;
	TInt32 err;

	__UHEAP_MARK;
	CLiwServiceHandler* ServiceHandler;
	
	CreateInterfaceL(ServiceHandler,iLandmarkIf);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*iLandmarkIf);
	
    iInList = &(ServiceHandler->InParamListL());
    iOutList = &(ServiceHandler->OutParamListL());

	ResetParams();

	/*Preconditions*/

	TLiwGenericParam param;
	param.SetNameAndValueL(KContentType,TLiwVariant(KCategory));    
	iInList->AppendL(param);
	param.Reset();

	CLiwMap* categoryMap = CLiwDefaultMap::NewL();
	categoryMap->InsertL(KCategoryName,TLiwVariant(KOffice));
	param.SetNameAndValueL(KDataFields,TLiwVariant(categoryMap));    
	iInList->AppendL(param);
	categoryMap->DecRef();
	param.Reset();

	iLandmarkIf->ExecuteCmdL(KAdd,*iInList,*iOutList,0,0);
 	ret |= CheckErrorCode (*iOutList,err);
 	if ( err != KErrNone )
		{
		iLog->Log( _L(" AddCategory on database failed with err...") );
		ret |= FAIL;
		}

	iLog->Log( _L("End of AddCategoryL") );
  	
  	CleanupStack::PopAndDestroy(2,ServiceHandler);
    ReleaseLandmarkResources();    
	__UHEAP_MARKEND;
	return ret;
    }
    
    // -----------------------------------------------------------------------------
// CTLmCategoryTests::AddCategoryL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CTLmCategoryTests::AddCategoryPosL( CStifItemParser& /*aItem */ )
    {
	_LIT( KExample, "In AddCategoryPosL" );
	_LIT(KOffice,"NokiaUpdate");
	iLog->Log( KExample );

	TInt ret=0;
	TInt32 err;

	__UHEAP_MARK;
	CLiwServiceHandler* ServiceHandler;
	
	CreateInterfaceL(ServiceHandler,iLandmarkIf);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*iLandmarkIf);
	
    iInList = &(ServiceHandler->InParamListL());
    iOutList = &(ServiceHandler->OutParamListL());

	ResetParams();
	/*Preconditions*/

	TLiwGenericParam param;
	param.SetNameAndValueL(KNullDesC8,TLiwVariant(KCategory));    
	iInList->AppendL(param);
	param.Reset();

	CLiwMap* categoryMap = CLiwDefaultMap::NewL();
	categoryMap->InsertL(KCategoryName,TLiwVariant(KOffice));
	param.SetNameAndValueL(KNullDesC8,TLiwVariant(categoryMap));    
	iInList->AppendL(param);
	categoryMap->DecRef();
	param.Reset();

	iLandmarkIf->ExecuteCmdL(KAdd,*iInList,*iOutList,0,0);
 	ret |= CheckErrorCode (*iOutList,err);
 	if ( err != KErrNone )
		{
		iLog->Log( _L(" AddCategory on database failed with err...") );
		ret |= FAIL;
		}

	iLog->Log( _L("End of AddCategoryL") );
  	CleanupStack::PopAndDestroy(2,ServiceHandler);
    ReleaseLandmarkResources();    
	__UHEAP_MARKEND;
	return ret;
    }
    
// -----------------------------------------------------------------------------
// CTLmCategoryTests::AddCategory1L
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CTLmCategoryTests::AddCategory1L( CStifItemParser& /*aItem */)
    {
	_LIT( KExample, "In AddCategory1L" );
	iLog->Log( KExample );
	_LIT(KOffice1,"NokiaPrevious");
	_LIT(KOffice,"NokiaUpdate");
	TInt ret=0;
	TInt32 err;

	__UHEAP_MARK;
	CLiwServiceHandler* ServiceHandler;
	
	CreateInterfaceL(ServiceHandler,iLandmarkIf);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*iLandmarkIf);
	
    iInList = &(ServiceHandler->InParamListL());
    iOutList = &(ServiceHandler->OutParamListL());

	ResetParams();


	/*Preconditions*/

	HPosLmDatabaseInfo*	 dbInfo	=	HPosLmDatabaseInfo::NewLC(KOtherDatabase);
	iDatabaseManager-> CreateDatabaseL(*dbInfo);
	CleanupStack::PopAndDestroy(dbInfo);
	
	TLiwGenericParam param;
	param.SetNameAndValueL(KContentType,TLiwVariant(KCategory));
	iInList->AppendL(param);
	param.Reset();

	CLiwMap* categoryMap = CLiwDefaultMap::NewL();
	categoryMap->InsertL(KCategoryName,TLiwVariant(KOffice));
	param.SetNameAndValueL(KDataFields,TLiwVariant(categoryMap));    
	iInList->AppendL(param);
	categoryMap->DecRef();
	param.Reset();

	iLandmarkIf->ExecuteCmdL(KAdd,*iInList,*iOutList,0,0);
 	ret |= CheckErrorCode (*iOutList,err);
 	if ( err != KErrNone )
		{
		iLog->Log( _L(" AddCategory on database failed with err...") );
		ret |= FAIL;
		}
	categoryMap->DecRef();
	ResetParams();

	categoryMap = CLiwDefaultMap::NewL();
	param.SetNameAndValueL(KContentType,TLiwVariant(KCategory));
	iInList->AppendL(param);
	param.Reset();
	categoryMap->InsertL(KCategoryName,TLiwVariant(KOffice));
	categoryMap->InsertL(KDbUri,TLiwVariant(KOtherDatabase));
	param.SetNameAndValueL(KDataFields,TLiwVariant(categoryMap));    
	iInList->AppendL(param);
	categoryMap->DecRef();
	param.Reset();

	iLog->Log( _L(" Calling ExecuteCmdL again.") );
	iLandmarkIf->ExecuteCmdL(KAdd,*iInList,*iOutList,0,0);
 	ret |= CheckErrorCode (*iOutList,err);
 	if ( err != KErrNone )
		{
		iLog->Log( _L(" AddCategory on database failed with err...") );
		ret |= FAIL;
		}
	categoryMap->DecRef();
	ResetParams();


	categoryMap = CLiwDefaultMap::NewL();
	param.SetNameAndValueL(KContentType,TLiwVariant(KCategory));
	iInList->AppendL(param);
	param.Reset();
	categoryMap->InsertL(KCategoryName,TLiwVariant(KOffice1));
	categoryMap->InsertL(KDbUri,TLiwVariant(KOtherDatabase));
	param.SetNameAndValueL(KDataFields,TLiwVariant(categoryMap));    
	iInList->AppendL(param);
	categoryMap->DecRef();
	param.Reset();
	iLandmarkIf->ExecuteCmdL(KAdd,*iInList,*iOutList,0,0);
 	ret |= CheckErrorCode (*iOutList,err);
 	if ( err != KErrNone )
		{
		iLog->Log( _L(" AddCategory on database failed with err...") );
		ret |= FAIL;
		}
	
	iLog->Log( _L("End of AddCategory1L") );
  	
  	CleanupStack::PopAndDestroy(2,ServiceHandler);
    ReleaseLandmarkResources();    
	__UHEAP_MARKEND;
	return ret;
    }

// -----------------------------------------------------------------------------
// CTLmCategoryTests::UpdateCategoryL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CTLmCategoryTests::UpdateCategoryL( CStifItemParser& /*aItem */)
    {
    _LIT( KExample, "In UpdateCategoryL" );
    iLog->Log( KExample );
	_LIT(KOffice,"NokiaUpdate");
	TInt ret=0;
	TInt32 err;
	TPosLmItemId catid1;

	__UHEAP_MARK;
	CLiwServiceHandler* ServiceHandler;
	
	CreateInterfaceL(ServiceHandler,iLandmarkIf);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*iLandmarkIf);
	
    iInList = &(ServiceHandler->InParamListL());
    iOutList = &(ServiceHandler->OutParamListL());

	ResetParams();


 	/*Preconditions*/

	CPosLandmarkDatabase* db = CPosLandmarkDatabase::OpenL(KDefaultDatabase);
	CleanupStack::PushL(db);
	ExecuteAndDeleteLD(db->InitializeL());
	CPosLmCategoryManager* catManager= CPosLmCategoryManager::NewL(*db);
	CleanupStack::PushL(catManager);
	CPosLandmarkCategory* category = CPosLandmarkCategory::NewLC();
	category->SetCategoryNameL(KOffice);
	catid1=catManager->AddCategoryL(*category);
	CleanupStack::PopAndDestroy(3,db);

	TLiwGenericParam param;
	param.SetNameAndValueL(KContentType,TLiwVariant(KCategory));
	iInList->AppendL(param);
	param.Reset();
	
	CLiwMap* categoryMap = CLiwDefaultMap::NewL();
	TBuf<5> catIdString1;
    catIdString1.Num(catid1,EDecimal);
    categoryMap->InsertL(KId,TLiwVariant(catIdString1));
	categoryMap->InsertL(KCategoryName,TLiwVariant(KOffice));
	param.SetNameAndValueL(KDataFields,TLiwVariant(categoryMap));    
	iInList->AppendL(param);
	categoryMap->DecRef();
	param.Reset();
	iLandmarkIf->ExecuteCmdL(KAdd,*iInList,*iOutList,0,0);
	ret |= CheckErrorCode (*iOutList,err);
 	if ( err != KErrNone )
		{
		iLog->Log( _L(" UpdateCategory1L on database failed with err...") );
		ret |= FAIL;
		}
	categoryMap->DecRef();

	iLog->Log( _L("End of UpdateCategoryL") );

  	CleanupStack::PopAndDestroy(2,ServiceHandler);
    ReleaseLandmarkResources();    
	__UHEAP_MARKEND;
	return ret;
  }

// -----------------------------------------------------------------------------
// CTLmCategoryTests::UpdateCategoryL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CTLmCategoryTests::UpdateCategoryPosL( CStifItemParser& /*aItem */)
    {
    _LIT( KExample, "In UpdateCategoryPosL" );
    iLog->Log( KExample );
	_LIT(KOffice,"NokiaUpdate");
	TInt ret=0;
	TInt32 err;
	TPosLmItemId catid1;

	__UHEAP_MARK;
	CLiwServiceHandler* ServiceHandler;
	
	CreateInterfaceL(ServiceHandler,iLandmarkIf);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*iLandmarkIf);
	
    iInList = &(ServiceHandler->InParamListL());
    iOutList = &(ServiceHandler->OutParamListL());

	ResetParams();


 	/*Preconditions*/

	CPosLandmarkDatabase* db = CPosLandmarkDatabase::OpenL(KDefaultDatabase);
	CleanupStack::PushL(db);
	ExecuteAndDeleteLD(db->InitializeL());
	CPosLmCategoryManager* catManager= CPosLmCategoryManager::NewL(*db);
	CleanupStack::PushL(catManager);
	CPosLandmarkCategory* category = CPosLandmarkCategory::NewLC();
	category->SetCategoryNameL(KOffice);
	catid1=catManager->AddCategoryL(*category);
	CleanupStack::PopAndDestroy(3,db);

	TLiwGenericParam param;
	param.SetNameAndValueL(KNullDesC8,TLiwVariant(KCategory));
	iInList->AppendL(param);
	param.Reset();
	
	CLiwMap* categoryMap = CLiwDefaultMap::NewL();
	TBuf<5> catIdString1;
    catIdString1.Num(catid1,EDecimal);
    categoryMap->InsertL(KId,TLiwVariant(catIdString1));
	categoryMap->InsertL(KCategoryName,TLiwVariant(KOffice));
	param.SetNameAndValueL(KNullDesC8,TLiwVariant(categoryMap));    
	iInList->AppendL(param);
	categoryMap->DecRef();
	param.Reset();
	iLandmarkIf->ExecuteCmdL(KAdd,*iInList,*iOutList,0,0);
	ret |= CheckErrorCode (*iOutList,err);
 	if ( err != KErrNone )
		{
		iLog->Log( _L(" UpdateCategory1L on database failed with err...") );
		ret |= FAIL;
		}
	categoryMap->DecRef();

	iLog->Log( _L("End of UpdateCategoryL") );
  	
  	CleanupStack::PopAndDestroy(2,ServiceHandler);
    ReleaseLandmarkResources();    
	__UHEAP_MARKEND;
	return ret;
  }

// -----------------------------------------------------------------------------
// CTLmCategoryTests::UpdateCategory1L
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CTLmCategoryTests::UpdateCategory1L( CStifItemParser& /*aItem */)
    {
    _LIT( KExample, "In UpdateCategory1L" );
    iLog->Log( KExample );
	_LIT(KOffice1,"NokiaPrevious");
	_LIT(KOffice,"NokiaUpdate");
	TInt ret=0;
	TInt32 err;
	TPosLmItemId catid1,catid2;

	__UHEAP_MARK;
	CLiwServiceHandler* ServiceHandler;
	
	CreateInterfaceL(ServiceHandler,iLandmarkIf);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*iLandmarkIf);
	
    iInList = &(ServiceHandler->InParamListL());
    iOutList = &(ServiceHandler->OutParamListL());

	ResetParams();


 	/*Preconditions*/
	CPosLandmarkDatabase* db = CPosLandmarkDatabase::OpenL(KDefaultDatabase);
	CleanupStack::PushL(db);
	ExecuteAndDeleteLD(db->InitializeL());
	CPosLmCategoryManager* catManager= CPosLmCategoryManager::NewL(*db);
	CleanupStack::PushL(catManager);
	CPosLandmarkCategory* category = CPosLandmarkCategory::NewLC();
	category->SetCategoryNameL(KOffice);
	catid1=catManager->AddCategoryL(*category);
	CleanupStack::PopAndDestroy(3,db);

	HPosLmDatabaseInfo*	 dbInfo	=	HPosLmDatabaseInfo::NewLC(KOtherDatabase);
	iDatabaseManager-> CreateDatabaseL(*dbInfo);
	CleanupStack::PopAndDestroy(dbInfo);
	
	db = CPosLandmarkDatabase::OpenL(KOtherDatabase);
	CleanupStack::PushL(db);
	ExecuteAndDeleteLD(db->InitializeL());
	catManager= CPosLmCategoryManager::NewL(*db);
	CleanupStack::PushL(catManager);
	category = CPosLandmarkCategory::NewLC();
	category->SetCategoryNameL(KOffice1);
	catid2=catManager->AddCategoryL(*category);
	CleanupStack::PopAndDestroy(3,db);	
	
	TLiwGenericParam param;
	param.SetNameAndValueL(KContentType,TLiwVariant(KCategory));    
	iInList->AppendL(param);
	param.Reset();
	
	CLiwMap* categoryMap = CLiwDefaultMap::NewL();
	TBuf<5> catIdString1;
    catIdString1.Num(catid1,EDecimal);
    categoryMap->InsertL(KId,TLiwVariant(catIdString1));
	categoryMap->InsertL(KCategoryName,TLiwVariant(KOffice));
	param.SetNameAndValueL(KDataFields,TLiwVariant(categoryMap));    
	iInList->AppendL(param);
	categoryMap->DecRef();
	param.Reset();
	iLandmarkIf->ExecuteCmdL(KAdd,*iInList,*iOutList,0,0);
	ret |= CheckErrorCode (*iOutList,err);
 	if ( err != KErrNone )
		{
		iLog->Log( _L(" UpdateCategory1L on database failed with err...") );
		ret |= FAIL;
		}
	categoryMap->DecRef();
	ResetParams();
	
	param.SetNameAndValueL(KContentType,TLiwVariant(KCategory));    
	iInList->AppendL(param);
	param.Reset();
	categoryMap = CLiwDefaultMap::NewL();
	TBuf<5> catIdString2;
    catIdString2.Num(catid2,EDecimal);
    categoryMap->InsertL(KId,TLiwVariant(catIdString2));
	categoryMap->InsertL(KCategoryName,TLiwVariant(KOffice));
	categoryMap->InsertL(KDbUri,TLiwVariant(KOtherDatabase));
	param.SetNameAndValueL(KDataFields,TLiwVariant(categoryMap));    
	iInList->AppendL(param);
	categoryMap->DecRef();
	param.Reset();
	iLandmarkIf->ExecuteCmdL(KAdd,*iInList,*iOutList,0,0);
	ret |= CheckErrorCode (*iOutList,err);
 	if ( err != KErrNone )
		{
		iLog->Log( _L(" UpdateCategory1L on database failed with err...") );
		ret |= FAIL;
		}
	categoryMap->DecRef();

	iLog->Log( _L("End of UpdateCategory1L") );
  	
  	CleanupStack::PopAndDestroy(2,ServiceHandler);
    ReleaseLandmarkResources();    
	__UHEAP_MARKEND;
	
	return ret;
  }
  
// -----------------------------------------------------------------------------
// CTLmCategoryTests::CheckErrorCode
// checks error code e
// called by all testcases.
// -----------------------------------------------------------------------------
//
TInt CTLmCategoryTests::CheckErrorCode( const CLiwGenericParamList& aOutList, TInt32 &aError )
	{
	iLog->Log( _L("In CheckErrorCode") );
	TInt Index = 0;
	const TLiwGenericParam* errcode = aOutList.FindFirst(Index,KErrorCode);
	if ( KErrNotFound == Index )
		{
		iLog->Log( _L("ErrorCode not found in output ArgList") );
		return FAIL;
		}
	else
		errcode->Value().Get(aError);
	iLog->Log( _L("End of CheckErrorCode") );	
	return PASS;
	}

// -----------------------------------------------------------------------------
// CTLmCategoryTests::RemoveAllCategoriesL
// Helper method to remove all categories for preconditional tests.
// -----------------------------------------------------------------------------
//  
void CTLmCategoryTests::RemoveAllCategoriesL	(CPosLmCategoryManager* aHandle)
	{
	iLog->Log( _L("In RemoveAllCategoriesLL") );
	TPosLmItemId catID;
	CPosLmItemIterator*iterator = aHandle->CategoryIteratorL();
	CleanupStack::PushL(iterator);
	
	while ((catID = iterator->NextL()) != KPosLmNullItemId)
		{
	    TRAP_IGNORE(ExecuteAndDeleteLD(aHandle->RemoveCategoryL( catID )));
		}
	CleanupStack::PopAndDestroy(iterator);
	iLog->Log( _L("End of RemoveAllCategoriesLL") );
}  

// -----------------------------------------------------------------------------
// CTLmCategoryTests::HandleNotifyL
// This gets called on completion of async request.
// -----------------------------------------------------------------------------
//
TInt CTLmCategoryTests::HandleNotifyL(
            TInt /*aCmdId*/,
            TInt /*aEventId*/,
            CLiwGenericParamList& aEventParamList,
            const CLiwGenericParamList& /*aInputParam*/)
	{
	iLog->Log( _L("In HandleNotifyL") );
	switch (iTestID)
		{
			case ETEST1:
				iResult = HandleAsyncTest1(aEventParamList);
				break;
			case ETEST2:
				iResult = HandleAsyncTest2(aEventParamList);
				break;
			case ETEST3:
				return KErrNone;
				
			default: 
				break;
		}
	iLog->Log( _L("Stopping Active Schduler in HandleNotifyL") );
	CActiveScheduler::Stop();
	return KErrNone;
	}
	
// -----------------------------------------------------------------------------
// CTLmCategoryTests::CreateCategoriesL
// Helper method to add categories to a default database.
// -----------------------------------------------------------------------------
// 
void CTLmCategoryTests::CreateCategoriesL (CPosLmCategoryManager* aHandle)
	{
	iLog->Log( _L("In CreateCategoriesL") );
	CPosLandmarkCategory * lc = CPosLandmarkCategory::NewLC ();

	lc->SetCategoryNameL (KCatName1);
	aHandle->AddCategoryL (*lc);

	lc->SetCategoryNameL (KCatName2);
	aHandle->AddCategoryL (*lc);

	lc->SetCategoryNameL (KCatName3);
	aHandle->AddCategoryL (*lc);

	lc->SetCategoryNameL (KCatName4);
	aHandle->AddCategoryL (*lc);

	lc->SetCategoryNameL (KCatName5);
	aHandle->AddCategoryL (*lc);

	lc->SetCategoryNameL (KCatName6);
	aHandle->AddCategoryL (*lc);

	CleanupStack::PopAndDestroy(lc);
	iLog->Log( _L("End of CreateCategoriesL") );
	}	
// -----------------------------------------------------------------------------
// CTLmCategoryTests::CreateCategoriesOtherL
// Helper method to add categories to a default database.
// -----------------------------------------------------------------------------
// 
void CTLmCategoryTests::CreateCategoriesOtherL (CPosLmCategoryManager* aHandle)	
	{
	iLog->Log( _L("In CreateCategoriesOtherL") );
	CPosLandmarkCategory * lc = CPosLandmarkCategory::NewLC ();

	lc->SetCategoryNameL (KOtherCatName1);
	aHandle->AddCategoryL (*lc);

	lc->SetCategoryNameL (KOtherCatName2);
	aHandle->AddCategoryL (*lc);

	lc->SetCategoryNameL (KOtherCatName3);
	aHandle->AddCategoryL (*lc);

	lc->SetCategoryNameL (KOtherCatName4);
	aHandle->AddCategoryL (*lc);

	lc->SetCategoryNameL (KOtherCatName5);
	aHandle->AddCategoryL (*lc);

	lc->SetCategoryNameL (KOtherCatName6);
	aHandle->AddCategoryL (*lc);

	CleanupStack::PopAndDestroy(lc);
	iLog->Log( _L("End of CreateCategoriesOtherL") );
	}	
// -----------------------------------------------------------------------------
// CTLmCategoryTests::DeleteAllDatabases
// removes all local databases from the terminal 
// called by all testcases.
// -----------------------------------------------------------------------------
//
void CTLmCategoryTests::DeleteAllLocalDatabasesL() 
    {
	iLog->Log( _L("In DeleteAllLocalDatabasesL") );
	TInt count;
	CDesCArray* dbList = iDatabaseManager->ListDatabasesLC(_L("file"));
	count = dbList->Count();

	for ( TInt i = 0; i < count; i++ )
		{
		TPtrC db = (*dbList)[i];
		iDatabaseManager->DeleteDatabaseL ( db );
		}
	CleanupStack::PopAndDestroy (dbList);
	iLog->Log( _L("End of DeleteAllLocalDatabasesL") );
    }	
// -----------------------------------------------------------------------------
// CTLmCategoryTests::ResetParams
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
void CTLmCategoryTests:: ResetParams ()
	{
	iLog->Log( _L("In ResetParams") );
	iOutList->Reset();
	iInList->Reset();
	iLog->Log( _L("End of ResetParams") );
	}
// -----------------------------------------------------------------------------
// CTLmCategoryTests::GetCatName
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
HBufC* CTLmCategoryTests::GetCatNameLC	(const CLiwMap* aCategoryMap)
	{
	iLog->Log( _L("In GetCatName") );
	TLiwVariant value;
	if ( aCategoryMap->FindL(KCategoryName,value) )
		{
		TPtrC catname;
		value.Get(catname);
		iLog->Log( _L("End of GetCatName") );
		HBufC* temp = catname.AllocLC();
		value.Reset();
		return (temp);
		}
	else
		{
		iLog->Log( _L("End of GetCatName") );
		return (NULL);
		}
	
	}

// -----------------------------------------------------------------------------
// CTLmCategoryTests::HandleAsyncTest1
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CTLmCategoryTests::HandleAsyncTest1 (const CLiwGenericParamList& aEventParamList)
{
	TInt ret = 0;
	TInt Index = 0;
	iLog->Log( _L("In HandleAsyncTest1") );
	const TLiwGenericParam* itrparm = aEventParamList.FindFirst(Index,KReturnValue);
	TLiwVariant cat;
	CLiwIterable* iter = itrparm->Value().AsIterable();
	TInt cnt = 0;
	while ( iter->NextL(cat) )
		{
		const CLiwMap* CategoryMap = cat.AsMap();
		HBufC* category = GetCatNameLC (CategoryMap);
		TPtrC categoryName = category->Des(); 

		if (categoryName == KCatName1 ||
			categoryName == KCatName2 ||
			categoryName == KCatName3)
			{
			cnt++;
			CleanupStack::PopAndDestroy(category);
			}
		cat.Reset();
		}
	if ( 3 != cnt )
		{
		iLog->Log( _L("All expected categories not listed") );
		ret |= FAIL;
		}

	iter->Reset();
	cnt = 0;
	while ( iter->NextL(cat) )
		{
		const CLiwMap* CategoryMap = cat.AsMap();
		HBufC* category = GetCatNameLC (CategoryMap);
		TPtrC categoryName = category->Des(); 

		if (categoryName == KCatName1 ||
			categoryName == KCatName2 ||
			categoryName == KCatName3)
			{
			cnt++;
			CleanupStack::PopAndDestroy(category);
			}
		cat.Reset();
		}		
	if ( 3 != cnt )
		{
		iLog->Log( _L("All expected categories not listed after reset") );
		ret |= FAIL;
		}
		
	iLog->Log( _L("End of HandleAsyncTest1") );
	return ret;
}

// -----------------------------------------------------------------------------
// CTLmCategoryTests::CategoryAsyncTest2
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//		
TInt CTLmCategoryTests::CategoryAsyncTest2	( CStifItemParser& /*aItem */ )
	{
	_LIT( KExample, "CategoryAsyncTest2" );
	iLog->Log( KExample );
	iTestID = ETEST2;
	iResult = 0;
	TInt32 err;
	TInt ret = 0;

	__UHEAP_MARK;
	CLiwServiceHandler* ServiceHandler;
	
	CreateInterfaceL(ServiceHandler,iLandmarkIf);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*iLandmarkIf);
	
    iInList = &(ServiceHandler->InParamListL());
    iOutList = &(ServiceHandler->OutParamListL());

	ResetParams();

	/*Preconditions*/
	HPosLmDatabaseInfo*	 dbInfo	=	HPosLmDatabaseInfo::NewLC(KOtherDatabase);
	iDatabaseManager-> CreateDatabaseL(*dbInfo);
	CleanupStack::PopAndDestroy(dbInfo);


	CPosLandmarkDatabase* db = CPosLandmarkDatabase::OpenL();
	CleanupStack::PushL(db);
	ExecuteAndDeleteLD(db->InitializeL());
	CPosLmCategoryManager* catManager= CPosLmCategoryManager::NewL(*db);
	CleanupStack::PushL(catManager);
	CreateCategoriesL(catManager);
	CleanupStack::PopAndDestroy(2,db);
	
	db = CPosLandmarkDatabase::OpenL(KOtherDatabase);
	CleanupStack::PushL(db);
	ExecuteAndDeleteLD(db->InitializeL());
	catManager = CPosLmCategoryManager::NewL(*db);
	CleanupStack::PushL(catManager);
	CreateCategoriesOtherL(catManager);
	CleanupStack::PopAndDestroy(2,db);	
	
		
	TLiwGenericParam param;
    param.SetNameAndValueL(KContentType,TLiwVariant(KCategory));    
    iInList->AppendL(param);
    param.Reset();
    
    CLiwMap* categoryMap = CLiwDefaultMap::NewL();
    categoryMap->InsertL(KCategoryName,TLiwVariant(KCatSearchString));
    iInList->AppendL(TLiwGenericParam(KFilter,TLiwVariant(categoryMap)));
    categoryMap->DecRef();
    iAsyncCallCnt = 0;
    iLandmarkIf->ExecuteCmdL(KGetList,*iInList,*iOutList,KLiwOptASyncronous,this);
 	ret |= CheckErrorCode (*iOutList,err);
 	if ( err != KErrNone )
		{
		iLog->Log( _L(" Getlist on database failed with err...") );
		ret |= FAIL;
		}   

	TInt Index = -1;
	const TLiwGenericParam* cparam = iOutList->FindFirst(Index,KReturnValue);
	if ( cparam )
		{
			CLiwIterable* iterable = cparam->Value().AsIterable();
		
		iLog->Log( _L("Database iterator found in output ArgList") );
		ret |= FAIL;
		}

	Index = 0;
	cparam = iOutList->FindFirst(Index,KTransactionId);
	if ( !cparam )
		{
		iLog->Log( _L("TransactionID not found in output ArgList") );
		ret |= FAIL;
		}
	categoryMap->DecRef();
	ResetParams ();
	if ( !ret )
		CActiveScheduler::Start();
	
	

    param.SetNameAndValueL(KContentType,TLiwVariant(KCategory));    
    iInList->AppendL(param);
    param.Reset();
    
	categoryMap = CLiwDefaultMap::NewL();
    categoryMap->InsertL(KCategoryName,TLiwVariant(KCatSearchString1));
    categoryMap->InsertL(KDbUri,TLiwVariant(KOtherDatabase));
    iInList->AppendL(TLiwGenericParam(KFilter,TLiwVariant(categoryMap)));
    categoryMap->DecRef();
    
    iAsyncCallCnt = 1;
    iLandmarkIf->ExecuteCmdL(KGetList,*iInList,*iOutList,KLiwOptASyncronous,this);
 	ret |= CheckErrorCode (*iOutList,err);
 	if ( err != KErrNone )
		{
		iLog->Log( _L(" Getlist on database failed with err...") );
		ret |= FAIL;
		}   

	Index = -1;
	cparam = iOutList->FindFirst(Index,KReturnValue);
	if ( cparam )
		{
		CLiwIterable* iterable = cparam->Value().AsIterable();
			
		iLog->Log( _L("Database iterator found in output ArgList") );
		ret |= FAIL;
		}
	Index = 0;
	cparam = iOutList->FindFirst(Index,KTransactionId);
	if ( !cparam )
		{
		iLog->Log( _L("TransactionID not found in output ArgList") );
		ret |= FAIL;
		}
	categoryMap->DecRef();
	ResetParams ();
	if ( !ret )
		CActiveScheduler::Start();

	ret |= iResult;
	iLog->Log( _L("End of CategoryAsyncTest2") );	
  	
  	CleanupStack::PopAndDestroy(2,ServiceHandler);
    ReleaseLandmarkResources();    
	__UHEAP_MARKEND;

	return ret;
	}
// -----------------------------------------------------------------------------
// CTLmCategoryTests::HandleAsyncTest2
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CTLmCategoryTests::HandleAsyncTest2 (const CLiwGenericParamList& aEventParamList)
{
	TInt ret = 0;
	TInt Index = 0;
	iLog->Log( _L("In HandleAsyncTest2") );
	const TLiwGenericParam* itrparm = aEventParamList.FindFirst(Index,KReturnValue);
	TLiwVariant cat;
	CLiwIterable* iter = itrparm->Value().AsIterable();
	if (iAsyncCallCnt == 0)
		{
		TInt cnt = 0;
		while ( iter->NextL(cat) )
			{
			const CLiwMap* CategoryMap = cat.AsMap();
			HBufC* category = GetCatNameLC (CategoryMap);
			TPtrC categoryName = category->Des(); 

			if (categoryName == KCatName1 ||
				categoryName == KCatName2 ||
				categoryName == KCatName3)
				{
				cnt++;
				CleanupStack::PopAndDestroy(category);
				}
			cat.Reset();
			}
		if ( 3 != cnt )
			{
			iLog->Log( _L("All expected categories not listed") );
			ret |= FAIL;
			}

		iter->Reset();
		cnt = 0;
		while ( iter->NextL(cat) )
			{
			const CLiwMap* CategoryMap = cat.AsMap();
			HBufC* category = GetCatNameLC (CategoryMap);
			TPtrC categoryName = category->Des(); 

			if (categoryName == KCatName1 ||
				categoryName == KCatName2 ||
				categoryName == KCatName3)
				{
				cnt++;
				CleanupStack::PopAndDestroy(category);
				}
			cat.Reset();
			}		
		if ( 3 != cnt )
			{
			iLog->Log( _L("All expected categories not listed after reset") );
			ret |= FAIL;
			}
		}
	else
		{
		TInt cnt = 0;
		while ( iter->NextL(cat) )
			{
			const CLiwMap* CategoryMap = cat.AsMap();
			HBufC* category = GetCatNameLC (CategoryMap);
			TPtrC categoryName = category->Des(); 

			if (categoryName == KOtherCatName1 ||
				categoryName == KOtherCatName2 ||
				categoryName == KOtherCatName3)
				{
				cnt++;
				CleanupStack::PopAndDestroy(category);
				}
			cat.Reset();
			}
		if ( 3 != cnt )
			{
			iLog->Log( _L("All expected categories not listed") );
			ret |= FAIL;
			}

		iter->Reset();
		cnt = 0;
		while ( iter->NextL(cat) )
			{
			const CLiwMap* CategoryMap = cat.AsMap();
			HBufC* category = GetCatNameLC (CategoryMap);
			TPtrC categoryName = category->Des(); 

			if (categoryName == KOtherCatName1 ||
				categoryName == KOtherCatName2 ||
				categoryName == KOtherCatName3)
				{
				cnt++;
				CleanupStack::PopAndDestroy(category);
				}
			cat.Reset();
			}		
		if ( 3 != cnt )
			{
			iLog->Log( _L("All expected categories not listed after reset") );
			ret |= FAIL;
			}
		}
		
	iLog->Log( _L("End of HandleAsyncTest2") );
	return ret;
}	

// -----------------------------------------------------------------------------
// CTLmCategoryTests::RemoveCategoryL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CTLmCategoryTests::RemoveCategoryL	( CStifItemParser& /*aItem */ )
	{
	_LIT( KExample, "RemoveCategoryL" );
	_LIT(KOffice,"NokiaUpdate");
	iLog->Log( KExample );
	TInt32 err;
	TInt ret = 0;
	TPosLmItemId catid1;
	
	__UHEAP_MARK;
	CLiwServiceHandler* ServiceHandler;
	
	CreateInterfaceL(ServiceHandler,iLandmarkIf);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*iLandmarkIf);
	
    iInList = &(ServiceHandler->InParamListL());
    iOutList = &(ServiceHandler->OutParamListL());

	ResetParams();

 	/*Preconditions*/
	CPosLandmarkDatabase* db = CPosLandmarkDatabase::OpenL(KDefaultDatabase);
	CleanupStack::PushL(db);
	ExecuteAndDeleteLD(db->InitializeL());
	CPosLmCategoryManager* catManager= CPosLmCategoryManager::NewL(*db);
	CleanupStack::PushL(catManager);
	CPosLandmarkCategory* category = CPosLandmarkCategory::NewLC();
	category->SetCategoryNameL(KOffice);
	catid1=catManager->AddCategoryL(*category);
	CleanupStack::PopAndDestroy(3,db);

	TLiwGenericParam param;
	param.SetNameAndValueL(KContentType,TLiwVariant(KCategory));
	iInList->AppendL(param);
	param.Reset();
	
	CLiwMap* categoryMap = CLiwDefaultMap::NewL();
	TBuf<5> catIdString1;
    catIdString1.Num(catid1,EDecimal);
    categoryMap->InsertL(KId,TLiwVariant(catIdString1));
	categoryMap->InsertL(KCategoryName,TLiwVariant(KOffice));
	param.SetNameAndValueL(KDataFields,TLiwVariant(categoryMap));    
	iInList->AppendL(param);
	categoryMap->DecRef();
	param.Reset();
	iLandmarkIf->ExecuteCmdL(KRemove,*iInList,*iOutList,0,0);
	ret |= CheckErrorCode (*iOutList,err);
 	if ( err != KErrNone )
		{
		iLog->Log( _L(" UpdateCategory1L on database failed with err...") );
		ret |= FAIL;
		}
	categoryMap->DecRef();

	iLog->Log( _L("End of RemoveCategoryL") );	

  	CleanupStack::PopAndDestroy(2,ServiceHandler);
    ReleaseLandmarkResources();    
	__UHEAP_MARKEND;
	
	return ret;
	}
	
// -----------------------------------------------------------------------------
// CTLmCategoryTests::RemoveCategoryL
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CTLmCategoryTests::RemoveCategoryPosL	( CStifItemParser& /*aItem */ )
	{
	_LIT( KExample, "RemoveCategoryPosL" );
	_LIT(KOffice,"NokiaUpdate");
	iLog->Log( KExample );
	TInt32 err;
	TInt ret = 0;
	TPosLmItemId catid1;

	__UHEAP_MARK;
	CLiwServiceHandler* ServiceHandler;
	
	CreateInterfaceL(ServiceHandler,iLandmarkIf);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*iLandmarkIf);
	
    iInList = &(ServiceHandler->InParamListL());
    iOutList = &(ServiceHandler->OutParamListL());

	ResetParams();

	
 	/*Preconditions*/
	CPosLandmarkDatabase* db = CPosLandmarkDatabase::OpenL(KDefaultDatabase);
	CleanupStack::PushL(db);
	ExecuteAndDeleteLD(db->InitializeL());
	CPosLmCategoryManager* catManager= CPosLmCategoryManager::NewL(*db);
	CleanupStack::PushL(catManager);
	CPosLandmarkCategory* category = CPosLandmarkCategory::NewLC();
	category->SetCategoryNameL(KOffice);
	catid1=catManager->AddCategoryL(*category);
	CleanupStack::PopAndDestroy(3,db);

	TLiwGenericParam param;
	param.SetNameAndValueL(KNullDesC8,TLiwVariant(KCategory));
	iInList->AppendL(param);
	param.Reset();
	
	CLiwMap* categoryMap = CLiwDefaultMap::NewL();
	TBuf<5> catIdString1;
    catIdString1.Num(catid1,EDecimal);
    categoryMap->InsertL(KId,TLiwVariant(catIdString1));
	categoryMap->InsertL(KCategoryName,TLiwVariant(KOffice));
	param.SetNameAndValueL(KNullDesC8,TLiwVariant(categoryMap));    
	iInList->AppendL(param);
	categoryMap->DecRef();
	param.Reset();
	iLandmarkIf->ExecuteCmdL(KRemove,*iInList,*iOutList,0,0);
	ret |= CheckErrorCode (*iOutList,err);
 	if ( err != KErrNone )
		{
		iLog->Log( _L(" UpdateCategory1L on database failed with err...") );
		ret |= FAIL;
		}
	categoryMap->DecRef();

	iLog->Log( _L("End of RemoveCategoryL") );	

  	CleanupStack::PopAndDestroy(2,ServiceHandler);
    ReleaseLandmarkResources();    
	__UHEAP_MARKEND;
	
	return ret;
	}

// -----------------------------------------------------------------------------
// CTLmCategoryTests::RemoveCategory1L
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//
TInt CTLmCategoryTests::RemoveCategory1L	( CStifItemParser& /*aItem */ )
	{
	_LIT(KOffice1,"NokiaPrevious");
	_LIT(KOffice,"NokiaUpdate");
	TInt ret=0;
	TInt32 err;
	TPosLmItemId catid1,catid2;

	__UHEAP_MARK;
	CLiwServiceHandler* ServiceHandler;
	
	CreateInterfaceL(ServiceHandler,iLandmarkIf);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*iLandmarkIf);
	
    iInList = &(ServiceHandler->InParamListL());
    iOutList = &(ServiceHandler->OutParamListL());

	ResetParams();

	
 	/*Preconditions*/
	CPosLandmarkDatabase* db = CPosLandmarkDatabase::OpenL(KDefaultDatabase);
	CleanupStack::PushL(db);
	ExecuteAndDeleteLD(db->InitializeL());
	CPosLmCategoryManager* catManager= CPosLmCategoryManager::NewL(*db);
	CleanupStack::PushL(catManager);
	CPosLandmarkCategory* category = CPosLandmarkCategory::NewLC();
	category->SetCategoryNameL(KOffice);
	catid1=catManager->AddCategoryL(*category);
	CleanupStack::PopAndDestroy(3,db);

	HPosLmDatabaseInfo*	 dbInfo	=	HPosLmDatabaseInfo::NewLC(KOtherDatabase);
	iDatabaseManager-> CreateDatabaseL(*dbInfo);
	CleanupStack::PopAndDestroy(dbInfo);
	
	db = CPosLandmarkDatabase::OpenL(KOtherDatabase);
	CleanupStack::PushL(db);
	ExecuteAndDeleteLD(db->InitializeL());
	catManager= CPosLmCategoryManager::NewL(*db);
	CleanupStack::PushL(catManager);
	category = CPosLandmarkCategory::NewLC();
	category->SetCategoryNameL(KOffice1);
	catid2=catManager->AddCategoryL(*category);
	CleanupStack::PopAndDestroy(3,db);


	TLiwGenericParam param;
	param.SetNameAndValueL(KContentType,TLiwVariant(KCategory));
	iInList->AppendL(param);
	param.Reset();
	
	CLiwMap* categoryMap = CLiwDefaultMap::NewL();
	TBuf<5> catIdString1;
    catIdString1.Num(catid1,EDecimal);
    categoryMap->InsertL(KId,TLiwVariant(catIdString1));
	categoryMap->InsertL(KCategoryName,TLiwVariant(KOffice));
	param.SetNameAndValueL(KDataFields,TLiwVariant(categoryMap));    
	iInList->AppendL(param);
	categoryMap->DecRef();
	param.Reset();
	iLandmarkIf->ExecuteCmdL(KRemove,*iInList,*iOutList,0,0);
	ret |= CheckErrorCode (*iOutList,err);
 	if ( err != KErrNone )
		{
		iLog->Log( _L(" UpdateCategory1L on database failed with err...") );
		ret |= FAIL;
		}
	categoryMap->DecRef();
	ResetParams();
	
	param.SetNameAndValueL(KContentType,TLiwVariant(KCategory));    
	iInList->AppendL(param);
	param.Reset();
	categoryMap = CLiwDefaultMap::NewL();
	TBuf<5> catIdString2;
    catIdString2.Num(catid2,EDecimal);
    categoryMap->InsertL(KId,TLiwVariant(catIdString2));
	categoryMap->InsertL(KCategoryName,TLiwVariant(KOffice));
	categoryMap->InsertL(KDbUri,TLiwVariant(KOtherDatabase));
	param.SetNameAndValueL(KDataFields,TLiwVariant(categoryMap));    
	iInList->AppendL(param);
	categoryMap->DecRef();
	param.Reset();
	iLandmarkIf->ExecuteCmdL(KRemove,*iInList,*iOutList,0,0);
	ret |= CheckErrorCode (*iOutList,err);
 	if ( err != KErrNone )
		{
		iLog->Log( _L(" UpdateCategory1L on database failed with err...") );
		ret |= FAIL;
		}
	categoryMap->DecRef();
	
	iLog->Log( _L("End of RemoveCategoryL") );	

  	CleanupStack::PopAndDestroy(2,ServiceHandler);
    ReleaseLandmarkResources();    
	__UHEAP_MARKEND;
	
	return ret;
	}	


// -----------------------------------------------------------------------------
// CTLmCategoryTests::CancelAsyncTest1
// Example test method function.
// (other items were commented in a header).
// -----------------------------------------------------------------------------
//		
TInt CTLmCategoryTests::CancelAsyncTest1	( CStifItemParser& /*aItem */ )
	{
	_LIT( KExample, "CancelAsyncTest1" );
	iLog->Log( KExample );
	iTestID = ETEST3;
	iResult = 0;

	TInt32 err;
	TInt ret = 0;

	__UHEAP_MARK;
	CLiwServiceHandler* ServiceHandler;
	
	CreateInterfaceL(ServiceHandler,iLandmarkIf);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*iLandmarkIf);
	
    iInList = &(ServiceHandler->InParamListL());
    iOutList = &(ServiceHandler->OutParamListL());

	ResetParams();

 	/*Preconditions*/
	CPosLandmarkDatabase* db = CPosLandmarkDatabase::OpenL(KDefaultDatabase);
	CleanupStack::PushL(db);
	ExecuteAndDeleteLD(db->InitializeL());
	CPosLmCategoryManager* catManager= CPosLmCategoryManager::NewL(*db);
	CleanupStack::PushL(catManager);
	CreateCategoriesL(catManager);
	CleanupStack::PopAndDestroy(2,db);

	TLiwGenericParam param;
    param.SetNameAndValueL(KContentType,TLiwVariant(KCategory));    
    iInList->AppendL(param);
    param.Reset();
    
    CLiwMap* categoryMap = CLiwDefaultMap::NewL();
    categoryMap->InsertL(KCategoryName,TLiwVariant(KCatSearchString));
    param.SetNameAndValueL(KFilter,TLiwVariant(categoryMap));    
    iInList->AppendL(param);
    categoryMap->DecRef();
    param.Reset();
    
    iLandmarkIf->ExecuteCmdL(KGetList,*iInList,*iOutList,KLiwOptASyncronous,this);
 	ret |= CheckErrorCode (*iOutList,err);
 	if ( err != KErrNone )
		{
		iLog->Log( _L(" Getlist on database failed wiht err...") );
		ret |= FAIL;
		}   

	TInt Index = -1;
	const TLiwGenericParam* cparam = iOutList->FindFirst(Index,KReturnValue);
	if ( cparam )
		{
		iLog->Log( _L("Database iterator found in output ArgList") );
		ret |= FAIL;
		}

	Index = 0;
	TInt32 tid;
	cparam = iOutList->FindFirst(Index,KTransactionId);
	if ( !cparam )
		{
		iLog->Log( _L("TransactionID not found in output ArgList") );
		ret |= FAIL;
		}
	else
		{
		tid = cparam->Value().AsTInt32();
		ResetParams();

	    param.SetNameAndValueL(KContentType,TLiwVariant(KCategory));    
	    iInList->AppendL(param);
	    param.Reset();
	
		iInList->AppendL(TLiwGenericParam(KTransactionId,TLiwVariant(TInt32(tid))));
	    iLandmarkIf->ExecuteCmdL(KCancel,*iInList,*iOutList,KLiwOptCancel);
	 	ret |= CheckErrorCode (*iOutList,err);
	 	if ( err != KErrNone )
			{
			iLog->Log( _L(" Getlist on database failed wiht err...") );
			ret |= FAIL;
			}   
	
		iLog->Log( _L("End of CancelAsyncTest1") );	
		ret |= iResult;
		}

  	CleanupStack::PopAndDestroy(2,ServiceHandler);
    ReleaseLandmarkResources();    
	__UHEAP_MARKEND;
	
	return ret;
	}

void CTLmCategoryTests::CreateInterfaceL(CLiwServiceHandler*& aHandler,
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

    InParamList->AppendL(TLiwGenericParam(KDbUri,TLiwVariant(KDefaultDatabase)));
	  
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
