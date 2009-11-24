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
* Description:  This Class provides information of all Application  on phone.
*				 				 
*
*/


#include <e32cmn.h>
#include <apmstd.h>
#include <apaid.h>
#include <apgcli.h>
#include "appiterator.h"
#include "appinfo.h"
#include "appmanagercommon.h"
#include "appmanagerservice.h"

// -----------------------------------------------------------------------------
// CAppIterator::NewL
// Returns the instance of CAppIterator class.
// -----------------------------------------------------------------------------
 CAppIterator* CAppIterator::NewL(RApaLsSession& aApaLsSession ,const CFilterParam* aFilterParam )
	{
	CAppIterator* self = new(ELeave) CAppIterator(aApaLsSession);
	CleanupStack::PushL(self);
	self->ConstructL(aFilterParam);
	CleanupStack::Pop(self);
	return self;
	}
// -----------------------------------------------------------------------------
// CAppIterator::CAppIterator
// C++ Constructor
// -----------------------------------------------------------------------------

CAppIterator::CAppIterator(RApaLsSession& aApaLsSession):iApaLsSession(aApaLsSession),iUid(KNullUid),iHandler(EFalse)
	{
	
		
	}

// -----------------------------------------------------------------------------
// CAppIterator::ConstructL
// Two-phase constructor
// -----------------------------------------------------------------------------
void CAppIterator::ConstructL(const CFilterParam* aFilterParam)
	{
	// If both document name and mimetype are given then document name would be given priority
	if( NULL == aFilterParam)
		{
		//Get all Application
		User::LeaveIfError(iApaLsSession.GetAllApps());	
		}
	else if( (0 != aFilterParam->DocName().Length() ) )	
		{
		
		CAppManagerService::ValidateFilePathL(aFilterParam->DocName());
		
		//Get Handler for Document
		iHandler = ETrue;
		TDataType notused;
		User::LeaveIfError(iApaLsSession.AppForDocument(aFilterParam->DocName(), iUid, notused));	
		
		if (iUid == KNullUid)
			User::Leave(KErrArgument);
		}
	else if( ( 0 != aFilterParam->MimeType().Length() ) )
		{
		 //Get Handler for MIME Type
		 iHandler = ETrue;
		 TDataType datatype( aFilterParam->MimeType() );// Now it is HBufC*
		 /// now makeTDataType object
		 User::LeaveIfError( iApaLsSession.AppForDataType(datatype,iUid) );
		 
		 if (iUid == KNullUid)
		 	User::Leave(KErrArgument);
		}	
    else
        {
        User::Leave( KErrNotFound);    
        }
	
	}

     
// -----------------------------------------------------------------------------
// CAppIterator::~CAppIterator
// Destructor
// -----------------------------------------------------------------------------
CAppIterator::~CAppIterator()	
	{
	
		
	}

// -----------------------------------------------------------------------------
// CAppIterator::~CAppIterator
// It gives the instance of MInfoMap which contains the information about next application on 
// iterator list.
// -----------------------------------------------------------------------------
 TBool  CAppIterator::NextL(MInfoMap*& aInfo)
	{

	
	TApaAppInfo appinfo;
	TBool retValue = ETrue;
	
	if( KNullUid != iUid && iHandler)
		{
		 //List will return Handler application and it contains only one handler application  
		 User::LeaveIfError (iApaLsSession.GetAppInfo(appinfo, iUid));
		 aInfo = CAppInfo::NewL(appinfo);
		 iHandler = EFalse;

		}
	else if(KNullUid == iUid && iHandler == EFalse)
		{
        //List will return all application
        TInt ret = iApaLsSession.GetNextApp(appinfo);

		if(RApaLsSession::ENoMoreAppsInList  == ret)
			{
			//underlying List finished
			aInfo = NULL;
			retValue = EFalse;	
			}
		else if(KErrNone != ret)
			User::LeaveIfError (ret);//Some error comes
		else
			{
			aInfo = CAppInfo::NewL(appinfo); //send the object of map
			}
		}	
	else
		{
		aInfo = NULL;
		retValue = EFalse;	
		}	
	
    return retValue;

	}
	
// -----------------------------------------------------------------------------
// CAppIterator::Reset
// It resets the iterator
// -----------------------------------------------------------------------------
void CAppIterator::Reset()
	{

	if( KNullUid != iUid )
		{
	    iHandler = ETrue;
		}
	else
		{
		//reset the underlying iterator to begining
		iApaLsSession.GetAllApps();	
		}


	
}
