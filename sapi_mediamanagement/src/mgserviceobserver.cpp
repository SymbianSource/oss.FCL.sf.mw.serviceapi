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
* Description:  This Class is observer for the mgservice class (core class)
*
*/

#include <liwcommon.h>
#include <mclfitemlistmodel.h>

#include "mgserviceobserver.h"
#include "mgitemslist.h"
#include "mginterface.h"
#include "serviceerrno.h"
//using namespace LIW;
//Output Keys/arguments
_LIT8(KResponse,"ReturnValue");
_LIT8(KErrorCode,"ErrorCode");

// -----------------------------------------------------------------------------
// CMgServiceObserver::NewL
// Returns the instance of CMgServiceObserver.
// -----------------------------------------------------------------------------
CMgServiceObserver* CMgServiceObserver::NewL()
	{

	CMgServiceObserver* self = new ( ELeave )CMgServiceObserver();
	CleanupStack::PushL( self );
	self->ConstructL();
	CleanupStack::Pop( self );
	return self;

	}





// -----------------------------------------------------------------------------
// CMgServiceObserver::MgNotify
// Called by CMgService class when asynch operation complete
// -----------------------------------------------------------------------------
void CMgServiceObserver :: MgNotifyL( TUint  aTransactionID,
                                      MCLFItemListModel* aListModel,
                                      TMgOperationEvent& aOperationEvent,
                                      const TInt& aError  )


	{
	iOutput->Reset();
    //const CLiwGenericParamList& temp1 = *iOutput;
    //const CLiwGenericParamList* temp2 = &temp1;
    //delete temp2;
    
    if ( EMgModelCancel == aOperationEvent )
        {
            if( iCallBack )

            {
             iOutput->AppendL( TLiwGenericParam ( KErrorCode,TLiwVariant( (TInt32)SErrNone ) ) );
             TRAP_IGNORE(iCallBack->HandleNotifyL ( aTransactionID, KLiwEventCanceled, *iOutput,*iInput ));
             //self destruction should be done here in future
             // instead of below four lines
             iCallBack = NULL ;
             //iOutput= NULL;
	         iInput = NULL;
	         iCmdId= EMgBlankCmdId;

            }

        }

	// Fill the Error code inside Generic Param List
	TInt sapiErr = SErrNone;
    if (aError)
    	{
    	sapiErr = CMgInterface::SapiError( aError );
    	}
    
    iOutput->AppendL(TLiwGenericParam(KErrorCode,TLiwVariant((TInt32)sapiErr)));
	// if not error create the iterator class and put it into output list
	if( ( EMgRefreshComplete == aOperationEvent   )&& ( KErrNone == aError   ) )
     	{
        // Fill the Iterator in Generic Paaram List
        TLiwVariant response;

	 	// Iterator will accept the cmd Id and iListmodel and
	 	// it will become the owner of iListModel,Ownership of
	 	// Iterator is transfered to consumer

	 	CMgItemsList *iterator = CMgItemsList::NewL( aListModel, iCmdId );
 	    CleanupStack::PushL( iterator );
	 	response.Set( iterator );
		iOutput->AppendL( TLiwGenericParam ( KResponse, response ) );
 		CleanupStack::Pop( iterator );
        iterator->DecRef();
        }
   	else
   	    {
		delete aListModel;
		aListModel = NULL;
	 	}

    if( NULL != iCallBack )
     	{
    	// call callback of consumer
    	if( KErrNone ==  aError   )
    	    {
    		TRAP_IGNORE(  
    		iCallBack->HandleNotifyL 
    		( aTransactionID, KLiwEventCompleted, *iOutput,*iInput ));

    	    }
        else
            {
            iCallBack->HandleNotifyL ( aTransactionID, KLiwEventError, *iOutput,*iInput );
            }

         }

    iCmdId = EMgBlankCmdId;
    iCallBack = NULL;
    iInput=NULL;

	}


// -----------------------------------------------------------------------------
// CMgServiceObserver::SetMemberVar
// set the member varibale for the current request.
// -----------------------------------------------------------------------------
void CMgServiceObserver::SetMemberVar(const TMgCmdId& aCmdId,
        				 			  const CLiwGenericParamList* aInput,
        				 			  MLiwNotifyCallback* aCallBack)
	{

	iCmdId= EMgBlankCmdId;

	iCallBack = aCallBack;
    iInput    = aInput;
    iCmdId    = aCmdId;

	}

// -----------------------------------------------------------------------------
// CMgServiceObserver::Cancel
// Cancel the pending asynchronous request
// -----------------------------------------------------------------------------
void CMgServiceObserver::CancelL()
	{
	if( iCallBack )
	    {
	     iCallBack->HandleNotifyL ( 0,
					KLiwEventCanceled,
					*iOutput,
					*iInput );

	    iCallBack = NULL ;
        iOutput->Reset();
	    iInput = NULL;
	    iCmdId= EMgBlankCmdId;
	    }
	}


// -----------------------------------------------------------------------------
// CMgServiceObserver::CMgServiceObserver
// constructor of class
// -----------------------------------------------------------------------------

CMgServiceObserver::CMgServiceObserver()
                   :iCallBack(NULL),
                    iOutput(NULL),
					iInput(NULL),
					iCmdId(EMgBlankCmdId)
	{

	}

// -----------------------------------------------------------------------------
// CMgServiceObserver::~CMgServiceObserver
// Destructor
// -----------------------------------------------------------------------------

CMgServiceObserver::~CMgServiceObserver()
	{
    //release output Parameter List
    if ( iOutput )
	    {
	    iOutput->Reset();
	    delete iOutput;
	  	}
	}

// -----------------------------------------------------------------------------
// CMgServiceObserver::ConstructL
// Destructor
// -----------------------------------------------------------------------------

void CMgServiceObserver::ConstructL()
	{
    iOutput = CLiwGenericParamList::NewL();
	}
