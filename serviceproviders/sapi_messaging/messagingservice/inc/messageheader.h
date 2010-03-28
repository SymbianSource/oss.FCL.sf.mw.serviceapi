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
* Description:  Support for header information retrieval 
*
*/


#ifndef __MESSAGEHEADER_H
#define __MESSAGEHEADER_H

#include <e32base.h>
#include <msvstd.h>
#include <msvapi.h>
#include <cmsvrecipientlist.h>

class CMsvAttachment;
class CRecipientList;

const TInt KArrayGranularity = 4;

_LIT(KMessageTypeMMS, 	"MMS");
_LIT(KMessageTypeSMS, 	"SMS");
_LIT(KUnknown, 			"unknown");
_LIT(KPriorityHigh, 	"High");
_LIT(KPriorityMedium, 	"Medium");
_LIT(KPriorityLow, 		"Low");

/**
 * TMessageStatusFlag enum for status of message
*/
enum TMessageStatusFlag
	{
	EUnread = 0,
	EReplied,
	EForward,
	EDelete
	};
	
/**
 * TNotificationType enum for notification of new arrival of message 
*/
enum TNotificationType
	{
	ENewMessage = 0
	};

/**
 * TMessageFilter enum is provided to filtering out search options 
*/
enum TMessageFilter
	{
	EFilterId = 		0x1,
	EFilterMtm = 		0x2,
	EFilterFrom = 		0x4,
	EFilterSubject = 	0x8,
	EFilterStartDate = 	0x10,
	EFilterEndDate = 	0x20
	};

/**
 * CFilterParamInfo  Contains filter and sorting information required for getting header list
*/
class CFilterParamInfo : public CBase
	{
	public:
	
		/**
		 * Two Phase Constructor
		*/ 
		IMPORT_C static CFilterParamInfo* NewL();
	
		/**
		 * Destructor
		*/ 
		~CFilterParamInfo();
		
		/**
		 * Adds the sender address as a filter
		 * @param aFrom It is sender address 
		 * @return void
		*/ 
		IMPORT_C void AddFromL( const TDesC& aFrom );

		/**
		 * Gets the sender address list
		 * @return CDesCArray*
		*/ 
		IMPORT_C const CDesCArray* From() const ;

		/**
		 * Adds the mtm as a filter
		 * @param aMtm It is mtm type
		 * @return void
		*/ 
		IMPORT_C TInt AddMtmL( const TDesC& aMtm );

		/**
		 * Gets the mtm list
		 * @return CDesCArray*
		*/ 
		IMPORT_C const CDesCArray* Mtm() const;

		/**
		 * Sets the subject filter
		 * @param aSubject It is the subject which user want to set as filter
		 * @return void
		*/ 
		IMPORT_C void SetSubjectL( const TDesC& aSubject );

		/**
		 * Gets the subject filter
		 * @return TPtrC
		*/ 
		IMPORT_C TPtrC Subject() const;

		/**
		 * Sets the sorting order
		 * @param aSortType It could be { @c EMsvSortByNone , @c EMsvSortByDate ,@c EMsvSortByDateReverse ,
		                      @c EMsvSortBySize ,@c  EMsvSortBySizeReverse, @c  EMsvSortByDetails ,
		                      @c EMsvSortByDetailsReverse ,@c EMsvSortByDescription ,@c EMsvSortByDescriptionReverse ,
		                      @c EMsvSortById ,@c EMsvSortByIdReverse } defined in @c MSVSTD.H 
		 * @return void		                      
		*/ 
		IMPORT_C void SetSortType( const TMsvSorting aSortType );

		/**
		 * Gets the sorting order
		 * @return TMsvSorting		                      
		*/ 
		IMPORT_C TMsvSorting SortType() const;

		/**
		 * Sets the message id as filter
		 * @param aMessageId It is the message id which user want to set as filter
		 * @return void
		*/ 
		IMPORT_C void SetMessageIdFilter( const TMsvId aMessageId );
		
		/**
		 * Gets the message id filter
		 * @return TMsvId
		*/ 
		IMPORT_C TMsvId MessageId() const;

		/**
		 * Sets the starting date for date range as a filter
		 * @param aStartDate It is the date to which we want 
		 *                   to set as starting date for date range
		 * @return void
		*/ 
		IMPORT_C void SetStartDateFilter( const TTime& aStartDate );
		
		/**
		 * Gets the starting date for date range as a filter
		 * @return TTime&
		*/ 
		IMPORT_C const TTime& StartDate() const;

		/**
		 * Sets the ending date for date range as a filter
		 * @param aEndDate It is the date to which we want 
		 *                 to set as ending date for date range
		 * @return void
		*/ 
		IMPORT_C void SetEndDate( const TTime& aEndDate );

		/**
		 * Gets the ending date for date range as a filter
		 * @return TTime&
		*/ 
		IMPORT_C const TTime& EndDate() const;

		/**
		 * Gives the iFilter 
		 * @return TInt 
		*/ 
		IMPORT_C TInt Filter() const;

		/**
		 * Resets the filterinfo object
		 * @return void 
		*/ 
		IMPORT_C  void Reset();
		
        /** 
        * Assignment operator. 
        * @param aFilterParamInfo Item to assign.
        * @return The source object.
        */
		CFilterParamInfo& operator=(const CFilterParamInfo& aFilterParamInfo);
		
	private:
		
		/**
		 * Constructor
		*/ 
		CFilterParamInfo();
		

	private:	

		/**
		 * Sender Array  
		*/ 
		CDesCArray* 			iFromArray;

		/**
		 * Mtm Array
		*/ 
		CDesCArray* 			iMtmArray;

		/**
		 * Subject 
		*/ 
		HBufC* 					iSubject;

		/**
		 * Sort type
		*/ 
		TMsvSorting				iSortType;

		/**
		 * Message Id
		*/ 
		TMsvId					iMessageId;

		/**
		 * Starting date of date range
		*/ 
		TTime 					iStartDate;

		/**
		 * End date of date range
		*/ 
		TTime					iEndDate;

		/**
		 * Filter options
		*/ 
		TInt					iFilter;
	};
	
	
/**
 * CMessageAttachInfo  Structure for attachment information
*/
class CMessageAttachInfo : public CBase
	{
	public: 
	
		/**
		 * Two Phase Constructor
		*/ 
		IMPORT_C static CMessageAttachInfo* NewL();

		/**
		 * Destructor
		*/ 
		~CMessageAttachInfo();
		
	    /** 
	     * Sets the Attachment Name
	     * @param aName Attachment Name
	     * @return void
	    */
		IMPORT_C void SetNameL(const TDesC& aName);
		
	    /** 
	     * Gets the Attachment Name
	     * @return TPtrC Attachment Name
	    */
		IMPORT_C const TPtrC Name() const;

	    /** 
	     * Sets the File handle
	     * @param aFile File handle
	     * @return void
	    */
		IMPORT_C void SetFileHandle( RFile aFile);
		
	    /** 
	     * Gets the File handle
	     * @return RFile File handle
	    */
		IMPORT_C RFile FileHandle() const;

	    /** 
	     * Sets the File size
	     * @param aSize File size
	     * @return void
	    */
		IMPORT_C void SetSize( TInt32 aSize);
		
	    /** 
	     * Gets the File size
	     * @return File size
	    */
		IMPORT_C TInt32 Size() const;

	    /** 
	     * Sets the Mime type
	     * @param aMimeType Mime type
	     * @return void
	    */
		IMPORT_C void SetMimeTypeL(const TDesC& aMimeType);
		
	    /** 
	     * Gets the Mime type
	     * @return TPtrC Mime type
	    */
		IMPORT_C const TPtrC MimeType() const;

	
	private:
	
		/**
		 * Constructor
		*/ 
		CMessageAttachInfo();
		
	private:
		
		/**
		 * Attachment name
		*/ 
		HBufC* 					iName;

		/**
		 * File Handle for attachment
		*/ 
		RFile					iFile;

		/**
		 * Size of attachment
		*/ 
		TInt32					iSize;

		/**
		 * Mimetype
		*/ 
		HBufC* 					iMimeType;
	};	
	
/**
 * CMessageDetailInfo  Structure for message detail  information
*/
class CMessageDetailInfo : public CBase
	{
	public:

		/**
		 * Two Phase Constructor
		*/ 
		IMPORT_C static CMessageDetailInfo* NewL();

		/**
		 * Destructor
		*/ 
		~CMessageDetailInfo();
		
	    /**
	     * Adds Recipient 
	     * @param aRecipient recipient address
	     * @param aType recipient type
	    */
		IMPORT_C void AddRecipientL( const TDesC& aRecipient, 
										TMsvRecipientType aType = EMsvRecipientTo );

		/**
		 * Gives the receipient array
		 * @return CRecipientList*
		*/ 
		IMPORT_C const CRecipientList* RecipientArray() const;

	    /** 
	     * Sets the sender address
	     * @param aFrom Sender address
	     * @return void
	    */
		IMPORT_C void SetFromL(const TDesC& aFrom);
		
	    /** 
	     * Gets the sender address
	     * @return TPtrC Sender address
	    */
		IMPORT_C const TPtrC From() const;

	    /**
	     * Sets the body for message
	     * @param aMsg Body for message
	    */
		IMPORT_C void SetBodyTextL( const TDesC& aMsg );

	    /**
	     * Gets the body text 
	     * @return  TPtrC 
	    */
		IMPORT_C const TPtrC BodyText() const;
		
	    /** 
	     * Sets the message id
	     * @param aMessageID Message ID
	     * @return void
	    */
		IMPORT_C void SetMessageId(const TMsvId aMessageID);
		
	    /** 
	     * Gets the message id
	     * @return TMsvId Message ID
	    */
		IMPORT_C TMsvId MessageId() const;
		
	    /**
	     * Adds attachment 
	     * @param aAttachment attachment information
	    */
		IMPORT_C void AddAttachmentInfoL( CMessageAttachInfo* aAttachment );

		/**
		 * Gives the attachment array
		 * @return CArrayPtr<CMsvAttachment>*
		*/ 
		IMPORT_C const CArrayPtr<CMessageAttachInfo>* AttachmentInfoArray();

	private:
	
		/**
		 * Constructor
		*/ 
		CMessageDetailInfo();
		
	private:	

		/**
		 * Message ID
		*/ 
		TMsvId 					iMessageId;

		/**
		 * Message Body text
		*/ 
		HBufC* 					iBodyText;

		/**
		 * Sender address
		*/ 
		HBufC*					iFrom;

		/**
		 * Receipient List
		*/ 
		CRecipientList*			iRecipientList;

		/**
		 * Array of Attachments
		*/ 
		CArrayPtr<CMessageAttachInfo>* iAttachEntries;
	};
	
/**
 * CSendMessageParams  Contains parameters required for sending a message
*/	
class CSendMessageParams : public CBase
	{
	public:	

		/**
		 * Two Phase Constructor
		*/ 
		IMPORT_C static CSendMessageParams* NewL();

		/**
		 * Destructor
		*/ 
		~CSendMessageParams();
		
	    /**
	     * Adds Recipient 
	     * @param aRecipient recipient address
	     * @param aType recipient type
	    */
		IMPORT_C void AddRecipientL( const TDesC& aRecipient, 
									TMsvRecipientType aType = EMsvRecipientTo );

		/**
		 * Gives the receipient array
		 * @return CRecipientList*
		*/ 
		IMPORT_C const CRecipientList* RecipientArray() const;

	    /**
	     * Adds attachment 
	     * @param aAttachment attachment information
	    */
		IMPORT_C void AddAttachmentL( CMsvAttachment* aAttachment );

		/**
		 * Gives the attachment array
		 * @return CArrayPtr<CMsvAttachment>*
		*/ 
		IMPORT_C const CArrayPtr<CMsvAttachment>* AttachmentArray();

	    /**
	     * Sets the message subject
	     * @param aSubject Message Subject 
	    */
		IMPORT_C void SetSubjectL( const TDesC& aSubject );

	    /**
	     * Gives message subject 
	     * @return  TPtrC 
	    */
		IMPORT_C const TPtrC Subject() const;

	    /**
	     * Sets the body for message
	     * @param aMsg Body for message
	    */
		IMPORT_C void SetBodyTextL( const TDesC& aMsg );

	    /**
	     * Appends the message to the existing bodytext
	     * @param aMsg Body for message
	    */
		void AppendBodyTextL( const TDesC& aMsg );

	    /**
	     * Gets the body text 
	     * @return  TPtrC 
	    */
		IMPORT_C const TPtrC BodyText() const;

	    /**
	     * Sets the templateid  
	     * @param aTemplateId template id
	    */
		IMPORT_C void SetTemplateId( const TMsvId aTemplateId );

	    /**
	     * Gets the template id
	     * @return  TMsvId 
	    */
		IMPORT_C TMsvId TemplateId() const;

	    /**
	     * Sets paramter to launch editor depends on argument value
	     * if ETrue then launches editor or if EFalse the don't launch editor.
	     * @param aLaunchEditor Boolean param 
	    */
		IMPORT_C void SetLaunchEditor( const TBool aLaunchEditor = ETrue );

	    /**
	     * Gets the LaunchEditor value
	     * @return  TBool
	    */
		IMPORT_C TBool LaunchEditor() const;

	    /**
	     * Sets the message type
	     * @param aMessageType Describing message type (SMS/MMS)
	    */
		IMPORT_C TInt SetMessageTypeL( const TDesC& aMessageType );

	    /**
	     * Gets the messagetype
	     * @return TUid 
	    */
		IMPORT_C TUid MessageType() const;

        /** 
        * Assignment operator. 
        * @param aSendMessageParams Item to assign.
        * @return The source object.
        */
		CSendMessageParams& operator=(const CSendMessageParams& aSendMessageParams);
		
	private:
	
	    /**
	     * Constructor
	    */
		CSendMessageParams();	
	
	private:	
	
	    /**
	     * Message Type
	    */
		TUid 					iMessageType;

	    /**
	     * Template id
	    */
		TMsvId 					iTemplateId;

	    /**
	     * Receipient Array
	    */
		CRecipientList* 		iRecipientArray;

	    /**
	     * Attachment Array
	    */
		CArrayPtr<CMsvAttachment>* iAttachmentArray;

	    /**
	     * Subject of message
	    */
		HBufC* 					iSubject;

	    /**
	     * Bpodytext
	    */
		HBufC* 					iBodyText;

	    /**
	     * Launch editor variable
	    */
		TBool 					iLaunchEditor;
	};	
	
/**
 * Contains recipients information
*/
class CRecipientList : public CBase
{
	public:

	    /**
	     * Two-phased constructor.
	     * @return CRecipientList*
	    */
		IMPORT_C static CRecipientList* NewL();

	    /**
	     * Destructor.
	    */
		~CRecipientList();

	    /** 
	     * Appends the recipient type 
	     * @param  aValue Recipient Type
	     * @param  aPtr recipient address
	     * @return void
	    */
		IMPORT_C void AppendL(TMsvRecipientType aType, const TDesC& aRecipient);

	    /**
	     * Gives the number of elements in recipient list
	     * @return TInt 
	    */
		IMPORT_C TInt Count() const;
		
	    /**
	     * Gives the recipient type
	     * @param aPos position 
	     * @return TMsvRecipientType 
	    */
		IMPORT_C TMsvRecipientType Type(TInt aPos) const;
		
	    /**
	     * Gives the recipient address
	     * @param aIndex index 
	     * @return TDesC recipient address
	    */		
		IMPORT_C const TDesC& operator[](TInt aIndex) const;
		
	    /**
	     * Resets the recipient list
	     * @return void
	    */		
		IMPORT_C void Reset();
	
	private: 

	    /**
	     * Symbian Constructor.
	    */
		void ConstructL();

	    /**
	     * Constructor
	    */
		CRecipientList();
		
	
	private:

	    /**
	     * Recipient type 
	    */
		RArray<TMsvRecipientType> iRecipientType;

	    /**
	     * Recipients
	    */
		CDesCArrayFlat*	iRecipients;
};

/**
 * Gives Message header 
*/
class CMessageHeader : public CBase
	{
	public:
	
	    /**
	     * Two-phased constructor.
	     * @return CMessageHeader*
	    */
		IMPORT_C static CMessageHeader* NewL();
	
	    /**
	    * Destructor.
	    */
		virtual ~CMessageHeader();
		
	private:

	    /** 
	     * Symbain   constructor.
	    */
		CMessageHeader();
		
	public:
		
	    /** 
	     * Sets the unread flag
	     * @param  aUnread unread flag
	     * @return void
	    */
		IMPORT_C void SetUnreadFlag(const TBool aUnread);

	    /** 
	     * Gets the unread flag
	     * @param aUnead Unread flag	    
	     * @return void
	    */
		IMPORT_C void GetUnreadFlag(TBool& aUnread) const;

	    /** 
	     * Gets the unread flag
	     * @return TBool unread flag	    
	    */
		IMPORT_C TBool UnreadFlag() const;

	    /** 
	     * Sets the attahment flag
	     * @param aAttachment Attachment flag
	     * @return void
	    */
		IMPORT_C void SetAttachFlag(const TBool aAttachment);

	    /** 
	     * Gets the attachment flag
	     * @param aAttachment Attachment flag	    
	     * @return void
	    */
		IMPORT_C void GetAttachFlag(TBool& aAttachment) const;

	    /** 
	     * Gets the Attachment flag
	     * @return TBool Attachment flag	    
	    */
		IMPORT_C TBool AttachFlag() const;

	    /** 
	     * Sets the priority flag
	     * @param aPriority Priority flag	    
	     * @return void
	    */
		IMPORT_C void SetPriorityFlag(const TMsvPriority aPriority);

	    /** 
	     * Gets the priority flag
	     * @param aPriority Priority flag	    	    
	     * @return void
	    */
		IMPORT_C void GetPriorityFlag(TMsvPriority& aPriority) const;

	    /** 
	     * Gets the priority 
	     * @return TPtrC Priority 	    	    
	    */
		IMPORT_C TPtrC Priority() const;

	    /** 
	     * Sets the mtm type
	     * @param aMtm Mtm id
	     * @return void
	    */
		IMPORT_C void SetMtmId(const TUid aMtm);
		
	    /** 
	     * Gets the mtm type
	     * @param aMtm Mtm id
	     * @return void
	    */
		IMPORT_C void GetMtmId(TUid& aMtm) const;
		
	    /** 
	     * Gets the mtm type
	     * @return TPtrC Message Type
	    */
		IMPORT_C TPtrC Mtm() const;

	    /** 
	     * Sets the message id
	     * @param aMessageID Message ID
	     * @return void
	    */
		IMPORT_C void SetMessageId(const TMsvId aMessageID);
		
	    /** 
	     * Gets the message id
	     * @param aMessageID Message ID
	     * @return void
	    */
		IMPORT_C void GetMessageId(TMsvId& aMessageID) const;
		
	    /** 
	     * Gets the message id
	     * @return TMsvId Message ID
	    */
		IMPORT_C TMsvId MessageId() const;
		
	    /** 
	     * Sets the time 
	     * @param aTime Time 
	     * @return void
  	  */
		IMPORT_C void SetTime(const TTime& aTime);
		
	    /** 
	     * Gets the time
	     * @param aTime Time 
	     * @return void
	    */
		IMPORT_C void GetTime(TTime& aTime) const;
		
	    /** 
	     * Gets the time
	     * @return TTime 
	    */
		IMPORT_C const TTime& Time() const;
		
	    /** 
	     * Sets the sender address
	     * @param aFrom Sender address
	     * @return void
	    */
		IMPORT_C void SetFromL(const TDesC& aFrom);
		
	    /** 
	     * Gets the sender address
	     * @return TPtrC Sender address
	    */
		IMPORT_C const TPtrC From() const;
		
	    /** 
	     * Sets the message subject
	     * @param aSubject Subject of message
	     * @return void
	    */
		IMPORT_C void SetSubjectL(const TDesC& aSubject);
		
	    /** 
	     * Gets the message 
	     * @return TPtrC Subject of message	     
	    */
		IMPORT_C const TPtrC Subject() const;

	private:
		
	    /** 
	     * Unread flag
	    */
		TBool			iUnread;
		
	    /** 
	     * Attachment flag
	    */
		TBool			iAttachment;
		
	    /** 
	     * Priority
	    */
		TMsvPriority	iPriority;
		
	    /** 
	     * Priority as string
	    */
		HBufC* 			iPriAsString;	

	    /** 
	     * Mtm
	    */
		TUid 			iMtm;

	    /** 
	     * Mtm
	    */
		HBufC* 			iMtmAsString;
		
	    /** 
	     * Message subject
	    */
		HBufC* 			iSubject;
		
	    /** 
	     * Address of sender
	    */
		HBufC* 			iFrom;
		
	    /** 
	     * Time
	    */
		TTime 			iTime;
			
	    /** 
	     * Entry id of message
	    */
		TMsvId 			iMessageID;
	}; 

/**
 * Messaging Callback base class
*/
class CMsgCallbackBase : public CBase
	{
	public:

	/**
	   * Gives the result
	   * @param aErrCode Error code
	   * @param aResult Result 
	   * @return void
  	*/
		virtual void NotifyResultL(TInt aErrCode, TAny* aResult) = 0;
		
	/**
	   * Gives the result
	   * @param aErrCode Error code
	   * @param aEntrySelection EntrySelection 
	   * @param aFilter Filter
	   * @return void
  	*/
		virtual void HandleGetlistL ( TInt aErrCode, CMsvEntrySelection* aEntrySelection, CFilterParamInfo* aFilter ) = 0;

		/**
	   * Input param 
  	*/		
		const TAny* iPtrInParamList; 

		/**
	   * Callback 
  	*/		
		TAny* iPtrNotifyCallback; 
		
		/**
	   * Transaction Id
  	*/		
		TInt32 iTransactionId;
	};
	
/**
 * Interface used to get callback notification from async request module 
 *	about completion of request. Implemented by the CMessagingService class, 
 *  which is used by the service modules to notify about request completion.
*/
class MAsyncRequestObserver	
	{
	public:

	/**
	   * Notifies Messaging service about the completeion of the request
	   * @param aTransactionId Asynchronous request transaction ID
	   * @return void
  	*/
		virtual void RequestComplete( TInt32 aTransactionId ) = 0;
	};

	
/**
 * Structure for storing transaction id and associated active object.
*/
struct TAsyncRequestInfo
	{

    /**
     * TransactionId
    */
	TInt32 iTransactionId;

    /**
     * Active object pointer
    */
	CActive* iAsyncObj;
	};
	


#endif __MESSAGEHEADER_H
