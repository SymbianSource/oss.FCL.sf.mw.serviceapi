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
* Description:   Loads the contact service
*
*/


#include <ecom/ImplementationProxy.h>
#include "contactprovider.h"
#include "contactinterface.h"
#include "../../inc/serviceerrno.h"
#include "contacterrormessage.hrh"


//Constant for contact servicecommand.
_LIT8( KIfaceContact, "IDataSource" );
_LIT8( KCmdId, "cmd" );

using namespace LIW;

/*
-----------------------------------------------------------------------------
    CContactProvider::CContactProvider()
    Description          : Constructor
    Return value        : N/A
-----------------------------------------------------------------------------
*/
CContactProvider::CContactProvider()                     
    {

    }
/*
-----------------------------------------------------------------------------
    CContactProvider* CContactProvider::NewL()
    Description                                 : Two-phased constructor.
    Return value                               : CContactProvider object pointer
-----------------------------------------------------------------------------
*/
CContactProvider* CContactProvider::NewL()
    {
    return new(ELeave) CContactProvider();
    }
/*
-----------------------------------------------------------------------------
    CContactProvider::~CContactProvider()
    Description          : Destructor, free allocated resources
    Return value        : N/A
-----------------------------------------------------------------------------
*/
CContactProvider::~CContactProvider()
    {
    }
/*
-----------------------------------------------------------------------------
    void CContactProvider::InitialiseL()
    Description               : CLiwServiceIfBase Method called by AIW Framework
                                when AttachL is called.
    Return value             : N/A
-----------------------------------------------------------------------------
*/
void CContactProvider::InitialiseL( MLiwNotifyCallback& /*aFrameworkCallback*/,
                                         const RCriteriaArray& /*aInterest*/ )
    {
    // Not needed.
    }

/*
-----------------------------------------------------------------------------
    void CContactProvider::HandleServiceCmdL()
    Description               : CLiwServiceIfBase Method called by AIW Framework.
                                Executes generic service commands included in criteria.
    Return value             : N/A
-----------------------------------------------------------------------------
*/
void CContactProvider::HandleServiceCmdL( const TInt& aCmdId,
                                               const CLiwGenericParamList& aInParamList,
                                               CLiwGenericParamList& aOutParamList,
                                               TUint /*aCmdOptions*/,
                                               const MLiwNotifyCallback* /*aCallback*/ )
    {

    TPtrC8 lCmdName;
    TLiwGenericParam result;
    const TLiwGenericParam* cmd = NULL;
    MLiwInterface* interface = NULL;

    if ( aCmdId == KLiwCmdAsStr )
        {
        TInt pos = 0;
        cmd = aInParamList.FindFirst( pos, KCmdId );
        if ( NULL != cmd )
            {
            lCmdName.Set( cmd->Value().AsData() );
            }
       	else
       	    {
       	     aOutParamList.AppendL(
  	         TLiwGenericParam( KErrorCode, TLiwVariant( TInt32( SErrServiceNotSupported ) ) ) );
  	         aOutParamList.AppendL(TLiwGenericParam( KErrorMessage, TLiwVariant( KInterfaceNameMissing ) ) );
       	    }
 
        }
    else
        {
         aOutParamList.AppendL(
         TLiwGenericParam(KErrorCode, TLiwVariant( TInt32( SErrServiceNotSupported ) ) ) );
         aOutParamList.AppendL(TLiwGenericParam( KErrorMessage, TLiwVariant( KCommandNotSupported ) ) );
        }

    if( lCmdName.CompareF( KIfaceContact ) == 0 )
        {
        //Create interface pointer and return the output param
        result.SetNameL( KIfaceContact );
        interface = CContactInterface::NewL();
        CleanupStack::PushL( interface );
        result.Value().Set( interface );
        }
    else
        {
		result.SetSemanticId( EGenericParamError );
		result.Value().Set( (TInt32)SErrNotFound );
        }
	aOutParamList.AppendL( result );
    aOutParamList.AppendL(
  	     TLiwGenericParam( KErrorCode, TLiwVariant( TInt32( SErrServiceNotSupported ) ) ) );
  	     
  	aOutParamList.AppendL(TLiwGenericParam( KErrorMessage, TLiwVariant( KInterfaceNotSupported ) ) );

	if( interface )
    	{
    	CleanupStack::Pop( interface );    
    	}
	result.Reset();
	return;
    }

// Map the interface UIDs to implementation factory functions
const TImplementationProxy ImplementationTable[] =
    {
    IMPLEMENTATION_PROXY_ENTRY( 0x10282CF5, CContactProvider::NewL )
    };

/*
 ---------------------------------------------------------
 Exported proxy for instantiation method resolution
 ---------------------------------------------------------
*/
EXPORT_C const TImplementationProxy* ImplementationGroupProxy(TInt& aTableCount)
    {
    aTableCount = sizeof(ImplementationTable) / sizeof(TImplementationProxy);
    return ImplementationTable;
    }


