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
* Description:  Implements logging service handler (This will be part of 
*									Ecom plugin.
*
*/

#include <liwserviceifbase.h>
#include <liwcommon.h>
#include <logwrap.h>
#include <ecom/implementationproxy.h>
#include "logclientchangeobserver.h"
#include "logiter.h"
#include "loggingservicehandler.h"
#include "logginginterface.h"

/**
* @Default constructor 
*/ 
CLogServiceHandler :: CLogServiceHandler()
    {
    }

/**
* @Default destructor 
*/ 
CLogServiceHandler :: ~CLogServiceHandler()
    {
    }

/**
* Two phased constructor implementation
*/
EXPORT_C CLogServiceHandler* CLogServiceHandler :: NewL()
    {
    CLogServiceHandler* self = CLogServiceHandler::NewLC();
    CleanupStack::Pop(self);
    return self; 
    }

/**
* Two phased constructor implementation
*/
CLogServiceHandler* CLogServiceHandler :: NewLC() 
    {
    CLogServiceHandler* self = new (ELeave) CLogServiceHandler();
    CleanupStack::PushL(self);
    return self;
    }

/**
* Called by the AIW framework to initialise provider with necessary information 
* from the Service Handler. This method is called when the consumer makes 
* the attach operation.         
*
* @param aFrameworkCallback callback handle function
* @param aInterest consumer application's intrest
*/
void CLogServiceHandler::InitialiseL( MLiwNotifyCallback& /*aFrameworkCallback*/,
                                      const RCriteriaArray& aInterest )
    {
    TInt count = aInterest.Count() ;
    for ( TInt i = 0; i < count; i++ )
        {
        if ( aInterest[i]->ContentType() == KLoggingContents ) 
            {
            iContentType = KLoggingContents;
            return;
            }
        }
    User::Leave( KErrNotFound );
    }

/**
* Executes generic service commands included in criteria, derived from CLiwServiceIfBase
* 
* @param aCmdId Command to be executed.
* @param aInParamList Input parameters, can be an empty list.
* @param aOutParamList Output parameters, can be an empty list.
* @param aCmdOptions Options for the command, see KLiwOpt* in LiwCommon.hrh.
* @param aCallback Callback for asynchronous command handling, parameter checking, etc.
*/
void CLogServiceHandler :: HandleServiceCmdL( const TInt& aCmdId,
                                              const CLiwGenericParamList& aInParamList,
                                              CLiwGenericParamList& aOutParamList,
                                              TUint aCmdOptions,
                                              const MLiwNotifyCallback* aCallback )
    {
    TRAPD( error , CmdExecuteL( aCmdId , aInParamList, aOutParamList ,aCmdOptions , aCallback ) ) ;
    
    if ( error )
    	{
    	TInt sapierror = CLoggingInterface::ConvertToSapiError( error );
    	aOutParamList.AppendL( TLiwGenericParam( KErrorCode , TLiwVariant( sapierror ) ) ) ;	
    	}
    else
    	{
    	aOutParamList.AppendL( TLiwGenericParam( KErrorCode , TLiwVariant( error ) ) ) ;
    	}
    }

/**
* CLogServiceHandler::CmdExecuteL, this method is called by CLogServiceHandler::HandleCmdL()
* to catch any leaves that might occur during execution of a LiwCommand. 
*/
void CLogServiceHandler::CmdExecuteL( const TInt& aCmdId,
        	                          const CLiwGenericParamList& aInParamList,
        	                          CLiwGenericParamList& aOutParamList,
        	                          TUint /*aCmdOptions */,
        	                          const MLiwNotifyCallback* /*aCallback*/ )
    {
    TLiwGenericParam r;
    const TLiwGenericParam* p = NULL;
    CLoggingInterface *interfaceLogging ;
    aOutParamList.Reset() ;
    
    if ( aCmdId == KLiwCmdAsStr ) 
        {
        TInt pos = 0;
        p = aInParamList.FindFirst(pos, _L8("cmd")); 
        }
    
    if ( p && ( p->Value().AsData() == KDsInterfaceName ) ) 
        {
        if ( iContentType == KLoggingContents )
    		{
    		interfaceLogging  = CLoggingInterface :: NewL() ;
    		CleanupStack :: PushL( interfaceLogging ) ;
    		aOutParamList.AppendL(TLiwGenericParam(KDsInterfaceName , TLiwVariant(interfaceLogging))) ;
    		}//End of KLoggingContents
    	} //End of KLsInterface
    
    else 
        {
        aOutParamList.AppendL(TLiwGenericParam(KErrorCode , TLiwVariant((TInt32)KErrGeneral)));
        aOutParamList.AppendL(TLiwGenericParam(KErrorMessage,TLiwVariant(KInterfaceMissing())));
        }
      
    aOutParamList.AppendL( TLiwGenericParam( KErrorCode , TLiwVariant( KErrNone ) ) ) ;
    CleanupStack :: Pop ( interfaceLogging ) ;
        
    return;
    }

/**
*   Map the interface UIDs to implementation factory functions
*/       
const TImplementationProxy ImplementationTable[] =
{
IMPLEMENTATION_PROXY_ENTRY( 0x2000CFC1, CLogServiceHandler::NewL )
};

/**
*  Exported proxy for instantiation method resolution
*/   
EXPORT_C const TImplementationProxy* ImplementationGroupProxy( TInt& aTableCount )
    {
    aTableCount = sizeof( ImplementationTable ) / sizeof( TImplementationProxy );
    return ImplementationTable;
    }
