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
#include <Stiftestinterface.h>
#include <epos_cposlandmarkparser.h> 
#include <epos_cposlandmarkencoder.h>
#include <lbsposition.h> 
#include <EPos_CPosLmTextCriteria.h>
#include <f32file.h>
#include <epos_cposlandmarkdatabase.h>
#include <epos_cposlmitemiterator.h> 
#include <epos_cposlandmark.h> 
#include "clandmarkfilter.h"
#include "CLandmarkAsyncTests.h"
#include "landmarkservice.h"
#include "Clmlandmarkstest.h"

_LIT(KLmName1, "lm1");
_LIT(KLmName2, "lm2");
_LIT(KLmName3, "lm3");
_LIT(KLmSearchString, "lm*");


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CClmlandmarkstest::Delete
// Delete here all resources allocated and opened from test methods. 
// Called from destructor. 
// -----------------------------------------------------------------------------
//
void CClmlandmarkstest::Delete() 
    {

    }

// -----------------------------------------------------------------------------
// CClmlandmarkstest::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CClmlandmarkstest::RunMethodL( 
    CStifItemParser& aItem ) 
    {
    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        //ENTRY( "Example", CClmlandmarkstest::ExampleL ),
				ENTRY( "AddLandmark", CClmlandmarkstest::AddLandmarkL ),
				ENTRY( "UpdateLandmark", CClmlandmarkstest::UpdateLandmarkL ),
				ENTRY( "RemoveLandmark", CClmlandmarkstest::RemoveLandmarkL ),
				ENTRY( "ImportLandmark", CClmlandmarkstest::ImportLandmarkL ),
				ENTRY( "ExportLandmark", CClmlandmarkstest::ExportLandmarkL ),
				ENTRY( "getlistasynctest1",    	CClmlandmarkstest::GetlistAsyncTest1 ),
				ENTRY( "getlistasynctest2",    	CClmlandmarkstest::GetlistAsyncTest2 ),
		        ENTRY( "landmarkgetlistsync", 	CClmlandmarkstest::LandmarkGetlistSync),
		        ENTRY( "landmarkgetlistGTK", 	CClmlandmarkstest::LandmarkGetlistGtk),
        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );
    }


TInt CClmlandmarkstest::AddLandmarkL( CStifItemParser& /*aItem*/ )
    {
	_LIT(KName,"Mainland China");    		
	_LIT(KDescription,"Extremely good chinese food");
		
	TLocality pos;
	pos.SetCoordinate(45.1122,34.0099);

	CPosLandmark* lm = CPosLandmark::NewLC();
	lm->SetLandmarkNameL(KName);
	lm->SetLandmarkDescriptionL(KDescription);
	lm->SetPositionL(pos);

	CPosLandmarkDatabase* db = CPosLandmarkDatabase::OpenL();
	CleanupStack::PushL(db);
	ExecuteAndDeleteLD(db->InitializeL());
	RemoveAllLandmarks(db);

	CLandmarkService* service = CLandmarkService::NewL();
	CleanupStack::PushL(service);
	service->AddItemL(*lm);//Adds 2 landmarks with same fields..duplicate entries
	service->AddItemL(*lm);
			
	CleanupStack::PopAndDestroy(3,lm);

	return KErrNone;
    }
 
TInt CClmlandmarkstest::UpdateLandmarkL( CStifItemParser& /*aItem*/ )
	{
	_LIT(KName,"3QC");
	_LIT(KName1,"Mainland China");
	_LIT(KPhone1,"123456");
  _LIT(KPhone2,"987654");
  
	CPosLandmarkDatabase* db = CPosLandmarkDatabase::OpenL();
	CleanupStack::PushL(db);
	ExecuteAndDeleteLD(db->InitializeL());
	RemoveAllLandmarks(db);

	TPosLmItemId lmId;
	CPosLandmark* lm = CPosLandmark::NewLC();
	lm->SetLandmarkNameL(KName1);
	lm->SetPositionFieldL(EPositionFieldBuildingTelephone,KPhone1);
	lm->SetPositionFieldL(EPositionFieldBuildingTelephone,KPhone2);
	lmId = db->AddLandmarkL(*lm);

	lm = db->ReadLandmarkLC(lmId);
	TPositionFieldId fieldId = lm->FirstPositionFieldId();
	TPtrC value;
	lm->GetPositionField (fieldId, value);
	fieldId = lm->NextPositionFieldId (fieldId);
	if( EPositionFieldNone  != fieldId)
			lm->GetPositionField (fieldId, value); 
	lm->SetLandmarkNameL(KName);
	CLandmarkService* service = CLandmarkService::NewL();
	CleanupStack::PushL(service);
	service->UpdateItemL(*lm);
	CleanupStack::PopAndDestroy(2,lm);

	CleanupStack::PopAndDestroy(2,db);
	ReleaseLandmarkResources();
	return KErrNone;
	}

TInt CClmlandmarkstest::RemoveLandmarkL( CStifItemParser& /*aItem*/ )
    {		
	_LIT(KName1,"Mainland China");
	CPosLandmarkDatabase* db = CPosLandmarkDatabase::OpenL();
	CleanupStack::PushL(db);
	ExecuteAndDeleteLD(db->InitializeL());
	RemoveAllLandmarks(db);

	TPosLmItemId lmId;
	CPosLandmark* lm = CPosLandmark::NewLC();
	lm->SetLandmarkNameL(KName1);
	lmId = db->AddLandmarkL(*lm);

	CLandmarkService* service = CLandmarkService::NewL();
	CleanupStack::PushL(service);
	service->RemoveItemL(lmId,CLandmarkService::ELandmark);
	CleanupStack::PopAndDestroy();

	CleanupStack::PopAndDestroy(2,db);
	ReleaseLandmarkResources();
	return KErrNone;
    }

TInt CClmlandmarkstest::ImportLandmarkL( CStifItemParser& /*aItem*/ )
    {
	_LIT(KFilePath, "c:\\eposLm.lmx");
	_LIT8(KPosMimeType, "application/vnd.nokia.landmarkcollection+xml");
	_LIT(KName1,"Mainland China");
	_LIT(KName2,"Chung Wah");
	_LIT(KName3,"Aromas of China");

	CPosLandmarkDatabase* db = CPosLandmarkDatabase::OpenL();
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

	CPosLandmarkParser* parser = CPosLandmarkParser::NewL(KPosMimeType);
	CleanupStack::PushL(parser);
	parser->SetInputFileL(KFilePath);

	CLandmarkService* service = CLandmarkService::NewL();
	CleanupStack::PushL(service);
	service->ImportL(iterLm,*parser);
	delete iterLm;

	CleanupStack::PopAndDestroy(4,db);
	ReleaseLandmarkResources();			
	return KErrNone;
    }

TInt CClmlandmarkstest::ExportLandmarkL( CStifItemParser& /*aItem*/ )
    {
	_LIT(KFilePath, "c:\\eposLmTest.lmx");
	_LIT8(KPosMimeType, "application/vnd.nokia.landmarkcollection+xml");
	_LIT(KName1,"Mainland China");
	_LIT(KName2,"Chung Wah");
	_LIT(KName3,"Aromas of China");

	CPosLandmarkDatabase* db = CPosLandmarkDatabase::OpenL();
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

	CLandmarkService* service = CLandmarkService::NewL();
	CleanupStack::PushL(service);
	service->ExportL(*encoder,landmarks);


	CleanupStack::PopAndDestroy(6,db);
	ReleaseLandmarkResources();	
	return KErrNone;
    } 

TInt CClmlandmarkstest::GetlistAsyncTest1( CStifItemParser& /*aItem*/ )
	{
	TInt err;
	_LIT( KExample, "Landmarksgetlist Async test1" );
	iLog->Log( KExample );

	RemoveAllLandmarks(iDefaultLmHandle);

	CLandmarkAsyncTests* test = CLandmarkAsyncTests::NewL(CLandmarkAsyncTests::ETEST1);
	CleanupStack::PushL(test);

	TRAP(err,test->StartL());
	if ( !err )
		err = test->Result();

	CleanupStack::PopAndDestroy(test);

	RemoveAllLandmarks(iDefaultLmHandle);

	return err;
	}

TInt CClmlandmarkstest::GetlistAsyncTest2( CStifItemParser& /*aItem*/ )
    {
	TInt err;
	_LIT( KExample, "Landmarksgetlist Async test2" );
	iLog->Log( KExample );

	RemoveAllLandmarks(iDefaultLmHandle);

	CLandmarkAsyncTests* test = CLandmarkAsyncTests::NewL(CLandmarkAsyncTests::ETEST2);
	CleanupStack::PushL(test);

	TRAP(err,test->StartL());
	if ( !err )
		err = test->Result();

	CleanupStack::PopAndDestroy(test);

	RemoveAllLandmarks(iDefaultLmHandle);

	return err;
    }

TInt CClmlandmarkstest::LandmarkGetlistSync( CStifItemParser& /*aItem*/ )
	{
	_LIT( KExample, "Landmark Getlist Sync" );
	iLog->Log( KExample );

	TInt err=0;
	TInt ret=0;

	TPosLmSortPref SortPref(CPosLandmark::ELandmarkName,TPosLmSortPref:: EAscending);

		   
	TLocality pos;
	pos.SetCoordinate(45.1122,34.0099);
		
	RemoveAllLandmarks(iDefaultLmHandle);

	CLandmarkService *obj = CLandmarkService::NewL ();
	CleanupStack::PushL(obj);

	CPosLandmark* lm = CPosLandmark::NewLC ();
	lm->SetLandmarkNameL (KLmName1);
	lm->SetLandmarkDescriptionL (KLmName1);
	lm->SetPositionL(pos);

	TRAP(err,iDefaultLmHandle->AddLandmarkL (*lm));
	lm->SetLandmarkNameL (KLmName2);
	lm->SetLandmarkDescriptionL (KLmName2);
	lm->SetPositionL(pos);
	TRAP(err,iDefaultLmHandle->AddLandmarkL (*lm));

	lm->SetLandmarkNameL (KLmName3);
	lm->SetLandmarkDescriptionL (KLmName3);
	lm->SetPositionL(pos);
	TRAP(err,iDefaultLmHandle->AddLandmarkL (*lm));
	   
	CleanupStack::PopAndDestroy(lm);

	CLandmarkFilter* filter = CLandmarkFilter::NewLC(CLandmarkFilter::ELandmark);

	CPosLmTextCriteria* crit = CPosLmTextCriteria::NewLC();
	crit->SetTextL(KLmSearchString);
	crit->SetAttributesToSearch  ( CPosLandmark::ELandmarkName );

	filter->SetCriteria(crit);
	CleanupStack::Pop(crit);
	filter->SetLmSortPref(SortPref);
		   
	CPosLmItemIterator* iterator;
	TRAP (err,obj->GetListL (iterator,*filter));
	if ( !err && ret == KErrNone )
	{
		TPosLmItemId lmID;
		TInt count = 0;
		while ((lmID = iterator->NextL()) != KPosLmNullItemId)
		{
		    CPosLandmark* lm = iDefaultLmHandle->ReadLandmarkLC(lmID);
			TPtrC lmname;
			if ( !lm->GetLandmarkName(lmname) )
			{
				if ( lmname.Compare(KLmName1) || lmname.Compare(KLmName2) || lmname.Compare(KLmName3) )
					count++;
			}
			else
			{
				break;
			}
			
		    CleanupStack::PopAndDestroy(lm);
	    }
	    if ( count != 3 )
	    {
	    	iLog->Log( _L("added landmarks doesn't match with in getlist iterator..") );
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

RemoveAllLandmarks(iDefaultLmHandle);
   
return err;
}  


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
	
TInt CClmlandmarkstest::LandmarkGetlistGtk( CStifItemParser& /*aItem*/ )
	{
	_LIT( KExample, "Landmark GetlistGtk Sync" );
	iLog->Log( KExample );

	TInt err=0;
	TInt ret=0;

	TPosLmSortPref SortPref(CPosLandmark::ELandmarkName,TPosLmSortPref:: EAscending);

		   
	TLocality pos;
	pos.SetCoordinate(45.1122,34.0099);
		
	RemoveAllLandmarks(iDefaultLmHandle);

	CLandmarkService *obj = CLandmarkService::NewL ();
	CleanupStack::PushL(obj);

	CPosLandmark* lm = CPosLandmark::NewLC ();
	lm->SetLandmarkNameL (KLmName1);
	lm->SetLandmarkDescriptionL (KLmName1);
	lm->SetPositionL(pos);

	TRAP(err,iDefaultLmHandle->AddLandmarkL (*lm));
	lm->SetLandmarkNameL (KLmName2);
	lm->SetLandmarkDescriptionL (KLmName2);
	lm->SetPositionL(pos);
	TRAP(err,iDefaultLmHandle->AddLandmarkL (*lm));

	lm->SetLandmarkNameL (KLmName3);
	lm->SetLandmarkDescriptionL (KLmName3);
	lm->SetPositionL(pos);
	TRAP(err,iDefaultLmHandle->AddLandmarkL (*lm));
	   
	CleanupStack::PopAndDestroy(lm);

	CLandmarkFilter* filter = CLandmarkFilter::NewLC(CLandmarkFilter::ELandmark);

	CPosLmTextCriteria* crit = CPosLmTextCriteria::NewLC();
	crit->SetTextL(KLmSearchString);
	crit->SetAttributesToSearch  ( CPosLandmark::ELandmarkName );

	filter->SetCriteria(crit);
	filter->SetLmSortPref(SortPref);
		   
	CPosLmItemIterator* iterator;
	TRAP (err,obj->GetListL (iterator,*filter));
	
	landmark* new_node = NULL;
	landmark* cur_node = NULL;
	landmark* lm_head = NULL;
	const TInt NAME_MAX = 255;
	
	if ( !err && ret == KErrNone )
	{
		TPosLmItemId lmID;
		TInt count = 0;
		while ((lmID = iterator->NextL()) != KPosLmNullItemId)
		{	
			TRAPD(err,new_node = (landmark*) User::AllocL(sizeof(landmark)));
			User::LeaveIfError(err);    
	    	new_node->next = lm_head;
	    	lm_head = new_node;
	    	//CleanupStack::PushL(new_node);
	    	CPosLandmark* lm = iDefaultLmHandle->ReadLandmarkLC(lmID);
	    	TPtrC lmname;
	    	if ( !lm->GetLandmarkName(lmname) )
			{
				if ( lmname.Compare(KLmName1) || lmname.Compare(KLmName2) || lmname.Compare(KLmName3) )
					count++;
				
				new_node->name = HBufC::NewL(NAME_MAX);
				(new_node->name->Des()).Copy(lmname);
			}
			
	    	TPtrC desc;
	    	if ( !lm->GetLandmarkName(desc) )
			{
				new_node->desc = HBufC::NewL(NAME_MAX);
				(new_node->desc->Des()).Copy(desc);		    
			}
	    	
			CleanupStack::PopAndDestroy(lm);
			//CleanupStack::Pop(new_node);
	    }
	    if ( count != 3 )
	    {
	    	iLog->Log( _L("added landmarks doesn't match with in getlist iterator..") );
	    	err = 1;
	    }
	}
	else
	{
	CleanupStack::PopAndDestroy(3,obj);	   	
	return err;	   	
	}

cur_node = lm_head;
	while(cur_node)
		{
		lm_head = cur_node->next;
		User::Free(cur_node->name);
		User::Free(cur_node->desc);
		User::Free(cur_node);
		cur_node = lm_head;
		}
delete iterator;

CleanupStack::PopAndDestroy(3,obj);

RemoveAllLandmarks(iDefaultLmHandle);
   
return err;
} 
// -----------------------------------------------------------------------------
// CTLmAsyncTest::RemoveAllLandmarks
// Helper method to remove all landmarks for preconditional tests.
// -----------------------------------------------------------------------------
//     

void CClmlandmarkstest::RemoveAllLandmarks (CPosLandmarkDatabase* aLandmarkHandle)
	{
		ExecuteAndDeleteLD(aLandmarkHandle->RemoveAllLandmarksL());
	}  


// ========================== OTHER EXPORTED FUNCTIONS =========================
// None

//  End of File
