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


#ifndef __SENDMESSAGE_H
#define __SENDMESSAGE_H

#include <rsendas.h>
#include <rsendasmessage.h>

class CMsvAttachment;
class CRecipientList;
class CMsgCallbackBase;

/**
 * This class provides functionality for sending SMS/MMS messages.
*/
class CSendMessage : public CActive
	{

	/**
	 * TMessageState enum represents the message states for asynchronous requests.
	*/
	enum TMessageState
		{
		EInitialize = 0,
		EValidate,
		ESend,
		EComplete
		};
		

	public:
	
	    /**
	     * Two-phased constructor.
	     * @param aServerSession  Object of CMsvSession Class which
	     *        represents a channel of communication between a client thread  
	     *        and the Message Server thread.
	     * @return CSendMessage object
	    */
		static CSendMessage* NewL( CMsvSession& aServerSession );

	    /**
	    * Destructor.
	    */
		virtual ~CSendMessage();

		
	private:

	    /** 
	     * Constructor.
	     * @param aServerSession  Object of CMsvSession Class which
	     *        represents a channel of communication between a client thread  
	     *        and the Message Server thread .
	    */
		CSendMessage( CMsvSession& aServerSession );


	public:	
	
	    /**
	     * Sets message input parameters 
	     * Ownership is transferred to this class
	     * @param aMessageParam Message Input Parameters
		 * @param aTemplateDetail 
	     * @param aNotifyCallback Bydefault it is NULL to make function
	     *        call synchronous , if provided then function call is asynchronous                  
		 * @param aAsyncRequestObserver Asynchronous request observer
	    */
		void SetInputParamsL( CSendMessageParams* aMessageParam, 
								CMessageDetailInfo* aTemplateDetail = NULL,
								CMsgCallbackBase* aNotifyCallback = NULL,
								MAsyncRequestObserver* aAsyncRequestObserver = NULL);
		
	    /**
	     * Sends the message
	    */
		void SendMessageL();
		
    private: 
    	
		/**
		 * Inherited from CActive class 
		*/ 
    	virtual void DoCancel();

		/**
		 * Inherited from CActive class 
		*/ 
        virtual void RunL();

		/**
		 * Internal function 
		*/ 
		void InitializeL();

		/**
		 * Internal function 
		*/ 
		void ValidateL();

		/**
		 * Internal function 
		*/ 
		void SendL();

		/**
		 * Activates the request and call SetActive() function
		*/ 
		void ActivateRequest(TInt aReason);

		/**
		 * Gives the result for notification request.
		*/ 
		void NotifyRequestResult(TInt aReason);
	
		/**
		 * Sets the subject for message
		*/ 
     	void AddSubjectL();
     	
		/**
		 * Sets the recipient address
		*/ 
		void AddRecipientL();
		
		/**
		 * Sets body text to message
		*/ 
		void AddBodyTextL();
		
		/**
		 * Adds attachments to message
		*/ 
		void AddAttachmentL();
       
	private:

		/**
		 * Represents a channel of communication between a client thread 
		 * and the Message Server thread
		*/ 
		CMsvSession& 			iServerSession;

		/**
		 * Asynchronous request observer, Used to get infromed of completion or request
		*/ 
		MAsyncRequestObserver* 	iAsyncRequestObserver;

		/**
		 * Represents a session with the SendAs Server
		*/ 
		RSendAs					iSendAs;

		/**
		 * RSendAsMessage class object which encapsulates creating and
		 * sending a message.
		*/ 
		RSendAsMessage			iMessage;

		/**
		 * State of message
		*/ 
		TMessageState			iMessageState;

		/**
		 * A callback notification for asynchronous function
		*/ 
		CMsgCallbackBase* 		iNotifyCallback;
		
		/**
		 * Message input parameters
		*/ 
		CSendMessageParams* 	iMessageParam;

		/**
		 * Message detail for template message id
		*/ 
       	CMessageDetailInfo*		iTemplateDetail;
       	
       	/**
       	 * Flag which specifies to cancel the request 
       	 * but not to call the NotifyResultL
       	 * If false doesnot call the NotifyResultL
       	**/
       	TBool iCallNotifyForCancelFlag;
       	
       	/*
       	 * Flag information specifying whether the body text file 
       	 * in case of MMS is created or not, if created need to be 
       	 * cleaned up checking this flag at the end
       	*/
       	TBool iBodyTextFileFlag;
       	
       	/*
       	 * FileName of the Body Text file used in case of MMS
       	*/
       	TFileName iBodyTextFileName;
	};




#endif __SENDMESSAGE_H