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
* Description:  Implementation of class CMessagingAccessFolder
*
*/



#include <e32base.h>
#include <badesca.h>
#include <msvapi.h>
#include <msvuids.h>
#include <SendUiConsts.h>

#include "messageheader.h"
#include "accessfolder.h"

// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
//
CMessagingAccessFolder* CMessagingAccessFolder::NewL( CMsvSession& aServerSession )
	{
	CMessagingAccessFolder* self = new (ELeave) CMessagingAccessFolder( aServerSession );
	return self;
	}

// ---------------------------------------------------------------------------
// Destructor.
// ---------------------------------------------------------------------------
//
CMessagingAccessFolder::~CMessagingAccessFolder()
	{
	if ( iEntrySelection )
		{
		iEntrySelection->Reset();
		}
	if ( IsActive() )
	    {
	    iCallNotifyForCancelFlag = EFalse;
	    Cancel();
	    }
	
	iMtmArrayId.Reset();
	
	delete iEntrySelection;
	delete iFilter;
	delete iNotifyCallback;
	}

// ---------------------------------------------------------------------------
// Constructor.
// ---------------------------------------------------------------------------
//
CMessagingAccessFolder::CMessagingAccessFolder( CMsvSession& aServerSession ):
				iServerSession(aServerSession),
				CActive( EPriorityStandard ),
				iCallNotifyForCancelFlag(ETrue)
	{
	}

// ---------------------------------------------------------------------------
// Activates the asynchronous request
// ---------------------------------------------------------------------------
//
void CMessagingAccessFolder::ActivateRequest( TInt aReason )
    {
    iStatus = KRequestPending;
    SetActive();
    TRequestStatus* temp = &iStatus;
    User::RequestComplete( temp, aReason );
    }

// ---------------------------------------------------------------------------
// Inherited from CActive class 
// ---------------------------------------------------------------------------
//
void CMessagingAccessFolder::DoCancel()
    {
    NotifyRequestResult( KErrCancel,iEntrySelection, iFilter );
    }

// ---------------------------------------------------------------------------
// Inherited from CActive class 
// ---------------------------------------------------------------------------
//
void CMessagingAccessFolder::RunL()
    {
    TInt err = iStatus.Int();
    if ( err == KErrNone )
       {
       TInt groupingKey = KMsvNoGrouping;
       TMsvSelectionOrdering order( groupingKey, iFilter->SortType() );
       CMsvEntry* entry = iServerSession.GetEntryL( iFolderId );
       CleanupStack::PushL( entry );
       
       // Getlist can be performed on Folders entries only
       if ( entry->Entry().iType != KUidMsvFolderEntry )
           {
           User::Leave( KErrArgument );
           }
       
       entry->SetSortTypeL( order );
       
       InitializeMtmArray();
       
       if ( iEntrySelection )
           {
           iEntrySelection->Reset();
           delete iEntrySelection;
           iEntrySelection = NULL;
           }
       
       if ( iMtmArrayId.Count() == 1 )
           {
           iEntrySelection = entry->ChildrenWithMtmL( iMtmArrayId[0] );
           }
       else
           {
           iEntrySelection = entry->ChildrenL();
           }
       
       CleanupStack::PopAndDestroy( entry );
       NotifyRequestResult( KErrNone, iEntrySelection, iFilter);
       }
    else
        {
        NotifyRequestResult( err, iEntrySelection, iFilter);
        }
    }

// ---------------------------------------------------------------------------
// Sets message input parameters 
// aMessageParam/aNotifyCallback ownership is passed to this
// ---------------------------------------------------------------------------
//
void CMessagingAccessFolder::SetInputParamsL(CMsgCallbackBase* aNotifyCallback ,
                                              MAsyncRequestObserver* aAsyncRequestObserver )
    {
    
    iNotifyCallback = aNotifyCallback;
    iAsyncRequestObserver = aAsyncRequestObserver;
    }
	
void CMessagingAccessFolder::GetIdListL(TMsvId aFolderId ,
										CFilterParamInfo* aFilter,
									    CMsvEntrySelection*& aEntrySelection )
	{
	if ( !iFilter )
		iFilter = CFilterParamInfo::NewL();
	
	if( aFilter ) //added this check to do the copy only if aFilter is not NULL
		*iFilter = *aFilter;
	iFolderId = aFolderId;
	
	GetListL();
	
	aEntrySelection = iEntrySelection;
	iEntrySelection = NULL;
	}

void CMessagingAccessFolder::GetNextHeaderL( CFilterParamInfo* aFilter,
												CMsvEntrySelection* aEntrySelection,
												TInt& aIndex, 
									        	CMessageHeader*& aHeader )
	{
	if(!aEntrySelection || ( aEntrySelection->Count() <= aIndex ))
		return;
	
	if ( !iFilter )
		iFilter = CFilterParamInfo::NewL();
	
	if( aFilter ) //added this check to do the copy only if aFilter is not NULL
		*iFilter = *aFilter;
	
	GetNextFilteredHeaderL( aEntrySelection, aIndex, aHeader );
	
	}

// ---------------------------------------------------------------------------
// Gives the list of message headers ,sets the sorting order and 
// call function for filtering the message headers.
// ---------------------------------------------------------------------------
//
void CMessagingAccessFolder::GetListL()
	{
	if ( iNotifyCallback ) // making call as asynchronous
        {
        CActiveScheduler::Add( this );
        ActivateRequest( KErrNone );
        }
	else
	    {
        TInt groupingKey = KMsvNoGrouping;
        TMsvSelectionOrdering order( groupingKey, iFilter->SortType() );
        CMsvEntry* entry = iServerSession.GetEntryL( iFolderId );
        CleanupStack::PushL( entry );
        
        // Getlist can be performed on Folders entries only
        if ( entry->Entry().iType != KUidMsvFolderEntry )
            {
            User::Leave( KErrArgument );
            }
        
        entry->SetSortTypeL( order );
        
        InitializeMtmArray();
        
        if ( iEntrySelection )
            {
            iEntrySelection->Reset();
            delete iEntrySelection;
            iEntrySelection = NULL;
            }
        
        if ( iMtmArrayId.Count() == 1 )
            {
            iEntrySelection = entry->ChildrenWithMtmL( iMtmArrayId[0] );
            }
        else
            {
            iEntrySelection = entry->ChildrenL();
            }
        
        CleanupStack::PopAndDestroy( entry );
	    } 
	}

// ---------------------------------------------------------------------------
// Notifies callback the result for asynchronous request.
// ---------------------------------------------------------------------------
//
void CMessagingAccessFolder::NotifyRequestResult( TInt aReason,CMsvEntrySelection* aEntrySelection ,CFilterParamInfo* aFilter )
        
    {
    if ( iNotifyCallback )
        {
        iEntrySelection=NULL;
        iFilter=NULL;
        iAsyncRequestObserver->RequestComplete( iNotifyCallback->iTransactionId );
        
        if( iCallNotifyForCancelFlag )
           {
           TRAPD( err, iNotifyCallback->HandleGetlistL( aReason, aEntrySelection, aFilter ));   
           }
        
        }
    // caller will delete the object in case of cancel
    if ( aReason != KErrCancel )
        delete this;
    }

// ---------------------------------------------------------------------------
// Initializes the MtmID array by the Mtm string passed
// by user.
// ---------------------------------------------------------------------------
//
void CMessagingAccessFolder::InitializeMtmArray()
	{
	const CDesCArray* mtmArray = iFilter->Mtm();

	iMtmArrayId.Reset();
	
	if ( mtmArray )
		{
		for ( int i= 0; i< mtmArray->Count(); i++ )
			{
			if ( (*mtmArray)[i].CompareF( KMessageTypeSMS ) == KErrNone ) 
				{
					iMtmArrayId.Append( KSenduiMtmSmsUid );
				}
			else if ( (*mtmArray)[i].CompareF( KMessageTypeMMS ) == KErrNone )	
				{
					iMtmArrayId.Append( KSenduiMtmMmsUid );
				}
			}
		}
	}

// ---------------------------------------------------------------------------
// Fetches next header based on input parameters
// ---------------------------------------------------------------------------
//
void CMessagingAccessFolder::GetNextFilteredHeaderL( CMsvEntrySelection* aEntrySelection, 
														TInt& aIndex, 
														CMessageHeader*& aHeader )
	{
	TInt count = aEntrySelection->Count();
	
	InitializeMtmArray();
	
	for ( ;aIndex < count; )
		{
		TMsvId id = (*aEntrySelection)[aIndex];
		TMsvEntry tentry;
		TMsvId serviceId;
	    iServerSession.GetEntry( id, serviceId, tentry ); // Getting TMsvEntry
		
		aIndex++;
		
		if ( iFilter->Filter() & EFilterId )
			{
			if ( !FilterId( id ) )
		  		continue;
			}
		
		if ( iFilter->Filter() & EFilterMtm )
			{
		  	if ( !FilterMtm( tentry ) )
		  		continue;
			}
			
		if ( iFilter->Filter() & EFilterFrom )
			{
		  	if ( !FilterFrom( tentry ) )
		  		continue;
			}
			
		if ( iFilter->Filter() & EFilterSubject )	
			{
		  	if ( !FilterSubject( tentry ) )
		  		continue;
			}

		if ( iFilter->Filter() & EFilterStartDate || 
				iFilter->Filter() & EFilterEndDate )
			{
		  	if ( !FilterDate( tentry ) )
		  		continue;
			}
		
		CMessageHeader *   header = CMessageHeader::NewL();
		CleanupStack::PushL( header );
		header->SetMessageId( id );
		header->SetFromL( tentry.iDetails );
		header->SetMtmId( tentry.iMtm );
		header->SetAttachFlag( tentry.Attachment() );
		header->SetPriorityFlag( tentry.Priority() );
		header->SetUnreadFlag( tentry.Unread() );
		header->SetSubjectL( tentry.iDescription );
		header->SetTime( tentry.iDate ); 
		CleanupStack::Pop( header );
		aHeader = header;
		break;
		}
	}

// ---------------------------------------------------------------------------
// Filters out with message id
// ---------------------------------------------------------------------------
//
TBool CMessagingAccessFolder::FilterId(const TMsvId aMessageId) const
	{
	if ( aMessageId == iFilter->MessageId() )
		{
			return ETrue;
		}
	return EFalse;  
	}

// ---------------------------------------------------------------------------
// Filters out with mtm type
// ---------------------------------------------------------------------------
//
TBool CMessagingAccessFolder::FilterMtm( const TMsvEntry& aEntry) const
	{
	for ( int i= 0; i< iMtmArrayId.Count(); i++ )
		{
		if( iMtmArrayId[i] == aEntry.iMtm ) 
			{
				return ETrue;
			}	
		}
	return EFalse;
	}

// ---------------------------------------------------------------------------
// Filters out with sender address
// ---------------------------------------------------------------------------
//
TBool CMessagingAccessFolder::FilterFrom( const TMsvEntry& aEntry) const 
	{
	const CDesCArray* fromArray = iFilter->From();
	for ( int i= 0; i < fromArray->Count(); i++ )
		{
		if ( aEntry.iDetails.FindF( (*fromArray)[i] ) != KErrNotFound )
			{
			return ETrue ;
		 	}	
		}
	
	return EFalse ;		 	 	
	}

// ---------------------------------------------------------------------------
// Filters out with subject
// ---------------------------------------------------------------------------
//
TBool CMessagingAccessFolder::FilterSubject( const TMsvEntry& aEntry) const 
	{
	if ( aEntry.iDescription.FindF( iFilter->Subject() ) != KErrNotFound )
     	{
     	return ETrue ;
     	}	

	return EFalse;
	}

// ---------------------------------------------------------------------------
// Filters out with Date
// ---------------------------------------------------------------------------
//
TBool CMessagingAccessFolder::FilterDate( const TMsvEntry& aEntry) const
	{
	TDateTime startDateTime( iFilter->StartDate().DateTime().Year(), 
								iFilter->StartDate().DateTime().Month(),
								iFilter->StartDate().DateTime().Day(), 
								0, 0, 0, 0 );
	
	TDateTime endDateTime( iFilter->EndDate().DateTime().Year(), 
								iFilter->EndDate().DateTime().Month(),
								iFilter->EndDate().DateTime().Day(), 
								0, 0, 0, 0 );
								
	TDateTime checkDateTime( aEntry.iDate.DateTime().Year(), 
								aEntry.iDate.DateTime().Month(),
								aEntry.iDate.DateTime().Day(), 
								0, 0, 0, 0 );
	
	TTime startTime( startDateTime );
	TTime endTime( endDateTime );
	TTime checkTime( checkDateTime );
	
	if ( ( iFilter->Filter() & EFilterStartDate ) && 
			( iFilter->Filter() & EFilterEndDate ) )
		{
		if ( checkTime >= startTime && checkTime <= endTime )
			{
			return ETrue;
			}	
		}
	else if ( iFilter->Filter() & EFilterStartDate ) 
		{
		if( checkTime >= startTime )
			{
			return ETrue;
			}	
		}
	else if ( iFilter->Filter() & EFilterEndDate )
	    {
		if( checkTime <= endTime )
			{
			return ETrue;
			}	
	    }
	return EFalse;
	}


