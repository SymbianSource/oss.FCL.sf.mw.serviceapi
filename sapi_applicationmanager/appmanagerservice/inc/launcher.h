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
* Description:  This Class provides the functionality to launch the application
*
*/



#ifndef __LAUNCHER_H
#define __LAUNCHER_H

class TOptions;
class RApaLsSession;
class CLauncherObserver;
class TDocument;


/**
* This Class provides the core functionality of launching 
* the application
*
* @since  Series60 v3.2
*/
class CLauncher : public CBase
    {

    public:

    	 /**
        * Returns the instance of CLauncher.
        * @since  Series60 v3.2
        * @param  aSession AppArch server session.
        * @return CLauncher* return the instance of CLauncher class
        */
        static CLauncher* NewL( RApaLsSession& aSession );

            
     	/**
        * This function Launch the Given Application
        * succeed.
        * @since  Series60 v3.2
        * @param  aAppId   UID of the application to be launch
        * @param  aCmdLine Commandline Argument
        * @param  aOptions mode for laucnhing the appilcation(standalone/chained)
        * @param  aObserver observer for informing when the launched application dies
        */
       	
        TThreadId LaunchApplicationL( const TDesC& aAppId, 
                                       const TDesC8& aCmdLine, 
                                       const TOptions& aOptions );
       	
       	/**
        * This function Launch the Given Document
        * succeed.
        * @since  Series60 v3.2
        * @param  aCriteria Document to be launch 
        * @param  aMimeType MimeType of application to be launch 
        * @param  aProperties postion and mode for laucnhing the appilcation(standalone/chained)
        * @param  aObserver observer for informing when the launched application dies
        */
       	TThreadId LaunchDocumentL( TDocument& aCriteria, 
       	                            const TDesC8& aMimeType, 
       	                            const TOptions& aProperties , 
       	                            TDesC& aFileName );

        
        /**
        * Destructor
        * @since  Series60 v3.2
        * @param void
        * @return void
        */
        ~CLauncher(); 
        
   	private:

        /**
        * This function parse the application id string  and convert into TUid 
        * @since  Series60 v3.2
        * @param  aSource String to Parse
        * @param  aUid Returns the Uid from the given string
        */
        void ParseAppIdL( const TDesC& aSource ,TUid& aUid );
        
         /**
        * This function parse the application id string  and covert into TUid 
        * @since  Series60 v3.2
        * @param  aHexString String conating UID in HEX format
        * @param  aUid Returns the Uid from the given string 
        */
        TInt ConvertHexStringToInt32(const TDesC& aHexString,TInt32& aInt32 );
       	
       	 /**
        * This function will set the application to launch in chained mode 
        * @since  Series60 v3.2
        * @param  aCmdLine underlying structure in which chained mode has to set
        * @param  aAppUid Uid of the applications
        */
       	      	
       	void SetChainedModeL( CApaCommandLine* aCmdLine  , const TUid& aAppUid );
   	
   		/**
        * Constructor
        * @since  Series60 v3.2
        * @param void
        * @return void
        */
        CLauncher( RApaLsSession& aSession);
        
     


    private:
    
       /**
     	* Session of application architecture server
     	*/
      
        RApaLsSession& iApaLsSession;

      };

#endif __LAUNCHER_H