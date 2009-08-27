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


#include <e32base.h>
#include <e32def.h>


#include "serviceerrno.h"
#include "calendarheader.h"
#include "entryattributes.h"
#include "calendarservice.h"
#include "calendarinterface.h"
#include "calendarcallback.h"
#include "calendariterableimpl.h"

using namespace LIW;

// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CCalendarInterface* CCalendarInterface::NewL()
	{
  	CCalendarInterface* self = new (ELeave) CCalendarInterface();
  	CleanupStack::PushL( self );
  	self->ConstructL();
  	CleanupStack::Pop( self );
	return self;
	}
// ---------------------------------------------------------------------------
// Destructor.
// ---------------------------------------------------------------------------
//	
CCalendarInterface::~CCalendarInterface()
	{
	TInt count = iArrayCalEntryList.Count();
	for(TInt index = 0; index < count; index++ )
		{
		iArrayCalEntryList[index]->SetResourceFree();
		}
		
	iArrayCalEntryList.Reset();
	delete iCalService;
	delete iErrorMessage;
	}

// ---------------------------------------------------------------------------
// Constructor
// ---------------------------------------------------------------------------
//
CCalendarInterface::CCalendarInterface()
	{
	}

// ---------------------------------------------------------------------------
// Symbian Constructor
// ---------------------------------------------------------------------------
//	
void CCalendarInterface::ConstructL()
	{
	iCalService = CCalendarService::NewL();	
	}

// ---------------------------------------------------------------------------
//  Executes the SAPI as per params
// ---------------------------------------------------------------------------
//
void CCalendarInterface::ExecuteCmdL( const TDesC8& aCmdName,
					                       const CLiwGenericParamList& aInParamList,
					                       CLiwGenericParamList& aOutParamList,
					                       TUint aCmdOptions,
					                       MLiwNotifyCallback* aCallback )
	{
	TInt errcode = KErrNotSupported;
	TInt32 transactionId = -1;
	
	aOutParamList.AppendL(TLiwGenericParam( KErrorCode, 
							TLiwVariant( ErrCodeConversion( KErrNone ))));

	TBool posBased;

	TPtrC contentType = GetContentType( aInParamList, posBased );
	
	if ( ( contentType.CompareF( KContentCalendar ) != 0 ) && 
			( contentType.CompareF( KContentCalendarEntry ) != 0 ) && 
			( aCmdName.CompareF( KCmdCancel ) != 0) )
		{
		errcode = KErrArgument;
		AppendErrorMessageL( aCmdName, KContentType, KInvalid );
		}

	else if (( aCallback && !( KLiwOptASyncronous & aCmdOptions )) || 
				( !aCallback && ( KLiwOptASyncronous & aCmdOptions )) )
		{
		errcode = KErrArgument;
		AppendErrorMessageL(aCmdName, KNullDesC8, _L("Insufficent arguments for asynchronous request"));
		}
		
	else if ( aCmdName.CompareF( KCmdAdd ) == 0 ) 
		{
		if( !aCallback )
			{
			if ( contentType.CompareF( KContentCalendar ) == 0 )
				{
				TRAP(errcode, AddCalendarL( aInParamList, aOutParamList, posBased ));
				}
			else if ( contentType.CompareF( KContentCalendarEntry ) == 0 )
				{
				TRAP(errcode, AddCalendarEntryL( aInParamList, aOutParamList, posBased ));
				}
			}
		else
			{
			AppendErrorMessageL(aCmdName, KNullDesC8, KAsyncNotSupported);
			}	
		}

	else if ( aCmdName.CompareF( KCmdDelete ) == 0 ) 
		{
		if( contentType.CompareF( KContentCalendar ) == 0 ) 
			{ 
			if ( !aCallback )//deletion of calendars only synchronous
				{
				TRAP(errcode, DeleteCalendarL( aInParamList, posBased) );
				}
			else
				{
				AppendErrorMessageL(aCmdName, KNullDesC8, KAsyncNotSupported);
				}	
			}
		else if ( contentType.CompareF( KContentCalendarEntry ) == 0) 
			{
			TRAP(errcode, DeleteCalendarEntryL( aInParamList, aOutParamList, aCmdOptions, aCallback, posBased, transactionId ));
			}
		}

	else if ( aCmdName.CompareF( KCmdImport ) == 0 ) 
		{
  		if ( contentType.CompareF( KContentCalendarEntry ) == 0 )	
			{
			TRAP(errcode, ImportCalendarEntryL( aInParamList, aOutParamList, aCmdOptions, aCallback, posBased, transactionId ));
			}
		else
			{
			AppendErrorMessageL( aCmdName, KContentType, KInvalid );
			}	
		}

	else if ( aCmdName.CompareF( KCmdExport ) == 0 ) 
		{
		if ( contentType.CompareF( KContentCalendarEntry ) == 0 )	
			{
			TRAP(errcode, ExportCalendarEntryL( aInParamList, aOutParamList, aCmdOptions, aCallback, posBased, transactionId ));
			}	
		else
			{
			AppendErrorMessageL( aCmdName, KContentType, KInvalid );
			}	
		}

	else if ( aCmdName.CompareF( KCmdGetList ) == 0 ) 
		{
		
			if ( contentType.CompareF( KContentCalendar ) == 0 )
				{
				if( !aCallback )
				    {
				    TRAP(errcode, GetListCalendarL( aInParamList, aOutParamList, posBased ));
				    }
				else
                    {
                    AppendErrorMessageL(aCmdName, KNullDesC8, KAsyncNotSupported);
                    }
				}
			else if ( contentType.CompareF( KContentCalendarEntry ) == 0 )
				{
				TRAP(errcode, GetListCalendarEntryL( aInParamList, aOutParamList, aCmdOptions, aCallback, posBased, transactionId ));
				}
		}

	else if ( aCmdName.CompareF( KCmdReqNot ) == 0 ) 
		{
		if (( contentType.CompareF( KContentCalendarEntry ) == 0 ) && 
				aCallback && ( KLiwOptASyncronous & aCmdOptions ) )
			{
			TRAP(errcode, RequestNotificationL(aInParamList, aCallback, posBased, transactionId ));
			}
		else if( !aCallback || !( KLiwOptASyncronous & aCmdOptions ))
			{
			AppendErrorMessageL(aCmdName, KNullDesC8, KInvalidAsyncParam);
			}
		else
			{
			AppendErrorMessageL( aCmdName, KContentType, KInvalid );
			}	
		}
		
	else if ( aCmdName.CompareF( KCmdCancel ) == 0 ) 
		{
		TInt32 transactionId;
		if( (KLiwOptCancel & aCmdOptions ) && !aCallback )
			{
			TRAP( errcode, GetTransactionIdL( aInParamList, transactionId ) );
			if( errcode == KErrNone )
				{
				errcode = iCalService->Cancel( transactionId );
				if ( errcode == KErrNotFound )
					{
					AppendErrorMessageL( aCmdName, KTransactionID, KInvalid );
					}
				else if( errcode == KErrInUse )
					{
					AppendErrorMessageL( aCmdName, KNullDesC8, KServiceInUse );
					}	
				}
			}
		else
			{
			AppendErrorMessageL( aCmdName, KNullDesC8, KInvalidCancelParam );
			}	
		}
		
	else
		{
		AppendErrorMessageL(aCmdName, KNullDesC8, KCmdInvalid);
		}	
				
	// Append transaction id in case of asynchronous requests
	if( aCallback && ( KLiwOptASyncronous & aCmdOptions ) && 
						( errcode == KErrNone ) && ( transactionId != -1 ) )
		{
		aOutParamList.AppendL(TLiwGenericParam( KTransactionID, 
								TLiwVariant( TInt32( transactionId ))));		
		}
			
	if( errcode != KErrNone )
		{
		aOutParamList.Reset();
		aOutParamList.AppendL(TLiwGenericParam( KErrorCode, 
									TLiwVariant(ErrCodeConversion(errcode))));		

		if ( iErrorMessage )
			{
			aOutParamList.AppendL(TLiwGenericParam( KErrorMessage, 
										TLiwVariant(iErrorMessage->Des())));
			delete iErrorMessage;
			iErrorMessage = NULL;		
			}
		}
	}

// ---------------------------------------------------------------------------
// Closes the interface
// ---------------------------------------------------------------------------
//
void CCalendarInterface::Close()
	{
	delete this;
	}

// ---------------------------------------------------------------------------
// Issues Add Calendar request to Calendar Service
// ---------------------------------------------------------------------------
//
void CCalendarInterface::AddCalendarL(const CLiwGenericParamList& aInParamList, 
													CLiwGenericParamList& /*aOutParamList*/, 
													const TBool aPosBased )
	{
    HBufC* calName = NULL;
    GetCalendarNameL( aInParamList, KCmdAdd, KItem, aPosBased, calName );
    if ( calName && calName->Des().Length() )
		{
		CleanupStack::PushL(calName);
		iCalService->AddL( calName->Des() );
		CleanupStack::PopAndDestroy(calName);
		}
	else
		{
		AppendErrorMessageL( KCmdAdd, KCalendarName, KMissing );
		User::Leave( KErrArgument );
		}
	}
	
// ---------------------------------------------------------------------------
// Issues Add Calendar Entry request to Calendar Service
// ---------------------------------------------------------------------------
//
void CCalendarInterface::AddCalendarEntryL(const CLiwGenericParamList& aInParamList, 
													CLiwGenericParamList& aOutParamList, 
													const TBool aPosBased )
	{
    HBufC* calName = NULL;

    GetCalendarNameL( aInParamList, KCmdAdd, KItem, aPosBased, calName );

    if ( calName )
		{
		CleanupStack::PushL(calName);
		}

	// Get New entry attributes from input param list
   	CEntryAttributes* addAttributes = GetAddParametersL( aInParamList, 
   														calName ? calName->Des() : TPtrC(), 
   														aPosBased );

    CleanupStack::PushL( addAttributes );

    TUIDSet* uidset = NULL;

	iCalService->AddL( calName ? calName->Des() : TPtrC() , addAttributes, uidset );

	// Return Uid of the newly added entry
	if ( uidset )
		{
		CleanupStack::PushL( uidset );
		
		HBufC* globalUid = HBufC::NewL( uidset->iGlobalUID->Length() + 1 );
		CleanupStack::PushL( globalUid );
		globalUid->Des().Copy( uidset->iGlobalUID->Des() );
		aOutParamList.AppendL( TLiwGenericParam( KReturnValue, TLiwVariant(*globalUid) ));
		CleanupStack::PopAndDestroy( globalUid );

		CleanupStack::Pop( uidset );
		
		delete uidset;
		
		CleanupStack::PopAndDestroy( addAttributes );
		}
	else
		{
		AppendErrorMessageL( KCmdAdd, KNullDesC8, KCmdFailed );
		User::Leave( KErrGeneral );
		}

    if ( calName )
		{
		CleanupStack::PopAndDestroy(calName);
		}
	}
	
// ---------------------------------------------------------------------------
// Issues Delete Calendar request to Calendar Service
// ---------------------------------------------------------------------------
//
void CCalendarInterface::DeleteCalendarL( const CLiwGenericParamList& aInParamList, TBool aPosBased)
	{
    HBufC* calName = NULL;
    GetCalendarNameL( aInParamList, KCmdDelete, KData, aPosBased, calName );
    if ( calName && calName->Length() )
		{
		CleanupStack::PushL( calName );
		if( CheckCalendarInUse( *calName ) )
			{
			AppendErrorMessageL( KCmdDelete, KCalendarName, _L(" in use.") );
			User::Leave( KErrInUse );
			}
		iCalService->DeleteL( calName->Des() );
		CleanupStack::PopAndDestroy( calName );
		}
	else
		{
		AppendErrorMessageL( KCmdDelete, KCalendarName, KMissing );
		User::Leave( KErrArgument );
		}
	}

// ---------------------------------------------------------------------------
// Issues Delete Calendar Entry request to Calendar Service
// ---------------------------------------------------------------------------
//
void CCalendarInterface::DeleteCalendarEntryL( const CLiwGenericParamList& aInParamList, 
													CLiwGenericParamList& /*aOutParamList*/,
													TUint aCmdOptions,
					                       			MLiwNotifyCallback* aCallback,
													const TBool aPosBased,
													TInt32& aTransactionId )
	{
    HBufC* calName = NULL;

    GetCalendarNameL( aInParamList, KCmdDelete, KData, aPosBased, calName );

    if ( calName )
		{
		CleanupStack::PushL(calName);
		}
	
	CCalendarFilter* filter = CCalendarFilter::NewL();
	
	CleanupStack::PushL(filter);
	
	// Get filter parameters from input list
	GetDeleteEntryFilterL( aInParamList, *filter, aPosBased );

	// Leave if there was no filter
	if( ! filter->Filter() )
		{
		AppendErrorMessageL( KCmdDelete, KData, KMissing );
		User::Leave( KErrArgument );
		}
	
	// Issue asynchronous request if Callback present
	if ( aCallback && ( KLiwOptASyncronous & aCmdOptions )) 
		{
		aTransactionId = aCallback->GetTransactionID();
		
		CCalCallbackInt* callback = CCalCallbackInt::NewL( aCallback, aInParamList, aTransactionId );
		
		CleanupStack::PushL( callback );
		
		iCalService->DeleteL(  	calName ? calName->Des() : TPtrC() , filter, callback );				

		CleanupStack::Pop( callback );
		}
	// Synchronous request	
	else 
		{
		iCalService->DeleteL( calName ? calName->Des() : TPtrC(), filter );
		}

	CleanupStack::PopAndDestroy(filter);

    if ( calName )
		{
		CleanupStack::PopAndDestroy(calName);
		}
	
	}
	
// ---------------------------------------------------------------------------
// Issues GetList Calendar request to Calendar Service
// ---------------------------------------------------------------------------
//
void CCalendarInterface::GetListCalendarL(const CLiwGenericParamList& aInParamList, 
													CLiwGenericParamList& aOutParamList, 
													const TBool aPosBased )
	{
	const TLiwGenericParam* filter = NULL; 

	if ( aPosBased )
		{
		if ( aInParamList.Count() > 1 )
			filter = &aInParamList[1];
		}
	else
		{
		TInt pos = 0 ;
		filter = aInParamList.FindFirst( pos, KFilter );
		}
		
	TBool defaultCalendar = EFalse;

	// Extracting "Default" input param
	// If True, Only default calendar is returned
	if ( filter )
		{
		const CLiwMap* inputMap = filter->Value().AsMap(); 
		if ( inputMap )
			{
			TLiwVariant defaultvalue;
			if( inputMap->FindL( KDefault, defaultvalue))
				{
				ValidateParamTypeL( defaultvalue, LIW::EVariantTypeTBool, 
									KCmdGetList, KDefault, KInvalid );

				defaultCalendar = defaultvalue.AsTBool();
				}
			defaultvalue.Reset();	
			}
		else
			{
			AppendErrorMessageL( KCmdGetList, KFilter, KInvalid );
			User::Leave(KErrArgument);
			}	
		}
	
	CDesCArray* returnList = NULL;

	// Issue request to Calendar Service	
	iCalService->GetListL( returnList, defaultCalendar );
	
	CleanupStack::PushL( returnList );
	
	// Encapsulate the returned list as Iterable
	CIterableCalendarList* iterList = CIterableCalendarList::NewL( returnList );

	CleanupStack::Pop( returnList );
	
	CleanupClosePushL( *iterList );
	
	aOutParamList.AppendL( TLiwGenericParam( KReturnValue, TLiwVariant( iterList )));
	
	CleanupStack::PopAndDestroy( iterList );
	
	}
	
// ---------------------------------------------------------------------------
// Issues GetList Calendar Entry request to Calendar Service
// ---------------------------------------------------------------------------
//
void CCalendarInterface::GetListCalendarEntryL(const CLiwGenericParamList& aInParamList, 
													CLiwGenericParamList& aOutParamList,
													TUint aCmdOptions,
													MLiwNotifyCallback* aCallback ,
													const TBool aPosBased,
													TInt32& aTransactionId)
	{
	const TLiwGenericParam* filterParam = NULL; 

	if ( aPosBased )
		{
		if ( aInParamList.Count() > 1 )
			filterParam = &aInParamList[1];
		}
	else
		{
		TInt pos = 0 ;
		filterParam = aInParamList.FindFirst( pos, KFilter );
		}
		
	CCalendarFilter* filter = CCalendarFilter::NewL();
	
	CleanupStack::PushL( filter );
	
	HBufC* calName = NULL;

	// Extract filter information from input param list	
	if ( filterParam )
		{
		const CLiwMap* inputMap = filterParam->Value().AsMap(); 
		if ( inputMap )
			{
			TLiwVariant param;
			CleanupStack::PushL( TCleanupItem(TLiwVariant::VariantCleanup , &param));
			
			
			if( inputMap->FindL( KId, param ))
				{
				ValidateParamTypeL( param, LIW::EVariantTypeDesC, 
									KCmdGetList, KId, KInvalid );
				
				//filter->AddGuidL( param.AsData() );
				HBufC8* globalUid = HBufC8::NewL(param.AsDes().Length());
				CleanupStack::PushL( globalUid );
				GetGlobalUid(param.AsDes(), globalUid->Des());
				filter->AddGuidL( globalUid->Des() );
				CleanupStack::PopAndDestroy( globalUid );
				}

			if( inputMap->FindL( KLocalId, param ))
				{
				ValidateParamTypeL( param, LIW::EVariantTypeDesC, 
									KCmdGetList, KLocalId, KInvalid );
									
				//filter->AddLocalUid( param.AsTUint() );
				TCalLocalUid localUid;
				GetLocalUid( param.AsDes(), localUid );
				filter->AddLocalUid( localUid );
				}
				
			if( inputMap->FindL( KStartRange, param))
				{
				ValidateParamTypeL( param, LIW::EVariantTypeTTime, 
									KCmdGetList, KStartRange, KInvalid );
									
				filter->SetStartTimeL( param.AsTTime() );
				}
				
			if( inputMap->FindL( KEndRange, param))
				{
				ValidateParamTypeL( param, LIW::EVariantTypeTTime, 
									KCmdGetList, KEndRange, KInvalid );
									
				filter->SetEndTimeL( param.AsTTime() );
				}

			if( inputMap->FindL( KSearchText, param))
				{
				ValidateParamTypeL( param, LIW::EVariantTypeDesC, 
									KCmdGetList, KSearchText, KInvalid );
									
				filter->SetFilterTextL( param.AsDes() );
				}
				
			if( inputMap->FindL( KEntryType, param))
				{
				ValidateParamTypeL( param, LIW::EVariantTypeDesC, 
									KCmdGetList, _L8("Entry Type") , KInvalid );
									
				filter->SetFilterTypeL( param.AsDes() );
				}
				
			if( inputMap->FindL( KCalendarName, param))
				{
				ValidateParamTypeL( param, LIW::EVariantTypeDesC, 
									KCmdGetList, KCalendarName, KInvalid );
				
				calName = param.AsDes().AllocL();
				}

			CleanupStack::Pop( &param);
			param.Reset();	
			}
		else
			{
			AppendErrorMessageL(KCmdGetList, KFilter, KInvalid);
			User::Leave(KErrArgument);
			}	
		}
	if( calName )
		CleanupStack::PushL(calName);	
	TPtrC calendarName(	calName ? calName->Des() : TPtrC() );	
	
	//asynchronous version of getlist is called if callback is provided
   if ( aCallback && ( KLiwOptASyncronous & aCmdOptions  ) )
        {
        aTransactionId = aCallback->GetTransactionID();

        CCalCallbackCalEntryList* callback = NULL;
        
       
       
       
       if(( filter->Filter() & EFilterGUid ) || ( filter->Filter() & EFilterLUid ))
           {
           callback = CCalCallbackCalEntryList::NewL( *this, aCallback, calendarName, aTransactionId, ETrue );
           }
       else
           {
           callback = CCalCallbackCalEntryList::NewL( *this, aCallback, calendarName, aTransactionId, EFalse );
           }
         
       CleanupStack::PushL( callback );
       if ( filter->Filter() & EFilterGUid )
           {
           // In case of GlobalUid only one entry is returned.
           iCalService->GetListL( calendarName, (*filter->GuidList())[0], callback);
           }
       else if( filter->Filter() & EFilterLUid )
           {
           // In case of LocalUid there can be more than one entry(child entries)
           iCalService->GetListL( calendarName, (filter->LocalUidList())[0], callback);
           }
       else
           {
           iCalService->GetListL( calendarName , filter, callback );
           }
       aOutParamList.AppendL(TLiwGenericParam( KTransactionID, TLiwVariant( aTransactionId )));
       
       CleanupStack::Pop( callback );    
        }

	// Return list of CalendarEntries if any of LocalUid or GlobalUid is passed as Filter.
    else if ( ( filter->Filter() & EFilterGUid ) || 
			( filter->Filter() & EFilterLUid ) )
		{
		CIterableCalEntryList* iterEntryList = CIterableCalEntryList::NewL( *this, calendarName, ETrue );
		CleanupStack::PushL(  TCleanupItem(CleanupIterableCalEntry, iterEntryList ) );
		
		
		if ( filter->Filter() & EFilterLUid )
			{
			// In case of LocalUid only one entry is returned.
			iCalService->GetListL( calendarName, (filter->LocalUidList())[0], iterEntryList->EntryArray());
			}
		else
			{
			// In case of GlobalUid there can be more than one entry(child entries)
			iCalService->GetListL( calendarName, (*filter->GuidList())[0], iterEntryList->EntryArray());
			}
		
		aOutParamList.AppendL( TLiwGenericParam( KReturnValue, TLiwVariant( iterEntryList )));
		iterEntryList->DecRef();

		iArrayCalEntryList.Append( iterEntryList );

		CleanupStack::Pop( iterEntryList );
		}
	// Return list of Instances if none of LocalUid or GlobalUid is passed as Filter.
	else 
		{
		CIterableCalEntryList* iterInstList = CIterableCalEntryList::NewL( *this, calendarName, EFalse );
		CleanupStack::PushL(  TCleanupItem(CleanupIterableCalEntry, iterInstList ) );

		iCalService->GetListL( calendarName, filter, iterInstList->InstanceArray());

		aOutParamList.AppendL( TLiwGenericParam( KReturnValue, TLiwVariant( iterInstList )));
		iterInstList->DecRef();
		
		iArrayCalEntryList.Append( iterInstList );

		CleanupStack::Pop( iterInstList );
		}

	if ( calName )
		CleanupStack::PopAndDestroy(calName);	
	
	CleanupStack::PopAndDestroy(filter);
	}
	
// ---------------------------------------------------------------------------
// Issues Import Calendar Entry request to Calendar Service
// ---------------------------------------------------------------------------
//
void CCalendarInterface::ImportCalendarEntryL(const CLiwGenericParamList& aInParamList, 
													CLiwGenericParamList& aOutParamList,
													TUint aCmdOptions,
					                       			MLiwNotifyCallback* aCallback ,
													const TBool aPosBased, 
													TInt32& aTransactionId )
	{
	HBufC8* inputBuffer = NULL;
	
	HBufC* calName = NULL;

	HBufC* importFile = NULL;
	
	HBufC8* calendarFormat = NULL;
	
	// Extract input information from input param list	
    GetCalendarNameL( aInParamList, KCmdImport, KData, aPosBased, calName );
    if ( calName )
    	{
    	CleanupStack::PushL( calName );
    	}
    
	GetDesCFieldFromMapL( aInParamList, KCmdImport, KData, KImExFileName, aPosBased, importFile );
    if ( importFile )
    	{
    	CleanupStack::PushL( importFile );
    	}
	
	GetDesC8FieldFromMapL( aInParamList, KCmdImport, KData, KInputBuffer, aPosBased, inputBuffer );
    if ( inputBuffer )
    	{
    	CleanupStack::PushL( inputBuffer );
    	}
    else if ( !importFile )	
    	{
		AppendErrorMessageL( KCmdImport, KImExFileName, KMissing );
		User::Leave( KErrArgument );
    	}
    	
    HBufC* tmpFormat = NULL;
	GetDesCFieldFromMapL( aInParamList, KCmdImport, KData, KCalendarFormat, aPosBased, tmpFormat );
    if ( tmpFormat )
    	{
    	CleanupStack::PushL( tmpFormat );
    	calendarFormat = HBufC8::NewL(tmpFormat->Des().Length());
    	calendarFormat->Des().Copy(tmpFormat->Des());
    	CleanupStack::PopAndDestroy( tmpFormat );
    	CleanupStack::PushL( calendarFormat );
    	}
	else
		{
		AppendErrorMessageL( KCmdImport, KCalendarFormat, KMissing );
		User::Leave( KErrArgument );
		}	
	
	
	//asynchronous version of import is called if callback is provided
	if ( aCallback && ( KLiwOptASyncronous & aCmdOptions )) 
		{
		aTransactionId = aCallback->GetTransactionID();
		
		CCalCallbackBaseUIDSet* callback = CCalCallbackBaseUIDSet::NewL( aCallback, aInParamList, aTransactionId);
		
		CleanupStack::PushL( callback );
		
		if ( inputBuffer )
			{
			// Import from the input buffer
			iCalService->ImportL( calName ? calName->Des() : TPtrC(), 
									*calendarFormat, *inputBuffer, callback );				
			}
		else
			{
			// Import from the given file
			iCalService->ImportL( calName ? calName->Des() : TPtrC(), 
									*calendarFormat , *importFile, callback );				
			}

		CleanupStack::Pop( callback );
		}
	else //synchronous version of import
		{
		RPointerArray<TUIDSet> outputUIDSet;//Push on to CalennupStack
		
		if ( inputBuffer )
			{
			// Import from the input buffer
			iCalService->ImportL( calName ? calName->Des() : TPtrC(), 
									*calendarFormat , *inputBuffer, outputUIDSet );				
			}
		else
			{
			// Import from the input file
			iCalService->ImportL( calName ? calName->Des() : TPtrC(), 
									*calendarFormat , *importFile, outputUIDSet );
			}
		
		//	Set output to output param
		SetImportOutputL( outputUIDSet, aOutParamList );				
			
		outputUIDSet.ResetAndDestroy();	
		}

    CleanupStack::PopAndDestroy( calendarFormat );
    
    if ( inputBuffer )
    	CleanupStack::PopAndDestroy( inputBuffer );
    	
    if ( importFile )
    	CleanupStack::PopAndDestroy( importFile );

    if ( calName )
    	CleanupStack::PopAndDestroy( calName );
	}

// ---------------------------------------------------------------------------
// Issues Export Calendar Entry request to Calendar Service
// ---------------------------------------------------------------------------
//
void CCalendarInterface::ExportCalendarEntryL(const CLiwGenericParamList& aInParamList, 
													CLiwGenericParamList& aOutParamList,
													TUint aCmdOptions,
					                       			MLiwNotifyCallback* aCallback ,
													const TBool aPosBased,
													TInt32& aTransactionId )
	{		
	HBufC* calendarName = NULL;
	
	HBufC8* exportFormat = NULL;
	
	CCalendarExportParams* calendarExportParams = CCalendarExportParams::NewL();
	
	CleanupStack::PushL( calendarExportParams );
		
	// Extract input information from input param list	
    GetCalendarNameL( aInParamList, KCmdExport, KData, aPosBased, calendarName );
    if ( calendarName )
    	{
    	CleanupStack::PushL( calendarName );
    	}
    
    HBufC* tmpFormat = NULL;
	GetDesCFieldFromMapL( aInParamList, KCmdExport, KData, KCalendarFormat, aPosBased, tmpFormat );
    if ( tmpFormat )
    	{
    	CleanupStack::PushL( tmpFormat );
    	exportFormat = HBufC8::NewL(tmpFormat->Des().Length());
    	exportFormat->Des().Copy(tmpFormat->Des());
    	CleanupStack::PopAndDestroy( tmpFormat );
    	CleanupStack::PushL( exportFormat );
    	}
	else
		{
		AppendErrorMessageL( KCmdExport, KCalendarFormat, KMissing );
		User::Leave( KErrArgument );
		}	

	// Extract input information from input param list	
	GetExportInputL( aInParamList , aPosBased , *calendarExportParams );
	
	//asynchronous version of Export is called if callback is provided
	if ( aCallback && ( KLiwOptASyncronous & aCmdOptions )) 
		{	
		aTransactionId = aCallback->GetTransactionID();
		
		CCalCallbackBaseBuffer* callback = CCalCallbackBaseBuffer::NewL( aCallback, aInParamList, aTransactionId );

		CleanupStack::PushL( callback );
		
		iCalService->ExportL( calendarName ? calendarName->Des() : TPtrC(), 
								*exportFormat, calendarExportParams , callback );
		
		CleanupStack::Pop( callback );
		}
	else //synchronous version of Export
		{
		HBufC8* outputBuffer = NULL;
	
		iCalService->ExportL( calendarName ? calendarName->Des() : TPtrC() , 
								*exportFormat, calendarExportParams , outputBuffer );

		// outputBuffer is NULL in case export is done to file		
		if ( outputBuffer )
			{
			CleanupStack::PushL( outputBuffer );
			aOutParamList.AppendL( TLiwGenericParam( KReturnValue, TLiwVariant( *outputBuffer ) ) );
			CleanupStack::PopAndDestroy( outputBuffer );
			}
		}  
	
    CleanupStack::PopAndDestroy( exportFormat );
    
    if ( calendarName )
    	CleanupStack::PopAndDestroy( calendarName );
    
	CleanupStack::PopAndDestroy( calendarExportParams );
	}
	

// ---------------------------------------------------------------------------
// Issues Change Notification request to Calendar Service
// ---------------------------------------------------------------------------
//
void CCalendarInterface::RequestNotificationL( const CLiwGenericParamList& aInParamList, 
					                       			MLiwNotifyCallback* aCallback,
													const TBool aPosBased,
													TInt32& aTransactionId )
	{
	HBufC* calName = NULL;
	
	GetCalendarNameL( aInParamList, KCmdReqNot, KFilter, aPosBased, calName );
	
	if ( calName )
		{
		CleanupStack::PushL(calName);
		}

	CCalendarFilter* filter = CCalendarFilter::NewL();

	CleanupStack::PushL(filter);

	// Get Notification filter	
	GetNotificationFilterL( aInParamList, *filter, aPosBased );
	
	aTransactionId = aCallback->GetTransactionID();
		
	CCalCallbackChangeNotify* callback = CCalCallbackChangeNotify::NewL( aCallback, aInParamList, aTransactionId );
		
	CleanupStack::PushL( callback );
		
	// Issue request
	iCalService->StartChangeNotifyL( calName ? calName->Des() : TPtrC(), filter, callback );				

	CleanupStack::Pop( callback );
	
	CleanupStack::PopAndDestroy(filter);

	if ( calName )
		{
		CleanupStack::PopAndDestroy(calName);
		}

	}

// ---------------------------------------------------------------------------
// Get content type from input param list
// ---------------------------------------------------------------------------
//
TPtrC CCalendarInterface::GetContentType(const CLiwGenericParamList& aInParamList, TBool& aPosBased )
	{
	TInt pos = 0;
	
	const TLiwGenericParam* inContentType = aInParamList.FindFirst( pos, KContentType );
	
	TPtrC type;
	
	if ( inContentType )
		{
		type.Set( inContentType->Value().AsDes() );
		aPosBased = EFalse;
		}
	else
		{
		if ( aInParamList.Count() > 0 )
			{
			inContentType = &aInParamList[0];
			if( inContentType->Name().Compare(KNullDesC8) == 0 )
				{
				type.Set( aInParamList[0].Value().AsDes() );
				aPosBased = ETrue;
				}
			}
		}

	return type;	
	}

// ---------------------------------------------------------------------------
// Gets the Transaction id 
// ---------------------------------------------------------------------------
//	
void CCalendarInterface::GetTransactionIdL( const CLiwGenericParamList& aInParamList, TInt32& aTransactionId )
	{
	TInt pos = 0;
	    
	const TLiwGenericParam* param = aInParamList.FindFirst( pos, 
															KTransactionID, 
															EVariantTypeTInt32 );
	if(!param && aInParamList.Count() > 0)
		{
		param = &aInParamList[0];
		if( param->Name().Compare(KNullDesC8) != 0 )
			{
			AppendErrorMessageL( KCmdCancel, KTransactionID, KMissing );
			User::Leave(KErrArgument);
			}
		}
	
	if ( param )
		{
		TLiwVariant* tempparam = const_cast<TLiwVariant*>(& param->Value());
		ValidateParamTypeL( *tempparam, LIW::EVariantTypeTInt32, 
					KCmdCancel, KTransactionID, KInvalid );

		aTransactionId = param->Value().AsTInt32();
		}
	else
		{
		AppendErrorMessageL( KCmdCancel, KTransactionID, KMissing );
		User::Leave(KErrArgument);
		}
	}
	
// ---------------------------------------------------------------------------
// Gets the Calendar Name from input param list
// ---------------------------------------------------------------------------
//
void CCalendarInterface::GetCalendarNameL( const CLiwGenericParamList& aInParamList, 
												const TDesC8& aCmdName, 
												const TDesC8& aField, 
												TBool aPosBased, 
												HBufC*& aCalendarName )
	{
	const TLiwGenericParam* param = NULL;
	
	if ( aPosBased && aInParamList.Count() > 1)
		{
		param = &aInParamList[1];
		}
	else
		{
		TInt pos = 0;
		param = aInParamList.FindFirst( pos, aField );
		}
	
	if ( param ) 
		{
		const CLiwMap* inMap = param->Value().AsMap();
		
		if(inMap)
			{
			TLiwVariant inParam;
			CleanupStack::PushL( TCleanupItem(TLiwVariant::VariantCleanup , &inParam));
			if ( inMap->FindL( KCalendarName, inParam ) ) 
				{
				ValidateParamTypeL( inParam, LIW::EVariantTypeDesC, 
									aCmdName, KCalendarName, KInvalid );
									
				if ( inParam.AsDes().Length() > KMaxFileName )
					{
					AppendErrorMessageL( aCmdName, KCalendarName, KInvalid );
					User::Leave(KErrArgument);
					}
					
				if( inParam.AsDes().Length() )
					{
					if ( inParam.AsDes().LocateF(':') == KErrNotFound )
						{
						AppendErrorMessageL( aCmdName, KCalendarName, KInvalid );
						User::Leave(KErrArgument);
						}
					else
						{
						aCalendarName = inParam.AsDes().AllocL();
						aCalendarName->Des().Trim();	
						}
					}
				}
			CleanupStack::Pop( &inParam );
			inParam.Reset();
			}
		else
			{
			AppendErrorMessageL( aCmdName, aField, KInvalid );
			User::Leave(KErrArgument);
			}	
		}
	}

// ---------------------------------------------------------------------------
// Gets the Field from Map in input param list
// ---------------------------------------------------------------------------
//
void CCalendarInterface::GetDesCFieldFromMapL( const CLiwGenericParamList& aInParamList, 
												const TDesC8& aCmdName, 
												const TDesC8& aMapName, 
												const TDesC8& aFieldName, 
												TBool aPosBased, 
												HBufC*& aOutputField )
	{
	const TLiwGenericParam* param = NULL;
	
	if ( aPosBased && aInParamList.Count() > 1)
		{
		param = &aInParamList[1];
		}
	else
		{
		TInt pos = 0;
		param = aInParamList.FindFirst( pos, aMapName );
		}
	
	if ( param ) 
		{
		const CLiwMap* inMap = param->Value().AsMap();
		
		if(inMap)
			{
			TLiwVariant inParam;
			CleanupStack::PushL( TCleanupItem(TLiwVariant::VariantCleanup , &inParam));
			if ( inMap->FindL( aFieldName, inParam ) ) 
				{
				ValidateParamTypeL( inParam, LIW::EVariantTypeDesC, 
									aCmdName, aFieldName, KInvalid );
									
				if ( inParam.AsDes().Length() > KMaxFileNameLength )
					{
					AppendErrorMessageL( aCmdName, aFieldName, KInvalid );
					User::Leave(KErrArgument);
					}
				
				if( inParam.AsDes().Length() )
					{
					aOutputField = HBufC::NewL(inParam.AsDes().Length());	
					aOutputField->Des().Copy( inParam.AsDes() );
					}
				}
			CleanupStack::Pop( &inParam );
			inParam.Reset();
			}
		else
			{
			AppendErrorMessageL( aCmdName, aMapName, KInvalid );
			User::Leave(KErrArgument);
			}	
		}
	}

// ---------------------------------------------------------------------------
// Gets the Field from Map in input param list
// ---------------------------------------------------------------------------
//
void CCalendarInterface::GetDesC8FieldFromMapL( const CLiwGenericParamList& aInParamList, 
												const TDesC8& aCmdName, 
												const TDesC8& aMapName, 
												const TDesC8& aFieldName, 
												TBool aPosBased, 
												HBufC8*& aOutputField )
	{
	const TLiwGenericParam* param = NULL;
	
	if ( aPosBased && aInParamList.Count() > 1)
		{
		param = &aInParamList[1];
		}
	else
		{
		TInt pos = 0;
		param = aInParamList.FindFirst( pos, aMapName );
		}
	
	if ( param ) 
		{
		const CLiwMap* inMap = param->Value().AsMap();
		
		if(inMap)
			{
			TLiwVariant inParam;
			CleanupStack::PushL( TCleanupItem(TLiwVariant::VariantCleanup , &inParam));
			
			if ( inMap->FindL( aFieldName, inParam ) ) 
				{
				ValidateParamTypeL( inParam, LIW::EVariantTypeDesC8, 
									aCmdName, aFieldName, KInvalid );
									
				if( inParam.AsData().Length() )
					{
					aOutputField = inParam.AsData().AllocL();
					}
				}
			CleanupStack::Pop( &inParam );
			inParam.Reset();
			}
		else
			{
			AppendErrorMessageL( aCmdName, aMapName, KInvalid );
			User::Leave(KErrArgument);
			}	
		}
	}

// ---------------------------------------------------------------------------
// Extracts Entry attributes of a Calendar entry
// ---------------------------------------------------------------------------
//
CEntryAttributes* CCalendarInterface::GetAddParametersL( const CLiwGenericParamList& aInParamList, 
														const TDesC& aCalendarName,
														TBool aPosBasedSearch )
	{
	CEntryAttributes* entryAttributes = CEntryAttributes::NewL();
	
	CleanupStack::PushL( entryAttributes );
	
	TBool id;
	
	const TLiwGenericParam* param = NULL;
	
	if ( aPosBasedSearch )
		{
		if( aInParamList.Count() > 1 )
			param = &aInParamList[1];
		}
	else
		{
		TInt pos = 0;
		param = aInParamList.FindFirst( pos, KItem );
		}
	
	if ( param )
		{
		const CLiwMap* inMap = param->Value().AsMap();
		if( inMap )
			{
			TLiwVariant inParam;
			TInt error = KErrNone;
			CleanupStack::PushL( TCleanupItem(TLiwVariant::VariantCleanup , &inParam));

			// Applicable only for Update request
			TBool isUpdate = EFalse;
			TInt entryType = -1;
			if ( inMap->FindL( KLocalId, inParam ) ) 
				{
				id = EFalse;
				ValidateParamTypeL( inParam, LIW::EVariantTypeDesC, 
									KCmdAdd, KLocalId, KInvalid );
				
				//entryAttributes->SetLocalUid( TCalLocalUid(inParam.AsTUint() ));
				TCalLocalUid localUid;
				GetLocalUid( inParam.AsDes(), localUid );
				entryAttributes->SetLocalUid( localUid );
				isUpdate = ETrue;
				}
            if ( inMap->FindL( KId, inParam ) ) 
                {
                id = ETrue;
                ValidateParamTypeL( inParam, LIW::EVariantTypeDesC, 
                                    KCmdAdd, KId, KInvalid );
                
                HBufC8* globalUid = HBufC8::NewL(inParam.AsDes().Length());
                CleanupStack::PushL( globalUid );
                GetGlobalUid(inParam.AsDes(), globalUid->Des());
                entryAttributes->SetUidL( globalUid->Des() );
                CleanupStack::PopAndDestroy( globalUid ); 
                isUpdate = ETrue;
                }
			
			if ( inMap->FindL( KType, inParam ) ) 
				{
				ValidateParamTypeL( inParam, LIW::EVariantTypeDesC, 
									KCmdAdd, _L8("Entry Type"), KInvalid );
									
				entryAttributes->SetTypeL( inParam.AsDes() );
				entryType = entryAttributes->EntryType();
				}

			//Adding New Entry	
			else if( !isUpdate )
				{
				AppendErrorMessageL( KCmdAdd, KType, KMissing );
				User::Leave( KErrArgument );
				}

			//Updating Existing Entry	
			//Get the type of the original entry. User cannot change the type
			if( isUpdate )
				{
				if(id)
				    {
                    entryType = GetEntryType( aCalendarName, entryAttributes->GlobalUid() );				    
                    }
				else
				    {
				    entryType = GetEntryType( aCalendarName, entryAttributes->LocalUid() );
				    }
				if ( entryType == -1 )
					{
					AppendErrorMessageL( KCmdAdd, KLocalId, KInvalid );
					User::Leave( KErrArgument );
					}
					
				// Leave if tring to set different entry type
				if ( entryAttributes->ModifiedAttributes() & CEntryAttributes::EEntryType )
					{
					TInt tmpType = entryAttributes->EntryType();
					if ( tmpType != entryType )
						{
						AppendErrorMessageL( KCmdAdd, _L8("Entry Type "), KInvalid );
						User::Leave( KErrArgument );
						}
					}
				}
			
			//For Add			
			if ( inMap->FindL( KSummary, inParam ) ) 
				{
				ValidateParamTypeL( inParam, LIW::EVariantTypeDesC, 
									KCmdAdd, KSummary, KInvalid );
				
				entryAttributes->SetSummaryL( inParam.AsDes() );
				}
			
			if ( inMap->FindL( KDescription, inParam ) ) 
				{
				ValidateParamTypeL( inParam, LIW::EVariantTypeDesC, 
									KCmdAdd, KDescription, KInvalid );
				
				entryAttributes->SetDescriptionL( inParam.AsDes() );
				}
			
			if ( inMap->FindL( KReplication, inParam ) ) 
				{
				ValidateParamTypeL( inParam, LIW::EVariantTypeDesC, 
									KCmdAdd, KReplication, KInvalid );
				
				entryAttributes->SetReplicationL( inParam.AsDes() );
				}
				
			if ( inMap->FindL( KPriority, inParam ) ) 
				{
				ValidateParamTypeL( inParam, LIW::EVariantTypeTInt32, 
									KCmdAdd, KPriority, KInvalid );
				
				error = entryAttributes->SetPriority( inParam.AsTInt32() );
				User::LeaveIfError( error );
				}
				
			if ( ( entryType != CCalEntry::ETodo ) && 
						inMap->FindL( KStartTime, inParam ) ) 
				{
				ValidateParamTypeL( inParam, LIW::EVariantTypeTTime, 
									KCmdAdd, KStartTime, KInvalid );
				
				entryAttributes->SetStartTimeL( inParam.AsTTime() );
				}
				
			if ( ( ( entryType == CCalEntry::EAppt ) ||
					( entryType == CCalEntry::ETodo ) ||
					( entryType == CCalEntry::EEvent ) ) &&  
					inMap->FindL( KEndTime, inParam ) )
				{
				ValidateParamTypeL( inParam, LIW::EVariantTypeTTime, 
									KCmdAdd, KEndTime, KInvalid );
				
				entryAttributes->SetEndTimeL( inParam.AsTTime() );
				}
				
			if ( inMap->FindL( KAlarmTime, inParam ) ) 
				{
				ValidateParamTypeL( inParam, LIW::EVariantTypeTTime, 
									KCmdAdd, KAlarmTime, KInvalid );
				
				entryAttributes->SetAlarm( inParam.AsTTime() );
				}
				
			if( ( entryType == CCalEntry::EAppt ) ||
					( entryType == CCalEntry::ETodo ) )
				{
				if ( inMap->FindL( KStatus, inParam ) ) 
					{
					ValidateParamTypeL( inParam, LIW::EVariantTypeDesC, 
										KCmdAdd, KStatus, KInvalid );
					
					entryAttributes->SetEntryStatusL( inParam.AsDes() );
					}
				}
				
			if( entryType == CCalEntry::EAppt )
				{
				// Applicable only for Update request
				if ( isUpdate && inMap->FindL( KInstStartTime, inParam ) ) 
					{
					ValidateParamTypeL( inParam, LIW::EVariantTypeTTime, 
										KCmdAdd, KInstStartTime, KInvalid );
					
					entryAttributes->SetInstanceStartTimeL( inParam.AsTTime() );
					}

				if ( inMap->FindL( KLocation, inParam ) ) 
					{
					ValidateParamTypeL( inParam, LIW::EVariantTypeDesC, 
										KCmdAdd, KLocation, KInvalid );
					
					entryAttributes->SetLocationL( inParam.AsDes() );
					}
					
				if ( inMap->FindL( KMethod, inParam ) ) 
					{
					ValidateParamTypeL( inParam, LIW::EVariantTypeDesC, 
										KCmdAdd, KMethod, KInvalid );
					
					entryAttributes->SetMethodL( inParam.AsDes() );
					}
					
				if ( inMap->FindL( KSeqNum, inParam ) ) 
					{
					ValidateParamTypeL( inParam, LIW::EVariantTypeTInt32, 
										KCmdAdd, KSeqNum, KInvalid );
					
					entryAttributes->SetSequenceNumber( inParam.AsTInt32() );
					}
					
				if ( inMap->FindL( KPhoneOwner, inParam ) ) 
					{
					ValidateParamTypeL( inParam, LIW::EVariantTypeDesC, 
										KCmdAdd, KPhoneOwner, KInvalid );
					
					entryAttributes->SetPhoneOwnerDataL( inParam.AsDes() );
					}
				
				if ( inMap->FindL( KOrganizer, inParam ) ) 
					{
					const CLiwMap* map = inParam.AsMap();
					if ( map )
						{
						TLiwVariant orgParam;
						CleanupStack::PushL( TCleanupItem(TLiwVariant::VariantCleanup , &orgParam));
						if ( map->FindL( KAddress, orgParam ) ) 
							{
							CAttendeeInfo* organizer = CAttendeeInfo::NewL( orgParam.AsDes() );
							CleanupStack::PushL( organizer );
							if ( map->FindL( KCommonName, orgParam ) ) 
								{
								ValidateParamTypeL( orgParam, LIW::EVariantTypeDesC, 
													KCmdAdd, KCommonName, KInvalid );
								
								organizer->SetCommonNameL( orgParam.AsDes() ); 
								}
							entryAttributes->SetOrganizerDataL( organizer );
							CleanupStack::PopAndDestroy( organizer ); 
							}
						else
							{
							AppendErrorMessageL(KCmdAdd, KOrganizer, KInvalid );
							User::Leave( KErrArgument );
							}
						CleanupStack::Pop( &orgParam );
						orgParam.Reset(); 
						}
					else
						{
						AppendErrorMessageL(KCmdAdd, KOrganizer, KInvalid );
						User::Leave( KErrArgument );
						}	
					}
				
				if ( inMap->FindL( KAttendeeList, inParam ) ) 
					{
					const CLiwList* obj = inParam.AsList();
					if ( obj )
						{
						TInt count = obj->Count();
						for ( int index = 0; index < count; index++ )
							{
							TLiwVariant element;
							CleanupStack::PushL( TCleanupItem(TLiwVariant::VariantCleanup , &element));
							obj->AtL(index, element);
							const CLiwMap* map = element.AsMap();
							TLiwVariant attParam;
							CleanupStack::PushL( TCleanupItem(TLiwVariant::VariantCleanup , &attParam));
							if ( map && map->FindL(KAddress, attParam) )
								{
								ValidateParamTypeL( attParam, LIW::EVariantTypeDesC, 
												KCmdAdd, KAddress, KInvalid );

								CAttendeeInfo* attendee = CAttendeeInfo::NewL( attParam.AsDes() );
								CleanupStack::PushL( attendee );
								if ( map->FindL( KCommonName, attParam ) ) 
									{
									ValidateParamTypeL( attParam, LIW::EVariantTypeDesC, 
												KCmdAdd, KCommonName, KInvalid );

									attendee->SetCommonNameL( attParam.AsDes() ); 
									}
								if ( map->FindL( KRole, attParam ) ) 
									{
									ValidateParamTypeL( attParam, LIW::EVariantTypeDesC, 
												KCmdAdd, KRole, KInvalid );

									attendee->SetRoleL( attParam.AsDes() ); 
									}
								
								if ( map->FindL( KStatus, attParam ) ) 
									{
									ValidateParamTypeL( attParam, LIW::EVariantTypeDesC, 
												KCmdAdd, KStatus, KInvalid );

									attendee->SetStatusL( attParam.AsDes() ); 
									}

								if ( map->FindL( KRsvp, attParam ) ) 
									{
									ValidateParamTypeL( attParam, LIW::EVariantTypeTBool, 
												KCmdAdd, KRsvp, KInvalid );

									attendee->SetRsvp( attParam.AsTBool() ); 
									}
								entryAttributes->AddAttendeeL( attendee );
								CleanupStack::PopAndDestroy( attendee ); 
								}
							else
								{
								AppendErrorMessageL(KCmdAdd, KAttendeeList, KInvalid);
								User::Leave( KErrArgument );
								}
							CleanupStack::Pop( &attParam );	
							attParam.Reset();
							CleanupStack::Pop( &element );
	                        element.Reset();
							}
						}
					else
						{
						AppendErrorMessageL(KCmdAdd, KAttendeeList, KInvalid);
						User::Leave( KErrArgument );
						}	
					}
					
				if( inMap->FindL( KRepeatDates, inParam ) )
					{
					const CLiwList* obj = inParam.AsList();
					if ( obj )
						{
						for ( int index = 0; index < obj->Count(); index++ )
							{
							TLiwVariant element;
							CleanupStack::PushL( TCleanupItem(TLiwVariant::VariantCleanup , &element));
							obj->AtL(index, element);

							ValidateParamTypeL( element, LIW::EVariantTypeTTime, 
											KCmdAdd, KRepeatDates, KInvalid);

							TTime reptDate = element.AsTTime();
							entryAttributes->AddRepeatDateL( reptDate );
							CleanupStack::Pop( &element );	
							element.Reset();
							}	
						}
					else
						{
						AppendErrorMessageL(KCmdAdd, KRepeatDates, KInvalid);
						User::Leave( KErrArgument );	
						}
					}
					
				if( inMap->FindL( KExceptionDates, inParam ) )
					{
					const CLiwList* obj = inParam.AsList();
					if ( obj )
						{
						for ( int index = 0; index < obj->Count(); index++ )
							{
							TLiwVariant element;
							CleanupStack::PushL( TCleanupItem(TLiwVariant::VariantCleanup , &element));
							obj->AtL(index, element);

							ValidateParamTypeL( element, LIW::EVariantTypeTTime, 
											KCmdAdd, KExceptionDates, KInvalid );

							TTime exDate = element.AsTTime();
							entryAttributes->AddExceptionDateL( exDate );
							CleanupStack::Pop( &element );	
							element.Reset();
							}	
						}
					else
						{
						inParam.Reset();
						AppendErrorMessageL( KCmdAdd, KExceptionDates, KInvalid );
						User::Leave( KErrArgument );	
						}
					}
			
				if ( inMap->FindL( KRepeatRule, inParam ) ) 
					{
					const CLiwMap* map = inParam.AsMap();
					if ( map )
						{
						CRepeatInfo* rrule = NULL;
						TLiwVariant rptParam;
						CleanupStack::PushL( TCleanupItem(TLiwVariant::VariantCleanup , &rptParam));
						if ( map->FindL( KRepeatType, rptParam ) ) 
							{
							ValidateParamTypeL( rptParam, LIW::EVariantTypeTInt32, 
											KCmdAdd, KRepeatType, KInvalid );

							rrule = CRepeatInfo::NewL( rptParam.AsTInt32() );
							CleanupStack::PushL( rrule );
	                        }
						else
							{
							AppendErrorMessageL( KCmdAdd, KRepeatType, KMissing );
							User::Leave( KErrArgument );
							}	
							
						if ( map->FindL( KDaysInWeek, rptParam ) ) 
							{
							const CLiwList* obj = rptParam.AsList();
							if ( obj )
								{
								RArray < TDay > days;
								for ( int index = 0; index < obj->Count(); index++ )
									{
									TLiwVariant element;
									CleanupStack::PushL( TCleanupItem(TLiwVariant::VariantCleanup , &element));
									obj->AtL(index, element);

									ValidateParamTypeL( element, LIW::EVariantTypeTInt32, 
														KCmdAdd, KDaysInWeek, KInvalid );

									days.Append( TDay(  element.AsTInt32() ) );
									if( element.AsTInt32() < 0 || element.AsTInt32() > 6 )
										{
										days.Close();
										AppendErrorMessageL( KCmdAdd, KDaysInWeek, KInvalid );
										User::Leave( KErrArgument );	
										}
									CleanupStack::Pop( &element );
									element.Reset(); 
									}
								rrule->SetDaysInWeek(days);
								days.Close();
								}
							else
								{
								AppendErrorMessageL( KCmdAdd, KDaysInWeek, KInvalid );
								User::Leave( KErrArgument );	
								}
							}

						if ( map->FindL( KUntilDate, rptParam ) ) 
							{
							ValidateParamTypeL( rptParam, LIW::EVariantTypeTTime, 
											KCmdAdd, KUntilDate, KInvalid );

							rrule->SetUntilTimeL( rptParam.AsTTime() );
							}
						
						if ( map->FindL( KRStartDate, rptParam ) ) 
							{
							ValidateParamTypeL( rptParam, LIW::EVariantTypeTTime, 
											KCmdAdd, _L8("RepeatRule:StartDate"), KInvalid );

							rrule->SetStartTimeL( rptParam.AsTTime() );
							}
						if ( map->FindL( KInterval, rptParam ) ) 
							{
							ValidateParamTypeL( rptParam, LIW::EVariantTypeTInt32, 
											KCmdAdd, KInterval, KInvalid );

							rrule->SetInterval( rptParam.AsTInt32() );
							}
							
						if ( map->FindL( KMonthDays, rptParam ) ) 
							{
							const CLiwList* obj = rptParam.AsList();
							if ( obj )
								{
								RArray < TInt > days;
								for ( int index = 0; index < obj->Count(); index++ )
									{
									TLiwVariant element;
									CleanupStack::PushL( TCleanupItem(TLiwVariant::VariantCleanup , &element));

									obj->AtL(index, element);

									ValidateParamTypeL( element, LIW::EVariantTypeTInt32, 
											KCmdAdd, KMonthDays, KInvalid );

									TInt mthdays = element.AsTInt32();
									if( mthdays < 0 || mthdays > 30 )
										{
										days.Close();
										AppendErrorMessageL( KCmdAdd, KMonthDays, KInvalid );
										User::Leave( KErrArgument );	
										}
									days.Append( TDay(  mthdays ) );
									CleanupStack::Pop( &element );
									element.Reset();
									}
								rrule->SetMonthDates(days);
								days.Close();
								}
							else
								{
								AppendErrorMessageL( KCmdAdd, KMonthDays, KInvalid );
								User::Leave( KErrArgument );	
								}	
							}
						
						if ( map->FindL( KDaysOfMonth, rptParam ) ) 
							{
							const CLiwList* obj = rptParam.AsList();
							if ( obj )
								{
								RArray <TCalRRule::TDayOfMonth> monthdays;
								TInt count = obj->Count();
								for ( int index = 0; index < count ; index++ )
									{
									TLiwVariant element;
									CleanupStack::PushL( TCleanupItem(TLiwVariant::VariantCleanup , &element));
									obj->AtL(index, element);
									const CLiwMap* map = element.AsMap();
									if( map )
										{
										TLiwVariant dayno;
										TLiwVariant week;
										
										if ( map->FindL( KDay, dayno ) && map->FindL( KWeekNum, week ) ) 
											{
											ValidateParamTypeL( dayno, LIW::EVariantTypeTInt32, 
													KCmdAdd, _L8("RepeatRule:DaysOfMonth:Day"), KInvalid );

											ValidateParamTypeL( week, LIW::EVariantTypeTInt32, 
													KCmdAdd, KRepeatWeekNum, KInvalid );

											TInt weekno = week.AsTInt32();
											TInt daynum = dayno.AsTInt32();
											
											if ( ( ( weekno == -1 ) || ( weekno >=1 && weekno <=4 ) ) &&
											     ( daynum >=0 && daynum <=6 ))
												{
												monthdays.Append(TCalRRule::TDayOfMonth( TDay( daynum ), weekno ) );
												}
											else
												{
												AppendErrorMessageL(KCmdAdd, KRepeatWeekNum, KInvalid);
												User::Leave( KErrArgument );
												}
											}
										dayno.Reset();
										week.Reset();
										CleanupStack::Pop( &element );
										element.Reset();
										}
									else
										{
										AppendErrorMessageL(KCmdAdd, KDaysOfMonth, KInvalid);
										User::Leave( KErrArgument );	
										}	
									}
								rrule->SetMonthDays( monthdays );
								monthdays.Close();
								}
							else
								{
								AppendErrorMessageL(KCmdAdd, KDaysOfMonth, KInvalid);
								User::Leave( KErrArgument );	
								}
							}
								
						if ( map->FindL( KMonth, rptParam ) ) 
							{
							ValidateParamTypeL( rptParam, LIW::EVariantTypeTInt32, 
									KCmdAdd, KMonth, KInvalid );

							TInt rptmonth = rptParam.AsTInt32();
							if( rptmonth <0 || rptmonth > 11 )
								{
								AppendErrorMessageL( KCmdAdd, KMonth, KInvalid );
								User::Leave( KErrArgument );
								}
							rrule->SetMonth( rptmonth );
							}
						entryAttributes->SetRepeatRule( rrule );
						CleanupStack::PopAndDestroy( rrule );
						CleanupStack::Pop( &rptParam );	
						rptParam.Reset();
						}
					else
						{
						AppendErrorMessageL( KCmdAdd, KRepeatRule, KInvalid );
						User::Leave( KErrArgument );
						}
					
					}
				}
			

			CleanupStack::Pop( &inParam );
			inParam.Reset();	
			}
		else
			{
			AppendErrorMessageL( KCmdAdd, KItem, KInvalid );
			User::Leave( KErrArgument );
			}	
		
		}
	else
		{
		AppendErrorMessageL( KCmdAdd, KItem, KMissing );
		User::Leave( KErrArgument );
		}
	CleanupStack::Pop( entryAttributes );
	return entryAttributes;
	}

// ---------------------------------------------------------------------------
// Extracts Delete Filter from input param list
// ---------------------------------------------------------------------------
//
void CCalendarInterface::GetDeleteEntryFilterL(const CLiwGenericParamList& aInParamList, 
													CCalendarFilter& aFilter, 
													const TBool aPosBased )
	{
	const TLiwGenericParam* filter = NULL; 

	if ( aPosBased )
		{
		if ( aInParamList.Count() > 1 )
			filter = &aInParamList[1];
		}
	else
		{
		TInt pos = 0 ;
		filter = aInParamList.FindFirst( pos, KData );
		}
		
	if ( filter )
		{
		const CLiwMap* filterMap = filter->Value().AsMap(); 
		if ( filterMap )
			{
			TLiwVariant param;
			CleanupStack::PushL( TCleanupItem(TLiwVariant::VariantCleanup , &param));
			if( filterMap->FindL( KStartRange, param ))
				{
				ValidateParamTypeL( param, LIW::EVariantTypeTTime, 
									KCmdDelete, KStartRange, KInvalid );
									
				aFilter.SetStartTimeL(param.AsTTime());
				}

			if( filterMap->FindL( KEndRange, param ))
				{
				ValidateParamTypeL( param, LIW::EVariantTypeTTime, 
									KCmdDelete, KEndRange, KInvalid );
									
				aFilter.SetEndTimeL(param.AsTTime());
				}

			if( filterMap->FindL( KDeleteAll, param ))
				{
				ValidateParamTypeL( param, LIW::EVariantTypeTBool, 
									KCmdDelete, KDeleteAll, KInvalid );
									
				aFilter.SetDeleteAll( param.AsTBool() );
				}

			if( filterMap->FindL( KIdList, param ))
				{
				const CLiwList* guidList = param.AsList();
				if ( guidList )
					{
					TLiwVariant listElement;
					CleanupStack::PushL( TCleanupItem(TLiwVariant::VariantCleanup , &listElement));
					TInt count = guidList->Count();
					for(TInt index = 0; index < count; index++)
						{
						if ( guidList->AtL(index, listElement) )
							{
							//aFilter.AddGuidL( listElement.AsData() );
							ValidateParamTypeL( listElement, LIW::EVariantTypeDesC, 
									KCmdDelete, KIdList, KInvalid );
												
							HBufC8* globalUid = HBufC8::NewL(listElement.AsDes().Length());
							CleanupStack::PushL( globalUid );
							GetGlobalUid(listElement.AsDes(), globalUid->Des());
							aFilter.AddGuidL( globalUid->Des() );
							CleanupStack::PopAndDestroy( globalUid );
							}
						}
					CleanupStack::Pop( &listElement );	
					listElement.Reset();
					}
				else
					{
					AppendErrorMessageL( KCmdDelete, KIdList, KInvalid );
					User::Leave(KErrArgument);
					}	
				}

			if( filterMap->FindL( KLocalIdList, param ))
				{
				const CLiwList* luidList = param.AsList();
				if ( luidList )
					{
					TLiwVariant listElement;
					CleanupStack::PushL( TCleanupItem(TLiwVariant::VariantCleanup , &listElement));
					TInt count = luidList->Count();
					for(TInt index = 0; index < count; index++)
						{
						if ( luidList->AtL(index, listElement) )
							{
							//aFilter.AddLocalUid( TCalLocalUid( listElement.AsTUint() ));
							ValidateParamTypeL( listElement, LIW::EVariantTypeDesC, 
									KCmdDelete, KLocalIdList, KInvalid );
									

							TCalLocalUid localUid;
							GetLocalUid( listElement.AsDes(), localUid );
							aFilter.AddLocalUid( localUid );
							}
						}
					CleanupStack::Pop( &listElement );	
					listElement.Reset();
					}
				else
					{
					AppendErrorMessageL( KCmdDelete, KLocalIdList, KInvalid );
					User::Leave(KErrArgument);
					}	
				}
			CleanupStack::Pop( &param );
			param.Reset();	
			}
		else
			{
			AppendErrorMessageL( KCmdDelete, KData, KInvalid );
			User::Leave(KErrArgument);
			}
		}
	else
		{
		AppendErrorMessageL( KCmdDelete, KData, KMissing );
		User::Leave(KErrArgument);
		}
	}
	
// ---------------------------------------------------------------------------
// Extracts Import input from input param list
// ---------------------------------------------------------------------------
//
void CCalendarInterface::GetImportInputL( const CLiwGenericParamList& aInParamList,
													  TBool    aPosBased, 
													  HBufC8*& aInputBuffer, 
													  TDes&   importFile,
													  TDes8&  aCalendarFormat, 
													  TDes&   aCalendarName )
	{

	//get the Input Filter Map
    const TLiwGenericParam* inMap = NULL;

  	if( aPosBased )
  		{
  		if( aInParamList.Count() > 1 )
			inMap = &(aInParamList[1]);//start searching from pos and reset the pos to found at index
  		}
	else
		{
	  	TInt pos = 0;
		inMap = aInParamList.FindFirst( pos, KData );
		}

	if ( inMap )
		{
	    const CLiwMap * filterMap = inMap->Value().AsMap();
	    
	    if ( filterMap )
	    	{
		    TLiwVariant value;
		    CleanupStack::PushL( TCleanupItem(TLiwVariant::VariantCleanup , &value));
		 	
			if ( filterMap->FindL( KCalendarName, value ))
				{
				ValidateParamTypeL( value, LIW::EVariantTypeDesC, 
									KCmdImport, KCalendarName, KInvalid );
									
				aCalendarName.Copy( value.AsDes() );
				}

			if ( filterMap->FindL( KCalendarFormat, value ))
				{
				ValidateParamTypeL( value, LIW::EVariantTypeDesC, 
									KCmdImport, KCalendarFormat, KInvalid );
									
				aCalendarFormat.Copy( value.AsDes() );
				}
			else
				{
				AppendErrorMessageL( KCmdImport, KCalendarFormat, KMissing );
				User::Leave( KErrArgument );
				}	

			if ( filterMap->FindL( KInputBuffer, value ))
				{
				ValidateParamTypeL( value, LIW::EVariantTypeDesC8, 
									KCmdImport, KInputBuffer, KInvalid );
									
				aInputBuffer = value.AsData().AllocL();
				}
			else if ( filterMap->FindL( KImExFileName, value ))
				{
				ValidateParamTypeL( value, LIW::EVariantTypeDesC, 
									KCmdImport, KImExFileName, KInvalid );
									
				importFile.Copy( value.AsDes() );
				}
			else	
				{
				AppendErrorMessageL( KCmdImport, KImExFileName, KMissing );
				User::Leave( KErrArgument );
				}
			CleanupStack::Pop( &value );
			value.Reset();
			
	    	}
		else
			{
			AppendErrorMessageL( KCmdImport, KData, KInvalid );
			User::Leave( KErrArgument );
			}
		}
	else
		{
		AppendErrorMessageL( KCmdImport, KData, KMissing );
		User::Leave( KErrArgument );
		}	
 	}

// ---------------------------------------------------------------------------
// Extracts Export input from input param list
// ---------------------------------------------------------------------------
//
void CCalendarInterface::GetExportInputL( const CLiwGenericParamList& aInParamList, 
												      TBool                  aPosBased, 
												      CCalendarExportParams& aCalExportParams )
	{
    const TLiwGenericParam* inMap = NULL;	//get the Input Filter Map

    TInt pos = 0;

    if( aPosBased )
	    {
	    if( aInParamList.Count() > 1 )	
	    	inMap = &(aInParamList[1]);
	    }
	else
		inMap = aInParamList.FindFirst( pos, KData );

    if( inMap )
	    {
	    const CLiwMap *filterMap = inMap->Value().AsMap();
   	
	   	if( filterMap )
	   		{
			TLiwVariant tLiwVariantValue;
			CleanupStack::PushL( TCleanupItem(TLiwVariant::VariantCleanup , &tLiwVariantValue));
		
			if ( filterMap->FindL( KImExFileName, tLiwVariantValue ))
				{
				ValidateParamTypeL( tLiwVariantValue, LIW::EVariantTypeDesC, 
									KCmdExport, KImExFileName, KInvalid );
									
				aCalExportParams.SetExportFileNameL( tLiwVariantValue.AsDes() );
				}

			
		 	TLiwVariant tLiwVariantValueTemp;
		 	CleanupStack::PushL( TCleanupItem(TLiwVariant::VariantCleanup , &tLiwVariantValueTemp));
		  	if( filterMap->FindL( KCalendarGuidList, tLiwVariantValue ) )
				{
				const CLiwList *cLiwList = tLiwVariantValue.AsList();
				
				if ( cLiwList )
					{
					for( TInt x = 0; x < cLiwList->Count(); ++x )
						{
						cLiwList->AtL( x , tLiwVariantValueTemp );
						
						ValidateParamTypeL( tLiwVariantValueTemp, LIW::EVariantTypeDesC, 
									KCmdExport, KCalendarGuidList, KInvalid );
									
						HBufC8* globalUid = HBufC8::NewL(tLiwVariantValueTemp.AsDes().Length());
						CleanupStack::PushL( globalUid );
						GetGlobalUid(tLiwVariantValueTemp.AsDes(), globalUid->Des());
						aCalExportParams.AddGuidL( globalUid->Des() );
						CleanupStack::PopAndDestroy( globalUid );
						}
					}
				else
					{
					AppendErrorMessageL( KCmdExport, KCalendarGuidList, KInvalid );
					User::Leave( KErrArgument );	
					}	
				
				}

			if( filterMap->FindL( KCalendarLuidList, tLiwVariantValue ) )
				{
				const CLiwList *cLiwListTemp = tLiwVariantValue.AsList();
				
				if ( cLiwListTemp )
					{
					if( cLiwListTemp->Count() && ( aCalExportParams.Params() & CCalendarExportParams::EParamsGUid ) )
						{//means the GUIDS are set so break, as both GUIDS and LUids cant be set
						AppendErrorMessageL(KCmdExport, KNullDesC8,_L("Only one of IdList and LocalIdList can be given"));
						User::Leave( KErrArgument );
						}
						
					for( TInt x = 0; x < cLiwListTemp->Count(); ++x )
						{
						cLiwListTemp->AtL( x , tLiwVariantValueTemp );
						
						ValidateParamTypeL( tLiwVariantValueTemp, LIW::EVariantTypeDesC, 
									KCmdExport, KCalendarLuidList, KInvalid );
									
						TCalLocalUid localUid;
						GetLocalUid( tLiwVariantValueTemp.AsDes(), localUid );
						aCalExportParams.AddLocalUid( localUid );
						}	
					}
				else
					{
					AppendErrorMessageL( KCmdExport, KCalendarLuidList, KInvalid );
					User::Leave( KErrArgument );	
					}	
				}
				
			CleanupStack::Pop( &tLiwVariantValueTemp );
			tLiwVariantValueTemp.Reset();
			CleanupStack::Pop( &tLiwVariantValue );
			tLiwVariantValue.Reset();
	   		}
	   	else	
			{
			AppendErrorMessageL( KCmdExport, KData, KInvalid );
			User::Leave( KErrArgument );
			}
	    }
	else
		{
		AppendErrorMessageL( KCmdExport, KData, KMissing );
		User::Leave( KErrArgument );
		}    
	}

// ---------------------------------------------------------------------------
// Extracts Change Notification filter from input param list
// ---------------------------------------------------------------------------
//
void CCalendarInterface::GetNotificationFilterL(const CLiwGenericParamList& aInParamList, 
													CCalendarFilter& aFilter, 
													const TBool aPosBased )
	{
	const TLiwGenericParam* filter = NULL; 

	if ( aPosBased )
		{
		if ( aInParamList.Count() > 1 )
			filter = &aInParamList[1];
		}
	else
		{
		TInt pos = 0 ;
		filter = aInParamList.FindFirst( pos, KFilter );
		}
		
	if ( filter )
		{
		const CLiwMap* filterMap = filter->Value().AsMap(); 
		if ( filterMap )
			{
			TLiwVariant param;
			CleanupStack::PushL( TCleanupItem(TLiwVariant::VariantCleanup , &param));
			if( filterMap->FindL( KStartRange, param ))
				{
				ValidateParamTypeL( param, LIW::EVariantTypeTTime, 
					KCmdReqNot, KStartRange, KInvalid );
							
				aFilter.SetStartTimeL(param.AsTTime());
				}

			if( filterMap->FindL( KEndRange, param ))
				{
				ValidateParamTypeL( param, LIW::EVariantTypeTTime, 
					KCmdReqNot, KEndRange, KInvalid );
							
				aFilter.SetEndTimeL(param.AsTTime());
				}

			if( filterMap->FindL( KIncludeUndatedTodos, param ))
				{
				ValidateParamTypeL( param, LIW::EVariantTypeTBool, 
					KCmdReqNot, KIncludeUndatedTodos, KInvalid );
							
				aFilter.SetIncludeUnDateToDo( param.AsTBool() );
				}

			if( filterMap->FindL( KLocalIdList, param ))
				{
				const CLiwList* luidList = param.AsList();
				if ( luidList )
					{
					TLiwVariant listElement;
					CleanupStack::PushL( TCleanupItem(TLiwVariant::VariantCleanup , &listElement));
					TInt count = luidList->Count();
					for(TInt index = 0; index < count; index++)
						{
						if ( luidList->AtL(index, listElement) )
							{
							TCalLocalUid localUid;

							ValidateParamTypeL( listElement, LIW::EVariantTypeDesC, 
											KCmdReqNot, KLocalIdList, KInvalid );
										
							GetLocalUid( listElement.AsDes(), localUid );
							aFilter.AddLocalUid( localUid );
							}
						}
					CleanupStack::Pop( &listElement );
					listElement.Reset();
					}
				else
					{
					AppendErrorMessageL( KCmdReqNot, KLocalIdList, KInvalid );
					User::Leave(KErrArgument);
					}
				}
			CleanupStack::Pop( &param );
			param.Reset();	
			}
		else
			{
			AppendErrorMessageL( KCmdReqNot, KFilter, KInvalid );
			User::Leave(KErrArgument);
			}
		}
	}
	

// ---------------------------------------------------------------------------
// Extracts LocalUid as TCalLocalUid from input Uid String
// ---------------------------------------------------------------------------
//
void CCalendarInterface::GetLocalUid( const TDesC& aLocalUid, TCalLocalUid& aOutLocalUid )
	{
	aOutLocalUid = 0;
	/*if( aLocalUid.Length() )
		{
		TInt sepPos = aLocalUid.Locate( KUidSeparator );
		TPtrC temp;
		if( sepPos == KErrNotFound )
			{
			temp.Set(aLocalUid.Mid(0));
			}
		else
			{
			temp.Set(aLocalUid.Mid(0, sepPos));
			}
	    }*/
		TLex lex(aLocalUid);
		TInt32 num;

		if(lex.Val(num) == KErrNone)
			aOutLocalUid = TCalLocalUid(num);
		
	}

// ---------------------------------------------------------------------------
// Extracts GlobalUid as 8-bit string from input Uid String
// ---------------------------------------------------------------------------
//
void CCalendarInterface::GetGlobalUid( const TDesC& aGlobalUid, TPtr8 aOutGlobalUid )
	{
	if( aGlobalUid.Length() )
		{
		/*TInt sepPos = aGlobalUid.Locate( KUidSeparator );

		if( sepPos == KErrNotFound )
			{
			aOutGlobalUid.Copy( aGlobalUid.Mid(0) );
			}
		else
			{
			aOutGlobalUid.Copy( aGlobalUid.Mid( sepPos + 1 ) );
			}*/
		aOutGlobalUid.Copy( aGlobalUid );	
		}
		
	}

// ---------------------------------------------------------------------------
// ErrCode Conversion
// ---------------------------------------------------------------------------
//
TInt32 CCalendarInterface::ErrCodeConversion(TInt code)
	{
	TInt32 err;
	switch (code)
		{
			case KErrCancel:
							// Returning KErrNone incase of KErrCancel
			case KErrNone:
							err= SErrNone;
							break;

			case KErrNotFound:
							err= SErrNotFound;
							break;

			case KErrNoMemory:
							err = SErrNoMemory;
							break;

			case KErrInUse:
							err = SErrServiceInUse;
							break;

			case KErrNotSupported:
							err = SErrServiceNotSupported;
							break;

			case KErrBadName:
							err = SErrBadArgumentType;
							break;
							
			case KErrArgument: 
							err = SErrInvalidServiceArgument;
							break;
							
			case KErrAccessDenied: 
							err = SErrAccessDenied;
							break;
							
			case KErrPathNotFound:
							err = SErrPathNotFound; 
							break;
						
			case KErrAlreadyExists:
							err = SErrEntryExists;
							break;
		
			default 		:
							err = SErrGeneralError;
							break;
		}
	
	    return err;
		
	}

// ---------------------------------------------------------------------------
// Validate the type of the input param with the expected type
// ---------------------------------------------------------------------------
//
void CCalendarInterface::ValidateParamTypeL( TLiwVariant& aParam, 
											LIW::TVariantTypeId aExpectedtype, 
											const TDesC8& aCmdName, 
											const TDesC8& aParameter,
											const TDesC& aMessage )
	{
	if( aParam.TypeId() != aExpectedtype )
		{
		AppendErrorMessageL(aCmdName, aParameter, aMessage);
		aParam.Reset();
		User::Leave(KErrArgument);
		}
	}

// ---------------------------------------------------------------------------
// Append Error Message
// ---------------------------------------------------------------------------
//
void CCalendarInterface::AppendErrorMessageL( const TDesC8& aCmdName, const TDesC8& aParameter, const TDesC& aMessage )
	{
	iErrorMessage = HBufC::NewL( KMaxErrorMessageLength );
	TPtr tmpMsgPtr = iErrorMessage->Des();
	tmpMsgPtr.Copy(KDomainName);
	
	HBufC* temp = HBufC::NewL( KMaxErrorMessageLength );

	if ( aCmdName.Length() )
		{
		tmpMsgPtr.Append( KErrorMsgSeparator );
		temp->Des().Copy( aCmdName ); 
		tmpMsgPtr.Append( temp->Des() );
		}

	tmpMsgPtr.Append(KErrorMsgSeparator);
	
	if ( aParameter.Length() )
		{
		temp->Des().Copy(aParameter); 
		tmpMsgPtr.Append(temp->Des());
		}
	
	if ( aMessage.Length() )
		{
		tmpMsgPtr.Append( aMessage );
		}

	delete temp;	
	}

// ---------------------------------------------------------------------------
// Set Import output to output parameter
// ---------------------------------------------------------------------------
//
void CCalendarInterface::SetImportOutputL( RPointerArray<TUIDSet>& aOutputUIDSet, CLiwGenericParamList& aOutParamList )
	{
	TInt arrCount = aOutputUIDSet.Count();
						
	//List of Maps
	CLiwDefaultList *uIDList = CLiwDefaultList::NewL();
	
	CleanupClosePushL( *uIDList );
	
	for( TInt index = 0; index < arrCount; ++index )
		{
		TLiwVariant liwVariant;
		CleanupStack::PushL( TCleanupItem(TLiwVariant::VariantCleanup , &liwVariant));
		
		GetTLiwVariantForUIDSetL( liwVariant, aOutputUIDSet[ index ] );
		
		uIDList->AppendL( liwVariant );
		
		CleanupStack::Pop( &liwVariant );
		liwVariant.Reset();
		}
			
	//Iterator over List of Maps	
	CIterableUIDMapList *outputIterableList = CIterableUIDMapList::NewL( uIDList );
	
	CleanupClosePushL( *outputIterableList );
	// Appending the Iteratot over List of Maps to the outParamList CLiwGenericParamList 
	aOutParamList.AppendL( TLiwGenericParam( KReturnValue, TLiwVariant( outputIterableList ) ) );
						
	CleanupStack::PopAndDestroy( outputIterableList );//doubt check at debugging
	
	CleanupStack::Pop( uIDList );
	}
// ---------------------------------------------------------------------------
// Set getlist output to output parameter
// ---------------------------------------------------------------------------
//
void CCalendarInterface::SetCalEntryOutputL( RPointerArray<CCalEntry>& aOutputCalEntry, 
                                             CLiwGenericParamList& aOutParamList, 
                                             const TDesC& aCalendarName )
    {
 
    TInt arrCount = aOutputCalEntry.Count();
    
    CIterableCalEntryList* iterEntryList = CIterableCalEntryList::NewL( *this, aCalendarName, ETrue );
   CleanupStack::PushL(  TCleanupItem(CleanupIterableCalEntry, iterEntryList ) );
            
    for( TInt index = 0; index < arrCount; ++index )
        {
            iterEntryList->EntryArray().Append(aOutputCalEntry[index]);
        }

     //Appending the Iterator over List of Maps to the outParamList CLiwGenericParamList 
    aOutParamList.AppendL( TLiwGenericParam( KReturnValue, TLiwVariant( iterEntryList ) ) );
                        
    iterEntryList->DecRef();
    
    iArrayCalEntryList.Append( iterEntryList );
    
    CleanupStack::Pop( iterEntryList );

    }
// ---------------------------------------------------------------------------
// Set getlist output to output parameter
// ---------------------------------------------------------------------------
//
void CCalendarInterface::SetCalInstanceOutputL( RPointerArray<CCalInstance>& aOutputCalInstance,
                                                CLiwGenericParamList& aOutParamList,
                                                const TDesC& aCalendarName)
    {
    TInt arrCount = aOutputCalInstance.Count();

   CIterableCalEntryList* iterInstanceList = CIterableCalEntryList::NewL( *this, aCalendarName, EFalse );
    CleanupStack::PushL(  TCleanupItem(CleanupIterableCalEntry, iterInstanceList ) );
            
    for( TInt index = 0; index < arrCount; ++index )
        {
        iterInstanceList->InstanceArray().Append(aOutputCalInstance[index]);
        }

    // Appending the Iterator over List of Maps to the outParamList CLiwGenericParamList 
    aOutParamList.AppendL( TLiwGenericParam( KReturnValue, TLiwVariant( iterInstanceList ) ) );
                        
    iterInstanceList->DecRef();
    
    iArrayCalEntryList.Append( iterInstanceList );
    
    CleanupStack::Pop( iterInstanceList );
    

    }
// ---------------------------------------------------------------------------
// Set Change Notification output to output parameter
// ---------------------------------------------------------------------------
//
void CCalendarInterface::SetNotifyOutputL( RArray<TCalChangeEntry>& aOutputChangeSet, CLiwGenericParamList& aOutParamList )
	{
	TInt arrCount = aOutputChangeSet.Count();
						
	//List of Maps
	CLiwDefaultList *changeList = CLiwDefaultList::NewL();
	
	CleanupClosePushL( *changeList );
	
	for( TInt index = 0; index < arrCount; ++index )
		{
		TLiwVariant liwVariant;
		CleanupStack::PushL( TCleanupItem(TLiwVariant::VariantCleanup , &liwVariant));
		
		GetTLiwVariantForCalChangeEntryL( liwVariant, aOutputChangeSet[index] );
		
		changeList->AppendL( liwVariant );
		
		CleanupStack::Pop( &liwVariant );
		liwVariant.Reset();
		}
			
	//Iterator over List of Maps	
	CIterableUIDMapList *outputIterableList = CIterableUIDMapList::NewL( changeList );
	CleanupStack::Pop( changeList );
	CleanupClosePushL( *outputIterableList );
	
	// Appending the Iteratot over List of Maps to the outParamList CLiwGenericParamList 
	aOutParamList.AppendL( TLiwGenericParam( KReturnValue, TLiwVariant( outputIterableList ) ) );
						
	CleanupStack::PopAndDestroy( outputIterableList );
						
	}

// ---------------------------------------------------------------------------
// Set GlobalUid/LocalUid to the LiwVariant
// ---------------------------------------------------------------------------
//
void CCalendarInterface::GetTLiwVariantForUIDSetL( TLiwVariant& aValue, TUIDSet* aUIDSet )
	{
	HBufC* globalUid = HBufC::NewL( aUIDSet->iGlobalUID->Length() + 1 );
	CleanupStack::PushL( globalUid );
	globalUid->Des().Copy( aUIDSet->iGlobalUID->Des() );
	aValue.SetL( TLiwVariant(*globalUid));
	CleanupStack::PopAndDestroy( globalUid );
	}

// ---------------------------------------------------------------------------
// Set Change type to the LiwVariant
// ---------------------------------------------------------------------------
//
void CCalendarInterface::GetTLiwVariantForCalChangeEntryL( TLiwVariant& aValue, TCalChangeEntry& aChangeEntry )
	{
	CLiwDefaultMap* uIDMap = CLiwDefaultMap::NewL();
	
	CleanupClosePushL( *uIDMap ); 
	
	TBuf<20> localUid;
	
	localUid.Num( TInt64(aChangeEntry.iEntryId ));
	
	uIDMap->InsertL( KLocalId, TLiwVariant( localUid ) );

	uIDMap->InsertL( KChangeType, TLiwVariant( CCalendarInterface::GetChangeType( aChangeEntry.iChangeType ) ) );
	
	aValue.SetL( uIDMap );
	
	CleanupStack::PopAndDestroy( uIDMap );
	
	}

// ---------------------------------------------------------------------------
// Cleanup function for an CIterableCalEntryList
// ---------------------------------------------------------------------------
//
void CCalendarInterface::CleanupIterableCalEntry(void* aIterEntryList)
	{
	CIterableCalEntryList* iterEntryList = static_cast<CIterableCalEntryList*>(aIterEntryList);
	if ( iterEntryList )
		{
		iterEntryList->DecRef();
		}
	}
	
// ---------------------------------------------------------------------------
// Returns Day of Month of repeat rule as LiwVariant Map. Caller takes the ownership of map
// ---------------------------------------------------------------------------
//
CLiwDefaultMap* CCalendarInterface::GetDayOfMonthL( const TCalRRule::TDayOfMonth&  aDayOfMonth )
	{
	CLiwDefaultMap* dayMap = CLiwDefaultMap::NewL();
	CleanupClosePushL( *dayMap );

	dayMap->InsertL( KDay, TLiwVariant( TInt32( aDayOfMonth.Day() ) ));
	dayMap->InsertL( KWeekNum, TLiwVariant( TInt32( aDayOfMonth.WeekInMonth() ) ));
	
	CleanupStack::Pop( dayMap );
	return dayMap;
	}
	
// ---------------------------------------------------------------------------
// Returns CalUser as LiwVariant Map. Caller takes the ownership of map
// ---------------------------------------------------------------------------
//
CLiwDefaultMap* CCalendarInterface::GetCalUserL( CCalUser* aCalUser, TBool aAttendee )
	{
	CLiwDefaultMap* userMap = CLiwDefaultMap::NewL();
	CleanupClosePushL( *userMap );

	userMap->InsertL( KCommonName, TLiwVariant( aCalUser->CommonName() ) );
	userMap->InsertL( KAddress, TLiwVariant( aCalUser->Address() ) );
	
	if ( aAttendee )
		{
		userMap->InsertL( KRole, TLiwVariant( CCalendarInterface::GetAttendeeRoleL(((CCalAttendee*)aCalUser)->RoleL() ) ));
		userMap->InsertL( KStatus, TLiwVariant( CCalendarInterface::GetAttendeeStatusL(((CCalAttendee*)aCalUser)->StatusL() ) ));
		userMap->InsertL( KRsvp, TLiwVariant( ((CCalAttendee*)aCalUser)->ResponseRequested() ) );
		}
	
	CleanupStack::Pop( userMap );
	return userMap;
	}
	
// ---------------------------------------------------------------------------
// Returns array of CalTime as LiwVariant List. Caller takes the ownership of list
// ---------------------------------------------------------------------------
//
CLiwDefaultList* CCalendarInterface::GetDatesListL( RArray<TCalTime>& aDates ) 
	{
	TInt count = aDates.Count();

	CLiwDefaultList* dateList = CLiwDefaultList::NewL();
	CleanupClosePushL( *dateList );

	for ( TInt index = 0 ; index < count; index++ )
		{
		dateList->AppendL( aDates[index].TimeUtcL() );
		}
	
	CleanupStack::Pop( dateList );
	return dateList;
	}

// ---------------------------------------------------------------------------
// Returns RepeatRule as LiwVariant Map. Caller takes the ownership of map
// ---------------------------------------------------------------------------
//
CLiwDefaultMap* CCalendarInterface::GetRRMapL( const TCalRRule& repeatRule )
	{
	TCalRRule::TType rrType = repeatRule.Type();
	
	if ( rrType == TCalRRule::EInvalid )
		return NULL;
	
	CLiwDefaultMap* rrMap = CLiwDefaultMap::NewL();
	
	CleanupClosePushL( *rrMap );
	
	rrMap->InsertL( KRepeatType, TLiwVariant( TInt32( rrType ) ));
	
	rrMap->InsertL( KUntilDate, TLiwVariant( repeatRule.Until().TimeUtcL() ));
	
	rrMap->InsertL( KInterval, TLiwVariant( TInt32( repeatRule.Interval() )));
	
	rrMap->InsertL( KRStartDate, TLiwVariant( repeatRule.DtStart().TimeUtcL() ));
	
	if ( rrType == TCalRRule::EWeekly )
		{
		RArray<TDay> dayArray;
		repeatRule.GetByDayL( dayArray );
		
		CLiwDefaultList* dayList = CLiwDefaultList::NewL();
		CleanupClosePushL( *dayList );

		TInt count = dayArray.Count();
		for ( TInt index = 0 ; index < count; index++ )
			{
			dayList->AppendL( TInt32( dayArray[index] ));
			}
		
		rrMap->InsertL( KDaysInWeek, TLiwVariant( dayList ));
		
		CleanupStack::PopAndDestroy( dayList );

		dayArray.Reset();
		}
	else if ( rrType == TCalRRule::EMonthly )
		{
		RArray<TInt> monthDays;
		repeatRule.GetByMonthDayL( monthDays );
		TInt count = monthDays.Count();
		if ( count > 0 )
			{
			//
			CLiwDefaultList* dayList = CLiwDefaultList::NewL();
			CleanupClosePushL( *dayList );

			for ( TInt index = 0 ; index < count; index++ )
				{
				dayList->AppendL( TInt32(monthDays[index] ));
				}
			
			rrMap->InsertL( KMonthDays, TLiwVariant( dayList ));
			
			CleanupStack::PopAndDestroy( dayList );

			
			}
		else
			{
			RArray< TCalRRule::TDayOfMonth > daysOfMonth;
			repeatRule.GetByDayL( daysOfMonth );
			count = daysOfMonth.Count();
			if ( count > 0 )
				{
				CLiwDefaultList* dayList = CLiwDefaultList::NewL();
				CleanupClosePushL( *dayList );

    			for ( TInt index = 0; index < count; index++ )
    				{
		    		CLiwDefaultMap* dayOfMonthMap = CCalendarInterface::GetDayOfMonthL( daysOfMonth[index] );
					dayList->AppendL( TLiwVariant ( dayOfMonthMap ) );
					dayOfMonthMap->DecRef(); 
    				}
				
				rrMap->InsertL( KDaysOfMonth, TLiwVariant( dayList ));
				
				CleanupStack::PopAndDestroy( dayList );

				}
			daysOfMonth.Reset();
			}
		monthDays.Reset();
		}
	else if ( rrType == TCalRRule::EYearly )
		{
		RArray<TMonth> monthArray;
		repeatRule.GetByMonthL( monthArray );
		
		if ( monthArray.Count() > 0 )
			{
			rrMap->InsertL( KMonth, TLiwVariant( TInt32( monthArray[0] ) ));
			}
		monthArray.Reset();
		
		
		RArray< TCalRRule::TDayOfMonth > daysOfMonth;
		repeatRule.GetByDayL( daysOfMonth );
		TInt count = daysOfMonth.Count();
		if ( count > 0 )
			{
			CLiwDefaultList* dayList = CLiwDefaultList::NewL();
			CleanupClosePushL( *dayList );

			for ( TInt index = 0; index < count; index++ )
				{
	    		CLiwDefaultMap* dayOfMonthMap = CCalendarInterface::GetDayOfMonthL( daysOfMonth[index] );
				dayList->AppendL( TLiwVariant ( dayOfMonthMap ) );
				dayOfMonthMap->DecRef();
				}
			
			rrMap->InsertL( KDaysOfMonth, TLiwVariant( dayList ));
			
			CleanupStack::PopAndDestroy( dayList );

			}
		daysOfMonth.Reset();
		
		}

	CleanupStack::Pop( rrMap );
	
	return rrMap;
	}


// ---------------------------------------------------------------------------
// Returns string literal for the given Entry Type
// ---------------------------------------------------------------------------
//
TPtrC CCalendarInterface::GetEntryTypeL( const CCalEntry::TType aType )
	{
	TPtrC retValue;
	
	if ( aType == CCalEntry::EAppt )
		retValue.Set( KEntryAppt );
	
	else if ( aType == CCalEntry::ETodo )
		retValue.Set( KEntryTodo );
	
	else if ( aType == CCalEntry::EEvent )
		retValue.Set( KEntryEvent );
	
	else if ( aType == CCalEntry::EReminder )
		retValue.Set( KEntryReminder );
	
	else if ( aType == CCalEntry::EAnniv )
		retValue.Set( KEntryAnniv );
	
	else
		User::Leave(KErrArgument);
	
	return retValue;
	
	}

// ---------------------------------------------------------------------------
// Returns string literal for the given Entry Replication status
// ---------------------------------------------------------------------------
//
TPtrC CCalendarInterface::GetReplicationL( const CCalEntry::TReplicationStatus aType )
	{
	TPtrC retValue;
	
	if ( aType == CCalEntry::EPrivate )
		retValue.Set( KReplPrivate );
	
	else if ( aType == CCalEntry::ERestricted )
		retValue.Set( KReplRest );
	
	else
		retValue.Set( KReplOpen );
	
	return retValue;
	
	}
	
// ---------------------------------------------------------------------------
// Returns string literal for Change Types
// ---------------------------------------------------------------------------
//
TPtrC CCalendarInterface::GetChangeType( const MCalChangeCallBack2::TChangeType aType )
	{
	TPtrC retValue;
	
	if ( aType == MCalChangeCallBack2::EChangeAdd )
		retValue.Set( KChangeAdd );
	
	else if ( aType == MCalChangeCallBack2::EChangeDelete )
		retValue.Set( KChangeDelete );
	
	else if ( aType == MCalChangeCallBack2::EChangeModify )
		retValue.Set( KChangeModify );
	
	else
		retValue.Set( KChangeUndefined );
	
	return retValue;
	
	}
	
// ---------------------------------------------------------------------------
// Returns string literal for Entry Status
// ---------------------------------------------------------------------------
//
TPtrC CCalendarInterface::GetStatusL( const CCalEntry::TStatus aStatus )
	{
	TPtrC retValue;
	
	if ( aStatus == CCalEntry::ETentative )
		retValue.Set( KStatusTentative );
	
	else if ( aStatus == CCalEntry::EConfirmed )
		retValue.Set( KStatusConfirmed );
	
	else if ( aStatus == CCalEntry::ECancelled )
		retValue.Set( KStatusCancelled );
	
	else if ( aStatus == CCalEntry::ETodoNeedsAction )
		retValue.Set( KStatusTodoNeedsAction );
	
	else if ( aStatus == CCalEntry::ETodoCompleted )
		retValue.Set( KStatusTodoCompleted );
	
	else if ( aStatus == CCalEntry::ETodoInProcess )
		retValue.Set( KStatusTodoInProcess );
	
	else
		retValue.Set( KNullStatus );
	
	return retValue;
	}
	
// ---------------------------------------------------------------------------
// Returns string literal for Attendee Status
// ---------------------------------------------------------------------------
//
TPtrC CCalendarInterface::GetAttendeeStatusL( const CCalAttendee::TCalStatus aStatus )
	{
	TPtrC retValue;
	
	if ( aStatus == CCalAttendee::EAccepted )
		retValue.Set( KAttStatusAccepted );
	
	else if ( aStatus == CCalAttendee::ETentative )
		retValue.Set( KAttStatusTentative );
	
	else if ( aStatus == CCalAttendee::EConfirmed )
		retValue.Set( KAttStatusConfirmed );
	
	else if ( aStatus == CCalAttendee::EDeclined )
		retValue.Set( KAttStatusDeclined );
	
	else if ( aStatus == CCalAttendee::ECompleted )
		retValue.Set( KAttStatusCompleted );
	
	else if ( aStatus == CCalAttendee::EDelegated )
		retValue.Set( KAttStatusDelegated );
	
	else if ( aStatus == CCalAttendee::EInProcess )
		retValue.Set( KAttStatusInProcess );
	
	else
		retValue.Set( KAttStatusNeedsAction );
	
	return retValue;
	}

// ---------------------------------------------------------------------------
// Get string literal for Attendee Role
// ---------------------------------------------------------------------------
//
TPtrC CCalendarInterface::GetAttendeeRoleL( const CCalAttendee::TCalRole aRole )
	{
	TPtrC retValue;
	
	if ( aRole == CCalAttendee::EOptParticipant )
		retValue.Set( KAttRoleOptParticipant );
	
	else if ( aRole == CCalAttendee::ENonParticipant )
		retValue.Set( KAttRoleNonParticipant );
	
	else if ( aRole == CCalAttendee::EChair )
		retValue.Set( KAttRoleChair );
	
	else
		retValue.Set( KAttRoleReqParticipant );
	
	return retValue;
	}

// ---------------------------------------------------------------------------
// Return string literal for Entry Method
// ---------------------------------------------------------------------------
//
TPtrC CCalendarInterface::GetMethodL( const CCalEntry::TMethod aMethod )
	{
	TPtrC retValue;
	
	if ( aMethod == CCalEntry::EMethodPublish )
		retValue.Set( KMethodPublish );
	
	else if ( aMethod == CCalEntry::EMethodRequest)
		retValue.Set( KMethodRequest );
	
	else if ( aMethod == CCalEntry::EMethodReply)
		retValue.Set( KMethodReply );
	
	else if ( aMethod == CCalEntry::EMethodAdd )
		retValue.Set( KMethodAdd );
	
	else if ( aMethod == CCalEntry::EMethodCancel )
		retValue.Set( KMethodCancel );
	
	else if ( aMethod == CCalEntry::EMethodRefresh )
		retValue.Set( KMethodRefresh );
	
	else if ( aMethod == CCalEntry::EMethodCounter )
		retValue.Set( KMethodCounter );
	
	else if ( aMethod == CCalEntry::EMethodDeclineCounter )
		retValue.Set( KMethodDecCounter );
	
	else
		retValue.Set( KMethodNone );
	
	return retValue;
	}
	
// ---------------------------------------------------------------------------
// Return string literal for Entry Method
// ---------------------------------------------------------------------------
//
void CCalendarInterface::RemoveCalEntryListFromArray( CIterableCalEntryList* aCalEntryList )
	{
	TInt count = iArrayCalEntryList.Count();
	for(TInt index = 0; index < count; index++ )
		{
		if ( iArrayCalEntryList[index] == aCalEntryList )
			{
			iArrayCalEntryList.Remove( index );
			break;
			}
		}
		
	iArrayCalEntryList.Compress();
	}

// ---------------------------------------------------------------------------
// Return Entry Type for given LocalUid
// ---------------------------------------------------------------------------
//
TInt CCalendarInterface::GetEntryType( const TDesC& aCalendarName, TCalLocalUid aLocalUid )
	{
	TInt entryType = -1;
	RPointerArray<CCalEntry> entryArray;
	iCalService->GetListL( aCalendarName, aLocalUid, entryArray);
	if( entryArray.Count() )
		{
		entryType = entryArray[0]->EntryTypeL();
		}
	entryArray.ResetAndDestroy();
	return entryType;
	}
// ---------------------------------------------------------------------------
// Return Entry Type for given GlobalUid
// ---------------------------------------------------------------------------
//
TInt CCalendarInterface::GetEntryType( const TDesC& aCalendarName, const TDesC8& aGuid )
    {
    TInt entryType = -1;
    RPointerArray<CCalEntry> entryArray;
    iCalService->GetListL( aCalendarName, aGuid, entryArray);
    if( entryArray.Count() )
        {
        entryType = entryArray[0]->EntryTypeL();
        }
    entryArray.ResetAndDestroy();
    return entryType;
    }	
// ---------------------------------------------------------------------------
// Check if given calendar is in use by other resources
// ---------------------------------------------------------------------------
//
TBool CCalendarInterface::CheckCalendarInUse( const TDesC& aCalendarName )
	{
	TBool retValue = EFalse;
	TInt count = iArrayCalEntryList.Count();
	for(TInt index = 0; index < count; index++ )
		{
		if ( aCalendarName.CompareF( iArrayCalEntryList[index]->CalendarName() ) == 0 )
			{
			retValue = ETrue;
			break;
			}
		}
	return retValue;
	}
