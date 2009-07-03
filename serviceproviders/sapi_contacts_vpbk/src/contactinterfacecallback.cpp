/*
* Copyright (c) 2006-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Implements the contact callback interface.
*
*/


#include <LiwCommon.h>
#include <LiwGenericParam.h>

// User Includes
#include "contactinterfacecallback.h"
#include "contactinterface.h"
#include "contacterrormessage.hrh"
#include "../../inc/serviceerrno.h"
#include "searchfields.h"

//_LIT8(KResponse,"ReturnValue");
//_LIT(KAddFieldKeyNotSupported,"Contacts : Add :Field Key Not Supported on this Database: ");
/*
-----------------------------------------------------------------------------
	CContactInterfaceCallback::CContactInterfaceCallback()
	Description             : Symbian default Constructor can NOT contain
				              any code that might leave.
    Return values           : N/A
-----------------------------------------------------------------------------
*/
CContactInterfaceCallback::CContactInterfaceCallback()
                          :iCallback(NULL),
                           iTransactionId(0),
                           iInParamList(NULL),
                           iEventParamList(NULL),
                           iContact(NULL)
    {
    }

/*
-----------------------------------------------------------------------------
    CContactInterfaceCallback::NewL()
    Description             : Two-phased constructor.
    Return values           : CContactInterfaceCallback object pointer
-----------------------------------------------------------------------------
*/
CContactInterfaceCallback* CContactInterfaceCallback::NewL()
    {
    return  new ( ELeave ) CContactInterfaceCallback();
    }
    
/*
-----------------------------------------------------------------------------
    CContactInterfaceCallback::NewL()
    Description             : Two-phased overloaded constructor.
    Return values           : CContactInterfaceCallback object pointer
-----------------------------------------------------------------------------
*/
CContactInterfaceCallback* CContactInterfaceCallback::NewL(CSingleContact* aContact)
    {
    CContactInterfaceCallback* self = new (ELeave) CContactInterfaceCallback();
    self->iContact = aContact;
    return self; 
    }
        

/*
-----------------------------------------------------------------------------
    CContactInterfaceCallback::~CContactInterfaceCallback()
    Description             : Destructor, free allocated resources
    Return values           : N/A
-----------------------------------------------------------------------------
*/
CContactInterfaceCallback::~CContactInterfaceCallback()
    {
        delete iEventParamList;
        delete iContact;
    }

/*
-----------------------------------------------------------------------------
	CContactInterfaceCallback::SetParams()
	Description             : Sets the basic params of the callback object
    Return values           : N/A
-----------------------------------------------------------------------------
*/
void CContactInterfaceCallback::SetParams( MLiwNotifyCallback* aCallback,
                                          const TInt aTransId,
                                          const CLiwGenericParamList* aInParamList )
    {
    iCallback = aCallback;
    iTransactionId = aTransId;
    iInParamList = aInParamList;
    }

/*
-----------------------------------------------------------------------------
    CContactInterfaceCallback::HandleReturnValue()
    Description             : The MContactCallback Method, is called when
                              Error  has occured.The Error is passed
                              to the consumer by appending to the CLiwGenericParamList.
    Return values           : N/A
-----------------------------------------------------------------------------
*/
void CContactInterfaceCallback::HandleReturnValue( TOperationEvent aEventId, const TInt& aError,TInt aTransId)
    {
    TInt err = 0;
    CleanupStack::PushL(this);
    if( iCallback )
        {
        if( iEventParamList )
            {
            iEventParamList->Reset();
            }
        else
            {
            iEventParamList = CLiwGenericParamList::NewL();
            }
            
		if(aEventId == EOpCancel)
    		{
    		iEventParamList->AppendL(TLiwGenericParam(KErrorCode,
    		                         TLiwVariant((TInt32)SErrCancelSuccess )));
    		//Call HandleNotify
            TRAP(err,iCallback->HandleNotifyL((TInt32)aTransId, 
                                               KLiwEventCanceled, 
                                               *iEventParamList, 
                                               *iInParamList));       		    
    		}
    	else if(aEventId == EOpError)
	    	{
	    	TInt32 sapiError = CContactInterface::SapiError(aError);
    		iEventParamList->AppendL(TLiwGenericParam( KErrorCode,
    		                         TLiwVariant((TInt32)sapiError)));
    		//Call HandleNotify
            TRAP(err,iCallback->HandleNotifyL((TInt32)aTransId, 
                                               KLiwEventError, 
                                              *iEventParamList, 
                                              *iInParamList));       		    
    		}
		else if(aEventId == EInvalidKey)
    		{
    		TPtrC8 ptr = CSearchFields::GetFieldKeyFromId(aError);
    		TBuf<25> buff;
            buff.Copy(ptr);
            TBuf<KMaxName> errmsg(KAddFieldKeyNotSupported);    		
    		errmsg.Append(buff);
    		
    		const_cast<TInt&> (aError) = KErrNotSupported;
    		TInt32 sapiError = CContactInterface::SapiError(aError);
    		
    		iEventParamList->AppendL(TLiwGenericParam( KErrorCode,
    		                         TLiwVariant((TInt32)sapiError)));
    		                         
    		iEventParamList->AppendL(TLiwGenericParam(KErrorMessage,
    		                         TLiwVariant(errmsg))); 
    		//Call HandleNotify
            TRAP(err,iCallback->HandleNotifyL((TInt32)aTransId, 
                                           KLiwEventError, 
                                           *iEventParamList, 
                                           *iInParamList));   
    		}
    	else	
    		{
	        //Append Error code
       		TInt32 sapiError = CContactInterface::SapiError(aError);
       		iEventParamList->AppendL(TLiwGenericParam( KErrorCode,
       		                         TLiwVariant( (TInt32)sapiError )));
			//Append Reason
	        	        			
    	    //Call HandleNotify
            TRAP(err,iCallback->HandleNotifyL((TInt32)aTransId, 
                                               KLiwEventCompleted, 
                                               *iEventParamList, 
                                               *iInParamList));
    		}
    		
        }
    CleanupStack::PopAndDestroy(this);
    }
/*
-----------------------------------------------------------------------------
    CContactInterfaceCallback::HandleReturnIter()
    Description             : The MContactCallback Method, is called when
                              GetList returns an iterator on a list of entries retrived.
    Return values           : N/A
-----------------------------------------------------------------------------
*/


void CContactInterfaceCallback::HandleReturnIter(const TInt& aError,
                                                 CContactIter* aIter, 
                                                 TInt aTransId)
    {
    TInt err = 0;
    CleanupStack::PushL(this);	
    if( iCallback )
        {
        if( iEventParamList )
            {
            iEventParamList->Reset();
            }
        else
            {
            iEventParamList = CLiwGenericParamList::NewL();
            }
        //Append Error Code
        TInt32 sapiError = CContactInterface::SapiError(aError);
        iEventParamList->AppendL(TLiwGenericParam( KErrorCode, 
                                 TLiwVariant((TInt32)sapiError)));
        
	if(aIter)
		{
	    CContactIterator* iterator=CContactIterator::NewL(aIter);
		CleanupStack::PushL(iterator);
		//Append Iterator in case it is valid
        iEventParamList->AppendL(TLiwGenericParam(KReturnValue, 
                                 TLiwVariant(iterator)));
        iterator->DecRef();                         
        CleanupStack::Pop(iterator);        
		}
	
		//Call HandleNotify
	    TRAP(err,iCallback->HandleNotifyL(aTransId, 
	                                      KLiwEventCompleted, 
	                                      *iEventParamList, 
	                                      *iInParamList));
    	}
    CleanupStack::PopAndDestroy(this);
    }
