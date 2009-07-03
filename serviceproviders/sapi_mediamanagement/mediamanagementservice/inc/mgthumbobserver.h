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
* Description:  This Class is observer class for thumbnail generation request
*
*/

#ifndef MGTHUMBOBSERVER_H_
#define MGTHUMBOBSERVER_H_

#include<e32base.h>
#include<e32cmn.h>
#include<thumbnailmanager.h>
#include<thumbnailmanagerobserver.h>

class CThumbnailManager;
class MThumbnailObserver;
const TInt KNegative = -1;

/**
*  TThumbnailRequestInfo class This class contains the information of thumbanil generation request 
*
*  @since  Series60 v3.2
*/

class TThumbnailRequestInfo 
    {
public:
    
    /**
     * Constructor
     */                 
   
       TThumbnailRequestInfo():iObserver(NULL),iThumbnailPath(NULL),iTransactionId(KNegative),iThumbnailRequestId(KNegative)
        {
    
        }
    
    public:
        /**
         *Pointer to instance of MThumbnailObserver  
         */    
        MThumbnailObserver* iObserver;
        /**
         *Thumbnail path 
         */    
        HBufC* iThumbnailPath;
        /**
         *Transaction Id
         */    
        TInt32 iTransactionId;
        /**
         *It is thumbanil request id 
         */    
  
        TThumbnailRequestId iThumbnailRequestId;
        
    };

/**
*  CThumbnailObserver class 
*  @since  Series60 v3.2
*/
class CThumbnailObserver: public CActive ,public MThumbnailManagerObserver
    {
    public:

        /**
         * Two-phased constructor
        * @return CThumbnailObserver*  Returns the instance of
         *                                 CThumbnailObserver.
         */                 
               
        static CThumbnailObserver* NewL();
        /**
         * This method adds the thumbnail request information to observer
         *@param aObserver  Observer
         *@param aTransactionID TransactionId
         *@param aThumbnailPath Path where thumbnail will be saved
         *@param aThumbnailRequestId It request id of thumbnail generation request
         * @return void 
         */                 
        void AddToObserverL(MThumbnailObserver* aObserver,TInt32 aTransactionID ,TDesC& aThumbnailPath , TThumbnailRequestId aThumbnailRequestId);
        /**
         * This method is derived from MThumbnailManagerObserver
         *@param aThumbnail  Thumbnaildata
         *@param aThumbnailRequestId It request id of thumbnail generation request
         * @return void 
         */             
        virtual void ThumbnailPreviewReady(MThumbnailData& aThumbnail, TThumbnailRequestId aId);
        /**
         * This method is derived from MThumbnailManagerObserver
         *@param aError  Error returned to callback method
         *@param aThumbnail  Thumbnaildata
         *@param aThumbnailRequestId It request id of thumbnail generation request
         * @return void 
         */             
        virtual void ThumbnailReady(TInt aError, MThumbnailData& aThumbnail, TThumbnailRequestId aId);
        /**
          * Destructor
          */             
        ~CThumbnailObserver();
        /**
          * This method cancels the thumbnail generation request
          *@param aTransactionID Transaction Id
          * @return TInt it returns KErrNone if request is canceled otherwise system wide error 
          */     
        TInt Cancel(TInt32 aTransactionID);
            /**
            * This method sets the thumbnail manager to observer class
            *@param aThumbnailManager pointer to thumbnail manager
            * @return void  
            */    
        void SetThumbnailMangager(CThumbnailManager* aThumbnailManager);
        /**
         * User will call this method when thumbnail already exists
         * @return void  
         */    	
        void ThumbnailAlreadyExists();
    public: 
        /**
         * Methods derived from CActive
         * @return void  
         */     

        void DoCancel();
        /**
         * Methods derived from CActive
         * @return void  
         */     

        void RunL();
				        
    private: 
        /**
         * Constructor
         */     

        CThumbnailObserver();
    private:
        
        /**
         * Pointer to thumbnailManager
         */     
      
        CThumbnailManager* iThumbnailManager;
        
        /**
         * Array of TThumbnailRequestInfo
         */     

        RArray<TThumbnailRequestInfo> iThumbnailRequestArray; 
         
    };

#endif /* MGTHUMBOBSERVER_H_ */
