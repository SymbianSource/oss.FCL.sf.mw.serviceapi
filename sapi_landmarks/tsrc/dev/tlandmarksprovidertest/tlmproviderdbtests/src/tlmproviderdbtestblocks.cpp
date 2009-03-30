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
#include <StifParser.h>
#include <Stiftestinterface.h>
#include <liwcommon.h>
#include <liwservicehandler.h>
#include <EPos_HPosLmDatabaseInfo.h> 
#include <EPos_CPosLmDatabaseManager.h> 
#include <epos_cposlandmarkdatabase.h>
#include <epos_landmarks.h>
#include <epos_cposlandmark.h>
#include <LiwCommon.h>
#include "tlmproviderdbtests.h"
#include "landmarkliwparams.hrh"

#define PASS	TInt(0)
#define FAIL	(!PASS)

_LIT(KDbInvalidUri1, "file:/c:invalid.ldb");
_LIT(KDbInvalidUri2, "z:invalid.ldb");
_LIT(KDbInvalidUri3, "c:invalid");
_LIT(KDbInvalidUri4, "c:\\invalid.ldb");
_LIT(KDbInvalidUri5, "e:invalid.ldb");
_LIT(KRemoteUnsupportedDbUri, "http://remote.ldb");
// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CTLmDbTests::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTLmDbTests::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "AddDatabase",    		CTLmDbTests::AddDatabase ),
        ENTRY( "DeleteDatabase", 		CTLmDbTests::DeleteDatabase),
        ENTRY( "AddExistingDatabase", 	CTLmDbTests::AddExistingDatabase),
        ENTRY( "AddInvalidDatabase", 	CTLmDbTests::AddInvalidDatabase),
        ENTRY( "AddRemoteDatabase", 	CTLmDbTests::AddRemoteDatabase), 
        ENTRY( "UpdateDatabase" ,  		CTLmDbTests::UpdateDatabase),
//        ENTRY( "SetActiveDb", 			CTLmDbTests::SetActiveDb ),
        ENTRY( "GetDbList", 			CTLmDbTests::GetDbList ),
        ENTRY( "AddDatabasePos",    		CTLmDbTests::AddDatabasePos ),
        ENTRY( "DeleteDatabasePos", 		CTLmDbTests::DeleteDatabasePos),
        ENTRY( "AddExistingDatabasePos", 	CTLmDbTests::AddExistingDatabasePos),
        ENTRY( "AddInvalidDatabasePos", 	CTLmDbTests::AddInvalidDatabasePos),
        ENTRY( "AddRemoteDatabasePos", 	CTLmDbTests::AddRemoteDatabasePos), 
        ENTRY( "UpdateDatabasePos" ,  		CTLmDbTests::UpdateDatabasePos),
        ENTRY( "GetDbListPos", 			CTLmDbTests::GetDbListPos )

        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CTLmDbTests::AddDatabase
// test method function.
// -----------------------------------------------------------------------------
//
TInt CTLmDbTests::AddDatabase( CStifItemParser& /*aItem*/ )
    {
	_LIT( KExample, "AddDatabase" );
	iLog->Log( KExample );

//	TInt ret = 0;
	TInt32 err=0;
/*	
	DeleteAllLocalDatabasesL();

	TLiwGenericParam content(KContentType,TLiwVariant(KDatabase));

	CLiwMap* dbinfo = CLiwDefaultMap::NewL();

	dbinfo->InsertL(KDbUri,TLiwVariant(_L("c:landmark1.ldb")));

	TLiwGenericParam db(KDataFields,TLiwVariant(dbinfo));

	iInList->AppendL(content);
	iInList->AppendL(db);

	iLandmarkIf->ExecuteCmdL(KAdd,*iInList,*iOutList);

	ret |= CheckErrorCode (*iOutList,err);
	if ( err )
		{
		iLog->Log( _L("Database Creation failed : %d"),err );
		ret |= FAIL;
		} 
		
	TRAPD (err1, iDatabaseManager->DatabaseExistsL(_L("c:landmark1.ldb")));
	if (err1)
		{
		iLog->Log( _L("Database haven't been created : %d"),err );
		ret |= FAIL;
		}
		
	dbinfo->DecRef();

	DeleteAllLocalDatabasesL();
	iLog->Log( _L("End of AddDatabase test" ));
*/
	return err;
    }
    
    // -----------------------------------------------------------------------------
// CTLmDbTests::AddDatabasePos
// test method function.
// -----------------------------------------------------------------------------
//
TInt CTLmDbTests::AddDatabasePos( CStifItemParser& /*aItem*/ )
    {
	_LIT( KExample, "AddDatabasePos" );
	iLog->Log( KExample );

//	TInt ret = 0;
	TInt32 err=0;
/*	
	DeleteAllLocalDatabasesL();

	TLiwGenericParam content(KNullDesC8,TLiwVariant(KDatabase));

	CLiwMap* dbinfo = CLiwDefaultMap::NewL();

	dbinfo->InsertL(KDbUri,TLiwVariant(_L("c:landmark1.ldb")));

	TLiwGenericParam db(KNullDesC8,TLiwVariant(dbinfo));

	iInList->AppendL(content);
	iInList->AppendL(db);

	iLandmarkIf->ExecuteCmdL(KAdd,*iInList,*iOutList);

	ret |= CheckErrorCode (*iOutList,err);
	if ( err )
		{
		iLog->Log( _L("Database Creation failed : %d"),err );
		ret |= FAIL;
		} 
		
	TRAPD (err1, iDatabaseManager->DatabaseExistsL(_L("c:landmark1.ldb")));
	if (err1)
		{
		iLog->Log( _L("Database haven't been created : %d"),err );
		ret |= FAIL;
		}
		
	dbinfo->DecRef();

	DeleteAllLocalDatabasesL();
	iLog->Log( _L("End of AddDatabase test" ));
*/
	return err;
    }
    
// -----------------------------------------------------------------------------
// CTLmDbTests::AddExistingDatabase
// test method function.
// -----------------------------------------------------------------------------
// 
TInt CTLmDbTests::AddExistingDatabase( CStifItemParser& /*aItem*/ )
    {
	_LIT( KExample, "AddExistingDatabase" );
	iLog->Log( KExample );

//	TInt32 err;
	TInt ret = 0;
/*
	DeleteAllLocalDatabasesL();

	HPosLmDatabaseInfo*	 dbInfo	=	HPosLmDatabaseInfo::NewLC(_L("c:landmark1.ldb"));
	iDatabaseManager-> CreateDatabaseL(*dbInfo);
	CleanupStack::PopAndDestroy(dbInfo);


	TLiwGenericParam content(KContentType,TLiwVariant(KDatabase));

	CLiwMap* dbinfo = CLiwDefaultMap::NewL();

	dbinfo->InsertL(KDbUri,TLiwVariant(_L("c:landmark1.ldb")));

	TLiwGenericParam db(KDataFields,TLiwVariant(dbinfo));

	iInList->AppendL(content);
	iInList->AppendL(db);

	iLandmarkIf->ExecuteCmdL(KAdd,*iInList,*iOutList);

	ret |= CheckErrorCode (*iOutList,err);
	if ( err )
		{
		iLog->Log( _L("Incorrect Error returned : %d"),err );
		ret |= FAIL;
		} 

	dbinfo->DecRef();

	DeleteAllLocalDatabasesL();
*/
	return ( ret );
    }   
    
// -----------------------------------------------------------------------------
// CTLmDbTests::AddExistingDatabase
// test method function.
// -----------------------------------------------------------------------------
// 
TInt CTLmDbTests::AddExistingDatabasePos( CStifItemParser& /*aItem*/ )
    {
	_LIT( KExample, "AddExistingDatabasePos" );
	iLog->Log( KExample );

//	TInt32 err;
	TInt ret = 0;
/*
	DeleteAllLocalDatabasesL();

	HPosLmDatabaseInfo*	 dbInfo	=	HPosLmDatabaseInfo::NewLC(_L("c:landmark1.ldb"));
	iDatabaseManager-> CreateDatabaseL(*dbInfo);
	CleanupStack::PopAndDestroy(dbInfo);


	TLiwGenericParam content(KNullDesC8,TLiwVariant(KDatabase));

	CLiwMap* dbinfo = CLiwDefaultMap::NewL();

	dbinfo->InsertL(KDbUri,TLiwVariant(_L("c:landmark1.ldb")));

	TLiwGenericParam db(KNullDesC8,TLiwVariant(dbinfo));

	iInList->AppendL(content);
	iInList->AppendL(db);

	iLandmarkIf->ExecuteCmdL(KAdd,*iInList,*iOutList);

	ret |= CheckErrorCode (*iOutList,err);
	if ( err )
		{
		iLog->Log( _L("Incorrect Error returned : %d"),err );
		ret |= FAIL;
		} 

	dbinfo->DecRef();

	DeleteAllLocalDatabasesL();
*/
	return ( ret );
    }   
    
// -----------------------------------------------------------------------------
// CTLmDbTests::AddInvalidDatabase
// test method function.
// -----------------------------------------------------------------------------
// 
TInt CTLmDbTests::AddInvalidDatabase( CStifItemParser& /*aItem*/ )
    {
	_LIT( KExample, "AddInvalidDatabase" );
	iLog->Log( KExample );
//	TInt32 err;
	TInt ret = PASS;
/*
	DeleteAllLocalDatabasesL();

	TLiwGenericParam content(KContentType,TLiwVariant(KDatabase));
	CLiwMap* dbinfo = CLiwDefaultMap::NewL();

	dbinfo->InsertL(KDbUri,TLiwVariant(KDbInvalidUri1));
	TLiwGenericParam db(KDataFields,TLiwVariant(dbinfo));
	ResetParams();
	iInList->AppendL(content);
	iInList->AppendL(db);
	iLandmarkIf->ExecuteCmdL(KAdd,*iInList,*iOutList);
	ret |= CheckErrorCode (*iOutList,err);
	if ( !err )
		{
		iLog->Log( _L("invalid uri1 failed : %d"),err );
		ret |= FAIL;
		}


	ResetParams();
	dbinfo->InsertL(KDbUri,TLiwVariant(KDbInvalidUri2));
	iInList->AppendL(content);
	iInList->AppendL(TLiwGenericParam(KDataFields,TLiwVariant(dbinfo)) );
	iLandmarkIf->ExecuteCmdL(KAdd,*iInList,*iOutList);
	ret |= CheckErrorCode (*iOutList,err);
	if ( err != SErrAccessDenied )
		{
		iLog->Log( _L("invalid uri2 failed : %d"),err );
		ret |= FAIL;
		}	


	ResetParams();
	dbinfo->InsertL(KDbUri,TLiwVariant(KDbInvalidUri3));
	iInList->AppendL(content);
	iInList->AppendL(TLiwGenericParam(KDataFields,TLiwVariant(dbinfo)) );
	iLandmarkIf->ExecuteCmdL(KAdd,*iInList,*iOutList);
	ret |= CheckErrorCode (*iOutList,err);
	if ( err != SErrBadArgumentType )
		{
		iLog->Log( _L("invalid uri3 failed : %d"),err );
		ret |= FAIL;
		}	


	ResetParams();
	dbinfo->InsertL(KDbUri,TLiwVariant(KDbInvalidUri4));
	iInList->AppendL(content);
	iInList->AppendL(TLiwGenericParam(KDataFields,TLiwVariant(dbinfo)) );
	iLandmarkIf->ExecuteCmdL(KAdd,*iInList,*iOutList);
	ret |= CheckErrorCode (*iOutList,err);
	if ( err != SErrBadArgumentType )
		{
		iLog->Log( _L("invalid uri4 failed : %d"),err );
		ret |= FAIL;
		}	



	DeleteAllLocalDatabasesL();
*/
	return ret;   
    }  
    
    // -----------------------------------------------------------------------------
// CTLmDbTests::AddInvalidDatabase
// test method function.
// -----------------------------------------------------------------------------
// 
TInt CTLmDbTests::AddInvalidDatabasePos( CStifItemParser& /*aItem*/ )
    {
	_LIT( KExample, "AddInvalidDatabasePos" );
	iLog->Log( KExample );
//	TInt32 err;
	TInt ret = PASS;
/*
	DeleteAllLocalDatabasesL();

	TLiwGenericParam content(KNullDesC8,TLiwVariant(KDatabase));
	CLiwMap* dbinfo = CLiwDefaultMap::NewL();

	dbinfo->InsertL(KDbUri,TLiwVariant(KDbInvalidUri1));
	TLiwGenericParam db(KNullDesC8,TLiwVariant(dbinfo));
	ResetParams();
	iInList->AppendL(content);
	iInList->AppendL(db);
	iLandmarkIf->ExecuteCmdL(KAdd,*iInList,*iOutList);
	ret |= CheckErrorCode (*iOutList,err);
	if ( !err )
		{
		iLog->Log( _L("invalid uri1 failed : %d"),err );
		ret |= FAIL;
		}


	ResetParams();
	dbinfo->InsertL(KDbUri,TLiwVariant(KDbInvalidUri2));
	iInList->AppendL(content);
	iInList->AppendL(TLiwGenericParam(KNullDesC8,TLiwVariant(dbinfo)) );
	iLandmarkIf->ExecuteCmdL(KAdd,*iInList,*iOutList);
	ret |= CheckErrorCode (*iOutList,err);
	if ( err != SErrAccessDenied )
		{
		iLog->Log( _L("invalid uri2 failed : %d"),err );
		ret |= FAIL;
		}	

    DeleteAllLocalDatabasesL();
*/
	return ret;   
    }   
     
// -----------------------------------------------------------------------------
// CTLmDbTests::AddRemoteDatabase
// test method function.
// -----------------------------------------------------------------------------
//
TInt CTLmDbTests::AddRemoteDatabase( CStifItemParser& /*aItem*/ )
    {
	_LIT( KExample, "AddRemoteDatabase" );
	iLog->Log( KExample );

	TInt ret=0;
//	TInt32 err;
/*
	DeleteAllLocalDatabasesL();

	TLiwGenericParam content(KContentType,TLiwVariant(KDatabase));
	CLiwMap* dbinfo = CLiwDefaultMap::NewL();

	dbinfo->InsertL(KDbUri,TLiwVariant(KRemoteUnsupportedDbUri));
	TLiwGenericParam db(KDataFields,TLiwVariant(dbinfo));
	ResetParams();
	iInList->AppendL(content);
	iInList->AppendL(db);
	iLandmarkIf->ExecuteCmdL(KAdd,*iInList,*iOutList);
	ret |= CheckErrorCode (*iOutList,err);
	if ( err != SErrServiceNotSupported )
		{
		iLog->Log( _L("invalid AddRemoteDatabase failed : %d"),err );
		ret |= FAIL;
		}   
	ResetParams();
*/
	return ret;
    }    
    
    // -----------------------------------------------------------------------------
// CTLmDbTests::AddRemoteDatabase
// test method function.
// -----------------------------------------------------------------------------
//
TInt CTLmDbTests::AddRemoteDatabasePos( CStifItemParser& /*aItem*/ )
    {
	_LIT( KExample, "AddRemoteDatabasePos" );
	iLog->Log( KExample );

	TInt ret=0;
//	TInt32 err;
/*
	DeleteAllLocalDatabasesL();

	TLiwGenericParam content(KNullDesC8,TLiwVariant(KDatabase));
	CLiwMap* dbinfo = CLiwDefaultMap::NewL();

	dbinfo->InsertL(KDbUri,TLiwVariant(KRemoteUnsupportedDbUri));
	TLiwGenericParam db(KNullDesC8,TLiwVariant(dbinfo));
	ResetParams();
	iInList->AppendL(content);
	iInList->AppendL(db);
	iLandmarkIf->ExecuteCmdL(KAdd,*iInList,*iOutList);
	ret |= CheckErrorCode (*iOutList,err);
	if ( err != SErrServiceNotSupported )
		{
		iLog->Log( _L("invalid AddRemoteDatabase failed : %d"),err );
		ret |= FAIL;
		}   
	ResetParams();
*/
	return ret;
    }     
               
// -----------------------------------------------------------------------------
// CTLmDbTests::DeleteDatabase
// test method function.
// -----------------------------------------------------------------------------
//
TInt CTLmDbTests ::DeleteDatabase(CStifItemParser& /*aItem*/)
	{
	_LIT(KDb1, "c:eposlm1.ldb");
	_LIT( KExample, "DeleteDatabase" );
	iLog->Log( KExample );

//	TInt32 err;
	TInt ret=0;
/*	DeleteAllLocalDatabasesL();

	HPosLmDatabaseInfo* info = HPosLmDatabaseInfo::NewL(KDb1);
	CleanupStack::PushL(info);
	iDatabaseManager->CreateDatabaseL (*info);
	CleanupStack::PopAndDestroy(info);

	TLiwGenericParam content(KContentType,TLiwVariant(KDatabase));
	CLiwMap* dbinfo = CLiwDefaultMap::NewL();

	dbinfo->InsertL(KDbUri,TLiwVariant(KDb1));
	TLiwGenericParam db(KDataFields,TLiwVariant(dbinfo));
	ResetParams();
	iInList->AppendL(content);
	iInList->AppendL(db);
	iLandmarkIf->ExecuteCmdL(KRemove,*iInList,*iOutList);
	ret |= CheckErrorCode (*iOutList,err);
	if ( err != KErrNone )
		{
		iLog->Log( _L("deletion of database failed : %d"),err );
		ret |= FAIL;
		}   
		ResetParams();

	DeleteAllLocalDatabasesL();   
*/
	return ret;
	}   
	
	// -----------------------------------------------------------------------------
// CTLmDbTests::DeleteDatabase
// test method function.
// -----------------------------------------------------------------------------
//
TInt CTLmDbTests ::DeleteDatabasePos(CStifItemParser& /*aItem*/)
	{
	_LIT(KDb1, "c:eposlm1.ldb");
	_LIT( KExample, "DeleteDatabase" );
	iLog->Log( KExample );

//	TInt32 err;
	TInt ret=0;
/*	DeleteAllLocalDatabasesL();

	HPosLmDatabaseInfo* info = HPosLmDatabaseInfo::NewL(KDb1);
	CleanupStack::PushL(info);
	iDatabaseManager->CreateDatabaseL (*info);
	CleanupStack::PopAndDestroy(info);

	TLiwGenericParam content(KNullDesC8,TLiwVariant(KDatabase));
	CLiwMap* dbinfo = CLiwDefaultMap::NewL();

	dbinfo->InsertL(KDbUri,TLiwVariant(KDb1));
	TLiwGenericParam db(KNullDesC8,TLiwVariant(dbinfo));
	ResetParams();
	iInList->AppendL(content);
	iInList->AppendL(db);
	iLandmarkIf->ExecuteCmdL(KRemove,*iInList,*iOutList);
	ret |= CheckErrorCode (*iOutList,err);
	if ( err != KErrNone )
		{
		iLog->Log( _L("deletion of database failed : %d"),err );
		ret |= FAIL;
		}   
		ResetParams();

	DeleteAllLocalDatabasesL();   
*/
	return ret;
	}   
	 
// -----------------------------------------------------------------------------
// CTLmDbTests::UpdateDatabase
// test method function.
// -----------------------------------------------------------------------------
//
TInt CTLmDbTests ::UpdateDatabase(CStifItemParser& /*aItem*/)
	{
	_LIT( KExample, "UpdateDatabase" );
	_LIT( KDatabaseUri, "C:landmark1.ldb");
	_LIT( KDatabaseName,"mylandmarkdb1");

	iLog->Log( KExample );

//	TInt32 err;
	TInt ret=PASS;
/*
	DeleteAllLocalDatabasesL();

	HPosLmDatabaseInfo*	 dbInfo	=	HPosLmDatabaseInfo::NewLC(KDatabaseUri);
	iDatabaseManager-> CreateDatabaseL(*dbInfo);
	CleanupStack::PopAndDestroy(dbInfo);

	TLiwGenericParam content(KContentType,TLiwVariant(KDatabase));
	CLiwMap* dbinfo = CLiwDefaultMap::NewL();

	dbinfo->InsertL(KDbUri,TLiwVariant(KDatabaseUri));
	dbinfo->InsertL(KDbName,TLiwVariant(KDatabaseName));
	TLiwGenericParam db(KDataFields,TLiwVariant(dbinfo));
	iInList->AppendL(content);
	iInList->AppendL(db);
	iLandmarkIf->ExecuteCmdL(KAdd,*iInList,*iOutList);
	ret |= CheckErrorCode (*iOutList,err);
	if ( err != KErrNone )
		{
		iLog->Log( _L("updation of database failed : %d"),err );
		ret |= FAIL;
		}   

	dbinfo->DecRef();

	if (!ret)
		{
		HPosLmDatabaseInfo* info = HPosLmDatabaseInfo::NewL(KDatabaseUri);
		CleanupStack::PushL(info);
		TRAPD(err1,iDatabaseManager->GetDatabaseInfoL (*info));
		if (!err1)
			{
			const TPosLmDatabaseSettings settings = info->Settings();
			TPtrC dbname = settings.DatabaseName();
			if ( !dbname.Compare( KDatabaseName ) )
				{
				iLog->Log( _L("Database updated correctly") );
				ret |= PASS;
				}
			else
				{
				iLog->Log( _L("Database not updated") );
				ret |= FAIL;					
				}
			}
		CleanupStack::PopAndDestroy(info);
		}
	else
		{
		iLog->Log( _L("Error updating database") );
		}

	DeleteAllLocalDatabasesL();
*/
	return ( ret );
	}    
	
	// -----------------------------------------------------------------------------
// CTLmDbTests::UpdateDatabase
// test method function.
// -----------------------------------------------------------------------------
//
TInt CTLmDbTests ::UpdateDatabasePos(CStifItemParser& /*aItem*/)
	{
	_LIT( KExample, "UpdateDatabasePos" );
	_LIT( KDatabaseUri, "C:landmark1.ldb");
	_LIT( KDatabaseName,"mylandmarkdb1");

	iLog->Log( KExample );

//	TInt32 err;
	TInt ret=PASS;
/*
	DeleteAllLocalDatabasesL();

	HPosLmDatabaseInfo*	 dbInfo	=	HPosLmDatabaseInfo::NewLC(KDatabaseUri);
	iDatabaseManager-> CreateDatabaseL(*dbInfo);
	CleanupStack::PopAndDestroy(dbInfo);

	TLiwGenericParam content(KNullDesC8,TLiwVariant(KDatabase));
	CLiwMap* dbinfo = CLiwDefaultMap::NewL();

	dbinfo->InsertL(KDbUri,TLiwVariant(KDatabaseUri));
	dbinfo->InsertL(KDbName,TLiwVariant(KDatabaseName));
	TLiwGenericParam db(KNullDesC8,TLiwVariant(dbinfo));
	iInList->AppendL(content);
	iInList->AppendL(db);
	iLandmarkIf->ExecuteCmdL(KAdd,*iInList,*iOutList);
	ret |= CheckErrorCode (*iOutList,err);
	if ( err != KErrNone )
		{
		iLog->Log( _L("updation of database failed : %d"),err );
		ret |= FAIL;
		}   

	dbinfo->DecRef();

	if (!ret)
		{
		HPosLmDatabaseInfo* info = HPosLmDatabaseInfo::NewL(KDatabaseUri);
		CleanupStack::PushL(info);
		TRAPD(err1,iDatabaseManager->GetDatabaseInfoL (*info));
		if (!err1)
			{
			const TPosLmDatabaseSettings settings = info->Settings();
			TPtrC dbname = settings.DatabaseName();
			if ( !dbname.Compare( KDatabaseName ) )
				{
				iLog->Log( _L("Database updated correctly") );
				ret |= PASS;
				}
			else
				{
				iLog->Log( _L("Database not updated") );
				ret |= FAIL;					
				}
			}
		CleanupStack::PopAndDestroy(info);
		}
	else
		{
		iLog->Log( _L("Error updating database") );
		}

	DeleteAllLocalDatabasesL();
*/
	return ( ret );
	}    
	
// -----------------------------------------------------------------------------
// CTLmDbTests::SetActiveDb
// test method function.
// -----------------------------------------------------------------------------
//

TInt CTLmDbTests ::SetActiveDb(CStifItemParser& /*aItem*/)
	{
	_LIT(KActiveDb1, "file://c:activelm1.ldb");
	_LIT(KActiveDb2, "file://c:activelm2.ldb");

	_LIT( KExample, "SetActiveDb" );
	iLog->Log( KExample );
//	TInt32 err;
	TInt ret=0;
/*
	DeleteAllLocalDatabasesL();
	HPosLmDatabaseInfo* info = HPosLmDatabaseInfo::NewL(KActiveDb1);
	CleanupStack::PushL(info);
	iDatabaseManager->CreateDatabaseL (*info);
	CleanupStack::PopAndDestroy(info);

	info = HPosLmDatabaseInfo::NewL(KActiveDb2);
	CleanupStack::PushL(info);
	iDatabaseManager->CreateDatabaseL (*info);		
	CleanupStack::PopAndDestroy(info);				


	TLiwGenericParam content(KContentType,TLiwVariant(KDatabase));
	CLiwMap* dbinfo = CLiwDefaultMap::NewL();

	dbinfo->InsertL(KDbUri,TLiwVariant(KActiveDb1));
	ResetParams();
	iInList->AppendL(content);
	iInList->AppendL(TLiwGenericParam(KDataFields,TLiwVariant(dbinfo)));
//	iLandmarkIf->ExecuteCmdL(KSetActive,*iInList,*iOutList);
	ret |= CheckErrorCode (*iOutList,err);
	if ( err != KErrNone )
		{
		iLog->Log( _L("Setting activedb1 failed") );
		ret |= FAIL;
		}   

	dbinfo->InsertL(KDbUri,TLiwVariant(KActiveDb2));
	ResetParams();
	iInList->AppendL(content);
	iInList->AppendL(TLiwGenericParam(KDataFields,TLiwVariant(dbinfo)));
//	iLandmarkIf->ExecuteCmdL(KSetActive,*iInList,*iOutList);
	ret |= CheckErrorCode (*iOutList,err);
	if ( err != KErrNone )
		{
		iLog->Log( _L("Setting activedb2 failed") );
		ret |= FAIL;
		}   
	ResetParams();
	dbinfo->DecRef();	
*/
	return ret;
	}    

// -----------------------------------------------------------------------------
// CTLmDbTests::GetDbList
// test method function.
// -----------------------------------------------------------------------------
//
TInt CTLmDbTests ::GetDbList(CStifItemParser& /*aItem*/)
	{
	_LIT(KDb1, "file://c:lmdb1.ldb");
	_LIT(KDb2, "file://c:lmdb2.ldb");
	_LIT(KDb3, "file://c:lmdb3.ldb");
	_LIT(KDb4, "file://c:lmdb4.ldb");

	__UHEAP_MARK;
	
	_LIT( KExample, "GetDbList" );
	iLog->Log( KExample );
	TInt32 err;
	TInt ret=0;
	
	DeleteAllLocalDatabasesL();

    CPosLandmarkDatabase* db = CPosLandmarkDatabase::OpenL();
    delete db;


	CLiwServiceHandler* ServiceHandler;
	CLiwGenericParamList* iInList,*iOutList;
	MLiwInterface* iLandmarkIf;
	
	CreateInterfaceL(ServiceHandler,iLandmarkIf);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*iLandmarkIf);
	
    iInList = &(ServiceHandler->InParamListL());
    iOutList = &(ServiceHandler->OutParamListL());

	iInList->Reset();
	iOutList->Reset();
	
	HPosLmDatabaseInfo* info = HPosLmDatabaseInfo::NewL(KDb1);
	CleanupStack::PushL(info);
	iDatabaseManager->CreateDatabaseL (*info);
	CleanupStack::PopAndDestroy(info);

	info = HPosLmDatabaseInfo::NewL(KDb2);
	CleanupStack::PushL(info);
	iDatabaseManager->CreateDatabaseL (*info);		
	CleanupStack::PopAndDestroy(info);				

	info = HPosLmDatabaseInfo::NewL(KDb3);
	CleanupStack::PushL(info);
	iDatabaseManager->CreateDatabaseL (*info);		
	CleanupStack::PopAndDestroy(info);				

	info = HPosLmDatabaseInfo::NewL(KDb4);
	CleanupStack::PushL(info);
	iDatabaseManager->CreateDatabaseL (*info);		
	CleanupStack::PopAndDestroy(info);				


	TLiwGenericParam content(KContentType,TLiwVariant(KDatabase));
	CLiwMap* dbinfo = CLiwDefaultMap::NewL();

	dbinfo->InsertL(KDbProtocol,TLiwVariant(_L("file")));
	iInList->AppendL(content);
	iInList->AppendL(TLiwGenericParam(KFilter,TLiwVariant(dbinfo)));
	iLandmarkIf->ExecuteCmdL(KGetList,*iInList,*iOutList);
	ret |= CheckErrorCode (*iOutList,err);
	if ( err != KErrNone )
		{
		iLog->Log( _L(" Getlist on database failed wiht err...") );
		ret |= FAIL;
		}   

	TInt Index = 0;
	const TLiwGenericParam* param = iOutList->FindFirst(Index,KReturnValue);
	if ( KErrNotFound == Index )
		{
		iLog->Log( _L("Database iterator not found in output ArgList") );
		ret |= FAIL;
		}
	CLiwIterable* dbiterator = param->Value().AsIterable();
	
	if ( !dbiterator )
		{
		iLog->Log( _L("Database iterator not set") );
		ret |= FAIL;
		}
	
	TLiwVariant item;
	while ( dbiterator->NextL(item) )	
		{
		const CLiwMap* db = item.AsMap();
		if (db)
			{
			TLiwVariant dburi;
			db->FindL(KDbUri,dburi);
			TPtrC URI = dburi.AsDes();
			iLog->Log( _L("Database URI: %s"), URI.Ptr());
			dburi.Reset();

			TLiwVariant drive;
			db->FindL(KDbDrive,drive);
			TPtrC drv = drive.AsDes();
			iLog->Log( _L("Drive: %s"), drv.Ptr());
			drive.Reset();

			TLiwVariant protocol;
			db->FindL(KDbProtocol,protocol);
			TPtrC pro = protocol.AsDes();
			iLog->Log( _L("Protocal: %s"), pro.Ptr());
			protocol.Reset();

			TLiwVariant sizev;
			db->FindL(KDbSize,sizev);
			TInt32 size;
			sizev.Get(size);
			iLog->Log( _L("Size: %d"), size);

			TLiwVariant activev;
			db->FindL(KDbActive,activev);
			TBool active;
			activev.Get(active);
			iLog->Log( _L("Active: %d"), active);
			}
		else
			{
			iLog->Log(_L(" ITEM NOT FOUND..."));
			}
		item.Reset();
		}
	
	dbiterator->DecRef();
	dbinfo->DecRef();	

   	CleanupStack::PopAndDestroy(2,ServiceHandler);
    ReleaseLandmarkResources();    
	__UHEAP_MARKEND;
	
	return ret;
	}    


// -----------------------------------------------------------------------------
// CTLmDbTests::GetDbList
// test method function.
// -----------------------------------------------------------------------------
//
TInt CTLmDbTests ::GetDbListPos(CStifItemParser& /*aItem*/)
	{
	_LIT(KDb1, "file://c:lmdb1.ldb");
	_LIT(KDb2, "file://c:lmdb2.ldb");
	_LIT(KDb3, "file://c:lmdb3.ldb");
	_LIT(KDb4, "file://c:lmdb4.ldb");

	_LIT( KExample, "GetDbList" );
	iLog->Log( KExample );
	TInt32 err;
	TInt ret=0;
	
	DeleteAllLocalDatabasesL();

	CLiwServiceHandler* ServiceHandler;
	CLiwGenericParamList* iInList,*iOutList;
	MLiwInterface* iLandmarkIf;
	
	CreateInterfaceL(ServiceHandler,iLandmarkIf);
	CleanupStack::PushL(ServiceHandler);
	CleanupClosePushL(*iLandmarkIf);
	
    iInList = &(ServiceHandler->InParamListL());
    iOutList = &(ServiceHandler->OutParamListL());

	iInList->Reset();
	iOutList->Reset();
	
	HPosLmDatabaseInfo* info = HPosLmDatabaseInfo::NewL(KDb1);
	CleanupStack::PushL(info);
	iDatabaseManager->CreateDatabaseL (*info);
	CleanupStack::PopAndDestroy(info);

	info = HPosLmDatabaseInfo::NewL(KDb2);
	CleanupStack::PushL(info);
	iDatabaseManager->CreateDatabaseL (*info);		
	CleanupStack::PopAndDestroy(info);				

	info = HPosLmDatabaseInfo::NewL(KDb3);
	CleanupStack::PushL(info);
	iDatabaseManager->CreateDatabaseL (*info);		
	CleanupStack::PopAndDestroy(info);				

	info = HPosLmDatabaseInfo::NewL(KDb4);
	CleanupStack::PushL(info);
	iDatabaseManager->CreateDatabaseL (*info);		
	CleanupStack::PopAndDestroy(info);				


	TLiwGenericParam content(KNullDesC8,TLiwVariant(KDatabase));
	CLiwMap* dbinfo = CLiwDefaultMap::NewL();

	dbinfo->InsertL(KDbProtocol,TLiwVariant(_L("file")));

	iInList->AppendL(content);
	iInList->AppendL(TLiwGenericParam(KNullDesC8,TLiwVariant(dbinfo)));
	iLandmarkIf->ExecuteCmdL(KGetList,*iInList,*iOutList);
	ret |= CheckErrorCode (*iOutList,err);
	if ( err != KErrNone )
		{
		iLog->Log( _L(" Getlist on database failed wiht err...") );
		ret |= FAIL;
		}   

	TInt Index = 0;
	const TLiwGenericParam* param = iOutList->FindFirst(Index,KReturnValue);
	if ( KErrNotFound == Index )
		{
		iLog->Log( _L("Database iterator not found in output ArgList") );
		ret |= FAIL;
		}
	CLiwIterable* dbiterator = param->Value().AsIterable();
	
	if ( !dbiterator )
		{
		iLog->Log( _L("Database iterator not set") );
		ret |= FAIL;
		}
	
	TLiwVariant item;
	while ( dbiterator->NextL(item) )	
		{
		const CLiwMap* db = item.AsMap();
		if (db)
			{
			TLiwVariant dburi;
			db->FindL(KDbUri,dburi);
			TPtrC URI = dburi.AsDes();
			iLog->Log( _L("Database URI: %s"), URI.Ptr());
			dburi.Reset();

			TLiwVariant drive;
			db->FindL(KDbDrive,drive);
			TPtrC drv = drive.AsDes();
			iLog->Log( _L("Drive: %s"), drv.Ptr());
			drive.Reset();

			TLiwVariant protocol;
			db->FindL(KDbProtocol,protocol);
			TPtrC pro = protocol.AsDes();
			iLog->Log( _L("Protocal: %s"), pro.Ptr());
			protocol.Reset();

			TLiwVariant media;
			db->FindL(KDbMedia,media);
			TInt32 mediatype;
			media.Get(mediatype);
			iLog->Log( _L("MediaType: %d"), mediatype);

			TLiwVariant sizev;
			db->FindL(KDbSize,sizev);
			TInt32 size;
			sizev.Get(size);
			iLog->Log( _L("Size: %d"), size);

			TLiwVariant activev;
			db->FindL(KDbActive,activev);
			TBool active;
			activev.Get(active);
			iLog->Log( _L("Active: %d"), active);
			}
		else
			{
			iLog->Log(_L(" ITEM NOT FOUND..."));
			}
		item.Reset();
		}
	
	dbiterator->DecRef();
	dbinfo->DecRef();	

   	CleanupStack::PopAndDestroy(2,ServiceHandler);
    ReleaseLandmarkResources();    
	__UHEAP_MARKEND;
	return ret;
	}    

// -----------------------------------------------------------------------------
// CTLmDbTests::DeleteAllDatabases
// removes all local databases from the terminal 
// called by all testcases.
// -----------------------------------------------------------------------------
//
void CTLmDbTests::DeleteAllLocalDatabasesL() 
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
// -----------------------------------------------------------------------------
// CTLmDbTests::CheckErrorCode
// checks error code e
// called by all testcases.
// -----------------------------------------------------------------------------
//
TInt CTLmDbTests::CheckErrorCode( const CLiwGenericParamList& aOutList, TInt32 &aError )
	{
	TInt Index = 0;
	const TLiwGenericParam* errcode = aOutList.FindFirst(Index,KErrorCode);
	if ( KErrNotFound == Index )
		{
		iLog->Log( _L("ErrorCode not found in output ArgList") );
		return FAIL;
		}
	else
		errcode->Value().Get(aError);
	return PASS;
	}

void CTLmDbTests::CreateInterfaceL(CLiwServiceHandler*& aHandler,
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


//end of file
