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
* Description:  Defination of class CMessagingAccessFolder
*
*/


#ifndef __ACCESSFOLDER_H
#define __ACCESSFOLDER_H


/**
 * This class provides function to get a list of measage header 
 * in a sorted order present in a folder . Message Headers are 
 * retrieved as per searching options provided by user. 
*/
class CMessagingAccessFolder : public CBase
	{

	public:

	    /**
	     * Two-phased constructor.
	     * @param aServerSession  Object of CMsvSession Class which
	     *        represents a channel of communication between a client thread  
	     *        and the Message Server thread.
	     */
		static CMessagingAccessFolder* NewL( CMsvSession& aServerSession );

	    /**
	    * Destructor.
	    */
		~CMessagingAccessFolder();
	
	private:

	    /** 
	     * Constructor.
	     * @param aServerSession  Object of CMsvSession Class which
	     *        represents a channel of communication between a client thread  
	     *        and the Message Server thread .
	     * @return void
	     */
		CMessagingAccessFolder( CMsvSession& aServerSession );


	public:

		/**
		 * Gives Message id list of messages 
		 * @param aFolderId  	 Folder to be used (Inbox/outbox/send/...)
		 * @param aFilterParams  Filter parameters
		 * @param aEntrySelection   output pararmeter for the result id array
		*/ 				
		void GetIdListL(TMsvId aFolderId ,
									CFilterParamInfo* aFilterParams,
								    CMsvEntrySelection*& aEntrySelection );
	
		/**
		 * Gives next header based on inputs 
		 * @param aFilterParams  Filter parameters
		 * @param aEntrySelection array of message ids on which filteration to be done
		 * @param aIndex      starting position on aEntrySelection to be start search
		 * @param aHeader   output pararmeter for the result header
		*/ 				
		void GetNextHeaderL( CFilterParamInfo* aFilterParams,
									CMsvEntrySelection* aEntrySelection,
									TInt& aIndex, 
									CMessageHeader*& aHeader );
	private:

		/**
		 * Gives the list of message headers
		 * @return void
		*/ 
		void GetListL();

		/**
		 * Gets next header which matches filter criteria
		 * @param  aEntrySelection Message Id list to be filtered for headers
		 * @param  aIndex starting position for filterting
		 * @param  aHeader return parameter for message header
		 * @return void
		*/ 
		void GetNextFilteredHeaderL( CMsvEntrySelection* aEntrySelection, 
											TInt& aIndex, 
											CMessageHeader*& aHeader );
														
		/**
		 * Initializes the MtmID array by the Mtm string passed by user.\
		*/ 
		void  InitializeMtmArray();

		/**
		 * Checks whether filter on message id is set
		 * @param  aMessageId The message id to which user want to apply filter
		 * @return TBool ETrue if filter on message id is set and entry matches with filter
		*/ 
		TBool FilterId( const TMsvId aMessageId) const;

		/**
		 * Checks whether filter on Mtm is set
		 * @param  aEntry The message entry to which user want to apply filter
		 * @return  TBool ETrue if filter on mtm is set and entry matches with filter
		*/ 
		TBool FilterMtm( const TMsvEntry& aEntry ) const;

		/**
		 * Checks whether filter on sender is set
		 * @param  aEntry The message entry to which user want to apply filter
		 * @return TBool  ETrue if filter on sender is set and entry matches with filter
		*/ 
		TBool FilterFrom( const TMsvEntry& aEntry ) const;

		/**
		 * Checks whether filter on subject is set
		 * @param  aEntry The message entry to which user want to apply filter
		 * @return TBool  ETrue if filter on subject is set and entry matches with filter
		*/ 
		TBool FilterSubject( const TMsvEntry& aEntry ) const;

		/**
		 * Checks whether filter on date is set
		 * @param  aEntry The message entry to which user want to apply filter
		 * @return TBool ETrue if filter on date is set and entry matches with filter
		*/ 
		TBool FilterDate( const TMsvEntry& aEntry ) const;


	private:

		/**
		 * Represents a channel of communication between a client thread 
		 * and the Message Server thread
		*/ 
	 	CMsvSession& 			iServerSession;
	 	
		/**
		 * Message Id list 
		*/ 
	 	CMsvEntrySelection*		iEntrySelection;

		/**
		 * Folder id from which list of message headers can be retrieved
		*/ 
		TMsvId 					iFolderId;

		/**
		 * Folder id from which list of message headers can be retrieved
		*/ 
        RArray<TUid> 			iMtmArrayId;

		/**
		 * Filter variable
		*/ 
        CFilterParamInfo*       iFilter;    

	};

#endif __ACCESSFOLDER_H