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

//System Includes
#include <e32cmn.h> 			//for RPointerArray
#include <calsession.h>			//For CCalSession
#include <calentryview.h>
#include <CalenInterimUtils2.h>
#include <s32mem.h>
#include <s32file.h>
#include <e32base.h>
#include <calinstanceview.h>
#include <calinstance.h>
#include <calentry.h>
//User Include
#include "calendarheader.h"
#include "calendarconstants.h"
#include "asyncreqobserver.h"
#include "calendargetlist.h"
#include "calendarheader.h"

void CleanupCCalEntryArray(TAny* aPointer);
void CleanupCCalInstanceArray(TAny* aPointer);

// --------------------------------------------------------------------------------------------------------
// Static Method which either returns the Two Phase constructed Object or Leave 
// NOTE: Ownership of any of the parameters is not taken through this function call
// NOTE: Therefore the User of this function needs to take care of neccessary cleanup of passed parameters
// --------------------------------------------------------------------------------------------------------
//
CCalendarGetList* CCalendarGetList::NewL ( CCalendarSessionInfo* aCalSessionInfo, 
                                            const TDesC8& aGuid, 
											CAsyncRequestObserver* aAsyncRequestObserver,
											MCalCallbackBase* aCallBack )
	{
	CCalendarGetList* self = new (ELeave) CCalendarGetList( aCalSessionInfo, aAsyncRequestObserver, aCallBack );
	
    CleanupStack::PushL(self);
    
    self->ConstructL( aGuid );
    
    CleanupStack::Pop(self); 
    
    return self;
	}	
// --------------------------------------------------------------------------------------------------------
// Static Method which either returns the Two Phase constructed Object or Leave 
// NOTE: Ownership of any of the parameters is not taken through this function call
// NOTE: Therefore the User of this function needs to take care of neccessary cleanup of passed parameters
// --------------------------------------------------------------------------------------------------------
//
CCalendarGetList* CCalendarGetList::NewL ( CCalendarSessionInfo* aCalSessionInfo, 
                                            const TCalLocalUid aLocalUid, 
                                            CAsyncRequestObserver* aAsyncRequestObserver,
                                            MCalCallbackBase* aCallBack )
    {
    CCalendarGetList* self = new (ELeave) CCalendarGetList( aCalSessionInfo, aAsyncRequestObserver, aCallBack );
    
    CleanupStack::PushL(self);
    
    self->ConstructL( aLocalUid );
    
    CleanupStack::Pop(self); 
    
    return self;
    }   
// --------------------------------------------------------------------------------------------------------
// Static Method which either returns the Two Phase constructed Object or Leave 
// NOTE: Ownership of any of the parameters is not taken through this function call
// NOTE: Therefore the User of this function needs to take care of neccessary cleanup of passed parameters
// --------------------------------------------------------------------------------------------------------
//
CCalendarGetList* CCalendarGetList::NewL ( CCalendarSessionInfo* aCalSessionInfo, 
                                            CCalendarFilter* aFilter,  
											CAsyncRequestObserver* aAsyncRequestObserver,
											MCalCallbackBase* aCallBack )
	{
	CCalendarGetList* self = new (ELeave) CCalendarGetList( aCalSessionInfo, aAsyncRequestObserver, aCallBack );
	
    CleanupStack::PushL(self);
    // Construct filter object which determines the type of get 
    self->ConstructL( aFilter );
    
    CleanupStack::Pop(self); 
    
    return self;
	}	

	
// --------------------------------------------------------------------------------------------------------
// Destructor.
// --------------------------------------------------------------------------------------------------------
//
CCalendarGetList::~CCalendarGetList()
	{
	Cancel();	
	
	delete iFilter;
	
	delete iGuid;
	
    iEntryList.Reset();
    iInstanceList.Reset();
	}
	
	
// --------------------------------------------------------------------------------------------------------
// Constructor.
// --------------------------------------------------------------------------------------------------------
//
CCalendarGetList::CCalendarGetList( CCalendarSessionInfo* aCalSessionInfo, 
									CAsyncRequestObserver* aAsyncRequestObserver,
									MCalCallbackBase* aCallBack ): 
															//CActive( EPriorityStandard ),
														  	iSessionInfo (aCalSessionInfo ),
														  	iCallBack( aCallBack ),
														  	iAsyncRequestObserver(aAsyncRequestObserver)
	{

	}
	
	
// --------------------------------------------------------------------------------------------------------
// 2nd-phased constructor of two phase construction
// --------------------------------------------------------------------------------------------------------
//
void CCalendarGetList::ConstructL( const TDesC8& aGuid )
	{	
   if(aGuid.Length())
       {
       iGuid = aGuid.AllocL();// = aGuid ; 
       iGetListOption = EGetListGUid;
       }
	}

void CCalendarGetList::ConstructL( const TCalLocalUid aLocalUid )
    {   
   
    iLocalUid = aLocalUid;    
    iGetListOption = EGetListLocalUid;
    }
// --------------------------------------------------------------------------------------------------------
// GetList implementation
// --------------------------------------------------------------------------------------------------------
//
void CCalendarGetList::ConstructL( CCalendarFilter* aFilter )
    {   
   
    iFilter = CCalendarFilter::NewL();
    *iFilter = *aFilter;   
    iGetListOption = EGetListTimeRange;
    
    }

void CCalendarGetList::GetListL( const TDesC8& aGuid, RPointerArray<CCalEntry>& aEntryList )
    {
        iSessionInfo ->EntryView()->FetchL( aGuid, aEntryList );
    }

void CCalendarGetList::GetListL(const TCalLocalUid aLocalUid, RPointerArray<CCalEntry>& aEntryList )
    {
  CCalEntry* entry = iSessionInfo ->EntryView()->FetchL( aLocalUid );
                if( entry )
                        {
                        aEntryList.Append( entry );
                        }
    }

void CCalendarGetList::GetListL( RPointerArray<CCalInstance>& aInstanceList )
    {
 //   iInstanceList = aInstanceList;
    CalCommon::TCalTimeRange range =  iFilter->TimeRange();
    if( (range.EndTime().TimeLocalL()) < (range.StartTime().TimeLocalL()) )
        User::Leave( KErrArgument );
    if ( iFilter->FilterText().Length() )
        {
        // Search and return all instances which match filter text and time range
        CCalInstanceView::TCalSearchParams searchParam( iFilter->FilterText(), CalCommon::EFoldedTextSearch );
        iSessionInfo ->InstanceView()->FindInstanceL( aInstanceList, 
                                                    iFilter->FilterType(), 
                                                    iFilter->TimeRange(), searchParam ) ;
        }
    else
        {
        // Search and return all instances which match filter type and time range
        iSessionInfo ->InstanceView()->FindInstanceL( aInstanceList, 
                                                    iFilter->FilterType(), 
                                                    iFilter->TimeRange() ) ;
        }   
    }

void CCalendarGetList::GetListL()
    {
    if( iCallBack )    // making call as asynchronous
        {
        if(!iAsyncRequestObserver ) 
        User::Leave( KErrArgument );
    
        CActiveScheduler::Add ( this );
    
        ActivateRequest( KErrNone );
        }
    }
// --------------------------------------------------------------------------------------------------------
// Notifies callback the result for asynchronous request.
// --------------------------------------------------------------------------------------------------------
//
void CCalendarGetList::NotifyRequestResult( TInt aReason )
    {

    if ( iCallBack )
        {
        iAsyncRequestObserver->RequestComplete( iCallBack->iTransactionId );
        
         if( iGetListOption == EGetListGUid )
            {
            TRAPD( err, iCallBack->NotifyResultL( aReason, ( TAny * )( & iEntryList )));    
            }
        else if( iGetListOption == EGetListLocalUid )
            {
            TRAPD( err, iCallBack->NotifyResultL( aReason, ( TAny * )( & iEntryList )));    
            }
        else
            {
            TRAPD( err, iCallBack->NotifyResultL( aReason, ( TAny * )( & iInstanceList ))); 
            }
        }
    if ( aReason != KErrCancel )
        delete this; 
    }
// ---------------------------------------------------------------------------
// Inherited from CActive class 
// ---------------------------------------------------------------------------
//
void CCalendarGetList::DoCancel()
	{
	
	NotifyRequestResult( KErrCancel );
	}

// ---------------------------------------------------------------------------
// Inherited from CActive class 
// ---------------------------------------------------------------------------
//
void CCalendarGetList::RunL()
	{
	TInt err = iStatus.Int();

	if ( err == KErrNone )
		{
        // Performs the actual delete depending on the parameters set
        TRAP(err, StartFetchingL());
		}
		
	NotifyRequestResult( err );		
	}

// --------------------------------------------------------------------------------------------------------
// retrieves asynchronous request transactionid.
// --------------------------------------------------------------------------------------------------------
//
/*TInt32 CCalendarGetList::GetTransactionID()
    {
    return(iCallBack->GetTransactionID());
    }*/


// ---------------------------------------------------------------------------
// retrieves Instances based on Time Range
// ---------------------------------------------------------------------------
//
void CCalendarGetList::GetTimeRangeL()
    {

     CalCommon::TCalTimeRange range =  iFilter->TimeRange();
     if( (range.EndTime().TimeLocalL()) < (range.StartTime().TimeLocalL()) )
         User::Leave( KErrArgument );
     if ( iFilter->FilterText().Length() )
         {
         // Search and return all instances which match filter text and time range
         CCalInstanceView::TCalSearchParams searchParam( iFilter->FilterText(), CalCommon::EFoldedTextSearch );
         iSessionInfo ->InstanceView()->FindInstanceL( iInstanceList, 
                                                     iFilter->FilterType(), 
                                                     iFilter->TimeRange(), searchParam ) ;
         }
     else
         {
         // Search and return all instances which match filter type and time range
         iSessionInfo ->InstanceView()->FindInstanceL( iInstanceList, 
                                                     iFilter->FilterType(), 
                                                     iFilter->TimeRange() ) ;
         }   
    }

// ---------------------------------------------------------------------------
// retrives Entries based in GlobalUid
// ---------------------------------------------------------------------------
//
void CCalendarGetList::GetGUidL()
    {
    TPtrC8 guid(iGuid->Des());
    
    iSessionInfo ->EntryView()->FetchL( guid, iEntryList );
    }

// ---------------------------------------------------------------------------
// retrives Entries based in LocalUid
// ---------------------------------------------------------------------------
//
void CCalendarGetList::GetLocalUidL()
    {

   CCalEntry* entry = iSessionInfo ->EntryView()->FetchL( iLocalUid/*(*iFilter->LocalUidList())[0], iEntryList*/ );
    if( entry )
            {
            iEntryList.Append( entry );
            }
    }

// ---------------------------------------------------------------------------
// Call the appropriate getlist based in getlist option
// ---------------------------------------------------------------------------
//
void CCalendarGetList::StartFetchingL()
    {
    switch ( iGetListOption )
        {
        case EGetListGUid: // get guid - entries
            GetGUidL();
            break;
        
        case EGetListLocalUid: // get localid - entries
            GetLocalUidL();
             break;
                    
        case EGetListTimeRange: // get time range - instances
            GetTimeRangeL();
            break;
            
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// Initialises getlist option
// ---------------------------------------------------------------------------
//
void CCalendarGetList::InitializeGetListOption()
    {
    //Filter having only GUids
    if ( iFilter->Filter() == EFilterGUid )
        {
        iGetListOption = EGetListGUid;
        }
    //Filter having only GUids
   else if ( iFilter->Filter() == EFilterLUid )
        {
        iGetListOption = EGetListLocalUid;
        }
 
    //Filter having time range only (No GUid/LocalUid)
    else
        {
        iGetListOption = EGetListTimeRange;
        }
    }
// ---------------------------------------------------------------------------
// Activates the asynchronous request
// ---------------------------------------------------------------------------
//
void CCalendarGetList::ActivateRequest( TInt aReason )
	{

	SetActive();
	
	iStatus = KRequestPending;
	    
	TRequestStatus* temp = &iStatus;
	
	User::RequestComplete( temp, aReason );
	
	}



