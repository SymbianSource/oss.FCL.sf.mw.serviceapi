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
* Description:  View observer for getlist Service API of contactservice.
*
*/




#ifndef C_CONTACTVIEWOBSERVER_H
#define C_CONTACTVIEWOBSERVER_H


#include <MVPbkContactViewObserver.h>
#include <MVPbkContactLinkArray.h>
#include "contactretrieveobserver.h"

class CContactService;

/**
  * View Flag is required so as to differentiate the callbacks, 
  * since the callback is called twice.
  */
enum TViewFlag
    {
	EContactDefaultView=0,
	EContactFilteredView
    };

/**
  * This class has methods for handling events after the view on a database is set.
  */

class CContactViewObserver:public CBase, 
						   public MVPbkContactViewObserver,
						   public MCancelAsync
{
public:
    static CContactViewObserver* NewL(MContactCallback* aCallback, 
                                      enum TViewFlag aFlag, 
                                      CContactIter* iIter, 
                                      CContactService* aContactService,
                                      const TDesC& aStoreUri, 
                                      TOrder aSortOrder, 
                                      TInt aTransId, 
                                      CActiveSchedulerWait* aSchedulerWait,
                                      TCmdType val);



/**
  * Methods to handle Contact Database View Setup events
  */
	void ContactViewReady( MVPbkContactViewBase& aView );
  
    void ContactViewUnavailable( MVPbkContactViewBase& aView ) ;
  
    void ContactAddedToView(MVPbkContactViewBase& aView, 
                            TInt aIndex, 
                            const MVPbkContactLink& aContactLink );
  
    void ContactRemovedFromView(MVPbkContactViewBase& aView, 
                                TInt aIndex, 
                                const MVPbkContactLink& aContactLink );
  
    void ContactViewError(MVPbkContactViewBase& aView, 
                          TInt aError, 
                          TBool aErrorNotified ) ;
    
	CContactViewObserver( const TDesC& aStoreUri, 
	                     enum TViewFlag aFlag, 
	                     CContactIter* aIter, 
	                     CContactService* aContactService,
	                     MContactCallback* aCallback,
	                     TOrder aSortOrder, 
	                     TInt aTransId, 
	                     CActiveSchedulerWait* aSchedulerWait,
	                     TCmdType val = EGetList);
	
	void ReturnDefaultView();

	/*
	 * Implementation of Cancel of MCancelAsync
	 */
	void Cancel();
	
private:
	
/** 
  *A method to setup the link array for the iterator to iterate over
  */
	void SetupContactLinkArrayL(MVPbkContactViewBase& aView );

private: 
	//Store Uri 
	const TDesC* iStoreUri;
	
	//Flag to determine the type of view
	TViewFlag iFlag;
	
	//Iterator - Output param
	CContactIter* iIter;
	
	//Callback Function
	MContactCallback* iCallback;
	
	//The order in which the result shud appear
	TOrder iSortOrder;
	
	//Transaction Id
	TInt iTransId;
	
	//To give default view of the database
	TBool iDefaultView;
	
	//For Stopping async calls
	CActiveSchedulerWait* iSchedulerWait;
	
	//View handle
	MVPbkContactViewBase* iView;
	
	//ContactService Handle
	CContactService* iContactService;
	TCmdType iVal;

};

#endif//C_CONTACTVIEWOBSERVER_H