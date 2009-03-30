/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  
*
*/

#include "calendarcallback.h"
#include "calendarconstants.h"
#include "calendarinterface.h"

// ---------------------------------------------------------------------------
// Two-phase Constructor
// ---------------------------------------------------------------------------
//
CCalCallbackBaseBuffer* CCalCallbackBaseBuffer::NewL( MLiwNotifyCallback *aPtrNotifyCallback, 
													const CLiwGenericParamList& aPtrInParamList, 
													TInt32 aTransactionId  )
	{
	return new (ELeave)	CCalCallbackBaseBuffer( aPtrNotifyCallback, aPtrInParamList, aTransactionId );
	}
	
// ---------------------------------------------------------------------------
//  Constructor
// ---------------------------------------------------------------------------
//	
CCalCallbackBaseBuffer::CCalCallbackBaseBuffer( MLiwNotifyCallback *aPtrNotifyCallback, 
													const CLiwGenericParamList& aPtrInParamList, 
													TInt32 aTransactionId  )
	{
	iPtrNotifyCallback = aPtrNotifyCallback; 
	iPtrInParamList = &aPtrInParamList;
	iTransactionId = aTransactionId;
	}
	
// ---------------------------------------------------------------------------
// Gives the result of asynchronous SAPI for Export
// ---------------------------------------------------------------------------
//
void CCalCallbackBaseBuffer::NotifyResultL( TInt aErrCode, TAny* aResult )
	{
	CleanupStack::PushL( this );

	CLiwGenericParamList* outParams = CLiwGenericParamList::NewL();

	CleanupStack::PushL( outParams );

	outParams->AppendL( TLiwGenericParam(KErrorCode, 
							TLiwVariant(CCalendarInterface::ErrCodeConversion(aErrCode))));		

	// Will be NULL if exported to file
	if ( aResult )
		{
		outParams->AppendL( TLiwGenericParam( KReturnValue, TLiwVariant( *(HBufC8*)aResult ) ) );
		}
	
	TInt event = KLiwEventCompleted;
	
	if ( aErrCode == KErrCancel )
		{
		event = KLiwEventCanceled;
		}
	else if ( aErrCode != KErrNone )
		{
		event = KLiwEventStopped;
		outParams->AppendL( TLiwGenericParam(KErrorMessage, 
							TLiwVariant(_L("Calendar:Export:Error exporting entries"))));		
		}

	((MLiwNotifyCallback*)iPtrNotifyCallback)->HandleNotifyL( iTransactionId, 
												 event, 
												 *outParams, 
												 *((CLiwGenericParamList*)iPtrInParamList) ); 
											 
	CleanupStack::PopAndDestroy( 2, this );
	}
	

// ---------------------------------------------------------------------------
// Two-phase Constructor
// ---------------------------------------------------------------------------
//
CCalCallbackBaseUIDSet* CCalCallbackBaseUIDSet::NewL( MLiwNotifyCallback *aPtrNotifyCallback, 
												const CLiwGenericParamList& aPtrInParamList, 
												TInt32 aTransactionId  )
	{
	return new (ELeave)	CCalCallbackBaseUIDSet( aPtrNotifyCallback, aPtrInParamList, aTransactionId );
	}
	
// ---------------------------------------------------------------------------
//  Constructor
// ---------------------------------------------------------------------------
//	
CCalCallbackBaseUIDSet::CCalCallbackBaseUIDSet( MLiwNotifyCallback *aPtrNotifyCallback, 
												const CLiwGenericParamList& aPtrInParamList, 
												TInt32 aTransactionId )
	{
	iPtrNotifyCallback = aPtrNotifyCallback; 
	iPtrInParamList = &aPtrInParamList;
	iTransactionId = aTransactionId;
	}
	
// ---------------------------------------------------------------------------
// Gives the result of asynchronous SAPI for Import
// ---------------------------------------------------------------------------
//
void CCalCallbackBaseUIDSet::NotifyResultL( TInt aErrCode, TAny* aResult )
	{
	CleanupStack::PushL( this );
	
	CLiwGenericParamList* outParams = CLiwGenericParamList::NewL();

	CleanupStack::PushL( outParams );

	outParams->AppendL(TLiwGenericParam(KErrorCode, 
							TLiwVariant(CCalendarInterface::ErrCodeConversion(aErrCode))));		

	CCalendarInterface::SetImportOutputL( *(RPointerArray<TUIDSet>*)( aResult ), *outParams );	
		
	TInt event = KLiwEventCompleted;
	
	if ( aErrCode == KErrCancel )
		{
		event = KLiwEventCanceled;
		}
	else if ( aErrCode != KErrNone )
		{
		event = KLiwEventStopped;
		outParams->AppendL( TLiwGenericParam(KErrorMessage, 
							TLiwVariant(_L("Calendar:Import:Error importing entries"))));		
		}

	((MLiwNotifyCallback*)iPtrNotifyCallback)->HandleNotifyL( iTransactionId, 
												 event, 
												 *outParams, 
												 *((CLiwGenericParamList*)iPtrInParamList) ); 
											 
	CleanupStack::PopAndDestroy( 2, this );
	}


// ---------------------------------------------------------------------------
// Two-phase Constructor
// ---------------------------------------------------------------------------
//
CCalCallbackInt* CCalCallbackInt::NewL( MLiwNotifyCallback *aPtrNotifyCallback, 
													const CLiwGenericParamList& aPtrInParamList, 
													TInt32 aTransactionId  )
	{
	return new (ELeave)	CCalCallbackInt( aPtrNotifyCallback, aPtrInParamList, aTransactionId );
	}
	
// ---------------------------------------------------------------------------
//  Constructor
// ---------------------------------------------------------------------------
//	
CCalCallbackInt::CCalCallbackInt( MLiwNotifyCallback *aPtrNotifyCallback, 
													const CLiwGenericParamList& aPtrInParamList, 
													TInt32 aTransactionId  )
	{
	iPtrNotifyCallback = aPtrNotifyCallback; 
	iPtrInParamList = &aPtrInParamList;
	iTransactionId = aTransactionId;
	}
	
// ---------------------------------------------------------------------------
// Gives the result of asynchronous SAPI for Delete
// ---------------------------------------------------------------------------
//
void CCalCallbackInt::NotifyResultL( TInt aErrCode, TAny* /*aResult*/ )
	{
	CleanupStack::PushL( this );

	CLiwGenericParamList* outParams = CLiwGenericParamList::NewL();

	CleanupStack::PushL( outParams );

	outParams->AppendL( TLiwGenericParam( KErrorCode, 
							TLiwVariant( CCalendarInterface::ErrCodeConversion( aErrCode ))));		

	TInt event = KLiwEventCompleted;
	
	if ( aErrCode == KErrCancel )
		{
		event = KLiwEventCanceled;
		}
	else if ( aErrCode != KErrNone )
		{
		event = KLiwEventStopped;
		outParams->AppendL( TLiwGenericParam(KErrorMessage, 
							TLiwVariant(_L("Calendar:Delete:Error deleting entries"))));		
		}

	((MLiwNotifyCallback*)iPtrNotifyCallback)->HandleNotifyL( iTransactionId, 
												 event, 
												 *outParams, 
												 *((CLiwGenericParamList*)iPtrInParamList) ); 
											 
	CleanupStack::PopAndDestroy( 2, this );
	}


// ---------------------------------------------------------------------------
// Two-phase Constructor
// ---------------------------------------------------------------------------
//
CCalCallbackChangeNotify* CCalCallbackChangeNotify::NewL( MLiwNotifyCallback *aPtrNotifyCallback, 
													const CLiwGenericParamList& aPtrInParamList, 
													TInt32 aTransactionId  )
	{
	return new (ELeave)	CCalCallbackChangeNotify( aPtrNotifyCallback, aPtrInParamList, aTransactionId );
	}
	
// ---------------------------------------------------------------------------
//  Constructor
// ---------------------------------------------------------------------------
//	
CCalCallbackChangeNotify::CCalCallbackChangeNotify( MLiwNotifyCallback *aPtrNotifyCallback, 
													const CLiwGenericParamList& aPtrInParamList, 
													TInt32 aTransactionId  )
	{
	iPtrNotifyCallback = aPtrNotifyCallback; 
	iPtrInParamList = &aPtrInParamList;
	iTransactionId = aTransactionId;
	}
	
// ---------------------------------------------------------------------------
// Gives the result of asynchronous SAPI for Change Notification
// ---------------------------------------------------------------------------
//
void CCalCallbackChangeNotify::NotifyResultL( TInt aErrCode, TAny* aResult )
	{
	CleanupStack::PushL( this );

	CLiwGenericParamList* outParams = CLiwGenericParamList::NewL();

	CleanupStack::PushL( outParams );

	outParams->AppendL( TLiwGenericParam(KErrorCode, 
							TLiwVariant( CCalendarInterface::ErrCodeConversion( aErrCode ))));	
						
	if ( aResult )
		{
		RArray<TCalChangeEntry>& outputChangeSet = *((RArray<TCalChangeEntry>*)aResult);
		CCalendarInterface::SetNotifyOutputL( outputChangeSet, *outParams );	
		}
		
	TInt event = KLiwEventInProgress;
	
	if ( aErrCode == KErrCancel )
		{
		event = KLiwEventCanceled;
		}
	else if ( aErrCode != KErrNone )
		{
		event = KLiwEventCompleted;
		outParams->AppendL( TLiwGenericParam(KErrorMessage, 
							TLiwVariant(_L("Calendar:RequestNotification:Notification stopped"))));		
		}

	((MLiwNotifyCallback*)iPtrNotifyCallback)->HandleNotifyL( iTransactionId, 
												 event, 
												 *outParams, 
												 *((CLiwGenericParamList*)iPtrInParamList) ); 
											 
	CleanupStack::PopAndDestroy( outParams );

	// Only in case of cancel the object is no more required
	if ( aErrCode == KErrCancel || event == KLiwEventCompleted )
		{
		CleanupStack::PopAndDestroy( this );
		}
	else
		{
		CleanupStack::Pop( this );
		}
	}
	

