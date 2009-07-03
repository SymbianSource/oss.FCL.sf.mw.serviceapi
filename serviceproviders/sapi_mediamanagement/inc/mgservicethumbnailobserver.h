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
* Description:  This class is the observer for thumbnail generation
*  *
*/


#ifndef MGSERVICETHUMBNAILOBSERVER_H_
#define MGSERVICETHUMBNAILOBSERVER_H_


#include"mgthumbnailobserver.h"

class MLiwNotifyCallback;

// CLASS DECLARATION
/**
*  It it observer for Thumbanil generation operation
* */

class CServiceThumbnailObserver : public CBase , public MThumbnailObserver
    {
    
    public:
    
        /**
            * Returns the instance of CServiceThumbnailObserver.
            * @since  Series60 v3.2
            * @param aCallback Callback 
            * @return CServiceThumbnailObserver
            */  
     
        static CServiceThumbnailObserver* NewL(MLiwNotifyCallback*  aCallback);

        /**
         * Abstract method to get thumbanil generation events. This method is
         * called when an event is received.
         * @since  Series60 v3.2
         * @param aError Error Code 
         * @param aThumbnailURL Url where thumbnail willbe present
         * @param aTransactionID Transaction Id 
         *  
         */        
        void ThumbnailReady(TInt aError, TDesC& aThumbnailURL,TInt32 aTransactionID);
        
        /**
         * Abstract method gets called when thumbanil generation events get cancel. This method is
         * called when an event is received.
         * @since  Series60 v3.2
         * @param aError Error Code 
         * @param aTransactionID Transaction Id 
         *  
         */  
        void ThumbnailRequestCancel(TInt aError,TInt32 aTransactionID);
        
        ~CServiceThumbnailObserver();
    
    
    private:
        
        /**
           * Constructor
           * @param aCallback Liw callback
           *  
           */   
        CServiceThumbnailObserver(MLiwNotifyCallback*  aCallback);
        
        /**
         * Liw Call back.
         */
         MLiwNotifyCallback* iCallBack ;        
    
    };






#endif /* MGSERVICETHUMBNAILOBSERVER_H_ */
