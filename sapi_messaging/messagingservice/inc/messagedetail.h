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
* Description:  Defination of class CMessageDetail
*
*/


#ifndef __MESSAGEDETAIL_H
#define __MESSAGEDETAIL_H


/**
 * This class provides function to get the message details. 
 * For SMS message, it gives bodytext, sender and recipient info.
 * For MMS, it gives list of attachment information, recipient, sender.
 */
class CMessageDetail : public CBase
	{

	public:
	    /**
	     * Two-phased constructor.
	     * @param aServerSession  It is an object of CMsvSession Class which
	     *        represents a channel of communication between a client thread  
	     *        and the Message Server thread .
	     * @return CMessageDetail
	    */

		static CMessageDetail* NewL( CMsvSession& aServerSession );

	    /** 
	     * Destructor.
	    */
		~CMessageDetail();
	
	private:

	    /** 
	     * Constructor.
	     * @param aServerSession  It is an object of CMsvSession Class which
	     *        represents a channel of communication between a client thread  
	     *        and the Message Server thread .
	    */
		CMessageDetail( CMsvSession& aServerSession );
	
	
	public:

		/**
		 * Gets the message details.
		 * Issues the synchronous or asynchronous request for function call 
		 * depending on the aNotifyCallback.
		 * @param aMessageId    Message Entry Id
		 * @param aMessageDetail Return parameter for synchronous call
		 * @return void 
		*/ 
		void GetMessageDetailL( TMsvId aMessageId, 
								CMessageDetailInfo*& aMessageDetail );

	private:

		/**
		 * Starts get detail request
		 * @return void
		*/ 
		void ProcessRequestL();
		
		/**
		 * Gets the Sender Recipient information for SMS
		 * @return void
		*/ 
		void GetSmsSenderRecipientL();

		/**
		 * Gets the Sender Recipient information for MMS
		 * @return void
		*/ 
		void GetMmsSenderRecipientL();


	private:

		/**
		 * Represents a channel of communication between a client thread 
		 * and the Message Server thread
		*/ 
	 	CMsvSession& 			iServerSession;

		/**
		 * Message Id
		*/ 
	 	TMsvId					iMessageId;

		/**
		 * Message detail
		*/ 
		CMessageDetailInfo* 	iMessageDetail;
	};


#endif __MESSAGEDETAIL_H