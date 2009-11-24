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
* Description:  Defination of class CMessagingInterface
*
*/


#ifndef __MESSAGINGINTERFACE_H
#define __MESSAGINGINTERFACE_H

#include <liwcommon.h>
#include <liwserviceifbase.h>
#include <liwbufferextension.h>

#include "messageheader.h" 

class CMessagingService;
class TInputValidator;
/**
 * This class provides the Messaging SAPI interface to LIW Framework 
*/
class CMessagingInterface : public CBase, public MLiwInterface
	{
	public:

	    /**
	     * Two-phased constructor.
	     * @return CMessagingInterface* 
	    */
		static CMessagingInterface* NewL();

	    /**
	    * Destructor.
	    */
		virtual ~CMessagingInterface();

	private:

		/**
	     * Constructor
	    */
		CMessagingInterface();

		/**
	     * Symbian Constructor
	    */
		void ConstructL();
		
		/*
		 * Function which checks the type of the source and leaves upon  
		 * setting the error message accordingly if the aLeaveFlag is set and
		 * returns ETrue in case of success, EFalse in case of failure and not leaving
		 *
		 * @param aSource
		 * @param aLeaveFlag
		 * @param aExpectedType
		 * @param aCmdName Command Name
	     * @param aParameter Parameter Name
	     * @param aMessage Error message
		 *
		 * @return TBool
		 */
		TBool CMessagingInterface::CheckInputTypeL( const TLiwVariant* aSource, 
                                            TBool aLeaveFlag, 
                                            LIW::TVariantTypeId aExpectedtype, 
                                            const TDesC8& aCmdName, 
											const TDesC8& aParameter,
											const TDesC& aMessage );
	
		
	    /**
	     * Appends error message
	     * @param aCmdName Command Name
	     * @param aParameter Parameter Name
	     * @param aMessage Error message
		 * @param aMissingOrIncorrectOrNone 0 for none or 1 for missing or 2 for incorrect
		 * For missing it leave with errorcode SErrMissingArgument
		 * For incorrect it leaves with errorcode KErrArgument
		 * For none it wont leave
		 *
	     * @return void
	    */
		void AppendErrorMessageL( const TDesC8& aCmdName, 
								  const TDesC8& aParameter, 
								  const TDesC& aMessage,
								  TInt aNoneOrMissingOrIncorrect );
			
			
		/**
	     * Function called from sync APIs to check whether Async set up is done 
	     * if yes then leaves
	     * 
	     * @param aCmdOptions Command option
	     * @param aCallback Callback object pointer
	     * @param aCmdName Command Name
	     * @param aMessage Error message
		 *
	     * @return void
	    */						  
		void LeaveIfAsynchronousL( TUint aCmdOptions,
	 				          	   MLiwNotifyCallback* aCallback,
					          	   const TDesC8& aCmdName,  
								   const TDesC& aMessage );								  
								
												
	// MLiwInterface member functions
	public:

		/**
	     * Executes the SAPI as per params
	     * @param aCmdName Command name defining which operation is to be performed
	     * @param aInParamList  Input param list
	     * @param aOutParamList Output list
	     * @param aCmdOptions Command option
	     * @param aCallback Callback object pointer
	    */
		virtual void ExecuteCmdL( const TDesC8& aCmdName,
		                       const CLiwGenericParamList& aInParamList,
		                       CLiwGenericParamList& aOutParamList,
		                       TUint aCmdOptions = 0,
		                       MLiwNotifyCallback* aCallback = 0 );
		
		/**
	     * Closes the interface 
	    */
		virtual void Close();
		
	private:
	
		/**
	     * Issues SendMessage request to Messaging Service
	     * @param aInParamList  Input param list
	     * @param aOutParamList Output list
	     * @param aCmdOptions Command option
	     * @param aCallback Callback object pointer
	    */
		void SendMessageL( const CLiwGenericParamList& aInParamList,
					                       CLiwGenericParamList& aOutParamList,
					                       TUint aCmdOptions,
					                       MLiwNotifyCallback* aCallback );
					                       
		/**
	     * Cancels the async operation issued earlier
	     * @param aCmdName Command name i.e.., Cancel
	     * @param aInParamList  Input param list
	     * @param aOutParamList Output list
	     * @param aCmdOptions Command option
	    */			                       
		void CancelAsyncL( const TDesC8& aCmdName,
										const CLiwGenericParamList& aInParamList,
				                       	CLiwGenericParamList& aOutParamList,
				                       	TUint aCmdOptions);			                       
		/**
	     * Issues GetList request to Messaging Service
	     * @param aInParamList  Input param list
	     * @param aOutParamList Output list
	     * @param aCmdOptions Command option
	     * @param aCallback Callback object pointer
	    */
		void GetHeaderListL( const CLiwGenericParamList& aInParamList,
					                       CLiwGenericParamList& aOutParamList,
					                       TUint aCmdOptions,
					                       MLiwNotifyCallback* aCallback );

		/**
	     * Issues New Message notification request to Messaging Service
	     * @param aInParamList  Input param list
	     * @param aOutParamList Output list
	     * @param aCmdOptions Command option
	     * @param aCallback Callback object pointer
	    */
		void RequestNotificationL( const CLiwGenericParamList& aInParamList,
					                       CLiwGenericParamList& aOutParamList,
					                       TUint aCmdOptions,
					                       MLiwNotifyCallback* aCallback );

		/**
	     * Cancels New Message notification Messaging Service
	     * @param aInParamList  Input param list
	     * @param aOutParamList Output list
	     * @param aCmdOptions Command option
	     * @param aCallback Callback object pointer
	    */
		void CancelNotificationL( const CLiwGenericParamList& aInParamList,
					                       CLiwGenericParamList& aOutParamList,
					                       TUint aCmdOptions,
					                       MLiwNotifyCallback* aCallback );

		/**
	     * Issues request for Deleteing Message to Messaging Service
	     * @param aInParamList  Input param list
	     * @param aOutParamList Output list
	     * @param aCmdOptions Command option
	     * @param aCallback Callback object pointer
	    */
		void DeleteMessageL( const CLiwGenericParamList& aInParamList,
					                       CLiwGenericParamList& aOutParamList,
					                       TUint aCmdOptions,
					                       MLiwNotifyCallback* aCallback );

		/**
	     * Issues request for Changing message status to Messaging Service
	     * @param aInParamList  Input param list
	     * @param aOutParamList Output list
	     * @param aCmdOptions Command option
	     * @param aCallback Callback object pointer
	    */
		void ChangeStatusL( const CLiwGenericParamList& aInParamList,
					                       CLiwGenericParamList& aOutParamList,
					                       TUint aCmdOptions,
					                       MLiwNotifyCallback* aCallback );

		/**
	     * Gets the param list for sending message form the inputparam list
	     * @param aInParamList A CLiwGenericParamList containing required input params
	     * @return TSendMessageParams* A send message params structure
	    */
		CSendMessageParams* GetSendParametersL( const CLiwGenericParamList& aInParamList );

  	  /**
	     * Gets the filter parameters, sorting option from the inputparam list
	     * @param aInParamList A CLiwGenericParamList containing required input parameters
	     * @return CFilterParamInfo* Filter parameter structure
	    */
		CFilterParamInfo* GetFilterParametersL( const CLiwGenericParamList& aInParamList, TBool aIndexBaseInp );

  	  /**
	     * Gets the message id from liw input parameter 
	     * @param aInParamList input param list
	     * @param aMessageId Output parameter containing message id
	     * @return TInt Error code
	    */
		void GetMessageIdL( const CLiwGenericParamList& aInParamList, TMsvId& aMessageId,
							const TDesC8& aCmdName  );

  	  /**
	     * Gets the transaction id from liw input parameter 
	     * @param aInParamList input param list
	     * @param aTransactionId Output param containing transaction id
	     * @return TInt Error code
	    */
		void GetTransactionIdL( const CLiwGenericParamList& aInParamList, 
								TInt32& aTransactionId,
								const TDesC8& aCmdName  );

  	  /**
	     * Gets the status flag and its value
	     * @param aInParamList input param list
	     * @param aStatusFlag Status flag
	     * @param aFlagValue Flag value
	     * @return TInt Error code
	    */
		void GetStatusFlagAndValueL( const CLiwGenericParamList&  aInParamList, 
									 TMessageStatusFlag& aStatusFlag, 
									 TBool& aFlagValue,
							  	     const TDesC8& aCmdName );

  	  /**
	     * Gets the notification type
	     * @param aInParamList input param list
	     * @param aNotificationType Notification type
	     * @return void
	    */													
		void GetNotificationTypeL( const CLiwGenericParamList& aInParamList, 
								   TNotificationType& aNotificationType,
								   const TDesC8& aCmdName );

  	  /**
	     * Gives the sort type
	     * @param aSortField Sort Field as input string
	     * @param aSortOrder Sort type as input string
	     * @return TMsvSorting Sort type
	    */		
		TMsvSorting SortType( const TDesC& aSortField, const TDesC& aSortOrder );
	

	private:
		
	  	/**
	     * CMessagingService  class pointer
	    */		
		CMessagingService* iMsgService;
		
		/**
	     * iErrorString  Heap Descriptor used to store the error message 
	     * in case of error, initially set to NULL
	    */
		HBufC* iErrorMessage;
	};

/**
 * Callback class for asynchronous SAPI whose result is Integer
*/		
class CMsgCallbackInt : public CMsgCallbackBase
	{
	private:

	  	/**
	     * Constructor
	    */		
		CMsgCallbackInt();

	public:

	  	/**
	     * Two-phase Constructor
	     * @return   CMsgCallbackBase* 
	    */		
		static CMsgCallbackBase* NewL();

	  	/**
	     * Gives the result of asynchronous SAPI
	     * @param aErrCode errcode
	     * @param aResult Result
	    */		
		void NotifyResultL(TInt aErrCode, TAny* aResult);
		
		/**
	     * Gives the result of asynchronous SAPI
	     * @param aErrCode errcode
	     * @param aEntrySelection  Entryselection
		 * @param aFilter  Filter
	    */
		
		void HandleGetlistL (TInt aErrCode, CMsvEntrySelection* aEntrySelection, CFilterParamInfo* aFilter);
		
		 
	};

/**
 * Callback class for asynchronous SAPI message header
*/	
class CMsgCallbackHeader : public CMsgCallbackBase
	{
	public:
		
	  	/**
	     * Two-phase Constructor
	     * @return   CMsgCallbackHeader* 
	    */		
		static CMsgCallbackHeader* NewL(CMessagingService* aMsgService);
		
	  	/**
	     * Destructor
	    */		
		virtual ~CMsgCallbackHeader();
		
	private:
	
	  	/**
	     * Constructor
	    */		
 		CMsgCallbackHeader(CMessagingService* aMsgService);
 		
	public:
	
	  	/**
	     * Gives the result of asynchronous SAPI
	     * @param aErrCode errcode
	     * @param aResult Result
	    */
		virtual void NotifyResultL(TInt aErrCode, TAny* aResult);
		 
		 /**
	     * Gives the result of asynchronous SAPI
	     * @param aErrCode errcode
	     * @param aEntrySelection  Entryselection
		 * @param aFilter  Filter
	    */
		 
		 virtual void HandleGetlistL (TInt aErrCode, CMsvEntrySelection* aEntrySelection, CFilterParamInfo* aFilter);
		 
	private:
	    
	     /**
	     * CMessagingService  class pointer
	    */
	    CMessagingService* iMsg;
	};

/**
* Implemenation of abstract interface to iterate over the collection of message IDs.
*
* @see CLiwIterable
*
*/
class CIterableIdList : public CLiwIterable	
	{
	public:
	  	/**
	     * Two-phase Constructor
	     * @param aList list to be iterated 
	     * @return new CIterableIdList object
	    */	
		static CIterableIdList* NewL(CMsvEntrySelection* aList, 
											CMessagingService* aMsgService, 
											CFilterParamInfo* aFilter );

		/**
		* Resets the iterator. 
		*
		*/
		void Reset();

		/**
		* Iterates over the collection entries to fetch the next data element.
		*
		* @param aEntry contains the next data element and its corresponding data type
		*
		* @return false if there are no more data elements to be fetched;
		* true otherwise
		* 
		*/
		TBool NextL(TLiwVariant&);
		
	    /**
	    * Destructor.
	    */
		~CIterableIdList();

	private:
	
	    /**
	    * Constructor
	     * @param aList list to be iterated 
	     * @return void
	    */
		CIterableIdList(CMsvEntrySelection* aList, 
											CMessagingService* aMsgService, 
											CFilterParamInfo* aFilter );


	private:
	
	  	/**
	     * CMsvEntrySelection  class pointer
	    */		
		CMsvEntrySelection* 	iList;

	  	/**
	     * CMessagingService  class pointer
	    */		
		CMessagingService* 		iMsgService;
		
	  	/**
	     * CFilterParamInfo  class pointer
	    */		
		CFilterParamInfo*		iFilter; 

	  	/**
	     * Index on list
	    */		
		TInt					iIndex;	
	};

/**
* An associative array or dictionary class. The collection
* key entries are of type string (Descriptor type) and their  
* associated values can be an variant type.
* 
*  \c CLiwDefaultMap provides default map implementation to
   *  <ul>
   *     <li>insert a key-value pair</li>
   *     <li>find a stored value based on a key</li>
   *     <li>get a key based on an index</li>
   *     <li>remove a key-value pair based on a key</li>
   *		 <li>get the total number of stored key-value pairs</li>
   *   </ul>
* 
*
* @see CLiwContainer
* @see TLiwVariant
* @see CLiwMap
*
*/
class CLiwMessagingMap : public CLiwMap
{
 public:
  
  /*
   * Creates an instance of \c CLiwMessagingMap
   *
   * @return an instance of \c CLiwMessagingMap
   */
   static CLiwMessagingMap* NewL( CMessagingService* aMsgService );
  
 
  /**
    * Inserts a key-value pair element to the map collection. If
    * the specified key already exists, it will be removed from
    * the collection and the new key-value pair will be added to the
    * map.
    *  
    * @param aKey the key to be stored
    * @param aValue the value associated with the key to be stored
    */
  void InsertL(const TDesC8& aKey, const TLiwVariant& aValue);
  
  /**
    * Finds a value stored in the map collection based on the key.
    *  
    * @param aKey the key to be searched
    * @param aFndValue the value associated with the found key
    *
    * @return false if there is no key stored; true otherwise
   */
  TBool FindL(const TDesC8& aKey, TLiwVariant& aValue) const;
  
  /**
    * Returns the number of key-value pair stored in the map collection.
    *  
    * @return the number of key-value pair stored in the map collection
   */
  TInt Count() const;
  
  /**
    * Returns the key stored at a specified index. 
    *  
    * @param aIndex the index of the key to be found
    * @param aFndKey the key found at the passed index
    *
    * @return true if a key-value entry is found at the passed index;
    * false otherwise
   */
  TBool AtL(TInt aIndex, TDes8& aFndKey) const;
  
  /**
    * Removes a key from the map collection.
    *  
    * @param aKey the key to be removed from the map
   */
  void Remove(const TDesC8& aKey);
  
 private:
 
 	/*
 	 * Constructor
 	 */
  CLiwMessagingMap(CLiwGenericParamList* aMap, CMessagingService* aMsgService) 
  : iMap(aMap), iMsgService(aMsgService)
  	 {}
  
	/*
	* Destructor
	*/
	virtual ~CLiwMessagingMap();
  
	/*
	* the underlying generic parameter list
	*/
	CLiwGenericParamList* iMap;
  
  	/**
     * CMessagingService  class pointer
    */		
	CMessagingService* iMsgService;
		
};

class CMsgFileBuffer : public CLiwFileBuffer
	{
	public:
	  	/**
	     * Two-phase Constructor
	     * @param aFile file handle
	     * @return new CMsgFileBuffer object
	    */	
		static CMsgFileBuffer* NewL(RFile& aFile);

	    /**
	    * Destructor.
	    */
		~CMsgFileBuffer();

		/*
		 * @return RFile handle
		 */
		RFile& AsFile();

		/*
		 * Returns the pointer to the underlying buffer
		 *
		 * @return the pointer to the underlying buffer
		 */
		TUint8* Buf() const;
		
		/*
		 * Returns the length of the buffer data
		 *
		 * @return the length of the buffer data
		 */
		TInt Len();
		
		/*
		 * Reads the specified number of bytes of buffer data 
		 * 
		 * @param aPtr the pointer to the area into which buffer data is read
		 * @param aLength the number of bytes to be read from the buffer
		 *
		 * @return KErrNone if the operation is successful; Otherwise
		 *		   TLiwBufferAccess::KLiwBufferNonReadable
		 *        
		 */
		TInt Read(TUint8* aPtr,TInt aLength);
		
		/*
		 * Writes the specified number of bytes into the buffer 
		 * 
		 * @param aPtr the pointer to the data to be written into buffer
		 * @param aLength the number of bytes to be written into buffer
		 *
		 * @return KErrNone if the operation is successful; Otherwise
		 *		   TLiwBufferAccess::KLiwBufferReadOnly if writing is not supported
		 *        
		 */
		TInt Write(const TUint8 aPtr, TInt aLength);
			
		/*
		 * Releases the buffer. The service provider implementing concrete buffer
		 * type should provide appropriate implementation
		 */
		void Release();
		
		/*
		 * Returns the appropriate type of buffer.
		 */
		TInt TypeID();
		
		/*
		 * The concrete implementation of buffer types should perform equality operation
		 * check
		 */
		virtual TBool operator==(CLiwBuffer& aBuffer);

	private:
		CMsgFileBuffer(RFile& aFile);
		
	private:
		RFile iFile;
	};

	
/**
 * Input Validator Class used internally to check Inputs
 */		
 class TInputValidator
 	{
 	public: 
 		TInputValidator();
		
		/*
		 * Check whether aTime is valid or not
		 */
 		TBool CheckValidDate( const TTime &aTime );
 		
 		/*
		 * Check whether aDes contains valid number or not
		 */
 		TBool CheckValidNumber( const TDesC &aDes );
 		
 		/*
		 * Check whether aFileName is a valid file or not
		 */
 		TBool CheckValidFile( const TDesC &aFileName );
 		
 		/*
		 * Check whether aDesc is a valid phone number
		 */
 		TBool CheckValidNumberWithPlus( const TDesC &aDes );
 		
 		/*
		 * Check whether aDesc size is not zero
		 */
 		TBool CheckDesSize( const TDesC &aDes );
 	};	

#endif __MESSAGINGINTERFACE_H