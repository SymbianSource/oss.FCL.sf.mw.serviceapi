/*
* Copyright (c) 2006-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:   Header file for logging SAPI core implementation.
*
*/


#ifndef C_LOGGINGCALLBACK_H
#define C_LOGGINGCALLBACK_H


/**
* Forward declarations 
*/
class MLoggingCallBack ;

/**
* CallBack fuction called by core dll loggingservice.lib on reciving
* Logging updates from log server
* Implements HandleNotifyL() from base class MLoggingCallBack
*
* @loggingservice.lib dependency
* @see MLoggingCallBack in loggingasyncservice.h for details.
*/
class LoggingInterfaceCB : public MLoggingCallback
    {
    public :

        /**
        * Construction method for call back class
        *
        * @param aCallBack: Callback object after reciving logging updates from core class
        * @param aInParamList: input paramater list for logging request 
        * @param aOutParamList: out put paramater list to be which will contained logging information
        * @param aModuleInfo module information of positioning module used
        */

        static LoggingInterfaceCB * NewL( MLiwNotifyCallback* aCallBack )  ;

        /**
        * Function to set call back object type , this is needed to 
        * for sending Event notifications to users(KLiwEventCompleted/KLiwEventInProgress) 
        * @aRequestType request type 
        */

        inline void SetRequestType( TInt aRequestType )
            {
            iRequestType = aRequestType ;
            }

        /**
        * Implementation of HandleNotifyL method, derived from MLoggingCB
        *
        * @param aTransid, Transaction id
        * @param aStaus ,  status of the async request
        * @iter, iterator for getlist results
        */

        void HandleNotifyL( TUint aTransid, TUint aStatus, CLogIter *aiter ) ;
		
        /**
        * Implementation of HandleRequestL method, derived from MLoggingCB
        *
        * @param aTransid, Transaction id
        * @param aStaus ,  status of the async request
        * @param, logData for notification
        */ 
        void HandleRequestL( TUint aTransid, TUint aStatus, CLogsEvent *event ) ;

        /**
        * Implementation of CancelNotifyL method, derived from MLoggingCB
        *
        * @param aTransid, Transaction id
        */
        
        void CancelNotifyL( TUint aTransid );
        
        /**
        * GetRequestType
        */
        inline TUint GetRequestType( void ) 
            {
            return iRequestType ;
            }
       
        /**
        * destructor 
        */
        virtual ~LoggingInterfaceCB( ) ;  //Default destructor   

    protected:

        
        /**
        * Overloaded constructor which registers the callback adders
        *
        * @param aCallBack: Callback object after reciving logging updates from core class
        * @param aInParamList: input paramater list for logging request 
        * @param aOutParamList: out put paramater list to be which will contained logging information
        * @param aModuleInfo module information of positioning module used
        */

        LoggingInterfaceCB( MLiwNotifyCallback* aCallBack ) ;



    private :

        MLiwNotifyCallback  *iCallBack ;
        CLiwGenericParamList *iOutParmList ;
        //  CLiwGenericParamList *iInParmList ;
        TUint iRequestType ;    


    };

#endif // C_LOGGINGCALLBACK_H