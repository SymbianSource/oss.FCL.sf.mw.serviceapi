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
* Description:  Implementation of class CMessageHeader
*
*/


#include <CMsvAttachment.h>
#include <senduiconsts.h>

#include "messageheader.h"


// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
EXPORT_C CMessageHeader* CMessageHeader::NewL()
	{
	CMessageHeader* self = new(ELeave) CMessageHeader();
	return self;
	}
	
// ---------------------------------------------------------------------------
// Destructor
// ---------------------------------------------------------------------------
CMessageHeader::~CMessageHeader()
	{
	delete iSubject;
	delete iFrom;
	delete iMtmAsString;
	delete iPriAsString;
	}
	
// --------------------------------------------------------------------------- 
//  C++  constructor.
// ---------------------------------------------------------------------------
CMessageHeader::CMessageHeader():
		iMtm(TUid(TUid::Null())),
		iMessageID(-1)
	{
	}

// --------------------------------------------------------------------------- 
// Sets the unread flag
// ---------------------------------------------------------------------------
EXPORT_C void CMessageHeader::SetUnreadFlag(const TBool aUnread)
	{
	iUnread = aUnread;
	}

// --------------------------------------------------------------------------- 
// Gets the unread flag
// ---------------------------------------------------------------------------
EXPORT_C void CMessageHeader::GetUnreadFlag(TBool& aUnread) const
	{
	aUnread = iUnread;
	}

// --------------------------------------------------------------------------- 
// Gets the unread flag
// ---------------------------------------------------------------------------
EXPORT_C TBool CMessageHeader::UnreadFlag() const
	{
	return ( iUnread ? ETrue : EFalse ); 
	}

// --------------------------------------------------------------------------- 
// Sets the attachment flag
// ---------------------------------------------------------------------------
EXPORT_C void CMessageHeader::SetAttachFlag(const TBool aAttachment)
	{
	iAttachment = aAttachment;
	}

// --------------------------------------------------------------------------- 
// Gets the attachment flag
// ---------------------------------------------------------------------------
EXPORT_C void CMessageHeader::GetAttachFlag(TBool& aAttachment) const
	{
	aAttachment = iAttachment ; 
	}

// --------------------------------------------------------------------------- 
// Gets the attachment flag
// ---------------------------------------------------------------------------
EXPORT_C TBool CMessageHeader::AttachFlag() const
	{
	return ( iAttachment ? ETrue : EFalse ); 
	}

// --------------------------------------------------------------------------- 
// Sets the priority flag
// ---------------------------------------------------------------------------
EXPORT_C void CMessageHeader::SetPriorityFlag(const TMsvPriority aPriority)
	{
	iPriority = aPriority;
	delete iPriAsString;
	iPriAsString = NULL;
	
	switch ( iPriority )
		{
		case EMsvHighPriority: 
			iPriAsString = KPriorityHigh.operator()().Alloc();
			break;
			
		case EMsvLowPriority: 
			iPriAsString = KPriorityLow.operator()().Alloc();
			break;
			
		case EMsvMediumPriority:
		default:
			iPriAsString = KPriorityMedium.operator()().Alloc();
		}
	}

// --------------------------------------------------------------------------- 
// Gets the priority flag
// ---------------------------------------------------------------------------
EXPORT_C void CMessageHeader::GetPriorityFlag(TMsvPriority& aPriority) const
	{
	aPriority = iPriority;
	}

// --------------------------------------------------------------------------- 
// Gets the priority 
// ---------------------------------------------------------------------------
EXPORT_C TPtrC CMessageHeader::Priority() const
	{
    return iPriAsString ? TPtrC( *iPriAsString ) : TPtrC(); 
	}

// --------------------------------------------------------------------------- 
// Sets the mtm id
// ---------------------------------------------------------------------------
EXPORT_C void CMessageHeader::SetMtmId(const TUid aMtm)
	{
	iMtm = aMtm;
	
	if ( iMtmAsString )
		delete iMtmAsString;
	
	iMtmAsString = NULL;
	
	if ( iMtm == KSenduiMtmSmsUid )
		{
		iMtmAsString = KMessageTypeSMS.operator()().Alloc();
		}
	else if ( iMtm == KSenduiMtmMmsUid )
		{
		iMtmAsString = KMessageTypeMMS.operator()().Alloc();
		}
	else
		{
		iMtmAsString = KUnknown.operator()().Alloc();
		}
	}

// --------------------------------------------------------------------------- 
// Gets the mtm id
// ---------------------------------------------------------------------------
EXPORT_C void CMessageHeader::GetMtmId(TUid& aMtm) const
	{
	aMtm = iMtm;	
	}

// --------------------------------------------------------------------------- 
// Gets the mtm 
// ---------------------------------------------------------------------------
EXPORT_C TPtrC CMessageHeader::Mtm() const
	{
    return iMtmAsString ? TPtrC( *iMtmAsString ) : TPtrC(); 
	}

// --------------------------------------------------------------------------- 
// Sets the messge id
// ---------------------------------------------------------------------------
EXPORT_C void CMessageHeader::SetMessageId(const TMsvId aMessageID)
	{
	iMessageID = aMessageID;
	}

// --------------------------------------------------------------------------- 
// Gets the messge id
// ---------------------------------------------------------------------------
EXPORT_C void CMessageHeader::GetMessageId(TMsvId& aMessageID) const
	{
	aMessageID = iMessageID;	
	}

// --------------------------------------------------------------------------- 
// returns the messge id
// ---------------------------------------------------------------------------
EXPORT_C TMsvId CMessageHeader::MessageId() const
	{
	return iMessageID;	
	}

// --------------------------------------------------------------------------- 
// Sets the time
// ---------------------------------------------------------------------------
EXPORT_C void CMessageHeader::SetTime(const TTime& aTime)
	{
	TDateTime tmp;
	tmp = aTime.DateTime();
	iTime = tmp;
	}

// --------------------------------------------------------------------------- 
// Gets the time
// ---------------------------------------------------------------------------
EXPORT_C void CMessageHeader::GetTime(TTime& aTime) const
	{
	TDateTime tmp;
	tmp = iTime.DateTime();
	aTime = tmp;
	}

// --------------------------------------------------------------------------- 
// Gets the time
// ---------------------------------------------------------------------------
EXPORT_C const TTime& CMessageHeader::Time() const
	{
	return iTime;
	}

// --------------------------------------------------------------------------- 
// Sets the sender address
// ---------------------------------------------------------------------------
EXPORT_C void CMessageHeader::SetFromL(const TDesC& aFrom)
	{
	if( iFrom )
		{
		delete iFrom;
		iFrom = NULL;	
		}
	iFrom = aFrom.AllocL();	
	}

// --------------------------------------------------------------------------- 
// Gets the sender address
// ---------------------------------------------------------------------------
EXPORT_C const TPtrC CMessageHeader::From() const
	{
    return iFrom ? TPtrC( *iFrom ) : TPtrC(); 
	}

// --------------------------------------------------------------------------- 
// Sets the subject
// ---------------------------------------------------------------------------
EXPORT_C void CMessageHeader::SetSubjectL(const TDesC& aSubject)
	{
	if( iSubject )
		{
		delete iSubject;
		iSubject = NULL;	
		}
	iSubject = aSubject.AllocL();	
	}

// --------------------------------------------------------------------------- 
// Gets the subject
// ---------------------------------------------------------------------------
EXPORT_C const TPtrC CMessageHeader::Subject() const
	{
    return iSubject ? TPtrC( *iSubject ) : TPtrC(); 
	}


// ---------------------------------------------------------------------------
// Two-phased constructor.
// ---------------------------------------------------------------------------
EXPORT_C CRecipientList* CRecipientList::CRecipientList::NewL()
	{
	CRecipientList* self = new (ELeave) CRecipientList;
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
	}

// ---------------------------------------------------------------------------
// Destructor.
// ---------------------------------------------------------------------------
CRecipientList::~CRecipientList()
	{
	if ( iRecipients )
		iRecipients->Reset();
	
	delete iRecipients;
	iRecipientType.Close();
	}

// ---------------------------------------------------------------------------
// Constructor
// ---------------------------------------------------------------------------
CRecipientList::CRecipientList()
	{
	}

// ---------------------------------------------------------------------------
// SYmbian Constructor
// ---------------------------------------------------------------------------
void CRecipientList::ConstructL()
	{
	iRecipients = new (ELeave) CDesCArrayFlat(KArrayGranularity);	
	}

// --------------------------------------------------------------------------- 
// Appends the recipient type 
// ---------------------------------------------------------------------------
EXPORT_C void CRecipientList::AppendL(TMsvRecipientType aValue, const TDesC& aPtr)
	{
	iRecipientType.AppendL(aValue);
	TRAPD(err, iRecipients->AppendL(aPtr));
	if (err != KErrNone)
		{
		iRecipientType.Remove(iRecipientType.Count() - 1);
		User::Leave(err);
		}
	}

// --------------------------------------------------------------------------- 
// Gives the number of recipients
// ---------------------------------------------------------------------------
EXPORT_C TInt CRecipientList::Count() const
	{
	return iRecipients->Count();
	}

// --------------------------------------------------------------------------- 
// Gives the recipient type
// ---------------------------------------------------------------------------
EXPORT_C TMsvRecipientType CRecipientList::Type(TInt aPos) const
	{
	return iRecipientType[aPos];
	}

// --------------------------------------------------------------------------- 
// Gives recipient address
// ---------------------------------------------------------------------------
EXPORT_C const TDesC& CRecipientList::operator[](TInt aIndex) const
	{
	HBufC16* temp=(*(HBufC16**)iRecipients->At(aIndex));
	return *temp;
	}
	
// --------------------------------------------------------------------------- 
// Resets the recipient list
// ---------------------------------------------------------------------------
EXPORT_C void CRecipientList::Reset()
	{
	iRecipients->Reset();
	iRecipientType.Reset();
	}
	

// --------------------------------------------------------------------------- 
// Two Phase Constructor
// ---------------------------------------------------------------------------
EXPORT_C CFilterParamInfo* CFilterParamInfo::NewL()
	{
	return new(ELeave) CFilterParamInfo;
	}
	
// --------------------------------------------------------------------------- 
// Destructor
// ---------------------------------------------------------------------------
CFilterParamInfo::~CFilterParamInfo()
	{
	Reset();
	}

// --------------------------------------------------------------------------- 
// Constructor
// ---------------------------------------------------------------------------
CFilterParamInfo::CFilterParamInfo()
	{
	
	}
		
// --------------------------------------------------------------------------- 
// Sets the sender address as a filter
// ---------------------------------------------------------------------------
EXPORT_C void CFilterParamInfo::AddFromL( const TDesC& aFrom )
	{
	if( !iFromArray )
		{
		iFromArray = new (ELeave) CDesCArraySeg( KArrayGranularity );
		}
		
	if ( aFrom.Length() )
		{
		iFromArray->AppendL( aFrom );	
		iFilter |= EFilterFrom;
		}
	}

// --------------------------------------------------------------------------- 
// Gets the sender address as a filter
// ---------------------------------------------------------------------------
EXPORT_C const CDesCArray* CFilterParamInfo::From() const 
	{
	return iFromArray;
	}


// --------------------------------------------------------------------------- 
// Sets the mtm as a filter
// ---------------------------------------------------------------------------
EXPORT_C TInt CFilterParamInfo::AddMtmL( const TDesC& aMtm )
	{
	if ( aMtm.CompareF( KMessageTypeSMS ) == 0 || aMtm.CompareF( KMessageTypeMMS ) == 0 )
		{
		}
	else
		{
		return KErrNotSupported;
		}
		
	if( !iMtmArray )
		{
		iMtmArray = new (ELeave) CDesCArraySeg( KArrayGranularity );
		}
		
	if ( aMtm.Length() )
		{
		iMtmArray->AppendL( aMtm );	
		iFilter |= EFilterMtm;
		}
	return KErrNone;	
	}

// --------------------------------------------------------------------------- 
// Gets the mtm array
// ---------------------------------------------------------------------------
EXPORT_C const CDesCArray* CFilterParamInfo::Mtm() const
	{
	return iMtmArray;
	}

// --------------------------------------------------------------------------- 
// Sets subject filter
// ---------------------------------------------------------------------------
EXPORT_C void CFilterParamInfo::SetSubjectL( const TDesC& aSubject )
	{
	if ( iSubject )
		{
		delete iSubject;
		iSubject = NULL;
		iFilter ^= ( iFilter & EFilterSubject );
		}
	
	if ( aSubject.Length() )
		{
		iSubject = HBufC::NewL( aSubject.Length() );
		iSubject->Des().Copy( aSubject );
		iFilter |= EFilterSubject;
		}
	}

// --------------------------------------------------------------------------- 
// Gets the filter for subject of message
// ---------------------------------------------------------------------------
EXPORT_C TPtrC CFilterParamInfo::Subject() const
	{
    return iSubject ? TPtrC( *iSubject ) : TPtrC(); 
	}

// --------------------------------------------------------------------------- 
// Sets the sorting order
// ---------------------------------------------------------------------------
EXPORT_C void CFilterParamInfo::SetSortType( const TMsvSorting aSortType )
	{
    iSortType = aSortType;   
	}
	

// --------------------------------------------------------------------------- 
// Gets the sorting order
// ---------------------------------------------------------------------------
EXPORT_C TMsvSorting CFilterParamInfo::SortType() const
	{
	return iSortType;
	}


// --------------------------------------------------------------------------- 
// Sets the message id as filter
// ---------------------------------------------------------------------------
EXPORT_C void CFilterParamInfo::SetMessageIdFilter( const TMsvId aMessageId )
	{
	iFilter ^= ( iFilter & EFilterId );
	
	if( aMessageId != 0)
		{
		iMessageId = aMessageId;
		iFilter |= EFilterId;
		}
	}
	
// --------------------------------------------------------------------------- 
// Gets the message id as filter
// ---------------------------------------------------------------------------
EXPORT_C TMsvId CFilterParamInfo::MessageId() const
	{
	return iMessageId;
	}


// --------------------------------------------------------------------------- 
// Sets the starting date for date range as a filter
// ---------------------------------------------------------------------------
EXPORT_C void CFilterParamInfo::SetStartDateFilter( const TTime& aStartDate )
	{
	iFilter ^= ( iFilter & EFilterStartDate );
	

	if ( aStartDate.Int64() > 0 )
		{
		iStartDate = aStartDate;
		iFilter |= EFilterStartDate;
		}
	}
	

// --------------------------------------------------------------------------- 
// Gets the starting date for date range as a filter
// ---------------------------------------------------------------------------
EXPORT_C const TTime& CFilterParamInfo::StartDate() const
	{
	return iStartDate;
	}


// --------------------------------------------------------------------------- 
// Sets the ending date for date range as a filter
// ---------------------------------------------------------------------------
EXPORT_C void CFilterParamInfo::SetEndDate( const TTime& aEndDate )
	{
	iFilter ^= ( iFilter & EFilterEndDate );

	if ( aEndDate.Int64() > 0 )
		{
		iEndDate = aEndDate;
		iFilter |= EFilterEndDate;
		}
	}
	

// --------------------------------------------------------------------------- 
// Gets the ending date for date range as a filter
// ---------------------------------------------------------------------------
EXPORT_C const TTime& CFilterParamInfo::EndDate() const
	{
	return iEndDate;
	}

// --------------------------------------------------------------------------- 
// Gives the iFilter
// ---------------------------------------------------------------------------
EXPORT_C TInt CFilterParamInfo::Filter() const
	{
	return iFilter;
	}


// --------------------------------------------------------------------------- 
// Resets the filterinfo object
// ---------------------------------------------------------------------------
EXPORT_C void CFilterParamInfo::Reset()
	{
	if ( iFromArray )
		{
		iFromArray->Reset();
		}
		
	if ( iMtmArray )
		{
		iMtmArray->Reset();
		}
		
	delete iFromArray;
	iFromArray = NULL;
	delete iMtmArray;
	iMtmArray = NULL;
	delete iSubject;
	iSubject = NULL;
	iFilter = 0;
	}

CFilterParamInfo& CFilterParamInfo::operator=( const CFilterParamInfo& aFilterParamInfo )
	{
	if ( iFromArray )
		{
		iFromArray->Reset();
		delete iFromArray;
		iFromArray = NULL;
		}
	
	if ( aFilterParamInfo.iFromArray )
		{
		TInt count = aFilterParamInfo.iFromArray->Count();
		for( TInt index = 0; index < count; index++ )
			{
			AddFromL((*(aFilterParamInfo.iFromArray))[index]);
			}
		}

	if ( iMtmArray )
		{
		iMtmArray->Reset();
		delete iMtmArray;
		iMtmArray = NULL;
		}
	
	if ( aFilterParamInfo.iMtmArray )
		{
		TInt count = aFilterParamInfo.iMtmArray->Count();
		for( TInt index = 0; index < count; index++ )
			{
			AddMtmL((*(aFilterParamInfo.iMtmArray))[index]);
			}
		}

	delete iSubject;
	iSubject = NULL;
	if( aFilterParamInfo.iSubject )
		{
		iSubject = aFilterParamInfo.Subject().AllocL();
		}

	iSortType = aFilterParamInfo.iSortType;

	iMessageId = aFilterParamInfo.iMessageId;

	iStartDate = aFilterParamInfo.iStartDate;

	iEndDate = aFilterParamInfo.iEndDate;

	iFilter = aFilterParamInfo.iFilter;
	
	return *this;
	}



// --------------------------------------------------------------------------- 
// Two Phase constructor
// ---------------------------------------------------------------------------
EXPORT_C CSendMessageParams* CSendMessageParams::NewL()
	{
	return new(ELeave) CSendMessageParams;
	}
	

// --------------------------------------------------------------------------- 
// Destructor
// ---------------------------------------------------------------------------
CSendMessageParams::~CSendMessageParams()
	{
    if ( iRecipientArray )
	    {
	    iRecipientArray->Reset();
	    }

    if ( iAttachmentArray )
	    {
	    iAttachmentArray->ResetAndDestroy();
	    }

    delete iRecipientArray;
    delete iAttachmentArray;
    delete iSubject;
    delete iBodyText;
 	}
	
// --------------------------------------------------------------------------- 
// Constructor
// ---------------------------------------------------------------------------
CSendMessageParams::CSendMessageParams()
	{
	}


// --------------------------------------------------------------------------- 
// Adds Recipient 
// ---------------------------------------------------------------------------
EXPORT_C void CSendMessageParams::AddRecipientL( const TDesC& aRecipient, TMsvRecipientType aType )
	{
	if ( !iRecipientArray )
		{
	    iRecipientArray = CRecipientList::NewL();
		}
		
	if ( aRecipient.Length() )
		{
			iRecipientArray->AppendL( aType, aRecipient );
		}
	}

// --------------------------------------------------------------------------- 
// Gets the Recipient arrary
// ---------------------------------------------------------------------------
EXPORT_C const CRecipientList* CSendMessageParams::RecipientArray() const
	{
	return iRecipientArray;
	}


// --------------------------------------------------------------------------- 
// Adds attachment 
// ---------------------------------------------------------------------------
EXPORT_C void CSendMessageParams::AddAttachmentL( CMsvAttachment* aAttachment )
	{
    if ( !iAttachmentArray )
	    {
	    iAttachmentArray = new (ELeave) CArrayPtrSeg<CMsvAttachment>( KArrayGranularity );
	    }
	    
	if ( aAttachment )
		{
		iAttachmentArray->AppendL( aAttachment );
		}
	}

// --------------------------------------------------------------------------- 
// Gets the array of attachment information
// ---------------------------------------------------------------------------
EXPORT_C const CArrayPtr<CMsvAttachment>* CSendMessageParams::AttachmentArray()
	{
	return iAttachmentArray;
	}
	
// --------------------------------------------------------------------------- 
// Sets the subject for message
// ---------------------------------------------------------------------------
EXPORT_C void CSendMessageParams::SetSubjectL( const TDesC& aSubject )
	{
	if ( iSubject )
		{
		delete iSubject;
		iSubject = NULL;
		}
	
	if ( aSubject.Length() )
		{
		iSubject = HBufC::NewL( aSubject.Length() );
		iSubject->Des().Copy( aSubject );
		}
	}

// --------------------------------------------------------------------------- 
// Gets the subject for message
// ---------------------------------------------------------------------------
EXPORT_C const TPtrC CSendMessageParams::Subject() const
	{
    return iSubject ? TPtrC( *iSubject ) : TPtrC(); 
	}


// --------------------------------------------------------------------------- 
// Sets the body for message
// ---------------------------------------------------------------------------
EXPORT_C void CSendMessageParams::SetBodyTextL( const TDesC& aMsg )
	{
	if ( iBodyText )
		{
		delete iBodyText;
		iBodyText = NULL;
		}
	
	if ( aMsg.Length() )
		{
		iBodyText = HBufC::NewL( aMsg.Length() );
		iBodyText->Des().Copy( aMsg );
		}
	}

// --------------------------------------------------------------------------- 
// Appends the message to existing bodytext
// ---------------------------------------------------------------------------
void CSendMessageParams::AppendBodyTextL( const TDesC& aMsg )
	{
	if ( aMsg.Length() )
		{
		HBufC* tmpMsgBody = HBufC::NewL( aMsg.Length() + BodyText().Length() );
		CleanupStack::PushL( tmpMsgBody );
		tmpMsgBody->Des().Copy( BodyText() );
		tmpMsgBody->Des().Append( aMsg );
		delete iBodyText;
		iBodyText = tmpMsgBody;
		CleanupStack::Pop( tmpMsgBody );
		}
	}

// --------------------------------------------------------------------------- 
// Gets the body for message
// ---------------------------------------------------------------------------
EXPORT_C const TPtrC CSendMessageParams::BodyText() const
	{
    return iBodyText ? TPtrC( *iBodyText ) : TPtrC(); 
	}

// --------------------------------------------------------------------------- 
// Sets the templateid  
// ---------------------------------------------------------------------------
EXPORT_C void CSendMessageParams::SetTemplateId( const TMsvId aTemplateId )
	{
	iTemplateId = aTemplateId;
	}

// --------------------------------------------------------------------------- 
// Gets the templateid  
// ---------------------------------------------------------------------------
EXPORT_C TMsvId CSendMessageParams::TemplateId() const
	{
	return iTemplateId;
	}

// --------------------------------------------------------------------------- 
// Sets paramter to launch editor depends on argument value  
// ---------------------------------------------------------------------------
EXPORT_C void CSendMessageParams::SetLaunchEditor( const TBool aLaunchEditor )
	{
	iLaunchEditor = aLaunchEditor;
	}
	
// --------------------------------------------------------------------------- 
// Gets the LaunchEditor value  
// ---------------------------------------------------------------------------
EXPORT_C TBool CSendMessageParams::LaunchEditor() const
	{
	return iLaunchEditor;
	}

// --------------------------------------------------------------------------- 
// Sets the message type
// ---------------------------------------------------------------------------
EXPORT_C TInt CSendMessageParams::SetMessageTypeL( const TDesC& aMessageType )
	{
	if ( aMessageType.CompareF( KMessageTypeSMS ) == 0 )
		{
		iMessageType = KSenduiMtmSmsUid;
		}
	else if ( aMessageType.CompareF( KMessageTypeMMS ) == 0 )
		{
		iMessageType = KSenduiMtmMmsUid;
		}
	else
		{
		return KErrNotSupported;
		}
	return KErrNone;	
	}

// --------------------------------------------------------------------------- 
// Gets the message type
// ---------------------------------------------------------------------------	
EXPORT_C TUid CSendMessageParams::MessageType() const
	{
	return iMessageType;
	}

CSendMessageParams& CSendMessageParams::operator=(const CSendMessageParams& aSendMessageParams )
	{
	iMessageType = aSendMessageParams.iMessageType;

	iTemplateId = aSendMessageParams.iTemplateId;
	
	iLaunchEditor = aSendMessageParams.iLaunchEditor;
	
	delete iSubject;
	iSubject = NULL;
	if( aSendMessageParams.iSubject )
		{
		iSubject = aSendMessageParams.Subject().AllocL();
		}

	delete iBodyText;
	iBodyText = NULL;
	if( aSendMessageParams.iBodyText )
		{
		iBodyText = aSendMessageParams.BodyText().AllocL();
		}
	
	if ( iRecipientArray )
		{
		iRecipientArray->Reset();
		delete iRecipientArray;
		iRecipientArray = NULL;
		}
	
	if( aSendMessageParams.iRecipientArray )
		{
		TInt count = aSendMessageParams.iRecipientArray->Count();
		for(TInt index = 0; index < count; index++)
			{
			AddRecipientL( (*(aSendMessageParams.iRecipientArray))[index], 
									aSendMessageParams.iRecipientArray->Type(index) );
			}
		}
	
	if ( iAttachmentArray )
		{
		iAttachmentArray->ResetAndDestroy();
		delete iAttachmentArray;
		iAttachmentArray = NULL;
		}
	
	if ( aSendMessageParams.iAttachmentArray )
		{
		TInt count = aSendMessageParams.iAttachmentArray->Count();
		for(TInt index = 0; index < count; index++)
			{
			CMsvAttachment* element = aSendMessageParams.iAttachmentArray->At( index );
			CMsvAttachment* newElement = CMsvAttachment::NewL( *element );
			CleanupStack::PushL( newElement );
			AddAttachmentL( newElement );
			CleanupStack::Pop( newElement );
			}
		}

	return *this;
	}

/**
 * Two Phase Constructor
*/ 
EXPORT_C CMessageAttachInfo* CMessageAttachInfo::NewL()
	{
	return new(ELeave) CMessageAttachInfo;
	}

/**
 * Constructor
*/ 
CMessageAttachInfo::CMessageAttachInfo()
	{
	}

/**
 * Destructor
*/ 
CMessageAttachInfo::~CMessageAttachInfo()
	{
	delete iName;
	delete iMimeType;
	}

/** 
 * Sets the Attachment Name
 * @param aName Attachment Name
 * @return void
*/
EXPORT_C void CMessageAttachInfo::SetNameL(const TDesC& aName)
	{
	if( iName )
		{
		delete iName;
		iName = NULL;	
		}
	iName = aName.AllocL();	
	}

/** 
 * Gets the Attachment Name
 * @return TPtrC Attachment Name
*/
EXPORT_C const TPtrC CMessageAttachInfo::Name() const
	{
	return iName ? TPtrC( *iName ) : TPtrC(); 
	}

/** 
 * Sets the File handle
 * @param aFile File handle
 * @return void
*/
EXPORT_C void CMessageAttachInfo::SetFileHandle( RFile aFile)
	{
	iFile = aFile;
	}

/** 
 * Gets the File handle
 * @return RFile File handle
*/
EXPORT_C RFile CMessageAttachInfo::FileHandle() const
	{
	return iFile;
	}

/** 
 * Sets the File size
 * @param aSize File size
 * @return void
*/
EXPORT_C void CMessageAttachInfo::SetSize( TInt32 aSize)
	{
	iSize = aSize;
	}

/** 
 * Gets the File size
 * @return File size
*/
EXPORT_C TInt32 CMessageAttachInfo::Size() const
	{
	return iSize;
	}

/** 
 * Sets the Mime type
 * @param aMimeType Mime type
 * @return void
*/
EXPORT_C void CMessageAttachInfo::SetMimeTypeL(const TDesC& aMimeType)
	{
	if( iMimeType )
		{
		delete iMimeType;
		iMimeType = NULL;	
		}
	iMimeType = aMimeType.AllocL();	
	}

/** 
 * Gets the Mime type
 * @return TPtrC Mime type
*/
EXPORT_C const TPtrC CMessageAttachInfo::MimeType() const
	{
	return iMimeType ? TPtrC( *iMimeType ) : TPtrC(); 
	}



/**
 * Two Phase Constructor
*/ 
EXPORT_C CMessageDetailInfo* CMessageDetailInfo::NewL()
	{
	return new(ELeave) CMessageDetailInfo;
	}

/**
 * Constructor
*/ 
CMessageDetailInfo::CMessageDetailInfo()
	{
	}

/**
 * Destructor
*/ 
CMessageDetailInfo::~CMessageDetailInfo()
	{
	if ( iRecipientList )
		iRecipientList->Reset();
	
	if ( iAttachEntries )
		iAttachEntries->ResetAndDestroy();
	
	delete iBodyText;
	delete iFrom;
	delete iRecipientList;
	delete iAttachEntries;
	}

/**
 * Adds Recipient 
 * @param aRecipient recipient address
 * @param aType recipient type
*/
EXPORT_C void CMessageDetailInfo::AddRecipientL( const TDesC& aRecipient, TMsvRecipientType aType )
	{
	if ( !iRecipientList )
		{
	    iRecipientList = CRecipientList::NewL();
		}
		
	if ( aRecipient.Length() )
		{
			iRecipientList->AppendL( aType, aRecipient );
		}
	}

/**
 * Gives the receipient array
 * @return CRecipientList*
*/ 
EXPORT_C const CRecipientList* CMessageDetailInfo::RecipientArray() const
	{
	return iRecipientList;
	}

/** 
 * Sets the sender address
 * @param aFrom Sender address
 * @return void
*/
EXPORT_C void CMessageDetailInfo::SetFromL(const TDesC& aFrom)
	{
	if( iFrom )
		{
		delete iFrom;
		iFrom = NULL;	
		}
		
	iFrom = aFrom.AllocL();	
	}

/** 
 * Gets the sender address
 * @return TPtrC Sender address
*/
EXPORT_C const TPtrC CMessageDetailInfo::From() const
	{
	return iFrom ? TPtrC( *iFrom ) : TPtrC(); 
	}

/**
 * Sets the body for message
 * @param aMsg Body for message
*/
EXPORT_C void CMessageDetailInfo::SetBodyTextL( const TDesC& aMsg )
	{
	if( iBodyText )
		{
		delete iBodyText;
		iBodyText = NULL;	
		}
		
	iBodyText = aMsg.AllocL();	
	}

/**
 * Gets the body text 
 * @return  TPtrC 
*/
EXPORT_C const TPtrC CMessageDetailInfo::BodyText() const
	{
	return iBodyText ? TPtrC( *iBodyText ) : TPtrC(); 
	}

/** 
 * Sets the message id
 * @param aMessageID Message ID
 * @return void
*/
EXPORT_C void CMessageDetailInfo::SetMessageId(const TMsvId aMessageId)
	{
	iMessageId = aMessageId;
	}

/** 
 * Gets the message id
 * @return TMsvId Message ID
*/
EXPORT_C TMsvId CMessageDetailInfo::MessageId() const
	{
	return iMessageId;
	}

/**
 * Adds attachment 
 * @param aAttachment attachment information
*/
EXPORT_C void CMessageDetailInfo::AddAttachmentInfoL( CMessageAttachInfo* aAttachment )
	{
   if ( !iAttachEntries )
	    {
	    iAttachEntries = new (ELeave) CArrayPtrSeg<CMessageAttachInfo>( KArrayGranularity );
	    }
	    
	if ( aAttachment )
		{
		iAttachEntries->AppendL( aAttachment );
		}
	}

/**
 * Gives the attachment array
 * @return CArrayPtr<CMsvAttachment>*
*/ 
EXPORT_C const CArrayPtr<CMessageAttachInfo>* CMessageDetailInfo::AttachmentInfoArray()
	{
	return iAttachEntries;
	}

