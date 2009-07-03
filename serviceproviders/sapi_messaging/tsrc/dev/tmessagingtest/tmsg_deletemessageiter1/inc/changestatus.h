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



#ifndef __CHANGESTATUS_H
#define __CHANGESTATUS_H

/**
 * This class implements ChangeStatus SAPI core logic.It includes  
 * methods for changing the status of message flag and deleting a message.
 * 
 */
class CMessageChangeStatus : public CBase
{

	public:
	 
		 /*
		 * Creates a new instance of a @ref CMessageChangeStatus
		 * @param CMsvSession
		 * @return The newly created CMessageChangeStatus
		 */
		static CMessageChangeStatus* NewL( CMsvSession& aSession );

		/*
		* Creates a new instance of a @ref CMessageChangeStatus
		* @param CMsvSession
		* @return The newly created CMessageChangeStatus
		*/
		static CMessageChangeStatus* NewLC( CMsvSession& aSession );

		/**
		 * Destructor.
		 */
		~CMessageChangeStatus();

		/**
		* Deletes the message of specified ID
		* @param aMsgId It is ID of message to be deleted
		* @param aNotifyCallback a callback object
		*/
		void DeleteMessageL( const TMsvId& aMsgId );

		/**
		* Changes the message flag to the value specified
		* @param aMsgId It is ID of message
		* @param aStatusFlag Message status flag
		* @param aValue  Message status flag value
		* @param aNotifyCallback a callback object
		*/
		void ChangeStatusL(const TMsvId& aMsgId, 
									const TMessageStatusFlag aStatusFlag, 
									const TBool aValue );
	
	private:

		/** 
	     * Default  constructor.
	     * @param aSession  It is an object of CMsvSession Class which
	     *        represents a channel of communication between a client thread  
	     *        and the Message Server thread .
	     */
		CMessageChangeStatus(CMsvSession& aSession);
		
		/**
		* Initializer
		*/
		void InitializeL();

		/**
		*   changes the message status 
		*/
		void ChangeStatusL();

		/**
		*   completes delete request
		*/
		void DeleteMessageL();
		
	private:

		/**
		 * Message server session. 
		*/
		CMsvSession& 			iServerSession;
		
		/**
		 * Message ID 
		*/ 
		TMsvId 					iMessageId;
		
		/**
		 * Message entry 
		*/ 
		CMsvEntry* 				iEntry;
		
		/**
		 * Index entry 
		*/ 
		TMsvEntry 				iIndexEntry;
		
		/**
		 * Message Status Flag
		*/ 
		TMessageStatusFlag		iStatusFlag;
		
		/**
		 * status flag value.
		*/ 
		TBool 					iFlagValue;
	
};


#endif __CHANGESTATUS_H