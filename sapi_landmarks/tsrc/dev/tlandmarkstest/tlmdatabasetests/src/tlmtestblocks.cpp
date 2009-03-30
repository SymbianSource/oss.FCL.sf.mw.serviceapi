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
#include "TLmDatabasesTest.h"
#include "landmarkservice.h"

// CONSTANTS  

_LIT(KLocalProtocol, "file");

_LIT(KDb1, "C:eposlm1.ldb");

_LIT(KActiveDb1, "file://c:activelm1.ldb");
_LIT(KActiveDb2, "file://c:activelm2.ldb");

_LIT(KDbInvalidUri1, "file:/c:invalid.ldb");
_LIT(KDbInvalidUri2, "z:invalid.ldb");
_LIT(KDbInvalidUri3, "c:invalid");
_LIT(KDbInvalidUri4, "c:\\invalid.ldb");
_LIT(KDbInvalidUri5, "e:invalid.ldb");


_LIT(KRemoteUnsupportedDbUri, "http://remote.ldb");


// ============================ MEMBER FUNCTIONS ===============================


// -----------------------------------------------------------------------------
// CTLmDbTest::RunMethodL
// Run specified method. Contains also table of test mothods and their names.
// -----------------------------------------------------------------------------
//
TInt CTLmDbTest::RunMethodL( 
    CStifItemParser& aItem ) 
    {

    static TStifFunctionInfo const KFunctions[] =
        {  
        // Copy this line for every implemented function.
        // First string is the function name used in TestScripter script file.
        // Second is the actual implementation member function. 
        ENTRY( "AddDatabase",    		CTLmDbTest::AddDatabase ),
        ENTRY( "DeleteDatabase", 		CTLmDbTest::DeleteDatabase),
        ENTRY( "AddExistingDatabase", 	CTLmDbTest::AddExistingDatabase),
        ENTRY( "AddInvalidDatabase", 	CTLmDbTest::AddInvalidDatabase),
        ENTRY( "AddRemoteDatabase", 	CTLmDbTest::AddRemoteDatabase), 
        ENTRY( "UpdateDatabase" ,  		CTLmDbTest::UpdateDatabase),
        ENTRY( "SetActiveDb", 			CTLmDbTest::SetActiveDb ),
        ENTRY( "GetDbList", 			CTLmDbTest::GetDbList )

        };

    const TInt count = sizeof( KFunctions ) / 
                        sizeof( TStifFunctionInfo );

    return RunInternalL( KFunctions, count, aItem );

    }

// -----------------------------------------------------------------------------
// CTLmDbTest::AddDatabase
// test method function.
// -----------------------------------------------------------------------------
//
TInt CTLmDbTest::AddDatabase( CStifItemParser& /*aItem*/ )
    {

	    _LIT( KExample, "AddDatabase" );
	    iLog->Log( KExample );
   
	   DeleteAllLocalDatabasesL();
	   
	   CLandmarkService *obj = CLandmarkService::NewL ();
	   CleanupStack::PushL(obj);
	    
	   TRAPD (err,obj->AddItemL (KDb1));
	   if (!err)
	   {
	   		CDesCArray* dbList = iDatabaseManager->ListDatabasesLC(KLocalProtocol);
			err = 1;
			for ( TInt i = 0; i < dbList->Count(); i++ )
			{
				TPtrC db = (*dbList)[i];
				if ( db.Compare(KDb1) )
				{
					err = 0;
					break;	
				}
			}
			CleanupStack::PopAndDestroy(); //dblist
	   }

	   CleanupStack::PopAndDestroy(obj);
	   
	   DeleteAllLocalDatabasesL();
	   
	   return err;
    }
// -----------------------------------------------------------------------------
// CTLmDbTest::AddExistingDatabase
// test method function.
// -----------------------------------------------------------------------------
// 
TInt CTLmDbTest::AddExistingDatabase( CStifItemParser& /*aItem*/ )
    {

	    _LIT( KExample, "AddExistingDatabase" );
	    iLog->Log( KExample );
   
	   TInt err;
	   DeleteAllLocalDatabasesL();
	   
	   CLandmarkService *obj = CLandmarkService::NewL ();
	   CleanupStack::PushL(obj);
	    
	   TRAP (err,obj->AddItemL (KDb1));
		if (err)
		{
			CleanupStack::PopAndDestroy(obj);
			return err;	
		}

	   TRAP (err,obj->AddItemL (KDb1) );
	   	
	   CleanupStack::PopAndDestroy(obj);
	   
	   DeleteAllLocalDatabasesL();
	   
	   return ( err != KErrAlreadyExists );
	   
    }   
// -----------------------------------------------------------------------------
// CTLmDbTest::AddExistingDatabase
// test method function.
// -----------------------------------------------------------------------------
// 
TInt CTLmDbTest::AddInvalidDatabase( CStifItemParser& /*aItem*/ )
    {

	    _LIT( KExample, "AddInvalidDatabase" );
	    iLog->Log( KExample );
   
	   TInt err;
	   DeleteAllLocalDatabasesL();
	   
	   CLandmarkService *obj = CLandmarkService::NewL ();
	   CleanupStack::PushL(obj);
	    
	   	
	   TRAP (err,obj->AddItemL (KDbInvalidUri1));
		if ( !err )
		{
			CleanupStack::PopAndDestroy(obj);
			iLog->Log( _L("KDbInvalidUri1 paniced incorrect error : %d"),err );
			return 1;	
		}

	   TRAP (err,obj->AddItemL (KDbInvalidUri2));
		if ( err != KErrAccessDenied )
		{
			CleanupStack::PopAndDestroy(obj);
			iLog->Log( _L("KDbInvalidUri2 paniced incorrect error : %d"),err );
			return err;	
		}

	   TRAP (err,obj->AddItemL (KDbInvalidUri3));
		if ( err != KErrArgument )
		{
			CleanupStack::PopAndDestroy(obj);
			iLog->Log( _L("KDbInvalidUri3 paniced incorrect error : %d"),err );
			return err;	
		}	   
	   TRAP (err,obj->AddItemL (KDbInvalidUri4));
		if ( err != KErrArgument )
		{
			CleanupStack::PopAndDestroy(obj);
			iLog->Log( _L("KDbInvalidUri4 paniced incorrect error : %d"),err );
			return err;	
		}	   

	   TRAP (err,obj->AddItemL (KDbInvalidUri5));
		if ( err != KErrNotReady )
		{
			CleanupStack::PopAndDestroy(obj);
			iLog->Log( _L("KDbInvalidUri5 paniced incorrect error : %d"),err );
			return err;	
		}

	   CleanupStack::PopAndDestroy(obj);
	   
	   DeleteAllLocalDatabasesL();
	   
	   return 0;
	   
    }   
// -----------------------------------------------------------------------------
// CTLmDbTest::AddRemoteDatabase
// test method function.
// -----------------------------------------------------------------------------
//
TInt CTLmDbTest::AddRemoteDatabase( CStifItemParser& /*aItem*/ )
    {

	    _LIT( KExample, "AddRemoteDatabase" );
	    iLog->Log( KExample );
   
	   TInt err;
	   DeleteAllLocalDatabasesL();
	   
	   CLandmarkService *obj = CLandmarkService::NewL ();
	   CleanupStack::PushL(obj);
	    
	   TRAP (err,obj->AddItemL (KRemoteUnsupportedDbUri));
		if ( err != KErrNotSupported )
		{
			CleanupStack::PopAndDestroy(obj);
			return err;	
		}

	   CleanupStack::PopAndDestroy(obj);
	   
	   DeleteAllLocalDatabasesL();
	   
	   return 0;
	   
    }               
// -----------------------------------------------------------------------------
// CTLmDbTest::DeleteDatabase
// test method function.
// -----------------------------------------------------------------------------
//
TInt CTLmDbTest ::DeleteDatabase(CStifItemParser& /*aItem*/)
	{
	    _LIT( KExample, "DeleteDatabase" );
	    iLog->Log( KExample );
   
	   TInt err;
	   DeleteAllLocalDatabasesL();
	   
	   CLandmarkService *obj = CLandmarkService::NewL ();
	   CleanupStack::PushL(obj);
	    
		HPosLmDatabaseInfo* info = HPosLmDatabaseInfo::NewL(KDb1);
		CleanupStack::PushL(info);
		
		iDatabaseManager->CreateDatabaseL (*info);
	   
	   CleanupStack::PopAndDestroy(info);


		TRAP(err,obj->RemoveItemL (KDb1))
		
		if (!err)
		{
			TRAP(err,iDatabaseManager->DatabaseExistsL (KDb1));
		}
		
	   CleanupStack::PopAndDestroy(obj);
	   
	   DeleteAllLocalDatabasesL();
	   
	   return err;
	}    
// -----------------------------------------------------------------------------
// CTLmDbTest::UpdateDatabase
// test method function.
// -----------------------------------------------------------------------------
//
TInt CTLmDbTest ::UpdateDatabase(CStifItemParser& /*aItem*/)
	{
	    _LIT( KExample, "UpdateDatabase" );
	    iLog->Log( KExample );
   
	   TInt err;
	   DeleteAllLocalDatabasesL();
  
	   CLandmarkService *obj = CLandmarkService::NewL ();
	   CleanupStack::PushL(obj);
	    
		HPosLmDatabaseInfo* info = HPosLmDatabaseInfo::NewL(KDb1);
		CleanupStack::PushL(info);
		
		iDatabaseManager->CreateDatabaseL (*info);
	   
	   CleanupStack::PopAndDestroy(info);

		TPosLmDatabaseSettings settings;
		TPosLmDatabaseName dbname = _L("loacal database");;
		settings.SetDatabaseName(dbname);
		
		TRAP(err,obj->UpdateItemL (settings,KDb1))
		
		if (!err)
		{
			HPosLmDatabaseInfo* info = HPosLmDatabaseInfo::NewL(KDb1);
			CleanupStack::PushL(info);
			TRAP(err,iDatabaseManager->GetDatabaseInfoL (*info));
	   		if (!err)
	   		{
				const TPosLmDatabaseSettings settings = info->Settings();
				TPtrC dbname = settings.DatabaseName();
				if ( !dbname.Compare( _L("loacal database") ) )
					err = 0;
				else
					err = 1;
	   			
	   		}
	   		CleanupStack::PopAndDestroy(info);
		}
		
	   CleanupStack::PopAndDestroy(obj);
	   
	   DeleteAllLocalDatabasesL();
	   
	   return err;
	}    
// -----------------------------------------------------------------------------
// CTLmDbTest::SetActiveDb
// test method function.
// -----------------------------------------------------------------------------
//
TInt CTLmDbTest ::SetActiveDb(CStifItemParser& /*aItem*/)
	{
	    _LIT( KExample, "UpdateDatabase" );
	    iLog->Log( KExample );
   
	   TInt err;
	   DeleteAllLocalDatabasesL();
 
	   CLandmarkService *obj = CLandmarkService::NewL ();
	   CleanupStack::PushL(obj);
	    
		HPosLmDatabaseInfo* info = HPosLmDatabaseInfo::NewL(KActiveDb1);
		CleanupStack::PushL(info);
		
		iDatabaseManager->CreateDatabaseL (*info);
	   
	   CleanupStack::PopAndDestroy(info);

		info = HPosLmDatabaseInfo::NewL(KActiveDb2);
		CleanupStack::PushL(info);
		
		iDatabaseManager->CreateDatabaseL (*info);		
	   
	   CleanupStack::PopAndDestroy(info);				

		TRAP (err,obj->SetActiveL(KActiveDb1));
		if ( !err )
		{
			HBufC* Defaultdb = iDatabaseManager->DefaultDatabaseUriLC ();
			if( !Defaultdb->Compare(KActiveDb1) )
				err = 0;
			else
				err = 1;
			CleanupStack::PopAndDestroy(Defaultdb); //Defaultdb	
		}
		
	   if ( !err )
	   {
		TRAP (err,obj->SetActiveL(KActiveDb2));
		if ( !err )
		{
			HBufC* Defaultdb = iDatabaseManager->DefaultDatabaseUriLC ();
			if( !Defaultdb->Compare(KActiveDb2) )
				err = 0;
			else
				err = 1;
			CleanupStack::PopAndDestroy(Defaultdb); //Defaultdb	
		}	   	
	   }
	   CleanupStack::PopAndDestroy(obj);
	   
	   DeleteAllLocalDatabasesL();
	   
	   return err;
	}    
// -----------------------------------------------------------------------------
// CTLmDbTest::GetDbList
// test method function.
// -----------------------------------------------------------------------------
//
TInt CTLmDbTest ::GetDbList(CStifItemParser& /*aItem*/)
	{
	    _LIT( KExample, "GetDbList" );
	    iLog->Log( KExample );
   
	   TInt err;
	   DeleteAllLocalDatabasesL();
 
	   CLandmarkService *obj = CLandmarkService::NewL ();
	   CleanupStack::PushL(obj);
	    
		HPosLmDatabaseInfo* info = HPosLmDatabaseInfo::NewL(KActiveDb1);
		CleanupStack::PushL(info);
		
		iDatabaseManager->CreateDatabaseL (*info);
		iLog->Log(_L("Database created: KActiveDb1")) ;	   
	  
	  CleanupStack::PopAndDestroy(info);

		info = HPosLmDatabaseInfo::NewL(KActiveDb2);
		CleanupStack::PushL(info);
		
		iDatabaseManager->CreateDatabaseL (*info);		
	   
	   CleanupStack::PopAndDestroy(info);				
		iLog->Log(_L(" Database created: KActiveDb2"));	   
		
		CDesCArray* aDatabaseList;
		TRAP(err,obj->GetListL(aDatabaseList));
		CleanupStack::PushL(aDatabaseList);
		iLog->Log(_L(" Count: %d"),aDatabaseList->Count() );  
		if ( !err )
		{
			for (TInt i = 0; i < aDatabaseList->Count(); i++)
			{
				TPtrC db = (*aDatabaseList)[i] ;
				TBuf<30> buf;
				buf.Copy(db);
				
				buf.LowerCase();
				iLog->Log(_L(" Database: %s"),db.Ptr() );
				if ( buf.Compare(KActiveDb1) && buf.Compare(KActiveDb2) && buf.Compare(_L("file://c:eposlm.ldb")))
				{
				    iLog->Log(_L(" error"));
				    err = 1;
					break;					
				}

				iLog->Log(_L(" i: %d"),i );
			}
		}
		iLog->Log(_L(" Error: %d"),err );   
		CleanupStack::PopAndDestroy(); //aDatabaseList

	   CleanupStack::PopAndDestroy(obj);
	   
	   DeleteAllLocalDatabasesL();
	   
	   return err;
	}    

// -----------------------------------------------------------------------------
// CTLmDbTest::DeleteAllDatabases
// removes all local databases from the terminal 
// called by all testcases.
// -----------------------------------------------------------------------------
//
void CTLmDbTest::DeleteAllLocalDatabasesL() 
    {
		TInt count;
		
		CDesCArray* dbList = iDatabaseManager->ListDatabasesLC(KLocalProtocol);
		count = dbList->Count();
		
		for ( TInt i = 0; i < count; i++ )
		{
			TPtrC db = (*dbList)[i];
			iDatabaseManager->DeleteDatabaseL ( db );
		}
		CleanupStack::PopAndDestroy (1);

    }
