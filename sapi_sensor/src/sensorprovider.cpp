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
* Description:   Loads the sensor service
*
*/


#include <ecom/ImplementationProxy.h>
#include "sensorservicehandler.h"
#include "sensorinterface.h"
#include "serviceerrno.h"
#include "sensorcallback.h"
//Constant for sensor servicecommand.
_LIT8( KIfaceSensor , "ISensor" );
_LIT8( KCmdId , "cmd" );

using namespace LIW;

/*
-----------------------------------------------------------------------------
    CSensorProvider::CSensorProvider()
    Description          : Constructor
    Return values        : N/A
-----------------------------------------------------------------------------
*/
CSensorProvider::CSensorProvider()                     
    {

    }
/*
-----------------------------------------------------------------------------
    CSensorProvider* CSensorProvider::NewL()
    Description                                 : Two-phased constructor.
    Return values                               : CSensorProvider object pointer
-----------------------------------------------------------------------------
*/
CSensorProvider* CSensorProvider::NewL()
    {
    return new( ELeave ) CSensorProvider();
    }
/*
-----------------------------------------------------------------------------
    CSensorProvider::~CSensorProvider()
    Description          : Destructor, free allocated resources
    Return values        : N/A
-----------------------------------------------------------------------------
*/
CSensorProvider::~CSensorProvider()
    {
    }
/*
-----------------------------------------------------------------------------
    void CSensorProvider::InitialiseL()
    Description               : CLiwServiceIfBase Method called by Liw Framework
                                when AttachL is called.
    Return values             : N/A
-----------------------------------------------------------------------------
*/
void CSensorProvider::InitialiseL( MLiwNotifyCallback& /*aFrameworkCallback*/,
                                   const RCriteriaArray& /*aInterest*/ )
    {
    // Not needed.
    }

/*
-----------------------------------------------------------------------------
    void CSensorProvider::HandleServiceCmdL()
    Description               : CLiwServiceIfBase Method called by Liw Framework.
                                Executes generic service commands included in criteria.
    Return values             : N/A
-----------------------------------------------------------------------------
*/
void CSensorProvider::HandleServiceCmdL( const TInt& aCmdId,
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
        cmd = aInParamList.FindFirst( pos , KCmdId );
        if ( NULL != cmd )
            {
            lCmdName.Set( cmd->Value().AsData() );
            }
        }
    if( lCmdName.CompareF( KIfaceSensor ) == 0 )    
        {
        //Create interface pointer and return the output param
        result.SetNameL( KIfaceSensor );
        interface = CSensorInterface::NewL();
        CleanupStack::PushL( interface );
        result.Value().Set( interface );
        }
    else
        {
		result.SetSemanticId( EGenericParamError );
		result.Value().Set( (TInt32) SErrInvalidServiceArgument );
        }

	aOutParamList.AppendL( result );
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
    	//need to change this UID
    IMPLEMENTATION_PROXY_ENTRY( 0x2000CFBE, CSensorProvider::NewL )
    };

/*
 ---------------------------------------------------------
 Exported proxy for instantiation method resolution
 ---------------------------------------------------------
*/
EXPORT_C const TImplementationProxy* ImplementationGroupProxy(TInt& aTableCount)
    {
    aTableCount = sizeof( ImplementationTable ) / sizeof( TImplementationProxy );
    return ImplementationTable;
    }


