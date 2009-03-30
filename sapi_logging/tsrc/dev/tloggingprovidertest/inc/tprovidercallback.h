/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  
*
*/

#ifndef TPROVIDERCALLBACK_H
#define TPROVIDERCALLBACK_H


/**
 * Forward declartaions
 */
 
 class MLiwNotifyCallback;
// class CSapiEvent ;
 class CActiveSchedulerWait ;
 class CLiwLogIter;

/**
 * Test Case Name : AddTest1 
 * Description: Simple functionality test for Add Provider command
 * Model: sync
 * Returns: KErrnone if successfull else symbian specific error code
 */
 
 class NotifyCB: public MLiwNotifyCallback
    {
    
	public:
	 TInt HandleNotifyL(
            TInt aCmdId,
            TInt aEventId,
            CLiwGenericParamList& aEventParamList,
            const CLiwGenericParamList& aInParamList);
								   
	
	 
	 inline TInt Status(void)
	 	{
	 	 return iRetVal ;
	 	}
	 //---------------------------------------------------------
	 // Starts the wait loop
	 //---------------------------------------------------------
	 void Start() ;
	 ~NotifyCB() ;
	 
	 NotifyCB();
	 
	void  Reset()
	    {
	    delete iScheduler ;
	    iConsumer = NULL ;
	    }
	    
	 
	 //NotifyCB(Ctprovidertest *aConsumer) ;
	 
	 
	   
	 inline Ctprovidertest* GetConsumer ()
	    {
	     return iConsumer ;
	    }
	private :							   
	   CActiveSchedulerWait *iScheduler ;
	   TInt iRetVal ; 
	   Ctprovidertest *iConsumer ;
};

#endif
