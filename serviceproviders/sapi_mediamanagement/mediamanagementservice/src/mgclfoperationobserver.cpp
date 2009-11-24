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
* Description:  This Class is observer for the CLF framework
*
*/


#include <MCLFItemListModel.h>
#include <MCLFSortingStyle.h>

#include "mgclfoperationobserver.h"
#include "mgservice.h"
#include "mgoperationobserver.h"
#include "asynchrequestmanager.h"
#include "mgpostfilter.h"


// -----------------------------------------------------------------------------
// CClfOperationObserver::NewL
// Returns the instance of CClfOperationObserver.
// -----------------------------------------------------------------------------
CClfOperationObserver* CClfOperationObserver::NewL()
	{
	CClfOperationObserver* self = new ( ELeave )CClfOperationObserver();
	return self;
	}


//-----------------------------------------------------------------------------
//CClfOperationObserver::HandleOperationEventL
//This Function called by the CLF Framework when the list of media items are ready
// -----------------------------------------------------------------------------

void CClfOperationObserver::HandleOperationEventL(
										  TCLFOperationEvent aOperationEvent,
                                          TInt aError )
	{
	    TMgOperationEvent mgEvent;

		aOperationEvent == ECLFRefreshComplete?
		mgEvent = EMgRefreshComplete:mgEvent = EMgModelOutdated;


    	if ( NULL != iMGService )
    	{
    	    // clear the state so that next request can be taken
    		iMGService->Clear();
    	}

    	if( NULL !=  iServiceObserver && (mgEvent == ECLFRefreshComplete)) //Asynchronous
    	{
         
		iServiceObserver->MgNotifyL( iTransactionID,iListModel,this,mgEvent, aError );
        
         // calling request complete on asyncrequestmanager
         iAsyncRequestManager->RequestComplete( iTransactionID );
         
		//Ownership of the List model and the observer are transferred to the Iterator class
         iListModel = NULL;
         //In future at the time of supporting back to back call
		//call delete this	
         iServiceObserver = NULL;
  	     iMGService = NULL;
  	     
		//delete this;
	     
    	}
    	
	}




// -----------------------------------------------------------------------------
// CClfOperationObserver::SetMemberVar
// set the member varibale for the current request.
// -----------------------------------------------------------------------------
void CClfOperationObserver::SetMemberVar( TUint  aTransactionID,
                                          MMgOperationObserver* aServiceObserver,
										  MCLFItemListModel* aListModel,
										  CMgService* aMGService,CAsynchRequestManager* aAsyncReqManager,
										  CPostFilter* aFilter,MCLFSortingStyle* aSortingStyle)
	{

	iServiceObserver = aServiceObserver;
  	iListModel = aListModel;
    iMGService = aMGService;
    iTransactionID = aTransactionID;
    iAsyncRequestManager = aAsyncReqManager;
    iFilter = aFilter;
    iSortingStyle= aSortingStyle;
    
	}


// -----------------------------------------------------------------------------
// CClfOperationObserver::Cancel
// Cancel the pending asynchronous request
// -----------------------------------------------------------------------------
void CClfOperationObserver::CancelL()
	{
	TMgOperationEvent mgEvent = EMgModelCancel;       
		if( iListModel )
			{
			iListModel->CancelRefresh();
			delete iListModel;
			iListModel = NULL;
			}
	
   	iServiceObserver->MgNotifyL(iTransactionID, NULL, NULL, mgEvent, KErrNone );
   	iMGService = NULL;
    iTransactionID = 0;	
    //In future at the time of supporting back to back call
	//call delete this	
	iServiceObserver = NULL;
 

	}
	
// -----------------------------------------------------------------------------
// CClfOperationObserver::CClfOperationObserver
// Destructor
// -----------------------------------------------------------------------------

CClfOperationObserver::~CClfOperationObserver()
                       
    {
        iListModel = NULL;
        if(iAsyncRequestManager)
            {
            iAsyncRequestManager = NULL;
            }
        
        if(iFilter)
            {
            delete iFilter;
            }
        if(iSortingStyle)
            {
            delete iSortingStyle;
            }
	//In future at the time of supporting 
	// back to back Calls we have to delete the iServiceOberver
    iServiceObserver = NULL;
	}

// -----------------------------------------------------------------------------
// CClfOperationObserver::CClfOperationObserver
// Constructor
// -----------------------------------------------------------------------------

CClfOperationObserver::CClfOperationObserver():
                        iServiceObserver( NULL ),
						iListModel( NULL ),
						iMGService ( NULL ),
						iTransactionID(0)
{

}
