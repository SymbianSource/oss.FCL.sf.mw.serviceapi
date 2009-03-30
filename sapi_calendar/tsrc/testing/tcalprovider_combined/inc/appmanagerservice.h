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
* Description:   This Class provides the core functionality to Application Manager
*				 SAPI
*
*/




#ifndef __APPMANAGERSERVICE_H
#define __APPMANAGERSERVICE_H


#include <apgcli.h>

#include "appobserver.h"
#include "appmanagercommon.h"


class CLauncherObserver;
class CLauncher;
class CAsynchRequestManager;
 
/**
* This Class provides the core functionality of
* Application Manager SAPI
*
* @since  Series60 v3.2
*/
class CAppManagerService : public CBase
    {

    public:

    	/**
        * Returns the instance of CAppManagerService.
        * @since  Series60 v3.2
        * @param  void
        * @return CAppManagerService* return the instance of CAppManagerService class
        */
        IMPORT_C static CAppManagerService* NewL();

        /**
    	* Destructor.
    	*/
        virtual ~CAppManagerService();

     	/**
        * This function Launch the given Application
        * @since  Series60 v3.2
        * @param  aAppId String to identify the application 
        * @param  aCmdLine command line argument to send to launching application
        * @param  aOptions specify the various attribut of application e.g its launching mode,document and postion
        * @param  aObserver callback for getting the notifaction when the launched application dies        
        */
       	IMPORT_C void LaunchApplicationL( const TDesC& aAppId,
                                          const TDesC8& aCmdLine,
                                          const TOptions& aOptions,
                                          MAppObserver* aObserver = NULL,
                                          TInt32 aTransactionID = 0  );

       	/**
        * This function Launch the given content
        * succeed.
        * @since  Series60 v3.2
        * @param  aCriteria structure for identifying the application(it can contain Handle or Path of the doc) 
        * @param  aMimeType MimeType of Document
        * @param  aOptions specify the various attribute of application e.g its launching mode
        * @param  aFileName Filled by the api if creates the new document
        * @param  aObserver callback for getting the notifaction when the launched application dies.
        * @return void        
        */
       	IMPORT_C void LaunchDocumentL( TDocument& aCriteria,
       	                               const TDesC8& aMimeType,
       	                               const TOptions& aOptions ,
       	                               TDesC& aFileName,
       	                               MAppObserver* aObserver = NULL,
       	                               TInt32 aTransactionID = 0 );

         /**
        * This function gives the list of all application or installed packages
        * as per content type and filter parameter.
        * @since  Series60 v3.2
        * @param  aContent      It contains the Content type.
        * @param  aFilterParam  Filter parameter for finding the handler application
        * @return MIterator     Iterator interface provided by dll 
        */
		IMPORT_C void  GetListL( MIterator*& aIterator, 
		                         const TDesC& aContent, 
		                         const CFilterParam*  aFilterParam =NULL  );




        /**
        * Cancel the pending asynchronous request
        * @since  Series60 v3.2
        * @param  aTransactionID  Unique number to identify the request
        * @return TInt System wide error code 
        */
        IMPORT_C TInt Cancel( TInt32 aTransactionID );



           



   	private:


   		/**
        * Two-phased constructor
        * @since  Series60 v3.2
        * @param  void
        * @return void
        */
        void ConstructL();


    private:
        /**
        * session for application architecture
        */
        RApaLsSession iApaLsSession;

        /**
        * instance of class which handles all launching request
        */
        CLauncher* iLauncher;


        /**
        * instance of class which handles Trans ID of all Asynch request
        */
        CAsynchRequestManager* iAsynchReqMngr;
        
        
     
    
      };

#endif __APPMANAGERSERVICE_H