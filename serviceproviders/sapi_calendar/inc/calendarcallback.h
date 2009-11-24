/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Defination of class CCalendarInterface
*
*/


#ifndef __CALENDARCALLBACK_H
#define __CALENDARCALLBACK_H

#include <liwcommon.h>
#include <liwserviceifbase.h>
#include <liwbufferextension.h>

#include <calchangecallback.h>

#include "calendarheader.h"
class CCalendarInterface;

/**
* Implemenation of abstract MCalCallbackBase interface for Buffer output
* Used in Async Export operation
*
* @see MCalCallbackBase
*
*/

class CCalCallbackCalEntryList: public CBase, public MCalCallbackBase 
    {
    public:

        /**
         * Two-phase Constructor
         * @return   CMsgCallbackBase* 
        */      
        static CCalCallbackCalEntryList* NewL( CCalendarInterface& aCalendarInterface, MLiwNotifyCallback *aPtrNotifyCallback, const TDesC& aCalendarName, TInt32 aTransactionId, TBool aIsEntryArray );

        /**
         * Gives the result of asynchronous SAPI
         * @param aErrCode errcode
         * @param aResult Result
         * @return   void
        */      
        void NotifyResultL(TInt aErrCode, TAny* aResult);
        
    //    TInt32 GetTransactionID();
        ~CCalCallbackCalEntryList();
    private:

        /**
         * Constructor
        */      
        CCalCallbackCalEntryList( CCalendarInterface& aCalendarInterface, MLiwNotifyCallback *aPtrNotifyCallback,  TInt32 aTransactionId, TBool aIsEntryArray );
		void ConstructL( const TDesC& aCalendarName );
        
   private:
   TBool               iIsEntryArray;
   CCalendarInterface&     iInterface;
   /**
       * Calendar Name
      */      
      HBufC*                  iCalendarName;

  /*      MLiwNotifyCallback* iCallback;
        TInt32              iTransactionId;
        
        */

    };

class CCalCallbackBaseBuffer: public CBase, public MCalCallbackBase //USED IN CASE OF EXPORT ASYNC
	{
	public:

	  	/**
	     * Two-phase Constructor
	     * @return   CMsgCallbackBase* 
	    */		
		static CCalCallbackBaseBuffer* NewL( MLiwNotifyCallback *aPtrNotifyCallback, const CLiwGenericParamList &aPtrInParamList, TInt32 aTransactionId );

	  	/**
	     * Gives the result of asynchronous SAPI
	     * @param aErrCode errcode
	     * @param aResult Result
	     * @return   void
	    */		
		void NotifyResultL(TInt aErrCode, TAny* aResult);
		
	private:

	  	/**
	     * Constructor
	    */		
		CCalCallbackBaseBuffer( MLiwNotifyCallback *aPtrNotifyCallback, const CLiwGenericParamList &aPtrInParamList, TInt32 aTransactionId );

	};
	
/**
* Implemenation of abstract MCalCallbackBase interface for TUIDSet output
* Used in Async Import operation
*
* @see MCalCallbackBase
*
*/
class CCalCallbackBaseUIDSet: public CBase, public MCalCallbackBase 
	{
	public:

	  	/**
	     * Two-phase Constructor
	     * @return   CMsgCallbackBase* 
	    */		
		static CCalCallbackBaseUIDSet* NewL( MLiwNotifyCallback *aPtrNotifyCallback, const CLiwGenericParamList &aPtrInParamList, TInt32 aTransactionId );

	  	/**
	     * Gives the result of asynchronous SAPI
	     * @param aErrCode errcode
	     * @param aResult Result
	     * @return   void
	    */		
		void NotifyResultL(TInt aErrCode, TAny* aResult);
		
	private:

	  	/**
	     * Constructor
	    */		
		CCalCallbackBaseUIDSet( MLiwNotifyCallback *aPtrNotifyCallback, const CLiwGenericParamList &aPtrInParamList, TInt32 aTransactionId );
	};

/**
* Implemenation of abstract MCalCallbackBase interface for Error code as output
* Used in Async Delete operation
*
* @see MCalCallbackBase
*
*/
class CCalCallbackInt: public CBase, public MCalCallbackBase 
	{
	public:

	  	/**
	     * Two-phase Constructor
	     * @return   CMsgCallbackBase* 
	    */		
		static CCalCallbackInt* NewL( MLiwNotifyCallback *aPtrNotifyCallback, const CLiwGenericParamList &aPtrInParamList, TInt32 aTransactionId );

	  	/**
	     * Gives the result of asynchronous SAPI
	     * @param aErrCode errcode
	     * @param aResult Result
	     * @return   void
	    */		
		void NotifyResultL(TInt aErrCode, TAny* aResult);
		
	private:

	  	/**
	     * Constructor
	    */		
		CCalCallbackInt( MLiwNotifyCallback *aPtrNotifyCallback, const CLiwGenericParamList &aPtrInParamList, TInt32 aTransactionId );
	};

/**
* Implemenation of abstract MCalCallbackBase interface for Change Notifications
*
* @see MCalCallbackBase
*
*/
class CCalCallbackChangeNotify : public CBase, public MCalCallbackBase 
	{
	public:

	  	/**
	     * Two-phase Constructor
	     * @return   CMsgCallbackBase* 
	    */		
		static CCalCallbackChangeNotify* NewL( MLiwNotifyCallback *aPtrNotifyCallback, const CLiwGenericParamList &aPtrInParamList, TInt32 aTransactionId );

	  	/**
	     * Gives the result of asynchronous SAPI
	     * @param aErrCode errcode
	     * @param aResult Result
	     * @return   void
	    */		
		void NotifyResultL(TInt aErrCode, TAny* aResult);
		
	private:

	  	/**
	     * Constructor
	    */		
		CCalCallbackChangeNotify( MLiwNotifyCallback *aPtrNotifyCallback, const CLiwGenericParamList &aPtrInParamList, TInt32 aTransactionId );
	};
#endif __CALENDARCALLBACK_H