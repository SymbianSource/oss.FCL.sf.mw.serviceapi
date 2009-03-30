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
* Description:  This Class is observer for the CLF framework
*
*/


#ifndef __MGCLFOPERATIONOBSERVER_H
#define __MGCLFOPERATIONOBSERVER_H


#include <mclfoperationobserver.h>
#include <e32base.h>

class MCLFItemListModel;
class MMgOperationObserver;
class CMgService;


// CLASS DECLARATION

/**
*  CClfOperationObserver class is for observing operation events of CLF
*  Client application gets notified when asynchronous operations
*  are completed.
*
*  @since  Series60 v3.2
*/
NONSHARABLE_CLASS( CClfOperationObserver ) : public CBase, public MCLFOperationObserver
    {
    public:

		/**
 		* Two-phased constructor
        * @since  Series60 v3.2
        * @param  void
        * @return CClfOperationObserver*  Returns the instance of
        *								  CClfOperationObserver.
        */
 
  		static CClfOperationObserver* NewL();

        /**
        * method to get CLF Framework events. This method is
        * called when an event is received.
        * @param aOperationEvent Operation event code of the event
        * @param aError System wide error code if the operation did not
        *        succeed.
        */
        virtual void HandleOperationEventL( TCLFOperationEvent aOperationEvent,
                                            TInt aError );

      	/**
        * Destructor.
        */
        virtual ~CClfOperationObserver();

       	/**
        * constructor
        * @since  Series60 v3.2
        * @param void
        * @return void
        */
        CClfOperationObserver();


        /**
        * method to set callback of service class(i.e ServiceObserver)
        * @since  Series60 v3.2
        * @param  aServiceObserver observer of the service class
        * @param  aListModel Iterator of clf which contains the required result
        * @param  aMGService Instance of service class
        */
        void SetMemberVar(TUint  aTransactionID,
                          MMgOperationObserver* aServiceObserver,
        				  MCLFItemListModel* aListModel,
        				  CMgService* aMGService);

        /**
        * Cancel the pending asynchronous request
        * @since  Series60 v3.2
        * @param  void
        * @return void
        */
        void CancelL();




   	private:

        /**
     	* Store the instance of the callback of service class
     	*/
  		MMgOperationObserver* iServiceObserver;

  		/**
     	* stores the instance of list model of CLF Framework.
     	*/
    	MCLFItemListModel* iListModel;

    	/**
     	* stores the instance of service class
     	*/
    	CMgService* iMGService;
    	/**
     	* stores the TransactionID
     	*/
    	TUint  iTransactionID;
	};

#endif __MGCLFOPERATIONOBSERVER_H