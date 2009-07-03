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
* Description:  Interface to Exporting the contents of a Calender
*
*/


//System Includes
#include <e32cmn.h> 		//for RPointerArray
#include <s32file.h>
#include <calsession.h>
#include <calentryview.h>
#include <CalenExporter.h>
#include <calentryview.h>
#include <caliterator.h>

//User Include
#include "calendarheader.h"
#include "calendarconstants.h"
#include "asyncreqobserver.h"
#include "CalendarExport.h"


void CleanupCCalEntryArray(TAny* aPointer);
void CleanupCCalInstanceArray(TAny* aPointer);


//used in case of writing the temporary output while exporting the entries
_LIT(KTempFilePath,"C:\\");

//--------------------------------------------------------------------------------------------------------
// Static Method which either returns the Two Phase constructed Object or Leave 
// Used to set local copies of some of the parameters like aFormat to iFormat
//--------------------------------------------------------------------------------------------------------
//
CCalendarExport* CCalendarExport::NewL ( CCalendarSessionInfo* aCalSessionInfo, 
										 const TDesC8& aFormat, 
										 CCalendarExportParams* aParams, 
										 CAsyncRequestObserver* aAsyncRequestObserver,
										 MCalCallbackBase* aCallBack )
	{
	CCalendarExport* self = new (ELeave) CCalendarExport( aCalSessionInfo, aAsyncRequestObserver, aCallBack );
	
    CleanupStack::PushL(self);
    
    self->ConstructL( aFormat, aParams );
    
    CleanupStack::Pop( self );
    
    return self;
	}


// --------------------------------------------------------------------------------------------------------
// Destructor.
// --------------------------------------------------------------------------------------------------------
//
CCalendarExport::~CCalendarExport()
	{
	Cancel();
	
	delete iCalenExporter;
	
	delete iFormat;
	
	delete iOutputBuffer;
	
	if ( iAsyncRequestObserver )
		delete iParams;	
	}

// --------------------------------------------------------------------------------------------------------
// Synchronous Export Function which decides the flow basing on the inputs set at the time of Construction 
// of this object through NewL and generates corresponding entries in an Ouput Buffer
// --------------------------------------------------------------------------------------------------------
//
void CCalendarExport::ExportL( HBufC8*& aOutputBuffer )
	{
	if( !iParams )
			User::Leave( KErrArgument );
	
	if( iParams->Params() & CCalendarExportParams::EParamsGUid && 
			iParams->Params() & CCalendarExportParams::EParamsLUid)
		{
		User::Leave( KErrArgument );		
		}
	else if( iParams->Params() & CCalendarExportParams::EParamsGUid )
		{
		ConvertGUIDAndExportL( aOutputBuffer );
		}
	else if( iParams->Params() & CCalendarExportParams::EParamsLUid )
		{
		ConvertLUIDAndExportL( aOutputBuffer );
		}
	else
		{
		GetCalEntriesAndExportL( aOutputBuffer );
		}
	}


// --------------------------------------------------------------------------------------------------------
// ASynchronous Export Function which actually sets the ActiveObject up in the Active Schedular
// 				Exports entries basing on the input set at the time of construction of this object througn NewL
//						all the entries of the Calender(outputis passed through callback)
// --------------------------------------------------------------------------------------------------------
//
void CCalendarExport::ExportL()
	{
	if( !iAsyncRequestObserver || !iCallBack )
		User::Leave( KErrArgument );
		
	CActiveScheduler::Add ( this );
	
	ActivateRequest( KErrNone );
	}
	
	
// --------------------------------------------------------------------------------------------------------
// Constructor
// --------------------------------------------------------------------------------------------------------
//
CCalendarExport::CCalendarExport( CCalendarSessionInfo* aCalSessionInfo, CAsyncRequestObserver* aAsyncRequestObserver, 
												MCalCallbackBase* aCallBack ): 
								  					//CActive( EPriorityStandard ),
								  					iCalSessionInfo( aCalSessionInfo ),
								  					iCallBack( aCallBack ),
								  					iAsyncRequestObserver( aAsyncRequestObserver )
	{
	}
	
	
// --------------------------------------------------------------------------------------------------------
// 2nd-phased constructor of two phase construction
// NOTE: Ownership of any of the parameters is not taken through this function call
// --------------------------------------------------------------------------------------------------------
//	
void CCalendarExport::ConstructL( const TDesC8& aFormat, CCalendarExportParams* aParams )
	{	
	if ( iAsyncRequestObserver )
		{
		iParams = aParams->CloneL();
		}
	else	
		{
		iParams = aParams;
		}
	
	iFormat = aFormat.AllocL();
	
	iCalenExporter = CCalenExporter::NewL( * ( iCalSessionInfo->Session() ) );
	}

// --------------------------------------------------------------------------------------------------------
// Private Export Function which is internally called (by both Overloaded 
// synchronous functions) to export the ccalentries to OutputBuffer
// --------------------------------------------------------------------------------------------------------
//
void CCalendarExport::ExportToBufferL( const RPointerArray<CCalEntry>& aCalEntryArray , HBufC8*& aOutputBuffer )
	{
	TFileName tempFileName;
	
	TPtrC filePath( KTempFilePath );
	
	RFs fileServer;
    
    User::LeaveIfError( fileServer.Connect() );
    
    CleanupClosePushL( fileServer );
	
	//writeStream for the Export to write to
	RFileWriteStream wFileStream;
	
	wFileStream.PushL();
	
	if ( iParams->Params() & CCalendarExportParams::EParamsFileName )
		{
		User::LeaveIfError( wFileStream.Replace(fileServer, iParams->ExportFileName(), EFileWrite ));
		}
	else
		{
		//opens the temp file for reading and writing and returns its name in tempFileName
		User::LeaveIfError( wFileStream.Temp( fileServer, filePath , tempFileName , EFileWrite ));
		}
	
	TInt calEntryArrayCount = aCalEntryArray.Count();	
	
	//Step2: Exporting the Entries to wFileStream(Temporary file) 
	if ( iFormat->CompareF(KCalFmtVCal) == 0 )
		{
		for(TInt j = 0 ; j < calEntryArrayCount ; ++j )
			{			
			//As the current Implementation of ExportVCal does not support taking an array of CCalEntries at a time and 
			//returning the result in the writeStream....Only one entry is supported at a time.
			//Though it provides the overloaded functions one taking an entry at a time and the other taking array at a time
			//the One that take an array at a time Leaves if the array length is greater than 1
			
			iCalenExporter->ExportVCalL( *aCalEntryArray[j], wFileStream );
			}
		}
	else if ( iFormat->CompareF(KCalFmtICal) == 0 )
		{
		for(TInt j = 0 ; j < calEntryArrayCount ;++j )
			{			
			//As the current Implementation of ExportVCal does not support taking an array of CCalEntries at a time and 
			//returning the result in the writeStream....Only one entry is supported at a time.
			//Though it provides the overloaded functions one taking an entry at a time and the other taking array at a time
			//the One that take an array at a time Leaves if the array length is greater than 1
			
			iCalenExporter->ExportICalL( *aCalEntryArray[j], wFileStream );
			}
		}
	else
		{
		User::Leave( KErrNotSupported );
		}	
	
	wFileStream.CommitL();
	
	wFileStream.Close();
	
	wFileStream.Pop();
	
	wFileStream.Release();
	
	//wStream( temporary file ) contains the entries exported from the calender...
	//Coping the content to the aOutputBuffer

	if ( !( iParams->Params() & CCalendarExportParams::EParamsFileName ))
		{
		RFile file;
		
		TInt fileSize;
		
		User::LeaveIfError( file.Open( fileServer, tempFileName, EFileRead ));
		
	    CleanupClosePushL( file );
		
		file.Size( fileSize );

		aOutputBuffer = HBufC8::NewL( fileSize );
		
		TPtr8 temp = aOutputBuffer->Des();
		
		//reads all the contents of the temporary file into the descriptor and its length is set accoordingly
		file.Read( temp );
		
		CleanupStack::PopAndDestroy( &file );//file
		
		//deleting the temporary file using the RFs Object 
		fileServer.Delete( tempFileName );
		}
	
	CleanupStack::PopAndDestroy( &fileServer );//fileServer
	}


// --------------------------------------------------------------------------------------------------------
// Internal Function For Conversion of LocalUIDS to CCalEntry and call ExportToBuffer
// (this is called in case of Asynchronous from RUNL)
// --------------------------------------------------------------------------------------------------------
//          
void CCalendarExport::GetCalEntriesAndExportL( HBufC8*& aOutputBuffer )
	{
	
	RPointerArray<CCalEntry> calEntryArray;
	 //to store all the calendery entries correspongind to the Input LocalUID Array

	CleanupStack::PushL( TCleanupItem(CleanupCCalEntryArray, &calEntryArray) );
	
	//Step1:Retrieving all the CCalEntryArray from the Calendar

	CCalIter* calIter = CCalIter::NewL( *iCalSessionInfo->Session() );
	
	CleanupStack::PushL( calIter );
	
	TPtrC8 calEntryUID(calIter->FirstL());
	
	while( calEntryUID != KNullDesC8 )
			{
			//fetch the total array of entries at once for the first uid
			iCalSessionInfo->EntryView()->FetchL( calEntryUID , calEntryArray );
			
			calEntryUID.Set(calIter->NextL());
			}
			
	//Step2: Exporting the Entries to writeStream(Temporary file) and copying the contents to the aOutputBuffer
	
	ExportToBufferL( calEntryArray, aOutputBuffer );
	
	CleanupStack::PopAndDestroy( 2, &calEntryArray );
	}
	
	
// --------------------------------------------------------------------------------------------------------
// Internal Function For Conversion of GlobalUIDS to CCalEntry and call ExportToBuffer
// (this is called in case of Asynchronous from RUNL)
// --------------------------------------------------------------------------------------------------------
//	
void CCalendarExport::ConvertGUIDAndExportL( HBufC8*& aOutputBuffer )
	{
	RPointerArray< CCalEntry > calEntryArray; 
	//to store all the calendery entries correspongind to the Input GUID Array
	CleanupStack::PushL( TCleanupItem(CleanupCCalEntryArray, &calEntryArray) );
	
	//Step1: Generating the CCalEntryArray corresponding to input GUID(Descriptor..alpha numberic) Array
	
	TInt inputArrayCount = iParams->GuidArray()->Count();//MdcaCount(); this can also be used
	
	for ( TInt i = 0; i < inputArrayCount; ++i ) 
		{	
		iCalSessionInfo->EntryView()->FetchL( (*iParams->GuidArray())[i] , calEntryArray );
		}
		
	
	//Step2: Exporting the Entries to writeStream(Temporary file) and copying the contents to the aOutputBuffer
	
	ExportToBufferL( calEntryArray , aOutputBuffer );
	
	CleanupStack::PopAndDestroy( &calEntryArray );
	}
		

// --------------------------------------------------------------------------------------------------------
// Internal Function For Conversion of LocalUIDS to CCalEntry and call ExportToBuffer
// (this is called in case of Asynchronous from RUNL)
// --------------------------------------------------------------------------------------------------------
//          
void CCalendarExport::ConvertLUIDAndExportL( HBufC8*& aOutputBuffer )
	{
	
	RPointerArray<CCalEntry> calEntryArray; //needs this to be pushed onto the stack But little support to do this
	//to store all the calendery entries correspongind to the Input LocalUID Array
	CleanupStack::PushL( TCleanupItem(CleanupCCalEntryArray, &calEntryArray) );
	
	//Step1:Generating the CCalEntryArray corresponding to input LocalUID(unsigned int) Array
	
	TInt inputArrayCount = iParams->LocalUidArray().Count();
	
	for(TInt i = 0; i < inputArrayCount ; ++i) 
		{
		CCalEntry* entry = iCalSessionInfo->EntryView()->FetchL( iParams->LocalUidArray()[i] );
		if ( entry )
			{
			CleanupStack::PushL( entry );
			
			calEntryArray.AppendL( entry );
			
			CleanupStack::Pop( entry );
			}
		}
		
		
	//Step2: Exporting the Entries to writeStream(Temporary file) and copying the contents to the aOutputBuffer
	
	ExportToBufferL( calEntryArray, aOutputBuffer );
	
	CleanupStack::PopAndDestroy( &calEntryArray );
	}
			
// --------------------------------------------------------------------------------------------------------
// Inherited from CActive class 
// --------------------------------------------------------------------------------------------------------
//
void CCalendarExport::DoCancel()
	{
	NotifyRequestResult( KErrCancel );
	}


// --------------------------------------------------------------------------------------------------------
// Inherited from CActive class 
// --------------------------------------------------------------------------------------------------------
//
void CCalendarExport::RunL()
	{
	TInt err = iStatus.Int();

	if ( err == KErrNone )//ExportL(const TDesC8 aFormat, RArray<TUint>& aInputLocalUidArray , HBufC8*& aOutputBuffer )
		{
		TRAP( err, ExportL( iOutputBuffer ));
		}		
	NotifyRequestResult( err );		
	}
	
	
// --------------------------------------------------------------------------------------------------------
// Activates the asynchronous request
// --------------------------------------------------------------------------------------------------------
//
void CCalendarExport::ActivateRequest( TInt aReason )
	{
	iStatus = KRequestPending;
	
	SetActive();
	
	TRequestStatus* temp = &iStatus;
	
	User::RequestComplete( temp, aReason );
	}


// --------------------------------------------------------------------------------------------------------
// Notifies callback the result for asynchronous request.
// --------------------------------------------------------------------------------------------------------
//
void CCalendarExport::NotifyRequestResult( TInt aReason )
	{
	if ( iCallBack )
		{
		iAsyncRequestObserver->RequestComplete( iCallBack->iTransactionId );
		
		TRAPD( err, iCallBack->NotifyResultL( aReason, ( TAny * )( iOutputBuffer )));
		}
	
	// caller will delete the object in case of cancel
	if ( aReason != KErrCancel )
		delete this;
	}
