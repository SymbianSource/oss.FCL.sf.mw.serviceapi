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
* Description:   This Class is observer for the Launching Application
*
*/



#ifndef __LAUNCHEROBSERVER_H
#define __LAUNCHEROBSERVER_H

#include <e32base.h>
#include "appmanagercommon.h"

class CAsynchRequestManager;
class MAppObserver;


// CLASS DECLARATION

/**
*  CLauncherObserver class used is for observing events of launched
*  application, Launching application gets notified when launched application
*  dies.
*
*  @since  Series60 v3.2
*/
NONSHARABLE_CLASS( CLauncherObserver ) : public CActive
    {
    public:

		/**
 		* Two-phased constructor
        * @since  Series60 v3.2
        * @param  void
        * @return CLauncherObserver*  Returns the instance of
        *								  CLauncherObserver.
        */

  		static CLauncherObserver* NewL(  MAppObserver* aObserver ,TInt32& aTransactionID, CAsynchRequestManager* aAsynchRequestManager );


        /**
    	* Destructor.
    	*/
        virtual ~CLauncherObserver();
        
        /**
        * This function activate the asynch request
        * succeed.
        * @since  Series60 v3.2
        */
       	
        void ActivateRequestL( TThreadId& aThreadId );
       	
       	 
        /**
        * This function set the pointer of observer
        * succeed.
        * @since  Series60 v3.2
        */
       	
        void SetAppObserver ( MAppObserver* aAppObserver );
           	
        
    private:

         /**
        * This function activate the asynch request
        * succeed.
        * @since  Series60 v3.2
        */
       	
        void NotifyRequestResultL( TInt aReason , TAppOperationEvent& aOperationEvent );
        
        /**
		 * Inherited from CActive class 
		*/ 
    	virtual void DoCancel();

		/**
		* Inherited from CActive class 
		*/ 
        virtual void RunL();


   		/**
        * Constructor
        * @since  Series60 v3.2
        * @param  void
        * @return void
        */
        CLauncherObserver( MAppObserver* aObserver , TInt32& aTransactionID, CAsynchRequestManager* aAsynchRequestManager );

                
        /**
     	* main thread of launched application
     	*/
  
        RThread iAppThread;
        
        
        /**
     	* Application Observer
     	*/
  
        MAppObserver* iAppObserver ;
        
        /**
     	* Transaction ID
     	*/
        TInt32 iTransactionID;
        
        /**
     	* Application Observer
     	*/
        CAsynchRequestManager* iAsynchRequestManager;
	};

#endif __LAUNCHEROBSERVER_H