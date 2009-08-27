/*
* Copyright (c) 2007-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  This Class provides the interface for 
*				 calling the functionality to Media Management SAPI. 	
*
*/



#ifndef __CMgInterface_H
#define __CMgInterface_H



class CMgService;
class CMgServiceObserver;

const TInt KMaxErrorMessageLength = 100;
// CLASS DECLARATION



/**
*  Interface class for Media Management SAPI.
*
*  @code
*   MLiwInterface* Interface = CMgInterface::NewL();
*	Interface->ExecuteCmdL(KGetList,input,output,KLiwOptASyncronous,CallBack);
*  @endcode
*  
*  
*  @since  Series60 v3.2
*/

class CMgInterface : public CBase, public MLiwInterface 
    {
    public:
 		/**
 		* Two-phased constructor
        * @since  Series60 v3.2
        * @param  void
        * @return CMgInterface*  Returns the instance of 
        *								   CMgInterface.
        */	
   		static CMgInterface* NewL();
  		
  		/**
    	* Destructor.
    	*/	
  		virtual ~CMgInterface();
  		
  		/**
        * This function handles the request of consumer 
        * @since  Series60 v3.2
        * @param  aCmdName 		Command name of SAPI
        * @param  aInParamList 	Contains argument on which operation has to 
                                be performed
        * @param  aOutParamList	Result of given command will be 
        *						stored in the output paramater list
        * @param  aCmdOptions	Set option for asyncronous request or 
        *						for canceling the asyncronous request
        * @param  aCallback		Contains the callback for Asynchronous request	
        */
  		
  		 virtual void ExecuteCmdL(const TDesC8& aCmdName,
                           const CLiwGenericParamList& aInParamList,
                           CLiwGenericParamList& aOutParamList,
                           TUint aCmdOptions = 0,
                           MLiwNotifyCallback* aCallback = 0);
         
               
        /**
        * This function will release all the internal resources
        * @since  Series60 v3.2
        * @param void 
        * @return void
        */                  
        virtual void Close() {delete this;}
        
        /**
        * This function will convert Symbian error codes to 
        * SAPI specific error codes
        * @since  Series60 v3.2
        * @param aSymbianErr Symbian error code to be converted to SAPI specific
        * error code
        * @return An integer error code
        */
  		static TInt SapiError( TInt aSymbianErr );

    private:
  		
  		/**
        * constructor
        * @since  Series60 v3.2
        * @param void
        * @return void
        */
  		CMgInterface();
  		
   		/**
        * Two-phased constructor
        * @since  Series60 v3.2
        * @param void
        * @return void
        */
  		void ConstructL();
  		/**
        * This function will send the request to SAPI core class
        * @since  Series60 v3.2
        * @param void
        * @return void
        */
  		void SendRequestL(const CLiwGenericParamList& aInParamList, TUint aTransactionID ,TBool aPostionBasedSearching,MLiwNotifyCallback* aCallBack );
  		  												
		/**
	     * Appends error message
	     * @param aCmdName Command Name
	     * @param aParameter Parameter Name
	     * @param aMessage Error message
		 *
	     * @return void
	    */
		void AppendErrorMessageL( const TDesC8& aCmdName, 
												const TDesC8& aParameter, 
												const TDesC& aMessage );
  		

    /**
    * This function will send the request to SAPI core class
    * @since  Series60 v3.2
    * @param void
    * @return void
    */
    void GetThumbnailL( const CLiwGenericParamList& aInParamList, 
                          CLiwGenericParamList& aOutParamList, 
                          MLiwNotifyCallback* aCallBack = NULL,
                          TInt32 aTransactionID = 0 );
    		
		
    private:  		
  		/**
     	* Stores the instance of SAPI Core Class
     	*/
  		CMgService *iCoreClass;
  		
  		/**
     	* Stores the instance of Service observer Class
     	*/
  	//	CMgServiceObserver *iServiceObserver;
  	    
  	    /**
        * Error Message object
        * @internal
	    */		
		HBufC* iErrorMessage;
  		
  
};

#endif __CMgInterface_H