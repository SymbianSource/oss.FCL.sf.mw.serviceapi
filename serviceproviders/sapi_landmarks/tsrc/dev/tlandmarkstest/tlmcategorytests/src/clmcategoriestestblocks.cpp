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
#include <StifTestInterface.h>
#include <EPos_CPosLmTextCriteria.h>
#include <lbsposition.h> 
#include <EPos_CPosLmItemIterator.h> 
#include <EPos_CPosLmCategoryManager.h> 
#include <EPos_CPosLandmarkDatabase.h> 
#include "clmcategoriestest.h"
#include "landmarkservice.h"
#include "clandmarkfilter.h"


// CONSTANTS
_LIT(KCatName1, "lc1");
_LIT(KCatName2, "lc2");
_LIT(KCatName3, "lc3");
_LIT(KCatName4, "category1");
_LIT(KCatName5, "category2");
_LIT(KCatName6, "category3");

_LIT(KCatSearchString, "lc*");

// -----------------------------------------------------------------------------
// CTLmAsyncTest::HandleLandmarkItemsL
// MLmObserver observer callback method for async getlist of landmarks request.
// -----------------------------------------------------------------------------
void CClmcategoriestest::HandleLandmarkItemsL( CPosLmItemIterator* /*aIterator*/,
												TInt32 /*aTransactionId*/, 
												TInt /*aError*/, const TDesC& /*aDatabaseUri*/)
{
	;
}

// -----------------------------------------------------------------------------
// CTLmAsyncTest::HandleCategoryItemsL
// MLmObserver observer callback method for async getlist of categories request.
// -----------------------------------------------------------------------------
//
void CClmcategoriestest::HandleCategoryItemsL(  CPosLmItemIterator* aIterator,
												TInt32 /*aTransactionId*/, 
												TInt /*aError*/, const TDesC& /*aDatabaseUri*/)
	{
	TPosLmItemId catID;
	TInt count = 0;
	switch (iTestCaseId)
		{
		case ECategoryGetlist1:
			while ((catID = aIterator->NextL()) != KPosLmNullItemId)
				{
				CPosLandmarkCategory* cat = iDefaultCategoryHandle->ReadCategoryLC(catID);
				TPtrC lcname;
				if ( !cat-> GetCategoryName (lcname) )
					{
					if ( lcname.Compare(KCatName1) || lcname.Compare(KCatName2) || lcname.Compare(KCatName3) )
					count++;
					}
				else
					{
					break;
					}
				CleanupStack::PopAndDestroy(cat);
				}
			if ( count != 3 )
				{
				iLog->Log( _L("added categories doesn't match with in getlist iterator..") );
				iResult = 1;
				}
		break;

		case ECategoryGetlist2:
			while ((catID = aIterator->NextL()) != KPosLmNullItemId)
				{
				CPosLandmarkCategory* cat = iDefaultCategoryHandle->ReadCategoryLC(catID);
				TPtrC lcname;
				if ( !cat-> GetCategoryName (lcname) )
					{
					if ( !lcname.Compare(KCatName1) || !lcname.Compare(KCatName2) || !lcname.Compare(KCatName3) )
						count++;
					if ( !lcname.Compare(KCatName4) || !lcname.Compare(KCatName5) || !lcname.Compare(KCatName6) )
						count++;					
					}
					else
					{
						break;
					}
				CleanupStack::PopAndDestroy(cat);
				}
			if ( count != 6 )
				{
				iLog->Log( _L("added categories doesn't match with in getlist iterator..") );
				iResult = 1;
				}
		break;

		default:
			iResult = 1;
		}

	delete aIterator;
	CActiveScheduler::Stop();	
	}


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CClmcategoriestest::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CClmcategoriestest::Delete() 
    {
    }

// -----------------------------------------------------------------------------
// CClmcategoriestest::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CClmcategoriestest::RunMethodL( 
    CStifItemParser& aItem ) 
    {
    static TStifFunctionInfo const KFunctions[] =
        {  
        ENTRY( "getlistasynctest1", 		CClmcategoriestest::GetlistAsyncTest1),
        ENTRY( "getlistasynctest2", 		CClmcategoriestest::GetlistAsyncTest2),
        ENTRY( "categorygetlistsync", 	CClmcategoriestest::CategoryGetlistSync),
        ENTRY( "AddCategory",    CClmcategoriestest::AddCategoryL ),
        ENTRY( "UpdateCategory", CClmcategoriestest::UpdateCategoryL),
        ENTRY( "RemoveCategory" ,  CClmcategoriestest :: RemoveCategoryL),
        ENTRY("LinkCategory", CClmcategoriestest :: LinkCategoryL ),
        ENTRY("UnLinkCategory", CClmcategoriestest :: UnLinkCategoryL ),

        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );
    }


TInt CClmcategoriestest::AddCategoryL( CStifItemParser& /*aItem*/ )
    {
	_LIT(KOffice,"Nokia");

	CPosLandmarkDatabase* db = CPosLandmarkDatabase::OpenL();
	CleanupStack::PushL(db);
	ExecuteAndDeleteLD(db->InitializeL());
	CPosLmCategoryManager* catManager= CPosLmCategoryManager::NewL(*db);
	CleanupStack::PushL(catManager);
	RemoveAllCategories(catManager);

	CPosLandmarkCategory* category = CPosLandmarkCategory::NewLC();
	category->SetCategoryNameL(KOffice);
	CLandmarkService* service = CLandmarkService::NewL();
	CleanupStack::PushL(service);
	service->AddItemL(*category);
	CleanupStack::PopAndDestroy(4,db);
	return KErrNone;
    }
 
TInt CClmcategoriestest::UpdateCategoryL( CStifItemParser& /*aItem*/ )
    {
	_LIT(KOffice1,"NokiaPrevious");
	_LIT(KOffice,"NokiaUpdate");
	CPosLandmarkDatabase* db = CPosLandmarkDatabase::OpenL();
	CleanupStack::PushL(db);
	ExecuteAndDeleteLD(db->InitializeL());


	CPosLmCategoryManager* catManager= CPosLmCategoryManager::NewL(*db);
	CleanupStack::PushL(catManager);
	RemoveAllCategories(catManager);

	TPosLmItemId catId;
	CPosLandmarkCategory* category = CPosLandmarkCategory::NewLC();
	category->SetCategoryNameL(KOffice1);
	catId=catManager->AddCategoryL(*category);

	category = catManager->ReadCategoryLC(catId);
	category->SetCategoryNameL(KOffice);
	CLandmarkService* service = CLandmarkService::NewL();
	CleanupStack::PushL(service);
	service->UpdateItemL(*category);
	CleanupStack::PopAndDestroy(2,category);
	CleanupStack::PopAndDestroy(3,db);
	ReleaseLandmarkResources();
	return KErrNone;
    }

TInt CClmcategoriestest::RemoveCategoryL( CStifItemParser& /*aItem*/ )
    {
	_LIT(KOffice1,"NokiaPrevious");
	CPosLandmarkDatabase* db = CPosLandmarkDatabase::OpenL();
	CleanupStack::PushL(db);
	ExecuteAndDeleteLD(db->InitializeL());


	CPosLmCategoryManager* catManager= CPosLmCategoryManager::NewL(*db);
	CleanupStack::PushL(catManager);
	RemoveAllCategories(catManager);
		
	TPosLmItemId catId;
	CPosLandmarkCategory* category = CPosLandmarkCategory::NewLC();
	category->SetCategoryNameL(KOffice1);
	catId=catManager->AddCategoryL(*category);

	//CPosLmItemIterator* iter = catManager->CategoryIteratorL();
	//CleanupStack::PushL(iter);

	CLandmarkService* service = CLandmarkService::NewL();
	CleanupStack::PushL(service);

	//	while ((catId = iter->NextL()) != KPosLmNullItemId)
	//{
		service->RemoveItemL(catId,CLandmarkService::ECategory);
			
	//}
	CleanupStack::PopAndDestroy(4,db);
	ReleaseLandmarkResources();
	return KErrNone;
    }

TInt CClmcategoriestest::LinkCategoryL( CStifItemParser& /*aItem*/ )
    {
	_LIT(KOffice1,"NokiaPrevious");
	_LIT(KName1,"Mainland China");
	_LIT(KName2,"Chung Wah");
	_LIT(KName3,"Aromas of China");

	CPosLandmarkDatabase* db = CPosLandmarkDatabase::OpenL();
	CleanupStack::PushL(db);
	ExecuteAndDeleteLD(db->InitializeL());

	TPosLmItemId lmId;
	RArray<TPosLmItemId> landmarks;
	CleanupClosePushL(landmarks);

	CPosLandmark* lm = CPosLandmark::NewLC();
	lm->SetLandmarkNameL(KName1);
	lmId = db->AddLandmarkL(*lm);
	User::LeaveIfError(landmarks.Append(lmId));
	lm->SetLandmarkNameL(KName2);
	lmId = db->AddLandmarkL(*lm);
	User::LeaveIfError(landmarks.Append(lmId));
	lm->SetLandmarkNameL(KName3);
	lmId = db->AddLandmarkL(*lm);
	User::LeaveIfError(landmarks.Append(lmId));

	CPosLmCategoryManager* catManager= CPosLmCategoryManager::NewL(*db);
	CleanupStack::PushL(catManager);
	RemoveAllCategories(catManager);

	TPosLmItemId catId;
	CPosLandmarkCategory* category = CPosLandmarkCategory::NewLC();
	category->SetCategoryNameL(KOffice1);
	catId = catManager->AddCategoryL(*category);

	CLandmarkService* service = CLandmarkService::NewL();
	CleanupStack::PushL(service);
	service->LinkCategoryToLandmarksL(catId,landmarks);

	CleanupStack::PopAndDestroy(6,db);
	ReleaseLandmarkResources();

	return KErrNone;
    }

TInt CClmcategoriestest::UnLinkCategoryL( CStifItemParser& /*aItem*/ )
    {
	_LIT(KOffice1,"NokiaPrevious");
	_LIT(KName1,"Mainland China");
	_LIT(KName2,"Chung Wah");
	_LIT(KName3,"Aromas of China");

	CPosLandmarkDatabase* db = CPosLandmarkDatabase::OpenL();
	CleanupStack::PushL(db);
	ExecuteAndDeleteLD(db->InitializeL());

	TPosLmItemId lmId;
	RArray<TPosLmItemId> landmarks;
	CleanupClosePushL(landmarks);

	CPosLandmark* lm = CPosLandmark::NewLC();
	lm->SetLandmarkNameL(KName1);
	lmId = db->AddLandmarkL(*lm);
	User::LeaveIfError(landmarks.Append(lmId));
	lm->SetLandmarkNameL(KName2);
	lmId = db->AddLandmarkL(*lm);
	User::LeaveIfError(landmarks.Append(lmId));
	lm->SetLandmarkNameL(KName3);
	lmId = db->AddLandmarkL(*lm);
	User::LeaveIfError(landmarks.Append(lmId));
				
	CPosLmCategoryManager* catManager= CPosLmCategoryManager::NewL(*db);
	CleanupStack::PushL(catManager);
	RemoveAllCategories(catManager);

	TPosLmItemId catId;
	CPosLandmarkCategory* category = CPosLandmarkCategory::NewLC();
	category->SetCategoryNameL(KOffice1);
	catId = catManager->AddCategoryL(*category);
	ExecuteAndDeleteLD(catManager->AddCategoryToLandmarksL(catId,landmarks));

	CLandmarkService* service = CLandmarkService::NewL();
	CleanupStack::PushL(service);
	service->UnlinkCategoryToLandmarksL(catId,landmarks);

	CleanupStack::PopAndDestroy(6,db);
	ReleaseLandmarkResources();
	return KErrNone;
    }     

TInt CClmcategoriestest::GetlistAsyncTest1( CStifItemParser& /*aItem*/ )
    {

	_LIT( KExample, "GetlistAsyncTest1 Async" );
	iLog->Log( KExample );

	TInt err=0;   
	iTestCaseId = ECategoryGetlist1;
	CPosLmCategoryManager::TCategorySortPref SortPref(CPosLmCategoryManager::ECategorySortOrderNone);
	
	iTestCaseId = ECategoryGetlist1;
		
	RemoveAllCategories(iDefaultCategoryHandle);
	CreateCategories ();
	
	CLandmarkService *obj = CLandmarkService::NewL ();
	CleanupStack::PushL(obj);
	obj->RegisterObserver(this);

	CLandmarkFilter* filter = CLandmarkFilter::NewLC(CLandmarkFilter::ECategory);
	CPosLmCatNameCriteria* crit = CPosLmCatNameCriteria ::NewLC();
	crit->SetSearchPatternL (KCatSearchString);
	filter->SetCriteria(crit);
	CleanupStack::Pop(crit);
	filter->SetCatSortPref(SortPref);
  TInt32 tranId = 0;
	TRAP (err,obj->GetListL (tranId,*filter));
	if ( !err )
		CActiveScheduler::Start();
	else
		{
		CleanupStack::PopAndDestroy(2,obj);	   	
		return err;	   	
		}
	User::After(5000);
	CleanupStack::PopAndDestroy(2,obj);

	RemoveAllCategories(iDefaultCategoryHandle);
	   
	return iResult;
    }

TInt CClmcategoriestest::GetlistAsyncTest2( CStifItemParser& /*aItem*/ )
    {
	_LIT( KExample, "GetlistAsyncTest2" );
	iLog->Log( KExample );
	
	TInt err=0; 
	iTestCaseId = ECategoryGetlist2;

	CPosLmCategoryManager::TCategorySortPref SortPref(CPosLmCategoryManager::ECategorySortOrderNone);
	
	RemoveAllCategories(iDefaultCategoryHandle);
	CreateCategories ();

	CLandmarkService *obj = CLandmarkService::NewL ();
	CleanupStack::PushL(obj);
	obj->RegisterObserver(this);

	CPosLmCatNameCriteria* crit = CPosLmCatNameCriteria ::NewLC();
	crit->SetSearchPatternL (KCatSearchString);

	CLandmarkFilter* filter = CLandmarkFilter::NewLC(CLandmarkFilter::ECategory);
//	filter->SetCriteria(crit);
	filter->SetCatSortPref(SortPref);
  TInt32 tranId = 0;
	TRAP (err,obj->GetListL (tranId,*filter));
	if ( !err )
		CActiveScheduler::Start();
	else
		{
		CleanupStack::PopAndDestroy(3,obj);	   	
		return err;	   	
		}

	CleanupStack::PopAndDestroy(3,obj);

	RemoveAllCategories(iDefaultCategoryHandle);
	   
	return iResult;
    }


// -----------------------------------------------------------------------------
// CClmcategoriestest::CategoryGetlist
// Test method for testing syncronous implimentation of getlist categories.
// -----------------------------------------------------------------------------
//
TInt CClmcategoriestest::CategoryGetlistSync( CStifItemParser& /*aItem*/ )
    {
	_LIT( KExample, "CategoryGetlist Sync" );
	iLog->Log( KExample );

	TInt err=0;
	TInt ret=0;

	CPosLmCategoryManager::TCategorySortPref SortPref(CPosLmCategoryManager::ECategorySortOrderNone);
	RemoveAllCategories(iDefaultCategoryHandle);

	CLandmarkService *obj = CLandmarkService::NewL ();
	CleanupStack::PushL(obj);

	CPosLandmarkCategory * lc = CPosLandmarkCategory::NewLC ();

	lc->SetCategoryNameL (KCatName1);
	TRAP(err,iDefaultCategoryHandle->AddCategoryL (*lc));

	lc->SetCategoryNameL (KCatName2);
	TRAP(err,iDefaultCategoryHandle->AddCategoryL (*lc));

	lc->SetCategoryNameL (KCatName3);
	TRAP(err,iDefaultCategoryHandle->AddCategoryL (*lc));

	CleanupStack::PopAndDestroy(lc);


	CLandmarkFilter* filter = CLandmarkFilter::NewLC(CLandmarkFilter::ECategory);
	CPosLmCatNameCriteria* crit = CPosLmCatNameCriteria ::NewLC();
	crit->SetSearchPatternL (KCatSearchString);
	filter->SetCriteria(crit);
	CleanupStack::Pop(crit);
	filter->SetCatSortPref(SortPref);

	CPosLmItemIterator* iterator;
	TRAP (err, obj->GetListL (iterator,*filter) );
	if ( !err && ret == KErrNone )
		{
		TPosLmItemId catID;
		TInt count = 0;
		while ((catID = iterator->NextL()) != KPosLmNullItemId)
			{
			CPosLandmarkCategory* cat = iDefaultCategoryHandle->ReadCategoryLC(catID);
			TPtrC lcname;
			if ( !cat-> GetCategoryName (lcname) )
				{
				if ( lcname.Compare(KCatName1) || lcname.Compare(KCatName2) || lcname.Compare(KCatName3) )
					count++;
				}
			else
				{
				break;
				}
			CleanupStack::PopAndDestroy(cat);
			}
		if ( 3 != count )
			{
			iLog->Log( _L("added categories doesn't match with in getlist iterator..") );
			err = 1;
			}
		}
	else
		{
		CleanupStack::PopAndDestroy(2,obj);	   	
		return err;	   	
		}

	delete iterator;
	CleanupStack::PopAndDestroy(2,obj);

	RemoveAllCategories(iDefaultCategoryHandle);
	return err;
    }
// -----------------------------------------------------------------------------
// CTLmAsyncTest::CreateCategories
// Helper method to add categories to a default database.
// -----------------------------------------------------------------------------
// 
void CClmcategoriestest::CreateCategories	()
	{
	CPosLandmarkCategory * lc = CPosLandmarkCategory::NewLC ();

	lc->SetCategoryNameL (KCatName1);
	iDefaultCategoryHandle->AddCategoryL (*lc);

	lc->SetCategoryNameL (KCatName2);
	iDefaultCategoryHandle->AddCategoryL (*lc);

	lc->SetCategoryNameL (KCatName3);
	iDefaultCategoryHandle->AddCategoryL (*lc);

	lc->SetCategoryNameL (KCatName4);
	iDefaultCategoryHandle->AddCategoryL (*lc);

	lc->SetCategoryNameL (KCatName5);
	iDefaultCategoryHandle->AddCategoryL (*lc);

	lc->SetCategoryNameL (KCatName6);
	iDefaultCategoryHandle->AddCategoryL (*lc);

	CleanupStack::PopAndDestroy(lc);
	}
// -----------------------------------------------------------------------------
// CTLmAsyncTest::RemoveAllLandmarks
// Helper method to remove all categories for preconditional tests.
// -----------------------------------------------------------------------------
//  
void CClmcategoriestest::RemoveAllCategories	(CPosLmCategoryManager* aHandle)
	{
	TPosLmItemId catID;
	CPosLmItemIterator*iterator = aHandle->CategoryIteratorL();
	CleanupStack::PushL(iterator);
	
	while ((catID = iterator->NextL()) != KPosLmNullItemId)
		{
	    TRAP_IGNORE(ExecuteAndDeleteLD(aHandle->RemoveCategoryL( catID )));
		}
	CleanupStack::PopAndDestroy(iterator);
}
//  End of File
