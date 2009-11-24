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
* Description:  Implements location service handler (This will be part of 
*									Ecom plugin.
*
*/


#include <liwserviceifbase.h>
#include <liwcommon.h>
#include <ecom/implementationproxy.h>
#include "locationservicehandler.h"
#include "locationcb.h"
#include "locationinterface.h"

using namespace LIW;

void CLocServiceHandler::InitialiseL(MLiwNotifyCallback& /*aFrameworkCallback*/,
                                 const RCriteriaArray& aInterest)
    {
    TInt count = aInterest.Count() ;
    for (TInt i = 0; i < count; i++)
        {
        if (aInterest[i]->ContentType() == KLocationContents) 
            {
            iContentType = KLocationContents;
            return;
            }
        }
    User::Leave(KErrNotFound);
    }


/**
 * HandleServiceCmdL
 */

void CLocServiceHandler :: HandleServiceCmdL(const TInt& aCmdId,
    const CLiwGenericParamList& aInParamList,
    CLiwGenericParamList& aOutParamList,
    TUint aCmdOptions,
    const MLiwNotifyCallback* aCallback)
    {
    TRAPD(error , CmdExecuteL(aCmdId , aInParamList, aOutParamList ,aCmdOptions , aCallback)) ;

    if ( error )
		{
		TInt sapierror = CLocationInterface::ConvertToSapiError(error);
    	aOutParamList.AppendL(TLiwGenericParam(KErrorCode , TLiwVariant(sapierror))) ;	
		}
	else
		{
		aOutParamList.AppendL(TLiwGenericParam(KErrorCode , TLiwVariant(error))) ;
		}

    }

/*
 * class CLocServiceHandler
 */ 

 CLocServiceHandler* CLocServiceHandler::NewL()
{
	return new (ELeave) CLocServiceHandler();
}

/**
 * CLocServiceHandler::CmdExecuteL, this method is called by CLocServiceHandler::HandleCmdL()
 * to catch any leaves that might occur during execution of a LiwCommand.This is an private 
 * method of this class.
*/

void CLocServiceHandler::CmdExecuteL(
         		const TInt& aCmdId,
            	const CLiwGenericParamList& aInParamList,
            	CLiwGenericParamList& aOutParamList,
            	TUint /*aCmdOptions */,
            	const MLiwNotifyCallback* /*aCallback*/)
    {
    TLiwGenericParam r;
    const TLiwGenericParam* p = NULL;
    CLocationInterface *interfaceLocation ;
    aOutParamList.Reset() ;

    if (aCmdId == KLiwCmdAsStr) 
        {
        TInt pos = 0;
        p = aInParamList.FindFirst(pos, _L8("cmd")); 
        }

    if (p && (p->Value().AsData() == KLsInterfaceName)) 
        {
        
        if (iContentType == KLocationContents)
			{
			interfaceLocation  = CLocationInterface :: NewL() ;
			CleanupStack :: PushL(interfaceLocation) ;
			aOutParamList.AppendL(TLiwGenericParam(KLsInterfaceName , TLiwVariant(interfaceLocation))) ;
			
			}//End of KLocationContents
			
   		 } //End of KLsInterface

    else 
        {
        aOutParamList.AppendL(TLiwGenericParam(KErrorCode , TLiwVariant((TInt32)KErrGeneral)));
        }

    
    
    aOutParamList.AppendL(TLiwGenericParam(KErrorCode , TLiwVariant(KErrNone))) ;
    CleanupStack :: Pop (interfaceLocation) ;

    return;

    }

  
  
/**
 * @Default constructor 
*/ 

CLocServiceHandler :: CLocServiceHandler()
    {
    	;
    }

/**
 * @Default destructor 
*/ 

CLocServiceHandler :: ~CLocServiceHandler()
    {
    	;
    }

// Map the interface UIDs to implementation factory functions
const TImplementationProxy ImplementationTable[] =
    {
       
        IMPLEMENTATION_PROXY_ENTRY(0x10282CF7, CLocServiceHandler::NewL)
    };

// ---------------------------------------------------------
// Exported proxy for instantiation method resolution
// ---------------------------------------------------------
//
EXPORT_C const TImplementationProxy* ImplementationGroupProxy(TInt& aTableCount)
    {
    aTableCount = sizeof(ImplementationTable) / sizeof(TImplementationProxy);
    return ImplementationTable;
    }
