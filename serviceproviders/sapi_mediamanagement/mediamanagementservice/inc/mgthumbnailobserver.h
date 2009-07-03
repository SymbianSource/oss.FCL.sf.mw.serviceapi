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
* Description:  This Class is observer for thumbnail generation
*
*/

#ifndef MGTHUMBNAILOBSERVER_H_
#define MGTHUMBNAILOBSERVER_H_
#include<e32des16.h>

/**
*  MThumbnailObserver class This class is interface for observer
*
*  @since  Series60 v3.2
*/

class MThumbnailObserver
    {

    public:
    /**
       * Abstract method to get URL of generated thumbnail. This method is
       * called when an thumbnail generation operation gets complete.
       * @since  Series60 
       * @param aError System wide error code showing success or failure of thumbnail generation
       * @param aThumbnailURL URL of generated thumbnail 
       * @param aTransactionID Transaction id of getthumbnail request
       * @return void
       */  
    
        virtual void ThumbnailReady(TInt aError, TDesC& aThumbnailURL,TInt32 aTransactionID)=0;
        /**
           * Abstract method when thumbnail request is canceled .It gets called
           * when an thumbnail generation operation gets canceled.
           * @since  Series60 
           * @param aError System wide error code showing success or failure of thumbnail generation
           * @param aTransactionID Transaction id of getthumbnail request
           * @return void  
           * */        
        virtual void ThumbnailRequestCancel(TInt aError,TInt32 aTransactionID)=0;


    };


#endif /* MGTHUMBNAILOBSERVER_H_ */
