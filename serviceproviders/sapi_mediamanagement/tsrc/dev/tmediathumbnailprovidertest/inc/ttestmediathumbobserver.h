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
* Description:  Operation Observer is for observing operation events of the appservice class.
*  							 Client application gets notified when asynchronous operations
*                are completed.
*
*/





#include <liwcommon.h>
#include  "e32base.h" 



// CLASS DECLARATION
/**
*  CThumbnailObserver Observer is for observing operation events of the mgservice class.
*  Client application gets notified when asynchronous operations
*  are completed.
*
*
*  @since  Series60 v3.2
*/

class CThumbnailObserver : public CBase, public MLiwNotifyCallback
    {

    public:

        /**
        * Abstract method to get mgservice class events. This method is
        * called when an event is received.
        * @since  Series60 v3.2
        * @param aReason indicates error code or sucess of asynch event
        * @return void
        */
        
        
        virtual TInt HandleNotifyL(
            TInt aCmdId,
            TInt aEventId,
            CLiwGenericParamList& aEventParamList,
            const CLiwGenericParamList& aInParamList);
             
        
	     /**
        * Destructor.
        */
        virtual ~CThumbnailObserver() {
        if(iThumbnailPath)
            {
            delete iThumbnailPath;
            iThumbnailPath = NULL;
            }
        }
        
        /**
        * NewL function .
        */
        
        static CThumbnailObserver* NewL(CActiveSchedulerWait * aWait,TInt aWidth, TInt aHeight);
        
        
        TInt32 iReason;
        
        TInt32 iErrorReturn;
        
        
        TBool  iCancel;
        HBufC* iThumbnailPath ;
        
        private:
            
            CThumbnailObserver(CActiveSchedulerWait*aWait,TInt aWidth, TInt aHeight);
            
            CActiveSchedulerWait* iWait;
            
            TInt iWidth;
            TInt iHeight;
            
  
            
      

	};

