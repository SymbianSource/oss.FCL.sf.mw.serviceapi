/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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


//System Includes
#include <e32cmn.h> 			//for RPointerArray
#include <calsession.h>			//For CCalSession
#include <calentryview.h>
#include <CalenImporter.h>
#include <CalenInterimUtils2.h>
#include <s32mem.h>
#include <s32file.h>

//User Include
#include "calendarheader.h"
#include "calendarconstants.h"
#include "asyncreqobserver.h"
#include "calendarimport.h"



void CleanupCCalEntryArray(TAny* aPointer);
void CleanupCCalInstanceArray(TAny* aPointer);

// --------------------------------------------------------------------------------------------------------
// Static Method which either returns the Two Phase constructed Object or Leave 
// NOTE: Ownership of any of the parameters is not taken through this function call
// NOTE: Therefore the User of this function needs to take care of neccessary cleanup of passed parameters
// --------------------------------------------------------------------------------------------------------
//
CCalendarImport* CCalendarImport::NewL ( CCalendarSessionInfo* aCalSessionInfo, 
											const TDesC8& aFormat, 
											const TDesC8& aInputBuffer, 
											CAsyncRequestObserver* aAsyncRequestObserver,
											MCalCallbackBase* aCallBack )
	{
	CCalendarImport* self = new (ELeave) CCalendarImport( aCalSessionInfo, aAsyncRequestObserver, aCallBack );
	
    CleanupStack::PushL(self);
    
    self->ConstructL( aFormat, aInputBuffer );
    
    CleanupStack::Pop(self); 
    
    return self;
	}	

// --------------------------------------------------------------------------------------------------------
// Static Method which either returns the Two Phase constructed Object or Leave 
// NOTE: Ownership of any of the parameters is not taken through this function call
// NOTE: Therefore the User of this function needs to take care of neccessary cleanup of passed parameters
// --------------------------------------------------------------------------------------------------------
//
CCalendarImport* CCalendarImport::NewL ( CCalendarSessionInfo* aCalSessionInfo, 
											const TDesC8& aFormat, 
											const TDesC& aImportFile, 
											CAsyncRequestObserver* aAsyncRequestObserver,
											MCalCallbackBase* aCallBack )
	{
	CCalendarImport* self = new (ELeave) CCalendarImport( aCalSessionInfo, aAsyncRequestObserver, aCallBack );
	
    CleanupStack::PushL(self);
    
    self->ConstructL( aFormat, aImportFile );
    
    CleanupStack::Pop(self); 
    
    return self;
	}	

	
// --------------------------------------------------------------------------------------------------------
// Destructor.
// --------------------------------------------------------------------------------------------------------
//
CCalendarImport::~CCalendarImport()
	{
	Cancel();	
	
	delete iCalenImporter;
	
	delete iFormat;
	
	delete iInputBuffer;
	
	delete iImportFile;
	
	iOutputUIDArray.ResetAndDestroy();
	}
	
// --------------------------------------------------------------------------------------------------------
// Synchronous Version of Import which takes InputBuffer set at the time of Construction of this object
// and Imports them to the Calender opened in CalSession of CalendarSessionInfoL object passed to this object
// It sets the LUids and GUids in the aOutputLocalUidArray, this object is not the owner of aOutputLocalUidArray
// --------------------------------------------------------------------------------------------------------
//
void CCalendarImport::ImportL( RPointerArray<TUIDSet>& aOutputUIDArray )
	{
	if ( iInputBuffer )
		{
		RDesReadStream rStream( *iInputBuffer );
		
	    CleanupClosePushL( rStream );
	    
	    ImportFromStreamL(rStream, aOutputUIDArray);

		CleanupStack::PopAndDestroy( &rStream );
		}
	else
		{
		RFs rfs;
		User::LeaveIfError( rfs.Connect() );
		CleanupClosePushL( rfs );
		
		RFile file;
		User::LeaveIfError( file.Open( rfs, *iImportFile, EFileRead ));
		CleanupClosePushL( rfs );
		
		RFileReadStream rStream( file );
		CleanupClosePushL( rStream );

	    ImportFromStreamL(rStream, aOutputUIDArray);
		
		CleanupStack::PopAndDestroy( 3 , &rfs );
		}
	}

// --------------------------------------------------------------------------------------------------------
// Synchronous Version of Import which takes InputStream set at the time of Construction of this object
// and Imports them to the Calender opened in CalSession of CalendarSessionInfoL object passed to this object
// It sets the LUids and GUids in the aOutputLocalUidArray, this object is not the owner of aOutputLocalUidArray
// --------------------------------------------------------------------------------------------------------
//	
void CCalendarImport::ImportFromStreamL(RReadStream& aStream,  RPointerArray<TUIDSet>& aOutputUIDArray )
	{
	RPointerArray<CCalEntry> outputCalEntryArray;

	CleanupStack::PushL( TCleanupItem(CleanupCCalEntryArray, &outputCalEntryArray) );
	
	if ( iFormat->CompareF(KCalFmtVCal) == 0 )
		{
		iCalenImporter->ImportVCalendarL( aStream, outputCalEntryArray );
		}
	else if ( iFormat->CompareF(KCalFmtICal) == 0 )
		{
		iCalenImporter->ImportICalendarL( aStream, outputCalEntryArray );
		}
	else
		User::Leave( KErrNotSupported );	
	
	TInt count = outputCalEntryArray.Count();
	
	for ( TInt index = 0; index < count; index ++ )
		{
		CCalenInterimUtils2::StoreL( *iCalSessionInfo->EntryView() , *outputCalEntryArray[index] );
		
		TUIDSet* newUid = new(ELeave) TUIDSet;
		
		CleanupStack::PushL( newUid );
		
		newUid->iLocalUID = outputCalEntryArray[index]->LocalUidL();
		
		newUid->iGlobalUID = outputCalEntryArray[index]->UidL().AllocL();
		
		aOutputUIDArray.AppendL( newUid );
		
		CleanupStack::Pop( newUid );
		}
	
	CleanupStack::PopAndDestroy( &outputCalEntryArray );
	}
	


// --------------------------------------------------------------------------------------------------------
// ASynchronous Version of Import which takes InputBuffer set at the time of Construction of this object through NewL
//                     and Imports to the Calender(outputis passed through callback)
// --------------------------------------------------------------------------------------------------------	
//
void CCalendarImport::ImportL()
	{
	if( !iCallBack || !iAsyncRequestObserver ) //if any of the async handlers are not set then leave
		User::Leave( KErrArgument );
	
	CActiveScheduler::Add ( this );
	
	ActivateRequest( KErrNone );
	}


	
// --------------------------------------------------------------------------------------------------------
// Constructor.
// --------------------------------------------------------------------------------------------------------
//
CCalendarImport::CCalendarImport( CCalendarSessionInfo* aCalSessionInfo, 
									CAsyncRequestObserver* aAsyncRequestObserver,
									MCalCallbackBase* aCallBack ): 
															//CActive( EPriorityStandard ),
														  	iCalSessionInfo(aCalSessionInfo),
														  	iCallBack( aCallBack ),
														  	iAsyncRequestObserver(aAsyncRequestObserver)
	{

	}
	
	
// --------------------------------------------------------------------------------------------------------
// 2nd-phased constructor of two phase construction
// --------------------------------------------------------------------------------------------------------
//
void CCalendarImport::ConstructL( const TDesC8& aFormat, const TDesC8& aInputBuffer )
	{	
	//instantiating the iCalDataExchange handle
	iCalenImporter=CCalenImporter::NewL(*(iCalSessionInfo->Session()));

	iFormat = aFormat.AllocL();
	
	iInputBuffer = aInputBuffer.AllocL();
	
	}

void CCalendarImport::ConstructL( const TDesC8& aFormat, const TDesC& aImportFile )
	{	
	//instantiating the iCalDataExchange handle
	iCalenImporter=CCalenImporter::NewL(*(iCalSessionInfo->Session()));

	iFormat = aFormat.AllocL();
	
	iImportFile = aImportFile.AllocL();
	
	}


// ---------------------------------------------------------------------------
// Inherited from CActive class 
// ---------------------------------------------------------------------------
//
void CCalendarImport::DoCancel()
	{
	NotifyRequestResult( KErrCancel );
	}

// ---------------------------------------------------------------------------
// Inherited from CActive class 
// ---------------------------------------------------------------------------
//
void CCalendarImport::RunL()
	{
	TInt err = iStatus.Int();

	if ( err == KErrNone )
		{
		TRAP( err, ImportL( iOutputUIDArray ));
		}

	NotifyRequestResult( err );		
	}

	
// ---------------------------------------------------------------------------
// Activates the asynchronous request
// ---------------------------------------------------------------------------
//
void CCalendarImport::ActivateRequest( TInt aReason )
	{
	iStatus = KRequestPending;
	
	SetActive();
	
	TRequestStatus* temp = &iStatus;
	
	User::RequestComplete( temp, aReason );
	}


// ---------------------------------------------------------------------------
// Notifies callback the result for asynchronous request.
// ---------------------------------------------------------------------------
//
void CCalendarImport::NotifyRequestResult( TInt aReason )
	{
	if ( iCallBack )
		{
		iAsyncRequestObserver->RequestComplete( iCallBack->iTransactionId );
		
		TRAPD( err, iCallBack->NotifyResultL( aReason, ( TAny * )( & iOutputUIDArray )));

		}
	
	// caller will delete the object in case of cancel
	if ( aReason != KErrCancel )
		delete this;
	}
