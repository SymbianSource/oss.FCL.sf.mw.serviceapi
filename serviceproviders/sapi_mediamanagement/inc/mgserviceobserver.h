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
* Description:  This class is the observer of CMgService class
*
*/


#ifndef MGSERVICEOBSERVER_H
#define MGSERVICEOBSERVER_H

#include "mgservice.hrh"
#include "mgoperationobserver.h"

class CLiwGenericParamList;
class MCLFItemListModel;
class CClfOperationObserver;




// CLASS DECLARATION
/**
*  Service Observer is for observing operation events of the MG service class.
*  CMgServiceObserver gets notified when asynchronous operations
*  are completed. 
* 
*  
*  @since  Series60 v3.2
*/


NONSHARABLE_CLASS( CMgServiceObserver ): public CBase, public MMgOperationObserver
    {
    public: 
    
    
    	/**
        * Returns the instance of CMgServiceObserver.
        * @since  Series60 v3.2
        * @param void
        * @return void
        */	
 
  		static CMgServiceObserver* NewL();
  		
  		/**
        * Destructor.
        */
        virtual ~CMgServiceObserver();
        

        /**
        * Abstract method to get CMgService class events. This method is
        * called when an event is received.
        * @since  Series60 v3.2
        * @param aListModel ClF Iterator contains the required result 
        * @param aOperationEvent specifies the asynchronous event
        * @param aError System wide error code if the operation did not
        *        succeed.
        */
        virtual void MgNotifyL(TUint  aTransactionID, 
                               MCLFItemListModel* aListModel,
                               CClfOperationObserver* aOperationObserver,
        					   TMgOperationEvent& aOperationEvent , 
                               const TInt& aError );

                
        
        /**
        * method to set callback of consumer and pointer to 
        * input/output parameter list.
        * @since  Series60 v3.2
        * @param  iCmdId  It represents whether the command if of request (FileInfo/File)
        * @param  iInput  sent by the consumer at the time of request	
        * @param  iOutput Result of given command will be 
        *				  stored in given output parameter list
        * @param  aCallback Contains the call back for Asynchronous request	
        */
        void SetMemberVar( const TMgCmdId& aCmdId,
        				   const CLiwGenericParamList* aInput,
        				   MLiwNotifyCallback* aCallBack );
        				   
          /**
        * Cancel the pending asynchronous request
        * @since  Series60 v3.2
        * @param  void
        * @return void
        */
        void CancelL();				   
        
    private :
        
         /**
        * Constructor.
        */
        CMgServiceObserver();
        
        /**
        * Two-phased constructor
        * @since  Series60 v3.2
        * @param  void
        * @return void
        */
        void ConstructL();
        
        
     private:
        
        /**
     	* Store the instance of the callback of the Client
     	*/
  		MLiwNotifyCallback* 			iCallBack;
  		
  		/**
     	* stores the pointer of aOutParamList 
     	*/
    	CLiwGenericParamList* 			iOutput; 
    	
    	/**
     	* stores the pointer of aInParamList 
     	*/
    	const CLiwGenericParamList* 	iInput;
    	 
    	/**
     	* command ID of ongoing request (Files/FilesInfo)
     	*/
    	TMgCmdId 						iCmdId;
    
   
	};

#endif MGSERVICEOBSERVER_H