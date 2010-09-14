/*
* Copyright (c) 2007-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  This Class provides the functionality to launch the application
*
*/




#include <apgcli.h>
#include <apacmdln.h>
#include <e32std.h>
#include <eikappui.h>
#include <eikenv.h>
#include <e32base.h>
#include <f32file.h>
#include <documenthandler.h>

#include "launcher.h"
#include "launcherobserver.h"
#include "appmanagerservice.h"


_LIT(KBackground ,"Background");
//_LIT(KChained,"Chained");
_LIT(KScheme,"s60uid://0x");
const TInt KDocMaxDigitsInHexString = 8; // 32 bits.

const TInt KLen = 2; // "//" for count these



// -----------------------------------------------------------------------------
// CLauncher::NewLC
// Returns the instance of CLauncher class.
// -----------------------------------------------------------------------------
CLauncher* CLauncher::NewL( RApaLsSession& aSession )
	{
	CLauncher* self = new ( ELeave )CLauncher( aSession );
	return self;
	}


// -----------------------------------------------------------------------------
// CLauncher::LaunchApplication
// This function Launch the Given Application
// -----------------------------------------------------------------------------

 TThreadId  CLauncher::LaunchApplicationL( const TDesC&    aAppId,
                                            const TDesC8&   aCmdLine,
                                            const TOptions& aOptions
                                           )
	{

	TUid appUid;
    TApaAppInfo appInfo;

    //parse the application string
    ParseAppIdL( aAppId, appUid );

    
    if(!( (0==aOptions.iMode.CompareF( KChained ) || 0 == aOptions.iMode.CompareF( KStandalone )  ) && (0==aOptions.iPostion.CompareF( KBackground ) || 0 == aOptions.iPostion.CompareF( KForeground ) ) ) )
        {
        User::Leave( KErrArgument );
        }
    
    CApaCommandLine* cmdLine = CApaCommandLine::NewLC();

    //Setting Executable name

    if( KErrNone == iApaLsSession.GetAppInfo( appInfo, appUid) )
        {
        cmdLine->SetExecutableNameL( appInfo.iFullName );
        }
    else
        {
        //Invalid UID
        User::Leave( KErrArgument );
        }


    //Setting command Line Argument

    if ( aCmdLine.Length() )
        {
        cmdLine->SetTailEndL( aCmdLine );
        }


    //Setting Document Name

    if ( aOptions.iDocument.Length() )
        {
        CAppManagerService::ValidateFilePathL(aOptions.iDocument);
        
        cmdLine->SetDocumentNameL( aOptions.iDocument );
        }

    //Set the Launchine Mode
    if( 0 == aOptions.iMode.CompareF( KChained ) )
       {

       //Chianed mode doesn;t make any sense with background 
       if( 0 != aOptions.iPostion.CompareF( KBackground ) )
	        cmdLine->SetCommandL( EApaCommandRun );
       else
            User::Leave( KErrNotSupported );

       SetChainedModeL( cmdLine, appUid );

       }

    else
        {
         //Setting the Launching postion means either background or foreground
        if( 0 == aOptions.iPostion.CompareF( KBackground ) )
            {
            cmdLine->SetCommandL( EApaCommandBackground );
            }
        else
            {
            cmdLine->SetCommandL( EApaCommandRun );
            }

        }

    // Launch the requested Application
    TThreadId threadNotUsed;
    TRequestStatus requestStatusForRendezvous;
    User::LeaveIfError( iApaLsSession.StartApp( *cmdLine,
								               threadNotUsed,
								               &requestStatusForRendezvous ));



	User::WaitForRequest( requestStatusForRendezvous );
	User::LeaveIfError( requestStatusForRendezvous.Int());
	CleanupStack::PopAndDestroy( cmdLine  );


    return threadNotUsed;
    }

 // -----------------------------------------------------------------------------
 // CLauncher::LaunchDocumentL
 // This function Launch the Given Document in synchronous chained mode
 // -----------------------------------------------------------------------------
 void CLauncher::LaunchDocumentL( TDocument& aCriteria ) 
     {
     if( !iDocHandler )
         {
         iDocHandler = CDocumentHandler::NewL();
         }
     TDataType dataType;
     User::LeaveIfError(iDocHandler->OpenFileEmbeddedL(aCriteria.iPath, dataType));
     }
// -----------------------------------------------------------------------------
// CLauncher::LaunchDocumentL
// This function Launch the Given Document
// -----------------------------------------------------------------------------

 TThreadId CLauncher::LaunchDocumentL(TDocument& aCriteria,
       	                               const TDesC8& aMimeType,
       	                               const TOptions& aOptions ,
       	                               TDesC& aFileName
       	                               )
    {

    TUid appUid;
    TApaAppInfo appInfo;
    TDataType dataType( aMimeType );
    CApaCommandLine* cmdLine = CApaCommandLine::NewLC();
    TFileName temp;

     //Extracting Application Uid
     if( 0 != aCriteria.iHandle.SubSessionHandle())
         {
         iApaLsSession.AppForDocument( aCriteria.iHandle,appUid,dataType);
         cmdLine->SetCommandL( EApaCommandOpen );
         cmdLine->SetFileByHandleL( aCriteria.iHandle );
         }
    else if (0 != aCriteria.iPath.CompareF(KNullDesC) )
         {
         CAppManagerService::ValidateFilePathL(aCriteria.iPath);
         
         iApaLsSession.AppForDocument( aCriteria.iPath,appUid,dataType);
         cmdLine->SetCommandL( EApaCommandOpen );
         cmdLine->SetDocumentNameL(aCriteria.iPath );	
         }
    else if ( 0 != aMimeType.CompareF( KNullDesC8 ) )
         {
         iApaLsSession.AppForDataType(dataType,appUid);
         cmdLine->SetCommandL( EApaCommandCreate );

            //This is the logic for handling the buffer right now we are not supported as 
            //underlying S60 classes showing memory leak and pecular behaviour with different 
            //buffer
            
         	/*if( 0 != aOptions.iBuffer.CompareF( KNullDesC8 ) )
             {
                __UHEAP_MARK;
                CDocumentHandler *temp = CDocumentHandler::NewLC();
                TRAPD (err, temp->SaveL(aOptions.iBuffer,dataType,KEntryAttNormal) );
                temp->GetPath(aFileName);
                __UHEAP_MARKEND;
                CleanupStack::PopAndDestroy( );
             }*/
        
         //left to the launch application for setting
         cmdLine->SetDocumentNameL( aFileName );


         }
    else
        {
        User::Leave(KErrArgument);
        }


    //extraction application path
    if( KErrNone == iApaLsSession.GetAppInfo( appInfo, appUid) )
        {
        cmdLine->SetExecutableNameL( appInfo.iFullName );
        }
    else
        {
        User::Leave( KErrNotFound );
        }




    //Set the Launchine Mode
    if( 0 == aOptions.iMode.CompareF( KChained ) )
       {
        SetChainedModeL( cmdLine  ,appUid );
       }
    else if ( 0 != aOptions.iMode.CompareF( KStandalone ) ) //The only other mode is "Standalone"
        {   
            User::Leave(KErrArgument);
        }


    // Launch the requested Application
    TThreadId threadNotUsed;
    TRequestStatus requestStatusForRendezvous;
    User::LeaveIfError( iApaLsSession.StartApp( *cmdLine,
								               threadNotUsed,
								               &requestStatusForRendezvous ));



	User::WaitForRequest( requestStatusForRendezvous );
	User::LeaveIfError( requestStatusForRendezvous.Int());
	CleanupStack::PopAndDestroy( cmdLine  );
    
    
    
    return threadNotUsed;


    }


// -----------------------------------------------------------------------------
// CLauncher::LaunchDocumentL
// This function will parse the application ID string and return the UID
// -----------------------------------------------------------------------------

void CLauncher::ParseAppIdL( const TDesC & aSource ,TUid & aUid )
{

	// Icoming string : s60uid://0x101f4d90 , output : 0x101f4d90
	
	if( (aSource.Length() > KScheme.iTypeLength )  &&(0 == aSource.Mid(0,KScheme.iTypeLength).CompareF(KScheme) ) )
		{
		TChar a('/');
		TInt offset = aSource.Locate(a);
		
		TPtrC uiddata;

		// To chk for pattern ://
		if((0 != aSource.Mid(offset+1,1).Compare(_L("/"))) && (0 != aSource.Mid(offset-1,1).Compare(_L(":"))) )
	    	User::LeaveIfError(KErrArgument);

	    TPtrC a1(aSource.Mid(offset+1,1));
	    TPtrC a2(aSource.Mid(offset-1,1));

		TInt sourcelen = aSource.Length();
		TInt off = offset + KLen;
		TInt len = sourcelen -(off) ;

		uiddata.Set(aSource.Mid(off,len));
		TInt32 uidinint ;
	    User::LeaveIfError( ConvertHexStringToInt32(uiddata,uidinint) );

	    aUid.iUid = uidinint;
		}
	else
		{
		TUid empt(TUid::Null());
		aUid.iUid = empt.iUid;
		}

}

// -----------------------------------------------------------------------------
// CLauncher::ConvertHexStringToInt32
// This function will convert the Hax string into TInt32
// -----------------------------------------------------------------------------



TInt CLauncher::ConvertHexStringToInt32(const TDesC& aHexString,TInt32& aInt32 )
    {
    aInt32 = 0;

    TInt pos = aHexString.LocateF( 'x' );
    if ( pos == KErrNotFound )
        {
        pos = 0;
        }
    else
        {
        pos++;
        }

    if( ( aHexString.Length() - pos ) > KDocMaxDigitsInHexString )
        {
        return KErrArgument; // Error: value too big.
        }
    TPtrC hexStringPtr( aHexString.Mid( pos ) );

    TInt64 value64;
    if ( TLex( hexStringPtr ).Val( value64, EHex ) != KErrNone )
        {
        return KErrArgument; // Error: conversion failed.
        }
    aInt32 = value64;

    return KErrNone;
    }


// -----------------------------------------------------------------------------
// CLauncher::SetChainedModeL
// This function will set the application to launch in chained mode
// -----------------------------------------------------------------------------


void CLauncher::SetChainedModeL( CApaCommandLine* aCmdLine  , const TUid& aAppUid )
    {

       CEikonEnv* eikEnv = CEikonEnv::Static();

       if( !eikEnv )
           {
	        //Console Based Application can not launch another application in
	        //chained mode
	        User::Leave( KErrNotSupported );
           }
       else
           {
            RWindowGroup& wg = eikEnv->RootWin();
            CEikAppUi* appUi = eikEnv->EikAppUi();


	        // Window chain the client with the current application
	        const TInt parentWindowGroupID = wg.Identifier();
	        if ( parentWindowGroupID )
		        {
		        aCmdLine->SetParentWindowGroupID( parentWindowGroupID );
		        wg.AllowProcessToCreateChildWindowGroups( aAppUid );
		        }
		    
		        if ( appUi )
		        {
     		     appUi->DeactivateActiveViewL();
                }
           }
    }





// -----------------------------------------------------------------------------
// CLauncher::CLauncher
// Constructor
// -----------------------------------------------------------------------------
CLauncher::CLauncher( RApaLsSession& aSession ): iApaLsSession( aSession )

	{

	}


// -----------------------------------------------------------------------------
// CLauncher::~CLauncher
// Destructor
// -----------------------------------------------------------------------------
CLauncher::~CLauncher( )

	{
    if( iDocHandler )
        {
        delete iDocHandler;
        }
	}


	
