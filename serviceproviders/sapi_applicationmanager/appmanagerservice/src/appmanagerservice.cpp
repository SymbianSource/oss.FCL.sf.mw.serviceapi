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
* Description:  This Class provides the core functionality to Application Manager
*				 SAPI
*
*/



#include <e32std.h>
#include <apgcli.h>

#include "appmanagerservice.h"
#include "launcher.h"
#include "launcherobserver.h"
#include "installpkgiterator.h"
#include "appiterator.h"
#include "asynchrequestmanager.h"

//Content Type
_LIT(KApplication,"Application");
_LIT(KUserInstalledPackage,"UserInstalledPackage");

#define KMAXPATHLENGTH 255

// -----------------------------------------------------------------------------
// CAppManagerService::NewLC
// Returns the instance of CAppManagerService class.
// -----------------------------------------------------------------------------
EXPORT_C CAppManagerService* CAppManagerService::NewL()
	{
	CAppManagerService* self = new ( ELeave )CAppManagerService();
	CleanupStack::PushL( self );
	self->ConstructL();
	CleanupStack::Pop( self );
	return self;
	}


// -----------------------------------------------------------------------------
// CAppManagerService::~CAppManagerService
// Destructor
// -----------------------------------------------------------------------------

CAppManagerService::~CAppManagerService()
	{
	
	//releasing the AsynchRequestManager class   
    delete iAsynchReqMngr;    
	
	//Closing the session of application  arch server
    iApaLsSession.Close();
    
    //releasing the launcher class
    delete iLauncher;
  
  	}


// -----------------------------------------------------------------------------
// CAppManagerService::LaunchApplication
// This function Launch the given Application
// -----------------------------------------------------------------------------

EXPORT_C void CAppManagerService::LaunchApplicationL( const TDesC& aAppId,
                                                      const TDesC8& aCmdLine,
                                                      const TOptions& aOptions,
                                                      MAppObserver* aObserver,
                                                      TInt32 aTransactionID )
	{

    if ( !aObserver )
        {
        //Synchronous call
       
        iLauncher->LaunchApplicationL( aAppId, aCmdLine, aOptions);
      
        }
    else
        {
        //Asynchorous opertaion
        //Add observer for supporting cancel to multiple asynch request
       
        TThreadId threadId =iLauncher->LaunchApplicationL( aAppId, aCmdLine, aOptions);
        CLauncherObserver* observer = iAsynchReqMngr->AddObsereverLC( aObserver,aTransactionID, threadId );
        CleanupStack::Pop( observer );
  	    
	    
	    }



   }


// -----------------------------------------------------------------------------
// CAppManagerService::LaunchApplication
// This function Launch the given content
// -----------------------------------------------------------------------------

EXPORT_C void CAppManagerService::LaunchDocumentL( TDocument& aCriteria,
       	                                           const TDesC8& aMimeType,
       	                                           const TOptions& aOptions ,
       	                                           TDesC& aFileName,
       	                                           MAppObserver* aObserver,
       	                                           TInt32 aTransactionID )
	{

    if ( !aObserver )
        {
        //Synchronous call
        __UHEAP_MARK;
        if( 0 == aOptions.iMode.CompareF( KChained ) )
            {
            iLauncher->LaunchDocumentL( aCriteria );
            }
        else
            {
            iLauncher->LaunchDocumentL( aCriteria, aMimeType, aOptions, aFileName);
            }
        __UHEAP_MARKEND;
        }
    else
        {
        //Asynchorous call
        //Add observer for supporting cancel to multiple asynch request
        TThreadId threadId = iLauncher->LaunchDocumentL(aCriteria, aMimeType, aOptions, aFileName );
        CLauncherObserver* observer = iAsynchReqMngr->AddObsereverLC( aObserver,aTransactionID, threadId );
        CleanupStack::Pop( observer );
        }

   }

// -----------------------------------------------------------------------------
// CAppManagerService::GetListL
// This function gives the list of all appication or installed packages 
// according to the content
// -----------------------------------------------------------------------------

EXPORT_C void  CAppManagerService::GetListL( MIterator*&   aIterator,
                                             const TDesC& aContent, 
                                             const CFilterParam* aFilterParam )
    {
	

	if( KErrNone == aContent.CompareF(KApplication) )
		{
        //CAppIterator class traverse the list of all application
		aIterator = CAppIterator::NewL( iApaLsSession, aFilterParam );
		}
	else if(KErrNone == aContent.CompareF(KUserInstalledPackage) )
		{
		//CInstallPkgIterator class traverse the list of user intsalled package
		aIterator = CInstallPkgIterator::NewL();
		}
	else
		{
		// wrong content
		User::Leave( KErrArgument );
		}
 

	}

// -----------------------------------------------------------------------------
// CAppManagerService::Cancel
// Cancel the pending asynchronous request
// -----------------------------------------------------------------------------
EXPORT_C TInt CAppManagerService::Cancel( TInt32 aTransactionID )
	{

       return iAsynchReqMngr->Cancel( aTransactionID );

	}

// -----------------------------------------------------------------------------
// CAppManagerService::CAppManagerService
// ConstructorL
// -----------------------------------------------------------------------------
void CAppManagerService::ConstructL()

	{
	//opening the session with application arch server
    User::LeaveIfError(iApaLsSession.Connect());
    
    //creating the instance of launcher class for delegating all launching request
    iLauncher = CLauncher::NewL( iApaLsSession );
	
	 //creating the instance of Asynch request manager which care the multiple asynch request
    iAsynchReqMngr = CAsynchRequestManager::NewL();
	
	}



// -----------------------------------------------------------------------------
// CAppManagerService::ValidateFilePathL
// Validate the given filepath
// -----------------------------------------------------------------------------
void CAppManagerService::ValidateFilePathL(const TDesC& aFilePath)
	{
	RFile file;	
	RFs fs;
	
	if (aFilePath.Length() > KMAXPATHLENGTH)
		User::Leave(KErrArgument);
	
	User::LeaveIfError(fs.Connect());
 
 	CleanupClosePushL(fs);
 	
 	if (file.Open(fs, aFilePath, EFileRead) != KErrNone)
 		{
 		User::Leave(KErrPathNotFound);
 		}
 		
 	CleanupStack::PopAndDestroy();
	}
