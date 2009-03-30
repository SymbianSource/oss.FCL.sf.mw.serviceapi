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
* Description:  Implementation of class CCalendarHeader
*
*/


#include <calsession.h>
#include <calcommon.h>
#include <calentry.h>
#include <calentryview.h>
#include <calinstanceview.h>
#include <calprogresscallback.h>
#include <caleninterimutils2.h>


#include "calendarheader.h"
#include "calendarconstants.h"

/**
 * MCalProgressCallBack implementation.
 * Used for the creation of CCalEntryView and CCalInstanceView
*/
class CCalProgressCallBack : public CBase, public MCalProgressCallBack
	{
		/**
		 * Constructor
		*/ 
		CCalProgressCallBack(CActiveSchedulerWait* aWaitSchedular) : iWaitSchedular(aWaitSchedular)
			{
			}
			
	public:

		/**
		 * Two Phase Constructor
		*/ 
		static CCalProgressCallBack* NewL(CActiveSchedulerWait* aWaitSchedular)
			{
			return new (ELeave) CCalProgressCallBack( aWaitSchedular );
			}

		/**
		 * MCalProgressCallBack implementation
		*/ 
		void Progress(TInt /*aPercentageCompleted*/)
			{
			}
		
		/**
		 * MCalProgressCallBack implementation
		*/ 
		void Completed(TInt aError)
			{
			iError = aError;
			
			if ( iWaitSchedular && iWaitSchedular->IsStarted() )
				iWaitSchedular->AsyncStop();
			}
		
		/**
		 * MCalProgressCallBack implementation
		*/ 
		TBool NotifyProgress()
			{
			return EFalse;
			}
		
		/**
		 * Returns error code
		*/ 
		TInt Error()
			{
			return iError;
			}
			
	private:

		/**
		 * CActiveSchedulerWait
		*/ 
		CActiveSchedulerWait* iWaitSchedular;

		/**
		 * Error code
		*/ 
		TInt	iError;	
	};

// ---------------------------------------------------------------------------
// Two phase Constructor
// ---------------------------------------------------------------------------
//
CCalendarSessionInfo* CCalendarSessionInfo::NewL( const TDesC& aCalendar )
	{
	CCalendarSessionInfo* self = new (ELeave) CCalendarSessionInfo;
	CleanupStack::PushL( self );
	self->ConstructL( aCalendar );
	CleanupStack::Pop( self );
	return self;
	}
	
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
//
CCalendarSessionInfo::~CCalendarSessionInfo()
	{
	delete iCalName;
	delete iCalEntView;
	delete iCalInstView;
	delete iCalSession;
	}

// ---------------------------------------------------------------------------
// Returns calendar name
// ---------------------------------------------------------------------------
//
TPtrC CCalendarSessionInfo::Calendar()
	{
	return iCalName ? TPtrC(*iCalName) : TPtrC();
	}
	
// ---------------------------------------------------------------------------
// Returns calendar session
// ---------------------------------------------------------------------------
//
CCalSession* CCalendarSessionInfo::Session()
	{
	return iCalSession;
	}

// ---------------------------------------------------------------------------
// Returns calendar entry view
// ---------------------------------------------------------------------------
//
CCalEntryView* CCalendarSessionInfo::EntryView()
	{
	return iCalEntView;
	}

// ---------------------------------------------------------------------------
// Returns calendar instance view
// ---------------------------------------------------------------------------
//
CCalInstanceView* CCalendarSessionInfo::InstanceView()
	{
	return iCalInstView;
	}
	
// ---------------------------------------------------------------------------
// Constructor
// ---------------------------------------------------------------------------
//
CCalendarSessionInfo::CCalendarSessionInfo()
	{
	}

// ---------------------------------------------------------------------------
// Two Phase Constructor
// ---------------------------------------------------------------------------
//
void CCalendarSessionInfo::ConstructL( const TDesC& aCalendar )
	{
	iCalSession = CCalSession::NewL();
	
	// Opens the specified calendar file or the default calendar file 
	// if aCalendar is KNullDesC
	TRAPD(err, iCalSession->OpenL( aCalendar ));
	
	if ( err != KErrNone && 
			( aCalendar.Length() == 0 || 
				aCalendar.CompareF( iCalSession->DefaultFileNameL() ) == 0 ) )
		{
		// Create and open default calendar file
		iCalSession->CreateCalFileL( iCalSession->DefaultFileNameL() );
		iCalSession->OpenL( aCalendar );
		}
	else if ( err != KErrNone )	
		User::Leave( err );
	
	if ( aCalendar.Length() )
		iCalName = aCalendar.AllocL();
	else
		iCalName = iCalSession->DefaultFileNameL().AllocL();

	CActiveSchedulerWait* waitSchedular = new(ELeave) CActiveSchedulerWait;
	CleanupStack::PushL( waitSchedular );

	CCalProgressCallBack* instancecallback = CCalProgressCallBack::NewL( waitSchedular );
	CleanupStack::PushL( instancecallback );
 
    // Create an instance of view class for accessing instances of calendar entries
	iCalInstView = CCalInstanceView::NewL( *iCalSession, *instancecallback );
	waitSchedular->Start();
	
	User::LeaveIfError( instancecallback->Error() );
	CleanupStack::PopAndDestroy( instancecallback );
	instancecallback = NULL;
	
	instancecallback = CCalProgressCallBack::NewL( waitSchedular );
	CleanupStack::PushL( instancecallback );
	// Create an instance of view class for accessing calendar entries
	iCalEntView = CCalEntryView::NewL( *iCalSession, *instancecallback );
	waitSchedular->Start();
	
	User::LeaveIfError( instancecallback->Error() );

	CleanupStack::PopAndDestroy( 2, waitSchedular ); 
	}

// ---------------------------------------------------------------------------
// Two Phase Constructor
// ---------------------------------------------------------------------------
//
EXPORT_C CCalendarFilter* CCalendarFilter::NewL()
	{
	CCalendarFilter* self = new (ELeave) CCalendarFilter;
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
	}
	
// ---------------------------------------------------------------------------
// Desstructor
// ---------------------------------------------------------------------------
//
CCalendarFilter::~CCalendarFilter()
	{
	delete iTextToSearch;
	
	iLocalUidList.Reset();

	if ( iGuidList )
		{
		iGuidList->Reset();
		
		delete iGuidList;
		}
	}

// ---------------------------------------------------------------------------
// Constructor
// ---------------------------------------------------------------------------
//
CCalendarFilter::CCalendarFilter()
	{
	}

// ---------------------------------------------------------------------------
// Constructor
// ---------------------------------------------------------------------------
//
void CCalendarFilter::ConstructL()
	{
	// initialise start time to minimum calendar time 
	iStartTimeRange.SetTimeUtcL( TCalTime::MinTime() );
	// initialise end time to maximum calendar time
	iEndTimeRange.SetTimeUtcL( TCalTime::MaxTime() );
	iFilterType = CalCommon::EIncludeAll;
	}

// ---------------------------------------------------------------------------
// Set Start time
// ---------------------------------------------------------------------------
//
EXPORT_C void CCalendarFilter::SetStartTimeL( const TTime& aStartTime )
	{
	iFilterFlags ^= ( iFilterFlags & EFilterStTime );
	
	if ( aStartTime != Time::NullTTime() )
		{
		if( aStartTime < TCalTime::MinTime() || aStartTime > TCalTime::MaxTime() )
			User::Leave( KErrArgument );

		iStartTimeRange.SetTimeUtcL( aStartTime );
		iFilterFlags |= EFilterStTime;
		}
	}
	
// ---------------------------------------------------------------------------
// Set End time
// ---------------------------------------------------------------------------
//
EXPORT_C void CCalendarFilter::SetEndTimeL( const TTime& aEndTime )
	{
	iFilterFlags ^= ( iFilterFlags & EFilterEndTime );

	if ( aEndTime != Time::NullTTime() )
		{
		if( aEndTime < TCalTime::MinTime() || aEndTime > TCalTime::MaxTime() )
			User::Leave( KErrArgument );

		iEndTimeRange.SetTimeUtcL( aEndTime );
		iFilterFlags |= EFilterEndTime;
		}
	}
	
// ---------------------------------------------------------------------------
// Set Filter type
// ---------------------------------------------------------------------------
//
EXPORT_C void CCalendarFilter::SetFilterTypeL( const TDesC& aType)
	{
	if ( aType.CompareF(KEntryAppt) == 0 )
		iFilterType = CalCommon::EIncludeAppts;
	
	else if ( aType.CompareF(KEntryTodo) == 0 )
		iFilterType = CalCommon::EIncludeCompletedTodos|CalCommon::EIncludeIncompletedTodos;
	
	else if ( aType.CompareF(KEntryEvent) == 0 )
		iFilterType = CalCommon::EIncludeEvents;
	
	else if ( aType.CompareF(KEntryReminder) == 0 )
		iFilterType = CalCommon::EIncludeReminder;
	
	else if ( aType.CompareF(KEntryAnniv) == 0 )
		iFilterType = CalCommon::EIncludeAnnivs;
	
	else if ( aType.CompareF(KIncludeAll) == 0 )
		iFilterType = CalCommon::EIncludeAll;
	
	else
		User::Leave(KErrArgument);
	
	iFilterFlags |= EFilterType;
	}
	
// ---------------------------------------------------------------------------
// Set Filter text
// ---------------------------------------------------------------------------
//
EXPORT_C void CCalendarFilter::SetFilterTextL( const TDesC&	aTextToSearch )
	{
	iFilterFlags ^= ( iFilterFlags & EFilterText );
	
	if ( iTextToSearch )
		{
		delete iTextToSearch;
		iTextToSearch = NULL;
		}
	
	if( aTextToSearch.Length() )
		{
		iTextToSearch = aTextToSearch.AllocL();
		iFilterFlags |= EFilterText;
		}
	}
	
// ---------------------------------------------------------------------------
// Set DeleteAll option
// ---------------------------------------------------------------------------
//
EXPORT_C void CCalendarFilter::SetDeleteAll( TBool aDeleteAll )
	{
	if ( aDeleteAll )
		iFilterFlags |= EFlagDeleteAll;
	else
		iFilterFlags ^= ( iFilterFlags & EFlagDeleteAll );
	}
	
// ---------------------------------------------------------------------------
// Set IncludeUnDateToDo option
// ---------------------------------------------------------------------------
//
EXPORT_C void CCalendarFilter::SetIncludeUnDateToDo( TBool aInclude )
	{
	if ( aInclude )
		iFilterFlags |= EFlagUnDateToDo;
	else
		iFilterFlags ^= ( iFilterFlags & EFlagUnDateToDo );
	}
	
// ---------------------------------------------------------------------------
// Add Global Uid
// ---------------------------------------------------------------------------
//
EXPORT_C void CCalendarFilter::AddGuidL( const TDesC8& aGuid )
	{
	if ( !iGuidList )
		iGuidList = new(ELeave) CDesC8ArraySeg( KArrayGran );
	
	TInt pos;
	if( aGuid.Length() && iGuidList->Find( aGuid, pos ) != 0 )
		{
		iGuidList->AppendL( aGuid );
		iFilterFlags |= EFilterGUid;
		}
	}
	
// ---------------------------------------------------------------------------
// Add Local Uid
// ---------------------------------------------------------------------------
//
EXPORT_C void CCalendarFilter::AddLocalUid( const TCalLocalUid aLocalUid )
	{
	if( iLocalUidList.Find( aLocalUid) == KErrNotFound )
		{
		iLocalUidList.Append( aLocalUid );
		iFilterFlags |= EFilterLUid;
		}
	}
	
// ---------------------------------------------------------------------------
// Return Time Range
// ---------------------------------------------------------------------------
//
EXPORT_C CalCommon::TCalTimeRange CCalendarFilter::TimeRange() const
	{
	return CalCommon::TCalTimeRange( iStartTimeRange, iEndTimeRange );
	}
	
// ---------------------------------------------------------------------------
// Return Filter Entry Type
// ---------------------------------------------------------------------------
//
EXPORT_C TUint CCalendarFilter::FilterType() const
	{
	return iFilterType;
	}
	
// ---------------------------------------------------------------------------
// Return Filter Text
// ---------------------------------------------------------------------------
//
EXPORT_C TPtrC CCalendarFilter::FilterText() const
	{
	return iTextToSearch ? TPtrC( *iTextToSearch ) : TPtrC();
	}

// ---------------------------------------------------------------------------
// Return Global Uid List
// ---------------------------------------------------------------------------
//
EXPORT_C const CDesC8Array* CCalendarFilter::GuidList() const
	{
	return iGuidList;
	}
	
// ---------------------------------------------------------------------------
// Return Local Uid List
// ---------------------------------------------------------------------------
//
EXPORT_C const RArray<TCalLocalUid>& CCalendarFilter::LocalUidList() const
	{
	return iLocalUidList;
	}

// ---------------------------------------------------------------------------
// Return Filter options selected
// ---------------------------------------------------------------------------
//
EXPORT_C TInt32 CCalendarFilter::Filter() const
	{
	return iFilterFlags;
	}

CCalendarFilter& CCalendarFilter::operator=( const CCalendarFilter& aFilter )
	{
	iStartTimeRange = aFilter.iStartTimeRange;
	iEndTimeRange = aFilter.iEndTimeRange;
	iFilterType = aFilter.iFilterType;
	iFilterFlags = aFilter.iFilterFlags;
	
	delete iTextToSearch;
	iTextToSearch = NULL;
	
	if ( aFilter.iTextToSearch )
		{
		iTextToSearch = aFilter.iTextToSearch->AllocL();
		}
	
	if ( iGuidList )
		{
		iGuidList->Reset();
		}
	
	if ( aFilter.iGuidList )
		{
		TInt count = aFilter.iGuidList->Count();
		for( TInt index = 0; index < count; index++ )
			{
			AddGuidL((*(aFilter.iGuidList))[index]);
			}
		}
	
	iLocalUidList.Reset();
	
	TInt count = aFilter.iLocalUidList.Count();
	for( TInt index = 0; index < count; index++ )
		{
		AddLocalUid((aFilter.iLocalUidList)[index]);
		}

	return *this;
	}


// ---------------------------------------------------------------------------
// Two Phase Constructor of CCalendarExportParams
// ---------------------------------------------------------------------------
//
EXPORT_C CCalendarExportParams* CCalendarExportParams::NewL()
	{
	return new (ELeave) CCalendarExportParams;
	}
	
// ---------------------------------------------------------------------------
// Desstructor of CCalendarExportParams
// ---------------------------------------------------------------------------
//
CCalendarExportParams::~CCalendarExportParams()
	{	
	iInputLocalUIDArray.Reset();

	if ( iInputGUIDArray )
		{
		iInputGUIDArray->Reset();
		
		delete iInputGUIDArray;
		}
		
	delete iFileName;	
	}

// ---------------------------------------------------------------------------
// Constructor
// ---------------------------------------------------------------------------
//
CCalendarExportParams::CCalendarExportParams()
	{
	}


// ---------------------------------------------------------------------------
// Add Global Uid, add one guid per time
// ---------------------------------------------------------------------------
//
EXPORT_C void CCalendarExportParams::AddGuidL( const TDesC8& aGuid )
	{
	if ( !iInputGUIDArray )
		{
		iInputGUIDArray = new(ELeave) CDesC8ArraySeg( KArrayGran );
		}
		
	TInt pos;
	if( aGuid.Length() && iInputGUIDArray->Find( aGuid, pos ) != 0 )
		{
		iInputGUIDArray->AppendL( aGuid );
		iParamsFlags |= EParamsGUid;
		}
	}
	
// ---------------------------------------------------------------------------
// Add Global Uid, add an entire GUid array
// NOTE: Takes the ownership of aInputGUID Array 
// ---------------------------------------------------------------------------
//
EXPORT_C void CCalendarExportParams::AddGuidL( const CDesC8Array* aInputGUIDArray )
	{
	if( !aInputGUIDArray )
		return;
	// append to array the new array elements and delete the input array
	TInt inputArrayCount = aInputGUIDArray->Count();
	
	if ( !iInputGUIDArray )
		{
		iInputGUIDArray = new(ELeave) CDesC8ArraySeg( KArrayGran );
		}

	for( TInt index = 0; index < inputArrayCount; ++index )
		{
		TInt pos = 0;
		if( (*aInputGUIDArray)[index].Length() && 
					iInputGUIDArray->Find( (*aInputGUIDArray)[index], pos ) != 0 )
			iInputGUIDArray->AppendL( (*aInputGUIDArray)[index] );	
		}	
	
	iParamsFlags |= EParamsGUid;
	}
		
// ---------------------------------------------------------------------------
// Add Local Uid, add one localuid per time
// ---------------------------------------------------------------------------
//
EXPORT_C void CCalendarExportParams::AddLocalUid( const TCalLocalUid aLocalUid )
	{
	if( iInputLocalUIDArray.Find( aLocalUid) == KErrNotFound )
		{
		iInputLocalUIDArray.Append( aLocalUid );
		iParamsFlags |= EParamsLUid;
		}
	}
	
// ---------------------------------------------------------------------------
// Add Local Uid, add the entire array
// ---------------------------------------------------------------------------
//
EXPORT_C void CCalendarExportParams::AddLocalUid( const RArray<TCalLocalUid>& aInputLocalUIDArray )
	{
	TInt inputArrayCount = aInputLocalUIDArray.Count();
	
	for (TInt index = 0; index < inputArrayCount; ++index )
		{
		if( iInputLocalUIDArray.Find( aInputLocalUIDArray[index]) == KErrNotFound )
			{
			iInputLocalUIDArray.Append( aInputLocalUIDArray[index] );
			iParamsFlags |= EParamsLUid;
			}
		}
	}


// ---------------------------------------------------------------------------
// SetCallBack
// ---------------------------------------------------------------------------
//
EXPORT_C void CCalendarExportParams::SetExportFileNameL( const TDesC& aExportFileName )
	{
	iParamsFlags ^= ( iParamsFlags & EParamsFileName );
	
	if ( iFileName )
		{
		delete iFileName;
		iFileName = NULL;
		}
	
	if( aExportFileName.Length() )
		{
		iFileName = aExportFileName.AllocL();
		iParamsFlags |= EParamsFileName;
		}
	else
		User::Leave(KErrArgument);
	}
	
		
// ---------------------------------------------------------------------------
// Return Global Uid Array
// ---------------------------------------------------------------------------
//
EXPORT_C const CDesC8Array* CCalendarExportParams::GuidArray() const
	{
	return iInputGUIDArray;
	}
	
// ---------------------------------------------------------------------------
// Return Local Uid Array
// ---------------------------------------------------------------------------
//
EXPORT_C const RArray<TCalLocalUid>& CCalendarExportParams::LocalUidArray() const
	{
	return iInputLocalUIDArray;
	}

// ---------------------------------------------------------------------------
// Return RequestObserver
// ---------------------------------------------------------------------------
//
EXPORT_C TPtrC CCalendarExportParams::ExportFileName()
	{
	return iFileName ? TPtrC(*iFileName) : TPtrC();
	}

// ---------------------------------------------------------------------------
// Return Params options selected
// ---------------------------------------------------------------------------
//
EXPORT_C TInt32 CCalendarExportParams::Params() const
	{
	return iParamsFlags;
	}

// ---------------------------------------------------------------------------
// Return CCalendarExportParams* exact copy of this object
// ---------------------------------------------------------------------------
//		
EXPORT_C CCalendarExportParams* CCalendarExportParams::CloneL()
	{
	CCalendarExportParams* cloneObject = CCalendarExportParams::NewL();
	
	CleanupStack::PushL( cloneObject );
	
	if(iParamsFlags & EParamsGUid)
		{
		cloneObject->AddGuidL( this->GuidArray() );
		}
	
	if(iParamsFlags & EParamsLUid)
		{
		cloneObject->AddLocalUid( this->LocalUidArray() );
		}
		
	if(iParamsFlags & EParamsFileName)
		{
		cloneObject->SetExportFileNameL( this->ExportFileName() );
		}
	
	CleanupStack::Pop( cloneObject );

	return cloneObject;
	}
