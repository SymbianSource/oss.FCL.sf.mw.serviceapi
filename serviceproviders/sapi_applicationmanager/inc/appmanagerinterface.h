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
*				 calling the functionality to Application Manager SAPI. 	
*
*/



#ifndef __CAPPMANAGERINTERFACE_H
#define __CAPPMANAGERINTERFACE_H



class CAppManagerService;
class CAppManagerServiceObserver;

#include <liwvariant.h>
// CLASS DECLARATION



/**
*  Interface class for Application Manager SAPI.
*
*  @code
*   MLiwInterface* Interface = CAppManagerInterface::NewL();
*	Interface->ExecuteCmdL(KGetList,input,output,KLiwOptSyncronous);
*  @endcode
*  
*  
*  @since  Series60 v3.2
*/

class CAppManagerInterface : public CBase, public MLiwInterface 
    {
    public:
 		/**
 		* Two-phased constructor
        * @since  Series60 v3.2
        * @param  void
        * @return CAppManagerInterface*  Returns the instance of 
        *								   CAppManagerInterface.
        */	
   		static CAppManagerInterface* NewL();
  		
  		/**
    	* Destructor.
    	*/	
  		virtual ~CAppManagerInterface();
  		
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
  		CAppManagerInterface();
  		
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
  		void GetListL( const CLiwGenericParamList& aInParamList , 
  		                    CLiwGenericParamList& aOutParamList );
  		
  			/**
        * This function will send the request to SAPI core class
        * @since  Series60 v3.2
        * @param void
        * @return void
        */
  		void LaunchAppL( const CLiwGenericParamList& aInParamList , 
  		                      CLiwGenericParamList& aOutParamList , 
  		                      MLiwNotifyCallback* aCallBack = NULL,
  		                      TInt32 aTransactionID = 0 );
  			/**
        * This function will send the request to SAPI core class
        * @since  Series60 v3.2
        * @param void
        * @return void
        */
  		void LaunchDocL( const CLiwGenericParamList& aInParamList, 
  		                      CLiwGenericParamList& aOutParamList, 
  		                      MLiwNotifyCallback* aCallBack = NULL,
  		                      TInt32 aTransactionID = 0 );
  		
  		
    private:  		
  		/**
     	* Stores the instance of SAPI Core Class
     	*/
  		CAppManagerService *iCoreClass;
  		
  	  
};

#endif __CAPPMANAGERINTERFACE_H